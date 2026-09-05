//-----------------------------------------------------------------------------
//----- Interaction.cpp : Implementation of CInteraction
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "CustomCommand.h"
#include "Interaction.h"
#include "Command.h"

HRESULT CInteraction::StartInteraction (Application* pApplication, BSTR bstrInteractionName, InteractionEventsObject **ppInteractionEvtsObj)
{	
	HRESULT hr;

	//get the command manager object
	CComPtr<CommandManager> pCommandManager;   
    hr = pApplication->get_CommandManager(&pCommandManager);
	if (FAILED(hr)) return hr;

	//create the interaction events object
	hr = pCommandManager->CreateInteractionEvents(&m_pInteractionEvtsObj);
	if (FAILED(hr)) return hr;

	//connect event handler in order to receive interaction events
	hr = InteractionEvtsSink::DispEventAdvise(m_pInteractionEvtsObj);
	if (FAILED(hr)) return hr;

	//set then name for the interaction events
	hr = m_pInteractionEvtsObj->put_Name(bstrInteractionName);
	
	//start the interaction
	hr = m_pInteractionEvtsObj->Start();
	if (FAILED(hr)) return hr;

	//return a copy of the interaction events object
	hr = m_pInteractionEvtsObj.CopyTo(ppInteractionEvtsObj);
	if (FAILED(hr)) return hr;

	return S_OK;	
}

HRESULT CInteraction::StopInteraction()
{
	HRESULT hr = S_OK;

	//disconnect interaction events sink
	if (m_pInteractionEvtsObj != NULL) 
	{
		hr = InteractionEvtsSink::DispEventUnadvise(m_pInteractionEvtsObj);	

		m_pInteractionEvtsObj = NULL;	
		
	}

	return hr;
}

HRESULT CInteraction::SubscribeToEvent(InteractionTypeEnum InteractionType, IDispatch **ppEvtsObj)
{
	HRESULT hr;

	//check if already subscribed to
	int iInteractionEvtsCount{ 0 };
	for(iInteractionEvtsCount = 0; iInteractionEvtsCount < m_kInteractionType.GetSize(); iInteractionEvtsCount++){

		if(InteractionType == m_kInteractionType[iInteractionEvtsCount]){
			
			return S_OK;

		}
	}

	//if not already subsribed to then, subscribe
	m_kInteractionType.Add(InteractionType);

	switch(InteractionType){

	case kSelection:
		
		//create the select events object
		hr = m_pInteractionEvtsObj->get_SelectEvents(&m_pSelectEvtsObj);
		if (FAILED(hr)) return hr;

		//connect event handler in order to receive select events
		hr = SelectEvtsSink::DispEventAdvise(m_pSelectEvtsObj);
		if (FAILED(hr)) return hr;

		//specify burn through
		hr = m_pSelectEvtsObj->put_PreSelectBurnThrough(VARIANT_TRUE);

		hr = m_pSelectEvtsObj.QueryInterface(ppEvtsObj);
		if (FAILED(hr)) return hr;

		break;

	case kMouse:
		
		//create the mouse events object
		hr = m_pInteractionEvtsObj->get_MouseEvents(&m_pMouseEvtsObj);
		if (FAILED(hr)) return hr;

		//connect event handler in order to receive mouse events
		hr = MouseEvtsSink::DispEventAdvise(m_pMouseEvtsObj);
		if (FAILED(hr)) return hr;

		hr = m_pMouseEvtsObj.QueryInterface(ppEvtsObj);
		if (FAILED(hr)) return hr;

		break;

	case kTriad:
		
		//create the triad events object
		hr = m_pInteractionEvtsObj->get_TriadEvents(&m_pTriadEvtsObj);
		if (FAILED(hr)) return hr;

		//connect event handler in order to receive triad events
 		hr = TriadEvtsSink::DispEventAdvise(m_pTriadEvtsObj);
		if (FAILED(hr)) return hr;

		hr = m_pTriadEvtsObj.QueryInterface(ppEvtsObj);
		if (FAILED(hr)) return hr;

		break;
	}

	return S_OK;

}

