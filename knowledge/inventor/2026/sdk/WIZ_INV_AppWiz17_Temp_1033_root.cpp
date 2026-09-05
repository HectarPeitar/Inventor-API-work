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
//----- [!output PROJECT_NAME].cpp : Implementation of DLL Exports.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//----- Note: Proxy/Stub Information
//-----  To build a separate proxy/stub DLL, 
//-----  run nmake -f [!output PROJECT_NAME]ps.mk in the project directory.

//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "resource.h"

#include <initguid.h>
#include "[!output PROJECT_NAME].h"
#include "[!output PROJECT_NAME]_i.c"

[!if USE_MFC]
#include "[!output PROJECT_NAME]App.h"
[!endif]
#include "[!output ADDIN_NAME].h"

//-----------------------------------------------------------------------------
class C[!output PROJECT_NAME]Module : public CAtlDllModuleT<C[!output PROJECT_NAME]Module>
{
public :
	DECLARE_LIBID(LIBID_[!output PROJECT_NAME]Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_[!output PROJECT_NAME], "{[!output ATLSERVER_CLSID_REGISTRY_FORMAT]}")
} ;

C[!output PROJECT_NAME]Module _AtlModule ;


[!if USE_MFC]
//-----------------------------------------------------------------------------
C[!output PROJECT_NAME]App theApp ;

//-----------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(C[!output PROJECT_NAME]App, CWinApp)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
BOOL C[!output PROJECT_NAME]App::InitInstance ()
{
	COleObjectFactory::RegisterAll () ;
	return CWinApp::InitInstance () ;
}

int C[!output PROJECT_NAME]App::ExitInstance ()
{
	return CWinApp::ExitInstance () ;
}

[!else]

//----- DLL Entry Point
extern "C" BOOL WINAPI DllMain (HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	//----- Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved) ;

	if ( dwReason == DLL_PROCESS_ATTACH )
	{
	}
	else if ( dwReason == DLL_PROCESS_DETACH )
	{
	}
	return _AtlModule.DllMain (dwReason, lpReserved) ;
}

[!endif]

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//----- Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow ()
{
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
[!endif]
	return ((_AtlModule.GetLockCount () == 0) ? S_OK : S_FALSE) ;
}

//-----------------------------------------------------------------------------
//----- Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject (REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
	if ( _AtlModule.GetClassObject (rclsid, riid, ppv) == S_OK )
		return S_OK ;
	return AfxDllGetClassObject (rclsid, riid, ppv) ;
[!else]
	return _AtlModule.GetClassObject (rclsid, riid, ppv) ;
[!endif]
}

//-----------------------------------------------------------------------------
//----- DllRegisterServer - Adds entries to the system registry
// STDAPI DllRegisterServer()
// {
// [!if USE_MFC]
// 	AFX_MANAGE_STATE (AfxGetStaticModuleState()) ;
// 	_AtlModule.UpdateRegistryAppId (TRUE) ;
// 	HRESULT hRes =_AtlModule.RegisterServer (TRUE) ;
// 	if ( hRes != S_OK )
// 		return hRes ;
// 	if ( !COleObjectFactory::UpdateRegistryAll (TRUE) )
// 		return ResultFromScode (SELFREG_E_CLASS) ;
// 	return S_OK ;
// [!else]
// 	return _AtlModule.RegisterServer (TRUE) ;
// [!endif]
// }

//-----------------------------------------------------------------------------
//----- DllUnregisterServer - Removes entries from the system registry
// STDAPI DllUnregisterServer ()
// {
// [!if USE_MFC]
// 	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
// 	_AtlModule.UpdateRegistryAppId (FALSE) ;
// 	HRESULT hRes =_AtlModule.UnregisterServer (TRUE) ;
// 	if ( hRes != S_OK )
// 		return hRes ;
// 	if ( !COleObjectFactory::UpdateRegistryAll (FALSE) )
// 		return ResultFromScode (SELFREG_E_CLASS) ;
// 	return S_OK ;
// [!else]
// 	return _AtlModule.UnregisterServer (TRUE) ;
// [!endif]
// }

//-----------------------------------------------------------------------------
#ifdef _WIN64
#pragma comment(linker, "/EXPORT:DllCanUnloadNow=DllCanUnloadNow,PRIVATE")
#pragma comment(linker, "/EXPORT:DllGetClassObject=DllGetClassObject,PRIVATE")
// #pragma comment(linker, "/EXPORT:DllRegisterServer=DllRegisterServer,PRIVATE")
// #pragma comment(linker, "/EXPORT:DllUnregisterServer=DllUnregisterServer,PRIVATE")
#else
#pragma comment(linker, "/EXPORT:DllCanUnloadNow=_DllCanUnloadNow@0,PRIVATE")
#pragma comment(linker, "/EXPORT:DllGetClassObject=_DllGetClassObject@12,PRIVATE")
//#pragma comment(linker, "/EXPORT:DllRegisterServer=_DllRegisterServer@0,PRIVATE")
//#pragma comment(linker, "/EXPORT:DllUnregisterServer=_DllUnregisterServer@0,PRIVATE")
#endif
