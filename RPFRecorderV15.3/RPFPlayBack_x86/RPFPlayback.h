

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Fri Jul 18 12:35:46 2008
 */
/* Compiler settings for ..\RPFPlayback.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __RPFPlayback_h__
#define __RPFPlayback_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __CRPFPlayback_FWD_DEFINED__
#define __CRPFPlayback_FWD_DEFINED__

#ifdef __cplusplus
typedef class CRPFPlayback CRPFPlayback;
#else
typedef struct CRPFPlayback CRPFPlayback;
#endif /* __cplusplus */

#endif 	/* __CRPFPlayback_FWD_DEFINED__ */


#ifndef __ScreenUIElement_FWD_DEFINED__
#define __ScreenUIElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class ScreenUIElement ScreenUIElement;
#else
typedef struct ScreenUIElement ScreenUIElement;
#endif /* __cplusplus */

#endif 	/* __ScreenUIElement_FWD_DEFINED__ */


#ifndef __IWinEventHandle_FWD_DEFINED__
#define __IWinEventHandle_FWD_DEFINED__
typedef interface IWinEventHandle IWinEventHandle;
#endif 	/* __IWinEventHandle_FWD_DEFINED__ */


#ifndef __IMonitoringWindowsCallback_FWD_DEFINED__
#define __IMonitoringWindowsCallback_FWD_DEFINED__
typedef interface IMonitoringWindowsCallback IMonitoringWindowsCallback;
#endif 	/* __IMonitoringWindowsCallback_FWD_DEFINED__ */


#ifndef __ILoggerCallback_FWD_DEFINED__
#define __ILoggerCallback_FWD_DEFINED__
typedef interface ILoggerCallback ILoggerCallback;
#endif 	/* __ILoggerCallback_FWD_DEFINED__ */


#ifndef __IScrollerCallback_FWD_DEFINED__
#define __IScrollerCallback_FWD_DEFINED__
typedef interface IScrollerCallback IScrollerCallback;
#endif 	/* __IScrollerCallback_FWD_DEFINED__ */


#ifndef __IAccessibleUia_FWD_DEFINED__
#define __IAccessibleUia_FWD_DEFINED__
typedef interface IAccessibleUia IAccessibleUia;
#endif 	/* __IAccessibleUia_FWD_DEFINED__ */


#ifndef __IAccessibleUiaSupport_FWD_DEFINED__
#define __IAccessibleUiaSupport_FWD_DEFINED__
typedef interface IAccessibleUiaSupport IAccessibleUiaSupport;
#endif 	/* __IAccessibleUiaSupport_FWD_DEFINED__ */


#ifndef __IScreenElement_FWD_DEFINED__
#define __IScreenElement_FWD_DEFINED__
typedef interface IScreenElement IScreenElement;
#endif 	/* __IScreenElement_FWD_DEFINED__ */


#ifndef __IRPFPlayback_FWD_DEFINED__
#define __IRPFPlayback_FWD_DEFINED__
typedef interface IRPFPlayback IRPFPlayback;
#endif 	/* __IRPFPlayback_FWD_DEFINED__ */


/* header files for imported files */
#include "prsht.h"
#include "mshtml.h"
#include "mshtmhst.h"
#include "objsafe.h"
#include "OleAcc.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_RPFPlayback_0000 */
/* [local] */ 

#define	DEFAULT_DRAG_SPEED	( 50 )

#define	DEFAULT_TYPING_DELAY	( 50 )

#define	PLAYBACK_VERSION_STRING	( L"15.3" )



extern RPC_IF_HANDLE __MIDL_itf_RPFPlayback_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_RPFPlayback_0000_v0_0_s_ifspec;


#ifndef __RPFPlayback_LIBRARY_DEFINED__
#define __RPFPlayback_LIBRARY_DEFINED__

/* library RPFPlayback */
/* [helpstring][uuid][version] */ 

#pragma region ScreenElement enums
typedef 
enum SearchFlags
    {	ALL_DESCENDANTS	= -1,
	CHILDREN_ONLY	= 1
    } 	SEARCHFLAGS;

typedef 
enum KeyboardAction
    {	PRESS	= 1,
	RELEASE	= 2,
	HIT	= 3
    } 	KEYBOARD_ACTION;

typedef 
enum VerificationFlags
    {	VF_VALUE_STATE_EXACT	= 0,
	VF_VALUE_DONTCARE	= 0x1,
	VF_STATE_DONTCARE	= 0x2,
	VF_STATE_HAS	= 0x4,
	VF_VALUE_BEGINS	= 0x8
    } 	VERIFICATIONFLAGS;

typedef 
enum SetValueAsSliderFlags
    {	DF_AUTO	= 0,
	DF_HORIZONTAL	= 0x1,
	DF_VERTICAL	= 0x2
    } 	SLIDERFLAGS;

typedef 
enum SetValueAsComboBoxFlags
    {	CF_LEFT_DROP_DOWN_BUTTON	= 0x1,
	CF_USE_SELECT	= 0x2,
	CF_USE_SET_AS_EDIT	= 0x4,
	CF_DONT_VERIFY_SENDKEYS	= 0x8,
	CF_DONT_VERIFY_MIRROR_LANG	= 0x10,
	CF_USE_QUERYID	= 0x20
    } 	VALUEASCOMBOBOXFLAGS;

typedef 
enum SetValueAsEditBoxFlags
    {	EF_DELETE_CONTENT	= 0x1,
	EF_USE_MSAA	= 0x2,
	EF_USE_WM_SETTEXT	= 0x4,
	EF_USE_COPY_PASTE	= 0x8,
	EF_USE_SENDKEYS	= 0x10,
	EF_DONT_VERIFY	= 0x20
    } 	VALUEASEDITBOXFLAGS;

typedef 
enum EnsureVisibleFlags
    {	EVF_BY_SCROLLING	= 0x1,
	EVF_BY_EXPANDING_ANCESTORS	= 0x2,
	EVF_BY_EXPANDING_SIBLINGS	= 0x4,
	EVF_BY_SETTING_FOCUS	= 0x8,
	EVF_BY_MOVING_OBSCURING_WND	= 0x10
    } 	ENSUREVISIBLEFLAGS;

typedef 
enum ScrollingFlags
    {	SF_SCROLL_BAR	= 0x1,
	SF_WHEEL	= 0x2,
	SF_KEYBOARD	= 0x4
    } 	SCROLLINGFLAGS;

typedef 
enum ExpandCollapseFlags
    {	ECF_USE_TVM_EXPAND	= 0x1,
	ECF_USE_DOUBLECLICK	= 0x2,
	ECF_USE_NUMPAD	= 0x4,
	ECF_USE_ENTER	= 0x8
    } 	EXPANDCOLLAPCEFLAGS;

typedef 
enum MouseButtons
    {	LEFT_BUTTON	= 0,
	RIGHT_BUTTON	= 1,
	MIDDLE_BUTTON	= 2,
	X_BUTTON_1	= 3,
	X_BUTTON_2	= 4
    } 	MOUSE_BUTTONS;

typedef 
enum PlaybackFlags
    {	SET_MOUSE_POS_INSTANTLY	= 0x1,
	ENSURE_VISIBLE	= 0x2
    } 	PLAYBACK_FLAGS;

#pragma endregion ScreenElement enums
#pragma region Playback enums
typedef 
enum LoggingFlags
    {	FL_DISABLE_LOGGING	= 0xffffffff,
	FL_LOG_SEARCH_AND_PRIMITIVES	= 0x1,
	FL_LOG_TIME	= 0x2,
	FL_LOG_INTERNAL_INFO	= 0x4,
	FL_LOG_DUMP_SCREEN	= 0x8,
	FL_LOG_FAILURE_AS_INFO	= 0x10,
	FL_LOG_MSAA_PERF	= 0x20,
	FL_DUMP_DESCENDANTS_WHEN_NOT_FOUND	= 0x40,
	FL_LOG_AS_HTML	= 0x80
    } 	LOGGINGFLAGS;

typedef 
enum DumpScreenFormat
    {	DUMP_SCREEN_BMP	= 1,
	DUMP_SCREEN_PNG	= 2,
	DUMP_SCREEN_JPEG	= 3,
	DUMP_SCREEN_GIF	= 4
    } 	DUMPSCREENFORMAT;

typedef 
enum WaitForReadyMode
    {	MW_THREAD_STATE	= 0x1,
	MW_PROCESS_IDLE	= 0x2
    } 	WAITFORREADYMODE;

typedef 
enum ThreadState
    {	Initialized	= 0,
	Ready	= 1,
	Running	= 2,
	Standby	= 3,
	Terminated	= 4,
	Waiting	= 5,
	Transition	= 6,
	UnknownState	= 7
    } 	THREAD_STATE;

typedef 
enum AccTechnology
    {	WINDOW	= 0x1,
	MSAA	= 0x2,
	UIA	= 0x4
    } 	ACC_TECHNOLOGY;

typedef 
enum InternalParameter
    {	SEARCH_IN_TARGETPROCESS_ONLY	= 1,
	WFR_TIMEOUT	= 2,
	DEBUG_MODE	= 3,
	UISYNCHRONIZATION_ENABLED	= 4,
	EXACT_QID_MATCH	= 5,
	TARGET_WINDOW	= 6,
	TARGET_PROCESS_ID	= 7,
	SEARCH_TIMEOUT	= 8,
	SENDKEYS_DELAY	= 9,
	ALLOW_INPUT_ON_DESCENDANTS	= 10,
	EXIT_AS	= 11,
	ENABLE_MESSAGE_BOXES	= 12,
	ACCESSIBLE_TECHNOLOGY	= 13,
	DUMP_SCREEN_FORMAT	= 14,
	ENSURE_VISIBLE_FLAG	= 15
    } 	INTERNAL_PARAMETER;

typedef 
enum ExistAsParameter
    {	EXIT_PROCESS	= 1,
	SKIP_ALL_STEPS	= 2
    } 	EXIT_AS_PARAMETER;

#pragma endregion Playback enums

EXTERN_C const IID LIBID_RPFPlayback;

EXTERN_C const CLSID CLSID_CRPFPlayback;

#ifdef __cplusplus

class DECLSPEC_UUID("6EFAE6CD-1EB3-4D73-8975-6FBA0AE56FEE")
CRPFPlayback;
#endif

EXTERN_C const CLSID CLSID_ScreenUIElement;

#ifdef __cplusplus

class DECLSPEC_UUID("7AAD456D-DE8F-4a58-B931-DA70E609C808")
ScreenUIElement;
#endif
#endif /* __RPFPlayback_LIBRARY_DEFINED__ */

#ifndef __IWinEventHandle_INTERFACE_DEFINED__
#define __IWinEventHandle_INTERFACE_DEFINED__

/* interface IWinEventHandle */
/* [uuid][object] */ 


