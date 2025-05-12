/*
 * A n t l r  T r a n s l a t i o n  H e a d e r
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 *
 *   ..\pccts\bin\antlr -emsvc -gd -gs -gh -e3 -cr -ga -k 2 -tab 2 -w2 -gk -rl 2000 script.g
 *
 */



#if defined(__TURBOC__)
#pragma warn -aus  /* unused assignment of 'xxx' */
#endif
#ifdef _MSC_VER
/* local variable is initialized but not referenced */
#pragma warning(disable : 4189)
#endif

#define ANTLR_VERSION	13333
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

#define EXCEPTION_HANDLING
#define NUM_SIGNALS 3
#define LL_K 2
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

/* MR23 In order to remove calls to PURIFY use the antlr -nopurify option */

#ifndef PCCTS_PURIFY
#define PCCTS_PURIFY(r,s) memset((char *) &(r),'\0',(s));
#endif

ANTLR_INFO


#if defined(USER_ZZSYN)

/*
* as we use exceptions to handle errors, we might reduce the amount of 'unreachable code'
* by redefining zzsyn() and zzresynch() which are only referenced by
* the _fail: labels.
*
* Our embedded compiler isn't that awfully smart: unreachable code STAYS around :-((
*/

#if 0
#define zzsyn(text, tok, egroup, eset, etok, k, bad_text)              \
/* should never get here as we use exception handling */             \
assert(0)                                                            
#endif

#define zzresynch(s, t)                                                \
/* should never get here as we use exception handling */             \
assert(0)                                                            


#endif


static const char *signal2descr(int _signal)
{
  const char *s;

  switch (_signal)
  {
    case NoSignal:
    s = "NoSignal (PCCTS standard exception)";
    break;

    case MismatchedToken:
    s = "MismatchedToken (PCCTS standard exception)";
    break;

    case NoViableAlt:
    s = "NoViableAlt (PCCTS standard exception)";
    break;

    case NoSemViableAlt:
    s = "NoSemViableAlt (PCCTS standard exception)";
    break;

    case Unwind:
    s = "Unwind (PCCTS standard exception)";
    break;


    case UnsupportedStatement:
    s = "UnsupportedStatement (I_A exception extension)";
    break;

    case UnsupportedTypedef:
    s = "UnsupportedTypedef (I_A exception extension)";
    break;

    case UnsupportedInitialization:
    s = "UnsupportedInitialization (I_A exception extension)";
    break;


    default:
    {
      static char response[5+1+9];

      sprintf(response, "???(%d)", _signal);
      return response;
    }
  }
  return s;
}


void
#ifdef __USE_PROTOS
zzdflthandlers( int _signal, int *_retsignal )
#else
zzdflthandlers( _signal, _retsignal )
int _signal;
int *_retsignal;
#endif
{
  *_retsignal = NoSignal; /* [i_a] MR33 */
  switch ( _signal ) {
  case NoSignal: break;  /* MR7 */
  case MismatchedToken:
  case NoViableAlt:
  case NoSemViableAlt:
  case UnsupportedStatement:
  case UnsupportedTypedef:

    printf("ERROR: Global default exception handler\n"
    "       (token is '%s')\n"
    "       (signal is %s)\n"
    "       line: %d..%d, column: %d..%d\n"
    ,LATEXT(1)
    ,signal2descr(_signal)
    ,zzline
    ,zzreal_line
    ,zzendcol
    ,zzbegcol);

#if 0
    zzMissTok = zzaCur.token_id; /* zzMissTok = 0??? */
    zzFAIL(0
    ,&zzMissSet, &zzMissText, &zzBadTok, &zzBadText, &zzErrk);
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
#endif

    /* flush all: nobody can save you now :-) */
    zzconsumeUntilToken(SCRIPT_EOF);
    /* pass signal to caller */
    zzsetSignal(Unwind); /* replaces: zzexportSignal; */
    break;  /* MR7 */
  case Unwind:

    /* we've got that one covered already! */
    zzexportSignal;
    break;  /* MR7 */
  default :
    *_retsignal = _signal;
  }
}


void
#ifdef __USE_PROTOS
script(int *_retsignal)
#else
script(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"script");
  zzMake0;
  *_retsignal = NoSignal;
  {
    zzmatch_wsig(SCRIPT, _handler);
    title(&_signal); if (_signal) goto _handler;
    param_def_list(&_signal); if (_signal) goto _handler;
    sections(&_signal); if (_signal) goto _handler;
    zzmatch_wsig(ENDSCRIPT, _handler);
    zzmatch_wsig(SCRIPT_EOF, _handler);
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"script");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"script");
  return;
}

void
#ifdef __USE_PROTOS
title(int *_retsignal)
#else
title(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"title");
  zzMake0;
  *_retsignal = NoSignal;
  {
    zzmatch_wsig(VARIABLE, _handler);
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"title");
    return;
  }
  /* exception handlers */
_handler:
  *_retsignal = NoSignal; /* [i_a] MR33 */
  switch ( _signal ) {
  case NoSignal: break;  /* MR7 */
  case MismatchedToken:
  case NoViableAlt:
  case NoSemViableAlt:

    printf("ERROR: Expected a SCRIPT or SUBROUTINE TITLE\n"
    "       (token is '%s')\n"
    "       (signal is %s)\n"
    "       line: %d..%d, column: %d..%d\n"
    ,LATEXT(1)
    ,signal2descr(_signal)
    ,zzline
    ,zzreal_line
    ,zzendcol
    ,zzbegcol);

    /* pass signal to caller */
    zzsetSignal(Unwind); /* replaces: zzexportSignal; */
    break;  /* MR7 */
  case UnsupportedStatement:
  case UnsupportedTypedef:
  case Unwind:

    assert(!"May never happen!");
    zzexportSignal;
    break;  /* MR7 */
  default :
    zzdflthandlers(_signal,_retsignal);
  }
  _signal=*_retsignal; /* recover from exception iff the user didn't use zzsetSignal() or zzexportSignal -- [i_a] MR33 */
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"title");
  return;
}

void
#ifdef __USE_PROTOS
sections(int *_retsignal)
#else
sections(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"sections");
  zzMake0;
  *_retsignal = NoSignal;
  {
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        if ( (LA(1)==DEFINITIONS) ) {
          definitions(&_signal); if (_signal) goto _handler;
        }
        /* MR23 skip error clause for {...} when exceptions in use */
        zzEXIT(zztasp2);
      }
    }
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==SUBROUTINE) ) {
          subroutine(&_signal); if (_signal) goto _handler;
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        if ( (LA(1)==DECLARATIONS) ) {
          declarations(&_signal); if (_signal) goto _handler;
        }
        /* MR23 skip error clause for {...} when exceptions in use */
        zzEXIT(zztasp2);
      }
    }
    implementation(&_signal); if (_signal) goto _handler;
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"sections");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"sections");
  return;
}

