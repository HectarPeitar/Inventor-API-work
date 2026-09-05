//-----------------------------------------------------------------------------
//----- CustomCommandAddInServer.cpp : Implementation of CCustomCommandAddInServer
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "../CustomCommand.h"
#include "CustomCommandAddInServer.h"

//-----------------------------------------------------------------------------
STDMETHODIMP CCustomCommandAddInServer::Activate (IDispatch *pDisp, VARIANT_BOOL FirstTime)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState ());

	HRESULT hr;

	if (pDisp == NULL) return E_INVALIDARG;

	hr = pDisp->QueryInterface (__uuidof (m_pAddInSite), reinterpret_cast<void**>(&m_pAddInSite)) ;
	ATLASSERT(SUCCEEDED(hr));
	if (FAILED(hr))	return hr;
	
	//----- get the Inventor application object
	hr = m_pAddInSite->get_Application (&m_pApplication);
	ATLASSERT(SUCCEEDED(hr));
	if (FAILED(hr))	return hr;

	//create the command button(s)
	//create instance of the "Rack Face" command class 
	hr = CComObject<CRackFaceCmd>::CreateInstance (&m_pRackFaceCmd);
	if (FAILED(hr))	return hr;

	m_pRackFaceCmd->AddRef();

	//create the "Rack Face" button
	CComPtr<ButtonDefinitionObject> pRackFaceCmdBtnDefObj;
	hr = m_pRackFaceCmd->CreateButton(m_pApplication, CComBSTR(_T("Rack Face")), CComBSTR(_T("Autodesk:CustomCommand:RackFaceCmd")), kShapeEditCmdType, CComVariant(_T("{05CC5326-B165-483A-8A2A-4B52B7A54BEF}")), CComBSTR(_T("Creates a rack feature")), CComBSTR(_T("Creates a rack feature")), CComVariant(_T("")), CComVariant(_T("")), kDisplayTextInLearningMode, false, &pRackFaceCmdBtnDefObj);
	if (FAILED(hr))	return hr;

	//create change definitons
	//create instance of the "Rack Face" change definition class 
	hr = CComObject<CRackFaceDefinition>::CreateInstance (&m_pRackFaceDefinition);
	if (FAILED(hr))	return hr;

	m_pRackFaceDefinition->AddRef();

	//create the "Rack Face" change definition
	hr = m_pRackFaceDefinition->Create(m_pApplication, CComBSTR(_T("Rack Face")), CComBSTR(_T("Autodesk:CustomCommand:RackFaceChgDef")));
	if (FAILED(hr))	return hr;

	//create command category
	//get the command manager
	CComPtr<CommandManager> pCommandManager;
	hr = m_pApplication->get_CommandManager(&pCommandManager);
	if (FAILED(hr)) return hr;

	//get the command categories collection
	CComPtr<CommandCategories> pCommandCategories;
	hr = pCommandManager->get_CommandCategories(&pCommandCategories);

	//create the command categories for this AddIn
	CComPtr<CommandCategory> pRackFaceCmdCat;
	hr = pCommandCategories->Add(CComBSTR(_T("Rack Face")), CComBSTR(_T("Autodesk:CustomCommand:RackFaceCmdCat")), CComVariant(_T("{05CC5326-B165-483A-8A2A-4B52B7A54BEF}")), &pRackFaceCmdCat);
	if (FAILED(hr)) return hr;

	//add the "Rack Face" command to the command category
	hr = pRackFaceCmdCat->Add(pRackFaceCmdBtnDefObj);
	if (FAILED(hr)) return hr;

	if (FirstTime != VARIANT_FALSE){

		//add the button to the part features toolbar
		CComPtr<UserInterfaceManager> pUserInterfaceMgr;
		hr = m_pApplication->get_UserInterfaceManager(&pUserInterfaceMgr);
		if (FAILED(hr))	return hr;

		//get the command bars collection
		CComPtr<CommandBars> pCommandBars;
		hr = pUserInterfaceMgr->get_CommandBars(&pCommandBars);
		if (FAILED(hr))	return hr;

		//get the part features toolbar
		CComPtr<CommandBar> pPartFeaturesToolBar;
		hr = pCommandBars->get_Item(CComVariant(_T(PartFeaturesToolBar_InternalName)), &pPartFeaturesToolBar);
		if (FAILED(hr))	return hr;

		//add the "Rack Face" button to the toolbar
		//get the controls of the toolbar
		CComPtr<CommandBarControls> pPartFeaturesToolBarCtrls;
		hr = pPartFeaturesToolBar->get_Controls(&pPartFeaturesToolBarCtrls);
		if (FAILED(hr))	return hr;

		//add the button as one of the controls
		CComPtr<CommandBarControl> pRackFaceCmdBtnCmdBarCtrl;
		hr = pPartFeaturesToolBarCtrls->AddButton(pRackFaceCmdBtnDefObj, 0, &pRackFaceCmdBtnCmdBarCtrl);
		if (FAILED(hr))	return hr;

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

//-----------------------------------------------------------------------------
STDMETHODIMP CCustomCommandAddInServer::Deactivate ()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr;

	//remove the command button(s)
	//remove the "Rack Face" button
	hr = m_pRackFaceCmd->RemoveButton();

	m_pRackFaceCmd->Release();
	m_pRackFaceCmd = NULL;
	
	//delete change definition(s)
	//remove the "Rack Face" change definition
	hr = m_pRackFaceDefinition->Remove();

	m_pRackFaceDefinition->Release();
	m_pRackFaceDefinition = NULL;

	//unadvise UserInterfaceEvents
	hr = DispEventUnadvise(m_pUserInterfaceEvtsObj);
	
	m_pAddInSite.Release();
	m_pApplication.Release();

	return S_OK ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CCustomCommandAddInServer::ExecuteCommand (long CommandID)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	return E_NOTIMPL;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CCustomCommandAddInServer::get_Automation (IDispatch **ppResult)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState ());

	if (ppResult == NULL) 
		return E_INVALIDARG;

	*ppResult = NULL;

	return E_NOTIMPL;
}

