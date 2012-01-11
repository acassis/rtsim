//File with the base code common for all the partials functions or methods that be added
//This file will be included in each version from edf with each function partial

#include <stdlib.h>
#include "common_edf_sched.h"

//#define USE_RESOURCES
#define USE_TRACE_FILE
//#define END_ON_MISS_DEADLINE


#ifdef SIMLUATOR_LIB_TCL
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
	parameters.algorithm	= EDF;
	parameters.mode			= LIB_MODE;
	//SHOULD BE USED ONLY ONE PARTIAL FUNCTION, NOT SPECIFY IN THE PARAMETERS
	// parameters.partial_func = EDF_PARTIAL_RBOUND_MP_NFR;
	
	parameters.processor	= atoi(strings[2]);
	parameters.time			= atoi(strings[3]);
	strcpy(parameters.data, strings[4]);
	
	//unused params count
	//t = objc - 2;
	//parameters.param_count = t;
	res = start_edf_main(parameters);
	//res = simulator_main(objc, strings);

	//DBG("\n End SimulatorCmd: %d",res);
	return res;
}
#else

//function input to execute the function how aplication 
int main(int argc, char* argv[])
{
	int res = 01;
	char* strings[255];
	int t = 0;
	ALGORITHM_PARAMS parameters;

	DBG("\n cleaning log...");
	init_logger();


	if(argc != 4)
	{
		DBG("Invalid params");
		return -1;
	}
	// 4 required params
	// 0 (as default) application name for example Simulator.exe
	// 1 file name
	// 2 processator counts
	// 3 time
	
	for(t=0;t<argc;t++)
	{
		strings[t] = argv[t];
	}


	//USE ALWAYS PARTIAL MODE 
	parameters.algorithm	= EDF;
	parameters.mode			= LIB_MODE;
	// ONLY WILL USED ONE PARTIAL FUNCTION, NOT SPECIFY IN THE PARAMETERS
	// parameters.partial_func = EDF_PARTIAL_RBOUND_MP_NFR;
	
	strcpy(parameters.data, strings[1]);
	parameters.processor	= atoi(strings[2]);
	parameters.time			= atoi(strings[3]);
	
	//t = objc - 2;
	//parameters.param_count = 6; //unused
	res = start_edf_main(parameters);
	
	return res;
}
#endif

#ifdef USE_THREAD

pthread_mutex_t edf_filetracker_mutex;
pthread_mutex_t edf_mutex; 
int edf_active_threads;

typedef struct {
	int mode;
	int no_proc;
	double max_time;
	task_set_t *task;
	char outfile[255];
}edf_thread_args;

void* thread_start_edf(void* params)
{
	edf_thread_args* edf_params = (edf_thread_args*)params;
	int mode		= edf_params->mode;
	int no_proc		= edf_params->no_proc;
	double max_time = edf_params->max_time;
	task_set_t *t	= edf_params->task;
	char* outfile	= (edf_params->outfile);

	//DBG("\nCreating new thread ... %s", edf_params->outfile);
	start_edf(mode, no_proc, max_time, t, outfile);

	free(edf_params);
	//DBG("\nThread End.");
}
#endif

