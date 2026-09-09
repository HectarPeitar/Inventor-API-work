# Coding Standards — Autodesk Inventor

## Purpose

Define coding standards for Autodesk Inventor automation and Add-in development.

These standards apply primarily to:

* C#
* VB.NET
* iLogic

The global Cline development rule defines general coding philosophy and communication behavior.

This file defines **Inventor-specific coding and workspace standards**.

---

# 1. Naming

Use meaningful names that communicate the purpose of the value or object.

Prefer:

```text
componentOccurrence
targetParameter
activeDocument
selectedFace
```

Avoid meaningless names such as:

```text
x
tmp
obj1
data2
thing
```

Short names are acceptable when their meaning is obvious from the scope and context.

---

# 2. Methods

Prefer methods with one clear responsibility.

Avoid methods that unnecessarily combine unrelated responsibilities such as:

* finding objects;
* validating input;
* modifying the model;
* updating the UI;
* handling errors;
* performing unrelated operations.

Separate responsibilities when doing so improves clarity and maintainability.

Do not create abstractions solely to satisfy an idealized architecture.

---

# 3. Inventor API Context

Code should make important Inventor context reasonably clear.

Where relevant, make it clear:

* which document is being accessed;
* which ComponentDefinition is being used;
* which occurrence is targeted;
* whether the operation is Part or Assembly specific;
* whether an object is native or a proxy;
* whether the operation depends on document state.

Do not hide critical Inventor context behind unnecessary abstraction.

---

# 4. Null / Nothing Handling

Do not assume Inventor API references always exist.

Check relevant references before use.

Potentially missing objects include:

* `ActiveDocument`
* `ComponentOccurrence`
* `Parameter`
* `Feature`
* `Sketch`
* `Face`
* `Edge`
* referenced `Document`

Handle missing references according to the actual requirements of the operation.

---

# 5. Error Handling

Handle expected failures explicitly.

Examples include:

* wrong document type;
* missing parameter;
* missing feature;
* invalid value;
* missing file;
* API exception;
* unavailable reference;
* invalid Assembly context.

Do not silently swallow exceptions unless that behavior is intentional and appropriate.

---

# 6. Error Messages

Error messages should provide useful context.

Prefer:

```text
Unable to find parameter 'Width' in the active Part document.
```

over:

```text
Error.
```

For development and debugging, include relevant context when useful.

---

# 7. Magic Numbers

Avoid unexplained numeric constants.

Bad:

```text
value = 25
```

Better:

```text
minimumThickness = 25
```

For unit-sensitive values, explicitly identify the intended unit or use an appropriate unit-aware representation.

---

# 8. Hardcoded Paths

Avoid hardcoded Autodesk installation paths.

Do not assume:

```text
C:\Program Files\Autodesk\Inventor 2026\
```

is valid on every machine.

Use configurable paths or discover installation paths where appropriate.

---

# 9. Units

Do not hide unit conversions inside arbitrary calculations.

Prefer explicit unit handling.

When a value represents a physical quantity, make the intended unit clear.

Use:

```text
knowledge/units.md
```

when relevant.

---

# 10. Performance

Avoid unnecessary:

* Inventor API calls;
* document updates;
* geometry queries;
* recursive traversal;
* UI updates;
* document opens/closes;
* repeated parameter lookups.

Performance becomes particularly important for large assemblies.

Do not sacrifice correctness merely to reduce API calls.

---

# 11. Model Updates

Do not trigger unnecessary Inventor model updates.

When multiple related changes are required, consider whether they can safely be performed before a final update.

Do not suppress required updates merely for performance.

Correct model state takes priority.

---

# 12. Transactions

Use Inventor transactions when they provide a meaningful undo/rollback boundary.

Do not use transactions for purely read-only operations.

When using transactions:

* start at the appropriate scope;
* commit on success;
* abort on failure where appropriate.

---

# 13. Comments

Comments should explain non-obvious reasons, including:

* why something is done;
* API workarounds;
* non-obvious Inventor behavior;
* version-specific behavior;
* important limitations.

Avoid comments that merely restate the code.

Bad:

```vb
' Set width to 20
width = 20
```

Better:

```vb
' Inventor requires this value to be supplied in the API's expected unit.
```

---

# 14. Logging and Diagnostics

For Add-ins and complex automation, diagnostic logging can be useful.

Log meaningful information such as:

* operation;
* document;
* object identifier;
* error;
* exception;
* relevant state.

Do not flood logs with unnecessary API details.

---

# 15. Existing Code

When modifying existing code:

1. Preserve working functionality.
2. Avoid unrelated formatting changes.
3. Avoid unnecessary rewrites.
4. Keep the diff focused.
5. Preserve established architecture unless there is a clear reason to change it.

The global development rule defines the general minimal-change principle.

This section applies that principle specifically to Inventor code.

---

# 16. API Calls

Prefer direct, well-understood API usage over complicated chains of speculative calls.

When an API call is uncertain, verify it before committing the implementation.

Follow the API evidence hierarchy defined in:

```text
.clinerules/00-core.md
```

---

# 17. Security and Reliability

Do not execute external files, commands, scripts, or installers unless explicitly required.

Do not silently modify files outside the intended workspace or document context.

---

# 18. Debug Mode for iLogic Testing

When developing iLogic rules that will be validated in Autodesk Inventor:

