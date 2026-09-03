# Tested

## Purpose

The `tested/` directory contains small, reusable patterns and API
behaviors that have been actually verified in Autodesk Inventor.

The purpose is to give the AI a collection of proven implementations
that can be reused in future tasks.

---

## What Belongs Here

Examples include:

- verified Inventor API usage;
- verified iLogic techniques;
- verified parameter operations;
- verified assembly operations;
- verified document operations;
- documented Inventor-specific behavior;
- small reusable implementation patterns.

Each item should clearly state the environment in which it was tested.

Where relevant, include:

- Inventor version;
- programming environment;
- document type;
- expected behavior;
- actual behavior;
- important limitations.

---

## What Does Not Belong Here

Do not use this directory for:

- temporary experiments;
- unfinished code;
- backup copies;
- complete Add-in projects;
- copies of projects from `addins/`;
- unverified API assumptions.

Temporary experiments belong in:

    scratch/

Complete Add-in projects belong in:

    addins/

---

## Verification

Content in `tested/` must have actually been tested.

Do not mark information as verified merely because:

- it compiles;
- it looks correct;
- an AI generated it;
- it appears in an old example;
- it is plausible.

Runtime behavior should be verified in Autodesk Inventor where
runtime behavior is relevant.

---

## Relationship to Add-ins

A complete Add-in remains in:

    addins/

Do not copy the complete Add-in into `tested/`.

If an Add-in produces a useful reusable pattern, extract only that
pattern.

Example:

    addins/ParameterTools/
        |
        |  complete Add-in
        |
        +----> tested/parameters/
                   |
                   +-- parameter-value-units.md

This avoids maintaining two copies of the same project.

---

## Relationship to Scratch

Typical workflow:

    scratch/
        ->
    test in Inventor
        ->
    verified result
        ->
    tested/

Only reusable knowledge should be extracted.

A temporary experiment that has no future value does not need to
be preserved.

---

## Version Awareness

A tested result is valid for the environment in which it was tested.

Always consider:

- Inventor version;
- programming environment;
- document type;
- API context.

Do not automatically assume that a tested pattern is valid in every
Inventor release or context.
