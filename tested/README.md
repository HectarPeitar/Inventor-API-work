# Tested Implementations

## Purpose

`tested/` contains verified, reusable Autodesk Inventor implementation patterns.

Content in this directory must be based on successful validation.

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
