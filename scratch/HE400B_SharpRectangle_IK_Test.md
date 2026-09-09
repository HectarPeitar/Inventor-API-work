# Manual Inventor Test — Sharp Rectangle IK Export (EXPORT_DSTV2)

## Purpose

Verify that the exporter now writes sharp-corner rectangular internal openings as
closed, clockwise `IK` internal contours instead of `BO ... l ... d=0.00` records,
and that round holes and slots are unchanged.

Basis: target-viewer evidence recorded in
`knowledge/dstv/nc1/7th-edition/blocks/BO.md`, `blocks/AK-IK.md` and
`scratch/diagnostic/HE400B_DiagnosticMatrix.md` (BO `d=0.00` → 1 validation warning;
same geometry as IK contour → no warning).

## Reference sources used for the implementation

- `knowledge/dstv/nc1/7th-edition/DSTV-KNOWLEDGE-MAP.md` (entry point)
- `knowledge/dstv/nc1/7th-edition/blocks/AK-IK.md` — IK contour rules
- `knowledge/dstv/nc1/7th-edition/DSTV-7th-edition-extracted.md` pp. 13–14 —
  IK syntax, closure, clockwise orientation, radius format
- `knowledge/dstv/nc1/7th-edition/DSTV-7th-edition-extracted.md` pp. 21–22 —
  HEB400 worked example (contour point format `face X[ref] Y radius`)

## Test geometry

Test part: `HE400B_CoordinateTest.ipt` (existing test part from the Phase 2/3
coordinate validation). The part must contain:

| Opening | Type | Position (DSTV o/u frame) | Size |
|---|---|---|---|
| Sharp rectangle (top flange) | cut extrude, 4 lines, no corner arcs | centre X=395.00, Y=230.00 | 80 mm (X) × 50 mm (Y) |
| Sharp rectangle (bottom flange) | cut extrude, 4 lines, no corner arcs | centre X=120.00, Y=245.00 | 60 mm (X) × 100 mm (Y) |
| Slot (top flange) | cut extrude, 2 lines + 2 arcs | centre X=150.00, Y=50.00 | d=24.00, centre-to-centre 70.00 |
| Round holes | cut extrude circles / cylinder faces | various | d=10.00 |

If recreating from scratch:

1. Create a part from the HE 400 B (HE400B) stock profile, length 525 mm.
2. Sketch on the top flange face (o): a 50 × 80 mm rectangle with **no corner
   radius**, centred at DSTV X=395.00 / Y=230.00, cut through the flange.
3. Sketch on the bottom flange face (u): a 60 × 100 mm rectangle, centred at
   DSTV X=120.00 / Y=245.00, cut through.
4. Add one 24 mm wide slot (centre-to-centre 70.00) on the top flange and the
   d=10 round holes.
5. Verify the rectangle sketches contain exactly 4 lines and 0 arcs
   (sharp corners — this is what routes them to IK).

## How to run the exporter

1. Open `HE400B_CoordinateTest.ipt` in Autodesk Inventor 2026.
2. Open the iLogic rule `EXPORT_DSTV2` (source:
   `scratch/dstv_exporter.vb`) and run it. `DebugMode` is currently `True`,
   so the diagnostic report also appears (MessageBox + `scratch/DSTV_Debug_Report.txt`).
3. The NC1 file is written next to the part as `<PieceId>.nc1`.

## Expected NC1 output

### Test 1 — sharp rectangle → IK block

- The rectangles must NOT appear in the `BO` block. There must be no
  `... 0.00 0.00l ...` record for them.
- Each rectangle must appear as one `IK` block after the `BO` block, before `EN`.
- Block structure (example for the top-flange rectangle; the walk start corner
  may differ — the checks below are the invariants, not byte order):

```text
IK
  o 355.00u 255.00 0.00
  o 435.00u 255.00 0.00
  o 435.00u 205.00 0.00
  o 355.00u 205.00 0.00
  o 355.00u 255.00 0.00
```

Checks (invariants):

1. `IK` header on its own line; data lines start with two spaces.
2. Each point line: face letter, X, X-reference letter, Y, radius —
   matching the BO record style for the same face.
3. Exactly 5 point lines: 4 distinct corners + first point repeated
   (closed contour; DSTV p. 13: first and last point identical).
4. Radius `0.00` on every point (sharp corners).
5. Corner set = centre ± half-size: X ∈ {355.00, 435.00}, Y ∈ {205.00, 255.00}
   for the 80×50 rectangle (matches the model, no hard-coded values).
6. Orientation clockwise: walking the points, the shoelace signed area
   Σ(x_i·y_{i+1} − x_{i+1}·y_i) must be negative (internal contours are
   described clockwise, DSTV p. 13).
7. Debug report shows `OPENING (rect): ... repr=IK` and one
   `IK contour: face=... corners=(...) closed=yes radius=0.00` line per rectangle.

### Test 2 — round holes unchanged

- Every round hole still exported as a `BO` record, format unchanged:
  `face X[ref] Y d 0.00` (e.g. `o 262.50u 50.00 10.00 0.00`).
