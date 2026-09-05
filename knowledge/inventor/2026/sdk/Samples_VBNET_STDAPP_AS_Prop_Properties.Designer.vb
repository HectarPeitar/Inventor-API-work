<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> Partial Class frmProperties
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
	Public WithEvents cmdCancel As System.Windows.Forms.Button
	Public WithEvents cmdSaveChanges As System.Windows.Forms.Button
	Public WithEvents lstProperties As System.Windows.Forms.ListBox
	Public WithEvents cmdBrowse As System.Windows.Forms.Button
	Public WithEvents txtFilename As System.Windows.Forms.TextBox
	Public CommonDialog1Open As System.Windows.Forms.OpenFileDialog
	Public WithEvents Label2 As System.Windows.Forms.Label
	Public WithEvents Label1 As System.Windows.Forms.Label
	'NOTE: The following procedure is required by the Windows Form Designer
	'It can be modified using the Windows Form Designer.
	'Do not modify it using the code editor.
	<System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdCancel = New System.Windows.Forms.Button()
        Me.cmdSaveChanges = New System.Windows.Forms.Button()
        Me.lstProperties = New System.Windows.Forms.ListBox()
        Me.cmdBrowse = New System.Windows.Forms.Button()
        Me.txtFilename = New System.Windows.Forms.TextBox()
        Me.CommonDialog1Open = New System.Windows.Forms.OpenFileDialog()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'cmdCancel
        '
        Me.cmdCancel.BackColor = System.Drawing.SystemColors.Control
        Me.cmdCancel.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdCancel.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdCancel.Location = New System.Drawing.Point(685, 510)
        Me.cmdCancel.Name = "cmdCancel"
        Me.cmdCancel.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdCancel.Size = New System.Drawing.Size(102, 32)
        Me.cmdCancel.TabIndex = 6
        Me.cmdCancel.Text = "Cancel"
        Me.cmdCancel.UseVisualStyleBackColor = False
        '
        'cmdSaveChanges
        '
        Me.cmdSaveChanges.BackColor = System.Drawing.SystemColors.Control
        Me.cmdSaveChanges.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdSaveChanges.Enabled = False
        Me.cmdSaveChanges.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdSaveChanges.Location = New System.Drawing.Point(570, 510)
        Me.cmdSaveChanges.Name = "cmdSaveChanges"
        Me.cmdSaveChanges.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdSaveChanges.Size = New System.Drawing.Size(112, 32)
        Me.cmdSaveChanges.TabIndex = 4
        Me.cmdSaveChanges.Text = "Save and Exit"
        Me.cmdSaveChanges.UseVisualStyleBackColor = False
        '
        'lstProperties
        '
        Me.lstProperties.BackColor = System.Drawing.SystemColors.Window
        Me.lstProperties.Cursor = System.Windows.Forms.Cursors.Default
        Me.lstProperties.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lstProperties.ItemHeight = 16
        Me.lstProperties.Location = New System.Drawing.Point(10, 40)
        Me.lstProperties.Name = "lstProperties"
        Me.lstProperties.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lstProperties.Size = New System.Drawing.Size(777, 452)
        Me.lstProperties.TabIndex = 3
        '
        'cmdBrowse
        '
        Me.cmdBrowse.BackColor = System.Drawing.SystemColors.Control
        Me.cmdBrowse.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdBrowse.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdBrowse.Location = New System.Drawing.Point(700, 2)
        Me.cmdBrowse.Name = "cmdBrowse"
        Me.cmdBrowse.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdBrowse.Size = New System.Drawing.Size(87, 27)
        Me.cmdBrowse.TabIndex = 2
        Me.cmdBrowse.Text = "Browse..."
        Me.cmdBrowse.UseVisualStyleBackColor = False
        '
        'txtFilename
        '
        Me.txtFilename.AcceptsReturn = True
        Me.txtFilename.BackColor = System.Drawing.SystemColors.Window
        Me.txtFilename.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtFilename.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtFilename.Location = New System.Drawing.Point(84, 5)
        Me.txtFilename.MaxLength = 0
        Me.txtFilename.Name = "txtFilename"
        Me.txtFilename.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtFilename.Size = New System.Drawing.Size(613, 22)
        Me.txtFilename.TabIndex = 0
        '
        'Label2
        '
        Me.Label2.BackColor = System.Drawing.SystemColors.Control
        Me.Label2.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label2.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label2.Location = New System.Drawing.Point(15, 505)
        Me.Label2.Name = "Label2"
        Me.Label2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label2.Size = New System.Drawing.Size(407, 27)
        Me.Label2.TabIndex = 5
        Me.Label2.Text = "Double-click property to edit."
        '
        'Label1
        '
        Me.Label1.BackColor = System.Drawing.SystemColors.Control
        Me.Label1.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label1.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label1.Location = New System.Drawing.Point(10, 10)
        Me.Label1.Name = "Label1"
        Me.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label1.Size = New System.Drawing.Size(82, 17)
        Me.Label1.TabIndex = 1
        Me.Label1.Text = "Filename:"
        '
        'frmProperties
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(8.0!, 16.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.SystemColors.Control
        Me.ClientSize = New System.Drawing.Size(794, 547)
        Me.Controls.Add(Me.cmdCancel)
        Me.Controls.Add(Me.cmdSaveChanges)
        Me.Controls.Add(Me.lstProperties)
        Me.Controls.Add(Me.cmdBrowse)
        Me.Controls.Add(Me.txtFilename)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Cursor = System.Windows.Forms.Cursors.Default
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.Location = New System.Drawing.Point(4, 28)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "frmProperties"
        Me.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "File Property Viewer/Editor"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
#End Region 
End Class