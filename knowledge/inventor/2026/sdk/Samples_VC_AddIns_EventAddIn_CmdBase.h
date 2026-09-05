///////////////////////////////////////////////////////////////////////////////////////////
//
// SampleCommandBase - This is the base class of all of the commands in this example.
// It allows commands to control what they want to do in response to messages from
// Inventor.  Note: In this example we have one event handler class for each type of
// event.
///////////////////////////////////////////////////////////////////////////////////////////

#ifndef _CmdBase_
#define _CmdBase_

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif



#include "samplecommand_i.h"


class SampleCommandBase {

public:
	virtual HRESULT OnPreSelect(
		IDispatch * * PreSelectEntity,
        VARIANT_BOOL * DoHighlight,
        struct ObjectCollection * * MorePreSelectEntities,
        enum SelectionDeviceEnum SelectionDevice,
        struct Point * ModelPosition,
        struct Point2d * ViewPosition,
        struct View * View );

	 virtual HRESULT OnPreSelectMouseMove(
		IDispatch * PreSelectEntity,
        Point * ModelPosition,
        Point2d * ViewPosition,
        View * View );

	virtual HRESULT OnStopPreSelect( 
		Point * ModelPosition,
        Point2d * ViewPosition,
        View * View);

	virtual HRESULT OnSelect(      
		ObjectsEnumerator * JustSelectedEntities,
        SelectionDeviceEnum SelectionDevice,
        Point * ModelPosition,
        Point2d * ViewPosition,
        View * View);

	virtual HRESULT OnUnSelect(        
		ObjectsEnumerator * UnSelectedEntities,
        SelectionDeviceEnum SelectionDevice,
        Point * ModelPosition,
        Point2d * ViewPosition,
        View * View );

	virtual void CancelCommand();
};






#endif
