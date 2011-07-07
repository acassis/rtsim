/*   FILE:

	 task_lists.hc

    DESCRIPTION:

	 List routines for real-time tasks programs

    Copyright (C) 2008

	 Arnoldo D�az Ram�rez, Pedro Mejia Alvarez

   This is free software;  you can  redistribute it  and/or modify it under
   terms of the  GNU General Public License as published  by the Free Soft-
   ware  Foundation;  either version 2,  or (at your option) any later ver-
   sion.  It is distributed in the hope that it will be useful, but WITH-
   OUT ANY WARRANTY;  without even the  implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
   for  more details.  You should have  received  a copy of the GNU General
   Public License;  see file COPYING.  If not, write to  the Free Software
   Foundation,  59 Temple Place - Suite 330,  Boston, MA 02111-1307, USA.

   LAST REVISION:    January 2008

 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../include/task.h"

/*
    Add task to list
 */

task_set_t * add_task_list(task_set_t * list, task_set_t ele)
{

	task_set_t *item, * prev = list;

	if (!list) { /* empty list  */
		list = (task_set_t *) malloc(sizeof(task_set_t));
		item = list; /* ???  */
	} else {
		while (prev -> next) {
			prev = (task_set_t *) prev -> next; /*  ???? */
		}
		prev -> next = (struct task_set_t *) malloc(sizeof(task_set_t));
		item = (task_set_t *) prev -> next;
	}

	item -> id = ele.id;
	item -> state = ele.state;
	item -> t = ele.t;
	item -> c = ele.c;
	item -> d = ele.d;
	item -> deadline = ele.deadline;
	item -> p = ele.p;
	item -> r = ele.r;
	item -> e = ele.e;
	item -> cet = ele.cet;
	item -> f = ele.f;
	item -> s = ele.s;
	item -> next = NULL;
	item ->res = ele.res;
	item ->se = ele.se;

	return list;
}

/*
   Add task to list, sorted by period
 */

task_set_t * add_task_list_t_sorted(task_set_t * list, task_set_t ele)
{

	task_set_t *item, *next, * prev = list;

	if (!list) { /* empty list  */
		list = (task_set_t *) malloc(sizeof(task_set_t));
		item = list;
		item -> next = NULL;
	} else {
		next = prev;
		while ((next) && (next -> t <= ele.t)) {
			prev = (task_set_t *) next;
			next = (task_set_t *) prev -> next;
		}
		item = (task_set_t *) malloc(sizeof(task_set_t));
		if (next == list)
			list = item;
		else
			prev -> next = (struct task_set_t *) item;
		item -> next = (struct task_set_t *) next;
	}

	item -> id = ele.id;
	item -> state = ele.state;
	item -> t = ele.t;
	item -> c = ele.c;
	item -> d = ele.d;
	item -> deadline = ele.deadline;
	item -> p = ele.p;
	item -> r = ele.r;
	item -> e = ele.e;
	item -> cet = ele.cet;
	item -> f = ele.f;
	item -> s = ele.s;
	item ->res = ele.res;
	item ->se = ele.se;

	return list;
}

/*
   Add task to list, sorted by period, descendent    
 */

task_set_t * add_task_list_t_sorted_desc(task_set_t * list, task_set_t ele)
{

	task_set_t *item, *next, * prev = list;

	if (!list) { /* empty list  */
		list = (task_set_t *) malloc(sizeof(task_set_t));
		item = list;
		item -> next = NULL;
	} else {
		next = prev;
		while ((next) && (next -> t >= ele.t)) {
			prev = (task_set_t *) next;
			next = (task_set_t *) prev -> next;
		}
		item = (task_set_t *) malloc(sizeof(task_set_t));
		if (next == list)
			list = item;
		else
			prev -> next = (struct task_set_t *) item;
		item -> next = (struct task_set_t *) next;
	}

	item -> id = ele.id;
	item -> state = ele.state;
	item -> t = ele.t;
	item -> c = ele.c;
	item -> d = ele.d;
	item -> deadline = ele.deadline;
	item -> p = ele.p;
	item -> r = ele.r;
	item -> e = ele.e;
	item -> cet = ele.cet;
	item -> f = ele.f;
	item -> s = ele.s;
	item ->res = ele.res;
	item ->se = ele.se;

	return list;
}

