<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> Partial Class frmUOM
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
	Public WithEvents txtOutputUnit As System.Windows.Forms.TextBox
	Public WithEvents txtResultValue As System.Windows.Forms.TextBox
	Public WithEvents txtInputUnit As System.Windows.Forms.TextBox
	Public WithEvents txtInputValue As System.Windows.Forms.TextBox
	Public WithEvents Line3 As System.Windows.Forms.Label
	Public WithEvents Line2 As System.Windows.Forms.Label
	Public WithEvents Line1 As System.Windows.Forms.Label
	Public WithEvents Label5 As System.Windows.Forms.Label
	Public WithEvents Label9 As System.Windows.Forms.Label
	Public WithEvents Label1 As System.Windows.Forms.Label
	Public WithEvents Frame3 As System.Windows.Forms.GroupBox
	Public WithEvents cboTimeUnits As System.Windows.Forms.ComboBox
	Public WithEvents cboAnglePrecision As System.Windows.Forms.ComboBox
	Public WithEvents cboAngleUnits As System.Windows.Forms.ComboBox
	Public WithEvents cboMassUnits As System.Windows.Forms.ComboBox
	Public WithEvents cboLengthPrecision As System.Windows.Forms.ComboBox
	Public WithEvents cboLengthUnits As System.Windows.Forms.ComboBox
	Public WithEvents Label12 As System.Windows.Forms.Label
	Public WithEvents Label11 As System.Windows.Forms.Label
	Public WithEvents Label10 As System.Windows.Forms.Label
	Public WithEvents Label8 As System.Windows.Forms.Label
	Public WithEvents Label7 As System.Windows.Forms.Label
	Public WithEvents Label6 As System.Windows.Forms.Label
	Public WithEvents Frame2 As System.Windows.Forms.GroupBox
	Public WithEvents cboUnitType As System.Windows.Forms.ComboBox
	Public WithEvents txtInput As System.Windows.Forms.TextBox
	Public WithEvents txtOutputEntry As System.Windows.Forms.TextBox
	Public WithEvents txtOutputDisplay As System.Windows.Forms.TextBox
	Public WithEvents txtResult As System.Windows.Forms.TextBox
	Public WithEvents Label14 As System.Windows.Forms.Label
	Public WithEvents lblResultType As System.Windows.Forms.Label
	Public WithEvents lblInputType As System.Windows.Forms.Label
	Public WithEvents Label2 As System.Windows.Forms.Label
	Public WithEvents Label3 As System.Windows.Forms.Label
	Public WithEvents Label4 As System.Windows.Forms.Label
	Public WithEvents Frame1 As System.Windows.Forms.GroupBox
	'NOTE: The following procedure is required by the Windows Form Designer
	'It can be modified using the Windows Form Designer.
	'Do not modify it using the code editor.
	<System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.Frame3 = New System.Windows.Forms.GroupBox()
        Me.txtOutputUnit = New System.Windows.Forms.TextBox()
        Me.txtResultValue = New System.Windows.Forms.TextBox()
        Me.txtInputUnit = New System.Windows.Forms.TextBox()
        Me.txtInputValue = New System.Windows.Forms.TextBox()
        Me.Line3 = New System.Windows.Forms.Label()
        Me.Line2 = New System.Windows.Forms.Label()
        Me.Line1 = New System.Windows.Forms.Label()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.Label9 = New System.Windows.Forms.Label()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Frame2 = New System.Windows.Forms.GroupBox()
        Me.cboTimeUnits = New System.Windows.Forms.ComboBox()
        Me.cboAnglePrecision = New System.Windows.Forms.ComboBox()
        Me.cboAngleUnits = New System.Windows.Forms.ComboBox()
        Me.cboMassUnits = New System.Windows.Forms.ComboBox()
        Me.cboLengthPrecision = New System.Windows.Forms.ComboBox()
        Me.cboLengthUnits = New System.Windows.Forms.ComboBox()
        Me.Label12 = New System.Windows.Forms.Label()
        Me.Label11 = New System.Windows.Forms.Label()
        Me.Label10 = New System.Windows.Forms.Label()
        Me.Label8 = New System.Windows.Forms.Label()
        Me.Label7 = New System.Windows.Forms.Label()
        Me.Label6 = New System.Windows.Forms.Label()
        Me.Frame1 = New System.Windows.Forms.GroupBox()
        Me.cboUnitType = New System.Windows.Forms.ComboBox()
        Me.txtInput = New System.Windows.Forms.TextBox()
        Me.txtOutputEntry = New System.Windows.Forms.TextBox()
        Me.txtOutputDisplay = New System.Windows.Forms.TextBox()
        Me.txtResult = New System.Windows.Forms.TextBox()
        Me.Label14 = New System.Windows.Forms.Label()
        Me.lblResultType = New System.Windows.Forms.Label()
        Me.lblInputType = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.Frame3.SuspendLayout()
        Me.Frame2.SuspendLayout()
        Me.Frame1.SuspendLayout()
        Me.SuspendLayout()
        '
        'Frame3
        '
        Me.Frame3.BackColor = System.Drawing.SystemColors.Control
        Me.Frame3.Controls.Add(Me.txtOutputUnit)
        Me.Frame3.Controls.Add(Me.txtResultValue)
        Me.Frame3.Controls.Add(Me.txtInputUnit)
        Me.Frame3.Controls.Add(Me.txtInputValue)
        Me.Frame3.Controls.Add(Me.Line3)
        Me.Frame3.Controls.Add(Me.Line2)
        Me.Frame3.Controls.Add(Me.Line1)
        Me.Frame3.Controls.Add(Me.Label5)
        Me.Frame3.Controls.Add(Me.Label9)
        Me.Frame3.Controls.Add(Me.Label1)
        Me.Frame3.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Frame3.Location = New System.Drawing.Point(5, 352)
        Me.Frame3.Name = "Frame3"
        Me.Frame3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Frame3.Size = New System.Drawing.Size(541, 84)
        Me.Frame3.TabIndex = 25
        Me.Frame3.TabStop = False
        Me.Frame3.Text = "Convert Units"
        '
        'txtOutputUnit
        '
        Me.txtOutputUnit.AcceptsReturn = True
        Me.txtOutputUnit.BackColor = System.Drawing.SystemColors.Window
        Me.txtOutputUnit.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtOutputUnit.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtOutputUnit.Location = New System.Drawing.Point(449, 50)
        Me.txtOutputUnit.MaxLength = 0
        Me.txtOutputUnit.Name = "txtOutputUnit"
        Me.txtOutputUnit.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtOutputUnit.Size = New System.Drawing.Size(67, 24)
        Me.txtOutputUnit.TabIndex = 31
        '
        'txtResultValue
        '
        Me.txtResultValue.AcceptsReturn = True
        Me.txtResultValue.BackColor = System.Drawing.SystemColors.Control
        Me.txtResultValue.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtResultValue.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtResultValue.Location = New System.Drawing.Point(325, 50)
        Me.txtResultValue.MaxLength = 0
        Me.txtResultValue.Name = "txtResultValue"
        Me.txtResultValue.ReadOnly = True
        Me.txtResultValue.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtResultValue.Size = New System.Drawing.Size(117, 24)
        Me.txtResultValue.TabIndex = 30
        '
        'txtInputUnit
        '
        Me.txtInputUnit.AcceptsReturn = True
        Me.txtInputUnit.BackColor = System.Drawing.SystemColors.Window
        Me.txtInputUnit.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtInputUnit.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtInputUnit.Location = New System.Drawing.Point(134, 50)
        Me.txtInputUnit.MaxLength = 0
        Me.txtInputUnit.Name = "txtInputUnit"
        Me.txtInputUnit.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtInputUnit.Size = New System.Drawing.Size(67, 24)
        Me.txtInputUnit.TabIndex = 29
        '
        'txtInputValue
        '
        Me.txtInputValue.AcceptsReturn = True
        Me.txtInputValue.BackColor = System.Drawing.SystemColors.Window
        Me.txtInputValue.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtInputValue.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtInputValue.Location = New System.Drawing.Point(10, 50)
        Me.txtInputValue.MaxLength = 0
        Me.txtInputValue.Name = "txtInputValue"
        Me.txtInputValue.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtInputValue.Size = New System.Drawing.Size(117, 24)
        Me.txtInputValue.TabIndex = 28
        Me.txtInputValue.Text = "0"
        '
        'Line3
        '
        Me.Line3.BackColor = System.Drawing.Color.Red
        Me.Line3.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.Line3.ForeColor = System.Drawing.Color.Black
        Me.Line3.Location = New System.Drawing.Point(307, 61)
        Me.Line3.Name = "Line3"
        Me.Line3.Size = New System.Drawing.Size(10, 11)
        Me.Line3.TabIndex = 32
        Me.Line3.Text = "Line3"
        '
        'Line2
        '
        Me.Line2.BackColor = System.Drawing.Color.Red
        Me.Line2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.Line2.ForeColor = System.Drawing.Color.Black
        Me.Line2.Location = New System.Drawing.Point(307, 50)
        Me.Line2.Name = "Line2"
        Me.Line2.Size = New System.Drawing.Size(10, 11)
        Me.Line2.TabIndex = 33
        Me.Line2.Text = "Line2"
        '
        'Line1
        '
        Me.Line1.BackColor = System.Drawing.SystemColors.WindowText
        Me.Line1.Location = New System.Drawing.Point(217, 61)
        Me.Line1.Name = "Line1"
        Me.Line1.Size = New System.Drawing.Size(100, 1)
        Me.Line1.TabIndex = 34
        '
        'Label5
        '
        Me.Label5.BackColor = System.Drawing.SystemColors.Control
        Me.Label5.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label5.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label5.Location = New System.Drawing.Point(234, 42)
        Me.Label5.Name = "Label5"
        Me.Label5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label5.Size = New System.Drawing.Size(75, 21)
        Me.Label5.TabIndex = 32
        Me.Label5.Text = "Convert To"
        '
        'Label9
        '
        Me.Label9.BackColor = System.Drawing.SystemColors.Control
        Me.Label9.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label9.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label9.Location = New System.Drawing.Point(325, 27)
        Me.Label9.Name = "Label9"
        Me.Label9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label9.Size = New System.Drawing.Size(209, 22)
        Me.Label9.TabIndex = 27
        Me.Label9.Text = "Output double value + string units:"
        '
        'Label1
        '
        Me.Label1.BackColor = System.Drawing.SystemColors.Control
        Me.Label1.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label1.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label1.Location = New System.Drawing.Point(10, 27)
        Me.Label1.Name = "Label1"
        Me.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label1.Size = New System.Drawing.Size(209, 22)
        Me.Label1.TabIndex = 26
        Me.Label1.Text = "Input double value + string units:"
        '
        'Frame2
        '
        Me.Frame2.BackColor = System.Drawing.SystemColors.Control
        Me.Frame2.Controls.Add(Me.cboTimeUnits)
        Me.Frame2.Controls.Add(Me.cboAnglePrecision)
        Me.Frame2.Controls.Add(Me.cboAngleUnits)
        Me.Frame2.Controls.Add(Me.cboMassUnits)
        Me.Frame2.Controls.Add(Me.cboLengthPrecision)
        Me.Frame2.Controls.Add(Me.cboLengthUnits)
        Me.Frame2.Controls.Add(Me.Label12)
        Me.Frame2.Controls.Add(Me.Label11)
        Me.Frame2.Controls.Add(Me.Label10)
        Me.Frame2.Controls.Add(Me.Label8)
        Me.Frame2.Controls.Add(Me.Label7)
        Me.Frame2.Controls.Add(Me.Label6)
        Me.Frame2.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Frame2.Location = New System.Drawing.Point(5, 201)
        Me.Frame2.Name = "Frame2"
        Me.Frame2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Frame2.Size = New System.Drawing.Size(547, 142)
        Me.Frame2.TabIndex = 12
        Me.Frame2.TabStop = False
        Me.Frame2.Text = "Unit Settings"
        '
        'cboTimeUnits
        '
        Me.cboTimeUnits.BackColor = System.Drawing.SystemColors.Window
        Me.cboTimeUnits.Cursor = System.Windows.Forms.Cursors.Default
        Me.cboTimeUnits.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboTimeUnits.ForeColor = System.Drawing.SystemColors.WindowText
        Me.cboTimeUnits.Location = New System.Drawing.Point(335, 105)
        Me.cboTimeUnits.Name = "cboTimeUnits"
        Me.cboTimeUnits.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cboTimeUnits.Size = New System.Drawing.Size(202, 24)
        Me.cboTimeUnits.TabIndex = 23
        '
        'cboAnglePrecision
        '
        Me.cboAnglePrecision.BackColor = System.Drawing.SystemColors.Window
        Me.cboAnglePrecision.Cursor = System.Windows.Forms.Cursors.Default
        Me.cboAnglePrecision.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboAnglePrecision.ForeColor = System.Drawing.SystemColors.WindowText
        Me.cboAnglePrecision.Location = New System.Drawing.Point(225, 105)
        Me.cboAnglePrecision.Name = "cboAnglePrecision"
        Me.cboAnglePrecision.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cboAnglePrecision.Size = New System.Drawing.Size(67, 24)
        Me.cboAnglePrecision.TabIndex = 21
        '
        'cboAngleUnits
        '
        Me.cboAngleUnits.BackColor = System.Drawing.SystemColors.Window
        Me.cboAngleUnits.Cursor = System.Windows.Forms.Cursors.Default
        Me.cboAngleUnits.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboAngleUnits.ForeColor = System.Drawing.SystemColors.WindowText
        Me.cboAngleUnits.Location = New System.Drawing.Point(10, 105)
        Me.cboAngleUnits.Name = "cboAngleUnits"
        Me.cboAngleUnits.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cboAngleUnits.Size = New System.Drawing.Size(202, 24)
        Me.cboAngleUnits.TabIndex = 19
        '
        'cboMassUnits
        '
        Me.cboMassUnits.BackColor = System.Drawing.SystemColors.Window
        Me.cboMassUnits.Cursor = System.Windows.Forms.Cursors.Default
        Me.cboMassUnits.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboMassUnits.ForeColor = System.Drawing.SystemColors.WindowText
        Me.cboMassUnits.Location = New System.Drawing.Point(335, 40)
        Me.cboMassUnits.Name = "cboMassUnits"
        Me.cboMassUnits.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cboMassUnits.Size = New System.Drawing.Size(202, 24)
        Me.cboMassUnits.TabIndex = 17
        '
        'cboLengthPrecision
        '
        Me.cboLengthPrecision.BackColor = System.Drawing.SystemColors.Window
        Me.cboLengthPrecision.Cursor = System.Windows.Forms.Cursors.Default
        Me.cboLengthPrecision.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboLengthPrecision.ForeColor = System.Drawing.SystemColors.WindowText
        Me.cboLengthPrecision.Location = New System.Drawing.Point(225, 40)
        Me.cboLengthPrecision.Name = "cboLengthPrecision"
        Me.cboLengthPrecision.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cboLengthPrecision.Size = New System.Drawing.Size(67, 24)
        Me.cboLengthPrecision.TabIndex = 15
        '
        'cboLengthUnits
        '
        Me.cboLengthUnits.BackColor = System.Drawing.SystemColors.Window
        Me.cboLengthUnits.Cursor = System.Windows.Forms.Cursors.Default
        Me.cboLengthUnits.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboLengthUnits.ForeColor = System.Drawing.SystemColors.WindowText
        Me.cboLengthUnits.Location = New System.Drawing.Point(10, 40)
        Me.cboLengthUnits.Name = "cboLengthUnits"
        Me.cboLengthUnits.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cboLengthUnits.Size = New System.Drawing.Size(202, 24)
        Me.cboLengthUnits.TabIndex = 13
        '
        'Label12
        '
        Me.Label12.BackColor = System.Drawing.SystemColors.Control
        Me.Label12.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label12.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label12.Location = New System.Drawing.Point(335, 85)
        Me.Label12.Name = "Label12"
        Me.Label12.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label12.Size = New System.Drawing.Size(117, 22)
        Me.Label12.TabIndex = 24
        Me.Label12.Text = "Time Units:"
        '
        'Label11
        '
        Me.Label11.BackColor = System.Drawing.SystemColors.Control
        Me.Label11.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label11.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label11.Location = New System.Drawing.Point(225, 85)
        Me.Label11.Name = "Label11"
        Me.Label11.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label11.Size = New System.Drawing.Size(84, 22)
        Me.Label11.TabIndex = 22
        Me.Label11.Text = "Precision:"
        '
        'Label10
        '
        Me.Label10.BackColor = System.Drawing.SystemColors.Control
        Me.Label10.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label10.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label10.Location = New System.Drawing.Point(10, 85)
        Me.Label10.Name = "Label10"
        Me.Label10.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label10.Size = New System.Drawing.Size(117, 22)
        Me.Label10.TabIndex = 20
        Me.Label10.Text = "Angle Units:"
        '
        'Label8
        '
        Me.Label8.BackColor = System.Drawing.SystemColors.Control
        Me.Label8.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label8.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label8.Location = New System.Drawing.Point(335, 20)
        Me.Label8.Name = "Label8"
        Me.Label8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label8.Size = New System.Drawing.Size(117, 22)
        Me.Label8.TabIndex = 18
        Me.Label8.Text = "Mass Units:"
        '
        'Label7
        '
        Me.Label7.BackColor = System.Drawing.SystemColors.Control
        Me.Label7.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label7.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label7.Location = New System.Drawing.Point(225, 20)
        Me.Label7.Name = "Label7"
        Me.Label7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label7.Size = New System.Drawing.Size(84, 22)
        Me.Label7.TabIndex = 16
        Me.Label7.Text = "Precision:"
        '
        'Label6
        '
        Me.Label6.BackColor = System.Drawing.SystemColors.Control
        Me.Label6.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label6.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label6.Location = New System.Drawing.Point(10, 20)
        Me.Label6.Name = "Label6"
        Me.Label6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label6.Size = New System.Drawing.Size(117, 22)
        Me.Label6.TabIndex = 14
        Me.Label6.Text = "Length Units:"
        '
        'Frame1
        '
        Me.Frame1.BackColor = System.Drawing.SystemColors.Control
        Me.Frame1.Controls.Add(Me.cboUnitType)
        Me.Frame1.Controls.Add(Me.txtInput)
        Me.Frame1.Controls.Add(Me.txtOutputEntry)
        Me.Frame1.Controls.Add(Me.txtOutputDisplay)
        Me.Frame1.Controls.Add(Me.txtResult)
        Me.Frame1.Controls.Add(Me.Label14)
        Me.Frame1.Controls.Add(Me.lblResultType)
        Me.Frame1.Controls.Add(Me.lblInputType)
        Me.Frame1.Controls.Add(Me.Label2)
        Me.Frame1.Controls.Add(Me.Label3)
        Me.Frame1.Controls.Add(Me.Label4)
        Me.Frame1.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Frame1.Location = New System.Drawing.Point(5, 5)
        Me.Frame1.Name = "Frame1"
        Me.Frame1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Frame1.Size = New System.Drawing.Size(547, 190)
        Me.Frame1.TabIndex = 0
        Me.Frame1.TabStop = False
        Me.Frame1.Text = "User Interaction"
        '
        'cboUnitType
        '
        Me.cboUnitType.BackColor = System.Drawing.SystemColors.Window
        Me.cboUnitType.Cursor = System.Windows.Forms.Cursors.Default
        Me.cboUnitType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboUnitType.ForeColor = System.Drawing.SystemColors.WindowText
        Me.cboUnitType.Location = New System.Drawing.Point(235, 20)
        Me.cboUnitType.Name = "cboUnitType"
        Me.cboUnitType.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cboUnitType.Size = New System.Drawing.Size(137, 24)
        Me.cboUnitType.TabIndex = 11
        '
        'txtInput
        '
        Me.txtInput.AcceptsReturn = True
        Me.txtInput.BackColor = System.Drawing.SystemColors.Window
        Me.txtInput.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtInput.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtInput.Location = New System.Drawing.Point(10, 70)
        Me.txtInput.MaxLength = 0
        Me.txtInput.Name = "txtInput"
        Me.txtInput.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtInput.Size = New System.Drawing.Size(268, 27)
        Me.txtInput.TabIndex = 4
        '
        'txtOutputEntry
        '
        Me.txtOutputEntry.AcceptsReturn = True
        Me.txtOutputEntry.BackColor = System.Drawing.SystemColors.Window
        Me.txtOutputEntry.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtOutputEntry.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtOutputEntry.Location = New System.Drawing.Point(10, 135)
        Me.txtOutputEntry.MaxLength = 0
        Me.txtOutputEntry.Name = "txtOutputEntry"
        Me.txtOutputEntry.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtOutputEntry.Size = New System.Drawing.Size(102, 27)
        Me.txtOutputEntry.TabIndex = 3
        Me.txtOutputEntry.Text = "0"
        '
        'txtOutputDisplay
        '
        Me.txtOutputDisplay.AcceptsReturn = True
        Me.txtOutputDisplay.BackColor = System.Drawing.SystemColors.Control
        Me.txtOutputDisplay.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtOutputDisplay.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtOutputDisplay.Location = New System.Drawing.Point(237, 135)
        Me.txtOutputDisplay.MaxLength = 0
        Me.txtOutputDisplay.Name = "txtOutputDisplay"
        Me.txtOutputDisplay.ReadOnly = True
        Me.txtOutputDisplay.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtOutputDisplay.Size = New System.Drawing.Size(300, 27)
        Me.txtOutputDisplay.TabIndex = 2
        '
        'txtResult
        '
        Me.txtResult.AcceptsReturn = True
        Me.txtResult.BackColor = System.Drawing.SystemColors.Control
        Me.txtResult.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtResult.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtResult.Location = New System.Drawing.Point(380, 70)
        Me.txtResult.MaxLength = 0
        Me.txtResult.Name = "txtResult"
        Me.txtResult.ReadOnly = True
        Me.txtResult.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtResult.Size = New System.Drawing.Size(102, 27)
        Me.txtResult.TabIndex = 1
        '
        'Label14
        '
        Me.Label14.BackColor = System.Drawing.SystemColors.Control
        Me.Label14.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label14.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label14.Location = New System.Drawing.Point(165, 25)
        Me.Label14.Name = "Label14"
        Me.Label14.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label14.Size = New System.Drawing.Size(67, 22)
        Me.Label14.TabIndex = 10
        Me.Label14.Text = "Unit Type:"
        Me.Label14.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'lblResultType
        '
        Me.lblResultType.BackColor = System.Drawing.SystemColors.Control
        Me.lblResultType.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblResultType.ForeColor = System.Drawing.SystemColors.ControlText
        Me.lblResultType.Location = New System.Drawing.Point(485, 75)
        Me.lblResultType.Name = "lblResultType"
        Me.lblResultType.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblResultType.Size = New System.Drawing.Size(57, 22)
        Me.lblResultType.TabIndex = 9
        Me.lblResultType.Text = "cm."
        '
        'lblInputType
        '
        Me.lblInputType.BackColor = System.Drawing.SystemColors.Control
        Me.lblInputType.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblInputType.ForeColor = System.Drawing.SystemColors.ControlText
        Me.lblInputType.Location = New System.Drawing.Point(10, 115)
        Me.lblInputType.Name = "lblInputType"
        Me.lblInputType.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblInputType.Size = New System.Drawing.Size(212, 22)
        Me.lblInputType.TabIndex = 8
        Me.lblInputType.Text = "Internal double value in cm:"
        '
        'Label2
        '
        Me.Label2.BackColor = System.Drawing.SystemColors.Control
        Me.Label2.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label2.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label2.Location = New System.Drawing.Point(115, 140)
        Me.Label2.Name = "Label2"
        Me.Label2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label2.Size = New System.Drawing.Size(127, 22)
        Me.Label2.TabIndex = 7
        Me.Label2.Text = "results in string"
        Me.Label2.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'Label3
        '
        Me.Label3.BackColor = System.Drawing.SystemColors.Control
        Me.Label3.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label3.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label3.Location = New System.Drawing.Point(10, 50)
        Me.Label3.Name = "Label3"
        Me.Label3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label3.Size = New System.Drawing.Size(212, 22)
        Me.Label3.TabIndex = 6
        Me.Label3.Text = "String entered by user:"
        '
        'Label4
        '
        Me.Label4.BackColor = System.Drawing.SystemColors.Control
        Me.Label4.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label4.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label4.Location = New System.Drawing.Point(285, 73)
        Me.Label4.Name = "Label4"
        Me.Label4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label4.Size = New System.Drawing.Size(89, 22)
        Me.Label4.TabIndex = 5
        Me.Label4.Text = "results in"
        Me.Label4.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'frmUOM
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(8.0!, 16.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.SystemColors.Control
        Me.ClientSize = New System.Drawing.Size(550, 455)
        Me.Controls.Add(Me.Frame3)
        Me.Controls.Add(Me.Frame2)
        Me.Controls.Add(Me.Frame1)
        Me.Cursor = System.Windows.Forms.Cursors.Default
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.Location = New System.Drawing.Point(4, 28)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "frmUOM"
        Me.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Text = "Units of Measure Sample"
        Me.Frame3.ResumeLayout(False)
        Me.Frame2.ResumeLayout(False)
        Me.Frame1.ResumeLayout(False)
        Me.ResumeLayout(False)

    End Sub
#End Region 
End Class