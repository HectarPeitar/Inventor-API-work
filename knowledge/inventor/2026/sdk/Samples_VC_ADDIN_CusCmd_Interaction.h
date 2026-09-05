//-----------------------------------------------------------------------------
//----- Interaction.h : Declaration of the CInteraction
//-----------------------------------------------------------------------------
#ifndef _Interaction_h_
#define _Interaction_h_

#include "resource.h"

class CCommand;

class CInteraction;

typedef IDispEventImpl<0, CInteraction, &DIID_InteractionEventsSink, &LIBID_Inventor, 1, 0> InteractionEvtsSink;
typedef IDispEventImpl<1, CInteraction, &DIID_SelectEventsSink, &LIBID_Inventor, 1, 0> SelectEvtsSink;
typedef IDispEventImpl<2, CInteraction, &DIID_MouseEventsSink, &LIBID_Inventor, 1, 0> MouseEvtsSink;
typedef IDispEventImpl<3, CInteraction, &DIID_TriadEventsSink, &LIBID_Inventor, 1, 0> TriadEvtsSink;

//-----------------------------------------------------------------------------
class ATL_NO_VTABLE CInteraction : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public InteractionEvtsSink,	
	public SelectEvtsSink,
	public MouseEvtsSink,
	public TriadEvtsSink
{
public:
	CInteraction () {

		m_pInteractionEvtsObj = NULL;
		m_pSelectEvtsObj = NULL;
		m_pMouseEvtsObj = NULL;
		m_pTriadEvtsObj = NULL;

		m_pParentCmd = NULL;
		
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CInteraction)
	END_COM_MAP()

	BEGIN_SINK_MAP(CInteraction)
		SINK_ENTRY_EX (0, DIID_InteractionEventsSink, InteractionEventsSink_OnTerminateMeth, InteractionEvents_OnTerminate)
		SINK_ENTRY_EX (0, DIID_InteractionEventsSink, InteractionEventsSink_OnHelpMeth, InteractionEvents_OnHelp)	

		SINK_ENTRY_EX (1, DIID_SelectEventsSink, SelectEventsSink_OnPreSelectMeth, SelectEvents_OnPreSelect)
		SINK_ENTRY_EX (1, DIID_SelectEventsSink, SelectEventsSink_OnPreSelectMouseMoveMeth, SelectEvents_OnPreSelectMouseMove)
		SINK_ENTRY_EX (1, DIID_SelectEventsSink, SelectEventsSink_OnStopPreSelectMeth, SelectEvents_OnStopPreSelect)
		SINK_ENTRY_EX (1, DIID_SelectEventsSink, SelectEventsSink_OnSelectMeth, SelectEvents_OnSelect)
		SINK_ENTRY_EX (1, DIID_SelectEventsSink, SelectEventsSink_OnUnSelectMeth, SelectEvents_OnUnSelect)	

		SINK_ENTRY_EX (2, DIID_MouseEventsSink, MouseEventsSink_OnMouseUpMeth, MouseEvents_OnMouseUp)
		SINK_ENTRY_EX (2, DIID_MouseEventsSink, MouseEventsSink_OnMouseDownMeth, MouseEvents_OnMouseDown)
		SINK_ENTRY_EX (2, DIID_MouseEventsSink, MouseEventsSink_OnMouseClickMeth, MouseEvents_OnMouseClick)
		SINK_ENTRY_EX (2, DIID_MouseEventsSink, MouseEventsSink_OnMouseDoubleClickMeth, MouseEvents_OnMouseDoubleClick)
		SINK_ENTRY_EX (2, DIID_MouseEventsSink, MouseEventsSink_OnMouseMoveMeth, MouseEvents_OnMouseMove)
		SINK_ENTRY_EX (2, DIID_MouseEventsSink, MouseEventsSink_OnMouseLeaveMeth, MouseEvents_OnMouseLeave)

		SINK_ENTRY_EX (3, DIID_TriadEventsSink, TriadEventsSink_OnActivateMeth, TriadEvents_OnActivate)
		SINK_ENTRY_EX (3, DIID_TriadEventsSink, TriadEventsSink_OnMoveMeth, TriadEvents_OnMove)
		SINK_ENTRY_EX (3, DIID_TriadEventsSink, TriadEventsSink_OnMoveTriadOnlyToggleMeth, TriadEvents_OnMoveTriadOnlyToggle)
		SINK_ENTRY_EX (3, DIID_TriadEventsSink, TriadEventsSink_OnStartMoveMeth, TriadEvents_OnStartMove)
		SINK_ENTRY_EX (3, DIID_TriadEventsSink, TriadEventsSink_OnTerminateMeth, TriadEvents_OnTerminate)
		SINK_ENTRY_EX (3, DIID_TriadEventsSink, TriadEventsSink_OnSegmentSelectionChangeMeth, TriadEvents_OnSegmentSelectionChange)
		SINK_ENTRY_EX (3, DIID_TriadEventsSink, TriadEventsSink_OnEndMoveMeth, TriadEvents_OnEndMove)
		SINK_ENTRY_EX (3, DIID_TriadEventsSink, TriadEventsSink_OnStartSequenceMeth, TriadEvents_OnStartSequence)
		SINK_ENTRY_EX (3, DIID_TriadEventsSink, TriadEventsSink_OnEndSequenceMeth, TriadEvents_OnEndSequence)
	END_SINK_MAP()

public:
	enum InteractionTypeEnum            
	{
		kSelection,
		kMouse,
		kKeyboard,
		kTriad  
	};	

private:  
	CArray<InteractionTypeEnum, InteractionTypeEnum&> m_kInteractionType;

	//InteractionEvents object
	CComPtr<InteractionEventsObject> m_pInteractionEvtsObj;

	//SelectEvents object
	CComPtr<SelectEventsObject> m_pSelectEvtsObj;

	//MouseEvents object
	CComPtr<MouseEventsObject> m_pMouseEvtsObj;

	//TriadEvents object
	CComPtr<TriadEventsObject> m_pTriadEvtsObj;

	//parent Command object
	CCommand *m_pParentCmd;

public:
	//----- InteractionEventsSink
	STDMETHOD(InteractionEvents_OnTerminate) () ;
	STDMETHOD(InteractionEvents_OnHelp) (EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode) ;

	//----- SelectEventsSink
	STDMETHOD(SelectEvents_OnPreSelect) (IDispatch **ppPreSelectEntity, VARIANT_BOOL *pDoHighlight, ObjectCollection **ppMorePreSelectEntities, SelectionDeviceEnum SelectionDevice, Point *pModelPosition, Point2d *pViewPosition, View *pView) ;
	STDMETHOD(SelectEvents_OnPreSelectMouseMove) (IDispatch *pPreSelectEntity, Point *pModelPosition, Point2d *pViewPosition, View *pView) ;
	STDMETHOD(SelectEvents_OnStopPreSelect) (Point *pModelPosition, Point2d *pViewPosition, View *pView) ;
	STDMETHOD(SelectEvents_OnSelect) (ObjectsEnumerator *pJustSelectedEntities, SelectionDeviceEnum SelectionDevice, Point *pModelPosition, Point2d *pViewPosition, View *pView) ;
	STDMETHOD(SelectEvents_OnUnSelect) (ObjectsEnumerator *pUnSelectedEntities, SelectionDeviceEnum SelectionDevice, Point *pModelPosition, Point2d *pViewPosition, View *pView) ;

	//----- MouseEventsSink
	STDMETHOD(MouseEvents_OnMouseUp) (MouseButtonEnum Button, ShiftStateEnum ShiftKeys, Point *pModelPosition, Point2d *pViewPosition, View *pView) ;
	STDMETHOD(MouseEvents_OnMouseDown) (MouseButtonEnum Button, ShiftStateEnum ShiftKeys, Point *pModelPosition, Point2d *pViewPosition, View *pView) ;
	STDMETHOD(MouseEvents_OnMouseClick) (MouseButtonEnum Button, ShiftStateEnum ShiftKeys, Point *pModelPosition, Point2d *pViewPosition, View *pView) ;
	STDMETHOD(MouseEvents_OnMouseDoubleClick) (MouseButtonEnum Button, ShiftStateEnum ShiftKeys, Point *pModelPosition, Point2d *pViewPosition, View *pView) ;
	STDMETHOD(MouseEvents_OnMouseMove) (MouseButtonEnum Button, ShiftStateEnum ShiftKeys, Point *pModelPosition, Point2d *pViewPosition, View *pView) ;
	STDMETHOD(MouseEvents_OnMouseLeave) (MouseButtonEnum Button, ShiftStateEnum ShiftKeys, View *pView) ;

	//----- TriadEventsSink
	STDMETHOD(TriadEvents_OnActivate) (NameValueMap *pContext, HandlingCodeEnum *pHandlingCode) ;
	STDMETHOD(TriadEvents_OnEndMove) (TriadSegmentEnum SelectedTriadSegment, ShiftStateEnum ShiftKeys, Matrix *pCoordinateSystem, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode) ;
	STDMETHOD(TriadEvents_OnMove) (TriadSegmentEnum SelectedTriadSegment, ShiftStateEnum ShiftKeys, Matrix *pCoordinateSystem, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode) ;
	STDMETHOD(TriadEvents_OnEndSequence) (VARIANT_BOOL Cancelled, Matrix *pCoordinateSystem, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode) ;
	STDMETHOD(TriadEvents_OnStartSequence) (Matrix *pCoordinateSystem, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode) ;
	STDMETHOD(TriadEvents_OnMoveTriadOnlyToggle) (VARIANT_BOOL MoveTriadOnly, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode) ;
	STDMETHOD(TriadEvents_OnStartMove) (TriadSegmentEnum SelectedTriadSegment, ShiftStateEnum ShiftKeys, Matrix *pCoordinateSystem, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode) ;
	STDMETHOD(TriadEvents_OnTerminate) (VARIANT_BOOL Cancelled, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode) ;
	STDMETHOD(TriadEvents_OnSegmentSelectionChange) (TriadSegmentEnum SelectedTriadSegment, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode) ;


	HRESULT StartInteraction(Application* pApplication, BSTR bstrInteractionName, InteractionEventsObject **ppInteractionEvtsObj);
	HRESULT StopInteraction();

	HRESULT EnableInteraction();
	HRESULT DisableInteraction();

	HRESULT SubscribeToEvent(InteractionTypeEnum InteractionType, IDispatch **ppEvtsObj);
	HRESULT UnsubscribeFromEvents();		

	void SetParentCmd(CCommand *m_pParentCmd);

} ;

//-----------------------------------------------------------------------------
#endif //----- _Interaction_h_