1. Add a `DebugMode` constant at the rule level.
2. When `DebugMode = True`, write the report to a text file in `scratch/`.
3. When `DebugMode = False`, use the intended production behavior.
4. After verification, set `DebugMode = False`.
5. Remove temporary text files from `scratch/`.

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

# 19. File Management

When modifying, extending, debugging, or improving existing functionality:

1. Search the workspace for an existing implementation before creating a new source file.
2. Identify the canonical source file.
3. Read the existing implementation completely before changing it.
4. Modify the existing implementation in place.
5. Preserve its file name and location unless there is an explicit reason to change them.
6. Do not create duplicate implementations of the same functionality.
7. During repair iterations, continue modifying the existing implementation.
8. Create a new file only when:

   * the user explicitly requests one;
   * the functionality is genuinely separate;
   * the architecture requires a separate file;
   * or a new implementation is explicitly required.
9. Apply the same principle to `tested/`: extend an existing tested implementation when appropriate instead of creating a duplicate.
10. Before creating any file, verify that the requested functionality does not already exist elsewhere in the workspace.

---

# 20. Storage Locations

Use these storage conventions:

| Output type                              | Location                          |
| ---------------------------------------- | --------------------------------- |
| New or modified production function      | source/project location           |
| Reusable verified implementation pattern | `tested/`                         |
| General reusable technical knowledge     | `knowledge/`                      |
| Verified negative knowledge              | `knowledge/errors/`               |
| Completed user-ready iLogic function     | `addins/<FunctionName>/`          |
| Completed function documentation         | `addins/<FunctionName>/README.md` |
| Temporary experiments                    | `scratch/`                        |

---

# 21. `tested/` — Reusable Patterns Only

`tested/` is a knowledge library, not a storage location for completed functions.

Use it for:

* concise reusable implementation patterns;
* verified API usage patterns;
* verified code fragments;
* reusable examples useful for future development.

Do not use it for:

* completed production functions;
* complete user-facing iLogic tools;
* every successfully tested function;
* project-specific implementations;
* user manuals;
* release documentation;
* automatic copies of completed source files.

A successful validation does not automatically create a `tested/` entry.

Create or update `tested/` only when the result contains a genuinely reusable implementation pattern.

---

# 22. Eligibility for `tested/`

A pattern is eligible for `tested/` only when all of the following are true:

1. It is verified in the stated environment.
2. It has meaningful reuse value beyond the current function.
3. It is not trivial boilerplate or an obvious one-line API call.
4. It is not specific to one business function.
5. It is independently useful in future Inventor/iLogic development.
6. Storing it will materially help future development, reliability, or API discovery.

When in doubt, do not promote it to `tested/`.

The goal is a small, high-confidence library rather than an archive of successful tasks.

Prefer:

```text
tested/ilogic/parameter-expression-and-units.md
```

over many tiny files when related patterns form one reusable topic.

---

# 23. `addins/` — Completed Functions

When an iLogic function is fully completed, validated, and explicitly ready for use, it belongs in:

```text
addins/<FunctionName>/
```

with:

```text
<FunctionName>.vb
README.md
```

The folder name must match the function name.

Example:

```text
addins/
└── ValidateAndSetParameters/
    ├── ValidateAndSetParameters.vb
    └── README.md
```

Before promotion:

1. The function must be implemented.
2. Relevant validation must pass.
3. Known runtime and compile errors must be resolved.
4. Requested behavior must be verified.
5. Validation status must be known.
6. The implementation must be clean enough for reuse.
7. Temporary debugging code must be removed unless intentionally part of the function.

Do not promote unfinished or unresolved functionality.

---

# 24. Modifying an Existing Function in `addins/`

If the function already exists in:

```text
addins/<FunctionName>/
```

treat it as the primary completed implementation unless the task explicitly requires a new function.

After modification:

* validate it;
* update the existing README when behavior or usage changes;
* update relevant `knowledge/` or `tested/` entries when genuinely reusable knowledge is discovered.

Do not create:

```text
<FunctionName>V2
<FunctionName>Final
<FunctionName>New
```

unless explicitly requested.

---

# 25. No Automatic Promotion

Do not automatically promote every successfully completed task to `addins/`.

The default lifecycle is:

```text
Develop
    ↓
Validate
    ↓
Repair if necessary
    ↓
Verified
    ↓
Ready for use?
    ├── No → keep in source/project location
    └── Yes → promote to addins/<FunctionName>/
```

---

# 26. `README.md` for Completed Functions

A README in:

```text
addins/<FunctionName>/README.md
```

should document practical use.

It may contain:

* purpose;
* behavior;
* requirements;
* supported document types;
* required parameters;
* required setup;
* installation/use;
* expected behavior;
* validation result;
* known limitations;
* important configuration;
* example usage.

Keep it focused on using and understanding the completed function.

Do not use it as a development diary.

Reusable negative knowledge belongs in:

```text
knowledge/errors/
```

---

# 27. Tool Usage for File Operations

When modifying, creating, or replacing file contents, use the Cline editor/file-editing capability directly.

Do not use a shell or programming script for a simple text edit when the editor can perform it safely.

Use command execution for operations that genuinely require commands, such as:

* Git operations;
* builds and compilation;
* file listings and inspections;
* running external programs;
* command-line searching;
* other operations that cannot be performed appropriately by the editor.

Use `scratch/` scripts only for genuinely complex transformations, programming experiments, or one-off operations requiring procedural logic.

Do not create scripts merely to perform a simple file write or replacement.