EXTERN_C const IID IID_IWinEventHandle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CC87985A-D401-415a-8196-B13A68F0ACBD")
    IWinEventHandle : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetQueryId( 
            /* [retval][out] */ BSTR *pbstrQueryId) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetQueryId( 
            /* [in] */ BSTR bstrQueryId) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetWinEvent( 
            /* [retval][out] */ INT *pnWinEvent) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetWinEvent( 
            /* [in] */ INT nWinEvent) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartWaiting( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWinEventHandleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWinEventHandle * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWinEventHandle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWinEventHandle * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetQueryId )( 
            IWinEventHandle * This,
            /* [retval][out] */ BSTR *pbstrQueryId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetQueryId )( 
            IWinEventHandle * This,
            /* [in] */ BSTR bstrQueryId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetWinEvent )( 
            IWinEventHandle * This,
            /* [retval][out] */ INT *pnWinEvent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetWinEvent )( 
            IWinEventHandle * This,
            /* [in] */ INT nWinEvent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartWaiting )( 
            IWinEventHandle * This);
        
        END_INTERFACE
    } IWinEventHandleVtbl;

    interface IWinEventHandle
    {
        CONST_VTBL struct IWinEventHandleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWinEventHandle_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWinEventHandle_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWinEventHandle_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWinEventHandle_GetQueryId(This,pbstrQueryId)	\
    (This)->lpVtbl -> GetQueryId(This,pbstrQueryId)

#define IWinEventHandle_SetQueryId(This,bstrQueryId)	\
    (This)->lpVtbl -> SetQueryId(This,bstrQueryId)

#define IWinEventHandle_GetWinEvent(This,pnWinEvent)	\
    (This)->lpVtbl -> GetWinEvent(This,pnWinEvent)

#define IWinEventHandle_SetWinEvent(This,nWinEvent)	\
    (This)->lpVtbl -> SetWinEvent(This,nWinEvent)

#define IWinEventHandle_StartWaiting(This)	\
    (This)->lpVtbl -> StartWaiting(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWinEventHandle_GetQueryId_Proxy( 
    IWinEventHandle * This,
    /* [retval][out] */ BSTR *pbstrQueryId);


void __RPC_STUB IWinEventHandle_GetQueryId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWinEventHandle_SetQueryId_Proxy( 
    IWinEventHandle * This,
    /* [in] */ BSTR bstrQueryId);


void __RPC_STUB IWinEventHandle_SetQueryId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWinEventHandle_GetWinEvent_Proxy( 
    IWinEventHandle * This,
    /* [retval][out] */ INT *pnWinEvent);


void __RPC_STUB IWinEventHandle_GetWinEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWinEventHandle_SetWinEvent_Proxy( 
    IWinEventHandle * This,
    /* [in] */ INT nWinEvent);


void __RPC_STUB IWinEventHandle_SetWinEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWinEventHandle_StartWaiting_Proxy( 
    IWinEventHandle * This);


void __RPC_STUB IWinEventHandle_StartWaiting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWinEventHandle_INTERFACE_DEFINED__ */


#ifndef __IMonitoringWindowsCallback_INTERFACE_DEFINED__
#define __IMonitoringWindowsCallback_INTERFACE_DEFINED__

/* interface IMonitoringWindowsCallback */
/* [uuid][object] */ 


EXTERN_C const IID IID_IMonitoringWindowsCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1C00DACB-4FE7-4040-A781-B93CDA73988C")
    IMonitoringWindowsCallback : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MonitoringWindowsCallBack( 
            /* [in] */ BSTR bstrWindowClass,
            /* [in] */ BSTR bstrWindowName,
            /* [in] */ INT64 hWnd,
            /* [in] */ int nWinEvent) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMonitoringInfo( 
            /* [out] */ BSTR *pbstrWindowClass,
            /* [in] */ int cchClass,
            /* [out] */ BSTR *pbstrWindowName,
            /* [in] */ int cchWindowName,
            /* [out] */ IWinEventHandle **ppWinEventHandle) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMonitoringWindowsCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMonitoringWindowsCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMonitoringWindowsCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMonitoringWindowsCallback * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MonitoringWindowsCallBack )( 
            IMonitoringWindowsCallback * This,
            /* [in] */ BSTR bstrWindowClass,
            /* [in] */ BSTR bstrWindowName,
            /* [in] */ INT64 hWnd,
            /* [in] */ int nWinEvent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMonitoringInfo )( 
            IMonitoringWindowsCallback * This,
            /* [out] */ BSTR *pbstrWindowClass,
            /* [in] */ int cchClass,
            /* [out] */ BSTR *pbstrWindowName,
            /* [in] */ int cchWindowName,
            /* [out] */ IWinEventHandle **ppWinEventHandle);
        
        END_INTERFACE
    } IMonitoringWindowsCallbackVtbl;

    interface IMonitoringWindowsCallback
    {
        CONST_VTBL struct IMonitoringWindowsCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMonitoringWindowsCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMonitoringWindowsCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMonitoringWindowsCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMonitoringWindowsCallback_MonitoringWindowsCallBack(This,bstrWindowClass,bstrWindowName,hWnd,nWinEvent)	\
    (This)->lpVtbl -> MonitoringWindowsCallBack(This,bstrWindowClass,bstrWindowName,hWnd,nWinEvent)

#define IMonitoringWindowsCallback_GetMonitoringInfo(This,pbstrWindowClass,cchClass,pbstrWindowName,cchWindowName,ppWinEventHandle)	\
    (This)->lpVtbl -> GetMonitoringInfo(This,pbstrWindowClass,cchClass,pbstrWindowName,cchWindowName,ppWinEventHandle)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMonitoringWindowsCallback_MonitoringWindowsCallBack_Proxy( 
    IMonitoringWindowsCallback * This,
    /* [in] */ BSTR bstrWindowClass,
    /* [in] */ BSTR bstrWindowName,
    /* [in] */ INT64 hWnd,
    /* [in] */ int nWinEvent);


void __RPC_STUB IMonitoringWindowsCallback_MonitoringWindowsCallBack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMonitoringWindowsCallback_GetMonitoringInfo_Proxy( 
    IMonitoringWindowsCallback * This,
    /* [out] */ BSTR *pbstrWindowClass,
    /* [in] */ int cchClass,
    /* [out] */ BSTR *pbstrWindowName,
    /* [in] */ int cchWindowName,
    /* [out] */ IWinEventHandle **ppWinEventHandle);


void __RPC_STUB IMonitoringWindowsCallback_GetMonitoringInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMonitoringWindowsCallback_INTERFACE_DEFINED__ */


#ifndef __ILoggerCallback_INTERFACE_DEFINED__
#define __ILoggerCallback_INTERFACE_DEFINED__

/* interface ILoggerCallback */
/* [uuid][object] */ 


EXTERN_C const IID IID_ILoggerCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("96BC3CB8-1523-4d63-A174-BF655B1911AA")
    ILoggerCallback : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoggerCallback( 
            /* [out][in] */ BSTR *pbstrLogString,
            /* [out][in] */ int *pfLogDefault,
            /* [out][in] */ int *pnDumpScreen) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILoggerCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoggerCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoggerCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoggerCallback * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoggerCallback )( 
            ILoggerCallback * This,
            /* [out][in] */ BSTR *pbstrLogString,
            /* [out][in] */ int *pfLogDefault,
            /* [out][in] */ int *pnDumpScreen);
        
        END_INTERFACE
    } ILoggerCallbackVtbl;

    interface ILoggerCallback
    {
        CONST_VTBL struct ILoggerCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoggerCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILoggerCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILoggerCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILoggerCallback_LoggerCallback(This,pbstrLogString,pfLogDefault,pnDumpScreen)	\
    (This)->lpVtbl -> LoggerCallback(This,pbstrLogString,pfLogDefault,pnDumpScreen)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILoggerCallback_LoggerCallback_Proxy( 
    ILoggerCallback * This,
    /* [out][in] */ BSTR *pbstrLogString,
    /* [out][in] */ int *pfLogDefault,
    /* [out][in] */ int *pnDumpScreen);


void __RPC_STUB ILoggerCallback_LoggerCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILoggerCallback_INTERFACE_DEFINED__ */


#ifndef __IScrollerCallback_INTERFACE_DEFINED__
#define __IScrollerCallback_INTERFACE_DEFINED__

/* interface IScrollerCallback */
/* [uuid][object] */ 

typedef 
enum ScrollAmountRpf
    {	NO_AMOUNT	= 0,
	FORWARD_BY_LARGE_AMOUNT	= 0x1,
	BACK_BY_LARGE_AMOUNT	= 0x2,
	FORWARD_BY_SMALL_AMOUNT	= 0x3,
	BACK_BY_SMALL_AMOUNT	= 0x4
    } 	SCROLLAMOUNT;


EXTERN_C const IID IID_IScrollerCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B653632A-D625-4ffa-9DD3-2775FC09E2E5")
    IScrollerCallback : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerticalScrollCallback( 
            /* [in] */ int nScrollAmount,
            /* [out] */ int *pnPercentScrolled) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HorizontalScrollCallback( 
            /* [in] */ int nScrollAmount,
            /* [out] */ int *pnPercentScrolled) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IScrollerCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IScrollerCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IScrollerCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IScrollerCallback * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerticalScrollCallback )( 
            IScrollerCallback * This,
            /* [in] */ int nScrollAmount,
            /* [out] */ int *pnPercentScrolled);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HorizontalScrollCallback )( 
            IScrollerCallback * This,
            /* [in] */ int nScrollAmount,
            /* [out] */ int *pnPercentScrolled);
        
        END_INTERFACE
    } IScrollerCallbackVtbl;

    interface IScrollerCallback
    {
        CONST_VTBL struct IScrollerCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IScrollerCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IScrollerCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IScrollerCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IScrollerCallback_VerticalScrollCallback(This,nScrollAmount,pnPercentScrolled)	\
    (This)->lpVtbl -> VerticalScrollCallback(This,nScrollAmount,pnPercentScrolled)

#define IScrollerCallback_HorizontalScrollCallback(This,nScrollAmount,pnPercentScrolled)	\
    (This)->lpVtbl -> HorizontalScrollCallback(This,nScrollAmount,pnPercentScrolled)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScrollerCallback_VerticalScrollCallback_Proxy( 
    IScrollerCallback * This,
    /* [in] */ int nScrollAmount,
    /* [out] */ int *pnPercentScrolled);


void __RPC_STUB IScrollerCallback_VerticalScrollCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScrollerCallback_HorizontalScrollCallback_Proxy( 
    IScrollerCallback * This,
    /* [in] */ int nScrollAmount,
    /* [out] */ int *pnPercentScrolled);


void __RPC_STUB IScrollerCallback_HorizontalScrollCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IScrollerCallback_INTERFACE_DEFINED__ */


#ifndef __IAccessibleUia_INTERFACE_DEFINED__
#define __IAccessibleUia_INTERFACE_DEFINED__

/* interface IAccessibleUia */
/* [uuid][object] */ 


EXTERN_C const IID IID_IAccessibleUia;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("37B28BC2-69EB-4aa6-9679-B28376A423D3")
    IAccessibleUia : public IAccessible
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReleaseAllChildren( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRuntimeId( 
            /* [retval][out] */ SAFEARRAY * *ppIdResults) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAutomationId( 
            /* [retval][out] */ BSTR *pbstrAutomationId) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAutomationElement( 
            /* [retval][out] */ VARIANT *automationElement) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetClassName( 
            /* [retval][out] */ BSTR *bstrClassName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFocus( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateScrollPattern( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateScrollItemPattern( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ScrollItemIntoView( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ScrollContainer( 
            /* [in] */ int nOrientation,
            /* [in] */ int nScrollAmount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ScrollPercent( 
            /* [in] */ int nOrientation,
            /* [retval][out] */ double *pdwScrollPercent) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SupportsScrollPattern( 
            /* [retval][out] */ BOOL *pfSupported) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SupportsScrollItemPattern( 
            /* [retval][out] */ BOOL *pfSupported) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReleaseScrollPattern( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReleaseScrollItemPattern( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRangeValue( 
            /* [in] */ int nPercentValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAccessibleUiaVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAccessibleUia * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAccessibleUia * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAccessibleUia * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAccessibleUia * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAccessibleUia * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAccessibleUia * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAccessibleUia * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_accParent )( 
            IAccessibleUia * This,
            /* [retval][out] */ IDispatch **ppdispParent);
        
        /* [id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_accChildCount )( 
            IAccessibleUia * This,
            /* [retval][out] */ long *pcountChildren);
        
        /* [id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_accChild )( 
            IAccessibleUia * This,
            /* [in] */ VARIANT varChild,
            /* [retval][out] */ IDispatch **ppdispChild);
        
        /* [id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_accName )( 
            IAccessibleUia * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR *pszName);
        
        /* [id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_accValue )( 
            IAccessibleUia * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR *pszValue);
        
        /* [id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_accDescription )( 
            IAccessibleUia * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR *pszDescription);
        
        /* [id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_accRole )( 
            IAccessibleUia * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ VARIANT *pvarRole);
        
        /* [id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_accState )( 
            IAccessibleUia * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ VARIANT *pvarState);
        
        /* [id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_accHelp )( 
            IAccessibleUia * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR *pszHelp);
        
        /* [id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_accHelpTopic )( 
            IAccessibleUia * This,
            /* [out] */ BSTR *pszHelpFile,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ long *pidTopic);
        
        /* [id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_accKeyboardShortcut )( 
            IAccessibleUia * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR *pszKeyboardShortcut);
        
        /* [id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_accFocus )( 
            IAccessibleUia * This,
            /* [retval][out] */ VARIANT *pvarChild);
        
        /* [id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_accSelection )( 
            IAccessibleUia * This,
            /* [retval][out] */ VARIANT *pvarChildren);
        
        /* [id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_accDefaultAction )( 
            IAccessibleUia * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR *pszDefaultAction);
        
        /* [id][hidden] */ HRESULT ( STDMETHODCALLTYPE *accSelect )( 
            IAccessibleUia * This,
            /* [in] */ long flagsSelect,
            /* [optional][in] */ VARIANT varChild);
        
        /* [id][hidden] */ HRESULT ( STDMETHODCALLTYPE *accLocation )( 
            IAccessibleUia * This,
            /* [out] */ long *pxLeft,
            /* [out] */ long *pyTop,
            /* [out] */ long *pcxWidth,
            /* [out] */ long *pcyHeight,
            /* [optional][in] */ VARIANT varChild);
        
        /* [id][hidden] */ HRESULT ( STDMETHODCALLTYPE *accNavigate )( 
            IAccessibleUia * This,
            /* [in] */ long navDir,
            /* [optional][in] */ VARIANT varStart,
            /* [retval][out] */ VARIANT *pvarEndUpAt);
        
        /* [id][hidden] */ HRESULT ( STDMETHODCALLTYPE *accHitTest )( 
            IAccessibleUia * This,
            /* [in] */ long xLeft,
            /* [in] */ long yTop,
            /* [retval][out] */ VARIANT *pvarChild);
        
        /* [id][hidden] */ HRESULT ( STDMETHODCALLTYPE *accDoDefaultAction )( 
            IAccessibleUia * This,
            /* [optional][in] */ VARIANT varChild);
        
        /* [id][propput][hidden] */ HRESULT ( STDMETHODCALLTYPE *put_accName )( 
            IAccessibleUia * This,
            /* [optional][in] */ VARIANT varChild,
            /* [in] */ BSTR szName);
        
        /* [id][propput][hidden] */ HRESULT ( STDMETHODCALLTYPE *put_accValue )( 
            IAccessibleUia * This,
            /* [optional][in] */ VARIANT varChild,
            /* [in] */ BSTR szValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReleaseAllChildren )( 
            IAccessibleUia * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRuntimeId )( 
            IAccessibleUia * This,
            /* [retval][out] */ SAFEARRAY * *ppIdResults);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAutomationId )( 
            IAccessibleUia * This,
            /* [retval][out] */ BSTR *pbstrAutomationId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAutomationElement )( 
            IAccessibleUia * This,
            /* [retval][out] */ VARIANT *automationElement);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            IAccessibleUia * This,
            /* [retval][out] */ BSTR *bstrClassName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetFocus )( 
            IAccessibleUia * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateScrollPattern )( 
            IAccessibleUia * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateScrollItemPattern )( 
            IAccessibleUia * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ScrollItemIntoView )( 
            IAccessibleUia * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ScrollContainer )( 
            IAccessibleUia * This,
            /* [in] */ int nOrientation,
            /* [in] */ int nScrollAmount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ScrollPercent )( 
            IAccessibleUia * This,
            /* [in] */ int nOrientation,
            /* [retval][out] */ double *pdwScrollPercent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SupportsScrollPattern )( 
            IAccessibleUia * This,
            /* [retval][out] */ BOOL *pfSupported);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SupportsScrollItemPattern )( 
            IAccessibleUia * This,
            /* [retval][out] */ BOOL *pfSupported);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReleaseScrollPattern )( 
            IAccessibleUia * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReleaseScrollItemPattern )( 
            IAccessibleUia * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetRangeValue )( 
            IAccessibleUia * This,
            /* [in] */ int nPercentValue);
        
        END_INTERFACE
    } IAccessibleUiaVtbl;

    interface IAccessibleUia
    {
        CONST_VTBL struct IAccessibleUiaVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAccessibleUia_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAccessibleUia_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAccessibleUia_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAccessibleUia_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAccessibleUia_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAccessibleUia_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAccessibleUia_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAccessibleUia_get_accParent(This,ppdispParent)	\
    (This)->lpVtbl -> get_accParent(This,ppdispParent)

#define IAccessibleUia_get_accChildCount(This,pcountChildren)	\
    (This)->lpVtbl -> get_accChildCount(This,pcountChildren)

#define IAccessibleUia_get_accChild(This,varChild,ppdispChild)	\
    (This)->lpVtbl -> get_accChild(This,varChild,ppdispChild)

#define IAccessibleUia_get_accName(This,varChild,pszName)	\
    (This)->lpVtbl -> get_accName(This,varChild,pszName)

#define IAccessibleUia_get_accValue(This,varChild,pszValue)	\
    (This)->lpVtbl -> get_accValue(This,varChild,pszValue)

#define IAccessibleUia_get_accDescription(This,varChild,pszDescription)	\
    (This)->lpVtbl -> get_accDescription(This,varChild,pszDescription)

#define IAccessibleUia_get_accRole(This,varChild,pvarRole)	\
    (This)->lpVtbl -> get_accRole(This,varChild,pvarRole)

#define IAccessibleUia_get_accState(This,varChild,pvarState)	\
    (This)->lpVtbl -> get_accState(This,varChild,pvarState)

#define IAccessibleUia_get_accHelp(This,varChild,pszHelp)	\
    (This)->lpVtbl -> get_accHelp(This,varChild,pszHelp)

#define IAccessibleUia_get_accHelpTopic(This,pszHelpFile,varChild,pidTopic)	\
    (This)->lpVtbl -> get_accHelpTopic(This,pszHelpFile,varChild,pidTopic)

#define IAccessibleUia_get_accKeyboardShortcut(This,varChild,pszKeyboardShortcut)	\
    (This)->lpVtbl -> get_accKeyboardShortcut(This,varChild,pszKeyboardShortcut)

#define IAccessibleUia_get_accFocus(This,pvarChild)	\
    (This)->lpVtbl -> get_accFocus(This,pvarChild)

#define IAccessibleUia_get_accSelection(This,pvarChildren)	\
    (This)->lpVtbl -> get_accSelection(This,pvarChildren)

#define IAccessibleUia_get_accDefaultAction(This,varChild,pszDefaultAction)	\
    (This)->lpVtbl -> get_accDefaultAction(This,varChild,pszDefaultAction)

#define IAccessibleUia_accSelect(This,flagsSelect,varChild)	\
    (This)->lpVtbl -> accSelect(This,flagsSelect,varChild)

#define IAccessibleUia_accLocation(This,pxLeft,pyTop,pcxWidth,pcyHeight,varChild)	\
    (This)->lpVtbl -> accLocation(This,pxLeft,pyTop,pcxWidth,pcyHeight,varChild)

#define IAccessibleUia_accNavigate(This,navDir,varStart,pvarEndUpAt)	\
    (This)->lpVtbl -> accNavigate(This,navDir,varStart,pvarEndUpAt)

#define IAccessibleUia_accHitTest(This,xLeft,yTop,pvarChild)	\
    (This)->lpVtbl -> accHitTest(This,xLeft,yTop,pvarChild)

#define IAccessibleUia_accDoDefaultAction(This,varChild)	\
    (This)->lpVtbl -> accDoDefaultAction(This,varChild)

#define IAccessibleUia_put_accName(This,varChild,szName)	\
    (This)->lpVtbl -> put_accName(This,varChild,szName)

#define IAccessibleUia_put_accValue(This,varChild,szValue)	\
    (This)->lpVtbl -> put_accValue(This,varChild,szValue)


#define IAccessibleUia_ReleaseAllChildren(This)	\
    (This)->lpVtbl -> ReleaseAllChildren(This)

#define IAccessibleUia_GetRuntimeId(This,ppIdResults)	\
    (This)->lpVtbl -> GetRuntimeId(This,ppIdResults)

#define IAccessibleUia_GetAutomationId(This,pbstrAutomationId)	\
    (This)->lpVtbl -> GetAutomationId(This,pbstrAutomationId)

#define IAccessibleUia_GetAutomationElement(This,automationElement)	\
    (This)->lpVtbl -> GetAutomationElement(This,automationElement)

#define IAccessibleUia_GetClassName(This,bstrClassName)	\
    (This)->lpVtbl -> GetClassName(This,bstrClassName)

#define IAccessibleUia_SetFocus(This)	\
    (This)->lpVtbl -> SetFocus(This)

#define IAccessibleUia_UpdateScrollPattern(This)	\
    (This)->lpVtbl -> UpdateScrollPattern(This)

#define IAccessibleUia_UpdateScrollItemPattern(This)	\
    (This)->lpVtbl -> UpdateScrollItemPattern(This)

#define IAccessibleUia_ScrollItemIntoView(This)	\
    (This)->lpVtbl -> ScrollItemIntoView(This)

#define IAccessibleUia_ScrollContainer(This,nOrientation,nScrollAmount)	\
    (This)->lpVtbl -> ScrollContainer(This,nOrientation,nScrollAmount)

#define IAccessibleUia_ScrollPercent(This,nOrientation,pdwScrollPercent)	\
    (This)->lpVtbl -> ScrollPercent(This,nOrientation,pdwScrollPercent)

#define IAccessibleUia_SupportsScrollPattern(This,pfSupported)	\
    (This)->lpVtbl -> SupportsScrollPattern(This,pfSupported)

#define IAccessibleUia_SupportsScrollItemPattern(This,pfSupported)	\
    (This)->lpVtbl -> SupportsScrollItemPattern(This,pfSupported)

#define IAccessibleUia_ReleaseScrollPattern(This)	\
    (This)->lpVtbl -> ReleaseScrollPattern(This)

#define IAccessibleUia_ReleaseScrollItemPattern(This)	\
    (This)->lpVtbl -> ReleaseScrollItemPattern(This)

#define IAccessibleUia_SetRangeValue(This,nPercentValue)	\
    (This)->lpVtbl -> SetRangeValue(This,nPercentValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAccessibleUia_ReleaseAllChildren_Proxy( 
    IAccessibleUia * This);


void __RPC_STUB IAccessibleUia_ReleaseAllChildren_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAccessibleUia_GetRuntimeId_Proxy( 
    IAccessibleUia * This,
    /* [retval][out] */ SAFEARRAY * *ppIdResults);


void __RPC_STUB IAccessibleUia_GetRuntimeId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAccessibleUia_GetAutomationId_Proxy( 
    IAccessibleUia * This,
    /* [retval][out] */ BSTR *pbstrAutomationId);


void __RPC_STUB IAccessibleUia_GetAutomationId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAccessibleUia_GetAutomationElement_Proxy( 
    IAccessibleUia * This,
    /* [retval][out] */ VARIANT *automationElement);


void __RPC_STUB IAccessibleUia_GetAutomationElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAccessibleUia_GetClassName_Proxy( 
    IAccessibleUia * This,
    /* [retval][out] */ BSTR *bstrClassName);


void __RPC_STUB IAccessibleUia_GetClassName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAccessibleUia_SetFocus_Proxy( 
    IAccessibleUia * This);


void __RPC_STUB IAccessibleUia_SetFocus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAccessibleUia_UpdateScrollPattern_Proxy( 
    IAccessibleUia * This);


void __RPC_STUB IAccessibleUia_UpdateScrollPattern_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAccessibleUia_UpdateScrollItemPattern_Proxy( 
    IAccessibleUia * This);


void __RPC_STUB IAccessibleUia_UpdateScrollItemPattern_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAccessibleUia_ScrollItemIntoView_Proxy( 
    IAccessibleUia * This);


void __RPC_STUB IAccessibleUia_ScrollItemIntoView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAccessibleUia_ScrollContainer_Proxy( 
    IAccessibleUia * This,
    /* [in] */ int nOrientation,
    /* [in] */ int nScrollAmount);


void __RPC_STUB IAccessibleUia_ScrollContainer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAccessibleUia_ScrollPercent_Proxy( 
    IAccessibleUia * This,
    /* [in] */ int nOrientation,
    /* [retval][out] */ double *pdwScrollPercent);


void __RPC_STUB IAccessibleUia_ScrollPercent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAccessibleUia_SupportsScrollPattern_Proxy( 
    IAccessibleUia * This,
    /* [retval][out] */ BOOL *pfSupported);


void __RPC_STUB IAccessibleUia_SupportsScrollPattern_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAccessibleUia_SupportsScrollItemPattern_Proxy( 
    IAccessibleUia * This,
    /* [retval][out] */ BOOL *pfSupported);


void __RPC_STUB IAccessibleUia_SupportsScrollItemPattern_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAccessibleUia_ReleaseScrollPattern_Proxy( 
    IAccessibleUia * This);


void __RPC_STUB IAccessibleUia_ReleaseScrollPattern_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAccessibleUia_ReleaseScrollItemPattern_Proxy( 
    IAccessibleUia * This);


void __RPC_STUB IAccessibleUia_ReleaseScrollItemPattern_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAccessibleUia_SetRangeValue_Proxy( 
    IAccessibleUia * This,
    /* [in] */ int nPercentValue);


void __RPC_STUB IAccessibleUia_SetRangeValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAccessibleUia_INTERFACE_DEFINED__ */


#ifndef __IAccessibleUiaSupport_INTERFACE_DEFINED__
#define __IAccessibleUiaSupport_INTERFACE_DEFINED__

/* interface IAccessibleUiaSupport */
/* [uuid][object] */ 


EXTERN_C const IID IID_IAccessibleUiaSupport;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D330F2FE-9AA1-4134-94ED-91A72AD387A6")
    IAccessibleUiaSupport : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRPFManagedUiaVersion( 
            /* [out] */ BSTR *pbstrVersion) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AccessibleUiaElementFromPoint( 
            /* [in] */ int x,
            /* [in] */ int y,
            /* [retval][out] */ IAccessibleUia **ppAccessibleUia) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AccessibleUiaFromHwnd( 
            /* [in] */ INT64 hWnd,
            /* [retval][out] */ IAccessibleUia **ppAccessibleUia) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WindowFromAccessibleUia( 
            /* [in] */ IAccessibleUia *pAccessibleUia,
            /* [retval][out] */ INT64 *pHWnd) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAccessibleUiaSupportVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAccessibleUiaSupport * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAccessibleUiaSupport * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAccessibleUiaSupport * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRPFManagedUiaVersion )( 
            IAccessibleUiaSupport * This,
            /* [out] */ BSTR *pbstrVersion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AccessibleUiaElementFromPoint )( 
            IAccessibleUiaSupport * This,
            /* [in] */ int x,
            /* [in] */ int y,
            /* [retval][out] */ IAccessibleUia **ppAccessibleUia);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AccessibleUiaFromHwnd )( 
            IAccessibleUiaSupport * This,
            /* [in] */ INT64 hWnd,
            /* [retval][out] */ IAccessibleUia **ppAccessibleUia);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WindowFromAccessibleUia )( 
            IAccessibleUiaSupport * This,
            /* [in] */ IAccessibleUia *pAccessibleUia,
            /* [retval][out] */ INT64 *pHWnd);
        
        END_INTERFACE
    } IAccessibleUiaSupportVtbl;

    interface IAccessibleUiaSupport
    {
        CONST_VTBL struct IAccessibleUiaSupportVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAccessibleUiaSupport_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAccessibleUiaSupport_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAccessibleUiaSupport_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAccessibleUiaSupport_GetRPFManagedUiaVersion(This,pbstrVersion)	\
    (This)->lpVtbl -> GetRPFManagedUiaVersion(This,pbstrVersion)

#define IAccessibleUiaSupport_AccessibleUiaElementFromPoint(This,x,y,ppAccessibleUia)	\
    (This)->lpVtbl -> AccessibleUiaElementFromPoint(This,x,y,ppAccessibleUia)

#define IAccessibleUiaSupport_AccessibleUiaFromHwnd(This,hWnd,ppAccessibleUia)	\
    (This)->lpVtbl -> AccessibleUiaFromHwnd(This,hWnd,ppAccessibleUia)

#define IAccessibleUiaSupport_WindowFromAccessibleUia(This,pAccessibleUia,pHWnd)	\
    (This)->lpVtbl -> WindowFromAccessibleUia(This,pAccessibleUia,pHWnd)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAccessibleUiaSupport_GetRPFManagedUiaVersion_Proxy( 
    IAccessibleUiaSupport * This,
    /* [out] */ BSTR *pbstrVersion);


void __RPC_STUB IAccessibleUiaSupport_GetRPFManagedUiaVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAccessibleUiaSupport_AccessibleUiaElementFromPoint_Proxy( 
    IAccessibleUiaSupport * This,
    /* [in] */ int x,
    /* [in] */ int y,
    /* [retval][out] */ IAccessibleUia **ppAccessibleUia);


void __RPC_STUB IAccessibleUiaSupport_AccessibleUiaElementFromPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAccessibleUiaSupport_AccessibleUiaFromHwnd_Proxy( 
    IAccessibleUiaSupport * This,
    /* [in] */ INT64 hWnd,
    /* [retval][out] */ IAccessibleUia **ppAccessibleUia);


void __RPC_STUB IAccessibleUiaSupport_AccessibleUiaFromHwnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAccessibleUiaSupport_WindowFromAccessibleUia_Proxy( 
    IAccessibleUiaSupport * This,
    /* [in] */ IAccessibleUia *pAccessibleUia,
    /* [retval][out] */ INT64 *pHWnd);


void __RPC_STUB IAccessibleUiaSupport_WindowFromAccessibleUia_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAccessibleUiaSupport_INTERFACE_DEFINED__ */


#ifndef __IScreenElement_INTERFACE_DEFINED__
#define __IScreenElement_INTERFACE_DEFINED__

/* interface IScreenElement */
/* [unique][helpstring][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IScreenElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E8C80E92-831A-44b3-8236-815A964473F8")
    IScreenElement : public IDispatch
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Accessible( 
            /* [retval][out] */ VARIANT *pvarDisp) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ChildId( 
            /* [retval][out] */ VARIANT *ChildId) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_hWnd( 
            /* [retval][out] */ INT64 *hWnd) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IdentificationString( 
            /* [retval][out] */ BSTR *pbstrIdentificationString) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pbstrName) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ClassName( 
            /* [retval][out] */ BSTR *pbstrClassName) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_RoleText( 
            /* [retval][out] */ BSTR *pbstrRoleText) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ BSTR *pbstrValue) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ BSTR *pbstrState) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IScreenElement **ppScreenElement) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_HTMLElement( 
            /* [retval][out] */ IHTMLElement **ppIHTMLElement) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_AccTechnology( 
            /* [retval][out] */ INT *pnAccTechnology) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LeftButtonClick( 
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ BOOL fEnsureVisible = TRUE,
            /* [defaultvalue][in] */ BSTR bstrKeyModifiers = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoubleClick( 
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ BOOL fEnsureVisible = TRUE,
            /* [defaultvalue][in] */ BSTR bstrKeyModifiers = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RightButtonClick( 
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ BOOL fEnsureVisible = TRUE,
            /* [defaultvalue][in] */ BSTR bstrKeyModifiers = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Expand( 
            /* [defaultvalue][in] */ INT nExpandCollapseFlag = ECF_USE_TVM_EXPAND | ECF_USE_DOUBLECLICK | ECF_USE_NUMPAD | ECF_USE_ENTER) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Check( 
            /* [defaultvalue][in] */ BOOL fSetIndeterminate = FALSE,
            /* [defaultvalue][in] */ BOOL fVerifyFinalState = TRUE) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Collapse( 
            /* [defaultvalue][in] */ INT nExpandCollapseFlag = ECF_USE_TVM_EXPAND | ECF_USE_DOUBLECLICK | ECF_USE_NUMPAD | ECF_USE_ENTER) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnsureVisible( 
            /* [defaultvalue][in] */ int nEnsureVisibleFlag = EVF_BY_SCROLLING,
            /* [defaultvalue][in] */ int x = -1,
            /* [defaultvalue][in] */ int y = -1,
            /* [defaultvalue][in] */ IScrollerCallback *pScrollerCallback = 0,
            /* [defaultvalue][in] */ int nScrollFlag = SF_SCROLL_BAR | SF_WHEEL,
            /* [defaultvalue][in] */ int nMaximumContainers = 2) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Select( 
            /* [defaultvalue][in] */ int nSelectionFlag = 0x2) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendKeys( 
            /* [in] */ BSTR bstrKeys,
            /* [defaultvalue][in] */ INT nKeyboardAction = HIT) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetValueAsComboBox( 
            /* [in] */ BSTR bstrNewValue,
            /* [defaultvalue][in] */ INT nSetValueAsComboBoxFlag = CF_USE_SET_AS_EDIT | CF_USE_SELECT) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetValueAsEditBox( 
            /* [in] */ BSTR bstrNewValue,
            /* [defaultvalue][in] */ INT nSetValueAsEditBoxFlag = EF_DELETE_CONTENT | EF_USE_SENDKEYS) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartDragging( 
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ INT nDraggingButton = LEFT_BUTTON,
            /* [defaultvalue][in] */ BSTR bstrKeyModifiers = 0,
            /* [defaultvalue][in] */ BOOL fEnsureVisible = TRUE) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopDragging( 
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ INT nSpeedPixelPerSecond = DEFAULT_DRAG_SPEED) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MoveMouse( 
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ BOOL fEnsureVisible = TRUE,
            /* [defaultvalue][in] */ INT nSpeedPixelPerSecond = DEFAULT_DRAG_SPEED) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MouseWheel( 
            /* [in] */ INT nDelta,
            /* [defaultvalue][in] */ BSTR bstrKeyModifiers = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Uncheck( 
            /* [defaultvalue][in] */ BOOL fVerifyFinalState = TRUE) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WaitForReady( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BringUp( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerifyScreenElement( 
            /* [in] */ BSTR bstrState,
            /* [in] */ BSTR bstrValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindScreenElementEx( 
            /* [in] */ BSTR bstrQueryId,
            /* [in] */ VARIANT *pvarResKeys,
            /* [in] */ INT cResKeys,
            /* [retval][out] */ IScreenElement **ppScreenElement) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindAllDescendants( 
            /* [in] */ BSTR bstrQueryId,
            /* [in] */ VARIANT *pvarResKeys,
            /* [in] */ INT cResKeys,
            /* [in] */ INT nMaxDepth,
            /* [retval][out] */ SAFEARRAY * *foundDescendants) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WaitForGone( 
            /* [in] */ INT nTimeOut,
            /* [in] */ INT nElapse) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetClickablePoint( 
            /* [out] */ INT *x,
            /* [out] */ INT *y) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsTextTruncated( 
            /* [out] */ BOOL *pfIsTruncated,
            /* [out] */ int *pnNumSymbolsFit) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetValueAsSlider( 
            /* [in] */ BSTR bstrNewValue,
            /* [defaultvalue][in] */ INT nOrientation = DF_AUTO) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetColors( 
            /* [out] */ int *pnTextColor,
            /* [out] */ int *pnBackGroundColor) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBoundingRectangle( 
            /* [out] */ int *pnLeft,
            /* [out] */ int *pnTop,
            /* [out] */ int *pnWidth,
            /* [out] */ int *pnHeight) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Equals( 
            /* [in] */ IScreenElement *pScreenElement,
            /* [retval][out] */ BOOL *pfEquals) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPlaybackFlag( 
            /* [in] */ int nPlaybackFlag,
            /* [retval][out] */ VARIANT *pvarPlaybackFlagValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPlaybackFlag( 
            /* [in] */ int nPlaybackFlag,
            /* [in] */ VARIANT varPlaybackFlagValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MatchesQueryId( 
            /* [in] */ BSTR bstrQueryId,
            /* [retval][out] */ BOOL *pfMatches) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_RunTimeId( 
            /* [retval][out] */ SAFEARRAY * *pRunTimeId) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IScreenElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IScreenElement * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IScreenElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IScreenElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IScreenElement * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IScreenElement * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IScreenElement * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IScreenElement * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Accessible )( 
            IScreenElement * This,
            /* [retval][out] */ VARIANT *pvarDisp);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ChildId )( 
            IScreenElement * This,
            /* [retval][out] */ VARIANT *ChildId);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_hWnd )( 
            IScreenElement * This,
            /* [retval][out] */ INT64 *hWnd);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_IdentificationString )( 
            IScreenElement * This,
            /* [retval][out] */ BSTR *pbstrIdentificationString);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IScreenElement * This,
            /* [retval][out] */ BSTR *pbstrName);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ClassName )( 
            IScreenElement * This,
            /* [retval][out] */ BSTR *pbstrClassName);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_RoleText )( 
            IScreenElement * This,
            /* [retval][out] */ BSTR *pbstrRoleText);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IScreenElement * This,
            /* [retval][out] */ BSTR *pbstrValue);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_State )( 
            IScreenElement * This,
            /* [retval][out] */ BSTR *pbstrState);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            IScreenElement * This,
            /* [retval][out] */ IScreenElement **ppScreenElement);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_HTMLElement )( 
            IScreenElement * This,
            /* [retval][out] */ IHTMLElement **ppIHTMLElement);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_AccTechnology )( 
            IScreenElement * This,
            /* [retval][out] */ INT *pnAccTechnology);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LeftButtonClick )( 
            IScreenElement * This,
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ BOOL fEnsureVisible,
            /* [defaultvalue][in] */ BSTR bstrKeyModifiers);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DoubleClick )( 
            IScreenElement * This,
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ BOOL fEnsureVisible,
            /* [defaultvalue][in] */ BSTR bstrKeyModifiers);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RightButtonClick )( 
            IScreenElement * This,
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ BOOL fEnsureVisible,
            /* [defaultvalue][in] */ BSTR bstrKeyModifiers);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Expand )( 
            IScreenElement * This,
            /* [defaultvalue][in] */ INT nExpandCollapseFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Check )( 
            IScreenElement * This,
            /* [defaultvalue][in] */ BOOL fSetIndeterminate,
            /* [defaultvalue][in] */ BOOL fVerifyFinalState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Collapse )( 
            IScreenElement * This,
            /* [defaultvalue][in] */ INT nExpandCollapseFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnsureVisible )( 
            IScreenElement * This,
            /* [defaultvalue][in] */ int nEnsureVisibleFlag,
            /* [defaultvalue][in] */ int x,
            /* [defaultvalue][in] */ int y,
            /* [defaultvalue][in] */ IScrollerCallback *pScrollerCallback,
            /* [defaultvalue][in] */ int nScrollFlag,
            /* [defaultvalue][in] */ int nMaximumContainers);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Select )( 
            IScreenElement * This,
            /* [defaultvalue][in] */ int nSelectionFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SendKeys )( 
            IScreenElement * This,
            /* [in] */ BSTR bstrKeys,
            /* [defaultvalue][in] */ INT nKeyboardAction);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetValueAsComboBox )( 
            IScreenElement * This,
            /* [in] */ BSTR bstrNewValue,
            /* [defaultvalue][in] */ INT nSetValueAsComboBoxFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetValueAsEditBox )( 
            IScreenElement * This,
            /* [in] */ BSTR bstrNewValue,
            /* [defaultvalue][in] */ INT nSetValueAsEditBoxFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartDragging )( 
            IScreenElement * This,
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ INT nDraggingButton,
            /* [defaultvalue][in] */ BSTR bstrKeyModifiers,
            /* [defaultvalue][in] */ BOOL fEnsureVisible);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopDragging )( 
            IScreenElement * This,
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ INT nSpeedPixelPerSecond);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MoveMouse )( 
            IScreenElement * This,
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ BOOL fEnsureVisible,
            /* [defaultvalue][in] */ INT nSpeedPixelPerSecond);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MouseWheel )( 
            IScreenElement * This,
            /* [in] */ INT nDelta,
            /* [defaultvalue][in] */ BSTR bstrKeyModifiers);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Uncheck )( 
            IScreenElement * This,
            /* [defaultvalue][in] */ BOOL fVerifyFinalState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WaitForReady )( 
            IScreenElement * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BringUp )( 
            IScreenElement * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerifyScreenElement )( 
            IScreenElement * This,
            /* [in] */ BSTR bstrState,
            /* [in] */ BSTR bstrValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindScreenElementEx )( 
            IScreenElement * This,
            /* [in] */ BSTR bstrQueryId,
            /* [in] */ VARIANT *pvarResKeys,
            /* [in] */ INT cResKeys,
            /* [retval][out] */ IScreenElement **ppScreenElement);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindAllDescendants )( 
            IScreenElement * This,
            /* [in] */ BSTR bstrQueryId,
            /* [in] */ VARIANT *pvarResKeys,
            /* [in] */ INT cResKeys,
            /* [in] */ INT nMaxDepth,
            /* [retval][out] */ SAFEARRAY * *foundDescendants);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WaitForGone )( 
            IScreenElement * This,
            /* [in] */ INT nTimeOut,
            /* [in] */ INT nElapse);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetClickablePoint )( 
            IScreenElement * This,
            /* [out] */ INT *x,
            /* [out] */ INT *y);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsTextTruncated )( 
            IScreenElement * This,
            /* [out] */ BOOL *pfIsTruncated,
            /* [out] */ int *pnNumSymbolsFit);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetValueAsSlider )( 
            IScreenElement * This,
            /* [in] */ BSTR bstrNewValue,
            /* [defaultvalue][in] */ INT nOrientation);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetColors )( 
            IScreenElement * This,
            /* [out] */ int *pnTextColor,
            /* [out] */ int *pnBackGroundColor);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetBoundingRectangle )( 
            IScreenElement * This,
            /* [out] */ int *pnLeft,
            /* [out] */ int *pnTop,
            /* [out] */ int *pnWidth,
            /* [out] */ int *pnHeight);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Equals )( 
            IScreenElement * This,
            /* [in] */ IScreenElement *pScreenElement,
            /* [retval][out] */ BOOL *pfEquals);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPlaybackFlag )( 
            IScreenElement * This,
            /* [in] */ int nPlaybackFlag,
            /* [retval][out] */ VARIANT *pvarPlaybackFlagValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPlaybackFlag )( 
            IScreenElement * This,
            /* [in] */ int nPlaybackFlag,
            /* [in] */ VARIANT varPlaybackFlagValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MatchesQueryId )( 
            IScreenElement * This,
            /* [in] */ BSTR bstrQueryId,
            /* [retval][out] */ BOOL *pfMatches);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_RunTimeId )( 
            IScreenElement * This,
            /* [retval][out] */ SAFEARRAY * *pRunTimeId);
        
        END_INTERFACE
    } IScreenElementVtbl;

    interface IScreenElement
    {
        CONST_VTBL struct IScreenElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IScreenElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IScreenElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IScreenElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IScreenElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IScreenElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IScreenElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IScreenElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IScreenElement_get_Accessible(This,pvarDisp)	\
    (This)->lpVtbl -> get_Accessible(This,pvarDisp)

#define IScreenElement_get_ChildId(This,ChildId)	\
    (This)->lpVtbl -> get_ChildId(This,ChildId)

#define IScreenElement_get_hWnd(This,hWnd)	\
    (This)->lpVtbl -> get_hWnd(This,hWnd)

#define IScreenElement_get_IdentificationString(This,pbstrIdentificationString)	\
    (This)->lpVtbl -> get_IdentificationString(This,pbstrIdentificationString)

#define IScreenElement_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define IScreenElement_get_ClassName(This,pbstrClassName)	\
    (This)->lpVtbl -> get_ClassName(This,pbstrClassName)

#define IScreenElement_get_RoleText(This,pbstrRoleText)	\
    (This)->lpVtbl -> get_RoleText(This,pbstrRoleText)

#define IScreenElement_get_Value(This,pbstrValue)	\
    (This)->lpVtbl -> get_Value(This,pbstrValue)

#define IScreenElement_get_State(This,pbstrState)	\
    (This)->lpVtbl -> get_State(This,pbstrState)

#define IScreenElement_get_Parent(This,ppScreenElement)	\
    (This)->lpVtbl -> get_Parent(This,ppScreenElement)

#define IScreenElement_get_HTMLElement(This,ppIHTMLElement)	\
    (This)->lpVtbl -> get_HTMLElement(This,ppIHTMLElement)

#define IScreenElement_get_AccTechnology(This,pnAccTechnology)	\
    (This)->lpVtbl -> get_AccTechnology(This,pnAccTechnology)

#define IScreenElement_LeftButtonClick(This,x,y,fEnsureVisible,bstrKeyModifiers)	\
    (This)->lpVtbl -> LeftButtonClick(This,x,y,fEnsureVisible,bstrKeyModifiers)

#define IScreenElement_DoubleClick(This,x,y,fEnsureVisible,bstrKeyModifiers)	\
    (This)->lpVtbl -> DoubleClick(This,x,y,fEnsureVisible,bstrKeyModifiers)

#define IScreenElement_RightButtonClick(This,x,y,fEnsureVisible,bstrKeyModifiers)	\
    (This)->lpVtbl -> RightButtonClick(This,x,y,fEnsureVisible,bstrKeyModifiers)

#define IScreenElement_Expand(This,nExpandCollapseFlag)	\
    (This)->lpVtbl -> Expand(This,nExpandCollapseFlag)

#define IScreenElement_Check(This,fSetIndeterminate,fVerifyFinalState)	\
    (This)->lpVtbl -> Check(This,fSetIndeterminate,fVerifyFinalState)

#define IScreenElement_Collapse(This,nExpandCollapseFlag)	\
    (This)->lpVtbl -> Collapse(This,nExpandCollapseFlag)

#define IScreenElement_EnsureVisible(This,nEnsureVisibleFlag,x,y,pScrollerCallback,nScrollFlag,nMaximumContainers)	\
    (This)->lpVtbl -> EnsureVisible(This,nEnsureVisibleFlag,x,y,pScrollerCallback,nScrollFlag,nMaximumContainers)

#define IScreenElement_Select(This,nSelectionFlag)	\
    (This)->lpVtbl -> Select(This,nSelectionFlag)

#define IScreenElement_SendKeys(This,bstrKeys,nKeyboardAction)	\
    (This)->lpVtbl -> SendKeys(This,bstrKeys,nKeyboardAction)

#define IScreenElement_SetValueAsComboBox(This,bstrNewValue,nSetValueAsComboBoxFlag)	\
    (This)->lpVtbl -> SetValueAsComboBox(This,bstrNewValue,nSetValueAsComboBoxFlag)

#define IScreenElement_SetValueAsEditBox(This,bstrNewValue,nSetValueAsEditBoxFlag)	\
    (This)->lpVtbl -> SetValueAsEditBox(This,bstrNewValue,nSetValueAsEditBoxFlag)

#define IScreenElement_StartDragging(This,x,y,nDraggingButton,bstrKeyModifiers,fEnsureVisible)	\
    (This)->lpVtbl -> StartDragging(This,x,y,nDraggingButton,bstrKeyModifiers,fEnsureVisible)

#define IScreenElement_StopDragging(This,x,y,nSpeedPixelPerSecond)	\
    (This)->lpVtbl -> StopDragging(This,x,y,nSpeedPixelPerSecond)

#define IScreenElement_MoveMouse(This,x,y,fEnsureVisible,nSpeedPixelPerSecond)	\
    (This)->lpVtbl -> MoveMouse(This,x,y,fEnsureVisible,nSpeedPixelPerSecond)

#define IScreenElement_MouseWheel(This,nDelta,bstrKeyModifiers)	\
    (This)->lpVtbl -> MouseWheel(This,nDelta,bstrKeyModifiers)

#define IScreenElement_Uncheck(This,fVerifyFinalState)	\
    (This)->lpVtbl -> Uncheck(This,fVerifyFinalState)

#define IScreenElement_WaitForReady(This)	\
    (This)->lpVtbl -> WaitForReady(This)

#define IScreenElement_BringUp(This)	\
    (This)->lpVtbl -> BringUp(This)

#define IScreenElement_VerifyScreenElement(This,bstrState,bstrValue)	\
    (This)->lpVtbl -> VerifyScreenElement(This,bstrState,bstrValue)

#define IScreenElement_FindScreenElementEx(This,bstrQueryId,pvarResKeys,cResKeys,ppScreenElement)	\
    (This)->lpVtbl -> FindScreenElementEx(This,bstrQueryId,pvarResKeys,cResKeys,ppScreenElement)

#define IScreenElement_FindAllDescendants(This,bstrQueryId,pvarResKeys,cResKeys,nMaxDepth,foundDescendants)	\
    (This)->lpVtbl -> FindAllDescendants(This,bstrQueryId,pvarResKeys,cResKeys,nMaxDepth,foundDescendants)

#define IScreenElement_WaitForGone(This,nTimeOut,nElapse)	\
    (This)->lpVtbl -> WaitForGone(This,nTimeOut,nElapse)

#define IScreenElement_GetClickablePoint(This,x,y)	\
    (This)->lpVtbl -> GetClickablePoint(This,x,y)

#define IScreenElement_IsTextTruncated(This,pfIsTruncated,pnNumSymbolsFit)	\
    (This)->lpVtbl -> IsTextTruncated(This,pfIsTruncated,pnNumSymbolsFit)

#define IScreenElement_SetValueAsSlider(This,bstrNewValue,nOrientation)	\
    (This)->lpVtbl -> SetValueAsSlider(This,bstrNewValue,nOrientation)

#define IScreenElement_GetColors(This,pnTextColor,pnBackGroundColor)	\
    (This)->lpVtbl -> GetColors(This,pnTextColor,pnBackGroundColor)

#define IScreenElement_GetBoundingRectangle(This,pnLeft,pnTop,pnWidth,pnHeight)	\
    (This)->lpVtbl -> GetBoundingRectangle(This,pnLeft,pnTop,pnWidth,pnHeight)

#define IScreenElement_Equals(This,pScreenElement,pfEquals)	\
    (This)->lpVtbl -> Equals(This,pScreenElement,pfEquals)

#define IScreenElement_GetPlaybackFlag(This,nPlaybackFlag,pvarPlaybackFlagValue)	\
    (This)->lpVtbl -> GetPlaybackFlag(This,nPlaybackFlag,pvarPlaybackFlagValue)

#define IScreenElement_SetPlaybackFlag(This,nPlaybackFlag,varPlaybackFlagValue)	\
    (This)->lpVtbl -> SetPlaybackFlag(This,nPlaybackFlag,varPlaybackFlagValue)

#define IScreenElement_MatchesQueryId(This,bstrQueryId,pfMatches)	\
    (This)->lpVtbl -> MatchesQueryId(This,bstrQueryId,pfMatches)

#define IScreenElement_get_RunTimeId(This,pRunTimeId)	\
    (This)->lpVtbl -> get_RunTimeId(This,pRunTimeId)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_get_Accessible_Proxy( 
    IScreenElement * This,
    /* [retval][out] */ VARIANT *pvarDisp);


void __RPC_STUB IScreenElement_get_Accessible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_get_ChildId_Proxy( 
    IScreenElement * This,
    /* [retval][out] */ VARIANT *ChildId);


void __RPC_STUB IScreenElement_get_ChildId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_get_hWnd_Proxy( 
    IScreenElement * This,
    /* [retval][out] */ INT64 *hWnd);


void __RPC_STUB IScreenElement_get_hWnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_get_IdentificationString_Proxy( 
    IScreenElement * This,
    /* [retval][out] */ BSTR *pbstrIdentificationString);


void __RPC_STUB IScreenElement_get_IdentificationString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_get_Name_Proxy( 
    IScreenElement * This,
    /* [retval][out] */ BSTR *pbstrName);


void __RPC_STUB IScreenElement_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_get_ClassName_Proxy( 
    IScreenElement * This,
    /* [retval][out] */ BSTR *pbstrClassName);


void __RPC_STUB IScreenElement_get_ClassName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_get_RoleText_Proxy( 
    IScreenElement * This,
    /* [retval][out] */ BSTR *pbstrRoleText);


void __RPC_STUB IScreenElement_get_RoleText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_get_Value_Proxy( 
    IScreenElement * This,
    /* [retval][out] */ BSTR *pbstrValue);


void __RPC_STUB IScreenElement_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_get_State_Proxy( 
    IScreenElement * This,
    /* [retval][out] */ BSTR *pbstrState);


void __RPC_STUB IScreenElement_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_get_Parent_Proxy( 
    IScreenElement * This,
    /* [retval][out] */ IScreenElement **ppScreenElement);


void __RPC_STUB IScreenElement_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_get_HTMLElement_Proxy( 
    IScreenElement * This,
    /* [retval][out] */ IHTMLElement **ppIHTMLElement);


void __RPC_STUB IScreenElement_get_HTMLElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_get_AccTechnology_Proxy( 
    IScreenElement * This,
    /* [retval][out] */ INT *pnAccTechnology);


void __RPC_STUB IScreenElement_get_AccTechnology_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_LeftButtonClick_Proxy( 
    IScreenElement * This,
    /* [in] */ INT x,
    /* [in] */ INT y,
    /* [defaultvalue][in] */ BOOL fEnsureVisible,
    /* [defaultvalue][in] */ BSTR bstrKeyModifiers);


void __RPC_STUB IScreenElement_LeftButtonClick_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_DoubleClick_Proxy( 
    IScreenElement * This,
    /* [in] */ INT x,
    /* [in] */ INT y,
    /* [defaultvalue][in] */ BOOL fEnsureVisible,
    /* [defaultvalue][in] */ BSTR bstrKeyModifiers);


void __RPC_STUB IScreenElement_DoubleClick_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_RightButtonClick_Proxy( 
    IScreenElement * This,
    /* [in] */ INT x,
    /* [in] */ INT y,
    /* [defaultvalue][in] */ BOOL fEnsureVisible,
    /* [defaultvalue][in] */ BSTR bstrKeyModifiers);


void __RPC_STUB IScreenElement_RightButtonClick_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_Expand_Proxy( 
    IScreenElement * This,
    /* [defaultvalue][in] */ INT nExpandCollapseFlag);


void __RPC_STUB IScreenElement_Expand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_Check_Proxy( 
    IScreenElement * This,
    /* [defaultvalue][in] */ BOOL fSetIndeterminate,
    /* [defaultvalue][in] */ BOOL fVerifyFinalState);


void __RPC_STUB IScreenElement_Check_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_Collapse_Proxy( 
    IScreenElement * This,
    /* [defaultvalue][in] */ INT nExpandCollapseFlag);


void __RPC_STUB IScreenElement_Collapse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_EnsureVisible_Proxy( 
    IScreenElement * This,
    /* [defaultvalue][in] */ int nEnsureVisibleFlag,
    /* [defaultvalue][in] */ int x,
    /* [defaultvalue][in] */ int y,
    /* [defaultvalue][in] */ IScrollerCallback *pScrollerCallback,
    /* [defaultvalue][in] */ int nScrollFlag,
    /* [defaultvalue][in] */ int nMaximumContainers);


void __RPC_STUB IScreenElement_EnsureVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_Select_Proxy( 
    IScreenElement * This,
    /* [defaultvalue][in] */ int nSelectionFlag);


void __RPC_STUB IScreenElement_Select_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_SendKeys_Proxy( 
    IScreenElement * This,
    /* [in] */ BSTR bstrKeys,
    /* [defaultvalue][in] */ INT nKeyboardAction);


void __RPC_STUB IScreenElement_SendKeys_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_SetValueAsComboBox_Proxy( 
    IScreenElement * This,
    /* [in] */ BSTR bstrNewValue,
    /* [defaultvalue][in] */ INT nSetValueAsComboBoxFlag);


void __RPC_STUB IScreenElement_SetValueAsComboBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_SetValueAsEditBox_Proxy( 
    IScreenElement * This,
    /* [in] */ BSTR bstrNewValue,
    /* [defaultvalue][in] */ INT nSetValueAsEditBoxFlag);


void __RPC_STUB IScreenElement_SetValueAsEditBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_StartDragging_Proxy( 
    IScreenElement * This,
    /* [in] */ INT x,
    /* [in] */ INT y,
    /* [defaultvalue][in] */ INT nDraggingButton,
    /* [defaultvalue][in] */ BSTR bstrKeyModifiers,
    /* [defaultvalue][in] */ BOOL fEnsureVisible);


void __RPC_STUB IScreenElement_StartDragging_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_StopDragging_Proxy( 
    IScreenElement * This,
    /* [in] */ INT x,
    /* [in] */ INT y,
    /* [defaultvalue][in] */ INT nSpeedPixelPerSecond);


void __RPC_STUB IScreenElement_StopDragging_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_MoveMouse_Proxy( 
    IScreenElement * This,
    /* [in] */ INT x,
    /* [in] */ INT y,
    /* [defaultvalue][in] */ BOOL fEnsureVisible,
    /* [defaultvalue][in] */ INT nSpeedPixelPerSecond);


void __RPC_STUB IScreenElement_MoveMouse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_MouseWheel_Proxy( 
    IScreenElement * This,
    /* [in] */ INT nDelta,
    /* [defaultvalue][in] */ BSTR bstrKeyModifiers);


void __RPC_STUB IScreenElement_MouseWheel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_Uncheck_Proxy( 
    IScreenElement * This,
    /* [defaultvalue][in] */ BOOL fVerifyFinalState);


void __RPC_STUB IScreenElement_Uncheck_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_WaitForReady_Proxy( 
    IScreenElement * This);


void __RPC_STUB IScreenElement_WaitForReady_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_BringUp_Proxy( 
    IScreenElement * This);


void __RPC_STUB IScreenElement_BringUp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_VerifyScreenElement_Proxy( 
    IScreenElement * This,
    /* [in] */ BSTR bstrState,
    /* [in] */ BSTR bstrValue);


void __RPC_STUB IScreenElement_VerifyScreenElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_FindScreenElementEx_Proxy( 
    IScreenElement * This,
    /* [in] */ BSTR bstrQueryId,
    /* [in] */ VARIANT *pvarResKeys,
    /* [in] */ INT cResKeys,
    /* [retval][out] */ IScreenElement **ppScreenElement);


void __RPC_STUB IScreenElement_FindScreenElementEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_FindAllDescendants_Proxy( 
    IScreenElement * This,
    /* [in] */ BSTR bstrQueryId,
    /* [in] */ VARIANT *pvarResKeys,
    /* [in] */ INT cResKeys,
    /* [in] */ INT nMaxDepth,
    /* [retval][out] */ SAFEARRAY * *foundDescendants);


void __RPC_STUB IScreenElement_FindAllDescendants_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_WaitForGone_Proxy( 
    IScreenElement * This,
    /* [in] */ INT nTimeOut,
    /* [in] */ INT nElapse);


void __RPC_STUB IScreenElement_WaitForGone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_GetClickablePoint_Proxy( 
    IScreenElement * This,
    /* [out] */ INT *x,
    /* [out] */ INT *y);


void __RPC_STUB IScreenElement_GetClickablePoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_IsTextTruncated_Proxy( 
    IScreenElement * This,
    /* [out] */ BOOL *pfIsTruncated,
    /* [out] */ int *pnNumSymbolsFit);


void __RPC_STUB IScreenElement_IsTextTruncated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_SetValueAsSlider_Proxy( 
    IScreenElement * This,
    /* [in] */ BSTR bstrNewValue,
    /* [defaultvalue][in] */ INT nOrientation);


void __RPC_STUB IScreenElement_SetValueAsSlider_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_GetColors_Proxy( 
    IScreenElement * This,
    /* [out] */ int *pnTextColor,
    /* [out] */ int *pnBackGroundColor);


void __RPC_STUB IScreenElement_GetColors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_GetBoundingRectangle_Proxy( 
    IScreenElement * This,
    /* [out] */ int *pnLeft,
    /* [out] */ int *pnTop,
    /* [out] */ int *pnWidth,
    /* [out] */ int *pnHeight);


void __RPC_STUB IScreenElement_GetBoundingRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_Equals_Proxy( 
    IScreenElement * This,
    /* [in] */ IScreenElement *pScreenElement,
    /* [retval][out] */ BOOL *pfEquals);


void __RPC_STUB IScreenElement_Equals_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_GetPlaybackFlag_Proxy( 
    IScreenElement * This,
    /* [in] */ int nPlaybackFlag,
    /* [retval][out] */ VARIANT *pvarPlaybackFlagValue);


void __RPC_STUB IScreenElement_GetPlaybackFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_SetPlaybackFlag_Proxy( 
    IScreenElement * This,
    /* [in] */ int nPlaybackFlag,
    /* [in] */ VARIANT varPlaybackFlagValue);


void __RPC_STUB IScreenElement_SetPlaybackFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_MatchesQueryId_Proxy( 
    IScreenElement * This,
    /* [in] */ BSTR bstrQueryId,
    /* [retval][out] */ BOOL *pfMatches);


void __RPC_STUB IScreenElement_MatchesQueryId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IScreenElement_get_RunTimeId_Proxy( 
    IScreenElement * This,
    /* [retval][out] */ SAFEARRAY * *pRunTimeId);


void __RPC_STUB IScreenElement_get_RunTimeId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IScreenElement_INTERFACE_DEFINED__ */


#ifndef __IRPFPlayback_INTERFACE_DEFINED__
#define __IRPFPlayback_INTERFACE_DEFINED__

/* interface IRPFPlayback */
/* [unique][helpstring][oleautomation][dual][uuid][object] */ 

typedef 
enum ThreadWaitReason
    {	ComponentOfTheWindowsNTExecutive1	= 0,
	PageToBeFreed	= 1,
	PageToBeMappedOrCopied	= 2,
	SpaceToBeAllocatedInThePagedOrNonpagedPool	= 3,
	ExecutionDelayToBeresolved1	= 4,
	Suspended1	= 5,
	UserRequest1	= 6,
	ComponentOfTheWindowsNTExecutive2	= 7,
	PageToBefreed	= 8,
	PageToBemappedOrCopied	= 9,
	SpaceToBeallocatedInThePagedOrNonpagedPool	= 10,
	ExecutionDelayToBeresolved2	= 11,
	Suspended2	= 12,
	UserRequest2	= 13,
	EentPairHigh	= 14,
	EventPairLow	= 15,
	LPCReceiveNotice	= 16,
	LPCReplyNotice	= 17,
	VirtualMemoryToBeAllocated	= 18,
	PageToBewrittenToDisk	= 19,
	Reserved	= 20
    } 	THREAD_WAIT_REASON;


EXTERN_C const IID IID_IRPFPlayback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C1478314-93FB-4ca8-9554-7D2DAAC0D15A")
    IRPFPlayback : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitPlayBack( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitPlayBackForTargetWindow( 
            /* [in] */ BSTR bstrMainWindowClass,
            /* [in] */ BSTR bstrMainWindowCaption,
            /* [in] */ BOOL fShowInfoWindow) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitPlayBackForTargetProcess( 
            /* [in] */ INT nTargetProcessId,
            /* [in] */ INT64 hWndTargetMainWindow,
            /* [in] */ BOOL fShowInfoWindow) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitPlayBackForTargetExecutable( 
            /* [in] */ BSTR bstrExecutablePath,
            /* [in] */ BOOL fShowInfoWindow) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FinishPlayBack( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindScreenElementEx( 
            /* [in] */ IScreenElement *pScreenElementStart,
            /* [in] */ BSTR bstrQueryId,
            /* [in] */ VARIANT *pvarResKeys,
            /* [in] */ INT cResKeys,
            /* [retval][out] */ IScreenElement **ppScreenElement) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindScreenElement( 
            /* [in] */ BSTR bstrQueryId,
            /* [retval][out] */ IScreenElement **ppScreenElement) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindAllScreenElements( 
            /* [in] */ IScreenElement *pScreenElementStart,
            /* [in] */ BSTR bstrQueryId,
            /* [in] */ VARIANT *pvarResKeys,
            /* [in] */ INT cResKeys,
            /* [in] */ INT nMaxDepth,
            /* [out] */ SAFEARRAY * *foundDescendants) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LeftButtonClick( 
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ BOOL fEnsureVisible = TRUE,
            /* [defaultvalue][in] */ BSTR bstrKeyModifiers = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoubleClick( 
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ BOOL fEnsureVisible = TRUE,
            /* [defaultvalue][in] */ BSTR bstrKeyModifiers = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RightButtonClick( 
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ BOOL fEnsureVisible = TRUE,
            /* [defaultvalue][in] */ BSTR bstrKeyModifiers = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Expand( 
            /* [defaultvalue][in] */ INT nExpandCollapseFlag = ECF_USE_TVM_EXPAND | ECF_USE_DOUBLECLICK | ECF_USE_NUMPAD | ECF_USE_ENTER) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Check( 
            /* [defaultvalue][in] */ BOOL fSetIndeterminate = FALSE,
            /* [defaultvalue][in] */ BOOL fVerifyFinalState = TRUE) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Collapse( 
            /* [defaultvalue][in] */ INT nExpandCollapseFlag = ECF_USE_TVM_EXPAND | ECF_USE_DOUBLECLICK | ECF_USE_NUMPAD | ECF_USE_ENTER) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnsureVisible( 
            /* [defaultvalue][in] */ int nEnsureVisibleFlag = EVF_BY_SCROLLING,
            /* [defaultvalue][in] */ int x = -1,
            /* [defaultvalue][in] */ int y = -1,
            /* [defaultvalue][in] */ IScrollerCallback *pScrollerCallback = 0,
            /* [defaultvalue][in] */ int nScrollFlag = SF_SCROLL_BAR | SF_WHEEL,
            /* [defaultvalue][in] */ int nMaximumContainers = 2) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Select( 
            /* [defaultvalue][in] */ int nSelectionFlag = 0x2) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendKeys( 
            /* [in] */ BSTR bstrKeys,
            /* [defaultvalue][in] */ INT nKeyboardAction = HIT) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetValueAsComboBox( 
            /* [in] */ BSTR bstrNewValue,
            /* [defaultvalue][in] */ INT nSetValueAsComboBoxFlag = CF_USE_SET_AS_EDIT | CF_USE_SELECT) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetValueAsEditBox( 
            /* [in] */ BSTR bstrNewValue,
            /* [defaultvalue][in] */ INT nSetValueAsEditBoxFlag = EF_DELETE_CONTENT | EF_USE_SENDKEYS) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartDragging( 
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ INT nDraggingButton = LEFT_BUTTON,
            /* [defaultvalue][in] */ BSTR bstrKeyModifiers = 0,
            /* [defaultvalue][in] */ BOOL fEnsureVisible = TRUE) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopDragging( 
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ INT nSpeedPixelPerSecond = DEFAULT_DRAG_SPEED) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MoveMouse( 
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ BOOL fEnsureVisible = TRUE,
            /* [defaultvalue][in] */ INT nSpeedPixelPerSecond = DEFAULT_DRAG_SPEED) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MouseWheel( 
            /* [in] */ INT nDelta,
            /* [defaultvalue][in] */ BSTR bstrKeyModifiers = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Uncheck( 
            /* [defaultvalue][in] */ BOOL fVerifyFinalState = TRUE) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WaitForReady( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerifyScreenElement( 
            /* [in] */ BSTR bstrState,
            /* [in] */ BSTR bstrValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BringScreenElementUp( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TypeString( 
            /* [in] */ BSTR bstrKeys,
            /* [defaultvalue][in] */ int nSleepBetweenActions = DEFAULT_TYPING_DELAY,
            /* [defaultvalue][in] */ BOOL fbLiteral = FALSE,
            /* [defaultvalue][in] */ INT nKeyboardAction = HIT) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WaitForScreenElementGone( 
            /* [in] */ INT nTimeOut,
            /* [in] */ INT nElapse) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetClickablePoint( 
            /* [out] */ INT *x,
            /* [out] */ INT *y) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnableInfoWindow( 
            /* [in] */ BOOL fEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnableEnsureVisibleForPrimitive( 
            /* [in] */ BOOL fEnable,
            /* [retval][out] */ BOOL *pfPreviousFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDebugMode( 
            /* [in] */ INT nDebuggingLevel) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVerificationFlag( 
            /* [in] */ int nVerificationFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRobustnessLevel( 
            /* [in] */ int nRobustnessLevel) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetLoggingFlag( 
            /* [in] */ int nLoggingFlag,
            /* [retval][out] */ int *nPreviousLoggingFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRobustnessLevelEx( 
            /* [in] */ int nRobustnessLevel,
            /* [in] */ BOOL fSystemWide,
            /* [in] */ INT nWaitForReadyMode,
            /* [in] */ BSTR bstrBackGroundThreadStates,
            /* [in] */ BSTR bstrBackGroundThreadWaitReasons,
            /* [defaultvalue][in] */ BSTR bstrForeGroundThreadStates = 0,
            /* [defaultvalue][in] */ BSTR bstrForeGroundThreadWaitReasons = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSearchTimeOut( 
            /* [in] */ INT nSearchTimeOut,
            /* [retval][out] */ INT *nPreviousSearchTimeOut) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LockNextSearches( 
            /* [in] */ BOOL bLock) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddMonitoringInfo( 
            /* [in] */ IMonitoringWindowsCallback *pMonitoringWindowsCallback) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartMonitoringWindows( 
            /* [in] */ int nElapse) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopMonitoringWindows( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCustomLogger( 
            /* [in] */ ILoggerCallback *pLoggerCallback) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LogStep( 
            /* [in] */ HRESULT hr,
            /* [in] */ BSTR lpstFunction) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LogInformation( 
            /* [in] */ BSTR bstrMessage,
            /* [in] */ BOOL fDeleteFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetClipBoard( 
            /* [in] */ BSTR bstrClipBoardString) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetClipBoard( 
            /* [retval][out] */ BSTR *pbstrClipBoardString) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TerminateProcessByModuleName( 
            /* [in] */ BSTR bstrModuleName,
            /* [in] */ int nExitCode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTargetProcess( 
            /* [in] */ INT nTargetProcessId,
            /* [out] */ INT *nCurrentTargetProcessId) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TerminateTargetProcess( 
            /* [in] */ int nTargetProcessId) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BringUpMainWindow( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ScreenElementFromPoint( 
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [retval][out] */ IScreenElement **ppScreenElement) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ScreenElementFromWindow( 
            /* [in] */ INT64 hWnd,
            /* [retval][out] */ IScreenElement **ppScreenElement) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ScreenElementFromAccessibleObject( 
            /* [in] */ VARIANT varDisp,
            /* [in] */ VARIANT varChildId,
            /* [retval][out] */ IScreenElement **ppScreenElement) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ScreenElementFromHTMLElement( 
            IHTMLElement *pIHTMLElement,
            /* [retval][out] */ IScreenElement **ppScreenElement) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ScreenElementFromWinEvent( 
            /* [retval][out] */ IScreenElement **ppScreenElement) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartWaitingForAnyWinEvent( 
            /* [in] */ SAFEARRAY * pWinEventsHandles,
            /* [in] */ INT cWinEventHandles) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetValueAsSlider( 
            /* [in] */ BSTR bstrNewValue,
            /* [defaultvalue][in] */ INT nOrientation = DF_AUTO) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DumpScreen( 
            /* [in] */ BSTR bstrFileName,
            /* [defaultvalue][in] */ INT nFileFormat = DUMP_SCREEN_JPEG) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WaitForCursor( 
            /* [in] */ INT hInstance,
            /* [in] */ BOOL fWaitForAnyCursor,
            /* [in] */ INT nElapse,
            /* [in] */ INT nTimeOut,
            /* [in] */ SAFEARRAY * pnCursors,
            /* [in] */ INT cCursors) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCurrentCursor( 
            /* [in] */ INT hInstance,
            /* [out] */ INT *nCursor) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLastFailures( 
            /* [retval][out] */ BSTR *pbstrLastFalures) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExtractResourceString( 
            /* [in] */ BSTR resourceKey,
            /* [retval][out] */ BSTR *pbstrResourceString) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetNextActionDelay( 
            /* [in] */ int nDelayTime) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCurrentUsers( 
            /* [in] */ BSTR bstrCurrentUsers) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAccTechnology( 
            /* [in] */ int nAccTechnology) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnableUISynchronization( 
            /* [in] */ BOOL fEnableUISync) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPlaybackProperty( 
            /* [in] */ int nParam,
            /* [retval][out] */ VARIANT *pVarParamValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPlaybackProperty( 
            /* [in] */ int nParam,
            /* [in] */ VARIANT varParamValue) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_PlaybackVersion( 
            /* [retval][out] */ BSTR *pbstrPlaybackVersion) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GlobalizeQueryId( 
            /* [in] */ BSTR bstrQueryId,
            /* [in] */ VARIANT *pvarResKeys,
            /* [in] */ INT cResKeys,
            /* [retval][out] */ BSTR *pbstrGlobalizedQueryId) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_TargetLanguageId( 
            /* [in] */ int nTargetLanguageId) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_TargetLanguageName( 
            /* [in] */ BSTR bstrTargetLanguageName) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_MUILanguageId( 
            /* [in] */ int nTMUILanguageId) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_ResFilesDirectories( 
            /* [in] */ BSTR bstrResFilesDirectories) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRPFPlaybackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRPFPlayback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRPFPlayback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRPFPlayback * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IRPFPlayback * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IRPFPlayback * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IRPFPlayback * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IRPFPlayback * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitPlayBack )( 
            IRPFPlayback * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitPlayBackForTargetWindow )( 
            IRPFPlayback * This,
            /* [in] */ BSTR bstrMainWindowClass,
            /* [in] */ BSTR bstrMainWindowCaption,
            /* [in] */ BOOL fShowInfoWindow);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitPlayBackForTargetProcess )( 
            IRPFPlayback * This,
            /* [in] */ INT nTargetProcessId,
            /* [in] */ INT64 hWndTargetMainWindow,
            /* [in] */ BOOL fShowInfoWindow);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitPlayBackForTargetExecutable )( 
            IRPFPlayback * This,
            /* [in] */ BSTR bstrExecutablePath,
            /* [in] */ BOOL fShowInfoWindow);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FinishPlayBack )( 
            IRPFPlayback * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindScreenElementEx )( 
            IRPFPlayback * This,
            /* [in] */ IScreenElement *pScreenElementStart,
            /* [in] */ BSTR bstrQueryId,
            /* [in] */ VARIANT *pvarResKeys,
            /* [in] */ INT cResKeys,
            /* [retval][out] */ IScreenElement **ppScreenElement);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindScreenElement )( 
            IRPFPlayback * This,
            /* [in] */ BSTR bstrQueryId,
            /* [retval][out] */ IScreenElement **ppScreenElement);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindAllScreenElements )( 
            IRPFPlayback * This,
            /* [in] */ IScreenElement *pScreenElementStart,
            /* [in] */ BSTR bstrQueryId,
            /* [in] */ VARIANT *pvarResKeys,
            /* [in] */ INT cResKeys,
            /* [in] */ INT nMaxDepth,
            /* [out] */ SAFEARRAY * *foundDescendants);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LeftButtonClick )( 
            IRPFPlayback * This,
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ BOOL fEnsureVisible,
            /* [defaultvalue][in] */ BSTR bstrKeyModifiers);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DoubleClick )( 
            IRPFPlayback * This,
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ BOOL fEnsureVisible,
            /* [defaultvalue][in] */ BSTR bstrKeyModifiers);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RightButtonClick )( 
            IRPFPlayback * This,
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ BOOL fEnsureVisible,
            /* [defaultvalue][in] */ BSTR bstrKeyModifiers);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Expand )( 
            IRPFPlayback * This,
            /* [defaultvalue][in] */ INT nExpandCollapseFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Check )( 
            IRPFPlayback * This,
            /* [defaultvalue][in] */ BOOL fSetIndeterminate,
            /* [defaultvalue][in] */ BOOL fVerifyFinalState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Collapse )( 
            IRPFPlayback * This,
            /* [defaultvalue][in] */ INT nExpandCollapseFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnsureVisible )( 
            IRPFPlayback * This,
            /* [defaultvalue][in] */ int nEnsureVisibleFlag,
            /* [defaultvalue][in] */ int x,
            /* [defaultvalue][in] */ int y,
            /* [defaultvalue][in] */ IScrollerCallback *pScrollerCallback,
            /* [defaultvalue][in] */ int nScrollFlag,
            /* [defaultvalue][in] */ int nMaximumContainers);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Select )( 
            IRPFPlayback * This,
            /* [defaultvalue][in] */ int nSelectionFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SendKeys )( 
            IRPFPlayback * This,
            /* [in] */ BSTR bstrKeys,
            /* [defaultvalue][in] */ INT nKeyboardAction);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetValueAsComboBox )( 
            IRPFPlayback * This,
            /* [in] */ BSTR bstrNewValue,
            /* [defaultvalue][in] */ INT nSetValueAsComboBoxFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetValueAsEditBox )( 
            IRPFPlayback * This,
            /* [in] */ BSTR bstrNewValue,
            /* [defaultvalue][in] */ INT nSetValueAsEditBoxFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartDragging )( 
            IRPFPlayback * This,
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ INT nDraggingButton,
            /* [defaultvalue][in] */ BSTR bstrKeyModifiers,
            /* [defaultvalue][in] */ BOOL fEnsureVisible);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopDragging )( 
            IRPFPlayback * This,
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ INT nSpeedPixelPerSecond);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MoveMouse )( 
            IRPFPlayback * This,
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [defaultvalue][in] */ BOOL fEnsureVisible,
            /* [defaultvalue][in] */ INT nSpeedPixelPerSecond);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MouseWheel )( 
            IRPFPlayback * This,
            /* [in] */ INT nDelta,
            /* [defaultvalue][in] */ BSTR bstrKeyModifiers);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Uncheck )( 
            IRPFPlayback * This,
            /* [defaultvalue][in] */ BOOL fVerifyFinalState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WaitForReady )( 
            IRPFPlayback * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerifyScreenElement )( 
            IRPFPlayback * This,
            /* [in] */ BSTR bstrState,
            /* [in] */ BSTR bstrValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BringScreenElementUp )( 
            IRPFPlayback * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TypeString )( 
            IRPFPlayback * This,
            /* [in] */ BSTR bstrKeys,
            /* [defaultvalue][in] */ int nSleepBetweenActions,
            /* [defaultvalue][in] */ BOOL fbLiteral,
            /* [defaultvalue][in] */ INT nKeyboardAction);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WaitForScreenElementGone )( 
            IRPFPlayback * This,
            /* [in] */ INT nTimeOut,
            /* [in] */ INT nElapse);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetClickablePoint )( 
            IRPFPlayback * This,
            /* [out] */ INT *x,
            /* [out] */ INT *y);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnableInfoWindow )( 
            IRPFPlayback * This,
            /* [in] */ BOOL fEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnableEnsureVisibleForPrimitive )( 
            IRPFPlayback * This,
            /* [in] */ BOOL fEnable,
            /* [retval][out] */ BOOL *pfPreviousFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDebugMode )( 
            IRPFPlayback * This,
            /* [in] */ INT nDebuggingLevel);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetVerificationFlag )( 
            IRPFPlayback * This,
            /* [in] */ int nVerificationFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetRobustnessLevel )( 
            IRPFPlayback * This,
            /* [in] */ int nRobustnessLevel);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetLoggingFlag )( 
            IRPFPlayback * This,
            /* [in] */ int nLoggingFlag,
            /* [retval][out] */ int *nPreviousLoggingFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetRobustnessLevelEx )( 
            IRPFPlayback * This,
            /* [in] */ int nRobustnessLevel,
            /* [in] */ BOOL fSystemWide,
            /* [in] */ INT nWaitForReadyMode,
            /* [in] */ BSTR bstrBackGroundThreadStates,
            /* [in] */ BSTR bstrBackGroundThreadWaitReasons,
            /* [defaultvalue][in] */ BSTR bstrForeGroundThreadStates,
            /* [defaultvalue][in] */ BSTR bstrForeGroundThreadWaitReasons);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSearchTimeOut )( 
            IRPFPlayback * This,
            /* [in] */ INT nSearchTimeOut,
            /* [retval][out] */ INT *nPreviousSearchTimeOut);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LockNextSearches )( 
            IRPFPlayback * This,
            /* [in] */ BOOL bLock);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddMonitoringInfo )( 
            IRPFPlayback * This,
            /* [in] */ IMonitoringWindowsCallback *pMonitoringWindowsCallback);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartMonitoringWindows )( 
            IRPFPlayback * This,
            /* [in] */ int nElapse);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopMonitoringWindows )( 
            IRPFPlayback * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCustomLogger )( 
            IRPFPlayback * This,
            /* [in] */ ILoggerCallback *pLoggerCallback);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LogStep )( 
            IRPFPlayback * This,
            /* [in] */ HRESULT hr,
            /* [in] */ BSTR lpstFunction);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LogInformation )( 
            IRPFPlayback * This,
            /* [in] */ BSTR bstrMessage,
            /* [in] */ BOOL fDeleteFile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetClipBoard )( 
            IRPFPlayback * This,
            /* [in] */ BSTR bstrClipBoardString);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetClipBoard )( 
            IRPFPlayback * This,
            /* [retval][out] */ BSTR *pbstrClipBoardString);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TerminateProcessByModuleName )( 
            IRPFPlayback * This,
            /* [in] */ BSTR bstrModuleName,
            /* [in] */ int nExitCode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetTargetProcess )( 
            IRPFPlayback * This,
            /* [in] */ INT nTargetProcessId,
            /* [out] */ INT *nCurrentTargetProcessId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TerminateTargetProcess )( 
            IRPFPlayback * This,
            /* [in] */ int nTargetProcessId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BringUpMainWindow )( 
            IRPFPlayback * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ScreenElementFromPoint )( 
            IRPFPlayback * This,
            /* [in] */ INT x,
            /* [in] */ INT y,
            /* [retval][out] */ IScreenElement **ppScreenElement);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ScreenElementFromWindow )( 
            IRPFPlayback * This,
            /* [in] */ INT64 hWnd,
            /* [retval][out] */ IScreenElement **ppScreenElement);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ScreenElementFromAccessibleObject )( 
            IRPFPlayback * This,
            /* [in] */ VARIANT varDisp,
            /* [in] */ VARIANT varChildId,
            /* [retval][out] */ IScreenElement **ppScreenElement);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ScreenElementFromHTMLElement )( 
            IRPFPlayback * This,
            IHTMLElement *pIHTMLElement,
            /* [retval][out] */ IScreenElement **ppScreenElement);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ScreenElementFromWinEvent )( 
            IRPFPlayback * This,
            /* [retval][out] */ IScreenElement **ppScreenElement);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartWaitingForAnyWinEvent )( 
            IRPFPlayback * This,
            /* [in] */ SAFEARRAY * pWinEventsHandles,
            /* [in] */ INT cWinEventHandles);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetValueAsSlider )( 
            IRPFPlayback * This,
            /* [in] */ BSTR bstrNewValue,
            /* [defaultvalue][in] */ INT nOrientation);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DumpScreen )( 
            IRPFPlayback * This,
            /* [in] */ BSTR bstrFileName,
            /* [defaultvalue][in] */ INT nFileFormat);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WaitForCursor )( 
            IRPFPlayback * This,
            /* [in] */ INT hInstance,
            /* [in] */ BOOL fWaitForAnyCursor,
            /* [in] */ INT nElapse,
            /* [in] */ INT nTimeOut,
            /* [in] */ SAFEARRAY * pnCursors,
            /* [in] */ INT cCursors);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCurrentCursor )( 
            IRPFPlayback * This,
            /* [in] */ INT hInstance,
            /* [out] */ INT *nCursor);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLastFailures )( 
            IRPFPlayback * This,
            /* [retval][out] */ BSTR *pbstrLastFalures);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ExtractResourceString )( 
            IRPFPlayback * This,
            /* [in] */ BSTR resourceKey,
            /* [retval][out] */ BSTR *pbstrResourceString);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetNextActionDelay )( 
            IRPFPlayback * This,
            /* [in] */ int nDelayTime);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCurrentUsers )( 
            IRPFPlayback * This,
            /* [in] */ BSTR bstrCurrentUsers);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAccTechnology )( 
            IRPFPlayback * This,
            /* [in] */ int nAccTechnology);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnableUISynchronization )( 
            IRPFPlayback * This,
            /* [in] */ BOOL fEnableUISync);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPlaybackProperty )( 
            IRPFPlayback * This,
            /* [in] */ int nParam,
            /* [retval][out] */ VARIANT *pVarParamValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPlaybackProperty )( 
            IRPFPlayback * This,
            /* [in] */ int nParam,
            /* [in] */ VARIANT varParamValue);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_PlaybackVersion )( 
            IRPFPlayback * This,
            /* [retval][out] */ BSTR *pbstrPlaybackVersion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GlobalizeQueryId )( 
            IRPFPlayback * This,
            /* [in] */ BSTR bstrQueryId,
            /* [in] */ VARIANT *pvarResKeys,
            /* [in] */ INT cResKeys,
            /* [retval][out] */ BSTR *pbstrGlobalizedQueryId);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_TargetLanguageId )( 
            IRPFPlayback * This,
            /* [in] */ int nTargetLanguageId);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_TargetLanguageName )( 
            IRPFPlayback * This,
            /* [in] */ BSTR bstrTargetLanguageName);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_MUILanguageId )( 
            IRPFPlayback * This,
            /* [in] */ int nTMUILanguageId);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ResFilesDirectories )( 
            IRPFPlayback * This,
            /* [in] */ BSTR bstrResFilesDirectories);
        
        END_INTERFACE
    } IRPFPlaybackVtbl;

    interface IRPFPlayback
    {
        CONST_VTBL struct IRPFPlaybackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRPFPlayback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRPFPlayback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRPFPlayback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRPFPlayback_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRPFPlayback_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRPFPlayback_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRPFPlayback_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRPFPlayback_InitPlayBack(This)	\
    (This)->lpVtbl -> InitPlayBack(This)

#define IRPFPlayback_InitPlayBackForTargetWindow(This,bstrMainWindowClass,bstrMainWindowCaption,fShowInfoWindow)	\
    (This)->lpVtbl -> InitPlayBackForTargetWindow(This,bstrMainWindowClass,bstrMainWindowCaption,fShowInfoWindow)

#define IRPFPlayback_InitPlayBackForTargetProcess(This,nTargetProcessId,hWndTargetMainWindow,fShowInfoWindow)	\
    (This)->lpVtbl -> InitPlayBackForTargetProcess(This,nTargetProcessId,hWndTargetMainWindow,fShowInfoWindow)

#define IRPFPlayback_InitPlayBackForTargetExecutable(This,bstrExecutablePath,fShowInfoWindow)	\
    (This)->lpVtbl -> InitPlayBackForTargetExecutable(This,bstrExecutablePath,fShowInfoWindow)

#define IRPFPlayback_FinishPlayBack(This)	\
    (This)->lpVtbl -> FinishPlayBack(This)

#define IRPFPlayback_FindScreenElementEx(This,pScreenElementStart,bstrQueryId,pvarResKeys,cResKeys,ppScreenElement)	\
    (This)->lpVtbl -> FindScreenElementEx(This,pScreenElementStart,bstrQueryId,pvarResKeys,cResKeys,ppScreenElement)

#define IRPFPlayback_FindScreenElement(This,bstrQueryId,ppScreenElement)	\
    (This)->lpVtbl -> FindScreenElement(This,bstrQueryId,ppScreenElement)

#define IRPFPlayback_FindAllScreenElements(This,pScreenElementStart,bstrQueryId,pvarResKeys,cResKeys,nMaxDepth,foundDescendants)	\
    (This)->lpVtbl -> FindAllScreenElements(This,pScreenElementStart,bstrQueryId,pvarResKeys,cResKeys,nMaxDepth,foundDescendants)

#define IRPFPlayback_LeftButtonClick(This,x,y,fEnsureVisible,bstrKeyModifiers)	\
    (This)->lpVtbl -> LeftButtonClick(This,x,y,fEnsureVisible,bstrKeyModifiers)

#define IRPFPlayback_DoubleClick(This,x,y,fEnsureVisible,bstrKeyModifiers)	\
    (This)->lpVtbl -> DoubleClick(This,x,y,fEnsureVisible,bstrKeyModifiers)

#define IRPFPlayback_RightButtonClick(This,x,y,fEnsureVisible,bstrKeyModifiers)	\
    (This)->lpVtbl -> RightButtonClick(This,x,y,fEnsureVisible,bstrKeyModifiers)

#define IRPFPlayback_Expand(This,nExpandCollapseFlag)	\
    (This)->lpVtbl -> Expand(This,nExpandCollapseFlag)

#define IRPFPlayback_Check(This,fSetIndeterminate,fVerifyFinalState)	\
    (This)->lpVtbl -> Check(This,fSetIndeterminate,fVerifyFinalState)

#define IRPFPlayback_Collapse(This,nExpandCollapseFlag)	\
    (This)->lpVtbl -> Collapse(This,nExpandCollapseFlag)

#define IRPFPlayback_EnsureVisible(This,nEnsureVisibleFlag,x,y,pScrollerCallback,nScrollFlag,nMaximumContainers)	\
    (This)->lpVtbl -> EnsureVisible(This,nEnsureVisibleFlag,x,y,pScrollerCallback,nScrollFlag,nMaximumContainers)

#define IRPFPlayback_Select(This,nSelectionFlag)	\
    (This)->lpVtbl -> Select(This,nSelectionFlag)

#define IRPFPlayback_SendKeys(This,bstrKeys,nKeyboardAction)	\
    (This)->lpVtbl -> SendKeys(This,bstrKeys,nKeyboardAction)

#define IRPFPlayback_SetValueAsComboBox(This,bstrNewValue,nSetValueAsComboBoxFlag)	\
    (This)->lpVtbl -> SetValueAsComboBox(This,bstrNewValue,nSetValueAsComboBoxFlag)

#define IRPFPlayback_SetValueAsEditBox(This,bstrNewValue,nSetValueAsEditBoxFlag)	\
    (This)->lpVtbl -> SetValueAsEditBox(This,bstrNewValue,nSetValueAsEditBoxFlag)

#define IRPFPlayback_StartDragging(This,x,y,nDraggingButton,bstrKeyModifiers,fEnsureVisible)	\
    (This)->lpVtbl -> StartDragging(This,x,y,nDraggingButton,bstrKeyModifiers,fEnsureVisible)

#define IRPFPlayback_StopDragging(This,x,y,nSpeedPixelPerSecond)	\
    (This)->lpVtbl -> StopDragging(This,x,y,nSpeedPixelPerSecond)

#define IRPFPlayback_MoveMouse(This,x,y,fEnsureVisible,nSpeedPixelPerSecond)	\
    (This)->lpVtbl -> MoveMouse(This,x,y,fEnsureVisible,nSpeedPixelPerSecond)

#define IRPFPlayback_MouseWheel(This,nDelta,bstrKeyModifiers)	\
    (This)->lpVtbl -> MouseWheel(This,nDelta,bstrKeyModifiers)

#define IRPFPlayback_Uncheck(This,fVerifyFinalState)	\
    (This)->lpVtbl -> Uncheck(This,fVerifyFinalState)

#define IRPFPlayback_WaitForReady(This)	\
    (This)->lpVtbl -> WaitForReady(This)

#define IRPFPlayback_VerifyScreenElement(This,bstrState,bstrValue)	\
    (This)->lpVtbl -> VerifyScreenElement(This,bstrState,bstrValue)

#define IRPFPlayback_BringScreenElementUp(This)	\
    (This)->lpVtbl -> BringScreenElementUp(This)

#define IRPFPlayback_TypeString(This,bstrKeys,nSleepBetweenActions,fbLiteral,nKeyboardAction)	\
    (This)->lpVtbl -> TypeString(This,bstrKeys,nSleepBetweenActions,fbLiteral,nKeyboardAction)

#define IRPFPlayback_WaitForScreenElementGone(This,nTimeOut,nElapse)	\
    (This)->lpVtbl -> WaitForScreenElementGone(This,nTimeOut,nElapse)

#define IRPFPlayback_GetClickablePoint(This,x,y)	\
    (This)->lpVtbl -> GetClickablePoint(This,x,y)

#define IRPFPlayback_EnableInfoWindow(This,fEnable)	\
    (This)->lpVtbl -> EnableInfoWindow(This,fEnable)

#define IRPFPlayback_EnableEnsureVisibleForPrimitive(This,fEnable,pfPreviousFlag)	\
    (This)->lpVtbl -> EnableEnsureVisibleForPrimitive(This,fEnable,pfPreviousFlag)

#define IRPFPlayback_SetDebugMode(This,nDebuggingLevel)	\
    (This)->lpVtbl -> SetDebugMode(This,nDebuggingLevel)

#define IRPFPlayback_SetVerificationFlag(This,nVerificationFlag)	\
    (This)->lpVtbl -> SetVerificationFlag(This,nVerificationFlag)

#define IRPFPlayback_SetRobustnessLevel(This,nRobustnessLevel)	\
    (This)->lpVtbl -> SetRobustnessLevel(This,nRobustnessLevel)

#define IRPFPlayback_SetLoggingFlag(This,nLoggingFlag,nPreviousLoggingFlag)	\
    (This)->lpVtbl -> SetLoggingFlag(This,nLoggingFlag,nPreviousLoggingFlag)

#define IRPFPlayback_SetRobustnessLevelEx(This,nRobustnessLevel,fSystemWide,nWaitForReadyMode,bstrBackGroundThreadStates,bstrBackGroundThreadWaitReasons,bstrForeGroundThreadStates,bstrForeGroundThreadWaitReasons)	\
    (This)->lpVtbl -> SetRobustnessLevelEx(This,nRobustnessLevel,fSystemWide,nWaitForReadyMode,bstrBackGroundThreadStates,bstrBackGroundThreadWaitReasons,bstrForeGroundThreadStates,bstrForeGroundThreadWaitReasons)

#define IRPFPlayback_SetSearchTimeOut(This,nSearchTimeOut,nPreviousSearchTimeOut)	\
    (This)->lpVtbl -> SetSearchTimeOut(This,nSearchTimeOut,nPreviousSearchTimeOut)

#define IRPFPlayback_LockNextSearches(This,bLock)	\
    (This)->lpVtbl -> LockNextSearches(This,bLock)

#define IRPFPlayback_AddMonitoringInfo(This,pMonitoringWindowsCallback)	\
    (This)->lpVtbl -> AddMonitoringInfo(This,pMonitoringWindowsCallback)

#define IRPFPlayback_StartMonitoringWindows(This,nElapse)	\
    (This)->lpVtbl -> StartMonitoringWindows(This,nElapse)

#define IRPFPlayback_StopMonitoringWindows(This)	\
    (This)->lpVtbl -> StopMonitoringWindows(This)

#define IRPFPlayback_SetCustomLogger(This,pLoggerCallback)	\
    (This)->lpVtbl -> SetCustomLogger(This,pLoggerCallback)

#define IRPFPlayback_LogStep(This,hr,lpstFunction)	\
    (This)->lpVtbl -> LogStep(This,hr,lpstFunction)

#define IRPFPlayback_LogInformation(This,bstrMessage,fDeleteFile)	\
    (This)->lpVtbl -> LogInformation(This,bstrMessage,fDeleteFile)

#define IRPFPlayback_SetClipBoard(This,bstrClipBoardString)	\
    (This)->lpVtbl -> SetClipBoard(This,bstrClipBoardString)

#define IRPFPlayback_GetClipBoard(This,pbstrClipBoardString)	\
    (This)->lpVtbl -> GetClipBoard(This,pbstrClipBoardString)

#define IRPFPlayback_TerminateProcessByModuleName(This,bstrModuleName,nExitCode)	\
    (This)->lpVtbl -> TerminateProcessByModuleName(This,bstrModuleName,nExitCode)

#define IRPFPlayback_SetTargetProcess(This,nTargetProcessId,nCurrentTargetProcessId)	\
    (This)->lpVtbl -> SetTargetProcess(This,nTargetProcessId,nCurrentTargetProcessId)

#define IRPFPlayback_TerminateTargetProcess(This,nTargetProcessId)	\
    (This)->lpVtbl -> TerminateTargetProcess(This,nTargetProcessId)

#define IRPFPlayback_BringUpMainWindow(This)	\
    (This)->lpVtbl -> BringUpMainWindow(This)

#define IRPFPlayback_ScreenElementFromPoint(This,x,y,ppScreenElement)	\
    (This)->lpVtbl -> ScreenElementFromPoint(This,x,y,ppScreenElement)

#define IRPFPlayback_ScreenElementFromWindow(This,hWnd,ppScreenElement)	\
    (This)->lpVtbl -> ScreenElementFromWindow(This,hWnd,ppScreenElement)

#define IRPFPlayback_ScreenElementFromAccessibleObject(This,varDisp,varChildId,ppScreenElement)	\
    (This)->lpVtbl -> ScreenElementFromAccessibleObject(This,varDisp,varChildId,ppScreenElement)

#define IRPFPlayback_ScreenElementFromHTMLElement(This,pIHTMLElement,ppScreenElement)	\
    (This)->lpVtbl -> ScreenElementFromHTMLElement(This,pIHTMLElement,ppScreenElement)

#define IRPFPlayback_ScreenElementFromWinEvent(This,ppScreenElement)	\
    (This)->lpVtbl -> ScreenElementFromWinEvent(This,ppScreenElement)

#define IRPFPlayback_StartWaitingForAnyWinEvent(This,pWinEventsHandles,cWinEventHandles)	\
    (This)->lpVtbl -> StartWaitingForAnyWinEvent(This,pWinEventsHandles,cWinEventHandles)

#define IRPFPlayback_SetValueAsSlider(This,bstrNewValue,nOrientation)	\
    (This)->lpVtbl -> SetValueAsSlider(This,bstrNewValue,nOrientation)

#define IRPFPlayback_DumpScreen(This,bstrFileName,nFileFormat)	\
    (This)->lpVtbl -> DumpScreen(This,bstrFileName,nFileFormat)

#define IRPFPlayback_WaitForCursor(This,hInstance,fWaitForAnyCursor,nElapse,nTimeOut,pnCursors,cCursors)	\
    (This)->lpVtbl -> WaitForCursor(This,hInstance,fWaitForAnyCursor,nElapse,nTimeOut,pnCursors,cCursors)

#define IRPFPlayback_GetCurrentCursor(This,hInstance,nCursor)	\
    (This)->lpVtbl -> GetCurrentCursor(This,hInstance,nCursor)

#define IRPFPlayback_GetLastFailures(This,pbstrLastFalures)	\
    (This)->lpVtbl -> GetLastFailures(This,pbstrLastFalures)

#define IRPFPlayback_ExtractResourceString(This,resourceKey,pbstrResourceString)	\
    (This)->lpVtbl -> ExtractResourceString(This,resourceKey,pbstrResourceString)

#define IRPFPlayback_SetNextActionDelay(This,nDelayTime)	\
    (This)->lpVtbl -> SetNextActionDelay(This,nDelayTime)

#define IRPFPlayback_SetCurrentUsers(This,bstrCurrentUsers)	\
    (This)->lpVtbl -> SetCurrentUsers(This,bstrCurrentUsers)

#define IRPFPlayback_SetAccTechnology(This,nAccTechnology)	\
    (This)->lpVtbl -> SetAccTechnology(This,nAccTechnology)

#define IRPFPlayback_EnableUISynchronization(This,fEnableUISync)	\
    (This)->lpVtbl -> EnableUISynchronization(This,fEnableUISync)

#define IRPFPlayback_GetPlaybackProperty(This,nParam,pVarParamValue)	\
    (This)->lpVtbl -> GetPlaybackProperty(This,nParam,pVarParamValue)

#define IRPFPlayback_SetPlaybackProperty(This,nParam,varParamValue)	\
    (This)->lpVtbl -> SetPlaybackProperty(This,nParam,varParamValue)

#define IRPFPlayback_get_PlaybackVersion(This,pbstrPlaybackVersion)	\
    (This)->lpVtbl -> get_PlaybackVersion(This,pbstrPlaybackVersion)

#define IRPFPlayback_GlobalizeQueryId(This,bstrQueryId,pvarResKeys,cResKeys,pbstrGlobalizedQueryId)	\
    (This)->lpVtbl -> GlobalizeQueryId(This,bstrQueryId,pvarResKeys,cResKeys,pbstrGlobalizedQueryId)

#define IRPFPlayback_put_TargetLanguageId(This,nTargetLanguageId)	\
    (This)->lpVtbl -> put_TargetLanguageId(This,nTargetLanguageId)

#define IRPFPlayback_put_TargetLanguageName(This,bstrTargetLanguageName)	\
    (This)->lpVtbl -> put_TargetLanguageName(This,bstrTargetLanguageName)

#define IRPFPlayback_put_MUILanguageId(This,nTMUILanguageId)	\
    (This)->lpVtbl -> put_MUILanguageId(This,nTMUILanguageId)

#define IRPFPlayback_put_ResFilesDirectories(This,bstrResFilesDirectories)	\
    (This)->lpVtbl -> put_ResFilesDirectories(This,bstrResFilesDirectories)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_InitPlayBack_Proxy( 
    IRPFPlayback * This);


void __RPC_STUB IRPFPlayback_InitPlayBack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_InitPlayBackForTargetWindow_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BSTR bstrMainWindowClass,
    /* [in] */ BSTR bstrMainWindowCaption,
    /* [in] */ BOOL fShowInfoWindow);


