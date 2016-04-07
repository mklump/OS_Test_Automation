#include <windows.h>            //Common Windows types
#include "rpf_constants.h"
#include "screenelement.h"  
#include "LoggingFunctions.h"
#include "rpf_SKUDIFF_Constants.h"


STDAPI InitTest(LPVOID)
{
    return InitPlayBackForTargetWindow(RPF_WINDOWLESS);
}

STDAPI UnInitTest()
{
    FinishPlayBack();
    return NOERROR;
}

//    
//    Verify BrandingWC_BVT_EntryPoints 
//  
STDAPI BrandingWC_BVT_EntryPoints(LPVOID pvReserved)
{
    BOOL fFoundUI = FALSE;
    LPWSTR pwszResultInfo = NULL;
    wchar_t* pszSkuName;
    HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
  
    LogTestBeginW(__FUNCTIONW__, L"Verify Welcome Center Branding UI is differentiated correctly (CPL).");    
 
    if (SUCCEEDED(hr))
    {
        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

        hr = LOG_FAILED_HR(FromPartialQueryId(START_MENU_WELCOME_CENTER));
        if (SUCCEEDED(hr))  
        {
            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
           
            DWORD dwProductInfoType = 0;
            if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
            {
                switch (dwProductInfoType)
                {
                    case PRODUCT_ULTIMATE:
                        pszSkuName = WC_WINVER_ULTIMATE;
                        pwszResultInfo = L"Windows Vista ULTIMATE text expected here.";
                        break;

                    case PRODUCT_ULTIMATE_N:
                        pszSkuName = WC_WINVER_ULTIMATEN;
                        pwszResultInfo = L"Windows Vista ULTIMATE N text expected here.";
                        break;

                    case PRODUCT_BUSINESS:
                        pszSkuName = WC_WINVER_BUSINESS;
                        pwszResultInfo = L"Windows Vista BUSINESS text expected here.";
                        break;

                    case PRODUCT_BUSINESS_N:
                        pszSkuName = WC_WINVER_BUSINESSN;
                        pwszResultInfo = L"Windows Vista BUSINESS N text expected here.";
                        break;

                    case PRODUCT_HOME_BASIC:
                        pszSkuName = WC_WINVER_HOMEBAS;
                        pwszResultInfo = L"Windows Vista HOME BASIC text expected here.";
                        break;

                    case PRODUCT_HOME_BASIC_N:
                        pszSkuName = WC_WINVER_HOMEN;
                        pwszResultInfo = L"Windows Vista HOME BASIC N text expected here.";
                        break;

                    case PRODUCT_HOME_PREMIUM:
                        pszSkuName = WC_WINVER_HOMEPREM;
                        pwszResultInfo = L"Windows Vista HOME PREMIUM text expected here.";
                        break;

                    case PRODUCT_HOME_PREMIUM_N:
                        pszSkuName = WC_WINVER_HOMEPREMN;
                        pwszResultInfo = L"Windows Vista HOME PREMIUM N text expected here.";
                        break;

                    case PRODUCT_STARTER:
                        pszSkuName = WC_WINVER_STARTER;
                        pwszResultInfo = L"Windows Vista STARTER text expected here.";
                        break;

                    case PRODUCT_ENTERPRISE:
                        pszSkuName = WC_WINVER_ENTERPRISE;
                        pwszResultInfo = L"Windows Vista ENTERPRISE text expected here.";
                        break;

                    case PRODUCT_ENTERPRISE_N:
                        pszSkuName = WC_WINVER_ENTERPRISEN;
                        pwszResultInfo = L"Windows Vista ENTERPRISE N text expected here.";
                        break;

                    default:
                        LogTestInfoW(__FUNCTIONW__, L"Wrong branding or could not determine the SKU");
                        pwszResultInfo = L"Could not verify behavior";
                        break;
                }

                fFoundUI =  SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(pszSkuName)));

                if (fFoundUI)
                {
                    pwszResultInfo = L"Welcome Center Branding is differentiated correctly";
                }
            }
            else
            {
                LogTestInfoW(__FUNCTIONW__, L"GetProductInfo failed.");
                pwszResultInfo = L"GetProductInfo failed.";
            }
        }
    }

    LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");
    
    hr = LOG_FAILED_HR(FromPartialQueryId(CPL_WC_CLOSE_BTN));
    if (SUCCEEDED(hr))
    {
        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }

    LogTestResultW(fFoundUI, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}


