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

float _light_decay(struct light *light, float dist){

	return light->decay / (dist*dist + light->decay);

}

/*
 * Given a light source, L, normal N and a ray from the intersection to L,
 * compute the shading coefficient.
 */
float _do_shade_intersection(struct scene_graph *graph, struct light *L,
			     struct myrt_line *r, struct myrt_vector *N,
			     int tid){

	int i;
	float dist;
	float coeff = 0;
	float partial;
	float dist_scale;
	struct object *obj;
	struct myrt_line r_base;
	struct myrt_line r_prime;
	struct myrt_vector v;

	/*
	 * Increment the origin of the ray by a small fraction of its traj to
	 * avoid floating point problems.
	 */
	copy(&r_base.orig, &r->traj_n);
	scale(&r_base.orig, .0001);
	add(&r_base.orig, &r->orig);
	copy(&r_base.traj_n, &r->traj_n);
	copy(&r_prime.orig, &r_base.orig);

	copy(&v, &L->visual.orig);
	sub(&v, &r_base.orig);
	dist = magnitude(&v);
	dist_scale = L->visual.radius / dist;

	/* Compute lots of possible trajectories to the light source. */
	for ( i = 0; i < graph->density; i++ ){

		/* Modify the trajectory by a small random amount. */
		
		_myrt_rand_uvect(graph->rseeds[tid].rseed1,
				 graph->rseeds[tid].rseed2, &v);
		scale(&v, dist_scale);
		copy(&r_prime.traj_n, &r_base.traj_n);
		add(&r_prime.traj_n, &v);
		normalize(&r_prime.traj_n);

		partial = L->intensity * _light_decay(L, dist) *
			dot(&r_prime.traj_n, N);
		if ( partial < 0 ){
			continue;
		}

		/* See if the light is occluded. */
		obj = _myrt_find_intersection(&graph->objs, &r_prime, &v);
		if ( obj != L->owner ){
			continue;
		}

		/* I guess not. */
		coeff += partial;
		

	}

	return coeff / graph->density;

}

/*
 * Algorithm:
 *   For each of the lights in the scene, see if it is visible from the point
 * in question. If it is then add that shading component S. When all lights
 * have been computed, compute the combination of each component.
 */
void _shade_intersection(struct scene_graph *graph, struct myrt_vector *inter,
			 struct myrt_vector *norm, struct myrt_line *incident, 
			 struct myrt_color *color, int tid){

	int i;
	int lights = 0;
	float comp;
	float shade = 1;
	float shade_factor;
	struct light *light;
	struct object *obj;
	struct myrt_line ray;

	for ( i = 0; i < graph->objs.next; i++ ){

		obj = graph->objs.objlist[i];
		if ( ! obj->light )
			continue;
		light = obj->priv;

		/* Compute the vector from the intersection to the light. */
		copy(&ray.traj_n, &light->visual.orig);
		sub(&ray.traj_n, inter);
		normalize(&ray.traj_n);
		copy(&ray.orig, inter);

		comp = _do_shade_intersection(graph, light, &ray, norm, tid);
		shade *= (1 - comp);
		lights = 1;

	}

	/* 
	 * Now scale the passed color by the shading factor we have just
	 * computed. Take into account ambience here.
	 */
	shade_factor = graph->ambience;
	if ( lights > 0 )
		shade_factor += (1-shade);
	myrt_color_scale(color, shade_factor);

}
