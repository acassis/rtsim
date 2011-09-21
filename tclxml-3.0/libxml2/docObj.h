/* docObj.h --
 *
 *	This module manages libxml2 xmlDocPtr Tcl objects.
 *
 * Copyright (c) 2003 Zveno Pty Ltd
 * http://www.zveno.com/
 *
 * See the file "LICENSE" for information on usage and
 * redistribution of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 * $Id: docObj.h,v 1.3 2003/12/09 04:43:15 balls Exp $
 */

#ifndef TCLXML_LIBXML2_DOCOBJ_H
#define TCLXML_LIBXML2_DOCOBJ_H

#ifdef TCLXML_BUILD_AS_FRAMEWORK
#include <Tcl/tcl.h>
#else
#include <tcl.h>
#endif /* TCLXML_BUILD_AS_FRAMEWORK */
#include <libxml/tree.h>

typedef void (TclXML_libxml2Doc_FreeHookProc) _ANSI_ARGS_((ClientData clientData));

/*
 * Values that define how documents are handled:
 * KEEP means that documents must be explicitly destroyed,
 * IMPLICIT means that documents will be destroyed when there are no longer
 * any references to it.
 */

typedef enum TclXML_libxml2_DocumentHandling {
  TCLXML_LIBXML2_DOCUMENT_KEEP,
  TCLXML_LIBXML2_DOCUMENT_IMPLICIT
} TclXML_libxml2_DocumentHandling;

typedef struct TclXML_libxml2_Document {
  xmlDocPtr docPtr;

  char *token;			/* string rep of this document */

  TclXML_libxml2_DocumentHandling keep;
				/* how to handle document destruction */

  void *objs;			/* List of Tcl_Obj's that reference this document */

  ClientData dom;		/* Hook for TclDOM data */
  TclXML_libxml2Doc_FreeHookProc *domfree;
  ClientData apphook;		/* Application hook - not used by TclXML or TclDOM */
  TclXML_libxml2Doc_FreeHookProc *appfree;
} TclXML_libxml2_Document;

#endif /* TCLXML_LIBXML2_DOCOBJ_H */
