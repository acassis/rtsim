/*   FILE:

	 sched_events.c

    DESCRIPTION:

	 Routines for scheduler events

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
#include "../include/processor.h"
#include "../include/sched_event.h"

/*
	Stack priority
 */

int popd_task_priority(task_set_t* task)
{
	if (task->sp) {
		stack_priority* value = (stack_priority*)task->sp;
		task->sp = value->prev;
		task->p = value->p;

		free(value);

		return 1;
		/*if(task->sp)
		{
			stack_priority* temp = task->sp;
			task->p = temp->p;
			free(value);
		}*/
	}
	return 0;
}

/*
   Set task priority
 */

double set_task_rm_priority(task_set_t * task)
{
	double priority;
	priority = task -> t;

	task->sp = NULL;

	return priority;
}

void push_task_priority(task_set_t* task, task_set_t* priority)
{
	stack_priority* new_value;
	//create new stack	///////////////////
	new_value = (stack_priority*) malloc(sizeof(stack_priority));
	new_value->p = task->p;
	new_value->prev = task->sp;
	///////////////////////////////////////
	task->sp = new_value;
	task->p = priority->p;
}

void push_task_event_to_stack(task_set_t* task, sched_event_t * event_list, double current_time)
{

	stack_event_task* new_event = (stack_event_task*) malloc(sizeof(stack_event_task));

	new_event->t_event = event_list->t_event;
	new_event->time = event_list->time - current_time;
	new_event->p = event_list->p;
	new_event->res_id = event_list->res_id;
	new_event->processor = event_list->processor; //maybe should not save processor
	new_event->next = 0;

	if (task->se) {
		stack_event_task* last_event = (stack_event_task*)task->se;

		while (last_event->next) {
			last_event = last_event->next;
		}

		last_event->next = (stack_event_task*) new_event;
	} else {
		task->se = (stack_event_task*) new_event;
	}
}

void push_task_stack_events(task_set_t* task, sched_event_t * event_list, double current_time)
{
	sched_event_t* current_event = event_list;

	while (current_event) {
		if (current_event->task->id == task->id /*&& current_event->t_event == SCHEDE_SUSPEND*/) {
			push_task_event_to_stack(task, current_event, current_time);
		}
		current_event = (sched_event_t*) current_event->next;
	}
}

sched_event_t* sort_event_list_move_first(sched_event_t * first_event, sched_event_t * event_list)
{
	sched_event_t * prev_event = 0;
	sched_event_t * next_event = 0;
	sched_event_t * current_event = event_list;

	if (first_event != current_event) {
		do {
			prev_event = current_event;
			current_event = (sched_event_t *)current_event->next;
			next_event = (sched_event_t *)current_event->next;
		} while (first_event != current_event);

		first_event->next = (sched_event_t *)event_list;
		prev_event->next = (sched_event_t *)next_event;

		return first_event;
	}

	return event_list;
}

sched_event_t* pop_task_stack_events(task_set_t* task, sched_event_t * event_list, double current_time, int *event_id)
{
	stack_event_task* stack_event = (stack_event_task*) task->se;
	stack_event_task* del_event;

	sched_event_t * first_event = event_list;
	sched_event_t new_event;


	while (stack_event) {

		new_event.id = (*event_id)++;
		new_event.t_event = (int) stack_event->t_event;
		new_event.time = current_time + stack_event->time;
		new_event.task = task;
		new_event.p = stack_event -> p;
		new_event.res_id = stack_event->res_id;
		new_event.processor = stack_event->processor;
		new_event.next = 0;
		event_list = add_sched_event_list_time_sorted(event_list, new_event);

		del_event = stack_event;
		stack_event = (stack_event_task*)stack_event->next;

		free(del_event);
		del_event = 0;
	}

	task->se = 0;

	event_list = sort_event_list_move_first(first_event, event_list);
	return event_list;
}

