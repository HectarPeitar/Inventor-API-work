//-----------------------------------------------------------------------------
//----- ChangeProcessor.cpp : Implementation of CChangeProcessor
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "ChangeProcessor.h"
#include "ChangeRequest.h"
#include "ChangeDefinition.h"

//called during command forward create scenario, creates a change processor object and executes it
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

//called during transcript replay scenario, stores the change processor object supplied by the change definition
HRESULT CChangeProcessor::Connect(ChangeProcessorObject *pChangeProcessorObj)
{
	HRESULT hr;

	//store a copy of the change processor 
	m_pChangeProcessorObj = pChangeProcessorObj;

	//connect event handler in order to receive change processor events
	hr = DispEventAdvise(m_pChangeProcessorObj);
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

void CChangeProcessor::SetParentDefinition(CChangeDefinition *pParentDefinition)
{
	//store the parent definition object
	m_pParentDefinition = pParentDefinition;

	//also, set the boolean to indicate that request is executed due to transcript replay
	m_bTranscriptReplay = true;
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
STDMETHODIMP CChangeProcessor::OnReadFromScript (Document *pDocument, BSTR Inputs, NameValueMap *pContext)
{
	HRESULT hr;

	hr = m_pParentRequest->ChangeProcessorEvents_OnReadFromScript (pDocument, Inputs, pContext);
	if(FAILED(hr)) return hr;

	return S_OK;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CChangeProcessor::OnWriteToScript (Document *pDocument, NameValueMap *pContext, BSTR *pResultInputs)
{
	HRESULT hr;

	hr = m_pParentRequest->ChangeProcessorEvents_OnWriteToScript (pDocument, pContext, pResultInputs);
	if(FAILED(hr)) return hr;

	return S_OK;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CChangeProcessor::ChangeProcessorEvents_OnTerminate ()
{	
	HRESULT hr;

	bool bMethodFailed = false;

	hr = m_pParentRequest->Terminate();
	if (FAILED(hr)) bMethodFailed = true;

	//if transcript replay scenario, end transcript replay
	if (m_bTranscriptReplay)
		m_pParentDefinition->TerminateReplay();

	if (bMethodFailed) return E_FAIL;
	else return S_OK;
}



