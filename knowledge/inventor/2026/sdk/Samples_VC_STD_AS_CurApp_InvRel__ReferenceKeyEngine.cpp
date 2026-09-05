/*
  DESCRIPTION

  Implementation of the management methods of the CReferenceKey and 
  CReferenceKeyEngine class. 


  HISTORY

  SAM  :  10/15/99  :  Creation
*/

#include <stdafx.h>
#include "referencefile.h"
#include "referencekeyengine.h"

/*
 *  CReferenceKey Implementation
 */

/*--------------- Constructor(s), destructor and initializers ----------------------*/

CReferenceKey::CReferenceKey()
{
  m_KeySize = 0;
  m_Key = NULL;
  m_IID = IID_IUnknown;
  m_pRefKey = NULL;
  m_CommandContext = 0;
}

CReferenceKey::~CReferenceKey()
{
  m_KeySize = 0;
  if(m_Key) 
  { 
    ::CoTaskMemFree(m_Key); 
    m_Key = NULL; 
  }

  m_IID = IID_IUnknown;

  if(m_pRefKey) 
  {
    m_pRefKey->Release(); 
    m_pRefKey = NULL; 
  }

  m_CommandContext = 0;
}

void CReferenceKey::Clean()
{
  m_KeySize = 0;
  if(m_Key) 
  { 
    ::CoTaskMemFree(m_Key); 
    m_Key = NULL; 
  }

  m_IID = IID_IUnknown;

  if(m_pRefKey) 
  { 
    m_pRefKey->Release(); 
    m_pRefKey = NULL; 
  }
}

/*------------------- Management functions ---------------------------------*/

const ULONG CReferenceKey::get_KeySize()
{
  return m_KeySize;
}

const BYTE* CReferenceKey::get_Key()
{
  return m_Key;
}

HRESULT CReferenceKey::put_Key(const ULONG keySize, const BYTE* key)
{
  // Input validation
  //
  OnErrorReturn(!keySize, E_INVALIDARG);
  OnErrorReturn(!key, E_INVALIDARG);

  m_KeySize = keySize;

  // hate this
  //
  m_Key = const_cast<BYTE*>(key);

  return S_OK;
}

const IID& CReferenceKey::get_Type()
{
  return m_IID;
}

HRESULT CReferenceKey::put_Type(const IID& iid)
{
  m_IID = iid;
  return S_OK;
}

// non-counting
//
IRxReferenceKey* CReferenceKey::get_Object()
{
  return m_pRefKey;
}

// counting
//
HRESULT CReferenceKey::put_Object(IRxReferenceKey *pRefKey)
{
  // Its like an IUnknown identity, (isn't it really ?)
  //
  if(pRefKey == m_pRefKey)
    return S_OK;

  // Release the earlier one
  //
  if(m_pRefKey)
    m_pRefKey->Release();

  m_pRefKey = pRefKey;

  // AddRef the new one
  //
  if(m_pRefKey)
    m_pRefKey->AddRef();

  return S_OK;
}

const int CReferenceKey::get_CommandContext()
{
  return m_CommandContext;
}

HRESULT CReferenceKey::put_CommandContext(const int commandContext)
{
  m_CommandContext = commandContext;
  return S_OK;
}

boolean CReferenceKey::IsBound()
{
  if(m_pRefKey || (m_KeySize && m_Key))
    return true;
  else
    return false;
}

// Persistence

HRESULT CReferenceKey::Save(IStream *pStream)
{
  HRESULT hr=NOERROR;
  ULONG uiWritten=0;

  // Input validation
  //
  OnErrorReturn(!pStream, E_INVALIDARG);

// schema:
//
//int m_CommandContext;
//ULONG m_KeySize;
//BYTE *m_Key;  
//IID m_pIID;

  // write the command context
  //
  hr = pStream->Write(&m_CommandContext, sizeof(int), &uiWritten);
  OnErrorState((FAILED(hr) || uiWritten != sizeof(int)), hr, E_FAIL, wrapup);

  // write the key size
  //
  hr = pStream->Write(&m_KeySize, sizeof(ULONG), &uiWritten);
  OnErrorState((FAILED(hr) || uiWritten != sizeof(ULONG)), hr, E_FAIL, wrapup);

  if(m_KeySize) {
    // write the key
    //
    hr = pStream->Write(m_Key, sizeof(BYTE)*m_KeySize, &uiWritten);
    OnErrorState((FAILED(hr) || uiWritten != sizeof(BYTE)*m_KeySize), hr, E_FAIL, wrapup);

    // write the IID
    //
    hr= pStream->Write(&m_IID, sizeof(unsigned long)*4, &uiWritten);
    OnErrorState((FAILED(hr) || uiWritten != sizeof(unsigned long)*4), hr, E_FAIL, wrapup);
  }

wrapup:  
  return hr;
}

