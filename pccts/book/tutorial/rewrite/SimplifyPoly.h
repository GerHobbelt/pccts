#ifndef SimplifyPoly_h
#define SimplifyPoly_h
/*
 * S O R C E R E R  T r a n s l a t i o n  H e a d e r
 *
 * SORCERER Developed by Terence Parr, Aaron Sawdey, & Gary Funck
 * Parr Research Corporation, Intrepid Technology, University of Minnesota
 * 1992-1994
 * SORCERER Version 1.00B15
 */
#include "STreeParser.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "tokens.h"
#include "AToken.h"
typedef ANTLRCommonToken ANTLRToken;
#include "AST.h"
typedef AST SORAST;

class SimplifyPoly : public STreeParser {
protected:
public:
	SimplifyPoly();

	void poly(SORASTBase **_root, SORASTBase **_result);
};

#endif /* SimplifyPoly_h */
