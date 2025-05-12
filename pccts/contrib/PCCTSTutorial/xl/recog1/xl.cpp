/*
 * A n t l r  T r a n s l a t i o n  H e a d e r
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 *
 *   ..\..\..\..\bin\antlr.exe -emsvc -CC -e3 -k 2 -gl xl.g
 *
 */

#define ANTLR_VERSION	13333
#include "pcctscfg.h"
#include "pccts_stdio.h"
#line 1 "xl.g"
#include "tokens.h"

// any definitions that you need in the generated files
#include "AParser.h"
#include "XLParser.h"
#include "DLexerBase.h"
#include "ATokPtr.h"

/* MR23 In order to remove calls to PURIFY use the antlr -nopurify option */

#ifndef PCCTS_PURIFY
#define PCCTS_PURIFY(r,s) memset((char *) &(r),'\0',(s));
#endif

#line 7 "xl.g"

// scanner definitions would go here
#include "DLexerBase.h"
#include "DLGLexer.h"
#include "AToken.h"
typedef ANTLRCommonToken ANTLRToken;

int main(int argc, char **argv)
{
  DLGFileInput in(stdin);
  DLGLexer scanner(&in);
  ANTLRTokenBuffer pipe(&scanner);
  ANTLRToken tok;
  scanner.setToken(&tok);
  XLParser xlParser(&pipe);

  xlParser.init(); // initialize
  xlParser.program(); // start first rule
  return 0;
}

void
XLParser::program(void)
{
#line 147 "xl.g"
  zzRULE;
#line 148 "xl.g"
  zzmatch(PROGRAM); consume();
#line 148 "xl.g"
  zzmatch(IDENT); consume();
#line 148 "xl.g"
  zzmatch(EQUALS); consume();
#line 149 "xl.g"
  subprogramBody();
#line 150 "xl.g"
  zzmatch(DOT); consume();
#line 151 "xl.g"
  zzmatch(1); consume();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd1, 0x1);
}

void
XLParser::subprogramBody(void)
{
#line 155 "xl.g"
  zzRULE;
#line 156 "xl.g"
  {
    while ( (setwd1[LA(1)]&0x2) ) {
#line 156 "xl.g"
      basicDecl();
    }
  }
#line 157 "xl.g"
  {
    while ( (LA(1)==PROCEDURE) ) {
#line 157 "xl.g"
      procedureDecl();
    }
  }
#line 158 "xl.g"
  zzmatch(BEGIN); consume();
#line 159 "xl.g"
  {
    while ( (setwd1[LA(1)]&0x4) && (setwd1[LA(2)]&0x8) && !( LA(1)==END && LA(2)==IDENT) ) {
#line 159 "xl.g"
      statement();
    }
  }
#line 160 "xl.g"
  zzmatch(END); consume();
#line 160 "xl.g"
  zzmatch(IDENT); consume();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd1, 0x10);
}

