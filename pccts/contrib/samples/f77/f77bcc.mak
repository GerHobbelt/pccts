#=============================================================
#
#	F77.MAK - Makefile for project D:\FORTRAN\GRAMMARS\ABRAXAS\F77\F77.PRJ
#		Created on 02/22/95 at 10:40
#	BORLAND C/C++ for OS/2 must be installed as well as PCCTS
#	Change teh PCCTS macro to point to the pccts's root directory.
#=============================================================

.AUTODEPEND

#=============================================================
#		Translator Definitions
#=============================================================
PCCTS = d:\pccts131
CC = bcc +F77.CFG
TASM = tasm.exe
TLIB = tlib.exe
TLINK = tlink
RC = brcc.exe
RB = rc.exe
LIBPATH = D:\BCOS2\LIB
INCLUDEPATH = D:\BCOS2\INCLUDE;$(PCCTS)\H

#=============================================================
#		Implicit Rules
#=============================================================
.c.obj:
   $(CC) -DZZCOL -A -c {$< }

.cpp.obj:
  $(CC) -c {$< }

.asm.obj:
  $(TASM) -Mx $*.asm,$*.obj

.rc.res:
  $(RC) -r $*.rc

#=============================================================
#		List Macros
#=============================================================


EXE_DEPENDENCIES =  \
 myclass.obj \
 bintree.obj \
 f77print.obj \
 err.obj \
 scan.obj \
 f77.obj \
 expr.obj \
 io.obj \
 decl.obj \
 f77trans.obj \
 f77out.obj

#=============================================================
#		Explicit Rules
#=============================================================
f77.exe: f77.cfg $(EXE_DEPENDENCIES)
  $(TLINK) -S:60000 /v /Toe /ap /L$(LIBPATH) @&&|
D:\BCOS2\LIB\C02.OBJ+
myclass.obj+
bintree.obj+
f77print.obj+
err.obj+
scan.obj+
f77.obj+
expr.obj+
io.obj+
decl.obj+
f77trans.obj+
f77out.obj
f77,f77
astlib.lib+
D:\BCOS2\LIB\BIDS2.LIB+
D:\BCOS2\LIB\C2.LIB+
D:\BCOS2\LIB\OS2.LIB

|


#=============================================================
#		Individual File Dependencies
#=============================================================
MYCLASS.obj: f77.cfg MYCLASS.CPP

BINTREE.obj: f77.cfg BINTREE.CPP

err.obj: f77.cfg err.c

scan.obj: f77.cfg scan.c

f77.obj: f77.cfg f77.c

expr.obj: f77.cfg expr.c

io.obj: f77.cfg io.c

decl.obj: f77.cfg decl.c

#=============================================================
#		Compiler Configuration File
#=============================================================
f77.cfg: f77bcc.mak
  copy &&|
-R
-Ob
-Oc
-L$(LIBPATH)
-I$(INCLUDEPATH)
-vi-
-k-
-O
-y
-v
-w-aus
-w-rvl
-w-pro
-w-par
| f77.cfg

f77.c expr.c io.c decl.c scan.c err.c parser.dlg: f77.g
	$(PCCTS)\bin\antlr -gh -ga -gt -k 2 f77.g expr.g io.g decl.g
	$(PCCTS)\bin\dlg -C2 -i -ci parser.dlg scan.c

SORCERER = d:\sorcerer
SOR_CFLAGS = -A -I$(SORCERER)\h -I$(SORCERER)\lib -D__USE_PROTOS -DZZCOL

f77out.obj: f77.cfg f77out.c
	$(CC) $(SOR_CFLAGS) -c f77out.c

f77out.c : f77out.sor
	$(SORCERER)\sor.exe -funcs both -prefix o_ f77out.sor

f77trans.obj: f77.cfg f77trans.c
	$(CC) $(SOR_CFLAGS) -c f77trans.c

f77trans.c : f77trans.sor
	$(SORCERER)\sor.exe -funcs both -prefix x_ f77trans.sor
