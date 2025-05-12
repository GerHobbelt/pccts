/*
 * S O R C E R E R  T r a n s l a t i o n  H e a d e r
 *
 * SORCERER Developed by Terence Parr, Aaron Sawdey, & Gary Funck
 * Parr Research Corporation, Intrepid Technology, University of Minnesota
 * 1992-1994
 * SORCERER Version 13333
 *
 *   ..\..\..\bin\sorcerer -emsvc f77trans.sor -proto-file f77trans.h -prefix x_
 *
 */
#define SORCERER_VERSION	13333
#define SORCERER_NONTRANSFORM
#include "pcctscfg.h"
#include <stdio.h>
#include <setjmp.h>
/* rename error routines; used in macros, must use /lib/cpp */
#define mismatched_token x_mismatched_token
#define mismatched_range x_mismatched_range
#define missing_wildcard x_missing_wildcard
#define no_viable_alt x_no_viable_alt
#define sorcerer_panic x_sorcerer_panic

#undef SORCERER_TRANSFORM
#define CASTBase_h	/*To eliminate castbase.h*/
#include <assert.h>
#include "stdpccts.h"
typedef AST SORAST;

/* Only requirements are that the user define what an AST is; it must have
* right, down pointers and a token field.  After that, the user can put it
* what he/she wants
*/
#ifdef __STDC__
#include "stdlib.h"
#else
#include "malloc.h"
#endif



#include "sorcerer.h"
#include "f77trans.h"

void
#ifdef __USE_PROTOS
x__refvar_inits(STreeParser *p)
#else
x__refvar_inits(p)
STreeParser *p;
#endif
{
}



/* define error routines here or include sorcerer.c */
#include "errsupport.c"
/* #include "slist.c" */
#include "astlib.c"
#include "sstack.c"
/* #include "sint.c" */

#include "sorlist.c"    /* [i_a] */
#include "sintstack.c" 	/* [i_a] */


#define FindForwardUntil(FoundPointer, Scope, Condition, UntilNode)	\
while(FoundPointer->token != UntilNode) {						\
	if(FoundPointer->token == Scope) {							\
		if(Condition) break;									\
	}														\
	FoundPointer=FoundPointer->right;							\
}															\
if(FoundPointer->token == UntilNode) {							\
	FoundPointer=NULL;											\
}

#define FindBackwardUntil(FoundPointer, Scope, Condition, UntilNode)	\
while(FoundPointer->token != UntilNode) {						\
	if(FoundPointer->token == Scope) {							\
		if(Condition) break;									\
	}														\
	FoundPointer=FoundPointer->left;							\
}															\
if(FoundPointer->token == UntilNode) {							\
	FoundPointer=NULL;											\
}															\
if(FoundPointer->left == NULL) {/*Begining of file.*/			\
	FoundPointer=NULL;											\
}

SORAST *file_root = NULL;
SORAST *open_root = NULL;

char *KindPtr = NULL;
char *TitlePtr = NULL;





extern void o_read_statement(STreeParser *_parser, SORAST **_root);
extern void o_write_statement(STreeParser *_parser, SORAST **_root);
extern void o_format_statement(STreeParser *_parser, SORAST **_root);







SORAST *FindTokenForward(SORAST *t, int token) {
	SORAST *l_t = t;
	if(t == NULL) return(NULL);
	if(t->token == token) return(t);
	l_t = FindTokenForward(l_t->down, token);
	if(!l_t) {
		l_t = FindTokenForward(t->right, token);
	}
	return(l_t);
}

SORAST *FindTokenBackward(SORAST *t, int token) {
	SORAST *l_t = t;
	if(t == NULL) return(NULL);
	if(t->token == token) return(t);
	l_t = FindTokenBackward(l_t->left, token);
	if(!l_t) {
		l_t = FindTokenBackward(t->up, token);
	}
	return(l_t);
}

SORAST *ast_node(int token, const char *sym) {
	SORAST *p = (SORAST *)calloc(1, sizeof(SORAST));
	assert(p != NULL);
	p->token = token;
	strcpy(p->f77NodeText, sym);
	return(p);
}

void F77SearchPerform(SORAST *root, int statement_id, void (*parse_function)(SORAST *)) {
	SORAST *format = ast_make(ast_node(statement_id,"a"), NULL);
	SORAST *cursor = root, *p;
	while((p=ast_find_all(root,format,&cursor)) != NULL)
	{
		parse_function(p);
	}
}

void FormatedIO(SORAST *root) {
	SORAST *format, *l_root = root;
	STreeParser l_parser;
	STreeParserInit(x_, &l_parser); /* calls the 'f77trans.sor' program() rule! --> use f77trans.sor _refvar_inits()! */
	assert((l_root->token == READ) || (l_root->token == WRITE));
	if(l_root->token == READ) {
		format = x_read_statement(&l_parser, &l_root);
	}
	else if(l_root->token == WRITE) {
		format = x_write_statement(&l_parser, &l_root);
	}
	if(format != NULL) {
		if(format->token == CONSTINT) {
			l_root = root;
			if(l_root->token == READ) {
				o_read_statement(&l_parser, &l_root);
			}
			else if(l_root->token == WRITE) {
				o_write_statement(&l_parser, &l_root);
			}
			/*Find first the begining of subroutine or program...*/
			l_root = FindTokenBackward(root, SUBROUTINE);
			/*Then, find the FORMAT statement which has the required label...*/
			do {
				l_root = FindTokenForward(l_root->right, FORMAT);
			}
			while(atoi(l_root->down->f77NodeText) != atoi(format->f77NodeText));

			if(l_root != NULL) {
				o_format_statement(&l_parser, &l_root);
			}
		}
	}
}

AST *F77TreeTranslator(AST *InpRoot, AST *OutRoot)
{
	SORAST *l_root = InpRoot;	/*l_root: program() sets the second pointer to NULL.*/
	STreeParser myparser;
	STreeParserInit(x_, &myparser); /* calls the 'f77trans.sor' program() rule! --> use f77trans.sor _refvar_inits()! */

	zzdouble_link(l_root, NULL, NULL);
	x_program(&myparser, &l_root);
	/*
	F77SearchPerform(InpRoot, READ, &FormatedIO);
	F77SearchPerform(InpRoot, WRITE, &FormatedIO);
	*/
	return(InpRoot);
}

/*Removes 'Node' and its sub-trees from the AST. Frees memory.*/
void F77UnlinkAndDestroy(SORAST *Node) {
	if(Node->left == NULL) {/*First element!*/
		Node->right->left = NULL;
	}
	else if(Node->right == NULL) {/*Last element!*/
		Node->left->right = NULL;
	}
	else {
		Node->right->left = Node->left;
		Node->left->right = Node->right;
	}
	ast_free(Node->down);
	free(Node);
}


void x_program(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==COMMENT_LINE||_t->token==BLANK_LINE||
	_t->token==BLOCK_GLOBALS||_t->token==COMMON||_t->token==SAVE||
	_t->token==PARAMETER||_t->token==EQUAL||_t->token==EXTERNAL||
	_t->token==INTRINSIC||_t->token==IMPLICIT||_t->token==INTEGER||
	_t->token==REAL||_t->token==DOUBLE_PRECISION||_t->token==LOGICAL||
	_t->token==CHARACTER||_t->token==DATA||_t->token==INQUIRE||
	_t->token==CONTROL_IMAGE||_t->token==FILEKEYWORD||_t->token==FIND||
	_t->token==DIMENSION||_t->token==EQUIVALENCE||_t->token==BACKSPACE||
	_t->token==ENDFILE||_t->token==REWIND||_t->token==READ||
	_t->token==WRITE||_t->token==END||_t->token==OPEN||
	_t->token==CLOSE||_t->token==CALL||_t->token==BLOCK_IF||
	_t->token==LOGICAL_IF||_t->token==ARITHMETIC_IF||_t->token==CONTINUE||
	_t->token==STOP||_t->token==RETURN||_t->token==UNCONDITIONAL_GOTO||
	_t->token==COMPUTED_GOTO||_t->token==ASSIGNED_GOTO||_t->token==DO||
	_t->token==CHANGE||_t->token==ASSIGN||_t->token==FORMAT) ) {
		
		if ( _t!=NULL && (_t->token==COMMENT_LINE||_t->token==BLANK_LINE||
		_t->token==CONTROL_IMAGE) ) {
			x_comment_block(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==BLOCK_GLOBALS||_t->token==COMMON||
		_t->token==SAVE||_t->token==PARAMETER||_t->token==EQUAL||
		_t->token==EXTERNAL||_t->token==INTRINSIC||_t->token==IMPLICIT||
		_t->token==INTEGER||_t->token==REAL||_t->token==DOUBLE_PRECISION||
		_t->token==LOGICAL||_t->token==CHARACTER||_t->token==DATA||
		_t->token==INQUIRE||_t->token==FILEKEYWORD||_t->token==FIND||
		_t->token==DIMENSION||_t->token==EQUIVALENCE||_t->token==BACKSPACE||
		_t->token==ENDFILE||_t->token==REWIND||_t->token==READ||
		_t->token==WRITE||_t->token==END||_t->token==OPEN||
		_t->token==CLOSE||_t->token==CALL||_t->token==BLOCK_IF||
		_t->token==LOGICAL_IF||_t->token==ARITHMETIC_IF||_t->token==CONTINUE||
		_t->token==STOP||_t->token==RETURN||_t->token==UNCONDITIONAL_GOTO||
		_t->token==COMPUTED_GOTO||_t->token==ASSIGNED_GOTO||_t->token==DO||
		_t->token==CHANGE||_t->token==ASSIGN||_t->token==FORMAT) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "program", _t);
		}
		}
		if ( _t!=NULL && (_t->token==FILEKEYWORD) ) {
			x_file_block(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==BLOCK_GLOBALS||_t->token==COMMON||
		_t->token==SAVE||_t->token==PARAMETER||_t->token==EQUAL||
		_t->token==EXTERNAL||_t->token==INTRINSIC||_t->token==IMPLICIT||
		_t->token==INTEGER||_t->token==REAL||_t->token==DOUBLE_PRECISION||
		_t->token==LOGICAL||_t->token==CHARACTER||_t->token==DATA||
		_t->token==INQUIRE||_t->token==FIND||_t->token==DIMENSION||
		_t->token==EQUIVALENCE||_t->token==BACKSPACE||_t->token==ENDFILE||
		_t->token==REWIND||_t->token==READ||_t->token==WRITE||
		_t->token==END||_t->token==OPEN||_t->token==CLOSE||
		_t->token==CALL||_t->token==BLOCK_IF||_t->token==LOGICAL_IF||
		_t->token==ARITHMETIC_IF||_t->token==CONTINUE||_t->token==STOP||
		_t->token==RETURN||_t->token==UNCONDITIONAL_GOTO||_t->token==COMPUTED_GOTO||
		_t->token==ASSIGNED_GOTO||_t->token==DO||_t->token==CHANGE||
		_t->token==ASSIGN||_t->token==FORMAT) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "program", _t);
		}
		}
		if ( _t!=NULL && (_t->token==BLOCK_GLOBALS) ) {
			x_block_globals_block(_parser, &_t);
			if ( _t!=NULL && (_t->token==COMMENT_LINE||_t->token==BLANK_LINE||
			_t->token==CONTROL_IMAGE) ) {
				x_comment_block(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==COMMON||_t->token==SAVE||
			_t->token==PARAMETER||_t->token==EQUAL||_t->token==EXTERNAL||
			_t->token==INTRINSIC||_t->token==IMPLICIT||_t->token==INTEGER||
			_t->token==REAL||_t->token==DOUBLE_PRECISION||_t->token==LOGICAL||
			_t->token==CHARACTER||_t->token==DATA||_t->token==INQUIRE||
			_t->token==FIND||_t->token==DIMENSION||_t->token==EQUIVALENCE||
			_t->token==BACKSPACE||_t->token==ENDFILE||_t->token==REWIND||
			_t->token==READ||_t->token==WRITE||_t->token==END||
			_t->token==OPEN||_t->token==CLOSE||_t->token==CALL||
			_t->token==BLOCK_IF||_t->token==LOGICAL_IF||_t->token==ARITHMETIC_IF||
			_t->token==CONTINUE||_t->token==STOP||_t->token==RETURN||
			_t->token==UNCONDITIONAL_GOTO||_t->token==COMPUTED_GOTO||_t->token==ASSIGNED_GOTO||
			_t->token==DO||_t->token==CHANGE||_t->token==ASSIGN||
			_t->token==FORMAT) ) {
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "program", _t);
			}
			}
		}
		else {
		if ( _t!=NULL && (_t->token==COMMON||_t->token==SAVE||
		_t->token==PARAMETER||_t->token==EQUAL||_t->token==EXTERNAL||
		_t->token==INTRINSIC||_t->token==IMPLICIT||_t->token==INTEGER||
		_t->token==REAL||_t->token==DOUBLE_PRECISION||_t->token==LOGICAL||
		_t->token==CHARACTER||_t->token==DATA||_t->token==INQUIRE||
		_t->token==FIND||_t->token==DIMENSION||_t->token==EQUIVALENCE||
		_t->token==BACKSPACE||_t->token==ENDFILE||_t->token==REWIND||
		_t->token==READ||_t->token==WRITE||_t->token==END||
		_t->token==OPEN||_t->token==CLOSE||_t->token==CALL||
		_t->token==BLOCK_IF||_t->token==LOGICAL_IF||_t->token==ARITHMETIC_IF||
		_t->token==CONTINUE||_t->token==STOP||_t->token==RETURN||
		_t->token==UNCONDITIONAL_GOTO||_t->token==COMPUTED_GOTO||_t->token==ASSIGNED_GOTO||
		_t->token==DO||_t->token==CHANGE||_t->token==ASSIGN||
		_t->token==FORMAT) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "program", _t);
		}
		}
		x_main_program(_parser, &_t);
		if ( _t!=NULL && (_t->token==COMMENT_LINE||_t->token==BLANK_LINE||
		_t->token==CONTROL_IMAGE) ) {
			x_comment_block(_parser, &_t);
		}
		else {
		if ( _t==NULL || (_t->token==SUBROUTINE||_t->token==FUNCTION) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "program", _t);
		}
		}
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==SUBROUTINE||_t->token==FUNCTION) ) {
				x_subroutine_block(_parser, &_t);
				if ( _t!=NULL && (_t->token==COMMENT_LINE||_t->token==BLANK_LINE||
				_t->token==CONTROL_IMAGE) ) {
					x_comment_block(_parser, &_t);
				}
				else {
				if ( _t==NULL || (_t->token==SUBROUTINE||_t->token==FUNCTION) ) {
				}
				else {
					if ( _parser->guessing ) _GUESS_FAIL;
					no_viable_alt(_parser, "program", _t);
				}
				}
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "program", _t);
			}
			}
		}
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "program", _t);
	}
	*_root = _t;
}

