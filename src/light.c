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
#include <light.h>
#include <parser.h>
#include <builtin_shapes.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * For the parser: define a light source.
 */
struct object _builtin_light = {

	.name = "light",
	.init = _light_init,
	.free = _light_free,
	.parse = _light_parse,
	.intersection = _light_intersection,
	.color = _light_color,
	.normal = _light_normal

};

int _light_init(struct object *this){

	struct light *light;

	light = (struct light *)malloc(sizeof(struct light));
	if ( ! light ){
		myrt_printf(ERROR, "Internal: out of memory.\n");
		return -1;
	}

	memset(light, 0, sizeof(struct light));

	/* Light fields. */
	light->owner = this;
	light->intensity = 1.0;
	light->decay = 2;
	light->glow_intersect = _light_glowsection;

	/* Field defaults for a sphere. */
	light->visual.owner = this;
	light->visual.radius = 1;
	VEC_SET(light->visual.orig, 0, 0, 0);
	COLOR_SET(light->visual.color, 255, 255, 255, 1);

	this->priv = light;
	this->light = 1;

	return 0;

}

void _light_free(struct object *this){

	free(this->priv);

}

int _light_parse(struct object *this){

	int token;
	char *text;
	struct light *light = this->priv;

	/*
	 * First: the origin vector.
	 */
	token = myrt_next_token(&text);
	if ( ! TOKEN_ACCEPT(token, TOKEN_VECTOR) )
		PARSE_ERROR("Expect vector as first field for a light.\n");
	myrt_strtovec(text, &light->visual.orig);
	light->visual.orig.w = 1;

	/* The intensity of the light. */
	token = myrt_next_token(&text);
	if ( ! TOKEN_ACCEPT(token, TOKEN_FLOAT|TOKEN_INTEGER) )
		PARSE_ERROR("Expect numeric as second field for a light.\n");
	light->intensity = atof(text);

	/* The radius. */
	token = myrt_next_token(&text);
	if ( token == TOKEN_NULL )
		goto success;
	if ( ! TOKEN_ACCEPT(token, TOKEN_FLOAT|TOKEN_INTEGER) )
		PARSE_ERROR("Expect numeric as third field for a light.\n");
	light->visual.radius = atof(text);

	/* The decay factor. */
	token = myrt_next_token(&text);
	if ( token == TOKEN_NULL )
		goto success;
	if ( ! TOKEN_ACCEPT(token, TOKEN_FLOAT|TOKEN_INTEGER) )
		PARSE_ERROR("Expect numeric as fourth field for a light.\n");
	light->decay = atof(text);

 success:
	light->glow_radius = light->visual.radius + (2 * light->visual.radius);
#ifdef _DEBUG
	myrt_dbg("Parsed light: radius = %f\n", light->visual.radius);
	myrt_dbg("  Origin: "); displayln(&light->visual.orig);
	myrt_dbg("  Intensity: %f\n", light->intensity);
	myrt_dbg("  decay: %f\n", light->decay);
#endif

	return 0;

}

int _light_intersection(struct object *this, struct myrt_line *ray,
			struct myrt_vector *point, float *t){

	struct light *light = this->priv;
	return __sphere_intersection(&light->visual, ray, point, t);

}

int _light_color(struct object *this, struct myrt_color *color){

	COLOR_SET_PTR(color, 255, 255, 255, 0);
	color->scale = 255;

	return 0;

}

int _light_normal(struct object *this, struct myrt_vector *q,
		  struct myrt_vector *n){

	struct light *light = this->priv;
	return __sphere_normal(&light->visual, q, n);

}

int _light_glowsection(struct object *this, struct myrt_line *ray,
		       struct myrt_vector *point, float *t){

	struct light *light = this->priv;
	struct _shape_sphere glow;

	copy(&glow.orig, &light->visual.orig);
	glow.radius = light->glow_radius;
	return __sphere_intersection(&glow, ray, point, t);

}

/*
 * Compute the intensity of the glow given the distance, dist, from the orig
 * of the light.
 */
float _light_glow_intensity(struct light *light, float dist){

	float k;
	float d_star = dist - light->visual.radius;
	
	k = .2 * (light->glow_radius - light->visual.radius);

	return expf(-d_star/k);

}
