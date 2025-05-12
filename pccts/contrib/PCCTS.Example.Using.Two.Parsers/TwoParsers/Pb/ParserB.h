/*
 * ParserB: P a r s e r  H e a d e r 
 *
 * Generated from: Pb\B.g
 *
 * Terence Parr, Russell Quong, Will Cohen, and Hank Dietz: 1989-2001
 * Parr Research Corporation
 * with Purdue University Electrical Engineering
 * with AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 */

#ifndef ParserB_h
#define ParserB_h

#ifndef ANTLR_VERSION
#define ANTLR_VERSION 13333
#endif

#include "AParser.h"

class ParserB : public ANTLRParser {
public:
	static  const ANTLRChar *tokenName(int tk);
	enum { SET_SIZE = 7 };
protected:
	static const ANTLRChar *_token_tbl[];
private:
protected:
	static SetWordType setwd1[7];
private:
	void zzdflthandlers( int _signal, int *_retsignal );

public:
	ParserB(ANTLRTokenBuffer *input);
	void statement(void);
};

#endif /* ParserB_h */
