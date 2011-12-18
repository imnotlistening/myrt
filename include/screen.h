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
 * Defines for manipulating the screen object.
 */

#include <png.h>
#include <color.h>

#ifndef _SCREEN_H_
#define _SCREEN_H_

/*
 * A screen. Holds screen related data.
 */
struct screen {

	unsigned int   width;
	unsigned int   height;

	unsigned char *data;

	/*
	 * PNG structures for writing a PNG file.
	 */
	png_structp    png_ptr;
	png_infop      info_ptr;

};

/*
 * Some functions.
 */
int  screen_init(struct screen *screne, int width, int height);
int  screen_write(struct screen *screen, char *file);
inline void screen_write_chan(struct screen *screen, int x, int y, 
			      int channel, char data);
inline void screen_write_pixel(struct screen *screen, int x, int y, 
			 struct myrt_color *color);
void screen_add_channel(struct screen *screen, int x, int y,
			int channel, unsigned char data);
void screen_add_pixel(struct screen *screen, int x, int y,
		      struct myrt_color *color);

#define COLOR_RED	0
#define COLOR_GREEN	1
#define COLOR_BLUE	2
#define COLOR_ALPHA	3

#endif
