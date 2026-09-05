//{{AFX_INCLUDES()
#include "avviewx.h"
//}}AFX_INCLUDES
#if !defined(AFX_IDWxView_H__EF950EC6_EF09_11D3_A484_00C04F6B9531__INCLUDED_)
#define AFX_IDWxView_H__EF950EC6_EF09_11D3_A484_00C04F6B9531__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IDWxView.h : header file
//

#pragma warning(disable : 4192) // automatically excluding 'name' while importing type library 'library'
#pragma warning(disable : 4278) // 'name':identifier in type library 'library' is already a macro

#include "InventorUtils.h"

/////////////////////////////////////////////////////////////////////////////
// IDWxView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class IDWxView : public CFormView
{
protected:
	IDWxView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(IDWxView)

// Form Data
public:
	//{{AFX_DATA(IDWxView)
	enum { IDD = IDD_DRAWING };
	CAvViewX	m_AvView;
	
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(IDWxView)
	public:
	virtual void OnInitialUpdate();
	afx_msg void OnEditchangeSheetlist();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

  void OnDestroy();
  void OnSize(UINT nType, int cx, int cy);
  BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
						DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
						UINT nID, CCreateContext* pContext);
  void ViewSheet(int nIndex);
  CDialogBar m_DialogBar;
  CComPtr<ApprenticeServer> m_spApp;
  CComPtr<Sheets> m_spSheets;
  CComBSTR m_strIDWDisplayName;
  bool PopulateSheetList();  
// Implementation
protected:
	virtual ~IDWxView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(IDWxView)
	afx_msg void OnEditRefresh();
	afx_msg void OnPaint();
	afx_msg void OnFileView();
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
    bool m_bViewerAvailable{false};
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IDWxView_H__EF950EC6_EF09_11D3_A484_00C04F6B9531__INCLUDED_)
