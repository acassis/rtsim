/*   FILE:

	 processor.h

    DESCRIPTION:

	 Task sctructure and data definitions

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

   LAST REVISION:    January 2009

 */
#ifndef __PROCESSOR_H__
#define __PROCESSOR_H__

#include "simulator.h"
#include "trace_event.h"

#define PROCESSOR_IDLE  0
#define PROCESSOR_BUSY  1

typedef struct {
	int id;
	int status;
	int n; /* no of tasks assigned to processor */
	float u; /* utilization of task assigned to processor  */
	task_set_t * task; /* task executing on processor */
	trace_event * tracer;

	struct processor_t * next;
} processor_t;


extern processor_t * add_processor_list(processor_t *, processor_t);

extern processor_t * add_processor_list_u_sorted(processor_t *, processor_t);

extern processor_t * add_processor_list_u_sorted_desc(processor_t *, processor_t);

extern processor_t * get_processor_pointer(processor_t *, int);

extern processor_t * del_processor_head_list(processor_t *);

extern processor_t * del_processor_list(processor_t *, int);

extern processor_t * copy_processor_list(processor_t *, processor_t *);

extern void print_processor_list(processor_t *);

extern void write_processor_list_to_file(processor_t *, FILE *);

#endif 