/*
    Add task to list, sorted by utilization
 */

task_set_t * add_task_list_u_sorted(task_set_t * list, task_set_t ele)
{

	task_set_t *item, *next, * prev = list;
	double u_next, u_ele;

	if (!list) { /* empty list  */
		list = (task_set_t *) malloc(sizeof(task_set_t));
		item = list;
		item -> next = NULL;
	} else {
		next = prev;
		u_next = next -> c / next -> t;
		u_ele = ele.c / ele.t;
		while ((next) && (u_next <= u_ele)) {
			prev = (task_set_t *) next;
			next = (task_set_t *) prev -> next;
		}
		item = (task_set_t *) malloc(sizeof(task_set_t));
		if (next == list)
			list = item;
		else
			prev -> next = (struct task_set_t *) item;
		item -> next = (struct task_set_t *) next;
	}

	item -> id = ele.id;
	item -> state = ele.state;
	item -> t = ele.t;
	item -> c = ele.c;
	item -> d = ele.d;
	item -> deadline = ele.deadline;
	item -> p = ele.p;
	item -> r = ele.r;
	item -> e = ele.e;
	item -> cet = ele.cet;
	item -> f = ele.f;
	item -> s = ele.s;
	item ->res = ele.res;
	item ->se = ele.se;

	return list;
}

/*
   Add task to list, sorted by utilization, descendent
 */

task_set_t * add_task_list_u_sorted_desc(task_set_t * list, task_set_t ele)
{

	task_set_t *item, *next, * prev = list;
	double u_next, u_ele;

	if (!list) { /* empty list  */
		list = (task_set_t *) malloc(sizeof(task_set_t));
		item = list;
		item -> next = NULL;
	} else {
		next = prev;
		u_next = next -> c / next -> t;
		u_ele = ele.c / ele.t;
		while ((next) && (u_next >= u_ele)) {
			prev = (task_set_t *) next;
			next = (task_set_t *) prev -> next;
			if (next) {
				u_next = next -> c / next -> t;
				u_ele = ele.c / ele.t;
			}
		}
		item = (task_set_t *) malloc(sizeof(task_set_t));
		if (next == list)
			list = item;
		else
			prev -> next = (struct task_set_t *) item;
		item -> next = (struct task_set_t *) next;
	}

	item -> id = ele.id;
	item -> state = ele.state;
	item -> t = ele.t;
	item -> c = ele.c;
	item -> d = ele.d;
	item -> deadline = ele.deadline;
	item -> p = ele.p;
	item -> r = ele.r;
	item -> e = ele.e;
	item -> cet = ele.cet;
	item -> f = ele.f;
	item -> s = ele.s;
	item ->res = ele.res;
	item ->se = ele.se;

	return list;
}

/*
    Add task to list, sorted by release time
 */

task_set_t * add_task_list_r_sorted(task_set_t * list, task_set_t ele)
{

	task_set_t *item, *next, * prev = list;

	if (!list) { /* empty list  */
		list = (task_set_t *) malloc(sizeof(task_set_t));
		item = list;
		item -> next = NULL;
	} else {
		next = prev;
		while ((next) && (next -> r < ele.r)) {
			prev = (task_set_t *) next;
			next = (task_set_t *) prev -> next;
		}
		/* if tasks have the same release time, sort'em by priority */
		while ((next) && (next -> r == ele.r) && (next -> p >= ele.p)) {
			prev = (task_set_t *) next;
			next = (task_set_t *) prev -> next;
		}
		item = (task_set_t *) malloc(sizeof(task_set_t));
		if (next == list)
			list = item;
		else
			prev -> next = (struct task_set_t *) item;
		item -> next = (struct task_set_t *) next;
	}

	item -> id = ele.id;
	item -> state = ele.state;
	item -> t = ele.t;
	item -> c = ele.c;
	item -> d = ele.d;
	item -> deadline = ele.deadline;
	item -> p = ele.p;
	item -> r = ele.r;
	item -> e = ele.e;
	item -> cet = ele.cet;
	item -> f = ele.f;
	item -> s = ele.s;
	item ->res = ele.res;
	item ->se = ele.se;

	return list;
}

