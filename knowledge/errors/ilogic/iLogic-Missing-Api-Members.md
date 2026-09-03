# iLogic Missing API Members — Inventor 2026

## Purpose

This file records API members that were **tested and confirmed unavailable** in iLogic (Autodesk Inventor 2026). These are verified negative findings — members that cannot be used in an iLogic rule even though they appear to exist in the full Inventor API.

This information should prevent the AI from repeating the same failed assumptions in future iLogic tasks.

## Status

All entries below were confirmed absent during the development and validation of the `ParameterWijzigingMetEenheden` iLogic rule (2026-09-03). The specific failures were captured during the repair loop iterations.

---

## Missing Members

### `DocumentTypeEnum` enum

**Attempted code:**

```vb
If doc.DocumentType = DocumentTypeEnum.kPartDocument Then ...
If doc.DocumentType = DocumentTypeEnum.PartDocument Then ...
```

**Result:** Enum type not found or not accessible in iLogic.

**Context:**

- Inventor version: 2026
- Environment: iLogic internal rule
- Document type: Part document
- Object: `Document`

**Root cause:** `DocumentTypeEnum` is defined in the full Inventor interop assemblies but is not exposed in the iLogic rule environment.

**Correct approach:** Use a `Try`/`Catch` around the `ComponentDefinition` cast (`PartComponentDefinition`, `AssemblyComponentDefinition`). If the document is the wrong type, the cast throws a runtime exception and the rule exits cleanly.

---

### `doc.FullName` property

**Attempted code:**

```vb
Dim path As String = doc.FullName
```

**Result:** Property not found on the iLogic-wrapped `Document` object.

**Context:**

- Inventor version: 2026
- Environment: iLogic internal rule
- Document type: Part document
- Object: `Document`

**Root cause:** The iLogic `Document` wrapper does not expose `FullName`. This is the full path to the file on disk.

**Correct approach:** Use `ThisApplication.ActiveDocument.DisplayName` for the file name without path. For the full path, additional verification is needed; the exact available property depends on the specific iLogic version.

---

### `ThisDoc.FullFileName` property

**Attempted code:**

```vb
Dim path As String = ThisDoc.FullFileName
```

**Result:** Property not found on `ThisDoc`.

**Context:**

- Inventor version: 2026
- Environment: iLogic internal rule

**Root cause:** `FullFileName` is not available on the iLogic `ThisDoc` helper object in this Inventor version.

**Correct approach:** See `doc.FullName` entry above.

---

### `UserParameter.IsLocked` property

**Attempted code:**

```vb
If widthParam.IsLocked Then ...
```

**Result:** Property not found on `UserParameter`.

**Context:**

- Inventor version: 2026
- Environment: iLogic internal rule
- Document type: Part document
- Parameter type: UserParameter

**Root cause:** `IsLocked` exists in the full Inventor API but is not exposed on the iLogic parameter wrapper.

**Correct approach:** Wrap the `Expression` or `Value` assignment in a `Try`/`Catch`. A locked or read-only parameter raises an exception, which is caught and reported to the user.

---

## Status

VERIFIED (individual entries confirmed during repair loop iterations 1–4 of the ParameterWijzigingMetEenheden task)
