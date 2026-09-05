// ApprenticeViewerMDIDoc.cpp : implementation of the CApprenticeViewerMDIDoc class
//

#include "stdafx.h"
#include "ApprenticeViewerMDIDoc.h"

#include "ApprenticeViewerMDI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CApprenticeViewerMDIDoc

IMPLEMENT_DYNCREATE(CApprenticeViewerMDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CApprenticeViewerMDIDoc, CDocument)
	//{{AFX_MSG_MAP(CApprenticeViewerMDIDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CApprenticeViewerMDIDoc construction/destruction

CApprenticeViewerMDIDoc::CApprenticeViewerMDIDoc()
{
	// TODO: add one-time construction code here
}

CApprenticeViewerMDIDoc::~CApprenticeViewerMDIDoc()
{
}

DocumentTypeEnum CApprenticeViewerMDIDoc::GetType()
{
	DocumentTypeEnum docType;

	if (m_pAppDoc)
		m_pAppDoc->get_DocumentType(&docType);
	
	return docType;
}

BOOL CApprenticeViewerMDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}


BOOL CApprenticeViewerMDIDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	CWinApp *pWinApp = AfxGetApp();

	CApprenticeViewerMDIApp *pApp = dynamic_cast<CApprenticeViewerMDIApp *>(pWinApp);
	
	if (pApp)
	{
		CComPtr<ApprenticeServer> pApprenticeServer = pApp->GetApprenticeServer();

		CString filename = lpszPathName;
		CComBSTR filenameBSTR((LPCTSTR)filename);

		pApprenticeServer->Open(filenameBSTR, &m_pAppDoc);
		if (m_pAppDoc == NULL)
		{	
			AfxMessageBox(L"Failed to open the specified document.");
			return FALSE;
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CApprenticeViewerMDIDoc serialization

void CApprenticeViewerMDIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CApprenticeViewerMDIDoc diagnostics

#ifdef _DEBUG
void CApprenticeViewerMDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CApprenticeViewerMDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CApprenticeViewerMDIDoc commands

CComPtr<ApprenticeServerDocument> CApprenticeViewerMDIDoc::GetApprenticeDocument()
{
	return m_pAppDoc;
}
