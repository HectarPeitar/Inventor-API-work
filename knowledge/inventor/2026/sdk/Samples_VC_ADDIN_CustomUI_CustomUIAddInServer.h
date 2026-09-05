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
//----- CustomUIAddInServer.h : Declaration of the CCustomUIAddInServer
//-----------------------------------------------------------------------------
#ifndef __CustomUIAddInServer_h_
#define __CustomUIAddInServer_h_

//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "resource.h"

//using namespace Inventor;

// forwards
//
class CCmdHandler;
class CCmdHandler1;
class CCmdHandler2;
class CCmdHandler3;
class CCmdHandler4;

class CCustomUIAddInServer;

typedef IDispEventImpl<0, CCustomUIAddInServer, &DIID_UserInputEventsSink, &LIBID_Inventor, 1, 0> UserInputEvtsSink;
typedef IDispEventImpl<1, CCustomUIAddInServer, &DIID_UserInterfaceEventsSink, &LIBID_Inventor, 1, 0> UserInterfaceEvtsSink;

//-----------------------------------------------------------------------------
class ATL_NO_VTABLE CCustomUIAddInServer : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCustomUIAddInServer, &CLSID_CustomUIAddInServer>,
	public IDispatchImpl<ICustomUIAddInServer, &IID_ICustomUIAddInServer, &LIBID_CustomUILib>,
	public UserInputEvtsSink,
	public UserInterfaceEvtsSink
{
protected:

private:
    CComPtr<Application> m_pApplication ;

	CComPtr<ApplicationAddInSite> m_pAddInSite ;

	// Cmd Buttons and Handlers
	//
	CComObject<CCmdHandler1>* m_pCmd1;
	CComObject<CCmdHandler2>* m_pCmd2;
	CComObject<CCmdHandler3>* m_pCmd3;
	CComObject<CCmdHandler4>* m_pCmd4;

	// User input event
	//
	CComPtr<UserInputEventsObject> m_pUserInputEvents;

	// User interface event
	//
	CComPtr<UserInterfaceEventsObject> m_pUserInterfaceEvents;

public:
	CCustomUIAddInServer ()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_CustomUIAddInServer)
	DECLARE_NOT_AGGREGATABLE(CCustomUIAddInServer)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CCustomUIAddInServer)
		COM_INTERFACE_ENTRY(ICustomUIAddInServer)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()


public:

	//----- ApplicationAddInServer
	STDMETHOD(Activate)(IDispatch * pDisp, VARIANT_BOOL FirstTime);
	STDMETHOD(Deactivate)();
	STDMETHOD(ExecuteCommand)(long CommandID);
	STDMETHOD(get_Automation)(IDispatch * * ppResult);

	//----- UserInputEventsSink for getting the OnContextMenu event callback
	STDMETHOD(OnContextMenu) (SelectionDeviceEnum SelectionDevice, NameValueMap* AdditionalInfo, CommandBar* pCmdBar);

	//----- UserInterfaceEventsSink for getting the OnResetCommandBars event callback
	STDMETHOD(OnResetCommandBars) (ObjectsEnumerator* pCmdBarObjEnumerator, NameValueMap* Context);

	//----- UserInterfaceEventsSink for getting the OnResetEnvironments event callback
	STDMETHOD(OnResetEnvironments) (ObjectsEnumerator* pEnvObjEnumerator, NameValueMap* Context);

	//----- UserInterfaceEventsSink for getting the OnResetRibbonInterface event callback
	STDMETHOD(OnResetRibbonInterface) (NameValueMap* pContext);

	BEGIN_SINK_MAP(CCustomUIAddInServer)
		SINK_ENTRY_EX (0, DIID_UserInputEventsSink, UserInputEventsSink_OnContextMenu, OnContextMenu)
		SINK_ENTRY_EX (1, DIID_UserInterfaceEventsSink, UserInterfaceEventsSink_OnResetCommandBarsMeth, OnResetCommandBars)
		SINK_ENTRY_EX (1, DIID_UserInterfaceEventsSink, UserInterfaceEventsSink_OnResetEnvironmentsMeth, OnResetEnvironments)
		SINK_ENTRY_EX (1, DIID_UserInterfaceEventsSink, UserInterfaceEventsSink_OnResetRibbonInterfaceMeth, OnResetRibbonInterface)
	END_SINK_MAP()

	// Non-COM protocol

	HRESULT AddCommandButtonToCommandBar(CCmdHandler* pCmd, CommandBar* pCmdBar, CommandBarControl** pCmdCtrl);
	HRESULT AddCommandToCommandCategory(CCmdHandler* pCmd, CommandCategory* pCmdCat);
	HRESULT AddCommandBarToEnvPanelBar(CommandBar* pCmdBar, Environment* pEnv);
	HRESULT AddPopUpToCommandBar(CommandBar* pPopUpCmdBar, CommandBar* pCmdBar, CommandBarControl** pPopUpCmdBarCtrl);
	HRESULT AddCommandButtonToCommandControls(CCmdHandler* pCmd, CommandControls* pCmdCtrls, CommandControl** pCmdCtrl);

	HRESULT RemoveButtonsFromSketchPanel();

} ;

//-----------------------------------------------------------------------------
#endif //----- __CustomUIAddInServer_h_
