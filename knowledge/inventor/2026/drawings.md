# Inventor 2026 Drawings — SDK Interpretation

## Source Relationship

| Field | Value |
|---|---|
| **Inventor Version** | 2026 |
| **This File** | CURATED SOURCE — SDK-aware interpretation |
| **SDK Reference** | `Samples_VBNET_AddIns_SDV_*` |

**Important:** This file interprets the SDK for drawing work. The SDK has limited drawing samples; the SDV sample is the primary reference.

---

## SDK Evidence

### SimpleDrawingViews (VB.NET Add-in)

`Samples_VBNET_AddIns_SDV_ScanViewsForm.vb` and `Samples_VBNET_AddIns_SDV_StandardAddInServer.vb`

Verified object path:

```
DrawingDocument
└── Sheets → Sheets
    └── Sheet
        ├── Name
        └── DrawingViews → DrawingViews
            └── DrawingView
                ├── Name
                ├── Center (Point2d: .X, .Y)
                ├── Left / Top
                ├── Height / Width
                └── Scale
```

- Document-type detection for drawings uses `Document.DocumentType = DocumentTypeEnum.kDrawingDocumentObject`.

---

## Drawing Document Type

```
DrawingDocument      [SDK]
```

DocumentTypeEnum value: `kDrawingDocumentObject` `[SDK]` (confirmed in SDV sample).

**iLogic note:** `DocumentTypeEnum` is not available in iLogic rule code — detect drawing context via `TryCast(doc, DrawingDocument)` / Try/Catch patterns. See `knowledge/errors/ilogic/iLogic-Missing-Api-Members.md`.

---

## Known Drawing API Areas (not deeply covered by local SDK samples)

- Dimension/annotation creation
- Parts lists and balloons
- Retained/derived drawing views
- Sheet formatting

These are `[CURATED]` topics from the conceptual object model (`knowledge/object-model.md` section 14). Verify exact members against official Autodesk documentation or runtime testing.

---

## Task Path

```
KNOWLEDGE-MAP.md → drawings → SDV SDK sample → implementation
```

---

## Related Files

- `knowledge/inventor/2026/object-model.md` — Object hierarchy (drawings section)
- `knowledge/object-model.md` — Existing conceptual object model
- `knowledge/inventor/2026/sdk/Samples_VBNET_AddIns_SDV_*` — RAW SOURCE sample