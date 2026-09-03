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

## Mandatory Loop

For executable tasks, follow this sequence:

1. Understand the requirement.
2. Identify the execution context.
3. Check relevant knowledge.
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

Repeat steps 7-13 until one of these conditions is met:

* `VERIFIED`
* `BLOCKED`
* `UNRESOLVED`
* Maximum iteration count reached

---

## Iteration Tracking

Track every implementation attempt explicitly.

Example:

```
Iteration: 1
Status: FAIL
Failure: <exact error>
Cause: <root cause or hypothesis>
Change: <change made>
```

Do not collapse multiple attempts into one.

Each iteration must produce new information or new evidence.

---

## Failure Capture

When validation fails, capture the strongest available evidence.

Record:

* Exact error message
* Error category
* File
* Line number, when available
* API member, when applicable
* Object type, when applicable
* Document type
* Programming environment
* Inventor version
* Relevant context
* Changes made in the current iteration

Do not replace or paraphrase the original error when the exact message is available.

---

## Failure Classification

Classify each failure before changing code.

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

Use `UNKNOWN` when the evidence is insufficient.

Do not force a failure into an incorrect category.

---

## Root Cause Analysis

Before changing code, determine the most likely root cause.

Use evidence in this order:

1. Exact validation output
2. Actual object type and document context
3. Current implementation
4. Previous iterations
5. `tested/`
6. `knowledge/errors/` — check before repeating an API assumption that previously failed
7. Relevant `knowledge/`
8. Official Autodesk documentation
9. Local SDK or Interop information
10. Other reliable sources

Do not replace an API member solely because another name appears plausible.

---

## Failure Must Change the Next Attempt

A failed iteration must affect the next hypothesis.

Required pattern:

```
Iteration N
    ->
Failure
    ->
New evidence
    ->
Revised hypothesis
    ->
Targeted change
    ->
Validation
```

Forbidden pattern:

```
Failure
    ->
Guess
    ->
Guess
    ->
Guess
```

---

## Repeated Failure

When the same or substantially equivalent failure appears twice:

1. Stop cosmetic changes.
2. Compare the affected iterations.
3. Check `knowledge/errors/` — confirm the failed API member or assumption is not already recorded as invalid for the current environment.
4. Determine why the previous correction did not resolve the failure.
5. Re-evaluate the root cause.
6. Re-verify the relevant API, object type, or context.
7. Apply a new targeted correction.
8. Validate again.

Do not repeat the same failed approach without checking `knowledge/errors/` first.

---

## No Blind Regeneration

When code fails, do not regenerate the entire implementation unless the evidence shows that the implementation approach is fundamentally incorrect.

Prefer:

```
Existing implementation
    ->
Identify failing assumption
    ->
Small correction
    ->
Retest
```

Do not discard working code without evidence that the architecture is wrong.

---

## Minimal Repair Principle

Each repair should:

* address the identified cause;
* modify the smallest relevant code region;
* preserve working behavior;
* avoid unrelated changes;
* be testable.

Do not make unrelated changes in the same repair iteration unless required by the root cause.

---

## Validation Levels

### GENERATED

Implementation exists but has not been validated.

### REVIEWED

Implementation has been inspected but not executed.

### BUILT

Compilation/build succeeded.

### RUNTIME-TESTED

Implementation executed successfully enough to obtain runtime evidence.

### VERIFIED

The requested behavior has been confirmed.

### BLOCKED

Validation cannot continue because an external action or unavailable environment is required.

### UNRESOLVED

The available evidence does not establish a correct solution within the permitted iterations.

---

## Success Criteria

Do not mark a task `VERIFIED` merely because:

* code compiles;
* no syntax errors remain;
* an API member appears plausible;
* the Add-in loads;
* the rule starts;
* no immediate exception occurs.

`VERIFIED` requires confirmation that the requested behavior works.

---

## External Validation

When validation requires Autodesk Inventor or Visual Studio and the environment is not directly available:

1. Prepare the required files.
2. State exactly what must be executed.
3. Specify the expected behavior.
4. Request the exact output or error.
5. Resume the repair loop using that result.

Prefer precise requests such as:

```
Run the rule in Autodesk Inventor 2026 and return the complete error message, including the line number if available.
```

Avoid vague requests such as:

```
Let me know whether it works.
```

---

## Build Validation

For .NET Add-ins:

1. Build the solution.
2. Capture the complete build result.
3. Repair compile errors before runtime testing.
4. Do not perform runtime validation on code that has not successfully built.

A successful build does not imply runtime correctness.

---

## Runtime Validation

For iLogic or Add-ins:

1. Execute in the target Inventor environment.
2. Capture exceptions and error messages.
3. Confirm the expected behavior.
4. Check for obvious regressions.
5. Only then mark the result `VERIFIED`.

---

## Error Memory

When a failure produces reusable knowledge, create or update a reusable record.

Use this structure:

```
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

## Knowledge Promotion

A successful test does not automatically mean that the entire development result belongs in `tested/`.

After validation, classify the result into the correct location:

| Result type | Destination |
|---|---|
| Reusable verified implementation | `tested/` |
| General technical knowledge | `knowledge/` |
| Verified negative knowledge (invalid API member, incorrect assumption, confirmed limitation) | `knowledge/errors/` |
| Project-specific documentation | project documentation |
| Future idea or enhancement proposal | backlog or `scratch/` |
| Temporary debugging information | discard |

Do not promote unverified information.

---

## Repair Limit

Default maximum:

`5 iterations`

Count the initial implementation as iteration `1`.

Example:

```
Iteration 1 -> Initial implementation
Iteration 2 -> Repair 1
Iteration 3 -> Repair 2
Iteration 4 -> Repair 3
Iteration 5 -> Repair 4
```

After the maximum:

1. Stop automatic repair.
2. Preserve the evidence.
3. Summarize the failed hypotheses.
4. Report `UNRESOLVED` unless the problem is externally blocked.
5. State what additional evidence is required.

---

## Environment Failures

Do not modify application code to compensate for an unrelated environment problem.

Examples:

* Inventor is not running.
* Visual Studio is unavailable.
* A required reference is not installed.
* A test document is missing.
* A required dependency is unavailable.

Classify the issue as `ENVIRONMENT_ERROR` or `DEPENDENCY_ERROR` when appropriate.

Report `BLOCKED` when code cannot be meaningfully validated because of the environment.

---

## Final Validation Report

At the end of the task, report:

```
Status: <status>
Iterations: <number>
Environment: <environment>
Inventor Version: <version>
Validation: <result>
Remaining Issues: <none or description>
```

Do not omit unresolved issues.

---

## Core Principle

A failure is feedback.

Feedback must change the next hypothesis.

The next hypothesis must produce a targeted change.

The change must be validated.

Verified discoveries must be preserved when reusable.

Therefore:

```
FAIL
    ->
CAPTURE
    ->
CLASSIFY
    ->
ANALYZE
    ->
CHECK KNOWLEDGE
    ->
PATCH
    ->
RETEST
    ->
PASS or REPEAT
```

Never use:

```
FAIL
    ->
BLIND REGENERATE
    ->
FAIL
    ->
BLIND REGENERATE
```
