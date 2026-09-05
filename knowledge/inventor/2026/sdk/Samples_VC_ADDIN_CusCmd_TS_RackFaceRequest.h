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
	CRackFaceRequest (Application *pApplication, Face *pRackFace, Edge *pRackEdge, int iNoTeeth, double dRackHeight, double dRackWidth, double dRackExtents, PartFeatureExtentDirectionEnum kRackFeatureExtentDirection) {

		m_pApplication = pApplication;
		m_pRackFace = pRackFace;
		m_pRackEdge = pRackEdge;
		m_iNoTeeth = iNoTeeth;
		m_dRackHeight = dRackHeight;
		m_dRackWidth = dRackWidth;
		m_dRackExtents = dRackExtents;
		m_kRackFeatureExtentDirection = kRackFeatureExtentDirection;

	}

	CRackFaceRequest (Application *pApplication) {

		m_pApplication = pApplication;
		m_pRackFace = NULL;
		m_pRackEdge = NULL;
	}

	//change processor callbacks
	HRESULT ChangeProcessorEvents_OnExecute(Document *pDocument, NameValueMap *pContext, VARIANT_BOOL *pSucceeded);
	HRESULT ChangeProcessorEvents_OnWriteToScript (Document *pDocument, NameValueMap *pContext, BSTR *pResultInputs);
	HRESULT ChangeProcessorEvents_OnReadFromScript (Document *pDocument, BSTR Inputs, NameValueMap *pContext);

private:
	CString GetNodeValue(CString strScriptInputs, CString strNodeName);

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

	//transcript string node names
	static const CString m_strNoTeethNodeName;
	static const CString m_strRackHeightNodeName;
	static const CString m_strRackWidthNodeName;
	static const CString m_strRackExtentsNodeName;
	static const CString m_strRackFeatureExtentDirectionNodeName;
	static const CString m_strRackFaceKeyNodeName;
	static const CString m_strRackEdgeKeyNodeName;
} ;


//-----------------------------------------------------------------------------
#endif //----- _RackFaceRequest_h_
