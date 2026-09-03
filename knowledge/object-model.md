# Autodesk Inventor Object Model

## Purpose

This file describes the conceptual relationships between important Autodesk Inventor API objects.

It is intended to help an AI assistant navigate the API correctly.

Primary target:

- Autodesk Inventor 2026

This is a conceptual guide, not a complete API reference.

---

## 1. High-Level Structure

Conceptually:

Application
|
+-- Documents
|
+-- ActiveDocument
|
+-- UserInterfaceManager
|
+-- TransactionManager
|
+-- TransientGeometry
|
+-- TransientObjects

ActiveDocument
|
+-- PartDocument
|   |
|   +-- PartComponentDefinition
|
+-- AssemblyDocument
|   |
|   +-- AssemblyComponentDefinition
|
+-- DrawingDocument
|
+-- PresentationDocument

---

## 2. Application

Application represents the running Inventor application.

Typical navigation:

Application
-> ActiveDocument
-> Document-specific API

Application-level objects include functionality for:

- active document;
- document collection;
- UI;
- transactions;
- transient geometry;
- transient objects.

---

## 3. Document

Document represents an Inventor document.

Important document types:

- PartDocument
- AssemblyDocument
- DrawingDocument
- PresentationDocument

The document type determines the valid document-specific API.

---

## 4. Part Document

Conceptual structure:

PartDocument
|
+-- PartComponentDefinition
    |
    +-- Parameters
    +-- Features
    +-- Sketches
    +-- WorkFeatures
    +-- B-Rep geometry

Use PartComponentDefinition for Part-specific model operations.

---

## 5. Assembly Document

Conceptual structure:

AssemblyDocument
|
+-- AssemblyComponentDefinition
    |
    +-- ComponentOccurrences
    +-- Constraints
    +-- Joints
    +-- Parameters
    +-- other assembly objects

AssemblyComponentDefinition is the main entry point for Assembly-specific model operations.

---

## 6. ComponentOccurrence

A ComponentOccurrence represents an occurrence of a component inside an Assembly.

Conceptually:

Assembly
-> ComponentOccurrence
-> referenced Component
-> referenced Document
-> ComponentDefinition

A ComponentOccurrence is not the same as the underlying component definition.

---

## 7. Definition vs Occurrence

Important distinction:

ComponentDefinition
- describes the component itself.

ComponentOccurrence
- represents an instance of that component inside an Assembly.

One component definition may have multiple occurrences.

Example:

ComponentDefinition: Bolt.ipt

Occurrences:

- Bolt:1
- Bolt:2
- Bolt:3

The occurrences are separate assembly instances.

---

## 8. Native Object vs Proxy

When geometry or features are accessed through an Assembly context, Inventor may expose proxy objects.

Conceptually:

Referenced Part object
-> native object

Same object accessed through Assembly
-> proxy object

When an API call works on a Part object but fails from an Assembly, check whether a proxy is required.

---

## 9. Parameters

Parameters can exist at different levels.

Conceptually:

Document
-> ComponentDefinition
-> Parameters

iLogic also provides simplified parameter access.

Do not confuse:

- iLogic Parameter object;
- Inventor Parameter API objects;
- parameter expressions;
- displayed parameter values.

Use `parameters.md` for detailed parameter rules.

---

## 10. Features

Features are generally accessed through the appropriate component definition.

Part:

PartComponentDefinition
-> Features

Assembly:

AssemblyComponentDefinition
-> assembly-specific features/objects

Do not assume that a Part feature API applies directly to an Assembly.

---

## 11. Sketches

Sketches belong to the relevant component definition.

Typical conceptual navigation:

PartDocument
-> PartComponentDefinition
-> Sketches

Specific sketch types and functionality must be verified against the current API.

---

## 12. Geometry

Inventor provides B-Rep and transient geometry APIs.

Important conceptual distinction:

B-Rep
- geometry belonging to the model.

Transient geometry
- temporary geometry objects used for construction or API operations.

Do not confuse persistent model geometry with transient geometry.

---

## 13. Documents and References

Documents may reference other documents.

Typical Assembly relationship:

AssemblyDocument
-> ComponentOccurrence
-> referenced Document

When traversing assemblies, avoid assuming that every occurrence has the same document state.

Consider:

- missing references;
- suppressed components;
- unresolved components;
- virtual components;
- content center components;
- document loading state.

---

## 14. Drawings

Conceptual structure:

DrawingDocument
|
+-- Sheets
    |
    +-- DrawingViews
    +-- Dimensions
    +-- Annotations
    +-- PartsLists
    +-- Balloons

Drawing API is separate from Part and Assembly modeling APIs.

---

## 15. UI

Conceptual structure:

Application
-> UserInterfaceManager
-> Ribbon
-> RibbonTab
-> RibbonPanel
-> Control

Commands generally use command definitions.

UI objects belong primarily to Add-in development.

---

## 16. Transactions

Conceptual structure:

Application
-> TransactionManager
-> Transaction

Transactions group changes into a logical undo operation.

---

## 17. Events

Events can exist at several levels.

Conceptually:

Application
-> Application Events

Document
-> Document Events

UI/Commands
-> Command/UI Events

Event lifecycle must be managed carefully in Add-ins.

---

## 18. Object Navigation Rule

When writing Inventor API code, identify the object path before generating code.

Example:

Requirement:
Change a parameter in the active Part.

Object path:

Application
-> ActiveDocument
-> PartDocument
-> PartComponentDefinition
-> Parameters
-> Parameter

Do not jump directly to a guessed API member without establishing this path.

---

## 19. Document Type Rule

Always determine the document type before using document-specific objects.

Example:

If document is Part:
use PartDocument / PartComponentDefinition.

If document is Assembly:
use AssemblyDocument / AssemblyComponentDefinition.

If document is Drawing:
use DrawingDocument and drawing-specific objects.

---

## 20. Related Knowledge

- APInotes.md
- api-compatibility.md
- ilogic.md
- addins.md
- assemblies.md
- parameters.md
- units.md
