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



//llamar a la funcion parcial
processor_t* partial_function(processor_t* list, int nproc, char *file)
{
	DBG(" \n start_rbound_mp");
	//funcion parcial que se llamara en esta libreria
	list = start_rbound_mp(nproc, file);
	return list;
	DBG(" \n END start_rbound_mp");
}

//nombre de la funcion que ejecutara los comandos
//USAR NOMBRE DE LA LIBRERIA MAS Cmd, la primera letra debera ser Mayuscula
//ejemplo RmnfllCmd para libreria librmnfll
static int RmrboundmpCmd(ClientData clientData, Tcl_CmdDeleteProc* proc, int objc, Tcl_Obj* const objv[]) 
{
	int res = TCL_OK;
	char* strings[255];
	int t = 0;
	ALGORITHM_PARAMS parameters;

	DBG("\n cleaning log...");
	init_logger();
	
//convertir la lista de parametros a cadenas de C
	DBG("\n called with %d arguments", objc);
	for(t=0;t<objc;t++)
	{
		DBG("\n%d: %s",t, (*objv[t]).bytes);
		strings[t] = (*objv[t]).bytes;
	}
	DBG("\n");
		
	//USAR SIEMPRE MODO PARCIAL
	parameters.algorithm	= RM;
	parameters.mode			= MODE_PARTIAL;
	// SOLO SE USARA UNA FUNCION PARCIAL, NO ESPECIFICAR EN LOS PARAMETROS
	// parameters.partial_func = RM_PARTIAL_RBOUND_MP_NFR;
	
	parameters.processor	= atoi(strings[2]);
	parameters.time			= atoi(strings[3]);
	strcpy(parameters.data, strings[4]);

	parameters.param_count = objc - 2;
	
	res = start_rm_main(parameters);
	//res = simulator_main(objc, strings);

	DBG("\n end main: %d",res);
	return res;
}

//USAR NOMBRE DE LA LIBRERIA MAS _Init
// ejemplo Rmnfll_init para librmnfll
int Rmrboundmp_Init(Tcl_Interp *interp)
{
	DBG("\nrmffll_Init TCL v[%s]", TCL_VERSION);

    if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL) {
		DBG("\nerror ");
		return TCL_ERROR;
    }
	
	DBG("\ncreating command [%s]\n",COMMAND_NAME);
    Tcl_CreateObjCommand(interp, COMMAND_NAME, RmrboundmpCmd, NULL, NULL);
    Tcl_PkgProvide(interp, COMMAND_NAME, "1.1");

	return TCL_OK;
}


//#define USE_RESOURCES
#define USE_TRACE_FILE
//#define END_ON_MISS_DEADLINE

//incluir codigo comun
#include "../base_rm_global_sched.cxx"