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

#include <vec.h>
#include <color.h>
#include <screen.h>

#ifndef _MYRT_H_
#define _MYRT_H_

struct light;

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
			      struct myrt_vector *point, float *t);
	int   (*color)(struct object *this, struct myrt_color *color);
	int   (*normal)(struct object *this, struct myrt_vector *q,
			struct myrt_vector *n);

	/*
	 * Object specific reflectance and diffusion. These should sum to 1.
	 */
	float reflectance;
	float diffusion;

	/*
	 * Set if the object is a light source.
	 */
	int   light;

	/*
	 * Shape specific data structure.
	 */
	void *priv;

} __attribute__ ((aligned (16)));

/*
 * List of objects in the scene.
 */
struct myrt_objlist {

	struct object **objlist;
	int             next;
	int             max;

} __attribute__((aligned (16)));

struct scene_graph;

/*
 * A model for rendering the scene. The parser keeps track of which model is
 * specified by the user and tells the renderer which one to use.
 */
struct myrt_model {

	/*
	 * Name of the model for the parser to match against.
	 */
	char	*name;

	/*
	 * The function to do the rendering.
	 */
	int	(*trace)(struct scene_graph *graph,
			 int row_lo, int row_hi, int tid);

	/*
	 * Model specific data.
	 */
	void	*priv;

};

extern struct myrt_model models[];

struct thread_seed {

	unsigned short int	rseed1[3];
	unsigned short int	rseed2[3];
	unsigned short int	rseed3[3];

	unsigned char		padding[46];

} __attribute__ ((aligned (16)));

/*
 * Scene graph. Describes all of the objects to be rendered.
 */
struct scene_graph {

	/*
	 * Useful data describing the scene.
	 */
	struct myrt_vector 	camera;
	float              	fov;
	float	           	vert_fov;
	float              	aratio;
	int                	width;
	int                	height;

	/*
	 * The two basis vectors required for generating all the required
	 * rays for tracing.
	 */
	struct myrt_vector 	h;
	struct myrt_vector 	v;

	/*
	 * Screen data; can be used to make a PNG.
	 */
	struct screen      	screen;

	/*
	 * Float pre computed data for making the rays.
	 */
	float              	delta_h; /* In degrees per pixel. */
	float              	delta_v;
	float              	x_min; /* -width/2 */
	float              	y_min; /* -height/2 */
	float              	cam_mag;
	struct myrt_vector 	cam_neg;

	/*
	 * Objects picked up by the parser.
	 */
	struct myrt_objlist	objs;
	struct myrt_model      *model;

	/*
	 * Global algorithm constraints.
	 */
	int			density;
	int			depth;
	int			aaliasing;
	int			aaliasing_sqrt;
	struct myrt_color	ambient_color;
	float			ambience;
	float			diffusion;

	/*
	 * Thread related stuff.
	 */
	int			threads;
	struct thread_seed     *rseeds;

};

struct thread_arg {

	int 			tid;
	struct scene_graph     *graph;

};

/*
 * Some functions.
 */
int  _myrt_scene_init(struct scene_graph *graph);
void _myrt_generate_ray(struct scene_graph *graph, struct myrt_line *vec,
			int x, int y, int ax, int ay);
void _myrt_rand_uvect(unsigned short int *rseed1, unsigned short int *rseed2,
		      struct myrt_vector *dest);
int   myrt_trace(struct scene_graph *graph);
int  _myrt_trace(struct scene_graph *graph, int row_lo, int row_hi);
void _myrt_rand_vector(unsigned short int *rseed1, unsigned short int *rseed2,
		       struct myrt_vector *norm, struct myrt_vector *dest);
int   myrt_write(struct scene_graph *graph, char *file_path);
void  myrt_objlist_init(struct myrt_objlist *list);
int   myrt_objlist_add(struct myrt_objlist *list, struct object *obj);
void _myrt_objlist_print(struct myrt_objlist *list);
struct object *_myrt_find_intersection(struct myrt_objlist *list,
				       struct myrt_line *line,
				       struct myrt_vector *p);
int  _myrt_first_glowsection(struct myrt_objlist *list, struct myrt_line *line,
			     struct light *light);
int  _myrt_occlusion(struct scene_graph *graph, struct myrt_vector *q,
		     struct light *light);

/* Path tracing functions. */
void _myrt_trace_path(struct scene_graph *graph, struct myrt_line *line,
		      struct myrt_color *color, int tid);
void _myrt_trace_point(struct scene_graph *graph, int x, int y, int tid);
int  _myrt_model_path_trace(struct scene_graph *graph,
			    int row_lo, int row_hi, int tid);

/* Ray tracing functions. */
int  _myrt_model_ray_trace(struct scene_graph *graph,
			   int row_lo, int row_hi, int tid);

/*
 * Shader.
 */
void _shade_intersection(struct scene_graph *graph, struct myrt_vector *inter,
			 struct myrt_vector *norm, struct myrt_line *incident,
			 struct myrt_color *color, int tid);

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
