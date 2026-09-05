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

Prefer deletion over addition. Remove unnecessary code when it is safe to do so.

Avoid adding new dependencies when existing project capabilities or native Inventor/iLogic functionality can solve the problem.

Avoid boilerplate that nobody asked for.

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

---

## 20. Debug Mode for Testing

When developing iLogic rules that will be validated in Autodesk Inventor:

1. Add a `DebugMode` constant at the rule level.
2. When `DebugMode = True`, write the report to a text file in `scratch/`.
3. When `DebugMode = False`, only show the MessageBox (production behavior).
4. After verification, set `DebugMode = False` and remove text files from `scratch/`.

Pattern:

```vb
Const DebugMode As Boolean = True
Const DebugOutputFile As String = "<path-to-scratch>\Output.txt"

' ... after building the report ...
If DebugMode Then
    Try
        System.IO.File.WriteAllText(DebugOutputFile, report.ToString())
    Catch
        ' Ignore file write failures
    End Try
End If
MessageBox.Show(report.ToString(), "RuleName")
```

---

## 21. File Management

When modifying, extending, debugging, or improving functionality that already exists:

1. Always search the workspace for an existing implementation before creating a new source file.
2. When the requested functionality already exists, identify the canonical source file.
3. Read the existing implementation completely before making changes.
4. Modify the existing implementation in place.
5. Preserve its file name and location unless there is an explicit reason to change them.
6. Do not create duplicate implementations of the same functionality.
7. During repair iterations, continue modifying the existing implementation instead of creating replacement files.
8. Only create a new file when:
   - the user explicitly requests one;
   - the functionality is genuinely separate;
   - the architecture requires a separate file;
   - or a new implementation is explicitly required.
9. Apply the same rule to `tested/`: when an existing tested implementation is extended, update the existing file rather than creating a second version.
10. Before creating any file, verify that the requested functionality does not already exist elsewhere in the workspace.

Violating this rule produces duplicate implementations, scattered functionality, and maintenance burden.

---

## 22. Function Promotion and Storage

### Storage Locations

| Output type | Location |
|---|---|
| New or modified production function | source/project location |
| Reusable verified implementation pattern | `tested/` |
| General reusable technical knowledge | `knowledge/` |
| Verified negative knowledge | `knowledge/errors/` |
| Completed user-ready iLogic function | `addins/<FunctionName>/` |
| Completed function documentation | `addins/<FunctionName>/README.md` |

### tested/ — Reusable Patterns Only

`tested/` is a knowledge library, not a storage location for completed functions.

Use `tested/` for:

* concise reusable implementation patterns;
* verified API usage patterns;
* verified code fragments;
* reusable examples useful for future development.

Do NOT use `tested/` for:

* completed production functions;
* complete user-facing iLogic tools;
* every successfully tested function;
* project-specific implementations;
* user manuals;
* release documentation;
* automatic copies of completed source files.

A successful validation does not automatically create a `tested/` entry.

Only create or update a `tested/` entry when the result contains a genuinely reusable implementation pattern.

### Reusable Enough for tested/

A pattern is eligible for `tested/` only when ALL of the following are true:

1. It is actually verified in the stated environment.
2. It has meaningful reuse value beyond the current function.
3. It is not trivial boilerplate or an obvious one-line API call.
4. It is not specific to one business function.
5. It is independently useful in future Inventor/iLogic development.
6. Storing it will materially help future development, reliability, or API discovery.

If any mandatory criterion is false, do not create a `tested/` entry.

When in doubt, do not promote to `tested/`.

The source implementation and relevant `knowledge/` files are the default locations for verified work.

`tested/` should be a small, high-confidence library rather than a comprehensive archive of successful work.

#### Decision process

```
Successful implementation
        |
        v
Is it reusable beyond this specific function?
        |
    +---+---+
    |       |
   NO      YES
    |       |
    v       v
Keep      Is it
source    meaningful
only      enough?
              |
          +---+---+
          |       |
         NO      YES
          |       |
          v       v
        Keep   tested/
        source
        only
```

#### Examples

This should generally NOT become a `tested/` entry:

```vb
Dim doc = ThisApplication.ActiveDocument
```

unless it demonstrates some non-obvious, verified Inventor/iLogic behavior that is useful beyond the current task.

This may be appropriate for `tested/`:

* a verified pattern for safely obtaining a PartComponentDefinition in iLogic;
* a verified pattern for setting Inventor parameter expressions with explicit units;
* a verified pattern for handling assembly occurrences recursively;
* a verified pattern for safely working with Inventor proxies;
* a verified pattern for converting or displaying Inventor internal units.

The goal is reusable knowledge, not a collection of tiny snippets.

#### File granularity

Prefer:

```
tested/ilogic/parameter-expression-and-units.md
```

over:

```
tested/ilogic/SetExpression.vb
tested/ilogic/GetValue.vb
tested/ilogic/GetParameter.vb
```

when the related patterns belong to the same reusable topic.

A `tested/` file should represent a meaningful reusable pattern or topic, not merely one API call.

### addins/ — Completed Functions

When an iLogic function is fully completed, validated, and ready for use, it belongs in `addins/`.

Use this structure:

```
addins/
└── <FunctionName>/
    ├── <FunctionName>.vb
    └── README.md
```

The folder name must match the function name.

Example:

```
addins/
└── ValidateAndSetParameters/
    ├── ValidateAndSetParameters.vb
    └── README.md
```

Before promotion:

1. The function must be implemented.
2. The function must pass relevant validation.
3. Known runtime and compile errors must be resolved.
4. The requested behavior must be verified.
5. The function must have a known validation status.
6. The final implementation must be clean enough for reuse.
7. The function must not contain temporary debugging code unless that debugging behavior is intentionally part of the function.

Do not promote unfinished or unresolved functionality to `addins/`.

### Modifying an Existing Function in addins/

If the function already exists in `addins/<FunctionName>/`, treat that as the primary completed implementation unless the task explicitly requires a new function.

After modification:

* validate it;
* update the existing README when behavior or usage changed;
* update relevant `knowledge/` or `tested/` entries when genuinely reusable knowledge was discovered.

Do not create a new folder for every modification.

Do not create `<FunctionName>V2`, `<FunctionName>Final`, `<FunctionName>New`, etc. unless explicitly requested.

### No Automatic Promotion

Do NOT automatically promote every successfully completed task to `addins/`.

Promotion should happen when the function is explicitly considered ready for use.

The default workflow is:

```
New Function
    ->
Develop in source/project location
    ->
Validate
    ->
Repair if necessary
    ->
Verified
    ->
Ready for use?
    |
    +-- NO --> Keep in source/project location
    |
    +-- YES
          ->
    Promote to addins/<FunctionName>/
          ->
    Add <FunctionName>.vb
          ->
    Add README.md
```

### README in addins/<FunctionName>/

A completed function in `addins/` may contain a `README.md`.

Unlike `tested/`, a Markdown file in an `addins/<FunctionName>/` folder IS appropriate because it documents the completed function for practical use.

The README may contain:

* Purpose
* What the function does
* Requirements
* Supported document types
* Required parameters
* Required setup
* How to install/use it
* Expected behavior
* Validation result
* Known limitations
* Important configuration
* Example usage

Keep the README focused on using and understanding the completed function.

Do not use the README as a development diary.

Do not include a long list of every failed API experiment unless that information is genuinely useful to future developers. Store reusable negative knowledge in `knowledge/errors/` instead.