STDAPI BrandingSysDM_BVT_EntryPoints(LPVOID pvReserved)
{
    LPWSTR pwszResultInfo = NULL;
    BOOL fFoundUI = FALSE; 
    wchar_t* pszSkuName;
    HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
  
    LogTestBeginW(__FUNCTIONW__, L"Verify System Info branding is differentiated correctly (CPL).");    
 
    if (SUCCEEDED(hr))
    {
        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
        
        hr = LOG_FAILED_HR(FromPartialQueryId(START_MENU_COMPUTER));
        if (SUCCEEDED(hr))  
        {
            LOG_FAILED_HR(RightButtonClick(CLICKABLE_POINT));

            hr = LOG_FAILED_HR(FromPartialQueryId(SYS_COMP_PROPERTIES));

            if (SUCCEEDED(hr))  
            {
                LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                DWORD dwProductInfoType = 0;

                if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
                {
                    switch (dwProductInfoType)
                    {
                        case PRODUCT_ULTIMATE:
                            pszSkuName = SYSINFO_WINVER_ULTIMATE;
                            pwszResultInfo = L"Windows Vista ULTIMATE text expected here.";
                            break;

                        case PRODUCT_ULTIMATE_N:
                            pszSkuName = SYSINFO_WINVER_ULTIMATEN;
                            pwszResultInfo = L"Windows Vista ULTIMATE N text expected here.";
                            break;

                        case PRODUCT_BUSINESS:
                            pszSkuName = SYSINFO_WINVER_BUSINESS;
                            pwszResultInfo = L"Windows Vista BUSINESS text expected here.";
                            break;

                        case PRODUCT_BUSINESS_N:
                            pszSkuName = SYSINFO_WINVER_BUSINESSN;
                            pwszResultInfo = L"Windows Vista BUSINESS N text expected here.";
                            break;

                        case PRODUCT_HOME_BASIC:
                            pszSkuName = SYSINFO_WINVER_HOMEBAS;
                            pwszResultInfo = L"Windows Vista HOME BASIC text expected here.";
                            break;

                        case PRODUCT_HOME_BASIC_N:
                            pszSkuName = SYSINFO_WINVER_HOMEN;
                            pwszResultInfo = L"Windows Vista HOME BASIC N text expected here.";
                            break;

                        case PRODUCT_HOME_PREMIUM:
                            pszSkuName = SYSINFO_WINVER_HOMEPREM;
                            pwszResultInfo = L"Windows Vista HOME PREMIUM text expected here.";
                            break;

                        case PRODUCT_HOME_PREMIUM_N:
                            pszSkuName = SYSINFO_WINVER_HOMEPREMN;
                            pwszResultInfo = L"Windows Vista HOME PREMIUM N text expected here.";
                            break;

                        case PRODUCT_STARTER:
                            pszSkuName = SYSINFO_WINVER_STARTER;
                            pwszResultInfo = L"Windows Vista STARTER text expected here.";
                            break;

                        case PRODUCT_ENTERPRISE:
                            pszSkuName = SYSINFO_WINVER_ENTERPRISE;
                            pwszResultInfo = L"Windows Vista ENTERPRISE text expected here.";
                            break;

                        case PRODUCT_ENTERPRISE_N:
                            pszSkuName = SYSINFO_WINVER_ENTERPRISEN;
                            pwszResultInfo = L"Windows Vista ENTERPRISE N text expected here.";
                            break;

                        default:
                            LogTestInfoW(__FUNCTIONW__, L"Wrong branding or could not determine the SKU");
                            pwszResultInfo = L"Could not verify behavior";
                            break;
                    }

                    fFoundUI =  SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(pszSkuName)));

                    if (fFoundUI)
                    {
                        pwszResultInfo = L"System Info Branding is differentiated correctly.";
                    }
                }
                else
                {
                    LogTestInfoW(__FUNCTIONW__, L"GetProductInfo failed.");
                    pwszResultInfo = L"GetProductInfo failed.";
                }
            }
        }
   
        LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");
    
        hr = LOG_FAILED_HR(FromPartialQueryId(CPL_SYS_CLOSE_BTN));
        if (SUCCEEDED(hr))
        {
            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
        }
    }
 
    LogTestResultW(fFoundUI, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;

}


