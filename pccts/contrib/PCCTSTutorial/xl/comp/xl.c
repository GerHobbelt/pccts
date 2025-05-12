/*
 * A n t l r  T r a n s l a t i o n  H e a d e r
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-1994
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.20
 */
#include <stdio.h>
#define ANTLR_VERSION	120
#include "xl.pccts.h"   
#define GENAST

#include "ast.h"

#define zzEOF_TOKEN 1
#define zzSET_SIZE 16
#include "antlr.h"
#include "tokens.h"
#include "dlgdef.h"
#include "mode.h"
#include "ast.c"
zzASTgvars

ANTLR_INFO

// define symbol table size
#define HashTableSize    999
#define StringTableSize 5000

   // define the global scope for the symbol table
static Sym *globals = NULL;

   // initialize flags in the program
int indent,level,walk_indent =0;
int walk_tree       = 0;
int show_definition = 0;
int list_variables  = 0;
int trace           = 0;
int error_occurred  = 0;
int loop_count      = 0;

   // define pointers in the AST to represent the types
AST *integer_type, *string_type, *boolean_type, *undefined_type;

   // define pointers in the AST to represent TRUE and FALSE
AST *def_true, *def_false;

   // the name of the object file
char *file_name;

   // change the way AST nodes are referred to, for readability
#define AST_Tok(token)                    zzmk_ast(zzastnew(),token, NULL)
#define AST_Node(token, str)              zzmk_ast(zzastnew(),token, str)
#define AST_List1(root, c1)               zztmake(root, c1, NULL)
#define AST_List2(root, c1, c2)           zztmake(root, c1, c2, NULL)
#define AST_List3(root, c1, c2, c3)       zztmake(root, c1, c2, c3, NULL)

   #include "xl.support.c"    // include support routines
#include "xl.ast_defs.h"   // include AST definitions

// routine to initialize compiler types and constants in the AST
AST *init_tree()   
{
	AST *def;
	
   // Define Built-in atype tree nodes
	integer_type = AST_Type("Integer");
	SizeOf(integer_type) = 1;
	string_type  = AST_Type("String");
	boolean_type = AST_Type("Boolean");
	SizeOf(boolean_type) = 1;
	undefined_type = AST_Type("<<**Undefined**>>");
	
   // Make AST nodes for TRUE and FALSE
	def_true           = AST_Constant("TRUE");
	TypeOf(def_true)   = boolean_type;
	DispOf(def_true)   = 0;
	LevelOf(def_true)  = 1;
	SizeOf(def_true)   = 1;
	Init(def_true)     = AST_IntLiteral("1");
	TypeOf(Init(def_true)) = boolean_type;
	def_false          = AST_Constant("FALSE");
	TypeOf(def_false)  = boolean_type;
	DispOf(def_false)  = 1;
	LevelOf(def_false) = 1;
	SizeOf(def_false)  = 1;
	Init(def_false)    = AST_IntLiteral("0");
	TypeOf(Init(def_false)) = boolean_type;
	
   // Create a tree (list) of all external defs so far
	def   =  zztmake(AST_All_Are_Siblings,
	AST_Define(integer_type),
	AST_Define(string_type),
	AST_Define(boolean_type),
	AST_Define(def_true),
	AST_Define(def_false), NULL);
	
   return(def);         
}                      

  

void
#ifdef __STDC__
program(AST **_root)
#else
program(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	
	// Initialize the compiler here
	Sym *p;                  // temporary, used when adding things to symbol table
	AST *extdefs,            // external definitions, used just by compiler
	*tree;               // the overall AST for the user's program
	int size;                // keeps track of global variable space
	
                                       indent = level = 0;      // base level, no indenting so far...
	
                                       extdefs = init_tree();   // initialize the tree
	
                                       zzs_scope(&globals);     // set up the global-level scope
	
                                       // add TRUE and FALSE to the symbol table
	define_symbol(p, "TRUE",     0, CONST, def_true);
	define_symbol(p, "FALSE",    0, CONST, def_false);
	zzTRACEIN((ANTLRChar *)"program");
	zzmatch(51); zzastDPush; zzCONSUME;
	_ast = NULL; def(&_ast, &globals,0,PROC );
	zzmatch(52); zzastDPush; zzCONSUME;
	_ast = NULL; subprogrambody(&_ast, &globals,1,zzaArg(zztasp1,2 ).text,NULL );
	zzmatch(53); zzastDPush;
	
	// create a Program AST node -- make its size be the size of the subprogram 
	//   (that was set to the size of all global vars)
	size = SizeOf(zzastArg(4));
	tree = AST_Program(AST_Name(zzaArg(zztasp1,2 ).text), AST_Body(zzastArg(4)));
	SizeOf(tree) = size;
	
                                       tree =   AST_File(extdefs, tree);  // Make the overall File node in the tree
	
                                       // If user requested a tree walk, walk the AST
	if (walk_tree)
	{
		walk(tree);
		printf("\n\n");
	}                                        
	p = zzs_rmscope(&globals);  // Remove the global variable scope
	
                                       // If user requested that we list all vars after a proc def, list globals
	if (list_variables)
	{
		printf("Globals:\n");
		if (p != NULL) pScope(p);
	}                                       
	// if everything parsed fine, generate code
	if (!error_occurred)
	generate_code(tree);
 zzCONSUME;
	zzmatch(1); zzastDPush; zzCONSUME;
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"program");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "program definition", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd1, 0x1);
	zzTRACEOUT((ANTLRChar *)"program");
	}
}

void
#ifdef __STDC__
subprogrambody(AST **_root, Sym **locals,
               int   level, 
               char *name,
               AST *type )
#else
subprogrambody(_root,locals,level,name,type)
AST **_root;
 Sym **locals;
int   level;
char *name;
AST *type ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	int size=0;   
	zzTRACEIN((ANTLRChar *)"subprogrambody");
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (setwd1[LA(1)]&0x2) ) {
			basicdecl(zzSTR,  locals,  level ); zzlink(_root, &_sibling, &_tail);
			size += SizeOf(zzastArg(1));   
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (LA(1)==69) ) {
			proceduredecl(zzSTR,  locals,  level ); zzlink(_root, &_sibling, &_tail);
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzmatch(54);  zzCONSUME;
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (setwd1[LA(1)]&0x4) ) {
			statement(zzSTR); zzlink(_root, &_sibling, &_tail);
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzmatch(55);  zzCONSUME;
	_ast = NULL; refproc(&_ast);
	
	// compare the name on the "end" statement to the name that the 
	//    program/procedure was declared under
	if (strcmp(name,zzaArg(zztasp1,6 ).text) != 0) 
	{
		syntax_error(zzline, zzaArg(zztasp1,6 ).text, "name referenced after end does not match subprogram declaration");
		printf("\tSubprogram was declared with name %s\n",  name);
	}                                       // set the size of the subprog definition to be the sum of the variable sizes
	SizeOf((*_root)) = size;  
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"subprogrambody");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "subprogram definition", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd1, 0x8);
	zzTRACEOUT((ANTLRChar *)"subprogrambody");
	}
}

void
#ifdef __STDC__
basicdecl(AST **_root, Sym **locals,
          int    level )
#else
basicdecl(_root,locals,level)
AST **_root;
 Sym **locals;
int    level ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"basicdecl");
	if ( (LA(1)==56) ) {
		vardecl(zzSTR,  locals,  level ); zzlink(_root, &_sibling, &_tail);
	}
	else {
		if ( (LA(1)==60) ) {
			constdecl(zzSTR,  locals,  level ); zzlink(_root, &_sibling, &_tail);
		}
		else {
			if ( (LA(1)==62) ) {
				typedecl(zzSTR,  locals,  level ); zzlink(_root, &_sibling, &_tail);
			}
			else {zzFAIL(1,zzerr1,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
		}
	}
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"basicdecl");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd1, 0x10);
	zzTRACEOUT((ANTLRChar *)"basicdecl");
	}
}

void
#ifdef __STDC__
vardecl(AST **_root, Sym **locals,                                 
         int   level )
#else
vardecl(_root,locals,level)
AST **_root;
 Sym **locals;
