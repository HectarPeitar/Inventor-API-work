' Rule: ValidateAndSetParameters
' Description: Controleert of de User Parameters Width, Height en Thickness bestaan
'   in het actieve Part-document, stelt ze in op respectievelijk 500 mm, 300 mm en
'   10 mm via Parameter.Expression, werkt het model bij en toont een eindrapport.
'
' Status: REVIEWED (fix voor culture-parsing - iteratie 6)
' Inventor version: 2026
'
' Ontwerpbeslissingen (gebaseerd op geverifieerde kennis uit tested/ilogic/):
' - Part-only via Try/Catch op ComponentDefinition cast. (iLogic heeft geen DocumentTypeEnum.)
' - Parameter lookup via iteratie van compDef.Parameters en naamvergelijking.
' - Expressie via Parameter.Expression = "500 mm" (Parameter.Value interpreteert in interne eenheid).
' - Read-only/locked detectie via Try/Catch (UserParameter.IsLocked niet beschikbaar in iLogic).
' - Weergave via UnitsOfMeasure.GetStringFromValue(..., kMillimeterLengthUnits).
' - Een eind-MessageBox met gewijzigde/ontbrekende parameters, fouten en status.
'
' Verwacht: Actief Part-document (.ipt) met User Parameters Width, Height, Thickness.

