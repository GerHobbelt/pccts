#
# PCCTS makefile for: cstr.g
#
# Created from: genmk -project cstr cstr.g
#
# PCCTS release 1.30
# Project: cstr
# C output
# DLG scanner
# ANTLR-defined token types
#
TOPDIR = /usr/local

TOKENS = tokens.h
#
# The following filenames must be consistent with ANTLR/DLG flags
DLG_FILE = parser.dlg
ERR = err
HDR_FILE =
MOD_FILE = mode.h
SCAN = scan
PCCTS = $(TOPDIR)/src/pccts
ANTLR_H = $(PCCTS)/h
BIN = $(TOPDIR)/bin
ANTLR = $(BIN)/antlr
DLG = $(BIN)/dlg
CFLAGS = -I. -I$(ANTLR_H)
AFLAGS = -e2 -ga
DFLAGS = -C2 -i
GRM = cstr.g
SRC = cstr.c $(SCAN).c $(ERR).c
OBJ = cstr.o $(SCAN).o $(ERR).o
ANTLR_SPAWN = cstr.c $(DLG_FILE) $(TOKENS) $(ERR).c
DLG_SPAWN = $(SCAN).c $(MOD_FILE)
CC=gcc

cstr : $(OBJ) $(SRC)
	$(CC) -o cstr $(CFLAGS) $(OBJ)

cstr.o : $(MOD_FILE) $(TOKENS) cstr.c
	$(CC) -c $(CFLAGS) -o cstr.o cstr.c

$(ERR).o : $(ERR).c $(TOKENS)
	$(CC) -c $(CFLAGS) -o $(ERR).o $(ERR).c

$(SCAN).o : $(SCAN).c $(TOKENS)
	$(CC) -c $(CFLAGS) -o $(SCAN).o $(SCAN).c

$(ANTLR_SPAWN) : $(GRM)
	$(ANTLR) $(AFLAGS) $(GRM)

$(DLG_SPAWN) : $(DLG_FILE)
	$(DLG) $(DFLAGS) $(DLG_FILE) $(SCAN).c

clean:
	rm -f *.o core cstr

scrub:
	rm -f *.o core cstr $(ANTLR_SPAWN) $(DLG_SPAWN)


TK_H = -I/usr/local/include -I/usr/local/X11
TK_MAIN = /usr/local/src/tcl-dp/tkMain.o
TK_OBJS = $(TK_MAIN) tkAppInit.o
TK_LIBS = -L/usr/local/lib -L. -lBLT -litcl -ldpnetwork -ltk -ltcl -L/usr/X11/lib -lX11 -lm
TK_CFLAGS = -DTCL_PARSER -DHAVE_UNISTD_H=1 $(CFLAGS)

tkAppInit.o: tkAppInit.c
	$(CC) -c $(TK_H) -O tkAppInit.c

parserd: $(OBJ) tkAppInit.o $(SRC)
	$(CC) -c $(TK_CFLAGS) -o cstr.o cstr.c
	$(CC) -o pwish $(TK_H) $(TK_CFLAGS) $(TK_OBJS) $(OBJ) $(TK_LIBS)

