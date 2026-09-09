# Core Rules — Autodesk Inventor Workspace

## Purpose

This workspace is used for Autodesk Inventor automation and development.

Primary use cases include:

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

Target Autodesk Inventor version:

**Inventor 2026**

---

# 1. Rule Precedence

When rules conflict, apply them in this order:

1. System, safety, platform, and tool constraints.
2. Explicit user requirements.
3. This project's `.clinerules/`.
4. Global Cline rules.
5. Local knowledge and reference material.
6. General model knowledge.

More specific project rules override general global behavior when they conflict.

Reference material is evidence, not an instruction to violate project rules.

Never ignore a higher-priority instruction because a lower-priority rule is more convenient.

---

# 2. Project Context

Unless explicitly stated otherwise, assume:

* Autodesk Inventor 2026
* Windows
* the execution environment must still be identified before implementation
* the existing project architecture should be preserved
* the existing workspace knowledge structure should be used

Do not assume that code targeting an older Inventor version is directly compatible with Inventor 2026.

When another Inventor version is involved:

1. Identify the original version.
2. Check compatibility.
3. Verify affected API members against the target version.
4. Update incompatible implementation where necessary.
5. Validate the result.

---

# 3. Execution Environment

Always identify the actual execution environment before implementing an Inventor task.

Possible environments include:

* iLogic
* External iLogic
* C# .NET Add-in
* VB.NET .NET Add-in
* VBA
* Apprentice
* External Inventor automation
* other explicitly identified Inventor automation environments

Do not assume that an API, assembly, reference, capability, or behavior available in one environment is available in another.

Do not introduce a .NET Add-in when the requirement can appropriately be implemented as iLogic.

Do not force iLogic when the requirement requires an Add-in or another execution environment.

---

# 4. Inventor API Evidence

For Inventor API questions, use evidence rather than assumptions.

Do not treat the following as verified:

* remembered API names
* generated code
* old examples
* plausible member names
* examples from another Inventor version
* examples from another programming environment

Before using an unfamiliar Inventor API member, establish:

1. The object type.
2. The member name.
3. That the member exists.
4. Its parameters.
5. Its return type.
6. Required object/document context.
7. Compatibility with Autodesk Inventor 2026.
8. Whether a verified implementation already exists in `tested/`.
9. Whether `knowledge/errors/` contains a known negative result for the same or equivalent assumption.

If verification is not possible, explicitly identify the assumption as unverified.

---

# 5. API Source Hierarchy

For Inventor API verification, prefer sources in this order:

1. Local Inventor 2026 SDK and API/source material.
2. Local official Autodesk SDK samples.
3. Curated local Inventor knowledge.
4. Verified implementations in `tested/`.
5. Negative knowledge in `knowledge/errors/`.
6. Autodesk web documentation when local evidence is insufficient.
7. General model knowledge.

Use the central Knowledge Map to navigate local sources:

```text
knowledge/inventor/KNOWLEDGE-MAP.md
```

Do not scan the entire SDK when a narrower source path is available.

Use the most specific relevant source first.

---

# 6. Knowledge Map and Narrow Search

For Inventor API questions, start from:

```text
knowledge/inventor/KNOWLEDGE-MAP.md
```

Follow the relevant topic path rather than loading unrelated knowledge.

Examples:

### Parameter task

```text
KNOWLEDGE-MAP
→ parameters
→ units when relevant
→ relevant SDK sample
→ tested pattern
→ implementation
```

### Property task

```text
KNOWLEDGE-MAP
→ properties
→ relevant SDK/property sample
→ iLogic guidance
→ implementation
```

### Assembly task

```text
KNOWLEDGE-MAP
→ assemblies
→ AssemblyTree sample
→ object model
→ implementation
```

For source mapping and sample discovery, use:

```text
knowledge/inventor/2026/API-SOURCE-MAP.md
knowledge/inventor/2026/SAMPLE-INDEX.md
```

Do not load unrelated knowledge merely because it exists.

---

# 7. Local SDK First

The complete Autodesk Inventor 2026 SDK is stored at:

```text
knowledge/inventor/2026/sdk/
```

Prefer these local SDK materials before using general web search when the required information is available locally.

Do not use web search merely because it is available.

Use Autodesk web documentation only when the local evidence is insufficient or when external verification is otherwise necessary.

---

# 8. Document Context

Before using document-specific Inventor API, establish the relevant context.

Determine, as applicable:

* active document
* document type
* ComponentDefinition
* target object
* assembly context
* proxy requirements
* object ownership
* object state

Do not use Part-specific API without confirming a Part context.

Do not use Assembly-specific API without confirming an Assembly context.

Do not assume native objects and proxy objects are interchangeable.

---

# 9. Units

Whenever a task involves physical values:

1. Identify the source unit.
2. Identify the expected API unit.
3. Determine whether conversion is required.
4. Use explicit unit handling where appropriate.
5. Avoid hidden unit assumptions.

Never assume that a raw numeric value represents millimeters, inches, degrees, or another unit without evidence.

Use:

```text
knowledge/units.md
```

when relevant.

---

# 10. Existing Code and Architecture

When modifying existing code:

1. Read the relevant implementation.
2. Identify its existing behavior.
3. Identify the requested change or actual defect.
4. Preserve working behavior.
5. Modify the canonical implementation rather than creating a duplicate.
6. Preserve existing file names and locations unless there is a clear reason to change them.
7. Avoid unrelated architectural changes.

