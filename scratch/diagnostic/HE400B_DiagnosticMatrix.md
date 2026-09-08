# HE400B Diagnostic Matrix

## Purpose

Record the isolated diagnostic NC1 variants used to identify which element(s) in the generated NC1 file cause validation errors in the target NC1 viewer.

## Source

Generated from the HE400B coordinate test exporter. All variants share the same ST header and geometry; only the BO records differ.

## Variants

### Variant A — Baseline (current generated output)

- **File**: `Variant_A_Baseline.nc1`
- **Content**: 7 BO holes, all using `u` dimension-reference letters
- **Result**: FAIL (2 validation warnings)

### Variant B — Dimension-reference letters corrected

- **File**: `Variant_B_DimensionRefs.nc1`
- **Content**: Same geometry, face-appropriate reference letters (`o`/`s`/`u`)
- **Result**: FAIL (2 validation warnings)
- **Conclusion**: Dimension-reference letters are NOT the cause of validation errors.

### Variant C — BO formatting (trailing 0.00 omitted)

- **File**: `Variant_C_BOFormatting.nc1`
- **Content**: BO records with trailing `0.00` omitted from round holes
- **Result**: Not tested in isolation for this investigation

### Variant D — Single round hole

- **File**: `Variant_D_SingleRoundHole.nc1`
- **Content**: Single round BO hole (`v 100.00u 200.00 10.00 0.00`)
- **Result**: PASS
- **Conclusion**: Round holes are accepted by the target viewer.

### Variant E — Single slot

- **File**: `Variant_E_SingleSlot.nc1`
- **Content**: Single rounded-end slot (`v 100.00u 200.00 10.00 0.00l 70.00 0.00 0.00`)
- **Result**: PASS
- **Conclusion**: Rounded-end slots represented as `BO ... l ...` are accepted by the target viewer.

### Variant F — Single rectangle (rounded corners, d=24.00)

- **File**: `Variant_F_SingleRectangle.nc1`
- **Content**: Single rectangular BO hole with rounded corners (`o 262.50u 100.00 24.00 0.00l 100.00 60.00 10.00`)
- **Result**: PASS (non-zero corner diameter)

## Additional Manual Viewer Tests (not saved as variant files)

### Sharp-corner rectangle (d=0.00)

- **BO representation**: `o 395.00u 230.00 0.00 0.00l 50.00 80.00 0.00`
- **Result**: FAIL — 1 validation warning

### Sharp-corner rectangle with non-zero d values

- `d = 1.00` → PASS
- `d = 10.00` → PASS
- `d = 20.00` → PASS

### Sharp-corner rectangle as IK internal contour

- **Representation**: IK closed clockwise contour using corner coordinates, radius=0.0 at corners
- **Result**: PASS — no validation warning

## Root Cause

Sharp-corner rectangular internal openings represented as BO with `d=0.00` are rejected by the target viewer. The same geometry passes as an IK internal contour.

## Verified Slot Interpretation

For the HEB400 reference slot record `u 1415.00s 251.50 24.00 0.00l 70.00 0.00 0.00`:

- `d` = round-end diameter
- `l Width` = centre-to-centre distance (70.00)
- `l Height` = 0.00
- `l Angle` = slot angle

This supersedes the previous interpretation that `l Width` = overall length (centreDist + diameter).