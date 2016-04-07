//////////////////////////////////////////////////////////////
//                 
//  This file contains RPF Resources and QueryIDs of Windows edition names, AKA 'SKU' names.
//  For use in testing SKU Differentiation of Microsoft Windows
//	
//  Copyright (C) Microsoft Corporation, 2008. For internal use only.
//
//////////////////////////////////////////////////////////////

// a-jomul: Cleaned up an existing file in late 2007, replaced long redundant macros with parameterized versions.


//Useful defines should go here
#define WINDOWS_VISTA_VERSION 6

const __declspec(selectany) wchar_t*	resKeyBrandingWindows = L"RKB1[];Windows;Win32String;%windir%\\branding\\basebrd\\basebrd.dll;10";
const __declspec(selectany) wchar_t*	resKeyBrandingWindowsVistaTM = L"RKB1[];Windows Vista™;Win32String;%windir%\\branding\\basebrd\\basebrd.dll;11";
const __declspec(selectany) wchar_t*	resKeyBrandingWindowsVistaTMSKUName = L"RKB1[];Windows Vista™ Ultimate;Win32String;%windir%\\branding\\basebrd\\basebrd.dll;12";
const __declspec(selectany) wchar_t*	resKeyBrandingSKUName = L"RKB1[];Ultimate;Win32String;%windir%\\branding\\basebrd\\basebrd.dll;13";
const __declspec(selectany) wchar_t*	resKeyBrandingCopyright = L"RKB1[];Copyright Message;Win32String;%windir%\\branding\\basebrd\\basebrd.dll;14";
const __declspec(selectany) wchar_t*	resKeyBrandingMicrosoft = L"RKB1[];Microsoft;Win32String;%windir%\\branding\\basebrd\\basebrd.dll;15";
const __declspec(selectany) wchar_t* resKeyAbout = L"RKB1[winver];About %s;Win32DialogString;%windir%\\system32\\shell32.dll;14352";



#define WELCOMECENTERBRANDING(skuname) 			
#define SYSTEMINFOBRANDING(reskey)				

//Sku and Product Name Strings

//const __declspec(selectany) wchar_t*	langNeutralWindowSVista(L"Windows Vista™");
#define WINDOWSVERSION L"Windows Vista™"

#define STARTER L"Starter"
#define ULTIMATE L"Ultimate"
#define ULTIMATE_N L"Ultimate N"
#define BUSINESS L"Business"
#define BUSINESS_N L"Business N"
#define HOME_BASIC L"Home Basic"
#define HOME_PREMIUM L"Home Premium"
#define ENTERPRISE L"Enterprise"
#define HOME_BASIC_N L"Home Basic N"
#define HOME_PREMIUM_N L"Home Premium N"
#define ENTERPRISE_N L"Enterprise N"

#define WINDOWS_STARTER WINDOWSVERSION L" " STARTER
#define WINDOWS_ULTIMATE WINDOWSVERSION L" " ULTIMATE
#define WINDOWS_BUSINESS WINDOWSVERSION L" " BUSINESS
#define WINDOWS_ULTIMATE_N WINDOWSVERSION L" " ULTIMATE_N
#define WINDOWS_BUSINESS_N WINDOWSVERSION L" " BUSINESS_N
#define WINDOWS_HOME_BASIC WINDOWSVERSION L" " HOME_BASIC
#define WINDOWS_ENTERPRISE WINDOWSVERSION L" " ENTERPRISE
#define WINDOWS_HOME_PREMIUM WINDOWSVERSION L" " HOME_PREMIUM
#define WINDOWS_HOME_BASIC_N WINDOWSVERSION L" " HOME_BASIC_N
#define WINDOWS_ENTERPRISE_N WINDOWSVERSION L" " ENTERPRISE_N
#define WINDOWS_HOME_PREMIUM_N WINDOWSVERSION L" " HOME_PREMIUM_N

