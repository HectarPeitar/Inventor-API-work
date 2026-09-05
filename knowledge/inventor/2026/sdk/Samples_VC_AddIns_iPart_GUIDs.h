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

// {8E260182-B94B-40DE-8661-DCA8E70600E0}
DEFINE_GUID (CLSID_IPart, 
0x8E260182, 0xB94B, 0x40DE, 0x86, 0x61, 0xDC, 0xA8, 0xE7, 0x06, 0x00, 0xE0);

#define CLSID_IPart_RegGUID _T("8E260182-B94B-40DE-8661-DCA8E70600E0")
#define CLSID_IPart_Name _T("iPart")
#define CLSID_IPart_Descr _T("Create iPart members")

#endif
