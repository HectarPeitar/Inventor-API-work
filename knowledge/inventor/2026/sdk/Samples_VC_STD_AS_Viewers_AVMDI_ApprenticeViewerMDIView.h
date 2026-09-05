// ApprenticeViewerMDIView.h : interface of the CApprenticeViewerMDIView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPRENTICEVIEWERMDIVIEW_H__44195606_3B9D_440B_A7F4_2037027872FB__INCLUDED_)
#define AFX_APPRENTICEVIEWERMDIVIEW_H__44195606_3B9D_440B_A7F4_2037027872FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CApprenticeViewerMDIView : public CView
{
protected: // create from serialization only
	CApprenticeViewerMDIView();
	DECLARE_DYNCREATE(CApprenticeViewerMDIView)

// Attributes
public:
	CApprenticeViewerMDIDoc* GetDocument();
	void SetClientView(CComPtr<ClientView> pClientView);
	CComPtr<ClientView> GetClientView();

// Operations
public:
	void SetDisplayMode(DisplayModeEnum mode);
	void SetPerspective(bool perspective);
    void SetViewingMode(ViewOperationTypeEnum mode);
	void Fit();
	void ResetView();
	void SelectionChanged(long index);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CApprenticeViewerMDIView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CApprenticeViewerMDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CApprenticeViewerMDIView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnUpdateOrientation(CCmdUI* pCmdUI);
	afx_msg void OnOrientation(UINT nCommandID);
	afx_msg void OnUpdateOverlay(CCmdUI* pCmdUI);
	afx_msg void OnOverlay(UINT nCommandID);
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()

private:
	CComPtr<ClientViews> GetClientViews();
	void DefaultView();
	CComPtr<TransientGeometry> GetTransientGeometry();

	DocumentTypeEnum		m_docType;
	CComPtr<ClientView>		m_pClientView;
	bool					m_perspective{false};
	DisplayModeEnum			m_displayMode;
	long					m_sheetIndex;
	bool					m_interactive{false};
	CPoint					m_previousPoint;
	ViewOperationTypeEnum	m_viewingMode;
	bool					m_mouseWheelDown{false};

	CString					m_text;
	CPoint					m_textPoint;
	bool					m_focusText{false};
	bool					m_movingText{false};
	bool					m_showOverlay{false};
};

#ifndef _DEBUG  // debug version in ApprenticeViewerMDIView.cpp
inline CApprenticeViewerMDIDoc* CApprenticeViewerMDIView::GetDocument()
   { return (CApprenticeViewerMDIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPRENTICEVIEWERMDIVIEW_H__44195606_3B9D_440B_A7F4_2037027872FB__INCLUDED_)
