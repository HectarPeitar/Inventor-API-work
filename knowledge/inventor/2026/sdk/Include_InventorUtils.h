//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted,
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting documentation. 
// <YOUR COMPANY NAME> PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// <YOUR COMPANY NAME> SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE. <YOUR COMPANY NAME>, INC.
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE. 
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable
// 

//-----------------------------------------------------------------------------
//----- Inventor Utils
//-----------------------------------------------------------------------------
#pragma once

#define Wizard_Version "18.0.0.0"

//-----------------------------------------------------------------------------

#pragma warning(push)
#pragma warning(disable:4192 4049 4278)
#import "RxInventor.tlb" no_namespace named_guids raw_dispinterfaces raw_method_prefix("") high_method_prefix("Method") \
	rename("DeleteFile", "APIDeleteFile"), rename("CopyFile", "APICopyFile"), rename("MoveFile", "APIMoveFile") \
	rename("SetEnvironmentVariable", "APISetEnvironmentVariable")
#pragma warning(pop)

//-----------------------------------------------------------------------------
#ifdef _AFXDLL
#include "AfxInventor.h"
#endif
#include "CATIDs.h"
#include "ClipboardFormats.h"
//#include "CommandNames.h"
#include "DispatchUtils.h"
#include "DocCLSIDs.h"
#include "EnvInternalNames.h"
#include "EventsDispIds.h"
#include "MiscConstants.h"
#include "PropFMTIDs.h"
#include "PropVariantProperty.h"
#include "SafeArrayUtil.h"
#include "ServerCLSIDs.h"
#include "ToolBarInternalNames.h"

#ifdef __ATLCOM_H__
#include "AtlAddinServer.h"
#endif
