<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> Partial Class ParametersForm
#Region "Windows Form Designer generated code"
    <System.Diagnostics.DebuggerNonUserCode()> Public Sub New(ByVal InventorApp As Inventor.Application, ByVal Analyses As Analyses)
        MyBase.New()

        m_InventorApp = InventorApp
        m_Analyses = Analyses

        m_bIsInitializing = True
        InitializeComponent()
        m_bIsInitializing = False
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

    Private m_InventorApp As Inventor.Application
    Private m_Analyses As Analyses

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer
    Public ToolTip1 As System.Windows.Forms.ToolTip
    Public WithEvents cmdOK As System.Windows.Forms.Button
    Public WithEvents txtSteps As System.Windows.Forms.TextBox
    Public WithEvents cmdAddParam As System.Windows.Forms.Button
    Public WithEvents txtEndValue As System.Windows.Forms.TextBox
    Public WithEvents txtStartValue As System.Windows.Forms.TextBox
    Public WithEvents lstParams As System.Windows.Forms.ListBox
    Public WithEvents Label4 As System.Windows.Forms.Label
    Public WithEvents lblEndValue As System.Windows.Forms.Label
    Public WithEvents lblStartValue As System.Windows.Forms.Label
    Public WithEvents Label1 As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(ParametersForm))
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
        Me.cmdOK = New System.Windows.Forms.Button
        Me.txtSteps = New System.Windows.Forms.TextBox
        Me.cmdAddParam = New System.Windows.Forms.Button
        Me.txtEndValue = New System.Windows.Forms.TextBox
        Me.txtStartValue = New System.Windows.Forms.TextBox
        Me.lstParams = New System.Windows.Forms.ListBox
        Me.Label4 = New System.Windows.Forms.Label
        Me.lblEndValue = New System.Windows.Forms.Label
        Me.lblStartValue = New System.Windows.Forms.Label
        Me.Label1 = New System.Windows.Forms.Label
        Me.SuspendLayout()
        Me.ToolTip1.Active = True
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.Text = "Parameters for Analysis Setup"
        Me.ClientSize = New System.Drawing.Size(363, 174)
        Me.Location = New System.Drawing.Point(17, 93)
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
        Me.Name = "Parameters"
        Me.cmdOK.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdOK.Text = "OK"
        Me.cmdOK.Size = New System.Drawing.Size(57, 21)
        Me.cmdOK.Location = New System.Drawing.Point(300, 148)
        Me.cmdOK.TabIndex = 9
        Me.cmdOK.BackColor = System.Drawing.SystemColors.Control
        Me.cmdOK.CausesValidation = True
        Me.cmdOK.Enabled = True
        Me.cmdOK.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdOK.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdOK.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdOK.TabStop = True
        Me.cmdOK.Name = "cmdOK"
        Me.txtSteps.AutoSize = False
        Me.txtSteps.Size = New System.Drawing.Size(65, 21)
        Me.txtSteps.Location = New System.Drawing.Point(136, 148)
        Me.txtSteps.TabIndex = 7
        Me.txtSteps.Text = "100"
        Me.txtSteps.AcceptsReturn = True
        Me.txtSteps.TextAlign = System.Windows.Forms.HorizontalAlignment.Left
        Me.txtSteps.BackColor = System.Drawing.SystemColors.Window
        Me.txtSteps.CausesValidation = True
        Me.txtSteps.Enabled = True
        Me.txtSteps.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtSteps.HideSelection = True
        Me.txtSteps.ReadOnly = False
        Me.txtSteps.MaxLength = 0
        Me.txtSteps.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtSteps.Multiline = False
        Me.txtSteps.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtSteps.ScrollBars = System.Windows.Forms.ScrollBars.None
        Me.txtSteps.TabStop = True
        Me.txtSteps.Visible = True
        Me.txtSteps.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.txtSteps.Name = "txtSteps"
        Me.cmdAddParam.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        Me.cmdAddParam.Text = "Add Parameter..."
        Me.cmdAddParam.Size = New System.Drawing.Size(101, 25)
        Me.cmdAddParam.Location = New System.Drawing.Point(256, 112)
        Me.cmdAddParam.TabIndex = 6
        Me.cmdAddParam.BackColor = System.Drawing.SystemColors.Control
        Me.cmdAddParam.CausesValidation = True
        Me.cmdAddParam.Enabled = True
        Me.cmdAddParam.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdAddParam.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdAddParam.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdAddParam.TabStop = True
        Me.cmdAddParam.Name = "cmdAddParam"
        Me.txtEndValue.AutoSize = False
        Me.txtEndValue.Size = New System.Drawing.Size(101, 21)
        Me.txtEndValue.Location = New System.Drawing.Point(256, 72)
        Me.txtEndValue.TabIndex = 4
        Me.txtEndValue.AcceptsReturn = True
        Me.txtEndValue.TextAlign = System.Windows.Forms.HorizontalAlignment.Left
        Me.txtEndValue.BackColor = System.Drawing.SystemColors.Window
        Me.txtEndValue.CausesValidation = True
        Me.txtEndValue.Enabled = True
        Me.txtEndValue.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtEndValue.HideSelection = True
        Me.txtEndValue.ReadOnly = False
        Me.txtEndValue.MaxLength = 0
        Me.txtEndValue.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtEndValue.Multiline = False
        Me.txtEndValue.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtEndValue.ScrollBars = System.Windows.Forms.ScrollBars.None
        Me.txtEndValue.TabStop = True
        Me.txtEndValue.Visible = True
        Me.txtEndValue.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.txtEndValue.Name = "txtEndValue"
        Me.txtStartValue.AutoSize = False
        Me.txtStartValue.Size = New System.Drawing.Size(101, 21)
        Me.txtStartValue.Location = New System.Drawing.Point(256, 28)
        Me.txtStartValue.TabIndex = 2
        Me.txtStartValue.AcceptsReturn = True
        Me.txtStartValue.TextAlign = System.Windows.Forms.HorizontalAlignment.Left
        Me.txtStartValue.BackColor = System.Drawing.SystemColors.Window
        Me.txtStartValue.CausesValidation = True
        Me.txtStartValue.Enabled = True
        Me.txtStartValue.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtStartValue.HideSelection = True
        Me.txtStartValue.ReadOnly = False
        Me.txtStartValue.MaxLength = 0
        Me.txtStartValue.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtStartValue.Multiline = False
        Me.txtStartValue.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtStartValue.ScrollBars = System.Windows.Forms.ScrollBars.None
        Me.txtStartValue.TabStop = True
        Me.txtStartValue.Visible = True
        Me.txtStartValue.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.txtStartValue.Name = "txtStartValue"
        Me.lstParams.Size = New System.Drawing.Size(245, 124)
        Me.lstParams.Location = New System.Drawing.Point(4, 20)
        Me.lstParams.TabIndex = 0
        Me.lstParams.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.lstParams.BackColor = System.Drawing.SystemColors.Window
        Me.lstParams.CausesValidation = True
        Me.lstParams.Enabled = True
        Me.lstParams.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lstParams.IntegralHeight = True
        Me.lstParams.Cursor = System.Windows.Forms.Cursors.Default
        Me.lstParams.SelectionMode = System.Windows.Forms.SelectionMode.One
        Me.lstParams.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lstParams.Sorted = False
        Me.lstParams.TabStop = True
        Me.lstParams.Visible = True
        Me.lstParams.MultiColumn = False
        Me.lstParams.Name = "lstParams"
        Me.Label4.Text = "Number of Analysis Steps:"
        Me.Label4.Size = New System.Drawing.Size(141, 13)
        Me.Label4.Location = New System.Drawing.Point(8, 152)
        Me.Label4.TabIndex = 8
        Me.Label4.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.Label4.BackColor = System.Drawing.SystemColors.Control
        Me.Label4.Enabled = True
        Me.Label4.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label4.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label4.UseMnemonic = True
        Me.Label4.Visible = True
        Me.Label4.AutoSize = False
        Me.Label4.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.Label4.Name = "Label4"
        Me.lblEndValue.Text = "End value:"
        Me.lblEndValue.Size = New System.Drawing.Size(73, 13)
        Me.lblEndValue.Location = New System.Drawing.Point(256, 56)
        Me.lblEndValue.TabIndex = 5
        Me.lblEndValue.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblEndValue.BackColor = System.Drawing.SystemColors.Control
        Me.lblEndValue.Enabled = True
        Me.lblEndValue.ForeColor = System.Drawing.SystemColors.ControlText
        Me.lblEndValue.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblEndValue.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblEndValue.UseMnemonic = True
        Me.lblEndValue.Visible = True
        Me.lblEndValue.AutoSize = False
        Me.lblEndValue.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblEndValue.Name = "lblEndValue"
        Me.lblStartValue.Text = "Start value:"
        Me.lblStartValue.Size = New System.Drawing.Size(73, 13)
        Me.lblStartValue.Location = New System.Drawing.Point(256, 12)
        Me.lblStartValue.TabIndex = 3
        Me.lblStartValue.TextAlign = System.Drawing.ContentAlignment.TopLeft
        Me.lblStartValue.BackColor = System.Drawing.SystemColors.Control
        Me.lblStartValue.Enabled = True
        Me.lblStartValue.ForeColor = System.Drawing.SystemColors.ControlText
        Me.lblStartValue.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblStartValue.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblStartValue.UseMnemonic = True
        Me.lblStartValue.Visible = True
        Me.lblStartValue.AutoSize = False
        Me.lblStartValue.BorderStyle = System.Windows.Forms.BorderStyle.None
        Me.lblStartValue.Name = "lblStartValue"
        Me.Label1.Text = "Parameters:"
        Me.Label1.Size = New System.Drawing.Size(113, 13)
        Me.Label1.Location = New System.Drawing.Point(4, 4)
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
        Me.Controls.Add(cmdOK)
        Me.Controls.Add(txtSteps)
        Me.Controls.Add(cmdAddParam)
        Me.Controls.Add(txtEndValue)
        Me.Controls.Add(txtStartValue)
        Me.Controls.Add(lstParams)
        Me.Controls.Add(Label4)
        Me.Controls.Add(lblEndValue)
        Me.Controls.Add(lblStartValue)
        Me.Controls.Add(Label1)
        Me.ResumeLayout(False)
        Me.PerformLayout()
    End Sub
#End Region
End Class