# DSTV/NC1 Project Rules — Autodesk Inventor Workspace

## Purpose

This file defines DSTV/NC1-specific behavioral rules for this workspace. These rules supplement the core Inventor rules in `.clinerules/00-core.md` through `.clinerules/20-workflow.md`.

---

## 1. Knowledge Retrieval Hierarchy

For DSTV/NC1 implementation questions, the retrieval order is:

1. **`knowledge/dstv/nc1/7th-edition/DSTV-KNOWLEDGE-MAP.md`** — central navigation point
2. Topic-specific curated files under `knowledge/dstv/nc1/7th-edition/blocks/` and `coordinate-system.md`, `examples.md`
3. `knowledge/dstv/nc1/7th-edition/DSTV-7th-edition-extracted.md` — searchable extracted text
4. Original PDF `reference/dstv/dstv_nc_eng_1998_en.pdf` — **archival/reference only**, consulted only when a figure, drawing, or layout cannot be reliably resolved from curated sources
5. General model knowledge — last resort

**Never** use the raw PDF as the normal implementation lookup path. The curated knowledge map and topic files are the working interface.

---

## 2. Validation Status Definitions (DSTV-Specific)

Use these status values **exactly** for DSTV capabilities:

| Status | Meaning |
|--------|---------|
| `IMPLEMENTED` | Code exists in `scratch/dstv_exporter.vb` and compiles (vbc PASS) |
| `RUNTIME-TESTED` | Code executed in Autodesk Inventor 2026 by the user; no runtime exception; NC1 generated |
| `VIEWER-TESTED` | Generated NC1 imported in the target NC1 viewer by the user; no validation error/warning recorded |
| `VERIFIED` | **Both** `RUNTIME-TESTED` **and** `VIEWER-TESTED` confirmed for the specific capability |
| `BLOCKED` | Cannot proceed because external action/environment unavailable (e.g., Inventor not running, viewer not available) |
| `UNRESOLVED` | Evidence insufficient to decide; explicit test/decision required |
| `KNOWN LIMITATION` | Deliberately deferred with documented reason |
| `NOT IMPLEMENTED` | No code exists |

**Never** mark `VERIFIED` based on code inspection alone. **Never** mark `VIEWER-TESTED` without user-provided viewer evidence. **Never** mark `RUNTIME-TESTED` without user-provided Inventor execution evidence.

---

## 3. Manual Runtime Testing Protocol

- **Cline cannot run Inventor.** All runtime validation is performed manually by the user.
- When a task requires runtime validation, Cline **must provide**:
  1. Exact test geometry/setup instructions
  2. Exact exporter action to perform
  3. Expected observations to record
  4. Exact NC1 lines/sections to inspect
  5. What each result would mean for the decision
- Cline **must not** claim a test was run unless the user explicitly provides the result.
- Cline **must not** proceed to implementation that depends on a test result until the user provides it.

---

## 4. AK Emission Policy (VERIFIED 2026-09)

- The exporter emits AK blocks **for every exported member** (`BuildAkBlocks` called on every export). This is intentional and viewer-verified:
  - Baseline test: plain HE 400 B member (525 mm, square ends, no openings) with profile code `I` and geometrically derived section dimensions (400.00 / 300.00 / 24.00 / 13.50 / 0.00) was accepted by the target viewer **with AK blocks and no warning**.
  - The HEB400 worked example (DSTV 7th ed., p. 21-22) likewise carries AK blocks for a standard I-profile.
- **Do not introduce conditions to suppress AK** when the ST header already describes the member, unless new viewer evidence shows a warning/error on a plain member.
- Radius rows (`o/u` bevel faces in format `X ref Y radius`, `v` plate coupling faces with `w` markers) are emitted as part of AK; viewer-accepted as of 2026-09.

---

## 5. SC Block Guardrail

- **Do not start SC (special cuts) implementation** until:
  - AK-1, AK-2, AK-3 are at least `RUNTIME-TESTED` (ideally `VIEWER-TESTED`)
  - The AK emission policy is resolved (done 2026-09: unconditional)
  - The cope/notch absorption into AK contours is working
- SC is lower priority than AK per DSTV spec (AK > SC). Implementing SC before AK is stabilized violates the spec priority.

---

## 6. Single-Task Scope Discipline

- Every implementation task must have **one narrowly defined objective**.
- Do **not** expand scope during a task because a related problem is discovered.
- If a related problem is found, document it as a separate task/issue and return to the original objective.
- Tasks that combine multiple capabilities (e.g., "implement AK-2 and AK-3") must be split.

---

## 7. Documentation Synchronization Requirement

- After any validation (runtime or viewer), update the relevant test documentation (`scratch/HE400B_*.md`) with the result.
- After any implementation, update `knowledge/dstv/README.md` §15 (Exporter mapping) and the relevant `blocks/*.md` file.
- Stale "PENDING" or "TODO" statements in documentation that no longer reflect code reality must be reconciled in the same task that changes the code — or explicitly flagged in a sync task like this one.

---

## 8. Status Reporting

At the end of every DSTV task, report:

```
Status: <IMPLEMENTED | RUNTIME-TESTED | VIEWER-TESTED | VERIFIED | BLOCKED | UNRESOLVED | KNOWN LIMITATION | NOT IMPLEMENTED>
Capability: <specific capability>
Runtime evidence: <user-provided or N/A>
Viewer evidence: <user-provided or N/A>
Documentation updated: <files>
Remaining gaps: <specific>
```
