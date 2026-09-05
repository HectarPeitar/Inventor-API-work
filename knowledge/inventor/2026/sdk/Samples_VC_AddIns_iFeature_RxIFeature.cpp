/*
  DESCRIPTION

  This file contains the implementation of the class that offers the first contact with
  Autodesk Inventor (R).

*/

#include "stdafx.h"

#include "rxIFeature.h"
#include "IFeature.h"
#include "AfxCtl.h"

static HINSTANCE s_hInst = NULL;

// The addin wizard adds command id definitions here.
#define CMD_PlaceiFeature			0
#define CMD_PlaceTableDriveniFeature			1

/*--------------------- IUnknown-interface related implementation  --------------------------------*/

/*
 * All of the standard IUnknown interfaces are taken care of in the CUnknown
 * class. The implementation in the CUnknown class relies on this override that
 * should end up looking like a non-delegating QueryInterface, except for the fact that QI
 * for the IUnknown is also taken care of by CUnknown (control will never reach here if
 * QI-ed for IUnknown).
 */

HRESULT CRxIFeature::InternalQueryInterface (REFIID riid, void **ppv)
{
  HRESULT Result = NOERROR;

  OnErrorState (!ppv, Result, E_INVALIDARG, wrapup);
  *ppv = NULL;

  if (IsEqualIID (riid, __uuidof (IRxApplicationAddInServer)))
    *ppv = static_cast<void *> (static_cast<IRxApplicationAddInServer *> (this));
  else
    Result = E_NOINTERFACE;

  if (SUCCEEDED (Result))
    ((LPUNKNOWN)*ppv)->AddRef();

wrapup:          
  return (Result);
}

/*---------------------- Constructor(s), initializers and destructor ---------------------------------*/

CRxIFeature::CRxIFeature () : CUnknown (NULL)
{ 
  m_pAddInSite = NULL;

  m_pButtonEvents1 = new CButtonDefEvents(this, CMD_PlaceiFeature);
  m_pButtonEvents2 = new CButtonDefEvents(this, CMD_PlaceTableDriveniFeature);
  	
  m_btnDefCookie1 = 0;
  m_btnDefCookie2 = 0;
  
  ::IncrementObjectCount();
}

CRxIFeature::~CRxIFeature()
{
  AFX_MANAGE_STATE (AfxGetAppModuleState()); 

  if (m_pAddInSite)
    m_pAddInSite = NULL;

  if(m_pButtonEvents1)
	delete m_pButtonEvents1;

  if(m_pButtonEvents2)
	delete m_pButtonEvents2;

  m_pBtnDef1 = NULL;
  m_pBtnDef2 = NULL;

  ::DecrementObjectCount();
}

/*---------------------- IRxApplicationAddInServer interface ---------------------------------*/

HRESULT CRxIFeature::Activate (IRxApplicationAddInSite *pAddInSite, BooleanType bFirstTime)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState()); 

	HRESULT Result = NOERROR;

	s_hInst = AfxGetInstanceHandle();
	OnErrorReturn(!s_hInst, E_FAIL);

	CComPtr<IUnknown> pAppUnk;
	CComPtr<IUnknown> pCmdUnk;

	// High-level interfaces supplied directly and implicitly by Inventor to the
	// AddIn. These may be held right up until the directive to shutdown (Deactivate) is received.

	m_pAddInSite = pAddInSite;
	Result = pAddInSite->get_Application(&pAppUnk);
	OnErrorReturn (FAILED (Result), Result);

	Result = pAppUnk->QueryInterface(DIID_Application, (void **) &m_pApplication);
	OnErrorReturn (FAILED (Result), Result);
  
	CreateCommands();

	return Result;
}
    
HRESULT CRxIFeature::Deactivate ()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());
	HRESULT Result=NOERROR;

	// disconnect event sinks
	if(m_btnDefCookie1)
	{
		BOOL bUnadvised = AfxConnectionUnadvise(m_pBtnDef1, DIID_ButtonDefinitionSink, m_pButtonEvents1->GetInterface(&IID_IUnknown), TRUE, m_btnDefCookie1);
		m_btnDefCookie1 = 0;
	}
    
	if(m_btnDefCookie2)
	{
		BOOL bUnadvised = AfxConnectionUnadvise(m_pBtnDef2, DIID_ButtonDefinitionSink, m_pButtonEvents2->GetInterface(&IID_IUnknown), TRUE, m_btnDefCookie2);
		m_btnDefCookie2 = 0;
	}

	// Cleanup up of interfaces supplied by Autodesk Inventor (R) and held on by this AddIn 
	// at initialization or load.

	m_pBtnDef1 = NULL;
    m_pBtnDef2 = NULL;

	m_pApplication = NULL;
	m_pAddInSite = NULL;

	return Result;
}


