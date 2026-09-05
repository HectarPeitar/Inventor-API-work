/*
  DESCRIPTION

  Implementation of the management methods of the CMeasureEngine class. 


  HISTORY

  SAM  :  10/15/99  :  Creation
*/

#include <stdafx.h>
#include <math.h>
#include "../AppRelated/MeasureDlg.h"
#include "measureengine.h"
#include "referencekeyengine.h"

/*------------------------ API-related functions -----------------------------*/

// Function takes in the Reference Key interface to the Face and outputs its
// area, calling into the Geometry & Topology API

HRESULT CMeasureEngine::MeasureFace(IRxReferenceKey *pFaceRefKey, double *area)
{
	HRESULT hr=NOERROR;
	IRxFace *pFace=NULL;
	IRxSurfaceEvaluator* pSurface=NULL;

	// If there is no key, return error
	//
	OnErrorReturn(!pFaceRefKey, E_INVALIDARG);

	// Initialize the outputs
	//
	*area = 0.0;

	// Get the face
	//
	hr = pFaceRefKey->QueryInterface(IID_IRxFace, (void**)&pFace);
	OnErrorReturn(FAILED(hr), hr);

	// Get the eval geometry (surface) for this face
	//
	hr = pFace->get_Evaluator(&pSurface);
	OnError(FAILED(hr), wrapup);

	// Get the area
	//
	hr = pSurface->get_Area(area);
	OnError(FAILED(hr), wrapup);

wrapup:
	// Release the resources
	//
	if(pSurface) { pSurface->Release(); pSurface = NULL; }
	if(pFace) { pFace->Release(); pFace = NULL; }

	return hr;
}


// Function takes in the Reference Key interface to the Edge and outputs its
// length, calling into the Geometry & Topology API
HRESULT CMeasureEngine::MeasureEdge(IRxReferenceKey *pEdgeRefKey, double *length)
{
	HRESULT hr=NOERROR;
	IRxEdge *pEdge=NULL;
	IRxCurveEvaluator* pCurve=NULL;
	double params[2];

	// If there is no key, return error
	//
	OnErrorReturn(!pEdgeRefKey, E_INVALIDARG);

	// Initialize the outputs
	//
	*length = 0.0;

	// Get the last selected face
	//
	hr = pEdgeRefKey->QueryInterface(IID_IRxEdge, (void**)&pEdge);
	OnErrorReturn(FAILED(hr), hr);

	// Get the eval geometry (curve) for this edge
	//
	hr = pEdge->get_Evaluator(&pCurve);
	OnError(FAILED(hr), wrapup);

	// Get the param extents
	//
	hr = pCurve->GetParamExtents(params, &params[1]);
	OnError(FAILED(hr), wrapup);

	// Now get the length between the 2 params
	//
	hr = pCurve->GetLengthAtParam (params[0], params[1], length);
	OnError(FAILED(hr), wrapup);

wrapup:
	// Release the resources
	//
	if(pCurve) { pCurve->Release(); pCurve = NULL; }
	if(pEdge) { pEdge->Release(); pEdge = NULL; }

	return hr;
}


// Function takes in the Reference Key interfaces to the two Verticese and outputs the
// distance between them, calling into the Geometry & Topology API
HRESULT CMeasureEngine::MeasureDistance(IRxReferenceKey *pVtx1RefKey, IRxReferenceKey *pVtx2RefKey, double *distance)
{
	HRESULT hr=NOERROR;
	IRxVertex *pPoint1=NULL, *pPoint2=NULL;
	double pt1[3], pt2[3], distSq=0.0;

	// If there is no keys, return error
	//
	OnErrorReturn(!pVtx1RefKey, E_INVALIDARG);
	OnErrorReturn(!pVtx2RefKey, E_INVALIDARG);

	// Initialize the outputs
	//
	*distance = 0.0;

	// Quick error check
	//
	OnErrorReturn((pVtx1RefKey == pVtx2RefKey), S_FALSE);

	// Get the underlying points
	//
	hr = pVtx1RefKey->QueryInterface(IID_IRxVertex, (void**)&pPoint1);
	OnErrorReturn(FAILED(hr), hr);

	hr = pVtx2RefKey->QueryInterface(IID_IRxVertex, (void**)&pPoint2);
	OnErrorReturn(FAILED(hr), hr);

	// Get the xyz points
	//
	hr = pPoint1->GetPoint(pt1);
	OnError(FAILED(hr), wrapup);

	hr = pPoint2->GetPoint(pt2);
	OnError(FAILED(hr), wrapup);

	// Compute the distance
	//
	distSq = (  (pt2[0]-pt1[0]) * (pt2[0]-pt1[0]) + 
		  (pt2[1]-pt1[1]) * (pt2[1]-pt1[1]) + 
		  (pt2[2]-pt1[2]) * (pt2[2]-pt1[2])  );

	OnError((distSq < (PTEQTOL * PTEQTOL)), wrapup);

	*distance = sqrt(distSq);

wrapup:
	// Release the resources
	//
	if(pPoint1) { pPoint1->Release(); pPoint1 = NULL; }
	if(pPoint2) { pPoint2->Release(); pPoint2 = NULL; }

	return hr;
}
  
