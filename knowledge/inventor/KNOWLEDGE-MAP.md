# Inventor Knowledge Map

## Purpose

This file is the central navigation point for all Inventor API knowledge in this workspace.

It provides the authoritative source hierarchy, subject index, and mapping from common development tasks to relevant SDK sources.

Primary target: **Autodesk Inventor 2026**

---

## SDK Location

`knowledge/inventor/2026/sdk/`

The complete Autodesk Inventor 2026 SDK is stored locally under this path.

Total files: ~1,489

---

## Source Hierarchy

For Inventor API questions, use sources in this priority order:

| Priority | Source | Description |
|---|---|---|
| 1 | Local Inventor 2026 API/source material | ObjectModel.pdf, curated object-model.md |
| 2 | Local official Autodesk SDK samples | VB.NET, C#, C++ sample code |
| 3 | Local curated Inventor knowledge | `knowledge/inventor/2026/*.md` |
| 4 | `tested/` | Verified reusable implementation patterns |
| 5 | `knowledge/errors/` | Verified negative knowledge |
| 6 | Autodesk web documentation | When local evidence is insufficient |
| 7 | General model knowledge | Last resort |

**Rule:** Do not use web search merely because a local SDK source exists.

---

## Subject Index

### Core API Objects

| Topic | Primary Source | Curated Knowledge |
|---|---|---|
| Application | ObjectModel.pdf, SimpleExe samples | `object-model.md` |
| Documents | ObjectModel.pdf, AssemblyTree samples | `object-model.md` |
| Parts | ObjectModel.pdf, Pulley sample | `object-model.md` |
| PartComponentDefinition | ObjectModel.pdf, feature samples | `features.md` |
| Assemblies | ObjectModel.pdf, AssemblyTree, AutoBolts | `assemblies.md` |
| ComponentOccurrences | ObjectModel.pdf, AssemblyTree | `assemblies.md` |
| Proxies | ObjectModel.pdf | `object-model.md` |
| Drawings | SDV sample | `drawings.md` |

### Parameters and Units

| Topic | Primary Source | Curated Knowledge |
|---|---|---|
| Parameters | UOM sample, Pulley sample | `parameters.md` |
| User Parameters | UOM sample | `parameters.md` |
| Units of Measure | UOM sample | `units.md` |

### Properties and Attributes

| Topic | Primary Source | Curated Knowledge |
|---|---|---|
| iProperties | Properties sample (Apprentice) | `properties.md` |
| PropertySets | Properties sample | `properties.md` |
| Attributes | Attributes sample | `API-SOURCE-MAP.md` |

### Features and Geometry

| Topic | Primary Source | Curated Knowledge |
|---|---|---|
| Features | SweepFeature, ThreadFeature, PFA samples | `features.md` |
| Feature suppression | `tested/ilogic/feature-suppression.md` | `features.md` |
| Client graphics | ClientGraphics sample | `API-SOURCE-MAP.md` |

### Events and UI

| Topic | Primary Source | Curated Knowledge |
|---|---|---|
| Events | EventAddIn, EventWatcher | `API-SOURCE-MAP.md` |
| UI/Ribbon | CustomUI, CustomCommand samples | `API-SOURCE-MAP.md` |
| Interaction | UserInteraction sample | `API-SOURCE-MAP.md` |

### Advanced

| Topic | Primary Source | Curated Knowledge |
|---|---|---|
| Translators | Translator sample | `API-SOURCE-MAP.md` |
| Apprentice | ApprenticeServer samples | `API-SOURCE-MAP.md` |
| Add-ins | SimpleAddIn, SA samples | `API-SOURCE-MAP.md` |
| iMate | iMate sample | `API-SOURCE-MAP.md` |
| iFeature | iFeature sample | `API-SOURCE-MAP.md` |
---

## Common Task Mapping

### Parameter Task
```
KNOWLEDGE-MAP.md → parameters → units (if required) → UOM SDK sample → tested pattern → implementation
```

### Property Task
```
KNOWLEDGE-MAP.md → properties → Properties SDK sample → iLogic guidance → implementation
```

### Assembly Task
```
KNOWLEDGE-MAP.md → assemblies → AssemblyTree SDK sample → object model → implementation
```

### Feature Task
```
KNOWLEDGE-MAP.md → features → relevant feature SDK sample → tested pattern → implementation
```

### Drawing Task
```
KNOWLEDGE-MAP.md → drawings → SDV SDK sample → implementation
```

### Event Task
```
KNOWLEDGE-MAP.md → events → EventAddIn SDK sample → implementation
```

### Add-in Task
```
KNOWLEDGE-MAP.md → add-ins → SimpleAddIn SDK sample → VS template → implementation
```

### iLogic Task
```
KNOWLEDGE-MAP.md → ilogic.md → check API transferability → relevant SDK sample (as reference) → tested pattern → implementation
```

