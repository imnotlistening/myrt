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
 * Here lies the code to do a ray trace.
 */

#include <myrt.h>
#include <parser.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct scene_graph graph;

/*
 * For now, lets keep it simple. Two args nothing more.
 * 
 *   Usage: ./myrt <scene_file> <output_file>
 * 
 */
int main(int argc, char *argv[]){

	if ( argc < 3 )
		myrt_die(1, "Usage: ./myrt <scene_file> <output_file>\n");

	/* Load the scene graph. */
	if ( myrt_parse(argv[1], &graph) < 0 )
		myrt_die(1, "Failed to parse scene: %s\n", argv[1]);

	/* Print some info about the scene graph. */
	myrt_msg("Camera location: "); displayln(&graph.camera);
	myrt_msg("Horizontal FoV: %.02f degrees\n", graph.fov);
	myrt_msg("Vertical FoV:   %.02f degrees\n", graph.vert_fov);
	myrt_msg("Ambient light: "); myrt_color_println(&graph.ambient_color);
	myrt_msg("Depth = %d, Density = %d\n", graph.depth, graph.density);

	/* Render. */
	if ( myrt_trace(&graph) < 0 )
		myrt_die(1, "Failed to trace scene.\n");

	/* Write it out. */
	if ( myrt_write(&graph, argv[2]) < 0 )
		myrt_die(1, "Failed to write scene to file: %s\n", argv[2]);

	return 0;

}
