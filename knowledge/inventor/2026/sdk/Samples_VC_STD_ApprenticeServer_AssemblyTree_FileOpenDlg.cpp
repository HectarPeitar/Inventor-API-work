// FileOpenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AssemblyTree.h"
#include "FileOpenDlg.h"


// CFileOpenDlg

IMPLEMENT_DYNAMIC(CFileOpenDlg, CFileDialog)
CFileOpenDlg::CFileOpenDlg(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}

CFileOpenDlg::~CFileOpenDlg()
{
}


BEGIN_MESSAGE_MAP(CFileOpenDlg, CFileDialog)
END_MESSAGE_MAP()



// CFileOpenDlg message handlers

