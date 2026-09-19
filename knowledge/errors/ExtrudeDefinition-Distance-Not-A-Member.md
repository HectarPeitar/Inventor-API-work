# ExtrudeDefinition.Distance — Not a Member (Inventor 2026)

## Error

Late-bound iLogic would fail at runtime with:

```text
Public member 'Distance' on type 'ExtrudeDefinition' not found.
```

(not observed in a run — intercepting it before implementation, because
late-bound compiles accept the wrong name silently; see the
`Face.Loops` / `EdgeLoop.IsOuter` error in
`scratch/HE400B_Example_TestG.md`.)

## Context

- Inventor version: 2026 (Interop DLL
  `C:\Program Files\Autodesk\Inventor 2026\Bin\Public Assemblies\Autodesk.Inventor.Interop.dll`)
- Environment: iLogic / external iLogic, late-bound (`Option Strict` off)
- Document type: Part
- Object/context: reading the **depth** of a cut-extrude to decide whether
  a cut is a partial-depth cope or a through-cut
  (`scratch/dstv_exporter.vb`, drafted `IsCopeCut` helper)

## Root cause

`ExtrudeDefinition` exposes no `Distance` property. Reflection over the
interop assembly lists only these distance-related members:

```text
SetDistanceExtent              Method
SetDistanceExtentTwo           Method
SetDistanceFromFaceExtent      Method
```

Properties that do exist: `Extent`, `ExtentTwo`, `ExtentType`,
`ExtentTwoType`, `Operation`, `Profile`, `TaperAngle`, `TaperAngleTwo`,
`AffectedBodies`, `AffectedOccurrences`, `IsTwoDirectional`, `MatchShape`,
`Parent`, `Application`.

## Incorrect assumption

"A cut-extrude's depth is read from `ExtrudeDefinition.Distance` (with
`.Value`)." Plausible member naming is not evidence, and a late-bound
compile cannot catch it.

## Correct approach

Read the extent instead (all names reflection-confirmed for Inventor 2026):

- `ExtrudeDefinition.ExtentType` -> `Inventor.PartFeatureExtentEnum`,
  e.g. `kDistanceExtent` (explicit distance cut) versus
  `kThroughAllExtent` (through cut);
- `ExtrudeDefinition.Extent` -> `PartFeatureExtent`, cast to
  `Inventor.DistanceExtent` for `.Distance` (cm) and `.Direction`;
- `ExtrudeDefinition.Operation` -> `PartFeatureOperationEnum`
  (`kCutOperation`).

So a partial-depth test is
`Definition.Operation = kCutOperation AndAlso Definition.ExtentType = kDistanceExtent`,
without touching a non-existent `Distance` property and without a
hardcoded height comparison.

## Verification

Reflection on `Autodesk.Inventor.Interop.dll` (Inventor 2026), 2026-09-19,
during the DSTV cope-absorption (CA-2) design:

- `Inventor.ExtrudeDefinition` property list (above);
- `Inventor.DistanceExtent` properties = `Type, Application, Parent,
  Distance, Direction`;
- `Inventor.PartFeatureExtentEnum` names include `kDistanceExtent` and
  `kThroughAllExtent`.

## Status

VERIFIED (API member fact, Inventor 2026 interop)
