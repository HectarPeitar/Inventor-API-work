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
//- AddInApplication
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
struct _INVCOMMANDBAR_ENTRY {
	UINT nDisplayNameID ;
	bool bVisible ;
	CommandBarTypeEnum commandBarType ;
	LPCTSTR pszCommandBarInternalName ;
	CComPtr<CommandBar> commandBar ;
} ;

#pragma section("INVCOMMANDBAR$__a", read, shared)
#pragma section("INVCOMMANDBAR$__z", read, shared)
#pragma section("INVCOMMANDBAR$__m", read, shared)

extern "C" {
	__declspec(selectany) __declspec(allocate("INVCOMMANDBAR$__a")) _INVCOMMANDBAR_ENTRY* __pInvCmdBarMapEntryFirst =NULL ;
	__declspec(selectany) __declspec(allocate("INVCOMMANDBAR$__z")) _INVCOMMANDBAR_ENTRY* __pInvCmdBarMapEntryLast =NULL ;
}

#define INVENTOR_COMMANDBAR_ENTRY_PRAGMA(id) __pragma(comment(linker, "/include:___pInvCmdBarMap_" #id)) ;

#define INVENTOR_TOOLBAR_ENTRY_AUTO(displayName, bVisible, tbType, internalName) \
	__declspec(selectany) _INVCOMMANDBAR_ENTRY __InvCmdBarMap_##__LINE__ = { displayName, bVisible, (CommandBarTypeEnum)(tbType), internalName } ; \
	extern "C" __declspec(allocate("INVCOMMANDBAR$__m")) __declspec(selectany) _INVCOMMANDBAR_ENTRY* const __pInvCmdBarMap_##__LINE__ = &__InvCmdBarMap_##__LINE__ ; \
	INVENTOR_COMMANDBAR_ENTRY_PRAGMA(__LINE__)

#define INVENTOR_TOOLBAR(displayName, bVisible, internalName) \
	INVENTOR_TOOLBAR_ENTRY_AUTO(displayName, bVisible, kRegularCommandBar, internalName)

//-----------------------------------------------------------------------------
struct _INVCOMMAND_ENTRY ; //- Forward declaration
typedef HRESULT (_INV_CREATECMDINSTANCE) (_INVCOMMAND_ENTRY **ppEntry, CComPtr<CommandBar> &pCommandBar, const IID *piid, Application *pApplication) ;
typedef HRESULT (_INV_RELEASECMDINSTANCE) (_INVCOMMAND_ENTRY **ppEntry, Application *pApplication) ;

struct _INVCOMMAND_ENTRY {
	LPCTSTR pszCommandName ;
	LPCTSTR pszCommandInternalName ;
	UINT nDisplayNameID, nTooltipID, nDescriptionID ;
	UINT nIconID ;
	LPCTSTR pszCommandBarInternalName ;
	CommandTypesEnum commandType ;
	ButtonDisplayEnum buttonDisplayType ;
	void *pCommandHdlr ;
	_INV_CREATECMDINSTANCE *pfnCreateCmdInstance ;
	_INV_RELEASECMDINSTANCE *pfnReleaseCmdInstance ;
} ;

#pragma section("INVCOMMAND$__a", read, shared)
#pragma section("INVCOMMAND$__z", read, shared)
#pragma section("INVCOMMAND$__m", read, shared)

extern "C" {
	__declspec(selectany) __declspec(allocate("INVCOMMAND$__a")) _INVCOMMAND_ENTRY* __pInvCmdMapEntryFirst =NULL ;
	__declspec(selectany) __declspec(allocate("INVCOMMAND$__z")) _INVCOMMAND_ENTRY* __pInvCmdMapEntryLast =NULL ;
}

#define INVENTOR_COMMAND_ENTRY_PRAGMA(cmd) __pragma(comment(linker, "/include:___pInvCmdMap_" #cmd)) ;

