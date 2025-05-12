
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
		return EXP;
	}


ANTLRTokenType DLGLexer::act5()
{ 
		return ADD;
	}


ANTLRTokenType DLGLexer::act6()
{ 
		return ID;
	}


ANTLRTokenType DLGLexer::act7()
{ 
		return INT;
	}

 unsigned char DLGLexer::shift0[257] = {
  0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
  1, 2, 7, 7, 7, 7, 7, 7, 7, 7, 
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
  7, 7, 7, 1, 7, 7, 7, 7, 7, 7, 
  7, 7, 7, 7, 4, 7, 7, 7, 7, 6, 
  6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
  7, 7, 7, 7, 7, 3, 7, 7, 5, 5, 
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
  5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
  7, 7, 7, 7, 7, 7, 7
};


const int DLGLexer::MAX_MODE=1;
const int DLGLexer::DfaStates=8;
const int DLGLexer::START=0;

DLGLexer::DfaState DLGLexer::st0[8] = {
  1, 2, 3, 4, 5, 6, 7, 8
};

DLGLexer::DfaState DLGLexer::st1[8] = {
  8, 8, 8, 8, 8, 8, 8, 8
};

DLGLexer::DfaState DLGLexer::st2[8] = {
  8, 2, 8, 8, 8, 8, 8, 8
};

DLGLexer::DfaState DLGLexer::st3[8] = {
  8, 8, 8, 8, 8, 8, 8, 8
};

DLGLexer::DfaState DLGLexer::st4[8] = {
  8, 8, 8, 8, 8, 8, 8, 8
};

DLGLexer::DfaState DLGLexer::st5[8] = {
  8, 8, 8, 8, 8, 8, 8, 8
};

DLGLexer::DfaState DLGLexer::st6[8] = {
  8, 8, 8, 8, 8, 8, 8, 8
};

DLGLexer::DfaState DLGLexer::st7[8] = {
  8, 8, 8, 8, 8, 8, 7, 8
};


DLGLexer::DfaState *DLGLexer::dfa[8] = {
	st0,
	st1,
	st2,
	st3,
	st4,
	st5,
	st6,
	st7
};


DLGLexer::DfaState DLGLexer::accepts[9] = {
  0, 1, 2, 3, 4, 5, 6, 7, 0
};

PtrDLGLexerMemberFunc DLGLexer::actions[8] = {
	&DLGLexer::erraction,
	&DLGLexer::act1,
	&DLGLexer::act2,
	&DLGLexer::act3,
	&DLGLexer::act4,
	&DLGLexer::act5,
	&DLGLexer::act6,
	&DLGLexer::act7
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
	0,
	0,
	1,
/* must have 0 for zzalternatives[DfaStates] */
	0
};

#include "DLexer.cpp"
