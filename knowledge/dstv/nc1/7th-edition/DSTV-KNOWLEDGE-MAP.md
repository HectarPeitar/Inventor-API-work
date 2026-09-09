# DSTV NC1 Knowledge Map - 7th Corrected Edition

## Source

- Title: **STANDARD DESCRIPTION FOR STEEL STRUCTURE PIECES FOR THE NUMERICAL CONTROLS**
- Edition: **7th Corrected Edition**
- Date: **July 1998**
- Source file: `DSTV-7th-edition.pdf`
- Language: English translation
- Authority note from source: in case of problems, the German version is valid.

## Purpose

This file is the central navigation point for the DSTV/NC1 format knowledge used by the Inventor NC1 exporter.

It is a curated interpretation and navigation layer. It does **not** replace the original DSTV PDF.

## Source hierarchy

1. Original DSTV 7th Corrected Edition PDF
2. `DSTV-7th-edition-extracted.md` for searchable text
3. This Knowledge Map and topic-specific curated files
4. Project-specific verified findings
5. General model knowledge only as a last resort

When a rule depends on a drawing, figure, dimensional example, or layout that is not reliably represented by text extraction, consult the original PDF visually before making an implementation decision.

## Core topics

| Topic | Primary source | Secondary source |
|---|---|---|
| Interface syntax | PDF p. 5 | extracted text |
| Units and formats | PDF p. 6 | extracted text |
| Profile codes | PDF p. 6 | extracted text |
| Piece coordinate system | PDF p. 7 | `coordinate-system.md` |
| Standard views / rolling tolerance | PDF p. 8 | `coordinate-system.md` |
| ST header | PDF p. 9 | `blocks/ST.md` |
| BO holes | PDF pp. 10-11 | `blocks/BO.md` |
| SI numeration | PDF p. 12 | `blocks/SI.md` |
| AK / IK contours and notches | PDF pp. 13-14 | `blocks/AK-IK.md` |
| SC cuts | PDF p. 15 | `blocks/SC.md` |
| Plane definitions | PDF pp. 16-17 | later topic file |
| KA bends | PDF p. 18 | later topic file |
| PR own profiles | PDF p. 19 | later topic file |
| IN information | PDF p. 20 | later topic file |
| Complete worked example | PDF p. 21 | `examples.md` |

## Critical implementation rules

### Interface file

- The interface is an editable ASCII text file.
- Block codes occupy columns 1 and 2.
- Block lines are empty from column 3 onward.
- Data lines start with two spaces.
- Space is the normal separator.
- A transition between numeric value and a letter is also interpreted as a separator.
- Comments must be preserved when a file is exported again.

### Units

- Length: mm
- Angle: degrees
- Weight per meter: kg/m
- Painting surface per meter: m²/m
- Free text: alphanumeric, max 80 characters
- Integer: integer without unit
- Decimal values: floating-point format
- Angles are positive in mathematical counter-clockwise orientation.

### Profile codes

- `I` = I profile
- `L` = L profile
- `U` = U profile
- `B` = sheets/plates
- `RU` = round profile
- `RO` = rounded tube
- `M` = rectangular tube
- `C` = C profile
- `T` = T profile
- `SO` = special profile

### Coordinate system

The specification defines the piece coordinate system per profile type.

Important facts:

- `V` = front web
- `O` = top
- `U` = bottom
- `H` = behind web
- `Np` = zero point
- `T` = displacement direction
- all coordinates are referenced to the theoretical coordinate system of the perfect profile;
- the smallest X coordinate of the piece is 0.0.

Do **not** substitute a generic Inventor OBB origin for `Np` without proving that the mapping is correct for the profile type.

### Dimension reference letters

The reference letter describes the edge/axis from which a dimension is taken. It does not change the coordinate value itself; it is information the post-processor uses to account for rolling tolerances.

For BO/SI/contour-style records the specification defines:

- `o` = top edge dimension reference
- blank = previous reference
- `s` = axis dimension reference
- `u` = bottom edge dimension reference

The face letters are separate:

- `o` = top flange
- `v` = front web
- `u` = bottom flange
- `h` = behind web

Do not confuse a face letter with an X/Y dimension-reference letter.

## Alternative-description priority

The 7th edition requires programs to take alternative-description priority into account.

Important example from the specification:

- A geometry that can be described by `BO` must be described by `BO`; using `IK` for that same hole is forbidden.
- `AK` has higher priority than `SC` when both descriptions would otherwise apply.

This priority must be preserved when extending the exporter.

### Verified viewer exception (2026-09) — sharp-corner rectangles

Manual testing in the target NC1 viewer established a project-specific compatibility finding:

- A sharp-corner rectangular internal opening exported as `BO` with `d = 0.00` is **rejected** (validation warning).
- The same geometry exported as an `IK` closed clockwise internal contour (4 corner points, radius = 0.0 at corners) **passes**.
- Any non-zero corner diameter (`d = 1.00 / 10.00 / 20.00`) passes as `BO`.
- Round holes and rounded-end slots pass as `BO` in all tested forms.

Classification: this is a **verified viewer/exporter compatibility rule**, not a universal DSTV specification rule. The DSTV 7th edition defines rectangular `BO` records and does not explicitly state that `d = 0.00` is invalid. Do not record or quote it as an unconditional DSTV requirement. The BO-over-IK priority rule from the specification remains in force for all geometry for which BO is applicable and accepted.

**Rounded/filleted rectangles (verified 2026-09-09):** a rectangle whose corners are filleted is BO-describable (non-zero `d` = 2 × fillet radius) and must be exported as `BO`. Verified for both detection paths — fillets drawn in the sketch (4 lines + 4 arcs profile) and fillets applied with the 3D Fillet tool (detected via the hole's actual inner edge loop on the face, `ProbeHoleBoundaryLoop`). No viewer warning for either path on the tested part.

Details and evidence: `blocks/BO.md` (Sharp rectangular openings, Alternative-description priority), `blocks/AK-IK.md` (Verified viewer observation), `scratch/diagnostic/HE400B_DiagnosticMatrix.md`.

### Verified slot interpretation (2026-09)

Manual viewer testing confirmed that in a slotted `BO` record (`... d ... l W H A`):

- `d` = round-end diameter
- `l Width` = **centre-to-centre distance** between the slot ends
- `l Height` = 0.00
- `l Angle` = slot angle

The earlier interpretation `l Width = overall length` (centre-to-centre + diameter) is **superseded**. See `blocks/BO.md` and `examples.md`.

## Topic-specific files

- `coordinate-system.md` - curated coordinate-system and reference rules
- `blocks/ST.md` - ST header rules
- `blocks/BO.md` - BO hole record rules
- `blocks/SI.md` - SI numeration rules
- `blocks/AK-IK.md` - contour and notch rules
- `examples.md` - verified worked-example observations

## AI usage rule

For NC1 implementation questions, first locate the relevant topic here, then inspect the cited source in the extracted Markdown. If the conclusion depends on a figure or geometric dimensioning example, inspect the original PDF page visually.

Never infer a DSTV field meaning from a variable name, an existing implementation, or a single software-generated NC1 file when the specification can answer the question.
