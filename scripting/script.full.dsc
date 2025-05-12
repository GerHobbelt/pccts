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
	  SCRIPT title param_def_list sections ENDSCRIPT SCRIPT_EOF /* [0] { SCRIPT } */

	;

title :
	  VARIABLE /* [0] { VARIABLE } */

	;

sections :
	  { definitions /* [1] { DEFINITIONS } */
 /* [2] { DECLARATIONS IMPLEMENTATION SUBROUTINE } (optional branch) */
 } ( subroutine /* [0] { SUBROUTINE } */
 /* Opt { DECLARATIONS IMPLEMENTATION } */
 )* { declarations /* [1] { DECLARATIONS } */
 /* [2] { IMPLEMENTATION } (optional branch) */
 } implementation /* [0] { DECLARATIONS DEFINITIONS IMPLEMENTATION SUBROUTINE } */

	;

definitions :
	  DEFINITIONS ( structdef /* [1] { DEFINE } */
 | const_init_type_def /* [2] { CONST } */
 )+ /* [0] { DEFINITIONS } */

	;

structdef :
	  DEFINE VARIABLE AS ( type /* [1] { ARRAY BOOLEAN INTEGER REAL STRING VARIABLE } */
 | STRUCT ( vardecl /* [1] { VARIABLE } */
 )+ ENDSTRUCT /* [2] { STRUCT } */
 ) SEMICOLON /* [0] { DEFINE } */

	;

const_init_type_def :
	  const_init_type SEMICOLON /* [0] { CONST } */

	;

subroutine :
	  SUBROUTINE title param_def_list COLON return_type sections ENDSUB /* [0] { SUBROUTINE } */

	;

param_def_list :
	  LPARENS { ( param_def ( COMMA param_def /* [0] { COMMA } */
 /* Opt { RPARENS COMMA }, { DECLARATIONS DEFINITIONS IMPLEMENTATION SUBROUTINE TRIPLE_DOT COLON } */
 )* { COMMA TRIPLE_DOT /* [1] { COMMA } */
 /* [2] { RPARENS } (optional branch) */
 } /* [1] { VARIABLE } */
 | TRIPLE_DOT /* [2] { TRIPLE_DOT } */
 ) /* [1] { TRIPLE_DOT VARIABLE } */
 /* [2] { RPARENS } (optional branch) */
 } RPARENS /* [0] { LPARENS } */

	;

param_def :
	  VARIABLE { COLON sub_param_type /* [1] { COLON } */
 /* [2] { RPARENS COMMA } (optional branch) */
 } /* [0] { VARIABLE } */

	;

declarations :
	  DECLARATIONS ( vardecl /* [1] { VARIABLE } */
 )+ /* [0] { DECLARATIONS } */

	;

vardecl :
	  VARIABLE COLON ( type /* [1] { ARRAY BOOLEAN INTEGER REAL STRING VARIABLE } */
 | const_init_type /* [2] { CONST } */
 ) SEMICOLON /* [0] { VARIABLE } */

	;

sub_param_type :
	  { CONST /* [1] { CONST } */
 /* [2] { ANY ARRAY BOOLEAN INTEGER REAL STRING VARIABLE } (optional branch) */
 } ( type /* [1] { ARRAY BOOLEAN INTEGER REAL STRING VARIABLE } */
 | ANY /* [2] { ANY } */
 ) /* [0] { ANY ARRAY BOOLEAN CONST INTEGER REAL STRING VARIABLE } */

	;

return_type :
	  type /* [1] { ARRAY BOOLEAN INTEGER REAL STRING VARIABLE } */

	| VOID /* [2] { VOID } */

	| ANY /* [3] { ANY } */

	;

type :
	  BOOLEAN /* [1] { BOOLEAN } */

	| integer_type /* [2] { INTEGER } */

	| REAL /* [3] { REAL } */

	| STRING /* [4] { STRING } */

	| ARRAY OF type /* [5] { ARRAY } */

	| VARIABLE /* [6] { VARIABLE } */

	;

integer_type :
	  INTEGER { MULTIPLY INT_VALUE /* [1] { MULTIPLY } */
 /* [2] { DECLARATIONS DEFINITIONS IMPLEMENTATION SUBROUTINE ASSIGN RPARENS COMMA SEMICOLON } (optional branch) */
 } /* [0] { INTEGER } */

	;

