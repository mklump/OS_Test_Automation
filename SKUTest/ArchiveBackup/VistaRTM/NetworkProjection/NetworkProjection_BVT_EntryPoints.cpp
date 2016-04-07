/***************************************************************
// Description: BVT - Network Projection entry point verification in SKUs
// Created:     HariniD
// Verify:      Pass test case if feature is available
//              in all SKUs but Starter and Home Basic
****************************************************************/

#include <windows.h>
#include "RPF_Constants.h"
#include "screenelement.h"
#include "LoggingFunctions.h"
#include <stdio.h>
#include "RPF_SKUDIFF_Constants.h"

// Initialize
STDAPI InitTest(LPVOID)
{
    return InitPlayBackForTargetWindow(RPF_WINDOWLESS);
}


// UnInitialize
STDAPI UnInitTest()
{
    FinishPlayBack();
    return NOERROR;
}


// Verify Network Projector entry point in Start Menu
STDAPI NetworkProjection_BVT_EntryPoints(LPVOID pvReserved)
{
    BOOL fResult = FALSE;

    LogTestBeginW(__FUNCTIONW__, L"Beginning Network Projector BVT test case...");


    HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));

    if (SUCCEEDED(hr))
    {
        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

        LogTestInfoW(__FUNCTIONW__, L"Click All Programs...");
        hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_ALLPROGRAMS));

        if (SUCCEEDED(hr))
        {
            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

            LogTestInfoW(__FUNCTIONW__, L"Click Accessoriess...");
            hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_ACCESSORIES));

            if (SUCCEEDED(hr))
            {
                LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                BOOL fExpected = FALSE;
                DWORD dwProductInfoType = 0;
                if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
                {
                    switch (dwProductInfoType)
                    {
                        case PRODUCT_STARTER:
                        case PRODUCT_HOME_BASIC:
                        case PRODUCT_HOME_BASIC_N:
                            LogTestInfoW(__FUNCTIONW__, L"Network Projector is NOT expected in this SKU.");
                            break;
                        case PRODUCT_HOME_PREMIUM:
                        case PRODUCT_HOME_PREMIUM_N:
                        case PRODUCT_BUSINESS:
                        case PRODUCT_BUSINESS_N:
                        case PRODUCT_ENTERPRISE:
                        case PRODUCT_ENTERPRISE_N:
                        case PRODUCT_ULTIMATE:
                        case PRODUCT_ULTIMATE_N:
                            fExpected = TRUE;
                            LogTestInfoW(__FUNCTIONW__, L"Network Projector is expected in this SKU.");
                            break;
                        default:
                            LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU.");
                            break;
                    }

                    LogTestInfoW(__FUNCTIONW__, L"Launch --Connect to Network Projector--");

                    BOOL fFoundUI = SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(START_MENU_PROJECTOR_ENU)));
                    BOOL fFoundClickablePoint = FALSE;
                    BOOL fLaunched = FALSE;

                    if (fFoundUI)
                    {
                        fFoundClickablePoint = SUCCEEDED(LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT)));
                        LogTestInfoW(__FUNCTIONW__, L"%s Clickable point", fFoundClickablePoint ? L"Found": L"Did not find");

                        //Actually launch the application if found
                        if(fFoundClickablePoint)
                        {
                            hr = LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                            if (SUCCEEDED(hr))
                            {
                                fLaunched = TRUE;
                            }
                        }
                    }

                    if ((fFoundUI && fFoundClickablePoint && fLaunched) != fExpected)
                    {
                        LogTestInfoW(__FUNCTIONW__,
                            L"Network Projection SKU differentiated feature failed.[Current: %s | Expected: %s ]",
                            fFoundUI ? L"Found": L"Not Found",
                            fExpected ? L"Found" : L"Not Found");
                    }
                    else
                    {
                        fResult = TRUE;
                        LogTestInfoW(__FUNCTIONW__, L"Network Projection is differentiated correctly.");
                    }
                }
                else
                {
                    LogTestInfoW(__FUNCTIONW__, L"GetProductInfo failed.");
                }
            }
        }
    }

    LogTestInfoW(__FUNCTIONW__, L"Cleaning up...\n");

    hr = LOG_FAILED_HR(FromPartialQueryId(CANCEL_PROJECTOR));
    if (SUCCEEDED(hr))
    {
        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }

    LogTestResultW(fResult, __FUNCTIONW__, L"Completed Network Projector BVT test case.");
    return NOERROR;
}
