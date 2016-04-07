#include <windows.h>            //Common Windows types
#include "screenelement.h"  
#include "LoggingFunctions.h"
#include "rpf_SKUDIFF.h"
#include "SKUDIFF_UTIL.h"
#include "SKUDIFF_MASK.h"

using namespace RPFPlayback;
using namespace SKUDiff;

const wchar_t* resKeyTurnWindowsFeaturesOnOffTask = L"RKB1[explorer];Turn WindowS features on or off;Win32String;%windir%\\system32\\appwiz.cpl;188";
const wchar_t* resKeyWindowsFeaturesCancel = L"RKB1[];Cancel;Win32String;%windir%\\system32\\appwiz.cpl;97";

#define WINDOWSFEATURES_CANCEL					L";Name => '{0}' && ClassName => 'NativeHWNDHost';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyWindowsFeatures, resKeyWindowsFeaturesCancel
#define CP_PROGRAMS_WINDOWSFEATURES				L";Name => '{0}' && ClassName => 'CabinetWClass';[VisibleOnly]Name = '{1}' && Role = 'link'", resKeyControlPanel, resKeyTurnWindowsFeaturesOnOffTask
#define CP_PROGRAMS_WINDOWSFEATURES_CLOSE_BTN   L";Name => '{0}' && ClassName => 'CabinetWClass';[VisibleOnly]Role = 'title bar' && ClassName = 'CabinetWClass';Name = '{1}' && Role = 'push button'", resKeyProgramsFeatures, resKeyClose    


void CloseExcessWindows() // test specific, ensure a clean state; can be made better with RPF 14+
{
	MultiLeftClickUntilGone(3,	WINDOWSFEATURES_CANCEL,	CPL_CLOSE_BTN, CP_PROGRAMS_WINDOWSFEATURES_CLOSE_BTN);
}

STDAPI InitTest(LPVOID)
{
	HRESULT hr = SKUInitTest();
	if SUCCEEDED(hr){CloseExcessWindows();}
	LogSKU();

	if(FAILED(OpenSpecificControlPanel(CPL_LINK_PROGRAMS, CPL_LINK_PROGRAMSFEATURES)))
	{
		LogTestResultW(FALSE, __FUNCTIONW__, L"Failed to open Programs and Features control panel.");
		return(E_FAIL);
	}

	LOG_FAILED_HR(WOWFromPartialQueryId(CP_PROGRAMS_WINDOWSFEATURES));
	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	// Wait a moment, for the features to be indexed.
	Snooze(10);
	return hr;
}

STDAPI UnInitTest()
{
	CloseExcessWindows();
	return SKUUnInitTest();
}


///////////////////////////////////
// Cannot check current checkbox state due to well known Accessibility bug for Treeviews.
///////////////////////////////////


HRESULT WindowsFeatures_Generic_Item(__in wchar_t *szFeatureDecription,__in wchar_t *szPackageName,__in int sdfMaskAvailable)//,__in int sdfMaskInstalled)
{
	try
	{
		HRESULT hr;

		BOOL fAvailableExpected = FeatureExpected(sdfMaskAvailable);
		BOOL fAvailableFound;
		BOOL fAvailablePassed = FALSE;
		
		LPWSTR pwszResultInfo = NULL;

		LogTestBeginW(__FUNCTIONW__, L"Verify %s should be %s in Windows Features.",
			szFeatureDecription,
			fAvailableExpected ? L"Available": L"Not Available");    




		wchar_t pwszRes[1024];
		if (FAILED(ResourceFromMUM(szPackageName, pwszRes, 1024)))
		{
			LogTestInfoW(__FUNCTIONW__, L"Unable to extract the package name, Safe to assume feature is not available.");
			fAvailableFound = FALSE;
		}
		else
		{
			LogTestInfoW(__FUNCTIONW__, L"%s appears to be named: %s",szFeatureDecription, pwszRes);

			hr = WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'NativeHWNDHost';[VisibleOnly]Name = '{0}' && Role = 'outline';Name = '{1}' && Role = 'outline item'", resKeyWindowsFeatures,pwszRes);
			if (SUCCEEDED(hr))
			{
				LogTestInfoW(__FUNCTIONW__, L"%s appears to be present",szFeatureDecription);
				fAvailableFound = TRUE;
			}
			else
			{
				LogTestInfoW(__FUNCTIONW__, L"%s appears to NOT be present",szFeatureDecription);
				fAvailableFound = FALSE;
			}
		}
		if (fAvailableFound == fAvailableExpected)
		{
			LogTestInfoW(__FUNCTIONW__, L"%s Availability is correct.",szFeatureDecription);
			fAvailablePassed = TRUE;
		}
		else
		{
			LogTestInfoW(__FUNCTIONW__, L"%s Availability is Incorrect.",szFeatureDecription);
			fAvailablePassed = FALSE;
		}
		LogTestResultW(fAvailablePassed, __FUNCTIONW__, pwszResultInfo);
		return NOERROR;
	}
	catch (...)
	{
		LogTestInfoW(__FUNCTIONW__, L"An exception occured while checking %s.",szFeatureDecription);
		return E_FAIL;
	}

}

STDAPI PremiumGames_WindowsFeature(LPVOID pvReserved)
{
	return WindowsFeatures_Generic_Item(L"Premium Games",L"Shell-PremiumInboxGames",SDF_WFA_PREMIUM_GAMES);//,SDF_WFD_UNIX
}
STDAPI Tablet_WindowsFeature(LPVOID pvReserved)
{
	return WindowsFeatures_Generic_Item(L"Tablet PC Components",L"TabletPC-OC",SDF_WFA_TABLET);//,SDF_WFD_UNIX
}
STDAPI SUA_WindowsFeature(LPVOID pvReserved)
{
	return WindowsFeatures_Generic_Item(L"Services for UNIX Applications",L"SUA",SDF_WFA_UNIX);//,SDF_WFD_UNIX
}
STDAPI NFS_WindowsFeature(LPVOID pvReserved)
{
	return WindowsFeatures_Generic_Item(L"Services for NFS Networks",L"NFS-ClientSKU",SDF_WFA_NFS);//,SDF_WFD_NFS
}
STDAPI Extras_WindowsFeature(LPVOID pvReserved)
{
	return WindowsFeatures_Generic_Item(L"Windows Ultimate Extras",L"Ultimate-Extras",SDF_WFA_EXTRAS);//,SDF_WFD_EXTRAS
}
STDAPI Fax_Scan_WindowsFeature(LPVOID pvReserved)
{
	return WindowsFeatures_Generic_Item(L"Windows Fax and Scan",L"Fax-Client-*",SDF_WFA_FAXSCAN);//,SDF_WFD_FAXSCAN
}
STDAPI Meetingspace_WindowsFeature(LPVOID pvReserved)
{
	return WindowsFeatures_Generic_Item(L"Windows Meetingspace",L"PeerToPeer-AdhocMeetings",SDF_WFA_MEETINGSPACE);//,SDF_WFD_FAXSCAN
}
STDAPI ActiveX_WindowsFeature(LPVOID pvReserved)
{
	return WindowsFeatures_Generic_Item(L"ActiveX thing",L"AxInstallService",SDF_WFA_ACTIVEX);//,SDF_WFD_FAXSCAN
}

