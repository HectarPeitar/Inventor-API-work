//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted,
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting documentation. 
// <YOUR COMPANY NAME> PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// <YOUR COMPANY NAME> SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE. <YOUR COMPANY NAME>, INC.
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE. 
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable
// 

//-----------------------------------------------------------------------------
//----- loftWithRailingsAddInServer.cpp : Implementation of CloftWithRailingsAddInServer
//-----------------------------------------------------------------------------
#include "StdAfx.h"


#include "loftWithRailings.h"
#include "loftWithRailingsAddInServer.h"


#define OnErrorReturn(badsts, errocode) if (badsts) return errocode;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
CloftWithRailingsAddInServer::CloftWithRailingsAddInServer () 
{ 
	m_pBtnDef1 = NULL;
	m_pButtonEvents1 = new CButtonDefEvents(this, 0);
	m_pApplication =NULL ;
	m_pAddInSite =NULL ;

	m_btnDefCookie1 = 0;

}


STDMETHODIMP CloftWithRailingsAddInServer::Activate (IDispatch *pDisp, VARIANT_BOOL FirstTime) {
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;

	m_pAddInSite = CComQIPtr<ApplicationAddInSite>(pDisp) ;

	//----- Get the application object.
	HRESULT hr =m_pAddInSite->get_Application (&m_pApplication) ;
	ATLASSERT( SUCCEEDED( hr ) ) ;

	if(!m_pApplication)
		return E_FAIL;

	CComPtr<CommandManager> pCommandMgr;
	hr = m_pApplication->get_CommandManager(&pCommandMgr);

	CComPtr<ControlDefinitions> pCtrlDefs;
	hr = pCommandMgr->get_ControlDefinitions(&pCtrlDefs);
	
	CComVariant vtAddInId;
	CComBSTR InternalNameBSTR;
	CComBSTR displayNameBSTR;
	CComBSTR DesTextBSTR;
	CComBSTR TooltipTextBSTR;
	CComVariant vtEmpty;
	CommandTypesEnum eCmdType;
	ButtonDisplayEnum eCmdDisplayType;

	// common button parameters
	// client Id for the buttons
	vtAddInId	      = _T("{37E7CBC7-F0F7-455B-85B4-668E0674C9DE}");
	// command type
	eCmdType = kQueryOnlyCmdType;
	// button display type
	eCmdDisplayType = kAlwaysDisplayText;

	//----- Create button definition
	InternalNameBSTR     = _T("LoftWithRailingsCmd_InternalName1");
	displayNameBSTR      = _T("Loft");
	DesTextBSTR          = _T("DescriptiveText - 1");
	TooltipTextBSTR      = _T("Tooltip -1");

	hr = pCtrlDefs->AddButtonDefinition(displayNameBSTR, InternalNameBSTR,eCmdType,vtAddInId,DesTextBSTR,TooltipTextBSTR,vtEmpty,vtEmpty,eCmdDisplayType,&m_pBtnDef1); 

	ATLASSERT(SUCCEEDED(hr));
	ATLASSERT(m_pBtnDef1 != NULL);

	m_pBtnDef1->put_Enabled(VARIANT_TRUE);

	if(m_pBtnDef1)
	{
		BOOL bBrwsrAdvised = AfxConnectionAdvise(m_pBtnDef1, DIID_ButtonDefinitionSink,
                                m_pButtonEvents1->GetInterface(&IID_IUnknown),
                                TRUE, &m_btnDefCookie1);

		ATLASSERT(bBrwsrAdvised == TRUE);
	}

	if(FirstTime != VARIANT_FALSE)
		InsertControlsInMenuBars();

	return (S_OK) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CloftWithRailingsAddInServer::Deactivate () {
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;

	// disconnect event sinks
	if(m_btnDefCookie1)
	{
		BOOL bUnadvised = AfxConnectionUnadvise(m_pBtnDef1, DIID_ButtonDefinitionSink,
											  m_pButtonEvents1->GetInterface(&IID_IUnknown),
											  TRUE, m_btnDefCookie1);
		m_btnDefCookie1 = 0;
	}

	m_pBtnDef1 = NULL;
	
	m_pAddInSite = NULL;
	m_pApplication = NULL;

	return (S_OK) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CloftWithRailingsAddInServer::ExecuteCommand (long CommandID) {
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;

	HRESULT hResult =S_OK ;
	return (loftCmd()) ;
}

//-----------------------------------------------------------------------------
STDMETHODIMP CloftWithRailingsAddInServer::get_Automation (IDispatch **ppDisp) {
	AFX_MANAGE_STATE (AfxGetStaticModuleState ()) ;

	if ( ppDisp == NULL )
		return (E_POINTER) ;

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}


//-----------------------------------------------------------------------------
HRESULT CloftWithRailingsAddInServer::loftCmd () {
	// Create loft here
	// Create new part document
	HRESULT hResult = S_OK;

	CComPtr<Documents> pDocs;
	
	hResult =m_pApplication->get_Documents(&pDocs); 
	OnErrorReturn(FAILED(hResult), hResult);

	//// decalre optional variant
	//VARIANT vopt;
	//VariantInit(&vopt);
	//V_VT(&vopt) = VT_ERROR;
	//vopt.scode = DISP_E_PARAMNOTFOUND;

	// get part document template name
	CComBSTR bstrTempFileName;
	hResult=m_pApplication->GetTemplateFile(kPartDocumentObject,
											kMetricSystemOfMeasure,
											kDefault_DraftingStandard,
											vtMissing,
											&bstrTempFileName);
	OnErrorReturn(FAILED(hResult), hResult);

	CComPtr<Document> pDoc;
	hResult=pDocs->Add(kPartDocumentObject,
						bstrTempFileName,
						VARIANT_TRUE,&pDoc); 
	OnErrorReturn(FAILED(hResult), hResult);
	
	CComPtr<TransientGeometry> pTg;
	hResult = m_pApplication->get_TransientGeometry(&pTg);
	OnErrorReturn(FAILED(hResult), hResult);
	
	CComQIPtr<PartDocument> pPartDoc(pDoc);
	if (pPartDoc != NULL)
	{
		
		
		// get PartComponentDefinition
		CComPtr<PartComponentDefinition> pCompDef;
		hResult = pPartDoc->get_ComponentDefinition(&pCompDef);
		OnErrorReturn(FAILED(hResult), hResult);

		// Get Sketches collectiom
		CComPtr<PlanarSketches> pSketches;
		hResult = pCompDef->get_Sketches(&pSketches); 
		OnErrorReturn(FAILED(hResult), hResult);


		// create sketch plane of default XY workplane
		CComPtr<PlanarSketch> pSketch1;

		CComPtr<WorkPlanes> pWorkPlanes ;	
		hResult= pCompDef->get_WorkPlanes(&pWorkPlanes)  ;
		OnErrorReturn(FAILED(hResult), hResult);

		CComPtr<WorkPlane> pWorkPlane ;
		hResult = pWorkPlanes->get_Item(CComVariant(3L), &pWorkPlane);
		OnErrorReturn(FAILED(hResult), hResult);
		
		hResult = pSketches->Add(pWorkPlane, VARIANT_FALSE,	&pSketch1);
		OnErrorReturn(FAILED(hResult), hResult);

	   // Create ellipse at 0,0 with major axis rad = 50 and min axis rad = 20, vector dir of maj axis is Y
		CComPtr<SketchEllipses> pSkEllipses;
		hResult= pSketch1->get_SketchEllipses(&pSkEllipses); 
		OnErrorReturn(FAILED(hResult), hResult);
		CComPtr<Point2d> pCpt;
		hResult =pTg->CreatePoint2d(0,0,&pCpt); 
		OnErrorReturn(FAILED(hResult), hResult);
		CComPtr<UnitVector2d> pDirVec;
		hResult = pTg->CreateUnitVector2d(0,1,&pDirVec);
		OnErrorReturn(FAILED(hResult), hResult);
		

		CComPtr<SketchEllipse> pSkEllipse;
		hResult = pSkEllipses->Add(pCpt, pDirVec,5,2, &pSkEllipse);
		OnErrorReturn(FAILED(hResult), hResult);

		// Create another ellipse at 200,0 with same dimension

		CComPtr<PlanarSketch> pSketch2;
		hResult = pSketches->Add(pWorkPlane, VARIANT_FALSE,	&pSketch2);
		OnErrorReturn(FAILED(hResult), hResult);

	    // Create ellipse at 0,0 with major axis rad = 50 and min axis rad = 20, vector dir of maj axis is Y
		// Reuse pSkEllipses
		pSkEllipses=NULL;
		hResult= pSketch2->get_SketchEllipses(&pSkEllipses); 
		OnErrorReturn(FAILED(hResult), hResult);
		// Reuse pCpt
		pCpt=NULL;
		hResult =pTg->CreatePoint2d(20,0,&pCpt); 
		OnErrorReturn(FAILED(hResult), hResult);
		// Reuse pDirVec
		pDirVec = NULL;
		hResult = pTg->CreateUnitVector2d(0,1,&pDirVec);
		OnErrorReturn(FAILED(hResult), hResult);
		

		// Reuse pSkEllipse
		pSkEllipse=NULL;
		hResult = pSkEllipses->Add(pCpt,
									pDirVec,
									5,
									2,
									&pSkEllipse);

		OnErrorReturn(FAILED(hResult), hResult);

		// Create a workplane parallel to default YZ workplane at offset 100


		pWorkPlane=NULL;
		hResult = pWorkPlanes->get_Item(CComVariant(1L), &pWorkPlane);

		CComPtr<WorkPlane> pWorkPlane1;
		hResult = pWorkPlanes->AddByPlaneAndOffset(pWorkPlane, 
													CComVariant(10.0),
													VARIANT_FALSE,
													&pWorkPlane1);
		OnErrorReturn(FAILED(hResult), hResult);
		// Set up sketch plane on above workplane

		CComPtr<PlanarSketch> pSketch3;
		hResult = pSketches->Add(pWorkPlane1, VARIANT_FALSE, &pSketch3);
		OnErrorReturn(FAILED(hResult), hResult);

		
		// Add ellipse at 0,20 with major rad = 20 , Min rad = 10 and Vector dir of maj Axis is Y
		// Reuse pSkEllipses
		pSkEllipses=NULL;
		hResult= pSketch3->get_SketchEllipses(&pSkEllipses); 
		OnErrorReturn(FAILED(hResult), hResult);
		// Reuse pCpt
		pCpt=NULL;
		hResult =pTg->CreatePoint2d(0,2,&pCpt); 
		OnErrorReturn(FAILED(hResult), hResult);
		// Reuse pDirVec
		pDirVec = NULL;
		hResult = pTg->CreateUnitVector2d(0,1,&pDirVec);
		OnErrorReturn(FAILED(hResult), hResult);
		

		// Reuse pSkEllipse
		pSkEllipse=NULL;
		hResult = pSkEllipses->Add(pCpt,
									pDirVec,
									1,
									2,
									&pSkEllipse);
		OnErrorReturn(FAILED(hResult), hResult);


		// Now create a workplane parallel to XZ at offset -40
		
		// get XZ workplane 

		
		pWorkPlane=NULL;
		hResult = pWorkPlanes->get_Item(CComVariant(2L), &pWorkPlane);
		OnErrorReturn(FAILED(hResult), hResult);

		CComPtr<WorkPlane> pWorkPlane2;
		hResult = pWorkPlanes->AddByPlaneAndOffset(pWorkPlane, CComVariant(-4.0),
			VARIANT_FALSE,	&pWorkPlane2);
		OnErrorReturn(FAILED(hResult), hResult);


		// Now create small ellipes inside existing ellipes in XY Plane


		// Draw first ellipse on left

		pWorkPlane=NULL;
		hResult = pWorkPlanes->get_Item(CComVariant(3L), &pWorkPlane);

		// Set up sketch plane on above workplane

		CComPtr<PlanarSketch> pSketch4;
		hResult = pSketches->Add(pWorkPlane,
									VARIANT_FALSE,
									&pSketch4);
		OnErrorReturn(FAILED(hResult), hResult);

		
		// Add ellipse at 0,-20 with major rad = 20 , Min rad = 10 and Vector dir of maj Axis is Y
		// Reuse pSkEllipses
		pSkEllipses=NULL;
		hResult= pSketch4->get_SketchEllipses(&pSkEllipses); 
		OnErrorReturn(FAILED(hResult), hResult);
		// Reuse pCpt
		pCpt=NULL;
		hResult =pTg->CreatePoint2d(0,-2,&pCpt); 
		OnErrorReturn(FAILED(hResult), hResult);
		// Reuse pDirVec
		pDirVec = NULL;
		hResult = pTg->CreateUnitVector2d(0,1,&pDirVec);
		OnErrorReturn(FAILED(hResult), hResult);
		

		// Reuse pSkEllipse
		pSkEllipse=NULL;
		hResult = pSkEllipses->Add(pCpt,
									pDirVec,
									2,
									1,
									&pSkEllipse);
		OnErrorReturn(FAILED(hResult), hResult);

		// get the workpoint at intersection of above workplane and newly created ellipses
		// get WorkPoints collection
		CComPtr<WorkPoints> pWorkPoints;
		hResult = pCompDef->get_WorkPoints(&pWorkPoints);
		OnErrorReturn(FAILED(hResult), hResult);

		CComPtr<WorkPoint> pWorkPoint1;
		hResult =pWorkPoints->AddByCurveAndEntity(pSkEllipse,
										 pWorkPlane2,
										 vtMissing,
										 VARIANT_FALSE,
										 &pWorkPoint1);

		OnErrorReturn(FAILED(hResult), hResult);
			

		// Draw another small ellipse on right
		pWorkPlane=NULL;
		hResult = pWorkPlanes->get_Item(CComVariant(3L), &pWorkPlane);

		// Set up sketch plane on above workplane

		CComPtr<PlanarSketch> pSketch5;
		hResult = pSketches->Add(pWorkPlane,
									VARIANT_FALSE,
									&pSketch5);

		OnErrorReturn(FAILED(hResult), hResult);

		
		// Add ellipse at 200,-20 with major rad = 20 , Min rad = 10 and Vector dir of maj Axis is Y
		// Reuse pSkEllipses
		pSkEllipses=NULL;
		hResult= pSketch5->get_SketchEllipses(&pSkEllipses); 
		OnErrorReturn(FAILED(hResult), hResult);
		// Reuse pCpt
		pCpt=NULL;
		hResult =pTg->CreatePoint2d(20,-2,&pCpt); 
		OnErrorReturn(FAILED(hResult), hResult);
		// Reuse pDirVec
		pDirVec = NULL;
		hResult = pTg->CreateUnitVector2d(0,1,&pDirVec);
		OnErrorReturn(FAILED(hResult), hResult);
		

		// Reuse pSkEllipse
		pSkEllipse=NULL;
		hResult = pSkEllipses->Add(pCpt,
									pDirVec,
									2,
									1,
									&pSkEllipse);
		OnErrorReturn(FAILED(hResult), hResult);

		CComPtr<WorkPoint> pWorkPoint2;
		hResult =pWorkPoints->AddByCurveAndEntity(pSkEllipse,
										 pWorkPlane2,
										 vtMissing,
										 VARIANT_FALSE,
										 &pWorkPoint2);

		OnErrorReturn(FAILED(hResult), hResult);



		// Creat a workaxis from workpoint1 to workpoint2
		// This WorkAxes will be used in creating inclined workplane

		// Get WorkAxes collection
		CComPtr<WorkAxes> pWorkAxes;
		hResult = pCompDef->get_WorkAxes(&pWorkAxes); 
		OnErrorReturn(FAILED(hResult), hResult);
		CComPtr<WorkAxis> pWorkAxis;
		hResult=pWorkAxes->AddByTwoPoints(pWorkPoint1,
								  pWorkPoint2,
								  VARIANT_FALSE,
								  &pWorkAxis);

		OnErrorReturn(FAILED(hResult), hResult);
		

		// Create a workplane inclined to XZ (-30 deg)

		CComPtr<WorkPlane> pWorkPlane3;
		hResult = pWorkPlanes->AddByLinePlaneAndAngle(pWorkAxis,
											pWorkPlane2,
											CComVariant("-30.0deg"),
											VARIANT_FALSE,
											&pWorkPlane3);
		OnErrorReturn(FAILED(hResult), hResult);

		// Draw some sketch lines and sketch arc for railings
		
		// Setup sketch plane on workplane4


		CComPtr<PlanarSketch> pSketch6;
		hResult = pSketches->Add(pWorkPlane3, VARIANT_FALSE, &pSketch6);
		OnErrorReturn(FAILED(hResult), hResult);
	
		// Get SketchLines collection
		
		CComPtr<Point> pPt1;
		hResult = pWorkPoint1->get_Point(&pPt1); 
		OnErrorReturn(FAILED(hResult), hResult);
		

		CComPtr<Point> pPt2;
		hResult = pWorkPoint2->get_Point(&pPt2); 
		OnErrorReturn(FAILED(hResult), hResult);

		CComPtr<Point2d> p2dPt1;
		hResult=pSketch6->ModelToSketchSpace(pPt1,&p2dPt1);
		OnErrorReturn(FAILED(hResult), hResult);


		CComPtr<Point2d> p2dPt2;
		hResult=pSketch6->ModelToSketchSpace(pPt2,&p2dPt2);
		OnErrorReturn(FAILED(hResult), hResult);
		


		// create point at 10,15
		CComPtr<Point2d> pMidPt;
		hResult = pTg->CreatePoint2d(10,-15,&pMidPt) 	;
		OnErrorReturn(FAILED(hResult), hResult);	


		CComPtr<SketchLines> pSkLines;
		hResult = pSketch6->get_SketchLines(&pSkLines) ;
		OnErrorReturn(FAILED(hResult), hResult);


		CComPtr<SketchLine> pSkLine1;	
		hResult = pSkLines->AddByTwoPoints(p2dPt1, pMidPt, &pSkLine1);
		OnErrorReturn(FAILED(hResult), hResult);	

		CComPtr<SketchPoint> pSkPt1;	
		hResult=pSkLine1->get_EndSketchPoint(&pSkPt1); 
		OnErrorReturn(FAILED(hResult), hResult);	

		CComPtr<SketchLine> pSkLine2;	
		hResult = pSkLines->AddByTwoPoints(pSkPt1, p2dPt2, &pSkLine2);
		OnErrorReturn(FAILED(hResult), hResult);	

		
		// Create fillet sketch ARC betwn Skline1 and Skline2 with rad = 50

		CComPtr<SketchArcs> pSkArcs;
		hResult = pSketch6->get_SketchArcs(&pSkArcs) ;
		OnErrorReturn(FAILED(hResult), hResult);

		CComQIPtr<SketchEntity> pSkEnt1(pSkLine1);
		CComQIPtr<SketchEntity> pSkEnt2(pSkLine2);

		CComPtr<SketchArc> pSkArc;
		hResult =pSkArcs->AddByFillet(pSkEnt1,
									  pSkEnt2,
									  CComVariant("50mm"),
									  p2dPt1,
									  p2dPt2 ,
									  &pSkArc);
		OnErrorReturn(FAILED(hResult), hResult);

		// Get intersection point between workplane2 and SkArc
		CComPtr<WorkPoint> pWorkPoint3;
		hResult = pWorkPoints->AddByCurveAndEntity(pSkArc,
												   pWorkPlane1,
												   vtMissing,
												   VARIANT_FALSE,
												   &pWorkPoint3); 	
		OnErrorReturn(FAILED(hResult), hResult);
		
		// Now setup the sketch plane on workplane1 ( YZ)

		CComPtr<PlanarSketch> pSketch7;
		hResult = pSketches->Add(pWorkPlane1, VARIANT_FALSE, &pSketch7);
		OnErrorReturn(FAILED(hResult), hResult);

		// Draw a circle at offset from WorkPoint3
		
		// convert workpoint3 to sketch space
		CComPtr<Point> pPt;
		hResult=pWorkPoint3->get_Point(&pPt); 
		OnErrorReturn(FAILED(hResult), hResult);

		CComPtr<Point2d> pCenPt;
		hResult=pSketch7->ModelToSketchSpace(pPt,&pCenPt); 
		OnErrorReturn(FAILED(hResult), hResult);
		double dXval=0.0;
		hResult =pCenPt->get_X(&dXval);			
		OnErrorReturn(FAILED(hResult), hResult);

		hResult =pCenPt->put_X(dXval+1.0);
		OnErrorReturn(FAILED(hResult), hResult);
		// Create circle of rad 10 at above point

		CComPtr<SketchCircles>  pSkCirs;
		hResult=pSketch7->get_SketchCircles(&pSkCirs); 
		OnErrorReturn(FAILED(hResult), hResult);
		
		CComPtr<SketchCircle>  pSkCir;
		hResult=pSkCirs->AddByCenterRadius(pCenPt, 1.0, &pSkCir);
	    OnErrorReturn(FAILED(hResult), hResult);

		// Ready to create loft feature

		// First create base loft feature
		
	
		// Create collection object to hold sections (profiles)
		CComPtr<TransientObjects> pTrObjs;
		hResult=m_pApplication->get_TransientObjects(&pTrObjs); 		
		OnErrorReturn(FAILED(hResult), hResult);
		
		CComPtr<ObjectCollection> pBaseColl;
		hResult=pTrObjs->CreateObjectCollection(vtMissing,&pBaseColl); 
		OnErrorReturn(FAILED(hResult), hResult);


		CComPtr<Profiles> pProfiles;
		hResult= pSketch1->get_Profiles(&pProfiles);  
		OnErrorReturn(FAILED(hResult), hResult);

		CComPtr<Profile> pProfile;
		hResult= pProfiles->AddForSolid(VARIANT_TRUE, vtMissing, vtMissing, &pProfile); 
		OnErrorReturn(FAILED(hResult), hResult);

		hResult=pBaseColl->Add(pProfile);
		OnErrorReturn(FAILED(hResult), hResult);

		pProfiles=NULL;
		hResult= pSketch3->get_Profiles(&pProfiles);  
		OnErrorReturn(FAILED(hResult), hResult);

		pProfile=NULL;
		hResult= pProfiles->AddForSolid(VARIANT_TRUE, vtMissing, vtMissing, &pProfile); 
		OnErrorReturn(FAILED(hResult), hResult);

		hResult=pBaseColl->Add(pProfile);
		OnErrorReturn(FAILED(hResult), hResult);



		pProfiles=NULL;
		hResult= pSketch2->get_Profiles(&pProfiles);  
		OnErrorReturn(FAILED(hResult), hResult);

		pProfile=NULL;
		hResult= pProfiles->AddForSolid(VARIANT_TRUE, vtMissing, vtMissing, &pProfile); 
		OnErrorReturn(FAILED(hResult), hResult);

		hResult=pBaseColl->Add(pProfile);
		OnErrorReturn(FAILED(hResult), hResult);


		// Get LoftFeatures collection

		CComPtr<PartFeatures> pPartFeatures;
		hResult = pCompDef->get_Features(&pPartFeatures);
		OnErrorReturn(FAILED(hResult), hResult);

		CComPtr<LoftFeatures> pLoftFeatures;
		hResult=pPartFeatures->get_LoftFeatures(&pLoftFeatures);
		OnErrorReturn(FAILED(hResult), hResult);

		// Create the LoftDefinition
		CComPtr<LoftDefinition> pLoftDefinition;
		hResult = pLoftFeatures->CreateLoftDefinition(pBaseColl, kJoinOperation, &pLoftDefinition);
		OnErrorReturn(FAILED(hResult), hResult);

		// Specify the loft inputs
		hResult = pLoftDefinition->put_FirstSectionCondition(kFreeLoftCondition);
		OnErrorReturn(FAILED(hResult), hResult);

		hResult = pLoftDefinition->put_LastSectionCondition(kFreeLoftCondition);
		OnErrorReturn(FAILED(hResult), hResult);

		CComPtr<LoftFeature> pLoftFeature;
		hResult=pLoftFeatures->Add(pLoftDefinition, &pLoftFeature);
		OnErrorReturn(FAILED(hResult), hResult);


		// Now create second loft with railing


		// Create collection object to hold sections (profiles)
		
		CComPtr<ObjectCollection> pSecColl;
		hResult=pTrObjs->CreateObjectCollection(vtMissing,&pSecColl); 
		OnErrorReturn(FAILED(hResult), hResult);


		pProfiles=NULL;
		hResult= pSketch4->get_Profiles(&pProfiles);  
		OnErrorReturn(FAILED(hResult), hResult);

		pProfile=NULL;
		hResult= pProfiles->AddForSolid(VARIANT_TRUE, vtMissing, vtMissing, &pProfile); 
		OnErrorReturn(FAILED(hResult), hResult);

		hResult=pSecColl->Add(pProfile);
		OnErrorReturn(FAILED(hResult), hResult);


		pProfiles=NULL;
		hResult= pSketch7->get_Profiles(&pProfiles);  
		OnErrorReturn(FAILED(hResult), hResult);

		pProfile=NULL;
        hResult = pProfiles->AddForSolid(VARIANT_TRUE, vtMissing, vtMissing, &pProfile); 
		OnErrorReturn(FAILED(hResult), hResult);

		hResult=pSecColl->Add(pProfile);
		OnErrorReturn(FAILED(hResult), hResult);


		pProfiles=NULL;
		hResult= pSketch5->get_Profiles(&pProfiles);  
		OnErrorReturn(FAILED(hResult), hResult);

		pProfile=NULL;
        hResult = pProfiles->AddForSolid(VARIANT_TRUE, vtMissing, vtMissing, &pProfile); 
		OnErrorReturn(FAILED(hResult), hResult);

		hResult=pSecColl->Add(pProfile);
		OnErrorReturn(FAILED(hResult), hResult);


		// Create a profile for railing (from sketch6)
		pProfiles=NULL;
		hResult= pSketch6->get_Profiles(&pProfiles);  
		OnErrorReturn(FAILED(hResult), hResult);

		pProfile=NULL;
		hResult= pProfiles->AddForSurface(vtMissing, &pProfile); 
		OnErrorReturn(FAILED(hResult), hResult);


		// Create collection for railings
		hResult = pLoftDefinition->put_Sections(pSecColl);
		OnErrorReturn(FAILED(hResult), hResult);

		CComPtr<LoftRails> pLoftRails;
		hResult = pLoftDefinition->get_LoftRails(&pLoftRails);
		OnErrorReturn(FAILED(hResult), hResult);

		hResult=pLoftRails->Add(pProfile, vtMissing, vtMissing);
		OnErrorReturn(FAILED(hResult), hResult);

		pLoftFeature=NULL;
		hResult=pLoftFeatures->Add(pLoftDefinition, &pLoftFeature);
		OnErrorReturn(FAILED(hResult), hResult);


		// Hide all workaxes, workplanes and workpoints

		long nWrkPts = 0;
		pWorkPoints->get_Count(&nWrkPts);
		
		for(long i = 1 ; i <= nWrkPts ; i++)
		{
			CComPtr<WorkPoint> pWrkpt;
			hResult=pWorkPoints->get_Item(CComVariant(i),&pWrkpt) ;
			OnErrorReturn(FAILED(hResult), hResult);
			hResult=pWrkpt->put_Visible(VARIANT_FALSE);
			OnErrorReturn(FAILED(hResult), hResult);
		}




		long nWrkPlanes = 0;
		pWorkPlanes->get_Count(&nWrkPlanes);
		
		for(long i = 1 ; i <= nWrkPlanes ; i++)
		{
			CComPtr<WorkPlane> pWrkpl;
			hResult=pWorkPlanes->get_Item(CComVariant(i),&pWrkpl) ;
			OnErrorReturn(FAILED(hResult), hResult);
			hResult=pWrkpl->put_Visible(VARIANT_FALSE);
			OnErrorReturn(FAILED(hResult), hResult);
		}


		hResult=pWorkAxis->put_Visible(VARIANT_FALSE); 
		OnErrorReturn(FAILED(hResult), hResult);
		
	}

	return (S_OK) ;
}

void CloftWithRailingsAddInServer::InsertControlInMenuBar(const CString intEnvName)
{
	ATLASSERT(m_pApplication);
	ATLASSERT(m_pAddInSite);

	CComPtr<CommandBarBase> pCmdBarDef;

	CComPtr<UserInterfaceManager> pUserInterfaceMgr;
	HRESULT hr = m_pApplication->get_UserInterfaceManager(&pUserInterfaceMgr);
	ATLASSERT(SUCCEEDED(hr));

	CComPtr<CommandBars> pCmdBars;
	hr = pUserInterfaceMgr->get_CommandBars(&pCmdBars);
	ATLASSERT(SUCCEEDED(hr));

	CComVariant vtAddInId(L"{37E7CBC7-F0F7-455B-85B4-668E0674C9DE}");
	CComBSTR InternalNameBSTR(L"LoftWithRailingsCmdBar_InternalName1");
	CComBSTR displayNameBSTR(L"Loft With Railings");

	CComPtr<CommandBar> pCmdBar;
	hr = pCmdBars->get_Item(CComVariant(InternalNameBSTR),&pCmdBar);

	if (hr != S_OK || pCmdBar == NULL){
		hr = pCmdBars->Add(displayNameBSTR,InternalNameBSTR,kPopUpCommandBar,vtAddInId,&pCmdBar);
		ATLASSERT(SUCCEEDED(hr));

		CComPtr<CommandBarControls> pCmdBarControls; 
		hr = pCmdBar->get_Controls(&pCmdBarControls) ;
		ATLASSERT(SUCCEEDED(hr)); 

		CComPtr<CommandBarControl> pCmdBarBtnCtrl; 
		hr = pCmdBarControls->AddButton(m_pBtnDef1, 0, &pCmdBarBtnCtrl) ; 
		ATLASSERT(SUCCEEDED(hr));	
	}
	
	CComPtr<Environments> pEnvs;
	hr = pUserInterfaceMgr->get_Environments(&pEnvs);
	ATLASSERT(SUCCEEDED(hr));

	CComPtr<Environment> pEnv;
	CComVariant vt(intEnvName);
	hr = pEnvs->get_Item(vt, &pEnv);
	ATLASSERT(SUCCEEDED(hr));

	CComPtr<CommandBar> pDefMenuBar;
	hr = pEnv->get_DefaultMenuBar(&pDefMenuBar);
	ATLASSERT(SUCCEEDED(hr));

	CComPtr<CommandBarControls> pDefMenuBarControls; 
	hr = pDefMenuBar->get_Controls(&pDefMenuBarControls) ;
	ATLASSERT(SUCCEEDED(hr)); 

	long lBefore = 4;
	hr = pDefMenuBarControls->AddPopup(pCmdBar,lBefore);
	ATLASSERT(SUCCEEDED(hr));	
}

void CloftWithRailingsAddInServer::InsertControlsInMenuBars()
{
	ATLASSERT(m_pApplication);
	ATLASSERT(m_pAddInSite);

	InsertControlInMenuBar(CString(L"FWxMainFrameEnvironment"));
	InsertControlInMenuBar(CString(L"AMxAssemblyEnvironment"));
	InsertControlInMenuBar(CString(L"DLxDrawingEnvironment"));
	InsertControlInMenuBar(CString(L"DXxPresentationEnvironment"));
	InsertControlInMenuBar(CString(L"PMxPartEnvironment"));
}

/////////////////////////////////////////////////////////////////////////////
// CButtonDefEvents

IMPLEMENT_DYNCREATE(CButtonDefEvents, CCmdTarget)

CButtonDefEvents::CButtonDefEvents(CloftWithRailingsAddInServer* pAddIn, UINT nID) : m_pAddIn(pAddIn), m_nID(nID)
{
   EnableAutomation();  // Needed in order to sink events.
}

CButtonDefEvents::~CButtonDefEvents()
{
}


BEGIN_MESSAGE_MAP(CButtonDefEvents, CCmdTarget)
	//{{AFX_MSG_MAP(CButtonDefEvents)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CButtonDefEvents, CCmdTarget)
	DISP_FUNCTION_ID(CButtonDefEvents, "OnExecute", 0x03009c81, OnExecuteEvent, VT_EMPTY, VTS_DISPATCH)
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CButtonDefEvents, CCmdTarget)
	INTERFACE_PART(CButtonDefEvents, DIID_ButtonDefinitionSink, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonDefEvents event handlers

void CButtonDefEvents::OnExecuteEvent(NameValueMap *context) 
{
	if(m_pAddIn)
		m_pAddIn->ExecuteCommand(m_nID);
}
