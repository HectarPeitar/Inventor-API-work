// AssemblyTreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AssemblyTree.h"
#include "AssemblyTreeDlg.h"
#include "FileOpenDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAssemblyTreeDlg dialog

CAssemblyTreeDlg::CAssemblyTreeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAssemblyTreeDlg::IDD, pParent)
	, m_strFileName_EditBox(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAssemblyTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILENAME_EDIT, m_strFileName_EditBox);
	DDX_Control(pDX, IDC_ASSEMBLY_TREE, m_Assembly_TreeCtrl);
}

BEGIN_MESSAGE_MAP(CAssemblyTreeDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BROWSE_BUTTON, OnBnClickedBrowsebutton)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON, OnBnClickedClosebutton)
	ON_BN_CLICKED(IDC_REFRESHTREE_BUTTON, OnBnClickedRefreshtreeButton)
END_MESSAGE_MAP()


// CAssemblyTreeDlg message handlers

BOOL CAssemblyTreeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	//create image list
	m_ImageList.Create( IDB_IMAGES, 16, 1, RGB(255,255,255) );	

	//set the image list for the assembly tree
	m_Assembly_TreeCtrl.SetImageList(&m_ImageList, TVSIL_NORMAL);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAssemblyTreeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAssemblyTreeDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAssemblyTreeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAssemblyTreeDlg::OnBnClickedBrowsebutton()
{
	// TODO: Add your control notification handler code here
	AFX_MANAGE_STATE (AfxGetAppModuleState());

	//get the current dialog values
	UpdateData(TRUE);

	//display the "file open" dialog
	bool bOpenFileDialog = true;

	//set up the file extension and other options for the dialog
	CString strDefExt = _T(".iam");
	CString strFileFilter = _T("Assembly Files (*.iam)|*.iam|");

	DWORD dFlags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
		
	//construct the dialog box
	CFileOpenDlg clsFileOpendlg(bOpenFileDialog,strDefExt,NULL,dFlags,strFileFilter);

	//show the dialog box
	if(clsFileOpendlg.DoModal() == IDOK){

		//get the file name that was entered and allocate it to FileName
		m_strFileName_EditBox = clsFileOpendlg.GetPathName();

	}

	//update the dialog display
	UpdateData(FALSE);

}

void CAssemblyTreeDlg::OnBnClickedClosebutton()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

HRESULT CAssemblyTreeDlg::GetAssemblyTree()
{
	HRESULT hr = NOERROR;

	//create Apprentice object
	CComPtr<ApprenticeServer> pApprenticeServer;
	hr = pApprenticeServer.CoCreateInstance(L"Inventor.ApprenticeServer");
	if(FAILED(hr)){
		AfxMessageBox(CString(_T("Failed to create instance of Apprentice")));
		return hr;
	}

	//open the assembly file
	CComPtr<ApprenticeServerDocument> pApprenticeServerDocument;
	hr = pApprenticeServer->Open(CComBSTR(m_strFileName_EditBox), &pApprenticeServerDocument);
	if(FAILED(hr) || !pApprenticeServerDocument)
	{
		AfxMessageBox(CString(_T("Failed to open document, please verify full file name of assembly ")));
		return E_FAIL;
	}
		
	//get the component definition 
	CComPtr<ComponentDefinition> pCompDef;
	hr = pApprenticeServerDocument->get_ComponentDefinition(&pCompDef);
	if(FAILED(hr)){
		AfxMessageBox(CString(_T("Failed to get the component definition from the document")));
		pApprenticeServer->Close();
		return hr;
	}

	//get the top assembly name 
	CComBSTR bstrDisplayName;
	pApprenticeServerDocument->get_DisplayName(&bstrDisplayName);

	//add the top assembly name to the tree
	HTREEITEM htritmTopNode;
	htritmTopNode = m_Assembly_TreeCtrl.InsertItem(bstrDisplayName,0,0);

	//get the the collection of component occurrences
	CComPtr<ComponentOccurrences> pCompOccs;
	hr = pCompDef->get_Occurrences(&pCompOccs);
	if(FAILED(hr)){
		AfxMessageBox(CString(_T("Failed to get occurrences from the component definition")));
		pApprenticeServer->Close();
		return hr;
	}

	//call the recursive function to get the assembly tree
	hr = GetOccurrences(pCompOccs, htritmTopNode );
	if (FAILED(hr))
	{
		AfxMessageBox(CString(_T("Failed to get the Assembly Occurrences")));
		pApprenticeServer->Close();
		return hr;
	}

	//close the apprentice document
	pApprenticeServer->Close();

	//expand the top node
	m_Assembly_TreeCtrl.Expand(htritmTopNode,TVE_EXPAND);

	return NOERROR;
}