HRESULT CInteraction::UnsubscribeFromEvents()
{	
	HRESULT hr = S_OK;

	int iInteractionEvtsCount{ 0 };
	for(iInteractionEvtsCount = 0; iInteractionEvtsCount < m_kInteractionType.GetSize(); iInteractionEvtsCount++){

		switch(m_kInteractionType[iInteractionEvtsCount]){
			
		case kSelection:

			//disconnect selection events sink
			if (m_pSelectEvtsObj != NULL){

				hr = SelectEvtsSink::DispEventUnadvise(m_pSelectEvtsObj);

				m_pSelectEvtsObj = NULL;
			
			}

			break;

		case kMouse:

			//disconnect mouse events sink
			if (m_pMouseEvtsObj != NULL){

				hr = MouseEvtsSink::DispEventUnadvise(m_pMouseEvtsObj);

				m_pMouseEvtsObj = NULL;
			
			}

			break;

		case kTriad:

			//disconnect triad events sink
			if (m_pTriadEvtsObj != NULL){

				hr = TriadEvtsSink::DispEventUnadvise(m_pTriadEvtsObj);

				m_pTriadEvtsObj = NULL;
			
			}

			break;

		}
	}
	
	m_kInteractionType.RemoveAll();

	return hr;
}

HRESULT CInteraction::EnableInteraction()
{	
	HRESULT hr;

	//enable events
	int iInteractionEvtsCount{ 0 };
	for(iInteractionEvtsCount = 0; iInteractionEvtsCount < m_kInteractionType.GetSize() ; iInteractionEvtsCount++){

		switch(m_kInteractionType[iInteractionEvtsCount]){
			
		case kSelection:

			//re-subscribe to selection events 
			if(m_pSelectEvtsObj == NULL){

				//create the select events object
				hr = m_pInteractionEvtsObj->get_SelectEvents(&m_pSelectEvtsObj);
				if (FAILED(hr)) return hr;

				//connect event handler in order to receive select events
				hr = SelectEvtsSink::DispEventAdvise(m_pSelectEvtsObj);
				if (FAILED(hr)) return hr;

				//specify burn through
				hr = m_pSelectEvtsObj->put_PreSelectBurnThrough(VARIANT_TRUE);

			}

			break;

		case kMouse:

			//re-subscribe to mouse events 
			if(m_pMouseEvtsObj == NULL){

				//create the mouse events object
				hr = m_pInteractionEvtsObj->get_MouseEvents(&m_pMouseEvtsObj);
				if (FAILED(hr)) return hr;

				//connect event handler in order to receive mouse events
				hr = MouseEvtsSink::DispEventAdvise(m_pMouseEvtsObj);
				if (FAILED(hr)) return hr;

			}

			break;

		case kTriad:

			//re-subscribe to triad events 
			if(m_pTriadEvtsObj == NULL){

				//create the triad events object
				hr = m_pInteractionEvtsObj->get_TriadEvents(&m_pTriadEvtsObj);
				if (FAILED(hr)) return hr;

				//connect event handler in order to receive triad events
				hr = TriadEvtsSink::DispEventAdvise(m_pTriadEvtsObj);
				if (FAILED(hr)) return hr;

			}

			break;

		}

	}
	
	return S_OK;
}

HRESULT CInteraction::DisableInteraction()
{		
	HRESULT hr = S_OK;

	//disable subscribed to events
	int iInteractionEvtsCount{ 0 };
	for(iInteractionEvtsCount = 0; iInteractionEvtsCount < m_kInteractionType.GetSize() ; iInteractionEvtsCount++){

		switch(m_kInteractionType[iInteractionEvtsCount]){
			
		case kSelection:

			//un-subscribe and delete selection events
			if (m_pSelectEvtsObj != NULL){

				hr = SelectEvtsSink::DispEventUnadvise(m_pSelectEvtsObj);

				m_pSelectEvtsObj = NULL;
			
			}

			break;

		case kMouse:

			//un-subscribe and delete mouse events 
			if (m_pMouseEvtsObj != NULL){

				hr = MouseEvtsSink::DispEventUnadvise(m_pMouseEvtsObj);

				m_pMouseEvtsObj = NULL;
			
			}

			break;

		case kTriad:

			//un-subscribe and delete triad events 
			if (m_pTriadEvtsObj != NULL){

				hr = TriadEvtsSink::DispEventUnadvise(m_pTriadEvtsObj);

				m_pTriadEvtsObj = NULL;
			
			}

			break;
		}
	}

	return hr;
}

void CInteraction::SetParentCmd(CCommand *pParentCmd)
{
	//store a copy of the parent command
	m_pParentCmd = pParentCmd;
}

//-----------------------------------------------------------------------------
//----- Implementation of Interaction Events sink methods
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
STDMETHODIMP CInteraction::InteractionEvents_OnTerminate ()
{	
	HRESULT hr;

	//terminate the command
	hr = m_pParentCmd->StopCommand();
	if (FAILED(hr)) return hr;

	return S_OK;	
}

