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
 * Parse a file that defines a scene graph.
 */

#include <myrt.h>
#include <parser.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * For communication with the parser.
 */
char *__parsed_text;
int   __line_no;
extern FILE *yyin;
extern int   yylex();

/*
 * List of known objects. This is initialized on library load. It can be added
 * to dynamically later on if necessary.
 */
struct object  *known_objects;
int             length;
int             next_offset;
#define        _INC_SIZE 2

/*
 * List of models known to the parser.
 */
struct myrt_model models[] = {

	{ "path-trace",	_myrt_model_path_trace,	NULL },
	{ "ray-trace",	_myrt_model_ray_trace,	NULL },
	{ NULL,		NULL,			NULL }

};
struct myrt_model *default_model = &models[0];

/*
 * Initialize the parser's internal data. This should be called before any other
 * parsing routines are called.
 */
void _myrt_parse_init(){

	known_objects = NULL;
	length = 0;
	next_offset = 0;

}

void _myrt_parse_cleanup(){

	free(known_objects);

}

int myrt_add_object(struct object *obj){

	struct object *new_list;

	/* Some preamble. */
	if ( ! obj )
		return -1;
	obj->priv = NULL;

	/* Make sure there is enough room. */
	if ( next_offset >= length ){
		new_list = (struct object *)
			realloc(known_objects, sizeof(struct object) * 
				(length + _INC_SIZE));
		if ( ! new_list )
			return -1;
		
		known_objects = new_list;
		memset(known_objects + length, 0, 
		       sizeof(struct object) * _INC_SIZE);
		length += _INC_SIZE;
	}

	/* Add the passed object. */
	memcpy(known_objects + next_offset, obj, sizeof(struct object));
	myrt_dbg("Added object: %s\n", 
		 known_objects[next_offset].name);
	next_offset++;

	return 0;

}

int myrt_parse(char *file, struct scene_graph *graph){

	FILE *filp;

	myrt_msg("Loading scene file: %s\n", file);

	/* Open the file. */
	filp = fopen(file, "r");
	if ( ! filp ){
		myrt_printf(ERROR, "Could not open '%s'\n", file);
		return -1;
	}

	myrt_objlist_init(&graph->objs);
	graph->model = default_model;

	/*
	 * Now parse through the passed file pulling out shapes, etc.
	 */
	if ( _myrt_parse_file(filp, graph) )
		return -1;

	/*
	 * Pull useful info from the variables.
	 */
	if ( _myrt_scene_init(graph) )
		return -1;

	/*
	 * Init the screen.
	 */
	screen_init(&graph->screen, graph->width, graph->height);

	return 0;

}

int _lookup_object(char *obj){

	int i = 0;

	for ( ; i < next_offset; i++){
		if ( strcmp(known_objects[i].name, obj) == 0 )
			return i;
	}

	return -1;

}

/*
 * Parse a shape directive. Use the callback functions!!!
 */
int _handle_shape(struct scene_graph *graph, char *shape){

	int ret;
	int offset;
	struct object *obj;

	/* First, is it a legit shape? */
	offset = _lookup_object(shape);
	if ( offset < 0 ){
		myrt_printf(ERROR, "(%d) Unknown object definition: %s\n",
			    __line_no, shape);
		return -1;
	}

	/* Assuming a legit shape, we can access the object array. */
	obj = (struct object *)malloc(sizeof(struct object));
	if ( ! obj ){
		myrt_printf(ERROR, "Internal: out of memory.\n");
		return -1;
	}

	/* And init the shape, etc, etc. */
	memcpy(obj, &known_objects[offset], sizeof(struct object));
	obj->reflectance = lookup_setting("reflectance")->data.num_f;
	obj->emittance = 1 - obj->reflectance;
	obj->light = 0;
	ret = obj->init(obj);
	if ( ret < 0 )
		return ret;

	/* Shape is inited; now allow the shape's parser to parse the fields. */
	ret = obj->parse(obj);
	if ( ! ret )
		myrt_objlist_add(&graph->objs, obj);

	return ret;

}

int _handle_setting(char *text){

	int token;
	struct myrt_setting *s = lookup_setting(text);

	if ( ! s )
		return -1;
	
	/* See if the next token matches the type on the setting. */
	token = yylex();
	switch ( s->type ){

	case TYPE_VECTOR:
		if ( token != TOKEN_VECTOR ){
			myrt_printf(ERROR, "(%d) Token misamtch: %s\n",
				    __line_no, __parsed_text);
			myrt_printf(ERROR, "  Expected vector.\n");
			return -1;
		}
		myrt_strtovec(__parsed_text, &s->data.vec);
		break;

	case TYPE_INTEGER:
		if ( token != TOKEN_INTEGER ){
			myrt_printf(ERROR, "(%d) Token misamtch: %s\n",
				    __line_no, __parsed_text);
			myrt_printf(ERROR, "  Expected integer.\n");
			return -1;
		}
		s->data.num_i = atoi(__parsed_text);
		break;

	case TYPE_FLOAT:
		if ( token != TOKEN_FLOAT && token != TOKEN_INTEGER ){
			myrt_printf(ERROR, "(%d) Token misamtch: %s\n",
				    __line_no, __parsed_text);
			myrt_printf(ERROR, "  Expected float.\n");
			return -1;
		}
		s->data.num_f = atof(__parsed_text);
		break;
	}

	return 0;

}

/*
 * This function returns < -1 for total failure (i.e stop parsing), -1 for a
 * command that might be a shape or setting, and 0 for a command that was
 * successfully executed.
 */
int _handle_command(struct scene_graph *graph, char *text){

	int ret;
	struct myrt_command *comm;

	if ( (comm = myrt_command_lookup(text)) == NULL ) 
		return -1;

	ret = comm->command_func(graph);
	if ( ret < 0 )
		return -2;
	return 0;

}


int _myrt_parse_file(FILE *filp, struct scene_graph *graph){

	int token, ret;

	yyin = filp;
	__line_no = 1;

	while ( (token = yylex()) != TOKEN_EOF ){

		switch (token){
			
		case TOKEN_NULL:
		case TOKEN_COMMENT:
		case TOKEN_NEWLINE:
			break;

		case TOKEN_COMMAND:
			ret = _handle_command(graph, __parsed_text);
			if ( ret < -1 )
				return ret;
			else if ( ret == 0 )
				break;
			ret = _handle_setting(__parsed_text);
			if ( ret == 0 )
				break;
			ret = _handle_shape(graph, __parsed_text);
			if ( ret < 0 )
				return ret;
			break;

		case TOKEN_VECTOR:
		case TOKEN_INTEGER:
		case TOKEN_FLOAT:
			myrt_printf(WARN, "(%d) Ignoring token: %s\n",
				    __line_no, __parsed_text);
			break;

		default:
			myrt_printf(ERROR, "Unknown token (%d): %s\n",
				    token, __parsed_text);
			return -1;
			
		}

	}

	return 0;

}

/*
 * Exported for the use of the shapes; hides the lexxer from them. They need
 * only call this to get the next token and the string.
 */
int myrt_next_token(char **token_ptr){

	int token;

	token = yylex();
	if ( token == TOKEN_FLOAT || token == TOKEN_VECTOR ||
	     token == TOKEN_INTEGER || token == TOKEN_ARG ){
		*token_ptr = __parsed_text;
		return token;
	}

	return TOKEN_NULL;

}


