/*
  DESCRIPTION

  This file contains the declaration of the class that defines the COM-object with which
  Autodesk Inventor (R) first communicates (supports the IRxApplicationAddInServer interface).

*/

#ifndef _RXSampleCommand_
#define _RXSampleCommand_

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "unknown.h"
#include "resource.h"
#include "eventhandler.h"
#include "patternsketch.h"

class CButtonDefEvents;
class ReplicateWorkplaneCmd;


class CRxSampleCommand : public CUnknown, public IRxApplicationAddInServer
{
  // The IUnknown implementation is handled largely by CUnknown. We only have to re-direct the methods
  // by including the following macro. The QueryInterface gets implemented by this class overiding
  // the InternalQueryInterface.

  public:
    DECLARE_UNKNOWN;
    HRESULT InternalQueryInterface (REFIID iid, void **ppv);

  
  // Private data and public accessors

  private:
    CComPtr<IRxApplicationAddInSite> m_pSite;
    CComPtr<Application> m_pApplication;

    CButtonDefEvents* m_pButtonEvents1{ nullptr };
	CButtonDefEvents* m_pButtonEvents2{ nullptr };
	
	ButtonDefinitionObjectPtr m_pBtnDef1;
	ButtonDefinitionObjectPtr m_pBtnDef2;
	
	DWORD m_btnDefCookie1, m_btnDefCookie2;

	PatternSketchCmd* m_pPatternSketchCmd{ nullptr };
	ReplicateWorkplaneCmd* m_pReplicateWorkplaneCmd{ nullptr };

	void CreateCommands();


  public:
    // Return the Autodesk Inventor (R) Add-In Site of this object's attachment. Do NOT Release().
    IRxApplicationAddInSite *Site()
     { return m_pSite; }

    // Return the Autodesk Inventor (R) Application. Do NOT Release().
    Application *Application()
     { return m_pApplication; }

  
  // Constructor(s), initializers and destructor

  public:
     CRxSampleCommand ();
    ~CRxSampleCommand();
  
  // Interface(s) supported by this object

  public:

    // IRxApplicationAddInSite

    virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Activate( 
        /* [in] */ IRxApplicationAddInSite __RPC_FAR *pAddInSite,
        /* [in] */ BooleanType bFirstTime);
    
    virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Deactivate( void);

    virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ExecuteCommand( 
        long CommandID);

    virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Automation( 
        /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);
};

class CButtonDefEvents : public CCmdTarget
{
	DECLARE_DYNCREATE(CButtonDefEvents)

	CButtonDefEvents(){}; 
	CButtonDefEvents(CRxSampleCommand* pServer, UINT nID); 
	virtual ~CButtonDefEvents();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonDefEvents)
	//}}AFX_VIRTUAL

// Implementation
protected:

	CRxSampleCommand* m_pAddIn{ nullptr };
	UINT m_nID{0};
	
	void OnExecuteEvent(NameValueMap* context);

	// Generated message map functions
	//{{AFX_MSG(CButtonDefEvents)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


#endif 
