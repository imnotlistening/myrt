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

	struct myrt_line blc, brc, tlc, trc, naught;

	if ( argc != 2 )
		myrt_die(1, "Usage %s <scene_graph>\n", argv[0]);

	myrt_parse(argv[1], &scene);

	_myrt_generate_ray(&scene, &blc, 0, 0);
	printf("[ %4d %4d ] traj_n: ", 0, 0);
	displayln(&blc.traj_n);
	
	_myrt_generate_ray(&scene, &brc, scene.width, 0);
	printf("[ %4d %4d ] traj_n: ", scene.width, 0);
	displayln(&brc.traj_n);
	
	_myrt_generate_ray(&scene, &tlc, 0, scene.height);
	printf("[ %4d %4d ] traj_n: ", 0, scene.height);
	displayln(&tlc.traj_n);

	_myrt_generate_ray(&scene, &trc, scene.width, scene.height);
	printf("[ %4d %4d ] traj_n: ", scene.width, scene.height);
	displayln(&trc.traj_n);

	_myrt_generate_ray(&scene, &naught, scene.width/2, scene.height/2);
	printf("[ %4d %4d ] traj_n: ", scene.width/2, scene.height/2);
	displayln(&naught.traj_n);

	myrt_msg("Angles:\n");
	myrt_msg("  blc <> brc: %.2f\n",
		 angle(&blc.traj_n, &brc.traj_n) * 180 / M_PI);

	return 0;

}
