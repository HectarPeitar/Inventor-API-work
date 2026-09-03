# Autodesk Inventor Units

## Purpose

This file contains rules and concepts for handling units in Autodesk Inventor automation.

Primary target:

- Autodesk Inventor 2026

Units are a high-risk area for automation bugs.

---

## 1. Never Assume Units

Never assume that a raw numeric value represents:

- millimeters;
- centimeters;
- inches;
- degrees;
- radians;
- or another unit

without checking the API/context.

---

## 2. Display Units vs API Units

Distinguish between:

- units displayed to the user;
- units used in expressions;
- units used internally/API-side.

These are not necessarily identical.

---

## 3. UnitsOfMeasure

Use Inventor's `UnitsOfMeasure` functionality when explicit unit conversion or interpretation is required.

Conceptually:

User Input
-> interpret units
-> UnitsOfMeasure
-> Inventor API value

---

## 4. User Input

When accepting user input:

Prefer explicit unit-aware input.

Good:

25 mm

Potentially ambiguous:

25

If the UI does not allow explicit units, the expected unit must be clearly documented.

---

## 5. Parameter Expressions

Parameter expressions may contain units.

Examples conceptually:

25 mm
1 in
2 * Width

When modifying parameter expressions:

- preserve valid expression syntax;
- preserve intended units;
- consider dependent parameters.

---

## 6. Geometry

Geometry operations are particularly sensitive to units.

Before creating or modifying geometry, determine:

- required API unit;
- source unit;
- target unit;
- conversion method.

Never copy a numeric value from a UI or external source directly into geometry API calls without understanding its unit.

---

## 7. Angles

Angles require the same caution as distances.

Determine whether the API expects:

- degrees;
- radians;
- angle expressions;
- another representation.

Do not assume degrees based only on what the user sees in the UI.

---

## 8. External Data

When importing values from:

- Excel;
- CSV;
- databases;
- JSON;
- text files;
- user input;

always define the expected unit.

Example:

A CSV column called:

Length

is ambiguous.

Prefer:

Length_mm

or:

Length_in

or include a separate unit definition.

---

## 9. Unit Conversion Strategy

Preferred approach:

1. identify source unit;
2. identify target API unit;
3. perform explicit conversion;
4. pass converted value to API;
5. document the conversion.

Avoid hidden conversion logic.

---

## 10. iLogic

iLogic often makes unit-aware expressions convenient.

However, do not assume iLogic syntax and raw Inventor API numeric values use identical semantics.

When moving code between iLogic and C#/.NET, review all unit handling.

---

## 11. Assembly Context

When working with Assembly geometry and transforms, also consider coordinate-system context.

Do not assume that a distance or transform value is only a unit problem.

It may also be a coordinate-space problem.

---

## 12. Unit Testing

When testing unit-sensitive code, test at least:

- default document units;
- alternative document units;
- explicit unit input;
- decimal values;
- unit conversions;
- parameter expressions.

---

## 13. Common Unit Bugs

Typical mistakes include:

- assuming everything is millimeters;
- confusing display units with API units;
- using degrees where radians are expected;
- converting twice;
- forgetting conversion;
- replacing an expression with a raw number;
- interpreting external data without a defined unit.

---

## 14. Unit Checklist

Before using a physical numeric value:

1. What does the value represent?
2. What unit does the source use?
3. What unit does the API expect?
4. Is the value an expression or raw number?
5. Is conversion required?
6. Can `UnitsOfMeasure` be used?
7. Has the unit behavior been tested?

---

## 15. Related Knowledge

- APInotes.md
- parameters.md
- ilogic.md
- assemblies.md
- object-model.md
- api-compatibility.md
