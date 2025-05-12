
#include "token.h"
#include "ATokenStream.h"

class lexer : public ANTLRTokenStream {

public:

  lexer() {};
  ~lexer() {};

  ANTLRAbstractToken *getToken();

};
