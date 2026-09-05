// CurvatureAppDoc.cpp : implementation of the CCurvatureAppDoc class
//

#include "stdafx.h"
#include <afxpriv.h>  // Only needed for USES_CONVERSION
#include "curvatureapp.h"

#include "curvatureappdoc.h"
#include "curvatureappview.h"

#include "AppRelated/ReferenceFileMgr.h"
#include "AppRelated/CurvatureAppDb.h"
#include "AppRelated/OptionsDialog.h"
#include "AppRelated/DebugBodyDlg.h"
#include "AppRelated/CurvatureDialog.h"

#include "InventorRelated/CurvatureEngine.h"
#include "InventorRelated/MeasureEngine.h"
#include "InventorRelated/SelectionEngine.h"
#include "InventorRelated/ReferenceFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurvatureAppDoc

IMPLEMENT_DYNCREATE(CCurvatureAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CCurvatureAppDoc, CDocument)
	//{{AFX_MSG_MAP(CCurvatureAppDoc)
	ON_COMMAND(ID_BOXCOMMANDS_REFERENCEBOXFILE, OnReferenceInventorFile)
	ON_COMMAND(ID_TOOLS_SELECTFACE, OnToolsMeasureFace)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SELECTFACE, OnUpdateToolsMeasureFace)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SELECTVERTEX, OnUpdateToolsMeasureDistance)
	ON_COMMAND(ID_TOOLS_SELECTVERTEX, OnToolsMeasureDistance)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SELECT_EDGE, OnUpdateToolsMeasureEdge)
	ON_COMMAND(ID_TOOLS_SELECT_EDGE, OnToolsMeasureEdge)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SHOW_CURVATURE, OnUpdateToolsShowCurvature)
	ON_COMMAND(ID_TOOLS_OPTION, OnToolsOption)
	ON_COMMAND(ID_TOOLS_SHOW_CURVATURE, OnToolsShowCurvature)
	ON_COMMAND(ID_VIEW_REFRESH, OnRefresh)
	ON_COMMAND(ID_TOOLS_DEBUGBODY, OnDebugbody)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_DEBUGBODY, OnUpdateToolsDebugbody)
	ON_UPDATE_COMMAND_UI(ID_APPCOMMANDS_UPDATE_INV_FILE, OnUpdateCommandUpdateInventorFile)
	ON_COMMAND(ID_APPCOMMANDS_UPDATE_INV_FILE, OnUpdateInventorFile)
	ON_COMMAND(IDD_DEBUG_STATE, OnDebugState)
	ON_UPDATE_COMMAND_UI(IDD_DEBUG_STATE, OnUpdateDebugState)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurvatureAppDoc construction/destruction

CCurvatureAppDoc::CCurvatureAppDoc()
: m_lpReferencedFileName(0), m_pReferenceFileMgr(0),
  m_eCommand(eUnknownCommand), m_chordHtTol(0.01), m_shadedDisplayOn(TRUE),
  m_edgeDisplayOn(FALSE), m_uDensity(10), m_vDensity(10),
  m_selectionTolerance(5), m_eSelectFilter(eUnknownFilter),
  m_pCurvatureDlg(0), m_curvatureType("Pin Cushion"),
  m_bConnectionTypeSelected(false),m_bUseLiveConnection(false)
{
  m_pReferenceFileMgr = new CReferenceFileMgr();
}

CCurvatureAppDoc::~CCurvatureAppDoc()
{
  if(m_pCurvatureDlg)
    m_pCurvatureDlg->DestroyWindow();
}

bool CCurvatureAppDoc::GetLiveConnection()
{
	if(!m_bConnectionTypeSelected)
	{
		m_bUseLiveConnection = false;
		CLSID AppClsId;
		HRESULT hr = ::CLSIDFromProgID (L"Inventor.Application", &AppClsId);
		if(SUCCEEDED(hr))
		{
			// Can we connect to Inventor
			//
			CComPtr<IUnknown> spAppUnk;
			hr = ::GetActiveObject (AppClsId, NULL, &spAppUnk);
			if (SUCCEEDED(hr)) 
			{
				int nSelection = ::AfxMessageBox("Do you want CurvatureApp to open Inventor documents using Inventor?",MB_YESNO);
				m_bUseLiveConnection = (IDYES == nSelection);
			}
		}
		m_bConnectionTypeSelected = true;
	}
	return m_bUseLiveConnection;
}