#define INVENTOR_COMMAND_ENTRY_AUTO(cmd, displayName, iconID, tooltip, desc, cmdType, buttDisp, internalName, inCmdBar) \
	__declspec(selectany) _INVCOMMAND_ENTRY __InvCmdMap_##cmd = { _T(#cmd), internalName, displayName, tooltip, desc, iconID, inCmdBar, (CommandTypesEnum)(cmdType), (ButtonDisplayEnum)(buttDisp), NULL, cmd::CreateInstance, cmd::ReleaseInstance } ; \
	extern "C" __declspec(allocate("INVCOMMAND$__m")) __declspec(selectany) _INVCOMMAND_ENTRY* const __pInvCmdMap_##cmd = &__InvCmdMap_##cmd ; \
	INVENTOR_COMMAND_ENTRY_PRAGMA(cmd)

#define INVENTOR_COMMAND_NOICONS(cmd, displayName, tooltip, desc, cmdType, internalName, inCmdBar) \
	INVENTOR_COMMAND_ENTRY_AUTO(cmd, displayName, -1, tooltip, desc, cmdType, kDisplayTextInLearningMode, internalName, inCmdBar)

#define INVENTOR_COMMAND(cmd, displayName, iconID, tooltip, desc, cmdType, internalName, inCmdBar) \
	INVENTOR_COMMAND_ENTRY_AUTO(cmd, displayName, iconID, tooltip, desc, cmdType, kDisplayTextInLearningMode, internalName, inCmdBar)

//-------------------------------------------------------------------------
template<class T>
class ATL_NO_VTABLE CApplicationAddInCommandHandler : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispEventImpl<0, T, &DIID_ButtonDefinitionSink, &LIBID_Inventor, 1, 0>
{
public:
	const IID *m_pClientIID ;
	CComPtr<Application> m_pApplication ;
	CComPtr<ButtonDefinitionObject> m_Cmd ;
	_INVCOMMAND_ENTRY **m_ppEntry ;

public:
	CApplicationAddInCommandHandler () : m_pClientIID(NULL), m_ppEntry(NULL) {}

	virtual HINSTANCE GetResourceInstance () {
		return (_AtlBaseModule.GetResourceInstance ()) ;
	}

	BEGIN_COM_MAP(T)
	END_COM_MAP()

	static HRESULT CreateInstance (_INVCOMMAND_ENTRY **ppEntry, CComPtr<CommandBar> &pCommandBar, const IID *piid, Application *pApplication =NULL) {
		ATLASSERT( ppEntry != NULL ) ;
		HRESULT hr =CComObject<T>::CreateInstance ((CComObject<T> **)&((*ppEntry)->pCommandHdlr)) ;
		(*((CComObject<T> **)&((*ppEntry)->pCommandHdlr)))->AddRef () ;
		(*((CComObject<T> **)&((*ppEntry)->pCommandHdlr)))->m_pClientIID =piid ;
		(*((CComObject<T> **)&((*ppEntry)->pCommandHdlr)))->m_pApplication =pApplication ;
		(*((CComObject<T> **)&((*ppEntry)->pCommandHdlr)))->m_ppEntry =ppEntry ;
		(*((CComObject<T> **)&((*ppEntry)->pCommandHdlr)))->CreateCommand (pCommandBar) ;
		return (hr) ;
	}

	static HRESULT ReleaseInstance (_INVCOMMAND_ENTRY **ppEntry, Application *pApplication =NULL) {
		ATLASSERT( ppEntry != NULL ) ;
		ATLASSERT ( (*((CComObject<T> **)&((*ppEntry)->pCommandHdlr))) != NULL ) ;
		(*((CComObject<T> **)&((*ppEntry)->pCommandHdlr)))->m_pApplication.Release () ;
		(*((CComObject<T> **)&((*ppEntry)->pCommandHdlr)))->RemoveCommand () ;
		(*((CComObject<T> **)&((*ppEntry)->pCommandHdlr)))->Release () ;
		(*((CComObject<T> **)&((*ppEntry)->pCommandHdlr))) =NULL ;
		return (S_OK) ;
	}

protected:
	CComVariant GetSharedIcon (UINT nID, short width, short height) {
		if ( nID != -1 ) {
			PICTDESC pdesc ;
			pdesc.cbSizeofstruct =sizeof (pdesc) ;
			pdesc.picType =PICTYPE_ICON ;
			pdesc.icon.hicon =(HICON)::LoadImage (GetResourceInstance (), MAKEINTRESOURCE(nID), IMAGE_ICON, width, height, LR_LOADTRANSPARENT | LR_SHARED) ;
			CComPtr<IPictureDisp> pPictureDisp ;
			HRESULT hr =::OleCreatePictureIndirect (&pdesc, IID_IPictureDisp, FALSE, (LPVOID *)&pPictureDisp) ;
			ATLASSERT( SUCCEEDED( hr ) ) ;
			return (CComVariant (pPictureDisp)) ;
		}
		return (vtMissing) ;
	}

