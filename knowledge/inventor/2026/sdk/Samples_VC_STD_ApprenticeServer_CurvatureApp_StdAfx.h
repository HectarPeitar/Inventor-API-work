// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows 7 or later.
#define WINVER 0x0601		// Change this to the appropriate value to target other versions of Windows.
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>       // MFC support for Internet Explorer 4 Common Controls

#include <atlbase.h>

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>         // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

////////////////////////// AA ///////////////////////
#include <objidl.h>

#pragma warning(disable : 4049) // compiler limit : terminating line number emission
#pragma warning(push)
#pragma warning(disable : 4192) // automatically excluding 'name' while importing type library 'library'
#pragma warning(disable : 4278) // 'name':identifier in type library 'library' is already a macro

//#import <RxInventor.tlb> no_namespace named_guids raw_dispinterfaces raw_method_prefix("") high_method_prefix("Method")
#include "InventorUtils.h"

#pragma warning(pop)


#define PTEQTOL 1e-6

#define M_PI 3.14159265358979323846

/*
 * Macros to be used to handle error return codes
 */

#define OnError(badsts, label) \
	if (badsts) { ASSERT(false); goto label; }

#define OnErrorState(badsts,retval,errocode,label) \
	if (badsts) { ASSERT(false); retval = errocode; goto label; }

#define OnErrorReturn(badsts, errocode) \
	if (badsts) { ASSERT(false); return errocode; }

////////////////////////// AA ///////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
