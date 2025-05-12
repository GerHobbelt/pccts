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
	/* 06 */	"=",
	/* 07 */	";",
	/* 08 */	"\\+",
	/* 09 */	"^"
};

PolyParser::PolyParser(ANTLRTokenBuffer *input) : ANTLRParser(input,1,0,0,4)
{
	token_tbl = _token_tbl;
}

SetWordType PolyParser::err1[4] = {0x80,0x3,0x0,0x0};
SetWordType PolyParser::err2[4] = {0x90,0x1,0x0,0x0};
SetWordType PolyParser::err3[4] = {0x80,0x3,0x0,0x0};
SetWordType PolyParser::err4[4] = {0x30,0x0,0x0,0x0};
SetWordType PolyParser::err5[4] = {0x30,0x0,0x0,0x0};
SetWordType PolyParser::setwd1[10] = {0x0,0x1,0x0,0x0,0x40,0x0,0x0,
	0xfe,0xfc,0x80};
SetWordType PolyParser::setwd2[10] = {0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x1,0x1,0x0};