void __RPC_STUB IRPFPlayback_InitPlayBackForTargetWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_InitPlayBackForTargetProcess_Proxy( 
    IRPFPlayback * This,
    /* [in] */ INT nTargetProcessId,
    /* [in] */ INT64 hWndTargetMainWindow,
    /* [in] */ BOOL fShowInfoWindow);


void __RPC_STUB IRPFPlayback_InitPlayBackForTargetProcess_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_InitPlayBackForTargetExecutable_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BSTR bstrExecutablePath,
    /* [in] */ BOOL fShowInfoWindow);


void __RPC_STUB IRPFPlayback_InitPlayBackForTargetExecutable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_FinishPlayBack_Proxy( 
    IRPFPlayback * This);


void __RPC_STUB IRPFPlayback_FinishPlayBack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_FindScreenElementEx_Proxy( 
    IRPFPlayback * This,
    /* [in] */ IScreenElement *pScreenElementStart,
    /* [in] */ BSTR bstrQueryId,
    /* [in] */ VARIANT *pvarResKeys,
    /* [in] */ INT cResKeys,
    /* [retval][out] */ IScreenElement **ppScreenElement);


void __RPC_STUB IRPFPlayback_FindScreenElementEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_FindScreenElement_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BSTR bstrQueryId,
    /* [retval][out] */ IScreenElement **ppScreenElement);


