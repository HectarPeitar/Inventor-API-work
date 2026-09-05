// ApprenticeViewerMDIView.cpp : implementation of the CApprenticeViewerMDIView class
//

#include "stdafx.h"
#include "ApprenticeViewerMDI.h"

#include "ApprenticeViewerMDIDoc.h"
#include "ApprenticeViewerMDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CApprenticeViewerMDIView

IMPLEMENT_DYNCREATE(CApprenticeViewerMDIView, CView)

BEGIN_MESSAGE_MAP(CApprenticeViewerMDIView, CView)
	//{{AFX_MSG_MAP(CApprenticeViewerMDIView)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_CONTEXTMENU()

	ON_COMMAND_RANGE(IDR_MENU_FRONT, IDR_MENU_BL_VIEW, OnOrientation)
	ON_UPDATE_COMMAND_UI_RANGE(IDR_MENU_FRONT, IDR_MENU_BL_VIEW, OnUpdateOrientation)

	ON_COMMAND_RANGE(IDR_MENU_SHOWOVERLAY, IDR_MENU_SHOWOVERLAY, OnOverlay)
	ON_UPDATE_COMMAND_UI_RANGE(IDR_MENU_SHOWOVERLAY, IDR_MENU_SHOWOVERLAY, OnUpdateOverlay)

	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CApprenticeViewerMDIView construction/destruction

CApprenticeViewerMDIView::CApprenticeViewerMDIView()
{
	m_docType = kUnknownDocumentObject;
	m_perspective = false;
	m_displayMode = kShadedRendering;
	m_sheetIndex = 1;
	m_interactive = false;

	m_text = _T("GDI String");
	m_textPoint = CPoint(50, 50);
	m_focusText = false;
	m_movingText = false;
	m_showOverlay = false;

	m_viewingMode = kRotateViewOperation;
	m_mouseWheelDown = false;
}

CApprenticeViewerMDIView::~CApprenticeViewerMDIView()
{
}

void CApprenticeViewerMDIView::SetClientView(CComPtr<ClientView> pClientView)
{
	m_pClientView = pClientView;
}

CComPtr<ClientView> CApprenticeViewerMDIView::GetClientView()
{
	return m_pClientView;
}

void CApprenticeViewerMDIView::SetDisplayMode(DisplayModeEnum mode)
{
	m_displayMode = mode;

	HRESULT hr = m_pClientView->put_DisplayMode(m_displayMode);

	Invalidate();
}

void CApprenticeViewerMDIView::SetPerspective(bool perspective)
{
	m_perspective = perspective;

	CComPtr<Camera> pCamera;
	HRESULT hr = m_pClientView->get_Camera(&pCamera);
	hr = pCamera->put_Perspective(m_perspective ? VARIANT_TRUE : VARIANT_FALSE);
	hr = pCamera->Apply();
	
	Invalidate();
}

void CApprenticeViewerMDIView::SetViewingMode(ViewOperationTypeEnum mode)
{
	m_viewingMode = mode;
}

void CApprenticeViewerMDIView::Fit()
{
	CComPtr<Camera> pCamera;
	HRESULT hr = m_pClientView->get_Camera(&pCamera);
	if (SUCCEEDED(hr) && pCamera)
	{
		pCamera->Fit();
		pCamera->Apply();
		Invalidate();
	}
}

void CApprenticeViewerMDIView::ResetView()
{
}

void CApprenticeViewerMDIView::SelectionChanged(long index)
{
	m_sheetIndex = index;
	CComPtr<ClientViews> pClientViews = GetClientViews();
	if (pClientViews)
	{
		m_pClientView = NULL;
		HRESULT hr = pClientViews->Add((long)m_hWnd, &m_pClientView);
	}

	DefaultView();
}

BOOL CApprenticeViewerMDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CApprenticeViewerMDIView drawing

void CApprenticeViewerMDIView::OnDraw(CDC* pDC)
{
	CApprenticeViewerMDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Force update of ClientView
	m_pClientView->Update(m_interactive ? VARIANT_TRUE : VARIANT_FALSE);

	if (m_showOverlay)
	{
		// Try drawing some GDI over the top.
		pDC->SetBkMode(TRANSPARENT);
		CSize textSize = pDC->GetTextExtent(m_text);
		CRect rect(m_textPoint.x, m_textPoint.y, m_textPoint.x+textSize.cx, m_textPoint.y+textSize.cy);
		CRect borderRect = rect;
		borderRect.InflateRect(2, 2);

		if (m_focusText)
			pDC->DrawFocusRect(borderRect);
		
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->DrawText(m_text, rect, 0); //DT_CENTER|DT_WORDBREAK);
	}
}

