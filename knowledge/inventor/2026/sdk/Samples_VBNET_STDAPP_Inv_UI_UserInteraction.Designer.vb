<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> Partial Class frmInteraction
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
	Public WithEvents chkXZPlaneTranslationSegment As System.Windows.Forms.CheckBox
	Public WithEvents chkYZPlaneTranslationSegment As System.Windows.Forms.CheckBox
	Public WithEvents chkZAxisTranslationSegment As System.Windows.Forms.CheckBox
	Public WithEvents chkZAxisRotationSegment As System.Windows.Forms.CheckBox
	Public WithEvents chkYAxisTranslationSegment As System.Windows.Forms.CheckBox
	Public WithEvents chkYAxisRotationSegment As System.Windows.Forms.CheckBox
	Public WithEvents chkXYPlaneTranslationSegment As System.Windows.Forms.CheckBox
	Public WithEvents chkXAxisTranslationSegment As System.Windows.Forms.CheckBox
	Public WithEvents chkXAxisRotationSegment As System.Windows.Forms.CheckBox
	Public WithEvents chkOriginSegment As System.Windows.Forms.CheckBox
	Public WithEvents fmDegreeOfFreedom As System.Windows.Forms.GroupBox
	Public WithEvents chkRepeat As System.Windows.Forms.CheckBox
	Public WithEvents chkMoveTriadOnlyEnabled As System.Windows.Forms.CheckBox
	Public WithEvents chkMoveTriadOnly As System.Windows.Forms.CheckBox
	Public WithEvents chkOnMoveTriadOnlyToggle As System.Windows.Forms.CheckBox
	Public WithEvents chkOnSegmentSelectionChange As System.Windows.Forms.CheckBox
	Public WithEvents chkOnEndSequence As System.Windows.Forms.CheckBox
	Public WithEvents chkOnStartSequence As System.Windows.Forms.CheckBox
	Public WithEvents chkEnableTriad As System.Windows.Forms.CheckBox
	Public WithEvents chkOnEndMove As System.Windows.Forms.CheckBox
	Public WithEvents chkOnMove As System.Windows.Forms.CheckBox
	Public WithEvents chkOnStartMove As System.Windows.Forms.CheckBox
	Public WithEvents chkOnTerminate As System.Windows.Forms.CheckBox
	Public WithEvents chkOnActivate As System.Windows.Forms.CheckBox
	Public WithEvents fmTriad As System.Windows.Forms.GroupBox
	Public WithEvents chkOnKeyDown As System.Windows.Forms.CheckBox
	Public WithEvents chkOnKeyPress As System.Windows.Forms.CheckBox
	Public WithEvents chkOnKeyUp As System.Windows.Forms.CheckBox
	Public WithEvents chkEnableKeyboard As System.Windows.Forms.CheckBox
	Public WithEvents fmKeyboard As System.Windows.Forms.GroupBox
	Public WithEvents txtStatusBar As System.Windows.Forms.TextBox
	Public WithEvents chkTriad As System.Windows.Forms.CheckBox
	Public WithEvents chkSelection As System.Windows.Forms.CheckBox
	Public WithEvents fmEventPriority As System.Windows.Forms.GroupBox
	Public WithEvents chkKeepFaces As System.Windows.Forms.CheckBox
	Public WithEvents chkDisableInteraction As System.Windows.Forms.CheckBox
    Public WithEvents cmdClear As System.Windows.Forms.Button
	Public WithEvents chkDatabaseUnits As System.Windows.Forms.CheckBox
	Public WithEvents txtResults As System.Windows.Forms.TextBox
	Public WithEvents cmdCancel As System.Windows.Forms.Button
	Public WithEvents chkOnMouseDoubleClick As System.Windows.Forms.CheckBox
	Public WithEvents chkOnMouseDown As System.Windows.Forms.CheckBox
	Public WithEvents chkOnMouseLeave As System.Windows.Forms.CheckBox
	Public WithEvents chkOnMouseMove As System.Windows.Forms.CheckBox
	Public WithEvents chkOnMouseUp As System.Windows.Forms.CheckBox
	Public WithEvents chkOnMouseClick As System.Windows.Forms.CheckBox
	Public WithEvents chkEnableMouse As System.Windows.Forms.CheckBox
	Public WithEvents chkEnableMouseMove As System.Windows.Forms.CheckBox
	Public WithEvents chkPointInference As System.Windows.Forms.CheckBox
	Public WithEvents fmMouse As System.Windows.Forms.GroupBox
    Public WithEvents lstFilters As System.Windows.Forms.ListBox
    Public WithEvents Frame1 As System.Windows.Forms.GroupBox
    Public WithEvents chkOnPreSelect As System.Windows.Forms.CheckBox
    Public WithEvents chkOnPreSelectMouseMove As System.Windows.Forms.CheckBox
    Public WithEvents chkOnSelect As System.Windows.Forms.CheckBox
    Public WithEvents chkOnUnselect As System.Windows.Forms.CheckBox
    Public WithEvents chkOnStopPreSelect As System.Windows.Forms.CheckBox
    Public WithEvents chkEnableSelection As System.Windows.Forms.CheckBox
    Public WithEvents chkDoHighlight As System.Windows.Forms.CheckBox
    Public WithEvents chkSingleSelect As System.Windows.Forms.CheckBox
    Public WithEvents chkSelectMouseMove As System.Windows.Forms.CheckBox
    Public WithEvents fmSelection As System.Windows.Forms.GroupBox
    Public WithEvents Label2 As System.Windows.Forms.Label
    Public WithEvents Label1 As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.fmTriad = New System.Windows.Forms.GroupBox()
        Me.fmDegreeOfFreedom = New System.Windows.Forms.GroupBox()
        Me.chkXZPlaneTranslationSegment = New System.Windows.Forms.CheckBox()
        Me.chkYZPlaneTranslationSegment = New System.Windows.Forms.CheckBox()
        Me.chkZAxisTranslationSegment = New System.Windows.Forms.CheckBox()
        Me.chkZAxisRotationSegment = New System.Windows.Forms.CheckBox()
        Me.chkYAxisTranslationSegment = New System.Windows.Forms.CheckBox()
        Me.chkYAxisRotationSegment = New System.Windows.Forms.CheckBox()
        Me.chkXYPlaneTranslationSegment = New System.Windows.Forms.CheckBox()
        Me.chkXAxisTranslationSegment = New System.Windows.Forms.CheckBox()
        Me.chkXAxisRotationSegment = New System.Windows.Forms.CheckBox()
        Me.chkOriginSegment = New System.Windows.Forms.CheckBox()
        Me.chkRepeat = New System.Windows.Forms.CheckBox()
        Me.chkMoveTriadOnlyEnabled = New System.Windows.Forms.CheckBox()
        Me.chkMoveTriadOnly = New System.Windows.Forms.CheckBox()
        Me.chkOnMoveTriadOnlyToggle = New System.Windows.Forms.CheckBox()
        Me.chkOnSegmentSelectionChange = New System.Windows.Forms.CheckBox()
        Me.chkOnEndSequence = New System.Windows.Forms.CheckBox()
        Me.chkOnStartSequence = New System.Windows.Forms.CheckBox()
        Me.chkEnableTriad = New System.Windows.Forms.CheckBox()
        Me.chkOnEndMove = New System.Windows.Forms.CheckBox()
        Me.chkOnMove = New System.Windows.Forms.CheckBox()
        Me.chkOnStartMove = New System.Windows.Forms.CheckBox()
        Me.chkOnTerminate = New System.Windows.Forms.CheckBox()
        Me.chkOnActivate = New System.Windows.Forms.CheckBox()
        Me.fmKeyboard = New System.Windows.Forms.GroupBox()
        Me.chkOnKeyDown = New System.Windows.Forms.CheckBox()
        Me.chkOnKeyPress = New System.Windows.Forms.CheckBox()
        Me.chkOnKeyUp = New System.Windows.Forms.CheckBox()
        Me.chkEnableKeyboard = New System.Windows.Forms.CheckBox()
        Me.txtStatusBar = New System.Windows.Forms.TextBox()
        Me.fmEventPriority = New System.Windows.Forms.GroupBox()
        Me.chkTriad = New System.Windows.Forms.CheckBox()
        Me.chkSelection = New System.Windows.Forms.CheckBox()
        Me.chkKeepFaces = New System.Windows.Forms.CheckBox()
        Me.chkDisableInteraction = New System.Windows.Forms.CheckBox()
        Me.cmdClear = New System.Windows.Forms.Button()
        Me.chkDatabaseUnits = New System.Windows.Forms.CheckBox()
        Me.txtResults = New System.Windows.Forms.TextBox()
        Me.cmdCancel = New System.Windows.Forms.Button()
        Me.fmMouse = New System.Windows.Forms.GroupBox()
        Me.chkOnMouseDoubleClick = New System.Windows.Forms.CheckBox()
        Me.chkOnMouseDown = New System.Windows.Forms.CheckBox()
        Me.chkOnMouseLeave = New System.Windows.Forms.CheckBox()
        Me.chkOnMouseMove = New System.Windows.Forms.CheckBox()
        Me.chkOnMouseUp = New System.Windows.Forms.CheckBox()
        Me.chkOnMouseClick = New System.Windows.Forms.CheckBox()
        Me.chkEnableMouse = New System.Windows.Forms.CheckBox()
        Me.chkEnableMouseMove = New System.Windows.Forms.CheckBox()
        Me.chkPointInference = New System.Windows.Forms.CheckBox()
        Me.fmSelection = New System.Windows.Forms.GroupBox()
        Me.btnReset = New System.Windows.Forms.Button()
        Me.Frame1 = New System.Windows.Forms.GroupBox()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.btnClearAll = New System.Windows.Forms.Button()
        Me.lstFilters = New System.Windows.Forms.ListBox()
        Me.chkOnPreSelect = New System.Windows.Forms.CheckBox()
        Me.chkOnPreSelectMouseMove = New System.Windows.Forms.CheckBox()
        Me.chkOnSelect = New System.Windows.Forms.CheckBox()
        Me.chkOnUnselect = New System.Windows.Forms.CheckBox()
        Me.chkOnStopPreSelect = New System.Windows.Forms.CheckBox()
        Me.chkEnableSelection = New System.Windows.Forms.CheckBox()
        Me.chkDoHighlight = New System.Windows.Forms.CheckBox()
        Me.chkSingleSelect = New System.Windows.Forms.CheckBox()
        Me.chkSelectMouseMove = New System.Windows.Forms.CheckBox()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.tabSettings = New System.Windows.Forms.TabControl()
        Me.tabSelectEvents = New System.Windows.Forms.TabPage()
        Me.tabMouseEvents = New System.Windows.Forms.TabPage()
        Me.tabKeyboardEvents = New System.Windows.Forms.TabPage()
        Me.tabTriadEvents = New System.Windows.Forms.TabPage()
        Me.btnStartStop = New System.Windows.Forms.Button()
        Me.fmTriad.SuspendLayout()
        Me.fmDegreeOfFreedom.SuspendLayout()
        Me.fmKeyboard.SuspendLayout()
        Me.fmEventPriority.SuspendLayout()
        Me.fmMouse.SuspendLayout()
        Me.fmSelection.SuspendLayout()
        Me.Frame1.SuspendLayout()
        Me.tabSettings.SuspendLayout()
        Me.tabSelectEvents.SuspendLayout()
        Me.tabMouseEvents.SuspendLayout()
        Me.tabKeyboardEvents.SuspendLayout()
        Me.tabTriadEvents.SuspendLayout()
        Me.SuspendLayout()
        '
        'fmTriad
        '
        Me.fmTriad.BackColor = System.Drawing.SystemColors.Control
        Me.fmTriad.Controls.Add(Me.fmDegreeOfFreedom)
        Me.fmTriad.Controls.Add(Me.chkRepeat)
        Me.fmTriad.Controls.Add(Me.chkMoveTriadOnlyEnabled)
        Me.fmTriad.Controls.Add(Me.chkMoveTriadOnly)
        Me.fmTriad.Controls.Add(Me.chkOnMoveTriadOnlyToggle)
        Me.fmTriad.Controls.Add(Me.chkOnSegmentSelectionChange)
        Me.fmTriad.Controls.Add(Me.chkOnEndSequence)
        Me.fmTriad.Controls.Add(Me.chkOnStartSequence)
        Me.fmTriad.Controls.Add(Me.chkEnableTriad)
        Me.fmTriad.Controls.Add(Me.chkOnEndMove)
        Me.fmTriad.Controls.Add(Me.chkOnMove)
        Me.fmTriad.Controls.Add(Me.chkOnStartMove)
        Me.fmTriad.Controls.Add(Me.chkOnTerminate)
        Me.fmTriad.Controls.Add(Me.chkOnActivate)
        Me.fmTriad.ForeColor = System.Drawing.SystemColors.ControlText
        Me.fmTriad.Location = New System.Drawing.Point(5, 5)
        Me.fmTriad.Margin = New System.Windows.Forms.Padding(2)
        Me.fmTriad.Name = "fmTriad"
        Me.fmTriad.Padding = New System.Windows.Forms.Padding(2)
        Me.fmTriad.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.fmTriad.Size = New System.Drawing.Size(330, 377)
        Me.fmTriad.TabIndex = 42
        Me.fmTriad.TabStop = False
        '
        'fmDegreeOfFreedom
        '
        Me.fmDegreeOfFreedom.BackColor = System.Drawing.SystemColors.Control
        Me.fmDegreeOfFreedom.Controls.Add(Me.chkXZPlaneTranslationSegment)
        Me.fmDegreeOfFreedom.Controls.Add(Me.chkYZPlaneTranslationSegment)
        Me.fmDegreeOfFreedom.Controls.Add(Me.chkZAxisTranslationSegment)
        Me.fmDegreeOfFreedom.Controls.Add(Me.chkZAxisRotationSegment)
        Me.fmDegreeOfFreedom.Controls.Add(Me.chkYAxisTranslationSegment)
        Me.fmDegreeOfFreedom.Controls.Add(Me.chkYAxisRotationSegment)
        Me.fmDegreeOfFreedom.Controls.Add(Me.chkXYPlaneTranslationSegment)
        Me.fmDegreeOfFreedom.Controls.Add(Me.chkXAxisTranslationSegment)
        Me.fmDegreeOfFreedom.Controls.Add(Me.chkXAxisRotationSegment)
        Me.fmDegreeOfFreedom.Controls.Add(Me.chkOriginSegment)
        Me.fmDegreeOfFreedom.ForeColor = System.Drawing.SystemColors.ControlText
        Me.fmDegreeOfFreedom.Location = New System.Drawing.Point(8, 235)
        Me.fmDegreeOfFreedom.Margin = New System.Windows.Forms.Padding(2)
        Me.fmDegreeOfFreedom.Name = "fmDegreeOfFreedom"
        Me.fmDegreeOfFreedom.Padding = New System.Windows.Forms.Padding(2)
        Me.fmDegreeOfFreedom.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.fmDegreeOfFreedom.Size = New System.Drawing.Size(314, 133)
        Me.fmDegreeOfFreedom.TabIndex = 56
        Me.fmDegreeOfFreedom.TabStop = False
        Me.fmDegreeOfFreedom.Text = "Degree of Freedom"
        '
        'chkXZPlaneTranslationSegment
        '
        Me.chkXZPlaneTranslationSegment.BackColor = System.Drawing.SystemColors.Control
        Me.chkXZPlaneTranslationSegment.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkXZPlaneTranslationSegment.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkXZPlaneTranslationSegment.Location = New System.Drawing.Point(164, 105)
        Me.chkXZPlaneTranslationSegment.Margin = New System.Windows.Forms.Padding(2)
        Me.chkXZPlaneTranslationSegment.Name = "chkXZPlaneTranslationSegment"
        Me.chkXZPlaneTranslationSegment.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkXZPlaneTranslationSegment.Size = New System.Drawing.Size(143, 18)
        Me.chkXZPlaneTranslationSegment.TabIndex = 66
        Me.chkXZPlaneTranslationSegment.Text = "XZ Plane Translation"
        Me.chkXZPlaneTranslationSegment.UseVisualStyleBackColor = False
        '
        'chkYZPlaneTranslationSegment
        '
        Me.chkYZPlaneTranslationSegment.BackColor = System.Drawing.SystemColors.Control
        Me.chkYZPlaneTranslationSegment.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkYZPlaneTranslationSegment.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkYZPlaneTranslationSegment.Location = New System.Drawing.Point(164, 83)
        Me.chkYZPlaneTranslationSegment.Margin = New System.Windows.Forms.Padding(2)
        Me.chkYZPlaneTranslationSegment.Name = "chkYZPlaneTranslationSegment"
        Me.chkYZPlaneTranslationSegment.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkYZPlaneTranslationSegment.Size = New System.Drawing.Size(144, 18)
        Me.chkYZPlaneTranslationSegment.TabIndex = 65
        Me.chkYZPlaneTranslationSegment.Text = "YZ Plane Translation "
        Me.chkYZPlaneTranslationSegment.UseVisualStyleBackColor = False
        '
        'chkZAxisTranslationSegment
        '
        Me.chkZAxisTranslationSegment.BackColor = System.Drawing.SystemColors.Control
        Me.chkZAxisTranslationSegment.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkZAxisTranslationSegment.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkZAxisTranslationSegment.Location = New System.Drawing.Point(164, 39)
        Me.chkZAxisTranslationSegment.Margin = New System.Windows.Forms.Padding(2)
        Me.chkZAxisTranslationSegment.Name = "chkZAxisTranslationSegment"
        Me.chkZAxisTranslationSegment.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkZAxisTranslationSegment.Size = New System.Drawing.Size(143, 18)
        Me.chkZAxisTranslationSegment.TabIndex = 64
        Me.chkZAxisTranslationSegment.Text = "Z Axis Translation "
        Me.chkZAxisTranslationSegment.UseVisualStyleBackColor = False
        '
        'chkZAxisRotationSegment
        '
        Me.chkZAxisRotationSegment.BackColor = System.Drawing.SystemColors.Control
        Me.chkZAxisRotationSegment.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkZAxisRotationSegment.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkZAxisRotationSegment.Location = New System.Drawing.Point(164, 17)
        Me.chkZAxisRotationSegment.Margin = New System.Windows.Forms.Padding(2)
        Me.chkZAxisRotationSegment.Name = "chkZAxisRotationSegment"
        Me.chkZAxisRotationSegment.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkZAxisRotationSegment.Size = New System.Drawing.Size(144, 18)
        Me.chkZAxisRotationSegment.TabIndex = 63
        Me.chkZAxisRotationSegment.Text = "Z Axis Rotation "
        Me.chkZAxisRotationSegment.UseVisualStyleBackColor = False
        '
        'chkYAxisTranslationSegment
        '
        Me.chkYAxisTranslationSegment.BackColor = System.Drawing.SystemColors.Control
        Me.chkYAxisTranslationSegment.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkYAxisTranslationSegment.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkYAxisTranslationSegment.Location = New System.Drawing.Point(8, 105)
        Me.chkYAxisTranslationSegment.Margin = New System.Windows.Forms.Padding(2)
        Me.chkYAxisTranslationSegment.Name = "chkYAxisTranslationSegment"
        Me.chkYAxisTranslationSegment.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkYAxisTranslationSegment.Size = New System.Drawing.Size(144, 18)
        Me.chkYAxisTranslationSegment.TabIndex = 62
        Me.chkYAxisTranslationSegment.Text = "Y Axis Translation"
        Me.chkYAxisTranslationSegment.UseVisualStyleBackColor = False
        '
        'chkYAxisRotationSegment
        '
        Me.chkYAxisRotationSegment.BackColor = System.Drawing.SystemColors.Control
        Me.chkYAxisRotationSegment.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkYAxisRotationSegment.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkYAxisRotationSegment.Location = New System.Drawing.Point(8, 83)
        Me.chkYAxisRotationSegment.Margin = New System.Windows.Forms.Padding(2)
        Me.chkYAxisRotationSegment.Name = "chkYAxisRotationSegment"
        Me.chkYAxisRotationSegment.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkYAxisRotationSegment.Size = New System.Drawing.Size(152, 18)
        Me.chkYAxisRotationSegment.TabIndex = 61
        Me.chkYAxisRotationSegment.Text = "Y Axis Rotation "
        Me.chkYAxisRotationSegment.UseVisualStyleBackColor = False
        '
        'chkXYPlaneTranslationSegment
        '
        Me.chkXYPlaneTranslationSegment.BackColor = System.Drawing.SystemColors.Control
        Me.chkXYPlaneTranslationSegment.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkXYPlaneTranslationSegment.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkXYPlaneTranslationSegment.Location = New System.Drawing.Point(164, 61)
        Me.chkXYPlaneTranslationSegment.Margin = New System.Windows.Forms.Padding(2)
        Me.chkXYPlaneTranslationSegment.Name = "chkXYPlaneTranslationSegment"
        Me.chkXYPlaneTranslationSegment.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkXYPlaneTranslationSegment.Size = New System.Drawing.Size(143, 18)
        Me.chkXYPlaneTranslationSegment.TabIndex = 60
        Me.chkXYPlaneTranslationSegment.Text = "XY Plane Translation "
        Me.chkXYPlaneTranslationSegment.UseVisualStyleBackColor = False
        '
        'chkXAxisTranslationSegment
        '
        Me.chkXAxisTranslationSegment.BackColor = System.Drawing.SystemColors.Control
        Me.chkXAxisTranslationSegment.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkXAxisTranslationSegment.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkXAxisTranslationSegment.Location = New System.Drawing.Point(8, 61)
        Me.chkXAxisTranslationSegment.Margin = New System.Windows.Forms.Padding(2)
        Me.chkXAxisTranslationSegment.Name = "chkXAxisTranslationSegment"
        Me.chkXAxisTranslationSegment.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkXAxisTranslationSegment.Size = New System.Drawing.Size(152, 18)
        Me.chkXAxisTranslationSegment.TabIndex = 59
        Me.chkXAxisTranslationSegment.Text = "XAxisTranslation"
        Me.chkXAxisTranslationSegment.UseVisualStyleBackColor = False
        '
        'chkXAxisRotationSegment
        '
        Me.chkXAxisRotationSegment.BackColor = System.Drawing.SystemColors.Control
        Me.chkXAxisRotationSegment.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkXAxisRotationSegment.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkXAxisRotationSegment.Location = New System.Drawing.Point(8, 39)
        Me.chkXAxisRotationSegment.Margin = New System.Windows.Forms.Padding(2)
        Me.chkXAxisRotationSegment.Name = "chkXAxisRotationSegment"
        Me.chkXAxisRotationSegment.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkXAxisRotationSegment.Size = New System.Drawing.Size(152, 18)
        Me.chkXAxisRotationSegment.TabIndex = 58
        Me.chkXAxisRotationSegment.Text = "X Axis Rotation"
        Me.chkXAxisRotationSegment.UseVisualStyleBackColor = False
        '
        'chkOriginSegment
        '
        Me.chkOriginSegment.BackColor = System.Drawing.SystemColors.Control
        Me.chkOriginSegment.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOriginSegment.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOriginSegment.Location = New System.Drawing.Point(8, 17)
        Me.chkOriginSegment.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOriginSegment.Name = "chkOriginSegment"
        Me.chkOriginSegment.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOriginSegment.Size = New System.Drawing.Size(152, 18)
        Me.chkOriginSegment.TabIndex = 57
        Me.chkOriginSegment.Text = "Origin"
        Me.chkOriginSegment.UseVisualStyleBackColor = False
        '
        'chkRepeat
        '
        Me.chkRepeat.BackColor = System.Drawing.SystemColors.Control
        Me.chkRepeat.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkRepeat.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkRepeat.Location = New System.Drawing.Point(182, 81)
        Me.chkRepeat.Margin = New System.Windows.Forms.Padding(2)
        Me.chkRepeat.Name = "chkRepeat"
        Me.chkRepeat.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkRepeat.Size = New System.Drawing.Size(114, 18)
        Me.chkRepeat.TabIndex = 55
        Me.chkRepeat.Text = "Repeat"
        Me.chkRepeat.UseVisualStyleBackColor = False
        '
        'chkMoveTriadOnlyEnabled
        '
        Me.chkMoveTriadOnlyEnabled.BackColor = System.Drawing.SystemColors.Control
        Me.chkMoveTriadOnlyEnabled.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkMoveTriadOnlyEnabled.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkMoveTriadOnlyEnabled.Location = New System.Drawing.Point(182, 37)
        Me.chkMoveTriadOnlyEnabled.Margin = New System.Windows.Forms.Padding(2)
        Me.chkMoveTriadOnlyEnabled.Name = "chkMoveTriadOnlyEnabled"
        Me.chkMoveTriadOnlyEnabled.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkMoveTriadOnlyEnabled.Size = New System.Drawing.Size(136, 18)
        Me.chkMoveTriadOnlyEnabled.TabIndex = 54
        Me.chkMoveTriadOnlyEnabled.Text = "Move Triad Only Enabled"
        Me.chkMoveTriadOnlyEnabled.UseVisualStyleBackColor = False
        '
        'chkMoveTriadOnly
        '
        Me.chkMoveTriadOnly.BackColor = System.Drawing.SystemColors.Control
        Me.chkMoveTriadOnly.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkMoveTriadOnly.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkMoveTriadOnly.Location = New System.Drawing.Point(182, 59)
        Me.chkMoveTriadOnly.Margin = New System.Windows.Forms.Padding(2)
        Me.chkMoveTriadOnly.Name = "chkMoveTriadOnly"
        Me.chkMoveTriadOnly.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkMoveTriadOnly.Size = New System.Drawing.Size(122, 18)
        Me.chkMoveTriadOnly.TabIndex = 53
        Me.chkMoveTriadOnly.Text = "Move Triad Only"
        Me.chkMoveTriadOnly.UseVisualStyleBackColor = False
        '
        'chkOnMoveTriadOnlyToggle
        '
        Me.chkOnMoveTriadOnlyToggle.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnMoveTriadOnlyToggle.Checked = True
        Me.chkOnMoveTriadOnlyToggle.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnMoveTriadOnlyToggle.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnMoveTriadOnlyToggle.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnMoveTriadOnlyToggle.Location = New System.Drawing.Point(23, 191)
        Me.chkOnMoveTriadOnlyToggle.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnMoveTriadOnlyToggle.Name = "chkOnMoveTriadOnlyToggle"
        Me.chkOnMoveTriadOnlyToggle.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnMoveTriadOnlyToggle.Size = New System.Drawing.Size(189, 18)
        Me.chkOnMoveTriadOnlyToggle.TabIndex = 52
        Me.chkOnMoveTriadOnlyToggle.Text = "Display OnMoveTriadOnlyToggle"
        Me.chkOnMoveTriadOnlyToggle.UseVisualStyleBackColor = False
        '
        'chkOnSegmentSelectionChange
        '
        Me.chkOnSegmentSelectionChange.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnSegmentSelectionChange.Checked = True
        Me.chkOnSegmentSelectionChange.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnSegmentSelectionChange.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnSegmentSelectionChange.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnSegmentSelectionChange.Location = New System.Drawing.Point(23, 213)
        Me.chkOnSegmentSelectionChange.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnSegmentSelectionChange.Name = "chkOnSegmentSelectionChange"
        Me.chkOnSegmentSelectionChange.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnSegmentSelectionChange.Size = New System.Drawing.Size(256, 18)
        Me.chkOnSegmentSelectionChange.TabIndex = 51
        Me.chkOnSegmentSelectionChange.Text = "Display OnSegmentSelectionChange"
        Me.chkOnSegmentSelectionChange.UseVisualStyleBackColor = False
        '
        'chkOnEndSequence
        '
        Me.chkOnEndSequence.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnEndSequence.Checked = True
        Me.chkOnEndSequence.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnEndSequence.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnEndSequence.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnEndSequence.Location = New System.Drawing.Point(23, 169)
        Me.chkOnEndSequence.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnEndSequence.Name = "chkOnEndSequence"
        Me.chkOnEndSequence.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnEndSequence.Size = New System.Drawing.Size(159, 18)
        Me.chkOnEndSequence.TabIndex = 50
        Me.chkOnEndSequence.Text = "Display OnEndSequence"
        Me.chkOnEndSequence.UseVisualStyleBackColor = False
        '
        'chkOnStartSequence
        '
        Me.chkOnStartSequence.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnStartSequence.Checked = True
        Me.chkOnStartSequence.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnStartSequence.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnStartSequence.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnStartSequence.Location = New System.Drawing.Point(22, 147)
        Me.chkOnStartSequence.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnStartSequence.Name = "chkOnStartSequence"
        Me.chkOnStartSequence.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnStartSequence.Size = New System.Drawing.Size(152, 18)
        Me.chkOnStartSequence.TabIndex = 49
        Me.chkOnStartSequence.Text = "Display OnStartSequence"
        Me.chkOnStartSequence.UseVisualStyleBackColor = False
        '
        'chkEnableTriad
        '
        Me.chkEnableTriad.BackColor = System.Drawing.SystemColors.Control
        Me.chkEnableTriad.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkEnableTriad.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkEnableTriad.Location = New System.Drawing.Point(8, 15)
        Me.chkEnableTriad.Margin = New System.Windows.Forms.Padding(2)
        Me.chkEnableTriad.Name = "chkEnableTriad"
        Me.chkEnableTriad.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkEnableTriad.Size = New System.Drawing.Size(103, 18)
        Me.chkEnableTriad.TabIndex = 48
        Me.chkEnableTriad.Text = "Enable Triad"
        Me.chkEnableTriad.UseVisualStyleBackColor = False
        '
        'chkOnEndMove
        '
        Me.chkOnEndMove.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnEndMove.Checked = True
        Me.chkOnEndMove.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnEndMove.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnEndMove.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnEndMove.Location = New System.Drawing.Point(22, 125)
        Me.chkOnEndMove.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnEndMove.Name = "chkOnEndMove"
        Me.chkOnEndMove.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnEndMove.Size = New System.Drawing.Size(182, 18)
        Me.chkOnEndMove.TabIndex = 47
        Me.chkOnEndMove.Text = "Display OnEndMove"
        Me.chkOnEndMove.UseVisualStyleBackColor = False
        '
        'chkOnMove
        '
        Me.chkOnMove.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnMove.Checked = True
        Me.chkOnMove.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnMove.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnMove.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnMove.Location = New System.Drawing.Point(22, 103)
        Me.chkOnMove.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnMove.Name = "chkOnMove"
        Me.chkOnMove.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnMove.Size = New System.Drawing.Size(122, 18)
        Me.chkOnMove.TabIndex = 46
        Me.chkOnMove.Text = "Display OnMove"
        Me.chkOnMove.UseVisualStyleBackColor = False
        '
        'chkOnStartMove
        '
        Me.chkOnStartMove.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnStartMove.Checked = True
        Me.chkOnStartMove.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnStartMove.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnStartMove.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnStartMove.Location = New System.Drawing.Point(22, 81)
        Me.chkOnStartMove.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnStartMove.Name = "chkOnStartMove"
        Me.chkOnStartMove.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnStartMove.Size = New System.Drawing.Size(182, 18)
        Me.chkOnStartMove.TabIndex = 45
        Me.chkOnStartMove.Text = "Display OnStartMove"
        Me.chkOnStartMove.UseVisualStyleBackColor = False
        '
        'chkOnTerminate
        '
        Me.chkOnTerminate.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnTerminate.Checked = True
        Me.chkOnTerminate.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnTerminate.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnTerminate.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnTerminate.Location = New System.Drawing.Point(22, 59)
        Me.chkOnTerminate.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnTerminate.Name = "chkOnTerminate"
        Me.chkOnTerminate.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnTerminate.Size = New System.Drawing.Size(166, 18)
        Me.chkOnTerminate.TabIndex = 44
        Me.chkOnTerminate.Text = "Display OnTerminate"
        Me.chkOnTerminate.UseVisualStyleBackColor = False
        '
        'chkOnActivate
        '
        Me.chkOnActivate.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnActivate.Checked = True
        Me.chkOnActivate.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnActivate.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnActivate.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnActivate.Location = New System.Drawing.Point(22, 37)
        Me.chkOnActivate.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnActivate.Name = "chkOnActivate"
        Me.chkOnActivate.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnActivate.Size = New System.Drawing.Size(114, 18)
        Me.chkOnActivate.TabIndex = 43
        Me.chkOnActivate.Text = "Display OnActivate"
        Me.chkOnActivate.UseVisualStyleBackColor = False
        '
        'fmKeyboard
        '
        Me.fmKeyboard.BackColor = System.Drawing.SystemColors.Control
        Me.fmKeyboard.Controls.Add(Me.chkOnKeyDown)
        Me.fmKeyboard.Controls.Add(Me.chkOnKeyPress)
        Me.fmKeyboard.Controls.Add(Me.chkOnKeyUp)
        Me.fmKeyboard.Controls.Add(Me.chkEnableKeyboard)
        Me.fmKeyboard.ForeColor = System.Drawing.SystemColors.ControlText
        Me.fmKeyboard.Location = New System.Drawing.Point(5, 5)
        Me.fmKeyboard.Margin = New System.Windows.Forms.Padding(2)
        Me.fmKeyboard.Name = "fmKeyboard"
        Me.fmKeyboard.Padding = New System.Windows.Forms.Padding(2)
        Me.fmKeyboard.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.fmKeyboard.Size = New System.Drawing.Size(328, 110)
        Me.fmKeyboard.TabIndex = 28
        Me.fmKeyboard.TabStop = False
        '
        'chkOnKeyDown
        '
        Me.chkOnKeyDown.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnKeyDown.Checked = True
        Me.chkOnKeyDown.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnKeyDown.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnKeyDown.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnKeyDown.Location = New System.Drawing.Point(22, 37)
        Me.chkOnKeyDown.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnKeyDown.Name = "chkOnKeyDown"
        Me.chkOnKeyDown.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnKeyDown.Size = New System.Drawing.Size(154, 18)
        Me.chkOnKeyDown.TabIndex = 32
        Me.chkOnKeyDown.Text = "Display OnKeyDown"
        Me.chkOnKeyDown.UseVisualStyleBackColor = False
        '
        'chkOnKeyPress
        '
        Me.chkOnKeyPress.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnKeyPress.Checked = True
        Me.chkOnKeyPress.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnKeyPress.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnKeyPress.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnKeyPress.Location = New System.Drawing.Point(22, 59)
        Me.chkOnKeyPress.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnKeyPress.Name = "chkOnKeyPress"
        Me.chkOnKeyPress.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnKeyPress.Size = New System.Drawing.Size(154, 18)
        Me.chkOnKeyPress.TabIndex = 31
        Me.chkOnKeyPress.Text = "Display OnKeyPress"
        Me.chkOnKeyPress.UseVisualStyleBackColor = False
        '
        'chkOnKeyUp
        '
        Me.chkOnKeyUp.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnKeyUp.Checked = True
        Me.chkOnKeyUp.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnKeyUp.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnKeyUp.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnKeyUp.Location = New System.Drawing.Point(22, 81)
        Me.chkOnKeyUp.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnKeyUp.Name = "chkOnKeyUp"
        Me.chkOnKeyUp.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnKeyUp.Size = New System.Drawing.Size(133, 18)
        Me.chkOnKeyUp.TabIndex = 30
        Me.chkOnKeyUp.Text = "Display OnKeyUp"
        Me.chkOnKeyUp.UseVisualStyleBackColor = False
        '
        'chkEnableKeyboard
        '
        Me.chkEnableKeyboard.BackColor = System.Drawing.SystemColors.Control
        Me.chkEnableKeyboard.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkEnableKeyboard.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkEnableKeyboard.Location = New System.Drawing.Point(8, 16)
        Me.chkEnableKeyboard.Margin = New System.Windows.Forms.Padding(2)
        Me.chkEnableKeyboard.Name = "chkEnableKeyboard"
        Me.chkEnableKeyboard.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkEnableKeyboard.Size = New System.Drawing.Size(147, 18)
        Me.chkEnableKeyboard.TabIndex = 29
        Me.chkEnableKeyboard.Text = "Enable Keyboard"
        Me.chkEnableKeyboard.UseVisualStyleBackColor = False
        '
        'txtStatusBar
        '
        Me.txtStatusBar.AcceptsReturn = True
        Me.txtStatusBar.BackColor = System.Drawing.SystemColors.Window
        Me.txtStatusBar.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtStatusBar.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtStatusBar.Location = New System.Drawing.Point(94, 65)
        Me.txtStatusBar.Margin = New System.Windows.Forms.Padding(2)
        Me.txtStatusBar.MaxLength = 0
        Me.txtStatusBar.Name = "txtStatusBar"
        Me.txtStatusBar.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtStatusBar.Size = New System.Drawing.Size(253, 20)
        Me.txtStatusBar.TabIndex = 35
        Me.txtStatusBar.Text = "Sample Text"
        '
        'fmEventPriority
        '
        Me.fmEventPriority.BackColor = System.Drawing.SystemColors.Control
        Me.fmEventPriority.Controls.Add(Me.chkTriad)
        Me.fmEventPriority.Controls.Add(Me.chkSelection)
        Me.fmEventPriority.ForeColor = System.Drawing.SystemColors.ControlText
        Me.fmEventPriority.Location = New System.Drawing.Point(141, 7)
        Me.fmEventPriority.Margin = New System.Windows.Forms.Padding(2)
        Me.fmEventPriority.Name = "fmEventPriority"
        Me.fmEventPriority.Padding = New System.Windows.Forms.Padding(2)
        Me.fmEventPriority.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.fmEventPriority.Size = New System.Drawing.Size(106, 56)
        Me.fmEventPriority.TabIndex = 39
        Me.fmEventPriority.TabStop = False
        Me.fmEventPriority.Text = "Event Priority"
        '
        'chkTriad
        '
        Me.chkTriad.BackColor = System.Drawing.SystemColors.Control
        Me.chkTriad.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkTriad.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkTriad.Location = New System.Drawing.Point(15, 35)
        Me.chkTriad.Margin = New System.Windows.Forms.Padding(2)
        Me.chkTriad.Name = "chkTriad"
        Me.chkTriad.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkTriad.Size = New System.Drawing.Size(62, 18)
        Me.chkTriad.TabIndex = 41
        Me.chkTriad.Text = "Triad"
        Me.chkTriad.UseVisualStyleBackColor = False
        '
        'chkSelection
        '
        Me.chkSelection.BackColor = System.Drawing.SystemColors.Control
        Me.chkSelection.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkSelection.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkSelection.Location = New System.Drawing.Point(15, 16)
        Me.chkSelection.Margin = New System.Windows.Forms.Padding(2)
        Me.chkSelection.Name = "chkSelection"
        Me.chkSelection.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkSelection.Size = New System.Drawing.Size(87, 18)
        Me.chkSelection.TabIndex = 40
        Me.chkSelection.Text = "Selection"
        Me.chkSelection.UseVisualStyleBackColor = False
        '
        'chkKeepFaces
        '
        Me.chkKeepFaces.BackColor = System.Drawing.SystemColors.Control
        Me.chkKeepFaces.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkKeepFaces.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkKeepFaces.Location = New System.Drawing.Point(12, 35)
        Me.chkKeepFaces.Margin = New System.Windows.Forms.Padding(2)
        Me.chkKeepFaces.Name = "chkKeepFaces"
        Me.chkKeepFaces.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkKeepFaces.Size = New System.Drawing.Size(98, 18)
        Me.chkKeepFaces.TabIndex = 36
        Me.chkKeepFaces.Text = "Keep Selected Faces"
        Me.chkKeepFaces.UseVisualStyleBackColor = False
        '
        'chkDisableInteraction
        '
        Me.chkDisableInteraction.BackColor = System.Drawing.SystemColors.Control
        Me.chkDisableInteraction.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkDisableInteraction.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkDisableInteraction.Location = New System.Drawing.Point(264, 7)
        Me.chkDisableInteraction.Margin = New System.Windows.Forms.Padding(2)
        Me.chkDisableInteraction.Name = "chkDisableInteraction"
        Me.chkDisableInteraction.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkDisableInteraction.Size = New System.Drawing.Size(83, 42)
        Me.chkDisableInteraction.TabIndex = 34
        Me.chkDisableInteraction.Text = "Interaction Disabled"
        Me.chkDisableInteraction.UseVisualStyleBackColor = False
        '
        'cmdClear
        '
        Me.cmdClear.BackColor = System.Drawing.SystemColors.Control
        Me.cmdClear.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdClear.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdClear.Location = New System.Drawing.Point(274, 508)
        Me.cmdClear.Margin = New System.Windows.Forms.Padding(2)
        Me.cmdClear.Name = "cmdClear"
        Me.cmdClear.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdClear.Size = New System.Drawing.Size(80, 22)
        Me.cmdClear.TabIndex = 3
        Me.cmdClear.Text = "Clear Results"
        Me.cmdClear.UseVisualStyleBackColor = False
        '
        'chkDatabaseUnits
        '
        Me.chkDatabaseUnits.BackColor = System.Drawing.SystemColors.Control
        Me.chkDatabaseUnits.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkDatabaseUnits.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkDatabaseUnits.Location = New System.Drawing.Point(8, 713)
        Me.chkDatabaseUnits.Margin = New System.Windows.Forms.Padding(2)
        Me.chkDatabaseUnits.Name = "chkDatabaseUnits"
        Me.chkDatabaseUnits.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkDatabaseUnits.Size = New System.Drawing.Size(172, 18)
        Me.chkDatabaseUnits.TabIndex = 2
        Me.chkDatabaseUnits.Text = "Display using document units."
        Me.chkDatabaseUnits.UseVisualStyleBackColor = False
        '
        'txtResults
        '
        Me.txtResults.AcceptsReturn = True
        Me.txtResults.BackColor = System.Drawing.SystemColors.Window
        Me.txtResults.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtResults.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtResults.Location = New System.Drawing.Point(8, 534)
        Me.txtResults.Margin = New System.Windows.Forms.Padding(2)
        Me.txtResults.MaxLength = 0
        Me.txtResults.Multiline = True
        Me.txtResults.Name = "txtResults"
        Me.txtResults.ReadOnly = True
        Me.txtResults.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtResults.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.txtResults.Size = New System.Drawing.Size(346, 171)
        Me.txtResults.TabIndex = 1
        '
        'cmdCancel
        '
        Me.cmdCancel.BackColor = System.Drawing.SystemColors.Control
        Me.cmdCancel.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdCancel.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdCancel.Location = New System.Drawing.Point(292, 709)
        Me.cmdCancel.Margin = New System.Windows.Forms.Padding(2)
        Me.cmdCancel.Name = "cmdCancel"
        Me.cmdCancel.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdCancel.Size = New System.Drawing.Size(62, 22)
        Me.cmdCancel.TabIndex = 0
        Me.cmdCancel.Text = "Cancel"
        Me.cmdCancel.UseVisualStyleBackColor = False
        '
        'fmMouse
        '
        Me.fmMouse.BackColor = System.Drawing.SystemColors.Control
        Me.fmMouse.Controls.Add(Me.chkOnMouseDoubleClick)
        Me.fmMouse.Controls.Add(Me.chkOnMouseDown)
        Me.fmMouse.Controls.Add(Me.chkOnMouseLeave)
        Me.fmMouse.Controls.Add(Me.chkOnMouseMove)
        Me.fmMouse.Controls.Add(Me.chkOnMouseUp)
        Me.fmMouse.Controls.Add(Me.chkOnMouseClick)
        Me.fmMouse.Controls.Add(Me.chkEnableMouse)
        Me.fmMouse.Controls.Add(Me.chkEnableMouseMove)
        Me.fmMouse.Controls.Add(Me.chkPointInference)
        Me.fmMouse.ForeColor = System.Drawing.SystemColors.ControlText
        Me.fmMouse.Location = New System.Drawing.Point(5, 5)
        Me.fmMouse.Margin = New System.Windows.Forms.Padding(2)
        Me.fmMouse.Name = "fmMouse"
        Me.fmMouse.Padding = New System.Windows.Forms.Padding(2)
        Me.fmMouse.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.fmMouse.Size = New System.Drawing.Size(328, 173)
        Me.fmMouse.TabIndex = 4
        Me.fmMouse.TabStop = False
        '
        'chkOnMouseDoubleClick
        '
        Me.chkOnMouseDoubleClick.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnMouseDoubleClick.Checked = True
        Me.chkOnMouseDoubleClick.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnMouseDoubleClick.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnMouseDoubleClick.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnMouseDoubleClick.Location = New System.Drawing.Point(22, 76)
        Me.chkOnMouseDoubleClick.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnMouseDoubleClick.Name = "chkOnMouseDoubleClick"
        Me.chkOnMouseDoubleClick.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnMouseDoubleClick.Size = New System.Drawing.Size(204, 18)
        Me.chkOnMouseDoubleClick.TabIndex = 13
        Me.chkOnMouseDoubleClick.Text = "Display OnMouseDoubleClick"
        Me.chkOnMouseDoubleClick.UseVisualStyleBackColor = False
        '
        'chkOnMouseDown
        '
        Me.chkOnMouseDown.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnMouseDown.Checked = True
        Me.chkOnMouseDown.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnMouseDown.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnMouseDown.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnMouseDown.Location = New System.Drawing.Point(22, 54)
        Me.chkOnMouseDown.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnMouseDown.Name = "chkOnMouseDown"
        Me.chkOnMouseDown.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnMouseDown.Size = New System.Drawing.Size(162, 18)
        Me.chkOnMouseDown.TabIndex = 12
        Me.chkOnMouseDown.Text = "Display OnMouseDown"
        Me.chkOnMouseDown.UseVisualStyleBackColor = False
        '
        'chkOnMouseLeave
        '
        Me.chkOnMouseLeave.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnMouseLeave.Checked = True
        Me.chkOnMouseLeave.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnMouseLeave.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnMouseLeave.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnMouseLeave.Location = New System.Drawing.Point(22, 32)
        Me.chkOnMouseLeave.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnMouseLeave.Name = "chkOnMouseLeave"
        Me.chkOnMouseLeave.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnMouseLeave.Size = New System.Drawing.Size(162, 18)
        Me.chkOnMouseLeave.TabIndex = 11
        Me.chkOnMouseLeave.Text = "Display OnMouseLeave"
        Me.chkOnMouseLeave.UseVisualStyleBackColor = False
        '
        'chkOnMouseMove
        '
        Me.chkOnMouseMove.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnMouseMove.Checked = True
        Me.chkOnMouseMove.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnMouseMove.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnMouseMove.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnMouseMove.Location = New System.Drawing.Point(22, 98)
        Me.chkOnMouseMove.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnMouseMove.Name = "chkOnMouseMove"
        Me.chkOnMouseMove.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnMouseMove.Size = New System.Drawing.Size(170, 18)
        Me.chkOnMouseMove.TabIndex = 10
        Me.chkOnMouseMove.Text = "Display OnMouseMove"
        Me.chkOnMouseMove.UseVisualStyleBackColor = False
        '
        'chkOnMouseUp
        '
        Me.chkOnMouseUp.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnMouseUp.Checked = True
        Me.chkOnMouseUp.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnMouseUp.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnMouseUp.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnMouseUp.Location = New System.Drawing.Point(22, 120)
        Me.chkOnMouseUp.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnMouseUp.Name = "chkOnMouseUp"
        Me.chkOnMouseUp.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnMouseUp.Size = New System.Drawing.Size(152, 18)
        Me.chkOnMouseUp.TabIndex = 9
        Me.chkOnMouseUp.Text = "Display Mouse Up"
        Me.chkOnMouseUp.UseVisualStyleBackColor = False
        '
        'chkOnMouseClick
        '
        Me.chkOnMouseClick.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnMouseClick.Checked = True
        Me.chkOnMouseClick.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnMouseClick.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnMouseClick.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnMouseClick.Location = New System.Drawing.Point(22, 142)
        Me.chkOnMouseClick.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnMouseClick.Name = "chkOnMouseClick"
        Me.chkOnMouseClick.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnMouseClick.Size = New System.Drawing.Size(168, 18)
        Me.chkOnMouseClick.TabIndex = 8
        Me.chkOnMouseClick.Text = "Display OnMouseClick"
        Me.chkOnMouseClick.UseVisualStyleBackColor = False
        '
        'chkEnableMouse
        '
        Me.chkEnableMouse.BackColor = System.Drawing.SystemColors.Control
        Me.chkEnableMouse.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkEnableMouse.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkEnableMouse.Location = New System.Drawing.Point(8, 12)
        Me.chkEnableMouse.Margin = New System.Windows.Forms.Padding(2)
        Me.chkEnableMouse.Name = "chkEnableMouse"
        Me.chkEnableMouse.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkEnableMouse.Size = New System.Drawing.Size(132, 22)
        Me.chkEnableMouse.TabIndex = 7
        Me.chkEnableMouse.Text = "Enable Mouse"
        Me.chkEnableMouse.UseVisualStyleBackColor = False
        '
        'chkEnableMouseMove
        '
        Me.chkEnableMouseMove.BackColor = System.Drawing.SystemColors.Control
        Me.chkEnableMouseMove.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkEnableMouseMove.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkEnableMouseMove.Location = New System.Drawing.Point(188, 54)
        Me.chkEnableMouseMove.Margin = New System.Windows.Forms.Padding(2)
        Me.chkEnableMouseMove.Name = "chkEnableMouseMove"
        Me.chkEnableMouseMove.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkEnableMouseMove.Size = New System.Drawing.Size(129, 18)
        Me.chkEnableMouseMove.TabIndex = 6
        Me.chkEnableMouseMove.Text = "Enable Mouse Move"
        Me.chkEnableMouseMove.UseVisualStyleBackColor = False
        '
        'chkPointInference
        '
        Me.chkPointInference.BackColor = System.Drawing.SystemColors.Control
        Me.chkPointInference.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkPointInference.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkPointInference.Location = New System.Drawing.Point(188, 32)
        Me.chkPointInference.Margin = New System.Windows.Forms.Padding(2)
        Me.chkPointInference.Name = "chkPointInference"
        Me.chkPointInference.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkPointInference.Size = New System.Drawing.Size(109, 18)
        Me.chkPointInference.TabIndex = 5
        Me.chkPointInference.Text = "Point Inference Enabled"
        Me.chkPointInference.UseVisualStyleBackColor = False
        '
        'fmSelection
        '
        Me.fmSelection.BackColor = System.Drawing.SystemColors.Control
        Me.fmSelection.Controls.Add(Me.btnReset)
        Me.fmSelection.Controls.Add(Me.Frame1)
        Me.fmSelection.Controls.Add(Me.chkOnPreSelect)
        Me.fmSelection.Controls.Add(Me.chkOnPreSelectMouseMove)
        Me.fmSelection.Controls.Add(Me.chkOnSelect)
        Me.fmSelection.Controls.Add(Me.chkOnUnselect)
        Me.fmSelection.Controls.Add(Me.chkOnStopPreSelect)
        Me.fmSelection.Controls.Add(Me.chkEnableSelection)
        Me.fmSelection.Controls.Add(Me.chkDoHighlight)
        Me.fmSelection.Controls.Add(Me.chkSingleSelect)
        Me.fmSelection.Controls.Add(Me.chkSelectMouseMove)
        Me.fmSelection.ForeColor = System.Drawing.SystemColors.ControlText
        Me.fmSelection.Location = New System.Drawing.Point(5, 5)
        Me.fmSelection.Margin = New System.Windows.Forms.Padding(2)
        Me.fmSelection.Name = "fmSelection"
        Me.fmSelection.Padding = New System.Windows.Forms.Padding(2)
        Me.fmSelection.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.fmSelection.Size = New System.Drawing.Size(330, 377)
        Me.fmSelection.TabIndex = 14
        Me.fmSelection.TabStop = False
        Me.fmSelection.Visible = False
        '
        'btnReset
        '
        Me.btnReset.Location = New System.Drawing.Point(234, 232)
        Me.btnReset.Name = "btnReset"
        Me.btnReset.Size = New System.Drawing.Size(75, 23)
        Me.btnReset.TabIndex = 26
        Me.btnReset.Text = "Reset"
        Me.btnReset.UseVisualStyleBackColor = True
        '
        'Frame1
        '
        Me.Frame1.BackColor = System.Drawing.SystemColors.Control
        Me.Frame1.Controls.Add(Me.Label3)
        Me.Frame1.Controls.Add(Me.btnClearAll)
        Me.Frame1.Controls.Add(Me.lstFilters)
        Me.Frame1.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Frame1.Location = New System.Drawing.Point(4, 10)
        Me.Frame1.Margin = New System.Windows.Forms.Padding(2)
        Me.Frame1.Name = "Frame1"
        Me.Frame1.Padding = New System.Windows.Forms.Padding(2)
        Me.Frame1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Frame1.Size = New System.Drawing.Size(317, 208)
        Me.Frame1.TabIndex = 25
        Me.Frame1.TabStop = False
        Me.Frame1.Text = "Filter"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(8, 180)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(222, 13)
        Me.Label3.TabIndex = 28
        Me.Label3.Text = "* Use control and shift to select multiple filters."
        '
        'btnClearAll
        '
        Me.btnClearAll.Location = New System.Drawing.Point(257, 180)
        Me.btnClearAll.Name = "btnClearAll"
        Me.btnClearAll.Size = New System.Drawing.Size(55, 23)
        Me.btnClearAll.TabIndex = 27
        Me.btnClearAll.Text = "Clear All"
        Me.btnClearAll.UseVisualStyleBackColor = True
        '
        'lstFilters
        '
        Me.lstFilters.BackColor = System.Drawing.SystemColors.Window
        Me.lstFilters.Cursor = System.Windows.Forms.Cursors.Default
        Me.lstFilters.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lstFilters.Location = New System.Drawing.Point(8, 16)
        Me.lstFilters.Margin = New System.Windows.Forms.Padding(2)
        Me.lstFilters.Name = "lstFilters"
        Me.lstFilters.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lstFilters.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended
        Me.lstFilters.Size = New System.Drawing.Size(301, 160)
        Me.lstFilters.TabIndex = 27
        '
        'chkOnPreSelect
        '
        Me.chkOnPreSelect.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnPreSelect.Checked = True
        Me.chkOnPreSelect.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnPreSelect.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnPreSelect.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnPreSelect.Location = New System.Drawing.Point(22, 267)
        Me.chkOnPreSelect.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnPreSelect.Name = "chkOnPreSelect"
        Me.chkOnPreSelect.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnPreSelect.Size = New System.Drawing.Size(150, 18)
        Me.chkOnPreSelect.TabIndex = 24
        Me.chkOnPreSelect.Text = "Display OnPreSelect"
        Me.chkOnPreSelect.UseVisualStyleBackColor = False
        '
        'chkOnPreSelectMouseMove
        '
        Me.chkOnPreSelectMouseMove.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnPreSelectMouseMove.Checked = True
        Me.chkOnPreSelectMouseMove.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnPreSelectMouseMove.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnPreSelectMouseMove.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnPreSelectMouseMove.Location = New System.Drawing.Point(22, 311)
        Me.chkOnPreSelectMouseMove.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnPreSelectMouseMove.Name = "chkOnPreSelectMouseMove"
        Me.chkOnPreSelectMouseMove.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnPreSelectMouseMove.Size = New System.Drawing.Size(212, 18)
        Me.chkOnPreSelectMouseMove.TabIndex = 23
        Me.chkOnPreSelectMouseMove.Text = "Display OnPreSelectMouseMove"
        Me.chkOnPreSelectMouseMove.UseVisualStyleBackColor = False
        '
        'chkOnSelect
        '
        Me.chkOnSelect.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnSelect.Checked = True
        Me.chkOnSelect.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnSelect.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnSelect.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnSelect.Location = New System.Drawing.Point(22, 289)
        Me.chkOnSelect.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnSelect.Name = "chkOnSelect"
        Me.chkOnSelect.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnSelect.Size = New System.Drawing.Size(166, 18)
        Me.chkOnSelect.TabIndex = 22
        Me.chkOnSelect.Text = "Display OnSelect"
        Me.chkOnSelect.UseVisualStyleBackColor = False
        '
        'chkOnUnselect
        '
        Me.chkOnUnselect.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnUnselect.Checked = True
        Me.chkOnUnselect.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnUnselect.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnUnselect.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnUnselect.Location = New System.Drawing.Point(22, 333)
        Me.chkOnUnselect.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnUnselect.Name = "chkOnUnselect"
        Me.chkOnUnselect.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnUnselect.Size = New System.Drawing.Size(150, 18)
        Me.chkOnUnselect.TabIndex = 21
        Me.chkOnUnselect.Text = "Display OnUnselect"
        Me.chkOnUnselect.UseVisualStyleBackColor = False
        '
        'chkOnStopPreSelect
        '
        Me.chkOnStopPreSelect.BackColor = System.Drawing.SystemColors.Control
        Me.chkOnStopPreSelect.Checked = True
        Me.chkOnStopPreSelect.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkOnStopPreSelect.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkOnStopPreSelect.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkOnStopPreSelect.Location = New System.Drawing.Point(22, 355)
        Me.chkOnStopPreSelect.Margin = New System.Windows.Forms.Padding(2)
        Me.chkOnStopPreSelect.Name = "chkOnStopPreSelect"
        Me.chkOnStopPreSelect.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkOnStopPreSelect.Size = New System.Drawing.Size(182, 18)
        Me.chkOnStopPreSelect.TabIndex = 20
        Me.chkOnStopPreSelect.Text = "Display OnStopPreSelect"
        Me.chkOnStopPreSelect.UseVisualStyleBackColor = False
        '
        'chkEnableSelection
        '
        Me.chkEnableSelection.BackColor = System.Drawing.SystemColors.Control
        Me.chkEnableSelection.Checked = True
        Me.chkEnableSelection.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkEnableSelection.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkEnableSelection.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkEnableSelection.Location = New System.Drawing.Point(8, 222)
        Me.chkEnableSelection.Margin = New System.Windows.Forms.Padding(2)
        Me.chkEnableSelection.Name = "chkEnableSelection"
        Me.chkEnableSelection.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkEnableSelection.Size = New System.Drawing.Size(136, 18)
        Me.chkEnableSelection.TabIndex = 19
        Me.chkEnableSelection.Text = "Enable Selection"
        Me.chkEnableSelection.UseVisualStyleBackColor = False
        '
        'chkDoHighlight
        '
        Me.chkDoHighlight.BackColor = System.Drawing.SystemColors.Control
        Me.chkDoHighlight.Checked = True
        Me.chkDoHighlight.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkDoHighlight.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkDoHighlight.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkDoHighlight.Location = New System.Drawing.Point(195, 289)
        Me.chkDoHighlight.Margin = New System.Windows.Forms.Padding(2)
        Me.chkDoHighlight.Name = "chkDoHighlight"
        Me.chkDoHighlight.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkDoHighlight.Size = New System.Drawing.Size(114, 18)
        Me.chkDoHighlight.TabIndex = 18
        Me.chkDoHighlight.Text = "Do Highlight"
        Me.chkDoHighlight.UseVisualStyleBackColor = False
        '
        'chkSingleSelect
        '
        Me.chkSingleSelect.BackColor = System.Drawing.SystemColors.Control
        Me.chkSingleSelect.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkSingleSelect.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkSingleSelect.Location = New System.Drawing.Point(15, 243)
        Me.chkSingleSelect.Margin = New System.Windows.Forms.Padding(2)
        Me.chkSingleSelect.Name = "chkSingleSelect"
        Me.chkSingleSelect.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkSingleSelect.Size = New System.Drawing.Size(148, 18)
        Me.chkSingleSelect.TabIndex = 17
        Me.chkSingleSelect.Text = "Single Select Mode"
        Me.chkSingleSelect.UseVisualStyleBackColor = False
        '
        'chkSelectMouseMove
        '
        Me.chkSelectMouseMove.BackColor = System.Drawing.SystemColors.Control
        Me.chkSelectMouseMove.Checked = True
        Me.chkSelectMouseMove.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chkSelectMouseMove.Cursor = System.Windows.Forms.Cursors.Default
        Me.chkSelectMouseMove.ForeColor = System.Drawing.SystemColors.ControlText
        Me.chkSelectMouseMove.Location = New System.Drawing.Point(195, 267)
        Me.chkSelectMouseMove.Margin = New System.Windows.Forms.Padding(2)
        Me.chkSelectMouseMove.Name = "chkSelectMouseMove"
        Me.chkSelectMouseMove.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.chkSelectMouseMove.Size = New System.Drawing.Size(126, 18)
        Me.chkSelectMouseMove.TabIndex = 16
        Me.chkSelectMouseMove.Text = "Enable Mouse Move"
        Me.chkSelectMouseMove.UseVisualStyleBackColor = False
        '
        'Label2
        '
        Me.Label2.BackColor = System.Drawing.SystemColors.Control
        Me.Label2.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label2.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label2.Location = New System.Drawing.Point(9, 68)
        Me.Label2.Margin = New System.Windows.Forms.Padding(2, 0, 2, 0)
        Me.Label2.Name = "Label2"
        Me.Label2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label2.Size = New System.Drawing.Size(91, 20)
        Me.Label2.TabIndex = 67
        Me.Label2.Text = "Status Bar Text:"
        '
        'Label1
        '
        Me.Label1.BackColor = System.Drawing.SystemColors.Control
        Me.Label1.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label1.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label1.Location = New System.Drawing.Point(5, 513)
        Me.Label1.Margin = New System.Windows.Forms.Padding(2, 0, 2, 0)
        Me.Label1.Name = "Label1"
        Me.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label1.Size = New System.Drawing.Size(99, 14)
        Me.Label1.TabIndex = 38
        Me.Label1.Text = "Results:"
        '
        'tabSettings
        '
        Me.tabSettings.Controls.Add(Me.tabSelectEvents)
        Me.tabSettings.Controls.Add(Me.tabMouseEvents)
        Me.tabSettings.Controls.Add(Me.tabKeyboardEvents)
        Me.tabSettings.Controls.Add(Me.tabTriadEvents)
        Me.tabSettings.Location = New System.Drawing.Point(8, 90)
        Me.tabSettings.Name = "tabSettings"
        Me.tabSettings.SelectedIndex = 0
        Me.tabSettings.Size = New System.Drawing.Size(346, 413)
        Me.tabSettings.TabIndex = 68
        '
        'tabSelectEvents
        '
        Me.tabSelectEvents.Controls.Add(Me.fmSelection)
        Me.tabSelectEvents.Location = New System.Drawing.Point(4, 22)
        Me.tabSelectEvents.Name = "tabSelectEvents"
        Me.tabSelectEvents.Padding = New System.Windows.Forms.Padding(3)
        Me.tabSelectEvents.Size = New System.Drawing.Size(338, 387)
        Me.tabSelectEvents.TabIndex = 0
        Me.tabSelectEvents.Text = "Selection Events"
        Me.tabSelectEvents.UseVisualStyleBackColor = True
        '
        'tabMouseEvents
        '
        Me.tabMouseEvents.Controls.Add(Me.fmMouse)
        Me.tabMouseEvents.Location = New System.Drawing.Point(4, 22)
        Me.tabMouseEvents.Name = "tabMouseEvents"
        Me.tabMouseEvents.Padding = New System.Windows.Forms.Padding(3)
        Me.tabMouseEvents.Size = New System.Drawing.Size(338, 387)
        Me.tabMouseEvents.TabIndex = 1
        Me.tabMouseEvents.Text = "Mouse Events"
        Me.tabMouseEvents.UseVisualStyleBackColor = True
        '
        'tabKeyboardEvents
        '
        Me.tabKeyboardEvents.Controls.Add(Me.fmKeyboard)
        Me.tabKeyboardEvents.Location = New System.Drawing.Point(4, 22)
        Me.tabKeyboardEvents.Name = "tabKeyboardEvents"
        Me.tabKeyboardEvents.Padding = New System.Windows.Forms.Padding(3)
        Me.tabKeyboardEvents.Size = New System.Drawing.Size(338, 387)
        Me.tabKeyboardEvents.TabIndex = 2
        Me.tabKeyboardEvents.Text = "Keyboard Events"
        Me.tabKeyboardEvents.UseVisualStyleBackColor = True
        '
        'tabTriadEvents
        '
        Me.tabTriadEvents.Controls.Add(Me.fmTriad)
        Me.tabTriadEvents.Location = New System.Drawing.Point(4, 22)
        Me.tabTriadEvents.Name = "tabTriadEvents"
        Me.tabTriadEvents.Padding = New System.Windows.Forms.Padding(3)
        Me.tabTriadEvents.Size = New System.Drawing.Size(338, 387)
        Me.tabTriadEvents.TabIndex = 3
        Me.tabTriadEvents.Text = "Triad Events"
        Me.tabTriadEvents.UseVisualStyleBackColor = True
        '
        'btnStartStop
        '
        Me.btnStartStop.Location = New System.Drawing.Point(12, 7)
        Me.btnStartStop.Name = "btnStartStop"
        Me.btnStartStop.Size = New System.Drawing.Size(98, 23)
        Me.btnStartStop.TabIndex = 69
        Me.btnStartStop.Text = "Start Interaction"
        Me.btnStartStop.UseVisualStyleBackColor = True
        '
        'frmInteraction
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.SystemColors.Control
        Me.ClientSize = New System.Drawing.Size(363, 737)
        Me.Controls.Add(Me.btnStartStop)
        Me.Controls.Add(Me.tabSettings)
        Me.Controls.Add(Me.txtStatusBar)
        Me.Controls.Add(Me.fmEventPriority)
        Me.Controls.Add(Me.chkKeepFaces)
        Me.Controls.Add(Me.chkDisableInteraction)
        Me.Controls.Add(Me.cmdClear)
        Me.Controls.Add(Me.chkDatabaseUnits)
        Me.Controls.Add(Me.txtResults)
        Me.Controls.Add(Me.cmdCancel)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Cursor = System.Windows.Forms.Cursors.Default
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Location = New System.Drawing.Point(5, 29)
        Me.Margin = New System.Windows.Forms.Padding(2)
        Me.MaximizeBox = False
        Me.Name = "frmInteraction"
        Me.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "User Interaction"
        Me.fmTriad.ResumeLayout(False)
        Me.fmDegreeOfFreedom.ResumeLayout(False)
        Me.fmKeyboard.ResumeLayout(False)
        Me.fmEventPriority.ResumeLayout(False)
        Me.fmMouse.ResumeLayout(False)
        Me.fmSelection.ResumeLayout(False)
        Me.Frame1.ResumeLayout(False)
        Me.Frame1.PerformLayout()
        Me.tabSettings.ResumeLayout(False)
        Me.tabSelectEvents.ResumeLayout(False)
        Me.tabMouseEvents.ResumeLayout(False)
        Me.tabKeyboardEvents.ResumeLayout(False)
        Me.tabTriadEvents.ResumeLayout(False)
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents btnReset As System.Windows.Forms.Button
    Friend WithEvents tabSettings As System.Windows.Forms.TabControl
    Friend WithEvents tabSelectEvents As System.Windows.Forms.TabPage
    Friend WithEvents tabMouseEvents As System.Windows.Forms.TabPage
    Friend WithEvents tabKeyboardEvents As System.Windows.Forms.TabPage
    Friend WithEvents tabTriadEvents As System.Windows.Forms.TabPage
    Friend WithEvents btnClearAll As System.Windows.Forms.Button
    Friend WithEvents btnStartStop As System.Windows.Forms.Button
    Friend WithEvents Label3 As System.Windows.Forms.Label
#End Region
End Class