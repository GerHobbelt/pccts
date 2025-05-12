/*
 * S O R C E R E R  T r a n s l a t i o n  H e a d e r
 *
 * SORCERER Developed by Terence Parr, Aaron Sawdey, & Gary Funck
 * Parr Research Corporation, Intrepid Technology, University of Minnesota
 * 1992-1994
 * SORCERER Version 13333
 *
 *   ..\..\..\bin\sorcerer -emsvc f77out.sor -proto-file f77out.h -prefix o_
 *
 */
#define SORCERER_VERSION	13333
#define SORCERER_NONTRANSFORM
#include "pcctscfg.h"
#include <stdio.h>
#include <setjmp.h>
/* rename error routines; used in macros, must use /lib/cpp */
#define mismatched_token o_mismatched_token
#define mismatched_range o_mismatched_range
#define missing_wildcard o_missing_wildcard
#define no_viable_alt o_no_viable_alt
#define sorcerer_panic o_sorcerer_panic

#define CASTBase_h	/*To eliminate castbase.h*/
#include <assert.h>
#include "stdpccts.h"
/* Only requirements are that the user define what an AST is; it must have
* right, down pointers and a token field.  After that, the user can put it
* what he/she wants
*/

typedef AST SORAST;

#ifdef __STDC__
#include "stdlib.h"
#else
#include "malloc.h"
#endif

extern void f77NewLine(int indent);
extern void f77PutText(const char *text);
extern void f77PrintLine(void);
extern void f77PutLabel(const char *text);

extern int Indentation;
extern int DontStartNewLine;




extern void f77PutText(const char *text); /* f77print.cpp */

#include "sorcerer.h"
#include "f77out.h"

void
#ifdef __USE_PROTOS
o__refvar_inits(STreeParser *p)
#else
o__refvar_inits(p)
STreeParser *p;
#endif
{
}



/* define error routines here or include sorcerer.c */
#include "errsupport.c"

int Indentation = 1; /*Indentation is 1 in order to start in column 7*/

void F77TreePrinter(AST *root)
{
	SORAST *ast_root = root; /*Copy it here. For some reason it gets overwriten by program.*/
	STreeParser myparser;
	STreeParserInit(o_, &myparser); /* calls the 'f77out.sor' program() rule! --> use f77out.sor _refvar_inits()! */

	/* gen code */
	o_program(&myparser, &root);
}


void o_program(STreeParser *_parser, SORAST **_root)
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
			o_comment_block(_parser, &_t);
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
			o_file_block(_parser, &_t);
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
			o_block_globals_block(_parser, &_t);
			if ( _t!=NULL && (_t->token==COMMENT_LINE||_t->token==BLANK_LINE||
			_t->token==CONTROL_IMAGE) ) {
				o_comment_block(_parser, &_t);
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
		o_main_program(_parser, &_t);
		if ( _t!=NULL && (_t->token==COMMENT_LINE||_t->token==BLANK_LINE||
		_t->token==CONTROL_IMAGE) ) {
			o_comment_block(_parser, &_t);
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
				o_subroutine_block(_parser, &_t);
				if ( _t!=NULL && (_t->token==COMMENT_LINE||_t->token==BLANK_LINE||
				_t->token==CONTROL_IMAGE) ) {
					o_comment_block(_parser, &_t);
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

void o_main_program(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
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
			o_decl_block(_parser, &_t);
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
			o_exec_block(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==END) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "main_program", _t);
		}
		}
		o_end_statement(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "main_program", _t);
	}
	*_root = _t;
}

void o_subroutine_block(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==SUBROUTINE||_t->token==FUNCTION) ) {
		STreeParser Parser;  
		if ( _t!=NULL && (_t->token==SUBROUTINE) ) {
			o_subroutine_statement(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==FUNCTION) ) {
			o_function_statement(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "subroutine_block", _t);
		}
		}
		if ( _t!=NULL && (_t->token==COMMENT_LINE||_t->token==BLANK_LINE||
		_t->token==CONTROL_IMAGE) ) {
			o_comment_block(_parser, &_t);
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
			o_decl_block(_parser, &_t);
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
			o_exec_block(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==END) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "subroutine_block", _t);
		}
		}
		o_end_statement(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "subroutine_block", _t);
	}
	*_root = _t;
}

void o_decl_block(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==COMMON||_t->token==SAVE||
	_t->token==PARAMETER||_t->token==EXTERNAL||_t->token==INTRINSIC||
	_t->token==IMPLICIT||_t->token==INTEGER||_t->token==REAL||
	_t->token==DOUBLE_PRECISION||_t->token==LOGICAL||_t->token==CHARACTER||
	_t->token==DATA||_t->token==DIMENSION||_t->token==EQUIVALENCE) ) {
		o_decl_statement(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMON||_t->token==SAVE||
			_t->token==PARAMETER||_t->token==EXTERNAL||_t->token==INTRINSIC||
			_t->token==IMPLICIT||_t->token==INTEGER||_t->token==REAL||
			_t->token==DOUBLE_PRECISION||_t->token==LOGICAL||_t->token==CHARACTER||
			_t->token==DATA||_t->token==DIMENSION||_t->token==EQUIVALENCE) ) {
				o_decl_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==COMMENT_LINE) ) {
				o_comment_line(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==BLANK_LINE) ) {
				o_blank_line(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==CONTROL_IMAGE) ) {
				o_control_image(_parser, &_t);
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

void o_decl_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==COMMON) ) {
		o_common_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==DATA) ) {
		o_data_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CHARACTER) ) {
		o_character_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==INTEGER) ) {
		o_integer_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==REAL) ) {
		o_real_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==LOGICAL) ) {
		o_logical_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==DOUBLE_PRECISION) ) {
		o_precision_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==DIMENSION) ) {
		o_dimension_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==EQUIVALENCE) ) {
		o_equivalence_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==EXTERNAL) ) {
		o_external_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==INTRINSIC) ) {
		o_intrinsic_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==SAVE) ) {
		o_save_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==PARAMETER) ) {
		o_parameter_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==IMPLICIT) ) {
		o_implicit_statement(_parser, &_t);
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

void o_comment_block(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==COMMENT_LINE||_t->token==BLANK_LINE||
	_t->token==CONTROL_IMAGE) ) {
		{int _done=0;
		do {
			if ( _t!=NULL && (_t->token==COMMENT_LINE) ) {
				o_comment_line(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==BLANK_LINE) ) {
				o_blank_line(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==CONTROL_IMAGE) ) {
				o_control_image(_parser, &_t);
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

void o_exec_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==CONTINUE) ) {
		o_continue_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==EQUAL) ) {
		o_assignment_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==DO) ) {
		o_do_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==UNCONDITIONAL_GOTO) ) {
		o_unconditional_goto(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==COMPUTED_GOTO) ) {
		o_computed_goto(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==ASSIGNED_GOTO) ) {
		o_assigned_goto(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==READ) ) {
		o_read_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==WRITE) ) {
		o_write_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==OPEN) ) {
		o_open_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CLOSE) ) {
		o_close_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==INQUIRE) ) {
		o_inquire_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CHANGE) ) {
		o_change_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==FIND) ) {
		o_find_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CALL) ) {
		o_call_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==BLOCK_IF) ) {
		o_block_if_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==ARITHMETIC_IF) ) {
		o_arithm_if_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==LOGICAL_IF) ) {
		o_log_if_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==STOP) ) {
		o_stop_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==RETURN) ) {
		o_return_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==FORMAT) ) {
		o_format_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==BACKSPACE) ) {
		o_backspace_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==REWIND) ) {
		o_rewind_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==ENDFILE) ) {
		o_endfile_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==ASSIGN) ) {
		o_assign_statement(_parser, &_t);
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

void o_exec_block(STreeParser *_parser, SORAST **_root)
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
		o_exec_statement(_parser, &_t);
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
				o_exec_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==COMMENT_LINE) ) {
				o_comment_line(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==ENTRY) ) {
				o_entry_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==BLANK_LINE) ) {
				o_blank_line(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==CONTROL_IMAGE) ) {
				o_control_image(_parser, &_t);
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

void o_block_globals_block(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==BLOCK_GLOBALS) ) {
		o_block_globals_statement(_parser, &_t);
		if ( _t!=NULL && (_t->token==FILEKEYWORD) ) {
			o_file_block(_parser, &_t);
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
			o_export_statement(_parser, &_t);
			if ( _t!=NULL && (_t->token==COMMENT_LINE||_t->token==BLANK_LINE||
			_t->token==CONTROL_IMAGE) ) {
				o_comment_block(_parser, &_t);
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
		o_end_statement(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "block_globals_block", _t);
	}
	*_root = _t;
}

void o_file_block(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==FILEKEYWORD) ) {
		o_file_statement(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==FILEKEYWORD) ) {
				o_file_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==COMMENT_LINE) ) {
				o_comment_line(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==BLANK_LINE) ) {
				o_blank_line(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==CONTROL_IMAGE) ) {
				o_control_image(_parser, &_t);
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

void o_comment_line(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *c=NULL;
	if ( _t!=NULL && (_t->token==COMMENT_LINE) ) {
		f77NewLine(0);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(COMMENT_LINE);
		c=(SORAST *)_t;
		_DOWN;
		
		f77PutText("C");
		f77PutText(c->f77NodeText);
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "comment_line", _t);
	}
	*_root = _t;
}

void o_blank_line(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *c=NULL;
	if ( _t!=NULL && (_t->token==BLANK_LINE) ) {
		f77NewLine(0);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(BLANK_LINE);
		c=(SORAST *)_t;
		_DOWN;
		
		f77PutText(c->f77NodeText);
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "blank_line", _t);
	}
	*_root = _t;
}

void o_block_globals_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==BLOCK_GLOBALS) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(BLOCK_GLOBALS);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "block_globals_statement", _t);
		}
		}
		f77PutText("BLOCK GLOBALS");  
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "block_globals_statement", _t);
	}
	*_root = _t;
}

void o_common_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==COMMON) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(COMMON);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
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
		f77PutText("COMMON ");  
		o_block_item(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				o_comma(_parser, &_t);
				o_block_item(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "common_statement", _t);
	}
	*_root = _t;
}

void o_block_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==INTEGER_ID||_t->token==REAL_ID||
	_t->token==CHARACTER_ID||_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||
	_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||
	_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==CHARACTER_SUBSTRING) ) {
		o_lvalue(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==DIV) ) {
		_MATCH(DIV);
		_RIGHT;
		f77PutText("/");  
		if ( _t!=NULL && (_t->token==IDENTIFIER) ) {
			o_identifier(_parser, &_t);
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
		f77PutText("/");  
		o_lvalue(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CONCAT) ) {
		_MATCH(CONCAT);
		_RIGHT;
		f77PutText("//");  
		o_lvalue(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "block_item", _t);
	}
	}
	}
	*_root = _t;
}

void o_save_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==SAVE) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(SAVE);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "save_statement", _t);
		}
		}
		f77PutText("SAVE");  
		o_lp(_parser, &_t);
		o_save_item(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				o_comma(_parser, &_t);
				o_save_item(_parser, &_t);
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
		o_rp(_parser, &_t);
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

void o_save_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *i=NULL;
	if ( _t!=NULL && (_t->token==DIV||_t->token==IDENTIFIER) ) {
		char buffer[100];  
		if ( _t!=NULL && (_t->token==DIV) ) {
			_MATCH(DIV);
			_RIGHT;
			_MATCH(IDENTIFIER);
			i=(SORAST *)_t;
			_RIGHT;
			_MATCH(DIV);
			_RIGHT;
			
			sprintf(buffer, "/%s/", i->f77NodeText);
			f77PutText(buffer);
		}
		else {
		if ( _t!=NULL && (_t->token==IDENTIFIER) ) {
			_MATCH(IDENTIFIER);
			i=(SORAST *)_t;
			_RIGHT;
			
			f77PutText(buffer);
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

void o_parameter_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==PARAMETER) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(PARAMETER);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "parameter_statement", _t);
		}
		}
		f77PutText("PARAMETER");  
		o_lp(_parser, &_t);
		o_para_item(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				o_comma(_parser, &_t);
				o_para_item(_parser, &_t);
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
		o_rp(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "parameter_statement", _t);
	}
	*_root = _t;
}

void o_para_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *c=NULL;
	if ( _t!=NULL && (_t->token==CONSTANT_NAME) ) {
		_MATCH(CONSTANT_NAME);
		c=(SORAST *)_t;
		_RIGHT;
		f77PutText(c->f77NodeText);  
		_MATCH(EQUAL);
		_RIGHT;
		f77PutText("=");  
		o_expression(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "para_item", _t);
	}
	*_root = _t;
}

void o_external_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==EXTERNAL) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(EXTERNAL);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==FUNCTION_NAME) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "external_statement", _t);
		}
		}
		f77PutText("EXTERNAL ");  
		o_function_name(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				o_comma(_parser, &_t);
				o_function_name(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "external_statement", _t);
	}
	*_root = _t;
}

void o_function_name(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *f=NULL;
	if ( _t!=NULL && (_t->token==FUNCTION_NAME) ) {
		_MATCH(FUNCTION_NAME);
		f=(SORAST *)_t;
		_RIGHT;
		f77PutText(f->f77NodeText);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "function_name", _t);
	}
	*_root = _t;
}

void o_intrinsic_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==INTRINSIC) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(INTRINSIC);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==FUNCTION_NAME) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "intrinsic_statement", _t);
		}
		}
		f77PutText("INTRINSIC ");  
		o_function_name(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				o_comma(_parser, &_t);
				o_function_name(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "intrinsic_statement", _t);
	}
	*_root = _t;
}

void o_implicit_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==IMPLICIT) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(IMPLICIT);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
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
		f77PutText("IMPLICIT ");  
		o_implicit_item(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				o_comma(_parser, &_t);
				o_implicit_item(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "implicit_statement", _t);
	}
	*_root = _t;
}

