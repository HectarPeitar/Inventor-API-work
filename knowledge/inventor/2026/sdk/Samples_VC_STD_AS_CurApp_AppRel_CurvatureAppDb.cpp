#include<stdafx.h>
#include <objbase.h>
#include <afxpriv.h>  

#include "referencefilemgr.h"
#include "curvatureappdb.h"

#include "../InventorRelated/ReferenceFile.h"


// Local const values
const ULONG c_uiRevId = 1;
const DWORD c_grfCreateRootRW = STGM_CREATE | STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE;

const DWORD c_grfCreateSubRW = STGM_CREATE | STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE;
const DWORD c_grfOpenSubR = STGM_READ | STGM_DIRECT | STGM_SHARE_EXCLUSIVE;
const DWORD c_grfOpenSubRW = STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE;

const DWORD c_grfCreateStrmW = STGM_CREATE | STGM_WRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE;
const DWORD c_grfOpenStrmR = STGM_READ | STGM_DIRECT | STGM_SHARE_EXCLUSIVE;
const DWORD c_grfOpenStrmW = STGM_WRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE;

static LPCOLESTR c_InfoStream = OLESTR("InfoStream");

//////////// Constructors/Destructors for CCurvatureAppDb ///////////////
//
CCurvatureAppDb::CCurvatureAppDb()
: m_eAccessMode(eUnknown), m_pRootStorage(0), m_pTempRootStorage(0), m_bSameAsLoad(false)
{
}

CCurvatureAppDb::~CCurvatureAppDb()
{
  m_eAccessMode = eUnknown;
}

HRESULT CCurvatureAppDb::Open(WCHAR* lpFileName)
{
  OnErrorReturn(m_pRootStorage, E_FAIL);
  OnErrorReturn(!lpFileName, E_INVALIDARG);

  // Open the storage file for read access
  //
  m_pRootStorage = NULL;
  HRESULT hr = ::StgOpenStorage(lpFileName, 0,
                                STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE,
                                0, 0, &m_pRootStorage);
  ASSERT(SUCCEEDED(hr));
  m_eAccessMode = eRead;

  return hr;
}

HRESULT CCurvatureAppDb::InitNew(CReferenceFileMgr *i_pReferenceFileMgr)
{
  return S_OK;
}

