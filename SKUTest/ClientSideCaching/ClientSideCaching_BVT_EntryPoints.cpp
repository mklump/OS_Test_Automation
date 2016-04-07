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

HRESULT BufferFile(__in PCWSTR  Filename, __deref_inout PWSTR &wBuffer);

using namespace SKUDiff;

wchar_t* pwszPathFromFile;
wchar_t* pwszPath;

char szMyPath [1024]; 

wchar_t pwszComputerName[1024];
char szComputerName[64];

LanguageNeutralString langNeutralParentFolder(L"SKU");



void GetMyComputerName()
{
	DWORD cchComputerNameSize = 64;
	if (GetComputerName(szComputerName, &cchComputerNameSize))
	{
	LogTestInfoA(__FUNCTION__, "Computer name is (%s)", szComputerName);
	
	strncat_s(szMyPath,1024,"\\",cchComputerNameSize);
	strncat_s(szMyPath,1024,szComputerName,cchComputerNameSize);
	

	LogTestInfoA(__FUNCTION__, "Path is (%s)", szMyPath);
	}
	else
	{
	LogTestInfoA(__FUNCTION__, "Computer name unavailable");
	}
}


void CreateFolder()
{
	BOOL fFolderCreated;
	fFolderCreated = g_AutomationObjects.SHTestEx.spFileSystem->CreateTestFolder(szMyPath);//
	if (fFolderCreated == TRUE)
	{
		LogTestInfoW(__FUNCTIONW__, L"Folder created");
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Folder could not be created");
	}
}

void DeleteFolder()
{
	BOOL fFolderDeleted;
	fFolderDeleted = g_AutomationObjects.SHTestEx.spFileSystem->DeleteTestFolder(szMyPath);//
	if (fFolderDeleted == TRUE)
	{
		LogTestInfoW(__FUNCTIONW__, L"Folder deleted");
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Folder could not be deleted");
	}

}
STDAPI InitTest(LPVOID)
{
	HRESULT hr = SKUInitTest();
	if SUCCEEDED(hr)
	{
		//SetRobustnessLevel(0);
		LOG_FAILED_HR(hr = InitializeAutomationObjects(SHTESTEX_FILESYSTEM));
	}
	return hr;
}

STDAPI UnInitTest()
{
	//CloseExcessWindows();
	DeleteFolder();
	wchar_t szGlobalQuery[1024];
	GlobalizeQueryId(szGlobalQuery, 1024, SKU_FOLDER_CLOSE );
	LeftClickUntilGone(szGlobalQuery);
	LOG_FAILED_HR(UninitializeAutomationObjects());
	return SKUUnInitTest();
}


