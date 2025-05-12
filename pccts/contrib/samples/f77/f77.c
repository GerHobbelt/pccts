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

#include "ast.c"
zzASTgvars

ANTLR_INFO
#line 110 "f77.g"

#include <ctype.h>	/*isprint()*/
int LineColumn = 0;
int LPCount = 0;
int ReadWriteControlFlag = FALSE;
int ExpectingIOKeyword = FALSE;
int CommaCount = 0;
int keyword_context;
int LineCount = 1;
int StatementCount = 1;
int CurrentStatement = INVALID;
AST *F77InpRoot = NULL;
AST *F77OutRoot = NULL;
extern void F77TreePrinter(AST *root);
extern AST *F77TreeTranslator(AST *InpRoot, AST *OutRoot);

void OutStatement(AST *stmnt) {
  printf("Statement.\n");
  printf("%s ", stmnt->f77NodeText);
  stmnt = stmnt->down;
  while(stmnt != NULL) {
    printf("%s ", stmnt->f77NodeText);
    stmnt = stmnt->right;
  }
}

void OutSource(AST *p) {
  AST *TempPtr = p;
  printf("Now printing the output.\n");
  while(TempPtr != NULL) {
    OutStatement(TempPtr);
    TempPtr = TempPtr->right;
  }
}

