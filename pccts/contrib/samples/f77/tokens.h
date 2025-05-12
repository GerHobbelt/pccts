#ifndef tokens_h
#define tokens_h
/* tokens.h -- List of labelled tokens and stuff
 *
 * Generated from: f77.g expr.g decl.g io.g
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * ANTLR Version 1.33MR33
 *
 *   ..\..\..\bin\antlr.exe -emsvc -k 2 -glms -gh -ga -gt f77.g expr.g decl.g io.g
 *
 */
#define zzEOF_TOKEN 1
#define SKIP_TOKEN 2
#define INVALID 3
#define FILEKEYWORD 4
#define CONTINUATION_LINE 6
#define BLANK_LINE 7
#define ERROR_WHITESPACE_LABEL 8
#define LABEL 10
#define ERROR_LABEL_TOKEN 11
#define CONTROL_IMAGE 12
#define CONTROL_IMAGE_ERROR 13
#define BLOCK_IF 14
#define ARITHMETIC_IF 15
#define LOGICAL_IF 16
#define IF 17
#define ELSE_IF 18
#define ELSE 19
#define END_IF 20
#define END 21
#define STOP 22
#define REAL 23
#define DOUBLE_PRECISION 24
#define LOGICAL 25
#define INTEGER 26
#define CHARACTER 27
#define COMPLEX 28
#define DOUBLE_COMPLEX 29
#define IMPLICIT 30
#define COMMON 31
#define DATA 32
#define DO 33
#define CONTINUE 34
#define CALL 35
#define SUBROUTINE 36
#define FUNCTION 37
#define GO_TO 38
#define UNCONDITIONAL_GOTO 39
#define COMPUTED_GOTO 40
#define ASSIGNED_GOTO 41
#define RETURN 42
#define EXTERNAL 43
#define INTRINSIC 44
#define SAVE 45
#define ENTRY 46
#define PARAMETER 47
#define FORMAT 48
#define INQUIRE 49
#define BACKSPACE 50
#define ENDFILE 51
#define REWIND 52
#define BLOCK_GLOBALS 53
#define EXPORT 54
#define CHANGE 55
#define OPEN 56
#define CLOSE 57
#define DIMENSION 58
#define EQUIVALENCE 59
#define ASSIGN 60
#define LIBRARY 61
#define WRITE 62
#define READ 63
#define FIND 64
#define KEYWORD_UNDEFINED 66
#define ASSIGNMENT 67
#define COMMENT_LINE 70
#define TRAILING_COMMENT 71
#define WHITESPACE 72
#define EQUAL 73
#define POW 74
#define STAR 75
#define MUL 76
#define MIN 77
#define PLU 78
#define UNARY_PLU 79
#define UNARY_MIN 80
#define CONCAT 81
#define DIV 82
#define AMPERSAND 83
#define COLUMN 84
#define SEMICOLUMN 85
#define IMPLIED_DO_VARIABLE 86
#define IMPLIED_LP 87
#define IMPLIED_RP 88
#define IO_SPEC_LP 89
#define IO_SPEC_RP 90
#define LP 91
#define RP 92
#define COMMA 93
#define EOL 94
#define HOLLERITH_CONST 95
#define T_FALSE 96
#define T_TRUE 97
#define AND 98
#define OR 99
#define NEQV 100
#define EQV 101
#define NOT 102
#define LT 103
#define LE 104
#define EQ 105
#define NE 106
#define GT 107
#define GE 108
#define IS 109
#define HEX_CONST 110
#define BASIC_REAL 111
#define REAL_EXPO 113
#define SOME_CONSTINTEGER 114
#define CONSTANT_NAME 115
#define CONSTINT 116
#define CONSTINT_ERROR 117
#define SEQUENCE 118
#define QUOTED_STRING 120
#define APOSTROPHY 121
#define TO 122
#define PAGE 123
#define SET 124
#define LIST 125
#define XREF 126
#define ERRLIST 127
#define LINEINFO 128
#define NEW 129
#define RESET 130
#define OWN 131
#define CHARS 132
#define STACK 133
#define FREE 134
#define POP 135
#define INCLUDE 136
#define FILE_WORD 155
#define THEN 156
#define LIBPARAMETER 157
#define FUNCTIONNAME 158
#define KIND 159
#define TITLE 160
#define FILETYPE 161
#define NEWFILE 162
#define MYUSE 163
#define MAXRECSIZE 164
#define SAVEFACTOR 165
#define BLOCKSIZE 166
#define SECURITYTYPE 167
#define AREAS 168
#define AREASIZE 169
#define PROTECTION 170
#define UNITS 171
#define UPDATEFILE 172
#define STATUS 173
#define FMT 174
#define RECL 175
#define REC 176
#define ERR 177
#define IOSTAT 178
#define URGENT 179
#define IO_DATA 180
#define NUMBER 181
#define NEXTREC 182
#define EXIST 183
#define OPENED 184
#define NAMED 185
#define RECORD 186
#define NAME 187
#define DISP 188
#define SUBFILE 189
#define OPENTYPE 190
#define RESIDENT 191
#define ACCESS 192
#define SEQUENTIAL 193
#define DIRECT 194
#define UNFORMATTED 195
#define FORMATTED 196
#define FORM 197
#define BLANK 198
#define IDENTIFIER 199
#define ARRAY_NAME 200
#define INTEGER_ID 201
#define INTEGER_ARRAY_ID 202
#define REAL_ID 203
#define REAL_ARRAY_ID 204
#define DOUBLE_PRECISION_ID 205
#define DOUBLE_PRECISION_ARRAY_ID 206
#define CHARACTER_ID 207
#define CHARACTER_ARRAY_ID 208
#define CHARACTER_SUBSTRING 209
#define LOGICAL_ID 210
#define LOGICAL_ARRAY_ID 211
#define COMPLEX_ID 212
#define DOUBLE_COMPLEX_ID 213
#define FUNCTION_NAME 214
#define SUBROUTINE_NAME 215
#define INTRINSIC_NAME 216
#define FIELD_WIDTH 217
#define DECIMAL_PLACES 218
#define EXPONENT_DIGITS 219
#define MIN_DIG_REQUIRED 220
#define REPEAT_COUNT 221
#define SCALE_FACTOR 222
#define DEC_POINT 226
#define TR 228
#define TL 229
#define T 230
#define X 231
#define SLASH 232
#define SP 233
#define SS 234
#define S 235
#define P 236
#define BN 237
#define BZ 238
#define I 239
#define J 240
#define F 241
#define E 242
#define D 243
#define G 244
#define O 245
#define L 246
#define A 247
#define Z 248
#define U 249
#define K 250
#define DOLLAR_EDITING 251
#define UNIT 257
#define INT_CONST 258
#define QUATED_STRING 259


