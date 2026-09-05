/*
  DESCRIPTION

  There are two classes defined in this file. The first is a convenience wrapper for
  handling the IRxReferenceKey interface on a BRep object (Face, Edge, Vertex). It provides
  the application a higher-level data item which possesses the knowledge of how to
  handle the streaming out and in of the persistent versions of these pointers. It
  also provides for the ability to hold associated with each 'Key' a piece of 
  application data (in this case, we are holding the Command associated with the
  particular Key). 
  
  The second class is an encapsulation of the overall handling of Reference Key generation
  and handling in various situations such as -- Load, Save, Update, etc. Most importantly,
  it is the encapsulation of what Inventor's calls a KeyContext. The KeyContext can be 
  thought of as a data-structure that aids Inventor in generating Keys more efficiently.
  The KeyContext needs to be stored inside this applications file. In other words, Inventor
  is provided storage into which it writes its KeyContext. A handle (DWORD) is provided
  that stands for KeyContext and each Key-related operation requires the caller to 
  pass in this handle. This way Inventor can service more than one Client at the same
  time, producing keys for them independent of the others and in their own context.

  
  An object of this class is held by the 'controller' Reference File Manager. There 
  is one Reference File Manager per Document.

  This functionality has been encapsulated into this class mainly to separate out
  and highlight the Inventor-related API calls that may need to be made for such
  purposes. This may not be the best way to structure your application though.

  See the corresponding .cpp file for details on the method


  HISTORY

  SAM  :  10/15/99  :  Creation
*/

#ifndef INCLUDED_REFERENCE_KEY_ENGINE_H
#define INCLUDED_REFERENCE_KEY_ENGINE_H

#include <vector>

class CReferenceFile;

class CReferenceKey
{
  public:
    CReferenceKey();
    ~CReferenceKey();

  public:
    void Clean();

  public:  
    const ULONG get_KeySize();
    const BYTE* get_Key();
    HRESULT put_Key(const ULONG keySize, const BYTE* key);

    const IID& get_Type();
    HRESULT put_Type(const IID& iid);

    IRxReferenceKey* get_Object();                 // non-counting
    HRESULT put_Object(IRxReferenceKey *pRefKey);  //counting

    const int get_CommandContext();
    HRESULT put_CommandContext(const int commandContext);

    boolean IsBound();
  
    HRESULT Save(IStream *pStream);
    HRESULT Load(IStream *pStream);

  protected:
    ULONG m_KeySize;
    BYTE *m_Key;  
    IID m_IID;
    IRxReferenceKey *m_pRefKey;
    int m_CommandContext{ 0 };
};




typedef std::vector<CReferenceKey> RefKeyVec;

class CReferenceKeyEngine
{
  public:
    CReferenceKeyEngine();
    ~CReferenceKeyEngine();

  public:
    void Clean();

  public:
    HRESULT _CreateKeyContext(IRxComponentDocument * pDoc);
    HRESULT _LoadKeyContext(IRxComponentDocument * pDoc, IStorage *pRootStg);
  
    HRESULT _ConvertToKeys(RefKeyVec& refKeyVec);
    HRESULT _ConvertToPointer(IRxComponentDocument * pDoc, RefKeyVec& refKeyVec);
  
    HRESULT _SaveKeyContext(IRxComponentDocument * pDoc, IStorage *pRootStg);
    HRESULT _SaveKeys(IStorage *pRootStg, RefKeyVec& refKeyVec);
    HRESULT _LoadKeys(IStorage *pRootStg, RefKeyVec& refKeyVec);


  // Higher level protocol used by the application. This higher level protocol is
  // then implemented in terms of lower level function calls which are really the
  // ones accessing Inventor's API.

  public:
    HRESULT _OnLoadDocument(IStorage *pRootStg, CReferenceFile *i_pReferenceFile, RefKeyVec& refKeyVec);
    HRESULT _OnSaveDocument(IStorage *pRootStg, CReferenceFile *i_pReferenceFile, RefKeyVec& refKeyVec);

    HRESULT _OnPreUpdateDocument(IStorage *pTempStg, CReferenceFile *i_pReferenceFile, RefKeyVec& refKeyVec);
    HRESULT _OnPostUpdateDocument(IStorage *pTempStg, CReferenceFile *i_pReferenceFile, RefKeyVec& refKeyVec);

  // Lower level functions which are the ones implemented utilizing Inventor's API.
  // These functions are not used directly by the rest of the application. It is more
  // convenient for the application to think in terms of a higher level semantics.

  protected:


    HRESULT CreateKeyContext(IRxComponentDocument * pDoc, DWORD *phKeyContext);

    HRESULT ConvertToKeys(DWORD hKeyContext, RefKeyVec& refKeyVec);
    HRESULT ConvertToPointer(IRxComponentDocument * pDoc, DWORD hKeyContext, RefKeyVec& refKeyVec);
  
    HRESULT SaveKeyContext(IRxComponentDocument * pDoc, IStorage *pRootStg, DWORD hKeyContext);
    HRESULT LoadKeyContext(IRxComponentDocument * pDoc, IStorage *pRootStg, DWORD *phKeyContext);

    HRESULT SaveKeys(IStorage *pRootStg, RefKeyVec& refKeyVec);
    HRESULT LoadKeys(IStorage *pRootStg, DWORD hKeyContext, RefKeyVec& refKeyVec);

  protected:
    DWORD m_hKeyContext;
};

#endif