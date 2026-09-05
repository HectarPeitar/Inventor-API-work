//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted,
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting documentation. 
// <YOUR COMPANY NAME> PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// <YOUR COMPANY NAME> SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE. <YOUR COMPANY NAME>, INC.
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE. 
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable
// 

//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
#ifdef PSEUDO_DEBUG
#undef _DEBUG
#pragma message ("     Compiling MFC / STL / ATL header files in release mode.")
#else
#if defined(_DEBUG) && defined(_AFXDLL)
#pragma message ("     Compiling MFC in Debug mode.")
#endif
#endif

//-----------------------------------------------------------------------------
#define STRICT

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN			//- Exclude rarely-used stuff from Windows headers
#endif

//- Modify the following defines if you have to target a platform prior to the ones specified below.
//- Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER					//- Allow use of features specific to Windows 7 or later.
#define WINVER 0x0601			//- Change this to the appropriate value to target Windows 7 or later.
#endif

#ifndef _WIN32_WINNT			//- Allow use of features specific to Windows 7 or later.
#define _WIN32_WINNT 0x0601		//- Change this to the appropriate value to target Windows 7 or later.
#endif						

#ifndef _WIN32_IE				//- Allow use of features specific to IE 4.0 or later.
#define _WIN32_IE 0x0700		//- Change this to the appropriate value to target IE 5.0 or later.
#endif

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	//- Some CString constructors will be explicit
//- Turns off ATL's hiding of some common and often safely ignored warning messages
#define _ATL_ALL_WARNINGS

[!if USE_MFC]
//-----------------------------------------------------------------------------
#include <afxwin.h>
#include <afxdisp.h>

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>				//- MFC OLE classes
#include <afxodlgs.h>			//- MFC OLE dialog classes
#include <afxdisp.h>			//- MFC Automation classes
#endif //- _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>				//- MFC ODBC database classes
#endif //- _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>				//- MFC DAO database classes
#endif //- _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>			//- MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>				//- MFC support for Windows Common Controls
#endif //- _AFX_NO_AFXCMN_SUPPORT

[!endif]
//-----------------------------------------------------------------------------
#include <AtlBase.h>
#include <AtlCom.h>
using namespace ATL ;

//-----------------------------------------------------------------------------
// Include SDK\DeveloperTools\Include\InventorUtils.h - this imports the Inventor typelibrary and includes other header files
#include "InventorUtils.h"

//-----------------------------------------------------------------------------
#ifdef PSEUDO_DEBUG
#define _DEBUG
#endif
