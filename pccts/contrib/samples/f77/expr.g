 /*********************/
 /*EXPRESSION section */
 /*********************/
expression > [int ret_type]: <<int type = 0;>>
		expr0
		<<$ret_type = type;>> /*Only needed for the PARAMETER statement*/
		;

expr0: <<int type;>>
	(expr1 (PLU|MIN|AND|OR|NEQV|EQV))?
		expr1 (PLU^|MIN^|AND^|OR^|NEQV^|EQV^) expr0
	|expr1
	;

expr1: <<int type;>>
	(expr2 (DIV|STAR|LT|LE|EQ|NE|GT|GE|IS|CONCAT))?
		expr2 (DIV^|STAR^ <<#1->token = MUL;>>|LT^|LE^|EQ^|NE^|GT^|GE^|IS^|CONCAT^) expr1
	|expr2
	;

expr2: <<int type;>>
	(operand > [type] POW)?
		operand > [type] POW^ expr2
	|operand > [type]
	;

operand > [int ret_type]: <<int type = 0;>>
	LP expression > [type] RP
	|variable[RVALUE]
	|constant > [type]
	|PLU^ expr0 <<#1->token = UNARY_PLU;>>
	|MIN^ expr0 <<#1->token = UNARY_MIN;>>
	|NOT^ expr0
	<<$ret_type = type;>>
	;
