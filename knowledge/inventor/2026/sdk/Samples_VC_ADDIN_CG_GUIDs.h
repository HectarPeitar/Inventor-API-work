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

// {E985C31C-56BF-11d5-8E36-0010B547BBF8}
DEFINE_GUID(CLSID_ClientGraphics, 0xe985c31c, 0x56bf, 0x11d5, 0x8e, 0x36, 0x0, 0x10, 0xb5, 0x47, 0xbb, 0xf8);

#define CLSID_ClientGraphics_RegGUID _T("E985C31C-56BF-11d5-8E36-0010B547BBF8")
#define CLSID_ClientGraphics_Name _T("Client Graphics Sample")
#define CLSID_ClientGraphics_Descr _T("AddIn sample for Client Graphics API.")

#endif
