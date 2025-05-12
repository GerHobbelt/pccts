# Microsoft Developer Studio Project File - Name="ANTLR" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=ANTLR - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AntlrMSVC50.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AntlrMSVC50.mak" CFG="ANTLR - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ANTLR - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ANTLR - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/PRJ_VC/Projects/pccts/antlr", XCGBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ANTLR - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /W4 /GX /O2 /I "." /I "..\h" /I "..\support\set" /D "NDEBUG" /D "USER_ZZSYN" /D ZZLEXBUFSIZE=65536 /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FR /FD /TP /c
# SUBTRACT CPP /nologo /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib uuid.lib /nologo /subsystem:console /machine:I386 /out:"./Release/Antlr.exe"
# SUBTRACT LINK32 /map
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Copy antlr to ..\bin directory
PostBuild_Cmds=mkdir   ..\bin  	copy   ..\bin\antlr.exe   antlr_old.exe  	copy   Release\antlr.exe   ..\bin\ 
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ANTLR - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /W4 /GX /ZI /Od /I "." /I "..\h" /I "..\support\set" /D "_DEBUG" /D "USER_ZZSYN" /D ZZLEXBUFSIZE=65536 /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FR /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib /nologo /subsystem:console /profile /map /debug /machine:I386 /out:"./Debug/Antlr.exe"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Copy antlr to ..\bin
PostBuild_Cmds=mkdir   ..\bin  	copy   ..\bin\antlr.exe   antlr_old.exe  	copy   Debug\antlr.exe   ..\bin\ 
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "ANTLR - Win32 Release"
# Name "ANTLR - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Group "unused"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\dumpcycles.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\dumpnode.c
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Source File

SOURCE=.\antlr.c
# End Source File
# Begin Source File

SOURCE=.\antlr.g

!IF  "$(CFG)" == "ANTLR - Win32 Release"

# Begin Custom Build - Building ANTLR Parser from ANTLR Grammar
InputPath=.\antlr.g
InputName=antlr

BuildCmds= \
	..\bin\antlr -e3 -w2 -ga -cr $(InputName).g \
	..\bin\dlg -C2 parser.dlg scan.c \
	..\bin\antlr -gc -pa -e3 -cr -ga -tab 2  -w2 -info ptfmo $(InputName).g  > $(InputName).full.dsc \
	..\bin\antlr -gc -p -e3 -ga -tab 2 -w2 $(InputName).g > $(InputName).dsc \
	

"antlr.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"err.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"mode.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"scan.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"tokens.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"parser.dlg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ANTLR - Win32 Debug"

# Begin Custom Build - Building ANTLR Parser from ANTLR Grammar
InputPath=.\antlr.g
InputName=antlr

BuildCmds= \
	..\bin\antlr -e3 -w2 -ga -cr $(InputName).g \
	..\bin\dlg -C2 parser.dlg scan.c \
	..\bin\antlr -gc -pa -e3 -cr -ga -tab 2  -w2 -info ptfmo $(InputName).g  > $(InputName).full.dsc \
	..\bin\antlr -gc -p -e3 -ga -tab 2 -w2 $(InputName).g > $(InputName).dsc \
	

"antlr.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"err.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"mode.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"scan.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"tokens.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"parser.dlg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\bits.c
# End Source File
# Begin Source File

SOURCE=.\build.c
# End Source File
# Begin Source File

SOURCE=.\egman.c
# End Source File
# Begin Source File

SOURCE=.\err.c
# End Source File
# Begin Source File

SOURCE=.\fcache.c
# End Source File
# Begin Source File

SOURCE=.\fset.c
# End Source File
# Begin Source File

SOURCE=.\fset2.c
# End Source File
# Begin Source File

SOURCE=.\gen.c
# End Source File
# Begin Source File

SOURCE=.\globals.c
# End Source File
# Begin Source File

SOURCE=.\hash.c
# End Source File
# Begin Source File

SOURCE=.\lex.c
# End Source File
# Begin Source File

SOURCE=.\main.c
# End Source File
# Begin Source File

SOURCE=.\misc.c
# End Source File
# Begin Source File

SOURCE=.\mrhoist.c
# End Source File
# Begin Source File

SOURCE=.\parser.dlg
# End Source File
# Begin Source File

SOURCE=.\pred.c
# End Source File
# Begin Source File

SOURCE=.\scan.c
# End Source File
# Begin Source File

SOURCE=..\support\set\set.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\h\antlr.h
# End Source File
# Begin Source File

SOURCE=..\h\dlgauto.h
# End Source File
# Begin Source File

SOURCE=..\h\dlgdef.h
# End Source File
# Begin Source File

SOURCE=..\h\err.h
# End Source File
# Begin Source File

SOURCE=.\generic.h
# End Source File
# Begin Source File

SOURCE=.\hash.h
# End Source File
# Begin Source File

SOURCE=.\mode.h
# End Source File
# Begin Source File

SOURCE=..\h\pccts_stdarg.h
# End Source File
# Begin Source File

SOURCE=..\h\pccts_stdio.h
# End Source File
# Begin Source File

SOURCE=..\h\pccts_stdlib.h
# End Source File
# Begin Source File

SOURCE=..\h\pccts_string.h
# End Source File
# Begin Source File

