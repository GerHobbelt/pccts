#ifndef tokens_h
#define tokens_h
/* tokens.h -- List of labelled tokens and stuff
 *
 * Generated from: sor.g
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * ANTLR Version 1.33MR33
 *
 *   ..\bin\antlr -emsvc -gh -k 2 -gt sor.g
 *
 */
#define zzEOF_TOKEN 1
#define Eof 1
#define RExpr 2
#define Action 27
#define PassAction 28
#define Header 65
#define Tokdef 66
#define BLOCK 67
#define ALT 68
#define LABEL 69
#define OPT 70
#define POS_CLOSURE 71
#define CLOSURE 72
#define WILD 73
#define PRED_OP 74
#define BT 75
#define RULE 76
#define REFVAR 77
#define NonTerm 82
#define Token 83
#define ID 108
#define INT 109


#define zzSET_SIZE 16
#define zzTOKEN_COUNT 118



#ifdef __USE_PROTOS
void sordesc(AST**_root);
#else
extern void sordesc();
#endif

#ifdef __USE_PROTOS
void header(AST**_root);
#else
extern void header();
#endif

#ifdef __USE_PROTOS
void tokdef(AST**_root);
#else
extern void tokdef();
#endif

#ifdef __USE_PROTOS
void class_def(AST**_root);
#else
extern void class_def();
#endif

#ifdef __USE_PROTOS
void rule(AST**_root);
#else
extern void rule();
#endif

#ifdef __USE_PROTOS
void block(AST**_root,int no_copy);
#else
extern void block();
#endif

#ifdef __USE_PROTOS
void alt(AST**_root,int no_copy);
#else
extern void alt();
#endif

#ifdef __USE_PROTOS
void element(AST**_root,int no_copy);
#else
extern void element();
#endif

#ifdef __USE_PROTOS
void labeled_element(AST**_root,int no_copy);
#else
extern void labeled_element();
#endif

#ifdef __USE_PROTOS
void token(AST**_root,int no_copy);
#else
extern void token();
#endif

#ifdef __USE_PROTOS
void tree(AST**_root,int no_copy);
#else
extern void tree();
#endif

#ifdef __USE_PROTOS
void enum_file(AST**_root);
#else
extern void enum_file();
#endif

#ifdef __USE_PROTOS
void defines(AST**_root);
#else
extern void defines();
#endif

#ifdef __USE_PROTOS
void enum_def(AST**_root);
#else
extern void enum_def();
#endif

extern ANTLRChar *zztokens[zzTOKEN_COUNT /* 118 */];
extern SetWordType zzerr1[zzSET_SIZE];
extern SetWordType zzerr2[zzSET_SIZE];
extern SetWordType setwd1[zzTOKEN_COUNT];
extern SetWordType zzerr3[zzSET_SIZE];
extern SetWordType zzerr4[zzSET_SIZE];
extern SetWordType zzerr5[zzSET_SIZE];
extern SetWordType zzerr6[zzSET_SIZE];
extern SetWordType zzerr7[zzSET_SIZE];
extern SetWordType zzerr8[zzSET_SIZE];
extern SetWordType setwd2[zzTOKEN_COUNT];
extern SetWordType zzerr9[zzSET_SIZE];
extern SetWordType zzerr10[zzSET_SIZE];
extern SetWordType zzerr11[zzSET_SIZE];
extern SetWordType zzerr12[zzSET_SIZE];
extern SetWordType zzerr13[zzSET_SIZE];
extern SetWordType setwd3[zzTOKEN_COUNT];
extern SetWordType zzerr14[zzSET_SIZE];
extern SetWordType zzerr15[zzSET_SIZE];
extern SetWordType zzerr16[zzSET_SIZE];
extern SetWordType zzerr17[zzSET_SIZE];
extern SetWordType zzerr18[zzSET_SIZE];
extern SetWordType zzerr19[zzSET_SIZE];
extern SetWordType zzerr20[zzSET_SIZE];
extern SetWordType zzerr21[zzSET_SIZE];
extern SetWordType zzerr22[zzSET_SIZE];
extern SetWordType setwd4[zzTOKEN_COUNT];
extern SetWordType zzerr23[zzSET_SIZE];
extern SetWordType zzerr24[zzSET_SIZE];
extern SetWordType zzerr25[zzSET_SIZE];
extern SetWordType zzerr26[zzSET_SIZE];
extern SetWordType zzerr27[zzSET_SIZE];
extern SetWordType zzerr28[zzSET_SIZE];
extern SetWordType zzerr29[zzSET_SIZE];
extern SetWordType setwd5[zzTOKEN_COUNT];
extern SetWordType zzerr30[zzSET_SIZE];
extern SetWordType zzerr31[zzSET_SIZE];
extern SetWordType zzerr32[zzSET_SIZE];
extern SetWordType zzerr33[zzSET_SIZE];
extern SetWordType zzerr34[zzSET_SIZE];
extern SetWordType zzerr35[zzSET_SIZE];
extern SetWordType zzerr36[zzSET_SIZE];
extern SetWordType zzerr37[zzSET_SIZE];
extern SetWordType zzerr38[zzSET_SIZE];
extern SetWordType zzerr39[zzSET_SIZE];
extern SetWordType setwd6[zzTOKEN_COUNT];
extern SetWordType zzerr40[zzSET_SIZE];
extern SetWordType zzerr41[zzSET_SIZE];
extern SetWordType zzerr42[zzSET_SIZE];
extern SetWordType zzerr43[zzSET_SIZE];
extern SetWordType setwd7[zzTOKEN_COUNT];
extern SetWordType zzerr44[zzSET_SIZE];
extern SetWordType zzerr45[zzSET_SIZE];
extern SetWordType zzerr46[zzSET_SIZE];
extern SetWordType zzerr47[zzSET_SIZE];
extern SetWordType zzerr48[zzSET_SIZE];
extern SetWordType setwd8[zzTOKEN_COUNT];


#endif /* tokens_h */