int   level ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	
	AST *t, *ivalue=NULL;    // Used to assign type and init values to variables
	int size = 0;            // Used to track total size of identifier list
	zzTRACEIN((ANTLRChar *)"vardecl");
	zzmatch(56); zzastDPush; zzCONSUME;
	_ast = NULL; identifierlist(&_ast,  locals, level,VAR );
	zzmatch(57); zzastDPush; zzCONSUME;
	_ast = NULL; typename(&_ast);
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==58) ) {
			zzmatch(58); zzastDPush; zzCONSUME;
			_ast = NULL; constantvalue(&_ast);
			ivalue = find_val(zzastArg(2));   
		}
		zzEXIT(zztasp2);
		}
	}
	zzmatch(59); zzastDPush;
	
	// If there is an initializer, check that the variables' type is scalar
	if (ivalue)
	{
	if (zzastArg(4) != integer_type && zzastArg(4) != boolean_type)
	{
	syntax_error(zzline, ":=", "only scalar variables can be initialized");
	printf("\tVariables were defined as type %s\n", NameOf(zzastArg(4)));
}

                                          // Now check if the type of the initializer matches the type of the vars
if (TypeOf(ivalue) != zzastArg(4))                                    
{
syntax_error(zzline, NameOf(ivalue), "type conflict in attempted initialization");
printf("\tType of variables being declared: %s", NameOf(zzastArg(4)));
printf("\n\tType of initializer: %s\n", TypeNameOf(ivalue));
}                                       }

                                       // Assign the type and initial value (if present) to all variables in the list
for(t=zzastArg(2); t!=NULL; t=zzsibling(t))       // for each var in the list
{
TypeOf(zzchild(t)) = zzastArg(4);              //      set its type
Init(zzchild(t)) = ivalue;            //      set its initial value
SizeOf(zzchild(t)) = SizeOf(zzastArg(4));      //      set its size
size += SizeOf(zzastArg(4));                   //      add its size to the total
}                                       (*_root) = zzastArg(2);                                 // we'll return the list
SizeOf((*_root)) = size;                       // set its total size
 zzCONSUME;
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"vardecl");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "variable declaration", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd1, 0x20);
	zzTRACEOUT((ANTLRChar *)"vardecl");
	}
}

void
#ifdef __STDC__
constdecl(AST **_root, Sym **locals,
           int level )
#else
constdecl(_root,locals,level)
AST **_root;
 Sym **locals;
int level ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	
	AST *t; int size=0; 
	zzTRACEIN((ANTLRChar *)"constdecl");
	zzmatch(60); zzastDPush; zzCONSUME;
	_ast = NULL; identifierlist(&_ast,  locals, level,CONST );
	zzmatch(57); zzastDPush; zzCONSUME;
	_ast = NULL; typename(&_ast);
	zzmatch(58); zzastDPush; zzCONSUME;
	_ast = NULL; constantvalue(&_ast);
	zzmatch(59); zzastDPush;
	
	// Check that the constants' type is scalar
	if (zzastArg(4) != integer_type && zzastArg(4) != boolean_type)
	{
	syntax_error(zzline, NameOf(zzastArg(4)), "constants must be scalar");
	printf("\tConstants were initialized as type %s\n", NameOf(zzastArg(6)));
}                                       
// check that the type of the initializer matches the type of the constants
if (TypeOf(zzastArg(6)) != zzastArg(4))                                    
{
syntax_error(zzline, NameOf(zzastArg(6)), "type conflict in attempted initialization");
printf("\tType of variables being declared: %s", NameOf(zzastArg(4)));
printf("\n\tType of initializer: %s\n", TypeNameOf(zzastArg(6)));
}                                       
// Assign the type and initializer to all constants
for(t=zzastArg(2); t!=NULL; t=zzsibling(t))       // for each constant in the list
{
TypeOf(zzchild(t)) = zzastArg(4);              //      set its type
Init(zzchild(t)) = find_val(zzastArg(6));      //      find its value
SizeOf(zzchild(t)) = SizeOf(zzastArg(4));      //      set its size
size += SizeOf(zzastArg(4));                   //      add its size to the total
}                                       (*_root) = zzastArg(2);                                 // return the list
SizeOf((*_root)) = size;                       // set the list's total size
 zzCONSUME;
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"constdecl");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "constant declaration", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd1, 0x40);
	zzTRACEOUT((ANTLRChar *)"constdecl");
	}
}

void
#ifdef __STDC__
constantvalue(AST **_root)
#else
constantvalue(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"constantvalue");
	if ( (LA(1)==INTLIT) ) {
		zzmatch(INTLIT); zzastDPush;
		
		// An integer literal == make a node for it
		(*_root) = AST_IntLiteral(zzaArg(zztasp1,1 ).text);    TypeOf((*_root))=integer_type;   SizeOf((*_root)) = 1; 
		zzaArg(zztasp1,0)=zzaArg(zztasp1,1); 
 zzCONSUME;
	}
	else {
		if ( (LA(1)==STRINGLIT) ) {
			zzmatch(STRINGLIT); zzastDPush;
			
			// A string literal -- make a node for it
			(*_root) = AST_StringLiteral(zzaArg(zztasp1,1 ).text);    TypeOf((*_root))=string_type;   SizeOf((*_root)) = strlen(zzaArg(zztasp1,1 ).text); 
			zzaArg(zztasp1,0)=zzaArg(zztasp1,1); 
 zzCONSUME;
		}
		else {
			if ( (LA(1)==CONST) ) {
				_ast = NULL; constant(&_ast);
				
				// a constant -- it's already got a node -- just return it
				(*_root) = zzastArg(1); 
			}
			else {zzFAIL(1,zzerr2,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
		}
	}
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"constantvalue");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd1, 0x80);
	zzTRACEOUT((ANTLRChar *)"constantvalue");
	}
}

void
#ifdef __STDC__
identifierlist(AST **_root, Sym **locals,
                int    level,
                int    token )
#else
identifierlist(_root,locals,level,token)
AST **_root;
 Sym **locals;
int    level;
int    token ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	AST *t; (*_root) = NULL;   
	zzTRACEIN((ANTLRChar *)"identifierlist");
	_ast = NULL; def(&_ast,  locals, level, token );
	
	if (zzastArg(1) != NULL)   // If this is a valid NEW definition
	{
		(*_root) =  AST_Define(zzastArg(1));         // set up a Define node for it
		SizeOf((*_root)) = SizeOf(zzastArg(1));      // Copy the size and type
		TypeOf((*_root)) = TypeOf(zzastArg(1));
	}                                      
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (LA(1)==61) ) {
			zzmatch(61); zzastDPush; zzCONSUME;
			_ast = NULL; def(&_ast,  locals, level, token );
			
			if (zzastArg(2) != NULL)                       // If it's a valid NEW ident
			{
			t = AST_Define(zzastArg(2));                // Set up a Define node for it
			SizeOf(t) = SizeOf(zzastArg(2));            // Copy the size and type
			TypeOf(t) = TypeOf(zzastArg(2));
			if ((*_root) != NULL)                    // Attach it to the list so far...
			AST_Make_Siblings((*_root), t);
			else
			(*_root) = t;
		}                                         
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"identifierlist");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "identifier list", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd2, 0x1);
	zzTRACEOUT((ANTLRChar *)"identifierlist");
	}
}

void
#ifdef __STDC__
typedecl(AST **_root, Sym **locals,
          int    level )
#else
typedecl(_root,locals,level)
AST **_root;
 Sym **locals;
int    level ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	Sym *p;   
	zzTRACEIN((ANTLRChar *)"typedecl");
	zzmatch(62); zzastDPush; zzCONSUME;
	_ast = NULL; def(&_ast,  locals, level,TYPE );
	zzmatch(52); zzastDPush; zzCONSUME;
	_ast = NULL; typedefn(&_ast,  locals, level );
	zzmatch(59); zzastDPush;
	
	// If the declaration was a NEW one
	if (zzastArg(2))
	{
		p = zzs_get(zzaArg(zztasp1,2 ).text);                 // get its symbol table info
		TypeOf(p) = AST_List1(zzastArg(2), zzastArg(4));        // Attach a Type node to its sym tab info
		(*_root) = AST_Define(TypeOf(p));           // Create a Define node for it
		SizeOf(zzastArg(2)) = SizeOf(zzastArg(4));              // Copy the size and type
		TypeOf(zzastArg(2)) = TypeOf(zzastArg(4));
		SizeOf((*_root)) = 0;                     
	}                                       else
	(*_root) = NULL;
 zzCONSUME;
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"typedecl");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "type declaration", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd2, 0x2);
	zzTRACEOUT((ANTLRChar *)"typedecl");
	}
}

void
#ifdef __STDC__
typedefn(AST **_root, Sym **locals,
         int    level )
#else
typedefn(_root,locals,level)
AST **_root;
 Sym **locals;
int    level ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"typedefn");
	if ( (LA(1)==63) ) {
		recordtypedefn(zzSTR,  level ); zzlink(_root, &_sibling, &_tail);
	}
	else {
		if ( (LA(1)==64) ) {
			arraytypedefn(zzSTR,  locals, level ); zzlink(_root, &_sibling, &_tail);
		}
		else {zzFAIL(1,zzerr3,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"typedefn");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "type definition", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd2, 0x4);
	zzTRACEOUT((ANTLRChar *)"typedefn");
	}
}

