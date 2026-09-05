// RefBoxApp.h : main header file for the REFBOXAPP application
//

#if !defined(AFX_REFBOXAPP_H__B4B9ABC3_6F88_11D3_AE45_00C04F681329__INCLUDED_)
#define AFX_REFBOXAPP_H__B4B9ABC3_6F88_11D3_AE45_00C04F681329__INCLUDED_

#ifdef REFBOXAPP
#define REFBOXAPP_EXPORT __declspec(dllexport) 
#else
#define REFBOXAPP_EXPORT 
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCurvatureApp:
// See RefBoxApp.cpp for the implementation of this class
//

class CCurvatureApp : public CWinApp
{
public:
	CCurvatureApp();
	~CCurvatureApp();

protected:
	bool m_bInitialized{false};

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurvatureApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCurvatureApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REFBOXAPP_H__B4B9ABC3_6F88_11D3_AE45_00C04F681329__INCLUDED_)
