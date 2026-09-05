#pragma once

class CMFCBrowserPanesDlg;

class CBrowserPaneEvents : public CCmdTarget
{
	DECLARE_DYNCREATE(CBrowserPaneEvents)

	CBrowserPaneEvents(CMFCBrowserPanesDlg* pDlg = NULL); 
	virtual ~CBrowserPaneEvents();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBrowserPaneEvents)
	//}}AFX_VIRTUAL

// Implementation
protected:

	CMFCBrowserPanesDlg* m_pParent{ nullptr };
	
	void ActivateEvent();
	void DeactivateEvent();
	void OnHelp(EventTimingEnum BeforeOrAfter, NameValueMap * pContext, HandlingCodeEnum * HandlingCode);
	
	// Generated message map functions
	//{{AFX_MSG(CBrowserPaneEvents)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

class CApplicationEvents : public CCmdTarget
{
	DECLARE_DYNCREATE(CApplicationEvents)

	CApplicationEvents(CMFCBrowserPanesDlg* pDlg = NULL); 
	virtual ~CApplicationEvents();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CApplicationEvents)
	//}}AFX_VIRTUAL

// Implementation
protected:

	CMFCBrowserPanesDlg* m_pParent{ nullptr };
	
	void QuitEvent();

	// Generated message map functions
	//{{AFX_MSG(CApplicationEvents)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};