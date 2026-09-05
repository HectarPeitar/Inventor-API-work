// IDWViewer.h : main header file for the IDWViewer application
//

#if !defined(AFX_IDWViewer_H__F98FA8D0_ACE5_11D3_A478_00C04F6B9531__INCLUDED_)
#define AFX_IDWViewer_H__F98FA8D0_ACE5_11D3_A478_00C04F6B9531__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CIDWViewerApp:
// See IDWViewer.cpp for the implementation of this class
//

class CIDWViewerApp : public CWinApp
{
public:
	CIDWViewerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIDWViewerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
  BOOL SelfRegisteration(LPCTSTR szCmd);
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CIDWViewerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



class InventorLocation
{
public:
    InventorLocation() {
      m_bPathsInitialized = false;
      _tcscpy_s(m_szSupportPaths,_MAX_PATH,_T(""));
      _tcscpy_s(m_szCompatibilityPath,_MAX_PATH,_T(""));
      _tcscpy_s(m_szMDT_OE_Path,_MAX_PATH,_T(""));
    }
  HRESULT GetInventorCompatibilityLocation(LPTSTR szLocation);
  bool GetCompatibilityFilePath(LPTSTR szFileName, LPTSTR szBuffer);
  bool GetMDT_OE_FilePath(LPTSTR szFileName, LPTSTR szBuffer);
  bool IsIDWRegistered();
  bool IsInventorRegistered(HINSTANCE hInstance);

  static InventorLocation g_Location;

protected:
  void InitializePaths();
private:
  // This has to be long enough to hold 4 paths separated by ";"
  TCHAR m_szSupportPaths[_MAX_PATH+_MAX_PATH+_MAX_PATH+_MAX_PATH+8];
  TCHAR m_szCompatibilityPath[_MAX_PATH];
  TCHAR m_szMDT_OE_Path[_MAX_PATH];
  bool m_bPathsInitialized{false};
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IDWViewer_H__F98FA8D0_ACE5_11D3_A478_00C04F6B9531__INCLUDED_)
