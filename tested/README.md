# tested

## Purpose

This directory contains implementations that have been tested against a real Autodesk Inventor environment.

Tested code has a higher confidence level than generic examples or model-generated code.

---

## What belongs here?

Store code that has been actually tested.

Examples:

- working iLogic rules;
- working C# Add-in components;
- working VB.NET code;
- verified API patterns;
- tested Assembly operations;
- tested parameter operations;
- tested UI functionality.

---

## Required Context

Whenever practical, record:

- Inventor version;
- programming environment;
- language;
- document type;
- test scenario;
- expected result;
- actual result;
- known limitations.

Example:

    Inventor:
    2026

    Environment:
    iLogic

    Document:
    Part (.ipt)

    Purpose:
    Update a User Parameter

    Status:
    VERIFIED

---

## Confidence Levels

Use clear status labels where useful:

### VERIFIED

Successfully tested against the stated Inventor version.

### PARTIALLY VERIFIED

The main functionality works, but not all scenarios have been tested.

### LEGACY VERIFIED

Successfully tested, but against an older Inventor version.

### EXPERIMENTAL

Tested experimentally but not yet considered stable.

---

## What does NOT belong here?

Do not store code here merely because:

- it compiles;
- it looks correct;
- an AI generated it;
- it came from a GitHub example;
- it came from old Autodesk training.

Actual testing is required before calling code verified.

---

## Relationship to examples/

The distinction is:

    examples/
    "This demonstrates how something could work."

    tested/
    "This implementation has actually been tested."

A tested example may exist in both locations when that is useful.

---

## Design Principle

`tested/` answers:

> "What do we know actually works?"

This directory should become increasingly valuable over time because it captures real-world, version-specific experience.