HRESULT CCurvatureAppDb::WriteData(IStream* pInfoStrm,
                                   WCHAR* i_lpReferencedFileName,
                                   double i_chordHtTol,
                                   UINT i_densityU, UINT i_densityV,
                                   BOOL i_shadedDisplayFlag, BOOL i_edgeDisplayFlag,
                                   UINT i_selectionTolerance,
                                   CReferenceFileMgr* i_pReferenceFileMgr)
{
  USES_CONVERSION;
  HRESULT hr = E_NOTIMPL;
  ULONG uiWritten = 0;
  ULONG iReferencedFileNameSz = 0;

  OnErrorReturn(m_eAccessMode == eRead || m_eAccessMode == eUnknown, E_UNEXPECTED);

  // Write out the following information into it
  //
  // Schema Revision Number
  // Referenced Inventor Part full file name
  // The following option values for the active document view:
  //    chordal height tolerance (double)
  //    curvature density in u (int)
  //    curvature density in v (int)
  //    shaded display flag, on or off (bool)
  //    edge display flag, on or off (bool)
  //    selection aperture radius (double)
  //    (in future) translation, rotation and scale transform values

  hr = pInfoStrm->Write(&c_uiRevId, sizeof(ULONG), &uiWritten);
  OnError(FAILED(hr) || uiWritten != sizeof(ULONG), wrapup);

  if(i_lpReferencedFileName) {
    iReferencedFileNameSz = wcslen(i_lpReferencedFileName) + 1;
    hr = pInfoStrm->Write(&iReferencedFileNameSz, sizeof(iReferencedFileNameSz), &uiWritten);
    OnError(FAILED(hr) || uiWritten != sizeof(iReferencedFileNameSz), wrapup);

    hr = pInfoStrm->Write(i_lpReferencedFileName, iReferencedFileNameSz * sizeof(WCHAR), &uiWritten);
    OnError(FAILED(hr) || uiWritten != iReferencedFileNameSz * sizeof(WCHAR), wrapup);
  }
  else {
    iReferencedFileNameSz = 0;
    hr = pInfoStrm->Write(&iReferencedFileNameSz, sizeof(iReferencedFileNameSz), &uiWritten);
    OnError(FAILED(hr) || uiWritten != sizeof(iReferencedFileNameSz), wrapup);
  }

  hr = pInfoStrm->Write(&i_chordHtTol, sizeof(i_chordHtTol), &uiWritten);
  OnError(FAILED(hr) || uiWritten != sizeof(i_chordHtTol), wrapup);

  hr = pInfoStrm->Write(&i_densityU, sizeof(i_densityU), &uiWritten);
  OnError(FAILED(hr) || uiWritten != sizeof(i_densityU), wrapup);

  hr = pInfoStrm->Write(&i_densityV, sizeof(i_densityV), &uiWritten);
  OnError(FAILED(hr) || uiWritten != sizeof(i_densityV), wrapup);

  hr = pInfoStrm->Write(&i_shadedDisplayFlag, sizeof(i_shadedDisplayFlag), &uiWritten);
  OnError(FAILED(hr) || uiWritten != sizeof(i_shadedDisplayFlag), wrapup);

  hr = pInfoStrm->Write(&i_edgeDisplayFlag, sizeof(i_edgeDisplayFlag), &uiWritten);
  OnError(FAILED(hr) || uiWritten != sizeof(i_edgeDisplayFlag), wrapup);

  hr = pInfoStrm->Write(&i_selectionTolerance, sizeof(i_selectionTolerance), &uiWritten);
  OnError(FAILED(hr) || uiWritten != sizeof(i_selectionTolerance), wrapup);

  // write the keys and the context store
  //
  hr = i_pReferenceFileMgr->GetReferenceKeyEngine()->_OnSaveDocument(m_pRootStorage, i_pReferenceFileMgr->GetReferenceFile(), i_pReferenceFileMgr->m_RefKeys);
  OnError(FAILED(hr), wrapup);

wrapup:
  return hr;
}

// Save out the CurvatureApp file to the disk
HRESULT CCurvatureAppDb::Save(WCHAR* i_lpReferencedFileName,
                              double i_chordHtTol,
                              UINT i_densityU, UINT i_densityV,
                              BOOL i_shadedDisplayFlag, BOOL i_edgeDisplayFlag,
                              UINT i_selectionTolerance, CReferenceFileMgr *i_pReferenceFileMgr)
{
  USES_CONVERSION;
  IStream* pInfoStrm = nullptr;
  HRESULT hr = NOERROR;

  m_bSameAsLoad = true;

  OnErrorReturn(m_eAccessMode == eUnknown, E_UNEXPECTED);
  if(m_eAccessMode == eRead) {
    OnErrorReturn(!m_pRootStorage, E_UNEXPECTED);

    // Before releasing this read-only storage, remember the file name
    STATSTG stat;
    hr = m_pRootStorage->Stat(&stat, STATFLAG_DEFAULT);
    OnErrorReturn(FAILED(hr), hr);

    // Open the storage file for read-write access
    //
    LPWSTR pwcsName = stat.pwcsName;
	m_pRootStorage = NULL;
    hr = ::StgOpenStorage(pwcsName, 0,
                          STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE,
                          0, 0, &m_pRootStorage);
	CoTaskMemFree(stat.pwcsName);
    OnErrorReturn(FAILED(hr), hr);
    m_eAccessMode = eReadWrite;
  }

  // Open the stream within this root storage
  hr = m_pRootStorage->OpenStream(c_InfoStream, 0, c_grfOpenStrmW, 0, &pInfoStrm);
  OnErrorReturn(FAILED(hr), hr);

  hr = WriteData(pInfoStrm, i_lpReferencedFileName,
                  i_chordHtTol, i_densityU, i_densityV,
                  i_shadedDisplayFlag, i_edgeDisplayFlag, i_selectionTolerance, i_pReferenceFileMgr);
  OnError(FAILED(hr), wrapup);

wrapup:
  if(pInfoStrm)
    pInfoStrm->Release();

  return hr;
}

