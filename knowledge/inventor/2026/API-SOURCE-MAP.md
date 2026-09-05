# Inventor 2026 API Source Map

## Purpose

This file maps development topics to actual local SDK sources.

For each topic, it identifies the best available local source(s) from the Inventor 2026 SDK.

**Important:** SDK samples are reference material. Do not assume code from one environment (C++, VB.NET, C#) is directly valid in another (especially iLogic).

---

## Source Relationship

| Type | Description |
|---|---|
| `RAW SOURCE` | Original Autodesk SDK file |
| `CURATED SOURCE` | This file (AI-friendly mapping) |

This file is a curated interpretation. Consult original SDK sources for verification.

---

## Core API Objects

### Application

| Source | Path | Type | Notes |
|---|---|---|---|
| Object Model PDF | `Docs_InventorObjectModel.pdf` | RAW SOURCE | Authoritative object model diagram |
| Curated Object Model | `knowledge/inventor/2026/object-model.md` | CURATED SOURCE | AI-friendly navigation aid |
| SimpleExe (VB.NET) | `Samples_VBNET_STDAPP_Inv_SimpleExe_*` | RAW SOURCE | External connection to Inventor |
| SimpleExe (C#) | `Samples_VCSharp_STDAPP_INV_SimpleExe_*` | RAW SOURCE | External connection to Inventor |
| SimpleExe (C++) | `Samples_VC_STD_Inv_SimpleExe_*` | RAW SOURCE | External connection to Inventor |

### Documents

| Source | Path | Type | Notes |
|---|---|---|---|
| Object Model PDF | `Docs_InventorObjectModel.pdf` | RAW SOURCE | Document hierarchy |
| AssemblyTree (VB.NET) | `Samples_VBNET_STDAPP_AS_AssemblyTree_*` | RAW SOURCE | Assembly document traversal |
| AssemblyTree (Apprentice) | `Samples_VC_STD_ApprenticeServer_AssemblyTree_*` | RAW SOURCE | Assembly traversal via Apprentice |

### Parts

| Source | Path | Type | Notes |
|---|---|---|---|
| Object Model PDF | `Docs_InventorObjectModel.pdf` | RAW SOURCE | Part document structure |
| Pulley Sample | `Samples_VNET_STDAPP_Inv_Pulley_*` | RAW SOURCE | Parameter modification in parts |
| BRep Traversal (C++) | `Samples_VC_STD_ApprenticeServer_BRepTraversal_*` | RAW SOURCE | Part geometry traversal |

### PartComponentDefinition

| Source | Path | Type | Notes |
|---|---|---|---|
| Object Model PDF | `Docs_InventorObjectModel.pdf` | RAW SOURCE | Component definition hierarchy |
| SweepFeature (C++) | `Samples_VC_AddIns_SweepFeature_*` | RAW SOURCE | Feature creation in parts |
| ThreadFeature (C++) | `Samples_VC_AddIns_ThreadFeature_*` | RAW SOURCE | Thread feature creation/edit |
| PartFeaturesAddin (VB.NET) | `Samples_VBNET_AddIns_PFA_*` | RAW SOURCE | Part feature creation |

### Assemblies

| Source | Path | Type | Notes |
|---|---|---|---|
| Object Model PDF | `Docs_InventorObjectModel.pdf` | RAW SOURCE | Assembly document structure |
| AssemblyTree (VB.NET) | `Samples_VBNET_STDAPP_AS_AssemblyTree_*` | RAW SOURCE | Assembly occurrence traversal |
| AutoBolts (VB.NET) | `Samples_VBNET_STDAPP_Inv_Bolts_*` | RAW SOURCE | Assembly traversal, parameter modification, occurrence placement |
| OverlayAssembly (VB.NET) | `Samples_VBNET_STDAPP_INV_OA_*` | RAW SOURCE | Positional representations |
| iMate (C++) | `Samples_VC_AddIns_iMate_*` | RAW SOURCE | iMate constraints |

### ComponentOccurrences

| Source | Path | Type | Notes |
|---|---|---|---|
| Object Model PDF | `Docs_InventorObjectModel.pdf` | RAW SOURCE | Occurrence relationships |
| AssemblyTree (VB.NET) | `Samples_VBNET_STDAPP_AS_AssemblyTree_*` | RAW SOURCE | Occurrence traversal |
| AutoBolts (VB.NET) | `Samples_VBNET_STDAPP_Inv_Bolts_*` | RAW SOURCE | Occurrence placement |

### Proxies

---

## Parameters and Units

### Parameters

| Source | Path | Type | Notes |
|---|---|---|---|
| UOM Sample (VB.NET) | `Samples_VBNET_STDAPP_Inv_UOM_*` | RAW SOURCE | Parameter expressions, units |
| Pulley Sample | `Samples_VNET_STDAPP_Inv_Pulley_*` | RAW SOURCE | Parameter modification |
| AutoBolts (VB.NET) | `Samples_VBNET_STDAPP_Inv_Bolts_*` | RAW SOURCE | Parameter modification in context |
| `knowledge/parameters.md` | Existing knowledge | CURATED SOURCE | Parameter concepts |

### User Parameters

| Source | Path | Type | Notes |
|---|---|---|---|
| UOM Sample (VB.NET) | `Samples_VBNET_STDAPP_Inv_UOM_*` | RAW SOURCE | User parameter handling |

### Units of Measure

| Source | Path | Type | Notes |
|---|---|---|---|
| UOM Sample (VB.NET) | `Samples_VBNET_STDAPP_Inv_UOM_*` | RAW SOURCE | Units of Measure API, unit conversion |
| `knowledge/units.md` | Existing knowledge | CURATED SOURCE | Unit handling concepts |

---

## Properties and Attributes

### iProperties / PropertySets

| Source | Path | Type | Notes |
|---|---|---|---|
| Properties (VB.NET) | `Samples_VBNET_STDAPP_AS_Prop_*` | RAW SOURCE | Property access via Apprentice Server |
| `knowledge/errors/ilogic/ilogic-iproperties-api-limitations.md` | Error knowledge | CURATED SOURCE | iLogic iProperties limitations |
| `tested/ilogic/property-access-via-propertysets.md` | Tested pattern | CURATED SOURCE | Verified iProperty access pattern |

### Attributes

| Source | Path | Type | Notes |
|---|---|---|---|
| Attributes (VB.NET) | `Samples_VBNET_STDAPP_INV_Attr_*` | RAW SOURCE | Attribute creation, query, save, delete |
| AutoBolts (VB.NET) | `Samples_VBNET_STDAPP_Inv_Bolts_*` | RAW SOURCE | Dynamic attributes |

---

## Features and Geometry

### Features

| Source | Path | Type | Notes |
|---|---|---|---|
| SweepFeature (C++) | `Samples_VC_AddIns_SweepFeature_*` | RAW SOURCE | Sweep feature creation |
| ThreadFeature (C++) | `Samples_VC_AddIns_ThreadFeature_*` | RAW SOURCE | Thread feature creation/edit |
| PartFeaturesAddin (VB.NET) | `Samples_VBNET_AddIns_PFA_*` | RAW SOURCE | Part feature creation in Add-in |
| iFeature (C++) | `Samples_VC_AddIns_iFeature_*` | RAW SOURCE | iFeature placement |
| LoftWithRailings (C++) | `Samples_VC_AddIns_lWR_*` | RAW SOURCE | Loft feature with railings |
| `tested/ilogic/feature-suppression.md` | Tested pattern | CURATED SOURCE | Feature suppression in iLogic |

### Client Graphics

| Source | Path | Type | Notes |
|---|---|---|---|
| ClientGraphics (C++) | `Samples_VC_ADDIN_CG_*` | RAW SOURCE | Custom graphics API |
| TextClientGraphics (VB.NET) | `Samples_VBNET_AddIns_TCG_*` | RAW SOURCE | Text graphics |
| CustomGraphics (VB.NET) | `Samples_VBNET_STDAPP_Inv_CusGrap_*` | RAW SOURCE | Custom graphics visualization |

---

## Events and UI

### Events

| Source | Path | Type | Notes |
|---|---|---|---|
| EventAddIn (C++) | `Samples_VC_AddIns_EventAddIn_*` | RAW SOURCE | Selection and interaction events |
| EventWatcher (VB.NET) | `Tools_EventWatcher_*` | RAW SOURCE | Event monitoring tool |
| AtlWizEvents Templates | `WIZ_INV_AtlWiz17Evts_*` | RAW SOURCE | Event sink class templates |

### UI / Ribbon

| Source | Path | Type | Notes |
|---|---|---|---|
| CustomUI (C++) | `Samples_VC_ADDIN_CustomUI_*` | RAW SOURCE | UI customization, ribbon tabs/panels |
| CustomCommand (VB.NET) | `Samples_VBNET_AddIns_CC_*` | RAW SOURCE | Custom command implementation |
| CustomCommand (C++) | `Samples_VC_ADDIN_CusCmd_*` | RAW SOURCE | Custom command implementation |
| CustomCommand (C#) | `Samples_VCSharp_AddIns_CusCmd_*` | RAW SOURCE | Custom command implementation |

### Interaction

| Source | Path | Type | Notes |
|---|---|---|---|
| UserInteraction (VB.NET) | `Samples_VBNET_STDAPP_Inv_UI_*` | RAW SOURCE | InteractionEvents API |

---

## Advanced Topics

### Translators

| Source | Path | Type | Notes |
|---|---|---|---|
| Translator (C++) | `Samples_VC_AddIns_Translator_*` | RAW SOURCE | File translator API |

### Apprentice Server

| Source | Path | Type | Notes |
|---|---|---|---|
| AssemblyTree (C++) | `Samples_VC_STD_ApprenticeServer_AssemblyTree_*` | RAW SOURCE | Assembly traversal via Apprentice |
| BRep Traversal (C++) | `Samples_VC_STD_ApprenticeServer_BRepTraversal_*` | RAW SOURCE | B-Rep traversal via Apprentice |
| CurvatureApp (C++) | `Samples_VC_STD_ApprenticeServer_CurvatureApp_*` | RAW SOURCE | Curvature analysis via Apprentice |
| FileRefTree (C++) | `Samples_VC_STD_ApprenticeServer_FileRefTree_*` | RAW SOURCE | Document reference traversal |
| Properties (VB.NET) | `Samples_VBNET_STDAPP_AS_Prop_*` | RAW SOURCE | Property access via Apprentice |

### Add-ins

| Source | Path | Type | Notes |
|---|---|---|---|
| SimpleAddIn (VB.NET) | `Samples_VBNET_AddIns_SA_*` | RAW SOURCE | Minimal Add-in implementation |
| SimpleAddIn (C++) | `Samples_VC_AddIns_SimpleAddIn_*` | RAW SOURCE | Minimal Add-in implementation |
| SimpleAddIn (C#) | `Samples_VCSharp_AddIns_SimpleAddIn_*` | RAW SOURCE | Minimal Add-in implementation |
| Analyze (VB.NET) | `Samples_VBNET_AddIns_Analyze_*` | RAW SOURCE | Browser customization, client graphics |
| VS Templates | `VS15USRPRJTEMPLDIR_*`, `VS16USRPRJTEMPLDIR_*`, `VS17USRPRJTEMPLDIR_*` | RAW SOURCE | Add-in project templates |
| AppWiz Templates | `WIZ_INV_InvAppWiz17_*` | RAW SOURCE | Add-in wizard templates |

### iParts

| Source | Path | Type | Notes |
|---|---|---|---|
| iPart (VB.NET) | `Samples_VBNET_STDAPP_Inv_iPart_*` | RAW SOURCE | iPart factory, member update |
| iPart (C++) | `Samples_VC_AddIns_iPart_*` | RAW SOURCE | Loft feature (iPart sample) |

---

## When to Consult Original Sources

- When exact API signatures or parameters are required
- When the mapping above does not provide enough detail
- When visual relationships matter (use ObjectModel.pdf directly)
- When verifying that a curated representation is accurate

| Source | Path | Type | Notes |
|---|---|---|---|
| Object Model PDF | `Docs_InventorObjectModel.pdf` | RAW SOURCE | Proxy relationships |
| `knowledge/object-model.md` | Existing knowledge | CURATED SOURCE | Proxy concepts |
| `knowledge/assemblies.md` | Existing knowledge | CURATED SOURCE | Assembly proxy context |

### Drawings

| Source | Path | Type | Notes |
|---|---|---|---|
| SimpleDrawingViews (VB.NET) | `Samples_VBNET_AddIns_SDV_*` | RAW SOURCE | Drawing view access |
| IDW Viewer (C++) | `Samples_VC_STD_AS_Viewers_IDWViewer_*` | RAW SOURCE | Drawing viewer |
