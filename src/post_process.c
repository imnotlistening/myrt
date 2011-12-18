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
 * Post processing functions live here.
 */

#include <myrt.h>
#include <light.h>
#include <post_process.h>
#include <builtin_shapes.h>

#include <math.h>
#include <stdio.h>

struct post_process processes[] = {

	{ "glow",	0,	myrt_pp_glow },
	{ NULL,		0,	NULL }

};

void myrt_post_process(struct scene_graph *graph){

	int i = 0;

	for ( ; processes[i].name != NULL; i++ )
		if ( processes[i].enable )
			processes[i].process(graph);

}

struct post_process *myrt_lookup_process(char *name){

	int i = 0;

	for ( ; processes[i].name != NULL; i++ ){
		if ( strcmp(processes[i].name, name) == 0 )
			return &processes[i];
	}

	return NULL;

}

float _myrt_d_point_to_line(struct myrt_line *line, struct myrt_vector *Q){

	float proj;
	float dist_sqrd;
	struct myrt_vector diff;

	copy(&diff, Q);
	sub(&diff, &line->orig);
	
	proj = dot(&diff, &line->traj_n);
	dist_sqrd = dot(&diff, &diff) - (proj * proj);
	return sqrtf(dist_sqrd);

}

void _myrt_pp_glow(struct scene_graph *graph, struct light *light){

	int x, y;
	float dist;
	float intensity;
	struct object *obj;
	struct myrt_line ray;
	struct myrt_color color;

	for ( y = 0; y < graph->height; y++ ){
		for ( x = 0; x < graph->width; x++ ){
			
			/* The ray for the pixel. */
			_myrt_generate_ray(graph, &ray, x, y, 0, 0);
			
			/* Does this ray hit the light? */
			if ( ! _myrt_first_glowsection(&graph->objs,
						     &ray, light) )
				continue;

			obj = light->owner;
			obj->color(obj, &color);

			/*
			 * Figure out how close this ray is to the light source
			 * in order to determine the concentration of glow to
			 * add.
			 */
			dist = _myrt_d_point_to_line(&ray, &light->visual.orig);
			intensity = _light_glow_intensity(light, dist);
			myrt_color_scale(&color, intensity);
			screen_add_pixel(&graph->screen, x, y, &color);

		}
	}

}

/*
 * For each light in the scene iterate over each pixel in the screen. Compute
 * the glow contribution from the current light to that pixel. Add the combined
 * effect up at the end and add it to the pixel.
 */
void myrt_pp_glow(struct scene_graph *graph){

	int i;
	struct light *cur;

	myrt_msg("Post processing: applying glow effects.\n");

	for ( i = 0; i < graph->objs.next; i++ ){

		if ( ! graph->objs.objlist[i]->light )
			continue;

		cur = graph->objs.objlist[i]->priv;
		_myrt_pp_glow(graph, cur);

	}

}
