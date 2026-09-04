# Feature Suppression in iLogic

## Purpose

Verified pattern for suppressing and activating Part features by name in an iLogic rule (Autodesk Inventor 2026).

## Context

- Inventor version: 2026
- Environment: iLogic internal rule
- Document type: Part document (`.ipt`)
- Object/context: `PartComponentDefinition.Features`

## Verified API Members

| Member | Type | Description |
|---|---|---|
| `PartFeature.Name` | `String` (read) | Feature name for matching |
| `PartFeature.Suppressed` | `Boolean` (read/write) | Get or set suppression state |

Both members were confirmed working in iLogic 2026 during the development of `ApplyFeatureConfiguration`.

## Implementation Pattern

### Finding a Feature by Name

```vb
Dim targetFeature As PartFeature = Nothing
For Each f As PartFeature In compDef.Features
    If f.Name = "FeatureName" Then
        targetFeature = f
        Exit For
    End If
Next
```

### Suppressing a Feature

```vb
Try
    targetFeature.Suppressed = True
Catch ex As Exception
    ' Handle error (e.g., locked feature, invalid state)
End Try
```

### Activating a Feature

```vb
Try
    targetFeature.Suppressed = False
Catch ex As Exception
    ' Handle error
End Try
```

### Checking Current State

```vb
Dim state As String
Try
    state = If(targetFeature.Suppressed, "Suppressed", "Active")
Catch ex As Exception
    state = "Unknown"
End Try
```

## Validation

Verified as part of the `ApplyFeatureConfiguration` iLogic rule (2026-09-04):

- Successfully suppressed and activated `Fillet1` and `Hole1` features
- Successfully read feature names during iteration
- Successfully read `Suppressed` state after modification
- All operations wrapped in Try/Catch handled errors gracefully

## Result

VERIFIED

## Important Limitations

- `PartFeature.Name` and `PartFeature.Suppressed` are verified in Inventor 2026 iLogic only — compatibility with older versions is unknown.
- Feature names are case-sensitive.
- Some features may be locked or read-only — always wrap `Suppressed` assignments in Try/Catch.
- After changing suppression state, call `doc.Update()` to recompute the model.

## Related

- `addins/ApplyFeatureConfiguration/` — Production function using this pattern
- `knowledge/ilogic.md` — General iLogic knowledge (Section 8: Features)