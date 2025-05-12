# Microsoft Visual C++ generated build script - Do not modify

PROJ = SC_VC152
DEBUG = 1
PROGTYPE = 6
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\PRJ_VC\PROJECTS\SCRIPT~1\MAK\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = ERR.C       
FIRSTCPP =             
RC = rc
CFLAGS_D_DEXE = /f- /FPi87 /Gy /W4 /Gf /Zi /AL /Gx- /Od /OV0 /D "_DEBUG" /D "_DOS" /I "..\..\pccts\h" /I "..\..\pccts\support\set" /FR /Fd"SC_VC152.PDB"
CFLAGS_R_DEXE = /f- /Gs /FPi87 /Gy /W4 /Gf /AL /Gx- /Oe /Op /Ot /Ox /Ob1 /D "NDEBUG" /D "_DOS" /I "..\..\pccts\h" /I "..\..\pccts\support\set" /FR 
LFLAGS_D_DEXE = /NOI /PACKC:4096 /FARCALL /STACK:4096 /EXEPACK /SEG:256 /ONERROR:NOEXE /INFO /CO /MAP /LINE 
LFLAGS_R_DEXE = /NOI /PACKC:4096 /FARCALL /STACK:4096 /EXEPACK /SEG:256 /ONERROR:NOEXE /INFO /MAP /LINE 
LIBS_D_DEXE = oldnames llibc7 
LIBS_R_DEXE = oldnames llibc7 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_DEXE)
LFLAGS = $(LFLAGS_D_DEXE)
LIBS = $(LIBS_D_DEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_DEXE)
LFLAGS = $(LFLAGS_R_DEXE)
LIBS = $(LIBS_R_DEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = ERR.SBR \
		KEYWORDS.SBR \
		SCAN.SBR \
		SCRIPT.SBR


ERR_DEP = c:\prj_vc\projects\script~1\tokens.h


KEYWORDS_DEP = c:\prj_vc\projects\script~1\tokens.h


SCAN_DEP = c:\prj_vc\projects\script~1\tokens.h \
	c:\prj_vc\projects\script~1\mode.h


SCRIPT_DEP = c:\prj_vc\projects\script~1\tokens.h \
	c:\prj_vc\projects\script~1\mode.h


all:	$(PROJ).EXE $(PROJ).BSC

ERR.OBJ:	..\ERR.C $(ERR_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c ..\ERR.C

KEYWORDS.OBJ:	..\KEYWORDS.C $(KEYWORDS_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\KEYWORDS.C

SCAN.OBJ:	..\SCAN.C $(SCAN_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\SCAN.C

SCRIPT.OBJ:	..\SCRIPT.C $(SCRIPT_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\SCRIPT.C

$(PROJ).EXE::	ERR.OBJ KEYWORDS.OBJ SCAN.OBJ SCRIPT.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
ERR.OBJ +
KEYWORDS.OBJ +
SCAN.OBJ +
SCRIPT.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
