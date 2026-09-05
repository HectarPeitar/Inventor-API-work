// SimpleAddInServer.cpp : Implementation of CSimpleAddInServer

#include "stdafx.h"
#include "SimpleAddInServer.h"
#include "SimpleAddInServer.h"


// CSimpleAddInServer

STDMETHODIMP CSimpleAddInServer::Activate(IDispatch* pDisp, VARIANT_BOOL FirstTime)
{
	HRESULT hr;

	if (pDisp == NULL) return E_INVALIDARG;

	hr = pDisp->QueryInterface (__uuidof (m_pAddInSite), reinterpret_cast<void**>(&m_pAddInSite)) ;
	ATLASSERT(SUCCEEDED(hr));
	if (FAILED(hr))	return hr;
	
	//----- get the Inventor application object
	hr =m_pAddInSite->get_Application (&m_pApplication);
	ATLASSERT(SUCCEEDED(hr));
	if (FAILED(hr))	return hr;

	//get the command manager
	CComPtr<CommandManager> pCommandManager;
	hr = m_pApplication->get_CommandManager(&pCommandManager);
	if (FAILED(hr)) return hr;

	//create the combo boxes
	CComPtr<ControlDefinitions> pControlDefinitions;
	hr = pCommandManager->get_ControlDefinitions(&pControlDefinitions);
	if (FAILED(hr)) return hr;

	hr = pControlDefinitions->AddComboBoxDefinition(CComBSTR(_T("Slot Width")), 
													CComBSTR(_T("Autodesk:SimpleAddIn:SlotWidthCboBox")), 
													kShapeEditCmdType, 
													50, 
													CComVariant(_T("{DB59D9A7-EE4C-434A-BB5A-F93E8866E872}")), 
													CComBSTR(_T("Specifies slot width")), 
													CComBSTR(_T("Slot width")), 
													vtMissing, 
													vtMissing, 
													kDisplayTextInLearningMode, 
													&m_pSlotWidthComboBoxDef); 

	if (FAILED(hr)) return hr;

	hr = m_pSlotWidthComboBoxDef->AddItem(CComBSTR(_T("1 cm")), 0);
	hr = m_pSlotWidthComboBoxDef->AddItem(CComBSTR(_T("2 cm")), 0);
	hr = m_pSlotWidthComboBoxDef->AddItem(CComBSTR(_T("3 cm")), 0);
	hr = m_pSlotWidthComboBoxDef->AddItem(CComBSTR(_T("4 cm")), 0);
	hr = m_pSlotWidthComboBoxDef->AddItem(CComBSTR(_T("5 cm")), 0);

	hr = m_pSlotWidthComboBoxDef->put_ListIndex(1);
	
	hr = pControlDefinitions->AddComboBoxDefinition(CComBSTR(_T("Slot Height")), 
													CComBSTR(_T("Autodesk:SimpleAddIn:SlotHeightCboBox")), 
													kShapeEditCmdType, 
													100, 
													CComVariant(_T("{DB59D9A7-EE4C-434A-BB5A-F93E8866E872}")), 
													CComBSTR(_T("Specifies slot height")), 
													CComBSTR(_T("Slot height")), 
													vtMissing, 
													vtMissing, 
													kDisplayTextInLearningMode, 
													&m_pSlotHeightComboBoxDef); 

	if (FAILED(hr)) return hr;

	hr = m_pSlotHeightComboBoxDef->AddItem(CComBSTR(_T("1 cm")), 0);
	hr = m_pSlotHeightComboBoxDef->AddItem(CComBSTR(_T("2 cm")), 0);
	hr = m_pSlotHeightComboBoxDef->AddItem(CComBSTR(_T("3 cm")), 0);
	hr = m_pSlotHeightComboBoxDef->AddItem(CComBSTR(_T("4 cm")), 0);
	hr = m_pSlotHeightComboBoxDef->AddItem(CComBSTR(_T("5 cm")), 0);

	hr = m_pSlotHeightComboBoxDef->put_ListIndex(1);

	//create the command button(s)
	//create instance of the "DrawSlot" command button class 
	hr = CComObject<CDrawSlotCommandButton>::CreateInstance (&m_pDrawSlotCmdBtn);
	if (FAILED(hr))	return hr;

	m_pDrawSlotCmdBtn->AddRef();

	//create the "DrawSlot" button
	CComPtr<ButtonDefinitionObject> pDrawSlotCmdBtnDef;
	hr = m_pDrawSlotCmdBtn->CreateButtonDefinition(m_pApplication, 
										CComBSTR(_T("Draw Slot")), 
										CComBSTR(_T("Autodesk:SimpleAddIn:DrawSlotCmd")), 
										kShapeEditCmdType, 
										CComVariant(_T("{DB59D9A7-EE4C-434A-BB5A-F93E8866E872}")), 
										CComBSTR(_T("Create slot sketch graphics")), 
										CComBSTR(_T("Draw Slot")), 
										IDI_ICON_DRAWSLOT, 
										IDI_ICON_DRAWSLOT, 
										kDisplayTextInLearningMode,
										&pDrawSlotCmdBtnDef);
	if (FAILED(hr))	return hr;

	//create instance of the "AddSlotOption" command button class 
	hr = CComObject<CAddSlotOptionCommandButton>::CreateInstance (&m_pAddSlotOptionCmdBtn);
	if (FAILED(hr))	return hr;

	m_pAddSlotOptionCmdBtn->AddRef();

	//create the "AddSlotOption" button
	CComPtr<ButtonDefinitionObject> pAddSlotOptionCmdBtnDef;
	hr = m_pAddSlotOptionCmdBtn->CreateButtonDefinition(m_pApplication, 
										CComBSTR(_T("Add Slot width/height")), 
										CComBSTR(_T("Autodesk:SimpleAddIn:AddSlotOptionCmd")), 
										kShapeEditCmdType, 
										CComVariant(_T("{DB59D9A7-EE4C-434A-BB5A-F93E8866E872}")), 
										CComBSTR(_T("Adds option for slot width/height")), 
										CComBSTR(_T("Add slot option")), 
										IDI_ICON_ADDSLOTOPTION, 
										IDI_ICON_ADDSLOTOPTION, 
										kDisplayTextInLearningMode,
										&pAddSlotOptionCmdBtnDef);
	if (FAILED(hr))	return hr;

	//create instance of the "ToggleSlotState" command button class 
	hr = CComObject<CToggleSlotStateCommandButton>::CreateInstance (&m_pToggleSlotStateCmdBtn);
	if (FAILED(hr))	return hr;

	m_pToggleSlotStateCmdBtn->AddRef();

	//create the "ToggleSlotState" button
	CComPtr<ButtonDefinitionObject> pToggleSlotStateCmdBtnDef;
	hr = m_pToggleSlotStateCmdBtn->CreateButtonDefinition(m_pApplication, 
										CComBSTR(_T("Toggle Slot State")), 
										CComBSTR(_T("Autodesk:SimpleAddIn:ToggleSlotStateCmd")), 
										kShapeEditCmdType, 
										CComVariant(_T("{DB59D9A7-EE4C-434A-BB5A-F93E8866E872}")), 
										CComBSTR(_T("Enables/Disables state of slot command")), 
										CComBSTR(_T("Toggle Slot State")), 
										IDI_ICON_TOGGLESLOTSTATE, 
										IDI_ICON_TOGGLESLOTSTATE, 
										kDisplayTextInLearningMode,
										&pToggleSlotStateCmdBtnDef);
	if (FAILED(hr))	return hr;

	//create command category
	//get the command categories collection
	CComPtr<CommandCategories> pCommandCategories;
	hr = pCommandManager->get_CommandCategories(&pCommandCategories);

	//create the command categories for this AddIn
	CComPtr<CommandCategory> pDrawSlotCmdCat;
	hr = pCommandCategories->Add(CComBSTR(_T("Slot")), 
								CComBSTR(_T("Autodesk:SimpleAddIn:SlotCmdCat")), 
								CComVariant(_T("{DB59D9A7-EE4C-434A-BB5A-F93E8866E872}")), 
								&pDrawSlotCmdCat);
	if (SUCCEEDED(hr)){

		//add the commands to the command category
		//add the "Slot Width" combo box to the command category
		hr = pDrawSlotCmdCat->Add(m_pSlotWidthComboBoxDef);

		//add the "Slot Height" combo box to the command category
		hr = pDrawSlotCmdCat->Add(m_pSlotHeightComboBoxDef);

		//add the "Draw Slot" command to the command category
		hr = pDrawSlotCmdCat->Add(pDrawSlotCmdBtnDef);

		//add the "Add Slot Option" command to the command category
		hr = pDrawSlotCmdCat->Add(pAddSlotOptionCmdBtnDef);

		//add the "Toggle Slot State" command to the command category
		hr = pDrawSlotCmdCat->Add(pToggleSlotStateCmdBtnDef);
	}

	if (FirstTime != VARIANT_FALSE){

		//get the user interface manager
		CComPtr<UserInterfaceManager> pUserInterfaceMgr;
		hr = m_pApplication->get_UserInterfaceManager(&pUserInterfaceMgr);
		if (FAILED(hr))	return hr;

		InterfaceStyleEnum interfaceStyle;
		pUserInterfaceMgr->get_InterfaceStyle(&interfaceStyle);

		// create the UI for the classic interface
		if(interfaceStyle == kClassicInterface)
		{
			//get the command bars collection
			CComPtr<CommandBars> pCommandBars;
			hr = pUserInterfaceMgr->get_CommandBars(&pCommandBars);
			if (FAILED(hr))	return hr;

			//create the "AddIn Slot" toolbar
			CComPtr<CommandBar> pSlotCmdBar;
			hr = pCommandBars->Add(CComBSTR(_T("Slot")), 
								CComBSTR(_T("Autodesk:SimpleAddIn:SlotToolbar")),
								kRegularCommandBar,
								CComVariant(_T("{DB59D9A7-EE4C-434A-BB5A-F93E8866E872}")),
								&pSlotCmdBar);

			if (SUCCEEDED(hr)){
		
				//get the controls of the toolbar
				CComPtr<CommandBarControls> pSlotToolBarCtrls;
				hr = pSlotCmdBar->get_Controls(&pSlotToolBarCtrls);
				
				if (SUCCEEDED(hr)){

					//add the combo boxes to the toolbar
					CComPtr<CommandBarControl> pSlotWidthCmdCboBoxCmdBarCtrl;
					hr = pSlotToolBarCtrls->AddComboBox(m_pSlotWidthComboBoxDef, 0, &pSlotWidthCmdCboBoxCmdBarCtrl);

					CComPtr<CommandBarControl> pSlotHeightCmdCboBoxCmdBarCtrl;
					hr = pSlotToolBarCtrls->AddComboBox(m_pSlotHeightComboBoxDef, 0, &pSlotHeightCmdCboBoxCmdBarCtrl);

					//add the buttons to the toolbar
					CComPtr<CommandBarControl> pDrawSlotCmdBtnCmdBarCtrl;
					hr = pSlotToolBarCtrls->AddButton(pDrawSlotCmdBtnDef, 0, &pDrawSlotCmdBtnCmdBarCtrl);

					CComPtr<CommandBarControl> pAddSlotOptionCmdBtnCmdBarCtrl;
					hr = pSlotToolBarCtrls->AddButton(pAddSlotOptionCmdBtnDef, 0, &pAddSlotOptionCmdBtnCmdBarCtrl);

					CComPtr<CommandBarControl> pToggleSlotStateCmdBtnCmdBarCtrl;
					hr = pSlotToolBarCtrls->AddButton(pToggleSlotStateCmdBtnDef, 0, &pToggleSlotStateCmdBtnCmdBarCtrl);
				}
			}

			//get the envirionments collection
			CComPtr<Environments> pEnvs;
			hr = pUserInterfaceMgr->get_Environments(&pEnvs);
			if(FAILED(hr)) return hr;

			//get the part sketch environment from the environments collection
			CComPtr<Environment> pPartSketchEnv;
			hr = pEnvs->get_Item(CComVariant(_T(PartSketchEnvironment_InternalName)), &pPartSketchEnv);
			
			if (SUCCEEDED(hr)){

				CComPtr<PanelBarObject> pPartSketchEnvPanelBar;
				hr = pPartSketchEnv->get_PanelBar(&pPartSketchEnvPanelBar);
				
				if (SUCCEEDED(hr)){
					CComPtr<CommandBarList> pPartSketchEnvPanelBarCmdBarList;
					hr = pPartSketchEnvPanelBar->get_CommandBarList(&pPartSketchEnvPanelBarCmdBarList);

					if (SUCCEEDED(hr))
						hr = pPartSketchEnvPanelBarCmdBarList->Add(pSlotCmdBar);
				}
			}
		}

		// create the UI for the ribbon interface
		else
		{

			//get the ribbon associated with part documents
			CComPtr<Ribbons> pRibbons;
			hr = pUserInterfaceMgr->get_Ribbons(&pRibbons);
			if(FAILED(hr)) return hr;

			CComPtr<Ribbon> pPartRibbon;
			hr = pRibbons->get_Item(CComVariant(_T("Part")), &pPartRibbon);
			if(FAILED(hr)) return hr;

			//get the tabs associated with part ribbon
			CComPtr<RibbonTabs> pRibbonTabs;
			hr = pPartRibbon->get_RibbonTabs(&pRibbonTabs);
			if(FAILED(hr)) return hr;

			CComPtr<RibbonTab> pPartSketchRibbonTab;
			hr = pRibbonTabs->get_Item(CComVariant(_T("id_TabSketch")), &pPartSketchRibbonTab);
			if(FAILED(hr)) return hr;

			//create a new panel within the tab
			CComPtr<RibbonPanels> pRibbonPanels;
			hr = pPartSketchRibbonTab->get_RibbonPanels(&pRibbonPanels);
			if(FAILED(hr)) return hr;

			hr = pRibbonPanels->Add(CComBSTR(_T("Slot")), 
										CComBSTR(_T("Autodesk:SimpleAddIn:SlotRibbonPanel")), 
										CComBSTR(_T("{DB59D9A7-EE4C-434A-BB5A-F93E8866E872}")), 
										CComBSTR(_T("")),
										VARIANT_FALSE,
										&m_pPartSketchSlotRibbonPanel);
			if(FAILED(hr)) return hr;

			//add controls to the slot panel
			CComPtr<CommandControls> pPartSketchSlotRibbonPanelCtrls;
			hr = m_pPartSketchSlotRibbonPanel->get_CommandControls(&pPartSketchSlotRibbonPanelCtrls);

			if (SUCCEEDED(hr)){

				//add the combo boxes to the ribbon panel
				CComPtr<CommandControl> pSlotWidthCmdCboBoxCmdCtrl;
				hr = pPartSketchSlotRibbonPanelCtrls->AddComboBox(m_pSlotWidthComboBoxDef, 
																	CComBSTR(_T("")), 
																	VARIANT_FALSE, 
																	&pSlotWidthCmdCboBoxCmdCtrl);

				CComPtr<CommandControl> pSlotHeightCmdCboBoxCmdCtrl;
				hr = pPartSketchSlotRibbonPanelCtrls->AddComboBox(m_pSlotHeightComboBoxDef, 
																	CComBSTR(_T("")), 
																	VARIANT_FALSE, 
																	&pSlotHeightCmdCboBoxCmdCtrl);

				//add the buttons to the ribbon panel
				CComPtr<CommandControl> pDrawSlotCmdBtnCmdCtrl;
				hr = pPartSketchSlotRibbonPanelCtrls->AddButton(pDrawSlotCmdBtnDef, 
																	VARIANT_FALSE, 
																	VARIANT_TRUE, 
																	CComBSTR(_T("")), 
																	VARIANT_FALSE, 
																	&pDrawSlotCmdBtnCmdCtrl);

				CComPtr<CommandControl> pAddSlotOptionCmdBtnCmdCtrl;
				hr = pPartSketchSlotRibbonPanelCtrls->AddButton(pAddSlotOptionCmdBtnDef, 
																	VARIANT_FALSE, 
																	VARIANT_TRUE,
																	CComBSTR(_T("")), 
																	VARIANT_FALSE, 
																	&pAddSlotOptionCmdBtnCmdCtrl);

				CComPtr<CommandControl> pToggleSlotStateCmdBtnCmdCtrl;
				hr = pPartSketchSlotRibbonPanelCtrls->AddButton(pToggleSlotStateCmdBtnDef, 
																	VARIANT_FALSE, 
																	VARIANT_TRUE, 
																	CComBSTR(_T("")), 
																	VARIANT_FALSE, 
																	&pToggleSlotStateCmdBtnCmdCtrl);				
			}
		
		}


	}

	//advise to UserInterfaceEvents
	CComPtr<UserInterfaceManager> pUsrInterfaceMgr;
	hr = m_pApplication->get_UserInterfaceManager(&pUsrInterfaceMgr);
	if(FAILED(hr)) return hr;

	hr = pUsrInterfaceMgr->get_UserInterfaceEvents(&m_pUserInterfaceEvtsObj);
	if(FAILED(hr)) return hr;

	hr = DispEventAdvise(m_pUserInterfaceEvtsObj);
	if(FAILED(hr)) return hr;

	return S_OK;
}

