// ApprenticeViewerMDIDoc.h : interface of the CApprenticeViewerMDIDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPRENTICEVIEWERMDIDOC_H__2DF08CA0_10D1_40AB_8673_F597F3470997__INCLUDED_)
#define AFX_APPRENTICEVIEWERMDIDOC_H__2DF08CA0_10D1_40AB_8673_F597F3470997__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CApprenticeViewerMDIDoc : public CDocument
{
protected: // create from serialization only
	CApprenticeViewerMDIDoc();
	DECLARE_DYNCREATE(CApprenticeViewerMDIDoc)

// Attributes
public:
	CComPtr<ApprenticeServerDocument> GetApprenticeDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CApprenticeViewerMDIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CApprenticeViewerMDIDoc();

	DocumentTypeEnum GetType();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CApprenticeViewerMDIDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CComPtr<ApprenticeServerDocument>	m_pAppDoc;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPRENTICEVIEWERMDIDOC_H__2DF08CA0_10D1_40AB_8673_F597F3470997__INCLUDED_)
