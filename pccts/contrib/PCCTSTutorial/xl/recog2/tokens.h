#ifndef tokens_h
#define tokens_h
/* tokens.h -- List of labelled tokens and stuff
 *
 * Generated from: xl.g
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * ANTLR Version 1.33MR33
 *
 *   ..\..\..\..\bin\antlr.exe -emsvc -CC -e3 -gl xl.g
 *
 */
enum ANTLRTokenType {
	INTLIT=5,
	CHARLIT=6,
	PROGRAM=8,
	BEGIN=9,
	END=10,
	VAR=11,
	CONSTANT=12,
	TYPE=13,
	RECORD=14,
	ARRAY=15,
	OF=16,
	PROCEDURE=17,
	PUT=18,
	GET=19,
	SKIPLINE=20,
	NEWLINE=21,
	EXIT=22,
	WHEN=23,
	RETURN=24,
	IF=25,
	THEN=26,
	ELSE=27,
	ELSIF=28,
	WHILE=29,
	LOOP=30,
	AND=31,
	OR=32,
	INTEGER=33,
	BOOLEAN=34,
	DOT=35,
	BECOMES=36,
	COLON=37,
	SEMI=38,
	COMMA=39,
	EQUALS=40,
	LBRACKET=41,
	RBRACKET=42,
	DOTDOT=43,
	LPAREN=44,
	RPAREN=45,
	NOT_EQUALS=46,
	LT=47,
	LTE=48,
	GT=49,
	GTE=50,
	PLUS=51,
	MINUS=52,
	TIMES=53,
	DIV=54,
	MOD=55,
	NOT=56,
	IDENT=57,
	BADSTRING=59,
	STRINGLIT=60,
	DLGminToken=0,
	DLGmaxToken=9999};


#define zzSET_SIZE 12
#define zzTOKEN_COUNT 67





#endif /* tokens_h */
