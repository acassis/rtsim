#include "common_edf_sched.h"

// ################################################################
// 0. Define mode of the library, MODE_GLOBAL or MODE_PARTIAL
// ################################################################
//#define LIB_MODE MODE_GLOBAL
#define LIB_MODE MODE_PARTIAL

// ################################################################
// 1. Add the include.h of where the new partial function or method is located,
// only in case of MODE_PARTIAL 
// ################################################################
#include "edf_bf.h"

// ################################################################
// 2. Add the name of the command that was used in TCL to call native code 
// ################################################################
//name used for command call from TCL
//#define COMMAND_NAME "edfbf"
//name command that will used within TCL to call the native code
#define COMMAND_NAME "edfbf"
//example of calling from TCL 
//set r [catch {eval COMMAND_NAME $algorithmSelected $numberProcessors $simulationTime $pathSavedTasks } errmsg]

// ################################################################
// 3. Rename "partial_function" by the name of the new partial function or method to be added
// Only in case of MODE_PARTIAL, for MODE_GLOBAL dont call any
// ################################################################
//call to the partial function
processor_t* partial_function(processor_t* list, int nproc, char *file)
{
	//partial function or method that is will call in this library 
	// ## Change to function by the new partial function  
	DBG("\ncall start_edf_bf(%d, %s)", nproc, file);
	list = start_edf_bf(nproc, file);
	DBG("\nend start_edf_bf, list = %x", list);
	return list;
}
#ifdef SIMLUATOR_LIB_TCL
// name the common method used to access running the scheduler 
static int SimulatorCmd(ClientData clientData, Tcl_CmdDeleteProc* proc, int objc, Tcl_Obj* const objv[]);

// ################################################################
// 4. Rename the function using the name of the library + _Init
// ################################################################
// exemplo Edfbf_Init for edfbf
int Edfbf_Init(Tcl_Interp *interp)
{
	DBG("\nEdfbf_Init TCL v[%s]", TCL_VERSION);
	
    if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL) {
		DBG("\nerror ");
		return TCL_ERROR;
    }
	
	DBG("\nCreating command [%s]\n",COMMAND_NAME);
	//once it receives the command from TCL COMMAND_NAME,is sent the function call SimulatorCmd
    Tcl_CreateObjCommand(interp, COMMAND_NAME, (void*)SimulatorCmd, NULL, NULL);
    Tcl_PkgProvide(interp, COMMAND_NAME, "1.1");

	return TCL_OK;
}
#endif

//include code common for all methods
#include "../common_edf_sched.cxx"