#define zzSET_SIZE 36
#define zzTOKEN_COUNT 260



#ifdef __USE_PROTOS
void program(AST**_root);
#else
extern void program();
#endif

#ifdef __USE_PROTOS
void source_line(AST**_root);
#else
extern void source_line();
#endif

#ifdef __USE_PROTOS
void comment_line(AST**_root);
#else
extern void comment_line();
#endif

#ifdef __USE_PROTOS
void blank_line(AST**_root);
#else
extern void blank_line();
#endif

#ifdef __USE_PROTOS
void control_image(AST**_root);
#else
extern void control_image();
#endif

#ifdef __USE_PROTOS
void option_phrase(AST**_root);
#else
extern void option_phrase();
#endif

#ifdef __USE_PROTOS
void set_phrase(AST**_root);
#else
extern void set_phrase();
#endif

#ifdef __USE_PROTOS
void pop_phrase(AST**_root);
#else
extern void pop_phrase();
#endif

#ifdef __USE_PROTOS
void reset_phrase(AST**_root);
#else
extern void reset_phrase();
#endif

#ifdef __USE_PROTOS
void include_phrase(AST**_root);
#else
extern void include_phrase();
#endif

#ifdef __USE_PROTOS
void option(AST**_root);
#else
extern void option();
#endif

#ifdef __USE_PROTOS
void statement(AST**_root);
#else
extern void statement();
#endif

#ifdef __USE_PROTOS
void statement1(AST**_root);
#else
extern void statement1();
#endif

#ifdef __USE_PROTOS
void statement2(AST**_root);
#else
extern void statement2();
#endif

#ifdef __USE_PROTOS
void file_statement(AST**_root);
#else
extern void file_statement();
#endif

#ifdef __USE_PROTOS
void file_item(AST**_root);
#else
extern void file_item();
#endif

#ifdef __USE_PROTOS
void file_name(AST**_root);
#else
extern void file_name();
#endif

#ifdef __USE_PROTOS
void equivalence_statement(AST**_root);
#else
extern void equivalence_statement();
#endif

#ifdef __USE_PROTOS
void equiv_item(AST**_root);
#else
extern void equiv_item();
#endif

#ifdef __USE_PROTOS
void equiv_entity(AST**_root);
#else
extern void equiv_entity();
#endif

#ifdef __USE_PROTOS
void length_spec(AST**_root);
#else
extern void length_spec();
#endif

#ifdef __USE_PROTOS
void common_statement(AST**_root);
#else
extern void common_statement();
#endif

#ifdef __USE_PROTOS
void block_item(AST**_root);
#else
extern void block_item();
#endif

#ifdef __USE_PROTOS
void data_statement(AST**_root);
#else
extern void data_statement();
#endif

#ifdef __USE_PROTOS
void data_list(AST**_root);
#else
extern void data_list();
#endif

#ifdef __USE_PROTOS
void data_item(AST**_root);
#else
extern void data_item();
#endif

#ifdef __USE_PROTOS
void data_var_list(AST**_root);
#else
extern void data_var_list();
#endif

#ifdef __USE_PROTOS
void data_var_list_elem(AST**_root);
#else
extern void data_var_list_elem();
#endif

#ifdef __USE_PROTOS
void data_const_list(AST**_root);
#else
extern void data_const_list();
#endif

#ifdef __USE_PROTOS
void data_constant(AST**_root);
#else
extern void data_constant();
#endif

#ifdef __USE_PROTOS
void data_implied_do_list(AST**_root);
#else
extern void data_implied_do_list();
#endif

#ifdef __USE_PROTOS
void implied_do_variable(AST**_root);
#else
extern void implied_do_variable();
#endif

#ifdef __USE_PROTOS
void do_statement(AST**_root);
#else
extern void do_statement();
#endif

#ifdef __USE_PROTOS
void do_variable(AST**_root);
#else
extern void do_variable();
#endif

#ifdef __USE_PROTOS
void initial(AST**_root);
#else
extern void initial();
#endif

#ifdef __USE_PROTOS
void terminal(AST**_root);
#else
extern void terminal();
#endif

#ifdef __USE_PROTOS
void incremental(AST**_root);
#else
extern void incremental();
#endif

#ifdef __USE_PROTOS
void continue_statement(AST**_root);
#else
extern void continue_statement();
#endif

#ifdef __USE_PROTOS
void call_statement(AST**_root);
#else
extern void call_statement();
#endif

#ifdef __USE_PROTOS
void call_arg_list(AST**_root);
#else
extern void call_arg_list();
#endif

#ifdef __USE_PROTOS
void call_arg_item(AST**_root);
#else
extern void call_arg_item();
#endif

#ifdef __USE_PROTOS
void statement_label(AST**_root);
#else
extern void statement_label();
#endif

#ifdef __USE_PROTOS
void if_statement(AST**_root);
#else
extern void if_statement();
#endif

#ifdef __USE_PROTOS
void block_if_statement(AST**_root);
#else
extern void block_if_statement();
#endif

#ifdef __USE_PROTOS
void logical_if_statement(AST**_root);
#else
extern void logical_if_statement();
#endif

#ifdef __USE_PROTOS
void arithmetic_if_statement(AST**_root);
#else
extern void arithmetic_if_statement();
#endif

#ifdef __USE_PROTOS
void statement_block(AST**_root);
#else
extern void statement_block();
#endif

#ifdef __USE_PROTOS
void executable_statement(AST**_root);
#else
extern void executable_statement();
#endif

#ifdef __USE_PROTOS
void assignment_statement(AST**_root);
#else
extern void assignment_statement();
#endif