void o_implicit_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==INTEGER||_t->token==REAL||
	_t->token==DOUBLE_PRECISION||_t->token==LOGICAL||_t->token==CHARACTER||
	_t->token==COMPLEX||_t->token==DOUBLE_COMPLEX) ) {
		o_implicit_type(_parser, &_t);
		o_lp(_parser, &_t);
		o_letter_spec(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				o_comma(_parser, &_t);
				o_letter_spec(_parser, &_t);
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
		o_rp(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "implicit_item", _t);
	}
	*_root = _t;
}

void o_implicit_type(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *c=NULL;
	if ( _t!=NULL && (_t->token==INTEGER||_t->token==REAL||
	_t->token==DOUBLE_PRECISION||_t->token==LOGICAL||_t->token==CHARACTER||
	_t->token==COMPLEX||_t->token==DOUBLE_COMPLEX) ) {
		char buffer[100];  
		if ( _t!=NULL && (_t->token==INTEGER) ) {
			_MATCH(INTEGER);
			_RIGHT;
			f77PutText("INTEGER");  
		}
		else {
		if ( _t!=NULL && (_t->token==REAL) ) {
			_MATCH(REAL);
			_RIGHT;
			f77PutText("REAL");  
		}
		else {
		if ( _t!=NULL && (_t->token==DOUBLE_PRECISION) ) {
			_MATCH(DOUBLE_PRECISION);
			_RIGHT;
			f77PutText("DOUBLE PRECISION");  
		}
		else {
		if ( _t!=NULL && (_t->token==LOGICAL) ) {
			_MATCH(LOGICAL);
			_RIGHT;
			f77PutText("LOGICAL");  
		}
		else {
		if ( _t!=NULL && (_t->token==CHARACTER) ) {
			_MATCH(CHARACTER);
			_RIGHT;
			f77PutText("CHARACTER");  
		}
		else {
		if ( _t!=NULL && (_t->token==COMPLEX) ) {
			_MATCH(COMPLEX);
			_RIGHT;
			f77PutText("COMPLEX");  
		}
		else {
		if ( _t!=NULL && (_t->token==DOUBLE_COMPLEX) ) {
			_MATCH(DOUBLE_COMPLEX);
			_RIGHT;
			f77PutText("DOUBLE COMPLEX");  
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
			c=(SORAST *)_t;
			_RIGHT;
			
			sprintf(buffer,"*%s", c->f77NodeText);
			f77PutText(buffer);
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

void o_letter_spec(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *i=NULL;
	if ( _t!=NULL && (_t->token==IDENTIFIER) ) {
		char buffer[100];  
		_MATCH(IDENTIFIER);
		i=(SORAST *)_t;
		_RIGHT;
		sprintf(buffer,"%s",i->f77NodeText);  
		if ( _t!=NULL && (_t->token==MIN) ) {
			_MATCH(MIN);
			_RIGHT;
			_MATCH(IDENTIFIER);
			i=(SORAST *)_t;
			_RIGHT;
			
			strcat(buffer,"-");
			strcat(buffer,i->f77NodeText);
		}
		else {
		if ( _t!=NULL && (_t->token==COMMA||_t->token==RP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "letter_spec", _t);
		}
		}
		f77PutText(buffer);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "letter_spec", _t);
	}
	*_root = _t;
}

void o_data_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DATA) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(DATA);
		_DOWN;
		f77PutText("DATA ");  
		{int _done=0;
		do {
			if ( _t!=NULL ) {
				o_any_token(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "data_statement", _t);
	}
	*_root = _t;
}

void o_inquire_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==INQUIRE) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(INQUIRE);
		_DOWN;
		f77PutText("INQUIRE ");  
		{int _done=0;
		do {
			if ( _t!=NULL ) {
				o_any_token(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "inquire_statement", _t);
	}
	*_root = _t;
}

void o_assignment_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *e=NULL;
	SORAST *f=NULL;
	if ( _t!=NULL && (_t->token==EQUAL) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(EQUAL);
		e=(SORAST *)_t;
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
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
			o_lvalue(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==FUNCTION_NAME) ) {
			_MATCH(FUNCTION_NAME);
			f=(SORAST *)_t;
			_RIGHT;
			f77PutText(f->f77NodeText);  
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "assignment_statement", _t);
		}
		}
		f77PutText(e->f77NodeText);  
		o_rvalue(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "assignment_statement", _t);
	}
	*_root = _t;
}

void o_lvalue(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==INTEGER_ID||_t->token==INTEGER_ARRAY_ID) ) {
		o_int_lvalue(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==REAL_ID||_t->token==REAL_ARRAY_ID) ) {
		o_real_lvalue(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CHARACTER_ID||_t->token==CHARACTER_ARRAY_ID||
	_t->token==CHARACTER_SUBSTRING) ) {
		o_char_lvalue(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==LOGICAL_ID||_t->token==LOGICAL_ARRAY_ID) ) {
		o_log_lvalue(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==DOUBLE_PRECISION_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID) ) {
		o_double_lvalue(_parser, &_t);
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

void o_rvalue(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==FUNCTION_NAME||_t->token==CONSTINT||_t->token==MIN||
	_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==CHARACTER_ID||
	_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||
	_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||
	_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||_t->token==NOT||
	_t->token==UNARY_MIN||_t->token==PLU||_t->token==MUL||
	_t->token==POW||_t->token==AND||_t->token==OR||
	_t->token==NEQV||_t->token==EQV||_t->token==LT||
	_t->token==LE||_t->token==EQ||_t->token==NE||
	_t->token==GT||_t->token==GE||_t->token==IS||
	_t->token==HEX_CONST||_t->token==BASIC_REAL||_t->token==REAL_EXPO||
	_t->token==T_TRUE||_t->token==T_FALSE||_t->token==HOLLERITH_CONST||
	_t->token==CHARACTER_SUBSTRING||_t->token==LP||_t->token==QUOTED_STRING) ) {
		o_expression(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "rvalue", _t);
	}
	*_root = _t;
}

void o_array_reference(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==INTEGER_ARRAY_ID) ) {
		o_int_array_ref(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==REAL_ARRAY_ID) ) {
		o_real_array_ref(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CHARACTER_ARRAY_ID) ) {
		o_char_array_ref(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==DOUBLE_PRECISION_ARRAY_ID) ) {
		o_double_array_ref(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==LOGICAL_ARRAY_ID) ) {
		o_log_array_ref(_parser, &_t);
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

void o_int_lvalue(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *i=NULL;
	if ( _t!=NULL && (_t->token==INTEGER_ARRAY_ID) ) {
		o_int_array_ref(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==INTEGER_ID) ) {
		_MATCH(INTEGER_ID);
		i=(SORAST *)_t;
		_RIGHT;
		f77PutText(i->f77NodeText);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "int_lvalue", _t);
	}
	}
	*_root = _t;
}

void o_real_lvalue(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *i=NULL;
	if ( _t!=NULL && (_t->token==REAL_ARRAY_ID) ) {
		o_real_array_ref(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==REAL_ID) ) {
		_MATCH(REAL_ID);
		i=(SORAST *)_t;
		_RIGHT;
		f77PutText(i->f77NodeText);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "real_lvalue", _t);
	}
	}
	*_root = _t;
}

void o_char_lvalue(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *i=NULL;
	if ( _t!=NULL && (_t->token==CHARACTER_ARRAY_ID) ) {
		o_char_array_ref(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CHARACTER_ID) ) {
		_MATCH(CHARACTER_ID);
		i=(SORAST *)_t;
		_RIGHT;
		f77PutText(i->f77NodeText);  
	}
	else {
	if ( _t!=NULL && (_t->token==CHARACTER_SUBSTRING) ) {
		o_substring(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "char_lvalue", _t);
	}
	}
	}
	*_root = _t;
}

void o_double_lvalue(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *i=NULL;
	if ( _t!=NULL && (_t->token==DOUBLE_PRECISION_ARRAY_ID) ) {
		o_double_array_ref(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==DOUBLE_PRECISION_ID) ) {
		_MATCH(DOUBLE_PRECISION_ID);
		i=(SORAST *)_t;
		_RIGHT;
		f77PutText(i->f77NodeText);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "double_lvalue", _t);
	}
	}
	*_root = _t;
}

void o_log_lvalue(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *i=NULL;
	if ( _t!=NULL && (_t->token==LOGICAL_ARRAY_ID) ) {
		o_log_array_ref(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==LOGICAL_ID) ) {
		_MATCH(LOGICAL_ID);
		i=(SORAST *)_t;
		_RIGHT;
		f77PutText(i->f77NodeText);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "log_lvalue", _t);
	}
	}
	*_root = _t;
}

