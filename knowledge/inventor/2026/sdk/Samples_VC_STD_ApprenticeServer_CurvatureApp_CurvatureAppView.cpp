// CurvatureAppView.cpp : implementation of the CCurvatureAppView class
//

#include "stdafx.h"
#include "curvatureapp.h"
#include "curvatureappdoc.h"
#include "curvatureappview.h"

#include "AppRelated/CurvatureAppDisplay.h"
#include "AppRelated/ReferenceFileMgr.h"

#include "InventorRelated/ReferenceFile.h"
#include "InventorRelated/SelectionEngine.h"
#include "InventorRelated/Facets.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
// CCurvatureAppView

IMPLEMENT_DYNCREATE(CCurvatureAppView, CView)

BEGIN_MESSAGE_MAP(CCurvatureAppView, CView)
  //{{AFX_MSG_MAP(CCurvatureAppView)
  ON_WM_PAINT()
  ON_WM_DESTROY()
  ON_WM_SETFOCUS()
  ON_WM_SIZE()
  ON_WM_ERASEBKGND( )
  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONUP()
  ON_WM_MOUSEMOVE()
  ON_WM_KEYDOWN()
  ON_WM_CREATE()
  //}}AFX_MSG_MAP
  // Standard printing commands
  ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurvatureAppView construction/destruction

CCurvatureAppView::CCurvatureAppView()
: m_GLPixelIndex(0), m_LeftButtonDown(FALSE)
{
  //////////////////// AA /////////////////////////
  m_pDisplayEngine = new CCurvatureAppDisplay();
  //////////////////// AA /////////////////////////
}

CCurvatureAppView::~CCurvatureAppView()
{
  delete m_pDisplayEngine;
}

BOOL CCurvatureAppView::PreCreateWindow(CREATESTRUCT& cs)
{
  //////////////////// AA /////////////////////////
  // An OpenGL window must be created with the following flags and must not
  // include CS_PARENTDC for the class style. Refer to SetPixelFormat
  // documentation in the "Comments" section for further information.
  cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
  cs.style &= ~(CS_HREDRAW | CS_VREDRAW);
  //////////////////// AA /////////////////////////

  return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCurvatureAppView printing

BOOL CCurvatureAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
  // default preparation
  return DoPreparePrinting(pInfo);
}

void CCurvatureAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
  // TODO: add extra initialization before printing
}

void CCurvatureAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
  // TODO: add cleanup after printing
}

//////////////// AA /////////////////
afx_msg BOOL CCurvatureAppView::OnEraseBkgnd(CDC* pDC)
{
  // Returning TRUE here would mean that the background is not erased.
  // This is necessary to avoid Windows from repainting the background
  // with the default background color. We repaint the graphics screen
  // using OpenGL commands.
  return TRUE;
}
////////////////// AA //////////////////

/////////////////////////////////////////////////////////////////////////////
// CCurvatureAppView diagnostics

#ifdef _DEBUG
void CCurvatureAppView::AssertValid() const
{
  CView::AssertValid();
}

void CCurvatureAppView::Dump(CDumpContext& dc) const
{
  CView::Dump(dc);
}