void CApprenticeViewerMDIView::OnInitialUpdate()
{
	CApprenticeViewerMDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CComPtr<ApprenticeServerDocument> pAppDoc = pDoc->GetApprenticeDocument();
	pAppDoc->get_DocumentType(&m_docType);

	if (m_docType == kDrawingDocumentObject)
		m_viewingMode = kPanViewOperation;
	else
		m_viewingMode = kRotateViewOperation;

	CComPtr<ClientViews> pClientViews = GetClientViews();
	
	HRESULT hr = pClientViews->Add((long) m_hWnd, &m_pClientView);
	DefaultView();

	CView::OnInitialUpdate();	
}

/////////////////////////////////////////////////////////////////////////////
// CApprenticeViewerMDIView diagnostics

#ifdef _DEBUG
void CApprenticeViewerMDIView::AssertValid() const
{
	CView::AssertValid();
}

void CApprenticeViewerMDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CApprenticeViewerMDIDoc* CApprenticeViewerMDIView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CApprenticeViewerMDIDoc)));
	return (CApprenticeViewerMDIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CApprenticeViewerMDIView message handlers
void CApprenticeViewerMDIView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}

BOOL CApprenticeViewerMDIView::OnEraseBkgnd(CDC* pDC) 
{
	// We'll erase the background ourselves
	return TRUE;
}

void CApprenticeViewerMDIView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_interactive = true;
	SetCapture();

	CView::OnLButtonDown(nFlags, point);
}

void CApprenticeViewerMDIView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_interactive = false; // Force a non-interactive redraw.
	Invalidate();
	ReleaseCapture();

	CView::OnLButtonUp(nFlags, point);
}

void CApprenticeViewerMDIView::OnMouseMove(UINT nFlags, CPoint point) 
{
	bool leftButton = nFlags & MK_LBUTTON;
	bool middleButton = nFlags == MK_MBUTTON; // || m_mouseWheelDown;
	
	CWinApp *pWinApp = AfxGetApp();
	CApprenticeViewerMDIApp *pApp = dynamic_cast<CApprenticeViewerMDIApp *>(pWinApp);
	CComPtr<ApprenticeServer> pApprenticeServer = pApp->GetApprenticeServer();

	if ((leftButton || middleButton) && m_pClientView)
	{
		CComPtr<TransientGeometry> pTransientGeometry = GetTransientGeometry();

		CComPtr<Point2d> pFrom, pTo;
		pTransientGeometry->CreatePoint2d(m_previousPoint.x, m_previousPoint.y, &pFrom);
		pTransientGeometry->CreatePoint2d(point.x, point.y, &pTo);

		CComPtr<Camera> pCamera;
		HRESULT hr = m_pClientView->get_Camera(&pCamera);

		if (leftButton)
			hr = pCamera->ComputeWithMouseInput(pFrom, pTo, 0, m_viewingMode);
		else
			hr = pCamera->ComputeWithMouseInput(pFrom, pTo, 0, kPanViewOperation);
		
		hr = pCamera->Apply();					
		Invalidate();
	}
	
	m_previousPoint = point;

	CView::OnMouseMove(nFlags, point);
}

BOOL CApprenticeViewerMDIView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{	
	CComPtr<TransientGeometry> pTransientGeometry = GetTransientGeometry();

	CComPtr<Point2d> pFrom, pTo;
	pTransientGeometry->CreatePoint2d(m_previousPoint.x, m_previousPoint.y, &pFrom);
	pTransientGeometry->CreatePoint2d(pt.x, pt.y, &pTo);

	CComPtr<Camera> pCamera;
	HRESULT hr = m_pClientView->get_Camera(&pCamera);
	hr = pCamera->ComputeWithMouseInput(pFrom, pTo, zDelta, kZoomViewOperation);

	hr = pCamera->Apply();
	Invalidate();
	
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CApprenticeViewerMDIView::OnMButtonDown(UINT nFlags, CPoint point) 
{
	m_mouseWheelDown = true;
	m_interactive = true;
	SetCapture();
	
	CView::OnMButtonDown(nFlags, point);
}

void CApprenticeViewerMDIView::OnMButtonUp(UINT nFlags, CPoint point) 
{
	m_mouseWheelDown = false;
	m_interactive = false; // Force a non-interactive redraw.
	Invalidate();
	ReleaseCapture();

	CView::OnMButtonUp(nFlags, point);
}

void CApprenticeViewerMDIView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu viewMenu;
	viewMenu.LoadMenu(IDR_VIEW_MENU);

	CMenu *pContextMenu = viewMenu.GetSubMenu(0);
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());

	return;
}

