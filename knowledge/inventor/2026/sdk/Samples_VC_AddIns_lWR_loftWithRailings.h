

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 03:14:07 2038
 */
/* Compiler settings for loftWithRailings.idl:
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

#ifndef __loftWithRailings_h__
#define __loftWithRailings_h__

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

#ifndef __IloftWithRailingsAddInServer_FWD_DEFINED__
#define __IloftWithRailingsAddInServer_FWD_DEFINED__
typedef interface IloftWithRailingsAddInServer IloftWithRailingsAddInServer;

#endif 	/* __IloftWithRailingsAddInServer_FWD_DEFINED__ */


#ifndef __loftWithRailingsAddInServer_FWD_DEFINED__
#define __loftWithRailingsAddInServer_FWD_DEFINED__

#ifdef __cplusplus
typedef class loftWithRailingsAddInServer loftWithRailingsAddInServer;
#else
typedef struct loftWithRailingsAddInServer loftWithRailingsAddInServer;
#endif /* __cplusplus */

#endif 	/* __loftWithRailingsAddInServer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IloftWithRailingsAddInServer_INTERFACE_DEFINED__
#define __IloftWithRailingsAddInServer_INTERFACE_DEFINED__

/* interface IloftWithRailingsAddInServer */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IloftWithRailingsAddInServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B623765F-4AB1-4C78-A45F-294305E5956D")
    IloftWithRailingsAddInServer : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Activate( 
            /* [in] */ IDispatch *pDisp,
            /* [in] */ VARIANT_BOOL FirstTime) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Deactivate( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ExecuteCommand( 
            /* [in] */ long CommandID) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Automation( 
            /* [retval][out] */ IDispatch **ppDisp) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IloftWithRailingsAddInServerVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IloftWithRailingsAddInServer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IloftWithRailingsAddInServer * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IloftWithRailingsAddInServer * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IloftWithRailingsAddInServer * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IloftWithRailingsAddInServer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IloftWithRailingsAddInServer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IloftWithRailingsAddInServer * This,
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
        
        DECLSPEC_XFGVIRT(IloftWithRailingsAddInServer, Activate)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Activate )( 
            IloftWithRailingsAddInServer * This,
            /* [in] */ IDispatch *pDisp,
            /* [in] */ VARIANT_BOOL FirstTime);
        
        DECLSPEC_XFGVIRT(IloftWithRailingsAddInServer, Deactivate)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Deactivate )( 
            IloftWithRailingsAddInServer * This);
        
        DECLSPEC_XFGVIRT(IloftWithRailingsAddInServer, ExecuteCommand)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ExecuteCommand )( 
            IloftWithRailingsAddInServer * This,
            /* [in] */ long CommandID);
        
        DECLSPEC_XFGVIRT(IloftWithRailingsAddInServer, get_Automation)
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Automation )( 
            IloftWithRailingsAddInServer * This,
            /* [retval][out] */ IDispatch **ppDisp);
        
        END_INTERFACE
    } IloftWithRailingsAddInServerVtbl;

    interface IloftWithRailingsAddInServer
    {
        CONST_VTBL struct IloftWithRailingsAddInServerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IloftWithRailingsAddInServer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IloftWithRailingsAddInServer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IloftWithRailingsAddInServer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IloftWithRailingsAddInServer_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IloftWithRailingsAddInServer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IloftWithRailingsAddInServer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IloftWithRailingsAddInServer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IloftWithRailingsAddInServer_Activate(This,pDisp,FirstTime)	\
    ( (This)->lpVtbl -> Activate(This,pDisp,FirstTime) ) 

#define IloftWithRailingsAddInServer_Deactivate(This)	\
    ( (This)->lpVtbl -> Deactivate(This) ) 

#define IloftWithRailingsAddInServer_ExecuteCommand(This,CommandID)	\
    ( (This)->lpVtbl -> ExecuteCommand(This,CommandID) ) 

#define IloftWithRailingsAddInServer_get_Automation(This,ppDisp)	\
    ( (This)->lpVtbl -> get_Automation(This,ppDisp) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IloftWithRailingsAddInServer_INTERFACE_DEFINED__ */



#ifndef __loftWithRailingsLib_LIBRARY_DEFINED__
#define __loftWithRailingsLib_LIBRARY_DEFINED__

/* library loftWithRailingsLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_loftWithRailingsLib;

EXTERN_C const CLSID CLSID_loftWithRailingsAddInServer;

#ifdef __cplusplus

class DECLSPEC_UUID("37E7CBC7-F0F7-455B-85B4-668E0674C9DE")
loftWithRailingsAddInServer;
#endif
#endif /* __loftWithRailingsLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


