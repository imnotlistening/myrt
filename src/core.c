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
 * Core functionality required for the myrt library.
 */

#include <myrt.h>
#include <myrt_vec.h>
#include <myrt_parser.h>
#include <builtin_shapes.h>

#include <stdio.h>
#include <string.h>

/*
 * Required initialization.
 */
void __attribute__((constructor)) _myrt_init(void){

	myrt_dbg("Loading myrt...\n");
	_myrt_parse_init();
	_builtin_init();

}

/*
 * Any required de-initialization.
 */
void __attribute__((destructor)) _myrt_fini(void){

	myrt_dbg("Unloading myrt; goodbye.\n");
	_myrt_parse_cleanup();

}

/*
 * Routine to convert a string vector into a float. The format is expected to
 * be [ %f %f %f ]. The fourth field of the vector is set to 0 automatically.
 */
int myrt_strtovec(char *str, struct myrt_vector *vector){

	int convs;
	float x, y, z;

	convs = sscanf(str, "[ %f %f %f ]", &x, &y, &z);
	if ( convs < 3 )
		return -1;

	/* Sets w = 0 automagically. */
	VEC_SET_PTR(vector, x, y, z);
	return 0;

}

/*
 * Convert a vector string into a color.
 */
int myrt_strtocol(char *str, struct myrt_color *color){

	int convs;
	float x, y, z;

	convs = sscanf(str, "[ %f %f %f ]", &x, &y, &z);
	if ( convs < 3 )
		return -1;

	COLOR_SET_PTR(color, x, y, z, 1);
	return 0;

}

/*
 * Look up a setting for the ray tracer.
 */
struct myrt_setting *lookup_setting(char *setting){

	struct myrt_setting *tmp = settings;

	while ( tmp->name != NULL ){
		if ( strcmp(tmp->name, setting) == 0 )
			return tmp;
		tmp++;
	}

	return NULL;

}

char *_type_to_string(int type){

	switch ( type ){
	case TYPE_VECTOR:
		return "vector";
		break;
	case TYPE_FLOAT:
		return "float";
		break;
	case TYPE_INTEGER:
		return "integer";
		break;
	}

	return NULL;

}

void display_settings(){

	struct myrt_setting *s = settings;

	myrt_msg("Ray trace settings:\n");
	while ( s->name != NULL ){

		myrt_msg("%10s: %-7s ", s->name, _type_to_string(s->type));
		switch ( s->type ){
		case TYPE_VECTOR:
			displayln(&s->data.vec);
			break;
		case TYPE_FLOAT:
			printf("% .4f\n", s->data.num_f);
			break;
		case TYPE_INTEGER:
			printf("% d\n", s->data.num_i);
			break;
		}
		
		s++;

	}

}
