/*********************************************************
// Description: BVT - Mobility Center entry point in SKUs
// Created:     HariniD
// Verify:      Pass test case if feature is available
//              in all SKUs but Starter
**********************************************************/

#include <windows.h>
#include "rpf_constants.h"
#include "screenelement.h"
#include "LoggingFunctions.h"
#include <stdio.h>

// Localized strings
const wchar_t* resKeyControlPanel = L"RKB1[explorer];Control Panel;Win32String;$.\\explorer.exe;8234";
const wchar_t* resKeyControlbanel = L"RKB1[explorer];Control banel;Win32String;$.\\system32\\shell32.dll;4161";
const wchar_t* resKeyMaximize = L"RKB1[explorer];Maximize;Win32String;.\\system32\\oleaccrc.dll;143";
const wchar_t* resKeyMobilePC = L"RKB1[explorer];Mobile PC;Win32String;$.\\system32\\shell32.dll;32020";
const wchar_t* resKeyMobilityCenter = L"RKB1[explorer];Mobility Center;Win32String;$.\\system32\\mblctr.exe;1002";
const wchar_t* resKeyWindowsMobilityCenter = L"RKB1[mblctr];Windows Mobility Center;Win32DialogString;$.\\mblctr.exe;100";
const wchar_t* resKeyClose = L"RKB1[mblctr];Close;Win32String;.\\oleaccrc.dll;145";

// LanguageNeutral Strings
LanguageNeutralString langNeutralStartMenu(L"Start Menu");
LanguageNeutralString langNeutralCPCategoryPanel(L"CPCategoryPanel");
LanguageNeutralString langNeutralUnknown(L"\\");

// Complex Resource Keys
ComplexResourceKeyNative cmplxKeyControlbanelMobilePC(L"{%s%s%s}", resKeyControlbanel, langNeutralUnknown, resKeyMobilePC);

#define START_MENU_CONTROL_PANEL   L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", langNeutralStartMenu, resKeyControlPanel
#define CPL_MAXIMIZE               L";Name => '{0}' && ClassName => 'CabinetWClass';Role = 'title bar' && ClassName = 'CabinetWClass';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyControlbanel, resKeyMaximize
#define CPL_MOBILE_PC_LNK          L";Name => '{0}' && ClassName => 'CabinetWClass';Name = '{1}' && Role = 'pane';[VisibleOnly]Name = '{2}' && Role = 'link'", resKeyControlbanel, langNeutralCPCategoryPanel, resKeyMobilePC
#define CPL_MBLCTR_LNK             L";Name => '{1}' && ClassName => 'CabinetWClass';Name = '{0}' && Role = 'pane';[VisibleOnly]Name = '{2}' && Role = 'link'", langNeutralCPCategoryPanel, (wchar_t*) cmplxKeyControlbanelMobilePC, resKeyMobilityCenter
#define MBLCTR_CLOSE_BTN           L";Name => '{0}' && ClassName => 'MobilityCenterApp';Role = 'title bar' && ClassName = 'MobilityCenterApp';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyWindowsMobilityCenter, resKeyClose
#define CPL_CLOSE_BTN              L";Name => '{0}' && ClassName => 'CabinetWClass';Role = 'title bar' && ClassName = 'CabinetWClass';[VisibleOnly]Name = '{1}' && Role = 'push button'", (wchar_t*) cmplxKeyControlbanelMobilePC, resKeyClose

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

// Verify Mobility Center cpl in SKUs
STDAPI MobilityCenterEntryPoints(LPVOID pvReserved)
{

    BOOL fResult = FALSE;

    LogTestBeginW(__FUNCTIONW__, L"Beginning Mobility Center BVT test case...");

    LogTestInfoW(__FUNCTIONW__, L"Launch Start Button...\n");
    HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));

    if (SUCCEEDED(hr))
    {
        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
        LogTestInfoW(__FUNCTIONW__, L"Launch Control Panel...\n");
        hr = LOG_FAILED_HR(FromPartialQueryId(START_MENU_CONTROL_PANEL));

        if (SUCCEEDED(hr))
        {
            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
            LogTestInfoW(__FUNCTIONW__, L"Maximize Control Panel...\n");
            hr = LOG_FAILED_HR(FromPartialQueryId(CPL_MAXIMIZE));

            if (SUCCEEDED(hr))
            {
                LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                //Get Product Type
                LogTestInfoW(__FUNCTIONW__, L"Getting product type...\n");
                DWORD dwProductInfoType = 0;
                if (!GetProductInfo(6, 0, 0, 0, &dwProductInfoType))
                {
                    LogTestInfoW(__FUNCTIONW__, L"GetProductInfo failed.\n");
                }

                LogTestInfoW(__FUNCTIONW__, L"Click Mobile PC link...\n");
                hr = FromPartialQueryId(CPL_MOBILE_PC_LNK);
                LeftButtonClick(CLICKABLE_POINT);

                // Unable to find Mobile PC item
                if (FAILED(hr))
                {
                    if (PRODUCT_STARTER == dwProductInfoType)
                    {
                        // pass test case if Mobile PC not found in Starter
                        fResult = TRUE;
                    }

                    else
                    {
                        // fail test case if Mobile PC not found in other SKUs
                        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                        fResult = FALSE;
                    }
                }

                // Able to find Mobile PC item
                else
                {
                    // fail test case for Starter
                    if (PRODUCT_STARTER == dwProductInfoType)
                    {
                        fResult = FALSE;
                    }
                    else
                    {
                        LogTestInfoW(__FUNCTIONW__, L"Click Mobility Center link...\n");
                        hr = LOG_FAILED_HR(FromPartialQueryId(CPL_MBLCTR_LNK));

                        if (SUCCEEDED(hr))
                        {
                            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                            LogTestInfoW(__FUNCTIONW__, L"Close Mobility Center...\n");
                            hr = LOG_FAILED_HR(FromPartialQueryId(MBLCTR_CLOSE_BTN));

                            if (SUCCEEDED(hr))
                            {
                                LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                                fResult = TRUE;
                            }
                        }
                    }
                }
            }
        }
    }

    // clean up: close windows
    if (SUCCEEDED(hr))
    {

        LogTestInfoW(__FUNCTIONW__, L"Close Control Panel...\n");
        hr = LOG_FAILED_HR(FromPartialQueryId(CPL_CLOSE_BTN));

        if (SUCCEEDED(hr))
        {
            hr = LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
        }
    }

    LogTestResultW(fResult, __FUNCTIONW__, L"Completed Mobility Center BVT test case.");
    return NOERROR;
}


