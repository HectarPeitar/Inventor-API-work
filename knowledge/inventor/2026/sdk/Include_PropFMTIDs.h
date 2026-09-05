/*
  Copyright © 1998 by Autodesk, Inc.


  DESCRIPTION

  This file contains the definitions of FMTIDs that correspond to the various Property Sets
  found in an Inventor file. Along with the format ID, you would also find the strings that
  are the names of each of the Property Sets. These Property Sets can be accessed by their names
  as well.


  NOTE

  An "_Microsoft" has been added at the end of the symbolic name for each of the Property Set FMTIDs
  that correspond to Microsoft Office standard property sets. This is to avoid any name clashes
  that might occur with system include files. The FMTID values are identical to those defined
  in those header files. In addition, Inventor publishes names for each of these as well
  for easier access to such Property Sets. All Inventor properties are appended with an
  "_Inventor". 

  Access to File Properties will NOT be supported reliably through the Microsoft-defined COM interfaces
  such as IPropertySetStorage, etc. Access to them should be obtained ONLY through the API (either using
  the Autodesk Inventor's ApprenticeServer or Autodesk Inventor itself).


  INTERNAL IMPLEMENTATION DETAIL

  Though, the Microsoft defined Property Set definitions (FMTIDs and PROPIDs) are used, starting from 
  this Release (release 6), these property sets are created 'manually' by Inventor as new property sets 
  which are UNICODE-based. This path was chosen to alleviate the difficulty with moving the automatically-generated,
  Microsoft's code-page based property sets across locales and languages. As such, internally, these 
  active property sets end up having different FMTIDs, but the API maps accordingly to give you, 
  the client, a transparent and compatible feel as if you were accessing the Microsoft property sets 
  the same way as you did in previous releases.


  HISTORY

  SS  :  01/11/00  :  Creation
  SS  :  07/24/02  :  Modified to reflect new state of File Properties in Autodesk Inventor R6.
*/

#ifndef _AUTODESK_INVENTOR_PROPFMTIDS_
#define _AUTODESK_INVENTOR_PROPFMTIDS_

#include <objbase.h>


// Summary Information (Microsoft Office standard)

// {F29F85E0-4FF9-1068-AB91-08002B27B3D9}
DEFINE_GUID(FMTID_SummaryInformation_Microsoft, 
0xF29F85E0, 0x4FF9, 0x1068, 0xAB, 0x91, 0x08, 0x00, 0x2B, 0x27, 0xB3, 0xD9);

#define FMTID_SummaryInformation_RegGUID "F29F85E0-4FF9-1068-AB91-08002B27B3D9"
#define FMTID_SummaryInformation_Name L"Summary Information"


// Document Summary Information (Microsoft Office standard)

// {D5CDD502-2E9C-101B-9397-08002B2CF9AE}
DEFINE_GUID(FMTID_DocumentSummaryInformation_Microsoft,
0xD5CDD502, 0x2E9C, 0x101B, 0x93, 0x97, 0x08, 0x00, 0x2B, 0x2C, 0xF9, 0xAE);

#define FMTID_DocumentSummaryInformation_RegGUID "D5CDD502-2E9C-101B-9397-08002B2CF9AE"
#define FMTID_DocumentSummaryInformation_Name L"Document Summary Information"


// User Defined Properties (Microsoft Office standard)

// {D5CDD505-2E9C-101B-9397-08002B2CF9AE}
DEFINE_GUID(FMTID_UserDefinedProperties_Microsoft,
0xD5CDD505, 0x2E9C, 0x101B, 0x93, 0x97, 0x08, 0x00, 0x2B, 0x2C, 0xF9, 0xAE);

#define FMTID_UserDefinedProperties_RegGUID "D5CDD505-2E9C-101B-9397-08002B2CF9AE"
#define FMTID_UserDefinedProperties_Name L"User Defined Properties"


// Design Tracking Properties (Autodesk Inventor)

// {32853F0F-3444-11d1-9E93-0060B03C1CA6}
DEFINE_GUID(FMTID_DesignTrackingProperties_Inventor,
0x32853F0F, 0x3444, 0x11d1, 0x9E, 0x93, 0x00, 0x60, 0xB0, 0x3C, 0x1C, 0xA6);

#define FMTID_DesignTrackingProperties_RegGUID "32853F0F-3444-11d1-9E93-0060B03C1CA6"
#define FMTID_DesignTrackingProperties_Name L"Design Tracking Properties"


// Content Library Component Properties (Autodesk Inventor)
// {B9600981-DEE8-4547-8D7C-E525B3A1727A}
DEFINE_GUID(FMTID_ContentLibrary_Inventor, 
0xb9600981, 0xdee8, 0x4547, 0x8d, 0x7c, 0xe5, 0x25, 0xb3, 0xa1, 0x72, 0x7a);

#define FMTID_ContentLibraryComponentProperties_RegGUID "B9600981-DEE8-4547-8D7C-E525B3A1727A"
#define FMTID_ContentLibraryComponentProperties_Name L"Content Library Component Properties"

DEFINE_GUID(FMTID_ContentPart_Inventor, 
0xF73AD5E7, 0xC24C, 0x44F0, 0xB2, 0x77, 0x0F, 0x9A, 0x5A, 0xA3, 0xC3, 0x5B);

#endif
