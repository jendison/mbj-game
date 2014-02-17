

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0595 */
/* at Sat Dec 21 17:04:16 2013
 */
/* Compiler settings for CommomClientConfig.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0595 
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __CommomClientConfig_h_h__
#define __CommomClientConfig_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICommomClientConfig_FWD_DEFINED__
#define __ICommomClientConfig_FWD_DEFINED__
typedef interface ICommomClientConfig ICommomClientConfig;

#endif 	/* __ICommomClientConfig_FWD_DEFINED__ */


#ifndef __CommomClientConfig_FWD_DEFINED__
#define __CommomClientConfig_FWD_DEFINED__

#ifdef __cplusplus
typedef class CommomClientConfig CommomClientConfig;
#else
typedef struct CommomClientConfig CommomClientConfig;
#endif /* __cplusplus */

#endif 	/* __CommomClientConfig_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __CommomClientConfig_LIBRARY_DEFINED__
#define __CommomClientConfig_LIBRARY_DEFINED__

/* library CommomClientConfig */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_CommomClientConfig;

#ifndef __ICommomClientConfig_DISPINTERFACE_DEFINED__
#define __ICommomClientConfig_DISPINTERFACE_DEFINED__

/* dispinterface ICommomClientConfig */
/* [uuid] */ 


EXTERN_C const IID DIID_ICommomClientConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B8116DF4-67E8-49CB-B084-D2615BC48FF9")
    ICommomClientConfig : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ICommomClientConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICommomClientConfig * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICommomClientConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICommomClientConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICommomClientConfig * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICommomClientConfig * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICommomClientConfig * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICommomClientConfig * This,
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
        
        END_INTERFACE
    } ICommomClientConfigVtbl;

    interface ICommomClientConfig
    {
        CONST_VTBL struct ICommomClientConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICommomClientConfig_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICommomClientConfig_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICommomClientConfig_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICommomClientConfig_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICommomClientConfig_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICommomClientConfig_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICommomClientConfig_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ICommomClientConfig_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CommomClientConfig;

#ifdef __cplusplus

class DECLSPEC_UUID("28E9DF9D-E7FB-4B14-943F-CE3FD243DCBC")
CommomClientConfig;
#endif
#endif /* __CommomClientConfig_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


