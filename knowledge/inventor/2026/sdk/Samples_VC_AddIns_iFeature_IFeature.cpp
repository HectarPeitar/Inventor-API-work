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

#include "IFeature.h"
#include "rxIFeature.h"

#include "guids.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/*-------------------------- CIFeatureApp ------------------------------------------*/

BEGIN_MESSAGE_MAP(CIFeatureApp, CWinApp)
	//{{AFX_MSG_MAP(CIFeatureApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIFeatureApp construction

CIFeatureApp::CIFeatureApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CIFeatureApp object

CIFeatureApp theApp;


// Hold this DLL's instance handle for outside access

static HINSTANCE s_hModule=NULL;

BOOL CIFeatureApp::InitInstance() 
{
	s_hModule = m_hInstance;

	return CWinApp::InitInstance();
}

/*------------------------ CIFeatureFactory -----------------------------------*/

/*
 * This class factory is used by COM to create an object of class CIFeature
 * via its CreateInstance method. The CIFeature is the object with which Autodesk Inventor (R) establishes 
 * initial contact using the IRxApplicationAddInServer interface that it MUST support.
 */

STDMETHODIMP CIFeatureFactory::CreateInstance (IUnknown* pUnkOuter, REFIID riid, void **ppv)
{
  AFX_MANAGE_STATE (AfxGetStaticModuleState());
  HRESULT Result=NOERROR;
  CRxIFeature *pIFeature=NULL;

  *ppv = NULL;

  // The semantics of this method is that the target object cannot be aggregated in.

  OnErrorState (pUnkOuter, Result, CLASS_E_NOAGGREGATION, wrapup);

  // Create the Application AddIns controller object

  pIFeature = new CRxIFeature(); 
  OnErrorState (!pIFeature, Result, E_OUTOFMEMORY, wrapup);

  // Now QI for the requested interface and return as is.
  
  Result = pIFeature->QueryInterface (riid, ppv);

wrapup:
  if (FAILED (Result) && pIFeature)
    delete pIFeature;

  return Result;
}

STDMETHODIMP CIFeatureFactory::LockServer (BOOL fLock)
{
  AFX_MANAGE_STATE (AfxGetStaticModuleState());
  if (fLock)
    IncrementDllLocks();
  else
    DecrementDllLocks();

  return NOERROR;
}

// IUnknown interface methods 
 
STDMETHODIMP CIFeatureFactory::QueryInterface (REFIID riid, LPVOID *ppv)
{
  AFX_MANAGE_STATE (AfxGetStaticModuleState());
  HRESULT Result=NOERROR;

  *ppv = NULL;

  if (IsEqualIID (riid, IID_IUnknown) || IsEqualIID (riid, IID_IClassFactory))
  {
    *ppv = (LPVOID) this;
    AddRef();
  }
  else
    Result = E_NOINTERFACE;

  return Result;
}

STDMETHODIMP_(ULONG) CIFeatureFactory::AddRef()
{
  AFX_MANAGE_STATE (AfxGetStaticModuleState());
  ++m_cRef;
  return m_cRef;
}
 
STDMETHODIMP_(ULONG) CIFeatureFactory::Release()
{
  AFX_MANAGE_STATE (AfxGetStaticModuleState());
  if(! --m_cRef)
    delete this;
  return m_cRef;
}

// Constructor(s) and destructor

CIFeatureFactory::CIFeatureFactory ()
{
  m_cRef = 0;
  ::IncrementObjectCount();
}

CIFeatureFactory::~CIFeatureFactory ()
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

STDAPI DllGetClassObject (REFCLSID rclsid, REFIID riid, LPVOID FAR* ppv)
{
  AFX_MANAGE_STATE (AfxGetStaticModuleState());
  HRESULT Result=NOERROR;

  *ppv = NULL;

  // Check for supported interfaces (only IClassFactory and IUnknown). If not supported
  // return error.

  if (!IsEqualIID (riid, IID_IUnknown) &&
      !IsEqualIID (riid, IID_IClassFactory))
    Result = E_NOINTERFACE;

  // Else, return the class factory object of the specified class and reference count it. 

  else
	{
	  if (IsEqualCLSID (rclsid, CLSID_IFeature))
	  {
      *ppv = new CIFeatureFactory;
		  if (!*ppv)
		    return E_OUTOFMEMORY;
    }

    if (*ppv)
		  (reinterpret_cast<IUnknown *> (*ppv))->AddRef();
	  else
		  Result = E_FAIL;
	}												    

  return Result;
}


/*
 * This exported function simply returns an S_FALSE or an S_OK, depending on whether 
 * the DLL is currently being used (a client is using an object of this DLL) or not. 
 * This is known by looking up the reference count on the objects created in here 
 * and not yet released.
 */

STDAPI DllCanUnloadNow ()
{
  AFX_MANAGE_STATE (AfxGetStaticModuleState());
  return (ObjectCount() || DllLocks() ? S_FALSE : S_OK);
}


