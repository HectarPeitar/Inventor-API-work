//-----------------------------------------------------------------------------
//----- RackFaceCmd.cpp : Implementation of CRackFaceCmd
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "RackFaceCmd.h"

//-----------------------------------------------------------------------------
STDMETHODIMP CRackFaceCmd::ButtonDefinitionEvents_OnExecute (NameValueMap *pContext) 
{ 		
	HRESULT hr;

	//if command was already started, stop it first
	if (m_bCommandIsRunning) StopCommand();

	//start new command
	hr = StartCommand();
	if (FAILED(hr)) return hr;		

	return S_OK; 	
}

HRESULT CRackFaceCmd::StartCommand()
{	
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr;

	//call base command button's StartCommand (to also start interaction)
	hr = CCommand::StartCommand();
	if (FAILED(hr)) return hr;

	//implement this command specific functionality
	//subscribe to desired interaction event(s)
	hr = SubscribeToEvent(CInteraction::kSelection);
	if (FAILED(hr)) return hr;
	
	//initialize interaction graphics objects
	hr = InitializePreviewGraphics();

	//display the command dialog to accept the input parameters
	long lApplicationMainFrameHWND;
	hr = m_pApplication->get_MainFrameHWND(&lApplicationMainFrameHWND);			

	//create and display the dialog
	m_pRackFaceCmdDlg = new RackFaceCmdDlg(m_pApplication, this);
	
	if(m_pRackFaceCmdDlg != NULL){

		m_pRackFaceCmdDlg->Create(IDD_RACKFACEDIALOG, CWnd::FromHandle((HWND)lApplicationMainFrameHWND));				
		m_pRackFaceCmdDlg->ShowWindow(SW_SHOW);

	}

	//initialize this command's data members
	m_pRackFace = NULL;
	m_pRackEdge = NULL;

	//enable interaction
	hr = EnableInteraction();
	if (FAILED(hr)) return hr;

	return S_OK;
}

HRESULT CRackFaceCmd::ExecuteCommand()
{	
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr;

	bool bMethodFailed = false;

	//stop the command (to disconnect interaction events, interaction graphics and dismiss command dialog)
	hr = StopCommand();
	if (FAILED(hr)) bMethodFailed = true;

	//create the rack face request
	m_pRackFaceRequest = new CRackFaceRequest(m_pApplication, m_pRackFace, m_pRackEdge, m_iNoTeeth, m_dRackHeight, m_dRackWidth, m_dRackExtents, m_kRackFeatureExtentDirection);

	//execute the request
	CComPtr<Document> pActiveDocument;
	hr = m_pApplication->get_ActiveDocument(&pActiveDocument);

	hr = ExecuteChangeRequest(m_pRackFaceRequest, CComVariant(_T("Autodesk:CustomCommand:RackFaceChgDef")), pActiveDocument);
	if (FAILED (hr)) bMethodFailed = true;

	//delete the request
	delete m_pRackFaceRequest;

	if (bMethodFailed) return E_FAIL;
	else return S_OK;
}

HRESULT CRackFaceCmd::StopCommand()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr;

	//implement this command specific functionality
	TerminatePreviewGraphics();
		
	//destroy the command dialog
	m_pRackFaceCmdDlg->DestroyWindow();
	m_pRackFaceCmdDlg = NULL;	

	//call base command button's StopCommand (to disconnect interaction sinks)
	hr = CCommand::StopCommand();
	if (FAILED(hr)) return hr;

	return S_OK;	
}

HRESULT CRackFaceCmd::EnableInteraction()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr;
	
	//call base command button's Enable Interaction 
	hr = CCommand::EnableInteraction();
	if (FAILED(hr)) return hr;

	//implement this command specific functionality
	//clear selection filter
	hr = m_pSelectEvtsObj->ClearSelectionFilter();

	//reset selections
	hr = m_pSelectEvtsObj->ResetSelections();	

	//specify selection filter and cursor
	if(m_pRackFaceCmdDlg->m_SelectRackFaceButton.GetCheck() == BST_CHECKED){

		if(m_pRackEdge != NULL)
			m_pSelectEvtsObj->AddToSelectedEntities(m_pRackEdge);

		//set the selection filter to a planar face
		hr = m_pSelectEvtsObj->AddSelectionFilter(kPartFacePlanarFilter);

		//set a cursor to specify face selection
		hr = m_pInteractionEvtsObj->SetCursor(kCursorBuiltInCrosshair);	

		//set the status bar message
		hr = m_pInteractionEvtsObj->put_StatusBarText(CComBSTR(_T("Select a planar face with atleast one linear edge")));
	
	}
	else{

		if(m_pRackFace != NULL)
			m_pSelectEvtsObj->AddToSelectedEntities(m_pRackFace);

		//set the selection filter to a linear edge
		hr = m_pSelectEvtsObj->AddSelectionFilter(kPartEdgeLinearFilter);

		//set a cursor to specify edge selection
		hr = m_pInteractionEvtsObj->SetCursor(kCursorBuiltInArrowCursor);

		//set the status bar message
		hr = m_pInteractionEvtsObj->put_StatusBarText(CComBSTR(_T("Select a linear edge on the selected face")));

	}

	return S_OK;
}

