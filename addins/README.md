# Add-ins

## Purpose

The `addins/` directory contains the actual Autodesk Inventor .NET
Add-in projects being developed and maintained.

Each Add-in should have one authoritative project location here.

---

## What Belongs Here

Examples include:

- C# Inventor Add-ins;
- VB.NET Inventor Add-ins;
- Visual Studio solutions;
- Add-in project files;
- Add-in source code;
- Add-in configuration;
- Add-in-specific resources.

A complete Add-in project belongs here even after it has been
successfully tested.

---

## Development Workflow

For a new Add-in:

    templates/addin/
        ->
    addins/MyAddin/
        ->
    Visual Studio
        ->
    Build
        ->
    Autodesk Inventor
        ->
    Test
        ->
    Verify

Cline may create and modify the project from VS Code.

Visual Studio is used to build and debug the Add-in.

Autodesk Inventor is used to test the Add-in at runtime.

---

## Experimental Add-in Work

Small experiments that are not yet a real Add-in project may be
created in:

    scratch/

When the experiment becomes an actual Add-in project, move or
develop it under:

    addins/

The resulting Add-in should have only one authoritative project
location.

---

## Testing

An Add-in is not considered verified simply because:

- the source code exists;
- Cline generated the code;
- the project opens in Visual Studio;
- the project compiles.

A complete Add-in should be considered verified only after the
required functionality has been tested inside Autodesk Inventor.

Testing should use appropriate disposable CAD files from:

    cadfiles/

---

## Tested Patterns

Do not copy complete Add-ins into:

    tested/

Instead, extract reusable patterns from a verified Add-in.

For example:

    addins/MyAddin/
        |
        +----> tested/parameters/
                   |
                   +-- parameter-value-units.md

The Add-in remains in `addins/`.

The reusable pattern is documented separately in `tested/`.

---

## Templates

New Add-ins should normally start from:

    templates/addin/

Do not modify the template to solve project-specific problems.

Project-specific changes belong in the Add-in project under:

    addins/

If a change should apply to future Add-ins, update the template
separately and test the updated template.

---

## Version Awareness

Each Add-in should clearly target a known Inventor version and
compatible development environment.

Before creating or modifying an Add-in, check:

    knowledge/api-compatibility.md

and:

    knowledge/addins.md

---

## Authoritative Location

The complete Add-in source in `addins/` is the authoritative
project.

Do not maintain duplicate copies of the same Add-in elsewhere
in the workspace.
