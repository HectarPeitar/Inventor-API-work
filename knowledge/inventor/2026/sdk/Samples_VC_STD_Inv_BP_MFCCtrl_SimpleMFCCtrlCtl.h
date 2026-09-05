#if !defined(AFX_SIMPLEMFCCONTROLCTL_H__4C2CC578_158A_4C5E_B3EE_B27B37D601B0__INCLUDED_)
#define AFX_SIMPLEMFCCONTROLCTL_H__4C2CC578_158A_4C5E_B3EE_B27B37D601B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// SIMPLEMFCCONTROLCtl.h : Declaration of the CSIMPLEMFCCONTROLCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROLCtrl : See SIMPLEMFCCONTROLCtl.cpp for implementation.

class CSIMPLEMFCCONTROLCtrl : public COleControl
{
	DECLARE_DYNCREATE(CSIMPLEMFCCONTROLCtrl)

// Constructor
public:
	CSIMPLEMFCCONTROLCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSIMPLEMFCCONTROLCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CSIMPLEMFCCONTROLCtrl();

	DECLARE_OLECREATE_EX(CSIMPLEMFCCONTROLCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CSIMPLEMFCCONTROLCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CSIMPLEMFCCONTROLCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CSIMPLEMFCCONTROLCtrl)		// Type name and misc status

	// Subclassed control support
	BOOL IsSubclassedControl();
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

// Message maps
	//{{AFX_MSG(CSIMPLEMFCCONTROLCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CSIMPLEMFCCONTROLCtrl)
	afx_msg BOOL AddText(LPCTSTR text);
	afx_msg void ClearLBoxContents();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CSIMPLEMFCCONTROLCtrl)
	void FireContentChanged()
		{FireEvent(eventidContentChanged,EVENT_PARAM(VTS_NONE));}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CSIMPLEMFCCONTROLCtrl)
	dispidAddText = 1L,
	dispidClear = 2L,
	eventidContentChanged = 1L,
	//}}AFX_DISP_ID
	};

private:
	CListBox  m_listBox;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEMFCCONTROLCTL_H__4C2CC578_158A_4C5E_B3EE_B27B37D601B0__INCLUDED)
