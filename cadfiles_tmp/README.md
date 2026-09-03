# cadfiles

## Purpose

This directory is the safe CAD sandbox for the Autodesk Inventor AI workspace.

It contains Inventor files that Cline/AI may use for testing, experimentation, debugging, and validation.

Files in this directory should be considered disposable test data.

---

## What belongs here?

Examples:

- test Part files (`.ipt`);
- test Assembly files (`.iam`);
- test Drawing files (`.idw`);
- test Presentation files (`.ipn`);
- other CAD files required for testing.

Use simple, clearly named test files where possible.

Examples:

    TestPart.ipt
    TestAssembly.iam
    TestParameters.ipt
    TestDrawing.idw

---

## Safety

This directory is intentionally separated from important or production CAD files.

Cline/AI may:

- open files;
- modify files;
- create files;
- delete test files;
- run iLogic rules against them;
- use them for debugging.

Do not place important production CAD files in this directory.

---

## Relationship to .clineignore

The `cadfiles/` directory is excluded from normal AI context through `.clineignore`.

This does NOT mean that the files cannot be used for testing.

It means that CAD files should not automatically become part of the AI's general project context.

When a specific CAD file is needed for a task, it can be explicitly provided or opened as part of the testing workflow.

---

## Test Data

Whenever practical, keep test files:

- small;
- reproducible;
- clearly named;
- focused on one feature or behavior;
- independent from production projects.

Avoid unnecessary large assemblies unless the purpose of the test is specifically related to assembly scale or performance.

---

## What does NOT belong here?

Do not store:

- production CAD files;
- customer files;
- confidential project data;
- source code;
- Add-in projects;
- general API documentation.

---

## Design Principle

`cadfiles/` answers:

> "Where can the AI safely experiment with real Inventor documents?"

The directory is a sandbox, not a knowledge base.
