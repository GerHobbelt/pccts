#
# PCCTS makefile for: SAMPLE SCRIPT PARSER WITH PCCTS EXCEPTIONS IN 'C'
# Uses PCCTS release 1.33MR20
#
# Also demonstrates the use of a 'C' HANDWRITTEN lexer which is linked to
# the parser instead of the (generated) DLG scanner.
#
PCCTS=../pccts

BIN = $(PCCTS)/bin
ANTLR = $(BIN)/antlr
DLG = $(BIN)/dlg
PCCTS_H = $(PCCTS)/h
SET = $(PCCTS)/support/set

#
# added -DDEBUG=1 so the TRACE() macro works and shows code flow through the parser.
#
CFLAGS = -O2 -I. -I$(PCCTS_H) -I$(SET) -g -DDEBUG=1
#CFLAGS = -Wall -pedantic -O2 -I. -I$(PCCTS_H) -I$(SET) -g
#
# -gd added so you can see the test parser 'work' through the rule tracing.
#
AFLAGS = -gh -k 2 -ga -e3  -gd
DFLAGS = -C2 -ga
GRM = script.g
# replace lexer.c/o by scan.c/o to use the DLG produced lexer.
SRC = script.c err.c main.c keywords.c debug.c support.c lexer.c
OBJ = script.o err.o main.o keywords.o debug.o support.o lexer.o
GENHFILES = tokens.h mode.h stdpccts.h
CC=cc
SHELL=/bin/sh

test: $(OBJ) $(SRC)
	$(CC) -o test $(CFLAGS) $(OBJ)

script.o : script.c mode.h tokens.h

script.c stdpccts.h parser.dlg tokens.h err.c : script.g
	$(ANTLR) $(AFLAGS) script.g

scan.c mode.h : parser.dlg
	$(DLG) $(DFLAGS) parser.dlg scan.c

clean:
	rm -f *.o core test script.c stdpccts.h parser.dlg tokens.h err.c mode.h scan.c


