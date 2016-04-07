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
//    Verify MCE_BVT_EntryPoints 
//  
STDAPI MCE_BVT_EntryPoints(LPVOID pvReserved)
{
	BOOL    fPassed = FALSE;
	LPWSTR pwszResultInfo = NULL;

	LogTestBeginW(__FUNCTIONW__, L"Verify Media Center UI EntryPoints is differentiated correctly (CPL).");    
	// Log WEI scores
	Assessment();
	if(FAILED(OpenAllPrograms()))
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not open Start menu.");
	}
	else
	{
		if (IsAvailable(1000, STARTMENU_MEDIACENTER))
		{
			LogTestInfoW(__FUNCTIONW__, L"Found MCE");
		}
		else
		{
			LogTestInfoW(__FUNCTIONW__, L"Not Found MCE");
		}

		BOOL fFoundUI = SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(STARTMENU_MEDIACENTER)));
		BOOL fFoundClickablePoint = TRUE;
		if (fFoundUI)
		{
			int x;
			int y;
			fFoundClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));
			LogTestInfoW(__FUNCTIONW__,
				L"%s Clickable point", 
				fFoundClickablePoint ? L"Found": L"Did not find");
		}

		BOOL fExpected = FALSE; 
		DWORD dwProductInfoType = 0;
		if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
		{
			switch (dwProductInfoType)
			{
			case PRODUCT_STARTER:
			case PRODUCT_HOME_BASIC:
			case PRODUCT_HOME_BASIC_N:
			case PRODUCT_BUSINESS:
			case PRODUCT_BUSINESS_N:
			case PRODUCT_ENTERPRISE:
			case PRODUCT_ENTERPRISE_N:
			case PRODUCT_HOME_PREMIUM_N:
			case PRODUCT_ULTIMATE_N:
				LogTestInfoW(__FUNCTIONW__, L"Media Center EntryPoints not expected here!");
				break;
			case PRODUCT_HOME_PREMIUM:
			case PRODUCT_ULTIMATE:
				fExpected = TRUE;
				pwszResultInfo = L"Media Center EntryPoints expected here.";
				break;
			default:
				LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
				pwszResultInfo = L"Could not verify behavior";
				break;
			}

			if ((fFoundUI && fFoundClickablePoint) != fExpected)
			{
				LogTestInfoW(__FUNCTIONW__,
					L"Media Center SKU differentiation failed.[Current: %s | Expected: %s ]",
					fFoundUI ? L"Found": L"Not Found",
					fExpected ? L"Found" : L"Not Found");
			}
			else
			{
				fPassed = TRUE;
				pwszResultInfo = L"Media Center CPL entry point is differentiated correctly";
			}
		}
		else
		{
			LogTestInfoW(__FUNCTIONW__, L"GetProductInfo failed.");
			pwszResultInfo = L"GetProductInfo failed.";

		}
	}

	LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
	return NOERROR;
}