HRESULT CRackFaceCmd::DisableInteraction()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr;
	
	//call base command button's Disable Interaction 
	hr = CCommand::DisableInteraction();
	if (FAILED(hr)) return hr;

	//implement this command specific functionality
	//set the default cursor to notify that selection is not active
	hr = m_pInteractionEvtsObj->SetCursor(kCursorBuiltInArrow);

	return S_OK;
}

//-----------------------------------------------------------------------------
//----- Implementation of Callbacks
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//----- Implementation of SelectEvents callbacks
//-----------------------------------------------------------------------------
HRESULT CRackFaceCmd::SelectEvents_OnPreSelect(IDispatch **ppPreSelectEntity, VARIANT_BOOL *pDoHighlight, ObjectCollection **ppMorePreSelectEntities, SelectionDeviceEnum SelectionDevice, Point *pModelPosition, Point2d *pViewPosition, View *pView)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr;

	*pDoHighlight = VARIANT_FALSE;

	//get the selected entity type
	ObjectTypeEnum SelectedEntityType;
	hr = Rx::GetObjectType(*ppPreSelectEntity, &SelectedEntityType);
	if (FAILED(hr)) return hr;

	//if rack face is being pre-selected, if edge has been selected already
	//highlight the face only if the already selected edge belongs to the face
	if (SelectedEntityType == kFaceObject){

		if (m_pRackEdge != NULL){

			CComQIPtr<Face> pPreSelectFace(*ppPreSelectEntity);
			if (pPreSelectFace == NULL) return E_FAIL;	
			
			CComPtr<Edges> pEdges;
			hr = pPreSelectFace->get_Edges(&pEdges);
			if (FAILED(hr)) return hr;

			long lNoEdges;
			hr = pEdges->get_Count(&lNoEdges);
			if (FAILED(hr)) return hr;

			for(long lEdgeCt = 1; lEdgeCt <= lNoEdges; lEdgeCt++){

				CComPtr<Edge> pEdge;
				hr = pEdges->get_Item(lEdgeCt, &pEdge);
				if (FAILED(hr)) continue;

				if (pEdge == m_pRackEdge){
					*pDoHighlight = VARIANT_TRUE;
					break;
				}				

			}
		}
		else
			*pDoHighlight = VARIANT_TRUE;

	}
	
	//if rack edge is being pre-selected, if face has been selected already
	//highlight the edge only if the edge belongs to the already selected face
	if (SelectedEntityType == kEdgeObject){
	
		if (m_pRackFace != NULL){

			CComQIPtr<Edge> pPreSelectEdge(*ppPreSelectEntity);
			if (pPreSelectEdge == NULL) return E_FAIL;
			
			CComPtr<Edges> pEdges;
			hr = m_pRackFace->get_Edges(&pEdges);
			if (FAILED(hr)) return hr;

			long lNoEdges;
			hr = pEdges->get_Count(&lNoEdges);
			if (FAILED(hr)) return hr;

			for(long lEdgeCt = 1; lEdgeCt <= lNoEdges; lEdgeCt++){

				CComPtr<Edge> pEdge;
				hr = pEdges->get_Item(lEdgeCt, &pEdge);
				if (FAILED(hr)) continue;

				if (pEdge == pPreSelectEdge){
					*pDoHighlight = VARIANT_TRUE;
					break;
				}				

			}
		}
		else
			*pDoHighlight = VARIANT_TRUE;
			
	}
		
	return S_OK;
}

HRESULT CRackFaceCmd::SelectEvents_OnSelect (ObjectsEnumerator *pJustSelectedEntities, SelectionDeviceEnum SelectionDevice, Point *pModelPosition, Point2d *pViewPosition, View *pView)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr;

	long lNoSelectedEntities;
	hr = pJustSelectedEntities->get_Count(&lNoSelectedEntities);
		
	if (lNoSelectedEntities > 0) 
	{
		CComPtr<IDispatch> pSelectedEntity;
		hr = pJustSelectedEntities->get_Item(1, &pSelectedEntity);
		if(FAILED(hr)) return hr;

		//get the selected entity type
		ObjectTypeEnum SelectedEntityType;
		hr = Rx::GetObjectType(pSelectedEntity, &SelectedEntityType);
		if (FAILED(hr)) return hr;

		//if face is selected
		if ((m_pRackFaceCmdDlg->m_SelectRackFaceButton.GetCheck() == BST_CHECKED) && (SelectedEntityType == kFaceObject)){

			//get the selected face, if face had been previously selected, set it to NULL
			m_pRackFace = NULL;
			hr = pSelectedEntity.QueryInterface(&m_pRackFace);
			if (FAILED(hr)) return hr;

			//un-check rack face selection button
			m_pRackFaceCmdDlg->m_SelectRackFaceButton.SetCheck(BST_UNCHECKED);

			//if edge has not been selected, start selection for it
			if(m_pRackEdge == NULL){

				//change icon to specify face has been selected
				m_pRackFaceCmdDlg->m_SelectRackFaceButton.SetIcon(AfxGetApp()->LoadIcon(IDI_SELECTED));

				//check rack direction selection button
				m_pRackFaceCmdDlg->m_SelectRackDirectionButton.SetCheck(BST_CHECKED);

				//start direction selection
				hr = EnableInteraction();
			}
			else{

				//disable selection
				hr = DisableInteraction();

				hr = UpdateCommandStatus();

			}

		}
		
		//if edge is selected
		if ((m_pRackFaceCmdDlg->m_SelectRackDirectionButton.GetCheck() == BST_CHECKED) && (SelectedEntityType == kEdgeObject)){
		
			//get the selected edge, if edge had been previously selected, set it to NULL
			m_pRackEdge = NULL;
			hr = pSelectedEntity.QueryInterface(&m_pRackEdge);
			if (FAILED(hr)) return hr;

			//change icon to specify edge has been selected
			m_pRackFaceCmdDlg->m_SelectRackDirectionButton.SetIcon(AfxGetApp()->LoadIcon(IDI_SELECTED));

			//un-check rack direction selection button
			m_pRackFaceCmdDlg->m_SelectRackDirectionButton.SetCheck(BST_UNCHECKED);
			
			//disable selection
			hr = DisableInteraction();

			hr = UpdateCommandStatus();

		}
		
	}	

	return S_OK;
}