/*
   Add task to list, sorted by priority
 */

task_set_t * add_task_list_p_sorted(task_set_t * list, task_set_t ele)
{

	task_set_t *item, *next, * prev = list;

	if (!list) { /* empty list  */
		list = (task_set_t *) malloc(sizeof(task_set_t));
		item = list;
		item -> next = NULL;
	} else {
		next = prev;
		while ((next) && (next -> p <= ele.p)) {
			prev = (task_set_t *) next;
			next = (task_set_t *) prev -> next;
		}
		item = (task_set_t *) malloc(sizeof(task_set_t));
		if (next == list)
			list = item;
		else
			prev -> next = (struct task_set_t *) item;
		item -> next = (struct task_set_t *) next;
	}

	item -> id = ele.id;
	item -> state = ele.state;
	item -> t = ele.t;
	item -> c = ele.c;
	item -> d = ele.d;
	item -> deadline = ele.deadline;
	item -> p = ele.p;
	item -> sp = ele.sp;
	item -> r = ele.r;
	item -> e = ele.e;
	item -> cet = ele.cet;
	item -> f = ele.f;
	item -> s = ele.s;
	item ->res = ele.res;
	item ->se = ele.se;

	return list;
}

/*
     Add task to list, sorted by s (dummy variable)
 */

task_set_t * add_task_list_s_sorted(task_set_t * list, task_set_t ele)
{

	task_set_t *item, *next, * prev = list;

	if (!list) { /* empty list  */
		list = (task_set_t *) malloc(sizeof(task_set_t));
		item = list;
		item -> next = NULL;
	} else {
		next = prev;
		while ((next) && (next -> s <= ele.s)) {
			prev = (task_set_t *) next;
			next = (task_set_t *) prev -> next;
		}
		item = (task_set_t *) malloc(sizeof(task_set_t));
		if (next == list)
			list = item;
		else
			prev -> next = (struct task_set_t *) item;
		item -> next = (struct task_set_t *) next;
	}

	item -> id = ele.id;
	item -> state = ele.state;
	item -> t = ele.t;
	item -> c = ele.c;
	item -> d = ele.d;
	item -> deadline = ele.deadline;
	item -> p = ele.p;
	item -> sp = ele.sp;
	item -> r = ele.r;
	item -> e = ele.e;
	item -> cet = ele.cet;
	item -> f = ele.f;
	item -> s = ele.s;
	item ->res = ele.res;
	item ->se = ele.se;

	return list;
}

/*
    Add task to list, sorted by period, no duplicates
 */

task_set_t * add_task_list_t_sorted_nd(task_set_t * list, task_set_t ele)
{

	task_set_t *item, *next, * prev = list;

	if (!list) { /* empty list  */
		list = (task_set_t *) malloc(sizeof(task_set_t));
		item = list;
		item -> next = NULL;
	} else {
		next = prev;
		while ((next) && (next -> t < ele.t)) {
			prev = (task_set_t *) next;
			next = (task_set_t *) prev -> next;
		}
		if (next && (next -> t == ele.t))
			return list;
		item = (task_set_t *) malloc(sizeof(task_set_t));
		if (next == list)
			list = item;
		else
			prev -> next = (struct task_set_t *) item;
		item -> next = (struct task_set_t *) next;
	}

	item -> id = ele.id;
	item -> state = ele.state;
	item -> t = ele.t;
	item -> c = ele.c;
	item -> d = ele.d;
	item -> deadline = ele.deadline;
	item -> p = ele.p;
	item -> sp = ele.sp;
	item -> r = ele.r;
	item -> e = ele.e;
	item -> cet = ele.cet;
	item -> f = ele.f;
	item -> s = ele.s;
	item ->res = ele.res;
	item ->se = ele.se;

	return list;
}

/*
    Return pointer to task
 */

task_set_t * pointer_to_task(task_set_t * list, int task_id)
{
	task_set_t *next = list;

	while (next) {
		if (next -> id == task_id) {
			return next;
		} else {
			next = (task_set_t *) next -> next;
		}
	}
	return NULL;
}

int is_t_in_task_list(float t, task_set_t * list)
{

	task_set_t *next = list;

	if (!list) { /* empty list  */
		return 0;
	} else {
		while (next) {
			if (next -> t == t)
				return 1;
			next = (task_set_t *) next -> next;
		}
		return 0;
	}
}

