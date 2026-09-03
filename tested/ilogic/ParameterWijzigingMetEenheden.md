# ParameterWijzigingMetEenheden

## Purpose

Sets the value of a Part-document UserParameter named `"Width"` to `"50 mm"` from an iLogic rule, with explicit units in the input string and unit-correct display through `UnitsOfMeasure`.

This entry captures the **reusable implementation pattern**: how to find a named UserParameter, change it using a unit-bearing expression string, force a model update, and format the result for the user.

## Context

- Inventor version: 2026
- Programming environment: iLogic rule (internal rule)
- Document type: Part (`.ipt`)
- Object/context: active Part document, `PartComponentDefinition.Parameters`, UserParameter named `"Width"`

## Verified Implementation

See the companion file:

    tested/ilogic/ParameterWijzigingMetEenheden.vb

The implementation follows this pattern:

1. Get the active document via `ThisApplication.ActiveDocument`.
2. Cast `doc.ComponentDefinition` to `PartComponentDefinition` inside a `Try`/`Catch`. This is the iLogic-safe way to restrict the rule to Part documents, because iLogic does not expose `DocumentTypeEnum`.
3. Iterate `compDef.Parameters` and locate the parameter whose `.Name` equals the expected name.
4. Read the current value through `Parameter.Value` but format it for display with `doc.UnitsOfMeasure.GetStringFromValue(value, UnitsTypeEnum.kMillimeterLengthUnits)`. `Parameter.Value` returns the document's internal unit (e.g. cm) and must not be shown to the user directly.
5. Assign the new value through `Parameter.Expression = "50 mm"`. The Expression string accepts unit suffixes; assigning a raw number to `Parameter.Value` is interpreted in the document's internal unit, not the user's expected unit.
6. Call `doc.Update` to force dependent features to recompute.
7. Display the new value, again formatted through `UnitsOfMeasure`.

Wrap both the `Expression` assignment and the fallback `Value` assignment in `Try`/`Catch` so that a read-only or locked parameter produces a useful error message instead of an unhandled exception.

## Validation

- Run the rule from **Manage → iLogic → Rules** in a Part document that contains a UserParameter named `Width`.
- Expected runtime behaviour: the parameter value is updated to `50 mm` in the Parameters panel, dependent features recompute, and both MessageBox dialogs show values formatted in millimetres.
- Validation date: 2026-09-03, Autodesk Inventor 2026, iLogic internal rule.

## Status

VERIFIED

## Important Limitations

- Part documents only. The rule relies on `PartComponentDefinition`; assemblies and drawings are rejected by the `Try`/`Catch` on `ComponentDefinition`.
- User Parameters only. The lookup uses `Parameters` directly; Model Parameters and Reference Parameters are not addressed separately.
- The parameter must exist with the exact name used in the lookup. Lookup is case-sensitive.
- The new value is assigned without validation. Negative or extreme values are accepted by the rule; the model decides whether the geometry remains valid.
- No batching. The rule changes one parameter per execution.

## Related

- `knowledge/ilogic.md` — iLogic-specific API notes
- `knowledge/parameters.md` — parameter concepts
- `knowledge/units.md` — unit handling
- `knowledge/errors/ilogic/iLogic-Missing-Api-Members.md` — verified negative knowledge from this task

