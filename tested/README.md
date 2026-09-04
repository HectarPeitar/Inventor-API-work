# Tested Implementations

## Purpose

`tested/` contains verified, reusable Autodesk Inventor implementation patterns.

Content in this directory must be based on successful validation.

**Important:** `tested/` is a knowledge library, not a storage location for completed functions. Completed production functions belong in `addins/<FunctionName>/`.

---

## What Belongs Here

Use `tested/` for:

* concise reusable implementation patterns;
* verified API usage patterns;
* verified code fragments;
* reusable examples useful for future development.

## What Does NOT Belong Here

Do NOT use `tested/` for:

* completed production functions (use `addins/<FunctionName>/` instead);
* complete user-facing iLogic tools (use `addins/<FunctionName>/` instead);
* every successfully tested function;
* project-specific implementations;
* user manuals;
* release documentation;
* automatic copies of completed source files.

A successful validation does not automatically create a `tested/` entry.

Only create or update a `tested/` entry when the result contains a genuinely reusable implementation pattern.

---

## Requirements

Every tested implementation should identify, when relevant:

* Purpose
* Inventor version
* Programming environment
* Document type
* Relevant object/context
* API members used
* Validation method
* Verification status
* Known limitations

---

## Error-Driven Improvements

When a failed implementation reveals useful information:

1. Capture the original error.
2. Identify the incorrect assumption.
3. Determine the root cause.
4. Implement the correction.
5. Validate the correction.
6. Store the verified result only after successful validation.

Do not store failed attempts as tested implementations.

---

## Reliability

A tested implementation is strong evidence for the context in which it was verified.

It is not automatically valid for:

* another Inventor version;
* another programming environment;
* another document type;
* another object context;
* another API context.

Re-check compatibility before reuse.

---

## Recommended Structure

# <Implementation Name>

## Purpose

<What the implementation does>

## Context

* Inventor version:
* Environment:
* Document type:
* Object/context:

## Implementation

<Verified implementation>

## Validation

<How it was tested>

## Result

VERIFIED

## Notes

<Important limitations or assumptions>
