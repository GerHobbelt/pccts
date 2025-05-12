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


int
#ifdef __USE_PROTOS
expression(AST**_root)
#else
expression(_root)
AST **_root;
#endif
{
  int   _retv;
#line 4 "expr.g"
  zzRULE;
  zzBLOCK(zztasp1);
  PCCTS_PURIFY(_retv,sizeof(int  ))
  zzMake0;
  {
#line 4 "expr.g"
    int type = 0;
#line 5 "expr.g"
    expr0(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzNON_GUESS_MODE {
#line 6 "expr.g"
      _retv = type;
    }
    zzEXIT(zztasp1);
    return _retv;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd43, 0x20);
    return _retv;
  }
}

void
#ifdef __USE_PROTOS
expr0(AST**_root)
#else
expr0(_root)
AST **_root;
#endif
{
#line 9 "expr.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
#line 9 "expr.g"
    int type;
    zzGUESS
    if ( !zzrv && (setwd43[LA(1)]&0x40) && (setwd43[LA(2)]&0x80) ) {
#line 10 "expr.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 10 "expr.g"
          expr1(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 10 "expr.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              if ( (LA(1)==PLU) ) {
#line 10 "expr.g"
                zzmatch(PLU);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
              }
              else {
                if ( (LA(1)==MIN) ) {
#line 10 "expr.g"
                  zzmatch(MIN);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
                }
                else {
                  if ( 
(LA(1)==AND) ) {
#line 10 "expr.g"
                    zzmatch(AND);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
                  }
                  else {
                    if ( (LA(1)==OR) ) {
#line 10 "expr.g"
                      zzmatch(OR);zzNON_GUESS_MODE {
                         zzsubchild(_root, &_sibling, &_tail);                      }
                       zzCONSUME;
                    }
                    else {
                      if ( (LA(1)==NEQV) ) {
#line 10 "expr.g"
                        zzmatch(NEQV);zzNON_GUESS_MODE {
                           zzsubchild(_root, &_sibling, &_tail);                        }
                         zzCONSUME;
                      }
                      else {
                        if ( (LA(1)==EQV) ) {
#line 10 "expr.g"
                          zzmatch(EQV);zzNON_GUESS_MODE {
                             zzsubchild(_root, &_sibling, &_tail);                          }
                           zzCONSUME;
                        }
                        else {zzFAIL(1,zzerr122,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                      }
                    }
                  }
                }
              }
              zzEXIT(zztasp3);
            }
          }
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 11 "expr.g"
      expr1(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
#line 11 "expr.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
          if ( (LA(1)==PLU) ) {
#line 11 "expr.g"
            zzmatch(PLU);zzNON_GUESS_MODE {
               zzsubroot(_root, &_sibling, &_tail);            }
             zzCONSUME;
          }
          else {
            if ( 
(LA(1)==MIN) ) {
#line 11 "expr.g"
              zzmatch(MIN);zzNON_GUESS_MODE {
                 zzsubroot(_root, &_sibling, &_tail);              }
               zzCONSUME;
            }
            else {
              if ( (LA(1)==AND) ) {
#line 11 "expr.g"
                zzmatch(AND);zzNON_GUESS_MODE {
                   zzsubroot(_root, &_sibling, &_tail);                }
                 zzCONSUME;
              }
              else {
                if ( (LA(1)==OR) ) {
#line 11 "expr.g"
                  zzmatch(OR);zzNON_GUESS_MODE {
                     zzsubroot(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
                }
                else {
                  if ( (LA(1)==NEQV) ) {
#line 11 "expr.g"
                    zzmatch(NEQV);zzNON_GUESS_MODE {
                       zzsubroot(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
                  }
                  else {
                    if ( (LA(1)==EQV) ) {
#line 11 "expr.g"
                      zzmatch(EQV);zzNON_GUESS_MODE {
                         zzsubroot(_root, &_sibling, &_tail);                      }
                       zzCONSUME;
                    }
                    else {zzFAIL(1,zzerr123,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                  }
                }
              }
            }
          }
          zzEXIT(zztasp2);
        }
      }
#line 11 "expr.g"
      expr0(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( 
(setwd44[LA(1)]&0x1) && (setwd44[LA(2)]&0x2) ) {
#line 12 "expr.g"
        expr1(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {zzFAIL(2,zzerr124,zzerr125,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd44, 0x4);
  }
}

void
#ifdef __USE_PROTOS
expr1(AST**_root)
#else
expr1(_root)
AST **_root;
#endif
{
#line 15 "expr.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
#line 15 "expr.g"
    int type;
    zzGUESS
    if ( !zzrv && (setwd44[LA(1)]&0x8) && (setwd44[LA(2)]&0x10) ) {
#line 16 "expr.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 16 "expr.g"
          expr2(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 16 "expr.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              if ( (LA(1)==DIV) ) {
#line 16 "expr.g"
                zzmatch(DIV);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
              }
              else {
                if ( (LA(1)==STAR) ) {
#line 16 "expr.g"
                  zzmatch(STAR);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
                }
                else {
                  if ( (LA(1)==LT) ) {
#line 16 "expr.g"
                    zzmatch(LT);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
                  }
                  else {
                    if ( 
(LA(1)==LE) ) {
#line 16 "expr.g"
                      zzmatch(LE);zzNON_GUESS_MODE {
                         zzsubchild(_root, &_sibling, &_tail);                      }
                       zzCONSUME;
                    }
                    else {
                      if ( (LA(1)==EQ) ) {
#line 16 "expr.g"
                        zzmatch(EQ);zzNON_GUESS_MODE {
                           zzsubchild(_root, &_sibling, &_tail);                        }
                         zzCONSUME;
                      }
                      else {
                        if ( (LA(1)==NE) ) {
#line 16 "expr.g"
                          zzmatch(NE);zzNON_GUESS_MODE {
                             zzsubchild(_root, &_sibling, &_tail);                          }
                           zzCONSUME;
                        }
                        else {
                          if ( (LA(1)==GT) ) {
#line 16 "expr.g"
                            zzmatch(GT);zzNON_GUESS_MODE {
                               zzsubchild(_root, &_sibling, &_tail);                            }
                             zzCONSUME;
                          }
                          else {
                            if ( (LA(1)==GE) ) {
#line 16 "expr.g"
                              zzmatch(GE);zzNON_GUESS_MODE {
                                 zzsubchild(_root, &_sibling, &_tail);                              }
                               zzCONSUME;
                            }
                            else {
                              if ( 
(LA(1)==IS) ) {
#line 16 "expr.g"
                                zzmatch(IS);zzNON_GUESS_MODE {
                                   zzsubchild(_root, &_sibling, &_tail);                                }
                                 zzCONSUME;
                              }
                              else {
                                if ( (LA(1)==CONCAT) ) {
#line 16 "expr.g"
                                  zzmatch(CONCAT);zzNON_GUESS_MODE {
                                     zzsubchild(_root, &_sibling, &_tail);                                  }
                                   zzCONSUME;
                                }
                                else {zzFAIL(1,zzerr126,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
              zzEXIT(zztasp3);
            }
          }
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 17 "expr.g"
      expr2(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
#line 17 "expr.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
          if ( (LA(1)==DIV) ) {
#line 17 "expr.g"
            zzmatch(DIV);zzNON_GUESS_MODE {
               zzsubroot(_root, &_sibling, &_tail);            }
             zzCONSUME;
          }
          else {
            if ( (LA(1)==STAR) ) {
#line 17 "expr.g"
              zzmatch(STAR);zzNON_GUESS_MODE {
                 zzsubroot(_root, &_sibling, &_tail);              }
              
              zzNON_GUESS_MODE {
#line 17 "expr.g"
                zzastArg(1)->token = MUL;
              }
 zzCONSUME;

            }
            else {
              if ( (LA(1)==LT) ) {
#line 17 "expr.g"
                zzmatch(LT);zzNON_GUESS_MODE {
                   zzsubroot(_root, &_sibling, &_tail);                }
                 zzCONSUME;
              }
              else {
                if ( 
(LA(1)==LE) ) {
#line 17 "expr.g"
                  zzmatch(LE);zzNON_GUESS_MODE {
                     zzsubroot(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
                }
                else {
                  if ( (LA(1)==EQ) ) {
#line 17 "expr.g"
                    zzmatch(EQ);zzNON_GUESS_MODE {
                       zzsubroot(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
                  }
                  else {
                    if ( (LA(1)==NE) ) {
#line 17 "expr.g"
                      zzmatch(NE);zzNON_GUESS_MODE {
                         zzsubroot(_root, &_sibling, &_tail);                      }
                       zzCONSUME;
                    }
                    else {
                      if ( (LA(1)==GT) ) {
#line 17 "expr.g"
                        zzmatch(GT);zzNON_GUESS_MODE {
                           zzsubroot(_root, &_sibling, &_tail);                        }
                         zzCONSUME;
                      }
                      else {
                        if ( (LA(1)==GE) ) {
#line 17 "expr.g"
                          zzmatch(GE);zzNON_GUESS_MODE {
                             zzsubroot(_root, &_sibling, &_tail);                          }
                           zzCONSUME;
                        }
                        else {
                          if ( 
(LA(1)==IS) ) {
#line 17 "expr.g"
                            zzmatch(IS);zzNON_GUESS_MODE {
                               zzsubroot(_root, &_sibling, &_tail);                            }
                             zzCONSUME;
                          }
                          else {
                            if ( (LA(1)==CONCAT) ) {
#line 17 "expr.g"
                              zzmatch(CONCAT);zzNON_GUESS_MODE {
                                 zzsubroot(_root, &_sibling, &_tail);                              }
                               zzCONSUME;
                            }
                            else {zzFAIL(1,zzerr127,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
          zzEXIT(zztasp2);
        }
      }
#line 17 "expr.g"
      expr1(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (setwd44[LA(1)]&0x20) && (setwd44[LA(2)]&0x40) ) {
#line 18 "expr.g"
        expr2(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {zzFAIL(2,zzerr128,zzerr129,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd44, 0x80);
  }
}

void
#ifdef __USE_PROTOS
expr2(AST**_root)
#else
expr2(_root)
AST **_root;
#endif
{
#line 21 "expr.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
#line 21 "expr.g"
    int type;
    zzGUESS
    if ( !zzrv && (setwd45[LA(1)]&0x1) && (setwd45[LA(2)]&0x2) ) {
#line 22 "expr.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 22 "expr.g"
          zzNON_GUESS_MODE {
             type  = operand(zzSTR); zzlink(_root, &_sibling, &_tail);
          } else {
            operand(zzSTR);
          }
#line 22 "expr.g"
          zzmatch(POW);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 23 "expr.g"
      zzNON_GUESS_MODE {
         type  = operand(zzSTR); zzlink(_root, &_sibling, &_tail);
      } else {
        operand(zzSTR);
      }
#line 23 "expr.g"
      zzmatch(POW);zzNON_GUESS_MODE {
         zzsubroot(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 23 "expr.g"
      expr2(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (setwd45[LA(1)]&0x4) && 
(setwd45[LA(2)]&0x8) ) {
#line 24 "expr.g"
        zzNON_GUESS_MODE {
           type  = operand(zzSTR); zzlink(_root, &_sibling, &_tail);
        } else {
          operand(zzSTR);
        }
      }
      else {zzFAIL(2,zzerr130,zzerr131,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd45, 0x10);
  }
}

int
#ifdef __USE_PROTOS
operand(AST**_root)
#else
operand(_root)
AST **_root;
#endif
{
  int   _retv;
#line 27 "expr.g"
  zzRULE;
  zzBLOCK(zztasp1);
  PCCTS_PURIFY(_retv,sizeof(int  ))
  zzMake0;
  {
#line 27 "expr.g"
    int type = 0;
    if ( (LA(1)==LP) ) {
#line 28 "expr.g"
      zzmatch(LP);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 28 "expr.g"
      zzNON_GUESS_MODE {
         type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
      } else {
        expression(zzSTR);
      }
#line 28 "expr.g"
      zzmatch(RP);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
    }
    else {
      if ( (LA(1)==IDENTIFIER) ) {
#line 29 "expr.g"
        variable(zzSTR, RVALUE );
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {
        if ( (setwd45[LA(1)]&0x20) ) {
#line 30 "expr.g"
          zzNON_GUESS_MODE {
             type  = constant(zzSTR); zzlink(_root, &_sibling, &_tail);
          } else {
            constant(zzSTR);
          }
        }
        else {
          if ( (LA(1)==PLU) ) {
#line 31 "expr.g"
            zzmatch(PLU);zzNON_GUESS_MODE {
               zzsubroot(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 31 "expr.g"
            expr0(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
            zzNON_GUESS_MODE {
#line 31 "expr.g"
              zzastArg(1)->token = UNARY_PLU;
            }
          }
          else {
            if ( (LA(1)==MIN) ) {
#line 32 "expr.g"
              zzmatch(MIN);zzNON_GUESS_MODE {
                 zzsubroot(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 32 "expr.g"
              expr0(zzSTR);
              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
              }     /* MR10 */
              zzNON_GUESS_MODE {
#line 32 "expr.g"
                zzastArg(1)->token = UNARY_MIN;
              }
            }
            else {
              if ( 
(LA(1)==NOT) ) {
#line 33 "expr.g"
                zzmatch(NOT);zzNON_GUESS_MODE {
                   zzsubroot(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 33 "expr.g"
                expr0(zzSTR);
                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                }     /* MR10 */
                zzNON_GUESS_MODE {
#line 34 "expr.g"
                  _retv = type;
                }
              }
              else {zzFAIL(1,zzerr132,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
            }
          }
        }
      }
    }
    zzEXIT(zztasp1);
    return _retv;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd45, 0x40);
    return _retv;
  }
}
