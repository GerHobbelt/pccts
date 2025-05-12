#header <<
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
		>>

#lexaction <<
	void zzcr_attr(Attrib *attrib, int tok, char *tok_text) {
		strncpy(attrib->text, tok_text, D_TextSize-1);
		attrib->text[D_TextSize-1] = '\0';

		#ifndef SUPPRESS_TRAILING_COMMENTS
			if(zzinf_tokens[zzinf_labase+1] == TRAILING_COMMENT) {
				zzinf_tokens[zzinf_labase+1] = zzinf_tokens[zzinf_labase];
				zzinf_line[zzinf_labase+1] = zzinf_line[zzinf_labase];
				strncpy(attrib->trail_comment_text, zzinf_text[zzinf_labase+1], D_TextSize-1);
				/*strcat(zzinf_text[zzinf_labase], zzinf_text[zzinf_labase+1]);*/
				zzinf_text[zzinf_labase+1] = zzinf_text[zzinf_labase];
				zzinf_tokens[zzinf_labase] = SKIP_TOKEN;
			
				zzinf_labase++;
				}
			else if(zzinf_tokens[zzinf_labase] == SKIP_TOKEN) {
				zzinf_labase++;
				}
		#endif
		}
	>>

<<
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
>>

<<
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
>>

#token SKIP_TOKEN
#token INVALID

#lexclass NEWLINE
#token FILEKEYWORD	"FILE" <<keyword_context = FILEKEYWORD; zzmode(START);>>
#token "[\ ]+"
	<<
	if(EndCol < 4) {
		zzskip();
		}
	else if(EndCol == 4)
		{
		if(zzchar == '0')
			{/*Start of a new statement but skip this whitespace.*/
			zzmode(KEYWORD);
			keyword_context = KEYWORD_UNDEFINED;
			zzskip();
			}
		else	{/*Continuation line...*/
			NLA = CONTINUATION_LINE;
			if(keyword_context == FORMAT) {
				zzmode(FORMAT_CLASS);
				}
			else	{
				zzmode(START);
				}
			zzskip();
			}
		zzreplstr("DEBUGING");
		zzadvance();	/*Skip the char on column 6.*/
		}
	else if(EndCol < 71)
		{/*Start of a new statement but skip this whitespace.*/
		zzmode(KEYWORD);
		zzskip();
		}
	else if(EndCol == 71)
		{
		NLA = BLANK_LINE;
		zzmode(START);
		/*zzskip();*/
		}
	else	{
		NLA = ERROR_WHITESPACE_LABEL;
		zzmode(START);
		}
	>>
#token CONTINUATION_LINE
#token BLANK_LINE
#token ERROR_WHITESPACE_LABEL
#token "[C\*]"
	<<
	if(BegCol == 0) {
		zzmode(COMMENT);
		zzskip();
		}
	>>
#token LABEL	"[0-9]+"
	<<
	if(EndCol >= 5) {
		NLA = ERROR_LABEL_TOKEN;
		}
	else	{
		/*Start of a new statement follows.*/
		zzmode(KEYWORD);
		}
	>>
#token ERROR_LABEL_TOKEN
#token CONTROL_IMAGE	"$|$$"
		<<
		keyword_context = NLA;
		if(BegCol >= 2)
			NLA = CONTROL_IMAGE_ERROR;
		zzmode(START);
		>>
#token CONTROL_IMAGE_ERROR

#lexclass KEYWORD
#token BLOCK_IF
#token ARITHMETIC_IF
#token LOGICAL_IF
#token IF				"IF"						<<zzmode(START); keyword_context = NLA;>>
#token ELSE_IF			"ELSE IF"					<<zzmode(START); keyword_context = NLA;>>
#token ELSE				"ELSE"						<<zzmode(START); keyword_context = NLA;>>
#token END_IF			"ENDIF" 					<<zzmode(START); keyword_context = NLA;>>
#token END				"END"						<<zzmode(START); keyword_context = NLA;>>
#token STOP				"STOP"						<<zzmode(START); keyword_context = NLA;>>
#token REAL				"REAL"						<<zzmode(START); keyword_context = NLA;>>
#token DOUBLE_PRECISION	"DOUBLE[\ ]*PRECISION"		<<zzmode(START); keyword_context = NLA;>>
#token LOGICAL			"LOGICAL"					<<zzmode(START); keyword_context = NLA;>>
#token INTEGER			"INTEGER"					<<zzmode(START); keyword_context = NLA;>>
#token CHARACTER		"CHARACTER"					<<zzmode(START); keyword_context = NLA;>>
#token COMPLEX			"COMPLEX"					<<zzmode(START); keyword_context = NLA;>>
#token DOUBLE_COMPLEX	"DOUBLE_COMPLEX" 			<<zzmode(START); keyword_context = NLA;>>
#token IMPLICIT			"IMPLICIT"					<<             ; keyword_context = NLA;>>
#token COMMON			"COMMON"					<<zzmode(START); keyword_context = NLA;>>
#token DATA				"DATA"
	<<
	if(zzchar == ' ') {
		zzmode(START); keyword_context = NLA;
		}
	else {/*It is an identifier!*/
		zzmode(START);
		NLA = IDENTIFIER;
		keyword_context = ASSIGNMENT;
		}
	>>
