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
 * Built in shapes that can be used.
 */

#include <myrt.h>
#include <color.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Convert a vector string into a color.
 */
int myrt_strtocol(char *str, struct myrt_color *color){

	int convs;
	float x, y, z;

	convs = sscanf(str, "[ %f %f %f ]", &x, &y, &z);
	if ( convs < 3 )
		return -1;

	COLOR_SET_PTR(color, x, y, z, 0);
	return 0;

}

/*
 * Utility function: print a color out.
 */
void myrt_color_print(struct myrt_color *color){

	printf("[ 0x%02x 0x%02x 0x%02x 0x%02x ]",
	       (unsigned char)color->red, (unsigned char)color->green,
	       (unsigned char)color->blue, (unsigned char)color->scale);

}

inline void myrt_color_copy(struct myrt_color *dest,
			    struct myrt_color *source){

	memcpy(dest, source, sizeof(struct myrt_color));

}
