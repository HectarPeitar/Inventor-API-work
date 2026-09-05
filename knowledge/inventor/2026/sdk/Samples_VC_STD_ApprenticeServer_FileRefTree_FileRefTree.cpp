// FileRefTree.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "filereftree.h"
#include "filereftreedlg.h"


#include <atlconv.h>

#include <tchar.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileRefTreeApp

BEGIN_MESSAGE_MAP(CFileRefTreeApp, CWinApp)
	//{{AFX_MSG_MAP(CFileRefTreeApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileRefTreeApp construction

CFileRefTreeApp::CFileRefTreeApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFileRefTreeApp object

CFileRefTreeApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFileRefTreeApp initialization

BOOL CFileRefTreeApp::InitInstance()
{
	if(!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	CString sDefExt = L".asm";
	CString sFilter = L"Assembly Files (*.iam)|*.iam|Part Files (*.ipt)|*.ipt|Drawing Files (*.idw)|*.idw||";
	CString sMessage = L"Filename extension must be \".iam\",\".ipt\",  or \".idw\"";

	CFileDialog openFileDlg(true, sDefExt, NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, sFilter);

	if (openFileDlg.DoModal() != IDOK)
		return FALSE;

	CString pathName = openFileDlg.GetPathName();		// return full path and filename
	CString fileExt  = openFileDlg.GetFileExt();		// return only ext

	if (fileExt != L"idw" && fileExt != L"iam" && fileExt != L"ipt")
	{
		AfxMessageBox(sMessage);
		return FALSE;
	}
	
	//create Apprentice object
	CComPtr<ApprenticeServer> pApprenticeServer;
	HRESULT hr = pApprenticeServer.CoCreateInstance(CLSID_ApprenticeServerComponent);
	if(FAILED(hr))
	{
		AfxMessageBox(L"Failed to create an instance of Apprentice server.");
		return false;
	}

	ASSERT(pApprenticeServer != NULL);

	// Open the file.
	CComPtr<ApprenticeServerDocument> pTopLevelDoc;
	hr = pApprenticeServer->Open(CComBSTR(pathName), &pTopLevelDoc);
	if(FAILED(hr))
		return false;

	ASSERT(pTopLevelDoc != NULL);

	CMapStringToPtr fileRefMap;
	hr = visit(pathName, pTopLevelDoc, 0, fileRefMap) ? S_OK : E_FAIL;	// Recurse down through tree
	if (FAILED(hr))
		return false;

	// Iterate through the entire map, creating a WhereUsed list for each file occurring in
	//   the tree:
	AddString(0, CString(L""));
	AddString(0, CString(L"Where-used information:"));

	POSITION pos = fileRefMap.GetStartPosition();
	CString fileName;
	CComPtr<ApprenticeServerDocument> pDoc;   

	while (pos != NULL)
	{
		void* pVoid{ nullptr };
		fileRefMap.GetNextAssoc(pos, fileName, pVoid);
		
		AddString(1, fileName+CString(L" referenced by:"));

		// The referenced files full file name
		CComBSTR strFullFileName(fileName) ;
		
		CComPtr<ApprenticeServerDocuments> pOwningDocuments;
		hr = pTopLevelDoc->FindWhereUsed(strFullFileName,&pOwningDocuments);
		if (FAILED(hr))
			return FALSE;
    
		ASSERT(pOwningDocuments != NULL);
		if(!pOwningDocuments)
			return FALSE;

		long nDocs = 0;
		hr = pOwningDocuments->get_Count(&nDocs);
		if (FAILED(hr))
			return FALSE;

		for (int i = 1; i <= nDocs; i++)
		{
			CComPtr<ApprenticeServerDocument> pOwner;
			hr = pOwningDocuments->get_Item(i,&pOwner);
			if (FAILED(hr))
				return FALSE;

			ASSERT(pOwner != NULL);
			
			CComBSTR strOwnerFullFileName;
			hr = pOwner->get_FullFileName(&strOwnerFullFileName);
			if (FAILED(hr))
				return FALSE;

			ASSERT (strOwnerFullFileName.Length() != 0);

			CString owner(strOwnerFullFileName);
			ASSERT(!owner.IsEmpty());
			AddString(2, owner);
		}

		AddString(0, CString(L""));
	}

	// Create the dialog

	CFileRefTreeDlg dlg(this);
	m_pMainWnd = &dlg;

	dlg.DoModal();

	return FALSE;
}

bool CFileRefTreeApp::visit( CString pathName, ApprenticeServerDocument* pDoc,
							    int nestingLevel, CMapStringToPtr& fileRefMap)
{
	// Retrieve path::filename and SaveCounter information:
	ASSERT(pDoc != NULL);

	CComBSTR bstrSavedFileName;
	HRESULT hr = pDoc->get_DisplayName(&bstrSavedFileName);
	ASSERT(bstrSavedFileName.Length() != 0 );

	CString savedFileName(bstrSavedFileName);

	TCHAR drive[_MAX_DRIVE];
	TCHAR dir  [_MAX_DIR  ];
	TCHAR fname[_MAX_FNAME];
	TCHAR ext  [_MAX_EXT  ];

	_tsplitpath_s(savedFileName, drive, dir, fname, ext);

	CString title;
	if (!nestingLevel)
		title.Format(L"Top-level Inventor file:  %s%s", fname, ext);
	else
		title.Format(L"%s%s", fname, ext);

	AddString(nestingLevel, title);

	CString savedFileNameString(L"Saved as:  ");
	savedFileNameString += savedFileName;
	AddString(nestingLevel+1, savedFileNameString);

	CComBSTR bstrResolvedPathName;
	hr = pDoc->get_FullFileName(&bstrResolvedPathName);
	if(FAILED(hr))
		return false;

	ASSERT(bstrResolvedPathName.Length() != 0 );
	CString foundFileName(bstrResolvedPathName);
	CString foundFileNameString(L"Found at:  ");
	foundFileNameString += foundFileName;

	AddString(nestingLevel+1, foundFileNameString);

	long theSaveCounter;
	hr = pDoc->get_FileSaveCounter(&theSaveCounter);
	if(FAILED(hr))
		return false;

	ASSERT(theSaveCounter > 0);

	CString strSaveCounter;
	strSaveCounter.Format(L"SaveCounter:  %ld", theSaveCounter);

	AddString(nestingLevel+1, strSaveCounter);

	// Add resolved filename to map of unique files encompassed by the design:

	pDoc->AddRef(); 
	fileRefMap.SetAt(foundFileName, reinterpret_cast<void*>((ApprenticeServerDocument*)pDoc));

	// Iterate through the file's SaveCounters, building up a SaveCounters string; then
	//   add the SaveCounters string to the output vector

	CString strSaveCounters(L"Other versions present:  ");

	/*CComPtr<FileVersions> pFileVersions;
	hr 	= pDoc->get_FileVersions(&pFileVersions);
	if(FAILED(hr))
		return false;

	ASSERT(pFileVersions != NULL);

	bool bFirst = true;
	unsigned long fileVersionCt = 1;
	CComPtr<FileVersion> pFileVersion;
	for (;(hr = pFileVersions->get_Item(fileVersionCt, &pFileVersion)) == S_OK;pFileVersion.Release())
	{
		++fileVersionCt;

		// Get name of OLE file:
		long nSaveCounter; 
		pFileVersion->get_SaveCounter(&nSaveCounter);

		ASSERT(nSaveCounter > 0);
		CString v;

		if (nSaveCounter != theSaveCounter)
		{
			if (bFirst)
			{
				v.Format(L"%ld", nSaveCounter);
				bFirst = false;
			}
			else
				v.Format(L", %ld", nSaveCounter);

			strSaveCounters += v;
		}
	}
	
	ASSERT(pFileVersion == NULL); */

	AddString(nestingLevel+1, strSaveCounters);

	// Iterate through children if any, recursing on subassemblies

	CComPtr<ApprenticeServerDocuments> pRefDocs;
	hr = pDoc->get_ReferencedDocuments(&pRefDocs);
	if (FAILED(hr))
		return false;

	ASSERT(pRefDocs != NULL);

	bool bFirst = true;
	unsigned long refDocCt = 1;
	CComPtr<ApprenticeServerDocument> pRefDoc;
	for (;(hr = pRefDocs->get_Item(refDocCt, &pRefDoc)) == S_OK;pRefDoc.Release())
	{
		++refDocCt;

		if (bFirst)
		{
			AddString(nestingLevel+1, CString(L"Components:"));
			bFirst = false;
		}

		if (pRefDoc != NULL)
		{
			// Get child's resolved name
			CComBSTR bstrResolvedPathName;
			hr = pRefDoc->get_FullFileName(&bstrResolvedPathName);
			if(FAILED(hr))
				return false;

			ASSERT(bstrResolvedPathName.Length() != 0 );

			// Recurse:
			visit(CString(bstrResolvedPathName), pRefDoc, nestingLevel+2, fileRefMap);
		}

	}
	
	ASSERT(pRefDoc == NULL);

	// Iterate through OLE referenced files if any, adding each to the output vector
	CComPtr<ReferencedOLEFileDescriptors> pRefOLEDescrs;
	hr = pDoc->get_ReferencedOLEFileDescriptors(&pRefOLEDescrs);
	if(FAILED(hr))
		return false;

	ASSERT(pRefOLEDescrs != NULL);

	bFirst = true;
	unsigned long refOLEFileDescCt = 1;
	CComPtr<ReferencedOLEFileDescriptor> pRefOLEDescr;
	for (;(hr = pRefOLEDescrs->get_Item(refOLEFileDescCt, &pRefOLEDescr)) == S_OK;pRefOLEDescr.Release())
	{
		++refOLEFileDescCt;

		OLEDocumentTypeEnum eOleDocumentTypeEnum;
		hr = pRefOLEDescr->get_OLEDocumentType(&eOleDocumentTypeEnum);
		if(FAILED(hr))
			return false;

		// Only do OLE links (ignore embeddings)
		if (eOleDocumentTypeEnum == kOLEDocumentLinkObject)
		{
			  if (bFirst)
			  {
				  AddString(nestingLevel+1, CString(L"Linked OLE files:"));
				  bFirst = false;
			  }

			  // Get name of OLE file:
			  CComBSTR bstrPathName;
			  hr = pRefOLEDescr->get_DisplayName(&bstrPathName);
			  if(FAILED(hr))
					return false;

			  ASSERT(bstrPathName.Length() != 0);

			  AddString(nestingLevel+2, CString(bstrPathName));
		}
	}

	ASSERT(pRefOLEDescr == NULL);

	return true;
}

void CFileRefTreeApp::AddString(int nestingLevel, CString string)
{
	CString str;
	for (int i = 0; i < nestingLevel; i++)
		str += L"    ";
	str += string;
	m_strings.Add(str);
}

INT_PTR CFileRefTreeApp::NumberOfStrings()
{
	return m_strings.GetSize();
}

CString CFileRefTreeApp::GetString(int i)
{
	ASSERT(0 <= i && i < m_strings.GetSize());
	return m_strings[i];
}
