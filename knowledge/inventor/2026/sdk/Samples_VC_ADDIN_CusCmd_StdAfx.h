//-----------------------------------------------------------------------------
//----- StdAfx.h : include file for standard system include files,
//----- or project specific include files that are used frequently,
//----- but are changed infrequently
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
#ifdef PSEUDO_DEBUG
#undef _DEBUG
#pragma message ("     Compiling MFC / STL / ATL header files in release mode.")
#else
#endif

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
#include <afxtempl.h>

//-----------------------------------------------------------------------------
#include <atlbase.h>

//----- You may derive a class from CComModule and use it if you want to override
//----- something, but do not change the name of _Module
extern CComModule _Module ;
#include <atlcom.h>

//-----------------------------------------------------------------------------
#ifdef PSEUDO_DEBUG
#define _DEBUG
#endif

#pragma warning(disable : 4049) // compiler limit : terminating line number emission
#pragma warning(disable : 4192) // automatically excluding 'name' while importing type library 'library'
#pragma warning(disable : 4278) // 'name':identifier in type library 'library' is already a macro

//-----------------------------------------------------------------------------
//----- Inventor interfaces include
#include "InventorUtils.h"
