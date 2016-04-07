#include <windows.h>            //Common Windows types
//#include "rpf_constants.h"
#include "screenelement.h"  
#include "LoggingFunctions.h"
#include "rpf_SKUDIFF.h"
#include "SKUDIFF_UTIL.h"
 
using namespace RPFPlayback;
using namespace SKUDiff;

STDAPI InitTest(LPVOID)
{
	HRESULT hr = SKUInitTest();
	//if SUCCEEDED(hr){CloseExcessWindows();}
	return hr;
}

STDAPI UnInitTest()
{
	//CloseExcessWindows();
	return SKUUnInitTest();
}

//    
//    Verify BitLocker_BVT_EntryPoints 
//  
STDAPI BitLocker_BVT_EntryPoints(LPVOID pvReserved)
{
    BOOL    fPassed = FALSE;
    LPWSTR pwszResultInfo = NULL;
	HRESULT hr;
    LogTestBeginW(__FUNCTIONW__, L"Verify BitLocker EntryPoints UI is differentiated correctly (CPL).");    
	//int originalTimeout = SetSearchTimeOut(5000);
 /*
    hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
    if (SUCCEEDED(hr))
    {
        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
        
        hr = LOG_FAILED_HR(FromPartialQueryId(START_MENU_CONTROL_PANEL));*/
        if (SUCCEEDED(OpenControlPanelHomeView()))  
        {
            //LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

            hr = LOG_FAILED_HR(FromPartialQueryId(CPL_LINK_SECURITY));
            if (SUCCEEDED(hr))
            {
                LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                
                BOOL fFoundUI = SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(CPL_LINK_BITLOCKERDRIVEENCRYPTION)));
                BOOL fExpected = FALSE;
                BOOL fIsNotPresent = FALSE;
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
                            LogTestInfoW(__FUNCTIONW__, L"BitLocker EntryPoints not expected here!");
                            break;
                        case PRODUCT_ENTERPRISE:
                        case PRODUCT_ENTERPRISE_N:
                        case PRODUCT_ULTIMATE:
                        case PRODUCT_ULTIMATE_N:
                            fExpected = TRUE;
                            pwszResultInfo = L"BitLocker EntryPoints expected here.";
                            break;
                        default:
                            LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
                            pwszResultInfo = L"Could not verify behavior";
                            break;
                    }

                    if ((fFoundUI && fFoundClickablePoint) != fExpected)
                    {
                        LogTestInfoW(__FUNCTIONW__,
                            L"BitLocker SKU differentiation failed.[Current: %s | Expected: %s ]",
                            fFoundUI ? L"Found": L"Not Found",
                            fExpected ? L"Found" : L"Not Found");
                    }
                    else
                    {
                        fPassed = TRUE;
                        pwszResultInfo = L"BitLocker CPL entry point is differentiated correctly";
                    }
                }
                else
                {
                    LogTestInfoW(__FUNCTIONW__, L"GetProductInfo failed.");
                    pwszResultInfo = L"GetProductInfo failed.";
                }
               
            }
     //  }
    }
   
    LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");
    hr = LOG_FAILED_HR(FromPartialQueryId(CPL_CLOSE_BTN));
    if (SUCCEEDED(hr))
    {
        LeftButtonClick(CLICKABLE_POINT);
    }
 
    LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}




