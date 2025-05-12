 /*******************/
 /*REAL statement   */
 /*******************/
real_statement: {LABEL} REAL^ {STAR length_spec} {COMMA}
		real_item (COMMA real_item)*;
real_item :	(init_real_item)? init_real_item
		|(uninit_real_item)? uninit_real_item
		;
init_real_item:	real_var_list DIV real_const_list DIV;
uninit_real_item: real_var_list;

real_var_list: (var_decl[REAL_ID] COMMA)? var_decl[REAL_ID] COMMA real_var_list
		|var_decl[REAL_ID]
		;

real_const_list	: (real_const COMMA)? real_const COMMA real_const_list
		|real_const
		;
var_decl[int type]:
		(IDENTIFIER LP)? array_declarer[type]
		|(i:IDENTIFIER {STAR length_spec}
				<<
				#1->token = type;
				ChangeType($i.text,type);
				>>
		 )
		;

array_declarer[int type]:i:IDENTIFIER LP dimension_declarator (COMMA dimension_declarator)* RP {STAR length_spec}
		<<{
		switch(type) {
			case INTEGER_ID:type = INTEGER_ARRAY_ID; break;
			case REAL_ID:type = REAL_ARRAY_ID; break;
			case DOUBLE_PRECISION_ID:type = DOUBLE_PRECISION_ARRAY_ID; break;
			case CHARACTER_ID:type = CHARACTER_ARRAY_ID; break;
			case LOGICAL_ID:type = LOGICAL_ARRAY_ID; break;
			case DIMENSION:
				switch(LookUp($i.text)) {
					case FUNCTION_NAME: type = FUNCTION_NAME; break;
					case INTEGER_ARRAY_ID: type = INTEGER_ARRAY_ID; break;
					case REAL_ARRAY_ID: type = REAL_ARRAY_ID; break;
					case DOUBLE_PRECISION_ARRAY_ID: type = DOUBLE_PRECISION_ARRAY_ID; break;
					case CHARACTER_ARRAY_ID: type = CHARACTER_ARRAY_ID; break;
					case LOGICAL_ARRAY_ID: type = LOGICAL_ARRAY_ID; break;

					case INTEGER_ID:type = INTEGER_ARRAY_ID; break;
					case REAL_ID:type = REAL_ARRAY_ID; break;
					case DOUBLE_PRECISION_ID:type = DOUBLE_PRECISION_ARRAY_ID; break;
					case CHARACTER_ID:type = CHARACTER_ARRAY_ID; break;
					case LOGICAL_ID:type = LOGICAL_ARRAY_ID; break;
					case -1: /*Not found! Determine its type from its name.*/
						type = ((*($i.text) >= 'I') && (*($i.text) <= 'N'))?INTEGER_ARRAY_ID:REAL_ARRAY_ID;
						break;
					default:
						type = LookUp($i.text); /*Get it for debugging purposes!*/
						assert(1 == 0);
					}
				break;
			default:
				assert(1 == 0);
				break;
			}
		#1->token = type;
		ChangeType($i.text, type);
		}>>
		;

dimension_declarator:
	(lower_bound COLUMN)? lower_bound COLUMN upper_bound
	|upper_bound
	;
lower_bound: <<int type;>> expression > [type];
upper_bound: <<int type;>> expression > [type];

variable[int where]:
		(substring)? substring
		|(array_element_reference[where])? array_element_reference[where]
		|(i:IDENTIFIER
			<<{
			int type;
			type = LookUp($i.text);
			if((where == RVALUE) && (strlen($i.text) > 1)) /*It is not in implied do loop*/
				{
				/*If not found I assume its type from its name*/
				if(type == -1) {
					type = ((*($i.text) >= 'I') && (*($i.text) <= 'N'))?INTEGER_ID:REAL_ID;
					AddSymbol($i.text, type);
					}
				}
			else {
				if(type == -1) {
					type = ((*($i.text) >= 'I') && (*($i.text) <= 'N'))?INTEGER_ID:REAL_ID;
					AddSymbol($i.text, type);
					}
				}
			#1->token = type;
			}>>
			)
		;

array_element_reference[int where]:	/*Same as array_element_name*/
	<<int type;>>
	i:IDENTIFIER^ LP expression > [type] (COMMA expression > [type])* RP
	<<{
	int type;
	type = LookUp($i.text);
	assert(where == LVALUE || where == RVALUE);
	if((CurrentStatement == COMMON) && (type == FUNCTION_NAME)) {
		type = ((*($i.text) >= 'I') && (*($i.text) <= 'N'))?INTEGER_ARRAY_ID:REAL_ARRAY_ID;
		ChangeType($i.text,type);
		}
	else if(where == RVALUE) {
		if(type == -1) {/*Not found!*/
			/*It must be a function name. It is going to be declared later in the code.*/
			type = FUNCTION_NAME;
			AddSymbol($i.text, type); /*And add it to the symbol table.*/
			}
		}
	else {
		if(type == -1) {/*Not found! Determine its type from its name.*/
			type = ((*($i.text) >= 'I') && (*($i.text) <= 'N'))?INTEGER_ARRAY_ID:REAL_ARRAY_ID;
			AddSymbol($i.text, type); /*And add it to the symbol table.*/
			}
		}
	#1->token = type;
	}>>
	;

 /****************************/
 /*DOUBLE PRECISION statement*/
 /****************************/

double_precision_statement: {LABEL} DOUBLE_PRECISION^ {STAR length_spec} {COMMA}
		double_prec_item (COMMA double_prec_item)*;
