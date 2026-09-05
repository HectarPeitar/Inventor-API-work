/*
  DESCRIPTION

  This file contains the declaration of the class that defines the COM-object with which
  Autodesk Inventor (R) first communicates (supports the IRxApplicationAddInServer interface).

*/

#ifndef _RXClientGraphics_
#define _RXClientGraphics_

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "Unknown.h"
#include "Resource.h"
#include <map>

class CButtonDefEvents;

class CRxClientGraphics : public CUnknown, public IRxApplicationAddInServer
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
	COleVariant				m_clientIdVariant;
	CComBSTR				m_clientId;

	CComPtr<Document>			m_rCurrentDoc;			// The active document
	CComQIPtr<GraphicsDataSets>	m_rGraphicsDataSets;	// Our graphics data set in the active document
	CComPtr<ClientGraphics>		m_rClientGraphics;		// Our client graphics for the document
	std::map<long, CComBSTR>	m_commandMap;			// Maps command ids to command strings
	
	HRESULT TransformGroups();
	HRESULT DrawSquares();
	HRESULT DrawVonKoch();
	HRESULT DrawCircle();
	HRESULT DrawSharedCoords();
	HRESULT DrawCylinder();
	HRESULT DrawGraphicsStrips();
	HRESULT DrawSymbol();
	HRESULT ClearAll();
	HRESULT ShowGraphics(bool show);		
	HRESULT RedrawActive();

	void CreateCommands();
		
    CButtonDefEvents* m_pButtonEvents1{ nullptr };
	CButtonDefEvents* m_pButtonEvents2{ nullptr };
	CButtonDefEvents* m_pButtonEvents3{ nullptr };
	CButtonDefEvents* m_pButtonEvents4{ nullptr };
	CButtonDefEvents* m_pButtonEvents5{ nullptr };
	CButtonDefEvents* m_pButtonEvents6{ nullptr };
	CButtonDefEvents* m_pButtonEvents7{ nullptr };
	CButtonDefEvents* m_pButtonEvents8{ nullptr };
	CButtonDefEvents* m_pButtonEvents9{ nullptr };
	CButtonDefEvents* m_pButtonEvents10{ nullptr };
	CButtonDefEvents* m_pButtonEvents11{ nullptr };
	
	ButtonDefinitionObjectPtr m_pBtnDef1;
	ButtonDefinitionObjectPtr m_pBtnDef2;
	ButtonDefinitionObjectPtr m_pBtnDef3;
	ButtonDefinitionObjectPtr m_pBtnDef4;
	ButtonDefinitionObjectPtr m_pBtnDef5;
	ButtonDefinitionObjectPtr m_pBtnDef6;
	ButtonDefinitionObjectPtr m_pBtnDef7;
	ButtonDefinitionObjectPtr m_pBtnDef8;
	ButtonDefinitionObjectPtr m_pBtnDef9;
	ButtonDefinitionObjectPtr m_pBtnDef10;
	ButtonDefinitionObjectPtr m_pBtnDef11;

	DWORD m_btnDefCookie1;
	DWORD m_btnDefCookie2;
	DWORD m_btnDefCookie3;
	DWORD m_btnDefCookie4;
	DWORD m_btnDefCookie5;
	DWORD m_btnDefCookie6;
	DWORD m_btnDefCookie7;
	DWORD m_btnDefCookie8;
	DWORD m_btnDefCookie9;
	DWORD m_btnDefCookie10;
	DWORD m_btnDefCookie11;

  public:
    // Return the Autodesk Inventor (R) Add-In Site of this object's attachment. Do NOT Release().
    IRxApplicationAddInSite *Site()
     { return m_pSite; }

    // Return the Autodesk Inventor (R) Application. Do NOT Release().
    Application *Application()
     { return m_pApplication; }

  
  // Constructor(s), initializers and destructor

  public:
    CRxClientGraphics ();
    ~CRxClientGraphics();

  
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
	CButtonDefEvents(CRxClientGraphics* pServer, UINT nID); 
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

	CRxClientGraphics* m_pAddIn{ nullptr };
	UINT m_nID{0};
	
	void OnExecuteEvent(NameValueMap *context);
	
	// Generated message map functions
	//{{AFX_MSG(CButtonDefEvents)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

#endif 

