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
 * Holds array of settings.
 */

#include <parser.h>

/*
 * NULL terminated list of settings.
 */
struct myrt_setting settings[] = {

	/*
	 * Location of the camera.
	 */
	{"view",	TYPE_VECTOR,	.data.vec = {10, 10, 10, 0} },

	/*
	 * Feild of view. In degrees.
	 */
	{"fov",		TYPE_FLOAT,	.data.num_f = 45},

	/*
	 * Width/height of the rendered image in pixels.
	 */
	{"width",	TYPE_INTEGER,	.data.num_i = 400},
	{"height",	TYPE_INTEGER,	.data.num_i = 200},

	/*
	 * Ambient diffuse lighting constant.
	 */
	{"ambience",	TYPE_FLOAT,	.data.num_f = .4},

	/*
	 * Density of rays per pixel.
	 */
	{"density",	TYPE_INTEGER,	.data.num_i = 200},

	/*
	 * Maximum depth of recursion
	 */
	{"depth",	TYPE_INTEGER,	.data.num_i = 4},

	/*
	 * Default reflectance.
	 */
	{"reflectance",	TYPE_FLOAT,	.data.num_f = 0.1},

	/*
	 * Default specular component.
	 */
	{"aaliasing",	TYPE_INTEGER,	.data.num_i = 1},

	/*
	 * Threads. 0 implies dont use threading.
	 */
	{"threads",	TYPE_INTEGER,	.data.num_i = 0},

	/* NULL terminator. */
	{NULL,		0,		.data.num_i = 0}

};