void
#ifdef __STDC__
recordtypedefn(AST **_root, int level )
#else
recordtypedefn(_root,level)
AST **_root;
 int level ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	Sym *fields=NULL,*p; AST *t; int size=0; (*_root)=NULL;  
	zzTRACEIN((ANTLRChar *)"recordtypedefn");
	zzmatch(63); zzastDPush; zzCONSUME;
	{
		zzBLOCK(zztasp2);
		int zzcnt=1;
		zzMake0;
		{
		do {
			_ast = NULL; identifierlist(&_ast, &fields, level,VAR );
			zzmatch(57); zzastDPush; zzCONSUME;
			_ast = NULL; typename(&_ast);
			zzmatch(59); zzastDPush;
			
			// Assign the type and initial value to each field in the list
			for(t=zzastArg(1); t!=NULL; t=zzsibling(t))
			{
				TypeOf(zzchild(t)) = zzastArg(3);
				DispOf(zzchild(t)) = size;
				SizeOf(zzchild(t)) = SizeOf(zzastArg(3));
				size = size + SizeOf(zzastArg(3)); // keep running total of size for record
			}                                             if (!(*_root))           // If there is no list of fields yet
			(*_root) = zzastArg(1);        //      this list becomes the field list
			else               // otherwise, add this list to the field list
			AST_Make_Siblings((*_root), zzastArg(1));
 zzCONSUME;
			zzLOOP(zztasp2);
		} while ( (setwd2[LA(1)]&0x8) );
		zzEXIT(zztasp2);
		}
	}
	zzmatch(55); zzastDPush; zzCONSUME;
	zzmatch(63); zzastDPush;
	
	p = zzs_rmscope(&fields);        // remove the field scope
	if (list_variables)              // if user wants variable list, print field
	{
		printf("Fields for record\n");
		if (p != NULL) pScope(p);
	}                                       (*_root) = AST_Record((*_root));             // Create a new Record node from the list
	SizeOf((*_root)) = size;               // keep track of the record's total size
 zzCONSUME;
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"recordtypedefn");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "record type definition", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd2, 0x10);
	zzTRACEOUT((ANTLRChar *)"recordtypedefn");
	}
}

void
#ifdef __STDC__
arraytypedefn(AST **_root, Sym **locals,
               int    level )
#else
arraytypedefn(_root,locals,level)
AST **_root;
 Sym **locals;
int    level ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	AST *lower, *upper;  int upper_val, lower_val;   
	zzTRACEIN((ANTLRChar *)"arraytypedefn");
	zzmatch(64); zzastDPush; zzCONSUME;
	zzmatch(65); zzastDPush; zzCONSUME;
	_ast = NULL; integerconstant(&_ast,  locals, level );
	zzmatch(66); zzastDPush; zzCONSUME;
	_ast = NULL; integerconstant(&_ast,  locals, level );
	zzmatch(67); zzastDPush; zzCONSUME;
	zzmatch(68); zzastDPush; zzCONSUME;
	_ast = NULL; typename(&_ast);
	
	// Make sure that the lower and upprt bounds are integers
	if (TypeOf(zzastArg(3)) != integer_type)
	{
		syntax_error(zzline, NameOf(zzchild(zzastArg(3))), "array bounds must be of type Integer");
		printf("\tLower bound is of type %s\n", TypeNameOf(zzastArg(3)));
	}                                       if (TypeOf(zzastArg(5)) != integer_type)
	{
		syntax_error(zzline, NameOf(zzchild(zzastArg(5))), "array bounds must be of type Integer");
		printf("\tUpper bound is of type %s\n", TypeNameOf(zzastArg(5)));
	}                                       if (!error_occurred)
	{
		lower = find_val(zzastArg(3));                 // get the values of the bounds
		upper = find_val(zzastArg(5));
		lower_val = atoi(NameOf(lower));
		upper_val = atoi(NameOf(upper));
		if (lower_val > upper_val)            // make sure they are in the right order
		{
			syntax_error(zzline, NameOf(zzastArg(5)), "lower bound is higher than upper bound");
			printf("\tLower bound has value %d", lower_val);
			printf("\n\tUpper bound has value %d\n", upper_val);
		}                                       }
	(*_root) =  AST_Array(lower, upper);   // create a new array node in the AST
	TypeOf((*_root)) = zzastArg(8);                 // Set the type of the elements
	SizeOf((*_root)) = (upper_val - lower_val + 1) * SizeOf(zzastArg(8));   // Set overall array size
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"arraytypedefn");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "array type definition", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd2, 0x20);
	zzTRACEOUT((ANTLRChar *)"arraytypedefn");
	}
}

void
#ifdef __STDC__
integerconstant(AST **_root, Sym **locals,
                 int    level )
#else
integerconstant(_root,locals,level)
AST **_root;
 Sym **locals;
int    level ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"integerconstant");
	if ( (LA(1)==INTLIT) ) {
		zzmatch(INTLIT); zzastDPush;
		(*_root) = AST_IntLiteral(zzaArg(zztasp1,1 ).text); TypeOf((*_root)) = integer_type; SizeOf((*_root)) = 1; zzaArg(zztasp1,0)=zzaArg(zztasp1,1);  
 zzCONSUME;
	}
	else {
		if ( (setwd2[LA(1)]&0x40) ) {
			_ast = NULL; refconst(&_ast);
			(*_root) = zzastArg(1); zzaArg(zztasp1,0)=zzaArg(zztasp1,1);   
		}
		else {zzFAIL(1,zzerr4,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"integerconstant");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "integer constant reference", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd2, 0x80);
	zzTRACEOUT((ANTLRChar *)"integerconstant");
	}
}

void
#ifdef __STDC__
proceduredecl(AST **_root, Sym **locals,
               int    level )
#else
proceduredecl(_root,locals,level)
AST **_root;
 Sym **locals;
int    level ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	Sym *new_locals=NULL, *p, *s; AST *parms=NULL; (*_root)= NULL;   
	zzTRACEIN((ANTLRChar *)"proceduredecl");
	zzmatch(69); zzastDPush; zzCONSUME;
	_ast = NULL; def(&_ast,  locals, level,PROC );
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==70) ) {
			_ast = NULL; formalpart(&_ast, &new_locals, level+1 );
			parms = zzastArg(1);   
		}
		zzEXIT(zztasp2);
		}
	}
	zzmatch(52); zzastDPush;
	
	// Start an AST definition so recursive calls are possible
	//   (Statements will be added later as a sibling of the parameters)
	if (zzastArg(2))
	{
		p = zzs_get(zzaArg(zztasp1,2 ).text);         // Get symbol table record
		if (!parms)                   // if no parms, create a dummy parms record
		parms = AST_Parms(NULL);   
		
                                          // Create the new Procedure AST node
		TypeOf(p) = AST_StartProcedure(AST_Name(zzaArg(zztasp1,2 ).text), 
		parms);
		
                                          (*_root) = AST_Define(TypeOf(p));   // point the symbol table reference at the node
	}                                      
 zzCONSUME;
	_ast = NULL; subprogrambody(&_ast, &new_locals, level+1,zzaArg(zztasp1,2 ).text,NULL );
	zzmatch(59); zzastDPush;
	
	// Remove the scope for this procedure
	s = zzs_rmscope(&new_locals);
	
                                       // If user wants a variable list, give it to them
	if (list_variables)
	{
		printf("Locals for %s\n",zzaArg(zztasp1,2 ).text);
		if (s != NULL) pScope(s);
	}                                       
	// Set the size of the procedure's local variables and add statements after parms
	if ((*_root))  
	{
	SizeOf(TypeOf(p)) = SizeOf(zzastArg(5));
	AST_Make_Siblings(parms, AST_Body(zzastArg(5)));
}                                      
 zzCONSUME;
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"proceduredecl");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "procedure declaration", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd3, 0x1);
	zzTRACEOUT((ANTLRChar *)"proceduredecl");
	}
}

void
#ifdef __STDC__
formalpart(AST **_root, Sym **locals,
            int    level )
#else
formalpart(_root,locals,level)
AST **_root;
 Sym **locals;
int    level ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	AST *parms = NULL; int size = 0;  
	zzTRACEIN((ANTLRChar *)"formalpart");
	zzmatch(70); zzastDPush; zzCONSUME;
	_ast = NULL; parameterspec(&_ast,  locals, level );
	
	parms = zzastArg(2);           // make this parm spec the whole parm list so far
	size += SizeOf(zzastArg(2));   // keep track of total size
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (LA(1)==59) ) {
			zzmatch(59); zzastDPush; zzCONSUME;
			_ast = NULL; parameterspec(&_ast,  locals, level );
			
			AST_Make_Siblings(parms, zzastArg(2));      // add the new parms to the parm list
			size += SizeOf(zzastArg(2));                // keep track of total size
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzmatch(71); zzastDPush;
	
	(*_root) = AST_Parms(parms);   // Make a new parms node
	SizeOf((*_root)) = size;       // Copy the size
 zzCONSUME;
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"formalpart");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "formal parameter declaration", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd3, 0x2);
	zzTRACEOUT((ANTLRChar *)"formalpart");
	}
}