STDMETHODIMP CSimpleAddInServer::Deactivate()
{
	HRESULT hr;

	//disconnect button sinks
	hr = m_pDrawSlotCmdBtn->Disconnect();

	m_pDrawSlotCmdBtn->Release();
	m_pDrawSlotCmdBtn = NULL;

	hr = m_pAddSlotOptionCmdBtn->Disconnect();

	m_pAddSlotOptionCmdBtn->Release();
	m_pAddSlotOptionCmdBtn = NULL;

	hr = m_pToggleSlotStateCmdBtn->Disconnect();

	m_pToggleSlotStateCmdBtn->Release();
	m_pToggleSlotStateCmdBtn = NULL;
	
	if  (m_pPartSketchSlotRibbonPanel != NULL )
	{
		m_pPartSketchSlotRibbonPanel.Release();
		m_pPartSketchSlotRibbonPanel = NULL;
	}


	//unadvise UserInterfaceEvents
	hr = DispEventUnadvise(m_pUserInterfaceEvtsObj);
	
	m_pAddInSite.Release();
	m_pApplication.Release();

	return S_OK;
}

STDMETHODIMP CSimpleAddInServer::ExecuteCommand(long CommandId)
{
	return E_NOTIMPL;
}

STDMETHODIMP CSimpleAddInServer::get_Automation(IDispatch** ppResult)
{
	if (ppResult == NULL) 
		return E_INVALIDARG;

	*ppResult = NULL;

	return E_NOTIMPL;
}

