// SIMPLEMFCCONTROLPpg.cpp : Implementation of the CSIMPLEMFCCONTROLPropPage property page class.

#include "stdafx.h"
#include "SIMPLEMFCCONTROL.h"
#include "SIMPLEMFCCONTROLPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CSIMPLEMFCCONTROLPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CSIMPLEMFCCONTROLPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CSIMPLEMFCCONTROLPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CSIMPLEMFCCONTROLPropPage, "SIMPLEMFCCONTROL.SIMPLEMFCCONTROLPropPage.1",
	0xba512ab, 0x1b46, 0x40b9, 0x85, 0x67, 0xa9, 0x41, 0xa0, 0xe, 0x5d, 0xd2)


/////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROLPropPage::CSIMPLEMFCCONTROLPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CSIMPLEMFCCONTROLPropPage

BOOL CSIMPLEMFCCONTROLPropPage::CSIMPLEMFCCONTROLPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_SIMPLEMFCCONTROL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROLPropPage::CSIMPLEMFCCONTROLPropPage - Constructor

CSIMPLEMFCCONTROLPropPage::CSIMPLEMFCCONTROLPropPage() :
	COlePropertyPage(IDD, IDS_SIMPLEMFCCONTROL_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CSIMPLEMFCCONTROLPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROLPropPage::DoDataExchange - Moves data between page and properties

void CSIMPLEMFCCONTROLPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CSIMPLEMFCCONTROLPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROLPropPage message handlers
