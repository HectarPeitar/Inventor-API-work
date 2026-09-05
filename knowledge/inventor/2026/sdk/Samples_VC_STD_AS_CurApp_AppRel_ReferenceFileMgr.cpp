#include <stdafx.h>

#include "referencefilemgr.h"
#include "../CurvatureAppDoc.h"
#include "curvatureappdb.h"

#include "../InventorRelated/ReferenceFile.h"
#include "../InventorRelated/SelectionEngine.h"
#include "../InventorRelated/CurvatureEngine.h"
#include "../InventorRelated/MeasureEngine.h"
#include "../InventorRelated/ReferenceKeyEngine.h"
#include "../InventorRelated/Facets.h"

#include "safearrayutil.h"

CReferenceFileMgr::CReferenceFileMgr()
: m_pReferenceFile(0),
  m_pPersistenceEngine(0),
  m_pDb(0),
  m_pMeasureEngine(0),
  m_pSelectionEngine(0),
  m_pCurvatureEngine(0),
  m_pReferenceKeyEngine(0)
{
  m_pDb = new CCurvatureAppDb();

  // Allocate and initialize the reference keys
  //
  int nEntries = sizeof (k_CmdTable) / sizeof (*k_CmdTable);

  m_RefKeys.reserve(nEntries);

  for (int i=0; i<nEntries; i++)
  {
    CReferenceKey refKey;
    refKey.put_CommandContext(k_CmdTable[i][0]);

    m_RefKeys.push_back(refKey);
  }
}

CReferenceFileMgr::~CReferenceFileMgr()
{
  m_RefKeys.clear();
  delete m_pPersistenceEngine;
  delete m_pDb;
  delete m_pMeasureEngine;
  delete m_pSelectionEngine;
  delete m_pCurvatureEngine;
  delete m_pReferenceKeyEngine;
  delete m_pReferenceFile; // This has to be killed last
}

void CReferenceFileMgr::Clean()
{
  if(!m_pReferenceFile)
    return;

  m_pReferenceFile->Clean();
  //m_pPersistenceEngine->Clean();
  m_pMeasureEngine->Clean();
  m_pCurvatureEngine->Clean();
  m_pSelectionEngine->Clean();
  CleanKeys();
}

void CReferenceFileMgr::CleanKeys()
{
  // Reset the reference keys
  //
  int nEntries = sizeof (k_CmdTable) / sizeof (*k_CmdTable);
  for (int ii = 0; ii < nEntries; ++ii)
  {
    m_RefKeys[ii].Clean();
  }
}

//////////////////////////////////////////////////////////////
// Methods for referencing an Inventor file
//////////////////////////////////////////////////////////////

HRESULT CReferenceFileMgr::ReferenceFile(LPCOLESTR lpFileName,
                                         double chordTol,bool bUseLiveConnection)
{
  ULONG numVertices;
  double* pVertices = 0;
  double* pNormals = 0;
  ULONG numFacets;
  ULONG* pVertexIndices = 0;
  ULONG numWFVertices;
  double* pWFVertices = 0;
  ULONG numWFPolylines;
  ULONG* pWFPolylineLengths = 0;
  IRxComponentDocument *pDoc = NULL;

  if(!m_pReferenceFile) {
    ASSERT(!m_pPersistenceEngine && !m_pMeasureEngine && !m_pSelectionEngine &&
            !m_pCurvatureEngine && !m_pReferenceKeyEngine);
    m_pReferenceFile = new CReferenceFile(bUseLiveConnection);
    m_pPersistenceEngine = new CPersistenceEngine();
    m_pMeasureEngine = new CMeasureEngine();
    m_pSelectionEngine = new CSelectionEngine();
    m_pCurvatureEngine = new CCurvatureEngine();
    m_pReferenceKeyEngine = new CReferenceKeyEngine();
  }
  else {
    m_pReferenceFile->Clean();
    //m_pPersistenceEngine->Clean();
    m_pMeasureEngine->Clean();
    m_pCurvatureEngine->Clean();
    m_pSelectionEngine->Clean();
    m_pReferenceKeyEngine->Clean();
  }

  HRESULT hr = m_pReferenceFile->_ReferenceFile(lpFileName);
  OnError(FAILED(hr), wrapup);

  hr = GetReferenceFile()->_CalculateFacets(chordTol, &numVertices, &pVertices,
                                            &pNormals, &numFacets, &pVertexIndices);
  OnError(FAILED(hr), wrapup);

  hr = GetReferenceFile()->_CalculateStrokes(chordTol, &numWFVertices, &pWFVertices,
                                            &numWFPolylines, &pWFPolylineLengths);
  OnError(FAILED(hr), wrapup);

  GetReferenceFile()->SetNumVertices(numVertices);
  GetReferenceFile()->SetVertices(pVertices);
  GetReferenceFile()->SetNormals(pNormals);
  GetReferenceFile()->SetNumFacets(numFacets);
  GetReferenceFile()->SetVertexIndices(pVertexIndices);

  GetReferenceFile()->SetNumWFVertices(numWFVertices);
  GetReferenceFile()->SetWFVertices(pWFVertices);
  GetReferenceFile()->SetNumWFPolylines(numWFPolylines);
  GetReferenceFile()->SetWFPolylineLengths(pWFPolylineLengths);

  unsigned char Red, Green, Blue;
  pDoc = GetReferenceFile()->GetDocument();
  GetDocColor (pDoc, &Red, &Green, &Blue);
  GetReferenceFile()->SetColor (Red, Green, Blue);

  UnitsTypeEnum LengthUnits;
  GetDocUnits (pDoc, &LengthUnits);
  GetMeasureEngine()->PutLengthUnits (LengthUnits);
  pDoc->Release();

wrapup:
  if(FAILED(hr)) {
    ::CoTaskMemFree(pVertices);
    ::CoTaskMemFree(pNormals);
    ::CoTaskMemFree(pVertexIndices);
    ::CoTaskMemFree(pWFVertices);
    ::CoTaskMemFree(pWFPolylineLengths);

    delete m_pReferenceFile; m_pReferenceFile = 0;
    delete m_pPersistenceEngine; m_pPersistenceEngine = 0;
    delete m_pMeasureEngine; m_pMeasureEngine = 0;
    delete m_pSelectionEngine; m_pSelectionEngine = 0;
    delete m_pCurvatureEngine; m_pCurvatureEngine = 0;
    delete m_pReferenceKeyEngine; m_pReferenceKeyEngine = 0;
  }

  return hr;
}

