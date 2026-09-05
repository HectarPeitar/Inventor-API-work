#pragma once


// CFileOpenDlg

class CFileOpenDlg : public CFileDialog
{
	DECLARE_DYNAMIC(CFileOpenDlg)

public:
	CFileOpenDlg(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);
	virtual ~CFileOpenDlg();

protected:
	DECLARE_MESSAGE_MAP()
};


