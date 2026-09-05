# Inventor 2026 Features — SDK Interpretation

## Source Relationship

| Field | Value |
|---|---|
| **Inventor Version** | 2026 |
| **This File** | CURATED SOURCE — SDK-aware interpretation |
| **SDK Reference** | `Samples_VC_AddIns_SweepFeature_*`, `Samples_VC_AddIns_ThreadFeature_*`, `Samples_VBNET_AddIns_PFA_*`, `Samples_VC_AddIns_iFeature_*`, `Samples_VC_AddIns_lWR_*` |

**Important:** This file interprets the SDK for feature work. The SDK samples are C++/VB.NET Add-ins — treat them as reference sources, not copy/paste iLogic code.

---

## SDK Evidence

### SweepFeature (C++ Add-in)

`Samples_VC_AddIns_SweepFeature_*`

- Creates a sweep feature from a mixed 2D/3D sketch path with a workplane at the path start and a sweep profile on that plane.
- Demonstrates: sketch paths, workplanes, sweep profile, sweep feature creation.

### ThreadFeature (C++ Add-in)

`Samples_VC_AddIns_ThreadFeature_*`

- Creates a thread on a cylinder using a `ThreadInfo` object.
- Edit scenarios: (1) replace the entire `ThreadInfo` when many values change, (2) "live tear-off" for small changes.

### PartFeaturesAddin (VB.NET Add-in)

`Samples_VBNET_AddIns_PFA_*`

- Creates a bolt part feature from user input; demonstrates parameter-driven feature creation and interaction.

### iFeature (C++ Add-in)

`Samples_VC_AddIns_iFeature_*`

- Extracts an iFeature definition from an `.ide` file, positions it on a face/vertex, and creates the iFeature; also handles table-driven iFeature row selection.

### LoftWithRailings (C++ Add-in)

`Samples_VC_AddIns_lWR_*` (named `Samples_VC_AddIns_iPart_*` in file listing)

- Builds a loft feature with railings using multiple sketch ellipses, workplanes, workpoints, and sketch arcs.

---

## Feature Access Path (from object model)

```
PartDocument → PartComponentDefinition → Features → PartFeature
```

`PartFeature` members verified in iLogic (see `tested/ilogic/feature-suppression.md`):

| Member | Type | Notes |
|---|---|---|
| `Name` | String | Feature name (case-sensitive) |
| `Suppressed` | Boolean (read/write) | Suppression state |

---

## Feature Suppression (iLogic-verified)

Hardened pattern: `tested/ilogic/feature-suppression.md`

- Find features by `PartFeature.Name`.
- Set `PartFeature.Suppressed` True/False to suppress/activate.
- Wrap assignments in Try/Catch — some features are locked/read-only.
- Call `doc.Update()` after changing suppression state.

---

## Feature Health

- Feature health/state should be checked before operations. Verify the exact member against official documentation/API reference — not covered directly by the SDK samples in this workspace. `[CURATED]`

---

## iLogic Notes

- Feature **creation** logic in the SDK samples is C++/VB.NET Add-in code; translate the API concepts, not the syntax.
- Feature **suppression/activation** and **name lookup** are iLogic-verified locally.
- Assembly-context feature access on referenced parts may require proxies. `[CURATED; see knowledge/assemblies.md]`

---

## Task Path

```
KNOWLEDGE-MAP.md → features → relevant feature SDK sample → tested pattern → implementation
```

---

## Related Files

- `tested/ilogic/feature-suppression.md` — Verified suppression pattern
- `knowledge/inventor/2026/object-model.md` — Object hierarchy
- `knowledge/inventor/2026/assemblies.md` — Assembly feature context
- `knowledge/inventor/2026/sdk/Samples_VC_AddIns_SweepFeature_*` — RAW SOURCE sample
- `knowledge/inventor/2026/sdk/Samples_VC_AddIns_ThreadFeature_*` — RAW SOURCE sample