/***************************************************************
// Description: BVT - DWM entry point verification
//				Verifies expected features for Display Windows Management
// Created:     a-maklum
//
// Verify:      Pass test case if feature is available
//              in all SKUs but Starter and Home Basic
****************************************************************/

#include <windows.h>            //Common Windows types
#include "screenelement.h"             //RPF
//#include "rpf_constants.h"
#include "LoggingFunctions.h"
#include "rpf_SKUDIFF.h"
#include "SKUDIFF_UTIL.h"

using namespace RPFPlayback;
using namespace SKUDiff;

#include "DWM_BVT.h"

#pragma warning(disable : 4995)

namespace DWM_BVT
{
	// Globalized query ID buffer
	static wchar_t szGlobalQuery[1024];
	// Environment variable expansion buffer
	static LPWSTR expandedWinDir[MAX_PATH];
	static wchar_t *unsupportedSKU = NULL;

	#pragma region Resource Keys
	const wchar_t* resKeyIEAlternate = L"RKB1[];Internet Explorer;Win32String;%wirdir%\\system32\\ie4uinit.exe;734";
	const wchar_t* resKeyInternetExplorer = L"RKB1[];Internet Explorer;Win32String;%windir%\\system32\\ie4uinit.exe;731";
	const wchar_t* resKeyWindowsInternetExplorer = L"RKB1[];Windows Internet Explorer;Win32String;%windir%\\system32\\ieframe.dll;12613";
	const wchar_t* resKeyWordPad = L"RKB1[];WordPad;Win32String;%windir%\\system32\\shell32.dll;22069";
	const wchar_t* resKeyWindowsExplorer = L"RKB1[];WindowS Exolorer;Win32String;%windir%\\system32\\shell32.dll;22067";
	const wchar_t* resKeyNotepad = L"RKB1[];Notepad;Win32String;%windir%\\system32\\shell32.dll;22051";
	const wchar_t* resKeyDontSave = L"RKB1[];Do&n't Save;Win32String;%windir%\\notepad.exe;3003";
	const wchar_t* resKeyTaskSwitching = L"RKB1[];Task Switching;Win32String;%windir%\\system32\\alttab.dll;1000";
	const wchar_t* resKeyMicrosoftDashPhishingfilt = L"RKB1[];Microsoft-Phishingfilter;Win32String;%windir%\\system32\\ieframe.dll;12781";
	const wchar_t* resKeyRunningApolications = L"RKB1[];Running Apolications;Win32String;%windir%\\explorer.exe;594";
	/// LanguageNeutral Strings
	LanguageNeutralString langNeutralDocument(L"[QoERL][Ďöċümэňτ !]");
	LanguageNeutralString langNeutralDash(L"-");
	LanguageNeutralString langNeutralWordPad(L"[QoERL][ŴоŕđΡдď !]");
	LanguageNeutralString langNeutralCClnBslshUsersBslshAdmini((wchar_t*)expandedWinDir);
	LanguageNeutralString langNeutralMSNDotcomDash(L"MSN.com -");
	LanguageNeutralString langNeutralProgramManager(L"Program Manager");
	/// Complex Resource Keys
	const wchar_t* resKeyUntitled = L"RKB1[];Untitled;Win32String;%windir%\\notepad.exe;4";
	const wchar_t* resKeyDashNotepad = L"RKB1[]; - Notepad;Win32String;%windir%\\notepad.exe;5";
	ComplexResourceKeyNative cmplxKeyUntitledDashNotepad(L"{%s%s}", resKeyUntitled, resKeyDashNotepad);
	ComplexResourceKeyNative cmplxKeyDocumentDashWordPad(L"{%s %s %s}", langNeutralDocument, langNeutralDash, langNeutralWordPad);
	ComplexResourceKeyNative cmplxKeyMSNDotcomDashWindowS(L"{%s %s}", langNeutralMSNDotcomDash, resKeyWindowsInternetExplorer);
	#pragma endregion Resource Keys

