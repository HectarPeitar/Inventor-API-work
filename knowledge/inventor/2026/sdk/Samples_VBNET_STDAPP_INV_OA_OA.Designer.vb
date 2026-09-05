<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> Partial Class frmOverlayAssembly
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
	Public WithEvents RemoveRep As System.Windows.Forms.Button
	Public WithEvents AddRep As System.Windows.Forms.Button
	Public WithEvents SelectedStates As System.Windows.Forms.ListBox
	Public WithEvents AvailableStates As System.Windows.Forms.ListBox
	Public WithEvents cmdCancel As System.Windows.Forms.Button
	Public WithEvents cmdOK As System.Windows.Forms.Button
	Public WithEvents cmdBrowse As System.Windows.Forms.Button
	Public WithEvents txtFilename As System.Windows.Forms.TextBox
	Public CommonDialog1Open As System.Windows.Forms.OpenFileDialog
	Public WithEvents imgList As System.Windows.Forms.ImageList
	Public WithEvents Label3 As System.Windows.Forms.Label
	Public WithEvents Label2 As System.Windows.Forms.Label
	Public WithEvents Label1 As System.Windows.Forms.Label
	'NOTE: The following procedure is required by the Windows Form Designer
	'It can be modified using the Windows Form Designer.
	'Do not modify it using the code editor.
	<System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
		Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmOverlayAssembly))
		Me.components = New System.ComponentModel.Container()
		Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
		Me.RemoveRep = New System.Windows.Forms.Button
		Me.AddRep = New System.Windows.Forms.Button
		Me.SelectedStates = New System.Windows.Forms.ListBox
		Me.AvailableStates = New System.Windows.Forms.ListBox
		Me.cmdCancel = New System.Windows.Forms.Button
		Me.cmdOK = New System.Windows.Forms.Button
		Me.cmdBrowse = New System.Windows.Forms.Button
		Me.txtFilename = New System.Windows.Forms.TextBox
		Me.CommonDialog1Open = New System.Windows.Forms.OpenFileDialog
		Me.imgList = New System.Windows.Forms.ImageList
		Me.Label3 = New System.Windows.Forms.Label
		Me.Label2 = New System.Windows.Forms.Label
		Me.Label1 = New System.Windows.Forms.Label
		Me.SuspendLayout()
		Me.ToolTip1.Active = True
		Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
		Me.Text = "Overlay Assembly"
		Me.ClientSize = New System.Drawing.Size(472, 302)
		Me.Location = New System.Drawing.Point(4, 28)
		Me.MaximizeBox = False
		Me.MinimizeBox = False
		Me.ShowInTaskbar = False
		Me.StartPosition = System.Windows.Forms.FormStartPosition.WindowsDefaultLocation
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.BackColor = System.Drawing.SystemColors.Control
		Me.ControlBox = True
		Me.Enabled = True
		Me.KeyPreview = False
		Me.Cursor = System.Windows.Forms.Cursors.Default
		Me.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.HelpButton = False
		Me.WindowState = System.Windows.Forms.FormWindowState.Normal
		Me.Name = "frmOverlayAssembly"
		Me.RemoveRep.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.RemoveRep.Text = "Remove"
		Me.RemoveRep.Enabled = False
		Me.RemoveRep.Size = New System.Drawing.Size(72, 32)
		Me.RemoveRep.Location = New System.Drawing.Point(200, 180)
		Me.RemoveRep.TabIndex = 10
		Me.RemoveRep.BackColor = System.Drawing.SystemColors.Control
		Me.RemoveRep.CausesValidation = True
		Me.RemoveRep.ForeColor = System.Drawing.SystemColors.ControlText
		Me.RemoveRep.Cursor = System.Windows.Forms.Cursors.Default
		Me.RemoveRep.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.RemoveRep.TabStop = True
		Me.RemoveRep.Name = "RemoveRep"
		Me.AddRep.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.AddRep.Text = "Add >>"
		Me.AddRep.Enabled = False
		Me.AddRep.Size = New System.Drawing.Size(72, 32)
		Me.AddRep.Location = New System.Drawing.Point(200, 120)
		Me.AddRep.TabIndex = 9
		Me.AddRep.BackColor = System.Drawing.SystemColors.Control
		Me.AddRep.CausesValidation = True
		Me.AddRep.ForeColor = System.Drawing.SystemColors.ControlText
		Me.AddRep.Cursor = System.Windows.Forms.Cursors.Default
		Me.AddRep.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.AddRep.TabStop = True
		Me.AddRep.Name = "AddRep"
		Me.SelectedStates.Size = New System.Drawing.Size(162, 139)
		Me.SelectedStates.Location = New System.Drawing.Point(300, 100)
		Me.SelectedStates.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended
		Me.SelectedStates.TabIndex = 7
		Me.SelectedStates.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
		Me.SelectedStates.BackColor = System.Drawing.SystemColors.Window
		Me.SelectedStates.CausesValidation = True
		Me.SelectedStates.Enabled = True
		Me.SelectedStates.ForeColor = System.Drawing.SystemColors.WindowText
		Me.SelectedStates.IntegralHeight = True
		Me.SelectedStates.Cursor = System.Windows.Forms.Cursors.Default
		Me.SelectedStates.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.SelectedStates.Sorted = False
		Me.SelectedStates.TabStop = True
		Me.SelectedStates.Visible = True
		Me.SelectedStates.MultiColumn = False
		Me.SelectedStates.Name = "SelectedStates"
		Me.AvailableStates.Size = New System.Drawing.Size(162, 139)
		Me.AvailableStates.Location = New System.Drawing.Point(10, 100)
		Me.AvailableStates.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended
		Me.AvailableStates.TabIndex = 5
		Me.AvailableStates.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
		Me.AvailableStates.BackColor = System.Drawing.SystemColors.Window
		Me.AvailableStates.CausesValidation = True
		Me.AvailableStates.Enabled = True
		Me.AvailableStates.ForeColor = System.Drawing.SystemColors.WindowText
		Me.AvailableStates.IntegralHeight = True
		Me.AvailableStates.Cursor = System.Windows.Forms.Cursors.Default
		Me.AvailableStates.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.AvailableStates.Sorted = False
		Me.AvailableStates.TabStop = True
		Me.AvailableStates.Visible = True
		Me.AvailableStates.MultiColumn = False
		Me.AvailableStates.Name = "AvailableStates"
		Me.cmdCancel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.cmdCancel.Text = "Cancel"
		Me.cmdCancel.Size = New System.Drawing.Size(102, 32)
		Me.cmdCancel.Location = New System.Drawing.Point(280, 260)
		Me.cmdCancel.TabIndex = 4
		Me.cmdCancel.BackColor = System.Drawing.SystemColors.Control
		Me.cmdCancel.CausesValidation = True
		Me.cmdCancel.Enabled = True
		Me.cmdCancel.ForeColor = System.Drawing.SystemColors.ControlText
		Me.cmdCancel.Cursor = System.Windows.Forms.Cursors.Default
		Me.cmdCancel.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.cmdCancel.TabStop = True
		Me.cmdCancel.Name = "cmdCancel"
		Me.cmdOK.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.cmdOK.Text = "Create Overlay Assembly"
		Me.cmdOK.Enabled = False
		Me.cmdOK.Size = New System.Drawing.Size(172, 32)
		Me.cmdOK.Location = New System.Drawing.Point(50, 260)
		Me.cmdOK.TabIndex = 3
		Me.cmdOK.BackColor = System.Drawing.SystemColors.Control
		Me.cmdOK.CausesValidation = True
		Me.cmdOK.ForeColor = System.Drawing.SystemColors.ControlText
		Me.cmdOK.Cursor = System.Windows.Forms.Cursors.Default
		Me.cmdOK.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.cmdOK.TabStop = True
		Me.cmdOK.Name = "cmdOK"
		Me.cmdBrowse.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.cmdBrowse.Text = "Browse..."
		Me.cmdBrowse.Size = New System.Drawing.Size(77, 27)
		Me.cmdBrowse.Location = New System.Drawing.Point(380, 25)
		Me.cmdBrowse.TabIndex = 2
		Me.cmdBrowse.BackColor = System.Drawing.SystemColors.Control
		Me.cmdBrowse.CausesValidation = True
		Me.cmdBrowse.Enabled = True
		Me.cmdBrowse.ForeColor = System.Drawing.SystemColors.ControlText
		Me.cmdBrowse.Cursor = System.Windows.Forms.Cursors.Default
		Me.cmdBrowse.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.cmdBrowse.TabStop = True
		Me.cmdBrowse.Name = "cmdBrowse"
		Me.txtFilename.AutoSize = False
		Me.txtFilename.Size = New System.Drawing.Size(287, 27)
		Me.txtFilename.Location = New System.Drawing.Point(90, 25)
		Me.txtFilename.TabIndex = 0
		Me.txtFilename.AcceptsReturn = True
		Me.txtFilename.TextAlign = System.Windows.Forms.HorizontalAlignment.Left
		Me.txtFilename.BackColor = System.Drawing.SystemColors.Window
		Me.txtFilename.CausesValidation = True
		Me.txtFilename.Enabled = True
		Me.txtFilename.ForeColor = System.Drawing.SystemColors.WindowText
		Me.txtFilename.HideSelection = True
		Me.txtFilename.ReadOnly = False
		Me.txtFilename.Maxlength = 0
		Me.txtFilename.Cursor = System.Windows.Forms.Cursors.IBeam
		Me.txtFilename.MultiLine = False
		Me.txtFilename.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.txtFilename.ScrollBars = System.Windows.Forms.ScrollBars.None
		Me.txtFilename.TabStop = True
		Me.txtFilename.Visible = True
		Me.txtFilename.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
		Me.txtFilename.Name = "txtFilename"
		Me.imgList.ImageSize = New System.Drawing.Size(16, 16)
		Me.imgList.TransparentColor = System.Drawing.Color.FromARGB(192, 192, 192)
		Me.imgList.ImageStream = CType(resources.GetObject("imgList.ImageStream"), System.Windows.Forms.ImageListStreamer)
		Me.imgList.Images.SetKeyName(0, "Assembly")
		Me.imgList.Images.SetKeyName(1, "Part")
		Me.Label3.Text = "Selected Representations:"
		Me.Label3.Size = New System.Drawing.Size(172, 22)
		Me.Label3.Location = New System.Drawing.Point(300, 70)
		Me.Label3.TabIndex = 8
		Me.Label3.TextAlign = System.Drawing.ContentAlignment.TopLeft
		Me.Label3.BackColor = System.Drawing.SystemColors.Control
		Me.Label3.Enabled = True
		Me.Label3.ForeColor = System.Drawing.SystemColors.ControlText
		Me.Label3.Cursor = System.Windows.Forms.Cursors.Default
		Me.Label3.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.Label3.UseMnemonic = True
		Me.Label3.Visible = True
		Me.Label3.AutoSize = False
		Me.Label3.BorderStyle = System.Windows.Forms.BorderStyle.None
		Me.Label3.Name = "Label3"
		Me.Label2.Text = "Available Representations:"
		Me.Label2.Size = New System.Drawing.Size(172, 22)
		Me.Label2.Location = New System.Drawing.Point(10, 70)
		Me.Label2.TabIndex = 6
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
		Me.Label1.Text = "Source File:"
		Me.Label1.Size = New System.Drawing.Size(87, 17)
		Me.Label1.Location = New System.Drawing.Point(10, 30)
		Me.Label1.TabIndex = 1
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
		Me.Controls.Add(RemoveRep)
		Me.Controls.Add(AddRep)
		Me.Controls.Add(SelectedStates)
		Me.Controls.Add(AvailableStates)
		Me.Controls.Add(cmdCancel)
		Me.Controls.Add(cmdOK)
		Me.Controls.Add(cmdBrowse)
		Me.Controls.Add(txtFilename)
		Me.Controls.Add(Label3)
		Me.Controls.Add(Label2)
		Me.Controls.Add(Label1)
		Me.ResumeLayout(False)
		Me.PerformLayout()
	End Sub
#End Region 
End Class