HRESULT CRxIFeature::ExecuteCommand (long CommandID)
{
  HRESULT Result=E_NOTIMPL;

  return Result;
}

HRESULT CRxIFeature::get_Automation (IUnknown **ppUnk)
{
  HRESULT Result=NOERROR;

  if (!ppUnk)
    return E_INVALIDARG;
  *ppUnk = NULL;
  
  // TODO:  
  // If this AddIn wanted to expose any of its Automation API, it must do so by
  // returning its top-level interface through this method.

  Result = E_NOINTERFACE;

  return Result;
}


HRESULT CRxIFeature::PlaceiFeature()
{
	AFX_MANAGE_STATE (AfxGetAppModuleState());

	OnErrorReturn(!m_pApplication, E_INVALIDARG);

	HRESULT hr = S_OK;

	// Create new part document with an extrusion
	CComPtr<PartDocument> pPartDoc;
	CComPtr<PartComponentDefinition> pPartDef;
	CComPtr<iFeatureDefinition> piFeatDef;
	CComPtr<Face> pFace;
	CComPtr<PartFeatures> pPartFeats;
	CComPtr<iFeatures> piFeats;
	CComPtr<iFeature> piFeat;

	hr = CreateNewPart(&pPartDoc, &pPartDef, &pFace);
	OnErrorReturn(FAILED(hr), hr);

	hr = pPartDef->get_Features(&pPartFeats);
	OnErrorReturn(FAILED(hr), hr);

	hr = pPartFeats->get_iFeatures(&piFeats);
	OnErrorReturn(FAILED(hr), hr);

	hr = CreateiFeatDef(piFeats, pFace, &piFeatDef);
	OnErrorReturn(FAILED(hr), hr);

	// Create a new iFeature by adding the completed definition
	hr = piFeats->Add(piFeatDef,&piFeat);
	OnErrorReturn(FAILED(hr), hr);

	return hr;
}

HRESULT CRxIFeature::PlaceTableDriveniFeature()
{
	AFX_MANAGE_STATE (AfxGetAppModuleState());

	OnErrorReturn(!m_pApplication, E_INVALIDARG);

	HRESULT hr = S_OK;

	// Create new part document with an extrusion
	CComPtr<PartDocument> pPartDoc;
	CComPtr<PartComponentDefinition> pPartDef;
	CComPtr<iFeatureDefinition> pTableDriveniFeatDef;
	CComPtr<Face> pFace;
	CComPtr<PartFeatures> pPartFeats;
	CComPtr<iFeatures> piFeats;
	CComPtr<iFeature> pTableDriveniFeat;

	hr = CreateNewPart(&pPartDoc, &pPartDef, &pFace);
	OnErrorReturn(FAILED(hr), hr);

	hr = pPartDef->get_Features(&pPartFeats);
	OnErrorReturn(FAILED(hr), hr);

	hr = pPartFeats->get_iFeatures(&piFeats);
	OnErrorReturn(FAILED(hr), hr);

	hr = CreateTableDriveniFeatDef(piFeats, pFace, &pTableDriveniFeatDef);
	OnErrorReturn(FAILED(hr), hr);

	// Create a new iFeature by adding the completed definition
	hr = piFeats->Add(pTableDriveniFeatDef,&pTableDriveniFeat);
	OnErrorReturn(FAILED(hr), hr);

	return hr;
}

