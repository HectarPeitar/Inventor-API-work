/*
  DESCRIPTION

  Implementation of the API-related methods of the CReferenceFile class. 


  HISTORY

  AA, AM  :  10/15/99  :  Creation
*/

#include "stdafx.h"
#include <afxpriv.h>
#include <math.h>
#include <vector>
#include <algorithm>

#include <initguid.h>
//#include <docclsids.h>

#include "referencefile.h"
#include "facets.h"

//const CLSID CLSID_InventorAssemblyDocument;
//const CLSID CLSID_InventorPartDocument;

/*------------------------ API-related functions -----------------------------*/

// This function obtains Apprentice through a CoCreate call.
// No file is read; only the Server is made available for use.

HRESULT CReferenceFile::ConnectToServer(/* [out] */ IRxApprenticeServer **ppServer)
{
  // CLSID_ApprenticeServerComponent
  //
  CLSID AppClsId;
  HRESULT hr = ::CLSIDFromProgID (L"Inventor.ApprenticeServer", &AppClsId);
  if(FAILED(hr))
  {
    printf ("*** Failed to obtain CLSID. Check registration ***\n");
    ASSERT(0);
    return hr;
  }

  // Create an instance of the server and declare that we would like to tune its
	// behavior for a display-oriented application.
  //
  hr = ::CoCreateInstance(AppClsId, NULL, CLSCTX_INPROC_SERVER,
  IID_IRxApprenticeServer, (void**) ppServer);
  if (FAILED (hr)) 
  {
    printf ("*** Failed to create Apprentice Server component ***\n");
    ASSERT(0);
    return hr;
  }

	CComQIPtr<ApprenticeServer> pdispServer (*ppServer);
	hr = (pdispServer)->put_DisplayAffinity (VARIANT_TRUE);
  if (FAILED (hr)) 
  {
    printf ("*** Failed to set DisplayAffinity ***\n");
    ASSERT(0);
    return hr;
  }

  return hr;
}

HRESULT CReferenceFile::ConnectToInventor(Application * * ppApp)
{
  CLSID AppClsId;
  HRESULT hr = ::CLSIDFromProgID (L"Inventor.Application", &AppClsId);
  if(FAILED(hr))
  {
    printf ("*** Failed to obtain CLSID. Check registration ***\n");
    ASSERT(0);
    return hr;
  }

  // Connect to Inventor
  //
  IUnknown *pAppUnk=NULL;
    hr = ::GetActiveObject (AppClsId, NULL, &pAppUnk);
  if (FAILED (hr)) 
  {
    printf ("*** Failed to create Apprentice Server component ***\n");
    ASSERT(0);
    return hr;
  }

  hr = pAppUnk->QueryInterface (__uuidof(Application), (void **) ppApp);

  return hr;
}


// Wrappers that use Apprentice or Inventor, depending on the connection
bool CReferenceFile::IsConnected()
{
  if(m_bUseLiveConnection)
    return (m_spInventorApplication != NULL);
  else
    return (m_pApprenticeServer != NULL);
}


IUnknown * CReferenceFile::GetServer()
{
  IUnknown * pUnk = NULL;
  HRESULT hr = NOERROR;
  if(m_bUseLiveConnection)
    hr = m_spInventorApplication->QueryInterface(IID_IUnknown, (void **) &pUnk);
  else
    hr = m_pApprenticeServer->QueryInterface(IID_IUnknown, (void **) &pUnk);
  ASSERT(SUCCEEDED(hr));
  return pUnk;
}

IRxComponentDocument * CReferenceFile::GetDocument()
{
  IRxComponentDocument * pDoc= NULL;
  HRESULT hr = GetDocument(&pDoc);
  return pDoc;	
}

HRESULT CReferenceFile::GetDocument(IRxComponentDocument **  ppDoc)
{
  HRESULT hr = NOERROR;
  if(m_bUseLiveConnection)
    hr = m_spDocument->QueryInterface(IID_IRxComponentDocument, (void **) ppDoc);
  else
    hr = m_pApprenticeServer->get_Document(ppDoc);
  ASSERT(SUCCEEDED(hr));
  return hr;
}

HRESULT CReferenceFile::OpenDocument(BSTR bstrFileName, IRxComponentDocument **  ppDoc)
{
  HRESULT hr = NOERROR;

  if(m_bUseLiveConnection)
  {
    _variant_t vtShow(VARIANT_TRUE);
    hr = m_spInventorApplication->Documents->Open(bstrFileName,vtShow,&m_spDocument);
    if(SUCCEEDED(hr))
      return GetDocument(ppDoc);
  }
  else
  {
    hr = m_pApprenticeServer->Close();
    if (SUCCEEDED(hr))
      hr = m_pApprenticeServer->Open(bstrFileName,ppDoc);
  }
  return hr;
}



// This function loads up the Inventor Part file into the Server. After this call,
// the Server can now be viewed as synonymous with the file.

