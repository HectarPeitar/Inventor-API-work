// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__92EBF1C8_2651_45CD_BC0B_57A6F7C4850A__INCLUDED_)
#define AFX_CHILDFRM_H__92EBF1C8_2651_45CD_BC0B_57A6F7C4850A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CApprenticeViewerMDIView;

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
protected:
	CSplitterWnd m_wndSplitter;
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	CApprenticeViewerMDIView* GetRightPane();
// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	afx_msg void OnUpdateDisplayStyles(CCmdUI* pCmdUI);
	afx_msg void OnDisplayStyle(UINT nCommandID);
	afx_msg void OnUpdateProjectionStyles(CCmdUI* pCmdUI);
	afx_msg void OnProjectionStyle(UINT nCommandID);
	afx_msg void OnUpdateViewingMode(CCmdUI* pCmdUI);
	afx_msg void OnViewingMode(UINT nCommandID);
	DECLARE_MESSAGE_MAP()

private:
	DWORD	m_displayStyle;
	DWORD	m_projectionStyle;
	DWORD	m_viewingMode;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__92EBF1C8_2651_45CD_BC0B_57A6F7C4850A__INCLUDED_)
