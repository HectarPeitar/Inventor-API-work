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
