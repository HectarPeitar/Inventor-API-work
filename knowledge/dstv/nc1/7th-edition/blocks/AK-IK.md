# DSTV 7th Edition - AK / IK

## Source

DSTV 7th Corrected Edition, pp. 13-14.

## Purpose

- `AK` = external contour
- `IK` = internal contour

## Contour rules

- contours must be closed;
- first and last points have identical X/Y coordinates;
- other points must not be described more than once;
- external contours are described in mathematical orientation;
- internal contours are described clockwise;
- radius values define rounded contour elements;
- maximum single angle is +/-180 degrees.

For profile descriptions represented as plates, each plate may be associated with one of the standard faces (`o`, `u`, `v`, `h`).

## Notches

The `AK` block can contain a dedicated information line for a notch corner. The standard uses:

- `t` = tangential notch
- `w` = hole-like notch

The notch line is additional information and is not itself part of the contour point sequence.

## Priority

The 7th edition states that `AK` has higher priority than `SC` when both could describe the same geometry.

## Point line format

Per DSTV pp. 13–14 and the HEB400 worked example (p. 22):

```text
  {face} {X}{ref} {Y} {radius}
```

- face letter (`o`/`v`/`u`/`h`) and X-dimension-reference letter on every point in the worked example;
- radius last, two decimals; `+` radius sign = mathematical (CCW) arc orientation;
- sharp contour corners: radius `0.00`;
- the contour is closed by repeating the first point as the last point.

The exporter's `IK` output for sharp-corner rectangles uses exactly this format with radius `0.00` (implemented 2026-09 in `scratch/dstv_exporter.vb`).

## Verified viewer observation (2026-09)

Manual testing in the target NC1 viewer confirmed that a sharp-corner rectangular internal opening (50 × 80 mm) represented as an `IK` closed clockwise contour with radius = 0.0 at all corners **passes validation with no warning**, while the same geometry as a `BO` record with `d = 0.00` **fails with 1 validation warning**.

This makes the IK internal contour the verified working representation for sharp-corner internal rectangles in the exporter/viewer combination. This is a viewer-compatibility observation, not a universal DSTV rule — see `blocks/BO.md` for the full evidence and classification.

**Implementation status (verified 2026-09-09):** the exporter uses exactly this representation. A sharp rectangle (4-line closed sketch profile) whose **actual inner edge loop** on the face is still 4 lines / 0 arcs → IK contour (radius 0.0). If the loop shows 4 lines + 4 uniform arcs (3D Fillet-tool rounding) the opening is instead exported as **BO** with `d` = 2 × arc radius — see `blocks/BO.md` "Implementation status". Both paths validated in Inventor 2026 + the target NC1 viewer (no warning).

Related: `knowledge/dstv/nc1/7th-edition/blocks/BO.md` (Alternative-description priority section).
