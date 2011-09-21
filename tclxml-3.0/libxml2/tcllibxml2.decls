# tcllibxml2.decls --
#
# This file contains the declarations for all supported public
# functions that are exported by the TclXML/libxml2 library via the
# stubs table. This file is used to generate the tcllibxml2Decls.h /
# tcllibxml2StubsLib.c / tcllibxml2StubsInit.c files.
#

# Declare each of the functions in the public TclXML/libxml2
# interface.  Note that the an index should never be reused for a
# different function in order to preserve backwards compatibility.

library tcllibxml2

# Define the TclXML/libxml2 interface:

interface tcllibxml2
#hooks {}

declare 0 generic {
    int Tclxml_libxml2_Init(Tcl_Interp *interp)
}
if 0 {
    ## No SafeInit declared by package.
    declare 1 generic {
	int Tclxml_libxml2_SafeInit(Tcl_Interp *interp)
    }
}

#########################################################################
###  xmlDoc Accessor API

declare 2 generic {
    int TclXML_libxml2_InitDocObj (Tcl_Interp *interp)
}
declare 3 generic {
    Tcl_Obj * TclXML_libxml2_NewDocObj (Tcl_Interp *interp)
}
declare 4 generic {
    Tcl_Obj * TclXML_libxml2_CreateObjFromDoc (xmlDocPtr docPtr)
}
declare 5 generic {
    int TclXML_libxml2_GetDocFromObj (Tcl_Interp *interp, Tcl_Obj *objPtr, xmlDocPtr *docPtr)
}
declare 6 generic {
    int TclXML_libxml2_GetTclDocFromObj (Tcl_Interp *interp, Tcl_Obj *objPtr, TclXML_libxml2_Document **tDocPtrPtr)
}
declare 7 generic {
    int TclXML_libxml2_GetTclDocFromNode (Tcl_Interp *interp, xmlNodePtr nodePtr, TclXML_libxml2_Document **tDocPtrPtr)
}
declare 8 generic {
    void TclXML_libxml2_DestroyDocument (TclXML_libxml2_Document *tDocPtr)
}
declare 9 generic {
    void TclXML_libxml2_DocKeep (Tcl_Obj *objPtr, TclXML_libxml2_DocumentHandling keep)
}
declare 10 generic {
    void TclXML_libxml2_ErrorHandler (void *ctx, xmlErrorPtr error)
}
declare 11 generic {
    void TclXML_libxml2_ResetError (Tcl_Interp *interp)
}
declare 12 generic {
    Tcl_Obj * TclXML_libxml2_GetErrorObj (Tcl_Interp *interp)
}
declare 13 generic {
    void TclXML_libxml2_SetErrorNodeFunc (Tcl_Interp *interp, TclXML_ErrorNodeHandlerProc *proc)
}
#########################################################################
