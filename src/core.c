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
#include <light.h>
#include <parser.h>
#include <post_process.h>
#include <builtin_shapes.h>

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/timeb.h>

#define CHUNKS_PER_THREAD	8

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

void _myrt_init_thread_seed(struct thread_seed *seed){

	int i;

	for ( i = 0; i < 3; i++ )
		seed->rseed1[i] = (unsigned short) (rand() & 0xFFFF);
	for ( i = 0; i < 3; i++ )
		seed->rseed2[i] = (unsigned short) (rand() & 0xFFFF);
	for ( i = 0; i < 3; i++ )
		seed->rseed3[i] = (unsigned short) (rand() & 0xFFFF);


}

int _myrt_scene_init(struct scene_graph *graph){

	int i;
	float h_max;
	float v_max;

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
	graph->density = lookup_setting("density")->data.num_i;
	graph->depth = lookup_setting("depth")->data.num_i;
	graph->aaliasing = lookup_setting("aaliasing")->data.num_i;
	graph->ambience = lookup_setting("ambience")->data.num_f;
	if ( graph->ambience > 1 )
		graph->ambience = 1;
	if ( graph->ambience < 0 )
		graph->ambience = 0;
	graph->diffusion = 1 - graph->ambience;
	graph->ambient_color.red = graph->ambient_color.green = 
		graph->ambient_color.blue = (graph->ambience * 255);
	graph->ambient_color.scale = 0;

	/*
	 * Make sure the settings make sense.
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
	if ( graph->aaliasing != 1 && graph->aaliasing != 4 &&
	     graph->aaliasing != 16 ){
		myrt_printf(WARN, "Invalid A-Aliasing value chosen: %d\n",
			    graph->aaliasing);
		myrt_printf(WARN, "  Using x1. (Possible values: x1 x4 x16)\n");
		graph->aaliasing = 1;
	}
	graph->aaliasing_sqrt = sqrt(graph->aaliasing);

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
	graph->cam_mag = magnitude(&graph->camera);
	copy(&graph->cam_neg, &graph->camera);
	scale(&graph->cam_neg, -1);
	graph->cam_neg.w = 0; /* This is really a direction vector. */

	h_max = tanf((graph->fov/2) * (M_PI/180)) * graph->cam_mag;
	v_max = tanf((graph->vert_fov/2) * (M_PI/180)) * graph->cam_mag;
	graph->delta_h = (2 * h_max) / graph->width;
	graph->delta_v = (2 * v_max) / graph->height;
	graph->x_min = -graph->width / 2.0;
	graph->y_min = -graph->height / 2.0;

	/*
	 * Finally, the thread stuff and random state.
	 */
	graph->threads = lookup_setting("threads")->data.num_i;

	/* Make some random numbers. */
	if ( ! graph->threads ){
		graph->rseeds = (struct thread_seed *)
			malloc(sizeof(struct thread_seed));
		_myrt_init_thread_seed(graph->rseeds);
	} else {
		graph->rseeds = (struct thread_seed *)
			malloc(sizeof(struct thread_seed) * graph->threads);
		for ( i = 0; i < graph->threads; i++ ){
			_myrt_init_thread_seed(graph->rseeds + i);
		}
	}

	return 0;

}

/*
 * Compute an intial ray. ax and ay are the aliasing params.
 */
void _myrt_generate_ray(struct scene_graph *graph, struct myrt_line *ray,
			int x, int y, int ax, int ay){

	float h_shift;
	float v_shift;
	float x_coord = x + graph->x_min;
	float y_coord = y + graph->y_min;
	struct myrt_vector tmp_v;

	x_coord += ax / graph->aaliasing_sqrt;
	y_coord += ay / graph->aaliasing_sqrt;

	h_shift = (x_coord * graph->delta_h);
	v_shift = (y_coord * graph->delta_v);

	scale(copy(&ray->traj_n, &graph->h), h_shift);
	scale(copy(&tmp_v, &graph->v), v_shift);
	
	normalize(add(add(&ray->traj_n, &tmp_v), &graph->cam_neg));
	copy(&ray->orig, &graph->camera);

	ray->reflections = 0;

}

void _myrt_rand_uvect(unsigned short int *rseed1, unsigned short int *rseed2,
		      struct myrt_vector *dest){

	float z, t, r;

	z = (float) (erand48(rseed1) * 2) - 1;
	t = (float) (erand48(rseed2) * 2 * M_PI);
	r = sqrt(1 - z*z);

	dest->x = r * cos(t);
	dest->y = r * sin(t);
	dest->z = z;
	dest->w = 0;

	normalize(dest);

}

void _myrt_rand_vector(unsigned short int *rseed1, unsigned short int *rseed2,
		       struct myrt_vector *norm, struct myrt_vector *dest){

	_myrt_rand_uvect(rseed1, rseed2, dest);

	if ( dot(norm, dest) < 0 )
		scale(dest, -1);

}

