// opcodes.h -- instruction codes used by code generator, interpreter and disassembler
//    NOTE: this must be kept in synch with opnames.h!!!
#define i_add           0
#define i_sub           1
#define i_neg           2
#define i_mult          3
#define i_ne            4
#define i_div           5
#define i_eq            6
#define i_le            7
#define i_lt            8
#define i_ge            9
#define i_gt            10
#define i_not           11
#define i_mod           12
#define i_prev          13
#define i_succ          14
#define i_get_int       15 
#define i_put_int       16
#define i_new_line      17
#define i_halt          18
#define i_simple_assign 19
#define i_simple_value  20
#define i_skip_line     21
#define i_return        22
#define i_bounds        23
   
#define ONE_OPERAND_STARTS_HERE  24
#define i_program       24
#define i_branch_false  25
#define i_branch_true   26
#define i_constant      27
#define i_assign        28
#define i_value         29
#define i_goto          30
#define i_put_string    31
#define i_localvar      32
#define i_procedure     33
#define i_pop           34
   
#define TWO_OPERANDS_START_HERE  35
#define i_variable      35
#define i_proc_call     36

#define HAS_NO_OPERANDS(opcode)      (opcode < ONE_OPERAND_STARTS_HERE)
#define HAS_TWO_OPERANDS(opcode)     (opcode >= TWO_OPERANDS_START_HERE)

#define NUMBER_OF_OPCODES 36