/*
    Add task to list, sorted by s (dummy variable), no duplicates
 */

task_set_t * add_task_list_s_sorted_nd(task_set_t * list, task_set_t ele)
{

	task_set_t *item, *next, * prev = list;

	if (!list) { /* empty list  */
		list = (task_set_t *) malloc(sizeof(task_set_t));
		item = list;
		item -> next = NULL;
	} else {
		next = prev;
		while ((next) && (next -> s < ele.s)) {
			prev = (task_set_t *) next;
			next = (task_set_t *) prev -> next;
		}
		if (next && (next -> s == ele.s))
			return list;
		item = (task_set_t *) malloc(sizeof(task_set_t));
		if (next == list)
			list = item;
		else
			prev -> next = (struct task_set_t *) item;
		item -> next = (struct task_set_t *) next;
	}

	item -> id = ele.id;
	item -> t = ele.t;
	item -> c = ele.c;
	item -> d = ele.d;
	item -> deadline = ele.deadline;
	item -> p = ele.p;
	item -> r = ele.r;
	item -> e = ele.e;
	item -> cet = ele.cet;
	item -> f = ele.f;
	item -> s = ele.s;
	item ->res = ele.res;
	item ->se = ele.se;

	return list;
}

/*
    Delete task from list
 */

task_set_t * del_task_head_list(task_set_t * list)
{
	task_set_t * item;

	if (list) { /* not empty list  */
		item = (task_set_t *) list -> next;
		free(list);
		return item;
	} else
		return NULL;
}

task_set_t * del_task_from_list(task_set_t * list, int id)
{

	task_set_t *next, * prev = list;

	if (list) { /* not empty list  */
		if (list -> id == id) { /* task is list's head */
			next = (task_set_t *) list -> next;
			free(list);
			return next;
		}
		next = prev;
		while ((next) && (next -> id != id)) {
			prev = (task_set_t *) next;
			next = (task_set_t *) prev -> next;
		}
		if (next) { /* task's in list  */
			prev -> next = next -> next;
			free(next);
		}
	}
	// LOG("Deleted task %d\n", id);
	return list;
}

task_set_t * copy_task_list(task_set_t * source, task_set_t * dest)
{
	task_set_t * item, * prev, * list = source;

	dest = NULL;

	while (list) {
		item = (task_set_t *) malloc(sizeof(task_set_t));
		item -> id = list -> id;
		item -> t = list -> t;
		item -> c = list -> c;
		item -> d = list -> d;
		item -> deadline = list -> deadline;
		item -> p = list -> p;
		item -> r = list -> r;
		item -> e = list -> e;
		item -> cet = list -> cet;
		item -> f = list -> f;
		item -> s = list -> s;
		item -> next = NULL;

		if (!dest) {
			dest = item;
			prev = item;
		} else {
			prev -> next = (struct task_set_t *) item;
			prev = item;
		}
		list = (task_set_t *) list -> next;
	}
	return dest;
}

/*
    Print task list
 */


void print_task_list(task_set_t * list)
{
	task_set_t * item = list;

	LOG("Task set (period, execution time):\n");

	while (item) {
		LOG("task %d =\t%.2f\t%.2f\n", item -> id, item -> t, item -> c);
		item = (task_set_t *) item -> next;
	}
}

void write_task_list_to_file(task_set_t * list, FILE *file)
{
	/*
	    File MUST be opened by the calling function
	 */
	task_set_t * item = list;
	char line[80];

	while (item) {
		if (item -> next)
			sprintf(line, "%.2f\t%.2f\n", item -> t, item -> c);
		else
			sprintf(line, "%.2f\t%.2f\0n", item -> t, item -> c);
		fprintf(file, line);
		item = (task_set_t *) item -> next;
	}
}

