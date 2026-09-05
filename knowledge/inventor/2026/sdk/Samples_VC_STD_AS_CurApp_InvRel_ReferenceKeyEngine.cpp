/*
  DESCRIPTION

  Implementation of the API-related methods of the CReferenceFile class. 


  HISTORY

  SAM  :  10/15/99  :  Creation
*/

#include <stdafx.h>
#include "referencefile.h"
#include "referencekeyengine.h"


/*------------------------ Higher level functions -----------------------------*/

// This function is called by the application when a document is loaded up. The document's
// root storage is passed in, in which the function looks for and loads up the Key Context
// storage. It then loads up the Keys (now possessing a KeyContext) and converts these
// keys into live pointers that can now be used to make the API method calls.
//
// NOTE: This is a higher level function that does not directly make API calls. But it serves
// well to illustrate how the ReferenceKey mechanism si to be worked.

HRESULT CReferenceKeyEngine::_OnLoadDocument(IStorage *pRootStg, CReferenceFile *i_pReferenceFile, RefKeyVec& refKeyVec)
{
	HRESULT hr=NOERROR;

	// Intialize/load the key context store
	hr = _LoadKeyContext(i_pReferenceFile->GetDocument(), pRootStg);
	if(STG_E_FILENOTFOUND  == hr) 
	{
		// There are no keys to load. Return peacefully
		return S_OK;
	}
	OnErrorReturn(FAILED(hr), hr);

	// Load the keys 
	hr = _LoadKeys(pRootStg, refKeyVec);
	OnErrorReturn(FAILED(hr), hr);

	// Swizzle them to pointers (ready to fly)
	hr = _ConvertToPointer(i_pReferenceFile->GetDocument(), refKeyVec);
	return hr;
}

  
// This function is called by the application when a document is being saved. It is the 
// function that handles the saving of Keys (persistent version of a BRep object pointer)
// Only SurfaceBody, Face, Edge and Vertex pointers can be saved as such. FaceShell, EdgeLoop
// and EdgeUse pointers do not produce persistent versions of themselves.
//
// Towards saving, the first step is to convert the live pointers we have into Keys. For
// which we need to obtain a KeyContext (or the handle to it). Then using it, convert
// the live pointers to Keys. Then proceed to save both the Keys as well as the KeyContext.
//
// NOTE: This is a higher level function that does not directly make API calls. But it serves
// well to illustrate how the ReferenceKey mechanism si to be worked.

HRESULT CReferenceKeyEngine::_OnSaveDocument(IStorage *pRootStg, CReferenceFile *i_pReferenceFile, RefKeyVec& refKeyVec)
{
	HRESULT hr=NOERROR;

	// Trivial exit, if we find that none of the  keys passed in have any content
	RefKeyVec::iterator iter;
	for(iter = refKeyVec.begin(); iter != refKeyVec.end(); iter++)
	{
		if((*iter).IsBound())
			break;
	}
	if(iter == refKeyVec.end())
		return S_OK;


	// Create/retrieve the key context which helps us get to the keys
	//
	hr = _CreateKeyContext(i_pReferenceFile->GetDocument());
	OnErrorReturn(FAILED(hr), hr);

	// Convert the pointers to keys
	//
	hr = _ConvertToKeys(refKeyVec);
	OnErrorReturn(FAILED(hr), hr);

	// Now save the key context store
	//
	hr = _SaveKeyContext(i_pReferenceFile->GetDocument(), pRootStg);
	OnErrorReturn(FAILED(hr), hr);

	// Now save the keys
	//
	hr = _SaveKeys(pRootStg, refKeyVec);
	OnErrorReturn(FAILED(hr), hr);
	return hr;
}


// The update of a reference to an Inventor file is accomplished in 3 steps. The first
// one is a preparation for the update, the second is the actual reloading of the Inventor
// file, and the third is the fixup that follows. The following function accomplishes
// the first step as far as Keys are concerned -- converts all pointers to keys and temporarily
// stores away the KeyContext. In the final step, the KeyContext will be restored and the
// Keys bound back to live pointers.
//
// NOTE: This is a higher level function that does not directly make API calls. But it serves
// well to illustrate how the ReferenceKey mechanism si to be worked.