void
#ifdef __STDC__
parameterspec(AST **_root, Sym **locals,
               int    level )
#else
parameterspec(_root,locals,level)
AST **_root;
 Sym **locals;
int    level ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	int ref = 0;  AST *t;   
	zzTRACEIN((ANTLRChar *)"parameterspec");
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==56) ) {
			zzmatch(56); zzastDPush;
			ref = 1;   
 zzCONSUME;
		}
		zzEXIT(zztasp2);
		}
	}
	_ast = NULL; identifierlist(&_ast,  locals, level,VAR );
	zzmatch(57); zzastDPush; zzCONSUME;
	_ast = NULL; typename(&_ast);
	
	(*_root) = zzastArg(2);                                         // we'll return the whole list
	SizeOf((*_root)) = 0;                                  // start running size total
	// Assign the type and initial value
	for(t=zzastArg(2); t!=NULL; t=zzsibling(t))               // for each parm in the list
	{
	TypeOf(zzchild(t)) = zzastArg(4);                      //      add a type
	IsVarRef(zzchild(t))  = ref;                  //      set if "var" or not
	SizeOf(zzchild(t)) = SizeOf(zzastArg(4));              //      set its size
	SizeOf(zzastArg(2)) += SizeOf(zzastArg(4));                     //      keep running size total
}                                      
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"parameterspec");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "formal parameter specification", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd3, 0x4);
	zzTRACEOUT((ANTLRChar *)"parameterspec");
	}
}

void
#ifdef __STDC__
statement(AST **_root)
#else
statement(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"statement");
	if ( (setwd3[LA(1)]&0x8) ) {
		assignmentstmnt(zzSTR); zzlink(_root, &_sibling, &_tail);
	}
	else {
		if ( (LA(1)==76) ) {
			exitstmnt(zzSTR); zzlink(_root, &_sibling, &_tail);
		}
		else {
			if ( (LA(1)==PROC) ) {
				procedurecallstmnt(zzSTR); zzlink(_root, &_sibling, &_tail);
			}
			else {
				if ( (LA(1)==78) ) {
					returnstmnt(zzSTR); zzlink(_root, &_sibling, &_tail);
				}
				else {
					if ( (LA(1)==79) ) {
						ifstmnt(zzSTR); zzlink(_root, &_sibling, &_tail);
					}
					else {
						if ( (setwd3[LA(1)]&0x10) ) {
							loopstmnt(zzSTR); zzlink(_root, &_sibling, &_tail);
						}
						else {
							if ( (setwd3[LA(1)]&0x20) ) {
								iostatement(zzSTR); zzlink(_root, &_sibling, &_tail);
							}
							else {zzFAIL(1,zzerr5,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
						}
					}
				}
			}
		}
	}
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"statement");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "statement", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd3, 0x40);
	zzTRACEOUT((ANTLRChar *)"statement");
	}
}

void
#ifdef __STDC__
iostatement(AST **_root)
#else
iostatement(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	AST *ref;   
	zzTRACEIN((ANTLRChar *)"iostatement");
	if ( (LA(1)==72) ) {
		zzmatch(72); zzastDPush; zzCONSUME;
		zzmatch(70); zzastDPush; zzCONSUME;
		_ast = NULL; expression(&_ast);
		zzmatch(71); zzastDPush; zzCONSUME;
		zzmatch(59); zzastDPush;
		
		// Make sure we are putting either integers or strings
		if (TypeOf(zzastArg(3)) != integer_type && TypeOf(zzastArg(3)) != string_type)
		{
			syntax_error(zzline, ")", "cannot perform put on a value of this type");
			printf("\tExpression was of type %s", TypeNameOf(zzastArg(3)));
			printf("\n\tExpression in error was: ");
			print_expression(zzastArg(3));
			printf("\n");
		}                                       (*_root) = AST_Put(zzastArg(3)); // Create a "put" node
 zzCONSUME;
	}
	else {
		if ( (LA(1)==73) ) {
			zzmatch(73); zzastDPush; zzCONSUME;
			zzmatch(70); zzastDPush; zzCONSUME;
			_ast = NULL; variable(&_ast);
			zzmatch(71); zzastDPush; zzCONSUME;
			zzmatch(59); zzastDPush;
			
			// Make sure we only get integers
			if (TypeOf(zzastArg(3)) != integer_type)
			{
				syntax_error(zzline, ")", "cannot perform get to a variable of this type");
				printf("\tVariable was of type %s", TypeNameOf(zzastArg(3)));
				printf("\n\tVariable in error was: ");
				print_expression(zzastArg(3));
				printf("\n");
			}                                       // Cannot "get" to a constant...
			if (TokenOf(zzastArg(3)) == CONST)
			{
				syntax_error(zzline, ")", "cannot perform get to a constant");
				printf("\tConstant was of type %s", TypeNameOf(zzastArg(3)));
				printf("\n\tConstant in error was: ");
				print_expression(zzastArg(3));
				printf("\n");
			}                                       (*_root) = AST_Get(zzastArg(3));    // Create a "get" node
 zzCONSUME;
		}
		else {
			if ( (LA(1)==74) ) {
				zzmatch(74); zzastDPush; zzCONSUME;
				zzmatch(59); zzastDPush;
				(*_root) = AST_SkipLine;   
 zzCONSUME;
			}
			else {
				if ( (LA(1)==75) ) {
					zzmatch(75); zzastDPush; zzCONSUME;
					zzmatch(59); zzastDPush;
					(*_root) = AST_NewLine;    
 zzCONSUME;
				}
				else {zzFAIL(1,zzerr6,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
			}
		}
	}
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"iostatement");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "i/o statement", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd3, 0x80);
	zzTRACEOUT((ANTLRChar *)"iostatement");
	}
}

void
#ifdef __STDC__
assignmentstmnt(AST **_root)
#else
assignmentstmnt(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"assignmentstmnt");
	if ( (setwd4[LA(1)]&0x1) ) {
		_ast = NULL; variable(&_ast);
		zzmatch(58); zzastDPush; zzCONSUME;
		_ast = NULL; expression(&_ast);
		zzmatch(59); zzastDPush;
		
		// Make sure lvalue and rvalue types are the same
		if (TypeOf(zzastArg(1)) != TypeOf(zzastArg(3)))
		{
			syntax_error(zzline, ";", "type mismatch during assignment");
			printf("\tLvalue was of type %s", TypeNameOf(zzastArg(1)));
			printf("\n\tRvalue was of type %s", TypeNameOf(zzastArg(3)));
			printf("\n\tLvalue was: ");
			print_expression(zzastArg(1));
			printf("\n\tRvalue was: ");
			print_expression(zzastArg(3));
			printf("\n");
		}                                       (*_root) = AST_Assignment(zzastArg(1), zzastArg(3));     // Set up the assignment node
 zzCONSUME;
	}
	else {
		if ( (LA(1)==CONST) ) {
			_ast = NULL; constant(&_ast);
			zzmatch(58); zzastDPush; zzCONSUME;
			_ast = NULL; expression(&_ast);
			zzmatch(59); zzastDPush;
			
			// If user is trying to assign to a constant, tell them "NO!"
			syntax_error(zzline, zzaArg(zztasp1,1 ).text, "cannot assign to constant"); 
			(*_root) = AST_Assignment(zzastArg(1), zzastArg(3)); 
 zzCONSUME;
		}
		else {zzFAIL(1,zzerr7,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"assignmentstmnt");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "assignment", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd4, 0x2);
	zzTRACEOUT((ANTLRChar *)"assignmentstmnt");
	}
}

