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
 * Defines for the built in shapes.
 */

#include <myrt.h>

#ifndef _BUILTIN_SHAPES_
#define _BUILTIN_SHAPES_

/*
 * A sphere.
 */
struct _shape_sphere {

	/*
	 * Pointer to the struct object that contains this shere.
	 */
	struct object      *owner;

	/*
	 * Sphere data.
	 */
	struct myrt_vector  orig;
	float               radius;
	struct myrt_color   color;
	float               ambience;

};

/*
 * A plane.
 */
struct _shape_plane {

	/*
	 * Pointer to the struct object that contains this plane.
	 */
	struct object      *owner;

	/*
	 * The first 3 elements are the normal vector to the plane. The
	 * fourth element is the distance from the plane to the origin.
	 */
	struct myrt_vector  norm_d;
	
	/* Other useful things. */
	struct myrt_color   color;
	float               length;
	float               width;
	float               ambience;

};

void  _builtin_init();

/*
 * Sphere functions.
 */
int   _sphere_init(struct object *this);
void  _sphere_free(struct object *this);
int   _sphere_parse(struct object *this);
int   _sphere_intersection(struct object *this, struct myrt_line *ray,
			   struct myrt_vector *point, float *t);
int   _sphere_color(struct object *this, struct myrt_color *color);

/*
 * Plane functions.
 */
int   _plane_init(struct object *this);
void  _plane_free(struct object *this);
int   _plane_parse(struct object *this);
int   _plane_intersection(struct object *this, struct myrt_line *ray,
			  struct myrt_vector *point, float *t);
int   _plane_color(struct object *this, struct myrt_color *color);


#endif
