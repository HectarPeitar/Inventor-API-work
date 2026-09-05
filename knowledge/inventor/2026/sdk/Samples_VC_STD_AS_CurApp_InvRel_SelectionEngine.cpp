/*
  DESCRIPTION

  Implementation of the API-related methods of the CCurvatureEngine class. 


  HISTORY

  SAM  :  10/15/99  :  Creation
  SS   :  05/10/01  :  Updated
*/


#include <stdafx.h>
#include "selectionengine.h"
#include <math.h>

#include "facets.h"

enum AppSelectMode
{ 
  eUnknownFilter = 0x0, 
  eFaceFilter = 0x01, 
  eEdgeFilter = 0x02, 
  eVertexFilter = 0x03
};

/*------------------------ API-related functions -----------------------------*/

// This function is used by the application to detect the BRep objects that are
// 'hit' or 'picked' by the a given line segment. A radius around the line segment
// is specified as the vicinity within which to search. The search can be restricted
// to Faces, Edges, Vertices or some combinations thereof. The 'picked' objects are
// returned with the IRxReferenceKey interfaces inside a collection. The collection
// is returned sorted -- with the object nearest the first point of the line segment
// (also called the bore line) as the first element in the collection.

HRESULT CSelectionEngine::GetSelection(/* [in]  */ IRxComponentDocument * pDoc,
                                       /* [in]  */ AppSelectMode eSelectMode,
                                       /* [in]  */ double dLocateRadius,                                          
                                       /* [in]  */ double *pBoreVecPt1,
                                       /* [in]  */ double *pBoreVecPt2,
                                       /* [out] */ IRxReferenceKey **ppSelObjKey)
{
	HRESULT hr = NOERROR;
	IRxGeometricLocate *pDocLocate = NULL;
	BoreLineStruct boreline;
	ULONG dwNumTypes = 1;
	IID pType = IID_IRxFace;
	double veclen = 0;
	double unitvec[3];
	IRxEnumReferenceKeys *pEnumRefKeys = NULL;
	IRxReferenceKey *pRefKey = NULL;
	ULONG nFetched = 0;

	// Check the inputs
	//
	OnErrorReturn(!pDoc, E_INVALIDARG);
	OnErrorReturn(!pBoreVecPt1, E_INVALIDARG);
	OnErrorReturn(!pBoreVecPt2, E_INVALIDARG);
	OnErrorReturn(!ppSelObjKey, E_INVALIDARG);

	// Initialize
	//
	*ppSelObjKey = NULL;

	// set the locate filter
	//
	if(eFaceFilter == eSelectMode)
		pType = IID_IRxFace;
	else if(eEdgeFilter == eSelectMode)
		pType = IID_IRxEdge;
	else if(eVertexFilter == eSelectMode)
		pType = IID_IRxVertex;
	else
		OnErrorReturn(TRUE, E_INVALIDARG);

	// Get the locate interface
	//
	hr = pDoc->QueryInterface(IID_IRxGeometricLocate, (void **)&pDocLocate);
	OnError(FAILED(hr), wrapup);

	// Prepare the Boreline
	//
	boreline.m_point[0] = pBoreVecPt1[0];
	boreline.m_point[1] = pBoreVecPt1[1];
	boreline.m_point[2] = pBoreVecPt1[2];

	unitvec[0] = pBoreVecPt2[0] - pBoreVecPt1[0];
	unitvec[1] = pBoreVecPt2[1] - pBoreVecPt1[1];
	unitvec[2] = pBoreVecPt2[2] - pBoreVecPt1[2];

	veclen =  sqrt(unitvec[0] * unitvec[0] + unitvec[1] * unitvec[1] + unitvec[2] * unitvec[2]);

	// prepare the direction unit vector
	//
	unitvec[0] = unitvec[0]/veclen;
	unitvec[1] = unitvec[1]/veclen;
	unitvec[2] = unitvec[2]/veclen;

	// Intialize the boreline
	//
	boreline.m_direction[0] = unitvec[0];
	boreline.m_direction[1] = unitvec[1];
	boreline.m_direction[2] = unitvec[2];

	boreline.m_front = 10000;           //10000 * Container to Server scale 
	boreline.m_back = -10000;           //-10000 * Container to Server scale
	boreline.m_radius = dLocateRadius;  //dLocateRadius * Container to Server scale

	// Fire the locate
	//
	hr = pDocLocate->PointLocate(&boreline, dwNumTypes, &pType, &pEnumRefKeys);
	OnErrorState(FAILED(hr) || !pEnumRefKeys, hr, E_FAIL, wrapup);

	// Grab the 1st one, cause it is sorted (the closet element first)
	//
	hr = pEnumRefKeys->Next(1, &pRefKey, &nFetched);
	if (hr == S_OK)
	{
		*ppSelObjKey = pRefKey;
	}

wrapup:

	// Release the resource
	//
	pDoc->Release();
	if(pDocLocate)
		pDocLocate->Release();
	if(pEnumRefKeys)
		pEnumRefKeys->Release();

	return hr;
}