void
#ifdef __USE_PROTOS
definitions(int *_retsignal)
#else
definitions(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"definitions");
  zzMake0;
  *_retsignal = NoSignal;
  {
    zzmatch_wsig(DEFINITIONS, _handler);
    {
      zzBLOCK(zztasp2);
      int zzcnt=1;
      zzMake0;
      {
        do {
          LOOK(1);
          if ( (
LA(1)==DEFINE) ) {
            structdef(&_signal); if (_signal) goto _handler;
          }
          else {
            if ( (LA(1)==CONST) ) {
              const_init_type_def(&_signal); if (_signal) goto _handler;
            }
            /* MR10 ()+ */ else {
              if ( zzcnt > 1 ) break;
              else {
                if (_sva) _signal=NoViableAlt;
                else _signal=NoSemViableAlt;
                goto _handler;  /* MR7 */
              }
            }
          }
          zzcnt++; zzLOOP(zztasp2);
          LOOK(1);
        } while ( 1 );
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"definitions");
    return;
  }
  /* exception handlers */
_handler:
  *_retsignal = NoSignal; /* [i_a] MR33 */
  switch ( _signal ) {
  case NoSignal: break;  /* MR7 */
  case MismatchedToken:
  case NoSemViableAlt:

    printf("ERROR: in DEFINITIONS section\n"
    "       (token is '%s')\n"
    "       (signal is %s)\n"
    "       line: %d..%d, column: %d..%d\n"
    ,LATEXT(1)
    ,signal2descr(_signal)
    ,zzline
    ,zzreal_line
    ,zzendcol
    ,zzbegcol);

    /* pass signal to caller */
    zzsetSignal(Unwind); /* replaces: zzexportSignal; */
    break;  /* MR7 */
  case NoViableAlt:

    printf("ERROR: in DEFINITIONS section\n"
    "       (token is '%s')\n"
    "       (signal is %s)\n"
    "       line: %d..%d, column: %d..%d\n"
    "       -- Did you at least enter ONE definition? If not, leave out\n"
    "          the DEFINITIONS header too! --\n"
    ,LATEXT(1)
    ,signal2descr(_signal)
    ,zzline
    ,zzreal_line
    ,zzendcol
    ,zzbegcol);

    /* pass signal to caller */
    zzsetSignal(Unwind); /* replaces: zzexportSignal; */
    break;  /* MR7 */
  case UnsupportedTypedef:

    printf("ERROR: Unsupported type definition found.\n"
    "       Currently we do not yet support statements\n"
    "       of type: DEFINE...AS...\n"
    "       (token is '%s')\n"
    "       (signal is %s)\n"
    "       line: %d..%d, column: %d..%d\n"
    ,LATEXT(1)
    ,signal2descr(_signal)
    ,zzline
    ,zzreal_line
    ,zzendcol
    ,zzbegcol);

    /* pass signal to caller */
    zzsetSignal(Unwind); /* replaces: zzexportSignal; */
    break;  /* MR7 */
  case UnsupportedInitialization:

    /* pass signal to caller */
    zzexportSignal;
    break;  /* MR7 */
  default :
    zzdflthandlers(_signal,_retsignal);
  }
  _signal=*_retsignal; /* recover from exception iff the user didn't use zzsetSignal() or zzexportSignal -- [i_a] MR33 */
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"definitions");
  return;
}

void
#ifdef __USE_PROTOS
structdef(int *_retsignal)
#else
structdef(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  Attrib def;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"structdef");
  zzMake0;
  *_retsignal = NoSignal;
  {
    zzsetSignal(UnsupportedTypedef);
    zzmatch_wsig(DEFINE, _handler);
    def = zzaCur;

    zzmatch_wsig(VARIABLE, _handler);
    zzmatch_wsig(AS, _handler);
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        if ( (LA(1)==ARRAY || 
LA(1)==BOOLEAN || LA(1)==INTEGER || LA(1)==REAL || LA(1)==STRING || LA(1)==VARIABLE) ) {
          type(&_signal); if (_signal) goto _handler;
        }
        else {
          if ( 
(LA(1)==STRUCT) ) {
            zzmatch_wsig(STRUCT, _handler);
            {
              zzBLOCK(zztasp3);
              int zzcnt=1;
              zzMake0;
              {
                do {
                  vardecl(&_signal); if (_signal) goto _handler;
                  zzLOOP(zztasp3);
                  LOOK(1);
                } while ( (LA(1)==VARIABLE) );
                zzEXIT(zztasp3);
              }
            }
            zzmatch_wsig(ENDSTRUCT, _handler);
          }
          else {
            if (_sva) _signal=NoViableAlt;
            else _signal=NoSemViableAlt;
            goto _handler;  /* MR7 */
          }
        }
        zzEXIT(zztasp2);
      }
    }
    zzmatch_wsig(SEMICOLON, _handler);
    zzcopy_attr(&zzaRet, & def); /* test code */
    
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"structdef");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"structdef");
  return;
}

void
#ifdef __USE_PROTOS
const_init_type_def(int *_retsignal)
#else
const_init_type_def(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"const_init_type_def");
  zzMake0;
  *_retsignal = NoSignal;
  {
    const_init_type(&_signal); if (_signal) goto _handler;
    zzmatch_wsig(SEMICOLON, _handler);
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"const_init_type_def");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"const_init_type_def");
  return;
}

void
#ifdef __USE_PROTOS
subroutine(int *_retsignal)
#else
subroutine(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"subroutine");
  zzMake0;
  *_retsignal = NoSignal;
  {
    zzsetSignal(UnsupportedStatement);
    zzmatch_wsig(SUBROUTINE, _handler);
    title(&_signal); if (_signal) goto _handler;
    param_def_list(&_signal); if (_signal) goto _handler;
    zzmatch_wsig(COLON, _handler);
    return_type(&_signal); if (_signal) goto _handler;
    sections(&_signal); if (_signal) goto _handler;
    zzmatch_wsig(ENDSUB, _handler);
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"subroutine");
    return;
  }
  /* exception handlers */
_handler:
  *_retsignal = NoSignal; /* [i_a] MR33 */
  switch ( _signal ) {
  case NoSignal: break;  /* MR7 */
  case UnsupportedStatement:

    printf("ERROR: Unsupported statement found.\n"
    "       Currently we do not yet support SUBROUTINES.\n"
    "       (token is '%s')\n"
    "       (signal is %s)\n"
    "       line: %d..%d, column: %d..%d\n"
    ,LATEXT(1)
    ,signal2descr(_signal)
    ,zzline
    ,zzreal_line
    ,zzendcol
    ,zzbegcol);

    zzconsumeUntilToken(ENDSUB);
    /* pass signal to caller */
    zzsetSignal(Unwind); /* replaces: zzexportSignal; */
    break;  /* MR7 */
  default :
    zzdflthandlers(_signal,_retsignal);
  }
  _signal=*_retsignal; /* recover from exception iff the user didn't use zzsetSignal() or zzexportSignal -- [i_a] MR33 */
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"subroutine");
  return;
}

