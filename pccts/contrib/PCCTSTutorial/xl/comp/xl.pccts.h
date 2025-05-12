// xl.pccts.h -- definitions for the compiler

// definitions for the symbol table
#define HashTableSize    999
#define StringTableSize 5000

#define D_TextSize 101   // max size for identifier

// override the recursive descent trace routines
#define zzTRACEIN(text)  if (trace) sasTRACEIN((char *)text)
#define zzTRACEOUT(text) if (trace) sasTRACEOUT((char *)text)

// make it easier to define a symbol table symbol
#define define_symbol(p, name, lvl, symtype, astnode)   p = zzs_newadd(name); p->level = lvl; p->token = symtype; p->type = astnode;

#include "charbuf.h"   // include the atribute structure

// define the fields to be used int eh AST
#define AST_FIELDS int token, level, ref, size, displ; char str[D_TextSize]; struct _ast *type, *init; 

#include "sym.h"  // include the symbol table definition

// override the AST creation routine
#define zzcr_ast(ast,attr,tok,text) create_ast(ast,attr,tok,text)

#include "ast.h" // include the AST routine definitions

// define some global variables
extern int indent;
extern int level;
extern int walk_tree;
extern int show_definition;
extern int list_variables;
extern int trace;
extern char *file_name;

// declare the AST creation routine
void create_ast(AST *ast, Attrib *attr, int tok, char *text);
            
// define more meaningful access to the trees
#define TokenOf(ast_node)     ast_node->token
#define NameOf(ast_node)      ast_node->str
#define TypeOf(ast_node)      ast_node->type
#define SizeOf(ast_node)      ast_node->size
#define TypeNameOf(ast_node)  NameOf(TypeOf(ast_node))
#define Init(ast_node)        ast_node->init
#define IsVarRef(ast_node)    ast_node->ref
#define DispOf(ast_node)      ast_node->displ
#define LevelOf(ast_node)     ast_node->level
