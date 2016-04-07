#include "screenelement.h"				// RPF
#include "SKUDIFF_UTIL.h"
#include "rpf_SKUDIFF.h"                // SKU Header
#include "Winsatcominterfacei.h" // Windows Experience Index
#include "LoggingFunctions.h"			// MASH

//#include <windows.h>					// Common Windows types
//#include "Winsatcominterfacei.h"		// Windows Experience Index
//#include "unknwn.h"						// For custom logger
//#include "LoggingFunctions.h"			// MASH
namespace SKUDiff
{

	/////////////////////////////////////////////////////
	// Used by the library functions to log information, 
	// each line is prefixed by a number of hyphens to indicate depth of the call stack
	/////////////////////////////////////////////////////
	// TODO: move to logging functions .cpp file
	HRESULT LibraryLogInfoW(__in LPWSTR pwszFuncName, __in LPWSTR pwszTestInfo, ...)
	{
		try
		{
			va_list vaArgs;
			va_start(vaArgs, pwszTestInfo);
			HRESULT hr = S_OK;

			//if (LibraryLogDetail == TRUE)
			{
				WCHAR wszFmTestInfo[MAX_DESCRIPTION];
				StringCchVPrintfW(wszFmTestInfo, ARRAYSIZE(wszFmTestInfo), pwszTestInfo, vaArgs);
				int i = 0;
				while (i++ < (MAX_DESCRIPTION - 1))
				{
					if (wszFmTestInfo[i] == L'%')
					{
						wszFmTestInfo[i] = L'_';
					}
				}

				i = 0;
				wchar_t wszIndent[] = L"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
				while (i++ < LibraryDepth && i < 16)
				{
					wszIndent[i-1] = L'-';
				}
				LogTestInfoW(pwszFuncName, L"%s(%d)LIB: %s", wszIndent, LibraryDepth, wszFmTestInfo);
				//LogTestInfoW(pwszFuncName, L"LIB: %s", wszFmTestInfo);
			}
			va_end(vaArgs);
			return hr;
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"%s returning E_FAIL due to an exception, probably passed a bad string.", __FUNCTIONW__);
			return E_FAIL;
		}
	}


	HRESULT LogResKeyValue(__in const wchar_t* szResourceKeyName,__in const wchar_t* szResourceKey)
	{
		//TODO: exceptions
		LOGLIBENTER;
		wchar_t szResourceString[1024];

		HRESULT hrx = E_FAIL;
		hrx = ExtractResourceString(szResourceKey, szResourceString, 1024);
		if (SUCCEEDED(hrx))
		{
			LogTestInfoW(__FUNCTIONW__,	L"[%s] = [%s] = [%s]",	szResourceKeyName, szResourceKey, szResourceString);
		}
		else
		{
			LogTestInfoW(__FUNCTIONW__,	L"[%s] = [%s] = empty",	szResourceKeyName, szResourceKey );
		}
		LOGLIBRETURN_HRESULT(hrx);
	}
	// Just writes the name of the current SKU to the log.

	void LogSKU()
	{
		LOGLIBENTER;
		DWORD dwProductInfoType = 0;
		if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
		{
			switch (dwProductInfoType)
			{
			case PRODUCT_STARTER:
				LogTestInfoW(__FUNCTIONW__, L"Starter");
				break;
			case PRODUCT_HOME_BASIC:
				LogTestInfoW(__FUNCTIONW__, L"Home Basic");
				break;
			case PRODUCT_HOME_BASIC_N:
				LogTestInfoW(__FUNCTIONW__, L"Home Basic N");
				break;
			case PRODUCT_BUSINESS:
				LogTestInfoW(__FUNCTIONW__, L"Business");
				break;
			case PRODUCT_BUSINESS_N:
				LogTestInfoW(__FUNCTIONW__, L"Business N");
				break;
			case PRODUCT_ENTERPRISE:
				LogTestInfoW(__FUNCTIONW__, L"Enterprise");
				break;
			case PRODUCT_ENTERPRISE_N:
				LogTestInfoW(__FUNCTIONW__, L"Enterprise N");
				break;
			case PRODUCT_HOME_PREMIUM:
				LogTestInfoW(__FUNCTIONW__, L"Home Premium");
				break;
			case PRODUCT_HOME_PREMIUM_N:
				LogTestInfoW(__FUNCTIONW__, L"Home Premium N");
				break;
			case PRODUCT_ULTIMATE:
				LogTestInfoW(__FUNCTIONW__, L"Ultimate");
				break;
			case PRODUCT_ULTIMATE_N:
				LogTestInfoW(__FUNCTIONW__, L"Ultimate N");
				break;
			default:
				LogTestInfoW(__FUNCTIONW__, L"Unknown SKU");
				break;
			}
		}
		else
		{
			LogTestInfoW(__FUNCTIONW__, L"GetProductInfo failed.");
		}
		LOGLIBRETURN_void();
	}
	// Writes the values of Windows Experiance Index ratings to the log file, some tests depend on min values.

	void Assessment()
	{
		LOGLIBENTER;
		HRESULT hr = S_OK;
		IQueryRecentWinSATAssessment* pAssessment;
		IProvideWinSATResultsInfo* pResults = NULL;
		IProvideWinSATAssessmentInfo* pSubcomponent = NULL;
		BSTR bstrTitle = NULL;
		float score = 0.0;

		hr = CoCreateInstance(__uuidof(CQueryWinSAT),
			NULL,
			CLSCTX_INPROC_SERVER,
			__uuidof(IQueryRecentWinSATAssessment),
			(void**)&pAssessment);

		if (SUCCEEDED(hr))
		{
			hr = pAssessment->get_Info(&pResults);
			if (SUCCEEDED(hr))
			{
				hr = pResults->GetAssessmentInfo(WINSAT_ASSESSMENT_CPU, &pSubcomponent);
				if (SUCCEEDED(hr))
				{
					pSubcomponent->get_Score(&score);
					pSubcomponent->get_Title(&bstrTitle);
					//wprintf(L"%s %.1f\n", bstrTitle, score);
					LogTestInfoW(__FUNCTIONW__, L"%s (CPU) %.1f\n", bstrTitle, score);
					SysFreeString(bstrTitle);
					pSubcomponent->Release();
				}

				hr = pResults->GetAssessmentInfo(WINSAT_ASSESSMENT_MEMORY, &pSubcomponent);
				if (SUCCEEDED(hr))
				{
					pSubcomponent->get_Score(&score);
					pSubcomponent->get_Title(&bstrTitle);
					LogTestInfoW(__FUNCTIONW__, L"%s (Memory) %.1f\n", bstrTitle, score);
					SysFreeString(bstrTitle);
					pSubcomponent->Release();
				}

				hr = pResults->GetAssessmentInfo(WINSAT_ASSESSMENT_GRAPHICS, &pSubcomponent);
				if (SUCCEEDED(hr))
				{
					pSubcomponent->get_Score(&score);
					pSubcomponent->get_Title(&bstrTitle);
					LogTestInfoW(__FUNCTIONW__, L"%s (2D) %.1f\n", bstrTitle, score);
					SysFreeString(bstrTitle);
					pSubcomponent->Release();
				}


				hr = pResults->GetAssessmentInfo(WINSAT_ASSESSMENT_D3D, &pSubcomponent);
				if (SUCCEEDED(hr))
				{
					pSubcomponent->get_Score(&score);
					pSubcomponent->get_Title(&bstrTitle);
					LogTestInfoW(__FUNCTIONW__, L"%s (3D) %.1f\n", bstrTitle, score);
					SysFreeString(bstrTitle);
					pSubcomponent->Release();
				}

				hr = pResults->GetAssessmentInfo(WINSAT_ASSESSMENT_DISK, &pSubcomponent);
				if (SUCCEEDED(hr))
				{
					pSubcomponent->get_Score(&score);
					pSubcomponent->get_Title(&bstrTitle);
					LogTestInfoW(__FUNCTIONW__, L"%s (Disk) %.1f\n", bstrTitle, score);
					SysFreeString(bstrTitle);
					pSubcomponent->Release();
				}

				pResults->Release();
				pResults = NULL;
			}
			else
			{
				// Handle error
			}

			pAssessment->Release();
			pAssessment = NULL;
		}
		else
		{
			// Handle error
		}
		LOGLIBRETURN_void();
	}
}