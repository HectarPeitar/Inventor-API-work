Imports Inventor
Imports System.Drawing
Imports System.Windows.Forms

Friend Class DrawSlotButton
    Inherits Button

#Region "Methods"

    Public Sub New(ByVal displayName As String, _
                    ByVal internalName As String, _
                    ByVal commandType As CommandTypesEnum, _
                    ByVal clientId As String, _
                    Optional ByVal description As String = "", _
                    Optional ByVal tooltip As String = "", _
                    Optional ByVal standardIcon As Icon = Nothing, _
                    Optional ByVal largeIcon As Icon = Nothing, _
                    Optional ByVal buttonDisplayType As ButtonDisplayEnum = ButtonDisplayEnum.kDisplayTextInLearningMode)

        MyBase.New(displayName, internalName, commandType, clientId, description, tooltip, standardIcon, largeIcon, buttonDisplayType)

    End Sub

    Protected Overrides Sub ButtonDefinition_OnExecute(ByVal context As Inventor.NameValueMap)

        Try
            'check to make sure a sketch is active
            If TypeOf InventorApplication.ActiveEditObject Is PlanarSketch Then

                'if same session, combobox definitions will already exist
                Dim slotWidthComboBoxDefinition As ComboBoxDefinition
                slotWidthComboBoxDefinition = InventorApplication.CommandManager.ControlDefinitions.Item("Autodesk:SimpleAddIn:SlotWidthCboBox")

                Dim slotHeightComboBoxDefinition As ComboBoxDefinition
                slotHeightComboBoxDefinition = InventorApplication.CommandManager.ControlDefinitions.Item("Autodesk:SimpleAddIn:SlotHeightCboBox")

                'get the selected width from combo box
                Dim slotWidth As Double
                slotWidth = slotWidthComboBoxDefinition.ListIndex

                'get the selected height from combo box
                Dim slotHeight As Double
                slotHeight = slotHeightComboBoxDefinition.ListIndex

                If (slotWidth > 0 And slotHeight > 0) Then

                    'draw the sketch for the slot
                    Dim planarSketch As PlanarSketch
                    planarSketch = InventorApplication.ActiveEditObject

                    Dim lines(2) As SketchLine
                    Dim arcs(2) As SketchArc

                    Dim transientGeometry As TransientGeometry
                    transientGeometry = InventorApplication.TransientGeometry

                    'start a transaction so the slot will be within a single undo step
                    Dim createSlotTransaction As Transaction
                    createSlotTransaction = InventorApplication.TransactionManager.StartTransaction(InventorApplication.ActiveDocument, "Create Slot")

                    'draw the lines and arcs that make up the shape of the slot
                    lines(1) = planarSketch.SketchLines.AddByTwoPoints(transientGeometry.CreatePoint2d(0, 0), transientGeometry.CreatePoint2d(slotWidth, 0))
                    arcs(1) = planarSketch.SketchArcs.AddByCenterStartEndPoint(transientGeometry.CreatePoint2d(slotWidth, slotHeight / 2.0), lines(1).EndSketchPoint, transientGeometry.CreatePoint2d(slotWidth, slotHeight))

                    lines(2) = planarSketch.SketchLines.AddByTwoPoints(arcs(1).EndSketchPoint, transientGeometry.CreatePoint2d(0, slotHeight))
                    arcs(2) = planarSketch.SketchArcs.AddByCenterStartEndPoint(transientGeometry.CreatePoint2d(0, slotHeight / 2.0), lines(2).EndSketchPoint, lines(1).StartSketchPoint)

                    'create the tangent constraints between the lines and arcs
                    planarSketch.GeometricConstraints.AddTangent(lines(1), arcs(1))
                    planarSketch.GeometricConstraints.AddTangent(lines(2), arcs(1))
                    planarSketch.GeometricConstraints.AddTangent(lines(2), arcs(2))
                    planarSketch.GeometricConstraints.AddTangent(lines(1), arcs(2))

                    'create a parallel constraint between the two lines
                    planarSketch.GeometricConstraints.AddParallel(lines(1), lines(2))

                    'end the transaction
                    createSlotTransaction.End()

                Else

                    'valid width/height was not specified
                    MessageBox.Show("Please specify valid slot width and height")

                End If
            Else
                'no sketch is active, so display an error
                MessageBox.Show("A sketch must be active for this command")

            End If

        Catch ex As Exception
            MessageBox.Show(ex.ToString)
        End Try

    End Sub

#End Region

End Class