void write_task_info_list_to_file(task_set_t * list, FILE *file)
{
	/*
	    File MUST be opened by the calling function
	 */
	task_set_t * item = list;
	char line[80];
	float uu, ut;

	ut = 0.0;
	while (item) {
		uu = item->c / item->t;
		ut = ut + uu;
		if (item -> next)
			sprintf(line, "%.2f\t%.2f\t%.2f\n", item -> c, item -> t, uu);
		else
			sprintf(line, "%.2f\t%.2f\t%.2f\n", item -> c, item -> t, uu);
		fprintf(file, line);
		item = (task_set_t *) item -> next;
	}
	sprintf(line, "Utotal: %.4f\n", ut);
	fprintf(file, line);
}

void print_task_list_s(task_set_t * list)
{
	task_set_t * item = list;

	LOG("Task set (Si, period, execution time):\n");

	while (item) {
		LOG("task %d =\t%2.5f\t%.2f\t%.2f\n", item -> id, item -> s, item -> t, item -> c);
		item = (task_set_t *) item -> next;
	}
}

/*
     Extra routines
 */


s_t * add_s_list_sorted(s_t * list, s_t ele)
{

	s_t *item, *next, * prev = list;

	if (!list) { /* empty list  */
		list = (s_t *) malloc(sizeof(s_t));
		item = list;
		item -> next = NULL;
	} else {
		next = prev;
		while ((next) && (next -> s < ele.s)) {
			prev = (s_t *) next;
			next = (s_t *) prev -> next;
		}
		item = (s_t *) malloc(sizeof(s_t));
		if (next == list)
			list = item;
		else
			prev -> next = (struct s_t *) item;
		item -> next = (struct s_t *) next;
	}

	item -> id = ele.id;
	item -> s = ele.s;
	item -> r = ele.r;

	return list;
}

s_t * add_s_list_sorted_nd(s_t * list, s_t ele)
{

	s_t *item, *next, * prev = list;

	if (!list) { /* empty list  */
		list = (s_t *) malloc(sizeof(s_t));
		item = list;
		item -> next = NULL;
	} else {
		next = prev;
		while ((next) && (next -> s < ele.s)) {
			prev = (s_t *) next;
			next = (s_t *) prev -> next;
		}
		if (next && (next -> s == ele.s))
			return list;
		item = (s_t *) malloc(sizeof(s_t));
		if (next == list)
			list = item;
		else
			prev -> next = (struct s_t *) item;
		item -> next = (struct s_t *) next;
	}

	item -> id = ele.id;
	item -> s = ele.s;
	item -> r = ele.r;

	return list;
}

s_t * add_s_list_sorted_desc(s_t * list, s_t ele)
{

	s_t *item, *next, * prev = list;

	if (!list) { /* empty list  */
		list = (s_t *) malloc(sizeof(s_t));
		item = list;
		item -> next = NULL;
	} else {
		next = prev;
		while ((next) && (next -> s > ele.s)) {
			prev = (s_t *) next;
			next = (s_t *) prev -> next;
		}
		item = (s_t *) malloc(sizeof(s_t));
		if (next == list)
			list = item;
		else
			prev -> next = (struct s_t *) item;
		item -> next = (struct s_t *) next;
	}

	item -> id = ele.id;
	item -> s = ele.s;
	item -> r = ele.r;

	return list;
}

s_t * add_hc_ele_sorted_desc(s_t * list, s_t ele)
{

	s_t *item, *next, * prev = list;

	if (!list) { /* empty list  */
		list = (s_t *) malloc(sizeof(s_t));
		item = list;
		item -> list = NULL;
	} else {
		next = prev;
		while ((next) && (next -> s > ele.s)) {
			prev = (s_t *) next;
			next = (s_t *) prev -> list;
		}
		item = (s_t *) malloc(sizeof(s_t));
		if (next == list)
			list = item;
		else
			prev -> list = (struct s_t *) item;
		item -> list = (struct s_t *) next;
	}

	item -> id = ele.id;
	item -> s = ele.s;

	return list;
}

s_t * sort_hc_list_desc(s_t * list)
{

	s_t *next, *prev, *temp = NULL;
	s_t *ptr;

	next = list;
	ptr = (s_t *) next -> next;
	while (next) {
		temp = add_hc_ele_sorted_desc(temp, *next);
		prev = next;
		next = (s_t *) next -> list;
		free(prev);
	}
	temp -> next = (struct s_t *) ptr;

	return temp;
}