#define F77_BUFFER_SIZE 100
#define F77_LINE_SIZE 72
int main(int argc, char *argv[])
{
  FILE *fp, *tempfile;

  char buffer[F77_BUFFER_SIZE], *p;
  int i, LineLength, LastCharAlphaNum = FALSE;
  if(argc != 2) {
    printf("Usage: %s filename.\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  if((fp = fopen(argv[1], "r+")) == NULL) {
    printf("Cannot open %s.\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  if((tempfile = tmpfile()) == NULL) {
    printf("Cannot create a temporary file.\n");
    exit(EXIT_FAILURE);
  }
  while(fgets(&buffer[0], F77_BUFFER_SIZE, fp) != NULL) {
    if((LineLength = strlen(buffer)) < F77_LINE_SIZE) {
      printf("A line shorter than %d.\nImpossible in a healthy FORTRAN 77 source file!\n", F77_LINE_SIZE);
      exit(EXIT_FAILURE);
    }
    for(i=0; i < F77_LINE_SIZE; i++) {	/*Clear non printable and non-ASCII*/
      if(!isprint(buffer[i]))
      buffer[i] = ' ';
    }
    p = &buffer[0];
    if(LastCharAlphaNum) {
      /*I have to resolve the '\n' for the previous line first.*/
      while(*p == ' ') p++; /*Find first non-space*/
      if((p == &buffer[5]) && (*p != '0')) {/*... is on column 6 and is not '0'*/
        /*We have a continuation line*/
        p++;
        while(isalnum(*p)) { /*append all alphanumerics to the previous line*/
          putc(*p, tempfile);
          *p = ' ';	/*Replace moved chars with ' ' */
          p++;
        }
      }
      else {/*It is not continuation line behave normally.*/
        p = &buffer[0];
      }
      putc('\n', tempfile);
    }
    /*The '\n' in input line is to be copied to the output line.*/
    if(buffer[LineLength-1] == '\n') {
      LastCharAlphaNum = (isalnum(buffer[F77_LINE_SIZE-1]))? TRUE : FALSE;
      if(!LastCharAlphaNum) {
        buffer[F77_LINE_SIZE] = '\n';
        buffer[F77_LINE_SIZE+1] = '\0';
      }
      else {
        buffer[F77_LINE_SIZE] = '\0';
        /*Otherwise we have to wait till the next line.*/
      }
    }
    else {/*The last line...*/
      buffer[F77_LINE_SIZE] = '\0';
    }
    if(p > &buffer[6]) {
      memmove(&buffer[6], p, strlen(p)+1);
    }
    fputs(buffer, tempfile);
  }
  fclose(fp);
  rewind(tempfile);
  zzmode(NEWLINE);
  ANTLR(program(&F77InpRoot), tempfile);
  F77OutRoot = F77TreeTranslator(F77InpRoot, F77OutRoot);
  F77TreePrinter(F77OutRoot);
  printf("Lines processed %d.\n", LineCount);
  return(0);
}
#line 223 "f77.g"

void GetTrailingComment(void) {
  char *TextPtr, *TempPtr;
  TextPtr = TempPtr = (char *)malloc(100+sizeof('\0'));
  while(zzbegcol <= 72) {
    zzadvance();
    *TempPtr++ = zzchar;
  }
  zzadvance();
  *TempPtr = '\0';
  zzreplstr(TextPtr);
  free(TextPtr);
}

void GetQuotedString(void) {
  char *TextPtr, *TempPtr;
  TextPtr = TempPtr = (char *)malloc(100+sizeof('\0'));
  while(1) {
    zzadvance();
    if(zzchar == '\n') {
      NewLineProcessing();
      zzadvance(); /*skip '\n'*/
      zzadvance(); /*skip ''*/
      zzadvance(); /*skip ''*/
      zzadvance(); /*skip ''*/
      zzadvance(); /*skip ''*/
      zzadvance(); /*skip ''*/
      zzadvance(); /*skip ''*/
    }
    if(zzchar == *zzbegexpr) {
      zzadvance();
      zzendcol--;	/*This time compensate the zzendcol increment.*/
      if(zzchar != *zzbegexpr)
      break;
    }
    *TempPtr++ = zzchar;
  }
  *TempPtr = '\0';
  zzreplstr(TextPtr);
  free(TextPtr);
}

void ProcessHollerith(void) {
  char *TextPtr, *TempPtr;
  int HollerithLength;
  *zzendexpr = ' ';
  HollerithLength = atoi(zzbegexpr);
  TextPtr = TempPtr = (char *)malloc(HollerithLength+sizeof('\0'));
  while(HollerithLength--) {
    zzadvance();
    if(zzchar == '\n') {
      NewLineProcessing();
      zzadvance(); /*skip '\n'*/
      zzadvance(); /*skip ''*/
      zzadvance(); /*skip ''*/
      zzadvance(); /*skip ''*/
      zzadvance(); /*skip ''*/
      zzadvance(); /*skip ''*/
      zzadvance(); /*skip ''*/
    }
    *TempPtr++ = zzchar;
  }
  zzadvance();
  *TempPtr = '\0';
  zzreplstr(TextPtr);
  free(TextPtr);
}

void NewLineProcessing(void) {
  /*
  if(!(zzline % 100))
  printf("%d.\n", zzline);
  */
  zzline++;
  LineCount++;
  LineColumn = zzendcol;
}

void ReadWriteProcessing(void) {
  zzmode(START);
  keyword_context = NLA;
  LPCount = 0;
  ReadWriteControlFlag = TRUE;
  CommaCount = 0;
}

void IOStatement(void) {
  switch(keyword_context) {
    case FILEKEYWORD:
    case OPEN:
    case CLOSE:
    case CHANGE:
    case INQUIRE:
    case LIBRARY:
    break;
    case READ:
    case WRITE:
    if((ReadWriteControlFlag == TRUE) && (ExpectingIOKeyword == TRUE)) {
      ExpectingIOKeyword = FALSE;
    }
    else {
      NLA = IDENTIFIER;
    }
    break;
    default:
    NLA = IDENTIFIER;
    break;
  }
}

void
#ifdef __USE_PROTOS
program(AST**_root)
#else
program(_root)
AST **_root;
#endif
{
#line 876 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 877 "f77.g"

    AddSymbol("TIME", FUNCTION_NAME);	/*Intrisic TIME.*/
    AddSymbol("FLOAT", FUNCTION_NAME);	/*Intrisic FLOAT.*/
    AddSymbol("EXIT", FUNCTION_NAME);	/*Intrisic EXIT.*/
    AddSymbol("IABS", FUNCTION_NAME);	/*Intrisic IABS.*/
    AddSymbol("SIGN", FUNCTION_NAME);	/*Intrisic SIGN.*/
    AddSymbol("SQRT", FUNCTION_NAME);
    AddSymbol("AMAX1", FUNCTION_NAME);
    AddSymbol("AMAX0", FUNCTION_NAME);
    AddSymbol("AMIN1", FUNCTION_NAME);
    AddSymbol("AMIN0", FUNCTION_NAME);
    AddSymbol("ABS", FUNCTION_NAME);
    AddSymbol("ALOG", FUNCTION_NAME);
    AddSymbol("DEXP", FUNCTION_NAME);
    AddSymbol("DBLE", FUNCTION_NAME);
    AddSymbol("FREEZE", FUNCTION_NAME);	/*Intrisic subroutine*/
#line 894 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (setwd1[LA(1)]&0x1) ) {
#line 894 "f77.g"
          source_line(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
    zzNON_GUESS_MODE {
#line 895 "f77.g"

      /*OutSource(F77root);*/
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd1, 0x2);
  }
}

void
#ifdef __USE_PROTOS
source_line(AST**_root)
#else
source_line(_root)
AST **_root;
#endif
{
#line 899 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    if ( (LA(1)==COMMENT_LINE) ) {
#line 900 "f77.g"
      comment_line(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( (LA(1)==BLANK_LINE) ) {
#line 901 "f77.g"
        blank_line(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {
        if ( (LA(1)==CONTROL_IMAGE) ) {
#line 902 "f77.g"
          control_image(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( (setwd1[LA(1)]&0x4) ) {
#line 903 "f77.g"
            statement(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
            zzNON_GUESS_MODE {
#line 904 "f77.g"

              StatementCount++;
              printf("Processed %f. Line %d\n", 100*((float)zzline/LineCount), zzline);
            }
          }
          else {zzFAIL(1,zzerr1,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd1, 0x8);
  }
}

void
#ifdef __USE_PROTOS
comment_line(AST**_root)
#else
comment_line(_root)
AST **_root;
#endif
{
#line 910 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 910 "f77.g"
    zzmatch(COMMENT_LINE);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd1, 0x10);
  }
}

void
#ifdef __USE_PROTOS
blank_line(AST**_root)
#else
blank_line(_root)
AST **_root;
#endif
{
#line 913 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 913 "f77.g"
    zzmatch(BLANK_LINE);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd1, 0x20);
  }
}

void
#ifdef __USE_PROTOS
control_image(AST**_root)
#else
control_image(_root)
AST **_root;
#endif
{
#line 916 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 916 "f77.g"
    zzmatch(CONTROL_IMAGE);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 916 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (setwd1[LA(1)]&0x40) ) {
#line 916 "f77.g"
          option_phrase(zzSTR);
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
    zzresynch(setwd1, 0x80);
  }
}

void
#ifdef __USE_PROTOS
option_phrase(AST**_root)
#else
option_phrase(_root)
AST **_root;
#endif
{
#line 919 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    if ( (LA(1)==SET) ) {
#line 919 "f77.g"
      set_phrase(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( (LA(1)==POP) ) {
#line 920 "f77.g"
        pop_phrase(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {
        if ( (LA(1)==RESET) ) {
#line 921 "f77.g"
          reset_phrase(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( (LA(1)==INCLUDE) ) {
#line 922 "f77.g"
            include_phrase(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
          }
          else {
            if ( 
(setwd2[LA(1)]&0x1) ) {
#line 923 "f77.g"
              option(zzSTR);
              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
              }     /* MR10 */
            }
            else {zzFAIL(1,zzerr2,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
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
    zzresynch(setwd2, 0x2);
  }
}

void
#ifdef __USE_PROTOS
set_phrase(AST**_root)
#else
set_phrase(_root)
AST **_root;
#endif
{
#line 926 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 926 "f77.g"
    zzmatch(SET);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 927 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        zzGUESS_BLOCK
        zzGUESS
        if ( !zzrv && (setwd2[LA(1)]&0x4) && (setwd2[LA(2)]&0x8) ) {
#line 927 "f77.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
#line 927 "f77.g"
              option(zzSTR);
              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
              }     /* MR10 */
#line 927 "f77.g"
              zzmatch(EQUAL);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
              zzEXIT(zztasp3);
            }
          }
          zzGUESS_DONE
#line 927 "f77.g"
          option(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 927 "f77.g"
          zzmatch(EQUAL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 927 "f77.g"
          option(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( !zzrv ) zzGUESS_DONE;
          if ( (setwd2[LA(1)]&0x10) && (setwd2[LA(2)]&0x20) ) {
#line 928 "f77.g"
            option(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
          }
          else {zzFAIL(2,zzerr3,zzerr4,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
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
    zzresynch(setwd2, 0x40);
  }
}

void
#ifdef __USE_PROTOS
pop_phrase(AST**_root)
#else
pop_phrase(_root)
AST **_root;
#endif
{
#line 931 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 931 "f77.g"
    zzmatch(POP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 931 "f77.g"
    option(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd2, 0x80);
  }
}

void
#ifdef __USE_PROTOS
reset_phrase(AST**_root)
#else
reset_phrase(_root)
AST **_root;
#endif
{
#line 933 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 933 "f77.g"
    zzmatch(RESET);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 933 "f77.g"
    option(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd3, 0x1);
  }
}

void
#ifdef __USE_PROTOS
include_phrase(AST**_root)
#else
include_phrase(_root)
AST **_root;
#endif
{
#line 935 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 935 "f77.g"
    zzmatch(INCLUDE);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 935 "f77.g"
    char_const(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd3, 0x2);
  }
}

void
#ifdef __USE_PROTOS
option(AST**_root)
#else
option(_root)
AST **_root;
#endif
{
#line 937 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 937 "f77.g"
    int dummy;
    if ( (LA(1)==CHARS) ) {
#line 938 "f77.g"
      zzmatch(CHARS);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
    }
    else {
      if ( (LA(1)==STACK) ) {
#line 939 "f77.g"
        zzmatch(STACK);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
      }
      else {
        if ( 
(LA(1)==PAGE) ) {
#line 940 "f77.g"
          zzmatch(PAGE);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==FREE) ) {
#line 941 "f77.g"
            zzmatch(FREE);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
          }
          else {
            if ( (LA(1)==OWN) ) {
#line 942 "f77.g"
              zzmatch(OWN);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
            }
            else {
              if ( (LA(1)==NEW) ) {
#line 943 "f77.g"
                zzmatch(NEW);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
              }
              else {
                if ( (LA(1)==LIST) ) {
#line 944 "f77.g"
                  zzmatch(LIST);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
                }
                else {
                  if ( 
(LA(1)==XREF) ) {
#line 945 "f77.g"
                    zzmatch(XREF);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
                  }
                  else {
                    if ( (LA(1)==ERRLIST) ) {
#line 946 "f77.g"
                      zzmatch(ERRLIST);zzNON_GUESS_MODE {
                         zzsubchild(_root, &_sibling, &_tail);                      }
                       zzCONSUME;
                    }
                    else {
                      if ( (LA(1)==LINEINFO) ) {
#line 947 "f77.g"
                        zzmatch(LINEINFO);zzNON_GUESS_MODE {
                           zzsubchild(_root, &_sibling, &_tail);                        }
                         zzCONSUME;
                      }
                      else {
                        if ( (setwd3[LA(1)]&0x4) ) {
#line 948 "f77.g"
                          zzNON_GUESS_MODE {
                             dummy  = constant(zzSTR); zzlink(_root, &_sibling, &_tail);
                          } else {
                            constant(zzSTR);
                          }
                        }
                        else {
                          if ( (LA(1)==NOT) ) {
#line 949 "f77.g"
                            zzmatch(NOT);zzNON_GUESS_MODE {
                               zzsubchild(_root, &_sibling, &_tail);                            }
                             zzCONSUME;
#line 949 "f77.g"
                            option(zzSTR);
                            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                            }     /* MR10 */
                          }
                          else {zzFAIL(1,zzerr5,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
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
    zzresynch(setwd3, 0x8);
  }
}

void
#ifdef __USE_PROTOS
statement(AST**_root)
#else
statement(_root)
AST **_root;
#endif
{
#line 952 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    if ( 
(setwd3[LA(1)]&0x10) && (setwd3[LA(2)]&0x20) && !(
 LA(1)==LABEL
   && ( LA(2)==RETURN || LA(2)==READ || LA(2)==WRITE || LA(2)==INQUIRE
      || LA(2)==BACKSPACE || LA(2)==ENDFILE || LA(2)==REWIND || LA(2)==BLOCK_GLOBALS
      || LA(2)==EXPORT || LA(2)==CHANGE || LA(2)==OPEN || LA(2)==CLOSE
      || LA(2)==DIMENSION || LA(2)==EQUIVALENCE || LA(2)==IMPLICIT || LA(2)==SAVE
      || LA(2)==PARAMETER || LA(2)==ASSIGN || LA(2)==FIND)
) ) {
#line 952 "f77.g"
      statement1(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( (setwd3[LA(1)]&0x40) && (setwd3[LA(2)]&0x80) ) {
#line 953 "f77.g"
        statement2(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {zzFAIL(2,zzerr6,zzerr7,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd4, 0x1);
  }
}

void
#ifdef __USE_PROTOS
statement1(AST**_root)
#else
statement1(_root)
AST **_root;
#endif
{
#line 956 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    if ( (LA(1)==FILEKEYWORD) ) {
#line 957 "f77.g"
      file_statement(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      zzGUESS
      if ( !zzrv && (setwd4[LA(1)]&0x2) && (setwd4[LA(2)]&0x4) ) {
#line 958 "f77.g"
        {
          zzBLOCK(zztasp2);
          zzMake0;
          {
#line 958 "f77.g"
            function_statement(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
            zzEXIT(zztasp2);
          }
        }
        zzGUESS_DONE
#line 958 "f77.g"
        function_statement(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {
        if ( !zzrv ) zzGUESS_DONE;
        if ( (setwd4[LA(1)]&0x8) && 
(setwd4[LA(2)]&0x10) && !( LA(1)==LABEL && LA(2)==IDENTIFIER) ) {
#line 959 "f77.g"
          real_statement(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( !zzrv ) zzGUESS_DONE;
          if ( (setwd4[LA(1)]&0x20) && (setwd4[LA(2)]&0x40) && !( LA(1)==LABEL && LA(2)==IDENTIFIER) ) {
#line 960 "f77.g"
            double_precision_statement(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
          }
          else {
            if ( !zzrv ) zzGUESS_DONE;
            if ( (setwd4[LA(1)]&0x80) && (setwd5[LA(2)]&0x1) && !( LA(1)==LABEL && LA(2)==IDENTIFIER) ) {
#line 961 "f77.g"
              integer_statement(zzSTR);
              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
              }     /* MR10 */
            }
            else {
              if ( !zzrv ) zzGUESS_DONE;
              if ( (setwd5[LA(1)]&0x2) && (setwd5[LA(2)]&0x4) && !( LA(1)==LABEL && LA(2)==IDENTIFIER) ) {
#line 962 "f77.g"
                logical_statement(zzSTR);
                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                }     /* MR10 */
              }
              else {
                if ( !zzrv ) zzGUESS_DONE;
                if ( (setwd5[LA(1)]&0x8) && (setwd5[LA(2)]&0x10) && !( LA(1)==LABEL && LA(2)==IDENTIFIER) ) {
#line 963 "f77.g"
                  character_statement(zzSTR);
                  if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                  }     /* MR10 */
                }
                else {
                  if ( !zzrv ) zzGUESS_DONE;
                  if ( (setwd5[LA(1)]&0x20) && 
(setwd5[LA(2)]&0x40) && !( LA(1)==LABEL && LA(2)==IDENTIFIER) ) {
#line 964 "f77.g"
                    common_statement(zzSTR);
                    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                    }     /* MR10 */
                  }
                  else {
                    if ( !zzrv ) zzGUESS_DONE;
                    if ( (setwd5[LA(1)]&0x80) && (setwd6[LA(2)]&0x1) && !( LA(1)==LABEL && LA(2)==IDENTIFIER) ) {
#line 965 "f77.g"
                      external_statement(zzSTR);
                      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                      }     /* MR10 */
                    }
                    else {
                      if ( !zzrv ) zzGUESS_DONE;
                      if ( (setwd6[LA(1)]&0x2) && (setwd6[LA(2)]&0x4) && !( LA(1)==LABEL && LA(2)==IDENTIFIER) ) {
#line 966 "f77.g"
                        data_statement(zzSTR);
                        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                        }     /* MR10 */
                      }
                      else {
                        if ( !zzrv ) zzGUESS_DONE;
                        if ( (setwd6[LA(1)]&0x8) && (setwd6[LA(2)]&0x10) && !( LA(1)==LABEL && LA(2)==IDENTIFIER) ) {
#line 967 "f77.g"
                          call_statement(zzSTR);
                          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                          }     /* MR10 */
                        }
                        else {
                          if ( !zzrv ) zzGUESS_DONE;
                          if ( (setwd6[LA(1)]&0x20) && (setwd6[LA(2)]&0x40) ) {
#line 968 "f77.g"
                            do_statement(zzSTR);
                            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                            }     /* MR10 */
                          }
                          else {
                            if ( !zzrv ) zzGUESS_DONE;
                            if ( (setwd6[LA(1)]&0x80) && 
(setwd7[LA(2)]&0x1) && !(
 LA(1)==LABEL
   && ( LA(2)==IDENTIFIER || LA(2)==IF || LA(2)==END || LA(2)==STOP
      || LA(2)==SUBROUTINE || LA(2)==ENTRY || LA(2)==GO_TO)
) ) {
#line 969 "f77.g"
                              continue_statement(zzSTR);
                              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                              }     /* MR10 */
                            }
                            else {
                              if ( !zzrv ) zzGUESS_DONE;
                              if ( (setwd7[LA(1)]&0x2) && (setwd7[LA(2)]&0x4) ) {
#line 970 "f77.g"
                                assignment_statement(zzSTR);
                                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                }     /* MR10 */
                              }
                              else {
                                if ( !zzrv ) zzGUESS_DONE;
                                if ( (setwd7[LA(1)]&0x8) && (setwd7[LA(2)]&0x10) ) {
#line 971 "f77.g"
                                  if_statement(zzSTR);
                                  if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                  }     /* MR10 */
                                }
                                else {
                                  if ( !zzrv ) zzGUESS_DONE;
                                  if ( (setwd7[LA(1)]&0x20) && (setwd7[LA(2)]&0x40) && !(
 LA(1)==LABEL
   && ( LA(2)==STOP || LA(2)==SUBROUTINE || LA(2)==ENTRY || LA(2)==GO_TO)
) ) {
#line 972 "f77.g"
                                    end_statement(zzSTR);
                                    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                    }     /* MR10 */
                                  }
                                  else {
                                    if ( !zzrv ) zzGUESS_DONE;
                                    if ( (setwd7[LA(1)]&0x80) && (setwd8[LA(2)]&0x1) && !( LA(1)==LABEL && ( LA(2)==SUBROUTINE || LA(2)==ENTRY || LA(2)==GO_TO)) ) {
#line 973 "f77.g"
                                      stop_statement(zzSTR);
                                      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                      }     /* MR10 */
                                    }
                                    else {
                                      if ( !zzrv ) zzGUESS_DONE;
                                      if ( (setwd8[LA(1)]&0x2) && 
(setwd8[LA(2)]&0x4) ) {
#line 974 "f77.g"
                                        subroutine_statement(zzSTR);
                                        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                        }     /* MR10 */
                                      }
                                      else {
                                        if ( !zzrv ) zzGUESS_DONE;
                                        if ( (setwd8[LA(1)]&0x8) && (setwd8[LA(2)]&0x10) ) {
#line 975 "f77.g"
                                          entry_statement(zzSTR);
                                          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                          }     /* MR10 */
                                        }
                                        else {
                                          if ( !zzrv ) zzGUESS_DONE;
                                          if ( (setwd8[LA(1)]&0x20) && (setwd8[LA(2)]&0x40) ) {
#line 976 "f77.g"
                                            goto_statement(zzSTR);
                                            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                            }     /* MR10 */
                                          }
                                          else {zzFAIL(2,zzerr8,zzerr9,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
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
    zzresynch(setwd8, 0x80);
  }
}

void
#ifdef __USE_PROTOS
statement2(AST**_root)
#else
statement2(_root)
AST **_root;
#endif
{
#line 979 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    if ( (setwd9[LA(1)]&0x1) && (setwd9[LA(2)]&0x2) && !(
 LA(1)==LABEL
   && ( LA(2)==READ || LA(2)==WRITE || LA(2)==INQUIRE || LA(2)==BACKSPACE
      || LA(2)==ENDFILE || LA(2)==REWIND || LA(2)==BLOCK_GLOBALS || LA(2)==EXPORT
      || LA(2)==CHANGE || LA(2)==OPEN || LA(2)==CLOSE || LA(2)==DIMENSION
      || LA(2)==EQUIVALENCE || LA(2)==IMPLICIT || LA(2)==SAVE || LA(2)==PARAMETER
      || LA(2)==ASSIGN || LA(2)==FIND)
) ) {
#line 980 "f77.g"
      return_statement(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( (setwd9[LA(1)]&0x4) && (setwd9[LA(2)]&0x8) ) {
#line 981 "f77.g"
        read_statement(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {
        if ( (setwd9[LA(1)]&0x10) && 
(setwd9[LA(2)]&0x20) ) {
#line 982 "f77.g"
          write_statement(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( (LA(1)==LABEL) && (LA(2)==FORMAT) ) {
#line 983 "f77.g"
            format_statement(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
          }
          else {
            if ( (setwd9[LA(1)]&0x40) && (setwd9[LA(2)]&0x80) ) {
#line 984 "f77.g"
              inquire_statement(zzSTR);
              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
              }     /* MR10 */
            }
            else {
              if ( (setwd10[LA(1)]&0x1) && (setwd10[LA(2)]&0x2) ) {
#line 985 "f77.g"
                backspace_statement(zzSTR);
                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                }     /* MR10 */
              }
              else {
                if ( (setwd10[LA(1)]&0x4) && (setwd10[LA(2)]&0x8) ) {
#line 986 "f77.g"
                  endfile_statement(zzSTR);
                  if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                  }     /* MR10 */
                }
                else {
                  if ( (setwd10[LA(1)]&0x10) && 
(setwd10[LA(2)]&0x20) ) {
#line 987 "f77.g"
                    rewind_statement(zzSTR);
                    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                    }     /* MR10 */
                  }
                  else {
                    if ( (setwd10[LA(1)]&0x40) && (setwd10[LA(2)]&0x80) && !(
 LA(1)==LABEL
   && ( LA(2)==EXPORT || LA(2)==CHANGE || LA(2)==OPEN || LA(2)==CLOSE
      || LA(2)==DIMENSION || LA(2)==EQUIVALENCE || LA(2)==IMPLICIT || LA(2)==SAVE
      || LA(2)==PARAMETER || LA(2)==ASSIGN || LA(2)==FIND)
) ) {
#line 988 "f77.g"
                      block_globals_statement(zzSTR);
                      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                      }     /* MR10 */
                    }
                    else {
                      if ( (setwd11[LA(1)]&0x1) && (setwd11[LA(2)]&0x2) ) {
#line 989 "f77.g"
                        export_statement(zzSTR);
                        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                        }     /* MR10 */
                      }
                      else {
                        if ( (setwd11[LA(1)]&0x4) && (setwd11[LA(2)]&0x8) ) {
#line 990 "f77.g"
                          change_statement(zzSTR);
                          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                          }     /* MR10 */
                        }
                        else {
                          if ( (setwd11[LA(1)]&0x10) && (setwd11[LA(2)]&0x20) ) {
#line 991 "f77.g"
                            open_statement(zzSTR);
                            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                            }     /* MR10 */
                          }
                          else {
                            if ( (setwd11[LA(1)]&0x40) && 
(setwd11[LA(2)]&0x80) ) {
#line 992 "f77.g"
                              close_statement(zzSTR);
                              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                              }     /* MR10 */
                            }
                            else {
                              if ( (setwd12[LA(1)]&0x1) && (setwd12[LA(2)]&0x2) ) {
#line 993 "f77.g"
                                dimension_statement(zzSTR);
                                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                }     /* MR10 */
                              }
                              else {
                                if ( (setwd12[LA(1)]&0x4) && (setwd12[LA(2)]&0x8) ) {
#line 994 "f77.g"
                                  equivalence_statement(zzSTR);
                                  if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                  }     /* MR10 */
                                }
                                else {
                                  if ( (setwd12[LA(1)]&0x10) && (setwd12[LA(2)]&0x20) ) {
#line 995 "f77.g"
                                    implicit_statement(zzSTR);
                                    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                    }     /* MR10 */
                                  }
                                  else {
                                    if ( (setwd12[LA(1)]&0x40) && (setwd12[LA(2)]&0x80) ) {
#line 996 "f77.g"
                                      save_statement(zzSTR);
                                      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                      }     /* MR10 */
                                    }
                                    else {
                                      if ( (setwd13[LA(1)]&0x1) && 
(setwd13[LA(2)]&0x2) ) {
#line 997 "f77.g"
                                        parameter_statement(zzSTR);
                                        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                        }     /* MR10 */
                                      }
                                      else {
                                        if ( (setwd13[LA(1)]&0x4) && (setwd13[LA(2)]&0x8) ) {
#line 998 "f77.g"
                                          assign_statement(zzSTR);
                                          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                          }     /* MR10 */
                                        }
                                        else {
                                          if ( (setwd13[LA(1)]&0x10) && (setwd13[LA(2)]&0x20) ) {
#line 999 "f77.g"
                                            find_statement(zzSTR);
                                            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                            }     /* MR10 */
                                          }
                                          else {zzFAIL(2,zzerr10,zzerr11,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
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
    zzresynch(setwd13, 0x40);
  }
}

void
#ifdef __USE_PROTOS
file_statement(AST**_root)
#else
file_statement(_root)
AST **_root;
#endif
{
#line 1002 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1002 "f77.g"
    zzmatch(FILEKEYWORD);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1002 "f77.g"
    unit_identifier(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1003 "f77.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1003 "f77.g"
    file_item(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1003 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 1003 "f77.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1003 "f77.g"
          file_item(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
#line 1004 "f77.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd13, 0x80);
  }
}

void
#ifdef __USE_PROTOS
file_item(AST**_root)
#else
file_item(_root)
AST **_root;
#endif
{
#line 1006 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    if ( (LA(1)==KIND) ) {
#line 1007 "f77.g"
      zzmatch(KIND);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 1007 "f77.g"
      zzmatch(EQUAL);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 1007 "f77.g"
      file_name(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( (LA(1)==TITLE) ) {
#line 1008 "f77.g"
        zzmatch(TITLE);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
#line 1008 "f77.g"
        zzmatch(EQUAL);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
#line 1008 "f77.g"
        file_name(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {
        if ( (LA(1)==FILETYPE) ) {
#line 1009 "f77.g"
          zzmatch(FILETYPE);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1009 "f77.g"
          zzmatch(EQUAL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1009 "f77.g"
          int_const(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( (LA(1)==NEWFILE) ) {
#line 1010 "f77.g"
            zzmatch(NEWFILE);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 1010 "f77.g"
            zzmatch(EQUAL);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 1010 "f77.g"
            file_name(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
          }
          else {
            if ( 
(LA(1)==MYUSE) ) {
#line 1011 "f77.g"
              zzmatch(MYUSE);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 1011 "f77.g"
              zzmatch(EQUAL);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 1011 "f77.g"
              int_const(zzSTR);
              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
              }     /* MR10 */
            }
            else {
              if ( (LA(1)==MAXRECSIZE) ) {
#line 1012 "f77.g"
                zzmatch(MAXRECSIZE);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 1012 "f77.g"
                zzmatch(EQUAL);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 1012 "f77.g"
                int_const(zzSTR);
                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                }     /* MR10 */
              }
              else {
                if ( (LA(1)==SAVEFACTOR) ) {
#line 1013 "f77.g"
                  zzmatch(SAVEFACTOR);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
#line 1013 "f77.g"
                  zzmatch(EQUAL);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
#line 1013 "f77.g"
                  int_const(zzSTR);
                  if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                  }     /* MR10 */
                }
                else {
                  if ( (LA(1)==BLOCKSIZE) ) {
#line 1014 "f77.g"
                    zzmatch(BLOCKSIZE);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
#line 1014 "f77.g"
                    zzmatch(EQUAL);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
#line 1014 "f77.g"
                    int_const(zzSTR);
                    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                    }     /* MR10 */
                  }
                  else {
                    if ( (LA(1)==SECURITYTYPE) ) {
#line 1015 "f77.g"
                      zzmatch(SECURITYTYPE);zzNON_GUESS_MODE {
                         zzsubchild(_root, &_sibling, &_tail);                      }
                       zzCONSUME;
#line 1015 "f77.g"
                      zzmatch(EQUAL);zzNON_GUESS_MODE {
                         zzsubchild(_root, &_sibling, &_tail);                      }
                       zzCONSUME;
#line 1015 "f77.g"
                      file_name(zzSTR);
                      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                      }     /* MR10 */
                    }
                    else {
                      if ( 
(LA(1)==AREAS) ) {
#line 1016 "f77.g"
                        zzmatch(AREAS);zzNON_GUESS_MODE {
                           zzsubchild(_root, &_sibling, &_tail);                        }
                         zzCONSUME;
#line 1016 "f77.g"
                        zzmatch(EQUAL);zzNON_GUESS_MODE {
                           zzsubchild(_root, &_sibling, &_tail);                        }
                         zzCONSUME;
#line 1016 "f77.g"
                        int_const(zzSTR);
                        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                        }     /* MR10 */
                      }
                      else {
                        if ( (LA(1)==AREASIZE) ) {
#line 1017 "f77.g"
                          zzmatch(AREASIZE);zzNON_GUESS_MODE {
                             zzsubchild(_root, &_sibling, &_tail);                          }
                           zzCONSUME;
#line 1017 "f77.g"
                          zzmatch(EQUAL);zzNON_GUESS_MODE {
                             zzsubchild(_root, &_sibling, &_tail);                          }
                           zzCONSUME;
#line 1017 "f77.g"
                          int_const(zzSTR);
                          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                          }     /* MR10 */
                        }
                        else {
                          if ( (LA(1)==PROTECTION) ) {
#line 1018 "f77.g"
                            zzmatch(PROTECTION);zzNON_GUESS_MODE {
                               zzsubchild(_root, &_sibling, &_tail);                            }
                             zzCONSUME;
#line 1018 "f77.g"
                            zzmatch(EQUAL);zzNON_GUESS_MODE {
                               zzsubchild(_root, &_sibling, &_tail);                            }
                             zzCONSUME;
#line 1018 "f77.g"
                            zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
                               zzsubchild(_root, &_sibling, &_tail);                            }
                             zzCONSUME;
                          }
                          else {
                            if ( (LA(1)==UNITS) ) {
#line 1019 "f77.g"
                              zzmatch(UNITS);zzNON_GUESS_MODE {
                                 zzsubchild(_root, &_sibling, &_tail);                              }
                               zzCONSUME;
#line 1019 "f77.g"
                              zzmatch(EQUAL);zzNON_GUESS_MODE {
                                 zzsubchild(_root, &_sibling, &_tail);                              }
                               zzCONSUME;
#line 1019 "f77.g"
                              {
                                zzBLOCK(zztasp2);
                                zzMake0;
                                {
                                  if ( (setwd14[LA(1)]&0x1) ) {
#line 1019 "f77.g"
                                    file_name(zzSTR);
                                    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                    }     /* MR10 */
                                  }
                                  else {
                                    if ( 
(LA(1)==CONSTINT) ) {
#line 1019 "f77.g"
                                      zzmatch(CONSTINT);zzNON_GUESS_MODE {
                                         zzsubchild(_root, &_sibling, &_tail);                                      }
                                       zzCONSUME;
                                    }
                                    else {zzFAIL(1,zzerr12,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                                  }
                                  zzEXIT(zztasp2);
                                }
                              }
                            }
                            else {
                              if ( (LA(1)==UPDATEFILE) ) {
#line 1020 "f77.g"
                                zzmatch(UPDATEFILE);zzNON_GUESS_MODE {
                                   zzsubchild(_root, &_sibling, &_tail);                                }
                                 zzCONSUME;
#line 1020 "f77.g"
                                zzmatch(EQUAL);zzNON_GUESS_MODE {
                                   zzsubchild(_root, &_sibling, &_tail);                                }
                                 zzCONSUME;
#line 1020 "f77.g"
                                file_name(zzSTR);
                                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                }     /* MR10 */
                              }
                              else {
                                if ( (LA(1)==FILE_WORD) ) {
#line 1021 "f77.g"
                                  zzmatch(FILE_WORD);zzNON_GUESS_MODE {
                                     zzsubchild(_root, &_sibling, &_tail);                                  }
                                   zzCONSUME;
#line 1021 "f77.g"
                                  zzmatch(EQUAL);zzNON_GUESS_MODE {
                                     zzsubchild(_root, &_sibling, &_tail);                                  }
                                   zzCONSUME;
#line 1021 "f77.g"
                                  file_name(zzSTR);
                                  if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                  }     /* MR10 */
                                }
                                else {
                                  if ( (LA(1)==STATUS) ) {
#line 1022 "f77.g"
                                    zzmatch(STATUS);zzNON_GUESS_MODE {
                                       zzsubchild(_root, &_sibling, &_tail);                                    }
                                     zzCONSUME;
#line 1022 "f77.g"
                                    zzmatch(EQUAL);zzNON_GUESS_MODE {
                                       zzsubchild(_root, &_sibling, &_tail);                                    }
                                     zzCONSUME;
#line 1022 "f77.g"
                                    file_name(zzSTR);
                                    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                    }     /* MR10 */
                                  }
                                  else {
                                    if ( (LA(1)==ACCESS) ) {
#line 1023 "f77.g"
                                      zzmatch(ACCESS);zzNON_GUESS_MODE {
                                         zzsubchild(_root, &_sibling, &_tail);                                      }
                                       zzCONSUME;
#line 1023 "f77.g"
                                      zzmatch(EQUAL);zzNON_GUESS_MODE {
                                         zzsubchild(_root, &_sibling, &_tail);                                      }
                                       zzCONSUME;
#line 1023 "f77.g"
                                      file_name(zzSTR);
                                      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                      }     /* MR10 */
                                    }
                                    else {
                                      if ( 
(LA(1)==FORM) ) {
#line 1024 "f77.g"
                                        zzmatch(FORM);zzNON_GUESS_MODE {
                                           zzsubchild(_root, &_sibling, &_tail);                                        }
                                         zzCONSUME;
#line 1024 "f77.g"
                                        zzmatch(EQUAL);zzNON_GUESS_MODE {
                                           zzsubchild(_root, &_sibling, &_tail);                                        }
                                         zzCONSUME;
#line 1024 "f77.g"
                                        file_name(zzSTR);
                                        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                        }     /* MR10 */
                                      }
                                      else {
                                        if ( (LA(1)==RECL) ) {
#line 1025 "f77.g"
                                          zzmatch(RECL);zzNON_GUESS_MODE {
                                             zzsubchild(_root, &_sibling, &_tail);                                          }
                                           zzCONSUME;
#line 1025 "f77.g"
                                          zzmatch(EQUAL);zzNON_GUESS_MODE {
                                             zzsubchild(_root, &_sibling, &_tail);                                          }
                                           zzCONSUME;
#line 1025 "f77.g"
                                          file_name(zzSTR);
                                          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                          }     /* MR10 */
                                        }
                                        else {
                                          if ( (LA(1)==BLANK) ) {
#line 1026 "f77.g"
                                            zzmatch(BLANK);zzNON_GUESS_MODE {
                                               zzsubchild(_root, &_sibling, &_tail);                                            }
                                             zzCONSUME;
#line 1026 "f77.g"
                                            zzmatch(EQUAL);zzNON_GUESS_MODE {
                                               zzsubchild(_root, &_sibling, &_tail);                                            }
                                             zzCONSUME;
#line 1026 "f77.g"
                                            file_name(zzSTR);
                                            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                            }     /* MR10 */
                                          }
                                          else {zzFAIL(1,zzerr13,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
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
    zzresynch(setwd14, 0x2);
  }
}

void
#ifdef __USE_PROTOS
file_name(AST**_root)
#else
file_name(_root)
AST **_root;
#endif
{
#line 1029 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1029 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==IDENTIFIER) ) {
#line 1029 "f77.g"
          zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==QUOTED_STRING) ) {
#line 1029 "f77.g"
            zzmatch(QUOTED_STRING);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
          }
          else {zzFAIL(1,zzerr14,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
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
    zzresynch(setwd14, 0x4);
  }
}

void
#ifdef __USE_PROTOS
equivalence_statement(AST**_root)
#else
equivalence_statement(_root)
AST **_root;
#endif
{
#line 1034 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1034 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( 
(LA(1)==LABEL) ) {
#line 1034 "f77.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==EQUIVALENCE) ) {
          }
          else {zzFAIL(1,zzerr15,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1034 "f77.g"
    zzmatch(EQUIVALENCE);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1034 "f77.g"
    equiv_item(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1034 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 1034 "f77.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1034 "f77.g"
          equiv_item(zzSTR);
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
    zzresynch(setwd14, 0x8);
  }
}

void
#ifdef __USE_PROTOS
equiv_item(AST**_root)
#else
equiv_item(_root)
AST **_root;
#endif
{
#line 1036 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1036 "f77.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1036 "f77.g"
    equiv_entity(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1036 "f77.g"
    {
      zzBLOCK(zztasp2);
      int zzcnt=1;
      zzMake0;
      {
        do {
#line 1036 "f77.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1036 "f77.g"
          equiv_entity(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        } while ( (LA(1)==COMMA) );
        zzEXIT(zztasp2);
      }
    }
#line 1036 "f77.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd14, 0x10);
  }
}

void
#ifdef __USE_PROTOS
equiv_entity(AST**_root)
#else
equiv_entity(_root)
AST **_root;
#endif
{
#line 1038 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1038 "f77.g"
    variable(zzSTR, LVALUE );
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd14, 0x20);
  }
}

void
#ifdef __USE_PROTOS
length_spec(AST**_root)
#else
length_spec(_root)
AST **_root;
#endif
{
#line 1041 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1041 "f77.g"
    int type;
    if ( (LA(1)==LP) && (LA(2)==STAR) ) {
#line 1041 "f77.g"
      zzmatch(LP);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 1041 "f77.g"
      zzmatch(STAR);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 1041 "f77.g"
      zzmatch(RP);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
    }
    else {
      if ( (LA(1)==LP) && (setwd14[LA(2)]&0x40) ) {
#line 1042 "f77.g"
        zzmatch(LP);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
#line 1042 "f77.g"
        zzNON_GUESS_MODE {
           type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
        } else {
          expression(zzSTR);
        }
#line 1042 "f77.g"
        zzmatch(RP);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
      }
      else {
        if ( (LA(1)==CONSTINT) ) {
#line 1043 "f77.g"
          zzmatch(CONSTINT);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {zzFAIL(2,zzerr16,zzerr17,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd14, 0x80);
  }
}

void
#ifdef __USE_PROTOS
common_statement(AST**_root)
#else
common_statement(_root)
AST **_root;
#endif
{
#line 1046 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1046 "f77.g"
    CurrentStatement = COMMON;
#line 1047 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 1047 "f77.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( 
(LA(1)==COMMON) ) {
          }
          else {zzFAIL(1,zzerr18,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1047 "f77.g"
    zzmatch(COMMON);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1047 "f77.g"
    block_item(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1047 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 1047 "f77.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1047 "f77.g"
          block_item(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
    zzNON_GUESS_MODE {
#line 1048 "f77.g"
      CurrentStatement = INVALID;
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd15, 0x1);
  }
}

void
#ifdef __USE_PROTOS
block_item(AST**_root)
#else
block_item(_root)
AST **_root;
#endif
{
#line 1050 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    if ( (LA(1)==IDENTIFIER) ) {
#line 1051 "f77.g"
      variable(zzSTR, LVALUE );
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( (LA(1)==DIV) && (LA(2)==IDENTIFIER) ) {
#line 1052 "f77.g"
        zzmatch(DIV);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
#line 1052 "f77.g"
        zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
#line 1052 "f77.g"
        zzmatch(DIV);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
#line 1052 "f77.g"
        variable(zzSTR, LVALUE );
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {
        if ( (LA(1)==CONCAT) ) {
#line 1053 "f77.g"
          zzmatch(CONCAT);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1053 "f77.g"
          variable(zzSTR, LVALUE );
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( (LA(1)==DIV) && 
(LA(2)==DIV) ) {
#line 1054 "f77.g"
            zzmatch(DIV);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 1054 "f77.g"
            zzmatch(DIV);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 1054 "f77.g"
            variable(zzSTR, LVALUE );
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
          }
          else {zzFAIL(2,zzerr19,zzerr20,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd15, 0x2);
  }
}

void
#ifdef __USE_PROTOS
data_statement(AST**_root)
#else
data_statement(_root)
AST **_root;
#endif
{
#line 1057 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1057 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 1057 "f77.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==DATA) ) {
          }
          else {zzFAIL(1,zzerr21,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1057 "f77.g"
    zzmatch(DATA);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1057 "f77.g"
    data_list(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd15, 0x4);
  }
}

void
#ifdef __USE_PROTOS
data_list(AST**_root)
#else
data_list(_root)
AST **_root;
#endif
{
#line 1059 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1059 "f77.g"
    data_item(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1059 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (setwd15[LA(1)]&0x8) && (setwd15[LA(2)]&0x10) && !( LA(1)==1 && LA(2)==1 || LA(1)==IDENTIFIER && LA(2)==LP) ) {
#line 1059 "f77.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              if ( (LA(1)==COMMA) ) {
#line 1059 "f77.g"
                zzmatch(COMMA);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
              }
              else {
                if ( (setwd15[LA(1)]&0x20) ) {
                }
                else {zzFAIL(1,zzerr22,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
              }
              zzEXIT(zztasp3);
            }
          }
#line 1059 "f77.g"
          data_item(zzSTR);
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
    zzresynch(setwd15, 0x40);
  }
}

void
#ifdef __USE_PROTOS
data_item(AST**_root)
#else
data_item(_root)
AST **_root;
#endif
{
#line 1061 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1061 "f77.g"
    data_var_list(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1061 "f77.g"
    zzmatch(DIV);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1061 "f77.g"
    data_const_list(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1061 "f77.g"
    zzmatch(DIV);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd15, 0x80);
  }
}

void
#ifdef __USE_PROTOS
data_var_list(AST**_root)
#else
data_var_list(_root)
AST **_root;
#endif
{
#line 1063 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1063 "f77.g"
    data_var_list_elem(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1063 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 1063 "f77.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1063 "f77.g"
          data_var_list_elem(zzSTR);
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
    zzresynch(setwd16, 0x1);
  }
}

void
#ifdef __USE_PROTOS
data_var_list_elem(AST**_root)
#else
data_var_list_elem(_root)
AST **_root;
#endif
{
#line 1066 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (LA(1)==LP) ) {
#line 1067 "f77.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 1067 "f77.g"
          zzmatch(LP);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 1067 "f77.g"
      data_implied_do_list(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      zzGUESS
      if ( !zzrv && (LA(1)==IDENTIFIER) ) {
#line 1068 "f77.g"
        {
          zzBLOCK(zztasp2);
          zzMake0;
          {
#line 1068 "f77.g"
            zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
            zzEXIT(zztasp2);
          }
        }
        zzGUESS_DONE
#line 1068 "f77.g"
        variable(zzSTR, LVALUE );
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      /* MR10 */ else {
        /* MR10 */ if ( !zzrv ) zzGUESS_DONE;
        /* MR10 */ if (0) {}     /* last alternative of block is guess block */
        else {zzFAIL(1,zzerr23,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd16, 0x2);
  }
}

void
#ifdef __USE_PROTOS
data_const_list(AST**_root)
#else
data_const_list(_root)
AST **_root;
#endif
{
#line 1070 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1070 "f77.g"
    data_constant(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1070 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 1070 "f77.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1070 "f77.g"
          data_constant(zzSTR);
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
    zzresynch(setwd16, 0x4);
  }
}

void
#ifdef __USE_PROTOS
data_constant(AST**_root)
#else
data_constant(_root)
AST **_root;
#endif
{
#line 1072 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
#line 1072 "f77.g"
    int dummy;
    zzGUESS
    if ( !zzrv && (LA(1)==CONSTINT) && (LA(2)==STAR) ) {
#line 1073 "f77.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 1073 "f77.g"
          zzmatch(CONSTINT);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1073 "f77.g"
          zzmatch(STAR);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 1073 "f77.g"
      zzmatch(CONSTINT);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 1073 "f77.g"
      zzmatch(STAR);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 1073 "f77.g"
      zzNON_GUESS_MODE {
         dummy  = constant(zzSTR); zzlink(_root, &_sibling, &_tail);
      } else {
        constant(zzSTR);
      }
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      zzGUESS
      if ( !zzrv && (setwd16[LA(1)]&0x8) ) {
#line 1074 "f77.g"
        {
          zzBLOCK(zztasp2);
          zzMake0;
          {
            if ( (LA(1)==MIN) ) {
#line 1074 "f77.g"
              zzmatch(MIN);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
            }
            else {
              if ( (LA(1)==PLU) ) {
#line 1074 "f77.g"
                zzmatch(PLU);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
              }
              else {zzFAIL(1,zzerr24,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
            }
            zzEXIT(zztasp2);
          }
        }
        zzGUESS_DONE
#line 1074 "f77.g"
        {
          zzBLOCK(zztasp2);
          zzMake0;
          {
            if ( 
(LA(1)==MIN) ) {
#line 1074 "f77.g"
              zzmatch(MIN);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
            }
            else {
              if ( (LA(1)==PLU) ) {
#line 1074 "f77.g"
                zzmatch(PLU);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
              }
              else {zzFAIL(1,zzerr25,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
            }
            zzEXIT(zztasp2);
          }
        }
#line 1074 "f77.g"
        zzNON_GUESS_MODE {
           dummy  = constant(zzSTR); zzlink(_root, &_sibling, &_tail);
        } else {
          constant(zzSTR);
        }
      }
      else {
        if ( !zzrv ) zzGUESS_DONE;
        if ( (setwd16[LA(1)]&0x10) && (setwd16[LA(2)]&0x20) ) {
#line 1075 "f77.g"
          zzNON_GUESS_MODE {
             dummy  = constant(zzSTR); zzlink(_root, &_sibling, &_tail);
          } else {
            constant(zzSTR);
          }
        }
        else {zzFAIL(2,zzerr26,zzerr27,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd16, 0x40);
  }
}

void
#ifdef __USE_PROTOS
data_implied_do_list(AST**_root)
#else
data_implied_do_list(_root)
AST **_root;
#endif
{
#line 1077 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1077 "f77.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1077 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==IDENTIFIER) ) {
#line 1077 "f77.g"
          array_element_reference(zzSTR, LVALUE );
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( (LA(1)==LP) ) {
#line 1078 "f77.g"
            data_implied_do_list(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
          }
          else {zzFAIL(1,zzerr28,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1079 "f77.g"
    zzmatch(COMMA);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1079 "f77.g"
    implied_do_variable(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1079 "f77.g"
    zzmatch(EQUAL);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1079 "f77.g"
    int_const(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1080 "f77.g"
    zzmatch(COMMA);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1080 "f77.g"
    int_const(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1081 "f77.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd16, 0x80);
  }
}

void
#ifdef __USE_PROTOS
implied_do_variable(AST**_root)
#else
implied_do_variable(_root)
AST **_root;
#endif
{
#line 1083 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1083 "f77.g"
    zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd17, 0x1);
  }
}

void
#ifdef __USE_PROTOS
do_statement(AST**_root)
#else
do_statement(_root)
AST **_root;
#endif
{
#line 1085 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1085 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( 
(LA(1)==LABEL) ) {
#line 1085 "f77.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==DO) ) {
          }
          else {zzFAIL(1,zzerr29,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1085 "f77.g"
    zzmatch(DO);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1085 "f77.g"
    statement_label(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1086 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==COMMA) ) {
#line 1086 "f77.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==IDENTIFIER) ) {
          }
          else {zzFAIL(1,zzerr30,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1086 "f77.g"
    do_variable(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1086 "f77.g"
    zzmatch(EQUAL);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1086 "f77.g"
    initial(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1087 "f77.g"
    zzmatch(COMMA);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1087 "f77.g"
    terminal(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1087 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==COMMA) ) {
#line 1087 "f77.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1087 "f77.g"
          incremental(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( 
(setwd17[LA(1)]&0x2) ) {
          }
          else {zzFAIL(1,zzerr31,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
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
    zzresynch(setwd17, 0x4);
  }
}

void
#ifdef __USE_PROTOS
do_variable(AST**_root)
#else
do_variable(_root)
AST **_root;
#endif
{
#line 1089 "f77.g"
  zzRULE;
  Attrib i;
  AST *i_ast=NULL;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1089 "f77.g"
    zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
            i = zzaCur;
      i_ast = zzastCur;
    }
    
    zzNON_GUESS_MODE {
#line 1090 "f77.g"

      AddSymbol( i.text, INTEGER_ID); /*And add it to the symbol table.*/
      zzastArg(1)->token = INTEGER_ID;
    }
 zzCONSUME;

    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd17, 0x8);
  }
}

void
#ifdef __USE_PROTOS
initial(AST**_root)
#else
initial(_root)
AST **_root;
#endif
{
#line 1094 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1094 "f77.g"
    int type;
#line 1094 "f77.g"
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
    zzresynch(setwd17, 0x10);
  }
}

void
#ifdef __USE_PROTOS
terminal(AST**_root)
#else
terminal(_root)
AST **_root;
#endif
{
#line 1095 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1095 "f77.g"
    int type;
#line 1095 "f77.g"
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
    zzresynch(setwd17, 0x20);
  }
}

void
#ifdef __USE_PROTOS
incremental(AST**_root)
#else
incremental(_root)
AST **_root;
#endif
{
#line 1096 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1096 "f77.g"
    int type;
#line 1096 "f77.g"
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
    zzresynch(setwd17, 0x40);
  }
}

void
#ifdef __USE_PROTOS
continue_statement(AST**_root)
#else
continue_statement(_root)
AST **_root;
#endif
{
#line 1098 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1098 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 1098 "f77.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==CONTINUE) ) {
          }
          else {zzFAIL(1,zzerr32,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1098 "f77.g"
    zzmatch(CONTINUE);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
#line 1099 "f77.g"

    }
 zzCONSUME;

    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd17, 0x80);
  }
}

void
#ifdef __USE_PROTOS
call_statement(AST**_root)
#else
call_statement(_root)
AST **_root;
#endif
{
#line 1102 "f77.g"
  zzRULE;
  Attrib s;
  AST *s_ast=NULL;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1102 "f77.g"
    int type;
#line 1103 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 1103 "f77.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==CALL) ) {
          }
          else {zzFAIL(1,zzerr33,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1103 "f77.g"
    zzmatch(CALL);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1103 "f77.g"
    zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
            s = zzaCur;
      s_ast = zzastCur;
    }
     zzCONSUME;
#line 1103 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( 
(LA(1)==LP) ) {
#line 1103 "f77.g"
          call_arg_list(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( (setwd18[LA(1)]&0x1) ) {
          }
          else {zzFAIL(1,zzerr34,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
    zzNON_GUESS_MODE {
#line 1104 "f77.g"

      type = LookUp( s.text);
      if(type != FUNCTION_NAME) {
        ChangeType( s.text, FUNCTION_NAME);
      }
      zzastArg(3)->token = FUNCTION_NAME;
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd18, 0x2);
  }
}

void
#ifdef __USE_PROTOS
call_arg_list(AST**_root)
#else
call_arg_list(_root)
AST **_root;
#endif
{
#line 1112 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1112 "f77.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1112 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (setwd18[LA(1)]&0x4) ) {
#line 1112 "f77.g"
          call_arg_item(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 1113 "f77.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              while ( (LA(1)==COMMA) ) {
#line 1113 "f77.g"
                zzmatch(COMMA);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 1113 "f77.g"
                call_arg_item(zzSTR);
                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                }     /* MR10 */
                zzLOOP(zztasp3);
              }
              zzEXIT(zztasp3);
            }
          }
        }
        else {
          if ( (LA(1)==RP) ) {
          }
          else {zzFAIL(1,zzerr35,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1114 "f77.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd18, 0x8);
  }
}

void
#ifdef __USE_PROTOS
call_arg_item(AST**_root)
#else
call_arg_item(_root)
AST **_root;
#endif
{
#line 1115 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1115 "f77.g"
    int type;
#line 1117 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        zzGUESS_BLOCK
        zzGUESS
        if ( !zzrv && (setwd18[LA(1)]&0x10) ) {
#line 1117 "f77.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              if ( (LA(1)==STAR) ) {
#line 1117 "f77.g"
                zzmatch(STAR);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
              }
              else {
                if ( (LA(1)==AMPERSAND) ) {
#line 1117 "f77.g"
                  zzmatch(AMPERSAND);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
                }
                else {zzFAIL(1,zzerr36,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
              }
              zzEXIT(zztasp3);
            }
          }
          zzGUESS_DONE
#line 1117 "f77.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              if ( 
(LA(1)==STAR) ) {
#line 1117 "f77.g"
                zzmatch(STAR);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
              }
              else {
                if ( (LA(1)==AMPERSAND) ) {
#line 1117 "f77.g"
                  zzmatch(AMPERSAND);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
                }
                else {zzFAIL(1,zzerr37,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
              }
              zzEXIT(zztasp3);
            }
          }
#line 1117 "f77.g"
          statement_label(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( !zzrv ) zzGUESS_DONE;
          if ( (setwd18[LA(1)]&0x20) ) {
#line 1118 "f77.g"
            zzNON_GUESS_MODE {
               type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
            } else {
              expression(zzSTR);
            }
          }
          else {zzFAIL(1,zzerr38,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
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
    zzresynch(setwd18, 0x40);
  }
}

void
#ifdef __USE_PROTOS
statement_label(AST**_root)
#else
statement_label(_root)
AST **_root;
#endif
{
#line 1121 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1121 "f77.g"
    zzmatch(CONSTINT);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd18, 0x80);
  }
}

void
#ifdef __USE_PROTOS
if_statement(AST**_root)
#else
if_statement(_root)
AST **_root;
#endif
{
#line 1123 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1123 "f77.g"
    int type;
#line 1124 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        zzGUESS_BLOCK
        zzGUESS
        if ( !zzrv && (setwd19[LA(1)]&0x1) && (setwd19[LA(2)]&0x2) ) {
#line 1124 "f77.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
#line 1124 "f77.g"
              {
                zzBLOCK(zztasp4);
                zzMake0;
                {
                  if ( (LA(1)==LABEL) ) {
#line 1124 "f77.g"
                    zzmatch(LABEL);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
                  }
                  else {
                    if ( 
(LA(1)==IF) ) {
                    }
                    else {zzFAIL(1,zzerr39,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                  }
                  zzEXIT(zztasp4);
                }
              }
#line 1124 "f77.g"
              zzmatch(IF);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 1124 "f77.g"
              zzmatch(LP);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 1124 "f77.g"
              zzNON_GUESS_MODE {
                 type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
              } else {
                expression(zzSTR);
              }
#line 1124 "f77.g"
              zzmatch(RP);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
#line 1124 "f77.g"
              zzmatch(THEN);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
              zzEXIT(zztasp3);
            }
          }
          zzGUESS_DONE
#line 1124 "f77.g"
          block_if_statement(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( !zzrv ) zzGUESS_DONE;
          zzGUESS
          if ( !zzrv && (setwd19[LA(1)]&0x4) && (setwd19[LA(2)]&0x8) ) {
#line 1125 "f77.g"
            {
              zzBLOCK(zztasp3);
              zzMake0;
              {
#line 1125 "f77.g"
                {
                  zzBLOCK(zztasp4);
                  zzMake0;
                  {
                    if ( (LA(1)==LABEL) ) {
#line 1125 "f77.g"
                      zzmatch(LABEL);zzNON_GUESS_MODE {
                         zzsubchild(_root, &_sibling, &_tail);                      }
                       zzCONSUME;
                    }
                    else {
                      if ( (LA(1)==IF) ) {
                      }
                      else {zzFAIL(1,zzerr40,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                    }
                    zzEXIT(zztasp4);
                  }
                }
#line 1125 "f77.g"
                zzmatch(IF);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 1125 "f77.g"
                zzmatch(LP);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 1125 "f77.g"
                zzNON_GUESS_MODE {
                   type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
                } else {
                  expression(zzSTR);
                }
#line 1125 "f77.g"
                zzmatch(RP);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 1125 "f77.g"
                label(zzSTR);
                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                }     /* MR10 */
                zzEXIT(zztasp3);
              }
            }
            zzGUESS_DONE
#line 1125 "f77.g"
            arithmetic_if_statement(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
          }
          else {
            if ( !zzrv ) zzGUESS_DONE;
            if ( (setwd19[LA(1)]&0x10) && 
(setwd19[LA(2)]&0x20) ) {
#line 1126 "f77.g"
              logical_if_statement(zzSTR);
              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
              }     /* MR10 */
            }
            else {zzFAIL(2,zzerr41,zzerr42,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
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
    zzresynch(setwd19, 0x40);
  }
}

void
#ifdef __USE_PROTOS
block_if_statement(AST**_root)
#else
block_if_statement(_root)
AST **_root;
#endif
{
#line 1130 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1130 "f77.g"
    int type;
#line 1131 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 1131 "f77.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==IF) ) {
          }
          else {zzFAIL(1,zzerr43,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1131 "f77.g"
    zzmatch(IF);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1131 "f77.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1131 "f77.g"
    zzNON_GUESS_MODE {
       type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
    } else {
      expression(zzSTR);
    }
#line 1131 "f77.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1131 "f77.g"
    zzmatch(THEN);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1132 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (setwd19[LA(1)]&0x80) ) {
#line 1132 "f77.g"
          statement_block(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( (setwd20[LA(1)]&0x1) ) {
          }
          else {zzFAIL(1,zzerr44,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1135 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (setwd20[LA(1)]&0x2) ) {
#line 1134 "f77.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              if ( 
(LA(1)==ELSE) ) {
#line 1134 "f77.g"
                zzmatch(ELSE);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
              }
              else {
                if ( (LA(1)==ELSE_IF) ) {
#line 1134 "f77.g"
                  zzmatch(ELSE_IF);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
#line 1134 "f77.g"
                  zzmatch(LP);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
#line 1134 "f77.g"
                  zzNON_GUESS_MODE {
                     type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
                  } else {
                    expression(zzSTR);
                  }
#line 1134 "f77.g"
                  zzmatch(RP);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
                }
                else {zzFAIL(1,zzerr45,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
              }
              zzEXIT(zztasp3);
            }
          }
#line 1135 "f77.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              if ( (setwd20[LA(1)]&0x4) ) {
#line 1135 "f77.g"
                statement_block(zzSTR);
                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                }     /* MR10 */
              }
              else {
                if ( (LA(1)==END_IF) ) {
                }
                else {zzFAIL(1,zzerr46,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
              }
              zzEXIT(zztasp3);
            }
          }
        }
        else {
          if ( (LA(1)==END_IF) ) {
          }
          else {zzFAIL(1,zzerr47,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1137 "f77.g"
    zzmatch(END_IF);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
#line 1138 "f77.g"
      zzastArg(2)->token = BLOCK_IF;
    }
 zzCONSUME;

    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd20, 0x8);
  }
}

void
#ifdef __USE_PROTOS
logical_if_statement(AST**_root)
#else
logical_if_statement(_root)
AST **_root;
#endif
{
#line 1140 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1140 "f77.g"
    int type;
#line 1141 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( 
(LA(1)==LABEL) ) {
#line 1141 "f77.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==IF) ) {
          }
          else {zzFAIL(1,zzerr48,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1141 "f77.g"
    zzmatch(IF);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1141 "f77.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1141 "f77.g"
    zzNON_GUESS_MODE {
       type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
    } else {
      expression(zzSTR);
    }
#line 1141 "f77.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1141 "f77.g"
    executable_statement(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzNON_GUESS_MODE {
#line 1142 "f77.g"
      zzastArg(2)->token = LOGICAL_IF;
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd20, 0x10);
  }
}

void
#ifdef __USE_PROTOS
arithmetic_if_statement(AST**_root)
#else
arithmetic_if_statement(_root)
AST **_root;
#endif
{
#line 1144 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1144 "f77.g"
    int type;
#line 1145 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 1145 "f77.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==IF) ) {
          }
          else {zzFAIL(1,zzerr49,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1145 "f77.g"
    zzmatch(IF);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1145 "f77.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1145 "f77.g"
    zzNON_GUESS_MODE {
       type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
    } else {
      expression(zzSTR);
    }
#line 1145 "f77.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1145 "f77.g"
    label(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1145 "f77.g"
    zzmatch(COMMA);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1145 "f77.g"
    label(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1145 "f77.g"
    zzmatch(COMMA);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1145 "f77.g"
    label(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzNON_GUESS_MODE {
#line 1146 "f77.g"
      zzastArg(2)->token = ARITHMETIC_IF;
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd20, 0x20);
  }
}

void
#ifdef __USE_PROTOS
statement_block(AST**_root)
#else
statement_block(_root)
AST **_root;
#endif
{
#line 1149 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1150 "f77.g"
    {
      zzBLOCK(zztasp2);
      int zzcnt=1;
      zzMake0;
      {
        do {
          if ( (setwd20[LA(1)]&0x40) && 
(setwd20[LA(2)]&0x80) ) {
#line 1150 "f77.g"
            do_statement(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
          }
          else {
            if ( (setwd21[LA(1)]&0x1) && (setwd21[LA(2)]&0x2) ) {
#line 1151 "f77.g"
              if_statement(zzSTR);
              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
              }     /* MR10 */
            }
            else {
              if ( (LA(1)==LABEL) && (LA(2)==FORMAT) ) {
#line 1152 "f77.g"
                format_statement(zzSTR);
                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                }     /* MR10 */
              }
              else {
                if ( (setwd21[LA(1)]&0x4) && (setwd21[LA(2)]&0x8) && !( LA(1)==LABEL && LA(2)==IDENTIFIER) ) {
#line 1153 "f77.g"
                  call_statement(zzSTR);
                  if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                  }     /* MR10 */
                }
                else {
                  if ( (setwd21[LA(1)]&0x10) && (setwd21[LA(2)]&0x20) && !(
 LA(1)==LABEL
   && ( LA(2)==IDENTIFIER || LA(2)==GO_TO || LA(2)==RETURN || LA(2)==READ
      || LA(2)==WRITE || LA(2)==INQUIRE || LA(2)==BACKSPACE || LA(2)==ENDFILE
      || LA(2)==REWIND || LA(2)==OPEN || LA(2)==CLOSE || LA(2)==STOP
      || LA(2)==CHANGE || LA(2)==ASSIGN || LA(2)==FIND)
) ) {
#line 1154 "f77.g"
                    continue_statement(zzSTR);
                    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                    }     /* MR10 */
                  }
                  else {
                    if ( (setwd21[LA(1)]&0x40) && 
(setwd21[LA(2)]&0x80) ) {
#line 1155 "f77.g"
                      assignment_statement(zzSTR);
                      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                      }     /* MR10 */
                    }
                    else {
                      if ( (setwd22[LA(1)]&0x1) && (setwd22[LA(2)]&0x2) ) {
#line 1156 "f77.g"
                        goto_statement(zzSTR);
                        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                        }     /* MR10 */
                      }
                      else {
                        if ( (setwd22[LA(1)]&0x4) && (setwd22[LA(2)]&0x8) && !(
 LA(1)==LABEL
   && ( LA(2)==READ || LA(2)==WRITE || LA(2)==INQUIRE || LA(2)==BACKSPACE
      || LA(2)==ENDFILE || LA(2)==REWIND || LA(2)==OPEN || LA(2)==CLOSE
      || LA(2)==STOP || LA(2)==CHANGE || LA(2)==ASSIGN || LA(2)==FIND)
) ) {
#line 1157 "f77.g"
                          return_statement(zzSTR);
                          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                          }     /* MR10 */
                        }
                        else {
                          if ( (setwd22[LA(1)]&0x10) && (setwd22[LA(2)]&0x20) ) {
#line 1158 "f77.g"
                            read_statement(zzSTR);
                            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                            }     /* MR10 */
                          }
                          else {
                            if ( (setwd22[LA(1)]&0x40) && (setwd22[LA(2)]&0x80) ) {
#line 1159 "f77.g"
                              write_statement(zzSTR);
                              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                              }     /* MR10 */
                            }
                            else {
                              if ( (setwd23[LA(1)]&0x1) && 
(setwd23[LA(2)]&0x2) ) {
#line 1160 "f77.g"
                                inquire_statement(zzSTR);
                                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                }     /* MR10 */
                              }
                              else {
                                if ( (setwd23[LA(1)]&0x4) && (setwd23[LA(2)]&0x8) ) {
#line 1161 "f77.g"
                                  backspace_statement(zzSTR);
                                  if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                  }     /* MR10 */
                                }
                                else {
                                  if ( (setwd23[LA(1)]&0x10) && (setwd23[LA(2)]&0x20) ) {
#line 1162 "f77.g"
                                    endfile_statement(zzSTR);
                                    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                    }     /* MR10 */
                                  }
                                  else {
                                    if ( (setwd23[LA(1)]&0x40) && (setwd23[LA(2)]&0x80) ) {
#line 1163 "f77.g"
                                      rewind_statement(zzSTR);
                                      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                      }     /* MR10 */
                                    }
                                    else {
                                      if ( (setwd24[LA(1)]&0x1) && (setwd24[LA(2)]&0x2) ) {
#line 1164 "f77.g"
                                        open_statement(zzSTR);
                                        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                        }     /* MR10 */
                                      }
                                      else {
                                        if ( (setwd24[LA(1)]&0x4) && 
(setwd24[LA(2)]&0x8) ) {
#line 1165 "f77.g"
                                          close_statement(zzSTR);
                                          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                          }     /* MR10 */
                                        }
                                        else {
                                          if ( (setwd24[LA(1)]&0x10) && (setwd24[LA(2)]&0x20) && !( LA(1)==LABEL && ( LA(2)==CHANGE || LA(2)==ASSIGN || LA(2)==FIND)) ) {
#line 1166 "f77.g"
                                            stop_statement(zzSTR);
                                            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                            }     /* MR10 */
                                          }
                                          else {
                                            if ( (setwd24[LA(1)]&0x40) && (setwd24[LA(2)]&0x80) ) {
#line 1167 "f77.g"
                                              change_statement(zzSTR);
                                              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                              }     /* MR10 */
                                            }
                                            else {
                                              if ( (LA(1)==COMMENT_LINE) ) {
#line 1168 "f77.g"
                                                comment_line(zzSTR);
                                                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                                }     /* MR10 */
                                              }
                                              else {
                                                if ( (LA(1)==BLANK_LINE) ) {
#line 1169 "f77.g"
                                                  blank_line(zzSTR);
                                                  if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                                  }     /* MR10 */
                                                }
                                                else {
                                                  if ( (setwd25[LA(1)]&0x1) && 
(setwd25[LA(2)]&0x2) ) {
#line 1170 "f77.g"
                                                    assign_statement(zzSTR);
                                                    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                                    }     /* MR10 */
                                                  }
                                                  else {
                                                    if ( (setwd25[LA(1)]&0x4) && (setwd25[LA(2)]&0x8) ) {
#line 1171 "f77.g"
                                                      find_statement(zzSTR);
                                                      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                                      }     /* MR10 */
                                                    }
                                                    /* MR10 ()+ */ else {
                                                      if ( zzcnt > 1 ) break;
                                                      else {zzFAIL(2,zzerr50,zzerr51,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
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
          zzcnt++; zzLOOP(zztasp2);
        } while ( 1 );
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd25, 0x10);
  }
}

void
#ifdef __USE_PROTOS
executable_statement(AST**_root)
#else
executable_statement(_root)
AST **_root;
#endif
{
#line 1174 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    if ( (setwd25[LA(1)]&0x20) && (setwd25[LA(2)]&0x40) && !( LA(1)==LABEL && LA(2)==IDENTIFIER) ) {
#line 1175 "f77.g"
      call_statement(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( (setwd25[LA(1)]&0x80) && (setwd26[LA(2)]&0x1) && !(
 LA(1)==LABEL
   && ( LA(2)==IDENTIFIER || LA(2)==GO_TO || LA(2)==RETURN || LA(2)==READ
      || LA(2)==WRITE || LA(2)==INQUIRE || LA(2)==BACKSPACE || LA(2)==ENDFILE
      || LA(2)==REWIND || LA(2)==OPEN || LA(2)==CLOSE || LA(2)==STOP
      || LA(2)==CHANGE || LA(2)==IF || LA(2)==ASSIGN || LA(2)==FIND)
) ) {
#line 1176 "f77.g"
        continue_statement(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {
        if ( (setwd26[LA(1)]&0x2) && (setwd26[LA(2)]&0x4) ) {
#line 1177 "f77.g"
          assignment_statement(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( (setwd26[LA(1)]&0x8) && 
(setwd26[LA(2)]&0x10) ) {
#line 1178 "f77.g"
            goto_statement(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
          }
          else {
            if ( (setwd26[LA(1)]&0x20) && (setwd26[LA(2)]&0x40) && !(
 LA(1)==LABEL
   && ( LA(2)==READ || LA(2)==WRITE || LA(2)==INQUIRE || LA(2)==BACKSPACE
      || LA(2)==ENDFILE || LA(2)==REWIND || LA(2)==OPEN || LA(2)==CLOSE
      || LA(2)==STOP || LA(2)==CHANGE || LA(2)==IF || LA(2)==ASSIGN
      || LA(2)==FIND)
) ) {
#line 1179 "f77.g"
              return_statement(zzSTR);
              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
              }     /* MR10 */
            }
            else {
              if ( (setwd26[LA(1)]&0x80) && (setwd27[LA(2)]&0x1) ) {
#line 1180 "f77.g"
                read_statement(zzSTR);
                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                }     /* MR10 */
              }
              else {
                if ( (setwd27[LA(1)]&0x2) && (setwd27[LA(2)]&0x4) ) {
#line 1181 "f77.g"
                  write_statement(zzSTR);
                  if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                  }     /* MR10 */
                }
                else {
                  if ( (setwd27[LA(1)]&0x8) && (setwd27[LA(2)]&0x10) ) {
#line 1182 "f77.g"
                    inquire_statement(zzSTR);
                    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                    }     /* MR10 */
                  }
                  else {
                    if ( (setwd27[LA(1)]&0x20) && 
(setwd27[LA(2)]&0x40) ) {
#line 1183 "f77.g"
                      backspace_statement(zzSTR);
                      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                      }     /* MR10 */
                    }
                    else {
                      if ( (setwd27[LA(1)]&0x80) && (setwd28[LA(2)]&0x1) ) {
#line 1184 "f77.g"
                        endfile_statement(zzSTR);
                        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                        }     /* MR10 */
                      }
                      else {
                        if ( (setwd28[LA(1)]&0x2) && (setwd28[LA(2)]&0x4) ) {
#line 1185 "f77.g"
                          rewind_statement(zzSTR);
                          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                          }     /* MR10 */
                        }
                        else {
                          if ( (setwd28[LA(1)]&0x8) && (setwd28[LA(2)]&0x10) ) {
#line 1186 "f77.g"
                            open_statement(zzSTR);
                            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                            }     /* MR10 */
                          }
                          else {
                            if ( (setwd28[LA(1)]&0x20) && (setwd28[LA(2)]&0x40) ) {
#line 1187 "f77.g"
                              close_statement(zzSTR);
                              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                              }     /* MR10 */
                            }
                            else {
                              if ( (setwd28[LA(1)]&0x80) && 
(setwd29[LA(2)]&0x1) && !(
 LA(1)==LABEL
   && ( LA(2)==CHANGE || LA(2)==IF || LA(2)==ASSIGN || LA(2)==FIND)
) ) {
#line 1188 "f77.g"
                                stop_statement(zzSTR);
                                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                }     /* MR10 */
                              }
                              else {
                                if ( (setwd29[LA(1)]&0x2) && (setwd29[LA(2)]&0x4) ) {
#line 1189 "f77.g"
                                  change_statement(zzSTR);
                                  if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                  }     /* MR10 */
                                }
                                else {
                                  if ( (setwd29[LA(1)]&0x8) && (setwd29[LA(2)]&0x10) ) {
#line 1190 "f77.g"
                                    arithmetic_if_statement(zzSTR);
                                    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                    }     /* MR10 */
                                  }
                                  else {
                                    if ( (setwd29[LA(1)]&0x20) && (setwd29[LA(2)]&0x40) ) {
#line 1191 "f77.g"
                                      assign_statement(zzSTR);
                                      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                      }     /* MR10 */
                                    }
                                    else {
                                      if ( (setwd29[LA(1)]&0x80) && (setwd30[LA(2)]&0x1) ) {
#line 1192 "f77.g"
                                        find_statement(zzSTR);
                                        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                                        }     /* MR10 */
                                      }
                                      else {zzFAIL(2,zzerr52,zzerr53,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
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
    zzresynch(setwd30, 0x2);
  }
}

void
#ifdef __USE_PROTOS
assignment_statement(AST**_root)
#else
assignment_statement(_root)
AST **_root;
#endif
{
#line 1195 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1196 "f77.g"

    int type;
    printf("Parsing assignment statement. ");
#line 1200 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 1200 "f77.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( 
(LA(1)==IDENTIFIER) ) {
          }
          else {zzFAIL(1,zzerr54,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1200 "f77.g"
    variable(zzSTR, LVALUE );
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1200 "f77.g"
    zzmatch(EQUAL);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1200 "f77.g"
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
    zzresynch(setwd30, 0x4);
  }
}

void
#ifdef __USE_PROTOS
function_call(AST**_root)
#else
function_call(_root)
AST **_root;
#endif
{
#line 1203 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1203 "f77.g"
    zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1203 "f77.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1203 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (setwd30[LA(1)]&0x8) ) {
#line 1203 "f77.g"
          actual_argument_list(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( (LA(1)==RP) ) {
          }
          else {zzFAIL(1,zzerr55,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1203 "f77.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
#line 1204 "f77.g"

      zzastArg(1)->token = FUNCTION_NAME;
    }
 zzCONSUME;

    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd30, 0x10);
  }
}

void
#ifdef __USE_PROTOS
actual_argument_list(AST**_root)
#else
actual_argument_list(_root)
AST **_root;
#endif
{
#line 1208 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1208 "f77.g"
    actual_argument(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1208 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 1208 "f77.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1208 "f77.g"
          actual_argument(zzSTR);
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
    zzresynch(setwd30, 0x20);
  }
}

void
#ifdef __USE_PROTOS
actual_argument(AST**_root)
#else
actual_argument(_root)
AST **_root;
#endif
{
#line 1210 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
#line 1210 "f77.g"
    int type;
    zzGUESS
    if ( !zzrv && (LA(1)==IDENTIFIER) && (setwd30[LA(2)]&0x40) ) {
#line 1211 "f77.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 1211 "f77.g"
          zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1211 "f77.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              if ( (LA(1)==COMMA) ) {
#line 1211 "f77.g"
                zzmatch(COMMA);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
              }
              else {
                if ( (LA(1)==RP) ) {
#line 1211 "f77.g"
                  zzmatch(RP);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
                }
                else {zzFAIL(1,zzerr56,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
              }
              zzEXIT(zztasp3);
            }
          }
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 1211 "f77.g"
      zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      zzGUESS
      if ( !zzrv && (setwd30[LA(1)]&0x80) && 
(setwd31[LA(2)]&0x1) ) {
#line 1212 "f77.g"
        {
          zzBLOCK(zztasp2);
          zzMake0;
          {
#line 1212 "f77.g"
            zzNON_GUESS_MODE {
               type  = constant(zzSTR); zzlink(_root, &_sibling, &_tail);
            } else {
              constant(zzSTR);
            }
#line 1212 "f77.g"
            {
              zzBLOCK(zztasp3);
              zzMake0;
              {
                if ( (LA(1)==COMMA) ) {
#line 1212 "f77.g"
                  zzmatch(COMMA);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
                }
                else {
                  if ( (LA(1)==RP) ) {
#line 1212 "f77.g"
                    zzmatch(RP);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
                  }
                  else {zzFAIL(1,zzerr57,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                }
                zzEXIT(zztasp3);
              }
            }
            zzEXIT(zztasp2);
          }
        }
        zzGUESS_DONE
#line 1212 "f77.g"
        zzNON_GUESS_MODE {
           type  = constant(zzSTR); zzlink(_root, &_sibling, &_tail);
        } else {
          constant(zzSTR);
        }
      }
      else {
        if ( !zzrv ) zzGUESS_DONE;
        zzGUESS
        if ( !zzrv && (LA(1)==IDENTIFIER) && (LA(2)==LP) ) {
#line 1213 "f77.g"
          {
            zzBLOCK(zztasp2);
            zzMake0;
            {
#line 1213 "f77.g"
              function_call(zzSTR);
              if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
              }     /* MR10 */
#line 1213 "f77.g"
              {
                zzBLOCK(zztasp3);
                zzMake0;
                {
                  if ( (LA(1)==COMMA) ) {
#line 1213 "f77.g"
                    zzmatch(COMMA);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                     zzCONSUME;
                  }
                  else {
                    if ( (LA(1)==RP) ) {
#line 1213 "f77.g"
                      zzmatch(RP);zzNON_GUESS_MODE {
                         zzsubchild(_root, &_sibling, &_tail);                      }
                       zzCONSUME;
                    }
                    else {zzFAIL(1,zzerr58,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                  }
                  zzEXIT(zztasp3);
                }
              }
              zzEXIT(zztasp2);
            }
          }
          zzGUESS_DONE
#line 1213 "f77.g"
          function_call(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( !zzrv ) zzGUESS_DONE;
          if ( 
(setwd31[LA(1)]&0x2) && (setwd31[LA(2)]&0x4) ) {
#line 1214 "f77.g"
            zzNON_GUESS_MODE {
               type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
            } else {
              expression(zzSTR);
            }
          }
          else {zzFAIL(2,zzerr59,zzerr60,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd31, 0x8);
  }
}

void
#ifdef __USE_PROTOS
end_statement(AST**_root)
#else
end_statement(_root)
AST **_root;
#endif
{
#line 1217 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1217 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 1217 "f77.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==END) ) {
          }
          else {zzFAIL(1,zzerr61,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1217 "f77.g"
    zzmatch(END);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
#line 1218 "f77.g"

    }
 zzCONSUME;

    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd31, 0x10);
  }
}

void
#ifdef __USE_PROTOS
stop_statement(AST**_root)
#else
stop_statement(_root)
AST **_root;
#endif
{
#line 1221 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1221 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 1221 "f77.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==STOP) ) {
          }
          else {zzFAIL(1,zzerr62,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1221 "f77.g"
    zzmatch(STOP);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
#line 1222 "f77.g"

    }
 zzCONSUME;

    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd31, 0x20);
  }
}

void
#ifdef __USE_PROTOS
return_statement(AST**_root)
#else
return_statement(_root)
AST **_root;
#endif
{
#line 1225 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1225 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( 
(LA(1)==LABEL) ) {
#line 1225 "f77.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==RETURN) ) {
          }
          else {zzFAIL(1,zzerr63,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1225 "f77.g"
    zzmatch(RETURN);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
#line 1226 "f77.g"

    }
 zzCONSUME;

    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd31, 0x40);
  }
}

void
#ifdef __USE_PROTOS
block_globals_statement(AST**_root)
#else
block_globals_statement(_root)
AST **_root;
#endif
{
#line 1229 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1229 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 1229 "f77.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==BLOCK_GLOBALS) ) {
          }
          else {zzFAIL(1,zzerr64,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1229 "f77.g"
    zzmatch(BLOCK_GLOBALS);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd31, 0x80);
  }
}

void
#ifdef __USE_PROTOS
export_statement(AST**_root)
#else
export_statement(_root)
AST **_root;
#endif
{
#line 1231 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1231 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 1231 "f77.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( 
(LA(1)==EXPORT) ) {
          }
          else {zzFAIL(1,zzerr65,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1231 "f77.g"
    zzmatch(EXPORT);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1231 "f77.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1231 "f77.g"
    export_item(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1232 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 1232 "f77.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1232 "f77.g"
          export_item(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
#line 1233 "f77.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd32, 0x1);
  }
}

void
#ifdef __USE_PROTOS
export_item(AST**_root)
#else
export_item(_root)
AST **_root;
#endif
{
#line 1235 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1236 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==DIV) ) {
#line 1236 "f77.g"
          zzmatch(DIV);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1236 "f77.g"
          zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1236 "f77.g"
          zzmatch(DIV);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==IDENTIFIER) ) {
#line 1237 "f77.g"
            zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
          }
          else {
            if ( (LA(1)==CONSTINT) ) {
#line 1238 "f77.g"
              zzmatch(CONSTINT);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
            }
            else {zzFAIL(1,zzerr66,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
          }
        }
        zzEXIT(zztasp2);
      }
    }
#line 1238 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==EQUAL) ) {
#line 1238 "f77.g"
          zzmatch(EQUAL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1238 "f77.g"
          zzmatch(QUOTED_STRING);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( 
(setwd32[LA(1)]&0x2) ) {
          }
          else {zzFAIL(1,zzerr67,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
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
    zzresynch(setwd32, 0x4);
  }
}

void
#ifdef __USE_PROTOS
subroutine_statement(AST**_root)
#else
subroutine_statement(_root)
AST **_root;
#endif
{
#line 1241 "f77.g"
  zzRULE;
  Attrib i;
  AST *i_ast=NULL;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1241 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 1241 "f77.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==SUBROUTINE) ) {
          }
          else {zzFAIL(1,zzerr68,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1241 "f77.g"
    zzmatch(SUBROUTINE);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1241 "f77.g"
    zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
            i = zzaCur;
      i_ast = zzastCur;
    }
     zzCONSUME;
#line 1241 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LP) ) {
#line 1241 "f77.g"
          sub_arg_list(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( (setwd32[LA(1)]&0x8) ) {
          }
          else {zzFAIL(1,zzerr69,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
    zzNON_GUESS_MODE {
#line 1242 "f77.g"

      ChangeType( i.text, FUNCTION_NAME);
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd32, 0x10);
  }
}

void
#ifdef __USE_PROTOS
sub_arg_list(AST**_root)
#else
sub_arg_list(_root)
AST **_root;
#endif
{
#line 1246 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1246 "f77.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1246 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( 
(setwd32[LA(1)]&0x20) ) {
#line 1246 "f77.g"
          sub_argument(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 1246 "f77.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              while ( (LA(1)==COMMA) ) {
#line 1246 "f77.g"
                zzmatch(COMMA);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 1246 "f77.g"
                sub_argument(zzSTR);
                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                }     /* MR10 */
                zzLOOP(zztasp3);
              }
              zzEXIT(zztasp3);
            }
          }
        }
        else {
          if ( (LA(1)==RP) ) {
          }
          else {zzFAIL(1,zzerr70,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1246 "f77.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd32, 0x40);
  }
}

void
#ifdef __USE_PROTOS
sub_argument(AST**_root)
#else
sub_argument(_root)
AST **_root;
#endif
{
#line 1247 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    if ( (LA(1)==IDENTIFIER) ) {
#line 1248 "f77.g"
      formal_argument(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( (LA(1)==STAR) ) {
#line 1249 "f77.g"
        zzmatch(STAR);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
      }
      else {zzFAIL(1,zzerr71,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd32, 0x80);
  }
}

void
#ifdef __USE_PROTOS
formal_argument(AST**_root)
#else
formal_argument(_root)
AST **_root;
#endif
{
#line 1251 "f77.g"
  zzRULE;
  Attrib i;
  AST *i_ast=NULL;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1251 "f77.g"
    int type;
#line 1252 "f77.g"
    zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
            i = zzaCur;
      i_ast = zzastCur;
    }
    
    zzNON_GUESS_MODE {
#line 1253 "f77.g"

      /*I say that it is either INTEGER or REAL and let the rest of code change it if	needed*/
      type = LookUp( i.text);
      if(type == -1) {
        type = ((*( i.text) >= 'I') && (*( i.text) <= 'N'))?INTEGER_ID:REAL_ID;
        AddSymbol( i.text, type);
      }
      zzastArg(1)->token = type;
    }
 zzCONSUME;

    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd33, 0x1);
  }
}

void
#ifdef __USE_PROTOS
function_statement(AST**_root)
#else
function_statement(_root)
AST **_root;
#endif
{
#line 1264 "f77.g"
  zzRULE;
  Attrib i;
  AST *i_ast=NULL;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1264 "f77.g"
    int type = INVALID;
#line 1265 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (setwd33[LA(1)]&0x2) ) {
#line 1265 "f77.g"
          zzNON_GUESS_MODE {
             type  = function_type(zzSTR); zzlink(_root, &_sibling, &_tail);
          } else {
            function_type(zzSTR);
          }
        }
        else {
          if ( 
(LA(1)==FUNCTION) ) {
          }
          else {zzFAIL(1,zzerr72,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1265 "f77.g"
    zzmatch(FUNCTION);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1265 "f77.g"
    zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
            i = zzaCur;
      i_ast = zzastCur;
    }
     zzCONSUME;
#line 1265 "f77.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1265 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (setwd33[LA(1)]&0x4) ) {
#line 1265 "f77.g"
          function_arg_list(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( (LA(1)==RP) ) {
          }
          else {zzFAIL(1,zzerr73,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1265 "f77.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
#line 1266 "f77.g"

      if(type == INVALID) {
        type = ((*( i.text) >= 'I') && (*( i.text) <= 'N'))?INTEGER_ID:REAL_ID;
      }
      ChangeType( i.text, type);
    }
 zzCONSUME;

    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd33, 0x8);
  }
}

int
#ifdef __USE_PROTOS
function_type(AST**_root)
#else
function_type(_root)
AST **_root;
#endif
{
  int   _retv;
#line 1274 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  PCCTS_PURIFY(_retv,sizeof(int  ))
  zzMake0;
  {
#line 1276 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==INTEGER) ) {
#line 1276 "f77.g"
          zzmatch(INTEGER);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
          
          zzNON_GUESS_MODE {
#line 1276 "f77.g"
            _retv = INTEGER_ID;
          }
 zzCONSUME;

        }
        else {
          if ( (LA(1)==REAL) ) {
#line 1277 "f77.g"
            zzmatch(REAL);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
            
            zzNON_GUESS_MODE {
#line 1277 "f77.g"
              _retv = REAL_ID;
            }
 zzCONSUME;

          }
          else {
            if ( 
(LA(1)==DOUBLE_PRECISION) ) {
#line 1278 "f77.g"
              zzmatch(DOUBLE_PRECISION);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
              
              zzNON_GUESS_MODE {
#line 1278 "f77.g"
                _retv = DOUBLE_PRECISION_ID;
              }
 zzCONSUME;

            }
            else {
              if ( (LA(1)==LOGICAL) ) {
#line 1279 "f77.g"
                zzmatch(LOGICAL);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                
                zzNON_GUESS_MODE {
#line 1279 "f77.g"
                  _retv = LOGICAL_ID;
                }
 zzCONSUME;

              }
              else {
                if ( (LA(1)==CHARACTER) ) {
#line 1280 "f77.g"
                  zzmatch(CHARACTER);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                  
                  zzNON_GUESS_MODE {
#line 1280 "f77.g"
                    _retv = CHARACTER_ID;
                  }
 zzCONSUME;

                }
                else {
                  if ( (LA(1)==COMPLEX) ) {
#line 1281 "f77.g"
                    zzmatch(COMPLEX);zzNON_GUESS_MODE {
                       zzsubchild(_root, &_sibling, &_tail);                    }
                    
                    zzNON_GUESS_MODE {
#line 1281 "f77.g"
                      _retv = COMPLEX_ID;
                    }
 zzCONSUME;

                  }
                  else {
                    if ( (LA(1)==DOUBLE_COMPLEX) ) {
#line 1282 "f77.g"
                      zzmatch(DOUBLE_COMPLEX);zzNON_GUESS_MODE {
                         zzsubchild(_root, &_sibling, &_tail);                      }
                      
                      zzNON_GUESS_MODE {
#line 1282 "f77.g"
                        _retv = DOUBLE_COMPLEX_ID;
                      }
 zzCONSUME;

                    }
                    else {zzFAIL(1,zzerr74,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                  }
                }
              }
            }
          }
        }
        zzEXIT(zztasp2);
      }
    }
#line 1284 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( 
(LA(1)==STAR) ) {
#line 1284 "f77.g"
          zzmatch(STAR);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1284 "f77.g"
          length_spec(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( (LA(1)==FUNCTION) ) {
          }
          else {zzFAIL(1,zzerr75,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
    zzEXIT(zztasp1);
    return _retv;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd33, 0x10);
    return _retv;
  }
}

void
#ifdef __USE_PROTOS
function_arg_list(AST**_root)
#else
function_arg_list(_root)
AST **_root;
#endif
{
#line 1286 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1286 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==DIV) ) {
#line 1286 "f77.g"
          zzmatch(DIV);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
          
          zzNON_GUESS_MODE {
#line 1286 "f77.g"
            zzastArg(1)->token = SLASH;
          }
 zzCONSUME;

        }
        else {
          if ( (LA(1)==IDENTIFIER) ) {
          }
          else {zzFAIL(1,zzerr76,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1286 "f77.g"
    formal_argument(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1286 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==DIV) ) {
#line 1286 "f77.g"
          zzmatch(DIV);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
          
          zzNON_GUESS_MODE {
#line 1286 "f77.g"
            zzastArg(1)->token = SLASH;
          }
 zzCONSUME;

        }
        else {
          if ( 
(setwd33[LA(1)]&0x20) ) {
          }
          else {zzFAIL(1,zzerr77,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1287 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 1287 "f77.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1287 "f77.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              if ( (LA(1)==DIV) ) {
#line 1287 "f77.g"
                zzmatch(DIV);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                
                zzNON_GUESS_MODE {
#line 1287 "f77.g"
                  zzastArg(1)->token = SLASH;
                }
 zzCONSUME;

              }
              else {
                if ( (LA(1)==IDENTIFIER) ) {
                }
                else {zzFAIL(1,zzerr78,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
              }
              zzEXIT(zztasp3);
            }
          }
#line 1287 "f77.g"
          formal_argument(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 1287 "f77.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              if ( (LA(1)==DIV) ) {
#line 1287 "f77.g"
                zzmatch(DIV);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                
                zzNON_GUESS_MODE {
#line 1287 "f77.g"
                  zzastArg(1)->token = SLASH;
                }
 zzCONSUME;

              }
              else {
                if ( (setwd33[LA(1)]&0x40) ) {
                }
                else {zzFAIL(1,zzerr79,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
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
    zzresynch(setwd33, 0x80);
  }
}

void
#ifdef __USE_PROTOS
entry_statement(AST**_root)
#else
entry_statement(_root)
AST **_root;
#endif
{
#line 1290 "f77.g"
  zzRULE;
  Attrib i;
  AST *i_ast=NULL;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1290 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( 
(LA(1)==LABEL) ) {
#line 1290 "f77.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==ENTRY) ) {
          }
          else {zzFAIL(1,zzerr80,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1290 "f77.g"
    zzmatch(ENTRY);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1290 "f77.g"
    zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
            i = zzaCur;
      i_ast = zzastCur;
    }
     zzCONSUME;
#line 1290 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LP) ) {
#line 1290 "f77.g"
          sub_arg_list(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( (setwd34[LA(1)]&0x1) ) {
          }
          else {zzFAIL(1,zzerr81,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
    zzNON_GUESS_MODE {
#line 1291 "f77.g"

      ChangeType( i.text, FUNCTION_NAME);
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd34, 0x2);
  }
}

void
#ifdef __USE_PROTOS
goto_statement(AST**_root)
#else
goto_statement(_root)
AST **_root;
#endif
{
#line 1296 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (setwd34[LA(1)]&0x4) && 
(setwd34[LA(2)]&0x8) ) {
#line 1296 "f77.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 1296 "f77.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              if ( (LA(1)==LABEL) ) {
#line 1296 "f77.g"
                zzmatch(LABEL);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
              }
              else {
                if ( (LA(1)==GO_TO) ) {
                }
                else {zzFAIL(1,zzerr82,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
              }
              zzEXIT(zztasp3);
            }
          }
#line 1296 "f77.g"
          zzmatch(GO_TO);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1296 "f77.g"
          label(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 1296 "f77.g"
      unconditional_goto_statement(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      zzGUESS
      if ( !zzrv && (setwd34[LA(1)]&0x10) && (setwd34[LA(2)]&0x20) ) {
#line 1297 "f77.g"
        {
          zzBLOCK(zztasp2);
          zzMake0;
          {
#line 1297 "f77.g"
            {
              zzBLOCK(zztasp3);
              zzMake0;
              {
                if ( (LA(1)==LABEL) ) {
#line 1297 "f77.g"
                  zzmatch(LABEL);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
                }
                else {
                  if ( (LA(1)==GO_TO) ) {
                  }
                  else {zzFAIL(1,zzerr83,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
                }
                zzEXIT(zztasp3);
              }
            }
#line 1297 "f77.g"
            zzmatch(GO_TO);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 1297 "f77.g"
            zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
            zzEXIT(zztasp2);
          }
        }
        zzGUESS_DONE
#line 1297 "f77.g"
        assigned_goto_statement(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {
        if ( !zzrv ) zzGUESS_DONE;
        if ( 
(setwd34[LA(1)]&0x40) && (setwd34[LA(2)]&0x80) ) {
#line 1298 "f77.g"
          computed_goto_statement(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {zzFAIL(2,zzerr84,zzerr85,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd35, 0x1);
  }
}

void
#ifdef __USE_PROTOS
unconditional_goto_statement(AST**_root)
#else
unconditional_goto_statement(_root)
AST **_root;
#endif
{
#line 1301 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1301 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 1301 "f77.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==GO_TO) ) {
          }
          else {zzFAIL(1,zzerr86,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1301 "f77.g"
    zzmatch(GO_TO);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1301 "f77.g"
    label(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzNON_GUESS_MODE {
#line 1302 "f77.g"
      zzastArg(2)->token = UNCONDITIONAL_GOTO;
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd35, 0x2);
  }
}

void
#ifdef __USE_PROTOS
computed_goto_statement(AST**_root)
#else
computed_goto_statement(_root)
AST **_root;
#endif
{
#line 1304 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1304 "f77.g"
    int type;
#line 1305 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 1305 "f77.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==GO_TO) ) {
          }
          else {zzFAIL(1,zzerr87,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1305 "f77.g"
    zzmatch(GO_TO);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1305 "f77.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1305 "f77.g"
    label(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1305 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        while ( (LA(1)==COMMA) ) {
#line 1305 "f77.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1305 "f77.g"
          label(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzLOOP(zztasp2);
        }
        zzEXIT(zztasp2);
      }
    }
#line 1305 "f77.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1305 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==COMMA) ) {
#line 1305 "f77.g"
          zzmatch(COMMA);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (setwd35[LA(1)]&0x4) ) {
          }
          else {zzFAIL(1,zzerr88,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1305 "f77.g"
    zzNON_GUESS_MODE {
       type  = expression(zzSTR); zzlink(_root, &_sibling, &_tail);
    } else {
      expression(zzSTR);
    }
    zzNON_GUESS_MODE {
#line 1306 "f77.g"
      zzastArg(2)->token = COMPUTED_GOTO;
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd35, 0x8);
  }
}

void
#ifdef __USE_PROTOS
assigned_goto_statement(AST**_root)
#else
assigned_goto_statement(_root)
AST **_root;
#endif
{
#line 1308 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1308 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 1308 "f77.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==GO_TO) ) {
          }
          else {zzFAIL(1,zzerr89,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1308 "f77.g"
    zzmatch(GO_TO);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1308 "f77.g"
    zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1309 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( 
(setwd35[LA(1)]&0x10) ) {
#line 1309 "f77.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              if ( (LA(1)==COMMA) ) {
#line 1309 "f77.g"
                zzmatch(COMMA);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
              }
              else {
                if ( (LA(1)==LP) ) {
                }
                else {zzFAIL(1,zzerr90,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
              }
              zzEXIT(zztasp3);
            }
          }
#line 1309 "f77.g"
          zzmatch(LP);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1309 "f77.g"
          label(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 1309 "f77.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              while ( (LA(1)==COMMA) ) {
#line 1309 "f77.g"
                zzmatch(COMMA);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
#line 1309 "f77.g"
                label(zzSTR);
                if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
                }     /* MR10 */
                zzLOOP(zztasp3);
              }
              zzEXIT(zztasp3);
            }
          }
#line 1309 "f77.g"
          zzmatch(RP);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (setwd35[LA(1)]&0x20) ) {
          }
          else {zzFAIL(1,zzerr91,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
    zzNON_GUESS_MODE {
#line 1310 "f77.g"

      zzastArg(2)->token = ASSIGNED_GOTO;
      zzastArg(3)->token = INTEGER_ID;
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd35, 0x40);
  }
}

void
#ifdef __USE_PROTOS
library_statement(AST**_root)
#else
library_statement(_root)
AST **_root;
#endif
{
#line 1316 "f77.g"
  zzRULE;
  Attrib i;
  AST *i_ast=NULL;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1316 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==LABEL) ) {
#line 1316 "f77.g"
          zzmatch(LABEL);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==LIBRARY) ) {
          }
          else {zzFAIL(1,zzerr92,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1316 "f77.g"
    zzmatch(LIBRARY);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1316 "f77.g"
    zzmatch(IDENTIFIER);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
            i = zzaCur;
      i_ast = zzastCur;
    }
     zzCONSUME;
#line 1316 "f77.g"
    zzmatch(LP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1316 "f77.g"
    zzmatch(TITLE);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1316 "f77.g"
    zzmatch(EQUAL);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1316 "f77.g"
    zzmatch(QUOTED_STRING);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1316 "f77.g"
    zzmatch(RP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd35, 0x80);
  }
}

void
#ifdef __USE_PROTOS
label(AST**_root)
#else
label(_root)
AST **_root;
#endif
{
#line 1321 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1321 "f77.g"
    zzmatch(CONSTINT);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd36, 0x1);
  }
}

void
#ifdef __USE_PROTOS
repeat_count(AST**_root)
#else
repeat_count(_root)
AST **_root;
#endif
{
#line 1323 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1323 "f77.g"
    zzmatch(CONSTINT);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
#line 1323 "f77.g"
      zzastArg(1)->token = REPEAT_COUNT;
    }
 zzCONSUME;

    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd36, 0x2);
  }
}

void
#ifdef __USE_PROTOS
arithm_operator(AST**_root)
#else
arithm_operator(_root)
AST **_root;
#endif
{
#line 1325 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    if ( (LA(1)==POW) ) {
#line 1325 "f77.g"
      zzmatch(POW);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
    }
    else {
      if ( 
(LA(1)==PLU) ) {
#line 1325 "f77.g"
        zzmatch(PLU);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
      }
      else {
        if ( (LA(1)==MIN) ) {
#line 1325 "f77.g"
          zzmatch(MIN);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==STAR) ) {
#line 1325 "f77.g"
            zzmatch(STAR);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
          }
          else {
            if ( (LA(1)==DIV) ) {
#line 1325 "f77.g"
              zzmatch(DIV);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
            }
            else {zzFAIL(1,zzerr93,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
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
    zzresynch(setwd36, 0x4);
  }
}

void
#ifdef __USE_PROTOS
logical_operator(AST**_root)
#else
logical_operator(_root)
AST **_root;
#endif
{
#line 1326 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    if ( (LA(1)==AND) ) {
#line 1326 "f77.g"
      zzmatch(AND);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
    }
    else {
      if ( 
(LA(1)==OR) ) {
#line 1326 "f77.g"
        zzmatch(OR);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
      }
      else {
        if ( (LA(1)==NEQV) ) {
#line 1326 "f77.g"
          zzmatch(NEQV);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==EQV) ) {
#line 1326 "f77.g"
            zzmatch(EQV);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
          }
          else {zzFAIL(1,zzerr94,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd36, 0x8);
  }
}

void
#ifdef __USE_PROTOS
relational_operator(AST**_root)
#else
relational_operator(_root)
AST **_root;
#endif
{
#line 1327 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    if ( (LA(1)==LT) ) {
#line 1327 "f77.g"
      zzmatch(LT);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
    }
    else {
      if ( (LA(1)==LE) ) {
#line 1327 "f77.g"
        zzmatch(LE);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
      }
      else {
        if ( 
(LA(1)==EQ) ) {
#line 1327 "f77.g"
          zzmatch(EQ);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {
          if ( (LA(1)==NE) ) {
#line 1327 "f77.g"
            zzmatch(NE);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
          }
          else {
            if ( (LA(1)==GT) ) {
#line 1327 "f77.g"
              zzmatch(GT);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
               zzCONSUME;
            }
            else {
              if ( (LA(1)==GE) ) {
#line 1327 "f77.g"
                zzmatch(GE);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
              }
              else {
                if ( (LA(1)==IS) ) {
#line 1327 "f77.g"
                  zzmatch(IS);zzNON_GUESS_MODE {
                     zzsubchild(_root, &_sibling, &_tail);                  }
                   zzCONSUME;
                }
                else {zzFAIL(1,zzerr95,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
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
    zzresynch(setwd36, 0x10);
  }
}

int
#ifdef __USE_PROTOS
constant(AST**_root)
#else
constant(_root)
AST **_root;
#endif
{
  int   _retv;
#line 1329 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  PCCTS_PURIFY(_retv,sizeof(int  ))
  zzMake0;
  {
    if ( 
(setwd36[LA(1)]&0x20) ) {
#line 1330 "f77.g"
      int_const(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
      zzNON_GUESS_MODE {
#line 1330 "f77.g"
        _retv = INTEGER_ID;
      }
    }
    else {
      if ( (setwd36[LA(1)]&0x40) ) {
#line 1331 "f77.g"
        real_const(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
        zzNON_GUESS_MODE {
#line 1331 "f77.g"
          _retv = REAL_ID;
        }
      }
      else {
        if ( (setwd36[LA(1)]&0x80) ) {
#line 1332 "f77.g"
          logical_const(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzNON_GUESS_MODE {
#line 1332 "f77.g"
            _retv = LOGICAL_ID;
          }
        }
        else {
          if ( (setwd37[LA(1)]&0x1) ) {
#line 1333 "f77.g"
            char_const(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
            zzNON_GUESS_MODE {
#line 1333 "f77.g"
              _retv = CHARACTER_ID;
            }
          }
          else {zzFAIL(1,zzerr96,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
      }
    }
    zzEXIT(zztasp1);
    return _retv;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd37, 0x2);
    return _retv;
  }
}

void
#ifdef __USE_PROTOS
arithm_const(AST**_root)
#else
arithm_const(_root)
AST **_root;
#endif
{
#line 1336 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    if ( (setwd37[LA(1)]&0x4) ) {
#line 1336 "f77.g"
      int_const(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( 
(setwd37[LA(1)]&0x8) ) {
#line 1336 "f77.g"
        real_const(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {zzFAIL(1,zzerr97,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd37, 0x10);
  }
}

void
#ifdef __USE_PROTOS
real_const(AST**_root)
#else
real_const(_root)
AST **_root;
#endif
{
#line 1337 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    if ( (LA(1)==BASIC_REAL) ) {
#line 1337 "f77.g"
      zzmatch(BASIC_REAL);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
    }
    else {
      if ( (LA(1)==REAL_EXPO) ) {
#line 1337 "f77.g"
        zzmatch(REAL_EXPO);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
      }
      else {zzFAIL(1,zzerr98,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd37, 0x20);
  }
}

void
#ifdef __USE_PROTOS
int_const(AST**_root)
#else
int_const(_root)
AST **_root;
#endif
{
#line 1338 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    if ( (LA(1)==CONSTINT) ) {
#line 1338 "f77.g"
      zzmatch(CONSTINT);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
    }
    else {
      if ( (LA(1)==HEX_CONST) ) {
#line 1338 "f77.g"
        zzmatch(HEX_CONST);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
      }
      else {zzFAIL(1,zzerr99,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd37, 0x40);
  }
}

void
#ifdef __USE_PROTOS
logical_const(AST**_root)
#else
logical_const(_root)
AST **_root;
#endif
{
#line 1339 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    if ( 
(LA(1)==T_TRUE) ) {
#line 1339 "f77.g"
      zzmatch(T_TRUE);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
    }
    else {
      if ( (LA(1)==T_FALSE) ) {
#line 1339 "f77.g"
        zzmatch(T_FALSE);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
      }
      else {zzFAIL(1,zzerr100,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd37, 0x80);
  }
}

void
#ifdef __USE_PROTOS
char_const(AST**_root)
#else
char_const(_root)
AST **_root;
#endif
{
#line 1340 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    if ( (LA(1)==HOLLERITH_CONST) ) {
#line 1340 "f77.g"
      zzmatch(HOLLERITH_CONST);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
    }
    else {
      if ( (LA(1)==QUOTED_STRING) ) {
#line 1340 "f77.g"
        zzmatch(QUOTED_STRING);zzNON_GUESS_MODE {
           zzsubchild(_root, &_sibling, &_tail);        }
         zzCONSUME;
      }
      else {zzFAIL(1,zzerr101,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd38, 0x1);
  }
}

void
#ifdef __USE_PROTOS
hollerith_editing(AST**_root)
#else
hollerith_editing(_root)
AST **_root;
#endif
{
#line 1420 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1420 "f77.g"
    zzmatch(HOLLERITH_CONST);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd38, 0x2);
  }
}

void
#ifdef __USE_PROTOS
quote_editinig(AST**_root)
#else
quote_editinig(_root)
AST **_root;
#endif
{
#line 1421 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1421 "f77.g"
    zzmatch(QUOTED_STRING);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd38, 0x4);
  }
}

void
#ifdef __USE_PROTOS
tr_editing(AST**_root)
#else
tr_editing(_root)
AST **_root;
#endif
{
#line 1422 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1422 "f77.g"
    zzmatch(TR);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1422 "f77.g"
    zzmatch(CONSTINT);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd38, 0x8);
  }
}

void
#ifdef __USE_PROTOS
tl_editing(AST**_root)
#else
tl_editing(_root)
AST **_root;
#endif
{
#line 1423 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1423 "f77.g"
    zzmatch(TL);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1423 "f77.g"
    zzmatch(CONSTINT);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd38, 0x10);
  }
}

void
#ifdef __USE_PROTOS
t_editing(AST**_root)
#else
t_editing(_root)
AST **_root;
#endif
{
#line 1424 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1424 "f77.g"
    zzmatch(T);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1424 "f77.g"
    zzmatch(CONSTINT);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd38, 0x20);
  }
}

void
#ifdef __USE_PROTOS
x_editing(AST**_root)
#else
x_editing(_root)
AST **_root;
#endif
{
#line 1425 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1425 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==CONSTINT) ) {
#line 1425 "f77.g"
          zzmatch(CONSTINT);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
          
          zzNON_GUESS_MODE {
#line 1425 "f77.g"
            zzastArg(1)->token = REPEAT_COUNT;
          }
 zzCONSUME;

        }
        else {
          if ( 
(LA(1)==X) ) {
          }
          else {zzFAIL(1,zzerr102,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1425 "f77.g"
    zzmatch(X);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd38, 0x40);
  }
}

void
#ifdef __USE_PROTOS
colon_editing(AST**_root)
#else
colon_editing(_root)
AST **_root;
#endif
{
#line 1426 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1426 "f77.g"
    zzmatch(COLUMN);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd38, 0x80);
  }
}

void
#ifdef __USE_PROTOS
sp_editing(AST**_root)
#else
sp_editing(_root)
AST **_root;
#endif
{
#line 1427 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1427 "f77.g"
    zzmatch(SP);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd39, 0x1);
  }
}

void
#ifdef __USE_PROTOS
ss_editing(AST**_root)
#else
ss_editing(_root)
AST **_root;
#endif
{
#line 1428 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1428 "f77.g"
    zzmatch(SS);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd39, 0x2);
  }
}

void
#ifdef __USE_PROTOS
s_editing(AST**_root)
#else
s_editing(_root)
AST **_root;
#endif
{
#line 1429 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1429 "f77.g"
    zzmatch(S);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd39, 0x4);
  }
}

void
#ifdef __USE_PROTOS
p_editing(AST**_root)
#else
p_editing(_root)
AST **_root;
#endif
{
#line 1430 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1430 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==CONSTINT) ) {
#line 1430 "f77.g"
          zzmatch(CONSTINT);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
          
          zzNON_GUESS_MODE {
#line 1430 "f77.g"
            zzastArg(1)->token = SCALE_FACTOR;
          }
 zzCONSUME;

        }
        else {
          if ( (LA(1)==P) ) {
          }
          else {zzFAIL(1,zzerr103,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1430 "f77.g"
    zzmatch(P);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd39, 0x8);
  }
}

void
#ifdef __USE_PROTOS
bn_editing(AST**_root)
#else
bn_editing(_root)
AST **_root;
#endif
{
#line 1431 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1431 "f77.g"
    zzmatch(BN);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd39, 0x10);
  }
}

void
#ifdef __USE_PROTOS
bz_editing(AST**_root)
#else
bz_editing(_root)
AST **_root;
#endif
{
#line 1432 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1432 "f77.g"
    zzmatch(BZ);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd39, 0x20);
  }
}

void
#ifdef __USE_PROTOS
i_editing(AST**_root)
#else
i_editing(_root)
AST **_root;
#endif
{
#line 1434 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1434 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==CONSTINT) ) {
#line 1434 "f77.g"
          zzmatch(CONSTINT);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
          
          zzNON_GUESS_MODE {
#line 1434 "f77.g"
            zzastArg(1)->token = REPEAT_COUNT;
          }
 zzCONSUME;

        }
        else {
          if ( (LA(1)==I) ) {
          }
          else {zzFAIL(1,zzerr104,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1434 "f77.g"
    zzmatch(I);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1434 "f77.g"
    field_width(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1434 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( 
(LA(1)==DEC_POINT) ) {
#line 1434 "f77.g"
          zzmatch(DEC_POINT);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1434 "f77.g"
          min_dig_required(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
        }
        else {
          if ( (setwd39[LA(1)]&0x40) ) {
          }
          else {zzFAIL(1,zzerr105,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
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
    zzresynch(setwd39, 0x80);
  }
}

void
#ifdef __USE_PROTOS
j_editing(AST**_root)
#else
j_editing(_root)
AST **_root;
#endif
{
#line 1435 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1435 "f77.g"
    zzmatch(J);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1435 "f77.g"
    field_width(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd40, 0x1);
  }
}

void
#ifdef __USE_PROTOS
f_editing(AST**_root)
#else
f_editing(_root)
AST **_root;
#endif
{
#line 1436 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1436 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==CONSTINT) ) {
#line 1436 "f77.g"
          zzmatch(CONSTINT);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
          
          zzNON_GUESS_MODE {
#line 1436 "f77.g"
            zzastArg(1)->token = REPEAT_COUNT;
          }
 zzCONSUME;

        }
        else {
          if ( (LA(1)==F) ) {
          }
          else {zzFAIL(1,zzerr106,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1436 "f77.g"
    zzmatch(F);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1436 "f77.g"
    field_width(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1436 "f77.g"
    zzmatch(DEC_POINT);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1436 "f77.g"
    decimal_places(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd40, 0x2);
  }
}

void
#ifdef __USE_PROTOS
e_editing(AST**_root)
#else
e_editing(_root)
AST **_root;
#endif
{
#line 1438 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (setwd40[LA(1)]&0x4) && 
(setwd40[LA(2)]&0x8) ) {
#line 1438 "f77.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 1438 "f77.g"
          short_e_editing(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 1438 "f77.g"
          zzmatch(E);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 1438 "f77.g"
      short_e_editing(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
#line 1438 "f77.g"
      zzmatch(E);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 1438 "f77.g"
      exponent_digits(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (setwd40[LA(1)]&0x10) && (setwd40[LA(2)]&0x20) ) {
#line 1439 "f77.g"
        short_e_editing(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {zzFAIL(2,zzerr107,zzerr108,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd40, 0x40);
  }
}

void
#ifdef __USE_PROTOS
short_e_editing(AST**_root)
#else
short_e_editing(_root)
AST **_root;
#endif
{
#line 1440 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1440 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==CONSTINT) ) {
#line 1440 "f77.g"
          zzmatch(CONSTINT);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
          
          zzNON_GUESS_MODE {
#line 1440 "f77.g"
            zzastArg(1)->token = REPEAT_COUNT;
          }
 zzCONSUME;

        }
        else {
          if ( (LA(1)==E) ) {
          }
          else {zzFAIL(1,zzerr109,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1440 "f77.g"
    zzmatch(E);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1440 "f77.g"
    field_width(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1440 "f77.g"
    zzmatch(DEC_POINT);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1440 "f77.g"
    decimal_places(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd40, 0x80);
  }
}

void
#ifdef __USE_PROTOS
d_editing(AST**_root)
#else
d_editing(_root)
AST **_root;
#endif
{
#line 1441 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1441 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==CONSTINT) ) {
#line 1441 "f77.g"
          zzmatch(CONSTINT);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
          
          zzNON_GUESS_MODE {
#line 1441 "f77.g"
            zzastArg(1)->token = REPEAT_COUNT;
          }
 zzCONSUME;

        }
        else {
          if ( (LA(1)==D) ) {
          }
          else {zzFAIL(1,zzerr110,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1441 "f77.g"
    zzmatch(D);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1441 "f77.g"
    field_width(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1441 "f77.g"
    zzmatch(DEC_POINT);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1441 "f77.g"
    decimal_places(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd41, 0x1);
  }
}

void
#ifdef __USE_PROTOS
g_editing(AST**_root)
#else
g_editing(_root)
AST **_root;
#endif
{
#line 1442 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && 
(setwd41[LA(1)]&0x2) && (setwd41[LA(2)]&0x4) ) {
#line 1442 "f77.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 1442 "f77.g"
          short_g_editing(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 1442 "f77.g"
          zzmatch(G);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 1442 "f77.g"
      short_g_editing(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
#line 1442 "f77.g"
      zzmatch(G);zzNON_GUESS_MODE {
         zzsubroot(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 1442 "f77.g"
      exponent_digits(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (setwd41[LA(1)]&0x8) && (setwd41[LA(2)]&0x10) ) {
#line 1443 "f77.g"
        short_g_editing(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {zzFAIL(2,zzerr111,zzerr112,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd41, 0x20);
  }
}

void
#ifdef __USE_PROTOS
short_g_editing(AST**_root)
#else
short_g_editing(_root)
AST **_root;
#endif
{
#line 1444 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1444 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==CONSTINT) ) {
#line 1444 "f77.g"
          zzmatch(CONSTINT);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
          
          zzNON_GUESS_MODE {
#line 1444 "f77.g"
            zzastArg(1)->token = REPEAT_COUNT;
          }
 zzCONSUME;

        }
        else {
          if ( (LA(1)==G) ) {
          }
          else {zzFAIL(1,zzerr113,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1444 "f77.g"
    zzmatch(G);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1444 "f77.g"
    field_width(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
#line 1444 "f77.g"
    zzmatch(DEC_POINT);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1444 "f77.g"
    decimal_places(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd41, 0x40);
  }
}

void
#ifdef __USE_PROTOS
o_editing(AST**_root)
#else
o_editing(_root)
AST **_root;
#endif
{
#line 1445 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1445 "f77.g"
    zzmatch(O);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1445 "f77.g"
    field_width(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd41, 0x80);
  }
}

void
#ifdef __USE_PROTOS
l_editing(AST**_root)
#else
l_editing(_root)
AST **_root;
#endif
{
#line 1446 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1446 "f77.g"
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
        if ( (LA(1)==CONSTINT) ) {
#line 1446 "f77.g"
          zzmatch(CONSTINT);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
          
          zzNON_GUESS_MODE {
#line 1446 "f77.g"
            zzastArg(1)->token = REPEAT_COUNT;
          }
 zzCONSUME;

        }
        else {
          if ( 
(LA(1)==L) ) {
          }
          else {zzFAIL(1,zzerr114,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
        zzEXIT(zztasp2);
      }
    }
#line 1446 "f77.g"
    zzmatch(L);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1446 "f77.g"
    field_width(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd42, 0x1);
  }
}

void
#ifdef __USE_PROTOS
a_editing(AST**_root)
#else
a_editing(_root)
AST **_root;
#endif
{
#line 1447 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (setwd42[LA(1)]&0x2) && (setwd42[LA(2)]&0x4) ) {
#line 1447 "f77.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 1447 "f77.g"
          {
            zzBLOCK(zztasp3);
            zzMake0;
            {
              if ( (LA(1)==CONSTINT) ) {
#line 1447 "f77.g"
                zzmatch(CONSTINT);zzNON_GUESS_MODE {
                   zzsubchild(_root, &_sibling, &_tail);                }
                 zzCONSUME;
              }
              else {
                if ( (LA(1)==A) ) {
                }
                else {zzFAIL(1,zzerr115,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
              }
              zzEXIT(zztasp3);
            }
          }
#line 1447 "f77.g"
          zzmatch(A);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1447 "f77.g"
          field_width(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 1447 "f77.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
          if ( (LA(1)==CONSTINT) ) {
#line 1447 "f77.g"
            zzmatch(CONSTINT);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
            
            zzNON_GUESS_MODE {
#line 1447 "f77.g"
              zzastArg(1)->token = REPEAT_COUNT;
            }
 zzCONSUME;

          }
          else {
            if ( 
(LA(1)==A) ) {
            }
            else {zzFAIL(1,zzerr116,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
          }
          zzEXIT(zztasp2);
        }
      }
#line 1447 "f77.g"
      zzmatch(A);zzNON_GUESS_MODE {
         zzsubroot(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 1447 "f77.g"
      field_width(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      if ( (setwd42[LA(1)]&0x8) && (setwd42[LA(2)]&0x10) ) {
#line 1448 "f77.g"
        {
          zzBLOCK(zztasp2);
          zzMake0;
          {
            if ( (LA(1)==CONSTINT) ) {
#line 1448 "f77.g"
              zzmatch(CONSTINT);zzNON_GUESS_MODE {
                 zzsubchild(_root, &_sibling, &_tail);              }
              
              zzNON_GUESS_MODE {
#line 1448 "f77.g"
                zzastArg(1)->token = REPEAT_COUNT;
              }
 zzCONSUME;

            }
            else {
              if ( (LA(1)==A) ) {
              }
              else {zzFAIL(1,zzerr117,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
            }
            zzEXIT(zztasp2);
          }
        }
#line 1448 "f77.g"
        zzmatch(A);zzNON_GUESS_MODE {
           zzsubroot(_root, &_sibling, &_tail);        }
         zzCONSUME;
      }
      else {zzFAIL(2,zzerr118,zzerr119,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd42, 0x20);
  }
}

void
#ifdef __USE_PROTOS
z_editing(AST**_root)
#else
z_editing(_root)
AST **_root;
#endif
{
#line 1449 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1449 "f77.g"
    zzmatch(Z);zzNON_GUESS_MODE {
       zzsubroot(_root, &_sibling, &_tail);    }
     zzCONSUME;
#line 1449 "f77.g"
    field_width(zzSTR);
    if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
    }     /* MR10 */
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd42, 0x40);
  }
}

void
#ifdef __USE_PROTOS
u_editing(AST**_root)
#else
u_editing(_root)
AST **_root;
#endif
{
#line 1451 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
    zzGUESS_BLOCK
    zzGUESS
    if ( !zzrv && (LA(1)==U) && 
(LA(2)==CONSTINT) ) {
#line 1451 "f77.g"
      {
        zzBLOCK(zztasp2);
        zzMake0;
        {
#line 1451 "f77.g"
          zzmatch(U);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
#line 1451 "f77.g"
          field_width(zzSTR);
          if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
          }     /* MR10 */
#line 1451 "f77.g"
          zzmatch(DEC_POINT);zzNON_GUESS_MODE {
             zzsubchild(_root, &_sibling, &_tail);          }
           zzCONSUME;
          zzEXIT(zztasp2);
        }
      }
      zzGUESS_DONE
#line 1451 "f77.g"
      zzmatch(U);zzNON_GUESS_MODE {
         zzsubroot(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 1451 "f77.g"
      field_width(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
#line 1451 "f77.g"
      zzmatch(DEC_POINT);zzNON_GUESS_MODE {
         zzsubchild(_root, &_sibling, &_tail);      }
       zzCONSUME;
#line 1451 "f77.g"
      decimal_places(zzSTR);
      if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
      }     /* MR10 */
    }
    else {
      if ( !zzrv ) zzGUESS_DONE;
      zzGUESS
      if ( !zzrv && (LA(1)==U) && (LA(2)==CONSTINT) ) {
#line 1452 "f77.g"
        {
          zzBLOCK(zztasp2);
          zzMake0;
          {
#line 1452 "f77.g"
            zzmatch(U);zzNON_GUESS_MODE {
               zzsubchild(_root, &_sibling, &_tail);            }
             zzCONSUME;
#line 1452 "f77.g"
            field_width(zzSTR);
            if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
            }     /* MR10 */
            zzEXIT(zztasp2);
          }
        }
        zzGUESS_DONE
#line 1452 "f77.g"
        zzmatch(U);zzNON_GUESS_MODE {
           zzsubroot(_root, &_sibling, &_tail);        }
         zzCONSUME;
#line 1452 "f77.g"
        field_width(zzSTR);
        if (!zzguessing) {    /* MR10 */
 zzlink(_root, &_sibling, &_tail);
        }     /* MR10 */
      }
      else {
        if ( !zzrv ) zzGUESS_DONE;
        if ( (LA(1)==U) && (setwd42[LA(2)]&0x80) ) {
#line 1453 "f77.g"
          zzmatch(U);zzNON_GUESS_MODE {
             zzsubroot(_root, &_sibling, &_tail);          }
           zzCONSUME;
        }
        else {zzFAIL(2,zzerr120,zzerr121,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
      }
    }
    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd43, 0x1);
  }
}

void
#ifdef __USE_PROTOS
field_width(AST**_root)
#else
field_width(_root)
AST **_root;
#endif
{
#line 1455 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1455 "f77.g"
    zzmatch(CONSTINT);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
#line 1455 "f77.g"
      zzastArg(1)->token = FIELD_WIDTH;
    }
 zzCONSUME;

    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd43, 0x2);
  }
}

void
#ifdef __USE_PROTOS
min_dig_required(AST**_root)
#else
min_dig_required(_root)
AST **_root;
#endif
{
#line 1456 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1456 "f77.g"
    zzmatch(CONSTINT);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
#line 1456 "f77.g"
      zzastArg(1)->token = MIN_DIG_REQUIRED;
    }
 zzCONSUME;

    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd43, 0x4);
  }
}

void
#ifdef __USE_PROTOS
decimal_places(AST**_root)
#else
decimal_places(_root)
AST **_root;
#endif
{
#line 1457 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1457 "f77.g"
    zzmatch(CONSTINT);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
#line 1457 "f77.g"
      zzastArg(1)->token = DECIMAL_PLACES;
    }
 zzCONSUME;

    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd43, 0x8);
  }
}

void
#ifdef __USE_PROTOS
exponent_digits(AST**_root)
#else
exponent_digits(_root)
AST **_root;
#endif
{
#line 1458 "f77.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1458 "f77.g"
    zzmatch(CONSTINT);zzNON_GUESS_MODE {
       zzsubchild(_root, &_sibling, &_tail);    }
    
    zzNON_GUESS_MODE {
#line 1458 "f77.g"
      zzastArg(1)->token = EXPONENT_DIGITS;
    }
 zzCONSUME;

    zzEXIT(zztasp1);
    return;
fail:
    zzEXIT(zztasp1);
    if ( zzguessing ) zzGUESS_FAIL;
    zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
    zzresynch(setwd43, 0x10);
  }
}
