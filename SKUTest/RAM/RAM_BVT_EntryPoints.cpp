#include <windows.h>            //Common Windows types
//#include "rpf_constants.h"
#include "screenelement.h"             //RPF
#include "LoggingFunctions.h"
#include "rpf_skudiff.h" // SKU Diff Contants
#include <shldisp.h> // IShellDispatch2
#include <math.h>
#include "SKUDIFF_UTIL.h"


using namespace SKUDiff;

#define RAM_512MB               512
#define RAM_4GB_IN_MB           4096
#define RAM_8GB_IN_MB           8192
#define RAM_16GB_IN_MB          16384
#define RAM_128GB_IN_MB         131072
#define BYTE_TO_MB_DIVISOR      1048576

#define TEN_SECONDS_IN_MS       10000
#define TWO_SECONDS_IN_MS       2000

#define KILO      (1024)
#define MEGA      (1024*1024)
#define GIGA      (1024*1024*1024)


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

// GetMaxRamInMbExpected
//
// Helper function that determines the max RAM in MB supported on the current installed SKU.
// Returns 0 : if SKU not supported on current processor architecture or is SKU cannot be determined
int GetMaxRamInMbExpected()
{

   



    int nMaxRamInMbExpected = 0;

    // get processor architecture upfront.
    BOOL fIs64BitProcessor = FALSE;
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    if (systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ||
        systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
    {
        fIs64BitProcessor = TRUE;
    }



    DWORD dwProductInfoType = 0;
    if (GetProductInfo(6, 0, 0, 0, &dwProductInfoType))
    {
        switch (dwProductInfoType)
        {
            case PRODUCT_STARTER:
            {
                if (!fIs64BitProcessor)
                {
                    nMaxRamInMbExpected = RAM_4GB_IN_MB;
                    LogTestInfoW(__FUNCTIONW__, L"Max RAM for Starter on a 32-bit processor is %dMB!", nMaxRamInMbExpected);
                }
                else
                {
                    LogTestInfoW(__FUNCTIONW__, L"Starter not supported on 64-bit processors!!");
                }
                break;
            }
            case PRODUCT_HOME_BASIC:
            case PRODUCT_HOME_BASIC_N:
            {
                if (!fIs64BitProcessor)
                {
                    nMaxRamInMbExpected = RAM_4GB_IN_MB;
                    LogTestInfoW(__FUNCTIONW__, L"Max RAM for Home Basic on a 32-bit processor is %dMB!", nMaxRamInMbExpected);
                }
                else
                {
                    nMaxRamInMbExpected = RAM_8GB_IN_MB;
                    LogTestInfoW(__FUNCTIONW__, L"Max RAM for Home Basic on a 32-bit processor is %dMB!", nMaxRamInMbExpected);
                }
                break;
            }
            case PRODUCT_HOME_PREMIUM:
            case PRODUCT_HOME_PREMIUM_N:
            {
                if (!fIs64BitProcessor)
                {
                    nMaxRamInMbExpected = RAM_4GB_IN_MB;
                    LogTestInfoW(__FUNCTIONW__, L"Max RAM for Home Premium on a 32-bit processor is %dMB!", nMaxRamInMbExpected);
                }
                else
                {
                    nMaxRamInMbExpected = RAM_16GB_IN_MB;
                    LogTestInfoW(__FUNCTIONW__, L"Max RAM for Home Premium on a 32-bit processor is %dMB!", nMaxRamInMbExpected);
                }
                break;
            }
            case PRODUCT_BUSINESS:
            case PRODUCT_BUSINESS_N:
            case PRODUCT_ENTERPRISE:
            case PRODUCT_ENTERPRISE_N:
            case PRODUCT_ULTIMATE:
            case PRODUCT_ULTIMATE_N:
            {
                if (!fIs64BitProcessor)
                {
                    nMaxRamInMbExpected = RAM_4GB_IN_MB;
                    LogTestInfoW(__FUNCTIONW__, L"Max RAM for this SKU on a 32-bit processor is %dMB!", nMaxRamInMbExpected);
                }
                else
                {
                    nMaxRamInMbExpected = RAM_128GB_IN_MB;
                    LogTestInfoW(__FUNCTIONW__, L"Max RAM for this SKU on a 32-bit processor is %dMB!", nMaxRamInMbExpected);
                }
                break;
            }
            default:
                LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
                break;
        }
    }

    return nMaxRamInMbExpected;
}



//    
//    VerifyRAM_ControlPanelEntryPoint 
//  
STDAPI VerifyRAM_ControlPanelEntryPoint(LPVOID pvReserved)
{
    BOOL    fPassed = FALSE;
    LPWSTR pwszResultInfo = L"No Result String Set.";

    LogTestBeginW(__FUNCTIONW__, L"Verify RAM supported is as expected.");

	BOOL fIs64BitProcessor = FALSE;
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    if (systemInfo.wProcessorArchitecture != PROCESSOR_ARCHITECTURE_AMD64 &&
        systemInfo.wProcessorArchitecture != PROCESSOR_ARCHITECTURE_IA64)
    {
        //fIs64BitProcessor = FALSE;
		LogTestInfoW(__FUNCTIONW__, L"Test is Not Applicable on a 32 bit OS, exiting as a Pass."); 
		
		LogTestResultW(TRUE, __FUNCTIONW__, L"Test is Not Applicable.");
		return NOERROR;
    }

	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof (statex);
	GlobalMemoryStatusEx (&statex);

	LogTestInfoW(__FUNCTIONW__, L"There are %d total megabytes (2^20) of physical memory.", (DWORD)statex.ullTotalPhys/MEGA);
  
	if (((DWORD)statex.ullTotalPhys/MEGA) <= (DWORD)GetMaxRamInMbExpected())
	{
		LogTestInfoW(__FUNCTIONW__, L"Hardware has less RAM than the limit. Test is Not Applicable, exiting as a Pass."); 
		LogTestResultW(TRUE, __FUNCTIONW__, L"Test is Not Applicable.");
		return NOERROR;
	}
/*
  LogTestInfoW(__FUNCTIONW__, L"There are %d %d %d free bytes of physical memory.",
           (DWORD)statex.ullAvailPhys/KILO,(DWORD)statex.ullAvailPhys/MEGA,(DWORD)statex.ullAvailPhys/GIGA);
  LogTestInfoW(__FUNCTIONW__, L"There are %d %d %d total bytes of paging file.",
           (DWORD)statex.ullTotalPageFile/KILO,(DWORD)statex.ullTotalPageFile/MEGA,(DWORD)statex.ullTotalPageFile/GIGA);
  LogTestInfoW(__FUNCTIONW__, L"There are %d %d %d free bytes of paging file.",
           (DWORD)statex.ullAvailPageFile/KILO,(DWORD)statex.ullAvailPageFile/MEGA,(DWORD)statex.ullAvailPageFile/GIGA);
  LogTestInfoW(__FUNCTIONW__, L"There are %d %d %d total bytes of virtual memory.",
           (DWORD)statex.ullTotalVirtual/KILO,(DWORD)statex.ullTotalVirtual/MEGA,(DWORD)statex.ullTotalVirtual/GIGA);
  LogTestInfoW(__FUNCTIONW__, L"There are %d %d %d free bytes of virtual memory.",
           (DWORD)statex.ullAvailVirtual/KILO,(DWORD)statex.ullAvailVirtual/MEGA,(DWORD)statex.ullAvailVirtual/GIGA);

  // Show the amount of extended memory available.

  printf ("There are %*I64d free Kbytes of extended memory.",
           statex.ullAvailExtendedVirtual);

*/

    HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
    if (SUCCEEDED(hr))
    {
        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
        
        hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_CONTROL_PANEL));
        if (SUCCEEDED(hr))  
        {
            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

            // "Control Panel Home" assumes a "link" role only if the Control Panel is opened in the "Classic" view.
            // If the Control Panel is already opened in the "Home" view then "Control Panel Home" assumes a "text" role.
            //
            // So set timeout to 10 seconds to quickly check if CPL is currently being opened in 
            // Classic (Control Panel Home role = link) or Classic (Control Panel Home role = text) view.
            // Save the original timeout so it can be set later.
            int nOriginalTimeout = SetSearchTimeOut(TEN_SECONDS_IN_MS);
            hr = LOG_FAILED_HR(FromPartialQueryId(CPL_HOME_VIEW_LINK));
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
            SetSearchTimeOut(nOriginalTimeout);


            hr = LOG_FAILED_HR(FromPartialQueryId(CPL_LINK_SYSTEMMAINTENANCE));
            if (SUCCEEDED(hr))
            {
                LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                hr = LOG_FAILED_HR(FromPartialQueryId(CPL_LINK_SYSTEMCONTROLPANEL));
                if (SUCCEEDED(hr))
                {
                    LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                    ScreenElement *pScreenElement = ScreenElement::FromPartialQueryId(RAM_IN_MB);
                    if (pScreenElement != NULL)
                    {
                        LPWSTR pwszRamControlName = pScreenElement->get_Name();
                        delete pScreenElement;
                        long lDisplayRam = _wtol(pwszRamControlName);

                        LogTestInfoW(__FUNCTIONW__, L"Display RAM in MB = %ld", lDisplayRam);

                        int nRamExpected = GetMaxRamInMbExpected();
                        // check how much RAM this machine is using.
                        MEMORYSTATUSEX memoryStatus;
                        memoryStatus.dwLength = sizeof (memoryStatus);
                        if (LOG_FALSE_BOOL(GlobalMemoryStatusEx (&memoryStatus)))
                        {
                            long lActualRam = ((long)memoryStatus.ullTotalPhys / BYTE_TO_MB_DIVISOR);
                            LogTestInfoW(__FUNCTIONW__, L"RAM on this machine = %dMB actual", lActualRam);

                            // verify that
                            // - actual ram does not exceed ram expected.
                            // - actual ram is within 1MB of displayed ram to account for possible rounding.
                            if (lActualRam <= nRamExpected && (abs(lDisplayRam - lActualRam) <= 1))
                            {
                                fPassed = TRUE;
                                pwszResultInfo = L"RAM Entry point is differentiated correctly";
                                LogTestInfoW(__FUNCTIONW__,
                                    L"RAM SKU differentiation results.[Current RAM : %ld | Displayed RAM: %ld | Expected Max RAM: %d ]",
                                            lActualRam, lDisplayRam, nRamExpected);
                            }
                            else
                            {
                                pwszResultInfo = L"RAM Entry point is not differentiated correctly";
                                LogTestInfoW(__FUNCTIONW__,
                                    L"RAM SKU differentiation failed.[Current RAM : %ld | Displayed RAM: %ld | Expected Max RAM: %d ]",
                                            lActualRam, lDisplayRam, nRamExpected);
                            }
                        }
                    }
                }
            }
            LogTestInfoW(__FUNCTIONW__, L"Closing Control Panel...");
        
            hr = LOG_FAILED_HR(FromPartialQueryId(CPL_SYSTEM_CLOSE_BTN));
            if (SUCCEEDED(hr))
            {
                LeftButtonClick(CLICKABLE_POINT);
                LOG_FAILED_HR(WaitForScreenElementGone(TEN_SECONDS_IN_MS, TWO_SECONDS_IN_MS));
            }
        }
        else
        {
            pwszResultInfo = L"RAM Entry point differentiated could not be verified.";
            LogTestInfoW(__FUNCTIONW__, L"Could not find Control Panel on the Start Menu. Closing Start Menu...");
            hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
            if (SUCCEEDED(hr))
            {
                LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                LOG_FAILED_HR(WaitForScreenElementGone(TEN_SECONDS_IN_MS, TWO_SECONDS_IN_MS));
            }
        }
    }

    LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}