void
#ifdef __STDC__
variable(AST **_root)
#else
variable(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	AST *type, *t, *field;   
	zzTRACEIN((ANTLRChar *)"variable");
	_ast = NULL; refvar(&_ast);
	(*_root) = zzastArg(1); zzaArg(zztasp1,0)=zzaArg(zztasp1,1);  
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( 1 ) {
			if ( (LA(1)==65) ) {
				zzmatch(65); zzastDPush; zzCONSUME;
				_ast = NULL; expression(&_ast);
				zzmatch(67); zzastDPush;
				
				// Make sure the variable is an array...
				if (zzchild(TypeOf((*_root))) == NULL || TokenOf(zzchild(TypeOf((*_root)))) != Array)
				{
					syntax_error(zzline, "[", "attempt to index a non-array");
					printf("\tType of base variable: %s", TypeNameOf((*_root)));
					printf("\n\tBase variable was ");
					print_expression((*_root));
					printf("\n");
				}                                          else
				{
					// Make sure the index is an integer
					if (TypeOf(zzastArg(2)) != integer_type)
					{
						syntax_error(zzline, "]", "illegal array index; must be an Integer value");
						printf("\tType of array index: %s", TypeNameOf(zzastArg(2)));
						printf("\n\tIndex expression was ");
						print_expression(zzastArg(2));
						printf("\n");
					}                                          }
				type = TypeOf(TypeOf((*_root)));            // Type of the index is the type of array element
				(*_root) = AST_Index(AST_Name((*_root)),          // Create an index node
				AST_Selector(zzastArg(2))); 
				TypeOf((*_root)) = type;                    // copy the type and the size of element
				SizeOf((*_root)) = SizeOf(type);
 zzCONSUME;
			}
			else {
				if ( (LA(1)==53) ) {
					zzmatch(53); zzastDPush; zzCONSUME;
					zzsetmatch(zzerr8); zzastDPush;
					field = NULL;
					// Make sure we are accessing a record 
					if (zzchild(TypeOf((*_root))) == NULL || TokenOf(zzchild(TypeOf((*_root)))) != Record)
					{
						syntax_error(zzline, zzaArg(zztasp2,2 ).text, "field reference to a non-record type");
						printf("\tBase variable type was %s", TypeNameOf((*_root)));
						printf("\n\tBase variable was ");
						print_expression((*_root));
						printf("\n");
					}                                          else
					{
						// Check if the identifier is a valid field in the record
						for (t = zzchild(zzchild(TypeOf((*_root)))); t!=NULL; t=zzsibling(t))
						if (strcmp(NameOf(zzchild(t)), zzaArg(zztasp2,2 ).text) == 0) 
						{
							field = zzchild(t);
							t = NULL;
						}                                             if (!type)
						{
							syntax_error(zzline, zzaArg(zztasp2,2 ).text, "undefined field");
							printf("\tType of base variable record was %s\n", TypeNameOf((*_root)));
						}                                          }
					t = AST_Ref(field);                   // Create a reference to the field
					TypeOf(t) = TypeOf(field);            // Copy the type and size
					SizeOf(t) = SizeOf(field);            
					(*_root) = AST_Field(AST_Name((*_root)),          // Create a field node
					AST_Selector(t)); 
					TypeOf((*_root)) = TypeOf(field);           // Copy the type and size
					SizeOf((*_root)) = SizeOf(field);
 zzCONSUME;
				}
				else break;
			}
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"variable");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "variable reference", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd4, 0x4);
	zzTRACEOUT((ANTLRChar *)"variable");
	}
}

void
#ifdef __STDC__
exitstmnt(AST **_root)
#else
exitstmnt(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	AST *when_expr=NULL;   
	zzTRACEIN((ANTLRChar *)"exitstmnt");
	zzmatch(76); zzastDPush;
	
	// If we are not currently in a loop, it's a problem...
	if (loop_count == 0)
	syntax_error(zzline, "exit", "exit allowed only from inside a loop");
 zzCONSUME;
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==77) ) {
			zzmatch(77); zzastDPush; zzCONSUME;
			_ast = NULL; expression(&_ast);
			
			// If there was an expression, make sure it's boolean
			if (TypeOf(zzastArg(2)) != boolean_type)
			{
			syntax_error(zzline, "when expression", "when expression not Boolean");
			printf("\tWhen condition type was %s", TypeNameOf(zzastArg(2)));
			printf("\n\tWhen condition was ");
			print_expression(zzastArg(2));
			printf("\n");
		}                                          when_expr = zzastArg(2); 
		}
		zzEXIT(zztasp2);
		}
	}
	zzmatch(59); zzastDPush;
	(*_root) = AST_Exit(when_expr);   
 zzCONSUME;
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"exitstmnt");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "exit statement", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd4, 0x8);
	zzTRACEOUT((ANTLRChar *)"exitstmnt");
	}
}

void
#ifdef __STDC__
procedurecallstmnt(AST **_root)
#else
procedurecallstmnt(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	Sym *p; AST *parms=NULL, *f, *a;   
	zzTRACEIN((ANTLRChar *)"procedurecallstmnt");
	_ast = NULL; proc(&_ast);
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==70) ) {
			_ast = NULL; actualparameterlist(&_ast);
			parms=zzastArg(1);  
		}
		zzEXIT(zztasp2);
		}
	}
	zzmatch(59); zzastDPush;
	
	f = zzchild(zzchild(zzastArg(1)));                        // find formal parms of proc
	// find the actual parameters used during the call
	a = parms;
	while(f || a)  // while we have formals or actuals left...
	{
		if (!f)        // if no more formals
		{
			syntax_error(zzline, zzaArg(zztasp1,1 ).text, "too many parameters in procedure call");
			a = NULL;   // so we can get out of loop
		}                                          else if (!a)   // if no more actuals
		{
			syntax_error(zzline, zzaArg(zztasp1,1 ).text, "Too few parameters in procedure call");
			f = NULL;   // so we can get out of loop
		}                                          else if (TypeOf(zzchild(f)) != TypeOf(a))     // actual & formal type mismatch
		{
			syntax_error(zzline, zzaArg(zztasp1,1 ).text, "type mismatch between actual and formal parameters");
			printf("\tFormal parameter type was %s", TypeNameOf(zzchild(f)));
			printf("\n\tActual parameter type was %s", TypeNameOf(a));
			printf("\n\tFormal parameter was  %s", NameOf(zzchild(f)));
			printf("\n\tActual parameter was ");
			print_expression(a);
			printf("\n");
		}                                          else if (IsVarRef(zzchild(f))) // non-modifiable value used in place of "var" formal
		if (!is_modifiable(a))
		{
			syntax_error(zzline, zzaArg(zztasp1,1 ).text, "only a variable can be used in place of a pass-by-reference formal parameter");
			printf("\tFormal parameter type was %s", TypeNameOf(zzchild(f)));
			printf("\n\tActual parameter type was %s", TypeNameOf(a));
			printf("\n\tFormal parameter was %s", NameOf(zzchild(f)));
			printf("\n\tActual parameter was ");
			print_expression(a);
			printf("\n");
		}                                             else // actual is pass-by-reference -- Change Value to PassAddr (a dummy token)
		TokenOf(a) = PassAddr;
		if (f)   // if any formals left, move to next one
		f = zzsibling(f);
		if (a)   // if any actuals left, move to next one
		a = zzsibling(a);
	}                                       (*_root) =  AST_ProcCall(AST_Ref(zzastArg(1)) , AST_Parms(parms));      // Set up procedure call node
 zzCONSUME;
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"procedurecallstmnt");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "procedure call statement", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd4, 0x10);
	zzTRACEOUT((ANTLRChar *)"procedurecallstmnt");
	}
}

void
#ifdef __STDC__
actualparameterlist(AST **_root)
#else
actualparameterlist(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"actualparameterlist");
	zzmatch(70);  zzCONSUME;
	expression(zzSTR); zzlink(_root, &_sibling, &_tail);
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (LA(1)==61) ) {
			zzmatch(61);  zzCONSUME;
			expression(zzSTR); zzlink(_root, &_sibling, &_tail);
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzmatch(71);  zzCONSUME;
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"actualparameterlist");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "actual parameter list", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd4, 0x20);
	zzTRACEOUT((ANTLRChar *)"actualparameterlist");
	}
}

void
#ifdef __STDC__
returnstmnt(AST **_root)
#else
returnstmnt(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"returnstmnt");
	zzmatch(78); zzastDPush; zzCONSUME;
	zzmatch(59); zzastDPush;
	(*_root) = AST_Return;   
 zzCONSUME;
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"returnstmnt");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "return statement", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd4, 0x40);
	zzTRACEOUT((ANTLRChar *)"returnstmnt");
	}
}

void
#ifdef __STDC__
ifstmnt(AST **_root)
#else
ifstmnt(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"ifstmnt");
	zzmatch(79); zzastDPush; zzCONSUME;
	_ast = NULL; ifpart(&_ast);
	zzmatch(55); zzastDPush; zzCONSUME;
	zzmatch(79); zzastDPush; zzCONSUME;
	zzmatch(59); zzastDPush;
	(*_root) = zzastArg(2);   
 zzCONSUME;
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"ifstmnt");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "if statement", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd4, 0x80);
	zzTRACEOUT((ANTLRChar *)"ifstmnt");
	}
}

