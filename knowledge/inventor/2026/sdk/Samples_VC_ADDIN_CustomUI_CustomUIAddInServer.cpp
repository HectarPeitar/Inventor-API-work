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
//----- CustomUIAddInServer.cpp : Implementation of CCustomUIAddInServer
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "CustomUI.h"
#include "CustomUIAddInServer.h"
#include "CmdHandler1.h"
#include "CmdHandler2.h"
#include "CmdHandler3.h"
#include "CmdHandler4.h"

//-----------------------------------------------------------------------------
STDMETHODIMP CCustomUIAddInServer::Activate (IDispatch *pDisp, VARIANT_BOOL FirstTime)
{
	HRESULT hr = S_OK;

	if (pDisp == NULL) return E_INVALIDARG;

	hr = pDisp->QueryInterface (__uuidof (m_pAddInSite), reinterpret_cast<void**>(&m_pAddInSite)) ;
	ATLASSERT(SUCCEEDED(hr));
	if (FAILED(hr))	return hr;
	
	//----- get the Inventor application object
	hr = m_pAddInSite->get_Application(&m_pApplication);
	ATLASSERT(SUCCEEDED(hr));
	if (FAILED(hr))	return hr;

	// CREATE THE COMMAND BUTTONS AND THEIR HANDLERS
	
	// Command1
	//
	hr = CComObject<CCmdHandler1>::CreateInstance(&m_pCmd1);
	ATLASSERT(SUCCEEDED(hr));
	if (SUCCEEDED(hr))
	{

		m_pCmd1->AddRef();

		// Make sure the Internal Name is unique 
		// (you could follow a naming scheme like: "CompanyName:ProductName:ItemName")
		//
		hr = m_pCmd1->CreateButtonDefinition(m_pApplication, 
											CComBSTR(_T("Command 1")), // Display name
											CComBSTR(_T("Autodesk:CustomUI:Cmd1")), // Internal name
											kQueryOnlyCmdType, // Command type
											CComVariant(_T("{B6CD8174-8817-4AF2-9561-C0F273ABF5D8}")), // Client id
											CComBSTR(_T("Command 1")),// Description
											CComBSTR(_T("Command 1")), // Tool tip
											IDI_ICON1, // Small icon
											IDI_ICON1_LG, // Large icon
											kDisplayTextInLearningMode); //Button display type
		ATLASSERT(SUCCEEDED(hr));
	}

	// Command2
	//
	hr = CComObject<CCmdHandler2>::CreateInstance(&m_pCmd2);
	ATLASSERT(SUCCEEDED(hr));
	if (SUCCEEDED(hr))
	{
		m_pCmd2->AddRef();
	
		// Make sure the Internal Name is unique 
		// (you could follow a naming scheme like: "CompanyName:ProductName:ItemName")
		//
		hr = m_pCmd2->CreateButtonDefinition(m_pApplication, 
											CComBSTR(_T("Command 2")), // Display name
											CComBSTR(_T("Autodesk:CustomUI:Cmd2")), // Internal name
											kQueryOnlyCmdType, // Command type
											CComVariant(_T("{B6CD8174-8817-4AF2-9561-C0F273ABF5D8}")), // Client id
											CComBSTR(_T("Command 2")),// Description
											CComBSTR(_T("Command 2")), // Tool tip
											IDI_ICON2, // Small icon
											IDI_ICON2_LG, // Large icon
											kDisplayTextInLearningMode); //Button display type
		ATLASSERT(SUCCEEDED(hr));
	}

	// Command3
	//
	hr = CComObject<CCmdHandler3>::CreateInstance(&m_pCmd3);
	ATLASSERT(SUCCEEDED(hr));
	if (SUCCEEDED(hr))
	{
		m_pCmd3->AddRef();
	
		// Make sure the Internal Name is unique 
		// (you could follow a naming scheme like: "CompanyName:ProductName:ItemName")
		//
		hr = m_pCmd3->CreateButtonDefinition(m_pApplication, 
											CComBSTR(_T("Command 3")), // Display name
											CComBSTR(_T("Autodesk:CustomUI:Cmd3")), // Internal name
											kQueryOnlyCmdType, // Command type
											CComVariant(_T("{B6CD8174-8817-4AF2-9561-C0F273ABF5D8}")), // Client id
											CComBSTR(_T("Command 3")),// Description
											CComBSTR(_T("Command 3")), // Tool tip
											IDI_ICON3, // Small icon
											IDI_ICON3_LG, // Large icon
											kDisplayTextInLearningMode); //Button display type
		ATLASSERT(SUCCEEDED(hr));
	}

	// Command4
	//
	hr = CComObject<CCmdHandler4>::CreateInstance(&m_pCmd4);
	ATLASSERT(SUCCEEDED(hr));
	if (SUCCEEDED(hr))
	{
		m_pCmd4->AddRef();
	
		// Make sure the Internal Name is unique 
		// (you could follow a naming scheme like: "CompanyName:ProductName:ItemName")
		//
		hr = m_pCmd4->CreateButtonDefinition(m_pApplication, 
											CComBSTR(_T("Command 4")), // Display name
											CComBSTR(_T("Autodesk:CustomUI:Cmd4")), // Internal name
											kQueryOnlyCmdType, // Command type
											CComVariant(_T("{B6CD8174-8817-4AF2-9561-C0F273ABF5D8}")), // Client id
											CComBSTR(_T("Command 4")),// Description
											CComBSTR(_T("Command 4")), // Tool tip
											IDI_ICON4, // Small icon
											IDI_ICON4_LG, // Large icon
											kDisplayTextInLearningMode); //Button display type
		ATLASSERT(SUCCEEDED(hr)) ;
	}

	// Get the command manager
	//
	CComPtr<CommandManager> pCmdMgr;
	hr = m_pApplication->get_CommandManager(&pCmdMgr);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;

	// Create command category
	//
	CComPtr<CommandCategories> pCmdCategories;
	hr = pCmdMgr->get_CommandCategories(&pCmdCategories);
	ATLASSERT(SUCCEEDED(hr));
	if (SUCCEEDED(hr))
	{
		CComPtr<CommandCategory> pCmdCat1;
		hr = pCmdCategories->Add(CComBSTR(_T("CustomUI")), // Display name
								CComBSTR(_T("Autodesk:CustomUI:CmdCat1")), // Internal name
								CComVariant(_T("{B6CD8174-8817-4AF2-9561-C0F273ABF5D8}")),
								&pCmdCat1); // Client id
		ATLASSERT(SUCCEEDED(hr));
		if (SUCCEEDED(hr))
		{
			hr = AddCommandToCommandCategory(m_pCmd1, pCmdCat1);
			ATLASSERT(SUCCEEDED(hr));

			hr = AddCommandToCommandCategory(m_pCmd2, pCmdCat1);
			ATLASSERT(SUCCEEDED(hr));

			hr = AddCommandToCommandCategory(m_pCmd3, pCmdCat1);
			ATLASSERT(SUCCEEDED(hr));

			hr = AddCommandToCommandCategory(m_pCmd4, pCmdCat1);
			ATLASSERT(SUCCEEDED(hr));			
		}
	}

	if (FirstTime != VARIANT_FALSE){	

		// Get the user interface manager which provides access to command bars, environments
		//
		CComPtr<UserInterfaceManager> pUserInterfaceMgr;
		hr = m_pApplication->get_UserInterfaceManager(&pUserInterfaceMgr);
		ATLASSERT(SUCCEEDED(hr));
		if(FAILED(hr)) return hr;

		InterfaceStyleEnum interfaceStyle;
		pUserInterfaceMgr->get_InterfaceStyle(&interfaceStyle);

		// create the UI for the classic interface
		if(interfaceStyle == kClassicInterface)
		{
			// CREATE THE COMMAND BAR 
			//
			CComPtr<CommandBars> pCmdBars;
			hr = pUserInterfaceMgr->get_CommandBars(&pCmdBars);
			ATLASSERT(SUCCEEDED(hr));
			if(FAILED(hr)) return hr;

			// Make sure the Internal Name is unique (you could follow a naming scheme like: "CompanyName:ProductName:ItemName")
			//
			CComPtr<CommandBar> pCmdBar1;
			hr = pCmdBars->Add(CComBSTR(_T("Command Bar1")), // Display name
				CComBSTR(_T("Autodesk:CustomUI:CmdBar1")), // Internal name
				kPopUpCommandBar, // Command bar type
				CComVariant(_T("{B6CD8174-8817-4AF2-9561-C0F273ABF5D8}")), // Client id
				&pCmdBar1);
			ATLASSERT(SUCCEEDED(hr));

			// CUSTOMIZE COMMAND BARS
			//
			if (SUCCEEDED(hr))
			{
				// add the four commands to the Command Bar
				// Add Command1 to the Command Bar
				//
				CComPtr<CommandBarControl> pCmd1CmdBar1Ctrl;
				hr = AddCommandButtonToCommandBar(m_pCmd1, pCmdBar1, &pCmd1CmdBar1Ctrl);	
				ATLASSERT(SUCCEEDED(hr));

				// Add Command2 to the Command Bar
				//
				CComPtr<CommandBarControl> pCmd2CmdBar1Ctrl;
				hr = AddCommandButtonToCommandBar(m_pCmd2, pCmdBar1, &pCmd2CmdBar1Ctrl);	
				ATLASSERT(SUCCEEDED(hr));

				// Add Command3 to the Command Bar
				//
				CComPtr<CommandBarControl> pCmd3CmdBar1Ctrl;
				hr = AddCommandButtonToCommandBar(m_pCmd3, pCmdBar1, &pCmd3CmdBar1Ctrl);	
				ATLASSERT(SUCCEEDED(hr));

				// Add Command4 to the Command Bar
				//
				CComPtr<CommandBarControl> pCmd4CmdBar1Ctrl;
				hr = AddCommandButtonToCommandBar(m_pCmd4, pCmdBar1, &pCmd4CmdBar1Ctrl);	
				ATLASSERT(SUCCEEDED(hr));
			}

			// Add the Command Bar as a popup to the Menu bar for the part environment
			//
			CComPtr<CommandBar> pPartEnvMenuCmdBar;
			hr = pCmdBars->get_Item(CComVariant(_T("PartMenuBar")), &pPartEnvMenuCmdBar);
			ATLASSERT(SUCCEEDED(hr));

			if (SUCCEEDED(hr))
			{
				CComPtr<CommandBarControl> pCmdBar1PartEnvMenuBarCtrl;
				hr = AddPopUpToCommandBar(pCmdBar1, pPartEnvMenuCmdBar, &pCmdBar1PartEnvMenuBarCtrl);
				ATLASSERT(SUCCEEDED(hr));
			}

			// CUSTOMIZE ENVIRONMENTS

			// Get the environments collection
			//
			CComPtr<Environments> pEnvs;
			hr = pUserInterfaceMgr->get_Environments(&pEnvs);
			ATLASSERT(SUCCEEDED(hr));
			if(FAILED(hr)) return hr;

			// CUSTOMIZE THE PART ENVIRONMENT
			//
			// Get the part environment from the environments collection
			CComPtr<Environment> pPartEnv;
			hr = pEnvs->get_Item(CComVariant(_T(PartEnvironment_InternalName)), &pPartEnv);
			ATLASSERT(SUCCEEDED(hr));
			if (SUCCEEDED(hr))
			{
				// Add the Command Bar to the Panel Bar for the part environment
				//
				hr = AddCommandBarToEnvPanelBar(pCmdBar1, pPartEnv);
				ATLASSERT(SUCCEEDED(hr));

				// Add Command Buttons 3, and 4 to the environment Tool bar
				// 
				CComPtr<CommandBar> pPartEnvDefaultToolBar;
				hr = pPartEnv->get_DefaultToolBar(&pPartEnvDefaultToolBar);
				ATLASSERT(SUCCEEDED(hr));
				if (SUCCEEDED(hr))
				{
					CComPtr<CommandBarControl> pCmd3PartEnvDefaultToolBarCtrl;
					hr = AddCommandButtonToCommandBar(m_pCmd3, pPartEnvDefaultToolBar, &pCmd3PartEnvDefaultToolBarCtrl);
					ATLASSERT(SUCCEEDED(hr));

					CComPtr<CommandBarControl> pCmd4PartEnvDefaultToolBarCtrl;
					hr = AddCommandButtonToCommandBar(m_pCmd4, pPartEnvDefaultToolBar, &pCmd4PartEnvDefaultToolBarCtrl);
					ATLASSERT(SUCCEEDED(hr));
				}
			}
		}
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

			//Introduce RibbonTab(“CustomUI”).RibbonPanels(“CustomUI”)
			//{ Begin
			CComPtr<RibbonTab> pPartCustUIRibbonTab;
			hr = pRibbonTabs->Add(CComBSTR(_T("CustomUI")), 
				CComBSTR(_T("Autodesk:CustomUI:CustomUIRibbonTab")), 
				CComBSTR(_T("{B6CD8174-8817-4AF2-9561-C0F273ABF5D8}")), // Client id, 
				CComBSTR(_T("")),
				VARIANT_FALSE,
				VARIANT_FALSE,
				&pPartCustUIRibbonTab);
			if(FAILED(hr)) return hr;

			//create a new panel within the tab
			CComPtr<RibbonPanels> pRibbonPanels;
			hr = pPartCustUIRibbonTab->get_RibbonPanels(&pRibbonPanels);
			if(FAILED(hr)) return hr;

			CComPtr<RibbonPanel> pPartCustUIRibbonPanel;
			hr = pRibbonPanels->Add(CComBSTR(_T("CustomUI")), 
				CComBSTR(_T("Autodesk:CustomUI:CustomUIRibbonPanel")), 
				CComBSTR(_T("{B6CD8174-8817-4AF2-9561-C0F273ABF5D8}")), // Client id, 
				CComBSTR(_T("")),
				VARIANT_FALSE,
				&pPartCustUIRibbonPanel);
			if(FAILED(hr)) return hr;

			//add controls to the "CustUI" panel
			CComPtr<CommandControls> pPartCustUIRibbonPanelCtrls;
			hr = pPartCustUIRibbonPanel->get_CommandControls(&pPartCustUIRibbonPanelCtrls);

			if (SUCCEEDED(hr)){

				CComPtr<CommandControl> pCmd1CmdCtrl;
				hr = AddCommandButtonToCommandControls(m_pCmd1, pPartCustUIRibbonPanelCtrls, &pCmd1CmdCtrl);	
				ATLASSERT(SUCCEEDED(hr));

				CComPtr<CommandControl> pCmd2CmdCtrl;
				hr = AddCommandButtonToCommandControls(m_pCmd2, pPartCustUIRibbonPanelCtrls, &pCmd2CmdCtrl);	
				ATLASSERT(SUCCEEDED(hr));

				CComPtr<CommandControl> pCmd3CmdCtrl;
				hr = AddCommandButtonToCommandControls(m_pCmd3, pPartCustUIRibbonPanelCtrls, &pCmd3CmdCtrl);	
				ATLASSERT(SUCCEEDED(hr));

				CComPtr<CommandControl> pCmd4CmdCtrl;
				hr = AddCommandButtonToCommandControls(m_pCmd4, pPartCustUIRibbonPanelCtrls, &pCmd4CmdCtrl);	
				ATLASSERT(SUCCEEDED(hr));		
			}
			//End }

			//Append the command to an existing RibbonPanel: Format in Sketch ("id_PanelP_2DSketchFormat" from "id_TabSketch")
			//{ Begin
			CComPtr<RibbonTab> pPartSketchRibbonTab;
			hr = pRibbonTabs->get_Item(CComVariant(_T("id_TabSketch")), &pPartSketchRibbonTab);
			if(FAILED(hr)) return hr;

			CComPtr<RibbonPanels> pSketchRibbonPanels;
			hr = pPartSketchRibbonTab->get_RibbonPanels(&pSketchRibbonPanels);
			if(FAILED(hr)) return hr;

			CComPtr<RibbonPanel> pFormatRibbonPanel;
			hr = pSketchRibbonPanels->get_Item(CComVariant(_T("id_PanelP_2DSketchFormat")), &pFormatRibbonPanel);
			if(FAILED(hr)) return hr;

			//add controls to the panel
			CComPtr<CommandControls> pPartRibbonPanelCtrls;
			hr = pFormatRibbonPanel->get_CommandControls(&pPartRibbonPanelCtrls);

			if (SUCCEEDED(hr)){

				CComPtr<CommandControl> pCmd1CmdCtrl;
				hr = AddCommandButtonToCommandControls(m_pCmd1, pPartRibbonPanelCtrls, &pCmd1CmdCtrl);	
				ATLASSERT(SUCCEEDED(hr));

				CComPtr<CommandControl> pCmd2CmdCtrl;
				hr = AddCommandButtonToCommandControls(m_pCmd2, pPartRibbonPanelCtrls, &pCmd2CmdCtrl);	
				ATLASSERT(SUCCEEDED(hr));

				CComPtr<CommandControl> pCmd3CmdCtrl;
				hr = AddCommandButtonToCommandControls(m_pCmd3, pPartRibbonPanelCtrls, &pCmd3CmdCtrl);	
				ATLASSERT(SUCCEEDED(hr));

				CComPtr<CommandControl> pCmd4CmdCtrl;
				hr = AddCommandButtonToCommandControls(m_pCmd4, pPartRibbonPanelCtrls, &pCmd4CmdCtrl);	
				ATLASSERT(SUCCEEDED(hr));		
			}
			//End }
		}
	}

	// Advise to UserInputEvents
	// ContextMenu Sink so that it would Add 1, PopUp (2,3), & 4 to ContextMenu only if active env is Sketch.
	//	
	hr = pCmdMgr->get_UserInputEvents(&m_pUserInputEvents);
	ATLASSERT(SUCCEEDED(hr));
	if (SUCCEEDED(hr))
	{
		hr = UserInputEvtsSink::DispEventAdvise(m_pUserInputEvents);
		ATLASSERT(SUCCEEDED(hr));	
		if(FAILED(hr)) return hr;
	}

	// Advise to UserInterfaceEvents
	//	
	CComPtr<UserInterfaceManager> pUsrInterfaceMgr;
	hr = m_pApplication->get_UserInterfaceManager(&pUsrInterfaceMgr);
	ATLASSERT(SUCCEEDED(hr));
	if (SUCCEEDED(hr))
	{
		hr = pUsrInterfaceMgr->get_UserInterfaceEvents(&m_pUserInterfaceEvents);
		ATLASSERT(SUCCEEDED(hr));
		if(FAILED(hr)) return hr;

		hr = UserInterfaceEvtsSink::DispEventAdvise(m_pUserInterfaceEvents);
		ATLASSERT(SUCCEEDED(hr));	
		if(FAILED(hr)) return hr;
	}

	return hr;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CCustomUIAddInServer::Deactivate ()
{

	// Unsubcribe from all the events
	//

	// UserInputEvents
	//
	HRESULT hr = UserInputEvtsSink::DispEventUnadvise(m_pUserInputEvents);
	m_pUserInputEvents.Release();

	// UserInterfaceEvents
	//
	hr = UserInterfaceEvtsSink::DispEventUnadvise(m_pUserInterfaceEvents);
	m_pUserInterfaceEvents.Release();

	// Remove the buttons to the existing Sketch RibbonPanel ("id_PanelP_2DSketchFormat" from "id_TabSketch")
	hr = RemoveButtonsFromSketchPanel();
	ATLASSERT(SUCCEEDED(hr));

	// Release the button definitions handler classes
	//
	m_pCmd1->Cleanup();
	m_pCmd1->Release();
	
	m_pCmd2->Cleanup();
	m_pCmd2->Release();
	
	m_pCmd3->Cleanup();
	m_pCmd3->Release();

	m_pCmd4->Cleanup();
	m_pCmd4->Release();

	// Release the outstanding references
	//	
	m_pAddInSite.Release () ;
	m_pApplication.Release () ;


	return S_OK ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CCustomUIAddInServer::ExecuteCommand (long CommandID)
{
	return S_OK;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CCustomUIAddInServer::get_Automation (IDispatch * * ppResult)
{
	if ( ppResult == NULL )
		return E_POINTER ;
	*ppResult =NULL ;

	//return S_OK ; //----- If you do anything in there
	return E_NOTIMPL ;
}

HRESULT CCustomUIAddInServer::AddCommandButtonToCommandBar(CCmdHandler* pCmd, CommandBar* pCmdBar, CommandBarControl** pCmdCtrl)
{
	HRESULT hr = S_OK;

	// Add instance of the button to the tool bar as a control
	
	// Get the handle to the control definition of button
	//
	CComPtr<ButtonDefinitionObject> pBtnDef;
	hr = pCmd->GetButtonDefinition(&pBtnDef);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;

	// Add the button to the tool bar
	//
	CComPtr<CommandBarControls> pCmdBarCtrls;
	hr = pCmdBar->get_Controls(&pCmdBarCtrls);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;

	hr = pCmdBarCtrls->AddButton(pBtnDef, 0, pCmdCtrl);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;
	
	return hr;
}

HRESULT CCustomUIAddInServer::AddCommandToCommandCategory(CCmdHandler* pCmd, CommandCategory* pCmdCat)
{
	HRESULT hr = S_OK;

	// Get the handle to the control definition of button
	//
	CComPtr<ButtonDefinitionObject> pBtnDef;
	hr = pCmd->GetButtonDefinition(&pBtnDef);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;

	// Add the command to the command category
	//
	hr = pCmdCat->Add(pBtnDef);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;
	
	return hr;
}

HRESULT CCustomUIAddInServer::AddCommandBarToEnvPanelBar(CommandBar* pCmdBar, Environment* pEnv)
{
	HRESULT hr = S_OK;

	CComPtr<PanelBarObject> pPanelBar;
	hr = pEnv->get_PanelBar(&pPanelBar);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;

	CComPtr<CommandBarList> pCmdBarList;
	hr = pPanelBar->get_CommandBarList(&pCmdBarList);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;

	hr = pCmdBarList->Add(pCmdBar);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;

	return hr;
}

HRESULT CCustomUIAddInServer::AddPopUpToCommandBar(CommandBar* pPopUpCmdBar, CommandBar* pCmdBar, CommandBarControl** pPopUpCmdBarCtrl)
{
	HRESULT hr = S_OK;

	CComPtr<CommandBarControls> pCmdBarControls;
	hr = pCmdBar->get_Controls(&pCmdBarControls);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;

	hr = pCmdBarControls->AddPopup(pPopUpCmdBar, 0, pPopUpCmdBarCtrl);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;
	
	return hr;

}

HRESULT CCustomUIAddInServer::AddCommandButtonToCommandControls(CCmdHandler* pCmd, CommandControls* pCmdCtrls, CommandControl** pCmdCtrl)
{
	HRESULT hr = S_OK;

	// Add instance of the button to the CommandControls as a control

	// Get the handle to the control definition of button
	//
	CComPtr<ButtonDefinitionObject> pBtnDef;
	hr = pCmd->GetButtonDefinition(&pBtnDef);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;

	// Add the button to the Panel
	//
	hr = pCmdCtrls->AddButton(pBtnDef,
					VARIANT_FALSE,
					VARIANT_TRUE,
					CComBSTR(_T("")),
					VARIANT_FALSE,
					pCmdCtrl);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;

	return hr;
}

HRESULT CCustomUIAddInServer::RemoveButtonsFromSketchPanel()
{
	HRESULT hr = S_OK;

	// Only do it if this AddIn is not loaded in classical UI.
	CComPtr<UserInterfaceManager> pUserInterfaceMgr;
	hr = m_pApplication->get_UserInterfaceManager(&pUserInterfaceMgr);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;

	InterfaceStyleEnum interfaceStyle;
	hr = pUserInterfaceMgr->get_InterfaceStyle(&interfaceStyle);
	if(FAILED(hr)) return hr;

	// create the UI for the classic interface
	if(interfaceStyle != kClassicInterface)
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

		CComPtr<RibbonPanels> pSketchRibbonPanels;
		hr = pPartSketchRibbonTab->get_RibbonPanels(&pSketchRibbonPanels);
		if(FAILED(hr)) return hr;

		CComPtr<RibbonPanel> pFormatRibbonPanel;
		hr = pSketchRibbonPanels->get_Item(CComVariant(_T("id_PanelP_2DSketchFormat")), &pFormatRibbonPanel);
		if(FAILED(hr)) return hr;

		// get controls of the panel
		CComPtr<CommandControls> pPartRibbonPanelCtrls;
		hr = pFormatRibbonPanel->get_CommandControls(&pPartRibbonPanelCtrls);
		if(FAILED(hr)) return hr;

		// delete first command
		CComPtr<CommandControl> pCmd1;
		hr = pPartRibbonPanelCtrls->get_Item(CComVariant(_T("Autodesk:CustomUI:Cmd1")), &pCmd1);
		if(FAILED(hr)) return hr;

		hr = pCmd1->Delete();
		ATLASSERT(SUCCEEDED(hr));

		// delete second command
		CComPtr<CommandControl> pCmd2;
		hr = pPartRibbonPanelCtrls->get_Item(CComVariant(_T("Autodesk:CustomUI:Cmd2")), &pCmd2);
		if(FAILED(hr)) return hr;

		hr = pCmd2->Delete();
		ATLASSERT(SUCCEEDED(hr));

		// delete third command
		CComPtr<CommandControl> pCmd3;
		hr = pPartRibbonPanelCtrls->get_Item(CComVariant(_T("Autodesk:CustomUI:Cmd3")), &pCmd3);
		if(FAILED(hr)) return hr;

		hr = pCmd3->Delete();
		ATLASSERT(SUCCEEDED(hr));

		// delete forth command
		CComPtr<CommandControl> pCmd4;
		hr = pPartRibbonPanelCtrls->get_Item(CComVariant(_T("Autodesk:CustomUI:Cmd4")), &pCmd4);
		if(FAILED(hr)) return hr;

		hr = pCmd4->Delete();
		ATLASSERT(SUCCEEDED(hr));
	}

	return hr;
}

STDMETHODIMP CCustomUIAddInServer::OnContextMenu(SelectionDeviceEnum SelectionDevice, NameValueMap* AdditionalInfo, CommandBar* pCmdBar)
{
	HRESULT hr = S_OK;
	
	// Add 1, PopUp (2,3), & 4 to ContextMenu only if active env is Sketch.
	//
	CComPtr<CommandBarControl> pCmd1Ctrl;
	hr = AddCommandButtonToCommandBar(m_pCmd1, pCmdBar, &pCmd1Ctrl);
	ATLASSERT(SUCCEEDED(hr));
	if (SUCCEEDED(hr))
		hr = pCmd1Ctrl->put_GroupBegins(VARIANT_TRUE);

	// Add Popup
	CComPtr<UserInterfaceManager> pUserInterfaceMgr;
	hr = m_pApplication->get_UserInterfaceManager(&pUserInterfaceMgr);
	if (SUCCEEDED(hr))
	{

		CComPtr<CommandBars> pCmdBars;
		hr = pUserInterfaceMgr->get_CommandBars(&pCmdBars);
		if (SUCCEEDED(hr))
		{
			CComPtr<CommandBar> pCmdBarPopUp1;
			hr = pCmdBars->get_Item(CComVariant(_T("Autodesk:CustomUI:CmdPopUp1")), &pCmdBarPopUp1);

			if (hr != S_OK || pCmdBarPopUp1 == NULL)
			{
				hr = pCmdBars->Add(CComBSTR(_T("Command PopUp1")), // Display name
									CComBSTR(_T("Autodesk:CustomUI:CmdPopUp1")), // Internal name
									kPopUpCommandBar, // Command bar type 
									CComVariant(_T("{B6CD8174-8817-4AF2-9561-C0F273ABF5D8}")), // Client id
									&pCmdBarPopUp1);
				ATLASSERT(SUCCEEDED(hr));
				if (SUCCEEDED(hr))
				{
					CComPtr<CommandBarControl> pCmd2Ctrl;
					hr = AddCommandButtonToCommandBar(m_pCmd2, pCmdBarPopUp1, &pCmd2Ctrl);
					ATLASSERT(SUCCEEDED(hr));

					CComPtr<CommandBarControl> pCmd3Ctrl;
					hr = AddCommandButtonToCommandBar(m_pCmd3, pCmdBarPopUp1, &pCmd3Ctrl);
					ATLASSERT(SUCCEEDED(hr));
				}
			}

			CComPtr<CommandBarControl> pCmdBarPopup1Ctrl;
			AddPopUpToCommandBar(pCmdBarPopUp1, pCmdBar, &pCmdBarPopup1Ctrl);
			if (SUCCEEDED(hr))
				hr = pCmdBarPopup1Ctrl->put_GroupBegins(VARIANT_TRUE);
		}
	}

	// Add 4 to Popup
	//
	CComPtr<CommandBarControl> pCmd4Ctrl;
	hr = AddCommandButtonToCommandBar(m_pCmd4, pCmdBar, &pCmd4Ctrl);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;
	
	return hr;
}

STDMETHODIMP CCustomUIAddInServer::OnResetCommandBars(ObjectsEnumerator* pCmdBarObjEnumerator, NameValueMap* Context)
{
	HRESULT hr = S_OK;

	// Get the part environment and its default toolbar name, we will need to check if
	// this has been reset, if so, customize it again
	//

	CComBSTR bstrPartEnvToolBarIntName;

	// Get the user interface manager which provides access to command bars, environments
	//
	CComPtr<UserInterfaceManager> pUserInterfaceMgr;
	hr = m_pApplication->get_UserInterfaceManager(&pUserInterfaceMgr);
	ATLASSERT(SUCCEEDED(hr));
	if(SUCCEEDED(hr)) 
	{
		CComPtr<Environments> pEnvs;
		hr = pUserInterfaceMgr->get_Environments(&pEnvs);
		ATLASSERT(SUCCEEDED(hr));
		if(SUCCEEDED(hr)) 
		{
			// Get the part environment from the environments collection
			//
			CComPtr<Environment> pPartEnv;
			hr = pEnvs->get_Item(CComVariant(_T(PartEnvironment_InternalName)), &pPartEnv);
			ATLASSERT(SUCCEEDED(hr));
			if (SUCCEEDED(hr))
			{
				// Get the default tool bar
				//
				CComPtr<CommandBar> pPartEnvDefaultToolBar;
				hr = pPartEnv->get_DefaultToolBar(&pPartEnvDefaultToolBar);
				ATLASSERT(SUCCEEDED(hr));
				if (SUCCEEDED(hr))
				{
					// Get the default tool bar's internal name
					//
					hr = pPartEnvDefaultToolBar->get_InternalName(&bstrPartEnvToolBarIntName);	
					ATLASSERT(SUCCEEDED(hr));
				}
			}
		}
	}
	
	long lNoCmdBars;
	hr = pCmdBarObjEnumerator->get_Count(&lNoCmdBars);
	
	for (long lCmdBarCt = 1; lCmdBarCt <= lNoCmdBars; lCmdBarCt++)
	{
		CComPtr<IDispatch> pCmdBarDisp;
		hr = pCmdBarObjEnumerator->get_Item(lCmdBarCt, &pCmdBarDisp);
		
		CComQIPtr<CommandBar> pCmdBar(pCmdBarDisp);

		CComBSTR bstrCmdBarInternalName;
		hr = pCmdBar->get_InternalName(&bstrCmdBarInternalName);
		
		// check if the CmdBar1 command bar has been reset, if so, customize it again
		//
		if (bstrCmdBarInternalName == _T("Autodesk:CustomUI:CmdBar1"))
		{
			// ADD THE FOUR COMMANDS TO THE COMMAND BAR
			// Add Command1 to the Command Bar
			//
			CComPtr<CommandBarControl> pCmd1CmdBar1Ctrl;
			hr = AddCommandButtonToCommandBar(m_pCmd1, pCmdBar, &pCmd1CmdBar1Ctrl);	
			ATLASSERT(SUCCEEDED(hr));

			// Add Command2 to the Command Bar
			//
			CComPtr<CommandBarControl> pCmd2CmdBar1Ctrl;
			hr = AddCommandButtonToCommandBar(m_pCmd2, pCmdBar, &pCmd2CmdBar1Ctrl);	
			ATLASSERT(SUCCEEDED(hr));
	
			// Add Command3 to the Command Bar
			//
			CComPtr<CommandBarControl> pCmd3CmdBar1Ctrl;
			hr = AddCommandButtonToCommandBar(m_pCmd3, pCmdBar, &pCmd3CmdBar1Ctrl);	
			ATLASSERT(SUCCEEDED(hr));
	
			// Add Command4 to the Command Bar
			//
			CComPtr<CommandBarControl> pCmd4CmdBar1Ctrl;
			hr = AddCommandButtonToCommandBar(m_pCmd4, pCmdBar, &pCmd4CmdBar1Ctrl);	
			ATLASSERT(SUCCEEDED(hr));

		}

		// check if the part environment's menu bar has been reset, if so, customize it again
		//
		if (bstrCmdBarInternalName == _T("PartMenuBar"))
		{
			// Add the Command Bar as a popup to the Menu bar for the part environment
			//
			CComPtr<UserInterfaceManager> pUserInterfaceMgr;
			hr = m_pApplication->get_UserInterfaceManager(&pUserInterfaceMgr);
			ATLASSERT(SUCCEEDED(hr));
			if(FAILED(hr)) continue;

			// Get the Command Bar1
			CComPtr<CommandBars> pCmdBars;
			hr = pUserInterfaceMgr->get_CommandBars(&pCmdBars);
			ATLASSERT(SUCCEEDED(hr));
			if(FAILED(hr)) continue;

			CComPtr<CommandBar> pCmdBar1;
			hr = pCmdBars->get_Item(CComVariant(_T("Autodesk:CustomUI:CmdBar1")), &pCmdBar1);
			ATLASSERT(SUCCEEDED(hr));
			if(FAILED(hr)) continue;

			// Add the Command Bar as a popup to the Menu bar
			//
			CComPtr<CommandBarControl> pCmdBar1PartEnvDefaultMenuBarCtrl;
			hr = AddPopUpToCommandBar(pCmdBar1, pCmdBar, &pCmdBar1PartEnvDefaultMenuBarCtrl);
			ATLASSERT(SUCCEEDED(hr));
		}

		// check if the part environment's default toolbar has been reset, if so, customize it again
		//
		if (bstrCmdBarInternalName == bstrPartEnvToolBarIntName)
		{
			// Add Command Buttons 3, and 4 to the environment Tool bar
			// 
			CComPtr<CommandBarControl> pCmd3PartEnvDefaultToolBarCtrl;
			hr = AddCommandButtonToCommandBar(m_pCmd3, pCmdBar, &pCmd3PartEnvDefaultToolBarCtrl);
			ATLASSERT(SUCCEEDED(hr));

			CComPtr<CommandBarControl> pCmd4PartEnvDefaultToolBarCtrl;
			hr = AddCommandButtonToCommandBar(m_pCmd4, pCmdBar, &pCmd4PartEnvDefaultToolBarCtrl);
			ATLASSERT(SUCCEEDED(hr));
		}

		// check if the CmdPopUp1 command bar has been reset, if so, customize it again
		//
		if (bstrCmdBarInternalName == _T("Autodesk:CustomUI:CmdPopUp1"))
		{
			CComPtr<CommandBarControl> pCmd2Ctrl;
			hr = AddCommandButtonToCommandBar(m_pCmd2, pCmdBar, &pCmd2Ctrl);
			ATLASSERT(SUCCEEDED(hr));

			CComPtr<CommandBarControl> pCmd3Ctrl;
			hr = AddCommandButtonToCommandBar(m_pCmd3, pCmdBar, &pCmd3Ctrl);
			ATLASSERT(SUCCEEDED(hr));

		}
		
	}
	
	return hr;
}

STDMETHODIMP CCustomUIAddInServer::OnResetEnvironments(ObjectsEnumerator* pEnvObjEnumerator, NameValueMap* Context)
{
	HRESULT hr = S_OK;

	// Get the CmdBar1 command bar, if the part environment has been reset, we will
	// need to add the CmdBar1 command bar back to the part environment's panel bar
	//
	CComPtr<UserInterfaceManager> pUserInterfaceMgr;
	hr = m_pApplication->get_UserInterfaceManager(&pUserInterfaceMgr);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;

	CComPtr<CommandBars> pCmdBars;
	hr = pUserInterfaceMgr->get_CommandBars(&pCmdBars);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;

	CComPtr<CommandBar> pCmdBar1;
	hr = pCmdBars->get_Item(CComVariant(_T("Autodesk:CustomUI:CmdBar1")), &pCmdBar1);
	ATLASSERT(SUCCEEDED(hr));
	if(FAILED(hr)) return hr;

	long lNoEnvs;
	hr = pEnvObjEnumerator->get_Count(&lNoEnvs);
	
	for (long lEnvCt = 1; lEnvCt <= lNoEnvs; lEnvCt++)
	{
		CComPtr<IDispatch> pEnvDisp;
		hr = pEnvObjEnumerator->get_Item(lEnvCt, &pEnvDisp);
		
		CComQIPtr<Environment> pEnv(pEnvDisp);

		CComBSTR bstrEnvInternalName;
		hr = pEnv->get_InternalName(&bstrEnvInternalName);
		
		if (bstrEnvInternalName == _T(PartEnvironment_InternalName))
		{
			// Add the CmdBar1 command bar to the Panel Bar for the environment
			//
			hr = AddCommandBarToEnvPanelBar(pCmdBar1, pEnv);
			ATLASSERT(SUCCEEDED(hr));

			return S_OK;
		
		}
	}

	return hr;
}

STDMETHODIMP CCustomUIAddInServer::OnResetRibbonInterface(NameValueMap* pContext)
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

	//Introduce RibbonTab(“CustomUI”).RibbonPanels(“CustomUI”)
	//{ Begin
	CComPtr<RibbonTab> pPartCustUIRibbonTab;
	hr = pRibbonTabs->Add(CComBSTR(_T("CustomUI")), 
		CComBSTR(_T("Autodesk:CustomUI:CustomUIRibbonTab")), 
		CComBSTR(_T("{B6CD8174-8817-4AF2-9561-C0F273ABF5D8}")), // Client id, 
		CComBSTR(_T("")),
		VARIANT_FALSE,
		VARIANT_FALSE,
		&pPartCustUIRibbonTab);
	if(FAILED(hr)) return hr;

	//create a new panel within the tab
	CComPtr<RibbonPanels> pRibbonPanels;
	hr = pPartCustUIRibbonTab->get_RibbonPanels(&pRibbonPanels);
	if(FAILED(hr)) return hr;

	CComPtr<RibbonPanel> pPartCustUIRibbonPanel;
	hr = pRibbonPanels->Add(CComBSTR(_T("CustomUI")), 
		CComBSTR(_T("Autodesk:CustomUI:CustomUIRibbonPanel")), 
		CComBSTR(_T("{B6CD8174-8817-4AF2-9561-C0F273ABF5D8}")), // Client id, 
		CComBSTR(_T("")),
		VARIANT_FALSE,
		&pPartCustUIRibbonPanel);
	if(FAILED(hr)) return hr;

	//add controls to the "CustUI" panel
	CComPtr<CommandControls> pPartCustUIRibbonPanelCtrls;
	hr = pPartCustUIRibbonPanel->get_CommandControls(&pPartCustUIRibbonPanelCtrls);

	if (SUCCEEDED(hr)){

		CComPtr<CommandControl> pCmd1CmdCtrl;
		hr = AddCommandButtonToCommandControls(m_pCmd1, pPartCustUIRibbonPanelCtrls, &pCmd1CmdCtrl);	
		ATLASSERT(SUCCEEDED(hr));

		CComPtr<CommandControl> pCmd2CmdCtrl;
		hr = AddCommandButtonToCommandControls(m_pCmd2, pPartCustUIRibbonPanelCtrls, &pCmd2CmdCtrl);	
		ATLASSERT(SUCCEEDED(hr));

		CComPtr<CommandControl> pCmd3CmdCtrl;
		hr = AddCommandButtonToCommandControls(m_pCmd3, pPartCustUIRibbonPanelCtrls, &pCmd3CmdCtrl);	
		ATLASSERT(SUCCEEDED(hr));

		CComPtr<CommandControl> pCmd4CmdCtrl;
		hr = AddCommandButtonToCommandControls(m_pCmd4, pPartCustUIRibbonPanelCtrls, &pCmd4CmdCtrl);	
		ATLASSERT(SUCCEEDED(hr));		
	}
	//End }

	//Append the command to an existing RibbonPanel: Format in Sketch ("id_PanelP_2DSketchFormat" from "id_TabSketch")
	//{ Begin
	CComPtr<RibbonTab> pPartSketchRibbonTab;
	hr = pRibbonTabs->get_Item(CComVariant(_T("id_TabSketch")), &pPartSketchRibbonTab);
	if(FAILED(hr)) return hr;


	CComPtr<RibbonPanels> pSketchRibbonPanels;
	hr = pPartSketchRibbonTab->get_RibbonPanels(&pSketchRibbonPanels);
	if(FAILED(hr)) return hr;

	CComPtr<RibbonPanel> pFormatRibbonPanel;
	hr = pSketchRibbonPanels->get_Item(CComVariant(_T("id_PanelP_2DSketchFormat")), &pFormatRibbonPanel);
	if(FAILED(hr)) return hr;

	//add controls to the panel
	CComPtr<CommandControls> pPartRibbonPanelCtrls;
	hr = pFormatRibbonPanel->get_CommandControls(&pPartRibbonPanelCtrls);

	if (SUCCEEDED(hr)){

		CComPtr<CommandControl> pCmd1CmdCtrl;
		hr = AddCommandButtonToCommandControls(m_pCmd1, pPartRibbonPanelCtrls, &pCmd1CmdCtrl);	
		ATLASSERT(SUCCEEDED(hr));

		CComPtr<CommandControl> pCmd2CmdCtrl;
		hr = AddCommandButtonToCommandControls(m_pCmd2, pPartRibbonPanelCtrls, &pCmd2CmdCtrl);	
		ATLASSERT(SUCCEEDED(hr));

		CComPtr<CommandControl> pCmd3CmdCtrl;
		hr = AddCommandButtonToCommandControls(m_pCmd3, pPartRibbonPanelCtrls, &pCmd3CmdCtrl);	
		ATLASSERT(SUCCEEDED(hr));

		CComPtr<CommandControl> pCmd4CmdCtrl;
		hr = AddCommandButtonToCommandControls(m_pCmd4, pPartRibbonPanelCtrls, &pCmd4CmdCtrl);	
		ATLASSERT(SUCCEEDED(hr));		
	}
	//End }

	return hr;
}