//////////////////////////////////////////////////////////////
// Methods for updating an Inventor Part from disk
//////////////////////////////////////////////////////////////

HRESULT CReferenceFileMgr::Update(LPCOLESTR lpFileName, double dChordHtTol,bool bUseLiveConnection)
{
  // Prepare the db engine for Update
  m_pDb->PreUpdate(this);

  // Clean the engines (close down Apprentice, etc...)
  m_pReferenceFile->Clean();
  m_pMeasureEngine->Clean();
  m_pCurvatureEngine->Clean();
  m_pSelectionEngine->Clean(true);
  m_pReferenceKeyEngine->Clean();

  // Rehook Server, and re-reference the inventor file
  HRESULT hr = ReferenceFile(lpFileName, dChordHtTol,bUseLiveConnection);
  OnErrorReturn(FAILED(hr), hr);

  // Post update
  hr = m_pDb->PostUpdate(this);

  return hr;
}

//////////////////////////////////////////////////////////////
// Methods for traversing an Inventor Part
//////////////////////////////////////////////////////////////

HRESULT CReferenceFileMgr::GetBodyInfo(CString& strFileName,
                                       int& nShellCount,
                                       int& nFaceCount,
                                       int& nEdgeCount,
                                       int& nVertexCount,
                                       double& fVolume)
{
  return GetReferenceFile()->_GetBodyInfo(nShellCount, nFaceCount, nEdgeCount, nVertexCount, fVolume);
}

//////////////////////////////////////////////////////////////
// Methods for selecting faces, edges and vertices from the graphics region
//////////////////////////////////////////////////////////////

HRESULT CReferenceFileMgr::PerformSelection(AppSelectMode eSelectMode,
                                            double chordHeightTol,
                                            double locateRadius,
                                            double pt1[3],
                                            double pt2[3])
{
	//double locateRadius = 0.001; //!! make it 5 pixels default, and configurable from the options dlg
  //if(eSelectMode != eFaceFilter)
  //  locateRadius = 0.08;

  IRxComponentDocument * pDoc = GetReferenceFile()->GetDocument();
  return GetSelectionEngine()->PerformSelection(pDoc, eSelectMode, locateRadius,
                                                chordHeightTol, pt1, pt2);
}

HRESULT CReferenceFileMgr::BuildSelectStrokes(double chordHeightTol)
{
  HRESULT hr = GetSelectionEngine()->BuildSelectStrokes(chordHeightTol);
  return hr;
}

IRxReferenceKey* CReferenceFileMgr::GetLastSelectedObject(CCurvatureAppDoc* pDoc)
{
  IRxReferenceKey* pRefKey = GetSelectionEngine()->GetLastSelectedObject();
  if(!pRefKey) {
    // Pull it from the ref key vector
    pRefKey = m_RefKeys.at(pDoc->GetCurrentCommand()).get_Object();
    HRESULT hr = SetLastSelectedObject(pRefKey);
    OnErrorReturn(FAILED(hr), NULL);

    if(pRefKey) {
      hr = BuildSelectStrokes(pDoc->m_chordHtTol);
      OnErrorReturn(FAILED(hr), NULL);
    }
  }

  return pRefKey;
}

//Get the previous selected vertex
IRxReferenceKey* CReferenceFileMgr::GetFirstVertex(CCurvatureAppDoc* pDoc)
{
  IRxReferenceKey* pRefKey = GetSelectionEngine()->GetFirstVertex();
  if(!pRefKey) {
    // Pull it from the ref key vector
    //(eMeasureDistanceCommand + 1 = 0x04) is equal to eMeasureDistanceCmdEntity2 that's the placeholder for the previous selected vertex.
    pRefKey = m_RefKeys.at(pDoc->eMeasureDistanceCommand + 1).get_Object();
    }

  return pRefKey;
}


