//File with the base code common for all the partials functions or methods that be added
//This file will be included in each version from rm with each function partial

#include <stdlib.h>

//function input to run the scheduler
static int SimulatorCmd(ClientData clientData, Tcl_CmdDeleteProc* proc, int objc, Tcl_Obj* const objv[]) 
{
	int res = TCL_OK;
	char* strings[255];
	int t = 0;
	ALGORITHM_PARAMS parameters;

	DBG("\n cleaning log...");
	init_logger();
	
//convert the list of arguments to C strings
	//DBG("\n called with %d arguments", objc);
	for(t=0;t<objc;t++)
	{
		//DBG("\n%d: %s",t, (*objv[t]).bytes);
		strings[t] = (*objv[t]).bytes;
	}
	//DBG("\n");
		
	//USE ALWAYS PARTIAL MODE 
	parameters.algorithm	= RM;
	parameters.mode			= MODE_PARTIAL;
	//SHOULD BE USED ONLY ONE PARTIAL FUNCTION, NOT SPECIFY IN THE PARAMETERS
	// parameters.partial_func = RM_PARTIAL_RBOUND_MP_NFR;
	
	parameters.processor	= atoi(strings[2]);
	parameters.time			= atoi(strings[3]);
	strcpy(parameters.data, strings[4]);

	parameters.param_count = objc - 2;
	
	res = start_rm_main(parameters);
	//res = simulator_main(objc, strings);

	DBG("\n End SimulatorCmd: %d",res);
	return res;
}

/*
typedef enum
{
	PARAM_MODE=0,
	PARAM_NOPROC,
	PARAM_MAXTIME,
	PARAM_FILE,
	PARAM_COUNT,
}RM_PARAMS;
*/

#ifdef USE_THREAD

pthread_mutex_t rm_mutex; 
int rm_active_threads;

typedef struct {
	int mode;
	int no_proc;
	double max_time;
	task_set_t *task;
	char outfile[255];
}rm_thread_args;

