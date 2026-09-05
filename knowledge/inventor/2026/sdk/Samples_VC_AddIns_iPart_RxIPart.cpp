/*
  DESCRIPTION

  This file contains the implementation of the class that offers the first contact with
  Autodesk Inventor (R).

*/

#include "stdafx.h"

#include "rxIPart.h"
#include "IPart.h"
#include "AfxCtl.h"

// The addin wizard adds command id definitions here.
#define CMD_CreateStdiPartmembers			0
#define CMD_CreateCstiPartmembers           1

/*--------------------- IUnknown-interface related implementation  --------------------------------*/

/*
 * All of the standard IUnknown interfaces are taken care of in the CUnknown
 * class. The implementation in the CUnknown class relies on this override that
 * should end up looking like a non-delegating QueryInterface, except for the fact that QI
 * for the IUnknown is also taken care of by CUnknown (control will never reach here if
 * QI-ed for IUnknown).
 */

HRESULT CRxIPart::InternalQueryInterface (REFIID riid, void **ppv)
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

CRxIPart::CRxIPart () : CUnknown (NULL)
{ 
  m_pSite = NULL;

  m_pButtonEvents1 = new CButtonDefEvents(this, CMD_CreateStdiPartmembers);
  m_pButtonEvents2 = new CButtonDefEvents(this, CMD_CreateCstiPartmembers);
	
  m_btnDefCookie1 = 0;
  m_btnDefCookie2 = 0;

  ::IncrementObjectCount();
}

CRxIPart::~CRxIPart()
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

HRESULT CRxIPart::Activate (IRxApplicationAddInSite *pAddInSite, BooleanType bFirstTime)
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

  CreateCommands();


wrapup:
  if (pAppUnk)
    pAppUnk->Release();

  return Result;
}
    
HRESULT CRxIPart::Deactivate ()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());
	HRESULT Result=NOERROR;

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

	m_pApplication->Release();
	m_pApplication = NULL;

	m_pSite->Release();
	m_pSite = NULL;

	return Result;
}


HRESULT CRxIPart::ExecuteCommand (long CommandID)
{
  HRESULT Result=NOERROR;

  CComPtr<AssemblyDocument> pAssyDoc;

  switch (CommandID)
  {
    case CMD_CreateStdiPartmembers: 
	  Result = CreateAssyDoc(pAssyDoc);
	  OnErrorReturn(FAILED(Result), Result);

      Result = AddStdiPartMembers(pAssyDoc);
	  OnErrorReturn(FAILED(Result), Result);
      break;

    case CMD_CreateCstiPartmembers: 
      Result = CreateAssyDoc(pAssyDoc);
	  OnErrorReturn(FAILED(Result), Result);

      Result = AddCstiPartMembers(pAssyDoc);
	  OnErrorReturn(FAILED(Result), Result);
      break;

    default:
      Result = E_NOTIMPL;
  }

  return Result;
}

HRESULT CRxIPart::get_Automation (IUnknown **ppUnk)
{
  HRESULT Result=NOERROR;

  if (!ppUnk)
    return E_INVALIDARG;
  *ppUnk = NULL;
  
  Result = E_NOINTERFACE;

  return Result;
}

HRESULT CRxIPart::AddStdiPartMembers(CComPtr<AssemblyDocument> pAssyDoc)
{
	HRESULT hr = S_OK;

	// Get the Autodesk Inventor (R) path
	CString sPath;
	hr = GetPath(sPath);
	OnErrorReturn(FAILED(hr), hr);

	sPath += CString(_T("Data_Files\\StandardFactory.ipt"));

	// Add the iPart members to the assembly
	return AddiPartMems(pAssyDoc, sPath, false);
}

HRESULT CRxIPart::AddCstiPartMembers(CComPtr<AssemblyDocument> pAssyDoc)
{
	HRESULT hr = S_OK;

	// Get the Autodesk Inventor (R) path
	CString sPath;
	hr = GetPath(sPath);
	OnErrorReturn(FAILED(hr), hr);

	sPath += CString(_T("Data_Files\\CustomFactory.ipt"));

	// Add the iPart members to the assembly
	return AddiPartMems(pAssyDoc, sPath, true);
}

HRESULT CRxIPart::CreateAssyDoc(CComPtr<AssemblyDocument> &pAssyDoc)
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
	hr = pFileManager->GetTemplateFile(kAssemblyDocumentObject,
										 kDefaultSystemOfMeasure,
										 kDefault_DraftingStandard,
										 CComVariant(),
										 &templateFilename);
	OnErrorReturn(FAILED(hr), hr);

    // Create a new part document, using the default part template. 
	CComPtr<Document> pDoc;
	hr = pDocs->Add(kAssemblyDocumentObject, templateFilename, VARIANT_TRUE, &pDoc);
	OnErrorReturn(FAILED(hr), hr);

	pAssyDoc = CComQIPtr<AssemblyDocument>(pDoc);
	OnErrorReturn(!pAssyDoc, E_FAIL);

	return hr;
}

