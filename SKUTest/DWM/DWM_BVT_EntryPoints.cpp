#include <windows.h>            //Common Windows types
//#include "rpf_constants.h"
#include "screenelement.h"             //RPF
#include "LoggingFunctions.h"
#include "rpf_skudiff.h" // SKU Diff Contants
#include "SKUDIFF_UTIL.h"

using namespace RPFPlayback;
using namespace SKUDiff;

#include "DWM_BVT.h"

namespace DWM_BVT
{
	STDAPI InitTest(LPVOID)
	{
		HRESULT hr = SKUInitTest();
		// if SUCCEEDED(hr){CloseExcessWindows();}
		return hr;
	}

	STDAPI UnInitTest()
	{
		HRESULT hr = CloseExcessWindows();
		hr = SKUUnInitTest();
		return hr;
	}

	LanguageNeutralString neutralProgramManager(L"Program Manager");

	// IsAero_GlassExpected
	//
	// Helper function that determines if Glass Entry points must be present on the current installed SKU or not.
	// Returns True : if Glass entry points are expected
	// Returns False : if Glass entry points are not expected
	BOOL IsAero_GlassExpected()
	{
		BOOL fExpected = FALSE;

		DWORD dwProductInfoType = 0;

		//Log WEI Scores
		Assessment();

		if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
		{
			switch (dwProductInfoType)
			{
			case PRODUCT_STARTER:
			case PRODUCT_HOME_BASIC:
			case PRODUCT_HOME_BASIC_N:
				LogTestInfoW(__FUNCTIONW__, L"Glass not expected on this SKU.");
				fExpected = FALSE;
				break;
			case PRODUCT_BUSINESS:
			case PRODUCT_BUSINESS_N:
			case PRODUCT_ENTERPRISE:
			case PRODUCT_ENTERPRISE_N:
			case PRODUCT_HOME_PREMIUM:
			case PRODUCT_HOME_PREMIUM_N:
			case PRODUCT_ULTIMATE:
			case PRODUCT_ULTIMATE_N:
				if (Get2DScore() >= 2)
				{
					LogTestInfoW(__FUNCTIONW__, L"Glass expected here.");
					fExpected = TRUE;
				}
				else
				{
					LogTestInfoW(__FUNCTIONW__, L"Video rating not good enough for Glass.");
					fExpected = FALSE;
				}
				break;
			default:
				LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
				break;
			}
		}
		return fExpected;
	}


	HRESULT OpenChangeYourColorScheme()
	{
		

		//BOOL fChangeYourColorSchemeOpened = FALSE;
		HRESULT hr;

		wchar_t Section[1024];
		wchar_t Link[1024];	
		if (SUCCEEDED(GlobalizeQueryId(Section, 1024, CPL_LINK_APPEARANCEPERSONALIZATION)) &&
			SUCCEEDED(GlobalizeQueryId(Link, 1024, CPL_LINK_PERSONALIZATION)) &&
			SUCCEEDED(OpenSpecificHomeControlPanel(Section, Link)))
		{
			LogTestInfoW(__FUNCTIONW__,	L"Opened Personalization Control Panel.");
			hr = LOG_FAILED_HR(FromPartialQueryId(CPL_WIN_COLOR_AND_APPEARANCE));
			if (SUCCEEDED(hr))  
			{
				hr = LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				if (SUCCEEDED(hr))  
				{
					LogTestInfoW(__FUNCTIONW__,	L"Opened Change your Color Scheme.");
					return NOERROR;
					//fChangeYourColorSchemeOpened = TRUE;
				}
				else
				{
					LogTestInfoW(__FUNCTIONW__,	L"Failed to open Change your Color Scheme.");
					return hr;
				}
			}
			else
			{
				LogTestInfoW(__FUNCTIONW__,	L"Failed to open Change your Color Scheme.");
				return hr;
			}
		}
		else
		{
			LogTestInfoW(__FUNCTIONW__,	L"Failed to open Personalization Control Panel.");
			return E_FAIL;
		}

		//return fChangeYourColorSchemeOpened;
	}

