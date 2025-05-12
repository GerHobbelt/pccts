#ifndef MyEvalPoly_h
#define MyEvalPoly_h

#include "EvalPoly.h"

class MyEvalPoly : public EvalPoly {
protected:
	float regs['z'-'a'+1];
	virtual float value(char *r)			{ return regs[r[0]-'a']; }
	virtual void store(char *r, float v)	{ regs[r[0]-'a'] = v; }
public:
	MyEvalPoly()
		{
			for (int i='a'; i<='z'; i++) regs[i-'a'] = 0.0;
		}
};

#endif

