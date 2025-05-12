/*
 * P: P a r s e r  S u p p o r t
 *
 * Generated from: simple.g
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
#include "P.h"

const ANTLRChar *P::tokenName(int tok)   { return _token_tbl[tok]; }

const ANTLRChar *P::_token_tbl[]={
	/* 00 */	"Invalid",
	/* 01 */	"Eof",
	/* 02 */	"Number",
	/* 03 */	"Word",
	/* 04 */	"Whitespace",
	/* 05 */	"Other",
	/* 06 */	"Newline",
	/* 07 */	"statement"
};

P::P(ANTLRTokenBuffer *input) : ANTLRParser(input,2,0,0,zzSET_SIZE /* 4 */)
{
	token_tbl = _token_tbl;
	traceOptionValueDefault=0;		// MR10 turn trace OFF
}

SetWordType P::xxx[4] = {0x2e,0x0,0x0,0x0};
SetWordType P::setwd1[8] = {0x0,0x1,0x0,0x0,0x0,0x0,0x0,
	0x0};
