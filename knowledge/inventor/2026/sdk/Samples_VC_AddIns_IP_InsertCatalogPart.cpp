/*
	DESCRIPTION

	The intention with this sample is more to illustrate the concepts and provide a working example.
	It does not necessarily use all of the latest technology and other boiler-plate, error-handling,
	thread-safe code that you might want to use. So, treat this more as an advanced  starting point.

	This file contains the functions that deal with the DLL as a whole. Some of them are exported
	to the external world and others are used to keep track of the state of the DLL as far is it's
	usage is concerned.


	BRIEF EXPLANATION

	More importantly, this file contains the one function that becomes the single entry point for a
	client (Autodesk Inventor (R)) to use in order to get at the functionality encapsulated inside. The immediate client,
	in most cases, is the intermediary -- COM runtime library, acting on behalf of the Client
	which usually is the caller of the CoCreateInstance function. The function is the DllGetClassObject.
	Via the DllGetClassObject, the clients get hold of the various class factories that in turn create
	the actual objects of interest -- in this DLL.

	Another exported function is the DllCanUnloadNow. This function is called by the system periodically,
	to check if the memory resource being used for the DLL can be freed if none of the parts of the DLL
	are currently in use.

	Other functions are for internal book-keeping, serving to give the correct answer when
	the question is asked whether the DLL can unload. These are not exported. The various COM objects
	supported in here, use these functions to keep up the count of objects that are currently in use
	by clients. A ref-counter on the DLL itself is provided. This is mainly used by the
	IClassFactory::LockServer method, probably called by the COM Runtime.

	The registration of this DLL takes place via the DllRegisterServer/DllUnRegisterServer functions
	invoked by the installer.

*/

#include "stdafx.h"

#include "insertcatalogpart.h"
#include "rxinsertcatalogpart.h"

#include "guids.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/*-------------------------- CInsertCatalogPartApp ------------------------------------------*/

BEGIN_MESSAGE_MAP(CInsertCatalogPartApp, CWinApp)
	//{{AFX_MSG_MAP(CInsertCatalogPartApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsertCatalogPartApp construction

CInsertCatalogPartApp::CInsertCatalogPartApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CInsertCatalogPartApp object

CInsertCatalogPartApp theApp;


// Hold this DLL's instance handle for outside access

static HINSTANCE s_hModule = NULL;

BOOL CInsertCatalogPartApp::InitInstance()
{
	s_hModule = m_hInstance;
	return CWinApp::InitInstance();
}

/*------------------------ CInsertCatalogPartFactory -----------------------------------*/

/*
 * This class factory is used by COM to create an object of class CInsertCatalogPart
 * via its CreateInstance method. The CInsertCatalogPart is the object with which Autodesk Inventor (R) establishes
 * initial contact using the IRxApplicationAddInServer interface that it MUST support.
 */

STDMETHODIMP CInsertCatalogPartFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	OnErrorReturn(!ppv, E_INVALIDARG);
	*ppv = NULL;

	// The semantics of this method is that the target object cannot be aggregated in.

	OnErrorReturn(pUnkOuter, CLASS_E_NOAGGREGATION);

	// Create the Application AddIns controller object

	CRxInsertCatalogPart* pInsertCatalogPart = new CRxInsertCatalogPart();
	OnErrorReturn(!pInsertCatalogPart, E_OUTOFMEMORY);

	// Now QI for the requested interface and return as is.

	HRESULT hr = pInsertCatalogPart->QueryInterface(riid, ppv);
	if (FAILED(hr))
		delete pInsertCatalogPart;
	return hr;
}

STDMETHODIMP CInsertCatalogPartFactory::LockServer(BOOL fLock)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (fLock)
		IncrementDllLocks();
	else
		DecrementDllLocks();

	return S_OK;
}

// IUnknown interface methods
STDMETHODIMP CInsertCatalogPartFactory::QueryInterface(REFIID riid, void** ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	OnErrorReturn(!ppv, E_INVALIDARG);
	*ppv = NULL;

	if (IsEqualIID(riid, IID_IUnknown) ||
	    IsEqualIID(riid, IID_IClassFactory))
		*ppv = static_cast<IClassFactory*>(this);

	if (*ppv)
		static_cast<IUnknown*>(*ppv)->AddRef();

	return *ppv ? S_OK : E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) CInsertCatalogPartFactory::AddRef()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return ++m_cRef;
}

STDMETHODIMP_(ULONG) CInsertCatalogPartFactory::Release()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	ULONG cRef = --m_cRef;
	if(!m_cRef)
		delete this;
	return cRef;
}

