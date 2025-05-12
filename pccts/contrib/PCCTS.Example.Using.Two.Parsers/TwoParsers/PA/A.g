//
//  Parser A
//
//  Two parsers in a single executable
//
//    Use every default
//
//       No AST options
//       Default token
//       No column counting
//
//   pccts 1.33mr17


/*  This file should be accompanied by DISCLAIMER.TXT stating disclaimers */

<<
#include "AToken.h"
#include "DlgA.h"

typedef ANTLRCommonToken ANTLRToken;
>>


#token	Eof	"@"

#token  Number		"[0-9]+"
#token  Word		"[a-z A-Z]+"
#token  Whitespace  "[\t \ \f]"		<<skip(); >>
#token  Other	    "~[\ \t \n \r \f]+"
#token  Newline		"\n|\r|\n\r"	<<newline(); skip(); >>

class ParserA {

statement : 
		  (	n:Number	<<fprintf(stdout,"Number: %s\n",$n->getText()); >>
		  | w:Word		<<fprintf(stdout,"Word: %s\n",$w->getText()); >>
		  | o:Other     <<fprintf(stdout,"Other: %s\n",$o->getText()); >>
		  )*
		  Eof
		  ;
}
