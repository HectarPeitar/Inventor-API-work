//-----------------------------------------------------------------------------
//----- RackFaceRequest.cpp : Implementation of CRackFaceRequest
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "RackFaceRequest.h"

//-----------------------------------------------------------------------------
//----- Implementation of Callbacks
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//----- Implementation of ChangeProcessor callbacks
//-----------------------------------------------------------------------------

HRESULT CRackFaceRequest::ChangeProcessorEvents_OnExecute (Document *pDocument, NameValueMap *pContext, VARIANT_BOOL *pSucceeded)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr;

	//execute command functionality
	CComQIPtr<PartDocument> pPartDocument(pDocument);

	CComPtr<PartComponentDefinition> pPartCompDef;
	hr = pPartDocument->get_ComponentDefinition(&pPartCompDef);
	if (FAILED(hr)) return hr;	

	//get rack edge start point and end point
	CComPtr<Vertex> pRackEdgeStartVertex;
	hr = m_pRackEdge->get_StartVertex(&pRackEdgeStartVertex);
	if (FAILED(hr)) return hr;

	CComPtr<Point> pRackEdgeStartPt;
	hr = pRackEdgeStartVertex->get_Point(&pRackEdgeStartPt);
	if (FAILED(hr)) return hr;

	CComPtr<Vertex> pRackEdgeStopVertex;
	hr = m_pRackEdge->get_StopVertex(&pRackEdgeStopVertex);
	if (FAILED(hr)) return hr;

	CComPtr<Point> pRackEdgeStopPt;
	hr = pRackEdgeStopVertex->get_Point(&pRackEdgeStopPt);
	if (FAILED(hr)) return hr;

	double dRackEdgeLength{0.0};
	hr = pRackEdgeStartPt->DistanceTo(pRackEdgeStopPt, &dRackEdgeLength);
	if (FAILED(hr)) return hr;

	double dNonRackWidth = dRackEdgeLength - m_dRackWidth;

	double dToothWidthProportion = 0.25;

	double dToothMajorWidth  = m_dRackWidth  / (m_iNoTeeth + (m_iNoTeeth - 1) * dToothWidthProportion);

	double dToothMinorWidth = dToothWidthProportion * dToothMajorWidth;

	double dToothSlopeWidth = (dToothMajorWidth - dToothMinorWidth) / 2.0;

	double dRackStart = dNonRackWidth / 2.0;

	CComPtr<TransientGeometry> pTransientGeometry;
	hr = m_pApplication->get_TransientGeometry(&pTransientGeometry);
	if (FAILED(hr)) return hr;

	CComPtr<TransientObjects> pTransientObjects;
	hr = m_pApplication->get_TransientObjects(&pTransientObjects);
	if (FAILED(hr)) return hr;

	CComVariant varObjEnumerator;
	CComPtr<ObjectCollection> pSketchLineCollection;
	hr = pTransientObjects->CreateObjectCollection(varObjEnumerator, &pSketchLineCollection);
	if (FAILED(hr)) return hr;

	CComPtr<WorkPlanes> pWorkPlanes;
	hr = pPartCompDef->get_WorkPlanes(&pWorkPlanes);
	if (FAILED(hr)) return hr;

	CComPtr<WorkPlane> pWorkPlane;
	hr = pWorkPlanes->AddByLinePlaneAndAngle(m_pRackEdge, m_pRackFace, CComVariant(_T("90 deg")), VARIANT_FALSE, &pWorkPlane);
	if (FAILED(hr)) return hr;

	hr = pWorkPlane->put_Visible(VARIANT_FALSE);

	CComPtr<PlanarSketches> pPlanarSketches;
	hr = pPartCompDef->get_Sketches(&pPlanarSketches);
	if (FAILED(hr)) return hr;

	CComPtr<PlanarSketch> pPlanarSketch;
	hr = pPlanarSketches->AddWithOrientation(pWorkPlane, m_pRackEdge, VARIANT_TRUE, VARIANT_TRUE, pRackEdgeStartVertex, VARIANT_FALSE, &pPlanarSketch); 
	if (FAILED(hr)) return hr;

	CComPtr<SketchPoints> pSketchPoints;
	hr = pPlanarSketch->get_SketchPoints(&pSketchPoints);
	if (FAILED(hr)) return hr;

	CComPtr<SketchLines> pSketchLines;
	hr = pPlanarSketch->get_SketchLines(&pSketchLines);
	if (FAILED(hr)) return hr;

	CComPtr<Point2d> pPoint1, pPoint2, pPoint3, pPoint4;
	CComPtr<SketchPoint> pSketchPoint1, pSketchPoint2, pSketchPoint3, pSketchPoint4;
	CComPtr<SketchLine> pSketchLine1, pSketchLine2, pSketchLine3, pSketchLine4;

	for (int iToothCt = 0;iToothCt < m_iNoTeeth; iToothCt++)
	{
		hr = pTransientGeometry->CreatePoint2d(dRackStart, 0, &pPoint1);
		hr = pTransientGeometry->CreatePoint2d(dRackStart + dToothSlopeWidth, -m_dRackHeight, &pPoint2);
		hr = pTransientGeometry->CreatePoint2d(dRackStart + dToothSlopeWidth + dToothMinorWidth, -m_dRackHeight, &pPoint3);
		hr = pTransientGeometry->CreatePoint2d(dRackStart + dToothMajorWidth, 0, &pPoint4);

		hr = pSketchPoints->Add(pPoint1, VARIANT_FALSE, &pSketchPoint1);
		hr = pSketchPoints->Add(pPoint2, VARIANT_FALSE, &pSketchPoint2);
		hr = pSketchPoints->Add(pPoint3, VARIANT_FALSE, &pSketchPoint3);
		hr = pSketchPoints->Add(pPoint4, VARIANT_FALSE, &pSketchPoint4);

		hr = pSketchLines->AddByTwoPoints(pSketchPoint1, pSketchPoint2, &pSketchLine1);
		hr = pSketchLines->AddByTwoPoints(pSketchPoint2, pSketchPoint3, &pSketchLine2);
		hr = pSketchLines->AddByTwoPoints(pSketchPoint3, pSketchPoint4, &pSketchLine3);
		hr = pSketchLines->AddByTwoPoints(pSketchPoint4, pSketchPoint1, &pSketchLine4);
															
		hr = pSketchLineCollection->Add(pSketchLine1);
		hr = pSketchLineCollection->Add(pSketchLine2);
		hr = pSketchLineCollection->Add(pSketchLine3);
		hr = pSketchLineCollection->Add(pSketchLine4);
		
		pSketchLine1 = NULL;
		pSketchLine2 = NULL;
		pSketchLine3 = NULL;
		pSketchLine4 = NULL;

		pPoint1 = NULL;
		pPoint2 = NULL;
		pPoint3 = NULL;
		pPoint4 = NULL;

		pSketchPoint1 = NULL;
		pSketchPoint2 = NULL;
		pSketchPoint3 = NULL;
		pSketchPoint4 = NULL;
		
		dRackStart += (dToothMajorWidth + dToothMinorWidth);
	}

	CComPtr<Profiles> pProfiles;
	hr = pPlanarSketch->get_Profiles(&pProfiles);
	if (FAILED(hr)) return hr;

	CComPtr<Profile> pProfile;
	hr = pProfiles->AddForSolid(VARIANT_TRUE, CComVariant(pSketchLineCollection), CComVariant(0), &pProfile);
	if (FAILED(hr)) return hr;

	CComPtr<PartFeatures> pPartFeatures;
	hr = pPartCompDef->get_Features(&pPartFeatures);
	if (FAILED(hr)) return hr;

	CComPtr<ExtrudeFeatures> pExtrudeFeatures;
	hr = pPartFeatures->get_ExtrudeFeatures(&pExtrudeFeatures);
	if (FAILED(hr)) return hr;

	CComPtr<ExtrudeFeature> pRackExtrudeFeature;
	hr = pExtrudeFeatures->AddByDistanceExtent(pProfile, CComVariant(m_kRackFeatureExtentDirection == kSymmetricExtentDirection ? m_dRackExtents *= 2 : m_dRackExtents), m_kRackFeatureExtentDirection, kCutOperation, CComVariant(0), &pRackExtrudeFeature);
	if (FAILED(hr)) return hr;
	
	return S_OK;
}








