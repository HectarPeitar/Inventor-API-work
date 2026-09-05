# iProperty Access via PropertySets in iLogic

## Purpose

Verified pattern for reading and writing iProperties in an iLogic rule (Autodesk Inventor 2026) using the `doc.PropertySets` API.

## Context

- Inventor version: 2026
- Environment: iLogic internal rule
- Document type: Part document (`.ipt`)
- Object/context: `doc.PropertySets`

## Verified API Members

| Member | Type | Description |
|---|---|---|
| `doc.PropertySets.Item("SetName")` | `PropertySet` | Access a property set by name |
| `PropertySet.Item("PropertyName")` | `Property` | Access a property by name |
| `Property.Value` | `Object` (read/write) | Get or set the property value |

## Property Set Mapping

| iProperty | Property Set Name |
|---|---|
| Part Number | `Design Tracking Properties` |
| Description | `Design Tracking Properties` |
| Designer | `Design Tracking Properties` |
| Title | `Summary Information` |
| Subject | `Summary Information` |
| Author | `Summary Information` |

## Implementation Pattern

### Reading an iProperty

```vb
Dim val As String = "" & doc.PropertySets.Item("Design Tracking Properties").Item("Part Number").Value
```

### Writing an iProperty

```vb
doc.PropertySets.Item("Design Tracking Properties").Item("Part Number").Value = "New Value"
```

### Safe Read with Error Handling

```vb
Dim val As String = ""
Try
    val = "" & doc.PropertySets.Item("Design Tracking Properties").Item("Part Number").Value
Catch ex As Exception
    ' Property not found or inaccessible
End Try
```

### Setting Material (Special Case)

The Material iProperty is linked to the document's Material object. Do NOT use PropertySets for Material — use `compDef.Material` instead:

```vb
' Reading
Dim matName As String = compDef.Material.Name

' Writing
Dim targetMaterial As Material = Nothing
For Each mat As Material In doc.Materials
    If mat.Name = "Steel, Carbon" Then
        targetMaterial = mat
        Exit For
    End If
Next
If targetMaterial IsNot Nothing Then
    compDef.Material = targetMaterial
End If
```

## Validation

Verified as part of the `UpdateStandardProperties` iLogic rule (2026-09-05):
- Successfully read and wrote Part Number, Description, and Designer via PropertySets
- Successfully read and wrote Material via `compDef.Material`
- All operations wrapped in Try/Catch handled errors gracefully

## Result

VERIFIED

## Important Limitations

- The iLogic `iProperties.Value` member does NOT accept a String argument — always use `doc.PropertySets` instead.
- The "Physical Properties" property set has COM registration issues in Inventor 2026 — use `compDef.Material` for Material.
- Property names are case-sensitive.
- Always wrap PropertySets access in Try/Catch for missing properties.

## Related

- `knowledge/errors/ilogic/ilogic-iproperties-api-limitations.md` — Documented API limitations
- `addins/UpdateStandardProperties/` — Production function using this pattern