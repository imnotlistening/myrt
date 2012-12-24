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

int main(int argc, char **argv){

	vec a = VEC_INIT(4, 6, -5);
	vec b = VEC_INIT4(-.5, .4, -7.1, -1);
	vec c = VEC_INIT(.001, .002, .003);

	vec norm_a = a;
	vec norm_b = b;
	vec norm_c = c;

	myrt_msg("Test vectors:\n");
	display_msg(&a, "a: ");
	display_msg(&b, "b: ");
	display_msg(&c, "c: ");

	myrt_msg("Adding two vectors:\n");
	display_msg(add(&a, &b), "a + b = ");
	myrt_msg("And fixing them...\n");
	display_msg(sub(&a, &b), "a - b = ");

	myrt_msg("Some dot products:\n");
	myrt_msg("dot(a, b) = %f\n", dot(&a, &b));

	myrt_msg("Magnitudes:\n");
	myrt_msg("  |a| = %f\n", magnitude(&a));
	myrt_msg("  |b| = %f\n", magnitude(&b));
	myrt_msg("  |c| = %f\n", magnitude(&c));

	/* Scale a vector. */
	display_msg(scale(&a, 2), "2 * a = ");

	/* Compute the norms. */
	normalize(&norm_a);
	normalize(&norm_b);
	normalize(&norm_c);

	myrt_msg("Normalizations of a, b, c:\n");
	myrt_msg("  norm(a) = "); displayln(&norm_a);
	myrt_msg("  norm(b) = "); displayln(&norm_b);
	myrt_msg("  norm(c) = "); displayln(&norm_c);

	/* Now print the norm's magnitudes; should all equal 1. */
	myrt_msg("Magnitude of the normalizations of a, b, c:\n");
	myrt_msg("  |norm(a)| = %f\n", magnitude(&norm_a));
	myrt_msg("  |norm(b)| = %f\n", magnitude(&norm_b));
	myrt_msg("  |norm(c)| = %f\n", magnitude(&norm_c));

	/* Reflections. */
	VEC_SET(a, 2, 1, -6);
	VEC_SET(b, -1, 5, 1);
	VEC_SET(c, -1, -7, 4);

	normalize(&a);
	normalize(&b);
	normalize(&c);

	myrt_msg("Computing reflections about A: "); displayln(&a);
	myrt_msg("  B = "); display(&b);
	printf(" (theta = %f)\n", angle(&a, &b));
	myrt_msg("  C = "); display(&c);
	printf(" (theta = %f)\n", angle(&a, &c));
	myrt_msg("  B v A = "); display(refl(&b, &a));
	printf(" (theta = %f)\n", angle(&a, &b));
	myrt_msg("  C v A = "); display(refl(&c, &a));
	printf(" (theta = %f)\n", angle(&a, &c));

	/* Test some cross products. */
	VEC_SET(a, .45, -3, -1);
	VEC_SET(b, -.33, 11, -.1);
	VEC_SET(c, 0, 0, 1);

	display_msg(cross(&a, &b), "X x Y = ");
	display_msg(cross(&b, &c), "Y x Z = ");

	return 0;

}