	//    
	//    VerifyDWM_GlassEntryPoint 
	//  
	STDAPI VerifyDWM_GlassEntryPoint(LPVOID pvReserved)
	{
		__try
		{

		CloseExcessWindows();
		
		BOOL    fPassed = FALSE;
		LPWSTR pwszResultInfo = NULL;
		HRESULT hr;
		LogTestBeginW(__FUNCTIONW__, L"Verify Glass is available.");    
		BOOL fExpected = IsAero_GlassExpected();
		BOOL fFoundEtcClickablePoint = FALSE;
		if (SUCCEEDED(OpenChangeYourColorScheme()))
		{
			if (SUCCEEDED(FromPartialQueryId(CPL_ENABLE_TRANSPARENT_GLASS)))
			{
				int x, y;
				fFoundEtcClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));
				LogTestInfoW(__FUNCTIONW__,
					L"%s Clickable point for Enable Transparency Checkbox", 
					fFoundEtcClickablePoint ? L"Found": L"Did not find");

				if (fFoundEtcClickablePoint != fExpected)
				{
					pwszResultInfo = L"Glass Entry point is not differentiated correctly";
					LogTestInfoW(__FUNCTIONW__,
						L"DWM Glass SKU differentiation failed.[Current: %s | Expected: %s ]",
						fFoundEtcClickablePoint ? L"Found": L"Not Found",
						fExpected ? L"Found" : L"Not Found");
				}
				else
				{
					fPassed = TRUE;
					if (fExpected)
					{
						// Go ahead and change state of the checkbox.
						LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
						// return checkbox to original state.
						LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					}
					pwszResultInfo = L"Glass Entry point is differentiated correctly";
					LogTestInfoW(__FUNCTIONW__,
						L"Entry point results.[Current: %s | Expected: %s ]",
						fFoundEtcClickablePoint ? L"Found": L"Not Found",
						fExpected ? L"Found" : L"Not Found");  
				}
			}
			else
			{
				if (fExpected)
				{
					pwszResultInfo = L"Glass Entry point is not differentiated correctly";
					LogTestInfoW(__FUNCTIONW__,
						L"DWM Glass SKU differentiation failed.[Current: %s | Expected: %s ]",
						fFoundEtcClickablePoint ? L"Found": L"Not Found",
						fExpected ? L"Found" :  L"Not Found");
				}
				else
				{
					pwszResultInfo = L"Glass Entry point is differentiated correctly";
					fPassed = TRUE;
				}
			}


		}
		else
		{
			pwszResultInfo = L"Could not open 'Change your color scheme' CPL";
			LogTestInfoW(__FUNCTIONW__,
				L"DWM Glass SKU differentiation failed.[Current: %s | Expected: %s ]",
				fFoundEtcClickablePoint ? L"Found": L"Not Found",
				fExpected ? L"Found" :  L"Not Found");
		}
		
		LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
		return NOERROR;
	  }
		__except(ExceptionFilter(GetExceptionCode(), GetExceptionInformation()))
      {
            LogTestInfoW(__FUNCTIONW__, L"Failing due to an exception.");
            return E_FAIL;
      }

	}


	//    
	//    VerifyDWM_AeroEntryPoint 
	//  
	STDAPI VerifyDWM_AeroEntryPoint(LPVOID pvReserved)
	{
		__try
		{

		CloseExcessWindows();

		BOOL    fPassed = FALSE;
		LPWSTR pwszResultInfo = NULL;
		HRESULT hr;
		LogTestBeginW(__FUNCTIONW__, L"Verify Vista Aero Color Scheme is available.");    
		BOOL fExpected = IsAero_GlassExpected();
		BOOL fFoundAeroColorSchemeClickablePoint = FALSE;

		if (SUCCEEDED(OpenChangeYourColorScheme()))
		{
			HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(CPL_OPEN_CLASSIC_APPEARANCE));
			if (SUCCEEDED(hr))
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
			}
			if (SUCCEEDED(FromPartialQueryId(WINDOWS_VISTA_AERO_COLOR_SCHEME)))
			{
				int x, y;
				fFoundAeroColorSchemeClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));
				LogTestInfoW(__FUNCTIONW__,
					L"%s Clickable point for Aero Color Scheme", 
					fFoundAeroColorSchemeClickablePoint ? L"Found": L"Did not find");

				if (fFoundAeroColorSchemeClickablePoint != fExpected)
				{
					pwszResultInfo = L"Aero Entry point is not differentiated correctly(a)";
					// Save Screen Capture
					hr = DumpScreen(L"dwmaeroa", DUMP_SCREEN_PNG);
					if (SUCCEEDED(hr))
					{
						LogTestInfoW(__FUNCTIONW__,	L"Screen Dumped as dwmaeroa.png");
					}
					
					LogTestInfoW(__FUNCTIONW__,
						L"DWM Aero SKU differentiation failed.[Current: %s | Expected: %s ]",
						fFoundAeroColorSchemeClickablePoint ? L"Found": L"Not Found",
						fExpected ? L"Found" : L"Not Found");
				}
				else
				{
					fPassed = TRUE;
					if (fExpected)
					{
						// Go ahead and click it.
						LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					}
					pwszResultInfo = L"Aero Entry point is differentiated correctly";
					LogTestInfoW(__FUNCTIONW__,
						L"Entry point results.[Current: %s | Expected: %s ]",
						fFoundAeroColorSchemeClickablePoint ? L"Found": L"Not Found",
						fExpected ? L"Found" : L"Not Found");  
				}
			}
			else
			{
				if (fExpected)
				{
					pwszResultInfo = L"Aero Entry point is not differentiated correctly(b)";
					// Save Screen Capture
					hr = DumpScreen(L"dwmaerob", DUMP_SCREEN_PNG);
					if (SUCCEEDED(hr))
					{
						LogTestInfoW(__FUNCTIONW__,	L"Screen Dumped as dwmaerob.png");
					}
					LogTestInfoW(__FUNCTIONW__,
						L"DWM Aero SKU differentiation failed.[Current: %s | Expected: %s ]",
						fFoundAeroColorSchemeClickablePoint ? L"Found": L"Not Found",
						fExpected ? L"Found" :  L"Not Found");
				}
				else
				{
					pwszResultInfo = L"Aero Entry point is differentiated correctly";
					fPassed = TRUE;
				}
			}


		}
		else
		{
			pwszResultInfo = L"Could not open 'Change your color scheme' CPL";
			LogTestInfoW(__FUNCTIONW__,
				L"DWM Glass SKU differentiation failed.[Current: %s | Expected: %s ]",
				fFoundAeroColorSchemeClickablePoint ? L"Found": L"Not Found",
				fExpected ? L"Found" :  L"Not Found");
		}
		
		//SetSearchTimeOut(originalTimeout); //Haste
		LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
		return NOERROR;
	  }
		__except(ExceptionFilter(GetExceptionCode(), GetExceptionInformation()))
      {
            LogTestInfoW(__FUNCTIONW__, L"Failing due to an exception.");
            return E_FAIL;
      }
	}

	//    
	//    VerifyDWM_WindowsSwitcherEntryPoint 
	//  
	STDAPI VerifyDWM_WindowsSwitcherEntryPoint(LPVOID pvReserved)
	{
		__try
		{

		CloseExcessWindows();

		BOOL    fPassed = FALSE;
		LPWSTR pwszResultInfo = NULL;
		BOOL fExpected = IsAero_GlassExpected();

		LogTestBeginW(__FUNCTIONW__, L"Verify Windows Flip 3D is available.");    

		if (SUCCEEDED(OpenChangeYourColorScheme()))
		{
			BOOL fFoundSwitcherClickablePoint = FALSE;
			if (SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(WINDOWS_SWITCHER))))
			{
				int x, y;
				LOG_FAILED_HR(GetClickablePoint(&x, &y));

				// Go ahead and click it to bring up windows switcher.
				keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_LCONTROL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				Sleep((DWORD)5000);
				// check if 3D switcher came up
				fFoundSwitcherClickablePoint = SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(DWM_FLIP3D)));
				if( FALSE == fFoundSwitcherClickablePoint )
				{
					fFoundSwitcherClickablePoint = SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(L";AccessibleName = '{0}' && ClassName => 'Flip3D';[VisibleOnly]Name = '{0}' && Role = 'list';Name = '{1}' && Role = 'list item'", resKeyFlip3D, neutralProgramManager)));
					if( FALSE == fFoundSwitcherClickablePoint )
					{
						LogTestInfoW(__FUNCTIONW__, L"Rolodex Flip3D screen presence was not detected. Try again to detect with another query...");
						fFoundSwitcherClickablePoint = SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(L";AccessibleName = '{0}' && ClassName => 'Flip3D';[VisibleOnly]Name = '{0}' && Role = 'list'", resKeyFlip3D)));
					}
				}
				else if( FALSE == fFoundSwitcherClickablePoint )
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				// Release WinLKey+LCtrl+Tab keys
				keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				keybd_event(VK_LCONTROL, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);

				if (fFoundSwitcherClickablePoint)
				{
					LogTestInfoW(__FUNCTIONW__,
						L"%s Flip 3D.", 
						fFoundSwitcherClickablePoint ? L"Found": L"Did not find");

					if (fFoundSwitcherClickablePoint != fExpected)
					{
						pwszResultInfo = L"Windows Flip 3D is not differentiated correctly";
						LogTestInfoW(__FUNCTIONW__,
							L"DWM Flip 3D SKU differentiation failed.[Current: %s | Expected: %s ]",
							fFoundSwitcherClickablePoint ? L"Found": L"Not Found",
							fExpected ? L"Found" : L"Not Found");
					}
					else
					{
						fPassed = TRUE;
					}

				}
				// Click it again to return back.
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
			}
		}
		LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
		return NOERROR;
	  }
		__except(ExceptionFilter(GetExceptionCode(), GetExceptionInformation()))
      {
            LogTestInfoW(__FUNCTIONW__, L"Failing due to an exception.");
            return E_FAIL;
      }
	} // End STDAPI VerifyDWM_WindowsSwitcherEntryPoint(LPVOID pvReserved)
} // End namespace DWM_BVT



