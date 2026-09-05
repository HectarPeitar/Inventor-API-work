#include "stdafx.h"
#include "resource.h"
#include "simplemfccontrol.h"
#include "MFCBrowserPanesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROL properties

/////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROL operations

BOOL CSIMPLEMFCCONTROL::AddText(LPCTSTR text)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		text);
	return result;
}

void CSIMPLEMFCCONTROL::Clear()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CSIMPLEMFCCONTROL::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CMFCControlEvents

IMPLEMENT_DYNCREATE(CMFCControlEvents, CCmdTarget)

CMFCControlEvents::CMFCControlEvents(CMFCBrowserPanesDlg* pParent) : m_pParent(pParent)
{
   ASSERT(m_pParent);

   EnableAutomation();  // Needed in order to sink events.
}

CMFCControlEvents::~CMFCControlEvents()
{
}


BEGIN_MESSAGE_MAP(CMFCControlEvents, CCmdTarget)
	//{{AFX_MSG_MAP(CMFCControlEvents)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMFCControlEvents, CCmdTarget)
	DISP_FUNCTION_ID(CMFCControlEvents, "ContentChanged", 0x1,
	                    ContentChanged, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CMFCControlEvents, CCmdTarget)
INTERFACE_PART(CMFCControlEvents, SIMPLEMFCCONTROLLib::DIID__DSIMPLEMFCCONTROLEvents, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCControlEvents event handlers
void CMFCControlEvents::ContentChanged() 
{
	ASSERT_VALID(m_pParent);
	m_pParent->AddListBoxText(CString("SimpleMFCControl Event - Content Changed"));
}
