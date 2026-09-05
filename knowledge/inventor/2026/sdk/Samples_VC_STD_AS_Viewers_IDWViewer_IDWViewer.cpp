// IDWViewer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "IDWViewer.h"

#include "MainFrm.h"
#include "IpFrame.h"
#include "IDWViewerDoc.h"
#include "IDWxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




InventorLocation InventorLocation::g_Location;

typedef HKEY MHKEY;
typedef MHKEY* MPHKEY;

#define INVENTOR_EXE _T("INVENTOR.exe")
#define DWFVIEWCTR_EXE _T("IDWViewer.exe")
#define INVENTORIDW_EXT _T("Software\\Classes\\.IDW")
#define INVENTORIDW_PROGID _T("Inventor.DrawingDocument")
#define KEY_CLSID _T("Software\\Classes\\CLSID")
#define KEY_PARTCLSID _T("{4D29B490-49B2-11D0-93C3-7E0706000000}")
#define KEY_INVENTORCLSID _T("{8E75D913-3D21-11d2-85C4-080009A0C626}")
#define KEY_INVENTORCLSID_UNICODE _T("{8E75D913-3D21-11d2-85C4-080009A0C626}")
#define KEY_LocalServer32 _T("LocalServer32")
#define wcharNul _T('\0')


static void RegisterIDWExtension()
{
  HRESULT hr = E_FAIL;
  MHKEY rootKey = HKEY_CURRENT_USER;
  HKEY hIDWExtensionKey = NULL;
  DWORD dw     = 0;
  
  // Create the key if it does not find it
  if (RegCreateKeyEx(rootKey, INVENTORIDW_EXT, 0, REG_NONE, 
    REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, 
    NULL,static_cast<HKEY*>(&hIDWExtensionKey), &dw) == ERROR_SUCCESS)
  {
    DWORD valueSize = _MAX_PATH;
    DWORD dwType    = 0;
    TCHAR szEntry[_MAX_PATH];
    // get the value
    LONG dwStatus = RegQueryValueEx(hIDWExtensionKey, (LPCTSTR) _T(""), NULL,
      &dwType, (LPBYTE) szEntry, &valueSize);
    bool bFound = false;
    if (dwStatus == ERROR_SUCCESS) 
    {
      // make sure value is a string
      if(dwType == REG_SZ)
      { 
        // The string must be INVENTORIDW_PROGID else OLE will not find this server 
        // And consequently linking of MDT parts will not work 
        bFound = (_tcscmp(szEntry,INVENTORIDW_PROGID) == 0);
      }
    }
    if(!bFound)
    {
      DWORD cbData = _tcslen(INVENTORIDW_PROGID);
      // make the entry
      if(RegSetValueEx(hIDWExtensionKey,           // handle to key
        (LPCTSTR) _T(""), // value name
        0,      // reserved
        REG_SZ,        // value type
        (CONST BYTE *)INVENTORIDW_PROGID,  cbData) != ERROR_SUCCESS)
      {
        ASSERT(NULL);
      }
    }
    
  }
  else
  {
    ASSERT(NULL);
  }
  
  if (hIDWExtensionKey != NULL)
    RegCloseKey(hIDWExtensionKey);
}



bool InventorLocation::GetCompatibilityFilePath(LPTSTR szFileName, LPTSTR szBuffer)
{
   InitializePaths();
   _tcscpy_s(szBuffer,_MAX_PATH,m_szCompatibilityPath);
   _tcscat_s(szBuffer,_MAX_PATH,_T("\\")); 
   _tcscat_s(szBuffer,_MAX_PATH,szFileName); 
    return true;
}


void InventorLocation::InitializePaths()
{
  if(!m_bPathsInitialized)
  {
    HRESULT hr = GetInventorCompatibilityLocation(m_szCompatibilityPath);
    m_bPathsInitialized = true;
  }
}

// the buffer will return the full path
bool InventorLocation::GetMDT_OE_FilePath(LPTSTR szFileName, LPTSTR szBuffer)
{
   InitializePaths();
   _tcscpy_s(szBuffer,_MAX_PATH,m_szMDT_OE_Path);
   _tcscat_s(szBuffer,_MAX_PATH,_T("\\")); 
   _tcscat_s(szBuffer,_MAX_PATH,szFileName); 
    return true;
}



