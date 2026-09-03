# Coding Standards — Autodesk Inventor

## Purpose

Define coding standards for Inventor automation and Add-in development.

These rules apply primarily to:

- C#
- VB.NET
- iLogic

---

## 1. General Principles

Generated code should be:

- clear;
- maintainable;
- predictable;
- testable;
- explicit;
- as simple as reasonably possible.

Avoid unnecessary abstraction.

---

## 2. Naming

Use meaningful names.

Prefer:

    componentOccurrence
    targetParameter
    activeDocument
    selectedFace

Avoid meaningless names such as:

    x
    tmp
    obj1
    data2
    thing

unless the scope makes the meaning obvious.

---

## 3. Methods

Prefer methods with one clear responsibility.

Avoid large methods that:

- find objects;
- validate input;
- modify the model;
- update the UI;
- handle errors;
- perform unrelated operations.

Split responsibilities when this improves clarity.

---

## 4. API Context

Do not hide important Inventor API context.

Code should make it reasonably clear:

- which document is being accessed;
- which ComponentDefinition is being used;
- which occurrence is targeted;
- whether the operation is Part or Assembly specific.

---

## 5. Null / Nothing Handling

Do not assume Inventor API objects always exist.

Check relevant references before use.

Potentially missing objects include:

- ActiveDocument
- ComponentOccurrence
- Parameter
- Feature
- Sketch
- Face
- Edge
- referenced Document

---

## 6. Error Handling

Handle expected failures explicitly.

Examples:

- wrong document type;
- missing parameter;
- missing feature;
- invalid value;
- missing file;
- API exception;
- unavailable reference;
- invalid Assembly context.

Do not silently swallow exceptions unless that behavior is intentional.

---

## 7. Error Messages

Error messages should provide useful context.

Prefer:

    Unable to find parameter 'Width' in the active Part document.

over:

    Error.

For development and debugging, include relevant context where appropriate.

---

## 8. Magic Numbers

Avoid unexplained numeric constants.

Bad:

    value = 25

Better:

    minimumThickness = 25

For unit-sensitive values, explicitly document or encode the intended unit.

---

## 9. Hardcoded Paths

Avoid hardcoded Autodesk installation paths.

Do not assume that:

    C:\Program Files\Autodesk\Inventor 2026\

is valid on every machine.

Use configurable paths or discover installation paths where appropriate.

---

## 10. Units

Do not hide unit conversions inside arbitrary calculations.

Prefer explicit unit handling.

When a value represents a physical quantity, make the intended unit clear.

See:

    knowledge/units.md

---

## 11. Performance

Avoid unnecessary:

- Inventor API calls;
- document updates;
- geometry queries;
- recursive traversal;
- UI updates;
- document opens/closes;
- repeated parameter lookups.

For large assemblies, performance considerations become especially important.

---

## 12. Model Updates

Do not trigger unnecessary model updates.

When multiple related changes are required, consider whether they can safely be performed before a final update.

Do not suppress required updates merely for performance.

Correct model state takes priority.

---

## 13. Transactions

Use Inventor transactions when they provide a meaningful undo/rollback boundary.

Do not use transactions for purely read-only operations.

When using transactions:

- start at the appropriate scope;
- commit on success;
- abort on failure where appropriate.

---

## 14. Comments

Comments should explain:

- why something is done;
- API workarounds;
- non-obvious Inventor behavior;
- version-specific behavior;
- important limitations.

Avoid comments that merely restate obvious code.

Bad:

    // Set width to 20
    width = 20

Better:

    // Inventor requires this value to be supplied in the API's expected unit.

---

## 15. Existing Code

When modifying existing code:

- preserve working functionality;
- avoid unrelated formatting changes;
- avoid unnecessary rewrites;
- keep the diff focused;
- preserve established architecture unless there is a clear reason to change it.

---

## 16. API Calls

Prefer direct, well-understood API usage over complicated chains of speculative calls.

When an API call is uncertain, verify it before committing the implementation.

---

## 17. Logging and Diagnostics

For Add-ins and complex automation, diagnostic logging can be useful.

Log meaningful information such as:

- operation;
- document;
- object identifier;
- error;
- exception;
- relevant state.

Do not flood logs with unnecessary API details.

---

## 18. Security and Reliability

Do not execute external files, commands, scripts, or installers unless explicitly required.

Do not silently modify files outside the intended workspace or document context.

---

## 19. General Rule

Prefer:

Simple
>
Explicit
>
Verified
>
Maintainable

over:

Clever
>
Implicit
>
Speculative
>
Over-engineered