void _myrt_trace_path(struct scene_graph *graph, struct myrt_line *line,
		      struct myrt_color *color, int tid){

	struct object *nearest;
	struct myrt_line refl;
	struct myrt_color col;
	struct myrt_color refl_col;
	struct myrt_vector norm;
	struct myrt_vector inter;

	/* End of recursion. */
	if ( line->reflections >= graph->depth ){
		COLOR_SET_PTR(color, 0, 0, 0, 0);
		return;
	}

	/* Find the nearest object to us. */
	nearest = _myrt_find_intersection(&graph->objs, line, &inter);
	if ( nearest == NULL ){
		if ( line->reflections == 0 )
			COLOR_SET_PTR(color, 0, 0, 0, 0);
		else
			myrt_color_copy(color, &graph->ambient_color);
		return;
	}

	/*
	 * Terminate recursion on a light source.
	 */
	if ( nearest->light ){
		nearest->color(nearest, color);
		return;
	}

	/* Now get some info about the object. */
	nearest->normal(nearest, &inter, &norm);
	nearest->color(nearest, &col);

	/* Compute the reflected contribution of the light. */
	_myrt_rand_vector(graph->rseeds[tid].rseed1,
			  graph->rseeds[tid].rseed2, &norm, &refl.traj_n);
	copy(&refl.orig, &refl.traj_n);
	scale(&refl.orig, 0.0001);
	add(&refl.orig, &inter);
	refl.reflections = line->reflections + 1;
	_myrt_trace_path(graph, &refl, &refl_col, tid);

	myrt_color_mult(&col, &refl_col);
	myrt_color_copy(color, &col);

}

/*
 * Trace a ray through a particular point in the scene graph.
 */
void _myrt_trace_point(struct scene_graph *graph, int x, int y, int tid){

	int i;
	struct myrt_line ray;
	struct myrt_color tmp;
	struct myrt_color color = COLOR_INIT(0, 0, 0, 0);

	/*
	 * Make the initial ray. No AAliasing for path tracing.
	 */
	_myrt_generate_ray(graph, &ray, x, y, 0, 0);

	/*
	 * Call the recursive ray casting function a whole bunch of times.
	 */
	for ( i = 0; i < graph->density; i++ ){
		_myrt_trace_path(graph, &ray, &tmp, tid);
		myrt_color_cmean(&color, &tmp, i);
	}
	
	if ( color.red > 255 )
		color.red = 255;
	if ( color.green > 255 )
		color.green = 255;
	if ( color.blue > 255 )
		color.blue = 255;

	/* And finally write out the pixel to the screen. */
	color.scale = 255;
	screen_write_pixel(&graph->screen, x, y, &color);

}

/*
 * Trace a section of the scene graph using a path tracing model.
 */
int _myrt_model_path_trace(struct scene_graph *graph, 
			   int row_lo, int row_hi, int tid){

	int x, y;

	if ( row_lo < 0 || row_hi > graph->height )
		return -1;

	for ( y = row_lo; y < row_hi; y++ ){
		for ( x = 0; x < graph->width; x++ ){
			_myrt_trace_point(graph, x, y, tid);
		}
	}

	return 0;

}

/*
 * Core ray tracing code. Compute the color of a given point that is intersected
 * by the passed line.
 */
void _myrt_do_ray_trace(struct scene_graph *graph, struct myrt_line *line,
			struct myrt_color *color, int tid){

	struct object *nearest;
	struct myrt_line refl_ray;
	struct myrt_color diffuse;
	struct myrt_color reflected;
	struct myrt_vector inter;
	struct myrt_vector normal;

	if ( line->reflections > graph->depth ){
		myrt_color_copy(color, &graph->ambient_color);
		return;
	}

	/*
	 * First things first, compute the first intersection of the passed
	 * line.
	 */
	nearest = _myrt_find_intersection(&graph->objs, line, &inter);
	if ( nearest == NULL ){
		if ( line->reflections == 0 )
			COLOR_SET_PTR(color, 0, 0, 0, 0);
		else
			myrt_color_copy(color, &graph->ambient_color);
		return;
	}

	/*
	 * Figure out the color and normal of the object where we intersected.
	 */
	nearest->color(nearest, &diffuse);
	nearest->normal(nearest, &inter, &normal);

	if ( nearest->light ){
		myrt_color_copy(color, &diffuse);
		return;
	}

	/*
	 * Work out the shading for the point.
	 */
	_shade_intersection(graph, &inter, &normal, line, &diffuse, tid);
	/*printf("Shaded (%d): [%.0f %.0f %.0f]\n", line->reflections,
	  diffuse.red, diffuse.green, diffuse.blue);*/

	/*
	 * Work out the reflectance (if its non-zero);
	 */
	if ( nearest->reflectance == 0 ){
		COLOR_SET(reflected, 0, 0, 0, 0);
	} else {
		/* Compute the reflected ray. */
		copy(&refl_ray.orig, &line->traj_n);
		scale(&refl_ray.orig, .1);
		add(&refl_ray.orig, &line->orig);
		copy(&refl_ray.traj_n, &line->traj_n);
		refl_ray.reflections = line->reflections + 1;
		refl(&refl_ray.traj_n, &normal);
		_myrt_do_ray_trace(graph, &refl_ray, &reflected, tid);
	}

	/*
	 * Combine the reflected and diffuse components.
	 */
	myrt_color_scale(&diffuse, nearest->diffusion);
	myrt_color_scale(&reflected, nearest->reflectance);
	if ( line->reflections == -1 && reflected.blue > 150 )
		printf("reflected color: [%.0f %.0f %.0f] (scale=%f)\n",
		       reflected.red, reflected.green,
		       reflected.blue, nearest->reflectance);
	myrt_color_cadd(&diffuse, &reflected);
	myrt_color_copy(color, &diffuse);

}

