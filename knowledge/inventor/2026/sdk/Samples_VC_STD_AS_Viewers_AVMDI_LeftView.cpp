// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "ApprenticeViewerMDI.h"

#include "ApprenticeViewerMDIDoc.h"
#include "LeftView.h"
#include "ApprenticeViewerMDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
	// TODO: add construction code here

}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CApprenticeViewerMDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void GetComponents(CComQIPtr<ComponentOccurrences> pInCollection, CTreeCtrl *pTree, HTREEITEM pNode)
{
	long occCount = 0;
	pInCollection->get_Count(&occCount);

	for (int i=1; i<=occCount; ++i)
	{
		CComPtr<ComponentOccurrence> pOcc;
		HRESULT hr = pInCollection->get_Item(i, &pOcc);

		CComBSTR nameBSTR;
		pOcc->get_Name(&nameBSTR);
		CString name = nameBSTR;

		CComPtr<ComponentDefinition> pCompDef;
		CComPtr<IDispatch> pDocDispatch;
		hr = pOcc->get_Definition(&pCompDef);
		hr = pCompDef->get_Document(&pDocDispatch);
		CComQIPtr<ApprenticeServerDocument> pDoc = pDocDispatch;
		DocumentTypeEnum docType;
		pDoc->get_DocumentType(&docType);
		int image = docType == kAssemblyDocumentObject ? 0 : 1;
	
		HTREEITEM pNewNode = pTree->InsertItem(name, image, image, pNode);
//		pTree->SetItemData(pNewNode, (DWORD) pDoc.Detach());

		CComPtr<ComponentOccurrencesEnumerator> pSubOccurrencesEnum;
		hr = pOcc->get_SubOccurrences(&pSubOccurrencesEnum);
		CComQIPtr<ComponentOccurrences> pSubOccurrences = pSubOccurrencesEnum;

		GetComponents(pSubOccurrences, pTree, pNewNode);
	}

}

void GetSheets(CComPtr<Sheets> pSheets, CTreeCtrl *pTree, HTREEITEM pNode)
{
	HRESULT hr = S_OK;

	long sheetCount = 0;
	pSheets->get_Count(&sheetCount);

	for (long i=1; i<=sheetCount; ++i)
	{
		CComPtr<Sheet> pSheet;
		hr = pSheets->get_Item(_variant_t(i), &pSheet);

		CComBSTR nameBSTR;
		hr = pSheet->get_Name(&nameBSTR);
		CString name = nameBSTR;

		HTREEITEM pNewNode = pTree->InsertItem(name, 3, 3, pNode);
		pTree->SetItemData(pNewNode, i);
	}
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	CTreeCtrl *pTree = &GetTreeCtrl();
	pTree->ModifyStyle(0, TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT);

	pTree->ModifyStyle(0, TVS_SHOWSELALWAYS);

	m_assemblyTreeImages.Create(IDB_ASSEMBLY_TREE_IMAGES, 16, 1, RGB(255, 0, 255));
	pTree->SetImageList(&m_assemblyTreeImages, TVSIL_NORMAL);

	HTREEITEM pNode = pTree->GetRootItem();

	//oDoc.ComponentDefinition.Occurrences
	CComPtr<ComponentDefinition> pCompDef;
	CComQIPtr<ComponentOccurrences> pOccurrences;
	CComPtr<ApprenticeServerDocument> pDoc = GetDocument()->GetApprenticeDocument();
	if (pDoc)
	{
		CComBSTR nameBSTR;
		pDoc->get_DisplayName(&nameBSTR);
		CString name = nameBSTR;

		// Add the root item to the tree
		DocumentTypeEnum docType;
		pDoc->get_DocumentType(&docType);
		if (docType == kAssemblyDocumentObject || docType == kPartDocumentObject)
		{
			int image = docType == kAssemblyDocumentObject ? 0 : 1;

			pDoc->get_ComponentDefinition(&pCompDef);
			pCompDef->get_Occurrences(&pOccurrences);

			HTREEITEM pNewNode = pTree->InsertItem(name, image, image, pNode);
			pTree->SetItemData(pNewNode, (DWORD_PTR) pDoc.Detach());

			// Add its children to the tree
			GetComponents(pOccurrences, pTree, pNewNode);
		}
		else if (docType == kDrawingDocumentObject)
		{
			CComQIPtr<ApprenticeServerDrawingDocument> pDrawingDoc = pDoc;

			HTREEITEM pNewNode = pTree->InsertItem(name, 2, 2, pNode);
			pTree->SetItemData(pNewNode, (DWORD_PTR) pDoc.Detach());

			CComPtr<Sheets> pSheets;
			pDrawingDoc->get_Sheets(&pSheets);

			// Add its sheets here
			GetSheets(pSheets, pTree, pNewNode);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CApprenticeViewerMDIDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CApprenticeViewerMDIDoc)));
	return (CApprenticeViewerMDIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

void CLeftView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	CTreeCtrl *pTree = &GetTreeCtrl();

	HTREEITEM selectedItem = pTree->GetSelectedItem();

	if (selectedItem != pTree->GetRootItem())
	{
		long index = (long) pTree->GetItemData(selectedItem);

		CWnd *pOwner = this->GetOwner();
		CSplitterWnd *pSplitterWnd = DYNAMIC_DOWNCAST(CSplitterWnd, pOwner);

		CWnd *pViewWnd = pSplitterWnd->GetPane(0, 1);
		CApprenticeViewerMDIView *pView = DYNAMIC_DOWNCAST(CApprenticeViewerMDIView, pViewWnd);
		
		pView->SelectionChanged(index);
	}

/*
	CComQIPtr<ApprenticeServerDocument> pOccDoc 
		= (ApprenticeServerDocument *) pTree->GetItemData(pNMTreeView->itemNew.hItem);

	// Determine what type of document the user selected
	DocumentTypeEnum docType;
	pOccDoc->get_DocumentType(&docType);
	bool isPart = docType == kPartDocumentObject;

	CComPtr<ClientViews> pClientViews;
	pOccDoc->get_ClientViews(&pClientViews);

	pView->SetClientViews(pClientViews);
	pView->ResetView();
*/	
	*pResult = 0;
}

void CLeftView::OnClose() 
{
	CTreeView::OnClose();
}
