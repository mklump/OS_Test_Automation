#include <windows.h>            //Common Windows types
#include "screenelement.h"             //RPF
//#include "rpf_constants.h"
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
//    Verify MUI_BVT_EntryPoints 
//  
STDAPI MUI_BVT_EntryPoints(LPVOID pvReserved)
{
	BOOL    fPassed = FALSE;
	LPWSTR pwszResultInfo = NULL;
	HRESULT hr = E_FAIL;
	BOOL fExpected = FALSE;
	
	LogTestBeginW(__FUNCTIONW__, L"Verify MUI UI is differentiated correctly (CPL).");    

	//	
	// Get SKU information, to set expectations.
	//

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
		case PRODUCT_BUSINESS:
		case PRODUCT_BUSINESS_N:
		case PRODUCT_ENTERPRISE_N: //Only Korean, so no MUI
		case PRODUCT_ULTIMATE_N: //Only Korean, so no MUI

			LogTestInfoW(__FUNCTIONW__, L"Manage Languages button not expected here!");
			break;
		case PRODUCT_ENTERPRISE:
		case PRODUCT_ULTIMATE:
			fExpected = TRUE;
			LogTestInfoW(__FUNCTIONW__, L"Manage Languages button expected here!");
			//pwszResultInfo = L"Manage Languages button expected here.";
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
		LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
		return(NOERROR);
	}



	if (SUCCEEDED(FromPartialQueryId(MUI_KEYBOARDSLANGUAGES_TAB)))
		{
			LogTestInfoW(__FUNCTIONW__, L"Regional and Language Options tab was already open! attempting to close...");
			LeftButtonClick(CLICKABLE_POINT);
			TypeString(L"{ESC}");
		}

	//
	// Open the Regional and Language options control panel.
	//
	wchar_t Section[1024];
	wchar_t Link[1024];	
	if (SUCCEEDED(GlobalizeQueryId(Section, 1024, CPL_LINK_CLOCKLANGUAGEREGION)) &&
		SUCCEEDED(GlobalizeQueryId(Link, 1024, CPL_LINK_REGIONALLANGUAGEOPTIONS)) &&
		SUCCEEDED(OpenSpecificHomeControlPanel(Section, Link)))
	{

		//
		//find the Tab that may contain MUI settings
		//
		
		ScreenElement* pScreenElement;
		if(NULL != (pScreenElement = ScreenElement::FromPartialQueryId(MUI_MANAGE_LANGUAGES_BTN)))
		{
		pScreenElement->WaitForReady();
		delete pScreenElement;
		}
		
		
		if (FAILED(LOG_FAILED_HR(FromPartialQueryId(MUI_KEYBOARDSLANGUAGES_TAB))))
		{
			LogTestInfoW(__FUNCTIONW__, L"Failed to locate Keyboards and Languages tab.");
			return(NOERROR);
		}

		
		if (FAILED(LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT))))
		{
			LogTestInfoW(__FUNCTIONW__, L"Failed to click Keyboards and Languages tab.");
			return(NOERROR);
		}
		
		if (FAILED(LOG_FAILED_HR(FromPartialQueryId(MUI_KEYBOARDSLANGUAGES_TAB))))
		{
			LogTestInfoW(__FUNCTIONW__, L"Failed to locate Keyboards and Languages tab.");
			return(NOERROR);
		}

		
		if (FAILED(LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT))))
		{
			LogTestInfoW(__FUNCTIONW__, L"Failed to click Keyboards and Languages tab.");
			return(NOERROR);
		}
		
		
		//
		//find the Manage Languages Button
		//

		if(NULL != (pScreenElement = ScreenElement::FromPartialQueryId(MUI_MANAGE_LANGUAGES_BTN)))
		{
			LogTestInfoW(__FUNCTIONW__, L"[MUI_MANAGE_LANGUAGES_BTN] found a button named [%s]",pScreenElement->get_Name());
		
			delete pScreenElement;
		}


		BOOL fFoundUI = SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(MUI_MANAGE_LANGUAGES_BTN)));

		BOOL fFoundClickablePoint = TRUE;

/* This code seems pointless.
		if (fFoundUI)
		{
			int x, y;
			fFoundClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));
			LogTestInfoW(__FUNCTIONW__,
				L"%s Clickable point", fFoundClickablePoint ? L"Found": L"Did not find");
		}
*/

		if ((fFoundUI && fFoundClickablePoint) != fExpected)
		{
			LogTestInfoW(__FUNCTIONW__,
				L"MUI UI SKU differentiation failed.[Current: %s | Expected: %s ]",
				fFoundUI ? L"Found": L"Not Found",
				fExpected ? L"Found" : L"Not Found");
		}
		else
		{
			fPassed = TRUE;
			pwszResultInfo = L"MUI CPL entry point is differentiated correctly";
		}

//
// Test is done, cleanup phase.
//


		LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");

		if (SUCCEEDED(FromPartialQueryId(MUI_KEYBOARDSLANGUAGES_TAB)))
		{
			LeftButtonClick(CLICKABLE_POINT);
			TypeString(L"{ESC}");
		}

		hr = LOG_FAILED_HR(FromPartialQueryId(CPL_CLOSE_BTN));
		if (SUCCEEDED(hr))
		{
			LeftButtonClick(CLICKABLE_POINT);
		}
	}
	LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
	return NOERROR;


}




