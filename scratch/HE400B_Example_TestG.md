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
