# HE 400 B DSTV Coordinate System — Manual Regression Test

## Purpose

Verify that the existing DSTV/NC1 exporter produces coordinates consistent with the **verified** DSTV 7th Edition I-profile coordinate system for an HE 400 B profile.

This is a **manual** test performed in Autodesk Inventor 2026. No automated test framework.

## References

- `knowledge/dstv/nc1/7th-edition/coordinate-system.md` (verified I-profile definition)
- DSTV 7th Edition, pp. 7–8 (verified figure interpretation)
- Existing exporter: `scratch/dstv_exporter.vb`

## Verified DSTV I-Profile Coordinate System

From `coordinate-system.md` (DIRECT FIGURE VERIFICATION — DSTV 7th Edition p. 7):

| Element | Definition |
|---|---|
| `Np` | Zero point at the **lower/right** reference point of the I-profile |
| `+X` | Longitudinal, starting from `Np` |
| `+Y` | From `Np` toward the **left** across the section |
| `+Z` | **Upward** from `Np` |
| `T` | Displacement direction (opposite to `+X`) |
| `O` | Top face |
| `U` | Bottom face |
| `V` | Front web |
| `H` | Behind web |

**Consequences:**
- Smallest X-coordinate is `0.0` (at `Np`)
- `O` face at maximum Z; `U` face at minimum Z
- `Y = 0` at the right edge (the `Np` side); `Y` increases toward the left

## Test Environment

- Autodesk Inventor 2026
- Existing exporter: `scratch/dstv_exporter.vb` (iLogic rule, unmodified)
- Test part: HE 400 B, length 525 mm

## Test Part Setup

### 1. Create the part

1. File → New → Standard.ipt (mm units)
2. Save as `HE400B_CoordinateTest.ipt`

### 2. Sketch the I-cross-section

1. Start a 2D sketch on the **XY plane**
2. Draw the HE 400 B cross-section (simplified, no root radii):
   - Overall height: **400 mm** (Y direction)
   - Overall width: **300 mm** (X direction)
   - Flange thickness: **24 mm**
   - Web thickness: **13.5 mm**
3. Position the cross-section so that:
   - Bottom face sits on **Y = 0**
   - Left edge at **X = 0**
   - Right edge at **X = 300**
   - Top face at **Y = 400**
4. Fully constrain the sketch

### 3. Extrude

1. Extrude the profile **525 mm** in the **+Z direction**
2. The beam now runs from **Z = 0** (Np end) to **Z = 525** (far end)

## Test Features

Add the following **10 mm diameter holes** (through all) at the specified positions. Each hole is placed on the named face, dimensioned from the edges.

| Feature | Face | Model X | Model Y | Model Z | Description |
|---|---|---|---|---|---|
| F1 | Top (O) | 75 | 400 | 25 | Top flange, offset from web, near start |
| F2 | Top (O) | 75 | 400 | 500 | Top flange, offset from web, near end |
| F3 | Bottom (U) | 75 | 0 | 262.5 | Bottom flange, offset from web, mid-length |
| F4 | Top (O) | 50 | 400 | 262.5 | Top, near right edge |
| F5 | Top (O) | 250 | 400 | 262.5 | Top, near left edge |
| F6 | Web | 143.25 | 200 | 100 | Web, mid-height, near start |
| F7 | Web | 156.75 | 200 | 425 | Web, mid-height, near end |

**Notes:**
- F1–F3 are at X=75 (not X=150) so they sit clearly on the flange, offset from the web center.
- F6 is on the web face at X=143.25 (web center is X=150, web thickness 13.5, so faces at X=143.25 and X=156.75).
- F7 is on the opposite web face at X=156.75.
- F6 and F7 differ in Z (along the beam length) to verify the web face Z mapping.

**Placement method for each hole:**
1. Select the target face
2. Create a hole (10 mm diameter, through all)
3. Dimension the hole center from the face edges to achieve the target model coordinates

## Expected Results

Derived from the verified DSTV coordinate system (NOT from the exporter):

**Coordinate mapping for this part orientation:**
- DSTV X = model Z (0 to 525)
- DSTV Z = model Y (0 to 400, upward)
- DSTV Y = 300 − model X (0 at right edge to 300 at left edge)

