<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class ScanViewsForm
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
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.ExitBut = New System.Windows.Forms.Button()
        Me.ListBox1 = New System.Windows.Forms.ListBox()
        Me.SuspendLayout()
        '
        'ExitBut
        '
        Me.ExitBut.BackColor = System.Drawing.SystemColors.Control
        Me.ExitBut.Cursor = System.Windows.Forms.Cursors.Default
        Me.ExitBut.ForeColor = System.Drawing.SystemColors.ControlText
        Me.ExitBut.Location = New System.Drawing.Point(20, 770)
        Me.ExitBut.Name = "ExitBut"
        Me.ExitBut.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.ExitBut.Size = New System.Drawing.Size(572, 52)
        Me.ExitBut.TabIndex = 3
        Me.ExitBut.Text = "Exit"
        Me.ExitBut.UseVisualStyleBackColor = False
        '
        'ListBox1
        '
        Me.ListBox1.BackColor = System.Drawing.SystemColors.Window
        Me.ListBox1.Cursor = System.Windows.Forms.Cursors.Default
        Me.ListBox1.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.ListBox1.ForeColor = System.Drawing.SystemColors.WindowText
        Me.ListBox1.ItemHeight = 18
        Me.ListBox1.Location = New System.Drawing.Point(20, 20)
        Me.ListBox1.Name = "ListBox1"
        Me.ListBox1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.ListBox1.Size = New System.Drawing.Size(572, 724)
        Me.ListBox1.TabIndex = 2
        '
        'ScanViewsForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(8.0!, 16.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(615, 838)
        Me.Controls.Add(Me.ExitBut)
        Me.Controls.Add(Me.ListBox1)
        Me.Name = "ScanViewsForm"
        Me.Text = "ScanViewsForm"
        Me.ResumeLayout(False)

    End Sub
    Public WithEvents ToolTip1 As System.Windows.Forms.ToolTip
    Public WithEvents ExitBut As System.Windows.Forms.Button
    Public WithEvents ListBox1 As System.Windows.Forms.ListBox
End Class
