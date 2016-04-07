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
	return SKUUnInitTest();
}

//    
//    VerifyWmp_StartMenuEntryPoint 
//  
STDAPI VerifyWmp_StartMenuEntryPoint(LPVOID pvReserved)
{
	BOOL    fPassed = FALSE;
	LPWSTR pwszResultInfo = NULL;
	HRESULT hr = E_FAIL;

	LogTestBeginW(__FUNCTIONW__, L"Verify Windows Media Player available in the Start Menu");    
	// Log WEI scores
	Assessment();

	if (SUCCEEDED(OpenAllPrograms()))
	{

		/*
		hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_ALLPROGRAMS));
		if (SUCCEEDED(hr))  
		{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

		hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_ALLPROGRAMS));
		if (SUCCEEDED(hr))  
		{
		LogTestInfoW(__FUNCTIONW__, L"Have to re-open All Programs menu.");
		//LogTestResultW(fHDCodecsPassed, __FUNCTIONW__, pwszResultInfo);
		//return NOERROR;
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		}
		*/

		BOOL fFoundWMP = SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(STARTMENU_WINDOWS_MEDIA_PLAYER)));
		BOOL fExpected = FALSE;
		DWORD dwProductInfoType = 0;
		if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
		{
			switch (dwProductInfoType)
			{
			case PRODUCT_BUSINESS_N:
			case PRODUCT_HOME_BASIC_N:
			case PRODUCT_HOME_PREMIUM_N:
			case PRODUCT_ENTERPRISE_N:
			case PRODUCT_ULTIMATE_N:
				LogTestInfoW(__FUNCTIONW__, L"Windows Media Player is not expected here!");
				break;
			case PRODUCT_STARTER:
			case PRODUCT_HOME_BASIC:
			case PRODUCT_HOME_PREMIUM:
			case PRODUCT_BUSINESS:
			case PRODUCT_ENTERPRISE:
			case PRODUCT_ULTIMATE:
				fExpected = TRUE;
				pwszResultInfo = L"Windows Media Player expected here.";
				break;
			default:
				LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
				pwszResultInfo = L"Could not verify behavior";
				break;
			}

			if (fFoundWMP != fExpected)
			{
				LogTestInfoW(__FUNCTIONW__,
					L"WMP SKU differentiation failed.[Current: %s | Expected: %s ]",
					fFoundWMP ? L"Found": L"Not Found",
					fExpected ? L"Found" : L"Not Found");
			}
			else
			{
				fPassed = TRUE;
				pwszResultInfo = L"WMP entry point is differentiated correctly";
				if (fExpected)
				{
					//RightButtonClick(CLICKABLE_POINT);
				}
			}
		}
		else
		{
			LogTestInfoW(__FUNCTIONW__, L"GetProductInfo failed.");
			pwszResultInfo = L"GetProductInfo failed.";
		}

	}

	LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");

	hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
	if (SUCCEEDED(hr))
	{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	}


	LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
	return NOERROR;
}


//    
//    VerifyMm_StartMenuEntryPoint 
//  
STDAPI VerifyMm_StartMenuEntryPoint(LPVOID pvReserved)
{
	BOOL    fPassed = FALSE;
	LPWSTR pwszResultInfo = NULL;
	HRESULT hr = E_FAIL;

	LogTestBeginW(__FUNCTIONW__, L"Verify Movie Maker is available in the Start Menu");    
	LOGRESKEY(resKeyWindowsMovieMaker);
	if (SUCCEEDED(OpenAllPrograms()))
	{
		/*
		hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
		if (SUCCEEDED(hr))
		{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

		hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_ALLPROGRAMS));
		if (SUCCEEDED(hr))  
		{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

		hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_ALLPROGRAMS));
		if (SUCCEEDED(hr))  
		{
		LogTestInfoW(__FUNCTIONW__, L"Have to re-open All Programs menu.");
		//LogTestResultW(fHDCodecsPassed, __FUNCTIONW__, pwszResultInfo);
		//return NOERROR;
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		}
		*/



		//BOOL fFoundMMx64 = SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(STARTMENU_WINDOWS_MOVIE_MAKERx64)));
		//BOOL fFoundMM = (fFoundMMx86 || fFoundMMx64);
		BOOL fExpected = FALSE;
		DWORD dwProductInfoType = 0;

		if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
		{
			switch (dwProductInfoType)
			{
			case PRODUCT_BUSINESS_N:
			case PRODUCT_HOME_BASIC_N:
			case PRODUCT_HOME_PREMIUM_N:
			case PRODUCT_ENTERPRISE_N:
			case PRODUCT_ULTIMATE_N:
				LogTestInfoW(__FUNCTIONW__, L"Windows Movie Maker is not expected here!");
				break;
			case PRODUCT_STARTER:
			case PRODUCT_HOME_BASIC:
			case PRODUCT_HOME_PREMIUM:
			case PRODUCT_BUSINESS:
			case PRODUCT_ENTERPRISE:
			case PRODUCT_ULTIMATE:
				fExpected = TRUE;
				pwszResultInfo = L"Windows Movie Maker expected here.";
				break;
			default:
				LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
				pwszResultInfo = L"Could not verify behavior";
				break;
			}

			BOOL fFoundMM = SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(STARTMENU_WINDOWS_MOVIE_MAKER)));
		
			if (fFoundMM != fExpected)
			{
				LogTestInfoW(__FUNCTIONW__,
					L"MM SKU differentiation failed.[Current: %s | Expected: %s ]",
					fFoundMM ? L"Found": L"Not Found",
					fExpected ? L"Found" : L"Not Found");
			}
			else
			{
				fPassed = TRUE;
				pwszResultInfo = L"Movie Maker entry point is differentiated correctly";
				if (fExpected)
				{
					//RightButtonClick(CLICKABLE_POINT);
				}
			}
		}
		else
		{
			LogTestInfoW(__FUNCTIONW__, L"GetProductInfo failed.");
			pwszResultInfo = L"GetProductInfo failed.";
		}

	}

	LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");

	hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
	if (SUCCEEDED(hr))
	{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	}


	LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
	return NOERROR;
}