//-----------------------------------------------------------------------------
//----- Implementation of UserInterface Events sink methods
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
STDMETHODIMP CSimpleAddInServer::OnResetCommandBars(ObjectsEnumerator* pCommandBars, NameValueMap* pContext)
{
	HRESULT hr = S_OK;

	long lNoCmdBars;
	hr = pCommandBars->get_Count(&lNoCmdBars);
	if (FAILED(hr)) return hr;
	
	for (long lCmdBarCt = 1; lCmdBarCt <= lNoCmdBars; lCmdBarCt++)
	{
		CComPtr<IDispatch> pCmdBarDisp;
		hr = pCommandBars->get_Item(lCmdBarCt, &pCmdBarDisp);
		if (FAILED(hr)) continue;
		
		CComQIPtr<CommandBar> pCmdBar(pCmdBarDisp);
		if (!pCmdBar) continue;

		CComBSTR bstrCmdBarInternalName;
		hr = pCmdBar->get_InternalName(&bstrCmdBarInternalName);
		if (FAILED(hr)) continue;
		
		//add the command buttons back to the slot toolbar
		if (bstrCmdBarInternalName == _T("Autodesk:SimpleAddIn:SlotToolbar"))
		{
			//get the controls of the command bar
			CComPtr<CommandBarControls> pCmdBarCtrls;
			hr = pCmdBar->get_Controls(&pCmdBarCtrls);
			if (FAILED(hr))	return hr;

			//add the combo boxes to the toolbar
			CComPtr<CommandBarControl> pSlotWidthCmdCboBoxCmdBarCtrl;
			hr = pCmdBarCtrls->AddComboBox(m_pSlotWidthComboBoxDef, 0, &pSlotWidthCmdCboBoxCmdBarCtrl);

			CComPtr<CommandBarControl> pSlotHeightCmdCboBoxCmdBarCtrl;
			hr = pCmdBarCtrls->AddComboBox(m_pSlotHeightComboBoxDef, 0, &pSlotHeightCmdCboBoxCmdBarCtrl);

			//add the buttons to the toolbar
			CComPtr<ButtonDefinitionObject> pDrawSlotCmdBtnDef;
			hr = m_pDrawSlotCmdBtn->GetButtonDefinition(&pDrawSlotCmdBtnDef);

			if(SUCCEEDED(hr)){
				CComPtr<CommandBarControl> pDrawSlotCmdBtnCmdBarCtrl;
				hr = pCmdBarCtrls->AddButton(pDrawSlotCmdBtnDef, 0, &pDrawSlotCmdBtnCmdBarCtrl);
			}

			CComPtr<ButtonDefinitionObject> pAddSlotOptionCmdBtnDef;
			hr = m_pAddSlotOptionCmdBtn->GetButtonDefinition(&pAddSlotOptionCmdBtnDef);
			
			if(SUCCEEDED(hr)){
				CComPtr<CommandBarControl> pAddSlotOptionCmdBtnCmdBarCtrl;
				hr = pCmdBarCtrls->AddButton(pAddSlotOptionCmdBtnDef, 0, &pAddSlotOptionCmdBtnCmdBarCtrl);
			}

			CComPtr<ButtonDefinitionObject> pToggleSlotStateCmdBtnDef;
			hr = m_pToggleSlotStateCmdBtn->GetButtonDefinition(&pToggleSlotStateCmdBtnDef);
			
			if(SUCCEEDED(hr)){
				CComPtr<CommandBarControl> pToggleSlotStateCmdBtnCmdBarCtrl;
				hr = pCmdBarCtrls->AddButton(pToggleSlotStateCmdBtnDef, 0, &pToggleSlotStateCmdBtnCmdBarCtrl);
			}

			return S_OK;
		}
		
	}	
	return hr;
}

