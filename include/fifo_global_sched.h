#include "simulator.h"

#include <string.h>
#include <stdio.h>
#include <math.h>

#include "simulator.h"
#include "task.h"
#include "processor.h"
#include "sched_event.h"
#include "trace_event.h"


extern int start_fifo_main(ALGORITHM_PARAMS parameters);
extern void print_fifo_usage();