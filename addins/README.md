# addins

## Purpose

This directory contains active Autodesk Inventor Add-in projects.

These are real development projects rather than examples or documentation.

---

## What belongs here?

Examples:

- C# Inventor Add-ins;
- VB.NET Inventor Add-ins;
- Add-in UI projects;
- Add-in command implementations;
- Add-in event handling;
- Add-in services and supporting code;
- project files and solution files.

Example:

    addins/
    └── HoleInspector/
        ├── HoleInspector.sln
        ├── HoleInspector.csproj
        ├── ThisAddIn.cs
        ├── Commands/
        ├── Services/
        └── UI/

---

## Active Development

Files in this directory represent active development work.

Cline/AI may modify these files when explicitly asked to implement, debug, refactor, or extend an Add-in.

Changes should therefore be treated as real code changes.

Do not assume that files in this directory are disposable.

---

## Build Output

Build output should not be stored as useful source material.

Typical generated directories include:

    bin/
    obj/

These directories are excluded through `.clineignore`.

---

## Relationship to tested/

The distinction is important.

`addins/` contains active projects:

> "What are we currently building?"

`tested/` contains verified implementations and patterns:

> "What do we know actually works?"

A pattern discovered and tested during Add-in development can later be documented in `tested/`.

---

## Relationship to examples/

The distinction is:

    addins/
    Active development projects

    examples/
    Reusable demonstrations and implementation examples

An Add-in project should not automatically be copied into `examples/`.

Extract only the reusable pattern when appropriate.

---

## Relationship to templates/

The distinction is:

    templates/
    Starting point for a new Add-in

    addins/
    Actual Add-in project built from a template

---

## Version Information

Each Add-in should make its target environment clear where practical.

Document relevant information such as:

- Autodesk Inventor version;
- .NET version;
- language;
- Interop version;
- target framework;
- required dependencies.

See:

    knowledge/api-compatibility.md

---

## What does NOT belong here?

Do not use this directory for:

- generic API documentation;
- old training material;
- disposable test CAD files;
- unrelated experiments;
- compiled build output;
- large third-party source repositories.

---

## Design Principle

`addins/` answers:

> "What actual Inventor Add-in projects are we developing?"