void x_main_program(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *e=NULL;
	if ( _t!=NULL && (_t->token==COMMON||_t->token==SAVE||
	_t->token==PARAMETER||_t->token==EQUAL||_t->token==EXTERNAL||
	_t->token==INTRINSIC||_t->token==IMPLICIT||_t->token==INTEGER||
	_t->token==REAL||_t->token==DOUBLE_PRECISION||_t->token==LOGICAL||
	_t->token==CHARACTER||_t->token==DATA||_t->token==INQUIRE||
	_t->token==FIND||_t->token==DIMENSION||_t->token==EQUIVALENCE||
	_t->token==BACKSPACE||_t->token==ENDFILE||_t->token==REWIND||
	_t->token==READ||_t->token==WRITE||_t->token==END||
	_t->token==OPEN||_t->token==CLOSE||_t->token==CALL||
	_t->token==BLOCK_IF||_t->token==LOGICAL_IF||_t->token==ARITHMETIC_IF||
	_t->token==CONTINUE||_t->token==STOP||_t->token==RETURN||
	_t->token==UNCONDITIONAL_GOTO||_t->token==COMPUTED_GOTO||_t->token==ASSIGNED_GOTO||
	_t->token==DO||_t->token==CHANGE||_t->token==ASSIGN||
	_t->token==FORMAT) ) {
		if ( _t!=NULL && (_t->token==COMMON||_t->token==SAVE||
		_t->token==PARAMETER||_t->token==EXTERNAL||_t->token==INTRINSIC||
		_t->token==IMPLICIT||_t->token==INTEGER||_t->token==REAL||
		_t->token==DOUBLE_PRECISION||_t->token==LOGICAL||_t->token==CHARACTER||
		_t->token==DATA||_t->token==DIMENSION||_t->token==EQUIVALENCE) ) {
			x_decl_block(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==EQUAL||_t->token==INQUIRE||
		_t->token==FIND||_t->token==BACKSPACE||_t->token==ENDFILE||
		_t->token==REWIND||_t->token==READ||_t->token==WRITE||
		_t->token==END||_t->token==OPEN||_t->token==CLOSE||
		_t->token==CALL||_t->token==BLOCK_IF||_t->token==LOGICAL_IF||
		_t->token==ARITHMETIC_IF||_t->token==CONTINUE||_t->token==STOP||
		_t->token==RETURN||_t->token==UNCONDITIONAL_GOTO||_t->token==COMPUTED_GOTO||
		_t->token==ASSIGNED_GOTO||_t->token==DO||_t->token==CHANGE||
		_t->token==ASSIGN||_t->token==FORMAT) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "main_program", _t);
		}
		}
		if ( _t!=NULL && (_t->token==EQUAL||_t->token==INQUIRE||
		_t->token==FIND||_t->token==BACKSPACE||_t->token==ENDFILE||
		_t->token==REWIND||_t->token==READ||_t->token==WRITE||
		_t->token==OPEN||_t->token==CLOSE||_t->token==CALL||
		_t->token==BLOCK_IF||_t->token==LOGICAL_IF||_t->token==ARITHMETIC_IF||
		_t->token==CONTINUE||_t->token==STOP||_t->token==RETURN||
		_t->token==UNCONDITIONAL_GOTO||_t->token==COMPUTED_GOTO||_t->token==ASSIGNED_GOTO||
		_t->token==DO||_t->token==CHANGE||_t->token==ASSIGN||
		_t->token==FORMAT) ) {
			e=(SORAST *)_t; x_exec_block(_parser, &_t);
			ast_insert_after(e->left, open_root);  
		}
		else {
		if ( _t!=NULL && (_t->token==END) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "main_program", _t);
		}
		}
		x_end_statement(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "main_program", _t);
	}
	*_root = _t;
}

void x_subroutine_block(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==SUBROUTINE||_t->token==FUNCTION) ) {
		if ( _t!=NULL && (_t->token==SUBROUTINE) ) {
			x_subroutine_statement(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==FUNCTION) ) {
			x_function_statement(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "subroutine_block", _t);
		}
		}
		if ( _t!=NULL && (_t->token==COMMENT_LINE||_t->token==BLANK_LINE||
		_t->token==CONTROL_IMAGE) ) {
			x_comment_block(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==COMMON||_t->token==SAVE||
		_t->token==PARAMETER||_t->token==EQUAL||_t->token==EXTERNAL||
		_t->token==INTRINSIC||_t->token==IMPLICIT||_t->token==INTEGER||
		_t->token==REAL||_t->token==DOUBLE_PRECISION||_t->token==LOGICAL||
		_t->token==CHARACTER||_t->token==DATA||_t->token==INQUIRE||
		_t->token==FIND||_t->token==DIMENSION||_t->token==EQUIVALENCE||
		_t->token==BACKSPACE||_t->token==ENDFILE||_t->token==REWIND||
		_t->token==READ||_t->token==WRITE||_t->token==END||
		_t->token==OPEN||_t->token==CLOSE||_t->token==CALL||
		_t->token==BLOCK_IF||_t->token==LOGICAL_IF||_t->token==ARITHMETIC_IF||
		_t->token==CONTINUE||_t->token==STOP||_t->token==RETURN||
		_t->token==UNCONDITIONAL_GOTO||_t->token==COMPUTED_GOTO||_t->token==ASSIGNED_GOTO||
		_t->token==DO||_t->token==CHANGE||_t->token==ASSIGN||
		_t->token==FORMAT) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "subroutine_block", _t);
		}
		}
		if ( _t!=NULL && (_t->token==COMMON||_t->token==SAVE||
		_t->token==PARAMETER||_t->token==EXTERNAL||_t->token==INTRINSIC||
		_t->token==IMPLICIT||_t->token==INTEGER||_t->token==REAL||
		_t->token==DOUBLE_PRECISION||_t->token==LOGICAL||_t->token==CHARACTER||
		_t->token==DATA||_t->token==DIMENSION||_t->token==EQUIVALENCE) ) {
			x_decl_block(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==EQUAL||_t->token==INQUIRE||
		_t->token==FIND||_t->token==BACKSPACE||_t->token==ENDFILE||
		_t->token==REWIND||_t->token==READ||_t->token==WRITE||
		_t->token==END||_t->token==OPEN||_t->token==CLOSE||
		_t->token==CALL||_t->token==BLOCK_IF||_t->token==LOGICAL_IF||
		_t->token==ARITHMETIC_IF||_t->token==CONTINUE||_t->token==STOP||
		_t->token==RETURN||_t->token==UNCONDITIONAL_GOTO||_t->token==COMPUTED_GOTO||
		_t->token==ASSIGNED_GOTO||_t->token==DO||_t->token==CHANGE||
		_t->token==ASSIGN||_t->token==FORMAT) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "subroutine_block", _t);
		}
		}
		if ( _t!=NULL && (_t->token==EQUAL||_t->token==INQUIRE||
		_t->token==FIND||_t->token==BACKSPACE||_t->token==ENDFILE||
		_t->token==REWIND||_t->token==READ||_t->token==WRITE||
		_t->token==OPEN||_t->token==CLOSE||_t->token==CALL||
		_t->token==BLOCK_IF||_t->token==LOGICAL_IF||_t->token==ARITHMETIC_IF||
		_t->token==CONTINUE||_t->token==STOP||_t->token==RETURN||
		_t->token==UNCONDITIONAL_GOTO||_t->token==COMPUTED_GOTO||_t->token==ASSIGNED_GOTO||
		_t->token==DO||_t->token==CHANGE||_t->token==ASSIGN||
		_t->token==FORMAT) ) {
			x_exec_block(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==END) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "subroutine_block", _t);
		}
		}
		x_end_statement(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "subroutine_block", _t);
	}
	*_root = _t;
}

void x_decl_block(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==COMMON||_t->token==SAVE||
	_t->token==PARAMETER||_t->token==EXTERNAL||_t->token==INTRINSIC||
	_t->token==IMPLICIT||_t->token==INTEGER||_t->token==REAL||
	_t->token==DOUBLE_PRECISION||_t->token==LOGICAL||_t->token==CHARACTER||
	_t->token==DATA||_t->token==DIMENSION||_t->token==EQUIVALENCE) ) {
		x_decl_statement(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMON||_t->token==SAVE||
			_t->token==PARAMETER||_t->token==EXTERNAL||_t->token==INTRINSIC||
			_t->token==IMPLICIT||_t->token==INTEGER||_t->token==REAL||
			_t->token==DOUBLE_PRECISION||_t->token==LOGICAL||_t->token==CHARACTER||
			_t->token==DATA||_t->token==DIMENSION||_t->token==EQUIVALENCE) ) {
				x_decl_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==COMMENT_LINE) ) {
				x_comment_line(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==BLANK_LINE) ) {
				x_blank_line(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==CONTROL_IMAGE) ) {
				x_control_image(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==EQUAL||_t->token==INQUIRE||
			_t->token==FIND||_t->token==BACKSPACE||_t->token==ENDFILE||
			_t->token==REWIND||_t->token==READ||_t->token==WRITE||
			_t->token==END||_t->token==OPEN||_t->token==CLOSE||
			_t->token==CALL||_t->token==BLOCK_IF||_t->token==LOGICAL_IF||
			_t->token==ARITHMETIC_IF||_t->token==CONTINUE||_t->token==STOP||
			_t->token==RETURN||_t->token==UNCONDITIONAL_GOTO||_t->token==COMPUTED_GOTO||
			_t->token==ASSIGNED_GOTO||_t->token==DO||_t->token==CHANGE||
			_t->token==ASSIGN||_t->token==FORMAT) ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "decl_block", _t);
			}
			}
			}
			}
			}
		}
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "decl_block", _t);
	}
	*_root = _t;
}

void x_decl_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==COMMON) ) {
		x_common_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==DATA) ) {
		x_data_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CHARACTER) ) {
		x_character_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==INTEGER) ) {
		x_integer_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==REAL) ) {
		x_real_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==LOGICAL) ) {
		x_logical_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==DOUBLE_PRECISION) ) {
		x_precision_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==DIMENSION) ) {
		x_dimension_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==EQUIVALENCE) ) {
		x_equivalence_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==EXTERNAL) ) {
		x_external_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==INTRINSIC) ) {
		x_intrinsic_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==SAVE) ) {
		x_save_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==PARAMETER) ) {
		x_parameter_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==IMPLICIT) ) {
		x_implicit_statement(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "decl_statement", _t);
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	*_root = _t;
}

void x_comment_block(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==COMMENT_LINE||_t->token==BLANK_LINE||
	_t->token==CONTROL_IMAGE) ) {
		{int _done=0;
		do {
			if ( _t!=NULL && (_t->token==COMMENT_LINE) ) {
				x_comment_line(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==BLANK_LINE) ) {
				x_blank_line(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==CONTROL_IMAGE) ) {
				x_control_image(_parser, &_t);
			}
			else {
			if ( _t==NULL || (_t->token==BLOCK_GLOBALS||_t->token==COMMON||
			_t->token==SAVE||_t->token==PARAMETER||_t->token==EQUAL||
			_t->token==EXTERNAL||_t->token==INTRINSIC||_t->token==IMPLICIT||
			_t->token==INTEGER||_t->token==REAL||_t->token==DOUBLE_PRECISION||
			_t->token==LOGICAL||_t->token==CHARACTER||_t->token==DATA||
			_t->token==INQUIRE||_t->token==FILEKEYWORD||_t->token==FIND||
			_t->token==DIMENSION||_t->token==EQUIVALENCE||_t->token==BACKSPACE||
			_t->token==ENDFILE||_t->token==REWIND||_t->token==READ||
			_t->token==WRITE||_t->token==END||_t->token==OPEN||
			_t->token==CLOSE||_t->token==CALL||_t->token==SUBROUTINE||
			_t->token==FUNCTION||_t->token==BLOCK_IF||_t->token==LOGICAL_IF||
			_t->token==ARITHMETIC_IF||_t->token==CONTINUE||_t->token==STOP||
			_t->token==RETURN||_t->token==UNCONDITIONAL_GOTO||_t->token==COMPUTED_GOTO||
			_t->token==ASSIGNED_GOTO||_t->token==DO||_t->token==CHANGE||
			_t->token==ASSIGN||_t->token==FORMAT) ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "comment_block", _t);
			}
			}
			}
			}
		} while ( !_done );
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "comment_block", _t);
	}
	*_root = _t;
}

void x_exec_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==CONTINUE) ) {
		x_continue_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==EQUAL) ) {
		x_assignment_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==DO) ) {
		x_do_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==UNCONDITIONAL_GOTO) ) {
		x_unconditional_goto(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==COMPUTED_GOTO) ) {
		x_computed_goto(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==ASSIGNED_GOTO) ) {
		x_assigned_goto(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==READ) ) {
		x_read_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==WRITE) ) {
		x_write_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==OPEN) ) {
		x_open_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CLOSE) ) {
		x_close_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==INQUIRE) ) {
		x_inquire_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CHANGE) ) {
		x_change_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==FIND) ) {
		x_find_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CALL) ) {
		x_call_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==BLOCK_IF) ) {
		x_block_if_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==ARITHMETIC_IF) ) {
		x_arithm_if_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==LOGICAL_IF) ) {
		x_log_if_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==STOP) ) {
		x_stop_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==RETURN) ) {
		x_return_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==FORMAT) ) {
		x_format_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==BACKSPACE) ) {
		x_backspace_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==REWIND) ) {
		x_rewind_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==ENDFILE) ) {
		x_endfile_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==ASSIGN) ) {
		x_assign_statement(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "exec_statement", _t);
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	*_root = _t;
}

void x_exec_block(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==EQUAL||_t->token==INQUIRE||
	_t->token==FIND||_t->token==BACKSPACE||_t->token==ENDFILE||
	_t->token==REWIND||_t->token==READ||_t->token==WRITE||
	_t->token==OPEN||_t->token==CLOSE||_t->token==CALL||
	_t->token==BLOCK_IF||_t->token==LOGICAL_IF||_t->token==ARITHMETIC_IF||
	_t->token==CONTINUE||_t->token==STOP||_t->token==RETURN||
	_t->token==UNCONDITIONAL_GOTO||_t->token==COMPUTED_GOTO||_t->token==ASSIGNED_GOTO||
	_t->token==DO||_t->token==CHANGE||_t->token==ASSIGN||
	_t->token==FORMAT) ) {
		x_exec_statement(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==EQUAL||_t->token==INQUIRE||
			_t->token==FIND||_t->token==BACKSPACE||_t->token==ENDFILE||
			_t->token==REWIND||_t->token==READ||_t->token==WRITE||
			_t->token==OPEN||_t->token==CLOSE||_t->token==CALL||
			_t->token==BLOCK_IF||_t->token==LOGICAL_IF||_t->token==ARITHMETIC_IF||
			_t->token==CONTINUE||_t->token==STOP||_t->token==RETURN||
			_t->token==UNCONDITIONAL_GOTO||_t->token==COMPUTED_GOTO||_t->token==ASSIGNED_GOTO||
			_t->token==DO||_t->token==CHANGE||_t->token==ASSIGN||
			_t->token==FORMAT) ) {
				x_exec_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==COMMENT_LINE) ) {
				x_comment_line(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==ENTRY) ) {
				x_entry_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==BLANK_LINE) ) {
				x_blank_line(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==CONTROL_IMAGE) ) {
				x_control_image(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==END) ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "exec_block", _t);
			}
			}
			}
			}
			}
			}
		}
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "exec_block", _t);
	}
	*_root = _t;
}

void x_block_globals_block(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==BLOCK_GLOBALS) ) {
		x_block_globals_statement(_parser, &_t);
		if ( _t!=NULL && (_t->token==FILEKEYWORD) ) {
			x_file_block(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==END||_t->token==EXPORT) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "block_globals_block", _t);
		}
		}
		if ( _t!=NULL && (_t->token==EXPORT) ) {
			x_export_statement(_parser, &_t);
			if ( _t!=NULL && (_t->token==COMMENT_LINE||_t->token==BLANK_LINE||
			_t->token==CONTROL_IMAGE) ) {
				x_comment_block(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==END) ) {
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "block_globals_block", _t);
			}
			}
		}
		else {
		if ( _t!=NULL && (_t->token==END) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "block_globals_block", _t);
		}
		}
		x_end_statement(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "block_globals_block", _t);
	}
	*_root = _t;
}

void x_file_block(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==FILEKEYWORD) ) {
		x_file_statement(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==FILEKEYWORD) ) {
				x_file_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==COMMENT_LINE) ) {
				x_comment_line(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==BLANK_LINE) ) {
				x_blank_line(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==CONTROL_IMAGE) ) {
				x_control_image(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==BLOCK_GLOBALS||_t->token==COMMON||
			_t->token==SAVE||_t->token==PARAMETER||_t->token==EQUAL||
			_t->token==EXTERNAL||_t->token==INTRINSIC||_t->token==IMPLICIT||
			_t->token==INTEGER||_t->token==REAL||_t->token==DOUBLE_PRECISION||
			_t->token==LOGICAL||_t->token==CHARACTER||_t->token==DATA||
			_t->token==INQUIRE||_t->token==FIND||_t->token==DIMENSION||
			_t->token==EQUIVALENCE||_t->token==BACKSPACE||_t->token==ENDFILE||
			_t->token==REWIND||_t->token==READ||_t->token==WRITE||
			_t->token==END||_t->token==OPEN||_t->token==CLOSE||
			_t->token==CALL||_t->token==EXPORT||_t->token==BLOCK_IF||
			_t->token==LOGICAL_IF||_t->token==ARITHMETIC_IF||_t->token==CONTINUE||
			_t->token==STOP||_t->token==RETURN||_t->token==UNCONDITIONAL_GOTO||
			_t->token==COMPUTED_GOTO||_t->token==ASSIGNED_GOTO||_t->token==DO||
			_t->token==CHANGE||_t->token==ASSIGN||_t->token==FORMAT) ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "file_block", _t);
			}
			}
			}
			}
			}
		}
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "file_block", _t);
	}
	*_root = _t;
}

void x_comment_line(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==COMMENT_LINE) ) {
		_MATCH(COMMENT_LINE);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "comment_line", _t);
	}
	*_root = _t;
}

