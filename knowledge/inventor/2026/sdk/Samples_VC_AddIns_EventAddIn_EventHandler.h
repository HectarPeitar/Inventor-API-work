//////////////////////////////////////////////////////////////////////////
// EventHandler.h : Declaration of the CSelectEventHandler
/// EventHandler.h : Declaration of the CInteractionEventHandler
//
// This file contains the event handlers for the Select and Interaction
// events. These event handlers hold a parent which is the command that
// owns the event handler.  When the event handler recieves a message from
// Inventor, it passes the message to the command and allows the command
// to determine how it wants to handle the message.
//
///////////////////////////////////////////////////////////////////////////

#ifndef __EVENTHANDLER_H_
#define __EVENTHANDLER_H_

#include "resource.h"       // main symbols

#include "EventsDispIds.h"

#include "samplecommand_i.h"

#define SELECT_EVENTS 0
#define INTERACTION_EVENTS 0
#define MOUSE_EVENTS 0
#define KEYBOARD_EVENTS 0

#define INVENTOR_MAJOR 1
#define INVENTOR_MINOR 0

class SampleCommandBase;

/////////////////////////////////////////////////////////////////////////////
// CSelectEventHandler
class/* /*ATL_NO_VTABLE*/ CSelectEventHandler : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSelectEventHandler, &CLSID_SelectEventHandler>,
	public IDispatchImpl<ISelectEventHandler, &IID_ISelectEventHandler, &LIBID_SampleCommandLib>,
	public IDispEventImpl< 
					   SELECT_EVENTS, 
					   CSelectEventHandler,
					   &DIID_SelectEventsSink,
					   &LIBID_Inventor,
					   INVENTOR_MAJOR,
					   INVENTOR_MINOR
					   >
{
public:
	CSelectEventHandler()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SELECTEVENTHANDLER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSelectEventHandler)
	COM_INTERFACE_ENTRY(ISelectEventHandler)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ISelectEventHandler
public:

//      List of messages:

//		[id(0x03005581), helpstring("Fires signaling that a particular object has been indicated as a potential candidate for selection"), helpcontext(0x03005581)]
//        HRESULT OnPreSelect(
//                        [in, out] IDispatch** PreSelectEntity, 
//                        [out] VARIANT_BOOL* DoHighlight, 
//                        [in, out] ObjectCollection** MorePreSelectEntities, 
//                        [in] SelectionDeviceEnum SelectionDevice, 
//                        [in] Point* ModelPosition, 
//                        [in] Point2d* ViewPosition, 
//                        [in] View* View);
//        [id(0x03005582), helpstring("Fires on a mouse move while a given object has been indicated as a potential candidate for selection"), helpcontext(0x03005582)]
//        HRESULT OnPreSelectMouseMove(
//                        [in] IDispatch* PreSelectEntity, 
//                        [in] Point* ModelPosition, 
//                        [in] Point2d* ViewPosition, 
//                        [in] View* View);
//        [id(0x03005583), helpstring("Fires signaling that a particular object has just been gestured out of being a potential candidate for selection"), helpcontext(0x03005583)]
//        HRESULT OnStopPreSelect(
//                        [in] Point* ModelPosition, 
//                        [in] Point2d* ViewPosition, 
//                        [in] View* View);
//        [id(0x03005584), helpstring("Fires signaling that a particular object has just been selected by the end-user"), helpcontext(0x03005584)]
//        HRESULT OnSelect(
//                        [in] ObjectsEnumerator* JustSelectedEntities, 
//                        [in] SelectionDeviceEnum SelectionDevice, 
//                        [in] Point* ModelPosition, 
//                        [in] Point2d* ViewPosition, 
//                        [in] View* View);
//        [id(0x03005585), helpstring("Fires signaling that a particular object has just been un-selected by the end-user"), helpcontext(0x03005585)]
//        HRESULT OnUnSelect(
//                        [in] ObjectsEnumerator* UnSelectedEntities, 
//                        [in] SelectionDeviceEnum SelectionDevice, 
//                        [in] Point* ModelPosition, 
//                        [in] Point2d* ViewPosition, 
//                        [in] View* View);

	// NOTE: These functions MUST be __stdcall 
	STDMETHOD(onEvent_OnPreSelect)(      
		IDispatch * * PreSelectEntity,
        VARIANT_BOOL * DoHighlight,
        struct ObjectCollection * * MorePreSelectEntities,
        enum SelectionDeviceEnum SelectionDevice,
        struct Point * ModelPosition,
        struct Point2d * ViewPosition,
        struct View * View );

	STDMETHOD( onEvent_OnPreSelectMouseMove)(
		IDispatch * PreSelectEntity,
        Point * ModelPosition,
        Point2d * ViewPosition,
        View * View );

	STDMETHOD(onEvent_OnStopPreSelect)( 
		Point * ModelPosition,
        Point2d * ViewPosition,
        View * View);

	STDMETHOD(onEvent_OnSelect)(       
		ObjectsEnumerator * JustSelectedEntities,
        SelectionDeviceEnum SelectionDevice,
        Point * ModelPosition,
        Point2d * ViewPosition,
        View * View);

	STDMETHOD(onEvent_OnUnSelect)(        
		ObjectsEnumerator * UnSelectedEntities,
        SelectionDeviceEnum SelectionDevice,
        Point * ModelPosition,
        Point2d * ViewPosition,
        View * View );

	void SetParent(SampleCommandBase* pParent) {m_pParent = pParent;}

	BEGIN_SINK_MAP( CSelectEventHandler )

		SINK_ENTRY_EX( SELECT_EVENTS, DIID_SelectEventsSink, SelectEventsSink_OnPreSelectMeth, onEvent_OnPreSelect)
		SINK_ENTRY_EX( SELECT_EVENTS, DIID_SelectEventsSink, SelectEventsSink_OnPreSelectMouseMoveMeth, onEvent_OnPreSelectMouseMove)

		SINK_ENTRY_EX( SELECT_EVENTS, DIID_SelectEventsSink, SelectEventsSink_OnStopPreSelectMeth, onEvent_OnStopPreSelect)
		SINK_ENTRY_EX( SELECT_EVENTS, DIID_SelectEventsSink, SelectEventsSink_OnSelectMeth, onEvent_OnSelect)

		SINK_ENTRY_EX( SELECT_EVENTS, DIID_SelectEventsSink, SelectEventsSink_OnUnSelectMeth, onEvent_OnUnSelect)
	END_SINK_MAP()

