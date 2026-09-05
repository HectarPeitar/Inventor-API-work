//-----------------------------------------------------------------------------
//----- RackFaceDefinition.cpp : Implementation of CRackFaceDefinition
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "RackFaceDefinition.h"

//-----------------------------------------------------------------------------
//----- Implementation of ChangeDefinition Events sink methods
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
STDMETHODIMP CRackFaceDefinition::OnReplay (NameValueMap *pContext, ChangeProcessorObject **ppResultProcessor)
{	
	HRESULT hr;

	//create the rack face request
	m_pRackFaceRequest = new CRackFaceRequest(m_pApplication);

	hr = ExecuteChangeRequest(m_pRackFaceRequest, ppResultProcessor);
	if (FAILED(hr)) return hr;

	return S_OK;
}

void CRackFaceDefinition::TerminateReplay()
{
	delete m_pRackFaceRequest;
	m_pRackFaceRequest = NULL;
}

