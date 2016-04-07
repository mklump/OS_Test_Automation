//////////////////////////////////////////////////////////////
//                 
//  This file defines many functions of various types,
//  wrapping RPF, MASH, and native API functionality.
//  For use in testing SKU Differentiation of Microsoft Windows
//	
//  Copyright (C) Microsoft Corporation, 2008. For internal use only.
//
//////////////////////////////////////////////////////////////

// a-jomul: Created in late 2007 to early 2008

//#include <windows.h>            //Common Windows types
//#include "screenelement.h"             //RPF
//#include "LoggingFunctions.h"			// MASH
//#include "Winsatcominterfacei.h" // Windows Experience Index

//#include "unknwn.h" // For custom logger
//#include <AutomationObjectsInit.h>    
//#include <shellapi.h>
//#include <oleacc.h>             //XACC
//#include <ole2.h>
#define CLICKABLE_POINT         -1,-1
#define RPF_WINDOWLESS          L"", L"", 0

#define IID_IUnknown __uuidof(IUnknown)
#define LIBLOGDETAIL(logstring) if(LibraryLogDetail == TRUE) LogTestInfoW(__FUNCTIONW__, logstring);

//#define LOGLIBENTER if (LibraryDepth >= 0 && LibraryDepth < 127) {LibraryLogInfoW(__FUNCTIONW__, L"Entering Library Function: %s, depth %d",__FUNCTIONW__, ++LibraryDepth); LibraryStack[LibraryDepth] = _wcsdup(__FUNCTIONW__);}
//#define LOGLIBEXIT if (LibraryDepth > 0 && LibraryDepth < 127) {free(LibraryStack[LibraryDepth]);LibraryLogInfoW(__FUNCTIONW__, L"Exiting Library Function: %s, depth %d",__FUNCTIONW__, LibraryDepth--);}

#define LOGLIBENTER ++LibraryDepth; LibraryLogInfoW(__FUNCTIONW__, L"<<< Entering Library Function: %s. <<<",__FUNCTIONW__);
#define LOGLIBEXIT LibraryLogInfoW(__FUNCTIONW__, L">>> Exiting Library Function: %s.>>>",__FUNCTIONW__);LibraryDepth--;
#define LOGLIBRETURN(retval) LibraryLogInfoW(__FUNCTIONW__, L">>> Library Function: %s returning %s.>>>",__FUNCTIONW__, L#retval , LibraryDepth);LibraryDepth--;return(retval);

#define LOGLIBRETURN_void()          LibraryLogInfoW(__FUNCTIONW__, L">>> Library Function: %s returning void. >>>",__FUNCTIONW__);LibraryDepth--;
#define LOGLIBRETURN_bool(retval)    LibraryLogInfoW(__FUNCTIONW__, L">>> Library Function: %s returning a bool '%s' with a value of %s. >>>",__FUNCTIONW__,L#retval ,(retval) ? L"true": L"false");LibraryDepth--;return(retval);
#define LOGLIBRETURN_BOOL(retval)    LibraryLogInfoW(__FUNCTIONW__, L">>> Library Function: %s returning a BOOL '%s' with a value of %s. >>>",__FUNCTIONW__,L#retval ,(retval) ? L"TRUE": L"FALSE");LibraryDepth--;return(retval);
#define LOGLIBRETURN_HRESULT(retval) LibraryLogInfoW(__FUNCTIONW__, L">>> Library Function: %s returning a HRESULT '%s' that indicates %s. >>>",__FUNCTIONW__ , L#retval,SUCCEEDED(retval) ? L"Success": L"Failure");LibraryDepth--;return(retval);
#define LOGLIBRETURN_int(retval)     LibraryLogInfoW(__FUNCTIONW__, L">>> Library Function: %s returning an int '%s' with a value of %d. >>>",__FUNCTIONW__, L#retval ,(retval));LibraryDepth--;return(retval);

//#define LOGLIBENTER ++LibraryDepth;
//#define LOGLIBEXIT LibraryDepth--;

extern int LibraryDepth;

//extern wchar_t* LibraryStack[128];
//static int LibraryLogIndent;
//static BOOL LibraryLogDetail;
	

#define CPL_IS_INVALID 0
#define CPL_IS_CLASSIC 1
#define CPL_IS_HOME 2
#define LOGRESKEY(reskey) (LogResKeyValue(L#reskey,reskey))
#define RESKEYSEQUAL(reskey1,reskey2) (AreResKeyValuesEqual(L#reskey1,reskey1,L#reskey2,reskey2))