#ifdef __USE_PROTOS
void function_call(AST**_root);
#else
extern void function_call();
#endif

#ifdef __USE_PROTOS
void actual_argument_list(AST**_root);
#else
extern void actual_argument_list();
#endif

#ifdef __USE_PROTOS
void actual_argument(AST**_root);
#else
extern void actual_argument();
#endif

#ifdef __USE_PROTOS
void end_statement(AST**_root);
#else
extern void end_statement();
#endif

#ifdef __USE_PROTOS
void stop_statement(AST**_root);
#else
extern void stop_statement();
#endif

#ifdef __USE_PROTOS
void return_statement(AST**_root);
#else
extern void return_statement();
#endif

#ifdef __USE_PROTOS
void block_globals_statement(AST**_root);
#else
extern void block_globals_statement();
#endif

#ifdef __USE_PROTOS
void export_statement(AST**_root);
#else
extern void export_statement();
#endif

#ifdef __USE_PROTOS
void export_item(AST**_root);
#else
extern void export_item();
#endif

#ifdef __USE_PROTOS
void subroutine_statement(AST**_root);
#else
extern void subroutine_statement();
#endif

#ifdef __USE_PROTOS
void sub_arg_list(AST**_root);
#else
extern void sub_arg_list();
#endif

#ifdef __USE_PROTOS
void sub_argument(AST**_root);
#else
extern void sub_argument();
#endif

#ifdef __USE_PROTOS
void formal_argument(AST**_root);
#else
extern void formal_argument();
#endif

#ifdef __USE_PROTOS
void function_statement(AST**_root);
#else
extern void function_statement();
#endif

#ifdef __USE_PROTOS
extern int function_type(AST**_root);
#else
extern int function_type();
#endif

#ifdef __USE_PROTOS
void function_arg_list(AST**_root);
#else
extern void function_arg_list();
#endif

#ifdef __USE_PROTOS
void entry_statement(AST**_root);
#else
extern void entry_statement();
#endif

#ifdef __USE_PROTOS
void goto_statement(AST**_root);
#else
extern void goto_statement();
#endif

#ifdef __USE_PROTOS
void unconditional_goto_statement(AST**_root);
#else
extern void unconditional_goto_statement();
#endif

#ifdef __USE_PROTOS
void computed_goto_statement(AST**_root);
#else
extern void computed_goto_statement();
#endif

#ifdef __USE_PROTOS
void assigned_goto_statement(AST**_root);
#else
extern void assigned_goto_statement();
#endif

#ifdef __USE_PROTOS
void library_statement(AST**_root);
#else
extern void library_statement();
#endif

#ifdef __USE_PROTOS
void label(AST**_root);
#else
extern void label();
#endif

#ifdef __USE_PROTOS
void repeat_count(AST**_root);
#else
extern void repeat_count();
#endif

#ifdef __USE_PROTOS
void arithm_operator(AST**_root);
#else
extern void arithm_operator();
#endif

#ifdef __USE_PROTOS
void logical_operator(AST**_root);
#else
extern void logical_operator();
#endif

#ifdef __USE_PROTOS
void relational_operator(AST**_root);
#else
extern void relational_operator();
#endif

#ifdef __USE_PROTOS
extern int constant(AST**_root);
#else
extern int constant();
#endif

#ifdef __USE_PROTOS
void arithm_const(AST**_root);
#else
extern void arithm_const();
#endif

#ifdef __USE_PROTOS
void real_const(AST**_root);
#else
extern void real_const();
#endif

#ifdef __USE_PROTOS
void int_const(AST**_root);
#else
extern void int_const();
#endif

#ifdef __USE_PROTOS
void logical_const(AST**_root);
#else
extern void logical_const();
#endif

#ifdef __USE_PROTOS
void char_const(AST**_root);
#else
extern void char_const();
#endif

#ifdef __USE_PROTOS
void hollerith_editing(AST**_root);
#else
extern void hollerith_editing();
#endif

#ifdef __USE_PROTOS
void quote_editinig(AST**_root);
#else
extern void quote_editinig();
#endif

#ifdef __USE_PROTOS
void tr_editing(AST**_root);
#else
extern void tr_editing();
#endif

#ifdef __USE_PROTOS
void tl_editing(AST**_root);
#else
extern void tl_editing();
#endif

#ifdef __USE_PROTOS
void t_editing(AST**_root);
#else
extern void t_editing();
#endif

#ifdef __USE_PROTOS
void x_editing(AST**_root);
#else
extern void x_editing();
#endif

#ifdef __USE_PROTOS
void colon_editing(AST**_root);
#else
extern void colon_editing();
#endif

#ifdef __USE_PROTOS
void sp_editing(AST**_root);
#else
extern void sp_editing();
#endif

#ifdef __USE_PROTOS
void ss_editing(AST**_root);
#else
extern void ss_editing();
#endif

#ifdef __USE_PROTOS
void s_editing(AST**_root);
#else
extern void s_editing();
#endif

#ifdef __USE_PROTOS
void p_editing(AST**_root);
#else
extern void p_editing();
#endif

#ifdef __USE_PROTOS
void bn_editing(AST**_root);
#else
extern void bn_editing();
#endif

#ifdef __USE_PROTOS
void bz_editing(AST**_root);
#else
extern void bz_editing();
#endif

#ifdef __USE_PROTOS
void i_editing(AST**_root);
#else
extern void i_editing();
#endif

#ifdef __USE_PROTOS
void j_editing(AST**_root);
#else
extern void j_editing();
#endif

#ifdef __USE_PROTOS
void f_editing(AST**_root);
#else
extern void f_editing();
#endif

#ifdef __USE_PROTOS
void e_editing(AST**_root);
#else
extern void e_editing();
#endif

#ifdef __USE_PROTOS
void short_e_editing(AST**_root);
#else
extern void short_e_editing();
#endif

#ifdef __USE_PROTOS
void d_editing(AST**_root);
#else
extern void d_editing();
#endif

#ifdef __USE_PROTOS
void g_editing(AST**_root);
#else
extern void g_editing();
#endif

#ifdef __USE_PROTOS
void short_g_editing(AST**_root);
#else
extern void short_g_editing();
#endif

