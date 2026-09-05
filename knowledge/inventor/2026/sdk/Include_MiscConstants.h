/*
  Copyright © 1998 by Autodesk, Inc.


  DESCRIPTION

  This file contains some useful constants. They may or may not be available inside
  Inventor typelibs as well.


  HISTORY

  SS  :  04/09/00  :  Creation
*/

#ifndef _AUTODESK_INVENTOR_MISCCONSTANTS_
#define _AUTODESK_INVENTOR_MISCCONSTANTS_



/*----- *** DISCONTINUED FROM R3 ONWARDS. USE 'SOFTWAREVERSION' OBJECT INSTEAD *** --------*/

/*
 * The Minor Versions of each of Inventor's public releases, including any Service
 * Packs. 
 *
 * Due to their defunct nature, the symbols for the constants have been modified (prefixed
 * by an underscore). This will force any code recompiling to take a hard look at switching
 * over to the new SoftwareVersion object that provides this same capability, but in a much
 * more supportable and understandable way. The SoftwareVersion object is obtainable from 
 * Inventor's Application or Apprentice Server's ApprenticeServer objects, respectively.
 * This list is maintained only upto R2 and provided purely for compatibility reasons. 
 */

#define _InventorR1_BetaRelease                           211
#define _InventorR1_ProductRelease                        572
#define _InventorR1_ProductRelease_ServicePack1           581
#define _InventorR1_ProductRelease_ServicePack2           700

#define _InventorR2_BetaRelease                           2490
#define _InventorR2_ProductRelease                        2658
#define _InventorR2_ProductRelease_ServicePack1           2700
#define _InventorR2_ProductRelease_ServicePack2           2749
#define _InventorR2_ProductRelease_ServicePack3           2779

/*------------------------- *** END DISCONTINUED *** --------------------------------------*/

// 0x80040201
#define E_MISSING_REALDWG        MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0201)

#endif
