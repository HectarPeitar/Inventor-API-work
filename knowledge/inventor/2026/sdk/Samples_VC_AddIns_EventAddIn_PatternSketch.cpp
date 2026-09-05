

///////////////////////////////////////////////////////////////////////////////
// 
// class: PatternSketchCmd
// 
// This is an example takes a selected lines, selects the lines connected to 
// line and then patterns the selected geometry. It does not add constraints
// to the copied items.  This is an example of using the OnPreSelect callback 
// to place other connected objects in the select set.
//
// To use this example command, add a rectangle to a sketch and then select
// the Pattern Sketch command found in the Tools Menu.
//

#include "stdafx.h"
#include "patternsketch.h"

//////////////////////////////////////////////////////////////////////////////
//  Constructor - Initialize data to appropriate values
//////////////////////////////////////////////////////////////////////////////
PatternSketchCmd::PatternSketchCmd(Application* pApplication):
m_xOffset(1), m_yOffset(1), m_yOccurences(2), m_xOccurences(2), m_pApplication(pApplication)
{}


PatternSketchCmd::~PatternSketchCmd()
{
	m_pInteractionObject = NULL;
}

//////////////////////////////////////////////////////////////////////////////
// PatternSketchCmd::BeginCommand
//
//  Begin Command is called when the menu item for the command is selected. It
//  creates the InteractionObject and SelectObject. It starts the command by calling
//  Start on the InteractionObject.
//////////////////////////////////////////////////////////////////////////////
void PatternSketchCmd::BeginCommand()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT Result = NOERROR;
	CComQIPtr<CommandManager> pCommandManager;
    
	// Get the command manager
    Result = m_pApplication->get_CommandManager(&pCommandManager);
	if (FAILED (Result)) 
		return;

	// Create the Interaction Object
	m_pInteractionObject = NULL;
	Result = pCommandManager->CreateInteractionEvents(&m_pInteractionObject);
	if (FAILED (Result)) 
		return;

	// Create your Interaction Event Handler
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
	
	// Create the Select Events Object
	m_pInteractionObject->get_SelectEvents(&m_pSelectEventsObject);
	m_pSelectEventsObject->AddSelectionFilter(kSketchCurveLinearFilter);
	Result = m_pSelectEvents->DispEventAdvise( m_pSelectEventsObject );
	if (FAILED (Result)) 
		return;

	m_pSelectEvents->SetParent(this);

	// Start the command
	// Must always start command AFTER hooking up the interaction and 
	// select event handlers. Else the OnActivate() method on 
	// CInteractionEventHandler will not get a hit.
	//
	Result = m_pInteractionObject->Start();
	if (FAILED (Result)) 
		return;

	CComPtr<View> pActiveView;
	Result = m_pApplication->get_ActiveView(&pActiveView);
	
	// Create the Dialog
	m_pDialog = new PatternSketchDialog(m_pInteractionObject, this);
	ASSERT_VALID(m_pDialog);

	if (pActiveView !=	NULL) 
		m_pDialog->SetActiveView(pActiveView);

	LONG_PTR lMainFrameHWND = m_pApplication->MainFrameHWND;
	m_pDialog->Create(IDD_PATTERNSKETCH, CWnd::FromHandle((HWND)lMainFrameHWND));

	m_pDialog->ShowWindow(SW_SHOW);

}