SOURCE=..\h\pcctscfg.h
# End Source File
# Begin Source File

SOURCE=.\proto.h
# End Source File
# Begin Source File

SOURCE=..\support\set\set.h
# End Source File
# Begin Source File

SOURCE=.\stdpccts.h
# End Source File
# Begin Source File

SOURCE=.\syn.h
# End Source File
# Begin Source File

SOURCE=.\tokens.h
# End Source File
# End Group
# Begin Group "Documentation"

# PROP Default_Filter ""
# Begin Group "comp.compilers.tools.pccts"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\contrib\comp.compilers.tools.pccts\9310.txt
# End Source File
# Begin Source File

SOURCE=..\contrib\comp.compilers.tools.pccts\9311.txt
# End Source File
# Begin Source File

SOURCE=..\contrib\comp.compilers.tools.pccts\9312.txt
# End Source File
# Begin Source File

SOURCE=..\contrib\comp.compilers.tools.pccts\9401.txt
# End Source File
# Begin Source File

SOURCE=..\contrib\comp.compilers.tools.pccts\9402.txt
# End Source File
# Begin Source File

SOURCE=..\contrib\comp.compilers.tools.pccts\9403.txt
# End Source File
# Begin Source File

SOURCE=..\contrib\comp.compilers.tools.pccts\9404.txt
# End Source File
# Begin Source File

SOURCE=..\contrib\comp.compilers.tools.pccts\9405.txt
# End Source File
# Begin Source File

SOURCE=..\contrib\comp.compilers.tools.pccts\9406.txt
# End Source File
# Begin Source File

SOURCE=..\contrib\comp.compilers.tools.pccts\9407.txt
# End Source File
# Begin Source File

SOURCE=..\contrib\comp.compilers.tools.pccts\9408.txt
# End Source File
# Begin Source File

SOURCE=..\contrib\comp.compilers.tools.pccts\9409.txt
# End Source File
# Begin Source File

SOURCE=..\contrib\comp.compilers.tools.pccts\9410.txt
# End Source File
# Begin Source File

SOURCE=..\contrib\comp.compilers.tools.pccts\9411.txt
# End Source File
# End Group
# Begin Source File

SOURCE=.\antlr.dsc
# End Source File
# Begin Source File

SOURCE=.\antlr.full.dsc
# End Source File
# Begin Source File

SOURCE=..\CHANGES_FROM_1.31
# End Source File
# Begin Source File

SOURCE=..\CHANGES_FROM_1.33
# End Source File
# Begin Source File

SOURCE=..\history.txt
# End Source File
# Begin Source File

SOURCE=..\KNOWN_PROBLEMS
# End Source File
# Begin Source File

SOURCE=..\known_problems.txt
# End Source File
# Begin Source File

SOURCE=..\NOTES.BCC
# End Source File
# Begin Source File

SOURCE=..\NOTES.MSVC
# End Source File
# Begin Source File

SOURCE=..\NOTES.OS2
# End Source File
# Begin Source File

SOURCE=..\NOTES.watcom
# End Source File
# Begin Source File

SOURCE=..\notesv1.txt
# End Source File
# Begin Source File

SOURCE=..\old_README
# End Source File
# Begin Source File

SOURCE=..\pccts.1
# End Source File
# Begin Source File

SOURCE=..\pccts1.txt
# End Source File
# Begin Source File

SOURCE=..\README
# End Source File
# Begin Source File

SOURCE=..\RIGHTS
# End Source File
# Begin Source File

SOURCE=..\SERVICES
# End Source File
# End Group
# Begin Group "Examples"

# PROP Default_Filter ""
# Begin Group "ANSI C Grammar"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\contrib\samples\ansi.c\ansi.g
# End Source File
# Begin Source File

SOURCE=..\contrib\samples\ansi.c\README
# End Source File
# Begin Source File

SOURCE=..\contrib\samples\ansi.c\Version.txt
# End Source File
# End Group
# Begin Group "Fortran 77 Grammar"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\contrib\samples\f77\decl.g
# End Source File
# Begin Source File

SOURCE=..\contrib\samples\f77\expr.g
# End Source File
# Begin Source File

SOURCE=..\contrib\samples\f77\f77.g
# End Source File
# Begin Source File

SOURCE=..\contrib\samples\f77\f77.prj
# End Source File
# Begin Source File

SOURCE=..\contrib\samples\f77\f77out.sor
# End Source File
# Begin Source File

SOURCE=..\contrib\samples\f77\f77trans.sor
# End Source File
# Begin Source File

SOURCE=..\contrib\samples\f77\io.g
# End Source File
# Begin Source File

SOURCE=..\contrib\samples\f77\readme
# End Source File
# Begin Source File

SOURCE=..\contrib\samples\f77\readme.txt
# End Source File
# End Group
# Begin Group "C++ Grammar"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\contrib\samples\cppparser\cplusplus.g
# End Source File
# Begin Source File

SOURCE=..\contrib\samples\cppparser\expr.g
# End Source File
# Begin Source File

SOURCE=..\contrib\samples\cppparser\README
# End Source File
# Begin Source File

SOURCE=..\contrib\samples\cppparser\stat.g
# End Source File
# End Group
# End Group
# End Target
# End Project
