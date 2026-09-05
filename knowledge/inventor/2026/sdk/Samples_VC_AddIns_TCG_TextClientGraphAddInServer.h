//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted,
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting documentation. 
// <YOUR COMPANY NAME> PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// <YOUR COMPANY NAME> SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE. <YOUR COMPANY NAME>, INC.
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE. 
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable
// 

//-----------------------------------------------------------------------------
//----- TextClientGraphAddInServer.h : Declaration of the CTextClientGraphAddInServer
//-----------------------------------------------------------------------------
#ifndef __TextClientGraphAddInServer_h_
#define __TextClientGraphAddInServer_h_

//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include <eventsdispids.h>

#include "resource.h"

class CButtonDefEvents;

//-----------------------------------------------------------------------------
class ATL_NO_VTABLE CTextClientGraphAddInServer : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTextClientGraphAddInServer, &CLSID_TextClientGraphAddInServer>,
	public IDispatchImpl<ITextClientGraphAddInServer, &IID_ITextClientGraphAddInServer, &LIBID_TextClientGraphLib>	
{
protected:

public:
    CComPtr<Application> m_pApplication ;
	CComPtr<ApplicationAddInSite> m_pAddInSite ;


public:
	CTextClientGraphAddInServer ();
	~CTextClientGraphAddInServer ();

	DECLARE_REGISTRY_RESOURCEID(IDR_TextClientGraphAddInServer)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CTextClientGraphAddInServer)
		COM_INTERFACE_ENTRY(ITextClientGraphAddInServer)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()


	CComPtr<Command> m_AddClientTextCmd ;
	HRESULT AddClientTextCmd () ;


private:
	CComPtr<ButtonDefinitionObject> m_pBtnDef1;
	DWORD m_btnDefCookie1;
	CButtonDefEvents *m_pButtonEvents1;


public:
	void InsertControlsInMenuBars();
	void InsertControlInMenuBar(const CString intEnvName);

	//----- ApplicationAddInServer
	STDMETHOD(Activate)(IDispatch * pDisp, VARIANT_BOOL FirstTime);
	STDMETHOD(Deactivate)();
	STDMETHOD(ExecuteCommand)(long CommandID);
	STDMETHOD(get_Automation)(IDispatch * * ppResult);
} ;

class CButtonDefEvents : public CCmdTarget
{
	DECLARE_DYNCREATE(CButtonDefEvents)

	CButtonDefEvents(){}; 
	CButtonDefEvents(CTextClientGraphAddInServer* pServer, UINT nID); 
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

	CTextClientGraphAddInServer* m_pAddIn{ nullptr };
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
//-----------------------------------------------------------------------------
#endif //----- __TextClientGraphAddInServer_h_
