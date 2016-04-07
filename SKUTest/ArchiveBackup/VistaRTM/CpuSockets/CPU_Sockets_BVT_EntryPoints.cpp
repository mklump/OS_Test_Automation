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

// GetMaxCpuSocketsExpected
//
// Helper function that determines the max number of CPU Sockets supported on the current installed SKU.
// Returns 0 : if SKU not supported on current processor architecture or is SKU cannot be determined
int GetMaxCpuSocketsExpected()
{
    int nMaxCpuSocketsExpected = 0;

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
                LogTestInfoW(__FUNCTIONW__, L"Max CPU Sockets supported = 1!");
                nMaxCpuSocketsExpected = 1;
                break;
            case PRODUCT_BUSINESS:
            case PRODUCT_BUSINESS_N:
            case PRODUCT_ENTERPRISE:
            case PRODUCT_ENTERPRISE_N:
            case PRODUCT_ULTIMATE:
            case PRODUCT_ULTIMATE_N:
                LogTestInfoW(__FUNCTIONW__, L"Max CPU Sockets supported = 2!");
                nMaxCpuSocketsExpected = 2;
                break;
            default:
                LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
                break;
        }
    }

    return nMaxCpuSocketsExpected;
}



//    
//    VerifyCpuSocketsUsage 
//  
STDAPI VerifyCpuSocketsUsage(LPVOID pvReserved)
{
    BOOL    fPassed = FALSE;
    LPWSTR pwszResultInfo = NULL;

    LogTestBeginW(__FUNCTIONW__, L"Verify CPU Sockets supported is as expected.");    
 
    int nMaxCpuSocketsExpected = GetMaxCpuSocketsExpected();
    // check how many CPU Sockets this machine is using.
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    int cCpuSocketsInUse = systemInfo.dwNumberOfProcessors;
    if (cCpuSocketsInUse <= nMaxCpuSocketsExpected)
    {
        fPassed = TRUE;
        pwszResultInfo = L"CPU Sockets Feature is differentiated correctly for this SKU";
    }
    else
    {
        pwszResultInfo = L"CPU Sockets is not differentiated correctly";
        LogTestInfoW(__FUNCTIONW__,
                    L"RAM SKU differentiation results.[Current CPU Sockets : %d | Expected Max CPU Sockets: %d ]",
                    systemInfo.dwNumberOfProcessors, nMaxCpuSocketsExpected);
    }

    LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}