STDAPI VerifyClientSideCaching(LPVOID pvReserved)
{
    BOOL    fPassed = FALSE;
    LPWSTR pwszResultInfo = NULL;
    HRESULT hr = E_FAIL;
    
	LogTestBeginW(__FUNCTIONW__, L"Verify Client Side Caching is available on Network Share");    
	// Log WEI scores
	Assessment();

 	 	

	BOOL fExpected = FALSE;
	BOOL fFoundAlwaysAvailableOffline= FALSE;

	DWORD dwProductInfoType = 0;
	if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
	{
       	 switch (dwProductInfoType)
        	{
           		
           		case PRODUCT_HOME_BASIC_N:
		    	case PRODUCT_HOME_PREMIUM_N:        		
		        case PRODUCT_STARTER: 
	    		case PRODUCT_HOME_PREMIUM:
           		case PRODUCT_HOME_BASIC:
          		 	pwszResultInfo = L"Always Available Offline is not expected here.";
                    break;
				case PRODUCT_BUSINESS_N:
				case PRODUCT_BUSINESS:
				case PRODUCT_ENTERPRISE_N:
           		case PRODUCT_ENTERPRISE:
				case PRODUCT_ULTIMATE_N:
				case PRODUCT_ULTIMATE:
					fExpected = TRUE;
               		pwszResultInfo = L"Always Available Offline is expected here.";
               		break;
           		default:
                	LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
                	pwszResultInfo = L"Could not verify behavior";
				  	 break;
       	 }
	}

	if(SUCCEEDED(BufferFile(L"network_path.txt",pwszPathFromFile)))
	{
		LogTestInfoW(__FUNCTIONW__,L"Text read from file network_path.txt = %s", pwszPathFromFile);
	}
	
	

	wchar_t* ch;
	ch = L"*";
	
	pwszPath = wcstok(pwszPathFromFile,ch);
	
	// If the test case fails Look for these two lines in the log
	LogTestInfoW(__FUNCTIONW__, L"%s!",pwszPath);
	LogTestInfoW(__FUNCTIONW__, L"If the ! is in the begining of new line then the Path provided in WTT Job doesn't end with * ");
	//If the test case fails Look for two lines in the log
	
	LanguageNeutralString langNeutralURL(pwszPath);
	int c;
	c = wcstombs(szMyPath,  pwszPath ,1024);

	GetMyComputerName();
 
	
	//Win+R key stroke
	ScreenElement* pScreenElement;
	if(NULL != (pScreenElement = ScreenElement::FromPartialQueryId(WINDOW_DESKTOP)))
	{
		TypeString(L"`r");
		delete pScreenElement;
	}

	ScreenElement* pScreenElement1;
	if(NULL != (pScreenElement1 = ScreenElement::FromPartialQueryId(RUN_DIALOG)))
	{

		wchar_t pszValueForlangNeutralURL[1024];
		ExtractResourceString(langNeutralURL, pszValueForlangNeutralURL, ARRAYSIZE(pszValueForlangNeutralURL));

		pScreenElement1->SetValueAsEditBox(pszValueForlangNeutralURL);
		delete pScreenElement1;
	}

	
	hr = LOG_FAILED_HR(WOWFromPartialQueryId(RUN_DIALOG_OK_BTN));
    if (SUCCEEDED(hr))  
    {
       	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	}
	
	Snooze();

	//If a domain users credentails are not cached on the machine then provide username and password on login

	wchar_t* pwszSharenameFromFile;
	wchar_t* pwszSharename;

	if(SUCCEEDED(BufferFile(L"network_sharename.txt",pwszSharenameFromFile)))
	{
		LogTestInfoW(__FUNCTIONW__, L"Text read from file network_sharename.txt = %s", pwszSharenameFromFile);
	}
	
	
	pwszSharename = wcstok(pwszSharenameFromFile,ch);
	
	// If the test case fails Look for these two lines in the log
	LogTestInfoW(__FUNCTIONW__, L"%s!",pwszSharename);
	LogTestInfoW(__FUNCTIONW__, L"If the ! is in the begining of new line then the Sharename provided in WTT Job doesn't end with * ");
	//If the test case fails Look for two lines in the log

	



	LanguageNeutralString langNeutralShare(pwszSharename);
	const wchar_t* resKeyConnectto = L"RKB1[];Connect to;Win32String;%windir%\\system32\\credui.dll;2008";
	ComplexResourceKeyNative cmplxKeyConnectToShare(1, resKeyConnectto,langNeutralShare);

	if(SUCCEEDED(WOWFromPartialQueryId(CONNECT_TO_SHARE_USERNAME)))
	{
		wchar_t pwszUsername[256];
		wchar_t pwszPasswd[256];
		GetLLU(L"LLU_Default",pwszUsername, 255, pwszPasswd, 255);
		LogTestInfoW(__FUNCTIONW__, L"The password for %s is %s",pwszUsername, pwszPasswd);
		

		LanguageNeutralString langNeutralUserName(pwszUsername);
		
		ScreenElement* pScreenElement2;
		if(NULL != (pScreenElement2 = ScreenElement::FromPartialQueryId(CONNECT_TO_SHARE_USERNAME)))
		{

			wchar_t pszValueForlangNeutralUserName[1024];
			ExtractResourceString(langNeutralUserName, pszValueForlangNeutralUserName, ARRAYSIZE(pszValueForlangNeutralUserName));
			
			pScreenElement2->SetValueAsEditBox(pszValueForlangNeutralUserName);
			delete pScreenElement2;
		}

		LanguageNeutralString langNeutralPasswd(pwszPasswd);

		ScreenElement* pScreenElement3;
		if(NULL != (pScreenElement3 = ScreenElement::FromPartialQueryId(CONNECT_TO_SHARE_PASSWORD)))
		{
			wchar_t pszValueForlangNeutralPasswd[1024];
			ExtractResourceString(langNeutralPasswd, pszValueForlangNeutralPasswd, ARRAYSIZE(pszValueForlangNeutralPasswd));
			pScreenElement3->SetValueAsEditBox(pszValueForlangNeutralPasswd);
			delete pScreenElement3;
		}

		hr = LOG_FAILED_HR(WOWFromPartialQueryId(CONNECT_TO_SHARE_OK ));
		if(SUCCEEDED(hr))
		{
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		}
	}//end of If<found the Connect to .... box>
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Did not prompt for username and password to access the share");
	}


	//Once the credentials are provided and Share URL opens create  a test Folder


	CreateFolder();	

	int i;
	i = mbstowcs(pwszComputerName, szComputerName,1024 );
	LogTestInfoW(__FUNCTIONW__, L"Computer Name == %s",pwszComputerName);
	 
		
	LanguageNeutralString langNeutralTestFolder(pwszComputerName);

	hr = LOG_FAILED_HR(WOWFromPartialQueryId(COMPUTER_NAME_FOLDER_ON_SHARE));
  									
	if (FAILED(hr))  
   	{   	
    	LogTestResultW(fPassed, __FUNCTIONW__, L"Couldn't locate the %s Folder",pwszComputerName);
	    return NOERROR;
	}
	
	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT)); // added to get it working on PS
	LOG_FAILED_HR(RightButtonClick(CLICKABLE_POINT));


	hr = LOG_FAILED_HR(WOWFromPartialQueryId(CMENU_ALWAYS_AVAILABLE_OFFLINE));
	if(SUCCEEDED(hr))
	{
		fFoundAlwaysAvailableOffline= TRUE;
	}

	if (fFoundAlwaysAvailableOffline!= fExpected)
		{
				LogTestInfoW(__FUNCTIONW__,
				L" Client Side Caching availability SKU differentiation failed.[Current: %s | Expected: %s ]",
				fFoundAlwaysAvailableOffline ? L"Found": L"Not Found",
				fExpected ? L"Found" : L"Not Found");
		}
		else
		{
			fPassed = TRUE;
			pwszResultInfo = L" Client Side Caching (Always Available Offline) entry point is differentiated correctly";
		}

	

	DeleteFolder();

	LogTestInfoW(__FUNCTIONW__, L"Cleaning up ...");

	hr = LOG_FAILED_HR(WOWFromPartialQueryId(SKU_FOLDER_CLOSE));

	if(SUCCEEDED(hr))
	{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	}
	
	//Final attempt to close any open window
	wchar_t szGlobalQuery[1024];
	GlobalizeQueryId(szGlobalQuery, 1024,SKU_FOLDER_CLOSE);
	LeftClickUntilGone(szGlobalQuery);
 
    LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}