// Constructor(s) and destructor
CInsertCatalogPartFactory::CInsertCatalogPartFactory()
{
	m_cRef = 0;
	::IncrementObjectCount();
}

CInsertCatalogPartFactory::~CInsertCatalogPartFactory()
{
	::DecrementObjectCount();
}

/*------------------------------- DLL Exported functions ----------------------------------------*/

/*
 * This function returns the class-factory object that would in turn create objects of the
 * specified class ('rClsid', registered in the system's registry at install time, identifies
 * the COM-object). The interface that the caller (quite often the COM API --
 * CoCreateInstance) is looking for on this object, is specified in 'riid'. The class factory
 * must support IClassFactory and of course, IUnknown.
 */

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	OnErrorReturn(!ppv, E_INVALIDARG);
	*ppv = NULL;

	// Ckeck for supported classid.
	//
	OnErrorReturn(!IsEqualCLSID(rclsid, CLSID_InsertCatalogPart), E_INVALIDARG);

	// Check for supported interfaces (only IClassFactory and IUnknown). If not supported
	// return error.
	//
	OnErrorReturn(!IsEqualIID(riid, IID_IUnknown) &&
		!IsEqualIID(riid, IID_IClassFactory), E_NOINTERFACE);

	// Else, return the class factory object and reference count it.

	*ppv = static_cast<IClassFactory*>(new CInsertCatalogPartFactory());
	OnErrorReturn(!*ppv, E_OUTOFMEMORY);


	static_cast<IUnknown*>(*ppv)->AddRef();

	return S_OK;
}

/*
 * This exported function simply returns an S_FALSE or an S_OK, depending on whether
 * the DLL is currently being used (a client is using an object of this DLL) or not.
 * This is known by looking up the reference count on the objects created in here
 * and not yet released.
 */

STDAPI DllCanUnloadNow()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());
	return ObjectCount() || DllLocks() ? S_FALSE : S_OK;
}

/*
 * This exported function registers this DLL as the in-proc server against the appropriate
 * CLSID. It performs all other registration tasks as well, such as registering the CATIDs
 * which allows Autodesk Inventor (R) to find this as a legitimate AddIn to load up into its process.
 */
#define SOFTWARE_VERSION_SUPPORTED _T("14..")

#define DLLNAME_VALUE (TCHAR*) - 1
const TCHAR* g_RegTable[][3] =
{
	// Format is: { Key, Value name, Value }
	{ _T("Software\\Classes\\CLSID\\{") CLSID_InsertCatalogPart_RegGUID _T("}"), 0, CLSID_InsertCatalogPart_Name },
	{ _T("Software\\Classes\\CLSID\\{") CLSID_InsertCatalogPart_RegGUID _T("}\\Description"), 0, CLSID_InsertCatalogPart_Descr },
	{ _T("Software\\Classes\\CLSID\\{") CLSID_InsertCatalogPart_RegGUID _T("}\\Implemented Categories"), 0, _T("Server has implemented these") },
	{ _T("Software\\Classes\\CLSID\\{") CLSID_InsertCatalogPart_RegGUID _T("}\\InprocServer32"), 0, DLLNAME_VALUE },
	{ _T("Software\\Classes\\CLSID\\{") CLSID_InsertCatalogPart_RegGUID _T("}\\InprocServer32"), _T("ThreadingModel"), _T("Apartment") },
	{ _T("Software\\Classes\\CLSID\\{") CLSID_InsertCatalogPart_RegGUID _T("}\\Settings"), 0, _T("Programmatically Configurable") },
	{ _T("Software\\Classes\\CLSID\\{") CLSID_InsertCatalogPart_RegGUID _T("}\\Settings"), _T("LoadOnStartUp"), _T("1") },
	{ _T("Software\\Classes\\CLSID\\{") CLSID_InsertCatalogPart_RegGUID _T("}\\Settings"), _T("Type"), _T("Standard") },
	{ _T("Software\\Classes\\CLSID\\{") CLSID_InsertCatalogPart_RegGUID _T("}\\Settings"), _T("SupportedSoftwareVersionGreaterThan"), SOFTWARE_VERSION_SUPPORTED },
	{ _T("Software\\Classes\\CLSID\\{") CLSID_InsertCatalogPart_RegGUID  _T("}\\Settings"), _T("Version"), _T("1")},
};

