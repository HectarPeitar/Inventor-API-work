# GetStringFromValue Returns Locale-Formatted String

## Error

When reading a parameter value via `UnitsOfMeasure.GetStringFromValue()` and parsing it with `Double.TryParse()` using `CultureInfo.InvariantCulture`, the parsed value is incorrect (e.g., 1000x too large).

**Example:**
- `GetStringFromValue` returns: `"500,000 mm"` (Dutch locale, comma = decimal separator)
- Parsed with `InvariantCulture`: `500000` (comma interpreted as thousands separator)
- Expected value: `500.000` mm

## Context

- Inventor version: 2026
- Environment: iLogic internal rule
- Document type: Part document
- API members: `UnitsOfMeasure.GetStringFromValue()`, `Double.TryParse()`

## Root Cause

`UnitsOfMeasure.GetStringFromValue()` returns a string formatted according to the **user's current culture** (e.g., Dutch locale uses comma as decimal separator). When this string is parsed with `CultureInfo.InvariantCulture` (where comma is a thousands separator), the numeric value is misinterpreted.

**Example with Dutch locale:**
- Expression set: `"500 mm"`
- `GetStringFromValue` returns: `"500,000 mm"`
- `Double.TryParse("500,000", NumberStyles.Any, CultureInfo.InvariantCulture, result)` → `result = 500000` (wrong!)
- `Double.TryParse("500,000", NumberStyles.Any, CultureInfo.CurrentCulture, result)` → `result = 500.000` (correct!)

## Incorrect Assumption

Assuming that `GetStringFromValue` returns a culture-invariant string format that can be parsed with `InvariantCulture`.

## Correct Approach

Always parse the string returned by `GetStringFromValue` using `CultureInfo.CurrentCulture`:

```vb
Dim waardeInMM As String = uom.GetStringFromValue(param.Value, UnitsTypeEnum.kMillimeterLengthUnits)
Dim numericValue As Double
Dim numericString As String = waardeInMM.Replace("mm", "").Trim()
Double.TryParse(numericString, _
        Globalization.NumberStyles.Any, _
        Globalization.CultureInfo.CurrentCulture, _
        numericValue)
```

## Verification

- Validated during development of `ValidateAndSetParameters` iLogic rule (2026-09-03)
- Using `CurrentCulture` correctly parses "500,000" as 500.000 in Dutch locale

## Status

VERIFIED

## Related

- `knowledge/ilogic.md` — iLogic-specific API notes
- `knowledge/units.md` — unit handling
- `tested/ilogic/ValidateAndSetParameters.vb` — implementation using this pattern
