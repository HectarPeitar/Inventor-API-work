Option Strict Off
Option Explicit On
Module modGlobals
	
	'declare the Application object
	Public oInventorApp As Inventor.Application
	
	'declare the PartDocument object
	Public oPartDocument As Inventor.PartDocument
	
	'declare a TransientGeometry object
	Public oTransGeom As Inventor.TransientGeometry
	
	'declare the graphics data set
	Public oGraphicData As Inventor.GraphicsDataSets
	
	'declare the client graphics object
	Public oGraphics As Inventor.ClientGraphics
	
	'declare the coordinate sets
	Public oLaserPathCoordSet As Inventor.GraphicsCoordinateSet
	Public oLaserToolCoordSet As Inventor.GraphicsCoordinateSet
	Public oSparksCoordSet As Inventor.GraphicsCoordinateSet
	Public oLaserTraceCoordSet As Inventor.GraphicsCoordinateSet
	Public oRemovedPartCoordSet As Inventor.GraphicsCoordinateSet
	
	'declare the index set objects
	Public oLaserToolCap1IndexSet As Inventor.GraphicsIndexSet
	Public oLaserToolCap2IndexSet As Inventor.GraphicsIndexSet
	Public oLaserToolCylinderIndexSet As Inventor.GraphicsIndexSet
	Public oRemovedPartCap1IndexSet As Inventor.GraphicsIndexSet
	Public oRemovedPartCap2IndexSet As Inventor.GraphicsIndexSet
	Public oRemovedPartCylinderIndexSet As Inventor.GraphicsIndexSet
	
	'declare the color set objects
	Public oLaserPathColorSet As Inventor.GraphicsColorSet
	Public oLaserToolColorSet As Inventor.GraphicsColorSet
	Public oSparksColorSet As Inventor.GraphicsColorSet
	Public oLaserTraceColorSet As Inventor.GraphicsColorSet
	Public oRemovedPartColorSet As Inventor.GraphicsColorSet
	
	
	
	'declare the client graphics node objects
	Public oLaserPathNode As Inventor.GraphicsNode
	Public oLaserToolNode As Inventor.GraphicsNode
	Public oSparksNode As Inventor.GraphicsNode
	Public oLaserTraceNode As Inventor.GraphicsNode
	Public oRemovedPartNode As Inventor.GraphicsNode
	
	'declare the graphics objects
	'laser tool
	Public oLaserToolCap1TriangleFan As Inventor.TriangleFanGraphics
	Public oLaserToolCap2TriangleFan As Inventor.TriangleFanGraphics
	Public oLaserToolCylinderTriangleStrip As Inventor.TriangleStripGraphics
	'removed part
	Public oRemovedPartCap1TriangleFan As Inventor.TriangleFanGraphics
	Public oRemovedPartCap2TriangleFan As Inventor.TriangleFanGraphics
	Public oRemovedPartCylinderTriangleStrip As Inventor.TriangleStripGraphics
	'laser path
	Public oLaserPathLine As Inventor.LineGraphics
	'laser trace
	Public oLaserTraceLineStrip As Inventor.LineStripGraphics
	'sparks
	Public oSparksLineStrip As Inventor.LineStripGraphics
	
	
	'declare the ClientId for the graphics and data sets objects
	Public Const kLaserOperationID As String = "LaserCutOperation"
	
	'declare the NodeId's for the client graphics
	Public Const kLaserPathId As Short = 1
	Public Const kLaserToolId As Short = 2
	Public Const kSparksId As Short = 3
	Public Const kLaserTraceId As Short = 4
	Public Const kRemovedPartId As Short = 5
	
	
	'laser operation parameters
	'diameter of hole to be drilled
	Public dHole As Double
	'height from which to be drilled
	Public dHeight As Double
	
	'laser tool parameters
	Public dToolDia As Double
	Public dToolLength As Double
	
	'extrusion thicknes
	Public dExtrudeHeight As Double
	
	'accuracy for display
	Public Accuracy As Integer
	
	Public Const Pi As Double = 3.14159265358979
	
    Public Sub Main_Renamed()

    End Sub
End Module