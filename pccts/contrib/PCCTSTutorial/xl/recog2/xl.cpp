/*
 * A n t l r  T r a n s l a t i o n  H e a d e r
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 *
 *   ..\..\..\..\bin\antlr.exe -emsvc -CC -e3 -gl xl.g
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
  if ( guessing ) zzGUESS_FAIL;
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
  statementList();
#line 160 "xl.g"
  zzmatch(END); consume();
#line 160 "xl.g"
  zzmatch(IDENT); consume();
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd1, 0x4);
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
    if ( (LA(1)==CONSTANT) ) {
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
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd1, 0x8);
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
      if ( (LA(1)==SEMI) ) {
      }
      else {FAIL(1,err2,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
#line 174 "xl.g"
  zzmatch(SEMI); consume();
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd1, 0x10);
}

void
XLParser::constDecl(void)
{
#line 178 "xl.g"
  zzRULE;
#line 179 "xl.g"
  zzmatch(CONSTANT); consume();
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
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd1, 0x20);
}

void
XLParser::identList(void)
{
#line 184 "xl.g"
  zzRULE;
#line 185 "xl.g"
  zzmatch(IDENT); consume();
#line 185 "xl.g"
  {
    while ( (LA(1)==COMMA) ) {
#line 185 "xl.g"
      zzmatch(COMMA); consume();
#line 185 "xl.g"
      zzmatch(IDENT); consume();
    }
  }
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd1, 0x40);
}

void
XLParser::constantValue(void)
{
#line 189 "xl.g"
  zzRULE;
  if ( (LA(1)==INTLIT) ) {
#line 190 "xl.g"
    zzmatch(INTLIT); consume();
  }
  else {
    if ( (setwd1[LA(1)]&0x80) ) {
#line 191 "xl.g"
      zzsetmatch(STRING_LITERAL_set, STRING_LITERAL_errset); consume();
    }
    else {
      if ( (LA(1)==IDENT) ) {
#line 192 "xl.g"
        zzmatch(IDENT); consume();
      }
      else {FAIL(1,err5,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd2, 0x1);
}

void
XLParser::typeDecl(void)
{
#line 196 "xl.g"
  zzRULE;
#line 197 "xl.g"
  zzmatch(TYPE); consume();
#line 197 "xl.g"
  zzmatch(IDENT); consume();
#line 197 "xl.g"
  zzmatch(EQUALS); consume();
#line 198 "xl.g"
  {
    if ( (LA(1)==ARRAY) ) {
#line 198 "xl.g"
      arrayDecl();
    }
    else {
      if ( (LA(1)==RECORD) ) {
#line 199 "xl.g"
        recordDecl();
      }
      else {FAIL(1,err6,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
#line 201 "xl.g"
  zzmatch(SEMI); consume();
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd2, 0x2);
}

void
XLParser::arrayDecl(void)
{
#line 205 "xl.g"
  zzRULE;
#line 206 "xl.g"
  zzmatch(ARRAY); consume();
#line 206 "xl.g"
  zzmatch(LBRACKET); consume();
#line 206 "xl.g"
  integerConstant();
#line 206 "xl.g"
  zzmatch(DOTDOT); consume();
#line 206 "xl.g"
  integerConstant();
#line 206 "xl.g"
  zzmatch(RBRACKET); consume();
#line 207 "xl.g"
  zzmatch(OF); consume();
#line 207 "xl.g"
  typeName();
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd2, 0x4);
}

void
XLParser::integerConstant(void)
{
#line 210 "xl.g"
  zzRULE;
  if ( (LA(1)==INTLIT) ) {
#line 211 "xl.g"
    zzmatch(INTLIT); consume();
  }
  else {
    if ( (LA(1)==IDENT) ) {
#line 212 "xl.g"
      zzmatch(IDENT); consume();
    }
    else {FAIL(1,err7,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
  }
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd2, 0x8);
}

void
XLParser::recordDecl(void)
{
#line 216 "xl.g"
  zzRULE;
#line 217 "xl.g"
  zzmatch(RECORD); consume();
#line 217 "xl.g"
  {
    int zzcnt=1;
    do {
#line 217 "xl.g"
      identList();
#line 217 "xl.g"
      zzmatch(COLON); consume();
#line 217 "xl.g"
      typeName();
#line 217 "xl.g"
      zzmatch(SEMI); consume();
    } while ( (LA(1)==IDENT) );
  }
#line 217 "xl.g"
  zzmatch(END); consume();
#line 217 "xl.g"
  zzmatch(RECORD); consume();
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd2, 0x10);
}

void
XLParser::typeName(void)
{
#line 221 "xl.g"
  zzRULE;
  if ( (LA(1)==IDENT) ) {
#line 222 "xl.g"
    zzmatch(IDENT); consume();
  }
  else {
    if ( (LA(1)==INTEGER) ) {
#line 223 "xl.g"
      zzmatch(INTEGER); consume();
    }
    else {
      if ( (LA(1)==BOOLEAN) ) {
#line 224 "xl.g"
        zzmatch(BOOLEAN); consume();
      }
      else {FAIL(1,err8,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd2, 0x20);
}

void
XLParser::procedureDecl(void)
{
#line 228 "xl.g"
  zzRULE;
#line 229 "xl.g"
  zzmatch(PROCEDURE); consume();
#line 229 "xl.g"
  zzmatch(IDENT); consume();
#line 229 "xl.g"
  {
    if ( (LA(1)==LPAREN) ) {
#line 229 "xl.g"
      formalParameters();
    }
    else {
      if ( (LA(1)==EQUALS) ) {
      }
      else {FAIL(1,err9,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
#line 229 "xl.g"
  zzmatch(EQUALS); consume();
#line 230 "xl.g"
  subprogramBody();
#line 231 "xl.g"
  zzmatch(SEMI); consume();
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd2, 0x40);
}

void
XLParser::formalParameters(void)
{
#line 235 "xl.g"
  zzRULE;
#line 236 "xl.g"
  zzmatch(LPAREN); consume();
#line 236 "xl.g"
  parameterSpec();
#line 236 "xl.g"
  {
    while ( (LA(1)==SEMI) ) {
#line 236 "xl.g"
      zzmatch(SEMI); consume();
#line 236 "xl.g"
      parameterSpec();
    }
  }
#line 236 "xl.g"
  zzmatch(RPAREN); consume();
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd2, 0x80);
}

void
XLParser::parameterSpec(void)
{
#line 240 "xl.g"
  zzRULE;
#line 241 "xl.g"
  {
    if ( (LA(1)==VAR) ) {
#line 241 "xl.g"
      zzmatch(VAR); consume();
    }
    else {
      if ( (LA(1)==IDENT) ) {
      }
      else {FAIL(1,err10,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
#line 241 "xl.g"
  identList();
#line 241 "xl.g"
  zzmatch(COLON); consume();
#line 241 "xl.g"
  typeName();
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd3, 0x1);
}

void
XLParser::statement(void)
{
#line 244 "xl.g"
  zzRULE;
  zzGUESS_BLOCK
  if ( (LA(1)==EXIT) ) {
#line 245 "xl.g"
    exitStatement();
  }
  else {
    if ( (LA(1)==RETURN) ) {
#line 246 "xl.g"
      returnStatement();
    }
    else {
      if ( (LA(1)==IF) ) {
#line 247 "xl.g"
        ifStatement();
      }
      else {
        if ( (setwd3[LA(1)]&0x2) ) {
#line 248 "xl.g"
          loopStatement();
        }
        else {
          if ( (setwd3[LA(1)]&0x4) ) {
#line 249 "xl.g"
            ioStatement();
          }
          else {
            zzGUESS
            if ( !zzrv && (LA(1)==IDENT) ) {
#line 250 "xl.g"
              {
#line 250 "xl.g"
                zzmatch(IDENT); consume();
#line 250 "xl.g"
                {
                  if ( (LA(1)==LPAREN) ) {
#line 250 "xl.g"
                    zzmatch(LPAREN); consume();
                  }
                  else {
                    if ( (LA(1)==SEMI) ) {
#line 250 "xl.g"
                      zzmatch(SEMI); consume();
                    }
                    else {FAIL(1,err11,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                  }
                }
              }
              zzGUESS_DONE
#line 250 "xl.g"
              procedureCallStatement();
            }
            else {
              if ( !zzrv ) zzGUESS_DONE;
              if ( (LA(1)==IDENT) ) {
#line 251 "xl.g"
                assignmentStatement();
              }
              else {FAIL(1,err12,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
            }
          }
        }
      }
    }
  }
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd3, 0x8);
}

void
XLParser::statementList(void)
{
#line 254 "xl.g"
  zzRULE;
  zzGUESS_BLOCK
  if ( (setwd3[LA(1)]&0x10) ) {
#line 255 "xl.g"
    statement();
#line 255 "xl.g"
    statementList();
  }
  else {
    zzGUESS
    if ( !zzrv && (LA(1)==END) ) {
#line 256 "xl.g"
      {
#line 256 "xl.g"
        endStatement();
      }
      zzGUESS_DONE
#line 256 "xl.g"
      endStatement();
#line 256 "xl.g"
      statementList();
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (setwd3[LA(1)]&0x20) ) {
      }
      else {FAIL(1,err13,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd3, 0x40);
}

void
XLParser::assignmentStatement(void)
{
#line 260 "xl.g"
  zzRULE;
#line 261 "xl.g"
  variableReference();
#line 261 "xl.g"
  zzmatch(BECOMES); consume();
#line 261 "xl.g"
  expression();
#line 261 "xl.g"
  zzmatch(SEMI); consume();
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd3, 0x80);
}

void
XLParser::exitStatement(void)
{
#line 265 "xl.g"
  zzRULE;
#line 266 "xl.g"
  zzmatch(EXIT); consume();
#line 266 "xl.g"
  zzmatch(WHEN); consume();
#line 266 "xl.g"
  expression();
#line 266 "xl.g"
  zzmatch(SEMI); consume();
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd4, 0x1);
}

void
XLParser::procedureCallStatement(void)
{
#line 269 "xl.g"
  zzRULE;
#line 270 "xl.g"
  zzmatch(IDENT); consume();
#line 270 "xl.g"
  {
    if ( (LA(1)==LPAREN) ) {
#line 270 "xl.g"
      actualParameters();
    }
    else {
      if ( (LA(1)==SEMI) ) {
      }
      else {FAIL(1,err14,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
#line 270 "xl.g"
  zzmatch(SEMI); consume();
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd4, 0x2);
}

void
XLParser::actualParameters(void)
{
#line 273 "xl.g"
  zzRULE;
#line 274 "xl.g"
  zzmatch(LPAREN); consume();
#line 274 "xl.g"
  {
    if ( (setwd4[LA(1)]&0x4) ) {
#line 274 "xl.g"
      expression();
#line 274 "xl.g"
      {
        while ( (LA(1)==COMMA) ) {
#line 274 "xl.g"
          zzmatch(COMMA); consume();
#line 274 "xl.g"
          expression();
        }
      }
    }
    else {
      if ( (LA(1)==RPAREN) ) {
      }
      else {FAIL(1,err15,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
#line 274 "xl.g"
  zzmatch(RPAREN); consume();
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd4, 0x8);
}

void
XLParser::returnStatement(void)
{
#line 278 "xl.g"
  zzRULE;
#line 279 "xl.g"
  zzmatch(RETURN); consume();
#line 279 "xl.g"
  zzmatch(SEMI); consume();
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd4, 0x10);
}

void
XLParser::ifStatement(void)
{
#line 283 "xl.g"
  zzRULE;
#line 284 "xl.g"
  zzmatch(IF); consume();
#line 284 "xl.g"
  ifPart();
#line 284 "xl.g"
  zzmatch(END); consume();
#line 284 "xl.g"
  zzmatch(IF); consume();
#line 284 "xl.g"
  zzmatch(SEMI); consume();
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd4, 0x20);
}

void
XLParser::ifPart(void)
{
#line 287 "xl.g"
  zzRULE;
#line 288 "xl.g"
  expression();
#line 288 "xl.g"
  zzmatch(THEN); consume();
#line 289 "xl.g"
  statementList();
#line 290 "xl.g"
  {
    if ( (LA(1)==ELSIF) ) {
#line 290 "xl.g"
      zzmatch(ELSIF); consume();
#line 290 "xl.g"
      ifPart();
    }
    else {
      if ( (LA(1)==ELSE) ) {
#line 291 "xl.g"
        zzmatch(ELSE); consume();
#line 291 "xl.g"
        statementList();
      }
      else {
        if ( (LA(1)==END) ) {
        }
        else {FAIL(1,err16,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
      }
    }
  }
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd4, 0x40);
}

void
XLParser::loopStatement(void)
{
#line 295 "xl.g"
  zzRULE;
#line 296 "xl.g"
  {
    if ( (LA(1)==WHILE) ) {
#line 296 "xl.g"
      zzmatch(WHILE); consume();
#line 296 "xl.g"
      expression();
    }
    else {
      if ( (LA(1)==LOOP) ) {
      }
      else {FAIL(1,err17,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
#line 296 "xl.g"
  zzmatch(LOOP); consume();
#line 297 "xl.g"
  statementList();
#line 298 "xl.g"
  zzmatch(END); consume();
#line 298 "xl.g"
  zzmatch(LOOP); consume();
#line 298 "xl.g"
  zzmatch(SEMI); consume();
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd4, 0x80);
}

void
XLParser::endStatement(void)
{
#line 301 "xl.g"
  zzRULE;
#line 302 "xl.g"
  zzmatch(END); consume();
#line 302 "xl.g"
  zzmatch(SEMI); consume();
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd5, 0x1);
}

void
XLParser::variableReference(void)
{
#line 305 "xl.g"
  zzRULE;
#line 306 "xl.g"
  zzmatch(IDENT); consume();
#line 309 "xl.g"
  {
    for (;;) {
      if ( !((setwd5[LA(1)]&0x2))) break;
      if ( (LA(1)==LBRACKET) ) {
#line 307 "xl.g"
        zzmatch(LBRACKET); consume();
#line 307 "xl.g"
        expression();
#line 307 "xl.g"
        zzmatch(RBRACKET); consume();
      }
      else {
        if ( (LA(1)==DOT) ) {
#line 308 "xl.g"
          zzmatch(DOT); consume();
#line 308 "xl.g"
          zzmatch(IDENT); consume();
        }
        else break; /* MR6 code for exiting loop "for sure" */
      }
    }
  }
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd5, 0x4);
}

