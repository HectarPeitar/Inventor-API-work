#if !defined(AFX_SIMPLEMFCCONTROL_H__F0EBED6D_8FFB_42C4_9FA3_8DC4177A13E4__INCLUDED_)
#define AFX_SIMPLEMFCCONTROL_H__F0EBED6D_8FFB_42C4_9FA3_8DC4177A13E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// SIMPLEMFCCONTROL.h : main header file for SIMPLEMFCCONTROL.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSIMPLEMFCCONTROLApp : See SIMPLEMFCCONTROL.cpp for implementation.

class CSIMPLEMFCCONTROLApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEMFCCONTROL_H__F0EBED6D_8FFB_42C4_9FA3_8DC4177A13E4__INCLUDED)
