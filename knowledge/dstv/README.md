# DSTV NC1 — Curated Specification Digest

7th corrected edition, July 1998. Digest for the EXPORT_DSTV2 exporter
(`scratch/dstv_exporter.vb`) and future DSTV work.

---

## Status

- **CURATED SOURCE** — AI-friendly digest derived from the raw PDF in
  `reference/dstv/`. The archived raw PDF is authoritative for any dispute.
- The **German original outranks this English translation**. The document
  itself states: *"In case of Problems, only the german version is valid"*.
- Text was extracted verbatim (all 23 pages) from the byte-identical
  Tekla-hosted mirror of the archived PDF. The four figures
  (p. 7, 8, 11, 12) are images; figure-derived details are marked
  PENDING in section 14.
- Every rule below cites the page of the raw PDF.

---

## 1. Provenance

| Field | Value |
|---|---|
| Title | STANDARD DESCRIPTION FOR STEEL STRUCTURE PIECES FOR THE NUMERICAL CONTROLS |
| Publisher | Deutscher Stahlbau-Verband (DSTV) — Recommendations of the DSTV Commissions |
| Edition | Juli 1998 (7th Edition) — "This Version delete and replace all the previous ones" |
| Editors | J.-P. Gutsch, U. Kammertöns, J. Keil, D. Knierim, H.-G. Liekweg, U. Pfingst, F. Streit, J. Verlies, B. Wiefel, J. Zühlke |
| Translation | English by BSI S.A. (B4560 Ocquier), version 980511 |
| Archived raw source | `reference/dstv/dstv_nc_eng_1998_en.pdf` — copy of the user's `dstv_nc_eng (1).pdf`, SHA256-verified identical to the Tekla mirror `support.tekla.com/dist/sxf/document/dstv_nc_eng.pdf` |
| Mirrors | atekglobal.com/download/casetups/SICAM/Misc/NC-DSTV-Interface.pdf · atekglobal.com/Download/ATekSetups/dstv_nc_eng.pdf · scribd.com/document/484624581 · scribd.com/document/295617587 |
| German original (to verify) | dstv.deutscherstahlbau.de → BFS-RL_03-109.pdf (search evidence indicates it contains the DSTV description; verify before citing it as the authoritative German text) |

---

## 2. Page map

p. 3 News of the 7th edition · p. 4 Foreword / recommendations / generalities ·
p. 5 Interface file + bloc codes table · p. 6 Units + used profiles ·
p. 7 Coordinate system of the piece · p. 8 Standard views + rolling tolerance ·
p. 9 Header data · p. 9–10 Saw length + skew cuts · p. 10–12 Bloc list of holes
(BO) + hole examples · p. 12–13 Marks by powder/punch (PU/KO) + numeration (SI) ·
p. 13–15 External & internal contour (AK/IK) + welding preparation + notches ·
p. 15 Cut (SC) / tolerance (TO) / camber (UE) · p. 16–18 Plane definition (En) +
example · p. 18–19 Bended parts (KA) · p. 19–20 Profile (PR) · p. 21 Informations
(IN) · p. 21–22 HEB400 example.

---

## 3. File syntax (p. 5)

- The interface file is an editable ASCII text file. Each part has its own
  file, sorted by order.
- Extension: maximum 3 characters; **NC** recommended. The name must be
  meaningful and contain the drawing and piece number (example: `Z23P15.NC`).
- **The first two columns contain the Code Bloc.** The code line is empty from
  the third column; **data lines start with two spaces**.
- From the third column the format is free. The separator of the data is the
  space.