double_prec_item :	(init_double_prec_item)? init_double_prec_item
		|(uninit_double_prec_item)? uninit_double_prec_item
		;
init_double_prec_item:	double_prec_var_list DIV double_prec_const_list DIV;
uninit_double_prec_item: double_prec_var_list;
double_prec_var_list: (var_decl[DOUBLE_PRECISION_ID] COMMA)? var_decl[DOUBLE_PRECISION_ID] COMMA double_prec_var_list
		|var_decl[DOUBLE_PRECISION_ID]
		;
double_prec_const_list	: (real_const COMMA)? real_const COMMA real_const_list
		|real_const
		;

 /*******************/
 /*INTEGER statement*/
 /*******************/

integer_statement: {LABEL} INTEGER^ {STAR length_spec} {COMMA}
		int_item (COMMA int_item)*;
int_item:	(init_int_item)? init_int_item
		|(uninit_int_item)? uninit_int_item
		;
init_int_item:	int_var_list DIV int_const_list DIV;
uninit_int_item: int_var_list;
int_var_list: (var_decl[INTEGER_ID] COMMA)? var_decl[INTEGER_ID] COMMA int_var_list
		|var_decl[INTEGER_ID]
		;
int_const_list: (int_const COMMA)? int_const COMMA int_const_list
		|int_const
		;

 /*********************/
 /*DIMENSION statement*/
 /*********************/
dimension_statement: {LABEL} DIMENSION^ array_declarer[DIMENSION] (COMMA array_declarer[DIMENSION])*
	 ;
 /*******************/
 /*LOGICAL statement*/
 /*******************/
logical_statement: {LABEL} LOGICAL^ {STAR length_spec} {COMMA}
		log_item (COMMA log_item)*;
log_item :	(init_log_item)? init_log_item
		|(uninit_log_item)? uninit_log_item
		;
init_log_item:	log_var_list DIV log_const_list DIV;
uninit_log_item: log_var_list;
log_var_list	: (var_decl[LOGICAL_ID] COMMA)? var_decl[LOGICAL_ID] COMMA log_var_list
		|var_decl[LOGICAL_ID]
		;
log_const_list	: (logical_const COMMA)? logical_const COMMA log_const_list
		|logical_const
		;
 /*********************/
 /*CHARACTER statement*/
 /*********************/

character_statement: {LABEL} CHARACTER^ {STAR length_spec} {COMMA}
		char_item (COMMA char_item)*;
char_item :	(init_char_item)? init_char_item
		|(uninit_char_item)? uninit_char_item
		;
init_char_item:	char_var_list DIV char_const_list DIV;
uninit_char_item: char_var_list;
char_var_list	: (var_decl[CHARACTER_ID] COMMA)? var_decl[CHARACTER_ID] COMMA char_var_list
		|var_decl[CHARACTER_ID]
		;
char_const_list	: (char_const COMMA)? char_const COMMA char_const_list
		|char_const
		;

substring: <<int type;>> /*Character variables have to be predefined!*/
	(
	(array_element_reference[RVALUE] LP)? array_element_reference[RVALUE] LP {expression > [type]}
		COLUMN {expression > [type]} RP
	|i:IDENTIFIER LP {expression > [type]} COLUMN {expression > [type]} RP
		<<
		ChangeType($i.text,CHARACTER_ID); /*Now I know that it is a character string*/
		#1->token = CHARACTER_SUBSTRING;
		>>
	)
	;
 /*******************/
 /*EXTERNAL statement   */
 /*******************/
external_statement: {LABEL} EXTERNAL^ function_name (COMMA function_name)*;
function_name:
	i:IDENTIFIER
		<<
		#1->token = FUNCTION_NAME;
		ChangeType($i.text, FUNCTION_NAME);
		>>
	;

 /*******************/
 /*INTRINSIC statement   */
 /*******************/
intrinsic_statement: {LABEL} INTRINSIC^ function_name (COMMA function_name)*
	;

 /*******************/
 /*SAVE statement   */
 /*******************/
save_statement: {LABEL} SAVE^ LP save_item (COMMA save_item)* RP
	;
save_item:
	DIV IDENTIFIER DIV /*Common block designator*/
	|IDENTIFIER
	;

 /*******************/
 /*IMPLICIT statement   */
 /*******************/
implicit_statement: {LABEL} IMPLICIT^ implicit_item (COMMA implicit_item)*
	;
implicit_item: implicit_type LP letter_spec (COMMA letter_spec)* RP
	;

implicit_type:(INTEGER
		|REAL
		|DOUBLE_PRECISION
		|LOGICAL
		|CHARACTER
		|COMPLEX
		|DOUBLE_COMPLEX)
		{STAR length_spec}
		;

letter_spec: IDENTIFIER {MIN IDENTIFIER}
	;

 /*******************/
 /*PARAMETER statement   */
 /*******************/
parameter_statement: {LABEL} PARAMETER^ LP para_item (COMMA para_item)* RP
	;

para_item:<<int type;>>
	i:IDENTIFIER EQUAL expression > [type]
	<<
	assert((type == INTEGER_ID) || (type == REAL_ID) || (type == CHARACTER_ID) || (type == LOGICAL_ID));
	ChangeType($i.text, type);
	#1->token = CONSTANT_NAME;
	>>
	;

 /*******************/
 /*ASSIGN statement   */
 /*******************/
assign_statement: {LABEL} ASSIGN^ CONSTINT TO i:IDENTIFIER
	<<
	AddSymbol($i.text, INTEGER_ID);
	>>
	;
