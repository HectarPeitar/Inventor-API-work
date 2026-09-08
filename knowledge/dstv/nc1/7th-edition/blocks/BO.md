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

## Alternative description priority

A hole that can be described as `BO` must use `BO`; describing the same hole with `IK` is forbidden by the 7th edition.