int get_hc_list_tail(s_t * list)
{

	s_t * item = list;

	if (item) {
		while (item -> list) {
			item = (s_t *) item -> list;
		}
		return(int) item -> s;
	} else
		return -1;
}

s_t * add_hc_list(s_t * list, s_t ele)
{
	s_t *item, * prev = list;

	if (!list) { /* empty list  */
		list = (s_t *) malloc(sizeof(s_t));
		item = list;
	} else {
		while (prev -> next) {
			prev = (s_t *) prev ->next;
		}
		prev -> next = (struct s_t *) malloc(sizeof(s_t));
		item = (s_t *) prev -> next;
	}

	item -> id = ele.id;
	item -> s = ele.s;
	item -> next = NULL;
	item -> list = NULL;

	return list;
}

s_t * add_hc_ele(s_t * list, s_t ele, float base)
{

	s_t *item, *prev = list;

	if (!list) { /* empty list  */
		list = (s_t *) malloc(sizeof(s_t));
		item = list;
		item -> list = NULL;
		item -> id = ele.id;
		item -> s = ele.s;

	} else {
		while ((prev) && (prev -> s != base))
			prev = (s_t *) prev -> next;
		if ((prev) && (prev -> s == base)) {
			while (prev -> list)
				prev = (s_t *) prev -> list;
			item = (s_t *) malloc(sizeof(s_t));
			prev -> list = (struct s_t *) item;
		} else
			return list;
	}
	item -> list = NULL;
	item -> id = ele.id;
	item -> s = ele.s;

	return list;
}

int get_roots_hc_list(s_t * list, float ele)
{
	s_t *hc, *item_temp, *item = list;
	int root, x, is_root, r;

	r = 0;
	while (item) {
		r++; /* explore a new harmonic chain */
		root = get_hc_list_tail(item);
		// LOG("\nroot found = %d\n", root);
		is_root = 1; /* suppose we got a new root  */
		item_temp = list;
		while (item_temp && is_root) {
			hc = item_temp;
			while (hc) {
				x = (int) hc -> s;
				if (((root % x) != 0) || (x > root) || (x > ele)) {
					is_root = 0; /* it's not a root */
					break;
				}
				hc = (s_t *) hc -> list;
			}
			item_temp = (s_t *) item_temp -> next;
		}
		if (is_root)
			r--; /* it's a root */
		item = (s_t *) item -> next;
	}
	return r;
}

void print_s_list(s_t * list)
{
	s_t * item = list;
	int i = 0;

	LOG("\nScheduling points:\n");

	while (item) {
		LOG("S[%d] =\t%.3f\t%.3f\n", i, item -> s, item -> r);
		item = (s_t *) item -> next;
		i++;
	}
}

s_t * get_harmonic_chains_hc_list(task_set_t * list, int * h)
{
	task_set_t *s, *hc_list = list, *tp = NULL;
	s_t new_s;
	static s_t *hc = NULL;
	int base, x, k = 0;

	k = 0; /* number of harmonic chains */

	tp = copy_task_list(hc_list, tp);

	while (tp) {
		base = tp -> t;
		//LOG("BASE = %d\n", base);
		new_s.s = tp -> t;
		new_s.id = tp -> id;
		hc = add_hc_list(hc, new_s);
		//print_s_list(hc);
		tp = del_task_head_list(tp);
		k++;
		//LOG("k = %d\n", k);
		s = tp;
		while (s) {
			x = s -> t;
			if ((x % base) == 0) {
				//LOG("HC found, t = %d, id = %d\n", x, s -> id);
				new_s.s = s -> t;
				new_s.id = s -> id;
				hc = add_hc_ele(hc, new_s, base);
				tp = del_task_from_list(tp, s -> id);
				s = tp;
			} else if (s) {
				s = (task_set_t *) s -> next;
			}
		}
	}
	*h = k;
	return hc;
}

void print_hc_list(s_t * list)
{
	s_t *hc, * item = list;
	int i = 1;

	LOG("\nHarmonic Chains:\n");

	while (item) {
		hc = item;
		LOG("hc(%d):\n", i);
		while (hc) {
			LOG("%d\t%.1f\n", hc -> id, hc -> s);
			hc = (s_t *) hc -> list;
		}
		item = (s_t *) item -> next;
		i++;
	}
}

