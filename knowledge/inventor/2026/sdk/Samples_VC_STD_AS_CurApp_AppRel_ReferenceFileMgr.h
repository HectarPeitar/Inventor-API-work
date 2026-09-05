#ifndef INCLUDED_REFERENCE_FILE_MGR_H
#define INCLUDED_REFERENCE_FILE_MGR_H

#include "../InventorRelated/ReferenceKeyEngine.h"

class CCurvatureAppDoc;
class CReferenceFile;
class CSelectionEngine;
class CCurvatureEngine;
class CPersistenceEngine;
class CMeasureEngine;
class CCurvatureAppDb;

enum AppSelectMode { eUnknownFilter = 0x0, eFaceFilter = 0x01, eEdgeFilter = 0x02, eVertexFilter = 0x03 };

//eMeasureDistanceCmdEntity2 is a placeholder for the second vertex when using MeasureDistance
enum CurvatureAppCmdEntities { eCurvatureCmdEntity = 0x0,
							   eMeasureFaceCmdEntity = 0x1, 
                               eMeasureEdgeCmdEntity = 0x2,
                               eMeasureDistanceCmdEntity = 0x3,
							   eMeasureDistanceCmdEntity2 = 0x4,
							  };

const CurvatureAppCmdEntities k_CmdTable[][1] = 
{
  { eCurvatureCmdEntity },
  { eMeasureFaceCmdEntity },  
  { eMeasureEdgeCmdEntity },  
  { eMeasureDistanceCmdEntity },
  { eMeasureDistanceCmdEntity2 },
};



class CReferenceFileMgr {

friend CCurvatureAppDb;

public:
  CReferenceFileMgr();
  ~CReferenceFileMgr();

  // Called immediately after the constructor to tell whether this object is the owner of
  // m_pReferenceFile, m_pPersistenceEngine and m_pMeasureEngine members.
  // These members are shared by all views of a document. Only the owner is allowed to
  // new and delete these members.
  void SetOwner(CReferenceFileMgr* pRefFileMgr = 0);

  void Clean();
  void CleanKeys();

  //////////////////////////////////////////////////////////////
  // Methods for referencing/updating an Inventor file
  //////////////////////////////////////////////////////////////

  // Are we referencing an Inventor file right now?
  bool IsReferencingInventorFile() { return m_pReferenceFile != 0; }

  // Function used to refer a given inventor part file
  // Also creates the facet and stroke information with the given chordal height tolerance
  HRESULT ReferenceFile(LPCOLESTR lpFileName, double dChordHtTol,bool bUseLiveConnection);

  // Update (re-reference) an Inventor file
  HRESULT Update(LPCOLESTR lpFileName, double dChordHtTol,bool bUseLiveConnection);

  //////////////////////////////////////////////////////////////
  // Methods for traversing an Inventor Part
  //////////////////////////////////////////////////////////////

  // Traverses through the open inventor body, and gathers some brep information
	HRESULT GetBodyInfo(CString & strFileName, int & nShellCount, int & nFaceCount, int & nEdgeCount, int & nVertexCount, double & fVolume);

  //////////////////////////////////////////////////////////////
  // Methods for selecting faces, edges and vertices from the graphics region
  //////////////////////////////////////////////////////////////

  // Performs the selection on the open Inventor part.
  // The select mode has to one of eVertexFilter, eEdgeFilter or eFaceFilter
  HRESULT PerformSelection(AppSelectMode eSelectMode, double chordHeightTol, double locateRadius, double pt1[3], double pt2[3]);

  // Calculates the strokes and builds an OpenGL display list for the selected entity
  HRESULT BuildSelectStrokes(double chordHeightTol);

  // Get/Set the last selected object -> Vertex, Edge, Face
  IRxReferenceKey* GetLastSelectedObject(CCurvatureAppDoc* pDoc); // non counting
  IRxReferenceKey* GetFirstVertex(CCurvatureAppDoc* pDoc); // non counting, get the first vertex selected previous to measure distance with the last selected vertex.
  HRESULT SetLastSelectedObject(IRxReferenceKey *pRefKey);  //counting

  //////////////////////////////////////////////////////////////
  // Methods for calculating curvature info for a selected face
  //////////////////////////////////////////////////////////////

  // Calculates the curvatures on a selected face
  HRESULT BuildCurvatureDisplayList(int uDensity, int vDensity);
  HRESULT BuildCurvatureGradient(double chordHtTol);

  // Measure the face
  HRESULT MeasureFace();
  HRESULT MeasureEdge();
  HRESULT MeasureDistance();

  // Get/Set face for which curvature information is to be shown
  IRxReferenceKey* GetCurvatureFace();                   // non counting
  HRESULT SetCurvatureFace(IRxReferenceKey *pRefKey);    //counting

  IRxReferenceKey* GetMeasureFace();
  HRESULT SetMeasureFace(IRxReferenceKey *pRefKey);
  IRxReferenceKey* GetMeasureEdge();
  HRESULT SetMeasureEdge(IRxReferenceKey *pRefKey);
  IRxReferenceKey* GetMeasureVextex1();
  IRxReferenceKey* GetMeasureVextex2();
  HRESULT SetMeasureVertices(IRxReferenceKey *pRefKey1, IRxReferenceKey *pRefKey2);

  // Accessors
  CReferenceFile* GetReferenceFile() { ASSERT(m_pReferenceFile); return m_pReferenceFile; }
  CSelectionEngine* GetSelectionEngine() { ASSERT(m_pSelectionEngine); return m_pSelectionEngine; }
  CCurvatureEngine* GetCurvatureEngine() { ASSERT(m_pCurvatureEngine); return m_pCurvatureEngine; }
  CPersistenceEngine* GetPersistenceEngine() { ASSERT(m_pPersistenceEngine); return m_pPersistenceEngine; }
  CCurvatureAppDb* GetDb() { ASSERT(m_pDb); return m_pDb; }
  CMeasureEngine* GetMeasureEngine() { ASSERT(m_pMeasureEngine); return m_pMeasureEngine; }
  CReferenceKeyEngine* GetReferenceKeyEngine() { ASSERT(m_pReferenceKeyEngine); return m_pReferenceKeyEngine; }

protected:
  CReferenceFile* m_pReferenceFile{ nullptr };
  CPersistenceEngine* m_pPersistenceEngine{ nullptr };
  CCurvatureAppDb* m_pDb{ nullptr };
  CMeasureEngine* m_pMeasureEngine{ nullptr };
  CSelectionEngine* m_pSelectionEngine{ nullptr };
  CCurvatureEngine* m_pCurvatureEngine{ nullptr };
  CReferenceKeyEngine* m_pReferenceKeyEngine{ nullptr };

  RefKeyVec m_RefKeys;
};

class CPersistenceEngine {};

#endif
