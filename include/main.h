#include "simulator.h"

#include "edf_global_sched.h"
#include "rm_global_sched.h"
#include "edf_deadlines_global_sched.h"
#include "rm_deadlines_global_sched.h"
#include "fifo_global_sched.h"

#ifdef SIMLUATOR_LIB_TCL
#include <tcl.h>
#include <stdio.h>

extern int simulator_main(int argc, char* argv[]);

//extern static int SimulatorCmd(ClientData clientData, Tcl_CmdDeleteProc* interp, int objc, Tcl_Obj* const objv[]);
//extern int Simulator_Init(Tcl_Interp *interp);
#endif