namespace SKUDiff
{
	//Should be called by InitTest() and UnInitTest()
	STDAPI SKUInitTest();
	STDAPI SKUUnInitTest();

	//Get the Username(with domain) and Password for a WTT LLU account
	__checkReturn HRESULT __cdecl GetLLU (__in LPCWSTR lpwszLLU, __out_ecount(cchUsername) LPWSTR Username, __inout unsigned int cchUsername, __out_ecount(cchPassword) LPWSTR Password, __inout unsigned int cchPassword);
	//Informational Logging
	void LogSKU(); // Writes the current SKU name to the log
	void Assessment(); // Writes the Windows Experiance Index scores to the log

	//Common UI actions
	__checkReturn HRESULT OpenStartMenu();
	__checkReturn HRESULT OpenAllPrograms();
	__checkReturn HRESULT OpenWelcomeCenter();
	__checkReturn HRESULT OpenSpecificControlPanel(__in PCWSTR pszQueryId, ...);

	__checkReturn HRESULT OpenControlPanelClassicView();
	__checkReturn HRESULT OpenControlPanelHomeView();
	__checkReturn HRESULT OpenSpecificClassicControlPanel(__in wchar_t* Item);
	__checkReturn HRESULT OpenSpecificHomeControlPanel(__in wchar_t* Section,__in wchar_t* Link);
	
	HRESULT CloseControlPanel();
	//HRESULT LeftClickUntilGone(__in wchar_t* gqid);
	HRESULT LeftClickUntilGone(__in PCWSTR pszQueryId, ...);
	HRESULT MultiLeftClickUntilGone(__in unsigned int Count, ...);
	//64 bit aware RPF wrapper functions
	__checkReturn HRESULT WOWFromPartialQueryId(__in PCWSTR pszQueryId, ... );
	ScreenElement* WOWScreenElementFromPartialQueryId(__in PCWSTR pszQueryId, ... );
	bool WOWIsAvailable(__in unsigned int nTimeOut, __in PCWSTR pszQueryId, ...);
	__checkReturn HRESULT WOWGlobalizeQueryId(__out_ecount(cchGlobalizedQuery) PWSTR  GlobalizedQuery, __in unsigned int cchGlobalizedQuery, PCWSTR pszQueryId, ... ); 
	HRESULT WOWGlobalizeQueryIdInternal(__out_ecount(cchGlobalizedQuery) PWSTR  GlobalizedQuery, __in unsigned int cchGlobalizedQuery, PCWSTR &pszQueryId, va_list arguments);
	//HRESULT WOWGlobalizeQueryId(__out_ecount(cchGlobalizedQuery) PWSTR  GlobalizedQuery, __in unsigned int cchGlobalizedQuery, PCWSTR pszQueryId, ... );
	
	//Questions your test code may have about the system
	//int GetControlPanelMode();
	__checkReturn float Get2DScore();

	//Wait about 10 seconds, plan to add an optional configurable delay.
	VOID Snooze(unsigned int Seconds = 10);
	
	//Should not be called directly
	void CustomLoggingHandler(BSTR* bstrLogString, BOOL *bLogDefault, BOOL *bDumpScreen); 
	//Don't use these, use the Macros defined above.
	BOOL AreResKeyValuesEqual(__in const wchar_t* szResourceKeyName1,__in const wchar_t* szResourceKey1,__in const wchar_t* szResourceKeyName2,__in const wchar_t* szResourceKey2);
	HRESULT LogResKeyValue(__in const wchar_t* szResourceKeyName,__in const wchar_t* szResourceKey);
	
	//You shouldn't need to call these directly
	//HRESULT SetControlPanelHomeView();
	//HRESULT SetControlPanelClassicView();
	//HRESULT OpenControlPanel();
	

	//64 bit control functions used by the 64 adapted functions, shouldn't be called directly
	//void RedirectionOFF();
	//void RedirectionON();
	//HRESULT wcsreplace(__out_ecount(cchDestination) PWSTR pwszDestination, __in unsigned int cchDestination, __in PCWSTR pszBase,__in PCWSTR  pszReplace, __in PCWSTR pszWith );
	//BOOL IsWow64();

