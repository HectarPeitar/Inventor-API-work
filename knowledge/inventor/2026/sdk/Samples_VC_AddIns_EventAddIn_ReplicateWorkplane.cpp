
///////////////////////////////////////////////////////////////////////////////
// 
// class: ReplicateWorkplaneCmd
// 
// This is an example takes a selected Workplane, the number of occurrences
// and an offset distance and replicates the selected workplane.
//
// To use this example command, select the Replicate Workplane command 
// found in the Tools > Sample Command Menu. The dialog will prompt you
// to select a workplane and specify the distance and number of occurrences.
//


#include "stdafx.h"
#include "replicateworkplane.h"
#include "replicateworkplanedlg.h"

///////////////////////////////////////////////////////////////////
//
//ReplicateWorkplaneCmd::ReplicateWorkplaneCmd-Constructor
//
///////////////////////////////////////////////////////////////////
ReplicateWorkplaneCmd::ReplicateWorkplaneCmd(Application* pApplication):
m_dOffset(3), m_pApplication(pApplication), m_dNumOccurences(1)
{}

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
ReplicateWorkplaneCmd::~ReplicateWorkplaneCmd()
{
	m_pInteractionObject = NULL;
}



///////////////////////////////////////////////////////////////////
//
//  ReplicateWorkplaneCmd::BeginCommand
// 
//  BeginCommand is called when the menu item for the command is selected. It
//  creates the InteractionObject and SelectObject. It starts the command by calling
//  Start on the InteractionObject.
///////////////////////////////////////////////////////////////////
void ReplicateWorkplaneCmd::BeginCommand()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());
	HRESULT Result = NOERROR;
	
	// Create the interaction object
	CComQIPtr<CommandManager> pCommandManager;   
    Result = m_pApplication->get_CommandManager(&pCommandManager);
	
    if (FAILED(Result)) 
		return;

	m_pInteractionObject = NULL;
	Result = pCommandManager->CreateInteractionEvents(&m_pInteractionObject);
	if (FAILED (Result)) 
		return;

	// Create the Interaction Event Handler
	CComObject<CInteractionEventHandler>* pInteractionEvents;
	Result = CComObject<CInteractionEventHandler>::CreateInstance( &pInteractionEvents);
	if (FAILED (Result)) 
		return;

	m_pInteractionEvents = pInteractionEvents;
	m_pInteractionEvents->AddRef();

	Result = m_pInteractionEvents->DispEventAdvise(m_pInteractionObject);
	if (FAILED (Result)) 
		return;

	m_pInteractionEvents->SetParent(this);

	// Create the Select Event Handler
	CComObject<CSelectEventHandler>* pSelectEvents;
	Result = CComObject<CSelectEventHandler>::CreateInstance( &pSelectEvents);
	if (FAILED (Result)) 
		return;

	m_pSelectEvents = pSelectEvents;
	m_pSelectEvents->AddRef();

	Result = m_pInteractionObject->get_SelectEvents(&m_pSelectEventsObject);
	if (FAILED (Result)) 
		return;

	Result = m_pSelectEventsObject->AddSelectionFilter(kWorkPlaneFilter);
	if (FAILED (Result)) 
		return;

	Result = m_pSelectEvents->DispEventAdvise( m_pSelectEventsObject );
	if (FAILED (Result)) 
		return;

	m_pSelectEvents->SetParent(this);
	
	// Start the command
	// Must always start command AFTER hooking up the interaction and 
	// select event handlers. Else, the OnActivate() method on 
	// CInteractionEventHandler will not get a hit.
	//
	Result = m_pInteractionObject->Start();
	if (FAILED (Result)) 
		return;
	
	CComPtr<View> pActiveView;
	Result = m_pApplication->get_ActiveView(&pActiveView);

	// Create the Dialog
	m_pDialog = new ReplicateWorkplaneDialog(m_pInteractionObject, this);
	ASSERT_VALID(m_pDialog);

	if (pActiveView !=	NULL) 
		m_pDialog->SetActiveView(pActiveView);

	LONG_PTR lMainFrameHWND = m_pApplication->MainFrameHWND;
	m_pDialog->Create(IDD_REPLICATEWORKPLANE, CWnd::FromHandle((HWND)lMainFrameHWND));

	m_pDialog->ShowWindow(SW_SHOW);

}

