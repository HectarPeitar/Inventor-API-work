# Autodesk Inventor .NET Add-ins

## Purpose

This file contains knowledge about Autodesk Inventor .NET Add-in development.

Primary target:

- Autodesk Inventor 2026

Primary languages:

- C#
- VB.NET

---

## 1. Runtime

Modern Inventor Add-ins for Inventor 2025 and newer use:

- .NET 8

For this workspace:

- Inventor 2026
- .NET 8

Do not use an old .NET Framework project as the default starting point for a new Inventor 2026 Add-in.

---

## 2. Visual Studio

Use current Visual Studio 2022 tooling supported by the target Inventor release.

Prefer current Autodesk Inventor Add-in templates.

Verify:

- Visual Studio version;
- .NET SDK;
- target framework;
- Inventor SDK;
- Interop references;
- project configuration.

---

## 3. Add-in Architecture

A typical Inventor Add-in contains:

- Add-in server;
- Inventor Application reference;
- command definitions;
- UI controls;
- event handlers;
- cleanup/deactivation logic;
- Add-in manifest;
- dependencies.

The exact Autodesk template structure should be used as the authoritative starting point.

---

## 4. ApplicationAddInServer

Inventor .NET Add-ins use the Autodesk Add-in server architecture.

The Add-in server is responsible for lifecycle management.

Important lifecycle concepts:

- activation;
- initialization;
- Inventor Application reference;
- command registration;
- event registration;
- deactivation;
- cleanup.

Do not assume exact method signatures from memory.

Verify them against the Inventor 2026 API/template.

---

## 5. Inventor Application Reference

The Add-in should maintain access to the Inventor Application object as required by its architecture.

Avoid keeping unnecessary long-lived Inventor API references.

Consider object lifetime and cleanup.

---

## 6. Ribbon and UI

Typical conceptual structure:

Application
-> UserInterfaceManager
-> Ribbon
-> RibbonTab
-> RibbonPanel
-> Control

Commands generally follow:

CommandDefinition
-> Control
-> RibbonPanel

Use the current Inventor API for exact classes and methods.

---

## 7. Command Definitions

Commands should have a clear lifecycle.

When creating commands:

- use unique internal names;
- provide user-facing names;
- register once;
- avoid duplicate controls;
- remove or clean up appropriately during Add-in deactivation.

---

## 8. Events

Add-ins commonly use Inventor events.

Examples include:

- Application events;
- document events;
- command events;
- user input events;
- UI events.

When subscribing:

- store references where required;
- prevent duplicate registration;
- unsubscribe during shutdown/deactivation;
- avoid callbacks into disposed state.

---

## 9. UI Thread and Long Operations

Long-running operations should not unnecessarily block the UI.

For complex operations:

- consider user feedback;
- minimize repeated API calls;
- avoid unnecessary UI refreshes;
- consider cancellation where appropriate.

Inventor API threading restrictions must be respected.

Do not assume Inventor API objects are freely usable from arbitrary background threads.

---

## 10. Interop

Use the Interop assembly matching the target Inventor version.

For Inventor 2026:

- Inventor 2026 Interop;
- .NET 8;
- local SDK/template.

Do not copy Interop DLLs from another Inventor installation without verifying compatibility.

See `api-compatibility.md`.

---

## 11. Add-in Manifest

The Add-in deployment normally includes an Autodesk Add-in manifest.

The manifest must correctly identify the Add-in and its assembly.

When an Add-in does not load, inspect:

- manifest;
- assembly path;
- assembly dependencies;
- target framework;
- Inventor version;
- installation location;
- load behavior.

---

## 12. Deployment

An Add-in deployment may include:

- compiled assembly;
- Add-in manifest;
- dependencies;
- supporting files;
- installer configuration.

A successful build does not guarantee successful loading in Inventor.

Always test installation on the target environment.

---

## 13. Error Handling

Add-ins should handle:

- invalid document context;
- missing objects;
- API exceptions;
- event lifecycle problems;
- UI registration problems;
- dependency loading problems;
- shutdown issues.

Do not swallow exceptions without a deliberate reason.

---

## 14. Performance

Minimize:

- repeated API calls;
- repeated geometry traversal;
- unnecessary document updates;
- unnecessary UI refreshes;
- repeated document loading.

Large assemblies require particular attention to API call frequency.

---

## 15. Project Structure

A typical Add-in source structure may be:

src/
    AddInServer.cs
    Commands/
    UI/
    Events/
    Services/
    Utilities/

The exact structure can vary.

Prefer separation of:

- Add-in lifecycle;
- commands;
- UI;
- event handlers;
- business logic;
- Inventor API helpers.

---

## 16. Testing

When possible, test:

1. Add-in installation;
2. Inventor startup;
3. Add-in activation;
4. command creation;
5. Ribbon controls;
6. command execution;
7. document switching;
8. event handling;
9. Add-in deactivation;
10. Inventor shutdown.

---

## 17. Related Knowledge

- APInotes.md
- api-compatibility.md
- object-model.md
