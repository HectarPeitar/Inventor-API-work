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

// [!output HEADER_FILE] : Declaration of the [!output CLASS_NAME]

#pragma once
#include "resource.h"       // main symbols

[!if !ATTRIBUTED]
#include "[!output PROJECT_NAME].h"
[!if CONNECTION_POINTS]
#include "_[!output INTERFACE_NAME]Events_CP.h"
[!endif]
[!endif]

[!if ATTRIBUTED]

// [!output INTERFACE_NAME]
[
	object,
	uuid("[!output INTERFACE_IID]"),
[!if INTERFACE_DUAL]	dual,[!endif]
[!if AUTOMATION]	oleautomation,[!endif]
[!if INTERFACE_DUAL][!if AUTOMATION]	nonextensible,[!endif][!endif]
	helpstring("[!output INTERFACE_NAME] Interface"),
	pointer_default(unique)
]
__interface [!output INTERFACE_NAME] : [!if INTERFACE_DUAL]IDispatch[!else]IUnknown[!endif]

{
};

[!if CONNECTION_POINTS]

// _[!output INTERFACE_NAME]Events
[
	dispinterface,
	uuid("[!output CONNECTION_POINT_IID]"),
	helpstring("_[!output INTERFACE_NAME]Events Interface")
]
__interface _[!output INTERFACE_NAME]Events
{
};
[!endif]
[!endif]


// [!output CLASS_NAME]

[!if ATTRIBUTED]
[
	coclass,
[!if THREADING_SINGLE]
	threading("single"),
[!endif]
[!if THREADING_APARTMENT]
	threading("apartment"),
[!endif]
[!if THREADING_BOTH]
	threading("both"),
[!endif]
[!if THREADING_FREE]
	threading("free"),
[!endif]
[!if THREADING_NEUTRAL]
	threading("neutral"),
[!endif]
[!if SUPPORT_ERROR_INFO]
	support_error_info("[!output INTERFACE_NAME]"),
[!endif]
[!if CONNECTION_POINTS]
	event_source("com"),
[!endif]
[!if AGGREGATION_NO]
	aggregatable("never"),
[!endif]
[!if AGGREGATION_ONLY]
	aggregatable("always"),
[!endif]
	vi_progid("[!output VERSION_INDEPENDENT_PROGID]"),
	progid("[!output PROGID]"),
	version(1.0),
	uuid("[!output CLSID_REGISTRY_FORMAT]"),
	helpstring("[!output TYPE_NAME]")
]
[!endif]
class ATL_NO_VTABLE [!output CLASS_NAME] : 
[!if ATTRIBUTED]
[!if OBJECT_WITH_SITE]
	public IObjectWithSiteImpl<[!output CLASS_NAME]>,
[!endif]
	public [!output INTERFACE_NAME]
[!else]
[!if THREADING_SINGLE]
	public CComObjectRootEx<CComSingleThreadModel>,
[!endif]
[!if THREADING_APARTMENT]
	public CComObjectRootEx<CComSingleThreadModel>,
[!endif]
[!if THREADING_FREE]
	public CComObjectRootEx<CComMultiThreadModel>,
[!endif]
[!if THREADING_BOTH]
	public CComObjectRootEx<CComMultiThreadModel>,
[!endif]
[!if THREADING_NEUTRAL]
	public CComObjectRootEx<CComMultiThreadModel>,
[!endif]
	public CComCoClass<[!output CLASS_NAME], &CLSID_[!output COCLASS]>,
[!if SUPPORT_ERROR_INFO]
	public ISupportErrorInfo,
[!endif]
[!if CONNECTION_POINTS]
	public IConnectionPointContainerImpl<[!output CLASS_NAME]>,
	public CProxy_[!output INTERFACE_NAME]Events<[!output CLASS_NAME]>, 
[!endif]
[!if OBJECT_WITH_SITE]
	public IObjectWithSiteImpl<[!output CLASS_NAME]>,
[!endif]
[!if INTERFACE_DUAL]
	public IDispatchImpl<[!output INTERFACE_NAME], &IID_[!output INTERFACE_NAME], &LIBID_[!output LIB_NAME], /*wMajor =*/ [!output TYPELIB_VERSION_MAJOR], /*wMinor =*/ [!output TYPELIB_VERSION_MINOR]>,
	public IDispEventImpl<0, [!output CLASS_NAME], &DIID_[!output SINKCLASSNAME], &LIBID_Inventor, 1, 0>