void x_blank_line(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *c=NULL;
	if ( _t!=NULL && (_t->token==BLANK_LINE) ) {
		_MATCH(BLANK_LINE);
		c=(SORAST *)_t;
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "blank_line", _t);
	}
	*_root = _t;
}

void x_block_globals_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==BLOCK_GLOBALS) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(BLOCK_GLOBALS);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "block_globals_statement", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "block_globals_statement", _t);
	}
	*_root = _t;
}

void x_common_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==COMMON) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(COMMON);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==CHARACTER_ID||
		_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||
		_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||
		_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==CHARACTER_SUBSTRING) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "common_statement", _t);
		}
		}
		x_block_item(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				_MATCH(COMMA);
				_RIGHT;
				x_block_item(_parser, &_t);
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "common_statement", _t);
			}
			}
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "common_statement", _t);
	}
	*_root = _t;
}

void x_block_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==INTEGER_ID||_t->token==REAL_ID||
	_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
	_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
	_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==CHARACTER_SUBSTRING) ) {
		x_lvalue(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==DIV) ) {
		_MATCH(DIV);
		_RIGHT;
		if ( _t!=NULL && (_t->token==IDENTIFIER) ) {
			_MATCH(IDENTIFIER);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==DIV) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "block_item", _t);
		}
		}
		_MATCH(DIV);
		_RIGHT;
		x_lvalue(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CONCAT) ) {
		_MATCH(CONCAT);
		_RIGHT;
		x_lvalue(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "block_item", _t);
	}
	}
	}
	*_root = _t;
}

void x_save_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==SAVE) ) {
		
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(SAVE);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "save_statement", _t);
		}
		}
		_MATCH(LP);
		_RIGHT;
		x_save_item(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				_MATCH(COMMA);
				_RIGHT;
				x_save_item(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==RP) ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "save_statement", _t);
			}
			}
		}
		}
		_MATCH(RP);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "save_statement", _t);
	}
	*_root = _t;
}

void x_save_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DIV||_t->token==IDENTIFIER) ) {
		if ( _t!=NULL && (_t->token==DIV) ) {
			_MATCH(DIV);
			_RIGHT;
			_MATCH(IDENTIFIER);
			_RIGHT;
			_MATCH(DIV);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==IDENTIFIER) ) {
			_MATCH(IDENTIFIER);
			_RIGHT;
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "save_item", _t);
		}
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "save_item", _t);
	}
	*_root = _t;
}

void x_parameter_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==PARAMETER) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(PARAMETER);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "parameter_statement", _t);
		}
		}
		_MATCH(LP);
		_RIGHT;
		x_para_item(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				_MATCH(COMMA);
				_RIGHT;
				x_para_item(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==RP) ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "parameter_statement", _t);
			}
			}
		}
		}
		_MATCH(RP);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "parameter_statement", _t);
	}
	*_root = _t;
}

void x_para_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==CONSTANT_NAME) ) {
		_MATCH(CONSTANT_NAME);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		x_expression(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "para_item", _t);
	}
	*_root = _t;
}

void x_external_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==EXTERNAL) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(EXTERNAL);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==FUNCTION_NAME) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "external_statement", _t);
		}
		}
		x_function_name(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				_MATCH(COMMA);
				_RIGHT;
				x_function_name(_parser, &_t);
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "external_statement", _t);
			}
			}
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "external_statement", _t);
	}
	*_root = _t;
}

void x_function_name(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==FUNCTION_NAME) ) {
		_MATCH(FUNCTION_NAME);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "function_name", _t);
	}
	*_root = _t;
}

void x_intrinsic_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==INTRINSIC) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(INTRINSIC);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==FUNCTION_NAME) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "intrinsic_statement", _t);
		}
		}
		x_function_name(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				_MATCH(COMMA);
				_RIGHT;
				x_function_name(_parser, &_t);
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "intrinsic_statement", _t);
			}
			}
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "intrinsic_statement", _t);
	}
	*_root = _t;
}

void x_implicit_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==IMPLICIT) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(IMPLICIT);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==INTEGER||_t->token==REAL||
		_t->token==DOUBLE_PRECISION||_t->token==LOGICAL||_t->token==CHARACTER||
		_t->token==COMPLEX||_t->token==DOUBLE_COMPLEX) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "implicit_statement", _t);
		}
		}
		x_implicit_item(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				_MATCH(COMMA);
				_RIGHT;
				x_implicit_item(_parser, &_t);
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "implicit_statement", _t);
			}
			}
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "implicit_statement", _t);
	}
	*_root = _t;
}

void x_implicit_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==INTEGER||_t->token==REAL||
	_t->token==DOUBLE_PRECISION||_t->token==LOGICAL||_t->token==CHARACTER||
	_t->token==COMPLEX||_t->token==DOUBLE_COMPLEX) ) {
		x_implicit_type(_parser, &_t);
		_MATCH(LP);
		_RIGHT;
		x_letter_spec(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				_MATCH(COMMA);
				_RIGHT;
				x_letter_spec(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==RP) ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "implicit_item", _t);
			}
			}
		}
		}
		_MATCH(RP);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "implicit_item", _t);
	}
	*_root = _t;
}

void x_implicit_type(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==INTEGER||_t->token==REAL||
	_t->token==DOUBLE_PRECISION||_t->token==LOGICAL||_t->token==CHARACTER||
	_t->token==COMPLEX||_t->token==DOUBLE_COMPLEX) ) {
		if ( _t!=NULL && (_t->token==INTEGER) ) {
			_MATCH(INTEGER);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==REAL) ) {
			_MATCH(REAL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==DOUBLE_PRECISION) ) {
			_MATCH(DOUBLE_PRECISION);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==LOGICAL) ) {
			_MATCH(LOGICAL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==CHARACTER) ) {
			_MATCH(CHARACTER);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==COMPLEX) ) {
			_MATCH(COMPLEX);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==DOUBLE_COMPLEX) ) {
			_MATCH(DOUBLE_COMPLEX);
			_RIGHT;
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "implicit_type", _t);
		}
		}
		}
		}
		}
		}
		}
		if ( _t!=NULL && (_t->token==STAR) ) {
			_MATCH(STAR);
			_RIGHT;
			_MATCH(CONSTINT);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "implicit_type", _t);
		}
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "implicit_type", _t);
	}
	*_root = _t;
}

void x_letter_spec(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==IDENTIFIER) ) {
		_MATCH(IDENTIFIER);
		_RIGHT;
		if ( _t!=NULL && (_t->token==MIN) ) {
			_MATCH(MIN);
			_RIGHT;
			_MATCH(IDENTIFIER);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==COMMA||_t->token==RP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "letter_spec", _t);
		}
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "letter_spec", _t);
	}
	*_root = _t;
}

void x_data_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DATA) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(DATA);
		_DOWN;
		{int _done=0;
		do {
			if ( _t!=NULL ) {
				x_any_token(_parser, &_t);
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "data_statement", _t);
			}
			}
		} while ( !_done );
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "data_statement", _t);
	}
	*_root = _t;
}

void x_inquire_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==INQUIRE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(INQUIRE);
		_DOWN;
		{int _done=0;
		do {
			if ( _t!=NULL ) {
				x_any_token(_parser, &_t);
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "inquire_statement", _t);
			}
			}
		} while ( !_done );
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "inquire_statement", _t);
	}
	*_root = _t;
}

void x_assignment_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==EQUAL) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(EQUAL);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==FUNCTION_NAME||_t->token==INTEGER_ID||
		_t->token==REAL_ID||_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||
		_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||
		_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||
		_t->token==CHARACTER_SUBSTRING) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "assignment_statement", _t);
		}
		}
		if ( _t!=NULL && (_t->token==INTEGER_ID||_t->token==REAL_ID||
		_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
		_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
		_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==CHARACTER_SUBSTRING) ) {
			x_lvalue(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==FUNCTION_NAME) ) {
			_MATCH(FUNCTION_NAME);
			_RIGHT;
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "assignment_statement", _t);
		}
		}
		x_rvalue(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "assignment_statement", _t);
	}
	*_root = _t;
}

void x_lvalue(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==INTEGER_ID||_t->token==INTEGER_ARRAY_ID) ) {
		x_int_lvalue(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==REAL_ID||_t->token==REAL_ARRAY_ID) ) {
		x_real_lvalue(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CHARACTER_ID||_t->token==CHARACTER_ARRAY_ID||
	_t->token==CHARACTER_SUBSTRING) ) {
		x_char_lvalue(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==LOGICAL_ID||_t->token==LOGICAL_ARRAY_ID) ) {
		x_log_lvalue(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==DOUBLE_PRECISION_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID) ) {
		x_double_lvalue(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "lvalue", _t);
	}
	}
	}
	}
	}
	*_root = _t;
}

void x_rvalue(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==LP||_t->token==FUNCTION_NAME||_t->token==CONSTINT||
	_t->token==MIN||_t->token==INTEGER_ID||_t->token==REAL_ID||
	_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
	_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
	_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||
	_t->token==NOT||_t->token==UNARY_MIN||_t->token==PLU||
	_t->token==MUL||_t->token==POW||_t->token==AND||
	_t->token==OR||_t->token==NEQV||_t->token==EQV||
	_t->token==LT||_t->token==LE||_t->token==EQ||
	_t->token==NE||_t->token==GT||_t->token==GE||
	_t->token==IS||_t->token==HEX_CONST||_t->token==BASIC_REAL||
	_t->token==REAL_EXPO||_t->token==T_TRUE||_t->token==T_FALSE||
	_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||_t->token==CHARACTER_SUBSTRING) ) {
		x_expression(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "rvalue", _t);
	}
	*_root = _t;
}

void x_array_reference(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==INTEGER_ARRAY_ID) ) {
		x_int_array_ref(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==REAL_ARRAY_ID) ) {
		x_real_array_ref(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CHARACTER_ARRAY_ID) ) {
		x_char_array_ref(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==DOUBLE_PRECISION_ARRAY_ID) ) {
		x_double_array_ref(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==LOGICAL_ARRAY_ID) ) {
		x_log_array_ref(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "array_reference", _t);
	}
	}
	}
	}
	}
	*_root = _t;
}

void x_int_lvalue(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==INTEGER_ARRAY_ID) ) {
		x_int_array_ref(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==INTEGER_ID) ) {
		_MATCH(INTEGER_ID);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "int_lvalue", _t);
	}
	}
	*_root = _t;
}

void x_real_lvalue(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==REAL_ARRAY_ID) ) {
		x_real_array_ref(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==REAL_ID) ) {
		_MATCH(REAL_ID);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "real_lvalue", _t);
	}
	}
	*_root = _t;
}

void x_char_lvalue(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==CHARACTER_ARRAY_ID) ) {
		x_char_array_ref(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CHARACTER_ID) ) {
		_MATCH(CHARACTER_ID);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==CHARACTER_SUBSTRING) ) {
		x_substring(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "char_lvalue", _t);
	}
	}
	}
	*_root = _t;
}

void x_double_lvalue(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DOUBLE_PRECISION_ARRAY_ID) ) {
		x_double_array_ref(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==DOUBLE_PRECISION_ID) ) {
		_MATCH(DOUBLE_PRECISION_ID);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "double_lvalue", _t);
	}
	}
	*_root = _t;
}

void x_log_lvalue(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==LOGICAL_ARRAY_ID) ) {
		x_log_array_ref(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==LOGICAL_ID) ) {
		_MATCH(LOGICAL_ID);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "log_lvalue", _t);
	}
	}
	*_root = _t;
}

void x_int_array_ref(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==INTEGER_ARRAY_ID) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(INTEGER_ARRAY_ID);
		_DOWN;
		if ( _t!=NULL && (_t->token==LP) ) {
			_MATCH(LP);
			_RIGHT;
			x_expression(_parser, &_t);
			{int _done=0;
			while ( !_done ) {
				if ( _t!=NULL && (_t->token==COMMA) ) {
					_MATCH(COMMA);
					_RIGHT;
					x_expression(_parser, &_t);
				}
				else {
				if ( _t!=NULL && (_t->token==RP) ) {
					_done = 1;
				}
				else {
					if ( _parser->guessing ) _GUESS_FAIL;
					no_viable_alt(_parser, "int_array_ref", _t);
				}
				}
			}
			}
			_MATCH(RP);
			_RIGHT;
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "int_array_ref", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "int_array_ref", _t);
	}
	*_root = _t;
}

void x_real_array_ref(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==REAL_ARRAY_ID) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(REAL_ARRAY_ID);
		_DOWN;
		if ( _t!=NULL && (_t->token==LP) ) {
			_MATCH(LP);
			_RIGHT;
			x_expression(_parser, &_t);
			{int _done=0;
			while ( !_done ) {
				if ( _t!=NULL && (_t->token==COMMA) ) {
					_MATCH(COMMA);
					_RIGHT;
					x_expression(_parser, &_t);
				}
				else {
				if ( _t!=NULL && (_t->token==RP) ) {
					_done = 1;
				}
				else {
					if ( _parser->guessing ) _GUESS_FAIL;
					no_viable_alt(_parser, "real_array_ref", _t);
				}
				}
			}
			}
			_MATCH(RP);
			_RIGHT;
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "real_array_ref", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "real_array_ref", _t);
	}
	*_root = _t;
}

void x_char_array_ref(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==CHARACTER_ARRAY_ID) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(CHARACTER_ARRAY_ID);
		_DOWN;
		if ( _t!=NULL && (_t->token==LP) ) {
			_MATCH(LP);
			_RIGHT;
			x_expression(_parser, &_t);
			{int _done=0;
			while ( !_done ) {
				if ( _t!=NULL && (_t->token==COMMA) ) {
					_MATCH(COMMA);
					_RIGHT;
					x_expression(_parser, &_t);
				}
				else {
				if ( _t!=NULL && (_t->token==RP) ) {
					_done = 1;
				}
				else {
					if ( _parser->guessing ) _GUESS_FAIL;
					no_viable_alt(_parser, "char_array_ref", _t);
				}
				}
			}
			}
			_MATCH(RP);
			_RIGHT;
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "char_array_ref", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "char_array_ref", _t);
	}
	*_root = _t;
}

void x_log_array_ref(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==LOGICAL_ARRAY_ID) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(LOGICAL_ARRAY_ID);
		_DOWN;
		if ( _t!=NULL && (_t->token==LP) ) {
			_MATCH(LP);
			_RIGHT;
			x_expression(_parser, &_t);
			{int _done=0;
			while ( !_done ) {
				if ( _t!=NULL && (_t->token==COMMA) ) {
					_MATCH(COMMA);
					_RIGHT;
					x_expression(_parser, &_t);
				}
				else {
				if ( _t!=NULL && (_t->token==RP) ) {
					_done = 1;
				}
				else {
					if ( _parser->guessing ) _GUESS_FAIL;
					no_viable_alt(_parser, "log_array_ref", _t);
				}
				}
			}
			}
			_MATCH(RP);
			_RIGHT;
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "log_array_ref", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "log_array_ref", _t);
	}
	*_root = _t;
}

void x_double_array_ref(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DOUBLE_PRECISION_ARRAY_ID) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(DOUBLE_PRECISION_ARRAY_ID);
		_DOWN;
		if ( _t!=NULL && (_t->token==LP) ) {
			_MATCH(LP);
			_RIGHT;
			x_expression(_parser, &_t);
			{int _done=0;
			while ( !_done ) {
				if ( _t!=NULL && (_t->token==COMMA) ) {
					_MATCH(COMMA);
					_RIGHT;
					x_expression(_parser, &_t);
				}
				else {
				if ( _t!=NULL && (_t->token==RP) ) {
					_done = 1;
				}
				else {
					if ( _parser->guessing ) _GUESS_FAIL;
					no_viable_alt(_parser, "double_array_ref", _t);
				}
				}
			}
			}
			_MATCH(RP);
			_RIGHT;
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "double_array_ref", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "double_array_ref", _t);
	}
	*_root = _t;
}

void x_array_name(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||
	_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID) ) {
		if ( _t!=NULL && (_t->token==INTEGER_ARRAY_ID) ) {
			_MATCH(INTEGER_ARRAY_ID);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==REAL_ARRAY_ID) ) {
			_MATCH(REAL_ARRAY_ID);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==CHARACTER_ARRAY_ID) ) {
			_MATCH(CHARACTER_ARRAY_ID);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==LOGICAL_ARRAY_ID) ) {
			_MATCH(LOGICAL_ARRAY_ID);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==DOUBLE_PRECISION_ARRAY_ID) ) {
			_MATCH(DOUBLE_PRECISION_ARRAY_ID);
			_RIGHT;
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "array_name", _t);
		}
		}
		}
		}
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "array_name", _t);
	}
	*_root = _t;
}

