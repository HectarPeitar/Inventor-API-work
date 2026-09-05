#ifndef _ReplicateWorkplane_
#define _ReplicateWorkplane_
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


#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "unknown.h"
#include "resource.h"
#include "CmdBase.h"
#include "EventHandler.h"
#include "replicateworkplanedlg.h"

class ReplicateWorkplaneCmd : public SampleCommandBase
{
public:
	ReplicateWorkplaneCmd(Application*);
	~ReplicateWorkplaneCmd();

	// Command execution control
	void BeginCommand();
	void ExecuteReplicateWorkplaneCmd();
	void EndCommand(bool cancelled = false);

	// Set the data
	void SetOffset(double offset) {m_dOffset = offset;}
	void SetWorkplaneToOffset(WorkPlane* pWorkplane); 
	void SetNumOccurrences(long numOccurrences) {m_dNumOccurences = numOccurrences;}

	// Overrides from Base class
	virtual HRESULT OnSelect(      
		ObjectsEnumerator * JustSelectedEntities,
        SelectionDeviceEnum SelectionDevice,
        Point * ModelPosition,
        Point2d * ViewPosition,
        View * View);
	virtual void CancelCommand();

	// accessors
	Application* GetApplication() { return m_pApplication;}

	
private:
	double m_dOffset{0.0};
	long m_dNumOccurences;

	CComPtr<Application> m_pApplication;
	ReplicateWorkplaneDialog* m_pDialog{ nullptr };

	CComPtr<SelectEventsObject> m_pSelectEventsObject;
	CComPtr<InteractionEventsObject> m_pInteractionObject;

	CComObject< CInteractionEventHandler> *m_pInteractionEvents;
	CComObject< CSelectEventHandler > * m_pSelectEvents;

	CComPtr<WorkPlane> m_pWorkplaneToOffset;
	
};

#endif