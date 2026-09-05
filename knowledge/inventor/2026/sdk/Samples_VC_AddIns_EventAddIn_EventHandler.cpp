
///////////////////////////////////////////////////////////////////////////
// This file contains the event handlers for the Select and Interaction
// events. These event handlers hold a parent which is the command that
// owns the event handler.  When the event handler recieves a message from
// Inventor, it passes the message to the command and allows the command
// to determine how it wants to handle the message.
//
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SampleCommand.h"
#include "EventHandler.h"
#include "rxsamplecommand.h"


/////////////////////////////////////////////////////////////////////////////
// CSelectEventHandler

STDMETHODIMP CSelectEventHandler::onEvent_OnPreSelect(IDispatch **PreSelectEntity,
									VARIANT_BOOL * DoHighlight, ObjectCollection * * MorePreSelectEntities,
									SelectionDeviceEnum SelectionDevice,Point * ModelPosition,
									Point2d * ViewPosition, View * View )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 

	return m_pParent->OnPreSelect(PreSelectEntity, DoHighlight, MorePreSelectEntities, SelectionDevice,
								  ModelPosition, ViewPosition, View );
}

STDMETHODIMP CSelectEventHandler::onEvent_OnPreSelectMouseMove(IDispatch * PreSelectEntity,
								Point * ModelPosition, Point2d * ViewPosition,
								View * View)

{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 

	return m_pParent->OnPreSelectMouseMove (PreSelectEntity,
		  ModelPosition, ViewPosition, View );
}

STDMETHODIMP CSelectEventHandler::onEvent_OnStopPreSelect(Point * ModelPosition, Point2d * ViewPosition,
															View * View )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 

	return m_pParent->OnStopPreSelect(ModelPosition,ViewPosition, View );
}

STDMETHODIMP CSelectEventHandler::onEvent_OnSelect(ObjectsEnumerator * JustSelectedEntities,
									SelectionDeviceEnum SelectionDevice, Point * ModelPosition,
									Point2d * ViewPosition, View * View )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 

	return m_pParent->OnSelect (JustSelectedEntities, SelectionDevice,
		  ModelPosition, ViewPosition, View );
}


STDMETHODIMP CSelectEventHandler::onEvent_OnUnSelect(ObjectsEnumerator * UnSelectedEntities,
							SelectionDeviceEnum SelectionDevice, Point * ModelPosition,
							Point2d * ViewPosition, View * View )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	
	return m_pParent->OnUnSelect(UnSelectedEntities,
		SelectionDevice, ModelPosition,ViewPosition,View );
}

/*---------------------- Constructor(s), initializers and destructor ---------------------------------*/
CInteractionEventHandler::CInteractionEventHandler(): m_pParent(NULL)
{ 
}

CInteractionEventHandler::~CInteractionEventHandler()
{
}


STDMETHODIMP CInteractionEventHandler::onEvent_OnActivate()
{
	return NOERROR;
}

STDMETHODIMP CInteractionEventHandler::onEvent_OnTerminate()

{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	
	if (m_pParent) 
		m_pParent->CancelCommand();
	return NOERROR;
}

STDMETHODIMP CInteractionEventHandler::onEvent_OnSuspend()
{
	return NOERROR;
}

STDMETHODIMP CInteractionEventHandler::onEvent_OnResume()
{
	return NOERROR;
}

STDMETHODIMP CInteractionEventHandler::onEvent_OnHelp(EventTimingEnum BeforeOrAfter, NameValueMap * pContext,  HandlingCodeEnum * HandlingCode)
{
	AfxMessageBox(_T("No help is available for SampleCommand API Sample"));
	*HandlingCode = kEventHandled;
	return NOERROR;
}