#ifdef __USE_PROTOS
void o_editing(AST**_root);
#else
extern void o_editing();
#endif

#ifdef __USE_PROTOS
void l_editing(AST**_root);
#else
extern void l_editing();
#endif

#ifdef __USE_PROTOS
void a_editing(AST**_root);
#else
extern void a_editing();
#endif

#ifdef __USE_PROTOS
void z_editing(AST**_root);
#else
extern void z_editing();
#endif

#ifdef __USE_PROTOS
void u_editing(AST**_root);
#else
extern void u_editing();
#endif

#ifdef __USE_PROTOS
void field_width(AST**_root);
#else
extern void field_width();
#endif

#ifdef __USE_PROTOS
void min_dig_required(AST**_root);
#else
extern void min_dig_required();
#endif

#ifdef __USE_PROTOS
void decimal_places(AST**_root);
#else
extern void decimal_places();
#endif

#ifdef __USE_PROTOS
void exponent_digits(AST**_root);
#else
extern void exponent_digits();
#endif

#ifdef __USE_PROTOS
extern int expression(AST**_root);
#else
extern int expression();
#endif

#ifdef __USE_PROTOS
void expr0(AST**_root);
#else
extern void expr0();
#endif

#ifdef __USE_PROTOS
void expr1(AST**_root);
#else
extern void expr1();
#endif

#ifdef __USE_PROTOS
void expr2(AST**_root);
#else
extern void expr2();
#endif

#ifdef __USE_PROTOS
extern int operand(AST**_root);
#else
extern int operand();
#endif

#ifdef __USE_PROTOS
void real_statement(AST**_root);
#else
extern void real_statement();
#endif

#ifdef __USE_PROTOS
void real_item(AST**_root);
#else
extern void real_item();
#endif

#ifdef __USE_PROTOS
void init_real_item(AST**_root);
#else
extern void init_real_item();
#endif

#ifdef __USE_PROTOS
void uninit_real_item(AST**_root);
#else
extern void uninit_real_item();
#endif

#ifdef __USE_PROTOS
void real_var_list(AST**_root);
#else
extern void real_var_list();
#endif

#ifdef __USE_PROTOS
void real_const_list(AST**_root);
#else
extern void real_const_list();
#endif

#ifdef __USE_PROTOS
void var_decl(AST**_root,int type);
#else
extern void var_decl();
#endif

#ifdef __USE_PROTOS
void array_declarer(AST**_root,int type);
#else
extern void array_declarer();
#endif

#ifdef __USE_PROTOS
void dimension_declarator(AST**_root);
#else
extern void dimension_declarator();
#endif

#ifdef __USE_PROTOS
void lower_bound(AST**_root);
#else
extern void lower_bound();
#endif

#ifdef __USE_PROTOS
void upper_bound(AST**_root);
#else
extern void upper_bound();
#endif

#ifdef __USE_PROTOS
void variable(AST**_root,int where);
#else
extern void variable();
#endif

#ifdef __USE_PROTOS
void array_element_reference(AST**_root,int where);
#else
extern void array_element_reference();
#endif

#ifdef __USE_PROTOS
void double_precision_statement(AST**_root);
#else
extern void double_precision_statement();
#endif

#ifdef __USE_PROTOS
void double_prec_item(AST**_root);
#else
extern void double_prec_item();
#endif

#ifdef __USE_PROTOS
void init_double_prec_item(AST**_root);
#else
extern void init_double_prec_item();
#endif

#ifdef __USE_PROTOS
void uninit_double_prec_item(AST**_root);
#else
extern void uninit_double_prec_item();
#endif

#ifdef __USE_PROTOS
void double_prec_var_list(AST**_root);
#else
extern void double_prec_var_list();
#endif

#ifdef __USE_PROTOS
void double_prec_const_list(AST**_root);
#else
extern void double_prec_const_list();
#endif

#ifdef __USE_PROTOS
void integer_statement(AST**_root);
#else
extern void integer_statement();
#endif

#ifdef __USE_PROTOS
void int_item(AST**_root);
#else
extern void int_item();
#endif

#ifdef __USE_PROTOS
void init_int_item(AST**_root);
#else
extern void init_int_item();
#endif

#ifdef __USE_PROTOS
void uninit_int_item(AST**_root);
#else
extern void uninit_int_item();
#endif

#ifdef __USE_PROTOS
void int_var_list(AST**_root);
#else
extern void int_var_list();
#endif

#ifdef __USE_PROTOS
void int_const_list(AST**_root);
#else
extern void int_const_list();
#endif

#ifdef __USE_PROTOS
void dimension_statement(AST**_root);
#else
extern void dimension_statement();
#endif

#ifdef __USE_PROTOS
void logical_statement(AST**_root);
#else
extern void logical_statement();
#endif

#ifdef __USE_PROTOS
void log_item(AST**_root);
#else
extern void log_item();
#endif

#ifdef __USE_PROTOS
void init_log_item(AST**_root);
#else
extern void init_log_item();
#endif

#ifdef __USE_PROTOS
void uninit_log_item(AST**_root);
#else
extern void uninit_log_item();
#endif

#ifdef __USE_PROTOS
void log_var_list(AST**_root);
#else
extern void log_var_list();
#endif

#ifdef __USE_PROTOS
void log_const_list(AST**_root);
#else
extern void log_const_list();
#endif

#ifdef __USE_PROTOS
void character_statement(AST**_root);
#else
extern void character_statement();
#endif

#ifdef __USE_PROTOS
void char_item(AST**_root);
#else
extern void char_item();
#endif

#ifdef __USE_PROTOS
void init_char_item(AST**_root);
#else
extern void init_char_item();
#endif

#ifdef __USE_PROTOS
void uninit_char_item(AST**_root);
#else
extern void uninit_char_item();
#endif

#ifdef __USE_PROTOS
void char_var_list(AST**_root);
#else
extern void char_var_list();
#endif

#ifdef __USE_PROTOS
void char_const_list(AST**_root);
#else
extern void char_const_list();
#endif

#ifdef __USE_PROTOS
void substring(AST**_root);
#else
extern void substring();
#endif

#ifdef __USE_PROTOS
void external_statement(AST**_root);
#else
extern void external_statement();
#endif

