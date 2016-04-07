#include <windows.h>            //Common Windows types
#include "rpf_constants.h"
#include "screenelement.h"             //RPF
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
//    VerifyDomainJoinCPLEntryPoint 
//  
STDAPI DomainJoinEntryPoints(LPVOID pvReserved)
{
    BOOL    fPassed = FALSE;
    LPWSTR pwszResultInfo = NULL;
    HRESULT hr = E_FAIL;
    
    LogTestBeginW(__FUNCTIONW__, L"Verify Domain join is available from the CPL");    
 
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

                    hr = LOG_FAILED_HR(FromPartialQueryId(CPL_SYSTEM_CHANGE_SETTINGS_BTN));
                    if (SUCCEEDED(hr))
                    {
                        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                        hr = LOG_FAILED_HR(FromPartialQueryId(COMPUTER_NAME_CHANGE_BTN));
                        if (SUCCEEDED(hr))
                        {
                            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                            BOOL fFoundDomainUI = SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(COMPUTER_NAME_DOMAIN_RADIO)));
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
                                        LogTestInfoW(__FUNCTIONW__, L"Domain join UI not expected here!");
                                        break;
                                    case PRODUCT_BUSINESS:
                                    case PRODUCT_BUSINESS_N:
                                    case PRODUCT_ENTERPRISE:
                                    case PRODUCT_ENTERPRISE_N:
                                    case PRODUCT_ULTIMATE:
                                    case PRODUCT_ULTIMATE_N:
                                        fExpected = TRUE;
                                        pwszResultInfo = L"Domain join UI expected here.";
                                        break;
                                    default:
                                        LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
                                        pwszResultInfo = L"Could not verify behavior";
                                        break;
                                }

                                if (fFoundDomainUI != fExpected)
                                {
                                    LogTestInfoW(__FUNCTIONW__,
                                        L"Domain UI SKU differentiation failed.[Current: %s | Expected: %s ]",
                                        fFoundDomainUI ? L"Found": L"Not Found",
                                        fExpected ? L"Found" : L"Not Found");
                                }
                                else
                                {
                                    fPassed = TRUE;
                                    pwszResultInfo = L"Domain Join CPL entry point is differentiated correctly";
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
}
   
    LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");
    
    hr = LOG_FAILED_HR(FromPartialQueryId(COMPUTER_NAME_CANCEL_BTN));
    if (SUCCEEDED(hr))
    {
       LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }

    hr = LOG_FAILED_HR(FromPartialQueryId(COMPUTER_NAME_OK_BTN));
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




