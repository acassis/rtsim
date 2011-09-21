/* 
 * tcldomxmlStubLib.c --
 *
 *	Stub object that will be statically linked into extensions that wish
 *	to access the TCLDOMXML API.
 *
 * Copyright (c) 2005 Explain
 * http://www.explain.com.au/
 * Copyright (c) 1998 Paul Duffin.
 * Copyright (c) 1998-1999 by Scriptics Corporation.
 *
 * See the file "license.terms" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 * RCS: @(#) $Id: tcldomlibxml2StubLib.c,v 1.2 2005/05/24 21:09:56 balls Exp $
 */

#ifndef USE_TCL_STUBS
#define USE_TCL_STUBS
#endif

#include <tcldom-libxml2/tcldomlibxml2.h>

Tcldom_libxml2Stubs *tcldom_libxml2StubsPtr;

/*
 *----------------------------------------------------------------------
 *
 * Tcldomxml_InitStubs --
 *
 *	Checks that the correct version of Blt is loaded and that it
 *	supports stubs. It then initialises the stub table pointers.
 *
 * Results:
 *	The actual version of BLT that satisfies the request, or
 *	NULL to indicate that an error occurred.
 *
 * Side effects:
 *	Sets the stub table pointers.
 *
 *----------------------------------------------------------------------
 */

#ifdef Tcldom_libxml2_InitStubs
#undef Tcldom_libxml2_InitStubs
#endif

CONST char *
Tcldom_libxml2_InitStubs(interp, version, exact)
    Tcl_Interp *interp;
    CONST char *version;
    int exact;
{
    CONST char *result;

    /* HACK: de-CONST 'version' if compiled against 8.3.
     * The API has no CONST despite not modifying the argument
     * And a debug build with high warning-level on windows
     * will abort the compilation.
     */

#if ((TCL_MAJOR_VERSION < 8) || ((TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION < 4)))
#define UNCONST (char*)
#else
#define UNCONST 
#endif

    result = Tcl_PkgRequireEx(interp, "dom::libxml2", UNCONST version, exact,
		(ClientData *) &tcldom_libxml2StubsPtr);
    if (!result || !tcldom_libxml2StubsPtr) {
        return (char *) NULL;
    }

    return result;
}
#undef UNCONST
