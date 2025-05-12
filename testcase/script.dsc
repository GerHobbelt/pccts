Cross Reference:

Rule               script referenced by { }
Rule                title referenced by { script subroutine }
Rule             sections referenced by { script subroutine }
Rule          definitions referenced by { sections }
Rule            structdef referenced by { definitions }
Rule  const_init_type_def referenced by { definitions }
Rule           subroutine referenced by { sections }
Rule       param_def_list referenced by { script subroutine }
Rule            param_def referenced by { param_def_list }
Rule         declarations referenced by { sections }
Rule              vardecl referenced by { structdef declarations }
Rule       sub_param_type referenced by { param_def }
Rule          return_type referenced by { subroutine }
Rule                 type referenced by { structdef vardecl sub_param_type return_type type }
Rule         integer_type referenced by { type const_init_type }
Rule      const_init_type referenced by { const_init_type_def vardecl }
Rule   const_string_value referenced by { const_init_type simple_rvalue_expr }
Rule       implementation referenced by { sections }
Rule            statement referenced by { implementation block_statement }
Rule     return_statement referenced by { statement }
Rule      label_statement referenced by { statement }
Rule      break_statement referenced by { statement }
Rule    special_statement referenced by { statement }
Rule assignment_statement referenced by { statement }
Rule conditional_statement referenced by { statement }
Rule       loop_statement referenced by { statement }
Rule bracketed_conditional_expr referenced by { conditional_statement loop_statement }
Rule      block_statement referenced by { statement conditional_statement loop_statement }
Rule          lvalue_expr referenced by { assignment_statement }
Rule   elemental_variable referenced by { lvalue_expr simple_rvalue_expr }
Rule          rvalue_expr referenced by { assignment_statement bracketed_conditional_expr elemental_variable simple_rvalue_expr param_list }
Rule compare_or_rvalue_expr referenced by { rvalue_expr }
Rule compare_and_rvalue_expr referenced by { compare_or_rvalue_expr }
Rule bitwise_or_rvalue_expr referenced by { compare_and_rvalue_expr }
Rule bitwise_xor_rvalue_expr referenced by { bitwise_or_rvalue_expr }
Rule bitwise_and_rvalue_expr referenced by { bitwise_xor_rvalue_expr }
Rule compare_ne_rvalue_expr referenced by { bitwise_and_rvalue_expr }
Rule compare_eq_rvalue_expr referenced by { compare_ne_rvalue_expr }
Rule compare_ge_rvalue_expr referenced by { compare_eq_rvalue_expr }
Rule compare_gt_rvalue_expr referenced by { compare_ge_rvalue_expr }
Rule compare_le_rvalue_expr referenced by { compare_gt_rvalue_expr }
Rule compare_lt_rvalue_expr referenced by { compare_le_rvalue_expr }
Rule   rshift_rvalue_expr referenced by { compare_lt_rvalue_expr }
Rule   lshift_rvalue_expr referenced by { rshift_rvalue_expr }
Rule substract_rvalue_expr referenced by { lshift_rvalue_expr }
Rule      add_rvalue_expr referenced by { substract_rvalue_expr }
Rule   modulo_rvalue_expr referenced by { add_rvalue_expr }
Rule   divide_rvalue_expr referenced by { modulo_rvalue_expr }
Rule multiply_rvalue_expr referenced by { divide_rvalue_expr }
Rule    power_rvalue_expr referenced by { multiply_rvalue_expr }
Rule    unary_rvalue_expr referenced by { power_rvalue_expr unary_rvalue_expr }
Rule   simple_rvalue_expr referenced by { unary_rvalue_expr }
Rule           param_list referenced by { simple_rvalue_expr }

script :
	  SCRIPT title param_def_list sections ENDSCRIPT SCRIPT_EOF
	;

title :
	  VARIABLE
	;

sections :
	  { definitions } ( subroutine )* { declarations } implementation
	;

definitions :
	  DEFINITIONS ( structdef | const_init_type_def )+
	;

structdef :
	  DEFINE VARIABLE AS ( type | STRUCT ( vardecl )+ ENDSTRUCT ) SEMICOLON
	;

const_init_type_def :
	  const_init_type SEMICOLON
	;

subroutine :
	  SUBROUTINE title param_def_list COLON return_type sections ENDSUB
	;

param_def_list :
	  LPARENS { ( param_def ( COMMA param_def )* { COMMA TRIPLE_DOT } | TRIPLE_DOT ) } RPARENS
	;

param_def :
	  VARIABLE { COLON sub_param_type }
	;

declarations :
	  DECLARATIONS ( vardecl )+
	;

vardecl :
	  VARIABLE COLON ( type | const_init_type ) SEMICOLON
	;

sub_param_type :
	  { CONST } ( type | ANY )
	;

return_type :
	  type
	| VOID
	| ANY
	;

type :
	  BOOLEAN
	| integer_type
	| REAL
	| STRING
	| ARRAY OF type
	| VARIABLE
	;

integer_type :
	  INTEGER { MULTIPLY INT_VALUE }
	;

