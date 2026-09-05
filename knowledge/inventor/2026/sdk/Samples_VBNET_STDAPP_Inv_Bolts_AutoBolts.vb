Option Strict Off
Option Explicit On
Imports System.Runtime.InteropServices
Imports VB = Microsoft.VisualBasic
Friend Class frmAutoBolts
    Inherits System.Windows.Forms.Form

    Private Const BIF_RETURNONLYFSDIRS As Short = &H1S
    Private Const MAX_PATH As Short = 260

    Private Structure BrowseInfo
        Dim hOwner As Integer
        Dim pidlRoot As Integer
        Dim pszDisplayName As String
        Dim lpszTitle As String
        Dim ulFlags As Integer
        Dim lpfn As Integer
        Dim lParam As Integer
        Dim iImage As Integer
    End Structure

    Private Declare Function SHGetPathFromIDList Lib "shell32.dll" (ByVal pidl As Integer, ByVal pszPath As String) As Integer
    Private Declare Function SHBrowseForFolder Lib "shell32.dll" (ByRef lpBrowseInfo As BrowseInfo) As Integer

    Private Structure udtHoleInfo
        Dim Position As Inventor.Matrix
        Dim Radius As Double
        Dim Edge As Inventor.EdgeProxy
    End Structure

    Private oInventorApp As Inventor.Application
    Private oAssemblyDocument As Inventor.AssemblyDocument
    Private OccurrencesList() As Inventor.ComponentOccurrence
    Private LibraryPath As String

    Private Sub cmdBrowse_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdBrowse.Click
        Dim strFolderName As String
        strFolderName = Space(MAX_PATH)

        Dim bi As BrowseInfo
        With bi
            .hOwner = Me.Handle.ToInt32
            .pszDisplayName = "Select Folder"
            .lpszTitle = "Bolt library path:"
            .ulFlags = BIF_RETURNONLYFSDIRS
        End With

        Dim dwIDList As Integer
        dwIDList = SHBrowseForFolder(bi)

        Dim lGotPath As Integer
        lGotPath = SHGetPathFromIDList(dwIDList, strFolderName)

        If lGotPath Then
            strFolderName = VB.Left(strFolderName, InStr(strFolderName, Chr(0)) - 1)
            txtLibraryPath.Text = strFolderName
        Else
            strFolderName = vbNullString
        End If
    End Sub

    Private Sub cmdCancel_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdCancel.Click
        End
    End Sub

    Private Sub cmdPlaceBolts_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdPlaceBolts.Click
        Dim HoleInfo() As udtHoleInfo
        Dim HoleInfoCount As Integer

        ' Call the function that examines the B-Rep and finds the holes.
        Call GetHoleInfo(HoleInfo, HoleInfoCount, OccurrencesList(treAssembly.SelectedNode.Index))

        ' Call the function to place the bolts using the previously obtained hole information.
        Call PlaceBolts(HoleInfo, HoleInfoCount, oAssemblyDocument)
    End Sub

    Private Sub frmAutoBolts_Load(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load
        On Error Resume Next
        oInventorApp = Win32.GetActiveObject("Inventor.Application")
        If Err.Number Then
            MsgBox("Inventor must be running.")
            End
        End If
        On Error GoTo 0

        If oInventorApp.Documents.Count = 0 Then
            MsgBox("An assembly document must be active.")
            End
        End If

        If oInventorApp.ActiveDocumentType <> Inventor.DocumentTypeEnum.kAssemblyDocumentObject Then
            MsgBox("An assembly document must be active.")
            End
        End If

        oAssemblyDocument = oInventorApp.ActiveDocument

        Call BuildTree(oAssemblyDocument.ComponentDefinition.Occurrences, OccurrencesList, 0, Nothing)

        If Not OccurrencesList(0) Is Nothing Then
            cmdPlaceBolts.Enabled = True
        End If

        txtLibraryPath.Text = My.Application.Info.DirectoryPath & "\Bolt Library"
    End Sub


    Private Sub BuildTree(ByRef Occurrences As Inventor.ComponentOccurrences, ByRef OccurrenceList() As Inventor.ComponentOccurrence, ByRef OccurrenceCount As Short, ByRef ParentNode As System.Windows.Forms.TreeNode)

        ' Redimension the array so there's room for these occurrences.
        If OccurrenceCount = 0 Then
            ReDim Preserve OccurrenceList(Occurrences.Count - 1)
        Else
            ReDim Preserve OccurrenceList(UBound(OccurrenceList) + Occurrences.Count - 1)
        End If

        ' Iterate through the ocurrences.
        Dim oOccurrence As Inventor.ComponentOccurrence
        Dim AssemblyNode As System.Windows.Forms.TreeNode
        Dim PartNode As System.Windows.Forms.TreeNode
        For Each oOccurrence In Occurrences
            OccurrenceCount = OccurrenceCount + 1

            ' Use the Count property of the SubOccurrences property to determine if it's a subassembly or not.
            If oOccurrence.SubOccurrences.Count > 0 Then
                OccurrenceList(OccurrenceCount - 1) = Nothing

                ' Add a node to the tree list for the assembly.
                If ParentNode Is Nothing Then
                    AssemblyNode = treAssembly.Nodes.Add("", oOccurrence.Name, 1)
                Else
                    AssemblyNode = treAssembly.Nodes.Find(ParentNode.Name, True)(0).Nodes.Add("", oOccurrence.Name, 1)
                End If
                AssemblyNode.EnsureVisible()

                ' Recursively call the BuildTree function to traverse through the assembly.
                Call BuildTree((oOccurrence.SubOccurrences), OccurrenceList, OccurrenceCount, AssemblyNode)
            Else
                OccurrenceList(OccurrenceCount - 1) = oOccurrence

                ' Add a node to the tree list for the part.
                If ParentNode Is Nothing Then
                    PartNode = treAssembly.Nodes.Add("", oOccurrence.Name, 2)
                Else
                    PartNode = treAssembly.Nodes.Find(ParentNode.Name, True)(0).Nodes.Add("", oOccurrence.Name, 2)
                End If
                PartNode.EnsureVisible()
            End If
        Next oOccurrence
    End Sub


    Private Sub PlaceBolts(ByRef HoleInfo() As udtHoleInfo, ByRef HoleInfoCount As Integer, ByRef AssmDoc As Inventor.AssemblyDocument)

        ' Create the bolt library directory if it does not exist.
        Dim oFileSystemObject As New Scripting.FileSystemObject

        If (oFileSystemObject.FolderExists(txtLibraryPath.Text) = False) Then
            oFileSystemObject.CreateFolder(txtLibraryPath.Text)
        End If

        Dim oOccurrences As Inventor.ComponentOccurrences
        oOccurrences = AssmDoc.ComponentDefinition.Occurrences

        Dim i As Short
        Dim strFilename As String
        Dim strFilePath As String
        Dim oBoltDoc As Inventor.PartDocument
        Dim DiamParam As Inventor.ModelParameter
        Dim oBoltOccurrence As Inventor.ComponentOccurrence
        Dim oBoltEdge As Inventor.EdgeProxy
        Dim oInsert As Inventor.InsertConstraint
        For i = 0 To HoleInfoCount - 1
            strFilename = "Bolt_" & VB.Format(HoleInfo(i).Radius, "0.000") & ".ipt"

            ' Check to see if a bolt this size exists in the library directory.
            strFilePath = txtLibraryPath.Text & "\" & strFilename

            If (oFileSystemObject.FileExists(strFilePath) = False) Then
                ' Create a new bolt file of the correct size.

                ' Open the seed bolt file.  (Can be opened invisibly by seeting the second
                ' argument to False.  This leaves it visible to you can see what's happening.)

                Debug.Print(My.Application.Info.DirectoryPath & "\..\..\..\..\..\Data_Files\BoltSeed.ipt")


                oBoltDoc = oInventorApp.Documents.Open(My.Application.Info.DirectoryPath & "\..\..\..\..\..\Data_Files\BoltSeed.ipt", True)

                ' Obtain a reference to the parameter called "Diameter".
                DiamParam = oBoltDoc.ComponentDefinition.Parameters.ModelParameters("Diameter")

                ' Change the value of parameter, rounding it to 3 decimal places.
                DiamParam.Value = Val(VB.Format(HoleInfo(i).Radius * 2, "0.000"))

                ' Update the part.
                oBoltDoc.Update()

                ' Save the file using to the new filename.
                Call oBoltDoc.SaveAs(strFilePath, True)

                ' Close the seed bolt file without saving.
                oBoltDoc.Close(True)
            End If

            ' Place the bolt using the matrix that was defined previously.
            oBoltOccurrence = oOccurrences.Add(strFilePath, HoleInfo(i).Position)

            ' Get the edge of the bolt to use for the constraint.
            Call GetBoltEdge(oBoltOccurrence, oBoltEdge)

            ' If an edge was defined, place a constraint.
            If Not oBoltEdge Is Nothing Then
                oInsert = AssmDoc.ComponentDefinition.Constraints.AddInsertConstraint(oBoltEdge, HoleInfo(i).Edge, True, 0)
            End If
        Next
    End Sub

    Private Sub GetBoltEdge(ByRef oOccurrence As Inventor.ComponentOccurrence, ByRef oEdge As Inventor.EdgeProxy)
        ' Obtain the document the bolt occurrence references.
        Dim oPartDocument As Inventor.PartDocument
        oPartDocument = oOccurrence.Definition.Document

        ' Query for the edge with the "AutoBolts" attribute set.
        Dim oEdges As Inventor.ObjectCollection
        oEdges = oPartDocument.AttributeManager.FindObjects("AutoBolts")

        If oEdges.Count = 1 Then
            ' The edge obtained is in the context of the part document.
            ' Now get the edge in the context of this particular occurrence.
            Call oOccurrence.CreateGeometryProxy(oEdges.Item(1), oEdge)
        Else
            oEdge = Nothing
        End If
    End Sub


    Private Sub GetHoleInfo(ByRef HoleInfo() As udtHoleInfo, ByRef HoleInfoCount As Integer, ByRef Occurrence As Inventor.ComponentOccurrence)
        ' Get the surface body of the first occurrence in the assembly
        Dim oOccurrenceBody As Inventor.SurfaceBody
        'oOccurrenceBody = Occurrence.SurfaceBodies(1)
        For Each oOccurrenceBody In Occurrence.SurfaceBodies
            ' Iterate through loops of the body looking for loops containing
            ' single circular edges that connects a cylinder to a face that
            ' contains more than one loop.
            Dim oFace As Inventor.Face
            Dim oLoop As Inventor.EdgeLoop
            Dim oEdge As Inventor.Edge
            Dim oCylinderFace As Inventor.Face
            Dim oPlaneFace As Inventor.Face
            Dim oPlane As Inventor.Plane
            Dim oCylinder As Inventor.Cylinder
            Dim oCircle As Inventor.Circle
            Dim oMatrix As Inventor.Matrix
            Dim Tangent(2) As Double
            Dim Normal(2) As Double
            Dim oParam(1) As Double
            For Each oFace In oOccurrenceBody.Faces
                If oFace.SurfaceType = Inventor.SurfaceTypeEnum.kPlaneSurface Then
                    For Each oLoop In oFace.EdgeLoops
                        ' Check to see if the loop contains a single edge.

                        If oLoop.Edges.Count = 1 And oLoop.Edges(1).CurveType = Inventor.CurveTypeEnum.kCircleCurve Then
                            oEdge = oLoop.Edges(1)

                            ' Get the faces joined by the edge.
                            oCylinderFace = Nothing
                            oPlaneFace = Nothing
                            If oEdge.Faces(1).SurfaceType = Inventor.SurfaceTypeEnum.kCylinderSurface Then
                                oCylinderFace = oEdge.Faces(1)
                            ElseIf oEdge.Faces(1).SurfaceType = Inventor.SurfaceTypeEnum.kPlaneSurface Then
                                oPlaneFace = oEdge.Faces(1)
                            End If

                            If oEdge.Faces(2).SurfaceType = Inventor.SurfaceTypeEnum.kCylinderSurface Then
                                oCylinderFace = oEdge.Faces(2)
                            ElseIf oEdge.Faces(2).SurfaceType = Inventor.SurfaceTypeEnum.kPlaneSurface Then
                                oPlaneFace = oEdge.Faces(2)
                            End If

                            If Not oCylinderFace Is Nothing And Not oPlaneFace Is Nothing Then
                                ' Check that the planar face has multiple loops.  This should
                                ' eliminate the bottom of holes.
                                If oPlaneFace.EdgeLoops.Count > 1 Then
                                    ' Check to see if the cylinder is perpendicular to the plane.
                                    oPlane = oPlaneFace.Surface(Inventor.SurfaceTypeEnum.kPlaneSurface)
                                    oCylinder = oCylinderFace.Surface(Inventor.SurfaceTypeEnum.kCylinderSurface)
                                    If oPlane.Normal.IsParallelTo(oCylinder.AxisVector) Then
                                        HoleInfoCount = HoleInfoCount + 1
                                        ReDim Preserve HoleInfo(HoleInfoCount - 1)

                                        ' Save the edge.
                                        HoleInfo(HoleInfoCount - 1).Edge = oEdge

                                        oCircle = oEdge.Curve(oEdge.CurveType)

                                        ' Save the radius
                                        HoleInfo(HoleInfoCount - 1).Radius = oCircle.Radius

                                        oMatrix = oInventorApp.TransientGeometry.CreateMatrix

                                        oMatrix.Cell(1, 4) = oCircle.Center.X
                                        oMatrix.Cell(2, 4) = oCircle.Center.Y
                                        oMatrix.Cell(3, 4) = oCircle.Center.Z

                                        ' Get a normal from the face.
                                        oParam(0) = oPlaneFace.Evaluator.ParamRangeRect.MinPoint.X
                                        oParam(1) = oPlaneFace.Evaluator.ParamRangeRect.MinPoint.Y
                                        Call oPlaneFace.Evaluator.GetNormal(oParam, Normal)

                                        ' Set the Z Vector of the matrix.
                                        oMatrix.Cell(1, 3) = Normal(0)
                                        oMatrix.Cell(2, 3) = Normal(1)
                                        oMatrix.Cell(3, 3) = Normal(2)

                                        ' Get a tangent from the face.
                                        Call oPlaneFace.Evaluator.GetTangents(oParam, Tangent, Tangent)

                                        ' Set the X Vector of the matrix.
                                        oMatrix.Cell(1, 1) = Tangent(0)
                                        oMatrix.Cell(2, 1) = Tangent(1)
                                        oMatrix.Cell(3, 1) = Tangent(2)

                                        ' Cross the Z and X to create the Y vector.
                                        oMatrix.Cell(1, 2) = (Normal(1) * Tangent(2)) - (Normal(2) * Tangent(1))
                                        oMatrix.Cell(2, 2) = (Normal(2) * Tangent(0)) - (Normal(0) * Tangent(2))
                                        oMatrix.Cell(3, 2) = (Normal(0) * Tangent(1)) - (Normal(1) * Tangent(0))

                                        ' Save the matrix.
                                        HoleInfo(HoleInfoCount - 1).Position = oMatrix
                                    End If
                                End If
                            End If
                        End If
                    Next oLoop
                End If
            Next oFace
        Next oOccurrenceBody
    End Sub


    Private Sub treAssembly_NodeClick(ByVal eventSender As System.Object, ByVal eventArgs As System.Windows.Forms.TreeNodeMouseClickEventArgs) Handles treAssembly.NodeMouseClick
        Dim Node As System.Windows.Forms.TreeNode = eventArgs.Node
        If OccurrencesList(Node.Index) Is Nothing Then
            cmdPlaceBolts.Enabled = False
        Else
            cmdPlaceBolts.Enabled = True
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