void
#ifdef __USE_PROTOS
param_def_list(int *_retsignal)
#else
param_def_list(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"param_def_list");
  zzMake0;
  *_retsignal = NoSignal;
  {
    zzmatch_wsig(LPARENS, _handler);
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        if ( (LA(1)==TRIPLE_DOT || LA(1)==VARIABLE) ) {
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              LOOK(1);
              if ( 
(LA(1)==VARIABLE) ) {
                param_def(&_signal); if (_signal) goto _handler;
                {
                  zzBLOCK(zztasp4);
                  zzMake0;
                  {
                    LOOK(2);
                    while ( (LA(1)==COMMA) && (LA(2)==VARIABLE) ) {
                      zzmatch_wsig(COMMA, _handler);
                      param_def(&_signal); if (_signal) goto _handler;
                      zzLOOP(zztasp4);
                      LOOK(2);
                    }
                    zzEXIT(zztasp4);
                  }
                }
                {
                  zzBLOCK(zztasp4);
                  zzMake0;
                  {
                    LOOK(1);
                    if ( (LA(1)==COMMA) ) {
                      zzmatch_wsig(COMMA, _handler);
                      zzmatch_wsig(TRIPLE_DOT, _handler);
                    }
                    /* MR23 skip error clause for {...} when exceptions in use */
                    zzEXIT(zztasp4);
                  }
                }
              }
              else {
                if ( 
(LA(1)==TRIPLE_DOT) ) {
                  zzmatch_wsig(TRIPLE_DOT, _handler);
                }
                else {
                  if (_sva) _signal=NoViableAlt;
                  else _signal=NoSemViableAlt;
                  goto _handler;  /* MR7 */
                }
              }
              zzEXIT(zztasp3);
            }
          }
        }
        /* MR23 skip error clause for {...} when exceptions in use */
        zzEXIT(zztasp2);
      }
    }
    zzmatch_wsig(RPARENS, _handler);
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"param_def_list");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"param_def_list");
  return;
}

void
#ifdef __USE_PROTOS
param_def(int *_retsignal)
#else
param_def(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"param_def");
  zzMake0;
  *_retsignal = NoSignal;
  {
    zzmatch_wsig(VARIABLE, _handler);
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        if ( (LA(1)==COLON) ) {
          zzmatch_wsig(COLON, _handler);
          sub_param_type(&_signal); if (_signal) goto _handler;
        }
        /* MR23 skip error clause for {...} when exceptions in use */
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"param_def");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"param_def");
  return;
}

void
#ifdef __USE_PROTOS
declarations(int *_retsignal)
#else
declarations(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"declarations");
  zzMake0;
  *_retsignal = NoSignal;
  {
    zzmatch_wsig(DECLARATIONS, _handler);
    {
      zzBLOCK(zztasp2);
      int zzcnt=1;
      zzMake0;
      {
        do {
          vardecl(&_signal); if (_signal) goto _handler;
          zzLOOP(zztasp2);
          LOOK(1);
        } while ( (LA(1)==VARIABLE) );
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"declarations");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"declarations");
  return;
}

void
#ifdef __USE_PROTOS
vardecl(int *_retsignal)
#else
vardecl(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"vardecl");
  zzMake0;
  *_retsignal = NoSignal;
  {
    zzmatch_wsig(VARIABLE, _handler);
    zzmatch_wsig(COLON, _handler);
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        if ( (LA(1)==ARRAY || LA(1)==BOOLEAN || 
LA(1)==INTEGER || LA(1)==REAL || LA(1)==STRING || LA(1)==VARIABLE) ) {
          type(&_signal); if (_signal) goto _handler;
        }
        else {
          if ( (
LA(1)==CONST) ) {
            const_init_type(&_signal); if (_signal) goto _handler;
          }
          else {
            if (_sva) _signal=NoViableAlt;
            else _signal=NoSemViableAlt;
            goto _handler;  /* MR7 */
          }
        }
        zzEXIT(zztasp2);
      }
    }
    zzmatch_wsig(SEMICOLON, _handler);
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"vardecl");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"vardecl");
  return;
}

void
#ifdef __USE_PROTOS
sub_param_type(int *_retsignal)
#else
sub_param_type(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"sub_param_type");
  zzMake0;
  *_retsignal = NoSignal;
  {
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        if ( (LA(1)==CONST) ) {
          zzmatch_wsig(CONST, _handler);
        }
        /* MR23 skip error clause for {...} when exceptions in use */
        zzEXIT(zztasp2);
      }
    }
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        if ( (LA(1)==ARRAY || 
LA(1)==BOOLEAN || LA(1)==INTEGER || LA(1)==REAL || LA(1)==STRING || LA(1)==VARIABLE) ) {
          type(&_signal); if (_signal) goto _handler;
        }
        else {
          if ( 
(LA(1)==ANY) ) {
            zzmatch_wsig(ANY, _handler);
          }
          else {
            if (_sva) _signal=NoViableAlt;
            else _signal=NoSemViableAlt;
            goto _handler;  /* MR7 */
          }
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"sub_param_type");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"sub_param_type");
  return;
}

void
#ifdef __USE_PROTOS
return_type(int *_retsignal)
#else
return_type(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"return_type");
  zzMake0;
  *_retsignal = NoSignal;
  {
    LOOK(1);
    if ( (LA(1)==ARRAY || LA(1)==BOOLEAN || 
LA(1)==INTEGER || LA(1)==REAL || LA(1)==STRING || LA(1)==VARIABLE) ) {
      type(&_signal); if (_signal) goto _handler;
    }
    else {
      if ( (
LA(1)==VOID) ) {
        zzmatch_wsig(VOID, _handler);
      }
      else {
        if ( (LA(1)==ANY) ) {
          zzmatch_wsig(ANY, _handler);
        }
        else {
          if (_sva) _signal=NoViableAlt;
          else _signal=NoSemViableAlt;
          goto _handler;  /* MR7 */
        }
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"return_type");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"return_type");
  return;
}

void
#ifdef __USE_PROTOS
type(int *_retsignal)
#else
type(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"type");
  zzMake0;
  *_retsignal = NoSignal;
  {
    LOOK(1);
    if ( (LA(1)==BOOLEAN) ) {
      zzmatch_wsig(BOOLEAN, _handler);
    }
    else {
      if ( 
(LA(1)==INTEGER) ) {
        integer_type(&_signal); if (_signal) goto _handler;
      }
      else {
        if ( (LA(1)==REAL) ) {
          zzmatch_wsig(REAL, _handler);
        }
        else {
          if ( (
LA(1)==STRING) ) {
            zzmatch_wsig(STRING, _handler);
          }
          else {
            if ( (LA(1)==ARRAY) ) {
              zzmatch_wsig(ARRAY, _handler);
              zzmatch_wsig(OF, _handler);
              type(&_signal); if (_signal) goto _handler;
            }
            else {
              if ( (LA(1)==VARIABLE) ) {
                zzmatch_wsig(VARIABLE, _handler);
              }
              else {
                if (_sva) _signal=NoViableAlt;
                else _signal=NoSemViableAlt;
                goto _handler;  /* MR7 */
              }
            }
          }
        }
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"type");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"type");
  return;
}

void
#ifdef __USE_PROTOS
integer_type(int *_retsignal)
#else
integer_type(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"integer_type");
  zzMake0;
  *_retsignal = NoSignal;
  {
    zzmatch_wsig(INTEGER, _handler);
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        if ( 
(LA(1)==MULTIPLY) ) {
          zzmatch_wsig(MULTIPLY, _handler);
          zzmatch_wsig(INT_VALUE, _handler);
        }
        /* MR23 skip error clause for {...} when exceptions in use */
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"integer_type");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"integer_type");
  return;
}

