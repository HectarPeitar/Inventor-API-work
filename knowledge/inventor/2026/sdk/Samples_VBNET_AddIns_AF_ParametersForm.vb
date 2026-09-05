Option Strict Off
Option Explicit On
Friend Class ParametersForm
    Inherits System.Windows.Forms.Form

    Private m_Doc As Inventor.AssemblyDocument
    Private m_UOM As Inventor.UnitsOfMeasure
    Private m_CurrentParamSetting As ParamSetting
    Private m_EditLine As Integer
    Private m_bSettingValues As Boolean
    Private m_ParamListForm As ParamListForm
    Private m_bIsInitializing As Boolean


    Private Sub cmdAddParam_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdAddParam.Click
        m_ParamListForm = New ParamListForm
        Call m_ParamListForm.Initialize(m_Doc.ComponentDefinition.Parameters)
        m_ParamListForm.ShowDialog()
        Dim i As Integer
        Dim oParam As Inventor.Parameter
        Dim oAttribSet As Inventor.AttributeSet
        For i = 0 To m_ParamListForm.lstParams.Items.Count - 1
            If m_ParamListForm.lstParams.GetSelected(i) Then
                ' Get the specified parameter.
                oParam = m_Doc.ComponentDefinition.Parameters(i + 1)

                ' Attempt to create the attribute set.
                On Error Resume Next
                oAttribSet = oParam.AttributeSets.Add("AnalyzeSample")
                If Err.Number = 0 Then
                    Call m_Analyses.ActiveCase.ParamSettings.Add(oParam, (oParam.Expression), (oParam.Expression))
                    Call oAttribSet.Add("StartValue", Inventor.ValueTypeEnum.kStringType, oParam.Expression)
                    Call oAttribSet.Add("EndValue", Inventor.ValueTypeEnum.kStringType, oParam.Expression)

                    lstParams.Items.Add(oParam.Name & ", (" & oParam.Expression & ", " & oParam.Expression & ")")
                End If
                On Error GoTo 0
            End If
        Next

        m_ParamListForm.Close()
    End Sub

    Private Sub cmdOK_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdOK.Click
        Dim oAttribSet As Inventor.AttributeSet
        On Error Resume Next
        oAttribSet = m_Doc.ComponentDefinition.AttributeSets.Item("AnalyzeSample")
        If Err.Number Then
            Err.Clear()
            oAttribSet = m_Doc.ComponentDefinition.AttributeSets.Add("AnalyzeSample")
            Call oAttribSet.Add("StepCount", Inventor.ValueTypeEnum.kIntegerType, Val(Me.txtSteps.Text))
        Else
            oAttribSet.Item("StepCount").Value = Me.txtSteps
        End If

        Me.Visible = False
    End Sub

    Private Sub ParametersForm_Load(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load
        m_Doc = m_InventorApp.ActiveDocument
        m_UOM = m_Doc.UnitsOfMeasure
        m_CurrentParamSetting = Nothing

        Dim oParamSetting As ParamSetting
        If m_Analyses.ActiveCase.ParamSettings.Count = 0 Then
            cmdAddParam_Click(cmdAddParam, New System.EventArgs())
        Else
            For Each oParamSetting In m_Analyses.ActiveCase.ParamSettings
                lstParams.Items.Add(oParamSetting.Parameter.Name & ", (" & oParamSetting.StartValue & ", " & oParamSetting.EndValue & ")")
            Next oParamSetting
        End If
    End Sub

    Private Sub ParametersForm_FormClosed(ByVal eventSender As System.Object, ByVal eventArgs As System.Windows.Forms.FormClosedEventArgs) Handles Me.FormClosed
        m_UOM = Nothing
        m_Doc = Nothing
    End Sub

    Private Sub lstParams_SelectedIndexChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles lstParams.SelectedIndexChanged
        If m_bIsInitializing = True Then
            Exit Sub
        Else
            Dim i As Integer
            For i = 0 To lstParams.Items.Count - 1
                If lstParams.GetSelected(i) Then
                    m_bSettingValues = True
                    txtStartValue.Text = m_Analyses.ActiveCase.ParamSettings(i + 1).StartValue
                    txtEndValue.Text = m_Analyses.ActiveCase.ParamSettings(i + 1).EndValue
                    m_bSettingValues = False
                    m_CurrentParamSetting = m_Analyses.ActiveCase.ParamSettings(i + 1)
                    m_EditLine = i
                    Exit For
                End If
            Next
        End If
    End Sub

    Private Sub txtEndValue_KeyPress(ByVal eventSender As System.Object, ByVal eventArgs As System.Windows.Forms.KeyPressEventArgs) Handles txtEndValue.KeyPress
        Dim KeyAscii As Short = Asc(eventArgs.KeyChar)
        If KeyAscii = 13 Then
            KeyAscii = 0
            txtEndValue_Leave(txtEndValue, New System.EventArgs())
            cmdOK.Focus()
        End If
        eventArgs.KeyChar = Chr(KeyAscii)
        If KeyAscii = 0 Then
            eventArgs.Handled = True
        End If
    End Sub

    Private Sub txtStartValue_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtStartValue.TextChanged
        If m_bIsInitializing = True Then
            Exit Sub
        Else
            Dim dValue As Double
            If Not m_bSettingValues Then
                If Not m_CurrentParamSetting Is Nothing Then
                    On Error Resume Next
                    dValue = m_UOM.GetValueFromExpression(txtStartValue.Text, m_CurrentParamSetting.Parameter.Units)
                    If Err.Number Then
                        txtStartValue.ForeColor = System.Drawing.ColorTranslator.FromOle(RGB(255, 0, 0))
                    Else
                        txtStartValue.ForeColor = System.Drawing.ColorTranslator.FromOle(RGB(0, 0, 0))
                        m_CurrentParamSetting.StartValue = txtStartValue.Text
                        lstParams.Items.Item(m_EditLine).Value = m_CurrentParamSetting.Parameter.Name & ", (" & m_CurrentParamSetting.StartValue & ", " & m_CurrentParamSetting.EndValue & ")"
                        m_CurrentParamSetting.Parameter.AttributeSets.Item("AnalyzeSample").Item("StartValue").Value = txtStartValue.Text
                    End If
                End If
            End If
        End If
    End Sub

    Private Sub txtStartValue_KeyPress(ByVal eventSender As System.Object, ByVal eventArgs As System.Windows.Forms.KeyPressEventArgs) Handles txtStartValue.KeyPress
        Dim KeyAscii As Short = Asc(eventArgs.KeyChar)
        If KeyAscii = 13 Then
            KeyAscii = 0
            txtEndValue_Leave(txtEndValue, New System.EventArgs())
            cmdOK.Focus()
        End If
        eventArgs.KeyChar = Chr(KeyAscii)
        If KeyAscii = 0 Then
            eventArgs.Handled = True
        End If
    End Sub

    Private Sub txtStartValue_Leave(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtStartValue.Leave
        Dim dValue As Double
        If Not m_CurrentParamSetting Is Nothing Then
            On Error Resume Next
            dValue = m_UOM.GetValueFromExpression(txtStartValue.Text, m_CurrentParamSetting.Parameter.Units)
            If Err.Number Then
                Exit Sub
            Else
                txtStartValue.Text = m_UOM.GetStringFromValue(dValue, m_CurrentParamSetting.Parameter.Units)
                m_CurrentParamSetting.StartValue = txtStartValue.Text
                lstParams.Items.Item(m_EditLine).Value = m_CurrentParamSetting.Parameter.Name & ", (" & m_CurrentParamSetting.StartValue & ", " & m_CurrentParamSetting.EndValue & ")"
                m_CurrentParamSetting.Parameter.AttributeSets.Item("AnalyzeSample").Item("StartValue").Value = txtStartValue.Text
            End If
        End If
    End Sub

    Private Sub txtEndValue_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtEndValue.TextChanged
        If m_bIsInitializing = True Then
            Exit Sub
        Else
            Dim dValue As Double
            If Not m_bSettingValues Then
                If Not m_CurrentParamSetting Is Nothing Then
                    On Error Resume Next
                    dValue = m_UOM.GetValueFromExpression(txtEndValue.Text, m_CurrentParamSetting.Parameter.Units)
                    If Err.Number Then
                        txtEndValue.ForeColor = System.Drawing.ColorTranslator.FromOle(RGB(255, 0, 0))
                    Else
                        txtEndValue.ForeColor = System.Drawing.ColorTranslator.FromOle(RGB(0, 0, 0))
                        m_CurrentParamSetting.EndValue = txtEndValue.Text
                        lstParams.Items.Item(m_EditLine).Value = m_CurrentParamSetting.Parameter.Name & ", (" & m_CurrentParamSetting.StartValue & ", " & m_CurrentParamSetting.EndValue & ")"
                        m_CurrentParamSetting.Parameter.AttributeSets.Item("AnalyzeSample").Item("EndValue").Value = txtEndValue.Text
                    End If
                End If
            End If
        End If
    End Sub

    Private Sub txtEndValue_Leave(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtEndValue.Leave
        Dim dValue As Double
        If Not m_CurrentParamSetting Is Nothing Then
            On Error Resume Next
            dValue = m_UOM.GetValueFromExpression(txtEndValue.Text, m_CurrentParamSetting.Parameter.Units)
            If Err.Number Then
                Exit Sub
            Else
                txtEndValue.Text = m_UOM.GetStringFromValue(dValue, m_CurrentParamSetting.Parameter.Units)
                m_CurrentParamSetting.EndValue = txtEndValue.Text
                lstParams.Items.Item(m_EditLine).Value = m_CurrentParamSetting.Parameter.Name & ", (" & m_CurrentParamSetting.StartValue & ", " & m_CurrentParamSetting.EndValue & ")"
                m_CurrentParamSetting.Parameter.AttributeSets.Item("AnalyzeSample").Item("EndValue").Value = txtEndValue.Text
            End If
        End If
    End Sub
End Class