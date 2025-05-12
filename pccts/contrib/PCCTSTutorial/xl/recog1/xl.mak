# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=xl - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to xl - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "xl - Win32 Release" && "$(CFG)" != "xl - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "xl.mak" CFG="xl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xl - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "xl - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "xl - Win32 Debug"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "xl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\xl.exe"

CLEAN : 
	-@erase "$(INTDIR)\AParser.obj"
	-@erase "$(INTDIR)\ATokenBuffer.obj"
	-@erase "$(INTDIR)\DLexerBase.obj"
	-@erase "$(INTDIR)\DLGLexer.obj"
	-@erase "$(INTDIR)\xl.obj"
	-@erase "$(INTDIR)\XLParser.obj"
	-@erase ".\DLGLexer.cpp"
	-@erase ".\DLGLexer.h"
	-@erase ".\tokens.h"
	-@erase ".\xl.cpp"
	-@erase ".\xl.exe"
	-@erase ".\XLParser.cpp"
	-@erase ".\XLParser.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I "c:\pccts\h" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "c:\pccts\h" /D "WIN32" /D "NDEBUG" /D\
 "_CONSOLE" /Fp"$(INTDIR)/xl.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/xl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"xl.exe"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)/xl.pdb"\
 /machine:I386 /out:"xl.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AParser.obj" \
	"$(INTDIR)\ATokenBuffer.obj" \
	"$(INTDIR)\DLexerBase.obj" \
	"$(INTDIR)\DLGLexer.obj" \
	"$(INTDIR)\xl.obj" \
	"$(INTDIR)\XLParser.obj"

".\xl.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "xl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\xl.exe"

CLEAN : 
	-@erase "$(INTDIR)\AParser.obj"
	-@erase "$(INTDIR)\ATokenBuffer.obj"
	-@erase "$(INTDIR)\DLexerBase.obj"
	-@erase "$(INTDIR)\DLGLexer.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\xl.obj"
	-@erase "$(INTDIR)\XLParser.obj"
	-@erase "$(OUTDIR)\xl.pdb"
	-@erase ".\DLGLexer.cpp"
	-@erase ".\DLGLexer.h"
	-@erase ".\tokens.h"
	-@erase ".\xl.cpp"
	-@erase ".\xl.exe"
	-@erase ".\xl.ilk"
	-@erase ".\XLParser.cpp"
	-@erase ".\XLParser.h"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "c:\pccts\h" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "c:\pccts\h" /D "WIN32" /D\
 "_DEBUG" /D "_CONSOLE" /Fp"$(INTDIR)/xl.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/xl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"xl.exe"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/xl.pdb" /debug /machine:I386 /out:"xl.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AParser.obj" \
	"$(INTDIR)\ATokenBuffer.obj" \
	"$(INTDIR)\DLexerBase.obj" \
	"$(INTDIR)\DLGLexer.obj" \
	"$(INTDIR)\xl.obj" \
	"$(INTDIR)\XLParser.obj"

".\xl.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "xl - Win32 Release"
# Name "xl - Win32 Debug"

!IF  "$(CFG)" == "xl - Win32 Release"

!ELSEIF  "$(CFG)" == "xl - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\xl.g

!IF  "$(CFG)" == "xl - Win32 Release"

# Begin Custom Build - PCCTS Stuff
InputPath=.\xl.g

BuildCmds= \
	c:\bin\antlr.exe  -CC  -gl xl.g \
	c:\bin\dlg.exe -CC parser.dlg \
	

"XLParser.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"XLParser.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DLGLexer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DLGLexer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"tokens.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"xl.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "xl - Win32 Debug"

# Begin Custom Build - PCCTS Stuff
InputPath=.\xl.g

BuildCmds= \
	c:\bin\antlr.exe  -CC  -gl xl.g \
	c:\bin\dlg.exe -CC parser.dlg \
	

"XLParser.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"XLParser.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DLGLexer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DLGLexer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"tokens.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"xl.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\XLParser.cpp
DEP_CPP_XLPAR=\
	"..\..\..\..\pccts\h\config.h"\
	".\tokens.h"\
	".\XLParser.h"\
	"\pccts\h\AParser.h"\
	

"$(INTDIR)\XLParser.obj" : $(SOURCE) $(DEP_CPP_XLPAR) "$(INTDIR)"\
 ".\XLParser.h" ".\tokens.h"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\xl.cpp
DEP_CPP_XL_CP=\
	"..\..\..\..\pccts\h\config.h"\
	".\DLGLexer.h"\
	".\tokens.h"\
	".\XLParser.h"\
	"\pccts\h\AParser.h"\
	"\pccts\h\AToken.h"\
	"\pccts\h\ATokPtr.h"\
	"\pccts\h\DLexerBase.h"\
	

"$(INTDIR)\xl.obj" : $(SOURCE) $(DEP_CPP_XL_CP) "$(INTDIR)" ".\XLParser.h"\
 ".\DLGLexer.h" ".\tokens.h"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DLGLexer.cpp
DEP_CPP_DLGLE=\
	"..\..\..\..\pccts\h\config.h"\
	".\DLGLexer.h"\
	".\tokens.h"\
	"\pccts\h\AParser.h"\
	"\pccts\h\AToken.h"\
	"\pccts\h\DLexer.cpp"\
	"\pccts\h\DLexerBase.h"\
	

"$(INTDIR)\DLGLexer.obj" : $(SOURCE) $(DEP_CPP_DLGLE) "$(INTDIR)"\
 ".\DLGLexer.h" ".\tokens.h"


# End Source File
################################################################################
# Begin Source File

SOURCE=\pccts\h\DLexerBase.cpp
DEP_CPP_DLEXE=\
	"..\..\..\..\pccts\h\config.h"\
	

"$(INTDIR)\DLexerBase.obj" : $(SOURCE) $(DEP_CPP_DLEXE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\pccts\h\ATokenBuffer.cpp
DEP_CPP_ATOKE=\
	"..\..\..\..\pccts\h\config.h"\
	

"$(INTDIR)\ATokenBuffer.obj" : $(SOURCE) $(DEP_CPP_ATOKE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\pccts\h\AParser.cpp
DEP_CPP_APARS=\
	"..\..\..\..\pccts\h\config.h"\
	

"$(INTDIR)\AParser.obj" : $(SOURCE) $(DEP_CPP_APARS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
