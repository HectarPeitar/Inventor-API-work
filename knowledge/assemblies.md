# Autodesk Inventor Assembly API

## Purpose

This file contains knowledge specific to Autodesk Inventor Assembly automation.

Primary target:

- Autodesk Inventor 2026

---

## 1. Assembly Structure

Conceptually:

AssemblyDocument
-> AssemblyComponentDefinition
-> ComponentOccurrences

The AssemblyComponentDefinition is the primary entry point for many Assembly operations.

---

## 2. AssemblyDocument

An Assembly document normally has the file extension:

.iam

The corresponding API document object is:

AssemblyDocument

Before using Assembly-specific API, verify that the active document is an Assembly.

---

## 3. AssemblyComponentDefinition

AssemblyComponentDefinition provides access to Assembly-specific model information.

Important conceptual areas include:

- ComponentOccurrences
- Constraints
- Joints
- Parameters
- assembly-specific features and objects

---

## 4. ComponentOccurrence

A ComponentOccurrence represents one occurrence of a component inside an Assembly.

Example:

Assembly:

MainAssembly.iam

Occurrences:

- PartA:1
- PartA:2
- PartB:1

PartA:1 and PartA:2 may reference the same underlying component definition.

---

## 5. Occurrence vs Definition

Important distinction:

ComponentOccurrence
- instance inside the Assembly.

ComponentDefinition
- definition of the underlying component.

Do not treat these as interchangeable.

---

## 6. Referenced Documents

Typical relationship:

AssemblyDocument
-> ComponentOccurrence
-> referenced component
-> referenced Document
-> ComponentDefinition

When traversing an Assembly, consider:

- missing references;
- unresolved references;
- suppressed components;
- virtual components;
- unloaded documents.

---

## 7. Native Objects and Proxies

An object belonging to a referenced Part may have a proxy representation when accessed through the Assembly context.

Conceptually:

Part context:
Native object

Assembly context:
Proxy object

When geometry or feature access fails in an Assembly, determine whether the correct proxy object is required.

---

## 8. Recursive Assembly Traversal

Assemblies may contain nested Assemblies.

Conceptually:

Top Assembly
-> Occurrence
   -> Part
or
   -> Sub Assembly
      -> Occurrence
         -> Part

Assembly traversal code should account for nested assemblies when the requirement includes the complete hierarchy.

Do not assume that all occurrences are leaf components.

---

## 9. Occurrence Names

Occurrence names are not necessarily the same as file names.

Examples:

PartA:1
PartA:2

Both occurrences may reference:

PartA.ipt

Do not assume occurrence name == file name.

---

## 10. Component Identity

When identifying components, consider what the requirement actually means:

- occurrence identity;
- document identity;
- file path;
- component definition;
- part number;
- display name.

Do not use display names as unique identifiers unless uniqueness is guaranteed.

---

## 11. Suppressed Components

Assembly automation may encounter suppressed components.

Do not assume every occurrence is in a fully active state.

Check the relevant occurrence state before attempting operations that require loaded/active component data.

---

## 12. Constraints and Joints

Assemblies can contain different mechanisms for positioning components.

Relevant concepts include:

- assembly constraints;
- joints;
- grounded components;
- component transforms.

Use the appropriate API for the specific Assembly design.

---

## 13. Occurrence Transforms

Component occurrences have spatial relationships within the Assembly.

When working with positions and transforms, consider:

- component coordinate system;
- Assembly coordinate system;
- occurrence transform;
- nested Assembly transforms.

Do not assume coordinates are always expressed in the same context.

---

## 14. Assembly Parameters

Parameters may exist at different levels.

Distinguish between:

- Assembly parameters;
- Part parameters;
- parameters of referenced components.

When modifying a parameter, first determine which document/component owns it.

---

## 15. Performance

Large assemblies can contain thousands of objects.

Avoid unnecessary:

- recursive traversal;
- repeated document access;
- repeated geometry queries;
- repeated parameter lookups;
- unnecessary updates.

Cache information where appropriate.

---

## 16. Assembly Automation Checklist

Before modifying an Assembly:

1. confirm document type;
2. obtain AssemblyComponentDefinition;
3. identify target occurrence;
4. determine referenced document/component;
5. determine whether proxy context is required;
6. check occurrence state;
7. check parameter/feature ownership;
8. perform modification;
9. update only when required;
10. handle errors.

---

## 17. Related Knowledge

- APInotes.md
- object-model.md
- parameters.md
- units.md
- api-compatibility.md