void x_function_reference(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==FUNCTION_NAME) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(FUNCTION_NAME);
		_DOWN;
		_MATCH(LP);
		_RIGHT;
		x_expression(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				_MATCH(COMMA);
				_RIGHT;
				x_expression(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==RP) ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "function_reference", _t);
			}
			}
		}
		}
		_MATCH(RP);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "function_reference", _t);
	}
	*_root = _t;
}

void x_expression(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==MIN||_t->token==UNARY_PLU||_t->token==NOT||
	_t->token==UNARY_MIN||_t->token==PLU||_t->token==MUL||
	_t->token==POW||_t->token==AND||_t->token==OR||
	_t->token==NEQV||_t->token==EQV||_t->token==LT||
	_t->token==LE||_t->token==EQ||_t->token==NE||
	_t->token==GT||_t->token==GE||_t->token==IS) ) {
		x_real_expression(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==LP||_t->token==FUNCTION_NAME||
	_t->token==CONSTINT||_t->token==INTEGER_ID||_t->token==REAL_ID||
	_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
	_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
	_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==HEX_CONST||
	_t->token==BASIC_REAL||_t->token==REAL_EXPO||_t->token==T_TRUE||
	_t->token==T_FALSE||_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||
	_t->token==CHARACTER_SUBSTRING) ) {
		x_exp_operand(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "expression", _t);
	}
	}
	*_root = _t;
}

void x_real_expression(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==UNARY_PLU) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(UNARY_PLU);
		_DOWN;
		x_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==NOT) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(NOT);
		_DOWN;
		x_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==UNARY_MIN) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(UNARY_MIN);
		_DOWN;
		x_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==PLU) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(PLU);
		_DOWN;
		x_expression(_parser, &_t);
		x_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==MIN) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(MIN);
		_DOWN;
		x_expression(_parser, &_t);
		x_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==MUL) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(MUL);
		_DOWN;
		x_expression(_parser, &_t);
		x_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==DIV) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(DIV);
		_DOWN;
		x_expression(_parser, &_t);
		x_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==POW) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(POW);
		_DOWN;
		x_expression(_parser, &_t);
		x_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==AND) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(AND);
		_DOWN;
		x_expression(_parser, &_t);
		x_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==OR) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(OR);
		_DOWN;
		x_expression(_parser, &_t);
		x_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==NEQV) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(NEQV);
		_DOWN;
		x_expression(_parser, &_t);
		x_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==EQV) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(EQV);
		_DOWN;
		x_expression(_parser, &_t);
		x_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==LT) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(LT);
		_DOWN;
		x_expression(_parser, &_t);
		x_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==LE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(LE);
		_DOWN;
		x_expression(_parser, &_t);
		x_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==EQ) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(EQ);
		_DOWN;
		x_expression(_parser, &_t);
		x_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==NE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(NE);
		_DOWN;
		x_expression(_parser, &_t);
		x_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==GT) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(GT);
		_DOWN;
		x_expression(_parser, &_t);
		x_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==GE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(GE);
		_DOWN;
		x_expression(_parser, &_t);
		x_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==IS) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(IS);
		_DOWN;
		x_expression(_parser, &_t);
		x_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==CONCAT) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(CONCAT);
		_DOWN;
		x_expression(_parser, &_t);
		x_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "real_expression", _t);
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	*_root = _t;
}

void x_exp_operand(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||
	_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID) ) {
		x_array_reference(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==FUNCTION_NAME) ) {
		x_function_reference(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==INTEGER_ID) ) {
		_MATCH(INTEGER_ID);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==REAL_ID) ) {
		_MATCH(REAL_ID);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==DOUBLE_PRECISION_ID) ) {
		_MATCH(DOUBLE_PRECISION_ID);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==CONSTINT) ) {
		_MATCH(CONSTINT);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==HEX_CONST) ) {
		_MATCH(HEX_CONST);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==BASIC_REAL) ) {
		_MATCH(BASIC_REAL);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==REAL_EXPO) ) {
		_MATCH(REAL_EXPO);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==LOGICAL_ID) ) {
		_MATCH(LOGICAL_ID);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==T_TRUE) ) {
		_MATCH(T_TRUE);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==T_FALSE) ) {
		_MATCH(T_FALSE);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==CHARACTER_SUBSTRING) ) {
		x_substring(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CHARACTER_ID) ) {
		_MATCH(CHARACTER_ID);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==HOLLERITH_CONST) ) {
		if ( _t!=NULL && (_t->token==HOLLERITH_CONST) ) {
			_MATCH(HOLLERITH_CONST);
			_RIGHT;
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "exp_operand", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==QUOTED_STRING) ) {
		if ( _t!=NULL && (_t->token==QUOTED_STRING) ) {
			_MATCH(QUOTED_STRING);
			_RIGHT;
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "exp_operand", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==LP) ) {
		_MATCH(LP);
		_RIGHT;
		x_expression(_parser, &_t);
		_MATCH(RP);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "exp_operand", _t);
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	*_root = _t;
}

void x_integer_expr(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==UNARY_PLU) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(UNARY_PLU);
		_DOWN;
		x_integer_expr(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==UNARY_MIN) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(UNARY_MIN);
		_DOWN;
		x_integer_expr(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==PLU) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(PLU);
		_DOWN;
		x_integer_expr(_parser, &_t);
		if ( _t!=NULL && (_t->token==DIV||_t->token==LP||
		_t->token==FUNCTION_NAME||_t->token==CONSTINT||_t->token==MIN||
		_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==INTEGER_ARRAY_ID||
		_t->token==UNARY_PLU||_t->token==UNARY_MIN||_t->token==PLU||
		_t->token==MUL||_t->token==HEX_CONST) ) {
			x_integer_expr(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==QUOTED_STRING) ) {
			_MATCH(QUOTED_STRING);
			_RIGHT;
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "integer_expr", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==MIN) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(MIN);
		_DOWN;
		x_integer_expr(_parser, &_t);
		if ( _t!=NULL && (_t->token==DIV||_t->token==LP||
		_t->token==FUNCTION_NAME||_t->token==CONSTINT||_t->token==MIN||
		_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==INTEGER_ARRAY_ID||
		_t->token==UNARY_PLU||_t->token==UNARY_MIN||_t->token==PLU||
		_t->token==MUL||_t->token==HEX_CONST) ) {
			x_integer_expr(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==QUOTED_STRING) ) {
			_MATCH(QUOTED_STRING);
			_RIGHT;
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "integer_expr", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==MUL) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(MUL);
		_DOWN;
		x_integer_expr(_parser, &_t);
		x_integer_expr(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==DIV) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(DIV);
		_DOWN;
		x_integer_expr(_parser, &_t);
		x_integer_expr(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==LP) ) {
		_MATCH(LP);
		_RIGHT;
		x_integer_expr(_parser, &_t);
		_MATCH(RP);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==INTEGER_ARRAY_ID) ) {
		x_int_array_ref(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==FUNCTION_NAME) ) {
		x_function_reference(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==INTEGER_ID) ) {
		_MATCH(INTEGER_ID);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==CONSTINT) ) {
		_MATCH(CONSTINT);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==HEX_CONST) ) {
		_MATCH(HEX_CONST);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==REAL_ID) ) {
		_MATCH(REAL_ID);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "integer_expr", _t);
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	*_root = _t;
}

void x_substring(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==CHARACTER_SUBSTRING) ) {
		_MATCH(CHARACTER_SUBSTRING);
		_RIGHT;
		_MATCH(LP);
		_RIGHT;
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==LP||_t->token==FUNCTION_NAME||_t->token==CONSTINT||
		_t->token==MIN||_t->token==INTEGER_ID||_t->token==REAL_ID||
		_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
		_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
		_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||
		_t->token==NOT||_t->token==UNARY_MIN||_t->token==PLU||
		_t->token==MUL||_t->token==POW||_t->token==AND||
		_t->token==OR||_t->token==NEQV||_t->token==EQV||
		_t->token==LT||_t->token==LE||_t->token==EQ||
		_t->token==NE||_t->token==GT||_t->token==GE||
		_t->token==IS||_t->token==HEX_CONST||_t->token==BASIC_REAL||
		_t->token==REAL_EXPO||_t->token==T_TRUE||_t->token==T_FALSE||
		_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||_t->token==CHARACTER_SUBSTRING) ) {
			x_expression(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==COLUMN) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "substring", _t);
		}
		}
		_MATCH(COLUMN);
		_RIGHT;
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==LP||_t->token==FUNCTION_NAME||_t->token==CONSTINT||
		_t->token==MIN||_t->token==INTEGER_ID||_t->token==REAL_ID||
		_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
		_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
		_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||
		_t->token==NOT||_t->token==UNARY_MIN||_t->token==PLU||
		_t->token==MUL||_t->token==POW||_t->token==AND||
		_t->token==OR||_t->token==NEQV||_t->token==EQV||
		_t->token==LT||_t->token==LE||_t->token==EQ||
		_t->token==NE||_t->token==GT||_t->token==GE||
		_t->token==IS||_t->token==HEX_CONST||_t->token==BASIC_REAL||
		_t->token==REAL_EXPO||_t->token==T_TRUE||_t->token==T_FALSE||
		_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||_t->token==CHARACTER_SUBSTRING) ) {
			x_expression(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==RP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "substring", _t);
		}
		}
		_MATCH(RP);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "substring", _t);
	}
	*_root = _t;
}

void x_control_image(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==CONTROL_IMAGE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(CONTROL_IMAGE);
		_DOWN;
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL ) {
				x_any_token(_parser, &_t);
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "control_image", _t);
			}
			}
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "control_image", _t);
	}
	*_root = _t;
}

void x_file_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *f=NULL;
	SORAST *c=NULL;
	if ( _t!=NULL && (_t->token==FILEKEYWORD) ) {
		SORAST *l_root; char buffer[100];  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(FILEKEYWORD);
		f=(SORAST *)_t;
		_DOWN;
		_MATCH(CONSTINT);
		c=(SORAST *)_t;
		_RIGHT;
		_MATCH(LP);
		_RIGHT;
		x_file_item(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				_MATCH(COMMA);
				_RIGHT;
				x_file_item(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==RP) ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "file_statement", _t);
			}
			}
		}
		}
		_MATCH(RP);
		_RESTORE;
		}
		_RIGHT;
		{
			if(strcmp(KindPtr, "REMOTE")) {
				strcpy(buffer, " ");
			}
			else {
				strcpy(buffer, "USER");
			}
			l_root = ast_make(ast_node(OPEN, "OPEN"),ast_node(LP, "("),ast_node(UNIT, "UNIT"),ast_node(EQUAL, "="),
			ast_node(CONSTINT, c->f77NodeText),ast_node(COMMA, ","),ast_node(FILE_WORD, "FILE"),ast_node(EQUAL, "="),
			ast_node(QUOTED_STRING, buffer),ast_node(RP, ")"), NULL);
			if(open_root == NULL) {
				open_root = l_root;
			}
			else {
				ast_append(open_root, l_root);
			}
			F77UnlinkAndDestroy(f);
		}  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "file_statement", _t);
	}
	*_root = _t;
}

void x_file_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *k=NULL;
	SORAST *t=NULL;
	if ( _t!=NULL && (_t->token==KIND) ) {
		_MATCH(KIND);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		_WILDCARD;
		k=(SORAST *)_t;
		_RIGHT;
		KindPtr = k->f77NodeText;  
	}
	else {
	if ( _t!=NULL && (_t->token==TITLE) ) {
		_MATCH(TITLE);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		_WILDCARD;
		t=(SORAST *)_t;
		_RIGHT;
		TitlePtr = t->f77NodeText;  
	}
	else {
	if ( _t!=NULL && (_t->token==FILETYPE) ) {
		_MATCH(FILETYPE);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		_WILDCARD;
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==NEWFILE) ) {
		_MATCH(NEWFILE);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		_WILDCARD;
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==MYUSE) ) {
		_MATCH(MYUSE);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		_WILDCARD;
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==MAXRECSIZE) ) {
		_MATCH(MAXRECSIZE);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		_WILDCARD;
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==SAVEFACTOR) ) {
		_MATCH(SAVEFACTOR);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		_WILDCARD;
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==BLOCKSIZE) ) {
		_MATCH(BLOCKSIZE);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		_WILDCARD;
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==SECURITYTYPE) ) {
		_MATCH(SECURITYTYPE);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		_WILDCARD;
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==AREAS) ) {
		_MATCH(AREAS);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		_WILDCARD;
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==AREASIZE) ) {
		_MATCH(AREASIZE);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		_WILDCARD;
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==PROTECTION) ) {
		_MATCH(PROTECTION);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		_WILDCARD;
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==UNITS) ) {
		_MATCH(UNITS);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		_WILDCARD;
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==UPDATEFILE) ) {
		_MATCH(UPDATEFILE);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		_WILDCARD;
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==FILE_WORD) ) {
		_MATCH(FILE_WORD);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		_WILDCARD;
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==STATUS) ) {
		_MATCH(STATUS);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		_WILDCARD;
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==ACCESS) ) {
		_MATCH(ACCESS);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		_WILDCARD;
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==FORM) ) {
		_MATCH(FORM);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		_WILDCARD;
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==RECL) ) {
		_MATCH(RECL);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		_WILDCARD;
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==BLANK) ) {
		_MATCH(BLANK);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		_WILDCARD;
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "file_item", _t);
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	*_root = _t;
}

void x_find_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==FIND) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(FIND);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "find_statement", _t);
		}
		}
		_MATCH(LP);
		_RIGHT;
		x_findlist(_parser, &_t);
		_MATCH(RP);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "find_statement", _t);
	}
	*_root = _t;
}

void x_findlist(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==COMMA) ) {
		if ( _t!=NULL && (_t->token==COMMA) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(COMMA);
			_DOWN;
			x_unit_id(_parser, &_t);
			_MATCH(REC);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_integer_expr(_parser, &_t);
			_RESTORE;
			}
			_RIGHT;
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "findlist", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==APOSTROPHY) ) {
		if ( _t!=NULL && (_t->token==APOSTROPHY) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(APOSTROPHY);
			_DOWN;
			x_unit_id(_parser, &_t);
			x_integer_expr(_parser, &_t);
			_RESTORE;
			}
			_RIGHT;
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "findlist", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==UNIT) ) {
		if ( _t!=NULL && (_t->token==UNIT) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(UNIT);
			_DOWN;
			_MATCH(EQUAL);
			_RIGHT;
			x_unit_id(_parser, &_t);
			_MATCH(COMMA);
			_RIGHT;
			_MATCH(REC);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_integer_expr(_parser, &_t);
			_RESTORE;
			}
			_RIGHT;
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "findlist", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==REC) ) {
		if ( _t!=NULL && (_t->token==REC) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(REC);
			_DOWN;
			_MATCH(EQUAL);
			_RIGHT;
			x_integer_expr(_parser, &_t);
			_MATCH(COMMA);
			_RIGHT;
			_MATCH(UNIT);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_unit_id(_parser, &_t);
			_RESTORE;
			}
			_RIGHT;
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "findlist", _t);
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "findlist", _t);
	}
	}
	}
	}
	*_root = _t;
}

void x_character_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==CHARACTER) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(CHARACTER);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t==NULL || (_t!=NULL) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "character_statement", _t);
		}
		}
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL ) {
				x_any_token(_parser, &_t);
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "character_statement", _t);
			}
			}
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "character_statement", _t);
	}
	*_root = _t;
}

void x_integer_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==INTEGER) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(INTEGER);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t==NULL || (_t!=NULL) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "integer_statement", _t);
		}
		}
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL ) {
				x_any_token(_parser, &_t);
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "integer_statement", _t);
			}
			}
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "integer_statement", _t);
	}
	*_root = _t;
}

void x_real_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==REAL) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(REAL);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t==NULL || (_t!=NULL) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "real_statement", _t);
		}
		}
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL ) {
				x_any_token(_parser, &_t);
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "real_statement", _t);
			}
			}
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "real_statement", _t);
	}
	*_root = _t;
}

void x_logical_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==LOGICAL) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(LOGICAL);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t==NULL || (_t!=NULL) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "logical_statement", _t);
		}
		}
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL ) {
				x_any_token(_parser, &_t);
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "logical_statement", _t);
			}
			}
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "logical_statement", _t);
	}
	*_root = _t;
}

void x_precision_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DOUBLE_PRECISION) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(DOUBLE_PRECISION);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t==NULL || (_t!=NULL) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "precision_statement", _t);
		}
		}
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL ) {
				x_any_token(_parser, &_t);
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "precision_statement", _t);
			}
			}
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "precision_statement", _t);
	}
	*_root = _t;
}