STDAPI DllRegisterServer()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	// First register the DLL/CLSID based entries

	// Obtain the full path of this DLL via its instance handle.

	TCHAR szDllFileName[MAX_PATH];
	DWORD res = GetModuleFileName (s_hModule, szDllFileName, MAX_PATH);
	OnErrorReturn(!res, E_UNEXPECTED);

	// Process each entry. Keep track of the current DLL being registered in szDllFileName.
	// This is the most recent DLLNAME_TO_FOLLOW that has been read in.

	int nEntries = sizeof(g_RegTable) / sizeof(*g_RegTable);
	HRESULT hr = S_OK;
	for (int i = 0;SUCCEEDED(hr) && i < nEntries;++i)
	{
		// Manipulate pieces of the strings as needed
		const TCHAR* pszKeyName = g_RegTable[i][0];
		const TCHAR* pszValueName = g_RegTable[i][1];
		const TCHAR* pszValue = g_RegTable[i][2];

		// Now substitute in the rogue value in the "Value" field.
		if (pszValue == DLLNAME_VALUE)
			pszValue = szDllFileName;

		// Create the Key and set the Value
		HKEY hKey;
		res = RegCreateKey(HKEY_CURRENT_USER, pszKeyName, &hKey);
		if (res == ERROR_SUCCESS)
		{
			if (0 == wcscmp(pszValueName, _T("Version")))
			{
				DWORD dwValue = _tcstol(pszValue, NULL, 10);
				res = RegSetValueEx(hKey, pszValueName, 0, REG_DWORD, reinterpret_cast<const BYTE*>(&dwValue), static_cast<DWORD>(sizeof(TCHAR) * (_tcslen(pszValue) + 1)));
			}
			else
				res = RegSetValueEx(hKey, pszValueName, 0, REG_SZ, reinterpret_cast<const BYTE*>(pszValue), static_cast<DWORD>(sizeof(TCHAR) * (_tcslen(pszValue) + 1)));

			RegCloseKey(hKey);
		}
		if (res != ERROR_SUCCESS)
			hr = E_FAIL;
	}

	if (SUCCEEDED(hr))
	{
		// Now Register the CATIDs
		CComPtr<ICatRegister> pCatReg;
		hr = pCatReg.CoCreateInstance(CLSID_StdComponentCategoriesMgr);
		if (SUCCEEDED(hr))
		{
			CATID ImplCATID = CATID_InventorVersionedApplicationAddIn;

			// Use the following catid if you wish to support versions of Autodesk Inventor (R)
			// prior to addin version control.
			//
			//CATID ImplCATID = CATID_InventorApplicationAddIn;

			hr = pCatReg->RegisterClassImplCategories(CLSID_InsertCatalogPart, 1, &ImplCATID);
		}
	}

	if (FAILED(hr))
	{
		DllUnregisterServer();
		hr = SELFREG_E_CLASS;
	}
	return hr;
}

STDAPI DllUnregisterServer()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// First UnRegister the CATIDs

	CComPtr<ICatRegister> pCatReg;
	HRESULT hr = pCatReg.CoCreateInstance(CLSID_StdComponentCategoriesMgr);
	if (SUCCEEDED(hr))
	{
		CATID ImplCATID = CATID_InventorVersionedApplicationAddIn;

		// Use the following catid if you wish to support versions of Autodesk Inventor (R)
		// prior to addin version control.
		//
		//CATID ImplCATID = CATID_InventorApplicationAddIn;

		if (FAILED(pCatReg->UnRegisterClassImplCategories (CLSID_InsertCatalogPart, 1, &ImplCATID)))
			hr = E_FAIL;
	}

	// Now Unregister DLL/CLSID entries

	int nEntries = sizeof(g_RegTable) / sizeof(*g_RegTable);
	for (int i = nEntries - 1;i >= 0;--i)
	{
		const TCHAR* pszKeyName = g_RegTable[i][0];

		// Remove the Key
		DWORD res = RegDeleteKey(HKEY_CURRENT_USER, pszKeyName);
		if (res != ERROR_SUCCESS)
			hr = E_FAIL;
	}

	if (FAILED(hr))
		hr = S_FALSE;
	return hr;
}

/*----------------------- DLL internal functions that manage the DLL --------------------------------------*/

/*
 * Variable keeping a count of the number of objects in use. C++ initialized to 0!
 * Below are the functions that update or read this number.
 */

static ULONG nObjects;
static ULONG nDllLocks;

void IncrementObjectCount()
{
	++nObjects;
}

void DecrementObjectCount()
{
	--nObjects;
}

ULONG ObjectCount()
{
	return nObjects;
}

void IncrementDllLocks()
{
	++nDllLocks;
}

void DecrementDllLocks()
{
	--nDllLocks;
}

ULONG DllLocks()
{
	return nDllLocks;
}
