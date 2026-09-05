// RackFaceCmdDlg.cpp : implementation file
//

#include "StdAfx.h"
#include "Resource.h"
#include "RackFaceCmdDlg.h"
#include "RackFaceCmd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RackFaceCmdDlg dialog

RackFaceCmdDlg::RackFaceCmdDlg(Application* pApplication, CRackFaceCmd* pRackFaceCmd, CWnd* pParent /*=NULL*/)
	: CDialog(RackFaceCmdDlg::IDD, pParent), m_pApplication(pApplication), m_pRackFaceCmd(pRackFaceCmd)
{
	//{{AFX_DATA_INIT(RackFaceCmdDlg)
	m_strRackHeight = _T("0.1");
	m_strRackWidth = _T("0.50");
	m_strNoTeeth = _T("5");
	m_strRackExtents = _T("1.0");
	m_iRackExtentsDirection = 0;
	//}}AFX_DATA_INIT
}


void RackFaceCmdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RackFaceCmdDlg)
	DDX_Control(pDX, IDC_RACKSYMMETRICEXTENTSRADIO, m_RackSymmetricExtentsButton);
	DDX_Control(pDX, IDC_RACKNEGATIVEEXTENTSRADIO, m_RackNegativeExtentsButton);
	DDX_Control(pDX, IDC_RACKPOSITIVEEXTENTSRADIO, m_RackPositiveExtentsButton);
	DDX_Control(pDX, IDC_HELPBUTTON, m_HelpButton);
	DDX_Control(pDX, IDC_SELECTRACKFACECHECKBOX, m_SelectRackFaceButton);
	DDX_Control(pDX, IDC_SELECTRACKDIRECTIONCHECKBOX, m_SelectRackDirectionButton);
	DDX_Control(pDX, IDCANCEL, m_CancelButton);
	DDX_Control(pDX, IDOK, m_OKButton);
	DDX_Text(pDX, IDC_RACKHEIGHTEDIT, m_strRackHeight);
	DDX_Text(pDX, IDC_RACKWIDTHEDIT, m_strRackWidth);
	DDX_Text(pDX, IDC_TEETHNUMBEREDIT, m_strNoTeeth);
	DDX_Text(pDX, IDC_RACKEXTENTSEDIT, m_strRackExtents);
	DDX_Radio(pDX, IDC_RACKNEGATIVEEXTENTSRADIO, m_iRackExtentsDirection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RackFaceCmdDlg, CDialog)
	//{{AFX_MSG_MAP(RackFaceCmdDlg)
	ON_BN_CLICKED(IDC_SELECTRACKDIRECTIONCHECKBOX, OnSelectRackDirectionButton)
	ON_BN_CLICKED(IDC_SELECTRACKFACECHECKBOX, OnSelectRackFaceButton)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_HELPBUTTON, OnHelpButton)
	ON_EN_CHANGE(IDC_TEETHNUMBEREDIT, OnChangeTeethNumberEdit)
	ON_EN_CHANGE(IDC_RACKHEIGHTEDIT, OnChangeRackHeightEdit)
	ON_EN_CHANGE(IDC_RACKWIDTHEDIT, OnChangeRackWidthEdit)
	ON_EN_CHANGE(IDC_RACKEXTENTSEDIT, OnChangeRackExtentsEdit)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_RACKNEGATIVEEXTENTSRADIO, OnRackNegativeExtentsButton)
	ON_BN_CLICKED(IDC_RACKPOSITIVEEXTENTSRADIO, OnRackPositiveExtentsButton)
	ON_BN_CLICKED(IDC_RACKSYMMETRICEXTENTSRADIO, OnRackSymmetricExtentsButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RackFaceCmdDlg message handlers

BOOL RackFaceCmdDlg::OnInitDialog() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	CDialog::OnInitDialog();	

	CRect rcDlgRect;

	GetWindowRect(rcDlgRect);
	rcDlgRect.NormalizeRect();

	int iDlgLeft = AfxGetApp()->GetProfileInt(_T("Rack Face Dialog"), _T("Left"), 10);
	int iDlgTop = AfxGetApp()->GetProfileInt(_T("Rack Face Dialog"), _T("Top"), 10);

	MoveWindow(iDlgLeft, iDlgTop, rcDlgRect.Width(), rcDlgRect.Height());

	//set the icons for the radio buttons
	m_SelectRackFaceButton.SetIcon(AfxGetApp()->LoadIcon(IDI_SELECTION));
	m_SelectRackDirectionButton.SetIcon(AfxGetApp()->LoadIcon(IDI_SELECTION));
	m_RackNegativeExtentsButton.SetIcon(AfxGetApp()->LoadIcon(IDI_NEGATIVEEXTENTS));
	m_RackPositiveExtentsButton.SetIcon(AfxGetApp()->LoadIcon(IDI_POSITIVEEXTENTS));
	m_RackSymmetricExtentsButton.SetIcon(AfxGetApp()->LoadIcon(IDI_SYMMETRICEXTENTS));
	m_HelpButton.SetIcon(AfxGetApp()->LoadIcon(IDI_HELP));

	m_OKButton.EnableWindow(FALSE);
	m_SelectRackFaceButton.SetCheck(BST_CHECKED);

	return TRUE;  
}

