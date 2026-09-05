// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// _DSIMPLEMFCCONTROL wrapper class

#pragma once


class CMFCBrowserPanesDlg;

class CMFCControlEvents : public CCmdTarget
{
	DECLARE_DYNCREATE(CMFCControlEvents)

	CMFCControlEvents(CMFCBrowserPanesDlg* pDlg = NULL); // protected constructor used by dynamic creation
	virtual ~CMFCControlEvents();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCControlEvents)
	//}}AFX_VIRTUAL

// Implementation
protected:

	CMFCBrowserPanesDlg* m_pParent{ nullptr };
	
	void ContentChanged();

	// Generated message map functions
	//{{AFX_MSG(CMFCControlEvents)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

class CSIMPLEMFCCONTROL : public COleDispatchDriver
{
public:
	CSIMPLEMFCCONTROL() {}		// Calls COleDispatchDriver default constructor
	CSIMPLEMFCCONTROL(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CSIMPLEMFCCONTROL(const CSIMPLEMFCCONTROL& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL AddText(LPCTSTR text);
	void Clear();
	void AboutBox();
};