HRESULT CRxIFeature::CreateNewPart(PartDocument **pPartDoc, PartComponentDefinition **pPartDef, Face **pFace)
{
	HRESULT hr = S_OK;
	
	// Get Documents collection
	CComPtr<Documents> pDocs;
	hr = m_pApplication->get_Documents(&pDocs);
	OnErrorReturn(FAILED(hr), hr);
		
    // Get part document template
	CComPtr<FileManager> pFileManager;
	hr = m_pApplication->get_FileManager(&pFileManager);
	OnErrorReturn(FAILED(hr), hr);

	CComBSTR templateFilename;
	hr = pFileManager->GetTemplateFile(kPartDocumentObject,
										 kDefaultSystemOfMeasure,
										 kDefault_DraftingStandard,
										 CComVariant(),
										 &templateFilename);
	OnErrorReturn(FAILED(hr), hr);

    // Create a new part document, using the default part template. 
	CComPtr<Document> pDoc;
	hr = pDocs->Add(kPartDocumentObject, templateFilename, VARIANT_TRUE, &pDoc);
	OnErrorReturn(FAILED(hr), hr);

	//pPartDoc = CComQIPtr<PartDocument>(pDoc);
	pDoc.QueryInterface(pPartDoc);
	OnErrorReturn(!pPartDoc, E_FAIL);
	
	// Set a reference to the component definition.
	hr = (*pPartDoc)->get_ComponentDefinition(pPartDef); 
	OnErrorReturn(FAILED(hr), hr);

	// Get PlanarSketches
	CComPtr<PlanarSketches> pSketches;
	hr = (*pPartDef)->get_Sketches(&pSketches);
	OnErrorReturn(FAILED(hr), hr);

	// Get standard WorkPlanes
	CComPtr<WorkPlanes> pWorkPlanes ;
	hr = (*pPartDef)->get_WorkPlanes(&pWorkPlanes);
	OnErrorReturn(FAILED(hr), hr);
	
	// Get the standard XY work plane
	CComPtr<WorkPlane> pWorkPlane ;
	hr = pWorkPlanes->get_Item(CComVariant(3), &pWorkPlane);
	OnErrorReturn(FAILED(hr), hr);

    // Create a new sketch on the X-Y work plane.
    CComPtr<PlanarSketch> pSketch; 
    hr = pSketches->Add(pWorkPlane, false, &pSketch);
	OnErrorReturn(FAILED(hr), hr);

	// Set reference to transient geometry object
	CComPtr<TransientGeometry> pTrGeom;
	hr = m_pApplication->get_TransientGeometry(&pTrGeom); 
	OnErrorReturn(FAILED(hr), hr);

	// Create lower left corner point (-4, -4)
	CComPtr<Point2d> pPoint1;
	hr = pTrGeom->CreatePoint2d(-4, -4, &pPoint1);
	OnErrorReturn(FAILED(hr), hr);

	// Create upper right corner point (4, 4)
	CComPtr<Point2d> pPoint2;
	hr = pTrGeom->CreatePoint2d(4, 4, &pPoint2);
	OnErrorReturn(FAILED(hr), hr);

	// Get the SketchLines collection
	CComPtr<SketchLines> pSketchLines;
	hr = pSketch->get_SketchLines(&pSketchLines);
	OnErrorReturn(FAILED(hr), hr);
	
	// Draw a rectangle
	CComPtr<SketchEntitiesEnumerator> pSketchEnts;
	hr = pSketchLines->AddAsTwoPointRectangle(pPoint1, pPoint2, &pSketchEnts);
	OnErrorReturn(FAILED(hr), hr);

	// Get the Profiles collection
	CComPtr<Profiles> pProfiles;
	hr = pSketch->get_Profiles(&pProfiles);
	OnErrorReturn(FAILED(hr), hr);

	// Get the Profile
	CComPtr<Profile> pProfile;
	hr = pProfiles->AddForSolid(VARIANT_TRUE, vtMissing, vtMissing, &pProfile);
	OnErrorReturn(FAILED(hr), hr);

	// Get the Features collection
	CComPtr<PartFeatures> pFeats;
	hr = (*pPartDef)->get_Features(&pFeats);
	OnErrorReturn(FAILED(hr), hr);

	// Get the Extrusion features collection
	CComPtr<ExtrudeFeatures> pExtrudeFeats;
	hr = pFeats->get_ExtrudeFeatures(&pExtrudeFeats);
	OnErrorReturn(FAILED(hr), hr);
	
	// Create an extrusion using the rectangular profile
	CComPtr<ExtrudeFeature> pExtrude;
	hr = pExtrudeFeats->AddByDistanceExtent(pProfile, 
		                                    CComVariant(8), 
		      							    kSymmetricExtentDirection, 
											kJoinOperation, 
											CComVariant(0), 
											&pExtrude);
	OnErrorReturn(FAILED(hr), hr);

	// Get the faces collection for the extrusion feature
	CComPtr<Faces> pFaces;
	hr = pExtrude->get_Faces(&pFaces);
	OnErrorReturn(FAILED(hr), hr);

	// Get the first face on the extrusion
	return pFaces->get_Item(6, pFace);
}

