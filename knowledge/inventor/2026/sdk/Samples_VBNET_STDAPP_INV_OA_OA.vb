Option Strict Off
Option Explicit On
Imports System.Runtime.InteropServices
Imports VB = Microsoft.VisualBasic
Friend Class frmOverlayAssembly
    Inherits System.Windows.Forms.Form

    Private oApp As Inventor.Application
    Private CurrentFileName As String

    Private Sub frmOverlayAssembly_Load(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load
        ' Get Inventor object
        On Error Resume Next
        oApp = Win32.GetActiveObject("Inventor.Application")
        If Err.Number Then
            MsgBox("Inventor must be running.", MsgBoxStyle.OkOnly + MsgBoxStyle.Exclamation)
            Me.Close()
            End
        End If

        Dim oDoc As Inventor.AssemblyDocument
        oDoc = oApp.ActiveDocument

        Dim oAssemblyCompDef As Inventor.AssemblyComponentDefinition
        Dim oPosReps As Inventor.PositionalRepresentations
        Dim NoPosReps As Integer
        If Not oDoc Is Nothing Then
            oAssemblyCompDef = oDoc.ComponentDefinition

            oPosReps = oAssemblyCompDef.RepresentationsManager.PositionalRepresentations

            NoPosReps = oPosReps.Count

            If NoPosReps > 0 Then
                ' Write the filename to the text box.
                txtFilename.Text = oDoc.FullFileName
                CurrentFileName = txtFilename.Text

                ListPositionalStates()
            End If

        End If

        On Error GoTo 0
    End Sub

    Private Sub AddRep_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles AddRep.Click

        Dim counter1 As Integer
        Dim StateAdded As Boolean
        Dim counter2 As Integer
        If AvailableStates.SelectedItems.Count > 0 Then

            For counter1 = 1 To AvailableStates.Items.Count

                If AvailableStates.GetSelected(counter1 - 1) Then
                    ' If we find a match of a state in the SelectedStates box,
                    ' we shouldn't be adding it again.
                    StateAdded = False

                    For counter2 = 1 To SelectedStates.Items.Count
                        'If VB6.GetItemString(AvailableStates, counter1 - 1) = VB6.GetItemString(SelectedStates, counter2 - 1) Then
                        If AvailableStates.Items(counter1 - 1).ToString = AvailableStates.Items(counter2 - 1).ToString Then
                            StateAdded = True
                        End If
                    Next

                    If Not StateAdded Then
                        'SelectedStates.Items.Add((VB6.GetItemString(AvailableStates, counter1 - 1)))
                        SelectedStates.Items.Add(AvailableStates.Items(counter1 - 1).ToString)
                    End If

                    AvailableStates.SetSelected(counter1 - 1, False)
                End If
            Next

            'Enable removal if we have any rep.
            If SelectedStates.Items.Count > 0 Then
                RemoveRep.Enabled = True
            End If

            'Enable creation if we have more than 1 rep.
            If SelectedStates.Items.Count > 1 Then
                cmdOK.Enabled = True
            End If
        End If

    End Sub

    'Bring up the Assembly dialog Box
    Private Sub cmdBrowse_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdBrowse.Click

        ' Setup parameters for the open dialog.
        With CommonDialog1Open
            .InitialDirectory = oApp.FileLocations.Workspace
            .Title = "Overlay Assembly"
            .DefaultExt = ".iam"
            .Filter = "Inventor Assembly File (*.iam) | *.iam"
            .FilterIndex = 0
            .ShowReadOnly = False
            On Error Resume Next
            .ShowDialog()
            If Err.Number Then
                Exit Sub
            End If
            On Error GoTo 0
        End With

        ' Write the filename to the text box.
        txtFilename.Text = CommonDialog1Open.FileName
        CurrentFileName = txtFilename.Text

        ' Check to see if a filename was specified and call the ListPositionalStates function.
        If txtFilename.Text <> "" Then
            ListPositionalStates()
        End If
    End Sub

    Private Sub ListPositionalStates()

        'Restore original state of dialog
        AvailableStates.Items.Clear()
        SelectedStates.Items.Clear()
        RemoveRep.Enabled = False
        cmdOK.Enabled = False

        On Error Resume Next

        Dim oActiveDoc As Inventor.AssemblyDocument
        oActiveDoc = oApp.ActiveDocument

        ' Open the specified file.
        Dim oDoc As Inventor.AssemblyDocument
        On Error Resume Next
        oDoc = oApp.Documents.Open(txtFilename.Text, False)
        If Err.Number Then
            MsgBox("Unable to open the specified file.", MsgBoxStyle.OkOnly + MsgBoxStyle.Exclamation)
            Exit Sub
        End If
        On Error GoTo 0

        Dim CloseSourceDoc As Boolean
        CloseSourceDoc = True

        If Not oActiveDoc Is Nothing Then
            If oActiveDoc.Type = oDoc.Type Then
                CloseSourceDoc = False
            End If
        End If

        ' Set a reference to the assembly component definition.
        Dim oAssemblyCompDef As Inventor.AssemblyComponentDefinition
        oAssemblyCompDef = oDoc.ComponentDefinition

        ' Get the list of all the available positional states.
        Dim oPosReps As Inventor.PositionalRepresentations
        oPosReps = oAssemblyCompDef.RepresentationsManager.PositionalRepresentations

        Dim NoPosReps As Integer
        NoPosReps = oPosReps.Count

        If NoPosReps < 1 Then
            MsgBox("No Positional Representations found in Assembly.", MsgBoxStyle.OkOnly + MsgBoxStyle.Exclamation)
            Exit Sub
        End If

        ' Populate the list box.
        Dim i As Integer

        For i = 1 To NoPosReps
            AvailableStates.Items.Add((oPosReps(i).Name))

            'Add the 'master' to the selected states (by default)
            If oPosReps(i).Master Then
                SelectedStates.Items.Add((oPosReps(i).Name))
            End If
        Next

        AddRep.Enabled = True
        RemoveRep.Enabled = True

        If CloseSourceDoc Then
            oDoc.Close()
        End If

        On Error GoTo 0

    End Sub


    Private Sub cmdCancel_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdCancel.Click
        Me.Close()
    End Sub

    Private Sub cmdOK_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdOK.Click

        ' Create a new assembly doc.
        Dim oAsmDoc As Inventor.AssemblyDocument
        oAsmDoc = oApp.Documents.Add(Inventor.DocumentTypeEnum.kAssemblyDocumentObject, oApp.FileManager.GetTemplateFile(Inventor.DocumentTypeEnum.kAssemblyDocumentObject))

        Dim occurrenceCount As Integer
        occurrenceCount = SelectedStates.Items.Count

        Dim counter As Integer
        ' Insert occurrences.
        Dim oMatrix As Inventor.Matrix
        Dim oCompOcc As Inventor.ComponentOccurrence
        For counter = 1 To occurrenceCount

            oMatrix = oApp.TransientGeometry.CreateMatrix

            oCompOcc = oAsmDoc.ComponentDefinition.Occurrences.Add(txtFilename.Text, oMatrix)

            ' Set the positional state
            oCompOcc.ActivePositionalRepresentation = AvailableStates.Items(counter - 1).ToString 'VB6.GetItemString(SelectedStates, counter - 1)

            ' Set occurrence to be Reference
            ' Don't do this for the first representation
            If counter <> 1 Then
                oCompOcc.BOMStructure = Inventor.BOMStructureEnum.kReferenceBOMStructure
            End If

            ' Ground the occurrence
            oCompOcc.Grounded = True

        Next

        oAsmDoc.ComponentDefinition.BOMStructure = Inventor.BOMStructureEnum.kReferenceBOMStructure

        ' Save the assembly.
        Dim TempString As String
        TempString = VB.Left(txtFilename.Text, InStr(txtFilename.Text, ".") - 1)

        Dim NewFileName As String

        Dim FileFound As Boolean
        FileFound = True

        Dim i As Integer
        i = 0

        Do While FileFound
            i = i + 1
            NewFileName = TempString & "_Overlay" & i & ".iam"
            If (Dir(NewFileName) = "") Then
                FileFound = False
            End If
        Loop

        oAsmDoc.FullFileName = NewFileName
        Me.Close()

    End Sub


    Private Sub RemoveRep_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles RemoveRep.Click

        Dim counter As Integer
        If SelectedStates.SelectedItems.Count > 0 Then

            'Remove selected items.
            counter = SelectedStates.Items.Count
            For counter = SelectedStates.Items.Count To 1 Step -1
                If SelectedStates.GetSelected(counter - 1) Then
                    SelectedStates.Items.RemoveAt((counter - 1))
                End If
            Next

            'If the list count falls to 0, disable 'Remove'
            If SelectedStates.Items.Count < 1 Then
                RemoveRep.Enabled = False
            End If

            'If the list count falls to 1, disable 'Create Overlay Assembly'
            If SelectedStates.Items.Count < 2 Then
                cmdOK.Enabled = False
            End If

        End If

    End Sub


    Private Sub txtFilename_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtFilename.TextChanged
        If Len(txtFilename.Text) = 0 Then
            AvailableStates.Items.Clear()
            SelectedStates.Items.Clear()
            AddRep.Enabled = False
            RemoveRep.Enabled = False
            cmdOK.Enabled = False
        End If
    End Sub

    ' Check to see if they entered a return and process the states.
    Private Sub txtFilename_KeyPress(ByVal eventSender As System.Object, ByVal eventArgs As System.Windows.Forms.KeyPressEventArgs) Handles txtFilename.KeyPress
        Dim KeyAscii As Short = Asc(eventArgs.KeyChar)

        If KeyAscii = 13 And Len(txtFilename.Text) > 0 Then
            KeyAscii = 0
            ListPositionalStates()
        End If
        eventArgs.KeyChar = Chr(KeyAscii)
        If KeyAscii = 0 Then
            eventArgs.Handled = True
        End If
    End Sub

    ' Check to see if a filename was specified and call the ListPositionalStates function.
    Private Sub txtFilename_Leave(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtFilename.Leave

        If txtFilename.Text <> CurrentFileName And Len(txtFilename.Text) <> 0 Then
            CurrentFileName = txtFilename.Text
            ListPositionalStates()
        End If
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