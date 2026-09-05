#if !defined(AFX_PatternSketchDialog_H__68510893_6456_490E_B9EB_49FCD7F1BED6__INCLUDED_)
#define AFX_PatternSketchDialog_H__68510893_6456_490E_B9EB_49FCD7F1BED6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PatternSketchDialog.h : header file
//

class PatternSketchCmd;

/////////////////////////////////////////////////////////////////////////////
// PatternSketchDialog dialog

class PatternSketchDialog : public CDialog
{
// Construction
public:
	PatternSketchDialog(InteractionEventsObject* pEvents, 
						PatternSketchCmd*  pSampleCommand,
						CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PatternSketchDialog)
	enum { IDD = IDD_PATTERNSKETCH };
	CButton	m_OkButton;
	CButton	m_CancelButton;
	CButton	m_SelectButton;
	CString	m_Edit;
	CString m_csXOccurence;
	CString m_csYOccurence;
	CString m_csXOffset;
	CString m_csYOffset;
	//}}AFX_DATA

	BOOL OnInitDialog();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PatternSketchDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PatternSketchDialog();
	afx_msg void OnChangeXOccurence();
	afx_msg void OnSetfocusXOccurence();

	afx_msg void OnChangeYOccurence();
	afx_msg void OnSetfocusYOccurence();

	afx_msg void OnChangeXOffset();
	afx_msg void OnSetfocusXOffset();

	afx_msg void OnChangeYOffset();
	afx_msg void OnSetfocusYOffset();

	afx_msg void OnSelectButton();
	virtual void OnCancel();
	virtual void OnOK();

	USE_INV_REGDLL_HANDLING(CRegHandling)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CComPtr<InteractionEventsObject> m_pEvents;
	PatternSketchCmd*  m_pSampleCommand{ nullptr };
	CComPtr<View> m_pActiveView;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void SetActiveView(CComPtr<View>& pActiveView);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PatternSketchDialog_H__68510893_6456_490E_B9EB_49FCD7F1BED6__INCLUDED_)
