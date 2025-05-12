# Microsoft Developer Studio Generated NMAKE File, Based on DlgMSVC50.dsp
!IF "$(CFG)" == ""
CFG=DLG - Win32 Debug
!MESSAGE No configuration specified. Defaulting to DLG - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DLG - Win32 Release" && "$(CFG)" != "DLG - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DlgMSVC50.mak" CFG="DLG - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DLG - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "DLG - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "DLG - Win32 Release"

OUTDIR=.\.
INTDIR=.\.
# Begin Custom Macros
OutDir=.\.
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "tokens.h" "parser.dlg" "mode.h" "err.c" "dlg_p.c" "dlg_a.c"\
 "$(OUTDIR)\Dlg.exe"

!ELSE 

ALL : "tokens.h" "parser.dlg" "mode.h" "err.c" "dlg_p.c" "dlg_a.c"\
 "$(OUTDIR)\Dlg.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\automata.obj"
	-@erase "$(INTDIR)\dlg_a.obj"
	-@erase "$(INTDIR)\dlg_p.obj"
	-@erase "$(INTDIR)\err.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\output.obj"
	-@erase "$(INTDIR)\relabel.obj"
	-@erase "$(INTDIR)\set.obj"
	-@erase "$(INTDIR)\support.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Dlg.exe"
	-@erase "dlg_a.c"
	-@erase "dlg_p.c"
	-@erase "err.c"
	-@erase "mode.h"
	-@erase "parser.dlg"
	-@erase "tokens.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\h" /I "..\support\set" /D "NDEBUG" /D\
 "LONGFILENAMES" /D "PC" /D "USER_ZZSYN" /D ZZLEXBUFSIZE=65536 /D "_DEBUG" /D\
 "WIN32" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\DlgMSVC50.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=./
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DlgMSVC50.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)\Dlg.pdb" /machine:I386 /out:"$(OUTDIR)\Dlg.exe" 
LINK32_OBJS= \
	"$(INTDIR)\automata.obj" \
	"$(INTDIR)\dlg_a.obj" \
	"$(INTDIR)\dlg_p.obj" \
	"$(INTDIR)\err.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\output.obj" \
	"$(INTDIR)\relabel.obj" \
	"$(INTDIR)\set.obj" \
	"$(INTDIR)\support.obj"

"$(OUTDIR)\Dlg.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DLG - Win32 Debug"

OUTDIR=.\.
INTDIR=.\.
# Begin Custom Macros
OutDir=.\.
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "tokens.h" "parser.dlg" "mode.h" "err.c" "dlg_p.c" "dlg_a.c"\
 "$(OUTDIR)\Dlg.exe"

!ELSE 

ALL : "tokens.h" "parser.dlg" "mode.h" "err.c" "dlg_p.c" "dlg_a.c"\
 "$(OUTDIR)\Dlg.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\automata.obj"
	-@erase "$(INTDIR)\dlg_a.obj"
	-@erase "$(INTDIR)\dlg_p.obj"
	-@erase "$(INTDIR)\err.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\output.obj"
	-@erase "$(INTDIR)\relabel.obj"
	-@erase "$(INTDIR)\set.obj"
	-@erase "$(INTDIR)\support.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Dlg.exe"
	-@erase "$(OUTDIR)\Dlg.ilk"
	-@erase "$(OUTDIR)\Dlg.pdb"
	-@erase "dlg_a.c"
	-@erase "dlg_p.c"
	-@erase "err.c"
	-@erase "mode.h"
	-@erase "parser.dlg"
	-@erase "tokens.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\h" /I "..\support\set" /D\
 "__STDC__" /D "LONGFILENAMES" /D "PC" /D "USER_ZZSYN" /D ZZLEXBUFSIZE=65536 /D\
 "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\DlgMSVC50.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=./
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DlgMSVC50.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)\Dlg.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Dlg.exe"\
 /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\automata.obj" \
	"$(INTDIR)\dlg_a.obj" \
	"$(INTDIR)\dlg_p.obj" \
	"$(INTDIR)\err.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\output.obj" \
	"$(INTDIR)\relabel.obj" \
	"$(INTDIR)\set.obj" \
	"$(INTDIR)\support.obj"

"$(OUTDIR)\Dlg.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "DLG - Win32 Release" || "$(CFG)" == "DLG - Win32 Debug"
SOURCE=.\automata.c
DEP_CPP_AUTOM=\
	"..\h\config.h"\
	"..\support\set\set.h"\
	".\dlg.h"\
	