void
#ifdef __STDC__
ifpart(AST **_root)
#else
ifpart(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	AST *then_part=NULL, *else_part=NULL;   
	zzTRACEIN((ANTLRChar *)"ifpart");
	_ast = NULL; expression(&_ast);
	zzmatch(80); zzastDPush;
	
	// Make sure the expression was boolean
	if (TypeOf(zzastArg(1)) != boolean_type)
	{
		syntax_error(zzline, "then", "type of condition on if statement is not Boolean");
		printf("\tType of condition was %s", TypeNameOf(zzastArg(1)));
		printf("\n\tExpression was ");
		print_expression(zzastArg(1));
		printf("\n");
	}                                      
 zzCONSUME;
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (setwd5[LA(1)]&0x1) ) {
			_ast = NULL; statement(&_ast);
			
			if (then_part == NULL)        // If no statements in "then" yet
			then_part = zzastArg(1);            //      make this the first
			else                          // otherwise, tack it on
			then_part = AST_Make_Siblings(then_part, zzastArg(1)); 
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==81) ) {
			zzmatch(81); zzastDPush; zzCONSUME;
			_ast = NULL; ifpart(&_ast);
			else_part = zzastArg(2);   
		}
		else {
			if ( (LA(1)==82) ) {
				zzmatch(82); zzastDPush; zzCONSUME;
				{
					zzBLOCK(zztasp3);
					zzMake0;
					{
					while ( (setwd5[LA(1)]&0x2) ) {
						_ast = NULL; statement(&_ast);
						
						if (else_part == NULL)     // if no statements in "else" so far
						else_part = zzastArg(1);         //      make this the first
						else                       // otherwise, tack it on
						else_part = AST_Make_Siblings(else_part, zzastArg(1)); 
						zzLOOP(zztasp3);
					}
					zzEXIT(zztasp3);
					}
				}
			}
		}
		zzEXIT(zztasp2);
		}
	}
	// Create the If node
	(*_root) = AST_If(zzastArg(1), 
	AST_Then(then_part), 
	AST_Else(else_part));   
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"ifpart");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "if statement", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd5, 0x4);
	zzTRACEOUT((ANTLRChar *)"ifpart");
	}
}

void
#ifdef __STDC__
loopstmnt(AST **_root)
#else
loopstmnt(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	(*_root) = NULL;   
	zzTRACEIN((ANTLRChar *)"loopstmnt");
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (LA(1)==83) ) {
			zzmatch(83); zzastDPush; zzCONSUME;
			_ast = NULL; expression(&_ast);
			
			// Make sure the "while" expression is boolean
			if (TypeOf(zzastArg(2)) != boolean_type)
			{
				syntax_error(zzline, "while expression", "while expression type not Boolean");
				printf("\tWhile condition type was %s", TypeNameOf(zzastArg(2)));
				printf("\n\tWhile condition was ");
				print_expression(zzastArg(2));
				printf("\n");
			}                                          (*_root) = AST_While(zzastArg(2));   // Create a "while" node
		}
		zzEXIT(zztasp2);
		}
	}
	zzmatch(84); zzastDPush;
	loop_count++;   
 zzCONSUME;
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (setwd5[LA(1)]&0x8) ) {
			_ast = NULL; statement(&_ast);
			if ((*_root) == NULL)    // If there was no "while"
			(*_root) = zzastArg(1);        //      keep just the statements
			else               // otherwise, tack statements after while part
			(*_root) = AST_Make_Siblings((*_root), zzastArg(1));
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzmatch(55); zzastDPush; zzCONSUME;
	zzmatch(84); zzastDPush; zzCONSUME;
	zzmatch(59); zzastDPush;
	
	loop_count--;        // so we can catch bad exit placement
	(*_root) = AST_Loop((*_root));   // make a new loop node
 zzCONSUME;
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"loopstmnt");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "loop statement", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd5, 0x10);
	zzTRACEOUT((ANTLRChar *)"loopstmnt");
	}
}

void
#ifdef __STDC__
expression(AST **_root)
#else
expression(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"expression");
	_ast = NULL; relation(&_ast);
	(*_root) = zzastArg(1);   
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (setwd5[LA(1)]&0x20) ) {
			{
				zzBLOCK(zztasp3);
				zzMake0;
				{
				if ( (LA(1)==85) ) {
					zzmatch(85); zzastDPush;
					zzaArg(zztasp3,0)=zzaArg(zztasp3,1);   
 zzCONSUME;
				}
				else {
					if ( (LA(1)==86) ) {
						zzmatch(86); zzastDPush;
						zzaArg(zztasp3,0)=zzaArg(zztasp3,1);   
 zzCONSUME;
					}
					else {zzFAIL(1,zzerr9,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
				}
				zzEXIT(zztasp3);
				}
			}
			_ast = NULL; relation(&_ast);
			
			// "and" and "or" require boolean ops
			if (TypeOf((*_root)) != boolean_type)
			{
				syntax_error(zzline, zzaArg(zztasp2,1 ).text, "left side is not Boolean");
				printf("\tType of left side was %s", TypeNameOf((*_root)));
				printf("\n\tLeft side was ");
				print_expression((*_root));
				printf("\n");
			}                                          if (TypeOf(zzastArg(2)) != boolean_type)
			{
				syntax_error(zzline, zzaArg(zztasp2,1 ).text, "right side is not Boolean");
				printf("\tType of right side was %s", TypeNameOf(zzastArg(2)));
				printf("\n\tRight side was ");
				print_expression(zzastArg(2));
				printf("\n");
			}                                          // Create a new binary expression node
			(*_root) = AST_BinaryOp(AST_Operand(zzaArg(zztasp2,1 ).text), 
			AST_Left((*_root)), 
			AST_Right(zzastArg(2)));     
			TypeOf((*_root)) = boolean_type;    // Assume it ends up with correct type
			SizeOf((*_root)) = 1;               // With correct size
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"expression");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "expression", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd5, 0x40);
	zzTRACEOUT((ANTLRChar *)"expression");
	}
}

void
#ifdef __STDC__
relation(AST **_root)
#else
relation(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"relation");
	_ast = NULL; simpleexpression(&_ast);
	(*_root) = zzastArg(1);   
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (setwd5[LA(1)]&0x80) ) {
			{
				zzBLOCK(zztasp3);
				zzMake0;
				{
				if ( (LA(1)==52) ) {
					zzmatch(52); zzastDPush;
					zzaArg(zztasp3,0)=zzaArg(zztasp3,1);  
 zzCONSUME;
				}
				else {
					if ( (LA(1)==87) ) {
						zzmatch(87); zzastDPush;
						zzaArg(zztasp3,0)=zzaArg(zztasp3,1);  
 zzCONSUME;
					}
					else {
						if ( (LA(1)==88) ) {
							zzmatch(88); zzastDPush;
							zzaArg(zztasp3,0)=zzaArg(zztasp3,1);  
 zzCONSUME;
						}
						else {
							if ( (LA(1)==89) ) {
								zzmatch(89); zzastDPush;
								zzaArg(zztasp3,0)=zzaArg(zztasp3,1);  
 zzCONSUME;
							}
							else {
								if ( (LA(1)==90) ) {
									zzmatch(90); zzastDPush;
									zzaArg(zztasp3,0)=zzaArg(zztasp3,1);  
 zzCONSUME;
								}
								else {
									if ( (LA(1)==91) ) {
										zzmatch(91); zzastDPush;
										zzaArg(zztasp3,0)=zzaArg(zztasp3,1);  
 zzCONSUME;
									}
									else {zzFAIL(1,zzerr10,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
								}
							}
						}
					}
				}
				zzEXIT(zztasp3);
				}
			}
			_ast = NULL; simpleexpression(&_ast);
			
			// These are arithmetic operators and require integers
			if (TypeOf((*_root)) != integer_type)
			{
				syntax_error(zzline, zzaArg(zztasp2,1 ).text, "left side is not Integer");
				printf("\tType of left side was %s", TypeNameOf((*_root)));
				printf("\n\tLeft side was ");
				print_expression((*_root));
				printf("\n");
			}                                          if (TypeOf(zzastArg(2)) != integer_type)
			{
				syntax_error(zzline, zzaArg(zztasp2,1 ).text, "right side is not Integer");
				printf("\tType of right side was %s", TypeNameOf(zzastArg(2)));
				printf("\n\tRight side was ");
				print_expression(zzastArg(2));
				printf("\n");
			}                                          // Create a new binary expression node
			(*_root) = AST_BinaryOp(AST_Operand(zzaArg(zztasp2,1 ).text), 
			AST_Left((*_root)), 
			AST_Right(zzastArg(2)));
			TypeOf((*_root)) = boolean_type;    // Assume the end-type is correct
			SizeOf((*_root)) = 1;               // Assume size is right
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"relation");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "expression", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd6, 0x1);
	zzTRACEOUT((ANTLRChar *)"relation");
	}
}

