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

// [!output IMPL_FILE] : Implementation of [!output CLASS_NAME]

#include "stdafx.h"
#include "[!output HEADER_FILE]"


// [!output CLASS_NAME]

[!if !ATTRIBUTED]
[!if SUPPORT_ERROR_INFO]
STDMETHODIMP [!output CLASS_NAME]::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_[!output INTERFACE_NAME]
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
[!endif]
[!endif]

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnNewDocument (Document *pDocumentObject, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here. Document *pDocumentObject might be NULL depending on the context

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ; 
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnOpenDocument (Document *pDocumentObject, BSTR FullFileName, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here. Document *pDocumentObject might be NULL depending on the context

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnSaveDocument (Document *pDocumentObject, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here. Document *DocumentObject might be NULL depending on the context

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnCloseDocument (Document *pDocumentObject, BSTR FullFileName, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here. Document *pDocumentObject might be NULL depending on the context

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnActivateDocument (Document *pDocumentObject, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here. Document *pDocumentObject might be NULL depending on the context

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnDeactivateDocument (Document *pDocumentObject, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here. Document *pDocumentObject might be NULL depending on the context

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnQuit (EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnNewEditObject (IDispatch *pEditObject, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here. IDispatch *EditObject might be NULL depending on the context

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnTranslateDocument (VARIANT_BOOL TranslatingIn, Document *pDocumentObject, BSTR FullFileName, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here. IDispatch *pDocumentObject might be NULL depending on the context
	
	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnActiveProjectChanged (DesignProject *pProjectObject, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnDocumentChange (Document *pDocumentObject, EventTimingEnum BeforeOrAfter, CommandTypesEnum ReasonsForChange, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnReady (EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnInitializeDocument (Document *pDocumentObject, BSTR FullDocumentName, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)  {
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here. Document *pDocumentObject might be NULL depending on the context

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnTerminateDocument (Document *pDocumentObject, BSTR FullDocumentName, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)  {
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here. Document *pDocumentObject might be NULL depending on the context

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnNewView (View *pViewObject, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnDisplayModeChange (View *pViewObject, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnCloseView (View *pViewObject, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnActivateView (View *pViewObject, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnDeactivateView (View *pViewObject, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnApplicationOptionChange (EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnMigrateDocument (Document *pDocumentObject, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here. Document *pDocumentObject might be NULL depending on the context

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnRestart32BitHost (EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnMoveApplicationWindow (Application *pApplicationObject, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnMoveView (View *pViewObject, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnResizeApplicationWindow (Application *pApplicationObject, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnResizeView (View *pViewObject, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}