The global development rules govern general simplicity, scope control, and minimal changes.

This project rule governs how those principles apply to this workspace.

---

# 11. Questioning Complex Requests

Question an approach only when there is evidence that a simpler, equally correct solution may satisfy the requirement.

Consider:

* Does the user actually need the requested mechanism?
* Does an existing project mechanism already provide the required result?
* Can native Inventor/iLogic functionality solve the requirement?
* Is there an existing verified project pattern that should be reused?

Do not challenge a requirement merely to avoid work.

---

# 12. Knowledge Base

Use the workspace knowledge base as technical reference material.

Typical sources include:

```text
knowledge/APInotes.md
knowledge/api-compatibility.md
knowledge/object-model.md
knowledge/ilogic.md
knowledge/addins.md
knowledge/assemblies.md
knowledge/parameters.md
knowledge/units.md
```

Use the most specific relevant source first.

Do not store unverified assumptions as knowledge.

Technical API knowledge belongs in `knowledge/`, not primarily in `.clinerules/`.

---

# 13. Knowledge Source Handling

The original authoritative source must remain identifiable.

For derived or curated technical sources:

* preserve the original source;
* clearly treat derived material as an interpretation or retrieval aid;
* do not silently replace the original source with a derived representation;
* consult the original source when exact verification, visual relationships, or potentially lost information matter.

---

# 14. PDF and Document Sources

The local SDK and reference material may contain PDF, DOC, and DOCX files.

Do not automatically convert every document to Markdown.

For each source:

1. Determine what information it contains.
2. Determine whether the information is useful for future development.
3. Determine whether the original is already sufficiently searchable.
4. Determine whether a derived representation materially improves retrieval.
5. Preserve the original as authoritative.

Source types:

| Type             | Description                        |
| ---------------- | ---------------------------------- |
| `RAW SOURCE`     | Original Autodesk document         |
| `CURATED SOURCE` | AI-friendly derived representation |

A curated source must never silently replace a raw source.

Normal retrieval should use the best available searchable representation, but return to the original when exact verification or missing context requires it.

---

# 15. Tested Implementations

`tested/` is a reusable knowledge library.

It is not a general archive of completed work.

Use `tested/` only for verified, reusable implementation patterns.

Before implementing unfamiliar or reusable functionality:

1. Search `tested/`.
2. Identify the closest relevant pattern.
3. Compare Inventor version.
4. Compare execution environment.
5. Compare document context.
6. Compare API context.
7. Reuse the pattern only when the context matches sufficiently.

A tested pattern is evidence, not universal proof.

Do not assume that a successful test automatically creates a `tested/` entry.

Detailed rules for `tested/` storage are defined in:

```text
.clinerules/10-coding-standards.md
```

---

# 16. Error Knowledge

Reusable negative knowledge belongs in:

```text
knowledge/errors/
```

Examples include:

* API members confirmed invalid
* incorrect API assumptions
* version-specific limitations
* environment-specific limitations
* verified failed approaches

Do not store failed or unverified attempts as established knowledge.

Detailed error-memory rules are defined in:

```text
.clinerules/15-validation-loop.md
```

---

# 17. Completed Functions

Completed user-ready iLogic functions belong in:

```text
addins/<FunctionName>/
```

with:

```text
<FunctionName>.vb
README.md
```

Only explicitly ready-for-use functions should be promoted there.

Validation does not automatically imply promotion.

Detailed promotion and storage rules are defined in:

```text
.clinerules/10-coding-standards.md
```

---

# 18. Status Values

Use these status values consistently:

| Status           | Meaning                                                            |
| ---------------- | ------------------------------------------------------------------ |
| `GENERATED`      | Code exists but has not been validated.                            |
| `REVIEWED`       | Code has been inspected but not executed.                          |
| `BUILT`          | Compilation/build succeeded.                                       |
| `RUNTIME-TESTED` | Code executed successfully enough to produce runtime evidence.     |
| `VERIFIED`       | Requested behavior was confirmed.                                  |
| `BLOCKED`        | Validation requires an unavailable external action or environment. |
| `UNRESOLVED`     | Available evidence does not establish a correct solution.          |

Never report `VERIFIED` unless the requested behavior was actually confirmed.

Never invent build, runtime, or validation results.

---

# 19. Validation and Repair

Executable Inventor work must follow:

```text
.clinerules/15-validation-loop.md
```

The development sequence is defined in:

```text
.clinerules/20-workflow.md
```

Do not duplicate those complete procedures here.

---

# 20. External Environments

Use the appropriate application for the operation:

| Operation                                               | Preferred environment |
| ------------------------------------------------------- | --------------------- |
| Planning, editing, repository navigation, documentation | VS Code / Cline       |
| .NET Add-in build and debugging                         | Visual Studio         |
| Inventor runtime validation                             | Autodesk Inventor     |

Do not claim that an external operation succeeded unless the result is available.

When external validation is required but unavailable, use:

`BLOCKED`

rather than inventing a result.

---

# 21. General Project Principle

This workspace follows:

```text
Evidence
    ↓
Correct context
    ↓
Verified implementation
    ↓
Validation
    ↓
Reusable knowledge
```

Project-specific technical knowledge belongs in `knowledge/`.

Reusable verified implementation patterns belong in `tested/`.

Completed user-ready functions belong in `addins/`.

Temporary experiments belong in `scratch/`.

Behavioral instructions belong in `.clinerules/`.
