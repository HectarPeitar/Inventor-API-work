# Development Workflow — Autodesk Inventor

## Purpose

This file defines the standard execution workflow for Autodesk Inventor development tasks.

Detailed validation and repair behavior is defined in:

```text
.clinerules/15-validation-loop.md
```

Project context, API evidence, source hierarchy, and knowledge-base policy are defined in:

```text
.clinerules/00-core.md
```

Coding and storage standards are defined in:

```text
.clinerules/10-coding-standards.md
```

Do not duplicate those detailed rules here.

---

# 1. Phase 1 — Understand

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

# 2. Phase 2 — Inspect

Inspect the existing project before creating or modifying files.

Check, as relevant:

* existing source code;
* project structure;
* existing iLogic rules;
* existing Add-ins;
* existing templates;
* `knowledge/`;
* `tested/`;
* `scratch/`.

Search for an existing implementation before creating a new one.

---

# 3. Phase 3 — Knowledge Lookup

For Inventor API work, follow the source hierarchy defined in:

```text
.clinerules/00-core.md
```

Start from:

```text
knowledge/inventor/KNOWLEDGE-MAP.md
```

Use only the knowledge relevant to the current task.

Typical sources include:

```text
knowledge/inventor/2026/ilogic.md
knowledge/ilogic.md
knowledge/parameters.md
knowledge/units.md

knowledge/addins.md
knowledge/api-compatibility.md

knowledge/inventor/2026/object-model.md
knowledge/object-model.md

knowledge/inventor/2026/API-SOURCE-MAP.md
knowledge/inventor/2026/SAMPLE-INDEX.md
```

Do not scan the entire SDK when a narrower source path is available.

---

# 4. Phase 4 — Tested Pattern Lookup

Before implementing unfamiliar or reusable functionality:

1. Search `tested/`.
2. Identify the closest relevant pattern.
3. Compare Inventor version.
4. Compare programming environment.
5. Compare document type.
6. Compare object context.
7. Compare API context.
8. Reuse only when the pattern is applicable.

A tested pattern is evidence, not universal proof.

Do not blindly copy a pattern whose context differs.

---

# 5. Phase 5 — API Verification

For each unfamiliar Inventor API member:

1. Verify object type.
2. Verify member existence.
3. Verify parameters.
4. Verify return type.
5. Verify object/context requirements.
6. Verify target Inventor version.
7. Follow the authoritative source hierarchy in `00-core.md`.
8. Check `knowledge/errors/` for previously confirmed invalid assumptions.
9. Check `tested/` for verified implementations when relevant.

Do not guess API members.
Do not rely on guessed member names merely because they appear plausible.

---

# 6. Phase 6 — Plan

Before implementation, establish:

* required behavior;
* relevant API objects;
* main execution flow;
* validation method;
* expected failure points;
* required external environment.

Keep the plan proportional to the task.

Do not introduce architecture that is not required.

---

# 7. Phase 7 — Choose the Implementation

After understanding the task, use this decision ladder:

1. Does this need to be built at all?
2. Does the functionality already exist in the codebase?
3. Can native Inventor/iLogic functionality solve it?
4. Can an existing project helper, utility, or verified `tested/` pattern solve it?
5. Can an already-installed dependency solve it?
6. Can the solution be simplified without reducing correctness?
7. Implement the minimum necessary solution.

The ladder is applied **after understanding the problem**, not instead of understanding it.

Correctness and verified Inventor behavior take priority over minimizing code.

---

# 8. Phase 8 — Implement

During implementation:

1. Follow existing project conventions.
2. Use verified API usage.
3. Respect document context.
4. Respect units.
5. Handle expected failure cases.
6. Preserve working behavior.
7. Avoid unrelated refactoring.
8. Follow `10-coding-standards.md`.

For temporary experiments, use:

```text
scratch/
```

Do not treat scratch work as production-ready.

---

# 9. Phase 9 — Review

Before validation:

1. Check syntax.
2. Check API usage.
3. Check object/context assumptions.
4. Check null/reference risks.
5. Check units.
6. Check error handling.
7. Check that the implementation satisfies the original requirement.

Review is not runtime verification.

---

# 10. Phase 10 — Validate

Validate in the appropriate environment.

### iLogic

Run the rule in Autodesk Inventor.

### .NET Add-in

Build in Visual Studio, then load and test in Autodesk Inventor.

### API Experiment

Execute the experiment in the relevant Inventor environment.

### External Dependency

Validate after the required dependency becomes available.

Capture exact results and errors.

Follow:

```text
.clinerules/15-validation-loop.md
```

for failures and repair.

---

