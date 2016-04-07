#include <windows.h>            //Common Windows types
#include "rpf_constants.h"
#include "screenelement.h"             //RPF
#include "LoggingFunctions.h"
#include "rpf_skudiff_constants.h" // SKU Diff Contants
#include <lm.h>

STDAPI InitTest(LPVOID)
{
    return InitPlayBackForTargetWindow(RPF_WINDOWLESS);
}

STDAPI UnInitTest()
{
    FinishPlayBack();
    return NOERROR;
}


// isParentalControlsExpected
//
// Helper function that determines if Parental Control Entry points must be present on the current installed SKU or not.
// Returns True : if Parental Control entry points are expected
// Returns False : if Parental Control entry points are not expected
BOOL isParentalControlsExpected()
{
    BOOL fExpected = FALSE;
                        
    DWORD dwProductInfoType = 0;
    if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
    {
        switch (dwProductInfoType)
        {
            case PRODUCT_BUSINESS:
            case PRODUCT_BUSINESS_N:
            case PRODUCT_ENTERPRISE:
            case PRODUCT_ENTERPRISE_N:
                LogTestInfoW(__FUNCTIONW__, L"Parental Controls not expected here!");
                break;
            case PRODUCT_STARTER:
            case PRODUCT_HOME_BASIC:
            case PRODUCT_HOME_BASIC_N:
            case PRODUCT_HOME_PREMIUM:
            case PRODUCT_HOME_PREMIUM_N:
                fExpected = TRUE;
                break;
            case PRODUCT_ULTIMATE:
            case PRODUCT_ULTIMATE_N:
            {
                fExpected = TRUE;

                LPWSTR  pszName;
                NETSETUP_JOIN_STATUS  njs;
                LPCWSTR lpServer = NULL;
                NET_API_STATUS status = NetGetJoinInformation(lpServer, &pszName, &njs);
                if (status != NERR_Success)
                {
                    LogTestInfoW(__FUNCTIONW__, L"NetGetJoinInformation(...) invocation failed. Error code = %d", status);
                }
                else
                {
                    if (njs == NetSetupDomainName)
                    {
                        LogTestInfoW(__FUNCTIONW__, L"Computer is Domain joined. Parental Control entry points not expected here.");
                        fExpected = FALSE;
                    }
                }                
                break;
            }
            default:
                LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
                break;
        }
    }

    return fExpected;
}

//    
//    VerifyParentalControlCplHomeViewEntryPoint 
//  
STDAPI VerifyParentalControlsCplHomeViewEntryPoint(LPVOID pvReserved)
{
    BOOL    fPassed = FALSE;
    LPWSTR pwszResultInfo = NULL;

    EnableInfoWindow(TRUE);
    LogTestBeginW(__FUNCTIONW__, L"Verify Parental Controls is available from the CPL in Home View");    

    wchar_t str[1024];
    ExtractResourceString(resKeyControlPanel, str, 1024);

 
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

            BOOL fExpected = isParentalControlsExpected();
            BOOL fFoundParentalControls = SUCCEEDED(FromPartialQueryId(CPL_HOME_USER_ACCTS_AND_FAMILY_LNK));

            // To ascertain presence/absence, look for the clickable point.
            int x, y;
            BOOL fFoundClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));
            LogTestInfoW(__FUNCTIONW__,
                         L"%s Clickable point for Parental Controls", fFoundClickablePoint ? L"Found": L"Did not find");

            if (fFoundParentalControls && fFoundClickablePoint != fExpected)
            {
                pwszResultInfo = L"Parental Controls CPL entry point is NOT differentiated correctly";
                LogTestInfoW(__FUNCTIONW__,
                            L"Parental Controls SKU differentiation failed.[Current: %s | Expected: %s ]",
                            fFoundParentalControls ? L"Found": L"Not Found",
                            fExpected ? L"Found" : L"Not Found");
            }
            else
            {
                fPassed = TRUE;
                pwszResultInfo = L"Parental Controls CPL entry point is differentiated correctly";
                // Go ahead and click the User Accounts and Family link.
                if (fExpected)
                {
                    LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                    hr = LOG_FAILED_HR(FromPartialQueryId(CPL_HOME_PARENTAL_CONTROLS));
                    if (SUCCEEDED(hr))  
                    {
                        LogTestInfoW(__FUNCTIONW__,
                                    L"Parental Controls entry point results.[Current: %s | Expected: %s ]",
                                    fFoundParentalControls ? L"Found": L"Not Found",
                                    fExpected ? L"Found" : L"Not Found");            

                        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                    }
                    else
                    {
                        fPassed = FALSE;
                        pwszResultInfo = L"Parental Controls CPL entry point is NOT differentiated correctly";
                        LogTestInfoW(__FUNCTIONW__,
                                    L"Parental Controls SKU differentiation failed.[Current: %s | Expected: %s ]",
                                    L"Not Found",
                                    fExpected ? L"Found" : L"Not Found");
                    }
                }
            }
        } 
    } 
   
    LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");
    
    hr = LOG_FAILED_HR(FromPartialQueryId(CPL_CLOSE_BTN));
    if (SUCCEEDED(hr))
    {
       LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }

    LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}

