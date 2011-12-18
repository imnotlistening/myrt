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
 * Keep track of the list of objects that the scene graph is aware of.
 */

#include <myrt.h>
#include <light.h>

#include <math.h>
#include <stdlib.h>

#define MAXFLOAT	3.40282347e+38F

#define _INCREMENT_SIZE	(2)

void myrt_objlist_init(struct myrt_objlist *list){

	list->next = 0;
	list->max = 0;
	list->objlist = NULL;

}

int myrt_objlist_add(struct myrt_objlist *list, struct object *obj){

	struct object **tmp;

	/*
	 * Check to see if we need more space.
	 */
	if ( list->next >= list->max ){

		tmp = (struct object **)
			realloc(list->objlist,
				sizeof(struct object *) * 
				(list->max + _INCREMENT_SIZE));

		if ( ! tmp ){
			myrt_printf(ERROR, "Unable to allocate more object "
				    "space; this is bad.\n");
			return -1;
		}

		memset(&tmp[list->next], 0,
		       sizeof(struct object *) * _INCREMENT_SIZE);
		list->objlist = tmp;
		list->max += _INCREMENT_SIZE;

	}

	list->objlist[list->next] = obj;
	list->next++;

	return 0;

}

void _myrt_objlist_print(struct myrt_objlist *list){

	int i;

	myrt_msg("Object list:\n");
	for ( i = 0; i < list->next; i++)
		myrt_msg("  Object: %s\n", list->objlist[i]->name);

}

/*
 * If light is non-zero then use the glow intersection comutation for a light
 * and the regular intersection for a non-light object.
 */
struct object *_myrt_do_find_intersection(struct myrt_objlist *list,
					  struct myrt_line *line,
					  struct myrt_vector *p, int light){

	int i;
	int ret;
	float t, min = MAXFLOAT;
	struct light *glow;
	struct object *obj, *closest = NULL;
	struct myrt_vector tmp;

	for ( i = 0; i < list->next; i++ ){

		obj = list->objlist[i];
		if ( light && obj->light ){
			glow = obj->priv;
			ret = glow->glow_intersect(obj, line, &tmp, &t);
		} else {
			ret = obj->intersection(obj, line, &tmp, &t);
		}
		if ( ret < 0 )
			continue; /* No intersection. */

		/*
		 * If this object's intersection is farther than the current
		 * closest, just skip it.
		 */
		if ( t > min || t <= 0 )
			continue;

		min = t;
		closest = obj;
		copy(p, &tmp);
	
	}

	return closest;

}

/*
 * Compute the closest intersection of a line and the given list of objects.
 */
struct object *_myrt_find_intersection(struct myrt_objlist *list,
				       struct myrt_line *line,
				       struct myrt_vector *p){

	return _myrt_do_find_intersection(list, line, p, 0);

}

/*
 * Find intersections only use the glow size of lights instead.
 */
struct object *_myrt_find_glowsection(struct myrt_objlist *list,
				      struct myrt_line *line,
				      struct myrt_vector *p){

	return _myrt_do_find_intersection(list, line, p, 1);

}

/*
 * See if a point, q, is visable from a specified light.
 */
int _myrt_occlusion(struct scene_graph *graph, struct myrt_vector *q,
		    struct light *light){

	struct myrt_line d;
	struct myrt_vector p;
	struct object *nearest;

	/* Make a line pointing at the light source from the passed point q. */
	copy(&d.traj_n , &light->visual.orig);
	sub(&d.traj_n, q);
	normalize(&d.traj_n);
	copy(&d.orig, q);
	
	/* See what object intersects it first. */
	nearest = _myrt_find_intersection(&graph->objs, &d, &p);
	if ( nearest == NULL )
		return -1; /* This is only gonna be from a bug. */

	if ( light->owner != nearest )
		return -1;

	return 0;

}

/*
 * See if the first thing a ray intersects with is the glow radius of a
 * given light. Other lights are treated normally.
 */
int _myrt_first_glowsection(struct myrt_objlist *list, struct myrt_line *line,
			    struct light *light){

	int i, ret;
	float t, min = MAXFLOAT;
	struct object *obj, *closest = NULL;
	struct myrt_vector tmp;

	for ( i = 0; i < list->next; i++ ){

		obj = list->objlist[i];
		if ( obj == light->owner ){
			ret = light->glow_intersect(obj, line, &tmp, &t);
		} else {
			ret = obj->intersection(obj, line, &tmp, &t);
		}
		if ( ret < 0 )
			continue; /* No intersection. */

		/*
		 * If this object's intersection is farther than the current
		 * closest, just skip it.
		 */
		if ( t > min || t <= 0 )
			continue;

		min = t;
		closest = obj;
	
	}

	return closest == light->owner;

}
