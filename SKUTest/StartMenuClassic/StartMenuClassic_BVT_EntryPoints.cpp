#include <windows.h>            //Common Windows types
//#include "rpf_constants.h"
#include "screenelement.h"             //RPF
#include "LoggingFunctions.h"
#include "rpf_skudiff.h" // SKU Diff Contants
#include "SKUDIFF_UTIL.h"

using namespace RPFPlayback;
using namespace SKUDiff;


LPWSTR pwszResultInfo = NULL;
BOOL    fPassed = FALSE;
wchar_t szGlobalQuery[1024];

bool ChangeStartMenuProperty(wchar_t* radioType,wchar_t* pszQueryID, ...)
{
	
	if(! IsAvailable(10000, START_BUTTON))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find start button");
		return NOERROR;
	}
	
	LOG_FAILED_HR(RightButtonClick(CLICKABLE_POINT));

	
	if( ! IsAvailable(10000, STARTMENU_PROPERTIES))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Propertis for Start button");
		return NOERROR;
	}

	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
;
	if(! IsAvailable(1000,pszQueryID))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find {0} Radio Button",radioType);
		return NOERROR;
	}

	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

	if(!IsAvailable(1000, TASKBAR_STARTMENU_OK))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find OK button in Taskbar and start menu");
		return NOERROR;
	}

	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

	return true;


}

STDAPI InitTest(LPVOID)
{
	HRESULT hr = SKUInitTest();
	if (SUCCEEDED(hr))
	{
		GlobalizeQueryId(szGlobalQuery, 1024,STARTMENU_PROPERTIES_STARTMENU);
		ChangeStartMenuProperty(L"Start Menu",szGlobalQuery);
	}
	return hr;
}

STDAPI UnInitTest()
{
	GlobalizeQueryId(szGlobalQuery, 1024,STARTMENU_PROPERTIES_STARTMENU);
	ChangeStartMenuProperty(L"Start Menu",szGlobalQuery);
	return SKUUnInitTest();
}

//    
//    Verify Classic Start Menu Items
//  
STDAPI VerifyStartMenuClassic_EntryPoint(LPVOID pvReserved)
{
//	BOOL    fPassed = FALSE;
//	LPWSTR pwszResultInfo = NULL;

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
		case PRODUCT_HOME_PREMIUM:
		case PRODUCT_HOME_PREMIUM_N:
		case PRODUCT_ENTERPRISE:
		case PRODUCT_ENTERPRISE_N:
		case PRODUCT_BUSINESS:
		case PRODUCT_BUSINESS_N:
		case PRODUCT_ULTIMATE:
		case PRODUCT_ULTIMATE_N:
			fExpected = TRUE;
			LogTestInfoW(__FUNCTIONW__, L"Classic Menu expected here!");
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
	
	GlobalizeQueryId(szGlobalQuery, 1024, STARTMENU_PROPERTIES_CLASSICMENU);
	if(ChangeStartMenuProperty(L"Classic Menu",szGlobalQuery))
	{
		LogTestInfoW(__FUNCTIONW__, L"Start Menu Changed to classic view");
	}
	else
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Could not set to classic view");
		return NOERROR;
	}

 
	//Verify elements in Classic Start Menu

	if(!IsAvailable(10000, START_BUTTON))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find start button");
		return NOERROR;
	}
	
	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

	if(! IsAvailable(10000,STARTMENU_CLASSIC_DEFAULT_PROGRAMS))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Default Programs in Start Menu classic view");
		return NOERROR;
	}
	
	//GlobalizeQueryId(szGlobalQuery, 1024, );
	
	if(FAILED(LOG_FAILED_HR(WOWFromPartialQueryId(STARTMENU_CLASSIC_WINDOWS_UPDATE))))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Windows Update in Start Menu classic view");	
		return NOERROR;
	}
	 
		
	/*if (!IsAvailable(10000,STARTMENU_CLASSIC_WINDOWS_UPDATE))
	{
		//LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Windows Update in Start Menu classic view");	
		//return NOERROR;
	}*/

	if(! IsAvailable(10000,STARTMENU_CLASSIC_PROGRAMS))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Programs in Start Menu classic view ");
		return NOERROR;
	}
	//LOG_FAILED_HR(RightButtonClick(CLICKABLE_POINT));

	if(! IsAvailable(10000,STARTMENU_CLASSIC_DOCUMENTS))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Documents in Start Menu classic view");
		return NOERROR;
	}

	

	if(! IsAvailable(10000,STARTMENU_CLASSIC_SETTINGS))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Settings in Start Menu classic view");
		return NOERROR;
	}

	//LOG_FAILED_HR(RightButtonClick(CLICKABLE_POINT));
	
	if(! IsAvailable(10000,STARTMENU_CLASSIC_SEARCH))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Search  in Start Menu classic view");
		return NOERROR;
	}

	
	if(! IsAvailable(10000,STARTMENU_CLASSIC_HELP_AND_SUPPORT))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Help and Support in Start Menu classic view");
		return NOERROR;
	}

	if(! IsAvailable(10000,STARTMENU_CLASSIC_RUN))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Run in Start Menu classic view");
		return NOERROR;
	}

	
 
	GlobalizeQueryId(szGlobalQuery, 1024, STARTMENU_PROPERTIES_STARTMENU);
	if(ChangeStartMenuProperty(L"Start Menu",szGlobalQuery))
	{
		LogTestInfoW(__FUNCTIONW__, L"Start Menu Changed to Normal View");
	}
	else
	{
		return NOERROR;
	}
	
	fPassed =TRUE;

	LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
	return NOERROR;
	
}