#token DO				"DO"						<<zzmode(START); keyword_context = NLA;>>
#token CONTINUE     	"CONTINUE"					<<zzmode(START); keyword_context = NLA;>>
#token CALL				"CALL"						<<keyword_context = NLA;>>
#token SUBROUTINE		"SUBROUTINE"				<<keyword_context = NLA;>>
#token FUNCTION			"FUNCTION"					<<zzmode(START); keyword_context = NLA;>> /*Function without return type specified.*/
#token GO_TO			"GO[\ \t]*TO"				<<zzmode(START); keyword_context = NLA;>>
#token UNCONDITIONAL_GOTO
#token COMPUTED_GOTO
#token ASSIGNED_GOTO

#token RETURN		"RETURN"	<<zzmode(START); keyword_context = NLA;>>
#token EXTERNAL		"EXTERNAL"	<<zzmode(START); keyword_context = NLA;>>
#token INTRINSIC	"INTRINSIC"	<<zzmode(START); keyword_context = NLA;>>
#token SAVE			"SAVE"		<<zzmode(START); keyword_context = NLA;>>
#token ENTRY		"ENTRY"		<<zzmode(START); keyword_context = NLA;>>
#token PARAMETER 	"PARAMETER"	<<zzmode(START); keyword_context = NLA;>>
#token FORMAT		"FORMAT"
	<<
	zzmode(FORMAT_CLASS);
	keyword_context = NLA;
	LPCount = 0;
	CommaCount = 0;
	>>
#token INQUIRE		"INQUIRE"	<<zzmode(START); keyword_context = NLA;>>
#token BACKSPACE	"BACKSPACE"	<<zzmode(START); keyword_context = NLA;>>
#token ENDFILE		"ENDFILE"	<<zzmode(START); keyword_context = NLA;>>
#token REWIND		"REWIND"	<<zzmode(START); keyword_context = NLA;>>
#token BLOCK_GLOBALS	"BLOCK[\ ]+GLOBALS" <<zzmode(START); keyword_context = NLA;>>
#token EXPORT		"EXPORT"	<<zzmode(START); keyword_context = NLA;>>
#token CHANGE		"CHANGE"	<<zzmode(START); keyword_context = NLA;>>
#token OPEN			"OPEN"		<<zzmode(START); keyword_context = NLA;>>
#token CLOSE		"CLOSE"		<<zzmode(START); keyword_context = NLA;>>
#token DIMENSION	"DIMENSION"	<<zzmode(START); keyword_context = NLA;>>
#token EQUIVALENCE	"EQUIVALENCE"	<<zzmode(START); keyword_context = NLA;>>
#token ASSIGN		"ASSIGN"		<<zzmode(START); keyword_context = NLA;>>
#token LIBRARY		"LIBRARY"		<<zzmode(START); keyword_context = NLA;>>
#token WRITE		"WRITE"		<<ReadWriteProcessing();>>
#token READ		"READ"		<<ReadWriteProcessing();>>
 /*UNISYS FORTRAN V4.0*/
#token FIND 		"FIND"		<<zzmode(START); keyword_context = NLA;>>

#token "[a-zA-Z\$][a-zA-Z0-9_\$]*"
	<<
	zzmode(START);
	NLA = IDENTIFIER;
	keyword_context = ASSIGNMENT;
	>>
#token KEYWORD_UNDEFINED /*While keyword is not resolved */
#token ASSIGNMENT

#token "[\ \t]+"	<<zzskip();>>
#token "[\%\!]"
	<<
	zzmode(COMMENT);
	zzreplstr("!");
	zzmore();
	>>

#lexclass COMMENT
#token COMMENT_LINE "(~[\n])*"
			<<{
			if(BegCol >= 5) {
				NLA = TRAILING_COMMENT;
				#ifdef SUPPRESS_TRAILING_COMMENTS
					zzskip();
				#endif
				}
			zzmode(START);
			}>>
#token TRAILING_COMMENT

#lexclass START

#token WHITESPACE "[\ ]+" << zzskip();>>

#token EQUAL	"="	<<>>

#token POW	"\*\*"	<<>>
#token STAR	"\*"	<<>>
#token MUL		/*I will use this one later.*/
#token MIN	"\-"	<<>>
#token PLU	"\+"	<<>>
#token UNARY_PLU
#token UNARY_MIN

#token CONCAT	"\/\/"	<<>>
#token DIV	"\/"	<<>>
#token AMPERSAND "\&"	<<>>


#token COLUMN "\:"	<<>>
 /*UNISYS FORTRAN 3.8*/
#token SEMICOLUMN "\;"
	<<
	zzmode(KEYWORD);
	zzskip();
	>>
#token IMPLIED_DO_VARIABLE
#token IMPLIED_LP
#token IMPLIED_RP
#token IO_SPEC_LP
#token IO_SPEC_RP
#token LP	"\("
	<<
	if((keyword_context == WRITE) || (keyword_context == READ))
		{
		LPCount++;
		if((LPCount == 1) && (ReadWriteControlFlag == TRUE)) {
			ExpectingIOKeyword = TRUE;
			}
		}
	>>
