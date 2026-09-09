# Validation and Repair Loop

## Purpose

This file defines the mandatory validation and repair behavior for executable Autodesk Inventor code.

Applies to:

* iLogic Rules
* External iLogic
* C# Inventor Add-ins
* VB.NET Inventor Add-ins
* Inventor API automation
* Buildable Inventor projects
* Executable test code

---

# 1. Mandatory Validation Loop

For executable tasks, follow this sequence:

1. Understand the requirement.
2. Identify the execution context.
3. Check relevant project knowledge.
4. Check `tested/`.
5. Implement the smallest reasonable solution.
6. Validate the implementation.
7. If validation succeeds, verify the requested behavior.
8. If validation fails, capture the failure.
9. Classify the failure.
10. Determine the most likely root cause.
11. Check whether the same failure or assumption already exists.
12. Apply a targeted correction.
13. Validate again.

Repeat until one of these conditions is met:

* `VERIFIED`
* `BLOCKED`
* `UNRESOLVED`
* maximum iteration count reached

---

# 2. API and Knowledge Verification

For API evidence and source priority, follow:

```text
.clinerules/00-core.md
```

Do not create a second source hierarchy here.

This file defines **what to do after validation evidence exists**.

---

# 3. Iteration Tracking

Track each implementation attempt explicitly.

Example:

```text
Iteration: 1
Status: FAIL
Failure: <exact error>
Cause: <root cause or hypothesis>
Change: <change made>
```

Do not collapse multiple attempts into one.

Each iteration must produce new information, new evidence, or a changed hypothesis.

Do not repeat an unsuccessful approach without new evidence.

---

# 4. Failure Capture

When validation fails, capture the strongest available evidence.

Record, when available:

* exact error message;
* error category;
* file;
* line number;
* API member;
* object type;
* document type;
* programming environment;
* Inventor version;
* relevant context;
* changes made in the current iteration.

Do not paraphrase the original error when the exact message is available.

---

# 5. Failure Classification

Classify each failure before modifying the code.

Allowed categories:

* `COMPILE_ERROR`
* `RUNTIME_API_ERROR`
* `DOCUMENT_STATE_ERROR`
* `OBJECT_STATE_ERROR`
* `INPUT_ERROR`
* `ENVIRONMENT_ERROR`
* `DEPENDENCY_ERROR`
* `LOGIC_ERROR`
* `UNKNOWN`

Use `UNKNOWN` when evidence is insufficient.

Do not force an unsupported classification.

---

# 6. Root Cause Analysis

Before changing code, determine the most likely root cause using available evidence.

Consider:

1. Exact validation output.
2. Actual object type and document context.
3. Current implementation.
4. Previous iterations.
5. `tested/`.
6. `knowledge/errors/`.
7. Relevant project knowledge.
8. Verified API/source evidence defined by `00-core.md`.

When fixing a bug in shared code, inspect relevant callers and usages.

Prefer correcting a shared root cause over adding repeated workarounds at each call site.

---

# 7. Failure Must Change the Next Attempt

A failed iteration must affect the next hypothesis.

Required pattern:

```text
Iteration N
    ↓
Failure
    ↓
New evidence
    ↓
Revised hypothesis
    ↓
Targeted change
    ↓
Validation
```

Forbidden pattern:

```text
Failure
    ↓
Guess
    ↓
Guess
    ↓
Guess
```

---

# 8. Repeated Failure

When the same or substantially equivalent failure appears twice:

1. Stop cosmetic changes.
2. Compare the affected iterations.
3. Check `knowledge/errors/`.
4. Determine why the previous correction failed.
5. Re-evaluate the root cause.
6. Re-verify the relevant API, object type, or context.
7. Apply a new targeted correction.
8. Validate again.

Do not repeat the same failed approach without new evidence.

---

# 9. No Blind Regeneration

When code fails, do not regenerate the entire implementation unless evidence shows that the implementation approach is fundamentally incorrect.

Prefer:

```text
Existing implementation
    ↓
Identify failing assumption
    ↓
Small correction
    ↓
Retest
```

Do not discard working code without evidence that the approach itself is wrong.

---

# 10. Minimal Repair

Each repair should:

* address the identified cause;
* modify the smallest relevant code region;
* preserve working behavior;
* avoid unrelated changes;
* remain testable.

