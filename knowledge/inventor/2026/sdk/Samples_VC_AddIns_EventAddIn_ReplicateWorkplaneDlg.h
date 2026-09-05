#ifndef _ReplicateWorkplaneDlg_
#define _ReplicateWorkplaneDlg_


/////////////////////////////////////////////////////////////////////////////
// ReplicateWorkplaneDialog
//
// This defines the code needed for the Replicate Workplane dialog.
//
/////////////////////////////////////////////////////////////////////////////


class ReplicateWorkplaneCmd;

class ReplicateWorkplaneDialog : public CDialog
{
// Construction
public:
	ReplicateWorkplaneDialog(InteractionEventsObject* pEvents, 
						ReplicateWorkplaneCmd*  pSampleCommand,
						CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ApiNonModalDialog)
	enum { IDD = IDD_REPLICATEWORKPLANE };
	CButton	m_OkButton;
	CButton	m_CancelButton;
	CButton	m_SelectButton;
	CString	m_csOccurence;
	CString	m_csOffset;
	//}}AFX_DATA

	BOOL OnInitDialog();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ReplicateWorkplaneDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ReplicateWorkplaneDialog)
	afx_msg void OnChangeOccurence();
	afx_msg void OnSetfocusOccurence();
	afx_msg void OnChangeOffset();
	afx_msg void OnSetfocusOffset();
	afx_msg void OnSelectButton();
	virtual void OnCancel();
	virtual void OnOK();

	USE_INV_REGDLL_HANDLING(CRegHandling)

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	InteractionEventsObject* m_pEvents{ nullptr };
	ReplicateWorkplaneCmd*  m_pSampleCommand{ nullptr };
	CComPtr<View> m_pActiveView;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void SetActiveView(CComPtr<View>& pActiveView);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif 