/*   FILE:

	 processor_lists.h

    DESCRIPTION:

	 List routines for real-time multi-processors programs

    Copyright (C) 2008

	 Arnoldo Diaz Ramirez, Pedro Mejia Alvarez

   This is free software;  you can  redistribute it  and/or modify it under
   terms of the  GNU General Public License as published  by the Free Soft-
   ware  Foundation;  either version 2,  or (at your option) any later ver-
   sion.  It is distributed in the hope that it will be useful, but WITH-
   OUT ANY WARRANTY;  without even the  implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
   for  more details.  You should have  received  a copy of the GNU General
   Public License;  see file COPYING.  If not, write to  the Free Software
   Foundation,  59 Temple Place - Suite 330,  Boston, MA 02111-1307, USA.

   LAST REVISION:    June 2009

 */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../include/task.h"
#include "../include/processor.h"
#include "../include/trace_event.h"

/*
    Add processor to list
 */

processor_t * add_processor_list(processor_t * list, processor_t ele)
{
	processor_t *item, * prev = list;

	if (!list) { /* empty list  */
		list = (processor_t *) malloc(sizeof(processor_t));
		item = list;
	} else {
		while (prev -> next) {
			prev = (processor_t *) prev -> next;
		}
		prev -> next = (struct processor_t *) malloc(sizeof(processor_t));
		item = (processor_t *) prev -> next;
	}

	item -> id = ele.id;
	item -> status = ele.status;
	item -> n = ele.n;
	item -> u = ele.u;
	item -> task = ele.task;
	item -> next = NULL;
	item-> tracer = NULL;

	return list;
}

/*
    Add processor to list, sorted by utilization
 */

processor_t * add_processor_list_u_sorted(processor_t * list, processor_t ele)
{

	processor_t *item, *next, * prev = list;

	if (!list) { /* empty list  */
		list = (processor_t *) malloc(sizeof(processor_t));
		item = list;
		item -> next = NULL;
	} else {
		next = prev;
		while ((next) && (next -> u <= ele.u)) {
			prev = (processor_t *) next;
			next = (processor_t *) prev -> next;
		}
		item = (processor_t *) malloc(sizeof(processor_t));
		if (next == list)
			list = item;
		else
			prev -> next = (struct processor_t *) item;
		item -> next = (struct processor_t *) next;
	}

	item -> id = ele.id;
	item -> status = ele.status;
	item -> n = ele.n;
	item -> u = ele.u;
	item -> task = ele.task;

	return list;
}

/*
   Add processor to list, sorted by utilization, descendent
 */

processor_t * add_processor_list_u_sorted_desc(processor_t * list, processor_t ele)
{

	processor_t *item, *next, * prev = list;

	if (!list) { /* empty list  */
		list = (processor_t *) malloc(sizeof(processor_t));
		item = list;
		item -> next = NULL;
	} else {
		next = prev;
		while ((next) && (next -> u >= ele.u)) {
			prev = (processor_t *) next;
			next = (processor_t *) prev -> next;
		}
		item = (processor_t *) malloc(sizeof(processor_t));
		if (next == list)
			list = item;
		else
			prev -> next = (struct processor_t *) item;
		item -> next = (struct processor_t *) next;
	}

	item -> id = ele.id;
	item -> status = ele.status;
	item -> n = ele.n;
	item -> u = ele.u;
	item -> task = ele.task;
	return list;
}

/*
   Get processor pointer
 */

processor_t * get_processor_pointer(processor_t * list, int processor_id)
{

	processor_t *next = list;

	while (next) {
		if (next -> id == processor_id) {
			return next;
		} else {
			next = (processor_t *) next -> next;
		}
	}

	return NULL;
}

/*
    Delete processor from list
 */

processor_t * del_processor_head_list(processor_t * list)
{
	processor_t * item;

	if (list) { /* not empty list  */
		item = (processor_t *) list -> next;
		free(list);
		return item;
	} else
		return NULL;
}

processor_t * del_processor_list(processor_t * list, int id)
{

	processor_t *next, * prev = list;

	if (list) { /* not empty list  */
		if (list -> id == id) { /* processor is list's head */
			next = (processor_t *) list -> next;
			free(list);
			return next;
		}
		next = prev;
		while ((next) && (next -> id != id)) {
			prev = (processor_t *) next;
			next = (processor_t *) prev -> next;
		}
		if (next) { /* processor's in list  */
			prev -> next = next -> next;
			free(next);
		}
	}
	// LOG("Deleted processor %d\n", id);
	return list;
}

processor_t * copy_processor_list(processor_t * source, processor_t * dest)
{
	processor_t * item, * prev, * list = source;

	dest = NULL;

	while (list) {
		item = (processor_t *) malloc(sizeof(processor_t));
		item -> id = list -> id;
		item -> status = list -> status;
		item -> u = list -> u;
		item -> task = list -> task;
		item -> next = NULL;
		if (!dest) {
			dest = item;
			prev = item;
		} else {
			prev -> next = (struct processor_t *) item;
			prev = item;
		}
		list = (processor_t *) list -> next;
	}
	return dest;
}

/*
    Print processor list
 */


void print_processor_list(processor_t * list)
{
	processor_t * item = list;
	task_set_t *task;

	LOG("Processors used (processor id, status (0=idle), utilization, no of tasks):\n");

	while (item) {
		task = item -> task;
		LOG("processor %d, %d, %.2f, %d\n", item -> id, item -> status, item -> u, item -> n);
		item = (processor_t *) item -> next;
	}
}

void write_processor_list_to_file(processor_t * list, FILE *file)
{
	/*
	    File MUST be opened by the calling function
	 */
	processor_t * item = list;
	task_set_t *task;
	char line[80];

	while (item) {
		task = item -> task;
		if (item -> next)
			sprintf(line, "%d\t%.2f\%d\n", item -> id, item -> status, item -> u, task -> id);
		else
			sprintf(line, "%d\t%.2f\%d\0n", item -> id, item -> status, item -> u, task -> id);
		fprintf(file, line);
		item = (processor_t *) item -> next;
	}
}
