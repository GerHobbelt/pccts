#ifndef STDPCCTS_H
#define STDPCCTS_H
/*
 * stdpccts.h -- P C C T S  I n c l u d e
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 *
 *   ..\..\bin\antlr.exe -emsvc -CC simple.g -glms -ge -gs -gh -e3 -cr -ga -k 2 -tab 2 -gk -w2 -rl 200000 -emsvc
 *
 */

#ifndef ANTLR_VERSION
#define ANTLR_VERSION	13333
#endif

#include "pcctscfg.h"
#include "pccts_stdio.h"
#include "tokens.h"
#include "AToken.h"
#include "ATokenBuffer.h"
static const unsigned LL_K=2;
#include "AParser.h"
#include "P.h"
#include "DLexerBase.h"
#endif
