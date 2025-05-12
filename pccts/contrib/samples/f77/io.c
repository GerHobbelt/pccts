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
read_statement(AST**_root)
#else
read_statement(_root)
AST **_root;
#endif
{
#line 1 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 1 "io.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==READ) ) {
          }
          else {zzFAIL(1,zzerr203,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1 "io.g"
    zzmatch(READ);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1 "io.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1 "io.g"
    control_info(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1 "io.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1 "io.g"
    io_list(zzSTR, LVALUE );
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd58, 0x4);
  }
}

void
#ifdef __USE_PROTOS
write_statement(AST**_root)
#else
write_statement(_root)
AST **_root;
#endif
{
#line 4 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 4 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( 
(LA(1)==LABEL) ) {
#line 4 "io.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==WRITE) ) {
          }
          else {zzFAIL(1,zzerr204,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 4 "io.g"
    zzmatch(WRITE);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 4 "io.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 4 "io.g"
    control_info(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 4 "io.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 4 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        zzGUESS_BLOCK
        zzGUESS
        if ( !zzrv && (setwd58[LA(1)]&0x8) && (setwd58[LA(2)]&0x10) ) {
#line 4 "io.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
#line 4 "io.g"
              io_list(zzSTR, RVALUE );
              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
              }     /* MR10 */
              zzEXIT(zztasp3);
            }
          }
          zzGUESS_DONE
#line 4 "io.g"
          io_list(zzSTR, RVALUE );
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( !zzrv ) zzGUESS_DONE;
          if ( (setwd58[LA(1)]&0x20) && (setwd58[LA(2)]&0x40) ) {
          }
          else {zzFAIL(2,zzerr205,zzerr206,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
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
    zzresynch(setwd58, 0x80);
  }
}

void
#ifdef __USE_PROTOS
control_info(AST**_root)
#else
control_info(_root)
AST **_root;
#endif
{
#line 7 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 7 "io.g"
    int type; int dummy;
#line 9 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        zzGUESS_BLOCK
        zzGUESS
        if ( !zzrv && (setwd59[LA(1)]&0x1) && 
(setwd59[LA(2)]&0x2) ) {
#line 9 "io.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
#line 9 "io.g"
              unit_identifier(zzSTR);
              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
              }     /* MR10 */
#line 9 "io.g"
              zzmatch(COMMA);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 9 "io.g"
              format_identifier(zzSTR);
              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
              }     /* MR10 */
              zzEXIT(zztasp3);
            }
          }
          zzGUESS_DONE
#line 9 "io.g"
          unit_identifier(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 9 "io.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubroot(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 9 "io.g"
          format_identifier(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( !zzrv ) zzGUESS_DONE;
          zzGUESS
          if ( !zzrv && (setwd59[LA(1)]&0x4) && (setwd59[LA(2)]&0x8) ) {
#line 10 "io.g"
            {
              zzBLOCK(zztasp3);
              zzMake0;
              {
#line 10 "io.g"
                combined_expression(zzSTR);
                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                }     /* MR10 */
#line 10 "io.g"
                zzmatch(COMMA);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 10 "io.g"
                format_identifier(zzSTR);
                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                }     /* MR10 */
                zzEXIT(zztasp3);
              }
            }
            zzGUESS_DONE
#line 10 "io.g"
            combined_expression(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
#line 10 "io.g"
            zzmatch(COMMA);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 10 "io.g"
            format_identifier(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
          }
          else {
            if ( !zzrv ) zzGUESS_DONE;
            zzGUESS
            if ( !zzrv && (setwd59[LA(1)]&0x10) && (setwd59[LA(2)]&0x20) ) {
#line 11 "io.g"
              {
                zzBLOCK(zztasp3);
                zzMake0;
                {
#line 11 "io.g"
                  unit_identifier(zzSTR);
                  if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                  }     /* MR10 */
#line 11 "io.g"
                  zzmatch(APOSTROPHY);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
                  zzEXIT(zztasp3);
                }
              }
              zzGUESS_DONE
#line 11 "io.g"
              combined_expression(zzSTR);
              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
              }     /* MR10 */
            }
            else {
              if ( !zzrv ) zzGUESS_DONE;
              if ( (LA(1)==UNIT) ) {
#line 12 "io.g"
                zzmatch(UNIT);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 12 "io.g"
                zzmatch(EQUAL);zzNON_GUESS_MODE {
                   zzsubroot(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 12 "io.g"
                unit_identifier(zzSTR);
                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                }     /* MR10 */
              }
              else {
                if ( !zzrv ) zzGUESS_DONE;
                if ( (setwd59[LA(1)]&0x40) && (setwd59[LA(2)]&0x80) ) {
#line 13 "io.g"
                  unit_identifier(zzSTR);
                  if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                  }     /* MR10 */
                }
                else {zzFAIL(2,zzerr207,zzerr208,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
              }
            }
          }
        }
        zzEXIT(zztasp2);
      }
    }
#line 22 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 15 "io.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 16 "io.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              if ( (LA(1)==FMT) ) {
#line 16 "io.g"
                zzmatch(FMT);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 16 "io.g"
                zzmatch(EQUAL);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 16 "io.g"
                format_identifier(zzSTR);
                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                }     /* MR10 */
              }
              else {
                if ( (LA(1)==IO_DATA) ) {
#line 17 "io.g"
                  zzmatch(IO_DATA);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
#line 17 "io.g"
                  zzmatch(EQUAL);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
#line 17 "io.g"
                  zzNON_GUESS_MODE {
                     type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
                  } else {
                    expression(zzSTR);
                  }
                }
                else {
                  if ( (LA(1)==REC) ) {
#line 18 "io.g"
                    zzmatch(REC);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
#line 18 "io.g"
                    zzmatch(EQUAL);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
#line 18 "io.g"
                    zzNON_GUESS_MODE {
                       type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
                    } else {
                      expression(zzSTR);
                    }
                  }
                  else {
                    if ( (LA(1)==END) ) {
#line 19 "io.g"
                      zzmatch(END);zzNON_GUESS_MODE {
                         zzsubchild(_root, &_sibling, &_tail);                      }
                       zzCONSUME;
#line 19 "io.g"
                      zzmatch(EQUAL);zzNON_GUESS_MODE {
                         zzsubchild(_root, &_sibling, &_tail);                      }
                       zzCONSUME;
#line 19 "io.g"
                      label(zzSTR);
                      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                      }     /* MR10 */
                    }
                    else {
                      if ( 
(LA(1)==ERR) ) {
#line 20 "io.g"
                        zzmatch(ERR);zzNON_GUESS_MODE {
                           zzsubchild(_root, &_sibling, &_tail);                        }
                         zzCONSUME;
#line 20 "io.g"
                        zzmatch(EQUAL);zzNON_GUESS_MODE {
                           zzsubchild(_root, &_sibling, &_tail);                        }
                         zzCONSUME;
#line 20 "io.g"
                        label(zzSTR);
                        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                        }     /* MR10 */
                      }
                      else {
                        if ( (LA(1)==IOSTAT) ) {
#line 21 "io.g"
                          {
                            zzBLOCK(zztasp4);
                            zzMake0;
                            {
#line 21 "io.g"
                              zzmatch(IOSTAT);zzNON_GUESS_MODE {
                                 zzsubchild(_root, &_sibling, &_tail);                              }
                               zzCONSUME;
#line 21 "io.g"
                              zzmatch(EQUAL);zzNON_GUESS_MODE {
                                 zzsubchild(_root, &_sibling, &_tail);                              }
                               zzCONSUME;
#line 21 "io.g"
                              zzNON_GUESS_MODE {
                                 dummy  = operand(zzSTR); zzlink(_root, &_sibling, &_tail);
                              } else {
                                operand(zzSTR);
                              }
                              zzEXIT(zztasp4);
                            }
                          }
                        }
                        else {
                          if ( (LA(1)==URGENT) ) {
#line 22 "io.g"
                            zzmatch(URGENT);zzNON_GUESS_MODE {
                               zzsubchild(_root, &_sibling, &_tail);                            }
                             zzCONSUME;
#line 22 "io.g"
                            zzmatch(EQUAL);zzNON_GUESS_MODE {
                               zzsubchild(_root, &_sibling, &_tail);                            }
                             zzCONSUME;
#line 22 "io.g"
                            zzNON_GUESS_MODE {
                               type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
                            } else {
                              expression(zzSTR);
                            }
                          }
                          else {zzFAIL(1,zzerr209,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                        }
                      }
                    }
                  }
                }
              }
              zzEXIT(zztasp3);
            }
          }
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
    zzresynch(setwd60, 0x1);
  }
}

