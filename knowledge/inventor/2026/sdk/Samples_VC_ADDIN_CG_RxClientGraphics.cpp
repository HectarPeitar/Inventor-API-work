/*
	DESCRIPTION

	Sample code demonstrating the use of the Client Graphics API.
*/

#include "stdafx.h"
#include <math.h>

#include "RxClientGraphics.h"
#include "ClientGraphics.h"

#include "safearrayutil.h"
#include "AfxCtl.h"

CComPtr<TransientGeometry> g_pTransientGeometry;

// The addin wizard adds command id definitions here.
#define CMD_DrawSquare			0
#define CMD_DrawVonKoch			1
#define CMD_DrawCircle			2
#define CMD_SharedCoords		3
#define CMD_DrawTriangles		4
#define CMD_GraphicsStrips		5
#define CMD_DrawSymbol			6
#define CMD_MoveGraphics		7
#define CMD_ShowGraphics		8
#define CMD_HideGraphics		9
#define CMD_ClearAll			10


/*--------------------- IUnknown-interface related implementation	--------------------------------*/

/*
 * All of the standard IUnknown interfaces are taken care of in the CUnknown
 * class. The implementation in the CUnknown class relies on this override that
 * should end up looking like a non-delegating QueryInterface, except for the fact that QI
 * for the IUnknown is also taken care of by CUnknown (control will never reach here if
 * QI-ed for IUnknown).
 */

HRESULT CRxClientGraphics::InternalQueryInterface(REFIID riid, void** ppv)
{
	OnErrorReturn(!ppv, E_INVALIDARG);
	*ppv = NULL;

	if (IsEqualIID(riid, __uuidof(IRxApplicationAddInServer)))
		*ppv = static_cast<IRxApplicationAddInServer*>(this);

	if (*ppv)
		static_cast<IUnknown*>(*ppv)->AddRef();

	return *ppv ? S_OK : E_NOINTERFACE;
}

/*---------------------- Constructor(s), initializers and destructor ---------------------------------*/

CRxClientGraphics::CRxClientGraphics () : CUnknown (NULL)
{
	m_pSite = NULL;

	//////////////////////////
	// Set up our client ID //
	//////////////////////////
	CString clientID = _T("{2DE8EAA8-56D3-11d5-8E36-0010B547BBF8}");
	m_clientId = clientID;
	m_clientIdVariant.SetString(clientID, VT_BSTR);

	m_pButtonEvents1  = new CButtonDefEvents(this, CMD_DrawSquare);
	m_pButtonEvents2  = new CButtonDefEvents(this, CMD_DrawVonKoch);
	m_pButtonEvents3  = new CButtonDefEvents(this, CMD_DrawCircle);
	m_pButtonEvents4  = new CButtonDefEvents(this, CMD_SharedCoords);
	m_pButtonEvents5  = new CButtonDefEvents(this, CMD_DrawTriangles);
	m_pButtonEvents6  = new CButtonDefEvents(this, CMD_GraphicsStrips);
	m_pButtonEvents7  = new CButtonDefEvents(this, CMD_DrawSymbol);
	m_pButtonEvents8  = new CButtonDefEvents(this, CMD_MoveGraphics);
	m_pButtonEvents9  = new CButtonDefEvents(this, CMD_ShowGraphics);
	m_pButtonEvents10 = new CButtonDefEvents(this, CMD_HideGraphics);
	m_pButtonEvents11 = new CButtonDefEvents(this, CMD_ClearAll);
	
	m_btnDefCookie1  = 0;
	m_btnDefCookie2  = 0;
	m_btnDefCookie3  = 0;
	m_btnDefCookie4  = 0;
	m_btnDefCookie5  = 0;
	m_btnDefCookie6  = 0;
	m_btnDefCookie7  = 0;
	m_btnDefCookie8  = 0;
	m_btnDefCookie9  = 0;
	m_btnDefCookie10 = 0;
	m_btnDefCookie11 = 0;

	::IncrementObjectCount();
}

CRxClientGraphics::~CRxClientGraphics()
{
	AFX_MANAGE_STATE (AfxGetAppModuleState());
	
	if(m_pButtonEvents1)
		delete m_pButtonEvents1;

	if(m_pButtonEvents2)
		delete m_pButtonEvents2;

	if(m_pButtonEvents3)
		delete m_pButtonEvents3;

	if(m_pButtonEvents4)
		delete m_pButtonEvents4;

	if(m_pButtonEvents5)
		delete m_pButtonEvents5;

	if(m_pButtonEvents6)
		delete m_pButtonEvents6;

	if(m_pButtonEvents7)
		delete m_pButtonEvents7;

	if(m_pButtonEvents8)
		delete m_pButtonEvents8;

	if(m_pButtonEvents9)
		delete m_pButtonEvents9;

	if(m_pButtonEvents10)
		delete m_pButtonEvents10;

	if(m_pButtonEvents11)
		delete m_pButtonEvents11;


	m_pBtnDef1  = NULL;
	m_pBtnDef2  = NULL;
	m_pBtnDef3  = NULL;
	m_pBtnDef4  = NULL;
	m_pBtnDef5  = NULL;
	m_pBtnDef6  = NULL;
	m_pBtnDef7  = NULL;
	m_pBtnDef8  = NULL;
	m_pBtnDef9  = NULL;
	m_pBtnDef10 = NULL;
	m_pBtnDef11 = NULL;
	
	::DecrementObjectCount();
}

/*---------------------- IRxApplicationAddInServer interface ---------------------------------*/

HRESULT CRxClientGraphics::Activate (IRxApplicationAddInSite *pAddInSite, BooleanType bFirstTime)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr = NOERROR;
	CComPtr<IUnknown>pAppUnk ;
	CComPtr<IUnknown>pCmdUnk ;
	variant_t vInTools(VARIANT_TRUE);

	// Addin wizard adds display names of commands here.
	m_commandMap[CMD_DrawSquare] = L"Draw Squares";
	m_commandMap[CMD_DrawVonKoch] = L"Draw von Koch Snowflake";
	m_commandMap[CMD_DrawCircle] = L"Draw Circle";
	m_commandMap[CMD_SharedCoords] = L"Shared Coordinates";
	m_commandMap[CMD_DrawTriangles] = L"Draw Cylinder";
	m_commandMap[CMD_GraphicsStrips] = L"Draw Graphics Strips";
	m_commandMap[CMD_DrawSymbol] = L"Draw Symbol";
	m_commandMap[CMD_MoveGraphics] = L"Move Graphics";
	m_commandMap[CMD_ShowGraphics] = L"Show Graphics";
	m_commandMap[CMD_HideGraphics] = L"Hide Graphics";
	m_commandMap[CMD_ClearAll] = L"Clear";


	// High-level interfaces supplied directly and implicitly by Inventor to the
	// AddIn. These may be held right up until the directive to shutdown (Deactivate) is received.

	m_pSite = pAddInSite;
	//m_pSite->AddRef();

	hr = pAddInSite->get_Application(&pAppUnk);
	OnErrorReturn(FAILED (hr),hr);

	hr = pAppUnk->QueryInterface(DIID_Application, (void **) &m_pApplication);
	OnErrorReturn(FAILED (hr), hr);


	hr = m_pApplication->get_TransientGeometry(&g_pTransientGeometry);

	CreateCommands();

	return hr;
}

// Deactivate the commands. This gets called after the last document is classed.

HRESULT CRxClientGraphics::Deactivate()
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());

	HRESULT hr = NOERROR;

	if(m_btnDefCookie1 !=0)
	{
		BOOL bUnadvised = AfxConnectionUnadvise(m_pBtnDef1, DIID_ButtonDefinitionSink,
										  m_pButtonEvents1->GetInterface(&IID_IUnknown),
										  TRUE, m_btnDefCookie1);
		m_btnDefCookie1 = 0;
	}

	if(m_btnDefCookie2 !=0)
	{
		BOOL bUnadvised = AfxConnectionUnadvise(m_pBtnDef2, DIID_ButtonDefinitionHandlerEventsSink,
										  m_pButtonEvents2->GetInterface(&IID_IUnknown),
										  TRUE, m_btnDefCookie2);
		m_btnDefCookie2 = 0;
	}

	if(m_btnDefCookie3 !=0)
	{
		BOOL bUnadvised = AfxConnectionUnadvise(m_pBtnDef3, DIID_ButtonDefinitionHandlerEventsSink,
										  m_pButtonEvents3->GetInterface(&IID_IUnknown),
										  TRUE, m_btnDefCookie3);
		m_btnDefCookie3 = 0;
	}

	if(m_btnDefCookie4 !=0)
	{
		BOOL bUnadvised = AfxConnectionUnadvise(m_pBtnDef4, DIID_ButtonDefinitionHandlerEventsSink,
										  m_pButtonEvents4->GetInterface(&IID_IUnknown),
										  TRUE, m_btnDefCookie4);
		m_btnDefCookie4 = 0;
	}

	if(m_btnDefCookie5 !=0)
	{
		BOOL bUnadvised = AfxConnectionUnadvise(m_pBtnDef5, DIID_ButtonDefinitionHandlerEventsSink,
										  m_pButtonEvents5->GetInterface(&IID_IUnknown),
										  TRUE, m_btnDefCookie5);
		m_btnDefCookie5 = 0;
	}

	if(m_btnDefCookie6 !=0)
	{
		BOOL bUnadvised = AfxConnectionUnadvise(m_pBtnDef6, DIID_ButtonDefinitionHandlerEventsSink,
										  m_pButtonEvents6->GetInterface(&IID_IUnknown),
										  TRUE, m_btnDefCookie6);
		m_btnDefCookie6 = 0;
	}

	if(m_btnDefCookie7 !=0)
	{
		BOOL bUnadvised = AfxConnectionUnadvise(m_pBtnDef7, DIID_ButtonDefinitionHandlerEventsSink,
										  m_pButtonEvents7->GetInterface(&IID_IUnknown),
										  TRUE, m_btnDefCookie7);
		m_btnDefCookie7 = 0;
	}

	if(m_btnDefCookie8 !=0)
	{
		BOOL bUnadvised = AfxConnectionUnadvise(m_pBtnDef8, DIID_ButtonDefinitionHandlerEventsSink,
										  m_pButtonEvents8->GetInterface(&IID_IUnknown),
										  TRUE, m_btnDefCookie8);
		m_btnDefCookie8 = 0;
	}

	if(m_btnDefCookie9 !=0)
	{
		BOOL bUnadvised = AfxConnectionUnadvise(m_pBtnDef9, DIID_ButtonDefinitionHandlerEventsSink,
										  m_pButtonEvents9->GetInterface(&IID_IUnknown),
										  TRUE, m_btnDefCookie9);
		m_btnDefCookie9 = 0;
	}

	if(m_btnDefCookie10 !=0)
	{
		BOOL bUnadvised = AfxConnectionUnadvise(m_pBtnDef10, DIID_ButtonDefinitionHandlerEventsSink,
										  m_pButtonEvents10->GetInterface(&IID_IUnknown),
										  TRUE, m_btnDefCookie10);
		m_btnDefCookie10= 0;
	}

	if(m_btnDefCookie11 !=0)
	{
		BOOL bUnadvised = AfxConnectionUnadvise(m_pBtnDef11, DIID_ButtonDefinitionHandlerEventsSink,
										  m_pButtonEvents11->GetInterface(&IID_IUnknown),
										  TRUE, m_btnDefCookie11);
		m_btnDefCookie11 = 0;
	}

	m_pBtnDef1 = NULL;
	m_pBtnDef2 = NULL;
	m_pBtnDef3 = NULL;
	m_pBtnDef4 = NULL;
	m_pBtnDef5 = NULL;
	m_pBtnDef6 = NULL;
	m_pBtnDef7 = NULL;
	m_pBtnDef8 = NULL;
	m_pBtnDef9 = NULL;
	m_pBtnDef10 = NULL;
	m_pBtnDef11 = NULL;

	// Cleanup up of interfaces supplied by Inventor and held on by this AddIn
	// at initialization or load.
	g_pTransientGeometry = NULL;
	m_pApplication = NULL;
	m_pSite = NULL;

	return hr;
}

