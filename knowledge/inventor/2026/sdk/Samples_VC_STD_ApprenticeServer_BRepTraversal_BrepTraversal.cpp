/*
	DESCRIPTION

	Sample using the Autodesk Inventor (R) API to traverse through the B-Rep of a part.

*/

#include <objbase.h>
#include <atlbase.h>
#include <atlsafe.h>
#include <stdio.h>

#pragma warning(disable : 4192) // automatically excluding 'name' while importing type library 'library'
#pragma warning(disable : 4278) // 'name':identifier in type library 'library' is already a macro

// Autodesk Inventor (R) interfaces include
#include "InventorUtils.h"

// Forward declarations
HRESULT GetBrep();

int _tmain(int argc, _TCHAR* argv[])
{
	HRESULT hr = ::CoInitialize(NULL);
	
	if (SUCCEEDED(hr))
	{
		hr = GetBrep();
		if (FAILED(hr))
			wprintf_s(L"\nFailure during traversal!");
	}

	wprintf_s (L"\n\nExiting...press Enter _: ");
	
	TCHAR Return[81];
	_getts_s (Return);

	::CoUninitialize();
	return 0;
}

HRESULT GetBrep()
{
	HRESULT hr = NOERROR;

	//create Apprentice object
	CComPtr<ApprenticeServer> pApprenticeServer;
	hr = pApprenticeServer.CoCreateInstance(CLSID_ApprenticeServerComponent);
	if(FAILED(hr)){
		wprintf_s (L"Failed to create instance of Apprentice");
		return hr;
	}

	// Get the filename to open.
	wprintf_s (L"Specify part file to open: ");
	TCHAR Filename[200];
	_getts_s (Filename);

	CComBSTR fName(Filename);

	// Open the file.
	CComPtr<ApprenticeServerDocument> pApprenticeServerDocument;
	hr = pApprenticeServer->Open(fName, &pApprenticeServerDocument);
	if(FAILED(hr) || !pApprenticeServerDocument)
	{
		wprintf_s (L"Failed to open document, please verify full file name of part ");
		return E_FAIL;
	}

	// Get the first component definition from the document.
	CComPtr<ComponentDefinition> pCompDef;
	hr = pApprenticeServerDocument->get_ComponentDefinition(&pCompDef);
	if (FAILED(hr)) return hr;

	// Get the surface bodies from the compdef.
	CComPtr<SurfaceBodies> pSurfaceBodies;
	hr = pCompDef->get_SurfaceBodies(&pSurfaceBodies);
	if (FAILED(hr)) return hr;

	// Get the first surface body from the component definition.
	// (There should only ever be one surface body.)
	CComPtr<SurfaceBody> pBody;
	hr = pSurfaceBodies->get_Item(1, &pBody);
	if (FAILED(hr)) return hr;

	// Get the shells from the body.
	CComPtr<FaceShells> pShells;
	hr = pBody->get_FaceShells(&pShells);
	if (FAILED(hr)) return hr;

	// Enumerate through the shells.
	long shellCount = 1;
	CComPtr<FaceShell> pShell;
	for (;(hr = pShells->get_Item(shellCount, &pShell)) == S_OK; pShell.Release())
	{
		// Increment the counter and print the current value.
		++shellCount;
		wprintf_s(L"  Shell %d\n", shellCount);

		// Get the faces from the shell.
		CComPtr<Faces> pFaces;
		hr = pShell->get_Faces(&pFaces);
		if (FAILED(hr)) return hr;

		// Enumerate through the faces of the current shell.
		long faceCount = 1;
		CComPtr<Face> pFace;
		for (;(hr = pFaces->get_Item(faceCount, &pFace)) == S_OK;pFace.Release())
		{
			// Increment the counter and print the current value.
			++faceCount;
			wprintf_s(L"    Face %d\n", faceCount);

			// Get the geometry from the face.
			SurfaceTypeEnum surfaceType;
			hr = pFace->get_SurfaceType(&surfaceType);
			if (FAILED(hr)) return hr;

			// Check to see what type of surface the current
			// geometry is.  Do some additional processing if 
			// it is a cylinder, otherwise just print the type.
			if( surfaceType == kCylinderSurface )
			{
				// Get the cylinder geometry.
				CComPtr<IDispatch> pFaceGeom;
				hr = pFace->get_Geometry(&pFaceGeom);
				if (FAILED(hr)) return hr;

				CComQIPtr<Cylinder> pCylinder(pFaceGeom);

				// Get the Radius.
				double radius = 0;
				hr = pCylinder->get_Radius(&radius);
				if (FAILED(hr)) return hr;

				// Get the evaluator from the face.
				CComPtr<SurfaceEvaluator> pSurfEval;
				hr = pFace->get_Evaluator(&pSurfEval);
				if (FAILED(hr)) return hr;

				// Get the parametric range of the surface.
				CComPtr<Box2d> pParamRange;
				hr = pSurfEval->get_ParamRangeRect(&pParamRange);
				if (FAILED(hr)) return hr;

				CComPtr<Point2d> pMinPoint;
				hr = pParamRange->get_MinPoint(&pMinPoint);
				if (FAILED(hr)) return hr;

				CComPtr<Point2d> pMaxPoint;
				hr = pParamRange->get_MaxPoint(&pMaxPoint);
				if (FAILED(hr)) return hr;

				double minPoint[2];
				hr = pMinPoint->get_X(&minPoint[0]);
				if (FAILED(hr)) return hr;

				hr = pMinPoint->get_Y(&minPoint[1]);
				if (FAILED(hr)) return hr;

				double maxPoint[2];
				hr = pMaxPoint->get_X(&maxPoint[0]);
				if (FAILED(hr)) return hr;

				hr = pMaxPoint->get_Y(&maxPoint[1]);
				if (FAILED(hr)) return hr;

				// Define a point that is at the center of the parametric range.
				CComSafeArray<double> midPoint;
				midPoint.Add(2, minPoint);
				midPoint.Add(2, maxPoint);

				CComSafeArray<double> *maxTangents;
				maxTangents =  new CComSafeArray<double>;

				CComSafeArray<double> *maxCurvature;
				maxCurvature =  new CComSafeArray<double>;

				CComSafeArray<double> *minCurvature;
				minCurvature =  new CComSafeArray<double>;

				hr = pSurfEval->GetCurvatures(midPoint.GetSafeArrayPtr(), (*maxTangents).GetSafeArrayPtr(), (*maxCurvature).GetSafeArrayPtr(), (*minCurvature).GetSafeArrayPtr());
				if (FAILED(hr)) return hr;

				// Calculate the radius from the curvature.

				// Print the curvature radius.
				double curvatureRadius = 1.0 / (*maxCurvature)[0];
				wprintf_s( L"     Cylindrical face, cylinder radius = %lf, curvature radius = %lf\n", radius, curvatureRadius);
			}
			else if( surfaceType == kPlaneSurface )
				wprintf_s( L"     Planar face\n");
			else if( surfaceType == kConeSurface )
				wprintf_s( L"     Conical face\n");
			else if( surfaceType == kSphereSurface )
				wprintf_s( L"     Spherical face\n");
			else if( surfaceType == kTorusSurface )
				wprintf_s( L"     Toroidal face\n");
			else if( surfaceType == kBSplineSurface )
				wprintf_s( L"     B-Spline face\n");
			else
				wprintf_s( L"     Unexpected geometry type.\n");

			// Get the edgeloops from the face.
			CComPtr<EdgeLoops> pEdgeLoops;
			hr = pFace->get_EdgeLoops(&pEdgeLoops);
			if (FAILED(hr)) return hr;

			// Enumerate through the loops of the current face.
			long loopCount = 1;
			CComPtr<EdgeLoop> pEdgeLoop;
			for (;(hr = pEdgeLoops->get_Item(loopCount, &pEdgeLoop)) == S_OK;pEdgeLoop.Release())
			{
				// Increment the counter and print the current value.
				++loopCount;
				wprintf_s(L"      Loop %d\n", loopCount);

				// Get the edges from the loop.
				CComPtr<Edges> pEdges;
				hr = pEdgeLoop->get_Edges(&pEdges);
				if (FAILED(hr)) return hr;

				// Enumerate through the edges of the current loop.
				long edgeCount = 1;
				CComPtr<Edge> pEdge;
				for (;(hr = pEdges->get_Item(edgeCount, &pEdge)) == S_OK;pEdge.Release())
				{
					// Get the vertices from the edge.
					CComPtr<Vertex> pVertex;
					hr = pEdge->get_StartVertex(&pVertex);
					if (FAILED(hr)) return hr;

					CComSafeArray<double> *startPoint;
					startPoint = new CComSafeArray<double>;

					hr = pVertex->GetPoint((*startPoint).GetSafeArrayPtr());
					if (FAILED(hr)) return hr;

					pVertex.Release();

					hr = pEdge->get_StopVertex(&pVertex);
					if (FAILED(hr)) return hr;

					CComSafeArray<double> *endPoint;
					endPoint = new CComSafeArray<double>;

					hr = pVertex->GetPoint((*endPoint).GetSafeArrayPtr());
					if (FAILED(hr)) return hr;

					++edgeCount;
					wprintf_s(L"        Edge %d, end vertices: (%.3lf,%.3lf,%.3lf)-(%.3lf,%.3lf,%.3lf)\n", edgeCount,
						(*startPoint)[0], (*startPoint)[1], (*startPoint)[2], (*endPoint)[0], (*endPoint)[1], (*endPoint)[2]);

				}
			}

			wprintf_s (L"\n\nContinuing...press Enter _: ");
			TCHAR Return[81];
			_getts_s (Return);
		}
	}

	return S_OK;
}