#ifdef __USE_PROTOS
void function_name(AST**_root);
#else
extern void function_name();
#endif

#ifdef __USE_PROTOS
void intrinsic_statement(AST**_root);
#else
extern void intrinsic_statement();
#endif

#ifdef __USE_PROTOS
void save_statement(AST**_root);
#else
extern void save_statement();
#endif

#ifdef __USE_PROTOS
void save_item(AST**_root);
#else
extern void save_item();
#endif

#ifdef __USE_PROTOS
void implicit_statement(AST**_root);
#else
extern void implicit_statement();
#endif

#ifdef __USE_PROTOS
void implicit_item(AST**_root);
#else
extern void implicit_item();
#endif

#ifdef __USE_PROTOS
void implicit_type(AST**_root);
#else
extern void implicit_type();
#endif

#ifdef __USE_PROTOS
void letter_spec(AST**_root);
#else
extern void letter_spec();
#endif

#ifdef __USE_PROTOS
void parameter_statement(AST**_root);
#else
extern void parameter_statement();
#endif

#ifdef __USE_PROTOS
void para_item(AST**_root);
#else
extern void para_item();
#endif

#ifdef __USE_PROTOS
void assign_statement(AST**_root);
#else
extern void assign_statement();
#endif

#ifdef __USE_PROTOS
void read_statement(AST**_root);
#else
extern void read_statement();
#endif

#ifdef __USE_PROTOS
void write_statement(AST**_root);
#else
extern void write_statement();
#endif

#ifdef __USE_PROTOS
void control_info(AST**_root);
#else
extern void control_info();
#endif

#ifdef __USE_PROTOS
void unit_identifier(AST**_root);
#else
extern void unit_identifier();
#endif

#ifdef __USE_PROTOS
void format_identifier(AST**_root);
#else
extern void format_identifier();
#endif

#ifdef __USE_PROTOS
void combined_expression(AST**_root);
#else
extern void combined_expression();
#endif

#ifdef __USE_PROTOS
void io_list(AST**_root,int where);
#else
extern void io_list();
#endif

#ifdef __USE_PROTOS
void io_list_item(AST**_root,int where);
#else
extern void io_list_item();
#endif

#ifdef __USE_PROTOS
void io_implied_do_list(AST**_root,int where);
#else
extern void io_implied_do_list();
#endif

#ifdef __USE_PROTOS
void io_implied_do_loop(AST**_root,int where);
#else
extern void io_implied_do_loop();
#endif

#ifdef __USE_PROTOS
void find_statement(AST**_root);
#else
extern void find_statement();
#endif

#ifdef __USE_PROTOS
void findlist(AST**_root);
#else
extern void findlist();
#endif

#ifdef __USE_PROTOS
void open_statement(AST**_root);
#else
extern void open_statement();
#endif

#ifdef __USE_PROTOS
void open_item(AST**_root);
#else
extern void open_item();
#endif

#ifdef __USE_PROTOS
void close_statement(AST**_root);
#else
extern void close_statement();
#endif

#ifdef __USE_PROTOS
void close_item(AST**_root);
#else
extern void close_item();
#endif

#ifdef __USE_PROTOS
void close_name(AST**_root);
#else
extern void close_name();
#endif

#ifdef __USE_PROTOS
void inquire_statement(AST**_root);
#else
extern void inquire_statement();
#endif

#ifdef __USE_PROTOS
void inquire_item(AST**_root);
#else
extern void inquire_item();
#endif

#ifdef __USE_PROTOS
void inquire_name(AST**_root);
#else
extern void inquire_name();
#endif

#ifdef __USE_PROTOS
void backspace_statement(AST**_root);
#else
extern void backspace_statement();
#endif

#ifdef __USE_PROTOS
void endfile_statement(AST**_root);
#else
extern void endfile_statement();
#endif

#ifdef __USE_PROTOS
void rewind_statement(AST**_root);
#else
extern void rewind_statement();
#endif

#ifdef __USE_PROTOS
void io_specifier(AST**_root);
#else
extern void io_specifier();
#endif

#ifdef __USE_PROTOS
void change_statement(AST**_root);
#else
extern void change_statement();
#endif

#ifdef __USE_PROTOS
void change_item(AST**_root);
#else
extern void change_item();
#endif

#ifdef __USE_PROTOS
void file_clist(AST**_root);
#else
extern void file_clist();
#endif

#ifdef __USE_PROTOS
void library_id(AST**_root);
#else
extern void library_id();
#endif

#ifdef __USE_PROTOS
void library_clist(AST**_root);
#else
extern void library_clist();
#endif

#ifdef __USE_PROTOS
void change_file_specifier(AST**_root);
#else
extern void change_file_specifier();
#endif

#ifdef __USE_PROTOS
void format_statement(AST**_root);
#else
extern void format_statement();
#endif

#ifdef __USE_PROTOS
void format_specification(AST**_root);
#else
extern void format_specification();
#endif

#ifdef __USE_PROTOS
void format_specifier(AST**_root);
#else
extern void format_specifier();
#endif