HRESULT CReferenceFile::ReferenceFile(/* [in]  */ IUnknown *pServer,
                                      /* [in]  */ LPCOLESTR lpFileName)
{
  // Check if this is a valid Inventor file. If it isn't we must return an error
  // indicating invalid argument.
  //
  CLSID FileClsId;
  HRESULT hr = GetClassFile (lpFileName, &FileClsId);
  if(FAILED(hr)) 
  {
    ASSERT(false);
    return E_INVALIDARG;
  }

  if (!IsEqualCLSID (FileClsId, CLSID_InventorPartDocument) &&
        !IsEqualCLSID (FileClsId, CLSID_InventorAssemblyDocument)) 
  {
    ASSERT(false);
    return E_INVALIDARG;
  }

  // Load the inventor file (with read-only access) given the file name
  //
  _bstr_t bstrFileName(lpFileName);
  CComPtr<IRxComponentDocument> spCompDoc;
  hr = OpenDocument(bstrFileName, &spCompDoc);
  OnErrorReturn(FAILED(hr), hr);

  return hr;
}

// This function gets the facet information from a component occurrence.
// In the case of an assembly file, facet information can be built up over
// several occurrences so the input/output arrays are appended to.

HRESULT CReferenceFile::FacetsFromOccurrence(/* [in]   */ IRxComponentOccurrence* pOccurrence,
                                             /* [in]   */ double chordTol,
                                             /* [out]  */ ULONG* pNumVertices,
                                             /* [out]  */ double** ppVertices,
                                             /* [out]  */ double** ppNormals,
                                             /* [out]  */ ULONG* pNumFacets,
                                             /* [out]  */ ULONG** ppVertexIndices)
{
  // Make sure input is correct
  //
  OnErrorReturn(!pOccurrence, E_INVALIDARG);
  OnErrorReturn(chordTol <= 0.0, E_INVALIDARG);
  OnErrorReturn(!pNumVertices, E_INVALIDARG);
  OnErrorReturn(!ppVertices, E_INVALIDARG);
  OnErrorReturn(!ppNormals, E_INVALIDARG);
  OnErrorReturn(!pNumFacets, E_INVALIDARG);
  OnErrorReturn(!ppVertexIndices, E_INVALIDARG);

  HRESULT hr;

  // Get the component occurrence dispinterface.
  //
  CComQIPtr<ComponentOccurrence> pDIOccur(pOccurrence);
  OnErrorReturn(!pDIOccur, E_FAIL);

  // Get the collection of surface bodies from the occurrence.
  //
  CComPtr<SurfaceBodies> pSurfBodies;
  hr = pDIOccur->get_SurfaceBodies(&pSurfBodies);
  OnErrorReturn(FAILED(hr), hr);

  // Get the surface body enumerator from the collection.
  //
  CComQIPtr<IRxEnumSurfaceBodies> pEnumSurfBodies(pSurfBodies);
  OnErrorReturn(!pEnumSurfBodies, E_FAIL);

  // Get the facets from the surface bodies.
  //
  hr = FacetsFromSurfBodies(pEnumSurfBodies, chordTol, pNumVertices, ppVertices,
                            ppNormals, pNumFacets, ppVertexIndices);
  OnErrorReturn(FAILED(hr), hr);

  // Get the collection of sub-occurrences for this occurrence.
  //
  CComPtr<IRxEnumComponentOccurrences> pEnumOccurrences;
  hr = pOccurrence->get_SubOccurrences(&pEnumOccurrences);

  // Get the occurrences enumerator interface.
  //
  if (SUCCEEDED(hr))
  {
    // Get the facets from the sub-occurrences.
    //
    CComPtr<IRxComponentOccurrence> pSubOccur;
    for ( ; pEnumOccurrences->Next(1, &pSubOccur, NULL) == S_OK ; pSubOccur.Release())
    {
      hr = FacetsFromOccurrence(pSubOccur, chordTol, pNumVertices, ppVertices,
                                ppNormals, pNumFacets, ppVertexIndices);
      OnErrorReturn(FAILED(hr), hr);
    }
  }

  return S_OK;
}

// This function gets the facet information from each and every surface
// body referred to by the input surface body enumerator. In the case of
// an assembly file, facet information can be built up over several
// occurrences each possibly containing several surface bodies so the
// input/output arrays are appended to.

