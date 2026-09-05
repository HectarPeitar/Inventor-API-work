<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> Partial Class frmThumbnail
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
	Public WithEvents picThumbnail As System.Windows.Forms.PictureBox
	'NOTE: The following procedure is required by the Windows Form Designer
	'It can be modified using the Windows Form Designer.
	'Do not modify it using the code editor.
	<System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.picThumbnail = New System.Windows.Forms.PictureBox()
        CType(Me.picThumbnail, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'picThumbnail
        '
        Me.picThumbnail.BackColor = System.Drawing.SystemColors.Control
        Me.picThumbnail.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.picThumbnail.Cursor = System.Windows.Forms.Cursors.Default
        Me.picThumbnail.ForeColor = System.Drawing.SystemColors.ControlText
        Me.picThumbnail.Location = New System.Drawing.Point(5, 5)
        Me.picThumbnail.Name = "picThumbnail"
        Me.picThumbnail.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.picThumbnail.Size = New System.Drawing.Size(400, 400)
        Me.picThumbnail.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage
        Me.picThumbnail.TabIndex = 0
        Me.picThumbnail.TabStop = False
        '
        'frmThumbnail
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(8.0!, 16.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.SystemColors.Control
        Me.ClientSize = New System.Drawing.Size(412, 414)
        Me.Controls.Add(Me.picThumbnail)
        Me.Cursor = System.Windows.Forms.Cursors.Default
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.Location = New System.Drawing.Point(4, 28)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "frmThumbnail"
        Me.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent
        Me.Text = "Thumbnail"
        CType(Me.picThumbnail, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub
#End Region 
End Class