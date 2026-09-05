Option Strict Off
Option Explicit On
Friend Class frmEntityInformation
	Inherits System.Windows.Forms.Form
	
	Private Sub cmdOK_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdOK.Click
		Me.Close()
	End Sub
	
	Public Sub DisplaySurfaceBodyInformation(ByRef objSurfaceBody As Inventor.SurfaceBody)
		
		'determine if the surface body is a solid or not
		Dim strSolid As String
		If objSurfaceBody.IsSolid = True Then
			strSolid = "Solid"
		Else
			strSolid = "Non-Solid"
		End If
		
		'determine the volume of the surface body
		Dim dblVolume As Double
		dblVolume = objSurfaceBody.Volume(1)
		
		'obtain the range box information (min points and max points) for each of the face shells
		'loop through the FaceShells of the SurfaceBody
		Dim objFaceShell As Inventor.FaceShell
		Dim objFaceRangeBox As Inventor.Box
        Dim objMaxPoint As Inventor.Point = Nothing
        Dim objMinPoint As Inventor.Point = Nothing
		For	Each objFaceShell In objSurfaceBody.FaceShells
			
			'obtain the RangeBox of the FaceShell
			objFaceRangeBox = objFaceShell.RangeBox
			
			'obtain the Maxpoint and Minpoint
			
			objMaxPoint = objFaceRangeBox.MaxPoint
			objMinPoint = objFaceRangeBox.MinPoint
			
		Next objFaceShell
		
		'add all the above information to the list box
		list.Items.Add("Surface Body Information")
        list.Items.Add("Type = " & strSolid & " ,Volume = " & dblVolume.ToString("0.000"))
		list.Items.Add(Space(1) & "Box information within which the body is contained:")
		
		list.Items.Add(Space(2) & "MinPoint : (" & objMinPoint.X.ToString("0.000") & ", " & objMinPoint.Y.ToString("0.000") & ", " & objMinPoint.Z.ToString("0.000") & ")")
        list.Items.Add(Space(2) & "MaxPoint : (" & objMaxPoint.X.ToString("0.000") & ", " & objMaxPoint.Y.ToString("0.000") & ", " & objMaxPoint.Z.ToString("0.000") & ")")
		
		Me.Show()
		
	End Sub
	
	Public Sub DisplayFaceInformation(ByRef objFace As Inventor.Face)
		
		'determine the surface type of the face
        Dim strSurfaceType As String = ""
		
		Select Case objFace.SurfaceType
			Case Inventor.SurfaceTypeEnum.kBSplineSurface
				strSurfaceType = "BSpline"
			Case Inventor.SurfaceTypeEnum.kConeSurface
				strSurfaceType = "Cone"
			Case Inventor.SurfaceTypeEnum.kCylinderSurface
				strSurfaceType = "Cylinder"
			Case Inventor.SurfaceTypeEnum.kEllipticalConeSurface
				strSurfaceType = "Elliptical Cone"
			Case Inventor.SurfaceTypeEnum.kEllipticalCylinderSurface
				strSurfaceType = "Elliptical Cylinder"
			Case Inventor.SurfaceTypeEnum.kPlaneSurface
				strSurfaceType = "Plane"
			Case Inventor.SurfaceTypeEnum.kSphereSurface
				strSurfaceType = "Sphere"
			Case Inventor.SurfaceTypeEnum.kTorusSurface
				strSurfaceType = "Torus"
			Case Inventor.SurfaceTypeEnum.kUnknownSurface
                strSurfaceType = "Unknown"
        End Select
		
		'add the surface type info to the list box
		list.Items.Add("Face Information")
		list.Items.Add(Space(1) & "Type of face : " & strSurfaceType)
		
		'determine the vertices information
		Dim lngNoVertices As Integer
		lngNoVertices = objFace.Vertices.Count
		
		list.Items.Add(Space(2) & "Vertices information: no. of vertices : " & CStr(lngNoVertices))
		list.Items.Add(Space(5) & "X" & Space(10) & "Y" & Space(10) & "Z")
		
		'determine the coordinates of each of the vertices
		Dim objVertex As Inventor.Vertex
		'loop through the vertices
		Dim dblPoint(3) As Double
		For	Each objVertex In objFace.Vertices
			
			'get the point at the vertex
			objVertex.GetPoint(dblPoint)
			
			'add the coordinates to the list
            list.Items.Add(Space(2) & dblPoint(0).ToString("0.000") & ", " & dblPoint(1).ToString("0.000") & ", " & dblPoint(2).ToString("0.000"))
		Next objVertex
		
		'evalutator information
		'declare the SurfaceEvaluator object
		Dim objFaceEvaluator As Inventor.SurfaceEvaluator
		objFaceEvaluator = objFace.Evaluator
		
		Dim dblFaceArea As Double
		Dim objParamRange As Inventor.Box2d
		Dim dblU As Double
		Dim dblV As Double
        Dim dblFacePoints(2) As Double
        Dim dblFaceNormals(2) As Double
        Dim dblFaceUTangents(2) As Double
        Dim dblFaceVTangents(2) As Double
        Dim dblFaceParams(1) As Double
		If Not objFaceEvaluator Is Nothing Then
			
			'determine the area of the face
			dblFaceArea = objFaceEvaluator.Area
			
            list.Items.Add(Space(1) & "Area = " & dblFaceArea.ToString("0.000"))
			
			'get the Parametric range (box2d) from the evaluator
			objParamRange = objFaceEvaluator.ParamRangeRect
			
			list.Items.Add(Space(1) & "Normal and Tangent information:")
			list.Items.Add(Space(10) & "Point" & Space(25) & "Normal" & Space(20) & "Tangent")
			
			'declare the parameter space coordinate variables
			
			'iterate through the points in the parameter space and obtain the actual 3d coordinates and normals, tangents at the points on the face
			For dblU = objParamRange.MinPoint.X To objParamRange.MaxPoint.X Step 0.5
				For dblV = objParamRange.MinPoint.Y To objParamRange.MaxPoint.Y Step 0.5
					
                    dblFaceParams(0) = dblU
                    dblFaceParams(1) = dblV
					
					'get the 3D point using the parameter space coordinates
					objFaceEvaluator.GetPointAtParam(dblFaceParams, dblFacePoints)
					
					'get the normals
					objFaceEvaluator.GetNormal(dblFaceParams, dblFaceNormals)
					
					'get the tangents
					objFaceEvaluator.GetTangents(dblFaceParams, dblFaceUTangents, dblFaceVTangents)
					
					'add the information to the list box
                    list.Items.Add(Space(2) & dblFacePoints(0).ToString("0.000") & ", " & dblFacePoints(1).ToString("0.000") & ", " & dblFacePoints(2).ToString("0.000") & Space(4) & dblFaceNormals(0).ToString("0.000") & ", " & dblFaceNormals(1).ToString("0.000") & ", " & dblFaceNormals(2).ToString("0.000") & Space(4) & dblFaceUTangents(0).ToString("0.000") & ", " & dblFaceUTangents(1).ToString("0.000") & ", " & dblFaceUTangents(2).ToString("0.000"))
				Next 
			Next 
		End If
		
		Me.Show()
		
	End Sub
	
	Public Sub DisplayEdgeInformation(ByRef objEdge As Inventor.Edge)
		
		'determine the curve type of the edge
        Dim strEdgeType As String = ""
		
		Select Case objEdge.CurveType
			Case Inventor.CurveTypeEnum.kBSplineCurve
				strEdgeType = "BSpline"
			Case Inventor.CurveTypeEnum.kCircleCurve
				strEdgeType = "Circle"
			Case Inventor.CurveTypeEnum.kCircularArcCurve
				strEdgeType = "Circular Arc"
			Case Inventor.CurveTypeEnum.kEllipseFullCurve
				strEdgeType = "Ellipse Full"
			Case Inventor.CurveTypeEnum.kEllipticalArcCurve
				strEdgeType = "Elliptical Arc"
			Case Inventor.CurveTypeEnum.kLineCurve
				strEdgeType = "Line"
			Case Inventor.CurveTypeEnum.kLineSegmentCurve
				strEdgeType = "Line Segment"
			Case Inventor.CurveTypeEnum.kUnknownCurve
				strEdgeType = "Unknown"
		End Select
		
		'add information to the list box
		list.Items.Add("Edge Information")
		list.Items.Add(Space(1) & "Type of edge : " & strEdgeType)
		
		'get the curve evaluator object
		Dim objEdgeEvaluator As Inventor.CurveEvaluator
		objEdgeEvaluator = objEdge.Evaluator
		
		Dim dblUMin As Double
		Dim dblUMax As Double
		Dim dblU As Double

        Dim dblEdgePoints(2) As Double
        Dim dblEdgeUTangents(2) As Double
        Dim dblEdgeParams(0) As Double
		If Not objEdgeEvaluator Is Nothing Then
			
			'get the param extents
			objEdgeEvaluator.GetParamExtents(dblUMin, dblUMax)
			
			list.Items.Add(Space(1) & "Tangent information:")
			list.Items.Add(Space(10) & "Point" & Space(25) & "Tangent")
			
			'declare the parameter space coordinate variables
			
			'iterate through the points in the parameter space and obtain the actual 3d coordinates and  tangents at the points on the edge
			For dblU = dblUMin To dblUMax Step 0.5
				
				'declare and assign a parameter array
                dblEdgeParams(0) = dblU
				
				'get the point at the parameter
				objEdgeEvaluator.GetPointAtParam(dblEdgeParams, dblEdgePoints)
				
				'get the tangent at the parameter point
				objEdgeEvaluator.GetTangent(dblEdgeParams, dblEdgeUTangents)
				
				'add the information to the list box
                list.Items.Add(Space(2) & dblEdgePoints(0).ToString("0.000") & ", " & dblEdgePoints(1).ToString("0.000") & ", " & dblEdgePoints(2).ToString("0.000") & Space(4) & dblEdgeUTangents(0).ToString("0.000") & ", " & dblEdgeUTangents(1).ToString("0.000") & ", " & dblEdgeUTangents(2).ToString("0.000"))
			Next 
		End If
		
		'determine the start vertex and stop vertex of the edge
		Dim objStartVertex As Inventor.Vertex
		objStartVertex = objEdge.StartVertex
		
		Dim objStopVertex As Inventor.Vertex
		objStopVertex = objEdge.StopVertex
		
        Dim dblStartPoint(2) As Double
        Dim dblStopPoint(2) As Double
		
		'get the points from the start and stop vertices
		objStartVertex.GetPoint(dblStartPoint)
		objStopVertex.GetPoint(dblStopPoint)
		
        list.Items.Add(Space(2) & "StartVertex : (" & dblStartPoint(0).ToString("0.000") & ", " & dblStartPoint(1).ToString("0.000") & ", " & dblStartPoint(2).ToString("0.000") & ")")
        list.Items.Add(Space(2) & "StopVertex : (" & dblStopPoint(0).ToString("0.000") & ", " & dblStopPoint(1).ToString("0.000") & ", " & dblStopPoint(2).ToString("0.000") & ")")
		
		Me.Show()
		
	End Sub
End Class