HRESULT CReferenceFile::FacetsFromSurfBodies(/* [in]  */ IRxEnumSurfaceBodies* pEnumSurfBodies,
                                             /* [in]  */ double chordTol,
                                             /* [out] */ ULONG* pNumVertices,
                                             /* [out] */ double** ppVertices,
                                             /* [out] */ double** ppNormals,
                                             /* [out] */ ULONG* pNumFacets,
                                             /* [out] */ ULONG** ppVertexIndices)
{
  HRESULT hr=NOERROR;

  // Make sure input is correct
  //
  OnErrorReturn(!pEnumSurfBodies, E_INVALIDARG);
  OnErrorReturn(chordTol <= 0.0, E_INVALIDARG);
  OnErrorReturn(!pNumVertices, E_INVALIDARG);
  OnErrorReturn(!ppVertices, E_INVALIDARG);
  OnErrorReturn(!ppNormals, E_INVALIDARG);
  OnErrorReturn(!pNumFacets, E_INVALIDARG);
  OnErrorReturn(!ppVertexIndices, E_INVALIDARG);

  // For each surface body ...
  //

  CComPtr<IRxSurfaceBody> pSurfBody;
  for ( ; pEnumSurfBodies->Next(1, &pSurfBody, NULL) == S_OK ; pSurfBody.Release())
  {
    // Get the facets from the surface body.

    CComQIPtr<IRxFacets> pFacets(pSurfBody);
    OnErrorReturn(!pFacets, E_FAIL);

    ULONG   numVertices;
    double* pVertices{ nullptr };
    double* pNormals{ nullptr };
    ULONG   numFacets;
    ULONG*  pVertexIndices{ nullptr };

    hr = GetFacets (pFacets, &numVertices, &pVertices, &pNormals, &numFacets, &pVertexIndices, chordTol);
    OnErrorReturn (FAILED(hr), hr);

    // Now append the information of this body into the facet-information obtained so far
    // from the other bodies.

    int ni = numFacets * 3;
    for (int i = 0; i < ni; i++)
			pVertexIndices[i] += *pNumVertices;

    ULONG cb = ((*pNumVertices + numVertices) * 3) * sizeof(double);
    *ppVertices = (double*) ::CoTaskMemRealloc(*ppVertices, cb);
    *ppNormals  = (double*) ::CoTaskMemRealloc(*ppNormals, cb);

    cb = (numVertices * 3) * sizeof(double);
    memcpy((*ppVertices) + (*pNumVertices * 3), pVertices, cb);
    memcpy((*ppNormals)  + (*pNumVertices * 3), pNormals,  cb);

    cb = ((*pNumFacets + numFacets) * 3) * sizeof(ULONG);
    *ppVertexIndices = (ULONG*) ::CoTaskMemRealloc(*ppVertexIndices, cb);

    cb = (numFacets * 3) * sizeof(ULONG);
    memcpy((*ppVertexIndices) + (*pNumFacets * 3), pVertexIndices, cb);

    *pNumVertices = *pNumVertices + numVertices;
    *pNumFacets   = *pNumFacets   + numFacets;

    ::CoTaskMemFree(pVertices);
    ::CoTaskMemFree(pNormals);
    ::CoTaskMemFree(pVertexIndices);
  }

  return NOERROR;
}

// This function gets the stroke information from a component occurrence.
// In the case of an assembly file, stroke information can be built up over
// several occurrences so the input/output arrays are appended to.

HRESULT CReferenceFile::StrokesFromOccurrence(/* [in]  */ IRxComponentOccurrence* pOccurrence,
                                              /* [in]  */ double chordTol,
                                              /* [out] */ ULONG* pNumWFVertices,
                                              /* [out] */ double** ppWFVertices,
                                              /* [out] */ ULONG* pNumWFPolylines,
                                              /* [out] */ ULONG** ppWFPolylineLengths)
{
  HRESULT hr=NOERROR;

  // Make sure input is correct

  OnErrorReturn(!pOccurrence, E_INVALIDARG);
  OnErrorReturn(chordTol <= 0.0, E_INVALIDARG);
  OnErrorReturn(!pNumWFVertices, E_INVALIDARG);
  OnErrorReturn(!ppWFVertices, E_INVALIDARG);
  OnErrorReturn(!pNumWFPolylines, E_INVALIDARG);
  OnErrorReturn(!ppWFPolylineLengths, E_INVALIDARG);

  // Get the component occurrence dispinterface.

  CComQIPtr<ComponentOccurrence> pDIOccur(pOccurrence);
  OnErrorReturn(!pDIOccur, E_FAIL);

  // Get the collection of surface bodies from the occurrence.

  CComPtr<SurfaceBodies> pSurfBodies;
  hr = pDIOccur->get_SurfaceBodies(&pSurfBodies);
  OnErrorReturn(FAILED(hr), hr);

  // Get the surface body enumerator from the collection.

  CComQIPtr<IRxEnumSurfaceBodies> pEnumSurfBodies(pSurfBodies);
  OnErrorReturn(!pSurfBodies, E_FAIL);

  // Get the strokes from the surface bodies.

  hr = StrokesFromSurfBodies(pEnumSurfBodies, chordTol, pNumWFVertices, ppWFVertices,
                             pNumWFPolylines, ppWFPolylineLengths);
  OnErrorReturn(FAILED(hr), hr);

  // Get the collection of sub-occurrences for this occurrence.

  CComPtr<IRxEnumComponentOccurrences> pEnumOccurrences;
  hr = pOccurrence->get_SubOccurrences(&pEnumOccurrences);

  // Get the occurrences enumerator interface.

  if (SUCCEEDED(hr))
  {
    // Get the strokes from the sub-occurrences.

    CComPtr<IRxComponentOccurrence> pSubOccur;
    for ( ; pEnumOccurrences->Next(1, &pSubOccur, NULL) == S_OK ; pSubOccur.Release())
    {
      hr = StrokesFromOccurrence(pSubOccur, chordTol, pNumWFVertices, ppWFVertices,
                                 pNumWFPolylines, ppWFPolylineLengths);
      OnErrorReturn(FAILED(hr), hr);
    }
  }

    return S_OK;
}

