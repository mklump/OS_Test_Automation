#include <windows.h>            //Common Windows types
//#include "rpf_constants.h"
#include "screenelement.h"             //RPF
#include "LoggingFunctions.h"
#include "rpf_skudiff.h" // SKU Diff Contants
#include "SKUDIFF_UTIL.h"
#include <AutomationObjectsInit.h>    
#include <shellapi.h>
//#include <shlobj.h> 
#include <oleacc.h>             //XACC
#include <ole2.h>

using namespace SKUDiff;

LanguageNeutralString langNeutralTestFolder(L"TestFolder");
LanguageNeutralString langNeutralTestFile(L"TestFile");

ComplexResourceKeyNative cmplxKeyPropertiesTestFolder(1, resKeyPropertiesTitleBar, langNeutralTestFolder);
ComplexResourceKeyNative cmplxKeyPropertiesTestFile(1, resKeyPropertiesTitleBar, langNeutralTestFile);

void CloseExcessWindows() // test specific, ensure a clean state; can be made better with RPF 12+
{
	wchar_t szGlobalQuery[1024];
	GlobalizeQueryId(szGlobalQuery, 1024, TESTFILE_ADVANCED_CANCEL);
	LeftClickUntilGone(szGlobalQuery);
	GlobalizeQueryId(szGlobalQuery, 1024, TESTFOLDER_ADVANCED_CANCEL);
	LeftClickUntilGone(szGlobalQuery);
	GlobalizeQueryId(szGlobalQuery, 1024, TESTFOLDER_PROPERTIES_CANCEL);
	LeftClickUntilGone(szGlobalQuery);
	GlobalizeQueryId(szGlobalQuery, 1024, TESTFILE_PROPERTIES_CANCEL);
	LeftClickUntilGone(szGlobalQuery);
	GlobalizeQueryId(szGlobalQuery, 1024, PUBLIC_CLOSE );
	LeftClickUntilGone(szGlobalQuery);
}

void DeleteFolderAndFile()
{
	g_AutomationObjects.SHTestEx.spFileSystem->DeleteTestFolder("C:\\users\\public\\TestFolder");
	g_AutomationObjects.SHTestEx.spFileSystem->DeleteTestFile("C:\\users\\public\\TestFile.txt");
}
STDAPI InitTest(LPVOID)
{
	HRESULT hr = SKUInitTest();
	if SUCCEEDED(hr)
	{
		CloseExcessWindows();
		LOG_FAILED_HR(InitializeAutomationObjects(SHTESTEX_FILESYSTEM));
		DeleteFolderAndFile();
	}
	return hr;
}

STDAPI UnInitTest()
{
	CloseExcessWindows();
	DeleteFolderAndFile();
	LOG_FAILED_HR(UninitializeAutomationObjects());
	return SKUUnInitTest();
}

