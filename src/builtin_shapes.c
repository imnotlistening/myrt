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
 * Built in shapes that can be used.
 */

#include <myrt.h>
#include <color.h>
#include <parser.h>
#include <builtin_shapes.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct object _builtin_sphere = {

	.name = "sphere",
	.init = _sphere_init,
	.free = _sphere_free,
	.parse = _sphere_parse,
	.intersection = _sphere_intersection,
	.color = _sphere_color,
	.normal = _sphere_normal

};

struct object _builtin_plane = {

	.name = "plane",
	.init = _plane_init,
	.free = _plane_free,
	.parse = _plane_parse,
	.intersection = _plane_intersection,
	.color = _plane_color,
	.normal = _plane_normal

};

struct object _builtin_triangle = {

	.name = "triangle",
	.init = _triangle_init,
	.free = _triangle_free,
	.parse = _triangle_parse,
	.intersection = _triangle_intersection,
	.color = _triangle_color,
	.normal = _triangle_normal

};

extern struct object _builtin_light;

void _builtin_init(){

	myrt_add_object(&_builtin_sphere);
	myrt_add_object(&_builtin_triangle);
	myrt_add_object(&_builtin_plane);
	myrt_add_object(&_builtin_light);

}

/*
 * You need only init the priv field of the passed object stuct. The function
 * pointers will have already been initialized for you. Return 0 for success,
 * less than 0 for error.
 */
int _sphere_init(struct object *this){

	struct _shape_sphere *sphere;

	sphere = (struct _shape_sphere *)malloc(sizeof(struct _shape_sphere));
	if ( ! sphere ){
		myrt_printf(ERROR, "Internal: out of memory.\n");
		return -1;
	}

	memset(sphere, 0, sizeof(struct _shape_sphere));

	/* Field defaults for a sphere. */
	sphere->owner = this;
	sphere->radius = 1;
	VEC_SET(sphere->orig, 0, 0, 0);
	COLOR_SET(sphere->color, 255, 0, 0, 1);

	this->priv = sphere;

	return 0;

}

void _sphere_free(struct object *this){

	free(this->priv);

}

int _sphere_parse(struct object *this){

	int token;
	char *text;
	struct _shape_sphere *sphere = this->priv;

	/* 
	 * Very simplistic. Just go through each field of the sphere and match
	 * the next token to it. If the token types don't match, then fail.
	 *
	 * First: the origin vector.
	 */
	token = myrt_next_token(&text);
	if ( ! TOKEN_ACCEPT(token, TOKEN_VECTOR) )
		PARSE_ERROR("Expect vector as first field for a sphere.\n");
	myrt_strtovec(text, &sphere->orig);
	sphere->orig.w = 1;

	/* Next: radius. */
	token = myrt_next_token(&text);
	if ( token == TOKEN_NULL )
		goto success;
	if ( ! TOKEN_ACCEPT(token, TOKEN_FLOAT|TOKEN_INTEGER) )
		PARSE_ERROR("Expect numeric as second field for a sphere.\n");
	sphere->radius = atof(text);

	/* Next: color. */
	token = myrt_next_token(&text);
	if ( token == TOKEN_NULL )
		goto success;
	if ( ! TOKEN_ACCEPT(token, TOKEN_VECTOR) )
		PARSE_ERROR("Expect vector as third field for a sphere.\n");
	myrt_strtocol(text, &sphere->color);	

 success:
#ifdef _DEBUG
	myrt_dbg("Parsed sphere: radius = %f\n", sphere->radius);
	myrt_dbg("  Origin: "); displayln(&sphere->orig);
	myrt_dbg("  Color:  "); displayln((struct myrt_vector *)&sphere->color);
#endif

	return 0;

}

/*
 * Compute the intersection for a sphere. Implemented here so that the light
 * source can also piggy back of this implementation as well.
 */