/////////////////////////////////////////////////////////////////////////////
// CCurvatureAppDoc commands

BOOL CCurvatureAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

  // Tell the Db that a new file has been referenced.
  //
  HRESULT hr = m_pReferenceFileMgr->GetDb()->InitNew(GetReferenceFileMgr());
	ASSERT(SUCCEEDED(hr));

  return TRUE;
}

BOOL CCurvatureAppDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
  CWaitCursor waitCursor;
	USES_CONVERSION;

  // Create a new persistence engine for saving/loading referenced Inventor files
  m_pReferenceFileMgr->GetDb()->Open(T2W(lpszPathName));

  HRESULT hr = m_pReferenceFileMgr->GetDb()->PreLoad(&m_lpReferencedFileName, &m_chordHtTol, &m_uDensity, &m_vDensity,
                        &m_shadedDisplayOn, &m_edgeDisplayOn, &m_selectionTolerance);
  if(SUCCEEDED(hr) && m_lpReferencedFileName) {

    CReferenceFileMgr* pReferenceFileMgr = GetReferenceFileMgr();

	  // Reference the given file
	  hr = pReferenceFileMgr->ReferenceFile(m_lpReferencedFileName, m_chordHtTol,GetLiveConnection());
	  ASSERT(SUCCEEDED(hr));
    if(FAILED(hr))
      return FALSE;

    // Tell the DB to load itself from the file
    //
    hr = m_pReferenceFileMgr->GetDb()->Load(pReferenceFileMgr);
    if(FAILED(hr))
      return FALSE;

    CFileStatus rStatus;
    BOOL bRet = CFile::GetStatus(W2T(m_lpReferencedFileName), rStatus);
    if(bRet == FALSE)
      return FALSE;

    m_lastModifiedTime = rStatus.m_mtime;

    UpdateAllViews(0);
  }

  return TRUE;
}

void CCurvatureAppDoc::OnCloseDocument() 
{
  delete m_pReferenceFileMgr;
  delete m_lpReferencedFileName; m_lpReferencedFileName = 0;

	CDocument::OnCloseDocument();
}

BOOL CCurvatureAppDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
  CWaitCursor waitCursor;
  USES_CONVERSION;

  if(!IsModified() && !GetPathName().IsEmpty() && GetPathName() == lpszPathName)
    return TRUE;

  m_eCommand = eUnknownCommand;
  m_eSelectFilter = eUnknownFilter;
  HRESULT hr;
  CReferenceFileMgr* pReferenceFileMgr = GetReferenceFileMgr();
  if(GetPathName().IsEmpty() || GetPathName() != lpszPathName) {
    hr = m_pReferenceFileMgr->GetDb()->SaveAs(T2W(lpszPathName), m_lpReferencedFileName,
                  m_chordHtTol, m_uDensity, m_vDensity,
                  m_shadedDisplayOn, m_edgeDisplayOn,
                  m_selectionTolerance, pReferenceFileMgr);
  }
  else {
    hr = m_pReferenceFileMgr->GetDb()->Save(m_lpReferencedFileName,
                  m_chordHtTol, m_uDensity, m_vDensity,
                  m_shadedDisplayOn, m_edgeDisplayOn,
                  m_selectionTolerance, pReferenceFileMgr);
  }
  if(FAILED(hr)) {
    ASSERT(false);
    return FALSE;
  }

  SetModifiedFlag(FALSE);
	return SUCCEEDED(hr);
}

