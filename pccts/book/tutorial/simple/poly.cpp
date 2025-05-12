/*
 * A n t l r  T r a n s l a t i o n  H e a d e r
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-1994
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33
 */
#include <stdio.h>
#define ANTLR_VERSION	133
#include "tokens.h"
#include "AParser.h"
#include "PolyParser.h"
#include "DLexerBase.h"
#include "ATokPtr.h"
#ifndef PURIFY
#define PURIFY(r,s)
#endif

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

void
PolyParser::interp(void)
{
	zzRULE;
	ANTLRTokenPtr lhs=NULL;
	float r;  
	{
		int zzcnt=1;
		do {
			zzmatch(ID);
			
			lhs = (ANTLRTokenPtr)LT(1);
 consume();
			zzmatch(6);
			 consume();
			 r  = poly();

			zzmatch(7);
			
			store(lhs->getText(), r);  
 consume();
		} while ( (LA(1)==ID) );
	}
	return;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x1);
}

 float  
PolyParser::poly(void)
{
	 float  	 _retv;
	PURIFY(_retv,sizeof( float  	))
	zzRULE;
	float f;  
	 _retv  = term();

	{
		while ( (LA(1)==8) ) {
			zzmatch(8);
			 consume();
			 f  = term();

			_retv += f;  
		}
	}
	return _retv;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x2);
	return _retv;
}

 float  
PolyParser::term(void)
{
	 float  	 _retv;
	PURIFY(_retv,sizeof( float  	))
	zzRULE;
	float f=0.0, e=0.0, c=0.0, v=0.0;  
	if ( (LA(1)==FLOAT) ) {
		 c  = coefficient();

		{
			if ( (LA(1)==ID) ) {
				 v  = reg();

				{
					if ( (LA(1)==9) ) {
						zzmatch(9);
						 consume();
						 e  = exp();

						_retv = c*pow(v,e);  
					}
					else {
						if ( (setwd1[LA(1)]&0x4) ) {
							_retv = c*v;  
						}
						else {FAIL(1,err1,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
					}
				}
			}
			else {
				if ( (setwd1[LA(1)]&0x8) ) {
					_retv = c;  
				}
				else {FAIL(1,err2,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
			}
		}
	}
	else {
		if ( (LA(1)==ID) ) {
			 f  = reg();

			{
				if ( (LA(1)==9) ) {
					zzmatch(9);
					 consume();
					 e  = exp();

					_retv = pow(f,e);  
				}
				else {
					if ( (setwd1[LA(1)]&0x10) ) {
						_retv = f;  
					}
					else {FAIL(1,err3,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
				}
			}
		}
		else {FAIL(1,err4,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	return _retv;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x20);
	return _retv;
}

 float  
PolyParser::coefficient(void)
{
	 float  	 _retv;
	PURIFY(_retv,sizeof( float  	))
	zzRULE;
	ANTLRTokenPtr flt=NULL;
	zzmatch(FLOAT);
	
	flt = (ANTLRTokenPtr)LT(1);

	_retv = atof( flt->getText());  
 consume();
	return _retv;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x40);
	return _retv;
}

 float  
PolyParser::reg(void)
{
	 float  	 _retv;
	PURIFY(_retv,sizeof( float  	))
	zzRULE;
	ANTLRTokenPtr id=NULL;
	zzmatch(ID);
	
	id = (ANTLRTokenPtr)LT(1);

	_retv = value( id->getText());  
 consume();
	return _retv;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd1, 0x80);
	return _retv;
}

 float  
PolyParser::exp(void)
{
	 float  	 _retv;
	PURIFY(_retv,sizeof( float  	))
	zzRULE;
	ANTLRTokenPtr flt=NULL;
	if ( (LA(1)==ID) ) {
		 _retv  = reg();

	}
	else {
		if ( (LA(1)==FLOAT) ) {
			zzmatch(FLOAT);
			
			flt = (ANTLRTokenPtr)LT(1);

			_retv = atof( flt->getText());  
 consume();
		}
		else {FAIL(1,err5,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
	}
	return _retv;
fail:
	syn(zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk);
	resynch(setwd2, 0x1);
	return _retv;
}
