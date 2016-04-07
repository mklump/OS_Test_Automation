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
//    Verify RemoteDesktop_BVT_EntryPoints 
//  
STDAPI RemoteDesktop_BVT_EntryPoints(LPVOID pvReserved)
{
    BOOL    fPassed = FALSE;
    LPWSTR pwszResultInfo = NULL;
    HRESULT hr = E_FAIL;
  
    LogTestBeginW(__FUNCTIONW__, L"Verify Remote Desktop UI is differentiated correctly (CPL).");    
 
    hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
    if (SUCCEEDED(hr))
    {
        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
        
        hr = LOG_FAILED_HR(FromPartialQueryId(START_MENU_CONTROL_PANEL));
        if (SUCCEEDED(hr))  
        {
            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

            hr = LOG_FAILED_HR(FromPartialQueryId(CPL_SYSTEM_AND_MAINTENANCE_LNK));
            if (SUCCEEDED(hr))
            {
                LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));


                hr = LOG_FAILED_HR(FromPartialQueryId(CPL_SYSTEM_LNK));
                if (SUCCEEDED(hr))
                {
                    LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                    hr = LOG_FAILED_HR(FromPartialQueryId(CPL_SYSTEM_REMOTE_NAV_LINK));
                    if (SUCCEEDED(hr))
                    {
                        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                        BOOL fFoundRemoteDesktopUI = SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(CPL_REMOTE_ALLOWCONNTO_RADIO)));
                        BOOL fExpected = FALSE;
                        
                        BOOL fFoundClickablePoint = TRUE;

                        if (fFoundRemoteDesktopUI)
                        {
                            int x, y;
                            fFoundClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));
                            LogTestInfoW(__FUNCTIONW__,
                                L"%s Clickable point", fFoundClickablePoint ? L"Found": L"Did not find");
                        }
                        
                        DWORD dwProductInfoType = 0;
                        if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
                        {
                            switch (dwProductInfoType)
                            {
                                case PRODUCT_STARTER:
                                case PRODUCT_HOME_BASIC:
                                case PRODUCT_HOME_BASIC_N:
                                case PRODUCT_HOME_PREMIUM:
                                case PRODUCT_HOME_PREMIUM_N:
                                    LogTestInfoW(__FUNCTIONW__, L"Remote Desktop UI not expected here!");
                                    break;
                                case PRODUCT_BUSINESS:
                                case PRODUCT_BUSINESS_N:
                                case PRODUCT_ENTERPRISE:
                                case PRODUCT_ENTERPRISE_N:
                                case PRODUCT_ULTIMATE:
                                case PRODUCT_ULTIMATE_N:
                                    fExpected = TRUE;
                                    pwszResultInfo = L"Remote Desktop UI expected here.";
                                    break;
                                default:
                                    LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
                                    pwszResultInfo = L"Could not verify behavior";
                                    break;
                            }

                            if ((fFoundRemoteDesktopUI && fFoundClickablePoint) != fExpected)
                            {
                                LogTestInfoW(__FUNCTIONW__,
                                    L"Remote Desktop UI SKU differentiation failed.[Current: %s | Expected: %s ]",
                                    fFoundRemoteDesktopUI ? L"Found": L"Not Found",
                                    fExpected ? L"Found" : L"Not Found");
                            }
                            else
                            {
                                fPassed = TRUE;
                                pwszResultInfo = L"Remote Desktop CPL entry point is differentiated correctly";
                            }
                        }
                        else
                        {
                            LogTestInfoW(__FUNCTIONW__, L"GetProductInfo failed.");
                            pwszResultInfo = L"GetProductInfo failed.";
                        }
                    }
                }
            }
       }
    }
   
    LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");
    
    hr = LOG_FAILED_HR(FromPartialQueryId(SYSTEM_PROPERTIES_OK_BTN));
    if (SUCCEEDED(hr))
    {
        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }

    hr = LOG_FAILED_HR(FromPartialQueryId(CPL_SYSTEM_CLOSE_BTN));
    if (SUCCEEDED(hr))
    {
        LeftButtonClick(CLICKABLE_POINT);
    }
 
    LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}