void o_int_array_ref(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *a=NULL;
	if ( _t!=NULL && (_t->token==INTEGER_ARRAY_ID) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(INTEGER_ARRAY_ID);
		a=(SORAST *)_t;
		_DOWN;
		f77PutText(a->f77NodeText);  
		if ( _t!=NULL && (_t->token==LP) ) {
			o_lp(_parser, &_t);
			o_expression(_parser, &_t);
			{int _done=0;
			while ( !_done ) {
				if ( _t!=NULL && (_t->token==COMMA) ) {
					o_comma(_parser, &_t);
					o_expression(_parser, &_t);
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
			o_rp(_parser, &_t);
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

void o_real_array_ref(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *a=NULL;
	if ( _t!=NULL && (_t->token==REAL_ARRAY_ID) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(REAL_ARRAY_ID);
		a=(SORAST *)_t;
		_DOWN;
		f77PutText(a->f77NodeText);  
		if ( _t!=NULL && (_t->token==LP) ) {
			o_lp(_parser, &_t);
			o_expression(_parser, &_t);
			{int _done=0;
			while ( !_done ) {
				if ( _t!=NULL && (_t->token==COMMA) ) {
					o_comma(_parser, &_t);
					o_expression(_parser, &_t);
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
			o_rp(_parser, &_t);
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

void o_char_array_ref(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *a=NULL;
	if ( _t!=NULL && (_t->token==CHARACTER_ARRAY_ID) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(CHARACTER_ARRAY_ID);
		a=(SORAST *)_t;
		_DOWN;
		f77PutText(a->f77NodeText);  
		if ( _t!=NULL && (_t->token==LP) ) {
			o_lp(_parser, &_t);
			o_expression(_parser, &_t);
			{int _done=0;
			while ( !_done ) {
				if ( _t!=NULL && (_t->token==COMMA) ) {
					o_comma(_parser, &_t);
					o_expression(_parser, &_t);
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
			o_rp(_parser, &_t);
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

void o_log_array_ref(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *a=NULL;
	if ( _t!=NULL && (_t->token==LOGICAL_ARRAY_ID) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(LOGICAL_ARRAY_ID);
		a=(SORAST *)_t;
		_DOWN;
		f77PutText(a->f77NodeText);  
		if ( _t!=NULL && (_t->token==LP) ) {
			o_lp(_parser, &_t);
			o_expression(_parser, &_t);
			{int _done=0;
			while ( !_done ) {
				if ( _t!=NULL && (_t->token==COMMA) ) {
					o_comma(_parser, &_t);
					o_expression(_parser, &_t);
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
			o_rp(_parser, &_t);
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

void o_double_array_ref(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *a=NULL;
	if ( _t!=NULL && (_t->token==DOUBLE_PRECISION_ARRAY_ID) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(DOUBLE_PRECISION_ARRAY_ID);
		a=(SORAST *)_t;
		_DOWN;
		f77PutText(a->f77NodeText);  
		if ( _t!=NULL && (_t->token==LP) ) {
			o_lp(_parser, &_t);
			o_expression(_parser, &_t);
			{int _done=0;
			while ( !_done ) {
				if ( _t!=NULL && (_t->token==COMMA) ) {
					o_comma(_parser, &_t);
					o_expression(_parser, &_t);
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
			o_rp(_parser, &_t);
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

void o_array_name(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *a=NULL;
	if ( _t!=NULL && (_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||
	_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID) ) {
		if ( _t!=NULL && (_t->token==INTEGER_ARRAY_ID) ) {
			_MATCH(INTEGER_ARRAY_ID);
			a=(SORAST *)_t;
			_RIGHT;
			f77PutText(a->f77NodeText);  
		}
		else {
		if ( _t!=NULL && (_t->token==REAL_ARRAY_ID) ) {
			_MATCH(REAL_ARRAY_ID);
			a=(SORAST *)_t;
			_RIGHT;
			f77PutText(a->f77NodeText);  
		}
		else {
		if ( _t!=NULL && (_t->token==CHARACTER_ARRAY_ID) ) {
			_MATCH(CHARACTER_ARRAY_ID);
			a=(SORAST *)_t;
			_RIGHT;
			f77PutText(a->f77NodeText);  
		}
		else {
		if ( _t!=NULL && (_t->token==LOGICAL_ARRAY_ID) ) {
			_MATCH(LOGICAL_ARRAY_ID);
			a=(SORAST *)_t;
			_RIGHT;
			f77PutText(a->f77NodeText);  
		}
		else {
		if ( _t!=NULL && (_t->token==DOUBLE_PRECISION_ARRAY_ID) ) {
			_MATCH(DOUBLE_PRECISION_ARRAY_ID);
			a=(SORAST *)_t;
			_RIGHT;
			f77PutText(a->f77NodeText);  
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

void o_function_reference(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *a=NULL;
	if ( _t!=NULL && (_t->token==FUNCTION_NAME) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(FUNCTION_NAME);
		a=(SORAST *)_t;
		_DOWN;
		f77PutText(a->f77NodeText);  
		o_lp(_parser, &_t);
		o_expression(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				o_comma(_parser, &_t);
				o_expression(_parser, &_t);
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
		o_rp(_parser, &_t);
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

void o_expression(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==MIN||_t->token==UNARY_PLU||_t->token==NOT||
	_t->token==UNARY_MIN||_t->token==PLU||_t->token==MUL||
	_t->token==POW||_t->token==AND||_t->token==OR||
	_t->token==NEQV||_t->token==EQV||_t->token==LT||
	_t->token==LE||_t->token==EQ||_t->token==NE||
	_t->token==GT||_t->token==GE||_t->token==IS) ) {
		o_real_expression(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==FUNCTION_NAME||_t->token==CONSTINT||
	_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==CHARACTER_ID||
	_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||
	_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||
	_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==HEX_CONST||_t->token==BASIC_REAL||
	_t->token==REAL_EXPO||_t->token==T_TRUE||_t->token==T_FALSE||
	_t->token==HOLLERITH_CONST||_t->token==CHARACTER_SUBSTRING||_t->token==LP||
	_t->token==QUOTED_STRING) ) {
		o_exp_operand(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "expression", _t);
	}
	}
	*_root = _t;
}

void o_real_expression(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==UNARY_PLU) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(UNARY_PLU);
		_DOWN;
		f77PutText("+");  
		o_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==NOT) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(NOT);
		_DOWN;
		f77PutText(".NOT.");  
		o_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==UNARY_MIN) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(UNARY_MIN);
		_DOWN;
		f77PutText("-");  
		o_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==PLU) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(PLU);
		_DOWN;
		o_expression(_parser, &_t);
		f77PutText("+");  
		o_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==MIN) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(MIN);
		_DOWN;
		o_expression(_parser, &_t);
		f77PutText("-");  
		o_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==MUL) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(MUL);
		_DOWN;
		o_expression(_parser, &_t);
		f77PutText("*");  
		o_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==DIV) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(DIV);
		_DOWN;
		o_expression(_parser, &_t);
		f77PutText("/");  
		o_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==POW) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(POW);
		_DOWN;
		o_expression(_parser, &_t);
		f77PutText("**");  
		o_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==AND) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(AND);
		_DOWN;
		o_expression(_parser, &_t);
		f77PutText(".AND.");  
		o_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==OR) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(OR);
		_DOWN;
		o_expression(_parser, &_t);
		f77PutText(".OR.");  
		o_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==NEQV) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(NEQV);
		_DOWN;
		o_expression(_parser, &_t);
		f77PutText(".NEQV.");  
		o_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==EQV) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(EQV);
		_DOWN;
		o_expression(_parser, &_t);
		f77PutText(".EQV.");  
		o_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==LT) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(LT);
		_DOWN;
		o_expression(_parser, &_t);
		f77PutText(".LT.");  
		o_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==LE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(LE);
		_DOWN;
		o_expression(_parser, &_t);
		f77PutText(".LE.");  
		o_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==EQ) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(EQ);
		_DOWN;
		o_expression(_parser, &_t);
		f77PutText(".EQ.");  
		o_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==NE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(NE);
		_DOWN;
		o_expression(_parser, &_t);
		f77PutText(".NE.");  
		o_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==GT) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(GT);
		_DOWN;
		o_expression(_parser, &_t);
		f77PutText(".GT.");  
		o_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==GE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(GE);
		_DOWN;
		o_expression(_parser, &_t);
		f77PutText(".GE.");  
		o_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==IS) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(IS);
		_DOWN;
		o_expression(_parser, &_t);
		f77PutText(".IS.");  
		o_expression(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==CONCAT) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(CONCAT);
		_DOWN;
		o_expression(_parser, &_t);
		f77PutText("//");  
		o_expression(_parser, &_t);
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

void o_exp_operand(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *i=NULL;
	SORAST *d=NULL;
	SORAST *h=NULL;
	SORAST *b=NULL;
	SORAST *r=NULL;
	SORAST *c=NULL;
	if ( _t!=NULL && (_t->token==INTEGER_ARRAY_ID||_t->token==REAL_ARRAY_ID||
	_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||_t->token==DOUBLE_PRECISION_ARRAY_ID) ) {
		o_array_reference(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==FUNCTION_NAME) ) {
		o_function_reference(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==INTEGER_ID) ) {
		_MATCH(INTEGER_ID);
		i=(SORAST *)_t;
		_RIGHT;
		f77PutText(i->f77NodeText);  
	}
	else {
	if ( _t!=NULL && (_t->token==REAL_ID) ) {
		_MATCH(REAL_ID);
		i=(SORAST *)_t;
		_RIGHT;
		f77PutText(i->f77NodeText);  
	}
	else {
	if ( _t!=NULL && (_t->token==DOUBLE_PRECISION_ID) ) {
		_MATCH(DOUBLE_PRECISION_ID);
		d=(SORAST *)_t;
		_RIGHT;
		f77PutText(d->f77NodeText);  
	}
	else {
	if ( _t!=NULL && (_t->token==CONSTINT) ) {
		_MATCH(CONSTINT);
		i=(SORAST *)_t;
		_RIGHT;
		f77PutText(i->f77NodeText);  
	}
	else {
	if ( _t!=NULL && (_t->token==HEX_CONST) ) {
		_MATCH(HEX_CONST);
		h=(SORAST *)_t;
		_RIGHT;
		f77PutText(h->f77NodeText);  
	}
	else {
	if ( _t!=NULL && (_t->token==BASIC_REAL) ) {
		_MATCH(BASIC_REAL);
		b=(SORAST *)_t;
		_RIGHT;
		f77PutText(b->f77NodeText);  
	}
	else {
	if ( _t!=NULL && (_t->token==REAL_EXPO) ) {
		_MATCH(REAL_EXPO);
		r=(SORAST *)_t;
		_RIGHT;
		f77PutText(r->f77NodeText);  
	}
	else {
	if ( _t!=NULL && (_t->token==LOGICAL_ID) ) {
		_MATCH(LOGICAL_ID);
		i=(SORAST *)_t;
		_RIGHT;
		f77PutText(i->f77NodeText);  
	}
	else {
	if ( _t!=NULL && (_t->token==T_TRUE) ) {
		_MATCH(T_TRUE);
		i=(SORAST *)_t;
		_RIGHT;
		f77PutText(".TRUE.");  
	}
	else {
	if ( _t!=NULL && (_t->token==T_FALSE) ) {
		_MATCH(T_FALSE);
		i=(SORAST *)_t;
		_RIGHT;
		f77PutText(".FALSE.");  
	}
	else {
	if ( _t!=NULL && (_t->token==CHARACTER_SUBSTRING) ) {
		o_substring(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CHARACTER_ID) ) {
		_MATCH(CHARACTER_ID);
		c=(SORAST *)_t;
		_RIGHT;
		f77PutText(c->f77NodeText);  
	}
	else {
	if ( _t!=NULL && (_t->token==HOLLERITH_CONST) ) {
		if ( _t!=NULL && (_t->token==HOLLERITH_CONST) ) {
			char buffer[100];  
			_MATCH(HOLLERITH_CONST);
			h=(SORAST *)_t;
			_RIGHT;
			
			sprintf(buffer, "%dH%s", strlen(h->f77NodeText), h->f77NodeText);
			f77PutText(h->f77NodeText);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "exp_operand", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==QUOTED_STRING) ) {
		if ( _t!=NULL && (_t->token==QUOTED_STRING) ) {
			char buffer[100];  
			o_quoted_string(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "exp_operand", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==LP) ) {
		o_lp(_parser, &_t);
		o_expression(_parser, &_t);
		o_rp(_parser, &_t);
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

void o_integer_expr(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *i=NULL;
	SORAST *h=NULL;
	SORAST *r=NULL;
	if ( _t!=NULL && (_t->token==UNARY_PLU) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(UNARY_PLU);
		_DOWN;
		f77PutText("+");  
		o_integer_expr(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==UNARY_MIN) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(UNARY_MIN);
		_DOWN;
		f77PutText("-");  
		o_integer_expr(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==PLU) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(PLU);
		_DOWN;
		o_integer_expr(_parser, &_t);
		f77PutText("+");  
		if ( _t!=NULL && (_t->token==DIV||_t->token==FUNCTION_NAME||
		_t->token==CONSTINT||_t->token==MIN||_t->token==INTEGER_ID||
		_t->token==REAL_ID||_t->token==INTEGER_ARRAY_ID||_t->token==UNARY_PLU||
		_t->token==UNARY_MIN||_t->token==PLU||_t->token==MUL||
		_t->token==HEX_CONST||_t->token==LP) ) {
			o_integer_expr(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==QUOTED_STRING) ) {
			o_quoted_string(_parser, &_t);
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
		o_integer_expr(_parser, &_t);
		f77PutText("-");  
		if ( _t!=NULL && (_t->token==DIV||_t->token==FUNCTION_NAME||
		_t->token==CONSTINT||_t->token==MIN||_t->token==INTEGER_ID||
		_t->token==REAL_ID||_t->token==INTEGER_ARRAY_ID||_t->token==UNARY_PLU||
		_t->token==UNARY_MIN||_t->token==PLU||_t->token==MUL||
		_t->token==HEX_CONST||_t->token==LP) ) {
			o_integer_expr(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==QUOTED_STRING) ) {
			o_quoted_string(_parser, &_t);
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
		o_integer_expr(_parser, &_t);
		f77PutText("*");  
		o_integer_expr(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==DIV) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(DIV);
		_DOWN;
		o_integer_expr(_parser, &_t);
		f77PutText("/");  
		o_integer_expr(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->token==LP) ) {
		o_lp(_parser, &_t);
		o_integer_expr(_parser, &_t);
		o_rp(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==INTEGER_ARRAY_ID) ) {
		o_int_array_ref(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==FUNCTION_NAME) ) {
		o_function_reference(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==INTEGER_ID) ) {
		_MATCH(INTEGER_ID);
		i=(SORAST *)_t;
		_RIGHT;
		f77PutText(i->f77NodeText);  
	}
	else {
	if ( _t!=NULL && (_t->token==CONSTINT) ) {
		_MATCH(CONSTINT);
		i=(SORAST *)_t;
		_RIGHT;
		f77PutText(i->f77NodeText);  
	}
	else {
	if ( _t!=NULL && (_t->token==HEX_CONST) ) {
		_MATCH(HEX_CONST);
		h=(SORAST *)_t;
		_RIGHT;
		f77PutText(h->f77NodeText);  
	}
	else {
	if ( _t!=NULL && (_t->token==REAL_ID) ) {
		_MATCH(REAL_ID);
		r=(SORAST *)_t;
		_RIGHT;
		f77PutText(r->f77NodeText);  
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

void o_substring(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *a=NULL;
	if ( _t!=NULL && (_t->token==CHARACTER_SUBSTRING) ) {
		_MATCH(CHARACTER_SUBSTRING);
		a=(SORAST *)_t;
		_RIGHT;
		f77PutText(a->f77NodeText);  
		o_lp(_parser, &_t);
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==FUNCTION_NAME||_t->token==CONSTINT||_t->token==MIN||
		_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==CHARACTER_ID||
		_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||
		_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||
		_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||_t->token==NOT||
		_t->token==UNARY_MIN||_t->token==PLU||_t->token==MUL||
		_t->token==POW||_t->token==AND||_t->token==OR||
		_t->token==NEQV||_t->token==EQV||_t->token==LT||
		_t->token==LE||_t->token==EQ||_t->token==NE||
		_t->token==GT||_t->token==GE||_t->token==IS||
		_t->token==HEX_CONST||_t->token==BASIC_REAL||_t->token==REAL_EXPO||
		_t->token==T_TRUE||_t->token==T_FALSE||_t->token==HOLLERITH_CONST||
		_t->token==CHARACTER_SUBSTRING||_t->token==LP||_t->token==QUOTED_STRING) ) {
			o_expression(_parser, &_t);
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
		f77PutText(":");  
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==FUNCTION_NAME||_t->token==CONSTINT||_t->token==MIN||
		_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==CHARACTER_ID||
		_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||
		_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||
		_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||_t->token==NOT||
		_t->token==UNARY_MIN||_t->token==PLU||_t->token==MUL||
		_t->token==POW||_t->token==AND||_t->token==OR||
		_t->token==NEQV||_t->token==EQV||_t->token==LT||
		_t->token==LE||_t->token==EQ||_t->token==NE||
		_t->token==GT||_t->token==GE||_t->token==IS||
		_t->token==HEX_CONST||_t->token==BASIC_REAL||_t->token==REAL_EXPO||
		_t->token==T_TRUE||_t->token==T_FALSE||_t->token==HOLLERITH_CONST||
		_t->token==CHARACTER_SUBSTRING||_t->token==LP||_t->token==QUOTED_STRING) ) {
			o_expression(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==RP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "substring", _t);
		}
		}
		o_rp(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "substring", _t);
	}
	*_root = _t;
}

void o_control_image(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==CONTROL_IMAGE) ) {
		f77NewLine(0);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(CONTROL_IMAGE);
		_DOWN;
		f77PutText("C$");  
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL ) {
				f77PutText(" ");  
				o_any_token(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "control_image", _t);
	}
	*_root = _t;
}

void o_file_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *f=NULL;
	if ( _t!=NULL && (_t->token==FILEKEYWORD) ) {
		f77NewLine(0);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(FILEKEYWORD);
		f=(SORAST *)_t;
		_DOWN;
		f77PutText("FILE ");  
		o_const_int(_parser, &_t);
		o_lp(_parser, &_t);
		o_file_item(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				o_comma(_parser, &_t);
				o_file_item(_parser, &_t);
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
		o_rp(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "file_statement", _t);
	}
	*_root = _t;
}

void o_file_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==KIND) ) {
		_MATCH(KIND);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		f77PutText("KIND= ");  
		o_any_token(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==TITLE) ) {
		_MATCH(TITLE);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		f77PutText("FILE= ");  
		o_any_token(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==FILETYPE) ) {
		_MATCH(FILETYPE);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		f77PutText("FILETYPE= ");  
		o_any_token(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==NEWFILE) ) {
		_MATCH(NEWFILE);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		f77PutText("NEWFILE= ");  
		o_any_token(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==MYUSE) ) {
		_MATCH(MYUSE);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		f77PutText("MYUSE= ");  
		o_any_token(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==MAXRECSIZE) ) {
		_MATCH(MAXRECSIZE);
		_RIGHT;
		f77PutText("RECL= ");  
		_MATCH(EQUAL);
		_RIGHT;
		o_any_token(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==SAVEFACTOR) ) {
		_MATCH(SAVEFACTOR);
		_RIGHT;
		f77PutText("SAVEFACTOR= ");  
		_MATCH(EQUAL);
		_RIGHT;
		o_any_token(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==BLOCKSIZE) ) {
		_MATCH(BLOCKSIZE);
		_RIGHT;
		f77PutText("BLOCKSIZE= ");  
		_MATCH(EQUAL);
		_RIGHT;
		o_any_token(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==SECURITYTYPE) ) {
		_MATCH(SECURITYTYPE);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		f77PutText("SECURITYTYPE= ");  
		o_any_token(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==AREAS) ) {
		_MATCH(AREAS);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		f77PutText("AREAS= ");  
		o_any_token(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==AREASIZE) ) {
		_MATCH(AREASIZE);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		f77PutText("AREASIZE= ");  
		o_any_token(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==PROTECTION) ) {
		_MATCH(PROTECTION);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		f77PutText("PROTECTION= ");  
		o_any_token(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==UNITS) ) {
		_MATCH(UNITS);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		f77PutText("UNITS= ");  
		o_any_token(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==UPDATEFILE) ) {
		_MATCH(UPDATEFILE);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		f77PutText("UPDATEFILE= ");  
		o_any_token(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==FILE_WORD) ) {
		_MATCH(FILE_WORD);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		f77PutText("FILE= ");  
		o_any_token(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==STATUS) ) {
		_MATCH(STATUS);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		f77PutText("STATEUS= ");  
		o_any_token(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==ACCESS) ) {
		_MATCH(ACCESS);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		f77PutText("ACCESS= ");  
		o_any_token(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==FORM) ) {
		_MATCH(FORM);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		f77PutText("FORM= ");  
		o_any_token(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==RECL) ) {
		_MATCH(RECL);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		f77PutText("RECL= ");  
		o_any_token(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==BLANK) ) {
		_MATCH(BLANK);
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		f77PutText("BLANK= ");  
		o_any_token(_parser, &_t);
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

void o_find_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==FIND) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(FIND);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "find_statement", _t);
		}
		}
		f77PutText("FIND ");  
		o_lp(_parser, &_t);
		o_findlist(_parser, &_t);
		o_rp(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "find_statement", _t);
	}
	*_root = _t;
}

void o_findlist(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==COMMA) ) {
		if ( _t!=NULL && (_t->token==COMMA) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(COMMA);
			_DOWN;
			o_unit_id(_parser, &_t);
			f77PutText(",");  
			_MATCH(REC);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			f77PutText("REC=");  
			o_integer_expr(_parser, &_t);
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
			o_unit_id(_parser, &_t);
			f77PutText(",");  
			o_integer_expr(_parser, &_t);
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
			f77PutText("UNIT=");  
			o_unit_id(_parser, &_t);
			o_comma(_parser, &_t);
			_MATCH(REC);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			f77PutText("REC=");  
			o_integer_expr(_parser, &_t);
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
			f77PutText("REC=");  
			o_integer_expr(_parser, &_t);
			o_comma(_parser, &_t);
			_MATCH(UNIT);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			f77PutText("UNIT=");  
			o_unit_id(_parser, &_t);
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

void o_character_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==CHARACTER) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(CHARACTER);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t==NULL || (_t!=NULL) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "character_statement", _t);
		}
		}
		f77PutText("CHARACTER ");  
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL ) {
				o_any_token(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "character_statement", _t);
	}
	*_root = _t;
}

void o_integer_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==INTEGER) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(INTEGER);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t==NULL || (_t!=NULL) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "integer_statement", _t);
		}
		}
		f77PutText("INTEGER ");  
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL ) {
				o_any_token(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "integer_statement", _t);
	}
	*_root = _t;
}

void o_real_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==REAL) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(REAL);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t==NULL || (_t!=NULL) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "real_statement", _t);
		}
		}
		f77PutText("REAL ");  
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL ) {
				o_any_token(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "real_statement", _t);
	}
	*_root = _t;
}

void o_logical_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==LOGICAL) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(LOGICAL);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t==NULL || (_t!=NULL) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "logical_statement", _t);
		}
		}
		f77PutText("LOGICAL ");  
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL ) {
				o_any_token(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "logical_statement", _t);
	}
	*_root = _t;
}

void o_precision_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DOUBLE_PRECISION) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(DOUBLE_PRECISION);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t==NULL || (_t!=NULL) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "precision_statement", _t);
		}
		}
		f77PutText("DOUBLE PRECISION ");  
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL ) {
				o_any_token(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "precision_statement", _t);
	}
	*_root = _t;
}

void o_dimension_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DIMENSION) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(DIMENSION);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t==NULL || (_t!=NULL) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "dimension_statement", _t);
		}
		}
		f77PutText("DIMENSION ");  
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL ) {
				o_any_token(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "dimension_statement", _t);
	}
	*_root = _t;
}