HRESULT CRxIPart::GetPath(CString &sRelPath)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());
	
	HRESULT hr = S_OK;

	HINSTANCE hInst = AfxGetInstanceHandle();
	OnErrorReturn(!hInst, E_FAIL);
	
	TCHAR szDllFileName[MAX_PATH];
	HRESULT Result = NOERROR;
	DWORD Status = GetModuleFileName (hInst, szDllFileName, MAX_PATH);

	CString path(szDllFileName);

	path.MakeLower();

	int index = path.Find(_T("vc++"));
	OnErrorReturn(index == -1, E_FAIL);

	// Trim the string to the left iFeature
	sRelPath = path.Left(index);

	return hr;
}

HRESULT CRxIPart::AddiPartMems(CComPtr<AssemblyDocument> pAssyDoc, CString sPath, bool bCstFac)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	HRESULT hr = S_OK;

    // Get Documents collection
	CComPtr<Documents> pDocs;
	hr = m_pApplication->get_Documents(&pDocs);
	OnErrorReturn(FAILED(hr), hr);

	// Open the factory document
	CComPtr<Document> pDoc;
	hr = pDocs->Open(CComBSTR(sPath), VARIANT_FALSE, &pDoc);
	OnErrorReturn(FAILED(hr), hr);

	CComQIPtr<PartDocument> pFacDoc(pDoc);
	OnErrorReturn(!pFacDoc, E_FAIL);

	// Get the PartComponentDefinition
	CComPtr<PartComponentDefinition> pPartCompDef;
	hr = pFacDoc->get_ComponentDefinition(&pPartCompDef);
	OnErrorReturn(FAILED(hr), hr);

	// Make sure that we have an iPart factory
	VARIANT_BOOL bFac = VARIANT_FALSE;
	hr = pPartCompDef->get_IsiPartFactory(&bFac);
	OnErrorReturn(FAILED(hr), hr);
	OnErrorReturn(bFac == VARIANT_FALSE, E_FAIL);

	CComPtr<iPartFactory> piPartFac;
	hr = pPartCompDef->get_iPartFactory(&piPartFac);
	OnErrorReturn(FAILED(hr), hr);

	// Get the number of rows in the factory
	CComPtr<iPartTableRows> piPartRows;
	hr = piPartFac->get_TableRows(&piPartRows);
	OnErrorReturn(FAILED(hr), hr);
	
	long iNumRows = 0;
	hr = piPartRows->get_Count(&iNumRows);
	OnErrorReturn(FAILED(hr), hr);

	// Get the assembly component definition
	CComPtr<AssemblyComponentDefinition> pAssyCompDef;
	hr = pAssyDoc->get_ComponentDefinition(&pAssyCompDef);
	OnErrorReturn(FAILED(hr), hr);

	// Get the ComponentOccurrences collection for the assembly document
	CComPtr<ComponentOccurrences> pOccs;
	hr = pAssyCompDef->get_Occurrences(&pOccs);
	OnErrorReturn(FAILED(hr), hr);

	// Set reference to transient geometry object
	CComPtr<TransientGeometry> pTrGeom;
	hr = m_pApplication->get_TransientGeometry(&pTrGeom); 
	OnErrorReturn(FAILED(hr), hr);

	// Create an identity matrix
	CComPtr<Matrix> pPos;
	hr = pTrGeom->CreateMatrix(&pPos);
	OnErrorReturn(FAILED(hr), hr);

	// Get the path for Custom factory
	CString sRelPath;
	if ( bCstFac == true )
	{
		hr = GetPath(sRelPath);
		OnErrorReturn(FAILED(hr), hr);
	}
	
	// Iterate over all the rows in the factory and create a member for each row
	double  dTrans = 0.0;
	for ( int iRow = 1; iRow <= 3; ++iRow, dTrans += 10 )
	{
		// Create a vector
		CComPtr<Vector> pVec;
		hr = pTrGeom->CreateVector(dTrans, dTrans, 0.0, &pVec);
		OnErrorReturn(FAILED(hr), hr);

		// Set the translation in the matrix
		hr = pPos->SetTranslation(pVec, VARIANT_FALSE);
		OnErrorReturn(FAILED(hr), hr);

		// Add the iPart member to the assembly
		CComPtr<ComponentOccurrence> pOcc;
		if ( bCstFac == false ) // Standard iPart factory
		{
			pOccs->AddiPartMember(CComBSTR(sPath), pPos, CComVariant(iRow), &pOcc);
			// Ignore the error since it could be due to a failed compute
		}
		else // Custom factory
		{
			// Each custom factory member needs a unique file name. Assign one based on the 
			// row index
			CString sRow;
			sRow.Format(_T("%d"), iRow);
			
			CString sFilename = sRelPath + CString(_T("Data_Files\\CustomPart")) + sRow + CString(_T(".ipt"));
			
			pOccs->AddCustomiPartMember(CComBSTR(sPath), pPos, CComBSTR(sFilename), CComVariant(iRow), CComVariant(), &pOcc);
			// Ignore the result since it could be an error due to a failed compute
		}
	}

	return hr;
}

