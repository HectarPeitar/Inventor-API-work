// AssemblyTreeDlg.h : header file
//

#pragma once
#include "afxcmn.h"


// CAssemblyTreeDlg dialog
class CAssemblyTreeDlg : public CDialog
{
// Construction
public:
	CAssemblyTreeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ASSEMBLYTREE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBrowsebutton();
	afx_msg void OnBnClickedClosebutton();
	afx_msg void OnBnClickedRefreshtreeButton();

private:
	CString m_strFileName_EditBox;
	CImageList m_ImageList;
	CTreeCtrl m_Assembly_TreeCtrl;

	HRESULT GetAssemblyTree();
	HRESULT GetOccurrences(ComponentOccurrences* pCompOccs, HTREEITEM htritmTopNode );


};
