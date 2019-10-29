# Microsoft Developer Studio Project File - Name="WebComServer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=WebComServer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WebComServer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WebComServer.mak" CFG="WebComServer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WebComServer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "WebComServer - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "WebComServer - Win32 Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "WebComServer - Win32 Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE "WebComServer - Win32 Unicode Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "WebComServer - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WebComServer - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib Ws2_32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Work/WebComServer.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Performing registration
OutDir=.\Debug
TargetPath=.\Work\WebComServer.exe
InputPath=.\Work\WebComServer.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "WebComServer - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Performing registration
OutDir=.\DebugU
TargetPath=.\DebugU\WebComServer.exe
InputPath=.\DebugU\WebComServer.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "WebComServer - Win32 Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinSize"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib MSVCRT.LIB comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"Work/WebComServer.exe"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinSize
TargetPath=.\Work\WebComServer.exe
InputPath=.\Work\WebComServer.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "WebComServer - Win32 Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinDependency"
# PROP BASE Intermediate_Dir "ReleaseMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinDependency"
# PROP Intermediate_Dir "ReleaseMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib MSVCRT.LIB comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"Work/WebComServer.exe"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinDependency
TargetPath=.\Work\WebComServer.exe
InputPath=.\Work\WebComServer.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "WebComServer - Win32 Unicode Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinSize"
# PROP BASE Intermediate_Dir "ReleaseUMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinSize"
# PROP Intermediate_Dir "ReleaseUMinSize"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\WebComServer.exe
InputPath=.\ReleaseUMinSize\WebComServer.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "WebComServer - Win32 Unicode Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinDependency"
# PROP BASE Intermediate_Dir "ReleaseUMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinDependency"
# PROP Intermediate_Dir "ReleaseUMinDependency"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\WebComServer.exe
InputPath=.\ReleaseUMinDependency\WebComServer.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "WebComServer - Win32 Debug"
# Name "WebComServer - Win32 Unicode Debug"
# Name "WebComServer - Win32 Release MinSize"
# Name "WebComServer - Win32 Release MinDependency"
# Name "WebComServer - Win32 Unicode Release MinSize"
# Name "WebComServer - Win32 Unicode Release MinDependency"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CMonitoring.cpp
# End Source File
# Begin Source File

SOURCE=.\CSend.cpp
# End Source File
# Begin Source File

SOURCE=.\MServerComponent.cpp
# End Source File
# Begin Source File

SOURCE=.\RegisterSave.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WebComServer.cpp
# End Source File
# Begin Source File

SOURCE=.\WebComServer.idl
# ADD MTL /tlb ".\WebComServer.tlb" /h "WebComServer.h" /iid "WebComServer_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\WebComServer.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CMonitoring.h
# End Source File
# Begin Source File

SOURCE=.\CSend.h
# End Source File
# Begin Source File

SOURCE=.\MServerComponent.h
# End Source File
# Begin Source File

SOURCE=.\RegisterSave.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Image\Atom4.ico
# End Source File
# Begin Source File

SOURCE=.\Image\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\close.bmp
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\Image\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\Image\icontools.ico
# End Source File
# Begin Source File

SOURCE=.\Image\properti.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\selected.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\selectin.bmp
# End Source File
# Begin Source File

SOURCE=.\WebComServer.rgs
# End Source File
# End Group
# End Target
# End Project
# Section WebComServer : {00000000-0000-0000-0000-800000800000}
# 	1:15:IDD_CMONITORING:101
# End Section