	virtual bool CreateCommand (CComPtr<CommandBar> &pCommandBar) {
		HRESULT hr ;
		CComPtr<CommandManager> pCommandMgr ;
		//hr =m_pApplication->get_CommandManager (&pCommandMgr) ;
		hr =_com_dispatch_raw_method (m_pApplication, 0x300012d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&pCommandMgr, NULL) ;
		ATLASSERT( SUCCEEDED( hr ) ) ;
		CComPtr<ControlDefinitions> pControlDefs ;
		//hr =pCommandMgr->get_ControlDefinitions (&pControlDefs) ;
		hr =_com_dispatch_raw_method (pCommandMgr, 0x300331d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&pControlDefs, NULL) ;
		ATLASSERT( SUCCEEDED( hr ) ) ;
		LPOLESTR ppsz =NULL ;
		hr =::StringFromCLSID (*m_pClientIID, &ppsz) ;
		ATLASSERT( SUCCEEDED( hr ) ) ;
		BSTR bstrDisplayText =NULL, bstrDescriptionText =NULL, bstrTooltipText =NULL ;
		CComBSTR::LoadStringResource (GetResourceInstance (), (*m_ppEntry)->nDisplayNameID, bstrDisplayText) ;
		CComBSTR::LoadStringResource (GetResourceInstance (), (*m_ppEntry)->nDescriptionID, bstrDescriptionText) ;
		CComBSTR::LoadStringResource (GetResourceInstance (), (*m_ppEntry)->nTooltipID, bstrTooltipText) ;
		CComVariant varName(ppsz);
		//hr =pControlDefs->AddButtonDefinition (
		//	bstrDisplayText, CComBSTR ((*ppEntry)->pszCommandInternalName),
		//	(*m_ppEntry)->commandType, CComVariant(ppsz),
		//	bstrDescriptionText, bstrTooltipText,
		//	vtMissing, vtMissing,
		//	(*m_ppEntry)->buttonDisplayType,
		//	&m_Cmd
		//) ;
		hr =_com_dispatch_raw_method (
			pControlDefs, 0x3009b02, DISPATCH_METHOD, VT_DISPATCH, (void *)&m_Cmd, 
			L"\x0008\x0008\x0003\x000c\x0008\x0008\x000c\x000c\x0003",
			bstrDisplayText, CComBSTR ((*m_ppEntry)->pszCommandInternalName),
			(*m_ppEntry)->commandType, &varName,
			bstrDescriptionText, bstrTooltipText,
			&GetSharedIcon ((*m_ppEntry)->nIconID, 15, 14), &GetSharedIcon ((*m_ppEntry)->nIconID, 23, 21),
			(*m_ppEntry)->buttonDisplayType
		) ;
		ATLASSERT( SUCCEEDED( hr ) ) ;
		::SysFreeString (bstrDisplayText) ;
		::SysFreeString (bstrDescriptionText) ;
		::SysFreeString (bstrTooltipText) ;
		::CoTaskMemFree (ppsz) ;

		hr =this->DispEventAdvise (m_Cmd) ;
		ATLASSERT( SUCCEEDED( hr ) ) ;

		if ( pCommandBar != NULL ) {
			CComPtr<CommandBarControls> pCmdBarControls ;
			//hr =pCommandBar->get_Controls (&pCmdBarControls) ;
			hr =_com_dispatch_raw_method (pCommandBar, 0x3008202, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&pCmdBarControls, NULL) ;
			ATLASSERT( SUCCEEDED( hr ) ) ;
			CComPtr<CommandBarControl> pCmdBarCtrl ;
			//hr =pCmdBarControls->AddButton (m_Cmd, 0, &pCmdBarCtrl) ;
            auto cmdArg = static_cast<IDispatch*>(static_cast<ButtonDefinitionObject*>(m_Cmd));
            hr = _com_dispatch_raw_method(pCmdBarControls, 0x3008303, DISPATCH_METHOD, VT_DISPATCH, (void*)&pCmdBarCtrl, L"\x0009\x0003", cmdArg, 0);
			ATLASSERT( SUCCEEDED( hr ) ) ;
		} else {
			//hr =m_Cmd->AutoAddToGUI () ;
			hr =_com_dispatch_raw_method (m_Cmd, 0x3009a0e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL) ;
			ATLASSERT( SUCCEEDED( hr ) ) ;
		}
		return (true) ;
	}

