#include <windows.h>            //Common Windows types
#include "rpf_constants.h"
#include "screenelement.h"             //RPF
#include "LoggingFunctions.h"
#include "rpf_skudiff_constants.h" // SKU Diff Contants

#define MAHJONG_TITANS 0
#define CHESS_TITANS 3
#define FREECELL 6
#define HEARTS 9

LPCWSTR rg_Games_Open[] = {
    GAMES_MAHJONG_TITANS,
    GAMES_CHESS_TITANS,
    GAMES_FREECELL,
    GAMES_HEARTS
};

LPCWSTR rg_Games_Close[] = {
    MAHJONG_TITANS_CLOSE,
    CHESS_TITANS_CLOSE,
    FREECELL_CLOSE,
    HEARTS_CLOSE
};

LPCWSTR rg_WindowsFeaturesGames[] = {
    WINDOWS_FEATURES_MAHJONG_TITANS,
    WINDOWS_FEATURES_CHESS_TITANS
};


STDAPI InitTest(LPVOID)
{
    return InitPlayBackForTargetWindow(RPF_WINDOWLESS);
}

STDAPI UnInitTest()
{
    FinishPlayBack();
    return NOERROR;
}

// ArePremiumGamesExpected
//
// Helper function that determines if Premium Games Entry points must be present on the current installed SKU or not.
// Returns True : if Premium Games entry points are expected
// Returns False : if Premium Games entry points are not expected
BOOL ArePremiumGamesExpected()
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
                LogTestInfoW(__FUNCTIONW__, L"Premium Games not expected here!");
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
    else
    {
        LogTestInfoW(__FUNCTIONW__, L"Failed to get product/SKU info");
    }

    return fExpected;
}

// AreDefaultInstalledGamesExpected
//
// Helper function that determines if Default Installed Games Entry points must be present on the current installed SKU or not.
// Returns True : if Default Installed Games entry points are expected
// Returns False : if Default Installed Games entry points are not expected
BOOL AreDefaultInstalledGamesExpected()
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
                LogTestInfoW(__FUNCTIONW__, L"Games should not be installed by default on this SKU!");
                break;
            case PRODUCT_STARTER:
            case PRODUCT_HOME_BASIC:
            case PRODUCT_HOME_BASIC_N:
            case PRODUCT_HOME_PREMIUM:
            case PRODUCT_ULTIMATE:
                fExpected = TRUE;
                break;
            default:
                LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
                break;
        }
    }
    else
    {
        LogTestInfoW(__FUNCTIONW__, L"Failed to get product/SKU info");
    }

    return fExpected;
}

// OpenGamesExplorer
//
// Helper function that opens Games Explorer depending on the SKU installed.
// Business/Enterprise : Games are not installed by default. Go to Start->All Programs-> Games
// All other SKUs      : Games are installed by default. Go to Start-> Games.
//
// Returns True : if Games Explorer is opened successfully
// Returns False : if Games Explorer failed to open
BOOL OpenGamesExplorer()
{
    BOOL fOpenedGamesExplorer = FALSE;

    HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
    if (SUCCEEDED(hr))
    {
        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

        DWORD dwProductInfoType = 0;
        if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
        {
            switch (dwProductInfoType)
            {
                case PRODUCT_BUSINESS:
                case PRODUCT_BUSINESS_N:
                case PRODUCT_ENTERPRISE:
                {
                    HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_ALLPROGRAMS));
                    if (SUCCEEDED(hr))
                    {
                        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                        HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(ALL_PROGRAMS_GAMES));
                        if (SUCCEEDED(hr))
                        {
                            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                            HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(ALL_PROGRAMS_GAMES_EXPLORER));
                            if (SUCCEEDED(hr))
                            {
                                LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                                fOpenedGamesExplorer = TRUE;
                            }
                        }
                    }
                    break;
                }
                case PRODUCT_STARTER:
                case PRODUCT_HOME_BASIC:
                case PRODUCT_HOME_BASIC_N:
                case PRODUCT_HOME_PREMIUM:
                case PRODUCT_ULTIMATE:
                {
                    HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_GAMES));
                    if (SUCCEEDED(hr))
                    {
                        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                        fOpenedGamesExplorer = TRUE;
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
        else
        {
            LogTestInfoW(__FUNCTIONW__, L"Failed to get product/SKU info");
        }
    }

    if (fOpenedGamesExplorer)
    {
        // Games update and setup options dialog box may/maynot pop up depending 
        // on whether this is the first time Games Explorer is being opened.

        // So set timeout to 10 seconds to quickly close the dialog box if opened 
        // Save the original timeout so it can be set later.
        int originalTimeout = SetSearchTimeOut(10000);
        HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(GAMES_UPDATE_AND_OPTIONS));
        if (FAILED(hr))
        {
            // this is not the first time games explorer is being opened.
            LogTestInfoW(__FUNCTIONW__, L"Games update and options window was not open. Moving forward.");
        }
        else
        {
            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
        }
        // restore original timeout
        SetSearchTimeOut(originalTimeout);
    }
    else
    {
        LogTestInfoW(__FUNCTIONW__, L"Failed to open Games Explorer");
    }

    return fOpenedGamesExplorer;
}

