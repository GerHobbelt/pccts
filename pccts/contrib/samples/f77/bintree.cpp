#if 0

// ---------------------------------------------------------------------------
// Copyright (C) 1994 Borland International
// bintree.cpp
//    Must link with myclass.cpp.
// ---------------------------------------------------------------------------

#include <classlib/binimp.h>
//#include <classlib/sets.h>
//#include <classlib/arrays.h>
//#include <classlib/hashimp.h>

#include <iostream.h>
#include <strstrea.h>
#include "myclass.h"

typedef TBinarySearchTreeImp<SymbolClass> ContainerType;
typedef TBinarySearchTreeIteratorImp<SymbolClass> IteratorType;

//typedef TISetAsVector<SymbolClass> ContainerType;
//typedef TISetAsVectorIterator<SymbolClass> IteratorType;

//typedef TArrayAsVector<SymbolClass> ContainerType;
//typedef TArrayAsVectorIterator<SymbolClass> IteratorType;

//typedef THashTableImp<SymbolClass> ContainerType;
//typedef THashTableIteratorImp<SymbolClass> IteratorType;


ContainerType container/*(1000)*/;

extern "C" void AddSymbol(char *Name, int Type)
{
    SymbolClass& symbol = SymbolClass(Name, Type);
    container.Add(symbol);
}

extern "C" int LookUp(char *Name)
{
    SymbolClass& symbol = SymbolClass(Name, 0), *result;
    result = container.Find(symbol);
    if(result != NULL)
	return(result->Type());
    else
	return(-1);
}

extern "C" void ChangeType(char *Name, int Type)
{
    SymbolClass& symbol = SymbolClass(Name, 0), *result;
    result = container.Find(symbol);
    if(result != NULL)
		result->SetType(Type);
    else
		AddSymbol(Name, Type);
}

#else

/* [i_a] quick hack to make it compile */
extern "C" void AddSymbol(char *Name, int Type)
{
}

extern "C" int LookUp(char *Name)
{
	return(-1);
}

extern "C" void ChangeType(char *Name, int Type)
{
}
#endif