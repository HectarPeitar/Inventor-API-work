/*
  DESCRIPTION

  Implementation of the management methods of the CCurvatureEngine class. 


  HISTORY

  AA  :  10/15/99  :  Creation
*/

#include <stdafx.h>
#include "referencekeyengine.h"
#include "curvatureengine.h"

#include <vector>
#include <math.h>


/*--------------- Constructor(s), destructor and initializers ----------------------*/

CCurvatureEngine::CCurvatureEngine()
: m_numCurvaturePoints(0), m_pCurvaturePoints(NULL), m_pCurvatureNormals(NULL),
  m_pCurvatureGradientPoints(NULL), m_pCurvatureGradientNormals(NULL),
  m_numCurvatureGradientFacets(0), m_pCurvatureGradientIndices(NULL)
{
}

CCurvatureEngine::~CCurvatureEngine()
{
  Clean();
}

void CCurvatureEngine::Clean()
{
  m_numCurvaturePoints = 0;

  if (m_pCurvaturePoints)
    delete [] m_pCurvaturePoints; 
  m_pCurvaturePoints = NULL;

  if (m_pCurvatureNormals)
    delete [] m_pCurvatureNormals;
  m_pCurvatureNormals = NULL;

  m_numCurvatureGradientFacets = 0;
  if(m_pCurvatureGradientPoints)
    ::CoTaskMemFree(m_pCurvatureGradientPoints);
  m_pCurvatureGradientPoints = NULL;
  if(m_pCurvatureGradientNormals)
    ::CoTaskMemFree(m_pCurvatureGradientNormals);
  m_pCurvatureGradientNormals = NULL;
  if(m_pCurvatureGradientIndices)
    ::CoTaskMemFree(m_pCurvatureGradientIndices);
  m_pCurvatureGradientIndices = NULL;
}

/*------------------- Management functions ---------------------------------*/

HRESULT CCurvatureEngine::_CalculateCurvatureGradient(CReferenceKey& refKeyFace, double chordTol, double cutOff,
                            ULONG* pNumVertices, double** ppVertices, double** ppNormals, ULONG* pNumFacets, ULONG** ppVertexIndices)
{
  IRxReferenceKey *pFaceRefKey = refKeyFace.get_Object();
  if(!pFaceRefKey)
    return S_OK;
  else 
    return CalculateCurvatureGradient(pFaceRefKey, chordTol, cutOff,
            pNumVertices, ppVertices, ppNormals, pNumFacets, ppVertexIndices);
}

HRESULT CCurvatureEngine::_CalculatePinCushion (CReferenceKey& refKeyFace, int UDensity, int VDensity, double CutOff,
                            ULONG* pNumPoints, double** ppPoints, double** ppNormals)
{
  IRxReferenceKey *pFaceRefKey = refKeyFace.get_Object();
  if(!pFaceRefKey)
    return S_OK;
  else 
    return CalculatePinCushion (pFaceRefKey, UDensity, VDensity, CutOff,
            pNumPoints, ppPoints, ppNormals);
}

