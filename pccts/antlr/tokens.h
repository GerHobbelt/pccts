#ifndef tokens_h
#define tokens_h
/* tokens.h -- List of labelled tokens and stuff
 *
 * Generated from: antlr.g
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * ANTLR Version 1.33MR33
 *
 *   ..\bin\antlr -emsvc -gh -ga -e3 antlr.g
 *
 */
#define zzEOF_TOKEN 1
#define Eof 1
#define QuotedTerm 2
#define Action 34
#define Pred 35
#define PassAction 36
#define WildCard 87
#define LABEL 89
#define Pragma 92
#define FirstSetSymbol 93
#define NonTerminal 100
#define TokenTerm 101
#define ID 148
#define INT 150


#define zzSET_SIZE 20
#define zzTOKEN_COUNT 157



#ifdef __USE_PROTOS
void grammar(void);
#else
extern void grammar();
#endif

#ifdef __USE_PROTOS
void class_def(void);
#else
extern void class_def();
#endif

#ifdef __USE_PROTOS
void rule(void);
#else
extern void rule();
#endif

#ifdef __USE_PROTOS
void laction(void);
#else
extern void laction();
#endif

#ifdef __USE_PROTOS
void lmember(void);
#else
extern void lmember();
#endif

#ifdef __USE_PROTOS
void lprefix(void);
#else
extern void lprefix();
#endif

#ifdef __USE_PROTOS
void aPred(void);
#else
extern void aPred();
#endif

#ifdef __USE_PROTOS
extern Predicate * predOrExpr(void);
#else
extern Predicate * predOrExpr();
#endif

#ifdef __USE_PROTOS
extern Predicate * predAndExpr(void);
#else
extern Predicate * predAndExpr();
#endif

#ifdef __USE_PROTOS
extern Predicate * predPrimary(void);
#else
extern Predicate * predPrimary();
#endif

#ifdef __USE_PROTOS
void aLexclass(void);
#else
extern void aLexclass();
#endif

#ifdef __USE_PROTOS
void error(void);
#else
extern void error();
#endif

#ifdef __USE_PROTOS
void tclass(void);
#else
extern void tclass();
#endif

#ifdef __USE_PROTOS
void token(void);
#else
extern void token();
#endif

#ifdef __USE_PROTOS
void block(set * toksrefd,set * rulesrefd);
#else
extern void block();
#endif

#ifdef __USE_PROTOS
void alt(set * toksrefd,set * rulesrefd);
#else
extern void alt();
#endif

#ifdef __USE_PROTOS
extern LabelEntry * element_label(void);
#else
extern LabelEntry * element_label();
#endif

#ifdef __USE_PROTOS
extern Node * element(int old_not,int first_on_line,int use_def_MT_handler);
#else
extern Node * element();
#endif

#ifdef __USE_PROTOS
void default_exception_handler(void);
#else
extern void default_exception_handler();
#endif

#ifdef __USE_PROTOS
extern ExceptionGroup * exception_group(void);
#else
extern ExceptionGroup * exception_group();
#endif

#ifdef __USE_PROTOS
extern ExceptionHandler * exception_handler(void);
#else
extern ExceptionHandler * exception_handler();
#endif

#ifdef __USE_PROTOS
void enum_file(char * fname);
#else
extern void enum_file();
#endif

#ifdef __USE_PROTOS
void defines(char * fname);
#else
extern void defines();
#endif

#ifdef __USE_PROTOS
void enum_def(char * fname);
#else
extern void enum_def();
#endif

extern ANTLRChar *zztokens[zzTOKEN_COUNT /* 157 */];
extern SetWordType zzerr1[zzSET_SIZE];
extern SetWordType zzerr2[zzSET_SIZE];
extern SetWordType zzerr3[zzSET_SIZE];
extern SetWordType zzerr4[zzSET_SIZE];
extern SetWordType setwd1[zzTOKEN_COUNT];
extern SetWordType zzerr5[zzSET_SIZE];
extern SetWordType zzerr6[zzSET_SIZE];
extern SetWordType zzerr7[zzSET_SIZE];
extern SetWordType zzerr8[zzSET_SIZE];
extern SetWordType zzerr9[zzSET_SIZE];
extern SetWordType setwd2[zzTOKEN_COUNT];
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
extern SetWordType setwd4[zzTOKEN_COUNT];
extern SetWordType zzerr22[zzSET_SIZE];
extern SetWordType zzerr23[zzSET_SIZE];
extern SetWordType zzerr24[zzSET_SIZE];
extern SetWordType zzerr25[zzSET_SIZE];
extern SetWordType zzerr26[zzSET_SIZE];
extern SetWordType setwd5[zzTOKEN_COUNT];
extern SetWordType zzerr27[zzSET_SIZE];
extern SetWordType zzerr28[zzSET_SIZE];
extern SetWordType zzerr29[zzSET_SIZE];
extern SetWordType zzerr30[zzSET_SIZE];
extern SetWordType zzerr31[zzSET_SIZE];
extern SetWordType zzerr32[zzSET_SIZE];
extern SetWordType zzerr33[zzSET_SIZE];
extern SetWordType setwd6[zzTOKEN_COUNT];
extern SetWordType zzerr34[zzSET_SIZE];
extern SetWordType zzerr35[zzSET_SIZE];
extern SetWordType zzerr36[zzSET_SIZE];
extern SetWordType zzerr37[zzSET_SIZE];
extern SetWordType zzerr38[zzSET_SIZE];
extern SetWordType zzerr39[zzSET_SIZE];
extern SetWordType zzerr40[zzSET_SIZE];
extern SetWordType zzerr41[zzSET_SIZE];
extern SetWordType zzerr42[zzSET_SIZE];
extern SetWordType setwd7[zzTOKEN_COUNT];
extern SetWordType zzerr43[zzSET_SIZE];
extern SetWordType zzerr44[zzSET_SIZE];
extern SetWordType zzerr45[zzSET_SIZE];
extern SetWordType zzerr46[zzSET_SIZE];
extern SetWordType zzerr47[zzSET_SIZE];
extern SetWordType zzerr48[zzSET_SIZE];
extern SetWordType zzerr49[zzSET_SIZE];
extern SetWordType zzerr50[zzSET_SIZE];
extern SetWordType zzerr51[zzSET_SIZE];
extern SetWordType zzerr52[zzSET_SIZE];
extern SetWordType zzerr53[zzSET_SIZE];
extern SetWordType setwd8[zzTOKEN_COUNT];
extern SetWordType zzerr54[zzSET_SIZE];
extern SetWordType zzerr55[zzSET_SIZE];
extern SetWordType zzerr56[zzSET_SIZE];
extern SetWordType zzerr57[zzSET_SIZE];
extern SetWordType setwd9[zzTOKEN_COUNT];
extern SetWordType zzerr58[zzSET_SIZE];
extern SetWordType zzerr59[zzSET_SIZE];
extern SetWordType zzerr60[zzSET_SIZE];
extern SetWordType zzerr61[zzSET_SIZE];
extern SetWordType zzerr62[zzSET_SIZE];
extern SetWordType zzerr63[zzSET_SIZE];
extern SetWordType zzerr64[zzSET_SIZE];
extern SetWordType zzerr65[zzSET_SIZE];
extern SetWordType setwd10[zzTOKEN_COUNT];
extern SetWordType zzerr66[zzSET_SIZE];
extern SetWordType setwd11[zzTOKEN_COUNT];


#endif /* tokens_h */