const_init_type :
	  CONST integer_type ASSIGN INT_VALUE /* [1] { CONST }, { INTEGER } */

	| CONST REAL ASSIGN REAL_VALUE /* [2] { CONST }, { REAL } */

	| CONST BOOLEAN ASSIGN BOOLEAN_VALUE /* [3] { CONST }, { BOOLEAN } */

	| CONST STRING ASSIGN const_string_value /* [4] { CONST }, { STRING } */

	| CONST VARIABLE ASSIGN INT_VALUE /* [5] { CONST }, { VARIABLE } */

	;

const_string_value :
	  ( STRING_VALUE /* [1] { STRING_VALUE } */
 )+ /* [0] { STRING_VALUE } */

	;

implementation :
	  IMPLEMENTATION ( statement /* [1] { BREAK CONTINUE GOTO HALT IF REPEAT RESET RETURN VOID WHILE BEGIN VARIABLE } */
 )+ /* [0] { IMPLEMENTATION } */

	;

statement :
	  assignment_statement /* [1] { VOID VARIABLE }, { BOOLEAN_FALSE BOOLEAN_TRUE ASSIGN ASSIGN_PLUS ASSIGN_MINUS ASSIGN_MULTIPLY ASSIGN_DIVIDE ASSIGN_MODULO ASSIGN_POWER ASSIGN_LSHIFT ASSIGN_RSHIFT ASSIGN_BITWISE_OR ASSIGN_BITWISE_AND ASSIGN_BITWISE_XOR ASSIGN_BOOLEAN_OR ASSIGN_BOOLEAN_AND BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS LBRACKET DOT STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	| conditional_statement /* [2] { IF } */

	| loop_statement /* [3] { REPEAT WHILE } */

	| block_statement /* [4] { BEGIN } */

	| return_statement /* [5] { RETURN } */

	| break_statement /* [6] { BREAK CONTINUE } */

	| label_statement /* [7] { GOTO VARIABLE }, { COLON VARIABLE } */

	| special_statement /* [8] { HALT RESET } */

	;

return_statement :
	  RETURN SEMICOLON /* [0] { RETURN } */

	;

label_statement :
	  VARIABLE COLON /* [1] { VARIABLE } */

	| GOTO VARIABLE SEMICOLON /* [2] { GOTO } */

	;

break_statement :
	  BREAK SEMICOLON /* [1] { BREAK } */

	| CONTINUE SEMICOLON /* [2] { CONTINUE } */

	;

special_statement :
	  RESET SEMICOLON /* [1] { RESET } */

	| HALT SEMICOLON /* [2] { HALT } */

	;

assignment_statement :
	  lvalue_expr ( ASSIGNMENT rvalue_expr /* [1] { ASSIGN ASSIGN_PLUS ASSIGN_MINUS ASSIGN_MULTIPLY ASSIGN_DIVIDE ASSIGN_MODULO ASSIGN_POWER ASSIGN_LSHIFT ASSIGN_RSHIFT ASSIGN_BITWISE_OR ASSIGN_BITWISE_AND ASSIGN_BITWISE_XOR ASSIGN_BOOLEAN_OR ASSIGN_BOOLEAN_AND } */
 | PLUS PLUS /* [2] { PLUS } */
 | MINUS MINUS /* [3] { MINUS } */
 ) SEMICOLON /* [1] { VARIABLE } */

	| VOID rvalue_expr SEMICOLON /* [2] { VOID } */

	;

conditional_statement :
	  IF bracketed_conditional_expr block_statement ( ELIF bracketed_conditional_expr block_statement /* [0] { ELIF } */
 /* Opt { ELSE ENDIF } */
 )* { ELSE block_statement /* [1] { ELSE } */
 /* [2] { ENDIF } (optional branch) */
 } ENDIF SEMICOLON /* [0] { IF } */

	;

loop_statement :
	  WHILE bracketed_conditional_expr DO block_statement DONE SEMICOLON /* [1] { WHILE } */

	| REPEAT block_statement UNTIL bracketed_conditional_expr SEMICOLON /* [2] { REPEAT } */

	;

bracketed_conditional_expr :
	  LPARENS rvalue_expr RPARENS /* [0] { LPARENS } */

	;

