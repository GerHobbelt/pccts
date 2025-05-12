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



extern void x_program(STreeParser *_parser, SORAST **_root);
extern void x_main_program(STreeParser *_parser, SORAST **_root);
extern void x_subroutine_block(STreeParser *_parser, SORAST **_root);
extern void x_decl_block(STreeParser *_parser, SORAST **_root);
extern void x_decl_statement(STreeParser *_parser, SORAST **_root);
extern void x_comment_block(STreeParser *_parser, SORAST **_root);
extern void x_exec_statement(STreeParser *_parser, SORAST **_root);
extern void x_exec_block(STreeParser *_parser, SORAST **_root);
extern void x_block_globals_block(STreeParser *_parser, SORAST **_root);
extern void x_file_block(STreeParser *_parser, SORAST **_root);
extern void x_comment_line(STreeParser *_parser, SORAST **_root);
extern void x_blank_line(STreeParser *_parser, SORAST **_root);
extern void x_block_globals_statement(STreeParser *_parser, SORAST **_root);
extern void x_common_statement(STreeParser *_parser, SORAST **_root);
extern void x_block_item(STreeParser *_parser, SORAST **_root);
extern void x_save_statement(STreeParser *_parser, SORAST **_root);
extern void x_save_item(STreeParser *_parser, SORAST **_root);
extern void x_parameter_statement(STreeParser *_parser, SORAST **_root);
extern void x_para_item(STreeParser *_parser, SORAST **_root);
extern void x_external_statement(STreeParser *_parser, SORAST **_root);
extern void x_function_name(STreeParser *_parser, SORAST **_root);
extern void x_intrinsic_statement(STreeParser *_parser, SORAST **_root);
extern void x_implicit_statement(STreeParser *_parser, SORAST **_root);
extern void x_implicit_item(STreeParser *_parser, SORAST **_root);
extern void x_implicit_type(STreeParser *_parser, SORAST **_root);
extern void x_letter_spec(STreeParser *_parser, SORAST **_root);
extern void x_data_statement(STreeParser *_parser, SORAST **_root);
extern void x_inquire_statement(STreeParser *_parser, SORAST **_root);
extern void x_assignment_statement(STreeParser *_parser, SORAST **_root);
extern void x_lvalue(STreeParser *_parser, SORAST **_root);
extern void x_rvalue(STreeParser *_parser, SORAST **_root);
extern void x_array_reference(STreeParser *_parser, SORAST **_root);
extern void x_int_lvalue(STreeParser *_parser, SORAST **_root);
extern void x_real_lvalue(STreeParser *_parser, SORAST **_root);
extern void x_char_lvalue(STreeParser *_parser, SORAST **_root);
extern void x_double_lvalue(STreeParser *_parser, SORAST **_root);
extern void x_log_lvalue(STreeParser *_parser, SORAST **_root);
extern void x_int_array_ref(STreeParser *_parser, SORAST **_root);
extern void x_real_array_ref(STreeParser *_parser, SORAST **_root);
extern void x_char_array_ref(STreeParser *_parser, SORAST **_root);
extern void x_log_array_ref(STreeParser *_parser, SORAST **_root);
extern void x_double_array_ref(STreeParser *_parser, SORAST **_root);
extern void x_array_name(STreeParser *_parser, SORAST **_root);
extern void x_function_reference(STreeParser *_parser, SORAST **_root);
extern void x_expression(STreeParser *_parser, SORAST **_root);
extern void x_real_expression(STreeParser *_parser, SORAST **_root);
extern void x_exp_operand(STreeParser *_parser, SORAST **_root);
extern void x_integer_expr(STreeParser *_parser, SORAST **_root);
extern void x_substring(STreeParser *_parser, SORAST **_root);
extern void x_control_image(STreeParser *_parser, SORAST **_root);
extern void x_file_statement(STreeParser *_parser, SORAST **_root);
extern void x_file_item(STreeParser *_parser, SORAST **_root);
extern void x_find_statement(STreeParser *_parser, SORAST **_root);
extern void x_findlist(STreeParser *_parser, SORAST **_root);
extern void x_character_statement(STreeParser *_parser, SORAST **_root);
extern void x_integer_statement(STreeParser *_parser, SORAST **_root);
extern void x_real_statement(STreeParser *_parser, SORAST **_root);
extern void x_logical_statement(STreeParser *_parser, SORAST **_root);
extern void x_precision_statement(STreeParser *_parser, SORAST **_root);
extern void x_dimension_statement(STreeParser *_parser, SORAST **_root);
extern void x_equivalence_statement(STreeParser *_parser, SORAST **_root);
extern void x_backspace_statement(STreeParser *_parser, SORAST **_root);
extern void x_endfile_statement(STreeParser *_parser, SORAST **_root);
extern void x_rewind_statement(STreeParser *_parser, SORAST **_root);
extern void x_io_specifier(STreeParser *_parser, SORAST **_root);
extern  SORAST *  x_read_statement(STreeParser *_parser, SORAST **_root);
extern  SORAST *  x_write_statement(STreeParser *_parser, SORAST **_root);
extern  SORAST *  x_control_info(STreeParser *_parser, SORAST **_root);
extern  SORAST *  x_the_remainder(STreeParser *_parser, SORAST **_root);
extern void x_unit_id(STreeParser *_parser, SORAST **_root);
extern  SORAST *  x_format_id(STreeParser *_parser, SORAST **_root);
extern void x_input_list(STreeParser *_parser, SORAST **_root);
extern void x_input_item(STreeParser *_parser, SORAST **_root);
extern void x_inp_implied_list(STreeParser *_parser, SORAST **_root);
extern void x_output_list(STreeParser *_parser, SORAST **_root);
extern void x_output_item(STreeParser *_parser, SORAST **_root);
extern void x_outp_implied_list(STreeParser *_parser, SORAST **_root);
extern void x_implied_loop(STreeParser *_parser, SORAST **_root);
extern void x_open_statement(STreeParser *_parser, SORAST **_root);
extern void x_open_item(STreeParser *_parser, SORAST **_root);
extern void x_close_statement(STreeParser *_parser, SORAST **_root);
extern void x_close_item(STreeParser *_parser, SORAST **_root);
extern void x_close_name(STreeParser *_parser, SORAST **_root);
extern void x_call_statement(STreeParser *_parser, SORAST **_root);
extern void x_call_arg_list(STreeParser *_parser, SORAST **_root);
extern void x_call_arg_item(STreeParser *_parser, SORAST **_root);
extern void x_export_statement(STreeParser *_parser, SORAST **_root);
extern void x_subroutine_statement(STreeParser *_parser, SORAST **_root);
extern void x_entry_statement(STreeParser *_parser, SORAST **_root);
extern void x_function_statement(STreeParser *_parser, SORAST **_root);
extern void x_function_type(STreeParser *_parser, SORAST **_root);
extern void x_function_arg_list(STreeParser *_parser, SORAST **_root);
extern void x_length_spec(STreeParser *_parser, SORAST **_root);
extern void x_block_if_statement(STreeParser *_parser, SORAST **_root);
extern void x_block_if_block(STreeParser *_parser, SORAST **_root);
extern void x_log_if_statement(STreeParser *_parser, SORAST **_root);
extern void x_arithm_if_statement(STreeParser *_parser, SORAST **_root);
extern void x_log_substatement(STreeParser *_parser, SORAST **_root);
extern void x_continue_statement(STreeParser *_parser, SORAST **_root);
extern void x_stop_statement(STreeParser *_parser, SORAST **_root);
extern void x_end_statement(STreeParser *_parser, SORAST **_root);
extern void x_return_statement(STreeParser *_parser, SORAST **_root);
extern void x_unconditional_goto(STreeParser *_parser, SORAST **_root);
extern void x_computed_goto(STreeParser *_parser, SORAST **_root);
extern void x_assigned_goto(STreeParser *_parser, SORAST **_root);
extern void x_do_statement(STreeParser *_parser, SORAST **_root);
extern void x_change_statement(STreeParser *_parser, SORAST **_root);
extern void x_assign_statement(STreeParser *_parser, SORAST **_root);
extern void x_format_statement(STreeParser *_parser, SORAST **_root);
extern void x_format_spec(STreeParser *_parser, SORAST **_root);
extern void x_format_item(STreeParser *_parser, SORAST **_root);
extern void x_hollerith_editing(STreeParser *_parser, SORAST **_root);
extern void x_quote_editinig(STreeParser *_parser, SORAST **_root);
extern void x_tr_editing(STreeParser *_parser, SORAST **_root);
extern void x_tl_editing(STreeParser *_parser, SORAST **_root);
extern void x_t_editing(STreeParser *_parser, SORAST **_root);
extern void x_x_editing(STreeParser *_parser, SORAST **_root);
extern void x_ss_editing(STreeParser *_parser, SORAST **_root);
extern void x_p_editing(STreeParser *_parser, SORAST **_root);
extern void x_bz_editing(STreeParser *_parser, SORAST **_root);
extern void x_bn_editing(STreeParser *_parser, SORAST **_root);
extern void x_j_editing(STreeParser *_parser, SORAST **_root);
extern void x_e_editing(STreeParser *_parser, SORAST **_root);
extern void x_g_editing(STreeParser *_parser, SORAST **_root);
extern void x_l_editing(STreeParser *_parser, SORAST **_root);
extern void x_z_editing(STreeParser *_parser, SORAST **_root);
extern void x_u_editing(STreeParser *_parser, SORAST **_root);
extern void x_colon_editing(STreeParser *_parser, SORAST **_root);
extern void x_s_editing(STreeParser *_parser, SORAST **_root);
extern void x_i_editing(STreeParser *_parser, SORAST **_root);
extern void x_f_editing(STreeParser *_parser, SORAST **_root);
extern void x_d_editing(STreeParser *_parser, SORAST **_root);
extern void x_o_editing(STreeParser *_parser, SORAST **_root);
extern void x_a_editing(STreeParser *_parser, SORAST **_root);
extern void x_sp_editing(STreeParser *_parser, SORAST **_root);
extern void x_repeat_count(STreeParser *_parser, SORAST **_root);
extern void x_field_width(STreeParser *_parser, SORAST **_root);
extern void x_decimal_places(STreeParser *_parser, SORAST **_root);
extern void x_exponent_digits(STreeParser *_parser, SORAST **_root);
extern void x_min_dig_required(STreeParser *_parser, SORAST **_root);
extern void x_any_token(STreeParser *_parser, SORAST **_root);
