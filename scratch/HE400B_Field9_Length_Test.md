# Manual Test - DSTV ST Field 9 Length Semantics (Skew Cuts)

Status: MANUAL TEST PROCEDURE (Autodesk Inventor 2026 + target NC1 viewer)
Date: 2026-09

Objective: verify whether the existing single-value ST Length (field 9) remains
correct when skew cuts are present. Saw Length is NOT implemented in this task;
it is treated as a separate concept and its values are calculated only as reference.

The exporter is NOT modified in this test. Expected exporter output below is
based on the current code: field 9 = overall piece extent (maxX - minX),
single value, no saw length appended.

## Source basis (MCP knowledge; the original PDF is not consulted)

- `knowledge/dstv/nc1/7th-edition/DSTV-7th-edition-extracted.md` :381
  field 9 format: `2x, f [, f]  Length , Saw Length  <mm>` (a second, optional value)
- same file :403-406: "If an Rough length is necessary for the workshop, this one is
  introduced behind the normal length as Saw length. The saw length is the length
  between the teorical points. We will always take the shortest one."
- `DSTV-KNOWLEDGE-MAP.md` :97: "the smallest X coordinate of the piece is 0.0"
  (the piece occupies X in [0, Length])
- `examples.md` (HEB400 worked example): field 9 = single value `2000.00`,
  square ends, saw length omitted

Concepts kept distinct:

1. Length (value 1) = the normal piece length (overall piece extent under test).
2. Saw Length (optional value 2) = shortest distance between theoretical points;
   workshop rough length; only introduced "if necessary". NOT emitted here.
3. Physical OBB extent - what the current exporter computes.
4. Cut-plane geometry - what the skew fields 17-20 describe.

## Test part and geometry

Profile: HE 400 B (height 400.00, flange width 300.00, flange thickness 24.00,
web thickness 13.50, radius 27.00). Baseline part: the existing 525.00 mm
HE 400 B test part (e.g. `cadfiles/HE400B_CoordinateTest.ipt`).

All cuts are SIMPLE PLANAR WEB-VIEW cuts: one plane, 15 deg in the front (web)
view, no side lean, no cope, no mitre.

How to create a 15 deg web cut (Test B, START/minX end):
1. Sketch on the front web face (v) at the start end: a line at 15 deg to the
   piece axis, across the full section height.
2. Cut-extrude through all, removing the wedge; one planar skewed end face remains.
   (Deterministic alternative: work plane at 15 deg about the width axis through
   the start-end section + Split, discarding the wedge.)
3. Recompute the model.

Test C: apply the same 15 deg web cut at the END/maxX end as well (second
independent plane, so both ends are skewed; the piece is short on both web edges).

## Independent expected-value calculations (never derived from the exporter)

Formula: a planar skew cut at angle A across a section dimension D shifts the cut
plane's X position by D x tan(A) between the tall and short side of the section.

- shortest theoretical-point distance per skewed end: L_short = L_long - D x tan(A)
- D = profile height 400.00 for a web cut; tan(15 deg) = 0.2679491924
- per 15 deg web skew: 400.00 x 0.2679491924 = 107.18 mm

| Test | Overall piece extent L_long | Shortest theoretical-point distance (Saw Length reference) |
|---|---|---|
| A (square) | 525.00 | 525.00 (equal - both values coincide on square ends) |
| B (one 15 deg web skew) | 525.00 | 525.00 - 107.18 = 417.82 |
| C (two 15 deg web skews) | 525.00 | 525.00 - 214.36 = 310.64 |

Independent measurement in Inventor (sanity check per test): measure the X
positions of the flange-face corner pair at the cut end (tall side vs short
side); the difference must equal 107.18 per 15 deg web skew. Do not take this
value from the exporter.

## Expected CURRENT exporter output (code unchanged)

| Test | Field 9 | Fields 17-20 |
|---|---|---|
| A | `525.00` | `0.00 / 0.00 / 0.00 / 0.00` |
| B | `525.00` | webStart = -15.00 or +15.00 (verified sign convention, depends on lean direction); webEnd = 0.00; flangeStart/End = 0.00 |
| C | `525.00` | webStart and webEnd non-zero with OPPOSITE signs (verified convention); flange fields 0.00 |

The calculated Saw Length values (417.82 / 310.64) are recorded as REFERENCE ONLY
for the separate Saw Length concept. They are NOT appended to field 9 in this task.

## Manual validation steps (per test)

1. Create/verify the geometry (Test A: unmodified part; B: one cut; C: both cuts).
2. Independently measure the 107.18 difference in Inventor.
3. Run the exporter (DebugMode may stay True; the debug report shows the
   detected end cuts and skew fields).
4. Inspect the generated NC1: the ST field 9 line (10th ST line) and skew
   fields 17-20 (the 4 lines after field 16). No `SC` and no `AK` block should
   appear for these pieces (header describes them completely).
5. Import the NC1 into the target NC1 viewer. Note the rendered piece length
   and the slope direction; note any validation warning.
6. Record the block below.

Recording block (fill in per test):

```
Test:
Generated Length:
Calculated theoretical Saw Length:
Viewer result:
Warning:
```

Note: a viewer result is an observation of this viewer's behavior. It does not
by itself validate DSTV semantics; the spec text (extracted :381, :403-406)
remains the semantic basis. The p. 9-10 Length/Saw-length figure is
figure-dependent and was not visually decoded.

## Decision rule (after the manual tests)

- Viewer accepts `525.00` for the skewed parts (B, C) and represents the piece
  correctly -> the current exporter stays UNCHANGED and the Length investigation
  closes: Length = overall piece extent; the optional Saw Length remains omitted
  (consistent with the worked example and the "if necessary" wording).
- Viewer rejects `525.00` or clearly interprets Length differently -> report
  that evidence separately; reconsider the semantics before any code change.

The optional Saw Length value is NOT added unless a separate later task decides
the workshop workflow requires it.

## Restrictions honored in this task

No modifications to: `scratch/dstv_exporter.vb`, ST fields, the verified
skew-angle implementation, SC, AK, IK, BO, knowledge, `.clinerules`.
Only this test procedure was created.
## RESULT (2026-09) - INVESTIGATION CLOSED

Tests A/B/C executed manually in Inventor 2026 (square / one 15 deg web skew /
two 15 deg web skews). Generated field 9 = 525.00 in all three tests; the target
viewer accepted the results and represented the pieces correctly.

Decision: the current single-value ST field 9 implementation stays UNCHANGED.
Length = overall piece extent (confirmed for skew-cut members). The optional Saw
Length is recorded as a FUTURE/SPECIAL-CASE capability only (workshop rough
length; never needed unless the workshop workflow explicitly requires it).
Field 9 is not revisited unless new evidence requires it.
