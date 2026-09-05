//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted,
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting documentation. 
// <YOUR COMPANY NAME> PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// <YOUR COMPANY NAME> SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE. <YOUR COMPANY NAME>, INC.
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE. 
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable
// 

//-----------------------------------------------------------------------------
//----- iMateSampleAddinAddInServer.cpp : Implementation of CiMateSampleAddinAddInServer
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include <atlbase.h>
#include <eventsdispids.h>

#include "iMateSampleAddin.h"
#include "iMateSampleAddinAddInServer.h"

#define OnErrorReturn(badsts, errocode) \
  if (badsts) return errocode;

#define m_PlaceUsingiMatesCmd					1
#define m_AddConstraintsFromiMatesCmd			2
#define m_CreateConstraintFromiMateAndEntityCmd 3

/*---------------------- Constructor(s), initializers and destructor ---------------------------------*/

CiMateSampleAddinAddInServer::CiMateSampleAddinAddInServer ()
{ 
	m_pAddInSite = NULL;

	m_pButtonEvents1 = new CButtonDefEvents(this, m_PlaceUsingiMatesCmd);
	m_pButtonEvents2 = new CButtonDefEvents(this, m_AddConstraintsFromiMatesCmd);
	m_pButtonEvents3 = new CButtonDefEvents(this, m_CreateConstraintFromiMateAndEntityCmd);

	m_btnDefCookie1 = 0;
	m_btnDefCookie2 = 0;
	m_btnDefCookie3 = 0;
}

CiMateSampleAddinAddInServer::~CiMateSampleAddinAddInServer()
{
	if (m_pAddInSite)
		m_pAddInSite = NULL;

	if(m_pButtonEvents1)
		delete m_pButtonEvents1;

	if(m_pButtonEvents2)
		delete m_pButtonEvents2;

	if(m_pButtonEvents3)
		delete m_pButtonEvents3;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CiMateSampleAddinAddInServer::Activate (IDispatch *pDisp, VARIANT_BOOL FirstTime)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;

	if ( pDisp == NULL )
		return E_INVALIDARG ;

	HRESULT hr =pDisp->QueryInterface (__uuidof (m_pAddInSite), reinterpret_cast<void**>(&m_pAddInSite)) ;
	ATLASSERT( SUCCEEDED( hr ) ) ;
	if ( FAILED( hr ) )
		return hr ;
	
	//----- Get the application object.
	hr =m_pAddInSite->get_Application (&m_pApplication) ;
	ATLASSERT( SUCCEEDED( hr ) ) ;
	if ( FAILED( hr ) )
		return hr ;

	// Create buttons on toolbar
	CreateCommands();

	return S_OK ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CiMateSampleAddinAddInServer::Deactivate ()
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

	if(m_btnDefCookie2)
	{
		BOOL bUnadvised = AfxConnectionUnadvise(m_pBtnDef2, DIID_ButtonDefinitionSink,
											  m_pButtonEvents2->GetInterface(&IID_IUnknown),
											  TRUE, m_btnDefCookie2);
		m_btnDefCookie2 = 0;
	}

	if(m_btnDefCookie3)
	{
		BOOL bUnadvised = AfxConnectionUnadvise(m_pBtnDef3, DIID_ButtonDefinitionSink,
											  m_pButtonEvents3->GetInterface(&IID_IUnknown),
											  TRUE, m_btnDefCookie3);
		m_btnDefCookie3 = 0;
	}

	m_pBtnDef1 = NULL;
	m_pBtnDef2 = NULL;
	m_pBtnDef3 = NULL;

	m_pApplication = NULL;
	m_pAddInSite = NULL;

	return Result;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CiMateSampleAddinAddInServer::ExecuteCommand (long CommandID)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT Result = E_NOTIMPL;

	return Result;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CiMateSampleAddinAddInServer::get_Automation (IDispatch **ppResult)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;

	if ( ppResult == NULL )
		return E_POINTER ;
	*ppResult =NULL ;

	//return S_OK ; //----- If you do anything in there
	return E_NOTIMPL ;
}


