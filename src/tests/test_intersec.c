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
 * Test the intersection computations of the built in shapes.
 */

#include <myrt.h>
#include <myrt_vec.h>
#include <builtin_shapes.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct object plane = {
	.init = _plane_init,
	.intersection = _plane_intersection
};

struct myrt_line l;

int test_plane();
int test_sphere();

int main(int argc, char *argv[]){

	int result;
	
	/* First, test the plain. */
	result = test_plane();
	if ( result < 0 )
		myrt_printf(ERROR, "Plane test FAILED.\n");
	else
		myrt_msg("Plane test PASSED.\n");

	return 0;

}

int test_plane(){

	int ret;
	struct myrt_vector inter;
	struct _shape_plane *plane_data;

	/* Init the plane. */
	plane.init(&plane);

	/* OK, we have a default plane. Make some changes. */
	plane_data = plane.priv;
	VEC_SET(plane_data->norm_d, 1, 1, 1);
	/* From plane to origin, hence negative. */
	plane_data->norm_d.w = -10 * magnitude(&plane_data->norm_d);

	/* Now, set the line to something useful. */
	VEC_SET(l.orig, 0, 0, 0);
	l.orig.w = 1; /* Homogenious coordinate space. */
	VEC_SET(l.traj_n, 1, 0, 0);

	/* And the intersection is... */
	ret = plane.intersection(&plane, &l, &inter);
	if ( ret )
		myrt_msg("Intersection DNE.\n");
	else 
		myrt_msg("Computed Intersection: "); displayln(&inter);

	return 0;

}