HRESULT CRxIFeature::CreateiFeatDef(iFeatures *piFeats, Face *pFace, iFeatureDefinition **piFeatDef)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	HRESULT hr = S_OK;

	CComPtr<iFeatureInputs> piFeatInputs;
	CComPtr<iFeatureInput>	piFeatInput;
	CComPtr<iFeature> piFeat;
	CComPtr<iFeatureSketchPlaneInput> piFeatSketchPlaneInput;
	long piFeatCount = 0;
	long piFeatItr = 0;

	TCHAR szDllFileName[MAX_PATH];

	HRESULT Result = NOERROR;
	DWORD Status = GetModuleFileName (s_hInst, szDllFileName, MAX_PATH);

	CString path(szDllFileName);

	path.MakeLower();

	int index = path.Find(_T("vc++"));
	OnErrorReturn(index == -1, E_FAIL);

	// Trim the string to the left iFeature
	CString sRelPath = path.Left(index);

	// Add the remaining path to the string
	sRelPath += CString(_T("Data_Files\\ArrowX.ide"));
	
	hr = piFeats->CreateiFeatureDefinition(CComBSTR(sRelPath), piFeatDef);
	OnErrorReturn(FAILED(hr), hr);

	hr = (*piFeatDef)->get_iFeatureInputs(&piFeatInputs);
	OnErrorReturn(FAILED(hr), hr);

	hr = piFeatInputs->get_Count(&piFeatCount);
	OnErrorReturn(FAILED(hr), hr);

	for(piFeatItr=1;piFeatItr<=piFeatCount;piFeatItr++)
	{
		hr = piFeatInputs->get_Item(piFeatItr, &piFeatInput);
		OnErrorReturn(FAILED(hr), hr);

		ObjectTypeEnum eType;
		hr = piFeatInput->get_Type(&eType);
		OnErrorReturn(FAILED(hr), hr);

		if ( eType == kiFeatureSketchPlaneInputObject )
		{
			piFeatSketchPlaneInput = CComQIPtr<iFeatureSketchPlaneInput>(piFeatInput);
			break;
		}
	}

	// Assign the face to the sketch plane input
	hr = piFeatSketchPlaneInput->put_PlaneInput(pFace);
	OnErrorReturn(FAILED(hr), hr);

	// Get the Edges collection on the selected face
	CComPtr<Edges> pEdges;
	hr = pFace->get_Edges(&pEdges);
	OnErrorReturn(FAILED(hr), hr);

	// Get the first edge on the selected face
	CComPtr<Edge> pEdge;
	hr = pEdges->get_Item(1, &pEdge);
	OnErrorReturn(FAILED(hr), hr);

	// Get the start vertex for the first edge
	CComPtr<Vertex> pVtx;
	hr = pEdge->get_StartVertex(&pVtx);
	OnErrorReturn(FAILED(hr), hr);

	// Get the point for the start vertex. This is the placement point
	CComPtr<Point> pPlacePoint;
	hr = pVtx->get_Point(&pPlacePoint);
	OnErrorReturn(FAILED(hr), hr);

	// Get the third edge
	CComPtr<Edge> pEdge2;
	hr = pEdges->get_Item(3, &pEdge2);
	OnErrorReturn(FAILED(hr), hr);

	// Get the start vertex for the third edge
	CComPtr<Vertex> pVtx2;
	hr = pEdge2->get_StartVertex(&pVtx2);
	OnErrorReturn(FAILED(hr), hr);

	// Get the point for the start vertex on the third edge
	CComPtr<Point> pVecPoint;
	hr = pVtx2->get_Point(&pVecPoint);
	OnErrorReturn(FAILED(hr), hr);

	// Create a vector between the placement point and the vector point
	CComPtr<Vector> pDirVec;
	hr = pPlacePoint->VectorTo(pVecPoint, &pDirVec);
	OnErrorReturn(FAILED(hr), hr);

	// Set the position and direction for the iFeature
	return piFeatSketchPlaneInput->SetPosition(pPlacePoint, pDirVec, 0);
}

