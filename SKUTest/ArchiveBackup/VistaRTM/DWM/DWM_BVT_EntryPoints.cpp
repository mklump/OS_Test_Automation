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

// IsAero_GlassExpected
//
// Helper function that determines if Glass Entry points must be present on the current installed SKU or not.
// Returns True : if Glass entry points are expected
// Returns False : if Glass entry points are not expected
BOOL IsAero_GlassExpected()
{
    BOOL fExpected = FALSE;
                        
    DWORD dwProductInfoType = 0;
    if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
    {
        switch (dwProductInfoType)
        {
            case PRODUCT_STARTER:
            case PRODUCT_HOME_BASIC:
            case PRODUCT_HOME_BASIC_N:
                LogTestInfoW(__FUNCTIONW__, L"Glass not expected here!");
                break;
            case PRODUCT_BUSINESS:
            case PRODUCT_BUSINESS_N:
            case PRODUCT_ENTERPRISE:
            case PRODUCT_ENTERPRISE_N:
            case PRODUCT_HOME_PREMIUM:
            case PRODUCT_HOME_PREMIUM_N:
            case PRODUCT_ULTIMATE:
            case PRODUCT_ULTIMATE_N:
                fExpected = TRUE;
                break;
            default:
                LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
                break;
        }
    }

    return fExpected;
}


BOOL OpenChangeYourColorScheme()
{
    BOOL fChangeYourColorSchemeOpened = FALSE;

    HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
    if (SUCCEEDED(hr))
    {
        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
        

        hr = LOG_FAILED_HR(FromPartialQueryId(START_MENU_CONTROL_PANEL));
        if (SUCCEEDED(hr))  
        {
            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

            // "Control Panel Home" assumes a "link" role only if the Control Panel is opened in the "Classic" view.
            // If the Control Panel is already opened in the "Home" view then "Control Panel Home" assumes a "text" role.
            //
            // So set timeout to 10 seconds to quickly check if CPL is currently being opened in 
            // Classic (Control Panel Home role = link) or Classic (Control Panel Home role = text) view.
            // Save the original timeout so it can be set later.
            int originalTimeout = SetSearchTimeOut(10000);
            hr = LOG_FAILED_HR(FromPartialQueryId(CPL_HOME_VIEW_LNK));
            if (FAILED(hr))
            {
                // role = text. control panel is already in home view. move on.
                LogTestInfoW(__FUNCTIONW__, L"Attempt to switch to Home View failed. Control Panel is already in Home View mode...");
            }
            else
            {
                LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
            }

            // restore original timeout
            SetSearchTimeOut(originalTimeout);

            hr = LOG_FAILED_HR(FromPartialQueryId(CPL_HOME_APPEAR_AND_PERSONALIZE));
            if (SUCCEEDED(hr))  
            {
                LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                hr = LOG_FAILED_HR(FromPartialQueryId(CPL_PERSONALIZATION));
                if (SUCCEEDED(hr))  
                {
                    LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                    hr = LOG_FAILED_HR(FromPartialQueryId(CPL_WIN_COLOR_AND_APPEARANCE));
                    if (SUCCEEDED(hr))  
                    {
                        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                        fChangeYourColorSchemeOpened = TRUE;
                    }
                }
            }
        }
    }
    return fChangeYourColorSchemeOpened;
}

