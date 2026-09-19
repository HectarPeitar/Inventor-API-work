# Inventor 2026 — Apprentice / Headless Server Not Available (this machine)

## Error

Creating the Apprentice COM server fails out-of-process:

```text
New-Object -ComObject Inventor.InventorServer
  -> Retrieving the COM class factory for component with CLSID
     {3FC94EB5-AEBD-4F3F-A2A4-B6CE57113C01} failed due to the following
     error: 8007007E (module not found)

New-Object -ComObject Inventor.ApprenticeServerComponent
New-Object -ComObject Inventor.ApprenticeServer
  -> 80040154 REGDB_E_CLASSNOTREG
```

PowerShell 7 additionally reports:

```text
[System.Runtime.InteropServices.Marshal] does not contain a method named
'GetActiveObject'.
```

## Context

- Inventor version: 2026 (full Inventor install present, Interop DLL and SDK local)
- Environment: external out-of-process COM from PowerShell 7
- Purpose: read-only B-Rep self-inspection of a part while Inventor is running

## Root cause

- The Apprentice coclass CLSID that the .NET interop exposes
  (`Inventor.ApprenticeServerComponent` = `{c343ed82-a129-11d3-b799-0060b0f159ef}`)
  and the SDK header CLSID (`{C343ED84-A129-11d3-B799-0060B0F159EF}`,
  `Include_ServerCLSIDs.h`) are **not registered** in
  `HKLM\SOFTWARE\Classes\CLSID`, `HKLM\SOFTWARE\Classes\WOW6432Node\CLSID`
  or `HKCU\SOFTWARE\Classes\CLSID`.
- `Inventor.InventorServer` *is* registered, but its server module is missing
  (`0x8007007E`) — the separate headless "Inventor Server" component is not
  installed on this machine.

## Incorrect assumption

"Apprentice is available on any machine with Inventor installed, so a part can be
inspected out-of-process from a script." Availability must be probed, not assumed.
Also, the SDK header's `CLSID_ApprenticeServer` is not the CLSID of the interop
coclass, so checking the wrong GUID can look like a missing install.

## Correct approach

- Answer B-Rep questions inside Inventor (iLogic rule or .NET Add-in) on this
  machine; do not design tooling around Apprentice here.
- Probe availability first (registry CLSID check or one `New-Object` attempt)
  before investing in a script.
- `Marshal.GetActiveObject` is absent in PowerShell 7; attaching to a running
  Inventor instance needs a P/Invoke of `oleaut32!GetActiveObject` or
  `New-Object -ComObject Inventor.Application` (which normally attaches to the
  running instance).

## Verification

Registry and `CoCreateInstance` probes, 2026-09 (during DSTV AK-2 arc
investigation). Apprentice member names were instead verified by reflection on
`Autodesk.Inventor.Interop.dll`: `ApprenticeServer.Open`, `ApprenticeServerDocument.ComponentDefinition`,
`Edge.CurveType`, `Edge.Geometry`, `Cylinder.Radius`, `LineSegment.StartPoint`.

## Status

VERIFIED (local environment fact, not a universal Inventor 2026 limitation)