int __sphere_intersection(struct _shape_sphere *sphere, struct myrt_line *ray,
			  struct myrt_vector *point, float *t){
	
	float v_d;
	float disc;
	float v_squared;
	float v_d_squared;
	struct myrt_vector v;

	copy(&v, &ray->orig);
	sub(&v, &sphere->orig);

	/* Compute some temporaries */
	v_d = dot(&v, &ray->traj_n);
	v_d_squared = v_d * v_d;
	v_squared = dot(&v, &v);

	/* The discriminant; if negative, no intersection. */
	disc = v_d_squared - (v_squared - (sphere->radius * sphere->radius));
	if ( disc < 0 )
		return -1;
	disc = sqrtf(disc);

	/* Otherwise, compute minimum t. */
	*t = fminf(-v_d + disc, -v_d - disc);
	if ( *t < 0 )
		return -1;

	/* Fill in the passed data pointers. */
	copy(point, &ray->traj_n);
	scale(point, *t);
	add(point, &ray->orig);

	return 0;

}

int __sphere_normal(struct _shape_sphere *sphere, struct myrt_vector *q,
		    struct myrt_vector *n){

	copy(n, q);
	sub(n, &sphere->orig);
	normalize(n);

	return 0;

}

int _sphere_intersection(struct object *this, struct myrt_line *ray,
			 struct myrt_vector *point, float *t){

	struct _shape_sphere *sphere = this->priv;
	return __sphere_intersection(sphere, ray, point, t);

}

int _sphere_color(struct object *this, struct myrt_color *color){

	struct _shape_sphere *sphere = this->priv;

	myrt_color_copy(color, &sphere->color);
	
	return 0;

}

int _sphere_normal(struct object *this, struct myrt_vector *q,
		   struct myrt_vector *n){

	struct _shape_sphere *sphere = this->priv;
	return __sphere_normal(sphere, q, n);

}

int _plane_init(struct object *this){

	struct _shape_plane *plane;

	plane = (struct _shape_plane *)malloc(sizeof(struct _shape_plane));
	if ( ! plane ){
		myrt_printf(ERROR, "Internal: out of memory.\n");
		return -1;
	}

	plane->owner = this;
	VEC_SET(plane->norm_d, 0, 1, 0); /* w = 0 */
	COLOR_SET(plane->color, 255, 255, 255, 1);

	/* Width/length = 0 implies infinite. */
	plane->width = 0;
	plane->length = 0;

	this->priv = plane;

	return 0;

}

void _plane_free(struct object *this){

	free(this->priv);

}

void _plane_generate_bounds(struct _shape_plane *plane){
	
	float r, x;
	float theta;
	float y1, y2;
	struct myrt_vector h = VEC_INIT(0, 1, 0);
	struct myrt_vector w;

	theta = angle(&plane->norm_d, &h);
	if ( theta == 0 ){ /* Plane normal = y-axis */
		plane->h_hat.z = 1;
		plane->w_hat.x = 1;
		goto msg_and_return;
	} else if ( theta == M_PI_2 ){
		plane->h_hat.y = 1;
		copy(&plane->w_hat, &plane->norm_d);
		cross(&plane->w_hat, &plane->h_hat);
		normalize(&plane->w_hat);
		goto msg_and_return;
	}

	r = magnitude(&plane->norm_d);
	y1 = r * cosf(theta);

	x = sqrt((r * r) - (y1 * y1));
	y2 = x * tanf(theta);

	h.y = y1 + y2;
	sub(&h, &plane->norm_d);
	normalize(&h);

	copy(&w, &plane->norm_d);
	cross(&w, &h);
	normalize(&w);

	copy(&plane->h_hat, &h);
	copy(&plane->w_hat, &w);

 msg_and_return:
	myrt_msg("Plane size basis vectors:\n");
	myrt_msg("  h: "); displayln(&plane->h_hat);
	myrt_msg("  w: "); displayln(&plane->w_hat);

}

