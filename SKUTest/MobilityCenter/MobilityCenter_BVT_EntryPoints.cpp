/*********************************************************
// Description: BVT - Mobility Center entry point in SKUs
// Created:     HariniD
// Verify:      Pass test case if feature is available
//              in all SKUs but Starter
**********************************************************/

#include <windows.h>
//#include <stdio.h>
//#include "rpf_constants.h"
#include "screenelement.h"
#include "LoggingFunctions.h"
#include "rpf_skudiff.h" // SKU Diff Contants
#include "SKUDIFF_UTIL.h"



using namespace RPFPlayback;
using namespace SKUDiff;

LanguageNeutralString langNeutralMobilityCenter(L"mblctr.exe");


//#define MOBILITY_CENTER_NOT_FOUND_OK			L";Name => '{0}' && ClassName => '#32770';[VisibleOnly]Name = '{0}' && Role = 'pane';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyWindowsMobilityCenterNotFound, resKeyOK
//#define MOBILITY_CENTER_NOT_FOUND_OK			L";Name => '{0}' && ClassName => '#32770';Role = 'push button'", resKeyWindowsMobilityCenterNotFound //[VisibleOnly]Name = '{0}' && Role = 'pane';[VisibleOnly]Name = '{1}' && Role = 'push button', resKeyOk
//const wchar_t* resKeyWindowsMobilityCenterNotFound = L"RKB1[mblctr];WindowS MobilitY Center;Win32String;%windir%\\system32\\mblctr.exe;1006";
//const wchar_t* resKeyOK = L"RKB1[mblctr];OK;Win32String;%windir%\\system32\\comctl32.dll;4240";




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

// Verify Mobility Center cpl in SKUs
STDAPI MobilityCenterEntryPoints(LPVOID pvReserved)
{

	BOOL fPassed = FALSE;
	LPWSTR pwszResultInfo = NULL;
	HRESULT hr;
	LogTestBeginW(__FUNCTIONW__, L"Beginning Mobility Center BVT test case...");
	
	BOOL fExpected = FALSE;
	BOOL fFoundMobilityCenter= FALSE;

	DWORD dwProductInfoType = 0;
	if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
	{
       	switch (dwProductInfoType)
    	{	
			case PRODUCT_STARTER:
				fExpected = FALSE;
				pwszResultInfo = L"Mobility Center is not expected here.";
			    break;
			case PRODUCT_HOME_BASIC_N:
			case PRODUCT_HOME_PREMIUM_N:    		
			case PRODUCT_HOME_PREMIUM:
			case PRODUCT_HOME_BASIC:
			case PRODUCT_BUSINESS_N:
			case PRODUCT_BUSINESS:
			case PRODUCT_ENTERPRISE_N:
			case PRODUCT_ENTERPRISE:
			case PRODUCT_ULTIMATE_N:
			case PRODUCT_ULTIMATE:
				fExpected = TRUE;
				pwszResultInfo = L"Mobility Center is expected here.";
				break;
			default:
			LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
			pwszResultInfo = L"Could not verify behavior";
           					 break;
       	 }
	}


	if (SUCCEEDED(OpenStartMenu()))
	{

		ScreenElement* pScreenElement;
		if(NULL != (pScreenElement = ScreenElement::FromPartialQueryId(WINDOW_DESKTOP))) 
		{
			TypeString(L"`r");
			delete pScreenElement;
		}

		ScreenElement* pScreenElement1;
		if(NULL != (pScreenElement1 = ScreenElement::FromPartialQueryId(RUN_DIALOG))) 
		{

			wchar_t pszValueForlangNeutralMobilityCenter[1024];
			ExtractResourceString(langNeutralMobilityCenter, pszValueForlangNeutralMobilityCenter, ARRAYSIZE(pszValueForlangNeutralMobilityCenter));

			pScreenElement1->SetValueAsEditBox(pszValueForlangNeutralMobilityCenter);
			delete pScreenElement1;
		}

		
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(RUN_DIALOG_OK_BTN)); 
   		if (SUCCEEDED(hr))  
    	{
       		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		}
			
		//hr = LOG_FAILED_HR(WOWFromPartialQueryId(MOBILITY_CENTER_TITLE_BAR)); 
   		if (IsAvailable(10000,MOBILITY_CENTER_TITLE_BAR)) 
    	{
       		LogTestInfoW(__FUNCTIONW__, L"Found Mobility Center");
			fFoundMobilityCenter = TRUE;
		}
		else
		{
			LogTestInfoW(__FUNCTIONW__, L"Didn't find Mobility Center");
			fFoundMobilityCenter = FALSE;
			// more reliable than trying to hit Cancel for some reason.
			TypeString(L"{ESC}"); // closes any error dialog which opens up
			TypeString(L"{ESC}"); // closes the Run dialog box which opens up again
		}
			
		if (fFoundMobilityCenter!= fExpected)
		{
			LogTestInfoW(__FUNCTIONW__, 
			L" Mobility Center - SKU differentiation failed.[Current: %s | Expected: %s ]",
			fFoundMobilityCenter ? L"Found": L"Not Found",
			fExpected ? L"Found" : L"Not Found");
			pwszResultInfo = L"Mobility Center entry point is NOT differentiated correctly";
		}
		else
		{
			fPassed = TRUE;
			pwszResultInfo = L" Mobility Center entry point is differentiated correctly";
		}
		
	
		
   		if (IsAvailable(10000,MOBILITY_CENTER_CLOSE))  
    	{
       		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		}

		/*hr = LOG_FAILED_HR(WOWFromPartialQueryId(MOBILITY_CENTER_NOT_FOUND_OK)); 
   		if (SUCCEEDED(hr))  
    	{
       		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
			LogTestInfoW(__FUNCTIONW__, L"Test case failure may be due to some error in setting the registry keys");
		}*/

	}	

	LogTestResultW(fPassed, __FUNCTIONW__,pwszResultInfo);
	return NOERROR;
}


