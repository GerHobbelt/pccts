#ifndef AST_h
#define AST_h

#include "ASTBase.h"
#include "AToken.h"
#include "ATokPtr.h"

class AST : public ASTBase {
protected:
	ANTLRTokenPtr token;
	int iconst;
public:
	/* These ctor are called when you ref node constructor #[tok,s] */
	AST(ANTLRTokenType tok, char *s)
		{
			token = new ANTLRToken(tok, s);
			if ( token->getType() == INT ) iconst = atoi(token->getText());
		}
	AST(ANTLRTokenType tok, int i)
		{
			token = new ANTLRToken(tok, "");
			iconst = i;
		}
	AST(ANTLRTokenPtr t)
		{
			token = t;
			if ( token->getType() == INT )
			{
				iconst = atoi(token->getText());
			}
		}
	AST(const AST &t)	// shallow copy constructor
		{
			token = t.token;
			iconst = t.iconst;
			setDown(NULL);
			setRight(NULL);
		}
	void preorder_action() {
		char *s = token->getText();
		if ( token->getType()==INT ) printf(" %d", iconst);
		else printf(" %s", s);
	}
	virtual int type() { return token->getType(); }
	char *getText()	   { return token->getText(); }
	void setText(char *s) { token->setText(s); }
	virtual PCCTS_AST *shallowCopy()
	{
	    return new AST(*this);
/*	    *p = *this;
	    p->setDown(NULL);
	    p->setRight(NULL);
	    return p;
*/
	}
	int getIConst() { return iconst; }
	void setIConst(int i) { iconst = i; }
	void decIConst() { iconst--; }
};

#endif