void __RPC_STUB IRPFPlayback_FindScreenElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_FindAllScreenElements_Proxy( 
    IRPFPlayback * This,
    /* [in] */ IScreenElement *pScreenElementStart,
    /* [in] */ BSTR bstrQueryId,
    /* [in] */ VARIANT *pvarResKeys,
    /* [in] */ INT cResKeys,
    /* [in] */ INT nMaxDepth,
    /* [out] */ SAFEARRAY * *foundDescendants);


void __RPC_STUB IRPFPlayback_FindAllScreenElements_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_LeftButtonClick_Proxy( 
    IRPFPlayback * This,
    /* [in] */ INT x,
    /* [in] */ INT y,
    /* [defaultvalue][in] */ BOOL fEnsureVisible,
    /* [defaultvalue][in] */ BSTR bstrKeyModifiers);


void __RPC_STUB IRPFPlayback_LeftButtonClick_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_DoubleClick_Proxy( 
    IRPFPlayback * This,
    /* [in] */ INT x,
    /* [in] */ INT y,
    /* [defaultvalue][in] */ BOOL fEnsureVisible,
    /* [defaultvalue][in] */ BSTR bstrKeyModifiers);


void __RPC_STUB IRPFPlayback_DoubleClick_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_RightButtonClick_Proxy( 
    IRPFPlayback * This,
    /* [in] */ INT x,
    /* [in] */ INT y,
    /* [defaultvalue][in] */ BOOL fEnsureVisible,
    /* [defaultvalue][in] */ BSTR bstrKeyModifiers);


