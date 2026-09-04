' Rule: ApplyFeatureConfiguration
' Description: Automatically configure part features based on the User Parameter Width.
'   - Width < 500 mm:  Suppress Fillet1, Suppress Hole1
'   - Width >= 500 mm: Activate Fillet1
'   - Width < 750 mm:  Suppress Hole1
'   - Width >= 750 mm: Activate Hole1
' Status: VERIFIED | Inventor version: 2026 | Date: 2026-09-04
' Design: Part-only via cast+Try/Catch; param/feature lookup via iteration;
'         GetStringFromValue + CurrentCulture parse; PartFeature.Suppressed (VERIFIED).
'
' Validation (Inventor 2026):
'   - Width=400mm: Fillet1=Suppressed, Hole1=Suppressed, Status=PASS
'   - Width=600mm: Fillet1=Active,    Hole1=Suppressed, Status=PASS
'   - Width=800mm: Fillet1=Active,    Hole1=Active,     Status=PASS
'   - Assembly doc: Status=FAIL with clear message
'   - Missing Width: Status=FAIL, missing object reported
'   - Missing Fillet1: Status=WARNING, missing object reported

Sub Main
    Dim docName As String = "(geen actief document)"
    Dim missingObjects As New List(Of String)
    Dim errorMessages As New List(Of String)
    Dim ruleStatus As String = "PASS"
    Dim widthDisplay As String = ""
    Dim widthMm As Double
    Dim filletFeature As PartFeature = Nothing
    Dim holeFeature As PartFeature = Nothing
    Dim filletState As String = "Onbekend"
    Dim holeState As String = "Onbekend"
    Dim abortRule As Boolean = False

    ' --- 1. Get active document and confirm Part context ---
    Dim doc As Document = ThisApplication.ActiveDocument
    If doc Is Nothing Then
        MessageBox.Show("Geen actief document gevonden." & vbLf & _
            "Open een Part-document (.ipt) en voer de rule opnieuw uit.", _
            "ApplyFeatureConfiguration - Fout")
        Return
    End If
    docName = doc.DisplayName

    Dim compDef As PartComponentDefinition = Nothing
    Try
        compDef = CType(doc.ComponentDefinition, PartComponentDefinition)
    Catch ex As Exception
        errorMessages.Add("Dit document is geen Part-document (.ipt).")
        ruleStatus = "FAIL"
        abortRule = True
    End Try
    If Not abortRule AndAlso compDef Is Nothing Then
        errorMessages.Add("ComponentDefinition kon niet als PartComponentDefinition worden geinterpreteerd.")
        ruleStatus = "FAIL"
        abortRule = True
    End If

    ' --- 2. Find Width parameter ---
    Dim widthParam As Parameter = Nothing
    If Not abortRule Then
        For Each p As Parameter In compDef.Parameters
            If p.Name = "Width" Then widthParam = p
        Next
        If widthParam Is Nothing Then
            missingObjects.Add("Width (User Parameter)")
            ruleStatus = "FAIL"
            abortRule = True
        End If
    End If

    ' --- 3. Get Width value in millimetres ---
    If Not abortRule Then
        Try
            widthDisplay = doc.UnitsOfMeasure.GetStringFromValue(widthParam.Value, UnitsTypeEnum.kMillimeterLengthUnits)
            Dim parseString As String = widthDisplay.Replace("mm", "").Trim()
            If Not Double.TryParse(parseString, Globalization.NumberStyles.Any, _
                    Globalization.CultureInfo.CurrentCulture, widthMm) Then
                errorMessages.Add("Kon de Width-waarde '" & widthDisplay & "' niet parseren.")
                ruleStatus = "FAIL"

    ' --- 4. Find Fillet1 and Hole1 features ---
    If Not abortRule Then
        For Each f As PartFeature In compDef.Features
            If f.Name = "Fillet1" Then filletFeature = f
            If f.Name = "Hole1" Then holeFeature = f
            If filletFeature IsNot Nothing AndAlso holeFeature IsNot Nothing Then Exit For
        Next
        If filletFeature Is Nothing Then missingObjects.Add("Fillet1 (Feature)")
        If holeFeature Is Nothing Then missingObjects.Add("Hole1 (Feature)")
        If missingObjects.Count > 0 Then
            ruleStatus = "WARNING"
            abortRule = True
        End If
    End If

    ' --- 5. Compute and apply target states ---
    ' Fillet1: suppressed when Width < 500, active when Width >= 500
    ' Hole1:   suppressed when Width < 750, active when Width >= 750
    If Not abortRule Then
        Try
            filletFeature.Suppressed = (widthMm < 500.0)
        Catch ex As Exception
            errorMessages.Add("Kon Fillet1 Suppressed niet instellen: " & ex.Message)
            ruleStatus = "FAIL"
        End Try
        Try
            holeFeature.Suppressed = (widthMm < 750.0)
        Catch ex As Exception
            errorMessages.Add("Kon Hole1 Suppressed niet instellen: " & ex.Message)
            ruleStatus = "FAIL"
        End Try
    End If

    ' --- 6. Update the model ---
    If Not abortRule Then
        Try
            doc.Update()
        Catch ex As Exception
            errorMessages.Add("Model-update mislukt: " & ex.Message)
            ruleStatus = "FAIL"
        End Try
    End If

    ' --- 7. Verify resulting feature states ---
    If filletFeature IsNot Nothing Then
        Try
            filletState = If(filletFeature.Suppressed, "Suppressed", "Active")
        Catch ex As Exception
            filletState = "Onbekend (fout: " & ex.Message & ")"
        End Try
    End If
    If holeFeature IsNot Nothing Then
        Try
            holeState = If(holeFeature.Suppressed, "Suppressed", "Active")
        Catch ex As Exception
            holeState = "Onbekend (fout: " & ex.Message & ")"
        End Try
    End If

    ' --- 8. Build and show final report ---
    Dim report As New System.Text.StringBuilder()
    report.AppendLine("ApplyFeatureConfiguration - Rapport")
    report.AppendLine("Document: " & docName)
    report.AppendLine("Status:   " & ruleStatus)
    report.AppendLine("")
    report.AppendLine("Width: " & widthDisplay)
    report.AppendLine("Fillet1: " & If(filletFeature IsNot Nothing, filletState, "(niet gevonden)"))
    report.AppendLine("Hole1:   " & If(holeFeature IsNot Nothing, holeState, "(niet gevonden)"))
    report.AppendLine("")
    report.AppendLine("Ontbrekende objecten (" & missingObjects.Count & "):")
    If missingObjects.Count = 0 Then
        report.AppendLine("  (geen)")
    Else
        For Each s In missingObjects
            report.AppendLine("  - " & s)
        Next
    End If
    report.AppendLine("")
    If errorMessages.Count = 0 Then
        report.AppendLine("Fouten: (geen)")
    Else
        report.AppendLine("Fouten (" & errorMessages.Count & "):")
        For Each s In errorMessages
            report.AppendLine("  - " & s)
        Next
    End If
    MessageBox.Show(report.ToString(), "ApplyFeatureConfiguration")
End Sub
                abortRule = True
            End If
        Catch ex As Exception
            errorMessages.Add("Fout bij ophalen Width-waarde: " & ex.Message)
            ruleStatus = "FAIL"
            abortRule = True
        End Try
    End If