#include <windows.h>            //Common Windows types
//#include "rpf_constants.h"
#include "screenelement.h"             //RPF
#include "LoggingFunctions.h"
#include "rpf_skudiff.h" // SKU Diff Contants
#include "SKUDIFF_UTIL.h"
#include "SKUDIFF_MASK.h"

using namespace RPFPlayback;
using namespace SKUDiff;

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

//    
//    WelcomeCenter_Generic Item 
//  
BOOL WelcomeCenter_Generic_Item(__in wchar_t *szFeatureName,__in int sdfMask,__in wchar_t *gqidWCItem)
{
	BOOL    fPassed = FALSE;
	LPWSTR pwszResultInfo = NULL;

	LogTestBeginW(__FUNCTIONW__, L"Verify %s is available in Welcome Center on appropriate SKUs.",szFeatureName);    
	LogSKU();

	if (SUCCEEDED(OpenWelcomeCenter()))
	{
		BOOL fExpected = FeatureExpected(sdfMask);

		BOOL fFound = IsAvailable(10000, gqidWCItem);
			//SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(gqidWCItem)));

		if (fFound != fExpected)
		{
			LogTestInfoW(__FUNCTIONW__,
				L"%s SKU differentiation failed.[Current: %s | Expected: %s ]",
				szFeatureName,
				fFound ? L"Found": L"Not Found",
				fExpected ? L"Found" : L"Not Found");
		}
		else
		{
			fPassed = TRUE;
			pwszResultInfo = L"Feature is differentiated correctly";
		}
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not open Welcome Center.");
		pwszResultInfo = L"Could not open Welcome Center.";
	}


	LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");
	if (SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(CPL_WC_CLOSE_BTN))))
	{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	}
	LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
	return NOERROR;
}
//    
//    WelcomeCenter_Computer_Details 
//  
STDAPI WelcomeCenter_Comp_Details_EntryPoint(LPVOID pvReserved)
{
	wchar_t gqidItem[1024];
	if (SUCCEEDED(GlobalizeQueryId(gqidItem, 1024, WC_COMP_DETAILS)))
	{
		WelcomeCenter_Generic_Item(L"Computer Details", SDF_WC_COMP_DETAILS, gqidItem);
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not Globalize QID for Computer Details");
	}
	return NOERROR;
}

//    
//    WelcomeCenter_Add_User 
//  
STDAPI WelcomeCenter_Add_User_EntryPoint(LPVOID pvReserved)
{
	wchar_t gqidItem[1024];
	if (SUCCEEDED(GlobalizeQueryId(gqidItem, 1024, WC_ADD_USERS)))
	{
		WelcomeCenter_Generic_Item(L"Add User", SDF_WC_ADD_USERS, gqidItem);
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not Globalize QID for Add User");
	}
	return NOERROR;
}



//    
//    WelcomeCenter_Easy_Transfer 
//  
STDAPI WelcomeCenter_Easy_Transfer_EntryPoint(LPVOID pvReserved)
{
	wchar_t gqidItem[1024];
	if (SUCCEEDED(GlobalizeQueryId(gqidItem, 1024, WC_EASY_TRANSFER)))
	{
		WelcomeCenter_Generic_Item(L"Easy Transfer", SDF_WC_EASY_TRANSFER, gqidItem);
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not Globalize QID for Easy Transfer");
	}
	return NOERROR;
}


//    
//    WelcomeCenter_Connect_Internet
//  
STDAPI WelcomeCenter_Connect_Internet_EntryPoint(LPVOID pvReserved)
{
	wchar_t gqidItem[1024];
	if (SUCCEEDED(GlobalizeQueryId(gqidItem, 1024, WC_CONNECT_INTERNET)))
	{
		WelcomeCenter_Generic_Item(L"Connect to the Internet", SDF_WC_CONNECT_INTERNET, gqidItem);
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not Globalize QID for Connect to the Internet");
	}
	return NOERROR;
}



