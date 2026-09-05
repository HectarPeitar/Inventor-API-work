# iLogic and the Inventor 2026 SDK

## Purpose

This file explains how the local Inventor 2026 SDK should be interpreted specifically for iLogic development.

The Inventor SDK primarily demonstrates the Inventor API through environments such as VB.NET, C#, C++, standard applications, Add-ins, and Apprentice.

Do not assume that a sample written for one environment is directly valid in iLogic.

---

## Source Relationship

| Type | Description |
|---|---|
| `RAW SOURCE` | Original Autodesk SDK sample files |
| `CURATED SOURCE` | This file (AI-friendly guidance) |

This file is a curated interpretation. Consult original SDK samples for exact API behavior.

---

## Environment Differences That Matter

### iLogic vs .NET Add-ins

| Aspect | iLogic | .NET Add-in (C#/VB.NET) |
|---|---|---|
| Execution | Inside Inventor process | Can be inside or outside Inventor |
| Language | iLogic (VB.NET subset) | Full VB.NET or C# |
| Object access | `ThisApplication`, `ThisDoc` | `Application` via Add-in server |
| Type access | Limited (no `DocumentTypeEnum`) | Full Inventor interop types |
| References | Automatic (Inventor interop) | Manual (add references needed) |
| Deployment | Rule text in document or external | Compiled DLL + manifest |

### iLogic vs C++ Samples

| Aspect | iLogic | C++ |
|---|---|---|
| Memory management | Automatic (COM runtime) | Manual (COM pointers) |
| Error handling | Try/Catch | HRESULT checks |
| Object access | Direct | Via COM interfaces |
| Syntax | VB.NET-like | C++ |

### iLogic vs Apprentice

| Aspect | iLogic | Apprentice |
|---|---|---|
| Process | Inside Inventor | Outside Inventor |
| Capabilities | Full Inventor API | Limited subset (read-only mostly) |
| Documents | Can create/edit | Read-only access |

---

## API Concepts That Transfer Directly

The following Inventor API concepts from SDK samples can typically be translated to iLogic:

### Object Model Navigation

```
Application → ActiveDocument → ComponentDefinition → Parameters/Features
```

This hierarchy is consistent across all environments. SDK samples demonstrate the navigation; iLogic uses the same objects with simplified syntax.

### Parameter Access

SDK samples demonstrate:
- `Parameters.Item("Name")` — parameter lookup
- `Parameter.Value` — numeric value in internal units
- `Parameter.Expression` — string expression with units
- `Parameter.Name` — parameter name

iLogic equivalent: Same API members, but with iLogic-specific limitations (see below).

### Geometry and B-Rep

SDK samples demonstrate:
- Face/edge/vertex traversal
- Geometry queries (radius, length, area)
- B-Rep topology

iLogic: Same geometry objects accessible through `PartComponentDefinition`.

### Document Properties

SDK Properties sample demonstrates:
- `PropertySets.Item("SetName")`
- `PropertySet.Item("PropertyName")`
- `Property.Value`

iLogic: Same API path (but NOT `iProperties.Value("Name")` — see limitations).
---

## Syntax/Context Differences That Matter

### Object Access

**SDK/C#:**
```csharp
Application app = (Application)Marshal.GetActiveObject("Inventor.Application");
Document doc = app.ActiveDocument;
PartComponentDefinition compDef = (PartComponentDefinition)doc.ComponentDefinition;
```

**iLogic:**
```vb
Dim doc = ThisApplication.ActiveDocument
Dim compDef As PartComponentDefinition = doc.ComponentDefinition
```

### Parameter Value vs Expression

**SDK/C#:**
```csharp
param.Value = 25.0; // Internal units (cm)
param.Expression = "25 mm"; // User-facing with units
```

**iLogic:**
```vb
param.Value = 25.0 ' Internal units (cm) — DO NOT display directly
param.Expression = "25 mm" ' User-facing with units
```

### Unit Conversion

**SDK/C#:**
```csharp
double cmValue = uom.InternalUnits.DisplayUnits.Length...
```

**iLogic:**
```vb
Dim displayValue As String = doc.UnitsOfMeasure.GetStringFromValue(param.Value, UnitsTypeEnum.kMillimeterLengthUnits)
```

---

## Known iLogic-Specific Limitations

The following limitations were confirmed during development of iLogic rules in Autodesk Inventor 2026. See `knowledge/errors/ilogic/` for detailed documentation.

### Document Type Detection

iLogic does not expose `DocumentTypeEnum`. Do NOT use:
```vb
If doc.DocumentType = DocumentTypeEnum.kPartDocument Then ...
```

**Correct approach:** Cast `doc.ComponentDefinition` to `PartComponentDefinition` inside Try/Catch.

### Document Path Properties

`doc.FullName` and `ThisDoc.FullFileName` are not available in iLogic 2026.

**Correct approach:** Use `ThisApplication.ActiveDocument.DisplayName`.

### Parameter Lock State

`UserParameter.IsLocked` is not exposed in iLogic.

**Correct approach:** Wrap `Expression` or `Value` assignment in Try/Catch.

### iProperties API

`iProperties.Value("PropertyName")` does NOT accept a String argument in iLogic.

**Correct approach:** Use `doc.PropertySets.Item("SetName").Item("PropertyName").Value`.

### Physical Properties

The "Physical Properties" property set has COM registration issues in Inventor 2026.

**Correct approach:** For Material, use `compDef.Material` directly.

### GetStringFromValue Culture

`UnitsOfMeasure.GetStringFromValue()` returns locale-formatted strings (e.g., "500,000 mm" in Dutch).

**Correct approach:** Parse with `CultureInfo.CurrentCulture`, NOT `InvariantCulture`.
---

## How to Translate SDK Samples to iLogic

### Step-by-Step Process

1. **Identify the API concept** in the SDK sample (e.g., parameter modification)
2. **Extract the relevant API members** (e.g., `Parameter.Expression = "25 mm"`)
3. **Check for iLogic limitations** (see above and `knowledge/errors/ilogic/`)
4. **Translate syntax** to iLogic conventions
5. **Validate** in Autodesk Inventor

### Example: UOM SDK Sample → iLogic Concept

**SDK Sample (VB.NET Standard App):**
- Demonstrates: `uom.GetStringFromValue()`, `uom.GetInternalValueFromExpression()`
- iLogic translation: Same API members available
- Limitation: Culture-aware parsing required for display values

### Example: AssemblyTree SDK Sample → iLogic Concept

**SDK Sample (VB.NET Standard App):**
- Demonstrates: `AssemblyComponentDefinition.ComponentOccurrences` traversal
- iLogic translation: Same object model, simplified syntax
- Limitation: Some COM-specific code not applicable

---

## SDK Samples Useful for iLogic Reference

| Sample | Concept | iLogic Value |
|---|---|---|
| UOM | Unit handling, parameter expressions | High — direct concept transfer |
| AssemblyTree | Assembly traversal | High — object model concepts |
| Properties (Apprentice) | Property set structure | High — property access pattern |
| Attributes | Attribute API | High — attribute concepts |
| Pulley | Parameter modification | Medium — VBA syntax differs |
| AutoBolts | Comprehensive API usage | Medium — many concepts transfer |
| SweepFeature | Feature creation | Low — C++ syntax, complex |

---

## SDK Samples NOT Directly Usable in iLogic

| Sample | Reason |
|---|---|
| SimpleAddIn | Add-in architecture, command definitions |
| CustomCommand | Add-in command implementation |
| CustomUI | Ribbon/UI customization |
| ClientGraphics | Add-in graphics |
| EventAddIn | Add-in event handling |
| Translator | Add-in translator API |
| EventWatcher | Add-in tool |

These samples are useful for understanding API capabilities but require Add-in context.

---

## When to Consult SDK Samples for iLogic Tasks

1. **Parameter tasks:** Consult UOM sample for unit handling patterns
2. **Assembly tasks:** Consult AssemblyTree sample for traversal patterns
3. **Property tasks:** Consult Properties sample for property set structure
4. **Feature tasks:** Consult feature samples (SweepFeature, ThreadFeature) for creation logic
5. **Drawing tasks:** Consult SDV sample for drawing view access

---

## Related Files

- `knowledge/ilogic.md` — General iLogic knowledge (existing)
- `knowledge/errors/ilogic/` — Verified iLogic limitations
- `tested/ilogic/` — Verified iLogic patterns
- `knowledge/units.md` — Unit handling concepts
- `knowledge/parameters.md` — Parameter concepts