// Find using the CLSID for "Autodesk Inventor Part File" i.e. {4D29B490-49B2-11D0-93C3-7E0706000000}
// Get the path from HKCR\CLSID\{4D29B490-49B2-11D0-93C3-7E0706000000}\LocalServer32 
// and strip out the filespec of the exe
// szLocation must point to a string of length _MAX_PATH
HRESULT InventorLocation::GetInventorCompatibilityLocation(LPTSTR szLocation)
{
  HRESULT hr = E_FAIL;
  MHKEY rootKey = HKEY_CURRENT_USER;
	HKEY hCLSIDKey = NULL;
	HKEY hPARTCLSIDKey = NULL;
	HKEY hLocalServer32Key = NULL;
	if (RegOpenKeyEx(rootKey, KEY_CLSID, 0, KEY_WRITE|KEY_READ,&hCLSIDKey) == ERROR_SUCCESS)
	{
  	if (RegOpenKeyEx(hCLSIDKey, KEY_PARTCLSID, 0, KEY_WRITE|KEY_READ,&hPARTCLSIDKey) == ERROR_SUCCESS)
    {
  	  if (RegOpenKeyEx(hPARTCLSIDKey, KEY_LocalServer32, 0, KEY_WRITE|KEY_READ,&hLocalServer32Key) == ERROR_SUCCESS)
      {
        	DWORD valueSize = _MAX_PATH;
	        DWORD dwType    = 0;

	        // get the value
	        if (RegQueryValueEx(hLocalServer32Key, (LPCTSTR) _T(""), NULL,
							                &dwType, (LPBYTE) szLocation, &valueSize) == ERROR_SUCCESS) 
          {
		        // make sure value is a string
            if(dwType == REG_SZ)
            { 
              // At this point szLocation = "c:\program files\autodesk\inventor\bin\inventor.exe"
              // this reduces it to c:\program files\autodesk\inventor\bin
              LPTSTR lpstrBackslash = _tcsrchr(szLocation, _T('\\'));
              lpstrBackslash[0] =  wcharNul; 

              #ifdef _DEBUG
             // In the debug build, location will otherwise come back as r:\lib\Compatibility
             // With this code we remove lib so that it will now return as r:\Compatibility
              lpstrBackslash = _tcsrchr(szLocation, _T('\\'));
              lpstrBackslash[0] =  wcharNul; 
              #endif

              // this makes it c:\program files\autodesk\inventor\Compatibility
              lpstrBackslash = _tcsrchr(szLocation, _T('\\'));
           		_tcscpy_s(lpstrBackslash + 1,_MAX_PATH, _T("Compatibility")); 
              hr = NOERROR;
            }
          }
      }
    }
	}
	if (hLocalServer32Key != NULL)
		RegCloseKey(hLocalServer32Key);

	if (hPARTCLSIDKey != NULL)
		RegCloseKey(hPARTCLSIDKey);

	if (hCLSIDKey != NULL)
		RegCloseKey(hCLSIDKey);

	RegCloseKey(rootKey);

	return hr;
}






// Find using FindExecutable
bool InventorLocation::IsIDWRegistered()
{
// Create a temp file with .IDW extension
  // TBD: chose a name and location that is non-intrusive
  CStdioFile f1;
  if( !f1.Open( _T("c:\\a.IDW"), CFile::modeCreate | CFile::modeWrite | CFile::typeText ) ) {
  }
  f1.Close();
// use FindExecutable
  CString str;

  HINSTANCE hInst = ::FindExecutable(_T("c:\\a.IDW"),_T("c:\\"),str.GetBuffer(_MAX_PATH));
  str.ReleaseBuffer();
  // TBD: delete a.IDW

  return !(31 == (INT_PTR)hInst); // no association
}



// Find using the CLSID for Inventor.DrawingDocument
// Get the path from HKCR\CLSID\{BBF9FDF1-52DC-11D0-8C04-0800090BE8EC}\LocalServer32 
// and strip out the filespec of the exe
// szLocation must point to a string of length _MAX_PATH
bool InventorLocation::IsInventorRegistered(HINSTANCE hInst)
{
  HRESULT hr = E_FAIL;
  MHKEY rootKey = HKEY_CURRENT_USER;
	HKEY hCLSIDKey = NULL;
	HKEY hPARTCLSIDKey = NULL;
	HKEY hLocalServer32Key = NULL;
  TCHAR szLocation[_MAX_PATH];
  bool bFound = false;
	if (RegOpenKeyEx(rootKey, KEY_CLSID, 0, KEY_WRITE|KEY_READ,&hCLSIDKey) == ERROR_SUCCESS)
	{
  	if (RegOpenKeyEx(hCLSIDKey, KEY_INVENTORCLSID, 0, KEY_WRITE|KEY_READ,&hPARTCLSIDKey) == ERROR_SUCCESS)
    {
  	  if (RegOpenKeyEx(hPARTCLSIDKey, KEY_LocalServer32, 0, KEY_WRITE|KEY_READ,&hLocalServer32Key) == ERROR_SUCCESS)
      {
        	DWORD valueSize = _MAX_PATH;
	        DWORD dwType    = 0;

	        // get the value
	        if (RegQueryValueEx(hLocalServer32Key, (LPCTSTR) _T(""), NULL,
							                &dwType, (LPBYTE) szLocation, &valueSize) == ERROR_SUCCESS) 
          {
		        // make sure value is a string
            if(dwType == REG_SZ)
            { 
              // Did IDWViewer itself put it there?
              CString strFile = szLocation;
              CString strShortName;
	            TCHAR szLongPathName[_MAX_PATH];
	            ::GetModuleFileName(hInst, szLongPathName, _MAX_PATH);
	            if (::GetShortPathName(szLongPathName,
		            strShortName.GetBuffer(_MAX_PATH), _MAX_PATH) == 0)
	            {
		            // rare failure case (especially on not-so-modern file systems)
		            strShortName = szLongPathName;
	            }
	            strShortName.ReleaseBuffer();
              strShortName.MakeLower();
              strFile.MakeLower();
              bFound = (strFile.Find(INVENTOR_EXE) != -1); // found Inventor Executable in there
            }
          }
      }
    }
	}
	if (hLocalServer32Key != NULL)
		RegCloseKey(hLocalServer32Key);

	if (hPARTCLSIDKey != NULL)
		RegCloseKey(hPARTCLSIDKey);

	if (hCLSIDKey != NULL)
		RegCloseKey(hCLSIDKey);

	RegCloseKey(rootKey);

	return bFound;
}


