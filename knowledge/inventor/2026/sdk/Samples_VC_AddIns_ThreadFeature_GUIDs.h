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

// {D6C5BC20-7F20-401E-B317-60CB8380E254}
DEFINE_GUID (CLSID_ThreadFeature, 
0xD6C5BC20, 0x7F20, 0x401E, 0xB3, 0x17, 0x60, 0xCB, 0x83, 0x80, 0xE2, 0x54);

#define CLSID_ThreadFeature_RegGUID _T("D6C5BC20-7F20-401E-B317-60CB8380E254")
#define CLSID_ThreadFeature_Name _T("ThreadFeature")
#define CLSID_ThreadFeature_Descr _T("Creation and edit of Thread Feature")

#endif
