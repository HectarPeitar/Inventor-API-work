# Implementation Plan — AK `t`-notch information line (t-branch)

## Overview

Add a `t`-notch information-line branch to `FormatAkBlock` in `scratch/dstv_exporter.vb`, so that a ≤180° **notch** arc (concave, tangent-joined, corner-relieving) is emitted as: approach row with signed radius, `t` information line at the **theoretical sharp corner**, departure row — instead of today's bare contour-radius rows that the target viewer renders as a chamfer with side radii.

Scope is deliberately narrow: one new branch inside the existing `FormatAkBlock` notch handling, reusing the existing arc/chain infrastructure. No changes to arc collection, radius attachment, ST/BO/IK code, the VERIFIED `w`-path, AK emission policy, or any other file's behavior. Documentation updates are part of the change; `VERIFIED` marking only after user runtime + viewer evidence.

## Evidence (spec + user, deciding this design)

- DSTV 7th ed. p. 14 notch matrix (extracted :696-721): the tangential-notch column shows an arc approach row with signed radius, then `{X} {Y}t {R}` at the corner, then sharp departure. `t` = tangential notch, `w` = hole-like notch (:698-701).
- `blocks/AK-IK.md` "Notches" section: same `t`/`w` definitions; only `w` is VERIFIED so far.
- User viewer evidence (2026-09): current bare-radii output (`v 200u 310 -10` / `v 190u 300 -10`, no info line) renders as a 10 mm chamfer with a radius on each side. User requirement: NC1 must show the theoretical sharp corner, the `t` note, and the radius.
- User construction (proven by census `Extrusion7: face=h lines=5 arcs=0` + `Fillet3`): sharp 5-line notch sketch, body edges rounded with the 3D Fillet tool → genuine notch with theoretical corner, exactly the spec's `t` case.

## Types

No new types. Reuses `PlateArc` (`Cx/Cy/P1x/P1y/P2x/P2y/RadiusMm/IsWNotch`), `List(Of Point2d)`, `List(Of Double)`, `List(Of String)`, `System.Text.StringBuilder`.

## Files

- **Modify:** `c:\Users\ricog\3D Modeling\Inventor API work\scratch\dstv_exporter.vb` — one new branch in `FormatAkBlock` (after the existing `IsWNotch` loop, before emission) plus two small private helpers (corner intersection, concavity test).
- **Modify (doc, same change):** `knowledge/dstv/nc1/7th-edition/blocks/AK-IK.md` — add `t`-notch "Implementation status: IMPLEMENTED (pending validation)" note under the Notches section; `scratch/HE400B_Example_TestG.md` — add the `t`-notch as a new gap row in the gap list.
- **No other files.** No golden files, no test docs, no `.clinerules` changes. `VERIFIED` marking and any README updates happen only after user runtime + viewer evidence.

### New: t-notch detection + insertion inside `FormatAkBlock` (same function, new block)
Location: `FormatAkBlock`, immediately after the existing `IsWNotch` loop (line ~5148-5150), operating on the same `pts` / `radii` / `letters` lists (all still 1-to-1 at that point).

Trigger conditions for one `PlateArc oArc` (ALL must hold, else skip → current bare-radii behavior preserved):

1. `Not oArc.IsWNotch` (w-path untouched; 270° drilled-hole arcs keep their verified route).
2. Endpoints match a consecutive chain pair `(i, j=(i+1) Mod count)` within 0.05 mm, forward or backward (same matcher as the w-path, lines ~5076-5100).
3. The pair actually carries an attached radius: `|radii(i)| > 0.01` (guards the "niet in contour" case; the emitted `t`-line reuses this exact signed value so arc rows and `t`-line always agree).
4. No `t` (or `w`) letter already within 0.05 mm of the computed corner (duplicate-arc guard — the same physical arc appears twice, front/back face, exactly like the w-path `alreadyDone` pattern).
5. Theoretical corner `C` exists: intersection of the tangent line through `P` (direction = incoming wall) and through `Q` (direction = outgoing wall); `|P−C| ≈ R` and `|Q−C| ≈ R` within 0.10 mm. Walls come from the chain neighbors (predecessor of the approach point, successor of the departure point). Non-tangent or degenerate (parallel walls) arcs skip.
6. Concavity: with the CCW-oriented chain, the turn from incoming to outgoing wall direction at `C` is a right turn (`cross < -0.01` normalized) → genuine notch. Left turn → convex outline round → skip (bare radii stay, current behavior).

