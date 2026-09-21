# Plane.Normal Is Not the Outward Face Normal

## Error

No exception — silent logic failure. Debug evidence:

```
  [PROFILE] fallback: start face niet gevonden (bestDot=0.000)
```

on a part that HAS a perfect start face (planar cross-section face at minX,
normal exactly ±length axis).

## Context

- Inventor version: 2026
- Environment: iLogic rule (`scratch/dstv_exporter.vb`, EXPORT_DSTV2)
- Document type: Part (`HE400B_CoordinateTest.ipt`, plain extruded I-profile,
  525 mm, square ends)
- Object/context: start-face selection in `GetProfileDimensionsFromGeometry`,
  which originally picked the planar face whose `Plane.Normal` dot with the
  length axis was most negative (≈ −1.0).

## Root Cause

An Inventor `Plane` is stored as **normal + root point**, and **parallel planes
may both store the same normal direction**. For the test part BOTH end faces
stored their plane normal along +xUnit (dot = +1.0 each). Therefore:

- selecting "the face whose plane normal ≈ −xUnit" never matches;
- the minimum dot over all planar faces was 0.0 (the perpendicular side faces),
  hence `bestDot=0.000`.

Corroborating evidence from the same file: the end-cut detection receives the
raw `Plane.Normal` and then **flips it by face position** (start end: flip when
the X-component is positive) before using it as the outward normal — the raw
plane normal is direction-of-storage, not face orientation.

## Incorrect Assumption

That `CType(face.Geometry, Plane).Normal` equals the face's outward normal.

## Correct Approach

Identify end faces by **position**, using the runtime-verified pattern of the
end-cut detection (vertex X-extent):

1. planar faces only (`SurfaceTypeEnum.kPlaneSurface`);
2. plane parallel to the length axis, sign-independent:
   `|DotVector(plane.Normal, xUnit)| >= 0.9`;
3. the start face is the candidate whose **entire vertex X-extent** lies at
   the Np side: `fMinX <= minX + tol AndAlso fMaxX <= minX + tol`
   (tol = 0.05 cm in this project).

This is orientation-independent and immune to the plane-normal storage
direction.

Related finding from the same repair chain: a strict `<` comparison against an
initializer of −1.0 also excluded a perfect −1.0 match (the first attempted
fix); the position-based selection removes both problems at once.

## Verification

User runtime run in Inventor 2026 (2026-09) after the fix:

```
  [PROFILE] fallback: start face ok (eindvlak op minX, 12 randen)
  [PROFILE] fallback: loop 12 randen -> flange=6 web=6 arcs=0
  [PROFILE] fallback: OK flange=24.00 web=13.50 radius=0.00
```

Start face correctly identified; flange/web thickness derived from the
cross-section loop matched the independently calculated values (24.00 /
13.50 mm).

## Status

VERIFIED