#token RP	"\)"
	<<
	if((keyword_context == WRITE) || (keyword_context == READ))
		{
		LPCount--;
		if((LPCount == 0) && (ReadWriteControlFlag == TRUE)) {
			ReadWriteControlFlag = FALSE;
			}
		}
	>>

#token COMMA	"\,"
	<<
	if((keyword_context == WRITE) || (keyword_context == READ))
		{
		CommaCount++;	/*Commas since the last WRITE or READ*/
		if(ReadWriteControlFlag == TRUE) {
			ExpectingIOKeyword = TRUE;
			}
		}
	>>

#token EOL	"\n"
	<<
	NewLineProcessing();
	zzskip();
	zzmode(NEWLINE);
	>>
#token HOLLERITH_CONST "[1-9][0-9]*H"
	<<
	ProcessHollerith();
	>>

#token T_FALSE		".[\ ]*FALSE[\ ]*."  	<<>>
#token T_TRUE		".[\ ]*TRUE[\ ]*."		<<>>

 /**********************/
 /*LOGICAL OPERATORS*/
 /**********************/
#token AND		"{.[\ ]*}AND[\ ]*."		<<>>
#token OR		"{.[\ ]*}OR[\ ]*."		<<>>
#token NEQV		"{.[\ ]*}NEQV[\ ]*."		<<>>
#token EQV		"{.[\ ]*}EQV[\ ]*."		<<>>
#token NOT		"{.[\ ]*}NOT[\ ]*."		<<>>
 /**********************/
 /*RELATIONAL OPERATORS*/
 /**********************/
#token LT	"{.[\ ]*}LT[\ ]*."
#token LE	"{.[\ ]*}LE[\ ]*."
#token EQ	"{.[\ ]*}EQ[\ ]*."
#token NE	"{.[\ ]*}NE[\ ]*."
#token GT	"{.[\ ]*}GT[\ ]*."
#token GE	"{.[\ ]*}GE[\ ]*."
#token IS	".[\ ]*IS[\ ]*."

#token HEX_CONST	"[#Z][0-9A-F]+" /*|(['\"][0-9A-F]+['\"]X)" <<>>*/
	<<
	if(*zzbegexpr == 'Z') {/*If the Z notation...*/
		switch(keyword_context) {
			case DATA:
			case INTEGER:
			case CHARACTER:
			case REAL:
			case LOGICAL:
			case DOUBLE_PRECISION:
				break;
			default:
				NLA = IDENTIFIER;
				break;
			}
		}
	>>

#token BASIC_REAL      		"[0-9]*\.[0-9]+"
#token	"[0-9]+." /*To cater for VAR.GT.0.OR. ...*/
	<<
	if(	((zzchar >= 'a') && (zzchar <= 'z'))
		||
		((zzchar >= 'A') && (zzchar <= 'Z'))
	  )	{
		*zzendexpr = '\0';
		NLA = CONSTINT;
		}
	else
		{
		NLA = BASIC_REAL;
		}
	>>

#token REAL_EXPO	"([0-9]+.[0-9]+|[0-9]+.|.[0-9]+|[0-9]+)E{[\+\-]}[0-9]+"
#token SOME_CONSTINTEGER	"[0-9]+"
	<<
	if(EndCol < 72)
		NLA = CONSTINT;
	else if(BegCol >= 72) {
		NLA = SEQUENCE;
		zzskip();
		}
	else
		NLA = CONSTINT_ERROR;
	>>
#token CONSTANT_NAME /*For symbolic constants i.e. PARAMETER statements.*/
#token CONSTINT
#token CONSTINT_ERROR
#token SEQUENCE
 /*#token Eof	"@"			<<>>*/
#token "[\%\!]"
	<<
	zzmode(COMMENT);
	zzreplstr("!");
	zzmore();
	>>
#token QUOTED_STRING "[\"]"	<<GetQuotedString();>>
#token APOSTROPHY "[']"
	<<
	/*Detecting apostrophis in combined expressions.*/
	if(	(
		(keyword_context == WRITE)
		|| (keyword_context == READ)
		)
		&& (LPCount == 1)
		&& (CommaCount == 0)
		) {
		NLA = APOSTROPHY;
		}
	/*UNISYS FORTRAN V3.8*/
	else if(keyword_context == FIND) {
		NLA = APOSTROPHY;
		}
	else	{
		GetQuotedString();
		NLA = QUOTED_STRING;
		}
	>>
#token TO		"TO"
	<<
	if(keyword_context != ASSIGN)
		NLA = IDENTIFIER;
		
	>>