// This function is used by the application to retrieve the strokes or the polyline
// representation of a given BRep object. This set of strokes is then used to highlight
// the object within the process of the 'pick' command.
//
// The output of the strokes is in the following format:
//   ULONG *pNumVertices; // number of vertices. corresponds 
//   double **ppVertices; // array of vertices arranged in [x,y,z] values
//   ULONG *pNumSegments;  // number of line segments
//   ULONG **ppEndPointIndices;   // array of vertex indices that form each line segment;
//                                // a pair for each.
//
// NOTE: Strokes, facets are CoTaskMemAlloc'd by the server

HRESULT CSelectionEngine::GetSelectStrokes(/* [in]  */ IRxReferenceKey *pSelObjKey,
                                           /* [in]  */ double chordHeightTol,
                                           /* [out] */ ULONG *pNumVertices,
                                           /* [out] */ double **ppVertices,
                                           /* [out] */ ULONG *pNumSegments,
                                           /* [out] */ ULONG **ppEndpointIndices)
{
	HRESULT hr = NOERROR;
	double pt[3];  // pts for a vertex

	// Check the inputs
	//
	OnErrorReturn(!pSelObjKey, E_INVALIDARG);
	OnErrorReturn(!pNumVertices, E_INVALIDARG);
	OnErrorReturn(!ppVertices, E_INVALIDARG);
	OnErrorReturn(!pNumSegments, E_INVALIDARG);
	OnErrorReturn(!ppEndpointIndices, E_INVALIDARG);

	// Initialize
	//
	*pNumVertices = 0;
	*ppVertices = NULL;
	*pNumSegments = 0;
	*ppEndpointIndices = NULL;

	// See if this is a Vertex that got selected, else it is a Face or an Edge

	CComPtr<IRxVertex> pVertex;
	hr = pSelObjKey->QueryInterface(IID_IRxVertex, (void **)&pVertex);
	if(SUCCEEDED(hr)) // Vertex
	{
		hr = pVertex->GetPoint(pt);

		*pNumVertices = 1;
		(*ppVertices) = (double *)::CoTaskMemAlloc(*pNumVertices * 3 * sizeof(double));
		(*ppVertices)[0] = pt[0]; (*ppVertices)[1] = pt[1]; (*ppVertices)[2] = pt[2];
		*pNumSegments = 1;
		(*ppEndpointIndices) = (ULONG *)::CoTaskMemAlloc(sizeof(ULONG) * 2);
		(*ppEndpointIndices)[0] = 0;
		(*ppEndpointIndices)[1] = 0;
	}
	else  //face or an edge
	{
		CComPtr<IRxStrokes> pStrokes;
		hr = m_pRefKey->QueryInterface(IID_IRxStrokes, (void **)&pStrokes);
		OnErrorReturn(FAILED(hr), hr);

		hr = GetStrokes (pStrokes, pNumVertices, ppVertices, pNumSegments, ppEndpointIndices, chordHeightTol);
		OnErrorReturn(FAILED(hr), hr);
	}

	return S_OK;
}