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
//----- StdAfx.h : include file for standard system include files,
//----- or project specific include files that are used frequently,
//----- but are changed infrequently
#if !defined(AFX_STDAFX_H__86E6BE73_1DFE_44D6_A915_B8B3398F5A9D__INCLUDED_)
#define AFX_STDAFX_H__86E6BE73_1DFE_44D6_A915_B8B3398F5A9D__INCLUDED_

//-----------------------------------------------------------------------------
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//-----------------------------------------------------------------------------
#define STRICT
#ifndef _WIN32_WINNT
//#define _WIN32_WINNT 0x0400
#define _WIN32_WINNT 0x0501
#endif
#define _ATL_APARTMENT_THREADED

//-----------------------------------------------------------------------------
#include <afxwin.h>
#include <afxdisp.h>
#include <AfxCtl.h>

//-----------------------------------------------------------------------------
#include <atlbase.h>

//----- You may derive a class from CComModule and use it if you want to override
//----- something, but do not change the name of _Module
extern CComModule _Module ;
#include <atlcom.h>

//-----------------------------------------------------------------------------
//{{AFX_INSERT_LOCATION}}

// Eliminate botherware warnings
#pragma warning(disable : 4049) // compiler limit : terminating line number emission
#pragma warning(disable : 4192) // automatically excluding 'name' while importing type library 'library'
#pragma warning(disable : 4278) // 'name':identifier in type library 'library' is already a macro

// Inventor interfaces include
#include "InventorUtils.h"

//-----------------------------------------------------------------------------
#endif //----- !defined(AFX_STDAFX_H__86E6BE73_1DFE_44D6_A915_B8B3398F5A9D__INCLUDED)


