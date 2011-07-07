/*   FILE:

	 trace_event.c

    DESCRIPTION:

	 Trace event sctructure and data definitions

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
#include "../include/trace_event.h"

char *event_name[] ={
	"ACTIVE",
	"EXECUTE",
	"SUSPEND",
	"END",
	"DEADLINE",
	"FAIL",
};

void print_trace_list(trace_event* list)
{
	trace_event* event;

	event = list;
	LOG("\nTrace Info\n");
	while (event) {
		LOG("time: %d\t\t task: %d\t\t event: %s\n", event->time, event->task, event_name[event->t_event]);
		event = (trace_event*) (event->next);
	}

}

trace_event* add_trace_event(trace_event* list, trace_event element)
{

	trace_event *item = 0, *next = 0, * prev = list;

	if (!list) { /* empty list  */
		list = (trace_event *) (malloc(sizeof(trace_event)));
		item = list;
		item -> next = NULL;
	} else {
		next = prev;
		/* we go through list while time of events in list is smaller */
		while ((next) && (next -> time <= element.time)) {
			prev = (trace_event *) next;
			next = (trace_event *) prev -> next;
		}
		/* insert new event */
		item = (trace_event*) (malloc(sizeof(trace_event)));
		if (next == list) {
			list = item;
		} else {
			prev -> next = (struct trace_event *) item;
		}
		item -> next = (struct trace_event *) next;
	}

	//item -> id = ele.id;
	item ->t_event = element.t_event;
	item -> time = element.time;
	item -> task = element.task;

	return list;
}

#define MAX_LINE 255

FILE* trace_event_file;
char trace_event_line[MAX_LINE];

int open_file(char *path)
{
	if (trace_event_file != 0) {
		LOG("\n**warning previos file is open\n");
	}
	trace_event_file = 0;
	//open file for write text
	trace_event_file = fopen(path, "w+");
	if (trace_event_file == 0) {
		return 0;
	}

	return 1;
}

void close_file()
{
	//flush pending writes
	fflush(trace_event_file);
	//close file
	fclose(trace_event_file);
	trace_event_file = 0;
}

void active_task(int time, int task)
{
	//print lines for activate a task
	sprintf(trace_event_line, "%d  READY-B %d\n", time, task);
	fputs(trace_event_line, trace_event_file);
	sprintf(trace_event_line, "%d  START %d\n", time, task);
	fputs(trace_event_line, trace_event_file);
}

void run_task(int time, int task)
{
	//print lines for run a task
	//sprintf(trace_event_line, "%d    STOP %d\n", time, task);		fputs(trace_event_line,trace_event_file);
	sprintf(trace_event_line, "%d    EXEC-B %d\n", time, task);
	fputs(trace_event_line, trace_event_file);
}

void finish_task(int time, int task)
{
	//print lines for finish a task
	sprintf(trace_event_line, "%d  READY-E %d\n", time, task);
	fputs(trace_event_line, trace_event_file);
	sprintf(trace_event_line, "%d  STOP %d\n", time, task);
	fputs(trace_event_line, trace_event_file);
	sprintf(trace_event_line, "%d  EXEC-E %d\n", time, task);
	fputs(trace_event_line, trace_event_file);
}

void fail_task(int time, int task)
{
	//print lines for fail a task
	sprintf(trace_event_line, "%d  ARROWUP %d Miss\n", time, task);
	fputs(trace_event_line, trace_event_file);
	sprintf(trace_event_line, "%d  STOP %d\n", time, task);
	fputs(trace_event_line, trace_event_file);
	sprintf(trace_event_line, "%d  READY-E %d\n", time, task);
	fputs(trace_event_line, trace_event_file);
	sprintf(trace_event_line, "%d    EXEC-E %d\n", time, task);
	fputs(trace_event_line, trace_event_file);
	//finish_task(time,task);

}

