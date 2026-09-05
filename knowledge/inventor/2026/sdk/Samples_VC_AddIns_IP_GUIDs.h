/*
  DESCRIPTION

  This file contains the definitions of various GUIDs that may be used within this
  sample.

*/

#ifndef _GUIDS_
#define _GUIDS_

#include <objbase.h>


// This GUID is the CLSID of the object that Autodesk Inventor (R) first CoCreates. It is the 
// Add-In Server object.

// {04859830-A5FA-11D3-B799-0060B0F159EF}
DEFINE_GUID (CLSID_InsertCatalogPart, 
0x04859830, 0xA5FA, 0x11D3, 0xB7, 0x99, 0x00, 0x60, 0xB0, 0xF1, 0x59, 0xEF);

#define CLSID_InsertCatalogPart_RegGUID _T("04859830-A5FA-11D3-B799-0060B0F159EF")
#define CLSID_InsertCatalogPart_Name _T("Insert SAT Catalog Part")
#define CLSID_InsertCatalogPart_Descr _T("Sample Autodesk Inventor Add-In that demonstrates a straightforward way of providing an Insert Catalog Part capability")

#endif