	virtual bool RemoveCommand () {
		HRESULT hr =this->DispEventUnadvise (m_Cmd) ;
		ATLASSERT( SUCCEEDED( hr ) ) ;
		//- From Inventor 10 onwards, AddIns no longer need to delete the ButtonDefinitionObjects 
		//- (in the Deactivate method) which have been created in the Activate method. The 
		//- Inventor framework is supposed to clean up the orphaned buttons in case the AddIn
		//- is unloaded.
		//hr =m_Cmd->Delete () ;
		//hr =_com_dispatch_raw_method (m_Cmd, 0x3009a03, DISPATCH_METHOD, VT_EMPTY, NULL, NULL) ;
		//ATLASSERT( SUCCEEDED( hr ) ) ;
		m_Cmd.Release () ;
		m_Cmd =NULL ;
		return (true) ;
	}

public:
	BEGIN_SINK_MAP(T)
		SINK_ENTRY_EX (0, DIID_ButtonDefinitionSink, ButtonDefinitionSink_OnExecuteMeth, OnExecute)
	END_SINK_MAP()

	//- ButtonDefinitionSink
	STDMETHOD(OnExecute) (NameValueMap *Context) =0 ;
} ;

//-------------------------------------------------------------------------
template<const IID *piid>
class CCommonAddInServerImpl {

protected:
	CCommonAddInServerImpl () {}

public:
	virtual HINSTANCE GetResourceInstance () {
		return (_AtlBaseModule.GetResourceInstance ()) ;
	}

public:
	template<class T>
	CComObject<T> *GetCommand (LPCTSTR name) {
		_INVCOMMAND_ENTRY **ppInvCmdMapEntryFirst =&__pInvCmdMapEntryFirst + 1 ;
		_INVCOMMAND_ENTRY **ppInvCmdMapEntryLast =&__pInvCmdMapEntryLast ;
		TCHAR buffer [256] ;
		for ( _INVCOMMAND_ENTRY **ppEntry =ppInvCmdMapEntryFirst ; ppEntry < ppInvCmdMapEntryLast ; ppEntry++ ) {
			if (   *ppEntry != NULL
				&& (*ppEntry)->pCommandHdlr != NULL
				&& _tcscmp ((*ppEntry)->pszCommandName, name) == 0
				) {
					return ((CComObject<T> *)(*ppEntry)->pCommandHdlr) ;
				}
		}
		return (NULL) ;
	}