double set_task_edf_priority(task_set_t * task)
{
	double priority;

	priority = task -> d;
	return priority;
}

double set_task_edf_deadline_priority(task_set_t * task)
{
	double priority;

	priority = task -> deadline;
	return priority;
}

double set_task_tkc_priority(task_set_t * task, double k)
{
	double priority;

	priority = task -> t - k * task -> c;

	return priority;
}

double set_task_rm_us_3m_2_priority(task_set_t * task, int m)
{
	double u, heavy_task_util, priority;

	heavy_task_util = (double) m / (3 * (double) m - 2);
	u = task -> c / task -> t;
	if (u <= heavy_task_util) {
		priority = task -> t;
	} else {
		priority = -1000;
	}
	task->sp = NULL;
	return priority;
}

double set_task_edf_fpedf_priority(task_set_t * task)
{
	double u, bound, priority;

	bound = 0.5;
	u = task -> c / task -> t;
	if (u <= bound) {
		priority = task -> d;
	} else {
		priority = -1000;
	}
	task->sp = NULL;
	return priority;
}

double set_task_edf_us_2m_1_priority(task_set_t * task, int m)
{
	double u, heavy_task_util, priority;

	heavy_task_util = (double) m / (2 * (double) m - 1);
	u = task -> c / task -> t;
	if (u <= heavy_task_util) {
		priority = task -> d;
	} else {
		priority = -1000;
	}
	task->sp = NULL;
	return priority;
}

/*
   Assign task to processor
 */

int assign_task_to_processor(processor_t * processor, task_set_t * task_to_assign, double time)
{
	task_resource_t* task_res = (task_resource_t*)task_to_assign->res;

	processor -> status = PROCESSOR_BUSY;
	processor -> u = task_to_assign -> c / task_to_assign -> t;
	processor -> task = task_to_assign;
	task_to_assign -> state = TASK_RUNNING;
	task_to_assign -> e = time;

	while (task_res) {
		//check if task is owner of resource
		task_res->e = time;
		task_res = (task_resource_t*)task_res->next;
	}


	return 0;
}

/*
   Find next task to execute
 */

task_set_t * find_task_to_execute(task_set_t * list, double time)
{
	task_set_t * task = list;

	task_set_t* task_priority = NULL;
	while (task) {
		if ((task -> r <= time) && (task -> state == TASK_READY)) {
			if (task_priority == NULL)
				task_priority = task;
			else if (task->p < task_priority->p)
				task_priority = task;
			else if (task->p == task_priority->p) {
				//if both task have the same priority, look in the stack of priority
				//task with deep stack is prioritary
				stack_priority* stack_a = (stack_priority*)task->sp;
				stack_priority* stack_b = (stack_priority*)task_priority->sp;

				while (stack_a && stack_b) {
					stack_a = (stack_priority*)stack_a->prev;
					stack_b = (stack_priority*)stack_b->prev;
				}

				if (stack_a)
					task_priority = task;

			}
		}
		task = (task_set_t *) task -> next;
	}

	return task_priority;
}

/*
   Find next task to execute
 */

task_set_t * find_fifo_task_to_execute(task_set_t * list)
{
	task_set_t * task = list;
	task_set_t * firstTask = 0;

	while (task) {
		//if(task -> state == TASK_READY)
		{
			if (firstTask == 0)
				firstTask = task;
			else if (task->p < firstTask->p)
				firstTask = task;
		}

		task = (task_set_t *) task -> next;
	}

	return firstTask;
}
//////////////

/*
   Get name file from a path
 */
