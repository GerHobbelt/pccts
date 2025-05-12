/*
 * PolyParser: P a r s e r  H e a d e r 
 *
 * Generated from: poly.g
 *
 * Terence Parr, Russell Quong, Will Cohen, and Hank Dietz: 1989-1995
 * Parr Research Corporation
 * with Purdue University Electrical Engineering
 * with AHPCRC, University of Minnesota
 * ANTLR Version 1.33
 */

#ifndef PolyParser_h
#define PolyParser_h
#include "AParser.h"

class PolyParser : public ANTLRParser {
protected:
	static ANTLRChar *_token_tbl[];
private:

protected:
virtual void store(char *reg, float v) {;}
virtual float value(char *reg) {;}
	static SetWordType err1[4];
	static SetWordType err2[4];
	static SetWordType err3[4];
	static SetWordType err4[4];
	static SetWordType err5[4];
	static SetWordType setwd1[10];
	static SetWordType setwd2[10];
private:
	void zzdflthandlers( int _signal, int *_retsignal );

public:
	PolyParser(ANTLRTokenBuffer *input);
	void interp(void);
	 float   poly(void);
	 float   term(void);
	 float   coefficient(void);
	 float   reg(void);
	 float   exp(void);
};

#endif /* PolyParser_h */
