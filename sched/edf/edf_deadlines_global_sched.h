#include "simulator.h"

#include <string.h>
#include <stdio.h>
#include <math.h>

#include "task.h"
#include "processor.h"
#include "sched_event.h"
#include "trace_event.h"

extern int start_edf_deadline_main(ALGORITHM_PARAMS parameters);
extern void print_edf_deadline_usage();