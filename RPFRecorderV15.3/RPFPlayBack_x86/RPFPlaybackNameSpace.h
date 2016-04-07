#pragma once

// The following line is required for CoInitializeEx
#define _WIN32_DCOM 

#pragma warning (disable : 4311)
#pragma warning (disable : 4312)
#pragma warning (disable : 4995)
#pragma warning (disable : 4996)

#include <objbase.h>
#include <atlbase.h>
#include <atlstr.h>
#include <oleacc.h>
#include <strsafe.h>

#include "RPFPlayback.h"

#ifndef ARRAYSIZE
#define ARRAYSIZE(x) sizeof(x)/sizeof(*x)
#endif 

#define COMPLEX_RESOURCE_KEY_NATIVE_SIGNATURE	0x501
#define ANY_RESOURCE_KEY_SIGNATURE				0x502
#define LANG_NEUTRALSTRING_SIGNATURE			0x503

const BSTR RPF_NAMESPACE_VERSION_STRING = L"15.3";

namespace RPFPlayback
{
    const int MAX_RES_KEY_LENGTH = 256;

    const int MAX_CLASS_LENGTH = 256;
    const int MAX_ROLE_LENGTH = 256;
    const int MAX_NAME_LENGTH = 1024;
    const int MAX_VALUE_LENGTH = 1024;
    const int MAX_INDEX_LENGTH = 8;

    const int VERSION_MISMATCH_TIMEOUT = 30*1000;

    extern IRPFPlayback* g_pRPFPlayback;

    __declspec(selectany) HANDLE g_hVersionTimeoutExpired = NULL;
    __declspec(selectany) IRPFPlayback* g_pRPFPlayback;

    typedef void (*WindowMonitoringHandler) (BSTR bstrWindowClass, BSTR bstrWindowName);
    typedef void (*WindowMonitoringHandlerEx) (HWND hWnd, int nWinEvent);
    typedef HRESULT (*LoggingHandler) (BSTR* pbstrLogString, BOOL *pfLogDefault, BOOL *pfDumpScreen);
    typedef HRESULT (*VerticalScrollingHandler)(int nScrollAmount, int *pnPercentScrolled);
    typedef HRESULT (*HorizonatalScrollingHandler)(int nScrollAmount, int *pnPercentScrolled);
    typedef void (*MSAAElementFoundHandler) (IDispatch**  pAcc, int *nChildId);

    // Definitions of fucntions used in this file
    HRESULT LogInformation(wchar_t* pszMessage, BOOL fDeleteFile);
    HRESULT StartWaitingForAnyWinEvent(int cWinEventHandles, ...);
    void ComposeQueryId(wchar_t* pszQueryId, va_list arguments, int *pnTotalResourceKeys, wchar_t (**pszAllResourceKeys)[MAX_RES_KEY_LENGTH]);
    HRESULT GlobalizeQueryId(wchar_t* pszGlobalizedQueryId, int cchGlobalizedQueryId, wchar_t* pszQueryId, int nTotalResourceKeys, wchar_t (*pszAllResourceKeys)[MAX_RES_KEY_LENGTH]);

    #pragma region IWinEventsHandle implementation

    // Implementing IWinEventsHandle for WinEvent handles
    class WinEventHandle : public IWinEventHandle
    {
    private:
        ULONG m_dwRef;
        wchar_t* m_pszQueryId;
        int m_nWinEvent;

    private:
        void InitWinEventsHandle(bool fStartWaiting, int nWinEvent, wchar_t* pszQueryId, va_list arguments)
        {
            m_dwRef = 1;
            m_nWinEvent = nWinEvent;

            if(pszQueryId != NULL)
            {
                // TODO (dklem) create a better mechanism of defining the length of the globalized QueryId
                int nLen = (int) wcslen(pszQueryId) * 2;
                m_pszQueryId = new wchar_t[nLen];
                if(m_pszQueryId == NULL)
                {
                    LogInformation(L"[WARNING] Internal failure in wrapper: Not enough memory for internal QueryId\r\n", FALSE);
                    return;
                }

                // Compose and globalize QueryId
                int nTotalResourceKeys = 0;
                wchar_t (*pszAllResourceKeys)[MAX_RES_KEY_LENGTH];

                // Note that ComposeQueryId allocates memory for pszAllResourceKeys and GlobalizeQueryId releases it
                ComposeQueryId(pszQueryId, arguments, &nTotalResourceKeys, &pszAllResourceKeys);
                GlobalizeQueryId(m_pszQueryId, nLen, pszQueryId, nTotalResourceKeys, pszAllResourceKeys);
            }
            else
            {
                m_pszQueryId = NULL;
            }

            if(fStartWaiting)
            {
                StartWaiting();
            }
        }

    public:

        // Constructors
        WinEventHandle()
        {
            InitWinEventsHandle(false, 0, NULL, NULL);
        }

        WinEventHandle(int nWinEvent)
        {
            InitWinEventsHandle(false, nWinEvent, NULL, NULL);
        }

        WinEventHandle(bool fStartWaiting, int nWinEvent)
        {
            InitWinEventsHandle(fStartWaiting, nWinEvent, NULL, NULL);
        }

        WinEventHandle(int nWinEvent, wchar_t* pszQueryId, ...)
        {
            // Initialize variable arguments.
            va_list arguments;
            va_start( arguments, pszQueryId);
            InitWinEventsHandle(false, nWinEvent, pszQueryId, arguments);
        }

        WinEventHandle(bool fStartWaiting, int nWinEvent, wchar_t* pszQueryId, ...)
        {
            // Initialize variable arguments.
            va_list arguments;
            va_start( arguments, pszQueryId);
            InitWinEventsHandle(fStartWaiting, nWinEvent, pszQueryId, arguments);
        }

        // Destructor
        ~WinEventHandle()
        {
            if(m_pszQueryId != NULL)
            {
                delete [] m_pszQueryId;
                m_pszQueryId = NULL;
            }
        }

        // Properties
         virtual HRESULT __stdcall GetQueryId(BSTR* pbstrQueryId)
        {
            if(pbstrQueryId != NULL)
            {
                if(m_pszQueryId != NULL)
                {
                    *pbstrQueryId = SysAllocString(m_pszQueryId);
                }
                else
                {
                    *pbstrQueryId = NULL;
                }
            }

            return S_OK;
        }

        virtual HRESULT __stdcall SetQueryId(BSTR bstrQueryId)
        {
            if(m_pszQueryId != NULL)
            {
                delete [] m_pszQueryId;
                InitWinEventsHandle(false, m_nWinEvent, bstrQueryId, NULL);
            }

            return S_OK;
        }

        virtual HRESULT __stdcall GetWinEvent(int* pnWinEvent)
        {
            if(pnWinEvent != NULL)
            {
                *pnWinEvent = m_nWinEvent;
            }

            return S_OK;
        }

        virtual HRESULT __stdcall SetWinEvent(int nWinEvent)
        {
            m_nWinEvent = nWinEvent;

            return S_OK;
        }

        virtual HRESULT __stdcall StartWaiting()
        {
            return StartWaitingForAnyWinEvent(1, this);
        }

        // IUnknown implementation
        ULONG __stdcall AddRef() 
        { 
            return ++m_dwRef; 
        }

        ULONG __stdcall Release() 
        { 
            if (--m_dwRef == 0) 
            {
                delete this; 
                return 0;
            }
            return m_dwRef;
        }

        HRESULT __stdcall QueryInterface(REFIID iid, void FAR* FAR* ppvObj)
        {
            if (iid == IID_IUnknown || iid == __uuidof(IWinEventHandle))
            {
                *ppvObj = this;
                AddRef();
                return NOERROR;
            }
            return E_NOINTERFACE;
        }
    };
        
    #pragma endregion IWinEventsHandle implementation

    #pragma region IMonitoringWindowsCallback implementation

    // Implementing IMonitoringWindowsCallback for thread monitoring info
    class MonitorWindowBase : public IMonitoringWindowsCallback
    {
        ULONG m_dwRef;
        wchar_t* m_pszWindowName;
        wchar_t* m_pszWindowClass;
        WindowMonitoringHandler m_windowMonitoringHandler;
        WindowMonitoringHandlerEx m_windowMonitoringHanlerEx;
        IWinEventHandle* m_pWinEventHandle;

    private:

        void InitMonitorWindowBase(wchar_t* pszWindowClass, wchar_t* pszWindowName, WindowMonitoringHandler windowMonitoringHanler, WindowMonitoringHandlerEx windowMonitoringHanlerEx, IWinEventHandle* pWinEventHandle)
        {
            m_dwRef = 1;
            m_pszWindowClass = pszWindowClass;
            m_pszWindowName = pszWindowName;
            m_windowMonitoringHandler = windowMonitoringHanler;
            m_windowMonitoringHanlerEx = windowMonitoringHanlerEx;
            m_pWinEventHandle = pWinEventHandle;
        }

    public:
       
        // Constructors
        MonitorWindowBase(wchar_t* pszWindowClass, wchar_t* pszWindowName, WindowMonitoringHandler windowMonitoringHanler)
        {
            InitMonitorWindowBase(pszWindowClass, pszWindowName, windowMonitoringHanler, NULL, NULL);
        }

        MonitorWindowBase(wchar_t* pszWindowClass, wchar_t* pszWindowName, WindowMonitoringHandlerEx windowMonitoringHanlerEx)
        {
            InitMonitorWindowBase(pszWindowClass, pszWindowName, NULL, windowMonitoringHanlerEx, NULL);
        }

        MonitorWindowBase(WindowMonitoringHandlerEx windowMonitoringHanlerEx, IWinEventHandle* pWinEventHandle)
        {
            InitMonitorWindowBase(NULL, NULL, NULL, windowMonitoringHanlerEx, pWinEventHandle);
        }

        // IMonitoringWindowsCallback implementation
        virtual HRESULT __stdcall MonitoringWindowsCallBack(BSTR bstrWindowClass, BSTR bstrWindowName, INT64 hWnd, int nWinEvent)
        {
            if(m_windowMonitoringHandler)
            {
                m_windowMonitoringHandler(bstrWindowClass, bstrWindowName);
            }

            if(m_windowMonitoringHanlerEx)
            {
                m_windowMonitoringHanlerEx((HWND) hWnd, nWinEvent);
            }

            return S_OK;
        }

