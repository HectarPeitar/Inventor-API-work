/*
  Copyright © 1998 by Autodesk, Inc.


  DESCRIPTION

  This file contains the definitions of CLSIDs that correspond to the various Servers 
  found in Inventor or associated products. Along with the GUID, you would also find the strings that
  are the PROGIDs and the displayable names of each of the Servers.


  HISTORY

  SS  :  01/11/00  :  Creation
*/

#ifndef _AUTODESK_INVENTOR_SERVERCLSIDS_
#define _AUTODESK_INVENTOR_SERVERCLSIDS_

#include <objbase.h>


// Inventor Application

// {B6B5DC40-96E3-11d2-B774-0060B0F159EF}
DEFINE_GUID(CLSID_InventorApplication, 
0xB6B5DC40, 0x96E3, 0x11d2, 0xB7, 0x74, 0x00, 0x60, 0xB0, 0xF1, 0x59, 0xEF);

#define InventorApplication_RegGUID "B6B5DC40-96E3-11d2-B774-0060B0F159EF"
#define InventorApplication_Name L"Autodesk Inventor"
#define InventorApplication_ProgId L"Inventor.Application"


// Apprentice Server

// {C343ED84-A129-11d3-B799-0060B0F159EF}
DEFINE_GUID(CLSID_ApprenticeServer,
0xC343ED84, 0xA129, 0x11d3, 0xB7, 0x99, 0x00, 0x60, 0xB0, 0xF1, 0x59, 0xEF);

#define ApprenticeServer_RegGUID "C343ED84-A129-11d3-B799-0060B0F159EF"
#define ApprenticeServer_Name L"Autodesk Inventor Apprentice Server"
#define ApprenticeServer_ProgId L"Inventor.ApprenticeServer"

#endif
