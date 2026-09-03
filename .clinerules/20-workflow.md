# Development Workflow — Autodesk Inventor AI

## Purpose

Define the workflow the AI should follow when solving Autodesk Inventor
automation, iLogic, and .NET development tasks.

The goal is to:

- use the correct technical context;
- verify Autodesk Inventor API usage;
- keep implementations as small as possible;
- separate experimental work from verified projects;
- avoid unnecessary duplication;
- clearly distinguish generated code from tested code;
- continuously improve the workspace with verified knowledge.

---

# 1. Core Development Workflow

For every new task, follow this general process:

    Requirement
        |
        v
    Identify context
        |
        v
    Check relevant knowledge
        |
        v
    Check tested patterns
        |
        v
    Verify unfamiliar API
        |
        v
    Design smallest solution
        |
        v
    Implement
        |
        v
    Review
        |
        v
    Test in the appropriate environment
        |
        v
    Determine final status
        |
        v
    Store material in the appropriate location

Before writing code:

1. Understand the requirement.
2. Identify the programming environment.
3. Identify the Inventor version.
4. Identify the document type.
5. Identify the required object context.
6. Search the relevant knowledge files.
7. Search `tested/` for existing verified patterns.
8. Verify unfamiliar API members.
9. Design the smallest appropriate solution.

After implementation:

10. Review units.
11. Review error handling.
12. Review version compatibility.
13. Consider performance where relevant.
14. Test in the appropriate environment.
15. Clearly state what has and has not been tested.
16. Determine where the resulting material belongs.

---

# 2. Development Environments

Use the appropriate environment for each type of work.

## VS Code + Cline

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
- maintaining tested patterns;
- maintaining templates;
- preparing project files.

VS Code/Cline is the primary AI development environment.

---

## Visual Studio

Use Visual Studio for .NET Inventor Add-ins when:

- creating or opening a Visual Studio solution;
- building an Add-in;
- resolving project/reference issues;
- debugging C#;
- debugging VB.NET;
- attaching to Inventor;
- inspecting runtime state;
- debugging Inventor API calls.

Do not assume that VS Code replaces Visual Studio for building
and debugging Inventor .NET Add-ins.

---

## Autodesk Inventor

Use Autodesk Inventor for:

- executing iLogic rules;
- loading Add-ins;
- testing Add-in commands;
- testing UI;
- testing events;
- testing model modifications;
- validating actual Inventor API behavior.

Autodesk Inventor is the runtime environment and the primary source
of truth for runtime behavior.

---

# 3. Environment Handoff

When a task requires Visual Studio or Autodesk Inventor, Cline should
prepare the required files and clearly explain the next manual step.

Typical .NET Add-in workflow:

    VS Code / Cline
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
    Report result to Cline

Typical iLogic workflow:

    VS Code / Cline
        ->
    Create or modify rule
        ->
    Open test document in Inventor
        ->
    Run rule
        ->
    Test result
        ->
    Report result to Cline

For small experimental tasks, Cline should normally place temporary
code in `scratch/` so that it can easily be opened, copied, or tested
manually.

Do not claim that something has been successfully built, loaded,
executed, or tested unless that has actually been verified.

---

# 4. Programming Context

Before writing code, establish whether the task is:

- iLogic;
- external iLogic;
- C# Add-in;
- VB.NET Add-in;
- VBA;
- Apprentice;
- external automation.

If the context is unclear and materially affects the solution,
determine it before implementation.

Do not convert an iLogic task into an Add-in unless the requirements
actually require an Add-in.

Do not introduce Visual Studio or a .NET project for a task that can
be solved appropriately with a simple iLogic rule.

---

# 5. Document Context

Establish:

- active document;
- document type;
- ComponentDefinition;
- target object;
- assembly context;
- proxy requirements;
- object ownership.

Example object path:

    Application
    -> ActiveDocument
    -> PartDocument
    -> PartComponentDefinition
    -> Parameters
    -> Parameter

Do not skip context merely because a shorter API call appears possible.

---

# 6. Knowledge Lookup

Use the most specific knowledge file available.

Example:

    Parameter task
        ->
    knowledge/parameters.md
        ->
    knowledge/units.md
        ->
    knowledge/object-model.md if required

For an iLogic task:

    iLogic task
        ->
    knowledge/ilogic.md
        ->
    knowledge/parameters.md and/or knowledge/units.md if required

