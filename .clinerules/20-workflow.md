# Development Workflow

## Purpose

This file defines the standard execution workflow for Autodesk Inventor development tasks.

The validation and repair behavior is defined in:

`.clinerules/15-validation-loop.md`

All executable development tasks must follow that loop.

---

## Phase 1 — Understand

Before writing code:

1. Read the user requirement.
2. Identify the requested behavior.
3. Identify constraints.
4. Identify the programming environment.
5. Identify the Autodesk Inventor version.
6. Identify the document type.
7. Identify relevant objects.
8. Identify required inputs and outputs.

Do not implement before the required context is understood.

---

## Phase 2 — Inspect

Inspect the existing project before creating or changing files.

Check:

* Existing source code
* Existing project structure
* Existing iLogic rules
* Existing Add-ins
* Existing templates
* `knowledge/`
* `tested/`
* `scratch/`

Prefer reuse over duplication.

---

## Phase 3 — Knowledge Lookup

Search the most relevant knowledge sources.

For iLogic:

* `knowledge/ilogic.md`
* `knowledge/parameters.md`
* `knowledge/units.md`

For Add-ins:

* `knowledge/addins.md`
* `knowledge/api-compatibility.md`

For object relationships:

* `knowledge/object-model.md`
* relevant domain-specific knowledge

Do not load unrelated knowledge.

---

## Phase 4 — Tested Pattern Lookup

Search `tested/` before implementing unfamiliar or reusable functionality.

Evaluate:

* Inventor version
* Programming environment
* Document type
* Object context
* API context
* Validation status

Reuse an existing verified pattern when it matches the current context.

---

## Phase 5 — API Verification

For every unfamiliar API member:

1. Verify object type.
2. Verify member existence.
3. Verify parameters.
4. Verify return type.
5. Verify object/context requirements.
6. Verify target Inventor version.
7. Check for an existing tested implementation.

Do not rely on guessed member names.

---

## Phase 6 — Plan

Before implementation, define:

* Required behavior
* Relevant API objects
* Main execution flow
* Validation method
* Expected failure points
* Required external environment

Keep the plan proportional to the task.

Do not introduce unnecessary architecture.

---

## Phase 7 — Implement

Implement the smallest reasonable solution.

Requirements:

* Follow existing project conventions.
* Use verified API.
* Handle expected failure cases.
* Respect document context.
* Respect units.
* Preserve existing working behavior.
* Avoid unrelated refactoring.

For temporary experiments, use `scratch/`.

---

## Phase 8 — Review

Before validation:

1. Check syntax.
2. Check API usage.
3. Check object/context assumptions.
4. Check null/reference risks.
5. Check units.
6. Check error handling.
7. Check whether the implementation satisfies the original requirement.

Do not treat review as runtime verification.

---

## Phase 9 — Validate

Validate in the appropriate environment.

### iLogic

Run the rule in Autodesk Inventor.

### .NET Add-in

Build in Visual Studio, then load and test in Autodesk Inventor.

### API Experiment

Execute the experiment in the relevant Inventor environment.

### External Dependency

Validate after the required dependency becomes available.

Capture exact errors and results.

---

## Phase 10 — Repair

When validation fails:

1. Capture the exact failure.
2. Classify the failure.
3. Determine the most likely root cause.
4. Compare with previous iterations.
5. Check `tested/`.
6. Check relevant `knowledge/`.
7. Verify the relevant API/context.
8. Apply the smallest reasonable fix.
9. Validate again.

Do not restart from scratch unless evidence shows the implementation approach is fundamentally incorrect.

Follow `.clinerules/15-validation-loop.md`.

---

## Phase 11 — Repeated Failure Handling

When the same error appears more than once:

1. Stop repeating the current approach.
2. Identify the repeated assumption.
3. Determine why the previous correction failed.
4. Obtain additional evidence.
5. Change the hypothesis.
6. Apply a targeted correction.
7. Validate again.

A repeated failure is evidence that the current reasoning is insufficient.

---

## Phase 12 — Completion

A task is complete only when:

* requested behavior is implemented;
* relevant API assumptions are verified;
* validation has been attempted;
* known errors are resolved or explained;
* final status is known;
* reusable verified information is preserved.

---

## iLogic Workflow

For an iLogic task:

1. Identify the active document.
2. Identify the document type.
3. Identify the required Inventor objects.
4. Check `knowledge/ilogic.md`.
5. Check relevant parameter and unit knowledge.
6. Search `tested/`.
7. Verify unfamiliar API members.
8. Implement.
9. Review.
10. Run in Autodesk Inventor.
11. Capture exact result.
12. Enter the repair loop when validation fails.
13. Confirm requested behavior.
14. Record reusable verified findings.

Do not mark an iLogic rule `VERIFIED` merely because the rule was saved.

---

## Add-in Workflow

For a .NET Add-in:

1. Identify language.
2. Identify Add-in architecture.
3. Identify target Inventor version.
4. Check `knowledge/addins.md`.
5. Check `knowledge/api-compatibility.md`.
6. Search `tested/`.
7. Verify API usage.
8. Implement or modify the solution.
9. Build in Visual Studio.
10. Resolve compile failures.
11. Load the Add-in into Autodesk Inventor.
12. Execute the requested functionality.
13. Capture runtime results.
14. Enter the repair loop when validation fails.
15. Confirm requested behavior.
16. Record reusable verified findings.