int _plane_parse(struct object *this){

	int token;
	char *text;
	struct _shape_plane *plane = this->priv;

	/*
	 * First: the origin vector and the offset.
	 */
	token = myrt_next_token(&text);
	if ( ! TOKEN_ACCEPT(token, TOKEN_VECTOR) )
		PARSE_ERROR("Expect vector as first field for a plane.\n");
	myrt_strtovec(text, &plane->norm_d);	

	token = myrt_next_token(&text);
	if ( ! TOKEN_ACCEPT(token, TOKEN_FLOAT|TOKEN_INTEGER) )
		PARSE_ERROR("Expect numeric as second field for a plane.\n");
	plane->norm_d.w = -atof(text) * magnitude(&plane->norm_d);

	/* Next: color. */
	token = myrt_next_token(&text);
	if ( token == TOKEN_NULL )
		goto success;
	if ( ! TOKEN_ACCEPT(token, TOKEN_VECTOR) )
		PARSE_ERROR("Expect vector as third field for a plane.\n");
	myrt_strtocol(text, &plane->color);

	/* Next: length */
	token = myrt_next_token(&text);
	if ( token == TOKEN_NULL )
		goto success;
	if ( ! TOKEN_ACCEPT(token, TOKEN_FLOAT|TOKEN_INTEGER) )
		PARSE_ERROR("Expect numeric for length/width of a plane.\n");
	plane->length = atof(text);

	/* And now width. If length is specified, then width is required too. */
	token = myrt_next_token(&text);
	if ( token == TOKEN_NULL )
		PARSE_ERROR("Width required when "
			    "specifiying length of plane.\n");
	if ( ! TOKEN_ACCEPT(token, TOKEN_FLOAT|TOKEN_INTEGER) )
		PARSE_ERROR("Expect numeric for length/width of a plane.\n");
	plane->width = atof(text);

	_plane_generate_bounds(plane);

success:
#ifdef _DEBUG
	myrt_dbg("Parsed plane: w/l = %.2f %.2f\n", 
		 plane->width, plane->length);
	myrt_dbg("  Coords: "); displayln(&plane->norm_d);
	myrt_dbg("  Color:  "); displayln((struct myrt_vector *)&plane->color);
#endif

	return 0;

}

/*
 * Determine if the passed line intersects this plane.
 */
int _plane_intersection(struct object *this, struct myrt_line *ray,
			struct myrt_vector *point, float *t){

	struct _shape_plane *plane = this->priv;
	float inter;
	float factor;
	struct myrt_vector proj_h;
	struct myrt_vector proj_w;

	/*
	 * If the dot product of the plane's normal vector (the x, y, z
	 * components of the plane's norm_d vector) with the direction
	 * vector of the passed line is non-zero, then the plane and
	 * line intersect.
	 */
	inter = dot(&plane->norm_d, &ray->traj_n);
	if ( inter == 0 )
		return -1;

	/*
	 * If we are here, the intersection exists, and the caller wants
	 * to know what that point is.
	 */
	factor = - dot(&plane->norm_d, &ray->orig) / inter;
	
	/* Oops, intersects *behind* the camera. */
	if ( factor < 0 )
		return -1;

	copy(point, &ray->traj_n);
	scale(point, factor);
	add(point, &ray->orig);
	*t = factor;

	/*
	 * Check now to see if the intersection is in bounds of the plane. This
	 * assumes w_hat and h_hat have a length of 1.
	 */
	if ( plane->width > 0 && plane->length > 0 ){
		copy(&proj_h, &plane->h_hat);
		scale(&proj_h, dot(&plane->h_hat, point));
		if ( plane->length < magnitude(&proj_h) )
			return -1;
		copy(&proj_w, &plane->w_hat);
		scale(&proj_w, dot(&plane->w_hat, point));
		if ( plane->width < magnitude(&proj_w) )
			return -1;
	}
	return 0;

}

int _plane_color(struct object *this, struct myrt_color *color){

	struct _shape_plane *plane = this->priv;

	myrt_color_copy(color, &plane->color);
	
	return 0;

}

int _plane_normal(struct object *this, struct myrt_vector *q,
		  struct myrt_vector *n){

	struct _shape_plane *plane = this->priv;

	copy(n, &plane->norm_d);
	n->w = 0;
	normalize(n);

	return 0;

}

int _triangle_init(struct object *this){

	return 0;

}

void _triangle_free(struct object *this){

	free(this->priv);

}

int _triangle_parse(struct object *this){

	return 0;

}

int _triangle_intersection(struct object *this, struct myrt_line *ray,
			   struct myrt_vector *point, float *t){

	//struct _shape_triangle *triangle = this->priv;
	return 0;

}

int _triangle_color(struct object *this, struct myrt_color *color){

	struct _shape_triangle *triangle = this->priv;

	myrt_color_copy(color, &triangle->color);
	
	return 0;

}

int _triangle_normal(struct object *this, struct myrt_vector *q,
		     struct myrt_vector *n){

	//struct _shape_triangle *triangle = this->priv;


	return 0;

}