//    
//    VerifyDWM_GlassEntryPoint 
//  
STDAPI VerifyDWM_GlassEntryPoint(LPVOID pvReserved)
{
    BOOL    fPassed = FALSE;
    LPWSTR pwszResultInfo = NULL;

    LogTestBeginW(__FUNCTIONW__, L"Verify Glass is available.");    
 
    BOOL fExpected = IsAero_GlassExpected();
    BOOL fFoundEtcClickablePoint = FALSE;
    if (OpenChangeYourColorScheme())
    {
        if (SUCCEEDED(FromPartialQueryId(CPL_ENABLE_TRANSPARENT_GLASS)))
        {
            int x, y;
            fFoundEtcClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));
            LogTestInfoW(__FUNCTIONW__,
                         L"%s Clickable point for Enable Transparency Checkbox", 
                         fFoundEtcClickablePoint ? L"Found": L"Did not find");

            if (fFoundEtcClickablePoint != fExpected)
            {
                pwszResultInfo = L"Glass Entry point is not differentiated correctly";
                LogTestInfoW(__FUNCTIONW__,
                            L"DWM Glass SKU differentiation failed.[Current: %s | Expected: %s ]",
                            fFoundEtcClickablePoint ? L"Found": L"Not Found",
                            fExpected ? L"Found" : L"Not Found");
            }
            else
            {
                fPassed = TRUE;
                if (fExpected)
                {
                    // Go ahead and change state of the checkbox.
                    LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                    // return checkbox to original state.
                    LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                }
                pwszResultInfo = L"Glass Entry point is differentiated correctly";
                LogTestInfoW(__FUNCTIONW__,
                            L"Entry point results.[Current: %s | Expected: %s ]",
                            fFoundEtcClickablePoint ? L"Found": L"Not Found",
                            fExpected ? L"Found" : L"Not Found");  
            }
        }
        else
        {
            if (fExpected)
            {
                pwszResultInfo = L"Glass Entry point is not differentiated correctly";
                LogTestInfoW(__FUNCTIONW__,
                            L"DWM Glass SKU differentiation failed.[Current: %s | Expected: %s ]",
                            fFoundEtcClickablePoint ? L"Found": L"Not Found",
                            fExpected ? L"Found" :  L"Not Found");
            }
            else
            {
                pwszResultInfo = L"Glass Entry point is differentiated correctly";
                fPassed = TRUE;
            }
        }

        LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");
        
        HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(CPL_CHANGE_YOUR_COLOR_SCHEME_CLOSE));
        if (SUCCEEDED(hr))
        {
           LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
        }
    }
    else
    {
        pwszResultInfo = L"Could not open 'Change your color scheme' CPL";
        LogTestInfoW(__FUNCTIONW__,
                    L"DWM Glass SKU differentiation failed.[Current: %s | Expected: %s ]",
                    fFoundEtcClickablePoint ? L"Found": L"Not Found",
                    fExpected ? L"Found" :  L"Not Found");
    }

    LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}