//    
//    VerifyParentalControlCplClassicViewEntryPoint 
//  
STDAPI VerifyParentalControlsCplClassicViewEntryPoint(LPVOID pvReserved)
{
    BOOL    fPassed = FALSE;
    LPWSTR pwszResultInfo = NULL;

    LogTestBeginW(__FUNCTIONW__, L"Verify Parental Controls is available from the CPL in Classic View");    

    HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
    if (SUCCEEDED(hr))
    {
        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
        

        hr = LOG_FAILED_HR(FromPartialQueryId(START_MENU_CONTROL_PANEL));
        if (SUCCEEDED(hr))  
        {
            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

            // "Classic View" assumes a "link" role only if the Control Panel is opened in the "Home" view.
            // If the Control Panel is already opened in the "Classic" view then "Classic View" assumes a "text" role.
            //
            // So set timeout to 10 seconds to quickly check if CPL is currently being opened in 
            // Home (Classic View role = link) or Classic (Classic View role = text) view .
            // Save the original timeout so it can be set later.
            int originalTimeout = SetSearchTimeOut(10000);
            hr = LOG_FAILED_HR(FromPartialQueryId(CPL_CLASSIC_VIEW_LNK));
            if (FAILED(hr))
            {
                LogTestInfoW(__FUNCTIONW__, L"Attempt to switch to Classic View failed. Control Panel is already in Classic View mode...");
            }
            else
            {
                LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
            }

            // restore timeout
            SetSearchTimeOut(originalTimeout);

            BOOL fExpected = isParentalControlsExpected();
            BOOL fFoundParentalControls = SUCCEEDED(FromPartialQueryId(CPL_CLASSIC_PARENTAL_CONTROLS));
            int x, y;
            BOOL fFoundClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));
            LogTestInfoW(__FUNCTIONW__,
                         L"%s Clickable point for Parental Controls", fFoundClickablePoint ? L"Found": L"Did not find");

            if (fFoundParentalControls && fFoundClickablePoint != fExpected)
            {
                pwszResultInfo = L"Parental Controls CPL entry point is NOT differentiated correctly";
                LogTestInfoW(__FUNCTIONW__,
                            L"Parental Controls SKU differentiation failed.[Current: %s | Expected: %s ]",
                            fFoundParentalControls ? L"Found": L"Not Found",
                            fExpected ? L"Found" : L"Not Found");
            }
            else
            {
                fPassed = TRUE;
                pwszResultInfo = L"Parental Controls CPL entry point is differentiated correctly";
                if (fExpected)
                {
                    // Go ahead and double click the Parental Controls list item.
                    if (SUCCEEDED(LOG_FAILED_HR(DoubleClick(CLICKABLE_POINT))))
                    {
                        LogTestInfoW(__FUNCTIONW__,
                                    L"Parental Controls entry point results.[Current: %s | Expected: %s ]",
                                    fFoundParentalControls ? L"Found": L"Not Found",
                                    fExpected ? L"Found" : L"Not Found");         
                    }
                    else
                    {
                        fPassed = FALSE;
                        pwszResultInfo = L"Parental Controls CPL entry point is NOT differentiated correctly";
                        LogTestInfoW(__FUNCTIONW__,
                                    L"Parental Controls SKU differentiation failed.[Current: %s | Expected: %s ]",
                                    L"Not Found",
                                    fExpected ? L"Found" : L"Not Found");         
                    }
                }
            }
        } 
    } 
   
    LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");
    
    hr = LOG_FAILED_HR(FromPartialQueryId(CPL_CLOSE_BTN));
    if (SUCCEEDED(hr))
    {
       LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }

    LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}