/////////////////////////////////////////////////////////////////////////////
// CIDWViewerApp

BEGIN_MESSAGE_MAP(CIDWViewerApp, CWinApp)
	//{{AFX_MSG_MAP(CIDWViewerApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIDWViewerApp construction

CIDWViewerApp::CIDWViewerApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CIDWViewerApp object

CIDWViewerApp theApp;





// This generated CLSID is not being used. Instead Inventor Drawing Document's CLSID is being used.
// Inventor Drawing Document's CLSID: {BBF9FDF1-52DC-11D0-8C04-0800090BE8EC}
//
// {F98FA8CD-ACE5-11D3-A478-00C04F6B9531}
static const CLSID clsidIDWViewer =
 { 0xf98fa8cd, 0xace5, 0x11d3, { 0xa4, 0x78, 0x0, 0xc0, 0x4f, 0x6b, 0x95, 0x31 } };

/////////////////////////////////////////////////////////////////////////////
// CIDWViewerApp initialization

BOOL CIDWViewerApp::InitInstance()
{
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

  AfxEnableControlContainer();


	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

  // No registry entry for this container application
	// registry key under which our settings are stored.
	// SetRegistryKey(_T("IDWViewer"));

	// LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate{ nullptr };
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CIDWViewerDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(IDWxView));

	pDocTemplate->SetServerInfo(
		IDR_SRVR_EMBEDDED, IDR_SRVR_INPLACE,
		RUNTIME_CLASS(CInPlaceFrame));
	
  AddDocTemplate(pDocTemplate);

  CLSID clsidInventor;
  LPOLESTR lpszCLSID = KEY_INVENTORCLSID_UNICODE;
  HRESULT hr  = CLSIDFromString(lpszCLSID,  //Pointer to the string representation of the CLSID
                          &clsidInventor);  //Pointer to the CLSID  
  
  // Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
  if(InventorLocation::g_Location.IsInventorRegistered(m_hInstance))
  	m_server.ConnectTemplate(clsidIDWViewer, pDocTemplate, TRUE);
  else
	  m_server.ConnectTemplate(clsidInventor, pDocTemplate, TRUE);
		// Note: SDI applications register server objects only if /Embedding
		//   or /Automation is present on the command line.

  
  // Register all OLE server (factories) as running.  This enables the
	//  OLE libraries to create objects from other applications.
  COleTemplateServer::RegisterAll();

  // This code is left here just as a reference to state that we do not want to add this 
  // as we do not want to become the default application for IDW files
  // EnableShellOpen();
	// RegisterShellFileTypes(FALSE); 
  // However we do want to register .IDW as the extension and connect that to Inventor.DrawingDocument
  // Which we will do in  SelfRegisteration   

  // Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

  // is this just SelfRegisteration 
  if((__argc > 1) && SelfRegisteration(__targv[1]))
    return FALSE;

	// Check to see if launched as OLE server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{

		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		return TRUE;
	}

 // The only command that we want to process is new window
 // Dispatch commands specified on the command line
 if (!ProcessShellCommand(cmdInfo))
  	return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

  // This code is left here just as a reference to state that we do not want to add this 
	// Enable drag/drop open
	// m_pMainWnd->DragAcceptFiles();

	return TRUE;
}



BOOL CIDWViewerApp::SelfRegisteration(LPCTSTR szCmd)
{   
    CString strCmd = szCmd;
    if (strCmd == _T("/UnregServer"))
    {
	    ASSERT(NULL);
	    AfxMessageBox(_T("Not implemented"));
	    
      return true;
    }
    if (strCmd == _T("/RegServer"))
    {
     if(!InventorLocation::g_Location.IsInventorRegistered(m_hInstance))
     {
	    // When a server application is launched stand-alone, it is a good idea
	    //  to update the system registry in case it has been damaged.
	    m_server.UpdateRegistry(OAT_INPLACE_SERVER);
      // we also want to register .IDW as the extension and connect that to Inventor.DrawingDocument
      RegisterIDWExtension();
     }
      return true;
    }
   return false;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CIDWViewerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CIDWViewerApp message handlers

