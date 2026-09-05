# Inventor 2026 Object Model — Curated Representation

## Source Relationship

| Field | Value |
|---|---|
| **Original Source** | `knowledge/inventor/2026/sdk/Docs_InventorObjectModel.pdf` |
| **Source Type** | RAW SOURCE — Autodesk object model diagram |
| **Inventor Version** | 2026 |
| **This File** | CURATED SOURCE — AI-friendly structured representation |
| **Purpose** | Navigation and reasoning aid for the Inventor API object hierarchy |

**Important:** This file is a curated interpretation, not authoritative documentation.

**Consult the original PDF when:** visual relationships matter, this representation is ambiguous, exact source verification is required, or information may have been lost during derivation.

---

## Derivation Notes

- The original PDF is a **glyph-outlined diagram** and does not expose extractable text (`Tj`/`TJ` operators are absent).
- Relationships below are marked by evidence source:
  - `[SDK]` — confirmed from Autodesk SDK sample source code in this workspace
  - `[CURATED]` — from existing curated knowledge (`knowledge/object-model.md`, `knowledge/APInotes.md`)
  - `[PDF-UNVERIFIED]` — present in the conceptual hierarchy but not machine-verifiable from the diagram in this environment

Do not treat `[PDF-UNVERIFIED]` relationships as confirmed API facts.

---

## 1. Application and Documents

```
Application                                 [CURATED + SDK]
├── ActiveDocument                          [SDK]
├── Documents                               [SDK]
│   └── Documents.Open(path, refresh)       [SDK]
├── CommandManager                          [SDK]
│   ├── ControlDefinitions
│   │   └── AddButtonDefinition(...)        [SDK]
│   └── CommandCategories                   [SDK]
├── UserInterfaceManager                    [SDK]
│   └── CommandBars                          [SDK]
├── FileLocations (ApprenticeServer)        [SDK]
├── FileManager (ApprenticeServer)          [SDK]
└── UnitsOfMeasure                          [SDK]
```

Confirmed members (SDK samples): `Application.ActiveDocument`, `Application.Documents.Open()`, `Application.Documents`, `CommandManager.ControlDefinitions.AddButtonDefinition()`, `CommandManager.CommandCategories.Add()`, `UserInterfaceManager.CommandBars.Add()`.

---

## 2. Document Types

| Document Type | DocumentTypeEnum value | Key Object |
|---|---|---|
| Part | `kPartDocumentObject` `[PDF-UNVERIFIED]` | `PartDocument` `[SDK]` |
| Assembly | `kAssemblyDocumentObject` `[SDK]` | `AssemblyDocument` `[CURATED]` |
| Drawing | `kDrawingDocumentObject` `[SDK]` | `DrawingDocument` `[SDK]` |

- `Document.DocumentType` returns `DocumentTypeEnum`. Confirmed in SDV sample for drawings.
- `ComponentOccurrence.DefinitionDocumentType` returns `DocumentTypeEnum`. Confirmed in AssemblyTree sample.

**iLogic note:** `DocumentTypeEnum` is NOT available in iLogic rule code. See `knowledge/errors/ilogic/iLogic-Missing-Api-Members.md`.

---

## 3. Part Hierarchy

```
PartDocument                                   [SDK]
└── ComponentDefinition → PartComponentDefinition   [CURATED]
    ├── Parameters                               [CURATED]
    ├── Features                                 [CURATED + SDK]
    ├── Sketches                                 [CURATED]
    ├── WorkFeatures                             [CURATED]
    ├── B-Rep (SurfaceBody, faces, edges)        [CURATED]
    └── Material                                 [CURATED]
```

`[CURATED]` hierarchy from existing knowledge. Feature creation paths are demonstrated in the SweepFeature, ThreadFeature, PartFeaturesAddin, and iFeature samples `[SDK]`.

---

## 4. Assembly Hierarchy

```
AssemblyDocument                               [CURATED]
└── ComponentDefinition → AssemblyComponentDefinition   [SDK]
    └── Occurrences → ComponentOccurrences      [SDK]
        └── ComponentOccurrence                 [SDK]
            ├── Name                            [SDK]
            ├── Suppressed (Boolean)            [SDK]
            ├── SubOccurrences → ComponentOccurrences  [SDK]
            ├── DefinitionDocumentType          [SDK]
            └── (referenced definitions)        [CURATED]
```

Confirmed in `Samples_VBNET_STDAPP_AS_AssemblyTree_AssemblyTree.vb` via `ApprenticeServerDocument.ComponentDefinition.Occurrences` and recursive `ComponentOccurrence.SubOccurrences` traversal `[SDK]`.

---

## 5. References (Documents and Files)

```
ApprenticeServerDocument                      [SDK]
├── File → Inventor.File                      [SDK]
│   ├── FullFileName                           [SDK]
│   ├── ReferencedFileDescriptors             [SDK]
│   │   └── FileDescriptor                     [SDK]
│   │       ├── FullFileName                   [SDK]
│   │       └── ReferencedFile → File          [SDK]
│   └── AllReferencedFiles                     [SDK]
├── FullDocumentName                           [SDK]
├── DisplayName                                [SDK]
├── ReferencedDocumentDescriptors             [SDK]
│   └── DocumentDescriptor                     [SDK]
│       ├── FullDocumentName                   [SDK]
│       └── ReferencedDocument                 [SDK]
└── AllReferencedDocuments                     [SDK]
```

