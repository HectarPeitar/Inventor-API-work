#ifndef _PatternSketch_
#define _PatternSketch_

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


#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "unknown.h"
#include "resource.h"
#include "eventhandler.h"
#include "patternsketchdlg.h"
#include "CmdBase.h"


class PatternSketchCmd : public SampleCommandBase {
public:

	PatternSketchCmd(Application*);
	~PatternSketchCmd();

	// Command control
	void BeginCommand();
	void ExecutePatternCmd();
	void EndCommand(bool cancelled = false);

	// Set the data
	void SetXOffset(double offset) {m_xOffset = offset;}
	void SetYOffset(double offset) {m_yOffset = offset;}
	void SetXOccurences(int occurences) {m_xOccurences = occurences;}
	void SetYOccurences(int occurences) {m_yOccurences = occurences;}
	void SetSelectedObjects(ObjectsEnumerator* pObjectsToOffset);

	// accessors
	Application* GetApplication() { return m_pApplication;}

	// Overrides from base class
	//
	virtual HRESULT OnPreSelect(
		IDispatch * * PreSelectEntity,
        VARIANT_BOOL * DoHighlight,
        struct ObjectCollection * * MorePreSelectEntities,
        enum SelectionDeviceEnum SelectionDevice,
        struct Point * ModelPosition,
        struct Point2d * ViewPosition,
        struct View * View );
	virtual HRESULT OnSelect(      
		ObjectsEnumerator * JustSelectedEntities,
        SelectionDeviceEnum SelectionDevice,
        Point * ModelPosition,
        Point2d * ViewPosition,
        View * View);
	virtual void CancelCommand();


	
private:  // Data Members
	double      m_xOffset{0.0};
	double      m_yOffset{0.0};
	int         m_xOccurences{ 0 };
	int         m_yOccurences{ 0 };
	CComPtr<ObjectsEnumerator> m_pObjectsToOffset;

	CComPtr<Application> m_pApplication;
	PatternSketchDialog* m_pDialog{ nullptr };

	// Event Objects
	CComPtr<SelectEventsObject> m_pSelectEventsObject;
	CComPtr<InteractionEventsObject> m_pInteractionObject;

	// Event Handlers
	CComObject< CInteractionEventHandler>* m_pInteractionEvents;
	CComObject< CSelectEventHandler >* m_pSelectEvents;
	
};
 

#endif