//-----------------------------------------------------------------------------
//----- Implementation of InteractionEvents callbacks
//-----------------------------------------------------------------------------
HRESULT CRackFaceCmd::InteractionEvents_OnHelp(EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr;

	//get the help manager object
	CComPtr<HelpManager> pHelpManager;
	hr = m_pApplication->get_HelpManager(&pHelpManager);
	if (FAILED(hr)) return hr;

	//display the start page of the "Inventor API" help
	hr = pHelpManager->DisplayHelpTopic(_T("ADMAPI_17_0.chm"), _T(""));
	if (FAILED(hr)) return hr;

	return S_OK;

}

//-----------------------------------------------------------------------------
//----- End of Callbacks
//-----------------------------------------------------------------------------

HRESULT CRackFaceCmd::UpdateCommandStatus()
{
	HRESULT hr;

	//get the rack parameters from the rack command dialog
	m_pRackFaceCmdDlg->UpdateData(TRUE);

	//by default, disable the OK button on dialog
	//enable it later if all parameters are valid
	m_pRackFaceCmdDlg->m_OKButton.EnableWindow(FALSE);

	//validate all parameters
	m_iNoTeeth = _tstoi((LPCTSTR)m_pRackFaceCmdDlg->m_strNoTeeth);

	hr = GetValueFromExpression(m_pRackFaceCmdDlg->m_strRackHeight, &m_dRackHeight);
	if (FAILED(hr)) return hr;

	hr = GetValueFromExpression(m_pRackFaceCmdDlg->m_strRackWidth, &m_dRackWidth);
	if (FAILED(hr)) return hr;

	hr = GetValueFromExpression(m_pRackFaceCmdDlg->m_strRackExtents, &m_dRackExtents);
	if (FAILED(hr)) return hr;

	switch (m_pRackFaceCmdDlg->m_iRackExtentsDirection){
	case 0:
		m_kRackFeatureExtentDirection = kNegativeExtentDirection;
		break;
	case 1:
		m_kRackFeatureExtentDirection = kPositiveExtentDirection;
		break;
	case 2:
		m_kRackFeatureExtentDirection = kSymmetricExtentDirection;
	}

	//if all rack face parameters are alright, update the preview graphics and enable "OK" button
	if (m_pRackFace != NULL && m_pRackEdge != NULL && m_iNoTeeth > 0 && m_dRackHeight > 0 && m_dRackWidth > 0 && m_dRackExtents > 0){
		
		//update the preview
		hr = UpdatePreviewGraphics();

		//enable the OK button on dialog
		m_pRackFaceCmdDlg->m_OKButton.EnableWindow(TRUE);
	}

	return S_OK;

}

HRESULT CRackFaceCmd::GetValueFromExpression(CString strExpression, double *dValue)
{
	HRESULT hr;

	*dValue = 0.0;

	//get the active document
	CComPtr<Document> pActiveDocument;
	hr = m_pApplication->get_ActiveDocument(&pActiveDocument);
	if (FAILED(hr)) return hr;

	//get the units of measure object
	CComPtr<UnitsOfMeasure> pUnitsOfMeasure;
	hr = pActiveDocument->get_UnitsOfMeasure(&pUnitsOfMeasure);
	if (FAILED(hr)) return hr;

	//get the current length units of the user
	UnitsTypeEnum kLengthUnitsType;
	hr = pUnitsOfMeasure->get_LengthUnits(&kLengthUnitsType);
	if (FAILED(hr)) return hr;

	//convert the expression to the current length units of user
	hr = pUnitsOfMeasure->GetValueFromExpression(CComBSTR(strExpression), CComVariant(kLengthUnitsType) , dValue);
	if (FAILED(hr)) return hr;

	return S_OK;

}
