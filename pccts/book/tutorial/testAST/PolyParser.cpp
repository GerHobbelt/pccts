/*
 * PolyParser: P a r s e r  S u p p o r t
 *
 * Generated from: poly.g
 *
 * Terence Parr, Russell Quong, Will Cohen, and Hank Dietz: 1989-1995
 * Parr Research Corporation
 * with Purdue University Electrical Engineering
 * with AHPCRC, University of Minnesota
 * ANTLR Version 1.33
 */

#include <stdio.h>
#define ANTLR_VERSION	133
#define ANTLR_SUPPORT_CODE
#include "tokens.h"
#include "PolyParser.h"

ANTLRChar *PolyParser::_token_tbl[]={
	/* 00 */	"Invalid",
	/* 01 */	"@",
	/* 02 */	"[\\ \\t]+",
	/* 03 */	"\\n",
	/* 04 */	"ID",
	/* 05 */	"FLOAT",
	/* 06 */	"EXP",
	/* 07 */	"MULT",
	/* 08 */	"=",
	/* 09 */	";",
	/* 10 */	"\\+"
};

PolyParser::PolyParser(ANTLRTokenBuffer *input) : ANTLRParser(input,1,0,0,4)
{
	token_tbl = _token_tbl;
}

SetWordType PolyParser::err1[4] = {0x30,0x0,0x0,0x0};
SetWordType PolyParser::err2[4] = {0x40,0x6,0x0,0x0};
SetWordType PolyParser::err3[4] = {0x10,0x6,0x0,0x0};
SetWordType PolyParser::setwd1[11] = {0x0,0x3,0x0,0x0,0x82,0x0,0x0,
	0x0,0x0,0xfc,0xf8};
SetWordType PolyParser::err4[4] = {0x30,0x0,0x0,0x0};
SetWordType PolyParser::setwd2[11] = {0x0,0x0,0x0,0x0,0x0,0x0,0x1,
	0x0,0x0,0x3,0x3};