block_statement :
	  BEGIN ( statement /* [1] { BREAK CONTINUE GOTO HALT IF REPEAT RESET RETURN VOID WHILE BEGIN VARIABLE } */
 )+ END /* [0] { BEGIN } */

	;

lvalue_expr :
	  elemental_variable /* [0] { VARIABLE } */

	;

elemental_variable :
	  VARIABLE ( LBRACKET rvalue_expr RBRACKET /* [0] { LBRACKET } */
 /* Opt { BOOLEAN_AND BOOLEAN_OR BITWISE_AND BITWISE_OR BITWISE_XOR ASSIGN ASSIGN_PLUS ASSIGN_MINUS ASSIGN_MULTIPLY ASSIGN_DIVIDE ASSIGN_MODULO ASSIGN_POWER ASSIGN_LSHIFT ASSIGN_RSHIFT ASSIGN_BITWISE_OR ASSIGN_BITWISE_AND ASSIGN_BITWISE_XOR ASSIGN_BOOLEAN_OR ASSIGN_BOOLEAN_AND LSHIFT RSHIFT GE GT EQ LE LT NE DIVIDE MODULO POWER MINUS PLUS MULTIPLY RPARENS RBRACKET COMMA DOT SEMICOLON } */
 )* ( DOT VARIABLE ( LBRACKET rvalue_expr RBRACKET /* [0] { LBRACKET } */
 /* Opt { BOOLEAN_AND BOOLEAN_OR BITWISE_AND BITWISE_OR BITWISE_XOR ASSIGN ASSIGN_PLUS ASSIGN_MINUS ASSIGN_MULTIPLY ASSIGN_DIVIDE ASSIGN_MODULO ASSIGN_POWER ASSIGN_LSHIFT ASSIGN_RSHIFT ASSIGN_BITWISE_OR ASSIGN_BITWISE_AND ASSIGN_BITWISE_XOR ASSIGN_BOOLEAN_OR ASSIGN_BOOLEAN_AND LSHIFT RSHIFT GE GT EQ LE LT NE DIVIDE MODULO POWER MINUS PLUS MULTIPLY RPARENS RBRACKET COMMA DOT SEMICOLON } */
 )* /* [0] { DOT } */
 /* Opt { BOOLEAN_AND BOOLEAN_OR BITWISE_AND BITWISE_OR BITWISE_XOR ASSIGN ASSIGN_PLUS ASSIGN_MINUS ASSIGN_MULTIPLY ASSIGN_DIVIDE ASSIGN_MODULO ASSIGN_POWER ASSIGN_LSHIFT ASSIGN_RSHIFT ASSIGN_BITWISE_OR ASSIGN_BITWISE_AND ASSIGN_BITWISE_XOR ASSIGN_BOOLEAN_OR ASSIGN_BOOLEAN_AND LSHIFT RSHIFT GE GT EQ LE LT NE DIVIDE MODULO POWER MINUS PLUS MULTIPLY RPARENS RBRACKET COMMA SEMICOLON } */
 )* /* [0] { VARIABLE } */

	;

