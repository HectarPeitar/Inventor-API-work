Option Strict Off
Option Explicit On
Module modLaserTool
	
	'draw the cylindrical laser tool
	Public Sub DrawLaserTool()
		
		' Set the number of sides for the cylinder.
		Dim iSideCount As Integer
		iSideCount = Accuracy
		
		' Create an array containing points to used in drawing the cylinder.
		Dim ToolPointCoords() As Double
        ReDim ToolPointCoords((iSideCount * 2 + 2) * 3 - 1)
		Dim i As Integer
		Dim dAngle As Double
		' Define the points for the outline of one end of the cylinder.
		For i = 0 To iSideCount - 1
            ToolPointCoords(i * 3) = dHole + dToolDia * System.Math.Cos(dAngle)
            ToolPointCoords(i * 3 + 1) = dToolDia * System.Math.Sin(dAngle)
            ToolPointCoords(i * 3 + 2) = dHeight
			
			' Increment the angle for the next point
			dAngle = dAngle + ((2 * 3.14159265358979) / iSideCount)
		Next 
		
		' Define the points for the outline of the other end of the cylinder.
		dAngle = 0
		For i = iSideCount To (iSideCount * 2) - 1
            ToolPointCoords(i * 3) = dHole + dToolDia * System.Math.Cos(dAngle)
            ToolPointCoords(i * 3 + 1) = dToolDia * System.Math.Sin(dAngle)
            ToolPointCoords(i * 3 + 2) = dToolLength + dHeight
			
			' Increment the angle for the next point
			dAngle = dAngle + ((2 * 3.14159265358979) / iSideCount)
		Next 
		
		' Define coordinates at the center of each end of the cylinder.
        ToolPointCoords((iSideCount * 2) * 3) = dHole
        ToolPointCoords((iSideCount * 2) * 3 + 1) = 0
        ToolPointCoords((iSideCount * 2) * 3 + 2) = dHeight
        ToolPointCoords((iSideCount * 2) * 3 + 3) = dHole
        ToolPointCoords((iSideCount * 2) * 3 + 4) = 0
        ToolPointCoords((iSideCount * 2) * 3 + 5) = dToolLength + dHeight
		
		
		
		'create the laser tool coordinate set object
		oLaserToolCoordSet = oGraphicData.CreateCoordinateSet(kLaserToolId)
		'assign the points to the coordinate set
		Call oLaserToolCoordSet.PutCoordinates(ToolPointCoords)
		
		
		
		' Create an index set to use for the triangle fan of one cap of the cylinder.
		' This will serve as in index look-up into the coordinate set.
		oLaserToolCap1IndexSet = oGraphicData.CreateIndexSet(kLaserToolId)
		
		' Set the index values.  (This could also be done in array first and then
		' assigned to the index set, which is more efficient).
        Call oLaserToolCap1IndexSet.Add(1, iSideCount * 2)
        Call oLaserToolCap1IndexSet.Add(2, 1)
		Call oLaserToolCap1IndexSet.Add(3, 2)
		For i = 4 To iSideCount + 1
			Call oLaserToolCap1IndexSet.Add(i, i - 1)
		Next 
        Call oLaserToolCap1IndexSet.Add(iSideCount + 1, 1) '(iSideCount + 2, 1)
		
		
		
		' Create an index set to use for the triangle fan of the other cylinder cap.
		oLaserToolCap2IndexSet = oGraphicData.CreateIndexSet(kLaserToolId)
		
		' Set the index values.
        Call oLaserToolCap2IndexSet.Add(1, iSideCount * 2 + 1) '(1, iSideCount * 2 + 2)
        Call oLaserToolCap2IndexSet.Add(2, iSideCount) '(2, iSideCount + 1)
        Call oLaserToolCap2IndexSet.Add(3, iSideCount + 1) '(3, iSideCount + 2)
        For i = 4 To iSideCount  'iSideCount + 1
            Call oLaserToolCap2IndexSet.Add(i, i + iSideCount - 2) '(i, i + iSideCount - 1)
        Next
        Call oLaserToolCap2IndexSet.Add(iSideCount + 1, iSideCount) '(iSideCount + 2, iSideCount + 1)
		
		
		
		' Create an index set to use for the triangle strip that will define the sides of the cylinder.
		oLaserToolCylinderIndexSet = oGraphicData.CreateIndexSet(kLaserToolId)
		
		' Define the index values in an array.
		Dim iIndexValues() As Integer
        ReDim iIndexValues((iSideCount + 1) * 2)
		For i = 0 To iSideCount - 1
			Call oLaserToolCylinderIndexSet.Add(i * 2 + 1, i + 1)
			Call oLaserToolCylinderIndexSet.Add(i * 2 + 2, i + iSideCount + 1)
		Next 
		Call oLaserToolCylinderIndexSet.Add(iSideCount * 2 + 1, 1)
		Call oLaserToolCylinderIndexSet.Add(iSideCount * 2 + 2, iSideCount + 1)
		
		
		
		'create the laser tool color set object
		oLaserToolColorSet = oGraphicData.CreateColorSet(kLaserToolId)
		'assign the color to the color set object
		Call oLaserToolColorSet.Add(1, 0, 0, 255)
		
		
		
		' Create a triangle fan for cap 1 of the cylinder, use the oLaserToolCap1TriangleFan (TriangleFanGraphics) object
		oLaserToolCap1TriangleFan = oLaserToolNode.AddTriangleFanGraphics
		
		'set the coordinate set for the first cap
		oLaserToolCap1TriangleFan.CoordinateSet = oLaserToolCoordSet
		'set the index set for the first cap
		oLaserToolCap1TriangleFan.CoordinateIndexSet = oLaserToolCap1IndexSet
		'set the color set for the first cap
		oLaserToolCap1TriangleFan.ColorSet = oLaserToolColorSet
		
		
		
		' Create a triangle fan for cap 2 of the cylinder, use the oLaserToolCap2TriangleFan (TriangleFanGraphics) object
		oLaserToolCap2TriangleFan = oLaserToolNode.AddTriangleFanGraphics
		
		'set the coordinate set for the second cap
		oLaserToolCap2TriangleFan.CoordinateSet = oLaserToolCoordSet
		'set the index set for the second cap
		oLaserToolCap2TriangleFan.CoordinateIndexSet = oLaserToolCap2IndexSet
		'set the color set for the second cap
		oLaserToolCap2TriangleFan.ColorSet = oLaserToolColorSet
		
		
		' Create a triangle strip for the sides of the cylinder use the oLaserToolCylinderTriangleStrip (TriangleStripGraphics) object
		oLaserToolCylinderTriangleStrip = oLaserToolNode.AddTriangleStripGraphics
		
		'set the coordinate set for the cylinder
		oLaserToolCylinderTriangleStrip.CoordinateSet = oLaserToolCoordSet
		'set the index set for the cylinder
		oLaserToolCylinderTriangleStrip.CoordinateIndexSet = oLaserToolCylinderIndexSet
		'set the color set for the cylinder
		oLaserToolCylinderTriangleStrip.ColorSet = oLaserToolColorSet
		
		
		'update the view
		oInventorApp.ActiveView.Update()
		
	End Sub
	
	
	'move the laser tool in a circular path
	Public Sub MoveLaserTool()
		
		'create the vectors that help set the transformation matrix
		'create the resultant vector
		Dim oVector As Inventor.Vector
		oVector = oTransGeom.CreateVector
		'create the resultant vector
		Dim oTransVector As Inventor.Vector
		oTransVector = oTransGeom.CreateVector
		
		
		'set the no. of steps in which to complete the laser tool movement
		Dim iSideCount As Short
		iSideCount = 75
		
		'set the radius of drilling
		Dim dRadius As Double
		dRadius = dHole
		
		'set the previousx position of laser
		Dim previousx As Double
		previousx = dHole
		
		'set the previousy position of laser
		Dim previousy As Double
		previousy = 0#
		
		'set the angle increment
		Dim dAngle As Double
		dAngle = 0#
		
		
		
		' Define the points for the outline of one end of the cylinder.
		Dim i As Short
		Dim oCurrentTransform As Inventor.Matrix
		For i = 0 To iSideCount - 1
			
			'set the new x position of laser
			oTransVector.X = dRadius * System.Math.Cos(dAngle) - previousx
			'set the new y position of laser
			oTransVector.Y = dRadius * System.Math.Sin(dAngle) - previousy
			'the z position is always 0
			oTransVector.Z = 0#
			
			'declare and set the translation portion to the matrix
			'get the current matrix for the tool
			oCurrentTransform = oLaserToolNode.Transformation
			'add the oTransVector to oVector to increment it
			Call oVector.AddVector(oTransVector)
			'set the translation of the current matrix to the vector oVector
			oCurrentTransform.SetTranslation(oVector)
			
			'set the tool transform to the transformed matrix
			oLaserToolNode.Transformation = oCurrentTransform
			
			'set the laser path transform to the transformed matrix
			oLaserPathNode.Transformation = oCurrentTransform
			
			'set the sparks transform to the transformed matrix
			oSparksNode.Transformation = oCurrentTransform
			
			'call the method to extend the laser trace
			ExtendLaserTrace(dRadius * System.Math.Cos(dAngle), dRadius * System.Math.Sin(dAngle), dExtrudeHeight, i + 1)
			
			'update the view
			oInventorApp.ActiveView.Update()
			
			' Increment the angle for the next point
			previousx = dRadius * System.Math.Cos(dAngle)
			previousy = dRadius * System.Math.Sin(dAngle)
			dAngle = dAngle + ((2 * 3.14159265358979) / iSideCount)
			
		Next 
		
		'after laser cutting,make laser and sparks invisible
		oLaserPathNode.Visible = False
		oSparksNode.Visible = False
		
		
		'update the view
		oInventorApp.ActiveView.Update()
		
		
	End Sub
End Module