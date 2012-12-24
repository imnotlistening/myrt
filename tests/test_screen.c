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
 * Test the screen PNG writing code.
 */

#include <myrt.h>
#include <screen.h>

#include <stdio.h>
#include <stdlib.h>

struct screen scr;

#define ROWS	256
#define COLS	256

int main(int argc, char **argv){
	
	int ret;
	int x, y;
	struct myrt_color color;

	if ( argc < 2 )
		myrt_die(1, "Usage: test_screen <file>\n");

	ret = screen_init(&scr, COLS, ROWS);
	if ( ret < 0 )
		myrt_die(1, "PNG write failed.\n");
	
	for ( y = 0; y < ROWS; y++ ){
		for ( x = 0; x < COLS; x++ ){
			COLOR_SET(color, x, 0, y, (x + y) / 2);
			screen_write_pixel(&scr, x, y, &color);
		}
	}

	screen_write(&scr, argv[1]);

	return 0;

}

