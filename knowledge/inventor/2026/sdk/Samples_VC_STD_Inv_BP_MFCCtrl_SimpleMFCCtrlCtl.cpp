// SIMPLEMFCCONTROLCtl.cpp : Implementation of the CSIMPLEMFCCONTROLCtrl ActiveX Control class.

#include "stdafx.h"
#include "SIMPLEMFCCONTROL.h"
#include "SIMPLEMFCCONTROLCtl.h"
#include "SIMPLEMFCCONTROLPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_COMBOBOX 100

IMPLEMENT_DYNCREATE(CSIMPLEMFCCONTROLCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CSIMPLEMFCCONTROLCtrl, COleControl)
	//{{AFX_MSG_MAP(CSIMPLEMFCCONTROLCtrl)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(OCM_COMMAND, OnOcmCommand)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CSIMPLEMFCCONTROLCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CSIMPLEMFCCONTROLCtrl)
	DISP_FUNCTION(CSIMPLEMFCCONTROLCtrl, "AddText", AddText, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CSIMPLEMFCCONTROLCtrl, "Clear", ClearLBoxContents, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
	//DISP_FUNCTION_ID(CSIMPLEMFCCONTROLCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CSIMPLEMFCCONTROLCtrl, COleControl)
	//{{AFX_EVENT_MAP(CSIMPLEMFCCONTROLCtrl)
	EVENT_CUSTOM("ContentChanged", FireContentChanged, VTS_NONE)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CSIMPLEMFCCONTROLCtrl, 1)
	PROPPAGEID(CSIMPLEMFCCONTROLPropPage::guid)
END_PROPPAGEIDS(CSIMPLEMFCCONTROLCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CSIMPLEMFCCONTROLCtrl, "SIMPLEMFCCONTROL.SIMPLEMFCCONTROLCtrl.1",
	0x50ccd357, 0xfa53, 0x42b6, 0x8b, 0x6, 0xc5, 0xd6, 0xab, 0x37, 0xcd, 0xbf)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CSIMPLEMFCCONTROLCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DSIMPLEMFCCONTROL =
		{ 0xea9f39cd, 0x356, 0x4f7c, { 0x8d, 0xa8, 0xde, 0x91, 0x3d, 0xb6, 0x4d, 0x99 } };
const IID BASED_CODE IID_DSIMPLEMFCCONTROLEvents =
		{ 0xb1a2efbe, 0xa44e, 0x4a40, { 0xa4, 0xca, 0x80, 0x16, 0x85, 0xa6, 0xa6, 0x24 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwSIMPLEMFCCONTROLOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CSIMPLEMFCCONTROLCtrl, IDS_SIMPLEMFCCONTROL, _dwSIMPLEMFCCONTROLOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROLCtrl::CSIMPLEMFCCONTROLCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CSIMPLEMFCCONTROLCtrl

BOOL CSIMPLEMFCCONTROLCtrl::CSIMPLEMFCCONTROLCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_SIMPLEMFCCONTROL,
			IDB_SIMPLEMFCCONTROL,
			afxRegApartmentThreading,
			_dwSIMPLEMFCCONTROLOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROLCtrl::CSIMPLEMFCCONTROLCtrl - Constructor

CSIMPLEMFCCONTROLCtrl::CSIMPLEMFCCONTROLCtrl()
{
	InitializeIIDs(&IID_DSIMPLEMFCCONTROL, &IID_DSIMPLEMFCCONTROLEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROLCtrl::~CSIMPLEMFCCONTROLCtrl - Destructor

CSIMPLEMFCCONTROLCtrl::~CSIMPLEMFCCONTROLCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROLCtrl::OnDraw - Drawing function

void CSIMPLEMFCCONTROLCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	DoSuperclassPaint(pdc, rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROLCtrl::DoPropExchange - Persistence support

void CSIMPLEMFCCONTROLCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROLCtrl::OnResetState - Reset control to default state

void CSIMPLEMFCCONTROLCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROLCtrl::AboutBox - Display an "About" box to the user

void CSIMPLEMFCCONTROLCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_SIMPLEMFCCONTROL);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROLCtrl::PreCreateWindow - Modify parameters for CreateWindowEx

BOOL CSIMPLEMFCCONTROLCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	return COleControl::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROLCtrl::IsSubclassedControl - This is a subclassed control

BOOL CSIMPLEMFCCONTROLCtrl::IsSubclassedControl()
{
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROLCtrl::OnOcmCommand - Handle command messages

LRESULT CSIMPLEMFCCONTROLCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
{
#ifdef _WIN32
	WORD wNotifyCode = HIWORD(wParam);
#else
	WORD wNotifyCode = HIWORD(lParam);
#endif

	// TODO: Switch on wNotifyCode here.

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROLCtrl message handlers

int CSIMPLEMFCCONTROLCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect(0, 0, 100, 100);
	if(!m_listBox.Create(WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
		rect, this, ID_COMBOBOX))
	{
		TRACE(_T("Could not create list box"));
		return -1;
	}

	return 0;
}

void CSIMPLEMFCCONTROLCtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);
	
	if(m_listBox.GetSafeHwnd())
	{
		m_listBox.MoveWindow(0,0,cx,cy);
	}
	
}

BOOL CSIMPLEMFCCONTROLCtrl::AddText(LPCTSTR text) 
{
	if(m_listBox.GetSafeHwnd())
	{
		m_listBox.AddString(text);
		FireContentChanged();
		return TRUE;
	}

	return FALSE;
}

void CSIMPLEMFCCONTROLCtrl::ClearLBoxContents() 
{
	m_listBox.ResetContent();
	FireContentChanged();

	ASSERT(m_listBox.GetCount() == 0);
}
