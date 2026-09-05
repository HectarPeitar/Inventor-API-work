Option Strict Off
Option Explicit On
Module modSparks
	
	'draw the sparks
	Public Sub DrawSparks()
		
		'Set a reference to the transient geometry object for user later.
		Dim oTransGeom As Inventor.TransientGeometry
		oTransGeom = oInventorApp.TransientGeometry
		
		' Set the number of sides for the cylinder.
		Dim iNoSparks As Integer
		iNoSparks = 15
		
		' Create an array containing points to used in drawing the cylinder.
		' The points could also be directly defined in coordinate set, but
		' defining them in array and then setting the coordinates using the
		' array is more efficient for a large set of points.
		Dim SparkPointCoords() As Double
        ReDim SparkPointCoords((iNoSparks * 2) * 3 - 1)
		Dim i As Integer
		Dim dAngle As Double
		dAngle = 0#
		
		' Define the points for the outline of one end of the cylinder.
		For i = 0 To iNoSparks * 2 - 1 Step 2
            SparkPointCoords(i * 3) = dHole
            SparkPointCoords(i * 3 + 1) = 0.0#
            SparkPointCoords(i * 3 + 2) = dExtrudeHeight
            SparkPointCoords((i + 1) * 3) = dHole + dToolDia * System.Math.Cos(dAngle) * 1.5
            SparkPointCoords((i + 1) * 3 + 1) = dToolDia * System.Math.Sin(dAngle) * 1.5
            SparkPointCoords((i + 1) * 3 + 2) = dExtrudeHeight + dHeight / 15.0#
			
			' Increment the angle for the next point
			dAngle = dAngle + ((2 * 3.14159265358979) / iNoSparks)
		Next 
		
		
		'create the sparks coordinate set object
		oSparksCoordSet = oGraphicData.CreateCoordinateSet(kSparksId)
		'assign the points to the coordinate set.
		Call oSparksCoordSet.PutCoordinates(SparkPointCoords)
		
		
		'create the sparks color set object
		oSparksColorSet = oGraphicData.CreateColorSet(kSparksId)
		'also, assign the color to the object
		Call oSparksColorSet.Add(1, 255, 255, 0)
		
		
		' Create the graphics for the sparks, use the oSparksLineStrip (LineStripGraphics) object
		oSparksLineStrip = oSparksNode.AddLineStripGraphics
		
		' Set the coordinates for the sparks
		oSparksLineStrip.CoordinateSet = oSparksCoordSet
		'assign the color set for the sparks
		oSparksLineStrip.ColorSet = oSparksColorSet
		
		
		'update the view
		oInventorApp.ActiveView.Update()
		
		
	End Sub
End Module