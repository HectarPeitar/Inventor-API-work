' Rule: ValidateAssemblyStructure
' Description: Validates assembly contains required components (FRAME, MOTOR, COVER) at any depth
' Inventor: 2026 | Environment: iLogic | Status: VERIFIED
' Result: PASS=all present/valid, WARNING=attention, FAIL=missing/error
Sub Main
    Const DebugMode As Boolean = False
    Const DebugOutputFile As String = "C:\Users\ricog\3D Modeling\Inventor API work\scratch\ValidateAssemblyStructure-Output.txt"
    Dim requiredComponents As New List(Of String)({"FRAME", "MOTOR", "COVER"})
    Dim docName As String = "(no active document)"
    Dim ruleStatus As String = "PASS"
    Dim validationErrors As New List(Of String)
    Dim componentFindings As New Dictionary(Of String, List(Of String))
    For Each comp In requiredComponents
        componentFindings(comp) = New List(Of String)
    Next
    Dim missingComponents As New List(Of String)
    Dim duplicateComponents As New List(Of String)
    Dim doc As Document = ThisApplication.ActiveDocument
    If doc Is Nothing Then
        validationErrors.Add("No active document found.")
        ruleStatus = "FAIL"
        GoTo ReportSection
    End If
    docName = doc.DisplayName
    Dim asmCompDef As AssemblyComponentDefinition = Nothing
    Dim earlyExit As Boolean = False
    Try
        asmCompDef = CType(doc.ComponentDefinition, AssemblyComponentDefinition)
    Catch ex As Exception
        validationErrors.Add("This document is not an Assembly document (.iam).")
        ruleStatus = "FAIL"
        earlyExit = True
    End Try
    If earlyExit Then GoTo ReportSection
    If asmCompDef Is Nothing Then
        validationErrors.Add("ComponentDefinition could not be interpreted as AssemblyComponentDefinition.")
        ruleStatus = "FAIL"
        GoTo ReportSection
    End If
    Dim inspectionErrors As New List(Of String)
    Try
        TraverseOccurrences(asmCompDef.Occurrences, requiredComponents, componentFindings, inspectionErrors, "")
    Catch ex As Exception
        validationErrors.Add("Assembly traversal failed: " & ex.Message)
        ruleStatus = "FAIL"
        GoTo ReportSection
    End Try
    For Each inspErr In inspectionErrors
        validationErrors.Add(inspErr)
    Next
    For Each comp In requiredComponents
        Dim findings As List(Of String) = componentFindings(comp)
        If findings.Count = 0 Then
            missingComponents.Add(comp)
        ElseIf findings.Count > 1 Then
            duplicateComponents.Add(comp)
        End If
        Dim allSuppressed As Boolean = True
        For Each finding In findings
            If Not finding.StartsWith("[SUPPRESSED]") Then
                allSuppressed = False
                Exit For
            End If
        Next
        If findings.Count > 0 AndAlso allSuppressed Then
            If ruleStatus = "PASS" Then ruleStatus = "WARNING"
        End If
    Next
    If missingComponents.Count > 0 Then
        ruleStatus = "FAIL"
    ElseIf validationErrors.Count > 0 AndAlso ruleStatus = "PASS" Then
        ruleStatus = "WARNING"
    End If