rvalue_expr :
	  compare_or_rvalue_expr /* [0] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	;

compare_or_rvalue_expr :
	  compare_and_rvalue_expr ( BOOLEAN_OR compare_and_rvalue_expr /* [0] { BOOLEAN_OR } */
 /* Opt { RPARENS RBRACKET COMMA SEMICOLON } */
 )* /* [0] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	;

compare_and_rvalue_expr :
	  bitwise_or_rvalue_expr ( BOOLEAN_AND bitwise_or_rvalue_expr /* [0] { BOOLEAN_AND } */
 /* Opt { BOOLEAN_OR RPARENS RBRACKET COMMA SEMICOLON } */
 )* /* [0] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	;

bitwise_or_rvalue_expr :
	  bitwise_xor_rvalue_expr ( BITWISE_OR bitwise_xor_rvalue_expr /* [0] { BITWISE_OR } */
 /* Opt { BOOLEAN_AND BOOLEAN_OR RPARENS RBRACKET COMMA SEMICOLON } */
 )* /* [0] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	;

bitwise_xor_rvalue_expr :
	  bitwise_and_rvalue_expr ( BITWISE_XOR bitwise_and_rvalue_expr /* [0] { BITWISE_XOR } */
 /* Opt { BOOLEAN_AND BOOLEAN_OR BITWISE_OR RPARENS RBRACKET COMMA SEMICOLON } */
 )* /* [0] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	;

bitwise_and_rvalue_expr :
	  compare_ne_rvalue_expr ( BITWISE_AND compare_ne_rvalue_expr /* [0] { BITWISE_AND } */
 /* Opt { BOOLEAN_AND BOOLEAN_OR BITWISE_OR BITWISE_XOR RPARENS RBRACKET COMMA SEMICOLON } */
 )* /* [0] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	;

compare_ne_rvalue_expr :
	  compare_eq_rvalue_expr ( NE compare_eq_rvalue_expr /* [0] { NE } */
 /* Opt { BOOLEAN_AND BOOLEAN_OR BITWISE_AND BITWISE_OR BITWISE_XOR RPARENS RBRACKET COMMA SEMICOLON } */
 )* /* [0] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	;

compare_eq_rvalue_expr :
	  compare_ge_rvalue_expr ( EQ compare_ge_rvalue_expr /* [0] { EQ } */
 /* Opt { BOOLEAN_AND BOOLEAN_OR BITWISE_AND BITWISE_OR BITWISE_XOR NE RPARENS RBRACKET COMMA SEMICOLON } */
 )* /* [0] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	;

compare_ge_rvalue_expr :
	  compare_gt_rvalue_expr ( GE compare_gt_rvalue_expr /* [0] { GE } */
 /* Opt { BOOLEAN_AND BOOLEAN_OR BITWISE_AND BITWISE_OR BITWISE_XOR EQ NE RPARENS RBRACKET COMMA SEMICOLON } */
 )* /* [0] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	;

compare_gt_rvalue_expr :
	  compare_le_rvalue_expr ( GT compare_le_rvalue_expr /* [0] { GT } */
 /* Opt { BOOLEAN_AND BOOLEAN_OR BITWISE_AND BITWISE_OR BITWISE_XOR GE EQ NE RPARENS RBRACKET COMMA SEMICOLON } */
 )* /* [0] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	;

compare_le_rvalue_expr :
	  compare_lt_rvalue_expr ( LE compare_lt_rvalue_expr /* [0] { LE } */
 /* Opt { BOOLEAN_AND BOOLEAN_OR BITWISE_AND BITWISE_OR BITWISE_XOR GE GT EQ NE RPARENS RBRACKET COMMA SEMICOLON } */
 )* /* [0] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	;

compare_lt_rvalue_expr :
	  rshift_rvalue_expr ( LT rshift_rvalue_expr /* [0] { LT } */
 /* Opt { BOOLEAN_AND BOOLEAN_OR BITWISE_AND BITWISE_OR BITWISE_XOR GE GT EQ LE NE RPARENS RBRACKET COMMA SEMICOLON } */
 )* /* [0] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	;

rshift_rvalue_expr :
	  lshift_rvalue_expr ( RSHIFT lshift_rvalue_expr /* [0] { RSHIFT } */
 /* Opt { BOOLEAN_AND BOOLEAN_OR BITWISE_AND BITWISE_OR BITWISE_XOR GE GT EQ LE LT NE RPARENS RBRACKET COMMA SEMICOLON } */
 )* /* [0] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	;

lshift_rvalue_expr :
	  substract_rvalue_expr ( LSHIFT substract_rvalue_expr /* [0] { LSHIFT } */
 /* Opt { BOOLEAN_AND BOOLEAN_OR BITWISE_AND BITWISE_OR BITWISE_XOR RSHIFT GE GT EQ LE LT NE RPARENS RBRACKET COMMA SEMICOLON } */
 )* /* [0] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	;

substract_rvalue_expr :
	  add_rvalue_expr ( MINUS add_rvalue_expr /* [0] { MINUS } */
 /* Opt { BOOLEAN_AND BOOLEAN_OR BITWISE_AND BITWISE_OR BITWISE_XOR LSHIFT RSHIFT GE GT EQ LE LT NE RPARENS RBRACKET COMMA SEMICOLON } */
 )* /* [0] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	;

add_rvalue_expr :
	  modulo_rvalue_expr ( PLUS modulo_rvalue_expr /* [0] { PLUS } */
 /* Opt { BOOLEAN_AND BOOLEAN_OR BITWISE_AND BITWISE_OR BITWISE_XOR LSHIFT RSHIFT GE GT EQ LE LT NE MINUS RPARENS RBRACKET COMMA SEMICOLON } */
 )* /* [0] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	;

modulo_rvalue_expr :
	  divide_rvalue_expr ( MODULO divide_rvalue_expr /* [0] { MODULO } */
 /* Opt { BOOLEAN_AND BOOLEAN_OR BITWISE_AND BITWISE_OR BITWISE_XOR LSHIFT RSHIFT GE GT EQ LE LT NE MINUS PLUS RPARENS RBRACKET COMMA SEMICOLON } */
 )* /* [0] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	;

divide_rvalue_expr :
	  multiply_rvalue_expr ( DIVIDE multiply_rvalue_expr /* [0] { DIVIDE } */
 /* Opt { BOOLEAN_AND BOOLEAN_OR BITWISE_AND BITWISE_OR BITWISE_XOR LSHIFT RSHIFT GE GT EQ LE LT NE MODULO MINUS PLUS RPARENS RBRACKET COMMA SEMICOLON } */
 )* /* [0] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	;

multiply_rvalue_expr :
	  power_rvalue_expr ( MULTIPLY power_rvalue_expr /* [0] { MULTIPLY } */
 /* Opt { BOOLEAN_AND BOOLEAN_OR BITWISE_AND BITWISE_OR BITWISE_XOR LSHIFT RSHIFT GE GT EQ LE LT NE DIVIDE MODULO MINUS PLUS RPARENS RBRACKET COMMA SEMICOLON } */
 )* /* [0] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	;

power_rvalue_expr :
	  unary_rvalue_expr ( POWER unary_rvalue_expr /* [0] { POWER } */
 /* Opt { BOOLEAN_AND BOOLEAN_OR BITWISE_AND BITWISE_OR BITWISE_XOR LSHIFT RSHIFT GE GT EQ LE LT NE DIVIDE MODULO MINUS PLUS MULTIPLY RPARENS RBRACKET COMMA SEMICOLON } */
 )* /* [0] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	;

unary_rvalue_expr :
	  simple_rvalue_expr /* [1] { BOOLEAN_FALSE BOOLEAN_TRUE LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	| UNARY_OPERATOR unary_rvalue_expr /* [2] { BITWISE_NOT MINUS PLUS BOOLEAN_NOT } */

	;

