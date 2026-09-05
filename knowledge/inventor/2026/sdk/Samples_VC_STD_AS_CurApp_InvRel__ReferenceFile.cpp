/*
  DESCRIPTION

  Implementation of the management methods of the CReferenceFile class. 


  HISTORY

  AA  :  10/15/99  :  Creation
*/

#include "stdafx.h"
#include <afxpriv.h>
#include <math.h>
#include "vector"

#include "referencefile.h"

/*--------------- Constructor(s), destructor and initializers ----------------------*/

CReferenceFile::CReferenceFile(bool bUseLiveConnection)
: m_pApprenticeServer(0), m_dwNumVertices(0), m_vertices(0),
  m_normals(0), m_dwNumFacets(0), m_vertexIndices(0),
  m_dwNumWFVertices(0), m_WFVertices(0), m_dwNumWFPolylines(0), m_WFPolylineLengths(0),
  m_bUseLiveConnection(bUseLiveConnection), m_ucRed(0), m_ucBlue(0), m_ucGreen(0), m_LengthUnits(kCentimeterLengthUnits)

{

  HRESULT hr = NOERROR;
  if(bUseLiveConnection)
    ConnectToInventor(&m_spInventorApplication);
  else
    ConnectToServer (&m_pApprenticeServer);
}

CReferenceFile::~CReferenceFile()
{
  Clean();
  if(m_pApprenticeServer)
  {
	 m_pApprenticeServer->Close();
     m_pApprenticeServer->Release();
  }

  m_spInventorApplication = NULL;
}

void CReferenceFile::Clean()
{
  m_strFileName.Empty();

  m_spDocument = NULL;
  
  // facets for shaded image
  m_dwNumVertices = 0;
  m_dwNumFacets = 0;
  ::CoTaskMemFree(m_vertices); m_vertices = 0;
  ::CoTaskMemFree(m_normals); m_normals = 0;
  ::CoTaskMemFree(m_vertexIndices); m_vertexIndices = 0;

  // strokes for wframe image
  m_dwNumWFVertices = 0;
  ::CoTaskMemFree(m_WFVertices); m_WFVertices = 0;
  m_dwNumWFPolylines = 0;
  ::CoTaskMemFree(m_WFPolylineLengths); m_WFPolylineLengths = 0;

}

/*------------------- Management functions ---------------------------------*/

HRESULT CReferenceFile::_ReferenceFile(LPCOLESTR lpFileName)
{
  if(!IsConnected())
    return S_OK;
  else 
  {
    m_strFileName = lpFileName;
    return ReferenceFile(GetServer(), lpFileName);
  }
}

HRESULT CReferenceFile::_CalculateFacets(double chordTol, 
         ULONG* pNumVertices, double** ppVertices, double** ppNormals, ULONG* pNumFacets, ULONG** ppVertexIndices)
{
  if(!IsConnected())
    return S_OK;
  else 
    return CalculateFacets(GetServer(), chordTol, 
            pNumVertices, ppVertices, ppNormals, pNumFacets, ppVertexIndices);
}

HRESULT CReferenceFile::_CalculateStrokes(double chordTol,
         ULONG* pNumWFVertices, double** ppWFVertices, ULONG* pNumWFPolylines, ULONG** ppWFPolylineLengths)
{
  if(!IsConnected())
    return S_OK;
  else 
    return CalculateStrokes(GetServer(), chordTol,
            pNumWFVertices, ppWFVertices, pNumWFPolylines, ppWFPolylineLengths);
}

HRESULT CReferenceFile::_GetBodyInfo(int& nFaceShellCount, int& nFaceCount, int& nEdgeCount, int& nVertexCount, double& fVolume)
{
  if(!IsConnected())
    return S_OK;
  else 
    return GetBodyInfo(GetServer(), nFaceShellCount, nFaceCount, nEdgeCount, nVertexCount, fVolume);
}

