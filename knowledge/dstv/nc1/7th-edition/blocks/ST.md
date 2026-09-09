# DSTV 7th Edition - ST Block

## Source

DSTV 7th Corrected Edition, p. 9.

## Purpose

The `ST` block begins the description of a piece and contains the main header data required for NC processing.

## Header fields

1. Order identification
2. Drawing identification
3. Phase identification
4. Piece identification
5. Steel quality
6. Quantity of pieces
7. Profile
8. Code Profile
9. Length / saw length
10. Profile height
11. Flange width
12. Flange thickness
13. Web thickness
14. Radius
15. Weight by meter
16. Painting surface by meter
17. Web Start Cut
18. Web End Cut
19. Flange Start Cut
20. Flange End Cut
21. Text info on piece
22. Text info on piece
23. Text info on piece
24. Text info on piece

## Important rules

- Skew cuts are required in the header data.
- The four skew-cut values are angles.
- Length and geometric dimensions are expressed in mm.
- Weight is kg/m.
- Painting surface is m²/m.
- The four text-info fields are alphanumeric fields. The standard examples populate them, but the English source text does not explicitly state that every field must be non-empty.

## Skew-angle sign convention (EXPORTER/VIEWER VERIFIED CONVENTION, 2026-09)

The raw specification text does not define how the signs of fields 17–20 map to the physical lean direction of the cut plane (the p. 9–10 skew figure is visual; its extracted labels only show a `+15`/`−15` pair per view). The following convention was established empirically with the project exporter and confirmed in the target NC1 viewer (HE 400 B, Inventor 2026):

- Angle magnitude = tilt of the end cut plane relative to the perpendicular end plane (0.00 for a square end), in degrees, derived from the actual end-face plane normal.
- With the **outward** end-face normal (pointing out of the material):
  - web fields (17/18): lean = sign of the height (Z) component in the front view;
  - flange fields (19/20): lean = sign of the width (Y) component in the bottom view.
- Signs per field (the front view and the bottom view have opposite rotation senses in the DSTV projection, so the web pair is the mirror of the flange pair):

| Field | Value |
|---|---|
| 17 Web Start Cut | −lean × magnitude |
| 18 Web End Cut | +lean × magnitude |
| 19 Flange Start Cut | +lean × magnitude |
| 20 Flange End Cut | −lean × magnitude |

Identical (parallel) skew cuts at both ends therefore carry opposite signs — consistent with the `+15`/`−15` label pair per view in the p. 9–10 figure.

Verification:
- Flange fields: start-end cuts of +15° and −15° and an end-end cut (10°) render correctly; the end-end cut without negation rendered mirrored.
- Web fields: with the uniform start/end rule a web cut rendered mirrored; after the mirror correction web cuts render correctly at both ends.

Classification: exporter/viewer-verified behavior, **not** a raw-specification rule. Both the flange and web fields are viewer-verified at both ends (2026-09).

## Implementation guidance

Do not infer that blank text-info fields are invalid solely from a worked example. Treat their content as a separate business/documentation decision unless another explicit rule establishes a requirement.
