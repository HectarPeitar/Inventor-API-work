// CatalogBrowserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "insertcatalogpart.h"
#include "catalogbrowserdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCatalogBrowserDlg dialog


CCatalogBrowserDlg::CCatalogBrowserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCatalogBrowserDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCatalogBrowserDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCatalogBrowserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCatalogBrowserDlg)
	DDX_Control(pDX, IDC_COMBO1, m_PartsListCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCatalogBrowserDlg, CDialog)
	//{{AFX_MSG_MAP(CCatalogBrowserDlg)
	ON_CBN_SELENDOK(IDC_COMBO1, OnCatalogPartSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCatalogBrowserDlg message handlers

BOOL CCatalogBrowserDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_PartsListCtrl.AddString (_T("Box"));
	m_PartsListCtrl.AddString (_T("Cylinder"));
	m_PartsListCtrl.AddString (_T("Torus"));
	m_PartsListCtrl.AddString (_T("Sphere"));
	m_PartsListCtrl.AddString (_T("Cone"));

	m_PartsListCtrl.SetCurSel(0);
	OnCatalogPartSelect();

	SetWindowText (m_Title);

	return TRUE;
}

void CCatalogBrowserDlg::OnCatalogPartSelect() 
{
	int iCurSel = m_PartsListCtrl.GetCurSel(); 
	if(iCurSel == CB_ERR)
		return ;

	m_PartsListCtrl.GetLBText(iCurSel, m_strCatalogPartFile);	
}
