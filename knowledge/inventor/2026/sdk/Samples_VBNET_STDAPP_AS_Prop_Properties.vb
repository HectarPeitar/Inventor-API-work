Option Strict Off
Option Explicit On
Imports Inventor
Imports VB = Microsoft.VisualBasic
Friend Class frmProperties
    Inherits System.Windows.Forms.Form


    Private oApprenticeApp As Inventor.ApprenticeServerComponent
    Private oApprenticeServerDoc As Inventor.ApprenticeServerDocument
    Private ChangeMade As Boolean
    Private frmThumbnailObject As frmThumbnail

    Private Sub cmdBrowse_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdBrowse.Click
        If oApprenticeApp Is Nothing Then
            oApprenticeApp = New Inventor.ApprenticeServerComponent
        End If

        If Not oApprenticeApp.Document Is Nothing Then
            oApprenticeApp.Close()
        End If

        ' Define property for the open dialog.
        'UPGRADE_WARNING: CommonDialog variable was not upgraded Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="671167DC-EA81-475D-B690-7A40C7BF4A23"'
        With CommonDialog1Open
            ' Use the current workspace as the initial directory.  If there's not a workspace
            ' defined this will return an empty string which results in VB using a default
            ' initial directory.
            .InitialDirectory = oApprenticeApp.FileLocations.Workspace

            .Title = "Display Properties"
            .Filter = "Inventor Files (*.iam, *.ipt, *.idw, *.ipn, *.ide) | *.iam; *.ipt; *.idw; *.ipn; *.ide"
            .FilterIndex = 0
            .ShowReadOnly = False

            On Error Resume Next
            .ShowDialog()
            If Err.Number Then
                Exit Sub
            End If
            On Error GoTo 0
        End With

        ' Write the selected filename to the text box.
        txtFilename.Text = CommonDialog1Open.FileName

        ' Check to make sure a name was specified and call the function
        ' to list the properties of the file.
        If txtFilename.Text <> "" Then
            ShowProperties()
        End If
    End Sub

    Private Sub cmdCancel_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdCancel.Click
        Me.Close()
    End Sub

    Private Sub cmdSaveChanges_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdSaveChanges.Click
        ' If any properties were modified save the changes to the Inventor file.
        If ChangeMade Then
            ' Save the property changes to the document.
            oApprenticeServerDoc.FilePropertySets.FlushToFile()
        End If

        Me.Close()
    End Sub

    Private Sub ShowProperties()
        ' Clear the list.
        lstProperties.Items.Clear()

        ' Open the specified file.
        oApprenticeServerDoc = oApprenticeApp.Open(txtFilename.Text)
        If oApprenticeServerDoc Is Nothing Then
            MsgBox("Unable to open the specified document.")
            Exit Sub
        End If

        ' Iterate through each of the property sets.
        Dim oPropSet As Inventor.PropertySet
        Dim oProp As Inventor.Property
        For Each oPropSet In oApprenticeServerDoc.FilePropertySets
            lstProperties.Items.Add("Property Set: " & oPropSet.DisplayName & ", " & oPropSet.InternalName)

            ' Iterate through the properties in each set.
            For Each oProp In oPropSet
                ' Display information for the property, special casing for dates.
                If VarType(oProp.Value) <> VariantType.Date Then
                    lstProperties.Items.Add(Space(8) & oProp.Name & ", " & oProp.PropId & " = " & ShowValue(oProp))
                Else
                    ' Check for the special date of Jan. 1, 1601 which is used to indicate an undefined date.
                    If oProp.Value = #1/1/1601# Then
                        lstProperties.Items.Add(Space(8) & oProp.Name & ", " & oProp.PropId & " = ")
                    Else
                        lstProperties.Items.Add(Space(8) & oProp.Name & ", " & oProp.PropId & " = " & ShowValue(oProp))
                    End If
                End If
            Next oProp
        Next oPropSet
    End Sub

    Private Sub frmProperties_FormClosed(ByVal eventSender As System.Object, ByVal eventArgs As System.Windows.Forms.FormClosedEventArgs) Handles Me.FormClosed
        ' Release the document and apprentice references.
        'UPGRADE_NOTE: Object oApprenticeServerDoc may not be destroyed until it is garbage collected. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="6E35BFF6-CD74-4B09-9689-3E1A43DF8969"'
        oApprenticeServerDoc = Nothing
        'UPGRADE_NOTE: Object oApprenticeApp may not be destroyed until it is garbage collected. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="6E35BFF6-CD74-4B09-9689-3E1A43DF8969"'
        oApprenticeApp = Nothing
    End Sub


    Private Function ShowValue(ByRef InProp As Inventor.Property) As String
        ' Get the value within an On Error statement to catch the
        ' case of a file where no thumbnail image is available.
        Dim vValue As Object
        On Error Resume Next
        vValue = InProp.Value
        If Err.Number Or IsNothing(InProp.Value) Or IsError(InProp.Value) Or IsDBNull(InProp.Value) Then
            ShowValue = ""
        Else
            ' Return the value as a string.
            ShowValue = vValue
        End If
    End Function


    Private Sub lstProperties_DoubleClick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles lstProperties.DoubleClick
        Dim SelectIndex As Short
        SelectIndex = lstProperties.SelectedIndex
        Dim SelectText As String
        SelectText = lstProperties.GetItemText(lstProperties.SelectedItem) 'VB6.GetItemString(lstProperties, SelectIndex)

        ' Check to make sure a property and not a property set was selected.
        Dim StartDelimPosition As Short
        Dim EndDelimPosition As Short
        Dim PropID As Integer
        Dim i As Short
        Dim PropSetID As String
        Dim oProp As Inventor.Property
        Dim oPic As System.Drawing.Image
        Dim TestString As String
        Dim NewString As String
        Dim NewCurrency As Decimal
        Dim NewInteger As Short
        Dim NewLong As Integer
        Dim NewFloat As Single
        Dim NewDouble As Double
        Dim NewDate As Date
        If VB.Left(SelectText, 1) <> " " Then
            MsgBox("This sample does not support editing of property sets.  You must select a property.")
        Else
            ' Parse out the property ID from the selected item.
            StartDelimPosition = InStr(SelectText, ",")
            EndDelimPosition = InStr(SelectText, "=")
            SelectText = Mid(SelectText, StartDelimPosition + 1, EndDelimPosition - StartDelimPosition - 1)
            PropID = Val(SelectText)

            ' Search back up in the list to determine which property set the selected property belongs to.
            For i = SelectIndex - 1 To 0 Step -1
                Dim ItemText As String
                ItemText = lstProperties.GetItemText(lstProperties.Items(i))
                If VB.Left(ItemText, 13) = "Property Set:" Then

                    ' Parse out the ID of the property set.
                    ' The ID's of the different property sets can also be found by
                    ' using the VB Object Browser.  The ID will be displayed as part
                    ' of the description when selecting the propety set enum in the browser.
                    PropSetID = Trim(VB.Right(ItemText, Len(ItemText) - InStr(ItemText, ",")))
                    Exit For
                End If
            Next

            ' Get the specific property using the property set ID and the property ID.
            oProp = oApprenticeServerDoc.FilePropertySets.Item(PropSetID).ItemByPropId(PropID)

            ' Special case for the thumbnail property.
            If PropSetID = "{F29F85E0-4FF9-1068-AB91-08002B27B3D9}" And PropID = 17 Then

                oPic = ConvertImage.IPictureToImage(oProp.Value) 'VB6.IPictureToImage(oProp.Value)
                frmThumbnailObject.Show()
                frmThumbnailObject.picThumbnail.Image = oPic
            Else
                Select Case VarType(oProp.Value)
                    Case VariantType.String
                        NewString = ""
                        ' Display an input box initialized with the current value of the property.
                        NewString = InputBox("Enter new value for " & oProp.Name, "Specify New Value", oProp.Value)

                        ' Check for empty string and assume Cancel was selected in the input box.
                        If NewString <> oProp.Value And VarPtr(NewString) <> 0 Then
                            ' Set the property value to the new value.
                            oProp.Value = NewString

                            ' Update the line in the list box.
                            lstProperties.Items(SelectIndex) = "   " & oProp.Name & ", " & oProp.PropId & " = " & ShowValue(oProp)
                            'VB6.SetItemString(lstProperties, SelectIndex, "   " & oProp.Name & ", " & oProp.PropId & " = " & ShowValue(oProp))

                            ' Set the flag indicating changes were made.
                            ChangeMade = True
                            cmdSaveChanges.Enabled = True
                        End If
                    Case VariantType.Boolean
                        ' Toggle the value of the property.
                        oProp.Value = Not oProp.Value

                        ' Update the line in the list box.
                        lstProperties.Items(SelectIndex) = "   " & oProp.Name & ", " & oProp.PropId & " = " & ShowValue(oProp)
                        'VB6.SetItemString(lstProperties, SelectIndex, "   " & oProp.Name & ", " & oProp.PropId & " = " & ShowValue(oProp))

                        ' Set the flag indicating changes were made.
                        ChangeMade = True
                        cmdSaveChanges.Enabled = True
                    Case VariantType.Decimal
                        ' Display an input box initialized with the current value of the property.
                        TestString = InputBox("Enter a new Currency value for " & oProp.Name, "Specify New Currency Value", oProp.Value)

                        ' Check for empty string and assume Cancel was selected in the input box.
                        If TestString = "" Then
                            Exit Sub
                        End If

                        ' Check that the input string defines a valid number.
                        If Not IsNumeric(TestString) Then
                            MsgBox("Invalid currency value specified.")
                            Exit Sub
                        End If

                        ' Set the string to a variable of Currency type.  The value of a property is
                        ' a Variant so this ensures the actual type of the property remains Currency type.
                        NewCurrency = CDec(TestString)

                        ' Set the property value to the new value.
                        oProp.Value = NewCurrency

                        ' Update the line in the list box.
                        lstProperties.Items(SelectIndex) = "   " & oProp.Name & ", " & oProp.PropId & " = " & ShowValue(oProp)
                        'VB6.SetItemString(lstProperties, SelectIndex, "   " & oProp.Name & ", " & oProp.PropId & " = " & ShowValue(oProp))

                        ' Set the flag indicating changes were made.
                        ChangeMade = True
                        cmdSaveChanges.Enabled = True
                    Case VariantType.Short
                        ' Display an input box initialized with the current value of the property.
                        TestString = InputBox("Enter a new Integer value for " & oProp.Name, "Specify New Integer Value", oProp.Value)

                        ' Check for empty string and assume Cancel was selected in the input box.
                        If TestString = "" Then
                            Exit Sub
                        End If

                        ' Check that the input string defines a valid number.
                        If Not IsNumeric(TestString) Then
                            MsgBox("Invalid Integer value specified.")
                            Exit Sub
                        End If

                        ' Set the string to a variable of Integer type.  The value of a property is
                        ' a Variant so this ensures the actual type of the property remains Integer type.
                        NewInteger = CShort(TestString)

                        ' Set the property value to the new value.
                        oProp.Value = NewInteger

                        ' Update the line in the list box.
                        lstProperties.Items(SelectIndex) = "   " & oProp.Name & ", " & oProp.PropId & " = " & ShowValue(oProp)
                        'VB6.SetItemString(lstProperties, SelectIndex, "   " & oProp.Name & ", " & oProp.PropId & " = " & ShowValue(oProp))

                        ' Set the flag indicating changes were made.
                        ChangeMade = True
                        cmdSaveChanges.Enabled = True
                    Case VariantType.Integer
                        ' Display an input box initialized with the current value of the property.
                        TestString = InputBox("Enter a new Long value for " & oProp.Name, "Specify New Long Value", oProp.Value)

                        ' Check for empty string and assume Cancel was selected in the input box.
                        If TestString = "" Then
                            Exit Sub
                        End If

                        ' Check that the input string defines a valid number.
                        If Not IsNumeric(TestString) Then
                            MsgBox("Invalid Long value specified.")
                            Exit Sub
                        End If

                        ' Set the string to a variable of Long type.  The value of a property is
                        ' a Variant so this ensures the actual type of the property remains Long type.
                        NewLong = CInt(TestString)

                        ' Set the property value to the new value.
                        oProp.Value = NewLong

                        ' Update the line in the list box.
                        lstProperties.Items(SelectIndex) = "   " & oProp.Name & ", " & oProp.PropId & " = " & ShowValue(oProp)
                        'VB6.SetItemString(lstProperties, SelectIndex, "   " & oProp.Name & ", " & oProp.PropId & " = " & ShowValue(oProp))

                        ' Set the flag indicating changes were made.
                        ChangeMade = True
                        cmdSaveChanges.Enabled = True
                    Case VariantType.Single
                        ' Display an input box initialized with the current value of the property.
                        TestString = InputBox("Enter a new numeric value for " & oProp.Name, "Specify new numeric value", oProp.Value)

                        ' Check for empty string and assume Cancel was selected in the input box.
                        If TestString = "" Then
                            Exit Sub
                        End If

                        ' Check that the input string defines a valid number.
                        If Not IsNumeric(TestString) Then
                            MsgBox("Invalid Float value specified.")
                            Exit Sub
                        End If

                        ' Set the string to a variable of Float type.  The value of a property is
                        ' a Variant so this ensures the actual type of the property remains Float type.
                        NewFloat = CSng(TestString)

                        ' Set the property value to the new value.
                        oProp.Value = NewFloat

                        ' Update the line in the list box.
                        lstProperties.Items(SelectIndex) = "   " & oProp.Name & ", " & oProp.PropId & " = " & ShowValue(oProp)
                        'VB6.SetItemString(lstProperties, SelectIndex, "   " & oProp.Name & ", " & oProp.PropId & " = " & ShowValue(oProp))

                        ' Set the flag indicating changes were made.
                        ChangeMade = True
                        cmdSaveChanges.Enabled = True
                    Case VariantType.Double
                        ' Display an input box initialized with the current value of the property.
                        TestString = InputBox("Enter a new Double value for " & oProp.Name, "Specify new Double value", oProp.Value)

                        ' Check for empty string and assume Cancel was selected in the input box.
                        If TestString = "" Then
                            Exit Sub
                        End If

                        ' Check that the input string defines a valid number.
                        If Not IsNumeric(TestString) Then
                            MsgBox("Invalid Double value specified.")
                            Exit Sub
                        End If

                        ' Set the string to a variable of Double type.  The value of a property is
                        ' a Variant so this ensures the actual type of the property remains Double type.
                        NewDouble = CDbl(TestString)

                        ' Set the property value to the new value.
                        oProp.Value = NewDouble

                        ' Update the line in the list box.
                        lstProperties.Items(SelectIndex) = "   " & oProp.Name & ", " & oProp.PropId & " = " & ShowValue(oProp)
                        'VB6.SetItemString(lstProperties, SelectIndex, "   " & oProp.Name & ", " & oProp.PropId & " = " & ShowValue(oProp))

                        ' Set the flag indicating changes were made.
                        ChangeMade = True
                        cmdSaveChanges.Enabled = True
                    Case VariantType.Date
                        ' Display an input box initialized with the current value of the property, special casing for Jan. 1, 1601,
                        ' which is used to indicate an empty date.
                        If oProp.Value = #1/1/1601# Then
                            TestString = InputBox("Enter a new Date value for " & oProp.Name, "Specify new Date value")
                        Else
                            TestString = InputBox("Enter a new Date value for " & oProp.Name, "Specify new Date value", oProp.Value)
                        End If

                        ' Check for empty string and assume Cancel was selected in the input box.
                        If TestString = "" Then
                            Exit Sub
                        End If

                        ' Check that the input string defines a valid date.
                        If Not IsDate(TestString) Then
                            MsgBox("Invalid Date value specified.")
                            Exit Sub
                        End If

                        ' Set the string to a variable of Date type.  The value of a property is
                        ' a Variant so this ensures the actual type of the property remains Date type.
                        NewDate = CDate(TestString)

                        ' Set the property value to the new value.
                        oProp.Value = NewDate

                        ' Update the line in the list box.
                        lstProperties.Items(SelectIndex) = "   " & oProp.Name & ", " & oProp.PropId & " = " & ShowValue(oProp)
                        'VB6.SetItemString(lstProperties, SelectIndex, "   " & oProp.Name & ", " & oProp.PropId & " = " & ShowValue(oProp))

                        ' Set the flag indicating changes were made.
                        ChangeMade = True
                        cmdSaveChanges.Enabled = True
                    Case Else
                        MsgBox("This sample doesn't support editing the type of property selected.")
                End Select
            End If
        End If
    End Sub

    ' Below function is used to judge if the InputBox return a null string because of clicking Cancel or empty string with clicking OK.
    Private Function VarPtr(ByVal obj As Object) As Long
        Dim GC As System.Runtime.InteropServices.GCHandle = System.Runtime.InteropServices.GCHandle.Alloc(obj, System.Runtime.InteropServices.GCHandleType.Pinned)

        Dim ReturnVal As Long = GC.AddrOfPinnedObject.ToInt64

        GC.Free()
        Return ReturnVal
    End Function

    Private Sub txtFilename_KeyPress(ByVal eventSender As System.Object, ByVal eventArgs As System.Windows.Forms.KeyPressEventArgs) Handles txtFilename.KeyPress
        Dim KeyAscii As Short = Asc(eventArgs.KeyChar)
        If KeyAscii = 13 And txtFilename.Text <> "" Then
            KeyAscii = 0
            ShowProperties()
        End If
        eventArgs.KeyChar = Chr(KeyAscii)
        If KeyAscii = 0 Then
            eventArgs.Handled = True
        End If
    End Sub

    Private Sub txtFilename_Leave(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtFilename.Leave
        If txtFilename.Text <> "" Then
            ShowProperties()
        End If
    End Sub
End Class

Public Class ConvertImage
    Inherits System.Windows.Forms.AxHost

    Public Sub New()
        MyBase.New("59EE46BA-677D-4d20-BF10-8D8067CB8B33")
    End Sub

    'Public Shared Function ImageToIPicture(ByVal Image As System.Drawing.Image) As stdole.IPictureDisp
    '    Dim iPic As stdole.IPictureDisp
    '    Try
    '        Dim obj As Object = GetIPictureFromPicture(Image)
    '        iPic = CType(obj, stdole.IPictureDisp)
    '    Catch e As Exception
    '        Return Nothing
    '    End Try
    '    Return iPic
    'End Function

    <CLSCompliant(False)>
    Public Shared Function IPictureToImage(ByVal Image As stdole.IPictureDisp) As System.Drawing.Image
        Dim img As System.Drawing.Image
        Try
            img = GetPictureFromIPicture(Image)
        Catch e As Exception
            img = Nothing
        End Try
        Return img
    End Function

End Class