///////////////////////////////////////////////////////////////////
//
//  ReplicateWorkplaneCmd::ExecuteReplicateWorkplaneCmd
//
// ExecutePatternCmd is called after the user hits the okay 
// button on the Replicate Workplane Dialog.
// It takes the selected Workplane, the number of occurrences
// and an offset distance and replicates the selected workplane.
//
///////////////////////////////////////////////////////////////////
void ReplicateWorkplaneCmd::ExecuteReplicateWorkplaneCmd()
{		
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT Result = NOERROR;
	CComPtr<Document>  pDoc;
	Result = m_pApplication->get_ActiveDocument(&pDoc);
	if (FAILED(Result)) 
		return;

	// Get the part document
	CComQIPtr<PartDocument> pPartDoc(pDoc);

	if (pPartDoc)
	{

		// Get the part component definition
		CComPtr<PartComponentDefinition> pPartCompDef;
		Result = pPartDoc->get_ComponentDefinition(&pPartCompDef);
		if (FAILED(Result))
			return;

		// Get the workplanes
		CComPtr<WorkPlanes> pWorkPlanes;				
		Result = pPartCompDef->get_WorkPlanes(&pWorkPlanes);
		if (FAILED(Result)) 
			return;

		double dOffset = 0;
		VARIANT_BOOL construction = VARIANT_FALSE;
		for (int ii = 0; ii < m_dNumOccurences; ii++) 
		{
			CComPtr<WorkPlane> pNewWorkPlane;
			dOffset += m_dOffset;
			CComVariant offset(dOffset);
			Result = pWorkPlanes->AddByPlaneAndOffset(m_pWorkplaneToOffset, offset, construction, &pNewWorkPlane);
		}
	}

	EndCommand(false);
}


///////////////////////////////////////////////////////////////////
//
// CancelCommand is called from the interaction events OnTerminate. This usually means
// the that client has hit escape or executed another another command.
//
///////////////////////////////////////////////////////////////////
void ReplicateWorkplaneCmd::CancelCommand()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	m_pDialog->EndDialog(IDCANCEL);
	EndCommand(true);
}


///////////////////////////////////////////////////////////////////
//
// ReplicateWorkplaneCmd::EndCommand
//
// EndCommand is called as a final step to disconnnect the event sinks either after 
// the actual command functionality has been executed ("OK" button pressed) or when 
// the command is terminated ("Cancel" button pressed or "Esc" key pressed).
//
///////////////////////////////////////////////////////////////////
void ReplicateWorkplaneCmd::EndCommand(bool cancelled)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	m_pWorkplaneToOffset = NULL;
	if (m_pInteractionObject != NULL) 
	{
		delete m_pDialog;
		m_pSelectEvents->DispEventUnadvise( m_pSelectEventsObject );
		m_pSelectEvents->Release();

		m_pInteractionEvents->DispEventUnadvise(m_pInteractionObject);
		m_pInteractionEvents->Release();
		if (!cancelled)
			m_pInteractionObject->Stop(); // don't stop an already "stopped" interaction event

		m_pSelectEventsObject = NULL;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
// ReplicateWorkplaneCmd::SetWorkplaneToOffset
//
// This is called from OnSelect. It places the items to be selected into the member
// m_pWorkplaneToOffset.
//
/////////////////////////////////////////////////////////////////////////////////////////////
void ReplicateWorkplaneCmd::SetWorkplaneToOffset(WorkPlane* pWorkplane)
{
	m_pWorkplaneToOffset = pWorkplane;
	m_pDialog->GetDlgItem(IDOK)->EnableWindow(TRUE);
}


///////////////////////////////////////////////////////////////////
//
// ReplicateWorkplaneCmd::OnSelect
//
// OnSelect is called after the user accepts these selections by clicking the left mouse button.
//
/////////////////////////////////////////////////////////////////////////////////////////////
HRESULT ReplicateWorkplaneCmd::OnSelect( ObjectsEnumerator * JustSelectedEntities,
										 SelectionDeviceEnum SelectionDevice, Point * ModelPosition,
										 Point2d * ViewPosition, View * View)
{
	long numItems;
	HRESULT Result = JustSelectedEntities->get_Count(&numItems);
	OnErrorReturn(FAILED(Result), Result);
	
	CComPtr<IDispatch> pObject;
	if (numItems == 1) 
	{
		Result = JustSelectedEntities->get_Item(1, &pObject);
		OnErrorReturn(FAILED(Result), Result);

		CComQIPtr<WorkPlane> pWorkplane(pObject);
		if (pWorkplane) 
			SetWorkplaneToOffset(pWorkplane);
	}

	return Result;
}