void
XLParser::ioStatement(void)
{
#line 312 "xl.g"
  zzRULE;
  if ( (LA(1)==PUT) ) {
#line 313 "xl.g"
    zzmatch(PUT); consume();
#line 313 "xl.g"
    zzmatch(LPAREN); consume();
#line 313 "xl.g"
    expression();
#line 313 "xl.g"
    zzmatch(RPAREN); consume();
#line 313 "xl.g"
    zzmatch(SEMI); consume();
  }
  else {
    if ( (LA(1)==GET) ) {
#line 314 "xl.g"
      zzmatch(GET); consume();
#line 314 "xl.g"
      zzmatch(LPAREN); consume();
#line 314 "xl.g"
      variableReference();
#line 314 "xl.g"
      zzmatch(RPAREN); consume();
#line 314 "xl.g"
      zzmatch(SEMI); consume();
    }
    else {
      if ( (LA(1)==SKIPLINE) ) {
#line 315 "xl.g"
        zzmatch(SKIPLINE); consume();
#line 315 "xl.g"
        {
          if ( (LA(1)==LPAREN) ) {
#line 315 "xl.g"
            zzmatch(LPAREN); consume();
#line 315 "xl.g"
            zzmatch(RPAREN); consume();
          }
          else {
            if ( (LA(1)==SEMI) ) {
            }
            else {FAIL(1,err18,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
          }
        }
#line 315 "xl.g"
        zzmatch(SEMI); consume();
      }
      else {
        if ( (LA(1)==NEWLINE) ) {
#line 316 "xl.g"
          zzmatch(NEWLINE); consume();
#line 316 "xl.g"
          {
            if ( (LA(1)==LPAREN) ) {
#line 316 "xl.g"
              zzmatch(LPAREN); consume();
#line 316 "xl.g"
              zzmatch(RPAREN); consume();
            }
            else {
              if ( (LA(1)==SEMI) ) {
              }
              else {FAIL(1,err19,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
            }
          }
#line 316 "xl.g"
          zzmatch(SEMI); consume();
        }
        else {FAIL(1,err20,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
      }
    }
  }
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd5, 0x8);
}

void
XLParser::primitiveElement(void)
{
#line 320 "xl.g"
  zzRULE;
  if ( (LA(1)==IDENT) ) {
#line 321 "xl.g"
    variableReference();
  }
  else {
    if ( (setwd5[LA(1)]&0x10) ) {
#line 322 "xl.g"
      constantValue();
    }
    else {
      if ( (LA(1)==LPAREN) ) {
#line 323 "xl.g"
        zzmatch(LPAREN); consume();
#line 323 "xl.g"
        expression();
#line 323 "xl.g"
        zzmatch(RPAREN); consume();
      }
      else {FAIL(1,err21,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd5, 0x20);
}

void
XLParser::booleanNegationExpression(void)
{
#line 327 "xl.g"
  zzRULE;
#line 328 "xl.g"
  {
    while ( (LA(1)==NOT) ) {
#line 328 "xl.g"
      zzmatch(NOT); consume();
    }
  }
#line 328 "xl.g"
  primitiveElement();
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd5, 0x40);
}

void
XLParser::signExpression(void)
{
#line 331 "xl.g"
  zzRULE;
#line 332 "xl.g"
  {
    while ( (setwd5[LA(1)]&0x80) ) {
#line 332 "xl.g"
      zzsetmatch(ADD_OP_set, ADD_OP_errset); consume();
    }
  }
#line 332 "xl.g"
  booleanNegationExpression();
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd6, 0x1);
}

void
XLParser::multiplyingExpression(void)
{
#line 336 "xl.g"
  zzRULE;
#line 337 "xl.g"
  signExpression();
#line 337 "xl.g"
  {
    while ( (setwd6[LA(1)]&0x2) ) {
#line 337 "xl.g"
      zzsetmatch(MULT_OP_set, MULT_OP_errset); consume();
#line 337 "xl.g"
      signExpression();
    }
  }
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd6, 0x4);
}

void
XLParser::addingExpression(void)
{
#line 340 "xl.g"
  zzRULE;
#line 341 "xl.g"
  multiplyingExpression();
#line 341 "xl.g"
  {
    while ( (setwd6[LA(1)]&0x8) ) {
#line 341 "xl.g"
      zzsetmatch(ADD_OP_set, ADD_OP_errset); consume();
#line 341 "xl.g"
      multiplyingExpression();
    }
  }
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd6, 0x10);
}

void
XLParser::relationalExpression(void)
{
#line 344 "xl.g"
  zzRULE;
#line 345 "xl.g"
  addingExpression();
#line 345 "xl.g"
  {
    while ( (setwd6[LA(1)]&0x20) ) {
#line 345 "xl.g"
      zzsetmatch(RELATIONAL_OP_set, RELATIONAL_OP_errset); consume();
#line 345 "xl.g"
      addingExpression();
    }
  }
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd6, 0x40);
}

void
XLParser::expression(void)
{
#line 348 "xl.g"
  zzRULE;
#line 349 "xl.g"
  relationalExpression();
#line 349 "xl.g"
  {
    while ( (setwd6[LA(1)]&0x80) ) {
#line 349 "xl.g"
      zzsetmatch(BOOLEAN_OP_set, BOOLEAN_OP_errset); consume();
#line 349 "xl.g"
      relationalExpression();
    }
  }
  return;
fail:
  if ( guessing ) zzGUESS_FAIL;
  syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
  resynch(setwd7, 0x1);
}