//    
//    VerifyGames_PremiumGamesEntryPoint 
//  
STDAPI VerifyGames_PremiumGamesEntryPoint(LPVOID pvReserved)
{
    BOOL    fPassed = FALSE;
    LPWSTR pwszResultInfo = NULL;

    LogTestBeginW(__FUNCTIONW__, L"Verify Premium Games are available in Games Explorer");    

    // There are two ways to get to the games explorer depending on the SKU installed.
    // Business/Enterprise : Games are not installed by default.
    // All other SKUs      : Games are installed by default. Go to Start-> Games.
    if (!AreDefaultInstalledGamesExpected())
    {
        pwszResultInfo = L"Games not installed by default on Business/BusinessN/Enteprise. No need to check for Premium Games.";
        fPassed = TRUE;
    }
    else
    {
        if (OpenGamesExplorer())
        {
            BOOL fExpected = ArePremiumGamesExpected();

            // loop starting from MAHJONG_TITANS to CHESS_TITANS.
            for (int gamesIndex = MAHJONG_TITANS; gamesIndex <= CHESS_TITANS; gamesIndex += 3)
            {
                BOOL fFoundGameClickablePoint = FALSE;
                if (SUCCEEDED(FromPartialQueryId(
                                                (wchar_t*)rg_Games_Open[gamesIndex], 
                                                (wchar_t*)rg_Games_Open[gamesIndex + 1], 
                                                (wchar_t*)rg_Games_Open[gamesIndex + 2])))
                {
                    int x, y;
                    fFoundGameClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));

                    LogTestInfoW(__FUNCTIONW__,
                                 L"%s Clickable point ", fFoundGameClickablePoint ? L"Found": L"Did not find");

                    if (fFoundGameClickablePoint != fExpected)
                    {
                        pwszResultInfo = L"Entry point is not differentiated correctly";
                        LogTestInfoW(__FUNCTIONW__,
                                    L"Premium Games SKU differentiation failed.[Current: %s | Expected: %s ]",
                                    fFoundGameClickablePoint ? L"Found": L"Not Found",
                                    fExpected ? L"Found" : L"Not Found");
                        break;
                    }
                    else
                    {
                        fPassed = TRUE;
                        if (fExpected)
                        {
                            // Go ahead and open the game.
                            LOG_FAILED_HR(DoubleClick(CLICKABLE_POINT));

                            if (gamesIndex == CHESS_TITANS)
                            {
                                // Select difficulty dialog box may/maynot pop up depending 
                                // on whether this is the first time Chess is being opened.

                                // So set timeout to 10 seconds to quickly close the dialog box if opened 
                                // Save the original timeout so it can be set later.
                                int originalTimeout = SetSearchTimeOut(10000);
                                HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(GAMES_SELECT_DIFFICULTY));
                                if (FAILED(hr))
                                {
                                    // this is not the first time chess is being opened.
                                    LogTestInfoW(__FUNCTIONW__, L"Select Difficulty window was not open. Moving forward.");
                                }
                                else
                                {
                                    LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                                }

                                // restore original timeout
                                SetSearchTimeOut(originalTimeout);
                            }

                            // Now close the game.
                            if (SUCCEEDED(FromPartialQueryId(
                                                    (wchar_t*)rg_Games_Close[gamesIndex], 
                                                    (wchar_t*)rg_Games_Close[gamesIndex + 1], 
                                                    (wchar_t*)rg_Games_Close[gamesIndex + 2])))
                            {
                                LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                                pwszResultInfo = L"Entry point is differentiated correctly";
                                LogTestInfoW(__FUNCTIONW__,
                                            L"Entry point results.[Current: %s | Expected: %s ]",
                                            fFoundGameClickablePoint ? L"Found": L"Not Found",
                                            fExpected ? L"Found" : L"Not Found");  
                            }
                            else
                            {
                                fPassed = FALSE;
                            }
                        }
                    }
                }
                else
                {
                    if (fExpected)
                    {
                        pwszResultInfo = L"Entry point is not differentiated correctly";
                        LogTestInfoW(__FUNCTIONW__,
                                    L"Premium Games SKU differentiation failed.[Current: %s | Expected: %s ]",
                                    fFoundGameClickablePoint ? L"Found": L"Not Found",
                                    fExpected ? L"Found" : L"Not Found");
                    }
                    else
                    {
                        pwszResultInfo = L"Premium Games Entry point is differentiated correctly";
                        fPassed = TRUE;
                    }
                    break;
                }
            }
        }
        LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");
        
        HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(GAMES_CLOSE_BTN));
        if (SUCCEEDED(hr))
        {
           LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
        }
    } 
   
    LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}


