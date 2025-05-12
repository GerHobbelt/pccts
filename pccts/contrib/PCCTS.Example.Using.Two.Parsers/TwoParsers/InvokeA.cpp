#include "Pa/tokens.h"
#include "Pa/ParserA.h"

#include "AToken.h"

typedef ANTLRCommonToken ANTLRToken;

#include "Pa/DlgA.h"

void invokeA() {
	
   DLGFileInput		in(stdin);
   DlgA				Alexer(&in,2000);

   ANTLRTokenBuffer Apipe(&Alexer,1);

   ANTLRToken		aToken;
   ParserA			Aparser(&Apipe);

   Alexer.setToken(&aToken);
   Aparser.init();

   Aparser.statement();
   return;
}