- For compatibility: the passage of a numerical value to a letter or
  vice-versa is **also interpreted as a separator** ("the numerical value must
  be separated either by at least one space, or by a letter which must be
  interpreted").
- Bloc codes: ST (begin), EN (end), BO (holes), SI (numbering), AK (external
  contour), IK (internal contour), PU (powder), KO (mark/punch), SC (cut),
  TO (tolerance), UE (camber), PR (profile description), KA (bending).
- Plane blocs: En, Bn, Sn, An, In, Pn, Kn with n = 0..9 (opening bloc of plan n).
- `**` = comment line, allowed anywhere; comments must be preserved in the same
  place and form on re-export (p. 3).
- If a program cannot read a bloc it must skip to the next readable bloc (p. 9).

---

## 6. Coordinate system and faces (p. 7–9)

- Faces: **V** = web = front face · **U** = bottom · **O** = top · **H** = behind.
  **Np** = zero point, **T** = displacement direction (figure, p. 7 — PENDING for
  exact Np per profile type).
- All coordinates are referenced to this system with **theoretical dimensions of
  perfect profiles perfectly rolled**.
- **The smallest X-coordinate of a piece is 0.0.** Plates are described by the
  smallest rectangle in which they can be inserted.
- Rolling tolerance (p. 8–9): a dimension reference (e.g. "upper edge") indicates
  from which edge dimensions are taken; rolling tolerances are placed on the
  opposite side. **"The reference of the dimension does not modify the value of a
  coordinate, it is the post-processor which must use it to balance the tolerance
  of rolling."**

---

## 7. ST header (p. 9–10)

Order-confirmed field list (format `2x, a` = free text, `2x, i` = integer,
`2x, f` = decimal):

| # | Field | Format |
|---|---|---|
| 1 | Order identification | a |
| 2 | Drawing identification | a |
| 3 | Phase identification | a |
| 4 | Piece identification | a |
| 5 | Steel quality | a |
| 6 | Quantity of pieces | i |
| 7 | Profile (designation) | a |
| 8 | Profile code | a |
| 9 | Length, saw length [mm] | f |
| 10 | Profile height [mm] | f |
| 11 | Flange width [mm] | f |
| 12 | Flange thickness [mm] | f |
| 13 | Web thickness [mm] | f |
| 14 | Radius [mm] | f |
| 15 | Weight by meter [kg/m] | f |
| 16 | Painting surface by meter [m2/m] | f |
| 17 | Web start cut [degree] | f |
| 18 | Web end cut [degree] | f |
| 19 | Flange start cut [degree] | f |
| 20 | Flange end cut [degree] | f |
| 21–24 | Text info on piece (x4) | a |

For sheets (code B): width, 0.0, 0.0, sheet thickness [mm], [kg/m2], [m2/m2].

- **Saw length (p. 10):** if a rough length is needed it follows the normal length
  as "Length, Saw Length"; the saw length is between theoretical points, always
  the shortest.
- **Skew cuts (p. 10):** web skew cuts are represented in the view of the front
  face; flange skew cuts in the bottom face. "The skew cuts angles must be given
  in any case" (example values +/-15 deg).
- After the header, form blocs follow **in any order**.

---

## 8. BO — list of holes (p. 10–12)

Record: `face Xref Y O t [code [l width height angle]]`

- Face letter (first letter): o = top flange, v = front web, u = bottom flange,
  h = behind web.
- X is written with a trailing **dimension-reference letter**: o = top edge,
  (blank) = previous reference, s = axis, u = bottom edge. The letter does not
  change the coordinate value (see section 6, rolling tolerance).
- Y is written as a plain decimal.
- Fabrication codes: (blank) = complete hole (d = diameter, t = 0.0) · g = thread
  (d = diameter, t = 0.0) · l = left threaded (d = diameter, t = 0.0) · m =
  mark/trace (d = 0.0, t = 0.0) · s = countersink (d = diameter, t = depth).
- **Slotted / rectangular holes:** "we add the value ttt.tt the letter 'l' the
  width, height and the angle" — everything on ONE line after the O/t values.
- Countersink dimensions per DIN 74 part 1–2; complete holes per DIN ISO 273;
  pre-drilling per DIN 336.
- Verbatim examples (p. 12):
  - `BO v100.00u100.00 18.0 0.0` — through hole O18
  - `BO v100.00u100.00 18.0 12.0` — blind hole O18 deep 12
  - `BO v 100.00u100.00s18.0 12.0 v 100.00u100.00 12.0 0.0` — countersunk hole
    (countersink O18x12 + hole O12)
  - `BO v 100.00u100.00s18.0 8.0 0.0 0.0 90.0 v 100.00u100.00 12.0 0.0` —
    countersunk (O18x8, "90Deg.")
- Worked-example records (p. 21–22): round hole without t:
  `u 350.00s 98.00 18.00` · slot: `u 1415.00s 251.50 24.00 0.00l 70.00 0.00 0.00`
  · slot/rect: `v 1512.00o 144.00 24.00 0.00l 100.00 60.00 10.00`.

---

## 9. PU / KO marks and SI numeration (p. 12–13)

- **PU** (powder, flame cutting) / **KO** (punch): "The description is identical to
  the internal contour one." Format: `2x a1 f a1 f 1x f` -> face, X, ref, Y,
  radius. From the second point of a same contour the face letter is no longer
  necessary.
- **SI (numeration):** face, absolute X and Y, angle, text height, text. Format
  `2x a1 f a1 f 1x f 1x i a1 40a1` -> face, X, ref, Y, angle (ww.ww), height
  (integer mm), text (max 40 chars). Modifiers: r = text follows the piece if
  turned; (empty) = text at same position; z = force all parameters; if one or
  more parameters missing the numeration is not done. Example (p. 22):
  `SI u 200.00u 225.00 0000.00 5 1/1/1`.

---

## 10. AK / IK contours (p. 3, 13–15)

- AK = external contour, IK = internal contour. AK must NOT be used if the piece is
  completely described by length/dimensions/skew cuts in the header or by SC.
- Contour = points with parallel radius introduction. `+` radius = mathematical
  (CCW) orientation. Max angle +/-180 deg (220 deg -> 180 deg + 40 deg).
- **All contours closed:** first and last point identical; all other points only
  once (p. 3, 13).
- **External contours: mathematical orientation (CCW). Internal contours:
  clockwise.**
- Profiles are described by transforming the profile into **"plates"** with
  **theoretical total profile dimensions** (letters o, u, v, h identify the
  plate); each plate is one face in real dimensions; prefer faces **o and v**.
  Several outside contours in one view are merged into one. Rectangular tube (M)
  and C profile have a single plate for the web contour.
- Round tubes / solid rounds: the plate is the **development (unrolling) of the
  external cylindrical surface**; its width = external perimeter, described in
  "v"; contours describe the external edge.
- Point format: `2x a1 f a1 f a1 f 1x f 1x f 1x f 1x f` -> face, X, ref, Y,
  radius, [Phi, Y] welding-prep couple(s). From the second point of a contour the
  face letter may be omitted.
- **Welding preparation** (p. 14–15): two values after the radius: flame-cutting
  angle (Phi) to the vertical and distance Y; two couples when needed on both
  sides; Phi positive or negative.
- **Notches** (p. 15): an AK info line (not part of the contour) gives the corner
  coordinates + radius type: `t` = tangential notch, `w` = hole-like notch
  (examples p. 15 show `120.00w` / `120.00t` appended to a point line).

---

## 11. SC, TO, UE, PR, KA, IN, En (p. 15–21)

- **SC (cut, p. 15):** cuts are always given by a normal vector to the initial/final
  section, coming out of the material. Format: 6 decimals — point (X, Y, Z) then
  normal vector (X, Y, Z).
- **TO (tolerance, p. 15):** minimum and maximum value, distributed proportionally
  on the length.
- **UE (camber, p. 15):** all coordinates are for the beam WITHOUT camber. Format:
  face, X-dim of camber, Y-dim.
- **KA (bended parts, p. 18–19):** per bending axis: two points (X, Y) + angle +
  radius; coordinates refer to the unbended piece; positive angle bends in the XY
  plane toward +Z.
- **PR (own profile section, p. 20):** section described as contour; `+` = external
  contour, `-` = internal contour; normal rotation without crossing; only one of the
  four faces; **profile code must be SO**.
- **IN (informations, p. 21):** `IN <description> : <content>` (BESTELLER, OBJEKT,
  PROJEKTLEITER, STARTTERMIN, ENDTERMIN, GRUNDANSTRICH, DECKANSTRICH,
  ENTZUNDERUNG, VERZINKUNG, GEZEICHNET VON/AM, GEPRUeFT VON/AM).
- **En (plane definition, p. 16–18):** for geometries not describable by o/u/v/h
  (e.g. round tubes). `E` in column 1, plane number 0–9 in column 2, then three
  lines: origin (X, Y, Z); point of the X-axis at 100 mm from origin; point of the
  Y-axis at 100 mm from origin. Origin = the intersection of the plane with the
  piece Y/Z axes nearer the piece zero point. Affiliated geometries use bloc codes
  with the plane number in column 2 (B1, S1, A1, I1, P1, K1); no face letter on
  those lines. Plane numbers may be re-used; finish the previous plane's geometries
  first.

---

## 12. Priority and consistency rules (p. 3, 9)

- **A hole that can be described by BO must only be described by BO; IK is totally
  forbidden for it.**
- **AK has higher priority than SC.**
- Skew cuts must be described in the header data even when the external contour
  requires AK; other contour elements are 0.0 in the header.
- Comments must be preserved (same place, same form) on re-export.
- All contours must be closed (p. 3).

---

## 13. Worked examples (p. 17–22)

- ZS purlin (p. 17–18): `ST`, comment `**NC-DSTV-Schnittstelle, Stand Juli 1998`,
  order 1114, drawing 14, steel RST37-2, qty 2, profile ZS175*1.5, code SO,
  1133.00 / 175.00 / 81.00 / 1.50 / 1.50 / 4.00 / 4.416 / 0.753 / 0.000x4, text
  "Pfette", then PR, E1 + B1/S1, EN.
- HEB400 (p. 21–22): ST + comment, qty 1, HEB400, I, 2000.00 / 400.00 / 300.00 /
  **24.00 (flange) / 13.50 (web)** / 27.00 / 155.000 / 1.930 / 0.000x4, text
  TRAEGER, then per-face grouping: BO(v)+AK(v), BO(u)+AK(u), BO(o)+AK(o), SI(u),
  EN. Bloc order "in any order" is allowed (p. 9).

---

## 14. Open fine-points (PENDING — figures are images in the raw PDF)

| # | Item | Pages | Default until confirmed |
|---|---|---|---|
| F1 | Np (zero point) per profile type + standard-views orientation -> pins start-end rule and per-face X-reference letter | p. 7–8 | Phase 2 implemented this default: ref letter `u` on all faces, Np at minX (pins at start), t=0.00 on round holes; figure p. 7-8 analysis still PENDING for per-face/per-profile rule |
| F2 | BO slot `width` (70.00 in p. 22 example): center-to-center or overall length | p. 11-12, 23 | **SUPERSEDED 2026-09 by manual viewer testing: `l Width` = centre-to-centre distance**, not overall length. The Phase 3 "overall length" reading (centerDist + 2r) derived from the p. 23 HEB400 drawing is marked incorrect. Verified: a slot BO record using centre-to-centre passes the target viewer (see `nc1/7th-edition/blocks/BO.md` and `scratch/diagnostic/HE400B_DiagnosticMatrix.md`). The p. 23 figure interpretation should be re-examined if the original PDF is consulted again — do not re-derive slot width from that figure without this correction in mind |
| F3 | Rectangle O column meaning (24.00 in `...24.00 0.00l 100.00 60.00 10.00`) | p. 10-12, 23 | **Phase 3: corner diameter** (2 x corner radius). Confirmed by p. 10 figure (rectangle with four corner circles, leader Oslash;24 -> O=24.00) and p. 23 HEB400 drawing. Sharp corners when O = 0.0. Width/height = true edge lengths along rotated edges; angle = rectangle rotation from +w (piece X) reference. **Viewer note 2026-09: O = 0.00 (sharp corners) in a BO record is rejected by the target NC1 viewer — the same geometry passes as an IK internal contour. Do not export sharp rectangles as BO `d=0.00` for this viewer; see `nc1/7th-edition/blocks/BO.md`** |
| F4 | Empty ST text-info lines: written as blank lines or omitted (examples show a single filled text line) | p. 9, 17–22 | write all 4 lines |

---

## 15. Exporter mapping (EXPORT_DSTV2, scratch/dstv_exporter.vb)

| Digest rule | Exporter impact |
|---|---|
| section 3 syntax | indentation/schema of writer OK; keep two-space data lines |
| section 5 codes | full profile-code mapping DONE: B/RU/RO/M/C/T added to I/L/U; SO stays as fallback (scratch/dstv_exporter.vb, GetDstvProfileCode) |
| section 6 system | OBB axes kept; Np rule DONE Phase 2 (smallest X = 0.0, pins at minX end, documented default); theoretical-envelope alignment for curved profiles still open |
| section 7 ST | fields 1–16 already conform (flange before web OK); 17–20 skew angles -> Phase 5 |
| section 8 BO | round-hole `t` field + trailing X-ref letter DONE Phase 2 (`face X[ref] Y O t`); slot width/height DONE Phase 3 — **width = centre-to-centre distance (supersedes Phase 3 "overall length", see F2)**, height=0.00; rectangle O/width/height/angle DONE Phase 3 (corner diameter, edge lengths, rotation); slot/rectangle angle face-frame mapping still PENDING; **sharp-corner rectangles: target viewer rejects BO `d=0.00` — IK internal contour is the verified working representation (viewer-compatibility rule, see `nc1/7th-edition/DSTV-KNOWLEDGE-MAP.md`)** |
| section 8 vs 12 | cut classifier must never route BO-describable holes to IK; viewer-verified exception: sharp-corner rectangular internal openings (BO `d=0.00` rejected by target viewer) |
| section 10 AK/IK | Phase 5: plates with theoretical dimensions, CCW external / CW internal, closed |
| section 9 SI/PU/KO | Phase 6 (numeration vs marks — corrected mapping) |

---

## Related

- `knowledge/README.md` — knowledge index
- `knowledge/units.md` — Inventor internal units (cm) vs DSTV units (mm)
- Phase plan: EXPORT_DSTV2 (scratch/dstv_exporter.vb)
