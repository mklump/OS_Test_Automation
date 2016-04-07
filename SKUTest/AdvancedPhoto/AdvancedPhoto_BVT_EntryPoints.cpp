/// <copyright file="AdvancedPhoto_BVT_EntryPoints.cpp" company="Microsoft">
///  Copyright (c) Microsoft Corporation.  All rights reserved.
/// </copyright>
///
/// <summary>
///  Code for WTT WindowsShell, Job 368120
/// </summary>
///

// Complete Feb 2008, a-jomul

#include <windows.h>          //Common Windows types
#include "screenelement.h"    //RPF functions
#include "LoggingFunctions.h" //MASH logging functions
#include "rpf_SKUDIFF.h"      //RPF constants
#include "SKUDIFF_UTIL.h"     //Utility Functions

using namespace RPFPlayback;
using namespace SKUDiff;

// Ensure excess windows are closed; called before and after each test function by Inittest() and Uninittest()
void CloseExcessWindows()
{
	MultiLeftClickUntilGone(6,
		PHOTO_SCREEN_SAVER_THEME_CANCEL,
		SCREEN_SAVER_CANCEL,
		PHOTO_SCREEN_SAVER_THEME_CLOSE,
		SCREEN_SAVER_SETTINGS_CLOSE,
		CPL_PERSONALIZATION_CLOSE,
		CPL_CLOSE_BTN);
}

// Called by MASH before each test
STDAPI InitTest(LPVOID)
{
	HRESULT hr = SKUInitTest();
	if SUCCEEDED(hr){CloseExcessWindows();}
	return hr;
}

// Called by MASH after each test
STDAPI UnInitTest()
{
	CloseExcessWindows();
	return SKUUnInitTest();
}

/// <summary>
///  Check if selecting Photos by 'theme' is allowed in the Photos screen saver.
/// </summary>
/// <param name='pvReserved'>Unused.</param>

STDAPI AdvancedPhotoThemes(LPVOID pvReserved)
{
	BOOL fAdvancedPhotoThemesExpected = FALSE;
	BOOL fFoundAdvancedPhotoThemes = FALSE;
	BOOL fAdvancedPhotoThemesPassed = FALSE;
	HRESULT hr = E_FAIL;
	LanguageNeutralString langNeutralDV2ControlHost(L"DV2ControlHost");

	LPWSTR pwszResultInfo = L"Pre-test phase.";

	// Log the SKU name
	LogSKU();
	// Log WEI Scores
	Assessment();

	if(Get2DScore() < 3.0)
	{
		LogTestInfoW(__FUNCTIONW__, L"Test system has insufficent graphics support, test cannot continue.");
		LogTestResultW(fAdvancedPhotoThemesPassed, __FUNCTIONW__, pwszResultInfo);
		return NOERROR;			
	}
	LogTestBeginW(__FUNCTIONW__, L"Verify if Themes are available for the Photo Screensaver.");   

	// Indentify the current SKU
	pwszResultInfo = L"Set Expected state phase.";
	DWORD dwProductInfoType = 0;
	if (!GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
	{
		LogTestInfoW(__FUNCTIONW__, L"GetProductInfo API failed, test cannot continue.");
		LogTestResultW(fAdvancedPhotoThemesPassed, __FUNCTIONW__, pwszResultInfo);
		return NOERROR;			
	}

	switch (dwProductInfoType)
	{
	case PRODUCT_STARTER:
	case PRODUCT_HOME_BASIC:
	case PRODUCT_HOME_BASIC_N:
	case PRODUCT_BUSINESS:
	case PRODUCT_BUSINESS_N:
	case PRODUCT_ENTERPRISE:
	case PRODUCT_ENTERPRISE_N:
		LogTestInfoW(__FUNCTIONW__, L"Themes are not available for the Photo Screensaver on Basic and Business");
		fAdvancedPhotoThemesExpected = FALSE;
		break;
	case PRODUCT_HOME_PREMIUM:
	case PRODUCT_HOME_PREMIUM_N:
	case PRODUCT_ULTIMATE:
	case PRODUCT_ULTIMATE_N:
		LogTestInfoW(__FUNCTIONW__, L"Themes are available for the Photo Screensaver on Home Premium and Ultimate");
		fAdvancedPhotoThemesExpected = TRUE;
		break;
	default:
		pwszResultInfo = L"Could not determine the SKU, cannot set expectations.";
		LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU, cannot set expectations.");
		LogTestResultW(fAdvancedPhotoThemesPassed, __FUNCTIONW__, pwszResultInfo);
		return NOERROR;			
		break;
	}

	// Navigate to feature entry point
	pwszResultInfo = L"Navigate to feature entry point phase";

	if(FAILED(OpenSpecificControlPanel(CPL_LINK_APPEARANCEPERSONALIZATION, CPL_LINK_PERSONALIZATION)))
	{
		LogTestInfoW(__FUNCTIONW__, L"Something failed while opening Control Panel.");
		LogTestResultW(FALSE, __FUNCTIONW__, pwszResultInfo);
		return NOERROR;
	}

	LogTestInfoW(__FUNCTIONW__, L"Control Panel - Change Screen Saver...");
	hr = LOG_FAILED_HR(FromPartialQueryId(CPL_CHANGE_SCREEN_SAVER));
	if (!SUCCEEDED(hr))  
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not open Control Panel - Change Screen Saver.");
		LogTestResultW(FALSE, __FUNCTIONW__, pwszResultInfo);
		return NOERROR;
	}
	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

	//Select Photos saver
	LogTestInfoW(__FUNCTIONW__, L"Choose Photo saver...");

	// SetComboBoxValue - "combo box" named "Screen saver" in window "Screen Saver"
	ScreenElement* pScreenElement;
	if(NULL != (pScreenElement = ScreenElement::FromPartialQueryId(SCREEN_SAVER_SELECT)))
	{	
		wchar_t pszValueForresKeyPhotos[1024];
		ExtractResourceString(resKeyPhotoScreenSaver, pszValueForresKeyPhotos, ARRAYSIZE(pszValueForresKeyPhotos));
		pScreenElement->SetValueAsComboBox(pszValueForresKeyPhotos);
		delete pScreenElement;
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not select a Screen Saver.");
	}

	//open setting for photos saver
	// Left Button Click - "push button" named "Settings..." in window "Screen Saver"
	LogTestInfoW(__FUNCTIONW__, L"Screen Saver Settings...");
	hr = LOG_FAILED_HR(FromPartialQueryId(SCREEN_SAVER_SETTINGS));
	if (!SUCCEEDED(hr))  
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not open Screen Saver Settings.");

		LogTestResultW(FALSE, __FUNCTIONW__, pwszResultInfo);
		return NOERROR;
	}
	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

	// The actual check if themes are available.

	pwszResultInfo = L"Verification of feature phase.";
	fFoundAdvancedPhotoThemes =(SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(PHOTO_SCREEN_SAVER_THEME_LABEL))));
	if (fFoundAdvancedPhotoThemes != fAdvancedPhotoThemesExpected)
	{
		fAdvancedPhotoThemesPassed = FALSE;
	}
	else
	{
		fAdvancedPhotoThemesPassed = TRUE;
	}

	// Log the test result.

	pwszResultInfo = L"Result Reporting Phase.";
	LogTestInfoW(__FUNCTIONW__, L"SKU differentiation of Advanced Photography feature, Result is PASSED.[Current: %s | Expected: %s ]",
		fAdvancedPhotoThemesPassed ? L"PASSED": L"FAILED",
		fFoundAdvancedPhotoThemes ? L"Found": L"Not Found",
		fAdvancedPhotoThemesExpected ? L"Found" : L"Not Found");


	LogTestResultW(fAdvancedPhotoThemesPassed, __FUNCTIONW__, pwszResultInfo);
	return NOERROR;
}

