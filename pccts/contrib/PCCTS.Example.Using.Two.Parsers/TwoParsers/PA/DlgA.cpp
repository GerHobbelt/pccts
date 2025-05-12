/*
 * D L G tables
 *
 * Generated from: Pa\parser.dlg
 *
 * 1989-2001 by  Will Cohen, Terence Parr, and Hank Dietz
 * Purdue University Electrical Engineering
 * DLG Version 1.33MR33
 *
 *   ..\..\..\bin\dlg.exe -emsvc -CC -C2 Pa\parser.dlg -o Pa -cl DlgA
 *
 */



/* parser.dlg -- DLG Description of scanner
 *
 * Generated from: Pa\A.g
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 *
 *   ..\..\..\bin\antlr.exe -emsvc -CC Pa\A.g -glms -o Pa
 *
 */

#define ANTLR_VERSION	13333
#include "tokens.h"
#include "AToken.h"

#include "pcctscfg.h"
#include "pccts_stdio.h"

#include "AParser.h"
#include "DLexerBase.h"
#include "DlgA.h"

ANTLRTokenType DlgA::act1()
{ 
		return Eof;
	}


ANTLRTokenType DlgA::act2()
{ 
		return Number;
	}


ANTLRTokenType DlgA::act3()
{ 
		return Word;
	}


ANTLRTokenType DlgA::act4()
{ 
    skip();   
		return Whitespace;
	}


ANTLRTokenType DlgA::act5()
{ 
		return Other;
	}


ANTLRTokenType DlgA::act6()
{ 
    newline(); skip();   
		return Newline;
	}

 unsigned char DlgA::shift0[257] = {
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


const int DlgA::MAX_MODE=1;
const int DlgA::DfaStates=11;
const int DlgA::START=0;

DlgA::DfaState DlgA::st0[9] = {
  1, 2, 3, 4, 5, 6, 7, 8, 11
};

DlgA::DfaState DlgA::st1[9] = {
  11, 11, 11, 11, 11, 11, 11, 11, 11
};

DlgA::DfaState DlgA::st2[9] = {
  11, 2, 11, 6, 11, 6, 11, 11, 11
};

DlgA::DfaState DlgA::st3[9] = {
  11, 11, 9, 9, 11, 11, 11, 11, 11
};

DlgA::DfaState DlgA::st4[9] = {
  11, 6, 9, 4, 11, 6, 11, 11, 11
};

DlgA::DfaState DlgA::st5[9] = {
  11, 11, 11, 11, 11, 11, 11, 11, 11
};

DlgA::DfaState DlgA::st6[9] = {
  11, 6, 11, 6, 11, 6, 11, 11, 11
};

DlgA::DfaState DlgA::st7[9] = {
  11, 11, 11, 11, 11, 11, 11, 10, 11
};

DlgA::DfaState DlgA::st8[9] = {
  11, 11, 11, 11, 11, 11, 11, 11, 11
};

DlgA::DfaState DlgA::st9[9] = {
  11, 11, 9, 9, 11, 11, 11, 11, 11
};

DlgA::DfaState DlgA::st10[9] = {
  11, 11, 11, 11, 11, 11, 11, 11, 11
};


DlgA::DfaState *DlgA::dfa[11] = {
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


DlgA::DfaState DlgA::accepts[12] = {
  0, 1, 2, 3, 3, 4, 5, 6, 6, 3, 
  6, 0
};

PtrDlgAMemberFunc DlgA::actions[7] = {
	&DlgA::erraction,
	&DlgA::act1,
	&DlgA::act2,
	&DlgA::act3,
	&DlgA::act4,
	&DlgA::act5,
	&DlgA::act6
};

DlgA::DfaState DlgA::dfa_base[] = {
	0
};

 unsigned char *DlgA::b_class_no[] = {
	shift0
};

DLGChar DlgA::alternatives[12] = {
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

#define DLGLexer DlgA
#include "DLexer.h"
