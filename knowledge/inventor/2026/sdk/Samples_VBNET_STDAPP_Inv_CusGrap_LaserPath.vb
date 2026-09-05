Option Strict Off
Option Explicit On
Module modLaserPath
	
	'draw the laser path
	Public Sub DrawLaserPath()
		
		'laser path is just a line
        Dim LaserPathCoords(5) As Double
        LaserPathCoords(0) = dHole
        LaserPathCoords(1) = 0
        LaserPathCoords(2) = dExtrudeHeight
        LaserPathCoords(3) = dHole
        LaserPathCoords(4) = 0
        LaserPathCoords(5) = dHeight
		
		'create the laser path coordinate set object
		oLaserPathCoordSet = oGraphicData.CreateCoordinateSet(kLaserPathId)
		'assign the points to the coordinate set.
		Call oLaserPathCoordSet.PutCoordinates(LaserPathCoords)
		
		
		'create the laser path color set object
		oLaserPathColorSet = oGraphicData.CreateColorSet(kLaserPathId)
		'also,set the desired color
		Call oLaserPathColorSet.Add(1, 255, 0, 0)
		
		
		' Create the laser path graphics, use the oLaserPathLineStrip (LineGraphics object)
		oLaserPathLine = oLaserPathNode.AddLineGraphics
		
		' Set the coordinate set for the path
		oLaserPathLine.CoordinateSet = oLaserPathCoordSet
		'assign the color set for the path
		oLaserPathLine.ColorSet = oLaserPathColorSet
		
		
		'update the view
		oInventorApp.ActiveView.Update()
		
		
	End Sub
End Module