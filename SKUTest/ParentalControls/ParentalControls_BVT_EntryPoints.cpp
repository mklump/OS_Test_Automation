
// Fixed 9/2007 by a-jomul

#include <windows.h>            //Common Windows types
#include "screenelement.h"             //RPF
//#include "rpf_constants.h"
#include "LoggingFunctions.h"
#include "rpf_SKUDIFF.h"
#include "SKUDIFF_UTIL.h"
#include <lm.h> // To check domain join status

using namespace RPFPlayback;
using namespace SKUDiff;

void CloseExcessWindows() // test specific, ensure a clean state; can be made better with RPF 12+
{
	wchar_t szGlobalQuery[1024];
	GlobalizeQueryId(szGlobalQuery, 1024, CPL_PARENTAL_CONTROLS_CLOSE_BTN);
	LeftClickUntilGone(szGlobalQuery);
	GlobalizeQueryId(szGlobalQuery, 1024, IE_TOOLS_INTERNET_OPTIONS_CLOSE);
	LeftClickUntilGone(szGlobalQuery);
	GlobalizeQueryId(szGlobalQuery, 1024, CPL_CLOSE_BTN);
	LeftClickUntilGone(szGlobalQuery);
	GlobalizeQueryId(szGlobalQuery, 1024, GAMES_CLOSE_BTN);
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

// isParentalControlsExpected
//
// Helper function that determines if Parental Control Entry points must be present on the current installed SKU or not.
// Returns True : if Parental Control entry points are expected
// Returns False : if Parental Control entry points are not expected
BOOL isParentalControlsExpected()
{
	BOOL fExpected = FALSE;

	DWORD dwProductInfoType = 0;
	if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
	{
		switch (dwProductInfoType)
		{
		case PRODUCT_BUSINESS:
		case PRODUCT_BUSINESS_N:
		case PRODUCT_ENTERPRISE:
		case PRODUCT_ENTERPRISE_N:
			LogTestInfoW(__FUNCTIONW__, L"Parental Controls not expected here!");
			break;
		case PRODUCT_STARTER:
		case PRODUCT_HOME_BASIC:
		case PRODUCT_HOME_BASIC_N:
		case PRODUCT_HOME_PREMIUM:
		case PRODUCT_HOME_PREMIUM_N:
			fExpected = TRUE;
			break;
		case PRODUCT_ULTIMATE:
		case PRODUCT_ULTIMATE_N:
			{
				fExpected = TRUE;
				LPWSTR  pszName;
				NETSETUP_JOIN_STATUS  njs;
				LPCWSTR lpServer = NULL;
				NET_API_STATUS status = NetGetJoinInformation(lpServer, &pszName, &njs);
				if (status != NERR_Success)
				{

					LogTestInfoW(__FUNCTIONW__, L"NetGetJoinInformation(...) invocation failed. Error code = %d", status);
				}
				else
				{
					if (njs == NetSetupDomainName)
					{
						LogTestInfoW(__FUNCTIONW__, L"Computer is Domain joined. Parental Control entry points not expected here.");
						fExpected = FALSE;
					}
				}                
				break;
			}
		default:
			LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
			break;
		}
	}

	return fExpected;
}

//    
//    VerifyParentalControlCplHomeViewEntryPoint 
//  
STDAPI VerifyParentalControlsCplHomeViewEntryPoint(LPVOID pvReserved)
{
	BOOL    fPassed = FALSE;
	LPWSTR pwszResultInfo = NULL;
	HRESULT hr;
	EnableInfoWindow(TRUE);
	LogTestBeginW(__FUNCTIONW__, L"Verify Parental Controls is available from the CPL in Home View");    

	{

		if(SUCCEEDED(OpenControlPanelHomeView()))
		{

			BOOL fExpected = isParentalControlsExpected();
			BOOL fFoundParentalControls = SUCCEEDED(FromPartialQueryId(CPL_LINK_USERACCOUNTSFAMILYSAFETY));

			// To ascertain presence/absence, look for the clickable point.
			int x, y;
			BOOL fFoundClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));
			LogTestInfoW(__FUNCTIONW__,
				L"%s Clickable point for Parental Controls", fFoundClickablePoint ? L"Found": L"Did not find");

			if (fFoundParentalControls && fFoundClickablePoint != fExpected)
			{
				pwszResultInfo = L"Parental Controls CPL entry point is NOT differentiated correctly";
				LogTestInfoW(__FUNCTIONW__,
					L"Parental Controls SKU differentiation failed.[Current: %s | Expected: %s ]",
					fFoundParentalControls ? L"Found": L"Not Found",
					fExpected ? L"Found" : L"Not Found");
			}
			else
			{
				fPassed = TRUE;
				pwszResultInfo = L"Parental Controls CPL entry point is differentiated correctly";
				// Go ahead and click the User Accounts and Family link.
				if (fExpected)
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

					hr = LOG_FAILED_HR(WOWFromPartialQueryId(CPL_LINK_PARENTALCONTROLS));
					if (SUCCEEDED(hr))  
					{
						LogTestInfoW(__FUNCTIONW__,
							L"Parental Controls entry point results.[Current: %s | Expected: %s ]",
							fFoundParentalControls ? L"Found": L"Not Found",
							fExpected ? L"Found" : L"Not Found");            

						LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					}
					else
					{
						fPassed = FALSE;
						pwszResultInfo = L"Parental Controls CPL entry point is NOT differentiated correctly";
						LogTestInfoW(__FUNCTIONW__,
							L"Parental Controls SKU differentiation failed.[Current: %s | Expected: %s ]",
							L"Not Found",
							fExpected ? L"Found" : L"Not Found");
					}
				}
			}
		} 
	} 

	LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");

	hr = LOG_FAILED_HR(FromPartialQueryId(CPL_CLOSE_BTN));
	if (SUCCEEDED(hr))
	{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	}

	LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
	return NOERROR;
}

