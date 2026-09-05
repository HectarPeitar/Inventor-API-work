

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 03:14:07 2038
 */
/* Compiler settings for CustomCommand.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0628 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __CustomCommand_h__
#define __CustomCommand_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __ICustomCommandAddInServer_FWD_DEFINED__
#define __ICustomCommandAddInServer_FWD_DEFINED__
typedef interface ICustomCommandAddInServer ICustomCommandAddInServer;

#endif 	/* __ICustomCommandAddInServer_FWD_DEFINED__ */


#ifndef __CustomCommandAddInServer_FWD_DEFINED__
#define __CustomCommandAddInServer_FWD_DEFINED__

#ifdef __cplusplus
typedef class CustomCommandAddInServer CustomCommandAddInServer;
#else
typedef struct CustomCommandAddInServer CustomCommandAddInServer;
#endif /* __cplusplus */

#endif 	/* __CustomCommandAddInServer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ICustomCommandAddInServer_INTERFACE_DEFINED__
#define __ICustomCommandAddInServer_INTERFACE_DEFINED__

/* interface ICustomCommandAddInServer */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICustomCommandAddInServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F5B53DA9-D0DC-4EAE-A786-33F26087069D")
    ICustomCommandAddInServer : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Activate( 
            /* [in] */ IDispatch *pDisp,
            /* [in] */ VARIANT_BOOL FirstTime) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Deactivate( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ExecuteCommand( 
            /* [in] */ long CommandID) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Automation( 
            /* [retval][out] */ IDispatch **Result) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICustomCommandAddInServerVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICustomCommandAddInServer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICustomCommandAddInServer * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICustomCommandAddInServer * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICustomCommandAddInServer * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICustomCommandAddInServer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICustomCommandAddInServer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICustomCommandAddInServer * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        DECLSPEC_XFGVIRT(ICustomCommandAddInServer, Activate)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Activate )( 
            ICustomCommandAddInServer * This,
            /* [in] */ IDispatch *pDisp,
            /* [in] */ VARIANT_BOOL FirstTime);
        
        DECLSPEC_XFGVIRT(ICustomCommandAddInServer, Deactivate)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Deactivate )( 
            ICustomCommandAddInServer * This);
        
        DECLSPEC_XFGVIRT(ICustomCommandAddInServer, ExecuteCommand)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ExecuteCommand )( 
            ICustomCommandAddInServer * This,
            /* [in] */ long CommandID);
        
        DECLSPEC_XFGVIRT(ICustomCommandAddInServer, get_Automation)
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Automation )( 
            ICustomCommandAddInServer * This,
            /* [retval][out] */ IDispatch **Result);
        
        END_INTERFACE
    } ICustomCommandAddInServerVtbl;

    interface ICustomCommandAddInServer
    {
        CONST_VTBL struct ICustomCommandAddInServerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICustomCommandAddInServer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICustomCommandAddInServer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICustomCommandAddInServer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICustomCommandAddInServer_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICustomCommandAddInServer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICustomCommandAddInServer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICustomCommandAddInServer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ICustomCommandAddInServer_Activate(This,pDisp,FirstTime)	\
    ( (This)->lpVtbl -> Activate(This,pDisp,FirstTime) ) 

#define ICustomCommandAddInServer_Deactivate(This)	\
    ( (This)->lpVtbl -> Deactivate(This) ) 

#define ICustomCommandAddInServer_ExecuteCommand(This,CommandID)	\
    ( (This)->lpVtbl -> ExecuteCommand(This,CommandID) ) 

#define ICustomCommandAddInServer_get_Automation(This,Result)	\
    ( (This)->lpVtbl -> get_Automation(This,Result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICustomCommandAddInServer_INTERFACE_DEFINED__ */



#ifndef __CustomCommandLib_LIBRARY_DEFINED__
#define __CustomCommandLib_LIBRARY_DEFINED__

/* library CustomCommandLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CustomCommandLib;

EXTERN_C const CLSID CLSID_CustomCommandAddInServer;

#ifdef __cplusplus

class DECLSPEC_UUID("05CC5326-B165-483A-8A2A-4B52B7A54BEF")
CustomCommandAddInServer;
#endif
#endif /* __CustomCommandLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


