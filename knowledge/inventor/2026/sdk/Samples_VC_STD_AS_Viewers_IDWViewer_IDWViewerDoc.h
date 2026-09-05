// IDWViewerDoc.h : interface of the CIDWViewerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IDWViewerDOC_H__F98FA8D6_ACE5_11D3_A478_00C04F6B9531__INCLUDED_)
#define AFX_IDWViewerDOC_H__F98FA8D6_ACE5_11D3_A478_00C04F6B9531__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CIDWViewerSrvrItem;

class CIDWViewerDoc : public COleServerDoc
{
protected: // create from serialization only
	CIDWViewerDoc();
	DECLARE_DYNCREATE(CIDWViewerDoc)

// Attributes
public:
	CIDWViewerSrvrItem* GetEmbeddedItem()
		{ return (CIDWViewerSrvrItem*)COleServerDoc::GetEmbeddedItem(); }

// Operations
public:
	static void SaveIDWFile(CIDWViewerDoc * pDoc, CArchive& ar);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIDWViewerDoc)
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL


// Implementation
public:
	virtual ~CIDWViewerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CIDWViewerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IDWViewerDOC_H__F98FA8D6_ACE5_11D3_A478_00C04F6B9531__INCLUDED_)
