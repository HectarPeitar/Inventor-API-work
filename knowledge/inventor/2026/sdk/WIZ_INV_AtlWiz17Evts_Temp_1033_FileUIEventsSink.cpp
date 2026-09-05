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
STDMETHODIMP [!output CLASS_NAME]::OnFileNewDialog (BSTR TemplateDir, long ParentHWND, BSTR *pTemplateFileName, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnFileOpenDialog (SAFEARRAY *pFileTypes, long ParentHWND, BSTR *pFileName, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnFileSaveAsDialog (SAFEARRAY *pFileTypes, VARIANT_BOOL bSaveCopyAs, long ParentHWND, BSTR *pFileName, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnFileInsertNewDialog (BSTR TemplateDir, SAFEARRAY *pFileTypes, Document *pDocumentObject, long ParentHWND, BSTR *pTemplateFileName, BSTR *pFileName, BSTR *pRelativeFileName, BSTR *pLibraryName, SAFEARRAY *pCustomLogicalName, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnFileInsertDialog (SAFEARRAY *pFileTypes, Document *pDocumentObject, long ParentHWND, BSTR *pFileName, BSTR *pRelativeFileName, BSTR *pLibraryName, SAFEARRAY *pCustomLogicalName, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnFileNew (DocumentTypeEnum *pDocumentType, BSTR *pTemplateFileName, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnFileOpenFromMRU (BSTR *pFullFileName, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::OnPopulateFileMetadata (ObjectsEnumerator *pFileMetadataObjects, BSTR *pFormulae, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	if ( pHandlingCode == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}