/*
 * Pixel by pixel ray tracing model. Lighting is computed for every impact.
 */
int _myrt_trace_ray(struct scene_graph *graph, int x, int y, int tid){

	int ax, ay, i = 0;
	struct myrt_line ray;
	struct myrt_color sample;
	struct myrt_color pixel = COLOR_INIT(0, 0, 0, 0);

	for ( ax = 0; ax < graph->aaliasing_sqrt; ax++ ){
		for ( ay = 0; ay < graph->aaliasing_sqrt; ay++ ){
			/*
			 * Make the initial ray.
			 */
			_myrt_generate_ray(graph, &ray, x, y, ax, ay);

			/*
			 * Trace the ray.
			 */
			_myrt_do_ray_trace(graph, &ray, &sample, tid);

			myrt_color_cmean(&pixel, &sample, i++);

		}
	}

	/*
	 * In case stuff is over sampled.
	 */
	if ( pixel.red > 255 )
		pixel.red = 255;
	if ( pixel.green > 255 )
		pixel.green = 255;
	if ( pixel.blue > 255 )
		pixel.blue = 255;

	pixel.scale = 255;
	screen_write_pixel(&graph->screen, x, y, &pixel);

	return 0;

}

/*
 * Trace a scene using a normal reverse ray tracing model.
 */
int _myrt_model_ray_trace(struct scene_graph *graph,
			  int row_lo, int row_hi, int tid){

	int x, y;

	if ( row_lo < 0 || row_hi > graph->height )
		return -1;

	for ( y = row_lo; y < row_hi; y++ ){
		for ( x = 0; x < graph->width; x++ ){
			_myrt_trace_ray(graph, x, y, tid);
		}
	}

	return 0;

}

/*
 * The actual worker for a thread.
 */
void *_myrt_do_trace_par(void *data){

	int i;
	int tid;
	int start, stop;
	int chunk_size;
	struct thread_arg *arg = data;
	struct scene_graph *graph;
	
#ifdef _TIMING
	time_t t_start;
	time_t t_delta;
	struct timeb tmp_time;
#endif

	tid = arg->tid;
	graph = arg->graph;
	chunk_size = graph->height / (CHUNKS_PER_THREAD * graph->threads);
	if ( chunk_size == 0 )
		chunk_size = 1;

	/* Now get to work. */
	for ( i = 0; i < CHUNKS_PER_THREAD; i++ ){

		start = (i * graph->threads + tid) * chunk_size;
		stop = start + chunk_size;

#ifdef _TIMING
		ftime(&tmp_time);
		t_start = (tmp_time.time * 1000) + tmp_time.millitm;
#endif
		graph->model->trace(graph, start, stop, tid);
#ifdef _TIMING
		ftime(&tmp_time);
		t_delta = (tmp_time.time * 1000) + tmp_time.millitm;
		myrt_msg("> [%d] Computed %d -> %d: %u ms\n", tid, start, stop,
			 (unsigned int) (t_delta - t_start));
#endif

	}

	myrt_dbg("Thread (%d) done.\n", tid);
	return 0;

}

/*
 * Break the scene up into 8 x #threads. Let each thread take parts of the
 * scene that are multiples of its thread ID (TIDs exist in 0 -> #threads). If
 * this schedule is insufficient for good parallelization, then I will think
 * about using something else.
 */
int _myrt_trace_par(struct scene_graph *graph){

	int tid;
	pthread_t threads[graph->threads];
	struct thread_arg args[graph->threads];

	for ( tid = 0; tid < graph->threads; tid++ ){
		args[tid].tid = tid;
		args[tid].graph = graph;
		if ( pthread_create(&threads[tid], NULL, _myrt_do_trace_par,
				    &args[tid]) )
			myrt_die(1, "Failed to start thread.\n");
	}

	for ( tid = 0; tid < graph->threads; tid++ )
		pthread_join(threads[tid], NULL);

	return 0;

}

int _myrt_trace_seq(struct scene_graph *graph){

	/*
	 * Do the trace sequentially (i.e just one thread).
	 */
	return graph->model->trace(graph, 0, graph->height, 0);

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

	if ( graph->threads ){
		myrt_msg("Running parallel trace: "
			 "%d threads\n", graph->threads);
		_myrt_trace_par(graph);
	} else {
		myrt_msg("Running sequential trace\n");
		_myrt_trace_seq(graph);

	}

	/*
	 * Now run any post processing effects.
	 */
	myrt_post_process(graph);

	return 0;

}

int myrt_write(struct scene_graph *graph, char *file_path){
	
	return screen_write(&graph->screen, file_path);

}
