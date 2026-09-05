Imports Inventor
Imports System.Drawing
Imports System.Windows.Forms

Friend Class ToggleSlotStateButton
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
            'if same session, button definition will already exist
            Dim drawSlotButtonDefinition As ButtonDefinition
            drawSlotButtonDefinition = InventorApplication.CommandManager.ControlDefinitions.Item("Autodesk:SimpleAddIn:DrawSlotCmdBtn")

            If drawSlotButtonDefinition.Enabled = True Then
                drawSlotButtonDefinition.Enabled = False
            Else
                drawSlotButtonDefinition.Enabled = True
            End If

        Catch ex As Exception
            MessageBox.Show(ex.ToString)
        End Try

    End Sub

#End Region

End Class
