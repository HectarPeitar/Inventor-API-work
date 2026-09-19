# Test G — Example Beam (DSTV pp. 21-22) Golden Comparison

Working notes for the HEB400 2000 mm worked-example beam (reference NC1, p. 21).

## NOTE-1: Slot X anchor convention (2026-09)

Discrepancy between the example NC1 and the exporter output for the flange slot:

- Example NC1: `u/o 1415.00s 251.50 24.00 0.00l 70.00 0.00 0.00` — X = 1415
- Exporter:    `o 1450.00u 252.00 24.00 0.00l 70.00 0.00 0.00` — X = 1450

Both describe the SAME physical slot. The `l`-field 70.00 is centre-to-centre
(resolution F2, verified earlier in `blocks/BO.md`). The example therefore anchors
X at the slot START edge (1415 + 70 c-t-c -> centre 1450), while the exporter
anchors X at the slot CENTRE (1450).

The target viewer accepts the exporter's centre-anchored record and places the
slot correctly. Decision: keep the exporter's centre-anchor convention for now;
do NOT treat the example as erroneous — it is a different anchor convention
(start-edge vs centre). Revisit only if a future post-processor misplaces slots.

## NOTE-2: Weight / painting surface (2026-09)

ST weight and painting-surface fields (format table, extracted :387-388: kg/m and
m2/m — per METER values):

- Example NC1: 155.000 / 1.930 = nominal catalog values of the FULL HEB400 profile
- Exporter:    computed from actual B-REP mass: Inventor total mass 263.68 kg
  / 2.000 m = 131.841 kg/m (includes all removed material: holes, slots, copes)

Decision (2026-09): KEEP the computed actual values (truthful for the real piece,
viewer-accepted). The deviation vs the example's catalog values (155.000/1.930)
is an ACCEPTED DIFFERENCE, not a defect. Catalog lookup would require a profile
database — out of scope unless a future post-processor requires nominal values.

## NOTE-3: Extrusion5 = 200 x 100 cope with notched corner (2026-09)

User confirmation: Extrusion5 is a 200 x 100 mm cope with a notch in one corner,
modeled like the notch example on p. 14 (extracted :696-721: AK contour with
`w`/`t` notch line + radius).

This corresponds to the reference beam's near-end web cope: the v-face AK
outline contains the tongue/step region with the hole-like notch (`w`) and R10
radius at the tongue base corner — i.e. the reference represents this cope
INSIDE the external contour, not as a separate opening.

Exporter status: the cope was misclassified and mis-measured as
`h 1000.00u 362.50 0.00 0.00l 75.00 2000.00 0.00` (h-face "slot", size 2000 x 75
instead of 200 x 100, face h instead of v). Stage 2 must absorb cope cut-extrudes
into the face's external contour (AK) with the notch line, instead of emitting
BO records.

## STAGE 2 IMPLEMENTATION STATUS (2026-09)

Implemented in `scratch/dstv_exporter.vb` (BUILT, vbc compile PASS; runtime
validation in Inventor 2026 PENDING):

1. Per-face slot emission (fixes missing u-face slot): new helpers
   `GetFaceLetterFromNormal` + `GetOtherPiercedFaces` (parallel-face +
   inner-loop + center-projection match); the SLOT branch now emits one
   BO record per pierced face. Also fixes the future v-face slot if it
   pierces parallel faces.
2. Staircase (multi-level end) rule (fixes flangeEnd = -18.43): a
   length-aligned section end plane NOT touching the length tip, with
   Y/Z extent >= half section width/height, marks that end as
   STAIRCASE -> ST skew fields forced to 0.00 (contour material, AK),
   debug: "STAIRCASE ...". Full-section skew (Test B/C) still detected
   via the tip faces.

PENDING (Stage 2 continued): AK external-contour emission (absorbs the
cope openings + staircase end segments, arcs, `w`/`t` notch line,
welding-prep couples, per-face X-ref letters); SI (Stage 3).

## API ERROR (verified + fixed, 2026-09): Face.Loops / EdgeLoop.IsOuter

Runtime error: "Public member 'Loops' on type 'Face' not found."
- Correct member: `Face.EdgeLoops` (collection of EdgeLoop)
- Correct member: `EdgeLoop.IsOuterEdgeLoop` (NOT IsOuter)
- Verified via reflection on Autodesk.Inventor.Interop.dll (Inventor 2026)
  and SDK sample Samples_VC_STD_ApprenticeServer_BRepTraversal (:206,
  get_EdgeLoops). Compiled late-bound, so vbc did NOT catch this.
