Imports Inventor

Friend Class RackFaceCmd
    Inherits CustomCommand.Command

    'Rack face command dialog
    Private m_rackFaceCmdDlg As RackFaceCmdDlg

    'Rack face command parameters
    Private m_rackFace As Face
    Private m_rackEdge As Edge

    Private m_numTeeth As Integer
    Private m_rackHeight As Double
    Private m_rackWidth As Double
    Private m_rackExtents As Double
    Private m_rackFeatureExtentDirection As PartFeatureExtentDirectionEnum

    'Rack face previe object
    Private m_previewClientGraphicsNode As GraphicsNode
    Private m_triangleStripGraphics As TriangleStripGraphics
    Private m_graphicsCoordinateSet As GraphicsCoordinateSet
    Private m_graphicsColorSet As GraphicsColorSet
    Private m_graphicsColorIndexSet As GraphicsIndexSet

    Public Sub New()
        MyBase.New()

        m_rackFaceCmdDlg = Nothing

        m_rackFace = Nothing
        m_rackEdge = Nothing

        m_previewClientGraphicsNode = Nothing
        m_triangleStripGraphics = Nothing
        m_graphicsCoordinateSet = Nothing
        m_graphicsColorSet = Nothing
        m_graphicsColorIndexSet = Nothing

    End Sub

    Protected Overrides Sub ButtonDefinition_OnExecute(ByVal context As NameValueMap)
        'Make sure that the current environment is "Part Environment"
        Dim currEnvironment As Inventor.Environment
        currEnvironment = m_application.UserInterfaceManager.ActiveEnvironment

        If LCase$(currEnvironment.InternalName) <> LCase$("PMxPartEnvironment") Then
            System.Windows.Forms.MessageBox.Show("This command applies only to Part Environment")
            Exit Sub
        End If

        'If commmand was already started,stop is first
        If m_commandIsRunning Then
            StopCommand()
        End If

        'Start new command
        StartCommand()
    End Sub

    Public Overrides Sub StartCommand()
        'Call base command button's StartCommand( to also start interaction)
        MyBase.StartCommand()

        'Implement this command specific functionality
        'subscribe to desired interaction event(s)
        MyBase.SubscribeToEvent(Interaction.InteractionTypeEnum.kSelection)

        'Initialize interaction graphics objects
        InitializePreviewGraphics()

        'Create  and display the dialog
        m_rackFaceCmdDlg = New RackFaceCmdDlg(m_application, Me)

        If Not (m_rackFaceCmdDlg Is Nothing) Then
            m_rackFaceCmdDlg.Activate()
            m_rackFaceCmdDlg.TopMost = True
            m_rackFaceCmdDlg.ShowInTaskbar = True
            m_rackFaceCmdDlg.Show()
        End If

        'Initialize this command's data members
        m_rackFace = Nothing
        m_rackEdge = Nothing

        'Enable interaction
        EnableInteraction()

    End Sub

    Public Overrides Sub ExecuteCommand()
        'Stop the command(to disconnect interaction events,interaction graphics and dismiss command dialog)
        StopCommand()

        'Create the rack face request
        Dim rackFaceRequestion As RackFaceRequest
        rackFaceRequestion = New RackFaceRequest(m_application, m_rackFace, m_rackEdge, m_numTeeth, m_rackHeight, m_rackWidth, m_rackExtents, m_rackFeatureExtentDirection)

        'Execute the request
        MyBase.ExecuteChangeRequest(rackFaceRequestion, "Autodesk:CustomCommand:RackFaceChgDef", m_application.ActiveDocument)
    End Sub

    Public Overrides Sub StopCommand()
        'Implement this command specific functionality
        TerminatePreviewGraphics()

        'Destroy the command dialog
        m_rackFaceCmdDlg.Hide()
        m_rackFaceCmdDlg.Dispose()
        m_rackFaceCmdDlg = Nothing

        'Call base command button's StopCommand (to disconnect interaction sink)
        MyBase.StopCommand()
    End Sub

    Public Overrides Sub EnableInteraction()
        'Call base command button's EnableInteraction
        MyBase.EnableInteraction()

        'Implement this command specific functionality
        'Clear selection filter
        m_selectEvents.ClearSelectionFilter()

        'Reset selections
        m_selectEvents.ResetSelections()

        'Specify selection filter and cursor
        If m_rackFaceCmdDlg.checkBoxFace.Checked Then
            If Not (m_rackEdge Is Nothing) Then
                m_selectEvents.AddToSelectedEntities(m_rackEdge)
            End If

            'Set the selection filter to a planar face
            m_selectEvents.AddSelectionFilter(SelectionFilterEnum.kPartFacePlanarFilter)

            'Set a cursor to specify face selection
            m_interactionEvents.SetCursor(CursorTypeEnum.kCursorBuiltInCrosshair)

            'Set the status bar message
            m_interactionEvents.StatusBarText = "Select a planar face with at least one linear edge"
        Else
            If Not (m_rackFace Is Nothing) Then
                m_selectEvents.AddToSelectedEntities(m_rackFace)
            End If

            'Set the selection filter to a linear edge
            m_selectEvents.AddSelectionFilter(SelectionFilterEnum.kPartEdgeLinearFilter)

            'Set a cursor to specify edge selection
            m_interactionEvents.SetCursor(CursorTypeEnum.kCursorBuiltInArrowCursor)

            'Set the status bar message
            m_interactionEvents.StatusBarText = "Select a linear edge on the selected face"
        End If

    End Sub

    Public Overrides Sub DisableInteraction()
        'Call base command button's DisableInteraction
        MyBase.DisableInteraction()

        'Implement this command speific functionality
        'Set the default cursor to notify that selection is not active
        m_interactionEvents.SetCursor(CursorTypeEnum.kCursorBuiltInArrow)

        'Clean up status text
        m_interactionEvents.StatusBarText = String.Empty
    End Sub


    '------------------------------------------------------------
    '-----Implementation of CRackFaceCmd Preview Graphics
    '-----------------------------------------------------------

    Private Sub InitializePreviewGraphics()
        Dim interactionGraphics As InteractionGraphics
        interactionGraphics = m_interactionEvents.InteractionGraphics

        Dim previewClientGraphics As ClientGraphics
        previewClientGraphics = interactionGraphics.PreviewClientGraphics

        m_previewClientGraphicsNode = previewClientGraphics.AddNode(1)

        m_triangleStripGraphics = m_previewClientGraphicsNode.AddTriangleStripGraphics()

        Dim graphicsDataSets As GraphicsDataSets
        graphicsDataSets = interactionGraphics.GraphicsDataSets

        m_graphicsCoordinateSet = graphicsDataSets.CreateCoordinateSet(1)

        m_graphicsColorSet = graphicsDataSets.CreateColorSet(1)

        m_graphicsColorSet.Add(1, 100, 100, 200)
        m_graphicsColorSet.Add(2, 150, 150, 250)

        m_graphicsColorIndexSet = graphicsDataSets.CreateIndexSet(1)

        m_triangleStripGraphics.CoordinateSet = m_graphicsCoordinateSet

        m_triangleStripGraphics.ColorSet = m_graphicsColorSet

        m_triangleStripGraphics.ColorIndexSet = m_graphicsColorIndexSet

        m_triangleStripGraphics.ColorBinding = ColorBindingEnum.kPerItemColors
        m_triangleStripGraphics.DepthPriority = 4
        m_triangleStripGraphics.BurnThrough = True

    End Sub

    Private Sub UpdatePreviewGraphics()
        'Remove the existing co-ordinates
        m_graphicsCoordinateSet = Nothing

        Dim interactionGraphics As InteractionGraphics
        interactionGraphics = m_interactionEvents.InteractionGraphics

        Dim graphicsDataSets As GraphicsDataSets
        graphicsDataSets = interactionGraphics.GraphicsDataSets

        m_graphicsCoordinateSet = graphicsDataSets.CreateCoordinateSet(1)

        'Remove the existing color indices
        m_graphicsColorIndexSet = Nothing

        m_graphicsColorIndexSet = graphicsDataSets.CreateIndexSet(1)
        m_triangleStripGraphics.CoordinateSet = m_graphicsCoordinateSet
        m_triangleStripGraphics.ColorIndexSet = m_graphicsColorIndexSet

        Dim transientGeometry As TransientGeometry
        transientGeometry = m_application.TransientGeometry

        'Get rack edge start point and end point
        Dim rackEdgeStartVertex As Vertex
        rackEdgeStartVertex = m_rackEdge.StartVertex

        Dim rackEdgeStartPt As Point
        rackEdgeStartPt = rackEdgeStartVertex.Point

        Dim rackEdgeStopVertex As Vertex
        rackEdgeStopVertex = m_rackEdge.StopVertex

        Dim rackEdgeStopPt As Point
        rackEdgeStopPt = rackEdgeStopVertex.Point

        Dim rackEdgeStartPtX As Double : rackEdgeStartPtX = rackEdgeStartPt.X
        Dim rackEdgeStartPtY As Double : rackEdgeStartPtY = rackEdgeStartPt.Y
        Dim rackEdgeStartPtZ As Double : rackEdgeStartPtZ = rackEdgeStartPt.Z

        Dim rackEdgeStopPtX As Double : rackEdgeStopPtX = rackEdgeStopPt.X
        Dim rackEdgeStopPtY As Double : rackEdgeStopPtY = rackEdgeStopPt.Y
        Dim rackEdgeStopPtZ As Double : rackEdgeStopPtZ = rackEdgeStopPt.Z

        Dim rackEdgeLengthX As Double
        rackEdgeLengthX = (rackEdgeStopPtX - rackEdgeStartPtX)

        Dim rackEdgeLengthY As Double
        rackEdgeLengthY = (rackEdgeStopPtY - rackEdgeStartPtY)

        Dim rackEdgeLengthZ As Double
        rackEdgeLengthZ = (rackEdgeStopPtZ - rackEdgeStartPtZ)

        Dim rackEdgeVector As Vector
        rackEdgeVector = transientGeometry.CreateVector(rackEdgeLengthX, rackEdgeLengthY, rackEdgeLengthZ)

        Dim rackFaceGeometry As Object
        rackFaceGeometry = m_rackFace.Geometry

        Dim rackFacePlane As Plane
        rackFacePlane = rackFaceGeometry

        Dim rackFaceNormalUnitVector As UnitVector
        rackFaceNormalUnitVector = rackFacePlane.Normal

        Dim rackFaceNormalX As Double : rackFaceNormalX = rackFaceNormalUnitVector.X
        Dim rackFaceNormalY As Double : rackFaceNormalY = rackFaceNormalUnitVector.Y
        Dim rackFaceNormalZ As Double : rackFaceNormalZ = rackFaceNormalUnitVector.Z

        Dim rackFaceNormalVector As Vector
        rackFaceNormalVector = rackFaceNormalUnitVector.AsVector()

        Dim rackPositiveExtentDirectionVector As Vector
        rackPositiveExtentDirectionVector = rackEdgeVector.CrossProduct(rackFaceNormalVector)

        Dim rackPositiveExtentDirectionUnitVector As UnitVector
        rackPositiveExtentDirectionUnitVector = rackPositiveExtentDirectionVector.AsUnitVector()

        Dim rackPositiveExtentDirectionX As Double
        rackPositiveExtentDirectionX = rackPositiveExtentDirectionUnitVector.X

        Dim rackPositiveExtentDirectionY As Double
        rackPositiveExtentDirectionY = rackPositiveExtentDirectionUnitVector.Y

        Dim rackPositiveExtentDirectionZ As Double
        rackPositiveExtentDirectionZ = rackPositiveExtentDirectionUnitVector.Z

        Dim graphicsEdgeStartPt As Point : graphicsEdgeStartPt = Nothing
        Dim graphicsParallelEdgeStartPt As Point : graphicsParallelEdgeStartPt = Nothing

        Select Case m_rackFeatureExtentDirection
            Case PartFeatureExtentDirectionEnum.kNegativeExtentDirection
                graphicsEdgeStartPt = rackEdgeStartPt

                graphicsParallelEdgeStartPt = transientGeometry.CreatePoint(rackEdgeStartPtX - m_rackExtents * rackPositiveExtentDirectionX, _
                                                                                rackEdgeStartPtY - m_rackExtents * rackPositiveExtentDirectionY, _
                                                                                rackEdgeStartPtZ - m_rackExtents * rackPositiveExtentDirectionZ)

            Case PartFeatureExtentDirectionEnum.kPositiveExtentDirection
                graphicsEdgeStartPt = rackEdgeStartPt

                graphicsParallelEdgeStartPt = transientGeometry.CreatePoint(rackEdgeStartPtX + m_rackExtents * rackPositiveExtentDirectionX, _
                                                                                rackEdgeStartPtY + m_rackExtents * rackPositiveExtentDirectionY, _
                                                                                rackEdgeStartPtZ + m_rackExtents * rackPositiveExtentDirectionZ)

            Case PartFeatureExtentDirectionEnum.kSymmetricExtentDirection
                graphicsEdgeStartPt = transientGeometry.CreatePoint(rackEdgeStartPtX - m_rackExtents * rackPositiveExtentDirectionX, _
                                                                                rackEdgeStartPtY - m_rackExtents * rackPositiveExtentDirectionY, _
                                                                                rackEdgeStartPtZ - m_rackExtents * rackPositiveExtentDirectionZ)

                graphicsParallelEdgeStartPt = transientGeometry.CreatePoint(rackEdgeStartPtX + m_rackExtents * rackPositiveExtentDirectionX, _
                                                                                rackEdgeStartPtY + m_rackExtents * rackPositiveExtentDirectionY, _
                                                                                rackEdgeStartPtZ + m_rackExtents * rackPositiveExtentDirectionZ)
        End Select

        Dim graphicsEdgeStartPtX As Double
        graphicsEdgeStartPtX = graphicsEdgeStartPt.X

        Dim graphicsEdgeStartPtY As Double
        graphicsEdgeStartPtY = graphicsEdgeStartPt.Y

        Dim graphicsEdgeStartPtZ As Double
        graphicsEdgeStartPtZ = graphicsEdgeStartPt.Z

        Dim graphicsParallelEdgeStartPtX As Double
        graphicsParallelEdgeStartPtX = graphicsParallelEdgeStartPt.X

        Dim graphicsParallelEdgeStartPtY As Double
        graphicsParallelEdgeStartPtY = graphicsParallelEdgeStartPt.Y

        Dim graphicsParallelEdgeStartPtZ As Double
        graphicsParallelEdgeStartPtZ = graphicsParallelEdgeStartPt.Z

        'Get the rack parallel edge start point and end point
        Dim rackEdgeLength As Double
        rackEdgeLength = rackEdgeStartPt.DistanceTo(rackEdgeStopPt)

        Dim nonRackWidth As Double
        nonRackWidth = rackEdgeLength - m_rackWidth

        Dim toothWidthProportion As Double : toothWidthProportion = 0.35

        Dim toothMajorWidth As Double
        toothMajorWidth = m_rackWidth / (m_numTeeth + (m_numTeeth - 1) * toothWidthProportion)

        Dim toothMinorWidth As Double
        toothMinorWidth = toothWidthProportion * toothMajorWidth

        Dim toothSlopeWidth As Double
        toothSlopeWidth = (toothMajorWidth - toothMinorWidth) / 2.0

        Dim point1 As Point
        Dim point2 As Point
        Dim point3 As Point
        Dim point4 As Point

        point1 = transientGeometry.CreatePoint(graphicsEdgeStartPtX + (((nonRackWidth / 2) / rackEdgeLength) * rackEdgeLengthX), _
                                                    graphicsEdgeStartPtY + (((nonRackWidth / 2) / rackEdgeLength) * rackEdgeLengthY), _
                                                    graphicsEdgeStartPtZ + (((nonRackWidth / 2) / rackEdgeLength) * rackEdgeLengthZ))

        point3 = transientGeometry.CreatePoint(graphicsParallelEdgeStartPtX + (((nonRackWidth / 2) / rackEdgeLength) * rackEdgeLengthX), _
                                                    graphicsParallelEdgeStartPtY + (((nonRackWidth / 2) / rackEdgeLength) * rackEdgeLengthY), _
                                                    graphicsParallelEdgeStartPtZ + (((nonRackWidth / 2) / rackEdgeLength) * rackEdgeLengthZ))

        AddGraphicsPoints(point1, point3)

        Dim xnr As Double : xnr = rackFaceNormalX * m_rackHeight
        Dim ynr As Double : ynr = rackFaceNormalY * m_rackHeight
        Dim znr As Double : znr = rackFaceNormalZ * m_rackHeight

        Dim xintv As Double : xintv = toothSlopeWidth * rackEdgeLengthX / rackEdgeLength
        Dim yintv As Double : yintv = toothSlopeWidth * rackEdgeLengthY / rackEdgeLength
        Dim zintv As Double : zintv = toothSlopeWidth * rackEdgeLengthZ / rackEdgeLength

        Dim xsht As Double : xsht = toothMinorWidth * rackEdgeLengthX / rackEdgeLength
        Dim ysht As Double : ysht = toothMinorWidth * rackEdgeLengthY / rackEdgeLength
        Dim zsht As Double : zsht = toothMinorWidth * rackEdgeLengthZ / rackEdgeLength

        Dim toothCt As Integer
        For toothCt = 1 To m_numTeeth
            Dim point1X As Double : point1X = point1.X
            Dim point1Y As Double : point1Y = point1.Y
            Dim point1Z As Double : point1Z = point1.Z

            Dim point3X As Double : point3X = point3.X
            Dim point3Y As Double : point3Y = point3.Y
            Dim point3Z As Double : point3Z = point3.Z

            point2 = transientGeometry.CreatePoint(point1X + xintv - xnr, point1Y + yintv - ynr, point1Z + zintv - znr)
            point4 = transientGeometry.CreatePoint(point3X + xintv - xnr, point3Y + yintv - ynr, point3Z + zintv - znr)

            AddGraphicsPoints(point2, point4)
            AddColorIndex(1)

            point1 = Nothing
            point3 = Nothing

            Dim point2X As Double : point2X = point2.X
            Dim point2Y As Double : point2Y = point2.Y
            Dim point2Z As Double : point2Z = point2.Z

            Dim point4X As Double : point4X = point4.X
            Dim point4Y As Double : point4Y = point4.Y
            Dim point4Z As Double : point4Z = point4.Z

            point1 = transientGeometry.CreatePoint(point2X + xsht, point2Y + ysht, point2Z + zsht)
            point3 = transientGeometry.CreatePoint(point4X + xsht, point4Y + ysht, point4Z + zsht)

            AddGraphicsPoints(point1, point3)
            AddColorIndex(2)

            point2 = Nothing
            point4 = Nothing

            point1X = point1.X
            point1Y = point1.Y
            point1Z = point1.Z

            point3X = point3.X
            point3Y = point3.Y
            point3Z = point3.Z

            point2 = transientGeometry.CreatePoint(point1X + xintv + xnr, point1Y + yintv + ynr, point1Z + zintv + znr)
            point4 = transientGeometry.CreatePoint(point3X + xintv + xnr, point3Y + yintv + ynr, point3Z + zintv + znr)

            AddGraphicsPoints(point2, point4)
            AddColorIndex(1)

            point1 = Nothing
            point3 = Nothing

            point2X = point2.X
            point2Y = point2.Y
            point2Z = point2.Z

            point4X = point4.X
            point4Y = point4.Y
            point4Z = point4.Z

            point1 = transientGeometry.CreatePoint(point2X + xsht, point2Y + ysht, point2Z + zsht)
            point3 = transientGeometry.CreatePoint(point4X + xsht, point4Y + ysht, point4Z + zsht)

            If toothCt <> m_numTeeth Then
                AddGraphicsPoints(point1, point3)
                AddColorIndex(2)

                point2 = Nothing
                point4 = Nothing
            End If
        Next

        m_application.ActiveView.Update()
    End Sub

    Private Sub AddColorIndex(ByVal colorIndex As Integer)
        Dim numGraphicsColorIndices As Integer
        numGraphicsColorIndices = m_graphicsColorIndexSet.Count

        m_graphicsColorIndexSet.Add(numGraphicsColorIndices + 1, colorIndex)
        m_graphicsColorIndexSet.Add(numGraphicsColorIndices + 2, colorIndex)

    End Sub

    Private Sub AddGraphicsPoints(ByVal cornerPt1 As Point, ByVal cornerPt2 As Point)
        Dim numGraphicsCoordPts As Integer
        numGraphicsCoordPts = m_graphicsCoordinateSet.Count

        m_graphicsCoordinateSet.Add(numGraphicsCoordPts + 1, cornerPt1)
        m_graphicsCoordinateSet.Add(numGraphicsCoordPts + 2, cornerPt2)

    End Sub

    Private Sub TerminatePreviewGraphics()
        m_graphicsCoordinateSet.Delete()

        m_graphicsColorSet.Delete()

        m_graphicsColorIndexSet.Delete()

        m_triangleStripGraphics.Delete()

        m_previewClientGraphicsNode.Delete()

        m_graphicsCoordinateSet = Nothing
        m_graphicsColorSet = Nothing
        m_graphicsColorIndexSet = Nothing
        m_triangleStripGraphics = Nothing
        m_previewClientGraphicsNode = Nothing
    End Sub

    '-----------------------------------------------------
    '----------Implementation of Callbacks
    '-----------------------------------------------------

    '----------------------------------------------------
    '---------Implementation of SlectEvents callbacks
    '----------------------------------------------------

    Public Overrides Sub OnPreSelect(ByVal preSelectEntity As Object, ByRef doHighlight As Boolean, ByVal morePreSelectEntities As ObjectCollection, ByVal selectionDevice As SelectionDeviceEnum, ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        doHighlight = False

        'If rack face is being pre-selected,if edge has been selected already
        'highlight the face only if the already selected edge belongs to the face
        If TypeOf preSelectEntity Is Face Then
            If Not (m_rackEdge Is Nothing) Then
                Dim preSelectFace As Face
                preSelectFace = preSelectEntity

                Dim edges As Edges
                edges = preSelectFace.Edges

                Dim numEdges As Integer
                numEdges = edges.Count

                Dim edge As Edge
                Dim edgeCt As Integer
                For edgeCt = 1 To numEdges
                    edge = edges(edgeCt)

                    If edge Is m_rackEdge Then
                        doHighlight = True
                        Exit For
                    End If
                Next
            Else
                doHighlight = True
            End If
        End If

        'If rack edge is being pre-selected,if face has been selected alerady
        'highlight the edge only if the edge belongs to the already selected face
        If TypeOf preSelectEntity Is Edge Then
            If Not (m_rackFace Is Nothing) Then
                Dim preSelectEdge As Edge
                preSelectEdge = preSelectEntity

                Dim edges As Edges
                edges = m_rackFace.Edges

                Dim numEdges As Integer
                numEdges = edges.Count

                Dim edgeCt As Integer
                Dim edge As Edge
                For edgeCt = 1 To numEdges
                    edge = edges(edgeCt)

                    If edge Is preSelectEdge Then
                        doHighlight = True
                        Exit For
                    End If

                Next
            Else
                doHighlight = True
            End If
        End If
    End Sub

    Public Overrides Sub OnSelect(ByVal justSelectedEntities As ObjectsEnumerator, ByVal selectionDevice As SelectionDeviceEnum, ByVal modelPosition As Point, ByVal viewPosition As Point2d, ByVal view As Inventor.View)
        Dim numSelectedEntities As Integer
        numSelectedEntities = justSelectedEntities.Count

        If numSelectedEntities > 0 Then
            Dim selectedEntity As Object
            selectedEntity = justSelectedEntities(1)

            'If face is selected
            If m_rackFaceCmdDlg.checkBoxFace.Checked And (TypeOf selectedEntity Is Face) Then
                'Get the selected face,if face had been previously selected,se t it to nothing
                m_rackFace = selectedEntity

                'Un-check rack face selection button
                m_rackFaceCmdDlg.checkBoxFace.Checked = False

                'If edge has not been selected,start selection for it
                If m_rackEdge Is Nothing Then
                    'Check rack direction selection button
                    m_rackFaceCmdDlg.checkBoxDirection.Checked = True

                    'Start dirction selection
                    EnableInteraction()
                Else
                    'Disable selection
                    DisableInteraction()

                    UpdateCommandStatus()
                End If
            End If

            'If edge is selected
            If m_rackFaceCmdDlg.checkBoxDirection.Checked And (TypeOf selectedEntity Is Edge) Then
                'Get the selected edge,if edge had been previously selected,set it to nothing
                m_rackEdge = selectedEntity

                'Un-check rack direction selection button
                m_rackFaceCmdDlg.checkBoxDirection.Checked = False

                'Disable selection
                DisableInteraction()

                UpdateCommandStatus()
            End If
        End If
    End Sub

    '------------------------------------------------------------
    '-------Implementation of InteractionEvents callbacks
    '------------------------------------------------------------

    Public Overrides Sub OnHelp(ByVal beforeOrAfter As EventTimingEnum, ByVal context As NameValueMap, ByRef handlingCode As HandlingCodeEnum)
        'Get the help manager object and display the start page of the "Inventor API" help
        m_application.HelpManager.DisplayHelpTopic("ADMAPI_12_0.chm", "")
        handlingCode = HandlingCodeEnum.kEventHandled
    End Sub


    '---------------------------------------------------
    '-----End of Callbacks
    '----------------------------------------------------
    Public Sub UpdateCommandStatus()
        'Get the rack parameters from the rack command dialog

        'by default,disable the OK button on dialog
        'enable it later if all parameters are valid
        m_rackFaceCmdDlg.buttonOK.Enabled = False

        'All parameters must be valid
        If Not m_rackFaceCmdDlg.AllParametersAreValid() Then
            Exit Sub
        End If

        'Transfer parameters
        m_numTeeth = System.Convert.ToInt32(m_rackFaceCmdDlg.m_numTeeth)

        m_rackHeight = GetValueFromExpression(m_rackFaceCmdDlg.m_rackHeight)

        m_rackWidth = GetValueFromExpression(m_rackFaceCmdDlg.m_rackWidth)

        m_rackExtents = GetValueFromExpression(m_rackFaceCmdDlg.m_rackExtents)

        Select Case m_rackFaceCmdDlg.m_rackExtentsDirection
            Case 0 : m_rackFeatureExtentDirection = PartFeatureExtentDirectionEnum.kNegativeExtentDirection
            Case 1 : m_rackFeatureExtentDirection = PartFeatureExtentDirectionEnum.kPositiveExtentDirection
            Case 2 : m_rackFeatureExtentDirection = PartFeatureExtentDirectionEnum.kSymmetricExtentDirection
        End Select

        'If all rack face parameters are alright,update the preview graphics and enable "OK" button
        If (Not (m_rackFace Is Nothing)) And (Not (m_rackEdge Is Nothing)) And (m_numTeeth > 0) And (m_rackHeight > 0) And (m_rackWidth > 0) And (m_rackExtents > 0) Then
            'Update the preview
            UpdatePreviewGraphics()

            'Enable the  OK button on dialog
            m_rackFaceCmdDlg.buttonOK.Enabled = True
        End If
    End Sub

    Public Function GetValueFromExpression(ByVal expression As String) As Double
        'Get the active document
        Dim activeDocument As Document
        activeDocument = m_application.ActiveDocument

        'Get the units of measure object
        Dim unitsOfMeasure As UnitsOfMeasure
        unitsOfMeasure = activeDocument.UnitsOfMeasure

        'Get the current lenght units of the user
        Dim lengthUnitsType As UnitsTypeEnum
        lengthUnitsType = unitsOfMeasure.LengthUnits

        'Convert the expression to the current length units of user
        Try
            GetValueFromExpression = unitsOfMeasure.GetValueFromExpression(expression, lengthUnitsType)
        Catch
            GetValueFromExpression = 0.0
        End Try

    End Function
End Class