- Count and coordinates identical to the pre-change output (Variant A baseline).

### Test 3 — slot unchanged

- Slot still exported as `BO ... l ...`:
  `o 150.00u 50.00 24.00 0.00l 70.00 0.00 0.00`
- `l Width` must remain the verified **centre-to-centre** distance (`70.00`),
  `l Height` = `0.00`. No regression from the F2 correction.

## Validator

Run the project's existing structure validator on the generated file:

```powershell
powershell -File scratch/validate_nc1.ps1 -Path "<part folder>\HE400B_CoordinateTest.nc1"
```

Expected: `RESULT: PASS` (ST block intact, BO grammar valid, IK block lines are
2-space indented and pass the generic block-code checks).

A hand-built expected-structure file with an IK block is available as
`scratch/compile_check/expected_HE400B_ik.nc1` (synthetic — for validator
regression only, not generated output).

## Viewer import

1. Open the generated `.nc1` in the target NC1 viewer (same viewer used for the
   diagnostic matrix tests).
2. Import/validate the piece.

Expected viewer result:

- Test 1: **no validation warning** for the rectangles (previously 1 warning per
  rectangle with the BO `d=0.00` representation).
- Tests 2–3: no new warnings (round holes and slot were already accepted).

## Manual checks summary

- [ ] No `BO` record with `d=0.00 l ...` for either rectangle
- [ ] One `IK` block per sharp rectangle, after `BO`, before `EN`
- [ ] First and last IK point identical (closed contour)
- [ ] 4 distinct corners, radius `0.00` on all points
- [ ] Corner coordinates match the model geometry
- [ ] Point order clockwise (shoelace < 0 or visual check in the viewer)
- [ ] Round holes unchanged (BO records identical to baseline)
- [ ] Slot unchanged (`l 70.00 0.00 0.00` = centre-to-centre)
- [ ] `validate_nc1.ps1` → PASS
- [ ] Target viewer: no validation warning

### Test 4 — filleted rectangle → BO (added 2026-09-08)

Symptom fixed: a rectangle whose sketch has corner fillets (4 lines + 4 arcs)
previously fell through all classification branches and **disappeared from the
NC file entirely**.

Setup:

1. In `HE400B_CoordinateTest.ipt`, add a fillet to **all 4 corners** of a
   rectangle sketch (e.g. r = 5 mm) and re-run the exporter.

Expected:

- The opening **appears** as a BO record — no IK block for it:
  `face X[ref] Y 10.00 0.00l width height 0.00` (r = 5 mm → corner diameter
  `d = 10.00`, matching the viewer-verified d = 10.00 PASS case).
- For the 80×50 rectangle: `o 395.00u 230.00 10.00 0.00l 50.00 80.00 0.00`.
- `l width` / `l height` are the true edge lengths in the DSTV face frame
  (edge line length + 2 × fillet radius); the record center is the average of
  the 4 arc centers.
- Debug: `OPENING (rect-fillet): ... d=10.00 width=50.00 height=80.00 angle=0.00 repr=BO`.
- Viewer: BO with non-zero corner diameter is already viewer-verified
  (d = 1.00 / 10.00 / 20.00 → PASS), so no new viewer risk is expected.

Known limitations (skipped, with `OPENING (rect-fillet): SKIPPED (...)` debug):

- fillets on fewer than 4 corners (not representable as a single BO rectangle);
- non-uniform corner radii;
- non-rectangular 4-line + 4-arc profiles;
- `angle` sign convention for rectangles genuinely rotated within the piece
  face is still viewer-unverified (PENDING F3) — axis-aligned rectangles
  export with angle = 0.00.

### Test 5 — 3D Fillet-tool fillets on a sharp-rect sketch → BO (added 2026-09-08)

Symptom fixed: adding fillets with the **Fillet tool** (not in the sketch) left
the hole as a sharp square — the cut sketch stays a 4-line rectangle, so the
exporter kept routing it to IK radius 0.0 while the actual hole was rounded.

Fix: the exporter now probes the **actual hole boundary loop** on the sketch's
face (`ProbeHoleBoundaryLoop` — the inner `EdgeLoop`, nearest to the rectangle
center). 4 lines + 4 uniform arcs on that loop → the opening is exported as BO
with `d` = 2 × arc radius; 4 lines with no arcs → genuinely sharp → IK (unchanged).

Setup:

1. In `HE400B_CoordinateTest.ipt`, use a **sharp** rectangle sketch, then apply
   the Fillet tool to the 4 hole edges (e.g. r = 5 mm), and re-run the exporter.

Expected:

- The opening is exported as a BO record — **no IK block**:
  `face X[ref] Y 10.00 0.00l width height 0.00` (r = 5 mm → `d = 10.00`).
- `l width` / `l height` = full edge lengths (line length + 2 × r) from the
  loop geometry, in the DSTV face frame.