- Lesson: late-bound iLogic compiles pass with wrong member names;
  verify B-REP member names against the interop DLL (reflection) or
  the BRepTraversal sample BEFORE runtime testing.

## ILOGIC COMPILE QUIRK (2026-09): single-letter parameters

iLogic rule compiler error: "'b' is not declared. It may be inaccessible
due to its protection level." (one error per use) on the only two
functions whose parameters were SINGLE-LETTER names (a, b, o) — while
functions with multi-character parameter names compiled fine even with
two parameters on one continuation line. Raw vbc (standalone harness)
passes both forms, so this is an iLogic pre-compiler quirk, not VB.

Rule: in iLogic rule code avoid single-letter parameter/local names;
use descriptive names (pA, pB, pO). Fixed in ComparePoint2d and Cross2.

## STAGE 2 SLOT ITEM CLOSED (2026-09)

NC1 confirmed: `u 1450.00u 251.50 24.00 0.00l 70.00 0.00 0.00` present
alongside the o record (12 BO records). [pierce] log: MATCH face=u,
projDistCm=0.00, dedupe correct.

Stage 2 BO summary:
- all round holes + slot on both faces: matches reference pattern
- remaining BO deviations (pending AK absorption): `v 1558.03...`
  (rect-fillet cope) and `h 1000.00u 362.50 ...l 75.00 2000.00`
  (Extrusion5 cope, misclassified as h-face slot)
- X-ref letters `u` vs reference `o`/`s`: pending AK-3

## RUN 3 (2026-09): AK-1 first output + h-record root cause + v redefinition

First AK runtime output. Findings vs reference (extracted :1065-1101):

1. **u-AK matches** reference (200/1900/2000/300 + diagonal) except one
   extra collinear hull point (1961.25,183.75) = root-fillet tangent
   vertex exactly ON the diagonal; kept by a float-e hull-pop. FIX:
   RemoveCollinearPoints2d (sin < 1e-6) applied to the hull output.
2. **o-AK matches** (159.52≈159.50, 1750) except micro-vertex (164,0)
   = the model's real start-bevel edge (top 164.00 / underside 159.52,
   10.5° like the reference's 10.2° bevel); same fix merges it. R10
   corner arc missing = AK-2.
3. **v-AK structural mismatch**: reference AK(v) = FULL side view
   (depth 0-400, start tongue at X=0 spanning heights 100-325, start
   bevel (163.5,400)->(150,325), end staircase 1952/350/1750, notched
   cope w/t + R10) — NOT the web-face loop (51-349) we emitted. FIX:
   GetSideViewOutline replaces GetWebPlateContour for the v block:
   X-Z projection outline via slab sweep (per-X min/max envelope of
   all projected edges; breakpoints at edge endpoints).
4. **h-record root cause CLOSED**: `h 1000.00u 362.50 ...l 75.00
   2000.00` is bogus — its own debug line shows probe= probeLines=0
   probeArcs=0 (no cut edges on face h) and the AK contours prove no
   material removed near X=1000. Legacy BO-QUAD path emitted from
   sketch geometry without intersection evidence. FIX: BO-QUAD
   emission now requires probeLines+probeArcs > 0, else SKIP with
   debug line. Expect Extrusion4 -> "OPENING (rect): SKIP".