HRESULT  CRxIFeature::CreateTableDriveniFeatDef(iFeatures *piFeats, Face *pFace, iFeatureDefinition **piFeatDef)
{
	HRESULT hr = S_OK;

	TCHAR szDllFileName[MAX_PATH];

	HRESULT Result = NOERROR;
	DWORD Status = GetModuleFileName (s_hInst, szDllFileName, MAX_PATH);

	CString path(szDllFileName);

	path.MakeLower();

	int index = path.Find(_T("vc++"));
	OnErrorReturn(index == -1, E_FAIL);

	// Trim the string to the left iFeature
	CString sRelPath = path.Left(index);

	// Add the remaining path to the string
	sRelPath += CString(_T("Data_Files\\Block.ide"));

	hr = piFeats->CreateiFeatureDefinition(CComBSTR(sRelPath),piFeatDef);
	OnErrorReturn(FAILED(hr),hr);

	CComPtr<iFeatureInput> pInput;
	CComPtr<iFeatureInputs> pInputs;
	hr = (*piFeatDef)->get_iFeatureInputs(&pInputs);
	OnErrorReturn(FAILED(hr),hr);

	for(long i=1;i<pInputs->Count;i++)
	{
		pInput = NULL;
		hr = pInputs->get_Item(i,&pInput);
		OnErrorReturn(FAILED(hr),hr);

		if(_tcscmp(pInput->Prompt,_T("Pick a planar face or workplane"))==0)
		{
			CComQIPtr<iFeatureSketchPlaneInput> pPlaneInput;
			pPlaneInput = pInput;
			if(pPlaneInput ==NULL)
				return S_FALSE;

			hr = pPlaneInput->put_PlaneInput(pFace);
			OnErrorReturn(FAILED(hr),hr);

			break;
		}
	}

	CComPtr<iFeatureTable> pTable;
	hr = (*piFeatDef)->get_iFeatureTable(&pTable);
	OnErrorReturn(FAILED(hr),hr);

	CComPtr<iFeatureTableColumn> pTableColumn;
	CComPtr<iFeatureTableColumns> pTableColumns;

	hr = pTable->get_iFeatureTableColumns(&pTableColumns);
	OnErrorReturn(FAILED(hr),hr);

	BOOL bFoundDistance = false;
	long count;

	hr = pTableColumns->get_Count(&count);
	OnErrorReturn(FAILED(hr),hr);

	for(long i =1;i<count;i++)
	{
		pTableColumn = NULL;
		hr = pTableColumns->get_Item(CComVariant(i),&pTableColumn);

		CComBSTR DisplayHeading;
		hr = pTableColumn->get_DisplayHeading(&DisplayHeading);
		if(_tcscmp(DisplayHeading,_T("Distance"))==0)
		{
			bFoundDistance = true;
			break;
		}
	}

	if(bFoundDistance == false)
	{
		AfxMessageBox(_T("The column Distance was not found"));
		return S_FALSE;
	}

	BOOL bFoundLength = false;
	CComPtr<iFeatureTableCell> pCell;

	for(long i=1;i<pTableColumn->Count;i++)
	{
		pCell = NULL;
		hr = pTableColumn->get_Item(CComVariant(i),&pCell);
		CComBSTR CellValue;
		hr = pCell->get_Value(&CellValue);
		if(_tcscmp(CellValue,_T("1 in"))==0)
		{
			bFoundLength = true;
			break;
		}
	}

	if(bFoundLength == false)
	{
		AfxMessageBox(_T("The distance value 1 in was not found"));
		return S_FALSE;
	}

	CComPtr<iFeatureTableRow> pTableRow;
	hr = pCell->get_Row(&pTableRow);
	OnErrorReturn(FAILED(hr),hr);

	hr = (*piFeatDef)->put_ActiveTableRow(pTableRow);

	return S_OK;
}

