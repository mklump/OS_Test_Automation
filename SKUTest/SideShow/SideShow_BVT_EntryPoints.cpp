/***************************************************************
// Description: BVT - Windows SideShow entry point verification in SKUs
// Created:     HariniD
// Verify:      Pass test case if feature is available
//              in all SKUs but Starter and Home Basic
****************************************************************/

#include <windows.h>
//#include "RPF_Constants.h"
#include "screenelement.h"
#include "LoggingFunctions.h"
#include <stdio.h>
#include "RPF_SKUDIFF.h"
#include "SKUDIFF_UTIL.h"





using namespace RPFPlayback;
using namespace SKUDiff;

LanguageNeutralString langNeutralWindowsSideShow(L"Windows SideShow Simulator - 0");
LanguageNeutralString langNeutralClose(L"Close");

/*
#define WINDOWS_SIDE_SHOW_AUX_DISPLAY		 L";Name => '{0}' && ClassName => 'MainWindow';Name = '{0}' && Role = 'client'", langNeutralWindowsSideShow
LanguageNeutralString langNeutralWindowsSideShow(L"Windows SideShow Simulator - 0");

#define WINDOWS_SIDE_SHOW_AUX_DISPLAY_CLOSE 	L";AccessibleName = '{1}' && ClassName => '#32768' && Role = 'popup menu';[VisibleOnly]Name = '{0}' && Role = 'menu item'", langNeutralClose, resKeyContext
LanguageNeutralString langNeutralClose(L"Close");


#define WINDOWS_SIDE_SHOW_WINDOWS_MAIL  	L";Name => '{0}' && ClassName => 'CabinetWClass';[VisibleOnly]Name = '{1}' && Role = 'cell';[VisibleOnly]Role = 'check box' && ClassName = 'Button'", resKeyCPLWindowsSideShow, resKeyWindowsSideShowWindowsMail 

const wchar_t* resKeyCPLWindowsSideShow = L"RKB1[];Windows SideShow;Win32String;%windir%\\system32\\auxiliarydisplaycpl.dll;1";
const wchar_t* resKeyWindowsSideShowWindowsMail = L"RKB1[];Inbox - Windows Mail;Win32String;%programfiles%\\windows mail\\windowsmailgadget.exe;1006";

#define WINDOWS_SIDE_SHOW_WMP		L";Name => '{0}' && ClassName => 'CabinetWClass';[VisibleOnly]Name = '{1}' && Role = 'cell';[VisibleOnly]Role = 'check box' && ClassName = 'Button'", resKeyCPLWindowsSideShow, resKeyWindowsSideShowWMP
const wchar_t* resKeyWindowsSideShowWMP = L"RKB1[];Windows Media Player;Win32String;%programfiles%\\windows media player\\wmpsideshowgadget.exe;1100";
*/

void closeOpenWindow(BOOL fStatus)
{
	HRESULT hr;
	LogTestInfoW(__FUNCTIONW__, L"Cleaning up...\n");

	if (!fStatus)
	{
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(CPL_CLOSE_BTN));
		if (SUCCEEDED(hr))
		{
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		}
	}
	else
	{
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(CPL_SIDESHOW_CLOSE));
		if (SUCCEEDED(hr))
		{
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		}
	}
}


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


//Verify Windows SideShow (Aux display) item in CPL
STDAPI SideShow_BVT_EntryPoints(LPVOID pvReserved)
{
	BOOL fResult = FALSE;
	BOOL fLaunched = FALSE;
	BOOL fExpected = FALSE;
	DWORD dwProductInfoType = 0;
	HRESULT hr;
	LogTestBeginW(__FUNCTIONW__, L"Beginning Windows SideShow BVT test case...");

	if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
	{
		switch (dwProductInfoType)
		{
		case PRODUCT_STARTER:
		case PRODUCT_HOME_BASIC:
		case PRODUCT_HOME_BASIC_N:
			LogTestInfoW(__FUNCTIONW__, L"Windows SideShow is NOT expected in this SKU.");
			break;
		case PRODUCT_HOME_PREMIUM:
		case PRODUCT_HOME_PREMIUM_N:
		case PRODUCT_BUSINESS:
		case PRODUCT_BUSINESS_N:
		case PRODUCT_ENTERPRISE:
		case PRODUCT_ENTERPRISE_N:
		case PRODUCT_ULTIMATE:
		case PRODUCT_ULTIMATE_N:
			fExpected = TRUE;
			LogTestInfoW(__FUNCTIONW__, L"Windows SideShow is expected in this SKU.");
			break;
		default:
			LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU.");
			break;
		}
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU.");
		return NOERROR;
	}

	if (SUCCEEDED(OpenControlPanelClassicView()))
	{
		BOOL fFoundUI = SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(CPL_ICON_WINDOWSSIDESHOW)));

		if (fFoundUI)
		{
			fFoundUI &= SUCCEEDED(LOG_FAILED_HR(DoubleClick(CLICKABLE_POINT)));
			LogTestInfoW(__FUNCTIONW__, L"%s Item", fFoundUI ? L"Found": L"Did not find");
			fLaunched = TRUE;
		}

		if (fFoundUI != fExpected)
		{
			LogTestResultW(fResult, __FUNCTIONW__, L"Windows SideShow SKU differentiated feature failed.[Current: %s | Expected: %s ]",fFoundUI ? L"Found": L"Not Found",	fExpected ? L"Found" : L"Not Found");
				closeOpenWindow(fLaunched);
			return NOERROR;
		}
		else
		{
			fResult = TRUE;
			LogTestInfoW(__FUNCTIONW__, L"Windows SideShow is differentiated correctly.");
		}
	}
	else
	{
		
		LogTestResultW(fResult, __FUNCTIONW__, L"Completed Windows SideShow BVT test case.");
		closeOpenWindow(fLaunched);
		return NOERROR;
	}


	hr = LOG_FAILED_HR(WOWFromPartialQueryId(WINDOWS_SIDE_SHOW_WINDOWS_MAIL));
	
	if (SUCCEEDED(hr))
	{
		hr = Check();
		if(FAILED(hr))
		{
			LogTestResultW(fResult, __FUNCTIONW__, L"Couldn't Find Windows Mail in Windows SideShow");
			closeOpenWindow(fLaunched);
			return NOERROR;
		}
		else
		{
			fResult=TRUE;
			Uncheck();
		}
	}

	hr = LOG_FAILED_HR(WOWFromPartialQueryId(WINDOWS_SIDE_SHOW_WMP));
	
	if (SUCCEEDED(hr))
	{
		hr = Check();
		if(FAILED(hr))
		{
			LogTestResultW(fResult, __FUNCTIONW__, L"Couldn't Find Windows Media Player in Windows SideShow");
			closeOpenWindow(fLaunched);
			return NOERROR;
		}
		else
		{
			fResult=TRUE;
			Uncheck();
		}
	}


	closeOpenWindow(fLaunched);


	LogTestResultW(fResult, __FUNCTIONW__, L"Completed Windows SideShow BVT test case.");
	return NOERROR;
}
