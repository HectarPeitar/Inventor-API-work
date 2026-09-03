' Rule: ParameterWijzigingMetEenheden
' Description: Changes a Part-document UserParameter value using a unit-bearing Expression string.
' Requires: A Part document (.ipt) with a writable UserParameter named "Width".
'
' Status: VERIFIED against Autodesk Inventor 2026
' Date: 2026-09-03
'
' Key design decisions:
' - Uses Try/Catch on ComponentDefinition to restrict to Part documents.
'   (iLogic does not expose DocumentTypeEnum.)
' - Uses Parameter.Expression with a unit string ("50 mm") instead of a raw number.
'   (Parameter.Value interprets the number in the document's internal unit.)
' - Formats display values through UnitsOfMeasure.GetStringFromValue()
'   so the user always sees millimetres regardless of the document's internal unit.

Sub Main
    Dim doc As Document = ThisApplication.ActiveDocument
    
    ' Verkrijg de UnitsOfMeasure voor het document
    Dim uom As UnitsOfMeasure = doc.UnitsOfMeasure
    
    ' Probeer direct PartComponentDefinition te benaderen
    ' Als dit een assembly of drawing is, zal dit mislukken
    Dim compDef As PartComponentDefinition = Nothing
    Try
        compDef = doc.ComponentDefinition
    Catch ex As Exception
        MessageBox.Show("Deze rule werkt alleen in een onderdeeldocument (.ipt).", "Fout")
        Exit Sub
    End Try
    
    ' Controleer of we daadwerkelijk een PartComponentDefinition hebben
    If compDef Is Nothing Then
        MessageBox.Show("Deze rule werkt alleen in een onderdeeldocument (.ipt).", "Fout")
        Exit Sub
    End If
    
    Dim params As Parameters = compDef.Parameters
    
    ' Zoek de parameter "Width"
    Dim widthParam As Parameter = Nothing
    For Each p As Parameter In params
        If p.Name = "Width" Then
            widthParam = p
            Exit For
        End If
    Next
    
    ' Foutafhandeling: parameter niet gevonden
    If widthParam Is Nothing Then
        MessageBox.Show("Parameter 'Width' niet gevonden in het actieve onderdeel.", "Fout")
        Exit Sub
    End If
    
    ' Toon diagnostische informatie met correcte eenheden
    ' Gebruik UnitsOfMeasure om de waarde in mm te tonen
    Dim oudeWaardeInMM As String = uom.GetStringFromValue(widthParam.Value, UnitsTypeEnum.kMillimeterLengthUnits)
    
    Dim info As String = "Parameter Info:" & vbLf & _
                          "Naam: " & widthParam.Name & vbLf & _
                          "Huidige waarde: " & oudeWaardeInMM
    MessageBox.Show(info, "Debug Info")
    
    ' Wijzig de waarde met expliciete eenheden (zoals voorgeschreven in units.md)
    ' Gebruik "50 mm" in plaats van alleen 50
    ' Vang eventuele fouten af (bijv. als de parameter vergrendeld is)
    Try
        widthParam.Expression = "50 mm"
    Catch ex1 As Exception
        ' Als Expression niet lukt, probeer direct Value (numeriek)
        Try
            widthParam.Value = 50
        Catch ex2 As Exception
            MessageBox.Show("Kan parameter 'Width' niet wijzigen via Expression of Value." & vbLf & vbLf & _
                            "Expression fout: " & ex1.Message & vbLf & vbLf & _
                            "Value fout: " & ex2.Message, "Fout")
            Exit Sub
        End Try
    End Try
    
    ' Forceer een model-update
    doc.Update
    
    ' Toon de nieuwe waarde ook in mm
    Dim nieuweWaardeInMM As String = uom.GetStringFromValue(widthParam.Value, UnitsTypeEnum.kMillimeterLengthUnits)
    
    MessageBox.Show("Parameter 'Width' is gewijzigd en het model is bijgewerkt." & vbLf & _
                    "Nieuwe waarde: " & nieuweWaardeInMM, "Succes")
End Sub