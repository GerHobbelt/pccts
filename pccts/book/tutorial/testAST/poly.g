<<
#include "PBlackBox.h"
#include "DLGLexer.h"
typedef ANTLRCommonToken ANTLRToken;

#include "AST.h"

main()
{
	ParserBlackBox<DLGLexer, PolyParser, ANTLRToken> p(stdin);
	ASTBase *root = NULL;
	p.parser()->interp(&root);
}
>>

#token "[\ \t]+"	<<skip();>>
#token "\n"			<<skip(); newline();>>
#token ID			"[a-z]"
#token FLOAT		"[0-9]+ { . [0-9]+ }"

#token EXP		"^"
#token MULT

class PolyParser {

interp!
	:	( a:assign )+
	;

assign
	:	ID "="^ poly ";"!	<<#0->preorder(); printf("\n");>>
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
