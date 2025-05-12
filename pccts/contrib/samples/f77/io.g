read_statement : {LABEL} READ^ LP control_info RP io_list[LVALUE]
		/*LVALUE: variables can be overwritten prior to being declared*/
		;
write_statement : {LABEL} WRITE^ LP control_info RP ((io_list[RVALUE])? io_list[RVALUE]|)
	/*Cannot write a variable which has not been declared.*/
	;
control_info: <<int type; int dummy;>>
		(
		(unit_identifier COMMA format_identifier)? unit_identifier COMMA^ format_identifier
		|(combined_expression COMMA format_identifier)? combined_expression COMMA format_identifier
		|(unit_identifier APOSTROPHY)? combined_expression
		|UNIT EQUAL^ unit_identifier
		|unit_identifier
		)
		(COMMA
		(FMT EQUAL format_identifier
		|IO_DATA EQUAL expression > [type]
		|REC EQUAL expression > [type]
		|END EQUAL label
		|ERR EQUAL label
		|(IOSTAT EQUAL operand > [dummy])
		|URGENT EQUAL expression > [type]))*
		;

unit_identifier: <<int type;>>
	(STAR)? STAR
	|expression > [type] /*Integer or character expressions allowed.*/
	;
format_identifier:<<int type;>> 
	(STAR)? STAR  {DIV <<#1->token = SLASH;>>/*UNISYS FORTRAN V3.8*/}
	|DIV <<#1->token = SLASH;>>	/*Now I know it is not division but just a slash.*/
	|i:IDENTIFIER	/*character or integer.*/
		<<
		/*If it has been assigned a label before than it must have been stored into the symbol table
		as an INTEGER_ID, if not than it must be a CHARACTER_ID*/
		type = LookUp($i.text);
		assert((type == INTEGER_ID) || (type == CHARACTER_ID) || (type == REAL_ID) || (type == -1));
		if(type == -1) {
			type = CHARACTER_ID;
			AddSymbol($i.text, CHARACTER_ID);
			}
		else if(type == REAL_ID) {
			type = CHARACTER_ID;
			ChangeType($i.text, CHARACTER_ID);
			}
		#1->token = type;
		>>
	|QUOTED_STRING
	|label
	;

combined_expression: <<int type;>>
	unit_identifier APOSTROPHY^ expression > [type];

io_list[int where] : io_list_item[where] /*I need where to resolve the declaration of variables*/
	(COMMA io_list_item[where])*
	;

io_list_item[int where]:<<int type;>>
	(
	(LP)? io_implied_do_list[where]
	|expression > [type]
	)
	;

io_implied_do_list[int where]:
	(LP <<#1->token = IMPLIED_LP;>>)
	(io_list_item[where] COMMA)+ io_implied_do_loop[where]
	(RP <<#1->token = IMPLIED_RP;>>)
	;

io_implied_do_loop[int where]: <<int type;>>
	IDENTIFIER EQUAL expression > [type]
	COMMA expression > [type]
	{COMMA expression > [type]}
	<<#1->token = IMPLIED_DO_VARIABLE;>>
	;

 /*UNISYS FORTRAN V3.8*/
find_statement: {LABEL} FIND^ LP findlist RP
	;
findlist: <<int type;>>
	(unit_identifier COMMA)? unit_identifier COMMA^ REC EQUAL expression > [type]
	|(unit_identifier APOSTROPHY)? unit_identifier APOSTROPHY^ expression > [type]
	|UNIT^ EQUAL unit_identifier COMMA REC EQUAL expression > [type]
	|REC^ EQUAL expression > [type] COMMA UNIT EQUAL unit_identifier
	;

 /*END UNISYS FORTRAN V3.8*/

open_statement: {LABEL} OPEN^ LP open_item (COMMA open_item)* RP
		;
open_item: <<int type; int dummy;>>
		{UNIT EQUAL} unit_identifier
		|ERR		EQUAL label
		|FILE_WORD	EQUAL expression > [type]
		|STATUS		EQUAL expression > [type]
		|ACCESS		EQUAL expression > [type]
		|FORM		EQUAL expression > [type]
		|RECL		EQUAL expression > [type]
		|(IOSTAT EQUAL operand > [dummy])
		|TITLE		EQUAL expression > [type]
		|DISP		EQUAL expression > [type]
		|SUBFILE	EQUAL expression > [type]
		|MAXRECSIZE	EQUAL expression > [type]
		|SAVEFACTOR	EQUAL expression > [type]
		|OPENTYPE	EQUAL expression > [type]
		;
close_statement: {LABEL} CLOSE^ LP close_item (COMMA close_item)* RP
		;
close_item: <<int type; int dummy;>>
		({UNIT EQUAL} unit_identifier
		|ERR		EQUAL label
		|STATUS		EQUAL close_name
		|(IOSTAT EQUAL operand > [dummy])
		|DISP		EQUAL close_name
		|SUBFILE	EQUAL expression > [type]
		)
		;
close_name: (IDENTIFIER|QUOTED_STRING)
	;


inquire_statement: {LABEL} INQUIRE^ LP inquire_item (COMMA inquire_item)* RP
		;
inquire_item: <<int type; int dummy;>>
 	({UNIT EQUAL} unit_identifier|FILE_WORD EQUAL expression > [type])
	|ERR EQUAL label
	|(IOSTAT EQUAL operand > [dummy])
	|NUMBER		EQUAL IDENTIFIER
	|RECL		EQUAL IDENTIFIER
	|NEXTREC	EQUAL IDENTIFIER
	|EXIST		EQUAL IDENTIFIER
	|OPENED		EQUAL IDENTIFIER
	|OPEN		EQUAL IDENTIFIER
	|NAMED 		EQUAL IDENTIFIER
	|NAME 		EQUAL inquire_name
	|RECORD		EQUAL inquire_name
	|ACCESS		EQUAL inquire_name
	|SEQUENTIAL	EQUAL inquire_name
	|DIRECT		EQUAL inquire_name
	|FORM		EQUAL inquire_name
	|FORMATTED	EQUAL inquire_name
	|UNFORMATTED EQUAL inquire_name
	|BLANK		EQUAL inquire_name
	|TITLE		EQUAL inquire_name
	|MAXRECSIZE		EQUAL 	IDENTIFIER
	|RESIDENT	EQUAL inquire_name
	;

inquire_name: (IDENTIFIER|QUOTED_STRING)
	;

backspace_statement: {LABEL} BACKSPACE^ io_specifier
		;

endfile_statement: {LABEL} ENDFILE^ io_specifier
		;

rewind_statement: {LABEL} REWIND^ io_specifier
		;

 /*This is the same for BACKSPACE, ENDFILE and REWIND. Save some code size.*/
io_specifier:<<int option1=0, option2=0; int type; int dummy;>>
	(LP)?(LP <<#1->token = IO_SPEC_LP;>>) {UNIT EQUAL} unit_identifier
	(<<option1==0>>? COMMA ERR^ EQUAL INT_CONST <<option1=1;>>
	|<<option2==0>>? COMMA IOSTAT^ EQUAL operand > [dummy]
	)*
	(RP <<#1->token = IO_SPEC_RP;>>)
	|unit_identifier
	;

change_statement: {LABEL} CHANGE^ LP
		change_item (COMMA change_item)* RP
		;
change_item:	(library_id COMMA library_clist)? library_id COMMA library_clist
		|change_file_specifier
		|file_clist
		|{UNIT EQUAL} unit_identifier
		;
file_clist: <<int type; int dummy;>>
		(IOSTAT EQUAL operand > [dummy])
		|ERR	EQUAL	statement_label
		|FILE_WORD EQUAL	expression > [type]
		|STATUS	EQUAL	expression > [type]
		|BLANK	EQUAL	expression > [type]
		;

library_id:	IDENTIFIER|CONSTINT;
library_clist: <<int type;>>
		TITLE	EQUAL	expression > [type]
		|LIBPARAMETER	EQUAL	expression > [type]
		|FUNCTIONNAME	EQUAL	expression > [type]
		;

change_file_specifier: <<int type;>>
		KIND			EQUAL	(QUATED_STRING|IDENTIFIER {LP IDENTIFIER RP})
		|MAXRECSIZE		EQUAL 	expression > [type]
		;

format_statement: LABEL FORMAT^ LP format_specification RP
	;
format_specification: (format_specifier)+
			;
format_specifier:({CONSTINT} LP)? {CONSTINT} LP format_specification RP
		|hollerith_editing
		|quote_editinig		|tr_editing
		|tl_editing			|t_editing
		|x_editing			|colon_editing
		|ss_editing			|s_editing
		|p_editing 			|bn_editing
		|bz_editing			|i_editing
		|j_editing 			|f_editing
		|e_editing			|d_editing
		|g_editing 			|o_editing
		|l_editing 			|a_editing
		|z_editing			|sp_editing
		|SLASH
		/*UNISYS FORTRAN V3.8*/
		|u_editing
		;