void x_dimension_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DIMENSION) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(DIMENSION);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t==NULL || (_t!=NULL) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "dimension_statement", _t);
		}
		}
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL ) {
				x_any_token(_parser, &_t);
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "dimension_statement", _t);
			}
			}
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "dimension_statement", _t);
	}
	*_root = _t;
}

void x_equivalence_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==EQUIVALENCE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(EQUIVALENCE);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t==NULL || (_t!=NULL) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "equivalence_statement", _t);
		}
		}
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL ) {
				x_any_token(_parser, &_t);
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "equivalence_statement", _t);
			}
			}
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "equivalence_statement", _t);
	}
	*_root = _t;
}

void x_backspace_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==BACKSPACE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(BACKSPACE);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==LP||_t->token==FUNCTION_NAME||_t->token==STAR||
		_t->token==CONSTINT||_t->token==MIN||_t->token==INTEGER_ID||
		_t->token==REAL_ID||_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||
		_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||
		_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||
		_t->token==UNARY_PLU||_t->token==NOT||_t->token==UNARY_MIN||
		_t->token==PLU||_t->token==MUL||_t->token==POW||
		_t->token==AND||_t->token==OR||_t->token==NEQV||
		_t->token==EQV||_t->token==LT||_t->token==LE||
		_t->token==EQ||_t->token==NE||_t->token==GT||
		_t->token==GE||_t->token==IS||_t->token==HEX_CONST||
		_t->token==BASIC_REAL||_t->token==REAL_EXPO||_t->token==T_TRUE||
		_t->token==T_FALSE||_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||
		_t->token==CHARACTER_SUBSTRING||_t->token==IO_SPEC_LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "backspace_statement", _t);
		}
		}
		x_io_specifier(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "backspace_statement", _t);
	}
	*_root = _t;
}

void x_endfile_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==ENDFILE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(ENDFILE);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==LP||_t->token==FUNCTION_NAME||_t->token==STAR||
		_t->token==CONSTINT||_t->token==MIN||_t->token==INTEGER_ID||
		_t->token==REAL_ID||_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||
		_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||
		_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||
		_t->token==UNARY_PLU||_t->token==NOT||_t->token==UNARY_MIN||
		_t->token==PLU||_t->token==MUL||_t->token==POW||
		_t->token==AND||_t->token==OR||_t->token==NEQV||
		_t->token==EQV||_t->token==LT||_t->token==LE||
		_t->token==EQ||_t->token==NE||_t->token==GT||
		_t->token==GE||_t->token==IS||_t->token==HEX_CONST||
		_t->token==BASIC_REAL||_t->token==REAL_EXPO||_t->token==T_TRUE||
		_t->token==T_FALSE||_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||
		_t->token==CHARACTER_SUBSTRING||_t->token==IO_SPEC_LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "endfile_statement", _t);
		}
		}
		x_io_specifier(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "endfile_statement", _t);
	}
	*_root = _t;
}

void x_rewind_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==REWIND) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(REWIND);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==LP||_t->token==FUNCTION_NAME||_t->token==STAR||
		_t->token==CONSTINT||_t->token==MIN||_t->token==INTEGER_ID||
		_t->token==REAL_ID||_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||
		_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||
		_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||
		_t->token==UNARY_PLU||_t->token==NOT||_t->token==UNARY_MIN||
		_t->token==PLU||_t->token==MUL||_t->token==POW||
		_t->token==AND||_t->token==OR||_t->token==NEQV||
		_t->token==EQV||_t->token==LT||_t->token==LE||
		_t->token==EQ||_t->token==NE||_t->token==GT||
		_t->token==GE||_t->token==IS||_t->token==HEX_CONST||
		_t->token==BASIC_REAL||_t->token==REAL_EXPO||_t->token==T_TRUE||
		_t->token==T_FALSE||_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||
		_t->token==CHARACTER_SUBSTRING||_t->token==IO_SPEC_LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "rewind_statement", _t);
		}
		}
		x_io_specifier(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "rewind_statement", _t);
	}
	*_root = _t;
}

void x_io_specifier(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==IO_SPEC_LP) ) {
		_MATCH(IO_SPEC_LP);
		_RIGHT;
		if ( _t!=NULL && (_t->token==UNIT) ) {
			_MATCH(UNIT);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==LP||_t->token==FUNCTION_NAME||_t->token==STAR||
		_t->token==CONSTINT||_t->token==MIN||_t->token==INTEGER_ID||
		_t->token==REAL_ID||_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||
		_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||
		_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||
		_t->token==UNARY_PLU||_t->token==NOT||_t->token==UNARY_MIN||
		_t->token==PLU||_t->token==MUL||_t->token==POW||
		_t->token==AND||_t->token==OR||_t->token==NEQV||
		_t->token==EQV||_t->token==LT||_t->token==LE||
		_t->token==EQ||_t->token==NE||_t->token==GT||
		_t->token==GE||_t->token==IS||_t->token==HEX_CONST||
		_t->token==BASIC_REAL||_t->token==REAL_EXPO||_t->token==T_TRUE||
		_t->token==T_FALSE||_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||
		_t->token==CHARACTER_SUBSTRING) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "io_specifier", _t);
		}
		}
		x_unit_id(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==ERR) ) {
				{_SAVE; TREE_CONSTR_PTRS;
				_MATCH(ERR);
				_DOWN;
				_MATCH(COMMA);
				_RIGHT;
				_MATCH(EQUAL);
				_RIGHT;
				_MATCH(CONSTINT);
				_RESTORE;
				}
				_RIGHT;
			}
			else {
			if ( _t!=NULL && (_t->token==IOSTAT) ) {
				{_SAVE; TREE_CONSTR_PTRS;
				_MATCH(IOSTAT);
				_DOWN;
				_MATCH(COMMA);
				_RIGHT;
				_MATCH(EQUAL);
				_RIGHT;
				x_exp_operand(_parser, &_t);
				_RESTORE;
				}
				_RIGHT;
			}
			else {
			if ( _t!=NULL && (_t->token==IO_SPEC_RP) ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "io_specifier", _t);
			}
			}
			}
		}
		}
		_MATCH(IO_SPEC_RP);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==LP||_t->token==FUNCTION_NAME||_t->token==STAR||
	_t->token==CONSTINT||_t->token==MIN||_t->token==INTEGER_ID||
	_t->token==REAL_ID||_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||
	_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||
	_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||
	_t->token==UNARY_PLU||_t->token==NOT||_t->token==UNARY_MIN||
	_t->token==PLU||_t->token==MUL||_t->token==POW||
	_t->token==AND||_t->token==OR||_t->token==NEQV||
	_t->token==EQV||_t->token==LT||_t->token==LE||
	_t->token==EQ||_t->token==NE||_t->token==GT||
	_t->token==GE||_t->token==IS||_t->token==HEX_CONST||
	_t->token==BASIC_REAL||_t->token==REAL_EXPO||_t->token==T_TRUE||
	_t->token==T_FALSE||_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||
	_t->token==CHARACTER_SUBSTRING) ) {
		x_unit_id(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "io_specifier", _t);
	}
	}
	*_root = _t;
}

 SORAST *  x_read_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	 SORAST *Format ;
	if ( _t!=NULL && (_t->token==READ) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(READ);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "read_statement", _t);
		}
		}
		 Format =x_control_info(_parser, &_t);
		x_input_list(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "read_statement", _t);
	}
	*_root = _t;
	return Format;
}

 SORAST *  x_write_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	 SORAST *Format ;
	if ( _t!=NULL && (_t->token==WRITE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(WRITE);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "write_statement", _t);
		}
		}
		 Format =x_control_info(_parser, &_t);
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==LP||_t->token==FUNCTION_NAME||_t->token==CONSTINT||
		_t->token==MIN||_t->token==INTEGER_ID||_t->token==REAL_ID||
		_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
		_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
		_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||
		_t->token==NOT||_t->token==UNARY_MIN||_t->token==PLU||
		_t->token==MUL||_t->token==POW||_t->token==AND||
		_t->token==OR||_t->token==NEQV||_t->token==EQV||
		_t->token==LT||_t->token==LE||_t->token==EQ||
		_t->token==NE||_t->token==GT||_t->token==GE||
		_t->token==IS||_t->token==HEX_CONST||_t->token==BASIC_REAL||
		_t->token==REAL_EXPO||_t->token==T_TRUE||_t->token==T_FALSE||
		_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||_t->token==CHARACTER_SUBSTRING||
		_t->token==IMPLIED_LP) ) {
			x_output_list(_parser, &_t);
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "write_statement", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "write_statement", _t);
	}
	*_root = _t;
	return Format;
}

 SORAST *  x_control_info(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	 SORAST *Format ;
	if ( _t!=NULL && (_t->token==LP) ) {
		Format = NULL;  
		_MATCH(LP);
		_RIGHT;
		if ( _t!=NULL && (_t->token==COMMA) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(COMMA);
			_DOWN;
			x_unit_id(_parser, &_t);
			 Format =x_format_id(_parser, &_t);
			_RESTORE;
			}
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==APOSTROPHY) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(APOSTROPHY);
			_DOWN;
			x_unit_id(_parser, &_t);
			x_integer_expr(_parser, &_t);
			_RESTORE;
			}
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==EQUAL) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(EQUAL);
			_DOWN;
			_MATCH(UNIT);
			_RIGHT;
			x_unit_id(_parser, &_t);
			_RESTORE;
			}
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==LP||_t->token==FUNCTION_NAME||_t->token==STAR||
		_t->token==CONSTINT||_t->token==MIN||_t->token==INTEGER_ID||
		_t->token==REAL_ID||_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||
		_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||
		_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||
		_t->token==UNARY_PLU||_t->token==NOT||_t->token==UNARY_MIN||
		_t->token==PLU||_t->token==MUL||_t->token==POW||
		_t->token==AND||_t->token==OR||_t->token==NEQV||
		_t->token==EQV||_t->token==LT||_t->token==LE||
		_t->token==EQ||_t->token==NE||_t->token==GT||
		_t->token==GE||_t->token==IS||_t->token==HEX_CONST||
		_t->token==BASIC_REAL||_t->token==REAL_EXPO||_t->token==T_TRUE||
		_t->token==T_FALSE||_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||
		_t->token==CHARACTER_SUBSTRING) ) {
			x_unit_id(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "control_info", _t);
		}
		}
		}
		}
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				SORAST *l_node;  
				 l_node =x_the_remainder(_parser, &_t);
				if(l_node != NULL) Format = l_node;  
			}
			else {
			if ( _t!=NULL && (_t->token==RP) ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "control_info", _t);
			}
			}
		}
		}
		_MATCH(RP);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "control_info", _t);
	}
	*_root = _t;
	return Format;
}

 SORAST *  x_the_remainder(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	 SORAST *Format ;
	if ( _t!=NULL && (_t->token==COMMA) ) {
		Format = NULL;  
		_MATCH(COMMA);
		_RIGHT;
		if ( _t!=NULL && (_t->token==FMT) ) {
			_MATCH(FMT);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			 Format =x_format_id(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==IO_DATA) ) {
			_MATCH(IO_DATA);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_integer_expr(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==REC) ) {
			_MATCH(REC);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_integer_expr(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==END) ) {
			_MATCH(END);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			_MATCH(CONSTINT);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==ERR) ) {
			_MATCH(ERR);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			_MATCH(CONSTINT);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==IOSTAT) ) {
			_MATCH(IOSTAT);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_exp_operand(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==URGENT) ) {
			_MATCH(URGENT);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_expression(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==LP||_t->token==FUNCTION_NAME||_t->token==STAR||
		_t->token==CONSTINT||_t->token==MIN||_t->token==INTEGER_ID||
		_t->token==REAL_ID||_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||
		_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||
		_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||
		_t->token==UNARY_PLU||_t->token==NOT||_t->token==UNARY_MIN||
		_t->token==PLU||_t->token==MUL||_t->token==POW||
		_t->token==AND||_t->token==OR||_t->token==NEQV||
		_t->token==EQV||_t->token==LT||_t->token==LE||
		_t->token==EQ||_t->token==NE||_t->token==GT||
		_t->token==GE||_t->token==IS||_t->token==HEX_CONST||
		_t->token==BASIC_REAL||_t->token==REAL_EXPO||_t->token==T_TRUE||
		_t->token==T_FALSE||_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||
		_t->token==CHARACTER_SUBSTRING||_t->token==SLASH) ) {
			 Format =x_format_id(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "the_remainder", _t);
		}
		}
		}
		}
		}
		}
		}
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "the_remainder", _t);
	}
	*_root = _t;
	return Format;
}

void x_unit_id(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==STAR) ) {
		_MATCH(STAR);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==LP||_t->token==FUNCTION_NAME||_t->token==CONSTINT||
	_t->token==MIN||_t->token==INTEGER_ID||_t->token==REAL_ID||
	_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
	_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
	_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||
	_t->token==NOT||_t->token==UNARY_MIN||_t->token==PLU||
	_t->token==MUL||_t->token==POW||_t->token==AND||
	_t->token==OR||_t->token==NEQV||_t->token==EQV||
	_t->token==LT||_t->token==LE||_t->token==EQ||
	_t->token==NE||_t->token==GT||_t->token==GE||
	_t->token==IS||_t->token==HEX_CONST||_t->token==BASIC_REAL||
	_t->token==REAL_EXPO||_t->token==T_TRUE||_t->token==T_FALSE||
	_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||_t->token==CHARACTER_SUBSTRING) ) {
		x_expression(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "unit_id", _t);
	}
	}
	*_root = _t;
}

 SORAST *  x_format_id(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	 SORAST *Format ;
	SORAST *f=NULL;
	if ( _t!=NULL && (_t->token==STAR) ) {
		_MATCH(STAR);
		f=(SORAST *)_t;
		_RIGHT;
		if ( _t!=NULL && (_t->token==SLASH) ) {
			_MATCH(SLASH);
			_RIGHT;
		}
		else {
		if ( _t==NULL || (_t->token==COMMA||_t->token==RP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "format_id", _t);
		}
		}
		Format = f;  
	}
	else {
	if ( _t!=NULL && (_t->token==SLASH) ) {
		_MATCH(SLASH);
		f=(SORAST *)_t;
		_RIGHT;
		Format = f;  
	}
	else {
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==LP||_t->token==FUNCTION_NAME||_t->token==CONSTINT||
	_t->token==MIN||_t->token==INTEGER_ID||_t->token==REAL_ID||
	_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
	_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
	_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||
	_t->token==NOT||_t->token==UNARY_MIN||_t->token==PLU||
	_t->token==MUL||_t->token==POW||_t->token==AND||
	_t->token==OR||_t->token==NEQV||_t->token==EQV||
	_t->token==LT||_t->token==LE||_t->token==EQ||
	_t->token==NE||_t->token==GT||_t->token==GE||
	_t->token==IS||_t->token==HEX_CONST||_t->token==BASIC_REAL||
	_t->token==REAL_EXPO||_t->token==T_TRUE||_t->token==T_FALSE||
	_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||_t->token==CHARACTER_SUBSTRING) ) {
		f=(SORAST *)_t; x_expression(_parser, &_t);
		Format = f;  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "format_id", _t);
	}
	}
	}
	*_root = _t;
	return Format;
}

void x_input_list(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==LP||_t->token==FUNCTION_NAME||
	_t->token==CONSTINT||_t->token==INTEGER_ID||_t->token==REAL_ID||
	_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
	_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
	_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==HEX_CONST||
	_t->token==BASIC_REAL||_t->token==REAL_EXPO||_t->token==T_TRUE||
	_t->token==T_FALSE||_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||
	_t->token==CHARACTER_SUBSTRING||_t->token==IMPLIED_LP) ) {
		x_input_item(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				_MATCH(COMMA);
				_RIGHT;
				x_input_item(_parser, &_t);
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "input_list", _t);
			}
			}
		}
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "input_list", _t);
	}
	*_root = _t;
}

void x_input_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==LP||_t->token==FUNCTION_NAME||
	_t->token==CONSTINT||_t->token==INTEGER_ID||_t->token==REAL_ID||
	_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
	_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
	_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==HEX_CONST||
	_t->token==BASIC_REAL||_t->token==REAL_EXPO||_t->token==T_TRUE||
	_t->token==T_FALSE||_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||
	_t->token==CHARACTER_SUBSTRING||_t->token==IMPLIED_LP) ) {
		if ( _t!=NULL && (_t->token==LP||_t->token==FUNCTION_NAME||
		_t->token==CONSTINT||_t->token==INTEGER_ID||_t->token==REAL_ID||
		_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
		_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
		_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==HEX_CONST||
		_t->token==BASIC_REAL||_t->token==REAL_EXPO||_t->token==T_TRUE||
		_t->token==T_FALSE||_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||
		_t->token==CHARACTER_SUBSTRING) ) {
			x_exp_operand(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==IMPLIED_LP) ) {
			x_inp_implied_list(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "input_item", _t);
		}
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "input_item", _t);
	}
	*_root = _t;
}

