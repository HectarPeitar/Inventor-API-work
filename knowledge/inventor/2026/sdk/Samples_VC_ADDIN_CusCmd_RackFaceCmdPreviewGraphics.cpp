//-----------------------------------------------------------------------------
//----- RackFaceCmd.cpp : Implementation of CRackFaceCmd Preview Graphics
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "RackFaceCmd.h"

HRESULT CRackFaceCmd::InitializePreviewGraphics()
{
	HRESULT hr;
	
	CComPtr<InteractionGraphics> pInteractionGraphics;
	hr  = m_pInteractionEvtsObj->get_InteractionGraphics(&pInteractionGraphics);
	if (FAILED(hr)) return hr;

	CComPtr<ClientGraphics> pPreviewClientGraphics;
	hr = pInteractionGraphics->get_PreviewClientGraphics(&pPreviewClientGraphics);
	if (FAILED(hr)) return hr;

	hr = pPreviewClientGraphics->AddNode(1, &m_pPreviewClientGraphicsNode);
	if (FAILED(hr)) return hr;

	hr = m_pPreviewClientGraphicsNode->AddTriangleStripGraphics(&m_pTriangleStripGraphics);
	if (FAILED(hr)) return hr;

	CComPtr<GraphicsDataSets> pGraphicsDataSets;
	hr = pInteractionGraphics->get_GraphicsDataSets(&pGraphicsDataSets);
	if (FAILED(hr)) return hr;

	hr = pGraphicsDataSets->CreateCoordinateSet(1, &m_pGraphicsCoordinateSet);
	if (FAILED(hr)) return hr;

	hr = pGraphicsDataSets->CreateColorSet(1, &m_pGraphicsColorSet);
	if (FAILED(hr)) return hr;

	hr = m_pGraphicsColorSet->Add(1, 100, 100, 200);
	hr = m_pGraphicsColorSet->Add(2, 150, 150, 250);

	hr = pGraphicsDataSets->CreateIndexSet(1, &m_pGraphicsColorIndexSet);
	if (FAILED(hr)) return hr;

	hr = m_pTriangleStripGraphics->put_CoordinateSet(m_pGraphicsCoordinateSet);
	if (FAILED(hr)) return hr;

	hr = m_pTriangleStripGraphics->put_ColorSet(m_pGraphicsColorSet);
	if (FAILED(hr)) return hr;

	hr = m_pTriangleStripGraphics->put_ColorIndexSet(m_pGraphicsColorIndexSet);
	if (FAILED(hr)) return hr;

	hr = m_pTriangleStripGraphics->put_ColorBinding(kPerItemColors);
	hr = m_pTriangleStripGraphics->put_DepthPriority(4);
	hr = m_pTriangleStripGraphics->put_BurnThrough(VARIANT_TRUE);

	return S_OK;
	
}

