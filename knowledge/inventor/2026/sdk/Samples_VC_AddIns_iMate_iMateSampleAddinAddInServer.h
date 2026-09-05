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
//----- iMateSampleAddinAddInServer.h : Declaration of the CiMateSampleAddinAddInServer
//-----------------------------------------------------------------------------
#ifndef __iMateSampleAddinAddInServer_h_
#define __iMateSampleAddinAddInServer_h_

//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "resource.h"

//-----------------------------------------------------------------------------
class CButtonDefEvents;

class ATL_NO_VTABLE CiMateSampleAddinAddInServer : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CiMateSampleAddinAddInServer, &CLSID_iMateSampleAddinAddInServer>,
	public IDispatchImpl<IiMateSampleAddinAddInServer, &IID_IiMateSampleAddinAddInServer, &LIBID_iMateSampleAddinLib>	
{
public:
	CiMateSampleAddinAddInServer();
	~CiMateSampleAddinAddInServer();

	DECLARE_REGISTRY_RESOURCEID(IDR_iMateSampleAddinAddInServer)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CiMateSampleAddinAddInServer)
		COM_INTERFACE_ENTRY(IiMateSampleAddinAddInServer)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	HRESULT PlaceUsingiMatesCmd () ;
	HRESULT AddConstraintsFromiMatesCmd () ;
	HRESULT CreateConstraintFromiMateAndEntityCmd () ;

	//----- ApplicationAddInServer
	STDMETHOD(Activate)(IDispatch * pDisp, VARIANT_BOOL FirstTime);
	STDMETHOD(Deactivate)();
	STDMETHOD(ExecuteCommand)(long CommandID);
	STDMETHOD(get_Automation)(IDispatch * * ppResult);

	// helper functions
	HRESULT GetFilePath(CString& FilePath);

protected:
	void CreateCommands();

private:
	CComPtr<Application> m_pApplication ;
	CComPtr<ApplicationAddInSite> m_pAddInSite ;

	CButtonDefEvents* m_pButtonEvents1{ nullptr };
	CButtonDefEvents* m_pButtonEvents2{ nullptr };
	CButtonDefEvents* m_pButtonEvents3{ nullptr };

	CComPtr<ButtonDefinitionObject> m_pBtnDef1;
	CComPtr<ButtonDefinitionObject> m_pBtnDef2;
	CComPtr<ButtonDefinitionObject> m_pBtnDef3;

	DWORD m_btnDefCookie1, m_btnDefCookie2, m_btnDefCookie3;
} ;

class CButtonDefEvents : public CCmdTarget
{
	DECLARE_DYNCREATE(CButtonDefEvents)

	CButtonDefEvents(){}; 
	CButtonDefEvents(CiMateSampleAddinAddInServer* pServer, UINT nID); 
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

	CiMateSampleAddinAddInServer* m_pAddIn{ nullptr };
	UINT m_nID{0};
	
	HRESULT OnExecuteEvent(NameValueMap* context);

	// Generated message map functions
	//{{AFX_MSG(CButtonDefEvents)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

//-----------------------------------------------------------------------------
#endif //----- __iMateSampleAddinAddInServer_h_