//////////////////////
// Transform Groups //
///////////////////////////////////////////////////////////////////////////////
// Creates a tranformation matrix with a translation that move all existing
// graphics nodes in the direction of the y-axis.  This is useful for moving
// already created client graphics out of the way before you add new client
// graphics to a scene.
HRESULT CRxClientGraphics::TransformGroups()
{
	HRESULT hr = NOERROR;

	OnErrorReturn(!g_pTransientGeometry, E_FAIL);

	long count = 0;
	hr = m_rClientGraphics->get_Count(&count);

	for (int i = 1; i <= count; i++)
	{
		CComPtr<GraphicsNode> pGroup;
		m_rClientGraphics->get_Item(i, &pGroup);

		// Create a translation matrix
		CComPtr<Matrix> pNewTransform;
		CComPtr<Vector> pTranslation;
		g_pTransientGeometry->CreateMatrix(&pNewTransform);
		g_pTransientGeometry->CreateVector(0, 1, 0, &pTranslation);
		if (pTranslation && pTranslation)
			pNewTransform->SetTranslation(pTranslation, false);

		CComPtr<Matrix> pTransform;
		CSafeArray<double, VT_R8> matrixArray;
		hr = pGroup->get_Transformation(&pTransform);
		pTransform->GetMatrixData(&(matrixArray.m_psa));
		double *pTempData = matrixArray.DataBase();

		hr = pTransform->MultiplyBy(pNewTransform);
		hr = pGroup->put_Transformation(pTransform);
	}

	return hr;
}

//////////////////
// Draw Squares //
///////////////////////////////////////////////////////////////////////////////
// Creates to squares by adding a triangle strip with strip lengths set for
// two triangle strips of four vertices (two triangles) each.  The first triangle
// in each strip takes three vertices and each additional triangle takes an additional
// vertex.  See DrawGraphicsStrips for another example of this.  This example also
// shows how to add data to a GraphicsDataSet one at a time or all at once (in an array).
// The colors are added one at a time while the coordinates are added all at once.
HRESULT CRxClientGraphics::DrawSquares()
{
	HRESULT hr = NOERROR;

	int baseId = 100;
	int coordSetId = 555;

	// Create a new group
	// Create coordinates
	// Add a primitive (e.g. TriStrip) to the group
	// Set the  coordinates for the group.

	CComPtr<GraphicsNode> pNode;
	CComPtr<GraphicsCoordinateSet> pCoordinates;
	CComPtr<GraphicsColorSet> pColors;
	CComPtr<TriangleStripGraphics> pTriangles;

	const int coordArrayLength = 24;
	double coordArray[coordArrayLength] =
			{0, 0, 0,
			 0, -1, 0,
			 1, 0, 0,
			 1, -1, 0,
			 2, 0, 0,
			 2, -1, 0,
			 3, 0, 0,
			 3, -1, 0};
	CSafeArray<double, VT_R8> coordData;
	coordData.SetData(coordArrayLength, coordArray);

	hr = m_rClientGraphics->AddNode(baseId++, &pNode);
	hr = pNode->AddTriangleStripGraphics(&pTriangles);

	hr = m_rGraphicsDataSets->CreateCoordinateSet(coordSetId, &pCoordinates);
	hr = pCoordinates->PutCoordinates(&(coordData.m_psa));
	hr = pTriangles->put_CoordinateSet(pCoordinates);

	const int numStrips = 2;
	long stripLengthArray[numStrips] = {4, 4}; // number of vertices in each strip.
	CSafeArray<long, VT_I4> stripLengths;
	stripLengths.SetData(numStrips, stripLengthArray);
	hr = pTriangles->PutStripLengths(&(stripLengths.m_psa));

	// Use per item (triangle) colors so we can see the triangles.
	hr = m_rGraphicsDataSets->CreateColorSet(baseId++, &pColors);
	hr = pColors->Add(1, 255, 255, 255);
	hr = pColors->Add(2, 0, 0, 0);
	hr = pColors->Add(3, 255, 255, 255);
	hr = pColors->Add(4, 255, 0, 0);
	hr = pColors->Add(5, 0, 0, 255);
	hr = pColors->Add(6, 255, 255, 0);
	hr = pTriangles->put_ColorSet(pColors);
	hr = pTriangles->put_ColorBinding(kPerItemColors);

	hr = pTriangles->put_DepthPriority(4);

	CSafeArray<long, VT_I4> returnedLengths;
	hr = pTriangles->GetStripLengths(&(returnedLengths.m_psa));
	long returnedLength = 0;
	returnedLengths.Length(returnedLength);
	for (int returnedIndex=0; returnedIndex<returnedLength; ++returnedIndex)
	{
		int strip = returnedLengths[returnedIndex];
	}

	hr = pNode->put_Id(400);

	return hr;
}

///////////////////
// Draw Von Koch //
///////////////////////////////////////////////////////////////////////////////
// Creates a von Koch snowflake with replaces each line in a set of lines with
// four new lines.  Each time the function is run it retrieves the coordinates for
// the first line strip under a graphics node and uses those coordinates as the
// basis for the next iteration of the snowflake.  Show line graphics and
// coordinate retrieval and editing.
HRESULT CRxClientGraphics::DrawVonKoch()
{
	HRESULT hr = NOERROR;

	const int VON_KOCH_NODE_ID = 123456;
	CComPtr<GraphicsNode> pVonKochNode;
	hr = m_rClientGraphics->get_ItemById(VON_KOCH_NODE_ID, &pVonKochNode);

	// If we haven't created a node for our snowflake yet we should create it now
	// and add a single line to get things started.
	if (FAILED(hr) || !pVonKochNode)
	{
		hr = m_rClientGraphics->AddNode(VON_KOCH_NODE_ID, &pVonKochNode);

		CComPtr<GraphicsCoordinateSet> pCoordinates;
		m_rGraphicsDataSets->CreateCoordinateSet(CMD_DrawVonKoch, &pCoordinates);

		if (SUCCEEDED(hr) && pCoordinates)
		{
			float start = 0;
			float end = 1;

			CComPtr<Point> pStartVertex, pEndVertex;
			g_pTransientGeometry->CreatePoint(0, 0, 0, &pStartVertex);
			pCoordinates->Add(1, pStartVertex);
			g_pTransientGeometry->CreatePoint(1, 0, 0, &pEndVertex);
			pCoordinates->Add(2, pEndVertex);

			CComPtr<LineGraphics> pLineSet;
			hr = pVonKochNode->AddLineGraphics(&pLineSet);
			hr = pLineSet->put_CoordinateSet(pCoordinates);

			CComPtr<GraphicsColorSet> pColors;
			m_rGraphicsDataSets->CreateColorSet(CMD_DrawVonKoch, &pColors);
			pColors->Add(1, 126, 0, 255);
			hr = pLineSet->put_ColorSet(pColors);
			hr = pLineSet->put_ColorBinding(kOverallColor);
		}
	}
	else
	{
		long count = 0;
		hr = pVonKochNode->get_Count(&count);

		if (count > 0)
		{
			CComQIPtr<GraphicsPrimitive> pGraphicSet;
			pVonKochNode->get_Item(1, &pGraphicSet);

			CComQIPtr<LineGraphics> pLineGraphicSet = pGraphicSet;
			if (pLineGraphicSet)
			{
				CComPtr<GraphicsCoordinateSet> pLineCoords;
				pLineGraphicSet->get_CoordinateSet(&pLineCoords);

				CComPtr<GraphicsCoordinateSet> pNewCoords;
				hr = m_rGraphicsDataSets->CreateCoordinateSet(2*CMD_DrawVonKoch, &pNewCoords);

				long coordCount = 0;
				pLineCoords->get_Count(&coordCount);

				double *coordArray = new double [coordCount*4*3];

				for (int i=1; i+1<=coordCount; i+=2)
				{
					double s[3];
					double e[3];
					double d[3];
					double p1[3];
					double p2[3];
					double p3[3];
					double u[3];
					CComPtr<Point> pstartVertex, pendVertex;
					pLineCoords->get_Coordinate(i, &pstartVertex);
					pLineCoords->get_Coordinate(i+1, &pendVertex);

					hr = pstartVertex->get_X(&s[0]);
					hr = pstartVertex->get_Y(&s[1]);
					hr = pstartVertex->get_Z(&s[2]);

					hr = pendVertex->get_X(&e[0]);
					hr = pendVertex->get_Y(&e[1]);
					hr = pendVertex->get_Z(&e[2]);

					d[0] = e[0]-s[0]; d[1] = e[1]-s[1]; d[2] = e[2]-s[2]; // direction vector
					u[0] = -d[1]; u[1] = d[0]; u[2] = 0; // cross product of z-axis and d.

					p1[0] = s[0]+d[0]/3.0; p1[1] = s[1]+d[1]/3.0; p1[2] = s[2]+d[2]/3.0;
					p2[0] = s[0]+(d[0]/2.0)+(u[0]/3.0); p2[1] = s[1]+(d[1]/2.0)+(u[1]/3.0); p2[2] = s[2]+(d[2]/2.0)+(u[2]/3.0);
					p3[0] = s[0] + 2.0*d[0]/3.0; p3[1] = s[1]+2.0*d[1]/3.0; p3[2] = s[2]+2.0*d[2]/3.0;

					int c=0;
					int end=0;

					// Add start point s
					for (end=c+3; c<end; ++c)
						coordArray[12*(i-1)+c] = s[3-(end-c)];

					// Add p1
					for (end=c+3; c<end; ++c) //-V760
						coordArray[12*(i-1)+c] = p1[3-(end-c)];

					// Add p1
					for (end=c+3; c<end; ++c)
						coordArray[12*(i-1)+c] = p1[3-(end-c)];

					// Add p2
					for (end=c+3; c<end; ++c) //-V760
						coordArray[12*(i-1)+c] = p2[3-(end-c)];

					// Add p2
					for (end=c+3; c<end; ++c)
						coordArray[12*(i-1)+c] = p2[3-(end-c)];

					// Add p3
					for (end=c+3; c<end; ++c) //-V760
						coordArray[12*(i-1)+c] = p3[3-(end-c)];

					// Add p3
					for (end=c+3; c<end; ++c)
						coordArray[12*(i-1)+c] = p3[3-(end-c)];

					// Add end point
					for (end=c+3; c<end; ++c)
						coordArray[12*(i-1)+c] = e[3-(end-c)];
				}

				CSafeArray<double, VT_R8> coordData;
				coordData.SetData(coordCount*12, coordArray);
				pNewCoords->PutCoordinates(&(coordData.m_psa));
				delete [] coordArray;

				pLineGraphicSet->put_CoordinateSet(pNewCoords);
			}
		}
	}

	return hr;
}

