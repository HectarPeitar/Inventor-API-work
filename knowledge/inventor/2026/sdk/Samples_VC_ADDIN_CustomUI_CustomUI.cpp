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
//----- CustomUI.cpp : Implementation of DLL Exports.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//----- Note: Proxy/Stub Information
//-----  To build a separate proxy/stub DLL, 
//-----  run nmake -f CustomUIps.mk in the project directory.

//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "resource.h"

#include <initguid.h>
#include "CustomUI.h"
#include "CustomUI_i.c"

#include "CustomUIAddInServer.h"
#include "CmdHandler1.h"

//----- Do not delete the following line
//----- WIZARDS_VERSION=2, 0, 0, 6

//-----------------------------------------------------------------------------
CComModule _Module ;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_CustomUIAddInServer, CCustomUIAddInServer)
	//OBJECT_ENTRY(CLSID_CmdHandler1, CCmdHandler1)
	//OBJECT_ENTRY(CLSID_CmdHandler2, CCmdHandler2)
	//OBJECT_ENTRY(CLSID_CmdHandler3, CCmdHandler3)
	//OBJECT_ENTRY(CLSID_CmdHandler4, CCmdHandler4)
END_OBJECT_MAP()

//-----------------------------------------------------------------------------
//----- DLL Entry Point
extern "C" BOOL WINAPI DllMain (HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if ( dwReason == DLL_PROCESS_ATTACH )
	{
		_Module.Init (ObjectMap, hInstance, &LIBID_CustomUILib) ;
		DisableThreadLibraryCalls (hInstance) ;
	} else if ( dwReason == DLL_PROCESS_DETACH )
	{
		_Module.Term () ;
	}
	return TRUE ;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//----- Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow ()
{
    return ((_Module.GetLockCount () ==0 ) ? S_OK : S_FALSE) ;
}

//-----------------------------------------------------------------------------
//----- Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject (REFCLSID rclsid, REFIID riid, LPVOID *ppv) {
    return (_Module.GetClassObject (rclsid, riid, ppv)) ;
}

//-----------------------------------------------------------------------------
//----- DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer()
{
    //----- Registers object, typelib and all interfaces in typelib
    return _Module.RegisterServer (TRUE) ;
}

//-----------------------------------------------------------------------------
//----- DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer ()
{
    return _Module.UnregisterServer (TRUE) ;
}
#include "CmdHandler2.h"
#include "CmdHandler3.h"
#include "CmdHandler4.h"
