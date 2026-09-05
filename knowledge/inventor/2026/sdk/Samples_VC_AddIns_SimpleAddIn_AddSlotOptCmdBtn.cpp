#include "StdAfx.h"
#include "AddSlotOptionCommandButton.h"

//-----------------------------------------------------------------------------
STDMETHODIMP CAddSlotOptionCommandButton::ButtonDefinitionEvents_OnExecute (NameValueMap *pContext) 
{ 		
	HRESULT hr;

	CComPtr<CommandManager> pCommandManager;
	hr = m_pApplication->get_CommandManager(&pCommandManager);
	if(FAILED(hr)) return hr;

	CComPtr<ControlDefinitions> pControlDefinitions;
	hr = pCommandManager->get_ControlDefinitions(&pControlDefinitions);
	if(FAILED(hr)) return hr;

	CComPtr<ControlDefinition> pSlotHeightCtrlDef;
	hr = pControlDefinitions->get_Item(CComVariant("Autodesk:SimpleAddIn:SlotHeightCboBox"), &pSlotHeightCtrlDef);
	if(FAILED(hr)) return hr;

	CComPtr<ControlDefinition> pSlotWidthCtrlDef;
	hr = pControlDefinitions->get_Item(CComVariant("Autodesk:SimpleAddIn:SlotWidthCboBox"), &pSlotWidthCtrlDef);
	if(FAILED(hr)) return hr;
	
	CComQIPtr<ComboBoxDefinitionObject> pSlotHeightComboBoxDef(pSlotHeightCtrlDef);
	if (!pSlotHeightComboBoxDef) return E_FAIL;

	CComQIPtr<ComboBoxDefinitionObject> pSlotWidthComboBoxDef(pSlotWidthCtrlDef);
	if (!pSlotWidthComboBoxDef) return E_FAIL;

	long lNewIndex;
	hr = pSlotHeightComboBoxDef->get_ListCount(&lNewIndex);
	lNewIndex++;

	TCHAR strNewIndex[MAX_PATH];
	_ltot_s(lNewIndex, strNewIndex, MAX_PATH, 10);
	
	CComBSTR bstrNewHeightIndex(strNewIndex);
	bstrNewHeightIndex.Append(_T(" cm"));

	CComBSTR bstrNewWidthIndex(strNewIndex);
	bstrNewWidthIndex.Append(_T(" cm"));

	hr = pSlotHeightComboBoxDef->AddItem(bstrNewHeightIndex, lNewIndex);
	hr = pSlotWidthComboBoxDef->AddItem(bstrNewWidthIndex, lNewIndex);

	return S_OK; 	
}