void __RPC_STUB IRPFPlayback_RightButtonClick_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_Expand_Proxy( 
    IRPFPlayback * This,
    /* [defaultvalue][in] */ INT nExpandCollapseFlag);


void __RPC_STUB IRPFPlayback_Expand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_Check_Proxy( 
    IRPFPlayback * This,
    /* [defaultvalue][in] */ BOOL fSetIndeterminate,
    /* [defaultvalue][in] */ BOOL fVerifyFinalState);


void __RPC_STUB IRPFPlayback_Check_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_Collapse_Proxy( 
    IRPFPlayback * This,
    /* [defaultvalue][in] */ INT nExpandCollapseFlag);


void __RPC_STUB IRPFPlayback_Collapse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_EnsureVisible_Proxy( 
    IRPFPlayback * This,
    /* [defaultvalue][in] */ int nEnsureVisibleFlag,
    /* [defaultvalue][in] */ int x,
    /* [defaultvalue][in] */ int y,
    /* [defaultvalue][in] */ IScrollerCallback *pScrollerCallback,
    /* [defaultvalue][in] */ int nScrollFlag,
    /* [defaultvalue][in] */ int nMaximumContainers);


void __RPC_STUB IRPFPlayback_EnsureVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_Select_Proxy( 
    IRPFPlayback * This,
    /* [defaultvalue][in] */ int nSelectionFlag);


