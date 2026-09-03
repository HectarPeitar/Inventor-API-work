# reference

## Purpose

This directory contains external reference material used as source material for the AI workspace.

It is not necessarily rewritten or normalized.

---

## What belongs here?

Examples:

- Autodesk DevTech training material;
- downloaded Autodesk documentation;
- SDK documentation;
- official examples;
- third-party reference projects;
- archived documentation;
- external source repositories.

---

## Source Priority

Reference material does not automatically have the same authority.

Prefer:

1. Current official Autodesk documentation.
2. Current Autodesk SDK material.
3. Autodesk DevTech material.
4. Reliable community sources.
5. Older or archived material.

---

## Legacy Material

Older material can still be useful.

For example, old Autodesk training may explain concepts that remain relevant even when:

- project templates changed;
- .NET versions changed;
- API members changed;
- deployment changed.

Do not assume that old code is directly compatible with Inventor 2026.

Use:

    knowledge/api-compatibility.md

when evaluating legacy material.

---

## What does NOT belong here?

Do not use this directory as the primary place for:

- AI rules;
- normalized technical knowledge;
- verified production code;
- project-specific notes.

Those belong elsewhere.

---

## Design Principle

`reference/` answers:

> "Where did this information come from?"

It preserves source material so that knowledge can be checked against the original source.

---

## Source Preservation

When adding external material, preserve useful source information where possible:

- original author;
- project name;
- URL;
- version;
- date;
- license;
- source type.

Do not modify third-party source material unnecessarily.
