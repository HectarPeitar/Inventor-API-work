# Core Rules

## Purpose

This workspace is used for Autodesk Inventor automation and development.

Primary use cases:

* iLogic Rules
* External iLogic
* C# .NET Inventor Add-ins
* VB.NET .NET Inventor Add-ins
* Inventor API development
* Inventor UI and Ribbon development
* Inventor events
* Parts
* Assemblies
* Drawings
* Parameters
* Features
* Debugging
* Refactoring

Target platform:

* Autodesk Inventor 2026

---

## Rule Priority

Apply rules in this priority order:

1. User requirements
2. Safety and platform constraints
3. These core rules
4. Task-specific workflow rules
5. Knowledge files
6. Existing project conventions

When rules conflict, follow the higher-priority rule.

Never ignore a higher-priority rule because a lower-priority rule is more convenient.

---

## General Behavior

Act on evidence rather than assumptions.

Do not treat generated code, remembered API names, old examples, or plausible implementations as verified.

Before using an unfamiliar Inventor API member:

1. Identify the object type.
2. Identify the member.
3. Verify that the member exists.
4. Verify its parameters.
5. Verify its return type.
6. Verify the required context.
7. Verify compatibility with Autodesk Inventor 2026.
8. Check `tested/` for an existing verified implementation.
9. Check `knowledge/errors/` to confirm the member has not already been tested and found invalid in the target environment.

If verification is not possible, explicitly mark the assumption as unverified.

---

## Questioning Complex Requests

When a request involves complex implementation, verify whether the stated approach is actually needed.

Ask:
- Does the user actually need X, or does Y cover it?
- Is there a simpler way to achieve the same outcome?

Do not question requirements merely to avoid work. Question them when a simpler, equally correct solution may exist.

---

## Verification Levels

Use these status values consistently:

* `GENERATED` — code exists but has not been validated.
* `REVIEWED` — code has been inspected but not executed.
* `BUILT` — compilation/build succeeded.
* `RUNTIME-TESTED` — code executed in the target environment.
* `VERIFIED` — requested behavior was successfully confirmed.
* `BLOCKED` — validation requires an unavailable external action.
* `UNRESOLVED` — validation failed and the issue remains unresolved.

Never report `VERIFIED` unless the requested behavior has actually been confirmed.

Never invent build or runtime results.

---

## Inventor Version

Assume Autodesk Inventor 2026 unless the task explicitly specifies another version.

When existing code targets another Inventor version:

1. Identify the original version.
2. Check compatibility.
3. Verify API members against the target version.
4. Update the implementation where necessary.
5. Validate the result.

Do not assume that code written for an older Inventor version is directly compatible with Inventor 2026.

---

## Programming Environment

Always determine the execution environment before implementation.

Possible environments include:

* iLogic
* External iLogic
* C# .NET Add-in
* VB.NET .NET Add-in
* VBA
* Apprentice
* External Inventor automation

Do not assume that an API or capability available in one environment is available in another.

Do not introduce a .NET Add-in when the requirement can appropriately be implemented as an iLogic rule.

Do not force iLogic when the requirement requires an Add-in.

---

## Document Context

Before using document-specific API, determine:

* Active document
* Document type
* ComponentDefinition
* Target object
* Assembly context
* Proxy requirements
* Object ownership
* Object state

Do not use Part-specific API without confirming a Part context.

Do not use Assembly-specific API without confirming an Assembly context.

Do not assume that native objects and proxy objects are interchangeable.

---

## Units

Whenever a task involves physical values:

1. Identify the source unit.
2. Identify the expected API unit.
3. Determine whether conversion is required.
4. Use explicit unit handling where appropriate.
5. Avoid hidden unit assumptions.

Never assume that a raw numeric value represents millimeters, inches, degrees, or another unit without evidence.

Use `knowledge/units.md` when relevant.

---

## Existing Code

When modifying existing code:

1. Read the relevant implementation.
2. Identify the actual problem.
3. Preserve working behavior.
4. Make the smallest reasonable change.
5. Avoid unrelated refactoring.

Do not rewrite working code unless the task requires it.

---

## Knowledge Base

Use knowledge files as technical references.

Typical files include:

* `knowledge/APInotes.md`
* `knowledge/api-compatibility.md`
* `knowledge/object-model.md`
* `knowledge/ilogic.md`
* `knowledge/addins.md`
* `knowledge/assemblies.md`
* `knowledge/parameters.md`
* `knowledge/units.md`

