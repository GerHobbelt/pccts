# Microsoft Developer Studio Project File - Name="testcase" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=testcase - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "testcase.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "testcase.mak" CFG="testcase - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "testcase - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "testcase - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/prj_vc/projects/testcase", IAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "testcase - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /W4 /GX /O2 /I "." /I "..\pccts\h" /I "..\pccts\support\set" /I "..\pccts\support\rexpr" /I "..\pccts\support\sym" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "__USE_PROTOS" /D "USER_ZZSYN" /FR /FD /c
# SUBTRACT CPP /nologo /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /subsystem:console /machine:I386
# SUBTRACT LINK32 /nologo /map

!ELSEIF  "$(CFG)" == "testcase - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /W4 /Gm /GX /ZI /Od /I "." /I "..\pccts\h" /I "..\pccts\support\set" /I "..\pccts\support\rexpr" /I "..\pccts\support\sym" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "__USE_PROTOS" /D "USER_ZZSYN" /FR /FD /c
# SUBTRACT CPP /nologo /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /subsystem:console /profile /map /debug /machine:I386
# SUBTRACT LINK32 /nologo

!ENDIF 

# Begin Target

# Name "testcase - Win32 Release"
# Name "testcase - Win32 Debug"
# Begin Group "C Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\debug.c
# End Source File
# Begin Source File

SOURCE=.\err.c
# End Source File
# Begin Source File

SOURCE=.\i_a_script.gperf

!IF  "$(CFG)" == "testcase - Win32 Release"

# Begin Custom Build - Compile GPERF keyword hash table spec
InputPath=.\i_a_script.gperf

"keywords.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\cperf-2.1a\gperf -VpotT -e@ -lj1 -k1,5,$ -aCdgH decode_keyword -N                   in_reserved_keyword_set  i_a_script.gperf keywords.c

# End Custom Build

!ELSEIF  "$(CFG)" == "testcase - Win32 Debug"

# Begin Custom Build - Compile GPERF keyword hash table spec
InputPath=.\i_a_script.gperf

"keywords.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\cperf-2.1a\gperf -VpotTD -e@ -j1 -k1,3,4,5,7,$ -aCdgH decode_keyword -N                   in_reserved_keyword_set  i_a_script.gperf keywords.c

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\keywords.c
# End Source File
# Begin Source File

SOURCE=.\lexer.c
# End Source File
# Begin Source File

SOURCE=.\main.c
# End Source File
# Begin Source File

SOURCE=.\parser.dlg

!IF  "$(CFG)" == "testcase - Win32 Release"

# Begin Custom Build - Compiling with DLG
InputPath=.\parser.dlg

BuildCmds= \
	..\bin\dlg -C2 -ga -Wambiguity -i -ci parser.dlg scan.c

"scan.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"mode.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "testcase - Win32 Debug"

# Begin Custom Build - Compiling with DLG
InputPath=.\parser.dlg

BuildCmds= \
	..\bin\dlg -C2 -ga -Wambiguity -i -ci parser.dlg scan.c

"scan.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"mode.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\pccts\support\rexpr\rexpr.c
# End Source File
# Begin Source File

SOURCE=.\scan.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\script.c
# End Source File
# Begin Source File

SOURCE=.\script.g

!IF  "$(CFG)" == "testcase - Win32 Release"

# Begin Custom Build - Compile with ANTLR
InputPath=.\script.g
InputName=script

BuildCmds= \
	..\bin\antlr -gd -gs -gh -e3 -cr -ga -k 2 -tab 2 -w2  -gk -rl 2000 $(InputName).g \
	..\bin\antlr -gc -p -e3 -cr -ga -k 2 -tab 2 -gk  -w2  -rl 2000 $(InputName).g  > $(InputName).dsc \
	..\bin\antlr -gc -pa -e3 -cr -ga -k 2 -tab 2 -gk  -w2 -info ptfmo -rl 2000 $(InputName).g  > $(InputName).full.dsc \
	

"parser.dlg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"script.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"tokens.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"err.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"script.dsc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"script.full.dsc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "testcase - Win32 Debug"

# Begin Custom Build - Compile with ANTLR
InputPath=.\script.g
InputName=script

BuildCmds= \
	..\bin\antlr -gd -gs -gh -e3 -cr -ga -k 2 -tab 2 -w2  -gk -rl 2000 $(InputName).g \
	..\bin\antlr -gc -p -e3 -cr -ga -k 2 -tab 2 -gk  -w2  -rl 2000 $(InputName).g  > $(InputName).dsc \
	..\bin\antlr -gc -pa -e3 -cr -ga -k 2 -tab 2 -gk  -w2 -info ptfmo -rl 2000 $(InputName).g  > $(InputName).full.dsc \
	

"parser.dlg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"script.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"tokens.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"err.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"script.dsc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"script.full.dsc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\pccts\support\set\set.c
# End Source File
# Begin Source File

SOURCE=.\support.c
# End Source File
# Begin Source File

SOURCE=..\pccts\support\sym\sym.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\pccts\h\antlr.h
# End Source File
# Begin Source File

SOURCE=.\attrib.h
# End Source File
# Begin Source File

SOURCE=..\pccts\h\dlgauto.h
# End Source File
# Begin Source File

SOURCE=..\pccts\h\dlgdef.h
# End Source File
# Begin Source File

SOURCE=..\pccts\h\err.h
# End Source File
# Begin Source File

SOURCE=.\mode.h
# End Source File
# Begin Source File

SOURCE=..\pccts\h\pccts_stdarg.h
# End Source File
# Begin Source File

SOURCE=..\pccts\h\pccts_stdio.h
# End Source File
# Begin Source File

SOURCE=..\pccts\h\pccts_stdlib.h
# End Source File
# Begin Source File

SOURCE=..\pccts\h\pccts_string.h
# End Source File
# Begin Source File

SOURCE=..\pccts\h\pcctscfg.h
# End Source File
# Begin Source File

SOURCE=..\pccts\support\rexpr\rexpr.h
# End Source File
# Begin Source File

SOURCE=..\pccts\support\set\set.h
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

SOURCE=.\script.dsc
# End Source File
# Begin Source File

SOURCE=.\script.full.dsc
# End Source File
# End Group
# Begin Group "Tests"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\prof.bat
# End Source File
# Begin Source File

SOURCE=.\sample.sc
# End Source File
# End Group
# Begin Group "Archiving"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ARCHIVE.BAT
# End Source File
# Begin Source File

SOURCE=..\CLEANUP.BAT
# End Source File
# End Group
# End Target
# End Project
