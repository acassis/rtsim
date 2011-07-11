#include "../edf_global_sched.h"

// ################################################################3
// 1. agregar el include donde se encuentra la funcion parcial
// ################################################################3
#include "edf_ff.h"



// ################################################################3
// 2. nombre del comando que se usaran dentro de TCL para llamar al codigo nativo
// ################################################################3
//name used for command call from TCL
//#define COMMAND_NAME "edfbf"
#define COMMAND_NAME "edfff"
//ejemplo de llamada desde TCL
//set r [catch {eval COMMAND_NAME $algorithmSelected $numberProcessors $simulationTime $pathSavedTasks } errmsg]


// ################################################################3
// 3. Cambiar por la fucncion de la nueva funcion parcial
// ################################################################3
//llamar a la funcion parcial
processor_t* partial_function(processor_t* list, int nproc, char *file)
{
	//funcion parcial que se llamara en esta libreria
	// ## Cambiar por la fucncion de la nueva funcion parcial
	list = start_edf_ff(nproc, file);
	return list;
}

// Nombre del metodo comun usado para entrar a ejecutar el planificador
static int SimuladorCmd(ClientData clientData, Tcl_CmdDeleteProc* proc, int objc, Tcl_Obj* const objv[]);

// ################################################################3
// 4. Renombrar la fucion usando el nombre de la libreria + _Init
// ################################################################3
// ejemplo Edfbf_Init para edfbf
int Edfff_Init(Tcl_Interp *interp)
{
	DBG("\nEdfff_Init TCL v[%s]", TCL_VERSION);
	
    if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL) {
		DBG("\nerror ");
		return TCL_ERROR;
    }
	
	DBG("\nCreating command [%s]\n",COMMAND_NAME);
	//al recibir de TCL el commando COMMAND_NAME llamar a la funcion SimuladorCmd
    Tcl_CreateObjCommand(interp, COMMAND_NAME, SimuladorCmd, NULL, NULL);
    Tcl_PkgProvide(interp, COMMAND_NAME, "1.1");

	return TCL_OK;
}

//incluir el codigo comun para todos los metodos
#include "../common_edf_global_sched.cxx"