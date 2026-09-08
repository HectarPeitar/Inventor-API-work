# DSTV 7th Edition - Coordinate System

## Source

Primary source: DSTV 7th Corrected Edition, pp. 7-8.

## Piece coordinate system

The coordinate system is defined per profile type. The document explicitly distinguishes standard profile families and shows the position of `Np`, X, Y, Z, T and the four standard faces.

### Standard face names

- `V` = front web
- `O` = top
- `U` = bottom
- `H` = behind

### Key definitions

- `Np` = zero point
- `T` = displacement direction
- X = longitudinal direction of the piece
- Y/Z = cross-section directions according to profile type

All coordinates are referenced to the theoretical coordinate system of a perfect, correctly rolled profile. The smallest X-coordinate is 0.0.

## I-profile (type I) — verified coordinate system

> **DIRECT FIGURE VERIFICATION — DSTV 7th Edition p. 7.**
> The following interpretation of the I-profile coordinate system is read directly from the original figure, not inferred from the extracted text.

### Np location

`Np` (zero point) is located at the **lower/right reference point** of the I-profile drawing.

### Axes

| Axis | Direction | Evidence |
|---|---|---|
| `+X` | Longitudinally along the piece, starting from `Np` | DIRECT FIGURE |
| `+Y` | From `Np` toward the **left**, across the profile section | DIRECT FIGURE |
| `+Z` | **Upward** from `Np` | DIRECT FIGURE |

### T (displacement direction)

`T` is shown opposite to `+X` in the figure (DIRECT FIGURE).

### Faces

| Face | Meaning | Evidence |
|---|---|---|
| `O` | Top face | DIRECT FIGURE |
| `U` | Bottom face | DIRECT FIGURE |
| `V` | Front web | DIRECT FIGURE |
| `H` | Behind web | DIRECT FIGURE |

### Consequences

- The smallest X-coordinate is `0.0` (at `Np`); X increases away from `Np` along the piece.
- `+Z` is upward, so the bottom face (`U`) is at the lowest Z and the top face (`O`) at the highest Z.
- `+Y` points left across the section; the right edge of the section (at `Np`) is the Y=0 reference.

## Rolling tolerance reference

The dimension-reference letter indicates the edge from which a dimension is taken. It does **not** alter the coordinate value. The post-processor uses the reference information to compensate for rolling tolerances.

Valid dimension references shown by the specification:

- `o` = top edge
- blank = previous reference
- `s` = axis
- `u` = bottom edge

These are distinct from the face identifiers `o`, `v`, `u`, `h`.

## Implementation warning

An Inventor geometric construction such as `OrientedMinimumRangeBox` may provide a useful geometric frame, but it is not by itself proof that the resulting origin equals the DSTV `Np` for every profile family.

Before treating an OBB-derived frame as DSTV-correct, verify the mapping for the intended profile type against the profile diagram on page 7.

For the I-profile, the verified figure fixes the mapping (see section above): `Np` at the lower/right reference point, `+X` longitudinal from `Np`, `+Z` upward, `+Y` toward the left across the section. The Inventor implementation must therefore:

- place DSTV `X = 0` at the `Np` end of the piece (the end from which `+X` runs);
- orient DSTV `+Z` upward so the `O` (top) face is at maximum Z and the `U` (bottom) face at minimum Z;
- orient DSTV `+Y` toward the left across the section, with `Y = 0` at the right edge (the `Np` side);
- map faces as `O = +Z`, `U = -Z`, `V = +Y`, `H = -Y`.

Because the OBB frame is derived from raw geometry, confirm that the OBB's height axis points `+Z` (up) and that the chosen `Y = 0` edge is the right-hand edge of the section before trusting the frame as DSTV-correct.
