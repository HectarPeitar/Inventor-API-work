Option Strict Off
Option Explicit On
Imports System.Runtime.InteropServices
Imports System.Windows.Forms

Friend Class frmInteraction
    Inherits System.Windows.Forms.Form
    Private oInventorApp As Inventor.Application

    Private WithEvents oInteraction As Inventor.InteractionEvents
    Private WithEvents oSelectEvents As Inventor.SelectEvents
    Private WithEvents oMouseEvents As Inventor.MouseEvents
    Private WithEvents oKeyboardEvents As Inventor.KeyboardEvents
    Private WithEvents oTriadEvents As Inventor.TriadEvents

    Private bClearingFilter As Boolean

    Private Sub chkDisableInteraction_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkDisableInteraction.CheckStateChanged
        ' Toggle the InteractionDisabled property on/off.
        If chkDisableInteraction.CheckState = System.Windows.Forms.CheckState.Checked Then
            oInteraction.InteractionDisabled = True
        Else
            oInteraction.InteractionDisabled = False
        End If
    End Sub

    Private Sub chkEnableKeyboard_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkEnableKeyboard.CheckStateChanged
        ' Attach/detach to the keyboard events.
        If chkEnableKeyboard.CheckState = System.Windows.Forms.CheckState.Checked Then
            oKeyboardEvents = oInteraction.KeyboardEvents
        Else
            oKeyboardEvents = Nothing
        End If
    End Sub

    Private Sub chkEnableMouse_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkEnableMouse.CheckStateChanged
        ' Attach/detach to the mouse events.
        If chkEnableMouse.CheckState = System.Windows.Forms.CheckState.Checked Then
            oMouseEvents = oInteraction.MouseEvents
            If chkPointInference.CheckState = System.Windows.Forms.CheckState.Checked Then
                oMouseEvents.PointInferenceEnabled = True
            Else
                oMouseEvents.PointInferenceEnabled = False
            End If

            If chkEnableMouseMove.CheckState = System.Windows.Forms.CheckState.Checked Then
                oMouseEvents.MouseMoveEnabled = True
            Else
                oMouseEvents.MouseMoveEnabled = False
            End If
        Else
            oMouseEvents = Nothing
        End If
    End Sub

    Private Sub chkEnableMouseMove_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkEnableMouseMove.CheckStateChanged
        If Not oMouseEvents Is Nothing Then
            ' Toggle the MouseMoveEnabled property on/off.
            If chkEnableMouseMove.CheckState = System.Windows.Forms.CheckState.Checked Then
                oMouseEvents.MouseMoveEnabled = True
            Else
                oMouseEvents.MouseMoveEnabled = False
            End If
        End If
    End Sub

    Private Sub chkEnableSelection_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkEnableSelection.CheckStateChanged
        ' Attach/detach to the selection events.
        If chkEnableSelection.CheckState = System.Windows.Forms.CheckState.Checked Then
            oSelectEvents = oInteraction.SelectEvents

            ' Enable getting mouse move events within the selection.
            If chkSelectMouseMove.CheckState = System.Windows.Forms.CheckState.Checked Then
                oSelectEvents.MouseMoveEnabled = True
            Else
                oSelectEvents.MouseMoveEnabled = False
            End If
        Else
            oSelectEvents = Nothing
        End If
    End Sub

    Private Sub chkEnableTriad_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkEnableTriad.CheckStateChanged
        ' Attach/detach to the Triad events.
        If chkEnableTriad.CheckState = System.Windows.Forms.CheckState.Checked Then
            oTriadEvents = oInteraction.TriadEvents
        Else
            oTriadEvents = Nothing
        End If
    End Sub

    Private Sub chkMoveTriadOnly_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkMoveTriadOnly.CheckStateChanged
        ' Toggle the MoveTriadOnly property on/off.
        If chkMoveTriadOnly.CheckState = System.Windows.Forms.CheckState.Checked Then
            oTriadEvents.MoveTriadOnly = True
        Else
            oTriadEvents.MoveTriadOnly = False
        End If
    End Sub

    Private Sub chkMoveTriadOnlyEnabled_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkMoveTriadOnlyEnabled.CheckStateChanged
        ' Toggle the MoveTriadOnlyEnabled property on/off.
        If chkMoveTriadOnlyEnabled.CheckState = System.Windows.Forms.CheckState.Checked Then
            oTriadEvents.MoveTriadOnlyEnabled = True
        Else
            oTriadEvents.MoveTriadOnlyEnabled = False
        End If
    End Sub

    Private Sub chkOnMouseMove_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkOnMouseMove.CheckStateChanged
        If oInventorApp Is Nothing Then
            frmInteraction_Load(eventSender, eventArgs)
        End If

        If chkOnMouseMove.CheckState = System.Windows.Forms.CheckState.Checked Then
            chkEnableMouseMove.Enabled = True
        Else
            chkEnableMouseMove.Enabled = False
        End If
    End Sub


    Private Sub chkOriginSegment_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkOriginSegment.CheckStateChanged
        Call SetDOF()
    End Sub

    Private Sub chkPointInference_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkPointInference.CheckStateChanged
        If Not oMouseEvents Is Nothing Then
            ' Toggle the PointInferenceEnabled property on/off.
            If chkPointInference.CheckState = System.Windows.Forms.CheckState.Checked Then
                oMouseEvents.PointInferenceEnabled = True
            Else
                oMouseEvents.PointInferenceEnabled = False
            End If
        End If
    End Sub

    Private Sub chkRepeat_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkRepeat.CheckStateChanged
        ' Toggle the Repeat property on/off.
        If chkRepeat.CheckState = System.Windows.Forms.CheckState.Checked Then
            oTriadEvents.Repeat = True
        Else
            oTriadEvents.Repeat = False
        End If
    End Sub

    Private Sub chkSelection_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkSelection.CheckStateChanged
        ' Toggle the Selection enabled property on/off.

        If oSelectEvents Is Nothing Then
            If chkSelection.CheckState = System.Windows.Forms.CheckState.Checked Then
                MsgBox("Please enable Selection events first")
                chkSelection.CheckState = System.Windows.Forms.CheckState.Unchecked
            End If
            Exit Sub
        End If
        If chkSelection.CheckState = System.Windows.Forms.CheckState.Checked Then
            If chkTriad.CheckState = System.Windows.Forms.CheckState.Checked Then
                chkTriad.CheckState = System.Windows.Forms.CheckState.Unchecked
            End If
            oSelectEvents.Enabled = True
        Else
            oSelectEvents.Enabled = False
        End If
    End Sub

    Private Sub chkSelectMouseMove_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkSelectMouseMove.CheckStateChanged
        ' Toggle the MouseMoveEnabled property on/off.
        If chkSelectMouseMove.CheckState = System.Windows.Forms.CheckState.Checked Then
            oSelectEvents.MouseMoveEnabled = True
        Else
            oSelectEvents.MouseMoveEnabled = False
        End If
    End Sub

    Private Sub chkSingleSelect_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkSingleSelect.CheckStateChanged
        ' Toggle the SingleSelectEnabled property on/off.
        If chkSingleSelect.CheckState = System.Windows.Forms.CheckState.Checked Then
            oSelectEvents.SingleSelectEnabled = True
        Else
            oSelectEvents.SingleSelectEnabled = False
        End If
    End Sub

    Private Sub chkTriad_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkTriad.CheckStateChanged
        ' Toggle the Triad enabled property on/off.
        If oTriadEvents Is Nothing Then
            If chkTriad.CheckState = System.Windows.Forms.CheckState.Checked Then
                MsgBox("Please enable Triad events first")
                chkTriad.CheckState = System.Windows.Forms.CheckState.Unchecked
            End If
            Exit Sub
        End If
        If chkTriad.CheckState = System.Windows.Forms.CheckState.Checked Then
            If chkSelection.CheckState = System.Windows.Forms.CheckState.Checked Then
                chkSelection.CheckState = System.Windows.Forms.CheckState.Unchecked
            End If
            oTriadEvents.Enabled = True
        Else
            oTriadEvents.Enabled = False
        End If
    End Sub

    Private Sub chkXAxisRotationSegment_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkXAxisRotationSegment.CheckStateChanged
        Call SetDOF()
    End Sub

    Private Sub chkXAxisTranslationSegment_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkXAxisTranslationSegment.CheckStateChanged
        Call SetDOF()
    End Sub

    Private Sub chkXYPlaneTranslationSegment_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkXYPlaneTranslationSegment.CheckStateChanged
        Call SetDOF()
    End Sub

    Private Sub chkXZPlaneTranslationSegment_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkXZPlaneTranslationSegment.CheckStateChanged
        Call SetDOF()
    End Sub

    Private Sub chkYAxisRotationSegment_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkYAxisRotationSegment.CheckStateChanged
        Call SetDOF()
    End Sub

    Private Sub chkYAxisTranslationSegment_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkYAxisTranslationSegment.CheckStateChanged
        Call SetDOF()
    End Sub

    Private Sub chkYZPlaneTranslationSegment_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkYZPlaneTranslationSegment.CheckStateChanged
        Call SetDOF()
    End Sub

    Private Sub chkZAxisRotationSegment_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkZAxisRotationSegment.CheckStateChanged
        Call SetDOF()
    End Sub

    Private Sub chkZAxisTranslationSegment_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkZAxisTranslationSegment.CheckStateChanged
        Call SetDOF()
    End Sub

    Private Sub cmdCancel_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdCancel.Click
        Me.Close()
    End Sub

    Private Sub cmdClear_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdClear.Click
        ' Clear the results text box.
        txtResults.Text = ""
    End Sub

    Private Sub frmInteraction_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        ' Access the Inventor application object
        On Error Resume Next
        oInventorApp = Win32.GetActiveObject("Inventor.Application")

        If Err.Number Then
            Err.Clear()
            oInventorApp = CreateObject("Inventor.Application")
        End If
        On Error GoTo 0

        oInventorApp.Visible = True

        ' Make sure a document is open
        Dim i As Integer
        If oInventorApp.ActiveDocument Is Nothing Then
            MsgBox("Please open a document in Inventor to run this tool.")
            Me.Close()
            Exit Sub
        Else
            ' Initialize some arrays to use in displaying enum informatin.
            LoadFilterListEnums()
            LoadKeyConstants()

            ' Populate the filter list.
            For i = 0 To Filters.Length - 1
                lstFilters.Items.Add(Filters(i).Name)
            Next

            ' Create an InteractionEvents object.
            oInteraction = oInventorApp.CommandManager.CreateInteractionEvents

            ' connect to the SelectEvents object,
            ' because this is the default on the dialog.
            oSelectEvents = oInteraction.SelectEvents

            'Set the StatusBarText property from the text in the dialog.
            oInteraction.StatusBarText = txtStatusBar.Text

            fmSelection.Visible = True

            chkSelection.CheckState = System.Windows.Forms.CheckState.Checked

            Call SetWindowPos(Me.Handle.ToInt32, HWND_TOPMOST, 0, 0, 0, 0, FLAGS)

        End If
    End Sub
    'Private Sub frmInteraction_Load() '(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load

    '    ' Access the Inventor application object
    '    On Error Resume Next
    '    oInventorApp = GetObject(, "Inventor.Application")

    '    If Err.Number Then
    '        Err.Clear()
    '        oInventorApp = CreateObject("Inventor.Application")
    '    End If
    '    On Error GoTo 0

    '    oInventorApp.Visible = True

    '    ' Make sure a document is open
    '    Dim i As Integer
    '    If oInventorApp.ActiveDocument Is Nothing Then
    '        MsgBox("Please open a document in Inventor to run this tool.")
    '        Me.Close()
    '        Exit Sub
    '    Else
    '        ' Initialize some arrays to use in displaying enum informatin.
    '        LoadAllSelectEnums()
    '        LoadKeyConstants()

    '        ' Populate the filter list.
    '        For i = 1 To UBound(Filters)
    '            lstFilters.Items.Add(Filters(i).Name)
    '        Next

    '        ' Create an InteractionEvents object.
    '        oInteraction = oInventorApp.CommandManager.CreateInteractionEvents

    '        ' connect to the SelectEvents object,
    '        ' because this is the default on the dialog.
    '        oSelectEvents = oInteraction.SelectEvents

    '        'Set the StatusBarText property from the text in the dialog.
    '        oInteraction.StatusBarText = txtStatusBar.Text

    '        fmSelection.Visible = True

    '        chkSelection.CheckState = System.Windows.Forms.CheckState.Checked

    '        Call SetWindowPos(Me.Handle.ToInt32, HWND_TOPMOST, 0, 0, 0, 0, FLAGS)

    '    End If
    'End Sub
    Private Sub frmInteraction_FormClosed(ByVal eventSender As System.Object, ByVal eventArgs As System.Windows.Forms.FormClosedEventArgs) Handles Me.FormClosed
        oInteraction = Nothing
        oSelectEvents = Nothing
        oMouseEvents = Nothing
        oKeyboardEvents = Nothing
    End Sub

    Private Sub oInteraction_OnActivate() Handles oInteraction.OnActivate
        PrintResults("OnActivate")
    End Sub

    Private Sub oInteraction_OnResume() Handles oInteraction.OnResume
        PrintResults("OnResume")
    End Sub

    Private Sub oInteraction_OnSuspend() Handles oInteraction.OnSuspend
        txtResults.Text = "OnSuspend"
    End Sub

    Private Sub oInteraction_OnTerminate() Handles oInteraction.OnTerminate
        btnStartStop.Text = "Start Interaction"
        PrintResults("OnTerminate")
    End Sub

    '******************************************************
    ' Keyboard related methods.
    '******************************************************

    Private Sub oKeyboardEvents_OnKeyDown(ByVal Key As Integer, ByVal ShiftKeys As Inventor.ShiftStateEnum) Handles oKeyboardEvents.OnKeyDown
        ' If the key down box is checked, display the event information.
        Dim strStatus As String
        If chkOnKeyDown.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnKeyDown"
            strStatus = strStatus & vbCrLf & "  Key: " & KeyString(Key)
            strStatus = strStatus & vbCrLf & "  Shift: " & ShiftString(ShiftKeys)

            PrintResults(strStatus)
        End If
    End Sub

    Private Sub oKeyboardEvents_OnKeyPress(ByVal KeyASCII As Integer) Handles oKeyboardEvents.OnKeyPress
        ' If the key press box is checked, display the event information.
        Dim strStatus As String
        If chkOnKeyPress.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = txtResults.Text & vbCrLf & "OnKeyPress"
            strStatus = strStatus & vbCrLf & "  Key: " & KeyASCII & " (" & Chr(KeyASCII) & ")"

            PrintResults(strStatus)
        End If
    End Sub

    Private Sub oKeyboardEvents_OnKeyUp(ByVal Key As Integer, ByVal ShiftKeys As Inventor.ShiftStateEnum) Handles oKeyboardEvents.OnKeyUp
        ' If the key up box is checked, display the event information.
        Dim strStatus As String
        If chkOnKeyUp.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnKeyUp"
            strStatus = strStatus & vbCrLf & "  Key: " & KeyString(Key)
            strStatus = strStatus & vbCrLf & "  Shift: " & ShiftString(ShiftKeys)

            PrintResults(strStatus)
        End If
    End Sub


    '******************************************************
    ' Mouse related methods.
    '******************************************************

    Private Sub oMouseEvents_OnMouseClick(ByVal Button As Inventor.MouseButtonEnum, ByVal ShiftKeys As Inventor.ShiftStateEnum, ByVal ModelPosition As Inventor.Point, ByVal ViewPosition As Inventor.Point2d, ByVal View As Inventor.View) Handles oMouseEvents.OnMouseClick
        ' If the mouse click box is checked, display the event information.
        Dim strStatus As String
        Dim oPointInference As Inventor.PointInference
        Dim strInferenceType As String = ""
        If chkOnMouseClick.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnMouseClick"

            strStatus = strStatus & vbCrLf & "  Button:" & ButtonString(Button)
            strStatus = strStatus & vbCrLf & "  Shift:" & ShiftString(ShiftKeys)

            strStatus = strStatus & vbCrLf & "  ModelPosition: " & PointString(ModelPosition)
            strStatus = strStatus & vbCrLf & "  ViewPosition: " & Point2dString(ViewPosition)
            strStatus = strStatus & vbCrLf & "  View: " & View.Caption

            PrintResults(strStatus)

            If chkPointInference.CheckState = System.Windows.Forms.CheckState.Checked Then
                strStatus = ""
                For Each oPointInference In oMouseEvents.PointInferences
                    Select Case oPointInference.InferenceType
                        Case Inventor.PointInferenceEnum.kPtAtIntersection
                            strInferenceType = "Intersection"
                        Case Inventor.PointInferenceEnum.kPtAtMidPoint
                            strInferenceType = "MidPoint"
                        Case Inventor.PointInferenceEnum.kPtOnCurve
                            strInferenceType = "On Curve"
                        Case Inventor.PointInferenceEnum.kPtOnPt
                            strInferenceType = "On Point"
                    End Select
                    strStatus = "Point inference in OnMouseClick"
                    strStatus = strStatus & vbCrLf & "  Inference Type: " & strInferenceType
                Next oPointInference

                PrintResults(strStatus)
            End If
        End If
    End Sub

    Private Sub oMouseEvents_OnMouseDoubleClick(ByVal Button As Inventor.MouseButtonEnum, ByVal ShiftKeys As Inventor.ShiftStateEnum, ByVal ModelPosition As Inventor.Point, ByVal ViewPosition As Inventor.Point2d, ByVal View As Inventor.View) Handles oMouseEvents.OnMouseDoubleClick
        ' If the mouse double click box is checked, display the event information.
        Dim strStatus As String
        If chkOnMouseDoubleClick.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnMouseDoubleClick"

            strStatus = strStatus & vbCrLf & "  Button:" & ButtonString(Button)
            strStatus = strStatus & vbCrLf & "  Shift:" & ShiftString(ShiftKeys)

            strStatus = strStatus & vbCrLf & "  ModelPosition: " & PointString(ModelPosition)
            strStatus = strStatus & vbCrLf & "  ViewPosition: " & Point2dString(ViewPosition)
            strStatus = strStatus & vbCrLf & "  View: " & View.Caption

            PrintResults(strStatus)
        End If
    End Sub

    Private Sub oMouseEvents_OnMouseDown(ByVal Button As Inventor.MouseButtonEnum, ByVal ShiftKeys As Inventor.ShiftStateEnum, ByVal ModelPosition As Inventor.Point, ByVal ViewPosition As Inventor.Point2d, ByVal View As Inventor.View) Handles oMouseEvents.OnMouseDown
        ' If the mouse down box is checked, display the event information.
        Dim strStatus As String
        If chkOnMouseDown.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnMouseDown"

            strStatus = strStatus & vbCrLf & "  Button:" & ButtonString(Button)
            strStatus = strStatus & vbCrLf & "  Shift:" & ShiftString(ShiftKeys)

            strStatus = strStatus & vbCrLf & "  ModelPosition: " & PointString(ModelPosition)
            strStatus = strStatus & vbCrLf & "  ViewPosition: " & Point2dString(ViewPosition)
            strStatus = strStatus & vbCrLf & "  View: " & View.Caption

            PrintResults(strStatus)
        End If
    End Sub

    Private Sub oMouseEvents_OnMouseLeave(ByVal Button As Inventor.MouseButtonEnum, ByVal ShiftKeys As Inventor.ShiftStateEnum, ByVal View As Inventor.View) Handles oMouseEvents.OnMouseLeave
        ' If the mouse leave box is checked, display the event information.
        Dim strStatus As String
        If chkOnMouseLeave.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnMouseLeave"

            strStatus = strStatus & vbCrLf & "  Button:" & ButtonString(Button)
            strStatus = strStatus & vbCrLf & "  Shift:" & ShiftString(ShiftKeys)
            strStatus = strStatus & vbCrLf & "  View: " & View.Caption

            PrintResults(strStatus)
        End If
    End Sub

    Private Sub oMouseEvents_OnMouseMove(ByVal Button As Inventor.MouseButtonEnum, ByVal ShiftKeys As Inventor.ShiftStateEnum, ByVal ModelPosition As Inventor.Point, ByVal ViewPosition As Inventor.Point2d, ByVal View As Inventor.View) Handles oMouseEvents.OnMouseMove
        ' If the mouse move box is checked, display the event information.
        Dim strStatus As String
        Dim oPointInference As Inventor.PointInference
        Dim strInferenceType As String = ""
        If chkOnMouseMove.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnMouseMove"

            strStatus = strStatus & vbCrLf & "  Button:" & ButtonString(Button)
            strStatus = strStatus & vbCrLf & "  Shift:" & ShiftString(ShiftKeys)

            strStatus = strStatus & vbCrLf & "  ModelPosition: " & PointString(ModelPosition)
            strStatus = strStatus & vbCrLf & "  ViewPosition: " & Point2dString(ViewPosition)
            strStatus = strStatus & vbCrLf & "  View: " & View.Caption

            PrintResults(strStatus)

            If chkPointInference.CheckState = System.Windows.Forms.CheckState.Checked Then
                strStatus = ""
                For Each oPointInference In oMouseEvents.PointInferences
                    Select Case oPointInference.InferenceType
                        Case Inventor.PointInferenceEnum.kPtAtIntersection
                            strInferenceType = "Intersection"
                        Case Inventor.PointInferenceEnum.kPtAtMidPoint
                            strInferenceType = "MidPoint"
                        Case Inventor.PointInferenceEnum.kPtOnCurve
                            strInferenceType = "On Curve"
                        Case Inventor.PointInferenceEnum.kPtOnPt
                            strInferenceType = "On Point"
                    End Select
                    strStatus = "Point inference in OnMouseMove"
                    strStatus = strStatus & vbCrLf & "  Inference Type: " & strInferenceType
                Next oPointInference

                PrintResults(strStatus)
            End If
        End If
    End Sub

    Private Sub oMouseEvents_OnMouseUp(ByVal Button As Inventor.MouseButtonEnum, ByVal ShiftKeys As Inventor.ShiftStateEnum, ByVal ModelPosition As Inventor.Point, ByVal ViewPosition As Inventor.Point2d, ByVal View As Inventor.View) Handles oMouseEvents.OnMouseUp
        ' If the mouse up box is checked, display the event information.
        Dim strStatus As String
        If chkOnMouseUp.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnMouseUp"

            strStatus = strStatus & vbCrLf & "  Button:" & ButtonString(Button)
            strStatus = strStatus & vbCrLf & "  Shift:" & ShiftString(ShiftKeys)

            strStatus = strStatus & vbCrLf & "  ModelPosition: " & PointString(ModelPosition)
            strStatus = strStatus & vbCrLf & "  ViewPosition: " & Point2dString(ViewPosition)
            strStatus = strStatus & vbCrLf & "  View: " & View.Caption

            PrintResults(strStatus)
        End If
    End Sub



    '******************************************************
    ' Selection related methods.
    '******************************************************
    Private Sub lstFilters_SelectedIndexChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles lstFilters.SelectedIndexChanged
        Dim i As Short
        Dim iTemp As Integer
        If bClearingFilter Then
            bClearingFilter = False
        Else
            ' Check to make sure selection is enabled.
            If chkEnableSelection.CheckState <> System.Windows.Forms.CheckState.Checked Then
                MsgBox("The ""Enable Selection"" box must be checked before setting the filter.")
                bClearingFilter = True
                lstFilters.SelectedIndex = -1
                Exit Sub
            End If

            ' Clear the current filter.
            oSelectEvents.ClearSelectionFilter()

            ' Add each of the items selected in the list box to the filter.
            For i = 0 To lstFilters.Items.Count - 1
                If lstFilters.GetSelected(i) Then
                    iTemp = Filters(i).Value
                    On Error Resume Next
                    oSelectEvents.AddSelectionFilter(iTemp)
                    If Err.Number Then
                        MsgBox("Failed to set the filter to " & Filters(i).Name)
                    End If
                    On Error GoTo 0
                End If
            Next
        End If
    End Sub

    Private Sub oSelectEvents_OnPreSelect(ByRef PreSelectEntity As Object, ByRef DoHighlight As Boolean, ByRef MorePreSelectEntities As Inventor.ObjectCollection, ByVal SelectionDevice As Inventor.SelectionDeviceEnum, ByVal ModelPosition As Inventor.Point, ByVal ViewPosition As Inventor.Point2d, ByVal View As Inventor.View) Handles oSelectEvents.OnPreSelect
        ' If the OnPreSelect box is checked, display the event information.
        Dim strStatus As String
        If chkOnPreSelect.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnPreSelect"

            strStatus = strStatus & vbCrLf & "  Entity Type: " & TypeName(PreSelectEntity)

            If SelectionDevice = Inventor.SelectionDeviceEnum.kGraphicsWindowSelection Then
                strStatus = strStatus & vbCrLf & "  Device: Window"
            ElseIf SelectionDevice = Inventor.SelectionDeviceEnum.kBrowserSelection Then
                strStatus = strStatus & vbCrLf & "  Device: Browser"
            End If

            strStatus = strStatus & vbCrLf & "  ModelPosition: " & PointString(ModelPosition)
            strStatus = strStatus & vbCrLf & "  ViewPosition: " & Point2dString(ViewPosition)
            strStatus = strStatus & vbCrLf & "  View: " & View.Caption

            ' If the do highlight box is checked, return True for the DoHighlight argument.  This will
            ' cause any valid entity to prehighlight.  If the box isn't checked, return False which
            ' will cause then entity to not participate in the selection.
            If chkDoHighlight.CheckState = System.Windows.Forms.CheckState.Checked Then
                DoHighlight = True
            Else
                DoHighlight = False
            End If

            PrintResults(strStatus)
        End If
    End Sub

    Private Sub oSelectEvents_OnPreSelectMouseMove(ByVal PreSelectEntity As Object, ByVal ModelPosition As Inventor.Point, ByVal ViewPosition As Inventor.Point2d, ByVal View As Inventor.View) Handles oSelectEvents.OnPreSelectMouseMove
        ' If the OnPreSelectMouseMove box is checked, display the event information.
        Dim strStatus As String
        If chkOnPreSelectMouseMove.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnPreSelectMouseMove"
            strStatus = strStatus & vbCrLf & "  Entity Type: " & TypeName(PreSelectEntity.Item(1))
            strStatus = strStatus & vbCrLf & "  ModelPosition: " & PointString(ModelPosition)
            strStatus = strStatus & vbCrLf & "  ViewPosition: " & Point2dString(ViewPosition)
            strStatus = strStatus & vbCrLf & "  View: " & View.Caption

            PrintResults(strStatus)
        End If
    End Sub

    Private Sub oSelectEvents_OnSelect(ByVal JustSelectedEntities As Inventor.ObjectsEnumerator, ByVal SelectionDevice As Inventor.SelectionDeviceEnum, ByVal ModelPosition As Inventor.Point, ByVal ViewPosition As Inventor.Point2d, ByVal View As Inventor.View) Handles oSelectEvents.OnSelect
        ' If the OnSelect box is checked, display the event information.
        Dim strStatus As String
        Dim oSelectedEntity As Object
        If chkOnSelect.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnSelect"

            strStatus = strStatus & vbCrLf & "  Selected:"
            For Each oSelectedEntity In JustSelectedEntities
                strStatus = strStatus & vbCrLf & "      " & TypeName(oSelectedEntity)
            Next oSelectedEntity

            If SelectionDevice = Inventor.SelectionDeviceEnum.kGraphicsWindowSelection Then
                strStatus = strStatus & vbCrLf & "  Device: Window"
            ElseIf SelectionDevice = Inventor.SelectionDeviceEnum.kBrowserSelection Then
                strStatus = strStatus & vbCrLf & "  Device: Browser"
            End If

            strStatus = strStatus & vbCrLf & "  ModelPosition: " & PointString(ModelPosition)
            strStatus = strStatus & vbCrLf & "  ViewPosition: " & Point2dString(ViewPosition)
            strStatus = strStatus & vbCrLf & "  View: " & View.Caption

            PrintResults(strStatus)
        End If
    End Sub

    Private Sub oSelectEvents_OnStopPreSelect(ByVal ModelPosition As Inventor.Point, ByVal ViewPosition As Inventor.Point2d, ByVal View As Inventor.View) Handles oSelectEvents.OnStopPreSelect
        ' If the OnStopPreSelect box is checked, display the event information.
        Dim strStatus As String
        If chkOnStopPreSelect.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnStopPreSelect"
            strStatus = strStatus & vbCrLf & "  ModelPosition: " & PointString(ModelPosition)
            strStatus = strStatus & vbCrLf & "  ViewPosition: " & Point2dString(ViewPosition)
            strStatus = strStatus & vbCrLf & "  View: " & View.Caption

            PrintResults(strStatus)
        End If
    End Sub

    Private Sub oSelectEvents_OnUnSelect(ByVal UnSelectedEntities As Inventor.ObjectsEnumerator, ByVal SelectionDevice As Inventor.SelectionDeviceEnum, ByVal ModelPosition As Inventor.Point, ByVal ViewPosition As Inventor.Point2d, ByVal View As Inventor.View) Handles oSelectEvents.OnUnSelect
        ' If the OnUnSelect box is checked, display the event information.
        Dim strStatus As String
        Dim oSelectedEntity As Object
        If chkOnUnselect.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnUnSelect"

            strStatus = strStatus & vbCrLf & "  UnSelected:"
            For Each oSelectedEntity In UnSelectedEntities
                strStatus = strStatus & vbCrLf & "      " & TypeName(oSelectedEntity)
            Next oSelectedEntity

            If SelectionDevice = Inventor.SelectionDeviceEnum.kGraphicsWindowSelection Then
                strStatus = strStatus & vbCrLf & "  Device: Window"
            ElseIf SelectionDevice = Inventor.SelectionDeviceEnum.kBrowserSelection Then
                strStatus = strStatus & vbCrLf & "  Device: Browser"
            End If

            strStatus = strStatus & vbCrLf & "  ModelPosition: " & PointString(ModelPosition)
            strStatus = strStatus & vbCrLf & "  ViewPosition: " & Point2dString(ViewPosition)
            strStatus = strStatus & vbCrLf & "  View: " & View.Caption

            PrintResults(strStatus)
        End If
    End Sub


    '**************************************************************
    ' Utility functions
    '**************************************************************

    ' Create a string that contains the point coordinate information.
    Private Function PointString(ByRef Point As Inventor.Point) As String
        Dim sX As String
        Dim sY As String
        Dim sZ As String
        Dim oUOM As Inventor.UnitsOfMeasure
        If chkDatabaseUnits.CheckState = System.Windows.Forms.CheckState.Checked Then
            ' Get the UnitsOfMeasure object for the document where selection is taking place.
            oUOM = oInteraction.TargetDocument.UnitsOfMeasure

            sX = oUOM.GetStringFromValue(Point.X, Inventor.UnitsTypeEnum.kDefaultDisplayLengthUnits)
            sY = oUOM.GetStringFromValue(Point.Y, Inventor.UnitsTypeEnum.kDefaultDisplayLengthUnits)
            sZ = oUOM.GetStringFromValue(Point.Z, Inventor.UnitsTypeEnum.kDefaultDisplayLengthUnits)
        Else
            sX = Point.X.ToString("F6")
            sY = Point.Y.ToString("F6")
            sZ = Point.Z.ToString("F6")
        End If

        PointString = sX & ", " & sY & ", " & sZ
    End Function

    ' Create a string that contains the 2d point coordinate information.
    Private Function Point2dString(ByRef Point As Inventor.Point2d) As String
        Dim sX As String
        Dim sY As String
        sX = Point.X.ToString("F6")
        sY = Point.Y.ToString("F6")

        Point2dString = sX & ", " & sY
    End Function

    ' Create a string that contains information about the button.
    Private Function ButtonString(ByRef Button As Inventor.MouseButtonEnum) As String
        Select Case Button
            Case Inventor.MouseButtonEnum.kLeftMouseButton
                Return "Left Button"
            Case Inventor.MouseButtonEnum.kMiddleMouseButton
                Return "Middle Button"
            Case Inventor.MouseButtonEnum.kRightMouseButton
                Return "Right Button"
            Case Inventor.MouseButtonEnum.kNoneMouseButton
                Return "No Button"
            Case Else
                Return ""
        End Select
    End Function

    ' Create a string that contains information about the Triad segment.
    Private Function TriadSegmentString(ByRef SelectedTriadSegment As Inventor.TriadSegmentEnum) As String
        Select Case SelectedTriadSegment
            Case Inventor.TriadSegmentEnum.kAllSegments
                Return "All segments"
            Case Inventor.TriadSegmentEnum.kOriginSegment
                Return "Origin"
            Case Inventor.TriadSegmentEnum.kXAxisTranslationSegment
                Return "X Axis Translation"
            Case Inventor.TriadSegmentEnum.kXAxisRotationSegment
                Return "X Axis Rotation"
            Case Inventor.TriadSegmentEnum.kYAxisTranslationSegment
                Return "Y Axis Translation"
            Case Inventor.TriadSegmentEnum.kYAxisRotationSegment
                Return "Y Axis Rotation"
            Case Inventor.TriadSegmentEnum.kZAxisTranslationSegment
                Return "Z Axis Translation"
            Case Inventor.TriadSegmentEnum.kZAxisRotationSegment
                Return "Z Axis Rotation"
            Case Inventor.TriadSegmentEnum.kXYPlaneTranslationSegment
                Return "XY Plane Rotation"
            Case Inventor.TriadSegmentEnum.kXZPlaneTranslationSegment
                Return "XZ Plane Rotation"
            Case Inventor.TriadSegmentEnum.kYZPlaneTranslationSegment
                Return "YZ Plane Rotation"
            Case Else
                Return ""
        End Select
    End Function

    ' Create a string that contains information about which keys are pressed.
    Private Function ShiftString(ByRef ShiftKeys As Inventor.ShiftStateEnum) As String
        Select Case ShiftKeys
            Case Inventor.ShiftStateEnum.kShiftStateAlt
                Return "Alt Key"
            Case Inventor.ShiftStateEnum.kShiftStateCtrl
                Return "Control Key"
            Case Inventor.ShiftStateEnum.kShiftStateCtrlAlt
                Return "Control Alt Keys"
            Case Inventor.ShiftStateEnum.kShiftStateNone
                Return "No Additional Keys"
            Case Inventor.ShiftStateEnum.kShiftStateShift
                Return "Shift Key"
            Case Inventor.ShiftStateEnum.kShiftStateShiftAlt
                Return "Shift Alt Keys"
            Case Inventor.ShiftStateEnum.kShiftStateShiftCtrl
                Return "Shift Control Keys"
            Case Inventor.ShiftStateEnum.kShiftStateShiftCtrlAlt
                Return "Shift Controls Alt Keys"
            Case Else
                Return ""
        End Select
    End Function

    ' Create a string that contains information about which key was pressed.
    Private Function KeyString(ByRef Keycode As Integer) As String
        Dim i As Integer
        KeyString = "Uknown Key"
        For i = 1 To UBound(KeyConstants)
            If Keycode = KeyConstants(i).Value Then
                KeyString = KeyConstants(i).Name
                Exit For
            End If
        Next
    End Function

    ' Write information to the results text box.
    Private Sub PrintResults(ByRef Results As String)
        ' Trim down the text in the text box if it's getting close to the max
        ' length the text box can handle.
        If Len(txtResults.Text) > 60000 Then
            Dim iIndex As Integer
            iIndex = Len(txtResults.Text) / 2
            txtResults.Text = Mid(txtResults.Text, InStr(iIndex, txtResults.Text, "-------------------------------------"))
        End If

        ' Increment line counter.
        Static iLineCount As Integer
        iLineCount = iLineCount + 1

        Control.CheckForIllegalCrossThreadCalls = False

        ' Append new string to text box.
        txtResults.SelectionStart = Len(txtResults.Text)
        txtResults.SelectedText = vbCrLf & iLineCount & " -------------------------------------" & vbCrLf & Results

        'txtResults.SelectedText = vbCrLf & Results
    End Sub

    Private Sub oTriadEvents_OnActivate(ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles oTriadEvents.OnActivate
        Dim strStatus As String
        If chkOnActivate.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnActivate (Triad)"
            strStatus = strStatus & vbCrLf

            PrintResults(strStatus)
        End If
    End Sub

    Private Sub oTriadEvents_OnEndMove(ByVal SelectedTriadSegment As Inventor.TriadSegmentEnum, ByVal ShiftKeys As Inventor.ShiftStateEnum, ByVal CoordinateSystem As Inventor.Matrix, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles oTriadEvents.OnEndMove
        Dim strStatus As String
        If chkOnEndMove.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnEndMove (Triad)"
            strStatus = strStatus & vbCrLf & "   Selected Triad: " & TriadSegmentString(SelectedTriadSegment)
            strStatus = strStatus & vbCrLf & "   Shift: " & ShiftString(ShiftKeys)

            PrintResults(strStatus)
        End If
    End Sub

    Private Sub oTriadEvents_OnEndSequence(ByVal Cancelled As Boolean, ByVal CoordinateSystem As Inventor.Matrix, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles oTriadEvents.OnEndSequence
        Dim strStatus As String
        If chkOnEndSequence.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnEndSequence (Triad)"

            If Cancelled = True Then
                strStatus = strStatus & vbCrLf & "   Cancelled:  " & "yes"
            Else
                strStatus = strStatus & vbCrLf & "   Cancelled:  " & "no"
            End If

            PrintResults(strStatus)
        End If
    End Sub

    Private Sub oTriadEvents_OnMove(ByVal SelectedTriadSegment As Inventor.TriadSegmentEnum, ByVal ShiftKeys As Inventor.ShiftStateEnum, ByVal CoordinateSystem As Inventor.Matrix, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles oTriadEvents.OnMove
        Dim strStatus As String
        If chkOnMove.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnMove (Triad)"
            strStatus = strStatus & vbCrLf & "   Selected Triad: " & TriadSegmentString(SelectedTriadSegment)
            strStatus = strStatus & vbCrLf & "   Shift: " & ShiftString(ShiftKeys)

            PrintResults(strStatus)
        End If
    End Sub

    Private Sub oTriadEvents_OnMoveTriadOnlyToggle(ByVal MoveTriadOnly As Boolean, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles oTriadEvents.OnMoveTriadOnlyToggle
        Dim strStatus As String
        If chkOnMoveTriadOnlyToggle.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnMoveTriadOnlyToggle (Triad)"

            If MoveTriadOnly = True Then
                strStatus = strStatus & vbCrLf & "   Move Triad Only:  " & "yes"
            Else
                strStatus = strStatus & vbCrLf & "   Move Triad Only:  " & "no"
            End If

            PrintResults(strStatus)
        End If
    End Sub

    Private Sub oTriadEvents_OnSegmentSelectionChange(ByVal SelectedTriadSegment As Inventor.TriadSegmentEnum, ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles oTriadEvents.OnSegmentSelectionChange
        Dim strStatus As String
        If chkOnSegmentSelectionChange.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnSegmentSelectionChange (Triad)"
            strStatus = strStatus & vbCrLf & "   Selected Triad: " & TriadSegmentString(SelectedTriadSegment)

            PrintResults(strStatus)
        End If
    End Sub

    Private Sub oTriadEvents_OnStartMove(ByVal SelectedTriadSegment As Inventor.TriadSegmentEnum, ByVal ShiftKeys As Inventor.ShiftStateEnum, ByVal CoordinateSystem As Inventor.Matrix, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles oTriadEvents.OnStartMove
        Dim strStatus As String
        If chkOnStartMove.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnStartMove (Triad)"
            strStatus = strStatus & vbCrLf & "   Selected Triad: " & TriadSegmentString(SelectedTriadSegment)
            strStatus = strStatus & vbCrLf & "   Shift: " & ShiftString(ShiftKeys)

            PrintResults(strStatus)
        End If
    End Sub

    Private Sub oTriadEvents_OnStartSequence(ByVal CoordinateSystem As Inventor.Matrix, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles oTriadEvents.OnStartSequence
        Dim strStatus As String
        If chkOnStartSequence.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnStartSequence (Triad)"

            PrintResults(strStatus)
        End If
    End Sub

    Private Sub oTriadEvents_OnTerminate(ByVal Cancelled As Boolean, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles oTriadEvents.OnTerminate
        Dim strStatus As String
        If chkOnTerminate.CheckState = System.Windows.Forms.CheckState.Checked Then
            strStatus = "OnTerminate (Triad)"
            If Cancelled = True Then
                strStatus = strStatus & vbCrLf & "   Cancelled:  " & "yes"
            Else
                strStatus = strStatus & vbCrLf & "   Cancelled:  " & "no"
            End If

            PrintResults(strStatus)
        End If
    End Sub


    ' Update the StatusBarText property if the contents of the text box changes.
    Private Sub txtStatusBar_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtStatusBar.TextChanged
        If Not (oInteraction Is Nothing) Then
            oInteraction.StatusBarText = txtStatusBar.Text
        End If
    End Sub


    Private Sub SetDOF()
        oTriadEvents.DegreesOfFreedom = 0

        If Me.chkOriginSegment.CheckState = System.Windows.Forms.CheckState.Checked Then
            oTriadEvents.DegreesOfFreedom = oTriadEvents.DegreesOfFreedom + Inventor.TriadSegmentEnum.kOriginSegment
        End If

        If Me.chkXAxisRotationSegment.CheckState = System.Windows.Forms.CheckState.Checked Then
            oTriadEvents.DegreesOfFreedom = oTriadEvents.DegreesOfFreedom + Inventor.TriadSegmentEnum.kXAxisRotationSegment
        End If

        If Me.chkXAxisTranslationSegment.CheckState = System.Windows.Forms.CheckState.Checked Then
            oTriadEvents.DegreesOfFreedom = oTriadEvents.DegreesOfFreedom + Inventor.TriadSegmentEnum.kXAxisTranslationSegment
        End If

        If Me.chkXYPlaneTranslationSegment.CheckState = System.Windows.Forms.CheckState.Checked Then
            oTriadEvents.DegreesOfFreedom = oTriadEvents.DegreesOfFreedom + Inventor.TriadSegmentEnum.kXYPlaneTranslationSegment
        End If

        If Me.chkXZPlaneTranslationSegment.CheckState = System.Windows.Forms.CheckState.Checked Then
            oTriadEvents.DegreesOfFreedom = oTriadEvents.DegreesOfFreedom + Inventor.TriadSegmentEnum.kXZPlaneTranslationSegment
        End If

        If Me.chkYAxisRotationSegment.CheckState = System.Windows.Forms.CheckState.Checked Then
            oTriadEvents.DegreesOfFreedom = oTriadEvents.DegreesOfFreedom + Inventor.TriadSegmentEnum.kYAxisRotationSegment
        End If

        If Me.chkYAxisTranslationSegment.CheckState = System.Windows.Forms.CheckState.Checked Then
            oTriadEvents.DegreesOfFreedom = oTriadEvents.DegreesOfFreedom + Inventor.TriadSegmentEnum.kYAxisTranslationSegment
        End If

        If Me.chkYZPlaneTranslationSegment.CheckState = System.Windows.Forms.CheckState.Checked Then
            oTriadEvents.DegreesOfFreedom = oTriadEvents.DegreesOfFreedom + Inventor.TriadSegmentEnum.kYZPlaneTranslationSegment
        End If

        If Me.chkZAxisRotationSegment.CheckState = System.Windows.Forms.CheckState.Checked Then
            oTriadEvents.DegreesOfFreedom = oTriadEvents.DegreesOfFreedom + Inventor.TriadSegmentEnum.kZAxisRotationSegment
        End If

        If Me.chkZAxisTranslationSegment.CheckState = System.Windows.Forms.CheckState.Checked Then
            oTriadEvents.DegreesOfFreedom = oTriadEvents.DegreesOfFreedom + Inventor.TriadSegmentEnum.kZAxisTranslationSegment
        End If
    End Sub

    Private Sub btnReset_Click(sender As System.Object, e As System.EventArgs) Handles btnReset.Click
        ' Reset the current selection to clear the current selection.
        oSelectEvents.ResetSelections()
    End Sub

    Private Sub btnClearAll_Click(sender As System.Object, e As System.EventArgs) Handles btnClearAll.Click
        oSelectEvents.ClearSelectionFilter()

        ' Set flag so any events fired as a result of clearing
        ' the selection can be ignored.
        bClearingFilter = True
        lstFilters.SelectedIndex = -1
    End Sub

    Private Sub btnStartStop_Click(sender As System.Object, e As System.EventArgs) Handles btnStartStop.Click
        Dim oFaces As New Collection
        Dim i As Integer
        If btnStartStop.Text = "Start Interaction" Then
            btnStartStop.Text = "Stop Interaction"

            ' If the option is checked save all of the entities that
            ' are currently in the select set.  They need to be saved
            ' because the select set will be cleared when the Start is called.
            If chkKeepFaces.CheckState = System.Windows.Forms.CheckState.Checked Then
                For i = 1 To oInventorApp.ActiveDocument.SelectSet.Count
                    If TypeOf oInventorApp.ActiveDocument.SelectSet.Item(i) Is Inventor.Face Then
                        oFaces.Add(oInventorApp.ActiveDocument.SelectSet.Item(i))
                    End If
                Next
            End If

            ' Start the interaction.
            oInteraction.Start()

            ' If the option is checked add the previously selected entities
            ' to the current selection.
            If chkKeepFaces.CheckState = System.Windows.Forms.CheckState.Checked Then
                For i = 1 To oFaces.Count()
                    oSelectEvents.AddToSelectedEntities(oFaces.Item(i))
                Next
            End If
        Else
            oInteraction.Stop()
            btnStartStop.Text = "Start Interaction"
        End If
    End Sub

    Private Sub chkDisableInteraction_CheckedChanged(sender As System.Object, e As System.EventArgs) Handles chkDisableInteraction.CheckedChanged

    End Sub
End Class

Public Class Win32
    <DllImport("ole32")>
    Private Shared Function CLSIDFromProgIDEx(
        <MarshalAs(UnmanagedType.LPWStr)> ByVal lpszProgID As String, <Out> ByRef lpclsid As Guid) As Integer
    End Function
    <DllImport("ole32")>
    Private Shared Function CLSIDFromProgID(
        <MarshalAs(UnmanagedType.LPWStr)> ByVal lpszProgID As String, <Out> ByRef lpclsid As Guid) As Integer
    End Function
    <DllImport("oleaut32")>
    Private Shared Function GetActiveObject(
        <MarshalAs(UnmanagedType.LPStruct)> ByVal rclsid As Guid, ByVal pvReserved As IntPtr, <Out>
        <MarshalAs(UnmanagedType.IUnknown)> ByRef ppunk As Object) As Integer
    End Function

    Public Shared Function GetActiveObject(ByVal progID As String) As Object
        Dim obj As Object = Nothing
        Dim clsid As Guid

        ' Call CLSIDFromProgIDEx first then fall back on CLSIDFromProgID if
        ' CLSIDFromProgIDEx doesn't exist.
        Try
            CLSIDFromProgIDEx(progID, clsid)
        Catch ex As Exception
            CLSIDFromProgID(progID, clsid)
        End Try

        Dim hr = GetActiveObject(clsid, IntPtr.Zero, obj)
        If hr < 0 Then
            Err.Raise(0)
        End If
        Return obj
    End Function
End Class