[!else]
	public [!output SINKCLASSNAME],
	public [!output INTERFACE_NAME]
[!endif]
[!endif]
{
public:
	[!output CLASS_NAME]()
	{
[!if FREE_THREADED_MARSHALER]
		m_pUnkMarshaler = NULL;
[!endif]
	}

[!if !ATTRIBUTED]
DECLARE_REGISTRY_RESOURCEID([!output RGS_ID])

[!if AGGREGATION_NO]
DECLARE_NOT_AGGREGATABLE([!output CLASS_NAME])
[!endif]
[!if AGGREGATION_ONLY]
DECLARE_ONLY_AGGREGATABLE([!output CLASS_NAME])
[!endif]

BEGIN_COM_MAP([!output CLASS_NAME])
	COM_INTERFACE_ENTRY([!output INTERFACE_NAME])
[!if INTERFACE_DUAL]
	COM_INTERFACE_ENTRY(IDispatch)
[!else]
	COM_INTERFACE_ENTRY([!output SINKCLASSNAME])
[!endif]
[!if SUPPORT_ERROR_INFO]
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
[!endif]
[!if CONNECTION_POINTS]
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
[!endif]
[!if OBJECT_WITH_SITE]
	COM_INTERFACE_ENTRY(IObjectWithSite)
[!endif]
[!if FREE_THREADED_MARSHALER]
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
[!endif]
END_COM_MAP()

[!if CONNECTION_POINTS]
BEGIN_CONNECTION_POINT_MAP([!output CLASS_NAME])
	CONNECTION_POINT_ENTRY(__uuidof(_[!output INTERFACE_NAME]Events))
END_CONNECTION_POINT_MAP()
[!endif]
[!if SUPPORT_ERROR_INFO]
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
[!endif]
[!else]
[!if CONNECTION_POINTS]
	__event __interface _[!output INTERFACE_NAME]Events;
[!endif]
[!endif]

[!if FREE_THREADED_MARSHALER]

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	HRESULT FinalConstruct()
	{
		return CoCreateFreeThreadedMarshaler(GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
	}

	CComPtr<IUnknown> m_pUnkMarshaler;
[!else]

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}
[!endif]

public:
	//----- MiniToolbarTextBoxSink
	STDMETHOD(OnChange) () ;
	STDMETHOD(OnEnter) () ;
	STDMETHOD(OnExit) () ;
    STDMETHOD(OnItemHoverEnd) (MiniToolbarListItem *pListItem) ;
	STDMETHOD(OnItemHoverStart) (MiniToolbarListItem *pListItem) ;
	STDMETHOD(OnItemRemove) (MiniToolbarListItem *pListItem) ;
	STDMETHOD(OnSelect) (MiniToolbarListItem *pListItem) ;
	
	BEGIN_SINK_MAP([!output CLASS_NAME])
		SINK_ENTRY_EX (0, DIID_MiniToolbarTextBoxSink, MiniToolbarTextBoxSink_OnChangeMeth, OnChange)
		SINK_ENTRY_EX (0, DIID_MiniToolbarTextBoxSink, MiniToolbarTextBoxSink_OnEnterMeth, OnEnter)
		SINK_ENTRY_EX (0, DIID_MiniToolbarTextBoxSink, MiniToolbarTextBoxSink_OnExitMeth, OnExit)
		SINK_ENTRY_EX (0, DIID_MiniToolbarTextBoxSink, MiniToolbarTextBoxSink_OnItemHoverEndMeth, OnItemHoverEnd)
		SINK_ENTRY_EX (0, DIID_MiniToolbarTextBoxSink, MiniToolbarTextBoxSink_OnItemHoverStartMeth, OnItemHoverStart)
		SINK_ENTRY_EX (0, DIID_MiniToolbarTextBoxSink, MiniToolbarTextBoxSink_OnItemRemoveMeth, OnItemRemove)
		SINK_ENTRY_EX (0, DIID_MiniToolbarTextBoxSink, MiniToolbarTextBoxSink_OnSelectMeth, OnSelect)
	END_SINK_MAP()

};

[!if !ATTRIBUTED]
OBJECT_ENTRY_AUTO(__uuidof([!output COCLASS]), [!output CLASS_NAME])
[!endif]