HBRUSH RackFaceCmdDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	HRESULT hr;

	switch (nCtlColor){

	case CTLCOLOR_EDIT:
	case CTLCOLOR_MSGBOX:
		
		UpdateData(TRUE);

		switch (pWnd->GetDlgCtrlID()){     
		case IDC_TEETHNUMBEREDIT:
		{	
			//check if the new value is valid
			int iNoTeeth = _tstoi((LPCTSTR)m_strNoTeeth);
	
			if (iNoTeeth <= 0)
				pDC->SetTextColor(RGB(255, 0, 0));
			else
				pDC->SetTextColor(RGB(0, 0, 0));

			break;
		}
		case IDC_RACKHEIGHTEDIT:
		{
			//check if the new value is valid
			double dRackHeight{0.0};
			hr = m_pRackFaceCmd->GetValueFromExpression(m_strRackHeight, &dRackHeight);
	
			if (FAILED(hr) || dRackHeight <= 0)
				pDC->SetTextColor(RGB(255, 0, 0));
			else
				pDC->SetTextColor(RGB(0, 0, 0));

			break;
		}
		case IDC_RACKWIDTHEDIT:
		{	
			//check if the new value is valid
			double dRackWidth{0.0};
			hr = m_pRackFaceCmd->GetValueFromExpression(m_strRackWidth, &dRackWidth);

			if (FAILED(hr) || dRackWidth <= 0)
				pDC->SetTextColor(RGB(255, 0, 0));
			else
				pDC->SetTextColor(RGB(0, 0, 0));

			break;
		}
		case IDC_RACKEXTENTSEDIT:
		{	
			//check if the new value is valid
			double dRackExtents{0.0};
			hr = m_pRackFaceCmd->GetValueFromExpression(m_strRackExtents, &dRackExtents);

			if (FAILED(hr) || dRackExtents <= 0)
				pDC->SetTextColor(RGB(255, 0, 0));
			else
				pDC->SetTextColor(RGB(0, 0, 0));

			break;
		}
		}

	}

	return hbr;
}

void RackFaceCmdDlg::OnSelectRackFaceButton() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	//disable rack direction selection button
	m_SelectRackDirectionButton.SetCheck(BST_UNCHECKED);

	//if selected then start face selection
	if (m_SelectRackFaceButton.GetCheck() == BST_CHECKED){
		
		m_pRackFaceCmd->EnableInteraction();

	}
	else
		m_pRackFaceCmd->DisableInteraction();	
		
}

