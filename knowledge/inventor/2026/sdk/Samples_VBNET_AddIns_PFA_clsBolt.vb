'clsBolt: An auxiliary class to build a bolt by given definitions

'import libraries
Imports Inventor

Public Class clsBolt

    Public Structure BoltParameter
        'user-defined parameters for building the bold
        Public strBoltID As String
        Public strHeadDiameter As String
        Public strHeadHeight As String
        Public strBodyLength As String
        Public strBodyDiameter As String
        Public strFilletRadius As String
        Public strChamferDistance As String
        Public strCutAngle As String
        Public strThreadLength As String
    End Structure

    'constant definitions
    Public Const AXIS_A1 As String = "MSC_A1"
    Public Const PLANE_PF1 As String = "MSC_PF1"
    Public Const PLANE_PT1 As String = "MSC_PT1"

    Public Const SKETCH_1 As String = "Sketch1"
    Public Const SKETCH_2 As String = "Sketch2"
    Public Const SKETCH_3 As String = "Sketch3"
    Public Const SKETCH_4 As String = "Sketch4"
    Public Const CHAMFER_1 As String = "Chamfer1"
    Public Const FILLET_1 As String = "Fillet1"
    Public Const HEAD_EXTRUSION As String = "HeadExtrusion"
    Public Const BODY_EXTRUSION As String = "BodyExtrusion"
    Public Const REVOLVE_1 As String = "Revolve1"
    Public Const REVOLVE_2 As String = "Revolve2"
    Public Const THREAD_1 As String = "Thread1"

    Public Const HEAD_DIAMETER As String = "HeadDiameter"
    Public Const HEAD_HEIGHT As String = "HeadHeight"
    Public Const BODY_LENGTH As String = "BodyLength"
    Public Const BODY_DIAMETER As String = "BodyDiameter"
    Public Const FILLET_RADIUS As String = "FilletRadius"
    Public Const CHAMFER_DISTANCE As String = "ChamferDistance"
    Public Const CUT_ANGLE As String = "CutAngle"
    Public Const THREAD_LENGTH As String = "ThreadLength"
    Public Const THREAD_TYPE As String = "ANSI Unified Screw Threads"
    Public Const THREAD_DESIGNATION As String = "1/2-13 UNC"
    Public Const THREAD_CLASS As String = "1A"

    'class variable definitions
    Private oapp As Application
    Private oTG As TransientGeometry
    Private opartCompDef As PartComponentDefinition
    Private olocation As Point
    Private oaxis1 As WorkAxis
    Private oplanePT1, oplanePF1 As WorkPlane
    Private osketch1, osketch2, osketch3, osketch4 As PlanarSketch
    Private oheadExt, obodyExt As ExtrudeFeature
    Private ochamfer As ChamferFeature
    Private ofillet As FilletFeature
    Private ocutRev1, ocutRev2 As RevolveFeature
    Private othread As ThreadFeature
    Private oparameter As BoltParameter


    Public Sub New(ByVal oboltDefinition As BoltParameter)
        oparameter = oBoltDefinition
    End Sub

    Public Sub Create(ByVal otargetApp As Application, ByVal otargetDoc As PartDocument, ByVal otargetLocation As Point)
        Dim strError As String = ""

        Try
            If Not (otargetApp Is Nothing Or otargetDoc Is Nothing Or oTargetLocation Is Nothing) Then
                'set environments to create bolt
                oapp = otargetApp
                oTG = oapp.TransientGeometry
                opartCompDef = otargetDoc.ComponentDefinition
                olocation = oTargetLocation

                'set error message
                strError = "Exception happens in setting up user parameter. "

                'set parameters of bolt
                SetParameters()

                'set error message
                strError = "Exception happens in creating work axis and plane. "

                'create axis A1
                CreateWorkAxisA1()

                'create work plane PT1
                CreateWorkPlanePT1()

                'create work plane PF1
                CreateWorkPlanePF1()

                'set error message
                strError = "Please check the parameters of bolt head. "

                'create circle and hexagon on sketch 1
                CreateSketch1()

                'create head extrusion feature
                CreateHeadExtrusion()

                'set error message
                strError = "Please check the parameters of bolt body. "

                'create circle on sketch 2
                CreateSketch2()

                'create body extrusion feature
                CreateBodyExtrusion()

                'set error message
                strError = "Please check the parameter of chamfer. "

                'create chamfer feature
                CreateChamfer()

                'set error message
                strError = "Please check the parameter of fillet. "

                'create fillet feature
                CreateFillet()

                'set error message
                strError = "Please check the parameter of cut angle. "

                'create cutting profile on sketch 3
                CreateSketch3()

                'create revolution feature to cut upper edge of head with sketch 3
                CreateRevoluation1()

                'create cutting profile on sketch 4
                CreateSketch4()

                'create revolution feature to cut bottom edge of head with sketch 4
                CreateRevoluation2()

                'set error message
                strError = "Please check the parameter of thread. "

                'create thread
                CreateThread()
            End If
        Catch ex As Exception
            ex.Source = strError
            Throw ex
        End Try
    End Sub

    Private Sub SetParameters()
        Dim ouserParameters As UserParameters
        Dim fheadHeight, fheadDiameter, fbodyDiameter, fcutAngle As Double

        Try
            'set user-defined parameters for building the bold
            ouserParameters = opartCompDef.Parameters.UserParameters
            fheadDiameter = ouserParameters.AddByExpression(oparameter.strBoltID & "_" & HEAD_DIAMETER, oparameter.strHeadDiameter, UnitsTypeEnum.kInchLengthUnits).Value
            fHeadHeight = ouserParameters.AddByExpression(oparameter.strBoltID & "_" & HEAD_HEIGHT, oparameter.strHeadHeight, UnitsTypeEnum.kInchLengthUnits).Value
            ouserParameters.AddByExpression(oparameter.strBoltID & "_" & BODY_LENGTH, oparameter.strBodyLength, UnitsTypeEnum.kInchLengthUnits)
            fBodyDiameter = ouserParameters.AddByExpression(oparameter.strBoltID & "_" & BODY_DIAMETER, oparameter.strBodyDiameter, UnitsTypeEnum.kInchLengthUnits).Value
            ouserParameters.AddByExpression(oparameter.strBoltID & "_" & FILLET_RADIUS, oparameter.strFilletRadius, UnitsTypeEnum.kInchLengthUnits)
            ouserParameters.AddByExpression(oparameter.strBoltID & "_" & CHAMFER_DISTANCE, oparameter.strChamferDistance, UnitsTypeEnum.kInchLengthUnits)
            fCutAngle = ouserParameters.AddByExpression(oparameter.strBoltID & "_" & CUT_ANGLE, oparameter.strCutAngle, UnitsTypeEnum.kDegreeAngleUnits).Value
            ouserParameters.AddByExpression(oparameter.strBoltID & "_" & THREAD_LENGTH, oparameter.strThreadLength, UnitsTypeEnum.kInchLengthUnits)

            'check parameter constrains
            If fbodyDiameter > fheadDiameter Then Throw New Exception("Body diameter is bigger than head diameter. ")
            If fheadDiameter * (1 / Math.Cos(Math.PI / 6) - 1) * Math.Tan(fCutAngle) > fheadHeight Then Throw New Exception("Cut angle is not fit for head. ")
        Catch
            Throw
        End Try
    End Sub

    'create work axis A1 for revolution
    Private Sub CreateWorkAxisA1()
        Try
            'add work axis according to Z axis
            oaxis1 = opartCompDef.WorkAxes.AddFixed(olocation, oTG.CreateUnitVector(0, 0, 1))
            oaxis1.Name = oparameter.strBoltID & "_" & AXIS_A1
            oaxis1.Visible = False
        Catch
            Throw
        End Try
    End Sub

    'create work plane PT1 
    Private Sub CreateWorkPlanePT1()
        Try
            'add work plane according to XY plane
            oplanePT1 = opartCompDef.WorkPlanes.AddFixed(oLocation, oTG.CreateUnitVector(1, 0, 0), oTG.CreateUnitVector(0, 1, 0))
            oplanePT1.Name = oparameter.strBoltID & "_" & PLANE_PT1
            oplanePT1.Visible = False
        Catch
            Throw
        End Try
    End Sub

    'create work plane PF1 
    Private Sub CreateWorkPlanePF1()
        Try
            'add work axis according to XZ plane
            oplanePF1 = opartCompDef.WorkPlanes.AddFixed(oLocation, oTG.CreateUnitVector(1, 0, 0), oTG.CreateUnitVector(0, 0, 1))
            oplanePF1.Name = oparameter.strBoltID & "_" & PLANE_PF1
            oplanePF1.Visible = False
        Catch
            Throw
        End Try
    End Sub

    'create sketch 1 for head construction 
    Private Sub CreateSketch1()
        Dim oCenterPoint As SketchPoint
        Dim oCircle As SketchCircle
        Dim oDimConstrain As DiameterDimConstraint
        Dim oPointArray(5) As SketchPoint
        Dim oEdgeArray(5) As SketchLine
        Dim i As Integer

        Try
            'create a new sketch
            osketch1 = opartCompDef.Sketches.Add(oPlanePT1)
            osketch1.Name = oparameter.strBoltID & "_" & SKETCH_1

            'create a new sketch circle
            oCenterPoint = osketch1.AddByProjectingEntity(oaxis1)
            oCenterPoint.HoleCenter = False
            oCircle = osketch1.SketchCircles.AddByCenterRadius(oCenterPoint, 1)
            osketch1.GeometricConstraints.AddCoincident(oCenterPoint, oCircle.CenterSketchPoint)

            'create a dimension constrain of radius
            oDimConstrain = osketch1.DimensionConstraints.AddDiameter(oCircle, oTG.CreatePoint2d(1.5, 1.5))
            oDimConstrain.Parameter.Expression = oparameter.strBoltID & "_" & HEAD_DIAMETER

            'create a new hexagon
            'create vertices
            For i = 0 To 5
                oPointArray(i) = osketch1.SketchPoints.Add(oTG.CreatePoint2d(oDimConstrain.Parameter.Value * Math.Cos(Math.PI * i / 3) / 2, _
                                    oDimConstrain.Parameter.Value * Math.Sin(Math.PI * i / 3) / 2), False)
            Next

            'create edges
            For i = 0 To 5
                oEdgeArray(i) = osketch1.SketchLines.AddByTwoPoints(oPointArray((i + 1) Mod 6), oPointArray(i))
            Next

            'create length constrains
            For i = 0 To 4
                osketch1.GeometricConstraints.AddEqualLength(oEdgeArray(i + 1), oEdgeArray(i))
            Next

            'create tangent constrains
            For i = 0 To 4
                osketch1.GeometricConstraints.AddTangent(oEdgeArray(i), oCircle)
            Next

            'create parallel constrains
            osketch1.GeometricConstraints.AddParallel(oEdgeArray(5), oEdgeArray(2))

            'create horizontal align constrain
            osketch1.GeometricConstraints.AddHorizontalAlign(oPointArray(0), oPointArray(3))
        Catch
            Throw
        End Try
    End Sub

    'create sketch 2 for body construction 
    Private Sub CreateSketch2()
        Dim oCenterPoint As SketchPoint
        Dim oCircle As SketchCircle
        Dim oDimConstrain As DiameterDimConstraint

        Try
            'create a new sketch
            osketch2 = opartCompDef.Sketches.Add(oPlanePT1)
            osketch2.Name = oparameter.strBoltID & "_" & SKETCH_2

            'create a new sketch circle
            oCenterPoint = osketch2.AddByProjectingEntity(oaxis1)
            oCenterPoint.HoleCenter = False
            oCircle = osketch2.SketchCircles.AddByCenterRadius(oCenterPoint, 1)
            osketch2.GeometricConstraints.AddCoincident(oCenterPoint, oCircle.CenterSketchPoint)

            'create a dimension constrain of radius
            oDimConstrain = oSketch2.DimensionConstraints.AddDiameter(oCircle, oTG.CreatePoint2d(1.5, -1.5))
            oDimConstrain.Parameter.Expression = oparameter.strBoltID & "_" & BODY_DIAMETER
        Catch
            Throw
        End Try
    End Sub

    'create sketch 3 for cutting of upper head edge 
    Private Sub CreateSketch3()
        Dim oPoint1, oPoint2, oPoint3 As SketchPoint
        Dim oLine1, oLine2, oLine3 As SketchLine
        Dim oProjectedLine As SketchLine
        Dim oAngleConstrain As TwoLineAngleDimConstraint

        Try
            'create a new sketch
            osketch3 = opartCompDef.Sketches.Add(oplanePF1)
            osketch3.Name = oparameter.strBoltID & "_" & SKETCH_3

            'create projected line of the circle on sketch 1
            oProjectedLine = osketch3.AddByProjectingEntity(osketch1.SketchCircles(1))

            'create projected point of the first point of hexagon on sketch 1
            oPoint2 = osketch3.AddByProjectingEntity(osketch1.SketchPoints(3))

            'get right end point of projected line
            If oProjectedLine.StartSketchPoint.Geometry.X > oProjectedLine.EndSketchPoint.Geometry.X Then
                oPoint1 = oProjectedLine.StartSketchPoint
            Else
                oPoint1 = oProjectedLine.EndSketchPoint
            End If

            'create point 3 first, then give it proper constrains
            oPoint3 = osketch3.SketchPoints.Add(oTG.CreatePoint2d(oPoint2.Geometry.X, _
                        oPoint2.Geometry.Y + (oPoint2.Geometry.X - oPoint1.Geometry.X) * _
                            Math.Tan(opartCompDef.Parameters.UserParameters(oparameter.strBoltID & "_" & CUT_ANGLE).Value)), False)
            osketch3.GeometricConstraints.AddVerticalAlign(oPoint2, oPoint3)

            'create triangle profile
            oLine1 = osketch3.SketchLines.AddByTwoPoints(oPoint1, oPoint2)
            oLine2 = osketch3.SketchLines.AddByTwoPoints(oPoint2, oPoint3)
            oLine3 = osketch3.SketchLines.AddByTwoPoints(oPoint1, oPoint3)
            oAngleConstrain = osketch3.DimensionConstraints.AddTwoLineAngle(oLine3, oLine1, _
                                oTG.CreatePoint2d(oPoint1.Geometry.X + 1, oPoint1.Geometry.Y + _
                                    Math.Tan(opartCompDef.Parameters.UserParameters(oparameter.strBoltID & "_" & CUT_ANGLE).Value / 2)))
            oAngleConstrain.Parameter.Expression = oparameter.strBoltID & "_" & CUT_ANGLE
        Catch
            Throw
        End Try
    End Sub

    'create sketch 4 for cutting of bottom head edge
    Private Sub CreateSketch4()
        Dim oPoint1, oPoint2, oPoint3 As SketchPoint
        Dim oLine1, oLine2, oLine3 As SketchLine
        Dim oProjectedLine As SketchLine
        Dim oAngleConstrain As TwoLineAngleDimConstraint

        Try
            'create a new sketch
            osketch4 = opartCompDef.Sketches.Add(oplanePF1)
            osketch4.Name = oparameter.strBoltID & "_" & SKETCH_4

            'create projected line of the upper face of head
            oProjectedLine = osketch4.AddByProjectingEntity(oheadExt.EndFaces(1).Edges(3))

            'get right end point of projected line
            If oProjectedLine.StartSketchPoint.Geometry.X > oProjectedLine.EndSketchPoint.Geometry.X Then
                oPoint2 = oProjectedLine.StartSketchPoint
            Else
                oPoint2 = oProjectedLine.EndSketchPoint
            End If

            'create point 1 and 3
            oPoint1 = osketch4.SketchPoints.Add(oTG.CreatePoint2d(oPoint2.Geometry.X - osketch3.SketchLines(2).Length, oPoint2.Geometry.Y), False)
            oPoint3 = osketch4.SketchPoints.Add(oTG.CreatePoint2d(oPoint2.Geometry.X, oPoint2.Geometry.Y - osketch3.SketchLines(3).Length), False)

            'create triangle profile
            oLine1 = osketch4.SketchLines.AddByTwoPoints(oPoint1, oPoint2)
            oLine2 = osketch4.SketchLines.AddByTwoPoints(oPoint3, oPoint2)
            oLine3 = osketch4.SketchLines.AddByTwoPoints(oPoint1, oPoint3)
            osketch4.GeometricConstraints.AddCoincident(oProjectedLine, oPoint1)
            osketch4.GeometricConstraints.AddVertical(oLine2)
            osketch4.GeometricConstraints.AddEqualLength(oLine2, osketch3.SketchLines(3))
            oAngleConstrain = osketch4.DimensionConstraints.AddTwoLineAngle(oLine3, oLine1, _
                                oTG.CreatePoint2d(oPoint1.Geometry.X + 1, oPoint1.Geometry.Y - _
                                    Math.Tan(opartCompDef.Parameters.UserParameters(oparameter.strBoltID & "_" & CUT_ANGLE).Value / 2)))
            oAngleConstrain.Parameter.Expression = oparameter.strBoltID & "_" & CUT_ANGLE
        Catch
            Throw
        End Try
    End Sub

    'create head extrusion with sketch 1
    Private Sub CreateHeadExtrusion()
        Dim oProfile As Profile

        Try
            'create the profile needed for extrusion
            oProfile = osketch1.Profiles.AddForSolid(False)

            'create the extrusion feature
            oheadExt = opartCompDef.Features.ExtrudeFeatures.AddByDistanceExtent(oProfile, oparameter.strBoltID & "_" & HEAD_HEIGHT, _
                        PartFeatureExtentDirectionEnum.kPositiveExtentDirection, PartFeatureOperationEnum.kJoinOperation)
            oHeadExt.Name = oparameter.strBoltID & "_" & HEAD_EXTRUSION
        Catch
            Throw
        End Try
    End Sub

    'create body extrusion with sketch 2
    Private Sub CreateBodyExtrusion()
        Dim oProfile As Profile

        Try
            'create the profile needed for extrusion
            oProfile = osketch2.Profiles.AddForSolid(False)

            'create the extrusion feature
            obodyExt = opartCompDef.Features.ExtrudeFeatures.AddByDistanceExtent(oProfile, oparameter.strBoltID & "_" & BODY_LENGTH, _
                        PartFeatureExtentDirectionEnum.kNegativeExtentDirection, PartFeatureOperationEnum.kJoinOperation)
            oBodyExt.Name = oparameter.strBoltID & "_" & BODY_EXTRUSION
        Catch
            Throw
        End Try
    End Sub

    'create chamfer on bottom of body
    Private Sub CreateChamfer()
        Dim oEdge As Edge = Nothing
        Dim oEdgeCol As EdgeCollection

        Try
            'get bottom edge from body
            For Each oEdge In oBodyExt.EndFaces(1).Edges
                If oEdge.CurveType = CurveTypeEnum.kCircleCurve Then
                    Exit For
                End If
            Next
            oEdgeCol = oapp.TransientObjects.CreateEdgeCollection()
            oEdgeCol.Add(oEdge)

            'do chamfer
            oChamfer = opartCompDef.Features.ChamferFeatures.AddUsingDistance(oEdgeCol, oparameter.strBoltID & "_" & CHAMFER_DISTANCE)
            oChamfer.Name = oparameter.strBoltID & "_" & CHAMFER_1
        Catch
            Throw
        End Try
    End Sub

    'create fillet connecting body and head
    Private Sub CreateFillet()
        Dim oEdgeLoop As EdgeLoop = Nothing
        Dim oEdgeCol As EdgeCollection

        Try
            'get upper edge from body
            For Each oEdgeLoop In oHeadExt.StartFaces(1).EdgeLoops
                'since there two edgeloops in the start face of head, one consists of one circle edge while the other six edges
                If oEdgeLoop.Edges.Count = 1 Then
                    Exit For
                End If
            Next
            oEdgeCol = oapp.TransientObjects.CreateEdgeCollection()
            oEdgeCol.Add(oEdgeLoop.Edges(1))

            'do chamfer
            oFillet = opartCompDef.Features.FilletFeatures.AddSimple(oEdgeCol, oparameter.strBoltID & "_" & FILLET_RADIUS)
            oFillet.Name = oparameter.strBoltID & "_" & FILLET_1
        Catch
            Throw
        End Try
    End Sub

    'create revolve feature
    Private Sub CreateRevoluation1()
        Dim oProfile As Profile
        Dim oProjectedAxis As SketchLine

        Try
            'get the axis to revolve which must be on the same sketch with the profile
            oProjectedAxis = oSketch3.AddByProjectingEntity(oaxis1)

            'create the profile needed for extrusion
            oProfile = oSketch3.Profiles.AddForSolid(False)

            'create the revolution feature
            oCutRev1 = opartCompDef.Features.RevolveFeatures.AddFull(oProfile, oProjectedAxis, PartFeatureOperationEnum.kCutOperation)
            ocutRev1.Name = oParameter.strBoltID & "_" & REVOLVE_1
        Catch
            Throw
        End Try
    End Sub

    'create revolve feature
    Private Sub CreateRevoluation2()
        Dim oProfile As Profile
        Dim oProjectedAxis As SketchLine

        Try
            'get the axis to revolve which must be on the same sketch with the profile
            oProjectedAxis = osketch4.AddByProjectingEntity(oaxis1)

            'create the profile needed for extrusion
            oProfile = osketch4.Profiles.AddForSolid(False)

            'create the revolution feature
            ocutRev2 = opartCompDef.Features.RevolveFeatures.AddFull(oProfile, oProjectedAxis, PartFeatureOperationEnum.kCutOperation)
            ocutRev2.Name = oParameter.strBoltID & "_" & REVOLVE_2
        Catch
            Throw
        End Try
    End Sub

    'create thread feature
    Private Sub CreateThread()
        Dim oThreadInfo As ThreadInfo
        Dim oThreadFeatures As ThreadFeatures
        Dim oEdge As Edge = Nothing

        Try
            'create thread information
            oThreadFeatures = oPartCompDef.Features.ThreadFeatures
            oThreadInfo = oThreadFeatures.CreateStandardThreadInfo(False, True, THREAD_TYPE, THREAD_DESIGNATION, THREAD_CLASS)

            'get bottom edge of body
            For Each oEdge In obodyExt.SideFaces(1).Edges
                If oEdge.CurveType = CurveTypeEnum.kCircleCurve Then
                    Exit For
                End If
            Next

            'Create(thread)
            othread = oThreadFeatures.Add(obodyExt.SideFaces(1), oEdge, oThreadInfo, False, False, oparameter.strBoltID & "_" & THREAD_LENGTH)
            othread.Name = oparameter.strBoltID & "_" & THREAD_1
        Catch
            Throw
        End Try
    End Sub
End Class
