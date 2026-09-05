Imports System.Drawing
Imports System.Windows.Forms

Public Class frmAssemblyTree
    Inherits System.Windows.Forms.Form

#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call

    End Sub

    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    Friend WithEvents cmdRefreshTree As System.Windows.Forms.Button
    Friend WithEvents AssemblyStructureTree As System.Windows.Forms.TreeView
    Friend WithEvents OpenFileDialog As System.Windows.Forms.OpenFileDialog
    Friend WithEvents imageList As System.Windows.Forms.ImageList
    Friend WithEvents grpBoxAssemblyFile As System.Windows.Forms.GroupBox
    Friend WithEvents cmdBrowse As System.Windows.Forms.Button
    Friend WithEvents LODRep As System.Windows.Forms.ComboBox
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents RefdDocs As System.Windows.Forms.TreeView
    Friend WithEvents RefdFiles As System.Windows.Forms.TreeView
    Friend WithEvents ShowFlatList As System.Windows.Forms.RadioButton
    Friend WithEvents ShowAllLevels As System.Windows.Forms.RadioButton
    Friend WithEvents FirstLevel As System.Windows.Forms.RadioButton
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents Label6 As System.Windows.Forms.Label
    Friend WithEvents Label7 As System.Windows.Forms.Label
    Friend WithEvents txtFileName As System.Windows.Forms.TextBox
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(frmAssemblyTree))
        Me.cmdRefreshTree = New System.Windows.Forms.Button
        Me.AssemblyStructureTree = New System.Windows.Forms.TreeView
        Me.imageList = New System.Windows.Forms.ImageList(Me.components)
        Me.OpenFileDialog = New System.Windows.Forms.OpenFileDialog
        Me.grpBoxAssemblyFile = New System.Windows.Forms.GroupBox
        Me.ShowFlatList = New System.Windows.Forms.RadioButton
        Me.ShowAllLevels = New System.Windows.Forms.RadioButton
        Me.FirstLevel = New System.Windows.Forms.RadioButton
        Me.Label4 = New System.Windows.Forms.Label
        Me.LODRep = New System.Windows.Forms.ComboBox
        Me.txtFileName = New System.Windows.Forms.TextBox
        Me.cmdBrowse = New System.Windows.Forms.Button
        Me.Label1 = New System.Windows.Forms.Label
        Me.Label2 = New System.Windows.Forms.Label
        Me.Label3 = New System.Windows.Forms.Label
        Me.RefdDocs = New System.Windows.Forms.TreeView
        Me.RefdFiles = New System.Windows.Forms.TreeView
        Me.GroupBox1 = New System.Windows.Forms.GroupBox
        Me.Label5 = New System.Windows.Forms.Label
        Me.Label6 = New System.Windows.Forms.Label
        Me.Label7 = New System.Windows.Forms.Label
        Me.grpBoxAssemblyFile.SuspendLayout()
        Me.GroupBox1.SuspendLayout()
        Me.SuspendLayout()
        '
        'cmdRefreshTree
        '
        Me.cmdRefreshTree.Location = New System.Drawing.Point(259, 63)
        Me.cmdRefreshTree.Name = "cmdRefreshTree"
        Me.cmdRefreshTree.Size = New System.Drawing.Size(88, 21)
        Me.cmdRefreshTree.TabIndex = 16
        Me.cmdRefreshTree.Text = "Refresh "
        '
        'treList
        '
        Me.AssemblyStructureTree.ImageIndex = 0
        Me.AssemblyStructureTree.ImageList = Me.imageList
        Me.AssemblyStructureTree.Location = New System.Drawing.Point(13, 27)
        Me.AssemblyStructureTree.Name = "treList"
        Me.AssemblyStructureTree.SelectedImageIndex = 0
        Me.AssemblyStructureTree.Size = New System.Drawing.Size(339, 421)
        Me.AssemblyStructureTree.TabIndex = 15
        '
        'imageList
        '
        Me.imageList.ImageStream = CType(resources.GetObject("imageList.ImageStream"), System.Windows.Forms.ImageListStreamer)
        Me.imageList.TransparentColor = System.Drawing.Color.Transparent
        Me.imageList.Images.SetKeyName(0, "")
        Me.imageList.Images.SetKeyName(1, "")
        '
        'grpBoxAssemblyFile
        '
        Me.grpBoxAssemblyFile.Controls.Add(Me.Label4)
        Me.grpBoxAssemblyFile.Controls.Add(Me.LODRep)
        Me.grpBoxAssemblyFile.Controls.Add(Me.txtFileName)
        Me.grpBoxAssemblyFile.Controls.Add(Me.cmdRefreshTree)
        Me.grpBoxAssemblyFile.Controls.Add(Me.cmdBrowse)
        Me.grpBoxAssemblyFile.Location = New System.Drawing.Point(16, 8)
        Me.grpBoxAssemblyFile.Name = "grpBoxAssemblyFile"
        Me.grpBoxAssemblyFile.Size = New System.Drawing.Size(363, 100)
        Me.grpBoxAssemblyFile.TabIndex = 18
        Me.grpBoxAssemblyFile.TabStop = False
        Me.grpBoxAssemblyFile.Text = "Assembly File:"
        '
        'AllRefs
        '
        Me.ShowFlatList.AutoSize = True
        Me.ShowFlatList.Location = New System.Drawing.Point(583, 431)
        Me.ShowFlatList.Name = "AllRefs"
        Me.ShowFlatList.Size = New System.Drawing.Size(104, 17)
        Me.ShowFlatList.TabIndex = 21
        Me.ShowFlatList.TabStop = True
        Me.ShowFlatList.Text = "All levels as a list"
        Me.ShowFlatList.UseVisualStyleBackColor = True
        '
        'Recurse
        '
        Me.ShowAllLevels.AutoSize = True
        Me.ShowAllLevels.Location = New System.Drawing.Point(492, 430)
        Me.ShowAllLevels.Name = "Recurse"
        Me.ShowAllLevels.Size = New System.Drawing.Size(66, 17)
        Me.ShowAllLevels.TabIndex = 20
        Me.ShowAllLevels.TabStop = True
        Me.ShowAllLevels.Text = "All levels"
        Me.ShowAllLevels.UseVisualStyleBackColor = True
        '
        'FirstLevel
        '
        Me.FirstLevel.AutoSize = True
        Me.FirstLevel.Checked = True
        Me.FirstLevel.Location = New System.Drawing.Point(372, 431)
        Me.FirstLevel.Name = "FirstLevel"
        Me.FirstLevel.Size = New System.Drawing.Size(90, 17)
        Me.FirstLevel.TabIndex = 19
        Me.FirstLevel.TabStop = True
        Me.FirstLevel.Text = "Only first level"
        Me.FirstLevel.UseVisualStyleBackColor = True
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(10, 44)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(155, 13)
        Me.Label4.TabIndex = 18
        Me.Label4.Text = "Level of Details Representation"
        '
        'LODRep
        '
        Me.LODRep.FormattingEnabled = True
        Me.LODRep.Location = New System.Drawing.Point(8, 63)
        Me.LODRep.Name = "LODRep"
        Me.LODRep.Size = New System.Drawing.Size(243, 21)
        Me.LODRep.TabIndex = 17
        '
        'txtFileName
        '
        Me.txtFileName.Location = New System.Drawing.Point(8, 16)
        Me.txtFileName.Name = "txtFileName"
        Me.txtFileName.Size = New System.Drawing.Size(243, 20)
        Me.txtFileName.TabIndex = 16
        '
        'cmdBrowse
        '
        Me.cmdBrowse.Location = New System.Drawing.Point(259, 13)
        Me.cmdBrowse.Name = "cmdBrowse"
        Me.cmdBrowse.Size = New System.Drawing.Size(88, 24)
        Me.cmdBrowse.TabIndex = 15
        Me.cmdBrowse.Text = "Browse..."
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Location = New System.Drawing.Point(367, 10)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(140, 13)
        Me.Label1.TabIndex = 21
        Me.Label1.Text = "Referenced Documents"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label2.Location = New System.Drawing.Point(716, 12)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(103, 13)
        Me.Label2.TabIndex = 22
        Me.Label2.Text = "Referenced Files"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label3.Location = New System.Drawing.Point(12, 9)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(115, 13)
        Me.Label3.TabIndex = 23
        Me.Label3.Text = "Assembly Structure"
        '
        'RefdDocs
        '
        Me.RefdDocs.Location = New System.Drawing.Point(371, 27)
        Me.RefdDocs.Name = "RefdDocs"
        Me.RefdDocs.Size = New System.Drawing.Size(328, 369)
        Me.RefdDocs.TabIndex = 26
        '
        'RefdFiles
        '
        Me.RefdFiles.Location = New System.Drawing.Point(716, 27)
        Me.RefdFiles.Name = "RefdFiles"
        Me.RefdFiles.Size = New System.Drawing.Size(308, 369)
        Me.RefdFiles.TabIndex = 27
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.Label5)
        Me.GroupBox1.Controls.Add(Me.ShowFlatList)
        Me.GroupBox1.Controls.Add(Me.ShowAllLevels)
        Me.GroupBox1.Controls.Add(Me.RefdFiles)
        Me.GroupBox1.Controls.Add(Me.FirstLevel)
        Me.GroupBox1.Controls.Add(Me.RefdDocs)
        Me.GroupBox1.Controls.Add(Me.Label3)
        Me.GroupBox1.Controls.Add(Me.Label2)
        Me.GroupBox1.Controls.Add(Me.Label1)
        Me.GroupBox1.Controls.Add(Me.AssemblyStructureTree)
        Me.GroupBox1.Location = New System.Drawing.Point(11, 109)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(1033, 459)
        Me.GroupBox1.TabIndex = 28
        Me.GroupBox1.TabStop = False
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label5.Location = New System.Drawing.Point(373, 402)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(154, 13)
        Me.Label5.TabIndex = 28
        Me.Label5.Text = "References display option"
        '
        'Label6
        '
        Me.Label6.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label6.Location = New System.Drawing.Point(730, 9)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(305, 83)
        Me.Label6.TabIndex = 29
        Me.Label6.Text = "The same file may correspond to more than " & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "one document. So in general there wil" &
            "l be " & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "same or fewer entries in the list " & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "of referenced files than the document" &
            "s. " & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10)
        Me.Label6.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'Label7
        '
        Me.Label7.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label7.Location = New System.Drawing.Point(383, 9)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(305, 83)
        Me.Label7.TabIndex = 30
        Me.Label7.Text = "The same document may correspond to more than " & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "one component occurrence. In gene" &
            "ral there will " & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "be same or fewer entries in the list " & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "of referenced documents " &
            "than the " & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "component occurrences."
        Me.Label7.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'frmAssemblyTree
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(1049, 578)
        Me.Controls.Add(Me.Label7)
        Me.Controls.Add(Me.Label6)
        Me.Controls.Add(Me.GroupBox1)
        Me.Controls.Add(Me.grpBoxAssemblyFile)
        Me.Name = "frmAssemblyTree"
        Me.Text = "AssemblyTree"
        Me.grpBoxAssemblyFile.ResumeLayout(False)
        Me.grpBoxAssemblyFile.PerformLayout()
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox1.PerformLayout()
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private objapprenticeServerApp As New Inventor.ApprenticeServerComponent

    Private Sub cmdClose_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)
        Me.Close()
    End Sub

    Private Sub cmdRefreshTree_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdRefreshTree.Click
        'check to see if a filename was specified and call the BuildTree function
        If txtFileName.Text <> "" Then
            BuildTree()
        End If
    End Sub

    'traverse the assembly structure and build the occurrence tree.
    Private Sub BuildTree()

        Try

            Me.Cursor = Cursors.WaitCursor
            'supress re-painting tree view until all nodes have been created
            AssemblyStructureTree.BeginUpdate()

            'clear the tree contents
            AssemblyStructureTree.Nodes.Clear()

            'open the specified file
            Dim objapprenticeServerDocument As Inventor.ApprenticeServerDocument
            Dim strDocName As String
            strDocName = objapprenticeServerApp.FileManager.GetFullDocumentName(txtFileName.Text, LODRep.Text)
            objapprenticeServerDocument = objapprenticeServerApp.Open(strDocName)
            If Err.Number Then
                MsgBox("Unable to open the specified file", MsgBoxStyle.OkOnly + MsgBoxStyle.Exclamation)
                Exit Sub
            End If

            'build a node for the top level assembly
            Dim objtopNode As New TreeNode(objapprenticeServerDocument.DisplayName, 0, 0)
            AssemblyStructureTree.Nodes.Add(objtopNode)
            objtopNode.Tag = objapprenticeServerDocument

            'call the recursive function to iterate through the assembly tree
            Call GetComponents(objapprenticeServerDocument.ComponentDefinition.Occurrences, objtopNode)

            'expand the node representing the top level assembly
            objtopNode.Expand()

            're-paint the tree view
            AssemblyStructureTree.EndUpdate()
            UpdateReferenceTrees(objapprenticeServerDocument)
            cmdRefreshTree.ForeColor = Color.Black
        Catch ex As Exception
            MessageBox.Show("Unable to open and get the assembly heirarchy of the specified file", "Invalid File", MessageBoxButtons.OK, MessageBoxIcon.Exclamation)
        Finally
            Me.Cursor = Cursors.Arrow
        End Try

    End Sub

    'get the components from the Occurrences collection and add it to the tree
    Private Sub GetComponents(ByVal inCollection As Inventor.ComponentOccurrences, ByRef objparentNode As TreeNode)

        'iterate through the components in the current collection
        Dim objcompOccurrence As Inventor.ComponentOccurrence
        Dim imageType As Integer

        For Each objcompOccurrence In inCollection
            If Not objcompOccurrence.Suppressed Then
                'determine if the current component is an assembly or part
                If objcompOccurrence.DefinitionDocumentType = Inventor.DocumentTypeEnum.kAssemblyDocumentObject Then
                    imageType = 0
                Else
                    imageType = 1
                End If

                'display the current component in the tree
                Dim objcurrentNode As New TreeNode(objcompOccurrence.Name, imageType, imageType)
                objparentNode.Nodes.Add(objcurrentNode)
                objcurrentNode.Tag = objcompOccurrence

                'recursively call this function for the suboccurrences of the current component
                Call GetComponents((objcompOccurrence.SubOccurrences), objcurrentNode)

                objcurrentNode.Expand()
            End If
        Next objcompOccurrence

    End Sub

    Private Sub AssemblyTree_Closed(ByVal sender As Object, ByVal e As System.EventArgs) Handles MyBase.Closed
        objapprenticeServerApp = Nothing
    End Sub

    Private Sub InvalidateTrees()
        cmdRefreshTree.ForeColor = Color.Red
    End Sub

    Private Sub txtFileName_KeyPress(ByVal sender As System.Object, ByVal e As System.Windows.Forms.KeyPressEventArgs)
        Dim keyAscii As Short = Asc(e.KeyChar)

        If keyAscii = 13 And txtFileName.Text <> "" Then
            keyAscii = 0
            InvalidateTrees()
        End If

    End Sub

    Private Sub txtFileName_Leave(ByVal sender As System.Object, ByVal e As System.EventArgs)
        If txtFileName.Text <> "" Then
            InvalidateTrees()
        End If
    End Sub

    Private Sub cmdBrowse_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdBrowse.Click

        'setup parameters for the open dialog
        With OpenFileDialog
            .InitialDirectory = objapprenticeServerApp.FileLocations.Workspace
            .Title = "Select Assembly file"
            .DefaultExt = ".iam"
            .Filter = "Inventor Assembly File (*.iam) | *.iam"
            .ShowDialog()
        End With

        'write the filename to the text box
        txtFileName.Text = OpenFileDialog.FileName

        ' Fix DID1263714, exit this function if the user input an empty file name.
        ' This happens when the user select Cancel button on FileDialog.
        If txtFileName.Text = "" Then
            Exit Sub
        End If

        Dim strReps As String
        LODRep.Items.Clear()
        For Each strReps In objapprenticeServerApp.FileManager.GetLevelOfDetailRepresentations(txtFileName.Text)
            LODRep.Items.Add(strReps)
        Next
        InvalidateTrees()
        LODRep.SelectedIndex = 0
    End Sub

    ''' <summary>
    ''' Updates the reference documents and reference files trees
    ''' </summary>
    ''' <param name="oApprenticeDoc"></param>
    ''' <remarks></remarks>
    Private Sub UpdateReferenceTrees(ByVal oApprenticeDoc As Inventor.ApprenticeServerDocument)
        RefdFiles.Nodes.Clear()
        RefdFiles.BeginUpdate()
        Dim TopTreeNode As TreeNode
        Dim NewTreeNode As TreeNode
        TopTreeNode = RefdFiles.Nodes.Add(oApprenticeDoc.File.FullFileName)
        If Not ShowFlatList.Checked Then
            UpdateRefdFilesTree(oApprenticeDoc.File, TopTreeNode)
        Else
            Dim aReferencedFile As Inventor.File
            For Each aReferencedFile In oApprenticeDoc.File.AllReferencedFiles
                NewTreeNode = TopTreeNode.Nodes.Add(aReferencedFile.FullFileName)
            Next
        End If
        TopTreeNode.ExpandAll()
        RefdFiles.EndUpdate()

        RefdDocs.Nodes.Clear()
        RefdDocs.BeginUpdate()
        TopTreeNode = RefdDocs.Nodes.Add(oApprenticeDoc.FullDocumentName)
        If Not ShowFlatList.Checked Then
            UpdateRefdDocsTree(oApprenticeDoc, TopTreeNode)
        Else
            Dim aReferencedDocument As Inventor.ApprenticeServerDocument
            For Each aReferencedDocument In oApprenticeDoc.AllReferencedDocuments
                NewTreeNode = TopTreeNode.Nodes.Add(aReferencedDocument.FullDocumentName)
            Next
        End If
        TopTreeNode.ExpandAll()
        RefdDocs.EndUpdate()
    End Sub
    ''' <summary>
    ''' Adds the nodes to the reference documents tree for the given Inventor document
    ''' </summary>
    ''' <param name="ThisDocument">Given Inventor document</param>
    ''' <param name="ThisNode">Tree node for this document</param>
    ''' <remarks></remarks>
    Private Sub UpdateRefdDocsTree(ByVal ThisDocument As Inventor.ApprenticeServerDocument, ByVal ThisNode As TreeNode)
        Dim oRefdDocDesc As Inventor.DocumentDescriptor
        For Each oRefdDocDesc In ThisDocument.ReferencedDocumentDescriptors
            Dim NewNode As TreeNode
            NewNode = ThisNode.Nodes.Add(oRefdDocDesc.FullDocumentName)
            If ShowAllLevels.Checked Then
                Try
                    If Not oRefdDocDesc.ReferencedDocument Is Nothing Then
                        UpdateRefdDocsTree(oRefdDocDesc.ReferencedDocument, NewNode)
                    End If
                    If NewNode.Nodes.Count = 0 Then
                        NewNode.ForeColor = Color.Blue
                    End If
                Catch
                    NewNode.Text = NewNode.Text & "<document not loaded>"
                    NewNode.ForeColor = Color.Red
                End Try
            End If
        Next
        If ThisNode.Nodes.Count = 0 Then
            ThisNode.ForeColor = Color.Blue
        End If
    End Sub
    ''' <summary>
    ''' Adds the nodes to the reference files tree for the given Inventor file
    ''' </summary>
    ''' <param name="ThisFile">Given Inventor File</param>
    ''' <param name="ThisNode">Tree node for this file</param>
    ''' <remarks></remarks>
    Private Sub UpdateRefdFilesTree(ByVal ThisFile As Inventor.File, ByVal ThisNode As TreeNode)
        Dim oRefdFileDesc As Inventor.FileDescriptor
        For Each oRefdFileDesc In ThisFile.ReferencedFileDescriptors
            Dim NewNode As TreeNode
            NewNode = ThisNode.Nodes.Add(oRefdFileDesc.FullFileName)
            If ShowAllLevels.Checked Then
                Try
                    If Not oRefdFileDesc.ReferencedFile Is Nothing Then
                        UpdateRefdFilesTree(oRefdFileDesc.ReferencedFile, NewNode)
                    End If
                    If NewNode.Nodes.Count = 0 Then
                        NewNode.ForeColor = Color.Blue
                    End If
                Catch
                    NewNode.Text = NewNode.Text & "<Failed to get the file>"
                    NewNode.ForeColor = Color.Red
                End Try
            End If
        Next
        If ThisNode.Nodes.Count = 0 Then
            ThisNode.ForeColor = Color.Blue
        End If
    End Sub

    Private Sub LODRep_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles LODRep.SelectedIndexChanged
        'check to see if a filename was specified and call the BuildTree function
        If txtFileName.Text <> "" Then
            BuildTree()
        End If
    End Sub

    Private Sub FirstLevel_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles FirstLevel.CheckedChanged
        'check to see if a filename was specified and call the BuildTree function
        If txtFileName.Text <> "" Then
            BuildTree()
        End If
    End Sub

    Private Sub Recurse_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ShowAllLevels.CheckedChanged
        'check to see if a filename was specified and call the BuildTree function
        If txtFileName.Text <> "" Then
            BuildTree()
        End If
    End Sub

    Private Sub AllRefs_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ShowFlatList.CheckedChanged
        'check to see if a filename was specified and call the BuildTree function
        If txtFileName.Text <> "" Then
            BuildTree()
        End If
    End Sub
End Class
