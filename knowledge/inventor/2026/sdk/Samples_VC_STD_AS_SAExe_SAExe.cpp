/*
  DESCRIPTION

  Given the ProgID of the Apprentice Server, create one in-process
  and open a file and print some statistics from it.

*/

#include <stdio.h>
#include <comutil.h>
#include <atlbase.h>
#include <string.h>

#define OnErrorReturn(badsts, errocode) \
  if (badsts) return errocode;

#define OnError(badsts,label) if(badsts) goto label;

#pragma warning(disable:4192) // Automatic exclusion of system defined symbols
#pragma warning(disable : 4278) // 'name':identifier in type library 'library' is already a macro

#include "InventorUtils.h"

// Forward declarations
HRESULT GetApprenticeInformation();

// Main. Note that all COM related activity (including the automatic 'release' within smart
// pointers) MUST take place BEFORE CoUnitialize(). Hence the function 'block' within which
// the smart-pointers construct and destruct (and AddRef and Release) keeping the CoUnitialize
// safely out of the way.

int _tmain(int argc, _TCHAR* argv[])
{
	HRESULT Result=NOERROR;

	Result = ::CoInitialize (NULL);
	OnError (FAILED (Result), wrapup);

	Result = GetApprenticeInformation();
	OnError(FAILED (Result), wrapup);

	// we are done. call conunitialize
wrapup:
	::CoUninitialize(); 
	return 0;
}

HRESULT GetApprenticeInformation()
{
	HRESULT Result=NOERROR;
	bool bTerminate=false;
	CLSID ServerClsid;
	
	// Create an in-process instance of the Server
	Result = ::CLSIDFromProgID (L"Inventor.ApprenticeServer", &ServerClsid);
	OnErrorReturn(FAILED (Result), Result);

	CComPtr<ApprenticeServer> pServer;
	Result = pServer.CoCreateInstance(ServerClsid);
	OnErrorReturn(FAILED (Result), Result);

	ATLASSERT(pServer);

	TCHAR Str[MAX_PATH];
	while (!bTerminate)
	{
		// Open an Inventor Document (obtain its File And References interface)
		long nMajor, nMinor;
		
		_tprintf_s(L"Inventor file to be loaded: ");

		// clear the input buffer before calling _getts_s().
		fflush( stdin );
		_getts_s(Str);
		CComBSTR sFileName(Str);
    
		CComPtr<ApprenticeServerDocument> pDoc;
	    Result = pServer->Open(sFileName, &pDoc);
		OnErrorReturn (FAILED (Result), Result);
    
	    // Print Display Name, and File versions
		CComBSTR rawbstrStr;
		Result = pDoc->get_DisplayName(&rawbstrStr);
		OnErrorReturn(FAILED (Result), Result);

		sFileName = rawbstrStr;
		
		_tprintf_s(L"Display Name: %s\n", sFileName);

		CComPtr<SoftwareVersion> pSoftwareVersionCreated;
		Result = pDoc->get_SoftwareVersionCreated(&pSoftwareVersionCreated);
		OnErrorReturn(FAILED (Result), Result);

		Result = pSoftwareVersionCreated->get_Major(&nMajor);
		OnErrorReturn (FAILED (Result), Result);

		Result = pSoftwareVersionCreated->get_Minor(&nMinor);
		OnErrorReturn (FAILED (Result), Result);

		_tprintf_s(L"Created in Version: Major=%d, Minor=%d\n", nMajor, nMinor);

		CComPtr<SoftwareVersion> pSoftwareVersionSaved;
		Result = pDoc->get_SoftwareVersionSaved(&pSoftwareVersionSaved);
		OnErrorReturn(FAILED (Result), Result);

		Result = pSoftwareVersionSaved->get_Major (&nMajor);
		OnErrorReturn(FAILED (Result), Result);

		Result = pSoftwareVersionSaved->get_Minor (&nMinor);
		OnErrorReturn(FAILED (Result), Result);

		_tprintf_s(L"Last Saved with Version: Major=%d, Minor=%d\n", nMajor, nMinor);

		// Close the Document
		Result = pServer->Close();
		OnErrorReturn(FAILED (Result), Result);

		// Want to continue?
		_tprintf_s(L"Continue (y/n) ?: ");
		_tscanf_s(L"%s", Str, MAX_PATH);
		if(toupper(Str[0]) == 'N')
			bTerminate = true;

	}

	return Result;
}