/*Compiler control image keywords*/
#token PAGE "PAGE" <<if(keyword_context != CONTROL_IMAGE) NLA = IDENTIFIER;>>
#token SET "SET" <<if(keyword_context != CONTROL_IMAGE) NLA = IDENTIFIER;>>
#token LIST "LIST" <<if(keyword_context != CONTROL_IMAGE) NLA = IDENTIFIER;>>
#token XREF "XREF" <<if(keyword_context != CONTROL_IMAGE) NLA = IDENTIFIER;>>
#token ERRLIST "ERRLIST" <<if(keyword_context != CONTROL_IMAGE) NLA = IDENTIFIER;>>
#token LINEINFO "LINEINFO" <<if(keyword_context != CONTROL_IMAGE) NLA = IDENTIFIER;>>
#token NEW "NEW" <<if(keyword_context != CONTROL_IMAGE) NLA = IDENTIFIER;>>
#token RESET "RESET" <<if(keyword_context != CONTROL_IMAGE) NLA = IDENTIFIER;>>
#token OWN "OWN" <<if(keyword_context != CONTROL_IMAGE) NLA = IDENTIFIER;>>
#token CHARS "CHARS" <<if(keyword_context != CONTROL_IMAGE) NLA = IDENTIFIER;>>
#token STACK "STACK" <<if(keyword_context != CONTROL_IMAGE) NLA = IDENTIFIER;>>
#token FREE "FREE" <<if(keyword_context != CONTROL_IMAGE) NLA = IDENTIFIER;>>
#token POP "POP" <<if(keyword_context != CONTROL_IMAGE) NLA = IDENTIFIER;>>
#token INCLUDE "INCLUDE" <<if(keyword_context != CONTROL_IMAGE) NLA = IDENTIFIER;>>

#token "FUNCTION"	/*Function with return type specified.*/
	<<
	switch(keyword_context) {
		case INTEGER:
		case REAL:
		case DOUBLE_PRECISION:
		case LOGICAL:
		case CHARACTER:
		case COMPLEX:
		case DOUBLE_COMPLEX:
			NLA = FUNCTION;
			keyword_context = FUNCTION;
			break;
		default:
			NLA = IDENTIFIER;
			break;
		}
	>>
 /*
 This is to provide for logical if statement which has just one
 executable statement following the if expression.
 */
#token "IF"			<<keyword_context = NLA = IF;>>
#token "DO"			<<keyword_context = NLA = DO;>>
#token "GO[\ \t]*TO"	<<keyword_context = NLA = GO_TO;>>
#token "RETURN"		<<keyword_context = NLA = RETURN;>>
#token "ASSIGN"		<<keyword_context = NLA = ASSIGN;>>
#token "READ"		<<keyword_context = NLA = READ;ReadWriteProcessing();>>
#token "WRITE"		<<ReadWriteProcessing();keyword_context = NLA = WRITE;>>
 /*UNISYS FORTRAN V3.8*/
#token "FIND"		<<keyword_context = NLA = FIND;>>
 /*END UNISYS FORTRAN V3.8*/
#token "CALL"		<<zzmode(KEYWORD); keyword_context = NLA = CALL;>>
#token "INQUIRE"	<<keyword_context = NLA = INQUIRE;>>
#token "BACKSPACE"	<<keyword_context = NLA = BACKSPACE;>>
#token "ENDFILE"	<<keyword_context = NLA = ENDFILE;>>
#token "REWIND"		<<keyword_context = NLA = REWIND;>>
#token "OPEN"
	<<
	/*UNISYS FORTRAN V3.8*/
	if(keyword_context == INQUIRE) {
		keyword_context = NLA = OPEN;
		}
	/*END UNISYS FORTRAN V3.8*/
	else if(keyword_context == IF) {
		keyword_context = NLA = OPEN;
		ReadWriteProcessing();
		}
	else {
		NLA = IDENTIFIER;
		}
	>>
#token	"CLOSE"
	<<
	if(keyword_context == IF) {
		keyword_context = NLA = CLOSE;
		}
	else	{
		NLA = IDENTIFIER;
		}
	>>

#token "STOP"
	<<
	if(keyword_context == IF) {
		keyword_context = NLA = STOP;
		}
	else	{
		NLA = IDENTIFIER;
		}
	>>

#token	"CHANGE"
	<<
	if(keyword_context == IF) {
		keyword_context = NLA = CHANGE;
		}
	else	{
		NLA = IDENTIFIER;
		}
	>>


#token FILE_WORD	"FILE" <<>>

#token THEN		"THEN"
#token LIBPARAMETER	"LIBPARAMETER"
#token FUNCTIONNAME	"FUNCTIONNAME"
#token KIND		"KIND"
#token TITLE		"TITLE"	<<IOStatement();>>
#token FILETYPE		"FILETYPE"
#token NEWFILE		"NEWFILE"
#token MYUSE		"MYUSE"
#token MAXRECSIZE	"MAXRECSIZE"
#token SAVEFACTOR	"SAVEFACTOR"
#token BLOCKSIZE	"BLOCKSIZE"
#token SECURITYTYPE	"SECURITYTYPE"
#token AREAS 		"AREAS"
#token AREASIZE 	"AREASIZE"
#token PROTECTION 	"PROTECTION"
#token UNITS		"UNITS"
#token UPDATEFILE	"UPDATEFILE"
#token STATUS		"STATUS"
	<<
	IOStatement();
	if(zzchar == '(') {
		NLA = IDENTIFIER;
		}
		>>
