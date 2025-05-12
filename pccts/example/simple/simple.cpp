/*
 * A n t l r  T r a n s l a t i o n  H e a d e r
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 *
 *   ..\..\bin\antlr.exe -emsvc -CC simple.g -glms -ge -gs -gh -e3 -cr -ga -k 2 -tab 2 -gk -w2 -rl 200000 -emsvc
 *
 */

#define ANTLR_VERSION	13333
#include "pcctscfg.h"
#include "pccts_stdio.h"
#include "tokens.h"
#include "AParser.h"
#include "P.h"
#include "DLexerBase.h"
#include "ATokPtr.h"

/* MR23 In order to remove calls to PURIFY use the antlr -nopurify option */

#ifndef PCCTS_PURIFY
#define PCCTS_PURIFY(r,s) memset((char *) &(r),'\0',(s));
#endif

#line 18 "simple.g"

#include "AToken.h"
#include "DLGLexer.h"

typedef ANTLRCommonToken ANTLRToken;

int main() {

  fprintf(stdout,"A Simple Dev Studio Project for pccts 1.33mr15 - Version 3-Oct-1998\n"); 
  fprintf(stdout,"For use with Microsoft MSVC 5.0\n");
  fprintf(stdout,"\n");
  fprintf(stdout,"Sample input file in \"test.dat\"\n");
  fprintf(stdout,"\n");

  DLGFileInput		in(stdin);
  DLGLexer			lexer(&in,2000);
  ANTLRTokenBuffer	pipe(&lexer,1);
  ANTLRToken		aToken;
  P				parser(&pipe);

  lexer.setToken(&aToken);
  parser.init();
  parser.statement();
  fclose(stdin);
  fclose(stdout);
  return 0;
}

void
P::statement(void)
{
#line 57 "simple.g"
  zzRULE;
  ANTLRTokenPtr n=NULL, w=NULL, o=NULL;
#line 61 "simple.g"
  {
    /** #FirstSetSymbol(xxx) **/
    for (;;) {
      if ( !((LA(1)==Number || LA(1)==Word || LA(1)==Other))) break;
      if ( (
LA(1)==Number) ) {
#line 58 "simple.g"
        zzmatch(Number);
        n = (ANTLRTokenPtr)LT(1);

#line 58 "simple.g"
        fprintf(stdout,"Number: %s\n", n->getText());
 consume();
      }
      else {
        if ( (LA(1)==Word) ) {
#line 59 "simple.g"
          zzmatch(Word);
          w = (ANTLRTokenPtr)LT(1);

#line 59 "simple.g"
          fprintf(stdout,"Word: %s\n", w->getText());
 consume();
        }
        else {
          if ( (LA(1)==Other) ) {
#line 60 "simple.g"
            zzmatch(Other);
            o = (ANTLRTokenPtr)LT(1);

#line 60 "simple.g"
            fprintf(stdout,"Other: %s\n", o->getText());
 consume();
          }
          else break; /* MR6 code for exiting loop "for sure" */
        }
      }
    }
  }
#line 62 "simple.g"
  zzmatch(Eof); consume();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd1, 0x1);
}
