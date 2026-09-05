Imports Inventor

Friend Class RackFaceCmdDlg
    Inherits System.Windows.Forms.Form

#Region " Windows Form Designer generated code "

    Public m_rackHeight As String
    Public m_rackWidth As String
    Public m_numTeeth As String
    Public m_rackExtents As String
    Public m_rackExtentsDirection As Integer

    Private m_application As Application
    Private m_rackFaceCmd As RackFaceCmd

    Public Sub New(ByVal application As Application, ByVal rackFaceCmd As RackFaceCmd)
        MyBase.New()

        'This call is required by the Windows Form Designer.

        InitializeComponent()

        'Add any initialization after the InitializeComponent() call
        m_application = application
        m_rackFaceCmd = rackFaceCmd

        m_rackHeight = "0.1"
        m_rackWidth = "0.50"
        m_numTeeth = "5"
        m_rackExtents = "1.0"
        m_rackExtentsDirection = 0

        buttonOK.Enabled = False
        checkBoxFace.Checked = True

        radioButtonNegativeExtent.Checked = True
    End Sub

    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    Public WithEvents checkBoxFace As System.Windows.Forms.CheckBox
    Public WithEvents checkBoxDirection As System.Windows.Forms.CheckBox
    Private WithEvents buttonHelp As System.Windows.Forms.Button
    Friend WithEvents GroupBoxRackParams As System.Windows.Forms.GroupBox
    Friend WithEvents groupBoxExtents As System.Windows.Forms.GroupBox
    Friend textBoxExtentsEdit As System.Windows.Forms.TextBox
    Friend WithEvents radioButtonNegativeExtent As System.Windows.Forms.RadioButton
    Friend WithEvents radioButtonPositiveExtent As System.Windows.Forms.RadioButton
    Friend WithEvents radioButtonSymmetricExtent As System.Windows.Forms.RadioButton
    Friend WithEvents LabelFace As System.Windows.Forms.Label
    Friend WithEvents LabelDirection As System.Windows.Forms.Label
    Friend WithEvents LabelTeeth As System.Windows.Forms.Label
    Friend WithEvents LabelHeight As System.Windows.Forms.Label
    Friend WithEvents LabelWidth As System.Windows.Forms.Label
    Friend textBoxNumOfTeeth As System.Windows.Forms.TextBox
    Friend textBoxHeight As System.Windows.Forms.TextBox
    Friend textBoxWidth As System.Windows.Forms.TextBox
    Friend WithEvents buttonCancel As System.Windows.Forms.Button
    Public WithEvents buttonOK As System.Windows.Forms.Button

    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(RackFaceCmdDlg))
        Me.checkBoxFace = New System.Windows.Forms.CheckBox
        Me.checkBoxDirection = New System.Windows.Forms.CheckBox
        Me.buttonHelp = New System.Windows.Forms.Button
        Me.buttonOK = New System.Windows.Forms.Button
        Me.buttonCancel = New System.Windows.Forms.Button
        Me.GroupBoxRackParams = New System.Windows.Forms.GroupBox
        Me.textBoxWidth = New System.Windows.Forms.TextBox
        Me.textBoxHeight = New System.Windows.Forms.TextBox
        Me.textBoxNumOfTeeth = New System.Windows.Forms.TextBox
        Me.LabelWidth = New System.Windows.Forms.Label
        Me.LabelHeight = New System.Windows.Forms.Label
        Me.LabelTeeth = New System.Windows.Forms.Label
        Me.groupBoxExtents = New System.Windows.Forms.GroupBox
        Me.radioButtonSymmetricExtent = New System.Windows.Forms.RadioButton
        Me.radioButtonPositiveExtent = New System.Windows.Forms.RadioButton
        Me.radioButtonNegativeExtent = New System.Windows.Forms.RadioButton
        Me.textBoxExtentsEdit = New System.Windows.Forms.TextBox
        Me.LabelFace = New System.Windows.Forms.Label
        Me.LabelDirection = New System.Windows.Forms.Label
        Me.GroupBoxRackParams.SuspendLayout()
        Me.groupBoxExtents.SuspendLayout()
        Me.SuspendLayout()
        '
        'checkBoxFace
        '
        Me.checkBoxFace.Appearance = System.Windows.Forms.Appearance.Button
        Me.checkBoxFace.Image = CType(resources.GetObject("checkBoxFace.Image"), System.Drawing.Image)
        Me.checkBoxFace.Location = New System.Drawing.Point(15, 16)
        Me.checkBoxFace.Name = "checkBoxFace"
        Me.checkBoxFace.Size = New System.Drawing.Size(29, 25)
        Me.checkBoxFace.TabIndex = 0
        '
        'checkBoxDirection
        '
        Me.checkBoxDirection.Appearance = System.Windows.Forms.Appearance.Button
        Me.checkBoxDirection.Image = CType(resources.GetObject("checkBoxDirection.Image"), System.Drawing.Image)
        Me.checkBoxDirection.Location = New System.Drawing.Point(15, 56)
        Me.checkBoxDirection.Name = "checkBoxDirection"
        Me.checkBoxDirection.Size = New System.Drawing.Size(29, 25)
        Me.checkBoxDirection.TabIndex = 1
        '
        'buttonHelp
        '
        Me.buttonHelp.Image = CType(resources.GetObject("buttonHelp.Image"), System.Drawing.Image)
        Me.buttonHelp.Location = New System.Drawing.Point(16, 200)
        Me.buttonHelp.Name = "buttonHelp"
        Me.buttonHelp.Size = New System.Drawing.Size(29, 25)
        Me.buttonHelp.TabIndex = 2
        '
        'buttonOK
        '
        Me.buttonOK.Location = New System.Drawing.Point(160, 200)
        Me.buttonOK.Name = "buttonOK"
        Me.buttonOK.Size = New System.Drawing.Size(75, 23)
        Me.buttonOK.TabIndex = 3
        Me.buttonOK.Text = "OK"
        '
        'buttonCancel
        '
        Me.buttonCancel.Location = New System.Drawing.Point(272, 200)
        Me.buttonCancel.Name = "buttonCancel"
        Me.buttonCancel.Size = New System.Drawing.Size(75, 23)
        Me.buttonCancel.TabIndex = 4
        Me.buttonCancel.Text = "Cancel"
        '
        'GroupBoxRackParams
        '
        Me.GroupBoxRackParams.Controls.Add(Me.textBoxWidth)
        Me.GroupBoxRackParams.Controls.Add(Me.textBoxHeight)
        Me.GroupBoxRackParams.Controls.Add(Me.textBoxNumOfTeeth)
        Me.GroupBoxRackParams.Controls.Add(Me.LabelWidth)
        Me.GroupBoxRackParams.Controls.Add(Me.LabelHeight)
        Me.GroupBoxRackParams.Controls.Add(Me.LabelTeeth)
        Me.GroupBoxRackParams.Controls.Add(Me.groupBoxExtents)
        Me.GroupBoxRackParams.Location = New System.Drawing.Point(112, 16)
        Me.GroupBoxRackParams.Name = "GroupBoxRackParams"
        Me.GroupBoxRackParams.Size = New System.Drawing.Size(232, 168)
        Me.GroupBoxRackParams.TabIndex = 5
        Me.GroupBoxRackParams.TabStop = False
        Me.GroupBoxRackParams.Text = "Rack Parameters"
        '
        'textBoxWidth
        '
        Me.textBoxWidth.Location = New System.Drawing.Point(112, 80)
        Me.textBoxWidth.Name = "textBoxWidth"
        Me.textBoxWidth.Size = New System.Drawing.Size(114, 20)
        Me.textBoxWidth.TabIndex = 6
        Me.textBoxWidth.Text = "0.50"
        AddHandler textBoxWidth.TextChanged, AddressOf Me.OnChangeRackWidthEdit
        '
        'textBoxHeight
        '
        Me.textBoxHeight.Location = New System.Drawing.Point(112, 48)
        Me.textBoxHeight.Name = "textBoxHeight"
        Me.textBoxHeight.Size = New System.Drawing.Size(114, 20)
        Me.textBoxHeight.TabIndex = 5
        Me.textBoxHeight.Text = "0.1"
        AddHandler textBoxHeight.TextChanged, AddressOf Me.OnChangeRackHeightEdit
        '
        'textBoxNumOfTeeth
        '
        Me.textBoxNumOfTeeth.Location = New System.Drawing.Point(112, 16)
        Me.textBoxNumOfTeeth.Name = "textBoxNumOfTeeth"
        Me.textBoxNumOfTeeth.Size = New System.Drawing.Size(114, 20)
        Me.textBoxNumOfTeeth.TabIndex = 4
        Me.textBoxNumOfTeeth.Text = "5"
        AddHandler textBoxNumOfTeeth.TextChanged, AddressOf Me.OnChangeTeethNumberEdit
        '
        'LabelWidth
        '
        Me.LabelWidth.Location = New System.Drawing.Point(24, 80)
        Me.LabelWidth.Name = "LabelWidth"
        Me.LabelWidth.Size = New System.Drawing.Size(56, 23)
        Me.LabelWidth.TabIndex = 3
        Me.LabelWidth.Text = "Width"
        '
        'LabelHeight
        '
        Me.LabelHeight.Location = New System.Drawing.Point(24, 48)
        Me.LabelHeight.Name = "LabelHeight"
        Me.LabelHeight.Size = New System.Drawing.Size(56, 23)
        Me.LabelHeight.TabIndex = 2
        Me.LabelHeight.Text = "Height"
        '
        'LabelTeeth
        '
        Me.LabelTeeth.Location = New System.Drawing.Point(24, 16)
        Me.LabelTeeth.Name = "LabelTeeth"
        Me.LabelTeeth.Size = New System.Drawing.Size(64, 23)
        Me.LabelTeeth.TabIndex = 1
        Me.LabelTeeth.Text = "No.of teeth"
        '
        'groupBoxExtents
        '
        Me.groupBoxExtents.Controls.Add(Me.radioButtonSymmetricExtent)
        Me.groupBoxExtents.Controls.Add(Me.radioButtonPositiveExtent)
        Me.groupBoxExtents.Controls.Add(Me.radioButtonNegativeExtent)
        Me.groupBoxExtents.Controls.Add(Me.textBoxExtentsEdit)
        Me.groupBoxExtents.Location = New System.Drawing.Point(8, 112)
        Me.groupBoxExtents.Name = "groupBoxExtents"
        Me.groupBoxExtents.Size = New System.Drawing.Size(216, 48)
        Me.groupBoxExtents.TabIndex = 0
        Me.groupBoxExtents.TabStop = False
        Me.groupBoxExtents.Text = "Extents"
        '
        'radioButtonSymmetricExtent
        '
        Me.radioButtonSymmetricExtent.Appearance = System.Windows.Forms.Appearance.Button
        Me.radioButtonSymmetricExtent.Image = CType(resources.GetObject("radioButtonSymmetricExtent.Image"), System.Drawing.Image)
        Me.radioButtonSymmetricExtent.Location = New System.Drawing.Point(176, 16)
        Me.radioButtonSymmetricExtent.Name = "radioButtonSymmetricExtent"
        Me.radioButtonSymmetricExtent.Size = New System.Drawing.Size(29, 24)
        Me.radioButtonSymmetricExtent.TabIndex = 3
        '
        'radioButtonPositiveExtent
        '
        Me.radioButtonPositiveExtent.Appearance = System.Windows.Forms.Appearance.Button
        Me.radioButtonPositiveExtent.Image = CType(resources.GetObject("radioButtonPositiveExtent.Image"), System.Drawing.Image)
        Me.radioButtonPositiveExtent.Location = New System.Drawing.Point(144, 16)
        Me.radioButtonPositiveExtent.Name = "radioButtonPositiveExtent"
        Me.radioButtonPositiveExtent.Size = New System.Drawing.Size(29, 24)
        Me.radioButtonPositiveExtent.TabIndex = 2
        '
        'radioButtonNegativeExtent
        '
        Me.radioButtonNegativeExtent.Appearance = System.Windows.Forms.Appearance.Button
        Me.radioButtonNegativeExtent.Image = CType(resources.GetObject("radioButtonNegativeExtent.Image"), System.Drawing.Image)
        Me.radioButtonNegativeExtent.Location = New System.Drawing.Point(112, 16)
        Me.radioButtonNegativeExtent.Name = "radioButtonNegativeExtent"
        Me.radioButtonNegativeExtent.Size = New System.Drawing.Size(29, 24)
        Me.radioButtonNegativeExtent.TabIndex = 1
        '
        'textBoxExtentsEdit
        '
        Me.textBoxExtentsEdit.Location = New System.Drawing.Point(8, 16)
        Me.textBoxExtentsEdit.Name = "textBoxExtentsEdit"
        Me.textBoxExtentsEdit.Size = New System.Drawing.Size(100, 20)
        Me.textBoxExtentsEdit.TabIndex = 0
        Me.textBoxExtentsEdit.Text = "1.0"
        AddHandler textBoxExtentsEdit.TextChanged, AddressOf Me.OnChangeRackExtentsEdit
        '
        'LabelFace
        '
        Me.LabelFace.Location = New System.Drawing.Point(56, 16)
        Me.LabelFace.Name = "LabelFace"
        Me.LabelFace.Size = New System.Drawing.Size(32, 23)
        Me.LabelFace.TabIndex = 6
        Me.LabelFace.Text = "Face"
        '
        'LabelDirection
        '
        Me.LabelDirection.Location = New System.Drawing.Point(56, 56)
        Me.LabelDirection.Name = "LabelDirection"
        Me.LabelDirection.Size = New System.Drawing.Size(56, 24)
        Me.LabelDirection.TabIndex = 7
        Me.LabelDirection.Text = "Direction"
        '
        'RackFaceCmdDlg
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(362, 239)
        Me.Controls.Add(Me.LabelDirection)
        Me.Controls.Add(Me.LabelFace)
        Me.Controls.Add(Me.GroupBoxRackParams)
        Me.Controls.Add(Me.buttonCancel)
        Me.Controls.Add(Me.buttonOK)
        Me.Controls.Add(Me.buttonHelp)
        Me.Controls.Add(Me.checkBoxDirection)
        Me.Controls.Add(Me.checkBoxFace)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.KeyPreview = True
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "RackFaceCmdDlg"
        Me.Text = "Rack Face"
        Me.GroupBoxRackParams.ResumeLayout(False)
        Me.GroupBoxRackParams.PerformLayout()
        Me.groupBoxExtents.ResumeLayout(False)
        Me.groupBoxExtents.PerformLayout()
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub RackFaceCmdDlg_KeyPress(ByVal sender As Object, ByVal e As System.Windows.Forms.KeyPressEventArgs) Handles MyBase.KeyPress
        '"Esc" key cancels command
        If System.Convert.ToInt32(e.KeyChar) = 27 Then
            m_rackFaceCmd.StopCommand()
        End If
    End Sub

    Private Sub OnSelectRackDirectionButton(ByVal sender As Object, ByVal e As System.EventArgs) Handles checkBoxDirection.Click
        'Disable rack face selection button
        checkBoxFace.Checked = False

        'If selected then start direction selection
        If checkBoxDirection.Checked Then
            m_rackFaceCmd.EnableInteraction()
        Else
            m_rackFaceCmd.DisableInteraction()
        End If
    End Sub

    Private Sub OnSelectRackFaceButton(ByVal sender As Object, ByVal e As System.EventArgs) Handles checkBoxFace.Click
        'Disable rack direction selection button
        checkBoxDirection.Checked = False

        'If selected then start face selection
        If checkBoxFace.Checked Then
            m_rackFaceCmd.EnableInteraction()
        Else
            m_rackFaceCmd.DisableInteraction()
        End If
    End Sub

    Private Sub OnChangeTeethNumberEdit(ByVal sender As Object, ByVal e As System.EventArgs)
        'Reject invalid input
        If Not ValidateIntInput(textBoxNumOfTeeth.Text.Trim()) Then
            textBoxNumOfTeeth.ForeColor = System.Drawing.Color.Red
            buttonOK.Enabled = False
        Else
            'Input for this parameter is validated
            textBoxNumOfTeeth.ForeColor = System.Drawing.Color.Black
            m_numTeeth = textBoxNumOfTeeth.Text
            m_rackFaceCmd.UpdateCommandStatus()
        End If
    End Sub

    Private Sub OnChangeRackHeightEdit(ByVal sender As Object, ByVal e As System.EventArgs)
        Dim dHeight As Double
        dHeight = m_rackFaceCmd.GetValueFromExpression(textBoxHeight.Text.Trim())
        'Reject invalid input
        If Not ValidateFloatInput(dHeight.ToString()) Then
            textBoxHeight.ForeColor = System.Drawing.Color.Red
            buttonOK.Enabled = False
        Else
            'Input for this parameter is validated
            textBoxHeight.ForeColor = System.Drawing.Color.Black
            m_rackHeight = textBoxHeight.Text
            m_rackFaceCmd.UpdateCommandStatus()
        End If
    End Sub

    Private Sub OnChangeRackWidthEdit(ByVal sender As Object, ByVal e As System.EventArgs)
        Dim dWidth As Double
        dWidth = m_rackFaceCmd.GetValueFromExpression(textBoxWidth.Text.Trim())
        'Reject invalid input
        If Not ValidateFloatInput(dWidth.ToString()) Then
            textBoxWidth.ForeColor = System.Drawing.Color.Red
            buttonOK.Enabled = False
        Else
            'Input for this parameter is validated
            textBoxWidth.ForeColor = System.Drawing.Color.Black
            m_rackWidth = textBoxWidth.Text
            m_rackFaceCmd.UpdateCommandStatus()
        End If
    End Sub

    Private Sub OnChangeRackExtentsEdit(ByVal sender As Object, ByVal e As System.EventArgs)
        Dim dExtent As Double
        dExtent = m_rackFaceCmd.GetValueFromExpression(textBoxExtentsEdit.Text.Trim())
        'Reject invalid input
        If Not ValidateFloatInput(dExtent.ToString()) Then
            textBoxExtentsEdit.ForeColor = System.Drawing.Color.Red
            buttonOK.Enabled = False
        Else
            'Input for this parameter is validated
            textBoxExtentsEdit.ForeColor = System.Drawing.Color.Black
            m_rackExtents = textBoxExtentsEdit.Text
            m_rackFaceCmd.UpdateCommandStatus()
        End If
    End Sub

    Private Sub OnRackNegativeExtentsButton(ByVal sender As Object, ByVal e As System.EventArgs) Handles radioButtonNegativeExtent.Click
        m_rackExtentsDirection = 0
        m_rackFaceCmd.UpdateCommandStatus()
    End Sub

    Private Sub OnRackPositiveExtentsButton(ByVal sender As Object, ByVal e As System.EventArgs) Handles radioButtonPositiveExtent.Click
        m_rackExtentsDirection = 1
        m_rackFaceCmd.UpdateCommandStatus()
    End Sub

    Private Sub OnRackSymmetricExtentsButton(ByVal sender As Object, ByVal e As System.EventArgs) Handles radioButtonSymmetricExtent.Click
        m_rackExtentsDirection = 2
        m_rackFaceCmd.UpdateCommandStatus()
    End Sub

    Private Function ValidateIntInput(ByVal input As String) As Boolean
        Try
            Dim num As Integer
            num = System.Convert.ToInt32(input)

            If num <= 0 Then
                Return False
            End If
        Catch ex As Exception
            Return False
        End Try

        Return True
    End Function

    Private Function ValidateFloatInput(ByVal input As String) As Boolean
        Try
            Dim num As Single
            num = System.Convert.ToSingle(input)

            If num <= 0 Then
                Return False
            End If
        Catch ex As Exception
            Return False
        End Try

        Return True
    End Function

    Public Function AllParametersAreValid() As Boolean

        AllParametersAreValid = (Not textBoxNumOfTeeth.ForeColor.Equals(System.Drawing.Color.Red) And _
                Not textBoxHeight.ForeColor.Equals(System.Drawing.Color.Red) And _
                Not textBoxExtentsEdit.ForeColor.Equals(System.Drawing.Color.Red))
    End Function

    Private Sub OnOK(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles buttonOK.Click
        m_rackFaceCmd.ExecuteCommand()
    End Sub

    Private Sub OnCancel(ByVal sender As Object, ByVal e As System.EventArgs) Handles buttonCancel.Click
        m_rackFaceCmd.StopCommand()
    End Sub

    Private Sub RackFaceCmdDlg_Closed(ByVal sender As Object, ByVal e As System.EventArgs) Handles MyBase.Closed
        m_rackFaceCmd.StopCommand()
    End Sub

    Private Sub OnHelpButton(ByVal sender As Object, ByVal e As System.EventArgs) Handles buttonHelp.Click
        'Get the help manager object and display the start page of the "Inventor API help"
        m_application.HelpManager.DisplayHelpTopic("ADMAPI_12_0.chm", "")
    End Sub

End Class
