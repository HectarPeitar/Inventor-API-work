# Development Workflow — Autodesk Inventor AI

## Purpose

Define the workflow the AI should follow when solving Inventor automation and development tasks.

---

## 1. New Task Workflow

For a new task:

1. Understand the requirement.
2. Identify the programming environment.
3. Identify the Inventor version.
4. Identify the document type.
5. Identify the required object context.
6. Search the relevant knowledge files.
7. Search tested/ for existing working examples.
8. Verify unfamiliar API members.
9. Design the smallest appropriate solution.
10. Implement the solution.
11. Review units.
12. Review error handling.
13. Review version compatibility.
14. Review performance.
15. State what has and has not been tested.

---

## 2. Development Environment Workflow

Use the appropriate environment for each type of work.

### VS Code + Cline

Use VS Code/Cline for:

- planning;
- code generation;
- code editing;
- repository navigation;
- knowledge lookup;
- documentation;
- refactoring;
- reviewing existing code;
- maintaining examples;
- maintaining tested implementations;
- maintaining templates;
- project file preparation.

### Visual Studio

Use Visual Studio for .NET Inventor Add-ins when:

- creating or opening a Visual Studio solution;
- building an Add-in;
- resolving project/reference issues;
- debugging C#;
- debugging VB.NET;
- attaching to Inventor;
- inspecting runtime state;
- debugging Inventor API calls.

### Autodesk Inventor

Use Autodesk Inventor for:

- executing iLogic rules;
- loading Add-ins;
- testing Add-in commands;
- testing UI;
- testing events;
- testing model modifications;
- validating actual Inventor API behavior.

---

## Environment Handoff

When a task requires Visual Studio or Inventor, Cline should prepare the required files and explain the next manual step.

For example:

    Cline / VS Code
        ->
    Create or modify Add-in
        ->
    Open solution in Visual Studio
        ->
    Build
        ->
    Start or attach to Inventor
        ->
    Test
        ->
    Report result back to Cline

Do not claim that an Add-in has been successfully built or tested unless that has actually been verified.

---

## 3. Programming Context

Before writing code, establish whether the task is:

- iLogic;
- external iLogic;
- C# Add-in;
- VB.NET Add-in;
- VBA;
- Apprentice;
- external automation.

If the context is unclear and materially affects the solution, determine it before implementation.

---

## 4. Document Context

Establish:

- active document;
- document type;
- ComponentDefinition;
- target object;
- Assembly context;
- proxy requirements.

Example object path:

    Application
    -> ActiveDocument
    -> PartDocument
    -> PartComponentDefinition
    -> Parameters
    -> Parameter

Do not skip context merely because a shorter API call appears possible.

---

## 5. Knowledge Lookup

Use the most specific knowledge file available.

Example:

    Parameter task
    -> parameters.md
    -> units.md
    -> object-model.md if context requires it

Do not load or reproduce the entire knowledge base when only one topic is relevant.

---

## 6. Tested Examples

Before creating new code:

1. Search tested/.
2. Find the closest matching implementation.
3. Compare Inventor version.
4. Compare programming environment.
5. Compare document context.
6. Reuse proven patterns where appropriate.

---

## 7. API Verification

When an API member is unfamiliar:

1. Identify the expected class/interface.
2. Identify the expected member.
3. Verify its existence.
4. Verify parameters.
5. Verify return type.
6. Verify document/context requirements.
7. Verify Inventor version.
8. Verify limitations.

Do not substitute a guessed API member merely because the name appears plausible.

---

## 8. Implementation Strategy

Prefer the smallest implementation that:

- satisfies the requirement;
- uses verified API;
- handles expected failures;
- respects document context;
- handles units correctly;
- is maintainable.

Do not add architecture that the task does not require.

---

## 9. Bug-Fixing Workflow

When debugging:

    Symptom
        |
        v
    Determine compile-time or runtime failure
        |
        v
    Check programming context
        |
        v
    Check Inventor version
        |
        v
    Check document context
        |
        v
    Check API member
        |
        v
    Check units
        |
        v
    Check object lifetime/state
        |
        v
    Check existing tested examples
        |
        v
    Apply smallest reasonable fix
        |
        v
    Test

---

## 10. Compile Errors

For compile errors:

1. Read the exact error.
2. Identify the failing symbol.
3. Verify namespace/reference.
4. Verify API member.
5. Verify project target.
6. Verify Interop version.
7. Verify language/framework compatibility.

Do not rewrite unrelated code to solve a single compile error.

---

## 11. Runtime Errors

For runtime errors, check:

- document state;
- object existence;
- object type;
- proxy/native context;
- suppressed/unresolved components;
- API state;
- Interop version;
- external dependencies;
- event lifetime.

---

## 12. Old Code Migration

For old code:

    Old code
        |
        v
    Determine original Inventor version
        |
        v
    Determine programming environment
        |
        v
    Determine .NET version
        |
        v
    Determine Interop version
        |
        v
    Check api-compatibility.md
        |
        v
    Verify API members
        |
        v
    Determine Inventor 2026 equivalent
        |
        v
    Implement
        |
        v
    Test

