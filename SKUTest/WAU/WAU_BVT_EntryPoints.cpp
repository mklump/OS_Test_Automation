#include <windows.h>            //Common Windows types
#include "screenelement.h"             //RPF
//#include "rpf_constants.h"
#include "LoggingFunctions.h"
#include "rpf_SKUDIFF.h"
#include "SKUDIFF_UTIL.h"
#include "SKUDIFF_MASK.h"

using namespace RPFPlayback;
using namespace SKUDiff;

//    Verify Windows Anytime Upgrade Entry Point(s)
//  
//	  Welcome Center entry point current testing in Welcome Center test case.

/*
TODO:
Start menu->Extras and Upgrades
Classic Control Panel
System Control Panel link

Out of Scope:
MFU list; cannot be sure the is the test first run.
*/
VOID CloseExcessWindows()
{
	//TODO: Close existing WAU windows
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

STDAPI WAUStartMenuEntryPoint(LPVOID pvReserved)
{
	BOOL fExpected = FeatureExpected(SDF_WINDOWS_ANYTIME_UPGRADE);
	BOOL fPassed = FALSE;
	LPWSTR pwszResultInfo = NULL;
	HRESULT hr = E_FAIL;

	//	LanguageNeutralString langNeutralDV2ControlHost(L"DV2ControlHost");

	LogTestBeginW(__FUNCTIONW__, L"Verify if Windows Anytime Upgrade is in the Extras and Upgrades folder of the Start Menu.");    
	//Start
	if (SUCCEEDED(OpenStartMenu()))
	{

		//All programs
		LogTestInfoW(__FUNCTIONW__, L"Programs...");
		hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_ALLPROGRAMS));
		if (SUCCEEDED(hr))  
		{
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

			//Maintenance
			LogTestInfoW(__FUNCTIONW__, L"Extras and Upgrades...");
			hr = LOG_FAILED_HR(FromPartialQueryId(ALL_PROGRAMS_MAINTENANCE)); //TODO: QID for E&U
			if (SUCCEEDED(hr))
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

				//Compare Expected and Actual presence of Backup and Restore center.
				BOOL fFound = SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(STARTMENU_BACKUP_RESTORE_CENTER))); //TODO: QID for WAU
				if (fFound != fExpected)
				{
					fPassed = FALSE;
					LogTestInfoW(__FUNCTIONW__,
						L"Windows Anytime Upgrade SKU differentiation failed.[Current: %s | Expected: %s ]",
						fFound ? L"Found": L"Not Found",
						fExpected ? L"Found" : L"Not Found");
				}
				else
				{
					fPassed = TRUE;
					LogTestInfoW(__FUNCTIONW__, L"Windows Anytime Upgrade is differentiated correctly.");

					
				}
			} // /Maint
			else
			{
				LogTestInfoW(__FUNCTIONW__, L"Could not open Maintenance menu.");
			}
		} // /All Prog
		else
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not open All Programs menu.");
		}
	} // /Start
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not open Start menu.");
	}
	// Close the Backup and Restore Center, to prevent cluttering the desktop.
	//LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");
	//hr = LOG_FAILED_HR(FromPartialQueryId(BACKUP_CPL_CLOSE));
	//if (SUCCEEDED(hr))
	//{
	//LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	//}



//SetSearchTimeOut(originalTimeout);
// If any important element reported a failure, the test as a whole is failed.
LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
return NOERROR;
}

// This is a test for accessing Backup features under Accessories.

STDAPI WAUControlPanelEntryPoint(LPVOID pvReserved)
{
	//TODO: STandard CPL code
	return NOERROR;
}
STDAPI WAUSystemControlPanelEntryPoint(LPVOID pvReserved)
{
	//TODO: Change Domain Join link code
	return NOERROR;



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
	if (SUCCEEDED(GlobalizeQueryId(Section, 1024, CPL_LINK_SYSTEMMAINTENANCE)) &&
		SUCCEEDED(GlobalizeQueryId(Link, 1024, CPL_LINK_SYSTEMCONTROLPANEL)) &&
		SUCCEEDED(OpenSpecificHomeControlPanel(Section, Link)))
	{

		hr = LOG_FAILED_HR(FromPartialQueryId(CPL_SYSTEM_CHANGE_SETTINGS_BTN));
		if (SUCCEEDED(hr))
		{
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

			// Tab as it may appear on Domain enabled SKU's, if localized differently
			hr = LOG_FAILED_HR(FromPartialQueryId(COMPUTER_NAME_CHANGE_DOMAIN));//COMPUTER_NAME_CHANGE_NAME
			if (SUCCEEDED(hr))
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

				if (SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(COMPUTER_NAME_DOMAIN_RADIO))))//COMPUTER_NAME_CHANGE_NAME_CANCEL
				{
					fFoundDomainUI = TRUE;
				}
			}
			else
			{
				// Tab as it may appear on Non-Domain enabled SKU's, if localized differently

				hr = LOG_FAILED_HR(FromPartialQueryId(COMPUTER_NAME_CHANGE_NAME));//COMPUTER_NAME_CHANGE_NAME
				if (SUCCEEDED(hr))
				{
					LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

					if (SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(COMPUTER_NAME_DOMAIN_RADIO))))//COMPUTER_NAME_CHANGE_NAME_CANCEL
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