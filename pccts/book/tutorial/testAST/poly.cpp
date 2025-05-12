/*
 * A n t l r  T r a n s l a t i o n  H e a d e r
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-1994
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33
 */
#include <stdio.h>
#define ANTLR_VERSION	133
#include "tokens.h"
#include "ASTBase.h"

#include "AParser.h"
#include "PolyParser.h"
#include "DLexerBase.h"
#include "ATokPtr.h"
#ifndef PURIFY
#define PURIFY(r,s)
#endif

#include "PBlackBox.h"
#include "DLGLexer.h"
typedef ANTLRCommonToken ANTLRToken;

#include "AST.h"

main()
{
	ParserBlackBox<DLGLexer, PolyParser, ANTLRToken> p(stdin);
	ASTBase *root = NULL;
	p.parser()->interp(&root);
}

void
PolyParser::interp(ASTBase **_root)
{
	zzRULE;
	ASTBase **_astp, *_ast = NULL, *_sibling = NULL, *_tail = NULL;
;
	ANTLRTokenPtr a=NULL;
	AST *a_ast=NULL;
	{
		AST *_ast21=NULL;
		int zzcnt=1;
		do {
			_ast = NULL;
			assign(&_ast);
			_ast21 = (AST *)_ast;
			a_ast = _ast21;
		} while ( (LA(1)==ID) );
	}
	return;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x1);
}

void
PolyParser::assign(ASTBase **_root)
{
	zzRULE;
	ASTBase **_astp, *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL,_t12=NULL,_t14=NULL;
	AST *_ast11=NULL,*_ast12=NULL,*_ast13=NULL,*_ast14=NULL;
	zzmatch(ID); _t11 = (ANTLRTokenPtr)LT(1);

	
	_ast11 = new AST(_t11);
	_ast11->subchild(_root, &_sibling, &_tail);
	 consume();
	zzmatch(8); _t12 = (ANTLRTokenPtr)LT(1);

	
	_ast12 = new AST(_t12);
	_ast12->subroot(_root, &_sibling, &_tail);
	 consume();
	_ast = NULL;
	poly(&_ast);
	if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
	_ast13 = (AST *)_ast;
	ASTBase::link(_root, &_sibling, &_tail);
	zzmatch(9); _t14 = (ANTLRTokenPtr)LT(1);

	 
	(*_root)->preorder(); printf("\n");  
 consume();
	return;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x2);
}

void
PolyParser::poly(ASTBase **_root)
{
	zzRULE;
	ASTBase **_astp, *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	_ast = NULL;
	term(&_ast);
	if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
	_ast11 = (AST *)_ast;
	ASTBase::link(_root, &_sibling, &_tail);
	{
		ANTLRTokenPtr _t21=NULL;
		AST *_ast21=NULL,*_ast22=NULL;
		while ( (LA(1)==10) ) {
			zzmatch(10); _t21 = (ANTLRTokenPtr)LT(1);

			
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
	return;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x4);
}

void
PolyParser::term(ASTBase **_root)
{
	zzRULE;
	ASTBase **_astp, *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	AST *_ast11=NULL;
	if ( (LA(1)==FLOAT) ) {
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
				ANTLRTokenPtr _t21=NULL;
				AST *_ast21=NULL,*_ast22=NULL;
				if ( (LA(1)==EXP) ) {
					zzmatch(EXP); _t21 = (ANTLRTokenPtr)LT(1);

					
					_ast21 = new AST(_t21);
					_ast21->subroot(_root, &_sibling, &_tail);
					 consume();
					_ast = NULL;
					exp(&_ast);
					if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
					_ast22 = (AST *)_ast;
					ASTBase::link(_root, &_sibling, &_tail);
				}
			}
		}
		else {FAIL(1,err1,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	return;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x8);
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
					zzmatch(EXP); _t31 = (ANTLRTokenPtr)LT(1);

					 consume();
					_ast = NULL;
					exp(&_ast);
					_ast32 = (AST *)_ast;
					e_ast = _ast32;
					(*_root) = ASTBase::tmake((new AST(MULT,"MULT")), c_ast, ASTBase::tmake((new AST(EXP,"EXP")), r_ast, e_ast, NULL), NULL);  
				}
				else {
					if ( (setwd1[LA(1)]&0x10) ) {
						(*_root) = ASTBase::tmake((new AST(MULT,"MULT")), c_ast, r_ast, NULL);  
					}
					else {FAIL(1,err2,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
				}
			}
		}
		else {
			if ( (setwd1[LA(1)]&0x20) ) {
				(*_root) = c_ast;  
			}
			else {FAIL(1,err3,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
		}
	}
	return;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x40);
}

void
PolyParser::coefficient(ASTBase **_root)
{
	zzRULE;
	ASTBase **_astp, *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	zzmatch(FLOAT); _t11 = (ANTLRTokenPtr)LT(1);

	
	_ast11 = new AST(_t11);
	_ast11->subchild(_root, &_sibling, &_tail);
	 consume();
	return;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x80);
}

void
PolyParser::reg(ASTBase **_root)
{
	zzRULE;
	ASTBase **_astp, *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	zzmatch(ID); _t11 = (ANTLRTokenPtr)LT(1);

	
	_ast11 = new AST(_t11);
	_ast11->subchild(_root, &_sibling, &_tail);
	 consume();
	return;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd2, 0x1);
}

void
PolyParser::exp(ASTBase **_root)
{
	zzRULE;
	ASTBase **_astp, *_ast = NULL, *_sibling = NULL, *_tail = NULL;
	ANTLRTokenPtr _t11=NULL;
	AST *_ast11=NULL;
	if ( (LA(1)==ID) ) {
		_ast = NULL;
		reg(&_ast);
		if ( _tail==NULL ) _sibling = _ast; else _tail->setRight(_ast);
		_ast11 = (AST *)_ast;
		ASTBase::link(_root, &_sibling, &_tail);
	}
	else {
		if ( (LA(1)==FLOAT) ) {
			zzmatch(FLOAT); _t11 = (ANTLRTokenPtr)LT(1);

			
			_ast11 = new AST(_t11);
			_ast11->subchild(_root, &_sibling, &_tail);
			 consume();
		}
		else {FAIL(1,err4,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	return;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd2, 0x2);
}