// This function gets the stroke information from each and every surface
// body referred to by the input surface body enumerator. In the case of
// an assembly file, stroke information can be built up over several
// occurrences each possibly containing several surface bodies so the
// input/output arrays are appended to.

HRESULT CReferenceFile::StrokesFromSurfBodies(/* [in]  */ IRxEnumSurfaceBodies* pEnumSurfBodies,
                                              /* [in]  */ double chordTol,
                                              /* [out] */ ULONG* pNumWFVertices,
                                              /* [out] */ double** ppWFVertices,
                                              /* [out] */ ULONG* pNumWFPolylines,
                                              /* [out] */ ULONG** ppWFPolylineLengths)
{
  HRESULT hr = NOERROR;

  // Make sure the input is correct

  OnErrorReturn(!pEnumSurfBodies, E_INVALIDARG);
  OnErrorReturn(chordTol <= 0.0, E_INVALIDARG);
  OnErrorReturn(!pNumWFVertices, E_INVALIDARG);
  OnErrorReturn(!ppWFVertices, E_INVALIDARG);
  OnErrorReturn(!pNumWFPolylines, E_INVALIDARG);
  OnErrorReturn(!ppWFPolylineLengths, E_INVALIDARG);

  // For each surface body ...

  CComPtr<IRxSurfaceBody> pSurfBody;
  for (;pEnumSurfBodies->Next(1, &pSurfBody, NULL) == S_OK; pSurfBody.Release())
  {
    // Get the strokes from the surface body.

    CComQIPtr<IRxStrokes> pStrokes(pSurfBody);
    OnErrorReturn(!pStrokes, E_FAIL);

    ULONG   numWFVertices;
    double* pWFVertices{ nullptr };
    ULONG   numWFPolylines;
    ULONG*  pWFPolylineLengths{ nullptr };

    hr = GetStrokes (pStrokes, &numWFVertices, &pWFVertices, &numWFPolylines, &pWFPolylineLengths, chordTol);
    OnErrorReturn (FAILED (hr), hr);

    // The vertex index information needs to modified if and when we append to
    // an already existing list of vertices.
      
    ULONG cb;

    cb = ((*pNumWFVertices + numWFVertices) * 3) * sizeof(double);
    *ppWFVertices = (double*) ::CoTaskMemRealloc(*ppWFVertices, cb);
    cb = (numWFVertices * 3) * sizeof(double);
    memcpy((*ppWFVertices) + (*pNumWFVertices * 3), pWFVertices, cb);

    cb = (*pNumWFPolylines + numWFPolylines) * sizeof(ULONG);
    *ppWFPolylineLengths = (ULONG*) ::CoTaskMemRealloc(*ppWFPolylineLengths, cb);
    cb = numWFPolylines * sizeof(ULONG);
    memcpy((*ppWFPolylineLengths) + (*pNumWFPolylines), pWFPolylineLengths, cb);

    *pNumWFVertices  += numWFVertices;
    *pNumWFPolylines += numWFPolylines;

    ::CoTaskMemFree(pWFVertices);
    ::CoTaskMemFree(pWFPolylineLengths);
  }

  return NOERROR;
}

// This function computes the facets or the triangle-mesh representation of the entire
// Surface Body in the file represented by the input Server. The chordal-height tolerance
// within which to compute it is passed in. The output consists of an array of triangle
// vertex points and their corresponding normals. An array of vertex indices then describes
// each triangle or facet -- with 3 indices per facet.

HRESULT CReferenceFile::CalculateFacets(/* [in]  */ IUnknown *pServer,
                                        /* [in]  */ double chordTol,
                                        /* [out] */ ULONG* pNumVertices,
                                        /* [out] */ double** ppVertices,
                                        /* [out] */ double** ppNormals,
                                        /* [out] */ ULONG* pNumFacets,
                                        /* [out] */ ULONG** ppVertexIndices)
{
  // Make sure input is correct
  //
  OnErrorReturn(chordTol <= 0.0, E_INVALIDARG);
  OnErrorReturn(!pNumVertices, E_INVALIDARG);
  OnErrorReturn(!ppVertices, E_INVALIDARG);
  OnErrorReturn(!ppNormals, E_INVALIDARG);
  OnErrorReturn(!pNumFacets, E_INVALIDARG);
  OnErrorReturn(!ppVertexIndices, E_INVALIDARG);

  // Initialize input variables
  //
  *pNumVertices = 0;
  *ppVertices = 0;
  *ppNormals = 0;
  *pNumFacets = 0;
  *ppVertexIndices = 0;

  // Get the Apprentice Document
  //
  CComPtr<IRxComponentDocument> pDoc;
  HRESULT hr = GetDocument(&pDoc);
  OnErrorReturn(FAILED(hr), hr);

  // Get the component definition enumerator for this document
  //
  CComPtr<IRxEnumComponentDefinitions> pEnumCompDefs;
  hr = pDoc->get_Definitions(&pEnumCompDefs);
  OnErrorReturn(FAILED(hr), hr);

  // Get the one component from this document.

  CComPtr<IRxComponentDefinition> pCompDef;
  if((hr = pEnumCompDefs->Next(1, &pCompDef, NULL)) != S_OK)
  OnErrorReturn(FAILED(hr), hr);

  // Get the surface body enumerator from the component definition.

  CComPtr<IRxEnumSurfaceBodies> pEnumSurfBodies;
  hr = pCompDef->get_SurfaceBodies(&pEnumSurfBodies);
  OnErrorReturn(FAILED(hr), hr);

  // Get the facet information from the surface bodies.
  //
  hr = FacetsFromSurfBodies(pEnumSurfBodies, chordTol, pNumVertices, ppVertices,
                            ppNormals, pNumFacets, ppVertexIndices);
  OnErrorReturn(FAILED(hr), hr);

  // Get the occurrences enumerator in case this is an assembly.

  CComPtr<IRxEnumComponentOccurrences> pEnumOccurrences;
  hr = pCompDef->get_Occurrences(&pEnumOccurrences);

  // Loop through the occurrences getting the facet information off
  // each one.

  if (SUCCEEDED(hr))
  {
    CComPtr<IRxComponentOccurrence> pOccurrence;
    for ( ; pEnumOccurrences->Next(1, &pOccurrence, NULL) == S_OK ; pOccurrence.Release())
    {
      hr = FacetsFromOccurrence(pOccurrence, chordTol, pNumVertices, ppVertices,
                                ppNormals, pNumFacets, ppVertexIndices);
      OnErrorReturn(FAILED(hr), hr);
    }
  }

  return S_OK;
}


