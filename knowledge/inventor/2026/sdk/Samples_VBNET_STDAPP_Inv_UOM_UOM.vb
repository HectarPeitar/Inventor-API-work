Option Strict Off
Option Explicit On
Imports System.Runtime.InteropServices
Imports VB = Microsoft.VisualBasic
Friend Class frmUOM
    Inherits System.Windows.Forms.Form

    Private oUOM As Inventor.UnitsOfMeasure
    Private UnitType As Inventor.UnitsTypeEnum
    Private InputValue As Double
    Private InputUnit, OutputUnit As String

    'UPGRADE_WARNING: Event cboAnglePrecision.SelectedIndexChanged may fire when form is initialized. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="88B12AE1-6DE0-48A0-86F1-60C0686C026A"'
    Private Sub cboAnglePrecision_SelectedIndexChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cboAnglePrecision.SelectedIndexChanged
        ' Set the current angle precision.
        oUOM.AngleDisplayPrecision = Val(cboAnglePrecision.Text)

        ' Update the information on the form.
        txtInput_TextChanged(txtInput, New System.EventArgs())
        txtOutputEntry_TextChanged(txtOutputEntry, New System.EventArgs())
    End Sub

    'UPGRADE_WARNING: Event cboAngleUnits.SelectedIndexChanged may fire when form is initialized. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="88B12AE1-6DE0-48A0-86F1-60C0686C026A"'
    Private Sub cboAngleUnits_SelectedIndexChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cboAngleUnits.SelectedIndexChanged
        ' Set the angle unit.
        Select Case cboAngleUnits.Text
            Case "Degree"
                oUOM.AngleUnits = Inventor.UnitsTypeEnum.kDegreeAngleUnits
            Case "Radian"
                oUOM.AngleUnits = Inventor.UnitsTypeEnum.kRadianAngleUnits
        End Select

        ' Update the information on the form.
        txtInput_TextChanged(txtInput, New System.EventArgs())
        txtOutputEntry_TextChanged(txtOutputEntry, New System.EventArgs())
    End Sub

    'UPGRADE_WARNING: Event cboMassUnits.SelectedIndexChanged may fire when form is initialized. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="88B12AE1-6DE0-48A0-86F1-60C0686C026A"'
    Private Sub cboMassUnits_SelectedIndexChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cboMassUnits.SelectedIndexChanged
        ' Set the mass unit.
        Select Case cboMassUnits.Text
            Case "lbMass"
                oUOM.MassUnits = Inventor.UnitsTypeEnum.kLbMassMassUnits
            Case "Slug"
                oUOM.MassUnits = Inventor.UnitsTypeEnum.kSlugMassUnits
            Case "Gram"
                oUOM.MassUnits = Inventor.UnitsTypeEnum.kGramMassUnits
            Case "Kilogram"
                oUOM.MassUnits = Inventor.UnitsTypeEnum.kKilogramMassUnits
        End Select

        ' Update the information on the form.
        txtInput_TextChanged(txtInput, New System.EventArgs())
        txtOutputEntry_TextChanged(txtOutputEntry, New System.EventArgs())
    End Sub

    'UPGRADE_WARNING: Event cboTimeUnits.SelectedIndexChanged may fire when form is initialized. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="88B12AE1-6DE0-48A0-86F1-60C0686C026A"'
    Private Sub cboTimeUnits_SelectedIndexChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cboTimeUnits.SelectedIndexChanged
        ' Set the time unit.
        Select Case cboTimeUnits.Text
            Case "Second"
                oUOM.TimeUnits = Inventor.UnitsTypeEnum.kSecondTimeUnits
            Case "Minute"
                oUOM.TimeUnits = Inventor.UnitsTypeEnum.kMinuteTimeUnits
        End Select

        ' Update the information on the form.
        txtInput_TextChanged(txtInput, New System.EventArgs())
        txtOutputEntry_TextChanged(txtOutputEntry, New System.EventArgs())
    End Sub

    'UPGRADE_WARNING: Event cboUnitType.SelectedIndexChanged may fire when form is initialized. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="88B12AE1-6DE0-48A0-86F1-60C0686C026A"'
    Private Sub cboUnitType_SelectedIndexChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cboUnitType.SelectedIndexChanged
        ' Set the glogbal variable to contain the current unit type and
        ' configure the dialog to display information for the selected unit type.
        Select Case cboUnitType.Text
            Case "Length"
                UnitType = Inventor.UnitsTypeEnum.kDefaultDisplayLengthUnits
                lblResultType.Text = "cm"
                lblInputType.Text = "Internal double value in cm:"
            Case "Angle"
                UnitType = Inventor.UnitsTypeEnum.kDefaultDisplayAngleUnits
                lblResultType.Text = "radians"
                lblInputType.Text = "Internal double value in radians:"
            Case "Mass"
                UnitType = Inventor.UnitsTypeEnum.kDefaultDisplayMassUnits
                lblResultType.Text = "kilograms"
                lblInputType.Text = "Internal double value in kilograms:"
            Case "Time"
                UnitType = Inventor.UnitsTypeEnum.kDefaultDisplayTimeUnits
                lblResultType.Text = "seconds"
                lblInputType.Text = "Internal double value in seconds:"
        End Select

        ' Update the information on the form.
        txtInput_TextChanged(txtInput, New System.EventArgs())
        txtOutputEntry_TextChanged(txtOutputEntry, New System.EventArgs())
    End Sub

    Private Sub frmUOM_Load(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load
        ' Get a reference to a running instance of Inventor.
        On Error Resume Next
        Dim oInventorApp As Inventor.Application
        oInventorApp = Win32.GetActiveObject("Inventor.Application")

        If Err.Number Then
            MsgBox("Please open an Inventor session, then run the sample")
            Me.Close()
            Exit Sub
        End If

        If oInventorApp.Documents.Count = 0 Then
            ' Fix defect 1028511- Get the UnitsOfMeasure from Application when no Inv doc.
            oUOM = oInventorApp.UnitsOfMeasure

            ' Fix defect 1028511- Disable the "User Interaction" frame, "Unit Settings"
            ' frame and all combo boxes, text boxes, labels under them when no Inv doc.
            Frame1.Enabled = False
            cboUnitType.Enabled = False : lblInputType.Enabled = False
            Label2.Enabled = False : Label3.Enabled = False : Label4.Enabled = False
            Label14.Enabled = False : txtInput.Enabled = False : txtResult.Enabled = False
            lblResultType.Enabled = False : txtOutputEntry.Enabled = False : txtOutputDisplay.Enabled = False

            Frame2.Enabled = False
            Label6.Enabled = False : Label7.Enabled = False : Label8.Enabled = False
            Label10.Enabled = False : Label11.Enabled = False : Label12.Enabled = False
            cboLengthUnits.Enabled = False : cboLengthPrecision.Enabled = False
            cboMassUnits.Enabled = False : cboAngleUnits.Enabled = False
            cboAnglePrecision.Enabled = False : cboTimeUnits.Enabled = False
        Else
            ' Get UnitsOfMeasure object from the first document.
            oUOM = oInventorApp.ActiveDocument.UnitsOfMeasure
        End If

        ' Create the unit selection list in the combo box.
        cboUnitType.Items.Add("Length")
        cboUnitType.Items.Add("Angle")
        cboUnitType.Items.Add("Mass")
        cboUnitType.Items.Add("Time")

        ' Set "Length" as the default item.
        cboUnitType.SelectedIndex = 0

        ' Create the list used to select the current length unit.
        cboLengthUnits.Items.Add("Inch")
        cboLengthUnits.Items.Add("Foot")
        cboLengthUnits.Items.Add("Centimeter")
        cboLengthUnits.Items.Add("Millimeter")
        cboLengthUnits.Items.Add("Meter")
        cboLengthUnits.Items.Add("Micron")

        ' Set the current unit in the combo box.
        Select Case oUOM.LengthUnits
            Case Inventor.UnitsTypeEnum.kInchLengthUnits
                cboLengthUnits.SelectedIndex = 0
            Case Inventor.UnitsTypeEnum.kFootLengthUnits
                cboLengthUnits.SelectedIndex = 1
            Case Inventor.UnitsTypeEnum.kCentimeterLengthUnits
                cboLengthUnits.SelectedIndex = 2
            Case Inventor.UnitsTypeEnum.kMillimeterLengthUnits
                cboLengthUnits.SelectedIndex = 3
            Case Inventor.UnitsTypeEnum.kMeterLengthUnits
                cboLengthUnits.SelectedIndex = 4
            Case Inventor.UnitsTypeEnum.kMicronLengthUnits
                cboLengthUnits.SelectedIndex = 5
        End Select

        ' Create the list used to select the current angle unit.
        cboAngleUnits.Items.Add("Degree")
        cboAngleUnits.Items.Add("Radian")

        ' Set the current unit in the combo box.
        Select Case oUOM.AngleUnits
            Case Inventor.UnitsTypeEnum.kDegreeAngleUnits
                cboAngleUnits.SelectedIndex = 0
            Case Inventor.UnitsTypeEnum.kRadianAngleUnits
                cboAngleUnits.SelectedIndex = 1
        End Select

        ' Create the list used to select the current time unit.
        cboTimeUnits.Items.Add("Second")
        cboTimeUnits.Items.Add("Minute")

        ' Set the current unit in the combo box.
        Select Case oUOM.TimeUnits
            Case Inventor.UnitsTypeEnum.kSecondTimeUnits
                cboTimeUnits.SelectedIndex = 0
            Case Inventor.UnitsTypeEnum.kMinuteTimeUnits
                cboTimeUnits.SelectedIndex = 1
        End Select

        ' Create the list used to select the current mass unit.
        cboMassUnits.Items.Add("lbMass")
        cboMassUnits.Items.Add("Slug")
        cboMassUnits.Items.Add("Gram")
        cboMassUnits.Items.Add("Kilogram")

        ' Set the current unit in the combo box.
        Select Case oUOM.MassUnits
            Case Inventor.UnitsTypeEnum.kLbMassMassUnits
                cboMassUnits.SelectedIndex = 0
            Case Inventor.UnitsTypeEnum.kSlugMassUnits
                cboMassUnits.SelectedIndex = 1
            Case Inventor.UnitsTypeEnum.kGramMassUnits
                cboMassUnits.SelectedIndex = 1
            Case Inventor.UnitsTypeEnum.kKilogramMassUnits
                cboMassUnits.SelectedIndex = 1
        End Select

        ' Create the list used to select the length display precision.
        cboLengthPrecision.Items.Add("0")
        cboLengthPrecision.Items.Add("1")
        cboLengthPrecision.Items.Add("2")
        cboLengthPrecision.Items.Add("3")
        cboLengthPrecision.Items.Add("4")
        cboLengthPrecision.Items.Add("5")

        ' Set the list to display the current value.
        cboLengthPrecision.SelectedIndex = oUOM.LengthDisplayPrecision

        ' Create the list used to select the angle display precision.
        cboAnglePrecision.Items.Add("0")
        cboAnglePrecision.Items.Add("1")
        cboAnglePrecision.Items.Add("2")
        cboAnglePrecision.Items.Add("3")
        cboAnglePrecision.Items.Add("4")
        cboAnglePrecision.Items.Add("5")

        ' Set the list to display the current value.
        cboAnglePrecision.SelectedIndex = oUOM.AngleDisplayPrecision
    End Sub

    'UPGRADE_WARNING: Event txtInput.TextChanged may fire when form is initialized. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="88B12AE1-6DE0-48A0-86F1-60C0686C026A"'
    Private Sub txtInput_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtInput.TextChanged
        Dim ExpressionValue As Double

        ' Get the value of the input string, checking to make sure it is valid.
        On Error Resume Next
        'UPGRADE_WARNING: Couldn't resolve default property of object oUOM.GetValueFromExpression(). Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
        ExpressionValue = oUOM.GetValueFromExpression(txtInput.Text, UnitType)
        If Err.Number Then
            ' Invalid string was input, so change the color of the text to red.
            Err.Clear()
            txtInput.ForeColor = System.Drawing.ColorTranslator.FromOle(RGB(255, 0, 0))

            ' Clear the result.
            txtResult.Text = ""
        Else
            ' Change the color back to the default and display the result.
            txtInput.ForeColor = System.Drawing.SystemColors.WindowText
            txtResult.Text = VB.Format(ExpressionValue, "0.0000000")
        End If
    End Sub

    'UPGRADE_WARNING: Event txtOutputEntry.TextChanged may fire when form is initialized. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="88B12AE1-6DE0-48A0-86F1-60C0686C026A"'
    Private Sub txtOutputEntry_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtOutputEntry.TextChanged

        ' Display the corresonding string the value entered in the dialog.
        On Error Resume Next
        Dim dValue As Double : dValue = CDbl(txtOutputEntry.Text)

        If Err.Number Then
            ' Fix defect 1028493- Check input whether is value, show it
            ' with red color and clear the output if it's not.
            txtOutputEntry.ForeColor = System.Drawing.ColorTranslator.FromOle(RGB(255, 0, 0))
            txtOutputDisplay.Text = ""
        Else
            txtOutputDisplay.Text = oUOM.GetStringFromValue(dValue, UnitType)
            ' Set the color to the default.
            txtOutputEntry.ForeColor = System.Drawing.SystemColors.WindowText
        End If

    End Sub

    'UPGRADE_WARNING: Event cboLengthPrecision.SelectedIndexChanged may fire when form is initialized. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="88B12AE1-6DE0-48A0-86F1-60C0686C026A"'
    Private Sub cboLengthPrecision_SelectedIndexChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cboLengthPrecision.SelectedIndexChanged
        ' Set the precision for length.
        oUOM.LengthDisplayPrecision = Val(cboLengthPrecision.Text)

        ' Update the information on the form.
        txtInput_TextChanged(txtInput, New System.EventArgs())
        txtOutputEntry_TextChanged(txtOutputEntry, New System.EventArgs())
    End Sub

    'UPGRADE_WARNING: Event cboLengthUnits.SelectedIndexChanged may fire when form is initialized. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="88B12AE1-6DE0-48A0-86F1-60C0686C026A"'
    Private Sub cboLengthUnits_SelectedIndexChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cboLengthUnits.SelectedIndexChanged
        ' Set the document length units.
        Select Case cboLengthUnits.Text
            Case "Inch"
                oUOM.LengthUnits = Inventor.UnitsTypeEnum.kInchLengthUnits
            Case "Foot"
                oUOM.LengthUnits = Inventor.UnitsTypeEnum.kFootLengthUnits
            Case "Centimeter"
                oUOM.LengthUnits = Inventor.UnitsTypeEnum.kCentimeterLengthUnits
            Case "Millimeter"
                oUOM.LengthUnits = Inventor.UnitsTypeEnum.kMillimeterLengthUnits
            Case "Meter"
                oUOM.LengthUnits = Inventor.UnitsTypeEnum.kMeterLengthUnits
            Case "Micron"
                oUOM.LengthUnits = Inventor.UnitsTypeEnum.kMicronLengthUnits
        End Select

        ' Update the information on the form.
        txtInput_TextChanged(txtInput, New System.EventArgs())
        txtOutputEntry_TextChanged(txtOutputEntry, New System.EventArgs())
    End Sub

    ' Fix defect 108511- Using below four subroutines to implement converting
    ' units between two compatible units of all types.
    'UPGRADE_WARNING: Event txtInputUnit.TextChanged may fire when form is initialized. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="88B12AE1-6DE0-48A0-86F1-60C0686C026A"'
    Private Sub txtInputUnit_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtInputUnit.TextChanged
        InputUnit = txtInputUnit.Text

        ' Get the input string, checking to make sure it is valid unit.
        On Error Resume Next
        Call oUOM.GetDatabaseUnitsFromExpression("1", InputUnit)

        Dim IsCompatible As Boolean
        Dim ResultValue As Double
        If Err.Number Then
            Call ShowRedForErr(txtInputUnit)
        Else
            txtInputUnit.ForeColor = System.Drawing.SystemColors.WindowText

            'UPGRADE_WARNING: IsEmpty was upgraded to IsNothing and has a new behavior. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="9B7D5ADD-D8FE-4819-A36C-6DEDAF088CC7"'
            If InputValue <> 0 And Not IsNothing(OutputUnit) Then
                IsCompatible = oUOM.CompatibleUnits("1", InputUnit, "1", OutputUnit)

                If IsCompatible Then
                    ' Change the color back to the default and display the result.
                    txtOutputUnit.ForeColor = System.Drawing.SystemColors.WindowText
                    ResultValue = oUOM.ConvertUnits(InputValue, InputUnit, OutputUnit)
                    txtResultValue.Text = VB.Format(ResultValue, "0.0000000")
                Else : Call ShowRedForErr(txtOutputUnit)
                End If
            End If
        End If
    End Sub

    'UPGRADE_WARNING: Event txtInputValue.TextChanged may fire when form is initialized. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="88B12AE1-6DE0-48A0-86F1-60C0686C026A"'
    Private Sub txtInputValue_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtInputValue.TextChanged
        ' Get the input value, checking to make sure it is valid.
        On Error Resume Next
        InputValue = CObj(txtInputValue.Text)

        Dim ResultValue As Double
        If Err.Number Then
            Call ShowRedForErr(txtInputValue)
        Else
            ' Change the color back to the default and display the result.
            txtInputValue.ForeColor = System.Drawing.SystemColors.WindowText
            'UPGRADE_WARNING: IsEmpty was upgraded to IsNothing and has a new behavior. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="9B7D5ADD-D8FE-4819-A36C-6DEDAF088CC7"'
            If Not IsNothing(InputUnit) And Not IsNothing(OutputUnit) Then
                ResultValue = oUOM.ConvertUnits(InputValue, InputUnit, OutputUnit)
                txtResultValue.Text = VB.Format(ResultValue, "0.0000000")
            End If
        End If
    End Sub

    'UPGRADE_WARNING: Event txtOutputUnit.TextChanged may fire when form is initialized. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="88B12AE1-6DE0-48A0-86F1-60C0686C026A"'
    Private Sub txtOutputUnit_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtOutputUnit.TextChanged
        OutputUnit = txtOutputUnit.Text

        ' Get the input string, checking to make sure it is valid unit.
        On Error Resume Next
        Call oUOM.GetDatabaseUnitsFromExpression("1", OutputUnit)

        Dim IsCompatible As Boolean
        Dim ResultValue As Double
        If Err.Number Then
            Call ShowRedForErr(txtOutputUnit)
        Else
            IsCompatible = oUOM.CompatibleUnits("1", InputUnit, "1", OutputUnit)

            If Not IsCompatible Then
                Call ShowRedForErr(txtOutputUnit)
            Else
                ' Change the color back to the default and display the result.
                txtOutputUnit.ForeColor = System.Drawing.SystemColors.WindowText
                ResultValue = oUOM.ConvertUnits(InputValue, InputUnit, OutputUnit)
                txtResultValue.Text = VB.Format(ResultValue, "0.0000000")
            End If
        End If
    End Sub

    Private Sub ShowRedForErr(ByRef txtBox As System.Windows.Forms.TextBox)
        ' Invalid input, so change the color of the text to red.
        Err.Clear()
        txtBox.ForeColor = System.Drawing.ColorTranslator.FromOle(RGB(255, 0, 0))

        ' Clear the result.
        txtResultValue.Text = ""
    End Sub
End Class

Public Class Win32
    <DllImport("ole32")>
    Private Shared Function CLSIDFromProgIDEx(
        <MarshalAs(UnmanagedType.LPWStr)> ByVal lpszProgID As String, <Out> ByRef lpclsid As Guid) As Integer
    End Function
    <DllImport("ole32")>
    Private Shared Function CLSIDFromProgID(
        <MarshalAs(UnmanagedType.LPWStr)> ByVal lpszProgID As String, <Out> ByRef lpclsid As Guid) As Integer
    End Function
    <DllImport("oleaut32")>
    Private Shared Function GetActiveObject(
        <MarshalAs(UnmanagedType.LPStruct)> ByVal rclsid As Guid, ByVal pvReserved As IntPtr, <Out>
        <MarshalAs(UnmanagedType.IUnknown)> ByRef ppunk As Object) As Integer
    End Function

    Public Shared Function GetActiveObject(ByVal progID As String) As Object
        Dim obj As Object = Nothing
        Dim clsid As Guid

        ' Call CLSIDFromProgIDEx first then fall back on CLSIDFromProgID if
        ' CLSIDFromProgIDEx doesn't exist.
        Try
            CLSIDFromProgIDEx(progID, clsid)
        Catch ex As Exception
            CLSIDFromProgID(progID, clsid)
        End Try

        Dim hr = GetActiveObject(clsid, IntPtr.Zero, obj)
        If hr < 0 Then
            Err.Raise(0)
        End If
        Return obj
    End Function
End Class