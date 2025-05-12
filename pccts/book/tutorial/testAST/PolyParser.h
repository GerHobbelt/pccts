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
class ASTBase;
#include "AParser.h"

class PolyParser : public ANTLRParser {
protected:
	static ANTLRChar *_token_tbl[];
private:
	static SetWordType err1[4];
	static SetWordType err2[4];
	static SetWordType err3[4];
	static SetWordType setwd1[11];
	static SetWordType err4[4];
	static SetWordType setwd2[11];
private:
	void zzdflthandlers( int _signal, int *_retsignal );

public:
	PolyParser(ANTLRTokenBuffer *input);
	void interp(ASTBase **_root);
	void assign(ASTBase **_root);
	void poly(ASTBase **_root);
	void term(ASTBase **_root);
	void bigterm(ASTBase **_root);
	void coefficient(ASTBase **_root);
	void reg(ASTBase **_root);
	void exp(ASTBase **_root);
};

#endif /* PolyParser_h */