For an Add-in task:

    Add-in task
        ->
    knowledge/addins.md
        ->
    knowledge/api-compatibility.md
        ->
    other relevant knowledge files

Do not load or reproduce the entire knowledge base when only one
topic is relevant.

---

# 7. Tested Patterns

Before creating new code:

1. Search `tested/`.
2. Find the closest matching verified pattern.
3. Compare Inventor version.
4. Compare programming environment.
5. Compare document context.
6. Check whether the pattern is still applicable.
7. Reuse verified patterns where appropriate.

A tested pattern is evidence of previously verified behavior.
It does not automatically guarantee compatibility with another
Inventor version or context.

---

# 8. API Verification

Never assume that an Autodesk Inventor API member, property, method,
enum, object type, parameter, or return type exists based only on:

- naming conventions;
- memory;
- generated code;
- generic .NET conventions;
- old examples;
- a plausible-sounding name.

Before using an unfamiliar API member:

1. Identify the expected class or interface.
2. Identify the expected member.
3. Verify that the member exists.
4. Verify parameters.
5. Verify return type.
6. Verify document/context requirements.
7. Verify Inventor version.
8. Verify relevant limitations.

Prefer the following order of evidence:

    Verified tested pattern
        >
    Current official Autodesk documentation
        >
    Local API metadata / SDK information
        >
    Official Autodesk examples
        >
    Reliable community examples
        >
    General model knowledge

If an API member cannot be verified, state the uncertainty rather than
presenting it as confirmed fact.

---

# 9. API Errors Are Evidence

When Inventor reports an error such as:

    Public member 'X' on type 'Y' not found

treat the error as evidence that the assumed API member is incorrect,
unavailable, or being accessed in the wrong context.

Do not simply replace the member with another guessed name.

Instead:

1. Identify the actual object type.
2. Check the current API documentation.
3. Verify the replacement member.
4. Check the programming context.
5. Explain the correction.
6. Update `tested/` or `knowledge/` when the result provides reusable
   information.

Runtime errors should improve future API decisions rather than being
treated as isolated fixes.

---

# 10. Implementation Strategy

Prefer the smallest implementation that:

- satisfies the requirement;
- uses verified API;
- handles expected failures;
- respects document context;
- handles units correctly;
- is maintainable.

Do not add architecture that the task does not require.

For small tasks, prefer a small implementation over introducing:

- unnecessary classes;
- unnecessary services;
- unnecessary abstractions;
- unnecessary projects;
- unnecessary dependencies.

---

# 11. Experimental Development

New code should initially be treated as experimental.

For small experiments that are not yet part of an actual project,
use `scratch/`.

Examples include:

- temporary iLogic rules;
- API experiments;
- small C# or VB.NET snippets;
- temporary scripts;
- intermediate code;
- code intended to be manually copied into Inventor.

Typical workflow:

    Cline
        ->
    Create temporary file in scratch/
        ->
    User runs/tests it
        ->
    Feedback
        ->
    Modify scratch file
        ->
    Test again

Scratch code is not automatically permanent.

---

# 12. Scratch Directory

The `scratch/` directory is the temporary workspace for experimental
code and files that are not yet part of a real project.

Use `scratch/` for:

- temporary iLogic rules;
- temporary VB.NET snippets;
- temporary C# snippets;
- small API experiments;
- test scripts;
- temporary generated files;
- intermediate files needed during development.

Scratch files may be incomplete, experimental, or untested.

The presence of a file in `scratch/` does not mean that the code has
been verified.

---

## Scratch Workflow

For a small experiment:

    Cline
        ->
    Create file in scratch/
        ->
    User runs/tests it in Inventor
        ->
    Feedback
        ->
    Modify scratch file
        ->
    Test again

When the experiment is finished, determine whether it should be
preserved.

### Reusable verified pattern

If the experiment establishes a reusable API or implementation
pattern:

    scratch/
        ->
    tested/

Store only the reusable knowledge or pattern.

Do not copy an entire project into `tested/`.

### Actual Add-in

If an experiment becomes a real .NET Add-in:

    scratch/
        ->
    addins/

The resulting Add-in has one authoritative project location.

Do not maintain a duplicate copy in `tested/`.

### One-time experiment

If the experiment has no future value, it may remain temporarily in
`scratch/` and can later be deleted.

---

