#include "StdAfx.h"
#include "ToggleSlotStateCommandButton.h"

//-----------------------------------------------------------------------------
STDMETHODIMP CToggleSlotStateCommandButton::ButtonDefinitionEvents_OnExecute (NameValueMap *pContext) 
{ 		
	HRESULT hr;

	CComPtr<CommandManager> pCommandManager;
	hr = m_pApplication->get_CommandManager(&pCommandManager);
	if(FAILED(hr)) return hr;	

	CComPtr<ControlDefinitions> pControlDefinitions;
	hr = pCommandManager->get_ControlDefinitions(&pControlDefinitions);
	if(FAILED(hr)) return hr;

	CComPtr<ControlDefinition> pDrawSlotCtrlDef;
	hr = pControlDefinitions->get_Item(CComVariant("Autodesk:SimpleAddIn:DrawSlotCmd"), &pDrawSlotCtrlDef);
	if(FAILED(hr)) return hr;

	CComQIPtr<ButtonDefinitionObject> pDrawSlotCmdBtnDef(pDrawSlotCtrlDef);
	if (!pDrawSlotCmdBtnDef) return E_FAIL;

	VARIANT_BOOL varbIsEnabled;
	hr = pDrawSlotCmdBtnDef->get_Enabled(&varbIsEnabled);
	if(FAILED(hr)) return hr;

	if(varbIsEnabled != VARIANT_FALSE)
		hr = pDrawSlotCmdBtnDef->put_Enabled(VARIANT_FALSE);
	else
		hr = pDrawSlotCmdBtnDef->put_Enabled(VARIANT_TRUE);

	return S_OK; 	
}
