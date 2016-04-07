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
//    Verify MUI_BVT_EntryPoints 
//  
STDAPI MUI_BVT_EntryPoints(LPVOID pvReserved)
{
    BOOL    fPassed = FALSE;
    LPWSTR pwszResultInfo = NULL;
    HRESULT hr = E_FAIL;
  
    LogTestBeginW(__FUNCTIONW__, L"Verify MUI UI is differentiated correctly (CPL).");    
 
    hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
    if (SUCCEEDED(hr))
    {
        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
        
        hr = LOG_FAILED_HR(FromPartialQueryId(START_MENU_CONTROL_PANEL));
        if (SUCCEEDED(hr))  
        {
            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

            hr = LOG_FAILED_HR(FromPartialQueryId(CPL_CHNG_KEYRBD_LNK));
            if (SUCCEEDED(hr))
            {
                LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                BOOL fFoundUI = SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(MUI_MANAGE_LANGUAGES_BTN)));
                BOOL fExpected = FALSE;
                
                BOOL fFoundClickablePoint = TRUE;

                if (fFoundUI)
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
                        case PRODUCT_BUSINESS:
                        case PRODUCT_BUSINESS_N:
                            LogTestInfoW(__FUNCTIONW__, L"Manage Languages button not expected here!");
                            break;
                        case PRODUCT_ENTERPRISE:
                        case PRODUCT_ENTERPRISE_N:
                        case PRODUCT_ULTIMATE:
                        case PRODUCT_ULTIMATE_N:
                            fExpected = TRUE;
                            pwszResultInfo = L"Manage Languages button expected here.";
                            break;
                        default:
                            LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
                            pwszResultInfo = L"Could not verify behavior";
                            break;
                    }

                    if ((fFoundUI && fFoundClickablePoint) != fExpected)
                    {
                        LogTestInfoW(__FUNCTIONW__,
                            L"MUI UI SKU differentiation failed.[Current: %s | Expected: %s ]",
                            fFoundUI ? L"Found": L"Not Found",
                            fExpected ? L"Found" : L"Not Found");
                    }
                    else
                    {
                        fPassed = TRUE;
                        pwszResultInfo = L"MUI CPL entry point is differentiated correctly";
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
   
    LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");
    
    hr = LOG_FAILED_HR(FromPartialQueryId(MUI_KEYBRD_LANGUAGES_OK_BTN));
    if (SUCCEEDED(hr))
    {
        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }

    hr = LOG_FAILED_HR(FromPartialQueryId(CPL_CLOSE_BTN));
    if (SUCCEEDED(hr))
    {
        LeftButtonClick(CLICKABLE_POINT);
    }
 
    LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}