//    
//    VerifyParentalControlCplClassicViewEntryPoint 
//  
STDAPI VerifyParentalControlsCplClassicViewEntryPoint(LPVOID pvReserved)
{
	BOOL    fPassed = FALSE;
	LPWSTR pwszResultInfo = NULL;
	HRESULT hr;
	LogTestBeginW(__FUNCTIONW__, L"Verify Parental Controls is available from the CPL in Classic View");    
	{
		if (SUCCEEDED(OpenControlPanelClassicView()))
		{
			BOOL fExpected = isParentalControlsExpected();
			BOOL fFoundParentalControls = SUCCEEDED(WOWFromPartialQueryId(CPL_ICON_PARENTALCONTROLS));//CPL_CLASSIC_PARENTAL_CONTROLS

			EnsureVisible();
			int x, y;
			BOOL fFoundClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));
			LogTestInfoW(__FUNCTIONW__,
				L"%s Clickable point for Parental Controls", fFoundClickablePoint ? L"Found": L"Did not find");

			if (fFoundParentalControls && fFoundClickablePoint != fExpected)
			{
				pwszResultInfo = L"Parental Controls CPL entry point is NOT differentiated correctly";
				LogTestInfoW(__FUNCTIONW__,
					L"Parental Controls SKU differentiation failed.[Current: %s | Expected: %s ]",
					fFoundParentalControls ? L"Found": L"Not Found",
					fExpected ? L"Found" : L"Not Found");
			}
			else
			{
				fPassed = TRUE;
				pwszResultInfo = L"Parental Controls CPL entry point is differentiated correctly";
				if (fExpected)
				{
					// Go ahead and double click the Parental Controls list item.
					if (SUCCEEDED(LOG_FAILED_HR(DoubleClick(CLICKABLE_POINT))))
					{
						LogTestInfoW(__FUNCTIONW__,
							L"Parental Controls entry point results.[Current: %s | Expected: %s ]",
							fFoundParentalControls ? L"Found": L"Not Found",
							fExpected ? L"Found" : L"Not Found");         
					}
					else
					{
						fPassed = FALSE;
						pwszResultInfo = L"Parental Controls CPL entry point is NOT differentiated correctly";
						LogTestInfoW(__FUNCTIONW__,
							L"Parental Controls SKU differentiation failed.[Current: %s | Expected: %s ]",
							L"Not Found",
							fExpected ? L"Found" : L"Not Found");         
					}
				}
			}
		} 
	} 

	LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");

	hr = LOG_FAILED_HR(FromPartialQueryId(CPL_CLOSE_BTN));
	if (SUCCEEDED(hr))
	{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	}

	LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
	return NOERROR;
}


