#include <windows.h>            //Common Windows types
//#include "rpf_constants.h"
#include "screenelement.h"  
#include "LoggingFunctions.h"
#include "rpf_SKUDIFF.h"
#include "SKUDIFF_UTIL.h"

using namespace RPFPlayback;
using namespace SKUDiff;

#include "Branding_BVT.h"

LanguageNeutralString langNeutralWinver(L"winver.exe");
LanguageNeutralString langNeutralWindows(L"Windows");
ComplexResourceKeyNative cmplxKeyAboutWindows(1, resKeyAbout, langNeutralWindows);


namespace Branding_BVT
{
	
	STDAPI InitTest(LPVOID)
	{
		HRESULT hr = SKUInitTest();
		//if SUCCEEDED(hr){CloseExcessWindows();}
		return hr;
	}

	STDAPI UnInitTest()
	{
		HRESULT hr = SKUUnInitTest();
		hr = RenameCacheToDAT();
		//CloseExcessWindows();
		return hr;
	}
	//    
	//    Verify BrandingWC_BVT_EntryPoints 
	//  
	STDAPI BrandingWC_BVT_EntryPoints(LPVOID pvReserved)
{
	BOOL fFoundUI = FALSE;
	LPWSTR pwszResultInfo = NULL;
	HRESULT hr;
	ScreenElement* pScreenElement;
	wchar_t* pszSkuName = L"";
	LogTestBeginW(__FUNCTIONW__, L"Verify Welcome Center Branding UI is differentiated correctly.");   

	DWORD dwProductInfoType = 0;
	if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
	{
		switch (dwProductInfoType)
		{
		case PRODUCT_ULTIMATE:
			pszSkuName = (wchar_t*)(WINDOWS_ULTIMATE);
			LogTestInfoW(__FUNCTIONW__,  L"Windows Vista ULTIMATE text expected here.");
			break;

		case PRODUCT_BUSINESS:
			pszSkuName = (wchar_t*)(WINDOWS_BUSINESS);
			LogTestInfoW(__FUNCTIONW__,  L"Windows Vista BUSINESS text expected here.");
			break;

		case PRODUCT_HOME_BASIC:
			pszSkuName = (wchar_t*)(WINDOWS_HOME_BASIC);
			LogTestInfoW(__FUNCTIONW__, L"Windows Vista HOME BASIC text expected here.");
			break;

		case PRODUCT_HOME_PREMIUM:
			pszSkuName = (wchar_t*)(WINDOWS_HOME_PREMIUM);
			LogTestInfoW(__FUNCTIONW__, L"Windows Vista HOME PREMIUM text expected here.");
			break;

		case PRODUCT_STARTER:
			pszSkuName = (wchar_t*)(WINDOWS_STARTER);
			LogTestInfoW(__FUNCTIONW__, L"Windows Vista STARTER text expected here.");
			break;

		case PRODUCT_ENTERPRISE:
			pszSkuName = (wchar_t*)(WINDOWS_ENTERPRISE);
			LogTestInfoW(__FUNCTIONW__, L"Windows Vista ENTERPRISE text expected here.");
			break;

		default:
			LogTestInfoW(__FUNCTIONW__, L"SKU not in the list, might be N SKU.");
			LogTestResultW(FALSE, __FUNCTIONW__, L"Could not set expectation.");
			return NOERROR;
			break;
		}
	}
	else
	{
		LogTestResultW(FALSE, __FUNCTIONW__, L"GetProductInfo failed.");
		return NOERROR;
	}

	if (FAILED(OpenWelcomeCenter()))
	{
		LogTestResultW(FALSE, __FUNCTIONW__, L"Could not open Welcome Center.");
		return NOERROR;
	}

	if(NULL == (pScreenElement = ScreenElement::FromPartialQueryId(WC_WINVER_SKU)))
	{
		LogTestResultW(FALSE, __FUNCTIONW__, L"Could not locate SKU name in UI.");
		return NOERROR;
	}

	if (pScreenElement->get_Name()[0] == L'[')
	{
		LogTestInfoW(__FUNCTIONW__, L"System appears to be Pseudo-localized.");
		LogTestResultW(TRUE, __FUNCTIONW__, L"Aborting as a Pass for known issue.");
		
		wchar_t szGlobalQuery[1024];
		GlobalizeQueryId(szGlobalQuery, 1024, CPL_WC_CLOSE_BTN);
		LeftClickUntilGone(szGlobalQuery);
			
		return NOERROR;
	}


	LogTestInfoW(__FUNCTIONW__, L"Comparing found name [%s] to hardcoded name [%s].",pScreenElement->get_Name(),pszSkuName);
	
	if (wcscmp(pScreenElement->get_Name(),pszSkuName) == 0)
	{
		LogTestResultW(TRUE, __FUNCTIONW__, L"Welcome Center Branding is differentiated correctly");
	}
	else
	{
		LogTestResultW(FALSE, __FUNCTIONW__, L"Welcome Center Branding is NOT differentiated correctly");
	}

	delete pScreenElement;

	LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");

	hr = LOG_FAILED_HR(FromPartialQueryId(CPL_WC_CLOSE_BTN));
	if (SUCCEEDED(hr))
	{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	}
	return NOERROR;
}