simple_rvalue_expr :
	  INT_VALUE /* [1] { INT_VALUE } */

	| REAL_VALUE /* [2] { REAL_VALUE } */

	| BOOLEAN_VALUE /* [3] { BOOLEAN_FALSE BOOLEAN_TRUE } */

	| const_string_value /* [4] { STRING_VALUE } */

	| elemental_variable /* [5] { VARIABLE }, { BOOLEAN_AND BOOLEAN_OR BITWISE_AND BITWISE_OR BITWISE_XOR LSHIFT RSHIFT GE GT EQ LE LT NE DIVIDE MODULO POWER MINUS PLUS MULTIPLY RPARENS LBRACKET RBRACKET COMMA DOT SEMICOLON } */

	| VARIABLE LPARENS { param_list /* [1] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */
 /* [2] { RPARENS } (optional branch) */
 } RPARENS /* [6] { VARIABLE }, { LPARENS } */

	| LPARENS rvalue_expr RPARENS /* [7] { LPARENS } */

	;

param_list :
	  rvalue_expr ( COMMA rvalue_expr /* [0] { COMMA } */
 /* Opt { RPARENS } */
 )* /* [0] { BOOLEAN_FALSE BOOLEAN_TRUE BITWISE_NOT MINUS PLUS BOOLEAN_NOT LPARENS STRING_VALUE INT_VALUE REAL_VALUE VARIABLE } */

	;

Tree Nodes:  peak 5  created 15  lost 0


Dump of First/Follow Cache

rule add_rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule add_rvalue_expr Follow[1]

     BOOLEAN_AND      BOOLEAN_OR       BITWISE_AND      BITWISE_OR      
     BITWISE_XOR      LSHIFT           RSHIFT           GE              
     GT               EQ               LE               LT              
     NE               MINUS            RPARENS          RBRACKET        
     COMMA            SEMICOLON       

