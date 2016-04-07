#include <windows.h>            //Common Windows types
//#include "rpf_constants.h"
#include "screenelement.h"             //RPF
#include "LoggingFunctions.h"
#include "rpf_skudiff.h" // SKU Diff Contants
#include "SKUDIFF_UTIL.h"
//#include "rpf_skudiff_constants.h" // SKU Diff Contants

STDAPI InitTest(LPVOID)
{
    return InitPlayBackForTargetWindow(RPF_WINDOWLESS);
}

STDAPI UnInitTest()
{
    FinishPlayBack();
    return NOERROR;
}

#define ALLOCATION_FAILURE	-2
#define UNKNOWN_ERROR		-3
int GetProcessorCount()
{
    BOOL rc = FALSE;
    DWORD returnLength = 0;
    DWORD SocketCount = 0;
    DWORD byteOffset = 0;
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = NULL, ptr;

    while( !rc ) {
        rc = GetLogicalProcessorInformation(buffer, &returnLength);

        if( !rc ) {
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
                if (buffer) 
                    free(buffer);

                buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(returnLength);

                if (!buffer) {
                    return (ALLOCATION_FAILURE);
                }
            } 
            else 
            {
                 return (UNKNOWN_ERROR);
            }
        } 
    }

    ptr = buffer;

    while (byteOffset < returnLength) 
    {
        switch (ptr->Relationship) 
        {
            case RelationProcessorPackage:
                SocketCount++;
                break;

            default:
                break;
        }
        byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
        ptr++;
    }

    free (buffer);

    return SocketCount;
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
 
    int cCpuSocketsInUse = GetProcessorCount();

    if( cCpuSocketsInUse <= 0 ) {
        switch( cCpuSocketsInUse ) {
        case UNKNOWN_ERROR:
            LogTestInfoW(__FUNCTIONW__,
                    L"Unknown Error while getting processor relationship information.  [LastError : %d ]",
                    GetLastError());
            break;
        case ALLOCATION_FAILURE:
            LogTestInfoW(__FUNCTIONW__, L"Allocations Error of memory to store processor relationship information" );
	}

        LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
        return NOERROR;
    }

    int nMaxCpuSocketsExpected = GetMaxCpuSocketsExpected();

    LogTestInfoW(__FUNCTIONW__,
                    L"RAM SKU differentiation results.[Current CPU Sockets : %d | Expected Max CPU Sockets: %d ]",
                    cCpuSocketsInUse, nMaxCpuSocketsExpected);

    // check how many CPU Sockets this machine is using.
    if (cCpuSocketsInUse <= nMaxCpuSocketsExpected)
    {
        fPassed = TRUE;
        pwszResultInfo = L"CPU Sockets Feature is differentiated correctly for this SKU";
    }
    else
    {
        pwszResultInfo = L"CPU Sockets is not differentiated correctly";
    }

    LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}