//    
//    VerifyParentalControlsGamesExplorerEntryPoint 
//  
STDAPI VerifyParentalControlsGamesExplorerEntryPoint(LPVOID pvReserved)
{
	BOOL    fPassed = FALSE;
	LPWSTR pwszResultInfo = NULL;
	HRESULT hr;
	LogTestBeginW(__FUNCTIONW__, L"Verify Parental Controls is available from the Games Explorer");    
	BOOL gotToTheGamesExplorer = FALSE;

	//LogResKeyValue(L"resKeyAllProgramsGames",resKeyAllProgramsGames);
	//LogResKeyValue(L"resKeyGamesExplorer",resKeyGamesExplorer);

	if(SUCCEEDED(OpenAllPrograms()))
	{
		hr = LOG_FAILED_HR(FromPartialQueryId(ALL_PROGRAMS_GAMES));
		if (SUCCEEDED(hr))
		{
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
			hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_GAMES_EXPLORER));
			if (SUCCEEDED(hr))
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				BOOL fExpected = isParentalControlsExpected();
				BOOL fFoundParentalControls = SUCCEEDED(FromPartialQueryId(GAMES_PARENTAL_CONTROLS_BTN));

				// Parental Controls might end up off the menu-bar depending on Localization and/or window size
				// this bit of code checks for that case, and if so, checks the overflow menu.
				int x, y;
				BOOL fFoundClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));

				if((fFoundClickablePoint == FALSE))// && (IsAvailable(1000,GAMES_OVERFLOW_BTN))
				{
					hr = LOG_FAILED_HR(FromPartialQueryId(GAMES_OVERFLOW_BTN));
					if (SUCCEEDED(hr))
					{
						LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
						fFoundParentalControls = SUCCEEDED(FromPartialQueryId(GAMES_PARENTAL_CONTROLS_POPUP));
						fFoundClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));
					}
				}
				LogTestInfoW(__FUNCTIONW__,
					L"%s Button for Parental Controls", fFoundParentalControls ? L"Found": L"Did not find");

				LogTestInfoW(__FUNCTIONW__,
					L"%s Clickable point for Parental Controls", fFoundClickablePoint ? L"Found": L"Did not find");

				if (fFoundParentalControls && fFoundClickablePoint != fExpected)
				{
					pwszResultInfo = L"Parental Controls CPL entry point is NOT differentiated correctly";
					LogTestInfoW(__FUNCTIONW__,
						L"Parental Controls SKU differentiation failed.[Current: %s | Expected: %s ]",
						fFoundParentalControls ? L"Found": L"Not Found",
						fExpected ? L"Found" : L"Not Found");
				}
				else
				{
					fPassed = TRUE;
					pwszResultInfo = L"Parental Controls Games Explorer entry point is differentiated correctly";
					if (fExpected)
					{
						// Go ahead and open Parental Controls.
						if (SUCCEEDED(LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT))))
						{
							LogTestInfoW(__FUNCTIONW__,
								L"Parental Controls entry point results.[Current: %s | Expected: %s ]",
								fFoundParentalControls ? L"Found": L"Not Found",
								fExpected ? L"Found" : L"Not Found");  

							// close parental controls
							if (SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(CPL_PARENTAL_CONTROLS_CLOSE_BTN))))
							{
								LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
							}
						}
						else
						{
							pwszResultInfo = L"Parental Controls Games Explorer entry point is NOT differentiated correctly";
							fPassed = FALSE;
							LogTestInfoW(__FUNCTIONW__,
								L"Parental Controls SKU differentiation failed.[Current: %s | Expected: %s ]",
								L"Not Found",
								fExpected ? L"Found" : L"Not Found");
						}
					} // Expected
				}
			}// games explorer
		}// games
	}// all programs

LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");

hr = LOG_FAILED_HR(FromPartialQueryId(GAMES_CLOSE_BTN));
if (SUCCEEDED(hr))
{
	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
}
CloseControlPanel();
LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
return NOERROR;
}