// Reference a user supplied Inventor file.
//    - If I already reference an Inventor file, remove the reference.
//    - Leave the app in the same command state as it was before calling Reference Inventor File.
//
void CCurvatureAppDoc::OnReferenceInventorFile()
{
	USES_CONVERSION;

	CFileDialog fd(TRUE, NULL, NULL, OFN_SHOWHELP,
					"Part Files (*.ipt)|*.ipt|Assembly Files (.iam)|*.iam|Inventor Files (*.ipt;*.iam)|*.ipt;*.iam||", NULL);
	int iRe = fd.DoModal();
	if(iRe != IDOK) {
		return;
	}

  CFileStatus rStatus;
  BOOL bRet = CFile::GetStatus(fd.GetPathName(), rStatus);
  if(bRet == FALSE)
    return;

  m_lastModifiedTime = rStatus.m_mtime;

  CWaitCursor waitCursor;
  RefreshAllViews();
  m_pReferenceFileMgr->CleanKeys();

  m_lpReferencedFileName = new WCHAR[fd.GetPathName().GetLength() + 1];
  wcscpy_s(m_lpReferencedFileName, fd.GetPathName().GetLength() + 1, T2W((LPCTSTR)fd.GetPathName()));

	// Reference the given file
  CReferenceFileMgr* pReferenceFileMgr = GetReferenceFileMgr();
  HRESULT hr = pReferenceFileMgr->ReferenceFile(m_lpReferencedFileName, m_chordHtTol,GetLiveConnection());
  ASSERT(SUCCEEDED(hr));

  SetModifiedFlag(TRUE);
  
	UpdateAllViews(0);
}

/////////////////////// AA ///////////////////
void CCurvatureAppDoc::OnToolsOption() 
{
  ECommand eCommand = m_eCommand;
  CancelCommand();
  COptionsDialog optionsDlg;
  optionsDlg.SetChordalHeightTolerance(m_chordHtTol);
  optionsDlg.SetShadedDisplay(m_shadedDisplayOn);
  optionsDlg.SetEdgeDisplay(m_edgeDisplayOn);
  optionsDlg.SetSelectionTolerance(m_selectionTolerance);

  if(optionsDlg.DoModal() == IDOK) {
    m_chordHtTol = optionsDlg.GetChordalHeightTolerance();
    m_shadedDisplayOn = optionsDlg.IsShadedDisplayOn();
    m_edgeDisplayOn = optionsDlg.IsEdgeDisplayOn();
    m_selectionTolerance = optionsDlg.GetSelectionTolerance();

    UpdateAllViews(0); // This would recreate the facets

    // The document may have been modified
    SetModifiedFlag(TRUE);
  }

  if(eCommand == eMeasureFaceCommand || eCommand == eMeasureEdgeCommand || eCommand == eMeasureDistanceCommand) {
    ProcessCommand();
  }
}
/////////////////////// AA ///////////////////

void CCurvatureAppDoc::OnToolsMeasureFace() 
{
  ////////////////TODO//////////////////////////////////

  CancelCommand();
  RefreshAllViews();

  // turn on select mode
  //
  m_eSelectFilter = eFaceFilter;
  m_eCommand = eMeasureFaceCommand;

  ProcessCommand();
  //////////////////////////////////////////////////////	
}

void CCurvatureAppDoc::OnUpdateToolsMeasureFace(CCmdUI* pCmdUI) 
{
  ////////////////TODO//////////////////////////////////

	if(!m_pReferenceFileMgr->IsReferencingInventorFile())
    pCmdUI->Enable(FALSE);
  else
    pCmdUI->Enable(TRUE);

	return;

  //////////////////////////////////////////////////////		
}

void CCurvatureAppDoc::OnUpdateToolsMeasureDistance(CCmdUI* pCmdUI) 
{
  ////////////////TODO//////////////////////////////////

  // delegate it to the face update cmd ui
  //
  OnUpdateToolsMeasureFace(pCmdUI);
	
  //////////////////////////////////////////////////////		
}

void CCurvatureAppDoc::OnToolsMeasureDistance() 
{
  ////////////////TODO//////////////////////////////////

  CancelCommand();
  RefreshAllViews();

  // turn on select mode
  //
  m_eSelectFilter = eVertexFilter;
  m_eCommand = eMeasureDistanceCommand;

  ProcessCommand();
  //////////////////////////////////////////////////////			
}

