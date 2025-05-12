/*
 * XLParser: P a r s e r  H e a d e r 
 *
 * Generated from: xl.g
 *
 * Terence Parr, Russell Quong, Will Cohen, and Hank Dietz: 1989-2001
 * Parr Research Corporation
 * with Purdue University Electrical Engineering
 * with AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 */

#ifndef XLParser_h
#define XLParser_h

#ifndef ANTLR_VERSION
#define ANTLR_VERSION 13333
#endif

#include "AParser.h"


// any definitions that you need in the generated files
class XLParser : public ANTLRParser {
public:
	static  const ANTLRChar *tokenName(int tk);
	enum { SET_SIZE = 68 };
protected:
	static const ANTLRChar *_token_tbl[];
private:
#line 133 "xl.g"

// parser definitions go here

public:
void init()
{
  ANTLRParser::init();
  // any specific initialization you need
  // (if none, don't override the init() method
}
protected:
	static SetWordType err1[zzSET_SIZE /* 12 */];
	static SetWordType err2[zzSET_SIZE /* 12 */];
	static SetWordType setwd1[68];
	static SetWordType STRING_LITERAL_set[zzSET_SIZE /* 12 */];
	static SetWordType STRING_LITERAL_errset[zzSET_SIZE /* 12 */];
	static SetWordType err5[zzSET_SIZE /* 12 */];
	static SetWordType err6[zzSET_SIZE /* 12 */];
	static SetWordType err7[zzSET_SIZE /* 12 */];
	static SetWordType err8[zzSET_SIZE /* 12 */];
	static SetWordType err9[zzSET_SIZE /* 12 */];
	static SetWordType setwd2[68];
	static SetWordType err10[zzSET_SIZE /* 12 */];
	static SetWordType err11[zzSET_SIZE /* 12 */];
	static SetWordType err12[zzSET_SIZE /* 12 */];
	static SetWordType setwd3[68];
	static SetWordType err13[zzSET_SIZE /* 12 */];
	static SetWordType err14[zzSET_SIZE /* 12 */];
	static SetWordType setwd4[68];
	static SetWordType err15[zzSET_SIZE /* 12 */];
	static SetWordType err16[zzSET_SIZE /* 12 */];
	static SetWordType setwd5[68];
	static SetWordType err17[zzSET_SIZE /* 12 */];
	static SetWordType err18[zzSET_SIZE /* 12 */];
	static SetWordType err19[zzSET_SIZE /* 12 */];
	static SetWordType err20[zzSET_SIZE /* 12 */];
	static SetWordType err21[zzSET_SIZE /* 12 */];
	static SetWordType setwd6[68];
	static SetWordType ADD_OP_set[zzSET_SIZE /* 12 */];
	static SetWordType ADD_OP_errset[zzSET_SIZE /* 12 */];
	static SetWordType MULT_OP_set[zzSET_SIZE /* 12 */];
	static SetWordType MULT_OP_errset[zzSET_SIZE /* 12 */];
	static SetWordType RELATIONAL_OP_set[zzSET_SIZE /* 12 */];
	static SetWordType RELATIONAL_OP_errset[zzSET_SIZE /* 12 */];
	static SetWordType setwd7[68];
	static SetWordType BOOLEAN_OP_set[zzSET_SIZE /* 12 */];
	static SetWordType BOOLEAN_OP_errset[zzSET_SIZE /* 12 */];
	static SetWordType setwd8[68];
private:
	void zzdflthandlers( int _signal, int *_retsignal );

public:
	XLParser(ANTLRTokenBuffer *input);
	void program(void);
	void subprogramBody(void);
	void basicDecl(void);
	void varDecl(void);
	void constDecl(void);
	void identList(void);
	void constantValue(void);
	void typeDecl(void);
	void arrayDecl(void);
	void integerConstant(void);
	void recordDecl(void);
	void typeName(void);
	void procedureDecl(void);
	void formalParameters(void);
	void parameterSpec(void);
	void statement(void);
	void assignmentStatement(void);
	void exitStatement(void);
	void procedureCallStatement(void);
	void actualParameters(void);
	void returnStatement(void);
	void ifStatement(void);
	void ifPart(void);
	void loopStatement(void);
	void endStatement(void);
	void variableReference(void);
	void ioStatement(void);
	void primitiveElement(void);
	void booleanNegationExpression(void);
	void signExpression(void);
	void multiplyingExpression(void);
	void addingExpression(void);
	void relationalExpression(void);
	void expression(void);
};

#endif /* XLParser_h */
