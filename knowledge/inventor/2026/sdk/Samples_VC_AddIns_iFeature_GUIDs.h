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

// {90E841C3-C126-45FD-A985-FDFA6BC30C37}
DEFINE_GUID (CLSID_IFeature, 
0x90E841C3, 0xC126, 0x45FD, 0xA9, 0x85, 0xFD, 0xFA, 0x6B, 0xC3, 0x0C, 0x37);

#define CLSID_IFeature_RegGUID _T("90E841C3-C126-45FD-A985-FDFA6BC30C37")
#define CLSID_IFeature_Name    _T("iFeature")
#define CLSID_IFeature_Descr   _T("Sample demonstrating iFeature API")

#endif