/////////////////
// Draw Circle //
///////////////////////////////////////////////////////////////////////////////
// Adds a circle as a line strip and then adds a text label anchored at a corner
// point of the bounding box for the circle and marks some of the vertices
// with points.  Shows line strip graphics, text graphics, and point graphics.
HRESULT CRxClientGraphics::DrawCircle()
{
	HRESULT hr = NOERROR;

	// Create a new group.
	CComPtr<GraphicsNode> pGroup;
	hr = m_rClientGraphics->AddNode(1, &pGroup);

	CComPtr<LineStripGraphics> pLines;
	hr = pGroup->AddLineStripGraphics(&pLines);

	CComPtr<GraphicsDataSet> pDataSet;
	CComQIPtr<GraphicsColorSet> pColorSet;
	// Look for an existing color set with an id of 0.
	// If you don't find one, create a new one.
	hr = m_rGraphicsDataSets->get_ItemById(0, &pDataSet);
	if (SUCCEEDED(hr))
	{
		long id = -1;
		hr = pDataSet->get_Id(&id);

		pColorSet = pDataSet;
	}

	if (!pColorSet)
	{
		m_rGraphicsDataSets->CreateColorSet(1, &pColorSet);
		hr = pColorSet->Add(1, 0, 255, 0);
	}

	hr = pLines->put_ColorSet(pColorSet);
	hr = pLines->put_ColorBinding(kOverallColor);

	CComPtr<GraphicsCoordinateSet> pCoordinates;
	m_rGraphicsDataSets->CreateCoordinateSet(1, &pCoordinates);
	hr = pLines->put_CoordinateSet(pCoordinates);

	// Create a circle.
	const float PI = 3.14159265358979f;
	const int NUM_VERTS = 16;
	float alphaDelta = 2*PI / (float)NUM_VERTS;
	float firstX = 0;
	float firstY = 0;

	int index = 1;
	for (float alpha = 0; alpha < 2*PI; alpha += alphaDelta)
	{
		float x = (float)(.5 * cos(alpha));
		float y = (float)(.5 * sin(alpha));

		CComPtr<Point> rVertex;
		g_pTransientGeometry->CreatePoint(x, y, 0, &rVertex);
		hr = pCoordinates->Add(index++, rVertex);

		if (alpha == 0)
		{
			firstX = x;
			firstY = y;
		}
	}

	// Close the loop.
	CComPtr<Point> rVertex;
	g_pTransientGeometry->CreatePoint(firstX, firstY, 0, &rVertex);
	hr = pCoordinates->Add(index++, rVertex);

	CComPtr<Box> rangeBox;
	pLines->get_RangeBox(&rangeBox);

	CComPtr<Point> rAnchor;
	rangeBox->get_MaxPoint(&rAnchor);

	// Add some text
	CComPtr<TextGraphics> rLabel;
	hr = pGroup->AddTextGraphics(&rLabel);
	hr = rLabel->PutTextColor(0, 0, 255);

	CComBSTR labelString = _T("Circle");
	hr = rLabel->put_Text(labelString);
	hr = rLabel->put_Anchor(rAnchor);

	hr = rLabel->put_VerticalAlignment(kAlignTextLower);
	hr = rLabel->put_HorizontalAlignment(kAlignTextLeft);

	// Add some points
	CComPtr<PointGraphics> rPoints;
	hr = pGroup->AddPointGraphics(&rPoints);

	rPoints->put_CoordinateSet(pCoordinates);
	hr = rPoints->put_PointRenderStyle(kNoSnapPointStyle);
	hr = rPoints->put_DepthPriority(2);
	rangeBox.Detach();
	hr = rPoints->get_RangeBox(&rangeBox);

	CComPtr<GraphicsIndexSet> rPointIndices;
	m_rGraphicsDataSets->CreateIndexSet(CMD_DrawCircle*10+2, &rPointIndices);
	hr = rPoints->put_CoordinateIndexSet(rPointIndices);
	float quarterLength = NUM_VERTS/4.0;
	hr = rPointIndices->Add(1, 1);
	hr = rPointIndices->Add(2, (long)(quarterLength + 1.5));
	hr = rPointIndices->Add(3, (long)(2*quarterLength + 1.5));
	hr = rPointIndices->Add(4,(long)(3*quarterLength + 1.5));

	return hr;
}

////////////////////////
// Draw Shared Coords //
///////////////////////////////////////////////////////////////////////////////
// Creates a square with a triangle set and a line set that borders the square.
// Both the triangles and lines share the same coordinate set.  Then the entire
// graphics node is copied with a transform.
HRESULT CRxClientGraphics::DrawSharedCoords()
{
	HRESULT hr = NOERROR;

	// Create a new group.
	CComPtr<GraphicsNode> pGroup;
	hr = m_rClientGraphics->AddNode(CMD_SharedCoords, &pGroup);

	// Add line and triangle sets
	CComPtr<LineGraphics> pLineSet;
	hr = pGroup->AddLineGraphics(&pLineSet);

	CComPtr<TriangleGraphics> pTriSet;
	hr = pGroup->AddTriangleGraphics(&pTriSet);

	CComPtr<GraphicsCoordinateSet> pCoordinates;
	hr = m_rGraphicsDataSets->CreateCoordinateSet(CMD_SharedCoords*10, &pCoordinates);

	double coordArray[18] =
	{
		0, 0, 0,
		0, 1, 0,
		1, 1, 0,
		0, 0, 0,
		1, 0, 0,
		1, 1, 0
	};

	CSafeArray<double, VT_R8> coordData;
	coordData.SetData(18, coordArray);
	pCoordinates->PutCoordinates(&(coordData.m_psa));
	hr = pTriSet->put_CoordinateSet(pCoordinates);

	CComPtr<GraphicsIndexSet> rLineIndices;
	m_rGraphicsDataSets->CreateIndexSet(CMD_SharedCoords+10, &rLineIndices);
	hr = pLineSet->put_CoordinateIndexSet(rLineIndices);

	int i = 1;
	rLineIndices->Add(i++, 1);
	rLineIndices->Add(i++, 2);
	rLineIndices->Add(i++, 2);
	rLineIndices->Add(i++, 3);
	rLineIndices->Add(i++, 3);
	rLineIndices->Add(i++, 5);
	rLineIndices->Add(i++, 5);
	rLineIndices->Add(i++, 1);

	hr = pLineSet->put_CoordinateSet(pCoordinates);

	CComPtr<GraphicsColorSet> rLineColors;
	hr = m_rGraphicsDataSets->CreateColorSet(CMD_SharedCoords*10 + 1, &rLineColors);
	hr = rLineColors->Add(1, 0, 0, 0);
	hr = pLineSet->put_ColorSet(rLineColors);
	hr = pLineSet->put_ColorBinding(kOverallColor);

	CComPtr<GraphicsColorSet> pColors;
	hr = m_rGraphicsDataSets->CreateColorSet(CMD_SharedCoords*10, &pColors);
	pColors->Add(1, 126, 0, 0);
	pColors->Add(2, 0, 0, 0);
	pColors->Add(3, 255, 0, 0);
	pColors->Add(4, 126, 0, 0);
	pColors->Add(5, 255, 126, 0);
	pColors->Add(6, 255, 0, 0);
	pTriSet->put_ColorSet(pColors);
	pTriSet->put_ColorBinding(kPerVertexColors);

	// Make a copy
	CComPtr<Matrix> rTransform;
	CComPtr<Vector> pTranslation;
	g_pTransientGeometry->CreateMatrix(&rTransform);
	g_pTransientGeometry->CreateVector(-1.1, 0, 0, &pTranslation);
	if (pTranslation && pTranslation)
		rTransform->SetTranslation(pTranslation, false);

	long nodeId = 2;
	CComPtr<GraphicsNode> rGroup;
	pGroup->Copy(rTransform, nodeId, &rGroup);

	// Make the first node selectable
	hr = pGroup->put_Selectable(VARIANT_TRUE);

	return hr;
}

