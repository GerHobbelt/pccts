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

extern void o_program(STreeParser *_parser, SORAST **_root);
extern void o_main_program(STreeParser *_parser, SORAST **_root);
extern void o_subroutine_block(STreeParser *_parser, SORAST **_root);
extern void o_decl_block(STreeParser *_parser, SORAST **_root);
extern void o_decl_statement(STreeParser *_parser, SORAST **_root);
extern void o_comment_block(STreeParser *_parser, SORAST **_root);
extern void o_exec_statement(STreeParser *_parser, SORAST **_root);
extern void o_exec_block(STreeParser *_parser, SORAST **_root);
extern void o_block_globals_block(STreeParser *_parser, SORAST **_root);
extern void o_file_block(STreeParser *_parser, SORAST **_root);
extern void o_comment_line(STreeParser *_parser, SORAST **_root);
extern void o_blank_line(STreeParser *_parser, SORAST **_root);
extern void o_block_globals_statement(STreeParser *_parser, SORAST **_root);
extern void o_common_statement(STreeParser *_parser, SORAST **_root);
extern void o_block_item(STreeParser *_parser, SORAST **_root);
extern void o_save_statement(STreeParser *_parser, SORAST **_root);
extern void o_save_item(STreeParser *_parser, SORAST **_root);
extern void o_parameter_statement(STreeParser *_parser, SORAST **_root);
extern void o_para_item(STreeParser *_parser, SORAST **_root);
extern void o_external_statement(STreeParser *_parser, SORAST **_root);
extern void o_function_name(STreeParser *_parser, SORAST **_root);
extern void o_intrinsic_statement(STreeParser *_parser, SORAST **_root);
extern void o_implicit_statement(STreeParser *_parser, SORAST **_root);
extern void o_implicit_item(STreeParser *_parser, SORAST **_root);
extern void o_implicit_type(STreeParser *_parser, SORAST **_root);
extern void o_letter_spec(STreeParser *_parser, SORAST **_root);
extern void o_data_statement(STreeParser *_parser, SORAST **_root);
extern void o_inquire_statement(STreeParser *_parser, SORAST **_root);
extern void o_assignment_statement(STreeParser *_parser, SORAST **_root);
extern void o_lvalue(STreeParser *_parser, SORAST **_root);
extern void o_rvalue(STreeParser *_parser, SORAST **_root);
extern void o_array_reference(STreeParser *_parser, SORAST **_root);
extern void o_int_lvalue(STreeParser *_parser, SORAST **_root);
extern void o_real_lvalue(STreeParser *_parser, SORAST **_root);
extern void o_char_lvalue(STreeParser *_parser, SORAST **_root);
extern void o_double_lvalue(STreeParser *_parser, SORAST **_root);
extern void o_log_lvalue(STreeParser *_parser, SORAST **_root);
extern void o_int_array_ref(STreeParser *_parser, SORAST **_root);
extern void o_real_array_ref(STreeParser *_parser, SORAST **_root);
extern void o_char_array_ref(STreeParser *_parser, SORAST **_root);
extern void o_log_array_ref(STreeParser *_parser, SORAST **_root);
extern void o_double_array_ref(STreeParser *_parser, SORAST **_root);
extern void o_array_name(STreeParser *_parser, SORAST **_root);
extern void o_function_reference(STreeParser *_parser, SORAST **_root);
extern void o_expression(STreeParser *_parser, SORAST **_root);
extern void o_real_expression(STreeParser *_parser, SORAST **_root);
extern void o_exp_operand(STreeParser *_parser, SORAST **_root);
extern void o_integer_expr(STreeParser *_parser, SORAST **_root);
extern void o_substring(STreeParser *_parser, SORAST **_root);
extern void o_control_image(STreeParser *_parser, SORAST **_root);
extern void o_file_statement(STreeParser *_parser, SORAST **_root);
extern void o_file_item(STreeParser *_parser, SORAST **_root);
extern void o_find_statement(STreeParser *_parser, SORAST **_root);
extern void o_findlist(STreeParser *_parser, SORAST **_root);
extern void o_character_statement(STreeParser *_parser, SORAST **_root);
extern void o_integer_statement(STreeParser *_parser, SORAST **_root);
extern void o_real_statement(STreeParser *_parser, SORAST **_root);
extern void o_logical_statement(STreeParser *_parser, SORAST **_root);
extern void o_precision_statement(STreeParser *_parser, SORAST **_root);
extern void o_dimension_statement(STreeParser *_parser, SORAST **_root);
extern void o_equivalence_statement(STreeParser *_parser, SORAST **_root);
extern void o_backspace_statement(STreeParser *_parser, SORAST **_root);
extern void o_endfile_statement(STreeParser *_parser, SORAST **_root);
extern void o_rewind_statement(STreeParser *_parser, SORAST **_root);
extern void o_io_specifier(STreeParser *_parser, SORAST **_root);
extern void o_read_statement(STreeParser *_parser, SORAST **_root);
extern void o_write_statement(STreeParser *_parser, SORAST **_root);
extern void o_control_info(STreeParser *_parser, SORAST **_root);
extern void o_the_remainder(STreeParser *_parser, SORAST **_root);
extern void o_unit_id(STreeParser *_parser, SORAST **_root);
extern void o_format_id(STreeParser *_parser, SORAST **_root);
extern void o_input_list(STreeParser *_parser, SORAST **_root);
extern void o_input_item(STreeParser *_parser, SORAST **_root);
extern void o_inp_implied_list(STreeParser *_parser, SORAST **_root);
extern void o_output_list(STreeParser *_parser, SORAST **_root);
extern void o_output_item(STreeParser *_parser, SORAST **_root);
extern void o_outp_implied_list(STreeParser *_parser, SORAST **_root);
extern void o_implied_loop(STreeParser *_parser, SORAST **_root);
extern void o_open_statement(STreeParser *_parser, SORAST **_root);
extern void o_open_item(STreeParser *_parser, SORAST **_root);
extern void o_close_statement(STreeParser *_parser, SORAST **_root);
extern void o_close_item(STreeParser *_parser, SORAST **_root);
extern void o_close_name(STreeParser *_parser, SORAST **_root);
extern void o_call_statement(STreeParser *_parser, SORAST **_root);
extern void o_call_arg_list(STreeParser *_parser, SORAST **_root);
extern void o_call_arg_item(STreeParser *_parser, SORAST **_root);
extern void o_export_statement(STreeParser *_parser, SORAST **_root);
extern void o_subroutine_statement(STreeParser *_parser, SORAST **_root);
extern void o_entry_statement(STreeParser *_parser, SORAST **_root);
extern void o_function_statement(STreeParser *_parser, SORAST **_root);
extern void o_function_type(STreeParser *_parser, SORAST **_root);
extern void o_function_arg_list(STreeParser *_parser, SORAST **_root);
extern void o_length_spec(STreeParser *_parser, SORAST **_root);
extern void o_block_if_statement(STreeParser *_parser, SORAST **_root);
extern void o_block_if_block(STreeParser *_parser, SORAST **_root);
extern void o_log_if_statement(STreeParser *_parser, SORAST **_root);
extern void o_arithm_if_statement(STreeParser *_parser, SORAST **_root);
extern void o_log_substatement(STreeParser *_parser, SORAST **_root);
extern void o_continue_statement(STreeParser *_parser, SORAST **_root);
extern void o_stop_statement(STreeParser *_parser, SORAST **_root);
extern void o_end_statement(STreeParser *_parser, SORAST **_root);
extern void o_return_statement(STreeParser *_parser, SORAST **_root);
extern void o_unconditional_goto(STreeParser *_parser, SORAST **_root);
extern void o_computed_goto(STreeParser *_parser, SORAST **_root);
extern void o_assigned_goto(STreeParser *_parser, SORAST **_root);
extern void o_do_statement(STreeParser *_parser, SORAST **_root);
extern void o_change_statement(STreeParser *_parser, SORAST **_root);
extern void o_assign_statement(STreeParser *_parser, SORAST **_root);
extern void o_format_statement(STreeParser *_parser, SORAST **_root);
extern void o_format_spec(STreeParser *_parser, SORAST **_root);
extern void o_format_item(STreeParser *_parser, SORAST **_root);
extern void o_hollerith_editing(STreeParser *_parser, SORAST **_root);
extern void o_quote_editinig(STreeParser *_parser, SORAST **_root);
extern void o_tr_editing(STreeParser *_parser, SORAST **_root);
extern void o_tl_editing(STreeParser *_parser, SORAST **_root);
extern void o_t_editing(STreeParser *_parser, SORAST **_root);
extern void o_x_editing(STreeParser *_parser, SORAST **_root);
extern void o_ss_editing(STreeParser *_parser, SORAST **_root);
extern void o_p_editing(STreeParser *_parser, SORAST **_root);
extern void o_bz_editing(STreeParser *_parser, SORAST **_root);
extern void o_bn_editing(STreeParser *_parser, SORAST **_root);
extern void o_j_editing(STreeParser *_parser, SORAST **_root);
extern void o_e_editing(STreeParser *_parser, SORAST **_root);
extern void o_g_editing(STreeParser *_parser, SORAST **_root);
extern void o_l_editing(STreeParser *_parser, SORAST **_root);
extern void o_z_editing(STreeParser *_parser, SORAST **_root);
extern void o_u_editing(STreeParser *_parser, SORAST **_root);
extern void o_colon_editing(STreeParser *_parser, SORAST **_root);
extern void o_s_editing(STreeParser *_parser, SORAST **_root);
extern void o_i_editing(STreeParser *_parser, SORAST **_root);
extern void o_f_editing(STreeParser *_parser, SORAST **_root);
extern void o_d_editing(STreeParser *_parser, SORAST **_root);
extern void o_o_editing(STreeParser *_parser, SORAST **_root);
extern void o_a_editing(STreeParser *_parser, SORAST **_root);
extern void o_sp_editing(STreeParser *_parser, SORAST **_root);
extern void o_repeat_count(STreeParser *_parser, SORAST **_root, char *buffer );
extern void o_field_width(STreeParser *_parser, SORAST **_root, char *buffer );
extern void o_decimal_places(STreeParser *_parser, SORAST **_root, char *buffer );
extern void o_exponent_digits(STreeParser *_parser, SORAST **_root, char *buffer );
extern void o_min_dig_required(STreeParser *_parser, SORAST **_root, char *buffer );
extern void o_label(STreeParser *_parser, SORAST **_root);
extern void o_comma(STreeParser *_parser, SORAST **_root);
extern void o_lp(STreeParser *_parser, SORAST **_root);
extern void o_rp(STreeParser *_parser, SORAST **_root);
extern void o_equal(STreeParser *_parser, SORAST **_root);
extern void o_const_int(STreeParser *_parser, SORAST **_root);
extern void o_identifier(STreeParser *_parser, SORAST **_root);
extern void o_quoted_string(STreeParser *_parser, SORAST **_root);
extern void o_any_token(STreeParser *_parser, SORAST **_root);
extern void o_any_statement(STreeParser *_parser, SORAST **_root);
