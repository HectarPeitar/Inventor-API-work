# knowledge/errors

## Purpose

This directory stores **verified negative knowledge** about the Autodesk Inventor API and its environments.

Negative knowledge is information that was actively tested and found to be incorrect, unavailable, or invalid. It is recorded so the AI does not repeat the same failed assumption in a future task.

## What belongs here

- API members that were tested and confirmed not available in a given environment.
- Incorrect API assumptions that were disproven by validation.
- Object/context mistakes that were confirmed.
- Confirmed runtime limitations in a specific Inventor version or programming environment.
- Confirmed error causes that have a verified correction.

## What does NOT belong here

- General technical knowledge (use `knowledge/`).
- Verified reusable implementations (use `tested/`).
- Unverified guesses or speculation.
- Development history that has no reusable value.

## File structure

Files are organised by programming environment when relevant:

- `ilogic/` — iLogic-specific negative knowledge.
- `addins/` — .NET Add-in-specific negative knowledge.
- Other subdirectories may be created when needed.

Each file should follow the Error Memory structure defined in `.clinerules/15-validation-loop.md` (Error / Context / Root Cause / Incorrect Assumption / Correct Approach / Verification / Status).

## Status

Each entry must be backed by actual validation evidence. Use the same status values as the rest of the workspace: `VERIFIED`, `BLOCKED`, `UNRESOLVED`, `GENERATED`, `REVIEWED`, `BUILT`, `RUNTIME-TESTED`.

Do not invent negative knowledge. Only record failures that actually occurred during validation and that have a verified correction.