// Save out the CurvatureApp file to the disk
HRESULT CCurvatureAppDb::SaveAs(WCHAR* lpFileName,
                                WCHAR* i_lpReferencedFileName,
                                double i_chordHtTol,
                                UINT i_densityU, UINT i_densityV,
                                BOOL i_shadedDisplayFlag, BOOL i_edgeDisplayFlag,
                                UINT i_selectionTolerance, CReferenceFileMgr *i_pReferenceFileMgr)
{
  USES_CONVERSION;
  HRESULT hr = E_NOTIMPL;
  IStream* pInfoStrm = nullptr;

  // Create a new storage with the given file name
  //
  m_pRootStorage = NULL;
  hr = ::StgCreateDocfile(lpFileName, 
                           STGM_CREATE | STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE, 
                           0, 
                           &m_pRootStorage);
  if(FAILED(hr)) {
    ASSERT(false);
    return hr;
  }
  m_eAccessMode = eReadWrite;

  m_bSameAsLoad = false;

  // Create a new info stream in this storage
	hr = m_pRootStorage->CreateStream(c_InfoStream, c_grfCreateStrmW, 0, 0, &pInfoStrm);
  if(FAILED(hr)) {
    ASSERT(false);
    goto wrapup;
  }

  if(!i_pReferenceFileMgr)
    goto wrapup;

  hr = WriteData(pInfoStrm, i_lpReferencedFileName,
                  i_chordHtTol, i_densityU, i_densityV,
                  i_shadedDisplayFlag, i_edgeDisplayFlag, i_selectionTolerance, i_pReferenceFileMgr);
  if(FAILED(hr)) {
    ASSERT(false);
    goto wrapup;
  }

wrapup:
  if(pInfoStrm)
    pInfoStrm->Release();

  return hr;
}

// Load the given Curvature App file from the disk
HRESULT CCurvatureAppDb::PreLoad(WCHAR** o_lpReferencedFileName,
                              double* o_pChordHtTol,
                              UINT* o_pDensityU, UINT* o_pDensityV,
                              BOOL* o_pShadedDisplayFlag, BOOL* o_pEdgeDisplayFlag,
                              UINT* o_pSelectionTolerance)
{
  USES_CONVERSION;

  if(!m_pRootStorage) {
    ASSERT(false);
    return E_FAIL;
  }

  ASSERT(o_lpReferencedFileName && o_pChordHtTol && o_pDensityU && o_pDensityV &&
        o_pShadedDisplayFlag && o_pEdgeDisplayFlag && o_pSelectionTolerance);

  // Initialize values
  *o_lpReferencedFileName = nullptr;
  *o_pChordHtTol = 0;
  *o_pDensityU = *o_pDensityV = 0;
  *o_pShadedDisplayFlag = *o_pEdgeDisplayFlag = FALSE;
  *o_pSelectionTolerance = 0;

  // Open the stream within this root storage
  IStream* pInfoStrm = nullptr;
  HRESULT hr = m_pRootStorage->OpenStream(c_InfoStream, 0, c_grfOpenStrmR, 0, &pInfoStrm);
  if(FAILED(hr)) {
    ASSERT(false);
    return hr;
  }

  // Read in the following information from the stream
  //
  // Schema Revision Number
  // Referenced Inventor Part full file name
  // The following option values for the document views:
  //    chordal height tolerance (double)
  //    curvature density in u (int)
  //    curvature density in v (int)
  //    shaded display flag, on or off (bool)
  //    edge display flag, on or off (bool)
  //    selection aperture radius (double)
  //    (in future) translation, rotation and scale transform values

  ULONG uiRevId;
  ULONG cbRead = 0;
  ULONG iNameSz = 0;
  hr = pInfoStrm->Read(&uiRevId, sizeof(uiRevId), &cbRead);
  if(FAILED(hr)) {
    ASSERT(false);
    goto wrapup;
  }

  hr = pInfoStrm->Read(&iNameSz, sizeof(iNameSz), &cbRead);
  if(FAILED(hr)) {
    ASSERT(false);
    goto wrapup;
  }

  if(iNameSz) {
    *o_lpReferencedFileName = new WCHAR[iNameSz]{};
    hr = pInfoStrm->Read(*o_lpReferencedFileName, iNameSz * sizeof(WCHAR), &cbRead);
    if(FAILED(hr)) {
      ASSERT(false);
      goto wrapup;
    }
  }

  hr = pInfoStrm->Read(o_pChordHtTol, sizeof(*o_pChordHtTol), &cbRead);
  if(FAILED(hr)) {
    ASSERT(false);
    goto wrapup;
  }

  hr = pInfoStrm->Read(o_pDensityU, sizeof(*o_pDensityU), &cbRead);
  if(FAILED(hr)) {
    ASSERT(false);
    goto wrapup;
  }

  hr = pInfoStrm->Read(o_pDensityV, sizeof(*o_pDensityV), &cbRead);
  if(FAILED(hr)) {
    ASSERT(false);
    goto wrapup;
  }

  hr = pInfoStrm->Read(o_pShadedDisplayFlag, sizeof(*o_pShadedDisplayFlag), &cbRead);
  if(FAILED(hr)) {
    ASSERT(false);
    goto wrapup;
  }

  hr = pInfoStrm->Read(o_pEdgeDisplayFlag, sizeof(*o_pEdgeDisplayFlag), &cbRead);
  if(FAILED(hr)) {
    ASSERT(false);
    goto wrapup;
  }

  hr = pInfoStrm->Read(o_pSelectionTolerance, sizeof(*o_pSelectionTolerance), &cbRead);
  if(FAILED(hr)) {
    ASSERT(false);
    goto wrapup;
  }

wrapup:
  pInfoStrm->Release();

  if(FAILED(hr) && *o_lpReferencedFileName) {
    delete [] *o_lpReferencedFileName;
    *o_lpReferencedFileName = nullptr;
  }

  return hr;
}

