#include "stdafx.h"
#include "BrowserPaneEvent.h"
#include "MFCBrowserPanes.h"
#include "MFCBrowserPanesDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CBrowserPaneEvents

IMPLEMENT_DYNCREATE(CBrowserPaneEvents, CCmdTarget)

CBrowserPaneEvents::CBrowserPaneEvents(CMFCBrowserPanesDlg* pParent) : m_pParent(pParent)
{
   ASSERT(m_pParent);

   EnableAutomation();  // Needed in order to sink events.
}

CBrowserPaneEvents::~CBrowserPaneEvents()
{
}


BEGIN_MESSAGE_MAP(CBrowserPaneEvents, CCmdTarget)
	//{{AFX_MSG_MAP(CBrowserPaneEvents)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CBrowserPaneEvents, CCmdTarget)
DISP_FUNCTION_ID(CBrowserPaneEvents, "OnActivate",	 0x3007901, ActivateEvent, VT_EMPTY, VTS_NONE)
DISP_FUNCTION_ID(CBrowserPaneEvents, "OnDeactivate", 0x3007902, DeactivateEvent, VT_EMPTY, VTS_NONE)
DISP_FUNCTION_ID(CBrowserPaneEvents, "OnHelp", 0x3007903, OnHelp, VT_EMPTY, VTS_I4 VTS_DISPATCH VTS_PI4)
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CBrowserPaneEvents, CCmdTarget)
	INTERFACE_PART(CBrowserPaneEvents, DIID_BrowserPaneSink, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrowserPaneEvents event handlers
void CBrowserPaneEvents::ActivateEvent() 
{
	ASSERT_VALID(m_pParent);
	m_pParent->AddListBoxText(CString("BrowserPane Event - Activated"));
}

void CBrowserPaneEvents::DeactivateEvent() 
{
	ASSERT_VALID(m_pParent);
	m_pParent->AddListBoxText(CString("BrowserPane Event - DeActivated"));
}



void CBrowserPaneEvents::OnHelp(EventTimingEnum BeforeOrAfter, NameValueMap * pContext,  HandlingCodeEnum * HandlingCode)
{
	*HandlingCode = kEventHandled;
	m_pParent->AddListBoxText(CString("BrowserPane Event - On Help"));
}