CCurvatureAppDoc* CCurvatureAppView::GetDocument() // non-debug version is inline
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCurvatureAppDoc)));
  return (CCurvatureAppDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCurvatureAppView message handlers

void CCurvatureAppView::OnInitialUpdate() 
{
  ///////////////// AA ///////////////
  ///////////////// AA ///////////////

  CView::OnInitialUpdate();
}

// Implementation for pure virtual function
void CCurvatureAppView::OnDraw(CDC* pDC)
{
  CView::OnDraw(pDC);
}

void CCurvatureAppView::OnPaint() 
{
  CPaintDC dc(this); // device context for painting

  //////////////// AA //////////////
  m_pDisplayEngine->PaintGraphics(m_hWnd, &dc,
                                  GetDocument()->m_shadedDisplayOn,
                                  GetDocument()->m_edgeDisplayOn);
  //////////////// AA //////////////

  // Do not call CView::OnPaint() for painting messages
}

void CCurvatureAppView::OnDestroy() 
{
  CView::OnDestroy();

  //////////////// AA //////////////
  m_pDisplayEngine->DestroyGraphics();
  //////////////// AA //////////////
}

void CCurvatureAppView::OnSetFocus(CWnd* pOldWnd) 
{
  CView::OnSetFocus(pOldWnd);
}

void CCurvatureAppView::OnSize(UINT nType, int cx, int cy) 
{
  CView::OnSize(nType, cx, cy);
  
  ////////////////// AA ///////////////////
  if(nType == SIZE_MINIMIZED || nType == SIZE_MAXHIDE)
    return;

  if(cx == 0 || cy == 0)
    return;

  m_pDisplayEngine->ResizeGraphics(GetDC()->m_hDC, cx, cy);
  ////////////////// AA ///////////////////
}

////////////////// AA ///////////////////
BOOL CCurvatureAppView::SetWindowPixelFormat(HDC hDC)
{
  PIXELFORMATDESCRIPTOR pixelDesc;

  pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pixelDesc.nVersion = 1;

  pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | 
            PFD_SUPPORT_OPENGL |
            PFD_DOUBLEBUFFER |
            PFD_STEREO_DONTCARE;

  pixelDesc.iPixelType = PFD_TYPE_RGBA;
  pixelDesc.cColorBits = 32;
  pixelDesc.cRedBits = 8;
  pixelDesc.cRedShift = 16;
  pixelDesc.cGreenBits = 8;
  pixelDesc.cGreenShift = 8;
  pixelDesc.cBlueBits = 8;
  pixelDesc.cBlueShift = 0;
  pixelDesc.cAlphaBits = 0;
  pixelDesc.cAlphaShift = 0;
  pixelDesc.cAccumBits = 64;
  pixelDesc.cAccumRedBits = 16;
  pixelDesc.cAccumGreenBits = 16;
  pixelDesc.cAccumBlueBits = 16;
  pixelDesc.cAccumAlphaBits = 0;
  pixelDesc.cDepthBits = 32;
  pixelDesc.cStencilBits = 8;
  pixelDesc.cAuxBuffers = 0;
  pixelDesc.iLayerType = PFD_MAIN_PLANE;
  pixelDesc.bReserved = 0;
  pixelDesc.dwLayerMask = 0;
  pixelDesc.dwVisibleMask = 0;
  pixelDesc.dwDamageMask = 0;

  m_GLPixelIndex = ChoosePixelFormat(hDC, &pixelDesc);

  if(m_GLPixelIndex == 0) // Choose default
  {
    m_GLPixelIndex = 1;
    if(!DescribePixelFormat(hDC, m_GLPixelIndex, sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc))
      return FALSE;
  }

  if(!SetPixelFormat(hDC, m_GLPixelIndex, &pixelDesc))
    return FALSE;

  return TRUE;
}

void CCurvatureAppView::OnLButtonDown(UINT nFlags, CPoint point) 
{
  /////////////////// AA ////////////////
  if(GetDocument()->m_eSelectFilter) {
    GetDocument()->RefreshAllViews();

    m_LeftDownPos = point;
    DoSelection();

    GetDocument()->ProcessCommand();
  }
  else {
    m_LeftButtonDown = TRUE;
    m_LeftDownPos = point;
    SetCapture();
  }
  /////////////////// AA ////////////////
  
  CView::OnLButtonDown(nFlags, point);
}

void CCurvatureAppView::OnLButtonUp(UINT nFlags, CPoint point) 
{
  /////////////////// AA ////////////////
  m_LeftButtonDown = FALSE;
  ReleaseCapture();
  /////////////////// AA ////////////////
  
  CView::OnLButtonUp(nFlags, point);
}

void CCurvatureAppView::OnMouseMove(UINT nFlags, CPoint point) 
{
  /////////////////// AA ////////////////
  bool bInCommandMode = GetDocument()->InCommandMode();
  if(m_LeftButtonDown && !bInCommandMode)
  {
    CSize rotate = m_LeftDownPos - point;
    rotate.cx /= 2;
    rotate.cy /= 2;
    m_LeftDownPos = point;
    m_pDisplayEngine->Rotate(rotate);
    InvalidateRect(NULL, FALSE);
  }
  /////////////////// AA ////////////////

  CView::OnMouseMove(nFlags, point);
}

void CCurvatureAppView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  /////////////////// AA ////////////////
  switch(nChar)
    {
    case VK_ADD:
      m_pDisplayEngine->Scale(1.1f);
      InvalidateRect(NULL, FALSE);
      break;
    case VK_SUBTRACT:
      m_pDisplayEngine->Scale(1 / 1.1f);
      InvalidateRect(NULL, FALSE);
      break;
    case VK_LEFT:
      break;
    case VK_RIGHT:
      break;
    case VK_UP:
      break;
    case VK_DOWN:
      break;
    case VK_ESCAPE:
      GetDocument()->CancelCommand();
      break;
    default :
      {}

    }
  /////////////////// AA ////////////////
  
  CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCurvatureAppView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
  HDC hDC = GetDC()->m_hDC;
  if(SetWindowPixelFormat(hDC) == FALSE)
    return;

  m_pDisplayEngine->Init(hDC);

  CReferenceFileMgr* pReferenceFileMgr = GetDocument()->GetReferenceFileMgr();
  if(!pReferenceFileMgr->IsReferencingInventorFile())
    return;

  CReferenceFile* pReferenceFile = pReferenceFileMgr->GetReferenceFile();
  ULONG numFacets = pReferenceFile->GetNumFacets();
  double* pVertices = pReferenceFile->GetVertices();
  double* pNormals = pReferenceFile->GetNormals();
  ULONG* pVertexIndices = pReferenceFile->GetVertexIndices();

  ULONG numWFVertices = pReferenceFile->GetNumWFVertices();
  double* pWFVertices = pReferenceFile->GetWFVertices();
  ULONG numWFPolylines = pReferenceFile->GetNumWFPolylines();
  ULONG* pWFPolylineLengths = pReferenceFile->GetWFPolylineLengths();

  unsigned char Red, Green, Blue;
  pReferenceFile->GetColor (&Red, &Green, &Blue);

  m_pDisplayEngine->PutColor (Red, Green, Blue);
  m_pDisplayEngine->BuildDisplayList(hDC, numFacets, pVertices, pNormals, pVertexIndices,
                                      numWFVertices, pWFVertices, numWFPolylines, pWFPolylineLengths);

  CSelectionEngine* pSelectionEngine = pReferenceFileMgr->GetSelectionEngine();
  ULONG numSelectVertices = pSelectionEngine->GetNumWFSelVertices();
  double* pSelectVertices = pSelectionEngine->GetWFSelVertices();
  ULONG numSelectIndices = pSelectionEngine->GetNumWFSelIndices();
  ULONG* pSelectIndices = pSelectionEngine->GetWFSelIndices();

  m_pDisplayEngine->BuildSelectList(this, hDC, numSelectVertices, pSelectVertices,
                                    numSelectIndices, pSelectIndices);

  // Build the curvature display list

  ULONG numCurvaturePoints = GetDocument()->GetNumCurvaturePoints();
  double* pCurvaturePoints = GetDocument()->GetCurvaturePoints();
  double* pCurvatureNormals = GetDocument()->GetCurvatureNormals();
  m_pDisplayEngine->BuildCurvatureDisplayList(hDC, numCurvaturePoints, pCurvaturePoints, pCurvatureNormals);

  ULONG numCurvatureFacets = GetDocument()->GetNumCurvatureGradientFacets();
  pCurvaturePoints = GetDocument()->GetCurvatureGradientPoints();
  pCurvatureNormals = GetDocument()->GetCurvatureGradientNormals();
  ULONG* pCurvatureIndices = GetDocument()->GetCurvatureGradientIndices();
  m_pDisplayEngine->BuildCurvatureGradientDisplayList(hDC, numCurvatureFacets, pCurvaturePoints, pCurvatureNormals, pCurvatureIndices);

  CView::OnUpdate(pSender, lHint, pHint);
}