void
#ifdef __USE_PROTOS
const_init_type(int *_retsignal)
#else
const_init_type(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"const_init_type");
  zzMake0;
  *_retsignal = NoSignal;
  {
    LOOK(2);
    if ( (LA(1)==CONST) && (
LA(2)==INTEGER) ) {
      zzmatch_wsig(CONST, _handler);
      integer_type(&_signal); if (_signal) goto _handler;
      zzmatch_wsig(ASSIGN, _handler);
      zzmatch_wsig(INT_VALUE, _handler);
    }
    else {
      if ( (LA(1)==CONST) && (LA(2)==REAL) ) {
        zzmatch_wsig(CONST, _handler);
        zzmatch_wsig(REAL, _handler);
        zzmatch_wsig(ASSIGN, _handler);
        zzmatch_wsig(REAL_VALUE, _handler);
      }
      else {
        if ( (LA(1)==CONST) && 
(LA(2)==BOOLEAN) ) {
          zzmatch_wsig(CONST, _handler);
          zzmatch_wsig(BOOLEAN, _handler);
          zzmatch_wsig(ASSIGN, _handler);
          zzsetmatch_wsig(BOOLEAN_VALUE_set, _handler);
        }
        else {
          if ( (LA(1)==CONST) && (LA(2)==STRING) ) {
            zzmatch_wsig(CONST, _handler);
            zzmatch_wsig(STRING, _handler);
            zzmatch_wsig(ASSIGN, _handler);
            const_string_value(&_signal); if (_signal) goto _handler;
          }
          else {
            if ( (
LA(1)==CONST) && (LA(2)==VARIABLE) ) {
              zzmatch_wsig(CONST, _handler);
              zzmatch_wsig(VARIABLE, _handler);
              zzmatch_wsig(ASSIGN, _handler);
              zzmatch_wsig(INT_VALUE, _handler);
            }
            else {
              if (_sva) _signal=NoViableAlt;
              else _signal=NoSemViableAlt;
              goto _handler;  /* MR7 */
            }
          }
        }
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"const_init_type");
    return;
  }
  /* exception handlers */
_handler:
  *_retsignal = NoSignal; /* [i_a] MR33 */
  switch ( _signal ) {
  case NoSignal: break;  /* MR7 */
  case UnsupportedStatement:
  case UnsupportedTypedef:

    assert(!"May never get here!");
    break;  /* MR7 */
  case Unwind:

    /* pass signal to caller */
    zzexportSignal;
    break;  /* MR7 */
  case MismatchedToken:
  case NoViableAlt:
  case NoSemViableAlt:
  default:

    /* any erroneous initialization: no support for pre-initialized complex types! */
    zzsetSignal(UnsupportedInitialization); 

    printf("ERROR: Erroneous initialization: language only supports\n"
    "       CONSTants initialization of basic types:\n"
    "         INTEGER, REAL, BOOLEAN, STRING\n"
    "       (token is '%s')\n"
    "       (signal is %s)\n"
    "       line: %d..%d, column: %d..%d\n"
    ,LATEXT(1)
    ,signal2descr(_signal)
    ,zzline
    ,zzreal_line
    ,zzendcol
    ,zzbegcol);

    /* pass signal to caller */
    zzsetSignal(Unwind); /* replaces: zzexportSignal; */
    /* _signal=NoSignal; */ /* MR7 -- changed by [i_a] MR33 */
    break;  /* MR7 */
  }
  _signal=*_retsignal; /* default behaviour: exception recovered iff the user didn't use zzsetSignal() or zzexportSignal -- [i_a] MR33 */
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"const_init_type");
  return;
}

void
#ifdef __USE_PROTOS
const_string_value(int *_retsignal)
#else
const_string_value(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  Attrib str;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"const_string_value");
  zzMake0;
  *_retsignal = NoSignal;
  {

    zzaRet.token_id = 5000;
    zzaRet.token_descr = "const_string_value";
    zzaRet.string_value = "";
    zzaRet.dupped_string_value = strdup("");
    {
      zzBLOCK(zztasp2);
      int zzcnt=1;
      zzMake0;
      {
        do {
          zzmatch_wsig(STRING_VALUE, _handler);
          str = zzaCur;


          zzaRet.token_id++;
          zzaRet.string_value =  str.string_value;
          {
            int len = strlen(zzaRet.dupped_string_value)
            + strlen( str.dupped_string_value) 
            + 1;

            zzaRet.dupped_string_value = realloc(zzaRet.dupped_string_value, len);
            if (zzaRet.dupped_string_value == NULL)
            {
              /* failure --> exception! */
              zzsetSignal(UnsupportedInitialization); /* fake and incorrect! */
              /* goto _handler; ???????????????? */
            }
            else
            {
              strcat(zzaRet.dupped_string_value,  str.dupped_string_value);
            }
          }
          
          zzLOOP(zztasp2);
          LOOK(1);
        } while ( (LA(1)==STRING_VALUE) );
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"const_string_value");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"const_string_value");
  return;
}

void
#ifdef __USE_PROTOS
implementation(int *_retsignal)
#else
implementation(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"implementation");
  zzMake0;
  *_retsignal = NoSignal;
  {
    zzmatch_wsig(IMPLEMENTATION, _handler);
    TRACE(("start of implementation"));
    
    {
      zzBLOCK(zztasp2);
      int zzcnt=1;
      zzMake0;
      {
        do {
          statement(&_signal); if (_signal) goto _handler;
          zzLOOP(zztasp2);
          LOOK(1);
        } while ( (LA(1)==BREAK || LA(1)==CONTINUE || LA(1)==GOTO || LA(1)==HALT || 
LA(1)==IF || LA(1)==REPEAT || LA(1)==RESET || LA(1)==RETURN || LA(1)==VOID || 
LA(1)==WHILE || LA(1)==BEGIN || LA(1)==VARIABLE) );
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"implementation");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"implementation");
  return;
}

void
#ifdef __USE_PROTOS
statement(int *_retsignal)
#else
statement(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"statement");
  zzMake0;
  *_retsignal = NoSignal;
  {
    LOOK(2);
    if ( (LA(1)==VOID || 
LA(1)==VARIABLE) && (LA(2)==BOOLEAN_FALSE || LA(2)==BOOLEAN_TRUE || LA(2)==ASSIGN || 
LA(2)==ASSIGN_PLUS || LA(2)==ASSIGN_MINUS || LA(2)==ASSIGN_MULTIPLY || LA(2)==ASSIGN_DIVIDE || LA(2)==ASSIGN_MODULO || 
LA(2)==ASSIGN_POWER || LA(2)==ASSIGN_LSHIFT || LA(2)==ASSIGN_RSHIFT || LA(2)==ASSIGN_BITWISE_OR || LA(2)==ASSIGN_BITWISE_AND || 
LA(2)==ASSIGN_BITWISE_XOR || LA(2)==ASSIGN_BOOLEAN_OR || LA(2)==ASSIGN_BOOLEAN_AND || LA(2)==BITWISE_NOT || LA(2)==MINUS || 
LA(2)==PLUS || LA(2)==BOOLEAN_NOT || LA(2)==LPARENS || LA(2)==LBRACKET || LA(2)==DOT || 
LA(2)==STRING_VALUE || LA(2)==INT_VALUE || LA(2)==REAL_VALUE || LA(2)==VARIABLE) ) {
      assignment_statement(&_signal); if (_signal) goto _handler;
    }
    else {
      if ( (LA(1)==IF) ) {
        conditional_statement(&_signal); if (_signal) goto _handler;
      }
      else {
        if ( 
(LA(1)==REPEAT || LA(1)==WHILE) ) {
          loop_statement(&_signal); if (_signal) goto _handler;
        }
        else {
          if ( (LA(1)==BEGIN) ) {
            block_statement(&_signal); if (_signal) goto _handler;
          }
          else {
            if ( 
(LA(1)==RETURN) ) {
              return_statement(&_signal); if (_signal) goto _handler;
            }
            else {
              if ( (LA(1)==BREAK || LA(1)==CONTINUE) ) {
                break_statement(&_signal); if (_signal) goto _handler;
              }
              else {
                if ( 
(LA(1)==GOTO || LA(1)==VARIABLE) && (LA(2)==COLON || 
LA(2)==VARIABLE) ) {
                  label_statement(&_signal); if (_signal) goto _handler;
                }
                else {
                  if ( (LA(1)==HALT || LA(1)==RESET) ) {
                    special_statement(&_signal); if (_signal) goto _handler;
                  }
                  else {
                    if (_sva) _signal=NoViableAlt;
                    else _signal=NoSemViableAlt;
                    goto _handler;  /* MR7 */
                  }
                }
              }
            }
          }
        }
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"statement");
    return;
  }
  /* exception handlers */
_handler:
  *_retsignal = NoSignal; /* [i_a] MR33 */
  switch ( _signal ) {
  case NoSignal: break;  /* MR7 */
  case UnsupportedStatement:

    printf("ERROR: Unsupported statement found.\n"
    "       Currently we do not yet support statements\n"
    "       of type: RETURN, BREAK, CONTINUE, GOTO or <label>:\n"
    "       (token is '%s')\n"
    "       (signal is %s)\n"
    "       line: %d..%d, column: %d..%d\n"
    ,LATEXT(1)
    ,signal2descr(_signal)
    ,zzline
    ,zzreal_line
    ,zzendcol
    ,zzbegcol);

    zzconsumeUntilToken(SEMICOLON);
    /* pass signal to caller */
    zzsetSignal(Unwind); /* replaces: zzexportSignal; */
    break;  /* MR7 */
  default :
    zzdflthandlers(_signal,_retsignal);
  }
  _signal=*_retsignal; /* recover from exception iff the user didn't use zzsetSignal() or zzexportSignal -- [i_a] MR33 */
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"statement");
  return;
}

