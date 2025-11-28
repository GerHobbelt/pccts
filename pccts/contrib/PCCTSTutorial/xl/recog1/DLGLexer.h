/*
 * D L G tables
 *
 * Generated from: parser.dlg
 *
 * 1989-2001 by  Will Cohen, Terence Parr, and Hank Dietz
 * Purdue University Electrical Engineering
 * DLG Version 1.33MR33
 *
 *   ..\..\..\..\bin\dlg.exe -emsvc -CC parser.dlg
 *
 */


#ifndef DLGLexer_h
#define DLGLexer_h
/*
 * D L G L e x e r  C l a s s  D e f i n i t i o n
 *
 * Generated from: parser.dlg
 *
 * 1989-2001 by  Will Cohen, Terence Parr, and Hank Dietz
 * Purdue University Electrical Engineering
 * DLG Version 1.33MR33
 *
 *   ..\..\..\..\bin\dlg.exe -emsvc -CC parser.dlg
 *
 */


#include "DLexerBase.h"

class DLGLexer : public DLGLexerBase {
public:
public:
	static const int MAX_MODE;
	static const int DfaStates;
	static const int START;
	static const int STRING;
	typedef unsigned short DfaState;

	DLGLexer(DLGInputStream *in,
		unsigned bufsize=2000)
		: DLGLexerBase(in, bufsize, 0)
	{
	;
	}
	void	  mode(int);
	ANTLRTokenType nextTokenType(void);
	void     advance(void);
protected:
	ANTLRTokenType act1(void);
	ANTLRTokenType act2(void);
	ANTLRTokenType act3(void);
	ANTLRTokenType act4(void);
	ANTLRTokenType act5(void);
	ANTLRTokenType act6(void);
	ANTLRTokenType act7(void);
	ANTLRTokenType act8(void);
	ANTLRTokenType act9(void);
	ANTLRTokenType act10(void);
	ANTLRTokenType act11(void);
	ANTLRTokenType act12(void);
	ANTLRTokenType act13(void);
	ANTLRTokenType act14(void);
	ANTLRTokenType act15(void);
	ANTLRTokenType act16(void);
	ANTLRTokenType act17(void);
	ANTLRTokenType act18(void);
	ANTLRTokenType act19(void);
	ANTLRTokenType act20(void);
	ANTLRTokenType act21(void);
	ANTLRTokenType act22(void);
	ANTLRTokenType act23(void);
	ANTLRTokenType act24(void);
	ANTLRTokenType act25(void);
	ANTLRTokenType act26(void);
	ANTLRTokenType act27(void);
	ANTLRTokenType act28(void);
	ANTLRTokenType act29(void);
	ANTLRTokenType act30(void);
	ANTLRTokenType act31(void);
	ANTLRTokenType act32(void);
	ANTLRTokenType act33(void);
	ANTLRTokenType act34(void);
	ANTLRTokenType act35(void);
	ANTLRTokenType act36(void);
	ANTLRTokenType act37(void);
	ANTLRTokenType act38(void);
	ANTLRTokenType act39(void);
	ANTLRTokenType act40(void);
	ANTLRTokenType act41(void);
	ANTLRTokenType act42(void);
	ANTLRTokenType act43(void);
	ANTLRTokenType act44(void);
	ANTLRTokenType act45(void);
	ANTLRTokenType act46(void);
	ANTLRTokenType act47(void);
	ANTLRTokenType act48(void);
	ANTLRTokenType act49(void);
	ANTLRTokenType act50(void);
	ANTLRTokenType act51(void);
	ANTLRTokenType act52(void);
	ANTLRTokenType act53(void);
	ANTLRTokenType act54(void);
	ANTLRTokenType act55(void);
	ANTLRTokenType act56(void);
	ANTLRTokenType act57(void);
	ANTLRTokenType act58(void);
	ANTLRTokenType act59(void);
	ANTLRTokenType act60(void);
	ANTLRTokenType act61(void);
	ANTLRTokenType act62(void);
	static DfaState st0[258];
	static DfaState st1[258];
	static DfaState st2[258];
	static DfaState st3[258];
	static DfaState st4[258];
	static DfaState st5[258];
	static DfaState st6[258];
	static DfaState st7[258];
	static DfaState st8[258];
	static DfaState st9[258];
	static DfaState st10[258];
	static DfaState st11[258];
	static DfaState st12[258];
	static DfaState st13[258];
	static DfaState st14[258];
	static DfaState st15[258];
	static DfaState st16[258];
	static DfaState st17[258];
	static DfaState st18[258];
	static DfaState st19[258];
	static DfaState st20[258];
	static DfaState st21[258];
	static DfaState st22[258];
	static DfaState st23[258];
	static DfaState st24[258];
	static DfaState st25[258];
	static DfaState st26[258];
	static DfaState st27[258];
	static DfaState st28[258];
	static DfaState st29[258];
	static DfaState st30[258];
	static DfaState st31[258];
	static DfaState st32[258];
	static DfaState st33[258];
	static DfaState st34[258];
	static DfaState st35[258];
	static DfaState st36[258];
	static DfaState st37[258];
	static DfaState st38[258];
	static DfaState st39[258];
	static DfaState st40[258];
	static DfaState st41[258];
	static DfaState st42[258];
	static DfaState st43[258];
	static DfaState st44[258];
	static DfaState st45[258];
	static DfaState st46[258];
	static DfaState st47[258];
	static DfaState st48[258];
	static DfaState st49[258];
	static DfaState st50[258];
	static DfaState st51[258];
	static DfaState st52[258];
	static DfaState st53[258];
	static DfaState st54[258];
	static DfaState st55[258];
	static DfaState st56[258];
	static DfaState st57[258];
	static DfaState st58[258];
	static DfaState st59[258];
	static DfaState st60[258];
	static DfaState st61[258];
	static DfaState st62[258];
	static DfaState st63[258];
	static DfaState st64[258];
	static DfaState st65[258];
	static DfaState st66[258];
	static DfaState st67[258];
	static DfaState st68[258];
	static DfaState st69[258];
	static DfaState st70[258];
	static DfaState st71[258];
	static DfaState st72[258];
	static DfaState st73[258];
	static DfaState st74[258];
	static DfaState st75[258];
	static DfaState st76[258];
	static DfaState st77[258];
	static DfaState st78[258];
	static DfaState st79[258];
	static DfaState st80[258];
	static DfaState st81[258];
	static DfaState st82[258];
	static DfaState st83[258];
	static DfaState st84[258];
	static DfaState st85[258];
	static DfaState st86[258];
	static DfaState st87[258];
	static DfaState st88[258];
	static DfaState st89[258];
	static DfaState st90[258];
	static DfaState st91[258];
	static DfaState st92[258];
	static DfaState st93[258];
	static DfaState st94[258];
	static DfaState st95[258];
	static DfaState st96[258];
	static DfaState st97[258];
	static DfaState st98[258];
	static DfaState st99[258];
	static DfaState st100[258];
	static DfaState st101[258];
	static DfaState st102[258];
	static DfaState st103[258];
	static DfaState st104[258];
	static DfaState st105[258];
	static DfaState st106[258];
	static DfaState st107[258];
	static DfaState st108[258];
	static DfaState st109[258];
	static DfaState st110[258];
	static DfaState st111[258];
	static DfaState st112[258];
	static DfaState st113[258];
	static DfaState st114[258];
	static DfaState st115[258];
	static DfaState st116[258];
	static DfaState st117[258];
	static DfaState st118[258];
	static DfaState st119[258];
	static DfaState st120[258];
	static DfaState st121[258];
	static DfaState st122[258];
	static DfaState st123[258];
	static DfaState st124[258];
	static DfaState st125[258];
	static DfaState st126[258];
	static DfaState st127[258];
	static DfaState st128[258];
	static DfaState st129[258];
	static DfaState st130[258];
	static DfaState st131[258];
	static DfaState st132[258];
	static DfaState st133[258];
	static DfaState st134[258];
	static DfaState st135[258];
	static DfaState st136[258];
	static DfaState st137[258];
	static DfaState st138[258];
	static DfaState st139[258];
	static DfaState st140[258];
	static DfaState st141[258];
	static DfaState st142[258];
	static DfaState st143[258];
	static DfaState st144[258];
	static DfaState st145[258];
	static DfaState st146[258];
	static DfaState st147[258];
	static DfaState st148[258];
	static DfaState st149[258];
	static DfaState st150[258];
	static DfaState st151[258];
	static DfaState st152[258];
	static DfaState st153[258];
	static DfaState st154[258];
	static DfaState st155[258];
	static DfaState st156[258];
	static DfaState st157[258];
	static DfaState st158[258];
	static DfaState *dfa[159];
	static DfaState dfa_base[];
	static unsigned char *b_class_no[];
	static DfaState accepts[160];
	static DLGChar alternatives[160];
	static ANTLRTokenType (DLGLexer::*actions[63])();
	static unsigned char shift0[257];
	static unsigned char shift1[257];
	int ZZSHIFT(int c) { return 1+c; }
//
// 133MR1 Deprecated feature to allow inclusion of user-defined code in DLG class header
//
#ifdef DLGLexerIncludeFile
#include DLGLexerIncludeFile
#endif
};
typedef ANTLRTokenType (DLGLexer::*PtrDLGLexerMemberFunc)();
#endif
