// PatternSketchDialog.cpp : implementation file
//

#include "stdafx.h"
#include "patternsketch.h"
#include "patternsketchDlg.h"
#include "rxsamplecommand.h"
#include "resource.h"
#include "PatternSketchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PatternSketchDialog dialog


PatternSketchDialog::PatternSketchDialog(InteractionEventsObject* pEvents, PatternSketchCmd*  pSampleCommand, CWnd* pParent /*=NULL*/)
	: CDialog(PatternSketchDialog::IDD, pParent), m_pEvents(pEvents), m_pSampleCommand(pSampleCommand)
{
	//{{AFX_DATA_INIT(PatternSketchDialog)
	m_csXOccurence = _T("2");
	m_csYOccurence = _T("2");
	m_csYOffset = _T("1");
	m_csXOffset = _T("1");
	//}}AFX_DATA_INIT
}


void PatternSketchDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PatternSketchDialog)
	DDX_Control(pDX, IDOK, m_OkButton);
	DDX_Control(pDX, IDCANCEL, m_CancelButton);
	DDX_Control(pDX, IDC_CURVESELECT_BTN, m_SelectButton);
	DDX_Text(pDX, IDC_XOCCURENCE_CTL, m_csXOccurence);
	DDX_Text(pDX, IDC_YOCCURENCE_CTL, m_csYOccurence);
	DDX_Text(pDX, IDC_XOFFSET_CTL, m_csXOffset);
	DDX_Text(pDX, IDC_YOFFSET_CTL, m_csYOffset);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PatternSketchDialog, CDialog)
	//{{AFX_MSG_MAP(PatternSketchDialog)
	ON_EN_CHANGE(IDC_XOCCURENCE_CTL, OnChangeXOccurence)
	ON_EN_SETFOCUS(IDC_XOCCURENCE_CTL, OnSetfocusXOccurence)

	ON_EN_CHANGE(IDC_YOCCURENCE_CTL, OnChangeYOccurence)
	ON_EN_SETFOCUS(IDC_YOCCURENCE_CTL, OnSetfocusYOccurence)

	ON_EN_CHANGE(IDC_XOFFSET_CTL, OnChangeXOffset)
	ON_EN_SETFOCUS(IDC_XOFFSET_CTL, OnSetfocusXOffset)

	ON_EN_CHANGE(IDC_YOFFSET_CTL, OnChangeYOffset)
	ON_EN_SETFOCUS(IDC_YOFFSET_CTL, OnSetfocusYOffset)

	ON_BN_CLICKED(IDC_CURVESELECT_BTN, OnSelectButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL PatternSketchDialog::OnInitDialog()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	CDialog::OnInitDialog();
	m_SelectButton.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON1));
	GetDlgItem(IDOK)->EnableWindow(false);
	m_SelectButton.SetCheck(true);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// PatternSketchDialog message handlers

void PatternSketchDialog::OnChangeXOccurence() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	CString cDist;
	GetDlgItem(IDC_XOCCURENCE_CTL)->GetWindowText(cDist);

	long numOccurrences;
	numOccurrences = _tcstol(cDist, NULL,10);

	m_pSampleCommand->SetXOccurences(numOccurrences);	
}

void PatternSketchDialog::OnSetfocusXOccurence() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	VARIANT_BOOL bSelActive = VARIANT_FALSE;
	m_pEvents->put_SelectionActive(bSelActive);
	m_SelectButton.SetCheck(false);
}

void PatternSketchDialog::OnChangeYOccurence() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	CString cDist;
	GetDlgItem(IDC_YOCCURENCE_CTL)->GetWindowText(cDist);

	long numOccurrences;
	numOccurrences = _tcstol(cDist, NULL,10);

	m_pSampleCommand->SetYOccurences(numOccurrences);	
}

void PatternSketchDialog::OnSetfocusYOccurence() 
{	
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	VARIANT_BOOL bSelActive = VARIANT_FALSE;
	m_pEvents->put_SelectionActive(bSelActive);
	m_SelectButton.SetCheck(false);
}

void PatternSketchDialog::OnChangeXOffset() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	CString cDist;
	GetDlgItem(IDC_XOFFSET_CTL)->GetWindowText(cDist);

	double offset{0.0};
	offset = _tcstod(cDist, NULL);
	m_pSampleCommand->SetXOffset(offset);
}

void PatternSketchDialog::OnSetfocusXOffset() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	VARIANT_BOOL bSelActive = VARIANT_FALSE;
	m_pEvents->put_SelectionActive(bSelActive);
	m_SelectButton.SetCheck(false);	
}

void PatternSketchDialog::OnChangeYOffset() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	CString cDist;
	GetDlgItem(IDC_YOFFSET_CTL)->GetWindowText(cDist);

	double offset{0.0};
	offset = _tcstod(cDist, NULL);
	m_pSampleCommand->SetYOffset(offset);	
}

void PatternSketchDialog::OnSetfocusYOffset() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	VARIANT_BOOL bSelActive = VARIANT_FALSE;
	m_pEvents->put_SelectionActive(bSelActive);
	m_SelectButton.SetCheck(false);
}

void PatternSketchDialog::OnSelectButton() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	VARIANT_BOOL bSelActive = VARIANT_TRUE;
	m_pEvents->put_SelectionActive(bSelActive);
	m_SelectButton.SetCheck(true);	
}

void PatternSketchDialog::OnCancel() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	CDialog::OnCancel();
	m_pSampleCommand->EndCommand();
}

void PatternSketchDialog::OnOK() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	CDialog::OnOK();
	m_pSampleCommand->ExecutePatternCmd();
}

void PatternSketchDialog::SetActiveView(CComPtr<View>& pActiveView) 
{
	m_pActiveView = CComQIPtr<View>(pActiveView);
}

BOOL PatternSketchDialog::PreTranslateMessage(MSG* pMsg)
{
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
