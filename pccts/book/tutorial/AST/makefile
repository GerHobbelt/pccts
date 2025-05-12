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
SOR_H = $(PCCTS)/sorcerer/h
SOR_LIB = $(PCCTS)/sorcerer/lib
BIN = $(PCCTS)/bin
ANTLR = $(BIN)/antlr
DLG = $(BIN)/dlg
SOR = $(PCCTS)/sorcerer/sor
CFLAGS = -I. -I$(ANTLR_H) -g -I$(SOR_H)
AFLAGS = -CC -gt
DFLAGS = -C2 -i -CC
GRM = poly.g
SRC = poly.cpp \
      PolyParser.cpp \
      $(ANTLR_H)/AParser.cpp $(ANTLR_H)/DLexerBase.cpp \
      $(ANTLR_H)/ASTBase.cpp $(ANTLR_H)/PCCTSAST.cpp \
      $(ANTLR_H)/ATokenBuffer.cpp $(SCAN).cpp \
      eval.cpp EvalPoly.cpp \
      $(SOR_LIB)/STreeParser.cpp 
OBJ = poly.o \
      PolyParser.o \
       AParser.o DLexerBase.o \
      ASTBase.o PCCTSAST.o  \
       ATokenBuffer.o $(SCAN).o \
      eval.o EvalPoly.o \
      STreeParser.o
ANTLR_SPAWN = poly.cpp PolyParser.cpp \
	PolyParser.h $(DLG_FILE) $(TOKENS)
DLG_SPAWN = $(SCAN).cpp $(SCAN).h
SOR_SPAWN = EvalParser.cpp EvalParser.h eval.cpp
CCC=g++
CC=$(CCC)

poly : $(OBJ) $(SRC)
	$(CCC) -o poly $(CFLAGS) $(OBJ)

poly.o : $(TOKENS) $(SCAN).h poly.cpp EvalPoly.h
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

#
# SORCERER crud
#
EvalPoly.o : EvalPoly.cpp
	$(CCC) -c $(CFLAGS) EvalPoly.cpp

eval.o : eval.cpp
	$(CCC) -c $(CFLAGS) eval.cpp

eval.cpp EvalPoly.cpp EvalPoly.h : eval.sor
	$(SOR) -CPP eval.sor

STreeParser.o : $(SOR_LIB)/STreeParser.cpp
	$(CCC) -o STreeParser.o -c $(CFLAGS) $(SOR_LIB)/STreeParser.cpp

clean:
	rm -f *.o core poly

scrub:
	rm -f *.o core poly $(ANTLR_SPAWN) $(DLG_SPAWN) $(SOR_SPAWN)
