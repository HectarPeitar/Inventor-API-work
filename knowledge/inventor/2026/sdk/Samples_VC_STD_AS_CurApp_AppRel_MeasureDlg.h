#if !defined(AFX_MEASUREDLG_H__873BD0F0_8BEA_11D3_B7F7_0060B0EC020B__INCLUDED_)
#define AFX_MEASUREDLG_H__873BD0F0_8BEA_11D3_B7F7_0060B0EC020B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MeasureDlg.h : header file
//

#include "../resource.h"

/////////////////////////////////////////////////////////////////////////////
// CMeasureDlg dialog

class CMeasureDlg : public CDialog
{
// Construction
public:
	CMeasureDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMeasureDlg)
	enum { IDD = IDD_MEASURE_DIALOG };
	CString	m_MeasureValue;
	CString	m_MeasureProperty;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeasureDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMeasureDlg)
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEASUREDLG_H__873BD0F0_8BEA_11D3_B7F7_0060B0EC020B__INCLUDED_)