void
#ifdef __STDC__
simpleexpression(AST **_root)
#else
simpleexpression(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	int must_be_int=0;   
	zzTRACEIN((ANTLRChar *)"simpleexpression");
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		if ( (setwd6[LA(1)]&0x2) ) {
			{
				zzBLOCK(zztasp3);
				zzMake0;
				{
				if ( (LA(1)==92) ) {
					zzmatch(92); zzastDPush;
					must_be_int=1; zzaArg(zztasp3,0)=zzaArg(zztasp3,1);   
 zzCONSUME;
				}
				else {
					if ( (LA(1)==93) ) {
						zzmatch(93); zzastDPush;
						must_be_int=2; zzaArg(zztasp3,0)=zzaArg(zztasp3,1);   
 zzCONSUME;
					}
					else {zzFAIL(1,zzerr11,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
				}
				zzEXIT(zztasp3);
				}
			}
			zzaArg(zztasp2,0)=zzaArg(zztasp2,1);  
		}
		zzEXIT(zztasp2);
		}
	}
	_ast = NULL; simpleexpression2(&_ast);
	
	if (must_be_int)  // If it has a unary + or -
	{
		if (TypeOf(zzastArg(2)) != integer_type)  // make sure first op is an integer
		{
			syntax_error(zzline, zzaArg(zztasp1,1 ).text, "right side is not Integer");
			printf("\tType of right side was %s", TypeNameOf(zzastArg(2)));
			printf("\n\tRight side was ");
			print_expression(zzastArg(2));
			printf("\n");
		}                                       if (must_be_int == 2) // Don't bother putting in "+" op
		{
		(*_root) = AST_UnaryOp(AST_Operand(zzaArg(zztasp1,1 ).text), 
		AST_Right(zzastArg(2)));
		TypeOf((*_root)) = integer_type;
		SizeOf((*_root)) = 1;
	}                                       else  // For unary "+" just pass through the operand
	(*_root) = zzastArg(2);
} 
else
(*_root) = zzastArg(2);
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"simpleexpression");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "expression", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd6, 0x4);
	zzTRACEOUT((ANTLRChar *)"simpleexpression");
	}
}

void
#ifdef __STDC__
simpleexpression2(AST **_root)
#else
simpleexpression2(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"simpleexpression2");
	_ast = NULL; term(&_ast);
	(*_root)=zzastArg(1);  
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (setwd6[LA(1)]&0x8) ) {
			{
				zzBLOCK(zztasp3);
				zzMake0;
				{
				if ( (LA(1)==92) ) {
					zzmatch(92); zzastDPush;
					zzaArg(zztasp3,0)=zzaArg(zztasp3,1);  
 zzCONSUME;
				}
				else {
					if ( (LA(1)==93) ) {
						zzmatch(93); zzastDPush;
						zzaArg(zztasp3,0)=zzaArg(zztasp3,1);  
 zzCONSUME;
					}
					else {zzFAIL(1,zzerr12,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
				}
				zzEXIT(zztasp3);
				}
			}
			_ast = NULL; term(&_ast);
			
			// + and - require integer operands
			if (TypeOf((*_root)) != integer_type)
			{
				syntax_error(zzline, zzaArg(zztasp2,1 ).text, "Left side is not Integer");
				printf("\tType of left side was %s", TypeNameOf((*_root)));
				printf("\n\tLeft side was ");
				print_expression((*_root));
				printf("\n");
			}                                          if (TypeOf(zzastArg(2)) != integer_type)
			{
				syntax_error(zzline, zzaArg(zztasp2,1 ).text, "right side is not Integer");
				printf("\tType of right side was %s", TypeNameOf(zzastArg(2)));
				printf("\n\tRight side was ");
				print_expression(zzastArg(2));
				printf("\n");
			}                                          // Create a new bvinary expression node
			(*_root) = AST_BinaryOp(AST_Operand(zzaArg(zztasp2,1 ).text), 
			AST_Left((*_root)), 
			AST_Right(zzastArg(2)));
			TypeOf((*_root)) = integer_type;    // assume output is correct type
			SizeOf((*_root)) = 1;               // assume size if correct
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"simpleexpression2");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "expression", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd6, 0x10);
	zzTRACEOUT((ANTLRChar *)"simpleexpression2");
	}
}

void
#ifdef __STDC__
term(AST **_root)
#else
term(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"term");
	_ast = NULL; factor(&_ast);
	(*_root)=zzastArg(1);  
	{
		zzBLOCK(zztasp2);
		zzMake0;
		{
		while ( (setwd6[LA(1)]&0x20) ) {
			{
				zzBLOCK(zztasp3);
				zzMake0;
				{
				if ( (LA(1)==94) ) {
					zzmatch(94); zzastDPush;
					zzaArg(zztasp3,0)=zzaArg(zztasp3,1);  
 zzCONSUME;
				}
				else {
					if ( (LA(1)==95) ) {
						zzmatch(95); zzastDPush;
						zzaArg(zztasp3,0)=zzaArg(zztasp3,1);  
 zzCONSUME;
					}
					else {
						if ( (LA(1)==96) ) {
							zzmatch(96); zzastDPush;
							zzaArg(zztasp3,0)=zzaArg(zztasp3,1);  
 zzCONSUME;
						}
						else {zzFAIL(1,zzerr13,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
					}
				}
				zzEXIT(zztasp3);
				}
			}
			_ast = NULL; factor(&_ast);
			
			// * and / need integer operands
			if (TypeOf((*_root)) != integer_type)
			{
				syntax_error(zzline, zzaArg(zztasp2,1 ).text, "left side is not Integer");
				printf("\tType of left side was %s", TypeNameOf((*_root)));
				printf("\n\tLeft side was ");
				print_expression((*_root));
				printf("\n");
			}                                          if (TypeOf(zzastArg(2)) != integer_type)
			{
				syntax_error(zzline, zzaArg(zztasp2,1 ).text, "right side is not Integer");
				printf("\tType of right side was %s", TypeNameOf(zzastArg(2)));
				printf("\n\tRight side was ");
				print_expression(zzastArg(2));
				printf("\n");
			}                                          // Create a new binary expression
			(*_root) = AST_BinaryOp(AST_Operand(zzaArg(zztasp2,1 ).text), 
			AST_Left((*_root)), 
			AST_Right(zzastArg(2)));
			TypeOf((*_root)) = integer_type;    // Assume output is correct size and type
			SizeOf((*_root)) = 1;
			zzLOOP(zztasp2);
		}
		zzEXIT(zztasp2);
		}
	}
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"term");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "expression", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd6, 0x40);
	zzTRACEOUT((ANTLRChar *)"term");
	}
}

void
#ifdef __STDC__
factor(AST **_root)
#else
factor(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"factor");
	if ( (LA(1)==97) ) {
		zzmatch(97); zzastDPush; zzCONSUME;
		_ast = NULL; factor(&_ast);
		
		// "not" only applies to booleans
		if (TypeOf(zzastArg(2)) != boolean_type)
		{
			syntax_error(zzline, zzaArg(zztasp1,1 ).text, "right side is not Boolean");
			printf("\tType of right side was %s", TypeNameOf(zzastArg(2)));
			printf("\n\tRight side was ");
			print_expression(zzastArg(2));
			printf("\n");
		}                                       // Create a new unary expression node
		(*_root)=AST_UnaryOp(AST_Operand("not"), 
		zzastArg(2));
		TypeOf((*_root)) = boolean_type;       // assume type and size are correct
		SizeOf((*_root)) = 1;
	}
	else {
		if ( (setwd6[LA(1)]&0x80) ) {
			_ast = NULL; constantvalue(&_ast);
			(*_root)=zzastArg(1);   
		}
		else {
			if ( (setwd7[LA(1)]&0x1) ) {
				_ast = NULL; variable(&_ast);
				
				// Create a node to get the VALUE of the variable
				(*_root) = AST_Value(zzastArg(1)); TypeOf((*_root))=TypeOf(zzastArg(1)); SizeOf((*_root)) = SizeOf(zzastArg(1)); 
				zzaArg(zztasp1,0) = zzaArg(zztasp1,1);
			}
			else {
				if ( (LA(1)==70) ) {
					zzmatch(70); zzastDPush; zzCONSUME;
					_ast = NULL; expression(&_ast);
					zzmatch(71); zzastDPush;
					(*_root)=zzastArg(2);   
 zzCONSUME;
				}
				else {zzFAIL(1,zzerr14,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
			}
		}
	}
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"factor");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "expression", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd7, 0x2);
	zzTRACEOUT((ANTLRChar *)"factor");
	}
}

void
#ifdef __STDC__
typename(AST **_root)
#else
typename(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"typename");
	if ( (LA(1)==TYPE) ) {
		_ast = NULL; type(&_ast);
		(*_root) = zzastArg(1);   
	}
	else {
		if ( (LA(1)==98) ) {
			zzmatch(98); zzastDPush;
			(*_root) = integer_type;   
 zzCONSUME;
		}
		else {
			if ( (LA(1)==99) ) {
				zzmatch(99); zzastDPush;
				(*_root) = boolean_type;   
 zzCONSUME;
			}
			else {zzFAIL(1,zzerr15,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
		}
	}
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"typename");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, "type reference", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd7, 0x4);
	zzTRACEOUT((ANTLRChar *)"typename");
	}
}

void
#ifdef __STDC__
def(AST **_root, Sym **scope,        
     int    level,
     int    token )
#else
def(_root,scope,level,token)
AST **_root;
 Sym **scope;
