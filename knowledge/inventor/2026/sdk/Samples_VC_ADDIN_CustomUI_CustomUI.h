

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 03:14:07 2038
 */
/* Compiler settings for CustomUI.idl:
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

#ifndef __CustomUI_h__
#define __CustomUI_h__

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

#ifndef __ICustomUIAddInServer_FWD_DEFINED__
#define __ICustomUIAddInServer_FWD_DEFINED__
typedef interface ICustomUIAddInServer ICustomUIAddInServer;

#endif 	/* __ICustomUIAddInServer_FWD_DEFINED__ */


#ifndef __CustomUIAddInServer_FWD_DEFINED__
#define __CustomUIAddInServer_FWD_DEFINED__

#ifdef __cplusplus
typedef class CustomUIAddInServer CustomUIAddInServer;
#else
typedef struct CustomUIAddInServer CustomUIAddInServer;
#endif /* __cplusplus */

#endif 	/* __CustomUIAddInServer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ICustomUIAddInServer_INTERFACE_DEFINED__
#define __ICustomUIAddInServer_INTERFACE_DEFINED__

/* interface ICustomUIAddInServer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ICustomUIAddInServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ADAF3CA1-0685-4A54-B452-870CB1FF2F4C")
    ICustomUIAddInServer : public IDispatch
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

    typedef struct ICustomUIAddInServerVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICustomUIAddInServer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICustomUIAddInServer * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICustomUIAddInServer * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICustomUIAddInServer * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICustomUIAddInServer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICustomUIAddInServer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICustomUIAddInServer * This,
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
        
        DECLSPEC_XFGVIRT(ICustomUIAddInServer, Activate)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Activate )( 
            ICustomUIAddInServer * This,
            /* [in] */ IDispatch *pDisp,
            /* [in] */ VARIANT_BOOL FirstTime);
        
        DECLSPEC_XFGVIRT(ICustomUIAddInServer, Deactivate)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Deactivate )( 
            ICustomUIAddInServer * This);
        
        DECLSPEC_XFGVIRT(ICustomUIAddInServer, ExecuteCommand)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ExecuteCommand )( 
            ICustomUIAddInServer * This,
            /* [in] */ long CommandID);
        
        DECLSPEC_XFGVIRT(ICustomUIAddInServer, get_Automation)
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Automation )( 
            ICustomUIAddInServer * This,
            /* [retval][out] */ IDispatch **Result);
        
        END_INTERFACE
    } ICustomUIAddInServerVtbl;

    interface ICustomUIAddInServer
    {
        CONST_VTBL struct ICustomUIAddInServerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICustomUIAddInServer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICustomUIAddInServer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICustomUIAddInServer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICustomUIAddInServer_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICustomUIAddInServer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICustomUIAddInServer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICustomUIAddInServer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ICustomUIAddInServer_Activate(This,pDisp,FirstTime)	\
    ( (This)->lpVtbl -> Activate(This,pDisp,FirstTime) ) 

#define ICustomUIAddInServer_Deactivate(This)	\
    ( (This)->lpVtbl -> Deactivate(This) ) 

#define ICustomUIAddInServer_ExecuteCommand(This,CommandID)	\
    ( (This)->lpVtbl -> ExecuteCommand(This,CommandID) ) 

#define ICustomUIAddInServer_get_Automation(This,Result)	\
    ( (This)->lpVtbl -> get_Automation(This,Result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICustomUIAddInServer_INTERFACE_DEFINED__ */



#ifndef __CustomUILib_LIBRARY_DEFINED__
#define __CustomUILib_LIBRARY_DEFINED__

/* library CustomUILib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CustomUILib;

EXTERN_C const CLSID CLSID_CustomUIAddInServer;

#ifdef __cplusplus

class DECLSPEC_UUID("B6CD8174-8817-4AF2-9561-C0F273ABF5D8")
CustomUIAddInServer;
#endif
#endif /* __CustomUILib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


