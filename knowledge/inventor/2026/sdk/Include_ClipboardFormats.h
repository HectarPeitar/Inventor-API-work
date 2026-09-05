/*
  Copyright © 1998 by Autodesk, Inc.


  DESCRIPTION

  This file contains the possible Clipboard formats that Inventor supports in its Data Exchange
  interfaces and/or objects. The strings defined here can be used to obtain the identifier
  on this machine corresponding to a given format (using ::RegisterClipboardFormat). Some of the 
  APIs call for this identifier while others may call for the string itself.


  HISTORY

  SS  :  01/25/00  :  Creation
*/

#ifndef _AUTODESK_INVENTOR_CLIPBOARDFORMATS_
#define _AUTODESK_INVENTOR_CLIPBOARDFORMATS_

// There is also another version of this file in R:\XInterface\InventorSDK\Source\DeveloperTools\include\ClipboardFormats.h

/*------------------------- Format flavors involving ACIS --------------------------------*/

// Spatial Technology's ACIS SAT format (text-based). Primarily used to communicate BRep
// as data. No attributes are attached to the resulting entities in the data store. The
// data is always returned in centimetres.

#define ACIS_SAT "ACIS SAT"
#define LACIS_SAT L"ACIS SAT"


// Same as above, except that format is binary. User must be certain of the version compatibility
// with the ACIS being used inside Inventor. Binary formats are more compact but not very
// robust with respect to cross versions.

#define ACIS_SAB "ACIS SAB"
#define LACIS_SAB L"ACIS SAB"


// Same as ACIS SAT, except that it is now decorated with PID attributes on the Faces, Edges
// and vertices. These attributes are the 'Transient Keys' recognized by Inventor's API. Using
// these attributes as Transient Keys, a client can get different levels of associativity to
// the Faces, Edges and Vertices.

#define ACIS_SAT_with_TransientKeys "ACIS SAT with TransientKeys"
#define LACIS_SAT_with_TransientKeys L"ACIS SAT with TransientKeys"


// Same as ACIS SAT with Transient Keys, except that it is in binary format.
// Knowing compatibility of Client's ACIS version with Inventor's ACIS version may be
// important.

#define ACIS_SAB_with_TransientKeys "ACIS SAB with TransientKeys"
#define LACIS_SAB_with_TransientKeys L"ACIS SAB with TransientKeys"

// Same as ACIS SAT except all procedural surfaces will be converted to NURB surfaces
// for backwards compatibility

#define ACIS_SAT_ProceduralToNURBS "ACIS SAT with ProceduralToNURBS"
#define LACIS_SAT_ProceduralToNURBS L"ACIS SAT with ProceduralToNURBS"

// Same as ACIS SAB except all procedural surfaces will be converted to NURB surfaces
// for backwards compatibility

#define ACIS_SAB_ProceduralToNURBS "ACIS SAB with ProceduralToNURBS"
#define LACIS_SAB_ProceduralToNURBS L"ACIS SAB with ProceduralToNURBS"

// Combination of ACIS SAT ProceduralToNURBS and ACIS SAT with TransientKeys.
// The data is decorated with PID attributes on the Faces, Edges and vertices.
// These attributes are the 'Transient Keys' recognized by Inventor's API. Using
// these attributes as Transient Keys, a client can get different levels of associativity to
// the Faces, Edges and Vertices. Procedural surfaces will be decomposed in to NURB surfaces
//
#define ACIS_SAT_ProceduralToNURBS_with_TransientKeys  "ACIS SAT ProceduralToNURBS with TransientKeys"
#define LACIS_SAT_ProceduralToNURBS_with_TransientKeys L"ACIS SAT ProceduralToNURBS with TransientKeys"