void x_inp_implied_list(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==IMPLIED_LP) ) {
		_MATCH(IMPLIED_LP);
		_RIGHT;
		{int _done=0;
		do {
			if ( _t!=NULL && (_t->token==LP||_t->token==FUNCTION_NAME||
			_t->token==CONSTINT||_t->token==INTEGER_ID||_t->token==REAL_ID||
			_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
			_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
			_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==HEX_CONST||
			_t->token==BASIC_REAL||_t->token==REAL_EXPO||_t->token==T_TRUE||
			_t->token==T_FALSE||_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||
			_t->token==CHARACTER_SUBSTRING||_t->token==IMPLIED_LP) ) {
				x_input_item(_parser, &_t);
				_MATCH(COMMA);
				_RIGHT;
			}
			else {
			if ( _t!=NULL && (_t->token==IMPLIED_DO_VARIABLE) ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "inp_implied_list", _t);
			}
			}
		} while ( !_done );
		}
		x_implied_loop(_parser, &_t);
		_MATCH(IMPLIED_RP);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "inp_implied_list", _t);
	}
	*_root = _t;
}

void x_output_list(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==LP||_t->token==FUNCTION_NAME||_t->token==CONSTINT||
	_t->token==MIN||_t->token==INTEGER_ID||_t->token==REAL_ID||
	_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
	_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
	_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||
	_t->token==NOT||_t->token==UNARY_MIN||_t->token==PLU||
	_t->token==MUL||_t->token==POW||_t->token==AND||
	_t->token==OR||_t->token==NEQV||_t->token==EQV||
	_t->token==LT||_t->token==LE||_t->token==EQ||
	_t->token==NE||_t->token==GT||_t->token==GE||
	_t->token==IS||_t->token==HEX_CONST||_t->token==BASIC_REAL||
	_t->token==REAL_EXPO||_t->token==T_TRUE||_t->token==T_FALSE||
	_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||_t->token==CHARACTER_SUBSTRING||
	_t->token==IMPLIED_LP) ) {
		x_output_item(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				_MATCH(COMMA);
				_RIGHT;
				x_output_item(_parser, &_t);
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "output_list", _t);
			}
			}
		}
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "output_list", _t);
	}
	*_root = _t;
}

void x_output_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==IMPLIED_LP) ) {
		x_outp_implied_list(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==LP||_t->token==FUNCTION_NAME||_t->token==CONSTINT||
	_t->token==MIN||_t->token==INTEGER_ID||_t->token==REAL_ID||
	_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
	_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
	_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||
	_t->token==NOT||_t->token==UNARY_MIN||_t->token==PLU||
	_t->token==MUL||_t->token==POW||_t->token==AND||
	_t->token==OR||_t->token==NEQV||_t->token==EQV||
	_t->token==LT||_t->token==LE||_t->token==EQ||
	_t->token==NE||_t->token==GT||_t->token==GE||
	_t->token==IS||_t->token==HEX_CONST||_t->token==BASIC_REAL||
	_t->token==REAL_EXPO||_t->token==T_TRUE||_t->token==T_FALSE||
	_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||_t->token==CHARACTER_SUBSTRING) ) {
		x_rvalue(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "output_item", _t);
	}
	}
	*_root = _t;
}

void x_outp_implied_list(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==IMPLIED_LP) ) {
		_MATCH(IMPLIED_LP);
		_RIGHT;
		{int _done=0;
		do {
			if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
			_t->token==LP||_t->token==FUNCTION_NAME||_t->token==CONSTINT||
			_t->token==MIN||_t->token==INTEGER_ID||_t->token==REAL_ID||
			_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
			_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
			_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||
			_t->token==NOT||_t->token==UNARY_MIN||_t->token==PLU||
			_t->token==MUL||_t->token==POW||_t->token==AND||
			_t->token==OR||_t->token==NEQV||_t->token==EQV||
			_t->token==LT||_t->token==LE||_t->token==EQ||
			_t->token==NE||_t->token==GT||_t->token==GE||
			_t->token==IS||_t->token==HEX_CONST||_t->token==BASIC_REAL||
			_t->token==REAL_EXPO||_t->token==T_TRUE||_t->token==T_FALSE||
			_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||_t->token==CHARACTER_SUBSTRING||
			_t->token==IMPLIED_LP) ) {
				x_output_item(_parser, &_t);
				_MATCH(COMMA);
				_RIGHT;
			}
			else {
			if ( _t!=NULL && (_t->token==IMPLIED_DO_VARIABLE) ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "outp_implied_list", _t);
			}
			}
		} while ( !_done );
		}
		x_implied_loop(_parser, &_t);
		_MATCH(IMPLIED_RP);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "outp_implied_list", _t);
	}
	*_root = _t;
}

void x_implied_loop(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==IMPLIED_DO_VARIABLE) ) {
		_MATCH(IMPLIED_DO_VARIABLE);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		x_integer_expr(_parser, &_t);
		_MATCH(COMMA);
		_RIGHT;
		x_integer_expr(_parser, &_t);
		if ( _t!=NULL && (_t->token==COMMA) ) {
			_MATCH(COMMA);
			_RIGHT;
			x_integer_expr(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==IMPLIED_RP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "implied_loop", _t);
		}
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "implied_loop", _t);
	}
	*_root = _t;
}

void x_open_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==OPEN) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(OPEN);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "open_statement", _t);
		}
		}
		_MATCH(LP);
		_RIGHT;
		x_open_item(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				_MATCH(COMMA);
				_RIGHT;
				x_open_item(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==RP) ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "open_statement", _t);
			}
			}
		}
		}
		_MATCH(RP);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "open_statement", _t);
	}
	*_root = _t;
}

void x_open_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==LP||_t->token==FUNCTION_NAME||_t->token==STAR||
	_t->token==CONSTINT||_t->token==MIN||_t->token==INTEGER_ID||
	_t->token==REAL_ID||_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||
	_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||
	_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||
	_t->token==UNARY_PLU||_t->token==NOT||_t->token==UNARY_MIN||
	_t->token==PLU||_t->token==MUL||_t->token==POW||
	_t->token==AND||_t->token==OR||_t->token==NEQV||
	_t->token==EQV||_t->token==LT||_t->token==LE||
	_t->token==EQ||_t->token==NE||_t->token==GT||
	_t->token==GE||_t->token==IS||_t->token==HEX_CONST||
	_t->token==BASIC_REAL||_t->token==REAL_EXPO||_t->token==T_TRUE||
	_t->token==T_FALSE||_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||
	_t->token==CHARACTER_SUBSTRING||_t->token==UNIT) ) {
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==LP||_t->token==FUNCTION_NAME||_t->token==STAR||
		_t->token==CONSTINT||_t->token==MIN||_t->token==INTEGER_ID||
		_t->token==REAL_ID||_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||
		_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||
		_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||
		_t->token==UNARY_PLU||_t->token==NOT||_t->token==UNARY_MIN||
		_t->token==PLU||_t->token==MUL||_t->token==POW||
		_t->token==AND||_t->token==OR||_t->token==NEQV||
		_t->token==EQV||_t->token==LT||_t->token==LE||
		_t->token==EQ||_t->token==NE||_t->token==GT||
		_t->token==GE||_t->token==IS||_t->token==HEX_CONST||
		_t->token==BASIC_REAL||_t->token==REAL_EXPO||_t->token==T_TRUE||
		_t->token==T_FALSE||_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||
		_t->token==CHARACTER_SUBSTRING||_t->token==UNIT) ) {
			if ( _t!=NULL && (_t->token==UNIT) ) {
				_MATCH(UNIT);
				_RIGHT;
				_MATCH(EQUAL);
				_RIGHT;
			}
			else {
			if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
			_t->token==LP||_t->token==FUNCTION_NAME||_t->token==STAR||
			_t->token==CONSTINT||_t->token==MIN||_t->token==INTEGER_ID||
			_t->token==REAL_ID||_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||
			_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||
			_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||
			_t->token==UNARY_PLU||_t->token==NOT||_t->token==UNARY_MIN||
			_t->token==PLU||_t->token==MUL||_t->token==POW||
			_t->token==AND||_t->token==OR||_t->token==NEQV||
			_t->token==EQV||_t->token==LT||_t->token==LE||
			_t->token==EQ||_t->token==NE||_t->token==GT||
			_t->token==GE||_t->token==IS||_t->token==HEX_CONST||
			_t->token==BASIC_REAL||_t->token==REAL_EXPO||_t->token==T_TRUE||
			_t->token==T_FALSE||_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||
			_t->token==CHARACTER_SUBSTRING) ) {
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "open_item", _t);
			}
			}
			x_unit_id(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "open_item", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==ERR) ) {
		if ( _t!=NULL && (_t->token==ERR) ) {
			_MATCH(ERR);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			_MATCH(CONSTINT);
			_RIGHT;
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "open_item", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==FILE_WORD) ) {
		if ( _t!=NULL && (_t->token==FILE_WORD) ) {
			_MATCH(FILE_WORD);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_expression(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "open_item", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==STATUS) ) {
		if ( _t!=NULL && (_t->token==STATUS) ) {
			_MATCH(STATUS);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_expression(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "open_item", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==ACCESS) ) {
		if ( _t!=NULL && (_t->token==ACCESS) ) {
			_MATCH(ACCESS);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_expression(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "open_item", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==FORM) ) {
		if ( _t!=NULL && (_t->token==FORM) ) {
			_MATCH(FORM);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_expression(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "open_item", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==RECL) ) {
		if ( _t!=NULL && (_t->token==RECL) ) {
			_MATCH(RECL);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_expression(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "open_item", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==IOSTAT) ) {
		if ( _t!=NULL && (_t->token==IOSTAT) ) {
			_MATCH(IOSTAT);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_exp_operand(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "open_item", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==TITLE) ) {
		if ( _t!=NULL && (_t->token==TITLE) ) {
			_MATCH(TITLE);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_expression(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "open_item", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==DISP) ) {
		if ( _t!=NULL && (_t->token==DISP) ) {
			_MATCH(DISP);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_expression(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "open_item", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==SUBFILE) ) {
		if ( _t!=NULL && (_t->token==SUBFILE) ) {
			_MATCH(SUBFILE);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_integer_expr(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "open_item", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==MAXRECSIZE) ) {
		if ( _t!=NULL && (_t->token==MAXRECSIZE) ) {
			_MATCH(MAXRECSIZE);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_integer_expr(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "open_item", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==SAVEFACTOR) ) {
		if ( _t!=NULL && (_t->token==SAVEFACTOR) ) {
			_MATCH(SAVEFACTOR);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_integer_expr(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "open_item", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==OPENTYPE) ) {
		if ( _t!=NULL && (_t->token==OPENTYPE) ) {
			_MATCH(OPENTYPE);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_expression(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "open_item", _t);
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "open_item", _t);
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	*_root = _t;
}

void x_close_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==CLOSE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(CLOSE);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "close_statement", _t);
		}
		}
		_MATCH(LP);
		_RIGHT;
		x_close_item(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				_MATCH(COMMA);
				_RIGHT;
				x_close_item(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==RP) ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "close_statement", _t);
			}
			}
		}
		}
		_MATCH(RP);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "close_statement", _t);
	}
	*_root = _t;
}

void x_close_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==LP||_t->token==FUNCTION_NAME||_t->token==STAR||
	_t->token==CONSTINT||_t->token==MIN||_t->token==INTEGER_ID||
	_t->token==REAL_ID||_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||
	_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||
	_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||
	_t->token==UNARY_PLU||_t->token==NOT||_t->token==UNARY_MIN||
	_t->token==PLU||_t->token==MUL||_t->token==POW||
	_t->token==AND||_t->token==OR||_t->token==NEQV||
	_t->token==EQV||_t->token==LT||_t->token==LE||
	_t->token==EQ||_t->token==NE||_t->token==GT||
	_t->token==GE||_t->token==IS||_t->token==HEX_CONST||
	_t->token==BASIC_REAL||_t->token==REAL_EXPO||_t->token==T_TRUE||
	_t->token==T_FALSE||_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||
	_t->token==CHARACTER_SUBSTRING||_t->token==UNIT) ) {
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==LP||_t->token==FUNCTION_NAME||_t->token==STAR||
		_t->token==CONSTINT||_t->token==MIN||_t->token==INTEGER_ID||
		_t->token==REAL_ID||_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||
		_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||
		_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||
		_t->token==UNARY_PLU||_t->token==NOT||_t->token==UNARY_MIN||
		_t->token==PLU||_t->token==MUL||_t->token==POW||
		_t->token==AND||_t->token==OR||_t->token==NEQV||
		_t->token==EQV||_t->token==LT||_t->token==LE||
		_t->token==EQ||_t->token==NE||_t->token==GT||
		_t->token==GE||_t->token==IS||_t->token==HEX_CONST||
		_t->token==BASIC_REAL||_t->token==REAL_EXPO||_t->token==T_TRUE||
		_t->token==T_FALSE||_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||
		_t->token==CHARACTER_SUBSTRING||_t->token==UNIT) ) {
			if ( _t!=NULL && (_t->token==UNIT) ) {
				_MATCH(UNIT);
				_RIGHT;
				_MATCH(EQUAL);
				_RIGHT;
			}
			else {
			if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
			_t->token==LP||_t->token==FUNCTION_NAME||_t->token==STAR||
			_t->token==CONSTINT||_t->token==MIN||_t->token==INTEGER_ID||
			_t->token==REAL_ID||_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||
			_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||
			_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||
			_t->token==UNARY_PLU||_t->token==NOT||_t->token==UNARY_MIN||
			_t->token==PLU||_t->token==MUL||_t->token==POW||
			_t->token==AND||_t->token==OR||_t->token==NEQV||
			_t->token==EQV||_t->token==LT||_t->token==LE||
			_t->token==EQ||_t->token==NE||_t->token==GT||
			_t->token==GE||_t->token==IS||_t->token==HEX_CONST||
			_t->token==BASIC_REAL||_t->token==REAL_EXPO||_t->token==T_TRUE||
			_t->token==T_FALSE||_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||
			_t->token==CHARACTER_SUBSTRING) ) {
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "close_item", _t);
			}
			}
			x_unit_id(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "close_item", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==ERR) ) {
		if ( _t!=NULL && (_t->token==ERR) ) {
			_MATCH(ERR);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			_MATCH(CONSTINT);
			_RIGHT;
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "close_item", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==STATUS) ) {
		if ( _t!=NULL && (_t->token==STATUS) ) {
			_MATCH(STATUS);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_close_name(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "close_item", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==IOSTAT) ) {
		if ( _t!=NULL && (_t->token==IOSTAT) ) {
			_MATCH(IOSTAT);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_exp_operand(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "close_item", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==DISP) ) {
		if ( _t!=NULL && (_t->token==DISP) ) {
			_MATCH(DISP);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_close_name(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "close_item", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==SUBFILE) ) {
		if ( _t!=NULL && (_t->token==SUBFILE) ) {
			_MATCH(SUBFILE);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			x_integer_expr(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "close_item", _t);
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "close_item", _t);
	}
	}
	}
	}
	}
	}
	*_root = _t;
}

void x_close_name(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==IDENTIFIER||_t->token==QUOTED_STRING) ) {
		if ( _t!=NULL && (_t->token==IDENTIFIER) ) {
			_MATCH(IDENTIFIER);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==QUOTED_STRING) ) {
			_MATCH(QUOTED_STRING);
			_RIGHT;
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "close_name", _t);
		}
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "close_name", _t);
	}
	*_root = _t;
}

void x_call_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==CALL) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(CALL);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==FUNCTION_NAME) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "call_statement", _t);
		}
		}
		_MATCH(FUNCTION_NAME);
		_RIGHT;
		if ( _t!=NULL && (_t->token==LP) ) {
			x_call_arg_list(_parser, &_t);
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "call_statement", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "call_statement", _t);
	}
	*_root = _t;
}

