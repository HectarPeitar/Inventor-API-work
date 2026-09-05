Imports Inventor
Imports System.Drawing
Imports System.Windows.Forms

Friend Class AddSlotOptionButton
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
            'if same session, combobox definitions will already exist
            Dim slotWidthComboBoxDefinition As ComboBoxDefinition
            slotWidthComboBoxDefinition = InventorApplication.CommandManager.ControlDefinitions.Item("Autodesk:SimpleAddIn:SlotWidthCboBox")

            Dim slotHeightComboBoxDefinition As ComboBoxDefinition
            slotHeightComboBoxDefinition = InventorApplication.CommandManager.ControlDefinitions.Item("Autodesk:SimpleAddIn:SlotHeightCboBox")

            'add new item to combo boxes
            slotWidthComboBoxDefinition.AddItem(Convert.ToString(slotWidthComboBoxDefinition.ListCount + 1) + " cm", 0)
            slotHeightComboBoxDefinition.AddItem(Convert.ToString(slotHeightComboBoxDefinition.ListCount + 1) + " cm", 0)

        Catch ex As Exception
            System.Windows.Forms.MessageBox.Show(ex.ToString)
        End Try

    End Sub

#End Region

End Class
