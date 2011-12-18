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
#include <screen.h>

#include <png.h>

#include <stdio.h>
#include <stdlib.h>

int screen_init(struct screen *screen, int width, int height){

	screen->width = width;
	screen->height = height;

	screen->data = (unsigned char *)malloc(sizeof(unsigned char) * 
					       4 * width * height);
	if ( ! screen->data )
		return -1;
	return 0;

}

int screen_write(struct screen *screen, char *file){

	int y;
	png_bytep row;
	png_color_16 color;

	memset(&color, 0, sizeof(color));

	/* Create PNG file. */
        FILE *fp = fopen(file, "wb");
        if ( ! fp ){
		myrt_printf(ERROR, "Could not open file: %s\n", file);
		return -1;
	}

        /* Initialize stuff. */
        screen->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
						  NULL, NULL, NULL);

        if ( ! screen->png_ptr ){
		myrt_printf(ERROR, "Could not make PNG header.\n");
		return -1;
	}

        screen->info_ptr = png_create_info_struct(screen->png_ptr);
        if ( ! screen->info_ptr ){
		myrt_printf(ERROR, "Could not make PNG info struct.\n");
		return -1;
	}

        if ( setjmp(png_jmpbuf(screen->png_ptr)) ){
                myrt_printf(ERROR, "Failed to init png I/O.");
		return -1;
	}
        png_init_io(screen->png_ptr, fp);


        /* Write the header. */
        if ( setjmp(png_jmpbuf(screen->png_ptr)) ){
		myrt_printf(ERROR, "Failed to write PNG header.\n");
		return -1;
	}
        png_set_IHDR(screen->png_ptr, screen->info_ptr, screen->width,
		     screen->height, 8, PNG_COLOR_TYPE_RGB_ALPHA,
		     PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
		     PNG_FILTER_TYPE_BASE);
	png_set_background(screen->png_ptr, &color,
			   PNG_BACKGROUND_GAMMA_SCREEN, 0, 1.0);
        png_write_info(screen->png_ptr, screen->info_ptr);

        /* Write some bytes. */
        if ( setjmp(png_jmpbuf(screen->png_ptr)) ){
		myrt_printf(ERROR, "Unable to write png data.\n");
		return -1;
	}

	/* Write the PNG data. */
	row = (png_bytep) screen->data;
	for ( y = 0; y < screen->height; y++ ){
		png_write_row(screen->png_ptr, row);
		row += (screen->width * 4);
	}

        /* End write */
        if ( setjmp(png_jmpbuf(screen->png_ptr)) ){
		myrt_printf(ERROR, "Failed to finalize PNG.\n");
		return -1;
	}
        png_write_end(screen->png_ptr, NULL);

        fclose(fp);

	return 0;

}

inline void screen_write_channel(struct screen *screen, int x, int y,
				 int channel, char data){

	/*
	 * Screen space is upside down apparently. So invert the Y coord.
	 */
	y = (screen->height - 1) - y;

	screen->data[4 * (screen->width*y + x) + channel] = data;	

}

inline void screen_write_pixel(struct screen *screen, int x, int y,
			       struct myrt_color *color){

	screen_write_channel(screen, x, y, COLOR_RED,
			     (unsigned char)color->red);
	screen_write_channel(screen, x, y, COLOR_GREEN,
			     (unsigned char)color->green);
	screen_write_channel(screen, x, y, COLOR_BLUE,
			     (unsigned char)color->blue);
	screen_write_channel(screen, x, y, COLOR_ALPHA,
			     (unsigned char)color->scale);

}

void screen_add_channel(struct screen *screen, int x, int y,
			int channel, unsigned char data){

	unsigned int sum;

	y = (screen->height - 1) - y;
	sum = screen->data[4 * (screen->width*y + x) + channel] + 
		(unsigned int)data;
	if ( sum > 255 )
		screen->data[4 * (screen->width*y + x) + channel] = 255;
	else
		screen->data[4 * (screen->width*y + x) + channel] = 
			(unsigned char)sum;

}

void screen_add_pixel(struct screen *screen, int x, int y,
		      struct myrt_color *color){

	screen_add_channel(screen, x, y, COLOR_RED,
			   (unsigned char)color->red);
	screen_add_channel(screen, x, y, COLOR_GREEN,
			   (unsigned char)color->green);
	screen_add_channel(screen, x, y, COLOR_BLUE,
			   (unsigned char)color->blue);
	screen_add_channel(screen, x, y, COLOR_ALPHA,
			   (unsigned char)color->scale);

}
