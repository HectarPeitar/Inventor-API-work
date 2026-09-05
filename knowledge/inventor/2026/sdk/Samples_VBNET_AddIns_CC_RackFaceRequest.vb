Imports Inventor
Imports System.Runtime.InteropServices


Friend Class RackFaceRequest
    Inherits CustomCommand.ChangeRequest

    'Inventor application object
    Private m_application As Application

    'Rack face command parameters
    Private m_rackFace As Face
    Private m_rackEdge As Edge

    Private m_numTeeth As Integer
    Private m_rackHeight As Double
    Private m_rackWidth As Double
    Private m_rackExtents As Double
    Private m_rackFeatureExtentDirection As PartFeatureExtentDirectionEnum

    Public Sub New(ByVal application As Application, _
                    ByVal rackFace As Face, _
                    ByVal rackEdge As Edge, _
                    ByVal numTeeth As Integer, _
                    ByVal rackHeight As Double, _
                    ByVal rackWidth As Double, _
                    ByVal rackExtents As Double, _
                    ByVal rackFeatureExtentDirection As PartFeatureExtentDirectionEnum)

        m_application = application
        m_rackFace = rackFace
        m_rackEdge = rackEdge
        m_numTeeth = numTeeth
        m_rackHeight = rackHeight
        m_rackWidth = rackWidth
        m_rackExtents = rackExtents
        m_rackFeatureExtentDirection = rackFeatureExtentDirection

    End Sub

    Public Overrides Sub OnExecute(ByVal document As Document, ByVal context As NameValueMap, ByVal succeeded As Boolean)
        'Execute command functionality
        Dim partDocument As PartDocument
        partDocument = document

        Dim partCompDef As PartComponentDefinition
        partCompDef = partDocument.ComponentDefinition

        'Get rack edge start point and end point
        Dim rackEdgeStartVertex As Vertex
        rackEdgeStartVertex = m_rackEdge.StartVertex

        Dim rackEdgeStartPt As Point
        rackEdgeStartPt = rackEdgeStartVertex.Point

        Dim rackEdgeStopVertex As Vertex
        rackEdgeStopVertex = m_rackEdge.StopVertex

        Dim rackEdgeStopPt As Point
        rackEdgeStopPt = rackEdgeStopVertex.Point

        Dim rackEdgeLength As Double
        rackEdgeLength = rackEdgeStartPt.DistanceTo(rackEdgeStopPt)

        Dim nonRackWidth As Double
        nonRackWidth = rackEdgeLength - m_rackWidth

        Dim toothWidthProportion As Double : toothWidthProportion = 0.25

        Dim toothmajorWidth As Double
        toothmajorWidth = m_rackWidth / (m_numTeeth + (m_numTeeth - 1) * toothWidthProportion)

        Dim toothMinorWidth As Double
        toothMinorWidth = toothWidthProportion * toothmajorWidth

        Dim toothSlopeWidth As Double
        toothSlopeWidth = (toothmajorWidth - toothMinorWidth) / 2.0

        Dim rackStart As Double
        rackStart = nonRackWidth / 2.0

        Dim transientGeometry As TransientGeometry
        transientGeometry = m_application.TransientGeometry

        Dim transientObjects As TransientObjects
        transientObjects = m_application.TransientObjects

        Dim objEnumerator As Object : objEnumerator = Nothing
        Dim sketchLineCollection As ObjectCollection
        sketchLineCollection = transientObjects.CreateObjectCollection(objEnumerator)

        Dim workPlanes As WorkPlanes
        workPlanes = partCompDef.WorkPlanes

        Dim workPlane As WorkPlane
        workPlane = workPlanes.AddByLinePlaneAndAngle(m_rackEdge, m_rackFace, "90 deg")
        workPlane.Visible = False

        Dim planarSketches As PlanarSketches
        planarSketches = partCompDef.Sketches

        Dim planarSketch As PlanarSketch
        planarSketch = planarSketches.AddWithOrientation(workPlane, m_rackEdge, True, True, rackEdgeStartVertex)

        Dim sketchPoints As SketchPoints
        sketchPoints = planarSketch.SketchPoints

        Dim sketchLines As SketchLines
        sketchLines = planarSketch.SketchLines

        Dim point1 As Point2d
        Dim point2 As Point2d
        Dim point3 As Point2d
        Dim point4 As Point2d

        Dim sketchPoint1 As SketchPoint
        Dim sketchPoint2 As SketchPoint
        Dim sketchPoint3 As SketchPoint
        Dim sketchPoint4 As SketchPoint

        Dim sketchLine1 As SketchLine
        Dim sketchLine2 As SketchLine
        Dim sketchLine3 As SketchLine
        Dim sketchLine4 As SketchLine

        Dim yoothCt As Integer
        For yoothCt = 0 To m_numTeeth - 1

            point1 = transientGeometry.CreatePoint2d(rackStart, 0)
            point2 = transientGeometry.CreatePoint2d(rackStart + toothSlopeWidth, -m_rackHeight)
            point3 = transientGeometry.CreatePoint2d(rackStart + toothSlopeWidth + toothMinorWidth, -m_rackHeight)
            point4 = transientGeometry.CreatePoint2d(rackStart + toothmajorWidth, 0)

            sketchPoint1 = sketchPoints.Add(point1, False)
            sketchPoint2 = sketchPoints.Add(point2, False)
            sketchPoint3 = sketchPoints.Add(point3, False)
            sketchPoint4 = sketchPoints.Add(point4, False)

            sketchLine1 = sketchLines.AddByTwoPoints(sketchPoint1, sketchPoint2)
            sketchLine2 = sketchLines.AddByTwoPoints(sketchPoint2, sketchPoint3)
            sketchLine3 = sketchLines.AddByTwoPoints(sketchPoint3, sketchPoint4)
            sketchLine4 = sketchLines.AddByTwoPoints(sketchPoint4, sketchPoint1)

            sketchLineCollection.Add(sketchLine1)
            sketchLineCollection.Add(sketchLine2)
            sketchLineCollection.Add(sketchLine3)
            sketchLineCollection.Add(sketchLine4)

            sketchLine1 = Nothing
            sketchLine2 = Nothing
            sketchLine3 = Nothing
            sketchLine4 = Nothing

            point1 = Nothing
            point2 = Nothing
            point3 = Nothing
            point4 = Nothing

            sketchPoint1 = Nothing
            sketchPoint2 = Nothing
            sketchPoint3 = Nothing
            sketchPoint4 = Nothing

            rackStart = rackStart + (toothmajorWidth + toothMinorWidth)
        Next

        Dim profiles As Profiles
        profiles = planarSketch.Profiles

        Dim profile As Profile
        profile = profiles.AddForSolid(True, sketchLineCollection, 0)

        Dim partFeatures As PartFeatures
        partFeatures = partCompDef.Features

        Dim extrudeFeatures As ExtrudeFeatures
        extrudeFeatures = partFeatures.ExtrudeFeatures

        Dim distance As Object
        distance = IIf(m_rackFeatureExtentDirection = PartFeatureExtentDirectionEnum.kSymmetricExtentDirection, 2 * m_rackExtents, m_rackExtents)

        Dim extrudeFeature As ExtrudeFeature
        extrudeFeature = extrudeFeatures.AddByDistanceExtent(profile, distance, m_rackFeatureExtentDirection, PartFeatureOperationEnum.kCutOperation)


    End Sub
End Class
