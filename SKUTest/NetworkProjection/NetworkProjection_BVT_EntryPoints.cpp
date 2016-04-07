/***************************************************************
// Description: BVT - Network Projection entry point verification in SKUs
// Created:     HariniD
// Modified:	a-aaroh (05/15/2007)
// Modified:	a-jomul (10/15/2007)
//				Corrected logic error when trying to open Network Projector twice
//				Updated globalized query strings
// Modified:	a-jomul (10/15/2007)
//				Modified for robustness, using library functions
//				Updated globalized query strings
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

void CloseExcessWindows() // test specific, ensure a clean state; can be made better with RPF 12+
{
	wchar_t szGlobalQuery[1024];
	GlobalizeQueryId(szGlobalQuery, 1024, NETPROJ_DENY_FIREWALL_ACCESS);
	LeftClickUntilGone(szGlobalQuery);
	GlobalizeQueryId(szGlobalQuery, 1024, CANCEL_PROJECTOR);
	LeftClickUntilGone(szGlobalQuery);
	GlobalizeQueryId(szGlobalQuery, 1024, CLOSE_PROJECTOR);
	LeftClickUntilGone(szGlobalQuery);
}

// Initialize
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

// Verify Network Projector entry point in Start Menu
STDAPI NetworkProjection_BVT_EntryPoints(LPVOID pvReserved)
{
	BOOL fResult = FALSE;

	LogTestBeginW(__FUNCTIONW__, L"Beginning Network Projector BVT test case...");

	BOOL fExpected = FALSE;
	BOOL fSKUIdentificationFailed = FALSE;

	DWORD dwProductInfoType = 0;
	if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
	{
		switch (dwProductInfoType)
		{
		case PRODUCT_STARTER:
		case PRODUCT_HOME_BASIC:
		case PRODUCT_HOME_BASIC_N:
			LogTestInfoW(__FUNCTIONW__, L"Network Projector is NOT expected in this SKU.");
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
			LogTestInfoW(__FUNCTIONW__, L"Network Projector is expected in this SKU.");
			break;
		default:
			LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU.");
			fSKUIdentificationFailed = TRUE;
			break;
		}
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU.");
		fSKUIdentificationFailed = TRUE;


	}
	HRESULT hr;

	if(FAILED(OpenAllPrograms()))
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not open All Programs.");
	}
	else
	{

			LogTestInfoW(__FUNCTIONW__, L"Click Accessories...");
			hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_ACCESSORIES));

			if (SUCCEEDED(hr))
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));



				LogTestInfoW(__FUNCTIONW__, L"Launch --Connect to Network Projector--");
				BOOL fFoundUI = SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(STARTMENU_PROJECTOR)));
				BOOL fFoundClickablePoint = FALSE;
				BOOL fLaunched = FALSE;

				if (fFoundUI)
				{
					LogTestInfoW(__FUNCTIONW__, L"Found UI");
					{

						hr = LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
						if (SUCCEEDED(hr))
						{
							fLaunched = TRUE;

							//Check if Firewall needs permission to allow open Network Projector
							LogTestInfoW(__FUNCTIONW__, L"Grant Firewall Access Permission if needed");
							hr = (WOWFromPartialQueryId(NETPROJ_ALLOW_FIREWALL_ACCESS));
							if (SUCCEEDED(hr))
							{
								LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
							}
							//Close Network Projector Window
							LogTestInfoW(__FUNCTIONW__, L"Close Network Projector Window");
							hr = LOG_FAILED_HR(WOWFromPartialQueryId(CANCEL_PROJECTOR));
							if (SUCCEEDED(hr))
							{
								LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
							}
						}
					}
				}
				
				if (fSKUIdentificationFailed)
				{
					LogTestInfoW(__FUNCTIONW__, L"Could not verify behavior.");
				}
				else if ((fFoundUI && fLaunched) != fExpected)
				{
					LogTestInfoW(__FUNCTIONW__,
						L"Network Projection SKU differentiated feature failed.[Current: %s | Expected: %s ]",
						fFoundUI ? L"Found": L"Not Found",
						fExpected ? L"Found" : L"Not Found");
				}
				else
				{
					fResult = TRUE;
					LogTestInfoW(__FUNCTIONW__, L"Network Projection is differentiated correctly.");
				}

			}
		
	}

	LogTestResultW(fResult, __FUNCTIONW__, L"Completed Network Projector BVT test case.");
	return NOERROR;
}
