
#include <windows.h>            //Common Windows types
//#include "rpf_constants.h"
#include "screenelement.h"             //RPF
#include "LoggingFunctions.h"
#include "rpf_skudiff.h" // SKU Diff Contants
#include "SKUDIFF_UTIL.h"

using namespace RPFPlayback;
using namespace SKUDiff;



void CloseExcessWindows()
{
		wchar_t szGlobalQuery[1024];
		GlobalizeQueryId(szGlobalQuery, 1024,CLOSE_MEDIA_SHARING);
		LeftClickUntilGone(szGlobalQuery);
		GlobalizeQueryId(szGlobalQuery, 1024,CLOSE_OPTIONS);
		LeftClickUntilGone(szGlobalQuery);
		GlobalizeQueryId(szGlobalQuery, 1024,CLOSE_WMP);
		LeftClickUntilGone(szGlobalQuery);

}


STDAPI InitTest(LPVOID)
{
	HRESULT hr = SKUInitTest();
	if SUCCEEDED(hr)
	{
		CloseExcessWindows();
	}
	return hr;
}

STDAPI UnInitTest()
{
	CloseExcessWindows();
	return SKUUnInitTest();
}

//    
//    Verify Windows Media Connect In Windows Media Player
//  
STDAPI VerifyWindowsMediaConnect(LPVOID pvReserved)
{
	BOOL    fPassed = FALSE;
	LPWSTR pwszResultInfo = NULL;

	BOOL fFoundWMConnect = FALSE;
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
			fExpected = FALSE;
			LogTestInfoW(__FUNCTIONW__, L"Windows Media Connect in WMP not expected here!");
			break;
		case PRODUCT_HOME_BASIC:
		case PRODUCT_HOME_BASIC_N:
		case PRODUCT_HOME_PREMIUM:
		case PRODUCT_HOME_PREMIUM_N:
		case PRODUCT_ENTERPRISE:
		case PRODUCT_ENTERPRISE_N:
		case PRODUCT_BUSINESS:
		case PRODUCT_BUSINESS_N:
		case PRODUCT_ULTIMATE:
		case PRODUCT_ULTIMATE_N:
			fExpected = TRUE;
			LogTestInfoW(__FUNCTIONW__, L"Windows Media Connect in WMP is  expected here!");
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


		hr = (WOWFromPartialQueryId(STARTMENU_WINDOWS_MEDIA_PLAYER));

		if(FAILED(hr))
		{
			fFoundWMConnect = FALSE;
			
			if (fFoundWMConnect  != fExpected)
			{
				LogTestInfoW(__FUNCTIONW__,
				L"Windows Media Player- Enable Media Connect is SKU differentiation failed.[Current: %s | Expected: %s ]",
				fFoundWMConnect ? L"Found": L"Not Found",
				fExpected ? L"Found" : L"Not Found");		
			}
			else
			{
				fPassed = TRUE;
				pwszResultInfo = L"Windows Media Player - Enable Media Connect is differentiated correctly";
			}

			LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;
			
		}

	}

	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

	hr = (WOWFromPartialQueryId(WMP_FIRST_TIME_LAUNCH_EXPRESS_SETTING));

	if(SUCCEEDED(hr))
	{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

		hr = (WOWFromPartialQueryId(WMP_FIRST_TIME_LAUNCH_FINISH_BTN));

		if(SUCCEEDED(hr))
		{
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		}
		else
		{
			LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't Finish First Time setup of WMP successfully..");
			return NOERROR;			
		}
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__,L"Not a 1st time Lauch");
	}
	//Snooze();

	//hr= (WOWFromPartialQueryId(WMP_MENU_ITEM_TOOLS));
	//if( FAILED(hr))
	if(!IsAvailable(30000,WMP_MENU_ITEM_TOOLS)) //30 second time out used for First time setup
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Tools... in Windows Media Player (30 seconds)");
		return NOERROR;
	}
	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

	hr= (WOWFromPartialQueryId(WMP_TOOLS_OPTIONS));
	if( FAILED(hr))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Options... in Windows Media Player");
		return NOERROR;
	}
	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

	
	hr= (WOWFromPartialQueryId(OPTIONS_LIBRARY_TAB));
	if( FAILED(hr))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Library Tab... in Windows Media Player");
		return NOERROR;
	}
	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

	hr= (WOWFromPartialQueryId(OPTIONS_LIBRARY_CONFIGURE_SHARING));
	hr=LeftButtonClick(CLICKABLE_POINT);
	if( SUCCEEDED(hr))
	{
		fFoundWMConnect = TRUE;
	}
	else
	{
		fFoundWMConnect = FALSE;
	}
	//LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

	
	

	if (fFoundWMConnect  != fExpected)
	{
		LogTestInfoW(__FUNCTIONW__,
		L"Windows Media Player- Enable Media Connect is SKU differentiation failed.[Current: %s | Expected: %s ]",
		fFoundWMConnect ? L"Found": L"Not Found",
		fExpected ? L"Found" : L"Not Found");		
	}
	else
	{
		fPassed = TRUE;
		pwszResultInfo = L"Windows Media Player - Enable Media Connect is differentiated correctly";
	}



	LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");
	Snooze();

	hr = LOG_FAILED_HR(WOWFromPartialQueryId(CLOSE_MEDIA_SHARING));
	if (SUCCEEDED(hr))
	{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	}
	hr = LOG_FAILED_HR(WOWFromPartialQueryId(CLOSE_OPTIONS));
	if (SUCCEEDED(hr))
	{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	}
	hr = LOG_FAILED_HR(WOWFromPartialQueryId(CLOSE_WMP));
	if (SUCCEEDED(hr))
	{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	}
//SetSearchTimeOut(originalTimeout);

	LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
	return NOERROR;
}

