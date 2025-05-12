/*
 * P: P a r s e r  H e a d e r 
 *
 * Generated from: simple.g
 *
 * Terence Parr, Russell Quong, Will Cohen, and Hank Dietz: 1989-2001
 * Parr Research Corporation
 * with Purdue University Electrical Engineering
 * with AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 */

#ifndef P_h
#define P_h

#ifndef ANTLR_VERSION
#define ANTLR_VERSION 13333
#endif

#include "AParser.h"

class P : public ANTLRParser {
public:
	static  const ANTLRChar *tokenName(int tk);
	enum { SET_SIZE = 8 };
protected:
	static const ANTLRChar *_token_tbl[];
private:
protected:
	static SetWordType xxx[zzSET_SIZE /* 4 */];
	static SetWordType setwd1[8];
private:
	void zzdflthandlers( int _signal, int *_retsignal );

public:
	P(ANTLRTokenBuffer *input);
	void statement(void);
};

#endif /* P_h */
