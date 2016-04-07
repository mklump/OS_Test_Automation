//////////////////////////////////////////////////////////////
//                 
//  This file defines many functions of various types,
//  wrapping RPF, MASH, and native API functionality.
//  For use in testing SKU Differentiation of Microsoft Windows
//	
//  Copyright Microsoft Corporation, 2008. For internal use.
//
//////////////////////////////////////////////////////////////

// a-jomul: Created in late 2007
//          jan 2008, broke into seperate .h and .cpp
//			feb 2008, cleanup, comments, exception catching
#include <windows.h>					// Common Windows types
#include "setupapi.h"				// RPF
#include "screenelement.h"				// RPF
#include "SKUDIFF_UTIL.h"
#include "Winsatcominterfacei.h" // Windows Experience Index
#include "LoggingFunctions.h"			// MASH

int LibraryDepth;
namespace SKUDiff
{

	// Used to preserve RPF timeout from before the test began... probably not needed.
	int GlobalTimeout;



#pragma region WTT LLU Credentials
	/////////////////////////////////////////////////////////
	// This section is used to get the username, domain, and password of a given WTT Logical Logical User (LLU)
	// Mostly a cut-n-paste job from an example.
	///////////////////////////////////////////////////////////
	typedef LPWSTR ( *PROCQUERYLOGICALUSER ) ( LPCWSTR pcszLLUName, LPWSTR *ppszPassword, LPWSTR *ppszErrorXML );
	typedef VOID ( *PROCWTTFREEMEMORY ) ( LPVOID pMemory );


	__checkReturn HRESULT __cdecl GetLLU (__in LPCWSTR lpwszLLU, __out_ecount(cchUsername) LPWSTR Username, __inout unsigned int cchUsername, __out_ecount(cchPassword) LPWSTR Password, __inout unsigned int cchPassword)
	{
		try
		{
			LOGLIBENTER;
			DWORD dwRet = ERROR_SUCCESS;

			CoInitialize ( NULL );

			HMODULE hModule = NULL;
			PROCQUERYLOGICALUSER ProcQueryLogicalUser = NULL;
			PROCWTTFREEMEMORY ProcWTTFreeMemory = NULL;

			if ( ( hModule = LoadLibraryW ( L"wttsdk.dll") ) == NULL )
			{
				dwRet = GetLastError ();
				LogTestInfoW(__FUNCTIONW__, L"Failed to LoadLibrary (err=%d)\n", dwRet );
				goto ret;
			}

			//printf ( "Loaded library 0x%08x\n", hModule );

			if ( ( ProcQueryLogicalUser = ( PROCQUERYLOGICALUSER ) GetProcAddress ( hModule, ( LPCSTR ) "QueryLogicalUser" ) ) == NULL )
			{
				dwRet = GetLastError ();
				LogTestInfoW(__FUNCTIONW__,L"Failed to GetProcAddress QueryLogicalUser (err=%d)\n", dwRet );
				goto ret;
			}

			if ( ( ProcWTTFreeMemory = ( PROCWTTFREEMEMORY ) GetProcAddress ( hModule, ( LPCSTR ) "WTTFreeMemory" ) ) == NULL )
			{
				dwRet = GetLastError ();
				LogTestInfoW(__FUNCTIONW__,L"Failed to GetProcAddress WTTFreeMemory (err=%d)\n", dwRet );
				goto ret;
			}

			LPWSTR lpwszUser = NULL;
			LPWSTR lpwszPassword = NULL;
			LPWSTR lpwszError = NULL;

			if ( ( lpwszUser = ProcQueryLogicalUser ( lpwszLLU, &lpwszPassword, &lpwszError ) ) == NULL )
			{
				dwRet = ERROR_INVALID_PARAMETER;
				LogTestInfoW(__FUNCTIONW__, L"Failed to QueryLogicalUser\n" );
				if ( lpwszError != NULL )
					LogTestInfoW(__FUNCTIONW__,L"Error returned: %ls\n", lpwszError );
				goto ret;
			}

			LogTestInfoW(__FUNCTIONW__,L"LLU user is %ls\n", lpwszUser );
			wcscpy_s(Username, cchUsername,lpwszUser);

			if ( lpwszPassword != NULL )
			{
				LogTestInfoW(__FUNCTIONW__, L"First character of LLU password is '%c'\n", lpwszPassword[0] );
				wcscpy_s(Password, cchPassword,lpwszPassword);
			}	
			//LogTestInfoW(__FUNCTIONW__, L"LLU password is %ls\n", lpwszPassword );
			else
			{
				LogTestInfoW(__FUNCTIONW__,L"LLU password is NULL\n" );
			}
ret:
			if ( ( lpwszUser != NULL ) && ( ProcWTTFreeMemory != NULL ) )
			{
				ProcWTTFreeMemory ( lpwszUser );
				lpwszUser = NULL;
			}

			if ( ( lpwszPassword != NULL ) && ( ProcWTTFreeMemory != NULL ) )
			{
				ProcWTTFreeMemory ( lpwszPassword );
				lpwszPassword = NULL;
			}

			if ( ( lpwszError != NULL ) && ( ProcWTTFreeMemory != NULL ) )
			{
				ProcWTTFreeMemory ( lpwszError );
				lpwszError = NULL;
			}

			if ( hModule != NULL )
			{
				FreeLibrary ( hModule );
			}


			CoUninitialize ( );

			LOGLIBEXIT;
			return dwRet;
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"%s returning BOOL FALSE due to an exception.", __FUNCTIONW__);
			LOGLIBRETURN_HRESULT(E_FAIL);
		}
	}