#token FMT			"FMT"		<<IOStatement();>>
#token RECL			"RECL"		<<IOStatement();>>
#token REC			"REC"		<<IOStatement();>>
#token END			"END"		<<IOStatement();>>
#token ERR			"ERR"		<<IOStatement();>>
#token IOSTAT		"IOSTAT"	<<IOStatement();>>

#token URGENT		"URGENT"	<<IOStatement();>>
#token IO_DATA		"DATA"		<<IOStatement();>>
#token NUMBER		"NUMBER"	<<IOStatement();>>
#token NEXTREC		"NEXTREC"	<<IOStatement();>>
#token EXIST		"EXIST"		<<IOStatement();>>
#token OPENED		"OPENED"	<<IOStatement();>>
#token NAMED		"NAMED"		<<IOStatement();>>
#token RECORD		"RECORD"	<<IOStatement();>>
#token NAME			"NAME"		<<IOStatement();>>
#token DISP			"DISP"		<<IOStatement();>>
#token SUBFILE		"SUBFILE"	<<IOStatement();>>
#token OPENTYPE		"OPENTYPE"	<<IOStatement();>>

#token RESIDENT		"RESIDENT"	<<IOStatement();>>
#token ACCESS		"ACCESS"	<<IOStatement();>>
#token SEQUENTIAL	"SEQUENTIAL"	<<IOStatement();>>
#token DIRECT		"DIRECT"	<<IOStatement();>>
#token UNFORMATTED	"UNFORMATTED"	<<IOStatement();>>
#token FORMATTED	"FORMATTED"	<<IOStatement();>>
#token FORM			"FORM"	<<IOStatement();>>
#token BLANK		"BLANK"	<<IOStatement();>>


#token IDENTIFIER "[a-zA-Z\$][a-zA-Z0-9_\$]*"
#token ARRAY_NAME
#token INTEGER_ID
#token INTEGER_ARRAY_ID
#token REAL_ID
#token REAL_ARRAY_ID
#token DOUBLE_PRECISION_ID
#token DOUBLE_PRECISION_ARRAY_ID
#token CHARACTER_ID
#token CHARACTER_ARRAY_ID
#token CHARACTER_SUBSTRING
#token LOGICAL_ID
#token LOGICAL_ARRAY_ID
#token COMPLEX_ID
#token DOUBLE_COMPLEX_ID
#token FUNCTION_NAME
#token SUBROUTINE_NAME
#token INTRINSIC_NAME

#token FIELD_WIDTH
#token DECIMAL_PLACES
#token EXPONENT_DIGITS
#token MIN_DIG_REQUIRED
#token REPEAT_COUNT
#token SCALE_FACTOR

program:
	<<
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
	>>
	(source_line)*
	<<
	/*OutSource(F77root);*/
	>>
 ;
source_line :
	comment_line
	|blank_line
	|control_image
	|statement
	<<
	StatementCount++;
	printf("Processed %f. Line %d\n", 100*((float)zzline/LineCount), zzline);
	>>
	;

comment_line: COMMENT_LINE^
	;

blank_line: BLANK_LINE^
	;

control_image : CONTROL_IMAGE^ (option_phrase)*
		<<
		>>;
option_phrase:	set_phrase
		|pop_phrase
		|reset_phrase
		|include_phrase
		|option
		;

set_phrase: SET (
		(option EQUAL)? option EQUAL option
		|option
		)
		;
pop_phrase: POP option
		;
reset_phrase: RESET option
		;
include_phrase: INCLUDE char_const
	;
option: <<int dummy;>>
	CHARS
	|STACK
	|PAGE
	|FREE
	|OWN
	|NEW
	|LIST
	|XREF
	|ERRLIST
	|LINEINFO
	|constant > [dummy]
	|NOT option
	;

statement: statement1	/*Because of compiler stack overflow!*/
	|statement2
	;

statement1:
	 	file_statement
		|(function_statement)? function_statement
		|real_statement
		|double_precision_statement
		|integer_statement
		|logical_statement
		|character_statement
		|common_statement
		|external_statement
		|data_statement
		|call_statement
		|do_statement
		|continue_statement
		|assignment_statement
		|if_statement
		|end_statement
		|stop_statement
		|subroutine_statement
		|entry_statement
		|goto_statement
		;

statement2:
		return_statement
		|read_statement
		|write_statement
		|format_statement
		|inquire_statement
		|backspace_statement
		|endfile_statement
		|rewind_statement
		|block_globals_statement
		|export_statement
		|change_statement
		|open_statement
		|close_statement
		|dimension_statement
		|equivalence_statement
		|implicit_statement
		|save_statement
		|parameter_statement
		|assign_statement
		|find_statement	/*UNISYS FORTRAN V3.8*/
		;

file_statement: FILEKEYWORD^ unit_identifier
		LP file_item (COMMA file_item)*
		RP 
		;
