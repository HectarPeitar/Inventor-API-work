# Inventor 2026 Properties (iProperties) — SDK Interpretation

## Source Relationship

| Field | Value |
|---|---|
| **Inventor Version** | 2026 |
| **This File** | CURATED SOURCE — SDK-aware interpretation |
| **SDK Reference** | `Samples_VBNET_STDAPP_AS_Prop_*` (Apprentice properties sample) |

**Important:** This file interprets the SDK for iProperty work. See `knowledge/errors/ilogic/ilogic-iproperties-api-limitations.md` for verified iLogic limitations.

---

## SDK Evidence

### Properties Sample (Apprentice Server)

`Samples_VBNET_STDAPP_AS_Prop_*` (`Samples_VBNET_STDAPP_AS_Prop_ReadMe.txt`)

- Demonstrates reading file properties of an Inventor file using Apprentice Server.
- Iterates **all property sets, properties, and their values**.
- Supports editing string-valued properties.
- Useful for understanding the full property set structure available on a document.

**iLogic note:** In iLogic, the same `doc.PropertySets` API path is available, but `iProperties.Value("Name")` is NOT valid (see limitations file).

---

## Property Access Paths

### Standard API (iLogic-compatible)

```
doc.PropertySets.Item("SetName").Item("PropertyName").Value
```

| iProperty | Property Set |
|---|---|
| Part Number | Design Tracking Properties |
| Description | Design Tracking Properties |
| Designer | Design Tracking Properties |
| Title | Summary Information |
| Subject | Summary Information |
| Author | Summary Information |

(Hardened pattern: `tested/ilogic/property-access-via-propertysets.md`)

### Material — Special Case

The Material iProperty is linked to the document's Material object. Use `compDef.Material`, NOT the "Physical Properties" property set. The Physical Properties set has a COM registration issue in Inventor 2026.

---

## Verified Limitations (Inventor 2026)

See `knowledge/errors/ilogic/ilogic-iproperties-api-limitations.md` for full detail:

1. `iProperties.Value("PropertyName")` throws a COM cast error in iLogic.
2. `PropertySets.Item("Physical Properties").Item("Material")` fails with `CO_E_CLASSSTRING` ("class not registered").
3. Correct approaches: use `doc.PropertySets` path for regular iProperties and `compDef.Material` for Material.

---

## Task Path

```
KNOWLEDGE-MAP.md → properties → Properties SDK sample → iLogic guidance → implementation
```

---

## Related Files

- `knowledge/inventor/2026/sdk/Samples_VBNET_STDAPP_AS_Prop_*` — RAW SOURCE sample
- `tested/ilogic/property-access-via-propertysets.md` — Verified pattern
- `knowledge/errors/ilogic/ilogic-iproperties-api-limitations.md` — Verified limitations
- `knowledge/inventor/2026/object-model.md` — Object hierarchy