STDMETHODIMP CSimpleAddInServer::OnResetEnvironments(ObjectsEnumerator* pEnvironments, NameValueMap* pContext)
{
	HRESULT hr = S_OK;

	CComPtr<UserInterfaceManager> pUserInterfaceMgr;
	hr = m_pApplication->get_UserInterfaceManager(&pUserInterfaceMgr);
	if(FAILED(hr)) return hr;

	CComPtr<CommandBars> pCmdBars;
	hr = pUserInterfaceMgr->get_CommandBars(&pCmdBars);
	if(FAILED(hr)) return hr;

	CComPtr<CommandBar> pSlotCmdBar;
	hr = pCmdBars->get_Item(CComVariant(_T("Autodesk:SimpleAddIn:SlotToolbar")), &pSlotCmdBar);
	if(FAILED(hr)) return hr;

	long lNoEnvs;
	hr = pEnvironments->get_Count(&lNoEnvs);
	
	for (long lEnvCt = 1; lEnvCt <= lNoEnvs; lEnvCt++)
	{
		CComPtr<IDispatch> pEnvDisp;
		hr = pEnvironments->get_Item(lEnvCt, &pEnvDisp);
		if (FAILED(hr)) continue;
		
		CComQIPtr<Environment> pEnv(pEnvDisp);
		if (!pEnv) continue;

		CComBSTR bstrEnvInternalName;
		hr = pEnv->get_InternalName(&bstrEnvInternalName);
		if (FAILED(hr)) continue;
		
		if (bstrEnvInternalName == _T(PartSketchEnvironment_InternalName))
		{
			CComPtr<PanelBarObject> pPartSketchEnvPanelBar;
			hr = pEnv->get_PanelBar(&pPartSketchEnvPanelBar);
			
			if (SUCCEEDED(hr)){

				CComPtr<CommandBarList> pPartSketchEnvPanelBarCmdBarList;
				hr = pPartSketchEnvPanelBar->get_CommandBarList(&pPartSketchEnvPanelBarCmdBarList);
				
				if (SUCCEEDED(hr))
					hr = pPartSketchEnvPanelBarCmdBarList->Add(pSlotCmdBar);
			}

			return S_OK;
		
		}
	}

	return hr;
}

