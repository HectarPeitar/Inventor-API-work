# iLogic iProperties API Limitations — Inventor 2026

## Purpose

This file documents verified limitations of the iLogic iProperties API in Autodesk Inventor 2026. These are confirmed negative findings — API members and approaches that do not work as expected.

## Status

VERIFIED — confirmed during the development and validation of `UpdateStandardProperties` (2026-09-05).

---

## Error 1: `iProperties.Value` Does Not Accept a String Argument

### Error

```
Unable to cast COM object of type 'Inventor._DocumentClass' to class type 'System.String'.
Instances of types that represent COM components cannot be cast to types that do not represent COM components;
however they can be cast to interfaces as long as the underlying COM component supports QueryInterface calls for the IID of the interface.
```

### Context

- Inventor version: 2026
- Environment: iLogic internal rule
- Document type: Part document
- Object: `iProperties` (iLogic extender object)

### Root Cause

The iLogic `iProperties.Value` member does not accept a String property name argument. When called as `iProperties.Value("Part Number")`, the runtime attempts to interpret the Document object as a String, causing the COM cast error.

### Incorrect Assumption

Assuming `iProperties.Value("PropertyName")` works like a parameterized property accepting a String argument.

### Correct Approach

Use the full Inventor API path:

```vb
' Reading
Dim val As String = doc.PropertySets.Item("Design Tracking Properties").Item("Part Number").Value

' Writing
doc.PropertySets.Item("Design Tracking Properties").Item("Part Number").Value = "New Value"
```

### Property Set Mapping

| iProperty | Property Set |
|---|---|
| Part Number | Design Tracking Properties |
| Description | Design Tracking Properties |
| Designer | Design Tracking Properties |
| Material | Physical Properties (see Error 2) |

---

## Error 2: Physical Properties Property Set COM Registration Failure

### Error

```
Invalid class string (0x800401F3 (CO_E_CLASSSTRING))
```

Also reported in Dutch as: `Klasse is niet geregistreerd` ("Class is not registered").

### Context

- Inventor version: 2026
- Environment: iLogic internal rule
- Document type: Part document
- Object: `PropertySets.Item("Physical Properties").Item("Material")`

### Root Cause

The "Physical Properties" property set has a COM registration issue when accessed through the PropertySets API in Inventor 2026. The Material property within this set cannot be read or written through the standard PropertySets path.

### Incorrect Assumption

Assuming all iProperties can be accessed uniformly through `doc.PropertySets.Item("PropertySetName").Item("PropertyName").Value`.

### Correct Approach

For Material, use the document's Material object directly:

```vb
' Reading material name
Dim matName As String = compDef.Material.Name

' Setting material (find in MaterialManager and assign)
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

---

## Verification

Both errors were discovered and confirmed during the development of `UpdateStandardProperties` (2026-09-05). The correct approaches were validated through runtime testing in Autodesk Inventor 2026.

## Related

- `addins/UpdateStandardProperties/` — Production function using these correct approaches
- `tested/ilogic/property-access-via-propertysets.md` — Reusable pattern for iProperty access