void __RPC_STUB IRPFPlayback_Select_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_SendKeys_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BSTR bstrKeys,
    /* [defaultvalue][in] */ INT nKeyboardAction);


void __RPC_STUB IRPFPlayback_SendKeys_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_SetValueAsComboBox_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BSTR bstrNewValue,
    /* [defaultvalue][in] */ INT nSetValueAsComboBoxFlag);


void __RPC_STUB IRPFPlayback_SetValueAsComboBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_SetValueAsEditBox_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BSTR bstrNewValue,
    /* [defaultvalue][in] */ INT nSetValueAsEditBoxFlag);


void __RPC_STUB IRPFPlayback_SetValueAsEditBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_StartDragging_Proxy( 
    IRPFPlayback * This,
    /* [in] */ INT x,
    /* [in] */ INT y,
    /* [defaultvalue][in] */ INT nDraggingButton,
    /* [defaultvalue][in] */ BSTR bstrKeyModifiers,
    /* [defaultvalue][in] */ BOOL fEnsureVisible);


void __RPC_STUB IRPFPlayback_StartDragging_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_StopDragging_Proxy( 
    IRPFPlayback * This,
    /* [in] */ INT x,
    /* [in] */ INT y,
    /* [defaultvalue][in] */ INT nSpeedPixelPerSecond);