int uniform_func(int min, int max)
{
	int random;

	if ((max - min) == 0) {
		random = 1;
	} else {
		random = rand() % (max - min);
	}
	random = random + min;
	return(random);
}

/*
	Add resource to list, sorted by id, descendent
 */

list_resource_t* add_resource_list(list_resource_t* list, list_resource_t ele)
{

	list_resource_t *item, *next, * prev = list;

	if (!list) { /* empty list  */
		list = (list_resource_t *) malloc(sizeof(list_resource_t));
		item = list;
		item -> next = NULL;
	} else {
		next = prev;
		while ((next) && (next ->id <= ele.id)) {
			prev = (list_resource_t *) next;
			next = (list_resource_t *) prev -> next;
		}
		item = (list_resource_t *) malloc(sizeof(list_resource_t));
		if (next == list)
			list = item;
		else
			prev->next = (struct list_resource_t *) item;

		item->next = (struct list_resource_t *) next;
	}

	item -> id = ele.id;
	item -> task = NULL;
	return list;
}

task_resource_t* get_resource_task(int res_id, task_resource_t* list)
{
	task_resource_t *item, *next, * prev = list;

	if (!list) { /* empty list  */
		return NULL;
	} else {
		next = prev;
		while ((next)) {
			if (next ->id == res_id)
				return next;

			prev = (task_resource_t *) next;
			next = (task_resource_t *) prev -> next;
		}
	}

	return NULL;
}

task_resource_t* add_resource_task(task_resource_t ele, task_resource_t* list)
{
	task_resource_t *item, *next, * prev = list;

	if (!list) { /* empty list  */
		list = (task_resource_t *) malloc(sizeof(task_resource_t));
		item = list;
		item -> next = NULL;
	} else {
		next = prev;
		while ((next) && (next ->id <= ele.id)) {
			prev = (task_resource_t *) next;
			next = (task_resource_t *) prev -> next;
		}
		item = (task_resource_t *) malloc(sizeof(task_resource_t));
		if (next == list)
			list = item;
		else
			prev->next = (struct task_resource_t *) item;

		item->next = (struct task_resource_t *) next;
	}

	item -> id = ele.id;
	item -> c = ele.c;
	item -> e = ele.e;
	item ->cet = ele.cet;
	item ->f = ele.f;


	return list;
}

int is_id_in_resource_list(int id, list_resource_t * list)
{
	list_resource_t *next = list;
	if (!list) { /* empty list  */
		return 0;
	} else {
		while (next) {
			if (next ->id == id)
				return 1;
			next = (list_resource_t *) next -> next;
		}
		return 0;
	}
}


//#define RESOURCE_SUBFIX "-res.txt"

list_resource_t* load_resource_file(char* file, task_set_t* task, list_resource_t* resource_list)
{
	FILE *in_file; /* Input file */
	char line[255]; /* Input line */
	list_resource_t new_res;
	list_resource_t* list = resource_list;
	task_resource_t new_task_res;

	int d1, d2;
	int i, r;
	int task_res = 0;
	int res = 0;
	//char filename[255];
	//strcpy(filename, file);
	//strcat(&filename[0], RESOURCE_SUBFIX);

	in_file = fopen(file, "r");

	if (!in_file) {
		return 0;
	}

	//skip lines
	for (i = 0; i < (task->id); i++) {
		fgets(line, sizeof(line), in_file);
	}

	new_res.id = 0;
	new_res.next = NULL;

	task_res = 0;
	fscanf(in_file, "%d", &task_res);
	if (task_res > 0) {

		for (r = 0; r < task_res; r++) {
			new_task_res.id = 0;
			new_task_res.c = 0;
			new_task_res.e = 0;
			new_task_res.cet = 0;
			new_task_res.f = 0;
			new_task_res.next = NULL;

			fscanf(in_file, "%d%d%d", &res, &d1, &d2);
			new_task_res.id = res;
			new_task_res.f = d1;
			new_task_res.c = d2;

			if (res > 0) {
				task->res = (task_resource_t*)add_resource_task(new_task_res, (task_resource_t*)task->res);
				if (is_id_in_resource_list(res, resource_list) == 0) {
					new_res.id = res;
					resource_list = add_resource_list(resource_list, new_res);
				}
			}
		}
	}

	fclose(in_file);
	return resource_list;

}

