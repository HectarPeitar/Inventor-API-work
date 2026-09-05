// SimpleExe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Forward declarations
static HRESULT GetInventorInformation();

// Main. Note that all COM related activity (including the automatic 'release' within smart
// pointers) MUST take place BEFORE CoUnitialize(). Hence the function 'block' within which
// the smart-pointers construct and destruct (and AddRef and Release) keeping the CoUnitialize
// safely out of the way.

int _tmain(int argc, _TCHAR* argv[])
{
	HRESULT Result = NOERROR;
  
	Result = CoInitialize (NULL);

	if (SUCCEEDED(Result))
		Result = GetInventorInformation();

	CoUninitialize(); 

	return 0;
}

static HRESULT GetInventorInformation()
{
	HRESULT Result = NOERROR;

	TCHAR Str[_MAX_PATH];
	
	CLSID InvAppClsid;
	Result = CLSIDFromProgID (L"Inventor.Application", &InvAppClsid);
	if (FAILED(Result)) return Result;

	// Either create a new instance of the application or latch on to the currently active one.
	_tprintf_s (_T("Would you like to create a new Inventor application? (y/n) _: "));
	_tscanf_s (_T("%ls"), Str, _MAX_PATH);

	CComPtr<IUnknown> pInvAppUnk;
	if (toupper (Str[0]) == _T('Y'))
	{
		Result = CoCreateInstance (InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void **) &pInvAppUnk);
		if (FAILED (Result))
			_tprintf_s (_T("*** Failed to create a new Inventor application ***\n"));
	}
	else
	{ 
		Result = ::GetActiveObject (InvAppClsid, NULL, &pInvAppUnk);
		if (FAILED (Result))
			_tprintf_s (_T("*** Could not get hold of an active Inventor application ***\n"));
	}
	if (FAILED(Result)) return Result;

	CComPtr<Application> pInvApp;
	Result = pInvAppUnk->QueryInterface (__uuidof(Application), (void **) &pInvApp);
	if (FAILED(Result)) return Result;

	// Display some information about Inventor
	_tprintf_s(_T("\nInventor Information: \n"));

	CComBSTR bstrCaption;
	Result = pInvApp->get_Caption(&bstrCaption);
	if (SUCCEEDED(Result))
		_tprintf_s(_T("Caption: %ls \n"), bstrCaption);

	CComBSTR bstrLanguage;
	Result = pInvApp->get_LanguageName(&bstrLanguage);
	if (SUCCEEDED(Result))
		_tprintf_s(_T("Language: %ls \n"), bstrLanguage);

	CComBSTR bstrUserName;
	Result = pInvApp->get_UserName(&bstrUserName);
	if (SUCCEEDED(Result))
		_tprintf_s(_T("User Name: %ls \n"), bstrUserName);

	CComPtr<SoftwareVersion> pSoftwareVersion;
	Result =  pInvApp->get_SoftwareVersion(&pSoftwareVersion);
	if (SUCCEEDED(Result))
	{
		CComBSTR bstrSoftVerDispName;
		Result = pSoftwareVersion->get_DisplayName(&bstrSoftVerDispName);
		if (SUCCEEDED(Result))
			_tprintf_s(_T("Software Version: %ls \n"), bstrSoftVerDispName);
	}

	CComPtr<FileLocations> pFileLocations;
	Result =  pInvApp->get_FileLocations(&pFileLocations);
	if (SUCCEEDED(Result))
	{
		CComBSTR bstrFileLocationsFile;
		Result = pFileLocations->get_FileLocationsFile(&bstrFileLocationsFile);
		if (SUCCEEDED(Result))
			_tprintf_s(_T("Active Project File: %ls \n"), bstrFileLocationsFile);
	}

	CComPtr<GeneralOptions> pGeneralOptions;
	Result =  pInvApp->get_GeneralOptions(&pGeneralOptions);
	if (SUCCEEDED(Result))
	{
		CComBSTR bstrStartupProjectFile;
		Result = pGeneralOptions->get_StartupProjectFileName(&bstrStartupProjectFile);
		if (SUCCEEDED(Result))
			_tprintf_s(_T("Startup Project File: %ls \n\n"), bstrStartupProjectFile);
	}

	VARIANT_BOOL bVisible = VARIANT_FALSE;
	bool bDone = false;
	while (!bDone)
	{
		// Obtain the 'Visible' property of the active application
		VARIANT_BOOL bVisible;
		Result = pInvApp->get_Visible(&bVisible);
		if (FAILED(Result)) return Result;
	  
		if (bVisible != VARIANT_FALSE)
			_tcscpy_s (Str, _T("Visible"));
		else
			_tcscpy_s (Str, _T("Invisible"));

		_tprintf_s(_T("Active Inventor application is %s\nWould you like to toggle this? _: "), Str);
		_tscanf_s (_T("%ls"), Str, _MAX_PATH);	  
	  
		// Toggle the 'Visible' property of this application
		if (toupper (Str[0]) == _T('Y'))
			pInvApp->Visible = bVisible ? FALSE : TRUE;
		else
			bDone = TRUE;
	}

	return Result;
}

