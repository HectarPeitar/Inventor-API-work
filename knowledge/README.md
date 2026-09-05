# knowledge

## Purpose

This directory contains technical knowledge about Autodesk Inventor and its APIs.

The information is intended to give the AI a stable technical foundation when creating or modifying Inventor automation.

**Primary navigation for Inventor knowledge:** see `knowledge/inventor/KNOWLEDGE-MAP.md`.

The complete Autodesk Inventor 2026 SDK is stored at `knowledge/inventor/2026/sdk/` and is treated as raw authoritative source material. Curated interpretation files live in `knowledge/inventor/2026/`.

---

## What belongs here?

Technical concepts, API knowledge, compatibility information, and documented behavior.

Examples:

- Inventor object model;
- iLogic;
- .NET Add-ins;
- Assemblies;
- Parameters;
- Units;
- API compatibility;
- Inventor API concepts.

---

## What does NOT belong here?

Do not store:

- AI behavioral rules;
- project-specific coding instructions;
- temporary debugging notes;
- unverified guesses;
- large collections of complete example implementations.

Behavioral rules belong in:

    .clinerules/

Tested implementations belong in:

    tested/

Reusable examples belong in:

    examples/

External source material belongs in:

    reference/

---

## Current Files

- `APInotes.md`
  General Inventor API concepts and important API principles.

- `api-compatibility.md`
  Inventor version, .NET, Interop, and migration considerations.

- `object-model.md`
  Relationships between important Inventor API objects.

- `ilogic.md`
  iLogic-specific concepts and best practices.

- `addins.md`
  .NET Add-in architecture and development.

- `assemblies.md`
  Assembly API concepts and occurrence handling.

- `parameters.md`
  Parameter concepts and automation.

- `units.md`
  Unit handling and unit-related pitfalls.

---

## Design Principle

`knowledge/` answers:

> "What do we know about Autodesk Inventor?"

The information should be:

- reusable;
- relatively stable;
- technically focused;
- separated by topic;
- updated when better information becomes available.

---

## Source Confidence

Knowledge should preferably originate from:

1. Current Autodesk documentation.
2. Inventor SDK / local API information.
3. Verified local testing.
4. Autodesk DevTech examples.
5. Reliable community examples.

Clearly distinguish verified information from assumptions.

---

## Updating Knowledge

When a new discovery is made, first determine whether it is:

- general technical knowledge;
- a tested implementation;
- an example;
- an AI behavior rule.

Only general technical knowledge belongs here.

Avoid duplicating the same information across multiple knowledge files.