//-----------------------------------------------------------------------------
HRESULT CiMateSampleAddinAddInServer::PlaceUsingiMatesCmd() 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());
	OnErrorReturn(!m_pApplication, E_FAIL);

	CComPtr<Documents> pDocuments;
	HRESULT hr = m_pApplication->get_Documents(&pDocuments);
	OnErrorReturn(FAILED(hr), hr);
	
	CComBSTR strTemplateFilename; 
	// Get assembly document template
	CComPtr<FileManager> pFileManager;
	hr = m_pApplication->get_FileManager(&pFileManager);
	OnErrorReturn(FAILED(hr), hr);

	hr = pFileManager->GetTemplateFile(kAssemblyDocumentObject, kDefaultSystemOfMeasure,
													kDefault_DraftingStandard, CComVariant(), &strTemplateFilename);
	OnErrorReturn(FAILED(hr), hr);

	// create a new assembly document from a standard template
	CComPtr<Document> pDocument;
	hr = pDocuments->Add(kAssemblyDocumentObject, strTemplateFilename, VARIANT_TRUE, &pDocument);
	OnErrorReturn(FAILED(hr), hr);

	CComQIPtr<AssemblyDocument> pAsmDocument(pDocument);
	OnErrorReturn(!pAsmDocument, E_FAIL);

	// Get the ComponentDefinition
	CComPtr<AssemblyComponentDefinition> pAsmCompDef;
	hr = pAsmDocument->get_ComponentDefinition(&pAsmCompDef);
	OnErrorReturn(FAILED(hr), hr);

	//Get the occurrences collection
	CComPtr<ComponentOccurrences> pOccs;
	hr = pAsmCompDef->get_Occurrences(&pOccs);
	OnErrorReturn(FAILED(hr), hr);

	CString strFilePath;
	hr = GetFilePath(strFilePath);
	OnErrorReturn(FAILED(hr), hr);

	// Add the remaining path to the string
	CString strFileName = strFilePath + CString(_T("\\nut.ipt"));

	CComBSTR FileName = strFileName;
	OnErrorReturn(FileName.Length() == 0, E_FAIL);
	CComPtr<TransientGeometry> pTransGeom;
	hr = m_pApplication->get_TransientGeometry(&pTransGeom);
	OnErrorReturn(FAILED(hr), hr);

	CComPtr<Matrix> pMatrix;
	hr = pTransGeom->CreateMatrix(&pMatrix);
	OnErrorReturn(FAILED(hr), hr);

	// now add an occurrence to the occurrences collection
	CComPtr<ComponentOccurrence> pOcc1;
	hr = pOccs->Add(FileName, pMatrix, &pOcc1);
	OnErrorReturn(FAILED(hr), hr);

	CComPtr<Vector> pVector; 
	hr = pTransGeom->CreateVector(5,5,5, & pVector);
	OnErrorReturn(FAILED(hr), hr);

	hr = pMatrix->SetTranslation(pVector, VARIANT_FALSE);
	OnErrorReturn(FAILED(hr), hr);

	strFileName.Empty();
	strFileName = strFilePath + CString(_T("\\bolt.ipt"));

	FileName.Empty();
	FileName = strFileName;
	CComVariant varOptions;
	CComPtr<ComponentOccurrencesEnumerator> pOccEnum;
	hr = pOccs->AddUsingiMates(FileName, VARIANT_FALSE, varOptions, &pOccEnum);

	return hr;
}