//    
//    VerifyDWM_AeroEntryPoint 
//  
STDAPI VerifyDWM_AeroEntryPoint(LPVOID pvReserved)
{
    BOOL    fPassed = FALSE;
    LPWSTR pwszResultInfo = NULL;

    LogTestBeginW(__FUNCTIONW__, L"Verify Vista Aero Color Scheme is available.");    

    BOOL fExpected = IsAero_GlassExpected();
    BOOL fFoundAeroColorSchemeClickablePoint = FALSE;

    if (OpenChangeYourColorScheme())
    {
        HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(CPL_OPEN_CLASSIC_APPEARANCE));
        if (SUCCEEDED(hr))
        {
            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

            if (SUCCEEDED(FromPartialQueryId(WINDOWS_VISTA_AERO_COLOR_SCHEME)))
            {
                int x, y;
                fFoundAeroColorSchemeClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));
                LogTestInfoW(__FUNCTIONW__,
                             L"%s Clickable point for Aero Color Scheme", 
                             fFoundAeroColorSchemeClickablePoint ? L"Found": L"Did not find");

                if (fFoundAeroColorSchemeClickablePoint != fExpected)
                {
                    pwszResultInfo = L"Aero Entry point is not differentiated correctly";
                    LogTestInfoW(__FUNCTIONW__,
                                L"DWM Aero SKU differentiation failed.[Current: %s | Expected: %s ]",
                                fFoundAeroColorSchemeClickablePoint ? L"Found": L"Not Found",
                                fExpected ? L"Found" : L"Not Found");
                }
                else
                {
                    fPassed = TRUE;
                    if (fExpected)
                    {
                        // Go ahead and click it.
                        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                    }
                    pwszResultInfo = L"Aero Entry point is differentiated correctly";
                    LogTestInfoW(__FUNCTIONW__,
                                L"Entry point results.[Current: %s | Expected: %s ]",
                                fFoundAeroColorSchemeClickablePoint ? L"Found": L"Not Found",
                                fExpected ? L"Found" : L"Not Found");  
                }
            }
            else
            {
                if (fExpected)
                {
                    pwszResultInfo = L"Aero Entry point is not differentiated correctly";
                    LogTestInfoW(__FUNCTIONW__,
                                L"DWM Aero SKU differentiation failed.[Current: %s | Expected: %s ]",
                                fFoundAeroColorSchemeClickablePoint ? L"Found": L"Not Found",
                                fExpected ? L"Found" :  L"Not Found");
                }
                else
                {
                    pwszResultInfo = L"Aero Entry point is differentiated correctly";
                    fPassed = TRUE;
                }
            }

            hr = LOG_FAILED_HR(FromPartialQueryId(CLASSIC_APPEARANCE_CLOSE));
            if (SUCCEEDED(hr))
            {
               LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
            }
        }

        LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");
        
        hr = LOG_FAILED_HR(FromPartialQueryId(CPL_PERSONALIZATION_CLOSE));
        if (SUCCEEDED(hr))
        {
           LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
        }
    }
    else
    {
        pwszResultInfo = L"Could not open 'Change your color scheme' CPL";
        LogTestInfoW(__FUNCTIONW__,
                    L"DWM Glass SKU differentiation failed.[Current: %s | Expected: %s ]",
                    fFoundAeroColorSchemeClickablePoint ? L"Found": L"Not Found",
                    fExpected ? L"Found" :  L"Not Found");
    }

    LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}

//    
//    VerifyDWM_WindowsSwitcherEntryPoint 
//  
STDAPI VerifyDWM_WindowsSwitcherEntryPoint(LPVOID pvReserved)
{
    BOOL    fPassed = TRUE;
    LPWSTR pwszResultInfo = NULL;
    BOOL fExpected = IsAero_GlassExpected();

    LogTestBeginW(__FUNCTIONW__, L"Verify Windows Switcher is available in OCM");    
 
    if (OpenChangeYourColorScheme())
    {
        BOOL fFoundSwitcherClickablePoint = FALSE;
        if (SUCCEEDED(FromPartialQueryId(WINDOWS_SWITCHER)))
        {
            int x, y;
            fFoundSwitcherClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));
            LogTestInfoW(__FUNCTIONW__,
                         L"%s Clickable point for Windows Switcher", 
                         fFoundSwitcherClickablePoint ? L"Found": L"Did not find");

            if (fFoundSwitcherClickablePoint != fExpected)
            {
                pwszResultInfo = L"Windows Switcher Entry point is not differentiated correctly";
                LogTestInfoW(__FUNCTIONW__,
                            L"DWM Windows Switcher SKU differentiation failed.[Current: %s | Expected: %s ]",
                            fFoundSwitcherClickablePoint ? L"Found": L"Not Found",
                            fExpected ? L"Found" : L"Not Found");
            }
            else
            {
                fPassed = TRUE;
                if (fExpected)
                {
                    // Go ahead and click it to bring up windows switcher.
                    LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                    // Click it again to retun back.
                    LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                }
                pwszResultInfo = L"Windows Switcher Entry point is differentiated correctly";
                LogTestInfoW(__FUNCTIONW__,
                            L"Entry point results.[Current: %s | Expected: %s ]",
                            fFoundSwitcherClickablePoint ? L"Found": L"Not Found",
                            fExpected ? L"Found" : L"Not Found");  
            }
        }
    }

    LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");
    
    HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(CPL_CHANGE_YOUR_COLOR_SCHEME_CLOSE));
    if (SUCCEEDED(hr))
    {
       LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }

    LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}

   

