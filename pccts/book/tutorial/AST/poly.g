#header <<
// must be visible to all generated files; hence, must be in #header action
#include "AToken.h"
typedef ANTLRCommonToken ANTLRToken;
#include "MyEvalPoly.h"
>>

<<
#include "PBlackBox.h"
#include "DLGLexer.h"

main()
{
	ParserBlackBox<DLGLexer, PolyParser, ANTLRToken> p(stdin);
	ASTBase *root = NULL;
	p.parser()->interp(&root);
//	root->preorder();
//	printf("\n");
}
>>

#token "[\ \t]+"	<<skip();>>
#token "\n"			<<skip(); newline();>>
#token ID			"[a-z]"
#token FLOAT		"[0-9]+ { . [0-9]+ }"

#token EXP		"^"
#token ASSIGN	"="
#token ADD		"\+"
#token MULT

class PolyParser {

<<
protected:
	MyEvalPoly walker;
>>

interp!
	:	( a:assign
 )+
	;

assign
	:	ID "="^ poly ";"!
<<
	#0->preorder();
	printf("\n");
>>
 <<walker.assign((SORASTBase **)&#0);>>
	;

poly
	:	term ( "\+"^ term )*
	;

term:	bigterm
	|	reg { "^"^ exp }
	;

bigterm!
	:	c:coefficient
		(	r:reg
			(	"^" e:exp
				<<#0 = #(#[MULT,"MULT"], #c, #(#[EXP,"EXP"], #r, #e));>>
			|	<<#0 = #(#[MULT,"MULT"], #c, #r);>>
			)
		|		<<#0 = #c;>>
		)
	;

coefficient
	:	FLOAT
	;

reg	:	ID
	;

exp	:	reg
	|	FLOAT
	;

}