void
#ifdef __USE_PROTOS
unit_identifier(AST**_root)
#else
unit_identifier(_root)
AST **_root;
#endif
{
#line 25 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
#line 25 "io.g"
    int type;
    zzGUESS
    if ( !zzrv && (LA(1)==STAR) ) {
#line 26 "io.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 26 "io.g"
          zzmatch(STAR);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 26 "io.g"
      zzmatch(STAR);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (setwd60[LA(1)]&0x2) ) {
#line 27 "io.g"
        zzNON_GUESS_MODE {
           type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
        } else {
          expression(zzSTR);
        }
      }
      else {zzFAIL(1,zzerr210,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd60, 0x4);
  }
}

void
#ifdef __USE_PROTOS
format_identifier(AST**_root)
#else
format_identifier(_root)
AST **_root;
#endif
{
#line 29 "io.g"
  zzRULE;
  Attrib i;
  AST *i_ast=NULL;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
#line 29 "io.g"
    int type;
    zzGUESS
    if ( !zzrv && 
(LA(1)==STAR) ) {
#line 30 "io.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 30 "io.g"
          zzmatch(STAR);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 30 "io.g"
      zzmatch(STAR);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 30 "io.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
          if ( (LA(1)==DIV) ) {
#line 30 "io.g"
            zzmatch(DIV);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
            
            zzNON_GUESS_MODE {
#line 30 "io.g"
              zzastArg(1)->token = SLASH;
            }
 zzCONSUME;

          }
          else {
            if ( (setwd60[LA(1)]&0x8) ) {
            }
            else {zzFAIL(1,zzerr211,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
          }
          zzEXIT(zztasp2);
        }
      }
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (LA(1)==DIV) ) {
#line 31 "io.g"
        zzmatch(DIV);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
        
        zzNON_GUESS_MODE {
#line 31 "io.g"
          zzastArg(1)->token = SLASH;
        }
 zzCONSUME;

      }
      else {
        if ( !zzrv ) zzGUESS_DONE;
        if ( (LA(1)==IDENTIFIER) ) {
#line 32 "io.g"
          zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
          
          zzNON_GUESS_MODE {
                        i = zzaCur;
            i_ast = zzastCur;
          }
          
          zzNON_GUESS_MODE {
#line 33 "io.g"

            /*If it has been assigned a label before than it must have been stored into the symbol table
            as an INTEGER_ID, if not than it must be a CHARACTER_ID*/
            type = LookUp( i.text);
            assert((type == INTEGER_ID) || (type == CHARACTER_ID) || (type == REAL_ID) || (type == -1));
            if(type == -1) {
              type = CHARACTER_ID;
              AddSymbol( i.text, CHARACTER_ID);
            }
            else if(type == REAL_ID) {
              type = CHARACTER_ID;
              ChangeType( i.text, CHARACTER_ID);
            }
            zzastArg(1)->token = type;
          }
 zzCONSUME;

        }
        else {
          if ( !zzrv ) zzGUESS_DONE;
          if ( 
(LA(1)==QUOTED_STRING) ) {
#line 48 "io.g"
            zzmatch(QUOTED_STRING);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
          }
          else {
            if ( !zzrv ) zzGUESS_DONE;
            if ( (LA(1)==CONSTINT) ) {
#line 49 "io.g"
              label(zzSTR);
              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
              }     /* MR10 */
            }
            else {zzFAIL(1,zzerr212,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
          }
        }
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd60, 0x10);
  }
}

void
#ifdef __USE_PROTOS
combined_expression(AST**_root)
#else
combined_expression(_root)
AST **_root;
#endif
{
#line 52 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 52 "io.g"
    int type;
#line 53 "io.g"
    unit_identifier(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 53 "io.g"
    zzmatch(APOSTROPHY);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 53 "io.g"
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
    zzresynch(setwd60, 0x20);
  }
}

void
#ifdef __USE_PROTOS
io_list(AST**_root,int where)
#else
io_list(_root,where)
AST **_root;
 int where ;
#endif
{
#line 55 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 55 "io.g"
    io_list_item(zzSTR, where );
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 56 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 56 "io.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 56 "io.g"
          io_list_item(zzSTR, where );
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
    zzresynch(setwd60, 0x40);
  }
}

void
#ifdef __USE_PROTOS
io_list_item(AST**_root,int where)
#else
io_list_item(_root,where)
AST **_root;
 int where ;
#endif
{
#line 59 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 59 "io.g"
    int type;
#line 61 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        zzGUESS_BLOCK
        zzGUESS
        if ( !zzrv && (LA(1)==LP) && (setwd60[LA(2)]&0x80) ) {
#line 61 "io.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
#line 61 "io.g"
              zzmatch(LP);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
              zzEXIT(zztasp3);
            }
          }
          zzGUESS_DONE
#line 61 "io.g"
          io_implied_do_list(zzSTR, where );
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( !zzrv ) zzGUESS_DONE;
          if ( (setwd61[LA(1)]&0x1) && (setwd61[LA(2)]&0x2) ) {
#line 62 "io.g"
            zzNON_GUESS_MODE {
               type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
            } else {
              expression(zzSTR);
            }
          }
          else {zzFAIL(2,zzerr213,zzerr214,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
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
    zzresynch(setwd61, 0x4);
  }
}

void
#ifdef __USE_PROTOS
io_implied_do_list(AST**_root,int where)
#else
io_implied_do_list(_root,where)
AST **_root;
 int where ;
#endif
{
#line 66 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 67 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
#line 67 "io.g"
        zzmatch(LP);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
        
        zzNON_GUESS_MODE {
#line 67 "io.g"
          zzastArg(1)->token = IMPLIED_LP;
        }
 zzCONSUME;

        zzEXIT(zztasp2);
      }
    }
#line 68 "io.g"
    {
      zzBLOCK(zztasp2);
      int zzcnt=1;
      zzMake0;
      {
        do {
#line 68 "io.g"
          io_list_item(zzSTR, where );
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 68 "io.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzLOOP(zztasp2);
        } while ( (setwd61[LA(1)]&0x8) && (setwd61[LA(2)]&0x10) );
        zzEXIT(zztasp2);
      }
    }
#line 68 "io.g"
    io_implied_do_loop(zzSTR, where );
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 69 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
#line 69 "io.g"
        zzmatch(RP);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
        
        zzNON_GUESS_MODE {
#line 69 "io.g"
          zzastArg(1)->token = IMPLIED_RP;
        }
 zzCONSUME;

        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd61, 0x20);
  }
}

void
#ifdef __USE_PROTOS
io_implied_do_loop(AST**_root,int where)
#else
io_implied_do_loop(_root,where)
AST **_root;
 int where ;