void
#ifdef __USE_PROTOS
return_statement(int *_retsignal)
#else
return_statement(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"return_statement");
  zzMake0;
  *_retsignal = NoSignal;
  {
    zzsetSignal(UnsupportedStatement);
    zzmatch_wsig(RETURN, _handler);
    zzmatch_wsig(SEMICOLON, _handler);
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"return_statement");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"return_statement");
  return;
}

void
#ifdef __USE_PROTOS
label_statement(int *_retsignal)
#else
label_statement(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"label_statement");
  zzMake0;
  *_retsignal = NoSignal;
  {
    zzsetSignal(UnsupportedStatement);
    LOOK(1);
    if ( (LA(1)==VARIABLE) ) {
      zzmatch_wsig(VARIABLE, _handler);
      zzmatch_wsig(COLON, _handler);
    }
    else {
      if ( 
(LA(1)==GOTO) ) {
        zzmatch_wsig(GOTO, _handler);
        zzmatch_wsig(VARIABLE, _handler);
        zzmatch_wsig(SEMICOLON, _handler);
      }
      else {
        if (_sva) _signal=NoViableAlt;
        else _signal=NoSemViableAlt;
        goto _handler;  /* MR7 */
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"label_statement");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"label_statement");
  return;
}

void
#ifdef __USE_PROTOS
break_statement(int *_retsignal)
#else
break_statement(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"break_statement");
  zzMake0;
  *_retsignal = NoSignal;
  {
    zzsetSignal(UnsupportedStatement);
    LOOK(1);
    if ( (LA(1)==BREAK) ) {
      zzmatch_wsig(BREAK, _handler);
      zzmatch_wsig(SEMICOLON, _handler);
    }
    else {
      if ( (
LA(1)==CONTINUE) ) {
        zzmatch_wsig(CONTINUE, _handler);
        zzmatch_wsig(SEMICOLON, _handler);
      }
      else {
        if (_sva) _signal=NoViableAlt;
        else _signal=NoSemViableAlt;
        goto _handler;  /* MR7 */
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"break_statement");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"break_statement");
  return;
}

void
#ifdef __USE_PROTOS
special_statement(int *_retsignal)
#else
special_statement(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"special_statement");
  zzMake0;
  *_retsignal = NoSignal;
  {
    LOOK(1);
    if ( (LA(1)==RESET) ) {
      zzmatch_wsig(RESET, _handler);
      zzmatch_wsig(SEMICOLON, _handler);
      TRACE(("RESET() opcode"));
      
    }
    else {
      if ( (LA(1)==HALT) ) {
        zzmatch_wsig(HALT, _handler);
        zzmatch_wsig(SEMICOLON, _handler);
        TRACE(("HALT() opcode"));
        
      }
      else {
        if (_sva) _signal=NoViableAlt;
        else _signal=NoSemViableAlt;
        goto _handler;  /* MR7 */
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"special_statement");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"special_statement");
  return;
}

void
#ifdef __USE_PROTOS
assignment_statement(int *_retsignal)
#else
assignment_statement(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  Attrib op;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"assignment_statement");
  zzMake0;
  *_retsignal = NoSignal;
  {
    LOOK(1);
    if ( 
(LA(1)==VARIABLE) ) {
      lvalue_expr(&_signal); if (_signal) goto _handler;
      TRACE(("assignment: calculate reference to lvalue"));
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
          LOOK(1);
          if ( (LA(1)==ASSIGN || LA(1)==ASSIGN_PLUS || 
LA(1)==ASSIGN_MINUS || LA(1)==ASSIGN_MULTIPLY || LA(1)==ASSIGN_DIVIDE || LA(1)==ASSIGN_MODULO || LA(1)==ASSIGN_POWER || 
LA(1)==ASSIGN_LSHIFT || LA(1)==ASSIGN_RSHIFT || LA(1)==ASSIGN_BITWISE_OR || LA(1)==ASSIGN_BITWISE_AND || LA(1)==ASSIGN_BITWISE_XOR || 
LA(1)==ASSIGN_BOOLEAN_OR || LA(1)==ASSIGN_BOOLEAN_AND) ) {
            zzsetmatch_wsig(ASSIGNMENT_set, _handler);
            op = zzaCur;


            TRACE(("assignment op: %d [%s] text: \"%s\", dupped: \"%s\"\n"
            ,  op.token_id
            ,  op.token_descr
            ,  op.string_value
            ,  op.dupped_string_value
            ));
            
            rvalue_expr(&_signal); if (_signal) goto _handler;
            TRACE(("assignment: store(accu) in lvalue location"));
          }
          else {
            if ( (LA(1)==PLUS) ) {
              zzmatch_wsig(PLUS, _handler);
              zzmatch_wsig(PLUS, _handler);
              TRACE(("assignment: '++' => increment lvalue"));
              
            }
            else {
              if ( (
LA(1)==MINUS) ) {
                zzmatch_wsig(MINUS, _handler);
                zzmatch_wsig(MINUS, _handler);
                TRACE(("assignment: '--' => decrement lvalue"));
                
              }
              else {
                if (_sva) _signal=NoViableAlt;
                else _signal=NoSemViableAlt;
                goto _handler;  /* MR7 */
              }
            }
          }
          zzEXIT(zztasp2);
        }
      }
      zzmatch_wsig(SEMICOLON, _handler);
      TRACE(("end of assignment"));
      
    }
    else {
      if ( (LA(1)==VOID) ) {
        zzmatch_wsig(VOID, _handler);
        rvalue_expr(&_signal); if (_signal) goto _handler;
        zzmatch_wsig(SEMICOLON, _handler);
        TRACE(("assignment: void => discard (accu)"));
        
      }
      else {
        if (_sva) _signal=NoViableAlt;
        else _signal=NoSemViableAlt;
        goto _handler;  /* MR7 */
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"assignment_statement");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"assignment_statement");
  return;
}