Emission on trigger (indices consistent across all three lists):

- `pts.Insert(j, C)` — theoretical sharp corner inserted between the two arc endpoints in travel order (insertion at `j` is travel-correct for both forward and backward matches, including the `j=0` wrap case).
- `radii.Insert(j, radii(i))` — same signed value as the arc rows.
- `letters.Insert(j, "t")` — the existing emission loop already prints `Fmt(p.Y) & letters(i)`, so the line formats as `v <Xc>u <Yc>t <±R>` with zero extra formatter work.
- Debug: `  [AK] t-notch R=<R> op hoek (<Cx>,<Cy>) (t-regel ingevoegd)`; on skip with a matched pair, a one-line reason.

Expected output on the user's current part (no other line changes):

```text
  v 200.00u 400.00 0.00
  v 200.00u 310.00 -10.00
  v 200.00u 300.00t -10.00
  v 190.00u 300.00 -10.00
  v 0.00u 300.00 0.00
```

### New private helpers (same file, near `FormatAkBlock`)

- `TheoreticalNotchCorner(P, Q, wallIn, wallOut) As Point2d or Nothing` — line intersection + R-distance check (tol 0.10 mm). Returns `Nothing` when degenerate.
- Concavity inline in the branch (3-line cross test) — no separate function needed.

### Modified

- `FormatAkBlock` — gains the t-branch described above. The `w`-path, CCW handling, closing-point logic, and emission loop are untouched.

### Removed

- None. Degenerate/non-qualifying arcs keep today's bare-radii behavior (no silent drops added or removed).

## Classes

None.

## Dependencies

None. Uses only existing helpers (`DotVector`, `Fmt`, `ThisApplication.TransientGeometry.CreatePoint2d`) and existing patterns (0.05 mm match tolerance, `alreadyDone` dedup, `dbg IsNot Nothing` guards).

## Testing

1. **Build:** `powershell -ExecutionPolicy Bypass -File scratch\compile_check.ps1` → must print `COMPILE RESULT: PASS (BUILT)`.
2. **Runtime (user, Inventor 2026, same AK-2 part — no new geometry):** run rule `EXPORT_DSTV2` with `DebugMode = True`.
   - Expected debug: `[AK] t-notch R=10.00 op hoek (200.00,300.00) (t-regel ingevoegd)`.
   - Expected NC1 v-block: approach row `-10.00`, `t`-line at the theoretical corner with the same signed radius, departure row unchanged, all other blocks byte-identical to the previous export (diff the files to prove it).
   - `validate_nc1.ps1 -Path <file.nc1>` → PASS.
3. **Viewer (user, target NC1 viewer, unmodified NC1):** notch must render as the actual filleted notch (no chamfer, no side radii); accepted without warning/error.
4. **Failure handling:** any deviation (no `t`-line, wrong corner, viewer rejection) is reported with the exact debug + NC1 lines before any repair — per the validation loop, no blind regeneration.

## Implementation Order

1. Add the t-branch block in `FormatAkBlock` after the `IsWNotch` loop (detection + insertion + debug), plus the two helpers.
2. Add the `t`-notch "Implementation status: IMPLEMENTED" note to `blocks/AK-IK.md` and the new gap row to `HE400B_Example_TestG.md` gap list (doc sync in the same change, status not VERIFIED yet).
3. Run `compile_check.ps1` → PASS required before handoff.
4. Hand off to the user for runtime + viewer validation (steps 2–3 above).
5. Only on user evidence: mark `t`-notch VERIFIED in `blocks/AK-IK.md`, close the gap row, and record the outcome in the recovery state table.
