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
//----- TextClientGraphAddInServer.cpp : Implementation of CTextClientGraphAddInServer
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "TextClientGraph.h"
#include "TextClientGraphAddInServer.h"

#define OnErrorReturn(badsts, errocode) \
  if (badsts) return errocode;

//-----------------------------------------------------------------------------

CTextClientGraphAddInServer::CTextClientGraphAddInServer () 
{ 
	m_pButtonEvents1 = NULL;
	m_pButtonEvents1 = new CButtonDefEvents(this, 0);
	m_pApplication =NULL ;
	m_pAddInSite =NULL ;

	m_btnDefCookie1 = 0;
}

CTextClientGraphAddInServer::~CTextClientGraphAddInServer () 
{ 
	if (m_pAddInSite)
		m_pAddInSite = NULL;

	if(m_pButtonEvents1)
		delete m_pButtonEvents1;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CTextClientGraphAddInServer::Activate (IDispatch *pDisp, VARIANT_BOOL FirstTime)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
	
	if ( pDisp == NULL )
		return E_INVALIDARG ;
	
	m_pAddInSite = CComQIPtr<ApplicationAddInSite>(pDisp) ;
		
	//----- Get the application object.
	HRESULT hr =m_pAddInSite->get_Application (&m_pApplication) ;
	ATLASSERT( SUCCEEDED( hr ) ) ;
	
	if(!m_pApplication)
		return E_FAIL;

	CComPtr<CommandManager> pCommandMgr;
	hr = m_pApplication->get_CommandManager(&pCommandMgr);

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
	vtAddInId	      = _T("{9F605F71-7683-43D7-946A-523DCD9255D3}");
	// command type
	eCmdType = kQueryOnlyCmdType;
	// button display type
	eCmdDisplayType = kAlwaysDisplayText;

	
	//----- Create button definition
	InternalNameBSTR = _T("TextClientGraphicsCmd_InternalName1");
	displayNameBSTR  = _T("TextClientGraphics");
	DesTextBSTR      = _T("DescriptiveText - 1");
	TooltipTextBSTR  = _T("Tooltip -1");


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

	if(FirstTime != VARIANT_FALSE)	
		InsertControlsInMenuBars();	

	return S_OK ;
}


void CTextClientGraphAddInServer::InsertControlInMenuBar(const CString intEnvName)
{
	ATLASSERT(m_pApplication);
	ATLASSERT(m_pAddInSite);

	CComPtr<CommandBarBase> pCmdBarDef;

	CComPtr<UserInterfaceManager> pUserInterfaceMgr;
	HRESULT hr = m_pApplication->get_UserInterfaceManager(&pUserInterfaceMgr);
	ATLASSERT(SUCCEEDED(hr));

	CComPtr<CommandBars> pCmdBars;
	hr = pUserInterfaceMgr->get_CommandBars(&pCmdBars);
	ATLASSERT(SUCCEEDED(hr));

	CComVariant vtAddInId(L"{9F605F71-7683-43D7-946A-523DCD9255D3}");
	CComBSTR InternalNameBSTR(L"TextClientGraphicsCmdBar_InternalName1");
	CComBSTR displayNameBSTR(L"TextClientGraphics");

	CComPtr<CommandBar> pCmdBar;
	hr = pCmdBars->get_Item(CComVariant(InternalNameBSTR),&pCmdBar);

	if (hr != S_OK || pCmdBar == NULL){
		hr = pCmdBars->Add(displayNameBSTR,InternalNameBSTR,kPopUpCommandBar,vtAddInId,&pCmdBar);
		ATLASSERT(SUCCEEDED(hr));

		CComPtr<CommandBarControls> pCmdBarControls; 
		hr = pCmdBar->get_Controls(&pCmdBarControls) ;
		ATLASSERT(SUCCEEDED(hr)); 

		CComPtr<CommandBarControl> pCmdBarCtrl; 
		hr = pCmdBarControls->AddButton(m_pBtnDef1, 0, &pCmdBarCtrl) ; 
		ATLASSERT(SUCCEEDED(hr));	
	}

	CComPtr<Environments> pEnvs;
	hr = pUserInterfaceMgr->get_Environments(&pEnvs);
	ATLASSERT(SUCCEEDED(hr));

	CComPtr<Environment> pEnv;
	CComVariant vt(intEnvName);
	hr = pEnvs->get_Item(vt, &pEnv);
	ATLASSERT(SUCCEEDED(hr));

	CComPtr<CommandBar> pDefMenuBar;
	hr = pEnv->get_DefaultMenuBar(&pDefMenuBar);
	ATLASSERT(SUCCEEDED(hr));

	CComPtr<CommandBarControls> pDefMenuBarControls; 
	hr = pDefMenuBar->get_Controls(&pDefMenuBarControls) ;
	ATLASSERT(SUCCEEDED(hr)); 

	long lBefore = 4;
	hr = pDefMenuBarControls->AddPopup(pCmdBar,lBefore);
	ATLASSERT(SUCCEEDED(hr));
}

