#include <windows.h>            //Common Windows types
//#include "rpf_constants.h"
#include "screenelement.h"             //RPF
#include "LoggingFunctions.h"
#include "rpf_skudiff.h" // SKU Diff Contants
#include "SKUDIFF_UTIL.h"

using namespace RPFPlayback;
using namespace SKUDiff;



/* The test looks for the Video DVD link under the Burn Button*/



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
//    VerifyMakeDVDMovie_StartMenuEntryPoint 
//  
STDAPI VerifyMakeDVDMovie(LPVOID pvReserved)
{
	BOOL    fPassed = FALSE;
	LPWSTR pwszResultInfo = NULL;

	BOOL fFoundMakeDVDMovie = FALSE;
	BOOL fExpected = FALSE;
	DWORD dwProductInfoType = 0;

	HRESULT hr = E_FAIL;


	if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
	{
		switch (dwProductInfoType)
		{
		case PRODUCT_STARTER:
		case PRODUCT_HOME_BASIC:
		case PRODUCT_HOME_BASIC_N:
		case PRODUCT_ENTERPRISE:
		case PRODUCT_ENTERPRISE_N:
			fExpected = FALSE;
			LogTestInfoW(__FUNCTIONW__, L"Windows Photo Gallery - Make DVD Movie  not expected here");
			break;
		case PRODUCT_HOME_PREMIUM:
		case PRODUCT_HOME_PREMIUM_N:
		case PRODUCT_ULTIMATE:
		case PRODUCT_ULTIMATE_N:
			fExpected = TRUE;
			LogTestInfoW(__FUNCTIONW__, L"Windows Photo Gallery - Make DVD Movie expected here!");
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
		hr = (WOWFromPartialQueryId(STARTMENU_WINDOWS_PHOTO_GALLERY));

		if (FAILED(hr))
		{
			LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't Find Photo Gallery in Start Menu.");
			return NOERROR;
		}
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	}

	Snooze();
	
	hr = LOG_FAILED_HR(FromPartialQueryId(PHOTO_GALLERY_CLOSE));
	if (SUCCEEDED(hr))
	{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	}
	
	//Restaring the photo gallery because when you load it for the first time it takes while to load all the pictures and videos.
	
	if (SUCCEEDED(OpenAllPrograms()))
	{

		hr = (WOWFromPartialQueryId(STARTMENU_WINDOWS_PHOTO_GALLERY));

		if (FAILED(hr))
		{
			LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't Find Photo Gallery in Start Menu.");
			return NOERROR;
		}
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		
		
		//hr =(WOWFromPartialQueryId(PHOTO_GALLERY_BURN));
		if (!IsAvailable(1000,PHOTO_GALLERY_BURN)) //if Fails to find Burn on the window then look under the overflow buttons
		{
			hr = (WOWFromPartialQueryId(PHOTO_GALLERY_MORE_OPTIONS));
			if(SUCCEEDED(hr))
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				hr = (WOWFromPartialQueryId(PHOTO_GALLERY_MORE_OPTION_BURN));
				if(FAILED(hr)) //If you can't find Burn under the Overflow button test fails to proceed.
				{
					LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't Find Burn Option in Windows Photo Gallery");
					return NOERROR;
				}
				else
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));	
				}				
			}
			else 
			{
				LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't Find Burn Option in Windows Photo Gallery...");
				return NOERROR;
			}
		}
		else
		{
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		}

		hr = (WOWFromPartialQueryId(PHOTO_GALLERY_VIDEO_DVD));
		
		fFoundMakeDVDMovie = SUCCEEDED(hr);


		if (fFoundMakeDVDMovie  != fExpected)
		{
			LogTestInfoW(__FUNCTIONW__,
				L"Windows Photo Gallery - Make DVD Movie SKU differentiation failed.[Current: %s | Expected: %s ]",
				fFoundMakeDVDMovie ? L"Found": L"Not Found",
				fExpected ? L"Found" : L"Not Found");
		}
		else
		{
			fPassed = TRUE;
			pwszResultInfo = L"Windows Photo Gallery - Make DVD Movie entry point is differentiated correctly";
		}
		

	}

	LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");

	hr = LOG_FAILED_HR(FromPartialQueryId(PHOTO_GALLERY_CLOSE));
	if (SUCCEEDED(hr))
	{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	}

	LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
	return NOERROR;
}





