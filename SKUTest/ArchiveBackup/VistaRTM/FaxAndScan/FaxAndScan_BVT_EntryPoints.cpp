#include <windows.h>            //Common Windows types
#include "rpf_constants.h"
#include "screenelement.h"             //RPF
#include "LoggingFunctions.h"
#include "rpf_skudiff_constants.h" // SKU Diff Contants

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
//    VerifyFaxAndScan_StartMenuEntryPoint 
//  
STDAPI VerifyFaxAndScan_StartMenuEntryPoint(LPVOID pvReserved)
{
    BOOL    fPassed = FALSE;
    LPWSTR pwszResultInfo = NULL;
    HRESULT hr = E_FAIL;
    
    LogTestBeginW(__FUNCTIONW__, L"Verify Windows Fax and Scan is available in the Start Menu");    
 
    hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
    if (SUCCEEDED(hr))
    {
        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
        
        hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_ALLPROGRAMS));
        if (SUCCEEDED(hr))  
        {
            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

            BOOL fFoundFaxandScan = SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(WINDOWS_FAX_AND_SCAN)));
            BOOL fExpected = FALSE;
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
                        LogTestInfoW(__FUNCTIONW__, L"Windows Fax and Scan not expected here!");
                        break;
                    case PRODUCT_BUSINESS:
                    case PRODUCT_BUSINESS_N:
                    case PRODUCT_ENTERPRISE:
                    case PRODUCT_ENTERPRISE_N:
                    case PRODUCT_ULTIMATE:
                    case PRODUCT_ULTIMATE_N:
                        fExpected = TRUE;
                        LogTestInfoW(__FUNCTIONW__, L"Windows Fax and Scan expected here!");
                        break;
                    default:
                        LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
                        pwszResultInfo = L"Could not verify behavior";
                        break;
                }

                if (fFoundFaxandScan  != fExpected)
                {
                    LogTestInfoW(__FUNCTIONW__,
                        L"Windows Fax and Scan SKU differentiation failed.[Current: %s | Expected: %s ]",
                        fFoundFaxandScan ? L"Found": L"Not Found",
                        fExpected ? L"Found" : L"Not Found");
                }
                else
                {
                    fPassed = TRUE;
                    pwszResultInfo = L"Windows Fax and Scan entry point is differentiated correctly";
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
    
    hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
    if (SUCCEEDED(hr))
    {
       LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }
 
    LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}

