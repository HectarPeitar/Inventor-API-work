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

#include "IPart.h"
#include "rxIPart.h"

#include "guids.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/*-------------------------- CIPartApp ------------------------------------------*/

BEGIN_MESSAGE_MAP(CIPartApp, CWinApp)
	//{{AFX_MSG_MAP(CIPartApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPartApp construction

CIPartApp::CIPartApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CIPartApp object

CIPartApp theApp;


// Hold this DLL's instance handle for outside access

static HINSTANCE s_hModule=NULL;

BOOL CIPartApp::InitInstance() 
{
  s_hModule = m_hInstance;	
	return CWinApp::InitInstance();
}

/*------------------------ CIPartFactory -----------------------------------*/

/*
 * This class factory is used by COM to create an object of class CIPart
 * via its CreateInstance method. The CIPart is the object with which Autodesk Inventor (R) establishes 
 * initial contact using the IRxApplicationAddInServer interface that it MUST support.
 */

STDMETHODIMP CIPartFactory::CreateInstance (IUnknown* pUnkOuter, REFIID riid, void **ppv)
{
  AFX_MANAGE_STATE (AfxGetStaticModuleState());
  HRESULT Result=NOERROR;
  CRxIPart *pIPart=NULL;

  *ppv = NULL;

  // The semantics of this method is that the target object cannot be aggregated in.

  OnErrorState (pUnkOuter, Result, CLASS_E_NOAGGREGATION, wrapup);

  // Create the Application AddIns controller object

  pIPart = new CRxIPart(); 
  OnErrorState (!pIPart, Result, E_OUTOFMEMORY, wrapup);

  // Now QI for the requested interface and return as is.
  
  Result = pIPart->QueryInterface (riid, ppv);

wrapup:
  if (FAILED (Result) && pIPart)
    delete pIPart;

  return Result;
}

STDMETHODIMP CIPartFactory::LockServer (BOOL fLock)
{
  AFX_MANAGE_STATE (AfxGetStaticModuleState());
  if (fLock)
    IncrementDllLocks();
  else
    DecrementDllLocks();

  return NOERROR;
}

// IUnknown interface methods 
 
STDMETHODIMP CIPartFactory::QueryInterface (REFIID riid, LPVOID *ppv)
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

STDMETHODIMP_(ULONG) CIPartFactory::AddRef()
{
  AFX_MANAGE_STATE (AfxGetStaticModuleState());
  ++m_cRef;
  return m_cRef;
}
 
STDMETHODIMP_(ULONG) CIPartFactory::Release()
{
  AFX_MANAGE_STATE (AfxGetStaticModuleState());
  if(! --m_cRef)
    delete this;
  return m_cRef;
}

// Constructor(s) and destructor

CIPartFactory::CIPartFactory ()
{
  m_cRef = 0;
  ::IncrementObjectCount();
}

CIPartFactory::~CIPartFactory ()
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
	  if (IsEqualCLSID (rclsid, CLSID_IPart))
	  {
      *ppv = new CIPartFactory;
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
  { _T("Software\\Classes\\CLSID\\{") CLSID_IPart_RegGUID _T("}"), 0, CLSID_IPart_Name },
  { _T("Software\\Classes\\CLSID\\{") CLSID_IPart_RegGUID _T("}\\Description"), 0, CLSID_IPart_Descr },
  { _T("Software\\Classes\\CLSID\\{") CLSID_IPart_RegGUID _T("}\\Implemented Categories"), 0, _T("Server has implemented these") },
  { _T("Software\\Classes\\CLSID\\{") CLSID_IPart_RegGUID _T("}\\InprocServer32"), 0, DLLNAME_VALUE },
  { _T("Software\\Classes\\CLSID\\{") CLSID_IPart_RegGUID _T("}\\InprocServer32"), _T("ThreadingModel"), _T("Apartment") },
  { _T("Software\\Classes\\CLSID\\{") CLSID_IPart_RegGUID _T("}\\Settings"), 0, _T("Programmatically Configurable") },
  { _T("Software\\Classes\\CLSID\\{") CLSID_IPart_RegGUID _T("}\\Settings"), _T("LoadOnStartUp"), _T("1") },
  { _T("Software\\Classes\\CLSID\\{") CLSID_IPart_RegGUID _T("}\\Settings"), _T("Type"), _T("Standard") },
  { _T("Software\\Classes\\CLSID\\{") CLSID_IPart_RegGUID _T("}\\Settings"), _T("SupportedSoftwareVersionGreaterThan"), SOFTWARE_VERSION_SUPPORTED },
  { _T("Software\\Classes\\CLSID\\{") CLSID_IPart_RegGUID  _T("}\\Settings"), _T("Version"), _T("1")},
};

