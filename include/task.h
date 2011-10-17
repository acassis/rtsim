/*   FILE:

	 task.h

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

   LAST REVISION:    January 2008

 */

#ifndef __TASK_H__
#define __TASK_H__

#include "simulator.h"
#include <stdio.h>

/* task sates */

typedef enum {
	TASK_NEW = 0,
	TASK_READY,
	TASK_RUNNING,
	TASK_WAITING,
	TASK_TERMINATED,
} task_state;

typedef struct task_resource_t{
	int id; /* resource id in resource list */
	double c; /* execution time */
	double e; /* start execution time */
	double cet; /* cumulative execution time */
	double f; /* phase */
	struct task_resource_t* next;
} task_resource_t;

typedef struct list_resource_t{
	int id;
	struct task_set_t* task;
	struct list_resource_t* next;
} list_resource_t;

typedef struct stack_priority{
	double p;
	struct stack_priority* prev;
} stack_priority;

typedef struct task_set_t{
	int id;
	task_state state;
	double t; /* period  */
	double c; /* execution time */
	double d; /* deadline  */
	double deadline; /* current deadline  */
	double p; /* priority  */
	struct stack_priority *sp; //stack priority
	struct stack_event_task* se; //stack events for suspend task
	double r; /* release time */
	double e; /* start execution time */
	double cet; /* cumulative execution time */
	double f; /* phase */
	float s; /* dummy variable */
	struct task_resource_t* res; /*resource list*/
	struct task_set_t * next;
} task_set_t;

typedef struct s_t{
	int id;
	float s; /* dummy variable */
	float r; /* dummy variable */
	struct s_t * next;
	struct s_t * list;
} s_t;



extern list_resource_t* load_resource_file(char*, task_set_t*, list_resource_t*);
extern task_resource_t* add_resource_task(task_resource_t id, task_resource_t*);
extern task_resource_t* get_resource_task(int id, task_resource_t*);

extern list_resource_t* add_resource_list(list_resource_t*, list_resource_t);
extern int is_id_in_resource_list(int id, list_resource_t*);
extern int is_available_resource(int, list_resource_t*);
extern void assing_resource_to_task(int, task_set_t*, list_resource_t*);
extern void remove_resource_from_task(int, list_resource_t*);

extern void remove_resources_from_task(task_set_t*, list_resource_t*);
extern int is_available_resources(task_set_t*, list_resource_t*);
extern void assing_resources_to_task(task_set_t*, list_resource_t*);

extern task_set_t* get_task_with_resource(int, list_resource_t*);
extern void task_resources_update_executed_time(task_set_t*, double, list_resource_t*);


extern task_set_t * add_task_list(task_set_t *, task_set_t);

extern task_set_t * add_task_list_t_sorted(task_set_t *, task_set_t);

extern task_set_t * add_task_list_t_sorted_desc(task_set_t *, task_set_t);

extern task_set_t * add_task_list_u_sorted(task_set_t *, task_set_t);

extern task_set_t * add_task_list_u_sorted_desc(task_set_t *, task_set_t);

extern task_set_t * add_task_list_r_sorted(task_set_t *, task_set_t);

extern task_set_t * add_task_list_p_sorted(task_set_t *, task_set_t);

extern task_set_t * add_task_list_s_sorted(task_set_t *, task_set_t);

extern task_set_t * add_task_list_t_sorted_nd(task_set_t *, task_set_t);

extern task_set_t * pointer_to_task(task_set_t *, int);

extern task_set_t * add_task_list_s_sorted_nd(task_set_t *, task_set_t);

extern task_set_t * del_task_head_list(task_set_t *);

extern task_set_t * del_task_from_list(task_set_t *, int);

extern task_set_t * copy_task_list(task_set_t *, task_set_t *);

extern void print_task_list(task_set_t *);

extern void write_task_list_to_file(task_set_t *, FILE *);

extern void write_task_info_list_to_file(task_set_t *, FILE *);

extern void print_task_list_s(task_set_t *);

extern s_t * add_s_list_sorted(s_t *, s_t);

extern s_t * add_s_list_sorted_nd(s_t *, s_t);

extern s_t * add_s_list_sorted_desc(s_t *, s_t);

extern s_t * add_hc_ele_sorted_desc(s_t *, s_t);

extern s_t * sort_hc_list_desc(s_t *);

extern int get_hc_list_tail(s_t *);

extern s_t * add_hc_list(s_t *, s_t);

extern s_t * add_hc_ele(s_t *, s_t, float);

extern int get_roots_hc_list(s_t *, float);

extern void print_s_list(s_t *);

extern s_t * get_harmonic_chains_hc_list(task_set_t *, int *);

extern void print_hc_list(s_t *);

extern int uniform_func(int, int);

#endif