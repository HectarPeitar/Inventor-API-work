//-----------------------------------------------------------------------------
//----- ChangeDefinition.h : Declaration of the CChangeDefinition
//-----------------------------------------------------------------------------
#ifndef _ChangeDefinition_h_
#define _ChangeDefinition_h_

#include "../resource.h"

#include "ChangeRequest.h"

//-----------------------------------------------------------------------------
class ATL_NO_VTABLE CChangeDefinition : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispEventImpl<0, CChangeDefinition, &DIID_ChangeDefinitionSink, &LIBID_Inventor, 1, 0>
{
public:
	CChangeDefinition () {

		m_pApplication = NULL;

		m_pChangeDefinitionObj = NULL;

	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CChangeDefinition)
	END_COM_MAP()

	BEGIN_SINK_MAP(CChangeDefinition)
		SINK_ENTRY_EX (0, DIID_ChangeDefinitionSink, ChangeDefinitionSink_OnReplayMeth, OnReplay)
	END_SINK_MAP()

protected:
	//Inventor application object
	CComPtr<Application> m_pApplication;

	//ChangeDefinition object
	CComPtr<ChangeDefinitionObject> m_pChangeDefinitionObj;

public:
	//----- ChangeDefinitionSink
	STDMETHOD(OnReplay) (NameValueMap *pContext, ChangeProcessorObject **ppResultProcessor) = 0;

	virtual void TerminateReplay() = 0;

	//change definition creation/termination methods
	HRESULT Create(Application* pApplication, BSTR bstrDisplayName, BSTR bstrInternalName);
	HRESULT Remove();

//change request connection methods
protected:
	HRESULT ExecuteChangeRequest(CChangeRequest *pChangeRequest, ChangeProcessorObject **ppResultProcessor);

} ;

//-----------------------------------------------------------------------------
#endif //----- _ChangeDefinition_h_
