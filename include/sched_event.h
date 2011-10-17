/*   FILE:

	 sched_event.h

    DESCRIPTION:

	 Task sctructure and data definitions

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

   LAST REVISION:    January 2009

 */

#ifndef __SCHED_EVENT_H__
#define __SCHED_EVENT_H__


#include "simulator.h"
//order used as priority

typedef enum {
	SCHEDE_RELEASE = 0,
	SCHEDE_RELEASE_RES,
	SCHEDE_FINISH_RES,
	SCHEDE_SUSPEND,
	SCHEDE_DEADLN_MISS,
	SCHEDE_FINISH,
} event_type;

//#define SCHEDE_RELEASE      0
//#define SCHEDE_FINISH       1
//#define SCHEDE_DEADLN_MISS  2
//#define SCHEDE_RELEASE_RES	3
//#define SCHEDE_FINISH_RES	4
//#define SCHEDE_SUSPEND		5

#define MAX_SIMULATION_TIME  10000000

typedef struct sched_event_t{
	int id;
	event_type t_event;
	double time;
	task_set_t * task;
	double p; /* event (task) priority, if any*/
	int res_id; //resource id for resource events
	processor_t * processor;
	struct sched_event_t * next;
} sched_event_t;

typedef struct stack_event_task{
	event_type t_event;
	double time;
	double p; /* event (task) priority, if any*/
	int res_id; //resource id for resource events
	processor_t * processor;
	struct stack_event_task* next;
} stack_event_task;

/* scheduling events utility routines */

extern double set_task_rm_priority(task_set_t *); /* calculate task priority #*/
extern void push_task_rm_priority(task_set_t *, task_set_t *);

extern double set_task_edf_priority(task_set_t *);
extern double set_task_edf_deadline_priority(task_set_t * task);

extern double set_task_tkc_priority(task_set_t *, double);

extern double set_task_rm_us_3m_2_priority(task_set_t *, int);

extern double set_task_edf_fpedf_priority(task_set_t *);

extern double set_task_edf_us_2m_1_priority(task_set_t *, int);

extern int assign_task_to_processor(processor_t *, task_set_t *, double);

extern task_set_t * find_task_to_execute(task_set_t *, double);
extern task_set_t * find_fifo_task_to_execute(task_set_t *);
extern void get_basename(char *pathname, char* filename);
extern double lcm(task_set_t *); /* calculate lowest common multiple of task's periods */

extern sched_event_t * add_sched_event_list(sched_event_t *, sched_event_t);

extern sched_event_t * add_sched_event_list_time_sorted(sched_event_t *, sched_event_t);

extern sched_event_t * add_sched_event_list_time_sorted_desc(sched_event_t *, sched_event_t);

extern sched_event_t * get_sched_event_pointer(sched_event_t *, int);

extern int is_event_in_list(sched_event_t * list, sched_event_t * event, int *id);

extern sched_event_t * del_sched_event_head_list(sched_event_t *);

extern sched_event_t * del_sched_event_from_list(sched_event_t *, int);
extern sched_event_t * del_sched_event_task_from_list(sched_event_t * list, task_set_t* task);
extern sched_event_t * del_sched_event_task_resource_from_list(sched_event_t * list, task_set_t* task);

extern sched_event_t * copy_sched_event_list(sched_event_t *, sched_event_t *);

extern void print_sched_event_list(sched_event_t *);

extern void write_sched_event_list_to_file(sched_event_t * list, FILE *);


#endif