#include "screenelement.h"				// RPF
#include "SKUDIFF_UTIL.h"
//#include <windows.h>					// Common Windows types
//#include "screenelement.h"				// RPF
//#include "LoggingFunctions.h"			// MASH
//#include "rpf_SKUDIFF.h"                // SKU Header

//#include "Winsatcominterfacei.h"		// Windows Experience Index
//#include "unknwn.h"						// For custom logger
#include "LoggingFunctions.h"			// MASH





namespace SKUDiff
{
	// Wrapper functions to deal with x64 File System redirection for resources.
	// Should not noticably affect tests run on 32 bit.


	typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
	LPFN_ISWOW64PROCESS fnIsWow64Process;
	PVOID OldValue;
	BOOL WOW64State = FALSE;

	// Check if running under a 64 bit OS (assuming test code is 32 bit native only)
	BOOL IsWow64()
	{
		try
		{
			LOGLIBENTER;

			BOOL bIsWow64 = FALSE;

			HMODULE moduleKernel = GetModuleHandle(TEXT("kernel32"));

			if (NULL != moduleKernel)
			{
				fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(moduleKernel,"IsWow64Process");

				if (NULL != fnIsWow64Process)
				{
					if (!fnIsWow64Process(GetCurrentProcess(),&bIsWow64))
					{
						throw(L"fnIsWow64Process failed.");
					}
				}
			}
			LOGLIBRETURN_BOOL(bIsWow64);

		}
		catch (wchar_t *ExceptionString)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, %s",__FUNCTIONW__, ExceptionString);
			LOGLIBRETURN_BOOL(FALSE);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, Unknown Type",__FUNCTIONW__);
			LOGLIBRETURN_BOOL(FALSE);
		}
	}


	//Disable x64 folder redirection.
	__checkReturn HRESULT RedirectionOFF()
	{
		try
		{
			LOGLIBENTER;

			if ((WOW64State = Wow64DisableWow64FsRedirection (&OldValue)) == 0)
			{
				throw (L"Could not disable file system redirection.");	
			}
			LibraryLogInfoW(__FUNCTIONW__, L"WOW Remap - 64 bit OS file system redirection DISABLED for current thread.");
			LOGLIBRETURN_HRESULT(NOERROR);
		}
		catch (wchar_t *ExceptionString)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, %s",__FUNCTIONW__, ExceptionString);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, Unknown Type",__FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
		
	}
	//Restore the previous WOW64 file system redirection value.
	__checkReturn HRESULT RedirectionON()
	{
		try
		{
			LOGLIBENTER;

			if (WOW64State == TRUE)
			{
				if(Wow64RevertWow64FsRedirection(OldValue)==0)
				{
					throw (L"Could not revert file system redirection.");	
				}
				WOW64State = FALSE;
				LibraryLogInfoW(__FUNCTIONW__, L"WOW Remap - 64 bit OS file system redirection restored to prior value for current thread.");
				
			}
			LOGLIBRETURN_HRESULT(NOERROR);
		}
		catch (wchar_t *ExceptionString)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, %s",__FUNCTIONW__, ExceptionString);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, Unknown Type",__FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}

	//reordering of parameters for the function below this one
	__checkReturn HRESULT WOWGetResKeyValue(__in PCWSTR pwszResourceKey, __in unsigned int cchResourceString, __out_ecount(cchResourceString) PWSTR pwszResourceString)
	{
		LOGLIBENTER;

		LOGLIBRETURN_HRESULT(WOWExtractResourceString(pwszResourceKey , pwszResourceString, cchResourceString ));
	}

	__checkReturn HRESULT WOWExtractResourceString(__in PCWSTR pwszResourceKey, __out_ecount(cchResourceString) PWSTR pwszResourceString, __in unsigned int cchResourceString)
	{
		try
		{
			LOGLIBENTER;

			//TODO: Rename X0
			//wchar_t szResourceString[1024];
			HRESULT hrx = E_FAIL;
			wchar_t* pwszModifiedResourceKey;

			pwszModifiedResourceKey = _wcsdup(pwszResourceKey);
			if(pwszModifiedResourceKey == NULL)
			{
				throw(L"_wcsdup returned NULL");
			}


			if(wcsstr(pwszModifiedResourceKey, L"%programfiles%") != NULL) //"ProgramFiles" and "programw6432"
			{
				//if( wcsncpy_s(pwszDestination+SizeA, cchDestination-SizeA, pszWith, wcslen(pszWith)))

				if(0 != (wcsncpy_s(
					wcsstr(pwszModifiedResourceKey, L"%programfiles%"),
					wcsstr(pwszModifiedResourceKey, L"%programfiles%")-pwszModifiedResourceKey,
					L"%programw6432%",
					14
					)))
				{
					throw(L"first wcsncpy failed.");
				}
			}
			if(wcsstr(pwszModifiedResourceKey, L"system32") != NULL) //"system32" and "syswow64"
			{
				//if(FAILED(wcsncpy_s(wcsstr(pwszModifiedResourceKey, L"%system32%"), L"%syswow64%", 10)))

				if(0 != (wcsncpy_s(
					wcsstr(pwszModifiedResourceKey, L"system32"),
					wcsstr(pwszModifiedResourceKey, L"system32")-pwszModifiedResourceKey,
					L"syswow64",
					8
					)))

				{
					throw(L"second wcsncpy failed.");
				}
				
			}
			LibraryLogInfoW(__FUNCTIONW__,	L"[%s][%s]",pwszResourceKey, pwszModifiedResourceKey);

			//if (SUCCEEDED(RedirectionON()))
			{
				hrx = ExtractResourceString(pwszResourceKey, pwszResourceString, cchResourceString);
				if (SUCCEEDED(hrx))
				{
					LibraryLogInfoW(__FUNCTIONW__,	L"WOW Remap -  redir on normal: [%s] = [%s]", pwszResourceKey, pwszResourceString);
					free(pwszModifiedResourceKey);
					LOGLIBRETURN_HRESULT(hrx);
				}

				hrx = ExtractResourceString(pwszModifiedResourceKey, pwszResourceString, cchResourceString);
				if (SUCCEEDED(hrx))
				{
					LibraryLogInfoW(__FUNCTIONW__,	L"WOW Remap -   redir on Remap: [%s] = [%s]", pwszModifiedResourceKey, pwszResourceString);
					free(pwszModifiedResourceKey);
					LOGLIBRETURN_HRESULT(hrx);
				}
			}
			LOG_FAILED_HR(RedirectionOFF());//if (SUCCEEDED())
			{
				hrx = ExtractResourceString(pwszResourceKey, pwszResourceString, cchResourceString);
				if (SUCCEEDED(hrx))
				{
					LibraryLogInfoW(__FUNCTIONW__,	L"WOW Remap - redir off normal: [%s] = [%s]", pwszResourceKey, pwszResourceString);
					if (FAILED(RedirectionON()))
					{
						LogTestInfoW(__FUNCTIONW__,	L"Could not restore redirection state", pwszResourceKey);
					}
					free(pwszModifiedResourceKey);
					LOGLIBRETURN_HRESULT(hrx);
				}


				hrx = ExtractResourceString(pwszModifiedResourceKey, pwszResourceString, cchResourceString);
				if (SUCCEEDED(hrx))
				{
					LibraryLogInfoW(__FUNCTIONW__,	L"WOW Remap -  redir off remap: [%s] = [%s]", pwszModifiedResourceKey, pwszResourceString);
					if (FAILED(RedirectionON()))
					{
						LogTestInfoW(__FUNCTIONW__,	L"Could not restore redirection state", pwszResourceKey);
					}
					free(pwszModifiedResourceKey);
					LOGLIBRETURN_HRESULT(hrx);
				}


				//LogTestInfoW(__FUNCTIONW__,	L"Enabling file system redirection.");
				if (FAILED(RedirectionON()))
				{
					LogTestInfoW(__FUNCTIONW__,	L"Could not restore redirection state", pwszResourceKey);
				}
			}
			free(pwszModifiedResourceKey);
			LogTestInfoW(__FUNCTIONW__,	L"WOW Remap - Could not resolve ResKey: [%s]", pwszResourceKey);
			LOGLIBRETURN_HRESULT(hrx);

		}
		catch (wchar_t *ExceptionString)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, %s",__FUNCTIONW__, ExceptionString);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, Unknown Type",__FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}


	// Generic substring replace... I don't know a library function for it...
	__checkReturn HRESULT wcsreplace(__out_ecount(cchDestination) PWSTR pwszDestination, __in unsigned int cchDestination, __in PCWSTR pszBase,__in PCWSTR  pszReplace, __in PCWSTR pszWith )
	{
		try
		{
			LOGLIBENTER;
			wchar_t* psszInstance;
			if( (psszInstance = wcsstr(pszBase, pszReplace)) != NULL)
			{
				unsigned int SizeA = (unsigned int)(psszInstance - pszBase);
				//unsigned int SizeC = (psszInstance - pszBase);
				if(0 != wcsncpy_s(pwszDestination, cchDestination, pszBase, SizeA))
				{
					throw(L"First wcsncpy_s failed.");
				}
				if(0 != wcsncpy_s(pwszDestination+SizeA, cchDestination-SizeA, pszWith, wcslen(pszWith)))
				{
					throw(L"Second wcsncpy_s failed.");
				}
				if(0 != wcsncpy_s(pwszDestination+SizeA+wcslen(pszWith), (cchDestination-SizeA)-wcslen(pszWith), psszInstance+wcslen(pszReplace), (wcslen(pszBase)-SizeA)-wcslen(pszReplace)))
				{
					throw(L"Third wcsncpy_s failed.");
				}

			}
			else
			{
				if(0 != wcsncpy_s(pwszDestination, cchDestination, pszBase, wcslen(pszBase)))
				{
					throw(L"Fourth wcsncpy_s failed.");
				}

			}
			LOGLIBRETURN_HRESULT(NOERROR);
		}
		catch (wchar_t *ExceptionString)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, %s",__FUNCTIONW__, ExceptionString);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, Unknown Type",__FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}


	HRESULT WOWGlobalizeQueryIdInternal(__out_ecount(cchGlobalizedQuery) PWSTR  GlobalizedQuery, __in unsigned int cchGlobalizedQuery, PCWSTR &pszQueryId, va_list arguments) 
	{
		try
		{
			LOGLIBENTER;

			LibraryLogInfoW(__FUNCTIONW__, L"WOW Remap - Recomposing: %s", pszQueryId);
			wchar_t* pszBracketDigits = L"0123456789";
			wchar_t pszBracketTemplate[5];
			wchar_t pszOldComposedQuery[2048];
			wchar_t pszNewComposedQuery[2048];
			wchar_t* pszResKey;
			wchar_t pszResKeyValue[128];
			if (0 != (wcsncpy_s(pszOldComposedQuery, 2048, pszQueryId, wcslen(pszQueryId))))
			{
				throw (L"First Call to wcsncpy_s() failed!");
			}
			if (0 != (wcsncpy_s(pszNewComposedQuery, 2048, pszQueryId, wcslen(pszQueryId))))
			{
				throw (L"Second Call to wcsncpy_s() failed!");
			}

			for(int i = 0;i<10;i++)
			{
				swprintf_s(pszBracketTemplate,5,L"{%c}",pszBracketDigits[i]);
				//LogTestInfoW(__FUNCTIONW__,	L"Replacing: [%c] in [%s]", pszBracketDigits[i],pszBracketTemplate);
				//pszBracketTemplate[1] = pszBracketDigits[i];
				//LogTestInfoW(__FUNCTIONW__,	L"Checking: [%s] for [%s]", pszOldComposedQuery,pszBracketTemplate);
				if(wcsstr(pszOldComposedQuery, pszBracketTemplate))
				{
					pszResKey = _wcsdup(va_arg( arguments, LPWSTR));
					if (FAILED(WOWExtractResourceString(pszResKey,pszResKeyValue,128)))
					{
						throw (L"Call to WOWExtractResourceString() failed!");
					}

					if (FAILED(wcsreplace(pszNewComposedQuery, 2048, pszOldComposedQuery,pszBracketTemplate,pszResKeyValue)))
					{
						throw (L"Call to wcsreplace() failed!");
					}

					////LogTestInfoW(__FUNCTIONW__,	L"New: [%s]", pszNewComposedQuery);
					if (0 != (wcsncpy_s(pszOldComposedQuery, 2048, pszNewComposedQuery, wcslen(pszNewComposedQuery))))
					{
						throw (L"Third Call to wcsncpy_s() failed!");
					}
				}
				else 
				{
					i=10;
				}
			}
			LibraryLogInfoW(__FUNCTIONW__, L"WOW Remap - Result: %s", pszNewComposedQuery);

			if (0 != (wcsncpy_s(GlobalizedQuery, cchGlobalizedQuery, pszNewComposedQuery, wcslen(pszNewComposedQuery))))
			{
				throw (L"Fourth Call to wcsncpy_s() failed!");
			}
			LOGLIBRETURN_HRESULT(NOERROR);
		}
		catch (wchar_t *ExceptionString)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, %s",__FUNCTIONW__, ExceptionString);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, Unknown Type",__FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}

	//TODO: de-redundant code

	__checkReturn HRESULT WOWGlobalizeQueryId(__out_ecount(cchGlobalizedQuery) PWSTR  GlobalizedQuery, __in unsigned int cchGlobalizedQuery, PCWSTR pszQueryId, ... ) 
	{
		try
		{
			LOGLIBENTER;
			// Initialize variable arguments.
			va_list arguments;
			va_start( arguments, pszQueryId);

			LOGLIBRETURN_HRESULT(WOWGlobalizeQueryIdInternal(GlobalizedQuery, cchGlobalizedQuery, pszQueryId, arguments));
			//
			/*
			//HRESULT hrz;
			LibraryLogInfoW(__FUNCTIONW__, L"WOW Remap - Recomposing: %s", pszQueryId);
			wchar_t* pszBracketDigits = L"0123456789";
			wchar_t pszBracketTemplate[5];
			wchar_t pszOldComposedQuery[2048];
			wchar_t pszNewComposedQuery[2048];
			wchar_t* pszResKey;
			wchar_t pszResKeyValue[128];
			if (0 != (wcsncpy_s(pszOldComposedQuery, 2048, pszQueryId, wcslen(pszQueryId))))
			{
			throw (L"First Call to wcsncpy_s() failed!");
			}
			if (0 != (wcsncpy_s(pszNewComposedQuery, 2048, pszQueryId, wcslen(pszQueryId))))
			{
			throw (L"Second Call to wcsncpy_s() failed!");
			}

			for(int i = 0;i<10;i++)
			{
			swprintf_s(pszBracketTemplate,5,L"{%c}",pszBracketDigits[i]);
			//LogTestInfoW(__FUNCTIONW__,	L"Replacing: [%c] in [%s]", pszBracketDigits[i],pszBracketTemplate);
			//pszBracketTemplate[1] = pszBracketDigits[i];
			//LogTestInfoW(__FUNCTIONW__,	L"Checking: [%s] for [%s]", pszOldComposedQuery,pszBracketTemplate);
			if(wcsstr(pszOldComposedQuery, pszBracketTemplate))
			{
			pszResKey = _wcsdup(va_arg( arguments, LPWSTR));
			if (FAILED(WOWExtractResourceString(pszResKey,pszResKeyValue,128)))
			{
			throw (L"Call to WOWExtractResourceString() failed!");
			}

			if (FAILED(wcsreplace(pszNewComposedQuery, 2048, pszOldComposedQuery,pszBracketTemplate,pszResKeyValue)))
			{
			throw (L"Call to wcsreplace() failed!");
			}

			////LogTestInfoW(__FUNCTIONW__,	L"New: [%s]", pszNewComposedQuery);
			if (0 != (wcsncpy_s(pszOldComposedQuery, 2048, pszNewComposedQuery, wcslen(pszNewComposedQuery))))
			{
			throw (L"Third Call to wcsncpy_s() failed!");
			}
			}
			else 
			{
			i=10;
			}
			}
			LibraryLogInfoW(__FUNCTIONW__, L"WOW Remap - Result: %s", pszNewComposedQuery);
			wcsncpy_s(GlobalizedQuery, cchGlobalizedQuery, pszNewComposedQuery, wcslen(pszNewComposedQuery)); //TODO: Check return
			LOGLIBRETURN_HRESULT(NOERROR);
			*/
		}
		catch (wchar_t *ExceptionString)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, %s",__FUNCTIONW__, ExceptionString);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, Unknown Type",__FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}

	__checkReturn HRESULT WOWFromPartialQueryId(__in PCWSTR pszQueryId, ...)
	{
		try
		{
			LOGLIBENTER;
			// Initialize variable arguments.
			va_list arguments;
			va_start( arguments, pszQueryId);
			HRESULT hr;
			wchar_t GlobalizedQuery[2048];
			if (SUCCEEDED(LOG_FAILED_HR(hr = WOWGlobalizeQueryIdInternal(GlobalizedQuery, 2048, pszQueryId, arguments))))//
			{
				LogTestInfoW(__FUNCTIONW__,	L"WOW Remap - Querying: [%s]", GlobalizedQuery);
				hr = FromPartialQueryId(GlobalizedQuery);
				if (FAILED(hr))
				{
					wchar_t pszFileName[MAX_PATH];
					SYSTEMTIME Nowish;
					GetSystemTime(&Nowish);
					StringCchPrintfW(pszFileName,MAX_PATH,L"%04d%02d%02d_%02d%02d%02d_%03d.jpg",Nowish.wYear,Nowish.wMonth,Nowish.wDay,Nowish.wHour,Nowish.wMinute,Nowish.wSecond,Nowish.wMilliseconds );
					DumpScreen(pszFileName);
					LogTestInfoW(__FUNCTIONW__,	L"WOW Remap - Query FAILED, screen image saved as: [%s]", pszFileName);

				}
			}
			LOGLIBRETURN_HRESULT(hr);
		}
		catch (wchar_t *ExceptionString)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, %s",__FUNCTIONW__, ExceptionString);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, Unknown Type",__FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}

	bool WOWIsAvailable(__in unsigned int nTimeOut, __in PCWSTR pszQueryId, ...)
	{
		try
		{
			LOGLIBENTER;

			// Initialize variable arguments.
			va_list arguments;
			va_start( arguments, pszQueryId);
			wchar_t GlobalizedQuery[2048];
			bool fResult;

			// Set timeout zero
			int nOriginalSearchTimeOut = SetSearchTimeOut(nTimeOut);

			// Set logging flag, so no dumpscreen is performed and failure is recorded as info
			int nOriginalLoggingFlag = SetLoggingFlag(0);

			// No Dump Screen
			int nNewLoggingFlag = nOriginalLoggingFlag & ~FL_DUMP_SCREEN;

			// Log failure as info
			nNewLoggingFlag |= FL_LOG_FAILURE_AS_INFO;

			// Set new logging flag
			SetLoggingFlag(nNewLoggingFlag);

			if(SUCCEEDED(WOWGlobalizeQueryIdInternal(GlobalizedQuery, 2048, pszQueryId, arguments))) //
			{
				fResult = (S_OK == FromPartialQueryId(GlobalizedQuery));
			}
			else
			{
				fResult = false;
			}

			//bool fResult = (S_OK == WOWFromPartialQueryId(pszQueryId, arguments));

			// Restore timeout
			SetSearchTimeOut(nOriginalSearchTimeOut);

			// Restore logging flag
			SetLoggingFlag(nOriginalLoggingFlag);

			LOGLIBRETURN_bool(fResult);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"%s returning bool false due to an exception.", __FUNCTIONW__);
			LOGLIBRETURN_bool(false);
		}
	}

	ScreenElement* WOWScreenElementFromPartialQueryId(__in PCWSTR pszQueryId, ...)
	{
		try
		{
			LOGLIBENTER;

			IScreenElement* pScreenElement;
			// Initialize variable arguments.
			va_list arguments;
			va_start( arguments, pszQueryId);
			wchar_t GlobalizedQuery[2048];
			if (SUCCEEDED(WOWGlobalizeQueryIdInternal(GlobalizedQuery, 2048, pszQueryId, arguments)))//
			{
				if (S_OK == FindScreenElementEx(NULL, &pScreenElement, GlobalizedQuery, arguments))
				{
					//todo: return object type?
					LOGLIBRETURN(new ScreenElement(pScreenElement));
				}
			}
			LOGLIBRETURN(NULL);
		}
		catch (wchar_t *ExceptionString)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, %s",__FUNCTIONW__, ExceptionString);
			LOGLIBRETURN(NULL);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"EXCEPTION in %s, Unknown Type",__FUNCTIONW__);
			LOGLIBRETURN(NULL);
		}

	}
}