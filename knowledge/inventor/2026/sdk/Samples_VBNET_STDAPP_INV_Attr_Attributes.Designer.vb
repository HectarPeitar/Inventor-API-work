<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> Partial Class frmAttributes
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
	Public WithEvents Save_Command As System.Windows.Forms.Button
	Public WithEvents Close_Command As System.Windows.Forms.Button
	Public WithEvents QueryEntities_Text As System.Windows.Forms.TextBox
	Public WithEvents QueryEntities_Command As System.Windows.Forms.Button
	Public WithEvents GetAttribute_Command As System.Windows.Forms.Button
	Public WithEvents GetAttribute_Text As System.Windows.Forms.TextBox
	Public WithEvents DeleteAttribute_Command As System.Windows.Forms.Button
	Public WithEvents SetAttribute_Command As System.Windows.Forms.Button
	Public WithEvents SetAttribute_Text As System.Windows.Forms.TextBox
	Public WithEvents SetAttributeValueLabel As System.Windows.Forms.Label
	Public WithEvents CreateAttributesLabel As System.Windows.Forms.Label
	Public WithEvents SetAttributesFrame As System.Windows.Forms.GroupBox
	Public WithEvents GetAttributeValueLabel As System.Windows.Forms.Label
	Public WithEvents GetAttributesLabel As System.Windows.Forms.Label
	Public WithEvents GetAttributesFrame As System.Windows.Forms.GroupBox
	Public WithEvents Clear_Command As System.Windows.Forms.Button
	Public WithEvents QueryEntityLabel As System.Windows.Forms.Label
	Public WithEvents Label1 As System.Windows.Forms.Label
	Public WithEvents QueryAttributesFrame As System.Windows.Forms.GroupBox
	'NOTE: The following procedure is required by the Windows Form Designer
	'It can be modified using the Windows Form Designer.
	'Do not modify it using the code editor.
	<System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
		Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(frmAttributes))
		Me.components = New System.ComponentModel.Container()
		Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
		Me.Save_Command = New System.Windows.Forms.Button
		Me.Close_Command = New System.Windows.Forms.Button
		Me.QueryEntities_Text = New System.Windows.Forms.TextBox
		Me.QueryEntities_Command = New System.Windows.Forms.Button
		Me.GetAttribute_Command = New System.Windows.Forms.Button
		Me.GetAttribute_Text = New System.Windows.Forms.TextBox
		Me.DeleteAttribute_Command = New System.Windows.Forms.Button
		Me.SetAttribute_Command = New System.Windows.Forms.Button
		Me.SetAttribute_Text = New System.Windows.Forms.TextBox
		Me.SetAttributesFrame = New System.Windows.Forms.GroupBox
		Me.SetAttributeValueLabel = New System.Windows.Forms.Label
		Me.CreateAttributesLabel = New System.Windows.Forms.Label
		Me.GetAttributesFrame = New System.Windows.Forms.GroupBox
		Me.GetAttributeValueLabel = New System.Windows.Forms.Label
		Me.GetAttributesLabel = New System.Windows.Forms.Label
		Me.QueryAttributesFrame = New System.Windows.Forms.GroupBox
		Me.Clear_Command = New System.Windows.Forms.Button
		Me.QueryEntityLabel = New System.Windows.Forms.Label
		Me.Label1 = New System.Windows.Forms.Label
		Me.SetAttributesFrame.SuspendLayout()
		Me.GetAttributesFrame.SuspendLayout()
		Me.QueryAttributesFrame.SuspendLayout()
		Me.SuspendLayout()
		Me.ToolTip1.Active = True
		Me.Text = "Attributes Sample"
		Me.ClientSize = New System.Drawing.Size(505, 510)
		Me.Location = New System.Drawing.Point(5, 30)
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
		Me.Name = "frmAttributes"
		Me.Save_Command.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.Save_Command.Text = "Save"
		Me.Save_Command.Size = New System.Drawing.Size(102, 42)
		Me.Save_Command.Location = New System.Drawing.Point(200, 450)
		Me.Save_Command.TabIndex = 8
		Me.Save_Command.BackColor = System.Drawing.SystemColors.Control
		Me.Save_Command.CausesValidation = True
		Me.Save_Command.Enabled = True
		Me.Save_Command.ForeColor = System.Drawing.SystemColors.ControlText
		Me.Save_Command.Cursor = System.Windows.Forms.Cursors.Default
		Me.Save_Command.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.Save_Command.TabStop = True
		Me.Save_Command.Name = "Save_Command"
		Me.Close_Command.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.Close_Command.Text = "Close"
		Me.Close_Command.Size = New System.Drawing.Size(102, 42)
		Me.Close_Command.Location = New System.Drawing.Point(360, 450)
		Me.Close_Command.TabIndex = 7
		Me.Close_Command.BackColor = System.Drawing.SystemColors.Control
		Me.Close_Command.CausesValidation = True
		Me.Close_Command.Enabled = True
		Me.Close_Command.ForeColor = System.Drawing.SystemColors.ControlText
		Me.Close_Command.Cursor = System.Windows.Forms.Cursors.Default
		Me.Close_Command.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.Close_Command.TabStop = True
		Me.Close_Command.Name = "Close_Command"
		Me.QueryEntities_Text.AutoSize = False
		Me.QueryEntities_Text.Size = New System.Drawing.Size(212, 42)
		Me.QueryEntities_Text.Location = New System.Drawing.Point(40, 350)
		Me.QueryEntities_Text.TabIndex = 6
		Me.QueryEntities_Text.AcceptsReturn = True
		Me.QueryEntities_Text.TextAlign = System.Windows.Forms.HorizontalAlignment.Left
		Me.QueryEntities_Text.BackColor = System.Drawing.SystemColors.Window
		Me.QueryEntities_Text.CausesValidation = True
		Me.QueryEntities_Text.Enabled = True
		Me.QueryEntities_Text.ForeColor = System.Drawing.SystemColors.WindowText
		Me.QueryEntities_Text.HideSelection = True
		Me.QueryEntities_Text.ReadOnly = False
		Me.QueryEntities_Text.Maxlength = 0
		Me.QueryEntities_Text.Cursor = System.Windows.Forms.Cursors.IBeam
		Me.QueryEntities_Text.MultiLine = False
		Me.QueryEntities_Text.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.QueryEntities_Text.ScrollBars = System.Windows.Forms.ScrollBars.None
		Me.QueryEntities_Text.TabStop = True
		Me.QueryEntities_Text.Visible = True
		Me.QueryEntities_Text.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
		Me.QueryEntities_Text.Name = "QueryEntities_Text"
		Me.QueryEntities_Command.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.QueryEntities_Command.Text = "Query Entities"
		Me.QueryEntities_Command.Size = New System.Drawing.Size(102, 42)
		Me.QueryEntities_Command.Location = New System.Drawing.Point(270, 350)
		Me.QueryEntities_Command.TabIndex = 5
		Me.QueryEntities_Command.BackColor = System.Drawing.SystemColors.Control
		Me.QueryEntities_Command.CausesValidation = True
		Me.QueryEntities_Command.Enabled = True
		Me.QueryEntities_Command.ForeColor = System.Drawing.SystemColors.ControlText
		Me.QueryEntities_Command.Cursor = System.Windows.Forms.Cursors.Default
		Me.QueryEntities_Command.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.QueryEntities_Command.TabStop = True
		Me.QueryEntities_Command.Name = "QueryEntities_Command"
		Me.GetAttribute_Command.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.GetAttribute_Command.Text = "Get Attribute"
		Me.GetAttribute_Command.Size = New System.Drawing.Size(112, 42)
		Me.GetAttribute_Command.Location = New System.Drawing.Point(310, 210)
		Me.GetAttribute_Command.TabIndex = 4
		Me.GetAttribute_Command.BackColor = System.Drawing.SystemColors.Control
		Me.GetAttribute_Command.CausesValidation = True
		Me.GetAttribute_Command.Enabled = True
		Me.GetAttribute_Command.ForeColor = System.Drawing.SystemColors.ControlText
		Me.GetAttribute_Command.Cursor = System.Windows.Forms.Cursors.Default
		Me.GetAttribute_Command.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.GetAttribute_Command.TabStop = True
		Me.GetAttribute_Command.Name = "GetAttribute_Command"
		Me.GetAttribute_Text.AutoSize = False
		Me.GetAttribute_Text.Size = New System.Drawing.Size(212, 42)
		Me.GetAttribute_Text.Location = New System.Drawing.Point(40, 210)
		Me.GetAttribute_Text.TabIndex = 3
		Me.GetAttribute_Text.AcceptsReturn = True
		Me.GetAttribute_Text.TextAlign = System.Windows.Forms.HorizontalAlignment.Left
		Me.GetAttribute_Text.BackColor = System.Drawing.SystemColors.Window
		Me.GetAttribute_Text.CausesValidation = True
		Me.GetAttribute_Text.Enabled = True
		Me.GetAttribute_Text.ForeColor = System.Drawing.SystemColors.WindowText
		Me.GetAttribute_Text.HideSelection = True
		Me.GetAttribute_Text.ReadOnly = False
		Me.GetAttribute_Text.Maxlength = 0
		Me.GetAttribute_Text.Cursor = System.Windows.Forms.Cursors.IBeam
		Me.GetAttribute_Text.MultiLine = False
		Me.GetAttribute_Text.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.GetAttribute_Text.ScrollBars = System.Windows.Forms.ScrollBars.None
		Me.GetAttribute_Text.TabStop = True
		Me.GetAttribute_Text.Visible = True
		Me.GetAttribute_Text.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
		Me.GetAttribute_Text.Name = "GetAttribute_Text"
		Me.DeleteAttribute_Command.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.DeleteAttribute_Command.Text = "Delete Attribute"
		Me.DeleteAttribute_Command.Size = New System.Drawing.Size(112, 42)
		Me.DeleteAttribute_Command.Location = New System.Drawing.Point(30, 450)
		Me.DeleteAttribute_Command.TabIndex = 2
		Me.DeleteAttribute_Command.BackColor = System.Drawing.SystemColors.Control
		Me.DeleteAttribute_Command.CausesValidation = True
		Me.DeleteAttribute_Command.Enabled = True
		Me.DeleteAttribute_Command.ForeColor = System.Drawing.SystemColors.ControlText
		Me.DeleteAttribute_Command.Cursor = System.Windows.Forms.Cursors.Default
		Me.DeleteAttribute_Command.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.DeleteAttribute_Command.TabStop = True
		Me.DeleteAttribute_Command.Name = "DeleteAttribute_Command"
		Me.SetAttribute_Command.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.SetAttribute_Command.Text = "Set Attribute"
		Me.SetAttribute_Command.Size = New System.Drawing.Size(112, 42)
		Me.SetAttribute_Command.Location = New System.Drawing.Point(310, 70)
		Me.SetAttribute_Command.TabIndex = 1
		Me.SetAttribute_Command.BackColor = System.Drawing.SystemColors.Control
		Me.SetAttribute_Command.CausesValidation = True
		Me.SetAttribute_Command.Enabled = True
		Me.SetAttribute_Command.ForeColor = System.Drawing.SystemColors.ControlText
		Me.SetAttribute_Command.Cursor = System.Windows.Forms.Cursors.Default
		Me.SetAttribute_Command.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.SetAttribute_Command.TabStop = True
		Me.SetAttribute_Command.Name = "SetAttribute_Command"
		Me.SetAttribute_Text.AutoSize = False
		Me.SetAttribute_Text.Size = New System.Drawing.Size(212, 42)
		Me.SetAttribute_Text.Location = New System.Drawing.Point(40, 70)
		Me.SetAttribute_Text.TabIndex = 0
		Me.SetAttribute_Text.AcceptsReturn = True
		Me.SetAttribute_Text.TextAlign = System.Windows.Forms.HorizontalAlignment.Left
		Me.SetAttribute_Text.BackColor = System.Drawing.SystemColors.Window
		Me.SetAttribute_Text.CausesValidation = True
		Me.SetAttribute_Text.Enabled = True
		Me.SetAttribute_Text.ForeColor = System.Drawing.SystemColors.WindowText
		Me.SetAttribute_Text.HideSelection = True
		Me.SetAttribute_Text.ReadOnly = False
		Me.SetAttribute_Text.Maxlength = 0
		Me.SetAttribute_Text.Cursor = System.Windows.Forms.Cursors.IBeam
		Me.SetAttribute_Text.MultiLine = False
		Me.SetAttribute_Text.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.SetAttribute_Text.ScrollBars = System.Windows.Forms.ScrollBars.None
		Me.SetAttribute_Text.TabStop = True
		Me.SetAttribute_Text.Visible = True
		Me.SetAttribute_Text.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
		Me.SetAttribute_Text.Name = "SetAttribute_Text"
		Me.SetAttributesFrame.Size = New System.Drawing.Size(452, 122)
		Me.SetAttributesFrame.Location = New System.Drawing.Point(20, 30)
		Me.SetAttributesFrame.TabIndex = 9
		Me.SetAttributesFrame.BackColor = System.Drawing.SystemColors.Control
		Me.SetAttributesFrame.Enabled = True
		Me.SetAttributesFrame.ForeColor = System.Drawing.SystemColors.ControlText
		Me.SetAttributesFrame.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.SetAttributesFrame.Visible = True
		Me.SetAttributesFrame.Name = "SetAttributesFrame"
		Me.SetAttributeValueLabel.Text = "Attribute Value:"
		Me.SetAttributeValueLabel.Size = New System.Drawing.Size(212, 22)
		Me.SetAttributeValueLabel.Location = New System.Drawing.Point(20, 20)
		Me.SetAttributeValueLabel.TabIndex = 15
		Me.SetAttributeValueLabel.TextAlign = System.Drawing.ContentAlignment.TopLeft
		Me.SetAttributeValueLabel.BackColor = System.Drawing.SystemColors.Control
		Me.SetAttributeValueLabel.Enabled = True
		Me.SetAttributeValueLabel.ForeColor = System.Drawing.SystemColors.ControlText
		Me.SetAttributeValueLabel.Cursor = System.Windows.Forms.Cursors.Default
		Me.SetAttributeValueLabel.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.SetAttributeValueLabel.UseMnemonic = True
		Me.SetAttributeValueLabel.Visible = True
		Me.SetAttributeValueLabel.AutoSize = False
		Me.SetAttributeValueLabel.BorderStyle = System.Windows.Forms.BorderStyle.None
		Me.SetAttributeValueLabel.Name = "SetAttributeValueLabel"
		Me.CreateAttributesLabel.Text = "This sets the attribute value for the selected entity"
		Me.CreateAttributesLabel.Size = New System.Drawing.Size(362, 22)
		Me.CreateAttributesLabel.Location = New System.Drawing.Point(20, 90)
		Me.CreateAttributesLabel.TabIndex = 10
		Me.CreateAttributesLabel.TextAlign = System.Drawing.ContentAlignment.TopLeft
		Me.CreateAttributesLabel.BackColor = System.Drawing.SystemColors.Control
		Me.CreateAttributesLabel.Enabled = True
		Me.CreateAttributesLabel.ForeColor = System.Drawing.SystemColors.ControlText
		Me.CreateAttributesLabel.Cursor = System.Windows.Forms.Cursors.Default
		Me.CreateAttributesLabel.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.CreateAttributesLabel.UseMnemonic = True
		Me.CreateAttributesLabel.Visible = True
		Me.CreateAttributesLabel.AutoSize = False
		Me.CreateAttributesLabel.BorderStyle = System.Windows.Forms.BorderStyle.None
		Me.CreateAttributesLabel.Name = "CreateAttributesLabel"
		Me.GetAttributesFrame.Size = New System.Drawing.Size(452, 122)
		Me.GetAttributesFrame.Location = New System.Drawing.Point(20, 170)
		Me.GetAttributesFrame.TabIndex = 11
		Me.GetAttributesFrame.BackColor = System.Drawing.SystemColors.Control
		Me.GetAttributesFrame.Enabled = True
		Me.GetAttributesFrame.ForeColor = System.Drawing.SystemColors.ControlText
		Me.GetAttributesFrame.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.GetAttributesFrame.Visible = True
		Me.GetAttributesFrame.Name = "GetAttributesFrame"
		Me.GetAttributeValueLabel.Text = "Attribute Value:"
		Me.GetAttributeValueLabel.Size = New System.Drawing.Size(212, 22)
		Me.GetAttributeValueLabel.Location = New System.Drawing.Point(20, 20)
		Me.GetAttributeValueLabel.TabIndex = 16
		Me.GetAttributeValueLabel.TextAlign = System.Drawing.ContentAlignment.TopLeft
		Me.GetAttributeValueLabel.BackColor = System.Drawing.SystemColors.Control
		Me.GetAttributeValueLabel.Enabled = True
		Me.GetAttributeValueLabel.ForeColor = System.Drawing.SystemColors.ControlText
		Me.GetAttributeValueLabel.Cursor = System.Windows.Forms.Cursors.Default
		Me.GetAttributeValueLabel.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.GetAttributeValueLabel.UseMnemonic = True
		Me.GetAttributeValueLabel.Visible = True
		Me.GetAttributeValueLabel.AutoSize = False
		Me.GetAttributeValueLabel.BorderStyle = System.Windows.Forms.BorderStyle.None
		Me.GetAttributeValueLabel.Name = "GetAttributeValueLabel"
		Me.GetAttributesLabel.Text = "This gets the attribute value for the selected entity"
		Me.GetAttributesLabel.Size = New System.Drawing.Size(402, 22)
		Me.GetAttributesLabel.Location = New System.Drawing.Point(20, 90)
		Me.GetAttributesLabel.TabIndex = 12
		Me.GetAttributesLabel.TextAlign = System.Drawing.ContentAlignment.TopLeft
		Me.GetAttributesLabel.BackColor = System.Drawing.SystemColors.Control
		Me.GetAttributesLabel.Enabled = True
		Me.GetAttributesLabel.ForeColor = System.Drawing.SystemColors.ControlText
		Me.GetAttributesLabel.Cursor = System.Windows.Forms.Cursors.Default
		Me.GetAttributesLabel.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.GetAttributesLabel.UseMnemonic = True
		Me.GetAttributesLabel.Visible = True
		Me.GetAttributesLabel.AutoSize = False
		Me.GetAttributesLabel.BorderStyle = System.Windows.Forms.BorderStyle.None
		Me.GetAttributesLabel.Name = "GetAttributesLabel"
		Me.QueryAttributesFrame.Size = New System.Drawing.Size(452, 122)
		Me.QueryAttributesFrame.Location = New System.Drawing.Point(20, 310)
		Me.QueryAttributesFrame.TabIndex = 13
		Me.QueryAttributesFrame.BackColor = System.Drawing.SystemColors.Control
		Me.QueryAttributesFrame.Enabled = True
		Me.QueryAttributesFrame.ForeColor = System.Drawing.SystemColors.ControlText
		Me.QueryAttributesFrame.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.QueryAttributesFrame.Visible = True
		Me.QueryAttributesFrame.Name = "QueryAttributesFrame"
		Me.Clear_Command.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.Clear_Command.Text = "Clear"
		Me.Clear_Command.Size = New System.Drawing.Size(82, 42)
		Me.Clear_Command.Location = New System.Drawing.Point(360, 40)
		Me.Clear_Command.TabIndex = 18
		Me.Clear_Command.BackColor = System.Drawing.SystemColors.Control
		Me.Clear_Command.CausesValidation = True
		Me.Clear_Command.Enabled = True
		Me.Clear_Command.ForeColor = System.Drawing.SystemColors.ControlText
		Me.Clear_Command.Cursor = System.Windows.Forms.Cursors.Default
		Me.Clear_Command.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.Clear_Command.TabStop = True
		Me.Clear_Command.Name = "Clear_Command"
		Me.QueryEntityLabel.Text = "Attribute Value:"
		Me.QueryEntityLabel.Size = New System.Drawing.Size(212, 22)
		Me.QueryEntityLabel.Location = New System.Drawing.Point(20, 20)
		Me.QueryEntityLabel.TabIndex = 17
		Me.QueryEntityLabel.TextAlign = System.Drawing.ContentAlignment.TopLeft
		Me.QueryEntityLabel.BackColor = System.Drawing.SystemColors.Control
		Me.QueryEntityLabel.Enabled = True
		Me.QueryEntityLabel.ForeColor = System.Drawing.SystemColors.ControlText
		Me.QueryEntityLabel.Cursor = System.Windows.Forms.Cursors.Default
		Me.QueryEntityLabel.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.QueryEntityLabel.UseMnemonic = True
		Me.QueryEntityLabel.Visible = True
		Me.QueryEntityLabel.AutoSize = False
		Me.QueryEntityLabel.BorderStyle = System.Windows.Forms.BorderStyle.None
		Me.QueryEntityLabel.Name = "QueryEntityLabel"
		Me.Label1.Text = "This highlights the entities which have the specified attribute value "
		Me.Label1.Size = New System.Drawing.Size(402, 22)
		Me.Label1.Location = New System.Drawing.Point(20, 90)
		Me.Label1.TabIndex = 14
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
		Me.Controls.Add(Save_Command)
		Me.Controls.Add(Close_Command)
		Me.Controls.Add(QueryEntities_Text)
		Me.Controls.Add(QueryEntities_Command)
		Me.Controls.Add(GetAttribute_Command)
		Me.Controls.Add(GetAttribute_Text)
		Me.Controls.Add(DeleteAttribute_Command)
		Me.Controls.Add(SetAttribute_Command)
		Me.Controls.Add(SetAttribute_Text)
		Me.Controls.Add(SetAttributesFrame)
		Me.Controls.Add(GetAttributesFrame)
		Me.Controls.Add(QueryAttributesFrame)
		Me.SetAttributesFrame.Controls.Add(SetAttributeValueLabel)
		Me.SetAttributesFrame.Controls.Add(CreateAttributesLabel)
		Me.GetAttributesFrame.Controls.Add(GetAttributeValueLabel)
		Me.GetAttributesFrame.Controls.Add(GetAttributesLabel)
		Me.QueryAttributesFrame.Controls.Add(Clear_Command)
		Me.QueryAttributesFrame.Controls.Add(QueryEntityLabel)
		Me.QueryAttributesFrame.Controls.Add(Label1)
		Me.SetAttributesFrame.ResumeLayout(False)
		Me.GetAttributesFrame.ResumeLayout(False)
		Me.QueryAttributesFrame.ResumeLayout(False)
		Me.ResumeLayout(False)
		Me.PerformLayout()
	End Sub
#End Region 
End Class