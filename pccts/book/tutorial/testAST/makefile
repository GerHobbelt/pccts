#
# PCCTS makefile for: poly.g
#
# Created from: genmk -CC -class PolyParser -project poly -trees poly.g
#
# PCCTS release 1.33
# Project: poly
# C++ output
# DLG scanner
# ANTLR-defined token types
#
TOKENS = tokens.h
#
# The following filenames must be consistent with ANTLR/DLG flags
DLG_FILE = parser.dlg
ERR = err
HDR_FILE =
SCAN = DLGLexer
PCCTS = /projects/pccts
ANTLR_H = $(PCCTS)/h
BIN = $(PCCTS)/bin
ANTLR = $(BIN)/antlr
DLG = $(BIN)/dlg
CFLAGS = -I. -I$(ANTLR_H)
AFLAGS = -CC -gt
DFLAGS = -C2 -i -CC
GRM = poly.g
SRC = poly.cpp \
      PolyParser.cpp \
      $(ANTLR_H)/AParser.cpp $(ANTLR_H)/DLexerBase.cpp \
      $(ANTLR_H)/ASTBase.cpp $(ANTLR_H)/PCCTSAST.cpp \
       $(ANTLR_H)/ATokenBuffer.cpp $(SCAN).cpp
OBJ = poly.o \
      PolyParser.o \
       AParser.o DLexerBase.o \
      ASTBase.o PCCTSAST.o \
       ATokenBuffer.o $(SCAN).o
ANTLR_SPAWN = poly.cpp PolyParser.cpp \
              PolyParser.h $(DLG_FILE) $(TOKENS)
DLG_SPAWN = $(SCAN).cpp $(SCAN).h
CCC=g++
CC=$(CCC)

poly : $(OBJ) $(SRC)
	$(CCC) -o poly $(CFLAGS) $(OBJ)

poly.o : $(TOKENS) $(SCAN).h poly.cpp
	$(CCC) -c $(CFLAGS) -o poly.o poly.cpp

PolyParser.o : $(TOKENS) $(SCAN).h PolyParser.cpp PolyParser.h
	$(CCC) -c $(CFLAGS) -o PolyParser.o PolyParser.cpp

$(SCAN).o : $(SCAN).cpp $(TOKENS)
	$(CCC) -c $(CFLAGS) -o $(SCAN).o $(SCAN).cpp

$(ANTLR_SPAWN) : $(GRM)
	$(ANTLR) $(AFLAGS) $(GRM)

$(DLG_SPAWN) : $(DLG_FILE)
	$(DLG) $(DFLAGS) $(DLG_FILE)

AParser.o : $(ANTLR_H)/AParser.cpp
	$(CCC) -c $(CFLAGS) -o AParser.o $(ANTLR_H)/AParser.cpp

ATokenBuffer.o : $(ANTLR_H)/ATokenBuffer.cpp
	$(CCC) -c $(CFLAGS) -o ATokenBuffer.o $(ANTLR_H)/ATokenBuffer.cpp

DLexerBase.o : $(ANTLR_H)/DLexerBase.cpp
	$(CCC) -c $(CFLAGS) -o DLexerBase.o $(ANTLR_H)/DLexerBase.cpp

ASTBase.o : $(ANTLR_H)/ASTBase.cpp
	$(CCC) -c $(CFLAGS) -o ASTBase.o $(ANTLR_H)/ASTBase.cpp

PCCTSAST.o : $(ANTLR_H)/PCCTSAST.cpp
	$(CCC) -c $(CFLAGS) -o PCCTSAST.o $(ANTLR_H)/PCCTSAST.cpp

List.o : $(ANTLR_H)/List.cpp
	$(CCC) -c $(CFLAGS) -o List.o $(ANTLR_H)/List.cpp

clean:
	rm -f *.o core poly

scrub:
	rm -f *.o core poly $(ANTLR_SPAWN) $(DLG_SPAWN)
