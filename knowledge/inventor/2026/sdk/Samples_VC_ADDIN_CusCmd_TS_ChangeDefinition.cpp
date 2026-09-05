//-----------------------------------------------------------------------------
//----- ChangeDefinition.cpp : Implementation of CChangeDefinition
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "ChangeDefinition.h"

HRESULT CChangeDefinition::Create(Application* pApplication, BSTR bstrDisplayName, BSTR bstrInternalName)
{
	HRESULT hr;

	//store the Inventor application object
	m_pApplication = pApplication;

	//get the change manager object
	CComPtr<ChangeManager> pChangeManager;
	hr = m_pApplication->get_ChangeManager(&pChangeManager);
	if (FAILED(hr)) return hr;

	//get the change definitions collection object
	CComPtr<ChangeDefinitions> pChangeDefinitions;
	hr = pChangeManager->Add(CComBSTR(_T("{05CC5326-B165-483A-8A2A-4B52B7A54BEF}")), &pChangeDefinitions);
	if (FAILED(hr)) return hr;

	//create the change definition
	hr = pChangeDefinitions->Add(bstrInternalName, bstrDisplayName, &m_pChangeDefinitionObj);
	if (FAILED(hr))	return hr;

	//connect event handler in order to receive change definition events
	hr = DispEventAdvise(m_pChangeDefinitionObj);
	if (FAILED(hr))	return hr;

	return S_OK;
}

HRESULT CChangeDefinition::Remove()
{
	HRESULT hr;

	bool bMethodFailed = false;

	if (m_pChangeDefinitionObj != NULL){

		//disconnect change definition events sink
		hr = DispEventUnadvise (m_pChangeDefinitionObj);
		if (FAILED(hr))	bMethodFailed = true;

		//delete change definition
		hr = m_pChangeDefinitionObj->Delete();
		if (FAILED(hr))	bMethodFailed = true;	

	}

	if (bMethodFailed) return E_FAIL;
	else return S_OK;

}

HRESULT CChangeDefinition::ExecuteChangeRequest(CChangeRequest *pChangeRequest, ChangeProcessorObject **ppResultProcessor)
{
	HRESULT hr;

	//create the change processor object from change definition
	CComPtr<ChangeProcessorObject> pChangeProcessorObj;
	hr = m_pChangeDefinitionObj->CreateChangeProcessor(&pChangeProcessorObj);
	if (FAILED(hr)) return hr;

	hr = pChangeProcessorObj.CopyTo(ppResultProcessor);
	if (FAILED(hr)) return hr;

	//execute the specified change request 
	hr = pChangeRequest->Execute(this, pChangeProcessorObj);
	if (FAILED(hr)) return hr;

	return S_OK;
}