# 13. Bug-Fixing Workflow

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
    Check existing tested patterns
        |
        v
    Apply smallest reasonable fix
        |
        v
    Test again
        |
        v
    Record reusable knowledge if appropriate

Do not make unrelated changes while fixing a localized problem.

---

# 14. Compile Errors

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

# 15. Runtime Errors

For runtime errors, check:

- document state;
- object existence;
- object type;
- proxy/native context;
- suppressed/unresolved components;
- API state;
- Interop version;
- external dependencies;
- event lifetime;
- object lifetime.

When a runtime error reveals incorrect API knowledge, verify the correct
API usage before applying a replacement.

---

# 16. Old Code Migration

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

Do not assume that old Autodesk training code is directly suitable
for Inventor 2026.

---

# 17. iLogic Workflow

For a new iLogic rule:

1. Determine document context.
2. Identify parameters/components/features involved.
3. Check `knowledge/ilogic.md`.
4. Check `knowledge/parameters.md` and/or `knowledge/units.md`
   when relevant.
5. Check `tested/` for similar verified rules or API patterns.
6. Verify unfamiliar API members.
7. Implement the smallest solution.
8. Place temporary rule code in `scratch/` when it is not part of
   an existing project.
9. Review expected errors.
10. Test the rule in Autodesk Inventor.
11. Document important assumptions.
12. Decide whether the result contains reusable knowledge.
13. Preserve the result only if it has ongoing value.

A temporary iLogic rule does not need to be permanently stored.

---

# 18. Assembly Workflow

For Assembly tasks:

1. Confirm `AssemblyDocument`.
2. Obtain `AssemblyComponentDefinition`.
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

# 19. Parameter Workflow

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

# 20. Unit-Sensitive Workflow

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

Never silently assume millimeters, inches, degrees, or another unit.

---

# 21. Add-in Development Workflow

For a new .NET Inventor Add-in:

1. Establish Inventor version.
2. Establish .NET version.
3. Determine the target language.
4. Check `knowledge/addins.md`.
5. Check `knowledge/api-compatibility.md`.
6. Check `templates/addin/` for an appropriate starting point.
7. Check `tested/` for relevant verified API patterns.
8. Create the actual project under `addins/`.
9. Do not modify the template to solve project-specific problems.
10. Prepare the Visual Studio solution and project files.
11. Configure the required Inventor Interop references.
12. Implement the Add-in lifecycle.
13. Implement commands.
14. Implement UI where required.
15. Implement events where required.
16. Implement business logic.
17. Implement cleanup and lifecycle handling.
18. Review error handling.
19. Review version compatibility.
20. Build the Add-in in Visual Studio.
21. Test the Add-in inside Autodesk Inventor.
22. Use files from `cadfiles/` for safe CAD testing.
23. Fix and retest until the required functionality is verified.
24. Keep the complete Add-in in `addins/`.
25. Extract reusable verified patterns into `tested/` when appropriate.

### Important

Cline may create and modify Add-in source code and project files.

Cline should not claim that an Add-in:

- builds;
- loads;
- works;
- is compatible;
- has been tested;

unless that result has actually been verified.

A successful code-generation step is not equivalent to a successful build.

A successful build is not equivalent to a successful Inventor runtime test.

---

# 22. Testing

Testing must happen in the appropriate runtime environment.

## iLogic

Test inside Autodesk Inventor using a disposable or appropriate
test document.

Use files from:

    cadfiles/

when a CAD document is required.

Temporary rule code should normally be kept in:

    scratch/

until its status and future value are known.

## .NET Add-ins

Build in Visual Studio and test the resulting Add-in inside
Autodesk Inventor.

Use files from:

    cadfiles/

for safe CAD testing.

The complete Add-in project belongs in:

    addins/

---

## Testing Status

Always distinguish between:

    Generated
        Code has been created but not tested.

    Built
        The project successfully compiled.

    Runtime Tested
        The code has actually executed in Inventor.

    Verified
        The required behavior has been tested and confirmed.

Do not use "verified" when only code generation or compilation
has occurred.

---

# 23. Test Results

When a task has been tested, record where useful:

- Inventor version;
- programming environment;
- project type;
- document type;
- relevant input;
- expected result;
- actual result;
- limitations;
- important assumptions.

Not every small experiment requires a permanent test record.

Create a record when the result provides reusable information.

---

# 24. Tested Directory

