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
 * Generic implementation of the vector algebra required for ray tracing.
 */

#include <vec.h>
#include <myrt.h>

#include <math.h>
#include <stdio.h>
#include <string.h>

inline float myrt_vec_dot(struct myrt_vector *a, struct myrt_vector *b){

	return (a->x * b->x) + (a->y * b->y) + (a->z * b->z) + (a->w * b->w);

}

inline float myrt_vec_magnitude(struct myrt_vector *a){

	return sqrt(myrt_vec_dot(a, a));

}

inline float myrt_vec_angle(struct myrt_vector *a, struct myrt_vector *b){

	float num = myrt_vec_dot(a, b);
	float denom = sqrtf(myrt_vec_dot(a, a)) * 
		sqrtf(myrt_vec_dot(b, b));

	return acosf(num/denom);


}

inline struct myrt_vector *myrt_vec_normalize(struct myrt_vector *a){

	return myrt_vec_scale(a, 1 / myrt_vec_magnitude(a));

}

inline struct myrt_vector *myrt_vec_add(struct myrt_vector *a,
				 struct myrt_vector *b){

	a->x += b->x;
	a->y += b->y;
	a->z += b->z;
	a->w += b->w;

	return a;

}

inline struct myrt_vector *myrt_vec_sub(struct myrt_vector *a,
				 struct myrt_vector *b){

	a->x -= b->x;
	a->y -= b->y;
	a->z -= b->z;
	a->w -= b->w;

	return a;

}

inline struct myrt_vector *myrt_vec_scale(struct myrt_vector *a, float factor){

	a->x *= factor;
	a->y *= factor;
	a->z *= factor;
	a->w *= factor;

	return a;

}

inline struct myrt_vector *myrt_vec_cross(struct myrt_vector *a,
					  struct myrt_vector *b){

	float x, y, z;
	x = a->y * b->z - a->z * b->y;
	y = a->z * b->x - a->x * b->z;
	z = a->x * b->y - a->y * b->x;

	a->x = x;
	a->y = y;
	a->z = z;
	
	return a;

}

inline struct myrt_vector *myrt_vec_copy(struct myrt_vector *dest,
					 struct myrt_vector *src){

	memcpy(dest, src, sizeof(struct myrt_vector));
	return dest;

}

void myrt_vec_print(struct myrt_vector *a){

	printf("[% .4f % .4f % .4f % .4f]", a->x, a->y, a->z, a->w);


}

void myrt_vec_println(struct myrt_vector *a){

	myrt_vec_print(a);
	printf("\n");

}

void myrt_vec_display(struct myrt_vector *a, char *msg){

	myrt_msg(msg);
	myrt_vec_print(a);
	printf("\n");

}
