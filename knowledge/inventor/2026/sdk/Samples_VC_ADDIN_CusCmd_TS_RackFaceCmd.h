//-----------------------------------------------------------------------------
//----- RackFaceCmd.h : Declaration of the CRackFaceCmd
//-----------------------------------------------------------------------------
#ifndef _RackFaceCmd_h_
#define _RackFaceCmd_h_

#include "../resource.h"

#include "../RackFaceCmdDlg.h"
#include "RackFaceRequest.h"
#include "../Command.h"

class CRackFaceCmd : public CCommand
{
public:
	CRackFaceCmd () {

		m_pRackFaceCmdDlg = NULL;

		m_pRackFaceRequest = NULL;

		m_pRackFace = NULL;
		m_pRackEdge = NULL;

		m_pPreviewClientGraphicsNode = NULL;
		m_pTriangleStripGraphics = NULL;
		m_pGraphicsCoordinateSet = NULL;
		m_pGraphicsColorSet = NULL;
		m_pGraphicsColorIndexSet = NULL;
	}

	//----- ButtonDefinitionSink
	STDMETHOD(ButtonDefinitionEvents_OnExecute) (NameValueMap *pContext);

private:
	HRESULT StartCommand();
public:	
	HRESULT ExecuteCommand();
	HRESULT StopCommand();

public:
	HRESULT EnableInteraction();
	HRESULT DisableInteraction();

private:
	HRESULT InitializePreviewGraphics();
public:
	HRESULT UpdatePreviewGraphics();
private:
	HRESULT AddGraphicsPoints(Point *pCornerPt1, Point *pCornerPt2);
	HRESULT AddColorIndex(long lColorIndex);
	HRESULT GetPointCoordinates(Point *pPoint, double *dX, double *dY, double *dZ);
	HRESULT GetVectorCoordinates(UnitVector *pUnitVector, double *dX, double *dY, double *dZ);
	void TerminatePreviewGraphics();

public:
	HRESULT GetValueFromExpression(CString strExpression, double *dValue);
	
public:
	HRESULT UpdateCommandStatus();

//event callbacks
public:
	//selection event callbacks
	HRESULT SelectEvents_OnSelect(ObjectsEnumerator *pJustSelectedEntities, SelectionDeviceEnum SelectionDevice, Point *pModelPosition, Point2d *pViewPosition, View *pView);
	HRESULT SelectEvents_OnPreSelect(IDispatch **ppPreSelectEntity, VARIANT_BOOL *pDoHighlight, ObjectCollection **ppMorePreSelectEntities, SelectionDeviceEnum SelectionDevice, Point *pModelPosition, Point2d *pViewPosition, View *pView);

	//interaction event callbacks
	HRESULT InteractionEvents_OnHelp(EventTimingEnum BeforeOrAfter, NameValueMap *pContext, HandlingCodeEnum *pHandlingCode);

private:
	//rack face command dialog
	RackFaceCmdDlg* m_pRackFaceCmdDlg{ nullptr };

	//rack face request
	CRackFaceRequest* m_pRackFaceRequest{ nullptr };

	//rack face command parameters
	CComPtr<Face> m_pRackFace;
	CComPtr<Edge> m_pRackEdge;

	int m_iNoTeeth{ 0 };
	double m_dRackHeight{0.0};
	double m_dRackWidth{0.0};
	double m_dRackExtents{0.0};
	PartFeatureExtentDirectionEnum m_kRackFeatureExtentDirection;
	
	//rack face preview objects
	CComPtr<GraphicsNode> m_pPreviewClientGraphicsNode;
	CComPtr<TriangleStripGraphics> m_pTriangleStripGraphics;
	CComPtr<GraphicsCoordinateSet> m_pGraphicsCoordinateSet;
	CComPtr<GraphicsColorSet> m_pGraphicsColorSet;
	CComPtr<GraphicsIndexSet> m_pGraphicsColorIndexSet;
} ;

//-----------------------------------------------------------------------------
#endif //----- _RackFaceCmd_h_