///////////////////
// Draw Cylinder //
///////////////////////////////////////////////////////////////////////////////
// Creates a cylinder by adding a triangle strip for the main surface of the
// cylinder and two triange fans to form the end caps of the cylinder.  A
// line strip is also added to hilight one of the edges.  All of these graphics
// primitives share the same coordinate set that is made up of two circular sets of
// points and two center points.  A render style is also created for the cylinder.
HRESULT CRxClientGraphics::DrawCylinder()
{
	HRESULT hr = NOERROR;

	// Create a new group.
	CComPtr<GraphicsNode> pGroup;
	hr = m_rClientGraphics->AddNode(1, &pGroup);

	// Apply a render style to the cylinder
	static bool testRenderStyle = true;
	if (testRenderStyle)
	{
		CComPtr<RenderStyles> rRenderStyles;
		hr = m_rCurrentDoc->get_RenderStyles(&rRenderStyles);

		CComBSTR styleName = CString(_T("GraphicsTest"));
		COleVariant styleNameVariant(_T("GraphicsTest"));
		CComQIPtr<RenderStyle> rRenderStyle;

		// Get the style from the styles collection.
		hr = rRenderStyles->get_Item(styleNameVariant, &rRenderStyle);

		// If it doesn't yet exist, create it.
		if (FAILED(hr) || !rRenderStyle)
		{
			hr = rRenderStyles->Add(styleName, &rRenderStyle);
			if (SUCCEEDED(hr) && rRenderStyle)
			{
				rRenderStyle->SetDiffuseColor(200, 0, 0);
				rRenderStyle->SetSpecularColor(200, 0, 0);
			}
		}

		// Apply the style to the graphics node
		hr = pGroup->put_RenderStyle(rRenderStyle);

		CComPtr<RenderStyle> rReturnedStyle;
		hr = pGroup->get_RenderStyle(&rReturnedStyle);
		if (SUCCEEDED(hr) && rReturnedStyle)
		{
			unsigned char red, green, blue;
			red = green = blue = 0;
			hr = rReturnedStyle->GetDiffuseColor(&red, &green, &blue);
		}
	}

	// Create the color set(s)
	CComPtr<GraphicsColorSet> pColorset;
	hr = m_rGraphicsDataSets->CreateColorSet(CMD_DrawTriangles*10, &pColorset);
	hr = pColorset->Add(1, 0, 0, 255);
	hr = pColorset->Add(2, 255, 0, 0);

	// Create a coordinate sets and normals for a capped cylinder.
	// The same coordinate set will be used for the tri-strip covering
	// the sides of the cylinder, the two tri-fans that serve as the
	// top and bottom caps of the cylinder, and the two line strips
	// which represent the edges between the cylinder's faces.
	CComPtr<GraphicsCoordinateSet> pCoordinates;
	CComPtr<GraphicsNormalSet> pNormals;
	hr = m_rGraphicsDataSets->CreateCoordinateSet(CMD_DrawTriangles*10, &pCoordinates);
	hr = m_rGraphicsDataSets->CreateNormalSet(CMD_DrawTriangles*10+1, &pNormals);

	int numVertices = 32; // The number of vertices in the circles at each cap.
	const float PI = 3.14159265358979f;
	float alphaDelta = 2*PI / (float) numVertices;

	// Create a circle of points
	// =========================

	// Number of vertices at each end of cylinder multiplied by 3 (3 coords per vertex)
	const int coordArrayLength = (numVertices+1)*6;
	double *pCoordArray = new double [coordArrayLength];
	double *pNormalArray = new double [coordArrayLength];

	int index = 0;
	// Create the bottom center point
	pCoordArray[index] = 0;
	pCoordArray[index+1] = 0;
	pCoordArray[index+2] = 0;

	double firstNormal[3] = {0, 0, 0};

	index += 3;
	for (float alpha = 0; alpha < 2*PI-(alphaDelta*.1f); alpha += alphaDelta)
	{
		float x = (float)(.5 * cos(alpha));
		float y = 0;
		float z = (float)(.5 * sin(alpha));

		// Form the surface normals.  The index for the vertices is always three
		// ahead of the index for the normals.
		float l = sqrt(x*x + z*z);
		float nx = x / l;
		float nz = z / l;

		pNormalArray[index-3] = nx;
		pNormalArray[index-2] = 0;
		pNormalArray[index-1] = nz;
		pNormalArray[index] = nx;
		pNormalArray[index+1] = 0;
		pNormalArray[index+2] = nz;

		// Save the first normal so we can use it for the final set of vertices.
		if (alpha == 0)
		{
			firstNormal[0] = nx;
			firstNormal[1] = 0;
			firstNormal[2] = nz;
		}

		// Create the vertices at each cap
		pCoordArray[index] = x;
		pCoordArray[index+1] = y;
		pCoordArray[index+2] = z;

		pCoordArray[index+3] = x;
		pCoordArray[index+4] = 1;
		pCoordArray[index+5] = z;

		index += 6;
	}

	// The first two coordinates for the side will be repeated (in the index set)
	// so we need to repeat the first two normals.
	pNormalArray[index-3] = pNormalArray[index] = firstNormal[0];
	pNormalArray[index-2] = pNormalArray[index+1] = firstNormal[1];
	pNormalArray[index-1] = pNormalArray[index+2] = firstNormal[2];

	pCoordArray[index] = 0;
	pCoordArray[index+1] = 1;
	pCoordArray[index+2] = 0;

	CSafeArray<double, VT_R8> coordData;
	coordData.SetData(coordArrayLength, pCoordArray);
	hr = pCoordinates->PutCoordinates(&(coordData.m_psa));

	CSafeArray<double, VT_R8> normalData;
	normalData.SetData(coordArrayLength, pNormalArray);
	hr = pNormals->PutNormals(&(normalData.m_psa));

	delete [] pCoordArray;
	pCoordArray = NULL;
	delete [] pNormalArray;
	pNormalArray = NULL;

	// Create an index set for the tri-strip of the outside of the cylinder.
	// We need to do this because the full coordinate set includes two center
	// points at each cap that the tri-fans use but the tri-strip doesn't.
	CSafeArray<long, VT_I4> sideStripIndexArray;
	long sideStripIndexArrayLength = (numVertices+1)*2;
	long *pSideStripIndexData = new long [sideStripIndexArrayLength];

	CComPtr<GraphicsIndexSet> rSideStripIndices;
	hr = m_rGraphicsDataSets->CreateIndexSet(CMD_DrawTriangles*10+2, &rSideStripIndices);
	index = 0;
	for (int iSide = 2; iSide <= numVertices*2+1; iSide++)
		pSideStripIndexData[index++] = iSide;
	pSideStripIndexData[index++] = 2;
	pSideStripIndexData[index++] = 3;

	sideStripIndexArray.SetData(sideStripIndexArrayLength, pSideStripIndexData);
	hr = rSideStripIndices->PutIndices(&(sideStripIndexArray.m_psa));
	delete [] pSideStripIndexData;
	pSideStripIndexData = NULL;

	// Create index sets for the top and bottom caps so that they can use the
	// same coordinate set as the triangle strip.
	CSafeArray<long, VT_I4> capIndexArray;
	long capIndexArrayLength = numVertices + 2;
	long *pCapIndexData = new long [capIndexArrayLength];

	CComPtr<GraphicsIndexSet> rBottomCapIndices, rTopCapIndices;
	hr = m_rGraphicsDataSets->CreateIndexSet(CMD_DrawTriangles*10+1, &rBottomCapIndices);
	index = 0;
	pCapIndexData[index++] = 1;
	for (int iBottom = 2; iBottom <= numVertices*2; iBottom += 2)
		pCapIndexData[index++] = iBottom;
	pCapIndexData[index++] = 2;

	capIndexArray.SetData(capIndexArrayLength, pCapIndexData);
	hr = rBottomCapIndices->PutIndices(&(capIndexArray.m_psa));

	hr = m_rGraphicsDataSets->CreateIndexSet(CMD_DrawTriangles*10+2, &rTopCapIndices);
	index = 0;
	pCapIndexData[index++] = (numVertices+1)*2;
	for (int iTop = 3; iTop <= numVertices*2+1; iTop += 2)
		pCapIndexData[index++] = iTop;
	pCapIndexData[index++] = 3;

	capIndexArray.SetData(capIndexArrayLength, pCapIndexData);
	hr = rTopCapIndices->PutIndices(&(capIndexArray.m_psa));

	delete [] pCapIndexData;
	pCapIndexData = NULL;

	CComPtr<GraphicsNormalSet> rCapNormals;
	CComPtr<GraphicsIndexSet> rTopCapNormalIndex, rBottomCapNormalIndex;
	hr = m_rGraphicsDataSets->CreateNormalSet(CMD_DrawTriangles*10+3, &rCapNormals);
	hr = m_rGraphicsDataSets->CreateIndexSet(CMD_DrawTriangles*10+3, &rTopCapNormalIndex);
	hr = m_rGraphicsDataSets->CreateIndexSet(CMD_DrawTriangles*10+3, &rBottomCapNormalIndex);

	CComPtr<UnitVector> rTopNormal, rBottomNormal;
	hr = g_pTransientGeometry->CreateUnitVector(0, 1, 0, &rTopNormal);
	hr = g_pTransientGeometry->CreateUnitVector(0, -1, 0, &rBottomNormal);
	hr = rCapNormals->Add(1, rTopNormal);
	hr = rCapNormals->Add(2, rBottomNormal);

	hr = rTopCapNormalIndex->Add(1, 1);
	hr = rBottomCapNormalIndex->Add(1, 2);

	// Create a line strip for the bottom edge of the cylinder.
	CComPtr<GraphicsIndexSet> rBottomEdgeIndices, rEdgeColorIndices;
	hr = m_rGraphicsDataSets->CreateIndexSet(CMD_DrawTriangles*10+7, &rBottomEdgeIndices);
	hr = m_rGraphicsDataSets->CreateIndexSet(CMD_DrawTriangles*10+8, &rEdgeColorIndices);

	CSafeArray<long, VT_I4> edgeIndexArray;
	long edgeIndexArrayLength = numVertices + 1;
	long *pEdgeIndexData = new long [edgeIndexArrayLength];

	index = 0;
	for (int iEdgeIndex=2; iEdgeIndex <= 2*numVertices; iEdgeIndex += 2)
		pEdgeIndexData[index++] = iEdgeIndex;
	pEdgeIndexData[index++] = 2;

	edgeIndexArray.SetData(edgeIndexArrayLength, pEdgeIndexData);
	rBottomEdgeIndices->PutIndices(&(edgeIndexArray.m_psa));

	delete [] pEdgeIndexData;
	pEdgeIndexData = NULL;

	hr = rEdgeColorIndices->Add(1, 2);

	// Create a triangle strip for the cylindrical surface
	CComPtr<TriangleStripGraphics> rTriStrip;
	hr = pGroup->AddTriangleStripGraphics(&rTriStrip);
	hr = rTriStrip->put_CoordinateSet(pCoordinates);
	hr = rTriStrip->put_NormalSet(pNormals);
	hr = rTriStrip->put_NormalBinding(kPerVertexNormals);
	hr = rTriStrip->put_CoordinateIndexSet(rSideStripIndices);

	// Create a tri-fan for the top surface
	CComPtr<TriangleFanGraphics> rTopCap;
	hr = pGroup->AddTriangleFanGraphics(&rTopCap);
	hr = rTopCap->put_CoordinateSet(pCoordinates);
	hr = rTopCap->put_CoordinateIndexSet(rTopCapIndices);
	hr = rTopCap->put_NormalSet(rCapNormals);
	hr = rTopCap->put_NormalIndexSet(rTopCapNormalIndex);
	hr = rTopCap->put_NormalBinding(kOverallNormal);

	// Create a tri-fan for the bottom surface
	CComPtr<TriangleFanGraphics> rBottomCap;
	hr = pGroup->AddTriangleFanGraphics(&rBottomCap);
	hr = rBottomCap->put_CoordinateSet(pCoordinates);
	hr = rBottomCap->put_CoordinateIndexSet(rBottomCapIndices);
	hr = rBottomCap->put_NormalSet(rCapNormals);
	hr = rBottomCap->put_NormalIndexSet(rBottomCapNormalIndex);
	hr = rBottomCap->put_NormalBinding(kOverallNormal);

	// Create a line strip to highlight an edge
	CComPtr<LineStripGraphics> rBottomEdge;
	hr = pGroup->AddLineStripGraphics(&rBottomEdge);
	hr = rBottomEdge->put_CoordinateSet(pCoordinates);
	hr = rBottomEdge->put_CoordinateIndexSet(rBottomEdgeIndices);
	hr = rBottomEdge->put_ColorSet(pColorset);
	hr = rBottomEdge->put_ColorIndexSet(rEdgeColorIndices);
	hr = rBottomEdge->put_ColorBinding(kOverallColor);

	return hr;
}

