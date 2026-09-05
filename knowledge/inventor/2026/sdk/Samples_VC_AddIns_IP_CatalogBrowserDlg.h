#if !defined(AFX_CATALOGBROWSERDLG_H__552EC5E9_A6ED_11D3_B79A_0060B0F159EF__INCLUDED_)
#define AFX_CATALOGBROWSERDLG_H__552EC5E9_A6ED_11D3_B79A_0060B0F159EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CatalogBrowserDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCatalogBrowserDlg dialog

class CCatalogBrowserDlg : public CDialog
{
// Construction
public:
	CCatalogBrowserDlg(CWnd* pParent = NULL);   // standard constructor

	CString& GetCatalogPartFile() { return m_strCatalogPartFile; }

public:
	CString m_Title;

// Dialog Data
	//{{AFX_DATA(CCatalogBrowserDlg)
	enum { IDD = IDD_DIALOG2 };
	CComboBox	m_PartsListCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCatalogBrowserDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  
	// Generated message map functions
	//{{AFX_MSG(CCatalogBrowserDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCatalogPartSelect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

  // member data
	CString m_strCatalogPartFile;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CATALOGBROWSERDLG_H__552EC5E9_A6ED_11D3_B79A_0060B0F159EF__INCLUDED_)
