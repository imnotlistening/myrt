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
 * Post processing defines and set up.
 */

#include <myrt.h>

#ifndef _POST_PROCESS_H_
#define _POST_PROCESS_H_

/*
 * A post processing filter.
 */
struct post_process {

	/* The process name. */
	char	       *name;

	/* Set to non-zero if the process is enabled. */
	int		enable;

	/* And the function to call to do the processing. */
	void	      (*process)(struct scene_graph *graph);

};

/*
 * List of known processes.
 */
extern struct post_process processes[];

/*
 * Function definitions.
 */
void  myrt_post_process(struct scene_graph *graph);
struct post_process *myrt_lookup_process(char *name);
void  myrt_pp_glow(struct scene_graph *graph);

#endif
