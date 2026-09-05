// CommandButton.cpp : Implementation of CCommandButton

#include "stdafx.h"
#include "CommandButton.h"


// CCommandButton

HRESULT CCommandButton::CreateButtonDefinition(Application* pApplication, 
												   BSTR bstrDisplayName, 
												   BSTR bstrInternalName, 
												   CommandTypesEnum eCommandType, 
												   VARIANT varClientId, 
												   BSTR bstrDescription, 
												   BSTR bstrToolTip, 
												   int StandardIconResId, 
												   int LargeIconResId, 
												   ButtonDisplayEnum eButtonDisplayType,
												   ButtonDefinitionObject** pCommandButtonDefinition)
{
	HRESULT hr;

	m_pApplication = pApplication;

	// Extract the icon resource
	HICON hIcon = (HICON) LoadImage(_AtlBaseModule.GetResourceInstance(), MAKEINTRESOURCE(StandardIconResId), IMAGE_ICON, 0, 0, NULL);
	ATLASSERT(hIcon);
	if (NULL == hIcon) return E_FAIL;

	HICON hIconLg = (HICON) LoadImage(_AtlBaseModule.GetResourceInstance(), MAKEINTRESOURCE(LargeIconResId), IMAGE_ICON, 0, 0, NULL);
	ATLASSERT(hIconLg);
	if (NULL == hIconLg) return E_FAIL;

	// Create the picture 
	PICTDESC pdesc;
	pdesc.cbSizeofstruct = sizeof(pdesc);
	pdesc.picType = PICTYPE_ICON;
	pdesc.icon.hicon = hIcon;

	CComPtr<IPictureDisp> pPictureDisp;
	
	hr = ::OleCreatePictureIndirect(&pdesc, IID_IPictureDisp, FALSE, (LPVOID*)&pPictureDisp );
	if(FAILED(hr)) return hr;
	
	PICTDESC pdesclg;
	pdesclg.cbSizeofstruct = sizeof(pdesc);
	pdesclg.picType = PICTYPE_ICON;
	pdesclg.icon.hicon = hIconLg;

	CComPtr<IPictureDisp> pPictureDispLg;
	
	hr = ::OleCreatePictureIndirect(&pdesclg, IID_IPictureDisp, FALSE, (LPVOID*)&pPictureDispLg );
	if(FAILED(hr)) return hr;

	CComVariant vtPictdisp(pPictureDisp);
	CComVariant vtPictdispLg(pPictureDispLg);
	
	CComPtr<CommandManager> pCommandMgr;
	hr = m_pApplication->get_CommandManager(&pCommandMgr);
	if(FAILED(hr)) return hr;

	CComPtr<ControlDefinitions> pCtrlDefs;
	hr = pCommandMgr->get_ControlDefinitions(&pCtrlDefs);
	if(FAILED(hr)) return hr;

	// Create the button definition handler
	hr = pCtrlDefs->AddButtonDefinition(bstrDisplayName, bstrInternalName, eCommandType, varClientId, bstrDescription, bstrToolTip, vtPictdisp, vtPictdispLg, eButtonDisplayType, &m_pCommandButtonDef); 
	m_pCommandButtonDef.QueryInterface(pCommandButtonDefinition);
	if (FAILED(hr))	return hr;

	// Destroy the icons
	DestroyIcon(hIcon);
	DestroyIcon(hIconLg);

	// Sync up the event handler
	hr = this->DispEventAdvise(m_pCommandButtonDef);
	if(FAILED(hr)) return hr;

	return hr;
}

HRESULT CCommandButton::GetButtonDefinition(ButtonDefinitionObject** pCommandButtonDef)
{
	HRESULT hr;
	hr = m_pCommandButtonDef.QueryInterface(pCommandButtonDef);

	if (pCommandButtonDef != NULL)
		return S_OK;
	else
		return E_FAIL;
}

HRESULT CCommandButton::Disconnect()
{
	HRESULT hr = this->DispEventUnadvise(m_pCommandButtonDef);
	if(FAILED(hr)) return hr;

	m_pCommandButtonDef = NULL;
	return hr;
}

