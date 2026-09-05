// DebugBodyDlg.cpp : implementation file
//

#include "stdafx.h"

#include "../CurvatureApp.h"

#include "debugbodydlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDebugBodyDlg dialog


CDebugBodyDlg::CDebugBodyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDebugBodyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDebugBodyDlg)
	m_EdgesCount = _T("");
	m_FacesCount = _T("");
	m_ShellsCount = _T("");
	m_VerticesCount = _T("");
	m_Volume = _T("");
	m_FileName = _T("");
	//}}AFX_DATA_INIT
}


void CDebugBodyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDebugBodyDlg)
	DDX_Text(pDX, IDC_EDGES, m_EdgesCount);
	DDX_Text(pDX, IDC_FACES, m_FacesCount);
	DDX_Text(pDX, IDC_SHELLS, m_ShellsCount);
	DDX_Text(pDX, IDC_VERTICES, m_VerticesCount);
	DDX_Text(pDX, IDC_VOLUME, m_Volume);
	DDX_Text(pDX, IDC_FILE_NAME, m_FileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDebugBodyDlg, CDialog)
	//{{AFX_MSG_MAP(CDebugBodyDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDebugBodyDlg message handlers
