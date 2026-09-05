<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class FrmFeatureStatistics
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(FrmFeatureStatistics))
        Me.cmdRebuild = New System.Windows.Forms.Button()
        Me.cmdOK = New System.Windows.Forms.Button()
        Me.cmdSave = New System.Windows.Forms.Button()
        Me.cmdNumInfo = New System.Windows.Forms.Button()
        Me.checkIgnSuppressFeatures = New System.Windows.Forms.CheckBox()
        Me.checkIgnWkFeatures = New System.Windows.Forms.CheckBox()
        Me.checkIgnSks = New System.Windows.Forms.CheckBox()
        Me.menuCopy = New System.Windows.Forms.ToolStripMenuItem()
        Me.ListViewInfo = New System.Windows.Forms.ListView()
        Me.lblFileName = New System.Windows.Forms.Label()
        Me.menuEdit = New System.Windows.Forms.ToolStripMenuItem()
        Me.menuSelectAll = New System.Windows.Forms.ToolStripMenuItem()
        Me.lblFeaturesNum = New System.Windows.Forms.Label()
        Me.lblSolidsCount = New System.Windows.Forms.Label()
        Me.lblRebuildTime = New System.Windows.Forms.Label()
        Me.lblTime = New System.Windows.Forms.Label()
        Me.lblSolidsNumCount = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.Label1 = New System.Windows.Forms.Label()
        Me.lblFileNameText = New System.Windows.Forms.Label()
        Me.lblFeatureTypes = New System.Windows.Forms.Label()
        Me.lblFeatureTypesCount = New System.Windows.Forms.Label()
        Me.lblSurfNums = New System.Windows.Forms.Label()
        Me.lblSurfNumsCount = New System.Windows.Forms.Label()
        Me.lblFeatureNumsCount = New System.Windows.Forms.Label()
        Me.MainMenu1 = New System.Windows.Forms.MenuStrip()
        Me.MainMenu1.SuspendLayout()
        Me.SuspendLayout()
        '
        'cmdRebuild
        '
        Me.cmdRebuild.BackColor = System.Drawing.SystemColors.Control
        Me.cmdRebuild.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdRebuild.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdRebuild.Location = New System.Drawing.Point(124, 518)
        Me.cmdRebuild.Name = "cmdRebuild"
        Me.cmdRebuild.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdRebuild.Size = New System.Drawing.Size(70, 30)
        Me.cmdRebuild.TabIndex = 6
        Me.cmdRebuild.Text = "Rebuild"
        Me.cmdRebuild.UseVisualStyleBackColor = False
        '
        'cmdOK
        '
        Me.cmdOK.BackColor = System.Drawing.SystemColors.Control
        Me.cmdOK.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdOK.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdOK.Location = New System.Drawing.Point(321, 518)
        Me.cmdOK.Name = "cmdOK"
        Me.cmdOK.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdOK.Size = New System.Drawing.Size(70, 30)
        Me.cmdOK.TabIndex = 8
        Me.cmdOK.Text = "OK"
        Me.cmdOK.UseVisualStyleBackColor = False
        '
        'cmdSave
        '
        Me.cmdSave.BackColor = System.Drawing.SystemColors.Control
        Me.cmdSave.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdSave.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdSave.Location = New System.Drawing.Point(225, 518)
        Me.cmdSave.Name = "cmdSave"
        Me.cmdSave.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdSave.Size = New System.Drawing.Size(70, 30)
        Me.cmdSave.TabIndex = 7
        Me.cmdSave.Text = "Save"
        Me.cmdSave.UseVisualStyleBackColor = False
        '
        'cmdNumInfo
        '
        Me.cmdNumInfo.BackColor = System.Drawing.SystemColors.Control
        Me.cmdNumInfo.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdNumInfo.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdNumInfo.Location = New System.Drawing.Point(25, 518)
        Me.cmdNumInfo.Name = "cmdNumInfo"
        Me.cmdNumInfo.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdNumInfo.Size = New System.Drawing.Size(70, 30)
        Me.cmdNumInfo.TabIndex = 5
        Me.cmdNumInfo.Text = "NumInfo"
        Me.cmdNumInfo.UseVisualStyleBackColor = False
        '
        'checkIgnSuppressFeatures
        '
        Me.checkIgnSuppressFeatures.BackColor = System.Drawing.SystemColors.Control
        Me.checkIgnSuppressFeatures.Cursor = System.Windows.Forms.Cursors.Default
        Me.checkIgnSuppressFeatures.ForeColor = System.Drawing.SystemColors.ControlText
        Me.checkIgnSuppressFeatures.Location = New System.Drawing.Point(26, 406)
        Me.checkIgnSuppressFeatures.Name = "checkIgnSuppressFeatures"
        Me.checkIgnSuppressFeatures.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.checkIgnSuppressFeatures.Size = New System.Drawing.Size(361, 21)
        Me.checkIgnSuppressFeatures.TabIndex = 2
        Me.checkIgnSuppressFeatures.Text = "Ignore the Suppressed Features"
        Me.checkIgnSuppressFeatures.UseVisualStyleBackColor = False
        '
        'checkIgnWkFeatures
        '
        Me.checkIgnWkFeatures.BackColor = System.Drawing.SystemColors.Control
        Me.checkIgnWkFeatures.Cursor = System.Windows.Forms.Cursors.Default
        Me.checkIgnWkFeatures.ForeColor = System.Drawing.SystemColors.ControlText
        Me.checkIgnWkFeatures.Location = New System.Drawing.Point(26, 441)
        Me.checkIgnWkFeatures.Name = "checkIgnWkFeatures"
        Me.checkIgnWkFeatures.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.checkIgnWkFeatures.Size = New System.Drawing.Size(361, 21)
        Me.checkIgnWkFeatures.TabIndex = 3
        Me.checkIgnWkFeatures.Text = "Ignore the Work Features (Plane, Axis and Point)"
        Me.checkIgnWkFeatures.UseVisualStyleBackColor = False
        '
        'checkIgnSks
        '
        Me.checkIgnSks.BackColor = System.Drawing.SystemColors.Control
        Me.checkIgnSks.Cursor = System.Windows.Forms.Cursors.Default
        Me.checkIgnSks.ForeColor = System.Drawing.SystemColors.ControlText
        Me.checkIgnSks.Location = New System.Drawing.Point(26, 476)
        Me.checkIgnSks.Name = "checkIgnSks"
        Me.checkIgnSks.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.checkIgnSks.Size = New System.Drawing.Size(361, 21)
        Me.checkIgnSks.TabIndex = 4
        Me.checkIgnSks.Text = "Ignore the 2D and 3D Sketches"
        Me.checkIgnSks.UseVisualStyleBackColor = False
        '
        'menuCopy
        '
        Me.menuCopy.Name = "menuCopy"
        Me.menuCopy.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.C), System.Windows.Forms.Keys)
        Me.menuCopy.Size = New System.Drawing.Size(188, 24)
        Me.menuCopy.Text = "&Copy"
        '
        'ListViewInfo
        '
        Me.ListViewInfo.AllowColumnReorder = True
        Me.ListViewInfo.BackColor = System.Drawing.SystemColors.Window
        Me.ListViewInfo.ForeColor = System.Drawing.SystemColors.WindowText
        Me.ListViewInfo.FullRowSelect = True
        Me.ListViewInfo.LabelEdit = True
        Me.ListViewInfo.Location = New System.Drawing.Point(25, 141)
        Me.ListViewInfo.Name = "ListViewInfo"
        Me.ListViewInfo.Size = New System.Drawing.Size(360, 245)
        Me.ListViewInfo.TabIndex = 37
        Me.ListViewInfo.UseCompatibleStateImageBehavior = False
        Me.ListViewInfo.View = System.Windows.Forms.View.Details
        '
        'lblFileName
        '
        Me.lblFileName.AutoSize = True
        Me.lblFileName.BackColor = System.Drawing.SystemColors.Control
        Me.lblFileName.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblFileName.ForeColor = System.Drawing.SystemColors.ControlText
        Me.lblFileName.Location = New System.Drawing.Point(26, 38)
        Me.lblFileName.Name = "lblFileName"
        Me.lblFileName.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblFileName.Size = New System.Drawing.Size(75, 17)
        Me.lblFileName.TabIndex = 40
        Me.lblFileName.Text = "File Name:"
        '
        'menuEdit
        '
        Me.menuEdit.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.menuCopy, Me.menuSelectAll})
        Me.menuEdit.Name = "menuEdit"
        Me.menuEdit.Size = New System.Drawing.Size(47, 24)
        Me.menuEdit.Text = "&Edit"
        Me.menuEdit.Visible = False
        '
        'menuSelectAll
        '
        Me.menuSelectAll.Name = "menuSelectAll"
        Me.menuSelectAll.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.A), System.Windows.Forms.Keys)
        Me.menuSelectAll.Size = New System.Drawing.Size(188, 24)
        Me.menuSelectAll.Text = "&SelectAll"
        '
        'lblFeaturesNum
        '
        Me.lblFeaturesNum.AutoSize = True
        Me.lblFeaturesNum.BackColor = System.Drawing.SystemColors.Control
        Me.lblFeaturesNum.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblFeaturesNum.ForeColor = System.Drawing.SystemColors.ControlText
        Me.lblFeaturesNum.Location = New System.Drawing.Point(26, 71)
        Me.lblFeaturesNum.Name = "lblFeaturesNum"
        Me.lblFeaturesNum.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblFeaturesNum.Size = New System.Drawing.Size(110, 17)
        Me.lblFeaturesNum.TabIndex = 39
        Me.lblFeaturesNum.Text = "No. of Features:"
        '
        'lblSolidsCount
        '
        Me.lblSolidsCount.AutoSize = True
        Me.lblSolidsCount.BackColor = System.Drawing.SystemColors.Control
        Me.lblSolidsCount.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblSolidsCount.ForeColor = System.Drawing.SystemColors.ControlText
        Me.lblSolidsCount.Location = New System.Drawing.Point(26, 103)
        Me.lblSolidsCount.Name = "lblSolidsCount"
        Me.lblSolidsCount.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblSolidsCount.Size = New System.Drawing.Size(92, 17)
        Me.lblSolidsCount.TabIndex = 38
        Me.lblSolidsCount.Text = "No. of Solids:"
        '
        'lblRebuildTime
        '
        Me.lblRebuildTime.AutoSize = True
        Me.lblRebuildTime.BackColor = System.Drawing.SystemColors.Control
        Me.lblRebuildTime.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblRebuildTime.ForeColor = System.Drawing.SystemColors.ControlText
        Me.lblRebuildTime.Location = New System.Drawing.Point(226, 38)
        Me.lblRebuildTime.Name = "lblRebuildTime"
        Me.lblRebuildTime.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblRebuildTime.Size = New System.Drawing.Size(102, 17)
        Me.lblRebuildTime.TabIndex = 33
        Me.lblRebuildTime.Text = "Rebuild Times:"
        '
        'lblTime
        '
        Me.lblTime.AutoSize = True
        Me.lblTime.BackColor = System.Drawing.SystemColors.Control
        Me.lblTime.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblTime.ForeColor = System.Drawing.SystemColors.ControlText
        Me.lblTime.Location = New System.Drawing.Point(356, 38)
        Me.lblTime.Name = "lblTime"
        Me.lblTime.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblTime.Size = New System.Drawing.Size(16, 17)
        Me.lblTime.TabIndex = 32
        Me.lblTime.Text = "0"
        '
        'lblSolidsNumCount
        '
        Me.lblSolidsNumCount.AutoSize = True
        Me.lblSolidsNumCount.BackColor = System.Drawing.SystemColors.Control
        Me.lblSolidsNumCount.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblSolidsNumCount.ForeColor = System.Drawing.SystemColors.ControlText
        Me.lblSolidsNumCount.Location = New System.Drawing.Point(135, 103)
        Me.lblSolidsNumCount.Name = "lblSolidsNumCount"
        Me.lblSolidsNumCount.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblSolidsNumCount.Size = New System.Drawing.Size(16, 17)
        Me.lblSolidsNumCount.TabIndex = 31
        Me.lblSolidsNumCount.Text = "0"
        Me.lblSolidsNumCount.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.BackColor = System.Drawing.SystemColors.Control
        Me.Label2.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label2.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label2.Location = New System.Drawing.Point(-4, 30)
        Me.Label2.Name = "Label2"
        Me.Label2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label2.Size = New System.Drawing.Size(0, 17)
        Me.Label2.TabIndex = 30
        Me.Label2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.BackColor = System.Drawing.SystemColors.Control
        Me.Label1.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label1.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label1.Location = New System.Drawing.Point(-4, 30)
        Me.Label1.Name = "Label1"
        Me.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label1.Size = New System.Drawing.Size(0, 17)
        Me.Label1.TabIndex = 29
        Me.Label1.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblFileNameText
        '
        Me.lblFileNameText.BackColor = System.Drawing.SystemColors.Control
        Me.lblFileNameText.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblFileNameText.ForeColor = System.Drawing.SystemColors.ControlText
        Me.lblFileNameText.Location = New System.Drawing.Point(107, 38)
        Me.lblFileNameText.MaximumSize = New System.Drawing.Size(108, 17)
        Me.lblFileNameText.MinimumSize = New System.Drawing.Size(50, 17)
        Me.lblFileNameText.Name = "lblFileNameText"
        Me.lblFileNameText.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblFileNameText.Size = New System.Drawing.Size(104, 17)
        Me.lblFileNameText.TabIndex = 28
        Me.lblFileNameText.Text = "        "
        Me.lblFileNameText.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
        '
        'lblFeatureTypes
        '
        Me.lblFeatureTypes.AutoSize = True
        Me.lblFeatureTypes.BackColor = System.Drawing.SystemColors.Control
        Me.lblFeatureTypes.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblFeatureTypes.ForeColor = System.Drawing.SystemColors.ControlText
        Me.lblFeatureTypes.Location = New System.Drawing.Point(226, 70)
        Me.lblFeatureTypes.Name = "lblFeatureTypes"
        Me.lblFeatureTypes.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblFeatureTypes.Size = New System.Drawing.Size(127, 17)
        Me.lblFeatureTypes.TabIndex = 27
        Me.lblFeatureTypes.Text = "Types of Features:"
        '
        'lblFeatureTypesCount
        '
        Me.lblFeatureTypesCount.AutoSize = True
        Me.lblFeatureTypesCount.BackColor = System.Drawing.SystemColors.Control
        Me.lblFeatureTypesCount.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblFeatureTypesCount.ForeColor = System.Drawing.SystemColors.ControlText
        Me.lblFeatureTypesCount.Location = New System.Drawing.Point(356, 71)
        Me.lblFeatureTypesCount.Name = "lblFeatureTypesCount"
        Me.lblFeatureTypesCount.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblFeatureTypesCount.Size = New System.Drawing.Size(16, 17)
        Me.lblFeatureTypesCount.TabIndex = 26
        Me.lblFeatureTypesCount.Text = "0"
        Me.lblFeatureTypesCount.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
        '
        'lblSurfNums
        '
        Me.lblSurfNums.AutoSize = True
        Me.lblSurfNums.BackColor = System.Drawing.SystemColors.Control
        Me.lblSurfNums.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblSurfNums.ForeColor = System.Drawing.SystemColors.ControlText
        Me.lblSurfNums.Location = New System.Drawing.Point(227, 103)
        Me.lblSurfNums.Name = "lblSurfNums"
        Me.lblSurfNums.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblSurfNums.Size = New System.Drawing.Size(110, 17)
        Me.lblSurfNums.TabIndex = 25
        Me.lblSurfNums.Text = "No. of Surfaces:"
        '
        'lblSurfNumsCount
        '
        Me.lblSurfNumsCount.AutoSize = True
        Me.lblSurfNumsCount.BackColor = System.Drawing.SystemColors.Control
        Me.lblSurfNumsCount.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblSurfNumsCount.ForeColor = System.Drawing.SystemColors.ControlText
        Me.lblSurfNumsCount.Location = New System.Drawing.Point(355, 104)
        Me.lblSurfNumsCount.Name = "lblSurfNumsCount"
        Me.lblSurfNumsCount.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblSurfNumsCount.Size = New System.Drawing.Size(16, 17)
        Me.lblSurfNumsCount.TabIndex = 24
        Me.lblSurfNumsCount.Text = "0"
        Me.lblSurfNumsCount.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
        '
        'lblFeatureNumsCount
        '
        Me.lblFeatureNumsCount.AutoSize = True
        Me.lblFeatureNumsCount.BackColor = System.Drawing.SystemColors.Control
        Me.lblFeatureNumsCount.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblFeatureNumsCount.ForeColor = System.Drawing.SystemColors.ControlText
        Me.lblFeatureNumsCount.Location = New System.Drawing.Point(135, 70)
        Me.lblFeatureNumsCount.Name = "lblFeatureNumsCount"
        Me.lblFeatureNumsCount.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblFeatureNumsCount.Size = New System.Drawing.Size(16, 17)
        Me.lblFeatureNumsCount.TabIndex = 23
        Me.lblFeatureNumsCount.Text = "0"
        Me.lblFeatureNumsCount.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
        '
        'MainMenu1
        '
        Me.MainMenu1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.menuEdit})
        Me.MainMenu1.Location = New System.Drawing.Point(0, 0)
        Me.MainMenu1.Name = "MainMenu1"
        Me.MainMenu1.Size = New System.Drawing.Size(432, 24)
        Me.MainMenu1.TabIndex = 45
        '
        'FrmFeatureStatistics
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(8.0!, 16.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(432, 565)
        Me.Controls.Add(Me.cmdRebuild)
        Me.Controls.Add(Me.cmdOK)
        Me.Controls.Add(Me.cmdSave)
        Me.Controls.Add(Me.cmdNumInfo)
        Me.Controls.Add(Me.checkIgnSuppressFeatures)
        Me.Controls.Add(Me.checkIgnWkFeatures)
        Me.Controls.Add(Me.checkIgnSks)
        Me.Controls.Add(Me.ListViewInfo)
        Me.Controls.Add(Me.lblFileName)
        Me.Controls.Add(Me.lblFeaturesNum)
        Me.Controls.Add(Me.lblSolidsCount)
        Me.Controls.Add(Me.lblRebuildTime)
        Me.Controls.Add(Me.lblTime)
        Me.Controls.Add(Me.lblSolidsNumCount)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.lblFileNameText)
        Me.Controls.Add(Me.lblFeatureTypes)
        Me.Controls.Add(Me.lblFeatureTypesCount)
        Me.Controls.Add(Me.lblSurfNums)
        Me.Controls.Add(Me.lblSurfNumsCount)
        Me.Controls.Add(Me.lblFeatureNumsCount)
        Me.Controls.Add(Me.MainMenu1)
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.Name = "FrmFeatureStatistics"
        Me.Text = "Feature Statistics"
        Me.MainMenu1.ResumeLayout(False)
        Me.MainMenu1.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Public WithEvents cmdRebuild As System.Windows.Forms.Button
    Public WithEvents cmdOK As System.Windows.Forms.Button
    Public WithEvents cmdSave As System.Windows.Forms.Button
    Public WithEvents cmdNumInfo As System.Windows.Forms.Button
    Public WithEvents checkIgnSuppressFeatures As System.Windows.Forms.CheckBox
    Public WithEvents checkIgnWkFeatures As System.Windows.Forms.CheckBox
    Public WithEvents checkIgnSks As System.Windows.Forms.CheckBox
    Public WithEvents menuCopy As System.Windows.Forms.ToolStripMenuItem
    Public WithEvents ListViewInfo As System.Windows.Forms.ListView
    Public WithEvents lblFileName As System.Windows.Forms.Label
    Public WithEvents menuEdit As System.Windows.Forms.ToolStripMenuItem
    Public WithEvents menuSelectAll As System.Windows.Forms.ToolStripMenuItem
    Public WithEvents lblFeaturesNum As System.Windows.Forms.Label
    Public WithEvents lblSolidsCount As System.Windows.Forms.Label
    Public WithEvents lblRebuildTime As System.Windows.Forms.Label
    Public WithEvents lblTime As System.Windows.Forms.Label
    Public WithEvents lblSolidsNumCount As System.Windows.Forms.Label
    Public WithEvents Label2 As System.Windows.Forms.Label
    Public WithEvents ToolTip1 As System.Windows.Forms.ToolTip
    Public WithEvents Label1 As System.Windows.Forms.Label
    Public WithEvents lblFileNameText As System.Windows.Forms.Label
    Public WithEvents lblFeatureTypes As System.Windows.Forms.Label
    Public WithEvents lblFeatureTypesCount As System.Windows.Forms.Label
    Public WithEvents lblSurfNums As System.Windows.Forms.Label
    Public WithEvents lblSurfNumsCount As System.Windows.Forms.Label
    Public WithEvents lblFeatureNumsCount As System.Windows.Forms.Label
    Public WithEvents MainMenu1 As System.Windows.Forms.MenuStrip
End Class
