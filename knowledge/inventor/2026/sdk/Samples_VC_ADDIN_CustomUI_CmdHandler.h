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
//----- CmdHandler.h : Declaration of the CCmdHandler
//-----------------------------------------------------------------------------
#ifndef _CmdHandler_h_
#define _CmdHandler_h_

#include "resource.h"

//using namespace Inventor;

//-----------------------------------------------------------------------------
class ATL_NO_VTABLE CCmdHandler : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispEventImpl<0, CCmdHandler, &DIID_ButtonDefinitionSink, &LIBID_Inventor, 1, 0>
{

protected:
	HWND	m_ParentHwnd;
	CComPtr<ButtonDefinitionObject> m_pBtnDef;	

public:
	CCmdHandler () {
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CCmdHandler)
	END_COM_MAP()

public:

	//----- ICmdHandler

	//----- ButtonDefinitionSink
	STDMETHOD(OnExecute) (NameValueMap* context) = 0;

	BEGIN_SINK_MAP(CCmdHandler)
		SINK_ENTRY_EX (0, DIID_ButtonDefinitionSink, ButtonDefinitionSink_OnExecuteMeth, OnExecute)
	END_SINK_MAP()

	//----- Non-COM protocol
	//
	HRESULT CreateButtonDefinition(Application* pApplication, 
									BSTR bstrDisplayName, 
									BSTR bstrInternalName, 
									CommandTypesEnum eCommandType, 
									VARIANT varClientId, 
									BSTR bstrDescription, 
									BSTR bstrToolTip, 
									int StandardIconResId, 
									int LargeIconResId, 
									ButtonDisplayEnum eButtonDisplayType);

	HRESULT GetButtonDefinition(ButtonDefinitionObject** pBtnDef);

	HRESULT Cleanup();
} ;

//-----------------------------------------------------------------------------
#endif //----- _CmdHandler_h_
