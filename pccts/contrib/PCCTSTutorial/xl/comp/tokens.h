/* tokens.h -- List of labelled tokens and stuff
 *
 * Generated from: xl.pccts
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-1994
 * Purdue University Electrical Engineering
 * ANTLR Version 1.20
 */
#define PROC 4
#define TYPE 5
#define VAR 6
#define CONST 7
#define INTLIT 11
#define CHARLIT 12
#define STRINGLIT 13
#define Name 15
#define Op 16
#define File 17
#define Define 18
#define Undefined 19
#define Parms 20
#define Value 21
#define ThenPart 22
#define ElsePart 23
#define While 24
#define Ref 25
#define Index 26
#define Field 27
#define Program 28
#define Array 29
#define Record 30
#define Exit 31
#define ProcedureCall 32
#define Return 33
#define If 34
#define Loop 35
#define And 36
#define Or 37
#define Not 38
#define Mod 39
#define Body 40
#define Lower 41
#define Upper 42
#define Procedure 43
#define Type 44
#define Get 45
#define Put 46
#define SkipLine 47
#define NewLine 48
#define Assign 49
#define PassAddr 50
#define IDENT 100
#define BADIDENT 101

#ifdef __STDC__
void program(AST **);
#else
extern void program();
#endif

#ifdef __STDC__
void subprogrambody(AST **, Sym **locals,
               int   level, 
               char *name,
               AST *type );
#else
extern void subprogrambody();
#endif

#ifdef __STDC__
void basicdecl(AST **, Sym **locals,
          int    level );
#else
extern void basicdecl();
#endif

#ifdef __STDC__
void vardecl(AST **, Sym **locals,                                 
         int   level );
#else
extern void vardecl();
#endif

#ifdef __STDC__
void constdecl(AST **, Sym **locals,
           int level );
#else
extern void constdecl();
#endif

#ifdef __STDC__
void constantvalue(AST **);
#else
extern void constantvalue();
#endif

#ifdef __STDC__
void identifierlist(AST **, Sym **locals,
                int    level,
                int    token );
#else
extern void identifierlist();
#endif

#ifdef __STDC__
void typedecl(AST **, Sym **locals,
          int    level );
#else
extern void typedecl();
#endif

#ifdef __STDC__
void typedefn(AST **, Sym **locals,
         int    level );
#else
extern void typedefn();
#endif

#ifdef __STDC__
void recordtypedefn(AST **, int level );
#else
extern void recordtypedefn();
#endif

#ifdef __STDC__
void arraytypedefn(AST **, Sym **locals,
               int    level );
#else
extern void arraytypedefn();
#endif

#ifdef __STDC__
void integerconstant(AST **, Sym **locals,
                 int    level );
#else
extern void integerconstant();
#endif

#ifdef __STDC__
void proceduredecl(AST **, Sym **locals,
               int    level );
#else
extern void proceduredecl();
#endif

#ifdef __STDC__
void formalpart(AST **, Sym **locals,
            int    level );
#else
extern void formalpart();
#endif

#ifdef __STDC__
void parameterspec(AST **, Sym **locals,
               int    level );
#else
extern void parameterspec();
#endif

#ifdef __STDC__
void statement(AST **);
#else
extern void statement();
#endif

#ifdef __STDC__
void iostatement(AST **);
#else
extern void iostatement();
#endif

#ifdef __STDC__
void assignmentstmnt(AST **);
#else
extern void assignmentstmnt();
#endif

#ifdef __STDC__
void variable(AST **);
#else
extern void variable();
#endif

#ifdef __STDC__
void exitstmnt(AST **);
#else
extern void exitstmnt();
#endif

#ifdef __STDC__
void procedurecallstmnt(AST **);
#else
extern void procedurecallstmnt();
#endif

#ifdef __STDC__
void actualparameterlist(AST **);
#else
extern void actualparameterlist();
#endif

#ifdef __STDC__
void returnstmnt(AST **);
#else
extern void returnstmnt();
#endif

#ifdef __STDC__
void ifstmnt(AST **);
#else
extern void ifstmnt();
#endif

#ifdef __STDC__
void ifpart(AST **);
#else
extern void ifpart();
#endif

#ifdef __STDC__
void loopstmnt(AST **);
#else
extern void loopstmnt();
#endif

#ifdef __STDC__
void expression(AST **);
#else
extern void expression();
#endif

#ifdef __STDC__
void relation(AST **);
#else
extern void relation();
#endif

#ifdef __STDC__
void simpleexpression(AST **);
#else
extern void simpleexpression();
#endif

#ifdef __STDC__
void simpleexpression2(AST **);
#else
extern void simpleexpression2();
#endif

#ifdef __STDC__
void term(AST **);
#else
extern void term();
#endif

#ifdef __STDC__
void factor(AST **);
#else
extern void factor();
#endif

#ifdef __STDC__
void typename(AST **);
#else
extern void typename();
#endif

#ifdef __STDC__
void def(AST **, Sym **scope,        
     int    level,
     int    token );
#else
extern void def();
#endif

#ifdef __STDC__
void already_defined(AST **);
#else
extern void already_defined();
#endif

#ifdef __STDC__
void refvar(AST **);
#else
extern void refvar();
#endif

#ifdef __STDC__
void refconst(AST **);
#else
extern void refconst();
#endif

#ifdef __STDC__
void refproc(AST **);
#else
extern void refproc();
#endif

#ifdef __STDC__
void ident(AST **);
#else
extern void ident();
#endif

#ifdef __STDC__
void varx(AST **);
#else
extern void varx();
#endif

#ifdef __STDC__
void constant(AST **);
#else
extern void constant();
#endif

#ifdef __STDC__
void proc(AST **);
#else
extern void proc();
#endif

#ifdef __STDC__
void type(AST **);
#else
extern void type();
#endif
extern SetWordType zzerr1[];
extern SetWordType zzerr2[];
extern SetWordType setwd1[];
extern SetWordType zzerr3[];
extern SetWordType zzerr4[];
extern SetWordType setwd2[];
extern SetWordType zzerr5[];
extern SetWordType zzerr6[];
extern SetWordType setwd3[];
extern SetWordType zzerr7[];
extern SetWordType zzerr8[];
extern SetWordType setwd4[];
extern SetWordType zzerr9[];
extern SetWordType zzerr10[];
extern SetWordType setwd5[];
extern SetWordType zzerr11[];
extern SetWordType zzerr12[];
extern SetWordType zzerr13[];
extern SetWordType setwd6[];
extern SetWordType zzerr14[];
extern SetWordType zzerr15[];
extern SetWordType zzerr16[];
extern SetWordType zzerr17[];
extern SetWordType zzerr18[];
extern SetWordType zzerr19[];
extern SetWordType zzerr20[];
extern SetWordType setwd7[];
extern SetWordType setwd8[];
