/// <copyright file="GroupPolicy_BVT_EntryPoints.cpp" company="Microsoft">
///  Copyright (c) Microsoft Corporation.  All rights reserved.
/// </copyright>
///
/// <summary>
///  Code for WTT WindowsShell, Job ######
///  Group Policy editor availablity
/// </summary>
///
// Complete Feb 2008, a-jomul

#include <windows.h>            //Common Windows types
//#include "rpf_constants.h"
#include "screenelement.h"  
#include "LoggingFunctions.h"
#include "rpf_SKUDIFF.h"
#include "SKUDIFF_UTIL.h"

using namespace RPFPlayback;
using namespace SKUDiff;

void CloseExcessWindows() // test specific, ensure a clean state; can be made better with RPF 12+
{
	wchar_t pszValueForlangNeutralGpeditDotmsc[512];
	LanguageNeutralString langNeutralGpeditDotmsc(L"gpedit.msc");
	ExtractResourceString(langNeutralGpeditDotmsc, pszValueForlangNeutralGpeditDotmsc, ARRAYSIZE(pszValueForlangNeutralGpeditDotmsc));
	
	wchar_t Resource[1024];
				ResourceFromMSC(L"gpedit.msc", Resource, 1024);
				LogTestInfoW(__FUNCTIONW__, L"%s", Resource);
				
	//BOOL fFoundGPEditCloseBtn = SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId()));	
				
	wchar_t szGlobalQuery[1024];
	GlobalizeQueryId(szGlobalQuery, 1024, L";Name => '{0}' && ClassName => '" L"MMCMainFrame" L"';Role = 'title bar' && ClassName = '" L"MMCMainFrame" L"';Name = '{1}' && Role = 'push button'", Resource, resKeyClose);
	//LeftClickUntilGone(szGlobalQuery);
	
		MultiLeftClickUntilGone(3,
		szGlobalQuery,
		CLOSE_GP_FAILED_OPEN_WINDOW,
		CLOSE_RUN_WINDOW);

		//GROUP_POLICY_CLOSE,
				//CLOSE_GP_SUCCEEDED_OPEN_WINDOW CLOSE_GP_FAILED_OPEN_WINDOW
	/*
	GlobalizeQueryId(szGlobalQuery, 1024, CLOSE_GP_SUCCEEDED_OPEN_WINDOW);
	LeftClickUntilGone(szGlobalQuery);
	
			
	GlobalizeQueryId(szGlobalQuery, 1024, CLOSE_RUN_WINDOW);
	LeftClickUntilGone(szGlobalQuery);
	GlobalizeQueryId(szGlobalQuery, 1024, GROUP_POLICY_CLOSE);
	LeftClickUntilGone(szGlobalQuery);
	*/
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


//    
//    Verify Group_Policy_EntryPoints 
//  
STDAPI GroupPolicy_BVT_EntryPoints(LPVOID pvReserved)
{
    BOOL	fPassed = FALSE;
    LPWSTR	pwszResultInfo = L"No Result String Set.";
	LanguageNeutralString langNeutralGpeditDotmsc(L"gpedit.msc");
	HRESULT hr;
    LogTestBeginW(__FUNCTIONW__, L"Verify Global Policy Entry Point is differentiated correctly.");    

	LogTestInfoW(__FUNCTIONW__, L"Open Run Dialog.");
	hr = LOG_FAILED_HR(FromPartialQueryId(WINDOW_DESKTOP));
	if (SUCCEEDED(hr))
	{
		//Type 'Windows Key' + 'r' to open the Run Dialog
		TypeString(L"`r");

		//Verify that Run Dialog Opened by looking for its edit box
		LogTestInfoW(__FUNCTIONW__, L"Enter 'gpedit.msc' in Run Dialog.");
		hr = LOG_FAILED_HR(FromPartialQueryId(RUN_DIALOG));
		if (SUCCEEDED(hr))
		{
			wchar_t pszValueForlangNeutralGpeditDotmsc[512];
			
			//Run Dialog is open so type 'GPEdit.msc' into edit box
			ExtractResourceString(langNeutralGpeditDotmsc, pszValueForlangNeutralGpeditDotmsc, ARRAYSIZE(pszValueForlangNeutralGpeditDotmsc));
			SetValueAsEditBox(pszValueForlangNeutralGpeditDotmsc);//, EF_DELETE_CONTENT | EF_USE_WM_SETTEXT );

			//Find the Run Dialog OK Button
			LogTestInfoW(__FUNCTIONW__, L"Click Run Dialog OK Button.");
			hr = LOG_FAILED_HR(FromPartialQueryId(RUN_DIALOG_OK_BTN));		
			if (SUCCEEDED(hr))
			{
				//Click OK button on Run Dialog to try to start GPEdit
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				
				//Set Timeout to Shorter Time Period since these objects may not exist
				//These prevents very long search periods
				//Save the original timeout period to set back to normal timeout period later
				int originalTimout = SetSearchTimeOut(10000);
	  

				wchar_t Resource[1024];
				ResourceFromMSC(L"gpedit.msc", Resource, 1024);
				LogTestInfoW(__FUNCTIONW__, L"%s", Resource);
				
				
				//L";>assembly;>package;<update;=displayName;";
				//ID="1"

				//Check if close button for GPEdit is found to verify that GPEdit is running
				LogTestInfoW(__FUNCTIONW__, L"Check if GPEdit opened.");
				BOOL fFoundGPEditCloseBtn = SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => '" L"MMCMainFrame" L"';Role = 'title bar' && ClassName = '" L"MMCMainFrame" L"';Name = '{1}' && Role = 'push button'", Resource, resKeyClose)));			//CLOSE_GP_SUCCEEDED_OPEN_WINDOW
				BOOL fFoundGPEditCloseBtnClickablePoint = TRUE;
	            
				//If close button is found verify it is clickable point
				if (fFoundGPEditCloseBtn)
				{
					int x, y;
					fFoundGPEditCloseBtnClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));
					LogTestInfoW(__FUNCTIONW__,
						L"%s Clickable point", fFoundGPEditCloseBtnClickablePoint ? L"Found": L"Did not find");
					//Ok, found it, now close GPEdit since we already know it exists
					if (fFoundGPEditCloseBtnClickablePoint)
					{
						LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
					}
				}
				else
				{
					//Clean up by closing failed attempt to open GPEdit
					LogTestInfoW(__FUNCTIONW__, L"GPEdit Not Found");
					hr = LOG_FAILED_HR(FromPartialQueryId(CLOSE_GP_FAILED_OPEN_WINDOW));
					if (SUCCEEDED(hr))
					{
						LeftButtonClick(CLICKABLE_POINT);
						
						//Now Close the Run Dialog Box
						hr = LOG_FAILED_HR(FromPartialQueryId(CLOSE_RUN_WINDOW));
						if (SUCCEEDED(hr))
						{
							LeftButtonClick(CLICKABLE_POINT);
						}
					}
				}

				//Set search timeout back to its original value
				SetSearchTimeOut(originalTimout);

				BOOL fGPEditExpected = FALSE;
				BOOL fSKUIdentificationFailed = FALSE;
	            
				//Determine if current SKU should have Global Policy Entry Point
				DWORD dwProductInfoType = 0;
				if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
				{
					switch (dwProductInfoType)
					{
						case PRODUCT_STARTER:
						case PRODUCT_HOME_BASIC:
						case PRODUCT_HOME_BASIC_N:
						case PRODUCT_HOME_PREMIUM:
							LogTestInfoW(__FUNCTIONW__, L"Group Policy Entry Points not expected here!");
							break;
						case PRODUCT_BUSINESS:
						case PRODUCT_BUSINESS_N:
						case PRODUCT_ENTERPRISE:
						case PRODUCT_ULTIMATE:
							fGPEditExpected = TRUE;
							LogTestInfoW(__FUNCTIONW__, L"Group Policy Entry Points expected here.");
							break;
						default:
							LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU.");
							fSKUIdentificationFailed = TRUE;
							break;
					}
					//Check actual result versus expected result here to determine Test Pass/Fail
					BOOL fSkuDifferentiationfFailed = (fFoundGPEditCloseBtn && fFoundGPEditCloseBtnClickablePoint) != fGPEditExpected;
					if (fSKUIdentificationFailed)
					{
						pwszResultInfo = L"Could not verify behavior";
					}
					else if (fSkuDifferentiationfFailed)
					{
						LogTestInfoW(__FUNCTIONW__,
							L"Global Policy SKU differentiation failed.[Current: %s | Expected: %s ]",
							fFoundGPEditCloseBtn ? L"Found": L"Not Found",
							fGPEditExpected ? L"Found" : L"Not Found");
					}
					else
					{
						fPassed = TRUE;
						pwszResultInfo = L"Global Policy entry point is differentiated correctly";
					}
				}
				else
				{
					LogTestInfoW(__FUNCTIONW__, L"GetProductInfo failed.");
					pwszResultInfo = L"GetProductInfo failed.";
				}			
			}
			else
			{
				LogTestInfoW(__FUNCTIONW__, L"Click OK on OpenRunDialog failed.");
				pwszResultInfo = L"Click OK on OpenRunDialog failed.";
			}
		}
		else
		{
			LogTestInfoW(__FUNCTIONW__, L"OpenRunDialog failed.");
			pwszResultInfo = L"OpenRunDialog failed.";
		}
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"FindDesktop failed.");
		pwszResultInfo = L"FindDesktop failed.";
	}

	//Test is finished. Record the result of the test in the log.
	LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}