#pragma endregion WTT LLU Credentials
#pragma region IMonitoringWindowsCallback implementation
	////////////////////////////////////////////////////////////////////
	// Local implementation of RPF's WindowMonitor, since RPF's dosn't build due to a missing definition of IUnknown
	// Basically a cut-n-paste from RPF, with a defined IUnknown
	///////////////////////////////////////////////////////////////////	

	// Implementing IMonitoringWindowsCallback for thread monitoring info
	class SKUMonitorWindowBase : public IMonitoringWindowsCallback
	{
		ULONG m_dwRef;
		wchar_t* m_pszWindowName;
		wchar_t* m_pszWindowClass;
		WindowMonitoringHandler m_windowMonitoringHanler;

	public:

		// Constructor
		SKUMonitorWindowBase(__in wchar_t* pszWindowClass, __in wchar_t* pszWindowName, WindowMonitoringHandler windowMonitoringHanler)
		{
			m_pszWindowClass = pszWindowClass;
			m_pszWindowName = pszWindowName;
			m_windowMonitoringHanler = windowMonitoringHanler;
		}

		// IMonitoringWindowsCallback implementation
		__callback virtual HRESULT __stdcall MonitoringWindowsCallBack(BSTR bstrWindowClass, BSTR bstrWindowName)
		{
			m_windowMonitoringHanler(bstrWindowClass, bstrWindowName);
			return S_OK;
		}

		virtual HRESULT __stdcall GetMonitoringInfo(BSTR* pbstrWindowClass, int cchClass, BSTR* pbstrWindowName, int cchWindowName)
		{
			if (m_pszWindowClass)
			{
				StringCchCopyW(*pbstrWindowClass, cchClass, m_pszWindowClass);
			}
			else if (pbstrWindowClass != NULL && *pbstrWindowClass != NULL)
			{
				**pbstrWindowClass = L'\0';
			}

			if (m_pszWindowName)
			{
				return StringCchCopyW(*pbstrWindowName, cchWindowName, m_pszWindowName);
			}
			else if (pbstrWindowName != NULL && *pbstrWindowName != NULL)
			{
				**pbstrWindowName = L'\0';
			}

			return S_OK;
		}

		// IUnknown implementation
		ULONG __stdcall AddRef() 
		{ 
			return ++m_dwRef; 
		}

		ULONG __stdcall Release() 
		{ 
			if (--m_dwRef == 0) 
			{
				delete this; 
				return 0;
			}
			return m_dwRef;
		}

		HRESULT __stdcall QueryInterface(REFIID iid, void FAR* FAR* ppvObj)
		{
			if (iid == __uuidof(IUnknown) || iid == __uuidof(IMonitoringWindowsCallback))
			{
				*ppvObj = this;
				AddRef();
				return NOERROR;
			}
			*ppvObj = NULL;
			return E_NOINTERFACE;
		}
	};
	// Window monitor callback function
	// TODO: catch Stater app limit window
	__callback void WindowPopHandler(BSTR lpstrWindowClass, BSTR bstrlpstrWindowName)
	{
		try
		{
			LogTestInfoW(__FUNCTIONW__, L"POP: [%s] appeared.", bstrlpstrWindowName);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"%s exiting due to an exception, probably passed a bad string.", __FUNCTIONW__);
		}
	}

