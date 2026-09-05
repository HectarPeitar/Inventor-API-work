// MFCBrowserPanesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCBrowserPanes.h"
#include "MFCBrowserPanesDlg.h"
#include "BrowserPaneEvent.h"

#include "AfxCtl.h"
#include <afxpriv.h> // for WM_KICKIDLE

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

/////////////////////////////////////////////////////////////////////////////
// CMFCBrowserPanesDlg dialog

CMFCBrowserPanesDlg::CMFCBrowserPanesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCBrowserPanesDlg::IDD, pParent), 	m_bConnected(false), m_bPaneAdded(false)
{
	//{{AFX_DATA_INIT(CMFCBrowserPanesDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_dwCookie = 0;
	m_dwBrowserPaneEventCookie = 0;
	m_dwAppEventCookie = 0;
	m_pEvents = new CMFCControlEvents(this);
	m_pBrowserPaneEvents = new CBrowserPaneEvents(this);
	m_pApplicationEvents = new CApplicationEvents(this);
}

CMFCBrowserPanesDlg::~CMFCBrowserPanesDlg()
{
	delete m_pEvents;
	delete m_pBrowserPaneEvents;
	delete m_pApplicationEvents;
}

void CMFCBrowserPanesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMFCBrowserPanesDlg)
	DDX_Control(pDX, IDC_LISTBOX, m_listBox);
	DDX_Control(pDX, IDC_CONTROLTEXT, m_editText);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMFCBrowserPanesDlg, CDialog)
	//{{AFX_MSG_MAP(CMFCBrowserPanesDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CONNECT_BUTTON, OnConnect)
	ON_BN_CLICKED(IDC_ADDPANE, OnAddpane)
	ON_BN_CLICKED(IDC_ADDTEXT, OnAddtext)
	ON_BN_CLICKED(IDC_CLEARCONTENTS, OnClearcontents)
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
	ON_UPDATE_COMMAND_UI(IDC_CONNECT_BUTTON, OnUpdateConnectBtn)
	ON_UPDATE_COMMAND_UI(IDC_ADDPANE, OnUpdateAddBrowserBtn)
	ON_UPDATE_COMMAND_UI(IDC_CONTROLTEXT, OnUpdatePaneAddedState)
	ON_UPDATE_COMMAND_UI(IDC_ADDTEXT, OnUpdatePaneAddedState)
	ON_UPDATE_COMMAND_UI(IDC_CLEARCONTENTS, OnUpdatePaneAddedState)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCBrowserPanesDlg message handlers