The `tested/` directory is a library of verified, reusable patterns.

It is not:

- a staging area;
- a backup directory;
- a copy of `addins/`;
- a location for every successful experiment;
- a replacement for the active project.

Use `tested/` for:

- verified API usage;
- small reusable code patterns;
- proven iLogic techniques;
- proven parameter techniques;
- proven assembly techniques;
- documented Inventor behavior.

When a complete Add-in is successfully tested, keep the actual Add-in
in `addins/`.

Do not copy the complete Add-in into `tested/`.

If the Add-in reveals a reusable API or implementation pattern,
extract only that pattern into `tested/`.

---

# 25. Add-ins Directory

The `addins/` directory contains actual Inventor .NET Add-in projects.

A project should be placed in `addins/` when it is being developed
as an actual Add-in project rather than as a temporary experiment.

The project remains in `addins/` after successful verification.

`addins/` is the authoritative location for the complete Add-in source.

Do not maintain a second copy of the same Add-in in `tested/`.

---

# 26. Templates

The `templates/` directory contains starting points for new projects.

For a new Add-in:

    templates/addin/
        ->
    addins/MyAddin/

The template itself should remain unchanged during normal project
development.

Project-specific changes belong in the new project.

If a change improves the template for future projects:

1. Evaluate the change separately.
2. Update the template.
3. Build the template.
4. Test the template in the appropriate environment.
5. Treat the updated template as verified only after testing.

---

# 27. Updating the Workspace

When new work or information is created, determine what type of
material it is before storing it.

## Active Add-in Project

Store in:

    addins/

Use this for actual .NET Inventor Add-in projects.

## Temporary Experimental Work

Store in:

    scratch/

Use this for temporary code and files that are being developed,
tested, or manually transferred into Inventor.

Scratch content is not considered verified.

## Tested Implementation

Store in:

    tested/

Use this for small, reusable implementations or API patterns that
have actually been verified.

Do not automatically copy every successful experiment here.

## General Technical Knowledge

Store in:

    knowledge/

Use this for reusable technical knowledge about Inventor and its API.

## New AI Behavior Rule

Store in:

    .clinerules/

Use this only for instructions about how the AI should work.

If a debugging experience changes how the AI should behave in future
tasks, it may justify a `.clinerules` update.

## Reusable Demonstration

Store in:

    examples/

Use this for examples that demonstrate an implementation technique.

Examples do not automatically imply that the code has been verified.

## External Source Material

Store in:

    reference/

Use this for original external documentation, training material,
repositories, or other source material.

## CAD Test Files

Store in:

    cadfiles/

Use this only for disposable Inventor test documents.

Do not use production CAD files for experimental testing.

---

# 28. Avoid Duplication

Do not copy the same information into multiple directories without
a clear reason.

Use the following principle:

    .clinerules/
    How the AI should work

    knowledge/
    What the AI should know

    reference/
    Where information came from

    examples/
    How something can be implemented

    templates/
    How to start something new

    scratch/
    Temporary experimental work

    tested/
    What has been verified to work

    addins/
    Actual Add-in projects

    cadfiles/
    Where it is safe to experiment with CAD files

When information belongs in only one location, prefer a reference to
that location rather than duplicating the content.

---

# 29. Completion Checklist

Before considering a task complete:

- [ ] Requirement understood
- [ ] Programming context identified
- [ ] Inventor version identified
- [ ] Document context identified
- [ ] Relevant knowledge checked
- [ ] Existing tested patterns checked
- [ ] Unfamiliar API members verified
- [ ] Units checked
- [ ] Error handling reviewed
- [ ] Version compatibility reviewed
- [ ] Performance considered where relevant
- [ ] Existing code preserved where appropriate
- [ ] Appropriate runtime test performed
- [ ] Testing status clearly stated
- [ ] Result stored in the appropriate location
- [ ] No unnecessary duplication created

---

# 30. Core Principles

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

The AI should prefer:

    Small solution
        >
    Unnecessary architecture

The AI should prefer:

    One authoritative project location
        >
    Duplicate project copies

The AI should prefer:

    Explicit verification
        >
    Assumptions

The AI should prefer:

    Temporary experiment in scratch/
        >
    Prematurely creating a permanent project

When uncertain:

- Verify first.
- Do not guess.
- State uncertainty when verification is not possible.
- Do not claim testing that did not occur.
