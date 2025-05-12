#include "Pb/tokens.h"
#include "Pb/ParserB.h"

#include "AToken.h"

typedef ANTLRCommonToken ANTLRToken;

#include "Pb/DlgB.h"

void invokeB() {
	
   DLGFileInput		in(stdin);
   DlgB				Blexer(&in,2000);

   ANTLRTokenBuffer Bpipe(&Blexer,1);

   ANTLRToken		aToken;
   ParserB			Bparser(&Bpipe);

   Blexer.setToken(&aToken);
   Bparser.init();

   Bparser.statement();
   return;
}
