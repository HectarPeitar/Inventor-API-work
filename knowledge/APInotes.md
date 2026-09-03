# Autodesk Inventor API Notes

## Purpose

This file provides general technical knowledge about the Autodesk Inventor API.

Primary target version:

- Autodesk Inventor 2026

Use this file for general API concepts.
Use more specific files in this folder for detailed topics.

---

## 1. API Overview

The Autodesk Inventor API exposes Inventor functionality through an object-oriented API.

Relevant programming environments include:

- C#
- VB.NET
- iLogic
- VBA
- Apprentice

For this workspace, the primary development environments are:

1. iLogic
2. C# .NET Add-ins
3. VB.NET .NET Add-ins

Do not assume that functionality available in one environment is automatically available in another.

---

## 2. Primary API Objects

Important top-level objects include:

- Application
- Documents
- Document
- PartDocument
- AssemblyDocument
- DrawingDocument
- ComponentDefinition
- PartComponentDefinition
- AssemblyComponentDefinition
- ComponentOccurrence
- Parameters
- Features
- Sketches
- Transactions
- UnitsOfMeasure
- UserInterfaceManager
- TransientGeometry
- TransientObjects

This is not a complete API reference.

Always verify exact members against the Autodesk Inventor 2026 API documentation.

---

## 3. Application

The Application object represents the running Autodesk Inventor application.

Typical navigation:

Application
-> ActiveDocument
-> Document-specific API

Important Application-level functionality includes:

- ActiveDocument
- Documents
- UserInterfaceManager
- TransactionManager
- TransientGeometry
- TransientObjects

The exact available members must be verified against the current API documentation.

---

## 4. Documents

Important document types include:

| Document | Extension | Typical API object |
|---|---|---|
| Part | .ipt | PartDocument |
| Assembly | .iam | AssemblyDocument |
| Drawing | .idw / .dwg | DrawingDocument |
| Presentation | .ipn | PresentationDocument |

Document type determines which document-specific API is available.

Never use Part-specific API without establishing that the current document is a Part.

Never use Assembly-specific API without establishing that the current document is an Assembly.

---

## 5. Component Definitions

A component definition represents the model definition inside a document.

Typical relationship:

PartDocument
-> PartComponentDefinition

AssemblyDocument
-> AssemblyComponentDefinition

ComponentDefinition is an important navigation point for model automation.

---

## 6. Parts

Typical Part structure:

PartDocument
-> PartComponentDefinition
   -> Parameters
   -> Features
   -> Sketches
   -> WorkFeatures
   -> B-Rep geometry

Part-specific functionality should be implemented through the appropriate Part API.

---

## 7. Assemblies

Typical Assembly structure:

AssemblyDocument
-> AssemblyComponentDefinition
   -> ComponentOccurrences
   -> Constraints
   -> Joints
   -> Parameters
   -> other assembly objects

Assembly automation often works with ComponentOccurrence objects.

A ComponentOccurrence is not the same thing as the ComponentDefinition of the referenced document.

---

## 8. Assembly Context

When accessing geometry or features through an assembly, distinguish between:

- native object
- component occurrence
- component definition
- proxy object

An object accessed through an assembly context may require a proxy.

When assembly geometry or feature access behaves unexpectedly, check whether the object is being accessed in the correct context.

---

## 9. Parameters

Parameters are a major part of Inventor automation.

Relevant concepts include:

- Model Parameters
- User Parameters
- Reference Parameters
- Parameter expressions
- Parameter values
- Units

When changing parameters, consider:

- units
- expression syntax
- dependencies
- model updates
- read-only/reference parameters

See `parameters.md` for detailed parameter guidance.

---

## 10. Units

Never assume that a raw numeric value automatically represents millimeters, degrees, inches, or another user-facing unit.

Inventor has internal/API unit handling that may differ from the units displayed in the UI.

Use UnitsOfMeasure when explicit conversion is required.

