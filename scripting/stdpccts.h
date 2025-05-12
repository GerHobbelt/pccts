#ifndef STDPCCTS_H
#define STDPCCTS_H
/*
 * stdpccts.h -- P C C T S  I n c l u d e
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 *
 *   ..\pccts\bin\antlr -emsvc -gd -gs -gh -e3 -cr -ga -k 2 -tab 2 -w2 -gk -rl 2000 script.g
 *
 */

#ifndef ANTLR_VERSION
#define ANTLR_VERSION	13333
#endif



#if defined(__TURBOC__)
#pragma warn -aus  /* unused assignment of 'xxx' */
#endif
#ifdef _MSC_VER
/* local variable is initialized but not referenced */
#pragma warning(disable : 4189)
#endif

#include "pcctscfg.h"
#include "pccts_stdio.h"

/* ------------------------------------------------------------------------- */
/*                        (C) copyright Insh_Allah                           */
/* ------------------------------------------------------------------------- */
/* $Logfile:: /PRJ_VC/XLIBS/TSC/src/tsc_main.c                             $ */
/* $Workfile:: tsc_main.c                                                  $ */
/* $Header:: /PRJ_VC/XLIBS/TSC/src/tsc_main.c 14    29/05/98 3:14p Hobbg   $ */
/* $Date:: 29/05/98 3:14p                                                  $ */
/* $Revision:: 14                                                          $ */
/* $Modtime:: 29/05/98 2:34p                                               $ */
/* $Author:: Hobbg                                                         $ */
/*
*  GNU IAS is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 1, or (at your option)
*  any later version.
*
*  GNU IAS is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with GNU IAS; see the file COPYING.  If not, write to
*  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
*
* $Log: /PRJ_VC/XLIBS/TSC/src/tsc_main.c $
*/
#if !defined(_NO_VSS_STRING) 
#if defined(_WIN32) && (defined(_MSC_VER) && (_MSC_VER > 800))
#pragma comment (exestr, "$Header: /PRJ_VC/XLIBS/TSC/src/tsc_main.c 14    29/05/98 3:14p Hobbg $" )
#endif
#endif
/* $NoKeywords: $ */
/* ------------------------------------------------------------------------- */

#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "attrib.h"
#include "set.h" /* needed by antlr.h [at least] */

#ifndef zzTRACE_RULES
#define zzTRACE_RULES
#endif
#define LL_K 2
#define EXCEPTION_HANDLING
#define NUM_SIGNALS 3
#define DEMAND_LOOK
#define zzSET_SIZE 20
#define zzTOKEN_COUNT 134
#ifndef zzTRACE_RULES
#define zzTRACE_RULES
#endif
#include "antlr.h"
#include "tokens.h"
#include "dlgdef.h"
#include "mode.h"
#endif
