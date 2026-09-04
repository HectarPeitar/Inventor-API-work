# .clinerules

## Purpose

This directory contains behavioral rules for the AI assistant working on the Autodesk Inventor workspace.

The rules define how the AI should:

- reason about tasks;
- use the knowledge base;
- write code;
- verify API usage;
- handle uncertainty;
- debug problems;
- work with existing code;
- maintain the workspace.

---

## What belongs here?

Only rules that describe how the AI should behave.

Examples:

- coding standards;
- development workflow;
- API verification rules;
- testing expectations;
- source priority;
- error-handling principles;
- rules for maintaining the workspace.

---

## What does NOT belong here?

Do not store large amounts of technical API knowledge here.

For example:

Do not put detailed information about Parameters, Assemblies, Units, or iLogic in this directory.

That information belongs in:

    knowledge/

---

## Current Files

- `00-core.md`
  Core rules and general AI behavior.

- `10-coding-standards.md`
  Coding standards for Inventor automation.
  Includes file-management rules (section 20) and function promotion/storage rules (section 21).

- `20-workflow.md`
  Development and debugging workflow.

---

## Design Principle

`.clinerules/` answers:

> "How should the AI work?"

It should not primarily answer:

> "How does the Inventor API work?"

That belongs in `knowledge/`.
