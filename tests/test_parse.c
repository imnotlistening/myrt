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
 * Tests the parsing functionality.
 */

#include <myrt.h>
#include <parser.h>

#include <stdio.h>
#include <stdlib.h>

struct scene_graph scene;

int main(int argc, char *argv[]){

	if ( argc != 2 )
		myrt_die(1, "Usage %s <scene_graph>\n", argv[0]);

	myrt_parse(argv[1], &scene);

	myrt_msg("Camera:       "); displayln(&scene.camera);
	myrt_msg("FoV:          %.2fx%.2f\n", scene.fov, scene.vert_fov);
	myrt_msg("Aspect ratio: %.2f:1\n", scene.aratio);
	myrt_msg("Dimensions:   %dx%d\n", scene.width, scene.height);
	myrt_msg("FoV basis vectors:\n");
	myrt_msg("  "); displayln(&scene.h);
	myrt_msg("  "); displayln(&scene.v);
	myrt_msg("RPP (horizontal): %f\n", scene.delta_h);
	myrt_msg("RPP (vertical):   %f\n", scene.delta_v);

	_myrt_objlist_print(&scene.objs);

	return 0;

}
