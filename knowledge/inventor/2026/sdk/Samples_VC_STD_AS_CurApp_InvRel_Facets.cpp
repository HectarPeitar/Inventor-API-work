/*
  DESCRIPTION

  The functions in this file deal with the retrieval/generation of the facets and strokes pertaining
  to a SurfaceBOdy, Face or an Edge.


  HISTORY

  SS  05/10/01  :  Modified
*/

#include "stdafx.h"

HRESULT GetFacets (IRxFacets *pFacets, 
                   ULONG* pNumVertices, double** ppVertices, double** ppNormals,
                   ULONG* pNumFacets, ULONG** ppVertexIndices,
                   double AltChordTol)
{
  HRESULT hr=NOERROR;

  // First, try to obtain facets from the set of pre-existing ones already
  // present inside the Inventor Part file

  ULONG nTolerances;
  double* pTols{ nullptr };
  hr = pFacets->GetExistingTolerances(&nTolerances, &pTols);
  OnErrorReturn(FAILED(hr), hr);

  // This means that we have sets of facets, pre-existing within the file; one 
  // set of facets per each individual tolerance. Obtain the facets for an arbitrarily
  // selected tolerance (you can be more sophisticated and pick one that more closes matches the
  // current zoom factor and the viewing extents). The input tolerance is largely 
  // ignored in favor of one that has been found with associated facets.

  double Tol = pTols[0];
  ::CoTaskMemFree (pTols);

  float *pFVertices = NULL;
  float *pFNormals = NULL;
  hr = pFacets->GetExistingFacets (Tol,  pNumVertices, &pFVertices, &pFNormals, pNumFacets, ppVertexIndices);
  OnErrorReturn(FAILED(hr), hr);

  // Convert the floats into doubles, since that is the currency in which OpenGL
  // and the rest of the code deals with.

  *ppVertices = (double *) ::CoTaskMemAlloc (sizeof (double) * (*pNumVertices * 3));
  *ppNormals  = (double *) ::CoTaskMemAlloc (sizeof (double) * (*pNumVertices * 3));
  for(UINT i=0; i<(*pNumVertices) * 3; i++)
  {
    (*ppVertices)[i] = pFVertices[i];
    (*ppNormals)[i]  = pFNormals[i];
  }

  ::CoTaskMemFree(pFVertices);
  ::CoTaskMemFree(pFNormals);

  return S_OK;
}


HRESULT GetStrokes (IRxStrokes *pStrokes, 
                    ULONG* pNumVertices, double** ppVertices,
                    ULONG* pNumPolylines, ULONG** ppPolylineLengths,
                    double AltChordTol)
{
  HRESULT hr=NOERROR;

  // First, try to obtain strokes from the set of pre-existing ones already
  // present inside the Inventor Part file

  ULONG nTolerances = 0;
  double* pTols{ nullptr };
  hr = pStrokes->GetExistingTolerances(&nTolerances, &pTols);
  OnErrorReturn(FAILED(hr), hr);

  // This means that we have sets of strokes, pre-existing within the file; one 
  // set of strokes per each individual tolerance. Obtain the strokes for an arbitrarily
  // selected tolerance (you can be more sophisticated and pick one that more closes matches the
  // current zoom factor and the viewing extents). The input tolerance is largely 
  // ignored in favor of one that has been found with associated strokes.

  double Tol = pTols[0];
  ::CoTaskMemFree (pTols);

  float *pFVertices = NULL;
  hr = pStrokes->GetExistingStrokes (Tol, pNumVertices, &pFVertices, pNumPolylines, ppPolylineLengths);
  OnErrorReturn (FAILED(hr), hr);

  // Convert the float points into doubles, since that is the currency in which OpenGL
  // and the rest of the code deals.

  *ppVertices = (double *) ::CoTaskMemAlloc (sizeof(double) * (*pNumVertices * 3));
  for (UINT i = 0; i < *pNumVertices * 3; i++)
    (*ppVertices)[i] = pFVertices[i];

  ::CoTaskMemFree(pFVertices);

  return S_OK;
}

HRESULT GetDocColor (IRxComponentDocument *pDoc, 
                     unsigned char *pucRed, unsigned char *pucGreen, unsigned char *pucBlue)
{
	HRESULT hr=NOERROR;
	OnErrorReturn (!pucRed || !pucGreen || !pucBlue, E_INVALIDARG);

	// Set a reddish color as the default

	*pucRed = 225;
	*pucGreen = 100;
	*pucBlue = 80;

	CComPtr<RenderStyle> pRenderStyle;
	CComQIPtr<Document> pInvDoc = pDoc;

	if (pInvDoc)
	{
		DocumentTypeEnum DocType;
		hr = pInvDoc->get_DocumentType(&DocType);
		OnErrorReturn (FAILED (hr), hr);

		if (kPartDocumentObject == DocType)
		{
			CComQIPtr<PartDocument> pPartDoc = pInvDoc;
			hr = pPartDoc->get_ActiveRenderStyle(&pRenderStyle);
			OnErrorReturn (FAILED (hr), hr);
		}
	}
	else
	{
		CComQIPtr<ApprenticeServerDocument> pApprDoc = pDoc;

		if (pApprDoc)
		{
			DocumentTypeEnum DocType;
			hr = pApprDoc->get_DocumentType (&DocType);
			OnErrorReturn (FAILED (hr), hr);

			if (kPartDocumentObject == DocType)
			{
				// This is an Apprentice Server document for a Part.

				hr = pApprDoc->get_ActiveRenderStyle (&pRenderStyle);
				OnErrorReturn (FAILED (hr), hr);
			}
		}
	}

	if(pRenderStyle)
		return pRenderStyle->GetDiffuseColor (pucRed, pucGreen, pucBlue);

	return S_OK;
}

HRESULT GetDocUnits (IRxComponentDocument *pDoc, 
                     UnitsTypeEnum *pLengthUnits)
{
	HRESULT hr=NOERROR;
	OnErrorReturn (!pLengthUnits, E_INVALIDARG);

	// Set a reddish color as the default

	*pLengthUnits = kCentimeterLengthUnits;

	CComPtr<UnitsOfMeasure> pUnitsOfMeasure;
	CComQIPtr<Document> pInvDoc = pDoc;

	if (pInvDoc)
	{
		hr = pInvDoc->get_UnitsOfMeasure(&pUnitsOfMeasure);
		OnErrorReturn (FAILED (hr), hr);
	}
	else
	{
		CComQIPtr<ApprenticeServerDocument> pApprDoc = pDoc;

		if (pApprDoc)
		{
			// This is an Apprentice Server document.

			hr = pApprDoc->get_UnitsOfMeasure (&pUnitsOfMeasure);
			OnErrorReturn (FAILED (hr), hr);
		}
	}

	return pUnitsOfMeasure->get_LengthUnits (pLengthUnits);
}