//    
//    VerifyGames_DefaultInstalledGamesEntryPoint 
//  
STDAPI VerifyGames_DefaultInstalledGamesEntryPoint(LPVOID pvReserved)
{
    BOOL    fPassed = FALSE;
    LPWSTR pwszResultInfo = NULL;
    BOOL fExpected = AreDefaultInstalledGamesExpected();

    LogTestBeginW(__FUNCTIONW__, L"Verify Default Installed Games are available in Games Explorer");    
 
    EnableInfoWindow(TRUE);

    // There are two ways to get to the games explorer depending on the SKU installed.
    // Business/Enterprise : Games are not installed by default. Go to Start->All Programs-> Games
    // All other SKUs      : Games are installed by default. Go to Start-> Games.
    if (OpenGamesExplorer())
    {
        // loop starting from FREECELL to HEARTS.
        for (int gamesIndex = FREECELL; gamesIndex <= HEARTS; gamesIndex += 3)
        {
            BOOL fFoundGameClickablePoint = FALSE;
            if (SUCCEEDED(FromPartialQueryId(
                                            (wchar_t*)rg_Games_Open[gamesIndex], 
                                            (wchar_t*)rg_Games_Open[gamesIndex + 1], 
                                            (wchar_t*)rg_Games_Open[gamesIndex + 2])))
            {
                int x, y;
                fFoundGameClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));

                LogTestInfoW(__FUNCTIONW__,
                             L"%s Clickable point ", fFoundGameClickablePoint ? L"Found": L"Did not find");

                if (fFoundGameClickablePoint != fExpected)
                {
                    pwszResultInfo = L"Entry point is not differentiated correctly";
                    LogTestInfoW(__FUNCTIONW__,
                                L"Default Installed Games SKU differentiation failed.[Current: %s | Expected: %s ]",
                                fFoundGameClickablePoint ? L"Found": L"Not Found",
                                fExpected ? L"Found" : L"Not Found");
                    break;
                }
                else
                {
                    fPassed = TRUE;
                    if (fExpected)
                    {
                        // Go ahead and open the game.
                        LOG_FAILED_HR(DoubleClick(CLICKABLE_POINT));

                        // Now close the game.
                        if (SUCCEEDED(FromPartialQueryId(
                                                (wchar_t*)rg_Games_Close[gamesIndex], 
                                                (wchar_t*)rg_Games_Close[gamesIndex + 1], 
                                                (wchar_t*)rg_Games_Close[gamesIndex + 2])))
                        {
                            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                            pwszResultInfo = L"Entry point is differentiated correctly";
                            LogTestInfoW(__FUNCTIONW__,
                                        L"Entry point results.[Current: %s | Expected: %s ]",
                                        fFoundGameClickablePoint ? L"Found": L"Not Found",
                                        fExpected ? L"Found" : L"Not Found");  
                        }
                        else
                        {
                            fPassed = FALSE;
                        }
                    }
                }
            }
            else
            {
                if (fExpected)
                {
                    pwszResultInfo = L"Entry point is not differentiated correctly";
                    LogTestInfoW(__FUNCTIONW__,
                                L"Default Installed Games SKU differentiation failed.[Current: %s | Expected: %s ]",
                                fFoundGameClickablePoint ? L"Found": L"Not Found",
                                fExpected ? L"Found" : L"Not Found");
                }
                else
                {
                    pwszResultInfo = L"Default Installed Games Entry point is differentiated correctly";
                    fPassed = TRUE;
                }
                break;
            }
        }
    }
   
    LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");
    
    HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(GAMES_CLOSE_BTN));
    if (SUCCEEDED(hr))
    {
       LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }

    LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}