	//
	// Verify that correct bitmap image branding exists on the Windows Vista Logon Screen
	//
	STDAPI BrandingSysDM_BVT_EntryPoints(LPVOID pvReserved)
	{
		HRESULT hr;
		LPWSTR pwszResultInfo = NULL;
		BOOL fFoundUI = FALSE; 
		ScreenElement* pScreenElement;
		wchar_t* pszSkuName;
		//HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));

		LogTestBeginW(__FUNCTIONW__, L"Verify System Info branding is differentiated correctly (CPL).");    
		//int originalTimeout = SetSearchTimeOut(5000);
		if (SUCCEEDED(OpenStartMenu()))
		{
			//LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

			hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_COMPUTER));
			if (SUCCEEDED(hr))  
			{
				LOG_FAILED_HR(RightButtonClick(CLICKABLE_POINT));

				hr = LOG_FAILED_HR(FromPartialQueryId(SYS_COMP_PROPERTIES));

				if (SUCCEEDED(hr))  
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

					DWORD dwProductInfoType = 0;

					if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
					{
						switch (dwProductInfoType)
						{
						case PRODUCT_ULTIMATE:
							pszSkuName = (wchar_t*)(WINDOWS_ULTIMATE);
							pwszResultInfo = L"Windows Vista ULTIMATE text expected here.";
							break;

						case PRODUCT_BUSINESS:
							pszSkuName = (wchar_t*)(WINDOWS_BUSINESS);
							pwszResultInfo = L"Windows Vista BUSINESS text expected here.";
							break;

						case PRODUCT_HOME_BASIC:
							pszSkuName = (wchar_t*)(WINDOWS_HOME_BASIC);
							pwszResultInfo = L"Windows Vista HOME BASIC text expected here.";
							break;

						case PRODUCT_HOME_PREMIUM:
							pszSkuName = (wchar_t*)(WINDOWS_HOME_PREMIUM);
							pwszResultInfo = L"Windows Vista HOME PREMIUM text expected here.";
							break;
						
						case PRODUCT_STARTER:
							pszSkuName = (wchar_t*)(WINDOWS_STARTER);
							pwszResultInfo = L"Windows Vista STARTER text expected here.";
							break;

						case PRODUCT_ENTERPRISE:
							pszSkuName = (wchar_t*)(WINDOWS_ENTERPRISE);
							pwszResultInfo = L"Windows Vista ENTERPRISE text expected here.";
							break;


						default:
							LogTestInfoW(__FUNCTIONW__, L"Wrong branding or could not determine the SKU");
							pwszResultInfo = L"Could not verify behavior";
							break;
						}
						if(NULL != (pScreenElement = ScreenElement::FromPartialQueryId(SYSINFO_WINVER_SKU)))
						{	

							if (pScreenElement->get_Name()[0] == L'[')
							{
								LogTestInfoW(__FUNCTIONW__, L"System appears to be Pseudo-localized.");
								LogTestResultW(TRUE, __FUNCTIONW__, L"Aborting as a Pass for known issue.");
								
								wchar_t szGlobalQuery[1024];
								GlobalizeQueryId(szGlobalQuery, 1024, CPL_SYS_CLOSE_BTN);
								LeftClickUntilGone(szGlobalQuery);
								
								return NOERROR;
							}

							LogTestInfoW(__FUNCTIONW__, L"Comparing found name [%s] to hardcoded name [%s].",pScreenElement->get_Name(),pszSkuName);
							if (wcscmp(pScreenElement->get_Name(),pszSkuName) == 0)
							{
								LogTestInfoW(__FUNCTIONW__, L"Match.");
								fFoundUI = TRUE;
							}
							else
							{
								LogTestInfoW(__FUNCTIONW__, L"Did not match.");
								fFoundUI = FALSE;
							}
							delete pScreenElement;
						}
						else
						{
							LogTestInfoW(__FUNCTIONW__, L"Could not locate SKU name in UI.");
							fFoundUI = FALSE;
						}

						if (fFoundUI)
						{
							pwszResultInfo = L"System Info Branding is differentiated correctly.";
						}
					}
					else
					{
						LogTestInfoW(__FUNCTIONW__, L"GetProductInfo failed.");
						pwszResultInfo = L"GetProductInfo failed.";
					}
				}
			}

			LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");

			hr = LOG_FAILED_HR(FromPartialQueryId(CPL_SYS_CLOSE_BTN));
			if (SUCCEEDED(hr))
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
			}
		}
		LogTestResultW(fFoundUI, __FUNCTIONW__, pwszResultInfo);
		return NOERROR;
	}



