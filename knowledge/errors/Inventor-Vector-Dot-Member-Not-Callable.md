# Inventor Vector — Dot Member Not Callable (iLogic Late Binding)

## Error

`Public member 'Dot' on type 'Vector' not found.`

(iLogic runtime exception; in this project it was swallowed by a Try/Catch and
surfaced only after debug logging was added.)

## Context

- Inventor version: 2026
- Environment: iLogic rule (`scratch/dstv_exporter.vb`, EXPORT_DSTV2)
- Document type: Part (`HE400B_CoordinateTest.ipt`, plain extruded I-profile)
- Object/context: `GetProfileDimensionsFromGeometry` — start-face detection,
  edge classification, and corner-arc checks computed dot products via
  `oPlane.Normal.AsVector.Dot(xUnit.AsVector)` and similar `Vector.Dot(...)` calls.

## Root Cause

Inventor geometry objects do not expose a callable `Dot` member. Under iLogic
late binding (`Option Strict Off`) an invalid member name compiles silently and
only fails at runtime. The exception was invisible until `[PROFILE] fallback
EXCEPTION:` debug logging was added to the function.

## Incorrect Assumption

That `Vector.Dot(otherVector)` exists as a member, as in some other geometry
APIs. (The compile check also passed, because late binding defers the member
lookup to runtime.)

## Correct Approach

Use the project's `DotVector(a As Vector, b As Vector)` helper (manual
`a.X*b.X + a.Y*b.Y + a.Z*b.Z`), defined in `scratch/dstv_exporter.vb` and used
by all runtime-verified code paths in the exporter (B-Rep hole detection,
end-cut detection, AK plate mapping).

All 5 dot-product call sites in `GetProfileDimensionsFromGeometry` (start-face
abs-dot, edge classification, midpoint z-position, corner-arc check,
`MinDistanceBetweenEdgeGroups`) were converted to `DotVector`.

Related findings from the same repair chain:

- `Point` has no `TransientGeometry` property — use
  `ThisApplication.TransientGeometry.CreatePoint(...)` (runtime-verified in the
  same repair chain: the flange calculation depends on these midpoints).
- Inventor `Vector` supports no `-` (subtraction) operator — use
  `pointA.VectorTo(pointB)` to obtain a difference vector.
- LINQ extension calls such as `List(Of Double).Average()` are not reliably
  available in iLogic; use a manual sum/count loop.

## Verification

User runtime run in Inventor 2026 (2026-09) after the fix:

```
  [PROFILE] fallback: start face ok (eindvlak op minX, 12 randen)
  [PROFILE] fallback: loop 12 randen -> flange=6 web=6 arcs=0
  [PROFILE] fallback: OK flange=24.00 web=13.50 radius=0.00
```

The dot-based logic (start-face selection via |dot|, edge classification via
|dot|, section split via dot projection) executed correctly and produced the
independently expected values.

## Status

VERIFIED