void x_call_arg_list(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==LP) ) {
		_MATCH(LP);
		_RIGHT;
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==LP||_t->token==FUNCTION_NAME||_t->token==STAR||
		_t->token==CONSTINT||_t->token==MIN||_t->token==INTEGER_ID||
		_t->token==REAL_ID||_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||
		_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||
		_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||
		_t->token==UNARY_PLU||_t->token==NOT||_t->token==UNARY_MIN||
		_t->token==PLU||_t->token==MUL||_t->token==POW||
		_t->token==AND||_t->token==OR||_t->token==NEQV||
		_t->token==EQV||_t->token==LT||_t->token==LE||
		_t->token==EQ||_t->token==NE||_t->token==GT||
		_t->token==GE||_t->token==IS||_t->token==HEX_CONST||
		_t->token==BASIC_REAL||_t->token==REAL_EXPO||_t->token==T_TRUE||
		_t->token==T_FALSE||_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||
		_t->token==CHARACTER_SUBSTRING||_t->token==AMPERSAND) ) {
			x_call_arg_item(_parser, &_t);
			{int _done=0;
			while ( !_done ) {
				if ( _t!=NULL && (_t->token==COMMA) ) {
					_MATCH(COMMA);
					_RIGHT;
					x_call_arg_item(_parser, &_t);
				}
				else {
				if ( _t!=NULL && (_t->token==RP) ) {
					_done = 1;
				}
				else {
					if ( _parser->guessing ) _GUESS_FAIL;
					no_viable_alt(_parser, "call_arg_list", _t);
				}
				}
			}
			}
		}
		else {
		if ( _t!=NULL && (_t->token==RP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "call_arg_list", _t);
		}
		}
		_MATCH(RP);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "call_arg_list", _t);
	}
	*_root = _t;
}

void x_call_arg_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==LP||_t->token==FUNCTION_NAME||_t->token==STAR||
	_t->token==CONSTINT||_t->token==MIN||_t->token==INTEGER_ID||
	_t->token==REAL_ID||_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||
	_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||
	_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||
	_t->token==UNARY_PLU||_t->token==NOT||_t->token==UNARY_MIN||
	_t->token==PLU||_t->token==MUL||_t->token==POW||
	_t->token==AND||_t->token==OR||_t->token==NEQV||
	_t->token==EQV||_t->token==LT||_t->token==LE||
	_t->token==EQ||_t->token==NE||_t->token==GT||
	_t->token==GE||_t->token==IS||_t->token==HEX_CONST||
	_t->token==BASIC_REAL||_t->token==REAL_EXPO||_t->token==T_TRUE||
	_t->token==T_FALSE||_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||
	_t->token==CHARACTER_SUBSTRING||_t->token==AMPERSAND) ) {
		if ( _t!=NULL && (_t->token==STAR||_t->token==AMPERSAND) ) {
			if ( _t!=NULL && (_t->token==STAR) ) {
				_MATCH(STAR);
				_RIGHT;
			}
			else {
			if ( _t!=NULL && (_t->token==AMPERSAND) ) {
				_MATCH(AMPERSAND);
				_RIGHT;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "call_arg_item", _t);
			}
			}
			_MATCH(CONSTINT);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==LP||_t->token==FUNCTION_NAME||_t->token==CONSTINT||
		_t->token==MIN||_t->token==INTEGER_ID||_t->token==REAL_ID||
		_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
		_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
		_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||
		_t->token==NOT||_t->token==UNARY_MIN||_t->token==PLU||
		_t->token==MUL||_t->token==POW||_t->token==AND||
		_t->token==OR||_t->token==NEQV||_t->token==EQV||
		_t->token==LT||_t->token==LE||_t->token==EQ||
		_t->token==NE||_t->token==GT||_t->token==GE||
		_t->token==IS||_t->token==HEX_CONST||_t->token==BASIC_REAL||
		_t->token==REAL_EXPO||_t->token==T_TRUE||_t->token==T_FALSE||
		_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||_t->token==CHARACTER_SUBSTRING) ) {
			x_expression(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "call_arg_item", _t);
		}
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "call_arg_item", _t);
	}
	*_root = _t;
}

void x_export_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==EXPORT) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(EXPORT);
		_DOWN;
		{int _done=0;
		do {
			if ( _t!=NULL ) {
				x_any_token(_parser, &_t);
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "export_statement", _t);
			}
			}
		} while ( !_done );
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "export_statement", _t);
	}
	*_root = _t;
}

void x_subroutine_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==SUBROUTINE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(SUBROUTINE);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==IDENTIFIER) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "subroutine_statement", _t);
		}
		}
		_MATCH(IDENTIFIER);
		_RIGHT;
		if ( _t!=NULL && (_t->token==LP) ) {
			x_call_arg_list(_parser, &_t);
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "subroutine_statement", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "subroutine_statement", _t);
	}
	*_root = _t;
}

void x_entry_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==ENTRY) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(ENTRY);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==IDENTIFIER) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "entry_statement", _t);
		}
		}
		_MATCH(IDENTIFIER);
		_RIGHT;
		if ( _t!=NULL && (_t->token==LP) ) {
			x_call_arg_list(_parser, &_t);
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "entry_statement", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "entry_statement", _t);
	}
	*_root = _t;
}

void x_function_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==FUNCTION) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(FUNCTION);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==IDENTIFIER||_t->token==INTEGER||
		_t->token==REAL||_t->token==DOUBLE_PRECISION||_t->token==LOGICAL||
		_t->token==CHARACTER||_t->token==COMPLEX||_t->token==DOUBLE_COMPLEX) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "function_statement", _t);
		}
		}
		if ( _t!=NULL && (_t->token==INTEGER||_t->token==REAL||
		_t->token==DOUBLE_PRECISION||_t->token==LOGICAL||_t->token==CHARACTER||
		_t->token==COMPLEX||_t->token==DOUBLE_COMPLEX) ) {
			x_function_type(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==IDENTIFIER) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "function_statement", _t);
		}
		}
		_MATCH(IDENTIFIER);
		_RIGHT;
		_MATCH(LP);
		_RIGHT;
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==LP||_t->token==FUNCTION_NAME||_t->token==CONSTINT||
		_t->token==MIN||_t->token==INTEGER_ID||_t->token==REAL_ID||
		_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
		_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
		_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||
		_t->token==NOT||_t->token==UNARY_MIN||_t->token==PLU||
		_t->token==MUL||_t->token==POW||_t->token==AND||
		_t->token==OR||_t->token==NEQV||_t->token==EQV||
		_t->token==LT||_t->token==LE||_t->token==EQ||
		_t->token==NE||_t->token==GT||_t->token==GE||
		_t->token==IS||_t->token==HEX_CONST||_t->token==BASIC_REAL||
		_t->token==REAL_EXPO||_t->token==T_TRUE||_t->token==T_FALSE||
		_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||_t->token==CHARACTER_SUBSTRING||
		_t->token==SLASH) ) {
			x_function_arg_list(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==RP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "function_statement", _t);
		}
		}
		_MATCH(RP);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "function_statement", _t);
	}
	*_root = _t;
}

void x_function_type(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==INTEGER||_t->token==REAL||
	_t->token==DOUBLE_PRECISION||_t->token==LOGICAL||_t->token==CHARACTER||
	_t->token==COMPLEX||_t->token==DOUBLE_COMPLEX) ) {
		if ( _t!=NULL && (_t->token==INTEGER) ) {
			_MATCH(INTEGER);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==REAL) ) {
			_MATCH(REAL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==DOUBLE_PRECISION) ) {
			_MATCH(DOUBLE_PRECISION);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==LOGICAL) ) {
			_MATCH(LOGICAL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==CHARACTER) ) {
			_MATCH(CHARACTER);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==COMPLEX) ) {
			_MATCH(COMPLEX);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==DOUBLE_COMPLEX) ) {
			_MATCH(DOUBLE_COMPLEX);
			_RIGHT;
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "function_type", _t);
		}
		}
		}
		}
		}
		}
		}
		if ( _t!=NULL && (_t->token==STAR) ) {
			_MATCH(STAR);
			_RIGHT;
			x_length_spec(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==IDENTIFIER) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "function_type", _t);
		}
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "function_type", _t);
	}
	*_root = _t;
}

void x_function_arg_list(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==LP||_t->token==FUNCTION_NAME||_t->token==CONSTINT||
	_t->token==MIN||_t->token==INTEGER_ID||_t->token==REAL_ID||
	_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
	_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
	_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||
	_t->token==NOT||_t->token==UNARY_MIN||_t->token==PLU||
	_t->token==MUL||_t->token==POW||_t->token==AND||
	_t->token==OR||_t->token==NEQV||_t->token==EQV||
	_t->token==LT||_t->token==LE||_t->token==EQ||
	_t->token==NE||_t->token==GT||_t->token==GE||
	_t->token==IS||_t->token==HEX_CONST||_t->token==BASIC_REAL||
	_t->token==REAL_EXPO||_t->token==T_TRUE||_t->token==T_FALSE||
	_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||_t->token==CHARACTER_SUBSTRING||
	_t->token==SLASH) ) {
		if ( _t!=NULL && (_t->token==SLASH) ) {
			_MATCH(SLASH);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==LP||_t->token==FUNCTION_NAME||_t->token==CONSTINT||
		_t->token==MIN||_t->token==INTEGER_ID||_t->token==REAL_ID||
		_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
		_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
		_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||
		_t->token==NOT||_t->token==UNARY_MIN||_t->token==PLU||
		_t->token==MUL||_t->token==POW||_t->token==AND||
		_t->token==OR||_t->token==NEQV||_t->token==EQV||
		_t->token==LT||_t->token==LE||_t->token==EQ||
		_t->token==NE||_t->token==GT||_t->token==GE||
		_t->token==IS||_t->token==HEX_CONST||_t->token==BASIC_REAL||
		_t->token==REAL_EXPO||_t->token==T_TRUE||_t->token==T_FALSE||
		_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||_t->token==CHARACTER_SUBSTRING) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "function_arg_list", _t);
		}
		}
		x_expression(_parser, &_t);
		if ( _t!=NULL && (_t->token==SLASH) ) {
			_MATCH(SLASH);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==COMMA||_t->token==RP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "function_arg_list", _t);
		}
		}
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				_MATCH(COMMA);
				_RIGHT;
				if ( _t!=NULL && (_t->token==SLASH) ) {
					_MATCH(SLASH);
					_RIGHT;
				}
				else {
				if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
				_t->token==LP||_t->token==FUNCTION_NAME||_t->token==CONSTINT||
				_t->token==MIN||_t->token==INTEGER_ID||_t->token==REAL_ID||
				_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
				_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
				_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||
				_t->token==NOT||_t->token==UNARY_MIN||_t->token==PLU||
				_t->token==MUL||_t->token==POW||_t->token==AND||
				_t->token==OR||_t->token==NEQV||_t->token==EQV||
				_t->token==LT||_t->token==LE||_t->token==EQ||
				_t->token==NE||_t->token==GT||_t->token==GE||
				_t->token==IS||_t->token==HEX_CONST||_t->token==BASIC_REAL||
				_t->token==REAL_EXPO||_t->token==T_TRUE||_t->token==T_FALSE||
				_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||_t->token==CHARACTER_SUBSTRING) ) {
				}
				else {
					if ( _parser->guessing ) _GUESS_FAIL;
					no_viable_alt(_parser, "function_arg_list", _t);
				}
				}
				x_expression(_parser, &_t);
				if ( _t!=NULL && (_t->token==SLASH) ) {
					_MATCH(SLASH);
					_RIGHT;
				}
				else {
				if ( _t!=NULL && (_t->token==COMMA||_t->token==RP) ) {
				}
				else {
					if ( _parser->guessing ) _GUESS_FAIL;
					no_viable_alt(_parser, "function_arg_list", _t);
				}
				}
			}
			else {
			if ( _t!=NULL && (_t->token==RP) ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "function_arg_list", _t);
			}
			}
		}
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "function_arg_list", _t);
	}
	*_root = _t;
}

void x_length_spec(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==LP) ) {
		_MATCH(LP);
		_RIGHT;
		if ( _t!=NULL && (_t->token==STAR) ) {
			_MATCH(STAR);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==DIV||_t->token==LP||
		_t->token==FUNCTION_NAME||_t->token==CONSTINT||_t->token==MIN||
		_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==INTEGER_ARRAY_ID||
		_t->token==UNARY_PLU||_t->token==UNARY_MIN||_t->token==PLU||
		_t->token==MUL||_t->token==HEX_CONST) ) {
			x_integer_expr(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "length_spec", _t);
		}
		}
		_MATCH(RP);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==CONSTINT) ) {
		_MATCH(CONSTINT);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "length_spec", _t);
	}
	}
	*_root = _t;
}

void x_block_if_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==BLOCK_IF) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(BLOCK_IF);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "block_if_statement", _t);
		}
		}
		_MATCH(LP);
		_RIGHT;
		x_expression(_parser, &_t);
		_MATCH(RP);
		_RIGHT;
		_MATCH(THEN);
		_RIGHT;
		x_block_if_block(_parser, &_t);
		if ( _t!=NULL && (_t->token==ELSE||_t->token==ELSE_IF) ) {
			if ( _t!=NULL && (_t->token==ELSE||_t->token==ELSE_IF) ) {
				if ( _t!=NULL && (_t->token==ELSE) ) {
					_MATCH(ELSE);
					_RIGHT;
				}
				else {
				if ( _t!=NULL && (_t->token==ELSE_IF) ) {
					_MATCH(ELSE_IF);
					_RIGHT;
					_MATCH(LP);
					_RIGHT;
					x_expression(_parser, &_t);
					_MATCH(RP);
					_RIGHT;
				}
				else {
					if ( _parser->guessing ) _GUESS_FAIL;
					no_viable_alt(_parser, "block_if_statement", _t);
				}
				}
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "block_if_statement", _t);
			}
			x_block_if_block(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==END_IF) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "block_if_statement", _t);
		}
		}
		_MATCH(END_IF);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "block_if_statement", _t);
	}
	*_root = _t;
}

void x_block_if_block(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==COMMENT_LINE||_t->token==BLANK_LINE||
	_t->token==EQUAL||_t->token==INQUIRE||_t->token==CONTROL_IMAGE||
	_t->token==FIND||_t->token==BACKSPACE||_t->token==ENDFILE||
	_t->token==REWIND||_t->token==READ||_t->token==WRITE||
	_t->token==OPEN||_t->token==CLOSE||_t->token==CALL||
	_t->token==BLOCK_IF||_t->token==ELSE||_t->token==ELSE_IF||
	_t->token==END_IF||_t->token==LOGICAL_IF||_t->token==ARITHMETIC_IF||
	_t->token==CONTINUE||_t->token==STOP||_t->token==RETURN||
	_t->token==UNCONDITIONAL_GOTO||_t->token==COMPUTED_GOTO||_t->token==ASSIGNED_GOTO||
	_t->token==DO||_t->token==CHANGE||_t->token==ASSIGN||
	_t->token==FORMAT) ) {
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMENT_LINE) ) {
				x_comment_line(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==BLANK_LINE) ) {
				x_blank_line(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==EQUAL) ) {
				x_assignment_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==DO) ) {
				x_do_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==CONTROL_IMAGE) ) {
				x_control_image(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==FORMAT) ) {
				x_format_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==READ) ) {
				x_read_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==WRITE) ) {
				x_write_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==OPEN) ) {
				x_open_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==CLOSE) ) {
				x_close_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==INQUIRE) ) {
				x_inquire_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==CHANGE) ) {
				x_change_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==FIND) ) {
				x_find_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==CALL) ) {
				x_call_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==BLOCK_IF) ) {
				x_block_if_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==ARITHMETIC_IF) ) {
				x_arithm_if_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==LOGICAL_IF) ) {
				x_log_if_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==UNCONDITIONAL_GOTO) ) {
				x_unconditional_goto(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==COMPUTED_GOTO) ) {
				x_computed_goto(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==ASSIGNED_GOTO) ) {
				x_assigned_goto(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==CONTINUE) ) {
				x_continue_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==STOP) ) {
				x_stop_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==RETURN) ) {
				x_return_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==BACKSPACE) ) {
				x_backspace_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==REWIND) ) {
				x_rewind_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==ENDFILE) ) {
				x_endfile_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==ASSIGN) ) {
				x_assign_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==ELSE||_t->token==ELSE_IF||
			_t->token==END_IF) ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "block_if_block", _t);
			}
			}
			}
			}
			}
			}
			}
			}
			}
			}
			}
			}
			}
			}
			}
			}
			}
			}
			}
			}
			}
			}
			}
			}
			}
			}
			}
			}
		}
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "block_if_block", _t);
	}
	*_root = _t;
}

