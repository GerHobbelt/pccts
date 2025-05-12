#ifndef DLGLexer_h
#define DLGLexer_h
/*
 * D L G L e x e r  C l a s s  D e f i n i t i o n
 *
 * Generated from: parser.dlg
 *
 * 1989-1994 by  Will Cohen, Terence Parr, and Hank Dietz
 * Purdue University Electrical Engineering
 * DLG Version 1.33
 */


#include "DLexerBase.h"

class DLGLexer : public DLGLexerBase {
public:
	static const int MAX_MODE;
	static const int DfaStates;
	static const int START;
	typedef unsigned char DfaState;

	DLGLexer(DLGInputStream *in,
		unsigned bufsize=2000)
		: DLGLexerBase(in, bufsize, 1)
	{
	;
	}
	void	mode(int);
	ANTLRTokenType nextTokenType(void);
	void	advance(void);
protected:
	ANTLRTokenType act1();
	ANTLRTokenType act2();
	ANTLRTokenType act3();
	ANTLRTokenType act4();
	ANTLRTokenType act5();
	ANTLRTokenType act6();
	ANTLRTokenType act7();
	static DfaState st0[8];
	static DfaState st1[8];
	static DfaState st2[8];
	static DfaState st3[8];
	static DfaState st4[8];
	static DfaState st5[8];
	static DfaState st6[8];
	static DfaState st7[8];
	static DfaState *dfa[8];
	static DfaState dfa_base[];
	static unsigned char *b_class_no[];
	static DfaState accepts[9];
	static DLGChar alternatives[9];
	static ANTLRTokenType (DLGLexer::*actions[8])();
	static unsigned char shift0[257];
	int ZZSHIFT(int c) { return b_class_no[automaton][1+c]; }
};
typedef ANTLRTokenType (DLGLexer::*PtrDLGLexerMemberFunc)();
#endif
