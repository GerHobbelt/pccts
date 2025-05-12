# Microsoft Developer Studio Project File - Name="Sorcerer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Sorcerer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SorcererMSVC50.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SorcererMSVC50.mak" CFG="Sorcerer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Sorcerer - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Sorcerer - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/PRJ_VC/Projects/pccts/sorcerer", ZCGBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Sorcerer - Win32 Release"

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
# ADD CPP /W4 /GX /O2 /I "." /I "..\h" /I "..\support\set" /D "NDEBUG" /D ZZLEXBUFSIZE=65536 /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FR /FD /TP /c
# SUBTRACT CPP /nologo /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib uuid.lib /nologo /subsystem:console /machine:I386 /out:"./Release/Sorcerer.exe"
# SUBTRACT LINK32 /map
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Update executables in BIN directory and remove intermediate                  files
PostBuild_Cmds=del  ..\bin\Antlr.old 	rename         ..\bin\Antlr.exe           Antlr.old 	copy  ..\Antlr\Release\Antlr.exe  ..\bin\ 	del                  ..\bin\Dlg.old 	rename  ..\bin\Dlg.exe  Dlg.old 	copy           ..\Dlg\Release\dlg.exe         ..\bin 	del  ..\bin\Sorcerer.old 	rename           ..\bin\Sorcerer.exe         Sorcerer.old 	copy           ..\Sorcerer\Release\Sorcerer.exe  ..\bin\ 
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Sorcerer - Win32 Debug"

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
# ADD CPP /W4 /GX /ZI /Od /I "." /I "..\h" /I "..\support\set" /D ZZLEXBUFSIZE=65536 /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FR /FD /TP /c
# SUBTRACT CPP /nologo /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib /nologo /subsystem:console /profile /map /debug /machine:I386 /out:"./Debug/Sorcerer.exe"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Update executables in BIN directory and remove intermediate                  files
PostBuild_Cmds=mkdir  ..\bin 	del  ..\bin\Antlr.old 	rename  ..\bin\Antlr.exe  Antlr.old 	copy  ..\Antlr\Debug\Antlr.exe  ..\bin\ 	del  ..\bin\Dlg.old 	rename  ..\bin\Dlg.exe  Dlg.old 	copy  ..\Dlg\Debug\dlg.exe  ..\bin\ 	del  ..\bin\Sorcerer.old 	rename  ..\bin\Sorcerer.exe  Sorcerer.old 	copy  ..\Sorcerer\Debug\Sorcerer.exe  ..\bin\ 
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "Sorcerer - Win32 Release"
# Name "Sorcerer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cpp.c
# End Source File
# Begin Source File

SOURCE=.\err.c
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

SOURCE=.\look.c
# End Source File
# Begin Source File

SOURCE=.\main.c
# End Source File
# Begin Source File

SOURCE=.\parser.dlg
# End Source File
# Begin Source File

SOURCE=.\scan.c
# End Source File
# Begin Source File

SOURCE=..\support\set\set.c
# End Source File
# Begin Source File

SOURCE=.\sor.c
# End Source File
# Begin Source File

SOURCE=.\sor.g

!IF  "$(CFG)" == "Sorcerer - Win32 Release"

# Begin Custom Build - Generating Parser
InputPath=.\sor.g
InputName=sor

BuildCmds= \
	..\bin\antlr -gh -k 2 -e3 -gt $(InputName).g \
	..\bin\dlg -C2 parser.dlg scan.c \
	

"parser.dlg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"mode.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"stdpccts.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sor.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"scan.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"err.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Sorcerer - Win32 Debug"

# Begin Custom Build - Generating Parser
InputPath=.\sor.g
InputName=sor

BuildCmds= \
	..\bin\antlr -gh -k 2 -e3 -gt $(InputName).g \
	..\bin\dlg -C2 parser.dlg scan.c \
	

"parser.dlg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"mode.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"stdpccts.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"sor.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"scan.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"err.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\h\antlr.h
# End Source File
# Begin Source File

SOURCE=..\h\ast.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\h\ast.h
# End Source File
# Begin Source File

SOURCE=..\h\charbuf.h
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

SOURCE=.\sor.h
# End Source File
# Begin Source File

SOURCE=.\h\sorcerer.h
# End Source File
# Begin Source File

SOURCE=.\stdpccts.h
# End Source File
# Begin Source File

SOURCE=.\sym.h
# End Source File
# Begin Source File

SOURCE=.\tokens.h
# End Source File
# End Group
# Begin Group "Documentation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\testcpp\test4\lang.g
# End Source File
# Begin Source File

SOURCE=.\README
# End Source File
# Begin Source File

SOURCE=.\testcpp\test.sor
# End Source File
# Begin Source File

SOURCE=.\testcpp\test2.sor
# End Source File
# Begin Source File

SOURCE=.\testcpp\test3.sor
# End Source File
# Begin Source File

SOURCE=.\testcpp\test4\test4.sor
# End Source File
# Begin Source File

SOURCE=.\testcpp\test5.sor
# End Source File
# Begin Source File

SOURCE=.\UPDATES
# End Source File
# End Group
# End Target
# End Project
