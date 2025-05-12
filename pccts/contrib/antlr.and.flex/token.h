
#ifndef Token_HH
#define Token_HH

// Copyright (c) 1995 Ohio Board of Regents and the University of
// Cincinnati.  All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE
// FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
// RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS
// DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.

// author: philip a. wilsey
// phil.wilsey@uc.edu

#include "TokenTypes.h"
#include "AToken.h"
#include <fstream.h>

// class ANTLRToken : public ANTLRAbstractToken {

// derive from ANTLRRefCountToken so that tokens are automatically deleted
// when no remaining pointers to them exist.

class ANTLRToken : public ANTLRRefCountToken {

protected:

  ANTLRTokenType _type;
  char* _text;
  int _textLength;
  int _line;
  int _lineOffset; // offset from beginning of line
  int _fileOffset;   // offset from beginning of file
  
public:
  
  ANTLRToken() {

    _type = NONE;
    _text = NULL;
    _textLength = 0; 
    _line = -1;
    _lineOffset = -1;
    _fileOffset = -1;

  };

  ANTLRToken(ANTLRTokenType tt,
         char* text,
         int lineNo,
         int lineOffset,
         int fileOffset) { 
    
    _type = tt;
    _text = strdup(text);
    _textLength = strlen(text);
    _line = lineNo;
    _lineOffset = lineOffset;
    _fileOffset = fileOffset;

  };

  ~ANTLRToken() {if (_text!=NULL) delete _text;}

  ANTLRTokenType getType() const    {return _type;}
  ANTLRChar *getText() const        {return _text;}
  int getLine() const               {return _line;}
  int getLineOffset() const         {return _lineOffset;}
  int getFileOffset() const         {return _fileOffset;}

  void setType(ANTLRTokenType t) {
    cerr << "setType(): Token fields set on construction." << endl;
  }
  void setText(ANTLRChar *s) {
    cerr << "setText(): Token fields set on construction." << endl;
  }
  void setLine(int line) {
    cerr << "setLin(): Token fields set on construction." << endl;
  }
  virtual ANTLRAbstractToken *makeToken(ANTLRTokenType tt, ANTLRChar *txt,
                    int line) {
    cerr << "makeToken(): Tokens are now made by flex routines." << endl;
    return NULL;
  }

};

#endif