/*
 * This exported function registers this DLL as the in-proc server against the appropriate
 * CLSID. It performs all other registration tasks as well, such as registering the CATIDs
 * which allows Autodesk Inventor (R) to find this as a legitimate AddIn to load up into its process.
 */

#define SOFTWARE_VERSION_SUPPORTED _T("14..")

#define DLLNAME_VALUE (TCHAR*)-1
const TCHAR *g_RegTable[][3] = 
{
  // Format is: { Key, Value name, Value }
  { _T("Software\\Classes\\CLSID\\{") CLSID_IFeature_RegGUID _T("}"), 0, CLSID_IFeature_Name },
  { _T("Software\\Classes\\CLSID\\{") CLSID_IFeature_RegGUID _T("}\\Description"), 0, CLSID_IFeature_Descr },
  { _T("Software\\Classes\\CLSID\\{") CLSID_IFeature_RegGUID _T("}\\Implemented Categories"), 0, _T("Server has implemented these") },
  { _T("Software\\Classes\\CLSID\\{") CLSID_IFeature_RegGUID _T("}\\InprocServer32"), 0, DLLNAME_VALUE },
  { _T("Software\\Classes\\CLSID\\{") CLSID_IFeature_RegGUID _T("}\\InprocServer32"), _T("ThreadingModel"), _T("Apartment") },
  { _T("Software\\Classes\\CLSID\\{") CLSID_IFeature_RegGUID _T("}\\Settings"), 0, _T("Programmatically Configurable") },
  { _T("Software\\Classes\\CLSID\\{") CLSID_IFeature_RegGUID _T("}\\Settings"), _T("LoadOnStartUp"), _T("1") },
  { _T("Software\\Classes\\CLSID\\{") CLSID_IFeature_RegGUID _T("}\\Settings"), _T("Type"), _T("Standard") },
  { _T("Software\\Classes\\CLSID\\{") CLSID_IFeature_RegGUID _T("}\\Settings"), _T("SupportedSoftwareVersionGreaterThan"), SOFTWARE_VERSION_SUPPORTED },
  { _T("Software\\Classes\\CLSID\\{") CLSID_IFeature_RegGUID  _T("}\\Settings"), _T("Version"), _T("1")},  
};

STDAPI DllRegisterServer()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// First register the DLL/CLSID based entries

	// Obtain the full path of this DLL via its instance handle.

	TCHAR szDllFileName[MAX_PATH];
	DWORD res = GetModuleFileName(s_hModule, szDllFileName, MAX_PATH);
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


	// Now Register the CATIDs

	if (SUCCEEDED(hr))
	{
		CComPtr<ICatRegister> pCatReg;
		hr = pCatReg.CoCreateInstance(CLSID_StdComponentCategoriesMgr);
		if (SUCCEEDED(hr) && pCatReg)
		{
			CATID ImplCATID = CATID_InventorVersionedApplicationAddIn;

			// Use the following catid if you wish to support versions of Inventor
			// prior to addin version control.
			//
			//CATID ImplCATID = CATID_InventorApplicationAddIn;

			hr = pCatReg->RegisterClassImplCategories(CLSID_IFeature, 1, &ImplCATID);
		}
	}

	if (FAILED(hr))
	{
		DllUnregisterServer();
		return SELFREG_E_CLASS;
	}
	return S_OK;
}



STDAPI DllUnregisterServer ()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// First UnRegister the CATIDs

	CComPtr<ICatRegister> pCatReg;
	HRESULT hr = pCatReg.CoCreateInstance(CLSID_StdComponentCategoriesMgr);
	if (SUCCEEDED(hr) && pCatReg)
	{
		CATID ImplCATID = CATID_InventorVersionedApplicationAddIn;

		// Use the following catid if you wish to support versions of Inventor
		// prior to addin version control.
		//
		//CATID ImplCATID = CATID_InventorApplicationAddIn;

		if (FAILED(pCatReg->UnRegisterClassImplCategories(CLSID_IFeature, 1, &ImplCATID)))
			hr = E_FAIL;
	}

	// Now Unregister DLL/CLSID entries
	int nEntries = sizeof(g_RegTable) / sizeof(*g_RegTable);
	for (int i = nEntries - 1;i >= 0;--i)
	{
		const TCHAR* pszKeyName = g_RegTable[i][0];

		// Remove the Key
		LONG res = RegDeleteKey(HKEY_CURRENT_USER, pszKeyName);
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

void IncrementObjectCount ()
{
  nObjects++;
}

void DecrementObjectCount ()
{
  nObjects--;
}

ULONG ObjectCount ()
{
  return nObjects;
}

void IncrementDllLocks ()
{
  nDllLocks++;
}

void DecrementDllLocks ()
{
  nDllLocks--;
}

ULONG DllLocks ()
{
  return nDllLocks;
}

