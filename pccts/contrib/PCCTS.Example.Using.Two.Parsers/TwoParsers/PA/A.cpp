/*
 * A n t l r  T r a n s l a t i o n  H e a d e r
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 *
 *   ..\..\..\bin\antlr.exe -emsvc -CC Pa\A.g -glms -o Pa
 *
 */

#define ANTLR_VERSION	13333
#include "pcctscfg.h"
#include "pccts_stdio.h"
#include "tokens.h"
#include "AParser.h"
#include "ParserA.h"
#include "DLexerBase.h"
#include "ATokPtr.h"

/* MR23 In order to remove calls to PURIFY use the antlr -nopurify option */

#ifndef PCCTS_PURIFY
#define PCCTS_PURIFY(r,s) memset((char *) &(r),'\0',(s));
#endif

#line 17 "Pa/A.g"

#include "AToken.h"
#include "DlgA.h"

typedef ANTLRCommonToken ANTLRToken;

void
ParserA::statement(void)
{
#line 35 "Pa/A.g"
  zzRULE;
  ANTLRTokenPtr n=NULL, w=NULL, o=NULL;
#line 39 "Pa/A.g"
  {
    for (;;) {
      if ( !((setwd1[LA(1)]&0x1))) break;
      if ( (LA(1)==Number) ) {
#line 36 "Pa/A.g"
        zzmatch(Number);
        n = (ANTLRTokenPtr)LT(1);

#line 36 "Pa/A.g"
        fprintf(stdout,"Number: %s\n", n->getText());
 consume();
      }
      else {
        if ( (LA(1)==Word) ) {
#line 37 "Pa/A.g"
          zzmatch(Word);
          w = (ANTLRTokenPtr)LT(1);

#line 37 "Pa/A.g"
          fprintf(stdout,"Word: %s\n", w->getText());
 consume();
        }
        else {
          if ( (LA(1)==Other) ) {
#line 38 "Pa/A.g"
            zzmatch(Other);
            o = (ANTLRTokenPtr)LT(1);

#line 38 "Pa/A.g"
            fprintf(stdout,"Other: %s\n", o->getText());
 consume();
          }
          else break; /* MR6 code for exiting loop "for sure" */
        }
      }
    }
  }
#line 40 "Pa/A.g"
  zzmatch(Eof); consume();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd1, 0x2);
}
