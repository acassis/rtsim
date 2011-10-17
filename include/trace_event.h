/*   FILE:

	 trace_event.h

    DESCRIPTION:

	 Trace event sctructure and data declarations

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

   LAST REVISION:    January 2010

 */
#ifndef __TRACE_EVENT_H__
#define __TRACE_EVENT_H__

#include "simulator.h"
#include <stdio.h>

enum TEVENT {
	ACTIVATE_TASK = 0,
	EXECUTE_TASK,
	SUSPEND_TASK,
	END_TASK,
	DEADLINE_TASK,
	PERIOD_TASK,
	FAIL_TASK,
};

extern char* event_name[];

typedef struct trace_event{
	double time;
	int task;
	enum TEVENT t_event;
	struct trace_event *next;
} trace_event;

extern void create_trace_list(char* path, trace_event*list, int task, int time, char* algoritm);
extern trace_event* add_trace_event(trace_event* list, trace_event element);
extern void print_trace_list(trace_event* list);

#endif