Do not assume that old Autodesk training code is directly suitable for Inventor 2026.

---

## 13. Add-in Development Workflow

## Add-in Development Workflow

For a new or modified .NET Inventor Add-in:

1. Establish Inventor version.
2. Establish .NET version.
3. Determine the target language.
4. Check `knowledge/addins.md`.
5. Check `knowledge/api-compatibility.md`.
6. Check `templates/` for an appropriate starting point.
7. Check `tested/` for proven API patterns.
8. Create or modify the project in `addins/`.
9. Prepare the Visual Studio solution and project files.
10. Configure the required Inventor Interop references.
11. Implement the Add-in lifecycle.
12. Implement commands.
13. Implement UI where required.
14. Implement events where required.
15. Implement business logic.
16. Implement cleanup and lifecycle handling.
17. Review error handling.
18. Review version compatibility.
19. Build the Add-in in Visual Studio.
20. Test the Add-in inside Autodesk Inventor.
21. Use files from `cadfiles/` for safe CAD testing.
22. Record successful patterns in `tested/`.
23. Update `knowledge/` when a general technical insight has been established.

### Important

- Cline may create and modify the Add-in source code and project files.
- Cline should not claim that the Add-in builds, loads, or works correctly unless the result has actually been verified.
- A successful code-generation step is not equivalent to a successful build.
- A successful build is not equivalent to a successful Inventor runtime test.

---

## 14. iLogic Workflow

For a new iLogic rule:

1. Determine document context.
2. Identify parameters/components/features involved.
3. Check knowledge/ilogic.md.
4. Check knowledge/parameters.md and/or knowledge/units.md.
5. Check tested/ for similar rules.
6. Implement the smallest solution.
7. Handle expected errors.
8. Test the rule.
9. Document important assumptions.

---

## 15. Assembly Workflow

For Assembly tasks:

1. Confirm AssemblyDocument.
2. Obtain AssemblyComponentDefinition.
3. Identify target occurrence.
4. Determine referenced component.
5. Determine whether the target is nested.
6. Determine whether native or proxy objects are required.
7. Check suppression/unresolved state.
8. Determine parameter/feature ownership.
9. Modify.
10. Update if necessary.
11. Test.

---

## 16. Parameter Workflow

For parameter tasks:

1. Identify owning document.
2. Identify owning ComponentDefinition.
3. Identify parameter type.
4. Locate parameter.
5. Verify parameter exists.
6. Verify writable state.
7. Determine units.
8. Determine expression/value behavior.
9. Modify.
10. Update if necessary.
11. Validate result.

---

## 17. Unit-Sensitive Workflow

For physical values:

    Source value
        |
        v
    Identify source unit
        |
        v
    Identify API expected unit
        |
        v
    Determine conversion
        |
        v
    Use UnitsOfMeasure where appropriate
        |
        v
    Apply value
        |
        v
    Validate result

Never silently assume millimeters or degrees.

---

## 18. Testing

When testing code, record:

- Inventor version;
- programming environment;
- project type;
- document type;
- relevant input;
- expected result;
- actual result;
- limitations.

If the code has not been tested, say so.

Do not label untested code as verified.

---

## 19. Updating the Workspace

When new work or information is created, determine what type of material it is.

### Active Add-in project

Store in:

    addins/

Use this for actual Add-in projects that are currently being developed.

### Tested implementation

Store in:

    tested/

Use this for verified implementations or API patterns that have been tested against Inventor.

### General technical knowledge

Store in:

    knowledge/

Use this for reusable technical knowledge about Inventor and its API.

### New AI behavior rule

Store in:

    .clinerules/

Use this only for instructions about how the AI should work.

### Reusable demonstration

Store in:

    examples/

Use this for examples that demonstrate an implementation technique.

### External source material

Store in:

    reference/

Use this for original external documentation, training material, repositories, or other source material.

### CAD test files

Store in:

    cadfiles/

Use this only for disposable Inventor test documents.

---

## 20. Avoid Duplication

Do not copy the same information into multiple directories without a clear reason.

Use the following principle:

    .clinerules/
    How the AI should work

    knowledge/
    What the AI should know

    reference/
    Where information came from

    examples/
    How something can be implemented

    tested/
    What has been verified to work

    templates/
    How to start something new

    addins/
    What is currently being developed

    cadfiles/
    Where it is safe to experiment

---

## 21. Completion Checklist

Before considering a task complete:

- [ ] Requirement understood
- [ ] Programming context identified
- [ ] Inventor version identified
- [ ] Document context identified
- [ ] Relevant knowledge checked
- [ ] API members verified
- [ ] Units checked
- [ ] Error handling reviewed
- [ ] Version compatibility reviewed
- [ ] Performance considered
- [ ] Existing code preserved where appropriate
- [ ] Testing status stated

---

## 22. Core Principle

The AI should prefer:

    Verified knowledge
        >
    Tested implementation
        >
    Current official documentation
        >
    Older examples
        >
    Community examples
        >
    General model knowledge

When uncertain:

- Verify first.
- Do not guess.
