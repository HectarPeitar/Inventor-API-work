/*
  DESCRIPTION

  This file contains the implementation of the class that offers the first contact with
  Autodesk Inventor (R).

*/

#include "stdafx.h"

#include "rxSweepFeature.h"
#include "SweepFeature.h"
#include "AfxCtl.h"

// The addin wizard adds command id definitions here.
#define CMD_CreateSweepFeature			0

/*--------------------- IUnknown-interface related implementation  --------------------------------*/

/*
 * All of the standard IUnknown interfaces are taken care of in the CUnknown
 * class. The implementation in the CUnknown class relies on this override that
 * should end up looking like a non-delegating QueryInterface, except for the fact that QI
 * for the IUnknown is also taken care of by CUnknown (control will never reach here if
 * QI-ed for IUnknown).
 */

HRESULT CRxSweepFeature::InternalQueryInterface (REFIID riid, void **ppv)
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

CRxSweepFeature::CRxSweepFeature () : CUnknown (NULL)
{ 
  m_pSite = NULL;
  m_pButtonEvents1 = new CButtonDefEvents(this, CMD_CreateSweepFeature);

  m_btnDefCookie1 = 0;

  ::IncrementObjectCount();
}

CRxSweepFeature::~CRxSweepFeature()
{
  AFX_MANAGE_STATE (AfxGetAppModuleState()); 

  if (m_pSite)
    m_pSite->Release();

  if(m_pButtonEvents1)
	delete m_pButtonEvents1;

  m_pBtnDef1 = NULL;

  ::DecrementObjectCount();
}

/*---------------------- IRxApplicationAddInServer interface ---------------------------------*/

HRESULT CRxSweepFeature::Activate (IRxApplicationAddInSite *pAddInSite, BooleanType bFirstTime)
{
  AFX_MANAGE_STATE (AfxGetStaticModuleState()); 
  HRESULT Result=NOERROR;
  IUnknown *pAppUnk=NULL;
  variant_t vInTools(VARIANT_TRUE);

  // High-level interfaces supplied directly and implicitly by Autodesk Inventor (R) to the
  // AddIn. These may be held right up until the directive to shutdown (Deactivate) is received.

  m_pSite = pAddInSite;
  m_pSite->AddRef();

  Result = pAddInSite->get_Application (&pAppUnk);
  OnError (FAILED (Result), wrapup);

  Result = pAppUnk->QueryInterface (DIID_Application, (void **) &m_pApplication);
  OnError (FAILED (Result), wrapup);
  
  pAppUnk->Release();
  pAppUnk = NULL;

  // This is where you would place your startup.
  // AfxMessageBox("SweepFeature is loaded.");

  CreateCommands();

  
wrapup:
  if (pAppUnk)
    pAppUnk->Release();

  return Result;
}
    
HRESULT CRxSweepFeature::Deactivate ()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());
	HRESULT Result=NOERROR;

	// This is where you would place your shutdown procedure (releasing any resources,
	// interfaces, cleaning up your GUI, etc.)


	// disconnect event sinks
	if(m_btnDefCookie1)
	{
		BOOL bUnadvised = AfxConnectionUnadvise(m_pBtnDef1, DIID_ButtonDefinitionSink,
											  m_pButtonEvents1->GetInterface(&IID_IUnknown),
											  TRUE, m_btnDefCookie1);
		m_btnDefCookie1 = 0;
	}

	m_pBtnDef1 = NULL;


	// Cleanup up of interfaces supplied by Autodesk Inventor (R) and held on by this AddIn 
	// at initialization or load.

	m_pApplication->Release();
	m_pApplication = NULL;

	 m_pSite->Release();
	m_pSite = NULL;

	return Result;
}


HRESULT CRxSweepFeature::ExecuteCommand (long CommandID)
{
  HRESULT Result=NOERROR;

  // If this AddIn has instantiated commands within Autodesk Inventor (R), it must be ready to 
  // handle this message. Within this call, the specific command (identified
  // by its 'CommandID' which has been supplied by the AddIn at command-creation time)
  // must be executed.

  switch (CommandID)
  {
    case CMD_CreateSweepFeature: 
      Result = CreateSweepFeature();
      break;
    default:
      Result = E_NOTIMPL;
  }

  return Result;
}

HRESULT CRxSweepFeature::get_Automation (IUnknown **ppUnk)
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