// above options along with the option to save in Document units
#define ACIS_SAT_ProceduralToNURBS_with_TransientKeys_DocUnits  "ACIS SAT ProceduralToNURBS with TransientKeys DocUnits"
#define LACIS_SAT_ProceduralToNURBS_with_TransientKeys_DocUnits L"ACIS SAT ProceduralToNURBS with TransientKeys DocUnits"

#define ASM_SAT_with_TransientKeys_DocUnits  "ASM SAT with TransientKeys DocUnits"
#define LASM_SAT_with_TransientKeys_DocUnits L"ASM SAT with TransientKeys DocUnits"

// define options to save in latest ASM format
#define ASM_SAT_with_TransientKeys  "ASM SAT with TransientKeys"
#define LASM_SAT_with_TransientKeys L"ASM SAT with TransientKeys"

// define options to save in latest ASM format include simulation surface bodies(ignore invisible occurrences in the assembly)
#define ASM_SAT_with_TransientKeys_with_SimSurfaces  "ASM SAT with TransientKeys Include Simulation Surfaces"
#define LASM_SAT_with_TransientKeys_with_SimSurfaces L"ASM SAT with TransientKeys Include Simulation Surfaces"

// Combination of ACIS SAB ProceduralToNURBS and ACIS SAB with TransientKeys.
// The data is decorated with PID attributes on the Faces, Edges and vertices.
// These attributes are the 'Transient Keys' recognized by Inventor's API. Using
// these attributes as Transient Keys, a client can get different levels of associativity to
// the Faces, Edges and Vertices. Procedural surfaces will be decomposed in to NURB surfaces
// and the file is in a binary format
//
#define ACIS_SAB_ProceduralToNURBS_with_TransientKeys "ACIS SAB ProceduralToNURBS with TransientKeys"
#define LACIS_SAB_ProceduralToNURBS_with_TransientKeys L"ACIS SAB ProceduralToNURBS with TransientKeys"

// above options along with the option to save in Document units
#define ACIS_SAB_ProceduralToNURBS_with_TransientKeys_DocUnits  "ACIS SAB ProceduralToNURBS with TransientKeys DocUnits"
#define LACIS_SAB_ProceduralToNURBS_with_TransientKeys_DocUnits L"ACIS SAB ProceduralToNURBS with TransientKeys DocUnits"

#define ASM_SAB_with_TransientKeys_DocUnits  "ASM SAB with TransientKeys DocUnits"
#define LASM_SAB_with_TransientKeys_DocUnits L"ASM SAB with TransientKeys DocUnits"

#define ASM_SAB_with_TransientKeys  "ASM SAB with TransientKeys"
#define LASM_SAB_with_TransientKeys L"ASM SAB with TransientKeys"

// Don't strip attributes before writing out in latest ASM format.
#define ACIS_SAT_with_Attributes "ACIS SAT with Attributes"
#define LACIS_SAT_with_Attributes L"ACIS SAT with Attributes"

#define ACIS_SAB_with_Attributes  "ACIS SAB with Attributes"
#define LACIS_SAB_with_Attributes L"ACIS SAB with Attributes"


/*------------------------- Format flavors involving Autodesk --------------------------------*/

// Various Inventor/Apprentice objects can be output in a DWF format. Some of the notable objects are
// Drawing Sheets.

#define AUTODESK_DWF "DWF"
#define LAUTODESK_DWF L"DWF"

// Various Inventor/Apprentice objects can be output in a DXF format. Some of the notable objects are
// Sketches.

#define AUTODESK_DXF "DXF"
#define LAUTODESK_DXF L"DXF"

// Various Inventor/Apprentice objects can be output in a DWG format. Some of the notable objects are
// Sketches.

#define AUTODESK_DWG "DWG"
#define LAUTODESK_DWG L"DWG"

// An internally used XML format that supports Content Center
// Used to communicate Family and FamilyMember identification.

#define _CF_INVENTOR_CCXML "Inventor CC Xml"
#define L_CF_INVENTOR_CCXML L"Inventor CC Xml"

#endif
