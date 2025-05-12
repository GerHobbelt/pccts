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
#include "DiffPoly.h"

void DiffPoly::poly(SORASTBase **_root, SORASTBase **_result)
{
	SORASTBase *_t = *_root;
	SORASTBase *_tresult=NULL;
	TREE_CONSTR_PTRS;
	*_result = NULL;
	if ( _t!=NULL && (_t->type()==ADD) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(ADD);
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
	if ( _t!=NULL && (_t->type()==INT||_t->type()==ID||
	_t->type()==EXP||_t->type()==MULT) ) {
		term(&_t, &_tresult);
		_mkchild(&_r,&_s,&_e,_tresult);
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("poly", _t);
	}
	 _tresult = _r;
	}
	*_root = _t;
	if ( (*_result) == NULL ) *_result = _r;
}

void DiffPoly::term(SORASTBase **_root, SORASTBase **_result)
{
	SORASTBase *_t = *_root;
	SORASTBase *_tresult=NULL;
	TREE_CONSTR_PTRS;
	SORAST *i=NULL,*i_in=NULL;
	SORAST *id=NULL,*id_in=NULL;
	SORAST *ex=NULL,*ex_in=NULL;
	SORAST *e=NULL,*e_in=NULL;
	SORAST *m=NULL,*m_in=NULL;
	SORAST *ct=NULL,*ct_in=NULL;
	SORAST *idt=NULL,*idt_in=NULL;
	SORAST *et=NULL,*et_in=NULL;
	*_result = NULL;
	if ( _t!=NULL && (_t->type()==INT) ) {
		_MATCH(INT);
		_tresult=_t->shallowCopy();
		i=(SORAST *)_tresult; i_in=(SORAST *)_t;
		_RIGHT;
		(*_result) = new SORAST(INT,"0");  
	}
	else {
	if ( _t!=NULL && (_t->type()==ID) ) {
		_MATCH(ID);
		_tresult=_t->shallowCopy();
		id=(SORAST *)_tresult; id_in=(SORAST *)_t;
		_RIGHT;
		(*_result) = new SORAST(INT,"1");  
	}
	else {
	if ( _t!=NULL && (_t->type()==EXP) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(EXP);
		_tresult=_t->shallowCopy();
		ex=(SORAST *)_tresult; ex_in=(SORAST *)_t;
		_DOWN;
		_MATCH(ID);
		_tresult=_t->shallowCopy();
		id=(SORAST *)_tresult; id_in=(SORAST *)_t;
		_RIGHT;
		_MATCH(INT);
		_tresult=_t->shallowCopy();
		e=(SORAST *)_tresult; e_in=(SORAST *)_t;
		_RESTORE; _tresult = _r;
		}
		_RIGHT;
		
		(*_result) = PCCTS_AST::make(new SORAST(MULT,"MULT"), new SORAST(INT,e->getIConst()), PCCTS_AST::make(ex,id,e, NULL), NULL);
		e->decIConst();		// decrement exponent
	}
	else {
	if ( _t!=NULL && (_t->type()==MULT) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(MULT);
		_tresult=_t->shallowCopy();
		m=(SORAST *)_tresult; m_in=(SORAST *)_t;
		_DOWN;
		_MATCH(INT);
		_tresult=_t->shallowCopy();
		ct=(SORAST *)_tresult; ct_in=(SORAST *)_t;
		_RIGHT;
		if ( _t!=NULL && (_t->type()==EXP) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(EXP);
			_tresult=_t->shallowCopy();
			ex=(SORAST *)_tresult; ex_in=(SORAST *)_t;
			_DOWN;
			_MATCH(ID);
			_tresult=_t->shallowCopy();
			idt=(SORAST *)_tresult; idt_in=(SORAST *)_t;
			_RIGHT;
			_MATCH(INT);
			_tresult=_t->shallowCopy();
			et=(SORAST *)_tresult; et_in=(SORAST *)_t;
			_RESTORE; _tresult = _r;
			}
			_RIGHT;
			
			ct->setIConst(ct->getIConst()*et->getIConst());
			et->decIConst();
			(*_result) = PCCTS_AST::make(m, ct, PCCTS_AST::make(ex,idt,et, NULL), NULL);
		}
		else {
		if ( _t!=NULL && (_t->type()==ID) ) {
			_MATCH(ID);
			_RIGHT;
			(*_result) = ct;  
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("term", _t);
		}
		 _tresult = _r;
		}
		_RESTORE; _tresult = _r;
		}
		_RIGHT;
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("term", _t);
	}
	 _tresult = _r;
	}
	}
	}
	*_root = _t;
}