	// IsDesktopWindowManagerExpected
	//
	// Helper function that determines if Desktop Window Manager Entry points must be present
	// on the current installed SKU or not.
	// Returns True : if Desktop Window Manager entry points are expected
	// Returns False : if Desktop Window Manager entry points are not expected
	static BOOL IsDesktopWindowManagerExpected()
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
				unsupportedSKU = L"PRODUCT_STARTER";
				LogTestInfoW(__FUNCTIONW__, L"Desktop Window Manager not expected on this SKU.");
				fExpected = FALSE;
				break;
			case PRODUCT_HOME_BASIC:
				unsupportedSKU = L"PRODUCT_HOME_BASIC";
				LogTestInfoW(__FUNCTIONW__, L"Desktop Window Manager not expected on this SKU.");
				fExpected = FALSE;
				break;
			case PRODUCT_HOME_BASIC_N:
				unsupportedSKU = L"PRODUCT_HOME_BASIC_N";
				LogTestInfoW(__FUNCTIONW__, L"Desktop Window Manager not expected on this SKU.");
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
					LogTestInfoW(__FUNCTIONW__, L"Desktop Window Manager expected here.");
					fExpected = TRUE;
				}
				else
				{
					LogTestInfoW(__FUNCTIONW__, L"Video rating not good enough for Desktop Window Manager.");
					fExpected = FALSE;
				}
				break;
			default:
				LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
				break;
			}
		}
		return fExpected;
	} // End static BOOL IsDesktopWindowManagerExpected()

	/*    
	//    VerifyDWM_AltTabVisuals - Test Flip (ALT-Tab)
	// [Steps]
	//
	// 1. Open a few windows (IE, explorer, Wordpad, Notepad)
	// 2. ALT + Tab
	// 3. ALT + SHIFT + Tab to flip in reverse
	// 4. CTRL + ALT + Tab (same as ALT + TAB but sticky mode)
	//
	// [Expected results]
	//
	// Pass:
	// Thumbnails appear for all open windows in supported SKUs
	// Sticky mode works (CTRL+ALT+Tab), (CTRL+ALT+SHIFT+Tab)
	// Help related to Thumbnails is available on supported SKUs.
	//
	// Fail:
	// Thumbnails do not appear in supported SKUs
	// Thumbnails appear in starter and home basic SKUs
	// CTRL+ALT+Tab behaves like ALT+Tab
	// CTRL+ALT+SHIFT+Tab behaves like ALT+SHIFT+Tab
	// Help related to Thumbnails is available on unsupported SKUs.
	*/
	STDAPI VerifyDWM_AltTabVisuals(LPVOID pvReserved)
	{
		BOOL fExpected = FALSE;
		HRESULT hr = E_FAIL;
		wchar_t *pwszResultInfo = NULL,
				stateDescription[1024],
				*stateComparison = L"sizeable,moveable,focusable";
		__try
		{

		CloseExcessWindows();
		SetRobustnessLevel( 1 );

		LogTestBeginW(__FUNCTIONW__, L"Verifing that WDM Flip Alt+Tab feature can be used on a supported SKU.");
		fExpected = IsDesktopWindowManagerExpected();
		// Used to pass flow of control to after the end of the while loop if a failue occurs using break statements.
		// This also allows the loop to be restarted with a continue statement if required.
		while( TRUE )
		{
			// Left Button Click - "push button" named "Start" and "All Programs" in window "Start"
			LogTestInfoW(__FUNCTIONW__, L"Attempting to open START->ALL PROGRAMS...");
			if ( FAILED(hr = LOG_FAILED_HR(OpenAllPrograms())) )
				hr = LOG_FAILED_HR(OpenAllPrograms());
			if( SUCCEEDED(hr) )
				hr = NOERROR;
			else
			{
				pwszResultInfo = L"Failed to open START->ALL PROGRAMS.";
				hr = E_FAIL;
				break;
			}
			// Left Button Click - "menu item" named "Internet Explorer" in window "Start Menu"
			LogTestInfoW(__FUNCTIONW__, L"Attempting to open Internet Explorer...");
			hr = LOG_FAILED_HR(WOWFromPartialQueryId(STARTMENU_INTERNET_EXPLORER));
			if( FAILED(hr) )
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'DV2ControlHost';Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyInternetExplorer));
			if( FAILED(hr) )
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyIEAlternate));
			if( SUCCEEDED(hr) )
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				hr = NOERROR;
			}
			else
			{
				pwszResultInfo = L"Failed to open Internet Explorer, remaining tests skipped.";
				hr = NOERROR;
				break;
			}
			Sleep((DWORD)3000);
			LogTestInfoW(__FUNCTIONW__, L"Verifying that Switch Windows Flip dialogue is enabled and useable.");
			if ( SUCCEEDED(LOG_FAILED_HR(TypeString((BSTR)L"^(%({TAB})){ENTER}", 3000, FALSE))) )
			{
				LogTestInfoA(__FUNCTION__, "Querying WINDOWS_SWITCHER for success or failure status.");
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name = '{0}' && Role = 'list'", resKeyTaskSwitching));
				hr = ( !SUCCEEDED(hr) ) ? LOG_FAILED_HR(WOWFromPartialQueryId(WINDOWS_SWITCHER)) : hr;
				LogTestInfoA(__FUNCTION__, "Success status of WINDOWS_SWITCHER query is %s.", ( SUCCEEDED(hr) ) ? "SUCCEEDED" : "FAILED");
				if( SUCCEEDED(hr) )
					hr = NOERROR;
				else
				{
					pwszResultInfo = L"Failed to verify that Switch Windows Flip dialogue is enabled and useable.";
					hr = E_FAIL;
					break;
				}
			}
			else
			{
				pwszResultInfo = L"Failed on TypeString((BSTR)L\"^(%({TAB})){ENTER}\", 1000, FALSE) call.";
				hr = E_FAIL;
				break;
			}
			Sleep((DWORD)3000);
			// Left Button Click - "push button" named "Start" and "All Programs" in window "Start"
			LogTestInfoW(__FUNCTIONW__, L"Attempting to open START->ALL PROGRAMS...");
			if ( FAILED(hr = LOG_FAILED_HR(OpenAllPrograms())) )
				hr = LOG_FAILED_HR(OpenAllPrograms());
			if( SUCCEEDED(hr) )
				hr = NOERROR;
			else
			{
				pwszResultInfo = L"Failed to open START->ALL PROGRAMS.";
				hr = E_FAIL;
				break;
			}
			// Expand Item - "outline item" named "Accessories"
			LogTestInfoW(__FUNCTIONW__, L"Expanding Accessories start menu item...");
			hr = LOG_FAILED_HR(WOWFromPartialQueryId(STARTMENU_ACCESSORIES));
			if( SUCCEEDED(hr) )
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				hr = NOERROR;
			}
			else
			{
				pwszResultInfo = L"Failed to expand Accessories start menu item.";
				hr = E_FAIL;
				break;
			}
			// Left Button Click - "menu item" named "WordPad" in window "Start Menu"
			LogTestInfoW(__FUNCTIONW__, L"Attempting to launch Wordpad...");
			LOG_FAILED_HR(WOWGlobalizeQueryId((PWSTR)szGlobalQuery, 1024, L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyWordPad));
			hr = LOG_FAILED_HR(WOWFromPartialQueryId((wchar_t*)szGlobalQuery));
			if( SUCCEEDED(hr) )
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				hr = NOERROR;
			}
			else
			{
				pwszResultInfo = L"Failed to launch Wordpad.";
				hr = E_FAIL;
				break;
			}
			Sleep((DWORD)3000);
			// Left Button Click - "push button" named "Start" and "All Programs" in window "Start"
			LogTestInfoW(__FUNCTIONW__, L"Attempting to open START->ALL PROGRAMS...");
			if ( FAILED(hr = LOG_FAILED_HR(OpenAllPrograms())) )
				hr = LOG_FAILED_HR(OpenAllPrograms());
			if( SUCCEEDED(hr) )
				hr = NOERROR;
			else
			{
				pwszResultInfo = L"Failed to open START->ALL PROGRAMS.";
				hr = E_FAIL;
				break;
			}
			// Expand Item - "outline item" named "Accessories"
			LogTestInfoW(__FUNCTIONW__, L"Attempting to expand Accessories start menu item...");
			hr = LOG_FAILED_HR(WOWFromPartialQueryId(STARTMENU_ACCESSORIES));
			if( SUCCEEDED(hr) )
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				hr = NOERROR;
			}
			else
			{
				pwszResultInfo = L"Failed to expand Accessories start menu item.";
				hr = E_FAIL;
				break;
			}
			// Left Button Click - "menu item" named "Windows Explorer" in window "Start Menu"
			LogTestInfoW(__FUNCTIONW__, L"Attempting to launch Windows Explorer...");
			LOG_FAILED_HR(WOWGlobalizeQueryId((PWSTR)szGlobalQuery, 1024, L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyWindowsExplorer));
			hr = LOG_FAILED_HR(WOWFromPartialQueryId((PCWSTR)szGlobalQuery));
			if( SUCCEEDED(hr) )
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				hr = NOERROR;
			}
			else
			{
				pwszResultInfo = L"Failed to launch Windows Explorer.";
				hr = E_FAIL;
				break;
			}
			Sleep((DWORD)3000);
			// Left Button Click - "push button" named "Start" and "All Programs" in window "Start"
			LogTestInfoW(__FUNCTIONW__, L"Attempting to open START->ALL PROGRAMS...");
			if ( FAILED(hr = LOG_FAILED_HR(OpenAllPrograms())) )
				hr = LOG_FAILED_HR(OpenAllPrograms());
			if( SUCCEEDED(hr) )
				hr = NOERROR;
			else
			{
				pwszResultInfo = L"Failed to open START->ALL PROGRAMS.";
				hr = E_FAIL;
				break;
			}
			// Expand Item - "outline item" named "Accessories"
			LogTestInfoW(__FUNCTIONW__, L"Attempting to expand Accessories start menu item...");
			hr = LOG_FAILED_HR(WOWFromPartialQueryId(STARTMENU_ACCESSORIES));
			if( SUCCEEDED(hr) )
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				hr = NOERROR;
			}
			else
			{
				pwszResultInfo = L"Failed to expand Accessories start menu item.";
				hr = E_FAIL;
				break;
			}
			// Left Button Click - "menu item" named "Notepad" in window "Start Menu"
			LogTestInfoW(__FUNCTIONW__, L"Attempting to launch Notepad...");
			LOG_FAILED_HR(WOWGlobalizeQueryId((PWSTR)szGlobalQuery, 1024, L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyNotepad));
			hr = LOG_FAILED_HR(WOWFromPartialQueryId((PCWSTR)szGlobalQuery));
			if( SUCCEEDED(hr) )
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				hr = NOERROR;
			}
			else
			{
				pwszResultInfo = L"Failed to launch Notepad.";
				hr = E_FAIL;
				break;
			}
			// AltTab FlipForward - Press and hold the Alt key while simultaneously pressing the Tab key two times, then release
			// the Alt key. This test will pass if the Flip task swap window was previously detected, and the last window appearing
			// with focus is Internet Explorer.
			LogTestInfoW(__FUNCTIONW__, L"Sending two Alt+Tab key combinations to verify correct operation of Alt+Tab Flip-Forward.");
			LogTestInfoW(__FUNCTIONW__, L"To pass, Internet Explorer must be the last window on top with focus.");
			LogTestInfoW(__FUNCTIONW__, L"This portion of the test is %s to fail due to the detected SKU.", (fExpected) ? L"not expected" : L"expected");
			hr = LOG_FAILED_HR(TypeString((BSTR)L"%({TAB}{TAB}{ENTER})", 1000, FALSE));
			if( SUCCEEDED(hr) )
			{
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && Role = 'window'", (wchar_t*) cmplxKeyDocumentDashWordPad));
				if( !SUCCEEDED(hr) )
					hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => ' ' && Role = 'window'"));
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				LOG_FAILED_HR(GetScreenElementInfo(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, stateDescription, MAX_VALUE_LENGTH));
				LogTestInfoW(__FUNCTIONW__, L"The state description is %s, and state comparison is %s.", stateDescription, stateComparison);
				if( SUCCEEDED(hr) && NULL != wcspbrk(stateDescription, stateComparison) )
					hr = NOERROR;
				else
				{
					pwszResultInfo = L"Failed while detecting correct operation of Alt+Tab Flip-Forward.";
					hr = E_FAIL;
					break;
				}
			}
			else
			{
				pwszResultInfo = L"Failed on call to LOG_FAILED_HR(TypeString((BSTR)L\"%({TAB}{TAB}{ENTER})\", 1000, FALSE)).";
				hr = E_FAIL;
				break;
			}

			// AltTab Backward - Press and hold the Alt+Shift keys while pressing the Tab key thre times, then release the Alt+Shift keys.
			// This test will pass if the Flip task swap window was previously detected, and the last window appearing with focus
			// is Windows Explorer.
			LogTestInfoW(__FUNCTIONW__, L"Sending thee Alt+Shift+Tab key combinations to verify correct operation of Alt+Shift+Tab Flip-Backward.");
			LogTestInfoW(__FUNCTIONW__, L"To pass, Windows Explorer must be the last window on top with focus.");
			LogTestInfoW(__FUNCTIONW__, L"This portion of the test is %s to fail due to the detected SKU.", (fExpected) ? L"not expected" : L"expected");
			hr = LOG_FAILED_HR(TypeString((BSTR)L"%(+({TAB}{TAB}{TAB}{ENTER}))", 1000, FALSE));
			if( SUCCEEDED(hr) )
			{
				LogTestInfoW(__FUNCTIONW__, L"Calling ExpandEnvironmentStringsW(L\"%userprofile%\", (LPWSTR)expandedWinDir, MAX_PATH)");
				DWORD numLetters = ExpandEnvironmentStringsW(L"%userprofile%", (LPWSTR)expandedWinDir, MAX_PATH);
				LogTestInfoW(__FUNCTIONW__, L"End calling ExpandEnvironmentStringsW(L\"%userprofile%\", expandedWinDir, MAX_PATH)");
				if( 0 == (int)numLetters )
				{
					pwszResultInfo = L"Failed to expand environment variable %%userprofile%%";
					hr = E_FAIL;
					break;
				}
				wchar_t temp[MAX_PATH];
				wcscat_s(temp, MAX_PATH, L";Name => '"); 
				wcscat_s(temp, MAX_PATH, (const wchar_t*)expandedWinDir);
				wcscat_s(temp, MAX_PATH, L"\\Documents' && Role = 'window'");
				hr = LOG_FAILED_HR(WOWFromPartialQueryId((PCWSTR)temp));
				if( !SUCCEEDED(hr) )
					hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => 'MSN.com - {0}' && Role = 'window'", resKeyWindowsInternetExplorer));
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				LOG_FAILED_HR(GetScreenElementInfo(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, stateDescription, MAX_VALUE_LENGTH));
				LogTestInfoW(__FUNCTIONW__, L"The state description is %s, and state comparison is %s.", stateDescription, stateComparison);
				if( SUCCEEDED(hr) && NULL != wcspbrk(stateDescription, stateComparison) )
					hr = NOERROR;
				else
				{
					pwszResultInfo = L"Failed while detecting correct operation of Alt+Shift+Tab Flip-Backward.";
					hr = E_FAIL;
					break;
				}
			}
			else
			{
				pwszResultInfo = L"Failed on call to LOG_FAILED_HR(TypeString((BSTR)L\"%(+({TAB}{TAB}{TAB}{ENTER}))\", 1000, FALSE)).";
				hr = E_FAIL;
				break;
			}

			// Sticky AltTab Forward - Press and hold the Ctrl+Alt keys while pressing the Tab key
			// two times, then release the Ctrl+Alt keys and then press the enter key over the selected
			// window thumbnail. This test will pass if the Flip task swap window was previously
			// detected, and the last window appearing with focus is Notepad.
			LogTestInfoW(__FUNCTIONW__, L"Sending two Ctrl+Alt+Tab key combinations to verify correct operation of Ctrl+Alt+Tab Flip-Forward in sticky mode.");
			LogTestInfoW(__FUNCTIONW__, L"To pass, Notepad must be the last window on top with focus.");
			LogTestInfoW(__FUNCTIONW__, L"This portion of the test is %s to fail due to the detected SKU.", (fExpected) ? L"not expected" : L"expected");
			hr = LOG_FAILED_HR(TypeString((BSTR)L"^(%({TAB}{TAB}))", 1000, FALSE));
			if( SUCCEEDED(hr) )
			{
				LogTestInfoW(__FUNCTIONW__, L"Checking for reappearance of the Flip task swap window...");
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name = '{0}' && Role = 'list'", resKeyTaskSwitching));
				if( FAILED(hr) )
				{
					pwszResultInfo = L"Failed on checking for reappearance of the Flip task swap window.";
					hr = E_FAIL;
					break;
				}
				LOG_FAILED_HR(TypeString((BSTR)L"{ENTER}"));
				LogTestInfoW(__FUNCTIONW__, L"Checking for Notepad as the last window on top with focus...");
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && Role = 'window'", resKeyNotepad));
				if( SUCCEEDED(hr) || SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(L";Name = '{0}' && Role = 'window'", (wchar_t*) cmplxKeyUntitledDashNotepad))) )
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					hr = NOERROR;
				}
				else
				{
					pwszResultInfo = L"Failed on checking for Notepad as the last window on top with focus.";
					hr = E_FAIL;
					break;
				}
				LOG_FAILED_HR(GetScreenElementInfo(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, stateDescription, MAX_VALUE_LENGTH));
				hr = ( NULL != wcspbrk(stateDescription, stateComparison) ) ? NOERROR : E_FAIL;
				LogTestInfoW(__FUNCTIONW__, L"The state description is %s, and state comparison is %s.", stateDescription, stateComparison);
				if( SUCCEEDED(hr) )
					hr = NOERROR;
				else
				{
					pwszResultInfo = L"Failed on call to Ctrl+Alt+Tab Flip-Forward in sticky mode.";
					hr = E_FAIL;
					break;
				}
			}
			else
			{
				pwszResultInfo = L"Failed on call to TypeString((BSTR)L\"^(%({TAB}{TAB}))\", 1000, FALSE).";
				hr = E_FAIL;
				break;
			}

			pwszResultInfo = L"All test operations succeeded with no errors.";
			break; // No matter what, when the execution stack pointer reaches this position, break out! of the while() loop.
		} // End while( TRUE )
		if( !fExpected && unsupportedSKU != NULL )
		{
			pwszResultInfo = L"An unsupported SKU was detected and found that DWM feature is not present.";
			hr = NOERROR;
		}
		BOOL bfinalResult = SUCCEEDED(hr);
		LogTestInfoW(__FUNCTIONW__,
			L"Unit test function VerifyDWM_AltTabVisuals() has exited with error status: %s",
			bfinalResult ? L"0" : L"-1" );
		LogTestResultW(bfinalResult, __FUNCTIONW__, pwszResultInfo);
		return hr;
	  }
		__except(ExceptionFilter(GetExceptionCode(), GetExceptionInformation()))
      {
            LogTestInfoW(__FUNCTIONW__, L"Failing due to an exception.");
            return E_FAIL;
      }

	} // End STDAPI VerifyDWM_AltTabVisuals(LPVOID pvReserved)

	// Sticky AltTab Windows Switcher Backwards Navigation (four button key combination) - Press and hold the Ctrl+Alt+Shift
	// keys while pressing the Tab key two times, then release the Ctrl+Alt+Shift keys and then press the enter key over the
	// selected window thumbnail. This test will pass if the Flip task swap window was previously detected, the four button
	// key combination WILL ACTIVATE the Flip task swap window having window thumbnails, and the last window appearing with
	// focus is Internet Explorer.
	// Test update: Per Windows OS bug# 1428505 this feature is not available in all SKUs and this test will be set to reflect
	// this as the expected result.
	STDAPI VerifyDWM_4BTNComboDisabled(LPVOID pvReserved)
	{
		BOOL fExpected = FALSE;
		wchar_t *pwszResultInfo = NULL,
				stateDescription[1024],
				*stateComparison = L"sizeable,moveable,focusable";
	  __try
	  {
		LogTestInfoW(__FUNCTIONW__, L"Verifing that sticky windows switcher Ctrl+Alt+Shift+Tab Flip-Backward is disabled is ALL SKUs.");
		fExpected = IsDesktopWindowManagerExpected();
		LogTestInfoW(__FUNCTIONW__, L"To pass, this four-button-key-combination must not activate the Flip task swap/switcher window, and Internet Explorer must not be the last window on top with focus.");
		LogTestInfoW(__FUNCTIONW__, L"This portion of the test is %s to fail due to the detected SKU.", (fExpected) ? L"not expected" : L"expected");
		HRESULT hr = LOG_FAILED_HR(TypeString((BSTR)L"^(%(+({TAB}{TAB})))", 1000, FALSE));
		if( SUCCEEDED(hr) )
		{
			LogTestInfoW(__FUNCTIONW__, L"Checking that the Flip task swap window has not reappeared...");
			hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name = '{0}' && Role = 'list'", resKeyTaskSwitching));
			LogTestInfoW(__FUNCTIONW__, L"The query for NOT detecting the Task Switching Window as an expected result is %s.", ( FAILED(hr) ) ? L"SUCCEEDED" : L"FAILED");
			if( SUCCEEDED(hr) )
			{
				pwszResultInfo = L"Failed on checking that the Flip task swap window would not reappear per the resolution of Windows OS Bug 1428505.";
				hr = E_FAIL;
			}
			else
				hr = NOERROR;
			LOG_FAILED_HR(TypeString((BSTR)L"{ENTER}", 1000, FALSE));
			LogTestInfoW(__FUNCTIONW__, L"Checking that Internet Explorer is not the last window on top with focus...");
			hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name = '!!<NOMATCH>!!MSN.com - {0}' && Role = 'window'", resKeyWindowsInternetExplorer));
			LogTestInfoW(__FUNCTIONW__, L"The query ID for Internet Explorer of course failed as an expected success result. The status is %s.", ( FAILED(hr) ) ? L"SUCCEEDED" : L"FAILED");
			if( SUCCEEDED(hr) )
			{
				pwszResultInfo = L"Failed on Checking that Internet Explorer is not the last window on top with focus per the resolution of Windows OS Bug 1428505.";
				LOG_FAILED_HR(WOWFromPartialQueryId(L";Name = '!!<NOMATCH>!!MSN.com - {0}' && Role = 'window';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyWindowsInternetExplorer, resKeyClose));
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{1}' && ClassName => 'IEFrame';[VisibleOnly]Role = 'title bar' && ClassName = 'IEFrame';[VisibleOnly]Name = '{0}' && Role = 'push button'", resKeyClose, (wchar_t*) cmplxKeyMSNDotcomDashWindowS));
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				VerifyDWM_4BTNComboDisabled(pvReserved);
			}
			else
				hr = NOERROR;
			//LOG_FAILED_HR(GetScreenElementInfo(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, stateDescription, MAX_VALUE_LENGTH));
			//hr = ( NULL != wcspbrk(stateDescription, stateComparison) ) ? NOERROR : E_FAIL;
			//LogTestInfoW(__FUNCTIONW__, L"The state description is %s, and state comparison is %s.", (NULL == stateDescription) ? L"NULL POINTER" : stateDescription, stateComparison);
			//if( SUCCEEDED(hr) )
			//{
			//	LogTestInfoW(__FUNCTIONW__, L"The Four-Button-KeyCombination test has failed due to either activating the");
			//	LogTestInfoW(__FUNCTIONW__, L"Flip task swap window or detecting the last Window on top - Internet Explorer.");
			//	pwszResultInfo = L"Failed to verify Ctrl+Alt+Shift+Tab Flip-Backward in sticky mode is not enabled.";
			//	hr = E_FAIL;
			//}
			//else
			//	hr = NOERROR;
		}
		else
		{
			pwszResultInfo = L"Failed on call to TypeString((BSTR)L\"^(%(+({TAB}{TAB})))\", 1000, FALSE).";
			hr = E_FAIL;
		}
		if( !fExpected && unsupportedSKU != NULL )
		{
			pwszResultInfo = L"An unsupported SKU was detected and found that DWM feature is not present.";
			hr = NOERROR;
		}
		BOOL bfinalResult = SUCCEEDED(hr);
		LogTestInfoW(__FUNCTIONW__,
			L"Unit test function VerifyDWM_AltTabVisuals() has exited with error status: %s",
			bfinalResult ? L"0" : L"-1" );
		LogTestResultW(bfinalResult, __FUNCTIONW__, pwszResultInfo);
		return hr;
	  }
		__except(ExceptionFilter(GetExceptionCode(), GetExceptionInformation()))
      {
            LogTestInfoW(__FUNCTIONW__, L"Failing due to an exception.");
            return E_FAIL;
      }
	} // End of STDAPI VerifyDWM_4BTNComboDisabled(LPVOID pvReserved)

	// Helper function that sets and returns the QueryID needed to properly
	// close a Windows Explorer window by RPF clicking its close button.
	wchar_t* SetCloseWindowButtonQueryID(wchar_t *returnBuffer, UINT cch)
	{
		// QueryID manipulation variables
		wchar_t temp[MAX_PATH],
			queryID[1024];
		// Set expandedWinDir environment variable expansion
		LogTestInfoW(__FUNCTIONW__, L"Calling ExpandEnvironmentStringsW(L\"windir\", temp, MAX_PATH)");
		DWORD numLetters = ExpandEnvironmentStringsW(L"%userprofile%", temp, MAX_PATH);
		LogTestInfoW(__FUNCTIONW__, L"End calling ExpandEnvironmentStringsW(L\"windir\", temp, MAX_PATH)");
		if( 0 == (int)numLetters )
		{
			LogTestBeginW(__FUNCTIONW__, L"Failed to expand environment variable %%userprofile%%");
			return NULL;
		}
		wcscat_s(temp, MAX_PATH, L"\\Documents");
		// Copy back the complete expanded %userprofile%\Documets path and set it to a LanguageNeutralString
		LanguageNeutralString neutral(temp);
		wcscat_s(queryID, 1024, L"##;AccessibleName = '%s' && ClassName => 'ToolbarWindow32';[VisibleOnly]Name = '%s' && Role = 'tool bar';[VisibleOnly]Name = '%s' && Role = 'push button'##");
		wprintf((const wchar_t *)queryID, resKeyRunningApolications, resKeyRunningApolications, neutral);
		LogTestInfoW(__FUNCTIONW__, L"Windows Explorer close button QueryID is %s.", queryID);
		wcscat_s(returnBuffer, MAX_PATH, queryID);
		return returnBuffer;
	}

	/*
	//[Description]
	//Desktop Window Manager (DWM) - An upgrade to the venerable user32 window management system that includes composition, glass, blur, 3D animated effects, window thumbnails (via an API), among other goodness.
	//Verify that taskbar thumbnails  is available  in Home Premium, Business, Enterprise and Ultimate SKUs
	//[SKU information]
	//Supported SKUS: HP, Business, Enterprise and Ultimate
	//Unsupported SKUS: Starter, HB
	//[EntryPoints]
	//[Steps]
	//		1. open 2-3 windows (IE, explorer, Notepad, CMD, WMP in skin-mode)
	//		2. Hover over taskbar button
	//[Expected results]
	//Pass:
	//Thumbnails appear in Home Premium, Business, Enterprise and Ultimate SKUs
	//Help related to Thumbnails is available on supported SKUs.
	//Fail:
	//Thumbnails appears in starter or Home Basic
	//Help related to Thumbnails is available on unsupported SKUs.
	//[SLAPI/SDP]
	//SLAPI
	//[Additional Info]
	//- DWM Service, Productivity, Aeroglass and Animation Supported SKUs: Home Premium, Business, Enterprise, Ultimate
	//- DWM Service, Visual Quality Supported SKUs : Home Basic
	//- Unsupported SKUs: Starter
	//[Binaries]
	//N/A SLAPI diff
	*/
	STDAPI VerifyDWM_TaskbarThumbNails(LPVOID pvReserved)
	{
		HRESULT hr = E_FAIL;
		wchar_t *pwszResultInfo = NULL;
		BOOL fExpected;
		__try
		{
			CloseExcessWindows();
			SetRobustnessLevel( 1 );

			LogTestBeginW(__FUNCTIONW__, L"Verifing that WDM thumbnails on task bar feature can be viewer on a supported SKU.");
			fExpected = IsDesktopWindowManagerExpected();
			// Used to pass flow of control to after the end of the while loop if a failue occurs using break statements.
			// This also allows the loop to be restarted with a continue statement if required.
			while( TRUE )
			{
				// Left Button Click - "push button" named "Start" and "All Programs" in window "Start"
				LogTestInfoW(__FUNCTIONW__, L"Attempting to open START->ALL PROGRAMS...");
				if ( FAILED(hr = LOG_FAILED_HR(OpenAllPrograms())) )
				hr = LOG_FAILED_HR(OpenAllPrograms());
				if( SUCCEEDED(hr) )
					hr = NOERROR;
				else
				{
					pwszResultInfo = L"Failed to open START->ALL PROGRAMS.";
					hr = E_FAIL;
					break;
				}

				// Left Button Click - "menu item" named "Internet Explorer" in window "Start Menu"
				LogTestInfoW(__FUNCTIONW__, L"Attempting to open Internet Explorer...");
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(STARTMENU_INTERNET_EXPLORER));
				if( FAILED(hr) )
					hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'DV2ControlHost';Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyInternetExplorer));
				if( FAILED(hr) )
					hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyIEAlternate));
				if( SUCCEEDED(hr) )
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					hr = NOERROR;
				}
				else
				{
					pwszResultInfo = L"Failed to open Internet Explorer, remaining tests skipped.";
					hr = NOERROR;
					break;
				}
				Sleep((DWORD)3000);
				// Left Button Click - "push button" named "Start" and "All Programs" in window "Start"
				LogTestInfoW(__FUNCTIONW__, L"Attempting to open START->ALL PROGRAMS...");
				if ( FAILED(hr = LOG_FAILED_HR(OpenAllPrograms())) )
					hr = LOG_FAILED_HR(OpenAllPrograms());
				if( SUCCEEDED(hr) )
					hr = NOERROR;
				else
				{
					pwszResultInfo = L"Failed to open START->ALL PROGRAMS.";
					hr = E_FAIL;
					break;
				}
				// Expand Item - "outline item" named "Accessories"
				LogTestInfoW(__FUNCTIONW__, L"Attempting to expand Accessories start menu item...");
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(STARTMENU_ACCESSORIES));
				if( SUCCEEDED(hr) )
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					hr = NOERROR;
				}
				else
				{
					pwszResultInfo = L"Failed to expand Accessories start menu item.";
					hr = E_FAIL;
					break;
				}
				// Left Button Click - "menu item" named "Windows Explorer" in window "Start Menu"
				LogTestInfoW(__FUNCTIONW__, L"Attempting to launch Windows Explorer...");
				LOG_FAILED_HR(WOWGlobalizeQueryId((PWSTR)szGlobalQuery, 1024, L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyWindowsExplorer));
				hr = LOG_FAILED_HR(WOWFromPartialQueryId((PCWSTR)szGlobalQuery));
				if( SUCCEEDED(hr) )
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					hr = NOERROR;
				}
				else
				{
					pwszResultInfo = L"Failed to launch Windows Explorer.";
					hr = E_FAIL;
					break;
				}
				Sleep((DWORD)3000);
				// Left Button Click - "push button" named "Start" and "All Programs" in window "Start"
				LogTestInfoW(__FUNCTIONW__, L"Attempting to open START->ALL PROGRAMS...");
				if ( FAILED(hr = LOG_FAILED_HR(OpenAllPrograms())) )
					hr = LOG_FAILED_HR(OpenAllPrograms());
				if( SUCCEEDED(hr) )
					hr = NOERROR;
				else
				{
					pwszResultInfo = L"Failed to open START->ALL PROGRAMS.";
					hr = E_FAIL;
					break;
				}
				// Expand Item - "outline item" named "Accessories"
				LogTestInfoW(__FUNCTIONW__, L"Attempting to expand Accessories start menu item...");
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(STARTMENU_ACCESSORIES));
				if( SUCCEEDED(hr) )
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					hr = NOERROR;
				}
				else
				{
					pwszResultInfo = L"Failed to expand Accessories start menu item.";
					hr = E_FAIL;
					break;
				}
				// Left Button Click - "menu item" named "Notepad" in window "Start Menu"
				LogTestInfoW(__FUNCTIONW__, L"Attempting to launch Notepad...");
				LOG_FAILED_HR(WOWGlobalizeQueryId((PWSTR)szGlobalQuery, 1024, L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyNotepad));
				hr = LOG_FAILED_HR(WOWFromPartialQueryId((PCWSTR)szGlobalQuery));
				if( SUCCEEDED(hr) )
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					hr = NOERROR;
				}
				else
				{
					pwszResultInfo = L"Failed to launch Notepad.";
					hr = E_FAIL;
					break;
				}
				Sleep((DWORD)3000);
				// Start Dragging - "list" named "Desktop" in window "Program Manager"
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'Progman';ControlId = '1';[VisibleOnly]Role = 'list'", langNeutralProgramManager));
				if( SUCCEEDED(hr) )
					LOG_FAILED_HR(StartDragging(CLICKABLE_POINT));
					// Stop Dragging - "push button" named "MSN.com - WindowS Internet ExBlorer" in window "TaskBar"
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";AccessibleName = '{0}' && ClassName => 'ToolbarWindow32';[VisibleOnly]Name = '{0}' && Role = 'tool bar';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyRunningApolications, (wchar_t*) cmplxKeyMSNDotcomDashWindowS));
				if( SUCCEEDED(hr) )
				{
					hr = LOG_FAILED_HR(StopDragging(CLICKABLE_POINT, 500));
					Sleep((DWORD)5000);
					if( FAILED(hr) )
					{
						pwszResultInfo = L"Failed to activate Internet Explorer taskbar thumbnail.";
						hr = E_FAIL;
						break;
					}
					else
						hr = NOERROR;
				}
				// Start Dragging - "list" named "Desktop" in window "Program Manager"
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'Progman';ControlId = '1';[VisibleOnly]Role = 'list'", langNeutralProgramManager));
				if( SUCCEEDED(hr) )
					LOG_FAILED_HR(StartDragging(CLICKABLE_POINT));

				// Stop Dragging - "push button" named "%userprofile%\\Documents" in window "TaskBar"
				wchar_t *queryID = SetCloseWindowButtonQueryID((wchar_t*)pvReserved, MAX_PATH);
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(queryID));
				if( SUCCEEDED(hr) )
				{
					hr = LOG_FAILED_HR(StopDragging(CLICKABLE_POINT, 500));
					Sleep((DWORD)5000);
					if( FAILED(hr) )
					{
						pwszResultInfo = L"Failed to activate Windows Explorer taskbar thumbnail.";
						hr = E_FAIL;
						break;
					}
					else
						hr = NOERROR;
				}
				// Start Dragging - "list" named "Desktop" in window "Program Manager"
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'Progman';ControlId = '1';[VisibleOnly]Role = 'list'", langNeutralProgramManager));
				if( SUCCEEDED(hr) )
					StartDragging(CLICKABLE_POINT);
				// Stop Dragging - "push button" named "Untitled - Notepad" in window "TaskBar"
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";AccessibleName = '{0}' && ClassName => 'ToolbarWindow32';[VisibleOnly]Name = '{0}' && Role = 'tool bar';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyRunningApolications, (wchar_t*) cmplxKeyUntitledDashNotepad));
				if( SUCCEEDED(hr) )
				{
					hr = LOG_FAILED_HR(StopDragging(CLICKABLE_POINT, 500));
					Sleep((DWORD)5000);
					if( FAILED(hr) )
					{
						pwszResultInfo = L"Failed to activate Notepad taskbar thumbnail.";
						hr = E_FAIL;
						break;
					}
					else
						hr = NOERROR;
				}
				// Close Notepad
				LogTestInfoW(__FUNCTIONW__, L"Attempting to close Notepad...");
				LOG_FAILED_HR(LeftClickUntilGone(CLOSE_WINDOW(cmplxKeyUntitledDashNotepad,L"Notepad")));
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'Notepad';Role = 'title bar' && ClassName = 'Notepad';Name = '{1}' && Role = 'push button'", (wchar_t*) cmplxKeyUntitledDashNotepad, resKeyClose));
				if( SUCCEEDED(hr) )
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				else
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed to close Notepad.");
					hr = E_FAIL;
				}
					LogTestInfoW(__FUNCTIONW__, L"Attempting to shut down Notepad's Don't Save dialogue...");
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => '#32770';[VisibleOnly]Name = '{0}' && Role = 'pane';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyNotepad, resKeyDontSave));
				if( SUCCEEDED(hr) )
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					// Close Windows Explorer
				LogTestInfoW(__FUNCTIONW__, L"Attempting to close Windows Explorer...");
				LOG_FAILED_HR(LeftClickUntilGone(CLOSE_EXPLORER(resKeyDocuments)));
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{1}' && ClassName => 'CabinetWClass';Role = 'title bar' && ClassName = 'CabinetWClass';Name = '{0}' && Role = 'push button'", resKeyClose, langNeutralCClnBslshUsersBslshAdmini));
				if( SUCCEEDED(hr) )
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				else
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed to close Windows Explorer.");
					hr = E_FAIL;
				}
				
				// Close Internet Explorer
				LogTestInfoW(__FUNCTIONW__, L"Attempting to close Internet Explorer...");
				LOG_FAILED_HR(LeftClickUntilGone(CLOSE_WINDOW(resKeyInternetExplorer,L"IEFrame")));
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{1}' && ClassName => 'IEFrame';[VisibleOnly]Role = 'title bar' && ClassName = 'IEFrame';[VisibleOnly]Name = '{0}' && Role = 'push button'", resKeyClose, (wchar_t*) cmplxKeyMSNDotcomDashWindowS));
				if( SUCCEEDED(hr) )
				{
					if( !SUCCEEDED(LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT))) )
					{
						LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => '#32770';Role = 'title bar' && ClassName = '#32770';Name = '{1}' && Role = 'push button'", resKeyMicrosoftDashPhishingfilt, resKeyClose));
						LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
						LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{1}' && ClassName => 'IEFrame';[VisibleOnly]Role = 'title bar' && ClassName = 'IEFrame';[VisibleOnly]Name = '{0}' && Role = 'push button'", resKeyClose, (wchar_t*) cmplxKeyMSNDotcomDashWindowS));
						LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					}
				}
				else
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed to close Internet Explorer.");
					hr = E_FAIL;
				}
				if (!fExpected && unsupportedSKU != NULL)
				{
					pwszResultInfo = L"%s unsupported was SKU detected, taskbar thumbnails are not expected and were not found.";
					hr = NOERROR;
					break;
				}
				else if (Get2DScore() >= 2 && unsupportedSKU == NULL)
				{
					pwszResultInfo = L"Taskbar thumbnails are expected, were tested as found, and verified as functioning.";
					hr = NOERROR;
					break;
				}
				else
				{
					pwszResultInfo = L" General taskbar thumbnails test detection failure has occured.";
					hr = E_FAIL;
						break;
				}
				pwszResultInfo = L"All test operations succeeded with no errors.";
				break; // No matter what, when the execution stack pointer reaches this position, break out! of the while() loop.
			} // End while( TRUE )
			BOOL bfinalResult = SUCCEEDED(hr);
			LogTestInfoW(__FUNCTIONW__,
				L"Unit test function VerifyDWM_AltTabVisuals() has exited with error status: %s",
				bfinalResult ? L"0" : L"-1" );
			LogTestResultW(bfinalResult, __FUNCTIONW__, pwszResultInfo, unsupportedSKU);
			return hr;
		}
		__except(ExceptionFilter(GetExceptionCode(), GetExceptionInformation()))
		{
            LogTestInfoW(__FUNCTIONW__, L"Failing due to an exception.");
            return E_FAIL;
		}
	} // End STDAPI STDAPI VerifyDWM_TaskbarThumbNails(LPVOID pvReserved)

	///*
	//[Description]
	//Desktop Window Manager (DWM) - An upgrade to the venerable user32 window management system that includes composition, glass, blur, 3D animated effects, window thumbnails (via an API), among other goodness.
	//Verify that rolodex is available  in Home Premium, Business, Enterprise and Ultimate
	//[SKU information]
	//Supported SKUS: Home Premium, Business, Enterprise and Ultimate
	//Unsupported SKUS: Starter, HB
	//[EntryPoints]
	//[Steps]
	//1. Open a few windows (IE, explorer, Notepad)
	//2. Press Windows Key + Tab keys
	//3. Rolodex in reverse: Windows + Shift + Tab keys
	//4. Sticky mode : Press CTRL+WIN+Tab keys
	//5. Sticky Rolodex in reverse: CTRL+WIN+SHIFT+Tab keys (similar to previous, but when holding SHIFT it reverses)
	//[Expected results]
	//Pass:
	//Rolodex is available in Home Premium, Business, Enterprise and Ultimate SKUs
	//Sticky mode works
	//Help related to Flip3d is available on supported SKUs.
	//Fail:
	//Rolodex is available in Starter or Home Basic or Rolodex is not in Home Premium, Business, Enterprise and Ultimate SKUs
	//Sticky mode fails
	//Help related to Flip3d is available on unsupported SKUs.
	//[SLAPI/SDP]
	//SLAPI
	//[Additional Info]
	//- DWM Service, Productivity, Aeroglass and Animation Supported SKUs: Home Premium, Business, Business, Enterprise, Ultimate
	//- DWM Service, Visual Quality Supported SKUs : Home Basic
	//- Unsupported SKUs: Starter
	//*/
	STDAPI VerifyDWM_RolodexFlip3D(LPVOID pvReserved)
	{
		BOOL fExpected = FALSE;
		HRESULT hr = E_FAIL;
		wchar_t *pwszResultInfo = NULL,
				stateDescription[1024],
				*stateComparison = L"sizeable,moveable,focusable";
		__try
		{
			CloseExcessWindows();
			SetRobustnessLevel( 1 );

			LogTestBeginW(__FUNCTIONW__, L"Verifing that WDM Flip Alt+Tab feature can be used on a supported SKU.");
			fExpected = IsDesktopWindowManagerExpected();
			// Used to pass flow of control to after the end of the while loop if a failue occurs using break statements.
			// This also allows the loop to be restarted with a continue statement if required.
			while( TRUE )
			{
				// Left Button Click - "push button" named "Start" and "All Programs" in window "Start"
				LogTestInfoW(__FUNCTIONW__, L"Attempting to open START->ALL PROGRAMS...");
				if ( FAILED(hr = LOG_FAILED_HR(OpenAllPrograms())) )
					hr = LOG_FAILED_HR(OpenAllPrograms());
				if( SUCCEEDED(hr) )
					hr = NOERROR;
				else
				{
					pwszResultInfo = L"Failed to open START->ALL PROGRAMS.";
					hr = E_FAIL;
					break;
				}
				// Left Button Click - "menu item" named "Internet Explorer" in window "Start Menu"
				LogTestInfoW(__FUNCTIONW__, L"Attempting to open Internet Explorer...");
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(STARTMENU_INTERNET_EXPLORER));
				if( FAILED(hr) )
					hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'DV2ControlHost';Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyInternetExplorer));
				if( FAILED(hr) )
					hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyIEAlternate));
				if( SUCCEEDED(hr) )
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					hr = NOERROR;
				}
				else
				{
					pwszResultInfo = L"Failed to open Internet Explorer, remaining tests skipped.";
					hr = NOERROR;
					break;
				}
				Sleep((DWORD)3000);
				// Left Button Click - "push button" named "Start" and "All Programs" in window "Start"
				LogTestInfoW(__FUNCTIONW__, L"Attempting to open START->ALL PROGRAMS...");
				if ( FAILED(hr = LOG_FAILED_HR(OpenAllPrograms())) )
					hr = LOG_FAILED_HR(OpenAllPrograms());
				if( SUCCEEDED(hr) )
					hr = NOERROR;
				else
				{
					pwszResultInfo = L"Failed to open START->ALL PROGRAMS.";
					hr = E_FAIL;
					break;
				}
				// Expand Item - "outline item" named "Accessories"
				LogTestInfoW(__FUNCTIONW__, L"Attempting to expand Accessories start menu item...");
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(STARTMENU_ACCESSORIES));
				if( SUCCEEDED(hr) )
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					hr = NOERROR;
				}
				else
				{
					pwszResultInfo = L"Failed to expand Accessories start menu item.";
					hr = E_FAIL;
					break;
				}
				// Left Button Click - "menu item" named "Windows Explorer" in window "Start Menu"
				LogTestInfoW(__FUNCTIONW__, L"Attempting to launch Windows Explorer...");
				LOG_FAILED_HR(WOWGlobalizeQueryId((PWSTR)szGlobalQuery, 1024, L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyWindowsExplorer));
				hr = LOG_FAILED_HR(WOWFromPartialQueryId((PCWSTR)szGlobalQuery));
				if( SUCCEEDED(hr) )
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					hr = NOERROR;
				}
				else
				{
					pwszResultInfo = L"Failed to launch Windows Explorer.";
					hr = E_FAIL;
					break;
				}
				Sleep((DWORD)3000);
				// Left Button Click - "push button" named "Start" and "All Programs" in window "Start"
				LogTestInfoW(__FUNCTIONW__, L"Attempting to open START->ALL PROGRAMS...");
				if ( FAILED(hr = LOG_FAILED_HR(OpenAllPrograms())) )
					hr = LOG_FAILED_HR(OpenAllPrograms());
				if( SUCCEEDED(hr) )
					hr = NOERROR;
				else
				{
					pwszResultInfo = L"Failed to open START->ALL PROGRAMS.";
					hr = E_FAIL;
					break;
				}
				// Expand Item - "outline item" named "Accessories"
				LogTestInfoW(__FUNCTIONW__, L"Attempting to expand Accessories start menu item...");
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(STARTMENU_ACCESSORIES));
				if( SUCCEEDED(hr) )
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					hr = NOERROR;
				}
				else
				{
					pwszResultInfo = L"Failed to expand Accessories start menu item.";
					hr = E_FAIL;
					break;
				}
				// Left Button Click - "menu item" named "Notepad" in window "Start Menu"
				LogTestInfoW(__FUNCTIONW__, L"Attempting to launch Notepad...");
				LOG_FAILED_HR(WOWGlobalizeQueryId((PWSTR)szGlobalQuery, 1024, L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyNotepad));
				hr = LOG_FAILED_HR(WOWFromPartialQueryId((PCWSTR)szGlobalQuery));
				if( SUCCEEDED(hr) )
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					hr = NOERROR;
				}
				else
				{
					pwszResultInfo = L"Failed to launch Notepad.";
					hr = E_FAIL;
					break;
				}
				Sleep((DWORD)3000);
				LogTestInfoW(__FUNCTIONW__, L"Verifying DWM Rolodex Flip3D can be activated...");
				LogTestInfoW(__FUNCTIONW__, L"This portion of the DWM Rolodex Flip3D test is %s to fail due to the detected SKU.%s%s",
					(fExpected) ? L"not expected" : L"expected", (NULL == unsupportedSKU) ? L"" : L"Flip3D is not enabled on SKU %s.",
					(NULL == unsupportedSKU) ? L"" : unsupportedSKU);
				Sleep((DWORD)5000);
				LogTestInfoW(__FUNCTIONW__, L"Begin activating test SendKey set to activate Rolodex Flip3D screen.");
				keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_LCONTROL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				Sleep((DWORD)5000);
				keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				keybd_event(VK_LCONTROL, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				Sleep((DWORD)5000);
				LogTestInfoW(__FUNCTIONW__, L"Attempting to detect Rolodex Flip3D screen presence using queryID \";AccessibleName = '{0}' && ClassName => 'Flip3D';[VisibleOnly]Name = '{0}' && Role = 'list';Name = '{1}' && Role = 'list item'\", resKeyFlip3D, langNeutralProgramManager");
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";AccessibleName = '{0}' && ClassName => 'Flip3D';[VisibleOnly]Name = '{0}' && Role = 'list';Name = '{1}' && Role = 'list item'", resKeyFlip3D, langNeutralProgramManager));
				if( FAILED(hr) )
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed to correctly detect Rolodex Flip3D screen presence using queryID \";AccessibleName = '{0}' && ClassName => 'Flip3D';[VisibleOnly]Name = '{0}' && Role = 'list';Name = '{1}' && Role = 'list item'\", resKeyFlip3D, langNeutralProgramManager");
					pwszResultInfo = L"Failed to correctly detect Rolodex Flip3D screen presence using any known RPF queryID.";
					hr = E_FAIL;
				}
				LogTestInfoW(__FUNCTIONW__, L"Attempting to detect Rolodex Flip3D screen using queryID \";AccessibleName = '{0}' && ClassName => 'Flip3D';[VisibleOnly]Name = '{0}' && Role = 'list'\", resKeyFlip3D");
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";AccessibleName = '{0}' && ClassName => 'Flip3D';[VisibleOnly]Name = '{0}' && Role = 'list'", resKeyFlip3D));
				if( FAILED(hr) )
					LogTestInfoW(__FUNCTIONW__, L"Failed to correctly detect Rolodex Flip3D screen presence using queryID \";AccessibleName = '{0}' && ClassName => 'Flip3D';[VisibleOnly]Name = '{0}' && Role = 'list'\", resKeyFlip3D");
				LOG_FAILED_HR(TypeString((BSTR)L"{LEFT}{RIGHT}", 2000, FALSE));
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				LogTestInfoW(__FUNCTIONW__, L"End activating test SendKey set to activate Rolodex Flip3D screen.");
				if( FAILED(hr) )
					break;

				LogTestInfoW(__FUNCTIONW__, L"Testing the key combination of Winkey+Tab+Tab to flip forward the Rolodex Flip3D screen.");
				LogTestInfoW(__FUNCTIONW__, L"To pass this test portion, the last window detected ontop with focus must be Windows Explorer.");
				Sleep((DWORD)5000);
				keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				Sleep((DWORD)5000);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				Sleep((DWORD)5000);
				keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				Sleep((DWORD)5000);
				wchar_t *userprofile = (wchar_t*)malloc(sizeof(wchar_t[MAX_PATH]));
				DWORD numLetters = ExpandEnvironmentStringsW(L"%userprofile%", (LPWSTR)userprofile, MAX_PATH);
				if( 0 == (int)numLetters )
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed to expand environment variable %%userprofile%%");
					return NULL;
				}
				LogTestInfoW(__FUNCTIONW__, L"Variable userprofile is set to %s.", userprofile);
				wchar_t queryID[1024];
				LOG_FAILED_HR(GlobalizeQueryId(queryID, 1024, L";Name => '{0}\\Documents' && Role = 'window'", userprofile));
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(queryID));
				if( SUCCEEDED(hr) )
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					hr = NOERROR;
				}
				else
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed on Winkey+Tab+Tab operation. Variable queryID is %s.", queryID);
					pwszResultInfo = L"Failed while detecting correct operation of Winkey+Tab+Tab Flip-Backward.";
					hr = E_FAIL;
					break;
				}

				LogTestInfoW(__FUNCTIONW__, L"Testing the key combination of Winkey+Shift+Tab to flip backward the Rolodex Flip3D screen.");
				LogTestInfoW(__FUNCTIONW__, L"To pass this test portion, the last window detected ontop with focus must be Notepad.");
				Sleep((DWORD)5000);
				keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				Sleep((DWORD)5000);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				Sleep((DWORD)5000);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				Sleep((DWORD)5000);
				keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				Sleep((DWORD)5000);
				keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				Sleep((DWORD)5000);
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name = '{0}' && Role = 'window'", (wchar_t*) cmplxKeyUntitledDashNotepad));
				if( SUCCEEDED(hr) )
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					hr = NOERROR;
				}
				else
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed on Winkey+Shift+Tab operation. Variable queryID is %s.", queryID);
					pwszResultInfo = L"Failed while detecting correct operation of Winkey+Tab+Tab Flip-Backward.";
					hr = E_FAIL;
					break;
				}

				LogTestInfoW(__FUNCTIONW__, L"Testing the key combination of Winkey+Ctrl+Tab to flip backward the Rolodex Flip3D screen in sticky mode.");
				LogTestInfoW(__FUNCTIONW__, L"To pass this test portion, the last window detected ontop with focus must be Notepad.");
				Sleep((DWORD)5000);
				keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_LCONTROL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				keybd_event(VK_LCONTROL, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				Sleep((DWORD)5000);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				Sleep((DWORD)5000);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				Sleep((DWORD)5000);
				keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				Sleep((DWORD)5000);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				Sleep((DWORD)5000);
				LOG_FAILED_HR(TypeString((BSTR)L"{ENTER}", 5000, FALSE));
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name = '{0}' && Role = 'window'", (wchar_t*) cmplxKeyUntitledDashNotepad));
				if( SUCCEEDED(hr) )
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					hr = NOERROR;
				}
				else
				{
					LogTestInfoW(__FUNCTIONW__, L"Failed on Winkey+Shift+Tab operation. Variable queryID is %s.", queryID);
					pwszResultInfo = L"Failed while detecting correct operation of Winkey+Tab+Tab Flip-Backward.";
					hr = E_FAIL;
					break;
				}
				LogTestInfoW(__FUNCTIONW__, L"Testing that the key combination of Winkey+Ctrl+Shift+Tab to flip backward in sticky mode DOES NOT activate Rolodex Flip3D per Windows OS bug# 1428505.");
				LogTestInfoW(__FUNCTIONW__, L"To pass this final test, this four button key combination must fail (expected result) to activate Rolodex Flip3D screen.");
				Sleep((DWORD)5000);
				keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_LCONTROL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
				keybd_event(VK_TAB, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				Sleep((DWORD)5000);
				// Detect presence of Rolodex Flip3D?
				hr = E_FAIL;
				LogTestInfoW(__FUNCTIONW__, L"Attempting to detect Rolodex Flip3D screen presence using queryID \";AccessibleName = '{0}' && ClassName => 'Flip3D';[VisibleOnly]Name = '{0}' && Role = 'list';Name = '{1}' && Role = 'list item'\", resKeyFlip3D, langNeutralProgramManager");
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";AccessibleName = '{0}' && ClassName => 'Flip3D';[VisibleOnly]Name = '{0}' && Role = 'list';Name = '{1}' && Role = 'list item'", resKeyFlip3D, langNeutralProgramManager));
				if( FAILED(hr) )
				{
					LogTestInfoW(__FUNCTIONW__, L"Rolodex Flip3D screen presence was not detected. Try again to detect with another query...");
					hr = NOERROR;
				}
				else
				{
					pwszResultInfo = L"Rolodex Flip3D screen presence was detected.";
					hr = E_FAIL;
					break;
				}
				LogTestInfoW(__FUNCTIONW__, L"Attempting to detect Rolodex Flip3D screen using queryID \";AccessibleName = '{0}' && ClassName => 'Flip3D';[VisibleOnly]Name = '{0}' && Role = 'list'\", resKeyFlip3D");
				hr = E_FAIL;
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";AccessibleName = '{0}' && ClassName => 'Flip3D';[VisibleOnly]Name = '{0}' && Role = 'list'", resKeyFlip3D));
				if( FAILED(hr) )
				{
					LogTestInfoW(__FUNCTIONW__, L"Rolodex Flip3D screen presence was not detected.");
					hr = NOERROR;
				}
				else
				{
					pwszResultInfo = L"Rolodex Flip3D screen presence was detected.";
					hr = E_FAIL;
					break;
				}
				keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				keybd_event(VK_LCONTROL, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);

				pwszResultInfo = L"All test operations succeeded with no errors.";
				break; // No matter what, when the execution stack pointer reaches this position, break out! of the while() loop.
			} // End while( TRUE )
			if( !fExpected && unsupportedSKU != NULL )
			{
				pwszResultInfo = L"An unsupported SKU was detected and found that DWM feature is not present.";
				hr = NOERROR;
			}
			BOOL bfinalResult = SUCCEEDED(hr);
			LogTestInfoW(__FUNCTIONW__,
				L"Unit test function VerifyDWM_AltTabVisuals() has exited with error status: %s",
				bfinalResult ? L"0" : L"-1" );
			LogTestResultW(bfinalResult, __FUNCTIONW__, pwszResultInfo);
			return hr;
		}
		__except(ExceptionFilter(GetExceptionCode(), GetExceptionInformation()))
		{
            LogTestInfoW(__FUNCTIONW__, L"Failing due to an exception.");
            return E_FAIL;
		}
	} // End of STDAPI VerifyDWM_RolodexFlip3D(LPVOID pvReserved)

	// Helper function to close all opened and excessive windows that may or may not be left open.
	HRESULT CloseExcessWindows() // test specific, ensure a clean state; can be made better with RPF 12+
	{
		// Maximize all windows for termination (Winkey+Shift+M key combination)
		keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
		keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
		keybd_event(0x4D, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
		Sleep((DWORD)1000);
		keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		keybd_event(0x4D, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
		keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
		keybd_event(0x4D, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
		Sleep((DWORD)1000);
		keybd_event(VK_LWIN, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		keybd_event(0x4D, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);

		HRESULT hr = LOG_FAILED_HR(GlobalizeQueryId(szGlobalQuery, 1024, CLASSIC_APPEARANCE_CLOSE));
		hr = LOG_FAILED_HR(LeftClickUntilGone(szGlobalQuery));
		hr = LOG_FAILED_HR(GlobalizeQueryId(szGlobalQuery, 1024, CPL_CHANGE_YOUR_COLOR_SCHEME_CLOSE));
		hr = LOG_FAILED_HR(LeftClickUntilGone(szGlobalQuery));
		hr = LOG_FAILED_HR(GlobalizeQueryId(szGlobalQuery, 1024, CPL_PERSONALIZATION_CLOSE));
		hr = LOG_FAILED_HR(LeftClickUntilGone(szGlobalQuery));
		hr = LOG_FAILED_HR(GlobalizeQueryId(szGlobalQuery, 1024, CPL_CLOSE_BTN));
		hr = LOG_FAILED_HR(LeftClickUntilGone(szGlobalQuery));
		
		// Close Notepad
		LogTestInfoW(__FUNCTIONW__, L"Attempting to close Notepad...");
		LOG_FAILED_HR(LeftClickUntilGone(CLOSE_WINDOW(cmplxKeyUntitledDashNotepad,L"Notepad")));
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'Notepad';Role = 'title bar' && ClassName = 'Notepad';Name = '{1}' && Role = 'push button'", (wchar_t*) cmplxKeyUntitledDashNotepad, resKeyClose));
		if( SUCCEEDED(hr) )
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		else
			hr = E_FAIL;

		LogTestInfoW(__FUNCTIONW__, L"Attempting to shut down Notepad's Don't Save dialogue...");
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => '#32770';[VisibleOnly]Name = '{0}' && Role = 'pane';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyNotepad, resKeyDontSave));
		if( SUCCEEDED(hr) )
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		else
			hr = E_FAIL;

		wchar_t temp[MAX_PATH];
		LogTestInfoW(__FUNCTIONW__, L"Calling ExpandEnvironmentStringsW(L\"%userprofile%\", (LPWSTR)temp, MAX_PATH)");
		DWORD numLetters = ExpandEnvironmentStringsW(L"%userprofile%", temp, MAX_PATH);
		LogTestInfoW(__FUNCTIONW__, L"End calling ExpandEnvironmentStringsW(L\"%userprofile%\", (LPWSTR)temp, MAX_PATH)");
		if( 0 == (int)numLetters )
		{
			LogTestInfoW(__FUNCTIONW__, L"Failed to expand environment variable %%windir%%");
			return E_FAIL;
		}
		wcscat_s(temp, MAX_PATH, L"\\Documents");
		// Copy back the complete expanded %userprofile%Documets path
		LanguageNeutralString neutral(temp);
		LogTestInfoW(__FUNCTIONW__, L"Variable neutral that is the name of the Windows Explorer window has the value %s.", neutral);
		// Close Windows Explorer
		LogTestInfoW(__FUNCTIONW__, L"Attempting to close Windows Explorer...");
		LOG_FAILED_HR(LeftClickUntilGone(CLOSE_EXPLORER(resKeyDocuments)));
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{1}' && ClassName => 'CabinetWClass';Role = 'title bar' && ClassName = 'CabinetWClass';Name = '{0}' && Role = 'push button'", resKeyClose, neutral));
		if( SUCCEEDED(hr) )
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		else
			hr = E_FAIL;
		
		// Close Internet Explorer
		LogTestInfoW(__FUNCTIONW__, L"Attempting to close Internet Explorer...");
		LOG_FAILED_HR(LeftClickUntilGone(CLOSE_WINDOW(resKeyInternetExplorer,L"IEFrame")));
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{1}' && ClassName => 'IEFrame';[VisibleOnly]Role = 'title bar' && ClassName = 'IEFrame';[VisibleOnly]Name = '{0}' && Role = 'push button'", resKeyClose, (wchar_t*) cmplxKeyMSNDotcomDashWindowS));
		if( SUCCEEDED(hr) )
		{
			if( !SUCCEEDED(LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT))) )
			{
				LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => '#32770';Role = 'title bar' && ClassName = '#32770';Name = '{1}' && Role = 'push button'", resKeyMicrosoftDashPhishingfilt, resKeyClose));
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{1}' && ClassName => 'IEFrame';[VisibleOnly]Role = 'title bar' && ClassName = 'IEFrame';[VisibleOnly]Name = '{0}' && Role = 'push button'", resKeyClose, (wchar_t*) cmplxKeyMSNDotcomDashWindowS));
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
			}
		}
		else
			hr = E_FAIL;
		
		// Close Wordpad
		LogTestInfoW(__FUNCTIONW__, L"Attempting to close Wordpad...");
		LOG_FAILED_HR(LeftClickUntilGone(CLOSE_WINDOW(resKeyWordPad,L"WordPadClass")));
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{1}' && ClassName => 'WordPadClass';Role = 'title bar' && ClassName = 'WordPadClass';Name = '{0}' && Role = 'push button'", resKeyClose, (wchar_t*) cmplxKeyDocumentDashWordPad));
		if( SUCCEEDED(hr) )
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		else
			hr = E_FAIL;

		return hr;
	} // End of HRESULT CloseExcessWindows()
} // End namespace DWM_BVT