HRESULT CRackFaceCmd::UpdatePreviewGraphics()
{
	HRESULT hr;

	//remove the existing co-ordinates
	long lNoGraphicsCoordinates;
	hr = m_pGraphicsCoordinateSet->get_Count(&lNoGraphicsCoordinates);

	for(long lGraphicsCoordinateCt = lNoGraphicsCoordinates; lGraphicsCoordinateCt > 0; lGraphicsCoordinateCt--)
		hr = m_pGraphicsCoordinateSet->Remove(lGraphicsCoordinateCt);

	//remove the existing color indices
	long lNoGraphicsColorIndices;
	hr = m_pGraphicsColorIndexSet->get_Count(&lNoGraphicsColorIndices);

	for(long lGraphicsColorIndexCt = lNoGraphicsColorIndices; lGraphicsColorIndexCt > 0; lGraphicsColorIndexCt--)
		hr = m_pGraphicsColorIndexSet->Remove(lGraphicsColorIndexCt);
	
	CComPtr<TransientGeometry> pTransientGeometry;
	hr = m_pApplication->get_TransientGeometry(&pTransientGeometry);
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

	double dRackEdgeStartPtX, dRackEdgeStartPtY, dRackEdgeStartPtZ;
	hr = GetPointCoordinates(pRackEdgeStartPt, &dRackEdgeStartPtX, &dRackEdgeStartPtY, &dRackEdgeStartPtZ);
	if (FAILED(hr)) return hr;

	double dRackEdgeStopPtX, dRackEdgeStopPtY, dRackEdgeStopPtZ;
	hr = GetPointCoordinates(pRackEdgeStopPt, &dRackEdgeStopPtX, &dRackEdgeStopPtY, &dRackEdgeStopPtZ);
	if (FAILED(hr)) return hr;

	double dRackEdgeLengthX = dRackEdgeStopPtX - dRackEdgeStartPtX;
	double dRackEdgeLengthY = dRackEdgeStopPtY - dRackEdgeStartPtY;
	double dRackEdgeLengthZ = dRackEdgeStopPtZ - dRackEdgeStartPtZ;

	CComPtr<Vector> pRackEdgeVector;
	hr = pTransientGeometry->CreateVector(dRackEdgeLengthX, dRackEdgeLengthY, dRackEdgeLengthZ, &pRackEdgeVector);
	if (FAILED(hr)) return hr;

	CComPtr<IDispatch> pRackFaceGeometry;
	hr = m_pRackFace->get_Geometry(&pRackFaceGeometry);
	if (FAILED(hr)) return hr;

	CComQIPtr<Plane> pRackFacePlane(pRackFaceGeometry);

	CComPtr<UnitVector> pRackFaceNormalUnitVector;
	hr = pRackFacePlane->get_Normal(&pRackFaceNormalUnitVector);
	if (FAILED(hr)) return hr;

	double dRackFaceNormalX, dRackFaceNormalY, dRackFaceNormalZ;
	hr = GetVectorCoordinates(pRackFaceNormalUnitVector, &dRackFaceNormalX, &dRackFaceNormalY, &dRackFaceNormalZ);

	CComPtr<Vector> pRackFaceNormalVector;
	hr = pRackFaceNormalUnitVector->AsVector(&pRackFaceNormalVector);
	if (FAILED(hr)) return hr;

	CComPtr<Vector> pRackPositiveExtentDirectionVector;
	hr = pRackEdgeVector->CrossProduct(pRackFaceNormalVector, &pRackPositiveExtentDirectionVector);
	if (FAILED(hr)) return hr;

	CComPtr<UnitVector> pRackPositiveExtentDirectionUnitVector;
	hr = pRackPositiveExtentDirectionVector->AsUnitVector(&pRackPositiveExtentDirectionUnitVector);

	double dRackPositiveExtentDirectionX, dRackPositiveExtentDirectionY, dRackPositiveExtentDirectionZ;
	hr = GetVectorCoordinates(pRackPositiveExtentDirectionUnitVector, &dRackPositiveExtentDirectionX, &dRackPositiveExtentDirectionY, &dRackPositiveExtentDirectionZ);

	CComPtr<Point> pGraphicsEdgeStartPt;
	CComPtr<Point> pGraphicsParallelEdgeStartPt;

	switch (m_kRackFeatureExtentDirection){

	case kNegativeExtentDirection:

		hr = pRackEdgeStartPt.QueryInterface(&pGraphicsEdgeStartPt);

		hr = pTransientGeometry->CreatePoint(dRackEdgeStartPtX - m_dRackExtents * dRackPositiveExtentDirectionX,
											dRackEdgeStartPtY - m_dRackExtents * dRackPositiveExtentDirectionY,
											dRackEdgeStartPtZ - m_dRackExtents * dRackPositiveExtentDirectionZ,
											&pGraphicsParallelEdgeStartPt);
		break;

	case kPositiveExtentDirection:

		hr = pRackEdgeStartPt.QueryInterface(&pGraphicsEdgeStartPt);

		hr = pTransientGeometry->CreatePoint(dRackEdgeStartPtX + m_dRackExtents * dRackPositiveExtentDirectionX,
											dRackEdgeStartPtY + m_dRackExtents * dRackPositiveExtentDirectionY,
											dRackEdgeStartPtZ + m_dRackExtents * dRackPositiveExtentDirectionZ,
											&pGraphicsParallelEdgeStartPt);
		break;

	case kSymmetricExtentDirection:

		hr = pTransientGeometry->CreatePoint(dRackEdgeStartPtX - m_dRackExtents * dRackPositiveExtentDirectionX,
											dRackEdgeStartPtY - m_dRackExtents * dRackPositiveExtentDirectionY,
											dRackEdgeStartPtZ - m_dRackExtents * dRackPositiveExtentDirectionZ,
											&pGraphicsEdgeStartPt);

		hr = pTransientGeometry->CreatePoint(dRackEdgeStartPtX + m_dRackExtents * dRackPositiveExtentDirectionX,
											dRackEdgeStartPtY + m_dRackExtents * dRackPositiveExtentDirectionY,
											dRackEdgeStartPtZ + m_dRackExtents * dRackPositiveExtentDirectionZ,
											&pGraphicsParallelEdgeStartPt);
		break;


	}

	double dGraphicsEdgeStartPtX, dGraphicsEdgeStartPtY, dGraphicsEdgeStartPtZ;
	hr = GetPointCoordinates(pGraphicsEdgeStartPt, &dGraphicsEdgeStartPtX, &dGraphicsEdgeStartPtY, &dGraphicsEdgeStartPtZ);
	if (FAILED(hr)) return hr;

	double dGraphicsParallelEdgeStartPtX, dGraphicsParallelEdgeStartPtY, dGraphicsParallelEdgeStartPtZ;
	hr = GetPointCoordinates(pGraphicsParallelEdgeStartPt, &dGraphicsParallelEdgeStartPtX, &dGraphicsParallelEdgeStartPtY, &dGraphicsParallelEdgeStartPtZ);
	if (FAILED(hr)) return hr;

	//get the rack parallel edge start point and end point
	double dRackEdgeLength{0.0};
	hr = pRackEdgeStartPt->DistanceTo(pRackEdgeStopPt, &dRackEdgeLength);
	
	double dNonRackWidth = dRackEdgeLength - m_dRackWidth;

	double dToothWidthProportion = 0.35;

	double dToothMajorWidth  = m_dRackWidth  / (m_iNoTeeth + (m_iNoTeeth - 1) * dToothWidthProportion);

	double dToothMinorWidth = dToothWidthProportion * dToothMajorWidth;

	double dToothSlopeWidth = (dToothMajorWidth - dToothMinorWidth) / 2.0;

	CComPtr<Point> pPoint1,pPoint2,pPoint3,pPoint4;
	hr = pTransientGeometry->CreatePoint(dGraphicsEdgeStartPtX + (((dNonRackWidth / 2) / dRackEdgeLength) * dRackEdgeLengthX),
									dGraphicsEdgeStartPtY + (((dNonRackWidth / 2) / dRackEdgeLength) * dRackEdgeLengthY),
									dGraphicsEdgeStartPtZ + (((dNonRackWidth / 2) / dRackEdgeLength) * dRackEdgeLengthZ),
									&pPoint1);

	hr = pTransientGeometry->CreatePoint(dGraphicsParallelEdgeStartPtX + (((dNonRackWidth / 2) / dRackEdgeLength) * dRackEdgeLengthX),
									dGraphicsParallelEdgeStartPtY + (((dNonRackWidth / 2) / dRackEdgeLength) * dRackEdgeLengthY),
									dGraphicsParallelEdgeStartPtZ + (((dNonRackWidth / 2) / dRackEdgeLength) * dRackEdgeLengthZ),
									&pPoint3);

	hr = AddGraphicsPoints(pPoint1, pPoint3);

	double Xnr = dRackFaceNormalX * m_dRackHeight;
	double Ynr = dRackFaceNormalY * m_dRackHeight;
	double Znr = dRackFaceNormalZ * m_dRackHeight;

	double Xintv = dToothSlopeWidth * dRackEdgeLengthX / dRackEdgeLength;
	double Yintv = dToothSlopeWidth * dRackEdgeLengthY / dRackEdgeLength;
	double Zintv = dToothSlopeWidth * dRackEdgeLengthZ / dRackEdgeLength;

	double Xsht = dToothMinorWidth * dRackEdgeLengthX / dRackEdgeLength;
	double Ysht = dToothMinorWidth * dRackEdgeLengthY / dRackEdgeLength;
	double Zsht = dToothMinorWidth * dRackEdgeLengthZ / dRackEdgeLength;

	for (int iToothCt = 1; iToothCt <= m_iNoTeeth; iToothCt++)
	{
		double dPoint1X, dPoint1Y, dPoint1Z;
		hr = GetPointCoordinates(pPoint1, &dPoint1X, &dPoint1Y, &dPoint1Z);

		double dPoint3X, dPoint3Y, dPoint3Z;
		hr = GetPointCoordinates(pPoint3, &dPoint3X, &dPoint3Y, &dPoint3Z);

		hr = pTransientGeometry->CreatePoint(dPoint1X + Xintv - Xnr, dPoint1Y + Yintv - Ynr, dPoint1Z + Zintv - Znr, &pPoint2);
		hr = pTransientGeometry->CreatePoint(dPoint3X + Xintv - Xnr, dPoint3Y + Yintv - Ynr, dPoint3Z + Zintv - Znr, &pPoint4);

		hr = AddGraphicsPoints(pPoint2, pPoint4);
		hr = AddColorIndex(1);

		pPoint1 = NULL; 
		pPoint3 = NULL;

		double dPoint2X, dPoint2Y, dPoint2Z;
		hr = GetPointCoordinates(pPoint2, &dPoint2X, &dPoint2Y, &dPoint2Z);

		double dPoint4X, dPoint4Y, dPoint4Z;
		hr = GetPointCoordinates(pPoint4, &dPoint4X, &dPoint4Y, &dPoint4Z);

		hr = pTransientGeometry->CreatePoint(dPoint2X + Xsht, dPoint2Y + Ysht, dPoint2Z + Zsht, &pPoint1);
		hr = pTransientGeometry->CreatePoint(dPoint4X + Xsht, dPoint4Y + Ysht, dPoint4Z + Zsht, &pPoint3);

		hr = AddGraphicsPoints(pPoint1, pPoint3);
		hr = AddColorIndex(2);

		pPoint2 = NULL;
		pPoint4 = NULL;

		hr = GetPointCoordinates(pPoint1, &dPoint1X, &dPoint1Y, &dPoint1Z);
		hr = GetPointCoordinates(pPoint3, &dPoint3X, &dPoint3Y, &dPoint3Z);

		hr = pTransientGeometry->CreatePoint(dPoint1X + Xintv + Xnr, dPoint1Y + Yintv + Ynr, dPoint1Z + Zintv + Znr, &pPoint2);
		hr = pTransientGeometry->CreatePoint(dPoint3X + Xintv + Xnr, dPoint3Y + Yintv + Ynr, dPoint3Z + Zintv + Znr, &pPoint4);

		hr = AddGraphicsPoints(pPoint2, pPoint4);
		hr = AddColorIndex(1);

		pPoint1 = NULL; 
		pPoint3 = NULL;

		hr = GetPointCoordinates(pPoint2, &dPoint2X, &dPoint2Y, &dPoint2Z);
		hr = GetPointCoordinates(pPoint4, &dPoint4X, &dPoint4Y, &dPoint4Z);

		hr = pTransientGeometry->CreatePoint(dPoint2X + Xsht, dPoint2Y + Ysht, dPoint2Z + Zsht, &pPoint1);
		hr = pTransientGeometry->CreatePoint(dPoint4X + Xsht, dPoint4Y + Ysht, dPoint4Z + Zsht, &pPoint3);

		if (iToothCt != m_iNoTeeth)
		{
			hr = AddGraphicsPoints(pPoint1, pPoint3);
			hr = AddColorIndex(2);

			pPoint2 = NULL;
			pPoint4 = NULL;
		}

	}

	CComPtr<View> pActiveView;
	hr = m_pApplication->get_ActiveView(&pActiveView);

	hr = pActiveView->Update();

	return S_OK;

}

