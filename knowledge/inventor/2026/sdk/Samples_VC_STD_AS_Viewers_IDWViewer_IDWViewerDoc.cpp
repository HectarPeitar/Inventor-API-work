// IDWViewerDoc.cpp : implementation of the CIDWViewerDoc class
//

#include "stdafx.h"
 

#include "IDWViewerDoc.h"
#include "SrvrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIDWViewerDoc

IMPLEMENT_DYNCREATE(CIDWViewerDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(CIDWViewerDoc, COleServerDoc)
	//{{AFX_MSG_MAP(CIDWViewerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIDWViewerDoc construction/destruction

CIDWViewerDoc::CIDWViewerDoc()
{
	// Use OLE compound files
	EnableCompoundFile();


}

CIDWViewerDoc::~CIDWViewerDoc()
{
}

BOOL CIDWViewerDoc::OnNewDocument()
{
	if (!COleServerDoc::OnNewDocument())
		return FALSE;


	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CIDWViewerDoc server implementation

COleServerItem* CIDWViewerDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CIDWViewerSrvrItem* pItem = new CIDWViewerSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}


void CIDWViewerDoc::SaveIDWFile(CIDWViewerDoc * pDoc, CArchive& ar)
{
    CFile cfIn;
    CFileException cfFileException;
    TCHAR* pBuff = NULL;
    int iRet = TRUE;
    int nFileLen{ 0 };

    TRY
    {
        CString strFile = pDoc->GetPathName();
        CFileException cfFileException;
        BOOL bTemp = cfIn.Open((LPCTSTR)strFile,
                    CFile::modeRead | 
                    CFile::shareDenyNone,
                    &cfFileException);
        if (!bTemp) 
            return ;

        nFileLen = cfIn.GetLength();
        if (nFileLen == 0) {
            AfxThrowMemoryException();
        }

        TCHAR* pBuff = NULL;
        const int knTfBUFLEN = 0x2000;
        int nBufLen = min(nFileLen,  knTfBUFLEN);
        pBuff = new TCHAR[nBufLen];
        if (pBuff == NULL) {
            AfxThrowMemoryException();
            return;
        }

        int nLen = nBufLen;
        while (nLen == nBufLen) {
            nLen = cfIn.Read(pBuff, nBufLen); // at the end, nLen will be smaller than nBufLen
            if (nLen)
                ar.Write(pBuff, nLen);
        }
        delete []pBuff;
        pBuff = NULL;
        ar.Flush();
    }
    CATCH (CException, e)
    {
        iRet = FALSE;
    }
    END_CATCH

    cfIn.Close();
}



/////////////////////////////////////////////////////////////////////////////
// CIDWViewerDoc serialization

void CIDWViewerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		SaveIDWFile(this,ar);
	}
	else
	{
		// nothing to load
	}
}

/////////////////////////////////////////////////////////////////////////////
// CIDWViewerDoc diagnostics

#ifdef _DEBUG
void CIDWViewerDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}

void CIDWViewerDoc::Dump(CDumpContext& dc) const
{
	COleServerDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIDWViewerDoc commands
