<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> Partial Class ParamListForm
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
    Public WithEvents lstParams As System.Windows.Forms.ListBox
    Public WithEvents cmdOK As System.Windows.Forms.Button
    Public WithEvents Label1 As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(ParamListForm))
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
        Me.lstParams = New System.Windows.Forms.ListBox
        Me.cmdOK = New System.Windows.Forms.Button
        Me.Label1 = New System.Windows.Forms.Label
        Me.SuspendLayout()
        Me.ToolTip1.Active = True
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.Text = "Analysis Parameters"
        Me.ClientSize = New System.Drawing.Size(297, 225)
        Me.Location = New System.Drawing.Point(143, 150)
        Me.ControlBox = False
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.SystemColors.Control
        Me.Enabled = True
        Me.KeyPreview = False
        Me.Cursor = System.Windows.Forms.Cursors.Default
        Me.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.ShowInTaskbar = True
        Me.HelpButton = False
        Me.WindowState = System.Windows.Forms.FormWindowState.Normal
        Me.Name = "ParamListForm"
        Me.lstParams.Size = New System.Drawing.Size(233, 202)
        Me.lstParams.Location = New System.Drawing.Point(4, 20)
        Me.lstParams.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended
        Me.lstParams.TabIndex = 1
        Me.lstParams.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.lstParams.BackColor = System.Drawing.SystemColors.Window
        Me.lstParams.CausesValidation = True
        Me.lstParams.Enabled = True
        Me.lstParams.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lstParams.IntegralHeight = True
        Me.lstParams.Cursor = System.Windows.Forms.Cursors.Default
        Me.lstParams.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lstParams.Sorted = False
        Me.lstParams.TabStop = True
        Me.lstParams.Visible = True
        Me.lstParams.MultiColumn = False
        Me.lstParams.Name = "lstParams"
        Me.cmdOK.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdOK.Text = "OK"
        Me.cmdOK.Size = New System.Drawing.Size(49, 25)
        Me.cmdOK.Location = New System.Drawing.Point(244, 196)
        Me.cmdOK.TabIndex = 0
        Me.cmdOK.BackColor = System.Drawing.SystemColors.Control
        Me.cmdOK.CausesValidation = True
        Me.cmdOK.Enabled = True
        Me.cmdOK.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdOK.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdOK.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdOK.TabStop = True
        Me.cmdOK.Name = "cmdOK"
        Me.Label1.Text = "Select parameters to use in the analysis."
        Me.Label1.Size = New System.Drawing.Size(205, 13)
        Me.Label1.Location = New System.Drawing.Point(4, 4)
        Me.Label1.TabIndex = 2
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
        Me.Controls.Add(lstParams)
        Me.Controls.Add(cmdOK)
        Me.Controls.Add(Label1)
        Me.ResumeLayout(False)
        Me.PerformLayout()
    End Sub
#End Region
End Class