void CRxIFeature::CreateCommands()
{
	ATLASSERT(m_pApplication);

	if(!m_pApplication)
		return;

	CComPtr<CommandManager> pCommandMgr;
	HRESULT hr = m_pApplication->get_CommandManager(&pCommandMgr);

	CComPtr<ControlDefinitions> pCtrlDefs;
	hr = pCommandMgr->get_ControlDefinitions(&pCtrlDefs);
	
	CComVariant vtAddInId;
	CComBSTR InternalNameBSTR;
	CComBSTR displayNameBSTR;
	CComBSTR DesTextBSTR;
	CComBSTR TooltipTextBSTR;
	CComVariant vtEmpty;
	CommandTypesEnum eCmdType;
	ButtonDisplayEnum eCmdDisplayType;

	// common button parameters
	// client Id for the buttons
	vtAddInId	      = _T("{90E841C3-C126-45FD-A985-FDFA6BC30C37}");
	// command type
	eCmdType = kQueryOnlyCmdType;
	// button display type
	eCmdDisplayType = kAlwaysDisplayText;

	// Add the Place iFeature command
	InternalNameBSTR  =	_T("iFeatureAddIn.PlaceiFeatureCmd");
	displayNameBSTR	  =	_T("PlaceiFeature");
	DesTextBSTR		  =	_T("Execute Place iFeature Command");
	TooltipTextBSTR	  =	_T("Place iFeature");
	

	hr = pCtrlDefs->AddButtonDefinition(displayNameBSTR, InternalNameBSTR,eCmdType,vtAddInId,DesTextBSTR,TooltipTextBSTR,vtEmpty,vtEmpty,eCmdDisplayType,&m_pBtnDef1); 

	ATLASSERT(SUCCEEDED(hr));
	ATLASSERT(m_pBtnDef1 != NULL);

	m_pBtnDef1->put_Enabled(VARIANT_TRUE);

	if(m_pBtnDef1)
	{
		BOOL bBrwsrAdvised = AfxConnectionAdvise(m_pBtnDef1, DIID_ButtonDefinitionSink,
                                m_pButtonEvents1->GetInterface(&IID_IUnknown),
                                TRUE, &m_btnDefCookie1);

		ATLASSERT(bBrwsrAdvised == TRUE);
	}

	hr = m_pBtnDef1->AutoAddToGUI();
	ATLASSERT(SUCCEEDED(hr));

	InternalNameBSTR  =	_T("iFeatureAddIn.PlaceTableDriveniFeatureCmd");
	displayNameBSTR	  =	_T("PlaceTableDriveniFeature");
	DesTextBSTR		  =	_T("Execute Place Table Driven iFeature Command");
	TooltipTextBSTR	  =	_T("Place Table Driven iFeature");


	hr = pCtrlDefs->AddButtonDefinition(displayNameBSTR, InternalNameBSTR,eCmdType,vtAddInId,DesTextBSTR,TooltipTextBSTR,vtEmpty,vtEmpty,eCmdDisplayType,&m_pBtnDef2); 

	ATLASSERT(SUCCEEDED(hr));
	ATLASSERT(m_pBtnDef2 != NULL);

	m_pBtnDef2->put_Enabled(VARIANT_TRUE);

	if(m_pBtnDef2)
	{
		BOOL bBrwsrAdvised = AfxConnectionAdvise(m_pBtnDef2, DIID_ButtonDefinitionSink,
			m_pButtonEvents2->GetInterface(&IID_IUnknown),
			TRUE, &m_btnDefCookie2);

		ATLASSERT(bBrwsrAdvised == TRUE);
	}

	hr = m_pBtnDef2->AutoAddToGUI();
	ATLASSERT(SUCCEEDED(hr));
}


/////////////////////////////////////////////////////////////////////////////
// CButtonDefEvents

IMPLEMENT_DYNCREATE(CButtonDefEvents, CCmdTarget)

CButtonDefEvents::CButtonDefEvents(CRxIFeature* pAddIn, UINT nID) : m_pAddIn(pAddIn), m_nID(nID)
{
   EnableAutomation();  // Needed in order to sink events.
}

CButtonDefEvents::~CButtonDefEvents()
{
}


BEGIN_MESSAGE_MAP(CButtonDefEvents, CCmdTarget)
	//{{AFX_MSG_MAP(CButtonDefEvents)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CButtonDefEvents, CCmdTarget)
	DISP_FUNCTION_ID(CButtonDefEvents, "OnExecute", 0x03009c81, OnExecuteEvent, VT_EMPTY, VTS_DISPATCH)
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CButtonDefEvents, CCmdTarget)
	INTERFACE_PART(CButtonDefEvents, DIID_ButtonDefinitionSink, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonDefEvents event handlers

HRESULT CButtonDefEvents::OnExecuteEvent(NameValueMap *context) 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT Result = NOERROR;

	switch (m_nID)
	{
		case CMD_PlaceiFeature: 
		  Result = m_pAddIn->PlaceiFeature();
		  break;
		case CMD_PlaceTableDriveniFeature: 
			Result = m_pAddIn->PlaceTableDriveniFeature();
			break;
		default:
		  Result = E_NOTIMPL;
	}

	return Result;
}
