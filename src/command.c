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
 * Commands the parser knows about. For now there isn't much.
 */

#include <myrt.h>
#include <parser.h>

struct myrt_command commands[] = {

	{ "model",	myrt_command_model },
	{ NULL, 	NULL }

};

struct myrt_command *myrt_command_lookup(char *text){

	int i;

	for ( i = 0; commands[i].command_func != NULL; i++ ){
		if ( strcmp(commands[i].name, text) == 0 )
			return &commands[i];
	}

	return NULL;

}

int myrt_command_model(struct scene_graph *graph){

	int i;
	int token;
	char *text;

	token = myrt_next_token(&text);
	if ( token == TOKEN_NULL )
		PARSE_ERROR("model: missing argument.\n");

	for ( i = 0; models[i].name != NULL; i++ ){
		if ( strcmp(models[i].name, text) == 0 ){
			myrt_msg("Setting model type: %s\n", text);
			graph->model = &models[i];
			return 0;
		}
	}

	PARSE_ERROR("model: unknown model type: %s\n", text);

}
