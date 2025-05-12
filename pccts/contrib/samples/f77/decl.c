/*
 * A n t l r  T r a n s l a t i o n  H e a d e r
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 *
 *   ..\..\..\bin\antlr.exe -emsvc -k 2 -glms -gh -ga -gt f77.g expr.g decl.g io.g
 *
 */

#define ANTLR_VERSION	13333
#include "pcctscfg.h"
#include "pccts_stdio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
/* #include "cr_attr.h" */

#define D_TextSize 256

#ifndef D_TextSize
#define D_TextSize	30
#endif

typedef struct { char text[D_TextSize]; } Attrib;

void zzcr_attr(Attrib *attrib, int tok, char *tok_text);

#if 0
#define zzcr_attr(a,tok,t)	strncpy((a)->text, t, D_TextSize-1); \
(a)->text[D_TextSize-1] = '\0';
#endif


extern void ReadWriteProcessing(void);
extern void IOStatement(void);











#define SUPPRESS_TRAILING_COMMENTS
#define zzAST_DOUBLE
#define AST_FIELDS char f77NodeText[100]; int token; char *TrailingComment;
#ifndef zzcr_ast
#define zzcr_ast(ast,attr,tok,tok_text) {	\
  char *ptr;								\
  strcpy(ast->f77NodeText,tok_text);		\
  ast->TrailingComment = NULL;			\
  ptr = strchr(ast->f77NodeText, '!');	\
  if(ptr != NULL) {						\
    /**ptr = '\0';this is left for later!!!!*/ \
    ast->TrailingComment = ptr+1;		\
  }									\
  ast->token = tok;						\
}
#endif

#define IDENTIFIER_LENGTH (32)
#if !defined(TRUE)
#define TRUE (1 == 1)
#define FALSE (1 == 0)
#endif
enum {LVALUE, RVALUE}; /*Used to pass the position of an element relative to '="*/
extern void AddSymbol(char *Name, int Type);
extern int LookUp(char *Name);
extern void ChangeType(char *Name, int Type);

extern void GetTrailingComment(void);
extern void GetQuotedString(void);
extern void ProcessHollerith(void);
extern void NewLineProcessing(void);
extern int LineColumn;
extern int keyword_context;
/*This two are used to recognise 'combined expressions'.*/
extern int LPCount;
extern int ReadWriteControlFlag;
extern int ExpectingIOKeyword;
extern int CommaCount;	/*Whithin parenthesis!*/
#define BegCol (zzbegcol-LineColumn-1)
#define EndCol (zzendcol-LineColumn-1)
extern int LineCount;
extern int StatementCount;
extern int CurrentStatement;
#if !defined(ZZCOL)
#error ZZCOL must be defined
#endif
#define F77_BUFFER_SIZE 100
#define F77_LINE_SIZE 72
#define ZZCAN_GUESS
#include "pccts_setjmp.h"
#define LL_K 2
#define GENAST

#include "ast.h"

#define zzSET_SIZE 36
#define zzTOKEN_COUNT 260
#include "antlr.h"
#include "tokens.h"
#include "dlgdef.h"
#include "mode.h"

/* MR23 In order to remove calls to PURIFY use the antlr -nopurify option */

#ifndef PCCTS_PURIFY
#define PCCTS_PURIFY(r,s) memset((char *) &(r),'\0',(s));
#endif