//    
//    WelcomeCenter_Ultimate_Extras
//  
STDAPI WelcomeCenter_Ultimate_Extras_EntryPoint(LPVOID pvReserved)
{
	LogTestInfoW(__FUNCTIONW__, L"Ultimate Extras was removed from the Welcome Center in SP1, this case will fail on Ultimate RTM, and that is not a bug.");
	wchar_t gqidItem[1024];
	if (SUCCEEDED(GlobalizeQueryId(gqidItem, 1024, WC_ULTIMATE_EXTRAS)))
	{
		WelcomeCenter_Generic_Item(L"Ultimate Extras", SDF_WC_ULTIMATE_EXTRAS, gqidItem);
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not Globalize QID for Ultimate Extras");
	}
	return NOERROR;
}


//    
//    WelcomeCenter_Whats_New
//  
STDAPI WelcomeCenter_Whats_New_EntryPoint(LPVOID pvReserved)
{
	wchar_t gqidItem[1024];

	if (//RESKEYSEQUAL(resKeyWCWhatsNewWindows,resKeyWCWhatsNewWindows2)&&
		RESKEYSEQUAL(resKeyWCWhatsNewWindows,resKeyWCWhatsNewWindows3)&&
		RESKEYSEQUAL(resKeyWCWhatsNewWindows,resKeyWCWhatsNewWindows4)&&
		RESKEYSEQUAL(resKeyWCWhatsNewWindows,resKeyWCWhatsNewWindows5))
	{

		if (SUCCEEDED(GlobalizeQueryId(gqidItem, 1024, WC_WHATS_NEW)))
		{
			WelcomeCenter_Generic_Item(L"Whats new in Windows Vista (Business)", SDF_WC_WHATS_NEW, gqidItem);
		}
		else
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not Globalize QID for Whats new in Windows");
		}
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Localized strings for [What's new in Windows Vista] do not match, if this is not Psuedo-Loc it's probably a Localization bug.");
		return E_FAIL;
	}

	return NOERROR;
}


//    
//    WelcomeCenter_Personalize
//  
STDAPI WelcomeCenter_Personalize_EntryPoint(LPVOID pvReserved)
{
	wchar_t gqidItem[1024];
	if (SUCCEEDED(GlobalizeQueryId(gqidItem, 1024, WC_PERSONALIZE)))
	{
		WelcomeCenter_Generic_Item(L"Personalize Windows", SDF_WC_PERSONALIZE, gqidItem);
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not Globalize QID for Personalize Windows");
	}
	return NOERROR;
}


//    
//    WelcomeCenter_Register_Windows
//  
STDAPI WelcomeCenter_Register_Windows_EntryPoint(LPVOID pvReserved)
{
	wchar_t gqidItem[1024];

	if (RESKEYSEQUAL(resKeyWCRegisterWindowsOnline,resKeyWCRegisterWindowsOnline2)&&
		RESKEYSEQUAL(resKeyWCRegisterWindowsOnline,resKeyWCRegisterWindowsOnline3)&&
		RESKEYSEQUAL(resKeyWCRegisterWindowsOnline,resKeyWCRegisterWindowsOnline4)&&
		RESKEYSEQUAL(resKeyWCRegisterWindowsOnline,resKeyWCRegisterWindowsOnline5))
	{
		if (SUCCEEDED(GlobalizeQueryId(gqidItem, 1024, WC_REGISTER_WINDOWS)))
		{
			WelcomeCenter_Generic_Item(L"Register Windows", SDF_WC_REGISTER_WINDOWS, gqidItem);
		}
		else
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not Globalize QID for Register Windows");
		}
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Localized strings for [Register Windows Online] do not match, if this is not Psuedo-Loc it's probably a Localization bug.");
		return E_FAIL;
	}

	return NOERROR;
}


//    
//    WelcomeCenter_Add_Printer
//  
STDAPI WelcomeCenter_Add_Printer_EntryPoint(LPVOID pvReserved)
{
	wchar_t gqidItem[1024];
	if (SUCCEEDED(GlobalizeQueryId(gqidItem, 1024, WC_ADD_PRINTER)))
	{
		WelcomeCenter_Generic_Item(L"Add Printer", SDF_WC_ADD_PRINTER, gqidItem);
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not Globalize QID for Add Printer");
	}
	return NOERROR;
}


