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
//----- CmdHandler3.cpp : Implementation of CCmdHandler3
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "CustomUI.h"
#include "CmdHandler3.h"
#include <atlwin.h>

//-----------------------------------------------------------------------------
STDMETHODIMP CCmdHandler3::OnExecute (NameValueMap* context) {

	CWindow win;		
	win.Attach(m_ParentHwnd);
	win.MessageBox(_T("You clicked Command3 button"), _T("Command3 Implementation"));	
	return S_OK;
}