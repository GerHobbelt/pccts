#include "Pa/tokens.h"
#include "Pa/ParserA.h"
#include "Pb/ParserB.h"

#include "AToken.h"

typedef ANTLRCommonToken ANTLRToken;

#include "Pa/DlgA.h"
#include "Pb/DlgB.h"

void invokeA();
void invokeB();

int main() {
	invokeA();
	invokeB();
	return 0;
}