HRESULT BufferFile(__in PCWSTR  Filename, __deref_inout PWSTR &wBuffer)
      {
            //TODO: Check if wildcards (*?) are in the given path.
            LogTestInfoW(__FUNCTIONW__, L"Attempting to buffer %s",Filename);
            WIN32_FIND_DATAW X;
            char* Buffer;
            HANDLE Y = FindFirstFileW(Filename,&X);
            if (Y != INVALID_HANDLE_VALUE)
            {
                  LogTestInfoW(__FUNCTIONW__, L"Find handle not Invalid");

                 // if (X.nFileSizeLow <= (2^16) )//&& X.nFileSizeHigh == 0
                  {
                        LogTestInfoW(__FUNCTIONW__, L"File not over 64k");
                        Buffer = (char*)malloc(X.nFileSizeLow+1);
			
                        if (Buffer)
                        {
                         	  memset(Buffer,'\0',X.nFileSizeLow+1);
                              LogTestInfoW(__FUNCTIONW__, L"Allocated %d bytes", X.nFileSizeLow+1);

                              HANDLE W = CreateFileW(Filename,FILE_READ_DATA,FILE_SHARE_READ,  NULL,  OPEN_EXISTING,  FILE_FLAG_SEQUENTIAL_SCAN,NULL);
                              if (W != INVALID_HANDLE_VALUE)
                              {
                                    LogTestInfoW(__FUNCTIONW__, L"File handle not Invalid");

                                    DWORD BytesRead;
                                    BOOL fReadFile;
                                    if(ReadFile(W,Buffer,X.nFileSizeLow,&BytesRead,NULL))
                                    {

                                          LogTestInfoW(__FUNCTIONW__, L"Read %d bytes", BytesRead);

                                          DWORD wBufferSize=MultiByteToWideChar(CP_UTF8,0,Buffer,BytesRead,(wchar_t*)Buffer,0);
                                          if(wBuffer = (wchar_t*)malloc((wBufferSize*sizeof(wchar_t))+2))
                                          {
							memset(wBuffer,'\0',(wBufferSize*sizeof(wchar_t))+2);
                                                LogTestInfoW(__FUNCTIONW__, L"Converting to %d characters",wBufferSize);

                                                if(MultiByteToWideChar(CP_UTF8,0,Buffer,BytesRead,wBuffer,wBufferSize))
                                                {                       

                                                      LogTestInfoW(__FUNCTIONW__, L"Succeeded");
                                                      CloseHandle(W);
                                                      free(Buffer);
                                                      return NOERROR;
                                                }
                                                free(wBuffer);
                                          }
                                    }
                                    CloseHandle(W);
                              }
                              free(Buffer);
                        }
                  }
            }
            wBuffer = NULL;
            return E_FAIL;    
      }













