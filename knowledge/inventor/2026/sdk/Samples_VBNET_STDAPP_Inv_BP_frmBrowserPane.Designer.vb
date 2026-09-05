<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> Partial Class frmBrowserPane
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
	Public WithEvents MFCCtlAddTextBtn As System.Windows.Forms.Button
	Public WithEvents MFCCtrlTextCtrl As System.Windows.Forms.TextBox
	Public WithEvents MFCCtrlClearBtn As System.Windows.Forms.Button
	Public WithEvents Frame1 As System.Windows.Forms.GroupBox
	Public WithEvents BrowserPaneBtn As System.Windows.Forms.Button
	Public WithEvents ConnectBtn As System.Windows.Forms.Button
	Public WithEvents ListBoxCtrl As System.Windows.Forms.ListBox
	Public WithEvents ExitButton As System.Windows.Forms.Button
	'NOTE: The following procedure is required by the Windows Form Designer
	'It can be modified using the Windows Form Designer.
	'Do not modify it using the code editor.
	<System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
		Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmBrowserPane))
		Me.components = New System.ComponentModel.Container()
		Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
		Me.MFCCtlAddTextBtn = New System.Windows.Forms.Button
		Me.MFCCtrlTextCtrl = New System.Windows.Forms.TextBox
		Me.Frame1 = New System.Windows.Forms.GroupBox
		Me.MFCCtrlClearBtn = New System.Windows.Forms.Button
		Me.BrowserPaneBtn = New System.Windows.Forms.Button
		Me.ConnectBtn = New System.Windows.Forms.Button
		Me.ListBoxCtrl = New System.Windows.Forms.ListBox
		Me.ExitButton = New System.Windows.Forms.Button
		Me.Frame1.SuspendLayout()
		Me.SuspendLayout()
		Me.ToolTip1.Active = True
		Me.Text = "VBBrowserPanes"
		Me.ClientSize = New System.Drawing.Size(690, 360)
		Me.Location = New System.Drawing.Point(4, 23)
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
		Me.Name = "frmBrowserPane"
		Me.MFCCtlAddTextBtn.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.MFCCtlAddTextBtn.Text = "AddText"
		Me.MFCCtlAddTextBtn.Size = New System.Drawing.Size(111, 31)
		Me.MFCCtlAddTextBtn.Location = New System.Drawing.Point(240, 140)
		Me.MFCCtlAddTextBtn.TabIndex = 5
		Me.ToolTip1.SetToolTip(Me.MFCCtlAddTextBtn, "Add Text to ActiveX Control in Browser")
		Me.MFCCtlAddTextBtn.BackColor = System.Drawing.SystemColors.Control
		Me.MFCCtlAddTextBtn.CausesValidation = True
		Me.MFCCtlAddTextBtn.Enabled = True
		Me.MFCCtlAddTextBtn.ForeColor = System.Drawing.SystemColors.ControlText
		Me.MFCCtlAddTextBtn.Cursor = System.Windows.Forms.Cursors.Default
		Me.MFCCtlAddTextBtn.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.MFCCtlAddTextBtn.TabStop = True
		Me.MFCCtlAddTextBtn.Name = "MFCCtlAddTextBtn"
		Me.MFCCtrlTextCtrl.AutoSize = False
		Me.MFCCtrlTextCtrl.Size = New System.Drawing.Size(161, 31)
		Me.MFCCtrlTextCtrl.Location = New System.Drawing.Point(50, 140)
		Me.MFCCtrlTextCtrl.TabIndex = 4
		Me.MFCCtrlTextCtrl.Text = "SampleText"
		Me.MFCCtrlTextCtrl.AcceptsReturn = True
		Me.MFCCtrlTextCtrl.TextAlign = System.Windows.Forms.HorizontalAlignment.Left
		Me.MFCCtrlTextCtrl.BackColor = System.Drawing.SystemColors.Window
		Me.MFCCtrlTextCtrl.CausesValidation = True
		Me.MFCCtrlTextCtrl.Enabled = True
		Me.MFCCtrlTextCtrl.ForeColor = System.Drawing.SystemColors.WindowText
		Me.MFCCtrlTextCtrl.HideSelection = True
		Me.MFCCtrlTextCtrl.ReadOnly = False
		Me.MFCCtrlTextCtrl.Maxlength = 0
		Me.MFCCtrlTextCtrl.Cursor = System.Windows.Forms.Cursors.IBeam
		Me.MFCCtrlTextCtrl.MultiLine = False
		Me.MFCCtrlTextCtrl.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.MFCCtrlTextCtrl.ScrollBars = System.Windows.Forms.ScrollBars.None
		Me.MFCCtrlTextCtrl.TabStop = True
		Me.MFCCtrlTextCtrl.Visible = True
		Me.MFCCtrlTextCtrl.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
		Me.MFCCtrlTextCtrl.Name = "MFCCtrlTextCtrl"
		Me.Frame1.Text = "SimpleMFCControl"
		Me.Frame1.Size = New System.Drawing.Size(341, 131)
		Me.Frame1.Location = New System.Drawing.Point(30, 110)
		Me.Frame1.TabIndex = 6
		Me.Frame1.BackColor = System.Drawing.SystemColors.Control
		Me.Frame1.Enabled = True
		Me.Frame1.ForeColor = System.Drawing.SystemColors.ControlText
		Me.Frame1.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.Frame1.Visible = True
		Me.Frame1.Name = "Frame1"
		Me.MFCCtrlClearBtn.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.MFCCtrlClearBtn.Text = "Clear Contents"
		Me.MFCCtrlClearBtn.Size = New System.Drawing.Size(131, 31)
		Me.MFCCtrlClearBtn.Location = New System.Drawing.Point(100, 90)
		Me.MFCCtrlClearBtn.TabIndex = 7
		Me.ToolTip1.SetToolTip(Me.MFCCtrlClearBtn, "Clear ActiveX Controls Content")
		Me.MFCCtrlClearBtn.BackColor = System.Drawing.SystemColors.Control
		Me.MFCCtrlClearBtn.CausesValidation = True
		Me.MFCCtrlClearBtn.Enabled = True
		Me.MFCCtrlClearBtn.ForeColor = System.Drawing.SystemColors.ControlText
		Me.MFCCtrlClearBtn.Cursor = System.Windows.Forms.Cursors.Default
		Me.MFCCtrlClearBtn.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.MFCCtrlClearBtn.TabStop = True
		Me.MFCCtrlClearBtn.Name = "MFCCtrlClearBtn"
		Me.BrowserPaneBtn.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.BrowserPaneBtn.Text = "Add BrowserPane"
		Me.BrowserPaneBtn.Size = New System.Drawing.Size(131, 31)
		Me.BrowserPaneBtn.Location = New System.Drawing.Point(230, 30)
		Me.BrowserPaneBtn.TabIndex = 3
		Me.BrowserPaneBtn.BackColor = System.Drawing.SystemColors.Control
		Me.BrowserPaneBtn.CausesValidation = True
		Me.BrowserPaneBtn.Enabled = True
		Me.BrowserPaneBtn.ForeColor = System.Drawing.SystemColors.ControlText
		Me.BrowserPaneBtn.Cursor = System.Windows.Forms.Cursors.Default
		Me.BrowserPaneBtn.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.BrowserPaneBtn.TabStop = True
		Me.BrowserPaneBtn.Name = "BrowserPaneBtn"
		Me.ConnectBtn.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.ConnectBtn.Text = "Connect"
		Me.ConnectBtn.Size = New System.Drawing.Size(111, 31)
		Me.ConnectBtn.Location = New System.Drawing.Point(60, 30)
		Me.ConnectBtn.TabIndex = 2
		Me.ToolTip1.SetToolTip(Me.ConnectBtn, "Connect to Inventor")
		Me.ConnectBtn.BackColor = System.Drawing.SystemColors.Control
		Me.ConnectBtn.CausesValidation = True
		Me.ConnectBtn.Enabled = True
		Me.ConnectBtn.ForeColor = System.Drawing.SystemColors.ControlText
		Me.ConnectBtn.Cursor = System.Windows.Forms.Cursors.Default
		Me.ConnectBtn.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.ConnectBtn.TabStop = True
		Me.ConnectBtn.Name = "ConnectBtn"
		Me.ListBoxCtrl.Size = New System.Drawing.Size(271, 253)
		Me.ListBoxCtrl.Location = New System.Drawing.Point(400, 10)
		Me.ListBoxCtrl.TabIndex = 1
		Me.ListBoxCtrl.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
		Me.ListBoxCtrl.BackColor = System.Drawing.SystemColors.Window
		Me.ListBoxCtrl.CausesValidation = True
		Me.ListBoxCtrl.Enabled = True
		Me.ListBoxCtrl.ForeColor = System.Drawing.SystemColors.WindowText
		Me.ListBoxCtrl.IntegralHeight = True
		Me.ListBoxCtrl.Cursor = System.Windows.Forms.Cursors.Default
		Me.ListBoxCtrl.SelectionMode = System.Windows.Forms.SelectionMode.One
		Me.ListBoxCtrl.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.ListBoxCtrl.Sorted = False
		Me.ListBoxCtrl.TabStop = True
		Me.ListBoxCtrl.Visible = True
		Me.ListBoxCtrl.MultiColumn = False
		Me.ListBoxCtrl.Name = "ListBoxCtrl"
		Me.ExitButton.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.ExitButton.Text = "Exit"
		Me.ExitButton.Size = New System.Drawing.Size(101, 31)
		Me.ExitButton.Location = New System.Drawing.Point(290, 300)
		Me.ExitButton.TabIndex = 0
		Me.ToolTip1.SetToolTip(Me.ExitButton, "Exit")
		Me.ExitButton.BackColor = System.Drawing.SystemColors.Control
		Me.ExitButton.CausesValidation = True
		Me.ExitButton.Enabled = True
		Me.ExitButton.ForeColor = System.Drawing.SystemColors.ControlText
		Me.ExitButton.Cursor = System.Windows.Forms.Cursors.Default
		Me.ExitButton.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.ExitButton.TabStop = True
		Me.ExitButton.Name = "ExitButton"
		Me.Controls.Add(MFCCtlAddTextBtn)
		Me.Controls.Add(MFCCtrlTextCtrl)
		Me.Controls.Add(Frame1)
		Me.Controls.Add(BrowserPaneBtn)
		Me.Controls.Add(ConnectBtn)
		Me.Controls.Add(ListBoxCtrl)
		Me.Controls.Add(ExitButton)
		Me.Frame1.Controls.Add(MFCCtrlClearBtn)
		Me.Frame1.ResumeLayout(False)
		Me.ResumeLayout(False)
		Me.PerformLayout()
	End Sub
#End Region 
End Class