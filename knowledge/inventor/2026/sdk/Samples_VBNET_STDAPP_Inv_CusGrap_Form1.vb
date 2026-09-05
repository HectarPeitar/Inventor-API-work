Option Strict Off
Option Explicit On
Imports System.Runtime.InteropServices

Friend Class frmLaserDrilling
    Inherits System.Windows.Forms.Form

    Private Sub frmLaserDrilling_Load(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load

        On Error Resume Next

        'obtain the Inventor object if it is already open
        oInventorApp = Win32.GetActiveObject("Inventor.Application")

        'if Inventor is not open then create Inventor object
        If Err.Number Then
            'create and access Inventor's Application object
            oInventorApp = CreateObject("Inventor.Application")

        End If

        On Error GoTo 0

        'make Inventor visible if it is not
        oInventorApp.Visible = True

        'set the path file name to the part document
        Dim sPartFileName As String
        sPartFileName = My.Application.Info.DirectoryPath & "\Part.ipt"

        'open the part document
        oPartDocument = oInventorApp.Documents.Open(sPartFileName)

        'initialize the TransientGeometry object
        oTransGeom = oInventorApp.TransientGeometry

        'create or access already created data sets collection, store in oGraphicData variable
        On Error Resume Next
        'try to access the existing object
        oGraphicData = oPartDocument.GraphicsDataSetsCollection.Item(kLaserOperationID)
        If Err.Number Then
            Err.Clear()
            On Error GoTo 0
            'if there was an error,then create the new object
            oGraphicData = oPartDocument.GraphicsDataSetsCollection.Add(kLaserOperationID)
        End If
        On Error GoTo 0


        'create or access already created client graphics collection,store in oGraphics variable
        On Error Resume Next
        'try to access the existing object
        oGraphics = oPartDocument.ComponentDefinition.ClientGraphicsCollection.Item(kLaserOperationID)
        If Err.Number Then
            Err.Clear()
            On Error GoTo 0
            'if there was an
            oGraphics = oPartDocument.ComponentDefinition.ClientGraphicsCollection.Add(kLaserOperationID)
        End If
        On Error GoTo 0


        'we will use 5 data sets (for laser path, laser tool, sparks,laser trace, removed part) as part of the data sets collection object
        'each data set contains the coordinate sets, color sets, etc. for laser path, laser tool, sparks, laser trace, removed part
        'but, we need not explicitly create the DataSet objects, we can directly create the coordinate sets, color sets etc.


        'create 5 (for laser path, laser tool, sparks, laser trace, removed part) nodes as part of the client grapchics collection object
        'each node contains the grahphical information for laser path, laser tool, remove tool, removed part
        'just creation,we will set the graphical information later
        oLaserPathNode = oGraphics.AddNode(kLaserPathId)
        oLaserToolNode = oGraphics.AddNode(kLaserToolId)
        oSparksNode = oGraphics.AddNode(kSparksId)
        oLaserTraceNode = oGraphics.AddNode(kLaserTraceId)
        oRemovedPartNode = oGraphics.AddNode(kRemovedPartId)


        'set the laser operation parameters
        Call SetLaserOperationParameters()


    End Sub

    Private Sub SetLaserOperationParameters()

        'initialize the laser parameters
        'drill diameter
        dHole = 1.0#

        'drill height
        dHeight = 10.0#

        'laser tool diameter
        dToolDia = 0.25

        'laser tool diameter
        dToolLength = 5.0#

        'set the accuracy
        Accuracy = 25

        'not a laser parameter but a constant
        'extrusion height of the cylindrical section which we created in the "Part Modeling" lesson
        dExtrudeHeight = 3.0#

    End Sub

    Private Sub DrawTool_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles DrawTool.Click

        'draw the laser tool
        Call DrawLaserTool()

        'also enable the MoveTool button
        MoveTool.Enabled = True

    End Sub

    Private Sub MoveTool_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MoveTool.Click

        'first create laser path
        DrawLaserPath()

        'draw the sparks
        DrawSparks()

        'call the method to move the tool
        Call MoveLaserTool()

        'after laser cutting, enable removal of cut section
        RemoveCutSection.Enabled = True

    End Sub


    Private Sub RemoveCutSection_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles RemoveCutSection.Click

        'draw the cut portion first
        Call DrawCutPortion()

        'remove the cut portion
        Call RemoveCutPortion()

        'finally push out the cut portion with the laser tool
        Call PushOutCutPortion()
    End Sub


    Private Sub frmLaserDrilling_FormClosed(ByVal eventSender As System.Object, ByVal eventArgs As System.Windows.Forms.FormClosedEventArgs) Handles Me.FormClosed

        'check if the document is still open
        If Not oInventorApp.ActiveDocument Is Nothing Then

            'delete all nodes
            If Not oLaserPathNode Is Nothing Then
                oLaserPathNode.Delete()
            End If

            If Not oLaserToolNode Is Nothing Then
                oLaserToolNode.Delete()
            End If

            If Not oSparksNode Is Nothing Then
                oSparksNode.Delete()
            End If

            If Not oLaserTraceNode Is Nothing Then
                oLaserTraceNode.Delete()
            End If

            If Not oRemovedPartNode Is Nothing Then
                oRemovedPartNode.Delete()
            End If

            'delete data sets
            If Not oGraphicData Is Nothing Then
                oGraphicData.Delete()
            End If

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