Sub Main
    ' --- Initialisatie rapportverzamelingen ---
    Dim docName As String = "(geen actief document)"
    Dim changedParams As New List(Of String)
    Dim missingParams As New List(Of String)
    Dim errorMessages As New List(Of String)
    Dim ruleStatus As String = "Succes"

    ' --- 1. Actief document ophalen en Part-context bevestigen ---
    Dim doc As Document = ThisApplication.ActiveDocument
    If doc Is Nothing Then
        MessageBox.Show( _
            "Geen actief document gevonden." & vbLf & _
            "Open een Part-document (.ipt) en voer de rule opnieuw uit.",
            "ValidateAndSetParameters - Fout" )
        Return
    End If
    docName = doc.DisplayName

    ' iLogic heeft geen DocumentTypeEnum; detecteer via cast.
    Dim compDef As PartComponentDefinition = Nothing
    Try
        compDef = CType(doc.ComponentDefinition, PartComponentDefinition)
    Catch ex As Exception
        errorMessages.Add("Dit document is geen Part-document (.ipt)." )
        ruleStatus = "Mislukt"
        GoTo ReportSection
    End Try
    If compDef Is Nothing Then
        errorMessages.Add("ComponentDefinition kon niet als PartComponentDefinition worden geinterpreteerd." )
        ruleStatus = "Mislukt"
        GoTo ReportSection
    End If

    Dim params As Parameters = compDef.Parameters
    Dim uom As UnitsOfMeasure = doc.UnitsOfMeasure

    ' --- 2. Per parameter: bestaat hij? Zo ja, stel de waarde in. ---
    ' We verwerken alle parameters en stoppen NIET bij de eerste fout.
    Dim targets As New List(Of KeyValuePair(Of String, String))
    targets.Add(New KeyValuePair(Of String, String)("Width",     "500 mm"))
    targets.Add(New KeyValuePair(Of String, String)("Height",    "300 mm"))
    targets.Add(New KeyValuePair(Of String, String)("Thickness", "10 mm"))

    For Each target In targets
        Dim paramName As String = target.Key
        Dim newExpression As String = target.Value
        Dim foundParam As Parameter = Nothing

        ' Zoek de parameter op naam.
        For Each p As Parameter In params
            If p.Name = paramName Then
                foundParam = p
                Exit For
            End If
        Next

        If foundParam Is Nothing Then
            missingParams.Add(paramName)
            Continue For
        End If

        ' Stel de waarde in via Expression (met expliciete eenheid).
        Dim setSuccess As Boolean = False
        Try
            foundParam.Expression = newExpression
            setSuccess = True
        Catch ex As Exception
            errorMessages.Add("Parameter " & paramName & " kon niet worden gewijzigd: " & ex.Message)
            ruleStatus = "Gedeeltelijk mislukt"
        End Try

        If Not setSuccess Then
            Continue For
        End If

        ' --- 3. Verificatie: lees de waarde terug en vergelijk. ---
        Dim waardeInMM As String = ""
        Dim getSuccess As Boolean = False
        Try
            waardeInMM = uom.GetStringFromValue( _
                foundParam.Value, UnitsTypeEnum.kMillimeterLengthUnits)
            getSuccess = True
        Catch ex As Exception
            errorMessages.Add("Parameter " & paramName & " is ingesteld, maar kon niet worden geverifieerd: " & ex.Message)
            ruleStatus = "Gedeeltelijk mislukt"
            changedParams.Add(paramName & " -> " & newExpression & " (niet geverifieerd)" )
        End Try

        If Not getSuccess Then
            Continue For
        End If

        ' Verwachte waarde uit de expressie halen.
        Dim expectedMm As Double
        Dim expectedString As String = newExpression.Replace("mm", "" ).Trim()
        If Not Double.TryParse(expectedString, _
                Globalization.NumberStyles.Any, _
                Globalization.CultureInfo.InvariantCulture, _
                expectedMm) Then
            errorMessages.Add("Verwachte expressie " & newExpression & " kon niet worden verwerkt." )
            ruleStatus = "Gedeeltelijk mislukt"
            changedParams.Add(paramName & " -> " & newExpression)
            Continue For
        End If

        ' Gemeten waarde uit de weergave halen.
        ' BELANGRIJK: GetStringFromValue retourneert een string met de lokale
        ' notatie (bijv. "500,000" met komma als decimaal scheidingsteken in NL).
        ' We moeten deze parseren met CurrentCulture, niet InvariantCulture.
        Dim actualMm As Double
        Dim actualString As String = waardeInMM.Replace("mm", "" ).Trim()
        If Double.TryParse(actualString, _
                Globalization.NumberStyles.Any, _
                Globalization.CultureInfo.CurrentCulture, _
                actualMm) Then
            ' Gebruik tolerantie van 0.01 mm (10 micron) voor vergelijking.
            ' Dit absorbeert floating-point precisie-verlies van mm-cm-mm conversie.
            Dim verschil As Double = Math.Abs(actualMm - expectedMm)
            If verschil < 0.01 Then
                changedParams.Add(paramName & " = " & waardeInMM)
            Else
                errorMessages.Add("Parameter " & paramName & " verwacht " & newExpression & ", maar is " & waardeInMM & " (verschil: " & verschil.ToString("F6") & " mm)." )
                ruleStatus = "Gedeeltelijk mislukt"
                changedParams.Add(paramName & " -> " & waardeInMM & " (verwacht " & newExpression & " )" )
            End If
        Else
            changedParams.Add(paramName & " = " & waardeInMM)
        End If
    Next

    ' --- 4. Model bijwerken ---
    If changedParams.Count > 0 Then
        Try
            doc.Update()
        Catch ex As Exception
            errorMessages.Add("Model-update mislukt: " & ex.Message)
            ruleStatus = "Gedeeltelijk mislukt"
        End Try
    End If

    ' --- 5. Eindrapport tonen ---
ReportSection:
    Dim report As New System.Text.StringBuilder()
    report.AppendLine("ValidateAndSetParameters - Rapport" )
    report.AppendLine("Document: " & docName)
    report.AppendLine("Status:   " & ruleStatus)
    report.AppendLine("" )
    report.AppendLine("Gewijzigde parameters (" & changedParams.Count & "):" )
    If changedParams.Count = 0 Then
        report.AppendLine("  (geen)" )
    Else
        For Each s In changedParams
            report.AppendLine("  - " & s)
        Next
    End If
    report.AppendLine("" )
    report.AppendLine("Ontbrekende parameters (" & missingParams.Count & "):" )
    If missingParams.Count = 0 Then
        report.AppendLine("  (geen)" )
    Else
        For Each s In missingParams
            report.AppendLine("  - " & s)
        Next
    End If
    report.AppendLine("" )
    If errorMessages.Count = 0 Then
        report.AppendLine("Fouten: (geen)" )
    Else
        report.AppendLine("Fouten (" & errorMessages.Count & "):" )
        For Each s In errorMessages
            report.AppendLine("  - " & s)
        Next
    End If

    MessageBox.Show(report.ToString(), "ValidateAndSetParameters" )
End Sub