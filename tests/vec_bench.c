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
 * Test the vector algebra routines. Nothing too crazy.
 */

#include <vec.h>
#include <myrt.h>

#include <stdio.h>

#define BENCH_LOOP_COUNT	10000000

int main(int argc, char **argv){

	int i;

	vec a = VEC_INIT(1, 2, 3);
	vec b = VEC_INIT(-2, -3, -4);

	/* Compute some dot products since they are used a lot. */
	for ( i = 0; i < BENCH_LOOP_COUNT; i++){

		dot(&a, &b);
		angle(&a, &b);
		cross(&a, &b);
		normalize(&a);
		normalize(&b);
		refl(&a, &b);

	}

	return 0;

}
