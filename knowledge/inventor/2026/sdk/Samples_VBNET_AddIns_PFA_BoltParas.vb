'BoltParas: A dialog for user to input bolt parameters
Imports Inventor

Public Class BoltParas
    Inherits System.Windows.Forms.Form

    Public iParameterErrors As Integer = 0

    Private bInvalid As Boolean = False
    Private oUOM As UnitsOfMeasure = Nothing
    Private oPosition As Point = Nothing
    Private bExitFlag As Boolean = False

    'CreateBoltEvent fired when user clicks OK or Cancel to create a bolt or close the dialog
    Public Event CreateBoltEvent(ByVal sender As Object, ByVal OkFlag As Boolean, ByVal oDefinition As clsBolt.BoltParameter)
    'PositionChangedEvent fired when user modifies position coordinates
    Public Event PositionChangedEvent(ByVal sender As Object, ByVal x As Double, ByVal y As Double, ByVal z As Double)
    'define a delegate used for checking validation of parameters
    Private Delegate Function DelegateIfParameterValid(ByVal input As String, ByVal unit As UnitsTypeEnum) As Boolean

#Region " Windows Form Designer generated code "

    Public Sub New(ByVal oUnitsOfMeasure As UnitsOfMeasure)
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'initialize variables
        oUOM = oUnitsOfMeasure
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
    Friend WithEvents btCreate As System.Windows.Forms.Button
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents btCancel As System.Windows.Forms.Button
    Friend WithEvents txtZ As System.Windows.Forms.TextBox
    Friend WithEvents txtFillet As System.Windows.Forms.TextBox
    Friend WithEvents lblX As System.Windows.Forms.Label
    Friend WithEvents txtBoltName As System.Windows.Forms.TextBox
    Friend WithEvents lblBoltName As System.Windows.Forms.Label
    Friend WithEvents lblY As System.Windows.Forms.Label
    Friend WithEvents txtY As System.Windows.Forms.TextBox
    Friend WithEvents lblFillet As System.Windows.Forms.Label
    Friend WithEvents lblChamfer As System.Windows.Forms.Label
    Friend WithEvents lblAngle1 As System.Windows.Forms.Label
    Friend WithEvents lblLength2 As System.Windows.Forms.Label
    Friend WithEvents lblLength1 As System.Windows.Forms.Label
    Friend WithEvents lblHeight1 As System.Windows.Forms.Label
    Friend WithEvents lblDiameter2 As System.Windows.Forms.Label
    Friend WithEvents lbDiameter1 As System.Windows.Forms.Label
    Friend WithEvents lblZ As System.Windows.Forms.Label
    Friend WithEvents txtChamfer As System.Windows.Forms.TextBox
    Friend WithEvents txtAngle1 As System.Windows.Forms.TextBox
    Friend WithEvents txtLength2 As System.Windows.Forms.TextBox
    Friend WithEvents txtLength1 As System.Windows.Forms.TextBox
    Friend WithEvents txtHeight1 As System.Windows.Forms.TextBox
    Friend WithEvents txtDiameter2 As System.Windows.Forms.TextBox
    Friend WithEvents txtDiameter1 As System.Windows.Forms.TextBox
    Friend WithEvents txtX As System.Windows.Forms.TextBox
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.btCancel = New System.Windows.Forms.Button
        Me.btCreate = New System.Windows.Forms.Button
        Me.GroupBox1 = New System.Windows.Forms.GroupBox
        Me.txtZ = New System.Windows.Forms.TextBox
        Me.txtFillet = New System.Windows.Forms.TextBox
        Me.lblX = New System.Windows.Forms.Label
        Me.txtBoltName = New System.Windows.Forms.TextBox
        Me.lblBoltName = New System.Windows.Forms.Label
        Me.lblY = New System.Windows.Forms.Label
        Me.txtY = New System.Windows.Forms.TextBox
        Me.lblFillet = New System.Windows.Forms.Label
        Me.lblChamfer = New System.Windows.Forms.Label
        Me.lblAngle1 = New System.Windows.Forms.Label
        Me.lblLength2 = New System.Windows.Forms.Label
        Me.lblLength1 = New System.Windows.Forms.Label
        Me.lblHeight1 = New System.Windows.Forms.Label
        Me.lblDiameter2 = New System.Windows.Forms.Label
        Me.lbDiameter1 = New System.Windows.Forms.Label
        Me.lblZ = New System.Windows.Forms.Label
        Me.txtChamfer = New System.Windows.Forms.TextBox
        Me.txtAngle1 = New System.Windows.Forms.TextBox
        Me.txtLength2 = New System.Windows.Forms.TextBox
        Me.txtLength1 = New System.Windows.Forms.TextBox
        Me.txtHeight1 = New System.Windows.Forms.TextBox
        Me.txtDiameter2 = New System.Windows.Forms.TextBox
        Me.txtDiameter1 = New System.Windows.Forms.TextBox
        Me.txtX = New System.Windows.Forms.TextBox
        Me.GroupBox1.SuspendLayout()
        Me.SuspendLayout()
        '
        'btCancel
        '
        Me.btCancel.Location = New System.Drawing.Point(112, 348)
        Me.btCancel.Name = "btCancel"
        Me.btCancel.Size = New System.Drawing.Size(108, 24)
        Me.btCancel.TabIndex = 14
        Me.btCancel.Text = "Cancel"
        '
        'btCreate
        '
        Me.btCreate.Enabled = False
        Me.btCreate.Location = New System.Drawing.Point(8, 348)
        Me.btCreate.Name = "btCreate"
        Me.btCreate.Size = New System.Drawing.Size(104, 24)
        Me.btCreate.TabIndex = 13
        Me.btCreate.Text = "OK"
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.txtZ)
        Me.GroupBox1.Controls.Add(Me.txtFillet)
        Me.GroupBox1.Controls.Add(Me.lblX)
        Me.GroupBox1.Controls.Add(Me.txtBoltName)
        Me.GroupBox1.Controls.Add(Me.lblBoltName)
        Me.GroupBox1.Controls.Add(Me.lblY)
        Me.GroupBox1.Controls.Add(Me.txtY)
        Me.GroupBox1.Controls.Add(Me.lblFillet)
        Me.GroupBox1.Controls.Add(Me.lblChamfer)
        Me.GroupBox1.Controls.Add(Me.lblAngle1)
        Me.GroupBox1.Controls.Add(Me.lblLength2)
        Me.GroupBox1.Controls.Add(Me.lblLength1)
        Me.GroupBox1.Controls.Add(Me.lblHeight1)
        Me.GroupBox1.Controls.Add(Me.lblDiameter2)
        Me.GroupBox1.Controls.Add(Me.lbDiameter1)
        Me.GroupBox1.Controls.Add(Me.lblZ)
        Me.GroupBox1.Controls.Add(Me.txtChamfer)
        Me.GroupBox1.Controls.Add(Me.txtAngle1)
        Me.GroupBox1.Controls.Add(Me.txtLength2)
        Me.GroupBox1.Controls.Add(Me.txtLength1)
        Me.GroupBox1.Controls.Add(Me.txtHeight1)
        Me.GroupBox1.Controls.Add(Me.txtDiameter2)
        Me.GroupBox1.Controls.Add(Me.txtDiameter1)
        Me.GroupBox1.Controls.Add(Me.txtX)
        Me.GroupBox1.Location = New System.Drawing.Point(8, 8)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(212, 332)
        Me.GroupBox1.TabIndex = 54
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Parameters"
        '
        'txtZ
        '
        Me.txtZ.Enabled = False
        Me.txtZ.Location = New System.Drawing.Point(160, 304)
        Me.txtZ.Name = "txtZ"
        Me.txtZ.Size = New System.Drawing.Size(36, 20)
        Me.txtZ.TabIndex = 68
        Me.txtZ.Text = "0"
        '
        'txtFillet
        '
        Me.txtFillet.Location = New System.Drawing.Point(144, 276)
        Me.txtFillet.Name = "txtFillet"
        Me.txtFillet.Size = New System.Drawing.Size(56, 20)
        Me.txtFillet.TabIndex = 65
        Me.txtFillet.Text = "0.02994"
        '
        'lblX
        '
        Me.lblX.Location = New System.Drawing.Point(12, 308)
        Me.lblX.Name = "lblX"
        Me.lblX.Size = New System.Drawing.Size(16, 16)
        Me.lblX.TabIndex = 78
        Me.lblX.Text = "X:"
        '
        'txtBoltName
        '
        Me.txtBoltName.Location = New System.Drawing.Point(144, 20)
        Me.txtBoltName.Name = "txtBoltName"
        Me.txtBoltName.Size = New System.Drawing.Size(56, 20)
        Me.txtBoltName.TabIndex = 57
        Me.txtBoltName.Text = "Bolt1"
        '
        'lblBoltName
        '
        Me.lblBoltName.Location = New System.Drawing.Point(8, 24)
        Me.lblBoltName.Name = "lblBoltName"
        Me.lblBoltName.Size = New System.Drawing.Size(128, 16)
        Me.lblBoltName.TabIndex = 71
        Me.lblBoltName.Text = "Bolt Name:"
        '
        'lblY
        '
        Me.lblY.Location = New System.Drawing.Point(72, 308)
        Me.lblY.Name = "lblY"
        Me.lblY.Size = New System.Drawing.Size(20, 16)
        Me.lblY.TabIndex = 79
        Me.lblY.Text = "Y:"
        '
        'txtY
        '
        Me.txtY.Enabled = False
        Me.txtY.Location = New System.Drawing.Point(96, 304)
        Me.txtY.Name = "txtY"
        Me.txtY.Size = New System.Drawing.Size(36, 20)
        Me.txtY.TabIndex = 67
        Me.txtY.Text = "0"
        '
        'lblFillet
        '
        Me.lblFillet.Location = New System.Drawing.Point(8, 276)
        Me.lblFillet.Name = "lblFillet"
        Me.lblFillet.Size = New System.Drawing.Size(128, 16)
        Me.lblFillet.TabIndex = 77
        Me.lblFillet.Text = "Fillet Radius(inch):"
        '
        'lblChamfer
        '
        Me.lblChamfer.Location = New System.Drawing.Point(8, 244)
        Me.lblChamfer.Name = "lblChamfer"
        Me.lblChamfer.Size = New System.Drawing.Size(128, 16)
        Me.lblChamfer.TabIndex = 76
        Me.lblChamfer.Text = "Chamfer Distance(inch):"
        '
        'lblAngle1
        '
        Me.lblAngle1.Location = New System.Drawing.Point(8, 212)
        Me.lblAngle1.Name = "lblAngle1"
        Me.lblAngle1.Size = New System.Drawing.Size(128, 16)
        Me.lblAngle1.TabIndex = 75
        Me.lblAngle1.Text = "Cut Angle(deg):"
        '
        'lblLength2
        '
        Me.lblLength2.Location = New System.Drawing.Point(8, 180)
        Me.lblLength2.Name = "lblLength2"
        Me.lblLength2.Size = New System.Drawing.Size(128, 16)
        Me.lblLength2.TabIndex = 74
        Me.lblLength2.Text = "Thread Length(inch):"
        '
        'lblLength1
        '
        Me.lblLength1.Location = New System.Drawing.Point(8, 148)
        Me.lblLength1.Name = "lblLength1"
        Me.lblLength1.Size = New System.Drawing.Size(128, 16)
        Me.lblLength1.TabIndex = 73
        Me.lblLength1.Text = "Body Length(inch):"
        '
        'lblHeight1
        '
        Me.lblHeight1.Location = New System.Drawing.Point(8, 116)
        Me.lblHeight1.Name = "lblHeight1"
        Me.lblHeight1.Size = New System.Drawing.Size(128, 16)
        Me.lblHeight1.TabIndex = 72
        Me.lblHeight1.Text = "Head Height(inch):"
        '
        'lblDiameter2
        '
        Me.lblDiameter2.Location = New System.Drawing.Point(8, 84)
        Me.lblDiameter2.Name = "lblDiameter2"
        Me.lblDiameter2.Size = New System.Drawing.Size(128, 16)
        Me.lblDiameter2.TabIndex = 70
        Me.lblDiameter2.Text = "Body Diameter(inch):"
        '
        'lbDiameter1
        '
        Me.lbDiameter1.Location = New System.Drawing.Point(8, 52)
        Me.lbDiameter1.Name = "lbDiameter1"
        Me.lbDiameter1.Size = New System.Drawing.Size(128, 16)
        Me.lbDiameter1.TabIndex = 69
        Me.lbDiameter1.Text = "Head Diameter(inch):"
        '
        'lblZ
        '
        Me.lblZ.Location = New System.Drawing.Point(136, 308)
        Me.lblZ.Name = "lblZ"
        Me.lblZ.Size = New System.Drawing.Size(20, 16)
        Me.lblZ.TabIndex = 80
        Me.lblZ.Text = "Z:"
        '
        'txtChamfer
        '
        Me.txtChamfer.Location = New System.Drawing.Point(144, 244)
        Me.txtChamfer.Name = "txtChamfer"
        Me.txtChamfer.Size = New System.Drawing.Size(56, 20)
        Me.txtChamfer.TabIndex = 64
        Me.txtChamfer.Text = "0.03845"
        '
        'txtAngle1
        '
        Me.txtAngle1.Location = New System.Drawing.Point(144, 212)
        Me.txtAngle1.Name = "txtAngle1"
        Me.txtAngle1.Size = New System.Drawing.Size(56, 20)
        Me.txtAngle1.TabIndex = 63
        Me.txtAngle1.Text = "30"
        '
        'txtLength2
        '
        Me.txtLength2.Location = New System.Drawing.Point(144, 180)
        Me.txtLength2.Name = "txtLength2"
        Me.txtLength2.Size = New System.Drawing.Size(56, 20)
        Me.txtLength2.TabIndex = 62
        Me.txtLength2.Text = "1.25"
        '
        'txtLength1
        '
        Me.txtLength1.Location = New System.Drawing.Point(144, 148)
        Me.txtLength1.Name = "txtLength1"
        Me.txtLength1.Size = New System.Drawing.Size(56, 20)
        Me.txtLength1.TabIndex = 61
        Me.txtLength1.Text = "2.0"
        '
        'txtHeight1
        '
        Me.txtHeight1.Location = New System.Drawing.Point(144, 116)
        Me.txtHeight1.Name = "txtHeight1"
        Me.txtHeight1.Size = New System.Drawing.Size(56, 20)
        Me.txtHeight1.TabIndex = 60
        Me.txtHeight1.Text = "0.3125"
        '
        'txtDiameter2
        '
        Me.txtDiameter2.Location = New System.Drawing.Point(144, 84)
        Me.txtDiameter2.Name = "txtDiameter2"
        Me.txtDiameter2.Size = New System.Drawing.Size(56, 20)
        Me.txtDiameter2.TabIndex = 59
        Me.txtDiameter2.Text = "0.5"
        '
        'txtDiameter1
        '
        Me.txtDiameter1.Location = New System.Drawing.Point(144, 52)
        Me.txtDiameter1.Name = "txtDiameter1"
        Me.txtDiameter1.Size = New System.Drawing.Size(56, 20)
        Me.txtDiameter1.TabIndex = 58
        Me.txtDiameter1.Text = "0.75"
        '
        'txtX
        '
        Me.txtX.Enabled = False
        Me.txtX.Location = New System.Drawing.Point(32, 304)
        Me.txtX.Name = "txtX"
        Me.txtX.Size = New System.Drawing.Size(36, 20)
        Me.txtX.TabIndex = 66
        Me.txtX.Text = "0"
        '
        'BoltParas
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(226, 379)
        Me.Controls.Add(Me.btCancel)
        Me.Controls.Add(Me.btCreate)
        Me.Controls.Add(Me.GroupBox1)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "BoltParas"
        Me.Text = "Create Bolt"
        Me.GroupBox1.ResumeLayout(False)
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub btCancel_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btCancel.Click
        Try
            'set exit flag
            bExitFlag = False

            'close dialog
            Me.Close()
        Catch ex As Exception
            System.Windows.Forms.MessageBox.Show(ex.Message, "PartFeaturesAddin", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Exclamation)
        End Try
    End Sub

    Private Sub btCreate_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btCreate.Click
        Dim oDefinition As clsBolt.BoltParameter

        Try
            'set exit flag
            bExitFlag = True

            'disable this dialog
            Me.Enabled = False

            'get parameters from input
            oDefinition.strBoltID = txtBoltName.Text
            oDefinition.strHeadDiameter = txtDiameter1.Text
            oDefinition.strHeadHeight = txtHeight1.Text
            oDefinition.strBodyDiameter = txtDiameter2.Text
            oDefinition.strBodyLength = txtLength1.Text
            oDefinition.strThreadLength = txtLength2.Text
            oDefinition.strCutAngle = txtAngle1.Text
            oDefinition.strChamferDistance = txtChamfer.Text
            oDefinition.strFilletRadius = txtFillet.Text

            'send event to create
            RaiseEvent CreateBoltEvent(Me, True, oDefinition)
        Catch ex As Exception
            System.Windows.Forms.MessageBox.Show(ex.Message, "PartFeaturesAddin", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Exclamation)
        End Try
    End Sub

    Private Sub BoltParas_Closing(ByVal sender As Object, ByVal e As System.ComponentModel.CancelEventArgs) Handles MyBase.Closing
        Try
            'if exit flag is true then raise event to create bolt, otherwise not
            If Not bExitFlag Then
                'disable this dialog
                Me.Enabled = False

                'raise event to abort 
                RaiseEvent CreateBoltEvent(Me, False, Nothing)
            End If
        Catch ex As Exception
            System.Windows.Forms.MessageBox.Show(ex.Message, "PartFeaturesAddin", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Exclamation)
        End Try
    End Sub

    Private Sub txtX_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtX.TextChanged
        Try
            'check input string format and raise an event to update the preview graphics
            If TextboxFormatCheck(txtX, UnitsTypeEnum.kUnitlessUnits, Nothing) And Not bInvalid Then
                RaiseEvent PositionChangedEvent(Me, CType(txtX.Text, Double), CType(txtY.Text, Double), CType(txtZ.Text, Double))
            End If
        Catch : End Try
    End Sub

    Private Sub txtY_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtY.TextChanged
        Try
            'check input string format and raise an event to update the preview graphics
            If TextboxFormatCheck(txtY, UnitsTypeEnum.kUnitlessUnits, Nothing) And Not bInvalid Then
                RaiseEvent PositionChangedEvent(Me, CType(txtX.Text, Double), CType(txtY.Text, Double), CType(txtZ.Text, Double))
            End If
        Catch : End Try
    End Sub

    Private Sub txtZ_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtZ.TextChanged
        Try
            'check input string format and raise an event to update the preview graphics
            If TextboxFormatCheck(txtZ, UnitsTypeEnum.kUnitlessUnits, Nothing) And Not bInvalid Then
                RaiseEvent PositionChangedEvent(Me, CType(txtX.Text, Double), CType(txtY.Text, Double), CType(txtZ.Text, Double))
            End If
        Catch : End Try
    End Sub

    Private Sub txtDiameter1_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtDiameter1.TextChanged
        'test if the input string is in correct format
        Try
            TextboxFormatCheck(txtDiameter1, UnitsTypeEnum.kInchLengthUnits, New DelegateIfParameterValid(AddressOf Me.ifValidLength))
        Catch : End Try
    End Sub

    Private Sub txtDiameter2_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtDiameter2.TextChanged
        'test if the input string is in correct format
        Try
            TextboxFormatCheck(txtDiameter2, UnitsTypeEnum.kInchLengthUnits, New DelegateIfParameterValid(AddressOf Me.ifValidLength))
        Catch : End Try
    End Sub

    Private Sub txtHeight1_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtHeight1.TextChanged
        'test if the input string is in correct format
        Try
            TextboxFormatCheck(txtHeight1, UnitsTypeEnum.kInchLengthUnits, New DelegateIfParameterValid(AddressOf Me.ifValidLength))
        Catch : End Try
    End Sub

    Private Sub txtLength1_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtLength1.TextChanged
        'test if the input string is in correct format
        Try
            TextboxFormatCheck(txtLength1, UnitsTypeEnum.kInchLengthUnits, New DelegateIfParameterValid(AddressOf Me.ifValidLength))
        Catch : End Try
    End Sub

    Private Sub txtLength2_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtLength2.TextChanged
        'test if the input string is in correct format
        Try
            TextboxFormatCheck(txtLength2, UnitsTypeEnum.kInchLengthUnits, New DelegateIfParameterValid(AddressOf Me.ifValidLength))
        Catch : End Try
    End Sub

    Private Sub txtChamfer_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtChamfer.TextChanged
        'test if the input string is in correct format
        Try
            TextboxFormatCheck(txtChamfer, UnitsTypeEnum.kInchLengthUnits, New DelegateIfParameterValid(AddressOf Me.ifValidLength))
        Catch : End Try
    End Sub

    Private Sub txtFillet_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtFillet.TextChanged
        'test if the input string is in correct format
        Try
            TextboxFormatCheck(txtFillet, UnitsTypeEnum.kInchLengthUnits, New DelegateIfParameterValid(AddressOf Me.ifValidLength))
        Catch : End Try
    End Sub

    Private Sub txtAngle1_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtAngle1.TextChanged
        'test if the input string is in correct format
        Try
            TextboxFormatCheck(txtAngle1, UnitsTypeEnum.kDegreeAngleUnits, New DelegateIfParameterValid(AddressOf Me.ifValidCutAngle))
        Catch : End Try
    End Sub

    'check if the input parameter is in correct format
    Private Function TextboxFormatCheck(ByVal txtbox As System.Windows.Forms.TextBox, ByVal unit As UnitsTypeEnum, ByVal ifValid As DelegateIfParameterValid) As Boolean
        'get the UnitsOfMeasure object
        Try
            If Not oUOM Is Nothing Then

                'call CompatibleUnits method and ifValid function to determine if the input is valid
                If oUOM.CompatibleUnits(txtbox.Text, unit, "1", unit) Then
                    If Not ifValid Is Nothing Then
                        If Not ifValid(txtbox.Text, unit) Then Throw New Exception
                    End If

                    'restore the text color
                    txtbox.ForeColor = System.Windows.Forms.TextBox.DefaultForeColor

                    'if the format is previously incorrect then reduce the error count
                    If Not txtbox.Tag Is Nothing Then
                        iParameterErrors = iParameterErrors - 1
                        'enable the create button if there is no error or position has been specified
                        If iParameterErrors = 0 And Not oPosition Is Nothing Then
                            btCreate.Enabled = True
                        End If
                    End If

                    'mark this textbox as in a healthy state
                    txtbox.Tag = Nothing
                Else
                    Throw New Exception
                End If
            End If
        Catch
            'set text color to notify
            txtbox.ForeColor = Drawing.Color.Red

            'if the format is previously incorrect then reduce the error count
            If txtbox.Tag Is Nothing Then
                iParameterErrors = iParameterErrors + 1
            End If

            'mark this textbox as in an error state
            txtbox.Tag = "Error"

            'disable the create button
            btCreate.Enabled = False
            Return False
        End Try
        Return True
    End Function

    'set the location of bolt
    Public Sub SetPosition(ByVal pos As Point)
        Try
            bInvalid = True
            oPosition = pos
            txtX.Text = pos.X.ToString("F")
            txtY.Text = pos.Y.ToString("F")
            txtZ.Text = pos.Z.ToString("F")
        Catch
        Finally
            bInvalid = False
        End Try
    End Sub

    'check if input value is positive
    Private Function ifValidLength(ByVal input As String, ByVal unit As UnitsTypeEnum) As Boolean
        Try
            If oUOM.GetValueFromExpression(input, unit) >= 0 Then
                Return True
            Else
                Return False
            End If
        Catch
            Return False
        End Try
    End Function

    'check if input value is a valid angle for cutting [0-90)
    Private Function ifValidCutAngle(ByVal input As String, ByVal unit As UnitsTypeEnum) As Boolean
        Dim fCutAngle As Double

        Try
            fCutAngle = oUOM.GetValueFromExpression(input, unit)
            If fCutAngle >= 0 And fCutAngle < Math.PI / 2 Then
                Return True
            Else
                Return False
            End If
        Catch
            Return False
        End Try
    End Function

End Class