void suspend_task(int time, int task)
{
	//print lines for suspend a task
	/*
time   READY-E task
time   STOP task 
time   EXEC-E task
time	 ARROWDOWN task "pause"
	 */
	sprintf(trace_event_line, "%d    READY-E %d\n", time, task);
	fputs(trace_event_line, trace_event_file);
	sprintf(trace_event_line, "%d    STOP %d\n", time, task);
	fputs(trace_event_line, trace_event_file);
	sprintf(trace_event_line, "%d    EXEC-E %d\n", time, task);
	fputs(trace_event_line, trace_event_file);
	sprintf(trace_event_line, "%d    ARROWDOWN %d \n", time, task);
	fputs(trace_event_line, trace_event_file);
}

void period_task(int time, int task)
{
	sprintf(trace_event_line, "%d	DEADLINE %d\n", time, task);
	fputs(trace_event_line, trace_event_file);
}

void deadline_task(int time, int task)
{
	//print lines for mark deadline's task
	sprintf(trace_event_line, "%d	UNLOCK %d d\n", time, task);
	fputs(trace_event_line, trace_event_file);
}

void init_trace(int tasks, int duration, char* algoritm)
{
	char l = 'A';
	int i;
	//print lines for header tracer
	/*
	DECIMAL_DIGITS 0
	DURATION  150
	LINE_NAME 0 A
	LINE_NAME 1 B
	LINE_NAME 2 C
	PALETTE Rainbow
	ZOOM_X    3
	ZOOM_Y  24
	COLOR EXEC-E 0 orchid4 */
	sprintf(trace_event_line, "# File make with the Algorithm %s \n", algoritm);
	fputs(trace_event_line, trace_event_file);
	sprintf(trace_event_line, "DECIMAL_DIGITS 0\n");
	fputs(trace_event_line, trace_event_file);
	sprintf(trace_event_line, "DURATION %d\n", duration);
	fputs(trace_event_line, trace_event_file);

	for (i = 0; i < tasks; i++) {
		sprintf(trace_event_line, "LINE_NAME %d %c\n", i, l + i);
		fputs(trace_event_line, trace_event_file);
	}
	sprintf(trace_event_line, "PALETTE Rainbow\n");
	fputs(trace_event_line, trace_event_file);
	sprintf(trace_event_line, "ZOOM_X 4\n");
	fputs(trace_event_line, trace_event_file);
	sprintf(trace_event_line, "ZOOM_Y 16\n");
	fputs(trace_event_line, trace_event_file);
	sprintf(trace_event_line, "COLOR EXEC-E 0 orchid4\n");
	fputs(trace_event_line, trace_event_file);
	sprintf(trace_event_line, "COLOR EXEC-E 1 cyan4\n");
	fputs(trace_event_line, trace_event_file);
}

void create_trace_list(char* path, trace_event* list, int task, int time, char* algoritm)
{
	trace_event *current_event = 0;
	if (open_file(path) == 1) {
		init_trace(task, time, algoritm);

		current_event = list;

		while (current_event != NULL && current_event->time < time) {
			switch (current_event->t_event) {
			case ACTIVATE_TASK:
				active_task((int)current_event->time, current_event->task - 1);
				break;
			case EXECUTE_TASK:
				run_task((int)current_event->time, current_event->task - 1);
				break;
			case SUSPEND_TASK:
				suspend_task((int)current_event->time, current_event->task - 1);
				break;
			case END_TASK:
				finish_task((int)current_event->time, current_event->task - 1);
				break;
			case DEADLINE_TASK:
				deadline_task((int)current_event->time, current_event->task - 1);
				break;
			case PERIOD_TASK:
				period_task((int)current_event->time, current_event->task - 1);
				break;
			case FAIL_TASK:
				fail_task((int)current_event->time, current_event->task - 1);
				break;
			}

			current_event = (trace_event*)(current_event->next);
		}

	}
	close_file();
}