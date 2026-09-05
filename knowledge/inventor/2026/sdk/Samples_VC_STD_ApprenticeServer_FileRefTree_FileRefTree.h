// FileRefTree.h : main header file for the FILEREFTREE application
//

#if !defined(AFX_FILEREFTREE_H__F10C31CC_F90D_11D2_86CA_080009DB6864__INCLUDED_)
#define AFX_FILEREFTREE_H__F10C31CC_F90D_11D2_86CA_080009DB6864__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include <atlbase.h>
#include <map>

/////////////////////////////////////////////////////////////////////////////
// CFileRefTreeApp:
// See FileRefTree.cpp for the implementation of this class
//

class CFileRefTreeApp : public CWinApp
{
public:
	CFileRefTreeApp();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileRefTreeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	// Implementation
	bool visit(CString pathName, ApprenticeServerDocument* spMyRef,
					int nestingLevel, CMapStringToPtr& fileRefMap);

	//{{AFX_MSG(CFileRefTreeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	// For self-initialization by CFileRefTreeDlg:
	INT_PTR NumberOfStrings();
	CString GetString(int i);

private:
	CStringArray m_strings;	// Array of FileRef strings for saving on exit
	void AddString(int nestingLevel, CString string);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEREFTREE_H__F10C31CC_F90D_11D2_86CA_080009DB6864__INCLUDED_)