HRESULT CReferenceKeyEngine::_OnPreUpdateDocument(IStorage *pTempStg, CReferenceFile *i_pReferenceFile, RefKeyVec& refKeyVec)
{
	HRESULT hr=NOERROR;

	// Trivial exit, if we find that none of the  keys passed in have any content
	//
	RefKeyVec::iterator iter;
	for(iter = refKeyVec.begin(); iter != refKeyVec.end(); iter++)
	{
		if((*iter).IsBound())
			break;
	}
	if(iter == refKeyVec.end())
		return S_OK;

	// Create the key context which helps us get to the keys
	//
	hr = _CreateKeyContext(i_pReferenceFile->GetDocument());
	OnErrorReturn(FAILED(hr), hr);

	// Convert the pointers to keys
	//
	hr = _ConvertToKeys(refKeyVec);
	OnErrorReturn(FAILED(hr), hr);

	// Now save the key context store
	//
	hr = _SaveKeyContext(i_pReferenceFile->GetDocument(), pTempStg);
	OnErrorReturn(FAILED(hr), hr);

	return hr;
}


// This is the final step in completing the update. In this step, the temporarily stored
// KeyContext is restored (obtaining the new KeyContext handle representing it). We can
// safely get rid of this temporary storage of the KeyContext. Note that we ended up
// creating a temporary storage for the KeyContext because Update does not imply
// 'Save'ing anything into this document. It is merely a refresh of the document.
// After obtaining the KeyContext we can now bind back the Keys to live pointers in the
// freshly referenced file.

HRESULT CReferenceKeyEngine::_OnPostUpdateDocument(IStorage *pTempStg, CReferenceFile *i_pReferenceFile, RefKeyVec& refKeyVec)
{
	HRESULT hr=NOERROR;

	// Intialize/load the key context store
	//
	hr = _LoadKeyContext(i_pReferenceFile->GetDocument(), pTempStg);
	if(STG_E_FILENOTFOUND  == hr) 
	{
		// There are no keys to load. Return peacefully
		return S_OK;
	}
	OnErrorReturn(FAILED(hr), hr);

	// Swizzle the keys to pointers (rebind them)
	//
	hr = _ConvertToPointer(i_pReferenceFile->GetDocument(), refKeyVec);
	return hr;
}




/*------------------------ API-related functions -----------------------------*/


const DWORD c_grfCreateRootRW = STGM_CREATE | STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE;

const DWORD c_grfCreateSubRW = STGM_CREATE | STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE;
const DWORD c_grfOpenSubR = STGM_READ | STGM_DIRECT | STGM_SHARE_EXCLUSIVE;
const DWORD c_grfOpenSubRW = STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE;

const DWORD c_grfCreateStrmW = STGM_CREATE | STGM_WRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE;
const DWORD c_grfOpenStrmR = STGM_READ | STGM_DIRECT | STGM_SHARE_EXCLUSIVE;
const DWORD c_grfOpenStrmW = STGM_WRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE;

// Stream where the keys lie
//
static LPCOLESTR c_ReferenceKeyStream = OLESTR("RefKeyStream");

// Sub-Storage where the Key context store resides
//
static LPCOLESTR c_RefKeyContextStorage = OLESTR("RefKeyContextStorage");



// This function creates a new Key Context in which Reference Keys are to be generated.
// The Server is passed in from whose Document one can obtain the KeyContext.

HRESULT CReferenceKeyEngine::CreateKeyContext(IRxComponentDocument * pDoc, DWORD *phKeyContext)
{
	HRESULT hr=NOERROR;
	IRxComponentDocument *pApprenticeSrvrDoc=pDoc;
	IRxReferenceKeyManager *pApprenticeRefMgr=NULL;

	// Validate the input
	//
	OnErrorReturn(!pDoc, E_INVALIDARG);
	OnErrorReturn(!phKeyContext, E_INVALIDARG);

	// Initialize
	//
	*phKeyContext = 0;

	// Get to the reference manager
	//
	hr = pApprenticeSrvrDoc->QueryInterface(IID_IRxReferenceKeyManager, (void **)&pApprenticeRefMgr);
	OnError(FAILED(hr), wrapup);

	// Create and Get the handle to the Key context store.
	//
	hr = pApprenticeRefMgr->CreateKeyContext(phKeyContext);
	OnErrorState((FAILED(hr) || !(*phKeyContext)), hr, E_FAIL, wrapup);


wrapup:  
	if (pApprenticeRefMgr) 
		pApprenticeRefMgr->Release(); 
	if (pApprenticeSrvrDoc) 
		pApprenticeSrvrDoc->Release();

	return hr;
}


