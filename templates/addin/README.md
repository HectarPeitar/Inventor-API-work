# Inventor Add-in Template

## Purpose

- This directory contains the starting template for new Autodesk Inventor .NET Add-in projects.
- The template provides a known, tested project structure so new Add-ins do not have to be created from scratch.
- The template is a starting point, not an active development project.

---

## Template vs Active Add-in

Keep the distinction clear:

    templates/addin/
        Starting point for new Add-ins

    addins/
        Actual Add-in projects under development

Never use the template directory as the working directory for an actual Add-in project.

---

## When to Use This Template

Use this template when creating a new Autodesk Inventor .NET Add-in.

Before creating the project:

1. Determine the target Inventor version.
2. Check `knowledge/api-compatibility.md`.
3. Check `knowledge/addins.md`.
4. Check `tested/` for relevant proven patterns.
5. Use this template as the starting point when it matches the target environment.

---

## Creating a New Add-in

A new Add-in should be created under:

    addins/

For example:

    templates/addin/
        ↓
    addins/ParameterTools/

The template itself should remain unchanged.

Project-specific modifications belong in the new project under `addins/`.

---

## Development Workflow

The normal workflow is:

    Cline / VS Code
        ↓
    Create project from template
        ↓
    addins/MyAddin/
        ↓
    Modify source code
        ↓
    Open solution in Visual Studio
        ↓
    Build
        ↓
    Debug / attach to Autodesk Inventor
        ↓
    Test in Autodesk Inventor
        ↓
    Validate behavior
        ↓
    Record verified patterns in tested/

Cline may prepare and modify source code and project files.

Visual Studio is used for building and debugging the .NET Add-in.

Autodesk Inventor is the runtime and primary validation environment.

---

## Template Integrity

Do not modify the template to solve a problem that belongs to a specific Add-in project.

If a project requires a project-specific change:

    Modify the project in addins/

If the same improvement is useful for every future Add-in:

    Consider updating the template.

Template changes should preferably be tested before becoming the new default.

---

## Version Compatibility

The template is version-specific.

Do not assume that a template created for one Inventor release is automatically valid for another release.

Check:

    knowledge/api-compatibility.md

before changing:

- Inventor references;
- Autodesk.Inventor.Interop;
- target framework;
- .NET version;
- project configuration;
- Add-in registration;
- deployment configuration.

---

## Build and Runtime Verification

The existence of a project file does not mean that the template works.

A template should be considered verified only after:

1. The project builds successfully.
2. The required Inventor references resolve correctly.
3. The Add-in can be loaded by Autodesk Inventor.
4. The Add-in lifecycle works correctly.
5. Basic Add-in functionality has been tested.

Do not describe a template as verified unless these conditions have actually been tested.

---

## Relationship to Other Directories

### `.clinerules/`

Defines how Cline should work.

### `knowledge/`

Contains technical knowledge about Inventor and its APIs.

### `reference/`

Contains original external source material.

### `examples/`

Contains reusable implementation examples.

### `tested/`

Contains implementations and patterns that have actually been tested.

### `templates/`

Contains starting points for new projects.

### `addins/`

Contains active development projects.

### `cadfiles/`

Contains safe, disposable Inventor documents for testing.

---

## Design Principle

This directory answers:

> "What should Cline use as the starting point for a new Inventor Add-in?"

The template should remain minimal, predictable, version-aware, and tested.