//-----------------------------------------------------------------------------
HRESULT CiMateSampleAddinAddInServer::AddConstraintsFromiMatesCmd () 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());
	OnErrorReturn(!m_pApplication, E_FAIL);

	CComPtr<Documents> pDocuments;
	HRESULT hr = m_pApplication->get_Documents(&pDocuments);
	OnErrorReturn(FAILED(hr), hr);
	
	CComBSTR strTemplateFilename; 
	// Get assembly document template
	CComPtr<FileManager> pFileManager;
	hr = m_pApplication->get_FileManager(&pFileManager);
	OnErrorReturn(FAILED(hr), hr);

	hr = pFileManager->GetTemplateFile(kAssemblyDocumentObject, kDefaultSystemOfMeasure,
													kDefault_DraftingStandard, CComVariant(), &strTemplateFilename);
	OnErrorReturn(FAILED(hr), hr);

	// create a new assembly document from a standard template
	CComPtr<Document> pDocument;
	hr = pDocuments->Add(kAssemblyDocumentObject, strTemplateFilename, VARIANT_TRUE, &pDocument);
	OnErrorReturn(FAILED(hr), hr);

	CComQIPtr<AssemblyDocument> pAsmDocument(pDocument);
	OnErrorReturn(!pAsmDocument, E_FAIL);

	// Get the ComponentDefinition
	CComPtr<AssemblyComponentDefinition> pAsmCompDef;
	hr = pAsmDocument->get_ComponentDefinition(&pAsmCompDef);
	OnErrorReturn(FAILED(hr), hr);

	//Get the occurrences collection
	CComPtr<ComponentOccurrences> pOccs;
	hr = pAsmCompDef->get_Occurrences(&pOccs);
	OnErrorReturn(FAILED(hr), hr);

	CString strFilePath;
	hr = GetFilePath(strFilePath);
	OnErrorReturn(FAILED(hr), hr);

	// Add the remaining path to the string
	CString strFileName = strFilePath + CString(_T("\\nut.ipt"));


	CComBSTR FileName = strFileName;
	OnErrorReturn(FileName.Length() == 0, E_FAIL);
	CComPtr<TransientGeometry> pTransGeom;
	hr = m_pApplication->get_TransientGeometry(&pTransGeom);
	OnErrorReturn(FAILED(hr), hr);

	CComPtr<Matrix> pMatrix;
	hr = pTransGeom->CreateMatrix(&pMatrix);
	OnErrorReturn(FAILED(hr), hr);

	// now add an occurrence to the occurrences collection
	CComPtr<ComponentOccurrence> pOcc1;
	hr = pOccs->Add(FileName, pMatrix, &pOcc1);
	OnErrorReturn(FAILED(hr), hr);

	CComPtr<Vector> pVector; 
	hr = pTransGeom->CreateVector(5,5,5, & pVector);
	OnErrorReturn(FAILED(hr), hr);

	hr = pMatrix->SetTranslation(pVector, VARIANT_FALSE);
	OnErrorReturn(FAILED(hr), hr);

	strFileName.Empty();
	strFileName = strFilePath + CString(_T("\\bolt.ipt"));

	FileName.Empty();
	FileName = strFileName;
	CComPtr<ComponentOccurrence> pOcc2;
	hr = pOccs->Add(FileName, pMatrix, &pOcc2);
	OnErrorReturn(FAILED(hr), hr);

	CComPtr<iMateDefinitionsEnumerator> pOcc1Defs;
	hr = pOcc1->get_iMateDefinitions(& pOcc1Defs);
	OnErrorReturn(FAILED(hr), hr);

	CComPtr<iMateDefinitionsEnumerator> pOcc2Defs;
	hr = pOcc2->get_iMateDefinitions(& pOcc2Defs);
	OnErrorReturn(FAILED(hr), hr);

	long nCount1, nCount2;
	hr = pOcc1Defs->get_Count(&nCount1);
	OnErrorReturn(FAILED(hr), hr);

	hr = pOcc2Defs->get_Count(&nCount2);
	OnErrorReturn(FAILED(hr), hr);

	OnErrorReturn(nCount1 != nCount2, E_FAIL);

	CComPtr<iMateResults> piMateResults;
	// get the imateresults collection. 
	hr = pAsmCompDef->get_iMateResults(&piMateResults);
	OnErrorReturn(FAILED(hr), hr);

	// now add constraints using the imatedefintions on each occurrence 
	for ( long ii =1; ii< nCount1+1; ++ii)
	{
		CComPtr<iMateDefinition> pDef1Proxy;
		hr = pOcc1Defs->get_Item(ii, &pDef1Proxy);
		OnErrorReturn(FAILED(hr), hr);

		CComPtr<iMateDefinition> pDef2Proxy;
		hr = pOcc2Defs->get_Item(ii, &pDef2Proxy);
		OnErrorReturn(FAILED(hr), hr);

		CComPtr<iMateResult> piMateResult;
		hr = piMateResults->AddByTwoiMates(pDef1Proxy, pDef2Proxy, &piMateResult);
		OnErrorReturn(FAILED(hr), hr);
	}

	return hr;
}


