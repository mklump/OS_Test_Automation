#include "RPFPlaybackNameSpace.h"

#ifndef __WTTLOGSUPPORT_H__
#define __WTTLOGSUPPORT_H__

namespace RPFPlayback
{
    #pragma region WTT Logging Internal support

    #define WTT_LVL_MSG                   0x10000000
    #define WTT_LVL_ERR                   0x01000000
    #define WTT_LVL_WARN                  0x00200000

    typedef HRESULT (WINAPI *WTTLogCreateLogDevice)(wchar_t*, long*);
    typedef HRESULT (*WTTLogTrace)(long, long, wchar_t*);
    typedef HRESULT (WINAPI *WTTLogCloseLogDevice)(long, wchar_t*);

    #define DEFAULT_DEVICE_STRING L"$logfile"

    extern BOOL g_fDumpScreen;
    __declspec(selectany) BOOL g_fDumpScreen;

    extern BOOL g_fLogDefault;
    __declspec(selectany) BOOL g_fLogDefault;

    extern long g_hDevice;
    __declspec(selectany) long g_hDevice;

    extern WTTLogCreateLogDevice g_lpfnWTTLogCreateLogDevice;
    __declspec(selectany) WTTLogCreateLogDevice g_lpfnWTTLogCreateLogDevice;

    extern WTTLogTrace g_lpfnWTTLogTrace;
    __declspec(selectany) WTTLogTrace g_lpfnWTTLogTrace;

    extern WTTLogCloseLogDevice g_lpfnWTTLogCloseLogDevice;
    __declspec(selectany) WTTLogCloseLogDevice g_lpfnWTTLogCloseLogDevice;

    /// <summary>
    /// WTT Logger Callback 
    /// </summary>
    inline HRESULT WTTLoggerCallBack(BSTR* bstrLogString, BOOL *pfLogDefault, BOOL *pfDumpScreen) 
    {
        if(wcsstr(*bstrLogString, L"[WARNING]")) 
        {
            g_lpfnWTTLogTrace(g_hDevice, WTT_LVL_WARN, *bstrLogString);
        }
        else if(wcsstr(*bstrLogString, L"[FAILED]")) 
        {
            g_lpfnWTTLogTrace(g_hDevice, WTT_LVL_ERR, *bstrLogString);
        }
        else
        {
            g_lpfnWTTLogTrace(g_hDevice, WTT_LVL_MSG, *bstrLogString);
        }

        if(pfLogDefault != NULL)
        {
            *pfLogDefault = g_fLogDefault;
        }

        if(pfDumpScreen != NULL)
        {
            *pfDumpScreen = g_fDumpScreen;
        }

		return S_OK;
    } 
        
    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="deviceString"></param>
    inline HRESULT InitializeWTTLoggerSupport(wchar_t* pszDeviceString, BOOL fLogDefault, BOOL fDumpScreen, long *hDevice)
    {
        g_fDumpScreen = fDumpScreen;
        g_fLogDefault = fLogDefault;

        HMODULE hinstLibEdit = GetModuleHandleW(L"WTTlog.dll");

        if(hinstLibEdit == NULL)
        {
            hinstLibEdit = LoadLibraryW(L"WTTlog.dll"); 
        }

        if(hinstLibEdit == NULL)
        {
            LogInformation(L"[WARNING] WTTLoggerSupport failure: Couldn't load WTTlog.dll\r\n", FALSE);
            return E_FAIL;
        }

        // Find WTTLogCreateLogDevice and WTTLogTrace functions
        g_lpfnWTTLogCreateLogDevice = (WTTLogCreateLogDevice) GetProcAddress (hinstLibEdit, "WTTLogCreateLogDevice");
        g_lpfnWTTLogTrace = (WTTLogTrace) GetProcAddress (hinstLibEdit, "WTTLogTrace");
        g_lpfnWTTLogCloseLogDevice = (WTTLogCloseLogDevice) GetProcAddress (hinstLibEdit, "WTTLogCloseLogDevice");

        if(g_lpfnWTTLogCreateLogDevice == NULL || g_lpfnWTTLogTrace == NULL || g_lpfnWTTLogCloseLogDevice == NULL)
        {
            LogInformation(L"[WARNING] WTTLoggerSupport failure: Couldn't find WTT functions in the dll\r\n", FALSE);
            return E_FAIL;
        }

        HRESULT hr;
        
        if(pszDeviceString != NULL)
        {
            hr = g_lpfnWTTLogCreateLogDevice(pszDeviceString, &g_hDevice);
        }
        else
        {
            hr = g_lpfnWTTLogCreateLogDevice(DEFAULT_DEVICE_STRING, &g_hDevice);
        }

        if(hr == S_OK)
        {
            if(hDevice != NULL)
            {
                *hDevice = g_hDevice;
            }

            // Set Callback procedure for custom logger
            SetCustomLogger(new LoggerBase(WTTLoggerCallBack));         
        }
        else
        {
            LogInformation(L"[WARNING] WTTLoggerSupport failure: Creating LogDevice failed\r\n", FALSE);
        }

        return hr;
    }

    #pragma endregion WTT Logging Internal support

    inline void CloseWttLogger()
    {
        if(g_lpfnWTTLogCloseLogDevice != NULL)
        {
            g_lpfnWTTLogCloseLogDevice(g_hDevice, NULL);
        }
    }

    inline long OpenWttLogger(wchar_t* pszDeviceString, BOOL fLogDefault, BOOL fDumpScreen)
    {
        long hDevice;
        CloseWttLogger();

        InitializeWTTLoggerSupport(pszDeviceString, fLogDefault, fDumpScreen, &hDevice);

        return hDevice;
    }

    inline long OpenWttLogger(wchar_t* pszDeviceString)
    {
        return OpenWttLogger(pszDeviceString, FALSE, FALSE);
    }

    inline long OpenWttLogger()
    {
        return OpenWttLogger(NULL);
    }
}

#endif