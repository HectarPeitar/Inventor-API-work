/*
  DESCRIPTION

  This file contains the implementation of the class that offers the first contact with
  Autodesk Inventor (R).

*/

#include "stdafx.h"

#include "rxThreadFeature.h"
#include "ThreadFeature.h"
#include "AfxCtl.h"

// The addin wizard adds command id definitions here.
#define CMD_CreateThreadFeature			0
#define CMD_EditThreadFeature			1

/*--------------------- IUnknown-interface related implementation  --------------------------------*/

/*
 * All of the standard IUnknown interfaces are taken care of in the CUnknown
 * class. The implementation in the CUnknown class relies on this override that
 * should end up looking like a non-delegating QueryInterface, except for the fact that QI
 * for the IUnknown is also taken care of by CUnknown (control will never reach here if
 * QI-ed for IUnknown).
 */

HRESULT CRxThreadFeature::InternalQueryInterface (REFIID riid, void **ppv)
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

CRxThreadFeature::CRxThreadFeature () : CUnknown (NULL)
{ 
  m_pSite = NULL;
  m_bThreadFeatureCreated = false;

  m_pButtonEvents1 = new CButtonDefEvents(this, CMD_CreateThreadFeature);
  m_pButtonEvents2 = new CButtonDefEvents(this, CMD_EditThreadFeature);
	
  m_btnDefCookie1 = 0;
  m_btnDefCookie2 = 0;

  ::IncrementObjectCount();
}

CRxThreadFeature::~CRxThreadFeature()
{
  AFX_MANAGE_STATE (AfxGetAppModuleState()); 

  if (m_pSite)
    m_pSite->Release();

  if(m_pButtonEvents1)
	delete m_pButtonEvents1;

  if(m_pButtonEvents2)
	delete m_pButtonEvents2;

  m_pBtnDef1 = NULL;
  m_pBtnDef2 = NULL;

  ::DecrementObjectCount();
}

/*---------------------- IRxApplicationAddInServer interface ---------------------------------*/

HRESULT CRxThreadFeature::Activate (IRxApplicationAddInSite *pAddInSite, BooleanType bFirstTime)
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


  // TODO:
  // This is where you would place your startup.
  // AfxMessageBox("ThreadFeature is loaded.");

  CreateCommands();


wrapup:
  if (pAppUnk)
    pAppUnk->Release();

  return Result;
}
    
HRESULT CRxThreadFeature::Deactivate ()
{
  AFX_MANAGE_STATE (AfxGetStaticModuleState());
  HRESULT Result=NOERROR;

  // TODO:
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

	if(m_btnDefCookie2)
	{
		BOOL bUnadvised = AfxConnectionUnadvise(m_pBtnDef2, DIID_ButtonDefinitionSink,
											  m_pButtonEvents2->GetInterface(&IID_IUnknown),
											  TRUE, m_btnDefCookie2);
		m_btnDefCookie2 = 0;
	}

	m_pBtnDef1 = NULL;
	m_pBtnDef2 = NULL;

  // Cleanup up of interfaces supplied by Autodesk Inventor (R) and held on by this AddIn 
  // at initialization or load.

  m_pApplication->Release();
  m_pApplication = NULL;

  m_pSite->Release();
  m_pSite = NULL;

  return Result;
}


HRESULT CRxThreadFeature::ExecuteCommand (long CommandID)
{
  HRESULT Result=NOERROR;

  // TODO:
  // If this AddIn has instantiated commands within Autodesk Inventor (R), it must be ready to 
  // handle this message. Within this call, the specific command (identified
  // by its 'CommandID' which has been supplied by the AddIn at command-creation time)
  // must be executed.

  switch (CommandID)
  {
    case CMD_CreateThreadFeature: 
      Result = CreateThreadFeature();
      break;
    case CMD_EditThreadFeature: 
      Result = EditThreadFeature();
      break;
    default:
      Result = E_NOTIMPL;
  }

  return Result;
}

HRESULT CRxThreadFeature::get_Automation (IUnknown **ppUnk)
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

