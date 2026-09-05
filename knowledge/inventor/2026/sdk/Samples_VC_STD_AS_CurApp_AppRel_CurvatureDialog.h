#if !defined(AFX_CURVATUREDIALOG_H__98DBB56A_907D_11D3_AE4F_00C04F681329__INCLUDED_)
#define AFX_CURVATUREDIALOG_H__98DBB56A_907D_11D3_AE4F_00C04F681329__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CurvatureDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCurvatureDialog dialog

class CCurvatureDialog : public CDialog
{
// Construction
public:
	CCurvatureDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCurvatureDialog)
	enum { IDD = IDD_CURVATURE_DIALOG };
	CString	m_curvatureType;
	UINT	m_uDensity{0};
	UINT	m_vDensity{0};
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurvatureDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCurvatureDialog)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVATUREDIALOG_H__98DBB56A_907D_11D3_AE4F_00C04F681329__INCLUDED_)