//    
//    VerifyParentalControlGamesExplorerEntryPoint 
//  
STDAPI VerifyParentalControlsGamesExplorerEntryPoint(LPVOID pvReserved)
{
    BOOL    fPassed = FALSE;
    LPWSTR pwszResultInfo = NULL;

    LogTestBeginW(__FUNCTIONW__, L"Verify Parental Controls is available from the Games Explorer");    
 
    HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
    if (SUCCEEDED(hr))
    {
        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
        
        // There are two ways to get to the games explorer depending on the SKU installed.
        // Business/Enterprise : Games are not installed by default. Go to Start->All Programs-> Games
        // All other SKUs      : Games are installed by default. Go to Start-> Games.
        BOOL gotToTheGamesExplorer = FALSE;
        DWORD dwProductInfoType = 0;
        if (GetProductInfo(6, 0, 0, 0, &dwProductInfoType))
        {
            switch (dwProductInfoType)
            {
                case PRODUCT_BUSINESS:
                case PRODUCT_BUSINESS_N:
                case PRODUCT_ENTERPRISE:
                {
                    hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_ALLPROGRAMS));
                    if (SUCCEEDED(hr))
                    {
                        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                        hr = LOG_FAILED_HR(FromPartialQueryId(ALL_PROGRAMS_GAMES));
                        if (SUCCEEDED(hr))
                        {
                            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                            hr = LOG_FAILED_HR(FromPartialQueryId(ALL_PROGRAMS_GAMES_EXPLORER));
                            if (SUCCEEDED(hr))
                            {
                                LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                                BOOL fExpected = isParentalControlsExpected();
                                BOOL fFoundParentalControls = SUCCEEDED(FromPartialQueryId(GAMES_PARENTAL_CONTROLS_BTN));
                                int x, y;
                                BOOL fFoundClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));
                                LogTestInfoW(__FUNCTIONW__,
                                             L"%s Clickable point for Parental Controls", fFoundClickablePoint ? L"Found": L"Did not find");

                                if (fFoundParentalControls && fFoundClickablePoint != fExpected)
                                {
                                    pwszResultInfo = L"Parental Controls CPL entry point is NOT differentiated correctly";
                                    LogTestInfoW(__FUNCTIONW__,
                                                L"Parental Controls SKU differentiation failed.[Current: %s | Expected: %s ]",
                                                fFoundParentalControls ? L"Found": L"Not Found",
                                                fExpected ? L"Found" : L"Not Found");
                                }
                                else
                                {
                                    fPassed = TRUE;
                                    pwszResultInfo = L"Parental Controls Games Explorer entry point is differentiated correctly";
                                    if (fExpected)
                                    {
                                        // Go ahead and open Parental Controls.
                                        if (LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT)))
                                        {
                                            LogTestInfoW(__FUNCTIONW__,
                                                        L"Parental Controls entry point results.[Current: %s | Expected: %s ]",
                                                        fFoundParentalControls ? L"Found": L"Not Found",
                                                        fExpected ? L"Found" : L"Not Found");  

                                            // close parental controls
                                            if (SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(CPL_PARENTAL_CONTROLS_CLOSE_BTN))))
                                            {
                                                LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                                            }
                                        }
                                        else
                                        {
                                            pwszResultInfo = L"Parental Controls Games Explorer entry point is NOT differentiated correctly";
                                            fPassed = FALSE;
                                            LogTestInfoW(__FUNCTIONW__,
                                                        L"Parental Controls SKU differentiation failed.[Current: %s | Expected: %s ]",
                                                        L"Not Found",
                                                        fExpected ? L"Found" : L"Not Found");
                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;
                }
                case PRODUCT_STARTER:
                case PRODUCT_HOME_BASIC:
                case PRODUCT_HOME_BASIC_N:
                case PRODUCT_HOME_PREMIUM:
                case PRODUCT_HOME_PREMIUM_N:
                case PRODUCT_ULTIMATE:
                case PRODUCT_ULTIMATE_N:
                {
                    hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_GAMES));
                    if (SUCCEEDED(hr))
                    {
                        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                        BOOL fExpected = isParentalControlsExpected();
                        BOOL fFoundParentalControls = SUCCEEDED(FromPartialQueryId(GAMES_PARENTAL_CONTROLS_BTN));
                        int x, y;
                        BOOL fFoundClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));
                        LogTestInfoW(__FUNCTIONW__,
                                     L"%s Clickable point for Parental Controls", fFoundClickablePoint ? L"Found": L"Did not find");

                        if (fFoundParentalControls && fFoundClickablePoint != fExpected)
                        {
                            pwszResultInfo = L"Parental Controls CPL entry point is NOT differentiated correctly";
                            LogTestInfoW(__FUNCTIONW__,
                                        L"Parental Controls SKU differentiation failed.[Current: %s | Expected: %s ]",
                                        fFoundParentalControls ? L"Found": L"Not Found",
                                        fExpected ? L"Found" : L"Not Found");
                        }
                        else
                        {
                            fPassed = TRUE;
                            pwszResultInfo = L"Parental Controls Games Explorer entry point is differentiated correctly";
                            // Go ahead and open Parental Controls.
                            if (LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT)))
                            {
                                LogTestInfoW(__FUNCTIONW__,
                                            L"Parental Controls entry point results.[Current: %s | Expected: %s ]",
                                            fFoundParentalControls ? L"Found": L"Not Found",
                                            fExpected ? L"Found" : L"Not Found");  

                                // Close Parental Controls
                                if (SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(CPL_PARENTAL_CONTROLS_CLOSE_BTN))))
                                {
                                    LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                                }
                            }
                            else
                            {
                                fPassed = FALSE;
                                pwszResultInfo = L"Parental Controls CPL entry point is NOT differentiated correctly";
                                LogTestInfoW(__FUNCTIONW__,
                                            L"Parental Controls SKU differentiation failed.[Current: %s | Expected: %s ]",
                                            L"Not Found",
                                            fExpected ? L"Found" : L"Not Found");
                            }
                        }
                    }
                    break;
                }
                default:
                {
                    LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
                    break;
                }
            }
        }
    } 
   
    LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");
    
    hr = LOG_FAILED_HR(FromPartialQueryId(GAMES_CLOSE_BTN));
    if (SUCCEEDED(hr))
    {
       LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }

    LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}