void __RPC_STUB IRPFPlayback_StopDragging_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_MoveMouse_Proxy( 
    IRPFPlayback * This,
    /* [in] */ INT x,
    /* [in] */ INT y,
    /* [defaultvalue][in] */ BOOL fEnsureVisible,
    /* [defaultvalue][in] */ INT nSpeedPixelPerSecond);


void __RPC_STUB IRPFPlayback_MoveMouse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_MouseWheel_Proxy( 
    IRPFPlayback * This,
    /* [in] */ INT nDelta,
    /* [defaultvalue][in] */ BSTR bstrKeyModifiers);


void __RPC_STUB IRPFPlayback_MouseWheel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_Uncheck_Proxy( 
    IRPFPlayback * This,
    /* [defaultvalue][in] */ BOOL fVerifyFinalState);


void __RPC_STUB IRPFPlayback_Uncheck_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_WaitForReady_Proxy( 
    IRPFPlayback * This);


void __RPC_STUB IRPFPlayback_WaitForReady_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_VerifyScreenElement_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BSTR bstrState,
    /* [in] */ BSTR bstrValue);


void __RPC_STUB IRPFPlayback_VerifyScreenElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_BringScreenElementUp_Proxy( 
    IRPFPlayback * This);


void __RPC_STUB IRPFPlayback_BringScreenElementUp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_TypeString_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BSTR bstrKeys,
    /* [defaultvalue][in] */ int nSleepBetweenActions,
    /* [defaultvalue][in] */ BOOL fbLiteral,
    /* [defaultvalue][in] */ INT nKeyboardAction);


