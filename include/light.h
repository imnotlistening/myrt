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
 * Lighting defines. 
 */

#include <myrt.h>
#include <builtin_shapes.h>

#ifndef _LIGHT_H_
#define _LIGHT_H_

/*
 * A struct for holding light data.
 */
struct light {

	/*
	 * Has the data we need for displaying a sphere.
	 */
	struct _shape_sphere	visual;

	/*
	 * Light specific things.
	 */
	struct object	       *owner;
	float			intensity;
	float			decay;
	float			glow_radius;

	/*
	 * For the post processing glow effect of lights.
	 */
	int	(*glow_intersect)(struct object *this, struct myrt_line *ray,
				  struct myrt_vector *point, float *t);

};

/*
 * Functions for the spherical light object.
 */
int   _light_init(struct object *this);
void  _light_free(struct object *this);
int   _light_parse(struct object *this);
int   _light_intersection(struct object *this, struct myrt_line *ray,
			   struct myrt_vector *point, float *t);
int   _light_color(struct object *this, struct myrt_color *color);
int   _light_normal(struct object *this, struct myrt_vector *q,
		    struct myrt_vector *n);
int   _light_glowsection(struct object *this, struct myrt_line *ray,
			 struct myrt_vector *point, float *t);
float _light_glow_intensity(struct light *light, float dist);

#endif
