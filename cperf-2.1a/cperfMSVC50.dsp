# Microsoft Developer Studio Project File - Name="cperf" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=cperf - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cperf.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cperf.mak" CFG="cperf - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cperf - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "cperf - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/prj_vc/projects/cperf-2.1a", EAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cperf - Win32 Release"

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
# ADD CPP /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FR /FD /TP /c
# SUBTRACT CPP /nologo
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 winspool.lib ole32.lib oleaut32.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib uuid.lib /subsystem:console /machine:I386 /out:".\gperf.exe"
# SUBTRACT LINK32 /nologo /map

!ELSEIF  "$(CFG)" == "cperf - Win32 Debug"

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
# ADD CPP /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /FD /TP /c
# SUBTRACT CPP /nologo
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib /subsystem:console /profile /map /debug /machine:I386 /out:".\gperf.exe"
# SUBTRACT LINK32 /nologo

!ENDIF 

# Begin Target

# Name "cperf - Win32 Release"
# Name "cperf - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\boolarray.c
# End Source File
# Begin Source File

SOURCE=.\src\getopt.c
# End Source File
# Begin Source File

SOURCE=.\src\hashtable.c
# End Source File
# Begin Source File

SOURCE=.\src\iterator.c
# End Source File
# Begin Source File

SOURCE=.\src\keylist.c
# End Source File
# Begin Source File

SOURCE=.\src\listnode.c
# End Source File
# Begin Source File

SOURCE=.\src\main.c
# End Source File
# Begin Source File

SOURCE=.\src\options.c
# End Source File
# Begin Source File

SOURCE=.\src\perfect.c
# End Source File
# Begin Source File

SOURCE=.\src\readline.c
# End Source File
# Begin Source File

SOURCE=.\src\stderr.c
# End Source File
# Begin Source File

SOURCE=.\src\version.c
# End Source File
# Begin Source File

SOURCE=.\src\xmalloc.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\boolarray.h
# End Source File
# Begin Source File

SOURCE=.\src\hashtable.h
# End Source File
# Begin Source File

SOURCE=.\src\iterator.h
# End Source File
# Begin Source File

SOURCE=.\src\keylist.h
# End Source File
# Begin Source File

SOURCE=.\src\listnode.h
# End Source File
# Begin Source File

SOURCE=.\src\options.h
# End Source File
# Begin Source File

SOURCE=.\src\perfect.h
# End Source File
# Begin Source File

SOURCE=.\src\prototype.h
# End Source File
# Begin Source File

SOURCE=.\src\readline.h
# End Source File
# Begin Source File

SOURCE=.\src\stderr.h
# End Source File
# End Group
# Begin Group "Documentation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ChangeLog
# End Source File
# Begin Source File

SOURCE=.\COPYING
# End Source File
# Begin Source File

SOURCE=.\gperf.1
# End Source File
# Begin Source File

SOURCE=.\README
# End Source File
# Begin Source File

SOURCE=".\README-FIRST"
# End Source File
# End Group
# Begin Group "Examples"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\tests\ada.gperf
# End Source File
# Begin Source File

SOURCE=.\tests\adapredefined.gperf
# End Source File
# Begin Source File

SOURCE=".\tests\c++.gperf"
# End Source File
# Begin Source File

SOURCE=".\tests\c-parse.gperf"
# End Source File
# Begin Source File

SOURCE=.\tests\c.gperf
# End Source File
# Begin Source File

SOURCE=.\tests\gpc.gperf
# End Source File
# Begin Source File

SOURCE=.\tests\gplus.gperf
# End Source File
# Begin Source File

SOURCE=.\tests\modula2.gperf
# End Source File
# Begin Source File

SOURCE=.\tests\modula3.gperf
# End Source File
# Begin Source File

SOURCE=.\tests\pascal.gperf
# End Source File
# End Group
# End Target
# End Project
