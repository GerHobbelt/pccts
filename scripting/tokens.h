#ifndef tokens_h
#define tokens_h
/* tokens.h -- List of labelled tokens and stuff
 *
 * Generated from: script.g
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * ANTLR Version 1.33MR33
 *
 *   ..\pccts\bin\antlr -emsvc -gd -gs -gh -e3 -cr -ga -k 2 -tab 2 -w2 -gk -rl 2000 script.g
 *
 */
#define zzEOF_TOKEN 1
#define SCRIPT_EOF 1
#define ERROR_ITS_EOF_TOKEN 2
#define ERROR_ITC_TOKEN 3
#define UNARY_PLUS 4
#define UNARY_MINUS 5
#define INTEGER_SIZE 6
#define INCREMENT 7
#define DECREMENT 8
#define ANY 9
#define ARRAY 10
#define AS 11
#define BOOLEAN 12
#define BOOLEAN_FALSE 13
#define BOOLEAN_TRUE 14
#define BREAK 15
#define CONST 16
#define CONTINUE 17
#define DECLARATIONS 18
#define DEFINE 19
#define DEFINITIONS 20
#define DO 21
#define DONE 22
#define ELIF 23
#define ELSE 24
#define ENDIF 25
#define ENDSCRIPT 26
#define ENDSTRUCT 27
#define ENDSUB 28
#define GOTO 29
#define HALT 30
#define IF 31
#define IMPLEMENTATION 32
#define INTEGER 33
#define OF 34
#define REAL 35
#define REPEAT 36
#define RESET 37
#define RETURN 38
#define SCRIPT 39
#define STRING 40
#define STRUCT 41
#define SUBROUTINE 42
#define UNTIL 43
#define VOID 44
#define WHILE 45
#define BOOLEAN_AND 46
#define BOOLEAN_OR 47
#define BITWISE_AND 48
#define BITWISE_OR 49
#define BITWISE_XOR 50
#define END 51
#define BEGIN 52
#define ASSIGN 53
#define ASSIGN_PLUS 54
#define ASSIGN_MINUS 55
#define ASSIGN_MULTIPLY 56
#define ASSIGN_DIVIDE 57
#define ASSIGN_MODULO 58
#define ASSIGN_POWER 59
#define ASSIGN_LSHIFT 60
#define ASSIGN_RSHIFT 61
#define ASSIGN_BITWISE_OR 62
#define ASSIGN_BITWISE_AND 63
#define ASSIGN_BITWISE_XOR 64
#define ASSIGN_BOOLEAN_OR 65
#define ASSIGN_BOOLEAN_AND 66
#define LSHIFT 67
#define RSHIFT 68
#define GE 69
#define GT 70
#define EQ 71
#define LE 72
#define LT 73
#define NE 74
#define DIVIDE 75
#define MODULO 76
#define POWER 77
#define BITWISE_NOT 78
#define MINUS 79
#define PLUS 80
#define MULTIPLY 81
#define BOOLEAN_NOT 82
#define TRIPLE_DOT 83
#define LPARENS 84
#define RPARENS 85
#define LBRACKET 86
#define RBRACKET 87
#define COMMA 88
#define DOT 89
#define SEMICOLON 90
#define COLON 91
#define STRING_VALUE 92
#define BOGUS1 93
#define BOGUS2 94
#define BOGUS3 95
#define BOGUS4 96
#define BOGUS5 97
#define BOGUS6 98
#define BOGUS7 99
#define BOGUS8 100
#define BOGUS9 101
#define BOGUS10 102
#define BOGUS11 103
#define BOGUS12 104
#define ERROR_INVALID_ESC_SEQ 105
#define BOGUS14 106
#define BOGUS15 107
#define ERROR_ITS_TOKEN 108
#define COMMENTBLOCK 109
#define BOGUS17 110
#define BOGUS18 111
#define BOGUS19 112
#define CPPCOMMENTLINE 113
#define BOGUS20 114
#define INT_VALUE 115
#define REAL_VALUE 116
#define LIB_FUNCTION_ID 118
#define SUBROUTINE_ID 119
#define JUMPLABEL_ID 120
#define TYPEDEF_ID 121
#define VARIABLE 122
#define WHITESPACE 123
#define NEWLINE 124
#define BOGUS21 125
#define BOGUS22 126
#define BOGUS23 127
#define UNKNOWN_CHAR 128


