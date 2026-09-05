Option Strict Off
Option Explicit On
Imports System.Runtime.InteropServices
Imports VB = Microsoft.VisualBasic
Friend Class Form1
    Inherits System.Windows.Forms.Form

    Private Const MAX_PATH As Integer = 260

    Private Const INVALID_HANDLE_VALUE As Integer = -1
    Private Const FILE_ATTRIBUTE_DIRECTORY As Integer = &H10S

    Private Structure FILETIME
        Dim dwLowDateTime As Integer
        Dim dwHighDateTime As Integer
    End Structure

    Private Structure WIN32_FIND_DATA
        Dim dwFileAttributes As Integer
        Dim ftCreationTime As FILETIME
        Dim ftLastAccessTime As FILETIME
        Dim ftLastWriteTime As FILETIME
        Dim nFileSizeHigh As Integer
        Dim nFileSizeLow As Integer
        Dim dwReserved0 As Integer
        Dim dwReserved1 As Integer
        'UPGRADE_WARNING: Fixed-length string size must fit in the buffer. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="3C1E4426-0B80-443E-B943-0627CD55D48B"'
        <VBFixedString(MAX_PATH), System.Runtime.InteropServices.MarshalAs(System.Runtime.InteropServices.UnmanagedType.ByValArray, SizeConst:=MAX_PATH)> Public cFileName() As Char
        'UPGRADE_WARNING: Fixed-length string size must fit in the buffer. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="3C1E4426-0B80-443E-B943-0627CD55D48B"'
        <VBFixedString(14), System.Runtime.InteropServices.MarshalAs(System.Runtime.InteropServices.UnmanagedType.ByValArray, SizeConst:=14)> Public cAlternate() As Char
    End Structure

    Private Declare Function FindClose Lib "kernel32" (ByVal hFindFile As Integer) As Integer

    'UPGRADE_WARNING: Structure WIN32_FIND_DATA may require marshalling attributes to be passed as an argument in this Declare statement. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="C429C3A5-5D47-4CD9-8F51-74A1616405DC"'
    Private Declare Function FindFirstFile Lib "kernel32" Alias "FindFirstFileA" (ByVal lpFileName As String, ByRef lpFindFileData As WIN32_FIND_DATA) As Integer

    Private oInventorApp As Inventor.Application
    Private sFacFullFileName As String

    ' Name of the folder in which the iPart members will be generated
    Private sMemFolderLoc As String

    Public Function TrimNull(ByRef startstr As String) As String
        'returns the string up to the first
        'null, if present, or the passed string
        Dim pos As Short

        pos = InStr(startstr, Chr(0))

        If pos Then
            TrimNull = VB.Left(startstr, pos - 1)
            Exit Function
        End If

        TrimNull = startstr

    End Function

    Private Function DoesFileExist(ByRef sPath As String) As Boolean

        Dim bFileExists As Boolean
        bFileExists = False

        'local working variables
        Dim WFD As WIN32_FIND_DATA
        Dim hFile As Integer
        Dim sTmp As String

        'obtain handle to the first filespec match
        hFile = FindFirstFile(sPath, WFD)

        'if valid ...
        If hFile <> INVALID_HANDLE_VALUE Then

            'remove trailing nulls
            sTmp = TrimNull(WFD.cFileName)

            'Even though this routine uses filespecs,
            '*.* is still valid and will cause the search
            'to return folders as well as files, so a
            'check against folders is still required.
            If Not (WFD.dwFileAttributes And FILE_ATTRIBUTE_DIRECTORY) = FILE_ATTRIBUTE_DIRECTORY Then

                ' File found !!
                bFileExists = True
            End If

            'close the handle
            hFile = FindClose(hFile)
        End If

        DoesFileExist = bFileExists
    End Function

    Private Sub Cancel_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles Cancel.Click
        Me.Close()
    End Sub

    Private Sub FileBrowse_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles FileBrowse.Click
        Dim oFileDialog As Inventor.FileDialog
        Call oInventorApp.CreateFileDialog(oFileDialog)

        With oFileDialog
            .DialogTitle = "Select iPart Factory"
            .Filter = "Inventor Part Files (*.ipt)|*.ipt"
            .FilterIndex = 0
            .ShowOpen()
            If .FileName <> "" Then
                sFacFullFileName = .FileName
                iPartFac.Text = sFacFullFileName
            Else
                Exit Sub
            End If
        End With

        ' Get the member cache directory from the factory
        ' Open the factory document
        Dim oPartFacDoc As Inventor.PartDocument
        oPartFacDoc = oInventorApp.Documents.Open(sFacFullFileName)

        Dim oCompDef As Inventor.PartComponentDefinition
        oCompDef = oPartFacDoc.ComponentDefinition

        ' Make sure we have a standard iPart factory and
        Dim oiPrtFac As Inventor.iPartFactory
        If oCompDef.IsiPartFactory = True Then
            oiPrtFac = oCompDef.iPartFactory

            If oiPrtFac.CustomFactory = True Then
                MsgBox("Expecting a standard factory")
                Exit Sub
            End If

            sMemFolderLoc = oiPrtFac.MemberCacheDir & "\"
        Else
            MsgBox("Expecting an iPart factory")
            Exit Sub
        End If

        ' We got a valid iPart file, enable the OK button
        OK.Enabled = True

        ' Since we are activating projects, we should close all documents
        Dim oDoc As Inventor.Document
        For Each oDoc In oInventorApp.Documents
            oDoc.Close()
        Next oDoc

        Dim oFileLocs As Inventor.FileLocations
        oFileLocs = oInventorApp.FileLocations

        Dim bHasUnderScoreLib As Boolean
        bHasUnderScoreLib = False

        ' Check if this file belongs to a project:
        ' Back resolve the fileName with the currently active project.
        ' If the file back resolves, it belongs to the currently active project

        ' Resolve the file with current project
        ' FindInLocations gives back a library Name if the file is in a library
        ' If the file is in a workspace it gives back the path to the workspace
        Dim eLocType As Inventor.LocationTypeEnum
        Dim sNameOrPath As String
        Call oFileLocs.FindInLocations(sFacFullFileName, sNameOrPath, eLocType)

        ' Special processing if factory is in a library
        Dim iNumLibs As Integer
        Dim asLibNames() As String
        Dim asLibPaths() As String
        Dim sTmpLib As String
        Dim iLibCnt As Short
        If eLocType = Inventor.LocationTypeEnum.kLibraryLocation Then

            ' Check if a corresponding a _library exists in this project
            ' Loop through all libraries in this project and look for
            ' _Library

            Call oFileLocs.Libraries(iNumLibs, asLibNames, asLibPaths)

            sTmpLib = "_" & sNameOrPath

            For iLibCnt = 0 To iNumLibs - 1
                If asLibNames(iLibCnt) = sTmpLib Then
                    bHasUnderScoreLib = True
                    Exit For
                End If
            Next
        End If

        ' Update the text field and tool tip with corresponding message
        ToolTip1.SetToolTip(iPartMem, sMemFolderLoc)

        If bHasUnderScoreLib = False Then
            iPartMem.Text = "Factory sub-folder"
        Else
            iPartMem.Text = "Library"
        End If
    End Sub

    Private Sub Form1_Load(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load
        On Error Resume Next
        oInventorApp = Win32.GetActiveObject("Inventor.Application")
        If Err.Number Then
            MsgBox("Inventor must be running.")
            Me.Close()
            Exit Sub
        End If

        ' Default is Regenerate existing
        RegenMems.Checked = True
        CreateMems.Checked = False

        ' Grey out the OK button till we get a valid iPart factory
        OK.Enabled = False

        ' Set the focus to the file browse button
        FileBrowse.Focus()
    End Sub

    Private Sub OK_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles OK.Click
        On Error Resume Next

        If RegenMems.Checked = True Then
            RegenerateExisting()
        Else
            CreateAll()
        End If

    End Sub

    ' Routine to regenerate existing iPart members
    Private Sub RegenerateExisting()
        On Error Resume Next

        ' Open the factory document
        Dim oFacDoc As Inventor.PartDocument
        oFacDoc = oInventorApp.Documents.Open(sFacFullFileName)

        Dim oCompDef As Inventor.PartComponentDefinition
        oCompDef = oFacDoc.ComponentDefinition

        Dim iNumRows As Short
        Dim oiPrtFac As Inventor.iPartFactory
        oiPrtFac = oCompDef.iPartFactory

        iNumRows = oiPrtFac.TableRows.Count

        ' Create a member for each row and update the member to make sure that it is in-synch
        ' with the factory
        Dim iRow As Short
        Dim oRow As Inventor.iPartTableRow
        Dim sMemFileName As String
        Dim oMem As Inventor.iPartMember
        Dim oMemDoc As Inventor.Document
        For iRow = 1 To iNumRows
            ' Need to retrieve the factory each time since the
            ' table objects are only valid for one transaction
            oiPrtFac = oCompDef.iPartFactory

            oRow = oiPrtFac.TableRows(iRow)

            ' Get the filename for the row
            sMemFileName = oRow.PartName

            ' Check if this file exists in the member file folder
            If DoesFileExist(sMemFolderLoc & sMemFileName) = True Then
                ' Regenerate the member
                oMem = oiPrtFac.CreateMember(iRow)

                oMemDoc = oMem.Parent.Document

                ' Update the member
                oMemDoc.Update()
                oMemDoc.Save()
                oMemDoc.Close()
            End If
        Next

        oFacDoc.Close()

    End Sub

    ' Routine to create iPart members for all rows in the iPart factory
    Private Sub CreateAll()
        On Error Resume Next

        ' Open the factory document
        Dim oFacDoc As Inventor.PartDocument
        oFacDoc = oInventorApp.Documents.Open(sFacFullFileName)

        Dim oCompDef As Inventor.PartComponentDefinition
        oCompDef = oFacDoc.ComponentDefinition

        Dim iNumRows As Short
        Dim oiPrtFac As Inventor.iPartFactory
        oiPrtFac = oCompDef.iPartFactory

        iNumRows = oiPrtFac.TableRows.Count

        ' Create a member for each row and update the member to make sure that it is in-synch
        ' with the factory
        Dim iRow As Short
        Dim oMem As Inventor.iPartMember
        Dim oMemDoc As Inventor.Document
        For iRow = 1 To iNumRows
            oMem = oiPrtFac.CreateMember(iRow)

            oMemDoc = oMem.Parent.Document

            ' Update the member
            oMemDoc.Update()
            oMemDoc.Save()
            oMemDoc.Close()
        Next

        oFacDoc.Close()

    End Sub

    'UPGRADE_WARNING: Event RegenMems.CheckedChanged may fire when form is initialized. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="88B12AE1-6DE0-48A0-86F1-60C0686C026A"'
    Private Sub RegenMems_CheckedChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles RegenMems.CheckedChanged
        If eventSender.Checked Then
            RegenMems.Checked = True
            CreateMems.Checked = False
        End If
    End Sub

    'UPGRADE_WARNING: Event CreateMems.CheckedChanged may fire when form is initialized. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="88B12AE1-6DE0-48A0-86F1-60C0686C026A"'
    Private Sub CreateMems_CheckedChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles CreateMems.CheckedChanged
        If eventSender.Checked Then
            RegenMems.Checked = False
            CreateMems.Checked = True
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