# 11. Phase 11 — Repair

When validation fails, enter the validation and repair loop defined in:

```text
.clinerules/15-validation-loop.md
```

Do not create a separate informal repair process.

Do not restart from scratch unless evidence shows that the implementation approach is fundamentally incorrect.

---

# 12. Phase 12 — Repeated Failure

When the same error appears more than once:

1. Stop repeating the current approach.
2. Identify the repeated assumption.
3. Determine why the previous correction failed.
4. Check `knowledge/errors/`.
5. Obtain additional evidence.
6. Change the hypothesis.
7. Apply a targeted correction.
8. Validate again.

A repeated failure is evidence that the current reasoning is insufficient.

---

# 13. iLogic Workflow

For an iLogic task:

1. Identify the active document.
2. Identify the document type.
3. Identify the required Inventor objects.
4. Check relevant iLogic knowledge.
5. Check relevant parameter and unit knowledge.
6. Search `tested/`.
7. Verify unfamiliar API members.
8. Implement.
9. Review.
10. Run in Autodesk Inventor.
11. Capture the exact result.
12. Enter the repair loop when validation fails.
13. Confirm requested behavior.
14. Record reusable verified findings.

Do not mark an iLogic rule `VERIFIED` merely because it was saved.

---

# 14. iLogic Testing Workflow

For iLogic rules requiring iterative Inventor testing:

1. Create a temporary test-case file in `scratch/` containing setup instructions and expected results.
2. Create a test Part or other required Inventor document with the required state.
3. Enable `DebugMode` as specified by `10-coding-standards.md`.
4. Run the rule in Inventor.
5. Capture the output or error.
6. Repair using `15-validation-loop.md`.
7. Repeat until the required test cases pass or the task becomes blocked/unresolved.
8. After verification:

   * set `DebugMode = False`;
   * remove temporary test files and output from `scratch/`;
   * promote to `addins/<FunctionName>/` only when explicitly ready for use.

---

# 15. Add-in Workflow

For a .NET Add-in:

1. Identify the language.
2. Identify the Add-in architecture.
3. Identify the target Inventor version.
4. Check relevant Add-in knowledge.
5. Check API compatibility information.
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

# 16. Existing Code Workflow

When modifying existing code:

1. Read the full relevant implementation.
2. Identify existing behavior.
3. Identify the failure or requested change.
4. Search for related callers/usages.
5. Modify the canonical implementation.
6. Avoid unrelated functionality changes.
7. Validate existing and new behavior where practical.
8. Enter the repair loop if validation fails.

Do not create replacement files merely because the existing implementation needs repair.

---

# 17. Migration Workflow

When updating older Inventor code:

1. Determine the original Inventor version.
2. Determine the programming environment.
3. Determine the framework/runtime version.
4. Determine the Interop version where applicable.
5. Check API compatibility knowledge.
6. Verify each affected API member.
7. Update incompatible code.
8. Build if applicable.
9. Runtime-test in Autodesk Inventor.
10. Enter the repair loop if validation fails.
11. Preserve reusable migration knowledge.

Do not modernize unrelated code during a migration unless required.

---

# 18. Scratch Workflow

Use `scratch/` for temporary experiments.

Typical sequence:

```text
Create experiment
    ↓
Run in target environment
    ↓
Capture result
    ↓
Repair if required
    ↓
Validate
    ↓
Promote verified result or discard
```

Do not treat `scratch/` as production storage.

Do not promote failed experiments to `tested/`.

---

# 19. Knowledge Classification After Validation

After successful validation, classify the resulting information.

| Information                                        | Location                 |
| -------------------------------------------------- | ------------------------ |
| Reusable verified implementation pattern           | `tested/`                |
| General technical fact or API behavior             | `knowledge/`             |
| Verified failed API attempt / confirmed limitation | `knowledge/errors/`      |
| Project-specific documentation                     | project folder           |
| Future idea / enhancement                          | `scratch/` or backlog    |
| Completed user-ready iLogic function               | `addins/<FunctionName>/` |
| Temporary development history                      | discard                  |

Do not leave all discovered information in one large report.

Update an existing knowledge file when the finding extends an existing topic.

Do not create duplicate competing knowledge files.

---

# 20. Final Response

At the end of a development task, report:

```text
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

Never claim a result that has not been established.

---

# 21. Definition of Done

A task is complete only when:

1. The requested behavior is implemented.
2. Relevant API assumptions are verified.
3. Validation has been attempted.
4. Known errors are resolved, explained, or blocked.
5. Final validation status is known.
6. Reusable verified knowledge has been preserved where appropriate.

A solution that merely appears correct is not considered verified.
