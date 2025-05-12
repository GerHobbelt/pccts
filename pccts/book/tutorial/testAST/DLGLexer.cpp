
/* parser.dlg -- DLG Description of scanner
 *
 * Generated from: poly.g
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-1994
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33
 */

#include "tokens.h"
#include "AToken.h"
#include "ASTBase.h"
/*
 * D L G tables
 *
 * Generated from: parser.dlg
 *
 * 1989-1994 by  Will Cohen, Terence Parr, and Hank Dietz
 * Purdue University Electrical Engineering
 * DLG Version 1.33
 */

#include <stdio.h>

#include "AParser.h"
#include "DLexerBase.h"
#include "DLGLexer.h"

ANTLRTokenType DLGLexer::act1()
{ 
		return (ANTLRTokenType)1;
	}


ANTLRTokenType DLGLexer::act2()
{ 
		skip();  
		return (ANTLRTokenType)2;
	}


ANTLRTokenType DLGLexer::act3()
{ 
		skip(); newline();  
		return (ANTLRTokenType)3;
	}


ANTLRTokenType DLGLexer::act4()
{ 
		return ID;
	}


ANTLRTokenType DLGLexer::act5()
{ 
		return FLOAT;
	}


ANTLRTokenType DLGLexer::act6()
{ 
		return EXP;
	}


ANTLRTokenType DLGLexer::act7()
{ 
		return (ANTLRTokenType)8;
	}


ANTLRTokenType DLGLexer::act8()
{ 
		return (ANTLRTokenType)9;
	}


ANTLRTokenType DLGLexer::act9()
{ 
		return (ANTLRTokenType)10;
	}

 unsigned char DLGLexer::shift0[257] = {
  0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
  1, 2, 10, 10, 10, 10, 10, 10, 10, 10, 
  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
  10, 10, 10, 1, 10, 10, 10, 10, 10, 10, 
  10, 10, 10, 10, 9, 10, 10, 5, 10, 4, 
  4, 4, 4, 4, 4, 4, 4, 4, 4, 10, 
  8, 10, 7, 10, 10, 10, 10, 10, 10, 10, 
  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
  10, 10, 10, 10, 10, 6, 10, 10, 3, 3, 
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
  3, 3, 3, 3, 10, 10, 10, 10, 10, 10, 
  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
  10, 10, 10, 10, 10, 10, 10
};


const int DLGLexer::MAX_MODE=1;
const int DLGLexer::DfaStates=12;
const int DLGLexer::START=0;

DLGLexer::DfaState DLGLexer::st0[11] = {
  1, 2, 3, 4, 5, 12, 6, 7, 8, 9, 
  12
};

DLGLexer::DfaState DLGLexer::st1[11] = {
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12
};

DLGLexer::DfaState DLGLexer::st2[11] = {
  12, 2, 12, 12, 12, 12, 12, 12, 12, 12, 
  12
};

DLGLexer::DfaState DLGLexer::st3[11] = {
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12
};

DLGLexer::DfaState DLGLexer::st4[11] = {
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12
};

DLGLexer::DfaState DLGLexer::st5[11] = {
  12, 12, 12, 12, 5, 10, 12, 12, 12, 12, 
  12
};

DLGLexer::DfaState DLGLexer::st6[11] = {
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12
};

DLGLexer::DfaState DLGLexer::st7[11] = {
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12
};

DLGLexer::DfaState DLGLexer::st8[11] = {
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12
};

DLGLexer::DfaState DLGLexer::st9[11] = {
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12
};

DLGLexer::DfaState DLGLexer::st10[11] = {
  12, 12, 12, 12, 11, 12, 12, 12, 12, 12, 
  12
};

DLGLexer::DfaState DLGLexer::st11[11] = {
  12, 12, 12, 12, 11, 12, 12, 12, 12, 12, 
  12
};


DLGLexer::DfaState *DLGLexer::dfa[12] = {
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
	st10,
	st11
};


DLGLexer::DfaState DLGLexer::accepts[13] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 
  0, 5, 0
};

PtrDLGLexerMemberFunc DLGLexer::actions[10] = {
	&DLGLexer::erraction,
	&DLGLexer::act1,
	&DLGLexer::act2,
	&DLGLexer::act3,
	&DLGLexer::act4,
	&DLGLexer::act5,
	&DLGLexer::act6,
	&DLGLexer::act7,
	&DLGLexer::act8,
	&DLGLexer::act9
};

DLGLexer::DfaState DLGLexer::dfa_base[] = {
	0
};

 unsigned char *DLGLexer::b_class_no[] = {
	shift0
};

DLGChar DLGLexer::alternatives[DLGLexer::DfaStates+1] = {
	1,
	0,
	1,
	0,
	0,
	1,
	0,
	0,
	0,
	0,
	1,
	1,
/* must have 0 for zzalternatives[DfaStates] */
	0
};

#include "DLexer.cpp"
