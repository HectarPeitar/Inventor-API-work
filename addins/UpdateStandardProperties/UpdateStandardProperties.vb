' Rule: UpdateStandardProperties
' Description: Standardize and validate key iProperties of a Part before release.
'   Uses User Parameters PartNumber and Description where available, while
'   preserving existing valid iProperty values. Reports Material from the
'   document and flags missing Designer values.
'
' Status: GENERATED (with DebugMode)
' Inventor version: 2026
' DebugMode: When True, writes report to scratch\UpdateStandardProperties-Output.txt
'   Set to False after verification to disable text file output.
'
' Design decisions (based on verified knowledge from the workspace):
' - Part-only via Try/Catch on ComponentDefinition cast.
'   (iLogic does not expose DocumentTypeEnum.)
    ' - iProperty read/write via doc.PropertySets.Item('PropertySetName').Item('PropertyName').Value
' - Parameter lookup via iteration of compDef.Parameters and name comparison.
' - Document material read from compDef.Material.Name for the Material check.
' - Read-only/locked parameter detection via Try/Catch on Expression read.
' - Final MessageBox with changed, preserved, missing, errors, and status.
'
' Expected: Active Part document (.ipt).

Sub Main
    ' --- Initialize tracking collections ---
    Dim docName As String = "(no active document)"
    Dim changedProps As New List(Of String)
    Dim preservedProps As New List(Of String)
    Dim missingValues As New List(Of String)
    Dim errorMessages As New List(Of String)
    Dim ruleStatus As String = "PASS"

    ' --- Debug mode: writes report to text file for testing ---
    Const DebugMode As Boolean = False
    Const DebugOutputFile As String = "C:\Users\ricog\3D Modeling\Inventor API work\scratch\UpdateStandardProperties-Output.txt"

    ' --- 1. Get active document and confirm Part context ---
    Dim doc As Document = ThisApplication.ActiveDocument
    If doc Is Nothing Then
        MessageBox.Show( _
            "No active document found." & vbLf & _
            "Open a Part document (.ipt) and run the rule again.", _
            "UpdateStandardProperties - Error")
        Return
    End If
    docName = doc.DisplayName

    ' iLogic does not expose DocumentTypeEnum; detect Part via cast.
    Dim compDef As PartComponentDefinition = Nothing
    Dim earlyExit As Boolean = False
    Try
        compDef = CType(doc.ComponentDefinition, PartComponentDefinition)
    Catch ex As Exception
        errorMessages.Add("This document is not a Part document (.ipt).")
        ruleStatus = "FAIL"
        earlyExit = True
    End Try
    If earlyExit Then GoTo ReportSection
    If compDef Is Nothing Then
        errorMessages.Add("ComponentDefinition could not be interpreted as PartComponentDefinition.")
        ruleStatus = "FAIL"
        GoTo ReportSection
    End If

    Dim params As Parameters = compDef.Parameters
    Dim currentPartNumber As String = ""
    Dim currentDescription As String = ""
    Dim currentMaterial As String = ""
    Dim currentDesigner As String = ""

    Try
        currentPartNumber = "" & doc.PropertySets.Item("Design Tracking Properties").Item("Part Number").Value
    Catch ex As Exception
        errorMessages.Add("Could not read Part Number iProperty: " & ex.Message)
    End Try

    Try
        currentDescription = "" & doc.PropertySets.Item("Design Tracking Properties").Item("Description").Value
    Catch ex As Exception
        errorMessages.Add("Could not read Description iProperty: " & ex.Message)
    End Try

    Try
        currentMaterial = compDef.Material.Name
    Catch ex As Exception
        errorMessages.Add("Could not read Material iProperty: " & ex.Message)
    End Try

    Try
        currentDesigner = "" & doc.PropertySets.Item("Design Tracking Properties").Item("Designer").Value
    Catch ex As Exception
        errorMessages.Add("Could not read Designer iProperty: " & ex.Message)
    End Try

    ' --- 3. Find User Parameters ---
    Dim partNumberParam As Parameter = Nothing
    Dim descriptionParam As Parameter = Nothing

    For Each p As Parameter In params
        If p.Name = "PartNumber" Then
            partNumberParam = p
        ElseIf p.Name = "Description" Then
            descriptionParam = p
        End If
    Next

    ' --- 4. Apply Part Number logic ---
    If partNumberParam IsNot Nothing Then
        Dim paramValue As String = ""
        Try
            paramValue = partNumberParam.Expression.Trim()
            ' Text parameters return their value wrapped in quotes; strip them.
            If paramValue.StartsWith("""") AndAlso paramValue.EndsWith("""") AndAlso paramValue.Length >= 2 Then
                paramValue = paramValue.Substring(1, paramValue.Length - 2)
            End If
        Catch ex As Exception
            errorMessages.Add("Could not read PartNumber parameter expression: " & ex.Message)
        End Try

        If Not String.IsNullOrEmpty(paramValue) Then
            If Not String.Equals(currentPartNumber, paramValue, StringComparison.OrdinalIgnoreCase) Then
                Try
                    doc.PropertySets.Item("Design Tracking Properties").Item("Part Number").Value = paramValue
                    changedProps.Add("Part Number -> " & paramValue)
                Catch ex As Exception
                    errorMessages.Add("Could not set Part Number iProperty: " & ex.Message)
                    ruleStatus = "FAIL"
                End Try
            Else
                preservedProps.Add("Part Number = " & currentPartNumber)
            End If
        ElseIf Not String.IsNullOrEmpty(currentPartNumber) Then
            preservedProps.Add("Part Number = " & currentPartNumber)
        Else
            missingValues.Add("Part Number")
        End If
    ElseIf Not String.IsNullOrEmpty(currentPartNumber) Then
        preservedProps.Add("Part Number = " & currentPartNumber)
    Else
        missingValues.Add("Part Number")
    End If

    ' --- 5. Apply Description logic ---
    If descriptionParam IsNot Nothing Then
        Dim descParamValue As String = ""
        Try
            descParamValue = descriptionParam.Expression.Trim()
            ' Text parameters return their value wrapped in quotes; strip them.
            If descParamValue.StartsWith("""") AndAlso descParamValue.EndsWith("""") AndAlso descParamValue.Length >= 2 Then
                descParamValue = descParamValue.Substring(1, descParamValue.Length - 2)
            End If
        Catch ex As Exception
            errorMessages.Add("Could not read Description parameter expression: " & ex.Message)
        End Try

        If Not String.IsNullOrEmpty(descParamValue) Then
            If Not String.Equals(currentDescription, descParamValue, StringComparison.OrdinalIgnoreCase) Then
                Try
                    doc.PropertySets.Item("Design Tracking Properties").Item("Description").Value = descParamValue
                    changedProps.Add("Description -> " & descParamValue)
                Catch ex As Exception
                    errorMessages.Add("Could not set Description iProperty: " & ex.Message)
                    ruleStatus = "FAIL"
                End Try
            Else
                preservedProps.Add("Description = " & currentDescription)
            End If
        ElseIf Not String.IsNullOrEmpty(currentDescription) Then
            preservedProps.Add("Description = " & currentDescription)
        Else
            missingValues.Add("Description")
        End If
    ElseIf Not String.IsNullOrEmpty(currentDescription) Then
        preservedProps.Add("Description = " & currentDescription)
    Else
        missingValues.Add("Description")
    End If

    ' --- 6. Apply Material logic ---
    Dim documentMaterial As String = ""
    Try
        If compDef.Material IsNot Nothing Then
            documentMaterial = compDef.Material.Name
        End If
    Catch ex As Exception
        errorMessages.Add("Could not read document material: " & ex.Message)
    End Try

    If String.IsNullOrEmpty(currentMaterial) AndAlso Not String.IsNullOrEmpty(documentMaterial) Then
        Try
            Dim targetMaterial As Material = Nothing
            For Each mat As Material In doc.Materials
                If mat.Name = documentMaterial Then
                    targetMaterial = mat
                    Exit For
                End If
            Next
            If targetMaterial IsNot Nothing Then
                compDef.Material = targetMaterial
                changedProps.Add("Material -> " & documentMaterial)
            End If
        Catch ex As Exception
            errorMessages.Add("Could not set Material: " & ex.Message)
            ruleStatus = "FAIL"
        End Try
    ElseIf Not String.IsNullOrEmpty(currentMaterial) Then
        preservedProps.Add("Material = " & currentMaterial)
    Else
        missingValues.Add("Material")
    End If

    ' --- 7. Apply Designer logic ---
    If Not String.IsNullOrEmpty(currentDesigner) Then
        preservedProps.Add("Designer = " & currentDesigner)
    Else
        missingValues.Add("Designer")
    End If

    ' --- 8. Re-read affected iProperties and verify ---
    For Each changedItem In changedProps
        Dim arrowIndex As Integer = changedItem.IndexOf("->")
        If arrowIndex > 0 Then
            Dim propName As String = changedItem.Substring(0, arrowIndex).Trim()
            Dim expectedValue As String = changedItem.Substring(arrowIndex + 2).Trim()
            Dim actualValue As String = ""
            Try
                If propName = "Material" Then
                    actualValue = compDef.Material.Name
                Else
                    Dim verifyPropSetName As String = ""
                    Select Case propName
                        Case "Part Number", "Description", "Designer"
                            verifyPropSetName = "Design Tracking Properties"
                        Case Else
                            verifyPropSetName = "Design Tracking Properties"
                    End Select
                    actualValue = "" & doc.PropertySets.Item(verifyPropSetName).Item(propName).Value
                End If
                If Not String.Equals(actualValue, expectedValue, StringComparison.OrdinalIgnoreCase) Then
                    errorMessages.Add("Verification failed for " & propName & ": expected '" & expectedValue & "', got '" & actualValue & "'")
                    ruleStatus = "FAIL"
                End If
            Catch ex As Exception
                errorMessages.Add("Could not verify " & propName & " iProperty: " & ex.Message)
                ruleStatus = "FAIL"
            End Try
        End If
    Next

    For Each preservedItem In preservedProps
        Dim eqIndex As Integer = preservedItem.IndexOf("=")
        If eqIndex > 0 Then
            Dim propName As String = preservedItem.Substring(0, eqIndex).Trim()
            Dim expectedValue As String = preservedItem.Substring(eqIndex + 1).Trim()
            Dim actualValue As String = ""
            Try
                If propName = "Material" Then
                    actualValue = compDef.Material.Name
                Else
                    Dim verifyPropSetName2 As String = ""
                    Select Case propName
                        Case "Part Number", "Description", "Designer"
                            verifyPropSetName2 = "Design Tracking Properties"
                        Case Else
                            verifyPropSetName2 = "Design Tracking Properties"
                    End Select
                    actualValue = "" & doc.PropertySets.Item(verifyPropSetName2).Item(propName).Value
                End If
                If Not String.Equals(actualValue, expectedValue, StringComparison.OrdinalIgnoreCase) Then
                    errorMessages.Add("Preserved value changed for " & propName & ": expected '" & expectedValue & "', got '" & actualValue & "'")
                    If ruleStatus <> "FAIL" Then ruleStatus = "WARNING"
                End If
            Catch ex As Exception
                errorMessages.Add("Could not verify preserved " & propName & " iProperty: " & ex.Message)
            End Try
        End If
    Next

    If changedProps.Count > 0 Then
        Try
            doc.Update()
        Catch ex As Exception
            errorMessages.Add("Model update failed: " & ex.Message)
            If ruleStatus <> "FAIL" Then ruleStatus = "WARNING"
        End Try
    End If

    ' --- 10. Determine final status ---
    ' WARNING when Designer is missing (non-critical) and no errors occurred.
    If ruleStatus = "PASS" AndAlso missingValues.Contains("Designer") Then
        ruleStatus = "WARNING"
    End If
    ' WARNING when important values are missing but no hard errors occurred.
    If ruleStatus = "PASS" AndAlso (missingValues.Contains("Part Number") OrElse missingValues.Contains("Description") OrElse missingValues.Contains("Material")) Then
        ruleStatus = "WARNING"
    End If

    ' --- 11. Show final report ---
ReportSection:
    Dim report As New System.Text.StringBuilder()
    report.AppendLine("UpdateStandardProperties - Report")
    report.AppendLine("Document: " & docName)
    report.AppendLine("Status:   " & ruleStatus)
    report.AppendLine("")
    report.AppendLine("--- iProperty Values ---")
    report.AppendLine("Part Number: " & If(String.IsNullOrEmpty(currentPartNumber), "(empty)", currentPartNumber))
    report.AppendLine("Description: " & If(String.IsNullOrEmpty(currentDescription), "(empty)", currentDescription))
    report.AppendLine("Material:    " & If(String.IsNullOrEmpty(currentMaterial), "(empty)", currentMaterial))
    report.AppendLine("Designer:    " & If(String.IsNullOrEmpty(currentDesigner), "(empty)", currentDesigner))
    report.AppendLine("")
    report.AppendLine("Changed (" & changedProps.Count & "):")
    If changedProps.Count = 0 Then
        report.AppendLine("  (none)")
    Else
        For Each s In changedProps
            report.AppendLine("  - " & s)
        Next
    End If
    report.AppendLine("")
    report.AppendLine("Preserved (" & preservedProps.Count & "):")
    If preservedProps.Count = 0 Then
        report.AppendLine("  (none)")
    Else
        For Each s In preservedProps
            report.AppendLine("  - " & s)
        Next
    End If
    report.AppendLine("")
    report.AppendLine("Missing (" & missingValues.Count & "):")
    If missingValues.Count = 0 Then
        report.AppendLine("  (none)")
    Else
        For Each s In missingValues
            report.AppendLine("  - " & s)
        Next
    End If
    report.AppendLine("")
    If errorMessages.Count = 0 Then
        report.AppendLine("Errors: (none)")
    Else
        report.AppendLine("Errors (" & errorMessages.Count & "):")
        For Each s In errorMessages
            report.AppendLine("  - " & s)
        Next
    End If


    ' --- Write to text file when DebugMode is True ---
    If DebugMode Then
        Try
            Dim outputFile As String = DebugOutputFile
            System.IO.File.WriteAllText(outputFile, report.ToString())
        Catch ex As Exception
            ' If file write fails, ignore and continue with MessageBox
        End Try
    End If

    MessageBox.Show(report.ToString(), "UpdateStandardProperties")
End Sub


