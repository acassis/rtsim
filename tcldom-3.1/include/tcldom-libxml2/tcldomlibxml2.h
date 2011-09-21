
/* tcldom-libxml2.h --
 *
 *	libxml2 wrapper for TclDOM.
 *
 * Copyright (c) 2005 Explain
 * http://www.explain.com.au/
 * Copyright (c) 2002-2003 Zveno Pty Ltd
 * http://www.zveno.com/
 *
 * See the file "LICENSE" for information on usage and
 * redistribution of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 * $Id: tcldomlibxml2.h,v 1.2 2005/05/24 21:09:56 balls Exp $
 */

#ifndef __TCLDOM_LIBXML2_H__
#define __TCLDOM_LIBXML2_H__

#include <tcldom-libxml2/tcldom.h>
#include <tclxml/tclxml.h>
#include <tclxml-libxml2/docObj.h>
#include <tclxml-libxml2/tclxml-libxml2Decls.h>
#include <libxml/tree.h>
#include <libxml/xmlschemas.h>

/*
 * For C++ compilers, use extern "C"
 */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * These macros are used to control whether functions are being declared for
 * import or export in Windows, 
 * They map to no-op declarations on non-Windows systems.
 * Assumes that tcl.h defines DLLEXPORT & DLLIMPORT correctly.
 * The default build on windows is for a DLL, which causes the DLLIMPORT
 * and DLLEXPORT macros to be nonempty. To build a static library, the
 * macro STATIC_BUILD should be defined before the inclusion of tcl.h
 *
 * If a function is being declared while it is being built
 * to be included in a shared library, then it should have the DLLEXPORT
 * storage class.  If is being declared for use by a module that is going to
 * link against the shared library, then it should have the DLLIMPORT storage
 * class.  If the symbol is beind declared for a static build or for use from a
 * stub library, then the storage class should be empty.
 *
 * The convention is that a macro called BUILD_xxxx, where xxxx is the
 * name of a library we are building, is set on the compile line for sources
 * that are to be placed in the library.  When this macro is set, the
 * storage class will be set to DLLEXPORT.  At the end of the header file, the
 * storage class will be reset to DLLIMPORt.
 */

#undef TCL_STORAGE_CLASS
#ifdef BUILD_Tcldom_libxml2
# define TCL_STORAGE_CLASS DLLEXPORT
#else
# ifdef USE_TCL_STUBS
#  define TCL_STORAGE_CLASS
# else
#  define TCL_STORAGE_CLASS DLLIMPORT
# endif
#endif

/*
 * The following function is required to be defined in all stubs aware
 * extensions of TclDOM.  The function is actually implemented in the stub
 * library, not the main Tcldom library, although there is a trivial
 * implementation in the main library in case an extension is statically
 * linked into an application.
 */

EXTERN CONST char *	Tcldom_libxml2_InitStubs _ANSI_ARGS_((Tcl_Interp *interp,
			    CONST char *version, int exact));

#ifndef USE_TCLDOMXML_STUBS

/*
 * When not using stubs, make it a macro.
 */

#define Tcldom_libxml2_InitStubs(interp, version, exact) \
    Tcl_PkgRequire(interp, "dom::generic", version, exact)

#endif

/*
 * DOM-specific data structure to hook onto documents.
 */

typedef struct TclDOM_libxml2_Document {
  Tcl_Interp *interp;
  TclXML_libxml2_Document *tDocPtr;	/* Pointer back to main document structure */
  Tcl_Obj *objPtr;	/* An object to hold onto for this document */
  Tcl_Command cmd;	/* Tcl command for this document */

  Tcl_HashTable *nodes;
  int nodeCntr;

  /*
   * Validation support
   */

  xmlSchemaPtr schema; /* XML Schemas */
  /* xmlRelaxNGPtr relaxng; */

  /*
   * Event support.
   *
   * These tables are indexed by xmlNodePtr.
   */

  Tcl_HashTable *captureListeners;
  Tcl_HashTable *bubbleListeners;

  /*
   * Optimisation: boolean flag to indicate whether an
   * event listener is registered for an event type.
   * If no event listeners are registered then there is
   * no point in propagating the event.
   */

  int listening[TCLDOM_NUM_EVENT_TYPES];

} TclDOM_libxml2_Document;

/*
 * Node management
 */

/*
 * "nodes" are overloaded: they can be either a libxml2 xmlNodePtr or 
 * an event, which is defined by this module.
 */

typedef struct _TclDOM_libxml2_Node TclDOM_libxml2_Node;

#define TCLDOM_LIBXML2_NODE_NODE 0
#define TCLDOM_LIBXML2_NODE_EVENT 1

/*
 * Data structure to support Events
 */

typedef struct TclDOM_libxml2_Event {
  TclDOM_libxml2_Node *tNodePtr;	/* Generic node structure for this event */
  TclDOM_libxml2_Document *ownerDocument;	/* Toplevel Document for this event */

  enum TclDOM_EventTypes type;	/* Enumerate rep of event type */
  Tcl_Obj *typeObjPtr;		/* For user defined event type */

  int stopPropagation;
  int preventDefault;
  int dispatched;

  Tcl_Obj *altKey;
  Tcl_Obj *attrName;
  Tcl_Obj *attrChange;
  Tcl_Obj *bubbles;
  Tcl_Obj *button;
  Tcl_Obj *cancelable;
  Tcl_Obj *clientX;
  Tcl_Obj *clientY;
  Tcl_Obj *ctrlKey;
  Tcl_Obj *currentNode;
  Tcl_Obj *detail;
  Tcl_Obj *eventPhase;
  Tcl_Obj *metaKey;
  Tcl_Obj *newValue;
  Tcl_Obj *prevValue;
  Tcl_Obj *relatedNode;
  Tcl_Obj *screenX;
  Tcl_Obj *screenY;
  Tcl_Obj *shiftKey;
  Tcl_Obj *target;
  Tcl_Obj *timeStamp;
  Tcl_Obj *view;
} TclDOM_libxml2_Event;

typedef void (TclDOM_libxml2_Node_FreeHookProc) _ANSI_ARGS_((ClientData clientData));

struct _TclDOM_libxml2_Node {
  union {
    xmlNodePtr nodePtr;
    TclDOM_libxml2_Event *eventPtr;
  } ptr;

  int type;			/* Distinguish between libxml2 nodes and events */

  char *token;			/* string rep of this node */
  Tcl_Command cmd;		/* Tcl command that access this structure */

  void *objs;			/* Opaque object for tracking Tcl_Obj's that refer to this node */

  ClientData apphook;		/* Application hook - not used by TclXML or TclDOM */
  TclDOM_libxml2_Node_FreeHookProc *appfree;
};

/*
 * Accessor functions => Stubs
 */

#include <tcldom-libxml2/tcldomlibxml2Decls.h>

#undef  TCL_STORAGE_CLASS
#define TCL_STORAGE_CLASS DLLIMPORT

#ifdef __cplusplus
}
#endif

#endif /* TCLDOM_LIBXML2_H__ */