| Feature | Exp. Face | Exp. X | Exp. Y | Exp. Z | Verification |
|---|---|---|---|---|---|
| F1 | o | 25 | 225 | 400 | Top flange, offset from web, near Np end |
| F2 | o | 500 | 225 | 400 | Top flange, offset from web, near far end |
| F3 | u | 262.5 | 225 | 0 | Bottom flange, offset from web |
| F4 | o | 262.5 | 250 | 400 | Top, right side (Y=300−50) |
| F5 | o | 262.5 | 50 | 400 | Top, left side (Y=300−250) |
| F6 | v or h | 100 | — | 200 | Web, mid-height, near start (2nd coord = Z height) |
| F7 | v or h | 425 | — | 200 | Web, mid-height, near end (2nd coord = Z height) |

**Notes:**
- For web features (F6, F7), the second BO coordinate is Z (height), not Y
- F4 and F5 must have Y values that sum to 300 (symmetric about center)
- F1 and F2 prove X increases away from Np (Z=0)
- F3 proves U face is at Z=0

## Manual Test Procedure

### Step 1: Prepare the part
Create the part exactly as described in Test Part Setup. Verify all dimensions.

### Step 2: Add test features
Add all 7 holes (F1–F7) at the specified positions. Double-check each hole's model coordinates using Inventor's measure tool.

### Step 3: Run the exporter
1. Open the iLogic rule `dstv_exporter.vb` in Inventor
2. Run the rule (the part must be the active document)
3. The rule writes the NC1 file to the same folder as the part

### Step 4: Locate the NC1 file
Find `HE400B_CoordinateTest.nc1` in the part's folder.

### Step 5: Inspect the NC1
Open the NC1 file in a text editor. Locate the `BO` block.

### Step 6: Compare records
For each feature, find the matching BO record and compare:

```
Expected format:  face X[ref] Y diameter 0.0
Example:          o 25.00u 150.00 10.00 0.0
```

### Step 7: Record results
Fill in the test record (see Recording Format below).

## Test Matrix

### X axis
| Check | Feature | Expected | Pass Criteria |
|---|---|---|---|
| X=0 location | F1 | X ≈ 25 (near Z=0) | X increases with model Z |
| X direction | F2 | X ≈ 500 (near Z=525) | X > F1.X |
| X range | F1, F2 | 25 to 500 | Consistent with 525 mm length |

### Z axis
| Check | Feature | Expected | Pass Criteria |
|---|---|---|---|
| O face = top | F1, F2, F4, F5 | face = o, Z = 400 | Top face at max Z |
| U face = bottom | F3 | face = u, Z = 0 | Bottom face at min Z |
| Z direction | F1 vs F3 | F1.Z > F3.Z | Z increases upward |

### Y axis
| Check | Feature | Expected | Pass Criteria |
|---|---|---|---|
| Y=0 at right edge | F4 | Y ≈ 250 | Right side (X=50) → Y=300−50 |
| Y increases left | F5 | Y ≈ 50 | Left side (X=250) → Y=300−250 |
| Y symmetry | F4, F5 | F4.Y + F5.Y = 300 | Symmetric about center |

### Web faces
| Check | Feature | Expected | Pass Criteria |
|---|---|---|---|
| V/H assignment | F6, F7 | face = v or h | Web faces classified |
| Z preserved | F6, F7 | Z ≈ 200 | Height coordinate correct |

## Manual Recording Format

```
========================================
HE 400 B Coordinate System Test Record
========================================
Date:
Inventor version: 2026
Test part: HE400B_CoordinateTest.ipt
Exporter: dstv_exporter.vb (unmodified)

Feature | Exp Face | Exp X | Exp Y | Exp Z | Act Face | Act X | Act Y | Act Z | PASS/FAIL
--------|----------|-------|-------|-------|----------|-------|-------|-------|--------
F1      | o        | 25    | 225   | 400   |          |       |       |       |
F2      | o        | 500   | 225   | 400   |          |       |       |       |
F3      | u        | 262.5 | 225   | 0     |          |       |       |       |
F4      | o        | 262.5 | 250   | 400   |          |       |       |       |
F5      | o        | 262.5 | 50    | 400   |          |       |       |       |
F6      | v/h      | 100   | —     | 200   |          |       |       |       |
F7      | v/h      | 425   | —     | 200   |          |       |       |       |

Overall result: PASS / FAIL
Notes:
========================================
```

