<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> Partial Class BrowserControl
#Region "Windows Form Designer generated code "
	<System.Diagnostics.DebuggerNonUserCode()> Public Sub New()
		MyBase.New()
        'This call is required by the Windows Form Designer.
        m_bIsInitializing = True
		InitializeComponent()
        UserControl_Initialize()
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
	'Required by the Windows Form Designer
	Private components As System.ComponentModel.IContainer
	Public ToolTip1 As System.Windows.Forms.ToolTip
	Friend WithEvents chkDisplayCurves As System.Windows.Forms.CheckBox
	Friend WithEvents lstTrackPoints As System.Windows.Forms.ListBox
	Friend WithEvents cmdRunAnalysis As System.Windows.Forms.Button
	Friend WithEvents Label1 As System.Windows.Forms.Label
	'NOTE: The following procedure is required by the Windows Form Designer
	'It can be modified using the Windows Form Designer.
	'Do not modify it using the code editor.
	<System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
		Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(BrowserControl))
		Me.components = New System.ComponentModel.Container()
		Me.ToolTip1 = New System.Windows.Forms.ToolTip(components)
		Me.chkDisplayCurves = New System.Windows.Forms.CheckBox
		Me.lstTrackPoints = New System.Windows.Forms.ListBox
		Me.cmdRunAnalysis = New System.Windows.Forms.Button
		Me.Label1 = New System.Windows.Forms.Label
		Me.SuspendLayout()
		Me.ToolTip1.Active = True
		Me.ClientSize = New System.Drawing.Size(167, 292)
		MyBase.Location = New System.Drawing.Point(0, 0)
		MyBase.Name = "BrowserControl"
		Me.chkDisplayCurves.Text = "Display Coupler Curves"
		Me.chkDisplayCurves.Enabled = False
		Me.chkDisplayCurves.Size = New System.Drawing.Size(149, 13)
		Me.chkDisplayCurves.Location = New System.Drawing.Point(8, 240)
		Me.chkDisplayCurves.TabIndex = 3
		Me.chkDisplayCurves.CheckState = System.Windows.Forms.CheckState.Checked
		Me.chkDisplayCurves.CheckAlign = System.Drawing.ContentAlignment.MiddleLeft
		Me.chkDisplayCurves.FlatStyle = System.Windows.Forms.FlatStyle.Standard
		Me.chkDisplayCurves.BackColor = System.Drawing.SystemColors.Control
		Me.chkDisplayCurves.CausesValidation = True
		Me.chkDisplayCurves.ForeColor = System.Drawing.SystemColors.ControlText
		Me.chkDisplayCurves.Cursor = System.Windows.Forms.Cursors.Default
		Me.chkDisplayCurves.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.chkDisplayCurves.Appearance = System.Windows.Forms.Appearance.Normal
		Me.chkDisplayCurves.TabStop = True
		Me.chkDisplayCurves.Visible = True
		Me.chkDisplayCurves.Name = "chkDisplayCurves"
		Me.lstTrackPoints.Size = New System.Drawing.Size(157, 215)
		Me.lstTrackPoints.Location = New System.Drawing.Point(4, 20)
		Me.lstTrackPoints.TabIndex = 2
		Me.lstTrackPoints.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
		Me.lstTrackPoints.BackColor = System.Drawing.SystemColors.Window
		Me.lstTrackPoints.CausesValidation = True
		Me.lstTrackPoints.Enabled = True
		Me.lstTrackPoints.ForeColor = System.Drawing.SystemColors.WindowText
		Me.lstTrackPoints.IntegralHeight = True
		Me.lstTrackPoints.Cursor = System.Windows.Forms.Cursors.Default
		Me.lstTrackPoints.SelectionMode = System.Windows.Forms.SelectionMode.One
		Me.lstTrackPoints.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.lstTrackPoints.Sorted = False
		Me.lstTrackPoints.TabStop = True
		Me.lstTrackPoints.Visible = True
		Me.lstTrackPoints.MultiColumn = False
		Me.lstTrackPoints.Name = "lstTrackPoints"
		Me.cmdRunAnalysis.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		Me.cmdRunAnalysis.Text = "Run Analysis"
		Me.cmdRunAnalysis.Enabled = False
		Me.cmdRunAnalysis.Size = New System.Drawing.Size(80, 25)
		Me.cmdRunAnalysis.Location = New System.Drawing.Point(8, 260)
		Me.cmdRunAnalysis.TabIndex = 1
		Me.cmdRunAnalysis.BackColor = System.Drawing.SystemColors.Control
		Me.cmdRunAnalysis.CausesValidation = True
		Me.cmdRunAnalysis.ForeColor = System.Drawing.SystemColors.ControlText
		Me.cmdRunAnalysis.Cursor = System.Windows.Forms.Cursors.Default
		Me.cmdRunAnalysis.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.cmdRunAnalysis.TabStop = True
		Me.cmdRunAnalysis.Name = "cmdRunAnalysis"
		Me.Label1.Text = "Track Points:"
		Me.Label1.Size = New System.Drawing.Size(101, 13)
		Me.Label1.Location = New System.Drawing.Point(8, 4)
		Me.Label1.TabIndex = 0
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
		Me.Controls.Add(chkDisplayCurves)
		Me.Controls.Add(lstTrackPoints)
		Me.Controls.Add(cmdRunAnalysis)
		Me.Controls.Add(Label1)
		Me.ResumeLayout(False)
		Me.PerformLayout()
	End Sub
#End Region 
#Region "Upgrade Support"
	<System.Runtime.InteropServices.ProgId("ShowHideResultCurvesEventArgs_NET.ShowHideResultCurvesEventArgs")> Public NotInheritable Class ShowHideResultCurvesEventArgs
		Inherits System.EventArgs
		Public Show_Renamed As Boolean
		Public Sub New(ByRef Show_Renamed As Boolean)
			MyBase.New()
			Me.Show_Renamed = Show_Renamed
		End Sub
	End Class
	<System.Runtime.InteropServices.ProgId("TrackPointDeletedEventArgs_NET.TrackPointDeletedEventArgs")> Public NotInheritable Class TrackPointDeletedEventArgs
		Inherits System.EventArgs
		Public PointName As String
		Public Sub New(ByRef PointName As String)
			MyBase.New()
			Me.PointName = PointName
		End Sub
	End Class
	<System.Runtime.InteropServices.ProgId("TrackPointSelectedEventArgs_NET.TrackPointSelectedEventArgs")> Public NotInheritable Class TrackPointSelectedEventArgs
		Inherits System.EventArgs
		Public PointName As String
		Public Sub New(ByRef PointName As String)
			MyBase.New()
			Me.PointName = PointName
		End Sub
	End Class
#End Region 
End Class