Use the most specific relevant source first.

Do not store unverified assumptions as knowledge.

---

## Tested Implementations

`tested/` is a knowledge library of reusable implementation patterns, not a storage location for completed functions.

Use `tested/` for concise reusable patterns, verified API usage patterns, and verified code fragments useful for future development.

Do NOT use `tested/` for completed production functions, complete user-facing iLogic tools, every successfully tested function, project-specific implementations, user manuals, or release documentation.

Before implementing new functionality:

1. Search `tested/` for relevant patterns.
2. Identify the closest verified pattern.
3. Compare Inventor version.
4. Compare programming environment.
5. Compare document context.
6. Compare API context.
7. Reuse the pattern when applicable.

Do not blindly copy a tested pattern when its context differs.

A tested pattern is evidence, not universal proof.

A successful validation does not automatically create a `tested/` entry.

Only create or update a `tested/` entry when the result contains a genuinely reusable implementation pattern.

---

## Completed Functions

When an iLogic function is fully completed, validated, and ready for use, it belongs in `addins/`.

Use this structure:

```
addins/
└── <FunctionName>/
    ├── <FunctionName>.vb
    └── README.md
```

The folder name must match the function name.

A function may only be promoted to `addins/` when it is explicitly considered ready for use.

Do not promote unfinished or unresolved functionality to `addins/`.

For detailed promotion rules, see `.clinerules/10-coding-standards.md` section 21.

---

## Validation vs Promotion

`VALIDATED` means the implementation has been tested successfully.

`PROMOTED` means the implementation has been intentionally placed in `addins/` as a completed reusable function.

A function can be `VALIDATED` without being `PROMOTED`.

Never assume promotion is implied by validation.

Do NOT automatically promote every successfully completed task to `addins/`.

---

## Error Handling

Treat compile errors, runtime errors, API errors, and incorrect behavior as feedback.

When validation fails:

1. Capture the exact failure.
2. Classify the failure.
3. Identify the most likely root cause.
4. Check previous attempts.
5. Check `tested/`.
6. Check relevant knowledge.
7. Apply the smallest reasonable correction.
8. Validate again.

Follow `.clinerules/15-validation-loop.md`.

---

## Error Memory

Do not discard reusable information discovered during debugging.

When a failure reveals reusable knowledge, preserve:

* Error
* Context
* Root cause
* Incorrect assumption
* Correct implementation
* Inventor version
* Programming environment
* Document context
* Verification status

Promote verified reusable information to the appropriate location:

* `tested/` for verified implementation patterns
* `knowledge/` for general technical facts
* `knowledge/errors/` for verified negative knowledge (API members tested and found invalid, incorrect assumptions, confirmed limitations)

Do not store failed or unverified implementations as tested solutions.

---

## External Tools and Environments

Use:

* VS Code / Cline for planning, editing, repository navigation, documentation, and knowledge management.
* Visual Studio for .NET Add-in builds and debugging.
* Autodesk Inventor for runtime validation.

Do not claim that an external operation succeeded unless its result is available.

If an external validation step cannot be executed, report `BLOCKED`.

---

## Autonomous Repair

For executable code, do not stop at the first generated implementation.

The required sequence is:

1. Implement
2. Validate
3. Capture failure
4. Analyze failure
5. Check previous knowledge
6. Patch
7. Validate again

Repeat until the implementation is verified, blocked, or unresolved.

Do not repeat an unsuccessful approach without new evidence.

---

## Repair Iteration Limit

Default maximum repair iterations:

`5`

The initial implementation is iteration `1`.

When the maximum is reached:

1. Stop speculative changes.
2. Preserve relevant evidence.
3. Summarize the failed hypotheses.
4. Report the current status as `UNRESOLVED`.
5. State what external validation or information is required.

Never loop indefinitely.

---

## Claims About Results

Never claim that code:

* compiles;
* builds;
* loads;
* executes;
* passes runtime validation;
* fixes the original issue;
* is compatible with Inventor 2026;

unless the relevant result has actually been established.

Use explicit status values.

---

## Definition of Done

A task is complete only when all applicable conditions are satisfied:

1. The requested functionality is implemented.
2. Relevant API assumptions are verified.
3. Validation has been attempted.
4. Failures have been repaired, explained, or blocked.
5. The final status is explicitly known.
6. Reusable verified knowledge has been preserved where appropriate.

A solution that merely looks correct is not considered verified.