// Dead code, kept for referance.

/*
BOOL fAdvancedPhotoQueryTagExpected = FALSE;
BOOL fAdvancedPhotoQueryRatingExpected = FALSE;
BOOL fAdvancedPhotoQueryTagPassed = FALSE;
BOOL fAdvancedPhotoQueryRatingPassed = FALSE;

wchar_t szGlobalQuery[1024];
GlobalizeQueryId(szGlobalQuery, 1024, PHOTO_SCREEN_SAVER_THEME_CANCEL);
LeftClickUntilGone(szGlobalQuery);
GlobalizeQueryId(szGlobalQuery, 1024, SCREEN_SAVER_CANCEL);
LeftClickUntilGone(szGlobalQuery);
GlobalizeQueryId(szGlobalQuery, 1024, PHOTO_SCREEN_SAVER_THEME_CLOSE);
LeftClickUntilGone(szGlobalQuery);
GlobalizeQueryId(szGlobalQuery, 1024, SCREEN_SAVER_SETTINGS_CLOSE);
LeftClickUntilGone(szGlobalQuery);
GlobalizeQueryId(szGlobalQuery, 1024, CPL_PERSONALIZATION_CLOSE);
LeftClickUntilGone(szGlobalQuery);
GlobalizeQueryId(szGlobalQuery, 1024, CPL_CLOSE_BTN);
LeftClickUntilGone(szGlobalQuery);
*/
//fAdvancedPhotoQueryTagExpected = FALSE;
//fAdvancedPhotoQueryRatingExpected = FALSE;
//fAdvancedPhotoQueryTagExpected = TRUE;
//fAdvancedPhotoQueryRatingExpected = TRUE;
/*
wchar_t Section[1024];
wchar_t Link[1024];	
if (FAILED(GlobalizeQueryId(Section, 1024, CPL_LINK_APPEARANCEPERSONALIZATION)) ||
FAILED(GlobalizeQueryId(Link, 1024, CPL_LINK_PERSONALIZATION)))
{
LogTestInfoW(__FUNCTIONW__, L"Something failed while resolving Control Panel resKeys.");
LogTestResultW(FALSE, __FUNCTIONW__, pwszResultInfo);
return NOERROR;
}
if(FAILED(OpenSpecificHomeControlPanel(Section, Link)))
*/			
/*
LogTestInfoW(__FUNCTIONW__,
L"SKU differentiation of Advanced Photography feature, Result is FAILED.[Current: %s | Expected: %s ]",
fFoundAdvancedPhotoThemes ? L"Found": L"Not Found",
fAdvancedPhotoThemesExpected ? L"Found" : L"Not Found");
*/