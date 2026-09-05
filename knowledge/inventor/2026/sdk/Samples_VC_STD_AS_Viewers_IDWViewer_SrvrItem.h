// SrvrItem.h : interface of the CIDWViewerSrvrItem class
//

#if !defined(AFX_SRVRITEM_H__F98FA8DB_ACE5_11D3_A478_00C04F6B9531__INCLUDED_)
#define AFX_SRVRITEM_H__F98FA8DB_ACE5_11D3_A478_00C04F6B9531__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIDWViewerSrvrItem : public COleServerItem
{
	DECLARE_DYNAMIC(CIDWViewerSrvrItem)

// Constructors
public:
	CIDWViewerSrvrItem(CIDWViewerDoc* pContainerDoc);

// Attributes
	CIDWViewerDoc* GetDocument() const
		{ return (CIDWViewerDoc*)COleServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIDWViewerSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CIDWViewerSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRVRITEM_H__F98FA8DB_ACE5_11D3_A478_00C04F6B9531__INCLUDED_)
