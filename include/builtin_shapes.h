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
	 * Sphere data.
	 */
	struct myrt_vector  orig;
	float               radius;
	struct myrt_color   color;

	/*
	 * Pointer to the object that contains this shere.
	 */
	struct object      *owner;

} __attribute__ ((aligned (16)));

/*
 * A plane.
 */
struct _shape_plane {

	/*
	 * The first 3 elements are the normal vector to the plane. The
	 * fourth element is the distance from the plane to the origin.
	 */
	struct myrt_vector  norm_d;
	
	/*
	 * Vectors to use for dealing with the size of a plane.
	 */
	struct myrt_vector  w_hat;
	struct myrt_vector  h_hat;

	/*
	 * Pointer to the struct object that contains this plane.
	 */
	struct object      *owner;

	/* Other useful things. */
	struct myrt_color   color;
	float               length;
	float               width;

} __attribute__ ((aligned (16)));

/*
 * A triangle.
 */
struct _shape_triangle {

	/*
	 * Normal to the triangle.
	 */
	struct myrt_vector  norm_d;

	/*
	 * The three points the define the triangle.
	 */
	struct myrt_vector  p_0;
	struct myrt_vector  p_1;
	struct myrt_vector  p_2;

	/*
	 * Pointer to the struct object that contains this triangle.
	 */
	struct object      *owner;

	/*
	 * Angle between (p_2 - p_0) and (p_1 - p_0).
	 */
	float		    ang;

	/*
	 * The color, but of course.
	 */
	struct myrt_color   color;
	
} __attribute__ ((aligned (16)));

void  _builtin_init();

/*
 * Sphere functions.
 */
int   _sphere_init(struct object *this);
void  _sphere_free(struct object *this);
int   _sphere_parse(struct object *this);
int   __sphere_intersection(struct _shape_sphere *sphere, struct myrt_line *ray,
			  struct myrt_vector *point, float *t);
int   _sphere_intersection(struct object *this, struct myrt_line *ray,
			   struct myrt_vector *point, float *t);
int   _sphere_color(struct object *this, struct myrt_color *color);
int   _sphere_normal(struct object *this, struct myrt_vector *q,
		     struct myrt_vector *n);
int   __sphere_normal(struct _shape_sphere *sphere, struct myrt_vector *q,
		    struct myrt_vector *n);

/*
 * Plane functions.
 */
int   _plane_init(struct object *this);
void  _plane_free(struct object *this);
int   _plane_parse(struct object *this);
int   _plane_intersection(struct object *this, struct myrt_line *ray,
			  struct myrt_vector *point, float *t);
int   _plane_color(struct object *this, struct myrt_color *color);
int   _plane_normal(struct object *this, struct myrt_vector *q,
		    struct myrt_vector *n);

/*
 * Triangle functions.
 */
int   _triangle_init(struct object *this);
void  _triangle_free(struct object *this);
int   _triangle_parse(struct object *this);
int   _triangle_intersection(struct object *this, struct myrt_line *ray,
			  struct myrt_vector *point, float *t);
int   _triangle_color(struct object *this, struct myrt_color *color);
int   _triangle_normal(struct object *this, struct myrt_vector *q,
		    struct myrt_vector *n);

#endif
