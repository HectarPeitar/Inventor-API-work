<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> Partial Class frmLaserDrilling
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
	Public WithEvents RemoveCutSection As System.Windows.Forms.Button
	Public WithEvents MoveTool As System.Windows.Forms.Button
	Public WithEvents DrawTool As System.Windows.Forms.Button
	'NOTE: The following procedure is required by the Windows Form Designer
	'It can be modified using the Windows Form Designer.
	'Do not modify it using the code editor.
	<System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
		Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmLaserDrilling))
		Me.components = New System.ComponentModel.Container()
		Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
		Me.RemoveCutSection = New System.Windows.Forms.Button
		Me.MoveTool = New System.Windows.Forms.Button
		Me.DrawTool = New System.Windows.Forms.Button
		Me.SuspendLayout()
		Me.ToolTip1.Active = True
		Me.Text = "Custom Graphics"
		Me.ClientSize = New System.Drawing.Size(434, 229)
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
		Me.Name = "frmLaserDrilling"
		Me.RemoveCutSection.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.RemoveCutSection.Text = "Remove Cut Section"
		Me.RemoveCutSection.Enabled = False
		Me.RemoveCutSection.Size = New System.Drawing.Size(142, 72)
		Me.RemoveCutSection.Location = New System.Drawing.Point(150, 140)
		Me.RemoveCutSection.TabIndex = 2
		Me.RemoveCutSection.BackColor = System.Drawing.SystemColors.Control
		Me.RemoveCutSection.CausesValidation = True
		Me.RemoveCutSection.ForeColor = System.Drawing.SystemColors.ControlText
		Me.RemoveCutSection.Cursor = System.Windows.Forms.Cursors.Default
		Me.RemoveCutSection.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.RemoveCutSection.TabStop = True
		Me.RemoveCutSection.Name = "RemoveCutSection"
		Me.MoveTool.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.MoveTool.Text = "Move Tool"
		Me.MoveTool.Enabled = False
		Me.MoveTool.Size = New System.Drawing.Size(112, 72)
		Me.MoveTool.Location = New System.Drawing.Point(260, 40)
		Me.MoveTool.TabIndex = 1
		Me.MoveTool.BackColor = System.Drawing.SystemColors.Control
		Me.MoveTool.CausesValidation = True
		Me.MoveTool.ForeColor = System.Drawing.SystemColors.ControlText
		Me.MoveTool.Cursor = System.Windows.Forms.Cursors.Default
		Me.MoveTool.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.MoveTool.TabStop = True
		Me.MoveTool.Name = "MoveTool"
		Me.DrawTool.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.DrawTool.Text = "Draw Tool"
		Me.DrawTool.Size = New System.Drawing.Size(122, 72)
		Me.DrawTool.Location = New System.Drawing.Point(70, 40)
		Me.DrawTool.TabIndex = 0
		Me.DrawTool.BackColor = System.Drawing.SystemColors.Control
		Me.DrawTool.CausesValidation = True
		Me.DrawTool.Enabled = True
		Me.DrawTool.ForeColor = System.Drawing.SystemColors.ControlText
		Me.DrawTool.Cursor = System.Windows.Forms.Cursors.Default
		Me.DrawTool.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.DrawTool.TabStop = True
		Me.DrawTool.Name = "DrawTool"
		Me.Controls.Add(RemoveCutSection)
		Me.Controls.Add(MoveTool)
		Me.Controls.Add(DrawTool)
		Me.ResumeLayout(False)
		Me.PerformLayout()
	End Sub
#End Region 
End Class