void
#ifdef __USE_PROTOS
real_statement(AST**_root)
#else
real_statement(_root)
AST **_root;
#endif
{
#line 4 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 4 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 4 "decl.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==REAL) ) {
          }
          else {zzFAIL(1,zzerr133,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 4 "decl.g"
    zzmatch(REAL);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 4 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==STAR) ) {
#line 4 "decl.g"
          zzmatch(STAR);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 4 "decl.g"
          length_spec(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( (setwd45[LA(1)]&0x80) ) {
          }
          else {zzFAIL(1,zzerr134,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 4 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( 
(LA(1)==COMMA) ) {
#line 4 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==IDENTIFIER) ) {
          }
          else {zzFAIL(1,zzerr135,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 5 "decl.g"
    real_item(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 5 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 5 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 5 "decl.g"
          real_item(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd46, 0x1);
  }
}

void
#ifdef __USE_PROTOS
real_item(AST**_root)
#else
real_item(_root)
AST **_root;
#endif
{
#line 6 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (LA(1)==IDENTIFIER) && (setwd46[LA(2)]&0x2) ) {
#line 6 "decl.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 6 "decl.g"
          init_real_item(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 6 "decl.g"
      init_real_item(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      zzGUESS
      if ( !zzrv && (LA(1)==IDENTIFIER) && (setwd46[LA(2)]&0x4) ) {
#line 7 "decl.g"
        {
          zzBLOCK(zztasp2);
          zzMake0;
          {
#line 7 "decl.g"
            uninit_real_item(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
            zzEXIT(zztasp2);
          }
        }
        zzGUESS_DONE
#line 7 "decl.g"
        uninit_real_item(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      /* MR10 */ else {
        /* MR10 */ if ( !zzrv ) zzGUESS_DONE;
        /* MR10 */ if (0) {}     /* last alternative of block is guess block */
        else {zzFAIL(2,zzerr136,zzerr137,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd46, 0x8);
  }
}

void
#ifdef __USE_PROTOS
init_real_item(AST**_root)
#else
init_real_item(_root)
AST **_root;
#endif
{
#line 9 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 9 "decl.g"
    real_var_list(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 9 "decl.g"
    zzmatch(DIV);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 9 "decl.g"
    real_const_list(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 9 "decl.g"
    zzmatch(DIV);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd46, 0x10);
  }
}

void
#ifdef __USE_PROTOS
uninit_real_item(AST**_root)
#else
uninit_real_item(_root)
AST **_root;
#endif
{
#line 10 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 10 "decl.g"
    real_var_list(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd46, 0x20);
  }
}

void
#ifdef __USE_PROTOS
real_var_list(AST**_root)
#else
real_var_list(_root)
AST **_root;
#endif
{
#line 12 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (LA(1)==IDENTIFIER) && (setwd46[LA(2)]&0x40) ) {
#line 12 "decl.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 12 "decl.g"
          var_decl(zzSTR, REAL_ID );
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 12 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 12 "decl.g"
      var_decl(zzSTR, REAL_ID );
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
#line 12 "decl.g"
      zzmatch(COMMA);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 12 "decl.g"
      real_var_list(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (LA(1)==IDENTIFIER) && 
(setwd46[LA(2)]&0x80) ) {
#line 13 "decl.g"
        var_decl(zzSTR, REAL_ID );
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {zzFAIL(2,zzerr138,zzerr139,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd47, 0x1);
  }
}

void
#ifdef __USE_PROTOS
real_const_list(AST**_root)
#else
real_const_list(_root)
AST **_root;
#endif
{
#line 16 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (setwd47[LA(1)]&0x2) && (LA(2)==COMMA) ) {
#line 16 "decl.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 16 "decl.g"
          real_const(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 16 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 16 "decl.g"
      real_const(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
#line 16 "decl.g"
      zzmatch(COMMA);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 16 "decl.g"
      real_const_list(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (setwd47[LA(1)]&0x4) && (LA(2)==DIV) ) {
#line 17 "decl.g"
        real_const(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {zzFAIL(2,zzerr140,zzerr141,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd47, 0x8);
  }
}

void
#ifdef __USE_PROTOS
var_decl(AST**_root,int type)
#else
var_decl(_root,type)
AST **_root;
 int type ;
#endif
{
#line 19 "decl.g"
  zzRULE;
  Attrib i;
  AST *i_ast=NULL;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (LA(1)==IDENTIFIER) && (LA(2)==LP) ) {
#line 20 "decl.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 20 "decl.g"
          zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 20 "decl.g"
          zzmatch(LP);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 20 "decl.g"
      array_declarer(zzSTR, type );
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (LA(1)==IDENTIFIER) && (setwd47[LA(2)]&0x10) ) {
#line 21 "decl.g"
        {
          zzBLOCK(zztasp2);
          zzMake0;
          {
#line 21 "decl.g"
            zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
            
            zzNON_GUESS_MODE {
                            i = zzaCur;
              i_ast = zzastCur;
            }
             zzCONSUME;
#line 21 "decl.g"
            {
              zzBLOCK(zztasp3);
              zzMake0;
              {
                if ( (LA(1)==STAR) ) {
#line 21 "decl.g"
                  zzmatch(STAR);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
#line 21 "decl.g"
                  length_spec(zzSTR);
                  if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                  }     /* MR10 */
                }
                else {
                  if ( 
(setwd47[LA(1)]&0x20) ) {
                  }
                  else {zzFAIL(1,zzerr142,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                }
                zzEXIT(zztasp3);
              }
            }
            zzNON_GUESS_MODE {
#line 22 "decl.g"

              zzastArg(1)->token = type;
              ChangeType( i.text,type);
            }
            zzEXIT(zztasp2);
          }
        }
      }
      else {zzFAIL(2,zzerr143,zzerr144,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd47, 0x40);
  }
}

void
#ifdef __USE_PROTOS
array_declarer(AST**_root,int type)
#else
array_declarer(_root,type)
AST **_root;
 int type ;
#endif
{
#line 29 "decl.g"
  zzRULE;
  Attrib i;
  AST *i_ast=NULL;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 29 "decl.g"
    zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
            i = zzaCur;
      i_ast = zzastCur;
    }
     zzCONSUME;
#line 29 "decl.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 29 "decl.g"
    dimension_declarator(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 29 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 29 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 29 "decl.g"
          dimension_declarator(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
#line 29 "decl.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 29 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==STAR) ) {
#line 29 "decl.g"
          zzmatch(STAR);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 29 "decl.g"
          length_spec(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( (setwd47[LA(1)]&0x80) ) {
          }
          else {zzFAIL(1,zzerr145,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
    zzNON_GUESS_MODE {
#line 30 "decl.g"
      {
        switch(type) {
          case INTEGER_ID:type = INTEGER_ARRAY_ID; break;
          case REAL_ID:type = REAL_ARRAY_ID; break;
          case DOUBLE_PRECISION_ID:type = DOUBLE_PRECISION_ARRAY_ID; break;
          case CHARACTER_ID:type = CHARACTER_ARRAY_ID; break;
          case LOGICAL_ID:type = LOGICAL_ARRAY_ID; break;
          case DIMENSION:
          switch(LookUp( i.text)) {
            case FUNCTION_NAME: type = FUNCTION_NAME; break;
            case INTEGER_ARRAY_ID: type = INTEGER_ARRAY_ID; break;
            case REAL_ARRAY_ID: type = REAL_ARRAY_ID; break;
            case DOUBLE_PRECISION_ARRAY_ID: type = DOUBLE_PRECISION_ARRAY_ID; break;
            case CHARACTER_ARRAY_ID: type = CHARACTER_ARRAY_ID; break;
            case LOGICAL_ARRAY_ID: type = LOGICAL_ARRAY_ID; break;

            case INTEGER_ID:type = INTEGER_ARRAY_ID; break;
            case REAL_ID:type = REAL_ARRAY_ID; break;
            case DOUBLE_PRECISION_ID:type = DOUBLE_PRECISION_ARRAY_ID; break;
            case CHARACTER_ID:type = CHARACTER_ARRAY_ID; break;
            case LOGICAL_ID:type = LOGICAL_ARRAY_ID; break;
            case -1: /*Not found! Determine its type from its name.*/
            type = ((*( i.text) >= 'I') && (*( i.text) <= 'N'))?INTEGER_ARRAY_ID:REAL_ARRAY_ID;
            break;
            default:
            type = LookUp( i.text); /*Get it for debugging purposes!*/
            assert(1 == 0);
          }
          break;
          default:
          assert(1 == 0);
          break;
        }
        zzastArg(1)->token = type;
        ChangeType( i.text, type);
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd48, 0x1);
  }
}

void
#ifdef __USE_PROTOS
dimension_declarator(AST**_root)
#else
dimension_declarator(_root)
AST **_root;
#endif
{
#line 68 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (setwd48[LA(1)]&0x2) && (setwd48[LA(2)]&0x4) ) {
#line 69 "decl.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 69 "decl.g"
          lower_bound(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 69 "decl.g"
          zzmatch(COLUMN);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 69 "decl.g"
      lower_bound(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
#line 69 "decl.g"
      zzmatch(COLUMN);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 69 "decl.g"
      upper_bound(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (setwd48[LA(1)]&0x8) && 
(setwd48[LA(2)]&0x10) ) {
#line 70 "decl.g"
        upper_bound(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {zzFAIL(2,zzerr146,zzerr147,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd48, 0x20);
  }
}

void
#ifdef __USE_PROTOS
lower_bound(AST**_root)
#else
lower_bound(_root)
AST **_root;
#endif
{
#line 72 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 72 "decl.g"
    int type;
#line 72 "decl.g"
    zzNON_GUESS_MODE {
       type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
    } else {
      expression(zzSTR);
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd48, 0x40);
  }
}

void
#ifdef __USE_PROTOS
upper_bound(AST**_root)
#else
upper_bound(_root)
AST **_root;
#endif
{
#line 73 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 73 "decl.g"
    int type;
#line 73 "decl.g"
    zzNON_GUESS_MODE {
       type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
    } else {
      expression(zzSTR);
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd48, 0x80);
  }
}

void
#ifdef __USE_PROTOS
variable(AST**_root,int where)
#else
variable(_root,where)
AST **_root;
 int where ;
#endif
{
#line 75 "decl.g"
  zzRULE;
  Attrib i;
  AST *i_ast=NULL;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (LA(1)==IDENTIFIER) && (LA(2)==LP) ) {
#line 76 "decl.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 76 "decl.g"
          substring(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 76 "decl.g"
      substring(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      zzGUESS
      if ( !zzrv && (LA(1)==IDENTIFIER) && (LA(2)==LP) ) {
#line 77 "decl.g"
        {
          zzBLOCK(zztasp2);
          zzMake0;
          {
#line 77 "decl.g"
            array_element_reference(zzSTR, where );
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
            zzEXIT(zztasp2);
          }
        }
        zzGUESS_DONE
#line 77 "decl.g"
        array_element_reference(zzSTR, where );
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {
        if ( !zzrv ) zzGUESS_DONE;
        if ( (LA(1)==IDENTIFIER) && (setwd49[LA(2)]&0x1) ) {
#line 78 "decl.g"
          {
            zzBLOCK(zztasp2);
            zzMake0;
            {
#line 78 "decl.g"
              zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
              
              zzNON_GUESS_MODE {
                                i = zzaCur;
                i_ast = zzastCur;
              }
              
              zzNON_GUESS_MODE {
#line 79 "decl.g"
                {
                  int type;
                  type = LookUp( i.text);
                  if((where == RVALUE) && (strlen( i.text) > 1)) /*It is not in implied do loop*/
                  {
                    /*If not found I assume its type from its name*/
                    if(type == -1) {
                      type = ((*( i.text) >= 'I') && (*( i.text) <= 'N'))?INTEGER_ID:REAL_ID;
                      AddSymbol( i.text, type);
                    }
                  }
                  else {
                    if(type == -1) {
                      type = ((*( i.text) >= 'I') && (*( i.text) <= 'N'))?INTEGER_ID:REAL_ID;
                      AddSymbol( i.text, type);
                    }
                  }
                  zzastArg(1)->token = type;
                }
              }
 zzCONSUME;

              zzEXIT(zztasp2);
            }
          }
        }
        else {zzFAIL(2,zzerr148,zzerr149,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd49, 0x2);
  }
}

void
#ifdef __USE_PROTOS
array_element_reference(AST**_root,int where)
#else
array_element_reference(_root,where)
AST **_root;
 int where ;
#endif
{
#line 101 "decl.g"
  zzRULE;
  Attrib i;
  AST *i_ast=NULL;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 102 "decl.g"
    int type;
#line 103 "decl.g"
    zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
            i = zzaCur;
      i_ast = zzastCur;
    }
     zzCONSUME;
#line 103 "decl.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 103 "decl.g"
    zzNON_GUESS_MODE {
       type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
    } else {
      expression(zzSTR);
    }
#line 103 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 103 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 103 "decl.g"
          zzNON_GUESS_MODE {
             type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
          } else {
            expression(zzSTR);
          }
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
#line 103 "decl.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
#line 104 "decl.g"
      {
        int type;
        type = LookUp( i.text);
        assert(where == LVALUE || where == RVALUE);
        if((CurrentStatement == COMMON) && (type == FUNCTION_NAME)) {
          type = ((*( i.text) >= 'I') && (*( i.text) <= 'N'))?INTEGER_ARRAY_ID:REAL_ARRAY_ID;
          ChangeType( i.text,type);
        }
        else if(where == RVALUE) {
          if(type == -1) {/*Not found!*/
            /*It must be a function name. It is going to be declared later in the code.*/
            type = FUNCTION_NAME;
            AddSymbol( i.text, type); /*And add it to the symbol table.*/
          }
        }
        else {
          if(type == -1) {/*Not found! Determine its type from its name.*/
            type = ((*( i.text) >= 'I') && (*( i.text) <= 'N'))?INTEGER_ARRAY_ID:REAL_ARRAY_ID;
            AddSymbol( i.text, type); /*And add it to the symbol table.*/
          }
        }
        zzastArg(1)->token = type;
      }
    }
 zzCONSUME;

    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd49, 0x4);
  }
}

void
#ifdef __USE_PROTOS
double_precision_statement(AST**_root)
#else
double_precision_statement(_root)
AST **_root;
#endif
{
#line 133 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 133 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 133 "decl.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==DOUBLE_PRECISION) ) {
          }
          else {zzFAIL(1,zzerr150,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 133 "decl.g"
    zzmatch(DOUBLE_PRECISION);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 133 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==STAR) ) {
#line 133 "decl.g"
          zzmatch(STAR);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 133 "decl.g"
          length_spec(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( (setwd49[LA(1)]&0x8) ) {
          }
          else {zzFAIL(1,zzerr151,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 133 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( 
(LA(1)==COMMA) ) {
#line 133 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==IDENTIFIER) ) {
          }
          else {zzFAIL(1,zzerr152,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 134 "decl.g"
    double_prec_item(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 134 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 134 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 134 "decl.g"
          double_prec_item(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd49, 0x10);
  }
}

void
#ifdef __USE_PROTOS
double_prec_item(AST**_root)
#else
double_prec_item(_root)
AST **_root;
#endif
{
#line 135 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (LA(1)==IDENTIFIER) && (setwd49[LA(2)]&0x20) ) {
#line 135 "decl.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 135 "decl.g"
          init_double_prec_item(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 135 "decl.g"
      init_double_prec_item(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      zzGUESS
      if ( !zzrv && (LA(1)==IDENTIFIER) && (setwd49[LA(2)]&0x40) ) {
#line 136 "decl.g"
        {
          zzBLOCK(zztasp2);
          zzMake0;
          {
#line 136 "decl.g"
            uninit_double_prec_item(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
            zzEXIT(zztasp2);
          }
        }
        zzGUESS_DONE
#line 136 "decl.g"
        uninit_double_prec_item(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      /* MR10 */ else {
        /* MR10 */ if ( !zzrv ) zzGUESS_DONE;
        /* MR10 */ if (0) {}     /* last alternative of block is guess block */
        else {zzFAIL(2,zzerr153,zzerr154,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd49, 0x80);
  }
}

void
#ifdef __USE_PROTOS
init_double_prec_item(AST**_root)
#else
init_double_prec_item(_root)
AST **_root;
#endif
{
#line 138 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 138 "decl.g"
    double_prec_var_list(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 138 "decl.g"
    zzmatch(DIV);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 138 "decl.g"
    double_prec_const_list(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 138 "decl.g"
    zzmatch(DIV);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd50, 0x1);
  }
}

void
#ifdef __USE_PROTOS
uninit_double_prec_item(AST**_root)
#else
uninit_double_prec_item(_root)
AST **_root;
#endif
{
#line 139 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 139 "decl.g"
    double_prec_var_list(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd50, 0x2);
  }
}

void
#ifdef __USE_PROTOS
double_prec_var_list(AST**_root)
#else
double_prec_var_list(_root)
AST **_root;
#endif
{
#line 140 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (LA(1)==IDENTIFIER) && (setwd50[LA(2)]&0x4) ) {
#line 140 "decl.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 140 "decl.g"
          var_decl(zzSTR, DOUBLE_PRECISION_ID );
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 140 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 140 "decl.g"
      var_decl(zzSTR, DOUBLE_PRECISION_ID );
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
#line 140 "decl.g"
      zzmatch(COMMA);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 140 "decl.g"
      double_prec_var_list(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (LA(1)==IDENTIFIER) && 
(setwd50[LA(2)]&0x8) ) {
#line 141 "decl.g"
        var_decl(zzSTR, DOUBLE_PRECISION_ID );
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {zzFAIL(2,zzerr155,zzerr156,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd50, 0x10);
  }
}

void
#ifdef __USE_PROTOS
double_prec_const_list(AST**_root)
#else
double_prec_const_list(_root)
AST **_root;
#endif
{
#line 143 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (setwd50[LA(1)]&0x20) && (LA(2)==COMMA) ) {
#line 143 "decl.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 143 "decl.g"
          real_const(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 143 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 143 "decl.g"
      real_const(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
#line 143 "decl.g"
      zzmatch(COMMA);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 143 "decl.g"
      real_const_list(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (setwd50[LA(1)]&0x40) && (LA(2)==DIV) ) {
#line 144 "decl.g"
        real_const(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {zzFAIL(2,zzerr157,zzerr158,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd50, 0x80);
  }
}

void
#ifdef __USE_PROTOS
integer_statement(AST**_root)
#else
integer_statement(_root)
AST **_root;
#endif
{
#line 151 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 151 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 151 "decl.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==INTEGER) ) {
          }
          else {zzFAIL(1,zzerr159,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 151 "decl.g"
    zzmatch(INTEGER);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 151 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==STAR) ) {
#line 151 "decl.g"
          zzmatch(STAR);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 151 "decl.g"
          length_spec(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( 
(setwd51[LA(1)]&0x1) ) {
          }
          else {zzFAIL(1,zzerr160,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 151 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==COMMA) ) {
#line 151 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==IDENTIFIER) ) {
          }
          else {zzFAIL(1,zzerr161,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 152 "decl.g"
    int_item(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 152 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 152 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 152 "decl.g"
          int_item(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd51, 0x2);
  }
}

void
#ifdef __USE_PROTOS
int_item(AST**_root)
#else
int_item(_root)
AST **_root;
#endif
{
#line 153 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (LA(1)==IDENTIFIER) && (setwd51[LA(2)]&0x4) ) {
#line 153 "decl.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 153 "decl.g"
          init_int_item(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 153 "decl.g"
      init_int_item(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      zzGUESS
      if ( !zzrv && (LA(1)==IDENTIFIER) && (setwd51[LA(2)]&0x8) ) {
#line 154 "decl.g"
        {
          zzBLOCK(zztasp2);
          zzMake0;
          {
#line 154 "decl.g"
            uninit_int_item(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
            zzEXIT(zztasp2);
          }
        }
        zzGUESS_DONE
#line 154 "decl.g"
        uninit_int_item(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      /* MR10 */ else {
        /* MR10 */ if ( !zzrv ) zzGUESS_DONE;
        /* MR10 */ if (0) {}     /* last alternative of block is guess block */
        else {zzFAIL(2,zzerr162,zzerr163,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd51, 0x10);
  }
}

void
#ifdef __USE_PROTOS
init_int_item(AST**_root)
#else
init_int_item(_root)
AST **_root;
#endif
{
#line 156 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 156 "decl.g"
    int_var_list(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 156 "decl.g"
    zzmatch(DIV);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 156 "decl.g"
    int_const_list(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 156 "decl.g"
    zzmatch(DIV);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd51, 0x20);
  }
}

void
#ifdef __USE_PROTOS
uninit_int_item(AST**_root)
#else
uninit_int_item(_root)
AST **_root;
#endif
{
#line 157 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 157 "decl.g"
    int_var_list(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd51, 0x40);
  }
}

void
#ifdef __USE_PROTOS
int_var_list(AST**_root)
#else
int_var_list(_root)
AST **_root;
#endif
{
#line 158 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (LA(1)==IDENTIFIER) && (setwd51[LA(2)]&0x80) ) {
#line 158 "decl.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 158 "decl.g"
          var_decl(zzSTR, INTEGER_ID );
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 158 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 158 "decl.g"
      var_decl(zzSTR, INTEGER_ID );
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
#line 158 "decl.g"
      zzmatch(COMMA);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 158 "decl.g"
      int_var_list(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (LA(1)==IDENTIFIER) && 
(setwd52[LA(2)]&0x1) ) {
#line 159 "decl.g"
        var_decl(zzSTR, INTEGER_ID );
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {zzFAIL(2,zzerr164,zzerr165,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd52, 0x2);
  }
}

void
#ifdef __USE_PROTOS
int_const_list(AST**_root)
#else
int_const_list(_root)
AST **_root;
#endif
{
#line 161 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (setwd52[LA(1)]&0x4) && (LA(2)==COMMA) ) {
#line 161 "decl.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 161 "decl.g"
          int_const(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 161 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 161 "decl.g"
      int_const(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
#line 161 "decl.g"
      zzmatch(COMMA);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 161 "decl.g"
      int_const_list(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (setwd52[LA(1)]&0x8) && (LA(2)==DIV) ) {
#line 162 "decl.g"
        int_const(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {zzFAIL(2,zzerr166,zzerr167,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd52, 0x10);
  }
}

void
#ifdef __USE_PROTOS
dimension_statement(AST**_root)
#else
dimension_statement(_root)
AST **_root;
#endif
{
#line 168 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 168 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 168 "decl.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==DIMENSION) ) {
          }
          else {zzFAIL(1,zzerr168,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 168 "decl.g"
    zzmatch(DIMENSION);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 168 "decl.g"
    array_declarer(zzSTR, DIMENSION );
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 168 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 168 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 168 "decl.g"
          array_declarer(zzSTR, DIMENSION );
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd52, 0x20);
  }
}

void
#ifdef __USE_PROTOS
logical_statement(AST**_root)
#else
logical_statement(_root)
AST **_root;
#endif
{
#line 173 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 173 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 173 "decl.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==LOGICAL) ) {
          }
          else {zzFAIL(1,zzerr169,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 173 "decl.g"
    zzmatch(LOGICAL);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 173 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==STAR) ) {
#line 173 "decl.g"
          zzmatch(STAR);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 173 "decl.g"
          length_spec(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( (setwd52[LA(1)]&0x40) ) {
          }
          else {zzFAIL(1,zzerr170,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 173 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( 
(LA(1)==COMMA) ) {
#line 173 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==IDENTIFIER) ) {
          }
          else {zzFAIL(1,zzerr171,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 174 "decl.g"
    log_item(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 174 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 174 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 174 "decl.g"
          log_item(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd52, 0x80);
  }
}

void
#ifdef __USE_PROTOS
log_item(AST**_root)
#else
log_item(_root)
AST **_root;
#endif
{
#line 175 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (LA(1)==IDENTIFIER) && (setwd53[LA(2)]&0x1) ) {
#line 175 "decl.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 175 "decl.g"
          init_log_item(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 175 "decl.g"
      init_log_item(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      zzGUESS
      if ( !zzrv && (LA(1)==IDENTIFIER) && (setwd53[LA(2)]&0x2) ) {
#line 176 "decl.g"
        {
          zzBLOCK(zztasp2);
          zzMake0;
          {
#line 176 "decl.g"
            uninit_log_item(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
            zzEXIT(zztasp2);
          }
        }
        zzGUESS_DONE
#line 176 "decl.g"
        uninit_log_item(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      /* MR10 */ else {
        /* MR10 */ if ( !zzrv ) zzGUESS_DONE;
        /* MR10 */ if (0) {}     /* last alternative of block is guess block */
        else {zzFAIL(2,zzerr172,zzerr173,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd53, 0x4);
  }
}

void
#ifdef __USE_PROTOS
init_log_item(AST**_root)
#else
init_log_item(_root)
AST **_root;
#endif
{
#line 178 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 178 "decl.g"
    log_var_list(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 178 "decl.g"
    zzmatch(DIV);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 178 "decl.g"
    log_const_list(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 178 "decl.g"
    zzmatch(DIV);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd53, 0x8);
  }
}

void
#ifdef __USE_PROTOS
uninit_log_item(AST**_root)
#else
uninit_log_item(_root)
AST **_root;
#endif
{
#line 179 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 179 "decl.g"
    log_var_list(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd53, 0x10);
  }
}

void
#ifdef __USE_PROTOS
log_var_list(AST**_root)
#else
log_var_list(_root)
AST **_root;
#endif
{
#line 180 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (LA(1)==IDENTIFIER) && (setwd53[LA(2)]&0x20) ) {
#line 180 "decl.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 180 "decl.g"
          var_decl(zzSTR, LOGICAL_ID );
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 180 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 180 "decl.g"
      var_decl(zzSTR, LOGICAL_ID );
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
#line 180 "decl.g"
      zzmatch(COMMA);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 180 "decl.g"
      log_var_list(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (LA(1)==IDENTIFIER) && 
(setwd53[LA(2)]&0x40) ) {
#line 181 "decl.g"
        var_decl(zzSTR, LOGICAL_ID );
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {zzFAIL(2,zzerr174,zzerr175,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd53, 0x80);
  }
}

void
#ifdef __USE_PROTOS
log_const_list(AST**_root)
#else
log_const_list(_root)
AST **_root;
#endif
{
#line 183 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (setwd54[LA(1)]&0x1) && (LA(2)==COMMA) ) {
#line 183 "decl.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 183 "decl.g"
          logical_const(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 183 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 183 "decl.g"
      logical_const(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
#line 183 "decl.g"
      zzmatch(COMMA);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 183 "decl.g"
      log_const_list(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (setwd54[LA(1)]&0x2) && (LA(2)==DIV) ) {
#line 184 "decl.g"
        logical_const(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {zzFAIL(2,zzerr176,zzerr177,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd54, 0x4);
  }
}

void
#ifdef __USE_PROTOS
character_statement(AST**_root)
#else
character_statement(_root)
AST **_root;
#endif
{
#line 190 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 190 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 190 "decl.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==CHARACTER) ) {
          }
          else {zzFAIL(1,zzerr178,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 190 "decl.g"
    zzmatch(CHARACTER);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 190 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==STAR) ) {
#line 190 "decl.g"
          zzmatch(STAR);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 190 "decl.g"
          length_spec(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( 
(setwd54[LA(1)]&0x8) ) {
          }
          else {zzFAIL(1,zzerr179,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 190 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==COMMA) ) {
#line 190 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==IDENTIFIER) ) {
          }
          else {zzFAIL(1,zzerr180,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 191 "decl.g"
    char_item(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 191 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 191 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 191 "decl.g"
          char_item(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd54, 0x10);
  }
}

void
#ifdef __USE_PROTOS
char_item(AST**_root)
#else
char_item(_root)
AST **_root;
#endif
{
#line 192 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (LA(1)==IDENTIFIER) && (setwd54[LA(2)]&0x20) ) {
#line 192 "decl.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 192 "decl.g"
          init_char_item(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 192 "decl.g"
      init_char_item(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      zzGUESS
      if ( !zzrv && (LA(1)==IDENTIFIER) && (setwd54[LA(2)]&0x40) ) {
#line 193 "decl.g"
        {
          zzBLOCK(zztasp2);
          zzMake0;
          {
#line 193 "decl.g"
            uninit_char_item(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
            zzEXIT(zztasp2);
          }
        }
        zzGUESS_DONE
#line 193 "decl.g"
        uninit_char_item(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      /* MR10 */ else {
        /* MR10 */ if ( !zzrv ) zzGUESS_DONE;
        /* MR10 */ if (0) {}     /* last alternative of block is guess block */
        else {zzFAIL(2,zzerr181,zzerr182,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd54, 0x80);
  }
}

void
#ifdef __USE_PROTOS
init_char_item(AST**_root)
#else
init_char_item(_root)
AST **_root;
#endif
{
#line 195 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 195 "decl.g"
    char_var_list(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 195 "decl.g"
    zzmatch(DIV);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 195 "decl.g"
    char_const_list(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 195 "decl.g"
    zzmatch(DIV);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd55, 0x1);
  }
}

void
#ifdef __USE_PROTOS
uninit_char_item(AST**_root)
#else
uninit_char_item(_root)
AST **_root;
#endif
{
#line 196 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 196 "decl.g"
    char_var_list(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd55, 0x2);
  }
}

void
#ifdef __USE_PROTOS
char_var_list(AST**_root)
#else
char_var_list(_root)
AST **_root;
#endif
{
#line 197 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (LA(1)==IDENTIFIER) && (setwd55[LA(2)]&0x4) ) {
#line 197 "decl.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 197 "decl.g"
          var_decl(zzSTR, CHARACTER_ID );
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 197 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 197 "decl.g"
      var_decl(zzSTR, CHARACTER_ID );
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
#line 197 "decl.g"
      zzmatch(COMMA);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 197 "decl.g"
      char_var_list(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (LA(1)==IDENTIFIER) && 
(setwd55[LA(2)]&0x8) ) {
#line 198 "decl.g"
        var_decl(zzSTR, CHARACTER_ID );
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {zzFAIL(2,zzerr183,zzerr184,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd55, 0x10);
  }
}

void
#ifdef __USE_PROTOS
char_const_list(AST**_root)
#else
char_const_list(_root)
AST **_root;
#endif
{
#line 200 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (setwd55[LA(1)]&0x20) && (LA(2)==COMMA) ) {
#line 200 "decl.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 200 "decl.g"
          char_const(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 200 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 200 "decl.g"
      char_const(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
#line 200 "decl.g"
      zzmatch(COMMA);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 200 "decl.g"
      char_const_list(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (setwd55[LA(1)]&0x40) && (LA(2)==DIV) ) {
#line 201 "decl.g"
        char_const(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {zzFAIL(2,zzerr185,zzerr186,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd55, 0x80);
  }
}

void
#ifdef __USE_PROTOS
substring(AST**_root)
#else
substring(_root)
AST **_root;
#endif
{
#line 204 "decl.g"
  zzRULE;
  Attrib i;
  AST *i_ast=NULL;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 204 "decl.g"
    int type;
#line 206 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        zzGUESS_BLOCK
        zzGUESS
        if ( !zzrv && (LA(1)==IDENTIFIER) && (LA(2)==LP) ) {
#line 206 "decl.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
#line 206 "decl.g"
              array_element_reference(zzSTR, RVALUE );
              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
              }     /* MR10 */
#line 206 "decl.g"
              zzmatch(LP);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
              zzEXIT(zztasp3);
            }
          }
          zzGUESS_DONE
#line 206 "decl.g"
          array_element_reference(zzSTR, RVALUE );
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 206 "decl.g"
          zzmatch(LP);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 206 "decl.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              if ( (setwd56[LA(1)]&0x1) ) {
#line 206 "decl.g"
                zzNON_GUESS_MODE {
                   type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
                } else {
                  expression(zzSTR);
                }
              }
              else {
                if ( (LA(1)==COLUMN) ) {
                }
                else {zzFAIL(1,zzerr187,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
              }
              zzEXIT(zztasp3);
            }
          }
#line 207 "decl.g"
          zzmatch(COLUMN);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 207 "decl.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              if ( 
(setwd56[LA(1)]&0x2) ) {
#line 207 "decl.g"
                zzNON_GUESS_MODE {
                   type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
                } else {
                  expression(zzSTR);
                }
              }
              else {
                if ( (LA(1)==RP) ) {
                }
                else {zzFAIL(1,zzerr188,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
              }
              zzEXIT(zztasp3);
            }
          }
#line 207 "decl.g"
          zzmatch(RP);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( !zzrv ) zzGUESS_DONE;
          if ( (LA(1)==IDENTIFIER) && (LA(2)==LP) ) {
#line 208 "decl.g"
            zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
            
            zzNON_GUESS_MODE {
                            i = zzaCur;
              i_ast = zzastCur;
            }
             zzCONSUME;
#line 208 "decl.g"
            zzmatch(LP);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 208 "decl.g"
            {
              zzBLOCK(zztasp3);
              zzMake0;
              {
                if ( (setwd56[LA(1)]&0x4) ) {
#line 208 "decl.g"
                  zzNON_GUESS_MODE {
                     type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
                  } else {
                    expression(zzSTR);
                  }
                }
                else {
                  if ( (LA(1)==COLUMN) ) {
                  }
                  else {zzFAIL(1,zzerr189,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                }
                zzEXIT(zztasp3);
              }
            }
#line 208 "decl.g"
            zzmatch(COLUMN);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 208 "decl.g"
            {
              zzBLOCK(zztasp3);
              zzMake0;
              {
                if ( 
(setwd56[LA(1)]&0x8) ) {
#line 208 "decl.g"
                  zzNON_GUESS_MODE {
                     type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
                  } else {
                    expression(zzSTR);
                  }
                }
                else {
                  if ( (LA(1)==RP) ) {
                  }
                  else {zzFAIL(1,zzerr190,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                }
                zzEXIT(zztasp3);
              }
            }
#line 208 "decl.g"
            zzmatch(RP);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
            
            zzNON_GUESS_MODE {
#line 209 "decl.g"

              ChangeType( i.text,CHARACTER_ID); /*Now I know that it is a character string*/
              zzastArg(1)->token = CHARACTER_SUBSTRING;
            }
 zzCONSUME;

          }
          else {zzFAIL(2,zzerr191,zzerr192,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd56, 0x10);
  }
}

void
#ifdef __USE_PROTOS
external_statement(AST**_root)
#else
external_statement(_root)
AST **_root;
#endif
{
#line 218 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 218 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 218 "decl.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==EXTERNAL) ) {
          }
          else {zzFAIL(1,zzerr193,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 218 "decl.g"
    zzmatch(EXTERNAL);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 218 "decl.g"
    function_name(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 218 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 218 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 218 "decl.g"
          function_name(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd56, 0x20);
  }
}

void
#ifdef __USE_PROTOS
function_name(AST**_root)
#else
function_name(_root)
AST **_root;
#endif
{
#line 219 "decl.g"
  zzRULE;
  Attrib i;
  AST *i_ast=NULL;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 220 "decl.g"
    zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
            i = zzaCur;
      i_ast = zzastCur;
    }
    
    zzNON_GUESS_MODE {
#line 221 "decl.g"

      zzastArg(1)->token = FUNCTION_NAME;
      ChangeType( i.text, FUNCTION_NAME);
    }
 zzCONSUME;

    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd56, 0x40);
  }
}

void
#ifdef __USE_PROTOS
intrinsic_statement(AST**_root)
#else
intrinsic_statement(_root)
AST **_root;
#endif
{
#line 230 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 230 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 230 "decl.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==INTRINSIC) ) {
          }
          else {zzFAIL(1,zzerr194,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 230 "decl.g"
    zzmatch(INTRINSIC);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 230 "decl.g"
    function_name(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 230 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 230 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 230 "decl.g"
          function_name(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd56, 0x80);
  }
}

void
#ifdef __USE_PROTOS
save_statement(AST**_root)
#else
save_statement(_root)
AST **_root;
#endif
{
#line 236 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 236 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 236 "decl.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==SAVE) ) {
          }
          else {zzFAIL(1,zzerr195,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 236 "decl.g"
    zzmatch(SAVE);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 236 "decl.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 236 "decl.g"
    save_item(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 236 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 236 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 236 "decl.g"
          save_item(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
#line 236 "decl.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd57, 0x1);
  }
}

void
#ifdef __USE_PROTOS
save_item(AST**_root)
#else
save_item(_root)
AST **_root;
#endif
{
#line 238 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    if ( (LA(1)==DIV) ) {
#line 239 "decl.g"
      zzmatch(DIV);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 239 "decl.g"
      zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 239 "decl.g"
      zzmatch(DIV);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
    }
    else {
      if ( (LA(1)==IDENTIFIER) ) {
#line 240 "decl.g"
        zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
      }
      else {zzFAIL(1,zzerr196,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd57, 0x2);
  }
}

void
#ifdef __USE_PROTOS
implicit_statement(AST**_root)
#else
implicit_statement(_root)
AST **_root;
#endif
{
#line 246 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 246 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 246 "decl.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==IMPLICIT) ) {
          }
          else {zzFAIL(1,zzerr197,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 246 "decl.g"
    zzmatch(IMPLICIT);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 246 "decl.g"
    implicit_item(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 246 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 246 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 246 "decl.g"
          implicit_item(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd57, 0x4);
  }
}

void
#ifdef __USE_PROTOS
implicit_item(AST**_root)
#else
implicit_item(_root)
AST **_root;
#endif
{
#line 248 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 248 "decl.g"
    implicit_type(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 248 "decl.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 248 "decl.g"
    letter_spec(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 248 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 248 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 248 "decl.g"
          letter_spec(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
#line 248 "decl.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd57, 0x8);
  }
}

void
#ifdef __USE_PROTOS
implicit_type(AST**_root)
#else
implicit_type(_root)
AST **_root;
#endif
{
#line 251 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 251 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==INTEGER) ) {
#line 251 "decl.g"
          zzmatch(INTEGER);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==REAL) ) {
#line 252 "decl.g"
            zzmatch(REAL);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
          }
          else {
            if ( (LA(1)==DOUBLE_PRECISION) ) {
#line 253 "decl.g"
              zzmatch(DOUBLE_PRECISION);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
            }
            else {
              if ( (LA(1)==LOGICAL) ) {
#line 254 "decl.g"
                zzmatch(LOGICAL);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
              }
              else {
                if ( 
(LA(1)==CHARACTER) ) {
#line 255 "decl.g"
                  zzmatch(CHARACTER);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
                }
                else {
                  if ( (LA(1)==COMPLEX) ) {
#line 256 "decl.g"
                    zzmatch(COMPLEX);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
                  }
                  else {
                    if ( (LA(1)==DOUBLE_COMPLEX) ) {
#line 257 "decl.g"
                      zzmatch(DOUBLE_COMPLEX);zzNON_GUESS_MODE {
                         zzsubchild(_root, &_sibling, &_tail);                      }
                       zzCONSUME;
                    }
                    else {zzFAIL(1,zzerr198,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                  }
                }
              }
            }
          }
        }
        zzEXIT(zztasp2);
      }
    }
#line 258 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==STAR) ) {
#line 258 "decl.g"
          zzmatch(STAR);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 258 "decl.g"
          length_spec(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( (LA(1)==LP) ) {
          }
          else {zzFAIL(1,zzerr199,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd57, 0x10);
  }
}

void
#ifdef __USE_PROTOS
letter_spec(AST**_root)
#else
letter_spec(_root)
AST **_root;
#endif
{
#line 261 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 261 "decl.g"
    zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 261 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( 
(LA(1)==MIN) ) {
#line 261 "decl.g"
          zzmatch(MIN);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 261 "decl.g"
          zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (setwd57[LA(1)]&0x20) ) {
          }
          else {zzFAIL(1,zzerr200,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd57, 0x40);
  }
}

void
#ifdef __USE_PROTOS
parameter_statement(AST**_root)
#else
parameter_statement(_root)
AST **_root;
#endif
{
#line 267 "decl.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 267 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 267 "decl.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==PARAMETER) ) {
          }
          else {zzFAIL(1,zzerr201,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 267 "decl.g"
    zzmatch(PARAMETER);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 267 "decl.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 267 "decl.g"
    para_item(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 267 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 267 "decl.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 267 "decl.g"
          para_item(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
#line 267 "decl.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd57, 0x80);
  }
}

void
#ifdef __USE_PROTOS
para_item(AST**_root)
#else
para_item(_root)
AST **_root;
#endif
{
#line 270 "decl.g"
  zzRULE;
  Attrib i;
  AST *i_ast=NULL;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 270 "decl.g"
    int type;
#line 271 "decl.g"
    zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
            i = zzaCur;
      i_ast = zzastCur;
    }
     zzCONSUME;
#line 271 "decl.g"
    zzmatch(EQUAL);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 271 "decl.g"
    zzNON_GUESS_MODE {
       type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
    } else {
      expression(zzSTR);
    }
    zzNON_GUESS_MODE {
#line 272 "decl.g"

      assert((type == INTEGER_ID) || (type == REAL_ID) || (type == CHARACTER_ID) || (type == LOGICAL_ID));
      ChangeType( i.text, type);
      zzastArg(1)->token = CONSTANT_NAME;
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd58, 0x1);
  }
}

void
#ifdef __USE_PROTOS
assign_statement(AST**_root)
#else
assign_statement(_root)
AST **_root;
#endif
{
#line 282 "decl.g"
  zzRULE;
  Attrib i;
  AST *i_ast=NULL;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 282 "decl.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 282 "decl.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==ASSIGN) ) {
          }
          else {zzFAIL(1,zzerr202,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 282 "decl.g"
    zzmatch(ASSIGN);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 282 "decl.g"
    zzmatch(CONSTINT);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 282 "decl.g"
    zzmatch(TO);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 282 "decl.g"
    zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
            i = zzaCur;
      i_ast = zzastCur;
    }
    
    zzNON_GUESS_MODE {
#line 283 "decl.g"

      AddSymbol( i.text, INTEGER_ID);
    }
 zzCONSUME;

    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd58, 0x2);
  }
}