/////////////////////////////////////////////////////////////////////////////////////////////
//
// PatternSketchCmd::ExecutePatternCmd
//
// ExecutePatternCmd is called after the user hits the okay button on the Pattern Sketch Dialog.
// It takes the selected lines and copies them using the tranform the user selects.
//
/////////////////////////////////////////////////////////////////////////////////////////////
void PatternSketchCmd::ExecutePatternCmd()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT Result = NOERROR;
	EndCommand(false);

	// Obtain the active sketch being edited
	CComPtr<IDispatch> pObject;
	Result = m_pApplication->get_ActiveEditObject(&pObject);
	if (FAILED(Result) || !pObject) 
		return;

	CComQIPtr<PlanarSketch> pSketch(pObject);
	if (pSketch) 
	{
		// Get the sketch lines collection
		CComPtr<SketchLines> pSketchLines;
		Result = pSketch->get_SketchLines(&pSketchLines);
		if (FAILED(Result) || !pSketchLines) 
			return;

		// Get the number of items to offset
		long numItems;
		Result = m_pObjectsToOffset->get_Count(&numItems);
		if (FAILED(Result)) 
			return;

		double yOffset = 0;
		
		for (int iyOcc = 0; iyOcc < m_yOccurences; iyOcc++) 
		{
			double xOffset = 0;

			for (int ixOcc = 0; ixOcc < m_xOccurences; ixOcc++) 
			{
				if (xOffset || yOffset) 
				{   //skip over the first occurence
					for (int i = 1; i <= numItems; i++) 
					{
						// Get the item selected
						CComPtr<IDispatch> pSLObject;
						Result = m_pObjectsToOffset->get_Item(i, &pSLObject);
						if(FAILED(Result))
							return;

						CComQIPtr<SketchLine> pSketchLine(pSLObject);

						// Transform the X coordinate and Y coordinate of the start point
						CComPtr<SketchLine> pNewSketchLine;
						CComPtr<Point2d> pStartPoint;
						CComPtr<SketchPoint> pSketchStartPoint;
						Result = pSketchLine->get_StartSketchPoint(&pSketchStartPoint);
						if(FAILED(Result))
							return;

						Result = pSketchStartPoint->get_Geometry(&pStartPoint);
						if(FAILED(Result))
							return;

						double x, y;
						Result = pStartPoint->get_X(&x);
						if(FAILED(Result))
							return;

						x += xOffset;

						Result = pStartPoint->put_X(x);
						if(FAILED(Result))
							return;

						Result = pStartPoint->get_Y(&y);
						if(FAILED(Result))
							return;

						y += yOffset;
						Result = pStartPoint->put_Y(y);
						if(FAILED(Result))
							return;

						// Transform the X coordinate and Y coordinate of the end point
						CComPtr<Point2d> pEndPoint;
						CComPtr<SketchPoint> pSketchEndPoint;
						Result = pSketchLine->get_EndSketchPoint(&pSketchEndPoint);
						if(FAILED(Result))
							return;

						Result = pSketchEndPoint->get_Geometry(&pEndPoint);
						if(FAILED(Result))
							return;

						Result = pEndPoint->get_X(&x);
						if(FAILED(Result))
							return;
						x += xOffset;
						Result = pEndPoint->put_X(x);

						// create a new sketch line
						Result = pEndPoint->get_Y(&y);
						if(FAILED(Result))
							return;

						y += yOffset;
						Result = pEndPoint->put_Y(y);
						if(FAILED(Result))
							return;

						Result = pSketchLines->AddByTwoPoints(pStartPoint, pEndPoint, &pNewSketchLine);
						if(FAILED(Result))
							return;
					}
				}

				xOffset += m_xOffset;
			}

			yOffset += m_yOffset;
		} // end of for yOcc
	}

	m_pObjectsToOffset = NULL;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
