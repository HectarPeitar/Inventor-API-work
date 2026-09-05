// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "ApprenticeViewerMDI.h"

#include "ChildFrm.h"
#include "LeftView.h"
#include "ApprenticeViewerMDIView.h"
#include "ApprenticeViewerMDIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_SHADED, ID_VIEW_WIREFRAME, OnUpdateDisplayStyles)
	ON_COMMAND_RANGE(ID_VIEW_SHADED, ID_VIEW_WIREFRAME, OnDisplayStyle)

	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_ORTHOGRAPHIC, ID_VIEW_PERSPECTIVE, OnUpdateProjectionStyles)
	ON_COMMAND_RANGE(ID_VIEW_ORTHOGRAPHIC, ID_VIEW_PERSPECTIVE, OnProjectionStyle)
	
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_FIT, ID_VIEW_ARC_ROTATE, OnUpdateViewingMode)
	ON_COMMAND_RANGE(ID_VIEW_FIT, ID_VIEW_ARC_ROTATE, OnViewingMode)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	m_displayStyle = ID_VIEW_SHADED;
	m_projectionStyle = ID_VIEW_ORTHOGRAPHIC;
	m_viewingMode = ID_VIEW_ARC_ROTATE;
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::OnCreateClient( LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(100, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CApprenticeViewerMDIView), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	return TRUE;
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers
CApprenticeViewerMDIView* CChildFrame::GetRightPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 1);
	CApprenticeViewerMDIView* pView = DYNAMIC_DOWNCAST(CApprenticeViewerMDIView, pWnd);
	return pView;
}

void CChildFrame::OnUpdateDisplayStyles(CCmdUI* pCmdUI)
{
	// TODO: customize or extend this code to handle choices on the
	// View menu.

	CApprenticeViewerMDIView* pView = GetRightPane(); 

	// if the right-hand pane hasn't been created or isn't a view,
	// disable commands in our range

	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		// Only enable if we are in a part or assembly.
		if (pView->GetDocument()->GetType() == kDrawingDocumentObject)
			pCmdUI->Enable(FALSE);
		else
			pCmdUI->Enable();

		pCmdUI->SetRadio(pCmdUI->m_nID == m_displayStyle);
	}
}

void CChildFrame::OnDisplayStyle(UINT nCommandID)
{
	CApprenticeViewerMDIView* pView = GetRightPane();

	// if the right-hand pane has been created and is a CApprenticeViewerMDIView,
	// process the menu commands...
	if (true) ///pView != NULL)
	{
		switch (nCommandID)
		{
		case ID_VIEW_SHADED:
			pView->SetDisplayMode(kShadedRendering);
			break;

		case ID_VIEW_HIDDEN_EDGE:
			pView->SetDisplayMode(kHiddenEdgeRendering);
			break;

		case ID_VIEW_WIREFRAME:
			pView->SetDisplayMode(kWireframeRendering);
			break;
		}

		m_displayStyle = nCommandID;
	}
}

void CChildFrame::OnUpdateProjectionStyles(CCmdUI* pCmdUI)
{
	// TODO: customize or extend this code to handle choices on the
	// View menu.

	CApprenticeViewerMDIView* pView = GetRightPane(); 

	// if the right-hand pane hasn't been created or isn't a view,
	// disable commands in our range

	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		// Only enable if we are in a part or assembly.
		if (pView->GetDocument()->GetType() == kDrawingDocumentObject)
			pCmdUI->Enable(FALSE);
		else
			pCmdUI->Enable();
	
		pCmdUI->SetRadio(pCmdUI->m_nID == m_projectionStyle);
	}
}

void CChildFrame::OnProjectionStyle(UINT nCommandID)
{
	CApprenticeViewerMDIView* pView = GetRightPane();

	// if the right-hand pane has been created and is a CApprenticeViewerMDIView,
	// process the menu commands...
	
	if (pView != NULL)
	{
		switch (nCommandID)
		{
		case ID_VIEW_ORTHOGRAPHIC:
			pView->SetPerspective(false);
			break;

		case ID_VIEW_PERSPECTIVE:
			pView->SetPerspective(true);
			break;
		}

		m_projectionStyle = nCommandID;
	}
}

void CChildFrame::OnUpdateViewingMode(CCmdUI* pCmdUI)
{
	CApprenticeViewerMDIView* pView = GetRightPane(); 

	// if the right-hand pane hasn't been created or isn't a view,
	// disable commands in our range

	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		bool isDrawing = pView->GetDocument()->GetType() == kDrawingDocumentObject;
		if (isDrawing && m_viewingMode == ID_VIEW_ARC_ROTATE)
			m_viewingMode = ID_VIEW_PAN;

		switch (pCmdUI->m_nID)
		{
		case ID_VIEW_FIT:
			pCmdUI->Enable();
			break;	
		case ID_VIEW_ZOOM:
			pCmdUI->Enable();
			pCmdUI->SetRadio(pCmdUI->m_nID == m_viewingMode);
			break;
		case ID_VIEW_PAN:
			pCmdUI->Enable();
			pCmdUI->SetRadio(pCmdUI->m_nID == m_viewingMode);
			break;
		case ID_VIEW_ARC_ROTATE:
			pCmdUI->Enable(!isDrawing);
			pCmdUI->SetRadio(pCmdUI->m_nID == m_viewingMode);
			break;
		}
	}
}

void CChildFrame::OnViewingMode(UINT nCommandID)
{
	CApprenticeViewerMDIView* pView = GetRightPane();

	// if the right-hand pane has been created and is a CApprenticeViewerMDIView,
	// process the menu commands...
	
	if (pView != NULL)
	{
		bool isDrawing = pView->GetDocument()->GetType() == kDrawingDocumentObject;

		switch (nCommandID)
		{
		case ID_VIEW_FIT:
			pView->Fit();
			break;	
		case ID_VIEW_ZOOM:
			pView->SetViewingMode(kZoomViewOperation);
			m_viewingMode = nCommandID;
			break;
		case ID_VIEW_PAN:
			pView->SetViewingMode(kPanViewOperation);
			m_viewingMode = nCommandID;
			break;
		case ID_VIEW_ARC_ROTATE:
			pView->SetViewingMode(kRotateViewOperation);
			m_viewingMode = nCommandID;
			break;
		}
	}
}