void CApprenticeViewerMDIView::OnOrientation(UINT contextMenuId)
{
	// Doesn't really make sense for drawings
	if (m_docType == kDrawingDocumentObject)
		return;

	CComPtr<Camera> pCamera;
	HRESULT hr = m_pClientView->get_Camera(&pCamera);

	if (SUCCEEDED(hr))
	{
		switch(contextMenuId)
		{
		case IDR_MENU_TOP_VIEW:
			pCamera->put_ViewOrientationType(kTopViewOrientation);
			break;
		case IDR_MENU_BOTTOM_VIEW:
			pCamera->put_ViewOrientationType(kBottomViewOrientation);
			break;
		case IDR_MENU_RIGHT_VIEW:
			pCamera->put_ViewOrientationType(kRightViewOrientation);
			break;
		case IDR_MENU_LEFT_VIEW:
			pCamera->put_ViewOrientationType(kLeftViewOrientation);
			break;
		case IDR_MENU_FRONT_VIEW:
			pCamera->put_ViewOrientationType(kFrontViewOrientation);
			break;
		case IDR_MENU_BACK_VIEW:
			pCamera->put_ViewOrientationType(kBackViewOrientation);
			break;
		case IDR_MENU_TR_VIEW:
			pCamera->put_ViewOrientationType(kIsoTopRightViewOrientation);
			break;
		case IDR_MENU_TL_VIEW:
			pCamera->put_ViewOrientationType(kIsoTopLeftViewOrientation);
			break;
		case IDR_MENU_BR_VIEW:
			pCamera->put_ViewOrientationType(kIsoBottomRightViewOrientation);
			break;
		case IDR_MENU_BL_VIEW:
			pCamera->put_ViewOrientationType(kIsoBottomLeftViewOrientation);
			break;
		}

		pCamera->Apply();
		Invalidate();
	}
}

void CApprenticeViewerMDIView::OnUpdateOrientation(CCmdUI *pCmdUI)
{
	// For now, all context menu items are enabled but not checked.
	pCmdUI->Enable();
}

void CApprenticeViewerMDIView::OnOverlay(UINT contextMenuId)
{
	if (contextMenuId == IDR_MENU_SHOWOVERLAY)
	{
		m_showOverlay = !m_showOverlay;
		Invalidate();
	}
}

void CApprenticeViewerMDIView::OnUpdateOverlay(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_showOverlay);
}

void CApprenticeViewerMDIView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
}

CComPtr<ClientViews> CApprenticeViewerMDIView::GetClientViews()
{
	HRESULT hr = S_OK;

	CComPtr<ClientViews> pClientViews;

	CApprenticeViewerMDIDoc* pDoc = GetDocument();
	CComPtr<ApprenticeServerDocument> pAppDoc = pDoc->GetApprenticeDocument();

	if (m_docType == kDrawingDocumentObject)
	{
		CComQIPtr<ApprenticeServerDrawingDocument> pDrawingDoc = pAppDoc;
		CComPtr<Sheets> pSheets;
		hr = pDrawingDoc->get_Sheets(&pSheets);

		long numSheets = 0;
		hr = pSheets->get_Count(&numSheets);

		CComQIPtr<Sheet> pSheet;
		hr = pSheets->get_Item(_variant_t(m_sheetIndex), &pSheet);			
		hr = pSheet->get_ClientViews(&pClientViews);
	}
	else
	{
		hr = pAppDoc->get_ClientViews(&pClientViews);
	}

	return pClientViews;
}

void CApprenticeViewerMDIView::DefaultView()
{
	if (m_pClientView)
	{
		CComPtr<Camera> pCamera;
		if (SUCCEEDED(m_pClientView->get_Camera(&pCamera)) && pCamera)
		{
			CApprenticeViewerMDIDoc* pDoc = GetDocument();
			CComPtr<ApprenticeServerDocument> pAppDoc = pDoc->GetApprenticeDocument();

			switch (m_docType)
			{
			case kPartDocumentObject:
			case kAssemblyDocumentObject:
				pCamera->put_ViewOrientationType(kIsoTopRightViewOrientation);
				break;
			case kDrawingDocumentObject:
				pCamera->put_ViewOrientationType(kFrontViewOrientation);
				break;
			default:
				pCamera->put_ViewOrientationType(kFrontViewOrientation);
			}

			pCamera->put_Perspective(m_perspective ? VARIANT_TRUE : VARIANT_FALSE);
			pCamera->Apply();
		}

		m_pClientView->put_DisplayMode(m_displayMode);

		Invalidate();
	}
}

CComPtr<TransientGeometry> CApprenticeViewerMDIView::GetTransientGeometry()
{
	CComPtr<TransientGeometry> pTransientGeometry;

	CWinApp *pWinApp = AfxGetApp();
	CApprenticeViewerMDIApp *pApp = dynamic_cast<CApprenticeViewerMDIApp *>(pWinApp);
	CComPtr<ApprenticeServer> pApprenticeServer = pApp->GetApprenticeServer();
	if (pApprenticeServer)
		pApprenticeServer->get_TransientGeometry(&pTransientGeometry);

	return pTransientGeometry;
}

