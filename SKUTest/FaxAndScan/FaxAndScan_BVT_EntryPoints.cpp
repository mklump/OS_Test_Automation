#include <windows.h>            //Common Windows types
//#include "rpf_constants.h"
#include "screenelement.h"             //RPF
#include "LoggingFunctions.h"
#include "rpf_skudiff.h" // SKU Diff Contants
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
//    VerifyFaxAndScan_StartMenuEntryPoint 
//  
STDAPI VerifyFaxAndScan_StartMenuEntryPoint(LPVOID pvReserved)
{
	BOOL    fPassed = FALSE;
	LPWSTR pwszResultInfo = NULL;

	BOOL fFoundFaxandScan = FALSE;
	BOOL fExpected = FALSE;
	DWORD dwProductInfoType = 0;

	HRESULT hr = E_FAIL;


	//LogTestBeginW(__FUNCTIONW__, L"Verify Windows Fax and Scan is available in the Start Menu");    
	//LogResKeyValue(L"resKeyWindowsFaxandScan", resKeyWindowsFaxandScan);
	//LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
	//return NOERROR;
	
	
	

	if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
	{
		switch (dwProductInfoType)
		{
		case PRODUCT_STARTER:
		case PRODUCT_HOME_BASIC:
		case PRODUCT_HOME_BASIC_N:
		case PRODUCT_HOME_PREMIUM:
		case PRODUCT_HOME_PREMIUM_N:
			fExpected = FALSE;
			LogTestInfoW(__FUNCTIONW__, L"Windows Fax and Scan not expected here!");
			break;
		case PRODUCT_ENTERPRISE:
		case PRODUCT_ENTERPRISE_N:
			fExpected = FALSE;
			LogTestInfoW(__FUNCTIONW__, L"Windows Fax and Scan Available, but off by default, assuming not enabled for BVT.");
			break;
		case PRODUCT_BUSINESS:
		case PRODUCT_BUSINESS_N:
		case PRODUCT_ULTIMATE:
		case PRODUCT_ULTIMATE_N:
			fExpected = TRUE;
			LogTestInfoW(__FUNCTIONW__, L"Windows Fax and Scan expected here!");
			break;
		default:
			LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
			pwszResultInfo = L"Could not verify behavior";
			break;
		}
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"GetProductInfo failed.");
		pwszResultInfo = L"GetProductInfo failed.";
	}


	
	if (SUCCEEDED(OpenAllPrograms()))
	{
		

			hr = (FromPartialQueryId(STARTMENU_WINDOWS_FAX_AND_SCAN));
			//LogTestInfoW(__FUNCTIONW__, L"[%x]",hr);
			fFoundFaxandScan = SUCCEEDED(hr);


			if (fFoundFaxandScan  != fExpected)
			{
				LogTestInfoW(__FUNCTIONW__,
					L"Windows Fax and Scan SKU differentiation failed.[Current: %s | Expected: %s ]",
					fFoundFaxandScan ? L"Found": L"Not Found",
					fExpected ? L"Found" : L"Not Found");
			}
			else
			{
				fPassed = TRUE;
				pwszResultInfo = L"Windows Fax and Scan entry point is differentiated correctly";
			}
		

	}

	LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");

	hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
	if (SUCCEEDED(hr))
	{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	}
//SetSearchTimeOut(originalTimeout);

	LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
	return NOERROR;
}