void
#ifdef __USE_PROTOS
conditional_statement(int *_retsignal)
#else
conditional_statement(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"conditional_statement");
  zzMake0;
  *_retsignal = NoSignal;
  {
    zzmatch_wsig(IF, _handler);
    TRACE(("start of if() mark"));
    
    bracketed_conditional_expr(&_signal); if (_signal) goto _handler;
    TRACE(("if(): if (accu != 0: execute block"));
    block_statement(&_signal); if (_signal) goto _handler;
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==ELIF) ) {
          zzmatch_wsig(ELIF, _handler);
          TRACE(("start of elif() mark"));
          
          bracketed_conditional_expr(&_signal); if (_signal) goto _handler;
          TRACE(("elif(): if (accu != 0: execute block"));
          block_statement(&_signal); if (_signal) goto _handler;
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        if ( (LA(1)==ELSE) ) {
          zzmatch_wsig(ELSE, _handler);
          TRACE(("start of else() mark"));
          
          block_statement(&_signal); if (_signal) goto _handler;
        }
        /* MR23 skip error clause for {...} when exceptions in use */
        zzEXIT(zztasp2);
      }
    }
    zzmatch_wsig(ENDIF, _handler);
    zzmatch_wsig(SEMICOLON, _handler);
    TRACE(("end of if() mark"));
    
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"conditional_statement");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"conditional_statement");
  return;
}

void
#ifdef __USE_PROTOS
loop_statement(int *_retsignal)
#else
loop_statement(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"loop_statement");
  zzMake0;
  *_retsignal = NoSignal;
  {
    LOOK(1);
    if ( (
LA(1)==WHILE) ) {
      zzmatch_wsig(WHILE, _handler);
      TRACE(("start loop mark"));
      
      bracketed_conditional_expr(&_signal); if (_signal) goto _handler;
      TRACE(("start loop: if (accu != 0: continue executing loop"));
      zzmatch_wsig(DO, _handler);
      block_statement(&_signal); if (_signal) goto _handler;
      zzmatch_wsig(DONE, _handler);
      zzmatch_wsig(SEMICOLON, _handler);
      TRACE(("end loop mark"));
      
    }
    else {
      if ( (LA(1)==REPEAT) ) {
        zzmatch_wsig(REPEAT, _handler);
        TRACE(("start loop mark"));
        
        block_statement(&_signal); if (_signal) goto _handler;
        zzmatch_wsig(UNTIL, _handler);
        bracketed_conditional_expr(&_signal); if (_signal) goto _handler;
        TRACE(("end loop: if (accu == 0: continue executing loop"));
        zzmatch_wsig(SEMICOLON, _handler);
        TRACE(("end loop mark"));
        
      }
      else {
        if (_sva) _signal=NoViableAlt;
        else _signal=NoSemViableAlt;
        goto _handler;  /* MR7 */
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"loop_statement");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"loop_statement");
  return;
}

void
#ifdef __USE_PROTOS
bracketed_conditional_expr(int *_retsignal)
#else
bracketed_conditional_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"bracketed_conditional_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    zzmatch_wsig(LPARENS, _handler);
    rvalue_expr(&_signal); if (_signal) goto _handler;
    zzmatch_wsig(RPARENS, _handler);
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"bracketed_conditional_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"bracketed_conditional_expr");
  return;
}

void
#ifdef __USE_PROTOS
block_statement(int *_retsignal)
#else
block_statement(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"block_statement");
  zzMake0;
  *_retsignal = NoSignal;
  {
    zzmatch_wsig(BEGIN, _handler);
    {
      zzBLOCK(zztasp2);
      int zzcnt=1;
      zzMake0;
      {
        do {
          statement(&_signal); if (_signal) goto _handler;
          zzLOOP(zztasp2);
          LOOK(1);
        } while ( (LA(1)==BREAK || LA(1)==CONTINUE || LA(1)==GOTO || LA(1)==HALT || 
LA(1)==IF || LA(1)==REPEAT || LA(1)==RESET || LA(1)==RETURN || LA(1)==VOID || 
LA(1)==WHILE || LA(1)==BEGIN || LA(1)==VARIABLE) );
        zzEXIT(zztasp2);
      }
    }
    zzmatch_wsig(END, _handler);
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"block_statement");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"block_statement");
  return;
}

void
#ifdef __USE_PROTOS
lvalue_expr(int *_retsignal)
#else
lvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"lvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    elemental_variable(&_signal); if (_signal) goto _handler;
    TRACE(("lvalue determined"));
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"lvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"lvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
elemental_variable(int *_retsignal)
#else
elemental_variable(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  Attrib basevar;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"elemental_variable");
  zzMake0;
  *_retsignal = NoSignal;
  {
    zzmatch_wsig(VARIABLE, _handler);
    basevar = zzaCur;

    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==LBRACKET) ) {
          zzmatch_wsig(LBRACKET, _handler);
          rvalue_expr(&_signal); if (_signal) goto _handler;
          zzmatch_wsig(RBRACKET, _handler);
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==DOT) ) {
          zzmatch_wsig(DOT, _handler);
          zzmatch_wsig(VARIABLE, _handler);
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              LOOK(1);
              while ( (LA(1)==LBRACKET) ) {
                zzmatch_wsig(LBRACKET, _handler);
                rvalue_expr(&_signal); if (_signal) goto _handler;
                zzmatch_wsig(RBRACKET, _handler);
                zzLOOP(zztasp3);
                LOOK(1);
              }
              zzEXIT(zztasp3);
            }
          }
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }

    TRACE(("load(element); var='%s'; "
    "no array or struct element decoding yet"
    , basevar.dupped_string_value));
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"elemental_variable");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"elemental_variable");
  return;
}

