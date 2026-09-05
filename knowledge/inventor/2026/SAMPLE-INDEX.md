# Inventor 2026 SDK Sample Index

## Purpose

This file indexes the most useful official Autodesk SDK samples for Inventor 2026 API development.

Each entry includes the sample name, path, language, application type, subject, and relevance to iLogic and Add-in development.

**Important:** Samples are API behavior/reference sources. Do not assume that a VB.NET or C# sample is directly usable as iLogic code.

---

## Source Relationship

| Type | Description |
|---|---|
| `RAW SOURCE` | Original Autodesk SDK sample files |
| `CURATED SOURCE` | This file (AI-friendly index) |

This file is a curated interpretation. Consult original SDK samples for exact implementation details.

---

## High-Priority Samples

### Units of Measure (UOM)

| Field | Value |
|---|---|
| **Sample Name** | Units of Measure |
| **Path** | `Samples_VBNET_STDAPP_Inv_UOM_*` |
| **Language** | VB.NET |
| **Application Type** | Standard Application (External EXE) |
| **Subject** | Units of Measure API |
| **API Concept** | Unit conversion, parameter expressions, display formatting |
| **iLogic Relevant** | Yes (concept) — demonstrates internal units (cm, radians, kg, seconds) vs display units |
| **Add-in Relevant** | Yes |
| **Limitations** | External application, not iLogic. Concepts transfer directly. |
| **Key Files** | `Samples_VBNET_STDAPP_Inv_UOM_ReadMe.txt`, `.vb` source files |

### AssemblyTree

| Field | Value |
|---|---|
| **Sample Name** | AssemblyTree |
| **Path** | `Samples_VBNET_STDAPP_AS_AssemblyTree_*` |
| **Language** | VB.NET |
| **Application Type** | Standard Application (External EXE) |
| **Subject** | Assembly traversal |
| **API Concept** | ComponentOccurrence traversal, referenced documents, level of detail |
| **iLogic Relevant** | Yes (concept) — assembly traversal patterns |
| **Add-in Relevant** | Yes |
| **Limitations** | External application. Traversal logic transfers. |
| **Key Files** | `Samples_VBNET_STDAPP_AS_AssemblyTree_ReadMe.txt`, `.vb` source files |

### Properties (Apprentice)

| Field | Value |
|---|---|
| **Sample Name** | Properties |
| **Path** | `Samples_VBNET_STDAPP_AS_Prop_*` |
| **Language** | VB.NET |
| **Application Type** | Standard Application (External EXE) |
| **Subject** | iProperties via Apprentice Server |
| **API Concept** | PropertySet/Property access, Apprentice Server document inspection |
| **iLogic Relevant** | Yes (concept) — property set structure |
| **Add-in Relevant** | Yes |
| **Limitations** | Uses Apprentice Server. In iLogic, use `doc.PropertySets` directly. |
| **Key Files** | `Samples_VBNET_STDAPP_AS_Prop_ReadMe.txt`, `.vb` source files |

### Attributes

| Field | Value |
|---|---|
| **Sample Name** | Attributes |
| **Path** | `Samples_VBNET_STDAPP_INV_Attr_*` |
| **Language** | VB.NET |
| **Application Type** | Standard Application (External EXE) |
| **Subject** | Attribute creation and query |
| **API Concept** | AttributeSet/Attribute creation, query, save, delete on entities (faces, edges, vertices) |
| **iLogic Relevant** | Yes (concept) — Attribute API |
| **Add-in Relevant** | Yes |
| **Limitations** | External application. Attribute API transfers. |
| **Key Files** | `Samples_VBNET_STDAPP_INV_Attr_ReadMe.txt`, `.vb` source files |

### AutoBolts

| Field | Value |
|---|---|
| **Sample Name** | AutoBolts |
| **Path** | `Samples_VBNET_STDAPP_Inv_Bolts_*` |
| **Language** | VB.NET |
| **Application Type** | Standard Application (External EXE) |
| **Subject** | Assembly traversal, parameter modification, occurrence placement |
| **API Concept** | B-Rep traversal, parameter modification, assembly occurrence placement, dynamic attributes |
| **iLogic Relevant** | Yes (concept) — comprehensive API demonstration |
| **Add-in Relevant** | Yes |
| **Limitations** | Complex external application. Many API concepts transfer. |
| **Key Files** | `Samples_VBNET_STDAPP_Inv_Bolts_ReadMe.txt`, `.vb` source files, `Data_Files/Base.ipt` |

### Pulley

| Field | Value |
|---|---|
| **Sample Name** | Pulley |
| **Path** | `Samples_VNET_STDAPP_Inv_Pulley_*` |
| **Language** | VBA (Excel) |
| **Application Type** | Standard Application (VBA macro) |
| **Subject** | Parameter modification in Part documents |
| **API Concept** | Parameter modification, model update, view fit |
| **iLogic Relevant** | Yes (concept) — parameter modification patterns |
| **Add-in Relevant** | Yes |
| **Limitations** | VBA in Excel. Parameter modification logic transfers. |
| **Key Files** | `Samples_VNET_STDAPP_Inv_Pulley_ReadMe.txt`, `.xls` file |

### OverlayAssembly