void CCurvatureAppView::Refresh(bool bDeleteCurvatureDisplay /* = true */)
{
  // Delete the selection and the curvature display lists
  m_pDisplayEngine->DeleteSelectList(GetDC()->m_hDC);

  if(bDeleteCurvatureDisplay)
    m_pDisplayEngine->DeleteCurvatureList(GetDC()->m_hDC);
}

void CCurvatureAppView::DoSelection()
{
  ////////////////TODO//////////////////////////////////
  Refresh();

  // perform selection
  //
  HDC hDC = GetDC()->m_hDC;
  GLdouble pt1[3], pt2[3];
  boolean bRet = m_pDisplayEngine->GetBorelineVector(m_hWnd, hDC, m_LeftDownPos, pt1, pt2);

  double boreDia = 0.0;

  if(!m_pDisplayEngine->GetBorelineDia(hDC, m_hWnd, GetDocument()->m_selectionTolerance, &boreDia))
    return;

  CReferenceFileMgr* pReferenceFileMgr = GetDocument()->GetReferenceFileMgr();
  HRESULT hr = pReferenceFileMgr->PerformSelection(GetDocument()->m_eSelectFilter,
                                                    GetDocument()->m_chordHtTol, boreDia,
                                                    pt1, pt2);

  // The document has been modified
  GetDocument()->SetModifiedFlag(TRUE);

  // force a redraw (even if we din't select any item)
  //
  InvalidateRect(NULL, FALSE);
  UpdateWindow();

  ////////////////////////////////////////////////////// 
}
