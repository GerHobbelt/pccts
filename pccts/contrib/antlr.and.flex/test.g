
<<
#include <fstream.h>
#include "lexer.h"
>>

<<
int main()
{
	lexer scan;
	ANTLRTokenBuffer pipe(&scan);
	/* create a parser of type Expr hooked to my scanner */
	Parser parser(&pipe);
	parser.init();
	parser.setEofToken(ENDFILE);

	parser.e();
	return 0;
}
>>

#token IDENTIFIER
#token NUMBER
#token ENDFILE		// end of file token
#token NONE		// indicates no token known

class Parser {				/* Define a grammar class */

e :
	ID:IDENTIFIER 
	<<cout << mytoken(ID)->getText() 
	       << " line " << mytoken(ID)->getLine()
	       << " file offset " << mytoken(ID)->getFileOffset()
	       << " line offset " << mytoken(ID)->getLineOffset()
	       << endl;>> e
| 
	NU:NUMBER
	<<cout << mytoken(NU)->getText() 
	       << " line " << mytoken(NU)->getLine()
	       << " file offset " << mytoken(NU)->getFileOffset()
	       << " line offset " << mytoken(NU)->getLineOffset()
	       << endl;>> e
| 
	ENDFILE
	;

}
