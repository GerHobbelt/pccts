/*
 * S O R C E R E R  T r a n s l a t i o n  H e a d e r
 *
 * SORCERER Developed by Terence Parr, Aaron Sawdey, & Gary Funck
 * Parr Research Corporation, Intrepid Technology, University of Minnesota
 * 1992-1994
 * SORCERER Version 1.00B15
 */
#define SORCERER_VERSION	100B15
#define SORCERER_NONTRANSFORM
#include "STreeParser.h"
#include "PrintPoly.h"

void PrintPoly::poly(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *id=NULL;
	SORAST *i=NULL;
	if ( _t!=NULL && (_t->type()==MULT) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(MULT);
		_DOWN;
		poly(&_t);
		poly(&_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->type()==ADD) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(ADD);
		_DOWN;
		poly(&_t);
		printf("+");  
		poly(&_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->type()==EXP) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(EXP);
		_DOWN;
		poly(&_t);
		printf("^");  
		poly(&_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->type()==ID) ) {
		_MATCH(ID);
		id=(SORAST *)_t;
		_RIGHT;
		printf("%s",id->getText());  
	}
	else {
	if ( _t!=NULL && (_t->type()==INT) ) {
		_MATCH(INT);
		i=(SORAST *)_t;
		_RIGHT;
		printf("%d",i->getIConst());  
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("poly", _t);
	}
	}
	}
	}
	}
	*_root = _t;
}
