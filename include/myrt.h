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
 * Defines for the vector algebra.
 */

#include <myrt_vec.h>
#include <myrt_color.h>

#ifndef _MYRT_H_
#define _MYRT_H_

/*
 * This struct defines the details of a shape. This is the generic struct
 * used to out line a shape or objects required functionality.
 */
struct object {

	char   *name;

	/*
	 * Initialization/de-initialization call backs.
	 */
	int   (*init)(struct object *this);
	void  (*free)(struct object *this);

	/*
	 * Parsing function callback. 'this' points to the specific object
	 * that the call back function is being applied to.
	 */
	int   (*parse)(struct object *this);

	/*
	 * Math functions that need to be implemented.
	 */
	int   (*intersection)(struct object *this, struct myrt_line *ray,
			      struct myrt_vector *point);
	int   (*color)(struct object *this, struct myrt_color *color);

	/*
	 * Shape specific data structure.
	 */
	void *priv;

};

/*
 * Scene graph. Describes all of the objects to be rendered.
 */
struct scene_graph {



};

/*
 * Make an myrt_msg() macro for formating messages to the user.
 */
#define __myrt_msg(LEVEL, FMT, ...)		\
	do {					\
		printf("# " LEVEL);		\
		printf(FMT, ##__VA_ARGS__);	\
	} while (0)	

#define myrt_msg(FMT, ...)			\
	__myrt_msg(DEFAULT, FMT, ##__VA_ARGS__)
#define myrt_printf(LEVEL, FMT, ...)		\
	__myrt_msg(LEVEL, FMT, ##__VA_ARGS__)

#define ERROR	"[error] " /* Error, execution must stop. */
#define CRIT	"[crit] "  /* Critical problem but execution can continue. */
#define WARN	"[warn] "  /* Warning but execution can continue. */
#define DEFAULT	""         /* General message; default level. */
#define DBG	"[dbg] "   /* Debug messages. */

/*
 * Debugging macro. Piggy back of the __myrt_msg() macro a little bit.
 */
#ifdef _DEBUG
# define myrt_dbg(FMT, ...)					\
	do {							\
		__myrt_msg(DBG, "%s:%d %s()  ",			\
			   __FILE__, __LINE__, __func__);	\
		printf(FMT, ##__VA_ARGS__);			\
	} while (0)
#else
# define myrt_dbg(FMT, ...)
#endif

/*
 * Macros to terminate myrt if some terminating condition is met.
 * die():  This will kill myrt with an error message.
 * stop(): This will stop myrt with a general message.
 */
#define __myrt_term(STATUS, LEVEL, FMT, ...)		\
	do {						\
		__myrt_msg(LEVEL, FMT, ##__VA_ARGS__);	\
		__myrt_msg(LEVEL, "Terminate.\n");	\
		exit(STATUS);				\
	} while (0)
#define myrt_die(STATUS, FMT, ...)			\
	__myrt_term(STATUS, ERROR, FMT, ##__VA_ARGS__)
#define myrt_stop(FMT, ...)				\
	__myrt_term(0, DEFAULT, FMT, ##__VA_ARGS__)


#endif