HRESULT CReferenceKey::Load(IStream *pStream)
{
  HRESULT hr=NOERROR;
  ULONG cbRead = 0;
  int commandContext=0;

	LARGE_INTEGER offset;
	ULARGE_INTEGER streamPos;

// schema:
//
//int m_CommandContext;
//ULONG m_KeySize;
//BYTE *m_Key;  
//IID m_pIID;

  // Input validation
  //
  OnErrorReturn(!pStream, E_INVALIDARG);

  offset.QuadPart = 0;
  hr = pStream->Seek(offset, STREAM_SEEK_CUR, &streamPos);
  OnErrorReturn(FAILED(hr), hr);

  // check if the command context matches the one saved, then it is ours
  // else reset the stream and return NOERROR;
  //
  hr = pStream->Read(&commandContext, sizeof(int), &cbRead);
  OnError(FAILED(hr), wrapup);

  if((cbRead != sizeof(int)) || (commandContext != m_CommandContext))
  {
   	offset.QuadPart = -cbRead;

    hr = pStream->Seek(offset, STREAM_SEEK_CUR, &streamPos);
    OnError(FAILED(hr), wrapup);

    hr = NOERROR;
    goto wrapup;
  }

  // read the key size
  //
  hr = pStream->Read(&m_KeySize, sizeof(ULONG), &cbRead);
  OnErrorState((FAILED(hr) || cbRead != sizeof(ULONG)), hr, E_FAIL, wrapup);

  if(m_KeySize) {
    // allocate for the key
    //
    m_Key = (BYTE *) ::CoTaskMemAlloc(m_KeySize*sizeof(BYTE)); //(new char[m_KeySize*sizeof(BYTE)];
    OnErrorState(!m_Key, hr, E_OUTOFMEMORY, wrapup)
  
    // read the key
    //
    hr = pStream->Read(m_Key, m_KeySize*sizeof(BYTE), &cbRead);
    OnErrorState((FAILED(hr) || cbRead != m_KeySize*sizeof(BYTE)), hr, E_FAIL, wrapup);

    // read the IID
    //
    hr= pStream->Read(&m_IID, sizeof(unsigned long)*4, &cbRead);
    OnErrorState((FAILED(hr) || cbRead != sizeof(unsigned long)*4), hr, E_FAIL, wrapup);
  }
    
wrapup:
  return hr;
}



/*
 *  CReferenceKeyEngine Implementation
 */

/*--------------- Constructor(s), destructor and initializers ----------------------*/


CReferenceKeyEngine::CReferenceKeyEngine()
{
  m_hKeyContext = 0;
}

CReferenceKeyEngine::~CReferenceKeyEngine()
{
  // release the resources;
  //
  m_hKeyContext = 0;
}

void CReferenceKeyEngine::Clean()
{
  m_hKeyContext = 0;
}


/*------------------- Management functions ---------------------------------*/

HRESULT CReferenceKeyEngine::_CreateKeyContext(IRxComponentDocument * pDoc)
{
  // Validate the input
  //
  OnErrorReturn(!pDoc, E_INVALIDARG);

  // We might have got loaded (not a new file), in which case we alread
  // have the key context handle
  //
  if(m_hKeyContext)
    return S_OK;

  return CreateKeyContext(pDoc, &m_hKeyContext);

}


HRESULT CReferenceKeyEngine::_LoadKeyContext(IRxComponentDocument * pDoc, IStorage *pRootStg)
{
  // Validate the input
  //
  OnErrorReturn(!pDoc, E_INVALIDARG);
  OnErrorReturn(!pRootStg, E_INVALIDARG);

  return LoadKeyContext(pDoc, pRootStg, &m_hKeyContext);
}



HRESULT CReferenceKeyEngine::_ConvertToKeys(RefKeyVec& refKeyVec)
{
  if(!m_hKeyContext || !refKeyVec.size())
    return S_OK;

  return ConvertToKeys(m_hKeyContext, refKeyVec);
}


HRESULT CReferenceKeyEngine::_ConvertToPointer(IRxComponentDocument * pDoc, RefKeyVec& refKeyVec)
{
  OnErrorReturn(!m_hKeyContext, E_FAIL);
  OnErrorReturn(!pDoc, E_INVALIDARG);
  if(!refKeyVec.size())
    return S_OK;

  return ConvertToPointer(pDoc, m_hKeyContext, refKeyVec);
}


HRESULT CReferenceKeyEngine::_SaveKeyContext(IRxComponentDocument * pDoc, IStorage *pRootStg)
{
  OnErrorReturn(!pRootStg, E_INVALIDARG);
  OnErrorReturn(!m_hKeyContext, E_FAIL);
  OnErrorReturn(!pDoc, E_INVALIDARG);

  return SaveKeyContext(pDoc, pRootStg, m_hKeyContext);
}


HRESULT CReferenceKeyEngine::_SaveKeys(IStorage *pRootStg, RefKeyVec& refKeyVec)
{
  // No member data to add here, just forward it to the exposed tutorial function.
  //
  return SaveKeys(pRootStg, refKeyVec);
}


HRESULT CReferenceKeyEngine::_LoadKeys(IStorage *pRootStg, RefKeyVec& refKeyVec)
{
  // No member data to add here, just forward it to the exposed tutorial function.
  //
  return LoadKeys(pRootStg, m_hKeyContext, refKeyVec);
}

