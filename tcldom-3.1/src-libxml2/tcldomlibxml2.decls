# tcldom.decls --
#
# This file contains the declarations for all supported public
# functions that are exported by the TCLDOM/lixml2 library via the
# stubs table. This file is used to generate the tcldomxmlDecls.h /
# tcldomxmlStubsLib.c / tcldomxmlStubsInit.c files.
#

# Declare each of the functions in the public TclDOM/libxml2
# interface.  Note that the an index should never be reused for a
# different function in order to preserve backwards compatibility.

library tcldom_libxml2

# Define the TCLDOM/libxml2 interface:

interface tcldom_libxml2
#hooks {}

declare 0 generic {
    int Tcldom_libxml2_Init(Tcl_Interp *interp)
}
if 0 {
    ## No SafeInit declared by package.
    declare 1 generic {
	int Tcldom_libxml2_SafeInit(Tcl_Interp *interp)
    }
}

#########################################################################
###  Accessor API

# Slots 2-6 are deprecated

#declare 2 generic {
#    Tcl_Obj * TclDOM_NewDoc (Tcl_Interp *interp)
#}
#declare 3 generic {
#    Tcl_Obj * TclDOM_CreateObjFromNode (xmlNodePtr nodePtr)
#}
#declare 4 generic {
#    Tcl_Obj * TclDOM_CreateObjFromDoc  (xmlDocPtr  docPtr)
#}
#declare 5 generic {
#    int TclDOM_GetNodeFromObj (Tcl_Interp *interp, Tcl_Obj *objPtr, xmlNodePtr *nodePtrPtr)
#}
#declare 6 generic {
#    int TclDOM_GetDocFromObj  (Tcl_Interp *interp, Tcl_Obj *objPtr, xmlDocPtr *docPtrPtr)
#}

# end of deprecated section

# Node accessors

declare 7 generic {
     Tcl_Obj * TclDOM_libxml2_CreateObjFromNode (Tcl_Interp *interp, xmlNodePtr nodePtr)
}
declare 8 generic {
     int TclDOM_libxml2_GetNodeFromObj (Tcl_Interp *interp, Tcl_Obj *objPtr, xmlNodePtr *nodePtrPtr)
}
declare 9 generic {
     int TclDOM_libxml2_GetTclNodeFromObj (Tcl_Interp *interp, Tcl_Obj *objPtr, TclDOM_libxml2_Node **tNodePtrPtr)
}

# Event node accessors

declare 10 generic {
     Tcl_Obj * TclDOM_libxml2_NewEventObj (Tcl_Interp *interp, xmlDocPtr doc, enum TclDOM_EventTypes type, Tcl_Obj *typeObjPtr)
}
declare 11 generic {
     int TclDOM_libxml2_GetEventFromObj (Tcl_Interp *interp, Tcl_Obj *objPtr, TclDOM_libxml2_Event **eventPtrPtr)
}
declare 12 generic {
     int TclDOM_libxml2_GetTclEventFromObj (Tcl_Interp *interp, Tcl_Obj *objPtr, TclDOM_libxml2_Node **nodePtrPtr)
}
declare 13 generic {
     void TclDOM_libxml2_DestroyNode (Tcl_Interp *interp, TclDOM_libxml2_Node *tNodePtr)
}
declare 14 generic {
     void TclDOM_libxml2_InvalidateNode (TclDOM_libxml2_Node *tNodePtr)
}
declare 15 generic {
     Tcl_Obj * TclDOM_libxml2_CreateObjFromDoc (Tcl_Interp *interp, xmlDocPtr docPtr)
}

# Slots 15-19 reserved for later use

# Event management

