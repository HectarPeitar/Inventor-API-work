#if !defined(AFX_SIMPLEMFCCONTROLPPG_H__E291F5DB_78CC_44E1_816B_0689320FFA51__INCLUDED_)
#define AFX_SIMPLEMFCCONTROLPPG_H__E291F5DB_78CC_44E1_816B_0689320FFA51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// SIMPLEMFCCONTROLPpg.h : Declaration of the CSIMPLEMFCCONTROLPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROLPropPage : See SIMPLEMFCCONTROLPpg.cpp.cpp for implementation.

class CSIMPLEMFCCONTROLPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CSIMPLEMFCCONTROLPropPage)
	DECLARE_OLECREATE_EX(CSIMPLEMFCCONTROLPropPage)

// Constructor
public:
	CSIMPLEMFCCONTROLPropPage();

// Dialog Data
	//{{AFX_DATA(CSIMPLEMFCCONTROLPropPage)
	enum { IDD = IDD_PROPPAGE_SIMPLEMFCCONTROL };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CSIMPLEMFCCONTROLPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEMFCCONTROLPPG_H__E291F5DB_78CC_44E1_816B_0689320FFA51__INCLUDED)