// This function computes the strokes or line segments which together make up the
// wire-frame display of the entire Surface Body in the file represented by the input Server. 
// The chordal-height tolerance within which to compute it is passed in. The output 
// consists of an array of vertex points. An array of vertex indices then describes
// each stroke or line segment -- with 2 indices per line segment.

HRESULT CReferenceFile::CalculateStrokes(/* [in] */ IUnknown *pServer,
                                         /* [in] */ double chordTol,
                                         /* [out] */ ULONG* pNumWFVertices,
                                         /* [out] */ double** ppWFVertices,
                                         /* [out] */ ULONG* pNumWFPolylines,
                                         /* [out] */ ULONG** ppWFPolylineLengths)
{
  // Make sure the input is correct
  //
  OnErrorReturn(chordTol <= 0.0, E_INVALIDARG);
  OnErrorReturn(!pNumWFVertices, E_INVALIDARG);
  OnErrorReturn(!ppWFVertices, E_INVALIDARG);
  OnErrorReturn(!pNumWFPolylines, E_INVALIDARG);
  OnErrorReturn(!ppWFPolylineLengths, E_INVALIDARG);

  // Initialize the input variables
  //
  *pNumWFVertices = 0;
  *ppWFVertices = 0;
  *pNumWFPolylines = 0;
  *ppWFPolylineLengths = 0;

  // Get the Apprentice Document
  //
  CComPtr<IRxComponentDocument> pDoc;
  HRESULT hr = GetDocument(&pDoc);
  OnErrorReturn(FAILED(hr), hr);

  // Get the component definition enumerator for this document
  //
  CComPtr<IRxEnumComponentDefinitions> pEnumCompDefs;
  hr = pDoc->get_Definitions(&pEnumCompDefs);
  OnErrorReturn(FAILED(hr), hr);

  // Get the one component from this document.
  //
  CComPtr<IRxComponentDefinition> pCompDef;
  if((hr = pEnumCompDefs->Next(1, &pCompDef, NULL)) != S_OK)
  OnErrorReturn(FAILED(hr), hr);

  // Get the surface body enumerator from the component definition.
  //
  CComPtr<IRxEnumSurfaceBodies> pEnumSurfBodies;
  hr = pCompDef->get_SurfaceBodies(&pEnumSurfBodies);
  OnErrorReturn(FAILED(hr), hr);

  // Get the stroke information from the surface bodies.
  //
  hr = StrokesFromSurfBodies(pEnumSurfBodies, chordTol, pNumWFVertices, ppWFVertices,
                             pNumWFPolylines, ppWFPolylineLengths);
  OnErrorReturn(FAILED(hr), hr);

  // Get the occurrences enumerator in case this is an assembly.
  //
  CComPtr<IRxEnumComponentOccurrences> pEnumOccurrences;
  hr = pCompDef->get_Occurrences(&pEnumOccurrences);

  // Loop through the occurrences getting the stroke information off
  // each one.
  //
  if (SUCCEEDED(hr))
  {
    CComPtr<IRxComponentOccurrence> pOccurrence;
    for ( ; pEnumOccurrences->Next(1, &pOccurrence, NULL) == S_OK ; pOccurrence.Release())
    {
      hr = StrokesFromOccurrence(pOccurrence, chordTol, pNumWFVertices, ppWFVertices,
                                 pNumWFPolylines, ppWFPolylineLengths);
      OnErrorReturn(FAILED(hr), hr);
    }
  }

  return S_OK;
}


// This method traverses down the Server through the BRep objects retrieving information
// such as the number of shells, faces, edges, vertices in the BRep. It also retrieves
// the volume of the BRep.