#define zzSET_SIZE 20
#define zzTOKEN_COUNT 134



#ifdef __USE_PROTOS
void script(int *_retsignal);
#else
extern void script();
#endif

#ifdef __USE_PROTOS
void title(int *_retsignal);
#else
extern void title();
#endif

#ifdef __USE_PROTOS
void sections(int *_retsignal);
#else
extern void sections();
#endif

#ifdef __USE_PROTOS
void definitions(int *_retsignal);
#else
extern void definitions();
#endif

#ifdef __USE_PROTOS
void structdef(int *_retsignal);
#else
extern void structdef();
#endif

#ifdef __USE_PROTOS
void const_init_type_def(int *_retsignal);
#else
extern void const_init_type_def();
#endif

#ifdef __USE_PROTOS
void subroutine(int *_retsignal);
#else
extern void subroutine();
#endif

#ifdef __USE_PROTOS
void param_def_list(int *_retsignal);
#else
extern void param_def_list();
#endif

#ifdef __USE_PROTOS
void param_def(int *_retsignal);
#else
extern void param_def();
#endif

#ifdef __USE_PROTOS
void declarations(int *_retsignal);
#else
extern void declarations();
#endif

#ifdef __USE_PROTOS
void vardecl(int *_retsignal);
#else
extern void vardecl();
#endif

#ifdef __USE_PROTOS
void sub_param_type(int *_retsignal);
#else
extern void sub_param_type();
#endif

#ifdef __USE_PROTOS
void return_type(int *_retsignal);
#else
extern void return_type();
#endif

#ifdef __USE_PROTOS
void type(int *_retsignal);
#else
extern void type();
#endif

#ifdef __USE_PROTOS
void integer_type(int *_retsignal);
#else
extern void integer_type();
#endif

#ifdef __USE_PROTOS
void const_init_type(int *_retsignal);
#else
extern void const_init_type();
#endif

#ifdef __USE_PROTOS
void const_string_value(int *_retsignal);
#else
extern void const_string_value();
#endif

#ifdef __USE_PROTOS
void implementation(int *_retsignal);
#else
extern void implementation();
#endif

#ifdef __USE_PROTOS
void statement(int *_retsignal);
#else
extern void statement();
#endif

#ifdef __USE_PROTOS
void return_statement(int *_retsignal);
#else
extern void return_statement();
#endif

#ifdef __USE_PROTOS
void label_statement(int *_retsignal);
#else
extern void label_statement();
#endif

#ifdef __USE_PROTOS
void break_statement(int *_retsignal);
#else
extern void break_statement();
#endif

#ifdef __USE_PROTOS
void special_statement(int *_retsignal);
#else
extern void special_statement();
#endif

#ifdef __USE_PROTOS
void assignment_statement(int *_retsignal);
#else
extern void assignment_statement();
#endif

#ifdef __USE_PROTOS
void conditional_statement(int *_retsignal);
#else
extern void conditional_statement();
#endif

#ifdef __USE_PROTOS
void loop_statement(int *_retsignal);
#else
extern void loop_statement();
#endif

#ifdef __USE_PROTOS
void bracketed_conditional_expr(int *_retsignal);
#else
extern void bracketed_conditional_expr();
#endif

#ifdef __USE_PROTOS
void block_statement(int *_retsignal);
#else
extern void block_statement();
#endif

#ifdef __USE_PROTOS
void lvalue_expr(int *_retsignal);
#else
extern void lvalue_expr();
#endif

#ifdef __USE_PROTOS
void elemental_variable(int *_retsignal);
#else
extern void elemental_variable();
#endif

#ifdef __USE_PROTOS
void rvalue_expr(int *_retsignal);
#else
extern void rvalue_expr();
#endif

#ifdef __USE_PROTOS
void compare_or_rvalue_expr(int *_retsignal);
#else
extern void compare_or_rvalue_expr();
#endif

#ifdef __USE_PROTOS
void compare_and_rvalue_expr(int *_retsignal);
#else
extern void compare_and_rvalue_expr();
#endif

#ifdef __USE_PROTOS
void bitwise_or_rvalue_expr(int *_retsignal);
#else
extern void bitwise_or_rvalue_expr();
#endif

#ifdef __USE_PROTOS
void bitwise_xor_rvalue_expr(int *_retsignal);
#else
extern void bitwise_xor_rvalue_expr();
#endif

