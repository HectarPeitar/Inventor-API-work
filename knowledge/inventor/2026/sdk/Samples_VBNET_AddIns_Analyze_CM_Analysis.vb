Option Strict Off
Option Explicit On

Friend Class Analysis

#Region "Data Member"

    Private WithEvents m_AnalyzeControl As AnalyzeControl.BrowserControl

    ' Select related events.
    Private WithEvents m_InteractionEvents As Inventor.InteractionEvents
    Private WithEvents m_SelectEvents As Inventor.SelectEvents
    Private WithEvents m_DocEvents As Inventor.DocumentEvents

    Private m_InventorApp As Inventor.Application
    Private m_AsmDoc As Inventor.AssemblyDocument
    Private m_Analyses As Analyses

    Private m_Pane As Inventor.BrowserPane

    Private m_ParamSettings As ParamSettings

    ' Graphics related declares.
    Private m_GraphicsDataSets As Inventor.GraphicsDataSets
    Private m_ClientGraphics As Inventor.ClientGraphics
    Private m_TempPointCoordSet As Inventor.GraphicsCoordinateSet
    Private m_TempPointNode As Inventor.GraphicsNode
    Private m_TrackPointCoordSet As Inventor.GraphicsCoordinateSet
    Private m_TrackPointNode As Inventor.GraphicsNode
    Private m_ResultCurvesCoordSets() As Inventor.GraphicsCoordinateSet
    Private m_ResultCurvesNode As Inventor.GraphicsNode
    Private m_ResultColorSet As Inventor.GraphicsColorSet
    Private Const TempPointDataID As Short = 1
    Private Const TempPointNodeID As Short = 1
    Private Const DefinedPointDataID As Short = 2
    Private Const DefinedPointNodeID As Short = 2
    Private Const ColorSetID As Short = 3
    Private Const ResultCurvesNodeID As Short = 4
    Private m_SelectedObjects As Inventor.ObjectCollection
    Private m_SelectionTransaction As Inventor.Transaction

    Private miPointCount As Integer
