// InventorThumbnailView.cpp : Implementation of DLL Exports.

#include "StdAfx.h"
#include "resource.h"
#include "InventorThumbnailView.h"

class CInventorThumbnailViewModule : public CAtlDllModuleT< CInventorThumbnailViewModule >
{
public :
	DECLARE_LIBID(LIBID_InventorThumbnailViewLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_INVENTORTHUMBNAILVIEW, "{FA253FF8-9A98-474D-85CA-DF34A4F2143D}")
};

CInventorThumbnailViewModule _AtlModule;


// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved); 
}


// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow()
{
    return _AtlModule.DllCanUnloadNow();
}


// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer()
{
    // registers object, typelib and all interfaces in typelib
    HRESULT hr = _AtlModule.DllRegisterServer();
	return hr;
}


// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer()
{
	HRESULT hr = _AtlModule.DllUnregisterServer();
	return hr;
}
