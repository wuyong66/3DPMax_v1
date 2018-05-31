# Microsoft Developer Studio Project File - Name="3DPMax" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=3DPMax - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "3DPMax.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "3DPMax.mak" CFG="3DPMax - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "3DPMax - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "3DPMax - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "3DPMax - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "3DPMax - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "3DPMax - Win32 Release"
# Name "3DPMax - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "3DPMax_S"

# PROP Default_Filter ""
# Begin Group "ModBusRTU_S"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODBUS_SERVER.cpp
# End Source File
# Begin Source File

SOURCE=.\MODBUS_SHARE.cpp
# End Source File
# Begin Source File

SOURCE=.\ModBusRTU.cpp
# End Source File
# Begin Source File

SOURCE=.\ModBusThread.cpp
# End Source File
# Begin Source File

SOURCE=.\PORT.cpp
# End Source File
# End Group
# Begin Group "ModBusTcp_S"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ModBusTcp.cpp
# End Source File
# Begin Source File

SOURCE=.\Mysocket.cpp
# End Source File
# End Group
# Begin Group "OTHER_S"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3DPMax.cpp
# End Source File
# Begin Source File

SOURCE=.\3DPMax.rc
# End Source File
# Begin Source File

SOURCE=.\3DPMaxDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\3DPMaxView.cpp
# End Source File
# Begin Source File

SOURCE=.\3DPSta.cpp
# End Source File
# Begin Source File

SOURCE=.\Bin2AscOfSTLDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CHECKDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\CheckThread.cpp
# End Source File
# Begin Source File

SOURCE=.\CheckView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChkPlace.cpp
# End Source File
# Begin Source File

SOURCE=.\Communication.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ModalProperty.cpp
# End Source File
# Begin Source File

SOURCE=.\mscomm3.cpp
# End Source File
# Begin Source File

SOURCE=.\PritMod.cpp
# End Source File
# Begin Source File

SOURCE=.\SliceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# End Group
# Begin Group "GeomCalc_S"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\GeomCalc\CadBase.cpp
# End Source File
# Begin Source File

SOURCE=..\GeomCalc\CadBase1.cpp
# End Source File
# End Group
# Begin Group "GeomKernel_S"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Geomkernel\Entity.cpp
# End Source File
# End Group
# Begin Group "glContext_S"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\glContext\Camera.cpp
# End Source File
# Begin Source File

SOURCE=..\glContext\GLView.cpp
# End Source File
# Begin Source File

SOURCE=..\glContext\OPenGLDC.cpp
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "3DPMax_H"

# PROP Default_Filter ""
# Begin Group "ModBusRTU_H"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODBUS_SERVER.h
# End Source File
# Begin Source File

SOURCE=.\MODBUS_SHARE.h
# End Source File
# Begin Source File

SOURCE=.\ModBusRTU.h
# End Source File
# Begin Source File

SOURCE=.\ModBusThread.h
# End Source File
# Begin Source File

SOURCE=.\PORT.h
# End Source File
# End Group
# Begin Group "ModusTcp_S"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ModBusTcp.h
# End Source File
# Begin Source File

SOURCE=.\Mysocket.h
# End Source File
# End Group
# Begin Group "OTHER_H"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3DPMax.h
# End Source File
# Begin Source File

SOURCE=.\3DPMaxDoc.h
# End Source File
# Begin Source File

SOURCE=.\3DPMaxView.h
# End Source File
# Begin Source File

SOURCE=.\3DPSta.h
# End Source File
# Begin Source File

SOURCE=.\Bin2AscOfSTLDlg.h
# End Source File
# Begin Source File

SOURCE=.\CHECKDLG.h
# End Source File
# Begin Source File

SOURCE=.\CheckThread.h
# End Source File
# Begin Source File

SOURCE=.\CheckView.h
# End Source File
# Begin Source File

SOURCE=.\ChkPlace.h
# End Source File
# Begin Source File

SOURCE=.\Communication.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\ModalProperty.h
# End Source File
# Begin Source File

SOURCE=.\mscomm3.h
# End Source File
# Begin Source File

SOURCE=.\PritMod.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SliceDlg.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# End Group
# Begin Group "GeomCalc_H"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\GeomCalc\CadBase.h
# End Source File
# End Group
# Begin Group "GeomKernel_H"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Geomkernel\Entity.h
# End Source File
# End Group
# Begin Group "glContext_H"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\glContext\Camera.h
# End Source File
# Begin Source File

SOURCE=..\glContext\OPenGLDC.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Group "3DPMax_R"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\res\3DPMax.ico
# End Source File
# Begin Source File

SOURCE=.\res\3DPMax.rc2
# End Source File
# Begin Source File

SOURCE=.\res\3DPMaxDoc.ico
# End Source File
# Begin Source File

SOURCE=..\FlashBmp\Flash.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "GeomCalc_R"

# PROP Default_Filter ""
# End Group
# Begin Group "GeomKernel_R"

# PROP Default_Filter ""
# End Group
# Begin Group "glContext_R"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=.\res\Flash.bmp
# End Source File
# Begin Source File

SOURCE=.\Splsh16.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section 3DPMax : {E6E17E90-DF38-11CF-8E74-00A0C90F26F8}
# 	2:5:Class:CMSComm
# 	2:10:HeaderFile:mscomm3.h
# 	2:8:ImplFile:mscomm3.cpp
# End Section
# Section 3DPMax : {648A5600-2C6E-101B-82B6-000000000014}
# 	2:21:DefaultSinkHeaderFile:mscomm3.h
# 	2:16:DefaultSinkClass:CMSComm
# End Section
# Section 3DPMax : {72ADFD78-2C39-11D0-9903-00A0C91BC942}
# 	1:11:IDB_SPLASH1:102
# 	2:21:SplashScreenInsertKey:4.0
# End Section
