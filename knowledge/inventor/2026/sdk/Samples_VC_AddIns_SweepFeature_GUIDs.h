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

// {2CDA1EC9-A800-4606-AA31-FCC77D8E3CA0}
DEFINE_GUID (CLSID_SweepFeature, 
0x2CDA1EC9, 0xA800, 0x4606, 0xAA, 0x31, 0xFC, 0xC7, 0x7D, 0x8E, 0x3C, 0xA0);

#define CLSID_SweepFeature_RegGUID _T("2CDA1EC9-A800-4606-AA31-FCC77D8E3CA0")
#define CLSID_SweepFeature_Name _T("SweepFeature")
#define CLSID_SweepFeature_Descr _T("Demonstrates the creation of a sweep feature using 2D & 3D sketches.")

#endif