| Field | Value |
|---|---|
| **Sample Name** | OverlayAssembly |
| **Path** | `Samples_VBNET_STDAPP_INV_OA_*` |
| **Language** | VB.NET |
| **Application Type** | Standard Application (External EXE) |
| **Subject** | Positional representations |
| **API Concept** | Overlay assembly creation, positional representations, BOM exclusion |
| **iLogic Relevant** | Yes (concept) |
| **Add-in Relevant** | Yes |
| **Limitations** | External application. Positional representation API transfers. |

---

### SweepFeature (C++)

| Field | Value |
|---|---|
| **Sample Name** | SweepFeature |
| **Path** | `Samples_VC_AddIns_SweepFeature_*` |
| **Language** | C++ |
| **Application Type** | Inventor Add-in (DLL) |
| **Subject** | Sweep feature creation |
| **API Concept** | 2D/3D sketch path creation, workplane at path start, sweep profile, sweep feature |
| **iLogic Relevant** | Yes (concept) — sweep creation logic |
| **Add-in Relevant** | Yes |
| **Limitations** | C++ Add-in. |
| **Key Files** | `Samples_VC_AddIns_SweepFeature_ReadMe.txt`, `.cpp` source files |

### ThreadFeature (C++)

| Field | Value |
|---|---|
| **Sample Name** | ThreadFeature |
| **Path** | `Samples_VC_AddIns_ThreadFeature_*` |
| **Language** | C++ |
| **Application Type** | Inventor Add-in (DLL) |
| **Subject** | Thread feature creation |
| **API Concept** | Helix/spiral creation, thread profile, extrusion/emboss options |
| **iLogic Relevant** | Yes (concept) — thread feature creation patterns |
| **Add-in Relevant** | Yes |
| **Limitations** | C++ Add-in. Requires .ide files in some cases. |
| **Key Files** | `Samples_VC_AddIns_ThreadFeature_ReadMe.txt`, `.cpp` source files |

### FilletFeature (C++)

| Field | Value |
|---|---|
| **Sample Name** | FilletFeature |
| **Path** | `Samples_VC_AddIns_FilletFeature_*` |
| **Language** | C++ |
| **Application Type** | Inventor Add-in (DLL) |
| **Subject** | Fillet feature creation |
| **API Concept** | Edge fillet creation, constant radius, variable radius, face fillet |
| **iLogic Relevant** | Yes (concept) — fillet creation logic |
| **Add-in Relevant** | Yes |
| **Limitations** | C++ Add-in. |
| **Key Files** | `Samples_VC_AddIns_FilletFeature_ReadMe.txt`, `.cpp` source files |

### ChamferFeature (C++)

| Field | Value |
|---|---|
| **Sample Name** | ChamferFeature |
| **Path** | `Samples_VC_AddIns_ChamferFeature_*` |
| **Language** | C++ |
| **Application Type** | Inventor Add-in (DLL) |
| **Subject** | Chamfer feature creation |
| **API Concept** | Edge chamfer creation, distance/angle chamfer, type selection |
| **iLogic Relevant** | Yes (concept) — chamfer creation logic |
| **Add-in Relevant** | Yes |
| **Limitations** | C++ Add-in. |
| **Key Files** | `Samples_VC_AddIns_ChamferFeature_ReadMe.txt`, `.cpp` source files |

## Add-in Samples

### SimpleAddIn (VB.NET)

| Field | Value |
|---|---|
| **Sample Name** | SimpleAddIn |
| **Path** | `Samples_VBNET_AddIns_SA_*` |
| **Language** | VB.NET |
| **Application Type** | Inventor Add-in (DLL) |
| **Subject** | Minimal Add-in implementation |
| **API Concept** | Add-in server, command definitions, ribbon panel |
| **iLogic Relevant** | No (Add-in only) |
| **Add-in Relevant** | Yes — primary reference for minimal Add-in |
| **Limitations** | Add-in architecture only. Not applicable to iLogic. |
| **Key Files** | `Samples_VBNET_AddIns_SA_ReadMe.txt`, `.vb` source files, `.addin` manifest |

### SimpleAddIn (C++)

| Field | Value |
|---|---|
| **Sample Name** | SimpleAddIn |
| **Path** | `Samples_VC_AddIns_SimpleAddIn_*` |
| **Language** | C++ |
| **Application Type** | Inventor Add-in (DLL) |
| **Subject** | Minimal Add-in implementation |
| **API Concept** | Add-in server, COM registration, command definitions |
| **iLogic Relevant** | No (Add-in only) |
| **Add-in Relevant** | Yes — primary reference for minimal Add-in |
| **Limitations** | Add-in architecture only. Not applicable to iLogic. |
| **Key Files** | `Samples_VC_AddIns_SimpleAddIn_ReadMe.txt`, `.cpp` source files |
### Tools and Utilities

### EventWatcher (VB.NET)

| Field | Value |
|---|---|
| **Sample Name** | EventWatcher |
| **Path** | `Tools_EventWatcher_*` |
| **Language** | VB.NET |
| **Application Type** | Inventor Add-in (DLL) |
| **Subject** | Event monitoring tool |
| **API Concept** | Comprehensive event monitoring, all Inventor event types |
| **iLogic Relevant** | No (Add-in only) |
| **Add-in Relevant** | Yes |
| **Limitations** | Add-in architecture only. Not applicable to iLogic. |
| **Key Files** | `Tools_EventWatcher_ReadMe.txt`, `.vb` source files |
| **Key Files** | `Samples_VBNET_STDAPP_INV_OA_ReadMe.txt`, `.vb` source files |
