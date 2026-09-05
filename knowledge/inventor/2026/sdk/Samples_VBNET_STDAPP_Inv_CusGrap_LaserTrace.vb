Option Strict Off
Option Explicit On
Module modLaserTrace
	
	'draw the laser trace
	Public Sub ExtendLaserTrace(ByRef XCoord As Double, ByRef YCoord As Double, ByRef ZCoord As Double, ByRef Index As Short)
		
		'create the laser trace point
		Dim oLaserTracePoint As Inventor.Point
		oLaserTracePoint = oTransGeom.CreatePoint(XCoord, YCoord, ZCoord)
		
		
		'create the laser trace coordinate set object,only the first time, since this method will be called recursively
		If Index = 1 Then
			oLaserTraceCoordSet = oGraphicData.CreateCoordinateSet(kLaserTraceId)
		End If
		
		'add the points to the coordinate set
		Call oLaserTraceCoordSet.Add(Index, oLaserTracePoint)
		
		
		'create the laser trace color set object,only the first time, since this method will be called recursively
		If Index = 1 Then
			oLaserTraceColorSet = oGraphicData.CreateColorSet(kLaserTraceId)
			'also, add the color to the object
			Call oLaserTraceColorSet.Add(1, 25, 0, 0)
		End If
		
		
		' Create the laser trace path graphics, use the oLaserTraceLineStrip (LineStripGraphics) object
		oLaserTraceLineStrip = oLaserTraceNode.AddLineStripGraphics
		
		
		'set the coordinate set for the laser trace path
		oLaserTraceLineStrip.CoordinateSet = oLaserTraceCoordSet
		'assign the color set to the trace path
		oLaserTraceLineStrip.ColorSet = oLaserTraceColorSet
		
		
		'update the view
		oInventorApp.ActiveView.Update()
		
		
	End Sub
End Module