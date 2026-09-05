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

// {F7F6732C-376D-4EAE-9F88-1E270638717E}
DEFINE_GUID (CLSID_SampleCommand, 
0xF7F6732C, 0x376D, 0x4EAE, 0x9F, 0x88, 0x1E, 0x27, 0x06, 0x38, 0x71, 0x7E);

#define CLSID_SampleCommand_RegGUID _T("F7F6732C-376D-4EAE-9F88-1E270638717E")
#define CLSID_SampleCommand_Name _T("SampleCommand")
#define CLSID_SampleCommand_Descr _T("AddIn sample that demonstrates simple command creation")

#endif