A successful build is not sufficient for `VERIFIED`.

---

## Existing Code Workflow

When modifying existing code:

1. Read the full relevant section.
2. Identify existing behavior.
3. Identify the failure or requested change.
4. Avoid changing unrelated functionality.
5. Make the smallest reasonable modification.
6. Validate existing and new behavior where practical.
7. Enter the repair loop if validation fails.

---

## Migration Workflow

When updating old Inventor code:

1. Determine original Inventor version.
2. Determine programming environment.
3. Determine framework/runtime version.
4. Determine Interop version where applicable.
5. Check `knowledge/api-compatibility.md`.
6. Verify every affected API member.
7. Update incompatible code.
8. Build if applicable.
9. Runtime-test in Autodesk Inventor.
10. Enter the repair loop if validation fails.
11. Preserve reusable migration knowledge.

Do not modernize unrelated code during a migration unless required.

---

## Scratch Workflow

Use `scratch/` for temporary experiments.

Typical sequence:

```
Create experiment
    ->
Run in target environment
    ->
Capture result
    ->
Repair if required
    ->
Validate
    ->
Promote verified result or discard
```

Do not treat files in `scratch/` as production-ready.

Do not promote failed experiments to `tested/`.

---

## Knowledge Classification After Validation

After a task is verified, all information produced during development must be classified and placed in the correct location. Do not leave all information in a single large report file.

### Information types and their target locations

| Information type | Target location | Notes |
|---|---|---|
| Reusable, verified implementation pattern | `tested/<environment>/<name>.md` + code file | Concise. Purpose, context, implementation reference, limitations only. For patterns, not completed functions. |
| General technical fact or API behaviour | `knowledge/<topic>.md` | Reusable across tasks. Update existing files rather than creating new ones when the topic already exists. |
| Verified failed API attempt / confirmed limitation | `knowledge/errors/<environment>/<name>.md` | Use the template in `.clinerules/15-validation-loop.md` → Error Memory section. |
| Project-specific documentation | Project folder | Keep task-specific docs with the project, not in `tested/`. |
| Future idea / enhancement proposal | `scratch/` or a backlog file | Not in `tested/` or `knowledge/` unless it is a verified technical fact. |
| Usage instructions for a specific task | Project documentation, not `tested/` | `tested/` is not a how-to-run manual. |
| Completed user-ready iLogic function | `addins/<FunctionName>/` | Contains `.vb` source and `README.md`. Folder name matches function name. Only when explicitly ready for use. |
| Development history / repair log | Discard | Not needed after verification. Save only the final working state. |

### `tested/` file structure

`tested/` is for reusable implementation patterns only, not completed functions.

A `tested/` entry should normally contain:

- **Purpose** — one sentence describing what the pattern does.
- **Context** — Inventor version, programming environment, document type, relevant objects.
- **Verified pattern** — a reference to the code file, plus a short prose description of the reusable pattern. Do not paste the full code again if the file already exists.
- **Validation** — how the pattern was tested and when.
- **Status** — `VERIFIED`.
- **Important limitations** — context-specific constraints that affect reuse.
- **Related** — links to relevant `knowledge/` and `knowledge/errors/` files.

Do **not** put in `tested/`:

- completed production functions (use `addins/<FunctionName>/` instead);
- complete user-facing iLogic tools (use `addins/<FunctionName>/` instead);
- every successfully tested function;
- step-by-step usage instructions;
- expected MessageBox content or UI screenshots;
- development history;
- failed attempts (those belong in `knowledge/errors/`);
- future ideas;
- automatic copies of completed source files.

A successful validation does not automatically create a `tested/` entry.

### Updating existing knowledge files

When a verified finding extends an existing topic, append to the existing `knowledge/` file rather than creating a new file. When creating a new topic, place it in the most specific existing subdirectory or create a new subdirectory if warranted.

### Keeping `tested/` and `knowledge/` in sync

When a new `tested/` entry is created, update the **Related** section of that entry to point to any relevant `knowledge/errors/` entries that were also discovered during the task.

### Promoting reusable findings from `tested/`

If a `tested/` file contains a general lesson (e.g., "prefer Try/Catch over DocumentTypeEnum"), extract it and move the lesson to the appropriate `knowledge/` file. The `tested/` entry should then only reference the knowledge file, not duplicate its content.

---

## Knowledge Promotion

See the **Knowledge Classification After Validation** section above for the complete routing table and rules.

The key rule: a successful test does not automatically mean that the entire development result belongs in `tested/`. Classify each piece of information separately.

---

## Final Response Format

At the end of a development task, report:

```
Status: <GENERATED | REVIEWED | BUILT | RUNTIME-TESTED | VERIFIED | BLOCKED | UNRESOLVED>
Iterations: <number>
Environment: <environment>
Inventor Version: <version>
Validation: <result>
Remaining Issues: <none or description>
```

When relevant, also report:

* files created or modified;
* important API decisions;
* known limitations;
* reusable knowledge created.

Never claim a result that has not been verified.

---

## Definition of Done

The task is done only when the requested behavior is implemented and the final validation status is known.

A solution that only appears correct is not considered verified.