int is_available_resource(int res_id, list_resource_t* list)
{
	list_resource_t *next = list;
	if (!list) { /* empty list  */
		return 0;
	} else {
		while (next) {
			if (next->id == res_id)
				if (next ->task != NULL)
					return 0;
				else
					break;
			next = (list_resource_t *) next -> next;
		}
	}
	return 1;
}

int is_available_resources(task_set_t* task, list_resource_t* list)
{
	list_resource_t* resource_list_element = (task_resource_t*)list;
	task_resource_t* task_resource_element = (task_resource_t*)task->res;
	if (!list) { /* empty list  */
		return 0;
	} else {
		while (task_resource_element) {
			resource_list_element = list;
			while (resource_list_element) {
				if (resource_list_element->id == task_resource_element->id)
					if (resource_list_element->task != NULL && resource_list_element->task != task)
						return 0;
					else
						break;
				resource_list_element = (list_resource_t *) resource_list_element -> next;
			}
			task_resource_element = (list_resource_t*)(task_resource_element->next);
		}
		return 1;
	}
}

void task_resources_update_executed_time(task_set_t* task, double current_time, list_resource_t* list)
{
	task_resource_t* resources = (task_resource_t*)task->res;
	task_set_t* current_task;

	while (resources) {

		current_task = get_task_with_resource(resources->id, list);

		if (current_task && current_task == task) {
			resources->cet += current_time - resources->e;

			//check if is better use this in finish resource event
			if (resources->cet >= resources->c)
				remove_resource_from_task(resources->id, list);
		}

		resources = (task_resource_t*) resources->next;
	}

}

task_set_t* get_task_with_resource(int res_id, list_resource_t* list)
{
	list_resource_t *next = list;

	if (!list) { /* empty list  */
		return 0;
	} else {
		next = list;
		while (next) {
			if (next->id == res_id)
				return (task_set_t*)(next->task);
			next = (list_resource_t *) next->next;
		}
	}

	return 0;
}

task_set_t* get_task_using_task_resource(task_set_t* task, list_resource_t* list)
{
	task_set_t* task_found;
	//task_resource_t* resources	= task->res;
	task_resource_t* current_element;

	if (!list || !task) { /* empty list  */
		return 0;
	} else {
		current_element = (task_resource_t*)task->res;
		while (current_element) {
			task_found = get_task_with_resource(current_element->id, list);
			if (task_found && task_found != task) {
				return task_found;
			}
			current_element = (list_resource_t *)(current_element->next);
		}
	}

	return NULL;

}

void assing_resources_to_task(task_set_t* task, list_resource_t* list)
{
	list_resource_t *next = list;
	task_resource_t *res = (task_resource_t*)task->res;
	if (!list) { /* empty list  */
		return;
	} else {
		while (res) {
			next = list;
			while (next) {
				if (next->id == res->id) {
					next->task = task;
					break;
				}
				next = (list_resource_t *) next -> next;
			}
			res = (list_resource_t*) res->next;
		}
	}
}

void assing_resource_to_task(int res_id, task_set_t* task, list_resource_t* list)
{
	list_resource_t *next = list;
	if (!list) { /* empty list  */
		return;
	} else {
		while (next) {
			if (next->id == res_id) {
				next ->task = task;
				break;
			}
			next = (list_resource_t *) next -> next;
		}
	}
}

void remove_resources_from_task(task_set_t* task, list_resource_t* list)
{
	list_resource_t *next = list;
	task_resource_t *res = (task_resource_t *)task->res;

	if (!list) { /* empty list  */
		return;
	} else {

		while (res) {
			next = list;
			while (next) {
				if (next->id == res->id) {
					next ->task = NULL;
					break;
				}
				next = (list_resource_t *) next -> next;
			}
			res = (list_resource_t*) res->next;
		}
	}
}

void remove_resource_from_task(int resId, list_resource_t* list)
{
	list_resource_t *next = list;
	if (!list) { /* empty list  */
		return;
	} else {
		while (next) {
			if (next->id == resId) {
				next ->task = NULL;
				break;
			}
			next = (list_resource_t *) next -> next;
		}
	}
}