        virtual HRESULT __stdcall GetMonitoringInfo(BSTR* pbstrWindowClass, int cchClass, BSTR* pbstrWindowName, int cchWindowName, IWinEventHandle** ppWinEventHandle)
        {
            if (m_pszWindowClass)
            {
                StringCchCopyW(*pbstrWindowClass, cchClass, m_pszWindowClass);
            }
            else if (pbstrWindowClass != NULL && *pbstrWindowClass != NULL)
            {
                **pbstrWindowClass = L'\0';
            }

            if (m_pszWindowName)
            {
                StringCchCopyW(*pbstrWindowName, cchWindowName, m_pszWindowName);
            }
            else if (pbstrWindowName != NULL && *pbstrWindowName != NULL)
            {
                **pbstrWindowName = L'\0';
            }

            if(ppWinEventHandle)
            {
                *ppWinEventHandle = m_pWinEventHandle;
            }

            return S_OK;
        }

        // IUnknown implementation
        ULONG __stdcall AddRef() 
        { 
            return ++m_dwRef; 
        }

        ULONG __stdcall Release() 
        { 
            if (--m_dwRef == 0) 
            {
                delete this; 
                return 0;
            }
            return m_dwRef;
        }

        HRESULT __stdcall QueryInterface(REFIID iid, void FAR* FAR* ppvObj)
        {
            if (iid == IID_IUnknown || iid == __uuidof(IMonitoringWindowsCallback))
            {
                *ppvObj = this;
                AddRef();
                return NOERROR;
            }

            return E_NOINTERFACE;
        }
    };

    #pragma endregion IMonitoringWindowsCallback implementation

    #pragma region ILoggerCallback implementation

    // Implementing ILoggerCallback for custom logging
    class LoggerBase : public ILoggerCallback
    {
        ULONG m_dwRef;
        LoggingHandler m_loggingHandler;

    public:

        // Constructor
        LoggerBase(LoggingHandler loggingHandler)
        {
            m_dwRef = 1;
            m_loggingHandler = loggingHandler;
        }

        // ILoggerCallback implementation
        virtual HRESULT __stdcall LoggerCallback(BSTR* pbstrLogString, BOOL *pfLogDefault, BOOL *pfDumpScreen)
        {
            return m_loggingHandler(pbstrLogString, pfLogDefault, pfDumpScreen);
        }

        // IUnknown implementation
        ULONG __stdcall AddRef() 
        { 
            return ++m_dwRef; 
        }

        ULONG __stdcall Release() 
        { 
            if (--m_dwRef == 0) 
            {
                delete this; 
                return 0;
            }
            return m_dwRef;
        }

        HRESULT __stdcall QueryInterface(REFIID iid, void FAR* FAR* ppvObj)
        {
            if (iid == IID_IUnknown || iid == __uuidof(ILoggerCallback))
            {
                *ppvObj = this;
                AddRef();
                return NOERROR;
            }
            return E_NOINTERFACE;
        }
    };
        
    #pragma endregion ILoggerCallback implementation

    #pragma region IScrollerCallback implementation

    // Implementing IScrollerCallback for custom logging
    class ScrollerBase : public IScrollerCallback
    {
        ULONG m_dwRef;
        VerticalScrollingHandler m_verticalScrollingHandler;
        HorizonatalScrollingHandler m_horizontalScrollingHandler;

    public:

        // Constructor
        ScrollerBase(VerticalScrollingHandler verticalScrollingHandler, HorizonatalScrollingHandler horizontalScrollingHandler)
        {
            m_dwRef = 1;
            m_verticalScrollingHandler = verticalScrollingHandler;
            m_horizontalScrollingHandler = horizontalScrollingHandler;
        }

        // IScrollerCallback implementation
        virtual HRESULT __stdcall VerticalScrollCallback(int nScrollAmount, int *pnPercentScrolled)
        {
            return m_verticalScrollingHandler(nScrollAmount, pnPercentScrolled);
        }

        virtual HRESULT __stdcall HorizontalScrollCallback(int nScrollAmount, int *pnPercentScrolled)
        {
            return m_horizontalScrollingHandler(nScrollAmount, pnPercentScrolled);
        }

        // IUnknown implementation
        ULONG __stdcall AddRef() 
        { 
            return ++m_dwRef; 
        }

        ULONG __stdcall Release() 
        { 
            if (--m_dwRef == 0) 
            {
                delete this; 
                return 0;
            }
            return m_dwRef;
        }

        HRESULT __stdcall QueryInterface(REFIID iid, void FAR* FAR* ppvObj)
        {
            if (iid == IID_IUnknown || iid == __uuidof(IScrollerCallback))
            {
                *ppvObj = this;
                AddRef();
                return NOERROR;
            }
            return E_NOINTERFACE;
        }
    };
        
    #pragma endregion ILoggerCallback implementation

    #pragma region RPFPlaybackNameSpace Functions definitions

    inline HRESULT LogInformation(wchar_t* pszMessage, BOOL fDeleteFile)
    { 
        return g_pRPFPlayback->LogInformation(CComBSTR(pszMessage), fDeleteFile); 
    }

    inline void LogStep(HRESULT hr, wchar_t* pszFunction)
    {
        g_pRPFPlayback->LogStep(hr, CComBSTR(pszFunction));
    }

    inline DWORD WINAPI VersionThread(LPVOID lpParameter)
    {
        CStringW csMessageTitle;
        csMessageTitle.Format(L"Playback Error. This Message box will be automatically dismissed in %d seconds", VERSION_MISMATCH_TIMEOUT/1000);

        MessageBoxW(NULL, (wchar_t*) lpParameter, csMessageTitle.GetBuffer(), MB_OK | MB_ICONSTOP);

        SetEvent(g_hVersionTimeoutExpired);
        return 1;
    }

    inline void VerifyPlaybackWrapperVersion()
    {
        bool fVersionsMatch = false;
        CStringW csPlaybackVersion(L"");

        if(CComBSTR(RPF_NAMESPACE_VERSION_STRING) == CComBSTR(PLAYBACK_VERSION_STRING))
        {
            BSTR bstrPlaybackVersion = NULL;
            if(S_OK == g_pRPFPlayback->get_PlaybackVersion(&bstrPlaybackVersion) && bstrPlaybackVersion)
            {
                if(CComBSTR(bstrPlaybackVersion) == CComBSTR(RPF_NAMESPACE_VERSION_STRING))
                {
                    fVersionsMatch = true;
                }

                csPlaybackVersion = CStringW(bstrPlaybackVersion);
                SysFreeString(bstrPlaybackVersion);
            }
        }

        if(!fVersionsMatch)
        {
            // Form the error message
            CStringW csErrorMessage(L"Playback DLL doesn't match headers.  This may cause failures in your test.\r\n");
            csErrorMessage += CStringW(L"\r\nRPFPlayback.h version = ") + CStringW(PLAYBACK_VERSION_STRING);
            csErrorMessage += CStringW(L"\r\nRPFPlaybackNameSpace.h version = ") + CStringW(RPF_NAMESPACE_VERSION_STRING);

            if(csPlaybackVersion.GetLength())
            {
                csErrorMessage += CStringW(L"\r\nRPFMSaaPlayback.DLL version = ") + csPlaybackVersion;
            }

            // Log the error, so user knows that the problem exists even if message box is dismissed automatically
            LogStep(E_FAIL, csErrorMessage.GetBuffer());

            // Create an event that is set when message box is dismissed
            if(NULL == (g_hVersionTimeoutExpired = CreateEvent(NULL, true, false, NULL)))
            {
                return;
            }

            // Start thread that displays the error message
            DWORD dwThreadId;
            HANDLE hThread = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE) VersionThread, csErrorMessage.GetBuffer(), 0, &dwThreadId);

            if(hThread != NULL)
            {
                if(WAIT_TIMEOUT == WaitForSingleObject(g_hVersionTimeoutExpired, VERSION_MISMATCH_TIMEOUT))
                {
                    // Kill thread is user did close the message box
                    TerminateThread(hThread, 0);
                }
            }

