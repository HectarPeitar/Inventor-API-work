# Autodesk Inventor iLogic

## Purpose

This file contains knowledge specific to Autodesk Inventor iLogic.

Primary target:

- Autodesk Inventor 2026

iLogic must be treated as a distinct programming environment built around Inventor functionality.

## API Verification in iLogic

iLogic provides access to the Inventor API, but iLogic code should not
assume that a familiar-looking .NET or VBA member exists on an
Inventor object.

When accessing Inventor API objects from iLogic:

- verify the actual Inventor API type;
- verify the exact property or method name;
- verify the expected return type;
- distinguish iLogic helper objects from Inventor API objects;
- prefer current Inventor API documentation over memory or generic
  .NET conventions.

For example, do not assume that an Inventor `Document` has a `Name`
property simply because other .NET objects commonly expose `Name`.

When the exact API member is uncertain, verify it before generating
the final rule.

---

## iLogic Limitations Observed in Inventor 2026

The following points were confirmed by validation of iLogic rules in Autodesk Inventor 2026. They are general iLogic behaviour, not specific to one rule.

### Document type detection

iLogic does not expose the `DocumentTypeEnum` used by the Inventor API.
Do not use `doc.DocumentType = DocumentTypeEnum.kPartDocument` or
similar in iLogic.

To restrict an iLogic rule to a specific document type, cast
`doc.ComponentDefinition` to the appropriate subtype
(`PartComponentDefinition`, `AssemblyComponentDefinition`) inside a
`Try`/`Catch`. A wrong document type is then reported as a clean
runtime error and the rule can exit gracefully.

### Document path properties

`doc.FullName` is not available on the iLogic-wrapped `Document` object.
`ThisDoc.FullFileName` is also not available on `ThisDoc` in current
iLogic.

If a file path is required, use `ThisApplication.ActiveDocument.DisplayName`
or obtain the file path through the Inventor API on a non-iLogic
reference. Verify the exact available property on the current Inventor
version before relying on it.

### Parameter lock state

`UserParameter.IsLocked` is not exposed in iLogic. The presence of a
lock or read-only state can only be detected indirectly by wrapping the
`Expression` (or `Value`) assignment in a `Try`/`Catch`.

### Parameter value vs. expression

`Parameter.Value` is a numeric property interpreted in the document's
internal unit (for example, centimetres even when the document is
displayed in millimetres). Never show `Parameter.Value` directly to the
user.

`Parameter.Expression` is a string property and accepts unit suffixes
such as `"50 mm"`, `"1 in"`, or expressions like `"Width * 2"`. To set
a parameter with an explicit, user-facing unit, assign to
`Parameter.Expression` rather than to `Parameter.Value`.

### Displaying parameter values

Use `doc.UnitsOfMeasure.GetStringFromValue(value, UnitsTypeEnum.kMillimeterLengthUnits)`
(or another `UnitsTypeEnum` constant) to format a parameter value for
display. The unit type passed to `GetStringFromValue` is the unit the
user should see, not the document's internal unit.

**Important:** `GetStringFromValue` returns a string formatted according to the
user's current culture (e.g., `"500,000 mm"` with comma as decimal separator in
Dutch locale). When parsing this string back to a number, use
`CultureInfo.CurrentCulture`, NOT `CultureInfo.InvariantCulture`. Using
`InvariantCulture` will misinterpret the comma as a thousands separator,
resulting in values that are 1000x too large.

See `knowledge/errors/ilogic/iLogic-GetStringFromValue-Culture.md` for details.

---

## 1. iLogic Overview

iLogic provides rule-based automation inside Autodesk Inventor.

Typical use cases:

- parameter automation;
- iProperties;
- component control;
- feature control;
- model configuration;
- file operations;
- user interaction;
- event-driven automation;
- automation of repetitive design tasks.

---

## 2. iLogic and Inventor API

iLogic can use both:

1. iLogic-specific functionality
2. Autodesk Inventor API objects

These are not the same API.

Examples of iLogic-specific functionality include:

- ThisApplication
- ThisDoc
- Parameter
- iProperties
- Component
- Feature
- iLogic Forms
- Event Triggers

The Inventor API contains objects such as:

