# Inventor 2026 Assemblies — SDK Interpretation

## Source Relationship

| Field | Value |
|---|---|
| **Inventor Version** | 2026 |
| **This File** | CURATED SOURCE — SDK-aware interpretation |
| **General Concepts** | See `knowledge/assemblies.md` |
| **SDK Reference** | `Samples_VBNET_STDAPP_AS_AssemblyTree_*`, `Samples_VBNET_STDAPP_Inv_Bolts_*`, `Samples_VBNET_STDAPP_INV_OA_*`, `Samples_VC_AddIns_iMate_*` |

**Important:** This file interprets the SDK for assembly work. It is not a replacement for `knowledge/assemblies.md` or the SDK samples.

---

## SDK Evidence — Verified Assembly Object Paths

### AssemblyTree Sample (VB.NET Standard App)

`Samples_VBNET_STDAPP_AS_AssemblyTree_AssemblyTree.vb`

Verified object path and members:

```
AssemblyDocument (via ApprenticeServerDocument)
└── ComponentDefinition.Occurrences → ComponentOccurrences
    └── ComponentOccurrence
        ├── Name
        ├── Suppressed (Boolean)
        ├── DefinitionDocumentType (= DocumentTypeEnum.kAssemblyDocumentObject)
        └── SubOccurrences (recursive)
```

Reference traversal (documents and files):

```
ApprenticeServerDocument
├── File.FullFileName, File.AllReferencedFiles, File.ReferencedFileDescriptors
├── FullDocumentName, DisplayName
├── ReferencedDocumentDescriptors (→ DocumentDescriptor)
└── AllReferencedDocuments
```

### AutoBolts Sample (VB.NET Standard App)

`Samples_VBNET_STDAPP_Inv_Bolts_ReadMe.txt`

- Comprehensive assembly/part workflow: traverse assembly tree, query component B-Rep for holes, size bolts from parameters, create and place occurrences, attach dynamic attributes, create assembly constraints (Insert).

### OverlayAssembly Sample (VB.NET Standard App)

`Samples_VBNET_STDAPP_INV_OA_ReadMe.txt`

- Positional representations: create an overlay assembly from multiple positional representations of a source assembly, ground occurrences, mark as reference, exclude from BOM.

### iMate Sample (C++ Add-in)

`Samples_VC_AddIns_iMate_Readme.txt`

- iMate definitions and constraint creation from iMates; three scenarios: place-using-iMates, constraint-from-iMate-definitions, constraint-from-iMate-and-entity.

---

## Assembly Concepts (from SDK evidence)

1. **Occurrence vs Definition** — a `ComponentOccurrence` is an instance; the underlying definition is referenced via the occurrence. `[CURATED; see knowledge/assemblies.md]`
2. **Recursive traversal** — nested assemblies use `SubOccurrences`. Do not assume all occurrences are leaf parts. `[SDK]`
3. **Suppressed components** — check `ComponentOccurrence.Suppressed` before operating. `[SDK]`
4. **Proxy objects** — when geometry/features of referenced parts are accessed through the assembly context, proxy objects may be required. `[CURATED; see knowledge/assemblies.md]`
5. **Referenced document state** — references may be missing, unresolved, or unloaded. `[SDK]`

---

## iLogic Notes (Inventor 2026)

- Assembly traversal patterns from the SDK samples translate conceptually to iLogic; the object model is the same.
- `DocumentTypeEnum` cannot be used in iLogic for document-type detection — cast `ComponentDefinition` to `AssemblyComponentDefinition` in Try/Catch.

---

## Task Path

```
KNOWLEDGE-MAP.md → assemblies → AssemblyTree SDK sample → object model → implementation
```

---

## Related Files

- `knowledge/assemblies.md` — General assembly concepts
- `knowledge/inventor/2026/object-model.md` — Object hierarchy
- `knowledge/inventor/2026/sdk/Samples_VBNET_STDAPP_AS_AssemblyTree_*` — RAW SOURCE sample
- `knowledge/inventor/2026/sdk/Samples_VBNET_STDAPP_Inv_Bolts_*` — RAW SOURCE sample