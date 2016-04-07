/// <copyright file="HDPublish_BVT_EntryPoints.cpp" company="Microsoft">
///  Copyright (c) Microsoft Corporation.  All rights reserved.
/// </copyright>
///
/// <summary>
///  Code for WTT WindowsShell, Job #######
///  Verify HD Publishing feature availablity
/// </summary>
///
// Complete Feb 2008, a-jomul

#include <windows.h>            //Common Windows types
#include "screenelement.h"             //RPF
#include "LoggingFunctions.h"
#include "rpf_SKUDIFF.h"
#include "SKUDIFF_UTIL.h"

using namespace RPFPlayback;
using namespace SKUDiff;


//
// Have to dive deep into Movie Maker to verify UI, changes to Movie Maker UI may break it.
// then compare the list of available Codecs to the list of known HD codecs.
//
// it compares the codec strings up until the first ‘%’ in the resource string, or lacking a ‘%’ the entire string.
// This would fail if, for example a localized version puts the replaceable parameter at the beginning of the string.
// I don’t know how likely that is.
//

void CloseExcessWindows() // test specific, ensure a clean state; can be made better with RPF 12+
{
	try
	{
		MultiLeftClickUntilGone(3,
			MOVIE_MAKER_PUBLISH_CLOSE,
			MOVIE_MAKER_CLOSE,
			MOVIE_MAKER_DO_NOT_SAVE);

		//TerminateProcessByModuleName(L"MOVIEMK.exe", 0);
	}
	catch (...)
	{
		LogTestInfoW(__FUNCTIONW__, L"%s reporting FAIL due to an unhandled unexpected exception.", __FUNCTIONW__);
		LogTestResultW(FALSE, __FUNCTIONW__, L"Test Code Failure");
		
	}
}
STDAPI InitTest(LPVOID)
{
	try
	{
		HRESULT hr = SKUInitTest();
		if SUCCEEDED(hr)
		{
			//EnableInfoWindow(FALSE); // needed for 800x600
			CloseExcessWindows();
		}
		return hr;
	}
	catch (...)
	{
		LogTestInfoW(__FUNCTIONW__, L"%s reporting FAIL due to an unhandled unexpected exception.", __FUNCTIONW__);
		LogTestResultW(FALSE, __FUNCTIONW__, L"Test Code Failure");
		return E_FAIL;
	}
}

STDAPI UnInitTest()
{
	try
	{
		CloseExcessWindows();
		return SKUUnInitTest();
	}
	catch (...)
	{
		LogTestInfoW(__FUNCTIONW__, L"%s reporting FAIL due to an unhandled unexpected exception.", __FUNCTIONW__);
		LogTestResultW(FALSE, __FUNCTIONW__, L"Test Code Failure");
		return E_FAIL;
	}
}


/*
STDAPI RealHDPublishSelection(LPVOID pvReserved);
STDAPI RealHDPublishSelection(LPVOID pvReserved)
{
__try
{
return RealHDPublishSelection(pvReserved);
}
__except(ExceptionFilter(GetExceptionCode(), GetExceptionInformation()))
{
LogTestResultW(FALSE, __FUNCTIONW__, L"Failing due to an exception in the test code.");
return E_FAIL;
}
}
*/


