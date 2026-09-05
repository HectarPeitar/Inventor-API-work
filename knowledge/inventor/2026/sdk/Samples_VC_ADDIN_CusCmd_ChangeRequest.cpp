//-----------------------------------------------------------------------------
//----- ChangeRequestBase.cpp : Implementation of CChangeRequestBase
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "ChangeRequest.h"

HRESULT CChangeRequest::Execute(Application *pApplication, VARIANT varChangeDefinition, Document *pDocument)
{
	HRESULT hr;

	//create instance of ChangeProcessor class
	hr = CComObject<CChangeProcessor>::CreateInstance(&m_pChangeProcessor);
	if (FAILED(hr)) return hr;

	m_pChangeProcessor->AddRef();

	//set the parent to get the call back when change processor terminates
	m_pChangeProcessor->SetParentRequest(this);

	//connect change processor
	hr = m_pChangeProcessor->Connect(pApplication, varChangeDefinition, pDocument);
	if (FAILED(hr)) return hr;

	return S_OK;
}

HRESULT CChangeRequest::Terminate()
{
	HRESULT hr;

	//disconnect change processor
	if (m_pChangeProcessor != NULL){

		hr = m_pChangeProcessor->Disconnect();

		m_pChangeProcessor->Release();
		m_pChangeProcessor = NULL;
	}

	return hr;
}