STDMETHODIMP CSimpleAddInServer::OnResetRibbonInterface(NameValueMap* pContext)
{
	HRESULT hr = S_OK;

	CComPtr<UserInterfaceManager> pUserInterfaceMgr;
	hr = m_pApplication->get_UserInterfaceManager(&pUserInterfaceMgr);
	if(FAILED(hr)) return hr;

	//get the ribbon associated with part documents
	CComPtr<Ribbons> pRibbons;
	hr = pUserInterfaceMgr->get_Ribbons(&pRibbons);
	if(FAILED(hr)) return hr;

	CComPtr<Ribbon> pPartRibbon;
	hr = pRibbons->get_Item(CComVariant(_T("Part")), &pPartRibbon);
	if(FAILED(hr)) return hr;

	//get the tabs associated with part ribbon
	CComPtr<RibbonTabs> pRibbonTabs;
	hr = pPartRibbon->get_RibbonTabs(&pRibbonTabs);
	if(FAILED(hr)) return hr;

	CComPtr<RibbonTab> pPartSketchRibbonTab;
	hr = pRibbonTabs->get_Item(CComVariant(_T("id_TabSketch")), &pPartSketchRibbonTab);
	if(FAILED(hr)) return hr;

	//create a new panel within the tab
	CComPtr<RibbonPanels> pRibbonPanels;
	hr = pPartSketchRibbonTab->get_RibbonPanels(&pRibbonPanels);
	if(FAILED(hr)) return hr;

	//CComPtr<RibbonPanel> pPartSketchSlotRibbonPanel;
	hr = pRibbonPanels->Add(CComBSTR(_T("Slot")), 
								CComBSTR(_T("Autodesk:SimpleAddIn:SlotRibbonPanel")), 
								CComBSTR(_T("{DB59D9A7-EE4C-434A-BB5A-F93E8866E872}")), 
								CComBSTR(_T("")),
								VARIANT_FALSE,
								&m_pPartSketchSlotRibbonPanel);
	if(FAILED(hr)) return hr;

	//add controls to the slot panel
	CComPtr<CommandControls> pPartSketchSlotRibbonPanelCtrls;
	hr = m_pPartSketchSlotRibbonPanel->get_CommandControls(&pPartSketchSlotRibbonPanelCtrls);

	if (SUCCEEDED(hr)){

		//add the combo boxes to the ribbon panel
		CComPtr<CommandControl> pSlotWidthCmdCboBoxCmdCtrl;
		hr = pPartSketchSlotRibbonPanelCtrls->AddComboBox(m_pSlotWidthComboBoxDef, 
															CComBSTR(_T("")), 
															VARIANT_FALSE, 
															&pSlotWidthCmdCboBoxCmdCtrl);

		CComPtr<CommandControl> pSlotHeightCmdCboBoxCmdCtrl;
		hr = pPartSketchSlotRibbonPanelCtrls->AddComboBox(m_pSlotHeightComboBoxDef, 
															CComBSTR(_T("")), 
															VARIANT_FALSE, 
															&pSlotHeightCmdCboBoxCmdCtrl);

		//add the buttons to the ribbon panel
		CComPtr<ButtonDefinitionObject> pDrawSlotCmdBtnDef;
		hr = m_pDrawSlotCmdBtn->GetButtonDefinition(&pDrawSlotCmdBtnDef);

		CComPtr<CommandControl> pDrawSlotCmdBtnCmdCtrl;
		hr = pPartSketchSlotRibbonPanelCtrls->AddButton(pDrawSlotCmdBtnDef, 
															VARIANT_FALSE, 
															VARIANT_TRUE, 
															CComBSTR(_T("")), 
															VARIANT_FALSE, 
															&pDrawSlotCmdBtnCmdCtrl);

		
		CComPtr<ButtonDefinitionObject> pAddSlotOptionCmdBtnDef;
		hr = m_pAddSlotOptionCmdBtn->GetButtonDefinition(&pAddSlotOptionCmdBtnDef);

		CComPtr<CommandControl> pAddSlotOptionCmdBtnCmdCtrl;
		hr = pPartSketchSlotRibbonPanelCtrls->AddButton(pAddSlotOptionCmdBtnDef, 
															VARIANT_FALSE, 
															VARIANT_TRUE,
															CComBSTR(_T("")), 
															VARIANT_FALSE, 
															&pAddSlotOptionCmdBtnCmdCtrl);

		CComPtr<ButtonDefinitionObject> pToggleSlotStateCmdBtnDef;
		hr = m_pToggleSlotStateCmdBtn->GetButtonDefinition(&pToggleSlotStateCmdBtnDef);

		CComPtr<CommandControl> pToggleSlotStateCmdBtnCmdCtrl;
		hr = pPartSketchSlotRibbonPanelCtrls->AddButton(pToggleSlotStateCmdBtnDef, 
															VARIANT_FALSE, 
															VARIANT_TRUE, 
															CComBSTR(_T("")), 
															VARIANT_FALSE, 
															&pToggleSlotStateCmdBtnCmdCtrl);				
	}

	return hr;
}
