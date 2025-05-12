<<
#include "PBlackBox.h"
#include "DLGLexer.h"
typedef ANTLRCommonToken ANTLRToken;

#include "AST.h"
#include "DiffPoly.h"
#include "SimplifyPoly.h"
#include "PrintPoly.h"

main()
{
	ParserBlackBox<DLGLexer, PolyParser, ANTLRToken> p(stdin);
	ASTBase *root = NULL;
	p.parser()->poly(&root);
//	root->preorder();
//	printf("\n");
}
>>

#token "[\ \t]+"	<<skip();>>
#token "\n"			<<skip(); newline();>>

#token EXP		"^"
#token ADD		"\+"
#token MULT

class PolyParser {

poly
	:	<<
		DiffPoly dp;
		AST *result=NULL, *nresult=NULL;
		PrintPoly pp;
		SimplifyPoly sp;
		>>
		term ( "\+"^ term )*
		<<
		#0->preorder();
		printf("\n");
		dp.poly((SORASTBase **)&(#0), (SORASTBase **)&result);
		result->preorder();
		printf("\n");
		sp.poly((SORASTBase **)&result, (SORASTBase **)&nresult);
		nresult->preorder();
		printf("\n");
		pp.poly((SORASTBase **)&nresult);
		printf("\n");
		>>
	;

term:	bigterm
	|	reg { "^"^ INT }
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
	:	INT
	;

reg	:	ID
	;

exp	:	INT
	;

}

#token ID		"[a-z]"
#token INT		"[0-9]+"
