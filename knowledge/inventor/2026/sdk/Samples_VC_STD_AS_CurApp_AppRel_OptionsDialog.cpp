// OptionsDialog.cpp : implementation file
//

#include "stdafx.h"

#include "../CurvatureApp.h"

#include "optionsdialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog dialog


COptionsDialog::COptionsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsDialog)
	m_chordHtTol = 0.01;
	m_shadedChecked = TRUE;
	m_edgeChecked = FALSE;
	m_selectionTolerance = 2;
	//}}AFX_DATA_INIT
}

void COptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDialog)
	DDX_Text(pDX, IDC_CHT_EDIT, m_chordHtTol);
	DDV_MinMaxDouble(pDX, m_chordHtTol, 0., 1.);
	DDX_Check(pDX, IDC_SHADED_CHECK, m_shadedChecked);
	DDX_Check(pDX, IDC_EDGE_CHECK, m_edgeChecked);
	DDX_Text(pDX, IDC_SELTOL_EDIT, m_selectionTolerance);
	DDV_MinMaxUInt(pDX, m_selectionTolerance, 1, 10);
	//}}AFX_DATA_MAP

	// Enable/disable edge and shaded display check boxes. If edge
	// display is turned off, then we cannot allow shaded display to
	// be turned off. Conversely, if shaded display is turned off,
	// then we cannot allow edge display to be turned off.
	//
	GetDlgItem(IDC_SHADED_CHECK)->EnableWindow(m_edgeChecked);
	GetDlgItem(IDC_EDGE_CHECK)->EnableWindow(m_shadedChecked);
}


BEGIN_MESSAGE_MAP(COptionsDialog, CDialog)
	//{{AFX_MSG_MAP(COptionsDialog)
	ON_BN_CLICKED(IDC_SHADED_CHECK, OnShadedCheckClick)
	ON_BN_CLICKED(IDC_EDGE_CHECK, OnEdgeCheckClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog message handlers

double COptionsDialog::GetChordalHeightTolerance() const
{
  return m_chordHtTol;
}

UINT COptionsDialog::GetSelectionTolerance() const
{
  return m_selectionTolerance;
}

BOOL COptionsDialog::IsShadedDisplayOn() const
{
  return m_shadedChecked;
}

BOOL COptionsDialog::IsEdgeDisplayOn() const
{
  return m_edgeChecked;
}

void COptionsDialog::SetShadedDisplay(BOOL bOn)
{
  m_shadedChecked = bOn;
}

void COptionsDialog::SetEdgeDisplay(BOOL bOn)
{
  m_edgeChecked = bOn;
}

void COptionsDialog::OnShadedCheckClick() 
{
  m_shadedChecked = !m_shadedChecked;

  UpdateData();
}

void COptionsDialog::OnEdgeCheckClick() 
{
  m_edgeChecked = !m_edgeChecked;

  UpdateData();
}