file_item:
		KIND EQUAL file_name
		|TITLE EQUAL file_name
		|FILETYPE EQUAL int_const
		|NEWFILE EQUAL file_name
		|MYUSE EQUAL int_const
		|MAXRECSIZE EQUAL int_const
		|SAVEFACTOR EQUAL int_const
		|BLOCKSIZE EQUAL int_const
		|SECURITYTYPE EQUAL file_name
		|AREAS EQUAL int_const
		|AREASIZE EQUAL int_const
		|PROTECTION EQUAL IDENTIFIER
		|UNITS EQUAL (file_name|CONSTINT)
		|UPDATEFILE EQUAL file_name
		|FILE_WORD EQUAL file_name
		|STATUS EQUAL file_name
		|ACCESS EQUAL file_name
		|FORM EQUAL file_name
		|RECL EQUAL file_name
		|BLANK EQUAL file_name
		;

file_name: (IDENTIFIER|QUOTED_STRING)
	;
 /************************/
 /*EQUIVALENCE statement */
 /************************/
equivalence_statement: {LABEL} EQUIVALENCE^ equiv_item (COMMA equiv_item)*
		;
equiv_item: LP equiv_entity (COMMA equiv_entity)+ RP
		;
equiv_entity: variable[LVALUE]
	;

length_spec: <<int type;>>	LP STAR RP
		|LP expression > [type] RP
		|CONSTINT
		;

common_statement: <<CurrentStatement = COMMON;>>
	{LABEL} COMMON^ block_item	(COMMA block_item)*
	<<CurrentStatement = INVALID;>>
	;
block_item :
	variable[LVALUE]
	|DIV IDENTIFIER DIV variable[LVALUE]
	|CONCAT variable[LVALUE]
	|DIV DIV variable[LVALUE]
	;

data_statement :{LABEL} DATA^ data_list
		;
data_list:  data_item ({COMMA} data_item)*;

data_item : data_var_list DIV data_const_list DIV
	;
data_var_list : data_var_list_elem (COMMA data_var_list_elem)*
	;

data_var_list_elem :
	(LP)? data_implied_do_list
	|(IDENTIFIER)? variable[LVALUE] /*Not declared but assigned first. OK.*/
	;
data_const_list : data_constant (COMMA data_constant)*
	;
data_constant:<<int dummy;>>
	(CONSTINT STAR)? CONSTINT STAR constant > [dummy]
	|(MIN|PLU)? (MIN|PLU) constant > [dummy]
	|constant > [dummy]
	;
data_implied_do_list : LP (array_element_reference[LVALUE]
							|data_implied_do_list)
			COMMA implied_do_variable EQUAL int_const
			COMMA int_const
			RP
			;
implied_do_variable :IDENTIFIER;

do_statement: {LABEL} DO^ statement_label
	{COMMA}	do_variable EQUAL initial
	COMMA terminal {COMMA incremental}
	;
do_variable : i:IDENTIFIER
	<<
	AddSymbol($i.text, INTEGER_ID); /*And add it to the symbol table.*/
	#1->token = INTEGER_ID;
	>>;
initial: <<int type;>> expression > [type] ;
terminal: <<int type;>> expression > [type] ;
incremental: <<int type;>> expression > [type] ;

continue_statement : {LABEL} CONTINUE^
		<<
		>>;

call_statement: <<int type;>>
		{LABEL} CALL^ s:IDENTIFIER {call_arg_list}
		<<
		type = LookUp($s.text);
		if(type != FUNCTION_NAME) {
			ChangeType($s.text, FUNCTION_NAME);
			}
		#3->token = FUNCTION_NAME;
		>>
		;
call_arg_list : LP {call_arg_item
		(COMMA call_arg_item)*}
		RP;
call_arg_item: <<int type;>> 
	(
		(STAR|AMPERSAND)? (STAR|AMPERSAND) statement_label
		|expression > [type]
	)
		;
statement_label : CONSTINT;

if_statement: <<int type;>>
	 	(({LABEL} IF LP expression > [type] RP THEN)? block_if_statement
		|({LABEL} IF LP expression > [type] RP label)? arithmetic_if_statement
		|logical_if_statement
		)
		;

block_if_statement: <<int type;>>
	{LABEL} IF^ LP expression > [type] RP THEN
	{statement_block}
	{
	(ELSE | ELSE_IF LP expression > [type] RP)
	{statement_block}
	}															 
	END_IF
	<<#2->token = BLOCK_IF;>>
	;
logical_if_statement: <<int type;>>
	{LABEL} IF^ LP expression > [type] RP executable_statement
	<<#2->token = LOGICAL_IF;>>
	;
arithmetic_if_statement: <<int type;>>
	{LABEL} IF^ LP expression > [type] RP label COMMA label COMMA label
	<<#2->token = ARITHMETIC_IF;>>
	;

statement_block : (
	do_statement
	|if_statement
	|format_statement
	|call_statement
	|continue_statement
	|assignment_statement
	|goto_statement
	|return_statement
	|read_statement
	|write_statement
	|inquire_statement
	|backspace_statement
	|endfile_statement
	|rewind_statement
	|open_statement
	|close_statement
	|stop_statement
	|change_statement
	|comment_line
	|blank_line
	|assign_statement
	|find_statement	/*UNISYS FORTRAN V3.8*/
	)+;

