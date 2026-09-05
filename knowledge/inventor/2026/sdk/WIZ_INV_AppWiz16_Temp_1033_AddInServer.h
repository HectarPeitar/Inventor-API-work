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
//----- [!output ADDIN_NAME].h : Declaration of the C[!output ADDIN_NAME]
//-----------------------------------------------------------------------------
#pragma once

#include "resource.h"

[!if USE_VTABLE]
//-----------------------------------------------------------------------------
class ATL_NO_VTABLE C[!output ADDIN_NAME] : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<C[!output ADDIN_NAME], &CLSID_[!output ADDIN_NAME]>,
	public I[!output ADDIN_NAME],
[!if ADDIN_APPTYPE]
	public IRxApplicationAddInServer
[!else]
	public IRxTranslatorAddInServer2
[!endif]
{
public:
	CComPtr<Application> m_pApplication ;
	CComPtr<IRxApplicationAddInSite> m_pAddInSite ;

public:
	C[!output ADDIN_NAME] () {}

	DECLARE_REGISTRY_RESOURCEID(IDR_[!output ADDIN_NAME])
	DECLARE_NOT_AGGREGATABLE(C[!output ADDIN_NAME])
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(C[!output ADDIN_NAME])
		COM_INTERFACE_ENTRY(I[!output ADDIN_NAME])
[!if ADDIN_APPTYPE]
		COM_INTERFACE_ENTRY(IRxApplicationAddInServer)
[!else]
		COM_INTERFACE_ENTRY(IRxTranslatorAddInServer2)
[!endif]
	END_COM_MAP()

public:
[!if ADDIN_APPTYPE]
	//----- IRxApplicationAddInServer
[!else]
	//----- IRxTranslatorAddInServer
[!endif]
	STDMETHOD(Activate)(IRxApplicationAddInSite * pAddInSite, BooleanType FirstTime);
	STDMETHOD(Deactivate)();
	STDMETHOD(ExecuteCommand)(LONG CommandID);
	STDMETHOD(get_Automation)(IUnknown * * ppResult) ;
[!if !ADDIN_APPTYPE]
	STDMETHOD(get_HasOpenOptions)(DataMedium * pSourceData, TranslationContext * pContext, NameValueMap * pDefaultOptions, char * pResult);
	STDMETHOD(ShowOpenOptions)(DataMedium * pSourceData, TranslationContext * pContext, NameValueMap * pChosenOptions);
	STDMETHOD(Open)(DataMedium * pSourceData, TranslationContext * pContext, NameValueMap * pOptions, IUnknown * * ppTargetObject);
	STDMETHOD(get_HasSaveCopyAsOptions)(IUnknown * pSourceObject, TranslationContext * pContext, NameValueMap * pDefaultOptions, char * pResult);
	STDMETHOD(ShowSaveCopyAsOptions)(IUnknown * pSourceObject, TranslationContext * pContext, NameValueMap * pChosenOptions);
	STDMETHOD(SaveCopyAs)(IUnknown * pSourceObject, TranslationContext * pContext, NameValueMap * pOptions, DataMedium * pTargetData);
	//------ IRxTranslatorAddInServer2
	STDMETHOD(GetThumbnail)(DataMedium * pSourceData, VARIANT * pResult);
[!endif]
} ;
[!else]
//-----------------------------------------------------------------------------
class ATL_NO_VTABLE C[!output ADDIN_NAME] : 
[!if ADDIN_APPTYPE]
	public CApplicationAddInServerImpl<C[!output ADDIN_NAME], I[!output ADDIN_NAME]>
[!else]
	public CTranslatorAddInServerImpl<C[!output ADDIN_NAME], I[!output ADDIN_NAME]>
[!endif]
{

public:
	C[!output ADDIN_NAME] () {}

	DECLARE_REGISTRY_RESOURCEID(IDR_[!output ADDIN_NAME])
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(C[!output ADDIN_NAME])
		COM_INTERFACE_ENTRY(I[!output ADDIN_NAME])
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

public:
	//- CApplicationAddInServerImpl
	STDMETHOD(OnActivate) (VARIANT_BOOL FirstTime) ;
	STDMETHOD(OnDeactivate) () ;

[!if !ADDIN_APPTYPE]
	//- TranslatorAddInServer
	STDMETHOD(get_HasOpenOptions) (IDispatch *pSourceData, IDispatch *pContext, IDispatch *pDefaultOptions, VARIANT_BOOL *pResult) ;
	//- DataMedium *pSourceData, TranslationContext *pContext, NameValueMap *pDefaultOptions

	STDMETHOD(ShowOpenOptions) (IDispatch *pSourceData, IDispatch *pContext, IDispatch *pChosenOptions) ;
	//- DataMedium *pSourceData, TranslationContext *pContext, NameValueMap *pChosenOptions

	STDMETHOD(Open) (IDispatch *pSourceData, IDispatch * pContext, IDispatch *pOptions, IDispatch **ppTargetObject) ;
	//- DataMedium *pSourceData, TranslationContext *pContext, NameValueMap *pOptions

	STDMETHOD(get_HasSaveCopyAsOptions) (IDispatch *pSourceObject, IDispatch *pContext, IDispatch *pDefaultOptions, VARIANT_BOOL *pResult) ;
	//- TranslationContext *pContext, NameValueMap *pDefaultOptions

	STDMETHOD(ShowSaveCopyAsOptions) (IDispatch *pSourceObject, IDispatch *pContext, IDispatch *pChosenOptions) ;
	//- TranslationContext *pContext, NameValueMap *pDefaultOptions

	STDMETHOD(SaveCopyAs) (IDispatch *pSourceObject, IDispatch *pContext, IDispatch *pOptions, IDispatch *pTargetData) ;
	//- TranslationContext *pContext, NameValueMap *pOptions, DataMedium *pTargetData

	STDMETHOD(GetThumbnail) (IDispatch *pSourceData, VARIANT *pResult) ;
	//- DataMedium *pSourceData
[!endif]
} ;
[!endif]

//-----------------------------------------------------------------------------
OBJECT_ENTRY_AUTO(__uuidof([!output ADDIN_NAME]), C[!output ADDIN_NAME])
