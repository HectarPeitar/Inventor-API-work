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

## Implementation guidance

Do not infer that blank text-info fields are invalid solely from a worked example. Treat their content as a separate business/documentation decision unless another explicit rule establishes a requirement.
