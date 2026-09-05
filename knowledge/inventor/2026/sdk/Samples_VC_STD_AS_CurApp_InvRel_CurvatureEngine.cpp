/*
  DESCRIPTION

  Implementation of the API-related methods of the CCurvatureEngine class. 


  HISTORY

  AA  :  10/15/99  :  Creation
*/

#include <stdafx.h>
#include "referencekeyengine.h"
#include "curvatureengine.h"

#include <vector>
#include <math.h>

#include "facets.h"

/*------------------------ API-related functions -----------------------------*/


// The Face is supplied via the its Persistent Key interface. The number of points to be computed in the
// U-parametric direction and the V-parametric direction are supplied. The method 
// returns a ray for each point of the implied grid that ends up lying inside the Face's
// bounded region. The length of the vector returned is the Barry Curvature at that 
// point and the direction is the direction is that of the normal at that point.
// If the value of the curvature is greater than the 'cutOff' it is truncated.

HRESULT CCurvatureEngine::CalculatePinCushion (IRxReferenceKey *pFaceRefKey,
                                               int uDensity,
                                               int vDensity,
                                               double cutOff,
                                               ULONG* o_pNumPoints,
                                               double** o_ppPoints,
                                               double** o_ppNormals)
{
	HRESULT hr=NOERROR;
	IRxFace* pFace = 0;
	IRxSurfaceEvaluator* pSurface = 0;
	IRxBox2d* pRange2d = 0;
	int uBegin, vBegin;
	int uEnd, vEnd;
	int ii = 0, jj = 0, kk = 0;
	double uParamDelta, vParamDelta;
	double* pMinParam = 0; double* pMaxParam = 0;
	LONG nParams = 0;
	double aParam[2];
	boolean bIsOnFace = false;
	double* pParams = 0;
	double* pPoints = 0;
	double* pNormals = 0;
	double* pMinCurvatures = 0;
	double* pMaxCurvatures = 0;
	double* pBarryCurvatures = 0;
	double* pRadiusOfCurvatures = 0;

	// Check and initialize output
	//
	OnErrorReturn (!pFaceRefKey || !o_pNumPoints || !o_ppPoints || !o_ppNormals, E_INVALIDARG);
	*o_pNumPoints = 0;
	*o_ppPoints = NULL;
	*o_ppNormals = NULL;

	// Get the last selected face
	//
	hr = pFaceRefKey->QueryInterface(IID_IRxFace, (void**)&pFace);
	OnErrorReturn(FAILED(hr), hr);

	// Get the eval geometry for this face
	//
	hr = pFace->get_Evaluator(&pSurface);
	OnError(FAILED(hr), wrapup);

	// Query for surface extents in parametric space
	//
	hr = pSurface->get_ParamRangeRect(&pRange2d);
	OnError(FAILED(hr), wrapup);

	pMinParam = (double*) ::CoTaskMemAlloc(2 * sizeof(double));
	pMaxParam = (double*) ::CoTaskMemAlloc(2 * sizeof(double));
	hr = pRange2d->GetBoxData(pMinParam, pMaxParam);
	OnError(FAILED(hr), wrapup);

	// Figure out if we have any discontinuous points on this surface
	//
	uBegin = 0; vBegin = 0;
	uEnd = uDensity; vEnd = vDensity;

	// Based on the user opted u and v densities, calculate the [u,v] parametric
	// locations where we would want to query the curvature information
	//
	uParamDelta = (pMaxParam[0] - pMinParam[0]) / (uDensity-1);
	vParamDelta = (pMaxParam[1] - pMinParam[1]) / (vDensity-1);

	nParams = uEnd * vEnd;
	pParams = new double[2 * nParams];
	for(ii = uBegin; ii < uEnd; ++ii) 
	{
		for(jj = vBegin; jj < vEnd; ++jj) 
		{
			bIsOnFace = false;
			aParam[0] = pMinParam[0] + (ii * uParamDelta);
			aParam[1] = pMinParam[1] + (jj * vParamDelta);
			hr = pSurface->get_IsParamOnFace(aParam, (char*)&bIsOnFace);
			OnError(FAILED(hr), wrapup);

			if(bIsOnFace) 
			{
				pParams[kk++] = aParam[0];
				pParams[kk++] = aParam[1];
			}
		}
	}
	nParams = kk / 2;

	// Get the 3d points at these param values
	//
	pPoints = new double[3 * nParams];
	hr = pSurface->GetPointAtParam(nParams, pParams, pPoints);
	OnError(FAILED(hr), wrapup);

	// Get the normals at these param values
	//
	pNormals = new double[3 * nParams];
	hr = pSurface->GetNormal(nParams, pParams, pNormals);
	OnError(FAILED(hr), wrapup);

	// Get the curvatures at these param values
	//
	pMinCurvatures = new double[nParams];
	pMaxCurvatures = new double[nParams];
	hr = pSurface->GetCurvatures(nParams, pParams, NULL, pMaxCurvatures, pMinCurvatures);
	OnError(FAILED(hr), wrapup);

	// Calculate the Barry curvature's from the min and max curvatures
	// Barry curvature = RMS of min and max curvatures
	//
	pBarryCurvatures = new double[nParams];
	for(ii = 0; ii < nParams; ++ii) 
	{
		pBarryCurvatures[ii] = sqrt(pMinCurvatures[ii] * pMinCurvatures[ii] + pMaxCurvatures[ii] * pMaxCurvatures[ii]);

		// Uncomment the two lines below if you wish to get a feel of the convexity or concavity
		// of the surfaces.
		// The sign signifies whether the center of curvature lies inside or outside the surface.
		// If the sign is positive, the center is inside. In other words, if the sign is positive,
		// the center is not in the same direction as the normal at that point.
		//if(0.0 > ((pMinCurvatures[ii] + pMaxCurvatures[ii]) / 2))
		//  pBarryCurvatures[ii] *= -1;
	}

	// Calculate the radius of curvature from the curvature values
	//
	pRadiusOfCurvatures = new double[nParams];
	for(ii = 0; ii < nParams; ++ii) 
	{
		if(fabs(pBarryCurvatures[ii]) > 0.000001) // greater than zero
			pRadiusOfCurvatures[ii] = 1.0 / pBarryCurvatures[ii];
		else
			pRadiusOfCurvatures[ii] = 0.0;

		// Cap off the radius of curvature value at cutOff
		//
		if(pRadiusOfCurvatures[ii] > cutOff)
			pRadiusOfCurvatures[ii] = cutOff;
		else if(pRadiusOfCurvatures[ii] < -cutOff)
			pRadiusOfCurvatures[ii] = -cutOff;
	}

	// Multiply the radius of curvature to the normals at each of these locations
	// to get the curvature vectors
	//
	for(ii = 0; ii < nParams; ++ii) 
	{
		if(!pRadiusOfCurvatures[ii])
			continue;

		pNormals[3*ii + 0] *= pRadiusOfCurvatures[ii];
		pNormals[3*ii + 1] *= pRadiusOfCurvatures[ii];
		pNormals[3*ii + 2] *= pRadiusOfCurvatures[ii];
	}

	*o_pNumPoints = nParams;
	*o_ppPoints = pPoints;
	*o_ppNormals = pNormals;

	wrapup:
	if(pFace)
		pFace->Release();
	if(pSurface)
		pSurface->Release();
	if(pRange2d)
		pRange2d->Release();

	if(pMinParam)
		::CoTaskMemFree(pMinParam);
	if(pMaxParam)
		::CoTaskMemFree(pMaxParam);

	delete [] pParams;
	if(!(*o_ppPoints))
		delete [] pPoints;
	if(!(*o_ppNormals))
		delete [] pNormals;
	delete [] pMinCurvatures;
	delete [] pMaxCurvatures;
	delete [] pBarryCurvatures;
	delete [] pRadiusOfCurvatures;
	return hr;
}

