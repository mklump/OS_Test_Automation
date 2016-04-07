#include <windows.h>            //Common Windows types
//#include "rpf_constants.h"
#include "screenelement.h"             //RPF
#include "LoggingFunctions.h"
#include "rpf_SKUDIFF.h"
#include "SKUDIFF_UTIL.h"



using namespace RPFPlayback;
using namespace SKUDiff;


void CloseExcessWindows() // test specific, ensure a clean state; can be made better with RPF 12+
{
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

}

STDAPI InitTest(LPVOID)
{
	HRESULT hr = SKUInitTest();
	if SUCCEEDED(hr){CloseExcessWindows();}
	return hr;
}

STDAPI UnInitTest()
{
	CloseExcessWindows();
	return SKUUnInitTest();
}



STDAPI PhotoScreenSaverSettingsScopeandRating(LPVOID pvReserved)
{

	BOOL fPhotoScreenSaverSettingsScopeExpected = FALSE;
	BOOL fPhotoScreenSaverSettingsScopePassed = FALSE;
	BOOL fFoundPhotoScreenSaverSettingsScope = FALSE;

	BOOL fPhotoScreenSaverSettingsRatingExpected = FALSE;
	BOOL fPhotoScreenSaverSettingsRatingPassed = FALSE;
	BOOL fFoundPhotoScreenSaverSettingsRating = FALSE;


	BOOL fFoundALLPictureAndVideoOption = FALSE;
	BOOL fFoundHigherRating = FALSE;

	LPWSTR pwszResultInfo_Scope = NULL;
	LPWSTR pwszResultInfo_Rating = NULL;

	HRESULT hr = E_FAIL;

	LanguageNeutralString langNeutralDV2ControlHost(L"DV2ControlHost");

	if(Get2DScore() < 3.0)
	{
		LogTestInfoW(__FUNCTIONW__, L"Test system has insufficent graphics support, test cannot continue.");
		return E_FAIL;			
	}
	LogTestBeginW(__FUNCTIONW__, L"Verify if Themes are available for the Photo Screensaver.");   
	
	// Log the SKU name
	LogSKU();
	// Log WEI Scores
	Assessment();
	// Indentify the current SKU
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
			LogTestInfoW(__FUNCTIONW__, L"Themes are not available for the Photo Screensaver on Basic and Business");
			pwszResultInfo_Scope = L"Use all pictures and videos from Photo Gallery is not expected here.";
			pwszResultInfo_Rating = L"With this rating or higher is not expected here";
			fPhotoScreenSaverSettingsScopeExpected = FALSE;
			fPhotoScreenSaverSettingsRatingExpected = FALSE;
			break;
		case PRODUCT_HOME_PREMIUM:
		case PRODUCT_HOME_PREMIUM_N:
		case PRODUCT_ULTIMATE:
		case PRODUCT_ULTIMATE_N:
			LogTestInfoW(__FUNCTIONW__, L"Themes are available for the Photo Screensaver on Home Premium and Ultimate");
			pwszResultInfo_Scope = L"Use all pictures and videos from Photo Gallery is expected here.";
			pwszResultInfo_Rating = L"With this rating or higher is expected here";
			fPhotoScreenSaverSettingsScopeExpected = TRUE;
			fPhotoScreenSaverSettingsRatingExpected = TRUE;
			break;
		default:
			pwszResultInfo_Scope = L"Could not determine the SKU, cannot set expectations.";
			LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU, cannot set expectations.");
			break;
		}
		wchar_t Section[1024];
		wchar_t Link[1024];	
		if (FAILED(GlobalizeQueryId(Section, 1024, CPL_LINK_APPEARANCEPERSONALIZATION)) ||
			FAILED(GlobalizeQueryId(Link, 1024, CPL_LINK_PERSONALIZATION)))
		{
			LogTestInfoW(__FUNCTIONW__, L"Something failed while resolving Control Panel resKeys.");
			pwszResultInfo_Scope = L"Something failed while resolving Control Panel resKeys.";
			LogTestResultW(FALSE, __FUNCTIONW__, pwszResultInfo_Scope);
			return NOERROR;
		}
		if(FAILED(OpenSpecificHomeControlPanel(Section, Link)))
		{
			LogTestInfoW(__FUNCTIONW__, L"Something failed while opening Control Panel.");
			pwszResultInfo_Scope = L"Something failed while opening Control Panel.";
			LogTestResultW(FALSE, __FUNCTIONW__, pwszResultInfo_Scope);
			return NOERROR;
		}
		
		LogTestInfoW(__FUNCTIONW__, L"Control Panel - Change Screen Saver...");
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(CPL_CHANGE_SCREEN_SAVER));
		if (!SUCCEEDED(hr))  
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not open Control Panel - Change Screen Saver.");
			pwszResultInfo_Scope = L"Could not open Control Panel - Change Screen Saver.";
			LogTestResultW(FALSE, __FUNCTIONW__, pwszResultInfo_Scope);
			return NOERROR;
		}
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

		//Select Photos saver
		LogTestInfoW(__FUNCTIONW__, L"Choose Photo saver...");

		// SetComboBoxValue - "combo box" named "Screen saver" in window "Screen Saver"
		ScreenElement* pScreenElement1;
		if(NULL != (pScreenElement1 = ScreenElement::FromPartialQueryId(SCREEN_SAVER_SELECT)))
		{	
			wchar_t pszValueForresKeyPhotos[1024];
			ExtractResourceString(resKeyPhotoScreenSaver, pszValueForresKeyPhotos, ARRAYSIZE(pszValueForresKeyPhotos));
			pScreenElement1->SetValueAsComboBox(pszValueForresKeyPhotos);
			delete pScreenElement1;
		}
		else
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not select a Screen Saver.");
			pwszResultInfo_Scope = L"Could not select a Screen Saver.";
		}

		//open setting for photos saver
		// Left Button Click - "push button" named "Settings..." in window "Screen Saver"
		LogTestInfoW(__FUNCTIONW__, L"Screen Saver Settings...");
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(SCREEN_SAVER_SETTINGS));
		if (!SUCCEEDED(hr))  
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not open Screen Saver Settings.");
			pwszResultInfo_Scope = L"Could not open Screen Saver Settings.";
			LogTestResultW(FALSE, __FUNCTIONW__, pwszResultInfo_Scope);
			return NOERROR;
		}
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		
	}
	// If any important element reported a failure, the test as a whole is failed.

	
	hr = LOG_FAILED_HR(WOWFromPartialQueryId(SCREEN_SAVER_ALL_PICTURE_AND_VIDEOS));
	
	if(SUCCEEDED(hr)) // all picture and videos option is avaialable
	{
		fFoundALLPictureAndVideoOption= TRUE;
	}
	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

	if (fFoundALLPictureAndVideoOption != fPhotoScreenSaverSettingsScopeExpected)
	{
		fPhotoScreenSaverSettingsScopePassed = FALSE;
		fPhotoScreenSaverSettingsRatingPassed = FALSE;// Rating combo box is only present if the option for "all picture and video..." is there.
		LogTestInfoW(__FUNCTIONW__,
			L"ADV Photo UI for 'ALL PICTURE AND VIDEO....' and 'WITH HIGHER RATING...' - SKU differentiation failed.[Current: %s | Expected: %s ]",//
			fFoundPhotoScreenSaverSettingsScope ? L"Found": L"Not Found",
			fPhotoScreenSaverSettingsScopeExpected ? L"Found" : L"Not Found");
		LogTestResultW(fPhotoScreenSaverSettingsScopePassed, __FUNCTIONW__, pwszResultInfo_Scope);
		LogTestResultW(fPhotoScreenSaverSettingsRatingPassed, __FUNCTIONW__, pwszResultInfo_Rating);
		return NOERROR;
	}
	else
	{
		fPhotoScreenSaverSettingsScopePassed = TRUE; 
		LogTestInfoW(__FUNCTIONW__, L"ADV Photo UI for 'ALL PICTURE AND VIDEO....' is differentiated correctly.");
		LogTestResultW(fPhotoScreenSaverSettingsScopePassed, __FUNCTIONW__, pwszResultInfo_Scope);
	}
	//Since "all picture and videos.... option was found we continue to check for "With this rating or Higher" 
	// To check for "With this rating or Higher" Combo Box we look for the corresponding label.

	hr = LOG_FAILED_HR(WOWFromPartialQueryId(SCREEN_SAVER_HIGHER_RATING_LABEL));
	//LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	if (SUCCEEDED(hr))  
	{
		fFoundHigherRating = TRUE;
		LogTestInfoW(__FUNCTIONW__, L"Found the Label");
	}
	else
	{
		fFoundHigherRating = FALSE;
	}
	
	if (fFoundHigherRating != fPhotoScreenSaverSettingsRatingExpected)
	{
		fPhotoScreenSaverSettingsRatingPassed = FALSE;
		LogTestInfoW(__FUNCTIONW__,
			L"ADV Photo UI for  'WITH HIGHER RATING...' - SKU differentiation failed.[Current: %s | Expected: %s ]",
			fFoundPhotoScreenSaverSettingsRating ? L"Found": L"Not Found",
			fPhotoScreenSaverSettingsRatingExpected ? L"Found" : L"Not Found");
		LogTestResultW(fPhotoScreenSaverSettingsRatingPassed, __FUNCTIONW__, pwszResultInfo_Rating);
		return NOERROR;
	}
	else
	{
		fPhotoScreenSaverSettingsRatingPassed = TRUE;
		LogTestInfoW(__FUNCTIONW__, L"ADV Photo UI for 'WITH HIGHER RATING....' is differentiated correctly.");
	}
	
	
	LogTestResultW(fPhotoScreenSaverSettingsRatingPassed, __FUNCTIONW__, pwszResultInfo_Rating);
	return NOERROR;
}