//-----------------------------------------------------------------------------
STDMETHODIMP CInteraction::InteractionEvents_OnHelp (EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{	
	HRESULT hr;

	hr = m_pParentCmd->InteractionEvents_OnHelp(BeforeOrAfter, pContext, pHandlingCode);
	if (FAILED(hr)) return hr;

	return S_OK;	
}

//-----------------------------------------------------------------------------
//----- Implementation of Select Events sink methods
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
STDMETHODIMP CInteraction::SelectEvents_OnPreSelect (IDispatch **ppPreSelectEntity, VARIANT_BOOL *pDoHighlight, ObjectCollection **ppMorePreSelectEntities, SelectionDeviceEnum SelectionDevice, Point *pModelPosition, Point2d *pViewPosition, View *pView)
{
	HRESULT hr;

	hr = m_pParentCmd->SelectEvents_OnPreSelect(ppPreSelectEntity, pDoHighlight, ppMorePreSelectEntities, SelectionDevice, pModelPosition, pViewPosition, pView);
	if(FAILED(hr)) return hr;

	return S_OK;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CInteraction::SelectEvents_OnPreSelectMouseMove (IDispatch *pPreSelectEntity, Point *pModelPosition, Point2d *pViewPosition, View *pView)
{
	HRESULT hr;

	hr = m_pParentCmd->SelectEvents_OnPreSelectMouseMove(pPreSelectEntity, pModelPosition, pViewPosition, pView);
	if(FAILED(hr)) return hr;

	return S_OK;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CInteraction::SelectEvents_OnStopPreSelect (Point *pModelPosition, Point2d *pViewPosition, View *pView)
{
	HRESULT hr;

	hr = m_pParentCmd->SelectEvents_OnStopPreSelect(pModelPosition, pViewPosition, pView);
	if(FAILED(hr)) return hr;

	return S_OK;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CInteraction::SelectEvents_OnSelect (ObjectsEnumerator *pJustSelectedEntities, SelectionDeviceEnum SelectionDevice, Point *pModelPosition, Point2d *pViewPosition, View *pView)
{	
	HRESULT hr;

	hr = m_pParentCmd->SelectEvents_OnSelect(pJustSelectedEntities, SelectionDevice, pModelPosition, pViewPosition, pView);
	if(FAILED(hr)) return hr;

	return S_OK;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CInteraction::SelectEvents_OnUnSelect (ObjectsEnumerator *pUnSelectedEntities, SelectionDeviceEnum SelectionDevice, Point *pModelPosition, Point2d *pViewPosition, View *pView)
{
	HRESULT hr;

	hr = m_pParentCmd->SelectEvents_OnUnSelect (pUnSelectedEntities, SelectionDevice, pModelPosition, pViewPosition, pView);
	if(FAILED(hr)) return hr;

	return S_OK;
}

//-----------------------------------------------------------------------------
//----- Implementation of Mouse Events sink methods
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
STDMETHODIMP CInteraction::MouseEvents_OnMouseUp (MouseButtonEnum Button, ShiftStateEnum ShiftKeys, Point *pModelPosition, Point2d *pViewPosition, View *pView)
{
	HRESULT hr;

	hr = m_pParentCmd->MouseEvents_OnMouseUp (Button, ShiftKeys, pModelPosition, pViewPosition, pView);
	if(FAILED(hr)) return hr;

	return S_OK;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CInteraction::MouseEvents_OnMouseDown (MouseButtonEnum Button, ShiftStateEnum ShiftKeys, Point *pModelPosition, Point2d *pViewPosition, View *pView)
{
	HRESULT hr;

	hr = m_pParentCmd->MouseEvents_OnMouseDown (Button, ShiftKeys, pModelPosition, pViewPosition, pView);
	if(FAILED(hr)) return hr;

	return S_OK;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CInteraction::MouseEvents_OnMouseClick (MouseButtonEnum Button, ShiftStateEnum ShiftKeys, Point *pModelPosition, Point2d *pViewPosition, View *pView)
{
	HRESULT hr;

	hr = m_pParentCmd->MouseEvents_OnMouseClick (Button, ShiftKeys, pModelPosition, pViewPosition, pView);
	if(FAILED(hr)) return hr;

	return S_OK;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CInteraction::MouseEvents_OnMouseDoubleClick (MouseButtonEnum Button, ShiftStateEnum ShiftKeys, Point *pModelPosition, Point2d *pViewPosition, View *pView)
{
	HRESULT hr;

	hr = m_pParentCmd->MouseEvents_OnMouseDoubleClick (Button, ShiftKeys, pModelPosition, pViewPosition, pView);
	if(FAILED(hr)) return hr;

	return S_OK;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CInteraction::MouseEvents_OnMouseMove (MouseButtonEnum Button, ShiftStateEnum ShiftKeys, Point *pModelPosition, Point2d *pViewPosition, View *pView)
{
	HRESULT hr;

	hr = m_pParentCmd->MouseEvents_OnMouseMove (Button, ShiftKeys, pModelPosition, pViewPosition, pView);
	if(FAILED(hr)) return hr;

	return S_OK;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CInteraction::MouseEvents_OnMouseLeave (MouseButtonEnum Button, ShiftStateEnum ShiftKeys, View *pView)
{
	HRESULT hr;

	hr = m_pParentCmd->MouseEvents_OnMouseLeave (Button, ShiftKeys, pView);
	if(FAILED(hr)) return hr;

	return S_OK;
}

//-----------------------------------------------------------------------------
//----- Implementation of Triad Events sink methods
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
STDMETHODIMP CInteraction::TriadEvents_OnActivate (NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	HRESULT hr;

	if (pHandlingCode == NULL)
		return E_POINTER;	

	hr = m_pParentCmd->TriadEvents_OnActivate (pContext, pHandlingCode);
	if(FAILED(hr)) return hr;

	return S_OK;

}

//-----------------------------------------------------------------------------
STDMETHODIMP CInteraction::TriadEvents_OnEndMove (TriadSegmentEnum SelectedTriadSegment, ShiftStateEnum ShiftKeys, Matrix *pCoordinateSystem, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	HRESULT hr; 

	if (pHandlingCode == NULL)
		return E_POINTER ;

	hr = m_pParentCmd->TriadEvents_OnEndMove (SelectedTriadSegment, ShiftKeys, pCoordinateSystem, pContext, pHandlingCode);
	if(FAILED(hr)) return hr;

	return S_OK;

}

//----------------------------------------------------------------------------
STDMETHODIMP CInteraction::TriadEvents_OnMove (TriadSegmentEnum SelectedTriadSegment, ShiftStateEnum ShiftKeys, Matrix *pCoordinateSystem, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	HRESULT hr; 

	if (pHandlingCode == NULL)
		return E_POINTER ;

	hr = m_pParentCmd->TriadEvents_OnMove (SelectedTriadSegment, ShiftKeys, pCoordinateSystem, pContext, pHandlingCode);
	if(FAILED(hr)) return hr;

	return S_OK;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CInteraction::TriadEvents_OnEndSequence (VARIANT_BOOL Cancelled, Matrix *pCoordinateSystem, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	HRESULT hr; 

	if (pHandlingCode == NULL)
		return E_POINTER ;

	hr = m_pParentCmd->TriadEvents_OnEndSequence (Cancelled, pCoordinateSystem, pContext, pHandlingCode);
	if(FAILED(hr)) return hr;

	return S_OK;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CInteraction::TriadEvents_OnStartSequence (Matrix *pCoordinateSystem, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	HRESULT hr; 

	if (pHandlingCode == NULL)
		return E_POINTER ;

	hr = m_pParentCmd->TriadEvents_OnStartSequence (pCoordinateSystem, pContext, pHandlingCode);
	if(FAILED(hr)) return hr;

	return S_OK;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CInteraction::TriadEvents_OnMoveTriadOnlyToggle (VARIANT_BOOL MoveTriadOnly, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	HRESULT hr; 

	if (pHandlingCode == NULL)
		return E_POINTER ;

	hr = m_pParentCmd->TriadEvents_OnMoveTriadOnlyToggle (MoveTriadOnly, BeforeOrAfter, pContext, pHandlingCode);
	if(FAILED(hr)) return hr;

	return S_OK;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CInteraction::TriadEvents_OnStartMove (TriadSegmentEnum SelectedTriadSegment, ShiftStateEnum ShiftKeys, Matrix *pCoordinateSystem, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	HRESULT hr; 

	if (pHandlingCode == NULL)
		return E_POINTER ;

	hr = m_pParentCmd->TriadEvents_OnStartMove (SelectedTriadSegment, ShiftKeys, pCoordinateSystem, pContext, pHandlingCode);
	if(FAILED(hr)) return hr;

	return S_OK;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CInteraction::TriadEvents_OnTerminate (VARIANT_BOOL Cancelled, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	HRESULT hr; 

	if (pHandlingCode == NULL)
		return E_POINTER ;

	hr = m_pParentCmd->TriadEvents_OnTerminate (Cancelled, pContext, pHandlingCode);
	if(FAILED(hr)) return hr;

	return S_OK;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CInteraction::TriadEvents_OnSegmentSelectionChange (TriadSegmentEnum SelectedTriadSegment, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode)
{
	HRESULT hr; 

	if (pHandlingCode == NULL)
		return E_POINTER ;

	hr = m_pParentCmd->TriadEvents_OnSegmentSelectionChange (SelectedTriadSegment, BeforeOrAfter, pContext, pHandlingCode);
	if(FAILED(hr)) return hr;

	return S_OK;
}




