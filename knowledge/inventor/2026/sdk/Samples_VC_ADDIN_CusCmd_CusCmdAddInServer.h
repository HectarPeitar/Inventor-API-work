//-----------------------------------------------------------------------------
//----- CustomCommandAddInServer.h : Declaration of the CCustomCommandAddInServer
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"

#include "RackFaceCmd.h"

//-----------------------------------------------------------------------------
class ATL_NO_VTABLE CCustomCommandAddInServer : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCustomCommandAddInServer, &CLSID_CustomCommandAddInServer>,
	public IDispatchImpl<ICustomCommandAddInServer, &IID_ICustomCommandAddInServer, &LIBID_CustomCommandLib>,
	public IDispEventImpl<1, CCustomCommandAddInServer, &DIID_UserInterfaceEventsSink, &LIBID_Inventor, 1, 0>
{
	
public:
	CCustomCommandAddInServer ()
	{
		m_pApplication = NULL;
		m_pAddInSite = NULL;

		m_pUserInterfaceEvtsObj = NULL;

		m_pRackFaceCmd = NULL;

	}

	DECLARE_REGISTRY_RESOURCEID(IDR_CustomCommandAddInServer)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CCustomCommandAddInServer)
		COM_INTERFACE_ENTRY(ICustomCommandAddInServer)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	BEGIN_SINK_MAP(CCustomCommandAddInServer)
		SINK_ENTRY_EX (1, DIID_UserInterfaceEventsSink, UserInterfaceEventsSink_OnResetCommandBarsMeth, OnResetCommandBars)
		SINK_ENTRY_EX (1, DIID_UserInterfaceEventsSink, UserInterfaceEventsSink_OnEnvironmentChange, OnEnvironmentChange)
		SINK_ENTRY_EX (1, DIID_UserInterfaceEventsSink, UserInterfaceEventsSink_OnResetRibbonInterfaceMeth, OnResetRibbonInterface)
	END_SINK_MAP()

private:
    CComPtr<Application> m_pApplication;
	CComPtr<ApplicationAddInSite> m_pAddInSite;

	//user interface event
	CComPtr<UserInterfaceEventsObject> m_pUserInterfaceEvtsObj;

	//commands
	//Rack Face command
	CComObject<CRackFaceCmd>* m_pRackFaceCmd;

public:
	//----- ApplicationAddInServer
	STDMETHOD(Activate)(IDispatch * pDisp, VARIANT_BOOL FirstTime);
	STDMETHOD(Deactivate)();
	STDMETHOD(ExecuteCommand)(long CommandID);
	STDMETHOD(get_Automation)(IDispatch * * ppResult);

	//----- UserInterfaceEventsSink 
	STDMETHOD(OnResetCommandBars) (ObjectsEnumerator* pCommandBars, NameValueMap* pContext);
	STDMETHOD(OnEnvironmentChange) (Environment* pEnvironment, EnvironmentStateEnum EnvironmentState, EventTimingEnum BeforeOrAfter, NameValueMap* pContext, HandlingCodeEnum* HandlingCode);
	STDMETHOD(OnResetRibbonInterface) (NameValueMap* pContext);
} ;
