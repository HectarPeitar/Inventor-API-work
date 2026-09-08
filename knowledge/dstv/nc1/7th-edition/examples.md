# DSTV 7th Edition - Worked Examples

## Source

DSTV 7th Corrected Edition, p. 21 (HEB400 worked example).

## HEB400 example observations

Header includes:

- profile `HEB400`
- code profile `I`
- length `2000.00`
- height `400.00`
- flange width `300.00`
- flange thickness `24.00`
- web thickness `13.50`
- radius `27.00`
- weight/m `155.000`
- painting surface/m `1.930`
- four skew-cut values `0.000`
- text `TRAEGER`

The example then uses BO and AK blocks separately for different faces and includes an SI block.

## Slot example

The BO record in the worked example is visually shown as:

`v 1512.00o 144.00 24.00 0.00l 100.00 60.00 10.00`

A similar slot record appears later using the `u` face and again using the `o` face:

`u 1415.00s 251.50 24.00 0.00l 70.00 0.00 0.00`

`o 1415.00s 251.50 24.00 0.00l 70.00 0.00 0.00`

For disputed slot semantics, the dimensional drawing on page 10 and the worked example on page 21 should be considered together. Do not silently reinterpret the 70 value without checking the geometry shown by the source.

## Verified slot interpretation (manual viewer evidence)

**IMPORTANT**: Manual viewer testing confirms that `l Width` represents the **centre-to-centre distance**, not the overall length.

For the HEB400 reference slot record `u 1415.00s 251.50 24.00 0.00l 70.00 0.00 0.00`:

- `70.00` is the centre-to-centre distance between slot ends
- The previous interpretation that `overall length = centreDist + diameter` is **SUPERSEDED**

This is verified by testing that the slot BO record with the correct centre-to-centre interpretation passes validation.

## Example interpretation caution

Worked examples show how the standard is used, but an example alone does not prove that every populated field is mandatory in every file.