//////////////////////////
// Draw Graphics Strips //
///////////////////////////////////////////////////////////////////////////////
// This example creates a triangle strip and line strip with essentially the
// same coordinates (offset differently along the Y-axis) but with strip lengths
// applied to the triangle strip which creates two different strips from a single
// TriangleStripGraphics object.
HRESULT CRxClientGraphics::DrawGraphicsStrips()
{
	HRESULT hr = NOERROR;

	const long GRAPHICS_STRIP_NODE		= 300;
	const long LINE_STRIP_COORDS		= 301;
	const long TRIANGLE_STRIP_COORDS	= 302;

	////////////////////////////
	// Create a graphics node //
	////////////////////////////
	CComPtr<GraphicsNode> rGraphicsNode;
	hr = m_rClientGraphics->AddNode(GRAPHICS_STRIP_NODE, &rGraphicsNode);

	////////////////////////////////////////////////////
	// Create coordinate data for our graphics strips //
	////////////////////////////////////////////////////
	const int rawDataLength = 10*3;
	double rawData[rawDataLength] = {
		-2.0, 0.0, 0.0,
		-2.0, 1.0, 0.0,
		-1.0, 0.0, 0.0,
		-1.0, 1.0, 0.0,
		 0.0, 0.0, 0.0,
		 0.0, 1.0, 0.0,
		 1.0, 0.0, 0.0,
		 1.0, 1.0, 0.0,
		 2.0, 0.0, 0.0,
		 2.0, 1.0, 0.0};

	const int lineStripDataLength = 10*3;
	double lineStripData[lineStripDataLength];

	const int triangleStripDataLength = 10*3;
	double triangleStripData[triangleStripDataLength];

	double yOffset = 0.0;
	int i = 0;
	for (i = 0; i < lineStripDataLength; i++)
	{
		lineStripData[i] = rawData[i];
		if (i%3 == 1)
			lineStripData[i] += yOffset;
	}
	CSafeArray<double, VT_R8> lineStripCoordsArray;
	lineStripCoordsArray.SetData(lineStripDataLength, lineStripData);

	yOffset += 1.0;
	for (i = 0; i < triangleStripDataLength; i++)
	{
		triangleStripData[i] = rawData[i];
		if (i%3 == 1)
			triangleStripData[i] += yOffset;
	}
	CSafeArray<double, VT_R8> triangleStripCoordsArray;
	triangleStripCoordsArray.SetData(triangleStripDataLength, triangleStripData);

	////////////////////
	// Add line strip //
	////////////////////
	CComPtr<GraphicsDataSet> rLineDataSet;
	CComQIPtr<GraphicsCoordinateSet> rLineStripCoordinates;
	m_rGraphicsDataSets->get_ItemById(LINE_STRIP_COORDS, &rLineDataSet);
	if (rLineDataSet)
	{
		rLineStripCoordinates = rLineDataSet;
	}
	else
	{
		hr = m_rGraphicsDataSets->CreateCoordinateSet(LINE_STRIP_COORDS, &rLineStripCoordinates);
		rLineStripCoordinates->PutCoordinates(&lineStripCoordsArray.m_psa);
	}

	CComPtr<LineStripGraphics> rLineStrip;
	hr = rGraphicsNode->AddLineStripGraphics(&rLineStrip);
	hr = rLineStrip->put_CoordinateSet(rLineStripCoordinates);

	////////////////////////
	// Add triangle strip //
	////////////////////////
	CComPtr<GraphicsDataSet> rTriangleDataSet;
	CComQIPtr<GraphicsCoordinateSet> rTriangleStripCoordinates;
	m_rGraphicsDataSets->get_ItemById(TRIANGLE_STRIP_COORDS, &rTriangleDataSet);
	if (rTriangleDataSet)
	{
		rTriangleStripCoordinates = rTriangleDataSet;
	}
	else
	{
		hr = m_rGraphicsDataSets->CreateCoordinateSet(TRIANGLE_STRIP_COORDS, &rTriangleStripCoordinates);
		rTriangleStripCoordinates->PutCoordinates(&triangleStripCoordsArray.m_psa);
	}

	CComPtr<TriangleStripGraphics> rTriangleStrip;

	hr = rGraphicsNode->AddTriangleStripGraphics(&rTriangleStrip);
	hr = rTriangleStrip->put_CoordinateSet(rTriangleStripCoordinates);

	/////////////////////////////////////
	// Put in colors and strip lengths //
	/////////////////////////////////////
	long stripLengthArray[2] = {6, 4};
	CSafeArray<long, VT_I4> stripLengths;
	stripLengths.SetData(2, stripLengthArray);
	hr = rTriangleStrip->PutStripLengths(&(stripLengths.m_psa));


	CComPtr<GraphicsColorSet> rTriangleColors;
	hr = m_rGraphicsDataSets->CreateColorSet(500, &rTriangleColors);
	hr = rTriangleColors->Add(1, 0, 0, 0);
	hr = rTriangleColors->Add(2, 50, 50, 0);
	hr = rTriangleColors->Add(3, 100, 100, 0);
	hr = rTriangleColors->Add(4, 150, 150, 0);
	hr = rTriangleColors->Add(5, 200, 200, 0);
	hr = rTriangleColors->Add(6, 250, 250, 0);
	hr = rTriangleColors->Add(7, 255, 0, 0);
	hr = rTriangleColors->Add(8, 0, 255, 0);
	hr = rTriangleColors->Add(9, 0, 0, 255);
	hr = rTriangleColors->Add(10, 0, 0, 0);
	hr = rTriangleStrip->put_ColorSet(rTriangleColors);
	ColorBindingEnum colorBinding = kPerStripColors;
	hr = rTriangleStrip->put_ColorBinding(colorBinding);

	hr = rLineStrip->put_ColorSet(rTriangleColors);
	hr = rLineStrip->put_ColorBinding(kPerItemColors);

	return hr;
}

/////////////////
// Draw Symbol //
///////////////////////////////////////////////////////////////////////////////
// This method uses the TransformBehavior property to create a feature control
// frame symbol that stays the same size and is always aligned with the camera
// and a leader line with an arrow head that stays the same size on screen
// but is not aligned with the camera.
HRESULT CRxClientGraphics::DrawSymbol()
{
	HRESULT hr = NOERROR;

	long baseId = 500;

	/////////////////////////////////////////////////////////////////////////
	// Create the FCF symbol (lines for the symbol and triangles to make a //
	// white background for the symbol).
	/////////////////////////////////////////////////////////////////////////
	CComPtr<GraphicsCoordinateSet> pSymbolCoords, pLeaderCoords;
	hr = m_rGraphicsDataSets->CreateCoordinateSet(baseId+1, &pSymbolCoords);
	const int symbolLinesDataLength = 18*3;
	double symbolLinesData[symbolLinesDataLength] = {
		3.5, 0.75, 0.0, 3.5, 1.25, 0.0,
		3.5, 1.25, 0.0, 5.0, 1.25, 0.0,
		5.0, 1.25, 0.0, 5.0, 0.75, 0.0,
		5.0, 0.75, 0.0, 3.5, 0.75, 0.0,
		4.5, 0.75, 0.0, 4.5, 1.25, 0.0,
		4.8, 0.85, 0.0, 4.8, 1.15, 0.0,
		4.75, 1.05, 0.0, 4.8, 1.15, 0.0,
		3.75, .85, 0.0, 4.25, 1.15, 0.0,
		3.75, .85, 0.0, 4.25, .85, 0.0};
	CSafeArray<double, VT_R8> symbolLinesArray;
	symbolLinesArray.SetData(symbolLinesDataLength, symbolLinesData);
	hr = pSymbolCoords->PutCoordinates(&(symbolLinesArray.m_psa));

	hr = m_rGraphicsDataSets->CreateCoordinateSet(baseId+2, &pLeaderCoords);
	CComPtr<Point> pLeaderAnchor, pSymbolAnchor;
	hr = g_pTransientGeometry->CreatePoint(3.5, 1, 0, &pSymbolAnchor);
	hr = g_pTransientGeometry->CreatePoint(1, 1, 0, &pLeaderAnchor);
	hr = pLeaderCoords->Add(1, pLeaderAnchor);
	hr = pLeaderCoords->Add(2, pSymbolAnchor);

	CComPtr<GraphicsNode> pGraphicsNode;
	CComPtr<LineGraphics> pSymbolLines, pLeaderLine;
	hr = m_rClientGraphics->AddNode(baseId + 3, &pGraphicsNode);
	hr = pGraphicsNode->put_Selectable(VARIANT_TRUE);
	hr = pGraphicsNode->AddLineGraphics(&pSymbolLines);
	hr = pGraphicsNode->AddLineGraphics(&pLeaderLine);

	hr = pSymbolLines->put_CoordinateSet(pSymbolCoords);
	hr = pSymbolLines->SetTransformBehavior(pSymbolAnchor, kFrontFacingAndPixelScaling, 30);
	hr = pLeaderLine->put_CoordinateSet(pLeaderCoords);

	CComPtr<TriangleStripGraphics> pSymbolBackground;
	hr = pGraphicsNode->AddTriangleStripGraphics(&pSymbolBackground);

	CComPtr<GraphicsIndexSet> pBackgroundIndices;
	m_rGraphicsDataSets->CreateIndexSet(baseId+8, &pBackgroundIndices);
	hr = pBackgroundIndices->Add(1, 1);
	hr = pBackgroundIndices->Add(2, 3);
	hr = pBackgroundIndices->Add(3, 7);
	hr = pBackgroundIndices->Add(4, 5);

	CComPtr<GraphicsColorSet> pBackgroundColors;
	m_rGraphicsDataSets->CreateColorSet(baseId, &pBackgroundColors);
	hr = pBackgroundColors->Add(1, 255, 255, 255);

	hr = pSymbolBackground->put_CoordinateSet(pSymbolCoords);
	hr = pSymbolBackground->put_CoordinateIndexSet(pBackgroundIndices);
	hr = pSymbolBackground->put_ColorSet(pBackgroundColors);
	hr = pSymbolBackground->SetTransformBehavior(pSymbolAnchor, kFrontFacingAndPixelScaling, 30);

	/////////////////////////////////////////////////////////////////////////////////
	// Create the arrow head with eight triangles fanned out from a central point. //
	// A triangle fan could have been used with the same effect but fewer          //
	// coordinates (see DrawCylinder)                                              //
	/////////////////////////////////////////////////////////////////////////////////
	CComPtr<TriangleGraphics> pArrowHead;
	CComPtr<GraphicsCoordinateSet> pArrowCoords;
	CComPtr<GraphicsIndexSet> pArrowCoordsIndices;
	hr = pGraphicsNode->AddTriangleGraphics(&pArrowHead);
	hr = pArrowHead->SetTransformBehavior(pLeaderAnchor, kPixelScaling, 5);

	hr = m_rGraphicsDataSets->CreateCoordinateSet(baseId+4, &pArrowCoords);
	hr = m_rGraphicsDataSets->CreateIndexSet(baseId+5, &pArrowCoordsIndices);
	const int arrowHeadDataLength = 9*3;
	double arrowHeadData[arrowHeadDataLength] = {
		1.0, 1.0, 0.0,
		3.0, 2.0, 0.0,
		3.0, 1.7, 0.7,
		3.0, 1.0, 1.0,
		3.0, 0.3, 0.7,
		3.0, 0.0, 0.0,
		3.0, 0.3, -0.7,
		3.0, 1.0, -1.0,
		3.0, 1.7, -0.7};
	CSafeArray<double, VT_R8> arrowHeadArray;
	arrowHeadArray.SetData(arrowHeadDataLength, arrowHeadData);
	hr = pArrowCoords->PutCoordinates(&(arrowHeadArray.m_psa));
	hr = pArrowHead->put_CoordinateSet(pArrowCoords);

	const int arrowCoordIndexDataLength = 24;
	const long arrowCoordIndexData[arrowCoordIndexDataLength] = {
		1, 2, 3,
		1, 3, 4,
		1, 4, 5,
		1, 5, 6,
		1, 6, 7,
		1, 7, 8,
		1, 8, 9,
		1, 9, 2};
	CSafeArray<long, VT_I4> arrowCoordIndexArray;
	arrowCoordIndexArray.SetData(arrowCoordIndexDataLength, arrowCoordIndexData);
	pArrowCoordsIndices->PutIndices(&(arrowCoordIndexArray.m_psa));
	hr = pArrowHead->put_CoordinateIndexSet(pArrowCoordsIndices);

	// Calculate the normals for the triangles of the arrow head.
	CComPtr<GraphicsNormalSet> pArrowNormals;
	m_rGraphicsDataSets->CreateNormalSet(baseId+6, &pArrowNormals);
	const int arrowNormalsDataLength = 9*3;
	for (int i=0; i<8; ++i)
	{
		long p1Index = arrowCoordIndexData[i*3] - 1;
		long p2Index = arrowCoordIndexData[i*3+1] - 1;
		long p3Index = arrowCoordIndexData[i*3+2] - 1;

		CComPtr<Point> p1, p2, p3;
		g_pTransientGeometry->CreatePoint(arrowHeadData[p1Index*3], arrowHeadData[p1Index*3+1],
			arrowHeadData[p1Index*3+2], &p1);
		g_pTransientGeometry->CreatePoint(arrowHeadData[p2Index*3], arrowHeadData[p2Index*3+1],
			arrowHeadData[p2Index*3+2], &p2);
		g_pTransientGeometry->CreatePoint(arrowHeadData[p3Index*3], arrowHeadData[p3Index*3+1],
			arrowHeadData[p3Index*3+2], &p3);

		CComPtr<Vector> pV1to2, pV1to3;
		hr = p2->VectorTo(p1, &pV1to2);
		hr = p3->VectorTo(p1, &pV1to3);

		CComPtr<Vector> pCross;
		hr = pV1to3->CrossProduct(pV1to2, &pCross);

		CComPtr<UnitVector> pNormal;
		hr = pCross->Normalize();
		hr = pCross->AsUnitVector(&pNormal);

		pArrowNormals->Add(i+1, pNormal);
	}
	hr = pArrowHead->put_NormalSet(pArrowNormals);
	hr = pArrowHead->put_NormalBinding(kPerItemNormals);
	hr = pArrowHead->put_DepthPriority(2);

	CComPtr<GraphicsColorSet> pSymbolColors;
	m_rGraphicsDataSets->CreateColorSet(baseId+7, &pSymbolColors);
	hr = pSymbolColors->Add(1, 0, 0, 0);
	hr = pArrowHead->put_ColorSet(pSymbolColors);
	hr = pSymbolLines->put_ColorSet(pSymbolColors);
	hr = pLeaderLine->put_ColorSet(pSymbolColors);

	return hr;
}

