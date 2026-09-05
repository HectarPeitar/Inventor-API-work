//-----------------------------------------------------------------------------
//----- CustomCommand.cpp : Implementation of DLL Exports.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//----- Note: Proxy/Stub Information
//-----  To build a separate proxy/stub DLL, 
//-----  run nmake -f CustomCommandps.mk in the project directory.

//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "resource.h"

#include <initguid.h>
#include "CustomCommand.h"
#include "CustomCommand_i.c"

#include "CustomCommandApp.h"
#include "CustomCommandAddInServer.h"

//----- Do not delete the following line
//----- WIZARDS_VERSION=9, 0, 0, 2

//-----------------------------------------------------------------------------
CComModule _Module ;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_CustomCommandAddInServer, CCustomCommandAddInServer)
END_OBJECT_MAP()

//-----------------------------------------------------------------------------
CCustomCommandApp theApp ;

//-----------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CCustomCommandApp, CWinApp)
	//{{AFX_MSG_MAP(CCustomCommandApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
BOOL CCustomCommandApp::InitInstance ()
{
    _Module.Init (ObjectMap, m_hInstance, &LIBID_CustomCommandLib) ;
    return CWinApp::InitInstance () ;
}

int CCustomCommandApp::ExitInstance ()
{
    _Module.Term () ;
    return CWinApp::ExitInstance () ;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//----- Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow ()
{
    AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
    return ((AfxDllCanUnloadNow () == S_OK && _Module.GetLockCount () == 0) ? S_OK : S_FALSE) ;
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