executable_statement:
	call_statement
	|continue_statement
	|assignment_statement
	|goto_statement
	|return_statement
	|read_statement
	|write_statement
	|inquire_statement
	|backspace_statement
	|endfile_statement
	|rewind_statement
	|open_statement
	|close_statement
	|stop_statement
	|change_statement
	|arithmetic_if_statement
	|assign_statement
	|find_statement	/*UNISYS FORTRAN V3.8*/
	;

assignment_statement:
		<<
		int type;
		printf("Parsing assignment statement. ");
		>>
		{LABEL} variable[LVALUE] EQUAL^ expression > [type]
		;

function_call: IDENTIFIER^ LP {actual_argument_list} RP
	<<
	#1->token = FUNCTION_NAME;
	>>
	;
actual_argument_list:  actual_argument (COMMA actual_argument)*
		;
actual_argument: <<int type;>>
	(IDENTIFIER (COMMA|RP))? IDENTIFIER
	|(constant > [type] (COMMA|RP))? constant > [type]
	|(function_call (COMMA|RP))? function_call
	|expression > [type] /*RVALUE because its reading.*/
	;

end_statement : {LABEL} END^
		<<
		>>;

stop_statement : {LABEL} STOP^
		<<
		>>;

return_statement : {LABEL} RETURN^
		<<
		>>;

block_globals_statement : {LABEL} BLOCK_GLOBALS^
		;
export_statement: {LABEL} EXPORT^ LP export_item
	(COMMA export_item)*
	RP ;

export_item:
	(DIV IDENTIFIER DIV /*Common block designator*/
	|IDENTIFIER
	|CONSTINT) {EQUAL QUOTED_STRING}
	;

subroutine_statement : {LABEL} SUBROUTINE^ i:IDENTIFIER {sub_arg_list}
	<<
	ChangeType($i.text, FUNCTION_NAME);
	>>
	;
sub_arg_list: LP {sub_argument (COMMA sub_argument)*} RP;
sub_argument:
	formal_argument
	|STAR	/*Dummy argument*/
	;
formal_argument: <<int type;>>
	i:IDENTIFIER
	<<
	/*I say that it is either INTEGER or REAL and let the rest of code change it if	needed*/
	type = LookUp($i.text);
	if(type == -1) {
		type = ((*($i.text) >= 'I') && (*($i.text) <= 'N'))?INTEGER_ID:REAL_ID;
		AddSymbol($i.text, type);
		}
	#1->token = type;
	>>
	;

function_statement: <<int type = INVALID;>>
	{function_type > [type]} FUNCTION^ i:IDENTIFIER LP {function_arg_list} RP
	<<
	if(type == INVALID) {
		type = ((*($i.text) >= 'I') && (*($i.text) <= 'N'))?INTEGER_ID:REAL_ID;
		}
	ChangeType($i.text, type);
	>>
		;

function_type > [int type]:
		(
		INTEGER				<<$type = INTEGER_ID;>>
		|REAL				<<$type = REAL_ID;>>
		|DOUBLE_PRECISION	<<$type = DOUBLE_PRECISION_ID;>>
		|LOGICAL			<<$type = LOGICAL_ID;>>
		|CHARACTER			<<$type = CHARACTER_ID;>>
		|COMPLEX			<<$type = COMPLEX_ID;>>
		|DOUBLE_COMPLEX		<<$type = DOUBLE_COMPLEX_ID;>>
		)
		{STAR length_spec}
		;
