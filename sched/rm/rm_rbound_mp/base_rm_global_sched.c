#include "../rm_global_sched.h"

// ################################################################3
// 0. agregar el include donde se encuentra la funcion parcial
// ################################################################3
#include "rbound_mp.h"


//name used for command call from TCL
// ################################################################3
// 1. nombre del comando que se usaran dentro de TCL para llamar al codigo nativo
// ################################################################3
#define COMMAND_NAME "rmrboundmp"
//ejemplo de llamada desde TCL
//set r [catch {eval COMMAND_NAME $algorithmSelected $numberProcessors $simulationTime $pathSavedTasks } errmsg]



// ################################################################3
// 2. Cambiar por la fucncion de la nueva funcion parcial
// ################################################################3
//llamar a la funcion parcial
processor_t* partial_function(processor_t* list, int nproc, char *file)
{
	//funcion parcial que se llamara en esta libreria
	list = start_rbound_mp(nproc, file);
	return list;
}

static int SimuladorCmd(ClientData clientData, Tcl_CmdDeleteProc* proc, int objc, Tcl_Obj* const objv[]);

//USAR NOMBRE DE LA LIBRERIA MAS _Init
// ejemplo Rmnfll_init para librmnfll
int Rmrboundmp_Init(Tcl_Interp *interp)
{
	DBG("\nrmffll_Init TCL v[%s]", TCL_VERSION);

    if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL) {
		DBG("\nerror ");
		return TCL_ERROR;
    }
	
	DBG("\nCreating command [%s]\n",COMMAND_NAME);
    Tcl_CreateObjCommand(interp, COMMAND_NAME, SimuladorCmd, NULL, NULL);
    Tcl_PkgProvide(interp, COMMAND_NAME, "1.1");

	return TCL_OK;
}


//#define USE_RESOURCES
#define USE_TRACE_FILE
//#define END_ON_MISS_DEADLINE

//incluir codigo comun
#include "../base_rm_global_sched.cxx"