void* thread_start_rm(void* params)
{
	DBG("\ncreating new thread ...");
	rm_thread_args* rm_params = (rm_thread_args*)params;
	int mode		= rm_params->mode;
	int no_proc		= rm_params->no_proc;
	double max_time = rm_params->max_time;
	task_set_t *t	= rm_params->task;
	char* outfile	= rm_params->outfile;

	start_rm(mode, no_proc, max_time, t, outfile);
	DBG("\nEnd thread.");
	free(rm_params);
}
#endif
int start_rm(int mode, int no_proc, double max_time, task_set_t *t, char* outfile)
{
	processor_t *p = NULL; /* Head of processor's list */
	sched_event_t *event_list = NULL; /* Head of scheduling events list */
	sched_event_t *missed_deadlines = NULL; /* Head of missed deadlines events list */

	
//	int mode;
//	int n; /* Number of tasks */
	//int m; /* Number of processors */
	double current_time;
	float util; /* system's total utilization  */
	int no_task;
	

	int i;//, task_not_assigned;
	int event_id = 0, deadln_miss_id = 0;
	//char line[80]; /* Input line */
//	float period, wcet, phase;
	task_set_t *task_to_execute, *task_in_processor, *task_in_event, *preemptable_task;
	processor_t new_processor;
	sched_event_t new_event;
	processor_t *current_processor, *preemptable_processor;

#ifdef USE_RESOURCES
	int available_resources = 0;
	list_resource_t new_resource;
	list_resource_t* resource_list = NULL;
	task_resource_t* current_task_res = NULL;
#endif


#ifdef USE_TRACE_FILE
	////////////// tracer
	int file_id = 0;
	char file_trace[255];
	char basename_trace[255];

	trace_event new_trace_event;
	new_trace_event.next = NULL;

	strcpy(basename_trace, outfile);
	///////////////////////////////
#endif

	//DBG("\n start rm simulator");

	
	
	/// Create processor's list
	for (i = 0; i < no_proc; i++) {
		new_processor.id = i;
		new_processor.status = PROCESSOR_IDLE;
		new_processor.u = 0.0;
		new_processor.task = NULL;
		p = add_processor_list(p, new_processor);
	}



	no_task = 0;
	task_to_execute = t;
	while(task_to_execute)
	{
		task_in_event = pointer_to_task(t, task_to_execute->id);
		
		//* add event (task release) to sched events list
		new_event.id = event_id++;
		new_event.t_event = (int) SCHEDE_RELEASE;
		new_event.time = task_to_execute->f;
		new_event.task = task_in_event;
		new_event.p = task_in_event -> p;
		new_event.res_id = 0;
		new_event.processor = NULL;
		event_list = add_sched_event_list_time_sorted(event_list, new_event);

		task_to_execute = (task_set_t*) (task_to_execute->next);
		no_task++;
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
		// LOG("Simulation time = [0, %.2f]\n", max_time);
	}

#ifdef USE_TRACE_FILE
	//// mark deadlines in file trace
	for (current_time = 1; current_time <= max_time; current_time++) {
		task_in_event = t;
		while (task_in_event) {
			if (((int) (current_time) % (int) (task_in_event -> t)) == 0) {
				// add task deadline
				new_trace_event.time = (int) current_time;
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

	///  Start scheduling task set on no_proc processors
	if (event_list) {
		task_in_event = event_list -> task;
		current_time = event_list -> time;
	}

	while ((event_list) && (current_time <= max_time)) {

		//if(previous_time != current_time)
		LOG("\n================= Time %.2f ==============\n", current_time);
		switch (event_list -> t_event) {
#ifdef USE_RESOURCES

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//										RESOURCES EVENTS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case SCHEDE_RELEASE_RES:
		{
			LOG("Event: Release Resource\n");
			//get task using the resource
			task_to_execute = get_task_with_resource((int) (event_list->res_id), resource_list);

			LOG("|_ Task %d request resource %d\n", task_in_event->id, event_list->res_id);
			//if not task using the resource
			if (task_to_execute == 0) {
				LOG("  |_ Resource %d is free assing\n", event_list->res_id);
				// Assing resources to task and schedule event for finish resource
				assing_resource_to_task(event_list->res_id, task_in_event, resource_list);

				// get information about current resource for this task
				current_task_res = get_resource_task(event_list->res_id, task_in_event->res);

				//add finish resource event
				new_event.id = event_id++;
				new_event.t_event = (int) SCHEDE_FINISH_RES;
				new_event.time = current_time + current_task_res -> c;
				new_event.task = task_in_event;
				new_event.res_id = current_task_res -> id;
				new_event.processor = current_processor;
				//////////////////////////////////////////////////////////////////////////////////
				// setup task running information
				current_task_res->e = current_time;
				current_task_res->cet = 0;

				event_list = add_sched_event_list_time_sorted(event_list, new_event);


				//if task with resource is not the same task
			} else if (task_to_execute != task_in_event) {
				LOG("  |_ Resource is currently assigned to %d, changing priority... \n", task_to_execute->id);
				//some task is actually using the resource, change the priority
				push_task_priority(task_to_execute, task_in_event);
				//TODO only saving one list of events
				push_task_stack_events(task_in_event, event_list, current_time);

				current_processor = p;
				//get current resource information
				current_task_res = get_resource_task(event_list->res_id, task_to_execute->res);

				if (task_to_execute->state == TASK_READY) {

					/// Update information for task in processor before paused	/////////////////////////
					task_in_processor = task_in_event;
					//new_event.time = task_in_processor -> e + task_in_processor -> c - task_in_processor -> cet;
					task_in_processor -> cet += current_time - task_in_processor -> e;
					//task keep in ready state
					task_in_processor -> state = TASK_READY;
					////////////////////////////////////////////////////////////////////////////////////

					// Update task resources time utilized
					task_resources_update_executed_time(task_in_processor, current_time, resource_list);


					//backup current event
					new_event = *event_list;
					new_event.next = 0;
					//delete all schedule events for this task
					event_list = del_sched_event_task_from_list(event_list, task_in_processor);
#ifdef USE_TRACE_FILE
					//////////////////////////////// add suspend task
					new_trace_event.task = task_in_processor->id;
					new_trace_event.time = (int) current_time;
					new_trace_event.t_event = SUSPEND_TASK;
					/*(trace_event *)*/ current_processor->tracer = (trace_event *) add_trace_event((trace_event *) current_processor->tracer, new_trace_event);
					//////////////////////////////////////////////////
#endif
					//restore current event
					event_list = add_sched_event_list_time_sorted(event_list, new_event);
					/////////////////////////////////////////////////////////////////////////////////////


					//// ADD schedule SCHEDE_RELEASE event for new task	/////////////////////////////////
					//                   new_event.id = event_id++;
					//                   new_event.t_event = (int) SCHEDE_RELEASE;
					//                   new_event.time = current_time;
					//                   new_event.task = task_to_execute;
					//                   new_event.p = task_to_execute -> p;
					//                   new_event.processor = current_processor;

					//	event_list = add_sched_event_list_time_sorted(event_list, new_event);
					//               /////////////////////////////////////////////////////////////////////////////


					// ADD schedule SUSPEND event for new task	/////////////////////////////////
					new_event.id = event_id++;
					new_event.t_event = (int) SCHEDE_SUSPEND;
					//suspend task one time after finish the current resource
					new_event.time = current_time + current_task_res->c - current_task_res->cet;
					new_event.task = task_to_execute;
					new_event.p = task_to_execute -> p;
					new_event.processor = current_processor;
					event_list = add_sched_event_list_time_sorted(event_list, new_event);
					/////////////////////////////////////////////////////////////////////////////

					// schedule Events for each resource used for task, DONT apply start
					current_task_res = task_to_execute->res;
					while (current_task_res) {
						//dont add release resource event for current release resource
						if (event_list->res_id != current_task_res->id) {
							//check if task is already has the resources
							task_in_processor = get_task_with_resource(current_task_res->id, resource_list);

							// if task has the resource, send the release event in this time

							if (task_in_processor == task_to_execute) {
								// add release event for resource in this time
								new_event.time = current_time;
							} else {
								// if none task has the resource, schedule the resource RELEASE	////////////////////
								new_event.time = current_time + current_task_res->f - task_to_execute->cet;
							}
							// add new release resource event
							new_event.id = event_id++;
							new_event.t_event = (int) SCHEDE_RELEASE_RES;
							new_event.task = task_to_execute;
							new_event.p = 0;
							new_event.res_id = current_task_res->id;
							new_event.processor = NULL;
							event_list = add_sched_event_list_time_sorted(event_list, new_event);
						}

						current_task_res = current_task_res->next;
					}
					////////////////////////////////////////////////////////////////////////
					// Asign new task to processor
					task_to_execute->state = TASK_READY;
					assign_task_to_processor(current_processor, task_to_execute, current_time);
					LOG("  |_ Task %d is now executing on processor %d\n", task_to_execute->id, current_processor->id);

#ifdef USE_TRACE_FILE
					//////////////////////////// deadline task and execute task
					new_trace_event.task = task_to_execute->id;
					new_trace_event.time = (int) current_time;
					new_trace_event.t_event = EXECUTE_TASK;
					/*(trace_event *)*/ current_processor->tracer = (trace_event *) add_trace_event((trace_event *) current_processor->tracer, new_trace_event);
					////////////////////////////////////////////////////
#endif

					/*current_processor -> status = PROCESSOR_IDLE;
					current_processor -> task = NULL;*/
				} else {
					//WARNING task should be ready;
					int a = 0; //task_to_execute -> state = TASK_READY;
				}
			} else {
				//this task already has the resourece, should not be requesting the resources again.
				int a = 0;
			}

		}
			break;
		case SCHEDE_FINISH_RES:
		{

			//finish the current resource, update executed time and remove from resource list
			current_task_res = get_resource_task(event_list->res_id, task_in_event->res);
			current_task_res->cet += current_time - current_task_res->e;


			remove_resource_from_task(event_list->res_id, resource_list);

			LOG("Event: Finish Resource %d\n", event_list->res_id);
		}
			break;

		case SCHEDE_SUSPEND:
		{
			LOG("Event: Suspend Task %d\n", task_in_event->id);
			current_processor = event_list -> processor;

			if (popd_task_priority(task_in_event)) {
				LOG("|_ Priority recovered\n");
			}

			// check if task deadline has missing*/
			if (current_time > task_in_event -> d) { /* deadline missed, thus generate event */

				LOG("|_ ** Task deadline missed\n");
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
					create_trace_list(file_trace, current_processor->tracer, no_task, current_time, (char *) "RM");
					current_processor = current_processor->next;

				}
				current_processor = event_list -> processor;

#endif
				////////////////////////////////////////////////////////
#endif

#ifdef END_ON_MISS_DEADLINE
				LOG("Not Scheduled by rm: %d", 0);
				return 0;
#endif
			}// end deadline missed

			// Update time executed and return task to ready state
			task_in_event -> cet += current_time - task_in_event->e;
			task_in_event -> state = (int) TASK_READY;

			// Update task resources time utilized
			task_resources_update_executed_time(task_in_event, current_time, resource_list);

#ifdef USE_TRACE_FILE
			//////////////////////////////// add suspend task
			new_trace_event.task = task_in_event->id;
			new_trace_event.time = (int) current_time;
			new_trace_event.t_event = SUSPEND_TASK;
			/*(trace_event *)*/ current_processor->tracer = (trace_event *) add_trace_event((trace_event *) current_processor->tracer, new_trace_event);
			//////////////////////////////////////////////////
#endif

			//// Delete schedule FINISH event	/////////////////////////////////
			//                    new_event.task = task_in_processor;
			//                    new_event.t_event = SCHEDE_FINISH;
			//                    if (is_event_in_list(event_list, &new_event, &i)) {
			//                        event_list = del_sched_event_from_list(event_list, i);
			//                    }
			//	/////////////////////////////////////////////////////////////////
			//backup current event
			new_event = *event_list;
			new_event.next = 0;
			//#ifdef USE_RESOURCES
			//delete all schedule Resource events for this task
			event_list = del_sched_event_task_from_list(event_list, task_in_event);
			//#endif

			// add dummy value for delete on finish
			new_event.id = event_id++;
			new_event.t_event = (int) SCHEDE_SUSPEND;
			new_event.time = (int) current_time;
			new_event.processor = current_processor;
			event_list = add_sched_event_list_time_sorted(event_list, new_event);
			/////////////////////////////////////////////////////////////////////////////////////



			// if exists more events
			if (event_list) {
				// search for new task to execute, if two o more task has the same priority select the deep priority stack
				task_to_execute = find_task_to_execute(t, event_list -> time);


				if (task_to_execute) {
					//print task to execute
					/* check if the release event for this task is in event list (i.e., if release time = current_time */
					if (task_to_execute -> r == current_time) {
						// LOG("checking for release event for task %d in event list at time %.2f\n", task_to_execute -> id, current_time);
						new_event.time = current_time;
						new_event.task = task_to_execute;
						new_event.t_event = SCHEDE_RELEASE;
						if (is_event_in_list(event_list, &new_event, &i)) {
							event_list = del_sched_event_from_list(event_list, i);
						}
					}

					// if exists, recover the stack events saved
					event_list = pop_task_stack_events(task_to_execute, event_list, current_time, &event_id);

					//// add finish event and assing new task to processor
					//	new_event.id = event_id++;
					//	new_event.t_event = (int) SCHEDE_FINISH;
					//	new_event.time = current_time + (task_to_execute -> c - task_to_execute -> cet);
					//	new_event.task = task_to_execute;
					//	new_event.p = task_to_execute -> p;
					//	new_event.processor = current_processor;
					//	event_list = add_sched_event_list_time_sorted(event_list, new_event);
					//
					assign_task_to_processor(current_processor, task_to_execute, current_time);

					LOG("|_ Task %d is now executing on processor %d\n", task_to_execute->id, current_processor->id);
#ifdef USE_TRACE_FILE
					/////////////////////////////////// add tracer deadline and execute
					new_trace_event.task = task_to_execute->id;
					new_trace_event.time = (int) current_time;
					new_trace_event.t_event = EXECUTE_TASK;
					/*(trace_event *)*/ current_processor->tracer = (trace_event *) add_trace_event((trace_event *) current_processor->tracer, new_trace_event);
					///////////////////////////////////
#endif
				}// end task to execute found
			} //end if exist more events
		}/// END SUSPEND_TASK
		break;
#endif
		


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
				new_event.p = event_list -> p;
				new_event.processor = current_processor;
				event_list = add_sched_event_list_time_sorted(event_list, new_event);
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

#ifdef USE_RESOURCES
				// schedule Events for each resource used for task, DONT apply start
				current_task_res = task_in_event->res;
				while (current_task_res) {
					new_event.id = event_id++;
					new_event.t_event = (int) SCHEDE_RELEASE_RES;
					new_event.time = current_time + current_task_res->f;
					new_event.task = task_in_event;
					new_event.p = 0;
					new_event.res_id = current_task_res->id;
					new_event.processor = NULL;
					event_list = add_sched_event_list_time_sorted(event_list, new_event);

					current_task_res = current_task_res->next;
				}
				////////////////////////////////////////////////////////////////////////
#endif
			} else {
				// NO IDLE processor found

				// Search for one task in processor less prioritary ////////////////////////////////////////////////////////////
				preemptable_task = NULL;
				current_processor = p;
				task_in_processor = current_processor -> task;
				while (current_processor) {
					if ((current_processor -> status == PROCESSOR_BUSY) && (event_list -> p < task_in_processor -> p)) {
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
					task_in_processor -> state = TASK_READY; //task keep in ready state

#ifdef USE_RESOURCES
					// Update task resources time utilized
					task_resources_update_executed_time(task_in_processor, current_time, resource_list);
#endif

					LOG("|_ Removing task %d, from processor %d\n", task_in_processor->id, current_processor->id);

					// Delete schedule FINISH event	/////////////////////////////////
					new_event.task = task_in_processor;
					new_event.t_event = SCHEDE_FINISH;
					if (is_event_in_list(event_list, &new_event, &i)) {
						event_list = del_sched_event_from_list(event_list, i);
					}
					/////////////////////////////////////////////////////////////////
#ifdef USE_RESOURCES
					//delete all schedule Resource events for this task
					event_list = del_sched_event_task_resource_from_list(event_list, task_in_processor);
#endif

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
					new_event.p = task_in_event -> p; //changed from event_list->p
					new_event.processor = current_processor;
					event_list = add_sched_event_list_time_sorted(event_list, new_event);
					/////////////////////////////////////////////////////////////////////////////

#ifdef USE_RESOURCES
					// schedule Events for each resource used for task, DONT apply start
					current_task_res = task_in_event->res;
					while (current_task_res) {
						new_event.id = event_id++;
						new_event.t_event = (int) SCHEDE_RELEASE_RES;
						new_event.time = current_time + current_task_res->f;
						new_event.task = task_in_event;
						new_event.p = 0;
						new_event.res_id = current_task_res->id;
						new_event.processor = NULL;
						event_list = add_sched_event_list_time_sorted(event_list, new_event);

						current_task_res = current_task_res->next;
					}
					////////////////////////////////////////////////////////////////////////
#endif
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
			current_processor = event_list -> processor;

			LOG("Event: Finish task %d\n", task_in_event->id);

			popd_task_priority(task_in_event);
			// check if task finished by its deadline */
			if (current_time > task_in_event -> d) { /* deadline miseed, thus generate event */

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
					create_trace_list(file_trace, current_processor->tracer, no_task, current_time, (char *) "RM");
			common_rm_global_sched		current_processor = current_processor->next;

				}
				current_processor = event_list -> processor;

#endif
				////////////////////////////////////////////////////////
#endif
#ifdef END_ON_MISS_DEADLINE
				LOG("Not Scheduled by rm: %d", 0);
				return 0;
#endif
			}
			/* set task parameters for next activation */
			task_in_event -> r += task_in_event -> t;
			task_in_event -> d = task_in_event -> r + task_in_event -> t;
			task_in_event -> cet = 0.0;
			task_in_event -> e = -1;
			task_in_event -> state = (int) TASK_READY;
			/* add event (task release) for next task activation (since current activation has finished */
			new_event.id = event_id++;
			new_event.t_event = (int) SCHEDE_RELEASE;
			new_event.time = task_in_event -> r;
			new_event.task = task_in_event;
			new_event.p = task_in_event -> p;
			new_event.processor = NULL;
			event_list = add_sched_event_list_time_sorted(event_list, new_event);
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

#ifdef USE_RESOURCES
			remove_resources_from_task(task_in_event, resource_list);
#endif

			//LOG("check if there is a task in ready state elegible to execute at time %.2f\n", current_time);
			task_to_execute = find_task_to_execute(t, event_list -> time);

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
					if (is_event_in_list(event_list, &new_event, &i)) {
						event_list = del_sched_event_from_list(event_list, i);
					}
				}

				new_event.id = event_id++;
				new_event.t_event = (int) SCHEDE_FINISH;
				new_event.time = current_time + (task_to_execute -> c - task_to_execute -> cet);
				new_event.task = task_to_execute;
				new_event.p = task_to_execute -> p;
				new_event.processor = current_processor;
				event_list = add_sched_event_list_time_sorted(event_list, new_event);
				// LOG("\nDefining new event FINISH task %d at time %.2f\n", task_to_execute -> id, new_event.time);
				// getchar();
				assign_task_to_processor(current_processor, task_to_execute, current_time);
				LOG("|_ Task %d is now executing on processor %d\n", task_to_execute->id, current_processor->id);

				task_to_execute -> e = current_time;
				task_to_execute -> state = (int) TASK_RUNNING;
				//LOG("task %d assigned to processor %d\n", task_to_execute -> id, current_processor -> id);

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

		event_list = del_sched_event_head_list(event_list);
		if (event_list) {
			//previous_time = current_time;
			task_in_event = event_list -> task;
			current_time = event_list -> time;
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
		create_trace_list(file_trace, (trace_event *) current_processor->tracer, no_task, (int) max_time, (char *) "RM");
		current_processor = (processor_t *) current_processor->next;

	}
	////////////////////////////////////////////////////////
#endif
//common_rm_global_sched
#ifdef USE_THREAD
	pthread_mutex_lock(&rm_mutex); 
		rm_active_threads--;
	pthread_mutex_unlock(&rm_mutex); 
#endif
	//LOG("Scheduling activities finished at current time = %.2f\n", current_time);
	return(no_proc);

}


int start_rm_main(ALGORITHM_PARAMS parameters)
{
#ifdef USE_THREAD
	pthread_t thread_task;
	rm_thread_args* args;
#endif
	sched_event_t new_event;
	task_set_t *t = NULL; /* Head of task set's list */
	task_set_t *current_task = NULL; /* Head of task set's list */
	task_set_t new_task; /* List pointers */
	processor_t* list, *current_processor;


	char line[255];
	char basename_trace[255];
	char partialname[255];

	int res;
	int n, i;
	ALGORITHM_MODE mode;
	int no_proc, no_task;
	int event_id;
	double max_time;
	float period, wcet, phase;

	FILE *in_file; /* Input file */

	/////////////////////////////////////// checking params
	/*if (parameters.param_count != PARAM_COUNT) {
		LOG( "\n You must supply the number of processors, simulation time (0 = lcm) and a file name with the task set parameters (see README file for details)\n");
		return -1;
	}*/

	mode = parameters.mode;//atoi(argv[argid+PARAM_MODE]);
	if (mode < 0 || mode >= MODE_COUNT) {
		LOG( "Error: invalid mode, use 0 for global or 1 for partial %d\n", mode);
		return -1;
	}

	no_proc = parameters.processor;//atoi(argv[argid+PARAM_NOPROC]);
	if (no_proc <= 0) {
		LOG( "Error: number of processor must be > 0 (%s)\n", no_proc);	
		return -1;
	}

	max_time = (double) parameters.time;//atoi(argv[argid + PARAM_MAXTIME]);
	if (max_time < 0) {
		LOG( "Error: simulation time must be >= 0 (%s)\n", max_time); //argv[argid + PARAM_MAXTIME]);
		return -1;
	}

	//in_file = fopen(argv[argid + PARAM_FILE], "r");
	in_file = fopen(parameters.data, "r");
	if (in_file == NULL) {
		LOG( "Error: Unable to open %s file\n", parameters.data);//argv[argid + PARAM_FILE]);
		return -1;
	}
	/////////////////////////////////////////////////////////////////////////////////////

#ifdef USE_TRACE_FILE
	//get basename used for trace file output
	//get_basename(argv[argid + PARAM_FILE], &basename_trace[0]);
	get_basename(parameters.data, &basename_trace[0]);
#endif

	no_task = 0;
	
	if(mode == MODE_GLOBAL)	//use global mode
	{
		DBG("MODE_GLOBAL");
		//* Read in data
		n = 0;
		event_id = 0;
		while (1) {
			if (fgets(line, sizeof(line), in_file) == NULL)
				break;


			//* read task set parameters from file
			if (line[0] != '#') {
				sscanf(line, "%f%f%f", &period, &wcet, &phase);
				//* set task parameters for first activation
				new_task.id = ++n;
				new_task.t = (double) period;
				new_task.c = (double) wcet;
				new_task.f = (double) phase;
				new_task.r = 0.0;
				new_task.res = NULL;
				new_task.d = new_task.r + new_task.t;
				new_task.cet = 0.0;
				new_task.e = -1;
				new_task.p = set_task_rm_priority(&new_task);
				new_task.state = TASK_READY;
				new_task.se = 0;

	#ifdef USE_RESOURCES
				/// load resource info for current task
				new_task.res = NULL;
				resource_list = load_resource_file(argv[4], &new_task, resource_list);
				
				if (!resource_list) {
					LOG( "Error: while loading resource file\n");
					return -1;
				}
	#endif

				//add task to task list
				t = add_task_list_p_sorted(t, new_task);
				no_task++;
			}
		}

		if (!n) {
			//LOG( "Error: empty file %s\n", argv[argid + PARAM_FILE]);
			LOG( "Error: empty file %s\n", parameters.data);
			return -1;
		}


		res = start_rm(mode,no_proc, max_time, t, basename_trace);

	}
	else if(mode == MODE_PARTIAL)		//partial mode
	{
		DBG("\nMODE_PARTIAL");
#ifdef USE_THREAD
		pthread_mutex_init (&rm_mutex, NULL); 
		rm_active_threads = 0;
#endif
		res = 0;
		list = NULL;
		
		DBG("\ncalling to partial function for %d processors", no_proc);
		list = partial_function(list, no_proc, parameters.data);
		DBG("\nend partial function");
/* no seleccionar la funcion parcial.
		switch(parameters.partial_func)
		{
			case RM_PARTIAL_NF_LL:
				//list = start_rm_nf_ll(1, argv[argid + PARAM_FILE]);
				list = start_rm_nf_ll(1, parameters.data);
			break;
			case RM_PARTIAL_BF_LL:
				list = start_rm_bf_ll(1, parameters.data);
			break;
			case RM_PARTIAL_FF_LL:
				list = start_rm_ff_ll(1, parameters.data);
			break;
			case RM_PARTIAL_WF_LL:
				list = start_rm_wf_ll(1, parameters.data);
			break;

			
			case RM_PARTIAL_FF_DU_UO:
				list = start_rm_ff_du_uo(1, parameters.data);
			break;
			case RM_PARTIAL_FF_IP:
				list = start_rm_ff_ip(1, parameters.data);
			break;
			case RM_PARTIAL_GT:
				list = start_rm_gt(1, parameters.data);
			break;
			case RM_PARTIAL_NF_IP:
				list = start_rm_nf_ip(1, parameters.data);
			break;
			case RM_PARTIAL_ST:
				list = start_rm_st(1, parameters.data);
			break;

			
			case RM_PARTIAL_BF_IP:
				list = start_rm_bf_ip(1, parameters.data);
			break;
			case RM_PARTIAL_BF_DU_UO:
				list = start_rm_bf_du_uo(1, parameters.data);
			break;
			case RM_PARTIAL_RBOUND_MP:
				list = start_rbound_mp(1, parameters.data);
			break;
			case RM_PARTIAL_RBOUND_MP_BF:
				list = start_rbound_mp_bf(1, parameters.data);
			break;
			case RM_PARTIAL_RBOUND_MP_NFR:
				list = start_rbound_mp_nfr(1, parameters.data);
			break;


			default:
				LOG( "Error: unknow partial function %d\n", parameters.partial_func);
				return -1;
		}*/
		
		if(list == NULL)
		{
			LOG("\nError: Task set no scheduable using partial function");
			return -1;
		}
		current_processor = list;

		while(current_processor)
		{
			n = 0;
			t = NULL;
			current_task = current_processor->task;
			//* read task set parameters from file
			while(current_task)
			{
				//* set task parameters for first activation
				new_task.id = ++n;
				new_task.t = (double) current_task->t;
				new_task.c = (double) current_task->c;
				new_task.f = (double) current_task->f;
				new_task.r = 0.0;
				new_task.res = NULL;
				new_task.d = new_task.r + new_task.t;
				new_task.cet = 0.0;
				new_task.e = -1;
				new_task.p = set_task_rm_priority(&new_task);
				new_task.state = TASK_READY;
				new_task.se = 0;

	#ifdef USE_RESOURCES
				/// load resource info for current task
				new_task.res = NULL;
				resource_list = load_resource_file(argv[4], &new_task, resource_list);
				
				if (!resource_list) {
					LOG( "Error: while loading resource file\n");
					return -1;
				}
	#endif

				//add task to task list
				t = add_task_list_p_sorted(t, new_task);
				current_task = (task_set_t*) (current_task->next);
			}

			sprintf(partialname, "%s_partial%d",basename_trace,current_processor->id);

#ifdef USE_THREAD
			args 			= (rm_thread_args*) (malloc(sizeof(rm_thread_args)));
			args->mode		= mode;
			args->no_proc	= 1;
			args->max_time	= max_time;
			args->task		= t;
			args->outfile[0] = '\0';
			strcpy(args->outfile, partialname);

			res = pthread_create(&thread_task, NULL, thread_start_rm, args);


			if( res != 0)
				DBG("\n Error creating thread");
			else
			{
				//DBG("\nnew thread created...");
				pthread_mutex_lock(&rm_mutex); 
					rm_active_threads ++;
				pthread_mutex_unlock(&rm_mutex); 

			}
#else
			res += start_rm(mode, 1, max_time, t, partialname);
#endif
			current_processor = (processor_t*) (current_processor->next);
		}
	}
	
#ifdef USE_THREAD
	//wait for finish threads
	while(rm_active_threads != 0);
	{
		DBG("\nwaitting for threads ... %d", rm_active_threads);
	}
#endif

	LOG("\n");
	return res;
}
