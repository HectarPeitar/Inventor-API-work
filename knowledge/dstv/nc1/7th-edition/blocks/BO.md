# DSTV 7th Edition - BO Block

## Source

DSTV 7th Corrected Edition, pp. 10-11.

## Purpose

`BO` describes holes in a piece.

The record contains:

- reference face of the piece;
- absolute X coordinate;
- absolute Y coordinate;
- diameter;
- manufacturing code;
- optional data for slotted or rectangular holes.

## Manufacturing codes

- ` ` / complete hole: diameter + `t = 0.0`
- `g`: thread, diameter + `t = 0.0`
- `l`: left thread, diameter + `t = 0.0`
- `m`: mark/trace, diameter = 0.0 and `t = 0.0`
- `s`: countersink, diameter + depth
- `l` after the numeric `t` field: slotted or rectangular hole, followed by width, height and angle

## Dimension-reference letters

- `o` = top edge
- blank = previous reference
- `s` = axis
- `u` = bottom edge

## Face identifiers

- `o` = top flange
- `v` = front web
- `u` = bottom flange
- `h` = behind web

## Slot / rectangular extension

When the hole is slotted or rectangular, the record adds:

`l width height angle`

The specification's worked examples must be used to interpret the geometric meaning of these values. Do not infer centre-to-centre versus overall dimensions from variable names alone.

## Worked example

Page 21 contains a HEB400 example with the slot record:

`v 1512.00o 144.00 24.00 0.00l 100.00 60.00 10.00`

and corresponding `u` and `o` examples later in the same file.

For any disputed interpretation, use the dimensional drawing on the relevant source page rather than relying only on extracted text.

## Verified slot interpretation (manual viewer evidence)

From manual viewer testing, the slot interpretation in the BO record must use **centre-to-centre distance**, not overall length.

For the HEB400 reference:

```text
u 1415.00s 251.50 24.00 0.00l 70.00 0.00 0.00
```

`70.00` is the **centre-to-centre distance** between slot ends, not overall length.

Slot interpretation:

- `d` = round-end diameter
- `l Width` = centre-to-centre distance
- `l Height` = 0.00  
- `l Angle` = slot angle

This supersedes the interpretation that `l Width` = overall length (centreDist + diameter).

## Sharp rectangular openings

The target NC1 viewer rejects sharp-corner rectangular openings represented as BO with `d=0.00` and accepts the same geometry as an IK internal contour.

BO representation that fails:

```text
o 395.00u 230.00 0.00 0.00l 50.00 80.00 0.00
```

Changing only `d`:

- `d = 1.00` → PASS
- `d = 10.00` → PASS
- `d = 20.00` → PASS

The same physical sharp rectangle represented as an IK internal contour using its corner coordinates produces:

```text
IK ... (closed clockwise contour, radius=0.0 at corners)
```

Result: PASS — no validation warning.

## Alternative-description priority

The DSTV 7th edition requires that a hole that can be described by BO must use BO; using IK for that same hole is forbidden.

However, the available DSTV specification does not explicitly state that `d=0.00` is invalid for a rectangular BO record. This is a **verified viewer/exporter compatibility rule**, not an unconditional DSTV specification requirement.

Current working guidance:

- Round hole → BO
- Rounded-end slot → BO  
- Rectangular opening with non-zero rounded/corner diameter → BO
- Sharp-corner internal rectangle → IK is the verified working representation for this exporter/viewer combination

This is a **verified viewer/exporter compatibility rule**, not a universal DSTV specification rule.