	CComPtr<CommandBar> GetCommandBar (LPCTSTR name) {
		_INVCOMMANDBAR_ENTRY **ppInvCmdBarMapEntryFirst =&__pInvCmdBarMapEntryFirst + 1 ;
		_INVCOMMANDBAR_ENTRY **ppInvCmdBarMapEntryLast =&__pInvCmdBarMapEntryLast ;
		for ( _INVCOMMANDBAR_ENTRY **ppEntry =ppInvCmdBarMapEntryFirst ; ppEntry < ppInvCmdBarMapEntryLast ; ppEntry++ ) {
			if (   *ppEntry != NULL
				&& (*ppEntry)->pszCommandBarInternalName != NULL
				&& _tcscmp ((*ppEntry)->pszCommandBarInternalName, name) == 0
				) {
					return ((*ppEntry)->commandBar) ;
				}
		}
		return (NULL) ;
	}

protected:
	STDMETHOD(Activate) (Application *pApp, VARIANT_BOOL FirstTime) {
		//- Create/Connect Command Bars
		CComPtr<UserInterfaceManager> pUserInterfaceMgr ;
		//HRESULT =hr =m_pApplication->get_UserInterfaceManager (&pUserInterfaceMgr) ;
		HRESULT hr =_com_dispatch_raw_method (pApp, 0x3000156, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&pUserInterfaceMgr, NULL) ;
		ATLASSERT( SUCCEEDED( hr ) ) ;
		CComPtr<CommandBars> pCmdBars ;
		//hr =pUserInterfaceMgr->get_CommandBars (&pCmdBars) ;
		hr =_com_dispatch_raw_method (pUserInterfaceMgr, 0x300dd01, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&pCmdBars, NULL) ;
		ATLASSERT( SUCCEEDED( hr ) ) ;
		LPOLESTR ppsz =NULL ;
		::StringFromCLSID (*piid, &ppsz) ;
		_INVCOMMANDBAR_ENTRY **ppInvCmdBarMapEntryFirst =&__pInvCmdBarMapEntryFirst + 1 ;
		_INVCOMMANDBAR_ENTRY **ppInvCmdBarMapEntryLast =&__pInvCmdBarMapEntryLast ;
		for ( _INVCOMMANDBAR_ENTRY **ppEntry =ppInvCmdBarMapEntryFirst ; ppEntry < ppInvCmdBarMapEntryLast ; ppEntry++ ) {
			if ( *ppEntry != NULL ) {
				if ( FirstTime == VARIANT_FALSE ) {
					//pCmdBars->get_Item (CComVariant ((*ppEntry)->pszCommandBarInternalName), &((*ppEntry)->commandBar)) ;
					CComVariant comVar((*ppEntry)->pszCommandBarInternalName);
					hr =_com_dispatch_raw_method (pCmdBars, 0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&((*ppEntry)->commandBar), L"\x000c", &comVar) ;
				}
				if ( FirstTime == VARIANT_TRUE || (*ppEntry)->commandBar == NULL ) {
					BSTR bstrDisplayName =NULL ;
					CComBSTR::LoadStringResource (GetResourceInstance (), (*ppEntry)->nDisplayNameID, bstrDisplayName) ;
					//hr =pCmdBars->Add (bstrDisplayName, CComBSTR ((*ppEntry)->pszCommandBarInternalName), (*ppEntry)->commandBarType, CComVariant (ppsz), &((*ppEntry)->commandBar)) ;
					CComVariant comVar(ppsz);
                    CComBSTR combInternalName((*ppEntry)->pszCommandBarInternalName);
					hr =_com_dispatch_raw_method (pCmdBars, 0x3008101, DISPATCH_METHOD, VT_DISPATCH, (void *)&((*ppEntry)->commandBar), L"\x0008\x0008\x0003\x080c", bstrDisplayName, static_cast<BSTR>(combInternalName), (*ppEntry)->commandBarType, &comVar) ;
					::SysFreeString (bstrDisplayName) ;
					ATLASSERT( SUCCEEDED( hr ) ) ;
					//hr =(*ppEntry)->commandBar->put_Visible ((*ppEntry)->bVisible ? VARIANT_TRUE : VARIANT_FALSE) ;
					hr =_com_dispatch_raw_method ((*ppEntry)->commandBar, 0x300820b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, L"\x000b", (*ppEntry)->bVisible ? VARIANT_TRUE : VARIANT_FALSE) ;
					ATLASSERT( SUCCEEDED( hr ) ) ;
				}
			}
		}
		::CoTaskMemFree (ppsz) ;
		//- Register Commands
		_INVCOMMAND_ENTRY **ppInvCmdMapEntryFirst =&__pInvCmdMapEntryFirst + 1 ;
		_INVCOMMAND_ENTRY **ppInvCmdMapEntryLast =&__pInvCmdMapEntryLast ;
		for ( _INVCOMMAND_ENTRY **ppEntry =ppInvCmdMapEntryFirst ; ppEntry < ppInvCmdMapEntryLast ; ppEntry++ ) {
			if (   *ppEntry != NULL
				&& (*ppEntry)->pfnCreateCmdInstance != NULL
				) {
					CComPtr<CommandBar> pCommandBar ;
					if ( (*ppEntry)->pszCommandBarInternalName != NULL )
						pCommandBar =GetCommandBar ((*ppEntry)->pszCommandBarInternalName) ;
					hr =(*ppEntry)->pfnCreateCmdInstance (ppEntry, pCommandBar, piid, pApp) ;
					ATLASSERT( SUCCEEDED( hr ) ) ;
				}
		}
		return (hr) ;
	}