//    
//    VerifyWmp_StartMenuEntryPoint 
//  
STDAPI VerifyEncryption(LPVOID pvReserved)
{
    BOOL    fPassed = FALSE;
    LPWSTR pwszResultInfo = NULL;
    HRESULT hr = E_FAIL;
   

    LogTestBeginW(__FUNCTIONW__, L"Verify File/Folder Encryption is available");    
	// Log WEI scores
	Assessment();
          

	BOOL fExpected = FALSE;
	
	BOOL fFileFoundEncryption = FALSE;
	BOOL fFilePassed = FALSE;
	
	BOOL fFolderFoundEncryption = FALSE;
	BOOL fFolderPassed = FALSE;

    DWORD dwProductInfoType = 0;
	if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
    {
        switch (dwProductInfoType)
        {
            case PRODUCT_BUSINESS_N:
            case PRODUCT_HOME_BASIC_N:
			case PRODUCT_HOME_PREMIUM_N:
            case PRODUCT_STARTER:
            case PRODUCT_HOME_BASIC:
			case PRODUCT_HOME_PREMIUM:
            	pwszResultInfo = L"File/Folder Encryption is not expected here.";
                break;
			case PRODUCT_BUSINESS:
            case PRODUCT_ENTERPRISE_N:
            case PRODUCT_ENTERPRISE:
            case PRODUCT_ULTIMATE_N:
			case PRODUCT_ULTIMATE:
                fExpected = TRUE;
                pwszResultInfo = L"File/Folder Encryption is expected here.";
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


	
	if (FAILED(OpenStartMenu()))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"GetProductInfo : Start Button failed.");
		return NOERROR;
	}
	hr = LOG_FAILED_HR(WOWFromPartialQueryId(STARTMENU_COMPUTER));// Loacte Computer on Start Menu
    if (FAILED(hr))
    {
		LogTestResultW(fPassed, __FUNCTIONW__, L"GetProductInfo : COMPUTER failed.");
		return NOERROR;
	}
	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));// click Computer in StartMenu
	hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'CabinetWClass';Role = 'list' && ClassName = 'SysListView32';Name = '{1}' && Role = 'list item'", resKeyComputer, (wchar_t*) pwszResult));  //Locate C: on Computer	
	if (FAILED(hr))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"GetProductInfo : LOCAL DRIVE C failed.");
		return NOERROR;
	}
	LOG_FAILED_HR(DoubleClick(CLICKABLE_POINT));// C:
	hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'CabinetWClass';[VisibleOnly]Role = 'list' && ClassName = 'SysListView32';Name = '{1}' && Role = 'list item'", (wchar_t*) pwszResult, resKeyUsers));// Locate Users on C:
	if (FAILED(hr))
	{
	 	LogTestResultW(fPassed, __FUNCTIONW__, L"GetProductInfo : USERS failed.");
		return NOERROR;
	}
	LOG_FAILED_HR(DoubleClick(CLICKABLE_POINT));// Open Users folder
	hr = LOG_FAILED_HR(WOWFromPartialQueryId(USERS_PUBLIC));// Locate Public folder in Users
	if(FAILED(hr))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"GetProductInfo : PUBLIC failed.");
		return NOERROR;
	}
	LOG_FAILED_HR(DoubleClick(CLICKABLE_POINT)); //Open Public folder
	
	
	// Create a new Folder
	BOOL fFolderCreated;
	fFolderCreated = g_AutomationObjects.SHTestEx.spFileSystem->CreateTestFolder("C:\\users\\public\\TestFolder");//
	if (fFolderCreated == TRUE)
	{
		LogTestInfoW(__FUNCTIONW__, L"Folder Created");
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Folder Not Created");
	}


	hr = LOG_FAILED_HR(WOWFromPartialQueryId(PUBLIC_TESTFOLDER));//Locate Test Folder just created
	if(FAILED(hr))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't loacte Test Folder.");
		return NOERROR;
	}

	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));// Added specially for Pseudo Loc
	LOG_FAILED_HR(RightButtonClick(CLICKABLE_POINT));//Click on Public Properties

	hr = LOG_FAILED_HR(WOWFromPartialQueryId(CMENU_PROPERTIES));//Locate properties on menu
	if(FAILED(hr))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't loacte Properties in popup menu.");
		return NOERROR;
	}
	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));//Click on Properties
	hr = LOG_FAILED_HR(WOWFromPartialQueryId(TESTFOLDER_PROPERTIES_ADVANCED));// click on Advanced Button
	if(FAILED(hr))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't Click Advanced... button");
		return NOERROR;
	}
	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));//Click on Advance...
	hr = LOG_FAILED_HR(WOWFromPartialQueryId(TESTFOLDER_CHECK_ENCRYPT));// check for encrypt checkbox
	if(FAILED(hr))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't Check Encrypt Checkbox");
		return NOERROR;
	}
	
	hr=Check();// clicks on Encrypt check box
	
	if(SUCCEEDED(hr))
	{
		fFolderFoundEncryption = TRUE; // Can check the checkbox on an supported SKU		
		LogTestInfoW(__FUNCTIONW__, L"Check Encrypt Folder Succeeded");
	}
	else
	{
		fFolderFoundEncryption = FALSE; // Can't check the check box on an unsupported SKU
		LogTestInfoW(__FUNCTIONW__, L"Check Encrypt Folder Failed");
	}
	
	
	if (fFolderFoundEncryption != fExpected)
	{
		fFolderPassed = FALSE;
		LogTestInfoW(__FUNCTIONW__,
			L"Folder Encryption SKU differentiation failed.[Current: %s | Expected: %s ]",
			fFolderFoundEncryption ? L"Found": L"Not Found",
			fExpected ? L"Found" : L"Not Found");
	}
	else
	{
		fFolderPassed = TRUE;
		pwszResultInfo = L"Folder Encryption is differentiated correctly";
	}

	
	// closing the windows that were open.

	LogTestInfoW(__FUNCTIONW__, L"Closing property windows for the folder...");
    
    hr = LOG_FAILED_HR(WOWFromPartialQueryId(TESTFOLDER_ADVANCED_CANCEL));
    if (SUCCEEDED(hr))
    {
       LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }
	
	hr = LOG_FAILED_HR(WOWFromPartialQueryId(TESTFOLDER_PROPERTIES_CANCEL));
    if (SUCCEEDED(hr))
    {
       LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }


	// Only window open now is Explorer with Users folder open
	// Create a text file and check for encryption

	BOOL fFileCreated;
	fFileCreated = g_AutomationObjects.SHTestEx.spFileSystem->CreateTestFile("C:\\users\\public\\TestFile.txt","This is a test");
	if (fFileCreated == TRUE)
	{
		LogTestInfoW(__FUNCTIONW__, L"File Created");
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"File Not Created");
	}


	hr = LOG_FAILED_HR(WOWFromPartialQueryId(PUBLIC_TESTFILE));//Locate Test File Created Above
	if(FAILED(hr))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't loacte test file.");
		return NOERROR;
	}

	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT)); // Added specially for Pseudo loc
	LOG_FAILED_HR(RightButtonClick(CLICKABLE_POINT));//Click on test file
	

	hr = LOG_FAILED_HR(WOWFromPartialQueryId(CMENU_PROPERTIES));//Locate properties on menu
	if(FAILED(hr))
	{
		LogTestResultW(fPassed, __FUNCTIONW__,L"Couldn't loacte Properties in popup menu.");
		return NOERROR;
	}
	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));//Click on Properties
	hr = LOG_FAILED_HR(WOWFromPartialQueryId(TESTFILE_PROPERTIES_ADVANCED));// click on Advanced Button
	if(FAILED(hr))
	{
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't Click Advanced... button");
		return NOERROR;
	}
	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));//Click on Advance...
	
	hr = LOG_FAILED_HR(WOWFromPartialQueryId(TESTFILE_CHECK_ENCRYPT));// look up for encrypt checkbox
	if(FAILED(hr))
	{
		;
		LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't Check File Encrypt Checkbox");
		return NOERROR;
	}
	hr = Check(); // check the checkbox
	//hr = LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));//Click on check box
	
	if(SUCCEEDED(hr))
	{
		fFileFoundEncryption = TRUE; // Can check the checkbox on an supported SKU		
		LogTestInfoW(__FUNCTIONW__, L"Check Encrypt File Succeeded");
	}
	else
	{
		fFileFoundEncryption = FALSE; // Can't check the check box on an unsupported SKU
		LogTestInfoW(__FUNCTIONW__, L"Check Encrypt File Failed");
	}
	
	
	if (fFileFoundEncryption != fExpected)
	{
		fFilePassed =FALSE;
		LogTestInfoW(__FUNCTIONW__,
			L"File Encryption SKU differentiation failed.[Current: %s | Expected: %s ]",
			fFileFoundEncryption ? L"Found": L"Not Found",
			fExpected ? L"Found" : L"Not Found");
	}
	else
	{
		fFilePassed = TRUE;
		pwszResultInfo = L"File Encryption is differentiated correctly";
	}

	// closing the windows that were open.

	LogTestInfoW(__FUNCTIONW__, L"Closing property windows for the folder...");
    
    hr = LOG_FAILED_HR(WOWFromPartialQueryId(TESTFILE_ADVANCED_CANCEL));
    if (SUCCEEDED(hr))
    {
       LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }
	
	hr = LOG_FAILED_HR(WOWFromPartialQueryId(TESTFILE_PROPERTIES_CANCEL));
    if (SUCCEEDED(hr))
    {
       LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }

	
	LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");

		
	

	hr = LOG_FAILED_HR(WOWFromPartialQueryId(PUBLIC_CLOSE));
    if (SUCCEEDED(hr))
    {
       LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }


	if(fFilePassed && fFolderPassed) // If Encryption on Folder and File found then test passes
	{
		fPassed = TRUE;
		pwszResultInfo = L"File/Folder Encryption is differentiated correctly";
	}
	else
	{
		fPassed = FALSE;
		pwszResultInfo = L"File Encryption is NOT differentiated correctly";
	}

	LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}




	