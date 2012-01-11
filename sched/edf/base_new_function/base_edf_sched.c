#include "common_edf_sched.h"

// ################################################################
// 0. Define mode of the library, MODE_GLOBAL or MODE_PARTIAL
// ################################################################
// #define LIB_MODE MODE_GLOBAL
#define LIB_MODE MODE_PARTIAL

// ################################################################
// 1. Add the include.h of where the new partial function or method is located
// Only in case of MODE_PARTIAL 
// ################################################################
// #include "edf_nf_ll.h"


// ################################################################
// 2. Add the name of the command that was used in TCL to call native code 
// ################################################################
//name used for command call from TCL
//#define COMMAND_NAME "edfbfduuo"
//name command that will used within TCL to call the native code
#define COMMAND_NAME "functionedfglobal"
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
	//list = start_edf_nf_ll(nproc, file);
	list = start_functionparcial(nproc, file);
	return list;
}

#ifdef SIMLUATOR_LIB_TCL
// name the common method used to access running the scheduler 
static int SimulatorCmd(ClientData clientData, Tcl_CmdDeleteProc* proc, int objc, Tcl_Obj* const objv[]);

// ################################################################
// 4. Rename the function using the name of the library + _Init
// ################################################################
// example edfnfll_init for edfnfll
int Edfglobal_Init(Tcl_Interp *interp)
{
	DBG("\nEdfglobal_Init TCL v[%s]", TCL_VERSION);
	
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