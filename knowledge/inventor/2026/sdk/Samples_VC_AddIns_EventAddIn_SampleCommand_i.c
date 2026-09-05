

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 03:14:07 2038
 */
/* Compiler settings for SampleCommand.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0628 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_ISelectEventHandler,0xD6283162,0x1026,0x46B5,0x80,0x1D,0xCA,0x47,0xDD,0xDE,0xCA,0x89);


MIDL_DEFINE_GUID(IID, IID_IInteractionEventHandler,0x74FD85D4,0xC442,0x4119,0xA4,0xBE,0xE9,0x34,0xB6,0x82,0x4D,0xA6);


MIDL_DEFINE_GUID(IID, LIBID_SampleCommandLib,0xE3953FB2,0x6ADB,0x4CC5,0x88,0x71,0x74,0x8A,0x59,0xDC,0xE3,0x88);


MIDL_DEFINE_GUID(CLSID, CLSID_SelectEventHandler,0x436DE7CF,0x3CB3,0x4032,0xBB,0x7E,0xA5,0x81,0xE8,0xBC,0x47,0xCF);


MIDL_DEFINE_GUID(CLSID, CLSID_InteractionEventHandler,0xD2864462,0xB9F5,0x491C,0x98,0x3F,0xD4,0x90,0x27,0x64,0x32,0x8C);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



