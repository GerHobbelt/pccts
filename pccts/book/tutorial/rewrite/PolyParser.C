/*
 * PolyParser: P a r s e r  S u p p o r t
 *
 * Generated from: poly.g
 *
 * Terence Parr, Russell Quong, Will Cohen, and Hank Dietz: 1989-1995
 * Parr Research Corporation
 * with Purdue University Electrical Engineering
 * with AHPCRC, University of Minnesota
 * ANTLR Version 1.32b6
 */

#include <stdio.h>
#define ANTLR_VERSION	132b6
#include "tokens.h"
#include "PolyParser.h"

ANTLRChar *PolyParser::_token_tbl[]={
	/* 00 */	"Invalid",
	/* 01 */	"@",
	/* 02 */	"[\\ \\t]+",
	/* 03 */	"\\n",
	/* 04 */	"EXP",
	/* 05 */	"ADD",
	/* 06 */	"MULT",
	/* 07 */	"INT",
	/* 08 */	"ID"
};

PolyParser::PolyParser(ANTLRTokenBuffer *input) : ANTLRParser(input,1,0,0,4)
{
	token_tbl = _token_tbl;
}

SetWordType PolyParser::err1[4] = {0x80,0x1,0x0,0x0};
SetWordType PolyParser::err2[4] = {0x32,0x0,0x0,0x0};
SetWordType PolyParser::err3[4] = {0x22,0x1,0x0,0x0};
SetWordType PolyParser::setwd1[9] = {0x0,0xff,0x0,0x0,0x40,0xfe,0x0,
	0x0,0x20};
