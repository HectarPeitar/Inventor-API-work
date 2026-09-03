# ParameterWijzigingMetEenheden

## Status

VERIFIED tegen Autodesk Inventor 2026

## Datum

2026-09-03

## Doel

Wijzigt de waarde van een UserParameter genaamd "Width" in een onderdeeldocument naar "50 mm", met expliciete eenheden en correcte weergave via `UnitsOfMeasure`.

## Vereisten

- Autodesk Inventor 2026
- Een onderdeeldocument (`.ipt`) geopend in Inventor
- Een UserParameter genaamd `"Width"` in het document (User Parameters, niet Model Parameters)
- iLogic-extensie geïnstalleerd (standaard aanwezig in Inventor 2026)

## Gebruik

1. Open een `.ipt`-bestand in Inventor
2. Voeg een User Parameter toe met de naam `Width` (User Parameters via Manage → Parameters)
3. Open Manage → iLogic → Edit Rules
4. Voeg een nieuwe rule toe en kopieer de inhoud van `ParameterWijzigingMetEenheden.vb`
5. Geef de rule de naam `ParameterWijzigingMetEenheden`
6. Klik **Save & Close**
7. Open Manage → iLogic → Rules en dubbelklik op de rule om deze uit te voeren

## Verwachte resultaten

- **Debug Info MessageBox** toont:
  - Naam: Width
  - Huidige waarde: `<vorige waarde in mm>`
- **Succes MessageBox** toont:
  - Parameter 'Width' is gewijzigd en het model is bijgewerkt
  - Nieuwe waarde: 50 mm
- De waarde in het Parameters-paneel verandert naar 50 mm
- Het model wordt bijgewerkt als er afhankelijke features zijn

## Wat werkt

| Stap | API | Opmerking |
|------|-----|-----------|
| ActiveDocument ophalen | `ThisApplication.ActiveDocument` | Werkt |
| ComponentDefinition ophalen | `doc.ComponentDefinition` | Werkt (Try-Catch voor type-fouten) |
| Parameters doorlopen | `For Each p In compDef.Parameters` | Werkt |
| Parameter vinden op naam | `If p.Name = "Width"` | Werkt |
| Waarde wijzigen | `widthParam.Expression = "50 mm"` | Werkt met Expression-string |
| Waarde lezen met eenheden | `uom.GetStringFromValue(value, UnitsTypeEnum.kMillimeterLengthUnits)` | Werkt |
| Model bijwerken | `doc.Update` | Werkt |

## Wat NIET werkt in iLogic

Tijdens ontwikkeling zijn deze API-pogingen mislukt:

| Poging | Probleem |
|--------|----------|
| `doc.DocumentType = DocumentTypeEnum.kPartDocument` | Enum niet gevonden |
| `doc.DocumentType = DocumentTypeEnum.PartDocument` | Enum niet gevonden |
| `doc.FullName` | Property niet gevonden in iLogic's Document class |
| `ThisDoc.FullFileName` | Property niet gevonden in ThisDoc class |
| `widthParam.IsLocked` | Property niet gevonden op UserParameter |
| `widthParam.Value = "50 mm"` | Waarde is numeriek, geen string |
| `widthParam.Value = 50` | Werkt in cm-documenten als 50 cm, niet 50 mm |

## Geleerde lessen

### 1. iLogic API ≠ Inventor API
iLogic heeft beperktere toegang tot Inventor API dan een C# Add-in. Sommige properties bestaan simpelweg niet in de iLogic-omgeving.

### 2. Vermijd DocumentTypeEnum in iLogic
Gebruik in plaats daarvan een **Try-Catch** rond `PartComponentDefinition`. Als het een assembly is, zal de cast/runtime-fout optreden en kun je netjes afhandelen.

### 3. UnitsOfMeasure voor weergave
`Parameter.Value` geeft de **interne document-eenheid** terug. Als je document op cm staat, krijg je 25 voor 250 mm. Gebruik altijd `UnitsOfMeasure.GetStringFromValue()` voor weergave aan de gebruiker.

### 4. Expression boven Value
Voor het instellen van waarden met eenheden, gebruik `Parameter.Expression` (string) in plaats van `Parameter.Value` (numeriek). De Expression-syntax herkent eenheden zoals "50 mm".

### 5. Geneste Try-Catch voor robuustheid
Wikkel parameter-wijzigingen in Try-Catch. Als de parameter vergrendeld of read-only is, geeft dit een nuttige foutmelding in plaats van een onverwachte crash.

## Bekende beperkingen

- Werkt alleen in **Part documents** (`.ipt`)
- Werkt alleen met **User Parameters** (niet Model Parameters of Reference Parameters)
- Parameter moet de **exacte naam** `"Width"` hebben (hoofdlettergevoelig)
- Geen ondersteuning voor **batch-verwerking** van meerdere parameters tegelijk
- Geen validatie van de **nieuwe waarde** (negatieve of extreem grote waarden worden geaccepteerd)

## Toekomstige uitbreidingen

Ideeën voor vervolg-tests:

- **Algemene parameter-tool**: accepteer parameternaam en waarde als input
- **Batch processing**: doorloop meerdere parameters tegelijk
- **Assembly-ondersteuning**: pas de rule aan voor `AssemblyComponentDefinition`
- **iProperty updates**: wijzig ook iProperties zoals Part Number en Description
- **Feature control**: onderdruk/activeer specifieke features op basis van parameterwaarden
- **External rule**: zet de rule om naar een externe rule voor hergebruik

## Gerelateerde kennis

- `knowledge/parameters.md` — parameter concepten
- `knowledge/units.md` — eenheid handling (kritisch voor deze rule)
- `knowledge/ilogic.md` — iLogic specifieke patronen
- `knowledge/api-compatibility.md` — versie compatibiliteit