void CTextClientGraphAddInServer::InsertControlsInMenuBars()
{
	ATLASSERT(m_pApplication);
	ATLASSERT(m_pAddInSite);

	
	InsertControlInMenuBar(CString(L"FWxMainFrameEnvironment"));
	InsertControlInMenuBar(CString(L"AMxAssemblyEnvironment"));
	InsertControlInMenuBar(CString(L"DLxDrawingEnvironment"));
	InsertControlInMenuBar(CString(L"DXxPresentationEnvironment"));
	InsertControlInMenuBar(CString(L"PMxPartEnvironment"));

}


//-----------------------------------------------------------------------------
STDMETHODIMP CTextClientGraphAddInServer::Deactivate ()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;

	// disconnect event sinks
	if(m_btnDefCookie1)
	{
		BOOL bUnadvised = AfxConnectionUnadvise(m_pBtnDef1, DIID_ButtonDefinitionSink,
											  m_pButtonEvents1->GetInterface(&IID_IUnknown),
											  TRUE, m_btnDefCookie1);
		m_btnDefCookie1 = 0;
	}

	m_pBtnDef1 = NULL;
	
	m_pAddInSite = NULL;
	m_pApplication = NULL;
	
	return S_OK ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CTextClientGraphAddInServer::ExecuteCommand (long CommandID)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
	
	return (AddClientTextCmd());
}

//-----------------------------------------------------------------------------
STDMETHODIMP CTextClientGraphAddInServer::get_Automation (IDispatch **ppResult)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
	
	if ( ppResult == NULL )
		return E_POINTER ;
	*ppResult =NULL ;
	
	//return S_OK ; //----- If you do anything in there
	return E_NOTIMPL ;
}


