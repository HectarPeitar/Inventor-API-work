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

## Arcs (AK) — verified rules (2026-09, AK-2)

From DSTV 7th ed. p. 13 (extracted :616-624) and the p. 21 example:

- the radius follows the Y value: `{face} {X}{ref} {Y} {radius}`;
- the sign belongs to the arc's orientation **in the contour's own plate
  coordinates**: `+` = mathematical (CCW) arc, `-` = CW arc;
- **both endpoints** of an arc carry the same signed radius in the
  worked example (v: `-10.00` on `(190,100)` and `(200,110)`);
- the closing point repeats only X/Y — its radius column stays `0.00`;
- maximum single angle `+/-180°` — a larger arc must be split
  (exporter: larger arcs are skipped with a debug note = AK-2b);
- sharp corners: radius `0.00` (AK-1 behaviour, unchanged).

Exporter sign test (implemented): for the chain pair `P -> Q` and the
projected centre `C`, `cross(P-C, Q-C) > 0` => `+`, else `-`. This
reproduces the `-10.00` notch radius of the HEB400 example.

## API: reading circular edges (Inventor 2026)

- `Edge.Geometry` returns an **`Arc3d`** for `kCircularArcCurve` edges
  and a `LineSegment` for lines — runtime-verified in this project's
  exporter (`ProbeHoleBoundaryLoop`) and used for AK-2;
- `Arc3d` members: `Center`, `Normal`, `Radius`, `StartAngle`,
  `SweepAngle`, `StartPoint`, `EndPoint`, `Evaluator` (all verified by
  reflection on `Autodesk.Inventor.Interop.dll`, Inventor 2026);
- alternative (Autodesk SDK sample `Analyze_CM_Analysis.vb:534`):
  `Edge.CurveType` + `Edge.Curve(CurveTypeEnum.kCircleCurve)` returns
  the full `Circle` (`Center`/`Radius`/`Normal`);
- there is **no 3D `Arc` type** in the API — only `Arc2d`/`Arc3d`;
- an arc is only emitted as a radius when its plane is parallel to the
  plate plane (`|dot(Normal, plateNormal)| >= 0.99`) and the projected
  endpoints keep the same radius as the model arc (orthonormal check).

## Reference notch decoded (p. 22 v block, 2026-09)

The worked example's v contour is emitted starting at `(200,0)`; the
notch region reads (extracted :1074-1079):

```text
  v     0.00o   100.00      0.00
  v 190.00o     100.00    -10.00
  v 200.00o     100.00w   -10.00
  v 200.00o     110.00    -10.00
  v 200.00o      90.00      0.00
  v 200.00o       0.00      0.00
```

So the corner relief is a corner-centred quarter arc:

- theoretical sharp corner = `(200,100)`; the `w` line carries that
  corner's coordinates plus the notch tool/radius (`-10.00`);
- the contour arc runs `(190,100) -> (200,110)`, centre `(200,100)`,
  `R = 10`; both endpoints print `-10.00`;
- `(200,90)` is an ordinary vertex on the `X = 200` line (radius
  `0.00`) — it is *not* an arc endpoint even though it lies on the
  same circle;
- the notch line is not part of the point sequence (p. 14), so the
  contour is `... (190,100) -> (200,110) -> (200,90) -> (200,0)`.

Sign check with the implemented rule
`cross(P-C, Q-C) > 0 => '+'`: `P=(190,100)`, `Q=(200,110)`,
`C=(200,100)` gives `cross = -100 < 0` => `-10.00` — the reference
value. The same rule applied to the (wrong) pair
`(190,100) -> (200,90)` would print `+10.00`, i.e. the rule
discriminates the two.

## w-notch information line (AK-3, implemented + runtime-verified 2026-09-18)

DSTV p. 13-14: an AK notch corner carries an **information line** that is
not a contour point with a radius:

```text
{face} {X}{ref} {Y}w {radius}
```

- the `w` marker is appended **directly to the Y value** (no space):
  `v 200.00u 100.00w 10.00` (p. 22 reference style: `v 200.00o 100.00w -10.00`);
- the line carries the **theoretical sharp-corner coordinates** (200,100)
  plus the notch type (`w` = hole-like, `t` = tangential) and the radius;
- it sits **inside the contour point sequence** at the notch location,
  between the adjacent contour segments — the contour stays closed
  (first point repeated, radius 0.00 on the closing line).

### Exporter representation (verified run, HE 400 B test beam)

A **drilled hole-notch** at the tongue corner produces, in the B-REP, a
contour arc of **270 degrees** around the hole (the fourth quadrant lies
inside the already-removed notch region). Two facts drive the emission:

1. A 270-degree arc **cannot** be emitted as contour arc(s) without
   splitting (max single angle +/-180, p. 13).
2. Inventor parameterises that hole-boundary edge with
   `Arc3d.SweepAngle = 4.712` (270 deg) while the chord endpoints are
   only 90 deg apart — detected via the geometric-angle check in
   `GetPlateArc` and flagged `PlateArc.IsWNotch`.

Emission (`FormatAkBlock`, after CCW orientation): the two consecutive
contour points that are the arc endpoints are **replaced by one point at
the notch centre**, marked `w`, radius = hole radius:

```text
AK
  v 0.00u 100.00 0.00
  v 200.00u 100.00w 10.00
  v 200.00u 0.00 0.00
  ...
```

- both arc-endpoint radius lines disappear (AK-2 endpoint radii are for
  <=180 deg contour arcs only — e.g. the p. 22 quarter-arc case);
- the duplicated hole edge (front/back circular edges of the drilled
  hole project identically) is deduped — the w-line is emitted once;
- fallback: if the endpoints are not consecutive in the contour, the
  code logs `w-notch ... geen w-regel` and leaves the sharp contour
  (visible in debug, never silent).

Status: **RUNTIME-TESTED in Inventor 2026** (exporter output verified
against independent geometry reasoning; debug line
`w-notch R=10.00 op hoek (200.00,100.00)`). Target-viewer import of the
`w` line: **PENDING**.

### Verified viewer observation (2026-09)

Manual testing in the target NC1 viewer confirmed that a sharp-corner rectangular internal opening (50 × 80 mm) represented as an `IK` closed clockwise contour with radius = 0.0 at all corners **passes validation with no warning**, while the same geometry as a `BO` record with `d = 0.00` **fails with 1 validation warning**.

This makes the IK internal contour the verified working representation for sharp-corner internal rectangles in the exporter/viewer combination. This is a viewer-compatibility observation, not a universal DSTV rule — see `blocks/BO.md` for the full evidence and classification.

**Implementation status (verified 2026-09-09):** the exporter uses exactly this representation. A sharp rectangle (4-line closed sketch profile) whose **actual inner edge loop** on the face is still 4 lines / 0 arcs → IK contour (radius 0.0). If the loop shows 4 lines + 4 uniform arcs (3D Fillet-tool rounding) the opening is instead exported as **BO** with `d` = 2 × arc radius — see `blocks/BO.md` "Implementation status". Both paths validated in Inventor 2026 + the target NC1 viewer (no warning).

Related: `knowledge/dstv/nc1/7th-edition/blocks/BO.md` (Alternative-description priority section).
