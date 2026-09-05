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

// {246084E3-F374-11D3-853D-0060B0F0B5B7}
DEFINE_GUID (CLSID_Translator, 
0x246084E3, 0xF374, 0x11D3, 0x85, 0x3D, 0x00, 0x60, 0xB0, 0xF0, 0xB5, 0xB7);

#define CLSID_Translator_RegGUID _T("246084E3-F374-11D3-853D-0060B0F0B5B7")
#define CLSID_Translator_Name _T("TranslatorSample")
#define CLSID_Translator_Descr _T("A simple translator sample addin.")

#endif