//-----------------------------------------------------------------------------
HRESULT CTextClientGraphAddInServer::AddClientTextCmd () {
	
	HRESULT hr=NOERROR;
	CComPtr<Document> pDoc;	
	
	// Get the active document and its type
	
	hr = m_pApplication->get_ActiveDocument(&pDoc);
	OnErrorReturn(FAILED(hr), hr);

	if(pDoc == NULL) {
		AfxMessageBox(_T("Please open an assembly file."));
		return (S_FALSE);
	}
	
    DocumentTypeEnum docType;
    hr = pDoc->get_DocumentType(&docType);
	OnErrorReturn(FAILED(hr), hr);
	
    if(docType != kAssemblyDocumentObject) {
		AfxMessageBox(_T("Please open an assembly file."));
		return (S_FALSE);
	}
	
	CComQIPtr<AssemblyDocument> pAssDoc(pDoc);
	OnErrorReturn(!pAssDoc, E_FAIL);

	// Get Component Definition	
	CComPtr<AssemblyComponentDefinition> pAssDef;
	hr = pAssDoc->get_ComponentDefinition(&pAssDef);
    OnErrorReturn(!pAssDef, E_FAIL);

	// Get Client Graphics Collection	
	CComPtr<ClientGraphicsCollection> pClientGraphCol;
	hr = pAssDef->get_ClientGraphicsCollection(&pClientGraphCol);
	OnErrorReturn(FAILED(hr) || !pClientGraphCol, E_FAIL);
	
	// Check for & delete TextGraphicsSample if it already exists
	
	CComBSTR sName(L"TextGraphicsSample");
	CComVariant vtName = sName;

	CComPtr<ClientGraphics> pClientGraph;
	hr = pClientGraphCol->get_Item(vtName, &pClientGraph);
		
	if(pClientGraph != NULL)
	{
		hr = pClientGraph->Delete();
		OnErrorReturn(FAILED(hr), hr);
		hr = m_pApplication->ActiveView->Update();
		OnErrorReturn(FAILED(hr), hr);
		return S_OK;
	} 
	
	// Create new Client Graphics and add it to collection
	
	hr = pClientGraphCol->Add(sName, &pClientGraph);
	OnErrorReturn(FAILED(hr) || !pClientGraph, E_FAIL);
		
	// Create new Graphics Node
	
	CComPtr<GraphicsNode> pDispGraphNode;
	
	
	// Add new node to Client Graphics with ID of one more than collection total
	
	long lClientGraphCount;
	
	hr = pClientGraph->get_Count(&lClientGraphCount);
	OnErrorReturn(FAILED(hr), hr);
		
	hr = pClientGraph->AddNode(lClientGraphCount + 1, &pDispGraphNode);
	OnErrorReturn(FAILED(hr) || !pDispGraphNode, E_FAIL);
	
	// Create TextGraphics object
	
	CComPtr<TextGraphics> pTextGraph;
	
	hr = pDispGraphNode->AddTextGraphics(&pTextGraph);
	OnErrorReturn(FAILED(hr) || !pTextGraph, E_FAIL);
		
	// Create TransientGeometry for text Anchor point
	
	CComPtr<TransientGeometry> pTransGeo;
	hr = m_pApplication->get_TransientGeometry(&pTransGeo);
	OnErrorReturn(FAILED(hr) || !pTransGeo, E_FAIL);
	
	// Create anchor Point of 0,0,0
	
	CComPtr<Point> pStartPoint;
	hr = pTransGeo->CreatePoint(0.0, 0.0, 0.0, &pStartPoint);
	OnErrorReturn(FAILED(hr) || !pStartPoint, E_FAIL);
	
	// Add attributes such as anchor point, font, size, content and color.
	
	hr = pTextGraph->put_Anchor(pStartPoint);
	OnErrorReturn(FAILED(hr), hr);

	hr = pTextGraph->put_Bold(VARIANT_TRUE);
	OnErrorReturn(FAILED(hr), hr);
		
	CComBSTR sFont = "Arial";
	hr = pTextGraph->put_Font(sFont);
	OnErrorReturn(FAILED(hr), hr);	
	
	CComBSTR sText = "This is Client Graphics Text.";
	hr = pTextGraph->put_Text(sText);
	OnErrorReturn(FAILED(hr), hr);
		
	hr = pTextGraph->put_FontSize(28);
	OnErrorReturn(FAILED(hr), hr);	
	
	hr = pTextGraph->PutTextColor(0, 255, 255);
	OnErrorReturn(FAILED(hr), hr);
		
	hr = m_pApplication->ActiveView->Update();
	OnErrorReturn(FAILED(hr), hr);
	
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CButtonDefEvents

IMPLEMENT_DYNCREATE(CButtonDefEvents, CCmdTarget)

CButtonDefEvents::CButtonDefEvents(CTextClientGraphAddInServer* pAddIn, UINT nID) : m_pAddIn(pAddIn), m_nID(nID)
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

void CButtonDefEvents::OnExecuteEvent(NameValueMap* context) 
{
	if(m_pAddIn)
		m_pAddIn->ExecuteCommand(m_nID);
}


















