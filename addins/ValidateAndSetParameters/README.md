# ValidateAndSetParameters

## Purpose

Checks whether the User Parameters `Width`, `Height`, and `Thickness` exist in the active Part document, sets them to 500 mm, 300 mm, and 10 mm respectively, verifies the values, updates the model, and displays a final report.

## Requirements

- Autodesk Inventor 2026
- iLogic internal rule
- Active Part document (`.ipt`)
- User Parameters named `Width`, `Height`, and `Thickness`

## Supported Document Types

Part documents only (`.ipt`). Assemblies and drawings are rejected.

## How to Use

1. Open a Part document that contains User Parameters named `Width`, `Height`, and `Thickness`.
2. Run the rule from **Manage → iLogic → Rules**.
3. The rule will set each parameter to its target value, verify the result, update the model, and display a report.

## Expected Behavior

- All three parameters are updated to 500 mm, 300 mm, 10 mm.
- The model recomputes.
- A MessageBox shows changed parameters, missing parameters, errors, and final status.

## Validation

- Validation date: 2026-09-03
- Autodesk Inventor 2026, iLogic internal rule
- Status: REVIEWED

## Known Limitations

- Part documents only (relies on `PartComponentDefinition`).
- User Parameters only (Model Parameters and Reference Parameters are not addressed separately).
- Parameter lookup is case-sensitive.
- The new value is assigned without validation; negative or extreme values are accepted.
- Culture-dependent: assumes `GetStringFromValue` returns a locale-formatted string.
