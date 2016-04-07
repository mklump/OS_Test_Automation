#include <windows.h>            //Common Windows types
//#include "rpf_constants.h"
#include "screenelement.h"             //RPF
#include "LoggingFunctions.h"
#include "rpf_SKUDIFF.h"
#include "SKUDIFF_UTIL.h"



using namespace RPFPlayback;
using namespace SKUDiff;


STDAPI InitTest(LPVOID)
{
	HRESULT hr = SKUInitTest();
	return hr;
}

STDAPI UnInitTest()
{
	return SKUUnInitTest();
}



STDAPI VerifyCreatingNewMeeting(LPVOID pvReserved)
{
	BOOL    fPassed = FALSE;
    	LPWSTR pwszResultInfo = NULL;
	BOOL fCanCreateMeeting = FALSE;
    	HRESULT hr = E_FAIL;
    
	LogTestBeginW(__FUNCTIONW__, L"Create a meeting Feature - available in Meeting Space");    
	// Log WEI scores
	Assessment();
 	

	BOOL fExpected = FALSE;
	BOOL fFoundCreateNewMeeting= FALSE;

	DWORD dwProductInfoType = 0;
	if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
	{
       	 switch (dwProductInfoType)
        	{
           		
           		
		    	case PRODUCT_STARTER: 
	    			pwszResultInfo = L"Meeting Space  is not expected here.";
                    		break;
			case PRODUCT_HOME_BASIC_N:
			case PRODUCT_HOME_BASIC:
				fExpected = TRUE;
				fCanCreateMeeting = FALSE;
				break;
			case PRODUCT_HOME_PREMIUM_N:        		
			case PRODUCT_HOME_PREMIUM:
			case PRODUCT_BUSINESS_N:
			case PRODUCT_BUSINESS:
			case PRODUCT_ENTERPRISE_N:
			case PRODUCT_ENTERPRISE:
			case PRODUCT_ULTIMATE_N:
			case PRODUCT_ULTIMATE:
					fExpected = TRUE;
					fCanCreateMeeting =TRUE;
               		pwszResultInfo = L"Meeting Space is expected here.";
               		break;
           		default:
                	LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
                	pwszResultInfo = L"Could not verify behavior";
				  	 break;
       	 }
	}


	DWORD cchComputerNameSize = 64;
	char szComputerName[64];
	wchar_t pwszComputerName[1024];
	GetComputerName(szComputerName, &cchComputerNameSize);
	int i;
	i = mbstowcs(pwszComputerName, szComputerName,1024 );
	LogTestInfoW(__FUNCTIONW__, L"Computer Name == %s",pwszComputerName);


	
	if (SUCCEEDED(OpenAllPrograms()))
	{
		hr = (WOWFromPartialQueryId(STARTMENU_WINDOWS_MEETING_SPACE));
		if (FAILED(hr))
		{
			fFoundCreateNewMeeting = FALSE;
			if(fFoundCreateNewMeeting != fExpected)
			{
				LogTestInfoW(__FUNCTIONW__,
				L"Windows Meeting Space SKU differentiation failed.[Current: %s | Expected: %s ]",
				fFoundCreateNewMeeting? L"Found": L"Not Found",
				fExpected ? L"Found" : L"Not Found");
			}
			else
			{
				fPassed = TRUE;
				pwszResultInfo = L"Windows Meeting Space entry point is differentiated correctly";
			}

			LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;
		}
	}

	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	Snooze();
	// This dialog will only be prompted the first time when you start Meeting space.
	hr = (WOWFromPartialQueryId(WINDOWS_MEETING_SPACE_SETTINGS));
	if (SUCCEEDED(hr))
	{	
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		LanguageNeutralString langNeutralDisplayName(pwszComputerName);
		ScreenElement* pScreenElement;
		if(NULL != (pScreenElement = ScreenElement::FromPartialQueryId(MEETING_SPACE_DISPLAY_NAME)))
		{

			wchar_t  pszValueForlangNeutralDisplayName[1024];
			ExtractResourceString(langNeutralDisplayName, pszValueForlangNeutralDisplayName, ARRAYSIZE(pszValueForlangNeutralDisplayName));
			pScreenElement->SetValueAsEditBox(pszValueForlangNeutralDisplayName);
			delete pScreenElement;
		}
		
			
		hr= (WOWFromPartialQueryId(PEOPLE_NEAR_ME));
		if(SUCCEEDED(hr))
		{
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));	
		}
	}
	
	hr = (WOWFromPartialQueryId(WINDOWS_MEETING_SPACE_START_A_NEW_MEETING));
	if(FAILED(hr))
	{
		LogTestInfoW(__FUNCTIONW__, L"Cannot find Create a new meeting");
		pwszResultInfo = L"Cannot find Create a new meeting";
		LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
		return NOERROR;
	}
	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));



	hr = (WOWFromPartialQueryId(MEETING_SPACE_MEETING_NAME));
	if(FAILED (hr))
	{
		//Home Basic has a "Start a New Meeting" button doesnt allow you to create a new meeting. 
		//Checking for textbox for entering the meeting determines the result of the test case
		fFoundCreateNewMeeting=FALSE;
		if(fFoundCreateNewMeeting != fCanCreateMeeting)
		{
			LogTestInfoW(__FUNCTIONW__,
			L"Windows Meeting Space SKU differentiation failed.[Current: %s | Expected: %s ]",
			fFoundCreateNewMeeting? L"Found": L"Not Found",
			fExpected ? L"Found" : L"Not Found");
		}
		else
		{
			fPassed = TRUE;
			pwszResultInfo = L"Windows Meeting Space entry point is differentiated correctly";
		}

		//close the two windows
		hr = LOG_FAILED_HR(FromPartialQueryId(MEETING_SPACE_GENERAL_CLOSE));
		if(SUCCEEDED(hr))
		{
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		}
		
		hr = LOG_FAILED_HR(FromPartialQueryId(MEETING_SPACE_GENERAL_CLOSE));
		if (SUCCEEDED(hr))
		{
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		}
		


		LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
		return NOERROR;
	}
	
 
	LanguageNeutralString langNeutralMeetingName(pwszComputerName); // Meeting name is same as the computer name
	LanguageNeutralString langNeutralPasswd(L"Abcd1234");	// password for the new meeting that is being created
	
	//enter the meeting name
	ScreenElement* pScreenElement;
	if(NULL != (pScreenElement = ScreenElement::FromPartialQueryId(MEETING_SAPCE_GENERAL_MEETING_NAME)))
	{

		wchar_t pszValueForlangNeutralMeetingName[1024];
		ExtractResourceString(langNeutralMeetingName, pszValueForlangNeutralMeetingName, ARRAYSIZE(pszValueForlangNeutralMeetingName));
		pScreenElement->SetValueAsEditBox(pszValueForlangNeutralMeetingName);
		delete pScreenElement;
	}
	
	// enter a password that is used to join the meeting
	ScreenElement* pScreenElement1;
	if(NULL != (pScreenElement1 = ScreenElement::FromPartialQueryId(MEETING_SPACE_MEETING_PASSWORD)))
	{

		wchar_t pszValueForlangNeutralPasswd[1024];
		ExtractResourceString(langNeutralPasswd, pszValueForlangNeutralPasswd, ARRAYSIZE(pszValueForlangNeutralPasswd));
		pScreenElement->SetValueAsEditBox(pszValueForlangNeutralPasswd);
		delete pScreenElement1;
	}

	//Since OK button is an clickable image hit enter to create a new meeting
	ScreenElement* pScreenElement2;
	if(NULL != (pScreenElement2= ScreenElement::FromPartialQueryId(MEETING_SPACE_MEETING_PASSWORD)))
	{
		TypeString(L"{ENTER}");
		delete pScreenElement2;
	}

	ComplexResourceKeyNative cmplxKeyWindowsMeetingSpace(1, resKeyWindowsMeetingSpaceMeeting, langNeutralMeetingName); 
	hr = (WOWFromPartialQueryId(WINDOWS_MEETING_SPACE_MEETING_TITLE_BAR)); 
	if(SUCCEEDED(hr))
	{
		// If a new window with the specified meeting name was create test case passes.
		fFoundCreateNewMeeting=TRUE;
	}
	
	if(fFoundCreateNewMeeting != fCanCreateMeeting)
	{
		LogTestInfoW(__FUNCTIONW__,
		L"Windows Meeting Space SKU differentiation failed.[Current: %s | Expected: %s ]",
		fFoundCreateNewMeeting? L"Found": L"Not Found",
		fExpected ? L"Found" : L"Not Found");
	}
	else
	{
		fPassed = TRUE;
		pwszResultInfo = L"Windows Meeting Space entry point is differentiated correctly";
	}

	LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");


	
	hr = LOG_FAILED_HR(WOWFromPartialQueryId(WINDOWS_MEETING_SPACE_MEETING_CLOSE));
	if (SUCCEEDED(hr))
	{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	}

	
	//Final attempt to close any open window
	wchar_t szGlobalQuery[1024];
	GlobalizeQueryId(szGlobalQuery, 1024,MEETING_SPACE_GENERAL_CLOSE);
	LeftClickUntilGone(szGlobalQuery);
	GlobalizeQueryId(szGlobalQuery, 1024,WINDOWS_MEETING_SPACE_MEETING_CLOSE);
	LeftClickUntilGone(szGlobalQuery);

	LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
	return NOERROR;


	
}
	
	




