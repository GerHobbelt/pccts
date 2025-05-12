Cross Reference:

Rule              grammar referenced by { }
Rule         start_states referenced by { grammar }
Rule        do_conversion referenced by { start_states }
Rule            rule_list referenced by { do_conversion }
Rule                 rule referenced by { rule_list }
Rule             reg_expr referenced by { rule expr }
Rule             and_expr referenced by { reg_expr }
Rule          repeat_expr referenced by { and_expr }
Rule                 expr referenced by { repeat_expr }
Rule            atom_list referenced by { expr }
Rule            near_atom referenced by { atom_list }
Rule                 atom referenced by { expr }
Rule              anychar referenced by { near_atom atom }

grammar :
	  ( { LEXACTION /* [1] { LEXACTION } */
 | LEXMEMBER /* [2] { LEXMEMBER } */
 | LEXPREFIX /* [3] { LEXPREFIX } */
 | PARSERCLASS /* [4] { PARSERCLASS } */
 /* [2] { ACTION } (optional branch) */
 } ACTION /* [0] { LEXMEMBER LEXACTION PARSERCLASS LEXPREFIX ACTION } */
 /* Opt { PER_PER NAME_PER_PER } */
 )* start_states ( ACTION /* [0] { ACTION } */
 /* Opt { "@" } */
 )* "@" /* [0] { PER_PER NAME_PER_PER LEXMEMBER LEXACTION PARSERCLASS LEXPREFIX ACTION } */

	;

start_states :
	  ( PER_PER do_conversion /* [1] { PER_PER } */
 | NAME_PER_PER do_conversion ( NAME_PER_PER do_conversion /* [0] { NAME_PER_PER } */
 /* Opt { PER_PER } */
 )* /* [2] { NAME_PER_PER } */
 ) PER_PER /* [0] { PER_PER NAME_PER_PER } */

	;

do_conversion :
	  rule_list /* [0] { L_EOF PER_PER NAME_PER_PER ACTION L_BRACE L_PAR L_BRACK ZERO_MORE ONE_MORE NOT OCTAL_VALUE HEX_VALUE DEC_VALUE TAB NL CR BS LIT REGCHAR } */

	;

rule_list :
	  rule ( rule /* [0] { L_EOF ACTION L_BRACE L_PAR L_BRACK ZERO_MORE ONE_MORE NOT OCTAL_VALUE HEX_VALUE DEC_VALUE TAB NL CR BS LIT REGCHAR } */
 /* Opt { PER_PER NAME_PER_PER } */
 )* /* [1] { L_EOF ACTION L_BRACE L_PAR L_BRACK ZERO_MORE ONE_MORE NOT OCTAL_VALUE HEX_VALUE DEC_VALUE TAB NL CR BS LIT REGCHAR } */

	|
	 /* [2] { PER_PER NAME_PER_PER } */

	;

rule :
	  reg_expr ACTION /* [1] { L_EOF L_BRACE L_PAR L_BRACK ZERO_MORE ONE_MORE NOT OCTAL_VALUE HEX_VALUE DEC_VALUE TAB NL CR BS LIT REGCHAR } */

	| ACTION /* [2] { ACTION } */

	;

reg_expr :
	  and_expr ( OR and_expr /* [0] { OR } */
 /* Opt { ACTION R_BRACE R_PAR } */
 )* /* [0] { L_EOF L_BRACE L_PAR L_BRACK ZERO_MORE ONE_MORE NOT OCTAL_VALUE HEX_VALUE DEC_VALUE TAB NL CR BS LIT REGCHAR } */

	;

and_expr :
	  repeat_expr ( repeat_expr /* [0] { L_EOF L_BRACE L_PAR L_BRACK ZERO_MORE ONE_MORE NOT OCTAL_VALUE HEX_VALUE DEC_VALUE TAB NL CR BS LIT REGCHAR } */
 /* Opt { ACTION R_BRACE R_PAR OR } */
 )* /* [0] { L_EOF L_BRACE L_PAR L_BRACK ZERO_MORE ONE_MORE NOT OCTAL_VALUE HEX_VALUE DEC_VALUE TAB NL CR BS LIT REGCHAR } */

	;

repeat_expr :
	  expr { ZERO_MORE /* [1] { ZERO_MORE } */
 | ONE_MORE /* [2] { ONE_MORE } */
 /* [2] { L_EOF ACTION L_BRACE R_BRACE L_PAR R_PAR L_BRACK ZERO_MORE ONE_MORE OR NOT OCTAL_VALUE HEX_VALUE DEC_VALUE TAB NL CR BS LIT REGCHAR } (optional branch) */
 } /* [1] { L_EOF L_BRACE L_PAR L_BRACK NOT OCTAL_VALUE HEX_VALUE DEC_VALUE TAB NL CR BS LIT REGCHAR } */

	| ZERO_MORE /* [2] { ZERO_MORE } */

	| ONE_MORE /* [3] { ONE_MORE } */

	;

expr :
	  L_BRACK atom_list R_BRACK /* [1] { L_BRACK } */

	| NOT L_BRACK atom_list R_BRACK /* [2] { NOT } */

	| L_PAR reg_expr R_PAR /* [3] { L_PAR } */

	| L_BRACE reg_expr R_BRACE /* [4] { L_BRACE } */

	| atom /* [5] { L_EOF OCTAL_VALUE HEX_VALUE DEC_VALUE TAB NL CR BS LIT REGCHAR } */

	;

