#ifndef __EDF_GLOBAL_SCHED_H__
#define __EDF_GLOBAL_SCHED_H__
#include <simulator.h>

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <task.h>
#include <processor.h>
#include <sched_event.h>
#include <trace_event.h>

#ifdef SIMLUATOR_LIB_TCL
	#include <tcl.h>
	#include <stdio.h>
#endif

extern int start_edf_main(ALGORITHM_PARAMS parameters);
extern void print_edf_usage();

/* lista antes usada para determinar la fucion parcial 
typedef enum
{
	EDF_PARTIAL_NF=0,
	EDF_PARTIAL_FF,
	EDF_PARTIAL_BF,
	EDF_PARTIAL_WF,
	EDF_PARTIAL_COUNT,

}EDF_PARTIAL_MODE;
*/
#endif