void get_basename(char *pathname, char* filename)
{
	int namestart = -1;
	int nameend = -1;
	int nameid = 0;
	char name[255];

	char *pname = pathname;
	int i = 0;
	while (*pname != '\0') {
		if (*pname == '.')
			nameend = i;

		pname++;
		i++;
	}

	i = 0;
	pname = pathname;
	while (*pname != '\0') {
		if (*pname == '/')
			namestart = i;

		pname++;
		i++;
	}

	if (namestart <= 0) {
		i = 0;
		pname = pathname;
		while (*pname != '\0') {
			if (*pname == '\\')
				namestart = i;

			pname++;
			i++;
		}
	}
	namestart++;


	for (i = namestart; i < nameend; i++) {
		name[nameid] = pathname[i];
		nameid++;
	}

	name[nameid] = '\0';
	strcpy(filename, &name[0]);
}///////////////////////////////

/*
  Calculate lowest common multiple of task's periods
 */

double lcm(task_set_t *task_list)
{
	int n;
	double period, last_period, factor;
	task_set_t *tt;

	tt = task_list;
	while (tt) {
		last_period = tt -> t;
		tt = (task_set_t *) tt -> next;
	}
	for (n = 1;; n++) {
		tt = task_list;
		factor = (double) n * last_period;
		if (factor > (double) MAX_SIMULATION_TIME)
			return(double) MAX_SIMULATION_TIME;
		period = (double) tt -> t;
		while ((tt) && (fmod(factor, period) == 0)) {
			tt = (task_set_t *) tt -> next;
			if (tt)
				period = (double) tt -> t;
		}
		if (!tt)
			return factor;
	}
}

/*
    Add sched_event to list
 */


sched_event_t * add_sched_event_list(sched_event_t * list, sched_event_t ele)
{

	sched_event_t *item, * prev = list;

	if (!list) { /* empty list  */
		list = (sched_event_t *) malloc(sizeof(sched_event_t));
		item = list;
	} else {
		while (prev -> next) {
			prev = (sched_event_t *) prev -> next;
		}
		prev -> next = (struct sched_event_t *) malloc(sizeof(sched_event_t));
		item = (sched_event_t *) prev -> next;
	}

	item -> id = ele.id;
	item ->t_event = ele.t_event;
	item -> time = ele.time;
	item -> task = ele.task;
	item -> p = ele.p;
	item -> res_id = ele.res_id;
	item -> processor = ele.processor;
	item -> next = NULL;

	return list;
}

/*
    Add sched_event to list, sorted by time
 */

sched_event_t * add_sched_event_list_time_sorted(sched_event_t * list, sched_event_t ele)
{

	sched_event_t *item, *next, * prev = list;

	if (!list) { /* empty list  */
		list = (sched_event_t *) malloc(sizeof(sched_event_t));
		item = list;
		item -> next = NULL;
	} else {
		next = prev;
		/* we go through list while time of events in list is smaller */
		while ((next) && (next -> time < ele.time)) {
			prev = (sched_event_t *) next;
			next = (sched_event_t *) prev -> next;
		}
		/* tnext, if event is not finish, go thorugh list until there are no finish events at the same time */
		if (ele.t_event != SCHEDE_FINISH) {
			/* now we go through list while time is equal and event is not TASK_FINISH */
			while ((next) && (next -> time == ele.time) && (next ->t_event == SCHEDE_FINISH)) {
				prev = (sched_event_t *) next;
				next = (sched_event_t *) prev -> next;
			}

			//sort events according with priority events "event_type" , (first task_release, last suspend, finish, and deadline miss)
			while ((next) && (next -> time == ele.time) && (next ->t_event < ele.t_event)) {
				prev = (sched_event_t *) next;
				next = (sched_event_t *) prev -> next;
			}

			/* now we go through list while time is equal and priority is not higher */
			while ((next) && (next -> time == ele.time) && (next -> p <= ele.p)) {
				prev = (sched_event_t *) next;
				next = (sched_event_t *) prev -> next;
			}
		} else {
			/* then, if event is finish, insert it, otherwise insert it (FIFO) after all finish events with equal time */
			while ((next) && (next -> time == ele.time) && (next ->t_event == SCHEDE_FINISH)) {
				prev = (sched_event_t *) next;
				next = (sched_event_t *) prev -> next;
			}
		}
		/* insert new event */
		item = (sched_event_t *) malloc(sizeof(sched_event_t));
		if (next == list) {
			list = item;
		} else {
			prev -> next = (struct sched_event_t *) item;
		}
		item -> next = (struct sched_event_t *) next;
	}

	item -> id = ele.id;
	item ->t_event = ele.t_event;
	item -> time = ele.time;
	item -> task = ele.task;
	item -> p = ele.p;
	item -> res_id = ele.res_id;
	item -> processor = ele.processor;

	return list;
}

