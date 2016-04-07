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
	//if (SUCCEEDED(hr)){}
	return hr;
}

STDAPI UnInitTest()
{
	return SKUUnInitTest();
}

//    
//    Verify Classic Start Menu Items
//  
STDAPI VerifyStartMenu_EntryPoint(LPVOID pvReserved)
{
	LPWSTR pwszResultInfo = NULL;
	BOOL    fPassed = FALSE;
	wchar_t szGlobalQuery[1024];

	BOOL fExpected = FALSE;
	BOOL fGamesExpected = FALSE;
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
		case PRODUCT_ULTIMATE:
		case PRODUCT_ULTIMATE_N:
			fGamesExpected = TRUE;
			fExpected = TRUE;
			LogTestInfoW(__FUNCTIONW__, L"Start Menu expected here!");
			break;
		case PRODUCT_ENTERPRISE:
		case PRODUCT_ENTERPRISE_N:
		case PRODUCT_BUSINESS:
		case PRODUCT_BUSINESS_N:
			fGamesExpected = FALSE;
			fExpected = TRUE;
			LogTestInfoW(__FUNCTIONW__, L"Start Menu expected here!");
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
	
	//GlobalizeQueryId(szGlobalQuery, 1024, STARTMENU_PROPERTIES_CLASSICMENU);
	 
	//Verify elements in Classic Start Menu

	if(!IsAvailable(10000, START_BUTTON))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find start button");
		return NOERROR;
	}
	
	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

	if(! IsAvailable(10000,STARTMENU_INTERNET))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Default Programs in Start Menu classic view");
		return NOERROR;
	}
	
	//GlobalizeQueryId(szGlobalQuery, 1024, );
	
	/*if(FAILED(LOG_FAILED_HR(WOWFromPartialQueryId(STARTMENU_CLASSIC_WINDOWS_UPDATE))))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Windows Update in Start Menu classic view");	
		return NOERROR;
	}*/
	 
		
	if (!IsAvailable(10000,STARTMENU_EMAIL))
	{
		//LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Windows Update in Start Menu classic view");	
		//return NOERROR;
	}

	if(! IsAvailable(10000,STARTMENU_DOCUMENTS))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Documents in Start Menu classic view ");
		return NOERROR;
	}
	//LOG_FAILED_HR(RightButtonClick(CLICKABLE_POINT));

	if(! IsAvailable(10000,STARTMENU_PICTURES))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Pictures in Start Menu classic view");
		return NOERROR;
	}

	

	if(! IsAvailable(10000,STARTMENU_MUSIC))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Music in Start Menu classic view");
		return NOERROR;
	}

	//LOG_FAILED_HR(RightButtonClick(CLICKABLE_POINT));
	
	if(! IsAvailable(10000,STARTMENU_GAMES))
	{
		if(fGamesExpected)
		{
			LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Games in Start Menu classic view");
			return NOERROR;	
		}
	}

	
	if(! IsAvailable(10000,STARTMENU_RECENT_ITEMS))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Recent Items in Start Menu classic view");
		return NOERROR;
	}

	if(! IsAvailable(10000,STARTMENU_COMPUTER))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Computer in Start Menu classic view");
		return NOERROR;
	}

	if(! IsAvailable(10000,STARTMENU_NETWORK))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Network in Start Menu classic view");
		return NOERROR;
	}

	if(! IsAvailable(10000,STARTMENU_CONNECT_TO))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Connect To in Start Menu classic view");
		return NOERROR;
	}

	if(! IsAvailable(10000,STARTMENU_CONTROL_PANEL))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Control Panel in Start Menu classic view");
		return NOERROR;
	}

	if(! IsAvailable(10000,STARTMENU_DEFAULT_PROGRAMS))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Default Program in Start Menu classic view");
		return NOERROR;
	}
	if(! IsAvailable(10000,STARTMENU_HELP_AND_SUPPORT))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't find Help And Support in Start Menu classic view");
		return NOERROR;
	}


	
 
	
	fPassed =TRUE;

	LogTestResultW(fPassed, __FUNCTIONW__,L"Start Menu view is verified correctly");
	return NOERROR;
	
}










