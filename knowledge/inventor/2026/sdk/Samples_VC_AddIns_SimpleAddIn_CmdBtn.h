// CommandButton.h : Declaration of the CCommandButton

#pragma once
#include "resource.h"       // main symbols

#include "SimpleAddIn.h"


// CCommandButton

class ATL_NO_VTABLE CCommandButton : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispEventImpl<0, CCommandButton, &DIID_ButtonDefinitionSink, &LIBID_Inventor, 1, 0>
{

protected:
	//Inventor application object
	CComPtr<Application> m_pApplication;

	//Command button definition
	CComPtr<ButtonDefinitionObject> m_pCommandButtonDef;	

public:
	CCommandButton()
	{
		m_pApplication = NULL;
		m_pCommandButtonDef = NULL;
	}

	DECLARE_NO_REGISTRY()

	BEGIN_COM_MAP(CCommandButton)
	END_COM_MAP()

	BEGIN_SINK_MAP(CCommandButton)
		SINK_ENTRY_EX (0, DIID_ButtonDefinitionSink, ButtonDefinitionSink_OnExecuteMeth, ButtonDefinitionEvents_OnExecute)
	END_SINK_MAP()

public:
	//----- ButtonDefinitionSink
	STDMETHOD(ButtonDefinitionEvents_OnExecute) (NameValueMap *pContext) = 0;

	HRESULT CreateButtonDefinition(Application* pApplication, 
									BSTR bstrDisplayName, 
									BSTR bstrInternalName, 
									CommandTypesEnum eCommandType, 
									VARIANT varClientId, 
									BSTR bstrDescription, 
									BSTR bstrToolTip, 
									int StandardIconResId, 
									int LargeIconResId, 
									ButtonDisplayEnum eButtonDisplayType,
									ButtonDefinitionObject** pCommandButtonDefinition);

	HRESULT GetButtonDefinition(ButtonDefinitionObject** pCommandButtonDef);

	HRESULT Disconnect();
};