// The Face is supplied via its Persistent Key interface. The chordal-height tolerance is supplied which
// is a measure of the fineness with which to compute the curvature map. The method 
// then returns a mesh of triangles (facets) identical in structure to the mesh returned
// for display. Except that the normal's length is the actual value of the Barry
// Curvature at that vertex. The calling function then assigns colors to each of these

HRESULT CCurvatureEngine::CalculateCurvatureGradient(IRxReferenceKey *pFaceRefKey,
                                                     double chordTol,
                                                     double cutOff,
                                                     ULONG* pNumVertices,
                                                     double** ppVertices,
                                                     double** ppNormals,
                                                     ULONG* pNumFacets,
                                                     ULONG** ppVertexIndices)
{
	OnErrorReturn(!pFaceRefKey || !pNumVertices || !ppVertices || !ppNormals || !pNumFacets || !ppVertexIndices, E_INVALIDARG);

	// Initialize input variables
	//
	*pNumVertices = 0;
	*ppVertices = 0;
	*ppNormals = 0;
	*pNumFacets = 0;
	*ppVertexIndices = 0;

	IRxFacets* pFacets = NULL;
	IRxFace* pFace = NULL;
	IRxSurfaceEvaluator* pSurface = NULL;
	ULONG ii = 0;
	double* pParams = 0;
	double* pMinCurvatures = 0;
	double* pMaxCurvatures = 0;
	double* pBarryCurvatures = 0;
	double* pRadiusOfCurvatures = 0;


	// Get the facet information for this face
	//

	HRESULT hr = pFaceRefKey->QueryInterface(IID_IRxFacets, (void**) &pFacets);
	OnError(FAILED(hr), wrapup);

	hr = GetFacets (pFacets, pNumVertices, ppVertices, ppNormals, pNumFacets, ppVertexIndices, chordTol);
	OnError(FAILED(hr), wrapup);

	// Query for the face interface
	//
	hr = pFaceRefKey->QueryInterface(IID_IRxFace, (void**)&pFace);
	OnErrorReturn(FAILED(hr), hr);

	// Get the eval geometry for this face
	//
	hr = pFace->get_Evaluator(&pSurface);
	OnError(FAILED(hr), wrapup);

	// Find the corresponding parametric locations for the 3d points
	//
	pParams = reinterpret_cast<double*> (new double[2* (*pNumVertices)]);

	//Create a temporary array used to get the parametric locations.
	//This temporary array will be modified by the function "GetParamAtPoint" when using ApprenticeServer,
	//so it can not be used again after the function "GetParamAtPoint.
	//The array "*ppVertices" can be used again after the function "GetParamAtPoint".
	//
	double *pTempVertices = NULL;
	pTempVertices = (double*)CoTaskMemAlloc((*pNumVertices * 3) * sizeof(**ppVertices));
	
	if (pTempVertices != NULL)
		memcpy((void*)pTempVertices, (void*)*ppVertices, (size_t)((*pNumVertices * 3) * sizeof(**ppVertices)));
	else
		OnError(FAILED(E_FAIL), wrapup);

	hr = pSurface->GetParamAtPoint( *pNumVertices, pTempVertices, NULL, NULL, pParams, NULL);

	CoTaskMemFree((void*)pTempVertices);

	OnError(FAILED(hr), wrapup);

	// Get the curvatures at these param values
	//
	pMinCurvatures = new double[*pNumVertices];
	pMaxCurvatures = new double[*pNumVertices];
	hr = pSurface->GetCurvatures(*pNumVertices, pParams, NULL, pMaxCurvatures, pMinCurvatures);
	OnError(FAILED(hr), wrapup);

	// Calculate the Barry curvature's from the min and max curvatures
	// Barry curvature = RMS of min and max curvatures
	//
	pBarryCurvatures = new double[*pNumVertices];
	for(ii = 0; ii < *pNumVertices; ++ii) 
	{
		pBarryCurvatures[ii] = sqrt(pMinCurvatures[ii] * pMinCurvatures[ii] + pMaxCurvatures[ii] * pMaxCurvatures[ii]);

		// Uncomment the two lines below if you wish to get a feel of the convexity or concavity
		// of the surfaces.
		// The sign signifies whether the center of curvature lies inside or outside the surface.
		// If the sign is positive, the center is inside. In other words, if the sign is positive,
		// the center is not in the same direction as the normal at that point.
		//if(0.0 > ((pMinCurvatures[ii] + pMaxCurvatures[ii]) / 2))
		//  pBarryCurvatures[ii] *= -1;
	}

	// Calculate the radius of curvature from the curvature values
	//
	pRadiusOfCurvatures = new double[*pNumVertices];
	for(ii = 0; ii < *pNumVertices; ++ii) 
	{
		if(fabs(pBarryCurvatures[ii]) > 0.000001) // greater than zero
			pRadiusOfCurvatures[ii] = 1.0 / pBarryCurvatures[ii];
		else
			pRadiusOfCurvatures[ii] = 0.0;

		// Cap off the radius of curvature value at cutOff
		if(pRadiusOfCurvatures[ii] > cutOff)
			pRadiusOfCurvatures[ii] = cutOff;
		else if(pRadiusOfCurvatures[ii] < -cutOff)
			pRadiusOfCurvatures[ii] = -cutOff;
	}

	// Multiply the radius of curvature to the normals at each of these locations
	// to get the curvature vectors
	//
	for(ii = 0; ii < *pNumVertices; ++ii) 
	{
		if(!pRadiusOfCurvatures[ii])
			continue;

		(*ppNormals)[3*ii + 0] *= pRadiusOfCurvatures[ii];
		(*ppNormals)[3*ii + 1] *= pRadiusOfCurvatures[ii];
		(*ppNormals)[3*ii + 2] *= pRadiusOfCurvatures[ii];
	}

	wrapup:
	if(pFacets)
		pFacets->Release();
	if(pFace)
		pFace->Release();
	if(pSurface)
		pSurface->Release();
	if(pParams)
		delete [] pParams;

	if(FAILED(hr)) 
	{
		*pNumVertices = 0;
		::CoTaskMemFree(*ppVertices); *ppVertices = 0;
		::CoTaskMemFree(*ppNormals); *ppNormals = 0;
		*pNumFacets = 0;
		::CoTaskMemFree(*ppVertexIndices); *ppVertexIndices = 0;
	}

	delete [] pMinCurvatures;
	delete [] pMaxCurvatures;
	delete [] pBarryCurvatures;
	delete [] pRadiusOfCurvatures;

	return hr;
}
