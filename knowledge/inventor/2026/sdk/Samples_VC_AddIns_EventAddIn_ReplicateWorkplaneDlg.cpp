
/////////////////////////////////////////////////////////////////////////////
// 
// ReplicateWorkplaneDialog.cpp : implementation file
//
// This file implements the Replicate Workplane Dialog.
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "replicateworkplane.h"
#include "replicateworkplanedlg.h"
#include "rxsamplecommand.h"
#include "resource.h"
#include "ReplicateWorkplaneDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

ReplicateWorkplaneDialog::ReplicateWorkplaneDialog(InteractionEventsObject* pEvents, ReplicateWorkplaneCmd*  pSampleCommand, CWnd* pParent /*=NULL*/)
	: CDialog(ReplicateWorkplaneDialog::IDD, pParent), m_pEvents(pEvents), m_pSampleCommand(pSampleCommand)
{
	//{{AFX_DATA_INIT(ReplicateWorkplaneDialog)
	m_csOccurence = _T("1");
	m_csOffset = _T("3");
	//}}AFX_DATA_INIT
}


void ReplicateWorkplaneDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ReplicateWorkplaneDialog)
	DDX_Control(pDX, IDOK, m_OkButton);
	DDX_Control(pDX, IDCANCEL, m_CancelButton);
	DDX_Control(pDX, IDC_WORKPLANE_BTN, m_SelectButton);
	DDX_Text(pDX, IDC_OFFSETDIST_CTL, m_csOffset);
	DDX_Text(pDX, IDC_OCCURENCE_CTL, m_csOccurence);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ReplicateWorkplaneDialog, CDialog)
	//{{AFX_MSG_MAP(ReplicateWorkplaneDialog)
	ON_EN_CHANGE(IDC_OCCURENCE_CTL, OnChangeOccurence)
	ON_EN_SETFOCUS(IDC_OCCURENCE_CTL, OnSetfocusOccurence)
	ON_EN_CHANGE(IDC_OFFSETDIST_CTL, OnChangeOffset)
	ON_EN_SETFOCUS(IDC_OFFSETDIST_CTL, OnSetfocusOffset)
	ON_BN_CLICKED(IDC_WORKPLANE_BTN, OnSelectButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL ReplicateWorkplaneDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_SelectButton.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));
	GetDlgItem(IDOK)->EnableWindow(false);
	m_SelectButton.SetCheck(true);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// ReplicateWorkplaneDialog message handlers
void ReplicateWorkplaneDialog::OnChangeOccurence() 
{
	CString cDist;
	GetDlgItem(IDC_OCCURENCE_CTL)->GetWindowText(cDist);

	long numOccurrences;
	numOccurrences = _tcstol(cDist, NULL,10);

	m_pSampleCommand->SetNumOccurrences(numOccurrences);	
}

void ReplicateWorkplaneDialog::OnSetfocusOccurence() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	VARIANT_BOOL bSelActive = VARIANT_FALSE;
	m_pEvents->put_SelectionActive(bSelActive);
	m_SelectButton.SetCheck(false);	
}


void ReplicateWorkplaneDialog::OnChangeOffset() 
{
	CString cDist;
	GetDlgItem(IDC_OFFSETDIST_CTL)->GetWindowText(cDist);

	double offset{0.0};
	offset = _tcstod(cDist, NULL);
	m_pSampleCommand->SetOffset(offset);	
}

void ReplicateWorkplaneDialog::OnSetfocusOffset() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	VARIANT_BOOL bSelActive = VARIANT_FALSE;
	m_pEvents->put_SelectionActive(bSelActive);
	m_SelectButton.SetCheck(false);	
}

void ReplicateWorkplaneDialog::OnSelectButton() 
{
	VARIANT_BOOL bSelActive = VARIANT_TRUE;
	m_pEvents->put_SelectionActive(bSelActive);
	m_SelectButton.SetCheck(true);
}

void ReplicateWorkplaneDialog::OnCancel() 
{
	CDialog::OnCancel();
	m_pSampleCommand->EndCommand();
}

void ReplicateWorkplaneDialog::OnOK() 
{
	CDialog::OnOK();
	m_pSampleCommand->ExecuteReplicateWorkplaneCmd();
}

void ReplicateWorkplaneDialog::SetActiveView(CComPtr<View>& pActiveView) 
{
	m_pActiveView = CComQIPtr<View>(pActiveView);
}
BOOL ReplicateWorkplaneDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (m_pActiveView != NULL && (pMsg->message == WM_KEYDOWN || pMsg->message == WM_KEYUP))
	{
		if (pMsg->wParam == VK_F2 || pMsg->wParam == VK_F3 || pMsg->wParam == VK_F4 || pMsg->wParam == VK_F5 || pMsg->wParam == VK_F6 ||  pMsg->wParam == VK_F10)
		{
			long lViewHwnd;
			m_pActiveView->get_HWND(&lViewHwnd);

			HWND hWnd = CWnd::FromHandle((HWND)lViewHwnd)->GetWindow(GW_CHILD)->GetSafeHwnd();
			if (hWnd != NULL)
			{
				pMsg->hwnd = (HWND)hWnd;
				return false;
			}
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