//-----------------------------------------------------------------------------
HRESULT CiMateSampleAddinAddInServer::CreateConstraintFromiMateAndEntityCmd () 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());
	OnErrorReturn(!m_pApplication, E_FAIL);

	CComPtr<Documents> pDocuments;
	HRESULT hr = m_pApplication->get_Documents(&pDocuments);
	OnErrorReturn(FAILED(hr), hr);
	
	CComBSTR strTemplateFilename; 
	// Get assembly document template
	CComPtr<FileManager> pFileManager;
	hr = m_pApplication->get_FileManager(&pFileManager);
	OnErrorReturn(FAILED(hr), hr);

	hr = pFileManager->GetTemplateFile(kAssemblyDocumentObject, kDefaultSystemOfMeasure,
													kDefault_DraftingStandard, CComVariant(), &strTemplateFilename);
	OnErrorReturn(FAILED(hr), hr);

	// create a new assembly document from a standard template
	CComPtr<Document> pDocument;
	hr = pDocuments->Add(kAssemblyDocumentObject, strTemplateFilename, VARIANT_TRUE, &pDocument);
	OnErrorReturn(FAILED(hr), hr);

	CComQIPtr<AssemblyDocument> pAsmDocument(pDocument);
	OnErrorReturn(!pAsmDocument, E_FAIL);

	// Get the ComponentDefinition
	CComPtr<AssemblyComponentDefinition> pAsmCompDef;
	hr = pAsmDocument->get_ComponentDefinition(&pAsmCompDef);
	OnErrorReturn(FAILED(hr), hr);

	//Get the occurrences collection
	CComPtr<ComponentOccurrences> pOccs;
	hr = pAsmCompDef->get_Occurrences(&pOccs);
	OnErrorReturn(FAILED(hr), hr);

	CString strFilePath;
	hr = GetFilePath(strFilePath);
	OnErrorReturn(FAILED(hr), hr);

	// Add the remaining path to the string
	CString strFileName = strFilePath + CString(_T("\\nut.ipt"));

	CComBSTR FileName = strFileName;
	OnErrorReturn(FileName.Length() == 0, E_FAIL);
	CComPtr<TransientGeometry> pTransGeom;
	hr = m_pApplication->get_TransientGeometry(&pTransGeom);
	OnErrorReturn(FAILED(hr), hr);

	CComPtr<Matrix> pMatrix;
	hr = pTransGeom->CreateMatrix(&pMatrix);
	OnErrorReturn(FAILED(hr), hr);

	// now add an occurrence to the occurrences collection
	CComPtr<ComponentOccurrence> pOcc1;
	hr = pOccs->Add(FileName, pMatrix, &pOcc1);
	OnErrorReturn(FAILED(hr), hr);

	CComPtr<Vector> pVector; 
	hr = pTransGeom->CreateVector(5,5,5, & pVector);
	OnErrorReturn(FAILED(hr), hr);

	hr = pMatrix->SetTranslation(pVector, VARIANT_FALSE);
	OnErrorReturn(FAILED(hr), hr);

	strFileName.Empty();
	strFileName = strFilePath + CString(_T("\\bolt.ipt"));

	FileName.Empty();
	FileName = strFileName;
	CComPtr<ComponentOccurrence> pOcc2;
	hr = pOccs->Add(FileName, pMatrix, &pOcc2);
	OnErrorReturn(FAILED(hr), hr);

	// get a circular edge on this occurrence

	CComPtr<SurfaceBodies> pSurfaceBodies;
	hr = pOcc2->get_SurfaceBodies(&pSurfaceBodies);
	OnErrorReturn(FAILED(hr), hr);

	CComPtr<SurfaceBody> pBody;
	hr = pSurfaceBodies->get_Item(1, &pBody);
	OnErrorReturn(FAILED(hr), hr);

	CComPtr<Edges> pEdges;
	hr = pBody->get_Edges(&pEdges);
	OnErrorReturn(FAILED(hr), hr);

	CComPtr<Edge> pEdge;
	hr = pEdges->get_Item(1, &pEdge);
	OnErrorReturn(FAILED(hr), hr);

	CComQIPtr<IDispatch> pEdgeDisp(pEdge);
	OnErrorReturn(!pEdgeDisp, E_NOINTERFACE);

	CurveTypeEnum kCurveType;
	pEdge->get_CurveType(&kCurveType);
	OnErrorReturn(kCurveType != kCircleCurve, E_FAIL);

	
	CComPtr<iMateResults> piMateResults;
	// get the imateresults collection. 
	hr = pAsmCompDef->get_iMateResults(&piMateResults);
	OnErrorReturn(FAILED(hr), hr);

	CComPtr<iMateDefinitionsEnumerator> pOcc1Defs;
	hr = pOcc1->get_iMateDefinitions(& pOcc1Defs);
	OnErrorReturn(FAILED(hr), hr);

	CComPtr<iMateDefinition> pDef1Proxy;
	hr = pOcc1Defs->get_Item(1, &pDef1Proxy);
	OnErrorReturn(FAILED(hr), hr);

	ObjectTypeEnum iMateType;
	hr = pDef1Proxy->get_Type(&iMateType);
	OnErrorReturn(iMateType != kInsertiMateDefinitionProxyObject, E_FAIL);

	CComPtr<iMateResult> piMateResult;
	CComVariant varBiasPoint;
	CComVariant varAngleDirection;

	// add a constraint between the imate and the entity.
	return piMateResults->AddByiMateAndEntity(pDef1Proxy, pEdgeDisp, varBiasPoint ,varBiasPoint, &piMateResult);
}