Do not make unrelated changes in the same repair iteration unless required by the root cause.

---

# 11. Validation Levels

## `GENERATED`

Implementation exists but has not been validated.

## `REVIEWED`

Implementation has been inspected but not executed.

## `BUILT`

Compilation/build succeeded.

## `RUNTIME-TESTED`

Implementation executed successfully enough to provide runtime evidence.

## `VERIFIED`

The requested behavior has been confirmed.

## `BLOCKED`

Validation cannot continue because an external action or unavailable environment is required.

## `UNRESOLVED`

Available evidence does not establish a correct solution within the permitted iterations.

---

# 12. Success Criteria

Do not mark a task `VERIFIED` merely because:

* code compiles;
* no syntax errors remain;
* an API member appears plausible;
* an Add-in loads;
* a rule starts;
* no immediate exception occurs.

`VERIFIED` requires confirmation that the requested behavior works.

---

# 13. External Validation

When validation requires Autodesk Inventor or Visual Studio and the environment is unavailable:

1. Prepare the required files.
2. State exactly what must be executed.
3. Specify the expected behavior.
4. Request the exact output or error.
5. Resume the repair loop using that result.

Prefer:

```text
Run the rule in Autodesk Inventor 2026 and return the complete error message, including the line number if available.
```

Avoid:

```text
Let me know whether it works.
```

---

# 14. Build Validation

For .NET Add-ins:

1. Build the solution.
2. Capture the complete build result.
3. Repair compile errors before runtime testing.
4. Do not perform runtime validation on code that has not successfully built.

A successful build does not imply runtime correctness.

---

# 15. Runtime Validation

For iLogic or Add-ins:

1. Execute in the target Inventor environment.
2. Capture exceptions and error messages.
3. Confirm expected behavior.
4. Check for obvious regressions.
5. Only then mark the result `VERIFIED`.

---

# 16. Error Memory

When a failure produces reusable knowledge, create or update a reusable record.

Use:

```text
# <Short Error Description>

## Error

<Exact error message>

## Context

- Inventor version: <version>
- Environment: <environment>
- Document type: <document type>
- Object/context: <context>

## Root Cause

<Confirmed or best-supported cause>

## Incorrect Assumption

<What was incorrectly assumed>

## Correct Approach

<Verified correction>

## Verification

<How the correction was verified>

## Status

VERIFIED
```

Only create a verified error/solution record after the corrected implementation has been validated.

---

# 17. Knowledge Promotion

After validation, classify reusable information correctly.

| Result type                              | Destination              |
| ---------------------------------------- | ------------------------ |
| Reusable verified implementation pattern | `tested/`                |
| General technical knowledge              | `knowledge/`             |
| Verified negative knowledge              | `knowledge/errors/`      |
| Project-specific documentation           | project documentation    |
| Future idea or enhancement               | `scratch/` or backlog    |
| Completed user-ready iLogic function     | `addins/<FunctionName>/` |
| Temporary debugging information          | discard                  |

Do not promote unverified information.

---

# 18. Repair Limit

Default maximum:

```text
5 iterations
```

Count the initial implementation as iteration 1.

Example:

```text
Iteration 1 → Initial implementation
Iteration 2 → Repair 1
Iteration 3 → Repair 2
Iteration 4 → Repair 3
Iteration 5 → Repair 4
```

After the maximum:

1. Stop automatic repair.
2. Preserve the evidence.
3. Summarize the failed hypotheses.
4. Report `UNRESOLVED` unless the issue is externally blocked.
5. State what additional evidence is required.

Never loop indefinitely.

---

# 19. Environment Failures

Do not modify application code to compensate for an unrelated environment problem.

Examples:

* Inventor is not running;
* Visual Studio is unavailable;
* required reference is not installed;
* test document is missing;
* required dependency is unavailable.

Classify as `ENVIRONMENT_ERROR` or `DEPENDENCY_ERROR` when appropriate.

Report `BLOCKED` when code cannot be meaningfully validated because of the environment.

---

# 20. Final Validation Report

At the end of the task, report:

```text
Status: <status>
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

# 21. Runnable Checks for Non-Trivial Logic

Non-trivial iLogic or Inventor logic should leave a small runnable check behind when practical — the smallest thing that would fail if the logic breaks later.

This is not a replacement for the validation loop.

Trivial one-line operations do not require a standalone check.
