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
//----- loftWithRailingsAddInServer.h : Declaration of the CloftWithRailingsAddInServer
//-----------------------------------------------------------------------------
#ifndef __loftWithRailingsAddInServer_h_
#define __loftWithRailingsAddInServer_h_

//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include <eventsdispids.h>

#include "resource.h"

class CButtonDefEvents;

//-----------------------------------------------------------------------------
class ATL_NO_VTABLE CloftWithRailingsAddInServer : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CloftWithRailingsAddInServer, &CLSID_loftWithRailingsAddInServer>,
	public IDispatchImpl<IloftWithRailingsAddInServer, &IID_IloftWithRailingsAddInServer, &LIBID_loftWithRailingsLib>	
{
protected:
	//{{AFX_INV_VARS_EVENT(CloftWithRailingsAddInServer)
	//}}AFX_INV_VARS_EVENT

public:

	CComPtr<Application> m_pApplication ;
	CComPtr<ApplicationAddInSite> m_pAddInSite ;

	//{{AFX_INV_VARS_DECL(CloftWithRailingsAddInServer)
	//}}AFX_INV_VARS_DECL

public:

	DECLARE_REGISTRY_RESOURCEID(IDR_loftWithRailingsAddInServer)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CloftWithRailingsAddInServer)
		COM_INTERFACE_ENTRY(IloftWithRailingsAddInServer)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	//{{AFX_INV_CMDS_DECL(CloftWithRailingsAddInServer)
	CComPtr<Command> m_loftCmd ;
	HRESULT loftCmd () ;
	//}}AFX_INV_CMDS_DECL
	 CloftWithRailingsAddInServer ();

private:
	CComPtr<ButtonDefinitionObject> m_pBtnDef1;
	DWORD m_btnDefCookie1;
	CButtonDefEvents *m_pButtonEvents1;

	void InsertControlsInMenuBars();
	void InsertControlInMenuBar(const CString intEnvName);


public:
	//----- ApplicationAddInServer
	STDMETHOD(Activate)(IDispatch * pDisp, VARIANT_BOOL FirstTime);
	STDMETHOD(Deactivate)();
	STDMETHOD(ExecuteCommand)(long CommandID);
	STDMETHOD(get_Automation)(IDispatch * * ppDisp);
} ;

class CButtonDefEvents : public CCmdTarget
{
	DECLARE_DYNCREATE(CButtonDefEvents)

	CButtonDefEvents(){}; 
	CButtonDefEvents(CloftWithRailingsAddInServer* pServer, UINT nID); 
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

	CloftWithRailingsAddInServer* m_pAddIn{ nullptr };
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

	//-----------------------------------------------------------------------------
#endif //----- __loftWithRailingsAddInServer_h_