STDAPI DllRegisterServer()
{
  AFX_MANAGE_STATE (AfxGetStaticModuleState());
  HRESULT Result=NOERROR;
  bool bDllExists=false;
  int i=0, nEntries=0;
  DWORD Status=TRUE;
  TCHAR szDllFileName[MAX_PATH];
  TCHAR *pDir=NULL;
  HKEY hKey;
  CATID ImplCATID=CATID_InventorVersionedApplicationAddIn;
  CComPtr<ICatRegister> pCatReg;

  // First register the DLL/CLSID based entries

  // Obtain the full path of this DLL via its instance handle.

  Status = GetModuleFileName (s_hModule, szDllFileName, MAX_PATH);
  OnErrorReturn(!Status, E_UNEXPECTED);

  // Process each entry. Keep track of the current DLL being registered in szDllFileName.
  // This is the most recent DLLNAME_TO_FOLLOW that has been read in.
   
  nEntries = sizeof (g_RegTable) / sizeof (*g_RegTable);
  for (i=0; i<nEntries; i++)
  {
    // Manipulate pieces of the strings as needed

    const TCHAR *pszKeyName = g_RegTable[i][0];
    const TCHAR *pszValueName = g_RegTable[i][1];
    const TCHAR *pszValue = g_RegTable[i][2];

    // Now substitute in the rogue value in the "Value" field.

    if (pszValue == DLLNAME_VALUE)
      pszValue = szDllFileName;
  
   // Create the Key and set the Value
	Status = RegCreateKey(HKEY_CURRENT_USER, pszKeyName, &hKey);
	if (Status == ERROR_SUCCESS)
	{
		if (0 == wcscmp(pszValueName, _T("Version")))
		{
			DWORD VersionValue = _tcstol(pszValue, NULL, 10);
			Status = RegSetValueEx(hKey, pszValueName, 0, REG_DWORD, reinterpret_cast<const BYTE*>(&VersionValue), static_cast<DWORD>(sizeof(TCHAR) * (_tcslen(pszValue) + 1)));
		}
		else
			Status = RegSetValueEx(hKey, pszValueName, 0, REG_SZ, reinterpret_cast<const BYTE*>(pszValue), static_cast<DWORD>(sizeof(TCHAR) * (_tcslen(pszValue) + 1)));

		RegCloseKey(hKey);
	}
	if (Status != ERROR_SUCCESS)
		Result = E_FAIL;
  }

  if (SUCCEEDED(Result))
	{
		// Now Register the CATIDs
		Result = pCatReg.CoCreateInstance(CLSID_StdComponentCategoriesMgr);
		if (SUCCEEDED(Result))
		{
			Result = pCatReg->RegisterClassImplCategories(CLSID_IPart, 1, &ImplCATID);
		}
	}

	if (FAILED(Result))
	{
		DllUnregisterServer();
		Result = SELFREG_E_CLASS;
	}
	return Result;

}



STDAPI DllUnregisterServer ()
{
  AFX_MANAGE_STATE (AfxGetStaticModuleState());
  HRESULT Result=NOERROR;
  int i=0, nEntries=0;
  CATID ImplCATID=CATID_InventorVersionedApplicationAddIn;
  CComPtr<ICatRegister> pCatReg;

  // First UnRegister the CATIDs
  
  Result = pCatReg.CoCreateInstance(CLSID_StdComponentCategoriesMgr);
  if (SUCCEEDED(Result))
	{
		if (FAILED(pCatReg->UnRegisterClassImplCategories (CLSID_IPart, 1, &ImplCATID)))
			Result = E_FAIL;
	}

	// Now Unregister DLL/CLSID entries

	nEntries = sizeof(g_RegTable) / sizeof(*g_RegTable);
	for (i = nEntries - 1;i >= 0;--i)
	{
		const TCHAR* pszKeyName = g_RegTable[i][0];

		// Remove the Key
		DWORD res = RegDeleteKey(HKEY_CURRENT_USER, pszKeyName);
		if (res != ERROR_SUCCESS)
			Result = E_FAIL;
	}

	if (FAILED(Result))
		Result = S_FALSE;
	return Result;
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

