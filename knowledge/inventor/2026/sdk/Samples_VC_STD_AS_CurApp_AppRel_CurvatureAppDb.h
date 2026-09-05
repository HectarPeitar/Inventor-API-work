#ifndef _CurvatureAppDb_
#define _CurvatureAppDb_

// CurvatureAppDb.h
// Contains methods used for persisting and loading CurvatureApp files.

class CReferenceFileMgr;

class CCurvatureAppDb
{
public:
  CCurvatureAppDb();
  ~CCurvatureAppDb();

  HRESULT Open(WCHAR* lpFileName);

  // New Document, like a init new
  HRESULT InitNew(CReferenceFileMgr *i_pReferenceFileMgr);

  // Save out the CurvatureApp file to the disk
  HRESULT Save(WCHAR* i_lpReferencedFileName,
               double i_chordHtTol, UINT i_densityU, UINT i_densityV,
               BOOL i_shadedDisplayFlag, BOOL i_edgeDisplayFlag,
               UINT i_selectionTolerance, CReferenceFileMgr *i_pReferenceFileMgr);
  
  HRESULT SaveAs(WCHAR* lpFileName, WCHAR* i_lpReferencedFileName,
               double i_chordHtTol, UINT i_densityU, UINT i_densityV,
               BOOL i_shadedDisplayFlag, BOOL i_edgeDisplayFlag,
               UINT i_selectionTolerance, CReferenceFileMgr *i_pReferenceFileMgr);
  
  // Load the given Curvature App file from the disk
  HRESULT PreLoad(WCHAR** o_lpReferencedFileName,
                double* o_pChordHtTol,
                UINT* o_pDensityU, UINT* o_pDensityV,
                BOOL* o_pShadedDisplayFlag, BOOL* o_pEdgeDisplayFlag,
                UINT* m_pSelectionTolerance);
  
  // Load the reference information
  HRESULT Load(CReferenceFileMgr *i_pReferenceFileMgr);

  HRESULT PreUpdate(CReferenceFileMgr *i_pReferenceFileMgr);
  HRESULT PostUpdate(CReferenceFileMgr *i_pReferenceFileMgr);

protected:
  HRESULT WriteData(IStream* pInfoStrm,
                    WCHAR* i_lpReferencedFileName,
                    double i_chordHtTol,
                    UINT i_densityU, UINT i_densityV,
                    BOOL i_shadedDisplayFlag, BOOL i_edgeDisplayFlag,
                    UINT i_selectionTolerance,
                    CReferenceFileMgr *i_pReferenceFileMgr);

protected:
  typedef enum { eRead, eWrite, eReadWrite, eUnknown } EAccessMode;
  EAccessMode m_eAccessMode;
  CComPtr<IStorage>   m_pRootStorage;
  CComPtr<IStorage>   m_pTempRootStorage;
  bool        m_bSameAsLoad{false};
};

#endif