	STDMETHOD(Deactivate) (Application *pApp) {
		HRESULT hr =S_OK ;
		//- Disconnect Command Bars
		_INVCOMMANDBAR_ENTRY **ppInvCmdBarMapEntryFirst =&__pInvCmdBarMapEntryFirst + 1 ;
		_INVCOMMANDBAR_ENTRY **ppInvCmdBarMapEntryLast =&__pInvCmdBarMapEntryLast ;
		for ( _INVCOMMANDBAR_ENTRY **ppEntry =ppInvCmdBarMapEntryFirst ; ppEntry < ppInvCmdBarMapEntryLast ; ppEntry++ ) {
			if ( *ppEntry != NULL )
				(*ppEntry)->commandBar =NULL ;
		}
		//- Unregister Commands
		_INVCOMMAND_ENTRY **ppInvCmdMapEntryFirst =&__pInvCmdMapEntryFirst + 1 ;
		_INVCOMMAND_ENTRY **ppInvCmdMapEntryLast =&__pInvCmdMapEntryLast ;
		for ( _INVCOMMAND_ENTRY **ppEntry =ppInvCmdMapEntryFirst ; ppEntry < ppInvCmdMapEntryLast ; ppEntry++ ) {
			if ( *ppEntry != NULL && (*ppEntry)->pfnReleaseCmdInstance != NULL ) {
				hr =(*ppEntry)->pfnReleaseCmdInstance (ppEntry, pApp) ;
				ATLASSERT( SUCCEEDED( hr ) ) ;
			}
		}
		return (hr) ;
	}

} ;

#pragma warning (push)
#pragma warning (disable : 4265)  // disable the missing virtual dtor warning
//-------------------------------------------------------------------------
template<
	class className,
	class intName,
	const IID *piid =&__uuidof (intName),
	const GUID *plibid =&CAtlModule::m_libid,
	WORD wMajor =1, WORD wMinor =0,
	class tihclass =CComTypeInfoHolder
>
class ATL_NO_VTABLE CApplicationAddInServerImpl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<className, piid>,
	public IDispatchImpl<intName, piid, plibid, wMajor, wMinor, tihclass>,
	public CCommonAddInServerImpl<piid>
{
public:
	CComPtr<Application> m_pApplication ;
	CComPtr<ApplicationAddInSite> m_pAddInSite ;

public:
    CApplicationAddInServerImpl () : m_szLicense(NULL) {}
	CApplicationAddInServerImpl (LPCTSTR szLicense)
	{
		const size_t len = _tcslen(szLicense) + 1;
		m_szLicense = new TCHAR[len];
		_tcscpy_s(m_szLicense, len, szLicense);
	}
    ~CApplicationAddInServerImpl()
    {
    }

	STDMETHOD(OnActivate) (VARIANT_BOOL FirstTime) =0 ;
	STDMETHOD(OnDeactivate) () =0 ;

public:
	//- ApplicationAddInServer
	STDMETHOD(Activate) (IDispatch *pDisp, VARIANT_BOOL FirstTime) {
#ifdef _AFXDLL
		AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
#endif
		if ( pDisp == NULL )
			return (E_INVALIDARG) ;
		HRESULT hr =pDisp->QueryInterface (__uuidof (m_pAddInSite), reinterpret_cast<void **>(&m_pAddInSite)) ;
		ATLASSERT( SUCCEEDED( hr ) ) ;
		if ( FAILED( hr ) )
			return (hr) ;

		//- Get the application object.
		//hr =m_pAddInSite->get_Application (&m_pApplication) ;
		hr =_com_dispatch_raw_method (pDisp, 0x3001401, DISPATCH_PROPERTYGET, VT_DISPATCH, (void *)&m_pApplication, NULL) ;
		ATLASSERT( SUCCEEDED( hr ) ) ;
		if ( FAILED( hr ) )
			return (hr) ;
		//- Create/Connect Command Bars and Commands
		CCommonAddInServerImpl<piid>::Activate (m_pApplication, FirstTime) ;
		//- Notify Application Object
		hr =OnActivate (FirstTime) ;
		return (hr) ;
	}

	STDMETHOD(Deactivate) () {
#ifdef _AFXDLL
		AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
#endif
		//- Disconnect Command Bars and Commands
		CCommonAddInServerImpl<piid>::Deactivate (m_pApplication) ;
		//- Notify Application Object
		HRESULT hr =OnDeactivate () ;
		//- Terminate server
		m_pAddInSite.Release () ;
		m_pApplication.Release () ;
		return (hr) ;
	}

	STDMETHOD(ExecuteCommand) (long /*CommandID*/) {
		//- Deprecated since R6
		ATLASSERT( 0 ) ;
		return (E_NOTIMPL) ;
	}

	STDMETHOD(get_Automation) (IDispatch **ppResult) {
		if ( ppResult == NULL )
			return (E_POINTER) ;
		*ppResult =NULL ;
		return (E_NOTIMPL) ;
	}
private:
	LPTSTR m_szLicense;
} ;
#pragma warning (pop)  // re-enable warning 4265 for missing virtual dtor

