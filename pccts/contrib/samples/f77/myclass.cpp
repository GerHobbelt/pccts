#if 0

// ---------------------------------------------------------------------------
// Copyright (C) 1994 Borland International
//  myclass.cpp
// ---------------------------------------------------------------------------

#include "myclass.h"

SymbolClass::SymbolClass(){}
SymbolClass::SymbolClass(const string& s) : Str(s) {}
SymbolClass::SymbolClass(const string& s, const int& i) : Str(s), SymType(i){}

SymbolClass::SymbolClass(const char *s) : Str(s) {}
SymbolClass::SymbolClass(const char *s, const int i) : Str(s), SymType(i){}

SymbolClass::SymbolClass(const SymbolClass& mc) : Str(mc.Str), SymType(mc.SymType){}
SymbolClass::~SymbolClass(){}

SymbolClass& SymbolClass::operator=(const SymbolClass& mc)
{
    Str = mc.Str;
    SymType = mc.SymType;
    return *this;
}

int SymbolClass::operator==(const SymbolClass& mc) const
{
    return Str == mc.Str;
}

int SymbolClass::operator<(const SymbolClass& mc) const
{
    return Str < mc.Str;
}

unsigned SymbolClass::HashValue() const
{
    return Str.hash();
}

int SymbolClass::Type() const
{
    return this->SymType;
}

int SymbolClass::SetType(int type)
{
	this->SymType = type;
    return this->SymType;
}

ostream& operator<<(ostream& os, const SymbolClass mc)
{
    return os << "'" << mc.Str << "' hash = " << mc.HashValue();
}

#else

/* [i_a] quick hack to make it compile */

#endif