/*
  DESCRIPTION

  This file contains the declaration of the class that defines the COM-object that
  supports the call-back (or outgoing, from Inventor's point of view) interface, using
  which Inventor communicates details of interesting events taking place, to this Client.

*/

#ifndef _RXAPPEVENTHNDLR_
#define _RXAPPEVENTHNDLR_

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "unknown.h"

class CRxInsertCatalogPart;

class CRxAppEventHandler : public CUnknown, public IRxApplicationEvents
{
  // The IUnknown implementation is handled largely by CUnknown. We only have to re-direct the methods
  // by including the following macro. The QueryInterface gets implemented by this class overiding
  // the InternalQueryInterface.

public:
    DECLARE_UNKNOWN;
    HRESULT InternalQueryInterface (REFIID iid, void **ppv);
  
  // Private data and public accessors
private:
    CRxInsertCatalogPart *m_pInsertCatalogPart;

    CComPtr<IUnknown>m_pApplicationEvents;
    DWORD m_dwApplicationEventsCookie;
  
  // Constructor(s), initializers and destructor
public:
    CRxAppEventHandler (CRxInsertCatalogPart *pInsertCatalogPart);
    ~CRxAppEventHandler();

  // Helper functions
public:
    // Allows objects within this DLL to connect to the Application Event source
    HRESULT Connect(Application *pApplication);

    // Allows objects within this DLL to disconnect from the Application Event source
    HRESULT Disconnect();

public:
    // IRxApplicationEvents

    virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnNewDocument( 
        /* [in] */ Document	__RPC_FAR *DocumentObject);
    
    virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnOpenDocument( 
        /* [in] */ Document	__RPC_FAR *DocumentObject);
    
    virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnSaveDocument( 
        /* [in] */ Document	__RPC_FAR *DocumentObject,
        /* [in] */ /* external definition not present */ EventTimingEnum BeforeOrAfter);
            
    virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnCloseDocument( 
        /* [in] */ Document	__RPC_FAR *DocumentObject,
        /* [in] */ /* external definition not present */ EventTimingEnum BeforeOrAfter);

    virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnActivateDocument( 
        /* [in] */ Document	__RPC_FAR *DocumentObject);
    
    virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnDeactivateDocument( 
        /* [in] */ Document	__RPC_FAR *DocumentObject);
    
    virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnNewView( 
        /* [in] */ View	__RPC_FAR *ViewObject);
    
    virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnCloseView( 
        /* [in] */ View	__RPC_FAR *ViewObject);
    
    virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnActivateView( 
        /* [in] */ View	__RPC_FAR *ViewObject);
    
    virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnDeactivateView( 
        /* [in] */ View	__RPC_FAR *ViewObject);
    
    virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnQuit();
};

#endif 
