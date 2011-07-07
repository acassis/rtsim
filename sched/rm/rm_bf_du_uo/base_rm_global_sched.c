#include "../rm_global_sched.h"

//agregar el include donde se encuentra la funcion parcial
// #include "rm_nf_ll.h"
// #include "rm_bf_ll.h"
// #include "rm_ff_ll.h"
// #include "rm_wf_ll.h"
// #include "rm_ff_du_uo.h"
// #include "rm_ff_ip.h"
// #include "rm_gt.h"
// #include "rm_nf_ip.h"
// #include "rm_st.h"
// #include "rm_bf_ip.h"
#include "rm_bf_du_uo.h"
// #include "rbound_mp.h"
// #include "rbound_mp_bf.h"
// #include "rbound_mp_nfr.h"

//#define USE_RESOURCES
#define USE_TRACE_FILE
//#define END_ON_MISS_DEADLINE

//name used for command call from TCL
//nombre del comando que se usaran dentro de TCL para llamar al codigo nativo
#define COMMAND_NAME "rmbfduuo"
//ejemplo de llamada desde TCL
//set r [catch {eval COMMAND_NAME $algorithmSelected $numberProcessors $simulationTime $pathSavedTasks } errmsg]

//llamar a la funcion parcial
processor_t* partial_function(processor_t* list, int nproc, char *file)
{
	//funcion parcial que se llamara en esta libreria
	list = start_rm_bf_du_uo(nproc, file);

	return list;
}


static int SimuladorCmd(ClientData clientData, Tcl_CmdDeleteProc* proc, int objc, Tcl_Obj* const objv[]);
//USAR NOMBRE DE LA LIBRERIA MAS _Init
// ejemplo Rmnfll_init para librmnfll
int Rmbfduuo_Init(Tcl_Interp *interp)
{
	DBG("\nrmffll_Init TCL v[%s]", TCL_VERSION);
	//ClientData data;
    if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL) {
		DBG("\nerror ");
		return TCL_ERROR;
    }

	DBG("\nCreating command [%s]\n",COMMAND_NAME);
    Tcl_CreateObjCommand(interp, COMMAND_NAME, SimuladorCmd, NULL, NULL);
    Tcl_PkgProvide(interp, COMMAND_NAME, "1.1");

	return TCL_OK;
}

#include "../base_rm_global_sched.cxx"