int start_edf(int mode, int no_proc, double max_time, task_set_t *t, char* outfile)
{
	processor_t *p = NULL; /* Head of processor's list */
	sched_event_t *event_list = NULL; /* Head of scheduling events list */
	sched_event_t *missed_deadlines = NULL; /* Head of missed deadlines events list */

//	int mode;
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

#ifdef USE_TRACE_FILE
	////////////// tracer
	int file_id = 0;
	char file_trace[255];
	char basename_trace[255];

	trace_event new_trace_event;
	new_trace_event.next = NULL;
	///////////////////////////////

	strcpy(basename_trace, outfile);

#endif
	
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
		new_event.t_event =  SCHEDE_RELEASE;
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
		//LOG("Simulation time = [0, %.2f]\n", max_time);
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
		task_in_event = event_list-> task;
		current_time = event_list-> time;
	}

	while ((event_list) && (current_time <= max_time)) {

		//if(previous_time != current_time)
		LOG("\n================= Time %.2f ==============\n", current_time);
		switch (event_list ->t_event) {

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
				new_event.t_event =  SCHEDE_FINISH;
				new_event.time = current_time + task_in_event -> c;
				new_event.task = task_in_event;
				new_event.p = event_list -> p;
				new_event.processor = current_processor;
				event_list = add_sched_event_list_time_sorted(event_list, new_event);

				// getchar();
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
					// LOG("..cet = %.2f\n", task_in_processor -> cet);
					task_in_processor -> state = TASK_READY;
					/* delerte finish event of preempted task */

					LOG("|_ Removing task %d, from processor %d\n", task_in_processor->id, current_processor->id);

					// Delete schedule FINISH event	/////////////////////////////////
					new_event.task = task_in_processor;
					new_event.t_event = SCHEDE_FINISH;
					if (is_event_in_list(event_list, &new_event, &i)) {
						event_list = del_sched_event_from_list(event_list, i);
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
					new_event.t_event =  SCHEDE_FINISH;
					new_event.time = current_time + task_in_event -> c;
					new_event.task = task_in_event;
					new_event.p = task_in_event -> p; //changed from event_list->p
					new_event.processor = current_processor;
					event_list = add_sched_event_list_time_sorted(event_list, new_event);
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
					task_in_event -> state = TASK_READY;
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
			/* check if task finished by its deadline */
			if (current_time > task_in_event -> d) { /* deadline miseed, thus generate event */

				LOG("|_ **Task deadline missed\n");
				//print task fail
				new_event.id = deadln_miss_id++;
				new_event.t_event =  SCHEDE_DEADLN_MISS;
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
					//DBG("\nOutfile %s",basename_trace);
					sprintf(file_trace, "%s_p%d.ktr", &basename_trace[0], file_id);
					create_trace_list(file_trace, current_processor->tracer, no_task, current_time, (char *) "EDF");
					
					current_processor = current_processor->next;

				}
				current_processor = event_list -> processor;

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
			task_in_event->d = task_in_event -> r + task_in_event -> t;
			task_in_event->cet = 0.0;
			task_in_event->e = -1;
			task_in_event->state = TASK_READY;
			task_in_event->p = set_task_edf_priority(task_in_event);
			/* add event (task release) for next task activation (since current activation has finished */
			new_event.id = event_id++;
			new_event.t_event =  SCHEDE_RELEASE;
			new_event.time = task_in_event -> r;
			new_event.task = task_in_event;
			new_event.p = task_in_event -> p;
			new_event.processor = NULL;
			event_list = add_sched_event_list_time_sorted(event_list, new_event);

#ifdef USE_TRACE_FILE
			////////////////////////////// add end task on tracer
			new_trace_event.task = task_in_event->id;
			new_trace_event.time = (int) current_time;
			new_trace_event.t_event = END_TASK;
			/*(trace_event *)*/ current_processor->tracer = (trace_event *) add_trace_event((trace_event *) current_processor->tracer, new_trace_event);
			//////////////////////////////
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
				new_event.t_event =  SCHEDE_FINISH;
				new_event.time = current_time + (task_to_execute -> c - task_to_execute -> cet);
				new_event.task = task_to_execute;
				new_event.p = task_to_execute -> p;
				new_event.processor = current_processor;
				event_list = add_sched_event_list_time_sorted(event_list, new_event);

				assign_task_to_processor(current_processor, task_to_execute, current_time);
				LOG("|_ Task %d is now executing on processor %d\n", task_to_execute->id, current_processor->id);
				task_to_execute -> e = current_time;
				task_to_execute -> state = TASK_RUNNING;
				//LOG("task %d assigned to processor %d\n", task_to_execute -> id, current_processor -> id);

#ifdef USE_TRACE_FILE
				/////////////////////////////////// add tracer deadline and execute
				new_trace_event.task = task_to_execute->id;
				new_trace_event.time = (int) current_time;
				new_trace_event.t_event = EXECUTE_TASK;
				/*(trace_event *)*/ current_processor->tracer = (trace_event *) add_trace_event((trace_event *) current_processor->tracer, new_trace_event);
				///////////////////////////////////
#endif

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

		//if is only 1 processor skip _p# from file name
		if(no_proc == 1)
		{
			sprintf(file_trace, "%s.ktr", &basename_trace[0]);
		}else
		{
			sprintf(file_trace, "%s_p%d.ktr", &basename_trace[0], file_id);
		}


		create_trace_list(file_trace, (trace_event *) current_processor->tracer, no_task, (int) max_time, (char *) "EDF");
		current_processor = (processor_t *) current_processor->next;

	}
	////////////////////////////////////////////////////////
#endif

#ifdef USE_THREAD
	pthread_mutex_lock(&edf_mutex); 
		edf_active_threads--;
	pthread_mutex_unlock(&edf_mutex); 
#endif
	//LOG("Scheduling activities finished at current time = %.2f\n", current_time);
	return(no_proc);
}


int start_edf_main(ALGORITHM_PARAMS parameters)
{

#ifdef USE_THREAD
	pthread_t thread_task;
	edf_thread_args* args;
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

	FILE *kiwi_files;
	FILE *in_file; /* Input file */
	DBG("\nstart_edf_main");
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
		LOG( "Error:Unable to open %s file\n", parameters.data);//argv[argid + PARAM_FILE]);
		return -1;
	}
	/////////////////////////////////////////////////////////////////////////////////////

	
	//create output list for open using kiwi.
	sprintf(partialname,"%s_kiwi_files.txt", COMMAND_NAME);
	kiwi_files = fopen(partialname, "w+");
	if (kiwi_files == NULL) {
		LOG( "Error: Unable to create kiwi_files.txt file\n");
		return -1;
	}
	

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
				new_task.p = set_task_edf_priority(&new_task);
				new_task.sp = NULL;
				new_task.state = TASK_READY;
				new_task.se = 0;
				

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


		//add to kiwi list the output file.
		fprintf(kiwi_files, "%s.ktr\n", basename_trace);
		
		res = start_edf(mode,no_proc, max_time, t, basename_trace);

	}
	else if(mode == MODE_PARTIAL)		//partial mode
	{
		DBG("\nMODE_PARTIAL");
#ifdef USE_THREAD
		
		pthread_mutex_init (&edf_mutex, NULL); 
		edf_active_threads = 0;
#endif
		res = 0;
		
		list = NULL;
		DBG("\ncalling to partial function for %d processors", no_proc);
		list = partial_function(list, no_proc, parameters.data);


		//task are not scheduable using partial funciton
		if(list == NULL)
		{
			LOG("\nError: Task set no scheduable using partial function");
			return -1;
		}

		
		//task are shceduable, display task assignations
		DBG("\n::: Planning :::");
		current_processor = list;
		while(current_processor)
		{
			DBG("\nProcessor %d", current_processor->id);
			current_task = current_processor->task;
			while(current_task)
			{
				DBG("\n    Task %d",current_task->id);
				current_task = current_task->next;
			}
			current_processor = current_processor->next;
		}

		DBG("\n ::: End Planning :::");
		
	

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
				new_task.p = set_task_edf_priority(&new_task);
				new_task.sp = NULL;
				new_task.state = TASK_READY;
				new_task.se = 0;

	
				//add task to task list
				t = add_task_list_p_sorted(t, new_task);
				current_task = (task_set_t*) (current_task->next);
			}

			sprintf(partialname, "%s_%s_partial_P%d", basename_trace, COMMAND_NAME,( current_processor->id)-1);

			//add to kiwi list the output file.
			fprintf(kiwi_files, "%s.ktr\n", partialname);
			
#ifdef USE_THREAD
			//create the thread for set task
			args 			= (edf_thread_args*) (malloc(sizeof(edf_thread_args)));
			args->mode		= mode;
			args->no_proc	= 1;
			args->max_time	= max_time;
			args->task		= t;
			args->outfile[0] = '\0';
			strcpy(args->outfile, partialname);

			//DBG("\nNew thread for %s, tasks %d", args->outfile, n);
			res = pthread_create(&thread_task, NULL, thread_start_edf, args);

			if( res != 0)
				DBG("\n Error creating thread");
			else
			{
				//DBG("\nnew thread created.");
				pthread_mutex_lock(&edf_mutex); 
					edf_active_threads ++;
				pthread_mutex_unlock(&edf_mutex); 
			}
#else
			//Run without thread.
			res += start_edf(mode, 1, max_time, t, partialname);
#endif
			current_processor = (processor_t*) (current_processor->next);
		}
	}
	
	//close output to kiwi list.
	fclose(kiwi_files);
	
#ifdef USE_THREAD
	//wait for finish threads
	while(edf_active_threads != 0);
	{
		DBG("\nwaitting for threads ... %d", edf_active_threads);
	}
#endif

	LOG("\n");
	return res;
}
