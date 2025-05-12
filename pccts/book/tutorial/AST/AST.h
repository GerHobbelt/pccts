#ifndef AST_h
#define AST_h

#include "ASTBase.h"
#include "AToken.h"
#include "ATokPtr.h"

class AST : public ASTBase {
protected:
	ANTLRTokenPtr token;
public:
	/* This ctor is implicitly called when you ref node constructor #[tok,s] */
	AST(ANTLRTokenType tok, char *s) { token = new ANTLRToken(tok, s); }
	AST(ANTLRTokenPtr t) { token = t; }
	void preorder_action() {
		char *s = token->getText();
		printf(" %s", s);
	}
	virtual int type() { return token->getType(); }
	char *getText()	   { return token->getText(); }
};

#endif

