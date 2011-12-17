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
 * Lighting: simple lighting based on sphereical object radiating light in all
 * directions.
 */

#include <myrt.h>
#include <parser.h>
#include <builtin_shapes.h>

#include <stdio.h>
#include <stdlib.h>

struct _shape_sphere sphere;
struct myrt_line ray;
struct myrt_vector inter;

/*
 * Test if a ray and a sphere intersect.
 */
int main(int argc, char *argv[]){

	int ok;
	float t;

	/* Fill in the necessary sphere data for a test sphere. */
	VEC_ZERO(sphere.orig);
	sphere.orig.w = 1; /* Homogenious coordinate space. */
	sphere.radius = 5;

	/* And a ray pointing at the sphere. */
	VEC_SET(ray.orig, 0, 0, 30);
	VEC_SET(ray.traj_n, .165, 0, -1);
	ray.orig.w = 1; /* Homogenious coordinate space. */
	normalize(&ray.traj_n);

	ok = __sphere_intersection(&sphere, &ray, &inter, &t);
	if ( ok < 0 )
		myrt_die(1, "Sphere intersection DNE.\n");

	myrt_msg("t = %f\n", t);
	myrt_msg("Intersection: "); displayln(&inter);

	return 0;

}
