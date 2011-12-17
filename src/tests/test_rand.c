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
 * Test the distribution of random vectors created by _myrt_rand_vector().
 */

#include <myrt.h>

int main(){

	int i = 0;
	float theta;
	unsigned short rseed1[] = {1, 2, 3};
	unsigned short rseed2[] = {7, -9, 4};
	struct myrt_vector dest;
	struct myrt_vector norm = VEC_INIT(0, 1, 0);

	while ( i++ < 10000 ){

		_myrt_rand_vector(rseed1, rseed2, &norm, &dest);
		displayln(&dest);

		/*
		theta = _myrt_normal_sample(rseed);
		printf("%f\n", theta);
		*/
	}

	return 0;

}