void
#ifdef __USE_PROTOS
rvalue_expr(int *_retsignal)
#else
rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    compare_or_rvalue_expr(&_signal); if (_signal) goto _handler;
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
compare_or_rvalue_expr(int *_retsignal)
#else
compare_or_rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"compare_or_rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    compare_and_rvalue_expr(&_signal); if (_signal) goto _handler;
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==BOOLEAN_OR) ) {
          zzmatch_wsig(BOOLEAN_OR, _handler);
          TRACE(("push(accu): left hand operand"));
          
          compare_and_rvalue_expr(&_signal); if (_signal) goto _handler;
          TRACE(("BOOLEAN_OR(accu, pop()) -> accu"));
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"compare_or_rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"compare_or_rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
compare_and_rvalue_expr(int *_retsignal)
#else
compare_and_rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"compare_and_rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    bitwise_or_rvalue_expr(&_signal); if (_signal) goto _handler;
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==BOOLEAN_AND) ) {
          zzmatch_wsig(BOOLEAN_AND, _handler);
          TRACE(("push(accu): left hand operand"));
          
          bitwise_or_rvalue_expr(&_signal); if (_signal) goto _handler;
          TRACE(("BOOLEAN_AND(accu, pop()) -> accu"));
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"compare_and_rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"compare_and_rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
bitwise_or_rvalue_expr(int *_retsignal)
#else
bitwise_or_rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"bitwise_or_rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    bitwise_xor_rvalue_expr(&_signal); if (_signal) goto _handler;
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==BITWISE_OR) ) {
          zzmatch_wsig(BITWISE_OR, _handler);
          TRACE(("push(accu): left hand operand"));
          
          bitwise_xor_rvalue_expr(&_signal); if (_signal) goto _handler;
          TRACE(("BITWISE_OR(accu, pop()) -> accu"));
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"bitwise_or_rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"bitwise_or_rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
bitwise_xor_rvalue_expr(int *_retsignal)
#else
bitwise_xor_rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"bitwise_xor_rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    bitwise_and_rvalue_expr(&_signal); if (_signal) goto _handler;
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==BITWISE_XOR) ) {
          zzmatch_wsig(BITWISE_XOR, _handler);
          TRACE(("push(accu): left hand operand"));
          
          bitwise_and_rvalue_expr(&_signal); if (_signal) goto _handler;
          TRACE(("BITWISE_XOR(accu, pop()) -> accu"));
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"bitwise_xor_rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"bitwise_xor_rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
bitwise_and_rvalue_expr(int *_retsignal)
#else
bitwise_and_rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"bitwise_and_rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    compare_ne_rvalue_expr(&_signal); if (_signal) goto _handler;
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==BITWISE_AND) ) {
          zzmatch_wsig(BITWISE_AND, _handler);
          TRACE(("push(accu): left hand operand"));
          
          compare_ne_rvalue_expr(&_signal); if (_signal) goto _handler;
          TRACE(("BITWISE_AND(accu, pop()) -> accu"));
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"bitwise_and_rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"bitwise_and_rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
compare_ne_rvalue_expr(int *_retsignal)
#else
compare_ne_rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"compare_ne_rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    compare_eq_rvalue_expr(&_signal); if (_signal) goto _handler;
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==NE) ) {
          zzmatch_wsig(NE, _handler);
          TRACE(("push(accu): left hand operand"));
          
          compare_eq_rvalue_expr(&_signal); if (_signal) goto _handler;
          TRACE(("NE?(accu, pop()) -> accu"));
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"compare_ne_rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"compare_ne_rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
compare_eq_rvalue_expr(int *_retsignal)
#else
compare_eq_rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"compare_eq_rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    compare_ge_rvalue_expr(&_signal); if (_signal) goto _handler;
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==EQ) ) {
          zzmatch_wsig(EQ, _handler);
          TRACE(("push(accu): left hand operand"));
          
          compare_ge_rvalue_expr(&_signal); if (_signal) goto _handler;
          TRACE(("EQ?(accu, pop()) -> accu"));
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"compare_eq_rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"compare_eq_rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
compare_ge_rvalue_expr(int *_retsignal)
#else
compare_ge_rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"compare_ge_rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    compare_gt_rvalue_expr(&_signal); if (_signal) goto _handler;
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==GE) ) {
          zzmatch_wsig(GE, _handler);
          TRACE(("push(accu): left hand operand"));
          
          compare_gt_rvalue_expr(&_signal); if (_signal) goto _handler;
          TRACE(("GE?(accu, pop()) -> accu"));
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"compare_ge_rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"compare_ge_rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
compare_gt_rvalue_expr(int *_retsignal)
#else
compare_gt_rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"compare_gt_rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    compare_le_rvalue_expr(&_signal); if (_signal) goto _handler;
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==GT) ) {
          zzmatch_wsig(GT, _handler);
          TRACE(("push(accu): left hand operand"));
          
          compare_le_rvalue_expr(&_signal); if (_signal) goto _handler;
          TRACE(("GT?(accu, pop()) -> accu"));
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"compare_gt_rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"compare_gt_rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
compare_le_rvalue_expr(int *_retsignal)
#else
compare_le_rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"compare_le_rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    compare_lt_rvalue_expr(&_signal); if (_signal) goto _handler;
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==LE) ) {
          zzmatch_wsig(LE, _handler);
          TRACE(("push(accu): left hand operand"));
          
          compare_lt_rvalue_expr(&_signal); if (_signal) goto _handler;
          TRACE(("LE?(accu, pop()) -> accu"));
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"compare_le_rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"compare_le_rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
compare_lt_rvalue_expr(int *_retsignal)
#else
compare_lt_rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"compare_lt_rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    rshift_rvalue_expr(&_signal); if (_signal) goto _handler;
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==LT) ) {
          zzmatch_wsig(LT, _handler);
          TRACE(("push(accu): left hand operand"));
          
          rshift_rvalue_expr(&_signal); if (_signal) goto _handler;
          TRACE(("LT?(accu, pop()) -> accu"));
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"compare_lt_rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"compare_lt_rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
rshift_rvalue_expr(int *_retsignal)
#else
rshift_rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"rshift_rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    lshift_rvalue_expr(&_signal); if (_signal) goto _handler;
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==RSHIFT) ) {
          zzmatch_wsig(RSHIFT, _handler);
          TRACE(("push(accu): left hand operand"));
          
          lshift_rvalue_expr(&_signal); if (_signal) goto _handler;
          TRACE(("RSHIFT(accu, pop()) -> accu"));
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"rshift_rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"rshift_rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
lshift_rvalue_expr(int *_retsignal)
#else
lshift_rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"lshift_rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    substract_rvalue_expr(&_signal); if (_signal) goto _handler;
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==LSHIFT) ) {
          zzmatch_wsig(LSHIFT, _handler);
          TRACE(("push(accu): left hand operand"));
          
          substract_rvalue_expr(&_signal); if (_signal) goto _handler;
          TRACE(("LSHIFT(accu, pop()) -> accu"));
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"lshift_rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"lshift_rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
substract_rvalue_expr(int *_retsignal)
#else
substract_rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"substract_rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    add_rvalue_expr(&_signal); if (_signal) goto _handler;
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==MINUS) ) {
          zzmatch_wsig(MINUS, _handler);
          TRACE(("push(accu): left hand operand"));
          
          add_rvalue_expr(&_signal); if (_signal) goto _handler;
          TRACE(("MINUS(accu, pop()) -> accu"));
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"substract_rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"substract_rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
add_rvalue_expr(int *_retsignal)
#else
add_rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"add_rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    modulo_rvalue_expr(&_signal); if (_signal) goto _handler;
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==PLUS) ) {
          zzmatch_wsig(PLUS, _handler);
          TRACE(("push(accu): left hand operand"));
          
          modulo_rvalue_expr(&_signal); if (_signal) goto _handler;
          TRACE(("PLUS(accu, pop()) -> accu"));
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"add_rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"add_rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
modulo_rvalue_expr(int *_retsignal)
#else
modulo_rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"modulo_rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    divide_rvalue_expr(&_signal); if (_signal) goto _handler;
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==MODULO) ) {
          zzmatch_wsig(MODULO, _handler);
          TRACE(("push(accu): left hand operand"));
          
          divide_rvalue_expr(&_signal); if (_signal) goto _handler;
          TRACE(("MODULO(accu, pop()) -> accu"));
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"modulo_rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"modulo_rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
divide_rvalue_expr(int *_retsignal)
#else
divide_rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"divide_rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    multiply_rvalue_expr(&_signal); if (_signal) goto _handler;
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==DIVIDE) ) {
          zzmatch_wsig(DIVIDE, _handler);
          TRACE(("push(accu): left hand operand"));
          
          multiply_rvalue_expr(&_signal); if (_signal) goto _handler;
          TRACE(("DIVIDE(accu, pop()) -> accu"));
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"divide_rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"divide_rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
multiply_rvalue_expr(int *_retsignal)
#else
multiply_rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"multiply_rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    power_rvalue_expr(&_signal); if (_signal) goto _handler;
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==MULTIPLY) ) {
          zzmatch_wsig(MULTIPLY, _handler);
          TRACE(("push(accu): left hand operand"));
          
          power_rvalue_expr(&_signal); if (_signal) goto _handler;
          TRACE(("MULTIPLY(accu, pop()) -> accu"));
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"multiply_rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"multiply_rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
power_rvalue_expr(int *_retsignal)
#else
power_rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"power_rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    unary_rvalue_expr(&_signal); if (_signal) goto _handler;
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==POWER) ) {
          zzmatch_wsig(POWER, _handler);
          TRACE(("push(accu): left hand operand"));
          
          unary_rvalue_expr(&_signal); if (_signal) goto _handler;
          TRACE(("POWER(accu, pop()) -> accu"));
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"power_rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"power_rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
unary_rvalue_expr(int *_retsignal)
#else
unary_rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  Attrib op;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"unary_rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    LOOK(1);
    if ( (LA(1)==BOOLEAN_FALSE || LA(1)==BOOLEAN_TRUE || 
LA(1)==LPARENS || LA(1)==STRING_VALUE || LA(1)==INT_VALUE || LA(1)==REAL_VALUE || LA(1)==VARIABLE) ) {
      simple_rvalue_expr(&_signal); if (_signal) goto _handler;
    }
    else {
      if ( 
(LA(1)==BITWISE_NOT || LA(1)==MINUS || LA(1)==PLUS || LA(1)==BOOLEAN_NOT) ) {
        zzsetmatch_wsig(UNARY_OPERATOR_set, _handler);
        op = zzaCur;

        TRACE(("has: UNARY_OPERATOR: %s",  op.token_descr));
        
        unary_rvalue_expr(&_signal); if (_signal) goto _handler;
      }
      else {
        if (_sva) _signal=NoViableAlt;
        else _signal=NoSemViableAlt;
        goto _handler;  /* MR7 */
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"unary_rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"unary_rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
simple_rvalue_expr(int *_retsignal)
#else
simple_rvalue_expr(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  Attrib b, s, f;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"simple_rvalue_expr");
  zzMake0;
  *_retsignal = NoSignal;
  {
    LOOK(2);
    if ( 
(LA(1)==INT_VALUE) ) {
      zzmatch_wdfltsig(INT_VALUE,zzerr7);
      TRACE(("load(INT_VALUE)"));
      
    }
    else {
      if ( (LA(1)==REAL_VALUE) ) {
        zzmatch_wdfltsig(REAL_VALUE,zzerr8);
        TRACE(("load(REAL_VALUE)"));
        
      }
      else {
        if ( (
LA(1)==BOOLEAN_FALSE || LA(1)==BOOLEAN_TRUE) ) {
          zzsetmatch_wdfltsig(BOOLEAN_VALUE_set,(ANTLRTokenType)130,zzerr9);
          b = zzaCur;

          TRACE(("load(BOOL_VALUE): %s",  b.token_descr));
          
        }
        else {
          if ( (LA(1)==STRING_VALUE) ) {
            const_string_value(&_signal); if (_signal) goto _handler;
            s = zzaCur;
            TRACE(("load(STRING_VALUE): %s",  s.dupped_string_value));
          }
          else {
            if ( (
LA(1)==VARIABLE) && (LA(2)==BOOLEAN_AND || LA(2)==BOOLEAN_OR || LA(2)==BITWISE_AND || 
LA(2)==BITWISE_OR || LA(2)==BITWISE_XOR || LA(2)==LSHIFT || LA(2)==RSHIFT || LA(2)==GE || 
LA(2)==GT || LA(2)==EQ || LA(2)==LE || LA(2)==LT || LA(2)==NE || 
LA(2)==DIVIDE || LA(2)==MODULO || LA(2)==POWER || LA(2)==MINUS || LA(2)==PLUS || 
LA(2)==MULTIPLY || LA(2)==RPARENS || LA(2)==LBRACKET || LA(2)==RBRACKET || LA(2)==COMMA || 
LA(2)==DOT || LA(2)==SEMICOLON) ) {
              elemental_variable(&_signal); if (_signal) goto _handler;
              TRACE(("load(elemental_variable): must be in accu already!"));
            }
            else {
              if ( (LA(1)==VARIABLE) && (LA(2)==LPARENS) ) {
                zzmatch_wdfltsig(VARIABLE,zzerr10);
                f = zzaCur;

                TRACE(("prepare call to function %s",  f.dupped_string_value));
                
                zzmatch_wdfltsig(LPARENS,zzerr11);
                {
                  zzBLOCK(zztasp2);
                  zzMake0;
                  {
                    LOOK(1);
                    if ( (
LA(1)==BOOLEAN_FALSE || LA(1)==BOOLEAN_TRUE || LA(1)==BITWISE_NOT || LA(1)==MINUS || LA(1)==PLUS || 
LA(1)==BOOLEAN_NOT || LA(1)==LPARENS || LA(1)==STRING_VALUE || LA(1)==INT_VALUE || LA(1)==REAL_VALUE || 
LA(1)==VARIABLE) ) {
                      param_list(&_signal); if (_signal) goto _handler;
                    }
                    /* MR23 skip error clause for {...} when exceptions in use */
                    zzEXIT(zztasp2);
                  }
                }
                zzmatch_wdfltsig(RPARENS,zzerr12);
                TRACE(("call function %s",  f.dupped_string_value));
                
              }
              else {
                if ( (LA(1)==LPARENS) ) {
                  zzmatch_wdfltsig(LPARENS,zzerr13);
                  TRACE(("'(' before expression"));
                  
                  rvalue_expr(&_signal); if (_signal) goto _handler;
                  zzmatch_wdfltsig(RPARENS,zzerr14);
                  TRACE(("')' after expression; accu already loaded"));
                  
                }
                else {
                  if (_sva) _signal=NoViableAlt;
                  else _signal=NoSemViableAlt;
                  goto _handler;  /* MR7 */
                }
              }
            }
          }
        }
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"simple_rvalue_expr");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"simple_rvalue_expr");
  return;
}

void
#ifdef __USE_PROTOS
param_list(int *_retsignal)
#else
param_list(_retsignal)
int *_retsignal;
#endif
{
  zzRULE;
  int _sva=1;
  int _signal=NoSignal;
  zzBLOCK(zztasp1);
  zzTRACEIN((ANTLRChar *)"param_list");
  zzMake0;
  *_retsignal = NoSignal;
  {
    int cnt = 0;
    rvalue_expr(&_signal); if (_signal) goto _handler;
    TRACE(("push(accu) -- as argument %d", ++cnt));
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        LOOK(1);
        while ( (LA(1)==COMMA) ) {
          zzmatch_wsig(COMMA, _handler);
          rvalue_expr(&_signal); if (_signal) goto _handler;
          TRACE(("push(accu) -- as argument %d", ++cnt));
          zzLOOP(zztasp2);
          LOOK(1);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    zzTRACEOUT((ANTLRChar *)"param_list");
    return;
  }
_handler:
  zzdflthandlers(_signal,_retsignal);
  if (_signal==NoSignal) {
    zzEXIT(zztasp1);
  }
  zzTRACEOUT((ANTLRChar *)"param_list");
  return;
}
