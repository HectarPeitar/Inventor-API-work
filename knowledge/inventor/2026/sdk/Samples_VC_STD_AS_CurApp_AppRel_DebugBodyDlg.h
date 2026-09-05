#if !defined(AFX_DEBUGBODYDLG_H__A4580A73_7B5B_11D3_A472_00C04F6B9531__INCLUDED_)
#define AFX_DEBUGBODYDLG_H__A4580A73_7B5B_11D3_A472_00C04F6B9531__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DebugBodyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDebugBodyDlg dialog

class CDebugBodyDlg : public CDialog
{
// Construction
public:
	CDebugBodyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDebugBodyDlg)
	enum { IDD = IDD_DEBUGBODY_DIALOG };
	CString	m_EdgesCount;
	CString	m_FacesCount;
	CString	m_ShellsCount;
	CString	m_VerticesCount;
	CString	m_Volume;
	CString	m_FileName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDebugBodyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDebugBodyDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEBUGBODYDLG_H__A4580A73_7B5B_11D3_A472_00C04F6B9531__INCLUDED_)
