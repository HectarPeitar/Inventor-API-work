///////////////////////////////////////////////////////////////////////////////////////////
//
// SampleCommandBase - 
//
// This is the base class of all of the commands in this example.
// It allows commands to control what they want to do in response to messages from
// Inventor.  Note: In this example we have one event handler class for each type of
// event.  This implements the default behavior for all connection points.
//
///////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CmdBase.h"

HRESULT SampleCommandBase::OnPreSelect( IDispatch ** PreSelectEntity, VARIANT_BOOL * DoHighlight,
			struct ObjectCollection * * MorePreSelectEntities, enum SelectionDeviceEnum SelectionDevice,
			struct Point * ModelPosition, struct Point2d * ViewPosition, struct View * View )
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState()); 

	HRESULT Result=NOERROR;

	// Set the highlight to true
	VARIANT_BOOL bHighlight = VARIANT_TRUE;
	DoHighlight = &bHighlight;
	return Result;
}

///////////////////////////////////////////////////////////////////////////////////////////
HRESULT SampleCommandBase::OnPreSelectMouseMove(IDispatch * PreSelectEntity, Point * ModelPosition,
													Point2d * ViewPosition, View * View )
{
	return NOERROR;
}


///////////////////////////////////////////////////////////////////////////////////////////
HRESULT SampleCommandBase::OnStopPreSelect( Point * ModelPosition, Point2d * ViewPosition, 
															View * View)
{
    return NOERROR;
}


///////////////////////////////////////////////////////////////////////////////////////////
HRESULT SampleCommandBase::OnSelect(ObjectsEnumerator * JustSelectedEntities,
								  SelectionDeviceEnum SelectionDevice, Point * ModelPosition,
								  Point2d * ViewPosition, View * View)
{
    return NOERROR;
}


///////////////////////////////////////////////////////////////////////////////////////////
HRESULT SampleCommandBase::OnUnSelect( ObjectsEnumerator * UnSelectedEntities,
							SelectionDeviceEnum SelectionDevice, Point * ModelPosition,
							Point2d * ViewPosition, View * View )
{
    return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////////////////
void  SampleCommandBase::CancelCommand()
{
	// do nothing
}