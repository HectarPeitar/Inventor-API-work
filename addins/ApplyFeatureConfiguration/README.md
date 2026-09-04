# ApplyFeatureConfiguration

## Purpose

Automatically configure part features based on the User Parameter `Width`. This iLogic rule suppresses or activates `Fillet1` and `Hole1` depending on the current value of `Width`.

## Requirements

- Autodesk Inventor 2026
- iLogic internal rule
- Active Part document (`.ipt`)
- A writable User Parameter named `Width`
- Features named `Fillet1` and `Hole1`

## Supported Document Types

- Part documents (`.ipt`) only

## Behavior

| Width Condition | Fillet1 State | Hole1 State |
|---|---|---|
| `Width < 500 mm` | Suppressed | Suppressed |
| `Width >= 500 mm` | Active | — |
| `Width < 750 mm` | — | Suppressed |
| `Width >= 750 mm` | — | Active |

### Combined Logic

- **Fillet1**: suppressed when `Width < 500 mm`, active when `Width >= 500 mm`
- **Hole1**: suppressed when `Width < 750 mm`, active when `Width >= 750 mm`

## How to Use

1. Open a Part document that contains a writable User Parameter named `Width` and features named `Fillet1` and `Hole1`.
2. Run the rule from **Manage → iLogic → Rules**.
3. The rule will read `Width`, apply the suppression logic, update the model, and display a report.

## Report Output

The rule displays a MessageBox with:

- Document name
- Width value (formatted in mm)
- Fillet1 state (Active / Suppressed / Unknown)
- Hole1 state (Active / Suppressed / Unknown)
- Missing objects list
- Errors list
- Final status: `PASS`, `WARNING`, or `FAIL`

## Error Handling

The rule safely handles:

- **Wrong document type** — reports FAIL with a clear message
- **Missing `Width` parameter** — reports FAIL, adds to missing objects
- **Missing `Fillet1`** — reports WARNING, adds to missing objects
- **Missing `Hole1`** — reports WARNING, adds to missing objects
- **Inability to change feature state** — catches the error, reports FAIL
- **Model update failure** — catches the error, reports FAIL

## Validation Results

Tested in Autodesk Inventor 2026:

| Test | Width | Fillet1 | Hole1 | Status |
|---|---|---|---|---|
| 1 | 400 mm | Suppressed | Suppressed | PASS |
| 2 | 600 mm | Active | Suppressed | PASS |
| 3 | 800 mm | Active | Active | PASS |
| 4 | Assembly (`.iam`) | — | — | FAIL |
| 5 | No `Width` param | — | — | FAIL |
| 6 | No `Fillet1` | — | — | WARNING |

## Known Limitations

- `PartFeature.Suppressed` and `PartFeature.Name` are verified in Inventor 2026 iLogic but may not be available in older versions.
- The rule does not handle locked or read-only features — these will raise an error caught by the Try/Catch blocks.
- Feature names (`Fillet1`, `Hole1`) are case-sensitive and must match exactly.

## Status

VERIFIED — 2026-09-04