---

## API Reference vs Sample Code

| Type | Description | Usage |
|---|---|---|
| **API Reference** | Authoritative information about the Inventor API itself (ObjectModel.pdf) | Verify object relationships, member existence |
| **Sample Code** | Autodesk-provided implementation examples | Understand API usage patterns, translate concepts |
| **Curated Knowledge** | AI-friendly derived representations | Navigation, interpretation, verified guidance |
| **Tested Patterns** | Verified reusable implementations | Direct reuse in similar contexts |

**Important:** SDK samples demonstrate the API through environments like VB.NET, C#, C++, standard applications, Add-ins, and Apprentice. Do not assume a sample written for one environment is directly valid in another (especially iLogic).

---

## PDF/DOC Source Handling

### Rules

For each PDF or document in the Inventor 2026 SDK:

1. Determine what information it contains.
2. Determine whether the information is useful for future Inventor API development.
3. Determine whether the original document is already sufficiently searchable.
4. Determine whether an AI-friendly derived representation would materially improve retrieval.
5. Keep the original Autodesk document unchanged as the authoritative source.

### Source Types

| Type | Description |
|---|---|
| `RAW SOURCE` | Original Autodesk document |
| `CURATED SOURCE` | AI-friendly derived representation |

The curated source must never silently replace the raw source.

### PDF Retrieval Sequence

```text
PDF/DOC source
    ↓
Check curated representation
    ↓
Use curated representation for normal retrieval
    ↓
Consult original document when:
- visual relationships matter;
- the curated representation is ambiguous;
- exact source verification is required;
- information may have been lost during derivation.
```

### Important

- Do not generate Markdown files for every PDF or document automatically.
- Use a derived representation only when it materially improves AI retrieval.
- Preserve all original Autodesk sources.
- Improve AI searchability without unnecessary duplicate documentation.

---

## SDK Usage Rules

### During API Verification

When an unfamiliar API member is encountered:

1. Check the Knowledge Map.
2. Check curated knowledge.
3. Check relevant local SDK source.
4. Check `knowledge/errors/`.
5. Check `tested/`.
6. Use web documentation only when local evidence is insufficient.

Do not guess API members.

### During Debugging

1. Check existing error knowledge (`knowledge/errors/`).
2. Check the local SDK for correct API usage patterns.
3. Verify the actual API/context.
4. Test the correction.
5. Record verified negative knowledge when reusable.

### Search Narrowly

Do not scan the entire SDK for every task.

Start from `KNOWLEDGE-MAP.md` → follow the most relevant source path.

---

## knowledge/errors/ Usage

- Stores **verified negative knowledge** about the Inventor API.
- Use when an API assumption fails.
- Each entry preserves context: Inventor version, environment, object type, document type, API member, failure, confirmed cause, verified alternative.
- A failed assumption must not automatically become a permanent global rule.
- Check before repeating an API assumption that previously failed.

---

## tested/ Usage

- Contains verified, reusable Autodesk Inventor implementation patterns.
- A knowledge library, not a storage location for completed functions.
- Only create entries when the result contains a genuinely reusable implementation pattern.
- Do NOT turn SDK samples into `tested/` entries.
- Re-check compatibility before reuse (Inventor version, environment, document type, object context).

---

## iLogic-Specific Source Guidance

The Inventor SDK primarily demonstrates the Inventor API through environments such as VB.NET, C#, C++, standard applications, Add-ins, and Apprentice.

Do not assume that a sample written for one environment is directly valid in iLogic.

See: `knowledge/inventor/2026/ilogic.md`

---

## Add-in-Specific Source Guidance

For .NET Add-in development, the SDK provides:

- Sample Add-in projects (VB.NET, C#, C++)
- Visual Studio templates and wizards
- Add-in manifest examples
- Event sink templates

See: `knowledge/addins.md` (general), `knowledge/inventor/2026/ilogic.md` (iLogic comparison)

---

## Related Files

- `knowledge/inventor/2026/API-SOURCE-MAP.md` — Topic-to-source mapping
- `knowledge/inventor/2026/SAMPLE-INDEX.md` — Sample index
- `knowledge/inventor/2026/ilogic.md` — iLogic SDK interpretation
- `knowledge/inventor/2026/object-model.md` — Curated object model (derived from ObjectModel.pdf)
- `knowledge/inventor/2026/parameters.md` — Curated parameter knowledge
- `knowledge/inventor/2026/properties.md` — Curated property knowledge
- `knowledge/inventor/2026/units.md` — Curated unit knowledge
- `knowledge/inventor/2026/assemblies.md` — Curated assembly knowledge
- `knowledge/inventor/2026/features.md` — Curated feature knowledge
- `knowledge/inventor/2026/drawings.md` — Curated drawing knowledge
- `knowledge/errors/` — Verified negative knowledge
- `tested/` — Verified reusable patterns

