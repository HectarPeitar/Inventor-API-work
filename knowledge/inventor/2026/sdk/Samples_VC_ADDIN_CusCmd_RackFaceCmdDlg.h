#if !defined (AFX_RACKFACECMDDLG_H__EE1E2038_9BF4_43B5_B40B_4653675A023C__INCLUDED_)
#define AFX_RACKFACECMDDLG_H__EE1E2038_9BF4_43B5_B40B_4653675A023C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RackFaceCmdDlg.h : header file
//

class CRackFaceCmd;

/////////////////////////////////////////////////////////////////////////////
// RackFaceCmdDlg dialog

class RackFaceCmdDlg : public CDialog
{
// Construction
public:
	RackFaceCmdDlg(Application* pApplication, CRackFaceCmd* pRackFaceCmd, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(RackFaceCmdDlg)
	enum { IDD = IDD_RACKFACEDIALOG };
	CButton	m_RackSymmetricExtentsButton;
	CButton	m_RackNegativeExtentsButton;
	CButton	m_RackPositiveExtentsButton;
	CButton	m_HelpButton;
	CButton	m_SelectRackFaceButton;
	CButton	m_SelectRackDirectionButton;
	CButton	m_CancelButton;
	CButton	m_OKButton;
	CString	m_strRackHeight;
	CString	m_strRackWidth;
	CString	m_strNoTeeth;
	CString	m_strRackExtents;
	int		m_iRackExtentsDirection{ 0 };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RackFaceCmdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RackFaceCmdDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelectRackDirectionButton();
	afx_msg void OnSelectRackFaceButton();
	afx_msg void OnDestroy();
	afx_msg void OnHelpButton();
	afx_msg void OnChangeTeethNumberEdit();
	afx_msg void OnChangeRackHeightEdit();
	afx_msg void OnChangeRackWidthEdit();
	afx_msg void OnChangeRackExtentsEdit();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnRackNegativeExtentsButton();
	afx_msg void OnRackPositiveExtentsButton();
	afx_msg void OnRackSymmetricExtentsButton();

	USE_INV_REGDLL_HANDLING(CRegHandling)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CComPtr<Application> m_pApplication;
	CRackFaceCmd* m_pRackFaceCmd{ nullptr };

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RACKFACECMDDLG_H__EE1E2038_9BF4_43B5_B40B_4653675A023C__INCLUDED_)