Confirmed in `Samples_VBNET_STDAPP_AS_AssemblyTree_AssemblyTree.vb` `[SDK]`.
---

## 6. Selection and Entities

```
Document
└── SelectSet                                   [SDK]
    └── Item(index) → selected entity           [SDK]

Entity (face, edge, vertex, feature, etc.)
└── AttributeSets                               [SDK]
    ├── Add(name) → AttributeSet                [SDK]
    ├── Item(name) → AttributeSet               [SDK]
    └── NameIsUsed(name) → Boolean              [SDK]

AttributeSet
├── Add(name, ValueTypeEnum.kStringType, value) → Attribute  [SDK]
└── Item(name) → Attribute                      [SDK]

Attribute
└── Value (read/write)                          [SDK]
```

Confirmed in `Samples_VBNET_STDAPP_INV_Attr_Attributes.vb` `[SDK]`.

---

## 7. Units of Measure

```
UnitsOfMeasure                                 [SDK]
├── AngleDisplayPrecision                       [SDK]
├── AngleUnits  (UnitsTypeEnum)                 [SDK]
├── MassUnits   (UnitsTypeEnum)                 [SDK]
├── TimeUnits   (UnitsTypeEnum)                 [SDK]
├── LengthUnits (UnitsTypeEnum)                 [CURATED]
├── ConvertUnits(value, inUnit, outUnit)        [SDK]
├── CompatibleUnits(...)                        [SDK]
├── GetDatabaseUnitsFromExpression(...)         [SDK]
└── GetStringFromValue(...)                     [CURATED + tested]
```

Confirmed in `Samples_VBNET_STDAPP_Inv_UOM_UOM.vb` `[SDK]`.

`UnitsTypeEnum` values confirmed in sample: `kDegreeAngleUnits`, `kRadianAngleUnits`, `kLbMassMassUnits`, `kSlugMassUnits`, `kGramMassUnits`, `kKilogramMassUnits`, `kSecondTimeUnits` `[SDK]`.

Internal database units (from UOM sample readme): lengths in **cm**, angles in **radians**, mass in **kg**, time in **seconds** `[SDK README]`.

---

## 8. Drawings

```
DrawingDocument                                [SDK]
└── Sheets → Sheets                            [SDK]
    └── Sheet                                  [SDK]
        ├── Name                               [SDK]
        └── DrawingViews → DrawingViews        [SDK]
            └── DrawingView                    [SDK]
                ├── Name                       [SDK]
                ├── Center (Point2d)           [SDK]
                ├── Left / Top                 [SDK]
                ├── Height / Width             [SDK]
                └── Scale                      [SDK]
```

Confirmed in `Samples_VBNET_AddIns_SDV_*` (`DrawingDocument.Sheets`, `Sheet.DrawingViews`, `DrawingView` properties) `[SDK]`.

---

## 9. Add-in / UI / Commands

```
Application
├── CommandManager                             [SDK]
│   ├── ControlDefinitions.AddButtonDefinition(name, internalName, CommandTypesEnum, guid, ...)  [SDK]
│   └── CommandCategories.Add(displayName, internalName, guid)  [SDK]
└── UserInterfaceManager                       [SDK]
    └── CommandBars.Add(...)                   [SDK]

ButtonDefinition
├── Enabled (Boolean)                          [SDK]
├── OnExecute event                            [SDK]
└── Delete()                                   [SDK]
```

Confirmed in `Samples_VBNET_AddIns_SDV_StandardAddInServer.vb` (AddButtonDefinition, CommandCategories, CommandBars, OnExecute) `[SDK]`.

---

## 10. Apprentice Server

```
ApprenticeServer (Application-like entry)      [SDK]
├── Open(fullName) → ApprenticeServerDocument  [SDK]
├── FileLocations.Workspace                    [SDK]
└── FileManager                                [SDK]
    ├── GetFullDocumentName(file, LODRep)      [SDK]
    └── GetLevelOfDetailRepresentations(file)  [SDK]
```

Confirmed in `Samples_VBNET_STDAPP_AS_AssemblyTree_AssemblyTree.vb` `[SDK]`.

---

## 11. Relationships Not Machine-Verified from the Diagram

The following conceptual groupings are carried from existing curated knowledge (`knowledge/object-model.md`, `knowledge/APInotes.md`) and should be verified against official documentation or by runtime testing when used:

- `TransientGeometry` / `TransientObjects` under Application
- `TransactionManager` under Application
- B-Rep structure (`SurfaceBody` → `FaceShell` → `Face`/`Edge`/`Vertex`)
- `Parameters` collections (Model/User parameter sub-objects)
- Proxy objects for assembly-context geometry

Consult `Docs_InventorObjectModel.pdf` directly (visually) for the authoritative diagram of these areas.

---

## Related Files

- `knowledge/inventor/2026/sdk/Docs_InventorObjectModel.pdf` — RAW SOURCE (consult for exact diagram)
- `knowledge/inventor/KNOWLEDGE-MAP.md` — Central navigation
- `knowledge/inventor/2026/API-SOURCE-MAP.md` — Topic-to-source mapping
- `knowledge/object-model.md` — Existing conceptual object model
- `knowledge/APInotes.md` — General API notes