void o_equivalence_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==EQUIVALENCE) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(EQUIVALENCE);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t==NULL || (_t!=NULL) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "equivalence_statement", _t);
		}
		}
		f77PutText("EQUIVALENCE ");  
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL ) {
				o_any_token(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "equivalence_statement", _t);
	}
	*_root = _t;
}

void o_backspace_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==BACKSPACE) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(BACKSPACE);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==FUNCTION_NAME||_t->token==STAR||_t->token==CONSTINT||
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
		_t->token==HOLLERITH_CONST||_t->token==CHARACTER_SUBSTRING||_t->token==IO_SPEC_LP||
		_t->token==LP||_t->token==QUOTED_STRING) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "backspace_statement", _t);
		}
		}
		f77PutText("READ ");  
		o_io_specifier(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "backspace_statement", _t);
	}
	*_root = _t;
}

void o_endfile_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==ENDFILE) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(ENDFILE);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==FUNCTION_NAME||_t->token==STAR||_t->token==CONSTINT||
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
		_t->token==HOLLERITH_CONST||_t->token==CHARACTER_SUBSTRING||_t->token==IO_SPEC_LP||
		_t->token==LP||_t->token==QUOTED_STRING) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "endfile_statement", _t);
		}
		}
		f77PutText("ENDFILE ");  
		o_io_specifier(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "endfile_statement", _t);
	}
	*_root = _t;
}

void o_rewind_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==REWIND) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(REWIND);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==FUNCTION_NAME||_t->token==STAR||_t->token==CONSTINT||
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
		_t->token==HOLLERITH_CONST||_t->token==CHARACTER_SUBSTRING||_t->token==IO_SPEC_LP||
		_t->token==LP||_t->token==QUOTED_STRING) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "rewind_statement", _t);
		}
		}
		f77PutText("REWIND ");  
		o_io_specifier(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "rewind_statement", _t);
	}
	*_root = _t;
}

void o_io_specifier(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==IO_SPEC_LP) ) {
		_MATCH(IO_SPEC_LP);
		_RIGHT;
		f77PutText("(");  
		if ( _t!=NULL && (_t->token==UNIT) ) {
			_MATCH(UNIT);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			f77PutText("UNIT=");  
		}
		else {
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==FUNCTION_NAME||_t->token==STAR||_t->token==CONSTINT||
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
		_t->token==HOLLERITH_CONST||_t->token==CHARACTER_SUBSTRING||_t->token==LP||
		_t->token==QUOTED_STRING) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "io_specifier", _t);
		}
		}
		o_unit_id(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==ERR) ) {
				{_SAVE; TREE_CONSTR_PTRS;
				_MATCH(ERR);
				_DOWN;
				o_comma(_parser, &_t);
				_MATCH(EQUAL);
				_RIGHT;
				f77PutText("ERR=");  
				o_const_int(_parser, &_t);
				_RESTORE;
				}
				_RIGHT;
			}
			else {
			if ( _t!=NULL && (_t->token==IOSTAT) ) {
				{_SAVE; TREE_CONSTR_PTRS;
				_MATCH(IOSTAT);
				_DOWN;
				o_comma(_parser, &_t);
				_MATCH(EQUAL);
				_RIGHT;
				f77PutText("IOSTAT=");  
				o_exp_operand(_parser, &_t);
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
		f77PutText(")");  
	}
	else {
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==FUNCTION_NAME||_t->token==STAR||_t->token==CONSTINT||
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
	_t->token==HOLLERITH_CONST||_t->token==CHARACTER_SUBSTRING||_t->token==LP||
	_t->token==QUOTED_STRING) ) {
		o_unit_id(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "io_specifier", _t);
	}
	}
	*_root = _t;
}

void o_read_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==READ) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(READ);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "read_statement", _t);
		}
		}
		f77PutText("READ ");  
		o_control_info(_parser, &_t);
		o_input_list(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "read_statement", _t);
	}
	*_root = _t;
}

void o_write_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==WRITE) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(WRITE);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "write_statement", _t);
		}
		}
		f77PutText("WRITE ");  
		o_control_info(_parser, &_t);
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==FUNCTION_NAME||_t->token==CONSTINT||_t->token==MIN||
		_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==CHARACTER_ID||
		_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||
		_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||
		_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||_t->token==NOT||
		_t->token==UNARY_MIN||_t->token==PLU||_t->token==MUL||
		_t->token==POW||_t->token==AND||_t->token==OR||
		_t->token==NEQV||_t->token==EQV||_t->token==LT||
		_t->token==LE||_t->token==EQ||_t->token==NE||
		_t->token==GT||_t->token==GE||_t->token==IS||
		_t->token==HEX_CONST||_t->token==BASIC_REAL||_t->token==REAL_EXPO||
		_t->token==T_TRUE||_t->token==T_FALSE||_t->token==HOLLERITH_CONST||
		_t->token==CHARACTER_SUBSTRING||_t->token==IMPLIED_LP||_t->token==LP||
		_t->token==QUOTED_STRING) ) {
			o_output_list(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "write_statement", _t);
	}
	*_root = _t;
}

void o_control_info(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==LP) ) {
		o_lp(_parser, &_t);
		if ( _t!=NULL && (_t->token==COMMA) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(COMMA);
			_DOWN;
			o_unit_id(_parser, &_t);
			f77PutText(",");  
			o_format_id(_parser, &_t);
			_RESTORE;
			}
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==APOSTROPHY) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(APOSTROPHY);
			_DOWN;
			o_unit_id(_parser, &_t);
			f77PutText("\'");  
			o_integer_expr(_parser, &_t);
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
			f77PutText("=");  
			o_unit_id(_parser, &_t);
			_RESTORE;
			}
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==FUNCTION_NAME||_t->token==STAR||_t->token==CONSTINT||
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
		_t->token==HOLLERITH_CONST||_t->token==CHARACTER_SUBSTRING||_t->token==LP||
		_t->token==QUOTED_STRING) ) {
			o_unit_id(_parser, &_t);
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
				o_the_remainder(_parser, &_t);
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
		o_rp(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "control_info", _t);
	}
	*_root = _t;
}

void o_the_remainder(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==COMMA) ) {
		o_comma(_parser, &_t);
		if ( _t!=NULL && (_t->token==FMT) ) {
			_MATCH(FMT);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			f77PutText("FMT=");  
			o_format_id(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==IO_DATA) ) {
			_MATCH(IO_DATA);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			f77PutText("DATA=");  
			o_integer_expr(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==REC) ) {
			_MATCH(REC);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			f77PutText("REC=");  
			o_integer_expr(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==END) ) {
			_MATCH(END);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			f77PutText("END=");  
			o_const_int(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==ERR) ) {
			_MATCH(ERR);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			f77PutText("ERR=");  
			o_const_int(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==IOSTAT) ) {
			_MATCH(IOSTAT);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			f77PutText("IOSTAT=");  
			o_exp_operand(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==URGENT) ) {
			_MATCH(URGENT);
			_RIGHT;
			_MATCH(EQUAL);
			_RIGHT;
			f77PutText("URGENT=");  
			o_expression(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==FUNCTION_NAME||_t->token==STAR||_t->token==CONSTINT||
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
		_t->token==HOLLERITH_CONST||_t->token==CHARACTER_SUBSTRING||_t->token==SLASH||
		_t->token==LP||_t->token==QUOTED_STRING) ) {
			o_format_id(_parser, &_t);
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
}

void o_unit_id(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==STAR) ) {
		_MATCH(STAR);
		_RIGHT;
		f77PutText("*");  
	}
	else {
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==FUNCTION_NAME||_t->token==CONSTINT||_t->token==MIN||
	_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==CHARACTER_ID||
	_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||
	_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||
	_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||_t->token==NOT||
	_t->token==UNARY_MIN||_t->token==PLU||_t->token==MUL||
	_t->token==POW||_t->token==AND||_t->token==OR||
	_t->token==NEQV||_t->token==EQV||_t->token==LT||
	_t->token==LE||_t->token==EQ||_t->token==NE||
	_t->token==GT||_t->token==GE||_t->token==IS||
	_t->token==HEX_CONST||_t->token==BASIC_REAL||_t->token==REAL_EXPO||
	_t->token==T_TRUE||_t->token==T_FALSE||_t->token==HOLLERITH_CONST||
	_t->token==CHARACTER_SUBSTRING||_t->token==LP||_t->token==QUOTED_STRING) ) {
		o_expression(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "unit_id", _t);
	}
	}
	*_root = _t;
}

