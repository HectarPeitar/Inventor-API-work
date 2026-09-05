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
//----- [!output ADDIN_NAME].cpp : Implementation of C[!output ADDIN_NAME]
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "[!output PROJECT_NAME].h"
#include "[!output ADDIN_NAME].h"

[!if USE_VTABLE]
//-----------------------------------------------------------------------------
STDMETHODIMP C[!output ADDIN_NAME]::Activate (IRxApplicationAddInSite *pAddInSite, BooleanType FirstTime)
{
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
[!endif]

	if ( pAddInSite == NULL )
		return E_INVALIDARG ;
	m_pAddInSite =pAddInSite ;

	//----- Get the application object.
	CComPtr<IUnknown> pAppUnk ;
	HRESULT hr =m_pAddInSite->get_Application (&pAppUnk) ;
	ATLASSERT( SUCCEEDED( hr ) ) ;
	if ( FAILED( hr ) )
		return hr ;

	hr =pAppUnk->QueryInterface (&m_pApplication) ;
	ATLASSERT( SUCCEEDED( hr ) ) ;
	if ( FAILED( hr ) )
		return hr ;

	return S_OK ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP C[!output ADDIN_NAME]::Deactivate ()
{
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
[!endif]

	m_pAddInSite.Release () ;
	m_pApplication.Release () ;

	return S_OK ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP C[!output ADDIN_NAME]::ExecuteCommand (LONG CommandID)
{
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
[!endif]

	return S_OK ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP C[!output ADDIN_NAME]::get_Automation (IUnknown **ppResult)
{
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
[!endif]

	if ( ppResult == NULL )
		return E_POINTER ;
	*ppResult =NULL ;

	//return S_OK ; //- If you do anything in there
	return E_NOTIMPL ;
}

[!if !ADDIN_APPTYPE]
//-----------------------------------------------------------------------------
STDMETHODIMP C[!output ADDIN_NAME]::get_HasOpenOptions (DataMedium *pSourceData, TranslationContext *pContext, NameValueMap *pDefaultOptions, char *pResult)
{
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
[!endif]

	if ( pSourceData == NULL || pContext == NULL || pDefaultOptions == NULL )
		return E_INVALIDARG ;
	if ( pResult == NULL )
		return E_POINTER ;
	*pResult =FALSE ;

	//return S_OK ; //- If you do anything in there
	return E_NOTIMPL ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP C[!output ADDIN_NAME]::ShowOpenOptions (DataMedium *pSourceData, TranslationContext *pContext, NameValueMap *pChosenOptions)
{
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
[!endif]
	if ( pSourceData == NULL || pContext == NULL || pChosenOptions == NULL )
		return E_INVALIDARG ;

	//return S_OK ; //- If you do anything in there
	return E_NOTIMPL ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP C[!output ADDIN_NAME]::Open (DataMedium *pSourceData, TranslationContext *pContext, NameValueMap *pOptions, IUnknown **ppTargetObject)
{
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
[!endif]
	if ( pSourceData == NULL || pContext == NULL || pOptions == NULL )
		return E_INVALIDARG ;
	if ( ppTargetObject == NULL )
		return E_POINTER ;
	*ppTargetObject =NULL ;

	//return S_OK ; //- If you do anything in there
	return E_NOTIMPL ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP C[!output ADDIN_NAME]::get_HasSaveCopyAsOptions (IUnknown *pSourceObject, TranslationContext *pContext, NameValueMap *pDefaultOptions, char *pResult)
{
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
[!endif]
	if ( pSourceObject == NULL || pContext == NULL || pDefaultOptions == NULL )
		return E_INVALIDARG ;
	if ( pResult == NULL )
		return E_POINTER ;
	*pResult =FALSE ;

	//return S_OK ; //- If you do anything in there
	return E_NOTIMPL ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP C[!output ADDIN_NAME]::ShowSaveCopyAsOptions (IUnknown *pSourceObject, TranslationContext *pContext, NameValueMap *pChosenOptions)
{
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
[!endif]
	if ( pSourceObject == NULL || pContext == NULL || pChosenOptions == NULL )
		return E_INVALIDARG ;

	//return S_OK ; //- If you do anything in there
	return E_NOTIMPL ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP C[!output ADDIN_NAME]::SaveCopyAs (IUnknown *pSourceObject, TranslationContext *pContext, NameValueMap *pOptions, DataMedium *pTargetData)
{
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
[!endif]
	if ( pSourceObject == NULL || pContext == NULL || pOptions == NULL || pTargetData == NULL )
		return E_INVALIDARG ;

	//return S_OK ; //- If you do anything in there
	return E_NOTIMPL ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP C[!output ADDIN_NAME]::GetThumbnail (DataMedium *pSourceData, VARIANT *pResult)
{
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
[!endif]

	if ( pSourceData == NULL )
		return E_INVALIDARG ;
	if ( pResult == NULL )
		return E_POINTER ;

	//return S_OK ; //- If you do anything in there
	return E_NOTIMPL ;
}

[!endif]
[!else]
//-----------------------------------------------------------------------------
STDMETHODIMP C[!output ADDIN_NAME]::OnActivate (VARIANT_BOOL FirstTime) {
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
[!endif]
	//- If needed, implement additional AddIn initialization code here...
	//- the m_pApplication member provides access to the Inventor Application object

	return S_OK ;
}

STDMETHODIMP C[!output ADDIN_NAME]::OnDeactivate () {
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
[!endif]
	//- If needed, implement additional AddIn clean-up code here...

	return S_OK ;
}

[!if !ADDIN_APPTYPE]
//- TranslatorAddInServer
STDMETHODIMP C[!output ADDIN_NAME]::get_HasOpenOptions (IDispatch *pSourceData, IDispatch *pContext, IDispatch *pDefaultOptions, VARIANT_BOOL *pResult) {
	//- DataMedium *pSourceData, TranslationContext *pContext, NameValueMap *pDefaultOptions
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
[!endif]
	if ( pSourceData == NULL || pContext == NULL || pDefaultOptions == NULL )
		return E_INVALIDARG ;
	if ( pResult == NULL )
		return E_POINTER ;
	*pResult =VARIANT_FALSE ;

	//return S_OK ; //- If you do anything in there
	return E_NOTIMPL ;
}

STDMETHODIMP C[!output ADDIN_NAME]::ShowOpenOptions (IDispatch *pSourceData, IDispatch *pContext, IDispatch *pChosenOptions) {
	//- DataMedium *pSourceData, TranslationContext *pContext, NameValueMap *pChosenOptions
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
[!endif]
	if ( pSourceData == NULL || pContext == NULL || pChosenOptions == NULL )
		return E_INVALIDARG ;

	//return S_OK ; //- If you do anything in there
	return E_NOTIMPL ;
}

STDMETHODIMP C[!output ADDIN_NAME]::Open (IDispatch *pSourceData, IDispatch * pContext, IDispatch *pOptions, IDispatch **ppTargetObject) {
	//- DataMedium *pSourceData, TranslationContext *pContext, NameValueMap *pOptions
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
[!endif]
	if ( pSourceData == NULL || pContext == NULL || pOptions == NULL )
		return E_INVALIDARG ;
	if ( ppTargetObject == NULL )
		return E_POINTER ;
	*ppTargetObject =NULL ;

	//return S_OK ; //- If you do anything in there
	return E_NOTIMPL ;
}

STDMETHODIMP C[!output ADDIN_NAME]::get_HasSaveCopyAsOptions (IDispatch *pSourceObject, IDispatch *pContext, IDispatch *pDefaultOptions, VARIANT_BOOL *pResult) {
	//- TranslationContext *pContext, NameValueMap *pDefaultOptions
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
[!endif]
	if ( pSourceObject == NULL || pContext == NULL || pDefaultOptions == NULL )
		return E_INVALIDARG ;
	if ( pResult == NULL )
		return E_POINTER ;
	*pResult =VARIANT_FALSE ;

	//return S_OK ; //- If you do anything in there
	return E_NOTIMPL ;
}

STDMETHODIMP C[!output ADDIN_NAME]::ShowSaveCopyAsOptions (IDispatch *pSourceObject, IDispatch *pContext, IDispatch *pChosenOptions) {
	//- TranslationContext *pContext, NameValueMap *pDefaultOptions
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
[!endif]
	if ( pSourceObject == NULL || pContext == NULL || pChosenOptions == NULL )
		return E_INVALIDARG ;

	//return S_OK ; //- If you do anything in there
	return E_NOTIMPL ;
}

STDMETHODIMP C[!output ADDIN_NAME]::SaveCopyAs (IDispatch *pSourceObject, IDispatch *pContext, IDispatch *pOptions, IDispatch *pTargetData) {
	//- TranslationContext *pContext, NameValueMap *pOptions, DataMedium *pTargetData
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
[!endif]
	if ( pSourceObject == NULL || pContext == NULL || pOptions == NULL || pTargetData == NULL )
		return E_INVALIDARG ;

	//return S_OK ; //- If you do anything in there
	return E_NOTIMPL ;
}

STDMETHODIMP C[!output ADDIN_NAME]::GetThumbnail (IDispatch *pSourceData, VARIANT *pResult) {
	//- DataMedium *pSourceData
[!if USE_MFC]
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
[!endif]
	if ( pSourceData == NULL )
		return E_INVALIDARG ;
	if ( pResult == NULL )
		return E_POINTER ;

	//return S_OK ; //- If you do anything in there
	return E_NOTIMPL ;
}
[!endif]
[!endif]