/////////////////////
// Trace Range Box //
///////////////////////////////////////////////////////////////////////////////
// Print out the value of the specified bounding box with the specified indentation
// level.  This function, along with the two reporting functions below, is
// designed to send the reported data to the output window in Microsoft Studio
// but it could easily be adapted to send its data to some other destination.
HRESULT TraceRangeBox(int indent, CComPtr<Box> rBoundingBox)
{
	HRESULT hr = NOERROR;

	if (!rBoundingBox)
		return E_INVALIDARG;

	CString indentStr;
	for (int i=0; i<indent; ++i)
		indentStr += _T(" ");

	CComPtr<Point> rMinPoint, rMaxPoint;
	hr = rBoundingBox->get_MinPoint(&rMinPoint);
	hr = rBoundingBox->get_MaxPoint(&rMaxPoint);

	double minX, minY, minZ, maxX, maxY, maxZ;
	minX = minY = minZ = maxX = maxY = maxZ = 0.0;
	rMinPoint->get_X(&minX);
	rMinPoint->get_Y(&minY);
	rMinPoint->get_Z(&minZ);
	rMaxPoint->get_X(&maxX);
	rMaxPoint->get_Y(&maxY);
	rMaxPoint->get_Z(&maxZ);

	TRACE(_T("%sRange Box = (%f, %f, %f) by (%f, %f, %f)\n"), indentStr, minX, minY, minZ, maxX, maxY, maxZ);

	return hr;
}

/////////////////////
// Report Graphics //
///////////////////////////////////////////////////////////////////////////////
// Iterate through all of the graphics nodes and graphics primitives for our
// client.  The coordinate sets and other graphics data are reported in the
// ReportGraphicsData function below this one.
HRESULT ReportGraphics(CComPtr<ClientGraphicsCollection> pGraphicsCollection)
{
	HRESULT hr = NOERROR;

	if (pGraphicsCollection)
	{
		TRACE(_T("\nClient Graphics Collection\n"));
		TRACE(_T("--------------------------\n"));

		long numClientGraphics = 0;
		hr = pGraphicsCollection->get_Count(&numClientGraphics);
		for (long clientIndex = 1; clientIndex <= numClientGraphics; ++clientIndex)
		{
			_variant_t clientIndexVariant = _variant_t(clientIndex);
			CComPtr<ClientGraphics> rClient;
			hr = pGraphicsCollection->get_Item(clientIndexVariant, &rClient);

			TRACE(_T("\n  Client Graphics\n"));
			TRACE(_T("  ---------------\n"));

			CComPtr<Box> rClientBox;
			hr = rClient->get_RangeBox(&rClientBox);
			hr = TraceRangeBox(2, rClientBox);

			long numNodes = 0;
			hr = rClient->get_Count(&numNodes);
			for (long nodeIndex = 1; nodeIndex <= numNodes; ++nodeIndex)
			{
				TRACE(_T("\n    Graphics Node\n"));
				TRACE(_T("    -------------\n"));

				CComPtr<GraphicsNode> pNode;
				hr = rClient->get_Item(nodeIndex, &pNode);

				CComPtr<Box> pNodeBox;
				hr = pNode->get_RangeBox(&pNodeBox);
				hr = TraceRangeBox(4, pNodeBox);

				CComPtr<GraphicsNode> testNode;
				long nodeId = 0;
				hr = pNode->get_Id(&nodeId);
				hr = rClient->get_ItemById(nodeId, &testNode);
				hr = testNode->get_Id(&nodeId);

				long numPrimitives = 0;
				hr = pNode->get_Count(&numPrimitives);

				for (long primitiveIndex = 1; primitiveIndex <= numPrimitives; ++primitiveIndex)
				{
					CComPtr<GraphicsPrimitive> rPrimitive;
					hr = pNode->get_Item(primitiveIndex, &rPrimitive);

					if (CComQIPtr<LineGraphics> rLines = rPrimitive)
					{
						TRACE(_T("\n      Line Graphics\n"));
						TRACE(_T("      -------------\n"));
					}
					else if (CComQIPtr<LineStripGraphics> rLineStrips = rPrimitive)
					{
						TRACE(_T("\n      Line Strip Graphics\n"));
						TRACE(_T("      -------------------\n"));
					}
					else if (CComQIPtr<TriangleGraphics> rTriangles = rPrimitive)
					{
						TRACE(_T("\n      Triangle Graphics\n"));
						TRACE(_T("      -----------------\n"));
					}
					else if (CComQIPtr<TriangleStripGraphics> rTriangleStrips = rPrimitive)
					{
						TRACE(_T("\n      Triangle Strip Graphics\n"));
						TRACE(_T("      -----------------------\n"));
					}
					else if (CComQIPtr<TriangleFanGraphics> rTriangleFans = rPrimitive)
					{
						TRACE(_T("\n      Triangle Fan Graphics\n"));
						TRACE(_T("      ---------------------\n"));
					}
					else if (CComQIPtr<TextGraphics> rText = rPrimitive)
					{
						TRACE(_T("\n      Text Graphics\n"));
						TRACE(_T("      -------------\n"));
					}
					else if (CComQIPtr<PointGraphics> rPoints = rPrimitive)
					{
						TRACE(_T("\n      Point Graphics\n"));
						TRACE(_T("      --------------\n"));
					}
					else
					{
						TRACE(_T("\n      Unknown Graphics Primitive\n"));
						TRACE(_T("      --------------------------\n"));
					}

					CComPtr<Box> rBoundingBox;
					hr = rPrimitive->get_RangeBox(&rBoundingBox);
					if (rBoundingBox)
					{
						hr = TraceRangeBox(6, rBoundingBox);
					}
					else
						hr = E_FAIL;
				}
			}
		}
	}
	else
		hr = E_FAIL;

	return hr;
}

//////////////////////////
// Report Graphics Data //
///////////////////////////////////////////////////////////////////////////////
// Iterate through all of the graphics data for our client.
HRESULT ReportGraphicsData(CComQIPtr<GraphicsDataSetsCollection> pDataCollection)
{
	HRESULT hr = NOERROR;

	TRACE(_T("\nGraphics Data Sets Collection\n"));
	TRACE(_T("-----------------------------\n"));

	long numClientData = 0;
	hr = pDataCollection->get_Count(&numClientData);

	for (long clientDataIndex = 1; clientDataIndex <= numClientData; ++clientDataIndex)
	{
		_variant_t clientDataIndexVariant = _variant_t(clientDataIndex);

		CComPtr<GraphicsDataSets> pClientData;
		hr = pDataCollection->get_Item(clientDataIndexVariant, &pClientData);

		BSTR clientBSTR;
		hr = pClientData->get_ClientId(&clientBSTR);

		TRACE(_T("\n  Graphics Data Sets\n"));
		TRACE(_T("  ------------------\n"));

		long numDataSets = 0;
		hr = pClientData->get_Count(&numDataSets);

		for (long dataSetIndex = 1; dataSetIndex <= numDataSets; ++dataSetIndex)
		{
			CComPtr<GraphicsDataSet> pDataSet;
			hr = pClientData->get_Item(dataSetIndex, &pDataSet);

			if (CComQIPtr<GraphicsCoordinateSet> pCoordSet = pDataSet)
			{
				TRACE(_T("    Coordinate Set\n"));
			}
			else if (CComQIPtr<GraphicsNormalSet> pNormalSet = pDataSet)
			{
				TRACE(_T("    Normal Set\n"));
			}
			else if (CComQIPtr<GraphicsColorSet> pColorset = pDataSet)
			{
				TRACE(_T("    Color Set\n"));
			}
			else if (CComQIPtr<GraphicsIndexSet> pIndexSet = pDataSet)
			{
				TRACE(_T("    Index Set\n"));
			}
		}
	}

	return hr;
}

///////////////
// Clear All //
///////////////////////////////////////////////////////////////////////////////
// Delete all of the graphics nodes for our client.  This permanently deletes
// all of the client graphics that were added to the current document, with the
// exception of an undo by the user which would restore the graphics as they
// were before the ClearAll was done.
HRESULT CRxClientGraphics::ClearAll()
{
	HRESULT hr = NOERROR;

	long count = 0;
	hr = m_rClientGraphics->get_Count(&count);

	for (int i=count; i > 0; --i)
	{
		CComPtr<GraphicsNode> pNode;
		hr = m_rClientGraphics->get_Item(i, &pNode);
		if (SUCCEEDED(hr) && pNode)
			hr = pNode->Delete();
	}

	return hr;
}

