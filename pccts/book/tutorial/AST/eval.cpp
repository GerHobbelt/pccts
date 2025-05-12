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
#include "EvalPoly.h"

void EvalPoly::assign(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *id=NULL;
	if ( _t!=NULL && (_t->type()==ASSIGN) ) {
		float r;  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(ASSIGN);
		_DOWN;
		_MATCH(ID);
		id=(SORAST *)_t;
		_RIGHT;
		 r =poly(&_t);
		_RESTORE;
		}
		_RIGHT;
		
		store(id->getText(), r);
		printf("storing %f in %s\n", r, id->getText());
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("assign", _t);
	}
	*_root = _t;
}

 float   EvalPoly::poly(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	 float r ;
	SORAST *id=NULL;
	SORAST *f=NULL;
	if ( _t!=NULL && (_t->type()==MULT) ) {
		float p1,p2;  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(MULT);
		_DOWN;
		 p1 =poly(&_t);
		 p2 =poly(&_t);
		_RESTORE;
		}
		_RIGHT;
		r = p1*p2;  
	}
	else {
	if ( _t!=NULL && (_t->type()==ADD) ) {
		float p1,p2;  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(ADD);
		_DOWN;
		 p1 =poly(&_t);
		 p2 =poly(&_t);
		_RESTORE;
		}
		_RIGHT;
		r = p1+p2;  
	}
	else {
	if ( _t!=NULL && (_t->type()==EXP) ) {
		float p1,p2;  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(EXP);
		_DOWN;
		 p1 =poly(&_t);
		 p2 =poly(&_t);
		_RESTORE;
		}
		_RIGHT;
		r = pow(p1,p2);  
	}
	else {
	if ( _t!=NULL && (_t->type()==ID) ) {
		_MATCH(ID);
		id=(SORAST *)_t;
		_RIGHT;
		r = value(id->getText());  
	}
	else {
	if ( _t!=NULL && (_t->type()==FLOAT) ) {
		_MATCH(FLOAT);
		f=(SORAST *)_t;
		_RIGHT;
		r = atof(f->getText());  
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
	return r;
}