void CCurvatureAppDoc::OnUpdateToolsMeasureEdge(CCmdUI* pCmdUI) 
{
  ////////////////TODO//////////////////////////////////

  // delegate it to the face update cmd ui
  //
  OnUpdateToolsMeasureFace(pCmdUI);

  //////////////////////////////////////////////////////		
}

void CCurvatureAppDoc::OnToolsMeasureEdge() 
{
  ////////////////TODO//////////////////////////////////

  CancelCommand();
  RefreshAllViews();

  // turn on select mode
  //
  m_eSelectFilter = eEdgeFilter;
  m_eCommand = eMeasureEdgeCommand;

  ProcessCommand();
  //////////////////////////////////////////////////////		
}

void CCurvatureAppDoc::OnDebugbody() 
{
  CancelCommand();
  RefreshAllViews();

  CReferenceFileMgr* pReferenceFileMgr = GetReferenceFileMgr();
	if(pReferenceFileMgr) {
    CString strFileName;
    int nShellCount, nFaceCount, nEdgeCount, nVertexCount;
    double fVolume{0.0};
    CWaitCursor waitCursor;
    HRESULT hr = pReferenceFileMgr->GetBodyInfo(strFileName, nShellCount, nFaceCount, nEdgeCount, nVertexCount, fVolume);
    // display the dialog box with this information
    if(SUCCEEDED(hr))
    {
      CDebugBodyDlg aDlg;
      aDlg.m_EdgesCount.Format("%d",nEdgeCount);
      aDlg.m_FacesCount.Format("%d",nFaceCount);
      aDlg.m_ShellsCount.Format("%d",nShellCount);
      aDlg.m_VerticesCount.Format("%d",nVertexCount);
      aDlg.m_Volume.Format("%16.3f cm**3",fVolume);
      aDlg.m_FileName = strFileName;
      aDlg.DoModal();
    }
  }	
}

void CCurvatureAppDoc::OnUpdateToolsDebugbody(CCmdUI* pCmdUI) 
{
	if(!m_pReferenceFileMgr->IsReferencingInventorFile())
    pCmdUI->Enable(FALSE);
  else
    pCmdUI->Enable(TRUE);
}

void CCurvatureAppDoc::OnUpdateToolsShowCurvature(CCmdUI* pCmdUI) 
{
  ////////////////TODO//////////////////////////////////
	if(!m_pReferenceFileMgr->IsReferencingInventorFile())
    pCmdUI->Enable(FALSE);
  else
    pCmdUI->Enable(TRUE);

	return;
  //////////////////////////////////////////////////////		
}

void CCurvatureAppDoc::OnToolsShowCurvature() 
{
  // Pop up the curvature dialog, asking the user for specific inputs.
  if(!m_pCurvatureDlg)
  {
    m_pCurvatureDlg = new CCurvatureDialog();
    BOOL ret = m_pCurvatureDlg->Create(IDD_CURVATURE_DIALOG, NULL);
    ASSERT(ret);
  }

  CancelCommand();
  RefreshAllViews();

  m_pCurvatureDlg->m_curvatureType = m_curvatureType;
  m_pCurvatureDlg->m_uDensity = m_uDensity;
  m_pCurvatureDlg->m_vDensity = m_vDensity;
  m_pCurvatureDlg->ShowWindow(SW_SHOW);
  m_pCurvatureDlg->UpdateData(FALSE);

  m_eSelectFilter = eFaceFilter;
  m_eCommand = eFaceCurvatureCommand;
  ProcessCommand();
}

bool CCurvatureAppDoc::ShowingPinCushion() const
{
  return m_curvatureType == CString("Pin Cushion");
}