void o_format_id(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==STAR) ) {
		if ( _t!=NULL && (_t->token==STAR) ) {
			_MATCH(STAR);
			_RIGHT;
			f77PutText("*");  
			if ( _t!=NULL && (_t->token==SLASH) ) {
				_MATCH(SLASH);
				_RIGHT;
				f77PutText("/");  
			}
			else {
			if ( _t==NULL || (_t->token==COMMA||_t->token==RP) ) {
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "format_id", _t);
			}
			}
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "format_id", _t);
		}
	}
	else {
	if ( _t!=NULL && (_t->token==SLASH) ) {
		_MATCH(SLASH);
		_RIGHT;
		f77PutText("/");  
	}
	else {
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==FUNCTION_NAME||_t->token==CONSTINT||_t->token==MIN||
	_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==CHARACTER_ID||
	_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||
	_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||
	_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||_t->token==NOT||
	_t->token==UNARY_MIN||_t->token==PLU||_t->token==MUL||
	_t->token==POW||_t->token==AND||_t->token==OR||
	_t->token==NEQV||_t->token==EQV||_t->token==LT||
	_t->token==LE||_t->token==EQ||_t->token==NE||
	_t->token==GT||_t->token==GE||_t->token==IS||
	_t->token==HEX_CONST||_t->token==BASIC_REAL||_t->token==REAL_EXPO||
	_t->token==T_TRUE||_t->token==T_FALSE||_t->token==HOLLERITH_CONST||
	_t->token==CHARACTER_SUBSTRING||_t->token==LP||_t->token==QUOTED_STRING) ) {
		o_expression(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "format_id", _t);
	}
	}
	}
	*_root = _t;
}

void o_input_list(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==FUNCTION_NAME||_t->token==CONSTINT||
	_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==CHARACTER_ID||
	_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||
	_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||
	_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==HEX_CONST||_t->token==BASIC_REAL||
	_t->token==REAL_EXPO||_t->token==T_TRUE||_t->token==T_FALSE||
	_t->token==HOLLERITH_CONST||_t->token==CHARACTER_SUBSTRING||_t->token==IMPLIED_LP||
	_t->token==LP||_t->token==QUOTED_STRING) ) {
		o_input_item(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				o_comma(_parser, &_t);
				o_input_item(_parser, &_t);
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

void o_input_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==FUNCTION_NAME||_t->token==CONSTINT||
	_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==CHARACTER_ID||
	_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||
	_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||
	_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==HEX_CONST||_t->token==BASIC_REAL||
	_t->token==REAL_EXPO||_t->token==T_TRUE||_t->token==T_FALSE||
	_t->token==HOLLERITH_CONST||_t->token==CHARACTER_SUBSTRING||_t->token==IMPLIED_LP||
	_t->token==LP||_t->token==QUOTED_STRING) ) {
		if ( _t!=NULL && (_t->token==FUNCTION_NAME||_t->token==CONSTINT||
		_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==CHARACTER_ID||
		_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||
		_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||
		_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==HEX_CONST||_t->token==BASIC_REAL||
		_t->token==REAL_EXPO||_t->token==T_TRUE||_t->token==T_FALSE||
		_t->token==HOLLERITH_CONST||_t->token==CHARACTER_SUBSTRING||_t->token==LP||
		_t->token==QUOTED_STRING) ) {
			o_exp_operand(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==IMPLIED_LP) ) {
			o_inp_implied_list(_parser, &_t);
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

void o_inp_implied_list(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==IMPLIED_LP) ) {
		_MATCH(IMPLIED_LP);
		_RIGHT;
		f77PutText("(");  
		{int _done=0;
		do {
			if ( _t!=NULL && (_t->token==FUNCTION_NAME||_t->token==CONSTINT||
			_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==CHARACTER_ID||
			_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||
			_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||
			_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==HEX_CONST||_t->token==BASIC_REAL||
			_t->token==REAL_EXPO||_t->token==T_TRUE||_t->token==T_FALSE||
			_t->token==HOLLERITH_CONST||_t->token==CHARACTER_SUBSTRING||_t->token==IMPLIED_LP||
			_t->token==LP||_t->token==QUOTED_STRING) ) {
				o_input_item(_parser, &_t);
				o_comma(_parser, &_t);
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
		o_implied_loop(_parser, &_t);
		_MATCH(IMPLIED_RP);
		_RIGHT;
		f77PutText(")");  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "inp_implied_list", _t);
	}
	*_root = _t;
}

void o_output_list(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==FUNCTION_NAME||_t->token==CONSTINT||_t->token==MIN||
	_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==CHARACTER_ID||
	_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||
	_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||
	_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||_t->token==NOT||
	_t->token==UNARY_MIN||_t->token==PLU||_t->token==MUL||
	_t->token==POW||_t->token==AND||_t->token==OR||
	_t->token==NEQV||_t->token==EQV||_t->token==LT||
	_t->token==LE||_t->token==EQ||_t->token==NE||
	_t->token==GT||_t->token==GE||_t->token==IS||
	_t->token==HEX_CONST||_t->token==BASIC_REAL||_t->token==REAL_EXPO||
	_t->token==T_TRUE||_t->token==T_FALSE||_t->token==HOLLERITH_CONST||
	_t->token==CHARACTER_SUBSTRING||_t->token==IMPLIED_LP||_t->token==LP||
	_t->token==QUOTED_STRING) ) {
		o_output_item(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				o_comma(_parser, &_t);
				o_output_item(_parser, &_t);
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

void o_output_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==IMPLIED_LP) ) {
		o_outp_implied_list(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==FUNCTION_NAME||_t->token==CONSTINT||_t->token==MIN||
	_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==CHARACTER_ID||
	_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||
	_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||
	_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||_t->token==NOT||
	_t->token==UNARY_MIN||_t->token==PLU||_t->token==MUL||
	_t->token==POW||_t->token==AND||_t->token==OR||
	_t->token==NEQV||_t->token==EQV||_t->token==LT||
	_t->token==LE||_t->token==EQ||_t->token==NE||
	_t->token==GT||_t->token==GE||_t->token==IS||
	_t->token==HEX_CONST||_t->token==BASIC_REAL||_t->token==REAL_EXPO||
	_t->token==T_TRUE||_t->token==T_FALSE||_t->token==HOLLERITH_CONST||
	_t->token==CHARACTER_SUBSTRING||_t->token==LP||_t->token==QUOTED_STRING) ) {
		o_rvalue(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "output_item", _t);
	}
	}
	*_root = _t;
}

void o_outp_implied_list(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==IMPLIED_LP) ) {
		_MATCH(IMPLIED_LP);
		_RIGHT;
		f77PutText("(");  
		{int _done=0;
		do {
			if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
			_t->token==FUNCTION_NAME||_t->token==CONSTINT||_t->token==MIN||
			_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==CHARACTER_ID||
			_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||
			_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||
			_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||_t->token==NOT||
			_t->token==UNARY_MIN||_t->token==PLU||_t->token==MUL||
			_t->token==POW||_t->token==AND||_t->token==OR||
			_t->token==NEQV||_t->token==EQV||_t->token==LT||
			_t->token==LE||_t->token==EQ||_t->token==NE||
			_t->token==GT||_t->token==GE||_t->token==IS||
			_t->token==HEX_CONST||_t->token==BASIC_REAL||_t->token==REAL_EXPO||
			_t->token==T_TRUE||_t->token==T_FALSE||_t->token==HOLLERITH_CONST||
			_t->token==CHARACTER_SUBSTRING||_t->token==IMPLIED_LP||_t->token==LP||
			_t->token==QUOTED_STRING) ) {
				o_output_item(_parser, &_t);
				o_comma(_parser, &_t);
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
		o_implied_loop(_parser, &_t);
		_MATCH(IMPLIED_RP);
		_RIGHT;
		f77PutText(")");  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "outp_implied_list", _t);
	}
	*_root = _t;
}

void o_implied_loop(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *i=NULL;
	if ( _t!=NULL && (_t->token==IMPLIED_DO_VARIABLE) ) {
		_MATCH(IMPLIED_DO_VARIABLE);
		i=(SORAST *)_t;
		_RIGHT;
		f77PutText(i->f77NodeText);  
		o_equal(_parser, &_t);
		o_integer_expr(_parser, &_t);
		o_comma(_parser, &_t);
		o_integer_expr(_parser, &_t);
		if ( _t!=NULL && (_t->token==COMMA) ) {
			o_comma(_parser, &_t);
			o_integer_expr(_parser, &_t);
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

void o_open_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==OPEN) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(OPEN);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "open_statement", _t);
		}
		}
		f77PutText("OPEN ");  
		o_lp(_parser, &_t);
		o_open_item(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				o_comma(_parser, &_t);
				o_open_item(_parser, &_t);
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
		o_rp(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "open_statement", _t);
	}
	*_root = _t;
}

void o_open_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==FUNCTION_NAME||_t->token==STAR||_t->token==CONSTINT||
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
	_t->token==HOLLERITH_CONST||_t->token==CHARACTER_SUBSTRING||_t->token==UNIT||
	_t->token==LP||_t->token==QUOTED_STRING) ) {
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==FUNCTION_NAME||_t->token==STAR||_t->token==CONSTINT||
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
		_t->token==HOLLERITH_CONST||_t->token==CHARACTER_SUBSTRING||_t->token==UNIT||
		_t->token==LP||_t->token==QUOTED_STRING) ) {
			if ( _t!=NULL && (_t->token==UNIT) ) {
				_MATCH(UNIT);
				_RIGHT;
				_MATCH(EQUAL);
				_RIGHT;
				f77PutText("UNIT=");  
			}
			else {
			if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
			_t->token==FUNCTION_NAME||_t->token==STAR||_t->token==CONSTINT||
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
			_t->token==HOLLERITH_CONST||_t->token==CHARACTER_SUBSTRING||_t->token==LP||
			_t->token==QUOTED_STRING) ) {
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "open_item", _t);
			}
			}
			o_unit_id(_parser, &_t);
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
			f77PutText("ERR=");  
			o_const_int(_parser, &_t);
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
			f77PutText("FILE=");  
			o_expression(_parser, &_t);
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
			f77PutText("STATUS=");  
			o_expression(_parser, &_t);
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
			f77PutText("ACCESS=");  
			o_expression(_parser, &_t);
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
			f77PutText("FORM=");  
			o_expression(_parser, &_t);
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
			f77PutText("RECL=");  
			o_expression(_parser, &_t);
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
			f77PutText("IOSTAT=");  
			o_exp_operand(_parser, &_t);
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
			f77PutText("FILE=");  
			o_expression(_parser, &_t);
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
			f77PutText("STATUS=");  
			o_expression(_parser, &_t);
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
			f77PutText("SUBFILE=");  
			o_integer_expr(_parser, &_t);
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
			f77PutText("RECL=");  
			o_integer_expr(_parser, &_t);
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
			f77PutText("SAVEFACTOR=");  
			o_integer_expr(_parser, &_t);
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
			f77PutText("OPENTYPE=");  
			o_expression(_parser, &_t);
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

void o_close_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==CLOSE) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(CLOSE);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "close_statement", _t);
		}
		}
		f77PutText("CLOSE ");  
		o_lp(_parser, &_t);
		o_close_item(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				o_comma(_parser, &_t);
				o_close_item(_parser, &_t);
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
		o_rp(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "close_statement", _t);
	}
	*_root = _t;
}

void o_close_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==FUNCTION_NAME||_t->token==STAR||_t->token==CONSTINT||
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
	_t->token==HOLLERITH_CONST||_t->token==CHARACTER_SUBSTRING||_t->token==UNIT||
	_t->token==LP||_t->token==QUOTED_STRING) ) {
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==FUNCTION_NAME||_t->token==STAR||_t->token==CONSTINT||
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
		_t->token==HOLLERITH_CONST||_t->token==CHARACTER_SUBSTRING||_t->token==UNIT||
		_t->token==LP||_t->token==QUOTED_STRING) ) {
			if ( _t!=NULL && (_t->token==UNIT) ) {
				_MATCH(UNIT);
				_RIGHT;
				_MATCH(EQUAL);
				_RIGHT;
				f77PutText("UNIT=");  
			}
			else {
			if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
			_t->token==FUNCTION_NAME||_t->token==STAR||_t->token==CONSTINT||
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
			_t->token==HOLLERITH_CONST||_t->token==CHARACTER_SUBSTRING||_t->token==LP||
			_t->token==QUOTED_STRING) ) {
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "close_item", _t);
			}
			}
			o_unit_id(_parser, &_t);
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
			f77PutText("ERR=");  
			o_const_int(_parser, &_t);
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
			f77PutText("STATUS=");  
			o_close_name(_parser, &_t);
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
			f77PutText("IOSTAT=");  
			o_exp_operand(_parser, &_t);
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
			f77PutText("STATUS=");  
			o_close_name(_parser, &_t);
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
			f77PutText("SUBFILE=");  
			o_integer_expr(_parser, &_t);
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

void o_close_name(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==IDENTIFIER||_t->token==QUOTED_STRING) ) {
		if ( _t!=NULL && (_t->token==IDENTIFIER) ) {
			o_identifier(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==QUOTED_STRING) ) {
			o_quoted_string(_parser, &_t);
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

void o_call_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *f=NULL;
	if ( _t!=NULL && (_t->token==CALL) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(CALL);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==FUNCTION_NAME) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "call_statement", _t);
		}
		}
		f77PutText("CALL ");  
		_MATCH(FUNCTION_NAME);
		f=(SORAST *)_t;
		_RIGHT;
		f77PutText(f->f77NodeText);  
		if ( _t!=NULL && (_t->token==LP) ) {
			o_call_arg_list(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "call_statement", _t);
	}
	*_root = _t;
}

