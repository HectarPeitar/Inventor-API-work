// ApprenticeViewerMDI.h : main header file for the APPRENTICEVIEWERMDI application
//

#if !defined(AFX_APPRENTICEVIEWERMDI_H__7AA3F6F0_A494_4151_A298_B941072E15AD__INCLUDED_)
#define AFX_APPRENTICEVIEWERMDI_H__7AA3F6F0_A494_4151_A298_B941072E15AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CApprenticeViewerMDIApp:
// See ApprenticeViewerMDI.cpp for the implementation of this class
//

class CApprenticeViewerMDIApp : public CWinApp
{
public:
	CApprenticeViewerMDIApp();
	~CApprenticeViewerMDIApp();
	
	CComPtr<ApprenticeServer> GetApprenticeServer();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CApprenticeViewerMDIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CApprenticeViewerMDIApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CComPtr<ApprenticeServer>	m_pApprenticeServer;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPRENTICEVIEWERMDI_H__7AA3F6F0_A494_4151_A298_B941072E15AD__INCLUDED_)
