#ifndef SYMCLASS_H          // prevent header from
#define SYMCLASS_H 1        // being included twice

#include <cstring.h>
#include <iostream.h>
#include <checks.h>

class SymbolClass
{
  public:
    SymbolClass();
    SymbolClass(const string& s);
    SymbolClass(const string& s, const int& i);
    SymbolClass(const char *s);
    SymbolClass(const char *s, const int i);
    SymbolClass(const SymbolClass& mc);

    ~SymbolClass();

    SymbolClass& operator=(const SymbolClass& mc);
    int operator==(const SymbolClass& mc) const;
    int operator<(const SymbolClass& mc) const;
    unsigned HashValue() const;
    int Type() const;
	int SetType(int type);

    friend ostream& operator << (ostream&, const SymbolClass);

  private:

    string Str;
    int SymType;
};

#endif