void x_log_if_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==LOGICAL_IF) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(LOGICAL_IF);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "log_if_statement", _t);
		}
		}
		_MATCH(LP);
		_RIGHT;
		x_expression(_parser, &_t);
		_MATCH(RP);
		_RIGHT;
		x_log_substatement(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "log_if_statement", _t);
	}
	*_root = _t;
}

void x_arithm_if_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==ARITHMETIC_IF) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(ARITHMETIC_IF);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "arithm_if_statement", _t);
		}
		}
		_MATCH(LP);
		_RIGHT;
		x_expression(_parser, &_t);
		_MATCH(RP);
		_RIGHT;
		_MATCH(CONSTINT);
		_RIGHT;
		_MATCH(COMMA);
		_RIGHT;
		_MATCH(CONSTINT);
		_RIGHT;
		_MATCH(COMMA);
		_RIGHT;
		_MATCH(CONSTINT);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "arithm_if_statement", _t);
	}
	*_root = _t;
}

void x_log_substatement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==CONTINUE) ) {
		x_continue_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==EQUAL) ) {
		x_assignment_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==DO) ) {
		x_do_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==UNCONDITIONAL_GOTO) ) {
		x_unconditional_goto(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==COMPUTED_GOTO) ) {
		x_computed_goto(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==ASSIGNED_GOTO) ) {
		x_assigned_goto(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==READ) ) {
		x_read_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==WRITE) ) {
		x_write_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==OPEN) ) {
		x_open_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CLOSE) ) {
		x_close_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==INQUIRE) ) {
		x_inquire_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CHANGE) ) {
		x_change_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==FIND) ) {
		x_find_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CALL) ) {
		x_call_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==END) ) {
		x_end_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==STOP) ) {
		x_stop_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==RETURN) ) {
		x_return_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==ARITHMETIC_IF) ) {
		x_arithm_if_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==BACKSPACE) ) {
		x_backspace_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==REWIND) ) {
		x_rewind_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==ENDFILE) ) {
		x_endfile_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==ASSIGN) ) {
		x_assign_statement(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "log_substatement", _t);
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	*_root = _t;
}

void x_continue_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==CONTINUE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(CONTINUE);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "continue_statement", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "continue_statement", _t);
	}
	*_root = _t;
}

void x_stop_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==STOP) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(STOP);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "stop_statement", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "stop_statement", _t);
	}
	*_root = _t;
}

void x_end_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==END) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(END);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "end_statement", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "end_statement", _t);
	}
	*_root = _t;
}

void x_return_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==RETURN) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(RETURN);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "return_statement", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "return_statement", _t);
	}
	*_root = _t;
}

void x_unconditional_goto(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==UNCONDITIONAL_GOTO) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(UNCONDITIONAL_GOTO);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==CONSTINT) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "unconditional_goto", _t);
		}
		}
		_MATCH(CONSTINT);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "unconditional_goto", _t);
	}
	*_root = _t;
}

void x_computed_goto(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==COMPUTED_GOTO) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(COMPUTED_GOTO);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "computed_goto", _t);
		}
		}
		_MATCH(LP);
		_RIGHT;
		_MATCH(CONSTINT);
		_RIGHT;
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				_MATCH(COMMA);
				_RIGHT;
				_MATCH(CONSTINT);
				_RIGHT;
			}
			else {
			if ( _t!=NULL && (_t->token==RP) ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "computed_goto", _t);
			}
			}
		}
		}
		_MATCH(RP);
		_RIGHT;
		if ( _t!=NULL && (_t->token==COMMA) ) {
			_MATCH(COMMA);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==DIV||_t->token==LP||
		_t->token==FUNCTION_NAME||_t->token==CONSTINT||_t->token==MIN||
		_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==INTEGER_ARRAY_ID||
		_t->token==UNARY_PLU||_t->token==UNARY_MIN||_t->token==PLU||
		_t->token==MUL||_t->token==HEX_CONST) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "computed_goto", _t);
		}
		}
		x_integer_expr(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "computed_goto", _t);
	}
	*_root = _t;
}

void x_assigned_goto(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==ASSIGNED_GOTO) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(ASSIGNED_GOTO);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==INTEGER_ID) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "assigned_goto", _t);
		}
		}
		_MATCH(INTEGER_ID);
		_RIGHT;
		if ( _t!=NULL && (_t->token==COMMA||_t->token==LP) ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				_MATCH(COMMA);
				_RIGHT;
			}
			else {
			if ( _t!=NULL && (_t->token==LP) ) {
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "assigned_goto", _t);
			}
			}
			_MATCH(LP);
			_RIGHT;
			_MATCH(CONSTINT);
			_RIGHT;
			{int _done=0;
			while ( !_done ) {
				if ( _t!=NULL && (_t->token==COMMA) ) {
					_MATCH(COMMA);
					_RIGHT;
					_MATCH(CONSTINT);
					_RIGHT;
				}
				else {
				if ( _t!=NULL && (_t->token==RP) ) {
					_done = 1;
				}
				else {
					if ( _parser->guessing ) _GUESS_FAIL;
					no_viable_alt(_parser, "assigned_goto", _t);
				}
				}
			}
			}
			_MATCH(RP);
			_RIGHT;
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "assigned_goto", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "assigned_goto", _t);
	}
	*_root = _t;
}

void x_do_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DO) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(DO);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==CONSTINT) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "do_statement", _t);
		}
		}
		_MATCH(CONSTINT);
		_RIGHT;
		if ( _t!=NULL && (_t->token==COMMA) ) {
			_MATCH(COMMA);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==INTEGER_ID) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "do_statement", _t);
		}
		}
		_MATCH(INTEGER_ID);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		x_integer_expr(_parser, &_t);
		_MATCH(COMMA);
		_RIGHT;
		x_integer_expr(_parser, &_t);
		if ( _t!=NULL && (_t->token==COMMA) ) {
			_MATCH(COMMA);
			_RIGHT;
			x_integer_expr(_parser, &_t);
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "do_statement", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "do_statement", _t);
	}
	*_root = _t;
}

void x_change_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==CHANGE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(CHANGE);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t==NULL || (_t!=NULL) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "change_statement", _t);
		}
		}
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL ) {
				x_any_token(_parser, &_t);
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "change_statement", _t);
			}
			}
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "change_statement", _t);
	}
	*_root = _t;
}

void x_assign_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==ASSIGN) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(ASSIGN);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==CONSTINT) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "assign_statement", _t);
		}
		}
		_MATCH(CONSTINT);
		_RIGHT;
		_MATCH(TO);
		_RIGHT;
		_MATCH(IDENTIFIER);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "assign_statement", _t);
	}
	*_root = _t;
}

void x_format_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==FORMAT) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(FORMAT);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			_MATCH(LABEL);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "format_statement", _t);
		}
		}
		_MATCH(LP);
		_RIGHT;
		x_format_spec(_parser, &_t);
		_MATCH(RP);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "format_statement", _t);
	}
	*_root = _t;
}

void x_format_spec(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==LP||_t->token==CONSTINT||
	_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||_t->token==COLUMN||
	_t->token==SLASH||_t->token==TR||_t->token==TL||
	_t->token==T||_t->token==X||_t->token==SS||
	_t->token==P||_t->token==BZ||_t->token==BN||
	_t->token==J||_t->token==E||_t->token==G||
	_t->token==L||_t->token==Z||_t->token==U||
	_t->token==S||_t->token==I||_t->token==F||
	_t->token==D||_t->token==O||_t->token==A||
	_t->token==SP) ) {
		x_format_item(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==LP||_t->token==CONSTINT||
			_t->token==HOLLERITH_CONST||_t->token==QUOTED_STRING||_t->token==COLUMN||
			_t->token==SLASH||_t->token==TR||_t->token==TL||
			_t->token==T||_t->token==X||_t->token==SS||
			_t->token==P||_t->token==BZ||_t->token==BN||
			_t->token==J||_t->token==E||_t->token==G||
			_t->token==L||_t->token==Z||_t->token==U||
			_t->token==S||_t->token==I||_t->token==F||
			_t->token==D||_t->token==O||_t->token==A||
			_t->token==SP) ) {
				x_format_item(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==RP) ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "format_spec", _t);
			}
			}
		}
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "format_spec", _t);
	}
	*_root = _t;
}

void x_format_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==LP||_t->token==CONSTINT) ) {
		if ( _t!=NULL && (_t->token==CONSTINT) ) {
			_MATCH(CONSTINT);
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "format_item", _t);
		}
		}
		_MATCH(LP);
		_RIGHT;
		x_format_spec(_parser, &_t);
		_MATCH(RP);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==HOLLERITH_CONST) ) {
		x_hollerith_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==QUOTED_STRING) ) {
		x_quote_editinig(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==TR) ) {
		x_tr_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==TL) ) {
		x_tl_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==T) ) {
		x_t_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==X) ) {
		x_x_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==COLUMN) ) {
		x_colon_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==SS) ) {
		x_ss_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==S) ) {
		x_s_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==P) ) {
		x_p_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==BN) ) {
		x_bn_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==BZ) ) {
		x_bz_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==I) ) {
		x_i_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==J) ) {
		x_j_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==F) ) {
		x_f_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==E) ) {
		x_e_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==D) ) {
		x_d_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==G) ) {
		x_g_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==O) ) {
		x_o_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==L) ) {
		x_l_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==A) ) {
		x_a_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==Z) ) {
		x_z_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==SP) ) {
		x_sp_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==SLASH) ) {
		_MATCH(SLASH);
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==U) ) {
		x_u_editing(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "format_item", _t);
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	*_root = _t;
}

void x_hollerith_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==HOLLERITH_CONST) ) {
		_MATCH(HOLLERITH_CONST);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "hollerith_editing", _t);
	}
	*_root = _t;
}

void x_quote_editinig(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==QUOTED_STRING) ) {
		_MATCH(QUOTED_STRING);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "quote_editinig", _t);
	}
	*_root = _t;
}

void x_tr_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==TR) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TR);
		_DOWN;
		_MATCH(CONSTINT);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "tr_editing", _t);
	}
	*_root = _t;
}

void x_tl_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==TL) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TL);
		_DOWN;
		_MATCH(CONSTINT);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "tl_editing", _t);
	}
	*_root = _t;
}

void x_t_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==T) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(T);
		_DOWN;
		_MATCH(CONSTINT);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "t_editing", _t);
	}
	*_root = _t;
}

void x_x_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==X) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(X);
		_DOWN;
		if ( _t!=NULL && (_t->token==REPEAT_COUNT) ) {
			x_repeat_count(_parser, &_t);
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "x_editing", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "x_editing", _t);
	}
	*_root = _t;
}

void x_ss_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==SS) ) {
		_MATCH(SS);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "ss_editing", _t);
	}
	*_root = _t;
}

void x_p_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==P) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(P);
		_DOWN;
		if ( _t!=NULL && (_t->token==SCALE_FACTOR) ) {
			_MATCH(SCALE_FACTOR);
			_RIGHT;
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "p_editing", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "p_editing", _t);
	}
	*_root = _t;
}

void x_bz_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==BZ) ) {
		_MATCH(BZ);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "bz_editing", _t);
	}
	*_root = _t;
}

void x_bn_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==BN) ) {
		_MATCH(BN);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "bn_editing", _t);
	}
	*_root = _t;
}

void x_j_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==J) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(J);
		_DOWN;
		x_field_width(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "j_editing", _t);
	}
	*_root = _t;
}

void x_e_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==E) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(E);
		_DOWN;
		if ( _t!=NULL && (_t->token==REPEAT_COUNT) ) {
			x_repeat_count(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==FIELD_WIDTH) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "e_editing", _t);
		}
		}
		x_field_width(_parser, &_t);
		_MATCH(DEC_POINT);
		_RIGHT;
		x_decimal_places(_parser, &_t);
		if ( _t!=NULL && (_t->token==E) ) {
			_MATCH(E);
			_RIGHT;
			x_exponent_digits(_parser, &_t);
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "e_editing", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "e_editing", _t);
	}
	*_root = _t;
}

void x_g_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==G) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(G);
		_DOWN;
		if ( _t!=NULL && (_t->token==REPEAT_COUNT) ) {
			x_repeat_count(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==FIELD_WIDTH) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "g_editing", _t);
		}
		}
		x_field_width(_parser, &_t);
		_MATCH(DEC_POINT);
		_RIGHT;
		x_decimal_places(_parser, &_t);
		if ( _t!=NULL && (_t->token==G) ) {
			_MATCH(G);
			_RIGHT;
			x_exponent_digits(_parser, &_t);
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "g_editing", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "g_editing", _t);
	}
	*_root = _t;
}

void x_l_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==L) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(L);
		_DOWN;
		if ( _t!=NULL && (_t->token==REPEAT_COUNT) ) {
			x_repeat_count(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==FIELD_WIDTH) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "l_editing", _t);
		}
		}
		x_field_width(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "l_editing", _t);
	}
	*_root = _t;
}

void x_z_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==Z) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(Z);
		_DOWN;
		x_field_width(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "z_editing", _t);
	}
	*_root = _t;
}

void x_u_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==U) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(U);
		_DOWN;
		if ( _t!=NULL && (_t->token==FIELD_WIDTH) ) {
			x_field_width(_parser, &_t);
			if ( _t!=NULL && (_t->token==COMMA) ) {
				_MATCH(COMMA);
				_RIGHT;
				x_decimal_places(_parser, &_t);
			}
			else {
			if ( _t==NULL ) {
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "u_editing", _t);
			}
			}
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "u_editing", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "u_editing", _t);
	}
	*_root = _t;
}

void x_colon_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==COLUMN) ) {
		_MATCH(COLUMN);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "colon_editing", _t);
	}
	*_root = _t;
}

void x_s_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==S) ) {
		_MATCH(S);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "s_editing", _t);
	}
	*_root = _t;
}

void x_i_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==I) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(I);
		_DOWN;
		if ( _t!=NULL && (_t->token==REPEAT_COUNT) ) {
			x_repeat_count(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==FIELD_WIDTH) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "i_editing", _t);
		}
		}
		x_field_width(_parser, &_t);
		if ( _t!=NULL && (_t->token==DEC_POINT) ) {
			_MATCH(DEC_POINT);
			_RIGHT;
			x_min_dig_required(_parser, &_t);
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "i_editing", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "i_editing", _t);
	}
	*_root = _t;
}

void x_f_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==F) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(F);
		_DOWN;
		if ( _t!=NULL && (_t->token==REPEAT_COUNT) ) {
			x_repeat_count(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==FIELD_WIDTH) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "f_editing", _t);
		}
		}
		x_field_width(_parser, &_t);
		_MATCH(DEC_POINT);
		_RIGHT;
		x_decimal_places(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "f_editing", _t);
	}
	*_root = _t;
}

void x_d_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==D) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(D);
		_DOWN;
		if ( _t!=NULL && (_t->token==REPEAT_COUNT) ) {
			x_repeat_count(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==FIELD_WIDTH) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "d_editing", _t);
		}
		}
		x_field_width(_parser, &_t);
		_MATCH(DEC_POINT);
		_RIGHT;
		x_decimal_places(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "d_editing", _t);
	}
	*_root = _t;
}

void x_o_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==O) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(O);
		_DOWN;
		x_field_width(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "o_editing", _t);
	}
	*_root = _t;
}

void x_a_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==A) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(A);
		_DOWN;
		if ( _t!=NULL && (_t->token==REPEAT_COUNT) ) {
			x_repeat_count(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==FIELD_WIDTH) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "a_editing", _t);
		}
		}
		x_field_width(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "a_editing", _t);
	}
	*_root = _t;
}

void x_sp_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==SP) ) {
		_MATCH(SP);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "sp_editing", _t);
	}
	*_root = _t;
}

void x_repeat_count(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==REPEAT_COUNT) ) {
		_MATCH(REPEAT_COUNT);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "repeat_count", _t);
	}
	*_root = _t;
}

void x_field_width(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==FIELD_WIDTH) ) {
		_MATCH(FIELD_WIDTH);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "field_width", _t);
	}
	*_root = _t;
}

void x_decimal_places(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DECIMAL_PLACES) ) {
		_MATCH(DECIMAL_PLACES);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "decimal_places", _t);
	}
	*_root = _t;
}

void x_exponent_digits(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==EXPONENT_DIGITS) ) {
		_MATCH(EXPONENT_DIGITS);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "exponent_digits", _t);
	}
	*_root = _t;
}

void x_min_dig_required(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==MIN_DIG_REQUIRED) ) {
		_MATCH(MIN_DIG_REQUIRED);
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "min_dig_required", _t);
	}
	*_root = _t;
}

void x_any_token(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL ) {
		_WILDCARD;
		_RIGHT;
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "any_token", _t);
	}
	*_root = _t;
}
