# iLogic Rule Compile Check (vbc + Interop Harness)

## Purpose

Compile-validate an iLogic rule **outside** Inventor before runtime testing.
Catches VB syntax errors and Inventor API type/member errors (wrong member
names, wrong signatures, missing enum members) without opening Inventor.

## Context

- Inventor version: 2026
- Environment: iLogic internal rule; check runs from PowerShell using
  `vbc.exe` (.NET Framework 4)
- Document type: any (rule-level static check, no Inventor session needed)
- Object/context: rule source only

## Implementation

Working script: `scratch/compile_check.ps1`. Pattern:

1. Wrap the rule body in `Module DstvRule` — iLogic wraps rules in a class
   internally; standalone VB requires all members inside a type.
2. Add the Imports that iLogic provides implicitly:
   `System`, `System.Collections.Generic`, `System.Windows.Forms`,
   `Inventor`.
3. Stub the iLogic implicit global:

   ```vb
   Module ILogicHost
       Public ThisApplication As Inventor.Application = Nothing
   End Module
   ```

4. Compile:

   ```
   C:\Windows\Microsoft.NET\Framework64\v4.0.30319\vbc.exe /nologo /t:library ^
     /platform:x64 /out:check.dll ^
     /r:"C:\Program Files\Autodesk\Inventor 2026\Bin\Public Assemblies\Autodesk.Inventor.Interop.dll" ^
     /r:System.Windows.Forms.dll harness.vb
   ```

## Validation

Verified 2026-09-06 during EXPORT_DSTV2 Phase 2 development:

- **Positive:** the full EXPORT_DSTV2 rule (2665 lines, DSTV NC1 exporter)
  compiled with exit code 0 against the real Inventor 2026 interop.
- **Negative:** injecting an undeclared identifier (`Return NotARealConstant`)
  produced exit code 1 with `BC30451` at every injected site — the harness
  demonstrably catches errors, it does not pass unconditionally.

## Result

VERIFIED

## Important Limitations

- **Static check only.** The `ThisApplication` stub is `Nothing`; runtime
  behavior (API calls, document state, iLogic events) is NOT validated.
  Runtime testing in Inventor is still required.
- iLogic-only globals beyond `ThisApplication` (`ThisDoc`, `iProperties`,
  `RuleArguments`, `SharedVariable`, feature-name functions such as
  `Feature.IsActive`) are NOT stubbed — rules using them need extra stub
  members in `ILogicHost`.
- `/platform:x64` is used because the interop may be x64-marked.
- Paths are machine-specific (Inventor 2026 default install location).

## Related

- `knowledge/inventor/KNOWLEDGE-MAP.md` — Inventor knowledge index
- `scratch/compile_check.ps1` — working implementation of this pattern
- `scratch/dstv_exporter.vb` — rule validated with this pattern (Phase 2)