function_arg_list: {DIV <<#1->token = SLASH;>>} formal_argument {DIV <<#1->token = SLASH;>>}
	(COMMA {DIV <<#1->token = SLASH;>>} formal_argument {DIV <<#1->token = SLASH;>>})*
	;

entry_statement : {LABEL} ENTRY^ i:IDENTIFIER {sub_arg_list}
	<<
	ChangeType($i.text, FUNCTION_NAME);
	>>
	;

goto_statement: ({LABEL} GO_TO label)? unconditional_goto_statement
		|({LABEL} GO_TO IDENTIFIER)? assigned_goto_statement
		|computed_goto_statement
		;

unconditional_goto_statement: {LABEL} GO_TO^ label
		<<#2->token = UNCONDITIONAL_GOTO;>>
		;
computed_goto_statement: <<int type;>>
	{LABEL} GO_TO^ LP label (COMMA label)* RP {COMMA} expression > [type]
	<<#2->token = COMPUTED_GOTO;>>
	;
assigned_goto_statement: {LABEL} GO_TO^ IDENTIFIER
		{{COMMA} LP label (COMMA label)* RP}
		<<
		#2->token = ASSIGNED_GOTO;
		#3->token = INTEGER_ID;
		>>
		;

library_statement : {LABEL} LIBRARY^ i:IDENTIFIER LP TITLE EQUAL QUOTED_STRING RP
	;



label: CONSTINT;

repeat_count: CONSTINT <<#1->token = REPEAT_COUNT;>>;				   

arithm_operator: POW|PLU|MIN|STAR|DIV;
logical_operator: AND|OR|NEQV|EQV;
relational_operator: LT|LE|EQ|NE|GT|GE|IS;

constant > [int const_type]:
	int_const		<<$const_type = INTEGER_ID;>>
	|real_const		<<$const_type = REAL_ID;>>
	|logical_const	<<$const_type = LOGICAL_ID;>>
	|char_const		<<$const_type = CHARACTER_ID;>>
	;

arithm_const: int_const | real_const;
real_const	: BASIC_REAL | REAL_EXPO;
int_const	: CONSTINT | HEX_CONST;
logical_const	: T_TRUE | T_FALSE;
char_const	: HOLLERITH_CONST | QUOTED_STRING;

#lexclass FORMAT_CLASS
#token "['\"]"
	<<
	GetQuotedString();
	NLA = QUOTED_STRING;
	>>
#token "[\ \t]+"	<<zzskip();>>
#token "\,"
	<<
	NLA = COMMA;
	zzskip();
	>>
#token DEC_POINT "\."	<<>>
#token "[1-9][0-9]*H"
	<<
	ProcessHollerith();
	NLA = HOLLERITH_CONST;
	>>

#token TR "TR" <<>>
#token TL "TL" <<>>
#token T  "T" <<>>

#token X  "X" <<>>

#token SLASH  "\/" <<>>
#token COLUMN  ":" <<>>

#token SP	"SP" <<>>
#token SS	"SS" <<>>
#token S	"S" <<>>

#token P	"P" <<>>

#token BN	"BN" <<>>
#token BZ	"BZ" <<>>

#token I	"I"
#token J	"J"
#token F	"F"
#token E	"E"
#token D	"D"
#token G	"G"

#token O	"O"
#token L	"L"
#token A	"A"
#token Z	"Z"
 /*UNISYS FORTRAN V3.8*/
#token U	"U"
#token K	"K" <<zzskip();>>
#token DOLLAR_EDITING	"$" <<zzskip();>>

#token "[0-9]+"
	<<
	if(BegCol >= 72) {
		NLA = SEQUENCE;
		zzskip();
		}
	else	{
		NLA = CONSTINT;
		}
	>>

#token "\("	<<NLA = LP; LPCount++;>>
#token "\)"	<<NLA = RP; LPCount--; if(LPCount == 0) zzmode(START);>>
#token "[\%\!]"
	<<
	zzmode(COMMENT);
	zzreplstr("!");
	zzmore();
	>>
#token "\n"
	<<
	NewLineProcessing();
	zzskip();
	zzmode(NEWLINE);
	>>
hollerith_editing: HOLLERITH_CONST;
quote_editinig: QUOTED_STRING;
tr_editing: TR^ CONSTINT;
tl_editing: TL^ CONSTINT;
t_editing:  T^ CONSTINT;
x_editing:  {CONSTINT <<#1->token = REPEAT_COUNT;>>} X^;
colon_editing: COLUMN;
sp_editing: SP;
ss_editing: SS;
s_editing: S;
p_editing: {CONSTINT <<#1->token = SCALE_FACTOR;>>} P^;
bn_editing: BN;
bz_editing: BZ;

i_editing: {CONSTINT <<#1->token = REPEAT_COUNT;>>} I^ field_width {DEC_POINT min_dig_required};
j_editing: J^ field_width;
f_editing: {CONSTINT <<#1->token = REPEAT_COUNT;>>} F^ field_width DEC_POINT decimal_places;

e_editing: (short_e_editing E)? short_e_editing E exponent_digits
	|short_e_editing;
short_e_editing: {CONSTINT <<#1->token = REPEAT_COUNT;>>} E^ field_width DEC_POINT decimal_places;
d_editing: {CONSTINT <<#1->token = REPEAT_COUNT;>>} D^ field_width DEC_POINT decimal_places;
g_editing: (short_g_editing G)? short_g_editing G^ exponent_digits
		|short_g_editing;
short_g_editing: {CONSTINT <<#1->token = REPEAT_COUNT;>>} G^ field_width DEC_POINT decimal_places;
o_editing: O^ field_width;
l_editing: {CONSTINT <<#1->token = REPEAT_COUNT;>>} L^ field_width;
a_editing: ( {CONSTINT} A field_width)? {CONSTINT <<#1->token = REPEAT_COUNT;>>} A^ field_width
	|{CONSTINT <<#1->token = REPEAT_COUNT;>>} A^;
z_editing: Z^ field_width;
 /*UNISYS FORTRAN V3.8*/
u_editing: (U field_width DEC_POINT)? U^ field_width DEC_POINT decimal_places
	|(U field_width)? U^ field_width
	|U^
	;
field_width: CONSTINT		<<#1->token = FIELD_WIDTH;>>;
min_dig_required: CONSTINT	<<#1->token = MIN_DIG_REQUIRED;>>;
decimal_places: CONSTINT	<<#1->token = DECIMAL_PLACES;>>;
exponent_digits: CONSTINT	<<#1->token = EXPONENT_DIGITS;>>;