//    
//    VerifyParentalControlInternetExplorerEntryPoint 
//  
STDAPI VerifyParentalControlsInternetExplorerEntryPoint(LPVOID pvReserved)
{
	HRESULT hr;
	BOOL    fPassed = FALSE;
	LPWSTR pwszResultInfo = NULL;

	LogTestBeginW(__FUNCTIONW__, L"Verify Parental Controls is available from the Internet Explorer");    

	// close existing Parental Controls windows
	// done by generic cleanup
	/*
	wchar_t CloseButton[1024];
	GlobalizeQueryId(CloseButton, 1024, CPL_PARENTAL_CONTROLS_CLOSE_BTN)
	LeftClickUntilGone(CloseButton)

	int MaxCloseAttempts = 0;
	while (SUCCEEDED(FromPartialQueryId(CPL_PARENTAL_CONTROLS_CLOSE_BTN)) && MaxCloseAttempts++ < 10);
	{
	LeftButtonClick(CLICKABLE_POINT);
	}
	if (MaxCloseAttempts > 0)
	{
	LogTestInfoW(__FUNCTIONW__, L"Closed some open Parental Controls windows.");
	}
	*/


	wchar_t Section[1024];
	wchar_t Link[1024];	
	if (FAILED(GlobalizeQueryId(Section, 1024, CPL_LINK_NETWORKINTERNET)) ||
		FAILED(GlobalizeQueryId(Link, 1024, CPL_LINK_INTERNETOPTIONS)))
	{
		LogTestInfoW(__FUNCTIONW__, L"Failed to get Control Panel names");
		LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
		return(NOERROR);
	}


	if(FAILED(OpenSpecificHomeControlPanel(Section, Link)))
	{
		LogTestInfoW(__FUNCTIONW__, L"Failed to open Internet Options control panel.");
		LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
		return(NOERROR);
	}
	else
	{
		hr = LOG_FAILED_HR(FromPartialQueryId(IE_TOOLS_CONTENT_TAB));

		if (SUCCEEDED(hr))
		{
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

			int x, y;
			BOOL fExpected = isParentalControlsExpected();
			BOOL fFoundParentalControls = SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(IE_TOOLS_PARENTAL_CONTROLS_BTN)));
			BOOL fFoundClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));
			LogTestInfoW(__FUNCTIONW__,
				L"%s Button for Parental Controls", fFoundParentalControls ? L"Found": L"Did not find");

			LogTestInfoW(__FUNCTIONW__,
				L"%s Clickable point for Parental Controls", fFoundClickablePoint ? L"Found": L"Did not find");

			if (fFoundParentalControls && fFoundClickablePoint != fExpected)
			{
				pwszResultInfo = L"Parental Controls CPL entry point is NOT differentiated correctly (check A)";
				LogTestInfoW(__FUNCTIONW__,
					L"Parental Controls SKU differentiation failed(c).[Current: %s | Expected: %s ]",
					(fFoundParentalControls == TRUE) ? L"Found": L"Not Found",
					(fExpected == TRUE) ? L"Found" : L"Not Found");
			}
			else
			{
				if(fFoundParentalControls && fFoundClickablePoint == TRUE)
				{

					// Go ahead and click the Parental Controls button.
					if SUCCEEDED((LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT))))
					{
						fPassed = TRUE;
						pwszResultInfo = L"Parental Controls Internet Explorer entry point is differentiated correctly";
						LogTestInfoW(__FUNCTIONW__,
							L"Parental Controls entry point results.[Current: %s | Expected: %s ]",
							(fFoundParentalControls == TRUE) ? L"Found": L"Not Found",
							(fExpected == TRUE) ? L"Found" : L"Not Found");      

						if (SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(CPL_PARENTAL_CONTROLS_CLOSE_BTN))))
						{
							LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
						}
					}
					else
					{
						pwszResultInfo = L"Parental Controls CPL entry point is NOT differentiated correctly (check B)";
						LogTestInfoW(__FUNCTIONW__,
							L"Parental Controls SKU differentiation failed(d).[Current: %s | Expected: %s ]",
							L"Not Found",
							fExpected ? L"Found" : L"Not Found");
					}
				}
				else
				{
					fPassed = TRUE;
					pwszResultInfo = L"Parental Controls Internet Explorer entry point is differentiated correctly";
					LogTestInfoW(__FUNCTIONW__,
						L"Parental Controls entry point results.[Current: %s | Expected: %s ]",
						(fFoundParentalControls == TRUE) ? L"Found": L"Not Found",
						(fExpected == TRUE) ? L"Found" : L"Not Found");      

				}
			}

			hr = LOG_FAILED_HR(FromPartialQueryId(IE_TOOLS_INTERNET_OPTIONS_CLOSE));
			if (SUCCEEDED(hr))
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
			}

		}

	}

	LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");

	hr = LOG_FAILED_HR(FromPartialQueryId(CPL_PARENTAL_CONTROLS_CLOSE_BTN));
	if (SUCCEEDED(hr))
	{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	}

	LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);

	return NOERROR;
}
