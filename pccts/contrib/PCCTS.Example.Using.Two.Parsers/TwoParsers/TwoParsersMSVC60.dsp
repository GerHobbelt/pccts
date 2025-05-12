# Microsoft Developer Studio Project File - Name="TwoParsers" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=TwoParsers - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TwoParsersMSVC60.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TwoParsersMSVC60.mak" CFG="TwoParsers - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TwoParsers - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "TwoParsers - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TwoParsers - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "." /I "..\..\..\h" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib comdlg32.lib advapi32.lib shell32.lib uuid.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "TwoParsers - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "." /I "..\..\..\h" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib comdlg32.lib advapi32.lib shell32.lib uuid.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "TwoParsers - Win32 Release"
# Name "TwoParsers - Win32 Debug"
# Begin Group "A"

# PROP Default_Filter ""
# Begin Group "Generated A"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PA\A.cpp
# End Source File
# Begin Source File

SOURCE=.\PA\DlgA.cpp
# End Source File
# Begin Source File

SOURCE=.\PA\DlgA.h
# End Source File
# Begin Source File

SOURCE=.\PA\ParserA.cpp
# End Source File
# Begin Source File

SOURCE=.\PA\ParserA.h
# End Source File
# Begin Source File

SOURCE=.\PA\tokens.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\PA\A.g

!IF  "$(CFG)" == "TwoParsers - Win32 Release"

# Begin Custom Build - Generate A
InputPath=.\PA\A.g

BuildCmds= \
	..\..\..\bin\antlr.exe -emsvc -CC Pa\A.g -glms  -o Pa \
	..\..\..\bin\dlg.exe -emsvc -CC -C2 Pa\parser.dlg -o Pa -cl DlgA \
	

"Pa\tokens.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Pa\DlgA.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Pa\DlgA.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Pa\A.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Pa\ParserA.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Pa\ParserA.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TwoParsers - Win32 Debug"

# Begin Custom Build - Generate A
InputPath=.\PA\A.g

BuildCmds= \
	..\..\..\bin\antlr.exe -emsvc -CC Pa\A.g -glms  -o Pa \
	..\..\..\bin\dlg.exe -emsvc -CC -C2 Pa\parser.dlg -o Pa -cl DlgA \
	

"Pa\tokens.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Pa\DlgA.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Pa\DlgA.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Pa\A.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Pa\ParserA.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Pa\ParserA.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "B"

# PROP Default_Filter ""
# Begin Group "Generated B"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Pb\B.cpp
# End Source File
# Begin Source File

SOURCE=.\Pb\DlgB.cpp
# End Source File
# Begin Source File

SOURCE=.\Pb\DlgB.h
# End Source File
# Begin Source File

SOURCE=.\Pb\ParserB.cpp
# End Source File
# Begin Source File

SOURCE=.\Pb\ParserB.h
# End Source File
# Begin Source File

SOURCE=.\Pb\tokens.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Pb\B.g

!IF  "$(CFG)" == "TwoParsers - Win32 Release"

# Begin Custom Build - Generate B
InputPath=.\Pb\B.g

BuildCmds= \
	..\..\..\bin\antlr.exe -emsvc -CC Pb\B.g -glms  -o Pb \
	..\..\..\bin\dlg.exe -emsvc -CC -C2 Pb\parser.dlg -o Pb -cl DlgB \
	

"Pb\tokens.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Pb\DlgLexer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Pb\DlgLexer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Pb\ParserB.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Pb\ParserB.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Pb\B.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TwoParsers - Win32 Debug"

# Begin Custom Build - Generate B
InputPath=.\Pb\B.g

BuildCmds= \
	..\..\..\bin\antlr.exe -emsvc -CC Pb\B.g -glms  -o Pb \
	..\..\..\bin\dlg.exe -emsvc -CC -C2 Pb\parser.dlg -o Pb -cl DlgB \
	

"Pb\tokens.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Pb\DlgB.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Pb\DlgB.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Pb\ParserB.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Pb\ParserB.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Pb\B.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Application"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\InvokeA.cpp
# End Source File
# Begin Source File

SOURCE=.\InvokeB.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# End Group
# Begin Group "Library files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\h\AParser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\h\ASTBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\h\ATokenBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\h\BufFileInput.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\h\DLexerBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\h\PCCTSAST.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\h\SList.cpp
# End Source File
# End Group
# End Target
# End Project