//    
//    VerifyGames_WindowsFeaturesEntryPoint 
//  
STDAPI VerifyGames_WindowsFeaturesEntryPoint(LPVOID pvReserved)
{
    BOOL    fPassed = FALSE;
    LPWSTR pwszResultInfo = NULL;
    BOOL fExpected = ArePremiumGamesExpected();

    LogTestBeginW(__FUNCTIONW__, L"Verify Premium Games are available in OCM");    
 
    EnableInfoWindow(TRUE);

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

            hr = LOG_FAILED_HR(FromPartialQueryId(CPL_HOME_PROGRAMS));
            if (SUCCEEDED(hr))  
            {
                LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                hr = LOG_FAILED_HR(FromPartialQueryId(CPL_PROGRAMS_WINDOWS_FEATURES));
                if (SUCCEEDED(hr))  
                {
                    LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                    hr = LOG_FAILED_HR(FromPartialQueryId(WINDOWS_FEATURES_GAMES));
                    if (SUCCEEDED(hr))  
                    {
                        LOG_FAILED_HR(Expand());

                        // loop starting from MAHJONG_TITANS to CHESS_TITANS.
                        for (int gamesIndex = MAHJONG_TITANS; gamesIndex <= CHESS_TITANS; gamesIndex += 3)
                        {
                            BOOL fFoundGameClickablePoint = FALSE; 
                            if (SUCCEEDED(FromPartialQueryId(
                                            (wchar_t*)rg_WindowsFeaturesGames[gamesIndex], 
                                            (wchar_t*)rg_WindowsFeaturesGames[gamesIndex + 1], 
                                            (wchar_t*)rg_WindowsFeaturesGames[gamesIndex + 2])))
                            {
                                // To ascertain presence/absence, look for the clickable point.
                                int x, y;
                                fFoundGameClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));
                                LogTestInfoW(__FUNCTIONW__,
                                             L"%s Clickable point for Mahjong Titans", 
                                             fFoundGameClickablePoint ? L"Found": L"Did not find");

                                if (fFoundGameClickablePoint != fExpected)
                                {
                                    pwszResultInfo = L"Windows Features Games entry point is NOT differentiated correctly";
                                    LogTestInfoW(__FUNCTIONW__,
                                                L"Windows Features Premium Games SKU differentiation failed.[Current: %s | Expected: %s ]",
                                                fFoundGameClickablePoint ? L"Found": L"Not Found",
                                                fExpected ? L"Found" : L"Not Found");
                                    break;
                                }
                                else
                                {
                                    fPassed = TRUE;
                                    pwszResultInfo = L"Premium Games Windows Features entry point is differentiated correctly";

                                    // Go ahead and click Mahjong Titans and then check for Chess Titans as well.
                                    if (fExpected)
                                    {
                                        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                                    }
                                }
                            }
                            else
                            {
                                if (fExpected)
                                {
                                    pwszResultInfo = L"Windows Features Games entry point is NOT differentiated correctly";
                                    LogTestInfoW(__FUNCTIONW__,
                                                L"Windows Features Premium Games SKU differentiation failed.[Current: %s | Expected: %s ]",
                                                fFoundGameClickablePoint ? L"Found": L"Not Found",
                                                fExpected ? L"Found" : L"Not Found");
                                }
                                else
                                {
                                    pwszResultInfo = L"Windows Features Games entry point is differentiated correctly";
                                    fPassed = TRUE;
                                }
                                break;
                            }
                        }
                    }
                    LogTestInfoW(__FUNCTIONW__, L"Closing Windows Features...");
                    
                    hr = LOG_FAILED_HR(FromPartialQueryId(WINDOWS_FEATURES_CLOSE));
                    if (SUCCEEDED(hr))
                    {
                       LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
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

   