private:
	SampleCommandBase* m_pParent{ nullptr };
};


//////////////////////////////////////////////////////////////////////////////
//
// Class CInteractionEventHandler
//
// Recieves the Suspend, Resume, OnActive and OnTerminate messages from Inventor.
// The command upon recieving this needs to determine what it wants to do.
//
///////////////////////////////////////////////////////////////////////////////
class CInteractionEventHandler : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CInteractionEventHandler, &CLSID_InteractionEventHandler>,
	public IDispatchImpl<IInteractionEventHandler, &IID_IInteractionEventHandler, &LIBID_SampleCommandLib>,
	public IDispEventImpl< 
					   INTERACTION_EVENTS, 
					   CInteractionEventHandler,
					   &DIID_InteractionEventsSink,
					   &LIBID_Inventor,
					   INVENTOR_MAJOR,
					   INVENTOR_MINOR
					   >
{
public:
	CInteractionEventHandler();
	~CInteractionEventHandler();

public:


	// SINK_ENTRY_EX takes the following parameters:
	// 0                           = first argument in IDispEventImpl base class
	// DIID__IEvents			   = GUID of source dispinterface
	// <dispID>                    = dispid of desired event.
	// <fnct>					   = pointer to event handling function.

DECLARE_REGISTRY_RESOURCEID(IDR_SELECTEVENTHANDLER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CInteractionEventHandler)
	COM_INTERFACE_ENTRY(IInteractionEventHandler)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

	BEGIN_SINK_MAP( CInteractionEventHandler )
		SINK_ENTRY_EX( INTERACTION_EVENTS, DIID_InteractionEventsSink, InteractionEventsSink_OnActivateMeth, onEvent_OnActivate)
		SINK_ENTRY_EX( INTERACTION_EVENTS, DIID_InteractionEventsSink, InteractionEventsSink_OnTerminateMeth, onEvent_OnTerminate)

		SINK_ENTRY_EX( INTERACTION_EVENTS, DIID_InteractionEventsSink, InteractionEventsSink_OnSuspendMeth, onEvent_OnSuspend)
		SINK_ENTRY_EX( INTERACTION_EVENTS, DIID_InteractionEventsSink, InteractionEventsSink_OnResumeMeth, onEvent_OnResume )
		SINK_ENTRY_EX( INTERACTION_EVENTS, DIID_InteractionEventsSink, InteractionEventsSink_OnHelpMeth, onEvent_OnHelp )
		
	END_SINK_MAP()

	void SetParent(SampleCommandBase* pParent) {m_pParent = pParent;}

	// NOTE: These functions MUST be __stdcall 
	STDMETHOD(onEvent_OnActivate)();

	STDMETHOD(onEvent_OnTerminate)();

	STDMETHOD(onEvent_OnSuspend)();

	STDMETHOD(onEvent_OnResume)();

	STDMETHOD(onEvent_OnHelp)(EventTimingEnum BeforeOrAfter, NameValueMap * pContext,  HandlingCodeEnum * HandlingCode);
	
private:
	SampleCommandBase* m_pParent{ nullptr };

};
	
#endif //__EVENTHANDLER_H_
