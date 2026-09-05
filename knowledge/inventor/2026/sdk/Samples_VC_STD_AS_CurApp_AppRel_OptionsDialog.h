#if !defined(AFX_OPTIONSDIALOG_H__0CED148F_7C4D_11D3_AE4C_00C04F681329__INCLUDED_)
#define AFX_OPTIONSDIALOG_H__0CED148F_7C4D_11D3_AE4C_00C04F681329__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog dialog

class COptionsDialog : public CDialog
{
// Construction
public:
	COptionsDialog(CWnd* pParent = NULL);   // standard constructor

  // Accessors
  BOOL IsShadedDisplayOn() const;
  BOOL IsEdgeDisplayOn() const;
	double GetChordalHeightTolerance() const;
  UINT GetSelectionTolerance() const;

  // Mutators
  void SetShadedDisplay(BOOL bOn);
  void SetEdgeDisplay(BOOL bOn);
  void SetChordalHeightTolerance(double tol) { m_chordHtTol = tol; }
  void SetSelectionTolerance(UINT tol) { m_selectionTolerance = tol; }

// Dialog Data
	//{{AFX_DATA(COptionsDialog)
	enum { IDD = IDD_OPTIONS_DIALOG };
	double	m_chordHtTol{0.0};
	BOOL	m_shadedChecked;
	BOOL	m_edgeChecked;
	UINT	m_selectionTolerance{0};
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsDialog)
	afx_msg void OnShadedCheckClick();
  afx_msg void OnEdgeCheckClick();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSDIALOG_H__0CED148F_7C4D_11D3_AE4C_00C04F681329__INCLUDED_)
