#include <windows.h>            //Common Windows types
//#include "rpf_constants.h"
#include "screenelement.h"             //RPF
#include "LoggingFunctions.h"
#include "rpf_skudiff.h" // SKU Diff Contants
#include "SKUDIFF_UTIL.h"

using namespace SKUDiff; 

LanguageNeutralString langNeutralRecordedTV(L"Recorded TV");
LanguageNeutralString langNeutralSampleMedia(L"Sample Media");
LanguageNeutralString langNeutralApollo13(L"Apollo 13");
LanguageNeutralString langNeutralJewelsofCaribbean(L"Jewels of Caribbean");
LanguageNeutralString langNeutralVertigo(L"Vertigo");


STDAPI InitTest(LPVOID)
{
	HRESULT hr = SKUInitTest();
	//if SUCCEEDED(hr){CloseExcessWindows();}
	return hr;
}

STDAPI UnInitTest()
{
	return SKUUnInitTest();
}

//    
//    VerifyWmp_StartMenuEntryPoint 
//  
STDAPI VerifyMediaSampleFiles(LPVOID pvReserved)
{
    BOOL    fPassed = FALSE;
    LPWSTR pwszResultInfo = NULL;
    HRESULT hr = E_FAIL;
   

    LogTestBeginW(__FUNCTIONW__, L"Verify Sample Media Files are available");    
	// Log WEI scores
	Assessment();
          

	BOOL fExpected = FALSE;
	BOOL fFoundMediaFiles = FALSE;

    DWORD dwProductInfoType = 0;
	if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
    {
        switch (dwProductInfoType)
        {
            case PRODUCT_BUSINESS_N:
            case PRODUCT_HOME_BASIC_N:
			case PRODUCT_HOME_PREMIUM_N:
            case PRODUCT_ENTERPRISE_N:
            case PRODUCT_ULTIMATE_N:
            case PRODUCT_STARTER:
            case PRODUCT_HOME_BASIC:
            case PRODUCT_BUSINESS:
            case PRODUCT_ENTERPRISE:
				pwszResultInfo = L"Sample Media Files are not expected here.";
                break;
			case PRODUCT_HOME_PREMIUM:
            case PRODUCT_ULTIMATE:
                fExpected = TRUE;
                pwszResultInfo = L"Sample Media Files are expected here.";
                break;
            default:
                LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
                pwszResultInfo = L"Could not verify behavior";
                break;
        }
	}


	LPDWORD lpVolumeSerialNumber = 0;
    LPDWORD lpMaximumComponentLength = 0;
    LPDWORD lpFileSystemFlags = 0;
  
	char pszDrives[1024];
	char pszLabel[1024];
	wchar_t pwszLabel[1024];
	wchar_t pwszTemplate[1024];
    char pszFSName[16];
    bool bFound = false;


	wchar_t szDrive[4] = (L" :\\");
	if(GetLogicalDriveStrings(1024,pszDrives))
	{
		char* p = pszDrives;
		do {
			if(GetDriveTypeA(p) == 3) // 3 means it's a hard drive (5 for DVD rom...)
			{
				GetVolumeInformation(  p,  pszLabel,  1024,  lpVolumeSerialNumber,  lpMaximumComponentLength,  lpFileSystemFlags,  pszFSName,  16);
				if (strcmp(pszFSName, "NTFS") == 0) // only NTFS Drives are considered
				{
					LogTestInfoA(__FUNCTION__, "Detected %s Fixed Disk named %s at %s", &pszFSName, &pszLabel, p);  
					*szDrive = *p; // Note: Conversion from single byte to double byte character... it's a drive letter, so safe.
					bFound=true;
				}

			}
			while (*p++); // next drive
		} while (*p && !bFound); // end of string //
	}
	if (bFound)
	{
		
		if (strcmp(pszLabel, "") == 0) // drive is unlabeled
		{
			ExtractResourceString(resKeyDefaultLabel, pwszLabel, 1024);
			//pwszLabel = (wchar_t*)resKeyDefaultLabel;

		}
		else
		{
			mbstowcs(pwszLabel,pszLabel, 512);
		}

		//LogTestInfoW(__FUNCTIONW__, L"Using Fixed Disk at %s", &szDrive);  
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"No suitable drives detected, aborting");
		return E_FAIL;
	}
	LogTestInfoW(__FUNCTIONW__, L"Using label [%s]",pwszLabel);
	//resKeyDefaultLabel = L";Local Disk;Win32String;%windir%\\system32\\shell32.dll;9404";
	//resKeyDriveTemplate = L";Drive Template;Win32String;%windir%\\system32\\shell32.dll;9224"; "%1!ls! (%2!c!:)"
	WOWGetResKeyValue(resKeyDriveTemplate, 1024, pwszTemplate);
	//ExtractResourceString(resKeyDriveTemplate, pwszTemplate, 1024);
	wchar_t pwszResult[1024] = L"###";
	wchar_t* pwszFirstParam = wcsstr(pwszTemplate, L"%1!ls!");
	wchar_t* pwszSecondParam = wcsstr(pwszTemplate, L"%2!c!");
	wcsncat_s(pwszResult,1024,pwszTemplate, pwszFirstParam - pwszTemplate); //beginning to drive label

	wcsncat_s(pwszResult,1024,pwszLabel,_TRUNCATE); //drive labe;

	wcsncat_s(pwszResult,1024,pwszFirstParam+6,pwszSecondParam-(pwszFirstParam+6)); //middle

	wcsncat_s(pwszResult,1024,szDrive,1); //drive letter, single character copied

	wcsncat_s(pwszResult,1024,pwszSecondParam+5,_TRUNCATE); //after drive letter toend
	
	wcsncat_s(pwszResult,1024,L"###",_TRUNCATE); //after drive letter toend
	
	//wcsstr(pwszTemplate, L"%1!ls!")
	//wcsstr(pwszTemplate, L"%2!c!")
	LogTestInfoW(__FUNCTIONW__, L"Composed text: [%s]",pwszResult);







	if (! SUCCEEDED(OpenStartMenu()))
	{
		LogTestInfoW(__FUNCTIONW__, L"GetProductInfo : Start Button failed.");
		pwszResultInfo = L"GetProductInfo : Start Button failed.";
		LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
		return NOERROR;
	}
    hr = LOG_FAILED_HR(WOWFromPartialQueryId(STARTMENU_COMPUTER)); 
    if (!SUCCEEDED(hr))
    {
			LogTestInfoW(__FUNCTIONW__, L"GetProductInfo : COMPUTER failed.");
			pwszResultInfo = L"GetProductInfo : COMPUTER failed.";
		    LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;
	}
	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'CabinetWClass';Role = 'list' && ClassName = 'SysListView32';Name = '{1}' && Role = 'list item'", resKeyComputer, (wchar_t*) pwszResult));  //COMPUTER_LOCALDRIVE
	if (!SUCCEEDED(hr)) //checking for Local Drive 
	{
		LogTestInfoW(__FUNCTIONW__, L"GetProductInfo : LOCAL DRIVE C failed.");
		pwszResultInfo = L"GetProductInfo : LOCAL DRIVE C failed.";
		LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
		return NOERROR;
	}
	LOG_FAILED_HR(DoubleClick(CLICKABLE_POINT));// C:
	hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'CabinetWClass';[VisibleOnly]Role = 'list' && ClassName = 'SysListView32';Name = '{1}' && Role = 'list item'", (wchar_t*) pwszResult, resKeyUsers));
	if (!SUCCEEDED(hr))
	{
		LogTestInfoW(__FUNCTIONW__, L"GetProductInfo : USERS failed.");
		pwszResultInfo = L"GetProductInfo : USERS failed.";
		LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
		return NOERROR;
	}
	LOG_FAILED_HR(DoubleClick(CLICKABLE_POINT));// Open Users folder
	hr = LOG_FAILED_HR(WOWFromPartialQueryId(USERS_PUBLIC));
	if(!SUCCEEDED(hr))
	{
		LogTestInfoW(__FUNCTIONW__, L"GetProductInfo : PUBLIC failed.");
		pwszResultInfo = L"GetProductInfo : PUBLIC failed.";
		LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
		return NOERROR;
	}
	LOG_FAILED_HR(DoubleClick(CLICKABLE_POINT)); // open public folder
	hr = LOG_FAILED_HR(WOWFromPartialQueryId(PUBLIC_RECORDEDTV));
	if(!SUCCEEDED(hr))
	{
		if (fExpected) // Recorded TV folder not found on an Supported SKU - Test FAILS
		{
			fPassed = FALSE;
			LogTestInfoW(__FUNCTIONW__, L"GetProductInfo : RECORDED TV failed.");
			pwszResultInfo = L"GetProductInfo : RECORDED TV failed.";
			LogTestInfoW(__FUNCTIONW__,
				L"Sample Media files SKU differentiation failed.[Current: %s | Expected: %s ]",
				fFoundMediaFiles ? L"Found": L"Not Found",
				fExpected ? L"Found" : L"Not Found");
			
		}
		else // Recorded TV folder not found on an Unsupported SKU - Test PASSES
		{
			fPassed = TRUE;
			pwszResultInfo = L"Sample Media file entry point is differentiated correctly";
			
		}
	LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");
    
    hr = LOG_FAILED_HR(WOWFromPartialQueryId(PUBLIC_CLOSE));
    if (SUCCEEDED(hr))
    {
       LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }
		LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
		return NOERROR;
	}
	LOG_FAILED_HR(DoubleClick(CLICKABLE_POINT));
	hr = LOG_FAILED_HR(WOWFromPartialQueryId(RECORDEDTV_SAMPLEMEDIA));
	if(!SUCCEEDED(hr))
	{	
		LogTestInfoW(__FUNCTIONW__, L"GetProductInfo : MEDIA SAMPLE failed.");
		pwszResultInfo = L"GetProductInfo : MEDIA SAMPLE failed.";
		LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
		return NOERROR;
	}
	LOG_FAILED_HR(DoubleClick(CLICKABLE_POINT));
	//If either one of the sample files are missing the test case fails.
	if(!SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(SAMPLEMEDIA_APOLLO13))) || 
		!SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(SAMPLEMEDIA_CARIBBEAN))) || 
		!SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(SAMPLEMEDIA_VERTIGO))) )
	{
			LogTestInfoW(__FUNCTIONW__, L"GetProductInfo :  SAMPLE FILES failed.");
			pwszResultInfo = L"GetProductInfo : SAMPLE FILES failed.";
			LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
			return NOERROR;
					
	}
	fFoundMediaFiles = TRUE;
	if (fFoundMediaFiles != fExpected)
	{
		LogTestInfoW(__FUNCTIONW__,
			L"Sample Media files SKU differentiation failed.[Current: %s | Expected: %s ]",
			fFoundMediaFiles ? L"Found": L"Not Found",
			fExpected ? L"Found" : L"Not Found");
	}
	else
	{
		fPassed = TRUE;
		pwszResultInfo = L"Sample Media file entry point is differentiated correctly";
	}


	LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");
    
    hr = LOG_FAILED_HR(WOWFromPartialQueryId(SAMPLEMEDIA_CLOSE));
    if (SUCCEEDED(hr))
    {
       LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }


	LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}
