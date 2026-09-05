#include "stdafx.h"
#include "ApplicationEvent.h"
#include "MFCBrowserPanes.h"
#include "MFCBrowserPanesDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CApplicationEvents

IMPLEMENT_DYNCREATE(CApplicationEvents, CCmdTarget)

CApplicationEvents::CApplicationEvents(CMFCBrowserPanesDlg* pParent) : m_pParent(pParent)
{
   ASSERT(m_pParent);

   EnableAutomation();  // Needed in order to sink events.
}

CApplicationEvents::~CApplicationEvents()
{
}


BEGIN_MESSAGE_MAP(CApplicationEvents, CCmdTarget)
	//{{AFX_MSG_MAP(CApplicationEvents)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CApplicationEvents, CCmdTarget)
	DISP_FUNCTION_ID(CApplicationEvents, "OnQuit",	 0x300061a, QuitEvent, VT_DISPATCH, VTS_NONE)
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CApplicationEvents, CCmdTarget)
	INTERFACE_PART(CApplicationEvents, DIID_ApplicationEventsSink, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CApplicationEvents event handlers
void CApplicationEvents::QuitEvent() 
{
	ASSERT_VALID(m_pParent);
	m_pParent->OnInventorExit();
}
