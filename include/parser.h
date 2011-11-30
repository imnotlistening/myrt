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
 * Definitions for the parser component of the ray tracer.
 */

#include <vec.h>
#include <myrt.h>

#include <stdio.h>

#ifndef _MYRT_PARSER_H_
#define _MYRT_PARSER_H_

/*
 * Line number for the parse.
 */
extern int __line_no;

/*
 * Tokens.
 */
#define TOKEN_NULL	0x00
#define TOKEN_COMMENT	0x01
#define TOKEN_SHAPE	0x02
#define TOKEN_FLOAT	0x04
#define TOKEN_VECTOR	0x08
#define TOKEN_INTEGER	0x10
#define TOKEN_NEWLINE	0x20
#define TOKEN_EOF	(~0)

/*
 * Setting struct. Specifies a setting that can be set. :).
 */
struct myrt_setting {

	/*
	 * Name of the setting as it should appear in a source file.
	 */
	char *name;

	/*
	 * And the data: type - vector or numeric - and a union for the data.
	 */
	int   type;
	union {

		struct myrt_vector vec;
		float              num_f;
		int	           num_i;

	} data;
	

};

#define TYPE_VECTOR	0x01
#define TYPE_FLOAT	0x02
#define TYPE_INTEGER	0x04

/*
 * An array of settings that the parser will know about. See seetings.c.
 */
extern struct myrt_setting settings[];

/*
 * Functions.
 */
void _myrt_parse_init();
void _myrt_parse_cleanup();
int   myrt_parse(char *file, struct scene_graph *graph);
int   myrt_add_object(struct object *obj);
int  _myrt_parse_file(FILE *filp, struct scene_graph *graph);
int   myrt_next_token(char **token_ptr);

/*
 * Settings functions.
 */
struct myrt_setting *lookup_setting(char *setting);
void                 display_settings();

/*
 * Macro for the shapes to use if they detect a parsing error. This will take
 * care of returning the right stuff to the parser proper and displaying a msg
 * thats relevent to the user.
 */
#define PARSE_ERROR(msg, ...)						\
	do {								\
		myrt_printf(ERROR, "Parsing error (line %d):\n",	\
			    __line_no);					\
		myrt_printf(ERROR, msg, ##__VA_ARGS__);			\
		return -1; /* Yep, thats all thats required. */		\
	} while (0)

#define TOKEN_ACCEPT(token, types) (token & (types))

#endif