void __RPC_STUB IRPFPlayback_TypeString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_WaitForScreenElementGone_Proxy( 
    IRPFPlayback * This,
    /* [in] */ INT nTimeOut,
    /* [in] */ INT nElapse);


void __RPC_STUB IRPFPlayback_WaitForScreenElementGone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_GetClickablePoint_Proxy( 
    IRPFPlayback * This,
    /* [out] */ INT *x,
    /* [out] */ INT *y);


void __RPC_STUB IRPFPlayback_GetClickablePoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_EnableInfoWindow_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BOOL fEnable);


void __RPC_STUB IRPFPlayback_EnableInfoWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_EnableEnsureVisibleForPrimitive_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BOOL fEnable,
    /* [retval][out] */ BOOL *pfPreviousFlag);


void __RPC_STUB IRPFPlayback_EnableEnsureVisibleForPrimitive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_SetDebugMode_Proxy( 
    IRPFPlayback * This,
    /* [in] */ INT nDebuggingLevel);


void __RPC_STUB IRPFPlayback_SetDebugMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_SetVerificationFlag_Proxy( 
    IRPFPlayback * This,
    /* [in] */ int nVerificationFlag);


void __RPC_STUB IRPFPlayback_SetVerificationFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_SetRobustnessLevel_Proxy( 
    IRPFPlayback * This,
    /* [in] */ int nRobustnessLevel);


void __RPC_STUB IRPFPlayback_SetRobustnessLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_SetLoggingFlag_Proxy( 
    IRPFPlayback * This,
    /* [in] */ int nLoggingFlag,
    /* [retval][out] */ int *nPreviousLoggingFlag);


void __RPC_STUB IRPFPlayback_SetLoggingFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_SetRobustnessLevelEx_Proxy( 
    IRPFPlayback * This,
    /* [in] */ int nRobustnessLevel,
    /* [in] */ BOOL fSystemWide,
    /* [in] */ INT nWaitForReadyMode,
    /* [in] */ BSTR bstrBackGroundThreadStates,
    /* [in] */ BSTR bstrBackGroundThreadWaitReasons,
    /* [defaultvalue][in] */ BSTR bstrForeGroundThreadStates,
    /* [defaultvalue][in] */ BSTR bstrForeGroundThreadWaitReasons);


void __RPC_STUB IRPFPlayback_SetRobustnessLevelEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_SetSearchTimeOut_Proxy( 
    IRPFPlayback * This,
    /* [in] */ INT nSearchTimeOut,
    /* [retval][out] */ INT *nPreviousSearchTimeOut);


void __RPC_STUB IRPFPlayback_SetSearchTimeOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_LockNextSearches_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BOOL bLock);


void __RPC_STUB IRPFPlayback_LockNextSearches_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_AddMonitoringInfo_Proxy( 
    IRPFPlayback * This,
    /* [in] */ IMonitoringWindowsCallback *pMonitoringWindowsCallback);


void __RPC_STUB IRPFPlayback_AddMonitoringInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_StartMonitoringWindows_Proxy( 
    IRPFPlayback * This,
    /* [in] */ int nElapse);


void __RPC_STUB IRPFPlayback_StartMonitoringWindows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_StopMonitoringWindows_Proxy( 
    IRPFPlayback * This);


void __RPC_STUB IRPFPlayback_StopMonitoringWindows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_SetCustomLogger_Proxy( 
    IRPFPlayback * This,
    /* [in] */ ILoggerCallback *pLoggerCallback);


void __RPC_STUB IRPFPlayback_SetCustomLogger_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_LogStep_Proxy( 
    IRPFPlayback * This,
    /* [in] */ HRESULT hr,
    /* [in] */ BSTR lpstFunction);


void __RPC_STUB IRPFPlayback_LogStep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_LogInformation_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BSTR bstrMessage,
    /* [in] */ BOOL fDeleteFile);


void __RPC_STUB IRPFPlayback_LogInformation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_SetClipBoard_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BSTR bstrClipBoardString);


void __RPC_STUB IRPFPlayback_SetClipBoard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_GetClipBoard_Proxy( 
    IRPFPlayback * This,
    /* [retval][out] */ BSTR *pbstrClipBoardString);


void __RPC_STUB IRPFPlayback_GetClipBoard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_TerminateProcessByModuleName_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BSTR bstrModuleName,
    /* [in] */ int nExitCode);


void __RPC_STUB IRPFPlayback_TerminateProcessByModuleName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_SetTargetProcess_Proxy( 
    IRPFPlayback * This,
    /* [in] */ INT nTargetProcessId,
    /* [out] */ INT *nCurrentTargetProcessId);


void __RPC_STUB IRPFPlayback_SetTargetProcess_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_TerminateTargetProcess_Proxy( 
    IRPFPlayback * This,
    /* [in] */ int nTargetProcessId);


void __RPC_STUB IRPFPlayback_TerminateTargetProcess_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_BringUpMainWindow_Proxy( 
    IRPFPlayback * This);


void __RPC_STUB IRPFPlayback_BringUpMainWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_ScreenElementFromPoint_Proxy( 
    IRPFPlayback * This,
    /* [in] */ INT x,
    /* [in] */ INT y,
    /* [retval][out] */ IScreenElement **ppScreenElement);


void __RPC_STUB IRPFPlayback_ScreenElementFromPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_ScreenElementFromWindow_Proxy( 
    IRPFPlayback * This,
    /* [in] */ INT64 hWnd,
    /* [retval][out] */ IScreenElement **ppScreenElement);


void __RPC_STUB IRPFPlayback_ScreenElementFromWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_ScreenElementFromAccessibleObject_Proxy( 
    IRPFPlayback * This,
    /* [in] */ VARIANT varDisp,
    /* [in] */ VARIANT varChildId,
    /* [retval][out] */ IScreenElement **ppScreenElement);


void __RPC_STUB IRPFPlayback_ScreenElementFromAccessibleObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_ScreenElementFromHTMLElement_Proxy( 
    IRPFPlayback * This,
    IHTMLElement *pIHTMLElement,
    /* [retval][out] */ IScreenElement **ppScreenElement);


void __RPC_STUB IRPFPlayback_ScreenElementFromHTMLElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_ScreenElementFromWinEvent_Proxy( 
    IRPFPlayback * This,
    /* [retval][out] */ IScreenElement **ppScreenElement);


void __RPC_STUB IRPFPlayback_ScreenElementFromWinEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_StartWaitingForAnyWinEvent_Proxy( 
    IRPFPlayback * This,
    /* [in] */ SAFEARRAY * pWinEventsHandles,
    /* [in] */ INT cWinEventHandles);


void __RPC_STUB IRPFPlayback_StartWaitingForAnyWinEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_SetValueAsSlider_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BSTR bstrNewValue,
    /* [defaultvalue][in] */ INT nOrientation);


void __RPC_STUB IRPFPlayback_SetValueAsSlider_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_DumpScreen_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BSTR bstrFileName,
    /* [defaultvalue][in] */ INT nFileFormat);


void __RPC_STUB IRPFPlayback_DumpScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_WaitForCursor_Proxy( 
    IRPFPlayback * This,
    /* [in] */ INT hInstance,
    /* [in] */ BOOL fWaitForAnyCursor,
    /* [in] */ INT nElapse,
    /* [in] */ INT nTimeOut,
    /* [in] */ SAFEARRAY * pnCursors,
    /* [in] */ INT cCursors);


void __RPC_STUB IRPFPlayback_WaitForCursor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_GetCurrentCursor_Proxy( 
    IRPFPlayback * This,
    /* [in] */ INT hInstance,
    /* [out] */ INT *nCursor);


void __RPC_STUB IRPFPlayback_GetCurrentCursor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_GetLastFailures_Proxy( 
    IRPFPlayback * This,
    /* [retval][out] */ BSTR *pbstrLastFalures);


void __RPC_STUB IRPFPlayback_GetLastFailures_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_ExtractResourceString_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BSTR resourceKey,
    /* [retval][out] */ BSTR *pbstrResourceString);


void __RPC_STUB IRPFPlayback_ExtractResourceString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_SetNextActionDelay_Proxy( 
    IRPFPlayback * This,
    /* [in] */ int nDelayTime);


void __RPC_STUB IRPFPlayback_SetNextActionDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_SetCurrentUsers_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BSTR bstrCurrentUsers);


void __RPC_STUB IRPFPlayback_SetCurrentUsers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_SetAccTechnology_Proxy( 
    IRPFPlayback * This,
    /* [in] */ int nAccTechnology);


void __RPC_STUB IRPFPlayback_SetAccTechnology_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_EnableUISynchronization_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BOOL fEnableUISync);


void __RPC_STUB IRPFPlayback_EnableUISynchronization_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_GetPlaybackProperty_Proxy( 
    IRPFPlayback * This,
    /* [in] */ int nParam,
    /* [retval][out] */ VARIANT *pVarParamValue);


void __RPC_STUB IRPFPlayback_GetPlaybackProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_SetPlaybackProperty_Proxy( 
    IRPFPlayback * This,
    /* [in] */ int nParam,
    /* [in] */ VARIANT varParamValue);


void __RPC_STUB IRPFPlayback_SetPlaybackProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_get_PlaybackVersion_Proxy( 
    IRPFPlayback * This,
    /* [retval][out] */ BSTR *pbstrPlaybackVersion);


void __RPC_STUB IRPFPlayback_get_PlaybackVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_GlobalizeQueryId_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BSTR bstrQueryId,
    /* [in] */ VARIANT *pvarResKeys,
    /* [in] */ INT cResKeys,
    /* [retval][out] */ BSTR *pbstrGlobalizedQueryId);


void __RPC_STUB IRPFPlayback_GlobalizeQueryId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_put_TargetLanguageId_Proxy( 
    IRPFPlayback * This,
    /* [in] */ int nTargetLanguageId);


void __RPC_STUB IRPFPlayback_put_TargetLanguageId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_put_TargetLanguageName_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BSTR bstrTargetLanguageName);


void __RPC_STUB IRPFPlayback_put_TargetLanguageName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_put_MUILanguageId_Proxy( 
    IRPFPlayback * This,
    /* [in] */ int nTMUILanguageId);


void __RPC_STUB IRPFPlayback_put_MUILanguageId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IRPFPlayback_put_ResFilesDirectories_Proxy( 
    IRPFPlayback * This,
    /* [in] */ BSTR bstrResFilesDirectories);


void __RPC_STUB IRPFPlayback_put_ResFilesDirectories_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRPFPlayback_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


