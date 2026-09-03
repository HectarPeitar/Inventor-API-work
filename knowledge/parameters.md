# Autodesk Inventor Parameters

## Purpose

This file contains knowledge about Inventor parameters and parameter automation.

Primary target:

- Autodesk Inventor 2026

Parameters are frequently used by both iLogic and Inventor API automation.

---

## 1. Parameter Types

Relevant concepts include:

- Model Parameters
- User Parameters
- Reference Parameters

The exact API type and availability depends on context.

---

## 2. Parameter Ownership

Before modifying a parameter, determine which object owns it.

Conceptually:

Document
-> ComponentDefinition
-> Parameters
-> Parameter

In an Assembly, also determine whether the parameter belongs to:

- Assembly;
- referenced Part;
- referenced Assembly;
- another component.

---

## 3. Parameter Name

Parameter names are commonly used for automation.

However:

- names may change;
- names may not be unique across different documents;
- names may be user-defined;
- localization may affect some user-facing naming.

Always establish the correct document/context before looking up a parameter.

---

## 4. Parameter Value

A parameter can have:

- a value;
- an expression;
- units;
- dependencies;
- a read-only/reference state.

Do not assume that the displayed value is directly interchangeable with an API numeric value.

---

## 5. Expressions

Parameters may use expressions rather than only raw numeric values.

Examples conceptually:

10 mm
Width * 2
OtherParameter + 5 mm

When modifying expressions:

- preserve valid unit syntax;
- consider dependencies;
- avoid accidentally replacing an expression with a raw value;
- verify the expected expression format.

---

## 6. Units

Parameter values are unit-sensitive.

Never assume:

10

means:

10 mm

unless the context explicitly establishes this.

Use Inventor unit handling when appropriate.

See `units.md`.

---

## 7. iLogic Parameter Access

iLogic provides convenient parameter access.

Use it for straightforward rule-based parameter operations.

Use the Inventor API when more detailed control is required.

Do not confuse iLogic parameter syntax with the underlying Inventor API.

---

## 8. Read-Only and Reference Parameters

Some parameters may not be directly writable.

Before changing a parameter, consider whether it is:

- read-only;
- reference;
- driven by another object;
- derived from geometry;
- controlled by an expression.

---

## 9. Parameter Updates

Changing a parameter may require Inventor to update/recompute the model.

Do not perform unnecessary updates repeatedly.

When changing multiple parameters, consider making all required changes before triggering an update where the API/context permits this safely.

---

## 10. Parameter Lookup

When looking up parameters by name:

1. determine document;
2. determine component definition;
3. determine parameter collection;
4. search for exact parameter;
5. handle missing parameter;
6. validate expected type;
7. validate units;
8. perform modification.

Do not assume a parameter exists.

---

## 11. Parameter Validation

Validate:

- parameter exists;
- parameter is writable;
- value is valid;
- units are correct;
- expression is valid;
- dependent model objects can accept the change.

---

## 12. Parameter Automation Checklist

Before modifying a parameter:

1. Which document owns it?
2. Which ComponentDefinition owns it?
3. Is it a Model/User/Reference parameter?
4. Is it writable?
5. What unit does it use?
6. Is it controlled by an expression?
7. Will changing it affect other parameters/features?
8. Does the model require an update?

---

## 13. Related Knowledge

- APInotes.md
- object-model.md
- ilogic.md
- assemblies.md
- units.md
