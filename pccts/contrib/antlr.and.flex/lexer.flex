%{

/*

Copyright (c) 1993 Ohio Board of Regents and the University of
Cincinnati.  All Rights Reserved.

UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES
SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
THIS SOFTWARE OR ITS DERIVATIVES.

By using or copying this Software, Licensee agrees to abide by the
intellectual property laws, and all other applicable laws of the U.S.,
and the terms of this license.

author: philip a. wilsey
phil.wilsey@uc.edu

*/

#include "lexer.h"
#include "TokenTypes.h"

#define YY_DECL ANTLRAbstractToken *lexer::getToken()

ANTLRToken *_Token;

int _LineNo;
int _LineOffset;
int _FileOffset;

%}

%%

[a-zA-Z]+	{
    _Token = new ANTLRToken(IDENTIFIER,yytext,_LineNo,_LineOffset,_FileOffset);
    _LineOffset = _LineOffset + yyleng;
    _FileOffset = _FileOffset + yyleng;
    return _Token;
}

[0-9]+	{
    _Token = new ANTLRToken(NUMBER,yytext,_LineNo,_LineOffset,_FileOffset);
    _LineOffset = _LineOffset + yyleng;
    _FileOffset = _FileOffset + yyleng;
    return _Token;
}

[\t ]*\n	{
    _LineNo = _LineNo + 1;
    _LineOffset = 0;
    _FileOffset = _FileOffset + yyleng;
}

[\t ]+	{
    _LineOffset = _LineOffset + yyleng;
    _FileOffset = _FileOffset + yyleng;
}

<<EOF>>	{
     return new ANTLRToken(ENDFILE,"",_LineNo,_LineOffset,_FileOffset);
}

%%

int yywrap() {return 1;}
