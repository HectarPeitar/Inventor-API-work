//-----------------------------------------------------------------------------
//----- CustomCommandApp.h
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
class CCustomCommandApp : public CWinApp
{

public:
	//{{AFX_VIRTUAL(CCustomCommandApp)
	public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CCustomCommandApp)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
} ;
