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
 * Defines for the vector algebra.
 */

#ifndef _MYRT_VEC_H_
#define _MYRT_VEC_H_

/*
 * Use single precision floating point for performace reasons. The accuracy
 * of double precision simply isn't necessary. Although only 3 dimensions are
 * strictly necessary, 4 dimensions allows for 4D -> 3D -> 2D.
 */
struct myrt_vector {

	float x;
	float y;
	float z;
	float w;

};

typedef struct myrt_vector vec;

/* 
 * Vector functions. All functions store the result in the first operand. They
 * also return pointers to the result in order to faciliate nesting of function
 * calls.
 */
inline float               myrt_vec_dot(struct myrt_vector *a,
					struct myrt_vector *b);
inline float               myrt_vec_magnitude(struct myrt_vector *a);
inline float               myrt_vec_angle(struct myrt_vector *a,
					  struct myrt_vector *b);
inline struct myrt_vector *myrt_vec_normalize(struct myrt_vector *a);
inline struct myrt_vector *myrt_vec_add(struct myrt_vector *a,
					struct myrt_vector *b);
inline struct myrt_vector *myrt_vec_scale(struct myrt_vector *a, float factor);
inline struct myrt_vector *myrt_vec_cross(struct myrt_vector *a,
					  struct myrt_vector *b);
inline struct myrt_vector *myrt_vec_copy(struct myrt_vector *dest,
					 struct myrt_vector *src);
void                       myrt_vec_print(struct myrt_vector *a);
void                       myrt_vec_println(struct myrt_vector *a);
void                       myrt_vec_display(struct myrt_vector *a, char *msg);
int                        myrt_strtovec(char *str, struct myrt_vector *vector);

/*
 * Some structs for defining useful things: lines, planes, etc.
 */
struct myrt_line {

	struct myrt_vector orig;
	struct myrt_vector traj_n;

};


/*
 * Some macros.
 */
#define VEC_ZERO(vec)		  \
	do {			  \
		vec.x = 0;	  \
		vec.y = 0;	  \
		vec.z = 0;	  \
		vec.w = 0;	  \
	} while (0) 

#define VEC_ZERO_PTR(vec)	  \
	do {			  \
		vec->x = 0;	  \
		vec->y = 0;	  \
		vec->z = 0;	  \
		vec->w = 0;	  \
	} while (0) 

#define VEC_SET(vec, a, b, c)	  \
	do {			  \
		vec.x = a;	  \
		vec.y = b;	  \
		vec.z = c;	  \
		vec.w = 0;	  \
	} while (0) 

#define VEC_SET_PTR(vec, a, b, c)		\
	do {					\
		vec->x = a;			\
		vec->y = b;			\
		vec->z = c;			\
		vec->w = 0;			\
	} while (0) 


#define VEC_INIT(x, y, z)     { x, y, z, 0 }
#define VEC_INIT4(x, y, z, w) { x, y, z, w }

/*
 * Shorten the function names of the vector algebra.
 */
#define dot(a, b)	(myrt_vec_dot(a, b))
#define magnitude(a)	(myrt_vec_magnitude(a))
#define angle(a, b)	(myrt_vec_angle(a, b))
#define normalize(a)	(myrt_vec_normalize(a))
#define add(a, b)	(myrt_vec_add(a, b))
#define scale(a, b)	(myrt_vec_scale(a, b))
#define cross(a, b)	(myrt_vec_cross(a, b))
#define copy(a, b)	(myrt_vec_copy(a, b))
#define display(a)	(myrt_vec_print(a))
#define displayln(a)	(myrt_vec_println(a))
#define display_msg(a, msg)	(myrt_vec_display(a, msg))

#endif