#ifdef __USE_PROTOS
void bitwise_and_rvalue_expr(int *_retsignal);
#else
extern void bitwise_and_rvalue_expr();
#endif

#ifdef __USE_PROTOS
void compare_ne_rvalue_expr(int *_retsignal);
#else
extern void compare_ne_rvalue_expr();
#endif

#ifdef __USE_PROTOS
void compare_eq_rvalue_expr(int *_retsignal);
#else
extern void compare_eq_rvalue_expr();
#endif

#ifdef __USE_PROTOS
void compare_ge_rvalue_expr(int *_retsignal);
#else
extern void compare_ge_rvalue_expr();
#endif

#ifdef __USE_PROTOS
void compare_gt_rvalue_expr(int *_retsignal);
#else
extern void compare_gt_rvalue_expr();
#endif

#ifdef __USE_PROTOS
void compare_le_rvalue_expr(int *_retsignal);
#else
extern void compare_le_rvalue_expr();
#endif

#ifdef __USE_PROTOS
void compare_lt_rvalue_expr(int *_retsignal);
#else
extern void compare_lt_rvalue_expr();
#endif

#ifdef __USE_PROTOS
void rshift_rvalue_expr(int *_retsignal);
#else
extern void rshift_rvalue_expr();
#endif

#ifdef __USE_PROTOS
void lshift_rvalue_expr(int *_retsignal);
#else
extern void lshift_rvalue_expr();
#endif

#ifdef __USE_PROTOS
void substract_rvalue_expr(int *_retsignal);
#else
extern void substract_rvalue_expr();
#endif

#ifdef __USE_PROTOS
void add_rvalue_expr(int *_retsignal);
#else
extern void add_rvalue_expr();
#endif

#ifdef __USE_PROTOS
void modulo_rvalue_expr(int *_retsignal);
#else
extern void modulo_rvalue_expr();
#endif

#ifdef __USE_PROTOS
void divide_rvalue_expr(int *_retsignal);
#else
extern void divide_rvalue_expr();
#endif

#ifdef __USE_PROTOS
void multiply_rvalue_expr(int *_retsignal);
#else
extern void multiply_rvalue_expr();
#endif

#ifdef __USE_PROTOS
void power_rvalue_expr(int *_retsignal);
#else
extern void power_rvalue_expr();
#endif

#ifdef __USE_PROTOS
void unary_rvalue_expr(int *_retsignal);
#else
extern void unary_rvalue_expr();
#endif

#ifdef __USE_PROTOS
void simple_rvalue_expr(int *_retsignal);
#else
extern void simple_rvalue_expr();
#endif

#ifdef __USE_PROTOS
void param_list(int *_retsignal);
#else
extern void param_list();
#endif

extern ANTLRChar *zztokens[zzTOKEN_COUNT /* 134 */];
extern SetWordType setwd1[zzTOKEN_COUNT];
extern SetWordType BOOLEAN_VALUE_set[zzSET_SIZE];
extern SetWordType BOOLEAN_VALUE_errset[zzSET_SIZE];
extern SetWordType setwd2[zzTOKEN_COUNT];
extern SetWordType ASSIGNMENT_set[zzSET_SIZE];
extern SetWordType ASSIGNMENT_errset[zzSET_SIZE];
extern SetWordType setwd3[zzTOKEN_COUNT];
extern SetWordType setwd4[zzTOKEN_COUNT];
extern SetWordType setwd5[zzTOKEN_COUNT];
extern SetWordType setwd6[zzTOKEN_COUNT];
extern SetWordType UNARY_OPERATOR_set[zzSET_SIZE];
extern SetWordType UNARY_OPERATOR_errset[zzSET_SIZE];
extern SetWordType zzerr7[zzSET_SIZE];
extern SetWordType zzerr8[zzSET_SIZE];
extern SetWordType zzerr9[zzSET_SIZE];
extern SetWordType zzerr10[zzSET_SIZE];
extern SetWordType zzerr11[zzSET_SIZE];
extern SetWordType zzerr12[zzSET_SIZE];
extern SetWordType zzerr13[zzSET_SIZE];
extern SetWordType zzerr14[zzSET_SIZE];
extern SetWordType setwd7[zzTOKEN_COUNT];
extern SetWordType BASIC_TYPES_set[zzSET_SIZE];


#endif /* tokens_h */
