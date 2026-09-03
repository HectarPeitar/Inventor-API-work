# Core Rules — Inventor AI Assistant

## Purpose

This workspace is used for Autodesk Inventor automation and development.

Primary use cases:

- iLogic Rules
- C# .NET Add-ins
- VB.NET .NET Add-ins
- Inventor API development
- UI and Ribbon development
- Events
- Parts
- Assemblies
- Drawings
- Parameters
- Features
- Debugging
- Refactoring

Primary target:

- Autodesk Inventor 2026

---

## Development Environment

This workspace is primarily operated through:

- VS Code
- Cline

VS Code/Cline is the primary environment for:

- AI-assisted development;
- repository navigation;
- editing source code;
- editing Markdown knowledge;
- managing project files;
- reviewing examples;
- maintaining tested implementations;
- managing templates;
- coordinating development tasks.

Visual Studio is the primary environment for:

- building .NET Inventor Add-ins;
- debugging C# and VB.NET Add-ins;
- managing .NET project references;
- working with Autodesk Inventor Interop;
- attaching the debugger to Inventor;
- runtime debugging and validation.

Autodesk Inventor is the runtime and primary test environment for:

- iLogic rules;
- Inventor Add-ins;
- API behavior;
- CAD document operations;
- UI behavior;
- events;
- model changes.

Do not assume that VS Code replaces Visual Studio for Inventor .NET Add-in build and debugging tasks.

---

## 1. Source Hierarchy

Use technical information according to this priority:

1. Current official Autodesk Inventor 2026 documentation
2. Local Inventor 2026 SDK / Interop assemblies
3. Locally tested code in `tested/`
4. Local examples in `examples/`
5. Current Autodesk / DevTech examples
6. Older Autodesk documentation
7. Community / GitHub projects
8. General model knowledge

When sources conflict, prefer the higher-priority source.

---

## 2. Never Invent API Members

Never invent or guess:

- classes
- interfaces
- methods
- properties
- events
- enums
- constructors
- namespaces
- parameters
- return types

A plausible API name is not evidence that the API exists.

When an API member is uncertain, verify it before using it.

---

## 3. Determine the Programming Context

Before writing code, determine which environment is being used:

- iLogic
- External iLogic
- C# Add-in
- VB.NET Add-in
- VBA
- Apprentice
- External automation

Do not assume that functionality available in one environment is automatically available in another.

---

## 4. Determine Document Context

Before using document-specific API:

1. determine the active document;
2. determine its document type;
3. determine the relevant ComponentDefinition;
4. determine whether the operation occurs in an Assembly context;
5. determine whether a proxy object is required.

Never use Part-specific API without establishing that the target is a Part.

Never use Assembly-specific API without establishing that the target is an Assembly.

---

## 5. Use the Knowledge Base

The `knowledge/` directory contains technical reference material.

Use the most specific relevant file.

Examples:

- API concepts → `knowledge/APInotes.md`
- API compatibility → `knowledge/api-compatibility.md`
- Object relationships → `knowledge/object-model.md`
- iLogic → `knowledge/ilogic.md`
- Add-ins → `knowledge/addins.md`
- Assemblies → `knowledge/assemblies.md`
- Parameters → `knowledge/parameters.md`
- Units → `knowledge/units.md`

Do not duplicate large amounts of knowledge into `.clinerules`.

Rules describe behavior.

Knowledge files describe technical facts.

---

## 6. Use Tested Code

Before creating new functionality, check `tested/` for similar working code.

Tested code has higher confidence than untested examples.

When reusing tested code:

- preserve known working behavior;
- understand its context;
- verify its Inventor version;
- verify its programming environment;
- adapt only what is necessary.

---

## 7. Units

Whenever physical values are involved:

1. identify the source unit;
2. identify the expected API unit;
3. check whether conversion is required;
4. use appropriate Inventor unit handling;
5. avoid hidden unit assumptions.

Never assume that a raw numeric value means millimeters, degrees, inches, or another unit.

See `knowledge/units.md`.

---

## 8. Existing Code

When modifying existing code:

1. understand the existing implementation;
2. identify the actual problem;
3. preserve working behavior;
4. make the smallest reasonable change;
5. avoid unnecessary rewrites.

Only refactor larger sections when there is a clear benefit.

---

## 9. Version Compatibility

The default target is Autodesk Inventor 2026.

Check `knowledge/api-compatibility.md` when:

- migrating older code;
- using old Autodesk examples;
- using GitHub projects;
- changing Inventor versions;
- troubleshooting Interop;
- troubleshooting .NET;
- working with old Add-in projects.

Do not assume that code written for an older Inventor version is directly compatible with Inventor 2026.

---

## 10. Uncertainty

When something cannot be verified:

- state the uncertainty;
- do not fabricate an answer;
- identify what needs verification;
- distinguish documented behavior from assumptions.

Prefer an explicit uncertainty over confidently incorrect API code.

---

## 11. Changes to Knowledge

When new information or code is discovered, classify it before storing it.

- AI behavior or workflow rule → `.clinerules/`
- General technical knowledge → `knowledge/`
- Tested implementation → `tested/`
- Reusable example → `examples/`
- Active Add-in project → `addins/`
- CAD test/sandbox file → `cadfiles/`
- External source material → `reference/`
- New project starting point → `templates/`

Do not duplicate the same information across multiple directories unless there is a clear reason.

---

## 12. General Principle

Use this priority:

Correctness
>
Verified API usage
>
Maintainability
>
Performance
>
Convenience

When in doubt, verify before generating.
