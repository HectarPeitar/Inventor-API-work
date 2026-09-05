//-----------------------------------------------------------------------------
//----- ChangeProcessor.cpp : Implementation of CChangeProcessor
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "ChangeProcessor.h"
#include "ChangeRequest.h"

HRESULT CChangeProcessor::Connect(Application *pApplication, VARIANT varChangeDefinition, Document *pDocument)
{
	HRESULT hr;

	//get the change manager object
	CComPtr<ChangeManager> pChangeManager;
	hr = pApplication->get_ChangeManager(&pChangeManager);
	if (FAILED(hr)) return hr;

	//get the change definitions collection for this AddIn
	CComPtr<ChangeDefinitions> pChangeDefinitions;
	hr = pChangeManager->get_Item(CComVariant(_T("{05CC5326-B165-483A-8A2A-4B52B7A54BEF}")), &pChangeDefinitions);
	if (FAILED(hr)) return hr;

	//get the specified change definition object
	CComPtr<ChangeDefinitionObject> pChangeDefinitionObj;
	hr = pChangeDefinitions->get_Item(varChangeDefinition, &pChangeDefinitionObj);
	if (FAILED(hr)) return hr;

	//create the change processor associated with the change definition
	hr = pChangeDefinitionObj->CreateChangeProcessor(&m_pChangeProcessorObj);
	if (FAILED(hr)) return hr;

	//connect event handler in order to receive change processor events
	hr = DispEventAdvise(m_pChangeProcessorObj);
	if (FAILED(hr)) return hr;

	//execute the change processor
	hr = m_pChangeProcessorObj->Execute(pDocument);
	if (FAILED(hr)) return hr;

	return S_OK;
}

HRESULT CChangeProcessor::Disconnect()
{
	HRESULT hr;

	//disconnect change processor events sink
	if (m_pChangeProcessorObj != NULL){

		hr = DispEventUnadvise(m_pChangeProcessorObj);

		m_pChangeProcessorObj = NULL;
	
	}

	return hr;
}

void CChangeProcessor::SetParentRequest(CChangeRequest *pParentRequest)
{
	//store the parent request object
	m_pParentRequest = pParentRequest;
}

//-----------------------------------------------------------------------------
//----- Implementation of ChangeProcessor Events sink methods
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
STDMETHODIMP CChangeProcessor::ChangeProcessorEvents_OnExecute (Document *pDocument, NameValueMap *pContext, VARIANT_BOOL *pSucceeded)
{
	HRESULT hr;

	hr = m_pParentRequest->ChangeProcessorEvents_OnExecute(pDocument, pContext, pSucceeded);
	if(FAILED(hr)) return hr;

	return S_OK;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CChangeProcessor::ChangeProcessorEvents_OnTerminate ()
{	
	HRESULT hr;

	//terminate the command execute change request
	hr = m_pParentRequest->Terminate();
	if(FAILED(hr)) return hr;

	return S_OK;
}