void
XLParser::basicDecl(void)
{
#line 164 "xl.g"
  zzRULE;
  if ( (LA(1)==VAR) ) {
#line 165 "xl.g"
    varDecl();
  }
  else {
    if ( (LA(1)==CONST) ) {
#line 166 "xl.g"
      constDecl();
    }
    else {
      if ( (LA(1)==TYPE) ) {
#line 167 "xl.g"
        typeDecl();
      }
      else {FAIL(1,err1,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd1, 0x20);
}

void
XLParser::varDecl(void)
{
#line 171 "xl.g"
  zzRULE;
#line 172 "xl.g"
  zzmatch(VAR); consume();
#line 172 "xl.g"
  identList();
#line 172 "xl.g"
  zzmatch(COLON); consume();
#line 172 "xl.g"
  typeName();
#line 173 "xl.g"
  {
    if ( (LA(1)==BECOMES) ) {
#line 173 "xl.g"
      zzmatch(BECOMES); consume();
#line 173 "xl.g"
      constantValue();
    }
    else {
      if ( 
(LA(1)==SEMI) ) {
      }
      else {FAIL(1,err2,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
#line 174 "xl.g"
  zzmatch(SEMI); consume();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd1, 0x40);
}

void
XLParser::constDecl(void)
{
#line 178 "xl.g"
  zzRULE;
#line 179 "xl.g"
  zzmatch(CONST); consume();
#line 179 "xl.g"
  identList();
#line 179 "xl.g"
  zzmatch(COLON); consume();
#line 179 "xl.g"
  typeName();
#line 180 "xl.g"
  zzmatch(BECOMES); consume();
#line 180 "xl.g"
  constantValue();
#line 180 "xl.g"
  zzmatch(SEMI); consume();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd1, 0x80);
}

void
XLParser::identList(void)
{
#line 185 "xl.g"
  zzRULE;
#line 186 "xl.g"
  zzmatch(IDENT); consume();
#line 186 "xl.g"
  {
    while ( (LA(1)==COMMA) ) {
#line 186 "xl.g"
      zzmatch(COMMA); consume();
#line 186 "xl.g"
      zzmatch(IDENT); consume();
    }
  }
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd2, 0x1);
}

void
XLParser::constantValue(void)
{
#line 190 "xl.g"
  zzRULE;
  if ( (LA(1)==INTLIT) ) {
#line 191 "xl.g"
    zzmatch(INTLIT); consume();
  }
  else {
    if ( (setwd2[LA(1)]&0x2) ) {
#line 192 "xl.g"
      zzsetmatch(STRING_LITERAL_set, STRING_LITERAL_errset); consume();
    }
    else {
      if ( (LA(1)==IDENT) ) {
#line 193 "xl.g"
        zzmatch(IDENT); consume();
      }
      else {FAIL(1,err5,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd2, 0x4);
}

void
XLParser::typeDecl(void)
{
#line 197 "xl.g"
  zzRULE;
#line 198 "xl.g"
  zzmatch(TYPE); consume();
#line 198 "xl.g"
  zzmatch(IDENT); consume();
#line 198 "xl.g"
  zzmatch(EQUALS); consume();
#line 199 "xl.g"
  {
    if ( (LA(1)==ARRAY) ) {
#line 199 "xl.g"
      arrayDecl();
    }
    else {
      if ( 
(LA(1)==RECORD) ) {
#line 200 "xl.g"
        recordDecl();
      }
      else {FAIL(1,err6,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
#line 202 "xl.g"
  zzmatch(SEMI); consume();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd2, 0x8);
}

void
XLParser::arrayDecl(void)
{
#line 206 "xl.g"
  zzRULE;
#line 207 "xl.g"
  zzmatch(ARRAY); consume();
#line 207 "xl.g"
  zzmatch(LBRACKET); consume();
#line 207 "xl.g"
  integerConstant();
#line 207 "xl.g"
  zzmatch(DOTDOT); consume();
#line 207 "xl.g"
  integerConstant();
#line 207 "xl.g"
  zzmatch(RBRACKET); consume();
#line 208 "xl.g"
  zzmatch(OF); consume();
#line 208 "xl.g"
  typeName();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd2, 0x10);
}

void
XLParser::integerConstant(void)
{
#line 211 "xl.g"
  zzRULE;
  if ( (LA(1)==INTLIT) ) {
#line 212 "xl.g"
    zzmatch(INTLIT); consume();
  }
  else {
    if ( (LA(1)==IDENT) ) {
#line 213 "xl.g"
      zzmatch(IDENT); consume();
    }
    else {FAIL(1,err7,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
  }
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd2, 0x20);
}

void
XLParser::recordDecl(void)
{
#line 217 "xl.g"
  zzRULE;
#line 218 "xl.g"
  zzmatch(RECORD); consume();
#line 218 "xl.g"
  {
    int zzcnt=1;
    do {
#line 218 "xl.g"
      identList();
#line 218 "xl.g"
      zzmatch(COLON); consume();
#line 218 "xl.g"
      typeName();
#line 218 "xl.g"
      zzmatch(SEMI); consume();
    } while ( (LA(1)==IDENT) );
  }
#line 218 "xl.g"
  zzmatch(END); consume();
#line 218 "xl.g"
  zzmatch(RECORD); consume();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd2, 0x40);
}

void
XLParser::typeName(void)
{
#line 222 "xl.g"
  zzRULE;
  if ( (LA(1)==IDENT) ) {
#line 223 "xl.g"
    zzmatch(IDENT); consume();
  }
  else {
    if ( (LA(1)==INTEGER) ) {
#line 224 "xl.g"
      zzmatch(INTEGER); consume();
    }
    else {
      if ( (LA(1)==BOOLEAN) ) {
#line 225 "xl.g"
        zzmatch(BOOLEAN); consume();
      }
      else {FAIL(1,err8,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd2, 0x80);
}

void
XLParser::procedureDecl(void)
{
#line 229 "xl.g"
  zzRULE;
#line 230 "xl.g"
  zzmatch(PROCEDURE); consume();
#line 230 "xl.g"
  zzmatch(IDENT); consume();
#line 230 "xl.g"
  {
    if ( (LA(1)==LPAREN) ) {
#line 230 "xl.g"
      formalParameters();
    }
    else {
      if ( 
(LA(1)==EQUALS) ) {
      }
      else {FAIL(1,err9,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
#line 230 "xl.g"
  zzmatch(EQUALS); consume();
#line 231 "xl.g"
  subprogramBody();
#line 232 "xl.g"
  zzmatch(SEMI); consume();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd3, 0x1);
}

void
XLParser::formalParameters(void)
{
#line 236 "xl.g"
  zzRULE;
#line 237 "xl.g"
  zzmatch(LPAREN); consume();
#line 237 "xl.g"
  parameterSpec();
#line 237 "xl.g"
  {
    while ( (LA(1)==SEMI) ) {
#line 237 "xl.g"
      zzmatch(SEMI); consume();
#line 237 "xl.g"
      parameterSpec();
    }
  }
#line 237 "xl.g"
  zzmatch(RPAREN); consume();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd3, 0x2);
}

void
XLParser::parameterSpec(void)
{
#line 241 "xl.g"
  zzRULE;
#line 242 "xl.g"
  {
    if ( (LA(1)==VAR) ) {
#line 242 "xl.g"
      zzmatch(VAR); consume();
    }
    else {
      if ( (LA(1)==IDENT) ) {
      }
      else {FAIL(1,err10,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
#line 242 "xl.g"
  identList();
#line 242 "xl.g"
  zzmatch(COLON); consume();
#line 242 "xl.g"
  typeName();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd3, 0x4);
}

void
XLParser::statement(void)
{
#line 245 "xl.g"
  zzRULE;
  if ( (LA(1)==EXIT) ) {
#line 246 "xl.g"
    exitStatement();
  }
  else {
    if ( (LA(1)==RETURN) ) {
#line 247 "xl.g"
      returnStatement();
    }
    else {
      if ( 
(LA(1)==IF) ) {
#line 248 "xl.g"
        ifStatement();
      }
      else {
        if ( (setwd3[LA(1)]&0x8) ) {
#line 249 "xl.g"
          loopStatement();
        }
        else {
          if ( (setwd3[LA(1)]&0x10) ) {
#line 250 "xl.g"
            ioStatement();
          }
          else {
            if ( (LA(1)==IDENT) && (setwd3[LA(2)]&0x20) ) {
#line 251 "xl.g"
              procedureCallStatement();
            }
            else {
              if ( (LA(1)==IDENT) && 
(setwd3[LA(2)]&0x40) ) {
#line 252 "xl.g"
                assignmentStatement();
              }
              else {
                if ( (LA(1)==END) ) {
#line 253 "xl.g"
                  endStatement();
                }
                else {FAIL(2,err11,err12,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
              }
            }
          }
        }
      }
    }
  }
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd3, 0x80);
}

void
XLParser::assignmentStatement(void)
{
#line 256 "xl.g"
  zzRULE;
#line 257 "xl.g"
  variableReference();
#line 257 "xl.g"
  zzmatch(BECOMES); consume();
#line 257 "xl.g"
  expression();
#line 257 "xl.g"
  zzmatch(SEMI); consume();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd4, 0x1);
}

void
XLParser::exitStatement(void)
{
#line 261 "xl.g"
  zzRULE;
#line 262 "xl.g"
  zzmatch(EXIT); consume();
#line 262 "xl.g"
  zzmatch(WHEN); consume();
#line 262 "xl.g"
  expression();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd4, 0x2);
}

void
XLParser::procedureCallStatement(void)
{
#line 265 "xl.g"
  zzRULE;
#line 266 "xl.g"
  zzmatch(IDENT); consume();
#line 266 "xl.g"
  {
    if ( (LA(1)==LPAREN) ) {
#line 266 "xl.g"
      actualParameters();
    }
    else {
      if ( (LA(1)==SEMI) ) {
      }
      else {FAIL(1,err13,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
#line 266 "xl.g"
  zzmatch(SEMI); consume();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd4, 0x4);
}

void
XLParser::actualParameters(void)
{
#line 269 "xl.g"
  zzRULE;
#line 270 "xl.g"
  zzmatch(LPAREN); consume();
#line 270 "xl.g"
  {
    if ( (setwd4[LA(1)]&0x8) ) {
#line 270 "xl.g"
      expression();
#line 270 "xl.g"
      {
        while ( (LA(1)==COMMA) ) {
#line 270 "xl.g"
          zzmatch(COMMA); consume();
#line 270 "xl.g"
          expression();
        }
      }
    }
    else {
      if ( (LA(1)==RPAREN) ) {
      }
      else {FAIL(1,err14,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
#line 270 "xl.g"
  zzmatch(RPAREN); consume();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd4, 0x10);
}

void
XLParser::returnStatement(void)
{
#line 274 "xl.g"
  zzRULE;
#line 275 "xl.g"
  zzmatch(RETURN); consume();
#line 275 "xl.g"
  zzmatch(SEMI); consume();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd4, 0x20);
}

void
XLParser::ifStatement(void)
{
#line 279 "xl.g"
  zzRULE;
#line 280 "xl.g"
  zzmatch(IF); consume();
#line 280 "xl.g"
  ifPart();
#line 280 "xl.g"
  zzmatch(END); consume();
#line 280 "xl.g"
  zzmatch(IF); consume();
#line 280 "xl.g"
  zzmatch(SEMI); consume();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd4, 0x40);
}

void
XLParser::ifPart(void)
{
#line 283 "xl.g"
  zzRULE;
#line 284 "xl.g"
  expression();
#line 284 "xl.g"
  zzmatch(THEN); consume();
#line 285 "xl.g"
  {
    while ( (setwd4[LA(1)]&0x80) && (setwd5[LA(2)]&0x1) && !( LA(1)==END && LA(2)==IF) ) {
#line 285 "xl.g"
      statement();
    }
  }
#line 286 "xl.g"
  {
    if ( (LA(1)==ELSIF) ) {
#line 286 "xl.g"
      zzmatch(ELSIF); consume();
#line 286 "xl.g"
      ifPart();
    }
    else {
      if ( (LA(1)==ELSE) ) {
#line 287 "xl.g"
        zzmatch(ELSE); consume();
#line 287 "xl.g"
        {
          while ( (setwd5[LA(1)]&0x2) && (setwd5[LA(2)]&0x4) && !( LA(1)==END && LA(2)==IF) ) {
#line 287 "xl.g"
            statement();
          }
        }
      }
      else {
        if ( (LA(1)==END) ) {
        }
        else {FAIL(1,err15,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
      }
    }
  }
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd5, 0x8);
}

void
XLParser::loopStatement(void)
{
#line 291 "xl.g"
  zzRULE;
#line 292 "xl.g"
  {
    if ( (LA(1)==WHILE) ) {
#line 292 "xl.g"
      zzmatch(WHILE); consume();
#line 292 "xl.g"
      expression();
    }
    else {
      if ( (LA(1)==LOOP) ) {
      }
      else {FAIL(1,err16,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
#line 292 "xl.g"
  zzmatch(LOOP); consume();
#line 293 "xl.g"
  {
    while ( (setwd5[LA(1)]&0x10) && (setwd5[LA(2)]&0x20) && !( LA(1)==END && LA(2)==LOOP) ) {
#line 293 "xl.g"
      statement();
    }
  }
#line 294 "xl.g"
  zzmatch(END); consume();
#line 294 "xl.g"
  zzmatch(LOOP); consume();
#line 294 "xl.g"
  zzmatch(SEMI); consume();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd5, 0x40);
}

void
XLParser::endStatement(void)
{
#line 297 "xl.g"
  zzRULE;
#line 298 "xl.g"
  zzmatch(END); consume();
#line 298 "xl.g"
  zzmatch(SEMI); consume();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd5, 0x80);
}

void
XLParser::variableReference(void)
{
#line 301 "xl.g"
  zzRULE;
#line 302 "xl.g"
  zzmatch(IDENT); consume();
#line 305 "xl.g"
  {
    for (;;) {
      if ( !((setwd6[LA(1)]&0x1))) break;
      if ( (LA(1)==LBRACKET) ) {
#line 303 "xl.g"
        zzmatch(LBRACKET); consume();
#line 303 "xl.g"
        expression();
#line 303 "xl.g"
        zzmatch(RBRACKET); consume();
      }
      else {
        if ( (LA(1)==DOT) ) {
#line 304 "xl.g"
          zzmatch(DOT); consume();
#line 304 "xl.g"
          zzmatch(IDENT); consume();
        }
        else break; /* MR6 code for exiting loop "for sure" */
      }
    }
  }
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd6, 0x2);
}

void
XLParser::ioStatement(void)
{
#line 310 "xl.g"
  zzRULE;
  if ( (LA(1)==PUT) ) {
#line 311 "xl.g"
    zzmatch(PUT); consume();
#line 311 "xl.g"
    zzmatch(LPAREN); consume();
#line 311 "xl.g"
    expression();
#line 311 "xl.g"
    zzmatch(RPAREN); consume();
#line 311 "xl.g"
    zzmatch(SEMI); consume();
  }
  else {
    if ( (LA(1)==GET) ) {
#line 312 "xl.g"
      zzmatch(GET); consume();
#line 312 "xl.g"
      zzmatch(LPAREN); consume();
#line 312 "xl.g"
      variableReference();
#line 312 "xl.g"
      zzmatch(RPAREN); consume();
#line 312 "xl.g"
      zzmatch(SEMI); consume();
    }
    else {
      if ( 
(LA(1)==NEWLINE) ) {
#line 313 "xl.g"
        zzmatch(NEWLINE); consume();
#line 313 "xl.g"
        {
          if ( (LA(1)==LPAREN) ) {
#line 313 "xl.g"
            zzmatch(LPAREN); consume();
#line 313 "xl.g"
            zzmatch(RPAREN); consume();
          }
          else {
            if ( (LA(1)==SEMI) ) {
            }
            else {FAIL(1,err17,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
          }
        }
#line 313 "xl.g"
        zzmatch(SEMI); consume();
      }
      else {
        if ( (LA(1)==SKIPLINE) ) {
#line 314 "xl.g"
          zzmatch(SKIPLINE); consume();
#line 314 "xl.g"
          {
            if ( (LA(1)==LPAREN) ) {
#line 314 "xl.g"
              zzmatch(LPAREN); consume();
#line 314 "xl.g"
              zzmatch(RPAREN); consume();
            }
            else {
              if ( 
(LA(1)==SEMI) ) {
              }
              else {FAIL(1,err18,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
            }
          }
#line 314 "xl.g"
          zzmatch(SEMI); consume();
        }
        else {FAIL(1,err19,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
      }
    }
  }
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd6, 0x4);
}

void
XLParser::primitiveElement(void)
{
#line 318 "xl.g"
  zzRULE;
  if ( (setwd6[LA(1)]&0x8) && (setwd6[LA(2)]&0x10) ) {
#line 319 "xl.g"
    constantValue();
  }
  else {
    if ( (LA(1)==IDENT) && (setwd6[LA(2)]&0x20) ) {
#line 320 "xl.g"
      variableReference();
    }
    else {
      if ( (LA(1)==LPAREN) ) {
#line 321 "xl.g"
        zzmatch(LPAREN); consume();
#line 321 "xl.g"
        expression();
#line 321 "xl.g"
        zzmatch(RPAREN); consume();
      }
      else {FAIL(2,err20,err21,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd6, 0x40);
}

void
XLParser::booleanNegationExpression(void)
{
#line 325 "xl.g"
  zzRULE;
#line 326 "xl.g"
  {
    while ( (LA(1)==NOT) ) {
#line 326 "xl.g"
      zzmatch(NOT); consume();
    }
  }
#line 326 "xl.g"
  primitiveElement();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd6, 0x80);
}

void
XLParser::signExpression(void)
{
#line 329 "xl.g"
  zzRULE;
#line 330 "xl.g"
  {
    while ( (setwd7[LA(1)]&0x1) ) {
#line 330 "xl.g"
      zzsetmatch(ADD_OP_set, ADD_OP_errset); consume();
    }
  }
#line 330 "xl.g"
  booleanNegationExpression();
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd7, 0x2);
}

void
XLParser::multiplyingExpression(void)
{
#line 334 "xl.g"
  zzRULE;
#line 335 "xl.g"
  signExpression();
#line 335 "xl.g"
  {
    while ( (setwd7[LA(1)]&0x4) ) {
#line 335 "xl.g"
      zzsetmatch(MULT_OP_set, MULT_OP_errset); consume();
#line 335 "xl.g"
      signExpression();
    }
  }
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd7, 0x8);
}

void
XLParser::addingExpression(void)
{
#line 338 "xl.g"
  zzRULE;
#line 339 "xl.g"
  multiplyingExpression();
#line 339 "xl.g"
  {
    while ( (setwd7[LA(1)]&0x10) ) {
#line 339 "xl.g"
      zzsetmatch(ADD_OP_set, ADD_OP_errset); consume();
#line 339 "xl.g"
      multiplyingExpression();
    }
  }
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd7, 0x20);
}

void
XLParser::relationalExpression(void)
{
#line 342 "xl.g"
  zzRULE;
#line 343 "xl.g"
  addingExpression();
#line 343 "xl.g"
  {
    while ( (setwd7[LA(1)]&0x40) ) {
#line 343 "xl.g"
      zzsetmatch(RELATIONAL_OP_set, RELATIONAL_OP_errset); consume();
#line 343 "xl.g"
      addingExpression();
    }
  }
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd7, 0x80);
}

void
XLParser::expression(void)
{
#line 346 "xl.g"
  zzRULE;
#line 347 "xl.g"
  relationalExpression();
#line 347 "xl.g"
  {
    while ( (setwd8[LA(1)]&0x1) ) {
#line 347 "xl.g"
      zzsetmatch(BOOLEAN_OP_set, BOOLEAN_OP_errset); consume();
#line 347 "xl.g"
      relationalExpression();
    }
  }
  return;
fail:
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd8, 0x2);
}
