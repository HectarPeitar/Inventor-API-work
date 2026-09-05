Option Strict Off
Option Explicit On
Imports System.Runtime.InteropServices

Friend Class frmBrowserPane
    Inherits System.Windows.Forms.Form

    Dim oInventorApp As Inventor.Application
    Dim WithEvents oAppEvents As Inventor.ApplicationEvents
    Dim bConnected As Boolean
    Dim oDoc As Inventor.Document
    Dim WithEvents oMFCCtl As SIMPLEMFCCONTROLLib.SIMPLEMFCCONTROL
    Dim oPanes As Inventor.BrowserPanes
    Dim WithEvents oPane As Inventor.BrowserPane

    Private Sub BrowserPaneBtn_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles BrowserPaneBtn.Click
        oPanes = oDoc.BrowserPanes
        oPane = oPanes.Add("Simple MFC Control", "SIMPLEMFCCONTROL.SIMPLEMFCCONTROLCtrl.1")
        oMFCCtl = oPane.Control
        oMFCCtl.Clear()
        oPane.Activate()
        MFCCtrlTextCtrl.Enabled = True
        MFCCtrlClearBtn.Enabled = True
        MFCCtlAddTextBtn.Enabled = True
        BrowserPaneBtn.Enabled = False
    End Sub

    ' Connect to existing session of Inventor
    Private Sub ConnectBtn_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles ConnectBtn.Click
        On Error Resume Next
        oInventorApp = Win32.GetActiveObject("Inventor.application")
        If Err.Number Then
            Err.Clear()
            MsgBox("Inventor must be running with a document opened")
            Exit Sub
        End If
        On Error GoTo 0

        On Error Resume Next
        oDoc = oInventorApp.ActiveDocument

        If Err.Number Or oDoc Is Nothing Then
            Err.Clear()
            MsgBox("Inventor must be running with a document opened")
            Exit Sub
        End If
        On Error GoTo 0

        bConnected = True
        oInventorApp.Visible = True
        BrowserPaneBtn.Enabled = True

        oAppEvents = oInventorApp.ApplicationEvents
        ConnectBtn.Enabled = False

    End Sub

    Private Sub ExitButton_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles ExitButton.Click
        Me.Close()
    End Sub

    Private Sub frmBrowserPane_Load(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load
        bConnected = False
        BrowserPaneBtn.Enabled = False
        MFCCtrlTextCtrl.Enabled = False
        MFCCtrlClearBtn.Enabled = False
        MFCCtlAddTextBtn.Enabled = False
    End Sub

    Private Sub frmBrowserPane_FormClosed(ByVal eventSender As System.Object, ByVal eventArgs As System.Windows.Forms.FormClosedEventArgs) Handles Me.FormClosed
        oDoc = Nothing
        oInventorApp = Nothing
        oMFCCtl = Nothing
    End Sub

    Private Sub MFCCtlAddTextBtn_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MFCCtlAddTextBtn.Click
        oPane.Activate()
        oMFCCtl.AddText(MFCCtrlTextCtrl.Text)
    End Sub

    Private Sub MFCCtrlClearBtn_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MFCCtrlClearBtn.Click
        oPane.Activate()
        oMFCCtl.Clear()
    End Sub
    ' Exit if inventor is exiting
    Private Sub oAppEvents_OnQuit(ByVal BeforeOrAfter As Inventor.EventTimingEnum, ByVal Context As Inventor.NameValueMap, ByRef HandlingCode As Inventor.HandlingCodeEnum) Handles oAppEvents.OnQuit
        Me.Close()
    End Sub
    ' Content of ActiveX control has changed. Event fired by the control
    Private Sub oMFCCtl_ContentChanged() Handles oMFCCtl.ContentChanged
        ListBoxCtrl.Items.Add(("SimpleMFCControl Event - Content Changed"))
    End Sub
    'BrowserPane Acitvation event
    Private Sub oPane_OnActivate() Handles oPane.OnActivate
        ListBoxCtrl.Items.Add(("BrowserPane Event - Activated"))
    End Sub
    'BrowserPane DeAcitvation event
    Private Sub oPane_OnDeactivate() Handles oPane.OnDeactivate
        ListBoxCtrl.Items.Add(("BrowserPane Event - DeActivated"))
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