rule assignment_statement First[1]

     VOID             VARIABLE        

rule assignment_statement First[2]

     BOOLEAN_FALSE    BOOLEAN_TRUE     ASSIGN           ASSIGN_PLUS     
     ASSIGN_MINUS     ASSIGN_MULTIPLY  ASSIGN_DIVIDE    ASSIGN_MODULO   
     ASSIGN_POWER     ASSIGN_LSHIFT    ASSIGN_RSHIFT    ASSIGN_BITWISE_OR
     ASSIGN_BITWISE_AND ASSIGN_BITWISE_XOR ASSIGN_BOOLEAN_OR ASSIGN_BOOLEAN_AND
     BITWISE_NOT      MINUS            PLUS             BOOLEAN_NOT     
     LPARENS          LBRACKET         DOT              STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule bitwise_and_rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule bitwise_and_rvalue_expr Follow[1]

     BOOLEAN_AND      BOOLEAN_OR       BITWISE_OR       BITWISE_XOR     
     RPARENS          RBRACKET         COMMA            SEMICOLON       

rule bitwise_or_rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule bitwise_or_rvalue_expr Follow[1]

     BOOLEAN_AND      BOOLEAN_OR       RPARENS          RBRACKET        
     COMMA            SEMICOLON       

rule bitwise_xor_rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule bitwise_xor_rvalue_expr Follow[1]

     BOOLEAN_AND      BOOLEAN_OR       BITWISE_OR       RPARENS         
     RBRACKET         COMMA            SEMICOLON       

rule block_statement First[1]

     BEGIN           

rule break_statement First[1]

     BREAK            CONTINUE        

rule compare_and_rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule compare_and_rvalue_expr Follow[1]

     BOOLEAN_OR       RPARENS          RBRACKET         COMMA           
     SEMICOLON       

rule compare_eq_rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule compare_eq_rvalue_expr Follow[1]

     BOOLEAN_AND      BOOLEAN_OR       BITWISE_AND      BITWISE_OR      
     BITWISE_XOR      NE               RPARENS          RBRACKET        
     COMMA            SEMICOLON       

rule compare_ge_rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule compare_ge_rvalue_expr Follow[1]

     BOOLEAN_AND      BOOLEAN_OR       BITWISE_AND      BITWISE_OR      
     BITWISE_XOR      EQ               NE               RPARENS         
     RBRACKET         COMMA            SEMICOLON       

rule compare_gt_rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule compare_gt_rvalue_expr Follow[1]

     BOOLEAN_AND      BOOLEAN_OR       BITWISE_AND      BITWISE_OR      
     BITWISE_XOR      GE               EQ               NE              
     RPARENS          RBRACKET         COMMA            SEMICOLON       

rule compare_le_rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule compare_le_rvalue_expr Follow[1]

     BOOLEAN_AND      BOOLEAN_OR       BITWISE_AND      BITWISE_OR      
     BITWISE_XOR      GE               GT               EQ              
     NE               RPARENS          RBRACKET         COMMA           
     SEMICOLON       

rule compare_lt_rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule compare_lt_rvalue_expr Follow[1]

     BOOLEAN_AND      BOOLEAN_OR       BITWISE_AND      BITWISE_OR      
     BITWISE_XOR      GE               GT               EQ              
     LE               NE               RPARENS          RBRACKET        
     COMMA            SEMICOLON       

rule compare_ne_rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule compare_ne_rvalue_expr Follow[1]

     BOOLEAN_AND      BOOLEAN_OR       BITWISE_AND      BITWISE_OR      
     BITWISE_XOR      RPARENS          RBRACKET         COMMA           
     SEMICOLON       

rule compare_or_rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule compare_or_rvalue_expr Follow[1]

     RPARENS          RBRACKET         COMMA            SEMICOLON       

rule conditional_statement First[1]

     IF              

rule const_init_type First[1]

     CONST           

rule const_init_type Follow[1]

     SEMICOLON       

rule const_init_type_def First[1]

     CONST           

rule const_string_value First[1]

     STRING_VALUE    