#End Region

    Public ReadOnly Property IsAnalysisReady() As Boolean
        Get
            ' Initialize return value.
            IsAnalysisReady = False

            ' Check to see that some parameters are defined.
            Dim Results As Inventor.ObjectCollection
            If ParamSettings.Count > 0 Then
                ' Determine if there are any track points.
                On Error Resume Next
                Results = m_AsmDoc.AttributeManager.FindObjects("AnalyzeSample", "TrackPoint")
                If Err.Number Then
                    Exit Property
                End If
                If Results.Count > 0 Then
                    IsAnalysisReady = True
                End If
            End If
        End Get
    End Property


    Public Property IsAnalysisEnabled() As Boolean
        Get
            IsAnalysisEnabled = m_AnalyzeControl.RunAnalysisEnabled
        End Get
        Set(ByVal Value As Boolean)
            m_AnalyzeControl.RunAnalysisEnabled = Value
        End Set
    End Property


    Public ReadOnly Property ParamSettings() As ParamSettings
        Get
            If m_ParamSettings Is Nothing Then
                m_ParamSettings = New ParamSettings
            End If

            ParamSettings = m_ParamSettings
        End Get
    End Property

    Public Sub ShowBrowser()
        m_Pane.Activate()
    End Sub

    Public Sub ParamsChanged()
        Dim Results As Inventor.ObjectCollection
        If ParamSettings.Count > 0 Then
            ' Determine if there are any track points.
            On Error Resume Next
            Results = m_AsmDoc.AttributeManager.FindObjects("AnalyzeSample", "TrackPoint")
            If Err.Number Then
                Exit Sub
            End If
            If Results.Count > 0 Then
                m_AnalyzeControl.RunAnalysisEnabled = True
            End If
        End If
    End Sub


    Public Sub Initialize(ByVal InventorApp As Inventor.Application, ByVal AsmDoc As Inventor.AssemblyDocument, ByVal Analyses As Analyses)
        Try

            m_InventorApp = InventorApp

            m_AsmDoc = AsmDoc

            m_Analyses = Analyses

            m_DocEvents = m_AsmDoc.DocumentEvents

            m_Pane = m_AsmDoc.BrowserPanes.Add("Analyze", "AnalyzeControl.BrowserControl")
            m_AnalyzeControl = m_Pane.Control

            ' Start a transaction so all of the client graphics calls are wrapped within a single undo.
            Dim Transaction As Inventor.Transaction
            Transaction = m_InventorApp.TransactionManager.StartTransaction(m_AsmDoc, "Initialize Analysis")

            ' Create the graphics data set.
            m_GraphicsDataSets = m_AsmDoc.GraphicsDataSetsCollection.Add("invtAnalyzeGraphics")

            ' Create coordinate set to use for temporary display of points.
            m_TempPointCoordSet = m_GraphicsDataSets.CreateCoordinateSet(TempPointDataID)

            ' Create the client graphics object.
            m_ClientGraphics = m_AsmDoc.ComponentDefinition.ClientGraphicsCollection.Add("invtAnalyzeGraphics")

            ' Create node to use for temporary display of points.
            m_TempPointNode = m_ClientGraphics.AddNode(TempPointNodeID)
            m_TempPointNode.Visible = False

            ' Set-up point default point data.  When it's used later it only needs to have
            ' the correct coordinate assigned and the visibility turned on.
            Call m_TempPointCoordSet.Add(1, m_InventorApp.TransientGeometry.CreatePoint)
            Dim PointGraphics As Inventor.PointGraphics
            PointGraphics = m_TempPointNode.AddPointGraphics
            PointGraphics.CoordinateSet = m_TempPointCoordSet
            PointGraphics.PointRenderStyle = Inventor.PointRenderStyleEnum.kCirclePointStyle
            PointGraphics.DepthPriority = 20

            ' Create coordinate set to use for displaying selected points.
            m_TrackPointCoordSet = m_GraphicsDataSets.CreateCoordinateSet(DefinedPointDataID)

            ' Create node to use for displaying selected points.
            m_TrackPointNode = m_ClientGraphics.AddNode(DefinedPointNodeID)
            m_TrackPointNode.Visible = False
            Dim SelectedPoints As Inventor.PointGraphics
            SelectedPoints = m_TrackPointNode.AddPointGraphics
            SelectedPoints.CoordinateSet = m_TrackPointCoordSet
            SelectedPoints.PointRenderStyle = Inventor.PointRenderStyleEnum.kFilledCircleSelectPointStyle

            ' Define the
            m_ResultColorSet = m_GraphicsDataSets.CreateColorSet(ColorSetID)
            Call m_ResultColorSet.Add(1, 0, 255, 255)

            ' Finish the transaction.
            Transaction.End()

            ' Find all parameters currently defined.
            Dim SearchResult As Inventor.ObjectCollection
            SearchResult = m_AsmDoc.AttributeManager.FindObjects("AnalyzeSample", "StartValue")
            Dim Param As Inventor.Parameter
            Dim AttribSet As Inventor.AttributeSet
            Dim StartValue As String
            Dim EndValue As String
            For Each Param In SearchResult
                AttribSet = Param.AttributeSets.Item("AnalyzeSample")

                StartValue = AttribSet.Item("StartValue").Value
                EndValue = AttribSet.Item("EndValue").Value
                Call Me.ParamSettings.Add(Param, (AttribSet.Item("StartValue").Value), (AttribSet.Item("EndValue").Value))
            Next Param

            ' Add items to the browser for any existing points.
            Dim AttribSets As Inventor.AttributeSetsEnumerator
            AttribSets = m_AsmDoc.AttributeManager.FindAttributeSets("AnalyzeSample", "TrackPoint")
            Dim i As Integer
            Dim PointName As String
            Dim Value As Integer
            If AttribSets.Count > 0 Then
                For i = 1 To AttribSets.Count
                    PointName = AttribSets.Item(i).Item("TrackPoint").Value

                    m_AnalyzeControl.AddNewTrackPoint(PointName)

                    ' Strip off the value portion of the name.
                    Value = Val(Right(PointName, Len(PointName) - InStr(PointName, " ")))

                    If miPointCount < Value Then
                        miPointCount = Value
                    End If
                Next
            End If

            ' Check to see if analysis can be enabled.
            If Me.IsAnalysisReady Then
                Me.IsAnalysisEnabled = True
            Else
                Me.IsAnalysisEnabled = False
            End If
        Catch ex As Exception

        End Try
    End Sub

    Private Sub Class_Terminated()
        m_ParamSettings = Nothing
        m_AnalyzeControl = Nothing

        On Error Resume Next
        m_Pane.Delete()
        m_ClientGraphics.Delete()
        m_GraphicsDataSets.Delete()
        On Error GoTo 0

        m_Pane = Nothing
        m_AsmDoc = Nothing
        m_GraphicsDataSets = Nothing
        m_ClientGraphics = Nothing
        m_TempPointCoordSet = Nothing
        m_TempPointNode = Nothing
        m_TrackPointCoordSet = Nothing
        m_TrackPointNode = Nothing
        m_ResultCurvesNode = Nothing
        m_ResultColorSet = Nothing
        m_SelectedObjects = Nothing
    End Sub

    Protected Overrides Sub Finalize()
        Class_Terminated()
        MyBase.Finalize()
    End Sub

    Private Sub m_AnalyzeControl_RunAnalysis() Handles m_AnalyzeControl.RunAnalysis
        Try

            ' Start a transaction so all of this will be within a single undo.
            Dim Transaction As Inventor.Transaction
            Transaction = m_InventorApp.TransactionManager.StartTransaction(m_AsmDoc, "Analysis Run")

            ' Rem_ve any existing result graphics if there are any.
            Dim i As Integer
            If Not m_ResultCurvesNode Is Nothing Then
                m_ResultCurvesNode.Delete()
                For i = 1 To UBound(m_ResultCurvesCoordSets)
                    m_ResultCurvesCoordSets(i).Delete()
                Next
            End If

            ' Find all existing track points based on attributes assigned to the m_del.
            Dim TrackPoints As Inventor.ObjectCollection
            TrackPoints = m_AsmDoc.AttributeManager.FindObjects("AnalyzeSample", "TrackPoint")

            ' Create a new graphics node to use for displaying the results.
            m_ResultCurvesNode = m_AsmDoc.ComponentDefinition.ClientGraphicsCollection.Item("invtAnalyzeGraphics").AddNode(ResultCurvesNodeID)

            ' Create a coordinate set and line strip for each track point and set them up.
            ReDim m_ResultCurvesCoordSets(TrackPoints.Count)
            Dim LineStrip As Inventor.LineStripGraphics
            For i = 1 To TrackPoints.Count
                m_ResultCurvesCoordSets(i) = m_AsmDoc.GraphicsDataSetsCollection.Item("invtAnalyzeGraphics").CreateCoordinateSet(100 + i)
                LineStrip = m_ResultCurvesNode.AddLineStripGraphics
                LineStrip.ColorBinding = Inventor.ColorBindingEnum.kOverallColor
                LineStrip.ColorSet = m_ResultColorSet
                LineStrip.CoordinateSet = m_ResultCurvesCoordSets(i)
            Next

            ' Obtain the number of steps to use.
            Dim Steps As Integer
            Steps = m_AsmDoc.ComponentDefinition.AttributeSets.Item("AnalyzeSample").Item("StepCount").Value

            ' Perform the actual analysis by stepping the assembly.
            Dim j As Integer
            Dim Increment As Double
            Dim StartValue As Double
            Dim EndValue As Double
            Dim NewValue As Double
            For i = 1 To Steps
                ' Change the value of each of the specified parameters.
                For j = 1 To ParamSettings.Count
                    ' Get the start and end values associated with the parameter.
                    StartValue = m_AsmDoc.UnitsOfMeasure.GetValueFromExpression(ParamSettings.Item(j).StartValue, ParamSettings.Item(j).Parameter.Units)
                    EndValue = m_AsmDoc.UnitsOfMeasure.GetValueFromExpression(ParamSettings.Item(j).EndValue, ParamSettings.Item(j).Parameter.Units)

                    ' Calculate the increment between each step.
                    Increment = (EndValue - StartValue) / (Steps - 1)

                    ' Determine the new value.
                    NewValue = StartValue + (Increment * (i - 1))

                    ' Set the value.
                    ParamSettings.Item(j).Parameter.Value = NewValue
                Next

                ' Update the assembly.
                m_AsmDoc.Update()

                ' For each track point add its current position to the associated coordinate set.
                For j = 1 To TrackPoints.Count
                    Call m_ResultCurvesCoordSets(j).Add(m_ResultCurvesCoordSets(j).Count + 1, GetPointFromGeometry(TrackPoints.Item(j)))
                Next

                ' Update the view.
                m_InventorApp.ActiveView.Update()
            Next

            ' Enable the display control on the dialog and set it to true.
            m_AnalyzeControl.ShowDisplayResults = True
            m_AnalyzeControl.DisplayCurvesValue = True

            ' Finish the transaction.
            Transaction.End()
        Catch ex As Exception

        End Try
    End Sub


    Private Sub m_AnalyzeControl_AddTrackPoint() Handles m_AnalyzeControl.AddTrackPoint
        Try

            ' Start a transaction.
            m_SelectionTransaction = m_InventorApp.TransactionManager.StartTransaction(m_AsmDoc, "Add Track Points")

            ' Get points that have already been selected and display them
            m_SelectedObjects = m_AsmDoc.AttributeManager.FindObjects("AnalyzeSample", "TrackPoint")
            Dim i As Integer
            Dim Coords() As Double
            Dim Point As Inventor.Point
            If m_SelectedObjects.Count > 0 Then
                ReDim Coords(m_SelectedObjects.Count * 3)
                For i = 1 To m_SelectedObjects.Count
                    Point = GetPointFromGeometry(m_SelectedObjects.Item(i))
                    Coords((i - 1) * 3 + 1) = Point.X
                    Coords((i - 1) * 3 + 2) = Point.Y
                    Coords((i - 1) * 3 + 3) = Point.Z
                Next
                Call m_TrackPointCoordSet.PutCoordinates(Coords)
                m_TrackPointNode.Visible = True
                m_InventorApp.ActiveView.Update()
            End If

            m_InteractionEvents = m_AsmDoc.Parent.CommandManager.CreateInteractionEvents
            m_SelectEvents = m_InteractionEvents.SelectEvents
            m_SelectEvents.ClearSelectionFilter()
            m_SelectEvents.AddSelectionFilter(Inventor.SelectionFilterEnum.kAllCircularEntities)
            m_SelectEvents.AddSelectionFilter(Inventor.SelectionFilterEnum.kAllPointEntities)
            m_SelectEvents.AddSelectionFilter(Inventor.SelectionFilterEnum.kPartFaceSphericalFilter)
            m_SelectEvents.AddSelectionFilter(Inventor.SelectionFilterEnum.kPartVertexFilter)
            m_SelectEvents.AddSelectionFilter(Inventor.SelectionFilterEnum.kWorkPointFilter)

            m_AnalyzeControl.ListEnabled = False
            m_AnalyzeControl.RunAnalysisEnabled = False
            m_InteractionEvents.Start()
        Catch ex As Exception

        End Try
    End Sub


    Private Sub m_AnalyzeControl_ShowHideResultCurves(ByRef eventArgs As Boolean) Handles m_AnalyzeControl.ShowHideResultCurves
        If eventArgs Then
            m_ResultCurvesNode.Visible = True
        Else
            m_ResultCurvesNode.Visible = False
        End If

        m_InventorApp.ActiveView.Update()
    End Sub

    Private Sub m_AnalyzeControl_TrackPointDeleted(ByRef eventArgs As String) Handles m_AnalyzeControl.TrackPointDeleted
        ' Find the entity using the attribute attached.
        Dim Results As Inventor.AttributeSetsEnumerator
        On Error Resume Next
        Results = m_AsmDoc.AttributeManager.FindAttributeSets("AnalyzeSample", "TrackPoint", eventArgs)
        If Err.Number Then
            Exit Sub
        End If
        On Error GoTo 0

        If Results.Count > 0 Then
            Results.Item(1).Delete()
            m_TempPointNode.Visible = False
            m_InventorApp.ActiveView.Update()
        End If

        ' Check to see if analysis can be enabled.
        If Me.IsAnalysisReady Then
            Me.IsAnalysisEnabled = True
        Else
            Me.IsAnalysisEnabled = False
        End If
    End Sub

    Private Sub m_DocEvents_OnClose(ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles m_DocEvents.OnClose
        If BeforeOrAfter = Inventor.EventTimingEnum.kBefore Then
            Call m_Analyses.Remove((m_AsmDoc.FullFileName))
        End If
    End Sub

    Private Sub m_InteractionEvents_OnTerminate() Handles m_InteractionEvents.OnTerminate
        Try

            ' Enabled the track point list.
            m_AnalyzeControl.ListEnabled = True

            ' Turn off the node that contains the track point display.
            m_TrackPointNode.Visible = False

            ' End the transaction that was started earlier.
            m_SelectionTransaction.End()

            ' Update the view.
            m_InventorApp.ActiveView.Update()

            m_SelectEvents = Nothing
            m_InteractionEvents = Nothing

            ' Check to see if analysis can be enabled.
            If Me.IsAnalysisReady Then
                Me.IsAnalysisEnabled = True
            Else
                Me.IsAnalysisEnabled = False
            End If
        Catch ex As Exception

        End Try
    End Sub

    Private Sub m_SelectEvents_OnPreSelect(ByRef PreSelectEntity As Object, ByRef DoHighlight As Boolean, ByRef m_rePreSelectEntities As Inventor.ObjectCollection, ByVal SelectionDevice As Inventor.SelectionDeviceEnum, ByVal m_delPosition As Inventor.Point, ByVal ViewPosition As Inventor.Point2d, ByVal View As Inventor.View) Handles m_SelectEvents.OnPreSelect
        Try

            ' Check to see if entity has already been selected.
            Dim i As Integer
            For i = 1 To m_SelectedObjects.Count
                If GetPointFromGeometry(m_SelectedObjects.Item(i)).DistanceTo(GetPointFromGeometry(PreSelectEntity)) < 0.0001 Then
                    DoHighlight = False
                    Exit Sub
                End If
            Next

            ' Display a client graphics point at the current preselected points position.
            Dim Point As Inventor.Point
            Point = GetPointFromGeometry(PreSelectEntity)
            If Not Point Is Nothing Then
                m_TempPointCoordSet.Coordinate(1) = Point
                m_TempPointNode.Visible = True
                m_InventorApp.ActiveView.Update()
            Else
                DoHighlight = False
            End If
        Catch ex As Exception

        End Try
    End Sub

    Private Sub m_SelectEvents_OnSelect(ByVal JustSelectedEntities As Inventor.ObjectsEnumerator, ByVal SelectionDevice As Inventor.SelectionDeviceEnum, ByVal m_delPosition As Inventor.Point, ByVal ViewPosition As Inventor.Point2d, ByVal View As Inventor.View) Handles m_SelectEvents.OnSelect
        Try

            ' Add an attribute to the object for persistance.
            Dim AttribSet As Inventor.AttributeSet
            AttribSet = JustSelectedEntities.Item(1).AttributeSets.Add("AnalyzeSample")
            miPointCount = miPointCount + 1
            Call AttribSet.Add("TrackPoint", Inventor.ValueTypeEnum.kStringType, "Point " & miPointCount)

            ' Add an item to the control in the browser.
            m_AnalyzeControl.AddNewTrackPoint("Point " & miPointCount)

            ' Turn off the display of the point.
            m_TempPointNode.Visible = False

            ' Add to the collection of selected points.
            m_SelectedObjects.Add(JustSelectedEntities.Item(1))
            Call m_TrackPointCoordSet.Add(m_TrackPointCoordSet.Count + 1, GetPointFromGeometry(JustSelectedEntities.Item(1)))
            m_TrackPointNode.Visible = True
            m_InventorApp.ActiveView.Update()

            m_SelectEvents.ResetSelections()

        Catch ex As Exception

        End Try
    End Sub

    Private Sub m_SelectEvents_OnStopPreSelect(ByVal m_delPosition As Inventor.Point, ByVal ViewPosition As Inventor.Point2d, ByVal View As Inventor.View) Handles m_SelectEvents.OnStopPreSelect
        m_TempPointNode.Visible = False
        m_InventorApp.ActiveView.Update()
    End Sub

    Private Sub m_AnalyzeControl_TrackPointSelected(ByRef eventArgs As String) Handles m_AnalyzeControl.TrackPointSelected
        ' Find the entity using the attribute attached.
        Dim Results As Inventor.ObjectCollection
        On Error Resume Next
        Results = m_AsmDoc.AttributeManager.FindObjects("AnalyzeSample", "TrackPoint", eventArgs)
        If Err.Number Then
            Exit Sub
        End If
        On Error GoTo 0
        If Results.Count > 0 Then
            m_TempPointCoordSet.Coordinate(1) = GetPointFromGeometry(Results.Item(1))
            m_TempPointNode.Visible = True
            m_InventorApp.ActiveView.Update()
        End If
    End Sub

    ' Get the coordinate location given an entity.
    Private Function GetPointFromGeometry(ByRef InGeometry As Object) As Inventor.Point
        Dim Face As Inventor.Face
        Dim Sphere As Inventor.Sphere
        Dim Edge As Inventor.Edge
        Dim Circle As Inventor.Circle
        Dim Ellipse As Inventor.EllipseFull
        Dim Vertex As Inventor.Vertex
        Dim AdCoords(3) As Double

        Select Case InGeometry.Type
            Case Inventor.ObjectTypeEnum.kFaceProxyObject
                Face = InGeometry
                If Face.SurfaceType = Inventor.SurfaceTypeEnum.kSphereSurface Then
                    Sphere = Face.Surface(Inventor.SurfaceTypeEnum.kSphereSurface)
                    GetPointFromGeometry = Sphere.CenterPoint
                Else
                    GetPointFromGeometry = Nothing
                End If
            Case Inventor.ObjectTypeEnum.kEdgeProxyObject
                Edge = InGeometry
                Select Case Edge.CurveType
                    Case Inventor.CurveTypeEnum.kCircleCurve, Inventor.CurveTypeEnum.kCircularArcCurve
                        Circle = Edge.Curve(Inventor.CurveTypeEnum.kCircleCurve)
                        GetPointFromGeometry = Circle.Center
                    Case Inventor.CurveTypeEnum.kEllipseFullCurve, Inventor.CurveTypeEnum.kEllipticalArcCurve
                        Ellipse = Edge.Curve(Inventor.CurveTypeEnum.kEllipseFullCurve)
                        GetPointFromGeometry = Ellipse.Center
                    Case Else
                        GetPointFromGeometry = Nothing
                End Select
            Case Inventor.ObjectTypeEnum.kVertexProxyObject
                Vertex = InGeometry
                Call Vertex.GetPoint(AdCoords)
                GetPointFromGeometry = m_InventorApp.TransientGeometry.CreatePoint(AdCoords(1), AdCoords(2), AdCoords(3))
            Case Else
                GetPointFromGeometry = Nothing
        End Select
    End Function

End Class