void o_call_arg_list(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==LP) ) {
		o_lp(_parser, &_t);
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==FUNCTION_NAME||_t->token==STAR||_t->token==CONSTINT||
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
		_t->token==HOLLERITH_CONST||_t->token==CHARACTER_SUBSTRING||_t->token==AMPERSAND||
		_t->token==LP||_t->token==QUOTED_STRING) ) {
			o_call_arg_item(_parser, &_t);
			{int _done=0;
			while ( !_done ) {
				if ( _t!=NULL && (_t->token==COMMA) ) {
					o_comma(_parser, &_t);
					o_call_arg_item(_parser, &_t);
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
		o_rp(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "call_arg_list", _t);
	}
	*_root = _t;
}

void o_call_arg_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *c=NULL;
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==FUNCTION_NAME||_t->token==STAR||_t->token==CONSTINT||
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
	_t->token==HOLLERITH_CONST||_t->token==CHARACTER_SUBSTRING||_t->token==AMPERSAND||
	_t->token==LP||_t->token==QUOTED_STRING) ) {
		if ( _t!=NULL && (_t->token==STAR||_t->token==AMPERSAND) ) {
			if ( _t!=NULL && (_t->token==STAR) ) {
				_MATCH(STAR);
				_RIGHT;
				f77PutText("*");  
			}
			else {
			if ( _t!=NULL && (_t->token==AMPERSAND) ) {
				_MATCH(AMPERSAND);
				_RIGHT;
				f77PutText("&");  
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "call_arg_item", _t);
			}
			}
			_MATCH(CONSTINT);
			c=(SORAST *)_t;
			_RIGHT;
			f77PutText(c->f77NodeText);  
		}
		else {
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==FUNCTION_NAME||_t->token==CONSTINT||_t->token==MIN||
		_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==CHARACTER_ID||
		_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||
		_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||
		_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||_t->token==NOT||
		_t->token==UNARY_MIN||_t->token==PLU||_t->token==MUL||
		_t->token==POW||_t->token==AND||_t->token==OR||
		_t->token==NEQV||_t->token==EQV||_t->token==LT||
		_t->token==LE||_t->token==EQ||_t->token==NE||
		_t->token==GT||_t->token==GE||_t->token==IS||
		_t->token==HEX_CONST||_t->token==BASIC_REAL||_t->token==REAL_EXPO||
		_t->token==T_TRUE||_t->token==T_FALSE||_t->token==HOLLERITH_CONST||
		_t->token==CHARACTER_SUBSTRING||_t->token==LP||_t->token==QUOTED_STRING) ) {
			o_expression(_parser, &_t);
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

void o_export_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==EXPORT) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(EXPORT);
		_DOWN;
		f77PutText("EXPORT ");  
		{int _done=0;
		do {
			if ( _t!=NULL ) {
				o_any_token(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "export_statement", _t);
	}
	*_root = _t;
}

void o_subroutine_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==SUBROUTINE) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(SUBROUTINE);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==IDENTIFIER) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "subroutine_statement", _t);
		}
		}
		f77PutText("SUBROUTINE ");  
		o_identifier(_parser, &_t);
		if ( _t!=NULL && (_t->token==LP) ) {
			o_call_arg_list(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "subroutine_statement", _t);
	}
	*_root = _t;
}

void o_entry_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==ENTRY) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(ENTRY);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==IDENTIFIER) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "entry_statement", _t);
		}
		}
		f77PutText("ENTRY ");  
		o_identifier(_parser, &_t);
		if ( _t!=NULL && (_t->token==LP) ) {
			o_call_arg_list(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "entry_statement", _t);
	}
	*_root = _t;
}

void o_function_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==FUNCTION) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(FUNCTION);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
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
			o_function_type(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==IDENTIFIER) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "function_statement", _t);
		}
		}
		f77PutText("FUNCTION ");  
		o_identifier(_parser, &_t);
		o_lp(_parser, &_t);
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==FUNCTION_NAME||_t->token==CONSTINT||_t->token==MIN||
		_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==CHARACTER_ID||
		_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||
		_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||
		_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||_t->token==NOT||
		_t->token==UNARY_MIN||_t->token==PLU||_t->token==MUL||
		_t->token==POW||_t->token==AND||_t->token==OR||
		_t->token==NEQV||_t->token==EQV||_t->token==LT||
		_t->token==LE||_t->token==EQ||_t->token==NE||
		_t->token==GT||_t->token==GE||_t->token==IS||
		_t->token==HEX_CONST||_t->token==BASIC_REAL||_t->token==REAL_EXPO||
		_t->token==T_TRUE||_t->token==T_FALSE||_t->token==HOLLERITH_CONST||
		_t->token==CHARACTER_SUBSTRING||_t->token==SLASH||_t->token==LP||
		_t->token==QUOTED_STRING) ) {
			o_function_arg_list(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==RP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "function_statement", _t);
		}
		}
		o_rp(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "function_statement", _t);
	}
	*_root = _t;
}

void o_function_type(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *i=NULL;
	if ( _t!=NULL && (_t->token==INTEGER||_t->token==REAL||
	_t->token==DOUBLE_PRECISION||_t->token==LOGICAL||_t->token==CHARACTER||
	_t->token==COMPLEX||_t->token==DOUBLE_COMPLEX) ) {
		if ( _t!=NULL && (_t->token==INTEGER) ) {
			_MATCH(INTEGER);
			i=(SORAST *)_t;
			_RIGHT;
			f77PutText(i->f77NodeText);  
		}
		else {
		if ( _t!=NULL && (_t->token==REAL) ) {
			_MATCH(REAL);
			i=(SORAST *)_t;
			_RIGHT;
			f77PutText(i->f77NodeText);  
		}
		else {
		if ( _t!=NULL && (_t->token==DOUBLE_PRECISION) ) {
			_MATCH(DOUBLE_PRECISION);
			i=(SORAST *)_t;
			_RIGHT;
			f77PutText(i->f77NodeText);  
		}
		else {
		if ( _t!=NULL && (_t->token==LOGICAL) ) {
			_MATCH(LOGICAL);
			i=(SORAST *)_t;
			_RIGHT;
			f77PutText(i->f77NodeText);  
		}
		else {
		if ( _t!=NULL && (_t->token==CHARACTER) ) {
			_MATCH(CHARACTER);
			i=(SORAST *)_t;
			_RIGHT;
			f77PutText(i->f77NodeText);  
		}
		else {
		if ( _t!=NULL && (_t->token==COMPLEX) ) {
			_MATCH(COMPLEX);
			i=(SORAST *)_t;
			_RIGHT;
			f77PutText(i->f77NodeText);  
		}
		else {
		if ( _t!=NULL && (_t->token==DOUBLE_COMPLEX) ) {
			_MATCH(DOUBLE_COMPLEX);
			i=(SORAST *)_t;
			_RIGHT;
			f77PutText(i->f77NodeText);  
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
			f77PutText("*");  
			o_length_spec(_parser, &_t);
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

void o_function_arg_list(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
	_t->token==FUNCTION_NAME||_t->token==CONSTINT||_t->token==MIN||
	_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==CHARACTER_ID||
	_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||
	_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||
	_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||_t->token==NOT||
	_t->token==UNARY_MIN||_t->token==PLU||_t->token==MUL||
	_t->token==POW||_t->token==AND||_t->token==OR||
	_t->token==NEQV||_t->token==EQV||_t->token==LT||
	_t->token==LE||_t->token==EQ||_t->token==NE||
	_t->token==GT||_t->token==GE||_t->token==IS||
	_t->token==HEX_CONST||_t->token==BASIC_REAL||_t->token==REAL_EXPO||
	_t->token==T_TRUE||_t->token==T_FALSE||_t->token==HOLLERITH_CONST||
	_t->token==CHARACTER_SUBSTRING||_t->token==SLASH||_t->token==LP||
	_t->token==QUOTED_STRING) ) {
		if ( _t!=NULL && (_t->token==SLASH) ) {
			_MATCH(SLASH);
			_RIGHT;
			f77PutText("/");  
		}
		else {
		if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
		_t->token==FUNCTION_NAME||_t->token==CONSTINT||_t->token==MIN||
		_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==CHARACTER_ID||
		_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||
		_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||
		_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||_t->token==NOT||
		_t->token==UNARY_MIN||_t->token==PLU||_t->token==MUL||
		_t->token==POW||_t->token==AND||_t->token==OR||
		_t->token==NEQV||_t->token==EQV||_t->token==LT||
		_t->token==LE||_t->token==EQ||_t->token==NE||
		_t->token==GT||_t->token==GE||_t->token==IS||
		_t->token==HEX_CONST||_t->token==BASIC_REAL||_t->token==REAL_EXPO||
		_t->token==T_TRUE||_t->token==T_FALSE||_t->token==HOLLERITH_CONST||
		_t->token==CHARACTER_SUBSTRING||_t->token==LP||_t->token==QUOTED_STRING) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "function_arg_list", _t);
		}
		}
		o_expression(_parser, &_t);
		if ( _t!=NULL && (_t->token==SLASH) ) {
			_MATCH(SLASH);
			_RIGHT;
			f77PutText("/");  
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
				o_comma(_parser, &_t);
				if ( _t!=NULL && (_t->token==SLASH) ) {
					_MATCH(SLASH);
					_RIGHT;
					f77PutText("/");  
				}
				else {
				if ( _t!=NULL && (_t->token==DIV||_t->token==CONCAT||
				_t->token==FUNCTION_NAME||_t->token==CONSTINT||_t->token==MIN||
				_t->token==INTEGER_ID||_t->token==REAL_ID||_t->token==CHARACTER_ID||
				_t->token==DOUBLE_PRECISION_ID||_t->token==LOGICAL_ID||_t->token==INTEGER_ARRAY_ID||
				_t->token==REAL_ARRAY_ID||_t->token==CHARACTER_ARRAY_ID||_t->token==LOGICAL_ARRAY_ID||
				_t->token==DOUBLE_PRECISION_ARRAY_ID||_t->token==UNARY_PLU||_t->token==NOT||
				_t->token==UNARY_MIN||_t->token==PLU||_t->token==MUL||
				_t->token==POW||_t->token==AND||_t->token==OR||
				_t->token==NEQV||_t->token==EQV||_t->token==LT||
				_t->token==LE||_t->token==EQ||_t->token==NE||
				_t->token==GT||_t->token==GE||_t->token==IS||
				_t->token==HEX_CONST||_t->token==BASIC_REAL||_t->token==REAL_EXPO||
				_t->token==T_TRUE||_t->token==T_FALSE||_t->token==HOLLERITH_CONST||
				_t->token==CHARACTER_SUBSTRING||_t->token==LP||_t->token==QUOTED_STRING) ) {
				}
				else {
					if ( _parser->guessing ) _GUESS_FAIL;
					no_viable_alt(_parser, "function_arg_list", _t);
				}
				}
				o_expression(_parser, &_t);
				if ( _t!=NULL && (_t->token==SLASH) ) {
					_MATCH(SLASH);
					_RIGHT;
					f77PutText("/");  
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

void o_length_spec(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *c=NULL;
	if ( _t!=NULL && (_t->token==LP) ) {
		o_lp(_parser, &_t);
		if ( _t!=NULL && (_t->token==STAR) ) {
			_MATCH(STAR);
			_RIGHT;
			f77PutText("*");  
		}
		else {
		if ( _t!=NULL && (_t->token==DIV||_t->token==FUNCTION_NAME||
		_t->token==CONSTINT||_t->token==MIN||_t->token==INTEGER_ID||
		_t->token==REAL_ID||_t->token==INTEGER_ARRAY_ID||_t->token==UNARY_PLU||
		_t->token==UNARY_MIN||_t->token==PLU||_t->token==MUL||
		_t->token==HEX_CONST||_t->token==LP) ) {
			o_integer_expr(_parser, &_t);
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "length_spec", _t);
		}
		}
		o_rp(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CONSTINT) ) {
		_MATCH(CONSTINT);
		c=(SORAST *)_t;
		_RIGHT;
		f77PutText(c->f77NodeText);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "length_spec", _t);
	}
	}
	*_root = _t;
}

void o_block_if_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==BLOCK_IF) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(BLOCK_IF);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "block_if_statement", _t);
		}
		}
		f77PutText("IF ");  
		o_lp(_parser, &_t);
		o_expression(_parser, &_t);
		o_rp(_parser, &_t);
		_MATCH(THEN);
		_RIGHT;
		
		f77PutText(" THEN");
		f77PrintLine();
		Indentation++;
		o_block_if_block(_parser, &_t);
		Indentation--;  
		if ( _t!=NULL && (_t->token==ELSE||_t->token==ELSE_IF) ) {
			if ( _t!=NULL && (_t->token==ELSE||_t->token==ELSE_IF) ) {
				f77NewLine(Indentation);  
				if ( _t!=NULL && (_t->token==ELSE) ) {
					_MATCH(ELSE);
					_RIGHT;
					f77PutText("ELSE");  
				}
				else {
				if ( _t!=NULL && (_t->token==ELSE_IF) ) {
					_MATCH(ELSE_IF);
					_RIGHT;
					f77PutText("ELSE IF");  
					o_lp(_parser, &_t);
					o_expression(_parser, &_t);
					o_rp(_parser, &_t);
				}
				else {
					if ( _parser->guessing ) _GUESS_FAIL;
					no_viable_alt(_parser, "block_if_statement", _t);
				}
				}
				f77PrintLine();  
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "block_if_statement", _t);
			}
			Indentation++;  
			o_block_if_block(_parser, &_t);
			Indentation--;  
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
		_RIGHT;
		
		f77NewLine(Indentation);
		f77PutText("ENDIF");
		f77PrintLine();
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

void o_block_if_block(STreeParser *_parser, SORAST **_root)
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
				o_comment_line(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==BLANK_LINE) ) {
				o_blank_line(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==EQUAL) ) {
				o_assignment_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==DO) ) {
				o_do_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==CONTROL_IMAGE) ) {
				o_control_image(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==FORMAT) ) {
				o_format_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==READ) ) {
				o_read_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==WRITE) ) {
				o_write_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==OPEN) ) {
				o_open_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==CLOSE) ) {
				o_close_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==INQUIRE) ) {
				o_inquire_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==CHANGE) ) {
				o_change_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==FIND) ) {
				o_find_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==CALL) ) {
				o_call_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==BLOCK_IF) ) {
				o_block_if_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==ARITHMETIC_IF) ) {
				o_arithm_if_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==LOGICAL_IF) ) {
				o_log_if_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==UNCONDITIONAL_GOTO) ) {
				o_unconditional_goto(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==COMPUTED_GOTO) ) {
				o_computed_goto(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==ASSIGNED_GOTO) ) {
				o_assigned_goto(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==CONTINUE) ) {
				o_continue_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==STOP) ) {
				o_stop_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==RETURN) ) {
				o_return_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==BACKSPACE) ) {
				o_backspace_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==REWIND) ) {
				o_rewind_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==ENDFILE) ) {
				o_endfile_statement(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==ASSIGN) ) {
				o_assign_statement(_parser, &_t);
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

void o_log_if_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==LOGICAL_IF) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(LOGICAL_IF);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "log_if_statement", _t);
		}
		}
		f77PutText("IF ");  
		o_lp(_parser, &_t);
		o_expression(_parser, &_t);
		o_rp(_parser, &_t);
		DontStartNewLine = TRUE;  
		o_log_substatement(_parser, &_t);
		DontStartNewLine = FALSE;  
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