- Application
- Document
- PartDocument
- AssemblyDocument
- ComponentDefinition
- ComponentOccurrence
- Parameter

---

## 3. ThisApplication

`ThisApplication` provides access to the active Inventor Application from iLogic.

Conceptually:

ThisApplication
-> ActiveDocument

Use the Inventor API when functionality requires direct access to Inventor objects.

---

## 4. ThisDoc

`ThisDoc` is iLogic-specific.

Do not automatically treat `ThisDoc` as interchangeable with every Inventor API Document reference.

Understand the rule context before using it.

---

## 5. Parameters

iLogic provides simplified parameter access.

Parameters may also be accessed through the Inventor API.

Use iLogic parameter functionality when it provides the simplest solution.

Use the Inventor API when more detailed control is required.

Always consider:

- parameter name;
- parameter type;
- expression;
- units;
- read-only state;
- dependencies;
- model update.

See `parameters.md`.

---

## 6. iProperties

iLogic provides convenient access to iProperties.

Common use cases include:

- setting part numbers;
- setting descriptions;
- reading custom properties;
- updating metadata.

For complex or generic document metadata operations, the Inventor API may be more appropriate.

---

## 7. Components

iLogic provides component-related functionality for assemblies.

Use this for straightforward assembly configuration tasks.

For advanced Assembly API work, use the Inventor Assembly API.

See `assemblies.md`.

---

## 8. Features

iLogic provides convenient mechanisms for controlling certain features.

Typical operations may include:

- suppressing;
- enabling;
- checking state;
- changing feature-related parameters.

For advanced feature operations, use the Inventor API.

---

## 9. Internal Rules

An internal rule is stored within the Inventor document.

Use internal rules when:

- the rule is specific to one document;
- portability outside the document is not important;
- the rule is relatively small.

---

## 10. External Rules

External rules are stored separately from the Inventor document.

Use external rules when:

- rules are reused;
- rules are centrally maintained;
- rules are large;
- rules are shared between documents;
- version control is important.

---

## 11. Event Triggers

iLogic rules can be executed in response to events.

When using Event Triggers, consider:

- repeated execution;
- performance;
- recursive updates;
- document context;
- unintended modifications;
- error handling.

A triggered rule should be safe to execute repeatedly whenever practical.

---

## 12. iLogic Forms

iLogic Forms are useful for simple user interaction.

Use Forms when:

- the UI is simple;
- interaction is document-specific;
- a full Add-in UI is unnecessary.

Consider a .NET Add-in when requirements include:

- complex UI;
- persistent modeless windows;
- custom Ribbon commands;
- complex state;
- advanced event handling.

---

## 13. External Assemblies

iLogic can interact with external .NET assemblies.

When using external assemblies, verify:

- .NET compatibility;
- Inventor Interop version;
- assembly dependencies;
- load path;
- Inventor version;
- permissions.

Interop version mismatches can cause runtime failures.

See `api-compatibility.md`.

---

## 14. Units

Never assume numeric input is automatically in millimeters or another specific unit.

When a rule accepts user input:

- determine expected units;
- validate input;
- use Inventor unit handling where appropriate;
- avoid hidden conversions.

See `units.md`.

---

## 15. Error Handling

Rules should handle expected failures.

Potential problems include:

- missing parameter;
- wrong document type;
- missing component;
- missing feature;
- invalid value;
- invalid unit;
- missing file;
- API exception.

User-facing rules should provide useful error information.

Avoid silently ignoring failures unless this behavior is intentional.

---

## 16. Performance

Avoid unnecessary:

- model updates;
- rule execution;
- repeated parameter reads;
- repeated API calls;
- document operations.

Event-triggered rules require particular attention to performance.

---

## 17. iLogic Design Principles

Prefer:

- small rules;
- clear names;
- reusable helper methods;
- explicit document context;
- explicit units;
- predictable execution;
- error handling.

Avoid:

- large monolithic rules;
- hidden dependencies;
- unnecessary UI interaction;
- hardcoded file paths;
- unexplained magic numbers.

---

## 18. Related Knowledge

- APInotes.md
- api-compatibility.md
- object-model.md
- assemblies.md
- parameters.md
- units.md