HRESULT CCurvatureAppDb::Load(CReferenceFileMgr *pReferenceFileMgr)
{
  USES_CONVERSION;
  HRESULT hr = NOERROR;

  OnErrorReturn(!m_pRootStorage, E_FAIL);

  // Load the keys and the context store
  //
  hr = pReferenceFileMgr->GetReferenceKeyEngine()->_OnLoadDocument(m_pRootStorage, pReferenceFileMgr->GetReferenceFile(),
                                                                   pReferenceFileMgr->m_RefKeys);
  OnError(FAILED(hr), wrapup);

wrapup:

  return hr;
}

HRESULT CCurvatureAppDb::PreUpdate(CReferenceFileMgr *i_pReferenceFileMgr)
{
  // Create a scratch space for the server object 
  //
  HRESULT hr = ::StgCreateDocfile(NULL, c_grfCreateRootRW | STGM_DELETEONRELEASE,
                           0, &m_pTempRootStorage);
  ASSERT(SUCCEEDED(hr));

  // Delegate it to the ReferenceKeyEngine 
  //
  hr = i_pReferenceFileMgr->GetReferenceKeyEngine()->_OnPreUpdateDocument(m_pTempRootStorage,
                                                                           i_pReferenceFileMgr->GetReferenceFile(),
                                                                           i_pReferenceFileMgr->m_RefKeys);
  OnErrorReturn(FAILED(hr), hr);

  return hr;
}

HRESULT CCurvatureAppDb::PostUpdate(CReferenceFileMgr* i_pReferenceFileMgr)
{
  // Delegate it to the ReferenceKeyEngine 
  //
  HRESULT hr=NOERROR;

  hr = i_pReferenceFileMgr->GetReferenceKeyEngine()->_OnPostUpdateDocument(m_pTempRootStorage,
                                                                           i_pReferenceFileMgr->GetReferenceFile(),
                                                                           i_pReferenceFileMgr->m_RefKeys);
  OnErrorReturn(FAILED(hr), hr);

  return hr;
}