//-----------------------------------------------------------------------------
#pragma warning (push)
#pragma warning (disable : 4265)  // disable the missing virtual dtor warning
    template<
	class className,
	class intName,
	const IID *piid =&__uuidof (intName),
	const GUID *plibid =&CAtlModule::m_libid,
	WORD wMajor =1, WORD wMinor =0,
	class tihclass =CComTypeInfoHolder
>
class ATL_NO_VTABLE CTranslatorAddInServerImpl :
	public CApplicationAddInServerImpl<className, intName, piid, plibid, wMajor, wMinor, tihclass>
{
public:
	CTranslatorAddInServerImpl () {}
    CTranslatorAddInServerImpl(LPCTSTR szLicense) : CApplicationAddInServerImpl<className, intName, piid, plibid, wMajor, wMinor, tihclass>(szLicense){}

	//- TranslatorAddInServer
	STDMETHOD(get_HasOpenOptions) (IDispatch *pSourceData, IDispatch *pContext, IDispatch *pDefaultOptions, VARIANT_BOOL *pResult) =0 ;
	//- DataMedium *pSourceData, TranslationContext *pContext, NameValueMap *pDefaultOptions

	STDMETHOD(ShowOpenOptions) (IDispatch *pSourceData, IDispatch *pContext, IDispatch *pChosenOptions) =0 ;
	//- DataMedium *pSourceData, TranslationContext *pContext, NameValueMap *pChosenOptions

	STDMETHOD(Open) (IDispatch *pSourceData, IDispatch * pContext, IDispatch *pOptions, IDispatch **ppTargetObject) =0 ;
	//- DataMedium *pSourceData, TranslationContext *pContext, NameValueMap *pOptions
	
	STDMETHOD(get_HasSaveCopyAsOptions) (IDispatch *pSourceObject, IDispatch *pContext, IDispatch *pDefaultOptions, VARIANT_BOOL *pResult) =0 ;
	//- TranslationContext *pContext, NameValueMap *pDefaultOptions
	
	STDMETHOD(ShowSaveCopyAsOptions) (IDispatch *pSourceObject, IDispatch *pContext, IDispatch *pChosenOptions) =0 ;
	//- TranslationContext *pContext, NameValueMap *pDefaultOptions
	
	STDMETHOD(SaveCopyAs) (IDispatch *pSourceObject, IDispatch *pContext, IDispatch *pOptions, IDispatch *pTargetData) =0 ;
	//- TranslationContext *pContext, NameValueMap *pOptions, DataMedium *pTargetData
	
	STDMETHOD(GetThumbnail) (IDispatch *pSourceData, VARIANT *pResult) =0 ;
	//- DataMedium *pSourceData
	
};
#pragma warning (pop)  // re-enable warning 4265 for missing virtual dtor

//-----------------------------------------------------------------------------
template<
	class className,
	class intName,
	const IID *piid =&__uuidof (intName)
