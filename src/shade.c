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
 * Very simple cosine implementation of a shader for the ray tracer.
 */

#include <myrt.h>
#include <light.h>

/*
 * Algorithm:
 *   For each of the lights in the scene, see if it is visible from the point
 * in question. If it is then add that shading component S. When all lights
 * have been computed, compute the mean of S by dividing S by the number of
 * lights in the scene.
 */
void _shade_intersection(struct scene_graph *graph, struct myrt_vector *inter,
			 struct myrt_vector *norm, struct myrt_line *incident, 
			 struct myrt_color *color){

	int i;
	float comp;
	float shade = 1;
	float lights = 0;
	float shade_factor;
	struct light *light;
	struct object *obj;
	struct object *ray_inter;
	struct myrt_line norm_traj;
	struct myrt_vector dummy;

	for ( i = 0; i < graph->objs.next; i++ ){

		obj = graph->objs.objlist[i];
		if ( ! obj->light )
			continue;
		light = obj->priv;

		/* Compute the vector from the intersection to the light. */
		copy(&norm_traj.traj_n, &light->visual.orig);
		sub(&norm_traj.traj_n, inter);
		normalize(&norm_traj.traj_n);

		/*
		 * Compute the shading factor here so we can skip negative
		 * shades. 
		 */
		comp = dot(&norm_traj.traj_n, norm);
		if ( comp < 0 )
			continue;

		/* Now, make a ray that represents this vector. */
		copy(&norm_traj.orig, &norm_traj.traj_n);
		scale(&norm_traj.orig, .0001); /* Fix floating point err. */
		add(&norm_traj.orig, inter);

		/* Figure out if the ray makes it to the light. */
		ray_inter = _myrt_find_intersection(&graph->objs, &norm_traj,
						    &dummy);
		if ( ray_inter != obj )
			continue;

		/* The ray was not occluded... */
		comp *= light->intensity;
		if ( comp > 1 )
			comp = 1;
		shade *= (1 - comp);
		lights = 1;

	}

	/* 
	 * Now scale the passed color by the shading factor we have just
	 * computed. Take into account ambience here.
	 */
	shade_factor = graph->ambience;
	if ( lights > 0 )
		shade_factor += (graph->diffusion * (1-shade));
	//myrt_msg("shade factor: %f\n", shade_factor);
	myrt_color_scale(color, shade_factor);

}
