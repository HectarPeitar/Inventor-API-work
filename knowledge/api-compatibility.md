# Autodesk Inventor API Compatibility

## Purpose

This file contains version and technology compatibility information relevant to Autodesk Inventor automation.

Primary target:

- Autodesk Inventor 2026

Use this file when:

- migrating old Inventor code;
- using old Autodesk examples;
- using GitHub projects;
- changing Inventor versions;
- troubleshooting Interop problems;
- troubleshooting .NET/Add-in problems.

---

## 1. Version Strategy

The default target for this workspace is:

Autodesk Inventor 2026

New code should target Inventor 2026 unless the user explicitly requests another version.

---

## 2. High-Level Version Overview

| Inventor version | Important consideration |
|---|---|
| Inventor 2014 | Main era of the included legacy ADN training |
| Inventor 2024 and earlier | Older .NET Framework Add-in environment |
| Inventor 2025 | Major transition to .NET 8 for Add-ins |
| Inventor 2026 | Primary target for this workspace |

This table is a high-level guide.

Always verify exact version requirements in official Autodesk documentation.

---

## 3. .NET

### Inventor 2024 and earlier

Older Inventor Add-in examples may target .NET Framework.

Do not assume that these project settings are suitable for Inventor 2026.

### Inventor 2025+

Modern Inventor Add-ins use .NET 8.

For Inventor 2026:

- Target Framework: .NET 8
- Use current Visual Studio 2022 tooling
- Prefer current Autodesk Add-in templates

Do not start a new Inventor 2026 Add-in from an old .NET Framework template unless there is a specific compatibility reason.

---

## 4. Interop Assemblies

Use the Interop assemblies corresponding to the target Inventor version.

For Inventor 2026:

- use Inventor 2026 Interop assemblies;
- avoid mixing Interop versions;
- verify references against the local installation;
- investigate duplicate or copied Interop DLLs when unexpected errors occur.

Potential installation location:

C:\Program Files\Autodesk\Inventor 2026\Bin\Public Assemblies\

Do not treat this path as universal.

---

## 5. Interop Version Mismatch

A project can fail even when the source code appears correct if the wrong Inventor Interop assembly is referenced.

Symptoms may include:

- compile errors;
- runtime errors;
- missing members;
- assembly loading problems;
- iLogic external assembly failures.

When this happens, check:

1. Inventor version;
2. referenced Interop DLL;
3. Interop assembly version;
4. project references;
5. copied DLLs;
6. output directory;
7. external dependencies.

---

## 6. Legacy Autodesk Training

The local ADN-DevTech training material is primarily based on older Inventor versions, approximately Inventor 2014.

The training is useful for:

- concepts;
- object model;
- API patterns;
- architecture;
- examples.

The training is not authoritative for Inventor 2026 API details.

When training material conflicts with Inventor 2026 documentation:

Inventor 2026 documentation wins.

---

## 7. Legacy Add-in Projects

Older Add-in projects may contain:

- .NET Framework targets;
- old Visual Studio project structures;
- old templates;
- old deployment methods;
- old Interop references.

Do not modernize such projects by changing only the Target Framework.

Review the complete project:

- project file;
- references;
- dependencies;
- AddInServer;
- manifest;
- deployment;
- UI;
- events.

---

## 8. iLogic Compatibility

Old iLogic code may still be conceptually valid.

However, verify:

- iLogic-specific objects;
- API members;
- Event Triggers;
- Forms;
- external assemblies;
- .NET dependencies;
- Inventor version.

Treat old iLogic code as:

Conceptually useful
+
API details require verification.

---

## 9. API Member Compatibility

An API member from an older version may:

- still exist;
- have changed;
- be deprecated;
- have changed behavior;
- have changed limitations;
- be unavailable in a specific context;
- have been replaced.

Never assume compatibility solely because the object model looks familiar.

---

## 10. Object Model Stability

The general Inventor object model has remained relatively stable.

Long-lived concepts include:

- Application
- Document
- ComponentDefinition
- Parameters
- Features
- Occurrences

These concepts can generally be used as conceptual knowledge.

However:

Object model stability does not guarantee API member or signature stability.

Always verify exact members for Inventor 2026.

---

## 11. Units Compatibility

When migrating old code, verify:

- database/API units;
- display units;
- expression units;
- UnitsOfMeasure;
- parameter expressions.

Never assume a numeric constant from an old example represents the same physical value without checking its context.

---

## 12. Assembly Compatibility

When migrating Assembly code, specifically check:

- ComponentOccurrence;
- ComponentDefinition;
- referenced documents;
- proxies;
- constraints;
- joints;
- assembly-specific APIs.

Part code cannot automatically be treated as Assembly code.

---

## 13. Event Compatibility

When migrating event-based Add-ins, check:

- event interfaces;
- event signatures;
- registration;
- unregistration;
- object lifetime;
- shutdown;
- cleanup.

Do not blindly copy event code from old Add-ins.

---

## 14. UI Compatibility

Older Ribbon/UI examples may depend on:

- older command APIs;
- old project templates;
- old Add-in lifecycle;
- old deployment assumptions.

Verify UI code against the current Inventor version.

---

## 15. GitHub and Community Projects

When using community code:

1. identify the Inventor version;
2. identify the .NET version;
3. inspect Interop references;
4. inspect dependencies;
5. inspect the Add-in manifest;
6. inspect project configuration;
7. check license;
8. test against Inventor 2026.

Community code is reference material, not authoritative API documentation.

---

## 16. Compatibility Decision Process

When old code is encountered:

Old code
-> determine Inventor version
-> determine programming environment
-> determine project type
-> determine .NET version
-> determine Interop version
-> verify API members
-> determine Inventor 2026 equivalent
-> test

Do not consider migrated code production-ready until it has been tested.

---

## 17. Compatibility Status

Use these labels when documenting compatibility:

### VERIFIED

Tested successfully against Inventor 2026.

### DOCUMENTED

Confirmed by current official Autodesk documentation.

### LIKELY

Probably compatible but not locally tested.

### LEGACY

Originates from an older Inventor version.

### UNKNOWN

Not enough information to determine compatibility.

### BROKEN

Known to fail or be incompatible.

---

## 18. Known Compatibility Issues

Add discovered issues using this format:

## YYYY-MM-DD - Short title

Inventor:
Context:
Problem:
Cause:
Solution:
Status:
Source:

Example:

## YYYY-MM-DD - Interop version mismatch

Inventor:
2026

Context:
iLogic / external .NET assembly

Problem:
An external assembly may fail when it uses an incompatible Inventor Interop assembly.

Cause:
Mismatch between the Interop assembly used by the external assembly and the Inventor installation.

Solution:
Use the Interop assembly corresponding to the target Inventor version.

Status:
Needs local verification

Source:
Autodesk documentation/release notes and local testing

---

## 19. Related Knowledge

- APInotes.md
- object-model.md
- ilogic.md
- addins.md
