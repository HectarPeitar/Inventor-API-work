// SrvrItem.cpp : implementation of the CIDWViewerSrvrItem class
//

#include "stdafx.h"
#include "IDWViewer.h"

#include "IDWViewerDoc.h"
#include "SrvrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CIDWViewerApp theApp;

#include "shlwapi.h"


/////////////////////////////////////////////////////////////////////////////
// CIDWViewerSrvrItem implementation

IMPLEMENT_DYNAMIC(CIDWViewerSrvrItem, COleServerItem)

CIDWViewerSrvrItem::CIDWViewerSrvrItem(CIDWViewerDoc* pContainerDoc)
	: COleServerItem(pContainerDoc, TRUE)
{
}

CIDWViewerSrvrItem::~CIDWViewerSrvrItem()
{
}

void CIDWViewerSrvrItem::Serialize(CArchive& ar)
{
	// CIDWViewerSrvrItem::Serialize will be called by the framework if
	//  the item is copied to the clipboard.  This can happen automatically
	//  through the OLE callback OnGetClipboardData.  
  //  We do not save anything for links
  // 

  // Save the whole file if it is embedded
	if (!IsLinkedItem())
	{
		CIDWViewerDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		CIDWViewerDoc::SaveIDWFile(pDoc,ar);
	}
}

BOOL CIDWViewerSrvrItem::OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize)
{
	// Most applications, like this one, only handle drawing the content
	//  aspect of the item.  If you wish to support other aspects, such
	//  as DVASPECT_THUMBNAIL (by overriding OnDrawEx), then this
	//  implementation of OnGetExtent should be modified to handle the
	//  additional aspect(s).

	if (dwDrawAspect != DVASPECT_CONTENT)
		return COleServerItem::OnGetExtent(dwDrawAspect, rSize);

	// CIDWViewerSrvrItem::OnGetExtent is called to get the extent in
	//  HIMETRIC units of the entire item.  The default implementation
	//  here simply returns a hard-coded number of units.

	CIDWViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int nX, nY;
	nX = 2000; // default size
	nY = 2000;
	rSize = CSize(nX, nY);   // 3000 x 3000 HIMETRIC units

	return TRUE;
}

BOOL CIDWViewerSrvrItem::OnDraw(CDC* pDC, CSize& rSize)
{
	// Remove this if you use rSize
	UNREFERENCED_PARAMETER(rSize);

	CIDWViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	// TODO: set mapping mode and extent
	//  (The extent is usually the same as the size returned from OnGetExtent)
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowOrg(0,0);
	pDC->SetWindowExt(40, 60);

  // Place the icon
  HICON hIcon = theApp.LoadIcon(IDR_ACTACATYPE);
  pDC->DrawIcon( 4, 4, hIcon);
  ::DestroyIcon(hIcon);


	//  All drawing takes place in the metafile device context (pDC).
  CString strFile = pDoc->GetPathName();
  CString strShortName;

  ::GetShortPathName(strFile.GetBuffer(_MAX_PATH), strShortName.GetBuffer(_MAX_PATH), _MAX_PATH);
  strShortName.ReleaseBuffer();
  strFile.ReleaseBuffer();

  ::PathStripPath(strShortName.GetBuffer(_MAX_PATH));
  strShortName.ReleaseBuffer();

  // CSize sizeChar = pDC->GetOutputTextExtent(strShortName );
  
  // Set the font. The choice of the font size should depends on the string length
  // but here we are writing only 8.3 names

  ///////////////////////////////////////////////////////////
  // TBD: The strings need to be localized in future.
  // The font name is not being used currently
  CFont aFont;
	CString fontName;
	fontName.LoadString(IDS_ICONFONTNAME);
  ///////////////////////////////////////////////////////////

	CString fontSize;
	fontSize.LoadString(IDS_ICONFONTSIZE);

	int fontSz = _ttoi(fontSize);

	aFont.CreatePointFont( fontSz, _T("") );

	CFont* pFont = pDC->SelectObject(&aFont);

  COLORREF whiteColor = RGB(255,255,255);
  COLORREF blackColor = RGB(0,0,0);
  pDC->SetBkMode(OPAQUE);
  pDC->SetBkColor(whiteColor);
  pDC->SetTextColor(blackColor);

  pDC->SetTextAlign(TA_CENTER | TA_BOTTOM );
  BOOL bDrawn = pDC->TextOut( 20, 50, strShortName);
	pDC->SelectObject(pFont);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CIDWViewerSrvrItem diagnostics

#ifdef _DEBUG
void CIDWViewerSrvrItem::AssertValid() const
{
	COleServerItem::AssertValid();
}

void CIDWViewerSrvrItem::Dump(CDumpContext& dc) const
{
	COleServerItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
