/*   FILE:

	 edf_deadlines_global_sched.c

    DESCRIPTION:

	 Implements Global Multiprocessor real-time scheduler

	 To execute the program:

	    $ ./edf_deadlines_global_sched m st file

	    where

	    "m" indicates the number of identical processors; if m=0, the number of
	     processors is infinite,

	     "st" simulation time; if st=0, then lcm of period values is set as simulation time, and

	    "file" contains the task's parameters, ordered in this fashion
	    (a line per task):

		  period   execution-time   deadline

	  Output:

	     0  indicates that the task set can not be scheduled on m processors

	     n  indicates the number of processor on which the task set can be feasible scheduled


	    See README file for details.

	To compile the program:

	    $ gcc -o edf_deadlines_global_sched edf_deadlines_global_sched.c -lm

    Copyright (C) 2009

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

   LAST REVISION:    June 2009                                                         */



#include "edf_deadlines_global_sched.h"


#define USE_TRACE_FILE
//#define END_ON_MISS_DEADLINE

/* system's total utilization  */


int start_edf_deadline_main(ALGORITHM_PARAMS parameters)
{

	task_set_t *t = NULL; /* Head of task set's list */
	processor_t *p = NULL; /* Head of processor's list */
	sched_event_t *event = NULL; /* Head of scheduling events list */
	sched_event_t *missed_deadlines = NULL; /* Head of missed deadlines events list */

	int n; /* Number of tasks */
	//int m; /* Number of processors */
	double current_time, max_time;
	float util;


	FILE *in_file; /* Input file */

	int no_proc, i;
	int event_id = 0, deadln_miss_id = 0;
	char line[80]; /* Input line */
	float period, wcet, deadline;
	task_set_t new_task; /* List pointers */
	task_set_t *task_to_execute, *task_in_processor, *task_in_event, *preemptable_task;
	processor_t new_processor;
	sched_event_t new_event;
	processor_t *current_processor, *preemptable_processor;

	int no_task = 0;
#ifdef USE_TRACE_FILE
	////////////// tracer
	int file_id = 0;
	char file_trace[255];
	char basename_trace[255];

	trace_event new_trace_event;
	new_trace_event.next = NULL;
	///////////////////////////////
#endif

	///////////////////////////////////////// checking params
	//if (argc != 3) {
	//	LOG( "\nYou must supply the number of processors, simulation time (0 = lcm) and a file name with the task set parameters (see README file for details)\n");
	//	return -1;
	//}

	no_proc = parameters.processor;//atoi(argv[argid]);
	if (no_proc <= 0) {
		LOG( "Error: number of processor must be > 0 (%s)\n", no_proc);
		return -1;
	}

	max_time = (double) parameters.time;//atoi(argv[argid + 1]);
	if (max_time < 0) {
		LOG( "Error: simulation time must be >= 0 (%s)\n", max_time);
		return -1;
	}

	//in_file = fopen(argv[argid + 2], "r");
	in_file = fopen(parameters.data, "r");
	if (in_file == NULL) {
		LOG( "Error:Unable to open %s file\n", parameters.data);
		return -1;
	}
	/////////////////////////////////////////////////////////////////////////////////////


#ifdef USE_TRACE_FILE
	//get basename used for trace file output
	get_basename(parameters.data, &basename_trace[0]);
#endif

	
	/// Create processor's list
	for (i = 0; i < no_proc; i++) {
		new_processor.id = i;
		new_processor.status = PROCESSOR_IDLE;
		new_processor.u = 0.0;
		new_processor.task = NULL;
		p = add_processor_list(p, new_processor);
	}

	//* Read in data
	n = 0;
	current_time = 0.0;
	event_id = 0;
	while (1) {
		if (fgets(line, sizeof(line), in_file) == NULL)
			break;

		/* read task set parameters from file */
		if (line[0] != '#') {
			sscanf(line, "%f%f%f", &period, &wcet, &deadline);
			/* set task parameters for first activation */
			new_task.id = ++n;
			new_task.t = (double) period;
			new_task.c = (double) wcet;
			new_task.d = (double) deadline;
			new_task.r = current_time;
			new_task.res = NULL;
			new_task.deadline = new_task.r + new_task.d;
			new_task.cet = 0.0;
			new_task.e = -1;
			new_task.p = set_task_edf_deadline_priority(&new_task);
			new_task.state = TASK_READY;
			t = add_task_list_p_sorted(t, new_task);
			
			task_in_event = pointer_to_task(t, new_task.id);
			
			//* add event (task release) to sched events list
			new_event.id = event_id++;
			new_event.t_event = (int) SCHEDE_RELEASE;
			// event.time = task.f;            /* start execution at 0 + task phase */
			new_event.time = current_time;
			new_event.task = task_in_event;
			new_event.p = task_in_event -> p;
			new_event.processor = NULL;
			event = add_sched_event_list_time_sorted(event, new_event);

			no_task++;
		}
	}

	if (!n) {
		LOG( "Error: empty file %s\n", parameters.data);
		return -1;
	}

	//* Get System's Utilization
	util = 0.0;
	task_in_event = t;
	while (task_in_event) {
		util += (float) (task_in_event -> c / task_in_event -> t); /* Ui = Ci/Ti  */
		// LOG("u(%d) = %f\n", task_in_event -> id, (float) (task_in_event -> c/task_in_event -> t));
		task_in_event = (task_set_t *) task_in_event -> next;
	}
	// LOG("\nTotal utilization of task set = %f\n", util);
	// LOG("\nTotal utilization of multiprocessor system = %f\n\n", util/no_proc);


	if (max_time == 0.0) {
		// LOG("Calculating simulation time\n");
		max_time = lcm(t);
		//LOG("Simulation time = [0, %.2f]\n", max_time);
	}

#ifdef USE_TRACE_FILE
	//////////////////////////////
	task_in_event = t;
	while (task_in_event) {

		// add task deadline
		new_trace_event.time = current_time + task_in_event->d;
		new_trace_event.task = task_in_event->id;
		new_trace_event.t_event = DEADLINE_TASK;
		//add finish task
		current_processor = p;
		while (current_processor) {
			/*(trace_event *)*/ current_processor->tracer = (trace_event *) add_trace_event((trace_event *) current_processor->tracer, new_trace_event);
			current_processor = (processor_t *) current_processor->next;
		}
		task_in_event = (task_set_t *) task_in_event -> next;
	}
	for (current_time = 1; current_time <= max_time; current_time++) {
		task_in_event = t;
		while (task_in_event) {
			if (((int) (current_time) % (int) (task_in_event -> t)) == 0) {
				// add task period
				new_trace_event.time = (int) current_time;
				new_trace_event.task = task_in_event->id;
				new_trace_event.t_event = PERIOD_TASK;
				//add finish task
				current_processor = p;
				while (current_processor) {
					/*(trace_event *) */current_processor->tracer = (trace_event *) add_trace_event((trace_event *) current_processor->tracer, new_trace_event);
					current_processor = (processor_t *) current_processor->next;
				}
				// add task deadline
				new_trace_event.time = current_time + task_in_event-> d;
				new_trace_event.task = task_in_event->id;
				new_trace_event.t_event = DEADLINE_TASK;
				//add finish task
				current_processor = p;
				while (current_processor) {
					/*(trace_event *)*/ current_processor->tracer = (trace_event *) add_trace_event((trace_event *) current_processor->tracer, new_trace_event);
					current_processor = (processor_t *) current_processor->next;
				}
			}

			task_in_event = (task_set_t *) task_in_event -> next;
		}
	}
	///////////////////////////////////////
#endif

	/*
	   Start scheduling task set on no_proc processors
	 */
	if (event) {
		task_in_event = event -> task;
		current_time = event -> time;
	}

	while ((event) && (current_time <= max_time)) {

		//if(previous_time != current_time)
		LOG("\n================= Time %.2f ==============\n", current_time);
		switch (event->t_event) {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//										TASK START/RESUME
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case SCHEDE_RELEASE: /* new task is released, try to assign it to a processor */
			LOG("Event: Release task %d\n", task_in_event->id);
#ifdef USE_TRACE_FILE
			////////////////////// print activate task
			current_processor = p;
			while (current_processor) {
				new_trace_event.task = task_in_event->id;
				new_trace_event.time = (int) current_time;
				new_trace_event.t_event = ACTIVATE_TASK;
				/*(trace_event *)*/ current_processor->tracer = (trace_event *) add_trace_event((trace_event *) current_processor->tracer, new_trace_event);
				current_processor = (processor_t *) current_processor->next;
			}
			///////////////////////////////////////
#endif

			// search an IDLE processor
			current_processor = p;
			task_in_processor = current_processor -> task;
			while ((current_processor) && (current_processor -> status != PROCESSOR_IDLE)) {
				current_processor = (processor_t *) current_processor -> next;
				if (current_processor)
					task_in_processor = current_processor -> task;
			}
			///////////////////////////////////////
			//if IDLE processor found
			if ((current_processor) && (current_processor->status == PROCESSOR_IDLE)) {
				// idle processors found	Active the current task	/////////////////////////////////
				// add FINISH event for task	/////////////////////////////////////////////////////
				new_event.id = event_id++;
				new_event.t_event = (int) SCHEDE_FINISH;
				new_event.time = current_time + task_in_event -> c;
				new_event.task = task_in_event;
				new_event.p = event -> p;
				new_event.processor = current_processor;
				event = add_sched_event_list_time_sorted(event, new_event);
				/////////////////////////////////////////////////////////////////////////////////////
				task_in_event -> e = current_time;

				// set Task to process task is now running
				assign_task_to_processor(current_processor, task_in_event, current_time);
				LOG("|_ Task %d is now executing on processor %d\n", task_in_event->id, current_processor->id);

#ifdef USE_TRACE_FILE				
				/// Print task execute
				new_trace_event.task = new_event.task->id;
				new_trace_event.time = (int) current_time;
				new_trace_event.t_event = EXECUTE_TASK;
				/*(trace_event *) */current_processor->tracer = (trace_event *) add_trace_event((trace_event *) current_processor->tracer, new_trace_event);
				//////////////////////////////////////////////
#endif
				//print task active
				// getchar();

			} else {
				// NO IDLE processor found

				// Search for one task in processor less prioritary ////////////////////////////////////////////////////////////
				preemptable_task = NULL;
				current_processor = p;
				task_in_processor = current_processor -> task;
				while (current_processor) {
					if ((current_processor->status == PROCESSOR_BUSY) && (event -> p < task_in_processor -> p)) {
						if (!preemptable_task) {
							preemptable_task = current_processor -> task;
							preemptable_processor = current_processor;
						} else {
							if (preemptable_task -> p < task_in_processor -> p) {
								preemptable_task = task_in_processor;
								preemptable_processor = current_processor;
							}
						}
					}
					current_processor = (processor_t *) current_processor -> next;
					if (current_processor) {
						task_in_processor = current_processor -> task;
					}
				}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// IF one task less prioritary found
				if (preemptable_task) {

					current_processor = preemptable_processor;

					/// Update information for task in processor before paused
					task_in_processor = preemptable_task;
					new_event.time = task_in_processor -> e + task_in_processor -> c - task_in_processor -> cet;
					task_in_processor -> cet += current_time - task_in_processor -> e;
					
					task_in_processor -> state = TASK_READY;
					/* delerte finish event of preempted task */
					// LOG("delete finish event for preempted task\n");
					LOG("|_ Removing task %d, from processor %d\n", task_in_processor->id, current_processor->id);

					// Delete schedule FINISH event	/////////////////////////////////
					new_event.task = task_in_processor;
					new_event.t_event = SCHEDE_FINISH;
					if (is_event_in_list(event, &new_event, &i)) {
						event = del_sched_event_from_list(event, i);
					
					}

#ifdef USE_TRACE_FILE
					//////////////////////////////// add suspend task
					new_trace_event.task = task_in_processor->id;
					new_trace_event.time = (int) current_time;
					new_trace_event.t_event = SUSPEND_TASK;
					/*(trace_event *)*/ current_processor->tracer =(trace_event *)  add_trace_event((trace_event *) current_processor->tracer, new_trace_event);
					//////////////////////////////////////////////////
#endif

					// ADD schedule FINISH event for new task	/////////////////////////////////
					new_event.id = event_id++;
					new_event.t_event = (int) SCHEDE_FINISH;
					new_event.time = current_time + task_in_event -> c;
					new_event.task = task_in_event;
					new_event.p = event -> p;
					new_event.processor = current_processor;
					event = add_sched_event_list_time_sorted(event, new_event);
					//LOG("\nDefining new event FINISH task %d at time %.2f\n", task_in_event -> id, new_event.time);

#ifdef USE_TRACE_FILE
					//////////////////////////// deadline task and execute task
					new_trace_event.task = task_in_event->id;
					new_trace_event.time = (int) current_time;
					new_trace_event.t_event = EXECUTE_TASK;
					/*(trace_event *)*/ current_processor->tracer = (trace_event *) add_trace_event((trace_event *) current_processor->tracer, new_trace_event);
					////////////////////////////////////////////////////
#endif
					// Asign new task to processor
					assign_task_to_processor(current_processor, task_in_event, current_time);

					LOG("|_ Task %d is now executing on processor %d\n", task_in_event->id, current_processor->id);


				} else { // Task less prioritary NOT FOUND, set this task in ready state, set execute time to 0
					task_in_event -> state = (int) TASK_READY;
					task_in_event -> cet = 0.0;
				}
			}
			break;
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//										TASK END
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case SCHEDE_FINISH:
			
			current_processor = event -> processor;
			LOG("Event: Finish task %d\n", task_in_event->id);
			/* check if task finished by its deadline */
			if (current_time > task_in_event -> deadline) { /* deadline miseed, thus generate event */

				LOG("|_ **Task deadline missed\n");
				//print task fail
				new_event.id = deadln_miss_id++;
				new_event.t_event = (int) SCHEDE_DEADLN_MISS;
				new_event.time = current_time;
				new_event.p = 0;
				new_event.task = task_in_event;
				missed_deadlines = add_sched_event_list_time_sorted(missed_deadlines, new_event);

#ifdef USE_TRACE_FILE
				/////////////////////////////////// add tracer fail task
				new_trace_event.task = task_in_event -> id;
				new_trace_event.time = (int) new_event.time;
				new_trace_event.t_event = FAIL_TASK;
				/*(trace_event *)*/ current_processor->tracer = (trace_event *) add_trace_event((trace_event *) current_processor->tracer, new_trace_event);
				/////////////////////////////////////////////////////

#ifdef END_ON_MISS_DEADLINE
				///////////////////// print trace to file
				current_processor = p;
				while (current_processor) {
					file_id++;
					//print_trace_list(current_processor->tracer);
					sprintf(file_trace, "%s_p%d.ktr", &basename_trace[0], file_id);
					create_trace_list(file_trace, current_processor->tracer, no_task, current_time, (char *) "EDF with Deadlines");
					current_processor = current_processor->next;

				}
				current_processor = event -> processor;

#endif
				////////////////////////////////////////////////////////
#endif
#ifdef END_ON_MISS_DEADLINE
				LOG("Not Scheduled by edf: %d", 0);
				return 0;
#endif
			}
			/* set task parameters for next activation */
			task_in_event->r += task_in_event -> t;
			task_in_event->deadline = task_in_event -> r + task_in_event -> d;
			task_in_event->cet = 0.0;
			task_in_event->e = -1;
			task_in_event->state = (int) TASK_READY;
			task_in_event->p = set_task_edf_priority(task_in_event);
			/* add event (task release) for next task activation (since current activation has finished */
			new_event.id = event_id++;
			new_event.t_event = (int) SCHEDE_RELEASE;
			new_event.time = task_in_event -> r;
			new_event.task = task_in_event;
			new_event.p = task_in_event -> p;
			new_event.processor = NULL;
			event = add_sched_event_list_time_sorted(event, new_event);

			//print new activate
			//LOG("\nDefining new event RELEASE task %d at time %.2f\n", task_in_event -> id, new_event.time);
			// getchar();

#ifdef USE_TRACE_FILE
			////////////////////////////// add end task on tracer
			new_trace_event.task = task_in_event->id;
			new_trace_event.time = (int) current_time;
			new_trace_event.t_event = END_TASK;
			/*(trace_event *)*/ current_processor->tracer = (trace_event *) add_trace_event((trace_event *) current_processor->tracer, new_trace_event);
			//////////////////////////////
#endif


			//LOG("check if there is a task in ready state elegible to execute at time %.2f\n", current_time);
			task_to_execute = find_task_to_execute(t, event -> time);
			if (task_to_execute) {

				//print task to execute
				//LOG("task %d found with release time %.2f and cet %.2f to be executed\n", task_to_execute -> id, task_to_execute -> r, task_to_execute -> cet);
				// getchar();
				/* check if the release event for this task is in event list (i.e., if release time = current_time */
				if (task_to_execute -> r == current_time) {
					// LOG("checking for release event for task %d in event list at time %.2f\n", task_to_execute -> id, current_time);
					new_event.time = current_time;
					new_event.task = task_to_execute;
					new_event.t_event = SCHEDE_RELEASE;
					if (is_event_in_list(event, &new_event, &i)) {
						event = del_sched_event_from_list(event, i);
					}
				}

				new_event.id = event_id++;
				new_event.t_event = (int) SCHEDE_FINISH;
				new_event.time = current_time + (task_to_execute -> c - task_to_execute -> cet);
				new_event.task = task_to_execute;
				new_event.p = task_to_execute -> p;
				new_event.processor = current_processor;
				event = add_sched_event_list_time_sorted(event, new_event);
				// LOG("\nDefining new event FINISH task %d at time %.2f\n", task_to_execute -> id, new_event.time);
				// getchar();
				assign_task_to_processor(current_processor, task_to_execute, current_time);
				task_to_execute -> e = current_time;
				task_to_execute -> state = (int) TASK_RUNNING;
				LOG("|_ Task %d is now executing on processor %d\n", task_to_execute->id, current_processor->id);

#ifdef USE_TRACE_FILE
				/////////////////////////////////// add tracer deadline and execute
				new_trace_event.task = task_to_execute->id;
				new_trace_event.time = (int) current_time;
				new_trace_event.t_event = EXECUTE_TASK;
				/*(trace_event *)*/ current_processor->tracer = (trace_event *) add_trace_event((trace_event *) current_processor->tracer, new_trace_event);
				///////////////////////////////////
#endif
				// getchar();

			} else {
				/* no task to execute found, set processor to idle state */
				LOG("|_ No task in wait queue found, set processor %d to idle state\n", current_processor -> id);
				current_processor -> status = PROCESSOR_IDLE;
				current_processor -> task = NULL;
			}
			break;
		}
		/*
			  if(event->event >= SCHEDE_RELEASE && event->event <= SCHEDE_DEADLN_MISS)
				eventLog = add_sched_event_list(eventLog, *event);*/
		event = del_sched_event_head_list(event);
		if (event) {
			task_in_event = event -> task;
			current_time = event -> time;
		}
	}

	LOG("\nScheduled by edf using: \n\nNo. of processors: %d", no_proc);
	LOG("\nSimulation time = [0, %.2f]\n", max_time);
#ifdef USE_TRACE_FILE
	///////////////////// print trace to file
	current_processor = p;
	while (current_processor) {
		file_id++;
		LOG("\nProcessor %d: U = %f", file_id, current_processor->u);
		//print_trace_list((trace_event *)current_processor->tracer);
		sprintf(file_trace, "%s_p%d.ktr", &basename_trace[0], file_id);
		create_trace_list(file_trace, (trace_event *) current_processor->tracer, no_task, (int) max_time, (char *) "EDF with Deadlines");
		current_processor = (processor_t *) current_processor->next;

	}
	////////////////////////////////////////////////////////
#endif

	//LOG("Scheduling activities finished at current time = %.2f\n", current_time);
	return(no_proc);
}


void print_edf_deadline_usage()
{
	LOG( "\n EDF Deadlines params:");
	LOG( "\n   processors time tasks.txt\n");
}