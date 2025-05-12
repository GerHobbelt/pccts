# Microsoft Developer Studio Project File - Name="DLG" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=DLG - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DlgMSVC50.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/PRJ_VC/Projects/pccts/dlg", YCGBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DLG - Win32 Release"

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
# ADD CPP /W4 /GX /O2 /I "..\h" /I "..\support\set" /D "NDEBUG" /D "USER_ZZSYN" /D ZZLEXBUFSIZE=65536 /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FR /FD /TP /c
# SUBTRACT CPP /nologo /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib uuid.lib /nologo /subsystem:console /machine:I386 /out:"./Release/Dlg.exe"
# SUBTRACT LINK32 /map
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Copy to ..\bin directory
PostBuild_Cmds=mkdir  ..\bin 	copy  ..\bin\dlg.exe  dlg_old.exe 	copy  Release\dlg.exe  ..\bin\ 
# End Special Build Tool

!ELSEIF  "$(CFG)" == "DLG - Win32 Debug"

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
# ADD CPP /W4 /GX /ZI /Od /I "..\h" /I "..\support\set" /D "_DEBUG" /D "USER_ZZSYN" /D ZZLEXBUFSIZE=65536 /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FR /FD /TP /c
# SUBTRACT CPP /nologo /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib /nologo /subsystem:console /profile /map /debug /machine:I386 /out:"./Debug/Dlg.exe"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Copy to ..\bin directory
PostBuild_Cmds=mkdir  ..\bin 	copy  ..\bin\dlg.exe  dlg_old.exe 	copy  Debug\dlg.exe  ..\bin\ 
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "DLG - Win32 Release"
# Name "DLG - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\automata.c
# End Source File
# Begin Source File

SOURCE=.\dlg_a.c
# End Source File
# Begin Source File

SOURCE=.\dlg_p.c
# End Source File
# Begin Source File

SOURCE=.\dlg_p.g

!IF  "$(CFG)" == "DLG - Win32 Release"

# Begin Custom Build - Building DLG Parser from ANTLR Grammar
InputPath=.\dlg_p.g
InputName=dlg_p

BuildCmds= \
	..\bin\antlr -e3 $(InputName).g \
	..\bin\dlg -C2 parser.dlg dlg_a.c \
	..\bin\antlr -gc -pa -e3 -cr -ga  -tab 2 -w2 -info ptfmo $(InputName).g  > $(InputName).full.dsc \
	..\bin\antlr -gc -p -e3 -ga  -tab 2 -w2 $(InputName).g  > $(InputName).dsc \
	

"dlg_a.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"dlg_p.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"err.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"mode.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"parser.dlg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"tokens.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "DLG - Win32 Debug"

# Begin Custom Build - Building DLG Parser from ANTLR Grammar
InputPath=.\dlg_p.g
InputName=dlg_p

BuildCmds= \
	..\bin\antlr -e3 $(InputName).g \
	..\bin\dlg -C2 parser.dlg dlg_a.c \
	..\bin\antlr -gc -pa -e3 -cr -ga  -tab 2 -w2 -info ptfmo $(InputName).g  > $(InputName).full.dsc \
	..\bin\antlr -gc -p -e3 -ga  -tab 2 -w2 $(InputName).g  > $(InputName).dsc \
	

"dlg_a.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"dlg_p.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"err.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"mode.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"parser.dlg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"tokens.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\err.c
# End Source File
# Begin Source File

SOURCE=.\main.c
# End Source File
# Begin Source File

SOURCE=.\output.c
# End Source File
# Begin Source File

SOURCE=.\parser.dlg
# End Source File
# Begin Source File

SOURCE=.\relabel.c
# End Source File
# Begin Source File

SOURCE=..\support\set\set.c
# End Source File
# Begin Source File

SOURCE=.\support.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\h\antlr.h
# End Source File
# Begin Source File

SOURCE=..\h\ast.inc
# End Source File
# Begin Source File

SOURCE=.\dlg.h
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

SOURCE=..\support\set\set.h
# End Source File
# Begin Source File

SOURCE=.\stdpccts.h
# End Source File
# Begin Source File

SOURCE=.\tokens.h
# End Source File
# End Group
# Begin Group "Documentation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\dlg1.txt
# End Source File
# Begin Source File

SOURCE=.\dlg_p.dsc
# End Source File
# Begin Source File

SOURCE=.\dlg_p.full.dsc
# End Source File
# End Group
# End Target
# End Project
