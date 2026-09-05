<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> Partial Class Form1
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
	Public WithEvents Cancel As System.Windows.Forms.Button
	Public WithEvents OK As System.Windows.Forms.Button
	Public WithEvents CreateMems As System.Windows.Forms.RadioButton
	Public WithEvents RegenMems As System.Windows.Forms.RadioButton
	Public WithEvents iPartMem As System.Windows.Forms.TextBox
	Public WithEvents FileBrowse As System.Windows.Forms.Button
	Public WithEvents Frame1 As System.Windows.Forms.GroupBox
	Public WithEvents iPartFac As System.Windows.Forms.TextBox
	Public WithEvents Frame2 As System.Windows.Forms.GroupBox
	'NOTE: The following procedure is required by the Windows Form Designer
	'It can be modified using the Windows Form Designer.
	'Do not modify it using the code editor.
	<System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
		Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(Form1))
		Me.components = New System.ComponentModel.Container()
		Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
		Me.Cancel = New System.Windows.Forms.Button
		Me.OK = New System.Windows.Forms.Button
		Me.CreateMems = New System.Windows.Forms.RadioButton
		Me.RegenMems = New System.Windows.Forms.RadioButton
		Me.iPartMem = New System.Windows.Forms.TextBox
		Me.FileBrowse = New System.Windows.Forms.Button
		Me.Frame1 = New System.Windows.Forms.GroupBox
		Me.Frame2 = New System.Windows.Forms.GroupBox
		Me.iPartFac = New System.Windows.Forms.TextBox
		Me.Frame2.SuspendLayout()
		Me.SuspendLayout()
		Me.ToolTip1.Active = True
		Me.Text = "Form1"
		Me.ClientSize = New System.Drawing.Size(564, 310)
		Me.Location = New System.Drawing.Point(5, 29)
		Me.StartPosition = System.Windows.Forms.FormStartPosition.WindowsDefaultLocation
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.BackColor = System.Drawing.SystemColors.Control
		Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Sizable
		Me.ControlBox = True
		Me.Enabled = True
		Me.KeyPreview = False
		Me.MaximizeBox = True
		Me.MinimizeBox = True
		Me.Cursor = System.Windows.Forms.Cursors.Default
		Me.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.ShowInTaskbar = True
		Me.HelpButton = False
		Me.WindowState = System.Windows.Forms.FormWindowState.Normal
		Me.Name = "Form1"
		Me.Cancel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.Cancel.Text = "Cancel"
		Me.Cancel.Size = New System.Drawing.Size(62, 52)
		Me.Cancel.Location = New System.Drawing.Point(470, 240)
		Me.Cancel.TabIndex = 5
		Me.Cancel.BackColor = System.Drawing.SystemColors.Control
		Me.Cancel.CausesValidation = True
		Me.Cancel.Enabled = True
		Me.Cancel.ForeColor = System.Drawing.SystemColors.ControlText
		Me.Cancel.Cursor = System.Windows.Forms.Cursors.Default
		Me.Cancel.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.Cancel.TabStop = True
		Me.Cancel.Name = "Cancel"
		Me.OK.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.OK.Text = "OK"
		Me.OK.Size = New System.Drawing.Size(62, 52)
		Me.OK.Location = New System.Drawing.Point(380, 240)
		Me.OK.TabIndex = 4
		Me.OK.BackColor = System.Drawing.SystemColors.Control
		Me.OK.CausesValidation = True
		Me.OK.Enabled = True
		Me.OK.ForeColor = System.Drawing.SystemColors.ControlText
		Me.OK.Cursor = System.Windows.Forms.Cursors.Default
		Me.OK.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.OK.TabStop = True
		Me.OK.Name = "OK"
		Me.CreateMems.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
		Me.CreateMems.Text = "Create all members"
		Me.CreateMems.Size = New System.Drawing.Size(302, 22)
		Me.CreateMems.Location = New System.Drawing.Point(30, 210)
		Me.CreateMems.TabIndex = 3
		Me.CreateMems.CheckAlign = System.Drawing.ContentAlignment.MiddleLeft
		Me.CreateMems.BackColor = System.Drawing.SystemColors.Control
		Me.CreateMems.CausesValidation = True
		Me.CreateMems.Enabled = True
		Me.CreateMems.ForeColor = System.Drawing.SystemColors.ControlText
		Me.CreateMems.Cursor = System.Windows.Forms.Cursors.Default
		Me.CreateMems.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.CreateMems.Appearance = System.Windows.Forms.Appearance.Normal
		Me.CreateMems.TabStop = True
		Me.CreateMems.Checked = False
		Me.CreateMems.Visible = True
		Me.CreateMems.Name = "CreateMems"
		Me.RegenMems.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
		Me.RegenMems.Text = "Regenerate existing members"
		Me.RegenMems.Size = New System.Drawing.Size(292, 22)
		Me.RegenMems.Location = New System.Drawing.Point(30, 180)
		Me.RegenMems.TabIndex = 2
		Me.RegenMems.CheckAlign = System.Drawing.ContentAlignment.MiddleLeft
		Me.RegenMems.BackColor = System.Drawing.SystemColors.Control
		Me.RegenMems.CausesValidation = True
		Me.RegenMems.Enabled = True
		Me.RegenMems.ForeColor = System.Drawing.SystemColors.ControlText
		Me.RegenMems.Cursor = System.Windows.Forms.Cursors.Default
		Me.RegenMems.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.RegenMems.Appearance = System.Windows.Forms.Appearance.Normal
		Me.RegenMems.TabStop = True
		Me.RegenMems.Checked = False
		Me.RegenMems.Visible = True
		Me.RegenMems.Name = "RegenMems"
		Me.iPartMem.AutoSize = False
		Me.iPartMem.Size = New System.Drawing.Size(402, 32)
		Me.iPartMem.Location = New System.Drawing.Point(40, 120)
		Me.iPartMem.TabIndex = 1
		Me.iPartMem.AcceptsReturn = True
		Me.iPartMem.TextAlign = System.Windows.Forms.HorizontalAlignment.Left
		Me.iPartMem.BackColor = System.Drawing.SystemColors.Window
		Me.iPartMem.CausesValidation = True
		Me.iPartMem.Enabled = True
		Me.iPartMem.ForeColor = System.Drawing.SystemColors.WindowText
		Me.iPartMem.HideSelection = True
		Me.iPartMem.ReadOnly = False
		Me.iPartMem.Maxlength = 0
		Me.iPartMem.Cursor = System.Windows.Forms.Cursors.IBeam
		Me.iPartMem.MultiLine = False
		Me.iPartMem.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.iPartMem.ScrollBars = System.Windows.Forms.ScrollBars.None
		Me.iPartMem.TabStop = True
		Me.iPartMem.Visible = True
		Me.iPartMem.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
		Me.iPartMem.Name = "iPartMem"
		Me.FileBrowse.TextAlign = System.Drawing.ContentAlignment.BottomCenter
		Me.FileBrowse.Size = New System.Drawing.Size(52, 52)
		Me.FileBrowse.Location = New System.Drawing.Point(460, 30)
		Me.FileBrowse.Image = CType(resources.GetObject("FileBrowse.Image"), System.Drawing.Image)
		Me.FileBrowse.TabIndex = 0
		Me.ToolTip1.SetToolTip(Me.FileBrowse, "File Open Dialog")
		Me.FileBrowse.BackColor = System.Drawing.SystemColors.Control
		Me.FileBrowse.CausesValidation = True
		Me.FileBrowse.Enabled = True
		Me.FileBrowse.ForeColor = System.Drawing.SystemColors.ControlText
		Me.FileBrowse.Cursor = System.Windows.Forms.Cursors.Default
		Me.FileBrowse.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.FileBrowse.TabStop = True
		Me.FileBrowse.Name = "FileBrowse"
		Me.Frame1.Text = "Location for iPart members"
		Me.Frame1.Size = New System.Drawing.Size(422, 62)
		Me.Frame1.Location = New System.Drawing.Point(30, 100)
		Me.Frame1.TabIndex = 6
		Me.Frame1.BackColor = System.Drawing.SystemColors.Control
		Me.Frame1.Enabled = True
		Me.Frame1.ForeColor = System.Drawing.SystemColors.ControlText
		Me.Frame1.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.Frame1.Visible = True
		Me.Frame1.Name = "Frame1"
		Me.Frame2.Text = "Select iPart factory"
		Me.Frame2.Size = New System.Drawing.Size(502, 82)
		Me.Frame2.Location = New System.Drawing.Point(30, 10)
		Me.Frame2.TabIndex = 7
		Me.Frame2.BackColor = System.Drawing.SystemColors.Control
		Me.Frame2.Enabled = True
		Me.Frame2.ForeColor = System.Drawing.SystemColors.ControlText
		Me.Frame2.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.Frame2.Visible = True
		Me.Frame2.Name = "Frame2"
		Me.iPartFac.AutoSize = False
		Me.iPartFac.Size = New System.Drawing.Size(402, 32)
		Me.iPartFac.Location = New System.Drawing.Point(10, 30)
		Me.iPartFac.TabIndex = 8
		Me.iPartFac.AcceptsReturn = True
		Me.iPartFac.TextAlign = System.Windows.Forms.HorizontalAlignment.Left
		Me.iPartFac.BackColor = System.Drawing.SystemColors.Window
		Me.iPartFac.CausesValidation = True
		Me.iPartFac.Enabled = True
		Me.iPartFac.ForeColor = System.Drawing.SystemColors.WindowText
		Me.iPartFac.HideSelection = True
		Me.iPartFac.ReadOnly = False
		Me.iPartFac.Maxlength = 0
		Me.iPartFac.Cursor = System.Windows.Forms.Cursors.IBeam
		Me.iPartFac.MultiLine = False
		Me.iPartFac.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.iPartFac.ScrollBars = System.Windows.Forms.ScrollBars.None
		Me.iPartFac.TabStop = True
		Me.iPartFac.Visible = True
		Me.iPartFac.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
		Me.iPartFac.Name = "iPartFac"
		Me.Controls.Add(Cancel)
		Me.Controls.Add(OK)
		Me.Controls.Add(CreateMems)
		Me.Controls.Add(RegenMems)
		Me.Controls.Add(iPartMem)
		Me.Controls.Add(FileBrowse)
		Me.Controls.Add(Frame1)
		Me.Controls.Add(Frame2)
		Me.Frame2.Controls.Add(iPartFac)
		Me.Frame2.ResumeLayout(False)
		Me.ResumeLayout(False)
		Me.PerformLayout()
	End Sub
#End Region 
End Class