typedef std::vector<IRxVertexPtr> VerticesVector;

//Calculate Geometry Info
HRESULT CReferenceFile::CalculateBodyInfo(SurfaceBodies *pSurfBodies,
										  int& nFaceShellCount,
										  int& nFaceCount,
										  int& nEdgeCount,
										  int& nVertexCount,
										  double& fVolume)
{
	
	int nEdgeUseCount = 0;
	int nEdgeLoopCount = 0;
	
	// Get the Surface bodies interface
	//
	CComQIPtr<IRxEnumSurfaceBodies> spEnumSurfBodies = pSurfBodies;
	if (NULL == spEnumSurfBodies)
		OnErrorReturn(FAILED(E_FAIL), E_FAIL);

	ULONG nBodiesFetched = 0;
	IRxSurfaceBodyPtr spSurfBody;
	VerticesVector aVector;

	HRESULT hr;

	while((hr = spEnumSurfBodies->Next(1, &spSurfBody, &nBodiesFetched)) == S_OK) 
	{
		OnErrorReturn(nBodiesFetched != 1, E_FAIL); 

		char bIsSolid;
		hr = spSurfBody->get_IsSolid(&bIsSolid);
		OnErrorReturn(FAILED(hr), hr);

		if(!bIsSolid)
			continue;  // continue to the next body

		// Compute the volume of the body and add to the volume. Use accuracy of 1%
		//
		double fBodyVolume =  0.0;
		hr = spSurfBody->get_Volume(0.01, &fBodyVolume);
		OnErrorReturn(FAILED(hr), hr);
		fVolume += fBodyVolume;

		// Compute the number of shells
		//
		IRxFaceShellPtr spFaceShell = NULL;
		IRxEnumFaceShellsPtr spEnumShells = NULL;
		ULONG nFaceShellsFetched = 0;

		hr = spSurfBody->get_FaceShells (&spEnumShells);
		OnErrorReturn(FAILED(hr), hr);
		while((hr = spEnumShells->Next(1, &spFaceShell, &nFaceShellsFetched)) == S_OK) 
		{
			nFaceShellCount++;
		}

		IRxEdgePtr spEdge = NULL;
		IRxEnumEdgesPtr spEnumEdges = NULL;
		ULONG nEdgesFetched = 0;

		hr = spSurfBody->get_Edges(&spEnumEdges);
		OnErrorReturn(FAILED(hr), hr);
		while((hr = spEnumEdges->Next(1, &spEdge, &nEdgesFetched)) == S_OK) 
		{
			OnErrorReturn(nEdgesFetched != 1, E_FAIL); 
			IRxVertexPtr spVertex = NULL;
			hr = spEdge->get_StartVertex(&spVertex);
			OnErrorReturn(FAILED(hr), hr);

			hr = spEdge->get_StopVertex(&spVertex);
			OnErrorReturn(FAILED(hr), hr);

			IRxFacePtr spFace2 = NULL;
			IRxEnumFacesPtr spEnumFaces2 = NULL;
			ULONG nFacesFetched2 = 0;
			hr = spEdge->get_Faces(&spEnumFaces2);
			OnErrorReturn(FAILED(hr), hr);

			while((hr = spEnumFaces2->Next(1, &spFace2, &nFacesFetched2)) == S_OK) 
			{
				OnErrorReturn(nFacesFetched2 != 1, E_FAIL); 
			}

			nEdgeCount++;
		}

		IRxFacePtr spFace = NULL;
		IRxEnumFacesPtr spEnumFaces = NULL;
		ULONG nFacesFetched = 0;
		hr = spSurfBody->get_Faces(&spEnumFaces);
		OnErrorReturn(FAILED(hr), hr);

		while((hr = spEnumFaces->Next(1, &spFace, &nFacesFetched)) == S_OK) 
		{
			OnErrorReturn(nFacesFetched != 1, E_FAIL); 

			IRxEdgeLoopPtr spEdgeLoop = NULL;
			IRxEnumEdgeLoopsPtr spEnumEdgeLoops = NULL;
			ULONG nEdgeLoopsFetched = 0;

			hr = spFace->get_EdgeLoops(&spEnumEdgeLoops);
			OnErrorReturn(FAILED(hr), hr);
			while((hr = spEnumEdgeLoops->Next(1, &spEdgeLoop, &nEdgeLoopsFetched)) == S_OK) 
			{
				OnErrorReturn(nEdgeLoopsFetched != 1, E_FAIL); 

				IRxEdgeUsePtr spEdgeUse = NULL;
				IRxEnumEdgeUsesPtr spEnumEdgeUses = NULL;
				ULONG nEdgeUsesFetched = 0;

				hr = spEdgeLoop->get_EdgeUses(&spEnumEdgeUses);
				OnErrorReturn(FAILED(hr), hr);
				while((hr = spEnumEdgeUses->Next(1, &spEdgeUse, &nEdgeUsesFetched)) == S_OK)
				{
					OnErrorReturn(nEdgeUsesFetched != 1, E_FAIL); 

					IRxEdgePtr spMyEdge = NULL;
					hr = spEdgeUse->get_Edge(&spMyEdge);
					OnErrorReturn(FAILED(hr), hr);

					IRxEdgeUsePtr spPartnerEdgeUse = NULL;
					hr = spEdgeUse->get_Partner(&spPartnerEdgeUse);
					OnErrorReturn(FAILED(hr), hr);

					IRxEdgePtr spPartnersEdge = NULL;
					hr = spEdgeUse->get_Edge(&spPartnersEdge);
					OnErrorReturn(FAILED(hr), hr);

					// Check that they are indeed the same
					//
					IUnknownPtr spMyEdgeUnknown = spMyEdge;
					IUnknownPtr spPartnersEdgeUnknown = spPartnersEdge;

					// This shows that you can use the IUnknown as the identity of an object
					//
					if(spMyEdgeUnknown != spPartnersEdgeUnknown)
					{
						// Houston, we have a problem
						return E_FAIL;
					}

					nEdgeUseCount++;
				}

				nEdgeLoopCount++;
			}

			// Look for all the vertices with this face
			//
			IRxEnumVerticesPtr spEnumVertices = NULL;
			hr = spFace->get_Vertices(&spEnumVertices);

			OnErrorReturn(FAILED(hr), hr);

			ULONG nVerticesFetched = 0;
			IRxVertexPtr spVertex = NULL;
			while((hr = spEnumVertices->Next(1, &spVertex, &nVerticesFetched)) == S_OK) 
			{
				OnErrorReturn(nVerticesFetched != 1, E_FAIL); 

				// to obviously overcount vertices, we keep a track of which ones we have already counted
				//
				if(aVector.end() == std::find(aVector.begin(),aVector.end(),spVertex))
				{
					aVector.push_back(spVertex);
					nVertexCount++; 
				}
			}      
			nFaceCount++;
		}
	}

	return hr;
}

