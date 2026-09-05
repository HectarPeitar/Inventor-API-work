# UpdateStandardProperties

## Purpose

Standardize and validate key iProperties of a Part before it is released to the next engineering or production step. Uses User Parameters where available while preserving existing valid iProperty values.

## Requirements

- Autodesk Inventor 2026
- iLogic internal or external rule
- Active Part document (`.ipt`)

## Supported Document Types

Part documents only (`.ipt`). Assemblies and drawings are rejected.

## How to Use

1. Open a Part document that contains User Parameters named `PartNumber` and `Description` (optional).
2. Run the rule from **Manage → iLogic → Rules**.
3. The rule will update iProperties from User Parameters, validate Material from the document, and report missing Designer values.
4. A MessageBox shows the final report with changed, preserved, missing, errors, and status.

## Expected Behavior

### Part Number
- If User Parameter `PartNumber` exists and has a value, it is used as the iProperty `Part Number`.
- If the existing iProperty differs, it is updated.
- If the parameter does not exist or has no usable value, the existing Part Number is preserved.

### Description
- If User Parameter `Description` exists and has a value, it is used as the iProperty `Description`.
- If the existing iProperty differs, it is updated.
- If the parameter does not exist or has no usable value, the existing Description is preserved.

### Material
- Read from the document's Material object (`compDef.Material.Name`).
- If the Material iProperty is empty and a valid material exists, it is populated.
- Existing Material values are never overwritten with empty values.

### Designer
- If Designer is populated, it is preserved.
- If Designer is missing, it is reported.
- Existing Designer values are never overwritten automatically.

## Final Status

| Status | Meaning |
|---|---|
| `PASS` | Required updates succeeded and no important information is missing |
| `WARNING` | Updates succeeded, but one or more non-critical values (e.g., Designer) are missing |
| `FAIL` | A required update or validation failed |

## Validation

- Validation date: 2026-09-05
- Autodesk Inventor 2026, iLogic internal rule
- Status: VERIFIED

## Known Limitations

- Part documents only (relies on `PartComponentDefinition`).
- Parameter names are case-sensitive: `PartNumber` and `Description`.
- The Material iProperty is read from the document Material object, not from the "Physical Properties" property set (which has COM registration issues in Inventor 2026).
- Designer is only reported, never automatically populated.

## API Notes

- iProperties are accessed via `doc.PropertySets.Item("Design Tracking Properties").Item("PropertyName").Value`
- The iLogic `iProperties.Value` member does NOT accept a String argument — use the PropertySets API instead
- Material is read/written via `compDef.Material` and `compDef.Material.Name`