See `units.md` for detailed unit guidance.

---

## 11. Transactions

Transactions can group multiple model changes into a logical undo operation.

Typical concept:

Start Transaction
-> perform changes
-> Commit on success
-> Abort on failure

Use transactions when appropriate for grouped model modifications.

Do not use transactions unnecessarily for read-only operations.

See `transactions.md` if detailed transaction knowledge is added later.

---

## 12. Events

Inventor provides event APIs for responding to application, document, command, user-input, and UI activity.

Events are particularly important for Add-ins.

When using events, consider:

- registration
- unregistration
- event lifetime
- duplicate subscriptions
- shutdown
- object lifetime
- cleanup

See `addins.md` or future `events.md` for detailed information.

---

## 13. User Interface

Inventor provides APIs for creating and managing UI elements.

Relevant concepts include:

- UserInterfaceManager
- Ribbon
- Ribbon Tabs
- Ribbon Panels
- Command Definitions
- Controls
- Buttons
- Dialogs

For simple iLogic interaction, iLogic Forms may be preferable.

For persistent or complex UI, use a .NET Add-in.

---

## 14. Attributes

Attributes allow custom data to be associated with Inventor objects.

Use Attributes when application-specific metadata needs to be attached to Inventor objects.

When using custom Attributes, document:

- AttributeSet name
- Attribute name
- data type
- purpose
- version if relevant

---

## 15. Reference Keys

Reference Keys can be used to identify Inventor objects across sessions or changes.

Use them when persistent object identification is required.

Do not rely exclusively on temporary object references when objects must be identified later.

---

## 16. Browser

The Browser API provides access to Inventor browser nodes and browser-related functionality.

Use Browser API only when browser functionality is part of the requirement.

---

## 17. Client Graphics

Client Graphics can be used to display custom graphics in the Inventor viewport.

This is primarily useful for interactive Add-ins and visualization tools.

---

## 18. Apprentice

Apprentice provides access to certain Inventor document functionality without running the full Inventor application.

Apprentice does not provide the complete functionality of the Inventor API.

Always verify whether the required operation is supported by Apprentice.

---

## 19. Interop Assemblies

.NET Add-ins use Autodesk Inventor Interop assemblies.

For Inventor 2026:

- use the Inventor 2026 Interop assemblies;
- do not mix Interop versions without a specific reason;
- verify references against the local Inventor installation;
- do not assume a hardcoded installation path is valid on every machine.

A typical installation location is:

C:\Program Files\Autodesk\Inventor 2026\Bin\Public Assemblies\

The actual installation path must be verified locally.

---

## 20. API Verification

When using an unfamiliar API member, verify:

1. exact class/interface
2. exact member name
3. parameters
4. return type
5. inheritance
6. document type
7. Inventor version
8. relevant limitations

Never create an API member based only on a plausible name.

---

## 21. Performance

Avoid unnecessary:

- API calls
- model updates
- geometry queries
- UI updates
- document opens/closes
- repeated traversal of large assemblies

For large models and assemblies, minimize repeated API calls.

Cache information when appropriate.

---

## 22. Error Handling

Inventor automation must account for:

- missing documents
- wrong document types
- missing parameters
- missing features
- null/Nothing references
- read-only objects
- invalid values
- invalid units
- COM/API exceptions
- incorrect assembly context
- event lifecycle problems

Error messages should provide enough context to diagnose the problem.

---

## 23. Official Documentation

Autodesk Inventor API:

https://help.autodesk.com/view/INVNTOR/2026/ENU/

Autodesk Inventor Object Type Enum:

https://help.autodesk.com/view/INVNTOR/2026/ENU/?guid=ObjectTypeEnum

The official Autodesk documentation is the primary API reference.

---

## 24. Related Knowledge Files

Use the following files for more specific information:

- api-compatibility.md
- object-model.md
- ilogic.md
- addins.md
- assemblies.md
- parameters.md
- units.md