#define WC_WINVER_SKU				L";Name => '{0}' && ClassName => 'CabinetWClass';Role = 'pane' && ClassName = 'DirectUIHWND';Name = '{1}' && Role = 'text'", resKeyWelcomeCenter, resKeyBrandingWindowsVistaTMSKUName
#define SYSINFO_WINVER_SKU			L";Name => '{0}' && ClassName => 'CabinetWClass';Role = 'client' && ClassName = 'DirectUIHWND';Name = '{1} {2}' && Role = 'text'", resKeySystem, resKeyBrandingWindowsVistaTM, resKeyBrandingSKUName
#define ABOUT_WINDOWS_SKU			L";Name => '{0}' && ClassName => 'Static';ControlId = '13587';[VisibleOnly]Role = 'text'", resKeyBrandingWindowsVistaTMSKUName
#define ABOUT_WINODWS_OK_BTN		L";Name => '{0}' && ClassName => '#32770';ControlId = '1';[VisibleOnly]Role = 'push button'", (wchar_t*) cmplxKeyAboutWindows


/*
#define WC_WINVER_HOMEBAS				WELCOMECENTERBRANDING(WINDOWS_HOME_BASIC)
#define WC_WINVER_HOMEN					WELCOMECENTERBRANDING(WINDOWS_HOME_BASIC_N)
#define WC_WINVER_ENTERPRISE			WELCOMECENTERBRANDING(WINDOWS_ENTERPRISE)
#define WC_WINVER_ENTERPRISEN			WELCOMECENTERBRANDING(WINDOWS_ENTERPRISE_N)
#define WC_WINVER_ULTIMATE				WELCOMECENTERBRANDING(WINDOWS_ULTIMATE)
#define WC_WINVER_ULTIMATEN				WELCOMECENTERBRANDING(WINDOWS_ULTIMATE_N)
#define WC_WINVER_BUSINESS				WELCOMECENTERBRANDING(WINDOWS_BUSINESS)
#define WC_WINVER_BUSINESSN				WELCOMECENTERBRANDING(WINDOWS_BUSINESS_N)
#define WC_WINVER_STARTER				WELCOMECENTERBRANDING(WINDOWS_STARTER)
#define WC_WINVER_HOMEPREM				WELCOMECENTERBRANDING(WINDOWS_HOME_PREMIUM)
#define WC_WINVER_HOMEPREMN				WELCOMECENTERBRANDING(WINDOWS_HOME_PREMIUM_N)

#define SYSINFO_WINVER_BUSINESSN		SYSTEMINFOBRANDING((wchar_t*) CMPLXKEYWINDOWSVISTABUSINESSN)
#define SYSINFO_WINVER_STARTER			SYSTEMINFOBRANDING((wchar_t*) CMPLXKEYWINDOWSVISTASTARTER)
#define SYSINFO_WINVER_HOMEPREM			SYSTEMINFOBRANDING((wchar_t*) CMPLXKEYWINDOWSVISTAHOMEPREM)
#define SYSINFO_WINVER_HOMEPREMN		SYSTEMINFOBRANDING((wchar_t*) CMPLXKEYWINDOWSVISTAHOMEPREMN)
#define SYSINFO_WINVER_HOMEBAS			SYSTEMINFOBRANDING((wchar_t*) CMPLXKEYWINDOWSVISTAHOMEBAS)
#define SYSINFO_WINVER_HOMEN			SYSTEMINFOBRANDING((wchar_t*) CMPLXKEYWINDOWSVISTAHOMEN)
#define SYSINFO_WINVER_ENTERPRISE		SYSTEMINFOBRANDING((wchar_t*) CMPLXKEYWINDOWSVISTAENTERPRISE)
#define SYSINFO_WINVER_ENTERPRISEN		SYSTEMINFOBRANDING((wchar_t*) CMPLXKEYWINDOWSVISTAENTERPRISEN)
#define SYSINFO_WINVER_ULTIMATEN		SYSTEMINFOBRANDING((wchar_t*) CMPLXKEYWINDOWSVISTAULTIMATEN)
#define SYSINFO_WINVER_ULTIMATE			SYSTEMINFOBRANDING((wchar_t*) CMPLXKEYWINDOWSVISTAULTIMATE)
#define SYSINFO_WINVER_BUSINESS			SYSTEMINFOBRANDING((wchar_t*) CMPLXKEYWINDOWSVISTABUSINESS)

const __declspec(selectany) wchar_t*	langNeutralUltimate(L"Ultimate");
const __declspec(selectany) wchar_t*	langNeutralUltimateN(L"Ultimate N");
const __declspec(selectany) wchar_t*	langNeutralBusiness(L"Business");
const __declspec(selectany) wchar_t*	langNeutralBusinessN(L"Business N");
const __declspec(selectany) wchar_t*	langNeutralEnterpriseN(L"Enterprise N");
const __declspec(selectany) wchar_t*	langNeutralEnterprise(L"Enterprise");
const __declspec(selectany) wchar_t*	langNeutralHomeBas(L"Home Basic");
const __declspec(selectany) wchar_t*	langNeutralHomeN(L"Home Basic N");
const __declspec(selectany) wchar_t*	langNeutralHomePrem(L"Home Premium");
const __declspec(selectany) wchar_t*	langNeutralHomePremN(L"Home Premium N");
const __declspec(selectany) wchar_t*	langNeutralStarter(L"Starter");

const __declspec(selectany) wchar_t*	langNeutralWindowsViStaHomeN(L"Windows Vista™ Home Basic N");
const __declspec(selectany) wchar_t*	langNeutralWindowsViStaEntN(L"Windows Vista™ Enterprise N");
const __declspec(selectany) wchar_t*	langNeutralWindowsViStaEnt(L"Windows Vista™ Enterprise");
const __declspec(selectany) wchar_t*	langNeutralWindowsViStaHomeBas(L"Windows Vista™ Home Basic");
const __declspec(selectany) wchar_t*	langNeutralWindowsViStaBusinessN(L"Windows Vista™ Business N");
const __declspec(selectany) wchar_t*	langNeutralWindowsViStaUltimateN(L"Windows Vista™ Ultimate N");
const __declspec(selectany) wchar_t*	langNeutralWindowsViStaUltimate(L"Windows Vista™ Ultimate");
const __declspec(selectany) wchar_t*	langNeutralWindowsViStaBusiness(L"Windows Vista™ Business");
const __declspec(selectany) wchar_t*	langNeutralWindowsViStaHomePremN(L"Windows Vista™ Home Premium N");
const __declspec(selectany) wchar_t*	langNeutralWindowsViStaHomePrem(L"Windows Vista™ Home Premium");
const __declspec(selectany) wchar_t*	langNeutralWindowsViStaStarter(L"Windows Vista™ Starter");

//#define CMPLXKEYWINDOWSVISTAHOMEN		L"'{0}' +'{1}'", resKeyBrandingWindowsVistaTM, langNeutralHomeN
//#define CMPLXKEYWINDOWSVISTAHOMEPREMN	L"'{0}' +'{1}'", resKeyBrandingWindowsVistaTM, langNeutralHomePremN
//#define CMPLXKEYWINDOWSVISTAHOMEBAS		L"'{0}' +'{1}'", resKeyBrandingWindowsVistaTM, langNeutralHomeBas
//#define CMPLXKEYWINDOWSVISTAENTERPRISE  L"'{0}' +'{1}'", resKeyBrandingWindowsVistaTM, langNeutralEnterprise
//#define CMPLXKEYWINDOWSVISTASTARTER		L"'{0}' +'{1}'", resKeyBrandingWindowsVistaTM, langNeutralStarter
//#define CMPLXKEYWINDOWSVISTABUSINESSN	L"'{0}' +'{1}'", resKeyBrandingWindowsVistaTM, langNeutralBusinessN
//#define CMPLXKEYWINDOWSVISTAULTIMATE	L"'{0}' +'{1}'", resKeyBrandingWindowsVistaTM, langNeutralUltimate
//#define CMPLXKEYWINDOWSVISTAULTIMATEN	L"'{0}' +'{1}'", resKeyBrandingWindowsVistaTM, langNeutralUltimateN
//#define CMPLXKEYWINDOWSVISTABUSINESS	L"'{0}' +'{1}'", resKeyBrandingWindowsVistaTM, langNeutralBusiness
//#define CMPLXKEYWINDOWSVISTAHOMEPREM	L"'{0}' +'{1}'", resKeyBrandingWindowsVistaTM, langNeutralHomePrem
//#define CMPLXKEYWINDOWSVISTAENTERPRISEN L"'{0}' +'{1}'", resKeyBrandingWindowsVistaTM, langNeutralEnterpriseN

*/