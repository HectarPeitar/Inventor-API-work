/*
	Copyright © 1998 by Autodesk, Inc.


	DESCRIPTION

	This file contains the definitions of CATIDs recognized by Inventor and its related products.
	A Third Party will decide which of these Categories to implement and will install its product
	registering itself as a standard ActiveX component. During its registration, it must use ActiveX's
	Category Manager to help register its Implemented Categories. It may also advertise Categories
	that it requires to be implemented by Inventor. But this latter, currently, is for future use.


	HISTORY

	SS  :  03/16/99  :  Creation
*/

#ifndef _AUTODESK_INVENTOR_CATIDS_
#define _AUTODESK_INVENTOR_CATIDS_

#include <objbase.h>
#include <initguid.h>


// The CATID that signifies the implementation of an Inventor Application-level AddIn. This
// essentially means a COM-component that has implemented the IRxApplicationAddinServer interface
// or its IDispatch counterpart, ApplicationAddInServer. Registering yourself with this
// CATID as "Implemented Categories" will cause Inventor to recognize your component as a potential
// Application-level AddIn that may be run alongside Inventor, remaining active, throughout the session.

// {E357129A-DB40-11d2-B783-0060B0F159EF}
DEFINE_GUID(CATID_InventorApplicationAddIn,
0xe357129a, 0xdb40, 0x11d2, 0xb7, 0x83, 0x0, 0x60, 0xb0, 0xf1, 0x59, 0xef);

#define CATID_InventorApplicationAddIn_RegGUID "E357129A-DB40-11d2-B783-0060B0F159EF"
#define CATID_InventorApplicationAddIn_Name L"Inventor Application AddIn Server protocol"


// The CATID that signifies the implementation of an Inventor Application-level Addin for a
// release of Inventor that supports Addin version control (refer to the reference manual
// for information about version control). This essentially means a COM-component that has
// implemented the IRxApplicationAddinServer interface or its IDispatch counterpart,
// ApplicationAddInServer. Registering yourself with this CATID as "Implemented Categories"
// will cause Inventor to recognize your component as a potential Application-level AddIn
// that may be run alongside Inventor, remaining active, throughout the session.

// {39AD2B5C-7A29-11D6-8E0A-0010B541CAA8}
DEFINE_GUID(CATID_InventorVersionedApplicationAddIn,
	0x39AD2B5C, 0x7A29, 0x11D6, 0x8E, 0x0A, 0x00, 0x10, 0xB5, 0x41, 0xCA, 0xA8);

#define CATID_InventorVersionedApplicationAddIn_RegGUID "39AD2B5C-7A29-11D6-8E0A-0010B541CAA8"
#define CATID_InventorVersionedApplicationAddIn_Name L"Inventor Versioned Application AddIn Server protocol"


// The CATID that signifies requiring the host to have implemented a Inventor Application-level AddIn Site
// protocol. The Inventor application implements this. The Third Party Application-level AddIn
// can register this CATID as required from the host.

// {E357129B-DB40-11d2-B783-0060B0F159EF}
DEFINE_GUID(CATID_InventorApplicationAddInSite,
0xe357129b, 0xdb40, 0x11d2, 0xb7, 0x83, 0x0, 0x60, 0xb0, 0xf1, 0x59, 0xef);

#define CATID_InventorApplicationAddInSite_RegGUID "E357129B-DB40-11d2-B783-0060B0F159EF"
#define CATID_InventorApplicationAddInSite_Name L"Inventor Application AddIn Site protocol"

#endif