5. **NOTE-4 (deliberate deviation)**: reference v bottom edge ends at
   1952 (plan-diagonal cut crossing the web) although its own u
   contour proves the bottom flange reaches X=2000 at the far width —
   the example is internally inconsistent at this corner ("cut path on
   the side plate" idealization). We emit the true projection outline
   (flange tip included: bottom edge to 2000, step at the tip).
6. X-ref letters: reference uses 'o' for the v block, 's' for u/o
   blocks; we emit 'u' everywhere — AK-3 scope.
7. ST skew 0.00 x4 matches reference ST; BO hole/slot set matches
   reference pattern (v 900/300 + 450/280, o/u slot + 3 holes).

## RUN 4 (2026-09): h-record suppressed; u/o EXACT; v side view decoded

1. **h-record GONE**: "OPENING (rect): SKIP (geen snijranden op vlak h)"
   emitted for Extrusion4; BO records 12 -> 11. BO-QUAD guard verified.
2. **u-AK = reference EXACTLY**: (200,0),(1900,0),(2000,300),(200,300).
3. **o-AK = reference** (159.52 vs 159.50 rounding; R10 corner arc = AK-2).
4. **v-AK = full side view, structure matches reference**: tongue at
   X=0 spanning heights 100-325 (EXACTLY the reference), tongue bottom
   edge (0,100)->(190,100) (reference identical), start bevel
   (164,400)->(150,325) (reference 163.5/150/325), staircase shoulder
   at Z=350 (reference identical), END BEVEL (1900,350)->(1750,400) =
   atan(50/150) = 18.43 deg — THE SAME angle the reference encodes as
   the (-18.430, 13.50) couple on its (1952,0) contour point (AK-4:
   welding-prep couples). The model replicates the reference geometry.
5. Defect found + fixed: sweep emitted leaning segment
   (1961.25,24)->(1952.25,350) across an envelope jump (phantom wedge
   above Z=24 between 1952.25-1961.25). Fix: per-breakpoint LEFT/RIGHT
   envelope values (vertical edges excluded from side values); jumps
   emitted as two points on the same X. Expected v chain now:
   ...(2000,24),(1952.25,24),(1952.25,350),(1900,350)...
6. Model-vs-reference note: our cope root is the plain diagonal
   (190,100)->(200,0); reference draws the notch with w/t lines + R10
   (kerf through the root). Verify visually whether the modeled cope
   corner is a plain diagonal or carries the p.14 notch; if the notch
   exists in the model it should appear as extra contour vertices.
7. Remaining: AK-2 (R10 corner arc on o; fillet/arc radii), AK-3
   (x-ref letters o/s/u vs reference 'o'/'s'; w/t notch line), AK-4
   (the (-18.430,13.50)-style bevel couples), SI (stage 3).

## RUN 5 (2026-09): side-plate clip; bevel-through confirmed by user

User observations on RUN 4 output:
1. Model's tongue root = the notch (like the reference); viewer showed
   a diagonal. CONFIRMED cause: the notch's R10 arc is chorded by the
   sweep (start/stop vertices only) -> the diagonal (190,100)->(200,90)
   is the arc's CHORD. The jump fix already revealed the notch extent
   (point 200,90 = reference's (200,90)). Fix belongs to AK-2 (arc
   support: emit radius instead of chord; reference marks it with the
   -10 sign) + AK-3 (w/t notch line). NOT an envelope bug.
2. End bevel: "runs all the way through the beam" in the model but
   displayed only at the bottom in the v contour. CAUSE: our v contour
   was the TRUE projection silhouette (flange tip wedge to 2000 +
   leaning fillet segment), while the reference renders a through-all
   plan cut in the side plate as the VERTICAL LINE at its web crossing
   (reference: 1952). FIX (side-plate semantics, reference-exact):
   GetSideViewOutline now clips all projected segments to the X-range
   of the WEB faces (GetSideViewOutline got yUnit/minY/maxY/
   dWebThickMm params). No-op for plain square ends (web spans full
   length). Debug: "[AK] v: zijplaat geknipt op lijf-X .. ..".

Expected v block now (11 pts + closure):
  (0,100),(190,100),(200,90),(200,0),(1952.25,0),(1952.25,350),
  (1750,350),(1750,400),(164,400),(150,325),(0,325)
- bevel = full-height vertical at 1952.25 (the model's web crossing;
  reference 1952.00 at their web) -> user issue resolved
- NOTE-4 RESOLVED: bottom edge now ends at 1952.25 like the reference
  (flange-tip wedge and (1961.25,24) gone); the earlier "deliberate
  true-projection deviation" is superseded by reference semantics.
- remaining deltas vs reference are notation-level: R10 arc (AK-2),
  w/t notch line + x-ref letters (AK-3), prep couples (AK-4).

## RUN 7 (2026-09): AK-2 arcs implemented (straal + teken)

- New: PlateArc, MapToPlate, GetPlateArc, CollectPlateArcs,
  AttachArcRadii; FormatAkBlock now emits the radius column.
- Geometry source: Edge.Geometry -> Arc3d (runtime-verified pattern in
  this file); arc must lie in the plate plane and be <= 180 deg.
- Sign rule: cross(P-C, Q-C) > 0 => '+', else '-' — spec-confirmed
  ("the sign + is the mathematical orientation", extracted :617) and
  reference-confirmed (see below).
- Both arc endpoints get the same signed radius (reference p. 22);
  closure point keeps radius 0.00.
- Debug per run:
    [AK] boog R=.. teken .. op (..)-(..)        (attached)
    [AK] boog R=.. niet in contour ((..)-(..))  (not a contour pair)
    [AK] v (zijaanzicht): <n> punten, <m> randen, <k> bogen
    [AK] o/u: hull <n> punten, <k> bogen

### RUN 7a (first attempt) — FAIL / NRE, fixed

Symptom: `[AK] v EXCEPTION: Object reference not set to an instance of
an object.` and every emitted radius stayed 0.00.

Cause: `arcRadii` was declared `ByRef` in GetSideViewOutline but only
initialised inside GetFlangePlateHull, so the tail loop `arcRadii.Add`
hit Nothing. The v points were already built, so the block still looked
normal while all radii silently fell back to 0.00.

Fix: initialise `arcRadii = New List(Of Double)` at the top of
GetSideViewOutline (comment records why) + defensive count guard in
AttachArcRadii. vbc PASS.

Two other RUN 7a facts, both correct behaviour:
- 2 arcs > 180 deg skipped for the v plate = the two v-face holes
  (D29 @ 900/300 and D24 @ 450/280, full 360 deg circles) -> those are
  BO records, not contour arcs. OK.
- 8 x R12 arcs "niet in contour" per plate family = the flange slot
  corner rounds (X 1415..1485, Y/z 239.50..263.50). The slot is given
  by the plate BO record, so it must NOT enter the plate contour. OK.

### Reference notch decoded (definitive, extracted :1074-1079)

    v     0.00o   100.00      0.00
    v 190.00o     100.00    -10.00
    v 200.00o     100.00w   -10.00
    v 200.00o     110.00    -10.00
    v 200.00o      90.00      0.00
    v 200.00o       0.00      0.00

- arc = quarter circle centred on the theoretical corner (200,100),
  from (190,100) to (200,110), R10, both endpoints -10.00;
- cross((190,100)-(200,100), (200,110)-(200,100)) = -100 => '-10.00'
  — the implemented rule reproduces the reference exactly;
- the `w` corner line sits at the theoretical corner (200,100) and is
  NOT part of the point sequence (AK-3);
- (200,90) is an ordinary vertex (radius 0.00);
- the reference o block `o 159.50s 0.00 0.00 10.000 0.00` has THREE
  numbers after Y => radius 0.00 + welding-prep couple (10.000, 0.00)
  (AK-4), i.e. the o plate corner is SHARP, confirming that our 4-point
  o/u hulls are right and that no o/u contour arc is expected here.

### RUN 7b (second attempt) — NRE gone, but the notch arc is still rejected

Result: no exception; `v (zijaanzicht): 11 punten, 82 randen, 8 bogen`;
NC1 unchanged (all radii 0.00).

What the collector actually saw for the v plate:
- 2 arcs > 180 gr skipped = the two v-face holes (360 gr circles, BO
  records) -> correct;
- 8 x R24 arcs = the rotated rect-fillet opening on face v
  (`v 1558.03u 182.23 48.00 0.00l 148.00 108.00 9.96`, d = 2 x 24)
  -> correctly rejected as "niet in contour";
- o/u: 8 x R12 each = the flange slot corner rounds (BO record)
  -> correctly rejected.

CONCLUSION: zero false positives (good), but the notch's R10 arc is
NOT reaching the collector, while NOTE-1 above (user-verified) says the
model's notch IS an R10 arc (our diagonal is its chord). So the loss
happens in a silent rejection path, not in the geometry.

Silent paths found and instrumented (all three now report):
1. `|dot(arc normal, plate normal)| < 0.99` -> was `Return Nothing`
   with no message. Now logs when `dot >= 0.5` (nearly-in-plane arcs,
   the dangerous case; perpendicular arcs stay silent to avoid noise):
   `[AK] boog buiten plaatvlak genegeerd (R=.. dot=.. (..,..)-(..,..))`
2. non-arc/non-line curve (spline, ellipse, or `Edge.Geometry` throw):
   now counted -> `[AK] <n> randen met niet-boog krommetype genegeerd`
3. `radii` count mismatch in AttachArcRadii: now a guarded return.

Prime suspect: the notch belongs to the cope (Extrusion5, 200 x 100) and
the rotated cut (angle 9.96 in the BO record) makes the arc's plane
slightly non-parallel to the v plate: dot ~ 0.985 would fall in
[0.5, 0.99) -> exactly what the new line 1 reports. vbc PASS.

### RUN 7c — what to check (expected)

Run the rule again and read only the [AK] lines. Three possible outcomes,
each naming the next action:

A. `[AK] boog buiten plaatvlak genegeerd (R=10.00 dot=0.9xx (190.00,100.00)-(200.00,90.00))`
   -> the notch arc EXISTS but its plane is tilted (cope cut), so the
   in-plane guard drops it. Fix = AK-2b: accept a documented tilt
   tolerance (e.g. dot >= 0.90) and emit the projected arc, or keep the
   chord and record the limitation. Needs a decision.
B. `[AK] <n> randen met niet-boog krommetype genegeerd` with n > 0
   -> the notch edge is not a circular arc (spline/ellipse or an
   unreadable geometry) -> the model needs a real arc (sketch fillet)
   for AK-2 to be exercised at all.
C. neither line, but `K bogen` still 8 and nothing attached
   -> the notch edge is a straight line in the model (the diagonal is
   the true geometry, not a chord) -> then AK-2 must be exercised with a
   model that really has a rounded corner.

In all three cases the expected AK-1 behaviour is unchanged: v = 11
points, u/o = 4-point hulls, all radii 0.00 except any attached arc.

Status: BUILT (vbc PASS). Runtime validation of AK-2 PENDING (run 7c).

### RUN 8 (2026-09) — rect-fillet regressie: 9.96 → -100.00 door 3D-fix + min-hoek-keuze

Symptoom (debug): `OPENING (rect-fillet): face=v holeX=1558.03u facePos=182.23
d=48.00 width=60.00 height=100.00 angle=-100.00 repr=BO` en NC1:
`v 1558.03u 182.23 48.00 0.00l 60.00 100.00 -100.00`.
Referentie p.21: `v 1512.00o 144.00 24.00 0.00l 100.00 60.00 10.00`
(X/Y = centrum onderste-linker gat, breedte = LANGE zijde).

Oorzaken (twee, samenvallend):
1. `ComputeFaceFrameAngleFromVector` gebruikte een andere conventie dan
   `GetDstvFaceFrameAngle`: generieke `cross(faceNormal, xUnit)`-Y-as en
   bereik (-180, 180] i.p.v. de per-vlak conventie (v/h: Y=+Z; o/u: Y=-Y)
   met bereik [0, 180). Op het v-vlak draait dat de hoek ~110° weg
   (10.00 → -100.00-modulo-180-verwarring).
2. Breedte-keuze `angleA <= angleB` (kleinste hoek) i.p.v. langste zijde;
   referentie p.21 toont 100.00 x 60.00 @ 10.00 = lange zijde eerst.
3. Positie = rechthoekcentrum i.p.v. onderste-linker boogmiddelpunt
   (1512.00/144.00 vs 1558.03/182.23); maten = rechte randlengte i.p.v.
   volle buitenmaten (100.00/60.00 zijn rond → volle maten, niet
   centre-to-centre).

Fix (alleen `scratch/dstv_exporter.vb`, vbc PASS):
- helper herschreven naar exact de `GetDstvFaceFrameAngle`-conventie;
- breedte = lange zijde (`lineLenA_Mm >= lineLenB_Mm`), hoek = richting
  daarvan; zelfde voor `BO-3DFILLET` (`fullW0/fullW1` = rand + d);
- positie = onderste-linker boogmiddelpunt (min X, dan min Y in DSTV-frame);
- `l width/height` = rechte rand + d (volle buitenmaten, p.21).
- Slot/stadium-conventie (centre-to-centre, `l 70.00 0.00 0.00`) ongewijzigd;
  geldt alleen voor echte slots, niet voor afgeronde rechthoeken (BO.md).

Status: BUILT (vbc PASS). Runtime-validatie RUN 8 PENDING (her-run in Inventor).

## AK PLAN (approved direction, 2026-09; v-row superseded by RUN 3 #3)

Plate concept (extracted :626-637): each DSTV face = ideal plate; its
external contour is the projected chain of the B-REP side faces inside
the slab band. Cope cut-extrudes dissolve into the chains (no more
separate-feature misclassification).

| Plate | Slab band | Side faces in band |
|---|---|---|
| o | Z 376-400, Y 0-300 | normals +-Y, +-X |
| u | Z 0-24, Y 0-300 | normals +-Y, +-X |
| v | Y 143-156.5, Z 24-376 | normals +-Z, +-X |

Sanity vs reference: u-AK = 4 corners + diagonal (matches); v-AK gets
the cope steps + notch corner from Extrusion5 side walls.

Sub-phases:
- AK-1: sharp-corner plate outline (slab-band collection -> edge
  chains -> CCW -> emit). Exit: u-AK matches reference; cope BO
  records suppressed.
- AK-2: arc edges -> radius field + sign.
- AK-3: notch line (w/t) + X-ref letter differentiation (o/s/u).
- AK-4: welding-prep couples (bevel faces at contour points).

Scratch cleanup 2026-09: removed page renders (knowledge/_renders has
them), DSTV_Debug_Report.txt, test_sample.nc1, diagnostic/ variants,
compile_check build artifacts (dll/harness). Kept: exporter, test
evidence docs, golden files, compile_check.ps1, validate_nc1.ps1,
check_ik.ps1 + expected ik nc1.