STDAPI HDPublishSelection(LPVOID pvReserved)
{
	try
	{

		LanguageNeutralString langNeutralDV2ControlHost(L"DV2ControlHost");

		LogTestBeginW(__FUNCTIONW__, L"Verify HD Publishing feature availablity");

		BOOL fHDCodecsExpected = FALSE;
		BOOL fHDCodecsPassed = FALSE;

		//LPWSTR pwszResultInfo = NULL;

		HRESULT hr = E_FAIL;
		LPWSTR pwszResultInfo = L"Initializing Test";

		// Log WEI scores
		Assessment();
		if (Get2DScore() < 2)
		{
			LogTestInfoW(__FUNCTIONW__, L"WEI Video score insufficent for test, exiting as a PASS.");
			LogTestResultW(TRUE, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;
		}

		// Indentify the current SKU
		pwszResultInfo = L"Set Expected state phase.";
		DWORD dwProductInfoType = 0;
		if (!GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
		{
			LogTestInfoW(__FUNCTIONW__, L"GetProductInfo API failed, test cannot continue.");
			LogTestResultW(FALSE, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;			
		}

		switch (dwProductInfoType)
		{
		case PRODUCT_STARTER:
		case PRODUCT_HOME_BASIC:
		case PRODUCT_HOME_BASIC_N:
		case PRODUCT_HOME_PREMIUM_N:
		case PRODUCT_BUSINESS:
		case PRODUCT_BUSINESS_N:
		case PRODUCT_ENTERPRISE:
		case PRODUCT_ENTERPRISE_N:
		case PRODUCT_ULTIMATE_N:
			// No HD Publishing Codec functionality
			LogTestInfoW(__FUNCTIONW__, L"HD Codecs NOT expected.");
			fHDCodecsExpected = FALSE;
			break;
		case PRODUCT_HOME_PREMIUM:
		case PRODUCT_ULTIMATE:
			// HD Publishing Codec functionality
			LogTestInfoW(__FUNCTIONW__, L"HD Codecs expected");
			fHDCodecsExpected = TRUE;
			break;
		default:
			LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU, cannot set expectations.");
			break;
		}

		//TODO: Ensure existing Movie Maker instances are closed.

		//
		// Terminate the Movie Maker Process
		//
		pwszResultInfo = L"Navigating to Entry point phase.";
		//TerminateProcessByModuleName(L"MOVIEMK.exe", 0);



		if (FAILED(OpenAllPrograms()))
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not open All Programs.");
			LogTestResultW(fHDCodecsPassed, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;
		}



		BOOL fFoundMM = SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(STARTMENU_WINDOWS_MOVIE_MAKER)));

		if (fFoundMM == FALSE)  //FAILED(hr)
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not Locate Windows Movie Maker.");
			LogTestResultW(fHDCodecsPassed, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;
		}
		else
		{
			hr = LOG_FAILED_HR( LeftButtonClick(CLICKABLE_POINT));
		}


		if (FAILED(hr))  
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not open Windows Movie Maker.");
			LogTestResultW(fHDCodecsPassed, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;
		}


		// Dismiss file recovery dialog if it appears.
		Snooze(3);
		if (SUCCEEDED(WOWFromPartialQueryId(MOVIE_MAKER_DO_NOT_SAVE)))  
		{
			LeftButtonClick(CLICKABLE_POINT);
		}


		//File...
		Snooze(3);
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(MOVIE_MAKER_FILE_MENU));
		if (FAILED(hr))  
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not open the File Menu(a).");
			LogTestResultW(fHDCodecsPassed, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;
		}
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

		//Import...
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(MOVIE_MAKER_FILE_IMPORT_MEDIA));
		if (FAILED(hr))  
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not select Import from File Menu.");
			LogTestResultW(fHDCodecsPassed, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;
		}
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

		//
		//enter file path/name in common control for 'Bear'
		//
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(MOVIE_MAKER_IMPORT_FILENAME));
		if (FAILED(hr))  
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not select the File Name field.");
			LogTestResultW(fHDCodecsPassed, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;
		}

		hr = LOG_FAILED_HR(SetValueAsEditBox(L"%public%\\videos\\sample videos\\bear.wmv", EF_DELETE_CONTENT | EF_USE_WM_SETTEXT ));
		if (FAILED(hr))  
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not change the File Name field.");
			LogTestResultW(fHDCodecsPassed, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;
		}

		TypeString(L"~"); // '~' means the Enter key.

		// I hate to use blind keystrokes, but trying to hit the 'Import' button just isn't working right.
		// Accept selected file(s)
		// The common control 'Import' button has two modes,
		// appearently depending on if the SKU supports file system rollback...
		// good use for a Wildcard QID later.

		//Right-click on 'Bear' in the Videos list
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(MOVIE_MAKER_VIDEO_BEAR));
		if (FAILED(hr))  
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not right-click Bear.");
			LogTestResultW(fHDCodecsPassed, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;
		}
		LOG_FAILED_HR(RightButtonClick(CLICKABLE_POINT)); /// <<<--- Notice RIGHT button click.

		//Add 'Bear' to the storyboard
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(MOVIE_MAKER_ADD_TO_STORYBOARD));
		if (FAILED(hr))  
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not add Bear to Storyboard.");
			LogTestResultW(fHDCodecsPassed, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;
		}
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

		//File...
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(MOVIE_MAKER_FILE_MENU));
		if (FAILED(hr))  
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not open file menu(b).");
			LogTestResultW(fHDCodecsPassed, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;
		}
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

		//Publish
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(MOVIE_MAKER_FILE_PUBLISH_MOVIE));
		if (FAILED(hr))  
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not File Publish.");
			LogTestResultW(fHDCodecsPassed, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;
		}
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

		//Ensure 'This Computer' is selected.
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(MOVIE_MAKER_PUBLISH_THIS_COMPUTER));
		if (FAILED(hr))  
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not select 'This Computer'.");
			LogTestResultW(fHDCodecsPassed, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;
		}
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

		// Move to the next step.
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(MOVIE_MAKER_PUBLISH_NEXT1));
		if (FAILED(hr))  
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not progress in Publish(a).");
			LogTestResultW(fHDCodecsPassed, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;
		}
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

		// Move to the next step.
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(MOVIE_MAKER_PUBLISH_NEXT2));
		if (FAILED(hr))  
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not progress in Publish(b).");
			LogTestResultW(fHDCodecsPassed, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;
		}
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

		// Select the 'More Settings' radio button
		hr = LOG_FAILED_HR(WOWFromPartialQueryId(MOVIE_MAKER_PUBLISH_MORE_SETTINGS));
		if (FAILED(hr))
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not choose 'More Settings'.");
			LogTestResultW(fHDCodecsPassed, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;
		}
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

		Snooze(2);

		pwszResultInfo = L"Determine feature state phase.";

		// Heart of the test, check for HD codecs in the Combobox.
		ScreenElement* pScreenElement;
		pScreenElement = WOWScreenElementFromPartialQueryId(MOVIE_MAKER_PUBLISH_UNNAMED_COMBOBOX);
		if(pScreenElement != NULL)
		{
			ScreenElementCollection* pFoundElements;
			pFoundElements = pScreenElement->FindAllDescendants(L";[FindAll, MSAA] Role = 'list item'");

			wchar_t szCodecName[8][256];
			//HRESULT hrx = E_FAIL;
			LOG_FAILED_HR(WOWGetResKeyValue(resKeyHDCodecNTSC720p,256,szCodecName[0]));
			LOG_FAILED_HR(WOWGetResKeyValue(resKeyHDCodecNTSC1080p,256,szCodecName[1]));
			LOG_FAILED_HR(WOWGetResKeyValue(resKeyHDCodecNTSC1080pVC1,256,szCodecName[2]));
			LOG_FAILED_HR(WOWGetResKeyValue(resKeyHDCodecNTSCXBox,256,szCodecName[3]));
			LOG_FAILED_HR(WOWGetResKeyValue(resKeyHDCodecPAL720p,256,szCodecName[4]));
			LOG_FAILED_HR(WOWGetResKeyValue(resKeyHDCodecPAL1080p,256,szCodecName[5]));
			LOG_FAILED_HR(WOWGetResKeyValue(resKeyHDCodecPAL1080pVC1,256,szCodecName[6]));
			LOG_FAILED_HR(WOWGetResKeyValue(resKeyHDCodecPALXBox,256,szCodecName[7]));

			int countHDCodecsfound = 0;

			for(int i=0; i < pFoundElements->Count(); i++)
			{
				ScreenElement* pSubScreenElement;
				pSubScreenElement = (*pFoundElements)[i];
				//LogTestInfoW(__FUNCTIONW__, pSubScreenElement->get_Name()); // Uncomment to list all codec choices in combobox
				for(int j=0; j < 7; j++)
				{
					size_t lenImportantBit;
					if (wcschr(szCodecName[j],'%') != NULL)
					{
						lenImportantBit = wcschr(szCodecName[j],'%')-szCodecName[j];
					}
					else
					{

						lenImportantBit =wcslen(szCodecName[j]);
					}	

					//Pointer Math; but result is not used as a pointer, but a size.
					int cmp = wcsncmp(pSubScreenElement->get_Name(),szCodecName[j],lenImportantBit);

					if (cmp == 0)
					{
						LogTestInfoW(__FUNCTIONW__,L"The first %d characters of [%s] and [%s] match.",lenImportantBit, pSubScreenElement->get_Name(),szCodecName[j],cmp);
						countHDCodecsfound++;
					}
				}
			}


			pwszResultInfo = L"Result Reporting phase.";

			LogTestInfoW(__FUNCTIONW__,
				L"HD Codecs %s expected, and %d were found.",
				fHDCodecsExpected ? L"were": L"were not",
				countHDCodecsfound);
			//StringCbPrintfW(pwszResultInfo, 1024, L"HD Codecs %s expected, and %d were found.",
			//	fHDCodecsExpected ? L"were": L"were not",
			//	countHDCodecsfound);

			if ((fHDCodecsExpected == TRUE) == (countHDCodecsfound != 0))
			{
				fHDCodecsPassed = TRUE;
			}
			else
			{
				fHDCodecsPassed = FALSE;
			}

		}
		else
		{
			LogTestInfoW(__FUNCTIONW__, L"Could not access combobox with Codec names.");
		}

		LogTestResultW(fHDCodecsPassed, __FUNCTIONW__, pwszResultInfo);

		LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");

		TypeString(L"{ESC}"); // more reliable than trying to hit Cancel for some reason.

		return NOERROR;
	}
	catch (...)
	{
		LogTestInfoW(__FUNCTIONW__, L"%s reporting FAIL due to an unhandled unexpected exception.", __FUNCTIONW__);
		LogTestResultW(FALSE, __FUNCTIONW__, L"Test Code Failure");
		return E_FAIL;
	}
}
