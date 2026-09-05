Option Strict Off
Option Explicit On
Imports System.Runtime.InteropServices
<ProgId("AnalyzeControl.BrowserControl")> Public Class BrowserControl
    Inherits System.Windows.Forms.UserControl

    Private m_bIsInitializing As Boolean

    Event TrackPointSelected(ByRef Arg As String)
    Event TrackPointUnSelected()
    Event TrackPointDeleted(ByRef Arg As String)
    Event AddTrackPoint()
    Event ShowHideResultCurves(ByRef ShowResult As Boolean)
    Event RunAnalysis()


    Public Sub AddNewTrackPoint(ByRef Caption As String)
        Call lstTrackPoints.Items.Insert(lstTrackPoints.Items.Count - 1, Caption)
    End Sub

    Private Sub chkDisplayCurves_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles chkDisplayCurves.CheckStateChanged
        If m_bIsInitializing = True Then
            Exit Sub
        Else

            If chkDisplayCurves.CheckState = System.Windows.Forms.CheckState.Checked Then
                RaiseEvent ShowHideResultCurves(True)
            Else
                RaiseEvent ShowHideResultCurves(False)
            End If
        End If
    End Sub

    Private Sub cmdRunAnalysis_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdRunAnalysis.Click
        RaiseEvent RunAnalysis()
    End Sub

    ' Handle select and add for track point.
    Private Sub lstTrackPoints_SelectedIndexChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles lstTrackPoints.SelectedIndexChanged
        If m_bIsInitializing = True Then
            Exit Sub
        Else
            If lstTrackPoints.Text <> "" Then
                If lstTrackPoints.SelectedIndex = lstTrackPoints.Items.Count - 1 Then
                    RaiseEvent AddTrackPoint()
                Else
                    RaiseEvent TrackPointSelected(lstTrackPoints.Text)
                End If
            End If
        End If
    End Sub

    ' Handle delete for track point.
    Private Sub lstTrackPoints_KeyDown(ByVal eventSender As System.Object, ByVal eventArgs As System.Windows.Forms.KeyEventArgs) Handles lstTrackPoints.KeyDown
        Dim KeyCode As Short = eventArgs.KeyCode
        Dim Shift As Short = eventArgs.KeyData \ &H10000
        If lstTrackPoints.Text <> "" Then
            If lstTrackPoints.SelectedIndex <> lstTrackPoints.Items.Count - 1 Then
                If KeyCode = 46 Then
                    RaiseEvent TrackPointDeleted(lstTrackPoints.Text)
                    Call lstTrackPoints.Items.RemoveAt(lstTrackPoints.SelectedIndex)
                End If
            End If
        End If
    End Sub

    Private Sub lstTrackPoints_Leave(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles lstTrackPoints.Leave
        lstTrackPoints.SelectedIndex = -1
        RaiseEvent TrackPointUnSelected()
    End Sub

    Private Sub UserControl_Initialize()
        lstTrackPoints.Items.Add("Click to add point")
    End Sub

    Public Property RunAnalysisEnabled() As Boolean
        Get
            RunAnalysisEnabled = cmdRunAnalysis.Enabled
        End Get
        Set(ByVal Value As Boolean)
            cmdRunAnalysis.Enabled = Value
        End Set
    End Property


    Public Property ListEnabled() As Boolean
        Get
            ListEnabled = lstTrackPoints.Enabled
        End Get
        Set(ByVal Value As Boolean)
            lstTrackPoints.Enabled = Value
        End Set
    End Property


    Public WriteOnly Property ShowDisplayResults() As Boolean
        Set(ByVal Value As Boolean)
            If Value Then
                chkDisplayCurves.Enabled = True
            Else
                chkDisplayCurves.Enabled = False
            End If
        End Set
    End Property


    Public Property DisplayCurvesValue() As Boolean
        Get
            If chkDisplayCurves.CheckState = System.Windows.Forms.CheckState.Checked Then
                DisplayCurvesValue = True
            Else
                DisplayCurvesValue = False
            End If
        End Get
        Set(ByVal Value As Boolean)
            If Value = True Then
                chkDisplayCurves.CheckState = System.Windows.Forms.CheckState.Checked
            Else
                chkDisplayCurves.CheckState = System.Windows.Forms.CheckState.Unchecked
            End If
        End Set
    End Property
End Class