//    
//    VerifyParentalControlInternetExplorerEntryPoint 
//  
STDAPI VerifyParentalControlsInternetExplorerEntryPoint(LPVOID pvReserved)
{
    BOOL    fPassed = FALSE;
    LPWSTR pwszResultInfo = NULL;

    LogTestBeginW(__FUNCTIONW__, L"Verify Parental Controls is available from the Internet Explorer");    
 
    HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
    if (SUCCEEDED(hr))
    {
        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
        

        hr = LOG_FAILED_HR(FromPartialQueryId(START_INTERNET_EXPLORER));
        if (SUCCEEDED(hr))  
        {
            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

            hr = LOG_FAILED_HR(FromPartialQueryId(IE_TOOLBAR));
            if (SUCCEEDED(hr))
            {
                TypeString(L"%");

                hr = LOG_FAILED_HR(FromPartialQueryId(IE_TOOLS_MENU_BAR));
                if (SUCCEEDED(hr))
                {
                    LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                    hr = LOG_FAILED_HR(FromPartialQueryId(IE_TOOLS_INTERNET_OPTIONS));
                    if (SUCCEEDED(hr))
                    {
                        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                        hr = LOG_FAILED_HR(FromPartialQueryId(IE_TOOLS_CONTENT_TAB));

                        if (SUCCEEDED(hr))
                        {
                            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                            BOOL fExpected = isParentalControlsExpected();
                            BOOL fFoundParentalControls = SUCCEEDED(FromPartialQueryId(IE_TOOLS_PARENTAL_CONTROLS_BTN));
                            int x, y;
                            BOOL fFoundClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));
                            LogTestInfoW(__FUNCTIONW__,
                                         L"%s Clickable point for Parental Controls", fFoundClickablePoint ? L"Found": L"Did not find");

                            if (fFoundParentalControls && fFoundClickablePoint != fExpected)
                            {
                                pwszResultInfo = L"Parental Controls CPL entry point is NOT differentiated correctly";
                                LogTestInfoW(__FUNCTIONW__,
                                            L"Parental Controls SKU differentiation failed.[Current: %s | Expected: %s ]",
                                            fFoundParentalControls ? L"Found": L"Not Found",
                                            fExpected ? L"Found" : L"Not Found");
                            }
                            else
                            {
                                // Go ahead and click the Parental Controls button.
                                if(LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT)))
                                {
                                    fPassed = TRUE;
                                    pwszResultInfo = L"Parental Controls Internet Explorer entry point is differentiated correctly";
                                    LogTestInfoW(__FUNCTIONW__,
                                                L"Parental Controls entry point results.[Current: %s | Expected: %s ]",
                                                fFoundParentalControls ? L"Found": L"Not Found",
                                                fExpected ? L"Found" : L"Not Found");      

                                    if (SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(CPL_PARENTAL_CONTROLS_CLOSE_BTN))))
                                    {
                                        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                                    }
                                }
                                else
                                {
                                    pwszResultInfo = L"Parental Controls CPL entry point is NOT differentiated correctly";
                                    LogTestInfoW(__FUNCTIONW__,
                                                L"Parental Controls SKU differentiation failed.[Current: %s | Expected: %s ]",
                                                L"Not Found",
                                                fExpected ? L"Found" : L"Not Found");
                                }
                            }

                            hr = LOG_FAILED_HR(FromPartialQueryId(IE_TOOLS_INTERNET_OPTIONS_CLOSE));
                            if (SUCCEEDED(hr))
                            {
                                LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                            }

                        }
                    }           
                }           
            }
        }
    }

    LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");
    
    hr = LOG_FAILED_HR(FromPartialQueryId(IE_CLOSE));
    if (SUCCEEDED(hr))
    {
       LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }

    LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}
