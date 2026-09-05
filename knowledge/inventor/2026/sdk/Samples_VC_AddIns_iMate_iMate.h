

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 03:14:07 2038
 */
/* Compiler settings for iMateSampleAddin.idl:
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

#ifndef __iMateSampleAddin_h__
#define __iMateSampleAddin_h__

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

#ifndef __IiMateSampleAddinAddInServer_FWD_DEFINED__
#define __IiMateSampleAddinAddInServer_FWD_DEFINED__
typedef interface IiMateSampleAddinAddInServer IiMateSampleAddinAddInServer;

#endif 	/* __IiMateSampleAddinAddInServer_FWD_DEFINED__ */


#ifndef __iMateSampleAddinAddInServer_FWD_DEFINED__
#define __iMateSampleAddinAddInServer_FWD_DEFINED__

#ifdef __cplusplus
typedef class iMateSampleAddinAddInServer iMateSampleAddinAddInServer;
#else
typedef struct iMateSampleAddinAddInServer iMateSampleAddinAddInServer;
#endif /* __cplusplus */

#endif 	/* __iMateSampleAddinAddInServer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IiMateSampleAddinAddInServer_INTERFACE_DEFINED__
#define __IiMateSampleAddinAddInServer_INTERFACE_DEFINED__

/* interface IiMateSampleAddinAddInServer */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IiMateSampleAddinAddInServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D6DC0ED8-A9BE-48A6-942D-6464C2B36EEE")
    IiMateSampleAddinAddInServer : public IDispatch
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

    typedef struct IiMateSampleAddinAddInServerVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IiMateSampleAddinAddInServer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IiMateSampleAddinAddInServer * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IiMateSampleAddinAddInServer * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IiMateSampleAddinAddInServer * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IiMateSampleAddinAddInServer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IiMateSampleAddinAddInServer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IiMateSampleAddinAddInServer * This,
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
        
        DECLSPEC_XFGVIRT(IiMateSampleAddinAddInServer, Activate)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Activate )( 
            IiMateSampleAddinAddInServer * This,
            /* [in] */ IDispatch *pDisp,
            /* [in] */ VARIANT_BOOL FirstTime);
        
        DECLSPEC_XFGVIRT(IiMateSampleAddinAddInServer, Deactivate)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Deactivate )( 
            IiMateSampleAddinAddInServer * This);
        
        DECLSPEC_XFGVIRT(IiMateSampleAddinAddInServer, ExecuteCommand)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ExecuteCommand )( 
            IiMateSampleAddinAddInServer * This,
            /* [in] */ long CommandID);
        
        DECLSPEC_XFGVIRT(IiMateSampleAddinAddInServer, get_Automation)
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Automation )( 
            IiMateSampleAddinAddInServer * This,
            /* [retval][out] */ IDispatch **Result);
        
        END_INTERFACE
    } IiMateSampleAddinAddInServerVtbl;

    interface IiMateSampleAddinAddInServer
    {
        CONST_VTBL struct IiMateSampleAddinAddInServerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IiMateSampleAddinAddInServer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IiMateSampleAddinAddInServer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IiMateSampleAddinAddInServer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IiMateSampleAddinAddInServer_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IiMateSampleAddinAddInServer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IiMateSampleAddinAddInServer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IiMateSampleAddinAddInServer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IiMateSampleAddinAddInServer_Activate(This,pDisp,FirstTime)	\
    ( (This)->lpVtbl -> Activate(This,pDisp,FirstTime) ) 

#define IiMateSampleAddinAddInServer_Deactivate(This)	\
    ( (This)->lpVtbl -> Deactivate(This) ) 

#define IiMateSampleAddinAddInServer_ExecuteCommand(This,CommandID)	\
    ( (This)->lpVtbl -> ExecuteCommand(This,CommandID) ) 

#define IiMateSampleAddinAddInServer_get_Automation(This,Result)	\
    ( (This)->lpVtbl -> get_Automation(This,Result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IiMateSampleAddinAddInServer_INTERFACE_DEFINED__ */



#ifndef __iMateSampleAddinLib_LIBRARY_DEFINED__
#define __iMateSampleAddinLib_LIBRARY_DEFINED__

/* library iMateSampleAddinLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_iMateSampleAddinLib;

EXTERN_C const CLSID CLSID_iMateSampleAddinAddInServer;

#ifdef __cplusplus

class DECLSPEC_UUID("D298E4CE-3D9F-4306-A667-A9CE578B9ED4")
iMateSampleAddinAddInServer;
#endif
#endif /* __iMateSampleAddinLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


