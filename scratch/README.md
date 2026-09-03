# Scratch

## Purpose

The `scratch/` directory is the temporary workspace for experimental
code and files.

It is intended for work that is being developed or tested but is not
yet part of a permanent project.

---

## Use Scratch For

Examples include:

- temporary iLogic rules;
- temporary VB.NET snippets;
- temporary C# snippets;
- API experiments;
- small test scripts;
- intermediate code;
- temporary generated files;
- code intended to be copied or manually tested in Autodesk Inventor.

---

## Typical Workflow

    Cline
        ->
    Create experimental code
        ->
    Save in scratch/
        ->
    User tests in Autodesk Inventor
        ->
    Feedback
        ->
    Cline modifies code
        ->
    Test again

This allows experimental code to remain separate from actual
Add-in projects.

---

## Status

Files in `scratch/` are considered:

    Experimental
    Potentially incomplete
    Potentially untested

A file in `scratch/` must never automatically be considered verified.

---

## After Successful Testing

After an experiment works, determine whether it has permanent value.

### One-time experiment

If it has no future value:

    Delete when no longer needed.

### Reusable API or implementation pattern

Extract the reusable information into:

    tested/

Do not copy an entire project when only a small pattern is useful.

### Actual Add-in

If the experiment becomes a real .NET Add-in:

    scratch/
        ->
    addins/

The Add-in in `addins/` becomes the authoritative project.

Do not maintain a duplicate copy in `tested/`.

---

## Relationship to Other Directories

    scratch/
    Temporary experimental work

    cadfiles/
    Disposable Inventor CAD files

    tested/
    Verified reusable patterns

    addins/
    Actual Add-in projects

    templates/
    Starting points for new projects

Scratch is therefore a temporary development area, not a permanent
knowledge or project repository.
