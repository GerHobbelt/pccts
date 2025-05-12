
grammar :
	  ( { LEXACTION | LEXMEMBER | LEXPREFIX | PARSERCLASS } ACTION )* start_states ( ACTION )* "@"
	;

start_states :
	  ( PER_PER do_conversion | NAME_PER_PER do_conversion ( NAME_PER_PER do_conversion )* ) PER_PER
	;

do_conversion :
	  rule_list
	;

rule_list :
	  rule ( rule )*
	|
	
	;

rule :
	  reg_expr ACTION
	| ACTION
	;

reg_expr :
	  and_expr ( OR and_expr )*
	;

and_expr :
	  repeat_expr ( repeat_expr )*
	;

repeat_expr :
	  expr { ZERO_MORE | ONE_MORE }
	| ZERO_MORE
	| ONE_MORE
	;

expr :
	  L_BRACK atom_list R_BRACK
	| NOT L_BRACK atom_list R_BRACK
	| L_PAR reg_expr R_PAR
	| L_BRACE reg_expr R_BRACE
	| atom
	;

atom_list :
	  ( near_atom )*
	;

near_atom :
	  anychar { RANGE anychar }
	;

atom :
	  anychar
	;

anychar :
	  REGCHAR
	| OCTAL_VALUE
	| HEX_VALUE
	| DEC_VALUE
	| TAB
	| NL
	| CR
	| BS
	| LIT
	| L_EOF
	;
