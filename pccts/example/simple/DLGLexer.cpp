/*
 * D L G tables
 *
 * Generated from: parser.dlg
 *
 * 1989-2001 by  Will Cohen, Terence Parr, and Hank Dietz
 * Purdue University Electrical Engineering
 * DLG Version 1.33MR33
 *
 *   ..\..\bin\dlg.exe -emsvc -CC -C2 parser.dlg
 *
 */



/* parser.dlg -- DLG Description of scanner
 *
 * Generated from: simple.g
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
#include "tokens.h"
#include "AToken.h"

#include "pcctscfg.h"
#include "pccts_stdio.h"

#include "AParser.h"
#include "DLexerBase.h"
#include "DLGLexer.h"

ANTLRTokenType DLGLexer::act1()
{ 
		return Eof;
	}


ANTLRTokenType DLGLexer::act2()
{ 
		return Number;
	}


ANTLRTokenType DLGLexer::act3()
{ 
		return Word;
	}


ANTLRTokenType DLGLexer::act4()
{ 
    skip();   
		return Whitespace;
	}


ANTLRTokenType DLGLexer::act5()
{ 
		return Other;
	}


ANTLRTokenType DLGLexer::act6()
{ 
    newline(); skip();   
		return Newline;
	}

 unsigned char DLGLexer::shift0[257] = {
  0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
  4, 6, 5, 5, 7, 5, 5, 5, 5, 5, 
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
  5, 5, 5, 4, 5, 5, 5, 5, 5, 5, 
  5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 
  1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 
  5, 5, 5, 5, 5, 5, 3, 3, 3, 3, 
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
  3, 3, 5, 5, 5, 5, 5, 5, 3, 3, 
  3, 3, 3, 2, 3, 3, 3, 3, 3, 3, 
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
  3, 3, 3, 3, 5, 5, 5, 5, 5, 5, 
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
  5, 5, 5, 5, 5, 5, 5
};


const int DLGLexer::MAX_MODE=1;
const int DLGLexer::DfaStates=11;
const int DLGLexer::START=0;

DLGLexer::DfaState DLGLexer::st0[9] = {
  1, 2, 3, 4, 5, 6, 7, 8, 11
};

DLGLexer::DfaState DLGLexer::st1[9] = {
  11, 11, 11, 11, 11, 11, 11, 11, 11
};

DLGLexer::DfaState DLGLexer::st2[9] = {
  11, 2, 11, 6, 11, 6, 11, 11, 11
};

DLGLexer::DfaState DLGLexer::st3[9] = {
  11, 11, 9, 9, 11, 11, 11, 11, 11
};

DLGLexer::DfaState DLGLexer::st4[9] = {
  11, 6, 9, 4, 11, 6, 11, 11, 11
};

DLGLexer::DfaState DLGLexer::st5[9] = {
  11, 11, 11, 11, 11, 11, 11, 11, 11
};

DLGLexer::DfaState DLGLexer::st6[9] = {
  11, 6, 11, 6, 11, 6, 11, 11, 11
};

DLGLexer::DfaState DLGLexer::st7[9] = {
  11, 11, 11, 11, 11, 11, 11, 10, 11
};

DLGLexer::DfaState DLGLexer::st8[9] = {
  11, 11, 11, 11, 11, 11, 11, 11, 11
};

DLGLexer::DfaState DLGLexer::st9[9] = {
  11, 11, 9, 9, 11, 11, 11, 11, 11
};

DLGLexer::DfaState DLGLexer::st10[9] = {
  11, 11, 11, 11, 11, 11, 11, 11, 11
};


DLGLexer::DfaState *DLGLexer::dfa[11] = {
	st0,
	st1,
	st2,
	st3,
	st4,
	st5,
	st6,
	st7,
	st8,
	st9,
	st10
};


DLGLexer::DfaState DLGLexer::accepts[12] = {
  0, 1, 2, 3, 3, 4, 5, 6, 6, 3, 
  6, 0
};

PtrDLGLexerMemberFunc DLGLexer::actions[7] = {
	&DLGLexer::erraction,
	&DLGLexer::act1,
	&DLGLexer::act2,
	&DLGLexer::act3,
	&DLGLexer::act4,
	&DLGLexer::act5,
	&DLGLexer::act6
};

DLGLexer::DfaState DLGLexer::dfa_base[] = {
	0
};

 unsigned char *DLGLexer::b_class_no[] = {
	shift0
};

DLGChar DLGLexer::alternatives[12] = {
	1,
	0,
	1,
	1,
	1,
	0,
	1,
	1,
	0,
	1,
	0,
/* must have 0 for zzalternatives[DfaStates] */
	0
};

#include "DLexer.h"