HRESULT CAssemblyTreeDlg::GetOccurrences(ComponentOccurrences* pCompOccs, HTREEITEM htritmTopNode )
{
	HRESULT hr = NOERROR;

	//get the number of occurrences at the current level 
	long lNoOccs; 
	hr = pCompOccs->get_Count(&lNoOccs);
	if(FAILED(hr))
	{
		AfxMessageBox(CString(_T("Failed to get the number of occurrences")));
		return hr;
	}

	//iterate through the current level of occurrences
	long lOccCount;
	for (lOccCount=1; lOccCount <= lNoOccs; ++lOccCount)
	{
		CComPtr<ComponentOccurrence> pCompOcc;
		hr = pCompOccs->get_Item(lOccCount, & pCompOcc);
		if(FAILED(hr))
		{
			AfxMessageBox(CString(_T("Failed to get an occurrrence from the collection")));
			return hr;
		}
		
		//get the display name from the component occurrence
		CComBSTR bstrDisplayName;
		hr = pCompOcc->get_Name(&bstrDisplayName);
		if(FAILED(hr))
		{
			AfxMessageBox(CString(_T("Failed to get the display name of the occurrence")));
			return hr;
		}

		//add the occurrence name to the assembly tree (under its parent)
		HTREEITEM htritmParentNode;
		if (pCompOcc->DefinitionDocumentType == kPartDocumentObject) 
			htritmParentNode = m_Assembly_TreeCtrl.InsertItem(bstrDisplayName,1,1,htritmTopNode);
		if (pCompOcc->DefinitionDocumentType == kAssemblyDocumentObject) 
			htritmParentNode = m_Assembly_TreeCtrl.InsertItem(bstrDisplayName,0,0,htritmTopNode);


		//get the sub occurrences of the current occurrence
		CComPtr<ComponentOccurrencesEnumerator> pCompOccsEnum;
		hr = pCompOcc->get_SubOccurrences(&pCompOccsEnum);
		if(FAILED(hr))
		{
			AfxMessageBox(CString(_T("Failed to get the sub occurrences")));
			return hr;
		}

		//QI for the ComponentOccurrences interface 
		CComQIPtr<ComponentOccurrences> pCompOccs(pCompOccsEnum);
		if(!pCompOccs)
		{
			AfxMessageBox(CString(_T("Failed to QI for ComponentOccurrences")));
			return E_FAIL;
		}

		//recursively call this function to get any sub occurrences
		hr = GetOccurrences(pCompOccs, htritmParentNode );
		if (FAILED(hr)) return hr;

		//expand the parent node
		m_Assembly_TreeCtrl.Expand(htritmParentNode,TVE_EXPAND);

	}

	return NOERROR;
}

void CAssemblyTreeDlg::OnBnClickedRefreshtreeButton()
{
	// TODO: Add your control notification handler code here
	HRESULT hr=NOERROR;
  
	//get current data from dialog box
	UpdateData(TRUE);

	//first delete existing items in the tree
	m_Assembly_TreeCtrl.DeleteAllItems();

	hr = ::CoInitialize (NULL);

	hr = GetAssemblyTree();
	
	::CoUninitialize(); 

}