declare 20 generic {
     void TclDOM_InitEvent (TclDOM_libxml2_Event *eventPtr,
			    enum TclDOM_EventTypes type,
                            Tcl_Obj *typeObjPtr,
                            Tcl_Obj *bubblesPtr,
                            Tcl_Obj *cancelablePtr)
}
declare 21 generic {
     void TclDOM_InitUIEvent (TclDOM_libxml2_Event *eventPtr,
			      enum TclDOM_EventTypes type,
                              Tcl_Obj *typeObjPtr,
                              Tcl_Obj *bubblesPtr,
                              Tcl_Obj *cancelablePtr,
                              Tcl_Obj *viewPtr,
                              Tcl_Obj *detailPtr)
}
declare 22 generic {
     void TclDOM_InitMouseEvent (TclDOM_libxml2_Event *eventPtr,
			         enum TclDOM_EventTypes type,
                                 Tcl_Obj *typeObjPtr,
                                 Tcl_Obj *bubblesPtr,
                                 Tcl_Obj *cancelablePtr,
                                 Tcl_Obj *viewPtr,
                                 Tcl_Obj *detailPtr,
                                 Tcl_Obj *screenXPtr,
                                 Tcl_Obj *screenYPtr,
                                 Tcl_Obj *clientXPtr,
                                 Tcl_Obj *clientYPtr,
                                 Tcl_Obj *ctrlKeyPtr,
                                 Tcl_Obj *altKeyPtr,
                                 Tcl_Obj *shiftKeyPtr,
                                 Tcl_Obj *metaKeyPtr,
                                 Tcl_Obj *buttonPtr,
                                 Tcl_Obj *relatedNodePtr)
}
declare 23 generic {
     void TclDOM_InitMutationEvent (TclDOM_libxml2_Event *eventPtr,
			            enum TclDOM_EventTypes type,
                                    Tcl_Obj *typeObjPtr,
                                    Tcl_Obj *bubblesPtr,
                                    Tcl_Obj *cancelablePtr,
                                    Tcl_Obj *relatedNodePtr,
                                    Tcl_Obj *prevValuePtr,
                                    Tcl_Obj *newValuePtr,
                                    Tcl_Obj *attrNamePtr,
                                    Tcl_Obj *attrChangePtr)
}
declare 24 generic {
     int TclDOM_PostUIEvent (Tcl_Interp *interp,
                             TclXML_libxml2_Document *tDocPtr,
                             Tcl_Obj *nodeObjPtr,
			     enum TclDOM_EventTypes type,
                             Tcl_Obj *typeObjPtr,
                             Tcl_Obj *bubblesPtr,
                             Tcl_Obj *cancelablePtr,
                             Tcl_Obj *viewPtr,
                             Tcl_Obj *detailPtr)
}
declare 25 generic {
     int TclDOM_PostMouseEvent (Tcl_Interp *interp,
                                TclXML_libxml2_Document *tDocPtr,
                                Tcl_Obj *nodeObjPtr,
			        enum TclDOM_EventTypes type,
                                Tcl_Obj *typeObjPtr,
                                Tcl_Obj *bubblesPtr,
                                Tcl_Obj *cancelablePtr,
                                Tcl_Obj *viewPtr,
                                Tcl_Obj *detailPtr,
                                Tcl_Obj *screenXPtr,
                                Tcl_Obj *screenYPtr,
                                Tcl_Obj *clientXPtr,
                                Tcl_Obj *clientYPtr,
                                Tcl_Obj *ctrlKeyPtr,
                                Tcl_Obj *altKeyPtr,
                                Tcl_Obj *shiftKeyPtr,
                                Tcl_Obj *metaKeyPtr,
                                Tcl_Obj *buttonPtr,
                                Tcl_Obj *relatedNodePtr)
}
declare 26 generic {
     int TclDOM_PostMutationEvent (Tcl_Interp *interp,
                                   TclXML_libxml2_Document *tDocPtr,
                                   Tcl_Obj *nodeObjPtr,
			           enum TclDOM_EventTypes type,
                                   Tcl_Obj *typeObjPtr,
                                   Tcl_Obj *bubblesPtr,
                                   Tcl_Obj *cancelablePtr,
                                   Tcl_Obj *relatedNodePtr,
                                   Tcl_Obj *prevValuePtr,
                                   Tcl_Obj *newValuePtr,
                                   Tcl_Obj *attrNamePtr,
                                   Tcl_Obj *attrChangePtr)
}
declare 27 generic {
     int TclDOM_AddEventListener (Tcl_Interp *interp,
                                  TclXML_libxml2_Document *tDocPtr,
                                  void *tokenPtr,
			          enum TclDOM_EventTypes type,
                                  Tcl_Obj *typeObjPtr,
                                  Tcl_Obj *listenerPtr,
                                  int capturing)
}
declare 28 generic {
     int TclDOM_RemoveEventListener (Tcl_Interp *interp,
                                     TclXML_libxml2_Document *tDocPtr,
                                     void *tokenPtr,
			             enum TclDOM_EventTypes type,
                                     Tcl_Obj *typeObjPtr,
                                     Tcl_Obj *listenerPtr,
                                     int capturing)
}
declare 29 generic {
     int TclDOM_DispatchEvent (Tcl_Interp *interp,
                               Tcl_Obj *nodePtr,
                               Tcl_Obj *eventObjPtr,
                               TclDOM_libxml2_Event *eventPtr)
}
declare 30 generic {
     Tcl_Obj * TclDOM_GetEventListener (Tcl_Interp *interp,
                                  TclXML_libxml2_Document *tDocPtr,
                                  void *tokenPtr,
			          enum TclDOM_EventTypes type,
                                  Tcl_Obj *typeObjPtr,
                                  int capturing)
}

#########################################################################
