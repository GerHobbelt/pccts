#
# PCCTS makefile for: test.g
#
# Created from: ../../bin/genmk -CC -project t -class Expr test.g -user-lexer
#
# PCCTS release 1.21
# Project: t
# C++ output
# User-defined scanner
# ANTLR-defined token types
#
TOKENS = tokens.h
#
# The following filenames must be consistent with ANTLR/DLG flags
DLG_FILE = parser.dlg
ERR = err
HDR_FILE =
SCAN = DLGLexer
OBJEXT = o
PCCTS = /pccts
ANTLR_H = $(PCCTS)/h
BIN = /pccts/bin
ANTLR = $(BIN)/antlr
DLG = $(BIN)/dlg
CFLAGS = -I. -I$(ANTLR_H) -g
AFLAGS = -gx -CC -ft TokenTypes.h
DFLAGS = -C2 -i -CC
GRM = test.g
SRC = test.cpp \
      Parser.cpp \
      $(ANTLR_H)/AParser.cpp $(ANTLR_H)/ATokenBuffer.cpp 
OBJ = test.$(OBJEXT) \
      Parser.$(OBJEXT) \
      lexer.$(OBJEXT) \
       AParser.$(OBJEXT) ATokenBuffer.$(OBJEXT) 
ANTLR_SPAWN = test.cpp Parser.cpp Parser.h TokenTypes.h \
              test.h \
              $(HDR_FILE) $(TOKENS)
###CCC=g++
CCC=CC

t : $(OBJ) $(SRC) lexer.o
	$(CCC) -o t $(CFLAGS) $(OBJ)

test.$(OBJEXT) : $(TOKENS) test.cpp $(HDR_FILE)
	$(CCC) -c $(CFLAGS) -o test.$(OBJEXT) test.cpp

Parser.$(OBJEXT) : $(TOKENS) Parser.cpp Parser.h $(HDR_FILE)
	$(CCC) -c $(CFLAGS) -o Parser.$(OBJEXT) Parser.cpp

lexer.o:	lexer.cpp
	$(CCC) -c $(CFLAGS) -o lexer.o lexer.cpp

lexer.cpp: lexer.flex
	flex -i -olexer.cpp lexer.flex

$(ANTLR_SPAWN) : $(GRM) lexer.h
	$(ANTLR) $(AFLAGS) $(GRM)

AParser.$(OBJEXT) : $(ANTLR_H)/AParser.cpp
	$(CCC) -c $(CFLAGS) -o AParser.$(OBJEXT) $(ANTLR_H)/AParser.cpp

ATokenBuffer.$(OBJEXT) : $(ANTLR_H)/ATokenBuffer.cpp
	$(CCC) -c $(CFLAGS) -o ATokenBuffer.$(OBJEXT) $(ANTLR_H)/ATokenBuffer.cpp

clean:
	rm -f *.$(OBJEXT) core Parser.cpp lexer.cpp test.cpp TokenTypes.h Parser.h t *.bak

scrub: clean
	rm -f t $(ANTLR_SPAWN)
