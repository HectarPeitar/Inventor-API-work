#include "StdAfx.h"
#include "DrawSlotCommandButton.h"

//-----------------------------------------------------------------------------
STDMETHODIMP CDrawSlotCommandButton::ButtonDefinitionEvents_OnExecute (NameValueMap *pContext) 
{ 		
	HRESULT hr;

	CComPtr<CommandManager> pCommandManager;
	hr = m_pApplication->get_CommandManager(&pCommandManager);
	if(FAILED(hr)) return hr;

	CComPtr<ControlDefinitions> pControlDefinitions;
	hr = pCommandManager->get_ControlDefinitions(&pControlDefinitions);
	if(FAILED(hr)) return hr;

	//get the values specified for the height and width in the combo boxes
	CComPtr<ControlDefinition> pSlotHeightCtrlDef;
	hr = pControlDefinitions->get_Item(CComVariant("Autodesk:SimpleAddIn:SlotHeightCboBox"), &pSlotHeightCtrlDef);
	if(FAILED(hr)) return hr;

	CComPtr<ControlDefinition> pSlotWidthCtrlDef;
	hr = pControlDefinitions->get_Item(CComVariant("Autodesk:SimpleAddIn:SlotWidthCboBox"), &pSlotWidthCtrlDef);
	if(FAILED(hr)) return hr;
	
	CComQIPtr<ComboBoxDefinitionObject> pSlotHeightComboBoxDef(pSlotHeightCtrlDef);
	if (!pSlotHeightComboBoxDef) return E_FAIL;

	CComQIPtr<ComboBoxDefinitionObject> pSlotWidthComboBoxDef(pSlotWidthCtrlDef);
	if (!pSlotWidthComboBoxDef) return E_FAIL;

	long dSlotWidth;
	long dSlotHeight;

	hr = pSlotWidthComboBoxDef->get_ListIndex(&dSlotWidth);
	if(FAILED(hr)) return hr;

	hr = pSlotHeightComboBoxDef->get_ListIndex(&dSlotHeight);
	if(FAILED(hr)) return hr;

	if(dSlotHeight > 0 && dSlotWidth > 0)
	{
		CComPtr<IDispatch> pActiveObj;
		hr = m_pApplication->get_ActiveEditObject(&pActiveObj);
		if(FAILED(hr)) return hr;

		CComQIPtr<PlanarSketch> p2DSketch(pActiveObj);
		if (!p2DSketch) return E_FAIL;

		CComPtr<TransientGeometry> pTransientGeometry;
		hr = m_pApplication->get_TransientGeometry(&pTransientGeometry);
		if(FAILED(hr)) return hr;

		CComPtr<Document> pActiveDoc;
		hr = m_pApplication->get_ActiveDocument(&pActiveDoc);
		if(FAILED(hr)) return hr;
		
		CComPtr<TransactionManager> pTransactionMgr;
		hr = m_pApplication->get_TransactionManager(&pTransactionMgr);
		if(FAILED(hr)) return hr;

		//start transaction
		CComPtr<Transaction> pSlotTransaction;
		hr = pTransactionMgr->StartTransaction(pActiveDoc, CComBSTR(_T("Create Slot")), &pSlotTransaction);
		if(FAILED(hr)) return hr;

		//create the transient geometry points
		CComPtr<Point2d> pPT1;
		hr = pTransientGeometry->CreatePoint2d(0, 0, &pPT1);
		if(FAILED(hr)) return hr;

		CComPtr<Point2d> pPT2;
		hr = pTransientGeometry->CreatePoint2d(dSlotWidth, 0, &pPT2);
		if(FAILED(hr)) return hr;

		CComPtr<Point2d> pPT3;
		hr = pTransientGeometry->CreatePoint2d(dSlotWidth, dSlotHeight / 2.0, &pPT3);
		if(FAILED(hr)) return hr;

		CComPtr<Point2d> pPT4;
		hr = pTransientGeometry->CreatePoint2d(dSlotWidth, dSlotHeight, &pPT4);
		if(FAILED(hr)) return hr;

		CComPtr<Point2d> pPT5;
		hr = pTransientGeometry->CreatePoint2d(0, dSlotHeight, &pPT5);
		if(FAILED(hr)) return hr;

		CComPtr<Point2d> pPT6;
		hr = pTransientGeometry->CreatePoint2d(0, dSlotHeight / 2.0, &pPT6);
		if(FAILED(hr)) return hr;

		//create the sketch lines and arcs
		CComPtr<SketchLines> pSketchLines;
		hr = p2DSketch->get_SketchLines(&pSketchLines);
		if(FAILED(hr)) return hr;
        
		CComPtr<SketchArcs> pSketchArcs;
		hr = p2DSketch->get_SketchArcs(&pSketchArcs);
		if(FAILED(hr)) return hr;

		CComPtr<SketchLine> pLine1;
		hr = pSketchLines->AddByTwoPoints(pPT1, pPT2, &pLine1);
		if(FAILED(hr)) return hr;

		CComPtr<SketchArc> pArc1;
		hr = pSketchArcs->AddByCenterStartEndPoint(pPT3, pLine1->EndSketchPoint, pPT4, VARIANT_TRUE, &pArc1);
		if(FAILED(hr)) return hr;	

		CComPtr<SketchLine> pLine2;
		hr = pSketchLines->AddByTwoPoints(pArc1->EndSketchPoint, pPT5, &pLine2);
		if(FAILED(hr)) return hr;					

		CComPtr<SketchArc> pArc2;
		hr = pSketchArcs->AddByCenterStartEndPoint(pPT6, pLine2->EndSketchPoint, pLine1->StartSketchPoint, VARIANT_TRUE, &pArc2);
		if(FAILED(hr)) return hr;

		CComPtr<GeometricConstraints> pGeomConstraints;
		hr = p2DSketch->get_GeometricConstraints(&pGeomConstraints);
		if(FAILED(hr)) return hr;

		//create the tangent constraints between the lines and arcs
		CComQIPtr<SketchEntity> pSkEntityLine1(pLine1);
		if (!pSkEntityLine1) return E_FAIL;

		CComQIPtr<SketchEntity> pSkEntityLine2(pLine2);
		if (!pSkEntityLine2) return E_FAIL;

		CComQIPtr<SketchEntity> pSkEntityArc1(pArc1);
		if (!pSkEntityArc1) return E_FAIL;

		CComQIPtr<SketchEntity> pSkEntityArc2(pArc2);
		if (!pSkEntityArc2) return E_FAIL;

		hr = pGeomConstraints->AddTangent(pSkEntityLine1, pSkEntityArc1, vtMissing);
		hr = pGeomConstraints->AddTangent(pSkEntityLine2, pSkEntityArc1, vtMissing);
		hr = pGeomConstraints->AddTangent(pSkEntityLine1, pSkEntityArc2, vtMissing);
		hr = pGeomConstraints->AddTangent(pSkEntityLine2, pSkEntityArc2, vtMissing);

		//create a parallel constraint between the two lines
		hr = pGeomConstraints->AddParallel(pSkEntityLine1, pSkEntityLine2, VARIANT_TRUE, VARIANT_TRUE);

		hr = pSlotTransaction->End();
		if(FAILED(hr)) return hr;
	}

	return S_OK;
}

