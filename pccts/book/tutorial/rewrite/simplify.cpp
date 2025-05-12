/*
 * S O R C E R E R  T r a n s l a t i o n  H e a d e r
 *
 * SORCERER Developed by Terence Parr, Aaron Sawdey, & Gary Funck
 * Parr Research Corporation, Intrepid Technology, University of Minnesota
 * 1992-1994
 * SORCERER Version 1.00B15
 */
#define SORCERER_VERSION	100B15
#define SORCERER_TRANSFORM
#include "STreeParser.h"
#include "SimplifyPoly.h"

void SimplifyPoly::poly(SORASTBase **_root, SORASTBase **_result)
{
	SORASTBase *_t = *_root;
	SORASTBase *_tresult=NULL;
	TREE_CONSTR_PTRS;
	SORAST *a=NULL,*a_in=NULL;
	SORAST *p=NULL,*p_in=NULL;
	SORAST *q=NULL,*q_in=NULL;
	SORAST *e=NULL,*e_in=NULL;
	SORAST *v=NULL,*v_in=NULL;
	SORAST *ex=NULL,*ex_in=NULL;
	SORAST *id=NULL,*id_in=NULL;
	SORAST *i=NULL,*i_in=NULL;
	*_result = NULL;
	if ( _t!=NULL && (_t->type()==MULT) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(MULT);
		_tresult=_t->shallowCopy();
 _mkroot(&_r,&_s,&_e,_tresult);
		_DOWN;
		poly(&_t, &_tresult);
		_mkchild(&_r,&_s,&_e,_tresult);
		poly(&_t, &_tresult);
		_mkchild(&_r,&_s,&_e,_tresult);
		_RESTORE; _tresult = _r;
		}
		_mkchild(&_r,&_s,&_e,_tresult);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->type()==ADD) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(ADD);
		_tresult=_t->shallowCopy();
		a=(SORAST *)_tresult; a_in=(SORAST *)_t;
		_DOWN;
		p=(SORAST *)_t; poly(&_t, &_tresult);
		p=(SORAST *)_tresult;
		q=(SORAST *)_t; poly(&_t, &_tresult);
		q=(SORAST *)_tresult;
		_RESTORE; _tresult = _r;
		}
		_mkchild(&_r,&_s,&_e,_tresult);
		_RIGHT;
		
		if ( p==NULL ) (*_result) = q;
		else if ( q==NULL ) (*_result) = p;
		else {
			int leftIdentity=( p->type()==INT && p->getIConst()==0 );
			int rightIdentity=( q->type()==INT && q->getIConst()==0 );
			if ( leftIdentity && !rightIdentity ) (*_result) = q;				// 0+x
			else if ( !leftIdentity && rightIdentity ) (*_result) = p;			// x+0
			else if ( !leftIdentity && !rightIdentity ) (*_result) = PCCTS_AST::make(a,p,q, NULL);	// x+y
			else (*_result) = NULL;												// 0+0
		}
	}
	else {
	if ( _t!=NULL && (_t->type()==EXP) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(EXP);
		_tresult=_t->shallowCopy();
		e=(SORAST *)_tresult; e_in=(SORAST *)_t;
		_DOWN;
		v=(SORAST *)_t; poly(&_t, &_tresult);
		v=(SORAST *)_tresult;
		_MATCH(INT);
		_tresult=_t->shallowCopy();
		ex=(SORAST *)_tresult; ex_in=(SORAST *)_t;
		_RESTORE; _tresult = _r;
		}
		_mkchild(&_r,&_s,&_e,_tresult);
		_RIGHT;
		
		if ( ex->getIConst()==1 ) (*_result) = v;
		else (*_result) = PCCTS_AST::make(e,v,ex, NULL);
	}
	else {
	if ( _t!=NULL && (_t->type()==ID) ) {
		_MATCH(ID);
		_tresult=_t->shallowCopy();
 _mkchild(&_r,&_s,&_e,_tresult);
		id=(SORAST *)_tresult; id_in=(SORAST *)_t;
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->type()==INT) ) {
		_MATCH(INT);
		_tresult=_t->shallowCopy();
 _mkchild(&_r,&_s,&_e,_tresult);
		i=(SORAST *)_tresult; i_in=(SORAST *)_t;
		_RIGHT;
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("poly", _t);
	}
	 _tresult = _r;
	}
	}
	}
	}
	*_root = _t;
	if ( (*_result) == NULL ) *_result = _r;
}