#endif
{
#line 72 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 72 "io.g"
    int type;
#line 73 "io.g"
    zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 73 "io.g"
    zzmatch(EQUAL);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 73 "io.g"
    zzNON_GUESS_MODE {
       type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
    } else {
      expression(zzSTR);
    }
#line 74 "io.g"
    zzmatch(COMMA);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 74 "io.g"
    zzNON_GUESS_MODE {
       type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
    } else {
      expression(zzSTR);
    }
#line 75 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==COMMA) ) {
#line 75 "io.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 75 "io.g"
          zzNON_GUESS_MODE {
             type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
          } else {
            expression(zzSTR);
          }
        }
        else {
          if ( (LA(1)==RP) ) {
          }
          else {zzFAIL(1,zzerr215,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
    zzNON_GUESS_MODE {
#line 76 "io.g"
      zzastArg(1)->token = IMPLIED_DO_VARIABLE;
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd61, 0x40);
  }
}

void
#ifdef __USE_PROTOS
find_statement(AST**_root)
#else
find_statement(_root)
AST **_root;
#endif
{
#line 80 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 80 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 80 "io.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==FIND) ) {
          }
          else {zzFAIL(1,zzerr216,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 80 "io.g"
    zzmatch(FIND);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 80 "io.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 80 "io.g"
    findlist(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 80 "io.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd61, 0x80);
  }
}

void
#ifdef __USE_PROTOS
findlist(AST**_root)
#else
findlist(_root)
AST **_root;
#endif
{
#line 82 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
#line 82 "io.g"
    int type;
    zzGUESS
    if ( !zzrv && 
(setwd62[LA(1)]&0x1) && (setwd62[LA(2)]&0x2) ) {
#line 83 "io.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 83 "io.g"
          unit_identifier(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 83 "io.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 83 "io.g"
      unit_identifier(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
#line 83 "io.g"
      zzmatch(COMMA);zzNON_GUESS_MODE {
         zzsubroot(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 83 "io.g"
      zzmatch(REC);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 83 "io.g"
      zzmatch(EQUAL);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 83 "io.g"
      zzNON_GUESS_MODE {
         type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
      } else {
        expression(zzSTR);
      }
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      zzGUESS
      if ( !zzrv && (setwd62[LA(1)]&0x4) && (setwd62[LA(2)]&0x8) ) {
#line 84 "io.g"
        {
          zzBLOCK(zztasp2);
          zzMake0;
          {
#line 84 "io.g"
            unit_identifier(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
#line 84 "io.g"
            zzmatch(APOSTROPHY);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
            zzEXIT(zztasp2);
          }
        }
        zzGUESS_DONE
#line 84 "io.g"
        unit_identifier(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
#line 84 "io.g"
        zzmatch(APOSTROPHY);zzNON_GUESS_MODE {
           zzsubroot(_root, &_sibling, &_tail);        }
         zzCONSUME;
#line 84 "io.g"
        zzNON_GUESS_MODE {
           type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
        } else {
          expression(zzSTR);
        }
      }
      else {
        if ( !zzrv ) zzGUESS_DONE;
        if ( (LA(1)==UNIT) ) {
#line 85 "io.g"
          zzmatch(UNIT);zzNON_GUESS_MODE {
             zzsubroot(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 85 "io.g"
          zzmatch(EQUAL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 85 "io.g"
          unit_identifier(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 85 "io.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 85 "io.g"
          zzmatch(REC);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 85 "io.g"
          zzmatch(EQUAL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 85 "io.g"
          zzNON_GUESS_MODE {
             type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
          } else {
            expression(zzSTR);
          }
        }
        else {
          if ( !zzrv ) zzGUESS_DONE;
          if ( (LA(1)==REC) ) {
#line 86 "io.g"
            zzmatch(REC);zzNON_GUESS_MODE {
               zzsubroot(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 86 "io.g"
            zzmatch(EQUAL);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 86 "io.g"
            zzNON_GUESS_MODE {
               type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
            } else {
              expression(zzSTR);
            }
#line 86 "io.g"
            zzmatch(COMMA);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 86 "io.g"
            zzmatch(UNIT);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 86 "io.g"
            zzmatch(EQUAL);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 86 "io.g"
            unit_identifier(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
          }
          else {zzFAIL(2,zzerr217,zzerr218,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd62, 0x10);
  }
}

void
#ifdef __USE_PROTOS
open_statement(AST**_root)
#else
open_statement(_root)
AST **_root;
#endif
{
#line 91 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 91 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 91 "io.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( 
(LA(1)==OPEN) ) {
          }
          else {zzFAIL(1,zzerr219,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 91 "io.g"
    zzmatch(OPEN);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 91 "io.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 91 "io.g"
    open_item(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 91 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 91 "io.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 91 "io.g"
          open_item(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
#line 91 "io.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd62, 0x20);
  }
}

void
#ifdef __USE_PROTOS
open_item(AST**_root)
#else
open_item(_root)
AST **_root;
#endif
{
#line 93 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 93 "io.g"
    int type; int dummy;
    if ( (setwd62[LA(1)]&0x40) ) {
#line 94 "io.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
          if ( (LA(1)==UNIT) ) {
#line 94 "io.g"
            zzmatch(UNIT);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 94 "io.g"
            zzmatch(EQUAL);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
          }
          else {
            if ( (setwd62[LA(1)]&0x80) ) {
            }
            else {zzFAIL(1,zzerr220,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
          }
          zzEXIT(zztasp2);
        }
      }
#line 94 "io.g"
      unit_identifier(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( (LA(1)==ERR) ) {
#line 95 "io.g"
        zzmatch(ERR);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
#line 95 "io.g"
        zzmatch(EQUAL);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
#line 95 "io.g"
        label(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {
        if ( 
(LA(1)==FILE_WORD) ) {
#line 96 "io.g"
          zzmatch(FILE_WORD);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 96 "io.g"
          zzmatch(EQUAL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 96 "io.g"
          zzNON_GUESS_MODE {
             type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
          } else {
            expression(zzSTR);
          }
        }
        else {
          if ( (LA(1)==STATUS) ) {
#line 97 "io.g"
            zzmatch(STATUS);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 97 "io.g"
            zzmatch(EQUAL);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 97 "io.g"
            zzNON_GUESS_MODE {
               type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
            } else {
              expression(zzSTR);
            }
          }
          else {
            if ( (LA(1)==ACCESS) ) {
#line 98 "io.g"
              zzmatch(ACCESS);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 98 "io.g"
              zzmatch(EQUAL);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 98 "io.g"
              zzNON_GUESS_MODE {
                 type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
              } else {
                expression(zzSTR);
              }
            }
            else {
              if ( (LA(1)==FORM) ) {
#line 99 "io.g"
                zzmatch(FORM);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 99 "io.g"
                zzmatch(EQUAL);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 99 "io.g"
                zzNON_GUESS_MODE {
                   type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
                } else {
                  expression(zzSTR);
                }
              }
              else {
                if ( (LA(1)==RECL) ) {
#line 100 "io.g"
                  zzmatch(RECL);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
#line 100 "io.g"
                  zzmatch(EQUAL);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
#line 100 "io.g"
                  zzNON_GUESS_MODE {
                     type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
                  } else {
                    expression(zzSTR);
                  }
                }
                else {
                  if ( 
(LA(1)==IOSTAT) ) {
#line 101 "io.g"
                    {
                      zzBLOCK(zztasp2);
                      zzMake0;
                      {
#line 101 "io.g"
                        zzmatch(IOSTAT);zzNON_GUESS_MODE {
                           zzsubchild(_root, &_sibling, &_tail);                        }
                         zzCONSUME;
#line 101 "io.g"
                        zzmatch(EQUAL);zzNON_GUESS_MODE {
                           zzsubchild(_root, &_sibling, &_tail);                        }
                         zzCONSUME;
#line 101 "io.g"
                        zzNON_GUESS_MODE {
                           dummy  = operand(zzSTR); zzlink(_root, &_sibling, &_tail);
                        } else {
                          operand(zzSTR);
                        }
                        zzEXIT(zztasp2);
                      }
                    }
                  }
                  else {
                    if ( (LA(1)==TITLE) ) {
#line 102 "io.g"
                      zzmatch(TITLE);zzNON_GUESS_MODE {
                         zzsubchild(_root, &_sibling, &_tail);                      }
                       zzCONSUME;
#line 102 "io.g"
                      zzmatch(EQUAL);zzNON_GUESS_MODE {
                         zzsubchild(_root, &_sibling, &_tail);                      }
                       zzCONSUME;
#line 102 "io.g"
                      zzNON_GUESS_MODE {
                         type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
                      } else {
                        expression(zzSTR);
                      }
                    }
                    else {
                      if ( (LA(1)==DISP) ) {
#line 103 "io.g"
                        zzmatch(DISP);zzNON_GUESS_MODE {
                           zzsubchild(_root, &_sibling, &_tail);                        }
                         zzCONSUME;
#line 103 "io.g"
                        zzmatch(EQUAL);zzNON_GUESS_MODE {
                           zzsubchild(_root, &_sibling, &_tail);                        }
                         zzCONSUME;
#line 103 "io.g"
                        zzNON_GUESS_MODE {
                           type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
                        } else {
                          expression(zzSTR);
                        }
                      }
                      else {
                        if ( (LA(1)==SUBFILE) ) {
#line 104 "io.g"
                          zzmatch(SUBFILE);zzNON_GUESS_MODE {
                             zzsubchild(_root, &_sibling, &_tail);                          }
                           zzCONSUME;
#line 104 "io.g"
                          zzmatch(EQUAL);zzNON_GUESS_MODE {
                             zzsubchild(_root, &_sibling, &_tail);                          }
                           zzCONSUME;
#line 104 "io.g"
                          zzNON_GUESS_MODE {
                             type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
                          } else {
                            expression(zzSTR);
                          }
                        }
                        else {
                          if ( (LA(1)==MAXRECSIZE) ) {
#line 105 "io.g"
                            zzmatch(MAXRECSIZE);zzNON_GUESS_MODE {
                               zzsubchild(_root, &_sibling, &_tail);                            }
                             zzCONSUME;
#line 105 "io.g"
                            zzmatch(EQUAL);zzNON_GUESS_MODE {
                               zzsubchild(_root, &_sibling, &_tail);                            }
                             zzCONSUME;
#line 105 "io.g"
                            zzNON_GUESS_MODE {
                               type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
                            } else {
                              expression(zzSTR);
                            }
                          }
                          else {
                            if ( 
(LA(1)==SAVEFACTOR) ) {
#line 106 "io.g"
                              zzmatch(SAVEFACTOR);zzNON_GUESS_MODE {
                                 zzsubchild(_root, &_sibling, &_tail);                              }
                               zzCONSUME;
#line 106 "io.g"
                              zzmatch(EQUAL);zzNON_GUESS_MODE {
                                 zzsubchild(_root, &_sibling, &_tail);                              }
                               zzCONSUME;
#line 106 "io.g"
                              zzNON_GUESS_MODE {
                                 type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
                              } else {
                                expression(zzSTR);
                              }
                            }
                            else {
                              if ( (LA(1)==OPENTYPE) ) {
#line 107 "io.g"
                                zzmatch(OPENTYPE);zzNON_GUESS_MODE {
                                   zzsubchild(_root, &_sibling, &_tail);                                }
                                 zzCONSUME;
#line 107 "io.g"
                                zzmatch(EQUAL);zzNON_GUESS_MODE {
                                   zzsubchild(_root, &_sibling, &_tail);                                }
                                 zzCONSUME;
#line 107 "io.g"
                                zzNON_GUESS_MODE {
                                   type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
                                } else {
                                  expression(zzSTR);
                                }
                              }
                              else {zzFAIL(1,zzerr221,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd63, 0x1);
  }
}

void
#ifdef __USE_PROTOS
close_statement(AST**_root)
#else
close_statement(_root)
AST **_root;
#endif
{
#line 109 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 109 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 109 "io.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==CLOSE) ) {
          }
          else {zzFAIL(1,zzerr222,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 109 "io.g"
    zzmatch(CLOSE);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 109 "io.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 109 "io.g"
    close_item(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 109 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 109 "io.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 109 "io.g"
          close_item(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
#line 109 "io.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd63, 0x2);
  }
}

void
#ifdef __USE_PROTOS
close_item(AST**_root)
#else
close_item(_root)
AST **_root;
#endif
{
#line 111 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 111 "io.g"
    int type; int dummy;
#line 112 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (setwd63[LA(1)]&0x4) ) {
#line 112 "io.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              if ( (LA(1)==UNIT) ) {
#line 112 "io.g"
                zzmatch(UNIT);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 112 "io.g"
                zzmatch(EQUAL);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
              }
              else {
                if ( (setwd63[LA(1)]&0x8) ) {
                }
                else {zzFAIL(1,zzerr223,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
              }
              zzEXIT(zztasp3);
            }
          }
#line 112 "io.g"
          unit_identifier(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( (LA(1)==ERR) ) {
#line 113 "io.g"
            zzmatch(ERR);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 113 "io.g"
            zzmatch(EQUAL);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 113 "io.g"
            label(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
          }
          else {
            if ( 
(LA(1)==STATUS) ) {
#line 114 "io.g"
              zzmatch(STATUS);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 114 "io.g"
              zzmatch(EQUAL);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 114 "io.g"
              close_name(zzSTR);
              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
              }     /* MR10 */
            }
            else {
              if ( (LA(1)==IOSTAT) ) {
#line 115 "io.g"
                {
                  zzBLOCK(zztasp3);
                  zzMake0;
                  {
#line 115 "io.g"
                    zzmatch(IOSTAT);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
#line 115 "io.g"
                    zzmatch(EQUAL);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
#line 115 "io.g"
                    zzNON_GUESS_MODE {
                       dummy  = operand(zzSTR); zzlink(_root, &_sibling, &_tail);
                    } else {
                      operand(zzSTR);
                    }
                    zzEXIT(zztasp3);
                  }
                }
              }
              else {
                if ( (LA(1)==DISP) ) {
#line 116 "io.g"
                  zzmatch(DISP);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
#line 116 "io.g"
                  zzmatch(EQUAL);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
#line 116 "io.g"
                  close_name(zzSTR);
                  if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                  }     /* MR10 */
                }
                else {
                  if ( (LA(1)==SUBFILE) ) {
#line 117 "io.g"
                    zzmatch(SUBFILE);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
#line 117 "io.g"
                    zzmatch(EQUAL);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
#line 117 "io.g"
                    zzNON_GUESS_MODE {
                       type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
                    } else {
                      expression(zzSTR);
                    }
                  }
                  else {zzFAIL(1,zzerr224,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                }
              }
            }
          }
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
    zzresynch(setwd63, 0x10);
  }
}

void
#ifdef __USE_PROTOS
close_name(AST**_root)
#else
close_name(_root)
AST **_root;
#endif
{
#line 120 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 120 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==IDENTIFIER) ) {
#line 120 "io.g"
          zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( 
(LA(1)==QUOTED_STRING) ) {
#line 120 "io.g"
            zzmatch(QUOTED_STRING);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
          }
          else {zzFAIL(1,zzerr225,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
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
    zzresynch(setwd63, 0x20);
  }
}

void
#ifdef __USE_PROTOS
inquire_statement(AST**_root)
#else
inquire_statement(_root)
AST **_root;
#endif
{
#line 124 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 124 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 124 "io.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==INQUIRE) ) {
          }
          else {zzFAIL(1,zzerr226,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 124 "io.g"
    zzmatch(INQUIRE);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 124 "io.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 124 "io.g"
    inquire_item(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 124 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 124 "io.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 124 "io.g"
          inquire_item(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
#line 124 "io.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd63, 0x40);
  }
}

void
#ifdef __USE_PROTOS
inquire_item(AST**_root)
#else
inquire_item(_root)
AST **_root;
#endif
{
#line 126 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 126 "io.g"
    int type; int dummy;
    if ( (setwd63[LA(1)]&0x80) ) {
#line 127 "io.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
          if ( (setwd64[LA(1)]&0x1) ) {
#line 127 "io.g"
            {
              zzBLOCK(zztasp3);
              zzMake0;
              {
                if ( (LA(1)==UNIT) ) {
#line 127 "io.g"
                  zzmatch(UNIT);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
#line 127 "io.g"
                  zzmatch(EQUAL);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
                }
                else {
                  if ( (setwd64[LA(1)]&0x2) ) {
                  }
                  else {zzFAIL(1,zzerr227,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                }
                zzEXIT(zztasp3);
              }
            }
#line 127 "io.g"
            unit_identifier(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
          }
          else {
            if ( 
(LA(1)==FILE_WORD) ) {
#line 127 "io.g"
              zzmatch(FILE_WORD);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 127 "io.g"
              zzmatch(EQUAL);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 127 "io.g"
              zzNON_GUESS_MODE {
                 type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
              } else {
                expression(zzSTR);
              }
            }
            else {zzFAIL(1,zzerr228,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
          }
          zzEXIT(zztasp2);
        }
      }
    }
    else {
      if ( (LA(1)==ERR) ) {
#line 128 "io.g"
        zzmatch(ERR);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
#line 128 "io.g"
        zzmatch(EQUAL);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
#line 128 "io.g"
        label(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {
        if ( (LA(1)==IOSTAT) ) {
#line 129 "io.g"
          {
            zzBLOCK(zztasp2);
            zzMake0;
            {
#line 129 "io.g"
              zzmatch(IOSTAT);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 129 "io.g"
              zzmatch(EQUAL);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 129 "io.g"
              zzNON_GUESS_MODE {
                 dummy  = operand(zzSTR); zzlink(_root, &_sibling, &_tail);
              } else {
                operand(zzSTR);
              }
              zzEXIT(zztasp2);
            }
          }
        }
        else {
          if ( (LA(1)==NUMBER) ) {
#line 130 "io.g"
            zzmatch(NUMBER);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 130 "io.g"
            zzmatch(EQUAL);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 130 "io.g"
            zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
          }
          else {
            if ( (LA(1)==RECL) ) {
#line 131 "io.g"
              zzmatch(RECL);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 131 "io.g"
              zzmatch(EQUAL);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 131 "io.g"
              zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
            }
            else {
              if ( 
(LA(1)==NEXTREC) ) {
#line 132 "io.g"
                zzmatch(NEXTREC);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 132 "io.g"
                zzmatch(EQUAL);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 132 "io.g"
                zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
              }
              else {
                if ( (LA(1)==EXIST) ) {
#line 133 "io.g"
                  zzmatch(EXIST);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
#line 133 "io.g"
                  zzmatch(EQUAL);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
#line 133 "io.g"
                  zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
                }
                else {
                  if ( (LA(1)==OPENED) ) {
#line 134 "io.g"
                    zzmatch(OPENED);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
#line 134 "io.g"
                    zzmatch(EQUAL);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
#line 134 "io.g"
                    zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
                  }
                  else {
                    if ( (LA(1)==OPEN) ) {
#line 135 "io.g"
                      zzmatch(OPEN);zzNON_GUESS_MODE {
                         zzsubchild(_root, &_sibling, &_tail);                      }
                       zzCONSUME;
#line 135 "io.g"
                      zzmatch(EQUAL);zzNON_GUESS_MODE {
                         zzsubchild(_root, &_sibling, &_tail);                      }
                       zzCONSUME;
#line 135 "io.g"
                      zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
                         zzsubchild(_root, &_sibling, &_tail);                      }
                       zzCONSUME;
                    }
                    else {
                      if ( (LA(1)==NAMED) ) {
#line 136 "io.g"
                        zzmatch(NAMED);zzNON_GUESS_MODE {
                           zzsubchild(_root, &_sibling, &_tail);                        }
                         zzCONSUME;
#line 136 "io.g"
                        zzmatch(EQUAL);zzNON_GUESS_MODE {
                           zzsubchild(_root, &_sibling, &_tail);                        }
                         zzCONSUME;
#line 136 "io.g"
                        zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
                           zzsubchild(_root, &_sibling, &_tail);                        }
                         zzCONSUME;
                      }
                      else {
                        if ( 
(LA(1)==NAME) ) {
#line 137 "io.g"
                          zzmatch(NAME);zzNON_GUESS_MODE {
                             zzsubchild(_root, &_sibling, &_tail);                          }
                           zzCONSUME;
#line 137 "io.g"
                          zzmatch(EQUAL);zzNON_GUESS_MODE {
                             zzsubchild(_root, &_sibling, &_tail);                          }
                           zzCONSUME;
#line 137 "io.g"
                          inquire_name(zzSTR);
                          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                          }     /* MR10 */
                        }
                        else {
                          if ( (LA(1)==RECORD) ) {
#line 138 "io.g"
                            zzmatch(RECORD);zzNON_GUESS_MODE {
                               zzsubchild(_root, &_sibling, &_tail);                            }
                             zzCONSUME;
#line 138 "io.g"
                            zzmatch(EQUAL);zzNON_GUESS_MODE {
                               zzsubchild(_root, &_sibling, &_tail);                            }
                             zzCONSUME;
#line 138 "io.g"
                            inquire_name(zzSTR);
                            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                            }     /* MR10 */
                          }
                          else {
                            if ( (LA(1)==ACCESS) ) {
#line 139 "io.g"
                              zzmatch(ACCESS);zzNON_GUESS_MODE {
                                 zzsubchild(_root, &_sibling, &_tail);                              }
                               zzCONSUME;
#line 139 "io.g"
                              zzmatch(EQUAL);zzNON_GUESS_MODE {
                                 zzsubchild(_root, &_sibling, &_tail);                              }
                               zzCONSUME;
#line 139 "io.g"
                              inquire_name(zzSTR);
                              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                              }     /* MR10 */
                            }
                            else {
                              if ( (LA(1)==SEQUENTIAL) ) {
#line 140 "io.g"
                                zzmatch(SEQUENTIAL);zzNON_GUESS_MODE {
                                   zzsubchild(_root, &_sibling, &_tail);                                }
                                 zzCONSUME;
#line 140 "io.g"
                                zzmatch(EQUAL);zzNON_GUESS_MODE {
                                   zzsubchild(_root, &_sibling, &_tail);                                }
                                 zzCONSUME;
#line 140 "io.g"
                                inquire_name(zzSTR);
                                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                }     /* MR10 */
                              }
                              else {
                                if ( (LA(1)==DIRECT) ) {
#line 141 "io.g"
                                  zzmatch(DIRECT);zzNON_GUESS_MODE {
                                     zzsubchild(_root, &_sibling, &_tail);                                  }
                                   zzCONSUME;
#line 141 "io.g"
                                  zzmatch(EQUAL);zzNON_GUESS_MODE {
                                     zzsubchild(_root, &_sibling, &_tail);                                  }
                                   zzCONSUME;
#line 141 "io.g"
                                  inquire_name(zzSTR);
                                  if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                  }     /* MR10 */
                                }
                                else {
                                  if ( 
(LA(1)==FORM) ) {
#line 142 "io.g"
                                    zzmatch(FORM);zzNON_GUESS_MODE {
                                       zzsubchild(_root, &_sibling, &_tail);                                    }
                                     zzCONSUME;
#line 142 "io.g"
                                    zzmatch(EQUAL);zzNON_GUESS_MODE {
                                       zzsubchild(_root, &_sibling, &_tail);                                    }
                                     zzCONSUME;
#line 142 "io.g"
                                    inquire_name(zzSTR);
                                    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                    }     /* MR10 */
                                  }
                                  else {
                                    if ( (LA(1)==FORMATTED) ) {
#line 143 "io.g"
                                      zzmatch(FORMATTED);zzNON_GUESS_MODE {
                                         zzsubchild(_root, &_sibling, &_tail);                                      }
                                       zzCONSUME;
#line 143 "io.g"
                                      zzmatch(EQUAL);zzNON_GUESS_MODE {
                                         zzsubchild(_root, &_sibling, &_tail);                                      }
                                       zzCONSUME;
#line 143 "io.g"
                                      inquire_name(zzSTR);
                                      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                      }     /* MR10 */
                                    }
                                    else {
                                      if ( (LA(1)==UNFORMATTED) ) {
#line 144 "io.g"
                                        zzmatch(UNFORMATTED);zzNON_GUESS_MODE {
                                           zzsubchild(_root, &_sibling, &_tail);                                        }
                                         zzCONSUME;
#line 144 "io.g"
                                        zzmatch(EQUAL);zzNON_GUESS_MODE {
                                           zzsubchild(_root, &_sibling, &_tail);                                        }
                                         zzCONSUME;
#line 144 "io.g"
                                        inquire_name(zzSTR);
                                        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                        }     /* MR10 */
                                      }
                                      else {
                                        if ( (LA(1)==BLANK) ) {
#line 145 "io.g"
                                          zzmatch(BLANK);zzNON_GUESS_MODE {
                                             zzsubchild(_root, &_sibling, &_tail);                                          }
                                           zzCONSUME;
#line 145 "io.g"
                                          zzmatch(EQUAL);zzNON_GUESS_MODE {
                                             zzsubchild(_root, &_sibling, &_tail);                                          }
                                           zzCONSUME;
#line 145 "io.g"
                                          inquire_name(zzSTR);
                                          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                          }     /* MR10 */
                                        }
                                        else {
                                          if ( (LA(1)==TITLE) ) {
#line 146 "io.g"
                                            zzmatch(TITLE);zzNON_GUESS_MODE {
                                               zzsubchild(_root, &_sibling, &_tail);                                            }
                                             zzCONSUME;
#line 146 "io.g"
                                            zzmatch(EQUAL);zzNON_GUESS_MODE {
                                               zzsubchild(_root, &_sibling, &_tail);                                            }
                                             zzCONSUME;
#line 146 "io.g"
                                            inquire_name(zzSTR);
                                            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                            }     /* MR10 */
                                          }
                                          else {
                                            if ( 
(LA(1)==MAXRECSIZE) ) {
#line 147 "io.g"
                                              zzmatch(MAXRECSIZE);zzNON_GUESS_MODE {
                                                 zzsubchild(_root, &_sibling, &_tail);                                              }
                                               zzCONSUME;
#line 147 "io.g"
                                              zzmatch(EQUAL);zzNON_GUESS_MODE {
                                                 zzsubchild(_root, &_sibling, &_tail);                                              }
                                               zzCONSUME;
#line 147 "io.g"
                                              zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
                                                 zzsubchild(_root, &_sibling, &_tail);                                              }
                                               zzCONSUME;
                                            }
                                            else {
                                              if ( (LA(1)==RESIDENT) ) {
#line 148 "io.g"
                                                zzmatch(RESIDENT);zzNON_GUESS_MODE {
                                                   zzsubchild(_root, &_sibling, &_tail);                                                }
                                                 zzCONSUME;
#line 148 "io.g"
                                                zzmatch(EQUAL);zzNON_GUESS_MODE {
                                                   zzsubchild(_root, &_sibling, &_tail);                                                }
                                                 zzCONSUME;
#line 148 "io.g"
                                                inquire_name(zzSTR);
                                                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                                }     /* MR10 */
                                              }
                                              else {zzFAIL(1,zzerr229,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd64, 0x4);
  }
}

void
#ifdef __USE_PROTOS
inquire_name(AST**_root)
#else
inquire_name(_root)
AST **_root;
#endif
{
#line 151 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 151 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==IDENTIFIER) ) {
#line 151 "io.g"
          zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==QUOTED_STRING) ) {
#line 151 "io.g"
            zzmatch(QUOTED_STRING);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
          }
          else {zzFAIL(1,zzerr230,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
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
    zzresynch(setwd64, 0x8);
  }
}

void
#ifdef __USE_PROTOS
backspace_statement(AST**_root)
#else
backspace_statement(_root)
AST **_root;
#endif
{
#line 154 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 154 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 154 "io.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( 
(LA(1)==BACKSPACE) ) {
          }
          else {zzFAIL(1,zzerr231,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 154 "io.g"
    zzmatch(BACKSPACE);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 154 "io.g"
    io_specifier(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd64, 0x10);
  }
}

void
#ifdef __USE_PROTOS
endfile_statement(AST**_root)
#else
endfile_statement(_root)
AST **_root;
#endif
{
#line 157 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 157 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 157 "io.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==ENDFILE) ) {
          }
          else {zzFAIL(1,zzerr232,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 157 "io.g"
    zzmatch(ENDFILE);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 157 "io.g"
    io_specifier(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd64, 0x20);
  }
}

void
#ifdef __USE_PROTOS
rewind_statement(AST**_root)
#else
rewind_statement(_root)
AST **_root;
#endif
{
#line 160 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 160 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 160 "io.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==REWIND) ) {
          }
          else {zzFAIL(1,zzerr233,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 160 "io.g"
    zzmatch(REWIND);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 160 "io.g"
    io_specifier(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd64, 0x40);
  }
}

void
#ifdef __USE_PROTOS
io_specifier(AST**_root)
#else
io_specifier(_root)
AST **_root;
#endif
{
#line 164 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
#line 164 "io.g"
    int option1=0, option2=0; int type; int dummy;
    zzGUESS
    if ( !zzrv && 
(LA(1)==LP) && (setwd64[LA(2)]&0x80) ) {
#line 165 "io.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 165 "io.g"
          zzmatch(LP);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 165 "io.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 165 "io.g"
          zzmatch(LP);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
          
          zzNON_GUESS_MODE {
#line 165 "io.g"
            zzastArg(1)->token = IO_SPEC_LP;
          }
 zzCONSUME;

          zzEXIT(zztasp2);
        }
      }
#line 165 "io.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
          if ( (LA(1)==UNIT) ) {
#line 165 "io.g"
            zzmatch(UNIT);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 165 "io.g"
            zzmatch(EQUAL);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
          }
          else {
            if ( (setwd65[LA(1)]&0x1) ) {
            }
            else {zzFAIL(1,zzerr234,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
          }
          zzEXIT(zztasp2);
        }
      }
#line 165 "io.g"
      unit_identifier(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
#line 168 "io.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
          for (;;) {
            if ( !((LA(1)==COMMA))) break;
            if ( (LA(1)==COMMA) && (LA(2)==ERR) ) {
              if (!(
#line 166 "io.g"
option1==0)                ) {zzfailed_pred("  option1==0",0 /* report */, { 0; /* no user action */ } );}
#line 166 "io.g"
              zzmatch(COMMA);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 166 "io.g"
              zzmatch(ERR);zzNON_GUESS_MODE {
                 zzsubroot(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 166 "io.g"
              zzmatch(EQUAL);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 166 "io.g"
              zzmatch(INT_CONST);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
              
              zzNON_GUESS_MODE {
#line 166 "io.g"
                option1=1;
              }
 zzCONSUME;

            }
            else {
              if ( (LA(1)==COMMA) && (LA(2)==IOSTAT) ) {
                if (!(
#line 167 "io.g"
option2==0)                  ) {zzfailed_pred("  option2==0",0 /* report */, { 0; /* no user action */ } );}
#line 167 "io.g"
                zzmatch(COMMA);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 167 "io.g"
                zzmatch(IOSTAT);zzNON_GUESS_MODE {
                   zzsubroot(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 167 "io.g"
                zzmatch(EQUAL);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 167 "io.g"
                zzNON_GUESS_MODE {
                   dummy  = operand(zzSTR); zzlink(_root, &_sibling, &_tail);
                } else {
                  operand(zzSTR);
                }
              }
              else break; /* MR6 code for exiting loop "for sure" */
            }
            zzLOOP(zztasp2);
          }
          zzEXIT(zztasp2);
        }
      }
#line 169 "io.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 169 "io.g"
          zzmatch(RP);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
          
          zzNON_GUESS_MODE {
#line 169 "io.g"
            zzastArg(1)->token = IO_SPEC_RP;
          }
 zzCONSUME;

          zzEXIT(zztasp2);
        }
      }
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (setwd65[LA(1)]&0x2) && (setwd65[LA(2)]&0x4) ) {
#line 170 "io.g"
        unit_identifier(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {zzFAIL(2,zzerr235,zzerr236,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd65, 0x8);
  }
}

void
#ifdef __USE_PROTOS
change_statement(AST**_root)
#else
change_statement(_root)
AST **_root;
#endif
{
#line 173 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 173 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 173 "io.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( 
(LA(1)==CHANGE) ) {
          }
          else {zzFAIL(1,zzerr237,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 173 "io.g"
    zzmatch(CHANGE);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 173 "io.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 174 "io.g"
    change_item(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 174 "io.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 174 "io.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 174 "io.g"
          change_item(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
#line 174 "io.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd65, 0x10);
  }
}

void
#ifdef __USE_PROTOS
change_item(AST**_root)
#else
change_item(_root)
AST **_root;
#endif
{
#line 176 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (setwd65[LA(1)]&0x20) && (LA(2)==COMMA) ) {
#line 176 "io.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 176 "io.g"
          library_id(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 176 "io.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 176 "io.g"
          library_clist(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 176 "io.g"
      library_id(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
#line 176 "io.g"
      zzmatch(COMMA);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 176 "io.g"
      library_clist(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (setwd65[LA(1)]&0x40) ) {
#line 177 "io.g"
        change_file_specifier(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {
        if ( !zzrv ) zzGUESS_DONE;
        if ( (setwd65[LA(1)]&0x80) ) {
#line 178 "io.g"
          file_clist(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( !zzrv ) zzGUESS_DONE;
          if ( (setwd66[LA(1)]&0x1) && 
(setwd66[LA(2)]&0x2) ) {
#line 179 "io.g"
            {
              zzBLOCK(zztasp2);
              zzMake0;
              {
                if ( (LA(1)==UNIT) ) {
#line 179 "io.g"
                  zzmatch(UNIT);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
#line 179 "io.g"
                  zzmatch(EQUAL);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
                }
                else {
                  if ( (setwd66[LA(1)]&0x4) ) {
                  }
                  else {zzFAIL(1,zzerr238,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                }
                zzEXIT(zztasp2);
              }
            }
#line 179 "io.g"
            unit_identifier(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
          }
          else {zzFAIL(2,zzerr239,zzerr240,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd66, 0x8);
  }
}

void
#ifdef __USE_PROTOS
file_clist(AST**_root)
#else
file_clist(_root)
AST **_root;
#endif
{
#line 181 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 181 "io.g"
    int type; int dummy;
    if ( (LA(1)==IOSTAT) ) {
#line 182 "io.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 182 "io.g"
          zzmatch(IOSTAT);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 182 "io.g"
          zzmatch(EQUAL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 182 "io.g"
          zzNON_GUESS_MODE {
             dummy  = operand(zzSTR); zzlink(_root, &_sibling, &_tail);
          } else {
            operand(zzSTR);
          }
          zzEXIT(zztasp2);
        }
      }
    }
    else {
      if ( (LA(1)==ERR) ) {
#line 183 "io.g"
        zzmatch(ERR);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
#line 183 "io.g"
        zzmatch(EQUAL);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
#line 183 "io.g"
        statement_label(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {
        if ( (LA(1)==FILE_WORD) ) {
#line 184 "io.g"
          zzmatch(FILE_WORD);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 184 "io.g"
          zzmatch(EQUAL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 184 "io.g"
          zzNON_GUESS_MODE {
             type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
          } else {
            expression(zzSTR);
          }
        }
        else {
          if ( 
(LA(1)==STATUS) ) {
#line 185 "io.g"
            zzmatch(STATUS);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 185 "io.g"
            zzmatch(EQUAL);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 185 "io.g"
            zzNON_GUESS_MODE {
               type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
            } else {
              expression(zzSTR);
            }
          }
          else {
            if ( (LA(1)==BLANK) ) {
#line 186 "io.g"
              zzmatch(BLANK);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 186 "io.g"
              zzmatch(EQUAL);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 186 "io.g"
              zzNON_GUESS_MODE {
                 type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
              } else {
                expression(zzSTR);
              }
            }
            else {zzFAIL(1,zzerr241,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
          }
        }
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd66, 0x10);
  }
}

void
#ifdef __USE_PROTOS
library_id(AST**_root)
#else
library_id(_root)
AST **_root;
#endif
{
#line 189 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    if ( (LA(1)==IDENTIFIER) ) {
#line 189 "io.g"
      zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
    }
    else {
      if ( (LA(1)==CONSTINT) ) {
#line 189 "io.g"
        zzmatch(CONSTINT);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
      }
      else {zzFAIL(1,zzerr242,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd66, 0x20);
  }
}

void
#ifdef __USE_PROTOS
library_clist(AST**_root)
#else
library_clist(_root)
AST **_root;
#endif
{
#line 190 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 190 "io.g"
    int type;
    if ( (LA(1)==TITLE) ) {
#line 191 "io.g"
      zzmatch(TITLE);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 191 "io.g"
      zzmatch(EQUAL);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 191 "io.g"
      zzNON_GUESS_MODE {
         type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
      } else {
        expression(zzSTR);
      }
    }
    else {
      if ( 
(LA(1)==LIBPARAMETER) ) {
#line 192 "io.g"
        zzmatch(LIBPARAMETER);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
#line 192 "io.g"
        zzmatch(EQUAL);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
#line 192 "io.g"
        zzNON_GUESS_MODE {
           type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
        } else {
          expression(zzSTR);
        }
      }
      else {
        if ( (LA(1)==FUNCTIONNAME) ) {
#line 193 "io.g"
          zzmatch(FUNCTIONNAME);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 193 "io.g"
          zzmatch(EQUAL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 193 "io.g"
          zzNON_GUESS_MODE {
             type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
          } else {
            expression(zzSTR);
          }
        }
        else {zzFAIL(1,zzerr243,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd66, 0x40);
  }
}

void
#ifdef __USE_PROTOS
change_file_specifier(AST**_root)
#else
change_file_specifier(_root)
AST **_root;
#endif
{
#line 196 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 196 "io.g"
    int type;
    if ( (LA(1)==KIND) ) {
#line 197 "io.g"
      zzmatch(KIND);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 197 "io.g"
      zzmatch(EQUAL);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 197 "io.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
          if ( (LA(1)==QUATED_STRING) ) {
#line 197 "io.g"
            zzmatch(QUATED_STRING);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
          }
          else {
            if ( (LA(1)==IDENTIFIER) ) {
#line 197 "io.g"
              zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 197 "io.g"
              {
                zzBLOCK(zztasp3);
                zzMake0;
                {
                  if ( 
(LA(1)==LP) ) {
#line 197 "io.g"
                    zzmatch(LP);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
#line 197 "io.g"
                    zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
#line 197 "io.g"
                    zzmatch(RP);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
                  }
                  else {
                    if ( (setwd66[LA(1)]&0x80) ) {
                    }
                    else {zzFAIL(1,zzerr244,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                  }
                  zzEXIT(zztasp3);
                }
              }
            }
            else {zzFAIL(1,zzerr245,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
          }
          zzEXIT(zztasp2);
        }
      }
    }
    else {
      if ( (LA(1)==MAXRECSIZE) ) {
#line 198 "io.g"
        zzmatch(MAXRECSIZE);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
#line 198 "io.g"
        zzmatch(EQUAL);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
#line 198 "io.g"
        zzNON_GUESS_MODE {
           type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
        } else {
          expression(zzSTR);
        }
      }
      else {zzFAIL(1,zzerr246,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd67, 0x1);
  }
}

void
#ifdef __USE_PROTOS
format_statement(AST**_root)
#else
format_statement(_root)
AST **_root;
#endif
{
#line 201 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 201 "io.g"
    zzmatch(LABEL);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 201 "io.g"
    zzmatch(FORMAT);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 201 "io.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 201 "io.g"
    format_specification(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 201 "io.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd67, 0x2);
  }
}

void
#ifdef __USE_PROTOS
format_specification(AST**_root)
#else
format_specification(_root)
AST **_root;
#endif
{
#line 203 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 203 "io.g"
    {
      zzBLOCK(zztasp2);
      int zzcnt=1;
      zzMake0;
      {
        do {
#line 203 "io.g"
          format_specifier(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        } while ( (setwd67[LA(1)]&0x4) );
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd67, 0x8);
  }
}

void
#ifdef __USE_PROTOS
format_specifier(AST**_root)
#else
format_specifier(_root)
AST **_root;
#endif
{
#line 205 "io.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (setwd67[LA(1)]&0x10) && (setwd67[LA(2)]&0x20) ) {
#line 205 "io.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 205 "io.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              if ( (LA(1)==CONSTINT) ) {
#line 205 "io.g"
                zzmatch(CONSTINT);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
              }
              else {
                if ( (LA(1)==LP) ) {
                }
                else {zzFAIL(1,zzerr247,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
              }
              zzEXIT(zztasp3);
            }
          }
#line 205 "io.g"
          zzmatch(LP);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 205 "io.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
          if ( (LA(1)==CONSTINT) ) {
#line 205 "io.g"
            zzmatch(CONSTINT);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
          }
          else {
            if ( 
(LA(1)==LP) ) {
            }
            else {zzFAIL(1,zzerr248,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
          }
          zzEXIT(zztasp2);
        }
      }
#line 205 "io.g"
      zzmatch(LP);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 205 "io.g"
      format_specification(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
#line 205 "io.g"
      zzmatch(RP);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (LA(1)==HOLLERITH_CONST) ) {
#line 206 "io.g"
        hollerith_editing(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {
        if ( !zzrv ) zzGUESS_DONE;
        if ( (LA(1)==QUOTED_STRING) ) {
#line 207 "io.g"
          quote_editinig(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( !zzrv ) zzGUESS_DONE;
          if ( (LA(1)==TR) ) {
#line 207 "io.g"
            tr_editing(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
          }
          else {
            if ( !zzrv ) zzGUESS_DONE;
            if ( (LA(1)==TL) ) {
#line 208 "io.g"
              tl_editing(zzSTR);
              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
              }     /* MR10 */
            }
            else {
              if ( !zzrv ) zzGUESS_DONE;
              if ( 
(LA(1)==T) ) {
#line 208 "io.g"
                t_editing(zzSTR);
                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                }     /* MR10 */
              }
              else {
                if ( !zzrv ) zzGUESS_DONE;
                if ( (setwd67[LA(1)]&0x40) && (setwd67[LA(2)]&0x80) && !(
 LA(1)==CONSTINT
   && ( LA(2)==P || LA(2)==I || LA(2)==F || LA(2)==E
      || LA(2)==D || LA(2)==G || LA(2)==L || LA(2)==A)
) ) {
#line 209 "io.g"
                  x_editing(zzSTR);
                  if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                  }     /* MR10 */
                }
                else {
                  if ( !zzrv ) zzGUESS_DONE;
                  if ( (LA(1)==COLUMN) ) {
#line 209 "io.g"
                    colon_editing(zzSTR);
                    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                    }     /* MR10 */
                  }
                  else {
                    if ( !zzrv ) zzGUESS_DONE;
                    if ( (LA(1)==SS) ) {
#line 210 "io.g"
                      ss_editing(zzSTR);
                      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                      }     /* MR10 */
                    }
                    else {
                      if ( !zzrv ) zzGUESS_DONE;
                      if ( (LA(1)==S) ) {
#line 210 "io.g"
                        s_editing(zzSTR);
                        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                        }     /* MR10 */
                      }
                      else {
                        if ( !zzrv ) zzGUESS_DONE;
                        if ( 
(setwd68[LA(1)]&0x1) && (setwd68[LA(2)]&0x2) && !(
 LA(1)==CONSTINT
   && ( LA(2)==I || LA(2)==F || LA(2)==E || LA(2)==D
      || LA(2)==G || LA(2)==L || LA(2)==A)
) ) {
#line 211 "io.g"
                          p_editing(zzSTR);
                          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                          }     /* MR10 */
                        }
                        else {
                          if ( !zzrv ) zzGUESS_DONE;
                          if ( (LA(1)==BN) ) {
#line 211 "io.g"
                            bn_editing(zzSTR);
                            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                            }     /* MR10 */
                          }
                          else {
                            if ( !zzrv ) zzGUESS_DONE;
                            if ( (LA(1)==BZ) ) {
#line 212 "io.g"
                              bz_editing(zzSTR);
                              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                              }     /* MR10 */
                            }
                            else {
                              if ( !zzrv ) zzGUESS_DONE;
                              if ( (setwd68[LA(1)]&0x4) && (setwd68[LA(2)]&0x8) ) {
#line 212 "io.g"
                                i_editing(zzSTR);
                                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                }     /* MR10 */
                              }
                              else {
                                if ( !zzrv ) zzGUESS_DONE;
                                if ( (LA(1)==J) ) {
#line 213 "io.g"
                                  j_editing(zzSTR);
                                  if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                  }     /* MR10 */
                                }
                                else {
                                  if ( !zzrv ) zzGUESS_DONE;
                                  if ( 
(setwd68[LA(1)]&0x10) && (setwd68[LA(2)]&0x20) ) {
#line 213 "io.g"
                                    f_editing(zzSTR);
                                    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                    }     /* MR10 */
                                  }
                                  else {
                                    if ( !zzrv ) zzGUESS_DONE;
                                    if ( (setwd68[LA(1)]&0x40) && (setwd68[LA(2)]&0x80) ) {
#line 214 "io.g"
                                      e_editing(zzSTR);
                                      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                      }     /* MR10 */
                                    }
                                    else {
                                      if ( !zzrv ) zzGUESS_DONE;
                                      if ( (setwd69[LA(1)]&0x1) && (setwd69[LA(2)]&0x2) ) {
#line 214 "io.g"
                                        d_editing(zzSTR);
                                        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                        }     /* MR10 */
                                      }
                                      else {
                                        if ( !zzrv ) zzGUESS_DONE;
                                        if ( (setwd69[LA(1)]&0x4) && (setwd69[LA(2)]&0x8) ) {
#line 215 "io.g"
                                          g_editing(zzSTR);
                                          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                          }     /* MR10 */
                                        }
                                        else {
                                          if ( !zzrv ) zzGUESS_DONE;
                                          if ( (LA(1)==O) ) {
#line 215 "io.g"
                                            o_editing(zzSTR);
                                            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                            }     /* MR10 */
                                          }
                                          else {
                                            if ( !zzrv ) zzGUESS_DONE;
                                            if ( 
(setwd69[LA(1)]&0x10) && (setwd69[LA(2)]&0x20) ) {
#line 216 "io.g"
                                              l_editing(zzSTR);
                                              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                              }     /* MR10 */
                                            }
                                            else {
                                              if ( !zzrv ) zzGUESS_DONE;
                                              if ( (setwd69[LA(1)]&0x40) && (setwd69[LA(2)]&0x80) ) {
#line 216 "io.g"
                                                a_editing(zzSTR);
                                                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                                }     /* MR10 */
                                              }
                                              else {
                                                if ( !zzrv ) zzGUESS_DONE;
                                                if ( (LA(1)==Z) ) {
#line 217 "io.g"
                                                  z_editing(zzSTR);
                                                  if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                                  }     /* MR10 */
                                                }
                                                else {
                                                  if ( !zzrv ) zzGUESS_DONE;
                                                  if ( (LA(1)==SP) ) {
#line 217 "io.g"
                                                    sp_editing(zzSTR);
                                                    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                                    }     /* MR10 */
                                                  }
                                                  else {
                                                    if ( !zzrv ) zzGUESS_DONE;
                                                    if ( (LA(1)==SLASH) ) {
#line 218 "io.g"
                                                      zzmatch(SLASH);zzNON_GUESS_MODE {
                                                         zzsubchild(_root, &_sibling, &_tail);                                                      }
                                                       zzCONSUME;
                                                    }
                                                    else {
                                                      if ( !zzrv ) zzGUESS_DONE;
                                                      if ( 
(LA(1)==U) ) {
#line 220 "io.g"
                                                        u_editing(zzSTR);
                                                        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                                        }     /* MR10 */
                                                      }
                                                      else {zzFAIL(2,zzerr249,zzerr250,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                                                    }
                                                  }
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd70, 0x1);
  }
}