rule const_string_value Follow[1]

     BOOLEAN_AND      BOOLEAN_OR       BITWISE_AND      BITWISE_OR      
     BITWISE_XOR      LSHIFT           RSHIFT           GE              
     GT               EQ               LE               LT              
     NE               DIVIDE           MODULO           POWER           
     MINUS            PLUS             MULTIPLY         RPARENS         
     RBRACKET         COMMA            SEMICOLON       

rule declarations First[1]

     DECLARATIONS    

rule declarations Follow[1]

     IMPLEMENTATION  

rule definitions First[1]

     DEFINITIONS     

rule definitions Follow[1]

     DECLARATIONS     IMPLEMENTATION   SUBROUTINE      

rule divide_rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule divide_rvalue_expr Follow[1]

     BOOLEAN_AND      BOOLEAN_OR       BITWISE_AND      BITWISE_OR      
     BITWISE_XOR      LSHIFT           RSHIFT           GE              
     GT               EQ               LE               LT              
     NE               MODULO           MINUS            PLUS            
     RPARENS          RBRACKET         COMMA            SEMICOLON       

rule elemental_variable First[1]

     VARIABLE        

rule elemental_variable First[2]

     LBRACKET         DOT             

rule elemental_variable Follow[1]

     BOOLEAN_AND      BOOLEAN_OR       BITWISE_AND      BITWISE_OR      
     BITWISE_XOR      ASSIGN           ASSIGN_PLUS      ASSIGN_MINUS    
     ASSIGN_MULTIPLY  ASSIGN_DIVIDE    ASSIGN_MODULO    ASSIGN_POWER    
     ASSIGN_LSHIFT    ASSIGN_RSHIFT    ASSIGN_BITWISE_OR ASSIGN_BITWISE_AND
     ASSIGN_BITWISE_XOR ASSIGN_BOOLEAN_OR ASSIGN_BOOLEAN_AND LSHIFT          
     RSHIFT           GE               GT               EQ              
     LE               LT               NE               DIVIDE          
     MODULO           POWER            MINUS            PLUS            
     MULTIPLY         RPARENS          RBRACKET         COMMA           
     SEMICOLON       

rule implementation First[1]

     IMPLEMENTATION  

rule implementation Follow[1]

     ENDSCRIPT        ENDSUB          

rule integer_type First[1]

     INTEGER         

rule integer_type Follow[1]

     DECLARATIONS     DEFINITIONS      IMPLEMENTATION   SUBROUTINE      
     ASSIGN           RPARENS          COMMA            SEMICOLON       

rule label_statement First[1]

     GOTO             VARIABLE        

rule label_statement First[2]

     COLON            VARIABLE        

rule loop_statement First[1]

     REPEAT           WHILE           

rule lshift_rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule lshift_rvalue_expr Follow[1]

     BOOLEAN_AND      BOOLEAN_OR       BITWISE_AND      BITWISE_OR      
     BITWISE_XOR      RSHIFT           GE               GT              
     EQ               LE               LT               NE              
     RPARENS          RBRACKET         COMMA            SEMICOLON       

rule lvalue_expr First[1]

     VARIABLE        

rule lvalue_expr First[2]

     LBRACKET         DOT             

rule lvalue_expr Follow[1]

     ASSIGN           ASSIGN_PLUS      ASSIGN_MINUS     ASSIGN_MULTIPLY 
     ASSIGN_DIVIDE    ASSIGN_MODULO    ASSIGN_POWER     ASSIGN_LSHIFT   
     ASSIGN_RSHIFT    ASSIGN_BITWISE_OR ASSIGN_BITWISE_AND ASSIGN_BITWISE_XOR
     ASSIGN_BOOLEAN_OR ASSIGN_BOOLEAN_AND MINUS            PLUS            

rule modulo_rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule modulo_rvalue_expr Follow[1]

     BOOLEAN_AND      BOOLEAN_OR       BITWISE_AND      BITWISE_OR      
     BITWISE_XOR      LSHIFT           RSHIFT           GE              
     GT               EQ               LE               LT              
     NE               MINUS            PLUS             RPARENS         
     RBRACKET         COMMA            SEMICOLON       

