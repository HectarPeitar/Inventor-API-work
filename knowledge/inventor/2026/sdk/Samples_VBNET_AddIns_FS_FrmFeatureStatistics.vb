Option Strict Off
Option Explicit On
Imports VB = Microsoft.VisualBasic
Friend Class FrmFeatureStatistics
    Inherits System.Windows.Forms.Form
    '  This sample contains all event handlers for the controls in the dialog box

    ' Declarations of the member functions and const variable, they will be used to find the notepad and send the message of clipboard to notepad
    Private Declare Function FindWindow Lib "user32" Alias "FindWindowA" (ByVal lpClassName As String, ByVal lpWindowName As String) As Integer
    Private Declare Function FindWindowEx Lib "user32" Alias "FindWindowExA" (ByVal hWnd1 As Integer, ByVal hWnd2 As Integer, ByVal lpsz1 As String, ByVal lpsz2 As String) As Integer

    Private Declare Function SendMessage Lib "user32" Alias "SendMessageA" (ByVal hwnd As Integer, ByVal wMsg As Integer, ByVal wParam As Integer, ByRef lParam As Integer) As Integer
    Private Const WM_PASTE As Short = &H302S

       Private Sub checkIgnSuppressFeatures_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles checkIgnSuppressFeatures.CheckStateChanged
        SetCurrentFeaturesCountTypesInfo()

        Dim tmpLstItem As System.Windows.Forms.ListViewItem
        Dim l, m As Integer
        For l = 0 To UBound(sFeatureName)
            If checkIgnSuppressFeatures.CheckState = 0 Then ' "Ignore the Suppressed Features" checkbox is canceled
                If Not IsExistingListItem(sFeatureName(l)) Then
                    ' Add the suppressed feature's info as a new row into ListView if this feature type is not contained by ListView
                    tmpLstItem = Nothing
                    tmpLstItem = ListViewInfo.Items.Add("")

                    tmpLstItem.Text = sFeatureName(l)
                    If tmpLstItem.SubItems.Count > 1 Then
                        tmpLstItem.SubItems(1).Text = CStr(lUnSuppressedFeatureCount(l) + lSuppressedFeatureCount(l))
                    Else
                        tmpLstItem.SubItems.Add(New System.Windows.Forms.ListViewItem.ListViewSubItem(Nothing, CStr(lUnSuppressedFeatureCount(l) + lSuppressedFeatureCount(l))))
                    End If
                Else
                    ' Just update the feature's count info if this feature type has been listed in the ListView window
                    For m = 0 To ListViewInfo.Items.Count - 1

                        If StrComp(ListViewInfo.Items.Item(m).Text, sFeatureName(l), CompareMethod.Text) = 0 Then
                            If ListViewInfo.Items.Item(m).SubItems.Count > 1 Then
                                ListViewInfo.Items.Item(m).SubItems(1).Text = CStr(lUnSuppressedFeatureCount(l) + lSuppressedFeatureCount(l))
                            Else
                                ListViewInfo.Items.Item(m).SubItems.Add(New System.Windows.Forms.ListViewItem.ListViewSubItem(Nothing, CStr(lUnSuppressedFeatureCount(l) + lSuppressedFeatureCount(l))))
                            End If : Exit For
                        End If
                    Next
                End If
            ElseIf checkIgnSuppressFeatures.CheckState = 1 Then  ' "Ignore the Suppressed Features" checkbox is checked
                If lUnSuppressedFeatureCount(l) = 0 Then
                    ' Remove the suppressed features' info- a row from ListView if all features of one type are suppressed
                    Call RemoveListItem(sFeatureName(l))
                Else
                    ' Just update the feature's count info if this feature type contains unsuppressed ones
                    For m = 0 To ListViewInfo.Items.Count - 1

                        If StrComp(ListViewInfo.Items.Item(m).Text, sFeatureName(l), CompareMethod.Text) = 0 Then

                            If ListViewInfo.Items.Item(m).SubItems.Count > 1 Then
                                ListViewInfo.Items.Item(m).SubItems(1).Text = CStr(lUnSuppressedFeatureCount(l))
                            Else
                                ListViewInfo.Items.Item(m).SubItems.Add(New System.Windows.Forms.ListViewItem.ListViewSubItem(Nothing, CStr(lUnSuppressedFeatureCount(l))))
                            End If : Exit For
                        End If
                    Next
                End If ' End of "If lUnSuppressedFeatureCount(l) = 0"
            End If ' End of "If checkIgnSuppressFeatures.Value = 0"
        Next
    End Sub

    ' Update the ListView content when checking or canceling "Ignore the Work Features (Plane, Axis and Point)" checkbox
    ' Add user-defined work features info- a row when "Ignore the Work Features (Plane, Axis and Point)" checkbox is canceled
    ' Remove user-defined work features info- a row when "Ignore the Work Features (Plane, Axis and Point)" checkbox is checked
    Private Sub checkIgnWkFeatures_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles checkIgnWkFeatures.CheckStateChanged
        SetCurrentFeaturesCountTypesInfo()

        Dim tmpLstItem As System.Windows.Forms.ListViewItem
        If checkIgnWkFeatures.CheckState = 0 Then
            If Not IsExistingListItem(sWkFeaturesName) Then

                tmpLstItem = ListViewInfo.Items.Add("")

                tmpLstItem.Text = sWkFeaturesName

                If tmpLstItem.SubItems.Count > 1 Then
                    tmpLstItem.SubItems(1).Text = CStr(lUserWkFeaturesNum)
                Else
                    tmpLstItem.SubItems.Add(New System.Windows.Forms.ListViewItem.ListViewSubItem(Nothing, CStr(lUserWkFeaturesNum)))
                End If
            End If
        ElseIf checkIgnWkFeatures.CheckState = 1 Then
            Call RemoveListItem(sWkFeaturesName)
        End If
    End Sub

    ' Update the ListView content when checking or canceling "Ignore the 2D and 3D Sketches" checkbox
    ' Add 2d&3d sketches info- a row when "Ignore the 2D and 3D Sketches" checkbox is canceled
    ' Remove 2d&3d sketches info- a row when "Ignore the 2D and 3D Sketches" checkbox is checked
    Private Sub checkIgnSks_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles checkIgnSks.CheckStateChanged
        Dim tmpLstItem As System.Windows.Forms.ListViewItem
        If checkIgnSks.CheckState = 0 Then
            If Not IsExistingListItem(sSksName) Then

                tmpLstItem = ListViewInfo.Items.Add("")

                tmpLstItem.Text = sSksName

                If tmpLstItem.SubItems.Count > 1 Then
                    tmpLstItem.SubItems(1).Text = CStr(lSksNum)
                Else
                    tmpLstItem.SubItems.Add(New System.Windows.Forms.ListViewItem.ListViewSubItem(Nothing, CStr(lSksNum)))
                End If
            End If
        ElseIf checkIgnSks.CheckState = 1 Then
            Call RemoveListItem(sSksName)
        End If
    End Sub

    ' This sub is used to remove the ListItem- a row of ListView
    Private Sub RemoveListItem(ByVal lstItemText As String)

        Dim l As Integer
        For l = 0 To ListViewInfo.Items.Count - 1

            If StrComp(ListViewInfo.Items.Item(l).Text, lstItemText, CompareMethod.Text) = 0 Then
                Call ListViewInfo.Items.RemoveAt(l) : Exit For
            End If
        Next
    End Sub

    ' Judge the ListItem- a row whether has been contained by ListView
    Private Function IsExistingListItem(ByVal lstItemText As String) As Boolean
        IsExistingListItem = False

        Dim l As Integer
        For l = 0 To ListViewInfo.Items.Count - 1

            If StrComp(ListViewInfo.Items.Item(l).Text, lstItemText, CompareMethod.Text) = 0 Then
                IsExistingListItem = True : Exit For
            End If
        Next
    End Function

    ' Resetting the appearance of dialog box and list numbers for each feature types when clicking "NumInfo" command
    Private Sub cmdNumInfo_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdNumInfo.Click
        checkIgnSuppressFeatures.Visible = True
        checkIgnWkFeatures.Visible = True
        checkIgnSks.Visible = True
        Me.ListViewInfo.Sort()
        Me.ListViewInfo.AllowColumnReorder = True
        ListFeatureNameNumInfo()
    End Sub

    Private Sub cmdOK_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdOK.Click
        Call Me.Close()
    End Sub

    ' Resetting the appearance of dialog box and list rebuild time info for each feature when clicking "Rebuild" command
    Private Sub cmdRebuild_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdRebuild.Click
        checkIgnSuppressFeatures.Visible = False
        checkIgnWkFeatures.Visible = False
        checkIgnSks.Visible = False
        'Dim FrmFeatureStatistics As New FrmFeatureStatistics

        Me.ListViewInfo.Sorting = System.Windows.Forms.SortOrder.Ascending
        Me.ListViewInfo.AllowColumnReorder = False
        ListFeatureOrderRebuilTimeInfo()
    End Sub

    ' New a notepad and paste modle info when clicking "Save" command
    ' Notepad content can like this:
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    '    File Name:             AttrBox.ipt
    '    Amount of Features:        6
    '    Types of Features:         4
    '    Num of Solids:             1
    '    Num of Surfaces:           1
    '
    '    Feature Name               Num
    '    2D & 3D Sketches           3
    '    ExtrudeFeature             2
    '    Work Geometries            4
    '
    '    Ignore the Suppressed Features                     False
    '    Ignore the Work Features (Plane, Axis and Point)   False
    '    Ignore the 2D and 3D Sketches                      False
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

    ' Or like this:
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    '    File Name:             AttrBox.ipt
    '    Total Rebuild Time(s):     0.56
    '    Amount of Features:        6
    '    Types of Features:         4
    '    Num of Solids:             1
    '    Num of Surfaces:           1
    '
    '    Feature Order       Time(s)        Time %
    '    Sketch1                0             0
    '    Extrusion1             0.34        61.11
    '    Work Point1            0.02        2.78
    '    Work Axis1             0             0
    '    Work Plane1            0             0
    '    Sketch2                0.02        2.78
    '    ExtrusionSrf1          0.17        30.56
    '    3D Sketch1             0.02        2.78
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    Private Sub cmdSave_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdSave.Click

        ' Define string variable "tmpCopyStr" to storage modle info
        Dim tmpCopyStr As String
        Dim l, m As Integer : tmpCopyStr = ""

        ' Record summary info
        tmpCopyStr = tmpCopyStr & lblFileName.Text & vbTab & vbTab & lblFileNameText.Text & vbCrLf ' File Name
        If lblRebuildTime.Visible Then
            tmpCopyStr = tmpCopyStr & lblRebuildTime.Text & vbTab & lblTime.Text & vbCrLf ' Total Rebuild Time
        End If
        tmpCopyStr = tmpCopyStr & lblFeaturesNum.Text & vbTab & lblFeatureNumsCount.Text & vbCrLf ' Amount of Features
        tmpCopyStr = tmpCopyStr & lblFeatureTypes.Text & vbTab & vbTab & lblFeatureTypesCount.Text & vbCrLf ' Types of Features
        tmpCopyStr = tmpCopyStr & lblSolidsCount.Text & vbTab & vbTab & lblSolidsNumCount.Text & vbCrLf ' Num of Solids
        tmpCopyStr = tmpCopyStr & lblSurfNums.Text & vbTab & vbTab & lblSurfNumsCount.Text & vbCrLf & vbCrLf ' Num of Surfaces

        ' Record detail info: features number or rebuild time within ListView
        For l = 1 To ListViewInfo.Columns.Count - 1
            tmpCopyStr = tmpCopyStr & ListViewInfo.Columns.Item(l).Text & vbTab & vbTab
        Next

        tmpCopyStr = tmpCopyStr & ListViewInfo.Columns.Item(ListViewInfo.Columns.Count - 1).Text & vbCrLf

        Dim lastTwoChars As Integer
        For l = 0 To ListViewInfo.Items.Count - 1

            tmpCopyStr = tmpCopyStr & ListViewInfo.Items.Item(l).Text & vbTab

            If Len(ListViewInfo.Items.Item(l).Text) < 9 Then
                tmpCopyStr = tmpCopyStr & vbTab & vbTab

            ElseIf Len(ListViewInfo.Items.Item(l).Text) = 9 Then
                On Error Resume Next

                lastTwoChars = CInt(VB.Right(ListViewInfo.Items.Item(l).Text, 2))
                If Err.Number <> 0 Then
                    tmpCopyStr = tmpCopyStr & vbTab
                Else : On Error GoTo 0
                End If

            ElseIf Len(ListViewInfo.Items.Item(l).Text) < 20 Then
                tmpCopyStr = tmpCopyStr & vbTab
            End If


            For m = 0 To ListViewInfo.Items.Item(l).SubItems.Count - 1

                tmpCopyStr = tmpCopyStr & ListViewInfo.Items.Item(l).SubItems(m).Text

                If m < ListViewInfo.Items.Item(l).SubItems.Count Then
                    tmpCopyStr = tmpCopyStr & vbTab & vbTab
                Else : tmpCopyStr = tmpCopyStr & vbCrLf
                End If
            Next
        Next

        ' Record the status info of checkbox
        If checkIgnSuppressFeatures.Visible And checkIgnWkFeatures.Visible And checkIgnSks.Visible Then
            tmpCopyStr = tmpCopyStr & vbCrLf
            tmpCopyStr = tmpCopyStr & checkIgnSuppressFeatures.Text & vbTab & vbTab & vbTab & CStr(checkIgnSuppressFeatures.CheckState = 1) & vbCrLf
            tmpCopyStr = tmpCopyStr & checkIgnWkFeatures.Text & vbTab & CStr(checkIgnWkFeatures.CheckState = 1) & vbCrLf
            tmpCopyStr = tmpCopyStr & checkIgnSks.Text & vbTab & vbTab & vbTab & CStr(checkIgnSks.CheckState = 1) & vbCrLf
        End If

        ' Puts above text string on the clipboard
        My.Computer.Clipboard.Clear()
        Call My.Computer.Clipboard.SetText(tmpCopyStr)

        ' New a notepad
        Call Shell("notepad", AppWinStyle.NormalFocus)

        ' Get the notepad
        Dim hwnd As Integer
        hwnd = FindWindow(vbNullString, "Untitled - Notepad")
        If hwnd = 0 Then hwnd = FindWindow(vbNullString, "无标题 - 记事本")

        ' Write the content of clipboard into notepad
        Call SendMessage(FindWindowEx(hwnd, 0, "Edit", vbNullString), WM_PASTE, 0, 0)

    End Sub



    'Private Sub ListViewInfo_MouseUp(ByVal eventSender As System.Object, ByVal eventArgs As System.Windows.Forms.MouseEventArgs) Handles ListViewInfo.MouseUp
    '    Dim Button As Short = eventArgs.Button \ &H100000
    '    Dim Shift As Short = System.Windows.Forms.Control.ModifierKeys \ &H10000
    '    Dim x As Single = VB6.PixelsToTwipsX(eventArgs.X)
    '    Dim y As Single = VB6.PixelsToTwipsY(eventArgs.Y)
    '    If Button = VB6.MouseButtonConstants.RightButton Then
    '        Call PopupMenu(menuEdit, vbPopupMenuLeftAlign)
    '    End If
    'End Sub

    ' Implement "Copy" command in the right-click context menu in the ViewList window
    Public Sub menuCopy_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles menuCopy.Click
        My.Computer.Clipboard.Clear()
        Dim tmpCopyStr As String
        Dim l As Integer : tmpCopyStr = ""

        For l = 1 To ListViewInfo.Items.Count
            If ListViewInfo.Items.Item(l).Selected Then
                tmpCopyStr = tmpCopyStr & ListViewInfo.Items.Item(l).Text & vbTab & ListViewInfo.Items.Item(l).SubItems(1).Text & vbCrLf
            End If
        Next

        Call My.Computer.Clipboard.SetText(tmpCopyStr)
    End Sub

    ' Implement "SelectAll" command in the right-click context menu in the ViewList window
    Public Sub menuSelectAll_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles menuSelectAll.Click
        Dim l As Integer
        For l = 1 To ListViewInfo.Items.Count
            ListViewInfo.Items.Item(l).Selected = True
        Next
    End Sub
End Class