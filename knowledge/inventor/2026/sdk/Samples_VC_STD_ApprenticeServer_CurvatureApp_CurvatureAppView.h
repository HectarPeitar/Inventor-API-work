// RefBoxAppView.h : interface of the CCurvatureAppView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_REFBOXAPPVIEW_H__B4B9ABCD_6F88_11D3_AE45_00C04F681329__INCLUDED_)
#define AFX_REFBOXAPPVIEW_H__B4B9ABCD_6F88_11D3_AE45_00C04F681329__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCurvatureAppDisplay;

class CCurvatureAppView : public CView
{
protected: // create from serialization only
	CCurvatureAppView();
	DECLARE_DYNCREATE(CCurvatureAppView)

// Attributes
public:
	CCurvatureAppDoc* GetDocument();

///////////////////////// AA ///////////////////////////
public:
	BOOL SetWindowPixelFormat(HDC hDC);
  void DoSelection();
  void Refresh(bool bDeleteCurvatureDisplay = true);

	int m_GLPixelIndex{ 0 };
	CPoint m_LeftDownPos;
	BOOL m_LeftButtonDown;

  CCurvatureAppDisplay* m_pDisplayEngine{ nullptr };
//////////////////////////////// AA //////////////////////

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurvatureAppView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCurvatureAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCurvatureAppView)
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RefBoxAppView.cpp
inline CCurvatureAppDoc* CCurvatureAppView::GetDocument()
   { return (CCurvatureAppDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REFBOXAPPVIEW_H__B4B9ABCD_6F88_11D3_AE45_00C04F681329__INCLUDED_)
