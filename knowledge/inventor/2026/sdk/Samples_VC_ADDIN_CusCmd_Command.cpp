//-----------------------------------------------------------------------------
//----- CommandBase.cpp : Implementation of CCommandBase
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "CustomCommand.h"
#include "Command.h"

HRESULT CCommand::CreateButton(Application* pApplication, BSTR bstrDisplayName, BSTR bstrInternalName, CommandTypesEnum CommandType, VARIANT varClientId, BSTR bstrDescription, BSTR bstrToolTip, VARIANT varStandardIcon, VARIANT varLargeIcon, ButtonDisplayEnum ButtonType, bool bAutoAddToGUI, ButtonDefinitionObject** pButtonDefinitionObj)
{
	HRESULT hr;

	//store the Inventor application object
	m_pApplication = pApplication;

	//get the Command Manager
	CComPtr<CommandManager> pCommandManager;
	hr = m_pApplication->get_CommandManager(&pCommandManager);
	if (FAILED(hr))	return hr;

	//create the command
	CComPtr<ControlDefinitions> pControlDefs;
	hr = pCommandManager->get_ControlDefinitions(&pControlDefs);
	if (FAILED(hr))	return hr;

	//create the button definition
	hr = pControlDefs->AddButtonDefinition(bstrDisplayName, bstrInternalName, CommandType, varClientId, bstrDescription, bstrToolTip, varStandardIcon, varLargeIcon, ButtonType, &m_pButtonDefinitionObj);
	m_pButtonDefinitionObj.QueryInterface(pButtonDefinitionObj);
	if (FAILED(hr))	return hr;

	//disable the button, it will be enabled when the part environment is activated
	hr = m_pButtonDefinitionObj->put_Enabled(VARIANT_FALSE);

	//connect the button events sink
	hr = DispEventAdvise(m_pButtonDefinitionObj);
	if (FAILED(hr))	return hr;

	//display button by default if specified 
	if(bAutoAddToGUI){

		hr = m_pButtonDefinitionObj->AutoAddToGUI();
		if (FAILED(hr))	return hr;
	}


	return S_OK;

}

HRESULT CCommand::GetButtonDefinition(ButtonDefinitionObject** pButtonDefinitionObj)
{
	HRESULT hr;

	hr = m_pButtonDefinitionObj.QueryInterface(pButtonDefinitionObj);
	if (FAILED(hr)) return hr;

	return S_OK;
}

HRESULT CCommand::RemoveButton()
{
	HRESULT hr;

	//disconnect button events sink
	if (m_pButtonDefinitionObj != NULL){

		hr = DispEventUnadvise(m_pButtonDefinitionObj);

		m_pButtonDefinitionObj = NULL;
	
	}

	return hr;
}

HRESULT CCommand::StartCommand()
{
	HRESULT hr;

	//start interaction events
	hr = StartInteraction();
	if (FAILED(hr))	return hr;

	//press the button
	hr = m_pButtonDefinitionObj->put_Pressed(VARIANT_TRUE);
	
	//set the command status to running
	m_bCommandIsRunning = true;	

	return S_OK;
}

HRESULT CCommand::StopCommand()
{
	HRESULT hr;

	bool bMethodFailed = false;

	//unsubscribe from the events
	hr = UnsubscribeFromEvents();
	if (FAILED(hr)) bMethodFailed = true;

	//stop interaction events
	hr = StopInteraction();
	if (FAILED(hr)) bMethodFailed = true;

	//un-press the button
	hr = m_pButtonDefinitionObj->put_Pressed(VARIANT_FALSE);

	//set the command status to not-running
	m_bCommandIsRunning = false;

	if (bMethodFailed) return E_FAIL;
	else return S_OK;	
}

HRESULT CCommand::StartInteraction ()
{	
	HRESULT hr;

	//create instance of the Interaction class
	hr = CComObject<CInteraction>::CreateInstance(&m_pInteraction);
	if (FAILED(hr)) return hr;

	m_pInteraction->AddRef();

	//set the parent to get the call back when event is terminated, or interaction is completed
	m_pInteraction->SetParentCmd(this);

	//set the interaction events name to the button's internal name
	CComBSTR bstrButtonDefObjInternalName;
	hr = m_pButtonDefinitionObj->get_InternalName(&bstrButtonDefObjInternalName);

	//start interaction events
	hr = m_pInteraction->StartInteraction(m_pApplication, bstrButtonDefObjInternalName, &m_pInteractionEvtsObj);
	if (FAILED(hr)) return hr;

	return S_OK;	
}

HRESULT CCommand::StopInteraction()
{
	HRESULT hr;

	//terminate interaction events
	hr = m_pInteraction->StopInteraction();

	m_pInteraction->Release();
	m_pInteraction = NULL;

	m_pInteractionEvtsObj = NULL;

	return hr;
}

HRESULT CCommand::SubscribeToEvent(CInteraction::InteractionTypeEnum InteractionType)
{
	HRESULT hr;

	//subscribe to the specified event type (selection, mouse etc.)
	//the event object is returned as IDispatch interface
	CComPtr<IDispatch> pEvtsObj;
	hr = m_pInteraction->SubscribeToEvent(InteractionType, &pEvtsObj);
	if (FAILED(hr)) return hr;

	//get the actual event object from the pEvtsObj object
	switch(InteractionType){

	case CInteraction::kSelection:
		
		//get the selection events object, if already subscribed to, first set it to NULL
		m_pSelectEvtsObj = NULL;
		hr = pEvtsObj.QueryInterface(&m_pSelectEvtsObj);
		if (FAILED(hr)) return hr;

		break;

	case CInteraction::kMouse:
		
		//get the mouse events object, if already subscribed to, first set it to NULL
		m_pMouseEvtsObj = NULL;
		hr = pEvtsObj.QueryInterface(&m_pMouseEvtsObj);
		if (FAILED(hr)) return hr;

		break;

	case CInteraction::kTriad:
		
		//get the triad events object, if already subscribed to, first set it to NULL
		m_pTriadEvtsObj = NULL;
		hr = pEvtsObj.QueryInterface(&m_pTriadEvtsObj);
		if (FAILED(hr)) return hr;

		break;
	}

	return S_OK;
}

HRESULT CCommand::UnsubscribeFromEvents()
{	
	HRESULT hr;

	//unsubscribe from all event objects (selection, mouse etc.)
	hr = m_pInteraction->UnsubscribeFromEvents();

	m_pSelectEvtsObj = NULL;
	m_pMouseEvtsObj = NULL;
	m_pTriadEvtsObj = NULL;

	return hr;
}

HRESULT CCommand::EnableInteraction()
{	
	HRESULT hr;

	//enable interaction events
	hr = m_pInteraction->EnableInteraction();
	if (FAILED(hr)) return hr;
	
	return S_OK;
}

HRESULT CCommand::DisableInteraction()
{		
	HRESULT hr;

	//disable interaction events
	hr = m_pInteraction->DisableInteraction();
	if (FAILED(hr)) return hr;

	return S_OK;
}

HRESULT CCommand::ExecuteChangeRequest(CChangeRequest *pChangeRequest, VARIANT varChangeDefinition, Document *pDocument)
{
	HRESULT hr;

	//execute the specified change request 
	hr = pChangeRequest->Execute(m_pApplication, varChangeDefinition, pDocument);
	if (FAILED(hr)) return hr;

	return S_OK;
}