HRESULT CRxSweepFeature::CreateSweepFeature()
{
	// Create a new part document, using the default part template.
    
	CComBSTR templateFilename; 
    // Get part document template
	HRESULT hr = m_pApplication->GetTemplateFile(kPartDocumentObject,
												 kDefaultSystemOfMeasure,
												 kDefault_DraftingStandard,
												 CComVariant(),
												 &templateFilename);
	OnErrorReturn(FAILED(hr), hr);

	// Get Documents collection
	CComPtr<Documents> pDocs;
	hr = m_pApplication->get_Documents(&pDocs);
	OnErrorReturn(FAILED(hr), hr);

    // Create a new part document, using the default part template. 
	CComPtr<Document> pDocument;
	hr = pDocs->Add(kPartDocumentObject, templateFilename, VARIANT_TRUE, &pDocument);
	OnErrorReturn(FAILED(hr), hr);
             
    // convert generic document to partdocument
	CComQIPtr<PartDocument> pPartDocument(pDocument);
	
	// Set a reference to the component definition.
	CComPtr<PartComponentDefinition> pPartDef;
	hr = pPartDocument->get_ComponentDefinition(&pPartDef); 
	OnErrorReturn(FAILED(hr), hr);
    
	// Get PlanarSketches
	CComPtr<PlanarSketches> pSketches;
	hr = pPartDef->get_Sketches(&pSketches);
	OnErrorReturn(FAILED(hr), hr);

	// Get standard WorkPlanes
	CComPtr<WorkPlanes> pWorkPlanes ;
	hr = pPartDef->get_WorkPlanes(&pWorkPlanes);
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

	// Create point 1 (start point of 2d arc)
	CComPtr<Point2d> pPoint1;
	hr = pTrGeom->CreatePoint2d(0, 0, &pPoint1);
	OnErrorReturn(FAILED(hr), hr);

	// Create point 2 (end point of 2d arc)
	CComPtr<Point2d> pPoint2;
	hr = pTrGeom->CreatePoint2d(2, 0, &pPoint2);
	OnErrorReturn(FAILED(hr), hr);

	// Create center point
	CComPtr<Point2d> pArcCenterPoint;
	hr = pTrGeom->CreatePoint2d(1, 1, &pArcCenterPoint);
	OnErrorReturn(FAILED(hr), hr);

	// Get SketchArcs
	CComPtr<SketchArcs> pArcs2d;
	hr = pSketch->get_SketchArcs(&pArcs2d);
	OnErrorReturn(FAILED(hr), hr);

	// Add the 2d arc segment of sweep path
	CComPtr<SketchArc> pArc2d;
    hr = pArcs2d->AddByCenterStartEndPoint(pArcCenterPoint, pPoint1, pPoint2, VARIANT_TRUE, &pArc2d);
	OnErrorReturn(FAILED(hr), hr);
	
	// Get Sketches3D
	CComPtr<Sketches3D> pSketches3D;
	hr = pPartDef->get_Sketches3D(&pSketches3D);
	OnErrorReturn(FAILED(hr), hr);

	// Create a new 3D sketch.
    CComPtr<Sketch3D> pSketch3D; 
    hr = pSketches3D->Add(&pSketch3D);
	OnErrorReturn(FAILED(hr), hr);

	// include (project) the end point of the 2d arc
	// to be used as the start point of a 3d line

	CComPtr<SketchPoint> pEndPoint2d;
	hr = pArc2d->get_EndSketchPoint(&pEndPoint2d);
	OnErrorReturn(FAILED(hr), hr);
	
	CComPtr<SketchEntity3D> pEntity3D;
	hr = pSketch3D->Include(pEndPoint2d, &pEntity3D);
	OnErrorReturn(FAILED(hr), hr);

	CComQIPtr<SketchPoint3D> p3dSketchPoint1(pEntity3D);

	// Create a fixed work point to be used as the end
	// point of the 3d line

	CComPtr<WorkPoints> pWorkPoints ;
	hr = pPartDef->get_WorkPoints(&pWorkPoints);
	OnErrorReturn(FAILED(hr), hr);
	
	// Create point
	CComPtr<Point> p3dPoint1;
	hr = pTrGeom->CreatePoint(4, 2, 2, &p3dPoint1);
	OnErrorReturn(FAILED(hr), hr);
	
	CComPtr<WorkPoint> pWorkPoint1;
	hr = pWorkPoints->AddFixed(p3dPoint1, false, &pWorkPoint1);
	OnErrorReturn(FAILED(hr), hr);

	// Get SketchLines3D
	CComPtr<SketchLines3D> pLines3d;
	hr = pSketch3D->get_SketchLines3D(&pLines3d);
	OnErrorReturn(FAILED(hr), hr);

	// Add a 3D line segment of sweep path
	CComPtr<SketchLine3D> p3dLine1;
	hr = pLines3d->AddByTwoPoints(p3dSketchPoint1, pWorkPoint1, false, CComVariant(), &p3dLine1);
	OnErrorReturn(FAILED(hr), hr);

	// Get the end point of the 3d line to be used as 
	// the start point of the next 3d line
	CComPtr<IDispatch> pDispatch;
	hr = p3dLine1->get_EndPoint(&pDispatch);
	OnErrorReturn(FAILED(hr), hr);

	CComQIPtr<SketchPoint3D> p3dSketchPoint2(pDispatch);

	// Create a fixed work point to be used as the end
	// point of the 3d line

	// Create point
	CComPtr<Point> p3dPoint2;
	hr = pTrGeom->CreatePoint(4, -2, 2, &p3dPoint2);
	OnErrorReturn(FAILED(hr), hr);
	
	CComPtr<WorkPoint> pWorkPoint2;
	hr = pWorkPoints->AddFixed(p3dPoint2, false, &pWorkPoint2);
	OnErrorReturn(FAILED(hr), hr);

	// Add the next 3D line segment of sweep path
	CComPtr<SketchLine3D> p3dLine2;
    hr = pLines3d->AddByTwoPoints(p3dSketchPoint2, pWorkPoint2, VARIANT_TRUE, CComVariant(), &p3dLine2);
	OnErrorReturn(FAILED(hr), hr);


	// To create the sweep profile, add a sketch by creating a workplane
	// normal to the first segment (arc) and at its start point.

	CComPtr<SketchPoint> pStartPoint2d;
	hr = pArc2d->get_StartSketchPoint(&pStartPoint2d);
	OnErrorReturn(FAILED(hr), hr);

	CComPtr<WorkPlane> pProfileWorkPlane ;
	hr = pWorkPlanes->AddByNormalToCurve(pArc2d, pStartPoint2d, false, &pProfileWorkPlane);
	OnErrorReturn(FAILED(hr), hr);

	// Create a new sketch on this work plane.
    CComPtr<PlanarSketch> pProfileSketch; 
    hr = pSketches->Add(pProfileWorkPlane, false, &pProfileSketch);
	OnErrorReturn(FAILED(hr), hr);

	// Project the start point of 2d arc (this will be the
	// center of a circle (the profile) )
	CComPtr<SketchEntity> pSketchEntity;
	hr = pProfileSketch->AddByProjectingEntity(pStartPoint2d, &pSketchEntity);
	OnErrorReturn(FAILED(hr), hr);

	CComQIPtr<SketchPoint> pCenterPoint(pSketchEntity);

	// Get SketchCircles
	CComPtr<SketchCircles> pCircles;
	hr = pProfileSketch->get_SketchCircles(&pCircles);
	OnErrorReturn(FAILED(hr), hr);

	// Draw a circle
	CComPtr<SketchCircle> pCircle;
	hr = pCircles->AddByCenterRadius(pCenterPoint, 0.5, &pCircle);
	OnErrorReturn(FAILED(hr), hr);

	// Get Profiles collection
	CComPtr<Profiles> pProfiles;
	hr = pProfileSketch->get_Profiles(&pProfiles);
	OnErrorReturn(FAILED(hr), hr);

	// Create profile for sweep
	CComPtr<Profile> pProfile;
    hr = pProfiles->AddForSolid(VARIANT_TRUE, vtMissing, vtMissing, &pProfile);
	OnErrorReturn(FAILED(hr), hr);

	// Get Features
	CComPtr<PartFeatures> pFeatures;
	hr = pPartDef->get_Features(&pFeatures);
	OnErrorReturn(FAILED(hr), hr);
	
	// Set a reference to the SweepFeatures collection object.
	CComPtr<SweepFeatures> pSweepFeatures;
	hr = pFeatures->get_SweepFeatures(&pSweepFeatures);
	OnErrorReturn(FAILED(hr), hr);

	// Create the sweep path
	CComPtr<Path> pPath;
	hr = pFeatures->CreatePath(pArc2d, &pPath);
	OnErrorReturn(FAILED(hr), hr);

	// Create the sweep feature
	CComPtr<SweepFeature> pSweepFeature;
	hr = pSweepFeatures->AddUsingPath(pProfile, pPath, kJoinOperation, kNormalToPath, CComVariant(), &pSweepFeature);
	OnErrorReturn(FAILED(hr), hr);

	return S_OK;
}

void CRxSweepFeature::CreateCommands()
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
	vtAddInId	      = _T("{2CDA1EC9-A800-4606-AA31-FCC77D8E3CA0}");
	// command type
	eCmdType = kQueryOnlyCmdType;
	// button display type
	eCmdDisplayType = kAlwaysDisplayText;


	// Add the Create Sweep Feature command
	InternalNameBSTR  =	_T("SweepFeatureAddIn.CreateCmd");
	displayNameBSTR	  =	_T("CreateSweepFeature");
	DesTextBSTR		  =	_T("Execute Create Sweep Feature Command");
	TooltipTextBSTR	  =	_T("Create Sweep Feature");
	

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
}


/////////////////////////////////////////////////////////////////////////////
// CButtonDefEvents

IMPLEMENT_DYNCREATE(CButtonDefEvents, CCmdTarget)

CButtonDefEvents::CButtonDefEvents(CRxSweepFeature* pAddIn, UINT nID) : m_pAddIn(pAddIn), m_nID(nID)
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

void CButtonDefEvents::OnExecuteEvent(NameValueMap *context) 
{
	if(m_pAddIn)
		m_pAddIn->ExecuteCommand(m_nID);
}


