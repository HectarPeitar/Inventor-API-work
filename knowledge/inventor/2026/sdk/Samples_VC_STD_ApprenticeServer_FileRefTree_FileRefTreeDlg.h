// FileRefTreeDlg.h : header file
//

#if !defined(AFX_FILEREFTREEDLG_H__F10C31CE_F90D_11D2_86CA_080009DB6864__INCLUDED_)
#define AFX_FILEREFTREEDLG_H__F10C31CE_F90D_11D2_86CA_080009DB6864__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFileRefTreeDlg dialog

class CFileRefTreeApp;

class CFileRefTreeDlg : public CDialog
{
// Construction
public:
	CFileRefTreeDlg(CFileRefTreeApp* pApp);

// Dialog Data
	//{{AFX_DATA(CFileRefTreeDlg)
	enum { IDD = IDD_FILEREFTREE_DIALOG };
	CListBox	m_listBox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileRefTreeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

public:
// Implementation
	
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFileRefTreeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CFileRefTreeApp* m_pApp{ nullptr };
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEREFTREEDLG_H__F10C31CE_F90D_11D2_86CA_080009DB6864__INCLUDED_)