//-----------------------------------------------------------------------------
//----- Implementation of UserInterface Events sink methods
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
STDMETHODIMP CCustomCommandAddInServer::OnResetCommandBars(ObjectsEnumerator* pCommandBars, NameValueMap* pContext)
{
	HRESULT hr = S_OK;

	long lNoCmdBars;
	hr = pCommandBars->get_Count(&lNoCmdBars);
	
	for (long lCmdBarCt = 1; lCmdBarCt <= lNoCmdBars; lCmdBarCt++)
	{
		CComPtr<IDispatch> pCmdBarDisp;
		hr = pCommandBars->get_Item(lCmdBarCt, &pCmdBarDisp);
		
		CComQIPtr<CommandBar> pCmdBar(pCmdBarDisp);

		CComBSTR bstrCmdBarInternalName;
		hr = pCmdBar->get_InternalName(&bstrCmdBarInternalName);
		
		//add the "Rack Face" button back to the part features toolbar
		if (bstrCmdBarInternalName == _T(PartFeaturesToolBar_InternalName))
		{
			//get the "Rack Face" button definition
			CComPtr<ButtonDefinitionObject> pRackFaceCmdBtnDefObj;
			hr = m_pRackFaceCmd->GetButtonDefinition(&pRackFaceCmdBtnDefObj);
			if(FAILED(hr)) return hr;
			
			//get the controls of the command bar
			CComPtr<CommandBarControls> pCmdBarCtrls;
			hr = pCmdBar->get_Controls(&pCmdBarCtrls);
			if (FAILED(hr))	return hr;

			//add the button as one of the controls
			CComPtr<CommandBarControl> pRackFaceCmdBtnCmdBarCtrl;
			hr = pCmdBarCtrls->AddButton(pRackFaceCmdBtnDefObj, 0, &pRackFaceCmdBtnCmdBarCtrl);
			if (FAILED(hr))	return hr;

			return S_OK;
		}
		
	}	
	return hr;
}

STDMETHODIMP CCustomCommandAddInServer::OnEnvironmentChange(Environment* pEnvironment, EnvironmentStateEnum EnvironmentState, EventTimingEnum BeforeOrAfter, NameValueMap* pContext, HandlingCodeEnum* HandlingCode)
{
	HRESULT hr = S_OK;
	
	CComBSTR bstrEnvInternalName;
	hr = pEnvironment->get_InternalName(&bstrEnvInternalName);
	if (FAILED(hr))	return hr;

	if (bstrEnvInternalName == _T(PartEnvironment_InternalName))
	{
		//get the "Rack Face" button definition
		CComPtr<ButtonDefinitionObject> pRackFaceCmdBtnDefObj;
		hr = m_pRackFaceCmd->GetButtonDefinition(&pRackFaceCmdBtnDefObj);
		if(FAILED(hr)) return hr;

		//enable the "Rack Face" button when the part environment is activated or resumed
		if (EnvironmentState == kActivateEnvironmentState || EnvironmentState == kResumeEnvironmentState)
		{
			hr = pRackFaceCmdBtnDefObj->put_Enabled(VARIANT_TRUE);
			if(FAILED(hr)) return hr;
		}

		//disable the "Rack Face" button when the part environment is terminated or suspended
		if (EnvironmentState == kTerminateEnvironmentState || EnvironmentState == kSuspendEnvironmentState)
		{
			hr = pRackFaceCmdBtnDefObj->put_Enabled(VARIANT_FALSE);
			if(FAILED(hr)) return hr;
		}

	}

	*HandlingCode = kEventNotHandled;

	return hr;

}


