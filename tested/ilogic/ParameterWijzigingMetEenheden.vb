' Regel: ParameterWijzigingMetEenheden
' Beschrijving: Wijzigt de waarde van een parameter met expliciete eenheden
' Vereist: Een onderdeeldocument (.ipt) met een beschrijfbare UserParameter genaamd "Width"
'
' Status: VERIFIED tegen Autodesk Inventor 2026
' Datum: 2026-09-03
'
' Geleerde lessen tijdens ontwikkeling:
' 1. DocumentTypeEnum werkt niet in iLogic - gebruik PartComponentDefinition met Try-Catch
' 2. doc.FullName bestaat niet - gebruik ThisDoc of ThisApplication.ActiveDocument
' 3. widthParam.IsLocked bestaat niet op UserParameter - gebruik Try-Catch rond Value/Expression
' 4. Parameter.Value geeft interne waarde terug (in cm bij mm-document), gebruik
'    UnitsOfMeasure.GetStringFromValue() met UnitsTypeEnum voor correcte weergave
' 5. widthParam.Expression = "50 mm" werkt beter dan widthParam.Value = "50 mm"

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