/*
 * (C) Copyright 2011
 * Alex Waterman <imNotListening@gmail.com>
 *
 * myrt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * myrt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with myrt.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Core functionality required for the myrt library.
 */

#include <vec.h>
#include <myrt.h>
#include <parser.h>
#include <builtin_shapes.h>

#include <math.h>
#include <stdio.h>
#include <string.h>

/*
 * Required initialization.
 */
void __attribute__((constructor)) _myrt_init(void){

	myrt_dbg("Loading myrt...\n");
	_myrt_parse_init();
	_builtin_init();

}

/*
 * Any required de-initialization.
 */
void __attribute__((destructor)) _myrt_fini(void){

	myrt_dbg("Unloading myrt; goodbye.\n");
	_myrt_parse_cleanup();

}

/*
 * Routine to convert a string vector into a float. The format is expected to
 * be [ %f %f %f ]. The fourth field of the vector is set to 0 automatically.
 */
int myrt_strtovec(char *str, struct myrt_vector *vector){

	int convs;
	float x, y, z;

	convs = sscanf(str, "[ %f %f %f ]", &x, &y, &z);
	if ( convs < 3 )
		return -1;

	/* Sets w = 0 automagically. */
	VEC_SET_PTR(vector, x, y, z);
	return 0;

}

/*
 * Look up a setting for the ray tracer.
 */
struct myrt_setting *lookup_setting(char *setting){

	struct myrt_setting *tmp = settings;

	while ( tmp->name != NULL ){
		if ( strcmp(tmp->name, setting) == 0 )
			return tmp;
		tmp++;
	}

	return NULL;

}

char *_type_to_string(int type){

	switch ( type ){
	case TYPE_VECTOR:
		return "vector";
		break;
	case TYPE_FLOAT:
		return "float";
		break;
	case TYPE_INTEGER:
		return "integer";
		break;
	}

	return NULL;

}

void display_settings(){

	struct myrt_setting *s = settings;

	myrt_msg("Ray trace settings:\n");
	while ( s->name != NULL ){

		myrt_msg("%10s: %-7s ", s->name, _type_to_string(s->type));
		switch ( s->type ){
		case TYPE_VECTOR:
			displayln(&s->data.vec);
			break;
		case TYPE_FLOAT:
			printf("% .4f\n", s->data.num_f);
			break;
		case TYPE_INTEGER:
			printf("% d\n", s->data.num_i);
			break;
		}
		
		s++;

	}

}

int _myrt_scene_init(struct scene_graph *graph){

	/*
	 * Read the settings; parsed by compiler or set by user.
	 */
	graph->camera = lookup_setting("view")->data.vec;
	graph->camera.w = 1; /* Homogenious coordinates. */
	graph->fov = lookup_setting("fov")->data.num_f;
	graph->width = lookup_setting("width")->data.num_i;
	graph->height = lookup_setting("height")->data.num_i;
	graph->vert_fov = (graph->fov * graph->height) / graph->width;
	graph->aratio = graph->fov / graph->vert_fov;

	/*
	 * Make sure they make sense.
	 */
	if ( graph->fov < 0 ){
		myrt_printf(ERROR, 
			    "Field of view angle cannot be negative.\n");
		return -1;
	}
	if ( graph->width < 0 || graph->height < 0 ){
		myrt_printf(ERROR, "Width/height cannot be negative.\n");
		return -1;
	}
	
	/*
	 * Fill in some other fields based on the passed data.
	 */
	graph->vert_fov = graph->fov * 
		((float)graph->height) / ((float)graph->width);
	VEC_SET(graph->h, 1, 0, -graph->camera.x/graph->camera.z);
	copy(&graph->v, &graph->h);
	cross(&graph->v, &graph->camera);
	normalize(&graph->h);
	normalize(&graph->v);
	scale(&graph->v, -1);

	/*
	 * These fields are for generating rays from coordinates.
	 */
	graph->delta_h = graph->fov / graph->width;
	graph->delta_v = graph->vert_fov / graph->height;
	graph->x_min = -graph->width / 2.0;
	graph->y_min = -graph->height / 2.0;
	graph->cam_mag = magnitude(&graph->camera);
	copy(&graph->cam_neg, &graph->camera);
	scale(&graph->cam_neg, -1);
	graph->cam_neg.w = 0; /* This is really a direction vector. */

	return 0;

}

/*
 * Compute the vector and 
 */
void _myrt_generate_ray(struct scene_graph *graph, struct myrt_line *ray,
			int x, int y){

	float h_shift;
	float v_shift;
	float x_coord = x + graph->x_min;
	float y_coord = y + graph->y_min;
	struct myrt_vector tmp_v;

	h_shift = graph->cam_mag * tanf(graph->delta_h * x_coord *
					(M_PI / 180.0));
	v_shift = graph->cam_mag * tanf(graph->delta_v * y_coord *
					(M_PI / 180.0));

	scale(copy(&ray->traj_n, &graph->h), h_shift);
	scale(copy(&tmp_v, &graph->v), v_shift);
	
	normalize(add(add(&ray->traj_n, &tmp_v), &graph->cam_neg));
	copy(&ray->orig, &graph->camera);

}

/*
 * Trace a ray through a particular point in the scene graph.
 */
void _myrt_trace_point(struct scene_graph *graph, int x, int y){

	struct object *nearest;
	struct myrt_line ray;
	struct myrt_color color;

	/*
	 * Make the initial ray.
	 */
	_myrt_generate_ray(graph, &ray, x, y);
	
	/*
	 * We must find the particular object that this ray first intersects
	 * with.
	 */
	nearest = _myrt_find_intersection(&graph->objs, &ray);
	if ( nearest == NULL ){
		COLOR_SET(color, 0, 0, 0, 0);
		screen_write_pixel(&graph->screen, x, y, &color);
		return;
	}

	/* If there is an intersection, work out what color it is. */
	nearest->color(nearest, &color);
	myrt_printf(DBG, "Found intersection of ray, color: ");
	myrt_color_print(&color); printf("\n");
	screen_write_pixel(&graph->screen, x, y, &color);

	

}

/*
 * Trace a section of the scene graph.
 */
int _myrt_trace(struct scene_graph *graph, int row_lo, int row_hi){

	int x, y;

	if ( row_lo < 0 || row_hi > graph->height )
		return -1;

	for ( y = row_lo; y < row_hi; y++ ){
		for ( x = 0; x < graph->width; x++ ){
			_myrt_trace_point(graph, x, y);
		}
	}

	return 0;

}

/*
 * Trace out a scene. Do all the initialization before handing of control to the
 * actual tracing functions.
 */
int myrt_trace(struct scene_graph *graph){

	/*
	 * First init the screen.
	 */
	if ( screen_init(&graph->screen, graph->width, graph->height) )
		return -1;

	/*
	 * Now do the trace. To be added later: parallelize this code.
	 */
	return _myrt_trace(graph, 0, graph->height);

}

int myrt_write(struct scene_graph *graph, char *file_path){
	
	return screen_write(&graph->screen, file_path);

}