ReportSection:
    Dim report As New System.Text.StringBuilder()
    report.AppendLine("============================================================")
    report.AppendLine(" ValidateAssemblyStructure - Validation Report")
    report.AppendLine("============================================================")
    report.AppendLine("")
    report.AppendLine("Document: " & docName)
    report.AppendLine("Status:   " & ruleStatus)
    report.AppendLine("")
    report.AppendLine("------------------------------------------------------------")
    report.AppendLine(" COMPONENT DETAILS")
    report.AppendLine("------------------------------------------------------------")
    report.AppendLine("")
    For Each comp In requiredComponents
        Dim findings As List(Of String) = componentFindings(comp)
        Dim totalCount As Integer = findings.Count
        Dim activeCount As Integer = 0
        Dim suppressedCount As Integer = 0
        For Each finding In findings
            If finding.StartsWith("[SUPPRESSED]") Then
                suppressedCount += 1
            Else
                activeCount += 1
            End If
        Next
        report.AppendLine("  " & comp)
        report.AppendLine("    Total Occurrences: " & totalCount)
        report.AppendLine("    Active: " & activeCount)
        report.AppendLine("    Suppressed: " & suppressedCount)
        If findings.Count = 0 Then
            report.AppendLine("    Status: MISSING")
        Else
            report.AppendLine("    Occurrences:")
            For Each finding In findings
                Dim occName As String = finding.Replace("[SUPPRESSED]", "").Trim()
                report.AppendLine("      - " & finding)
            Next
        End If
        report.AppendLine("")
    Next
    report.AppendLine("------------------------------------------------------------")
    report.AppendLine(" SUMMARY")
    report.AppendLine("------------------------------------------------------------")
    report.AppendLine("")
    If missingComponents.Count = 0 Then
        report.AppendLine("Missing Components: (none)")
    Else
        report.AppendLine("Missing Components (" & missingComponents.Count & "):")
        For Each missComp In missingComponents
            report.AppendLine("  - " & missComp)
        Next
    End If
    report.AppendLine("")
    If duplicateComponents.Count = 0 Then
        report.AppendLine("Duplicate Components: (none)")
    Else
        report.AppendLine("Duplicate Components (" & duplicateComponents.Count & "):")
        For Each dupComp In duplicateComponents
            Dim count As Integer = componentFindings(dupComp).Count
            report.AppendLine("  - " & dupComp & " (" & count & " occurrences)")
        Next
    End If
    report.AppendLine("")
    If validationErrors.Count = 0 Then
        report.AppendLine("Validation Errors: (none)")
    Else
        report.AppendLine("Validation Errors (" & validationErrors.Count & "):")
        For Each valErr In validationErrors
            report.AppendLine("  - " & valErr)
        Next
    End If
    report.AppendLine("")
    report.AppendLine("------------------------------------------------------------")
    report.AppendLine(" RESULT EXPLANATION")
    report.AppendLine("------------------------------------------------------------")
    report.AppendLine("")
    Select Case ruleStatus
        Case "PASS"
            report.AppendLine("  PASS - All required components are present and valid.")
        Case "WARNING"
            report.AppendLine("  WARNING - Required structure exists but requires attention.")
            report.AppendLine("  Possible causes: All occurrences suppressed, or duplicates detected.")
        Case "FAIL"
            report.AppendLine("  FAIL - One or more required components missing or validation failed.")
    End Select
    report.AppendLine("")
    report.AppendLine("============================================================")
    Dim reportText As String = report.ToString()
    If DebugMode Then
        Try
            System.IO.File.WriteAllText(DebugOutputFile, reportText)
        Catch ex As Exception
        End Try
    End If
    MessageBox.Show(reportText, "ValidateAssemblyStructure - " & ruleStatus)
End Sub

Private Sub TraverseOccurrences( _
    ByVal occurrences As ComponentOccurrences, _
    ByVal requiredComponents As List(Of String), _
    ByRef componentFindings As Dictionary(Of String, List(Of String)), _
    ByRef validationErrors As List(Of String), _
    ByVal path As String)
    
    For Each occ As ComponentOccurrence In occurrences
        Dim occName As String = ""
        Dim occPath As String = path & "/" & occ.Name
        
        Try
            occName = occ.Name
        Catch ex As Exception
            validationErrors.Add("Cannot read occurrence name at path: " & occPath)
            Continue For
        End Try
        
        Dim occNameUpper As String = occName.ToUpper()
        
        For Each reqComp In requiredComponents
            If occNameUpper.Contains(reqComp) Then
                ' Determine suppression state
                Dim suppressed As Boolean = False
                Try
                    suppressed = occ.Suppressed
                Catch ex As Exception
                    ' If we cannot read suppression state, assume it might be suppressed
                    suppressed = True
                    validationErrors.Add("Cannot read suppression state for: " & occPath)
                End Try
                
                ' Build the finding string with appropriate prefix
                Dim prefix As String
                If suppressed Then
                    prefix = "[SUPPRESSED] "
                Else
                    prefix = "[ACTIVE]   "
                End If
                Dim finding As String = prefix & occName
                componentFindings(reqComp).Add(finding)
            End If
        Next
        
        ' Recursively traverse sub-occurrences (nested subassemblies)
        ' Note: Suppressed components cannot have their SubOccurrences accessed
        ' This is normal Inventor behavior - skip traversal for suppressed occurrences
        Dim isSuppressed As Boolean = False
        Try
            isSuppressed = occ.Suppressed
        Catch ex As Exception
            ' Cannot determine suppression state
        End Try
        
        If Not isSuppressed Then
            Try
                If occ.SubOccurrences.Count > 0 Then
                    TraverseOccurrences(occ.SubOccurrences, requiredComponents, componentFindings, validationErrors, occPath)
                End If
            Catch ex As Exception
                ' Cannot access sub-occurrences - record error but continue traversal
                validationErrors.Add("Cannot traverse sub-occurrences at path: " & occPath)
            End Try
        End If
    Next
End Sub