void CRxIPart::CreateCommands()
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
	vtAddInId	      = _T("{8E260182-B94B-40DE-8661-DCA8E70600E}");
	// command type
	eCmdType = kQueryOnlyCmdType;
	// button display type
	eCmdDisplayType = kAlwaysDisplayText;


	// Add the Create Standard iPart Members command
	InternalNameBSTR  =	_T("iPartAddIn.StdiPartMembersCmd");
	displayNameBSTR	  =	_T("CreateStdiPartMembers");
	DesTextBSTR		  =	_T("Execute Create Standard iPart Members Command");
	TooltipTextBSTR	  =	_T("Create Standard iPart Members");
	
	// Get the command by its internal name. If it does not exist, create a new one.
	CComPtr<ControlDefinition> pConDef1 = NULL;
	hr = pCtrlDefs->get_Item(CComVariant(InternalNameBSTR), &pConDef1);

	if (FAILED(hr))
		hr = pCtrlDefs->AddButtonDefinition(displayNameBSTR, InternalNameBSTR,eCmdType,vtAddInId,DesTextBSTR,TooltipTextBSTR,vtEmpty,vtEmpty,eCmdDisplayType,&m_pBtnDef1);
	else
		hr = pConDef1->QueryInterface(__uuidof(m_pBtnDef1), reinterpret_cast<void**>(&m_pBtnDef1));

	ATLASSERT(SUCCEEDED(hr));
	ATLASSERT(m_pBtnDef1 != NULL);

	if(m_pBtnDef1)
	{
		m_pBtnDef1->put_Enabled(VARIANT_TRUE);

		BOOL bBrwsrAdvised = AfxConnectionAdvise(m_pBtnDef1, DIID_ButtonDefinitionSink,
                                m_pButtonEvents1->GetInterface(&IID_IUnknown),
                                TRUE, &m_btnDefCookie1);

		ATLASSERT(bBrwsrAdvised == TRUE);

		hr = m_pBtnDef1->AutoAddToGUI();
		ATLASSERT(SUCCEEDED(hr));
	}

	// Add the Create Custom iPart Members command
	InternalNameBSTR  =	_T("iPartAddIn.CustomiPartMembersCmd");
	displayNameBSTR	  =	_T("CreateCustomiPartMembers");
	DesTextBSTR		  =	_T("Execute Create Custom iPart Members Command");
	TooltipTextBSTR	  =	_T("Create Custom iPart Members");
	
	// Get the command by its internal name. If it does not exist, create a new one.
	CComPtr<ControlDefinition> pConDef2 = NULL;
	hr = pCtrlDefs->get_Item(CComVariant(InternalNameBSTR), &pConDef2);

	if (FAILED(hr))
		hr = pCtrlDefs->AddButtonDefinition(displayNameBSTR, InternalNameBSTR,eCmdType,vtAddInId,DesTextBSTR,TooltipTextBSTR,vtEmpty,vtEmpty,eCmdDisplayType,&m_pBtnDef2);
	else
		hr = pConDef2->QueryInterface(__uuidof(m_pBtnDef2), reinterpret_cast<void**>(&m_pBtnDef2));

	ATLASSERT(SUCCEEDED(hr));
	ATLASSERT(m_pBtnDef2 != NULL);

	if(m_pBtnDef2)
	{
		m_pBtnDef2->put_Enabled(VARIANT_TRUE);

		BOOL bBrwsrAdvised = AfxConnectionAdvise(m_pBtnDef2, DIID_ButtonDefinitionSink,
                                m_pButtonEvents2->GetInterface(&IID_IUnknown),
                                TRUE, &m_btnDefCookie2);

		ATLASSERT(bBrwsrAdvised == TRUE);

		hr = m_pBtnDef2->AutoAddToGUI();
		ATLASSERT(SUCCEEDED(hr));
	}
}


/////////////////////////////////////////////////////////////////////////////
// CButtonDefEvents

IMPLEMENT_DYNCREATE(CButtonDefEvents, CCmdTarget)

CButtonDefEvents::CButtonDefEvents(CRxIPart* pAddIn, UINT nID) : m_pAddIn(pAddIn), m_nID(nID)
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