///////////////////
// Show Graphics //
///////////////////////////////////////////////////////////////////////////////
// If show is false then all of the graphics nodes added to the current document
// will be hidden.  If show is true then all graphics nodes added to the current
// document will be made visible.  The same is true for the selectability of the
// graphics so that we don't select graphics that are not visible.  It is also
// possible to make a specific graphics node visible or hidden.  The visibility
// of a graphics node does not impact on the accessibility of the node through
// the API.  You can continue to make changes to a node while it is hidden and
// even delete the node.
HRESULT CRxClientGraphics::ShowGraphics(bool show)
{
	HRESULT hr = NOERROR;

	GraphicsVisibilityEnum clientVisible = kNoGraphicsVisible;
	hr = m_rClientGraphics->get_Visible(&clientVisible);

	if (show && clientVisible == kNoGraphicsVisible)
	{
		hr = m_rClientGraphics->put_Visible(kAllGraphicsVisible);
	}
	else if (show == false &&
			 (clientVisible == kSomeGraphicsVisible || clientVisible == kAllGraphicsVisible))
	{
		hr = m_rClientGraphics->put_Visible(kNoGraphicsVisible);
	}

	return hr;
}

///////////////////
// Redraw Active //
///////////////////////////////////////////////////////////////////////////////
// Redraws the active view.
HRESULT CRxClientGraphics::RedrawActive()
{
	HRESULT hr = NOERROR;

	CComPtr<View> pActiveView;
	m_pApplication->get_ActiveView(&pActiveView);
	if (SUCCEEDED(hr))
		hr = pActiveView->Update();

	return hr;
}

/////////////////////
// Execute Command //
///////////////////////////////////////////////////////////////////////////////
// Called whenever the user selects a specific command from the menu for this
// add-in.
HRESULT CRxClientGraphics::ExecuteCommand (long CommandID)
{
	AFX_MANAGE_STATE (AfxGetStaticModuleState());
	
	HRESULT hr = NOERROR;

	/////////////////////////////
	// Get the active document //
	/////////////////////////////
	hr = m_pApplication->get_ActiveDocument (&m_rCurrentDoc);
	if (!m_rCurrentDoc)
	{
		AfxMessageBox(CString(L"No active document to add client graphics to"));
		return E_FAIL;
	}

	//////////////////////////////////////////
	// Create a transaction for the command //
	//////////////////////////////////////////
	// Each named transaction will appear under the Edit menu and an undoable/
	// redoable action.  If you don't create a named transaction then each
	// individual action called through the API will appear as an undoable/redoable
	// action.
	CComPtr<TransactionManager> pTransactionManager;
	CComPtr<Transaction> pTransaction;
	hr = m_pApplication->get_TransactionManager(&pTransactionManager);

	hr = pTransactionManager->StartTransaction(m_rCurrentDoc, m_commandMap[CommandID], &pTransaction);

	/////////////////////////////////////////////////////////////////
	// Get the graphics data sets object for the current document. //
	///////////////////////////////////////////////////////	/////////
	CComQIPtr<GraphicsDataSetsCollection> pGraphicsDataSetsCollection;

	hr = m_rCurrentDoc->get_GraphicsDataSetsCollection(&pGraphicsDataSetsCollection);
	hr = pGraphicsDataSetsCollection->get_Item(m_clientIdVariant, &m_rGraphicsDataSets);
	if (FAILED(hr))
		hr = pGraphicsDataSetsCollection->Add(m_clientId, &m_rGraphicsDataSets);

	/////////////////////////////////////////////////////////////
	// Get the client graphics object for the current document //
	/////////////////////////////////////////////////////////////
	CComPtr<ClientGraphicsCollection> pGraphicsCollection;

	// Get the component definition for the document if its a part or assembly.
	// Return an error for all other document types.
	CComQIPtr<ComponentDefinition> pCompDef;
    if (CComQIPtr<PartDocument> pPartDoc = m_rCurrentDoc)
	{
		CComPtr<PartComponentDefinition> pPartCompDef;
		hr = pPartDoc->get_ComponentDefinition(&pPartCompDef);
		if (SUCCEEDED(hr))
			pCompDef = pPartCompDef;

		// Get the graphics collection from the component definition
		hr = pCompDef->get_ClientGraphicsCollection(&pGraphicsCollection);
	}
	else if (CComQIPtr<AssemblyDocument> pAssemblyDoc = m_rCurrentDoc)
	{
		CComPtr<AssemblyComponentDefinition> pAssemblyCompDef;
		hr = pAssemblyDoc->get_ComponentDefinition(&pAssemblyCompDef);

		if (SUCCEEDED(hr))
			pCompDef = pAssemblyCompDef;

		// Get the graphics collection from the component definition
		hr = pCompDef->get_ClientGraphicsCollection(&pGraphicsCollection);
	}
	else
	{
		AfxMessageBox(CString(L"Client graphics can only be added to part and assembly documents."));
		return E_FAIL;
	}

	// Attempt to get our graphics object
	hr = pGraphicsCollection->get_Item(m_clientIdVariant, &m_rClientGraphics);
	if (FAILED(hr))
	{
		// Add a new graphics object
		hr = pGraphicsCollection->Add(m_clientId, &m_rClientGraphics);
	}

	//////////////////////////////////
	// Execute the specific command //
	//////////////////////////////////
	switch (CommandID)
	{
		case CMD_DrawSquare:
			hr = DrawSquares();
			break;

		case CMD_DrawVonKoch:
			hr = DrawVonKoch();
			break;

		case CMD_DrawCircle:
			hr = DrawCircle();
			break;

		case CMD_DrawTriangles:
			hr = DrawCylinder();
			break;

		case CMD_SharedCoords:
			hr = DrawSharedCoords();
			break;

		case CMD_GraphicsStrips:
			hr = DrawGraphicsStrips();
			break;

		case CMD_DrawSymbol:
			hr = DrawSymbol();
			break;

		case CMD_MoveGraphics:
			hr = TransformGroups();
			break;

		case CMD_ClearAll:
			hr = ClearAll();
			break;

		case CMD_ShowGraphics:
			hr = ShowGraphics(true);
			break;

		case CMD_HideGraphics:
			hr = ShowGraphics(false);
			break;

		default:
			hr = E_NOTIMPL;
	}
	RedrawActive();

	static bool reportData = false;
	if (reportData)
	{
		hr = ReportGraphicsData(pGraphicsDataSetsCollection);
		hr = ReportGraphics(pGraphicsCollection);
	}

	/////////////////////////
	// End the transaction //
    /////////////////////////
	CComPtr<Transaction> pEndedTransaction;
	hr = pTransactionManager->EndTransaction(&pEndedTransaction);

	///////////////////////////////////////////
	// Free the document specific interfaces //
	///////////////////////////////////////////
	// We'll restore these at the start of the next execute.
	m_rCurrentDoc.Detach()->Release();
	m_rGraphicsDataSets.Detach()->Release();
	m_rClientGraphics.Detach()->Release();

	return hr;
}

HRESULT CRxClientGraphics::get_Automation (IUnknown **ppUnk)
{
	HRESULT hr = NOERROR;

	if (!ppUnk)
		return E_INVALIDARG;

	*ppUnk = NULL;

	// TODO:
	// If this AddIn wanted to expose any of its Automation API, it must do so by
	// returning its top-level interface through this method.

	hr = E_NOINTERFACE;

	return hr;
}