void CCurvatureAppDoc::ShowCurvature()
{
  CWaitCursor waitCursor;

  // set the selected face in app util
  //
  HRESULT hr = m_pReferenceFileMgr->SetCurvatureFace(m_pReferenceFileMgr->GetLastSelectedObject(this));
  if(FAILED(hr))
    return;
  m_pReferenceFileMgr->SetLastSelectedObject(NULL);

  m_curvatureType = m_pCurvatureDlg->m_curvatureType;
  m_uDensity = m_pCurvatureDlg->m_uDensity;
  m_vDensity = m_pCurvatureDlg->m_vDensity;

  if ((m_curvatureType == CString("Pin Cushion")) && ((m_uDensity < 3) || (m_vDensity < 3)))
  {
	  ::AfxMessageBox("Curvature display density u/v should be greater than \"3\"");
	  return;
  }

  // Build the curvature display list
  if(ShowingPinCushion()) {
    m_pReferenceFileMgr->BuildCurvatureDisplayList(m_uDensity, m_vDensity);
  }
  else
    m_pReferenceFileMgr->BuildCurvatureGradient(m_chordHtTol);

  // The document has been modified
  SetModifiedFlag(TRUE);

  UpdateAllViews(0);
}

void CCurvatureAppDoc::MeasureFace()
{
  // set the selected face in Reference File Manager; which stores it in its vector
  // of objects to remember. Now we don't need to hold on to the last selected object.
  //
  HRESULT hr = m_pReferenceFileMgr->SetMeasureFace(m_pReferenceFileMgr->GetLastSelectedObject(this));
  if(FAILED(hr))
    return;
  m_pReferenceFileMgr->SetLastSelectedObject(NULL);

  // Compute the area.
  m_pReferenceFileMgr->MeasureFace();

  // The document has been modified
  SetModifiedFlag(TRUE);

  UpdateAllViews(0);
}

void CCurvatureAppDoc::MeasureEdge()
{
  // set the selected face in app util
  //
  HRESULT hr = m_pReferenceFileMgr->SetMeasureEdge(m_pReferenceFileMgr->GetLastSelectedObject(this));
  if(FAILED(hr))
    return;
  m_pReferenceFileMgr->SetLastSelectedObject(NULL);

  // Compute the area
  m_pReferenceFileMgr->MeasureEdge();

  // The document has been modified
  SetModifiedFlag(TRUE);

  UpdateAllViews(0);
}

void CCurvatureAppDoc::MeasureDistance()
{
	HRESULT hr = m_pReferenceFileMgr->SetMeasureVertices(m_pReferenceFileMgr->GetFirstVertex(this), m_pReferenceFileMgr->GetLastSelectedObject(this));
	if (FAILED(hr))
		return;

	m_pReferenceFileMgr->SetLastSelectedObject(NULL);

	m_pReferenceFileMgr->MeasureDistance();

	SetModifiedFlag(TRUE);

	UpdateAllViews(0);
}

void CCurvatureAppDoc::RefreshAllViews(bool bDeleteCurvatureDisplay /* = true */)
{
  // Delete the selection and the curvature display lists
  POSITION pos = GetFirstViewPosition();
  CCurvatureAppView* pView = reinterpret_cast<CCurvatureAppView*>(GetNextView(pos));
  while(pView) {
    pView->Refresh(bDeleteCurvatureDisplay);
    pView = reinterpret_cast<CCurvatureAppView*>(GetNextView(pos));
  }

  if(m_pReferenceFileMgr->IsReferencingInventorFile()) {
    if(bDeleteCurvatureDisplay)
      m_pReferenceFileMgr->GetCurvatureEngine()->Clean();

    m_pReferenceFileMgr->GetSelectionEngine()->Clean(bDeleteCurvatureDisplay);
    m_pReferenceFileMgr->GetMeasureEngine()->Clean();
  }

  UpdateAllViews(0);
}

void CCurvatureAppDoc::OnRefresh()
{
  RefreshAllViews();
}

void CCurvatureAppDoc::ProcessCommand()
{
  switch(this->m_eCommand) {
  case eFaceCurvatureCommand:
    ShowCurvature();
    break;
  case eMeasureFaceCommand:
    MeasureFace();
    break;
  case eMeasureEdgeCommand:
    MeasureEdge();
    break;
  case eMeasureDistanceCommand:
    MeasureDistance();
    break;
  default:
    break;
  }
}

