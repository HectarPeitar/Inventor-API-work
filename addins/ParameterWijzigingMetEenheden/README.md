# ParameterWijzigingMetEenheden

## Purpose

Changes a Part-document UserParameter value using a unit-bearing Expression string. Sets the `Width` parameter to 50 mm and displays the before/after values.

## Requirements

- Autodesk Inventor 2026
- iLogic internal rule
- Active Part document (`.ipt`)
- A writable UserParameter named `Width`

## Supported Document Types

Part documents only (`.ipt`). Assemblies and drawings are rejected.

## How to Use

1. Open a Part document that contains a writable UserParameter named `Width`.
2. Run the rule from **Manage → iLogic → Rules**.
3. The rule displays the current value, sets it to 50 mm, updates the model, and shows the new value.

## Expected Behavior

- The `Width` parameter is set to 50 mm via `Parameter.Expression`.
- The model is updated.
- MessageBoxes show the before and after values.

## Validation

- Validation date: 2026-09-03
- Autodesk Inventor 2026, iLogic internal rule
- Status: VERIFIED

## Known Limitations

- Part documents only (relies on `PartComponentDefinition`).
- Targets only the `Width` parameter.
- Uses `Parameter.Expression` with a unit string (`"50 mm"`) rather than a raw number.