//Iterate all ComponentOccurrences of an assembly document to get the body info
HRESULT CReferenceFile::IterateOccurrence(ComponentOccurrence *pCompOcc,
										  int& nFaceShellCount,
										  int& nFaceCount,
										  int& nEdgeCount,
										  int& nVertexCount,
										  double& fVolume)
{
	DocumentTypeEnum eDocType;
	HRESULT hr = pCompOcc->get_DefinitionDocumentType(&eDocType);
	OnErrorReturn(FAILED(hr), hr);
	
	VARIANT_BOOL nSuppressed = VARIANT_FALSE;
	pCompOcc->get_Suppressed(&nSuppressed);

	if (VARIANT_FALSE != nSuppressed)
		return S_OK;

	if (kAssemblyDocumentObject == eDocType)
	{
		CComPtr<ComponentOccurrencesEnumerator> spSubOccsEnum = NULL;

		hr = pCompOcc->get_SubOccurrences(&spSubOccsEnum);
		OnErrorReturn(FAILED(hr), hr);
		
		long nSubOccesCount = 0;
		hr = spSubOccsEnum->get_Count(&nSubOccesCount);

		if (hr != S_OK)
			OnErrorReturn(FAILED(hr), hr);

		if (0 == nSubOccesCount)
			return S_OK;

		CComPtr<ComponentOccurrence> spSubOcc = NULL;
		for (long i = 1; i <= nSubOccesCount; i++)
		{
			spSubOcc = NULL;
			hr = spSubOccsEnum->get_Item(i, &spSubOcc);
			OnErrorReturn(FAILED(hr), hr);

			hr = IterateOccurrence(spSubOcc, nFaceShellCount, nFaceCount, nEdgeCount, nVertexCount, fVolume);
			OnErrorReturn(FAILED(hr), hr);
		}
	}
	else if (kPartDocumentObject == eDocType)
	{
		CComPtr<SurfaceBodies> spSurfBodies = NULL;
		hr = pCompOcc->get_SurfaceBodies(&spSurfBodies);
		OnErrorReturn(FAILED(hr), hr);

		/*CComPtr<SurfaceBody> spSurfBody = NULL;
		hr = spSurfBodies->get_Item(1, &spSurfBody);
		OnErrorReturn(FAILED(hr), hr);*/

		hr = CalculateBodyInfo(spSurfBodies, nFaceShellCount, nFaceCount, nEdgeCount, nVertexCount, fVolume);
		OnErrorReturn(FAILED(hr), hr);

		return S_OK;
	}

	return S_OK;
}


