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
 * Color related stuff.
 */

#ifndef _MYRT_COLOR_H_
#define _MYRT_COLOR_H_

struct myrt_color {

	float red;
	float green;
	float blue;
	float scale;

} __attribute__ ((aligned (16)));

/*
 * Functions.
 */
int  myrt_strtocol(char *str, struct myrt_color *color);
void myrt_color_print(struct myrt_color *color);
inline void myrt_color_copy(struct myrt_color *dest,
			    struct myrt_color *source);

/*
 * Macros for dealing with colors.
 */
#define COLOR_INIT(red, green, blue, scale) { red, green, blue, scale }

#define COLOR_SET(color, a, b, c, d)		\
	do {					\
		color.red = a;			\
		color.green = b;		\
		color.blue = c;			\
		color.scale = d;		\
	} while (0) 

#define COLOR_SET_PTR(color, a, b, c, d)	\
	do {					\
		color->red = a;			\
		color->green = b;		\
		color->blue = c;		\
		color->scale = d;		\
	} while (0) 

#endif
