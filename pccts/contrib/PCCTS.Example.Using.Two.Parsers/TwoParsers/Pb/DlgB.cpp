/*
 * D L G tables
 *
 * Generated from: Pb\parser.dlg
 *
 * 1989-2001 by  Will Cohen, Terence Parr, and Hank Dietz
 * Purdue University Electrical Engineering
 * DLG Version 1.33MR33
 *
 *   ..\..\..\bin\dlg.exe -emsvc -CC -C2 Pb\parser.dlg -o Pb -cl DlgB
 *
 */



/* parser.dlg -- DLG Description of scanner
 *
 * Generated from: Pb\B.g
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 *
 *   ..\..\..\bin\antlr.exe -emsvc -CC Pb\B.g -glms -o Pb
 *
 */

#define ANTLR_VERSION	13333
#include "tokens.h"
#include "AToken.h"

#include "pcctscfg.h"
#include "pccts_stdio.h"

#include "AParser.h"
#include "DLexerBase.h"
#include "DlgB.h"

ANTLRTokenType DlgB::act1()
{ 
		return Eof;
	}


ANTLRTokenType DlgB::act2()
{ 
		return Number;
	}


ANTLRTokenType DlgB::act3()
{ 
		return Word;
	}


ANTLRTokenType DlgB::act4()
{ 
    skip();   
		return Whitespace;
	}


ANTLRTokenType DlgB::act5()
{ 
		return Other;
	}


ANTLRTokenType DlgB::act6()
{ 
    newline(); skip();   
		return Newline;
	}

 unsigned char DlgB::shift0[257] = {
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


const int DlgB::MAX_MODE=1;
const int DlgB::DfaStates=11;
const int DlgB::START=0;

DlgB::DfaState DlgB::st0[9] = {
  1, 2, 3, 4, 5, 6, 7, 8, 11
};

DlgB::DfaState DlgB::st1[9] = {
  11, 11, 11, 11, 11, 11, 11, 11, 11
};

DlgB::DfaState DlgB::st2[9] = {
  11, 2, 11, 6, 11, 6, 11, 11, 11
};

DlgB::DfaState DlgB::st3[9] = {
  11, 11, 9, 9, 11, 11, 11, 11, 11
};

DlgB::DfaState DlgB::st4[9] = {
  11, 6, 9, 4, 11, 6, 11, 11, 11
};

DlgB::DfaState DlgB::st5[9] = {
  11, 11, 11, 11, 11, 11, 11, 11, 11
};

DlgB::DfaState DlgB::st6[9] = {
  11, 6, 11, 6, 11, 6, 11, 11, 11
};

DlgB::DfaState DlgB::st7[9] = {
  11, 11, 11, 11, 11, 11, 11, 10, 11
};

DlgB::DfaState DlgB::st8[9] = {
  11, 11, 11, 11, 11, 11, 11, 11, 11
};

DlgB::DfaState DlgB::st9[9] = {
  11, 11, 9, 9, 11, 11, 11, 11, 11
};

DlgB::DfaState DlgB::st10[9] = {
  11, 11, 11, 11, 11, 11, 11, 11, 11
};


DlgB::DfaState *DlgB::dfa[11] = {
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


DlgB::DfaState DlgB::accepts[12] = {
  0, 1, 2, 3, 3, 4, 5, 6, 6, 3, 
  6, 0
};

PtrDlgBMemberFunc DlgB::actions[7] = {
	&DlgB::erraction,
	&DlgB::act1,
	&DlgB::act2,
	&DlgB::act3,
	&DlgB::act4,
	&DlgB::act5,
	&DlgB::act6
};

DlgB::DfaState DlgB::dfa_base[] = {
	0
};

 unsigned char *DlgB::b_class_no[] = {
	shift0
};

DLGChar DlgB::alternatives[12] = {
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

#define DLGLexer DlgB
#include "DLexer.h"