// This function is used to load in the KeyContext that has been saved out with the 
// document. The KeyContext is stored in a sub-storage. In this application we chose
// to save it off the Root. Its name is available in the constant 'c_RefKeyContextStorage'
// and one could open this sub-storage thusly:
//
//  hr = pRootStg->OpenStorage (c_RefKeyContextStorage, 0, c_grfOpenSubR, 0, 0, &pRefKeyContextStorage);
//  if (STG_E_FILENOTFOUND == hr) 
//  {
//    // There are no reference keys saved to the disk
//      goto wrapup;
//  }
//  OnError(FAILED(hr), wrapup);
//
// Having obtained the IStorage* in which the KeyContext lives, one can now use the API method
// to retrieve the handle to the KeyContext.

HRESULT CReferenceKeyEngine::LoadKeyContext(IRxComponentDocument * pDoc, IStorage *pRootStg, 
                                            DWORD *phKeyContext)
{  
	HRESULT hr=NOERROR;
	IRxComponentDocument *pApprenticeSrvrDoc=pDoc;
	IRxReferenceKeyManager *pApprenticeRefMgr=NULL;
	IStorage* pRefKeyContextStorage=NULL;

  const OLECHAR *pwcsName = L"ContextStream";
  DWORD grfMode = STGM_READ|STGM_DIRECT | STGM_SHARE_EXCLUSIVE;
  void *reserved1 = NULL;
  DWORD reserved2 = 0;
  IStream *pstm = NULL;

  // Validate the input
	//
	OnErrorReturn(!pDoc, E_INVALIDARG);
	OnErrorReturn(!pRootStg, E_INVALIDARG);
	OnErrorReturn(!phKeyContext, E_INVALIDARG);

	// Initialize
	//
	*phKeyContext = 0;

	// Get to the reference manager
	//
	hr = pApprenticeSrvrDoc->QueryInterface(IID_IRxReferenceKeyManager, (void **)&pApprenticeRefMgr);
	OnError(FAILED(hr), wrapup);

	// Now open our "KeyContextStore" sub-storage. We need to pass it so that the
	// keys could swizzled to pointers.
	//   
	hr = pRootStg->OpenStorage(c_RefKeyContextStorage, 0, c_grfOpenSubR, 0, 0, &pRefKeyContextStorage);
	if(STG_E_FILENOTFOUND == hr) 
	{
		// There are no reference keys saved to the disk
		goto wrapup;
	}
	OnError(FAILED(hr), wrapup);

  // Create a stream in here
  hr = pRefKeyContextStorage->OpenStream(pwcsName,  //Pointer to name of stream to open
                                         reserved1,        //Reserved; must be NULL
                                         grfMode,          //Access mode for the new stream
                                         reserved2,        //Reserved; must be zero
                                         &pstm);

	OnError(FAILED(hr), wrapup);

	// Get the handle to the Key context store and ask it to load the "KeyContextStore"
	//
	hr = pApprenticeRefMgr->LoadKeyContext(phKeyContext, pstm);
	OnErrorState((FAILED(hr) || !(*phKeyContext)), hr, E_FAIL, wrapup);


	wrapup:  
	if (pRefKeyContextStorage) 
		pRefKeyContextStorage->Release();
	if (pApprenticeRefMgr) 
		pApprenticeRefMgr->Release();
	if (pApprenticeSrvrDoc) 
		pApprenticeSrvrDoc->Release(); 

	return hr;
}


// This function is used to save the current KeyContext with the Document.
// The KeyContext is stored in a sub-storage. In this application we chose to save it off the Root. 
// Its name is available in the constant 'c_RefKeyContextStorage' and one 
// could open this sub-storage thusly:
//
//    hr = pRootStg->OpenStorage(c_RefKeyContextStorage, 0, c_grfOpenSubRW, 0, 0, &pRefKeyContextStorage);
//    if(FAILED(hr))
//    {
//      // Create the "KeyContextStore" sub-storage (it does not exist)
//      //
//      hr = pRootStg->CreateStorage(c_RefKeyContextStorage, c_grfCreateSubRW, 0, 0, &pRefKeyContextStorage);
//      OnError(FAILED(hr), wrapup);
//    }
//
// Having obtained the IStorage* in which the KeyContext should live, one can now use the API method
// to store it away.