/*
   Add sched_event to list, sorted by time, descendent
 */

sched_event_t * add_sched_event_list_time_sorted_desc(sched_event_t * list, sched_event_t ele)
{

	sched_event_t *item, *next, * prev = list;

	if (!list) { /* empty list  */
		list = (sched_event_t *) malloc(sizeof(sched_event_t));
		item = list;
		item -> next = NULL;
	} else {
		next = prev;
		while ((next) && (next -> time >= ele.time)) {
			prev = (sched_event_t *) next;
			next = (sched_event_t *) prev -> next;
		}
		item = (sched_event_t *) malloc(sizeof(sched_event_t));
		/* we go through list while time is bigger */
		while ((next) && (next -> time < ele.time)) {
			prev = (sched_event_t *) next;
			next = (sched_event_t *) prev -> next;
		}
		/* now we go through list while time is equal and priority is not higher */
		while ((next) && (next -> time == ele.time) && (next -> p >= ele.p)) {
			prev = (sched_event_t *) next;
			next = (sched_event_t *) prev -> next;
		}
		if (next == list)
			list = item;
		else
			prev -> next = (struct sched_event_t *) item;
		item -> next = (struct sched_event_t *) next;
	}

	item -> id = ele.id;
	item ->t_event = ele.t_event;
	item -> time = ele.time;
	item -> task = ele.task;
	item -> p = ele.p;
	item -> res_id = ele.res_id;
	item -> processor = ele.processor;

	return list;
}

/*
   Get sched_event pointer
 */

sched_event_t * get_sched_event_pointer(sched_event_t * list, int id)
{

	sched_event_t *next = list;

	while ((next) && (next -> id != id)) {
		next = (sched_event_t *) next -> next;
	}

	if (next)
		return next;
	else
		return NULL;
}

/*
   Get sched_event pointer
 */


int is_event_in_list(sched_event_t * list, sched_event_t *event, int *id)
{

	sched_event_t *next = list;

	while (next) {
		if ((next -> time == event -> time) && (next -> task == event -> task) && (next ->t_event == event ->t_event)) {
			*id = next -> id;
			return 1;
		} else {
			next = (sched_event_t *) next -> next;
		}
	}

	return 0;
}

/*
    Delete sched_event from list
 */

sched_event_t * del_sched_event_head_list(sched_event_t * list)
{
	sched_event_t * item;

	if (list) { /* not empty list  */
		item = (sched_event_t *) list -> next;
		free(list);
		return item;
	} else
		return NULL;
}

sched_event_t * del_sched_event_from_list(sched_event_t * list, int id)
{

	sched_event_t *next, * prev = list;

	if (list) { /* not empty list  */
		if (list -> id == id) { /* sched_event is list's head */
			next = (sched_event_t *) list -> next;
			free(list);
			return next;
		}
		next = prev;
		while ((next) && (next -> id != id)) {
			prev = (sched_event_t *) next;
			next = (sched_event_t *) prev -> next;
		}
		if (next) { /* sched_event's in list  */
			prev -> next = next -> next;
			free(next);
		}
	}
	// LOG("Deleted sched_event %d\n", id);
	return list;
}