const_init_type :
	  CONST integer_type ASSIGN INT_VALUE
	| CONST REAL ASSIGN REAL_VALUE
	| CONST BOOLEAN ASSIGN BOOLEAN_VALUE
	| CONST STRING ASSIGN const_string_value
	| CONST VARIABLE ASSIGN INT_VALUE
	;

const_string_value :
	  ( STRING_VALUE )+
	;

implementation :
	  IMPLEMENTATION ( statement )+
	;

statement :
	  assignment_statement
	| conditional_statement
	| loop_statement
	| block_statement
	| return_statement
	| break_statement
	| label_statement
	| special_statement
	;

return_statement :
	  RETURN SEMICOLON
	;

label_statement :
	  VARIABLE COLON
	| GOTO VARIABLE SEMICOLON
	;

break_statement :
	  BREAK SEMICOLON
	| CONTINUE SEMICOLON
	;

special_statement :
	  RESET SEMICOLON
	| HALT SEMICOLON
	;

assignment_statement :
	  lvalue_expr ( ASSIGNMENT rvalue_expr | PLUS PLUS | MINUS MINUS ) SEMICOLON
	| VOID rvalue_expr SEMICOLON
	;

conditional_statement :
	  IF bracketed_conditional_expr block_statement ( ELIF bracketed_conditional_expr block_statement )* { ELSE block_statement } ENDIF SEMICOLON
	;

loop_statement :
	  WHILE bracketed_conditional_expr DO block_statement DONE SEMICOLON
	| REPEAT block_statement UNTIL bracketed_conditional_expr SEMICOLON
	;

bracketed_conditional_expr :
	  LPARENS rvalue_expr RPARENS
	;

block_statement :
	  BEGIN ( statement )+ END
	;

lvalue_expr :
	  elemental_variable
	;

elemental_variable :
	  VARIABLE ( LBRACKET rvalue_expr RBRACKET )* ( DOT VARIABLE ( LBRACKET rvalue_expr RBRACKET )* )*
	;

rvalue_expr :
	  compare_or_rvalue_expr
	;

compare_or_rvalue_expr :
	  compare_and_rvalue_expr ( BOOLEAN_OR compare_and_rvalue_expr )*
	;

compare_and_rvalue_expr :
	  bitwise_or_rvalue_expr ( BOOLEAN_AND bitwise_or_rvalue_expr )*
	;

bitwise_or_rvalue_expr :
	  bitwise_xor_rvalue_expr ( BITWISE_OR bitwise_xor_rvalue_expr )*
	;

bitwise_xor_rvalue_expr :
	  bitwise_and_rvalue_expr ( BITWISE_XOR bitwise_and_rvalue_expr )*
	;

bitwise_and_rvalue_expr :
	  compare_ne_rvalue_expr ( BITWISE_AND compare_ne_rvalue_expr )*
	;

compare_ne_rvalue_expr :
	  compare_eq_rvalue_expr ( NE compare_eq_rvalue_expr )*
	;

compare_eq_rvalue_expr :
	  compare_ge_rvalue_expr ( EQ compare_ge_rvalue_expr )*
	;

compare_ge_rvalue_expr :
	  compare_gt_rvalue_expr ( GE compare_gt_rvalue_expr )*
	;

compare_gt_rvalue_expr :
	  compare_le_rvalue_expr ( GT compare_le_rvalue_expr )*
	;

compare_le_rvalue_expr :
	  compare_lt_rvalue_expr ( LE compare_lt_rvalue_expr )*
	;

compare_lt_rvalue_expr :
	  rshift_rvalue_expr ( LT rshift_rvalue_expr )*
	;

rshift_rvalue_expr :
	  lshift_rvalue_expr ( RSHIFT lshift_rvalue_expr )*
	;

lshift_rvalue_expr :
	  substract_rvalue_expr ( LSHIFT substract_rvalue_expr )*
	;

substract_rvalue_expr :
	  add_rvalue_expr ( MINUS add_rvalue_expr )*
	;

add_rvalue_expr :
	  modulo_rvalue_expr ( PLUS modulo_rvalue_expr )*
	;

modulo_rvalue_expr :
	  divide_rvalue_expr ( MODULO divide_rvalue_expr )*
	;

divide_rvalue_expr :
	  multiply_rvalue_expr ( DIVIDE multiply_rvalue_expr )*
	;

multiply_rvalue_expr :
	  power_rvalue_expr ( MULTIPLY power_rvalue_expr )*
	;

power_rvalue_expr :
	  unary_rvalue_expr ( POWER unary_rvalue_expr )*
	;

unary_rvalue_expr :
	  simple_rvalue_expr
	| UNARY_OPERATOR unary_rvalue_expr
	;

simple_rvalue_expr :
	  INT_VALUE
	| REAL_VALUE
	| BOOLEAN_VALUE
	| const_string_value
	| elemental_variable
	| VARIABLE LPARENS { param_list } RPARENS
	| LPARENS rvalue_expr RPARENS
	;

param_list :
	  rvalue_expr ( COMMA rvalue_expr )*
	;