HRESULT CReferenceKeyEngine::SaveKeyContext(IRxComponentDocument * pDoc, IStorage *pRootStg, DWORD hKeyContext)
{
	HRESULT hr=NOERROR;
	IRxComponentDocument *pApprenticeSrvrDoc=pDoc;
	IRxReferenceKeyManager *pApprenticeRefMgr=NULL;
	IStorage* pRefKeyContextStorage=NULL;

  const OLECHAR *pwcsName = L"ContextStream";
  DWORD grfMode = STGM_DIRECT | STGM_CREATE | STGM_WRITE | STGM_SHARE_EXCLUSIVE;
  DWORD reserved1 = 0;
  DWORD reserved2 = 0;
  CComPtr<IStream> pstm;
  CComPtr<IStream> pTempStream;
  
	// Validate the input
	//
	OnErrorReturn(!pDoc, E_INVALIDARG);
	OnErrorReturn(!pRootStg, E_INVALIDARG);

	// If the handle is null, bail out, we should have created it
	// before swizzling the pointers to keys. Why else would you want
	// to save the key context if you handn't got keys.
	//
	OnErrorReturn(!hKeyContext, E_INVALIDARG);

	// Get to the reference manager
	//
	hr = pApprenticeSrvrDoc->QueryInterface(IID_IRxReferenceKeyManager, (void **)&pApprenticeRefMgr);
	OnError(FAILED(hr), wrapup);

	// Write the context into a temporary stream.
	//
	hr = ::CreateStreamOnHGlobal(NULL, TRUE, &pTempStream);
	OnErrorReturn(FAILED(hr), hr);

	hr = pApprenticeRefMgr->SaveKeyContext(hKeyContext, pTempStream);
	OnErrorState(FAILED(hr), hr, E_FAIL, wrapup);

	// Rewind the temporary stream
	//
	LARGE_INTEGER liOff;
	LISet32(liOff,  0);
	hr = pTempStream->Seek(liOff, STREAM_SEEK_SET, NULL);
	OnErrorReturn(FAILED(hr), hr);

	// At this time, we could have a new file or a file already loaded.
	// So, get to the "KeyContextStorage" if present or create one.
	//    
	hr = pRootStg->OpenStorage(c_RefKeyContextStorage, 0, c_grfOpenSubRW, 0, 0, &pRefKeyContextStorage);
	if(FAILED(hr))
	{
		// Create the "KeyContextStore" sub-storage (it does not exist)
		//
		hr = pRootStg->CreateStorage(c_RefKeyContextStorage, c_grfCreateSubRW, 0, 0, &pRefKeyContextStorage);
		OnError(FAILED(hr), wrapup);
	}

	// Create a stream in here
	hr = pRefKeyContextStorage->CreateStream(pwcsName,grfMode,reserved1,reserved2,&pstm);
	OnError(FAILED(hr), wrapup);
  
	// Read the data from the temporary stream and write it into the file stream
	//
	const int BufferSize = 256;
	BYTE buffer[BufferSize];
	ULONG nRead;
	ULONG nWritten;

	do
	{
		hr = pTempStream->Read(buffer, BufferSize, &nRead);
		if (nRead)
		{
			hr = pstm->Write(buffer, nRead, &nWritten);
			OnError((nRead != nWritten), wrapup);
		}
	} while (SUCCEEDED(hr) && nRead == BufferSize);


wrapup:

	// release the resources
	//
	if (pApprenticeRefMgr) 
		pApprenticeRefMgr->Release(); 
	if (pApprenticeSrvrDoc) 
		pApprenticeSrvrDoc->Release(); 
	if (pRefKeyContextStorage) 
		pRefKeyContextStorage->Release(); 

	return hr;
}


// Given a KeyContext handle this function is used to convert all of the live pointers
// in the input vector of Keys, into persistent 'Key' representations. Each of the pointers
// is encapsulated in a CReferenceKey class, which provides convenient ways of operating
// on the pointers/keys

