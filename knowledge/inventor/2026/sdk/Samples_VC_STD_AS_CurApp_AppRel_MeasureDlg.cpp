// MeasureDlg.cpp : implementation file
//

#include "stdafx.h"

#include "../CurvatureApp.h"

#include "measuredlg.h"
#include "../MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMeasureDlg dialog


CMeasureDlg::CMeasureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMeasureDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMeasureDlg)
	m_MeasureValue = _T("");
	m_MeasureProperty = _T("");
	//}}AFX_DATA_INIT
}


void CMeasureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMeasureDlg)
	DDX_Text(pDX, IDC_MEASURE_TEXT_EDIT, m_MeasureProperty);
	DDX_Text(pDX, IDC_MEASURE_VALUE_EDIT, m_MeasureValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMeasureDlg, CDialog)
	//{{AFX_MSG_MAP(CMeasureDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMeasureDlg message handlers

void CMeasureDlg::OnCancel() 
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

  CDialog::OnOK();
}