- Debug shows:
  `OPENING (rect): ... repr=BO-3DFILLET probe=FACE probeLines=4 probeArcs=4`
  and `OPENING (rect-3dfillet): ... d=10.00 width=... height=... angle=0.00 repr=BO`.
- A sharp square without fillets still shows `repr=IK probe=FACE probeLines=4 probeArcs=0`.

Known limitations:

- Sketch on a **workplane** (no face) → probe returns `NO-FACE` → stays IK
  (unchanged behavior; your parts sketch on faces).
- Chamfered corners or mixed radii → loop unrecognized → stays IK with the
  probe counts visible in debug (no regression).
- `angle` sign for genuinely rotated rectangles remains PENDING F3
  (axis-aligned rectangles export `0.00`).

## Run results (2026-09-08, Inventor 2026 — RUNTIME-TESTED)

Actual exports verified programmatically
(`scratch/compile_check/check_ik.ps1` + `scratch/validate_nc1.ps1`):

### `cadfiles/HE400B_CoordinateTest.nc1` (16:11)

- BO: 7 round holes (identical coordinates/format to the Variant A baseline) +
  1 slot `o 150.00u 250.00 24.00 0.00l 70.00 0.00 0.00` (centre-to-centre ✓).
- 2 IK blocks, both **[OK]**:
  - face=o: 5 points, closed=True, 4 distinct corners, radius 0.00,
    shoelace −8000 → CLOCKWISE
  - face=u: 5 points, closed=True, 4 distinct corners, radius 0.00,
    shoelace −12000 → CLOCKWISE
- BO records with `d=0.00 l`: **0**
- `validate_nc1.ps1`: PASS (8 BO records)

### `cadfiles/EURONORM 53-62 - HE 400 B-525.nc1` (16:20, real stock HE 400 B)

- ST profile code `I` resolved from the real designation ✓
- BO: 1 slot `o 150.00u 50.00 24.00 0.00l 70.00 0.00 0.00` (centre-to-centre ✓)
- 1 IK block (u-face rectangle 100×60, centre 120/245): **[OK]** — closed,
  4 corners, radius 0.00, shoelace −12000 → CLOCKWISE; corners match the
  debug report exactly
- BO records with `d=0.00 l`: **0**
- `validate_nc1.ps1`: PASS (1 BO record)

### Result

- Test 1 (sharp rectangle → IK): **PASS** (structural invariants verified on
  real exports; no BO `d=0.00` records anywhere)
- Test 2 (round holes unchanged): **PASS**
- Test 3 (slot unchanged, centre-to-centre): **PASS**
- Viewer: pending explicit confirmation that the target viewer import gives
  **no validation warning**; visual inspection reported "spot on" by the user.

### Final result — ALL PASS (verified 2026-09-09)

Run date: 2026-09-09, file timestamp 12:08, part `EURONORM 53-62 - HE 400 B-525`.

Conditions tested in one part:
- **u-face rectangle**: still sharp (no fillet) → **IK** (closed, clockwise, r=0.00)
- **o-face rectangle**: fillet applied with the **Fillet tool** (r = 5 mm) → **BO** `d=10.00`
- **slot**: unchanged (centre-to-centre `70.00`)

Export result (exact, from `cadfiles/EURONORM 53-62 - HE 400 B-525.nc1`):

```text
BO
  o 150.00u 50.00 24.00 0.00l 70.00 0.00 0.00
  o 395.00u 230.00 10.00 0.00l 50.00 80.00 0.00
IK
  u 70.00u 215.00 0.00
  u 70.00u 275.00 0.00
  u 170.00u 275.00 0.00
  u 170.00u 215.00 0.00
  u 70.00u 215.00 0.00
EN
```

Debug evidence (`scratch/DSTV_Debug_Report.txt`, 12:08):

```text
OPENING (rect): face=u ... repr=IK probe=FACE probeLines=4 probeArcs=0
OPENING (rect): face=o ... repr=BO-3DFILLET probe=FACE probeLines=4 probeArcs=4
OPENING (rect-3dfillet): face=o holeX=395.00u facePos=230.00 d=10.00 width=50.00 height=80.00 angle=0.00 repr=BO
FEATURE (not extrude): Fillet2 type=kFilletFeatureObject
```

Results:

| Test | Result |
|---|---|
| 1 — sharp rectangle → IK, no BO d=0.00 | **PASS** |
| 2 — round holes unchanged | **PASS** |
| 3 — slot unchanged (centre-to-centre) | **PASS** |
| 4 — sketch-filleted rectangle → BO | **PASS** (user-confirmed) |
| 5 — Fillet-tool fillet → BO with d=10.00 | **PASS** (user + debug evidence) |
| Target NC1 viewer import | **PASS — no validation error** (user-confirmed 2026-09-09) |

`DebugMode` is now `False` (production) as of 2026-09-09.

## After verification

- Set `DebugMode = False` in `scratch/dstv_exporter.vb` (production behaviour,
  see `.clinerules/10-coding-standards.md` section 20).
- Record the viewer result in this file and update the diagnostic matrix if needed.