	__callback int ExceptionFilter(unsigned int code, struct _EXCEPTION_POINTERS *ep);

	__checkReturn HRESULT ResourceForDriveFromPath(__in PCWSTR pwszPath, __out_ecount(cchResource) PWSTR pwszResource, __in unsigned int cchResource);

	STDAPI LibraryLogInfoW(__in LPWSTR pwszFuncName, __in LPWSTR pwszTestInfo, ...);
	
	//Deprecated:

	__checkReturn HRESULT WOWGetResKeyValue(__in PCWSTR pwszResourceKey, __in unsigned int cchResourceString, __out_ecount(cchResourceString) PWSTR pwszResourceString);
	__checkReturn HRESULT WOWExtractResourceString(__in PCWSTR pwszResourceKey, __out_ecount(cchResourceString) PWSTR pwszResourceString, __in unsigned int cchResourceString);
	__checkReturn HRESULT wcsreplace(__out_ecount(cchDestination) PWSTR pwszDestination, __in unsigned int cchDestination, __in PCWSTR pszBase,__in PCWSTR  pszReplace, __in PCWSTR pszWith );
	//HRESULT WOWGetResKeyValue(__in PWSTR &pwszResourceKey, __in unsigned int cchResourceString, __out_ecount(cchResourceString) PWSTR pwszResourceString);
	//HRESULT WOWExtractResourceString(__in PWSTR &pwszResourceKey, __out_ecount(cchResourceString) PWSTR &pwszResourceString, __in unsigned int cchResourceString);
	
	
	//HRESULT WOWGetResKeyValue(__in PCWSTR &pwszResourceKey, __in unsigned int cchResourceString, __out_ecount(cchResourceString) PWSTR &pwszResourceString);
	//HRESULT WOWExtractResourceString(__in PCWSTR &pwszResourceKey, __out_ecount(cchResourceString) PWSTR &pwszResourceString, __in unsigned int cchResourceString);
	
	//HRESULT WOWGetResKeyValue(__in PCWSTR pwszResourceKey, __in unsigned int cchResourceString, __out_ecount(cchResourceString) PWSTR pwszResourceString);
	//HRESULT WOWExtractResourceString(__in PCWSTR pwszResourceKey, __out_ecount(cchResourceString) PWSTR pwszResourceString, __in unsigned int cchResourceString);
	
	//STDAPI ResourceForDriveFromPath(__in const PWSTR pwszPath, __out wchar_t* pwszResource, __in unsigned int ccResource);
	//HRESULT ResourceFromMUM(__in const PWSTR  Component, __out_ecount(cchResource) PWSTR  Resource, __in unsigned int cchResource);
	//HRESULT wcsreplace(__out_ecount(cchResource) PWSTR pwszDestination, __in unsigned int cchDestination, __in PCWSTR pszBase,__in PCWSTR  pszReplace, __in PCWSTR pszWith );
	//HRESULT wcsreplace(__in const wchar_t* pszBase,__in const wchar_t*  pszReplace,__in const wchar_t*  pszWith,__in unsigned int MaxLen,__out PWSTR pszDestination);
	//HRESULT wcsreplace(__in const wchar_t* pszBase,__in const wchar_t*  pszReplace,__in const wchar_t*  pszWith,__in int MaxLen,__out PWSTR pszDestination);
	//HRESULT WOWFromPartialQueryId(const wchar_t* pszQueryId, ... );
	//ScreenElement* WOWScreenElementFromPartialQueryId(const wchar_t* pszQueryId, ... );
	__checkReturn HRESULT ResourceFromMUM(__in PCWSTR Component, __out_ecount(cchResource) PWSTR  Resource, __in unsigned int cchResource);
	__checkReturn HRESULT ResourceFromMSC(__in PCWSTR Filename, __out_ecount(cchResource) PWSTR  Resource, __in unsigned int cchResource);
	
	__checkReturn HRESULT GetLocaleString(__out_ecount(6) PWSTR Language);
	//HRESULT GetWindowsServicingPackagesPath(__out_ecount(MAX_PATH) PWSTR Path);
	//HRESULT GetOCfilename(__in PCWSTR  Component, __out_ecount(cchFilename) PWSTR pszFilename, __in unsigned int cchFilename = MAX_PATH);
	//HRESULT BufferFile(__in PCWSTR  Filename, __deref_inout PWSTR &wBuffer);
	
}
