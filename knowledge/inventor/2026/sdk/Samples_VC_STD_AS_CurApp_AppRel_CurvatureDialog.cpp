// CurvatureDialog.cpp : implementation file
//

#include "stdafx.h"
#include "../CurvatureApp.h"
#include "../CurvatureAppDoc.h"
#include "../MainFrm.h"
#include "curvaturedialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurvatureDialog dialog


CCurvatureDialog::CCurvatureDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCurvatureDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCurvatureDialog)
	m_curvatureType = _T("Pin Cushion");
	m_uDensity = 0;
	m_vDensity = 0;
	//}}AFX_DATA_INIT
}


void CCurvatureDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCurvatureDialog)
	DDX_CBString(pDX, IDC_CURVATURE_TYPE, m_curvatureType);
	DDX_Text(pDX, IDC_DENSITY_U_EDIT, m_uDensity);
	DDV_MinMaxUInt(pDX, m_uDensity, 0, 100);
	DDX_Text(pDX, IDC_DENSITY_V_EDIT, m_vDensity);
	DDV_MinMaxUInt(pDX, m_vDensity, 0, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCurvatureDialog, CDialog)
	//{{AFX_MSG_MAP(CCurvatureDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurvatureDialog message handlers

void CCurvatureDialog::OnOK()
{
  UpdateData(TRUE);

  CWnd* pWnd = AfxGetMainWnd();
  CMainFrame* pFrame = dynamic_cast<CMainFrame*>(pWnd);
  if (pFrame)
  {
    CFrameWnd* pActFrame = pFrame->GetActiveFrame();
    if (pActFrame)
    {
      CCurvatureAppDoc* pDoc = reinterpret_cast<CCurvatureAppDoc*>(pActFrame->GetActiveDocument());
      if(pDoc)
        pDoc->ProcessCommand();
    }
  }
}

void CCurvatureDialog::OnCancel() 
{
  CWnd* pWnd = AfxGetMainWnd();
  CMainFrame* pFrame = dynamic_cast<CMainFrame*>(pWnd);
  if (pFrame)
  {
    CFrameWnd* pActFrame = pFrame->GetActiveFrame();
    if (pActFrame)
    {
      CView* pView = pActFrame->GetActiveView();
      if (pView)
        pView->PostMessage (WM_KEYDOWN, VK_ESCAPE, 0);
    }
  }

  CDialog::OnCancel();
}

BOOL CCurvatureDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

  CComboBox* pBox = reinterpret_cast<CComboBox*>(GetDlgItem(IDC_CURVATURE_TYPE));
  pBox->SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
