#include <windows.h>            //Common Windows types
//#include "rpf_constants.h"
#include "screenelement.h"             //RPF
#include "LoggingFunctions.h"
#include "rpf_skudiff.h" // SKU Diff Contants
#include "SKUDIFF_UTIL.h"

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
//    Verify TabletPC Components
//  
STDAPI VerifyTabletPCComponents_EntryPoint(LPVOID pvReserved)
{
	BOOL    fPassed = FALSE;
	LPWSTR pwszResultInfo = NULL;

	BOOL fFoundTabletPCComponents = FALSE;
	BOOL fFoundStickyNotes = FALSE;
	BOOL fFoundTabletPCInputPanel = FALSE;
	BOOL fFoundWindowsJournal = FALSE;
	
	BOOL fExpected = FALSE;
	DWORD dwProductInfoType = 0;

	HRESULT hr = E_FAIL;


	//LogTestBeginW(__FUNCTIONW__, L"Verify Windows Fax and Scan is available in the Start Menu");    
	//LogResKeyValue(L"resKeyWindowsFaxandScan", resKeyWindowsFaxandScan);
	//LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
	//return NOERROR;
	
	
	

	if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
	{
		switch (dwProductInfoType)
		{
		case PRODUCT_STARTER:
		case PRODUCT_HOME_BASIC:
		case PRODUCT_HOME_BASIC_N:
			fExpected = FALSE;
			LogTestInfoW(__FUNCTIONW__, L"Tablet PC Components not expected here!");
			break;
		case PRODUCT_HOME_PREMIUM:
		case PRODUCT_HOME_PREMIUM_N:
		case PRODUCT_ENTERPRISE:
		case PRODUCT_ENTERPRISE_N:
		case PRODUCT_BUSINESS:
		case PRODUCT_BUSINESS_N:
		case PRODUCT_ULTIMATE:
		case PRODUCT_ULTIMATE_N:
			fExpected = TRUE;
			LogTestInfoW(__FUNCTIONW__, L"Tablet PC Components expected here!");
			break;
		default:
			LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
			pwszResultInfo = L"Could not verify behavior";
			break;
		}
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"SKU determination Failed");
		pwszResultInfo = L"SKU determination Failed";
	}


	
	if (SUCCEEDED(OpenAllPrograms()))
	{
		

		hr = (WOWFromPartialQueryId(ALL_PROGRAMS_ACCESSORIES));
		if (FAILED(hr))
		{
			LogTestResultW(fPassed, __FUNCTIONW__, L"Coundn't find Accessories in Start Menu -> All Programs");
			return NOERROR; 
		}
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

		//Check for Tablet PC in All Program -> Accessories 
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(ALL_PROGRAMS_ACCESSORIES_TABLET_PC));
		if(SUCCEEDED(hr))
		{
			fFoundTabletPCComponents = TRUE;
		}
		else
		{
			fFoundTabletPCComponents = FALSE;

			if(fFoundTabletPCComponents != fExpected)
			{	
				LogTestInfoW(__FUNCTIONW__,
				L"Tablet PC Components are SKU differentiation failed.[Current: %s | Expected: %s ]",
				fFoundTabletPCComponents? L"Found": L"Not Found",
				fExpected ? L"Found" : L"Not Found");
			}
			else
			{
				fPassed = TRUE;
				pwszResultInfo = L"Table PC Components entry point is differentiated correctly";
			}
			LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;
		}

		
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));


		
		//Check for Sticky Notes
		if(! IsAvailable(10000,ACCESSORIES_TABLET_PC_STICKY_NOTES ))
		{
			LogTestResultW(fPassed, __FUNCTIONW__, L"Coundn't find in Sticky Notes in Start Menu -> All Programs -> Accessories -> TabletPC ");
			return NOERROR;
		}
		fFoundStickyNotes = TRUE;

		//Check for Tablet PC Input Panel
		if(! IsAvailable(10000,ACCESSORIES_TABLET_PC_INPUT_PANEL ))
		{
			LogTestResultW(fPassed, __FUNCTIONW__, L"Coundn't find Table PC input Panel  in Start Menu -> All Programs -> Accessories -> TabletPC");
			return NOERROR;
		}
		fFoundTabletPCInputPanel = TRUE;
		
		//Check for Windows Journal
		if(!IsAvailable(10000, ACCESSORIES_TABLET_PC_WINODWS_JOURNAL))
		{
			LogTestResultW(fPassed, __FUNCTIONW__, L"Coundn't find Windows Journal in Start Menu -> All Programs -> Accessories -> TabletPC");
			return NOERROR;
		}
		fFoundWindowsJournal = TRUE;
			


		if (fFoundStickyNotes!= fExpected || fFoundTabletPCInputPanel != fExpected || fFoundWindowsJournal != fExpected)
		{
			LogTestInfoW(__FUNCTIONW__,L"Tablet PC Components  SKU differentiation failed.");
		}
		else
		{
			fPassed = TRUE;
			pwszResultInfo = L"Tablet PC Components entry point is differentiated correctly";
		}
		



	}

	LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");

	hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
	if (SUCCEEDED(hr))
	{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	}
//SetSearchTimeOut(originalTimeout);

	LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
	return NOERROR;
}