atom_list :
	  ( near_atom /* [0] { L_EOF OCTAL_VALUE HEX_VALUE DEC_VALUE TAB NL CR BS LIT REGCHAR } */
 /* Opt { R_BRACK } */
 )* /* [0] { L_EOF R_BRACK OCTAL_VALUE HEX_VALUE DEC_VALUE TAB NL CR BS LIT REGCHAR } */

	;

near_atom :
	  anychar { RANGE anychar /* [1] { RANGE } */
 /* [2] { L_EOF R_BRACK OCTAL_VALUE HEX_VALUE DEC_VALUE TAB NL CR BS LIT REGCHAR } (optional branch) */
 } /* [0] { L_EOF OCTAL_VALUE HEX_VALUE DEC_VALUE TAB NL CR BS LIT REGCHAR } */

	;

atom :
	  anychar /* [0] { L_EOF OCTAL_VALUE HEX_VALUE DEC_VALUE TAB NL CR BS LIT REGCHAR } */

	;

anychar :
	  REGCHAR /* [1] { REGCHAR } */

	| OCTAL_VALUE /* [2] { OCTAL_VALUE } */

	| HEX_VALUE /* [3] { HEX_VALUE } */

	| DEC_VALUE /* [4] { DEC_VALUE } */

	| TAB /* [5] { TAB } */

	| NL /* [6] { NL } */

	| CR /* [7] { CR } */

	| BS /* [8] { BS } */

	| LIT /* [9] { LIT } */

	| L_EOF /* [10] { L_EOF } */

	;


Dump of First/Follow Cache

rule and_expr First[1]

     L_EOF            L_BRACE          L_PAR            L_BRACK         
     ZERO_MORE        ONE_MORE         NOT              OCTAL_VALUE     
     HEX_VALUE        DEC_VALUE        TAB              NL              
     CR               BS               LIT              REGCHAR         

rule and_expr Follow[1]

     ACTION           R_BRACE          R_PAR            OR              

rule anychar First[1]

     L_EOF            OCTAL_VALUE      HEX_VALUE        DEC_VALUE       
     TAB              NL               CR               BS              
     LIT              REGCHAR         

rule atom First[1]

     L_EOF            OCTAL_VALUE      HEX_VALUE        DEC_VALUE       
     TAB              NL               CR               BS              
     LIT              REGCHAR         

rule atom_list Follow[1]

     R_BRACK         

rule do_conversion Follow[1]

     PER_PER          NAME_PER_PER    

rule expr First[1]

     L_EOF            L_BRACE          L_PAR            L_BRACK         
     NOT              OCTAL_VALUE      HEX_VALUE        DEC_VALUE       
     TAB              NL               CR               BS              
     LIT              REGCHAR         

rule near_atom First[1]

     L_EOF            OCTAL_VALUE      HEX_VALUE        DEC_VALUE       
     TAB              NL               CR               BS              
     LIT              REGCHAR         

rule near_atom Follow[1]

     L_EOF            R_BRACK          OCTAL_VALUE      HEX_VALUE       
     DEC_VALUE        TAB              NL               CR              
     BS               LIT              REGCHAR         

rule reg_expr First[1]

     L_EOF            L_BRACE          L_PAR            L_BRACK         
     ZERO_MORE        ONE_MORE         NOT              OCTAL_VALUE     
     HEX_VALUE        DEC_VALUE        TAB              NL              
     CR               BS               LIT              REGCHAR         

rule reg_expr Follow[1]

     ACTION           R_BRACE          R_PAR           

rule repeat_expr First[1]

     L_EOF            L_BRACE          L_PAR            L_BRACK         
     ZERO_MORE        ONE_MORE         NOT              OCTAL_VALUE     
     HEX_VALUE        DEC_VALUE        TAB              NL              
     CR               BS               LIT              REGCHAR         

rule repeat_expr Follow[1]

     L_EOF            ACTION           L_BRACE          R_BRACE         
     L_PAR            R_PAR            L_BRACK          ZERO_MORE       
     ONE_MORE         OR               NOT              OCTAL_VALUE     
     HEX_VALUE        DEC_VALUE        TAB              NL              
     CR               BS               LIT              REGCHAR         

rule rule First[1]

     L_EOF            ACTION           L_BRACE          L_PAR           
     L_BRACK          ZERO_MORE        ONE_MORE         NOT             
     OCTAL_VALUE      HEX_VALUE        DEC_VALUE        TAB             
     NL               CR               BS               LIT             
     REGCHAR         

rule rule_list First[1]

     L_EOF            ACTION           L_BRACE          L_PAR           
     L_BRACK          ZERO_MORE        ONE_MORE         NOT             
     OCTAL_VALUE      HEX_VALUE        DEC_VALUE        TAB             
     NL               CR               BS               LIT             
     REGCHAR         

rule rule_list Follow[1]

     PER_PER          NAME_PER_PER    

rule start_states First[1]

     PER_PER          NAME_PER_PER    

End dump of First/Follow Cache
