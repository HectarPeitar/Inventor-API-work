/*
  DESCRIPTION

  Implementation of the management methods of the CCurvatureEngine class. 


  HISTORY

  SAM  :  10/15/99  :  Creation
*/

#include <stdafx.h>
#include "selectionengine.h"
#include <math.h>

enum AppSelectMode
{ 
  eUnknownFilter = 0x0, 
  eFaceFilter = 0x01, 
  eEdgeFilter = 0x02, 
  eVertexFilter = 0x03
};

/*--------------- Constructor(s), destructor and initializers ----------------------*/

CSelectionEngine::CSelectionEngine()
                : m_pRefKey(NULL), m_pFirstVertex(NULL), m_dwNumWFSelVertices(0), m_WFSelVertices(NULL),
                  m_dwNumWFSelIndices(0), m_WFSelIndices(NULL)
{
}

CSelectionEngine::~CSelectionEngine()
{
  Clean();
}

void CSelectionEngine::Clean(bool bCleanForUpdate /* = false */)
{
  if(m_pRefKey && !bCleanForUpdate) {
    m_pRefKey->Release();
    m_pRefKey = NULL;
  }
  
  if(m_pFirstVertex && !bCleanForUpdate) {
	  m_pFirstVertex->Release();
	  m_pFirstVertex = NULL;
  }

  m_dwNumWFSelVertices = 0;
  ::CoTaskMemFree(m_WFSelVertices); m_WFSelVertices = NULL;
  m_dwNumWFSelIndices = 0;
  ::CoTaskMemFree(m_WFSelIndices); m_WFSelIndices = NULL;
}


/*------------------- Management functions ---------------------------------*/

IRxReferenceKey* CSelectionEngine::GetLastSelectedObject()
{
  return m_pRefKey;
}

IRxReferenceKey* CSelectionEngine::GetFirstVertex()
{
  return m_pFirstVertex;
}

HRESULT CSelectionEngine::SetLastSelectedObject(IRxReferenceKey *pRefKey)
{
	HRESULT hr = NOERROR;
	IRxVertex *pPoint = NULL;
	
	//If the last selected object is vertex, save this object.
	//Because the last vertex object maybe one of the two entities used at MeasureDistance.
	if (m_pRefKey)
	{
		hr = m_pRefKey->QueryInterface(IID_IRxVertex, (void**)&pPoint);

		if (SUCCEEDED(hr))
		{
			if (m_pFirstVertex)
				m_pFirstVertex->Release();

			m_pFirstVertex = m_pRefKey;
		}
		else
			m_pRefKey->Release();
	}

  m_pRefKey = pRefKey;

  if(m_pRefKey) 
    m_pRefKey->AddRef();

  return S_OK;
}

HRESULT CSelectionEngine::PerformSelection(IRxComponentDocument * pDoc,
                                           AppSelectMode eSelectMode,
                                           double dLocateRadius,
                                           double chordHeightTol,
                                           double *pBoreVecPt1,
                                           double *pBoreVecPt2)
{
  HRESULT hr = NOERROR;
  IRxReferenceKey *pRefKey=NULL;

  hr = GetSelection(pDoc, eSelectMode, dLocateRadius, pBoreVecPt1, pBoreVecPt2, &pRefKey);
  OnError(FAILED(hr), wrapup);

  hr = SetLastSelectedObject(pRefKey);
  OnError(FAILED(hr), wrapup);

  if(!pRefKey)
    return S_OK;

  hr = BuildSelectStrokes(chordHeightTol);
  OnError(FAILED(hr), wrapup);

wrapup:

  if(pRefKey)
    pRefKey->Release();

  return hr;
}

HRESULT CSelectionEngine::BuildSelectStrokes(double chordHeightTol)
{
  HRESULT hr = NOERROR;

  OnErrorReturn(!m_pRefKey, E_POINTER);

  m_dwNumWFSelVertices = 0;
  ::CoTaskMemFree(m_WFSelVertices); m_WFSelVertices = NULL;
  m_dwNumWFSelIndices = 0;
  ::CoTaskMemFree(m_WFSelIndices); m_WFSelIndices = NULL;

  hr = GetSelectStrokes(m_pRefKey, chordHeightTol, &m_dwNumWFSelVertices, &m_WFSelVertices, &m_dwNumWFSelIndices, &m_WFSelIndices);
  OnErrorReturn(FAILED(hr), hr);

  return S_OK;
}