void o_arithm_if_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *a=NULL;
	SORAST *b=NULL;
	SORAST *c=NULL;
	if ( _t!=NULL && (_t->token==ARITHMETIC_IF) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(ARITHMETIC_IF);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "arithm_if_statement", _t);
		}
		}
		f77PutText("IF ");  
		o_lp(_parser, &_t);
		o_expression(_parser, &_t);
		o_rp(_parser, &_t);
		_MATCH(CONSTINT);
		a=(SORAST *)_t;
		_RIGHT;
		f77PutText(a->f77NodeText);  
		o_comma(_parser, &_t);
		_MATCH(CONSTINT);
		b=(SORAST *)_t;
		_RIGHT;
		f77PutText(b->f77NodeText);  
		o_comma(_parser, &_t);
		_MATCH(CONSTINT);
		c=(SORAST *)_t;
		_RIGHT;
		f77PutText(c->f77NodeText);  
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "arithm_if_statement", _t);
	}
	*_root = _t;
}

void o_log_substatement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==CONTINUE) ) {
		o_continue_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==EQUAL) ) {
		o_assignment_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==DO) ) {
		o_do_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==UNCONDITIONAL_GOTO) ) {
		o_unconditional_goto(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==COMPUTED_GOTO) ) {
		o_computed_goto(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==ASSIGNED_GOTO) ) {
		o_assigned_goto(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==READ) ) {
		o_read_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==WRITE) ) {
		o_write_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==OPEN) ) {
		o_open_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CLOSE) ) {
		o_close_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==INQUIRE) ) {
		o_inquire_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CHANGE) ) {
		o_change_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==FIND) ) {
		o_find_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==CALL) ) {
		o_call_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==END) ) {
		o_end_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==STOP) ) {
		o_stop_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==RETURN) ) {
		o_return_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==ARITHMETIC_IF) ) {
		o_arithm_if_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==BACKSPACE) ) {
		o_backspace_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==REWIND) ) {
		o_rewind_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==ENDFILE) ) {
		o_endfile_statement(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==ASSIGN) ) {
		o_assign_statement(_parser, &_t);
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

void o_continue_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==CONTINUE) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(CONTINUE);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "continue_statement", _t);
		}
		}
		f77PutText("CONTINUE ");  
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "continue_statement", _t);
	}
	*_root = _t;
}

void o_stop_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==STOP) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(STOP);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "stop_statement", _t);
		}
		}
		f77PutText("STOP ");  
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "stop_statement", _t);
	}
	*_root = _t;
}

void o_end_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==END) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(END);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "end_statement", _t);
		}
		}
		f77PutText("END ");  
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "end_statement", _t);
	}
	*_root = _t;
}

void o_return_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==RETURN) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(RETURN);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "return_statement", _t);
		}
		}
		f77PutText("RETURN ");  
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "return_statement", _t);
	}
	*_root = _t;
}

void o_unconditional_goto(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *c=NULL;
	if ( _t!=NULL && (_t->token==UNCONDITIONAL_GOTO) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(UNCONDITIONAL_GOTO);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==CONSTINT) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "unconditional_goto", _t);
		}
		}
		f77PutText("GOTO ");  
		_MATCH(CONSTINT);
		c=(SORAST *)_t;
		_RIGHT;
		f77PutText(c->f77NodeText);  
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "unconditional_goto", _t);
	}
	*_root = _t;
}

void o_computed_goto(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *a=NULL;
	SORAST *b=NULL;
	if ( _t!=NULL && (_t->token==COMPUTED_GOTO) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(COMPUTED_GOTO);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "computed_goto", _t);
		}
		}
		f77PutText("GOTO ");  
		o_lp(_parser, &_t);
		_MATCH(CONSTINT);
		a=(SORAST *)_t;
		_RIGHT;
		f77PutText(a->f77NodeText);  
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				o_comma(_parser, &_t);
				_MATCH(CONSTINT);
				b=(SORAST *)_t;
				_RIGHT;
				f77PutText(b->f77NodeText);  
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
		o_rp(_parser, &_t);
		if ( _t!=NULL && (_t->token==COMMA) ) {
			o_comma(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==DIV||_t->token==FUNCTION_NAME||
		_t->token==CONSTINT||_t->token==MIN||_t->token==INTEGER_ID||
		_t->token==REAL_ID||_t->token==INTEGER_ARRAY_ID||_t->token==UNARY_PLU||
		_t->token==UNARY_MIN||_t->token==PLU||_t->token==MUL||
		_t->token==HEX_CONST||_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "computed_goto", _t);
		}
		}
		o_integer_expr(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "computed_goto", _t);
	}
	*_root = _t;
}

void o_assigned_goto(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *i=NULL;
	SORAST *a=NULL;
	SORAST *b=NULL;
	if ( _t!=NULL && (_t->token==ASSIGNED_GOTO) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(ASSIGNED_GOTO);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==INTEGER_ID) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "assigned_goto", _t);
		}
		}
		f77PutText("GOTO ");  
		_MATCH(INTEGER_ID);
		i=(SORAST *)_t;
		_RIGHT;
		f77PutText(i->f77NodeText);  
		if ( _t!=NULL && (_t->token==COMMA||_t->token==LP) ) {
			if ( _t!=NULL && (_t->token==COMMA) ) {
				o_comma(_parser, &_t);
			}
			else {
			if ( _t!=NULL && (_t->token==LP) ) {
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "assigned_goto", _t);
			}
			}
			o_lp(_parser, &_t);
			_MATCH(CONSTINT);
			a=(SORAST *)_t;
			_RIGHT;
			f77PutText(a->f77NodeText);  
			{int _done=0;
			while ( !_done ) {
				if ( _t!=NULL && (_t->token==COMMA) ) {
					o_comma(_parser, &_t);
					_MATCH(CONSTINT);
					b=(SORAST *)_t;
					_RIGHT;
					f77PutText(b->f77NodeText);  
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
			o_rp(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "assigned_goto", _t);
	}
	*_root = _t;
}

void o_do_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *a=NULL;
	SORAST *b=NULL;
	if ( _t!=NULL && (_t->token==DO) ) {
		char buffer[100]; f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(DO);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
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
		a=(SORAST *)_t;
		_RIGHT;
		if ( _t!=NULL && (_t->token==COMMA) ) {
			o_comma(_parser, &_t);
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
		b=(SORAST *)_t;
		_RIGHT;
		_MATCH(EQUAL);
		_RIGHT;
		
		sprintf(buffer, "DO %s %s = ",a->f77NodeText,b->f77NodeText);
		f77PutText(buffer);
		o_integer_expr(_parser, &_t);
		o_comma(_parser, &_t);
		o_integer_expr(_parser, &_t);
		if ( _t!=NULL && (_t->token==COMMA) ) {
			o_comma(_parser, &_t);
			o_integer_expr(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "do_statement", _t);
	}
	*_root = _t;
}

void o_change_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==CHANGE) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(CHANGE);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t==NULL || (_t!=NULL) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "change_statement", _t);
		}
		}
		f77PutText("CHANGE");  
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL ) {
				o_any_token(_parser, &_t);
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
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "change_statement", _t);
	}
	*_root = _t;
}

void o_assign_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==ASSIGN) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(ASSIGN);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==CONSTINT) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "assign_statement", _t);
		}
		}
		f77PutText("ASSIGN ");  
		o_const_int(_parser, &_t);
		_MATCH(TO);
		_RIGHT;
		f77PutText("TO ");  
		o_identifier(_parser, &_t);
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

void o_format_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==FORMAT) ) {
		f77NewLine(Indentation);  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(FORMAT);
		_DOWN;
		if ( _t!=NULL && (_t->token==LABEL) ) {
			o_label(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "format_statement", _t);
		}
		}
		f77PutText("FORMAT");  
		o_lp(_parser, &_t);
		o_format_spec(_parser, &_t);
		o_rp(_parser, &_t);
		_RESTORE;
		}
		_RIGHT;
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "format_statement", _t);
	}
	*_root = _t;
}

void o_format_spec(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==CONSTINT||_t->token==HOLLERITH_CONST||
	_t->token==COLUMN||_t->token==SLASH||_t->token==TR||
	_t->token==TL||_t->token==T||_t->token==X||
	_t->token==SS||_t->token==P||_t->token==BZ||
	_t->token==BN||_t->token==J||_t->token==E||
	_t->token==G||_t->token==L||_t->token==Z||
	_t->token==U||_t->token==S||_t->token==I||
	_t->token==F||_t->token==D||_t->token==O||
	_t->token==A||_t->token==SP||_t->token==LP||
	_t->token==QUOTED_STRING) ) {
		o_format_item(_parser, &_t);
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->token==CONSTINT||_t->token==HOLLERITH_CONST||
			_t->token==COLUMN||_t->token==SLASH||_t->token==TR||
			_t->token==TL||_t->token==T||_t->token==X||
			_t->token==SS||_t->token==P||_t->token==BZ||
			_t->token==BN||_t->token==J||_t->token==E||
			_t->token==G||_t->token==L||_t->token==Z||
			_t->token==U||_t->token==S||_t->token==I||
			_t->token==F||_t->token==D||_t->token==O||
			_t->token==A||_t->token==SP||_t->token==LP||
			_t->token==QUOTED_STRING) ) {
				f77PutText(",");  
				o_format_item(_parser, &_t);
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

void o_format_item(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==CONSTINT||_t->token==LP) ) {
		if ( _t!=NULL && (_t->token==CONSTINT) ) {
			o_const_int(_parser, &_t);
		}
		else {
		if ( _t!=NULL && (_t->token==LP) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "format_item", _t);
		}
		}
		o_lp(_parser, &_t);
		o_format_spec(_parser, &_t);
		o_rp(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==HOLLERITH_CONST) ) {
		o_hollerith_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==QUOTED_STRING) ) {
		o_quote_editinig(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==TR) ) {
		o_tr_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==TL) ) {
		o_tl_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==T) ) {
		o_t_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==X) ) {
		o_x_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==COLUMN) ) {
		o_colon_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==SS) ) {
		o_ss_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==S) ) {
		o_s_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==P) ) {
		o_p_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==BN) ) {
		o_bn_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==BZ) ) {
		o_bz_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==I) ) {
		o_i_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==J) ) {
		o_j_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==F) ) {
		o_f_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==E) ) {
		o_e_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==D) ) {
		o_d_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==G) ) {
		o_g_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==O) ) {
		o_o_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==L) ) {
		o_l_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==A) ) {
		o_a_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==Z) ) {
		o_z_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==SP) ) {
		o_sp_editing(_parser, &_t);
	}
	else {
	if ( _t!=NULL && (_t->token==SLASH) ) {
		_MATCH(SLASH);
		_RIGHT;
		f77PutText("/");  
	}
	else {
	if ( _t!=NULL && (_t->token==U) ) {
		o_u_editing(_parser, &_t);
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

void o_hollerith_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *h=NULL;
	if ( _t!=NULL && (_t->token==HOLLERITH_CONST) ) {
		char buffer[100];  
		_MATCH(HOLLERITH_CONST);
		h=(SORAST *)_t;
		_RIGHT;
		
		sprintf(buffer, "%dH%s", strlen(h->f77NodeText),h->f77NodeText);
		f77PutText(buffer);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "hollerith_editing", _t);
	}
	*_root = _t;
}

void o_quote_editinig(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==QUOTED_STRING) ) {
		o_quoted_string(_parser, &_t);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "quote_editinig", _t);
	}
	*_root = _t;
}

void o_tr_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *c=NULL;
	if ( _t!=NULL && (_t->token==TR) ) {
		char buffer[100];  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TR);
		_DOWN;
		_MATCH(CONSTINT);
		c=(SORAST *)_t;
		_RIGHT;
		
		sprintf(buffer, "TR%s", c->f77NodeText);
		f77PutText(buffer);
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

void o_tl_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *c=NULL;
	if ( _t!=NULL && (_t->token==TL) ) {
		char buffer[100];  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TL);
		_DOWN;
		_MATCH(CONSTINT);
		c=(SORAST *)_t;
		_RIGHT;
		
		sprintf(buffer, "TL%s", c->f77NodeText);
		f77PutText(buffer);
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

void o_t_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *c=NULL;
	if ( _t!=NULL && (_t->token==T) ) {
		char buffer[100];  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(T);
		_DOWN;
		_MATCH(CONSTINT);
		c=(SORAST *)_t;
		_RIGHT;
		
		sprintf(buffer, "T%s", c->f77NodeText);
		f77PutText(buffer);
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

void o_x_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==X) ) {
		char buffer[100]; buffer[0] = '\0';  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(X);
		_DOWN;
		if ( _t!=NULL && (_t->token==REPEAT_COUNT) ) {
			o_repeat_count(_parser, &_t,  buffer );
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "x_editing", _t);
		}
		}
		
		strcat(buffer, "X");
		f77PutText(buffer);
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

void o_ss_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==SS) ) {
		_MATCH(SS);
		_RIGHT;
		f77PutText("SS");  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "ss_editing", _t);
	}
	*_root = _t;
}

void o_p_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *s=NULL;
	if ( _t!=NULL && (_t->token==P) ) {
		char buffer[100]; buffer[0] = '\0';  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(P);
		_DOWN;
		if ( _t!=NULL && (_t->token==SCALE_FACTOR) ) {
			_MATCH(SCALE_FACTOR);
			s=(SORAST *)_t;
			_RIGHT;
			strcpy(buffer, s->f77NodeText);  
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "p_editing", _t);
		}
		}
		
		strcat(buffer, "P");
		f77PutText(buffer);
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

