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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct scene_graph scene;

int main(int argc, char *argv[]){

	int x = 0, y = 0, ax, ay;
	struct myrt_line ray;

	if ( argc != 2 )
		myrt_die(1, "Usage %s <scene_graph>\n", argv[0]);

	myrt_parse(argv[1], &scene);

	for ( ax = 0; ax < scene.aaliasing_sqrt; ax++ ){
		for ( ay = 0; ay < scene.aaliasing_sqrt; ay++ ){
			_myrt_generate_ray(&scene, &ray, x, y, ax, ay);
			display(&ray.orig);
			printf(" -> ");
			displayln(&ray.traj_n);
		}
	}

	return 0;

}
