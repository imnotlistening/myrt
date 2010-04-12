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
#include <myrt_color.h>
#include <myrt_parser.h>
#include <builtin_shapes.h>

#include <stdio.h>
#include <stdlib.h>

struct object _builtin_sphere = {

	.name = "sphere",
	.init = _sphere_init,
	.free = _sphere_free,
	.parse = _sphere_parse,
	.intersection = _sphere_intersection,
	.color = _sphere_color

};

struct object _builtin_plane = {

	.name = "plane",
	.init = _plane_init,
	.free = _plane_free,
	.parse = _plane_parse,
	.intersection = _plane_intersection,
	.color = _plane_color

};

void _builtin_init(){

	myrt_add_object(&_builtin_sphere);
	myrt_add_object(&_builtin_plane);

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
	myrt_dbg("Parsed sphere: radius = %f\n", sphere->radius);
	myrt_dbg("  Origin: "); displayln(&sphere->orig);
	myrt_dbg("  Color:  "); displayln((struct myrt_vector *)&sphere->color);

	return 0;

}

int _sphere_intersection(struct object *this, struct myrt_line *ray,
			 struct myrt_vector *point){

	return 0;

}

int _sphere_color(struct object *this, struct myrt_color *color){

	return 0;

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

	

}

int _plane_parse(struct object *this){

	int token;
	char *text;
	struct _shape_plane *plane = this->priv;

	/*
	 * First: the origin vector.
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

success:
	myrt_dbg("Parsed plane: w/l = %f %f\n", plane->width, plane->length);
	myrt_dbg("  Coords: "); displayln(&plane->norm_d);
	myrt_dbg("  Color:  "); displayln((struct myrt_vector *)&plane->color);

	return 0;

}

/*
 * Determine if the passed line intersects this plane.
 */
int _plane_intersection(struct object *this, struct myrt_line *ray,
			struct myrt_vector *point){

	struct _shape_plane *plane = this->priv;
	float inter;
	float factor;

	/*
	 * If the dot product of the plane's normal vector (the x, y, z
	 * components of the plane's norm_d vector) with the direction
	 * vector of the passed line is non-zero, then the plane and
	 * line intersect.
	 */
	inter = dot(&plane->norm_d, &ray->traj_n);
	if ( inter == 0 )
		return -1;
	if ( ! point )
		return 0;

	/*
	 * If we are here, the intersection exists, and the caller wants
	 * to know what that point is.
	 */
	factor = - dot(&plane->norm_d, &ray->orig) / inter;
	myrt_dbg("Intersection factor: % 4f\n", factor);

	copy(point, &ray->traj_n);
	myrt_msg(" -> ray trajectory: "); displayln(point);

	scale(point, factor);
	myrt_msg(" -> offset from origin: "); displayln(point);

	add(point, &ray->orig);

	return 0;

}

int _plane_color(struct object *this, struct myrt_color *color){

	return 0;

}