HRESULT CRackFaceCmd::AddGraphicsPoints(Point *pCornerPt1, Point *pCornerPt2)
{
	HRESULT hr;	
	
	long lNoGraphicsCoordPts;
	hr = m_pGraphicsCoordinateSet->get_Count(&lNoGraphicsCoordPts);
	if (FAILED(hr)) return hr;

	hr = m_pGraphicsCoordinateSet->Add(lNoGraphicsCoordPts + 1, pCornerPt1);
	hr = m_pGraphicsCoordinateSet->Add(lNoGraphicsCoordPts + 2, pCornerPt2);

	return S_OK;

}

HRESULT CRackFaceCmd::AddColorIndex(long lColorIndex)
{
	HRESULT hr;	
	
	long lNoGraphicsColorIndices;
	hr = m_pGraphicsColorIndexSet->get_Count(&lNoGraphicsColorIndices);
	if (FAILED(hr)) return hr;

	hr = m_pGraphicsColorIndexSet->Add(lNoGraphicsColorIndices + 1, lColorIndex);
	hr = m_pGraphicsColorIndexSet->Add(lNoGraphicsColorIndices + 2, lColorIndex);
	
	return S_OK;

}

HRESULT CRackFaceCmd::GetPointCoordinates(Point *pPoint, double *dX, double *dY, double *dZ)
{
	HRESULT hr;

	hr = pPoint->get_X(dX);
	if (FAILED(hr)) return hr;

	hr = pPoint->get_Y(dY);
	if (FAILED(hr)) return hr;

	hr = pPoint->get_Z(dZ);
	if (FAILED(hr)) return hr;

	return S_OK;

}

HRESULT CRackFaceCmd::GetVectorCoordinates(UnitVector *pUnitVector, double *dX, double *dY, double *dZ)
{
	HRESULT hr;

	hr = pUnitVector->get_X(dX);
	if (FAILED(hr)) return hr;

	hr = pUnitVector->get_Y(dY);
	if (FAILED(hr)) return hr;

	hr = pUnitVector->get_Z(dZ);
	if (FAILED(hr)) return hr;

	return S_OK;

}

void CRackFaceCmd::TerminatePreviewGraphics()
{
	m_pGraphicsCoordinateSet = NULL;
	m_pGraphicsColorSet = NULL;
	m_pGraphicsColorIndexSet = NULL;
	m_pTriangleStripGraphics = NULL;
	m_pPreviewClientGraphicsNode = NULL;
}