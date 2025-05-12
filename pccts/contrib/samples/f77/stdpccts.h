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
 *   ..\..\..\bin\antlr.exe -emsvc -k 2 -glms -gh -ga -gt f77.g expr.g decl.g io.g
 *
 */

#ifndef ANTLR_VERSION
#define ANTLR_VERSION	13333
#endif

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
#define zzSET_SIZE 36
#define zzTOKEN_COUNT 260
#include "antlr.h"
#include "ast.h"
#include "tokens.h"
#include "dlgdef.h"
#include "mode.h"
#endif
