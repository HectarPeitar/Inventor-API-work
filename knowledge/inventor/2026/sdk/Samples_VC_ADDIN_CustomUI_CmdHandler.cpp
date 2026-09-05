//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted,
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting documentation. 
// <YOUR COMPANY NAME> PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// <YOUR COMPANY NAME> SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE. <YOUR COMPANY NAME>, INC.
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE. 
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable
// 

//-----------------------------------------------------------------------------
//----- CmdHandler.cpp : Implementation of CCmdHandler
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "CustomUI.h"
#include "CmdHandler.h"
#include <atlwin.h>

HRESULT CCmdHandler::CreateButtonDefinition(Application* pApplication, 
												   BSTR bstrDisplayName, 
												   BSTR bstrInternalName, 
												   CommandTypesEnum eCommandType, 
												   VARIANT varClientId, 
												   BSTR bstrDescription, 
												   BSTR bstrToolTip, 
												   int StandardIconResId, 
												   int LargeIconResId, 
												   ButtonDisplayEnum eButtonDisplayType)
{
	// Get the hwnd
	//
	HRESULT hr = pApplication->get_MainFrameHWND((long *)&m_ParentHwnd);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;

	// Extract the icon resource
	//
	HICON hIcon = (HICON) LoadImage( _Module.GetResourceInstance(), MAKEINTRESOURCE(StandardIconResId), IMAGE_ICON, 0, 0, NULL);
	ATLASSERT(hIcon);
	if (NULL == hIcon) return E_FAIL;

	HICON hIconLg = (HICON) LoadImage( _Module.GetResourceInstance(), MAKEINTRESOURCE(LargeIconResId), IMAGE_ICON, 0, 0, NULL);
	ATLASSERT(hIconLg);
	if (NULL == hIconLg) return E_FAIL;

	// Create the picture 4
	//
	PICTDESC pdesc;
	pdesc.cbSizeofstruct = sizeof(pdesc);
	pdesc.picType = PICTYPE_ICON;
	pdesc.icon.hicon = hIcon;

	CComPtr<IPictureDisp> pPictureDisp;
	
	// 3rd arg is FALSE, so that the picture (icon) does not get destroyed when the picture obj is released
	// we will destroy it ourselves
	//
	hr = ::OleCreatePictureIndirect(&pdesc, IID_IPictureDisp, FALSE, (LPVOID*)&pPictureDisp );
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;
	
	PICTDESC pdesclg;
	pdesclg.cbSizeofstruct = sizeof(pdesc);
	pdesclg.picType = PICTYPE_ICON;
	pdesclg.icon.hicon = hIconLg;

	CComPtr<IPictureDisp> pPictureDispLg;
	
	// 3rd arg is FALSE, so that the picture (icon) does not get destroyed when the picture obj is released
	// we will destroy it ourselves
	//
	hr = ::OleCreatePictureIndirect(&pdesclg, IID_IPictureDisp, FALSE, (LPVOID*)&pPictureDispLg );
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;

	CComVariant vtPictdisp(pPictureDisp);
	CComVariant vtPictdispLg(pPictureDispLg);
	
	CComPtr<CommandManager> pCommandMgr;
	hr = pApplication->get_CommandManager(&pCommandMgr);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;

	CComPtr<ControlDefinitions> pCtrlDefs;
	hr = pCommandMgr->get_ControlDefinitions(&pCtrlDefs);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;

	// Create the button definition handler
	// Make sure the Internal Name is unique (you could follow a naming scheme like: "CompanyName:ProductName:ItemName")
	hr = pCtrlDefs->AddButtonDefinition(bstrDisplayName, bstrInternalName, eCommandType, varClientId, bstrDescription, bstrToolTip, vtPictdisp, vtPictdispLg, eButtonDisplayType, &m_pBtnDef); 

	// Destroy the icons
	//
	DestroyIcon(hIcon);
	DestroyIcon(hIconLg);

	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;
	
	// Sync up the event handler
	//
	hr = this->DispEventAdvise(m_pBtnDef);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;

	return hr;
}

HRESULT CCmdHandler::GetButtonDefinition(ButtonDefinitionObject** pBtnDef)
{
	HRESULT hr;
	hr = m_pBtnDef.QueryInterface(pBtnDef);

	if (pBtnDef != NULL)
		return S_OK;
	else
		return E_FAIL;
}

HRESULT CCmdHandler::Cleanup()
{
	HRESULT hr = this->DispEventUnadvise(m_pBtnDef);
	ATLASSERT(SUCCEEDED(hr));

	m_pBtnDef = NULL;
	return hr;
}
