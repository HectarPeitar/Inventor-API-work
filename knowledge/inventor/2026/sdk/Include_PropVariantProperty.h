/*
  Copyright © 1998 by Autodesk, Inc.


  DESCRIPTION

  This file contains the declaration of the COM interface supported on Inventor's
  Property and Property Set objects. These special interfaces are necessitated in order 
  to by-pass Microsoft's apparent #import bug that generates a 'multiply-defined structure' 
  if a PROPVARIANT is used as an argument in a method in a typelib. C++ users can 
  QueryInterface for this interface (IID_IRxPropVariantProperty and IID_IRxPropVariantPropertySet)
  and get/set/create the value of the property using the richer PROPVARIANT structure.

  In order to use this interface you would have to have this file included atleast once in your
  project soon after the 'initguid.h' file has been included. You can freely include this file 
  elsewhere, but just once in a file along with the 'initguid.h'. This latter allocates
  the IID_IRxPropVariantProperty in your project.


  NOTE

  This interface does not have any marshaling support installed. Hence, it can only be used
  in-process. The typical scenarios include -- the Client being an AddIn inside Inventor's process
  or when Inventor's Apprentice Server is working inside the Client's process space.
  
  
  HISTORY

  SS  :  01/04/00  :  Creation
*/

#ifndef _AUTODESK_INVENTOR_PROPVARIANTPROPERTY_
#define _AUTODESK_INVENTOR_PROPVARIANTPROPERTY_

#include <objbase.h>

#ifndef _INITGUID
#define _DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    EXTERN_C const GUID FAR name
#else
#define _DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    EXTERN_C const GUID name \
                = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }
#endif // INITGUID

interface IRxProperty;

/*------------------------ IRxPropVariantProperty -----------------------------------------*/

// {1BACED46-C2CB-11d3-B79D-0060B0F159EF}
DEFINE_GUID(IID_IRxPropVariantProperty, 
0x1baced46, 0xc2cb, 0x11d3, 0xb7, 0x9d, 0x0, 0x60, 0xb0, 0xf1, 0x59, 0xef);

struct __declspec(uuid("1BACED46-C2CB-11d3-B79D-0060B0F159EF"))
IRxPropVariantProperty : IUnknown
{
	// Gets the value of the Property in a PROPVARIANT structure
  // The caller is responsible for the freeing of memory that may have gotten allocated
  // as a result (BSTRs, ClipBoard Format, etc.)
  //
  virtual HRESULT GetValue (PROPVARIANT* pValue) = 0;

	// Sets the value of the Property from the PROPVARIANT structure
  // The memory passed in is not freed during this call.
  //
  virtual HRESULT PutValue (PROPVARIANT Value) = 0;
};


/*------------------------ IRxPropVariantPropertySet -----------------------------------------*/

// {9C88D3AE-C3EB-11d3-B79E-0060B0F159EF}
DEFINE_GUID(IID_IRxPropVariantPropertySet, 
0x9c88d3ae, 0xc3eb, 0x11d3, 0xb7, 0x9e, 0x0, 0x60, 0xb0, 0xf1, 0x59, 0xef);

struct __declspec(uuid("9C88D3AE-C3EB-11d3-B79E-0060B0F159EF"))
IRxPropVariantPropertySet : IUnknown
{
	// Creates a new Property in this Set. The Property's Id ('PropId') must be supplied (PROPID).
  // Its name is optional (pass in NULL). The value of the property must be supplied as a
  // PROPVARIANT. The newly created property's interface is returned.
  virtual HRESULT Create (long PropId, PROPVARIANT PropValue, BSTR Name, IRxProperty **ppProperty) = 0;

	// Creates a new Property in this Set. The Property's name must be supplied.
  // The value of the property must be supplied as a PROPVARIANT. The newly created property's 
  // interface is returned.
  virtual HRESULT CreateByName (PROPVARIANT PropValue, BSTR Name, IRxProperty **ppProperty) = 0;
};

#endif
