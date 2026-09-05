//-----------------------------------------------------------------------------
//----- Command.h : Declaration of the CCommand
//-----------------------------------------------------------------------------
#ifndef _Command_h_
#define _Command_h_

#include "resource.h"

#include "Interaction.h"
#include "ChangeRequest.h"

//-----------------------------------------------------------------------------
class ATL_NO_VTABLE CCommand : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispEventImpl<0, CCommand, &DIID_ButtonDefinitionSink, &LIBID_Inventor, 1, 0>
{
public:
	CCommand () {
		m_pApplication = NULL;

		m_pButtonDefinitionObj = NULL;

		m_pInteraction = NULL;
		m_pInteractionEvtsObj = NULL;
		m_pSelectEvtsObj = NULL;
		m_pMouseEvtsObj = NULL;
		m_pTriadEvtsObj = NULL;

		m_bCommandIsRunning = false;
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CCommand)
	END_COM_MAP()

	BEGIN_SINK_MAP(CCommand)
		SINK_ENTRY_EX (0, DIID_ButtonDefinitionSink, ButtonDefinitionSink_OnExecuteMeth, ButtonDefinitionEvents_OnExecute)
	END_SINK_MAP()

protected:
	//Inventor application object
	CComPtr<Application> m_pApplication;

	//button definition object (corresponding to this button handler sink)
	CComPtr<ButtonDefinitionObject> m_pButtonDefinitionObj;

	//Interaction object
	CComObject<CInteraction>  *m_pInteraction;

	//InteractionEvents object
	CComPtr<InteractionEventsObject> m_pInteractionEvtsObj;

	//SelectEvents object
	CComPtr<SelectEventsObject> m_pSelectEvtsObj;

	//MouseEvents object
	CComPtr<MouseEventsObject> m_pMouseEvtsObj;

	//TriadEvents object
	CComPtr<TriadEventsObject> m_pTriadEvtsObj;

	//command status
	bool m_bCommandIsRunning{false};

public:	
	//----- ButtonDefinitionSink
	STDMETHOD(ButtonDefinitionEvents_OnExecute) (NameValueMap *pContext) = 0;

	//button creation/display methods
	HRESULT CreateButton(Application* pApplication, BSTR bstrDisplayName, BSTR bstrInternalName, CommandTypesEnum CommandType, VARIANT varClientId, BSTR bstrDescription, BSTR bstrToolTip, VARIANT varStandardIcon, VARIANT varLargeIcon, ButtonDisplayEnum ButtonType, bool bAutoAddToGUI, ButtonDefinitionObject** pButtonDefinitionObj);
	HRESULT GetButtonDefinition(ButtonDefinitionObject** pButtonDefinitionObj);
	HRESULT RemoveButton();

//command execution controlling methods
protected:
	virtual HRESULT StartCommand();
public:
	virtual HRESULT ExecuteCommand() = 0;
	virtual HRESULT StopCommand();

//interaction controlling methods
private:
	HRESULT StartInteraction();
	HRESULT StopInteraction();

//event subscription/un-subscription methods
protected:
	HRESULT SubscribeToEvent(CInteraction::InteractionTypeEnum InteractionType);
private:
	HRESULT UnsubscribeFromEvents();
	
//event enable/disable methods
public:
	virtual HRESULT EnableInteraction();
	virtual HRESULT DisableInteraction();

//change request connection methods
protected:
	HRESULT ExecuteChangeRequest(CChangeRequest *pChangeRequest, VARIANT varChangeDefinition, Document *pDocument);
	
//event callbacks
public:
	//interaction event callbacks
	virtual HRESULT InteractionEvents_OnHelp(EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode) { return E_NOTIMPL ;}

