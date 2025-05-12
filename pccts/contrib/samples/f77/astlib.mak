#=============================================================
#
#	astlib.MAK - Makefile for project sorcerer AST library
#	BORLAND C/C++ for OS/2 must be installed as well as PCCTS
#=============================================================

.AUTODEPEND

#=============================================================
#		Translator Definitions
#=============================================================
CC = bcc +F77.CFG
TASM = tasm.exe
TLIB = tlib.exe
TLINK = tlink
RC = brcc.exe
RB = rc.exe
SORCERER = d:\sorcerer
LIBPATH = D:\BCOS2\LIB
INCLUDEPATH = D:\BCOS2\INCLUDE

SOR_CFLAGS = -A -I$(SORCERER)\h -I$(SORCERER)\lib -D__USE_PROTOS


#=============================================================
#		Individual File Dependencies
#=============================================================
slist.obj: astlib.cfg $(SORCERER)\lib\slist.c
   $(CC) $(SOR_CFLAGS) -c $(SORCERER)\lib\slist.c

astlib.obj: astlib.cfg $(SORCERER)\lib\astlib.c
   $(CC) $(SOR_CFLAGS) -c $(SORCERER)\lib\astlib.c

sstack.obj: astlib.cfg $(SORCERER)\lib\sstack.c
   $(CC) $(SOR_CFLAGS) -c $(SORCERER)\lib\sstack.c

sint.obj: astlib.cfg $(SORCERER)\lib\sint.c
   $(CC) $(SOR_CFLAGS) -c $(SORCERER)\lib\sint.c

#=============================================================
#		Implicit Rules
#=============================================================
.c.obj:
   $(CC) $(SOR_CFLAGS) -c {$< }

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
 slist.obj \
 astlib.obj \
 sstack.obj \
 sint.obj

#=============================================================
#		Explicit Rules
#=============================================================
astlib.lib: astlib.cfg $(EXE_DEPENDENCIES)
  - del astlib.lib
  $(TLIB) $<  @&&|
+slist.obj &
+astlib.obj &
+sstack.obj &
+sint.obj
|

#=============================================================
#		Compiler Configuration File
#=============================================================
astlib.cfg: astlib.mak
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
| astlib.cfg

