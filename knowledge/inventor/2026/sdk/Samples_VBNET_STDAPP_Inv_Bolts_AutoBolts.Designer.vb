<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> Partial Class frmAutoBolts
#Region "Windows Form Designer generated code "
	<System.Diagnostics.DebuggerNonUserCode()> Public Sub New()
		MyBase.New()
		'This call is required by the Windows Form Designer.
		InitializeComponent()
	End Sub
	'Form overrides dispose to clean up the component list.
	<System.Diagnostics.DebuggerNonUserCode()> Protected Overloads Overrides Sub Dispose(ByVal Disposing As Boolean)
		If Disposing Then
			If Not components Is Nothing Then
				components.Dispose()
			End If
		End If
		MyBase.Dispose(Disposing)
	End Sub
	'Required by the Windows Form Designer
	Private components As System.ComponentModel.IContainer
	Public ToolTip1 As System.Windows.Forms.ToolTip
	Public WithEvents Picture1 As System.Windows.Forms.PictureBox
	Public WithEvents cmdBrowse As System.Windows.Forms.Button
	Public WithEvents txtLibraryPath As System.Windows.Forms.TextBox
	Public cmnLibraryPathOpen As System.Windows.Forms.OpenFileDialog
	Public cmnLibraryPathSave As System.Windows.Forms.SaveFileDialog
	Public cmnLibraryPathFont As System.Windows.Forms.FontDialog
	Public cmnLibraryPathColor As System.Windows.Forms.ColorDialog
	Public cmnLibraryPathPrint As System.Windows.Forms.PrintDialog
	Public WithEvents cmdCancel As System.Windows.Forms.Button
	Public WithEvents cmdPlaceBolts As System.Windows.Forms.Button
	Public WithEvents imgIcons As System.Windows.Forms.ImageList
	Public WithEvents treAssembly As System.Windows.Forms.TreeView
	Public WithEvents Label2 As System.Windows.Forms.Label
	Public WithEvents Label1 As System.Windows.Forms.Label
	'NOTE: The following procedure is required by the Windows Form Designer
	'It can be modified using the Windows Form Designer.
	'Do not modify it using the code editor.
	<System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
		Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmAutoBolts))
		Me.components = New System.ComponentModel.Container()
		Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
		Me.Picture1 = New System.Windows.Forms.PictureBox
		Me.cmdBrowse = New System.Windows.Forms.Button
		Me.txtLibraryPath = New System.Windows.Forms.TextBox
		Me.cmnLibraryPathOpen = New System.Windows.Forms.OpenFileDialog
		Me.cmnLibraryPathSave = New System.Windows.Forms.SaveFileDialog
		Me.cmnLibraryPathFont = New System.Windows.Forms.FontDialog
		Me.cmnLibraryPathColor = New System.Windows.Forms.ColorDialog
		Me.cmnLibraryPathPrint = New System.Windows.Forms.PrintDialog
		Me.cmdCancel = New System.Windows.Forms.Button
		Me.cmdPlaceBolts = New System.Windows.Forms.Button
		Me.imgIcons = New System.Windows.Forms.ImageList
		Me.treAssembly = New System.Windows.Forms.TreeView
		Me.Label2 = New System.Windows.Forms.Label
		Me.Label1 = New System.Windows.Forms.Label
		Me.SuspendLayout()
		Me.ToolTip1.Active = True
		Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
		Me.Text = "Place Automatic Bolts"
		Me.ClientSize = New System.Drawing.Size(381, 472)
		Me.Location = New System.Drawing.Point(4, 28)
		Me.MaximizeBox = False
		Me.MinimizeBox = False
		Me.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None
		Me.BackgroundImage = CType(resources.GetObject("frmAutoBolts.BackgroundImage"), System.Drawing.Image)
		Me.StartPosition = System.Windows.Forms.FormStartPosition.WindowsDefaultLocation
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.BackColor = System.Drawing.SystemColors.Control
		Me.ControlBox = True
		Me.Enabled = True
		Me.KeyPreview = False
		Me.Cursor = System.Windows.Forms.Cursors.Default
		Me.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.ShowInTaskbar = True
		Me.HelpButton = False
		Me.WindowState = System.Windows.Forms.FormWindowState.Normal
		Me.Name = "frmAutoBolts"
		Me.Picture1.Size = New System.Drawing.Size(68, 121)
		Me.Picture1.Location = New System.Drawing.Point(285, 185)
		Me.Picture1.Image = CType(resources.GetObject("Picture1.Image"), System.Drawing.Image)
		Me.Picture1.TabIndex = 7
		Me.Picture1.Dock = System.Windows.Forms.DockStyle.None
		Me.Picture1.BackColor = System.Drawing.SystemColors.Control
		Me.Picture1.CausesValidation = True
		Me.Picture1.Enabled = True
		Me.Picture1.ForeColor = System.Drawing.SystemColors.ControlText
		Me.Picture1.Cursor = System.Windows.Forms.Cursors.Default
		Me.Picture1.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.Picture1.TabStop = True
		Me.Picture1.Visible = True
		Me.Picture1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize
		Me.Picture1.BorderStyle = System.Windows.Forms.BorderStyle.None
		Me.Picture1.Name = "Picture1"
		Me.cmdBrowse.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.cmdBrowse.Text = "Browse..."
		Me.cmdBrowse.Size = New System.Drawing.Size(72, 27)
		Me.cmdBrowse.Location = New System.Drawing.Point(305, 440)
		Me.cmdBrowse.TabIndex = 6
		Me.cmdBrowse.BackColor = System.Drawing.SystemColors.Control
		Me.cmdBrowse.CausesValidation = True
		Me.cmdBrowse.Enabled = True
		Me.cmdBrowse.ForeColor = System.Drawing.SystemColors.ControlText
		Me.cmdBrowse.Cursor = System.Windows.Forms.Cursors.Default
		Me.cmdBrowse.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.cmdBrowse.TabStop = True
		Me.cmdBrowse.Name = "cmdBrowse"
		Me.txtLibraryPath.AutoSize = False
		Me.txtLibraryPath.Size = New System.Drawing.Size(297, 27)
		Me.txtLibraryPath.Location = New System.Drawing.Point(5, 440)
		Me.txtLibraryPath.TabIndex = 4
		Me.txtLibraryPath.AcceptsReturn = True
		Me.txtLibraryPath.TextAlign = System.Windows.Forms.HorizontalAlignment.Left
		Me.txtLibraryPath.BackColor = System.Drawing.SystemColors.Window
		Me.txtLibraryPath.CausesValidation = True
		Me.txtLibraryPath.Enabled = True
		Me.txtLibraryPath.ForeColor = System.Drawing.SystemColors.WindowText
		Me.txtLibraryPath.HideSelection = True
		Me.txtLibraryPath.ReadOnly = False
		Me.txtLibraryPath.Maxlength = 0
		Me.txtLibraryPath.Cursor = System.Windows.Forms.Cursors.IBeam
		Me.txtLibraryPath.MultiLine = False
		Me.txtLibraryPath.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.txtLibraryPath.ScrollBars = System.Windows.Forms.ScrollBars.None
		Me.txtLibraryPath.TabStop = True
		Me.txtLibraryPath.Visible = True
		Me.txtLibraryPath.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
		Me.txtLibraryPath.Name = "txtLibraryPath"
		Me.cmdCancel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.cmdCancel.Text = "Cancel"
		Me.cmdCancel.Size = New System.Drawing.Size(102, 37)
		Me.cmdCancel.Location = New System.Drawing.Point(275, 45)
		Me.cmdCancel.TabIndex = 2
		Me.cmdCancel.BackColor = System.Drawing.SystemColors.Control
		Me.cmdCancel.CausesValidation = True
		Me.cmdCancel.Enabled = True
		Me.cmdCancel.ForeColor = System.Drawing.SystemColors.ControlText
		Me.cmdCancel.Cursor = System.Windows.Forms.Cursors.Default
		Me.cmdCancel.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.cmdCancel.TabStop = True
		Me.cmdCancel.Name = "cmdCancel"
		Me.cmdPlaceBolts.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.cmdPlaceBolts.Text = "Place Bolts"
		Me.cmdPlaceBolts.Enabled = False
		Me.cmdPlaceBolts.Size = New System.Drawing.Size(102, 37)
		Me.cmdPlaceBolts.Location = New System.Drawing.Point(275, 5)
		Me.cmdPlaceBolts.TabIndex = 1
		Me.cmdPlaceBolts.BackColor = System.Drawing.SystemColors.Control
		Me.cmdPlaceBolts.CausesValidation = True
		Me.cmdPlaceBolts.ForeColor = System.Drawing.SystemColors.ControlText
		Me.cmdPlaceBolts.Cursor = System.Windows.Forms.Cursors.Default
		Me.cmdPlaceBolts.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.cmdPlaceBolts.TabStop = True
		Me.cmdPlaceBolts.Name = "cmdPlaceBolts"
		Me.imgIcons.ImageSize = New System.Drawing.Size(16, 16)
		Me.imgIcons.TransparentColor = System.Drawing.Color.FromARGB(192, 192, 192)
		Me.imgIcons.ImageStream = CType(resources.GetObject("imgIcons.ImageStream"), System.Windows.Forms.ImageListStreamer)
		Me.imgIcons.Images.SetKeyName(0, "")
		Me.imgIcons.Images.SetKeyName(1, "")
		Me.treAssembly.LabelEdit = True
		Me.treAssembly.CausesValidation = True
		Me.treAssembly.Size = New System.Drawing.Size(267, 412)
		Me.treAssembly.Location = New System.Drawing.Point(5, 5)
		Me.treAssembly.TabIndex = 0
		Me.treAssembly.Indent = 45
		Me.treAssembly.ImageList = imgIcons
		Me.treAssembly.BorderStyle = System.Windows.Forms.BorderStyle.None
		Me.treAssembly.Name = "treAssembly"
		Me.Label2.Text = "Bolt Library Path:"
		Me.Label2.Size = New System.Drawing.Size(112, 22)
		Me.Label2.Location = New System.Drawing.Point(5, 420)
		Me.Label2.TabIndex = 5
		Me.Label2.TextAlign = System.Drawing.ContentAlignment.TopLeft
		Me.Label2.BackColor = System.Drawing.SystemColors.Control
		Me.Label2.Enabled = True
		Me.Label2.ForeColor = System.Drawing.SystemColors.ControlText
		Me.Label2.Cursor = System.Windows.Forms.Cursors.Default
		Me.Label2.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.Label2.UseMnemonic = True
		Me.Label2.Visible = True
		Me.Label2.AutoSize = False
		Me.Label2.BorderStyle = System.Windows.Forms.BorderStyle.None
		Me.Label2.Name = "Label2"
		Me.Label1.Text = "Select a part."
		Me.Label1.Size = New System.Drawing.Size(87, 22)
		Me.Label1.Location = New System.Drawing.Point(285, 95)
		Me.Label1.TabIndex = 3
		Me.Label1.TextAlign = System.Drawing.ContentAlignment.TopLeft
		Me.Label1.BackColor = System.Drawing.SystemColors.Control
		Me.Label1.Enabled = True
		Me.Label1.ForeColor = System.Drawing.SystemColors.ControlText
		Me.Label1.Cursor = System.Windows.Forms.Cursors.Default
		Me.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.Label1.UseMnemonic = True
		Me.Label1.Visible = True
		Me.Label1.AutoSize = False
		Me.Label1.BorderStyle = System.Windows.Forms.BorderStyle.None
		Me.Label1.Name = "Label1"
		Me.Controls.Add(Picture1)
		Me.Controls.Add(cmdBrowse)
		Me.Controls.Add(txtLibraryPath)
		Me.Controls.Add(cmdCancel)
		Me.Controls.Add(cmdPlaceBolts)
		Me.Controls.Add(treAssembly)
		Me.Controls.Add(Label2)
		Me.Controls.Add(Label1)
		Me.ResumeLayout(False)
		Me.PerformLayout()
	End Sub
#End Region 
End Class