// PatternSketchCmd::CancelCommand
//
// CancelCommand is called from the interaction events OnTerminate. This usually means
// the that client has hit escape or executed another another command.
//
/////////////////////////////////////////////////////////////////////////////////////////////
void PatternSketchCmd::CancelCommand()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	m_pDialog->EndDialog(IDCANCEL);
	EndCommand(true);
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
// PatternSketchCmd::EndCommand
//
// EndCommand is called as a final step to disconnnect the event sinks either after 
// the actual command functionality has been executed ("OK" button pressed) or when 
// the command is terminated ("Cancel" button pressed or "Esc" key pressed).
//
/////////////////////////////////////////////////////////////////////////////////////////////
void PatternSketchCmd::EndCommand(bool cancelled)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	if (m_pInteractionObject != NULL) 
	{
		m_pSelectEvents->DispEventUnadvise(m_pSelectEventsObject);
		m_pSelectEvents->Release();

		m_pInteractionEvents->DispEventUnadvise(m_pInteractionObject);
		m_pInteractionEvents->Release();
		if (!cancelled) 
			m_pInteractionObject->Stop();  // Don't stop an already stopped interaction object.

		m_pSelectEventsObject = NULL;
		delete m_pDialog;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
// PatternSketchCmd::SetSelectedObjects
//
// This is called from OnSelect. It places the items to be selected into the member
// m_pObjectsToOffset.
//
/////////////////////////////////////////////////////////////////////////////////////////////
void PatternSketchCmd::SetSelectedObjects(ObjectsEnumerator* pObjectsToOffset) 
{	
	AFX_MANAGE_STATE (AfxGetStaticModuleState());
	m_pObjectsToOffset = pObjectsToOffset;

	// Selection has been made, allow OK on dialog.
	m_pDialog->GetDlgItem(IDOK)->EnableWindow(TRUE);
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
// PatternSketchCmd::OnPreSelect
//
// OnPreSelect is called from the SelectHandler. Every time the user crosses over an item
// this is called.  We take the selected line and then add all lines attached to it to the
// MorePreSelectEntities ObjectCollection.
//
/////////////////////////////////////////////////////////////////////////////////////////////
HRESULT PatternSketchCmd::OnPreSelect(IDispatch * * PreSelectEntity, VARIANT_BOOL * DoHighlight,
									struct ObjectCollection * * MorePreSelectEntities,
									enum SelectionDeviceEnum SelectionDevice,
									struct Point * ModelPosition, struct Point2d * ViewPosition,
									struct View * View)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT Result=NOERROR;

	// Set the highlight to true
	VARIANT_BOOL bHighlight = VARIANT_TRUE;
	DoHighlight = &bHighlight;

	CComQIPtr<SketchLine> pSketchLine(*PreSelectEntity);

	// if there is a sketch line
	if (pSketchLine) 
	{
		// get the sketch lines endpoints
		CComPtr<SketchPoint> pStartSketchPoint;
		CComPtr<SketchPoint> pFirstSketchPoint;
		Result = pSketchLine->get_StartSketchPoint(&pFirstSketchPoint);
		OnErrorReturn(FAILED(Result), Result);

		CComPtr<SketchPoint> pEndSketchPoint;
		Result = pSketchLine->get_EndSketchPoint(&pEndSketchPoint);
		OnErrorReturn(FAILED(Result), Result);

		if (pEndSketchPoint) 
		{
			// get the items attached to the endpoint
			CComPtr<SketchEntitiesEnumerator> pSketchEntityEnumerator;		 
			Result = pEndSketchPoint->get_AttachedEntities(&pSketchEntityEnumerator);
			OnErrorReturn(FAILED(Result), Result);

			long numItems;
			Result = pSketchEntityEnumerator->get_Count(&numItems);
			OnErrorReturn(FAILED(Result), Result);

			CComPtr<TransientObjects> pTransientObject = NULL;
			CComVariant ObjectEnumerator;

			// if there is more than one start traversing
			if (numItems > 1) 
			{
				GetApplication()->get_TransientObjects (&pTransientObject);
				pTransientObject->CreateObjectCollection(ObjectEnumerator, MorePreSelectEntities);
			}

			bool done = false;
			while (!done && numItems > 1) 
			{
			  // for each item attached
			  for (int i = 1; i <= numItems; i++) 
			  {
					CComPtr<SketchEntity> pSketchEntity;
					Result = pSketchEntityEnumerator->get_Item(i, &pSketchEntity);
					OnErrorReturn(FAILED(Result), Result);

					CComQIPtr<SketchLine> pConnectedSketchLine(pSketchEntity);
					if (pConnectedSketchLine) 
					{
						if(pConnectedSketchLine != pSketchLine) 
						{
							(*MorePreSelectEntities)->Add(pConnectedSketchLine);
							pEndSketchPoint = NULL;
							pStartSketchPoint = NULL;
							Result = pConnectedSketchLine->get_EndSketchPoint(&pEndSketchPoint);
							OnErrorReturn(FAILED(Result), Result);

							Result = pConnectedSketchLine->get_StartSketchPoint(&pStartSketchPoint);
							OnErrorReturn(FAILED(Result), Result);

							if (pEndSketchPoint == pFirstSketchPoint || pStartSketchPoint == pFirstSketchPoint) 
							{
								done = true;
								break;
							} 
							else 
							{
								pSketchEntityEnumerator = NULL;
								Result = pEndSketchPoint->get_AttachedEntities(&pSketchEntityEnumerator);
								OnErrorReturn(FAILED(Result), Result);

								Result = pSketchEntityEnumerator->get_Count(&numItems);
								OnErrorReturn(FAILED(Result), Result);
							}
					  }
				  }
			  } //end of for			  
			} // end - While
	  }
  }

  return Result;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
// PatternSketchCmd::OnSelect
//
// OnSelect is called after the user accepts these selections by clicking the left mouse button.
//
/////////////////////////////////////////////////////////////////////////////////////////////
 HRESULT PatternSketchCmd::OnSelect(      
		ObjectsEnumerator * JustSelectedEntities,
        SelectionDeviceEnum SelectionDevice,
        Point * ModelPosition,
        Point2d * ViewPosition,
        View * View)
 {
	 AFX_MANAGE_STATE (AfxGetStaticModuleState());
     HRESULT Result=NOERROR;
	 SetSelectedObjects(JustSelectedEntities);
	 return Result;
 }