STDAPI BrandingAboutWindows_BVT_EntryPoints(LPVOID pvReserved)
	{
		HRESULT hr;
		LPWSTR pwszResultInfo = NULL;
		BOOL fFoundUI = FALSE; 
		ScreenElement* pScreenElement;
		wchar_t* pszSkuName;
	
		LogTestBeginW(__FUNCTIONW__, L"Verify  branding is differentiated correctly in winver.exe (About Windows)");    
		ScreenElement* pScreenElement2;
		if(NULL != (pScreenElement2 = ScreenElement::FromPartialQueryId(WINDOW_DESKTOP)))
		{
			TypeString(L"`r");
			delete pScreenElement2;
		}

		ScreenElement* pScreenElement1;
		if(NULL != (pScreenElement1 = ScreenElement::FromPartialQueryId(RUN_DIALOG)))
		{

			wchar_t pszValueForlangNeutralWinver[1024];
			ExtractResourceString(langNeutralWinver, pszValueForlangNeutralWinver, ARRAYSIZE(pszValueForlangNeutralWinver));

			pScreenElement1->SetValueAsEditBox(pszValueForlangNeutralWinver);
			delete pScreenElement1;
		}

		hr = LOG_FAILED_HR(WOWFromPartialQueryId(RUN_DIALOG_OK_BTN));
				
				if (SUCCEEDED(hr))  
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

					DWORD dwProductInfoType = 0;

					if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
					{
						switch (dwProductInfoType)
						{
						case PRODUCT_ULTIMATE:
							pszSkuName = (wchar_t*)(WINDOWS_ULTIMATE);
							pwszResultInfo = L"Windows Vista ULTIMATE text expected here.";
							break;

						case PRODUCT_BUSINESS:
							pszSkuName = (wchar_t*)(WINDOWS_BUSINESS);
							pwszResultInfo = L"Windows Vista BUSINESS text expected here.";
							break;

						case PRODUCT_HOME_BASIC:
							pszSkuName = (wchar_t*)(WINDOWS_HOME_BASIC);
							pwszResultInfo = L"Windows Vista HOME BASIC text expected here.";
							break;

						case PRODUCT_HOME_PREMIUM:
							pszSkuName = (wchar_t*)(WINDOWS_HOME_PREMIUM);
							pwszResultInfo = L"Windows Vista HOME PREMIUM text expected here.";
							break;
						
						case PRODUCT_STARTER:
							pszSkuName = (wchar_t*)(WINDOWS_STARTER);
							pwszResultInfo = L"Windows Vista STARTER text expected here.";
							break;

						case PRODUCT_ENTERPRISE:
							pszSkuName = (wchar_t*)(WINDOWS_ENTERPRISE);
							pwszResultInfo = L"Windows Vista ENTERPRISE text expected here.";
							break;


						default:
							LogTestInfoW(__FUNCTIONW__, L"Wrong branding or could not determine the SKU");
							pwszResultInfo = L"Could not verify behavior";
							break;
						}
						if(NULL != (pScreenElement = ScreenElement::FromPartialQueryId(ABOUT_WINDOWS_SKU)))
						{	

							if (pScreenElement->get_Name()[0] == L'[')
							{
								LogTestInfoW(__FUNCTIONW__, L"System appears to be Pseudo-localized.");
								LogTestResultW(TRUE, __FUNCTIONW__, L"Aborting as a Pass for known issue.");
								
								wchar_t szGlobalQuery[1024];
								GlobalizeQueryId(szGlobalQuery, 1024, ABOUT_WINODWS_OK_BTN);
								LeftClickUntilGone(szGlobalQuery);
								
								return NOERROR;
							}
							
							LogTestInfoW(__FUNCTIONW__, L"Comparing found name [%s] to hardcoded name [%s].",pScreenElement->get_Name(),pszSkuName);
							wchar_t* pszSubStr;
							pszSubStr = wcsstr(pScreenElement->get_Name(),pszSkuName);
							if(pszSubStr!= NULL)
							{
								LogTestInfoW(__FUNCTIONW__, L"Match.");
								fFoundUI = TRUE;
							}
							else
							{
								LogTestInfoW(__FUNCTIONW__, L"Did not match.");
								fFoundUI = FALSE;
							}
							delete pScreenElement;
						}
						else
						{
							LogTestInfoW(__FUNCTIONW__, L"Could not locate SKU name in UI.");
							fFoundUI = FALSE;
						}

						if (fFoundUI)
						{
							pwszResultInfo = L"Branding is differentiated correctly in winver.exe (About Windows).";
						}
					}
					else
					{
						LogTestInfoW(__FUNCTIONW__, L"GetProductInfo failed.");
						pwszResultInfo = L"GetProductInfo failed.";
					}
			

			LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");

			hr = LOG_FAILED_HR(FromPartialQueryId(ABOUT_WINODWS_OK_BTN));
			if (SUCCEEDED(hr))
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
			}
		}
		LogTestResultW(fFoundUI, __FUNCTIONW__, pwszResultInfo);
		return NOERROR;
}
} // End namespace Branding_BVT

