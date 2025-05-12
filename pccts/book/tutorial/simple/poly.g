<<
#include <math.h>

class InterpretingPolyParser : public PolyParser {
protected:
	float regs['z'-'a'+1];
	virtual void store(char *reg, float v)
		{
			regs[reg[0]-'a'] = v;
			printf("storing %f in %s\n", v, reg);
		}
	virtual float value(char *reg)
		{ return regs[reg[0]-'a']; }
public:
	InterpretingPolyParser(ANTLRTokenBuffer *input) : PolyParser(input)
		{
			for (int i='a'; i<='z'; i++) regs[i-'a'] = 0.0;
		}
};

#include "PBlackBox.h"
#include "DLGLexer.h"
typedef ANTLRCommonToken ANTLRToken;

main()
{
	ParserBlackBox<DLGLexer, InterpretingPolyParser, ANTLRToken> p(stdin);
	p.parser()->interp();
}
>>

#token "[\ \t]+"	<<skip();>>
#token "\n"			<<skip(); newline();>>
#token ID			"[a-z]"
#token FLOAT		"[0-9]+ { . [0-9]+ }"

class PolyParser {
<<
protected:
	virtual void store(char *reg, float v) {;}
	virtual float value(char *reg) {;}
>>

interp
	:	<<float r;>>
		(	lhs:ID "=" poly>[r] ";" <<store(lhs->getText(), r);>>
		)+
	;

poly > [float r]
	:	<<float f;>>
		term>[$r] ( "\+" term>[f] <<$r += f;>> )*
	;

term > [float r]
	:	<<float f=0.0, e=0.0, c=0.0, v=0.0;>>
		coefficient > [c]
		(	reg > [v]
			(	"^" exp>[e]		<<$r = c*pow(v,e);>>
			|					<<$r = c*v;>>
			)
		|						<<$r = c;>>
		)
	|	reg > [f]
		(	"^" exp > [e]		<<$r = pow(f,e);>>
		|						<<$r = f;>>
		)
	;

coefficient > [float r]
	:	flt:FLOAT		<<$r = atof($flt->getText());>>
	;

reg > [float r]
	:	id:ID			<<$r = value($id->getText());>>
	;

exp > [float r]
	:	reg > [$r]
	|	flt:FLOAT		<<$r = atof($flt->getText());>>
	;

}