extern ANTLRChar *zztokens[zzTOKEN_COUNT /* 260 */];
extern SetWordType zzerr1[zzSET_SIZE];
extern SetWordType setwd1[zzTOKEN_COUNT];
extern SetWordType zzerr2[zzSET_SIZE];
extern SetWordType zzerr3[zzSET_SIZE];
extern SetWordType zzerr4[zzSET_SIZE];
extern SetWordType setwd2[zzTOKEN_COUNT];
extern SetWordType zzerr5[zzSET_SIZE];
extern SetWordType zzerr6[zzSET_SIZE];
extern SetWordType zzerr7[zzSET_SIZE];
extern SetWordType setwd3[zzTOKEN_COUNT];
extern SetWordType setwd4[zzTOKEN_COUNT];
extern SetWordType setwd5[zzTOKEN_COUNT];
extern SetWordType setwd6[zzTOKEN_COUNT];
extern SetWordType setwd7[zzTOKEN_COUNT];
extern SetWordType zzerr8[zzSET_SIZE];
extern SetWordType zzerr9[zzSET_SIZE];
extern SetWordType setwd8[zzTOKEN_COUNT];
extern SetWordType setwd9[zzTOKEN_COUNT];
extern SetWordType setwd10[zzTOKEN_COUNT];
extern SetWordType setwd11[zzTOKEN_COUNT];
extern SetWordType setwd12[zzTOKEN_COUNT];
extern SetWordType zzerr10[zzSET_SIZE];
extern SetWordType zzerr11[zzSET_SIZE];
extern SetWordType setwd13[zzTOKEN_COUNT];
extern SetWordType zzerr12[zzSET_SIZE];
extern SetWordType zzerr13[zzSET_SIZE];
extern SetWordType zzerr14[zzSET_SIZE];
extern SetWordType zzerr15[zzSET_SIZE];
extern SetWordType zzerr16[zzSET_SIZE];
extern SetWordType zzerr17[zzSET_SIZE];
extern SetWordType zzerr18[zzSET_SIZE];
extern SetWordType setwd14[zzTOKEN_COUNT];
extern SetWordType zzerr19[zzSET_SIZE];
extern SetWordType zzerr20[zzSET_SIZE];
extern SetWordType zzerr21[zzSET_SIZE];
extern SetWordType zzerr22[zzSET_SIZE];
extern SetWordType setwd15[zzTOKEN_COUNT];
extern SetWordType zzerr23[zzSET_SIZE];
extern SetWordType zzerr24[zzSET_SIZE];
extern SetWordType zzerr25[zzSET_SIZE];
extern SetWordType zzerr26[zzSET_SIZE];
extern SetWordType zzerr27[zzSET_SIZE];
extern SetWordType zzerr28[zzSET_SIZE];
extern SetWordType setwd16[zzTOKEN_COUNT];
extern SetWordType zzerr29[zzSET_SIZE];
extern SetWordType zzerr30[zzSET_SIZE];
extern SetWordType zzerr31[zzSET_SIZE];
extern SetWordType zzerr32[zzSET_SIZE];
extern SetWordType zzerr33[zzSET_SIZE];
extern SetWordType setwd17[zzTOKEN_COUNT];
extern SetWordType zzerr34[zzSET_SIZE];
extern SetWordType zzerr35[zzSET_SIZE];
extern SetWordType zzerr36[zzSET_SIZE];
extern SetWordType zzerr37[zzSET_SIZE];
extern SetWordType zzerr38[zzSET_SIZE];
extern SetWordType setwd18[zzTOKEN_COUNT];
extern SetWordType zzerr39[zzSET_SIZE];
extern SetWordType zzerr40[zzSET_SIZE];
extern SetWordType zzerr41[zzSET_SIZE];
extern SetWordType zzerr42[zzSET_SIZE];
extern SetWordType zzerr43[zzSET_SIZE];
extern SetWordType setwd19[zzTOKEN_COUNT];
extern SetWordType zzerr44[zzSET_SIZE];
extern SetWordType zzerr45[zzSET_SIZE];
extern SetWordType zzerr46[zzSET_SIZE];
extern SetWordType zzerr47[zzSET_SIZE];
extern SetWordType zzerr48[zzSET_SIZE];
extern SetWordType zzerr49[zzSET_SIZE];
extern SetWordType setwd20[zzTOKEN_COUNT];
extern SetWordType setwd21[zzTOKEN_COUNT];
extern SetWordType setwd22[zzTOKEN_COUNT];
extern SetWordType setwd23[zzTOKEN_COUNT];
extern SetWordType setwd24[zzTOKEN_COUNT];
extern SetWordType zzerr50[zzSET_SIZE];
extern SetWordType zzerr51[zzSET_SIZE];
extern SetWordType setwd25[zzTOKEN_COUNT];
extern SetWordType setwd26[zzTOKEN_COUNT];
extern SetWordType setwd27[zzTOKEN_COUNT];
extern SetWordType setwd28[zzTOKEN_COUNT];
extern SetWordType setwd29[zzTOKEN_COUNT];
extern SetWordType zzerr52[zzSET_SIZE];
extern SetWordType zzerr53[zzSET_SIZE];
extern SetWordType zzerr54[zzSET_SIZE];
extern SetWordType zzerr55[zzSET_SIZE];
extern SetWordType zzerr56[zzSET_SIZE];
extern SetWordType setwd30[zzTOKEN_COUNT];
extern SetWordType zzerr57[zzSET_SIZE];
extern SetWordType zzerr58[zzSET_SIZE];
extern SetWordType zzerr59[zzSET_SIZE];
extern SetWordType zzerr60[zzSET_SIZE];
extern SetWordType zzerr61[zzSET_SIZE];
extern SetWordType zzerr62[zzSET_SIZE];
extern SetWordType zzerr63[zzSET_SIZE];
extern SetWordType zzerr64[zzSET_SIZE];
extern SetWordType zzerr65[zzSET_SIZE];
extern SetWordType setwd31[zzTOKEN_COUNT];
extern SetWordType zzerr66[zzSET_SIZE];
extern SetWordType zzerr67[zzSET_SIZE];
extern SetWordType zzerr68[zzSET_SIZE];
extern SetWordType zzerr69[zzSET_SIZE];
extern SetWordType zzerr70[zzSET_SIZE];
extern SetWordType zzerr71[zzSET_SIZE];
extern SetWordType setwd32[zzTOKEN_COUNT];
extern SetWordType zzerr72[zzSET_SIZE];
extern SetWordType zzerr73[zzSET_SIZE];
extern SetWordType zzerr74[zzSET_SIZE];
extern SetWordType zzerr75[zzSET_SIZE];
extern SetWordType zzerr76[zzSET_SIZE];
extern SetWordType zzerr77[zzSET_SIZE];
extern SetWordType zzerr78[zzSET_SIZE];
extern SetWordType zzerr79[zzSET_SIZE];
extern SetWordType zzerr80[zzSET_SIZE];
extern SetWordType setwd33[zzTOKEN_COUNT];
extern SetWordType zzerr81[zzSET_SIZE];
extern SetWordType zzerr82[zzSET_SIZE];
extern SetWordType zzerr83[zzSET_SIZE];
extern SetWordType zzerr84[zzSET_SIZE];
extern SetWordType zzerr85[zzSET_SIZE];
extern SetWordType setwd34[zzTOKEN_COUNT];
extern SetWordType zzerr86[zzSET_SIZE];
extern SetWordType zzerr87[zzSET_SIZE];
extern SetWordType zzerr88[zzSET_SIZE];
extern SetWordType zzerr89[zzSET_SIZE];
extern SetWordType zzerr90[zzSET_SIZE];
extern SetWordType zzerr91[zzSET_SIZE];
extern SetWordType zzerr92[zzSET_SIZE];
extern SetWordType setwd35[zzTOKEN_COUNT];
extern SetWordType zzerr93[zzSET_SIZE];
extern SetWordType zzerr94[zzSET_SIZE];
extern SetWordType zzerr95[zzSET_SIZE];
extern SetWordType setwd36[zzTOKEN_COUNT];
extern SetWordType zzerr96[zzSET_SIZE];
extern SetWordType zzerr97[zzSET_SIZE];
extern SetWordType zzerr98[zzSET_SIZE];
extern SetWordType zzerr99[zzSET_SIZE];
extern SetWordType zzerr100[zzSET_SIZE];
extern SetWordType zzerr101[zzSET_SIZE];
extern SetWordType setwd37[zzTOKEN_COUNT];
extern SetWordType zzerr102[zzSET_SIZE];
extern SetWordType setwd38[zzTOKEN_COUNT];
extern SetWordType zzerr103[zzSET_SIZE];
extern SetWordType zzerr104[zzSET_SIZE];
extern SetWordType zzerr105[zzSET_SIZE];
extern SetWordType setwd39[zzTOKEN_COUNT];
extern SetWordType zzerr106[zzSET_SIZE];
extern SetWordType zzerr107[zzSET_SIZE];
extern SetWordType zzerr108[zzSET_SIZE];
extern SetWordType zzerr109[zzSET_SIZE];
extern SetWordType zzerr110[zzSET_SIZE];
extern SetWordType setwd40[zzTOKEN_COUNT];
extern SetWordType zzerr111[zzSET_SIZE];
extern SetWordType zzerr112[zzSET_SIZE];
extern SetWordType zzerr113[zzSET_SIZE];
extern SetWordType zzerr114[zzSET_SIZE];
extern SetWordType setwd41[zzTOKEN_COUNT];
extern SetWordType zzerr115[zzSET_SIZE];
extern SetWordType zzerr116[zzSET_SIZE];
extern SetWordType zzerr117[zzSET_SIZE];
extern SetWordType zzerr118[zzSET_SIZE];
extern SetWordType zzerr119[zzSET_SIZE];
extern SetWordType zzerr120[zzSET_SIZE];
extern SetWordType zzerr121[zzSET_SIZE];
extern SetWordType setwd42[zzTOKEN_COUNT];
extern SetWordType zzerr122[zzSET_SIZE];
extern SetWordType zzerr123[zzSET_SIZE];
extern SetWordType setwd43[zzTOKEN_COUNT];
extern SetWordType zzerr124[zzSET_SIZE];
extern SetWordType zzerr125[zzSET_SIZE];
extern SetWordType zzerr126[zzSET_SIZE];
extern SetWordType zzerr127[zzSET_SIZE];
extern SetWordType zzerr128[zzSET_SIZE];
extern SetWordType zzerr129[zzSET_SIZE];
extern SetWordType setwd44[zzTOKEN_COUNT];
extern SetWordType zzerr130[zzSET_SIZE];
extern SetWordType zzerr131[zzSET_SIZE];
extern SetWordType zzerr132[zzSET_SIZE];
extern SetWordType zzerr133[zzSET_SIZE];
extern SetWordType zzerr134[zzSET_SIZE];
extern SetWordType zzerr135[zzSET_SIZE];
extern SetWordType setwd45[zzTOKEN_COUNT];
extern SetWordType zzerr136[zzSET_SIZE];
extern SetWordType zzerr137[zzSET_SIZE];
extern SetWordType zzerr138[zzSET_SIZE];
extern SetWordType zzerr139[zzSET_SIZE];
extern SetWordType setwd46[zzTOKEN_COUNT];
extern SetWordType zzerr140[zzSET_SIZE];
extern SetWordType zzerr141[zzSET_SIZE];
extern SetWordType zzerr142[zzSET_SIZE];
extern SetWordType zzerr143[zzSET_SIZE];
extern SetWordType zzerr144[zzSET_SIZE];
extern SetWordType zzerr145[zzSET_SIZE];
extern SetWordType setwd47[zzTOKEN_COUNT];
extern SetWordType zzerr146[zzSET_SIZE];
extern SetWordType zzerr147[zzSET_SIZE];
extern SetWordType setwd48[zzTOKEN_COUNT];
extern SetWordType zzerr148[zzSET_SIZE];
extern SetWordType zzerr149[zzSET_SIZE];
extern SetWordType zzerr150[zzSET_SIZE];
extern SetWordType zzerr151[zzSET_SIZE];
extern SetWordType zzerr152[zzSET_SIZE];
extern SetWordType zzerr153[zzSET_SIZE];
extern SetWordType zzerr154[zzSET_SIZE];
extern SetWordType setwd49[zzTOKEN_COUNT];
extern SetWordType zzerr155[zzSET_SIZE];
extern SetWordType zzerr156[zzSET_SIZE];
extern SetWordType zzerr157[zzSET_SIZE];
extern SetWordType zzerr158[zzSET_SIZE];
extern SetWordType zzerr159[zzSET_SIZE];
extern SetWordType setwd50[zzTOKEN_COUNT];
extern SetWordType zzerr160[zzSET_SIZE];
extern SetWordType zzerr161[zzSET_SIZE];
extern SetWordType zzerr162[zzSET_SIZE];
extern SetWordType zzerr163[zzSET_SIZE];
extern SetWordType setwd51[zzTOKEN_COUNT];
extern SetWordType zzerr164[zzSET_SIZE];
extern SetWordType zzerr165[zzSET_SIZE];
extern SetWordType zzerr166[zzSET_SIZE];
extern SetWordType zzerr167[zzSET_SIZE];
extern SetWordType zzerr168[zzSET_SIZE];
extern SetWordType zzerr169[zzSET_SIZE];
extern SetWordType zzerr170[zzSET_SIZE];
extern SetWordType zzerr171[zzSET_SIZE];
extern SetWordType setwd52[zzTOKEN_COUNT];
extern SetWordType zzerr172[zzSET_SIZE];
extern SetWordType zzerr173[zzSET_SIZE];
extern SetWordType zzerr174[zzSET_SIZE];
extern SetWordType zzerr175[zzSET_SIZE];
extern SetWordType setwd53[zzTOKEN_COUNT];
extern SetWordType zzerr176[zzSET_SIZE];
extern SetWordType zzerr177[zzSET_SIZE];
extern SetWordType zzerr178[zzSET_SIZE];
extern SetWordType zzerr179[zzSET_SIZE];
extern SetWordType zzerr180[zzSET_SIZE];
extern SetWordType zzerr181[zzSET_SIZE];
extern SetWordType zzerr182[zzSET_SIZE];
extern SetWordType setwd54[zzTOKEN_COUNT];
extern SetWordType zzerr183[zzSET_SIZE];
extern SetWordType zzerr184[zzSET_SIZE];
extern SetWordType zzerr185[zzSET_SIZE];
extern SetWordType zzerr186[zzSET_SIZE];
extern SetWordType setwd55[zzTOKEN_COUNT];
extern SetWordType zzerr187[zzSET_SIZE];
extern SetWordType zzerr188[zzSET_SIZE];
extern SetWordType zzerr189[zzSET_SIZE];
extern SetWordType zzerr190[zzSET_SIZE];
extern SetWordType zzerr191[zzSET_SIZE];
extern SetWordType zzerr192[zzSET_SIZE];
extern SetWordType zzerr193[zzSET_SIZE];
extern SetWordType zzerr194[zzSET_SIZE];
extern SetWordType zzerr195[zzSET_SIZE];
extern SetWordType setwd56[zzTOKEN_COUNT];
extern SetWordType zzerr196[zzSET_SIZE];
extern SetWordType zzerr197[zzSET_SIZE];
extern SetWordType zzerr198[zzSET_SIZE];
extern SetWordType zzerr199[zzSET_SIZE];
extern SetWordType zzerr200[zzSET_SIZE];
extern SetWordType zzerr201[zzSET_SIZE];
extern SetWordType setwd57[zzTOKEN_COUNT];
extern SetWordType zzerr202[zzSET_SIZE];
extern SetWordType zzerr203[zzSET_SIZE];
extern SetWordType zzerr204[zzSET_SIZE];
extern SetWordType zzerr205[zzSET_SIZE];
extern SetWordType zzerr206[zzSET_SIZE];
extern SetWordType setwd58[zzTOKEN_COUNT];
extern SetWordType zzerr207[zzSET_SIZE];
extern SetWordType zzerr208[zzSET_SIZE];
extern SetWordType zzerr209[zzSET_SIZE];
extern SetWordType setwd59[zzTOKEN_COUNT];
extern SetWordType zzerr210[zzSET_SIZE];
extern SetWordType zzerr211[zzSET_SIZE];
extern SetWordType zzerr212[zzSET_SIZE];
extern SetWordType setwd60[zzTOKEN_COUNT];
extern SetWordType zzerr213[zzSET_SIZE];
extern SetWordType zzerr214[zzSET_SIZE];
extern SetWordType zzerr215[zzSET_SIZE];
extern SetWordType zzerr216[zzSET_SIZE];
extern SetWordType setwd61[zzTOKEN_COUNT];
extern SetWordType zzerr217[zzSET_SIZE];
extern SetWordType zzerr218[zzSET_SIZE];
extern SetWordType zzerr219[zzSET_SIZE];
extern SetWordType zzerr220[zzSET_SIZE];
extern SetWordType zzerr221[zzSET_SIZE];
extern SetWordType setwd62[zzTOKEN_COUNT];
extern SetWordType zzerr222[zzSET_SIZE];
extern SetWordType zzerr223[zzSET_SIZE];
extern SetWordType zzerr224[zzSET_SIZE];
extern SetWordType zzerr225[zzSET_SIZE];
extern SetWordType zzerr226[zzSET_SIZE];
extern SetWordType setwd63[zzTOKEN_COUNT];
extern SetWordType zzerr227[zzSET_SIZE];
extern SetWordType zzerr228[zzSET_SIZE];
extern SetWordType zzerr229[zzSET_SIZE];
extern SetWordType zzerr230[zzSET_SIZE];
extern SetWordType zzerr231[zzSET_SIZE];
extern SetWordType zzerr232[zzSET_SIZE];
extern SetWordType zzerr233[zzSET_SIZE];
extern SetWordType setwd64[zzTOKEN_COUNT];
extern SetWordType zzerr234[zzSET_SIZE];
extern SetWordType zzerr235[zzSET_SIZE];
extern SetWordType zzerr236[zzSET_SIZE];
extern SetWordType zzerr237[zzSET_SIZE];
extern SetWordType setwd65[zzTOKEN_COUNT];
extern SetWordType zzerr238[zzSET_SIZE];
extern SetWordType zzerr239[zzSET_SIZE];
extern SetWordType zzerr240[zzSET_SIZE];
extern SetWordType zzerr241[zzSET_SIZE];
extern SetWordType zzerr242[zzSET_SIZE];
extern SetWordType zzerr243[zzSET_SIZE];
extern SetWordType zzerr244[zzSET_SIZE];
extern SetWordType zzerr245[zzSET_SIZE];
extern SetWordType zzerr246[zzSET_SIZE];
extern SetWordType setwd66[zzTOKEN_COUNT];
extern SetWordType zzerr247[zzSET_SIZE];
extern SetWordType zzerr248[zzSET_SIZE];
extern SetWordType setwd67[zzTOKEN_COUNT];
extern SetWordType setwd68[zzTOKEN_COUNT];
extern SetWordType zzerr249[zzSET_SIZE];
extern SetWordType zzerr250[zzSET_SIZE];
extern SetWordType setwd69[zzTOKEN_COUNT];
extern SetWordType setwd70[zzTOKEN_COUNT];


#endif /* tokens_h */