//Get the body info
HRESULT CReferenceFile::GetBodyInfo(IUnknown *pServer,
                                    int& nFaceShellCount,
                                    int& nFaceCount,
                                    int& nEdgeCount,
                                    int& nVertexCount,
                                    double& fVolume)
{
	fVolume = 0.0;
	nEdgeCount = 0;
	nVertexCount = 0;
	nFaceCount = 0;
	nFaceShellCount = 0;
	int nEdgeUseCount = 0;
	int nEdgeLoopCount = 0;

	// Get the Apprentice Document
	//
	IRxComponentDocumentPtr spDoc = NULL;
	HRESULT hr = GetDocument(&spDoc);
	OnErrorReturn(FAILED(hr), hr);
	
	//Get the PartDocument, AssemblyDocument or ApprenticeServerDocument
	//
	CComQIPtr<PartDocument> spPartDoc = spDoc;
	CComQIPtr<AssemblyDocument> spAssbyDoc = spDoc;
	CComQIPtr<ApprenticeServerDocument> pApprDoc = spDoc;

	if (NULL == spPartDoc && NULL == spAssbyDoc && NULL == pApprDoc)
		OnErrorReturn(FAILED(E_FAIL), E_FAIL);

	// Get the Component definition for this document
	//
	
	//PartDocument
	if (spPartDoc != NULL)
	{
		CComPtr<PartComponentDefinitions> spPartCompDefs = NULL;
		hr = spPartDoc->get_ComponentDefinitions(&spPartCompDefs);
		OnErrorReturn(FAILED(hr), hr);

		CComPtr<PartComponentDefinition> spPartCompDef = NULL;
		hr = spPartCompDefs->get_Item(1, &spPartCompDef);
		OnErrorReturn(FAILED(hr), hr);

		CComPtr<SurfaceBodies> spSurfBodies = NULL;
		hr = spPartCompDef->get_SurfaceBodies(&spSurfBodies);
		OnErrorReturn(FAILED(hr), hr);

		hr = CalculateBodyInfo(spSurfBodies, nFaceShellCount, nFaceCount, nEdgeCount, nVertexCount, fVolume);

		return hr;
	}
	else if (spAssbyDoc != NULL)
	{
		//Assembly Document
		CComPtr<AssemblyComponentDefinitions> spAssbyCompDefs = NULL;
		hr = spAssbyDoc->get_ComponentDefinitions(&spAssbyCompDefs);
		OnErrorReturn(FAILED(hr), hr);

		CComPtr<AssemblyComponentDefinition> spAssbyCompDef = NULL;
		hr = spAssbyCompDefs->get_Item(1, &spAssbyCompDef);
		OnErrorReturn(FAILED(hr), hr);
		
		CComPtr<ComponentOccurrences> spCompOccs = NULL;
		hr = spAssbyCompDef->get_Occurrences(&spCompOccs);
		OnErrorReturn(FAILED(hr), hr);
		
		long nCompOccsCount = 0;
		hr = spCompOccs->get_Count(&nCompOccsCount);

		if (hr != S_OK)
			OnErrorReturn(FAILED(hr), hr);

		if (0 == nCompOccsCount)
			return S_OK;
		
		CComPtr<ComponentOccurrence> spCompOcc = NULL;
		for (long i = 1; i <= nCompOccsCount; i++)
		{	
			spCompOcc = NULL;
			hr = spCompOccs->get_Item(i, &spCompOcc);
			OnErrorReturn(FAILED(hr), hr);

			hr = IterateOccurrence(spCompOcc, nFaceShellCount, nFaceCount, nEdgeCount, nVertexCount, fVolume);
			OnErrorReturn(FAILED(hr), hr);
		}

		return hr;
	}
	else
	{
		//ApprenticeServerDocument
		DocumentTypeEnum DocType;
		hr = pApprDoc->get_DocumentType (&DocType);
		OnErrorReturn (FAILED (hr), hr);

		CComPtr<ComponentDefinitions> spApprCompDefs = NULL;
		hr = pApprDoc->get_ComponentDefinitions(&spApprCompDefs);
		OnErrorReturn(FAILED(hr), hr);

		CComPtr<ComponentDefinition> spApprCompDef = NULL;
		hr = spApprCompDefs->get_Item(1, &spApprCompDef);
		OnErrorReturn(FAILED(hr), hr);

		if (kPartDocumentObject == DocType)
		{
			// This is an Apprentice Server document for a Part.
			CComPtr<SurfaceBodies> spApprSurfBodies = NULL;
			hr = spApprCompDef->get_SurfaceBodies(&spApprSurfBodies);
			OnErrorReturn(FAILED(hr), hr);

			hr = CalculateBodyInfo(spApprSurfBodies, nFaceShellCount, nFaceCount, nEdgeCount, nVertexCount, fVolume);

			return hr;
		}
		else if (kAssemblyDocumentObject == DocType)
		{
			CComPtr<ComponentOccurrences> spCompOccs = NULL;
			hr = spApprCompDef->get_Occurrences(&spCompOccs);
			OnErrorReturn(FAILED(hr), hr);
			
			long nCompOccsCount = 0;
			hr = spCompOccs->get_Count(&nCompOccsCount);

			if (hr != S_OK)
				OnErrorReturn(FAILED(hr), hr);

			if (0 == nCompOccsCount)
				return S_OK;
			
			CComPtr<ComponentOccurrence> spCompOcc = NULL;
			for (long i = 1; i <= nCompOccsCount; i++)
			{	
				spCompOcc = NULL;
				hr = spCompOccs->get_Item(i, &spCompOcc);
				OnErrorReturn(FAILED(hr), hr);

				hr = IterateOccurrence(spCompOcc, nFaceShellCount, nFaceCount, nEdgeCount, nVertexCount, fVolume);
				OnErrorReturn(FAILED(hr), hr);
			}

			return hr;
		}
	}

	return E_FAIL;
}