void RackFaceCmdDlg::OnSelectRackDirectionButton() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	//disable rack face selection button
	m_SelectRackFaceButton.SetCheck(BST_UNCHECKED);

	//if selected then start direction selection
	if (m_SelectRackDirectionButton.GetCheck() == BST_CHECKED){

		m_pRackFaceCmd->EnableInteraction();
	}
	else
		m_pRackFaceCmd->DisableInteraction();
	 
}

void RackFaceCmdDlg::OnOK() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr;

	CDialog::OnOK();

	hr = m_pRackFaceCmd->ExecuteCommand();

}

void RackFaceCmdDlg::OnCancel() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr;

	CDialog::OnCancel();

	hr = m_pRackFaceCmd->StopCommand();

}

void RackFaceCmdDlg::OnChangeTeethNumberEdit() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr;

	hr = m_pRackFaceCmd->UpdateCommandStatus();
}

void RackFaceCmdDlg::OnChangeRackHeightEdit() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());
	
	HRESULT hr;

	hr = m_pRackFaceCmd->UpdateCommandStatus();
	
}

void RackFaceCmdDlg::OnChangeRackWidthEdit() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr;

	hr = m_pRackFaceCmd->UpdateCommandStatus();
	
}

void RackFaceCmdDlg::OnChangeRackExtentsEdit() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr;

	hr = m_pRackFaceCmd->UpdateCommandStatus();
	
}

void RackFaceCmdDlg::OnRackNegativeExtentsButton() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr;

	hr = m_pRackFaceCmd->UpdateCommandStatus();

}

void RackFaceCmdDlg::OnRackPositiveExtentsButton() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr;

	hr = m_pRackFaceCmd->UpdateCommandStatus();
	
}

void RackFaceCmdDlg::OnRackSymmetricExtentsButton() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr;

	hr = m_pRackFaceCmd->UpdateCommandStatus();
	
}

void RackFaceCmdDlg::OnHelpButton() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr;

	//get the help manager object
	CComPtr<HelpManager> pHelpManager;
	hr = m_pApplication->get_HelpManager(&pHelpManager);
	if (FAILED(hr)) return;

	//display the start page of the "Inventor API" help
	hr = pHelpManager->DisplayHelpTopic(_bstr_t(_T("ADMAPI_16_0.chm")), _bstr_t(_T("")));
	
}

BOOL RackFaceCmdDlg::PreTranslateMessage(MSG* pMsg) 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr;

	//get the active view
	CComPtr<View> pActiveView;
	hr = m_pApplication->get_ActiveView(&pActiveView);

	if (pActiveView != NULL && (pMsg->message == WM_KEYDOWN || pMsg->message == WM_KEYUP))
	{
		if (pMsg->wParam == VK_F2 || pMsg->wParam == VK_F3 || pMsg->wParam == VK_F4 || pMsg->wParam == VK_F5 || pMsg->wParam == VK_F6 ||  pMsg->wParam == VK_F10)
		{
			long lViewHwnd;
			pActiveView->get_HWND(&lViewHwnd);

			HWND hWnd = CWnd::FromHandle((HWND)lViewHwnd)->GetWindow(GW_CHILD)->GetSafeHwnd();
			if (hWnd != NULL)
			{
				pMsg->hwnd = (HWND)hWnd;
				return FALSE;
			}
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void RackFaceCmdDlg::PostNcDestroy() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	CDialog::PostNcDestroy();

	delete this;
}

void RackFaceCmdDlg::OnDestroy() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	CDialog::OnDestroy();

	CRect rcDlgRect;

	GetWindowRect(rcDlgRect);
	rcDlgRect.NormalizeRect();

	AfxGetApp()->WriteProfileInt(_T("Rack Face Dialog"), _T("Left"), rcDlgRect.left);
	AfxGetApp()->WriteProfileInt(_T("Rack Face Dialog"), _T("Top"), rcDlgRect.top);
	
}


