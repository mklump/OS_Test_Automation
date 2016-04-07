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
	GlobalizeQueryId(szGlobalQuery, 1024, COMPUTER_NAME_CHANGE_DOMAIN_CANCEL);
	LeftClickUntilGone(szGlobalQuery);
	GlobalizeQueryId(szGlobalQuery, 1024, COMPUTER_NAME_CHANGE_NAME_CANCEL);
	LeftClickUntilGone(szGlobalQuery);
	GlobalizeQueryId(szGlobalQuery, 1024, SYSTEM_PROPERTIES_CLOSE_BTN);
	LeftClickUntilGone(szGlobalQuery);
	GlobalizeQueryId(szGlobalQuery, 1024, CPL_SYSTEM_CLOSE_BTN);
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

//    
//    VerifyDomainJoinCPLEntryPoint 
//  
STDAPI DomainJoinEntryPoints(LPVOID pvReserved)
{
	BOOL    fPassed = FALSE;
	LPWSTR pwszResultInfo = L"No Result String Set.";
	HRESULT hr = E_FAIL;
	LogTestBeginW(__FUNCTIONW__, L"Verify Domain join is available from the CPL");    

	BOOL fFoundDomainUI = FALSE;
	BOOL fExpected = FALSE;
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
			LogTestInfoW(__FUNCTIONW__, L"Domain join UI not expected here!");
			break;
		case PRODUCT_BUSINESS:
		case PRODUCT_BUSINESS_N:
		case PRODUCT_ENTERPRISE:
		case PRODUCT_ENTERPRISE_N:
		case PRODUCT_ULTIMATE:
		case PRODUCT_ULTIMATE_N:
			fExpected = TRUE;
			LogTestInfoW(__FUNCTIONW__, L"Domain join UI expected here.");
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
	}

	if(!RESKEYSEQUAL(resKeyComputerNameTab,resKeyComputerNameDomainTab))
	{
		LogTestInfoW(__FUNCTIONW__, L"Localized 'Computer Name' resource inconsistent, if this is not Psuedo-Loc it is very likely a Localization bug.");
		pwszResultInfo = L"Localized 'Computer Name' tab name resource inconsistent, if this is not Psuedo-Loc it is very likely a Localization bug.";
	}

	if(!RESKEYSEQUAL(resKeyComputerNameChange,resKeyComputerNameDomainChange))
	{
		LogTestInfoW(__FUNCTIONW__, L"Localized 'Change...' resource inconsistent, if this is not Psuedo-Loc it is very likely a Localization bug.");
		pwszResultInfo = L"Localized 'Change...' button label resource inconsistent, if this is not Psuedo-Loc it is very likely a Localization bug.";
	}
	wchar_t Section[1024];
	wchar_t Link[1024];	
	//SetRobustnessLevel(-2);
		
	if (SUCCEEDED(GlobalizeQueryId(Section, 1024, CPL_LINK_SYSTEMMAINTENANCE)) &&
		SUCCEEDED(GlobalizeQueryId(Link, 1024, CPL_LINK_SYSTEMCONTROLPANEL)) &&
		SUCCEEDED(OpenSpecificHomeControlPanel(Section, Link)))
	{
		//Attempt to ensure the window is fully drawn; is a problem on German.
		Snooze();

		hr = LOG_FAILED_HR(WOWFromPartialQueryId(CPL_SYSTEM_CHANGE_SETTINGS_BTN));
		
		if (SUCCEEDED(hr))
		{
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
			//SetRobustnessLevel(1);
		
			// Tab as it may appear on Domain enabled SKU's, if localized differently
			hr = LOG_FAILED_HR(WOWFromPartialQueryId(COMPUTER_NAME_CHANGE_DOMAIN));//COMPUTER_NAME_CHANGE_NAME
			if (SUCCEEDED(hr))
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

				if (SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(COMPUTER_NAME_DOMAIN_RADIO))))//COMPUTER_NAME_CHANGE_NAME_CANCEL
				{
					fFoundDomainUI = TRUE;
				}
			}
			else
			{
				// Tab as it may appear on Non-Domain enabled SKU's, if localized differently

				hr = LOG_FAILED_HR(WOWFromPartialQueryId(COMPUTER_NAME_CHANGE_NAME));//COMPUTER_NAME_CHANGE_NAME
				if (SUCCEEDED(hr))
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

					if (SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(COMPUTER_NAME_DOMAIN_RADIO))))//COMPUTER_NAME_CHANGE_NAME_CANCEL
					{
						fFoundDomainUI = TRUE;
					}
				}


			}

			if (fFoundDomainUI != fExpected)
			{
				LogTestInfoW(__FUNCTIONW__,
					L"Domain UI SKU differentiation failed.[Current: %s | Expected: %s ]",
					fFoundDomainUI ? L"Found": L"Not Found",
					fExpected ? L"Found" : L"Not Found");

				pwszResultInfo = L"Domain Join CPL entry point is NOT differentiated correctly";
			}
			else
			{
				fPassed = TRUE;
				pwszResultInfo = L"Domain Join CPL entry point is differentiated correctly";
			}
		}
	}

	LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
	return NOERROR;
}