            CloseHandle(g_hVersionTimeoutExpired);
        }
    }

    inline HRESULT InitPlayBackOnRemoteMachine(wchar_t* szMachineName, bool fInitSecurity = true)
    {
        HRESULT hr;

        // CoInitialize RPF to run in an STA thread model if caller hasn't done this.
        // Ohterwise simply ignore the return value since RPF can run in both STA and MTA thread models
        CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

        // This provides a NULL DACL which will allow access to everyone.
        if(fInitSecurity && S_OK != (hr = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_NONE, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL)))
        {
            return hr;
        }

        COSERVERINFO cosi = { 0, szMachineName, NULL, 0 };
        MULTI_QI mqi = { &__uuidof(IRPFPlayback), NULL, 0};

        if(S_OK != (hr = CoCreateInstanceEx(__uuidof(CRPFPlayback), NULL, CLSCTX_REMOTE_SERVER, &cosi, 1, &mqi)))
        {
            return hr;
        }

        if(S_OK != (hr = mqi.pItf->QueryInterface(__uuidof(IRPFPlayback), (void**) &g_pRPFPlayback)))
        {
            return hr;
        }

        hr  = g_pRPFPlayback->InitPlayBack();

        VerifyPlaybackWrapperVersion();

        // Log Step only if InitPlayBack failed
        if (hr != S_OK)
        {
            LogStep(hr, L"InitPlayBack");
        }
        else
        {
            // Delete log file only if hr == S_OK, since InitPlayBack may log failure info
            LogInformation(NULL, TRUE);
        }

        return hr; 
    }

    inline HRESULT InitPlayBack(void)
    {
        HRESULT hr;

        // CoInitialize RPF to run in an STA thread model if caller hasn't done this.
        // Ohterwise simply ignore the return value since RPF can run in both STA and MTA thread models
        CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

        if (S_OK != (hr = CoCreateInstance(__uuidof(CRPFPlayback), NULL, CLSCTX_ALL, __uuidof(IRPFPlayback), (void**) &g_pRPFPlayback)))
        {
            return hr;
        }

        hr  = g_pRPFPlayback->InitPlayBack();

        VerifyPlaybackWrapperVersion();

        // Log Step only if InitPlayBack failed
        if (hr != S_OK)
        {
            LogStep(hr, L"InitPlayBack");
        }
        else
        {
            // Delete log file only if hr == S_OK, since InitPlayBack may log failure info
            LogInformation(NULL, TRUE);
        }

        return hr; 
    }

    inline HRESULT InitPlayBackForTargetWindow(wchar_t* pszMainWindowClass, wchar_t* pszMainWindowWindow, BOOL fShowInfoWindow)
    {
        HRESULT hr;

        // CoInitialize RPF to run in an STA thread model if caller hasn't done this.
        // Ohterwise simply ignore the return value since RPF can run in both STA and MTA thread models
        CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

        if (S_OK != (hr = CoCreateInstance(__uuidof(CRPFPlayback), NULL, CLSCTX_ALL, __uuidof(IRPFPlayback), (void**) &g_pRPFPlayback)))
        {
            return hr;
        }

        hr  = g_pRPFPlayback->InitPlayBackForTargetWindow(CComBSTR(pszMainWindowClass), CComBSTR(pszMainWindowWindow), fShowInfoWindow);

        VerifyPlaybackWrapperVersion();

        // Log Step only if InitPlayBackForTargetWindow failed
        if (hr != S_OK)
        {
            LogStep(hr, L"InitPlayBackForTargetWindow");
        }
        else
        {
            // Delete log file only if hr == S_OK, since InitPlayBack may log failure info
            LogInformation(NULL, TRUE);
        }

        return hr;
    }

    inline HRESULT InitPlayBackForTargetProcess(int nDevenvProcessId, INT64 hWndDevenvMainWindow, BOOL fShowInfoWindow)
    {
        HRESULT hr;

        // CoInitialize RPF to run in an STA thread model if caller hasn't done this.
        // Ohterwise simply ignore the return value since RPF can run in both STA and MTA thread models
        CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

        if (S_OK != (hr = CoCreateInstance(__uuidof(CRPFPlayback), NULL, CLSCTX_ALL, __uuidof(IRPFPlayback), (void**) &g_pRPFPlayback)))
        {
            return hr;
        }

        hr  = g_pRPFPlayback->InitPlayBackForTargetProcess(nDevenvProcessId, hWndDevenvMainWindow, fShowInfoWindow);

        VerifyPlaybackWrapperVersion();
        
        // Log Step only if InitPlayBackForTargetProcess failed
        if (hr != S_OK)
        {
            LogStep(hr, L"InitPlayBackForTargetProcess");
        }
        else
        {
            // Delete log file only if hr == S_OK, since InitPlayBack may log failure info
            LogInformation(NULL, TRUE);
        }

        return hr;
    }

    inline HRESULT InitPlayBackForTargetExecutable(wchar_t* bstrExecutablePath, BOOL fShowInfoWindow)
    {
        HRESULT hr;

        // CoInitialize RPF to run in an STA thread model if caller hasn't done this.
        // Ohterwise simply ignore the return value since RPF can run in both STA and MTA thread models
        CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

        if (S_OK != (hr = CoCreateInstance(__uuidof(CRPFPlayback), NULL, CLSCTX_ALL, __uuidof(IRPFPlayback), (void**) &g_pRPFPlayback)))
        {
            return hr;
        }

        hr  = g_pRPFPlayback->InitPlayBackForTargetExecutable(CComBSTR(bstrExecutablePath), fShowInfoWindow);
        
        VerifyPlaybackWrapperVersion();

        // Log Step only if InitPlayBackForTargetExecutable failed
        if (hr != S_OK)
        {
            LogStep(hr, L"InitPlayBackForTargetExecutable");
        }
        else
        {
            // Delete log file only if hr == S_OK, since InitPlayBack may log failure info
            LogInformation(NULL, TRUE);
        }

        return hr;
    }

    inline void FinishPlayBack(void)
    {
        if (g_pRPFPlayback)
        {
            g_pRPFPlayback->FinishPlayBack();
            g_pRPFPlayback->Release();
            g_pRPFPlayback = NULL;
        }

        CoUninitialize();
    }

    /// RPF
    inline HRESULT WaitForScreenElementGone(int nTimeOut, int nElapse)
    {
        return g_pRPFPlayback->WaitForScreenElementGone(nTimeOut, nElapse);
    }

    inline HRESULT GetClickablePoint(int *x, int *y)
    {
        return g_pRPFPlayback->GetClickablePoint(x, y);
    }

    inline HRESULT TerminateProcessByModuleName(wchar_t* pszModuleName, int nExitCode)
    {
        return g_pRPFPlayback->TerminateProcessByModuleName(CComBSTR(pszModuleName), nExitCode);
    }

    inline HRESULT SetDebugMode(INT fEnableDebugMode)
    {
        return g_pRPFPlayback->SetDebugMode(fEnableDebugMode);
    }

    inline int SetSearchTimeOut(int nSearchTimeOut)
    {
        int nPreviousSearchTimeOut;
        if (S_OK == g_pRPFPlayback->SetSearchTimeOut(nSearchTimeOut, &nPreviousSearchTimeOut))
        {
            return nPreviousSearchTimeOut;
        }
        else
        {
            return -1;
        }
    }

    inline int SetLoggingFlag(int nLoggingFlag)
    {
        int nPreviousLoggingFlag;

        if (S_OK == g_pRPFPlayback->SetLoggingFlag(nLoggingFlag, &nPreviousLoggingFlag))
        {
            return nPreviousLoggingFlag;
        }
        else
        {
            return -1;
        }
    }

    inline void SetLogFailureAsInfo(bool bLogFailureAsInfo)
    {
        // Get current logging flag
        int nCurrentFlag = SetLoggingFlag(0);

        // Set current flag
        if (bLogFailureAsInfo && !(nCurrentFlag & FL_LOG_FAILURE_AS_INFO))
        {
            nCurrentFlag += FL_LOG_FAILURE_AS_INFO;
        }
        else if (!bLogFailureAsInfo && (nCurrentFlag & FL_LOG_FAILURE_AS_INFO))
        {
            nCurrentFlag -= FL_LOG_FAILURE_AS_INFO;
        }

        SetLoggingFlag(nCurrentFlag);
    }

    inline void SetVerificationFlag(int nVerificationFlag)
    {
        g_pRPFPlayback->SetVerificationFlag(nVerificationFlag);
    }

    inline HRESULT SetClipBoard(wchar_t* pszClipBoardString)
    {
        return g_pRPFPlayback->SetClipBoard(CComBSTR(pszClipBoardString));
    }

    inline HRESULT GetClipBoard(wchar_t* pszClipBoardString, int ccClipBoardString)
    {
        BSTR bstrClipBoardString;
        HRESULT hr = g_pRPFPlayback->GetClipBoard(&bstrClipBoardString);

        if (hr == S_OK)
        {
            if (pszClipBoardString && ccClipBoardString)
            {
                StringCchCopyW(pszClipBoardString, ccClipBoardString, bstrClipBoardString);
            }
            
            SysFreeString(bstrClipBoardString);
        }

        return hr;
    }

    inline bool TerminateTargetProcess(int nTargetProcessId)
    {
        return(S_OK == g_pRPFPlayback->TerminateTargetProcess(nTargetProcessId));
    }

    inline HRESULT SetTargetProcess(INT nTargetProcessId, INT *nCurrentTargetProcessId)
    {
        return g_pRPFPlayback->SetTargetProcess(nTargetProcessId, nCurrentTargetProcessId);
    }

    inline HRESULT SearchTargetProcessElementsOnly(BOOL fEnable)
    {
        VARIANT varParamValue;
        varParamValue.vt = VT_BOOL;
        varParamValue.boolVal = (fEnable) ? true : false;
        return g_pRPFPlayback->SetPlaybackProperty(SEARCH_IN_TARGETPROCESS_ONLY, varParamValue);
    }

    inline void BringUpMainWindow()
    {
        g_pRPFPlayback->BringUpMainWindow();
    }

    inline HRESULT AddMonitoringInfo(IMonitoringWindowsCallback* MonitoringWindowsCallback)
    {
        return g_pRPFPlayback->AddMonitoringInfo(MonitoringWindowsCallback);
    }

    inline HRESULT StartMonitoringWindows(int nElapse)
    {
        return g_pRPFPlayback->StartMonitoringWindows(nElapse);
    }

    inline HRESULT StopMonitoringWindows()
    {
        return g_pRPFPlayback->StopMonitoringWindows();
    }

    inline HRESULT SetRobustnessLevel(int nRobustnessLevel)
    {
        return g_pRPFPlayback->SetRobustnessLevel(nRobustnessLevel);
    }

    inline HRESULT SetRobustnessLevelEx(int nRobustnessLevel, wchar_t* pszBackGroundThreadStates, wchar_t* pszBackGroundThreadWaitReasons)
    {
        return g_pRPFPlayback->SetRobustnessLevelEx(nRobustnessLevel, FALSE, MW_THREAD_STATE, CComBSTR(pszBackGroundThreadStates), CComBSTR(pszBackGroundThreadWaitReasons));
    }

    inline HRESULT SetRobustnessLevelEx(int nRobustnessLevel, wchar_t* pszBackGroundThreadStates, wchar_t* pszBackGroundThreadWaitReasons, wchar_t* pszForeGroundThreadStates, wchar_t* pszForeGroundThreadWaitReasons)
    {
        return g_pRPFPlayback->SetRobustnessLevelEx(nRobustnessLevel, FALSE, MW_THREAD_STATE, CComBSTR(pszBackGroundThreadStates), CComBSTR(pszBackGroundThreadWaitReasons), CComBSTR(pszForeGroundThreadStates), CComBSTR(pszForeGroundThreadWaitReasons));
    }

    inline HRESULT SetRobustnessLevelEx(int nRobustnessLevel, BOOL fSystemWide, wchar_t* pszBackGroundThreadStates, wchar_t* pszBackGroundThreadWaitReasons, wchar_t* pszForeGroundThreadStates, wchar_t* pszForeGroundThreadWaitReasons)
    {
        return g_pRPFPlayback->SetRobustnessLevelEx(nRobustnessLevel, fSystemWide, MW_THREAD_STATE, CComBSTR(pszBackGroundThreadStates), CComBSTR(pszBackGroundThreadWaitReasons), CComBSTR(pszForeGroundThreadStates), CComBSTR(pszForeGroundThreadWaitReasons));
    }

    inline HRESULT SetRobustnessLevelEx(int nRobustnessLevel, BOOL fSystemWide, int nWaitForReadyMode, wchar_t* pszBackGroundThreadStates, wchar_t* pszBackGroundThreadWaitReasons, wchar_t* pszForeGroundThreadStates, wchar_t* pszForeGroundThreadWaitReasons)
    {
        return g_pRPFPlayback->SetRobustnessLevelEx(nRobustnessLevel, fSystemWide, nWaitForReadyMode, CComBSTR(pszBackGroundThreadStates), CComBSTR(pszBackGroundThreadWaitReasons), CComBSTR(pszForeGroundThreadStates), CComBSTR(pszForeGroundThreadWaitReasons));
    }

    // FromPartialQueryId functionalitiies
    #pragma region FromPartialQueryId

    inline HRESULT ComposeSafeArray(VARIANT *pvarResKeys, wchar_t (**pszAllResourceKeys)[MAX_RES_KEY_LENGTH], int cTotalElements)
    {
        if (!pvarResKeys)
        {
            return E_INVALIDARG;
        }

        VariantInit(pvarResKeys);

        VARIANT* varData;
        SAFEARRAYBOUND arrayBound[1];
        arrayBound[0].lLbound = 0; arrayBound[0].cElements = cTotalElements;

        SAFEARRAY* saResKeys = SafeArrayCreate(VT_VARIANT, 1, arrayBound);

        if (saResKeys == NULL)
        {
            return E_FAIL;
        }

        if (S_OK != SafeArrayAccessData(saResKeys, (void **)&varData))
        {
            return E_FAIL;
        }

        for (int i = 0; i < cTotalElements; i++)
        {
            varData[i].bstrVal = SysAllocString((*pszAllResourceKeys)[i]);
            varData[i].vt = VT_BSTR;
        }

        V_VT(pvarResKeys) = VT_ARRAY | VT_VARIANT;
        V_ARRAY(pvarResKeys) = saResKeys;

        return S_OK;
    }

    // Free BSTRs allocated in ComposeSafeArray and delete safearray
    inline HRESULT FreeSafeArray(VARIANT *pvarResKeys)
    {
        VARIANT *var;

        if (pvarResKeys->parray == NULL)
        {
            return E_FAIL;
        }

        if (S_OK == SafeArrayAccessData(pvarResKeys->parray, (void **)&var))
        {
            for (unsigned int i = 0; i < pvarResKeys->parray->rgsabound[0].cElements; i++)
            {
                SysFreeString(var[i].bstrVal);
            }

            // Unlock the array that was locked by SafeArrayAccessData in the "if" statement above
            SafeArrayUnlock(pvarResKeys->parray);
        }

        // Unlock the array that was locked by SafeArrayAccessData in ComposeSafeArray
        SafeArrayUnaccessData(pvarResKeys->parray);
        
        // Destroy safearray descriptior only since the data was freed earlier
        return SafeArrayDestroyDescriptor(pvarResKeys->parray);  
    }

    inline void ComposeQueryId(wchar_t* pszQueryId, va_list arguments, int *pnTotalResourceKeys, wchar_t (**pszAllResourceKeys)[MAX_RES_KEY_LENGTH])
    {
        wchar_t *pszCurrentArg = pszQueryId;
        wchar_t szFormatterIndex[MAX_INDEX_LENGTH];

        if (pnTotalResourceKeys == NULL)
        {
            return;
        }

        if (pszQueryId == NULL || pszAllResourceKeys == NULL)
        {
            *pnTotalResourceKeys = 0;
            return;
        }

        // Calculate how many resource keys were requested in QueryId
        for (*pnTotalResourceKeys = 0; ; (*pnTotalResourceKeys)++)
        {
            StringCchPrintfW(szFormatterIndex, ARRAYSIZE(szFormatterIndex), L"{%d}", *pnTotalResourceKeys);
            if (!wcsstr(pszQueryId, szFormatterIndex))
            {
                break;
            }
        }

        if (*pnTotalResourceKeys > 0)
        {
            *pszAllResourceKeys = new wchar_t[*pnTotalResourceKeys][MAX_RES_KEY_LENGTH];

            if ((*pszAllResourceKeys) == NULL)
            {
                LogInformation(L"[WARNING] Internal failure in wrapper: Not enough memory for the Resource Keys array\r\n", FALSE);
                *pnTotalResourceKeys = 0;
                return;
            }

            for (int i = 0; pszCurrentArg && i < *pnTotalResourceKeys; i++)
            {
                if ((NULL != (pszCurrentArg = va_arg(arguments, wchar_t*))))
                {
                    // The following if is used only to support legacy code for LanguageNeutralStrings
                    // It used to be possible to send those resKeys to FromPartialQueryId without (wchar_t*) cast
                    // This worked since the the first memeber of  class LanguageNeutralString was _csActualString and not _sSignature
                    // Now when the first memeber of LanguageNeutralString is _sSignature, "jump" over it to get to the _csActualString
                    // Would this work when _INTSIZEOF(short*) is the same as _INTSIZEOF(wchar_t*)?
                    if(LANG_NEUTRALSTRING_SIGNATURE == (short) pszCurrentArg)
                    {
#if defined(_M_IX86)
                        // If _INTSIZEOF(short*) is not the same as _INTSIZEOF(wchar_t*) - is this possible?
                        // move _INTSIZEOF(wchar_t*) back and then _INTSIZEOF(short*) forward
                        if(_INTSIZEOF(short*) != _INTSIZEOF(wchar_t*))
                        {
                            arguments +=_INTSIZEOF(short*) - _INTSIZEOF(wchar_t*);
                        }

                        pszCurrentArg = *((wchar_t**) arguments);
                        arguments +=_INTSIZEOF(short*);
#else
                        pszCurrentArg = *((wchar_t**) arguments);
                        arguments +=sizeof(__int64);
#endif
                    }

                    StringCchCopyW((*pszAllResourceKeys)[i], MAX_RES_KEY_LENGTH, pszCurrentArg);
                }
            }

            // Reset variable arguments
            va_end( arguments );              
        }
        else
        {
            *pszAllResourceKeys = NULL;
        }
    }

    // General FromPartialQueryId functionality
    inline HRESULT FindScreenElementEx(IScreenElement* pscreenElementStart, IScreenElement** ppscreenElement, wchar_t* pszQueryId, va_list arguments)
    {
        HRESULT hr = S_OK;
        int nTotalResourceKeys;
        VARIANT varResKeys;
        wchar_t (*pszAllResourceKeys)[MAX_RES_KEY_LENGTH];
        IScreenElement* pscreenElementTmp;
        bool fReleaseTmpScreenElement = false;

        if(ppscreenElement == NULL)
        {
            fReleaseTmpScreenElement = true;
            ppscreenElement = &pscreenElementTmp;
        }

        // Note that ComposeQueryId allocates memory for pszAllResourceKeys
        ComposeQueryId(pszQueryId, arguments, &nTotalResourceKeys, &pszAllResourceKeys);

        if (nTotalResourceKeys > 0)
        {
            if (SUCCEEDED(ComposeSafeArray(&varResKeys, &pszAllResourceKeys, nTotalResourceKeys)))
            {
                hr = g_pRPFPlayback->FindScreenElementEx(pscreenElementStart, CComBSTR(pszQueryId), &varResKeys, nTotalResourceKeys, ppscreenElement);

                // Free BSTRs allocated in ComposeSafeArray and delete safearray
                FreeSafeArray(&varResKeys);
            }
        }
        else
        {
            VariantInit(&varResKeys);
            hr = g_pRPFPlayback->FindScreenElementEx(pscreenElementStart, CComBSTR(pszQueryId), &varResKeys, 0, ppscreenElement);
        }

        delete [] pszAllResourceKeys;

        if(fReleaseTmpScreenElement && *ppscreenElement != NULL)
        {
            (*ppscreenElement)->Release();
        }

        return hr;  
    }

    inline HRESULT GlobalizeQueryId(wchar_t* pszGlobalizedQueryId, int cchGlobalizedQueryId, wchar_t* pszQueryId, int nTotalResourceKeys, wchar_t (*pszAllResourceKeys)[MAX_RES_KEY_LENGTH])
    {
        HRESULT hr = E_FAIL;

        if (nTotalResourceKeys > 0)
        {
            BSTR bstrGlobalizedQueryId;
            VARIANT varResKeys;

            if (SUCCEEDED(ComposeSafeArray(&varResKeys, &pszAllResourceKeys, nTotalResourceKeys)))
            {
                hr = g_pRPFPlayback->GlobalizeQueryId(CComBSTR(pszQueryId), &varResKeys, nTotalResourceKeys, &bstrGlobalizedQueryId);

                // Copy globalized QueryId
                if (hr == S_OK)
                {
                    hr = StringCchCopyW(pszGlobalizedQueryId, cchGlobalizedQueryId, bstrGlobalizedQueryId);
                    SysFreeString(bstrGlobalizedQueryId);
                }

                // Free BSTRs allocated in ComposeSafeArray and delete safearray
                FreeSafeArray(&varResKeys);
            }
        }
        else
        {
            hr = StringCchCopyW(pszGlobalizedQueryId, cchGlobalizedQueryId, pszQueryId);
        }

        delete [] pszAllResourceKeys;

        return hr;
    }

    inline HRESULT FromPartialQueryId(IScreenElement* pscreenElementStart, IScreenElement** ppscreenElement, wchar_t* pszQueryId, va_list arguments)
    {
        return FindScreenElementEx(pscreenElementStart, ppscreenElement, pszQueryId, arguments);
    }

    inline HRESULT FromPartialQueryId(wchar_t* pszQueryId, ... )
    {
        // Initialize variable arguments.
        va_list arguments;
        va_start( arguments, pszQueryId);

        return FromPartialQueryId(NULL, NULL, pszQueryId, arguments);
    }

    inline HRESULT FromPartialQueryId(IScreenElement** ppscreenElement, wchar_t* pszQueryId, ... )
    {
        // Initialize variable arguments.
        va_list arguments;
        va_start( arguments, pszQueryId);     

        return FromPartialQueryId(NULL, ppscreenElement, pszQueryId, arguments);
    }

    inline HRESULT FindAllScreenElements(IScreenElement* pscreenElement, IScreenElement* foundDescendants[], int cMaxFoundSize, int nMaxDepth, wchar_t* pszQueryId, va_list arguments)
    {
        SAFEARRAY *saDescendants;

        HRESULT hr = S_OK;
        int nTotalResourceKeys;
        VARIANT varResKeys;
        wchar_t (*pszAllResourceKeys)[MAX_RES_KEY_LENGTH];

        // Note that ComposeQueryId allocates memory for pszAllResourceKeys
        ComposeQueryId(pszQueryId, arguments, &nTotalResourceKeys, &pszAllResourceKeys);

        if (nTotalResourceKeys > 0)
        {
            if (SUCCEEDED(ComposeSafeArray(&varResKeys, &pszAllResourceKeys, nTotalResourceKeys)))
            {
                hr = g_pRPFPlayback->FindAllScreenElements(pscreenElement, CComBSTR(pszQueryId), &varResKeys, nTotalResourceKeys, nMaxDepth, &saDescendants);

                // Free BSTRs allocated in ComposeSafeArray and delete safearray
                FreeSafeArray(&varResKeys);
            }
            else
            {
                return hr;
            }
        }
        else
        {
            VariantInit(&varResKeys);
            hr = g_pRPFPlayback->FindAllScreenElements(pscreenElement, CComBSTR(pszQueryId), &varResKeys, 0, nMaxDepth, &saDescendants);
        }

        delete [] pszAllResourceKeys;

        // Compose array of found descendants
        VARIANT *var;
        if (S_OK != SafeArrayAccessData(saDescendants, (void **)&var))
        {
            return E_FAIL;
        }

        int nTotalFoundDescendants = saDescendants->rgsabound[0].cElements;

        for (int i = 0; i < nTotalFoundDescendants && i < cMaxFoundSize; i++)
        {
            var[i].pdispVal->QueryInterface(__uuidof(IScreenElement), (void**) &(foundDescendants[i]));
        }

        // Unlock the array
        SafeArrayUnaccessData(saDescendants);
        // Destroy safearray.  This will call Release for each screenElement whose RefCounf was incremented by QueryInterface
        SafeArrayDestroy(saDescendants);

        return hr;  
    }

    inline HRESULT FindAllScreenElements(IScreenElement* pscreenElement, IScreenElement* foundDescendants[], int cMaxFoundSize, int nMaxDepth, wchar_t* pszQueryId, ...)
    {
        // Initialize variable arguments.
        va_list arguments;
        va_start( arguments, pszQueryId);

        return FindAllScreenElements(pscreenElement, foundDescendants, cMaxFoundSize, nMaxDepth, pszQueryId, arguments);
    }

    inline HRESULT FindAllScreenElements(IScreenElement* pscreenElement, IScreenElement* foundDescendants[], int cMaxFoundSize, wchar_t* pszQueryId, ...)
    {
        // Initialize variable arguments.
        va_list arguments;
        va_start( arguments, pszQueryId);

        return FindAllScreenElements(pscreenElement, foundDescendants, cMaxFoundSize, ALL_DESCENDANTS, pszQueryId, arguments);
    }

    #pragma endregion FromPartialQueryId

    inline HRESULT ScreenElementFromPoint(int x, int y, IScreenElement** screenElement)
    {
        return g_pRPFPlayback->ScreenElementFromPoint(x, y, screenElement);
    }

    inline HRESULT ScreenElementFromWindow(HWND hWnd, IScreenElement** screenElement)
    {
        return g_pRPFPlayback->ScreenElementFromWindow((INT64) hWnd, screenElement);
    }

    inline HRESULT ScreenElementFromAccessibleObject(IAccessible *pAcc, VARIANT ChildId, IScreenElement** screenElement)
    {
        if(NULL == pAcc)
        {
            return E_FAIL;
        }

        // Create VARIANT for IDispatch that corresponds to IAccessible
        VARIANT varDisp;

        if(S_OK == pAcc->QueryInterface(__uuidof(IDispatch), (void**)&(varDisp.pdispVal)) && varDisp.pdispVal != NULL)
        {
            varDisp.vt = VT_DISPATCH;
        }
        else
        {
            return E_FAIL;
        }

        HRESULT hr = g_pRPFPlayback->ScreenElementFromAccessibleObject(varDisp, ChildId, screenElement);

        varDisp.pdispVal->Release();

        return hr;
    }

    inline HRESULT ScreenElementFromHTMLElement(IHTMLElement* pIHTMLElement, IScreenElement** ppScreenElement)
    {
        return g_pRPFPlayback->ScreenElementFromHTMLElement(pIHTMLElement, ppScreenElement);
    }

    inline HRESULT ScreenElementFromWinEvent(IScreenElement** ppscreenElement)
    {
        return g_pRPFPlayback->ScreenElementFromWinEvent(ppscreenElement);
    }

    inline HRESULT StartWaitingForAnyWinEvent(int cWinEventHandles, ...)
    {
        va_list arguments;
        va_start(arguments, cWinEventHandles);

        // Convert array of IWinEventHandle to an array of VARIANTs since playback expects SAFEARRAY (VARIANT)
        VARIANT *pvarWinEvents;
        SAFEARRAYBOUND arrayBound[1];
        arrayBound[0].lLbound = 0; arrayBound[0].cElements = cWinEventHandles;

        SAFEARRAY* saWinEventHandles = SafeArrayCreate(VT_VARIANT, 1, arrayBound);

        if (saWinEventHandles == NULL)
        {
            return E_FAIL;
        }

        if (S_OK != SafeArrayAccessData(saWinEventHandles, (void **)&pvarWinEvents))
        {
            return E_FAIL;
        }

        for (int i = 0; i < cWinEventHandles; i++)
        {
            if ((NULL != (pvarWinEvents[i].punkVal = va_arg(arguments, WinEventHandle*))))
            {
                pvarWinEvents[i].punkVal->AddRef();
                pvarWinEvents[i].vt = VT_UNKNOWN;
            }
            else
            {
                return E_FAIL;
            }
        }

        SafeArrayUnaccessData(saWinEventHandles);
        
        HRESULT hr = g_pRPFPlayback->StartWaitingForAnyWinEvent(saWinEventHandles, cWinEventHandles);

        SafeArrayDestroy(saWinEventHandles);

        return hr;
    }

    inline HRESULT LeftButtonClick(INT x, INT y)
    {
        return g_pRPFPlayback->LeftButtonClick(x, y);
    }

    inline HRESULT LeftButtonClick(INT x, INT y, BOOL fEnsureVisible, wchar_t* pszKeyModifiers)
    {
        return g_pRPFPlayback->LeftButtonClick(x, y, fEnsureVisible, CComBSTR(pszKeyModifiers));
    }

    inline HRESULT DoubleClick(INT x, INT y)
    {
        return g_pRPFPlayback->DoubleClick(x, y);
    }

    inline HRESULT DoubleClick(INT x, INT y, BOOL fEnsureVisible, wchar_t* pszKeyModifiers)
    {
        return g_pRPFPlayback->DoubleClick(x, y, fEnsureVisible, CComBSTR(pszKeyModifiers));
    }

    inline HRESULT RightButtonClick(INT x, INT y)
    {
        return g_pRPFPlayback->RightButtonClick(x, y);
    }

    inline HRESULT RightButtonClick(int x, int y, BOOL fEnsureVisible, wchar_t* pszKeyModifiers)
    {
        return g_pRPFPlayback->RightButtonClick(x, y, fEnsureVisible, CComBSTR(pszKeyModifiers));
    }

    inline HRESULT Expand()
    {
        return g_pRPFPlayback->Expand(ECF_USE_TVM_EXPAND | ECF_USE_DOUBLECLICK | ECF_USE_NUMPAD | ECF_USE_ENTER);
    }

    inline HRESULT Expand(int nExpandCollapseFlag)
    {
        return g_pRPFPlayback->Expand(nExpandCollapseFlag);
    }

    inline HRESULT Check(BOOL fSetIndeterminate, BOOL fVerifyFinalState = TRUE)
    {
        return g_pRPFPlayback->Check(fSetIndeterminate, fVerifyFinalState);
    }

    inline HRESULT Check()
    {
        return g_pRPFPlayback->Check(FALSE, TRUE);
    }

    inline HRESULT Collapse()
    {
        return g_pRPFPlayback->Collapse(ECF_USE_TVM_EXPAND | ECF_USE_DOUBLECLICK | ECF_USE_NUMPAD | ECF_USE_ENTER);
    }

    inline HRESULT Collapse(int nExpandCollapseFlag)
    {
        return g_pRPFPlayback->Collapse(nExpandCollapseFlag);
    }

    inline HRESULT EnsureVisible(int nEnsureVisibleFlag = EVF_BY_SCROLLING, int x = -1, int y = -1, IScrollerCallback* pScrollerCallback = NULL, int nScrollFlag = SF_SCROLL_BAR | SF_WHEEL, int nMaximumContainers = 2)
    {
        return g_pRPFPlayback->EnsureVisible(nEnsureVisibleFlag, x, y, pScrollerCallback, nScrollFlag, nMaximumContainers);
    }

    inline HRESULT Select()
    {
        return g_pRPFPlayback->Select();
    }

    inline HRESULT Select(int nSelectionFlag)
    {
        return g_pRPFPlayback->Select(nSelectionFlag);
    }

    inline HRESULT SendKeys(wchar_t* keys, int nKeyboardAction = HIT)
    {
        return g_pRPFPlayback->SendKeys(CComBSTR(keys), nKeyboardAction);
    }

    inline HRESULT SetValueAsComboBox(wchar_t* newValue, INT nSetValueAsComboBoxFlag = CF_USE_SET_AS_EDIT | CF_USE_SELECT)
    {
        return g_pRPFPlayback->SetValueAsComboBox(CComBSTR(newValue), nSetValueAsComboBoxFlag);
    }

    inline HRESULT SetValueAsEditBox(wchar_t* newValue, INT nSetValueAsEditBoxFlag = EF_DELETE_CONTENT | EF_USE_SENDKEYS)
    {
        return g_pRPFPlayback->SetValueAsEditBox(CComBSTR(newValue), nSetValueAsEditBoxFlag);
    }

    inline HRESULT SetValueAsSlider(wchar_t* newValue, int nOrientation = DF_AUTO) // defaultvalue DF_AUTO - Playback should define the orientation itself
    {
        return g_pRPFPlayback->SetValueAsSlider(CComBSTR(newValue), nOrientation);
    }

    inline HRESULT StartDragging(INT x, INT y, int nDraggingButton = LEFT_BUTTON)
    {
        return g_pRPFPlayback->StartDragging(x, y, nDraggingButton, NULL, true);
    }

    inline HRESULT StartDragging(INT x, INT y, int nDraggingButton, wchar_t* pszKeyModifiers, BOOL fEnsureVisible = TRUE)
    {
        return g_pRPFPlayback->StartDragging(x, y, nDraggingButton, CComBSTR(pszKeyModifiers), fEnsureVisible);
    }

    inline HRESULT StopDragging (INT x, INT y, INT nSpeedPixelPerSecond = 50)
    {
        return g_pRPFPlayback->StopDragging(x, y, nSpeedPixelPerSecond);
    }

    inline HRESULT MoveMouse(INT x, INT y, BOOL fEnsureVisible = TRUE, INT nSpeedPixelPerSecond = 50)
    {
        return g_pRPFPlayback->MoveMouse(x, y, fEnsureVisible, nSpeedPixelPerSecond);
    }

    inline HRESULT MouseWheel(INT nDelta)
    {
        return g_pRPFPlayback->MouseWheel(nDelta, NULL);
    }

    inline HRESULT MouseWheel(INT nDelta, wchar_t* pszKeyModifiers)
    {
        return g_pRPFPlayback->MouseWheel(nDelta, CComBSTR(pszKeyModifiers));
    }

    inline HRESULT Uncheck(BOOL fVerifyFinalState = TRUE)
    {
        return g_pRPFPlayback->Uncheck(fVerifyFinalState);
    }

    inline HRESULT WaitForReady()
    {
        return g_pRPFPlayback->WaitForReady();
    }

    inline HRESULT SetCustomLogger(ILoggerCallback* LoggerCallback)
    {
        return g_pRPFPlayback->SetCustomLogger(LoggerCallback);
    }

    inline HRESULT EnableInfoWindow(BOOL fEnable)
    {
        return g_pRPFPlayback->EnableInfoWindow(fEnable);
    }

    inline HRESULT EnableEnsureVisibleForPrimitive(BOOL fEnable)
    {
        BOOL f;
        return g_pRPFPlayback->EnableEnsureVisibleForPrimitive(fEnable, &f);
    }

    inline HRESULT VerifyScreenElement(wchar_t* pszState, wchar_t* pszValue)
    {
        return g_pRPFPlayback->VerifyScreenElement(CComBSTR(pszState), CComBSTR(pszValue));
    }

    // TODO dklem remove GetScreenElementInfo after Vista RTM
    #pragma deprecated(GetScreenElementInfo)

    inline HRESULT GetScreenElementInfo(wchar_t* pszUIElementName, int ccName, TCHAR* szUIElementRole, int ccRole, wchar_t* pszUIElementClass, int ccClass, wchar_t* pszValue, int ccValue, wchar_t* pszState, int ccState)
    {
        pszUIElementName = pszUIElementClass = pszValue = pszState = NULL;
        szUIElementRole = NULL;
        ccName = ccRole = ccClass = ccValue = ccState = 0;
        return E_NOTIMPL;
    }

    inline HRESULT BringScreenElementUp()
    {
        return g_pRPFPlayback->BringScreenElementUp();
    }

    inline HRESULT TypeString(wchar_t* szKeys)
    {
        return g_pRPFPlayback->TypeString(CComBSTR(szKeys), 50, FALSE, HIT);
    }

    inline HRESULT TypeString(wchar_t* szKeys, int nSleepBetweenActions, BOOL fLiteral = FALSE, int nKeyboardAction = HIT)
    {
        return g_pRPFPlayback->TypeString(CComBSTR(szKeys), nSleepBetweenActions, fLiteral, nKeyboardAction);
    }

    inline HRESULT LockNextSearches(BOOL bLock)
    {
        return g_pRPFPlayback->LockNextSearches(bLock);
    }

    inline bool IsAvailable(int nTimeOut, wchar_t* pszQueryId, ...)
    {
        // Initialize variable arguments.
        va_list arguments;
        va_start( arguments, pszQueryId);

        // Set timeout
        int nOriginalSearchTimeOut = SetSearchTimeOut(nTimeOut);

        // Set logging flag, so no dumpscreen is performed and failure is recorded as info
        int nOriginalLoggingFlag = SetLoggingFlag(0);

        // No Dump Screen
        int nNewLoggingFlag = nOriginalLoggingFlag & ~FL_LOG_DUMP_SCREEN;

        // Log failure as info
        nNewLoggingFlag |= FL_LOG_FAILURE_AS_INFO;

        // Set new logging flag
        SetLoggingFlag(nNewLoggingFlag);

        bool fResult = (S_OK == FromPartialQueryId(NULL, NULL, pszQueryId, arguments));

        // Restore timeout
        SetSearchTimeOut(nOriginalSearchTimeOut);

        // Restore logging flag
        SetLoggingFlag(nOriginalLoggingFlag);

        return fResult;
    }

    inline HRESULT ExtractResourceString(const wchar_t* resourceKey, wchar_t* pszResourceString, int ccResourceString)
    {
        BSTR bstrResourceString = NULL;

        HRESULT hr =  g_pRPFPlayback->ExtractResourceString(CComBSTR(resourceKey), &bstrResourceString);

        if (hr == S_OK && pszResourceString != NULL && bstrResourceString != NULL && ccResourceString > 0)
        {
            StringCchCopyW(pszResourceString, ccResourceString, bstrResourceString);
        }

        SysFreeString(bstrResourceString);

        return hr;
    }

    inline HRESULT WaitForWindowEx( int nTimeOut, wchar_t* pszQueryId, ... )
    {
        HRESULT hr;

        // Initialize variable arguments.
        va_list arguments;
        va_start( arguments, pszQueryId);     

        int nPreviousSearchTimeOut = SetSearchTimeOut(nTimeOut);
        hr = FromPartialQueryId(NULL, NULL, pszQueryId, arguments);
        SetSearchTimeOut(nPreviousSearchTimeOut);

        return hr;
    }

    inline HRESULT DumpScreen(wchar_t* pszFileName, INT nFileFormat = DUMP_SCREEN_JPEG)
    {
        return g_pRPFPlayback->DumpScreen(CComBSTR(pszFileName), nFileFormat);
    }

    inline HRESULT SetNextActionDelay(int nDelayTime)
    {
        return g_pRPFPlayback->SetNextActionDelay(nDelayTime);
    }
     
    inline HRESULT GlobalizeQueryId(wchar_t* pszGlobalizedQueryId, int cchGlobalizedQueryId, wchar_t* pszQueryId, ...)
    {
        // Initialize variable arguments.
        va_list arguments;
        va_start(arguments, pszQueryId);  

        int nTotalResourceKeys = 0;
        wchar_t (*pszAllResourceKeys)[MAX_RES_KEY_LENGTH];

        // Note that ComposeQueryId allocates memory for pszAllResourceKeys and GlobalizeQueryId releases it
        ComposeQueryId(pszQueryId, arguments, &nTotalResourceKeys, &pszAllResourceKeys);
        return GlobalizeQueryId(pszGlobalizedQueryId, cchGlobalizedQueryId, pszQueryId, nTotalResourceKeys, pszAllResourceKeys);
    }

    inline HRESULT SetCurrentUsers(wchar_t* pszurrentUsers)
    {
        return g_pRPFPlayback->SetCurrentUsers(CComBSTR(pszurrentUsers));
    }

    inline HRESULT SetWFRTimeOut(int nTimeOut)
    {
        VARIANT varParamValue;
        varParamValue.vt = VT_I4;
        varParamValue.lVal = nTimeOut;
        return g_pRPFPlayback->SetPlaybackProperty(WFR_TIMEOUT, varParamValue);
    }

    inline HRESULT SetAccTechnology(int nAccTechnology)
    {
        return g_pRPFPlayback->SetAccTechnology(nAccTechnology);
    }

    inline HRESULT EnableUISynchronization(BOOL fEnableUISync)
    {
        return g_pRPFPlayback->EnableUISynchronization(fEnableUISync);
    }

    inline HRESULT GetPlaybackProperty(int nParam, VARIANT* pVarParamValue)
    {
        return g_pRPFPlayback->GetPlaybackProperty(nParam, pVarParamValue);
    }

    inline HRESULT SetPlaybackProperty(int nParam, VARIANT varParamValue)
    {
        return g_pRPFPlayback->SetPlaybackProperty(nParam, varParamValue);
    }

    inline HRESULT SetTargetLanguageId(int nTargetLanguageId)
    {
        return g_pRPFPlayback->put_TargetLanguageId(nTargetLanguageId);
    }

    inline HRESULT SetMUILanguageId(int nTMUILanguageId)
    {
        return g_pRPFPlayback->put_MUILanguageId(nTMUILanguageId);
    }

    inline HRESULT SetTargetLanguageName(wchar_t* pszTargetLanguageName)
    {
        return g_pRPFPlayback->put_TargetLanguageName(CComBSTR(pszTargetLanguageName));
    }

    #pragma endregion RPFPlaybackNameSpace Functions definitions

    #pragma region Cursor functionality

    inline HRESULT WaitForCursor(BOOL fWaitForAnyCursor, INT nElapse, INT nTimeOut, int cTotalCursors, int *pnCursors)
    {
        int* pnData;
        SAFEARRAYBOUND arrayBound[1];
        arrayBound[0].lLbound = 0; arrayBound[0].cElements = cTotalCursors;

        LPSAFEARRAY saCursors = SafeArrayCreate(VT_VARIANT, 1, arrayBound);

        if (saCursors == NULL)
        {
            return E_FAIL;
        }

        if (S_OK != SafeArrayAccessData(saCursors, (void **)&pnData))
        {
            return E_FAIL;
        }

        for (int i = 0; i < cTotalCursors; i++)
        {
            pnData[i] = pnCursors[i];
        }
        
        SafeArrayUnaccessData(saCursors);

        return g_pRPFPlayback->WaitForCursor(0, fWaitForAnyCursor, nElapse, nTimeOut, saCursors, cTotalCursors);
    }

    inline HRESULT WaitForAnyCursor(INT nElapse, INT nTimeOut, int cTotalCursors, ...)
    {
        // Initialize variable arguments.
        va_list arguments;
        va_start( arguments, cTotalCursors); 

        // Initialize the array of cursors
        int *pnCursors = new int[cTotalCursors];

        if (pnCursors == NULL)
        {
            LogInformation(L"[WARNING] Internal failure in wrapper: Not enough memory for the Cursors array\r\n", FALSE);
            return E_FAIL;
        }

        for (int i = 0; i < cTotalCursors; i++)
        {
            pnCursors[i] = va_arg(arguments, int);
        }

        // Reset variable arguments
        va_end( arguments );              

        HRESULT hr = WaitForCursor(true, nElapse, nTimeOut, cTotalCursors, pnCursors);

        delete [] pnCursors;

        return hr;
    }

    inline HRESULT WaitForCursorGone(INT nElapse, INT nTimeOut, LPSTR cursor)
    {
        int pnCursors[1];
        pnCursors[0] = (int) cursor;

        HRESULT hr = WaitForCursor(false, nElapse, nTimeOut, 1, pnCursors);

        return hr;
    }

    inline HRESULT GetCurrentCursor(INT *nCursor)
    {
        return g_pRPFPlayback->GetCurrentCursor(0, nCursor);
    }

    #pragma endregion Cursor functionality
    
    #pragma region Complex String support

    inline CStringW DecorateString(wchar_t* pszString)
    {
        if (pszString == NULL)
        {
            return L"";
        }

        // Find decorationChar
        wchar_t chDecorationChar;
        bool fDecorationCharFound = false;
        for (chDecorationChar = L'#'; chDecorationChar < 254; chDecorationChar++)
        {
            if (!wcsstr(pszString, &chDecorationChar))
            {
                fDecorationCharFound = true;
                break;
            }
        }

        // Construct FullStringId
        if (!fDecorationCharFound)
        {
            return L"";
        }

        // Add three decorationChars in the beginning and three at the end
        CStringW csDecoration = CStringW(chDecorationChar) + CStringW(chDecorationChar) + CStringW(chDecorationChar);

        return csDecoration + pszString + csDecoration;
    }

    class LanguageNeutralString
    {
    private:
        // LanguageNeutralString class should start with two byte signature (LANG_NEUTRALSTRING_SIGNATURE) that a resKey string should not start with
        // This signature is used to distingush between objects that (void*)pointers in QueryId class point to
        // See QueryId::operator wchar_t*() for details
        // This class should not have virtual methods
        // Note: if the type or order of memebers changes make sure that corresponding changes are made in ComposeQueryId 
        //		 Search for LANG_NEUTRALSTRING_SIGNATURE in this function for details
        const short _sSignature;
        CStringW _csActualString;

    public:
        LanguageNeutralString(wchar_t* pszActualString) : _sSignature (LANG_NEUTRALSTRING_SIGNATURE)
        {
            // Decorate extracted string to notify the caller that it's not a res key but the actual string
            _csActualString = DecorateString(pszActualString);
        }

        // This operator performs actual resource extraction
        operator wchar_t*()
        {
            return _csActualString.GetBuffer();
        }
    };

    class AnyResourceKey
    {
    private:

        // AnyResourceKey class should start with two byte signature (ANY_RESOURCE_KEY_SIGNATURE) that a resKey string should not start with
        // This signature is used to distingush between objects that (void*)pointers in QueryId class point to
        // See QueryId::operator wchar_t*() for details
        // This class should not have virtual methods
        const short _sSignature;
        wchar_t (*m_pszAllResourceKeys)[MAX_RES_KEY_LENGTH];
        int m_nTotalResourceKeys;
        CStringW _csExtractedString;

    public:
        AnyResourceKey(int nTotalResourceKeys, wchar_t* pszResourceKey, ... ) : _sSignature (ANY_RESOURCE_KEY_SIGNATURE)
        {
            // Initialize variable arguments.
            va_list arguments;
            va_start(arguments, pszResourceKey); 
            arguments -= sizeof(wchar_t*);

            m_nTotalResourceKeys = nTotalResourceKeys;
            m_pszAllResourceKeys = new wchar_t[nTotalResourceKeys][MAX_RES_KEY_LENGTH];

            wchar_t *pszCurrentArg = pszResourceKey;

            for (int i = 0; pszCurrentArg && i < nTotalResourceKeys; i++)
            {
                if ((NULL != (pszCurrentArg = va_arg(arguments, wchar_t*))))
                {
                    StringCchCopyW((m_pszAllResourceKeys)[i], MAX_RES_KEY_LENGTH, pszCurrentArg);
                }
            }

            // Reset variable arguments
            va_end( arguments );              
        }

        ~AnyResourceKey()
        {
            delete[] m_pszAllResourceKeys;
        }

        // This operator performs actual resource extraction
        operator wchar_t*()
        {
            wchar_t pszResourceString[MAX_VALUE_LENGTH];

            for (int i = 0; i < m_nTotalResourceKeys; i++)
            {
                if (S_OK == ExtractResourceString(m_pszAllResourceKeys[i], pszResourceString, ARRAYSIZE(pszResourceString)))
                {
                    // Decorate extracted string to notify the caller that it's not a res key but extracted string
                    _csExtractedString = DecorateString(pszResourceString);

                    return _csExtractedString.GetBuffer();
                }
            }

            return L"";
        }
    };

    class ComplexResourceKeyNative
    {
    private:
        // ComplexResourceKeyNative class should start with two byte signature (COMPLEX_RESOURCE_KEY_NATIVE_SIGNATURE) that a resKey string should not start with
        // This signature is used to distingush between objects that (void*)pointers in QueryId class point to
        // See QueryId::operator wchar_t*() for details
        // This class should not have virtual methods
        const short _sSignature;
        CStringW _csPrimaryResourceKey;
        CStringW *_pcsComposingResourceKeys;
        CStringW _csExtractedString;
        bool _fExtracted;
        int _nTotalCompositeResKeys;

    public:

        ~ComplexResourceKeyNative()
        {
            if (_pcsComposingResourceKeys != NULL)
            {
                delete [] _pcsComposingResourceKeys;
                _pcsComposingResourceKeys = NULL;
            }
        }

    private:
        void InitializeComplexResourceKeyNative(int nTotalComposingResourceKeys, const wchar_t* pszPrimaryResourceKey,  va_list composingResourceKeys)
        {
            // Initialize composite keys
            _pcsComposingResourceKeys = NULL;
            _fExtracted  = false;

            if (pszPrimaryResourceKey == NULL)
            {
                return;
            }

            _csPrimaryResourceKey = pszPrimaryResourceKey;
            _nTotalCompositeResKeys = nTotalComposingResourceKeys;

            // Allocate memory for composite keys
            _pcsComposingResourceKeys = new CStringW[_nTotalCompositeResKeys];

            if (_pcsComposingResourceKeys == NULL)
            {
                LogInformation(L"[WARNING] Internal failure in wrapper: Not enough memory for the Composing Resource Keys\r\n", FALSE);
                return ;
            }

            // Initialize current pointer
            wchar_t *pszCurrentPointer = (wchar_t *) pszPrimaryResourceKey;

            for (int i = 0; i < _nTotalCompositeResKeys; i++)
            {
                if ((NULL != (pszCurrentPointer = va_arg(composingResourceKeys, wchar_t*))))
                {
                    _pcsComposingResourceKeys[i] = pszCurrentPointer;
                }
            }
        }

    public:
        ComplexResourceKeyNative(int nTotalComposingResourceKeys, const wchar_t* pszPrimaryResourceKey, ...) : _sSignature (COMPLEX_RESOURCE_KEY_NATIVE_SIGNATURE)
        {
            // Initialize variable arguments.
            va_list composingResourceKeys;
            va_start(composingResourceKeys, pszPrimaryResourceKey);     

            InitializeComplexResourceKeyNative(nTotalComposingResourceKeys, pszPrimaryResourceKey, composingResourceKeys);
        }

        ComplexResourceKeyNative(const wchar_t* pszPrimaryResourceKey, ...) : _sSignature (COMPLEX_RESOURCE_KEY_NATIVE_SIGNATURE)
        {
            int nTotalComposingResourceKeys;
            int nLen = (int) wcslen(pszPrimaryResourceKey);
            wchar_t *pszCurrentPointer;

            // Initialize variable arguments.
            va_list composingResourceKeys;
            va_start(composingResourceKeys, pszPrimaryResourceKey);     

            // Calculate the number of composite keys
            for (nTotalComposingResourceKeys = 0, pszCurrentPointer = (wchar_t *) pszPrimaryResourceKey; pszCurrentPointer < pszPrimaryResourceKey + nLen - 1; pszCurrentPointer++)
            {
                // Increment the total number of composite keys if % and not %% is encountered
                if (*pszCurrentPointer == L'%')
                {
                    // In the case of %% just skip it
                    if ( *(pszCurrentPointer + 1) == '%')
                    {
                        pszCurrentPointer++;
                    }
                    else
                    {
                        nTotalComposingResourceKeys++;
                    }
                }
            }

            InitializeComplexResourceKeyNative(nTotalComposingResourceKeys, pszPrimaryResourceKey, composingResourceKeys);
        }

        CStringW Extract()
        {
            int nComponentsInMessageFormatString = 0;
            int nIndexBegin;
            int nPrimaryResourceStringLen;
            HRESULT hr;
            wchar_t pszResourceString[MAX_VALUE_LENGTH];
            CStringW csPrimaryResourceString(L"");

            // Verify if the first string in the complex reskey is a key or just a fomatting string.  It is a formatting string if embraced with {}
            if (_csPrimaryResourceKey[0] == L'{' && _csPrimaryResourceKey[_csPrimaryResourceKey.GetLength()- 1] == L'}')
            {
                csPrimaryResourceString = _csPrimaryResourceKey.Mid(1, _csPrimaryResourceKey.GetLength() - 2);
            }
            else
            {
                ExtractResourceString(_csPrimaryResourceKey.GetBuffer(), pszResourceString, ARRAYSIZE(pszResourceString));
                csPrimaryResourceString = pszResourceString;
            }

            // Get length for the Primary resource string
            nPrimaryResourceStringLen = csPrimaryResourceString.GetLength();

            // Verify that the length for the Primary resource string is greater than zero
            if (0 == nPrimaryResourceStringLen)
            {
                return L"";
            }
                
            CStringW* pcsComposingResourceStrings = new CStringW[_nTotalCompositeResKeys];

            if (pcsComposingResourceStrings == NULL)
            {
                LogInformation(L"[WARNING] Internal failure in wrapper: Not enough memory for the composing resource strings\r\n", FALSE);
                return L"";
            }

            for (int i = nIndexBegin = 0; i < _nTotalCompositeResKeys; i++)
            {
                // Extract composing strings
                hr = ExtractResourceString(_pcsComposingResourceKeys[i].GetBuffer(), pszResourceString, ARRAYSIZE(pszResourceString));

                pcsComposingResourceStrings[i] = pszResourceString;

                if (hr != S_OK || 0 == pcsComposingResourceStrings[i].GetLength())
                {
                    delete[]pcsComposingResourceStrings;
                    return L"";
                }

                // In the case of native formatting replace %s with composite string
                for (; nIndexBegin < nPrimaryResourceStringLen - 1; nIndexBegin++)
                {
                    // If % and not %% is encountered
                    if (csPrimaryResourceString[nIndexBegin] == '%') 
                    {
                        // In the case of %% just skip it
                        if (csPrimaryResourceString[nIndexBegin + 1] == '%')
                        {
                            nIndexBegin++;
                        }
                        else if (0 < csPrimaryResourceString[nIndexBegin + 1] - L'0' && 0 <= L'9' - csPrimaryResourceString[nIndexBegin + 1])
                        {
                            nComponentsInMessageFormatString++;
                        }
                        else
                        {
                            int indexEnd;

                            // Find first space
                            for (indexEnd = nIndexBegin + 1; indexEnd < nPrimaryResourceStringLen
                                && (	csPrimaryResourceString[indexEnd] == 's'
                                    ||	csPrimaryResourceString[indexEnd] == 'S'
                                    ||	csPrimaryResourceString[indexEnd] == 'd'
                                    ||	csPrimaryResourceString[indexEnd] == 'D'
                                    ||	csPrimaryResourceString[indexEnd] == '0'
                                    )
                                ; indexEnd++);

                            // Delete formatting sub-string
                            csPrimaryResourceString.Delete(nIndexBegin, indexEnd - nIndexBegin);

                            // Insert actual string
                            csPrimaryResourceString.Insert(nIndexBegin, pcsComposingResourceStrings[i]);

                            // Adjust nIndexBegin
                            nIndexBegin += pcsComposingResourceStrings[i].GetLength();

                            // Update the length for the Primary resource string
                            nPrimaryResourceStringLen = csPrimaryResourceString.GetLength();

                            // After the first found %spec has replaced, break to use the next resource string
                            break;
                        }
                    }
                }
            }

            if(nComponentsInMessageFormatString == _nTotalCompositeResKeys)
            {
                PWSTR* pInserts = new PWSTR[_nTotalCompositeResKeys];

                if(pInserts == NULL)
                {
                    LogInformation(L"[WARNING] Internal failure in wrapper: Not enough memory for an array of composing resource strings used in FormatMessage\r\n", FALSE);
                    delete[]pcsComposingResourceStrings;
                    return L"";
                }

                for (int i = nIndexBegin = 0; i < _nTotalCompositeResKeys; i++)
                {
                    pInserts[i] = pcsComposingResourceStrings[i].GetBuffer();
                }

                LPWSTR pszFormattedString;
                FormatMessageW(FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ALLOCATE_BUFFER, 
                               csPrimaryResourceString.GetBuffer(), 0, 0, (LPWSTR)&pszFormattedString, csPrimaryResourceString.GetLength(), (va_list*) pInserts);

                csPrimaryResourceString = pszFormattedString;
                LocalFree(pszFormattedString);
                delete [] pInserts;
            }
            else if(0 < nComponentsInMessageFormatString)
            {
                LogInformation(L"[WARNING] Internal failure in wrapper: Number of composing resource strings  doesn't match the number of \"%n\" specifiers in the primary resource string\r\n", FALSE);
                delete[]pcsComposingResourceStrings;
                return L"";
            }

            delete[]pcsComposingResourceStrings;

            return csPrimaryResourceString;
        }

        // This operator performs actual resource extraction
        operator wchar_t*()
        {
            if (!_fExtracted)
            {
                // Extract resource string
                _csExtractedString = Extract();

                // Decorate extracted string to notify the caller that it's not a res key but extracted string
                _csExtractedString = DecorateString(_csExtractedString.GetBuffer());

                _fExtracted = true;
            }

            return _csExtractedString.GetBuffer();
        }

    };

    #pragma endregion Complex String support

    #pragma region QueryId

    class QueryId
    {
    private:
        int _nTotalResourceKeys;
        void **_pszAllResourceKeys;
        CStringW _csQueryId;
        CString _csId;
        int *_pnRefResKeys;

    public:

        QueryId(wchar_t* pszQueryId, ...)
        {
            // Initialize variable arguments.
            va_list arguments;
            va_start( arguments, pszQueryId);  

            InitQueryId(NULL, pszQueryId, arguments);
        }

        QueryId(char* pszId, wchar_t* pszQueryId, ...)
        {
            // Initialize variable arguments.
            va_list arguments;
            va_start( arguments, pszQueryId);  

            InitQueryId(pszId, pszQueryId, arguments);
        }

        // Copy constructor
        QueryId(const QueryId & rhQueryId)
        {
            _nTotalResourceKeys = rhQueryId._nTotalResourceKeys;
            _csQueryId = rhQueryId._csQueryId;
            _csId = rhQueryId._csId;

            _pszAllResourceKeys = rhQueryId._pszAllResourceKeys;
            _pnRefResKeys = rhQueryId._pnRefResKeys;

            if(rhQueryId._pszAllResourceKeys && rhQueryId._pnRefResKeys)
            {
                (*_pnRefResKeys)++;
            }
        }

        ~QueryId()
        {
            if(_pszAllResourceKeys && _pnRefResKeys && --(*_pnRefResKeys) == 0)
            {
                delete [] _pszAllResourceKeys;
                delete _pnRefResKeys;
            }
        }

        // This operator performs actual resource extraction
        operator wchar_t*()
        {
            if(0 < _nTotalResourceKeys)
            {
                // Create new wchar_t array to fill it with values of resKeys
                // This is necessary for not simple resources keys since cast to wchar_t* performs actual resource extraction
                // via "operator wchar_t*()"
                // Each resource class has a two byte signature that a resKey string should not start with, so there is a way to distingush
                // between objects that (void*)_pszAllResourceKeys[i] points to 
                wchar_t (*pszAllResourceKeys)[MAX_RES_KEY_LENGTH] = new wchar_t[_nTotalResourceKeys][MAX_RES_KEY_LENGTH];

                if ((*pszAllResourceKeys) == NULL)
                {
                    LogInformation(L"[WARNING] Internal failure in wrapper: Not enough memory for the Resource Keys array for QuieryId\r\n", FALSE);
                    _nTotalResourceKeys = 0;

                    return _csQueryId.GetBuffer();
                }

                // TODO (dklem) create a better mechanism of defining the length of the globalized QueryId
                int nLen = _csQueryId.GetLength() * 2;
                wchar_t* pszGlobalizedQueryId = new wchar_t[nLen];

                for(int i = 0; i < _nTotalResourceKeys; i++)
                {
                    wchar_t* pszResKey;

                    if(COMPLEX_RESOURCE_KEY_NATIVE_SIGNATURE == *((short*)_pszAllResourceKeys[i]))
                    {
                        pszResKey = (wchar_t*) *((ComplexResourceKeyNative*) _pszAllResourceKeys[i]);
                    }
                    else if(ANY_RESOURCE_KEY_SIGNATURE == *((short*)_pszAllResourceKeys[i]))
                    {
                        pszResKey = (wchar_t*) *((AnyResourceKey*) _pszAllResourceKeys[i]);
                    }
                    else if(LANG_NEUTRALSTRING_SIGNATURE == *((short*)_pszAllResourceKeys[i]))
                    {
                        pszResKey = (wchar_t*) *((LanguageNeutralString*) _pszAllResourceKeys[i]);
                    }
                    else
                    {
                        pszResKey = (wchar_t*) _pszAllResourceKeys[i];
                    }
                    
                    StringCchCopyW(pszAllResourceKeys[i], MAX_RES_KEY_LENGTH, pszResKey);
                }

                // Globalize QueryId, and GlobalizeQueryId releases memory for pszAllResourceKeys 
                GlobalizeQueryId(pszGlobalizedQueryId, nLen, _csQueryId.GetBuffer(), _nTotalResourceKeys, pszAllResourceKeys);

                // Save globalized QueryId
                _csQueryId = pszGlobalizedQueryId;

                // Set _nTotalResourceKeys equals to zero, which means that this QueryId is already globalized
                _nTotalResourceKeys = 0;

                // Delete temporary QueryId
                delete[] pszGlobalizedQueryId;
            }

            return _csQueryId.GetBuffer();
        }

    private:

        void InitQueryId(char* pszId, wchar_t* pszQueryId, va_list arguments)
        {
            void* pszCurrentArg = pszQueryId;
            wchar_t szFormatterIndex[MAX_INDEX_LENGTH];

            // Init "raw" Query id and Id
            _csQueryId = pszQueryId;

            if(pszId != NULL)
            {
                _csId = pszId;
            }
            else
            {
                _csId = "";
            }

            // Calculate how many resource keys were requested in QueryId
            for (_nTotalResourceKeys = 0; ; _nTotalResourceKeys++)
            {
                StringCchPrintfW(szFormatterIndex, ARRAYSIZE(szFormatterIndex), L"{%d}", _nTotalResourceKeys);
                if (!wcsstr(pszQueryId, szFormatterIndex))
                {
                    break;
                }
            }

            // Copy resource keys to array of void pointers.
            // Should not cast to strings since this will cause resource extraction which should not happen until QId is used in FromPartialQueryId
            // to find UScreenElement
            if (_nTotalResourceKeys > 0)
            {
                _pszAllResourceKeys = new void*[_nTotalResourceKeys];

                for (int i = 0; NULL != pszCurrentArg && i < _nTotalResourceKeys; i++)
                {
                    if ((NULL != (pszCurrentArg = va_arg(arguments, void*))))
                    {
                        _pszAllResourceKeys[i] = pszCurrentArg;
                    }
                }

                // Reset variable arguments
                va_end( arguments );    
                _pnRefResKeys = new int;

                if(_pnRefResKeys)
                {
                    *_pnRefResKeys = 1;
                }
            }
            else
            {
                _pszAllResourceKeys = NULL;
                _pnRefResKeys = NULL;
            }
        }
    };

    #pragma endregion QueryId
}

#pragma warning (default : 4311)
#pragma warning (default : 4312)
#pragma warning (default : 4995)
#pragma warning (default : 4996)