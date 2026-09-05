// IDWxView.cpp : implementation file
//

#include "stdafx.h"
#include "IDWViewer.h"
#include "IDWxView.h"

#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// IDWxView

IMPLEMENT_DYNCREATE(IDWxView, CFormView)

IDWxView::IDWxView()
	: CFormView((LPTSTR) NULL)
{
	//{{AFX_DATA_INIT(IDWxView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bViewerAvailable = false;

	HRESULT Result = m_spApp.CoCreateInstance(CLSID_ApprenticeServerComponent);
}

IDWxView::~IDWxView()
{
	// TBD: delete the temporary DWF file
	if (m_spApp)
	{
		m_spApp->Close();
		m_spApp = NULL;
	}
}

void IDWxView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(IDWxView)
	DDX_Control(pDX, IDC_ADVIEWER2, m_AvView);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(IDWxView, CFormView)
	//{{AFX_MSG_MAP(IDWxView)
	ON_COMMAND(ID_EDIT_REFRESH, OnEditRefresh)
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_OPEN, OnFileView)
	ON_WM_SIZE()
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_CBN_SELCHANGE(IDC_SHEETLIST, OnEditchangeSheetlist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// IDWxView diagnostics

#ifdef _DEBUG
void IDWxView::AssertValid() const
{
	CFormView::AssertValid();
}

void IDWxView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


void IDWxView::OnDestroy()
{
}

void IDWxView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	if (::IsWindow(m_AvView.m_hWnd))
	{
		// need to push non-client borders out of the client area
		CRect rect;
		GetClientRect(rect);
		::AdjustWindowRectEx(rect,
			m_AvView.GetStyle(), FALSE, WS_EX_CLIENTEDGE);
		m_AvView.SetWindowPos(NULL, rect.left, rect.top,
			rect.Width(), rect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

/////////////////////////////////////////////////////////////////////////////
// IDWxView operations

BOOL IDWxView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
						DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
						UINT nID, CCreateContext* pContext)
{
	// create the view window itself
	m_pCreateContext = pContext;
	if (!CView::Create(lpszClassName, lpszWindowName,
				dwStyle, rect, pParentWnd,  nID, pContext))
	{
		return FALSE;
	}

	AfxEnableControlContainer();

	RECT rectClient;
	GetClientRect(&rectClient);

	CLSID clsid;
	LPOLESTR lpsz = _T("{A662DA7E-CCB7-4743-B71A-D817F6D575DF}"); // CLSID for DWF Viewer control
	HRESULT hr  = CLSIDFromString(lpsz,  //Pointer to the string representation of the CLSID
	                        &clsid);  //Pointer to the CLSID

	// create the control window
	// AFX_IDW_PANE_FIRST is a safe but arbitrary ID
	if (!m_AvView.CreateControl(clsid, lpszWindowName,
				WS_VISIBLE | WS_CHILD, rectClient, this, AFX_IDW_PANE_FIRST))
	{
		// DWF Viewer ActiveX control not found, but that does not let us stop
		return TRUE;
	}
	m_DialogBar.Create(GetParentFrame(), IDD_SHEETS, CBRS_TOP, IDD_SHEETS);
	m_DialogBar.EnableWindow(FALSE);
	m_bViewerAvailable = true;
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// IDWxView message handlers

void IDWxView::OnEditRefresh()
{
	if(m_bViewerAvailable)
	{
		CDocument * pDoc = GetDocument();
		CString strFile = pDoc->GetPathName();
		m_AvView.SetSourcePath(strFile);
	}
}

void IDWxView::OnInitialUpdate()
{
	if(m_bViewerAvailable)
	{
		CFormView::OnInitialUpdate();

		// File being viewed
		CDocument * pDoc = GetDocument();
		CString strFile = pDoc->GetPathName();
		m_AvView.SetSourcePath(strFile);
		
			// scroll bars
		RECT rectClient;
		GetClientRect(&rectClient);
		SetScaleToFitSize(CSize(300,300));
	}
}

void IDWxView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if(!m_bViewerAvailable)
	{
		CDocument * pDoc = GetDocument();
		CString strFile = pDoc->GetPathName();
		CString str;
		CString strFormat;
		strFormat.LoadString(IDS_NOSUPPORT);
		str.Format(strFormat,strFile);
		BOOL bDrawn = dc.TextOut( 0, 0, str);
	}
}

void IDWxView::OnFileView()
{
	if(!m_bViewerAvailable)
		return;

	HRESULT Result=NOERROR;

	CString strIdwFileName;

	static TCHAR BASED_CODE szFilter[] = _T("Inventor Drawing Files (*.idw)|*.idw||");
	CFileDialog aDlg( TRUE, _T(".IDW"),NULL,OFN_FILEMUSTEXIST,szFilter);
	if(IDOK == aDlg.DoModal())
		strIdwFileName = aDlg.GetPathName( );
	else
		return;
	m_DialogBar.EnableWindow(TRUE);

	if(m_spApp)
	{
		CComBSTR strDocName((LPCTSTR)strIdwFileName );

		// Open the file
		CComPtr<ApprenticeServerDocument> spAppDoc;
		Result = m_spApp->Open(strDocName,&spAppDoc);
		if(FAILED(Result))
		{
			AfxMessageBox(_T("Error: Failed to open the IDW drawing document."));
			return;
		}
	
		CComQIPtr<ApprenticeServerDrawingDocument> spDrawingDocument(spAppDoc);

		Result = spDrawingDocument->get_DisplayName(&m_strIDWDisplayName);
	
		// Get the sheets and initialize the list of sheets in the UI
		m_spSheets = NULL;
		Result = spDrawingDocument->get_Sheets(&m_spSheets);
		if (SUCCEEDED(Result)) 
		{
			long nCount;
			m_spSheets->get_Count(&nCount);
			if (SUCCEEDED(Result)) 
			{
				CComBSTR strSheetName;

				CComboBox* pCBox = (CComboBox*)m_DialogBar.GetDlgItem(IDC_SHEETLIST);
				pCBox->ResetContent();

				long nIndex;
				for(nIndex = 1; nIndex<=nCount; nIndex++)
				{
					CComPtr<Sheet> spSheet;
					Result = m_spSheets->get_Item(CComVariant(nIndex),&spSheet);
					if (FAILED(Result)) 
						continue;
					strSheetName.Empty();  // Need to empty it to avoid leaking the BSTR from the previous pass
					Result = spSheet->get_Name(&strSheetName);
					if (SUCCEEDED(Result))
					{
						int nCBIndex = pCBox->AddString(strSheetName);
						ASSERT(nCBIndex == (nIndex - 1));
					}
				}

				// Select the first sheet as the one to be viewed
				nIndex = 1;
				pCBox->SetCurSel(nIndex - 1);
				ViewSheet(nIndex);

				// Update the title
				CString strTitle(m_strIDWDisplayName);
				strTitle += _T(":"); 
				strTitle += strSheetName;
				::AfxGetMainWnd()->SetWindowText(strTitle);
			}
			else
				AfxMessageBox(_T("Error: Failed to get the count of sheets from the drawing document."));
		}
		else
			AfxMessageBox(_T("Error: Failed to get the sheets from the drawing document."));

	}
	else
		AfxMessageBox(_T("Error: Inventor apprentice server is not correctly installed."));

}

void IDWxView::OnUpdateFileOpen(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_bViewerAvailable);
}

void IDWxView::ViewSheet(int nIndex)
{
	HRESULT Result=NOERROR;

	CComVariant vtIndex2((long)nIndex);

	if(m_spSheets)
	{
		CComPtr<Sheet> spSheet;
		Result = m_spSheets->get_Item(vtIndex2,&spSheet);
		if (SUCCEEDED(Result))
		{
			CComPtr<DataIO> spDataIO;
			Result = spSheet->get_DataIO(&spDataIO);
			if (SUCCEEDED(Result))
			{
				CComBSTR strSheetName;
				Result = spSheet->get_Name(&strSheetName);

				TCHAR strTempFolderPath[MAX_PATH];
				GetTempPath(MAX_PATH, strTempFolderPath);

				CString strTempDwfFileName = strTempFolderPath;
				strTempDwfFileName += m_strIDWDisplayName;
				strTempDwfFileName = strTempDwfFileName.Left(strTempDwfFileName.GetLength() - 4);
				strTempDwfFileName += _T("_Sheet");

				TCHAR strSheetNo[MAX_PATH];
				_itot_s(nIndex,strSheetNo,MAX_PATH,10);

				strTempDwfFileName += strSheetNo;
				strTempDwfFileName += _T(".dwf");

				CString strCurDwfFileName = m_AvView.GetSourcePath();
				if (strCurDwfFileName == strTempDwfFileName)
					return;

				Result = spDataIO->WriteDataToFile(_bstr_t(_T("DWF")),CComBSTR(strTempDwfFileName));
				if (SUCCEEDED(Result))
				{
					m_AvView.SetSourcePath(strTempDwfFileName);

					// Update the title
					CString strTitle(m_strIDWDisplayName);
					strTitle += _T(":");
					strTitle += strSheetName;
					::AfxGetMainWnd()->SetWindowText(strTitle);

				}
				else
					AfxMessageBox(_T("Error: Failed to write the DWF out from the sheet."));
			}
			else
				AfxMessageBox(_T("Error: Failed to get the DataIO from the sheet."));
		}
		else
			AfxMessageBox(_T("Error: Failed to get the sheet from the sheets collection."));
	}
	
}

void IDWxView::OnEditchangeSheetlist()
{
	CString strText;
	CString strItem;
	CComboBox* pCBox = (CComboBox*)m_DialogBar.GetDlgItem(IDC_SHEETLIST);

	int nIndex = pCBox->GetCurSel();
	if (nIndex == CB_ERR)
		return;

	// Select the sheet to be viewed
	nIndex ++;
	ViewSheet(nIndex);
}