rule multiply_rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule multiply_rvalue_expr Follow[1]

     BOOLEAN_AND      BOOLEAN_OR       BITWISE_AND      BITWISE_OR      
     BITWISE_XOR      LSHIFT           RSHIFT           GE              
     GT               EQ               LE               LT              
     NE               DIVIDE           MODULO           MINUS           
     PLUS             RPARENS          RBRACKET         COMMA           
     SEMICOLON       

rule param_def First[1]

     VARIABLE        

rule param_def Follow[1]

     RPARENS          COMMA           

rule param_def_list Follow[1]

     DECLARATIONS     DEFINITIONS      IMPLEMENTATION   SUBROUTINE      
     COLON           

rule param_list First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule param_list Follow[1]

     RPARENS         

rule power_rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule power_rvalue_expr Follow[1]

     BOOLEAN_AND      BOOLEAN_OR       BITWISE_AND      BITWISE_OR      
     BITWISE_XOR      LSHIFT           RSHIFT           GE              
     GT               EQ               LE               LT              
     NE               DIVIDE           MODULO           MINUS           
     PLUS             MULTIPLY         RPARENS          RBRACKET        
     COMMA            SEMICOLON       

rule return_statement First[1]

     RETURN          

rule return_type Follow[1]

     DECLARATIONS     DEFINITIONS      IMPLEMENTATION   SUBROUTINE      

rule rshift_rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule rshift_rvalue_expr Follow[1]

     BOOLEAN_AND      BOOLEAN_OR       BITWISE_AND      BITWISE_OR      
     BITWISE_XOR      GE               GT               EQ              
     LE               LT               NE               RPARENS         
     RBRACKET         COMMA            SEMICOLON       

rule rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule rvalue_expr Follow[1]

     RPARENS          RBRACKET         COMMA            SEMICOLON       

rule sections First[1]

     DECLARATIONS     DEFINITIONS      IMPLEMENTATION   SUBROUTINE      

rule sections Follow[1]

     ENDSCRIPT        ENDSUB          

rule simple_rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule simple_rvalue_expr Follow[1]

     BOOLEAN_AND      BOOLEAN_OR       BITWISE_AND      BITWISE_OR      
     BITWISE_XOR      LSHIFT           RSHIFT           GE              
     GT               EQ               LE               LT              
     NE               DIVIDE           MODULO           POWER           
     MINUS            PLUS             MULTIPLY         RPARENS         
     RBRACKET         COMMA            SEMICOLON       

rule special_statement First[1]

     HALT             RESET           

rule statement First[1]

     BREAK            CONTINUE         GOTO             HALT            
     IF               REPEAT           RESET            RETURN          
     VOID             WHILE            BEGIN            VARIABLE        

rule structdef First[1]

     DEFINE          

rule sub_param_type Follow[1]

     RPARENS          COMMA           

rule subroutine First[1]

     SUBROUTINE      

rule substract_rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule substract_rvalue_expr Follow[1]

     BOOLEAN_AND      BOOLEAN_OR       BITWISE_AND      BITWISE_OR      
     BITWISE_XOR      LSHIFT           RSHIFT           GE              
     GT               EQ               LE               LT              
     NE               RPARENS          RBRACKET         COMMA           
     SEMICOLON       

rule type First[1]

     ARRAY            BOOLEAN          INTEGER          REAL            
     STRING           VARIABLE        

rule type Follow[1]

     DECLARATIONS     DEFINITIONS      IMPLEMENTATION   SUBROUTINE      
     RPARENS          COMMA            SEMICOLON       

rule unary_rvalue_expr First[1]

     BOOLEAN_FALSE    BOOLEAN_TRUE     BITWISE_NOT      MINUS           
     PLUS             BOOLEAN_NOT      LPARENS          STRING_VALUE    
     INT_VALUE        REAL_VALUE       VARIABLE        

rule unary_rvalue_expr Follow[1]

     BOOLEAN_AND      BOOLEAN_OR       BITWISE_AND      BITWISE_OR      
     BITWISE_XOR      LSHIFT           RSHIFT           GE              
     GT               EQ               LE               LT              
     NE               DIVIDE           MODULO           POWER           
     MINUS            PLUS             MULTIPLY         RPARENS         
     RBRACKET         COMMA            SEMICOLON       

rule vardecl First[1]

     VARIABLE        

End dump of First/Follow Cache
