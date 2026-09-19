# Uncommitted exporter work lost by `git checkout` + stale-output evidence

## Error

Two related failures in one session (DSTV FK-0 / w-notch phase, 2026-09-18):

1. `scratch/dstv_exporter.vb` in the working tree was restored with
   `git checkout -- scratch/dstv_exporter.vb` while the LATEST
   implementation (the whole AK-2 arc pipeline: `PlateArc`,
   `GetPlateArc`, `CollectPlateArcs`, `AttachArcRadii`, radii-aware
   `FormatAkBlock`) existed ONLY as uncommitted changes / in the user's
   Inventor iLogic rule storage. The restore silently rolled the file
   back to git HEAD (AK-1). GitHub could NOT restore it (never pushed).
2. After the sync + w-notch fix, the user pasted an NC1 file that was
   from an EARLIER run (stale), which initially suggested the w-notch
   replacement had not taken effect.

## Context

- Inventor version: 2026
- Environment: VB.NET external iLogic-style rule (`scratch/dstv_exporter.vb`)
- Document type: Part (HE 400 B test beam)
- Object/context: AK external-contour emission (v plate), BO openings

## Root Cause

1. The exporter's authoritative latest version lived in the Inventor
   rule editor, not in git; the workspace file and git HEAD were both
   older. `git checkout -- <file>` was run assuming the working tree
   held the newest state, but it actually held intermediate edit states;
   the checkout discarded them.
2. Stale-output confusion: the exporter rewrites `<PieceId>.nc1` every
   run, but the pasted NC1 predated the run. Freshness was NOT checked
   against the debug report of the same run.

## Incorrect Assumption

1. "git HEAD / origin is the latest version of the exporter" — false:
   several verified fixes (RUN-8 rect-fillet position/angle, sweep-angle
   acceptance, AK-2 pipeline) were uncommitted.
2. "the pasted NC1 corresponds to the pasted debug report" — false until
   cross-checked.

## Correct Approach

1. NEVER discard uncommitted work without first diffing the working tree
   against the user's current external state (here: the Inventor rule).
   When versions diverge, ask the user to paste the authoritative text
   and sync the workspace FROM it.
2. Before interpreting run evidence, verify debug-report and NC1 come
   from the SAME run: every exported value in the NC1 must be traceable
   to a debug line of the same run (e.g. the BO rect-fillet record
   `1503.58/203.09/10.00` matched run N, while the same-run debug said
   `1558.03/182.23/9.96` — proof the NC1 was stale).
3. The regression introduced by the sync (rect-fillet fell back to
   centroid position + 9.96 angle) was detected exactly by that
   debug-vs-NC1 cross-check plus the known RUN-8 expected values, then
   repaired by porting the five un-committed fixes from the user's rule
   (3D-probe c-t-c lengths + vector angles, BO-3DFILLET long-side/fullW,
   sketch-fillet edgeDir3d + bottom-left arc-centre position,
   unrounded GetDstvFaceFrameAngle, added
   ComputeFaceFrameAngleFromVector).

## Verification

Re-run in Inventor 2026 after the repair: debug shows
`OPENING (rect-fillet): ... holeX=1503.58u facePos=203.09 ... angle=10.00`
matching the NC1 record of the SAME run; compile gate PASS
(169,505 bytes). w-notch emission verified in the same run
(`v 200.00u 100.00w 10.00` in the v-AK block).

## Status

VERIFIED