HRESULT CRxThreadFeature::CreateThreadFeature()
{
	AFX_MANAGE_STATE (AfxGetAppModuleState());
	// Create a new part document, using the default part template.
    
	CComBSTR templateFilename; 
    // Get part document template
	CComPtr<FileManager> pFileManager;
	HRESULT hr = m_pApplication->get_FileManager(&pFileManager);
	OnErrorReturn(FAILED(hr), hr);

	hr = pFileManager->GetTemplateFile(kPartDocumentObject,
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

	// Set reference to transient geomtry object
	CComPtr<TransientGeometry> pTrGeom;
	hr = m_pApplication->get_TransientGeometry(&pTrGeom); 
	OnErrorReturn(FAILED(hr), hr);

	// Get SketchCircles
	CComPtr<SketchCircles> pCircles;
	hr = pSketch->get_SketchCircles(&pCircles);
	OnErrorReturn(FAILED(hr), hr);

	// Create center point
	CComPtr<Point2d> pCenterPoint;
	hr = pTrGeom->CreatePoint2d(0, 0, &pCenterPoint);
	OnErrorReturn(FAILED(hr), hr);

	// Create a sketch circle.  (The radius is for 1 5/8 inch diameter shaft.)
    CComPtr<SketchCircle> pCircle;
    hr = pCircles->AddByCenterRadius(pCenterPoint, 4.1275 / 2, &pCircle);
	OnErrorReturn(FAILED(hr), hr);
    
	// Get Profiles
	CComPtr<Profiles> pProfiles;
	hr = pSketch->get_Profiles(&pProfiles);
	OnErrorReturn(FAILED(hr), hr);

	// Create a profile
    CComPtr<Profile> pProfile;
    hr = pProfiles->AddForSolid(VARIANT_TRUE, vtMissing, vtMissing, &pProfile);
	OnErrorReturn(FAILED(hr), hr);
    
	// Get Features
	CComPtr<PartFeatures> pFeatures;
	hr = pPartDef->get_Features(&pFeatures);
	OnErrorReturn(FAILED(hr), hr);
	
	// Set a reference to the ExtrudeFeatures collection object.
	CComPtr<ExtrudeFeatures> pExtrudeFeatures;
	hr = pFeatures->get_ExtrudeFeatures(&pExtrudeFeatures);
	OnErrorReturn(FAILED(hr), hr);
	
	// Extrude the circle to create a cylinder.
    CComPtr<ExtrudeFeature> pExtrude; 
    hr = pExtrudeFeatures->AddByDistanceExtent(pProfile, CComVariant(5), kPositiveExtentDirection, 
											   kJoinOperation, CComVariant(), &pExtrude);
	OnErrorReturn(FAILED(hr), hr);
	
    pSketch->Visible = false;
    
	// Set a reference to the ThreadFeatures collection object.
	CComPtr<ThreadFeatures> pThreadFeatures;
	hr = pFeatures->get_ThreadFeatures(&pThreadFeatures);
	OnErrorReturn(FAILED(hr), hr);
	
	// Define all of the thread information.
    CComPtr<StandardThreadInfo> pStdThreadInfo;
    hr = pThreadFeatures->CreateStandardThreadInfo(
                        false, VARIANT_TRUE, CComBSTR("ANSI Unified Screw Threads"), 
						CComBSTR("1 5/8-6 UN"), CComBSTR("2A"), 
						&pStdThreadInfo);
	OnErrorReturn(FAILED(hr), hr);
    
	// Set a reference to the (side) Faces object.
    CComPtr<Faces> pSideFaces;
    hr = pExtrude->get_SideFaces(&pSideFaces);
	OnErrorReturn(FAILED(hr), hr);

    // Get the face the thread will be applied to.
	CComPtr<Face> pFace;
    hr = pSideFaces->get_Item(1, &pFace);
	OnErrorReturn(FAILED(hr), hr);

	// Set a reference to the (end) Faces object.
    CComPtr<Faces> pEndFaces;
    hr = pExtrude->get_EndFaces(&pEndFaces);
	OnErrorReturn(FAILED(hr), hr);

	// Get an end face.
	CComPtr<Face> pEndFace;
    hr = pEndFaces->get_Item(1, &pEndFace);
	OnErrorReturn(FAILED(hr), hr);

	// Set a reference to the Edges object.
    CComPtr<Edges> pEdges;
    hr = pEndFace->get_Edges(&pEdges);
	OnErrorReturn(FAILED(hr), hr);

    // Get the edge the thread extent will be measured from.
	CComPtr<Edge> pEdge;
    hr = pEdges->get_Item(1, &pEdge);
	OnErrorReturn(FAILED(hr), hr);

	// convert std thread info to generic
	CComQIPtr<ThreadInfo> pThreadInfo(pStdThreadInfo);

	// Create the thread feature.
    CComPtr<ThreadFeature> pThreadFeature;
    hr = pThreadFeatures->Add(pFace, pEdge, pThreadInfo, false, false,
							  CComVariant("2 cm"), CComVariant(0), &pThreadFeature);
	OnErrorReturn(FAILED(hr), hr);

	m_bThreadFeatureCreated = true;

	return S_OK;
}

HRESULT CRxThreadFeature::EditThreadFeature()
{
	AFX_MANAGE_STATE (AfxGetAppModuleState());
	// Set a reference to the active document. 
	CComPtr<Document> pDocument;
	HRESULT hr = m_pApplication->get_ActiveDocument(&pDocument);
	OnErrorReturn(FAILED(hr), hr);
	
	if (!m_bThreadFeatureCreated || !pDocument)
	{
		AfxMessageBox(_T("ThreadFeature not found."));
		return E_FAIL;
	}
             
    // convert generic document to partdocument
	CComQIPtr<PartDocument> pPartDocument(pDocument);
	
	// Set a reference to the component definition.
	CComPtr<PartComponentDefinition> pPartDef;
	hr = pPartDocument->get_ComponentDefinition(&pPartDef); 
	OnErrorReturn(FAILED(hr), hr);

	// Get Features
	CComPtr<PartFeatures> pFeatures;
	hr = pPartDef->get_Features(&pFeatures);
	OnErrorReturn(FAILED(hr), hr);
	
	// Set a reference to the ThreadFeatures collection object.
	CComPtr<ThreadFeatures> pThreadFeatures;
	hr = pFeatures->get_ThreadFeatures(&pThreadFeatures);
	OnErrorReturn(FAILED(hr), hr);

	// Get the thread feature.
    CComPtr<ThreadFeature> pThreadFeature;
    hr = pThreadFeatures->get_Item(CComVariant(1), &pThreadFeature);
	OnErrorReturn(FAILED(hr), hr);

	// Get the thread info object
	CComPtr<ThreadInfo> pOldThreadInfo;
    hr = pThreadFeature->get_ThreadInfo(&pOldThreadInfo);
	OnErrorReturn(FAILED(hr), hr);
	
	// convert generic info to std thread info 
	CComQIPtr<StandardThreadInfo> pOldStdThreadInfo(pOldThreadInfo);

	// Replace the thread info object entirely.
	// Some of the old Info's values could be reused.
	// 
	CComPtr<StandardThreadInfo> pNewStdThreadInfo;
    hr = pThreadFeatures->CreateStandardThreadInfo(
                        false, VARIANT_TRUE, CComBSTR("ANSI Unified Screw Threads"), 
						CComBSTR("1 5/8-6 UN"), CComBSTR("2A"),
						&pNewStdThreadInfo);
	OnErrorReturn(FAILED(hr), hr);

	// convert the new std thread info to generic
	CComQIPtr<ThreadInfo> pNewThreadInfo(pNewStdThreadInfo);

	// Push the new thread info into the feature.
	// The part will be updated.
	//
	hr = pThreadFeature->put_ThreadInfo(pNewThreadInfo);
	OnErrorReturn(FAILED(hr), hr);

	
	// If not too many values are being changed, the entire Thread Info object
	// need not be replaced. Instead, just access the relevant property on the 
	// Info object and change that. The Thread Info object is a "live tear-off",
	// so changing a property on the Info object has the affect of editing the
	// feature.

	// For instance, if the right-handed thread was to be made left-handed....
	//
	// Get the thread info object
	CComPtr<ThreadInfo> pLiveThreadInfo;
    hr = pThreadFeature->get_ThreadInfo(&pLiveThreadInfo);
	OnErrorReturn(FAILED(hr), hr);

	// Make the thread left-handed. The part is updated.
	hr = pLiveThreadInfo->put_RightHanded(false);
	OnErrorReturn(FAILED(hr), hr);

	// Also, make the thread a full length one
	hr = pThreadFeature->put_FullDepth(VARIANT_TRUE);
	OnErrorReturn(FAILED(hr), hr);
	
	return S_OK;
}

void CRxThreadFeature::CreateCommands()
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
	vtAddInId	      = _T("{D6C5BC20-7F20-401E-B317-60CB8380E254}");
	// command type
	eCmdType = kQueryOnlyCmdType;
	// button display type
	eCmdDisplayType = kAlwaysDisplayText;


	// Add the Create Thread Feature command
	InternalNameBSTR  =	_T("ThreadFeatureAddIn.CreateCmd");
	displayNameBSTR	  =	_T("CreateThreadFeature");
	DesTextBSTR		  =	_T("Execute Create Thread Feature Command");
	TooltipTextBSTR	  =	_T("Create Thread Feature");
	

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

	// Add the Edit Thread Feature command
	InternalNameBSTR  =	_T("ThreadFeatureAddIn.EditCmd");
	displayNameBSTR	  =	_T("EditThreadFeature");
	DesTextBSTR		  =	_T("Execute Edit Thread Feature Command");
	TooltipTextBSTR	  =	_T("Edit Thread Feature");
	

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

CButtonDefEvents::CButtonDefEvents(CRxThreadFeature* pAddIn, UINT nID) : m_pAddIn(pAddIn), m_nID(nID)
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
