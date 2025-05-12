/*
 * A n t l r  T r a n s l a t i o n  H e a d e r
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-1994
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.32b6
 */
#include <stdio.h>
#define ANTLR_VERSION	132b6
#include "tokens.h"
#include "ASTBase.h"

#include "AParser.h"
#include "PolyParser.h"
#include "DLexerBase.h"

#include "PBlackBox.h"
#include "DLGLexer.h"
typedef ANTLRCommonToken ANTLRToken;

#include "AST.h"
#include "DiffPoly.h"
#include "SimplifyPoly.h"
#include "PrintPoly.h"

main()
{
	ParserBlackBox<DLGLexer, PolyParser, ANTLRToken> p(stdin);
	ASTBase *root = NULL;
	p.parser()->poly(&root);
	//	root->preorder();
	//	printf("\n");
}
typedef ANTLRToken *ANTLRTokenPtr;

void
PolyParser::poly(ASTBase **_root)
{
	zzRULE;
	ASTBase **_astp, *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	
	DiffPoly dp;
	AST *result=NULL, *nresult=NULL;
	PrintPoly pp;
	SimplifyPoly sp;
	_ast = NULL;
	term(&_ast);
	if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
	_ast11 = (AST *)_ast;
	ASTBase::link(_root, &_sibling, &_tail);
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL,*_ast22=NULL;
		while ( (LA(1)==ADD) ) {
			zzmatch(ADD); _t21 = (ANTLRToken *)LT(1);
			
			_ast21 = new AST(_t21);
			_ast21->subroot(_root, &_sibling, &_tail);
			 consume();
			_ast = NULL;
			term(&_ast);
			if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
			_ast22 = (AST *)_ast;
			ASTBase::link(_root, &_sibling, &_tail);
		}
	}
	
	(*_root)->preorder();
	printf("\n");
	dp.poly((SORASTBase **)&((*_root)), (SORASTBase **)&result);
	result->preorder();
	printf("\n");
	sp.poly((SORASTBase **)&result, (SORASTBase **)&nresult);
	nresult->preorder();
	printf("\n");
	pp.poly((SORASTBase **)&nresult);
	printf("\n");
	return;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x1);
}

void
PolyParser::term(ASTBase **_root)
{
	zzRULE;
	ASTBase **_astp, *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	if ( (LA(1)==INT) ) {
		_ast = NULL;
		bigterm(&_ast);
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	}
	else {
		if ( (LA(1)==ID) ) {
			_ast = NULL;
			reg(&_ast);
			if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
			_ast11 = (AST *)_ast;
			ASTBase::link(_root, &_sibling, &_tail);
			{
				ANTLRTokenPtr _t21=NULL,_t22=NULL;
				AST *_ast21=NULL,*_ast22=NULL;
				if ( (LA(1)==EXP) ) {
					zzmatch(EXP); _t21 = (ANTLRToken *)LT(1);
					
					_ast21 = new AST(_t21);
					_ast21->subroot(_root, &_sibling, &_tail);
					 consume();
					zzmatch(INT); _t22 = (ANTLRToken *)LT(1);
					
					_ast22 = new AST(_t22);
					_ast22->subchild(_root, &_sibling, &_tail);
					 consume();
				}
			}
		}
		else {FAIL(1,err1,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	return;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x2);
}

void
PolyParser::bigterm(ASTBase **_root)
{
	zzRULE;
	ASTBase **_astp, *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	ANTLRTokenPtr c=NULL, r=NULL, e=NULL;
	AST *c_ast=NULL, *r_ast=NULL, *e_ast=NULL;
	_ast = NULL;
	coefficient(&_ast);
	_ast11 = (AST *)_ast;
	c_ast = _ast11;
	{
		AST *_ast21=NULL;
		if ( (LA(1)==ID) ) {
			_ast = NULL;
			reg(&_ast);
			_ast21 = (AST *)_ast;
			r_ast = _ast21;
			{
				ANTLRTokenPtr _t31=NULL;
				AST *_ast31=NULL,*_ast32=NULL;
				if ( (LA(1)==EXP) ) {
					zzmatch(EXP); _t31 = (ANTLRToken *)LT(1);
					 consume();
					_ast = NULL;
					exp(&_ast);
					_ast32 = (AST *)_ast;
					e_ast = _ast32;
					(*_root) = ASTBase::tmake((new AST(MULT,"MULT")), c_ast, ASTBase::tmake((new AST(EXP,"EXP")), r_ast, e_ast, NULL), NULL);  
				}
				else {
					if ( (setwd1[LA(1)]&0x4) ) {
						(*_root) = ASTBase::tmake((new AST(MULT,"MULT")), c_ast, r_ast, NULL);  
					}
					else {FAIL(1,err2,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
				}
			}
		}
		else {
			if ( (setwd1[LA(1)]&0x8) ) {
				(*_root) = c_ast;  
			}
			else {FAIL(1,err3,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
		}
	}
	return;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x10);
}

void
PolyParser::coefficient(ASTBase **_root)
{
	zzRULE;
	ASTBase **_astp, *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	zzmatch(INT); _t11 = (ANTLRToken *)LT(1);
	
	_ast11 = new AST(_t11);
	_ast11->subchild(_root, &_sibling, &_tail);
	 consume();
	return;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x20);
}

void
PolyParser::reg(ASTBase **_root)
{
	zzRULE;
	ASTBase **_astp, *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	zzmatch(ID); _t11 = (ANTLRToken *)LT(1);
	
	_ast11 = new AST(_t11);
	_ast11->subchild(_root, &_sibling, &_tail);
	 consume();
	return;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x40);
}

void
PolyParser::exp(ASTBase **_root)
{
	zzRULE;
	ASTBase **_astp, *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	zzmatch(INT); _t11 = (ANTLRToken *)LT(1);
	
	_ast11 = new AST(_t11);
	_ast11->subchild(_root, &_sibling, &_tail);
	 consume();
	return;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x80);
}