HRESULT CReferenceKeyEngine::ConvertToKeys(DWORD hKeyContext, RefKeyVec& refKeyVec)
{
	HRESULT hr=NOERROR;
	ULONG keySize=0;
	BYTE* pKey=NULL;
	IID objectIID;

	RefKeyVec::iterator iter;

	// Validate the input
	//
	OnErrorReturn(!hKeyContext, E_INVALIDARG);
	OnErrorReturn(!refKeyVec.size(), E_INVALIDARG);

	// Now convert each object to key, skip those that are empty (not bound).
	//
	for(iter = refKeyVec.begin(); iter != refKeyVec.end(); iter++)
	{
		if((*iter).IsBound())
		{
			IRxReferenceKey *pRefKey=NULL;

			// get to the IRxReferenceKeyManager interface stowed inside the key class
			//
			pRefKey = (*iter).get_Object();
			OnErrorState(!pRefKey, hr, E_FAIL, wrapup);

			// Obtain the persistent Key for this object within the KeyContext (indicated
			// by its handle)
			//
			hr = pRefKey->get_Key(hKeyContext, &keySize, &pKey);
			OnError(FAILED(hr), wrapup);

			// Now stuff the key information into the Key class
			//
			hr = (*iter).put_Key(keySize, pKey);
			OnError(FAILED(hr), wrapup);

			// Stuff the primary (or type-identifying) IID of the object in as well
			//
			hr = pRefKey->get_ObjectType(&objectIID);
			OnError(FAILED(hr), wrapup);

			hr = (*iter).put_Type(objectIID);
			OnError(FAILED(hr), wrapup);      
		}
	}

wrapup: 
	return hr;
}


// Given a KeyContext handle this function is used to convert all of the persistent Keys
// in the input vector of Keys, into live pointers. 

HRESULT CReferenceKeyEngine::ConvertToPointer(IRxComponentDocument * pDoc, DWORD hKeyContext, RefKeyVec& refKeyVec)
{
	HRESULT hr=NOERROR;
	IRxComponentDocument *pApprenticeSrvrDoc=pDoc;
	IRxReferenceKeyManager *pApprenticeRefMgr=NULL;
	SolutionNatureEnum MatchType;

	RefKeyVec::iterator iter;
	IRxReferenceKey *pRefKey=NULL;
	IID refIID = IID_IRxReferenceKey;
  
	// Validate the input
	//
	OnErrorReturn(!pDoc, E_INVALIDARG);
	OnErrorReturn(!hKeyContext, E_INVALIDARG);
	OnErrorReturn(!refKeyVec.size(), E_INVALIDARG);

	// Get to the reference manager
	//
	hr = pApprenticeSrvrDoc->QueryInterface(IID_IRxReferenceKeyManager, (void **) &pApprenticeRefMgr);
	OnError(FAILED(hr), wrapup);

	// Now convert each key to pointer, skip the items that are empty
	//
	for(iter = refKeyVec.begin(); iter != refKeyVec.end(); iter++)
	{
		if((*iter).IsBound())
		{
			// Check the key class state
			//
			OnErrorState(!((*iter).get_KeySize()), hr, E_INVALIDARG, wrapup);

			// Populate the key classes with IRxReferenceKey interface
			//
			hr = pApprenticeRefMgr->BindKeyToInterface(hKeyContext, 
							 &refIID, (*iter).get_KeySize(), const_cast<BYTE*>((*iter).get_Key()), 
							 (void **)&pRefKey, &MatchType, NULL);
			OnError(FAILED(hr), wrapup);

			// Now stuff the pointer in the Key class
			//
			hr = (*iter).put_Object(pRefKey);

      // If no match was found, continue on to the next
      //
      if (MatchType == kNoSolution)
        continue;

			// Release the interface, as the put_Object has RefCounted it while storing away
			// the pointer
			//
			pRefKey->Release();

			// check how put_Object() fared.
			OnError(FAILED(hr), wrapup);
		}
	}

wrapup: 
	if (pApprenticeRefMgr) 
		pApprenticeRefMgr->Release(); 
	if (pApprenticeSrvrDoc) 
		pApprenticeSrvrDoc->Release();

	return hr;
}

