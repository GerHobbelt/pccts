/*
 * ParserB: P a r s e r  S u p p o r t
 *
 * Generated from: Pb\B.g
 *
 * Terence Parr, Russell Quong, Will Cohen, and Hank Dietz: 1989-2001
 * Parr Research Corporation
 * with Purdue University Electrical Engineering
 * with AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 */

#define ANTLR_VERSION	13333
#include "pcctscfg.h"
#include "pccts_stdio.h"
#define ANTLR_SUPPORT_CODE
#include "tokens.h"
#include "ParserB.h"

const ANTLRChar *ParserB::tokenName(int tok)   { return _token_tbl[tok]; }

const ANTLRChar *ParserB::_token_tbl[]={
	/* 00 */	"Invalid",
	/* 01 */	"Eof",
	/* 02 */	"Number",
	/* 03 */	"Word",
	/* 04 */	"Whitespace",
	/* 05 */	"Other",
	/* 06 */	"Newline"
};

ParserB::ParserB(ANTLRTokenBuffer *input) : ANTLRParser(input,1,0,0,zzSET_SIZE /* 4 */)
{
	token_tbl = _token_tbl;
	traceOptionValueDefault=0;		// MR10 turn trace OFF
}

SetWordType ParserB::setwd1[7] = {0x0,0x2,0x1,0x1,0x0,0x1,0x0};