HRESULT CiMateSampleAddinAddInServer::GetFilePath(CString& FilePath)
{
	FilePath.Empty();

	HINSTANCE hInst = AfxGetInstanceHandle();
	OnErrorReturn(!hInst, E_FAIL);
	
	TCHAR szDllFileName[MAX_PATH];
	DWORD Status = GetModuleFileName (hInst, szDllFileName, MAX_PATH);
	OnErrorReturn(!Status, E_FAIL);
	
	CString path(szDllFileName);
	
	path.MakeLower();
	
	int index = path.Find(_T("vc++"));
	OnErrorReturn(index == -1, E_FAIL);

	// Trim the string to the left iFeature
	FilePath = path.Left(index);
	FilePath = FilePath + _T("Data_Files");

	return S_OK;
}

void CiMateSampleAddinAddInServer::CreateCommands()
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
	vtAddInId	      = _T("{D298E4CE-3D9F-4306-A667-A9CE578B9ED4}");
	// command type
	eCmdType = kQueryOnlyCmdType;
	// button display type
	eCmdDisplayType = kAlwaysDisplayText;

	// Place Using iMates
	InternalNameBSTR  =	L"iMateSampleAddin.PlaceCmd";
	displayNameBSTR	  =	L"PlaceUsingiMates";
	DesTextBSTR		  =	L"Place Using iMates";
	TooltipTextBSTR	  =	L"Place Using iMates";
	
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

	// Add Constaints from iMates
	InternalNameBSTR  =	L"iMateSampleAddin.AddConstraintsCmd";
	displayNameBSTR	  =	L"AddConstraintsFromiMates";
	DesTextBSTR		  =	L"Add Constraints from iMates";
	TooltipTextBSTR	  =	L"Add Constraints from iMates";
	

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

	// Create Constraint From iMate And Entity
	InternalNameBSTR  =	L"iMateSampleAddin.CreateConstraintCmd";
	displayNameBSTR	  =	L"CreateConstraintFromiMates";
	DesTextBSTR		  =	L"Create Constraint from iMates";
	TooltipTextBSTR	  =	L"Create Constraint from iMates";
	

	hr = pCtrlDefs->AddButtonDefinition(displayNameBSTR, InternalNameBSTR,eCmdType,vtAddInId,DesTextBSTR,TooltipTextBSTR,vtEmpty,vtEmpty,eCmdDisplayType,&m_pBtnDef3); 

	ATLASSERT(SUCCEEDED(hr));
	ATLASSERT(m_pBtnDef3 != NULL);

	m_pBtnDef3->put_Enabled(VARIANT_TRUE);

	if(m_pBtnDef3)
	{
		BOOL bBrwsrAdvised = AfxConnectionAdvise(m_pBtnDef3, DIID_ButtonDefinitionSink,
                                m_pButtonEvents3->GetInterface(&IID_IUnknown),
                                TRUE, &m_btnDefCookie3);

		ATLASSERT(bBrwsrAdvised == TRUE);
	}

	hr = m_pBtnDef3->AutoAddToGUI();
	ATLASSERT(SUCCEEDED(hr));
}

/////////////////////////////////////////////////////////////////////////////
// CButtonDefHandlerEvents

IMPLEMENT_DYNCREATE(CButtonDefEvents, CCmdTarget)

CButtonDefEvents::CButtonDefEvents(CiMateSampleAddinAddInServer* pAddIn, UINT nID) : m_pAddIn(pAddIn), m_nID(nID)
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
// CButtonDefHandlerEvents event handlers

HRESULT CButtonDefEvents::OnExecuteEvent(NameValueMap *context) 
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT Result = NOERROR;

	switch (m_nID)
	{
	case m_PlaceUsingiMatesCmd:
		Result = m_pAddIn->PlaceUsingiMatesCmd();
		break;

	case m_AddConstraintsFromiMatesCmd:
		Result = m_pAddIn->AddConstraintsFromiMatesCmd();
		break;

    case m_CreateConstraintFromiMateAndEntityCmd:
		Result = m_pAddIn->CreateConstraintFromiMateAndEntityCmd();
		break;

	default:
		Result = E_NOTIMPL;
	}

	return Result;
}