void CCurvatureAppDoc::CancelCommand()
{
  // route the cancel cmd to all the engines (only to measure engine 
  // at this time since it puts out a modeless dlg
  //
  if(eMeasureFaceCommand == m_eCommand || eMeasureEdgeCommand == m_eCommand ||
     eMeasureDistanceCommand == m_eCommand)
    m_pReferenceFileMgr->GetMeasureEngine()->CancelCommand();

  // hide our curvature modeless dlg
  if(m_pCurvatureDlg)
    m_pCurvatureDlg->ShowWindow(SW_HIDE); 

  m_eCommand = eUnknownCommand;
  m_eSelectFilter = eUnknownFilter;

  RefreshAllViews(false);
}

void CCurvatureAppDoc::OnUpdateCommandUpdateInventorFile(CCmdUI* pCmdUI) 
{
  USES_CONVERSION;

  if(GetReferenceFileMgr()->IsReferencingInventorFile()) {
	if(m_bConnectionTypeSelected && m_bUseLiveConnection)
	{
      pCmdUI->Enable(TRUE);
	  return;
	}
    CFileStatus rStatus;
    BOOL bRet = CFile::GetStatus(W2T(m_lpReferencedFileName), rStatus);
    ASSERT(bRet != FALSE);
    if(m_lastModifiedTime != rStatus.m_mtime)
      pCmdUI->Enable(TRUE);
    else
      pCmdUI->Enable(FALSE);
  }
  else
    pCmdUI->Enable(FALSE);
}

void CCurvatureAppDoc::OnUpdateInventorFile() 
{
  CWaitCursor waitCursor;

  // Fire update events on all the engines
  GetReferenceFileMgr()->Update(m_lpReferencedFileName, m_chordHtTol,GetLiveConnection());

  // Clear the graphics on all views
  RefreshAllViews();

  ProcessCommand();
}

ULONG CCurvatureAppDoc::GetNumCurvaturePoints()
{
  return m_pReferenceFileMgr->GetCurvatureEngine()->m_numCurvaturePoints;
}

double* CCurvatureAppDoc::GetCurvaturePoints()
{
  return m_pReferenceFileMgr->GetCurvatureEngine()->m_pCurvaturePoints;
}

double* CCurvatureAppDoc::GetCurvatureNormals()
{
  return m_pReferenceFileMgr->GetCurvatureEngine()->m_pCurvatureNormals;
}

ULONG CCurvatureAppDoc::GetNumCurvatureGradientFacets()
{
  return m_pReferenceFileMgr->GetCurvatureEngine()->m_numCurvatureGradientFacets;
}

ULONG* CCurvatureAppDoc::GetCurvatureGradientIndices()
{
  return m_pReferenceFileMgr->GetCurvatureEngine()->m_pCurvatureGradientIndices;
}

double* CCurvatureAppDoc::GetCurvatureGradientPoints()
{
  return m_pReferenceFileMgr->GetCurvatureEngine()->m_pCurvatureGradientPoints;
}

double* CCurvatureAppDoc::GetCurvatureGradientNormals()
{
  return m_pReferenceFileMgr->GetCurvatureEngine()->m_pCurvatureGradientNormals;
}

CCurvatureAppView* CCurvatureAppDoc::GetFirstView()
{
  POSITION pos = GetFirstViewPosition();
  CCurvatureAppView* pFirstView = reinterpret_cast<CCurvatureAppView*>(GetNextView(pos));

  return pFirstView;
}

////////////// AA /////////////////

/////////////////////////////////////////////////////////////////////////////
// CCurvatureAppDoc serialization

void CCurvatureAppDoc::Serialize(CArchive& ar)
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
// CCurvatureAppDoc diagnostics

#ifdef _DEBUG
void CCurvatureAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCurvatureAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/*----------------- Inventor-specific Debug Command (***) ------------------*/

void CCurvatureAppDoc::OnDebugState() 
{
	return;
}

void CCurvatureAppDoc::OnUpdateDebugState(CCmdUI* pCmdUI) 
{
	if(!m_pReferenceFileMgr->IsReferencingInventorFile())
    pCmdUI->Enable(FALSE);
  else
    pCmdUI->Enable(TRUE);

	return;
}