## Manual Verification Record

**MANUALLY VERIFIED IN AUTODESK INVENTOR 2026**

| Field | Value |
|---|---|
| Date | 2026-09-08 |
| Inventor version | 2026 |
| Test part | HE400B_CoordinateTest.ipt |
| Exporter | scratch/dstv_exporter.vb |
| Exporter commit | `0356435` — Phase 3: fix slot width (F2) and rectangle O column (F3) |
| Result | **PASS** |

### Actual Results

```
BO
  h 425.00u 200.00 10.00 0.00
  v 100.00u 200.00 10.00 0.00
  o 262.50u 50.00 10.00 0.00
  o 262.50u 250.00 10.00 0.00
  u 262.50u 225.00 10.00 0.00
  o 500.00u 225.00 10.00 0.00
  o 25.00u 225.00 10.00 0.00
```

### Fixture Results

| Feature | Expected | Actual | Result |
|---|---|---|---|
| F1: top flange, near start | o, X≈25, Y=225 | o 25.00 225.00 | PASS |
| F2: top flange, near end | o, X≈500, Y=225 | o 500.00 225.00 | PASS |
| F3: bottom flange | u, X≈262.5, Y=225 | u 262.50 225.00 | PASS |
| F4: top, right edge | o, X≈262.5, Y=250 | o 262.50 250.00 | PASS |
| F5: top, left edge | o, X≈262.5, Y=50 | o 262.50 50.00 | PASS |
| F6: web, near start | v/h, X≈100, Z=200 | v 100.00 200.00 | PASS |
| F7: web, near end | v/h, X≈425, Z=200 | h 425.00 200.00 | PASS |

### Verified Behaviors

| Check | Result |
|---|---|
| X increases with model Z (F1=25 < F2=500) | PASS |
| Y = 300 − modelX (F4: 50→250, F5: 250→50) | PASS |
| Y symmetry (F4.Y + F5.Y = 300) | PASS |
| o = top face, u = bottom face | PASS |
| Web faces classified as {v, h} | PASS |
| Web Z height preserved (200) | PASS |

---

## Golden NC1

The verified NC1 file is stored at:

`scratch/golden/HE400B_CoordinateTest_GOLDEN.nc1`

This file is a **regression reference only**. It is not independent proof of the DSTV specification. The specification (`knowledge/dstv/nc1/7th-edition/coordinate-system.md`) and verified DSTV coordinate-system knowledge remain the source of truth.

Future exporter changes can diff their output against this golden file to detect regressions.

## Acceptance Criteria

The test **PASSes** only if ALL of the following hold:

1. All top-flagged features (F1, F2, F4, F5) have face = `o` and Z ≈ 400
2. Bottom feature (F3) has face = `u` and Z ≈ 0
3. X coordinates increase with model Z (F1.X < F2.X)
4. Y coordinates: F4.Y + F5.Y = 300 (within rounding tolerance of 0.01)
5. Web features (F6, F7) have face = `v` or `h` and Z ≈ 200
6. No feature has an unexpected face assignment

**Tolerance:** ±0.05 mm for all coordinates (Inventor rounding).

## Scope Restrictions

This test does NOT modify:
- Exporter code
- Coordinate calculations (GetDstvX/Y/Z)
- GetFaceNormal
- GetDstvXref
- Slot handling
- BO/ST/AK/IK/SC/SI/PU/KO

## Remaining Limitations

- The test verifies coordinate **ranges and directions**, not absolute model-to-DSTV origin offset (the exporter uses OBB min/max, which for a prismatic part coincides with the theoretical envelope)
- Web face assignment (v vs h) depends on model orientation; the test only verifies both web faces are classified as {v, h}
- Root radii are omitted from the test profile for simplicity