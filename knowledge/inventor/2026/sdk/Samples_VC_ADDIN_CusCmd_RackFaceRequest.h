//-----------------------------------------------------------------------------
//----- RackFaceRequest.h : Declaration of the CRackFaceRequest
//-----------------------------------------------------------------------------
#ifndef _RackFaceRequest_h_
#define _RackFaceRequest_h_

#include "ChangeRequest.h"

//-----------------------------------------------------------------------------
class CRackFaceRequest : public CChangeRequest
{
public:
	CRackFaceRequest (Application *pApplication, Face *pRackFace, Edge *pRackEdge, int iNoTeeth, double dRackHeight, double dRackWidth, double dRackExtents, PartFeatureExtentDirectionEnum kRackFeatureExtentDirection)
		: m_pApplication(pApplication),
		m_pRackFace(pRackFace),
		m_pRackEdge(pRackEdge),
		m_iNoTeeth(iNoTeeth),
		m_dRackHeight(dRackHeight),
		m_dRackWidth(dRackWidth),
		m_dRackExtents(dRackExtents),
		m_kRackFeatureExtentDirection(kRackFeatureExtentDirection)
	{
	}
	//change processor callbacks
	HRESULT ChangeProcessorEvents_OnExecute(Document *pDocument, NameValueMap *pContext, VARIANT_BOOL *pSucceeded);

private:
	//Inventor application object
	CComPtr<Application> m_pApplication;

	//rack face command parameters
	CComPtr<Face> m_pRackFace;
	CComPtr<Edge> m_pRackEdge;

	int m_iNoTeeth{ 0 };
	double m_dRackHeight{0.0};
	double m_dRackWidth{0.0};
	double m_dRackExtents{0.0};
	PartFeatureExtentDirectionEnum m_kRackFeatureExtentDirection;

} ;

//-----------------------------------------------------------------------------
#endif //----- _RackFaceRequest_h_