int    level;
int    token ;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	Sym *var;  
	zzTRACEIN((ANTLRChar *)"def");
	if ( (LA(1)==IDENT) ) {
		_ast = NULL; ident(&_ast);
		
		// If we get back "ident" as symbol, it's not defined yet
		// Define the symbol under the current scope
		zzs_scope( scope);   
		define_symbol(var, zzaArg(zztasp1,1 ).text,  level,  token, NULL);
		
                                       // Create a node for the symbol
		(*_root) = AST_Node( token,zzaArg(zztasp1,1 ).text); 
		
                                       // Keep a pointer to the AST node in the symbol table
		var->type = (*_root);
		
                                       // If user wants dynamic definition tracing, show it
		if (show_definition)
		printf("     defining %s\n",zzaArg(zztasp1,1 ).text);
		zzaArg(zztasp1,0)=zzaArg(zztasp1,1);
	}
	else {
		if ( (setwd7[LA(1)]&0x8) ) {
			_ast = NULL; already_defined(&_ast);
			
			// If we get here, symbol is already defined
			var = zzs_get(zzaArg(zztasp1,1 ).text);  // Get it's symbol table info
			
                                       // If it's already defined at the current level, it's an error
			if ( level == var->level)
			{
			syntax_error(zzline, zzaArg(zztasp1,1 ).text, "identifier redeclared");
			(*_root) = NULL;
		}                                       
		// otherwise, go ahead and define it at this scope
		else
		{
		zzs_scope( scope);
		define_symbol(var, zzaArg(zztasp1,1 ).text,  level,  token, NULL);
		(*_root) = AST_Node( token,zzaArg(zztasp1,1 ).text); 
		var->type = (*_root);
		if (show_definition)
		printf("     defining %s at new scope\n",zzaArg(zztasp1,1 ).text);
	}                                       zzaArg(zztasp1,0)=zzaArg(zztasp1,1);
		}
		else {zzFAIL(1,zzerr16,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"def");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd7, 0x10);
	zzTRACEOUT((ANTLRChar *)"def");
	}
}

void
#ifdef __STDC__
already_defined(AST **_root)
#else
already_defined(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"already_defined");
	if ( (LA(1)==VAR) ) {
		varx(zzSTR); zzlink(_root, &_sibling, &_tail);
		zzaArg(zztasp1,0)=zzaArg(zztasp1,1);  
	}
	else {
		if ( (LA(1)==CONST) ) {
			constant(zzSTR); zzlink(_root, &_sibling, &_tail);
			zzaArg(zztasp1,0)=zzaArg(zztasp1,1);  
		}
		else {
			if ( (LA(1)==PROC) ) {
				proc(zzSTR); zzlink(_root, &_sibling, &_tail);
				zzaArg(zztasp1,0)=zzaArg(zztasp1,1);  
			}
			else {
				if ( (LA(1)==TYPE) ) {
					type(zzSTR); zzlink(_root, &_sibling, &_tail);
					zzaArg(zztasp1,0)=zzaArg(zztasp1,1);  
				}
				else {zzFAIL(1,zzerr17,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
			}
		}
	}
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"already_defined");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd7, 0x20);
	zzTRACEOUT((ANTLRChar *)"already_defined");
	}
}

void
#ifdef __STDC__
refvar(AST **_root)
#else
refvar(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"refvar");
	if ( (LA(1)==IDENT) ) {
		_ast = NULL; ident(&_ast);
		syntax_error(zzline, zzaArg(zztasp1,1 ).text, "undefined variable"); zzaArg(zztasp1,0)=zzaArg(zztasp1,1); (*_root)=AST_Undefined; TypeOf((*_root)) = undefined_type; Init((*_root)) = NULL;   
	}
	else {
		if ( (LA(1)==VAR) ) {
			_ast = NULL; varx(&_ast);
			zzaArg(zztasp1,0)=zzaArg(zztasp1,1); (*_root) = AST_Ref(zzastArg(1)); TypeOf((*_root)) = TypeOf(zzastArg(1)); SizeOf((*_root)) = SizeOf(zzastArg(1)); 
			if (IsVarRef(zzastArg(1)))  // if it's a "var" parm, de-ref it once more to get real addr
			{ (*_root) = AST_Value((*_root)); TypeOf((*_root)) = TypeOf(zzastArg(1)); SizeOf((*_root)) = SizeOf(zzastArg(1)); }
		}
		else {zzFAIL(1,zzerr18,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"refvar");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd7, 0x40);
	zzTRACEOUT((ANTLRChar *)"refvar");
	}
}

void
#ifdef __STDC__
refconst(AST **_root)
#else
refconst(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"refconst");
	if ( (LA(1)==IDENT) ) {
		_ast = NULL; ident(&_ast);
		syntax_error(zzline, zzaArg(zztasp1,1 ).text, "undefined constant"); zzaArg(zztasp1,0)=zzaArg(zztasp1,1); (*_root)=AST_Undefined; TypeOf((*_root)) = undefined_type; Init((*_root)) = NULL;   
	}
	else {
		if ( (LA(1)==CONST) ) {
			_ast = NULL; constant(&_ast);
			zzaArg(zztasp1,0)=zzaArg(zztasp1,1); (*_root)=zzastArg(1);   
		}
		else {zzFAIL(1,zzerr19,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"refconst");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd7, 0x80);
	zzTRACEOUT((ANTLRChar *)"refconst");
	}
}

void
#ifdef __STDC__
refproc(AST **_root)
#else
refproc(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"refproc");
	if ( (LA(1)==IDENT) ) {
		ident(zzSTR); zzlink(_root, &_sibling, &_tail);
		syntax_error(zzline, zzaArg(zztasp1,1 ).text, "undefined subprogram"); zzaArg(zztasp1,0)=zzaArg(zztasp1,1); (*_root)=AST_Undefined; TypeOf((*_root)) = undefined_type; Init((*_root)) = NULL;   
	}
	else {
		if ( (LA(1)==PROC) ) {
			proc(zzSTR); zzlink(_root, &_sibling, &_tail);
			zzaArg(zztasp1,0)=zzaArg(zztasp1,1);   
		}
		else {zzFAIL(1,zzerr20,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"refproc");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd8, 0x1);
	zzTRACEOUT((ANTLRChar *)"refproc");
	}
}

void
#ifdef __STDC__
ident(AST **_root)
#else
ident(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"ident");
	zzmatch(IDENT); zzastDPush;
	zzaArg(zztasp1,0)=zzaArg(zztasp1,1); (*_root) = AST_Node(Undefined, zzaArg(zztasp1,1 ).text);   
 zzCONSUME;
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"ident");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd8, 0x2);
	zzTRACEOUT((ANTLRChar *)"ident");
	}
}

void
#ifdef __STDC__
varx(AST **_root)
#else
varx(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"varx");
	zzmatch(VAR); zzastDPush;
	zzaArg(zztasp1,0)=zzaArg(zztasp1,1); (*_root) = TypeOf(zzs_get(zzaArg(zztasp1,1 ).text));   
 zzCONSUME;
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"varx");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd8, 0x4);
	zzTRACEOUT((ANTLRChar *)"varx");
	}
}

void
#ifdef __STDC__
constant(AST **_root)
#else
constant(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"constant");
	zzmatch(CONST); zzastDPush;
	zzaArg(zztasp1,0)=zzaArg(zztasp1,1); (*_root) = zzdup_ast(find_val(TypeOf(zzs_get(zzaArg(zztasp1,1 ).text)))); 
	if ((*_root))
	{ (*_root)->down = NULL; (*_root)->right = NULL; } 
 zzCONSUME;
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"constant");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd8, 0x8);
	zzTRACEOUT((ANTLRChar *)"constant");
	}
}

void
#ifdef __STDC__
proc(AST **_root)
#else
proc(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"proc");
	zzmatch(PROC); zzastDPush;
	zzaArg(zztasp1,0)=zzaArg(zztasp1,1); (*_root) = TypeOf(zzs_get(zzaArg(zztasp1,1 ).text));   
 zzCONSUME;
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"proc");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd8, 0x10);
	zzTRACEOUT((ANTLRChar *)"proc");
	}
}

void
#ifdef __STDC__
type(AST **_root)
#else
type(_root)
AST **_root;
#endif
{
	zzRULE;
	zzBLOCK(zztasp1);
	zzMake0;
	{
	zzTRACEIN((ANTLRChar *)"type");
	zzmatch(TYPE); zzastDPush;
	zzaArg(zztasp1,0)=zzaArg(zztasp1,1); (*_root) = TypeOf(zzs_get(zzaArg(zztasp1,1 ).text));   
 zzCONSUME;
	zzEXIT(zztasp1);
	zzTRACEOUT((ANTLRChar *)"type");
	return;
fail:
	zzEXIT(zztasp1);
	zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
	zzresynch(setwd8, 0x20);
	zzTRACEOUT((ANTLRChar *)"type");
	}
}
