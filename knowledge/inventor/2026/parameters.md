# Inventor 2026 Parameters — SDK Interpretation

## Source Relationship

| Field | Value |
|---|---|
| **Inventor Version** | 2026 |
| **This File** | CURATED SOURCE — SDK-aware interpretation |
| **General Concepts** | See `knowledge/parameters.md` |
| **SDK Reference** | `Samples_VBNET_STDAPP_Inv_UOM_*`, `Samples_VNET_STDAPP_Inv_Pulley_*`, `Samples_VBNET_STDAPP_Inv_Bolts_*` |

**Important:** This file interprets the SDK for parameter work. It is not a replacement for `knowledge/parameters.md` (general concepts) or the SDK samples (authoritative usage).

---

## SDK Evidence for Parameter API

### Units of Measure Sample — Parameter-aware unit handling

`Samples_VBNET_STDAPP_Inv_UOM_UOM.vb` and `Samples_VBNET_STDAPP_Inv_UOM_ReadMe.txt`

- Internal database units are fixed regardless of document display units: **length = cm, angle = radians, mass = kg, time = seconds**.
- User input like `"3"`, `"3 cm"`, or `"(3 cm + d0) / 2"` is interpreted via unit-aware expressions.
- `UnitsOfMeasure.ConvertUnits()`, `CompatibleUnits()`, `GetDatabaseUnitsFromExpression()` handle user-facing unit conversion.
- `Parameter.Expression` accepts unit suffixes and parameter references.

### Pulley Sample — Parameter modification in a Part

`Samples_VNET_STDAPP_Inv_Pulley_*`

- Demonstrates modifying named parameters in a Part document, updating the part, and fitting the view.
- Parameter naming and inter-parameter relationships are essential for reliable automation.

### AutoBolts Sample — Parameter modification in context

`Samples_VBNET_STDAPP_Inv_Bolts_ReadMe.txt`

- Opens a seed part, modifies its `Diameter` parameter, updates the part, and places the result.
- Demonstrates parameters driving model geometry in an assembly workflow.

---

## Parameter Types in the 2026 Object Model

(Per curated object model — see `object-model.md` section 3.)

| Parameter Kind | Notes |
|---|---|
| Model Parameters | Driven by features; may be read-only or reference parameters |
| User Parameters | User-defined; writable in most cases |
| Reference Parameters | Normally read-only |

`[CURATED]` — verify exact member availability against the SDK/API reference.

---

## iLogic Notes (Inventor 2026)

- `Parameter.Value` is numeric in the document's internal unit. Do not display it directly.
- `Parameter.Expression` is a string and accepts unit suffixes (`"50 mm"`, `"1 in"`, `"Width * 2"`). Prefer it for user-facing sets.
- Override formula: `doc.UnitsOfMeasure.GetStringFromValue(value, UnitsTypeEnum.kMillimeterLengthUnits)` (or another `UnitsTypeEnum`).
- `GetStringFromValue` output is locale-formatted. Parse with `CultureInfo.CurrentCulture`, NOT `InvariantCulture`. See `knowledge/errors/ilogic/iLogic-GetStringFromValue-Culture.md`.
- `UserParameter.IsLocked` is not exposed in iLogic; detect lock via Try/Catch around assignment. See `knowledge/errors/ilogic/iLogic-Missing-Api-Members.md`.

---

## Task Path

```
KNOWLEDGE-MAP.md → parameters → units (if required) → UOM SDK sample → tested pattern → implementation
```

---

## Related Files

- `knowledge/parameters.md` — General parameter concepts
- `knowledge/units.md` — Unit handling concepts
- `knowledge/inventor/2026/units.md` — SDK unit interpretation
- `knowledge/inventor/2026/object-model.md` — Object hierarchy
- `knowledge/errors/ilogic/` — Verified iLogic limitations