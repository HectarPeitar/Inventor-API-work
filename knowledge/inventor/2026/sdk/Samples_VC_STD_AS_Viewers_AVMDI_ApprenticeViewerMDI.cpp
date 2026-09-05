// ApprenticeViewerMDI.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ApprenticeViewerMDI.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "ApprenticeViewerMDIDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CApprenticeViewerMDIApp

BEGIN_MESSAGE_MAP(CApprenticeViewerMDIApp, CWinApp)
	//{{AFX_MSG_MAP(CApprenticeViewerMDIApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CApprenticeViewerMDIApp construction

CApprenticeViewerMDIApp::CApprenticeViewerMDIApp()
{
	HRESULT hr = ::CoInitialize (NULL);
	ASSERT(SUCCEEDED(hr));
}

CApprenticeViewerMDIApp::~CApprenticeViewerMDIApp()
{
	// Need to release the server before we uninitialize	
	m_pApprenticeServer = NULL;
	
	::CoUninitialize(); 
}

CComPtr<ApprenticeServer> CApprenticeViewerMDIApp::GetApprenticeServer()
{
	return m_pApprenticeServer;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CApprenticeViewerMDIApp object

CApprenticeViewerMDIApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CApprenticeViewerMDIApp initialization

BOOL CApprenticeViewerMDIApp::InitInstance()
{
	AfxEnableControlContainer();

	// Create the apprentice server
	CLSID AppComponentClsid;
	HRESULT hr = ::CLSIDFromProgID(L"Inventor.ApprenticeServer", &AppComponentClsid);
	hr = m_pApprenticeServer.CoCreateInstance(AppComponentClsid);

	if (m_pApprenticeServer == NULL)
	{
		AfxMessageBox(L"Failed to create an instance of Apprentice server.");
		return FALSE;
	}

	ASSERT(m_pApprenticeServer);

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings(10);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pInventorFiles{ nullptr };
	pInventorFiles = new CMultiDocTemplate(
		IDR_INVENTORFILES,
		RUNTIME_CLASS(CApprenticeViewerMDIDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CLeftView));
	AddDocTemplate(pInventorFiles);

	CMultiDocTemplate* pAssemblyTemplate{ nullptr };
	pAssemblyTemplate = new CMultiDocTemplate(
		IDR_ASSEMBLYTYPE,
		RUNTIME_CLASS(CApprenticeViewerMDIDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CLeftView));
	AddDocTemplate(pAssemblyTemplate);
	
	CMultiDocTemplate* pPartDocTemplate{ nullptr };
	pPartDocTemplate = new CMultiDocTemplate(
		IDR_PARTTYPE,
		RUNTIME_CLASS(CApprenticeViewerMDIDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CLeftView));
	AddDocTemplate(pPartDocTemplate);

	CMultiDocTemplate* pDrawingDocTemplate{ nullptr };
	pDrawingDocTemplate = new CMultiDocTemplate(
		IDR_DRAWINGTYPE, 
		RUNTIME_CLASS(CApprenticeViewerMDIDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CLeftView));
	AddDocTemplate(pDrawingDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;

	// Turn off default OnFileNew() call
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
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
void CApprenticeViewerMDIApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CApprenticeViewerMDIApp message handlers

void CApprenticeViewerMDIApp::OnFileOpen() 
{
	// prompt the user (with all document templates)
	CString newName;
	if (!DoPromptFileName(newName, AFX_IDS_OPENFILE,
		OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, TRUE, NULL))
	{
		return; // open cancelled
	}

	AfxGetApp()->OpenDocumentFile(newName);
}
