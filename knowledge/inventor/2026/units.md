# Inventor 2026 Units — SDK Interpretation

## Source Relationship

| Field | Value |
|---|---|
| **Inventor Version** | 2026 |
| **This File** | CURATED SOURCE — SDK-aware interpretation |
| **General Concepts** | See `knowledge/units.md` |
| **SDK Reference** | `Samples_VBNET_STDAPP_Inv_UOM_*` |

**Important:** This file interprets the SDK for unit handling. It is not a replacement for `knowledge/units.md` (general concepts) or the SDK sample (authoritative usage).

---

## SDK Evidence — The Authoritative Unit Rules

`Samples_VBNET_STDAPP_Inv_UOM_ReadMe.txt` states (paraphrased):

> Internally, Inventor uses consistent units regardless of the units the user has specified for the document. Lengths are always in **cm**, angles are always in **radians**, mass is always in **kg**, and time is always in **seconds**. When working with any other API function, you can assume values are in these units. It is only when interacting with the user that you need to get/display information using the units specified by the user.

This is the authoritative rule for all Inventor API numeric values.

---

## Key UnitsOfMeasure Members (verified in UOM sample)

`Samples_VBNET_STDAPP_Inv_UOM_UOM.vb`:

| Member | Type | Purpose |
|---|---|---|
| `ConvertUnits(value, inUnit, outUnit)` | Double | Convert between compatible units |
| `CompatibleUnits(...)` | Boolean | Check cross-unit compatibility |
| `GetDatabaseUnitsFromExpression(...)` | — | Interpret a unit string into database units |
| `AngleUnits` / `MassUnits` / `TimeUnits` | UnitsTypeEnum | Display unit settings |
| `AngleDisplayPrecision` | — | Display precision |

`UnitsTypeEnum` values used in the sample: `kDegreeAngleUnits`, `kRadianAngleUnits`, `kLbMassMassUnits`, `kSlugMassUnits`, `kGramMassUnits`, `kKilogramMassUnits`, `kSecondTimeUnits`.

---

## Unit Handling Rules

1. **Never assume a raw numeric value is mm** — internal API values are in database units (cm, radians, kg, seconds).
2. **Parameter.Expression** accepts unit suffixes and resolves to the correct internal value.
3. **Parameter.Value** is in database units — format for display via `UnitsOfMeasure.GetStringFromValue(...)`.
4. **GetStringFromValue** outputs are **locale-formatted** (e.g. `"500,000 mm"` under a Dutch locale). Parse returns using `CultureInfo.CurrentCulture`. (`knowledge/errors/ilogic/iLogic-GetStringFromValue-Culture.md`.)
5. For geometry APIs, coordinates are in cm in the part/assembly coordinate space. Verify context before applying distances.

---

## iLogic Unit Workflow

```vb
' Set with explicit user-facing units
param.Expression = "50 mm"

' Read and format for display
Dim display As String = doc.UnitsOfMeasure.GetStringFromValue(param.Value, UnitsTypeEnum.kMillimeterLengthUnits)
```

---

## Task Path

```
KNOWLEDGE-MAP.md → units → UOM SDK sample → tested pattern → implementation
```

---

## Related Files

- `knowledge/units.md` — General unit handling concepts
- `knowledge/parameters.md` — Parameter concepts
- `knowledge/inventor/2026/parameters.md` — Parameter SDK interpretation
- `knowledge/inventor/2026/sdk/Samples_VBNET_STDAPP_Inv_UOM_*` — RAW SOURCE sample
- `knowledge/errors/ilogic/iLogic-GetStringFromValue-Culture.md` — Verified locale issue