//    
//    WelcomeCenter_MCE
//  
STDAPI WelcomeCenter_MCE_EntryPoint(LPVOID pvReserved)
{
	wchar_t gqidItem[1024];
	if (SUCCEEDED(GlobalizeQueryId(gqidItem, 1024, WC_MCE)))
	{
		WelcomeCenter_Generic_Item(L"Windows Media Center", SDF_WC_MCE, gqidItem);
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not Globalize QID for Windows Media Center");
	}
	return NOERROR;
}


//    
//    WelcomeCenter_Demos
//  
STDAPI WelcomeCenter_Demos_EntryPoint(LPVOID pvReserved)
{

	wchar_t gqidItem[1024];

	if (RESKEYSEQUAL(resKeyWCWindowsVistaDemos,resKeyWCWindowsVistaDemos2))
	{
		if (SUCCEEDED(GlobalizeQueryId(gqidItem, 1024, WC_DEMOS)))
		{
			WelcomeCenter_Generic_Item(L"Windows Demos", SDF_WC_DEMOS, gqidItem);
		}
		else
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not Globalize QID for Windows Demos");
		}
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Localized strings for [Windows Vista Demos] do not match, if this is not Psuedo-Loc it's probably a Localization bug.");
		return E_FAIL;
	}
	return NOERROR;
}


//    
//    WelcomeCenter_Basics
//  
STDAPI WelcomeCenter_Basics_EntryPoint(LPVOID pvReserved)
{
	wchar_t gqidItem[1024];
	if (SUCCEEDED(GlobalizeQueryId(gqidItem, 1024, WC_BASICS)))
	{
		WelcomeCenter_Generic_Item(L"Windows Basics", SDF_WC_BASICS, gqidItem);
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not Globalize QID for Windows Basics");
	}
	return NOERROR;
}

//    
//    WelcomeCenter_Ease_Access
//  
STDAPI WelcomeCenter_Ease_Access_EntryPoint(LPVOID pvReserved)
{
	wchar_t gqidItem[1024];
	if (SUCCEEDED(GlobalizeQueryId(gqidItem, 1024, WC_EASE_ACCESS)))
	{
		WelcomeCenter_Generic_Item(L"Ease of Access", SDF_WC_EASE_ACCESS, gqidItem);
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not Globalize QID for Ease of Access");
	}
	return NOERROR;
}


//    
//    WelcomeCenter_Backup_Restore
//  
STDAPI WelcomeCenter_Backup_Restore_EntryPoint(LPVOID pvReserved)
{
	wchar_t gqidItem[1024];
	if (SUCCEEDED(GlobalizeQueryId(gqidItem, 1024, WC_BACKUP_RESTORE)))
	{
		WelcomeCenter_Generic_Item(L"Backup and Restore", SDF_WC_BACKUP_RESTORE, gqidItem);
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not Globalize QID for Backup and Restore");
	}
	return NOERROR;
}



//    
//    WelcomeCenter_Control_Panel
//  
STDAPI WelcomeCenter_Control_Panel_EntryPoint(LPVOID pvReserved)
{
	wchar_t gqidItem[1024];
	if (SUCCEEDED(GlobalizeQueryId(gqidItem, 1024, WC_CONTROL_PANEL)))
	{
		WelcomeCenter_Generic_Item(L"Control Panel", SDF_WC_CONTROL_PANEL, gqidItem);
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not Globalize QID for Control Panel");
	}
	return NOERROR;
}


//    
//    WelcomeCenter_Anytime_Upgrade
//  
STDAPI WelcomeCenter_Anytime_Upgrade_EntryPoint(LPVOID pvReserved)
{
	wchar_t gqidItem[1024];
	if (SUCCEEDED(GlobalizeQueryId(gqidItem, 1024, WC_UPGRADE)))
	{
		WelcomeCenter_Generic_Item(L"Windows Anytime Upgrade", SDF_WC_UPGRADE, gqidItem);
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not Globalize QID for Windows Anytime Upgrade");
	}
	return NOERROR;
}