// This function is used to store away the persistent form of the BRep object pointers.
// These are stored away in a stream within the document's Root storage. The IStream*
// is thusly obtained (the name of the stream in this application is known in the constant
// 'c_ReferenceKeyStream':
//
//  hr = pRootStg->OpenStream(c_ReferenceKeyStream, 0, c_grfOpenStrmW, 0, &pRefKeyStrm);
//  if(FAILED(hr))
//  {
//    // We don't have the stream to store the keys, create it.
//    //
//      hr = pRootStg->CreateStream(c_ReferenceKeyStream, c_grfCreateStrmW, 0, 0, &pRefKeyStrm);
//      OnError(FAILED(hr), wrapup);
//  }
//
// On successful completion of this method we now have a saved version of the pointers
// which can be refreshed on retrieval or load. The actual streaming out of the persistent
// key is done via the 'Save' function on the CReferenceKey class (the wrapper for the
// IRxReferenceKey).

HRESULT CReferenceKeyEngine::SaveKeys(IStorage *pRootStg, RefKeyVec& refKeyVec)
{
	HRESULT hr=NOERROR;
	RefKeyVec::iterator iter;

	// Validate the input
	//
	OnErrorReturn(!refKeyVec.size(), E_INVALIDARG);
	OnErrorReturn(!pRootStg, E_INVALIDARG);
	IStream* pRefKeyStrm=NULL;

	// Now determine whether we have the "ReferenceKeyStream" to save the keys, if not
	// create it, and then save each key.
	// 
	hr = pRootStg->OpenStream(c_ReferenceKeyStream, 0, c_grfOpenStrmW, 0, &pRefKeyStrm);
	if(FAILED(hr))
	{
		// We don't have the stream to store the keys, create it.
		//
		hr = pRootStg->CreateStream(c_ReferenceKeyStream, c_grfCreateStrmW, 0, 0, &pRefKeyStrm);
		OnError(FAILED(hr), wrapup);
	}

	// Now save each key.
	//
	for(iter = refKeyVec.begin(); iter != refKeyVec.end(); iter++)
	{
		hr = (*iter).Save(pRefKeyStrm);
		OnError(FAILED(hr), wrapup);
	}

wrapup: 
	if (pRefKeyStrm) 
	pRefKeyStrm->Release();

	return hr;
}


// This function is used to retrieve Keys from the stream in the Document. 
// The Keys are to be found in the stream called by the name
// 'c_ReferenceKeyStream':
//
//  hr = pRootStg->OpenStream(c_ReferenceKeyStream, 0, c_grfOpenStrmR, 0, &pRefKeyStrm);
//  if(hr == STG_E_FILENOTFOUND) {
//    // There are no ref keys to load
//    return S_OK;
//  }
//  OnErrorReturn(FAILED(hr), hr);
//
// On successful completion of this method we now have Keys in their persistent
// form, read into memory. The next step after this call would typically be to convert
// them to live pointers. The actual streaming in of the persistent
// key is done via the 'Load' function on the CReferenceKey class (the wrapper for the
// IRxReferenceKey).

HRESULT CReferenceKeyEngine::LoadKeys(IStorage *pRootStg, DWORD hKeyContext, RefKeyVec& refKeyVec)
{
	HRESULT hr=NOERROR;
	RefKeyVec::iterator iter;

	// Validate the input
	//
	OnErrorReturn(!refKeyVec.size(), E_INVALIDARG);
	OnErrorReturn(!hKeyContext, E_INVALIDARG);
	OnErrorReturn(!pRootStg, E_INVALIDARG);
	IStream* pRefKeyStrm=NULL;

	// Open the "ReferenceKeyStream" where we have the keys stored.
	// 
	hr = pRootStg->OpenStream(c_ReferenceKeyStream, 0, c_grfOpenStrmR, 0, &pRefKeyStrm);
	if(hr == STG_E_FILENOTFOUND) 
	{
		// There are no ref keys to load
		return S_OK;
	}
	OnErrorReturn(FAILED(hr), hr);

	// Now load each key. This vector is designed as a fixed length with semantics for the
	// position of each key in it. For example, the second key is the one used by the Measure
	// Edge command. Some of the keys, thus, may be empty and not load up because a particular 
	// command was not used. Load would not return a bad HRESULT, the key class object will remain
	// empty. In this application each key object corresponds to a command that does a selection.  

	for(iter = refKeyVec.begin(); iter != refKeyVec.end(); iter++)
	{
		hr = (*iter).Load(pRefKeyStrm);
		OnError(FAILED(hr), wrapup);
	}

wrapup: 
	if (pRefKeyStrm) 
		pRefKeyStrm->Release(); 

	return hr;
}




