/*
  DESCRIPTION

  This file contains the implementation of the class that offers the first contact with
  Inventor.

*/

#include "stdafx.h"

#include "rxsamplecommand.h"
#include "samplecommand.h"
#include "replicateworkplane.h"
#include "patternsketch.h"
#include "AfxCtl.h"


// The addin wizard adds command id definitions here.
#define CMD_ReplicateWorkplaneCommand			1
#define CMD_SketchPatternCommand				2

/*--------------------- IUnknown-interface related implementation  --------------------------------*/

/*
 * All of the standard IUnknown interfaces are taken care of in the CUnknown
 * class. The implementation in the CUnknown class relies on this override that
 * should end up looking like a non-delegating QueryInterface, except for the fact that QI
 * for the IUnknown is also taken care of by CUnknown (control will never reach here if
 * QI-ed for IUnknown).
 */

HRESULT CRxSampleCommand::InternalQueryInterface (REFIID riid, void **ppv)
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

CRxSampleCommand::CRxSampleCommand () : CUnknown (NULL)
{ 
	m_pSite = NULL;

	m_pButtonEvents1 = new CButtonDefEvents(this, CMD_ReplicateWorkplaneCommand);
	m_pButtonEvents2 = new CButtonDefEvents(this, CMD_SketchPatternCommand);
	
	m_btnDefCookie1 = 0;
	m_btnDefCookie2 = 0;

	::IncrementObjectCount();
}

CRxSampleCommand::~CRxSampleCommand()
{
	AFX_MANAGE_STATE (AfxGetAppModuleState()); 
	
	if (m_pSite)
		m_pSite = NULL;

	if(m_pButtonEvents1)
		delete m_pButtonEvents1;

	if(m_pButtonEvents2)
		delete m_pButtonEvents2;

	m_pBtnDef1 = NULL;
	m_pBtnDef2 = NULL;

	::DecrementObjectCount();
}

/*---------------------- IRxApplicationAddInServer interface ---------------------------------*/

HRESULT CRxSampleCommand::Activate (IRxApplicationAddInSite *pAddInSite, BooleanType bFirstTime)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT Result=NOERROR;
	CComPtr<IUnknown> pAppUnk;
	variant_t vInTools(VARIANT_TRUE);

	// High-level interfaces supplied directly and implicitly by Inventor to the
	// AddIn. These may be held right up until the directive to shutdown (Deactivate) is received.

	m_pSite = pAddInSite;

	Result = pAddInSite->get_Application (&pAppUnk);
	OnErrorReturn(FAILED (Result), Result);

	Result = pAppUnk->QueryInterface (DIID_Application, (void **) &m_pApplication);
	OnErrorReturn(FAILED (Result), Result);

	pAppUnk = NULL;

	CreateCommands();

	// New up your commands here
	m_pPatternSketchCmd = new PatternSketchCmd(m_pApplication);
	m_pReplicateWorkplaneCmd = new ReplicateWorkplaneCmd(m_pApplication);

	ASSERT(m_pPatternSketchCmd);
	ASSERT(m_pReplicateWorkplaneCmd);

	return Result;
}
    
HRESULT CRxSampleCommand::Deactivate ()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

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

	// Delete Commands
	delete m_pPatternSketchCmd;
	delete m_pReplicateWorkplaneCmd;

	// Cleanup up of interfaces supplied by Inventor and held on by this AddIn 
	// at initialization or load.

	m_pApplication = NULL;
	m_pSite = NULL;

	return NOERROR;
}


HRESULT CRxSampleCommand::ExecuteCommand (long CommandID)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT Result=NOERROR;

	// Handle commands
	switch (CommandID)
	{
	case CMD_ReplicateWorkplaneCommand: 
		m_pReplicateWorkplaneCmd->BeginCommand();
		break;
	case CMD_SketchPatternCommand: 
		m_pPatternSketchCmd->BeginCommand();
		break;
	default:
		Result = E_NOTIMPL;
	}

	return Result;
}

HRESULT CRxSampleCommand::get_Automation (IUnknown **ppUnk)
{
  return E_NOINTERFACE;
}

void CRxSampleCommand::CreateCommands()
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
	vtAddInId	      = _T("{F7F6732C-376D-4EAE-9F88-1E270638717E}");
	// command type
	eCmdType = kQueryOnlyCmdType;
	// button display type
	eCmdDisplayType = kAlwaysDisplayText;

	// Add the Replicate Workplane command
	InternalNameBSTR  =	_T("SampleCommandAddIn.ReplicateCmd");
	displayNameBSTR	  =	_T("ReplicateWorkplane");
	DesTextBSTR		  =	_T("Execute Replicate Workplane Command");
	TooltipTextBSTR	  =	_T("Replicate Workplane");	

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

	// Add the Sketch Pattern command
	InternalNameBSTR  =	_T("SampleCommandAddIn.SketchPatternCmd");
	displayNameBSTR	  =	_T("SketchPattern");
	DesTextBSTR		  =	_T("Execute Sketch Pattern Command");
	TooltipTextBSTR	  =	_T("Sketch Pattern");
	

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
// CButtonDefHandlerEvents

IMPLEMENT_DYNCREATE(CButtonDefEvents, CCmdTarget)

CButtonDefEvents::CButtonDefEvents(CRxSampleCommand* pAddIn, UINT nID) : m_pAddIn(pAddIn), m_nID(nID)
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

void CButtonDefEvents::OnExecuteEvent(NameValueMap* context) 
{
	if(m_pAddIn)
		m_pAddIn->ExecuteCommand(m_nID);
}