>
class ATL_NO_VTABLE CRxApplicationAddInServerImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<className, piid>,
	public intName,
	public IRxApplicationAddInServer,
	public CCommonAddInServerImpl<piid>
{
public:
	CComPtr<Application> m_pApplication ;
	CComPtr<IRxApplicationAddInSite> m_pAddInSite ;

public:
	CRxApplicationAddInServerImpl () {}

	STDMETHOD(OnActivate) (VARIANT_BOOL FirstTime) =0 ;
	STDMETHOD(OnDeactivate) () =0 ;

public:
	//- IRxApplicationAddInServer
	STDMETHOD(Activate) (IRxApplicationAddInSite *pAddInSite, BooleanType FirstTime) {
#ifdef _AFXDLL
		AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
#endif
		if ( pAddInSite == NULL )
			return E_INVALIDARG ;
		m_pAddInSite =pAddInSite ;
		//- Get the application object.
		CComPtr<IUnknown> pAppUnk ;
		HRESULT hr =m_pAddInSite->get_Application (&pAppUnk) ;
		ATLASSERT( SUCCEEDED( hr ) ) ;
		if ( FAILED( hr ) )
			return (hr) ;
		hr =pAppUnk->QueryInterface (&m_pApplication) ;
		ATLASSERT( SUCCEEDED( hr ) ) ;
		if ( FAILED( hr ) )
			return (hr) ;
		//- Create/Connect Command Bars and Commands
		CCommonAddInServerImpl<piid>::Activate (m_pApplication, FirstTime) ;
		//- Notify Application Object
		hr =OnActivate (FirstTime) ;
		return (S_OK) ;
	}

	STDMETHOD(Deactivate) () {
#ifdef _AFXDLL
		AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;
#endif
		//- Disconnect Command Bars and Commands
		CCommonAddInServerImpl<piid>::Deactivate (m_pApplication) ;
		//- Notify Application Object
		HRESULT hr =OnDeactivate () ;
		//- Terminate server
		m_pAddInSite.Release () ;
		m_pApplication.Release () ;
		return (S_OK) ;
	}

	STDMETHOD(ExecuteCommand) (LONG CommandID) {
		//- Deprecated since R6
		ATLASSERT( 0 ) ;
		return (E_NOTIMPL) ;
	}

	STDMETHOD(get_Automation) (IUnknown **ppResult) {
		if ( ppResult == NULL )
			return (E_POINTER) ;
		*ppResult =NULL ;
		return (E_NOTIMPL) ;
	}

} ;

//-----------------------------------------------------------------------------
template<
	class className,
	class intName,
	const IID *piid =&__uuidof (intName)
>
class ATL_NO_VTABLE CRxTranslatorAddInServerImpl:
	public CRxApplicationAddInServerImpl<className, intName, piid>
{
public:
	CRxTranslatorAddInServerImpl () {}

	//- IRxTranslatorAddInServer
	STDMETHOD(get_HasOpenOptions) (DataMedium *pSourceData, TranslationContext *pContext, NameValueMap *pDefaultOptions, char *pResult) =0 ;
	STDMETHOD(ShowOpenOptions) (DataMedium *pSourceData, TranslationContext *pContext, NameValueMap *pChosenOptions) =0 ;
	STDMETHOD(Open) (DataMedium *pSourceData, TranslationContext *pContext, NameValueMap *pOptions, IUnknown **ppTargetObject) =0 ;
	STDMETHOD(get_HasSaveCopyAsOptions) (IUnknown *pSourceObject, TranslationContext *pContext, NameValueMap *pDefaultOptions, char *pResult) =0 ;
	STDMETHOD(ShowSaveCopyAsOptions) (IUnknown* pSourceObject, TranslationContext *pContext, NameValueMap *pChosenOptions) =0 ;
	STDMETHOD(SaveCopyAs) (IUnknown *pSourceObject, TranslationContext *pContext, NameValueMap *pOptions, DataMedium *pTargetData) =0 ;
	//- IRxTranslatorAddInServer2
	STDMETHOD(GetThumbnail) (DataMedium *pSourceData, VARIANT *pResult) =0 ;

} ;
