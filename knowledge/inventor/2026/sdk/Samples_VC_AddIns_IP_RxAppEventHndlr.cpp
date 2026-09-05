/*
  DESCRIPTION

  This file contains the implementation of the class that defines the call-back interface
  to Inventor.

*/

#include "stdafx.h"
#include <sys/stat.h>
#include <io.h>

#include "rxappeventhndlr.h"

#include "rxinsertcatalogpart.h"

/*--------------------- IUnknown-interface related implementation  --------------------------------*/

/*
 * All of the standard IUnknown interfaces are taken care of in the CUnknown
 * class. The implementation in the CUnknown class relies on this override that
 * should end up looking like a non-delegating QueryInterface, except for the fact that QI
 * for the IUnknown is also taken care of by CUnknown (control will never reach here if
 * QI-ed for IUnknown).
 */

HRESULT CRxAppEventHandler::InternalQueryInterface (REFIID riid, void **ppv)
{
	HRESULT Result = NOERROR;

	OnErrorState (!ppv, Result, E_INVALIDARG, wrapup);
	*ppv = NULL;

	if (IsEqualIID (riid, __uuidof (IRxApplicationEvents)))
		*ppv = static_cast<void *> (static_cast<IRxApplicationEvents *> (this));
	else
		Result = E_NOINTERFACE;

	if (SUCCEEDED (Result))
		((LPUNKNOWN)*ppv)->AddRef();

wrapup:          
  return (Result);
}

/*---------------------- Constructor(s), initializers and destructor ---------------------------------*/

CRxAppEventHandler::CRxAppEventHandler (CRxInsertCatalogPart *pInsertCatalogPart) : CUnknown (NULL)
{ 
	m_pInsertCatalogPart = pInsertCatalogPart;
	m_pApplicationEvents = NULL;
	m_dwApplicationEventsCookie = 0;
}

CRxAppEventHandler::~CRxAppEventHandler()
{
	if (m_pApplicationEvents)
		m_pApplicationEvents=NULL;
}

/*---------------------- IRxApplicationEvents interface ---------------------------------*/
    
HRESULT CRxAppEventHandler::OnNewDocument (Document	*DocumentObject)
{
	return NOERROR;
}

HRESULT CRxAppEventHandler::OnOpenDocument (Document *DocumentObject)
{
	return NOERROR;
}
                
HRESULT CRxAppEventHandler::OnSaveDocument (Document *DocumentObject, EventTimingEnum BeforeOrAfter)
{
	return NOERROR;
}

HRESULT CRxAppEventHandler::OnCloseDocument (Document *DocumentObject, EventTimingEnum BeforeOrAfter)
{  
	return NOERROR;
}
        
HRESULT CRxAppEventHandler::OnActivateDocument (Document *DocumentObject)
{
	if (m_pInsertCatalogPart)
		m_pInsertCatalogPart->HandleDocumentActivation (DocumentObject);

	return NOERROR;
}
        
HRESULT CRxAppEventHandler::OnDeactivateDocument (Document *DocumentObject)
{
	return NOERROR;
}
        
HRESULT CRxAppEventHandler::OnNewView (View *ViewObject)
{
	return NOERROR;
}
        
HRESULT CRxAppEventHandler::OnCloseView (View	*ViewObject)
{
	return NOERROR;
}
        
HRESULT CRxAppEventHandler::OnActivateView (View *ViewObject)
{
	return NOERROR;
}
        
HRESULT CRxAppEventHandler::OnDeactivateView (View *ViewObject)
{
	return NOERROR;
}
        
HRESULT CRxAppEventHandler::OnQuit ()
{
	return NOERROR;
}

//---------------------------- Helper Methods ---------------------------------------//

HRESULT CRxAppEventHandler::Connect (Application *pApplication)
{
	HRESULT Result = NOERROR; 
	CComPtr<IConnectionPointContainer> pCPC;
	CComPtr<IConnectionPoint> pCP ;

	OnErrorReturn (!pApplication, E_INVALIDARG);

	Result = pApplication->get_ApplicationEvents ((ApplicationEventsObject**)&m_pApplicationEvents);
	OnError (FAILED (Result), wrapup);

	Result = m_pApplicationEvents->QueryInterface (IID_IConnectionPointContainer, (void **) &pCPC);
	OnError (FAILED (Result), wrapup);

	Result = pCPC->FindConnectionPoint (IID_IRxApplicationEvents, &pCP);
	OnError (FAILED (Result), wrapup);

	Result = pCP->Advise (m_pUnkOuter, &m_dwApplicationEventsCookie);
	OnError (FAILED (Result), wrapup);

wrapup:
	return Result;
}

HRESULT CRxAppEventHandler::Disconnect()
{
	HRESULT Result = NOERROR;
	CComPtr<IConnectionPointContainer> pCPC;
	CComPtr<IConnectionPoint> pCP ;

	OnErrorReturn (!m_pApplicationEvents, E_POINTER);

	Result = m_pApplicationEvents->QueryInterface (IID_IConnectionPointContainer, (void **) &pCPC);
	OnError (FAILED (Result), wrapup);

	Result = pCPC->FindConnectionPoint (IID_IRxApplicationEvents, &pCP);
	OnError (FAILED (Result), wrapup);

	Result = pCP->Unadvise (m_dwApplicationEventsCookie);
	OnError (FAILED (Result), wrapup);

wrapup:
	return Result;
}