	//selection event callbacks
	virtual HRESULT SelectEvents_OnPreSelect(IDispatch **ppPreSelectEntity, VARIANT_BOOL *pDoHighlight, ObjectCollection **ppMorePreSelectEntities, SelectionDeviceEnum SelectionDevice, Point *pModelPosition, Point2d *pViewPosition, View *pView) { return E_NOTIMPL ;}
	virtual HRESULT SelectEvents_OnPreSelectMouseMove(IDispatch *pPreSelectEntity, Point *pModelPosition, Point2d *pViewPosition, View *pView) { return E_NOTIMPL ;}
	virtual HRESULT SelectEvents_OnStopPreSelect(Point *pModelPosition, Point2d *pViewPosition, View *pView) { return E_NOTIMPL ;}
	virtual HRESULT SelectEvents_OnSelect(ObjectsEnumerator *pJustSelectedEntities, SelectionDeviceEnum SelectionDevice, Point *pModelPosition, Point2d *pViewPosition, View *pView) { return E_NOTIMPL ;}
	virtual HRESULT SelectEvents_OnUnSelect(ObjectsEnumerator *pUnSelectedEntities, SelectionDeviceEnum SelectionDevice, Point *pModelPosition, Point2d *pViewPosition, View *pView) { return E_NOTIMPL ;}
	
	//----- MouseEventsSink
	virtual HRESULT MouseEvents_OnMouseUp(MouseButtonEnum Button, ShiftStateEnum ShiftKeys, Point *pModelPosition, Point2d *pViewPosition, View *pView) { return E_NOTIMPL ;}
	virtual HRESULT MouseEvents_OnMouseDown(MouseButtonEnum Button, ShiftStateEnum ShiftKeys, Point *pModelPosition, Point2d *pViewPosition, View *pView) { return E_NOTIMPL ;}
	virtual HRESULT MouseEvents_OnMouseClick(MouseButtonEnum Button, ShiftStateEnum ShiftKeys, Point *pModelPosition, Point2d *pViewPosition, View *pView) { return E_NOTIMPL ;}
	virtual HRESULT MouseEvents_OnMouseDoubleClick(MouseButtonEnum Button, ShiftStateEnum ShiftKeys, Point *pModelPosition, Point2d *pViewPosition, View *pView) { return E_NOTIMPL ;}
	virtual HRESULT MouseEvents_OnMouseMove(MouseButtonEnum Button, ShiftStateEnum ShiftKeys, Point *pModelPosition, Point2d *pViewPosition, View *pView) { return E_NOTIMPL ;}
	virtual HRESULT MouseEvents_OnMouseLeave(MouseButtonEnum Button, ShiftStateEnum ShiftKeys, View *pView) { return E_NOTIMPL ;}

	//----- TriadEventsSink
	virtual HRESULT TriadEvents_OnActivate(NameValueMap *pContext, HandlingCodeEnum *pHandlingCode) { return E_NOTIMPL ;}
	virtual HRESULT TriadEvents_OnEndMove(TriadSegmentEnum SelectedTriadSegment, ShiftStateEnum ShiftKeys, Matrix *pCoordinateSystem, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode) { return E_NOTIMPL ;}
	virtual HRESULT TriadEvents_OnMove(TriadSegmentEnum SelectedTriadSegment, ShiftStateEnum ShiftKeys, Matrix *pCoordinateSystem, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode) { return E_NOTIMPL ;}
	virtual HRESULT TriadEvents_OnEndSequence(VARIANT_BOOL Cancelled, Matrix *pCoordinateSystem, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode) { return E_NOTIMPL ;}
	virtual HRESULT TriadEvents_OnStartSequence(Matrix *pCoordinateSystem, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode) { return E_NOTIMPL ;}
	virtual HRESULT TriadEvents_OnMoveTriadOnlyToggle(VARIANT_BOOL MoveTriadOnly, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode) { return E_NOTIMPL ;}
	virtual HRESULT TriadEvents_OnStartMove(TriadSegmentEnum SelectedTriadSegment, ShiftStateEnum ShiftKeys, Matrix *pCoordinateSystem, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode) { return E_NOTIMPL ;}
	virtual HRESULT TriadEvents_OnTerminate(VARIANT_BOOL Cancelled, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode) { return E_NOTIMPL ;}
	virtual HRESULT TriadEvents_OnSegmentSelectionChange(TriadSegmentEnum SelectedTriadSegment, EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode) { return E_NOTIMPL ;}

} ;

//-----------------------------------------------------------------------------
#endif //----- _Command_h_
