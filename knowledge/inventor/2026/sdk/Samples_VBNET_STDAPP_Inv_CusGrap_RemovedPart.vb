Option Strict Off
Option Explicit On
Module modRemovedPart
	
	'draw the cut portion
	Public Sub DrawCutPortion()
		
		' Set the number of sides for the cylinder.
		Dim iSideCount As Integer
		iSideCount = Accuracy
		
		' Create an array containing points to used in drawing the cylinder.
		' The points could also be directly defined in coordinate set, but
		' defining them in array and then setting the coordinates using the
		' array is more efficient for a large set of points.
		Dim RemovedPartPointCoords() As Double
        ReDim RemovedPartPointCoords((iSideCount * 2 + 2) * 3)
		Dim i As Integer
		Dim dAngle As Double
		' Define the points for the outline of one end of the cylinder.
		For i = 0 To iSideCount - 1
            RemovedPartPointCoords(i * 3) = dHole * System.Math.Cos(dAngle)
            RemovedPartPointCoords(i * 3 + 1) = dHole * System.Math.Sin(dAngle)
            RemovedPartPointCoords(i * 3 + 2) = 0.0#
			
			' Increment the angle for the next point
			dAngle = dAngle + ((2 * 3.14159265358979) / iSideCount)
		Next 
		
		' Define the points for the outline of the other end of the cylinder.
		dAngle = 0
		For i = iSideCount To (iSideCount * 2) - 1
            RemovedPartPointCoords(i * 3) = dHole * System.Math.Cos(dAngle)
            RemovedPartPointCoords(i * 3 + 1) = dHole * System.Math.Sin(dAngle)
            RemovedPartPointCoords(i * 3 + 2) = dExtrudeHeight
			
			' Increment the angle for the next point
			dAngle = dAngle + ((2 * 3.14159265358979) / iSideCount)
		Next 
		
		' Define coordinates at the center of each end of the cylinder.
        RemovedPartPointCoords((iSideCount * 2) * 3) = 0
        RemovedPartPointCoords((iSideCount * 2) * 3 + 1) = 0
        RemovedPartPointCoords((iSideCount * 2) * 3 + 2) = 0
        RemovedPartPointCoords((iSideCount * 2) * 3 + 3) = 0
        RemovedPartPointCoords((iSideCount * 2) * 3 + 4) = 0
        RemovedPartPointCoords((iSideCount * 2) * 3 + 5) = 3.0#
		
		
		'create the removed part coordinate set object
		oRemovedPartCoordSet = oGraphicData.CreateCoordinateSet(kRemovedPartId)
		' Assign the points to the coordinate set.
		Call oRemovedPartCoordSet.PutCoordinates(RemovedPartPointCoords)
		
		
		
		' Create an index set to use for the triangle fan of one cap of the cylinder.
		' This will serve as in index look-up into the coordinate set.
		oRemovedPartCap1IndexSet = oGraphicData.CreateIndexSet(kRemovedPartId)
		
		' Set the index values.  (This could also be done in array first and then
		' assigned to the index set, which is more efficient).
		Call oRemovedPartCap1IndexSet.Add(1, iSideCount * 2 + 1)
		Call oRemovedPartCap1IndexSet.Add(2, 1)
		Call oRemovedPartCap1IndexSet.Add(3, 2)
		For i = 4 To iSideCount + 1
			Call oRemovedPartCap1IndexSet.Add(i, i - 1)
		Next 
		Call oRemovedPartCap1IndexSet.Add(iSideCount + 2, 1)
		
		
		' Create an index set to use for the triangle fan of the other cylinder cap.
		oRemovedPartCap2IndexSet = oGraphicData.CreateIndexSet(kRemovedPartId)
		
		' Set the index values.
        Call oRemovedPartCap2IndexSet.Add(1, iSideCount * 2 + 2)
		Call oRemovedPartCap2IndexSet.Add(2, iSideCount + 1)
		Call oRemovedPartCap2IndexSet.Add(3, iSideCount + 2)
		For i = 4 To iSideCount + 1
			Call oRemovedPartCap2IndexSet.Add(i, i + iSideCount - 1)
		Next 
		Call oRemovedPartCap2IndexSet.Add(iSideCount + 2, iSideCount + 1)
		
		
		
		' Create an index set to use for the triangle strip that will define the
		' sides of the cylinder.
		oRemovedPartCylinderIndexSet = oGraphicData.CreateIndexSet(kRemovedPartId)
		
		' Define the index values in an array.
		Dim iIndexValues() As Integer
        ReDim iIndexValues((iSideCount + 1) * 2)
		For i = 0 To iSideCount - 1
			Call oRemovedPartCylinderIndexSet.Add(i * 2 + 1, i + 1)
			Call oRemovedPartCylinderIndexSet.Add(i * 2 + 2, i + iSideCount + 1)
		Next 
		Call oRemovedPartCylinderIndexSet.Add(iSideCount * 2 + 1, 1)
		Call oRemovedPartCylinderIndexSet.Add(iSideCount * 2 + 2, iSideCount + 1)
		
		
		
		'create the removed part color set object
		oRemovedPartColorSet = oGraphicData.CreateColorSet(kRemovedPartId)
		'add the color to the color set object
		Call oRemovedPartColorSet.Add(1, 0, 255, 0)
		
		
		' Create a triangle fan for cap 1 of the cylinder, use the oRemovedPartCap1TriangleFan (TriangleFanGraphics) object
		oRemovedPartCap1TriangleFan = oRemovedPartNode.AddTriangleFanGraphics
		
		'set the coordinate set for the first cap
		oRemovedPartCap1TriangleFan.CoordinateSet = oRemovedPartCoordSet
		'set the index set for the first cap
		oRemovedPartCap1TriangleFan.CoordinateIndexSet = oRemovedPartCap1IndexSet
		'set the color set for the first cap
		oRemovedPartCap1TriangleFan.ColorSet = oRemovedPartColorSet
		
		
		' Create a triangle fan for cap 1 of the cylinder, use the oRemovedPartCap2TriangleFan (TriangleFanGraphics) object
		Dim oRemovedPartCap2TriangleFan As Inventor.TriangleFanGraphics
		oRemovedPartCap2TriangleFan = oRemovedPartNode.AddTriangleFanGraphics
		
		'set the coordinate set for the second cap
		oRemovedPartCap2TriangleFan.CoordinateSet = oRemovedPartCoordSet
		'set the index set for the second cap
		oRemovedPartCap2TriangleFan.CoordinateIndexSet = oRemovedPartCap2IndexSet
		'set the color set for the second cap
		oRemovedPartCap2TriangleFan.ColorSet = oRemovedPartColorSet
		
		
		
		' Create a triangle string for the sides of the cylinder use the oRemovedPartCylinderTriangleStrip (TriangleStripGraphics) object
		oRemovedPartCylinderTriangleStrip = oRemovedPartNode.AddTriangleStripGraphics
		
		'set the coordinate set for the cylinder
		oRemovedPartCylinderTriangleStrip.CoordinateSet = oRemovedPartCoordSet
		'set the index set for the cylinder
		oRemovedPartCylinderTriangleStrip.CoordinateIndexSet = oRemovedPartCylinderIndexSet
		'set the color set for the cylinder
		oRemovedPartCylinderTriangleStrip.ColorSet = oRemovedPartColorSet
		
		
		'update the view
		oInventorApp.ActiveView.Update()
		
		
	End Sub
	
	
	'remove the cut portion
	Public Sub RemoveCutPortion()
		
		
		'create the hole at the cut portion
		'get the part ComponentDefinition
		Dim oPartCompDef As Inventor.PartComponentDefinition
		oPartCompDef = oPartDocument.ComponentDefinition
		
		'access the sketch corresponding to the hole
		Dim oSketch As Inventor.PlanarSketch
		oSketch = oPartCompDef.Sketches.Item(2)
		
		'create the hole points
		Dim oHolePoints As Inventor.ObjectCollection
		oHolePoints = oInventorApp.TransientObjects.CreateObjectCollection
		oHolePoints.Add(oSketch.SketchPoints.Add(oInventorApp.TransientGeometry.CreatePoint2d(0, 0)))
		
		'create the hole
		Dim oHoleFeature As Inventor.HoleFeature
		oHoleFeature = oPartCompDef.Features.HoleFeatures.AddDrilledByThroughAllExtent(oHolePoints, dHole * 2#, Inventor.PartFeatureExtentDirectionEnum.kPositiveExtentDirection)
		
		
		'update the part
		oPartDocument.Update()
		
		'update the view
		oInventorApp.ActiveView.Update()
		
		
	End Sub
	
	
	'push out the cut portion
	Public Sub PushOutCutPortion()
		
		'remove the cut portion using the tool
		
		'declare the transformation matrices for removed part and tool
		Dim oCurrentTransform As Inventor.Matrix
		Dim oRemovedPartTransform As Inventor.Matrix
		
		'declare vectors to help set the transformation matrices
		Dim oToolVector As Inventor.Vector
		oToolVector = oInventorApp.TransientGeometry.CreateVector
		Dim oRemovedPartVector As Inventor.Vector
		oRemovedPartVector = oInventorApp.TransientGeometry.CreateVector
		Dim oTransVector As Inventor.Vector
		oTransVector = oInventorApp.TransientGeometry.CreateVector
		
		
		'set the transformation matrix to the current position of the laser tool
		oCurrentTransform = oLaserToolNode.Transformation
		
		'move the tool to the center of the hole
		oTransVector.X = -dHole
		oTransVector.Y = 0#
		oTransVector.Z = 0#
		
		'set the translation portion of the matrix
		Call oToolVector.AddVector(oTransVector)
		oCurrentTransform.SetTranslation(oToolVector)
		'set the tool transform
		oLaserToolNode.Transformation = oCurrentTransform
		
		
		'set the  number of steps
		Dim iNoSteps As Short
		iNoSteps = 100
		
		
		' Define the points for the outline of one end of the cylinder.
		Dim i As Short
		For i = 0 To iNoSteps - 1
			
			'set the oTransVector
			oTransVector.X = 0#
			oTransVector.Y = 0#
			oTransVector.Z = -dHeight / iNoSteps
			
			'set the translation vector of the transformation
			'get the current matrix from the laser tool graphics node object
			oCurrentTransform = oLaserToolNode.Transformation
			'add oTransVector to oToolVector
			Call oToolVector.AddVector(oTransVector)
			'set the translation portion of the matrix
			oCurrentTransform.SetTranslation(oToolVector)
			
			'set the tool transform
			oLaserToolNode.Transformation = oCurrentTransform
			
			'when the laser tool has reached the cut portion, transform that also
			If i > iNoSteps * dExtrudeHeight / (dHeight - dToolLength) Then
				
				'add oTransVector to oRemovedPartVector
				oRemovedPartTransform = oRemovedPartNode.Transformation
				'get the current matrix from the removed part graphics object
				Call oRemovedPartVector.AddVector(oTransVector)
				'set the translation portion of the matrix
				oRemovedPartTransform.SetTranslation(oRemovedPartVector)
				
				'set the removed part transform
				oRemovedPartNode.Transformation = oRemovedPartTransform
				
			End If
			
			'update the view
			oInventorApp.ActiveView.Update()
			
			
		Next 
	End Sub
End Module