HRESULT CReferenceFileMgr::SetLastSelectedObject(IRxReferenceKey *pRefKey)
{
  return GetSelectionEngine()->SetLastSelectedObject(pRefKey);
}

//////////////////////////////////////////////////////////////
// Methods for calculating curvature info for a selected face
//////////////////////////////////////////////////////////////

HRESULT CReferenceFileMgr::BuildCurvatureDisplayList(int uDensity, int vDensity)
{
  double* pPoints = 0; double* pNormals = 0;
  ULONG numPoints = 0;

  HRESULT hr = GetCurvatureEngine()->_CalculatePinCushion(m_RefKeys.at(eCurvatureCmdEntity),
                                                         uDensity, vDensity, 1.0,
                                                         &numPoints, &pPoints, &pNormals);
  OnErrorReturn(FAILED(hr), hr);

  GetCurvatureEngine()->Clean();
  GetCurvatureEngine()->m_numCurvaturePoints = numPoints;
  GetCurvatureEngine()->m_pCurvaturePoints = pPoints;
  GetCurvatureEngine()->m_pCurvatureNormals = pNormals;
  return hr;
}

HRESULT CReferenceFileMgr::BuildCurvatureGradient(double chordHtTol)
{
  double* pPoints = 0; double* pNormals = 0;
  ULONG numPoints = 0;
  ULONG numFacets = 0; ULONG* pPointIndices = 0;

  HRESULT hr = GetCurvatureEngine()->_CalculateCurvatureGradient(m_RefKeys.at(eCurvatureCmdEntity),
                        chordHtTol, 1.0, &numPoints, &pPoints, &pNormals,
                        &numFacets, &pPointIndices);
  OnErrorReturn(FAILED(hr), hr);

  GetCurvatureEngine()->Clean();
  GetCurvatureEngine()->m_pCurvatureGradientPoints = pPoints;
  GetCurvatureEngine()->m_pCurvatureGradientNormals = pNormals;
  GetCurvatureEngine()->m_numCurvatureGradientFacets = numFacets;
  GetCurvatureEngine()->m_pCurvatureGradientIndices = pPointIndices;

  return hr;
}

IRxReferenceKey* CReferenceFileMgr::GetCurvatureFace()
{
  return m_RefKeys.at(eCurvatureCmdEntity).get_Object();
}

HRESULT CReferenceFileMgr::SetCurvatureFace(IRxReferenceKey *pRefKey)
{
  HRESULT hr = m_RefKeys.at(eCurvatureCmdEntity).put_Object(pRefKey);
  return hr;
}

//////////////////////////////////////////////////////////////
// Measure methods
//////////////////////////////////////////////////////////////

HRESULT CReferenceFileMgr::MeasureFace()
{
  return GetMeasureEngine()->MeasureFace(m_RefKeys.at(eMeasureFaceCmdEntity));
}

HRESULT CReferenceFileMgr::MeasureEdge()
{
  return GetMeasureEngine()->MeasureEdge(m_RefKeys.at(eMeasureEdgeCmdEntity));
}

HRESULT CReferenceFileMgr::MeasureDistance()
{
  return GetMeasureEngine()->MeasureDistance(m_RefKeys.at(eMeasureDistanceCmdEntity2), m_RefKeys.at(eMeasureDistanceCmdEntity));
}

IRxReferenceKey* CReferenceFileMgr::GetMeasureFace()
{
  return m_RefKeys.at(eMeasureFaceCmdEntity).get_Object();
}

HRESULT CReferenceFileMgr::SetMeasureFace(IRxReferenceKey *pRefKey)
{
  return m_RefKeys.at(eMeasureFaceCmdEntity).put_Object(pRefKey);
}

IRxReferenceKey* CReferenceFileMgr::GetMeasureEdge()
{
  return m_RefKeys.at(eMeasureEdgeCmdEntity).get_Object();
}

HRESULT CReferenceFileMgr::SetMeasureEdge(IRxReferenceKey *pRefKey)
{
  return m_RefKeys.at(eMeasureEdgeCmdEntity).put_Object(pRefKey);
}

IRxReferenceKey* CReferenceFileMgr::GetMeasureVextex1()
{
	return m_RefKeys.at(eMeasureDistanceCmdEntity2).get_Object();
}

IRxReferenceKey* CReferenceFileMgr::GetMeasureVextex2()
{
	return m_RefKeys.at(eMeasureDistanceCmdEntity).get_Object();
}


HRESULT CReferenceFileMgr::SetMeasureVertices(IRxReferenceKey *pRefKey1, IRxReferenceKey *pRefKey2)
{
	HRESULT hr1, hr2;

	hr1 = m_RefKeys.at(eMeasureDistanceCmdEntity2).put_Object(pRefKey1);
	hr2 = m_RefKeys.at(eMeasureDistanceCmdEntity).put_Object(pRefKey2);

	if (SUCCEEDED(hr1) && SUCCEEDED(hr2))
		return S_OK;
	else
		return E_FAIL;
}
