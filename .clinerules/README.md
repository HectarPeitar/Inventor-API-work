# Cline Project Rules — Autodesk Inventor

## Purpose

This directory contains behavioral rules for Cline working on the Autodesk Inventor workspace.

The rules define:

* how Cline should apply Inventor-specific project policy;
* how Inventor code should be written;
* how API usage should be verified;
* how executable code should be validated and repaired;
* how knowledge and reusable implementations should be maintained;
* how completed functions should be stored and promoted.

Technical Inventor API knowledge belongs in `knowledge/`, not primarily in `.clinerules/`.

---

# Rule Architecture

The project rules are divided by concern.

```text
00-core.md
    ↓
Project context, rule precedence, API evidence,
knowledge sources, workspace conventions

10-coding-standards.md
    ↓
Inventor coding standards, file management,
tested/, addins/, debugging and storage

15-validation-loop.md
    ↓
Validation, failure analysis, repair iterations,
status tracking and evidence preservation

20-workflow.md
    ↓
Standard execution sequence for development tasks
```

Each file should have one primary responsibility.

Do not duplicate a complete rule from one file into another.

---

# Current Files

## `00-core.md`

Defines:

* Autodesk Inventor workspace context;
* target Inventor version;
* rule precedence;
* execution environments;
* API evidence requirements;
* source hierarchy;
* Knowledge Map usage;
* local SDK usage;
* document context;
* units;
* knowledge-base policy;
* status definitions;
* project-wide conventions.

This is the authoritative project rule for API/source evidence and project context.

---

## `10-coding-standards.md`

Defines:

* Inventor-specific coding standards;
* naming;
* method structure;
* API context;
* null/reference handling;
* error handling;
* units;
* performance;
* transactions;
* comments;
* logging;
* file management;
* `tested/`;
* `addins/`;
* DebugMode;
* storage and promotion rules.

---

## `15-validation-loop.md`

Defines:

* mandatory validation behavior;
* validation levels;
* failure classification;
* root-cause analysis;
* repair iterations;
* repeated-failure handling;
* external validation;
* error-memory rules;
* knowledge promotion;
* repair limits;
* final validation reporting.

Executable Inventor work must follow this loop.

---

## `20-workflow.md`

Defines the standard development sequence:

```text
Understand
    ↓
Inspect
    ↓
Knowledge Lookup
    ↓
Tested Pattern Lookup
    ↓
API Verification
    ↓
Plan
    ↓
Choose Implementation
    ↓
Implement
    ↓
Review
    ↓
Validate
    ↓
Repair
    ↓
Complete
```

The detailed repair procedure is defined in `15-validation-loop.md`.

---

# What Belongs in `.clinerules/`

Store rules describing how Cline should behave in this workspace.

Examples:

* coding standards;
* development workflow;
* API verification policy;
* validation requirements;
* source priority;
* error-handling policy;
* file-management rules;
* promotion rules;
* project conventions.

---

# What Does Not Belong Here?

Do not store large amounts of technical API knowledge here.

Do not put detailed reference information about:

* Parameters;
* Assemblies;
* Units;
* iLogic;
* Inventor object models;
* API members;
* SDK documentation.

Store that information in:

```text
knowledge/
```

Keep `.clinerules/` focused on:

> How should Cline work?

Keep `knowledge/` focused on:

> What is known about the technology?

---

# Related Workspace Locations

```text
knowledge/
    Technical Inventor knowledge

tested/
    Verified reusable implementation patterns

knowledge/errors/
    Verified negative knowledge and confirmed limitations

addins/
    Completed user-ready functions

scratch/
    Temporary experiments and validation artifacts
```

The rules in `.clinerules/` determine how these locations are used.

---

# Global Cline Rules

Global Cline rules are intentionally separate from these project rules.

Global rules define general development behavior and communication preferences.

These project rules define Autodesk Inventor-specific behavior.

Project-specific rules take precedence when they conflict with general global guidance.