#pragma endregion IMonitoringWindowsCallback implementation

#pragma region ILoggerCallback implementation
	////////////////////////////////////////////////////////////////////
	// Local implementation of RPF's ILoggerCallback, since RPF's dosn't build due to a missing definition of IUnknown
	// Basically a cut-n-paste from RPF, with a defined IUnknown
	///////////////////////////////////////////////////////////////////	
	class SKULoggerBase : public ILoggerCallback
	{
		ULONG m_dwRef;
		LoggingHandler m_loggingHandler;

	public:

		// Constructor
		SKULoggerBase(LoggingHandler loggingHandler)
		{
			m_loggingHandler = loggingHandler;
		}

		// ILoggerCallback implementation
		__callback virtual HRESULT __stdcall LoggerCallback(BSTR* pbstrLogString, BOOL *pfLogDefault, BOOL *pfDumpScreen)
		{
			m_loggingHandler(pbstrLogString, pfLogDefault, pfDumpScreen);
			return S_OK;
		}

		// IUnknown implementation
		ULONG __stdcall AddRef() 
		{ 
			return ++m_dwRef; 
		}

		ULONG __stdcall Release() 
		{ 
			if (--m_dwRef == 0) 
			{
				delete this; 
				return 0;
			}
			return m_dwRef;
		}

		HRESULT __stdcall QueryInterface(REFIID iid, void FAR* FAR* ppvObj)
		{
			if (iid == __uuidof(IUnknown) || iid == __uuidof(ILoggerCallback))
			{
				*ppvObj = this;
				AddRef();
				return NOERROR;
			}
			*ppvObj = NULL;
			return E_NOINTERFACE;
		}
	};


	// Callback function that re-defines the default logger behavior
	__callback void CustomLoggingHandler(BSTR* bstrLogString, BOOL *bLogDefault, BOOL *bDumpScreen) 
	{ 
		try
		{
			//uncomment the following line to only log RPF failures, not everything.
			//if(wcsstr(*bstrLogString, L"[FAILED]"))
			{ 
				LogTestInfoW(__FUNCTIONW__, L"RPF: %s", *bstrLogString);
			} 
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"%s exiting due to an exception, probably passed a bad string.", __FUNCTIONW__);			
		}
	} 

#pragma endregion ILoggerCallback implementation