void CRxClientGraphics::CreateCommands()
{
	ATLASSERT(m_pApplication);

	if(!m_pApplication)
		return;

	CComPtr<CommandManager> pCommandMgr;
	HRESULT hr = m_pApplication->get_CommandManager(&pCommandMgr);

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
	vtAddInId	      = _T("{E985C31C-56BF-11d5-8E36-0010B547BBF8}");
	// command type
	eCmdType = kQueryOnlyCmdType;
	// button display type
	eCmdDisplayType = kAlwaysDisplayText;

	// Add the Draw Squares command
	InternalNameBSTR  =	_T("ClientGraphicsAddIn.DrawSquaresCmd");
	displayNameBSTR	  =	_T("DrawSquares");
	DesTextBSTR		  =	_T("Execute Draw Squares Command");
	TooltipTextBSTR	  =	_T("Draw Squares");	
	
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

	hr = m_pBtnDef1->AutoAddToGUI();
	ATLASSERT(SUCCEEDED(hr));


	// Add the Draw von Koch Snowflake command
	InternalNameBSTR  =	_T("ClientGraphicsAddIn.DrawvonKochSnowflakeCmd");
	displayNameBSTR	  =	_T("DrawvonKochSnowflake");
	DesTextBSTR		  =	_T("Execute Draw von Koch Snowflake Command");
	TooltipTextBSTR	  =	_T("Draw von Koch Snowflake");
	

	hr = pCtrlDefs->AddButtonDefinition(displayNameBSTR, InternalNameBSTR,eCmdType,vtAddInId,DesTextBSTR,TooltipTextBSTR,vtEmpty,vtEmpty,eCmdDisplayType,&m_pBtnDef2); 

	ATLASSERT(SUCCEEDED(hr));
	ATLASSERT(m_pBtnDef2 != NULL);

	m_pBtnDef2->put_Enabled(VARIANT_TRUE);

	if(m_pBtnDef2)
	{
		BOOL bBrwsrAdvised = AfxConnectionAdvise(m_pBtnDef2, DIID_ButtonDefinitionSink,
                                m_pButtonEvents2->GetInterface(&IID_IUnknown),
                                TRUE, &m_btnDefCookie2);

		ATLASSERT(bBrwsrAdvised == TRUE);
	}

	hr = m_pBtnDef2->AutoAddToGUI();
	ATLASSERT(SUCCEEDED(hr));


	// Add the Draw Circle command
	InternalNameBSTR  =	_T("ClientGraphicsAddIn.DrawCircleCmd");
	displayNameBSTR	  =	_T("DrawCircle");
	DesTextBSTR		  =	_T("Execute Draw Circle Command");
	TooltipTextBSTR	  =	_T("Draw Circle");
	
	hr = pCtrlDefs->AddButtonDefinition(displayNameBSTR, InternalNameBSTR,eCmdType,vtAddInId,DesTextBSTR,TooltipTextBSTR,vtEmpty,vtEmpty,eCmdDisplayType,&m_pBtnDef3); 

	ATLASSERT(SUCCEEDED(hr));
	ATLASSERT(m_pBtnDef3 != NULL);

	m_pBtnDef3->put_Enabled(VARIANT_TRUE);

	if(m_pBtnDef3)
	{
		BOOL bBrwsrAdvised = AfxConnectionAdvise(m_pBtnDef3, DIID_ButtonDefinitionSink,
                                m_pButtonEvents3->GetInterface(&IID_IUnknown),
                                TRUE, &m_btnDefCookie3);

		ATLASSERT(bBrwsrAdvised == TRUE);
	}

	hr = m_pBtnDef3->AutoAddToGUI();
	ATLASSERT(SUCCEEDED(hr));


	// Add the Shared Coordinates command
	InternalNameBSTR  =	_T("ClientGraphicsAddIn.SharedCoordinatesCmd");
	displayNameBSTR	  =	_T("SharedCoordinates");
	DesTextBSTR		  =	_T("Execute Shared Coordinates Command");
	TooltipTextBSTR	  =	_T("Shared Coordinates");
	

	hr = pCtrlDefs->AddButtonDefinition(displayNameBSTR, InternalNameBSTR,eCmdType,vtAddInId,DesTextBSTR,TooltipTextBSTR,vtEmpty,vtEmpty,eCmdDisplayType,&m_pBtnDef4); 

	ATLASSERT(SUCCEEDED(hr));
	ATLASSERT(m_pBtnDef4 != NULL);

	m_pBtnDef4->put_Enabled(VARIANT_TRUE);

	if(m_pBtnDef4)
	{
		BOOL bBrwsrAdvised = AfxConnectionAdvise(m_pBtnDef4, DIID_ButtonDefinitionSink,
                                m_pButtonEvents4->GetInterface(&IID_IUnknown),
                                TRUE, &m_btnDefCookie4);

		ATLASSERT(bBrwsrAdvised == TRUE);
	}

	hr = m_pBtnDef4->AutoAddToGUI();
	ATLASSERT(SUCCEEDED(hr));



	// Add the Draw Cylinder command
	InternalNameBSTR  =	_T("ClientGraphicsAddIn.DrawCylinderCmd");
	displayNameBSTR	  =	_T("DrawCylinder");
	DesTextBSTR		  =	_T("Execute Draw Cylinder Command");
	TooltipTextBSTR	  =	_T("Draw Cylinder");
	

	hr = pCtrlDefs->AddButtonDefinition(displayNameBSTR, InternalNameBSTR,eCmdType,vtAddInId,DesTextBSTR,TooltipTextBSTR,vtEmpty,vtEmpty,eCmdDisplayType,&m_pBtnDef5); 

	ATLASSERT(SUCCEEDED(hr));
	ATLASSERT(m_pBtnDef5 != NULL);

	m_pBtnDef5->put_Enabled(VARIANT_TRUE);

	if(m_pBtnDef5)
	{
		BOOL bBrwsrAdvised = AfxConnectionAdvise(m_pBtnDef5, DIID_ButtonDefinitionSink,
                                m_pButtonEvents5->GetInterface(&IID_IUnknown),
                                TRUE, &m_btnDefCookie5);

		ATLASSERT(bBrwsrAdvised == TRUE);
	}

	hr = m_pBtnDef5->AutoAddToGUI();
	ATLASSERT(SUCCEEDED(hr));



	// Add the Draw Graphics Strips command
	InternalNameBSTR  =	_T("ClientGraphicsAddIn.DrawGraphicsStripsCmd");
	displayNameBSTR	  =	_T("DrawGraphicsStrips");
	DesTextBSTR		  =	_T("Execute Draw Graphics Strips Command");
	TooltipTextBSTR	  =	_T("Draw Graphics Strips");
	

	hr = pCtrlDefs->AddButtonDefinition(displayNameBSTR, InternalNameBSTR,eCmdType,vtAddInId,DesTextBSTR,TooltipTextBSTR,vtEmpty,vtEmpty,eCmdDisplayType,&m_pBtnDef6); 

	ATLASSERT(SUCCEEDED(hr));
	ATLASSERT(m_pBtnDef6 != NULL);

	m_pBtnDef6->put_Enabled(VARIANT_TRUE);

	if(m_pBtnDef6)
	{
		BOOL bBrwsrAdvised = AfxConnectionAdvise(m_pBtnDef6, DIID_ButtonDefinitionSink,
                                m_pButtonEvents6->GetInterface(&IID_IUnknown),
                                TRUE, &m_btnDefCookie6);

		ATLASSERT(bBrwsrAdvised == TRUE);
	}

	hr = m_pBtnDef6->AutoAddToGUI();
	ATLASSERT(SUCCEEDED(hr));



	// Add the Draw Symbol command
	InternalNameBSTR  =	_T("ClientGraphicsAddIn.DrawSymbolCmd");
	displayNameBSTR	  =	_T("DrawSymbol");
	DesTextBSTR		  =	_T("Execute Draw Symbol Command");
	TooltipTextBSTR	  =	_T("Draw Symbol");
	

	hr = pCtrlDefs->AddButtonDefinition(displayNameBSTR, InternalNameBSTR,eCmdType,vtAddInId,DesTextBSTR,TooltipTextBSTR,vtEmpty,vtEmpty,eCmdDisplayType,&m_pBtnDef7); 

	ATLASSERT(SUCCEEDED(hr));
	ATLASSERT(m_pBtnDef7 != NULL);

	m_pBtnDef7->put_Enabled(VARIANT_TRUE);

	if(m_pBtnDef7)
	{
		BOOL bBrwsrAdvised = AfxConnectionAdvise(m_pBtnDef7, DIID_ButtonDefinitionSink,
                                m_pButtonEvents7->GetInterface(&IID_IUnknown),
                                TRUE, &m_btnDefCookie7);

		ATLASSERT(bBrwsrAdvised == TRUE);
	}

	hr = m_pBtnDef7->AutoAddToGUI();
	ATLASSERT(SUCCEEDED(hr));



	// Add the Move Graphics command
	InternalNameBSTR  =	_T("ClientGraphicsAddIn.MoveGraphicsCmd");
	displayNameBSTR	  =	_T("MoveGraphics");
	DesTextBSTR	      =	_T("Execute Move Graphics Command");
	TooltipTextBSTR   =	_T("Move Graphics");
	
	hr = pCtrlDefs->AddButtonDefinition(displayNameBSTR, InternalNameBSTR,eCmdType,vtAddInId,DesTextBSTR,TooltipTextBSTR,vtEmpty,vtEmpty,eCmdDisplayType,&m_pBtnDef8); 

	ATLASSERT(SUCCEEDED(hr));
	ATLASSERT(m_pBtnDef8 != NULL);

	m_pBtnDef8->put_Enabled(VARIANT_TRUE);

	if(m_pBtnDef8)
	{
		BOOL bBrwsrAdvised = AfxConnectionAdvise(m_pBtnDef8, DIID_ButtonDefinitionSink,
                                m_pButtonEvents8->GetInterface(&IID_IUnknown),
                                TRUE, &m_btnDefCookie8);

		ATLASSERT(bBrwsrAdvised == TRUE);
	}

	hr = m_pBtnDef8->AutoAddToGUI();
	ATLASSERT(SUCCEEDED(hr));



	// Add the Show Graphics command
	InternalNameBSTR  =	_T("ClientGraphicsAddIn.ShowGraphicsCmd");
	displayNameBSTR	  =	_T("ShowGraphics");
	DesTextBSTR		  =	_T("Execute Show Graphics Command");
	TooltipTextBSTR	  =	_T("Show Graphics");
	

	hr = pCtrlDefs->AddButtonDefinition(displayNameBSTR, InternalNameBSTR,eCmdType,vtAddInId,DesTextBSTR,TooltipTextBSTR,vtEmpty,vtEmpty,eCmdDisplayType,&m_pBtnDef9); 

	ATLASSERT(SUCCEEDED(hr));
	ATLASSERT(m_pBtnDef9 != NULL);

	m_pBtnDef9->put_Enabled(VARIANT_TRUE);

	if(m_pBtnDef9)
	{
		BOOL bBrwsrAdvised = AfxConnectionAdvise(m_pBtnDef9, DIID_ButtonDefinitionSink,
                                m_pButtonEvents9->GetInterface(&IID_IUnknown),
                                TRUE, &m_btnDefCookie9);

		ATLASSERT(bBrwsrAdvised == TRUE);
	}

	hr = m_pBtnDef9->AutoAddToGUI();
	ATLASSERT(SUCCEEDED(hr));



	// Add the Hide Graphics command
	InternalNameBSTR  =	_T("ClientGraphicsAddIn.HideGraphicsCmd");
	displayNameBSTR	  =	_T("HideGraphics");
	DesTextBSTR		  =	_T("Execute Hide Graphics Command");
	TooltipTextBSTR	  =	_T("Hide Graphics");
	

	hr = pCtrlDefs->AddButtonDefinition(displayNameBSTR, InternalNameBSTR,eCmdType,vtAddInId,DesTextBSTR,TooltipTextBSTR,vtEmpty,vtEmpty,eCmdDisplayType,&m_pBtnDef10); 

	ATLASSERT(SUCCEEDED(hr));
	ATLASSERT(m_pBtnDef10 != NULL);

	m_pBtnDef10->put_Enabled(VARIANT_TRUE);

	if(m_pBtnDef10)
	{
		BOOL bBrwsrAdvised = AfxConnectionAdvise(m_pBtnDef10, DIID_ButtonDefinitionSink,
                                m_pButtonEvents10->GetInterface(&IID_IUnknown),
                                TRUE, &m_btnDefCookie10);

		ATLASSERT(bBrwsrAdvised == TRUE);
	}

	hr = m_pBtnDef10->AutoAddToGUI();
	ATLASSERT(SUCCEEDED(hr));



	// Add the Clear command
	InternalNameBSTR  =	_T("ClientGraphicsAddIn.ClearCmd");
	displayNameBSTR	  =	_T("Clear");
	DesTextBSTR		  =	_T("Execute Clear Command");
	TooltipTextBSTR	  =	_T("Clear");
	

	hr = pCtrlDefs->AddButtonDefinition(displayNameBSTR, InternalNameBSTR,eCmdType,vtAddInId,DesTextBSTR,TooltipTextBSTR,vtEmpty,vtEmpty,eCmdDisplayType,&m_pBtnDef11); 

	ATLASSERT(SUCCEEDED(hr));
	ATLASSERT(m_pBtnDef11 != NULL);

	m_pBtnDef11->put_Enabled(VARIANT_TRUE);

	if(m_pBtnDef11)
	{
		BOOL bBrwsrAdvised = AfxConnectionAdvise(m_pBtnDef11, DIID_ButtonDefinitionSink,
                                m_pButtonEvents11->GetInterface(&IID_IUnknown),
                                TRUE, &m_btnDefCookie11);

		ATLASSERT(bBrwsrAdvised == TRUE);
	}

	hr = m_pBtnDef11->AutoAddToGUI();
	ATLASSERT(SUCCEEDED(hr));

}


/////////////////////////////////////////////////////////////////////////////
// CButtonDefDefEvents

IMPLEMENT_DYNCREATE(CButtonDefEvents, CCmdTarget)

CButtonDefEvents::CButtonDefEvents(CRxClientGraphics* pAddIn, UINT nID) : m_pAddIn(pAddIn), m_nID(nID)
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
// CButtonDefDefEvents event handlers

void CButtonDefEvents::OnExecuteEvent(NameValueMap *context) 
{
	if(m_pAddIn)
		m_pAddIn->ExecuteCommand(m_nID);
}
