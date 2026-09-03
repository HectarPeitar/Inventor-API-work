# templates

## Purpose

This directory contains starting templates for new Autodesk Inventor automation projects.

Templates provide a known project structure so new work does not have to start from zero.

---

## What belongs here?

Examples:

- C# Inventor Add-in templates;
- VB.NET Add-in templates;
- iLogic rule templates;
- project skeletons;
- installer/deployment templates;
- common configuration files.

---

## Template vs Example

A template is intended to be copied and adapted.

An example is intended primarily to demonstrate a technique.

Therefore:

    templates/
    "Start a new project from this."

    examples/
    "Learn how this technique works."

---

## Template Quality

Templates should preferably be:

- minimal;
- clean;
- documented;
- tested;
- version-aware;
- free of unnecessary dependencies.

Where relevant, document:

- Inventor version;
- .NET version;
- language;
- required SDK;
- required Interop version;
- installation/deployment assumptions.

---

## Versioning

Inventor Add-in templates can be version-sensitive.

Do not assume that a template created for an older Inventor release is automatically suitable for Inventor 2026.

Use:

    knowledge/api-compatibility.md

when evaluating an existing template.

---

## What does NOT belong here?

Do not store:

- random project backups;
- unfinished experiments;
- large external source repositories;
- general API documentation.

---

## Design Principle

`templates/` answers:

> "What should I start with when creating something new?"
