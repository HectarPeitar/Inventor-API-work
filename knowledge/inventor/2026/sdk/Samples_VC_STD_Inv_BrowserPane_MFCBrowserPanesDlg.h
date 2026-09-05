// MFCBrowserPanesDlg.h : header file
//

#if !defined(AFX_MFCBROWSERPANESDLG_H__EC249920_F7ED_49CD_9663_D7832B5AD8A9__INCLUDED_)
#define AFX_MFCBROWSERPANESDLG_H__EC249920_F7ED_49CD_9663_D7832B5AD8A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBrowserPaneEvents;
class CApplicationEvents;

#include "SimpleMFCControl.h"

/////////////////////////////////////////////////////////////////////////////
// CMFCBrowserPanesDlg dialog

class CMFCBrowserPanesDlg : public CDialog
{
// Construction
public:
	CMFCBrowserPanesDlg(CWnd* pParent = NULL);	// standard constructor
	~CMFCBrowserPanesDlg();

	void AddListBoxText(CString& text);
	LRESULT OnKickIdle(WPARAM wp, LPARAM lCount);
	afx_msg void OnUpdateConnectBtn(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddBrowserBtn(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePaneAddedState(CCmdUI* pCmdUI);
	void ShutDownEventSinks();
	void OnInventorExit();

// Dialog Data
	//{{AFX_DATA(CMFCBrowserPanesDlg)
	enum { IDD = IDD_MFCBROWSERPANES_DIALOG };
	CListBox	m_listBox;
	CEdit	m_editText;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCBrowserPanesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CComPtr<IUnknown>			m_pAppUnk;
	CComPtr<Application>		m_pApplication;
	CComPtr<Documents>			m_pDocs;
	CComPtr<Document>			m_pDocument;
	CComPtr<BrowserPaneObject>	m_pBrowserPane;
	CComPtr<ApplicationEventsObject> m_spAppEvents;
	CSIMPLEMFCCONTROL			m_control;
	DWORD						m_dwCookie;
	CMFCControlEvents*			m_pEvents{ nullptr };
	CBrowserPaneEvents*			m_pBrowserPaneEvents{ nullptr };
	CApplicationEvents*			m_pApplicationEvents{ nullptr };
	DWORD						m_dwAppEventCookie;
	DWORD						m_dwBrowserPaneEventCookie;
	bool						m_bConnected{false};
	bool						m_bPaneAdded{false};
	HICON						m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMFCBrowserPanesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnConnect();
	afx_msg void OnAddpane();
	afx_msg void OnAddtext();
	afx_msg void OnClearcontents();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCBROWSERPANESDLG_H__EC249920_F7ED_49CD_9663_D7832B5AD8A9__INCLUDED_)
