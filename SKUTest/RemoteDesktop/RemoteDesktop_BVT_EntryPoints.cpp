#include <windows.h>            //Common Windows types
//#include "rpf_constants.h"
#include "screenelement.h"  
#include "LoggingFunctions.h"
#include "rpf_SKUDIFF.h"
#include "SKUDIFF_UTIL.h"

using namespace RPFPlayback;
using namespace SKUDiff;

void CloseExcessWindows() // test specific, ensure a clean state; can be made better with RPF 12+
{
    wchar_t szGlobalQuery[1024];
    GlobalizeQueryId(szGlobalQuery, 1024, SYSTEM_PROPERTIES_CLOSE_BTN);
    LeftClickUntilGone(szGlobalQuery);
    GlobalizeQueryId(szGlobalQuery, 1024, CPL_SYSTEM_CLOSE_BTN);
    LeftClickUntilGone(szGlobalQuery);
}

STDAPI InitTest(LPVOID)
{
    HRESULT hr = SKUInitTest();
    if SUCCEEDED(hr){CloseExcessWindows();}
    return hr;
}

STDAPI UnInitTest()
{
    CloseExcessWindows();
    return SKUUnInitTest();
}

//    
//    Verify RemoteDesktop_BVT_EntryPoints 
//  
STDAPI RemoteDesktop_BVT_EntryPoints(LPVOID pvReserved)
{
    BOOL fPassed = FALSE;
    LPWSTR pwszResultInfo = L"No Result String Set.";
    HRESULT hr = E_FAIL;

    LogTestBeginW(__FUNCTIONW__, L"Verify Remote Desktop UI is differentiated correctly (CPL).");    
/*
    LOGRESKEY(resKeyRemoteOK);
    LOGRESKEY(resKeySystemCPLMainWindow);
    LOGRESKEY(resKeyRemoteSettings);
    LOGRESKEY(resKeyDontallowconnectionsto);
    LOGRESKEY(resKeyAllowconnectionsfrom);
    LOGRESKEY(resKeyRemote);
    LOGRESKEY(resKeyRemoteDesktop);
    LOGRESKEY(resKeyHelpIcon);
    LOGRESKEY(resKeySystemProperties);
*/

    BOOL fExpected = FALSE;
    DWORD dwProductInfoType = 0;
    if( GetProductInfo( WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType ))
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
            LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
            return NOERROR;
        }
    }
    else {
        LogTestInfoW(__FUNCTIONW__, L"GetProductInfo failed.");
        pwszResultInfo = L"GetProductInfo failed.";
    }

	if(!RESKEYSEQUAL(resKeyRemoteTab,resKeyRemoteTabDomain))
	{
		LogTestInfoW(__FUNCTIONW__, L"Localized 'Remote' tab name resource inconsistent, if this is not Psuedo-Loc it is very likely a Localization bug.");
		pwszResultInfo = L"Localized 'Remote' tab name resource inconsistent, if this is not Psuedo-Loc it is very likely a Localization bug.";
	}

    wchar_t Section[1024];
    wchar_t Link[1024];    
    if (SUCCEEDED(GlobalizeQueryId(Section, 1024, CPL_LINK_SYSTEMMAINTENANCE)) &&
        SUCCEEDED(GlobalizeQueryId(Link, 1024, CPL_LINK_SYSTEMCONTROLPANEL)) &&
        SUCCEEDED(OpenSpecificHomeControlPanel(Section, Link)))    {

        hr = LOG_FAILED_HR(FromPartialQueryId(CPL_SYSTEM_REMOTE_NAV_LINK));

        if (SUCCEEDED(hr)) {
            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

		hr = LOG_FAILED_HR(FromPartialQueryId(CPL_REMOTE_PAGE_TAB));
		if(SUCCEEDED(hr))
		{
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		}
		    BOOL fFoundRemoteDesktopUI = SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(CPL_REMOTE_ALLOWCONNTO_RADIO)));
            BOOL fFoundClickablePoint = TRUE;

            if (fFoundRemoteDesktopUI) {
                int x, y;
                fFoundClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));
                LogTestInfoW(__FUNCTIONW__,
                    L"%s Clickable point", fFoundClickablePoint ? L"Found": L"Did not find");
            }


            if(( fFoundRemoteDesktopUI && fFoundClickablePoint ) != fExpected ) {
                LogTestInfoW(__FUNCTIONW__,
                    L"Remote Desktop UI SKU differentiation failed.[Current: %s | Expected: %s ]",
                fFoundRemoteDesktopUI ? L"Found": L"Not Found",
                fExpected ? L"Found" : L"Not Found");
            }
            else {
                fPassed = TRUE;
                pwszResultInfo = L"Remote Desktop CPL entry point is differentiated correctly";
            }
        }

    }

    LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}




