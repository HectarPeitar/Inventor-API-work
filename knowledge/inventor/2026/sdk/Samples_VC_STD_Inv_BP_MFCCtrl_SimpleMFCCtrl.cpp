// SIMPLEMFCCONTROL.cpp : Implementation of CSIMPLEMFCCONTROLApp and DLL registration.

#include "stdafx.h"
#include "SIMPLEMFCCONTROL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CSIMPLEMFCCONTROLApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xe230d8e9, 0xc189, 0x49aa, { 0xa9, 0x32, 0x1, 0xb5, 0xf4, 0x35, 0x7, 0xeb } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROLApp::InitInstance - DLL initialization

BOOL CSIMPLEMFCCONTROLApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROLApp::ExitInstance - DLL termination

int CSIMPLEMFCCONTROLApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer()
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	//if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
	//	return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer()
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	/*if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);*/

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