BOOL CMFCBrowserPanesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	ASSERT_VALID(&m_editText);
	m_editText.SetWindowText(_T("Sample Text"));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCBrowserPanesDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if(nID == SC_CLOSE)
	{
		CDialog::OnCancel();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBrowserPanesDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBrowserPanesDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMFCBrowserPanesDlg::OnOK() 
{
	CDialog::OnOK();
}

void CMFCBrowserPanesDlg::OnInventorExit()
{
	CDialog::OnOK();
}

void CMFCBrowserPanesDlg::OnCancel() 
{
}

void CMFCBrowserPanesDlg::OnConnect() 
{
	CLSID AppClsId;


	HRESULT hr = ::CLSIDFromProgID (L"Inventor.Application", &AppClsId);

	if(SUCCEEDED(hr))
	{
		hr = ::GetActiveObject (AppClsId, NULL, &m_pAppUnk);	
		if(SUCCEEDED(hr))
		{
			hr = m_pAppUnk->QueryInterface(DIID_Application, (void **) &m_pApplication);
			if(m_pApplication)
			{
				hr = m_pApplication->get_Documents(&m_pDocs);

				if(m_pDocs)
					hr = m_pApplication->get_ActiveDocument(&m_pDocument);
				if(!m_pDocument)
				{
					AfxMessageBox(_T("Inventor must be running with a document opened."));
					return;
				}					
			}

		}
	}

	if(SUCCEEDED(hr))
	{
		m_bConnected = true;
	
		HRESULT hr = m_pApplication->get_ApplicationEvents(&m_spAppEvents);
		ASSERT(m_spAppEvents);

		if(SUCCEEDED(hr))
		{
			BOOL bAppAdv = AfxConnectionAdvise(m_spAppEvents, DIID_ApplicationEventsSink,
                                m_pApplicationEvents->GetInterface(&IID_IUnknown),
                                TRUE, &m_dwAppEventCookie);
			ASSERT(bAppAdv);
		}
	}
	else
	{
		m_bConnected = false;
		AfxMessageBox(_T("Could Not connect. Please make sure Inventor is Running."));
	}
}

void CMFCBrowserPanesDlg::OnAddpane() 
{
	ASSERT(m_pDocument);

	CComPtr<BrowserPanes> spPanes;
	HRESULT hr = m_pDocument->get_BrowserPanes(&spPanes);
	ASSERT(spPanes);
	if(SUCCEEDED(hr))
	{
		CComBSTR mfcCtlName(_T("Simple MFC Control"));
		CComBSTR mfcCtlGuid(_T("SIMPLEMFCCONTROL.SIMPLEMFCCONTROLCtrl.1"));

		hr = spPanes->Add(mfcCtlName, mfcCtlGuid, &m_pBrowserPane);
		if(m_pBrowserPane)
		{
			BOOL bBrwsrAdvised = AfxConnectionAdvise(m_pBrowserPane, DIID_BrowserPaneSink,
                                m_pBrowserPaneEvents->GetInterface(&IID_IUnknown),
                                TRUE, &m_dwBrowserPaneEventCookie);
			// Activate it
			hr = m_pBrowserPane->Activate();
			ASSERT(SUCCEEDED(hr));
			
			IDispatch* lpDispatch = NULL;
			hr = m_pBrowserPane->get_Control(&lpDispatch);

			if(SUCCEEDED(hr))
				m_bPaneAdded = true;
			else
				m_bPaneAdded = false;
			
			if(lpDispatch)
			{
				m_control.AttachDispatch(lpDispatch);

				// Start listening to event of the control
				BOOL bAdvised = AfxConnectionAdvise(m_control, SIMPLEMFCCONTROLLib::DIID__DSIMPLEMFCCONTROLEvents,
                                m_pEvents->GetInterface(&IID_IUnknown),
                                TRUE, &m_dwCookie);
			}
		}
	}
}

void CMFCBrowserPanesDlg::OnAddtext() 
{
	ASSERT(m_control.m_lpDispatch);

	if(m_control.m_lpDispatch == NULL)
	{
		AfxMessageBox(_T("Control Not Sinked Yet"));
		return;
	}

	CString text;
	m_editText.GetWindowText(text);
	if(text.GetLength() > 0)
		m_control.AddText(text);
}

void CMFCBrowserPanesDlg::OnClearcontents() 
{
	ASSERT(m_control.m_lpDispatch);

	if(m_control.m_lpDispatch == NULL)
	{
		AfxMessageBox(_T("Control Not Sinked Yet"));
		return;
	}

	m_control.Clear();
}

void CMFCBrowserPanesDlg::AddListBoxText(CString& text)
{
	if(text.IsEmpty())
		return;
	
	ASSERT_VALID(&m_listBox);
	m_listBox.AddString(text);
}


void CMFCBrowserPanesDlg::OnDestroy() 
{
   ShutDownEventSinks();
   
   CDialog::OnDestroy();
}

void CMFCBrowserPanesDlg::ShutDownEventSinks()
{
   if (m_dwBrowserPaneEventCookie)
   {
		BOOL bUnadvised = AfxConnectionUnadvise(m_pBrowserPane, DIID_BrowserPaneSink,
                                              m_pBrowserPaneEvents->GetInterface(&IID_IUnknown),
                                              TRUE, m_dwBrowserPaneEventCookie);
		m_dwBrowserPaneEventCookie = 0;
   }

   if (m_dwCookie)
   {
		AfxConnectionAdvise(m_control, SIMPLEMFCCONTROLLib::DIID__DSIMPLEMFCCONTROLEvents,
								m_pEvents->GetInterface(&IID_IUnknown),
								TRUE, &m_dwCookie);
		m_dwCookie = 0;
   }

   if(m_dwAppEventCookie)
   {
		AfxConnectionAdvise(m_spAppEvents, DIID_ApplicationEventsSink,
								m_pApplicationEvents->GetInterface(&IID_IUnknown),
								TRUE, &m_dwAppEventCookie);
		m_dwAppEventCookie = 0;
   }
}

LRESULT CMFCBrowserPanesDlg::OnKickIdle(WPARAM wp, LPARAM lCount)
{
	UpdateDialogControls(this, TRUE);
	return 0;
}
 
afx_msg void CMFCBrowserPanesDlg::OnUpdateConnectBtn(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_bConnected ? FALSE : TRUE);
}

afx_msg void CMFCBrowserPanesDlg::OnUpdateAddBrowserBtn(CCmdUI* pCmdUI)
{
	if(m_bConnected)
		pCmdUI->Enable(m_bPaneAdded ? FALSE : TRUE);
	else
		pCmdUI->Enable(FALSE);
}

afx_msg void CMFCBrowserPanesDlg::OnUpdatePaneAddedState(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_bPaneAdded ? TRUE: FALSE);
}