void o_bz_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==BZ) ) {
		_MATCH(BZ);
		_RIGHT;
		f77PutText("BZ");  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "bz_editing", _t);
	}
	*_root = _t;
}

void o_bn_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==BN) ) {
		_MATCH(BN);
		_RIGHT;
		f77PutText("BN");  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "bn_editing", _t);
	}
	*_root = _t;
}

void o_j_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==J) ) {
		char buffer[100];  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(J);
		_DOWN;
		strcpy(buffer, "J");  
		o_field_width(_parser, &_t,  buffer );
		_RESTORE;
		}
		_RIGHT;
		f77PutText(buffer);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "j_editing", _t);
	}
	*_root = _t;
}

void o_e_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==E) ) {
		char buffer[100]; buffer[0] = '\0';  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(E);
		_DOWN;
		if ( _t!=NULL && (_t->token==REPEAT_COUNT) ) {
			o_repeat_count(_parser, &_t,  buffer );
		}
		else {
		if ( _t!=NULL && (_t->token==FIELD_WIDTH) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "e_editing", _t);
		}
		}
		strcat(buffer, "E");  
		o_field_width(_parser, &_t,  buffer );
		_MATCH(DEC_POINT);
		_RIGHT;
		strcat(buffer, ".");  
		o_decimal_places(_parser, &_t,  buffer );
		if ( _t!=NULL && (_t->token==E) ) {
			_MATCH(E);
			_RIGHT;
			strcat(buffer, "E");  
			o_exponent_digits(_parser, &_t,  buffer );
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
		f77PutText(buffer);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "e_editing", _t);
	}
	*_root = _t;
}

void o_g_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==G) ) {
		char buffer[100]; buffer[0] = '\0';  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(G);
		_DOWN;
		if ( _t!=NULL && (_t->token==REPEAT_COUNT) ) {
			o_repeat_count(_parser, &_t,  buffer );
		}
		else {
		if ( _t!=NULL && (_t->token==FIELD_WIDTH) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "g_editing", _t);
		}
		}
		strcat(buffer, "G");  
		o_field_width(_parser, &_t,  buffer );
		_MATCH(DEC_POINT);
		_RIGHT;
		strcat(buffer, ".");  
		o_decimal_places(_parser, &_t,  buffer );
		if ( _t!=NULL && (_t->token==G) ) {
			_MATCH(G);
			_RIGHT;
			strcat(buffer, "G");  
			o_exponent_digits(_parser, &_t,  buffer );
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
		f77PutText(buffer);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "g_editing", _t);
	}
	*_root = _t;
}

void o_l_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==L) ) {
		char buffer[100]; buffer[0] = '\0';  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(L);
		_DOWN;
		if ( _t!=NULL && (_t->token==REPEAT_COUNT) ) {
			o_repeat_count(_parser, &_t,  buffer );
		}
		else {
		if ( _t!=NULL && (_t->token==FIELD_WIDTH) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "l_editing", _t);
		}
		}
		strcat(buffer, "L");  
		o_field_width(_parser, &_t,  buffer );
		_RESTORE;
		}
		_RIGHT;
		f77PutText(buffer);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "l_editing", _t);
	}
	*_root = _t;
}

void o_z_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==Z) ) {
		char buffer[100]; buffer[0] = '\0';  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(Z);
		_DOWN;
		strcpy(buffer, "Z");  
		o_field_width(_parser, &_t,  buffer );
		_RESTORE;
		}
		_RIGHT;
		f77PutText(buffer);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "z_editing", _t);
	}
	*_root = _t;
}

void o_u_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==U) ) {
		char buffer[100]; buffer[0] = '\0';  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(U);
		_DOWN;
		strcpy(buffer, "U");  
		if ( _t!=NULL && (_t->token==FIELD_WIDTH) ) {
			o_field_width(_parser, &_t,  buffer );
			if ( _t!=NULL && (_t->token==COMMA) ) {
				_MATCH(COMMA);
				_RIGHT;
				strcat(buffer, ",");  
				o_decimal_places(_parser, &_t,  buffer );
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
		f77PutText(buffer);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "u_editing", _t);
	}
	*_root = _t;
}

void o_colon_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==COLUMN) ) {
		_MATCH(COLUMN);
		_RIGHT;
		f77PutText(":");  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "colon_editing", _t);
	}
	*_root = _t;
}

void o_s_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==S) ) {
		_MATCH(S);
		_RIGHT;
		f77PutText("S");  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "s_editing", _t);
	}
	*_root = _t;
}

void o_i_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==I) ) {
		char buffer[100]; buffer[0] = '\0';  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(I);
		_DOWN;
		if ( _t!=NULL && (_t->token==REPEAT_COUNT) ) {
			o_repeat_count(_parser, &_t,  buffer );
		}
		else {
		if ( _t!=NULL && (_t->token==FIELD_WIDTH) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "i_editing", _t);
		}
		}
		strcat(buffer, "I");  
		o_field_width(_parser, &_t,  buffer );
		if ( _t!=NULL && (_t->token==DEC_POINT) ) {
			_MATCH(DEC_POINT);
			_RIGHT;
			strcat(buffer,".");  
			o_min_dig_required(_parser, &_t,  buffer );
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
		f77PutText(buffer);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "i_editing", _t);
	}
	*_root = _t;
}

void o_f_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==F) ) {
		char buffer[100]; buffer[0] = '\0';  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(F);
		_DOWN;
		if ( _t!=NULL && (_t->token==REPEAT_COUNT) ) {
			o_repeat_count(_parser, &_t,  buffer );
		}
		else {
		if ( _t!=NULL && (_t->token==FIELD_WIDTH) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "f_editing", _t);
		}
		}
		strcat(buffer, "F");  
		o_field_width(_parser, &_t,  buffer );
		_MATCH(DEC_POINT);
		_RIGHT;
		strcat(buffer,".");  
		o_decimal_places(_parser, &_t,  buffer );
		_RESTORE;
		}
		_RIGHT;
		f77PutText(buffer);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "f_editing", _t);
	}
	*_root = _t;
}

void o_d_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==D) ) {
		char buffer[100]; buffer[0] = '\0';  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(D);
		_DOWN;
		if ( _t!=NULL && (_t->token==REPEAT_COUNT) ) {
			o_repeat_count(_parser, &_t,  buffer );
		}
		else {
		if ( _t!=NULL && (_t->token==FIELD_WIDTH) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "d_editing", _t);
		}
		}
		strcat(buffer, "D");  
		o_field_width(_parser, &_t,  buffer );
		_MATCH(DEC_POINT);
		_RIGHT;
		strcat(buffer,".");  
		o_decimal_places(_parser, &_t,  buffer );
		_RESTORE;
		}
		_RIGHT;
		f77PutText(buffer);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "d_editing", _t);
	}
	*_root = _t;
}

void o_o_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==O) ) {
		char buffer[100]; buffer[0] = '\0';  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(O);
		_DOWN;
		strcpy(buffer, "O");  
		o_field_width(_parser, &_t,  buffer );
		_RESTORE;
		}
		_RIGHT;
		f77PutText(buffer);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "o_editing", _t);
	}
	*_root = _t;
}

void o_a_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==A) ) {
		char buffer[100]; buffer[0] = '\0';  
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(A);
		_DOWN;
		if ( _t!=NULL && (_t->token==REPEAT_COUNT) ) {
			o_repeat_count(_parser, &_t,  buffer );
		}
		else {
		if ( _t!=NULL && (_t->token==FIELD_WIDTH) ) {
		}
		else {
			if ( _parser->guessing ) _GUESS_FAIL;
			no_viable_alt(_parser, "a_editing", _t);
		}
		}
		strcat(buffer,"A");  
		o_field_width(_parser, &_t,  buffer );
		_RESTORE;
		}
		_RIGHT;
		f77PutText(buffer);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "a_editing", _t);
	}
	*_root = _t;
}

void o_sp_editing(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==SP) ) {
		_MATCH(SP);
		_RIGHT;
		f77PutText("SP");  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "sp_editing", _t);
	}
	*_root = _t;
}

void o_repeat_count(STreeParser *_parser, SORAST **_root, char *buffer )
{
	SORAST *_t = *_root;
	SORAST *r=NULL;
	if ( _t!=NULL && (_t->token==REPEAT_COUNT) ) {
		_MATCH(REPEAT_COUNT);
		r=(SORAST *)_t;
		_RIGHT;
		
		strcpy(buffer, r->f77NodeText);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "repeat_count", _t);
	}
	*_root = _t;
}

void o_field_width(STreeParser *_parser, SORAST **_root, char *buffer )
{
	SORAST *_t = *_root;
	SORAST *f=NULL;
	if ( _t!=NULL && (_t->token==FIELD_WIDTH) ) {
		_MATCH(FIELD_WIDTH);
		f=(SORAST *)_t;
		_RIGHT;
		strcat(buffer, f->f77NodeText);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "field_width", _t);
	}
	*_root = _t;
}

void o_decimal_places(STreeParser *_parser, SORAST **_root, char *buffer )
{
	SORAST *_t = *_root;
	SORAST *d=NULL;
	if ( _t!=NULL && (_t->token==DECIMAL_PLACES) ) {
		_MATCH(DECIMAL_PLACES);
		d=(SORAST *)_t;
		_RIGHT;
		strcat(buffer, d->f77NodeText);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "decimal_places", _t);
	}
	*_root = _t;
}

void o_exponent_digits(STreeParser *_parser, SORAST **_root, char *buffer )
{
	SORAST *_t = *_root;
	SORAST *e=NULL;
	if ( _t!=NULL && (_t->token==EXPONENT_DIGITS) ) {
		_MATCH(EXPONENT_DIGITS);
		e=(SORAST *)_t;
		_RIGHT;
		strcat(buffer, e->f77NodeText);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "exponent_digits", _t);
	}
	*_root = _t;
}

void o_min_dig_required(STreeParser *_parser, SORAST **_root, char *buffer )
{
	SORAST *_t = *_root;
	SORAST *m=NULL;
	if ( _t!=NULL && (_t->token==MIN_DIG_REQUIRED) ) {
		_MATCH(MIN_DIG_REQUIRED);
		m=(SORAST *)_t;
		_RIGHT;
		strcat(buffer, m->f77NodeText);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "min_dig_required", _t);
	}
	*_root = _t;
}

void o_label(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *l=NULL;
	if ( _t!=NULL && (_t->token==LABEL) ) {
		_MATCH(LABEL);
		l=(SORAST *)_t;
		_RIGHT;
		f77PutLabel( l->f77NodeText);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "label", _t);
	}
	*_root = _t;
}

void o_comma(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==COMMA) ) {
		_MATCH(COMMA);
		_RIGHT;
		f77PutText(",");  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "comma", _t);
	}
	*_root = _t;
}

void o_lp(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==LP) ) {
		_MATCH(LP);
		_RIGHT;
		f77PutText("(");  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "lp", _t);
	}
	*_root = _t;
}

void o_rp(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==RP) ) {
		_MATCH(RP);
		_RIGHT;
		f77PutText(")");  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "rp", _t);
	}
	*_root = _t;
}

void o_equal(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	if ( _t!=NULL && (_t->token==EQUAL) ) {
		_MATCH(EQUAL);
		_RIGHT;
		f77PutText("=");  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "equal", _t);
	}
	*_root = _t;
}

void o_const_int(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *c=NULL;
	if ( _t!=NULL && (_t->token==CONSTINT) ) {
		_MATCH(CONSTINT);
		c=(SORAST *)_t;
		_RIGHT;
		f77PutText(c->f77NodeText);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "const_int", _t);
	}
	*_root = _t;
}

void o_identifier(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *i=NULL;
	if ( _t!=NULL && (_t->token==IDENTIFIER) ) {
		_MATCH(IDENTIFIER);
		i=(SORAST *)_t;
		_RIGHT;
		f77PutText(i->f77NodeText);  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "identifier", _t);
	}
	*_root = _t;
}

void o_quoted_string(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *q=NULL;
	if ( _t!=NULL && (_t->token==QUOTED_STRING) ) {
		char buffer[100];  
		_MATCH(QUOTED_STRING);
		q=(SORAST *)_t;
		_RIGHT;
		
		sprintf(buffer, "\'%s\'", q->f77NodeText);
		f77PutText(buffer);
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "quoted_string", _t);
	}
	*_root = _t;
}

void o_any_token(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *t=NULL;
	if ( _t!=NULL ) {
		char buffer[100];  
		_WILDCARD;
		t=(SORAST *)_t;
		_RIGHT;
		
		switch(t->token) {
			case QUOTED_STRING:
			sprintf(buffer, "\'%s\'", t->f77NodeText);
			f77PutText(buffer);
			break;
			case HOLLERITH_CONST:
			sprintf(buffer, "%dH%s", strlen(t->f77NodeText), t->f77NodeText);
			f77PutText(buffer);
			break;
			default:
			f77PutText(t->f77NodeText);
			break;
		}
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "any_token", _t);
	}
	*_root = _t;
}

void o_any_statement(STreeParser *_parser, SORAST **_root)
{
	SORAST *_t = *_root;
	SORAST *t=NULL;
	if ( _t!=NULL ) {
		f77NewLine(Indentation);  
		{int _done=0;
		do {
			if ( _t!=NULL ) {
				_WILDCARD;
				t=(SORAST *)_t;
				_RIGHT;
				f77PutText(t->f77NodeText);  
				o_any_token(_parser, &_t);
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( _parser->guessing ) _GUESS_FAIL;
				no_viable_alt(_parser, "any_statement", _t);
			}
			}
		} while ( !_done );
		}
		f77PrintLine();  
	}
	else {
		if ( _parser->guessing ) _GUESS_FAIL;
		no_viable_alt(_parser, "any_statement", _t);
	}
	*_root = _t;
}
