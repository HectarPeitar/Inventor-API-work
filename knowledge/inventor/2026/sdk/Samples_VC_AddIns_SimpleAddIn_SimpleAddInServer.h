// SimpleAddInServer.h : Declaration of the CSimpleAddInServer

#pragma once
#include "resource.h"       // main symbols

#include "SimpleAddIn.h"

#include "DrawSlotCommandButton.h"
#include "AddSlotOptionCommandButton.h"
#include "ToggleSlotStateCommandButton.h"


// CSimpleAddInServer

class ATL_NO_VTABLE CSimpleAddInServer : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSimpleAddInServer, &CLSID_SimpleAddInServer>,
	public IDispatchImpl<ISimpleAddInServer, &IID_ISimpleAddInServer, &LIBID_SimpleAddInLib, 1, 0>,
	public IDispEventImpl<1, CSimpleAddInServer, &DIID_UserInterfaceEventsSink, &LIBID_Inventor, 1, 0>
{

private:
	CComPtr<Application> m_pApplication;
	CComPtr<ApplicationAddInSite> m_pAddInSite;

	//user interface event
	CComPtr<UserInterfaceEventsObject> m_pUserInterfaceEvtsObj;

	//commands
	//Draw Slot command
	CComObject<CDrawSlotCommandButton>* m_pDrawSlotCmdBtn;

	//Add Slot Option command
	CComObject<CAddSlotOptionCommandButton>* m_pAddSlotOptionCmdBtn;

	//Toggle Slot State command
	CComObject<CToggleSlotStateCommandButton>* m_pToggleSlotStateCmdBtn;

	//Slot Width combo box
	CComPtr<ComboBoxDefinitionObject> m_pSlotWidthComboBoxDef;

	//Slot Height combo box
	CComPtr<ComboBoxDefinitionObject> m_pSlotHeightComboBoxDef;	
	
	// Slot panel
	CComPtr<RibbonPanel> m_pPartSketchSlotRibbonPanel;

public:
	CSimpleAddInServer()
	{
		m_pApplication = NULL;
		m_pAddInSite = NULL;

		m_pUserInterfaceEvtsObj = NULL;

		m_pDrawSlotCmdBtn = NULL;
		m_pAddSlotOptionCmdBtn = NULL;
		m_pToggleSlotStateCmdBtn = NULL;

		m_pSlotWidthComboBoxDef = NULL;
		m_pSlotHeightComboBoxDef = NULL;
		m_pPartSketchSlotRibbonPanel=NULL;

	}

	DECLARE_REGISTRY_RESOURCEID(IDR_SIMPLEADDINSERVER)

	BEGIN_COM_MAP(CSimpleAddInServer)
		COM_INTERFACE_ENTRY(ISimpleAddInServer)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	BEGIN_SINK_MAP(CSimpleAddInServer)
		SINK_ENTRY_EX (1, DIID_UserInterfaceEventsSink, UserInterfaceEventsSink_OnResetCommandBarsMeth, OnResetCommandBars)
		SINK_ENTRY_EX (1, DIID_UserInterfaceEventsSink, UserInterfaceEventsSink_OnResetEnvironmentsMeth, OnResetEnvironments)
		SINK_ENTRY_EX (1, DIID_UserInterfaceEventsSink, UserInterfaceEventsSink_OnResetRibbonInterfaceMeth, OnResetRibbonInterface)
	END_SINK_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:
	STDMETHOD(Activate)(IDispatch* pDisp, VARIANT_BOOL FirstTime);
	STDMETHOD(Deactivate)(void);
	STDMETHOD(ExecuteCommand)(long CommandId);
	STDMETHOD(get_Automation)(IDispatch** ppResult);

	//----- UserInterfaceEventsSink 
	STDMETHOD(OnResetCommandBars) (ObjectsEnumerator* pCommandBars, NameValueMap* pContext);
	STDMETHOD(OnResetEnvironments) (ObjectsEnumerator* pEnvironments, NameValueMap* pContext);
	STDMETHOD(OnResetRibbonInterface) (NameValueMap* pContext);


};

OBJECT_ENTRY_AUTO(__uuidof(SimpleAddInServer), CSimpleAddInServer)