#pragma region MASH InitTest/UnInitTest common functionality.
	__checkReturn STDAPI SKUInitTest()
	{
		try
		{
			LibraryDepth = 0;
			LOGLIBENTER;
			LogSKU();
			HRESULT hr;

			hr = InitPlayBackForTargetWindow(RPF_WINDOWLESS);
			if (FAILED(hr))
			{
				throw (L"InitPlayBackForTargetWindow failed.");
			}
			
			EnableInfoWindow(TRUE);
			GlobalTimeout = SetSearchTimeOut(1000); // Lower the default search timeout to 10 seconds
			
			const wchar_t* resKeyMicroSoftWindows = L"RKB1[WerFault];MicroSoft Windows;Win32String;.\\wer.dll;241";
			const wchar_t* resKeyCloSetheBrogram = L"RKB1[WerFault];CloSe the Brogram;Win32String;.\\wer.dll;240";

			//close previous crash dialog, if any.
			ScreenElement* pScreenElement;
			if(NULL != (pScreenElement = ScreenElement::FromPartialQueryId(L";Name => '{0}' && ClassName => '#32770';[VisibleOnly]Name = '{0}' && Role = 'pane';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyMicroSoftWindows, resKeyCloSetheBrogram)))
			{	
				pScreenElement->LeftButtonClick(-1,-1);
				delete pScreenElement;
			}
			SetSearchTimeOut(10000);
			
			if (FAILED(SetCustomLogger(new SKULoggerBase(CustomLoggingHandler))))
			{
				LogTestInfoW(__FUNCTIONW__, L"Failed to attach to RPF log, not aborting.");
			}
			SetLoggingFlag(FL_LOG_SEARCH_AND_PRIMITIVES);
			//Code to enable when monitoring for a window.
			//AddMonitoringInfo(new SKUMonitorWindowBase(L"", L"", WindowPopHandler));
			//StartMonitoringWindows(100);

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

	STDAPI SKUUnInitTest()
	{
		//try
		try
		{
			LOGLIBENTER;
			//Code to enable when monitoring for a window.
			//StopMonitoringWindows();
			//SetSearchTimeOut(GlobalTimeout); //Haste
			SetCustomLogger(NULL); 
			FinishPlayBack();
			LOGLIBEXIT;
			return NOERROR;
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

#pragma endregion MASH InitTest/UnInitTest common functionality.


	// Compare two resource keys, and compare/log the results.
	BOOL AreResKeyValuesEqual(__in const wchar_t* szResourceKeyName1,__in const wchar_t* szResourceKey1,__in const wchar_t* szResourceKeyName2,__in const wchar_t* szResourceKey2)
	{
		try
		{
			LOGLIBENTER;
			wchar_t szResourceString1[1024];
			wchar_t szResourceString2[1024];
			HRESULT hrx;

			hrx = ExtractResourceString(szResourceKey1, szResourceString1, 1024);
			if (FAILED(hrx))
			{
				throw (L"Could not resolve first resKey");
			}

			hrx = ExtractResourceString(szResourceKey2, szResourceString2, 1024);
			if (FAILED(hrx))
			{
				throw (L"Could not resolve second resKey");
			}

			if(wcscmp(szResourceString1,szResourceString2) != 0)
			{
				LogTestInfoW(__FUNCTIONW__,	L"[%s] [%s] does not match [%s] [%s]",	szResourceKeyName1, szResourceString1,	szResourceKeyName2, szResourceString2 );
				LOGLIBRETURN_BOOL(FALSE);
			}
			LOGLIBRETURN_BOOL(TRUE);
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




	// Gets the Windows Experiance Index 2D graphics score, DWM requires a minimal score.
	__checkReturn float Get2DScore()
	{
		try
		{
			LOGLIBENTER;
			HRESULT hr = S_OK;
			IQueryRecentWinSATAssessment* pAssessment;
			IProvideWinSATResultsInfo* pResults = NULL;
			IProvideWinSATAssessmentInfo* pSubcomponent = NULL;

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

					hr = pResults->GetAssessmentInfo(WINSAT_ASSESSMENT_GRAPHICS, &pSubcomponent);
					if (SUCCEEDED(hr))
					{
						pSubcomponent->get_Score(&score);
						pSubcomponent->Release();
					}
					pResults->Release();
					pResults = NULL;
				}
				pAssessment->Release();
				pAssessment = NULL;
			}
			LOGLIBRETURN(score);
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"%s returning Zero due to an exception.", __FUNCTIONW__);
			LOGLIBEXIT;
			return 0;
		}
	}






	////////////////////////////////////////////////////////
	// 'Sleep()' doesn't force a real wait, this will, for the given number of seconds, up to 60.
	////////////////////////////////////////////////////////
	VOID Snooze(unsigned int Seconds)
	{
		try
		{
			LOGLIBENTER;
			HANDLE hTimer = NULL;
			LARGE_INTEGER liDueTime;

			liDueTime.QuadPart=(-10000000LL) * Seconds;
			if (Seconds > 60)
			{
				LogTestInfoW(__FUNCTIONW__, L"Asked to Snooze for more than 60 seconds(%d), limiting to 60 seconds.",Seconds);
			}
			// Create a waitable timer.
			hTimer = CreateWaitableTimer(NULL, TRUE, "Local\\Snooze");
			if (NULL != hTimer)
			{

				// Set a timer to wait for the number of seconds.
				if (SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, 0))
				{

					// Wait for the timer, with a time limit of one minute.
					WaitForSingleObject(hTimer, 60000); //INFINITE
				}
			}
			LOGLIBEXIT;
		}
		catch (...)
		{
			LogTestInfoW(__FUNCTIONW__, L"%s exiting due to an exception.", __FUNCTIONW__);
			LOGLIBEXIT;
		}
	}

	//////////////////////////////////////////////////////////
	// Used to catch exceptions in library code
	//////////////////////////////////////////////////////////
	__callback int ExceptionFilter(unsigned int code, struct _EXCEPTION_POINTERS *ep) 
	{ 
		LogTestInfoW(__FUNCTIONW__, L"old C '__try' '__except' used, suggest using C++ 'try' 'catch' instead.");

		switch (code)
		{
		case EXCEPTION_ACCESS_VIOLATION:
			LogTestInfoW(__FUNCTIONW__, L"Exception: Access Violation (%x)",code);
			return EXCEPTION_EXECUTE_HANDLER;
			break;
		default:
			LogTestInfoW(__FUNCTIONW__, L"Exception: Unknown Description (%x)",code);
			return EXCEPTION_EXECUTE_HANDLER;
			break;
		}
	} 




}