"$(INTDIR)\automata.obj" : $(SOURCE) $(DEP_CPP_AUTOM) "$(INTDIR)"


SOURCE=.\dlg_a.c
DEP_CPP_DLG_A=\
	"..\h\antlr.h"\
	"..\h\config.h"\
	"..\h\dlgauto.h"\
	"..\h\dlgdef.h"\
	"..\support\set\set.h"\
	".\dlg.h"\
	".\mode.h"\
	".\tokens.h"\
	

"$(INTDIR)\dlg_a.obj" : $(SOURCE) $(DEP_CPP_DLG_A) "$(INTDIR)"\
 "$(INTDIR)\mode.h" "$(INTDIR)\tokens.h"


SOURCE=.\dlg_p.c
DEP_CPP_DLG_P=\
	"..\h\antlr.h"\
	"..\h\config.h"\
	"..\h\dlgdef.h"\
	"..\support\set\set.h"\
	".\dlg.h"\
	".\mode.h"\
	".\tokens.h"\
	

"$(INTDIR)\dlg_p.obj" : $(SOURCE) $(DEP_CPP_DLG_P) "$(INTDIR)"\
 "$(INTDIR)\mode.h" "$(INTDIR)\tokens.h"


SOURCE=.\dlg_p.g

!IF  "$(CFG)" == "DLG - Win32 Release"

InputPath=.\dlg_p.g
InputName=dlg_p

"dlg_a.c"	"dlg_p.c"	"err.c"	"mode.h"	"parser.dlg"	"tokens.h"	 : $(SOURCE)\
 "$(INTDIR)" "$(OUTDIR)"
	..\bin\Win32\antlr $(InputName).g 
	..\bin\Win32\dlg -C2 parser.dlg dlg_a.c 
	

!ELSEIF  "$(CFG)" == "DLG - Win32 Debug"

InputPath=.\dlg_p.g
InputName=dlg_p

"dlg_a.c"	"dlg_p.c"	"err.c"	"mode.h"	"parser.dlg"	"tokens.h"	 : $(SOURCE)\
 "$(INTDIR)" "$(OUTDIR)"
	..\bin\Win32\antlr $(InputName).g 
	..\bin\Win32\dlg -C2 parser.dlg dlg_a.c 
	

!ENDIF 

SOURCE=.\err.c
DEP_CPP_ERR_C=\
	"..\h\antlr.h"\
	"..\h\config.h"\
	"..\h\dlgdef.h"\
	"..\h\err.h"\
	"..\support\set\set.h"\
	".\dlg.h"\
	".\tokens.h"\
	

"$(INTDIR)\err.obj" : $(SOURCE) $(DEP_CPP_ERR_C) "$(INTDIR)"\
 "$(INTDIR)\tokens.h"


SOURCE=.\main.c
DEP_CPP_MAIN_=\
	"..\h\antlr.h"\
	"..\h\config.h"\
	"..\h\dlgdef.h"\
	"..\support\set\set.h"\
	".\dlg.h"\
	".\mode.h"\
	".\stdpccts.h"\
	".\tokens.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"\
 "$(INTDIR)\mode.h" "$(INTDIR)\tokens.h"


SOURCE=.\output.c
DEP_CPP_OUTPU=\
	"..\h\config.h"\
	"..\support\set\set.h"\
	".\dlg.h"\
	

"$(INTDIR)\output.obj" : $(SOURCE) $(DEP_CPP_OUTPU) "$(INTDIR)"


SOURCE=.\relabel.c
DEP_CPP_RELAB=\
	"..\h\config.h"\
	"..\support\set\set.h"\
	".\dlg.h"\
	

"$(INTDIR)\relabel.obj" : $(SOURCE) $(DEP_CPP_RELAB) "$(INTDIR)"


SOURCE=..\support\set\set.c
DEP_CPP_SET_C=\
	"..\h\config.h"\
	"..\support\set\set.h"\
	

"$(INTDIR)\set.obj" : $(SOURCE) $(DEP_CPP_SET_C) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\support.c
DEP_CPP_SUPPO=\
	"..\h\config.h"\
	"..\support\set\set.h"\
	".\dlg.h"\
	

"$(INTDIR)\support.obj" : $(SOURCE) $(DEP_CPP_SUPPO) "$(INTDIR)"



!ENDIF 

