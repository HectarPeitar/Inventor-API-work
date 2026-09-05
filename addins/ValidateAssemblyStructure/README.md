# ValidateAssemblyStructure

## Purpose

Validates that an active assembly document contains required components (FRAME, MOTOR, COVER) at any depth in the assembly hierarchy. Reports on component presence, suppression state, duplicates, and inspection errors.

## Inventor Version

Autodesk Inventor 2026

## Programming Environment

iLogic (VB.NET)

## What the Function Does

The rule recursively traverses every ComponentOccurrence in the active AssemblyComponentDefinition, from the top level down through nested subassemblies. It records whether each required component is present (by case-insensitive partial match on the occurrence name), the suppression state of each found occurrence, missing components, duplicate components, and inspection errors. After traversal, it produces a structured validation report and assigns a status: PASS (all present and at least one active), WARNING (all present but all suppressed or duplicates exist), or FAIL (missing, wrong document type, or traversal failed).

## Supported Document Types

Assembly documents (`.iam`) only. Part documents (`.ipt`) and Drawing documents (`.idw`) produce a FAIL with an explanatory error.

## Required Setup

Open or create an Assembly document (`.iam`) containing components whose names contain FRAME, MOTOR, or COVER. No external dependencies or parameters required.

## How to Install

In Inventor, go to **Manage → iLogic → Rules**, click **Add External Rule**, browse to `addins/ValidateAssemblyStructure/ValidateAssemblyStructure.vb`, and save the rule.

## How to Use

Open the Assembly document, go to **Manage → iLogic → Rules**, select **ValidateAssemblyStructure**, and click **Run**. A MessageBox displays the validation report.

## Report Format

```
============================================================
 ValidateAssemblyStructure - Validation Report
============================================================

Document: <AssemblyName>.iam
Status:   <PASS | WARNING | FAIL>

------------------------------------------------------------
 COMPONENT DETAILS
------------------------------------------------------------

  FRAME
    Total Occurrences: <n>
    Active: <n>
    Suppressed: <n>
    Occurrences:
      - [ACTIVE]   FRAME:1

  MOTOR
    ...

  COVER
    ...

------------------------------------------------------------
 SUMMARY
------------------------------------------------------------

Missing Components: (none) | <list>
Duplicate Components: (none) | <list>
Validation Errors: (none) | <list>

------------------------------------------------------------
 RESULT EXPLANATION
------------------------------------------------------------

  <PASS|WARNING|FAIL> - <explanation>

============================================================
```

## Configuration

The rule contains optional constants near the top of `Sub Main`:

| Constant | Default | Purpose |
|----------|---------|---------|
| `DebugMode` | `False` | When `True`, the report is also written to a text file. When `False`, only the MessageBox shows. |
| `DebugOutputFile` | (scratch path) | Path used when `DebugMode = True`. Not used in production. |

## Required Components

By default, the rule searches for FRAME, MOTOR, and COVER (case-insensitive, partial match on occurrence name). To search for different components, edit the `requiredComponents` list near the top of `Sub Main`:

```vb
Dim requiredComponents As New List(Of String)({"FRAME", "MOTOR", "COVER"})
```

## Component Matching

The rule uses **case-insensitive partial matching** on the occurrence name:

| Occurrence Name | Matches |
|-----------------|---------|
| `FRAME:1` | FRAME |
| `Motor_Assembly:1` | MOTOR |
| `Cover_Panel:1` | COVER |
| `MainFrame:1` | FRAME |

The occurrence name must **contain** the required identifier.

## Important Behavior Notes

- Component matching is by occurrence **name**, not by the referenced document file name.
- Recursive traversal handles unlimited nesting depth.
- Suppressed components are detected and reported, but their sub-occurrences are **not** traversed. This is a known Inventor API limitation — accessing `SubOccurrences` on a suppressed `ComponentOccurrence` throws an exception. The rule handles this gracefully by checking the suppression state before attempting traversal.
- Inspection errors are recorded in the report but do not stop traversal.
- If a suppression state cannot be read, the occurrence is conservatively treated as suppressed.

## Validation Result

| Test Case | Setup | Expected Status |
|-----------|-------|----------------|
| 1 | All three components present and active | PASS |
| 2 | One or more components missing | FAIL |
| 3 | Required component in a nested subassembly | PASS |
| 4 | Multiple occurrences of a required component | WARNING |
| 5 | One required component suppressed | WARNING |
| 6 | Active document is not an Assembly | FAIL |
| 7 | All required components suppressed | WARNING |

All seven test cases were verified during development in Autodesk Inventor 2026.

## Known Limitations

- Only checks the **active** document. Does not iterate through all open documents.
- Does not validate the file name of referenced documents. Only the occurrence name is inspected.
- Does not detect component swaps in/out of the assembly (only presence/absence in the BOM tree).
- Does not validate geometry, constraints, or iProperties. Only structural presence and suppression state.
- Case-insensitive partial match may produce false positives if a non-target occurrence name happens to contain a target identifier (for example, an occurrence named `MotorCover:1` would match both `MOTOR` and `COVER`).