sched_event_t * del_sched_event_task_from_list(sched_event_t * list, task_set_t* task)
{
	task_resource_t* resources = (task_resource_t*) task->res;
	sched_event_t *next, * prev = list;

	if (list) { /* not empty list  */

		while (resources && list) {
			int id = task->id;

			int repeat = 0;
			do {
				repeat = 0;
				next = prev = list;

				if (list->task->id == id) { /* sched_event is list's head */
					next = (sched_event_t *) list -> next;
					free(list);
					list = next;
					repeat = 1;
				} else {
					next = prev;
					while ((next) && (next->task->id != id)) {
						prev = (sched_event_t *) next;
						next = (sched_event_t *) prev -> next;
					}
					if (next) { /* sched_event's in list  */
						prev -> next = next -> next;
						free(next);
						repeat = 1;
					}
				}
			} while (repeat && list);
			resources = (task_resource_t*) resources->next;
		}

	}
	return list;
}

sched_event_t * del_sched_event_task_resource_from_list(sched_event_t * list, task_set_t* task)
{

	task_resource_t* resources = (task_resource_t*) task->res;

	sched_event_t *next, * prev = list;

	if (list) { /* not empty list  */

		while (resources && list) {
			int id = resources->id;

			int repeat = 0;
			do {
				repeat = 0;
				next = prev = list;

				if (list->res_id == id) { /* sched_event is list's head */
					next = (sched_event_t *) list -> next;
					free(list);
					list = next;
					repeat = 1;
				} else {
					next = prev;
					while ((next) && (next -> res_id != id)) {
						prev = (sched_event_t *) next;
						next = (sched_event_t *) prev -> next;
					}
					if (next) { /* sched_event's in list  */
						prev -> next = next -> next;
						free(next);
						repeat = 1;
					}
				}
			} while (repeat && list);
			resources = (task_resource_t*) resources->next;
		}

	}
	// LOG("Deleted sched_event %d\n", id);
	return list;
}

sched_event_t * copy_sched_event_list(sched_event_t * source, sched_event_t * dest)
{
	sched_event_t * item, * prev, * list = source;

	dest = NULL;

	while (list) {
		item = (sched_event_t *) malloc(sizeof(sched_event_t));
		item -> id = list -> id;
		item ->t_event = list ->t_event;
		item -> time = list -> time;
		item -> task = list -> task;
		item -> p = list -> p;
		item -> processor = list -> processor;
		item -> next = NULL;
		if (!dest) {
			dest = item;
			prev = item;
		} else {
			prev -> next = (struct sched_event_t *) item;
			prev = item;
		}
		list = (sched_event_t *) list -> next;
	}
	return dest;
}

/*
    Print sched_event list
 */


void print_sched_event_list(sched_event_t * list)
{
	sched_event_t * item = list;
	task_set_t *task;
	processor_t *proc;

	LOG("Scheduling events list:\n");

	while (item) {
		task = item -> task;
		proc = item -> processor;
		if (proc)
			LOG("sched_event %d, event %d, time %d, task id %d, priority %d, processor %d\n",  \
               item -> id, item ->t_event, item -> time, task -> id, item -> p, item -> processor->id);
		else
			LOG("sched_event %d, event %d, time %.2f, task id %d, priority %.2f\n",  \
               item -> id, item ->t_event, item -> time, task -> id, item -> p);

		item = (sched_event_t *) item -> next;
	}
}

void write_sched_event_list_to_file(sched_event_t * list, FILE *file)
{
	/*
	 File MUST be opened by the calling function
	 */
	sched_event_t * item = list;
	task_set_t * task;
	processor_t *proc;
	char line[80];

	while (item) {
		task = item -> task;
		proc = item -> processor;
		if (item -> next)
			sprintf(line, "%d\t%.2f\%d\n", item -> id, item ->t_event, item -> time, task -> id, item -> p, proc -> id);
		else
			sprintf(line, "%d\t%.2f\%d\0n", item -> id, item ->t_event, item -> time, task -> id, item -> p, proc -> id);
		fprintf(file, line);
		item = (sched_event_t *) item -> next;
	}
}
