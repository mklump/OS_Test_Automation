/***************************************************************
// Description: BVT - InternetConnectionSharing entry point verification
//				     for first time and second time reconfiguraton in SKUs
// Created:     a-maklum
//
// Verify:      Pass test case if feature is available
//              in all SKUs but Starter and Home Basic
****************************************************************/

#include <windows.h>            //Common Windows types
#include "screenelement.h"             //RPF
//#include "rpf_constants.h"
#include "LoggingFunctions.h"
#include "rpf_SKUDIFF.h"
#include "SKUDIFF_UTIL.h"
#include "InternetConnectionSharing_BVT_Entrypoints.h"

using namespace RPFPlayback;
using namespace SKUDiff;

namespace InternetConnectionSharing_BVT
{
	#pragma region Resource Keys
	// Resource Keys
	const wchar_t* resKeyManageNetwork = L"RKB1[];Manage network connectionS;Win32String;%windir%\\system32\\netcenter.dll;21";
	const wchar_t* resKeyViewStatus = L"RKB1[];View statuS;Win32String;%windir%\\system32\\netcenter.dll;42";
	const wchar_t* resKeyGeneral = L"RKB1[];General;Win32DialogString;%windir%\\system32\\netshell.dll;23500";
	const wchar_t* resKeyProperties = L"RKB1[];%1 Prooerties;Win32String;%windir%\\system32\\netshell.dll;1057";
	const wchar_t* resKeyProperties2 = L"RKB1[];P&rooerties;Win32String;%windir%\\system32\\netshell.dll;1608";
	const wchar_t* resKeyNetworkConnections = L"RKB1[];Network Connections;Win32String;%windir%\\system32\\netshell.dll;1200";
	const wchar_t* resKeyLocalAreaConnection = L"RKB1[];Local Area Connection;Win32String;%windir%\\system32\\nci.dll;1803";
	const wchar_t* resKeySharing = L"RKB1[];Sharing;Win32DialogString;%windir%\\system32\\netshell.dll;10751";
	const wchar_t* resKeyStatus = L"RKB1[];%1 Status;Win32String;%windir%\\system32\\netshell.dll;23041";
	const wchar_t* resKeyPropertiesInnerDialoge = L"RKB1[];%1 Prooerties;Win32String;%windir%\\system32\\netshell.dll;1057";
	const wchar_t* resKeyOpen = L"RKB1[];&Open;NativeMenuString;%windir%\\system32\\browseui.dll;271;1";
	const wchar_t* resKeyControlPanel133 = L"RKB1[];Control Panel;Win32String;%windir%\\en-us\\explorer.exe.mui;8234";
	const wchar_t* resKeyNetwork = L"RKB1[];Network;Win32DialogString;%windir%\\system32\\en-us\\ntlanui2.dll.mui;1026";
	const wchar_t* resKeyAnd = L"RKB1[]; and;Win32String;%windir%\\system32\\en-us\\objsel.dll.mui;338";
	const wchar_t* resKeyNetworkandSharing = L"RKB1[];Network and Sharing Center;Win32String;%windir%\\system32\\networkexplorer.dll;1028";

	// Complex Resource Keys
	ComplexResourceKeyNative cmplxKeyPropertiesLocalArea(1, resKeyProperties, resKeyLocalAreaConnection);
	ComplexResourceKeyNative cmplxKeyPropertiesLocalArea2(1, resKeyPropertiesInnerDialoge, resKeyLocalAreaConnection);
	ComplexResourceKeyNative cmplxKeyStatusLocalArea(1, resKeyStatus, resKeyLocalAreaConnection);
	ComplexResourceKeyNative cmplxKeyControlPanelBslshNetwork(L"{%s%s%s%s%s}", resKeyInternet, langNeutralBslsh, resKeyAnd, resKeyNetwork, resKeyControlPanel133);
	/// LanguageNeutral Strings
	LanguageNeutralString langNeutralCPCategoryPanel(L"CPCategoryPanel");
	LanguageNeutralString langNeutralBslsh(L"");
	LanguageNeutralString lnsViewStatusLink(L";Name => '{0}' && ClassName => 'CabinetWClass';Role = 'text' && ClassName = 'DirectUIHWND';Name = '{1}' && Role = 'link'");
	LanguageNeutralString lnsManageNetworkConnections(L";Name => '{0}' && ClassName => 'CabinetWClass';Role = 'pane' && ClassName = 'DirectUIHWND';Name = '{1}' && Role = 'link'");
	#pragma endregion Resource Keys

	static BOOL bfinalResult = FALSE,
		fICSExpected = FALSE;

	// Initialize the Test(s)
	STDAPI InitTest(LPVOID)
	{
		HRESULT hr = SKUInitTest();
		return hr;
	}

	// Uninitialize/Cleanup Environment
	STDAPI UnInitTest()
	{
		//// Left Button Click - "push button" named "Close" in window "Local Area Connection" in window "Properties Localarea"
		//LogTestInfoW(__FUNCTIONW__, L"Clicking on \"push button\" named \"Close\" in window \"Local Area Connection\" in window \"Properties Localarea\"...");
		//if( SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => '#32770';Role = 'title bar' && ClassName = '#32770';Name = '{1}' && Role = 'push button'", (wchar_t*) cmplxKeyPropertiesLocalArea, resKeyClose))) )
		//	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		//// Left Button Click - "push button" named "Close" in window "Local Area Connection"
		//LogTestInfoW(__FUNCTIONW__, L"Clicking on \"push button\" named \"Close\" in window \"Status Local Area Connection\"...");
		//if( SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{1}' && ClassName => '#32770';Role = 'title bar' && ClassName = '#32770';Name = '{0}' && Role = 'push button'", resKeyClose, (wchar_t*) cmplxKeyStatusLocalArea))) )
		//	LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

		// Left Button Click - "push button" named "Close" in window "Local Area Connection"
		LogTestInfoW(__FUNCTIONW__, L"Clicking on \"push button\" named \"Close\" in window \"Local Area Connection\"...");
		if( SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => '#32770';Role = 'title bar' && ClassName = '#32770';Name = '{1}' && Role = 'push button'", (wchar_t*) cmplxKeyPropertiesLocalArea2, resKeyClose))) )
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		// Left Button Click - "push button" named "Close" in window "Network Connections"
		LogTestInfoW(__FUNCTIONW__, L"Clicking on \"push button\" named \"Close\" in window \"Network Connections\"...");
		if( SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'CabinetWClass';Role = 'title bar' && ClassName = 'CabinetWClass';Name = '{1}' && Role = 'push button'", resKeyNetworkConnections, resKeyClose))) )
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		// Left Button Click - "push button" named "Close" in window "Network and Sharing Center"
		LogTestInfoW(__FUNCTIONW__, L"Clicking on \"push button\" named \"Close\" in window \"Network and Sharing Center\"...");
		if( SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'CabinetWClass';Role = 'title bar' && ClassName = 'CabinetWClass';Name = '{1}' && Role = 'push button'", resKeyNetworkSharing, resKeyClose))) )
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		return SKUUnInitTest();
	}

	// This is a test for verifying that Internet Connection Sharing feature can be enabled through the entry point of
	// Start -> Control Panel -> Network and Internet -> Network and Sharing Center -> View Status (First Network Connection)
	// -> Properties -> Sharing Tab
	STDAPI ICSViewStatusEntryPoint(LPVOID pvReserved)
	{
		wchar_t *pwszResultInfo = L"Result information not set.",
			*expectedError = L"";
		HRESULT hr = E_FAIL;
		
		LogTestBeginW(__FUNCTIONW__, L"Verify that Internet Connection Sharing feature can be enabled on a supported SKU.");
		hr = IsInternetConnectionSharingAvailable(hr);
		fICSExpected = SUCCEEDED(hr);
		if( !fICSExpected )
		{
			expectedError = L"Internet Connection Sharing feature cannot be enabled on STARTER SKU. ";
			hr = E_FAIL;
		}
		// Used to pass flow of control to after the end of the while loop if a failue occurs using break statements.
		// This also allows the loop to be restarted with a continue statement if required.
		while( TRUE )
		{
			LogTestInfoW(__FUNCTIONW__, L"Opening START->CONTROL PANEL...");
			hr = LOG_FAILED_HR(OpenControlPanelHomeView());
			if( !SUCCEEDED(hr) )
			{
				LogTestInfoW(__FUNCTIONW__, L"First attempt to open START->CONTROL PANEL failed, retrying to open START->CONTROL PANEL.");
				hr = LOG_FAILED_HR( OpenStartMenu() );

				// Right Button Click - "menu item" named "Control Panel" in window "Start Menu"
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'DV2ControlHost';Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyClassicStart_ControlPanel));
				hr = LOG_FAILED_HR(RightButtonClick(CLICKABLE_POINT));

				// Left Button Click - "menu item" named "Open" in window ""
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";AccessibleName = '{1}' && ClassName => '#32768' && Role = 'popup menu';Name = '{0}' && Role = 'menu item'", resKeyOpen, resKeyContextMenu));
				hr = LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
			}
			if( SUCCEEDED(hr) )
				bfinalResult = TRUE;
			else
			{
				pwszResultInfo = L"Failed to open START->CONTROL PANEL.";
				bfinalResult = FALSE;
				break;
			}

			// Left Button Click - "link" named "Network and Internet" in window "Control Panel"
			LogTestInfoW(__FUNCTIONW__, L"Clicking on \"link\" named \"Network and Internet\" in window \"Control Panel\"...");
			if( SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(CPL_LINK_NETWORKINTERNET))) )
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				bfinalResult = TRUE;
			}
			else
			{
				pwszResultInfo = L"Failed to click on \"link\" named \"Network and Internet\" in window \"Control Panel.\"";
				bfinalResult = FALSE;
				break;
			}

			// Left Button Click - "link" named "Network and Sharing Center" in window "Control Panel\Network and Internet"
			LogTestInfoW(__FUNCTIONW__, L"Clicking on \"link\" named \"Network and Sharing Center\" in window \"Control Panel\\Network and Internet\"...");
			hr = LOG_FAILED_HR(WOWFromPartialQueryId(CPL_LINK_NETWORKSHARINGCENTER));
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
			if( FALSE == SUCCEEDED(hr) )
			{
				LogTestInfoW(__FUNCTIONW__, L"Failed to click on \"link\" named \"Network and Sharing Center\" in window \"Control Panel\\Network and Internet,\" trying again...");
				// Left Button Click - "link" named "Network and Sharing Center" in window "Control Panel\\Network and Internet"
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{1}' && ClassName => 'CabinetWClass';Name = '{0}' && Role = 'pane';[VisibleOnly]Name = '{2}' && Role = 'link'", langNeutralCPCategoryPanel, (wchar_t*) cmplxKeyControlPanelBslshNetwork, resKeyNetworkandSharing));
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
			}
			if( SUCCEEDED(hr) )
				bfinalResult = TRUE;
			else
			{
				pwszResultInfo = L"Failed to click on \"link\" named \"Network and Sharing Center\" in window \"Control Panel\\Network and Internet.\"";
				bfinalResult = FALSE;
				break;
			}

			// Left Button Click - "link" named "View Status" in window "Network and Sharing Center"
			LogTestInfoW(__FUNCTIONW__, L"Clicking on \"link\" named \"View Status\" in window \"Network and Sharing Center\"...");
			hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'CabinetWClass';Role = 'text' && ClassName = 'DirectUIHWND';Name = '{1}' && Role = 'link'", resKeyNetworkSharing, resKeyViewStatus));
			if( !SUCCEEDED(hr) )
			{
				LogTestInfoW(__FUNCTIONW__, L"Failed to find originally recorded View Status Link, retrying to find with LanguageNeutralString version...");
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(lnsViewStatusLink, resKeyNetworkSharing, resKeyViewStatus));
			}
			if( SUCCEEDED(hr) )
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				bfinalResult = TRUE;
			}
			else
			{
				pwszResultInfo = L"Failed to click on \"link\" named \"View Status\" in window \"Network and Sharing Center.\"";
				bfinalResult = FALSE;
				break;
			}

			// Left Button Click - "push button" named "Properties" in window "General"
			LogTestInfoW(__FUNCTIONW__, L"Clicking on \"push button\" named \"Properties\" in window \"General\"...");
			if( SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => '#32770';ControlId = '1026';Role = 'push button'", resKeyGeneral))) )
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				bfinalResult = TRUE;
			}
			else
			{
				pwszResultInfo = L"Failed to click on \"push button\" named \"Properties\" in window \"General.\"";
				bfinalResult = FALSE;
				break;
			}

			// Left Button Click - "page tab" named "Sharing" in window "Local Area Connection"
			LogTestInfoW(__FUNCTIONW__, L"Clicking on \"page tab\" named \"Sharing\" in window \"Local Area Connection\"...");
			if( SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => '#32770';Role = 'page tab list' && ClassName = 'SysTabControl32';Name = '{1}' && Role = 'page tab'", (wchar_t*) cmplxKeyPropertiesLocalArea, resKeySharing))) )
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				bfinalResult = TRUE;
			}
			else
			{
				pwszResultInfo = L"Failed to click on \"page tab\" named \"Sharing\" in window \"Local Area Connection.\"";
				LogTestInfoW(__FUNCTIONW__, L"Current domain IPSEC policy explicitly forbids enabling Internet Connection Sharing while connected to the corporate network.");
				LogTestInfoW(__FUNCTIONW__, L"Please check that test computer is not joined to any Microsoft domain.");
				bfinalResult = FALSE;
				break;
			}

			// Check and Uncheck - "check box" named "Allow other network users to connect through this computer's internet connection" in window "Sharing"
			LogTestInfoW(__FUNCTIONW__, L"Clicking on \"check box\" named \"Allow other network users to connect through this computer's internet connection\" in window \"Sharing\"...");
			hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => '#32770';ControlId = '105';Role = 'check box'", resKeySharing));
			hr = LOG_FAILED_HR( Check() );
			hr = LOG_FAILED_HR( Uncheck() );
			if( SUCCEEDED(hr) )
				bfinalResult = TRUE;
			else
			{
				pwszResultInfo = L"Failed to click on \"check box\" named \"Allow other network users to connect through this computer's internet connection\" in window \"Sharing.\"";
				LogTestInfoW(__FUNCTIONW__, L"Current domain IPSEC policy explicitly forbids enabling Internet Connection Sharing while connected to the corporate network.");
				LogTestInfoW(__FUNCTIONW__, L"Please check that test computer is not joined to any Microsoft domain.");
				bfinalResult = FALSE;
				break;
			}

			// Left Button Click - "push button" named "Close" in window "Local Area Connection" in window "Properties Localarea"
			LogTestInfoW(__FUNCTIONW__, L"Clicking on \"push button\" named \"Close\" in window \"Local Area Connection\" in window \"Properties Localarea\"...");
			if( SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => '#32770';Role = 'title bar' && ClassName = '#32770';Name = '{1}' && Role = 'push button'", (wchar_t*) cmplxKeyPropertiesLocalArea, resKeyClose))) )
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				bfinalResult = TRUE;
			}
			else
			{
				pwszResultInfo = L"Failed to click on \"push button\" named \"Close\" in window \"Local Area Connection\" in window \"Properties Localarea.\"";
				bfinalResult = FALSE;
				break;
			}

			// Left Button Click - "push button" named "Close" in window "Local Area Connection"
			LogTestInfoW(__FUNCTIONW__, L"Clicking on \"push button\" named \"Close\" in window \"Status Local Area Connection\"...");
			if( SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{1}' && ClassName => '#32770';Role = 'title bar' && ClassName = '#32770';Name = '{0}' && Role = 'push button'", resKeyClose, (wchar_t*) cmplxKeyStatusLocalArea))) )
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				bfinalResult = TRUE;
			}
			else
			{
				pwszResultInfo = L"Failed to click on \"push button\" named \"Close\" in window \"Status Local Area Connection.\"";
				bfinalResult = FALSE;
				break;
			}

			// Left Button Click - "push button" named "Close" in window "Network and Sharing Center"
			LogTestInfoW(__FUNCTIONW__, L"Clicking on \"push button\" named \"Close\" in window \"Network and Sharing Center\"...");
			if( SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'CabinetWClass';Role = 'title bar' && ClassName = 'CabinetWClass';Name = '{1}' && Role = 'push button'", resKeyNetworkSharing, resKeyClose))) )
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				bfinalResult = TRUE;
			}
			else
			{
				pwszResultInfo = L"Failed to click on \"push button\" named \"Close\" in window \"Network and Sharing Center.\"";
				bfinalResult = FALSE;
				break;
			}
			pwszResultInfo = L"Test succeeded with no errors.";
			break; // No matter what, when the execution stack pointer reaches this position, break out! of the while() loop.
		} // End while( TRUE )
		if( bfinalResult )
			hr = NOERROR;
		else
			hr = E_FAIL;
		bfinalResult = SUCCEEDED(hr);
		if( FALSE == bfinalResult && FALSE == fICSExpected )
		{
			LogTestInfoW(__FUNCTIONW__, L"Internet Connection Sharring feature SKU differentiation succeeded.");
			bfinalResult = TRUE;
		}
		LogTestInfoW(__FUNCTIONW__,
			L"Unit test function ICSViewStatusEntryPoint() has exited with error status: %s",
			bfinalResult ? L"0" : L"-1" );
		LogTestResultW(bfinalResult, __FUNCTIONW__, L"%s%s", expectedError, pwszResultInfo);
		return hr;
	} // End STDAPI ICSViewStatusEntryPoint(LPVOID pvReserved)

	// This is a test for verifying that Internet Connection Sharing feature can be enabled through the entry point of
	// Start -> Control Panel -> Network and Internet -> Network and Sharing Center -> Manage network connections ->
	// right click on network connection (First Network Connection) -> Properties -> Sharing Tab
	STDAPI ICSManageNetworkConnectionsEntryPoint(LPVOID pvReserved)
	{
		wchar_t *pwszResultInfo = L"Result information not set.",
			*expectedError = L"";
		HRESULT hr = E_FAIL;
		
		LogTestBeginW(__FUNCTIONW__, L"Verify that Internet Connection Sharing feature can be enabled on a supported SKU.");
		hr = IsInternetConnectionSharingAvailable(hr);
		fICSExpected = SUCCEEDED(hr);
		if( !fICSExpected )
		{
			expectedError = L"Internet Connection Sharing feature cannot be enabled on STARTER SKU. ";
			hr = E_FAIL;
		}
		// Used to pass flow of control to after the end of the while loop if a failue occurs using break statements.
		// This also allows the loop to be restarted with a continue statement if required.
		while( TRUE )
		{
			LogTestInfoW(__FUNCTIONW__, L"Opening START->CONTROL PANEL...");
			hr = LOG_FAILED_HR(OpenControlPanelHomeView());
			if( !SUCCEEDED(hr) )
			{
				LogTestInfoW(__FUNCTIONW__, L"First attempt to open START->CONTROL PANEL failed, retrying to open START->CONTROL PANEL.");
				hr = LOG_FAILED_HR( OpenStartMenu() );

				// Right Button Click - "menu item" named "Control Panel" in window "Start Menu"
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'DV2ControlHost';Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyClassicStart_ControlPanel));
				hr = LOG_FAILED_HR(RightButtonClick(CLICKABLE_POINT));

				// Left Button Click - "menu item" named "Open" in window ""
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";AccessibleName = '{1}' && ClassName => '#32768' && Role = 'popup menu';Name = '{0}' && Role = 'menu item'", resKeyOpen, resKeyContextMenu));
				hr = LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
			}
			if( SUCCEEDED(hr) )
				bfinalResult = TRUE;
			else
			{
				pwszResultInfo = L"Failed to open START->CONTROL PANEL.";
				bfinalResult = FALSE;
				break;
			}

			// Left Button Click - "link" named "Network and Internet" in window "Control Panel"
			LogTestInfoW(__FUNCTIONW__, L"Clicking on \"link\" named \"Network and Internet\" in window \"Control Panel\"...");
			if( SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(CPL_LINK_NETWORKINTERNET))) )
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				bfinalResult = TRUE;
			}
			else
			{
				pwszResultInfo = L"Failed to click on \"link\" named \"Network and Internet\" in window \"Control Panel.\"";
				bfinalResult = FALSE;
				break;
			}

			// Left Button Click - "link" named "Network and Sharing Center" in window "Control Panel\Network and Internet"
			LogTestInfoW(__FUNCTIONW__, L"Clicking on \"link\" named \"Network and Sharing Center\" in window \"Control Panel\\Network and Internet\"...");
			hr = LOG_FAILED_HR(WOWFromPartialQueryId(CPL_LINK_NETWORKSHARINGCENTER));
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
			if( FALSE == SUCCEEDED(hr) )
			{
				LogTestInfoW(__FUNCTIONW__, L"Failed to click on \"link\" named \"Network and Sharing Center\" in window \"Control Panel\\Network and Internet,\" trying again...");
				// Left Button Click - "link" named "Network and Sharing Center" in window "Control Panel\\Network and Internet"
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{1}' && ClassName => 'CabinetWClass';Name = '{0}' && Role = 'pane';[VisibleOnly]Name = '{2}' && Role = 'link'", langNeutralCPCategoryPanel, (wchar_t*) cmplxKeyControlPanelBslshNetwork, resKeyNetworkandSharing));
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
			}
			if( SUCCEEDED(hr) )
				bfinalResult = TRUE;
			else
			{
				pwszResultInfo = L"Failed to click on \"link\" named \"Network and Sharing Center\" in window \"Control Panel\\Network and Internet.\"";
				bfinalResult = FALSE;
				break;
			}
			
			// Left Button Click - "link" named "Manage network connections" in window "Network and Sharing Center"
			LogTestInfoW(__FUNCTIONW__, L"Clicking on \"link\" named \"Manage network connections\" in window \"Network and Sharing Center\"...");
			hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'CabinetWClass';Role = 'pane' && ClassName = 'DirectUIHWND';Name = '{1}' && Role = 'link'", resKeyNetworkSharing, resKeyManageNetwork));
			if( !SUCCEEDED(hr) )
			{
				LogTestInfoW(__FUNCTIONW__, L"Failed to find originally recorded Manage network connections link, retrying with LanguageNeutralString version...");
				hr = LOG_FAILED_HR(WOWFromPartialQueryId(lnsManageNetworkConnections, resKeyNetworkSharing, resKeyManageNetwork));
			}
			if( SUCCEEDED(hr) )
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				bfinalResult = TRUE;
			}
			else
			{
				pwszResultInfo = L"Failed to click on \"link\" named \"Manage network connections\" in window \"Network and Sharing Center.\"";
				bfinalResult = FALSE;
				break;
			}

			// Right Button Click - "list item" named "Local Area Connection" in window "Network Connections"
			LogTestInfoW(__FUNCTIONW__, L"Clicking on \"list item\" named \"Local Area Connection\" in window \"Network Connections\"...");
			if( SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'CabinetWClass';Role = 'list' && ClassName = 'SysListView32';Name = '{1}' && Role = 'list item'", resKeyNetworkConnections, resKeyLocalAreaConnection))) )
			{
				LOG_FAILED_HR(RightButtonClick(CLICKABLE_POINT));
				bfinalResult = TRUE;
			}
			else
			{
				pwszResultInfo = L"Failed to click on \"list item\" named \"Local Area Connection\" in window \"Network Connections.\"";
				bfinalResult = FALSE;
				break;
			}

			// Left Button Click - "menu item" named "Properties" in window "Right Click Context Menu"
			LogTestInfoW(__FUNCTIONW__, L"Clicking on \"menu item\" named \"Properties\" in window \"Right Click Context Menu\"...");
			if( SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(L";AccessibleName = '{1}' && ClassName => '#32768' && Role = 'popup menu';Name = '{0}' && Role = 'menu item'", resKeyProperties2, resKeyContextMenu))) )
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				bfinalResult = TRUE;
			}
			else
			{
				pwszResultInfo = L"Failed to click on \"menu item\" named \"Properties\" in window \"Right Click Context Menu.\"";
				bfinalResult = FALSE;
				break;
			}

			// Left Button Click - "page tab" named "Sharing" in window "Local Area Connection"
			LogTestInfoW(__FUNCTIONW__, L"Clicking on \"page tab\" named \"Sharing\" in window \"Local Area Connection\"...");
			if( SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => '#32770';Role = 'page tab list' && ClassName = 'SysTabControl32';Name = '{1}' && Role = 'page tab'", (wchar_t*) cmplxKeyPropertiesLocalArea2, resKeySharing))) )
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				bfinalResult = TRUE;
			}
			else
			{
				pwszResultInfo = L"Failed to click on \"page tab\" named \"Sharing\" in window \"Local Area Connection.\"";
				LogTestInfoW(__FUNCTIONW__, L"Current domain IPSEC policy explicitly forbids enabling Internet Connection Sharing while connected to the corporate network.");
				LogTestInfoW(__FUNCTIONW__, L"Please check that test computer is not joined to any Microsoft domain.");
				bfinalResult = FALSE;
				break;
			}

			// Check and Uncheck - "check box" named "Allow other network users to connect through this computer's internet connection" in window "Sharing"
			LogTestInfoW(__FUNCTIONW__, L"Clicking on \"check box\" named \"Allow other network users to connect through this computer's internet connection\" in window \"Sharing\"...");
			hr = LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => '#32770';ControlId = '105';Role = 'check box'", resKeySharing));
			hr = LOG_FAILED_HR( Check() );
			hr = LOG_FAILED_HR( Uncheck() );
			if( SUCCEEDED(hr) )
				bfinalResult = TRUE;
			else
			{
				pwszResultInfo = L"Failed to click on \"check box\" named \"Allow other network users to connect through this computer's internet connection\" in window \"Sharing.\"";
				LogTestInfoW(__FUNCTIONW__, L"Current domain IPSEC policy explicitly forbids enabling Internet Connection Sharing while connected to the corporate network.");
				LogTestInfoW(__FUNCTIONW__, L"Please check that test computer is not joined to any Microsoft domain.");
				bfinalResult = FALSE;
				break;
			}

			// Left Button Click - "push button" named "Close" in window "Local Area Connection"
			LogTestInfoW(__FUNCTIONW__, L"Clicking on \"push button\" named \"Close\" in window \"Local Area Connection\"...");
			if( SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => '#32770';Role = 'title bar' && ClassName = '#32770';Name = '{1}' && Role = 'push button'", (wchar_t*) cmplxKeyPropertiesLocalArea2, resKeyClose))) )
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				bfinalResult = TRUE;
			}
			else
			{
				pwszResultInfo = L"Failed to click on \"push button\" named \"Close\" in window \"Local Area Connection.\"";
				bfinalResult = FALSE;
				break;
			}

			// Left Button Click - "push button" named "Close" in window "Network Connections"
			LogTestInfoW(__FUNCTIONW__, L"Clicking on \"push button\" named \"Close\" in window \"Network Connections\"...");
			if( SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'CabinetWClass';Role = 'title bar' && ClassName = 'CabinetWClass';Name = '{1}' && Role = 'push button'", resKeyNetworkConnections, resKeyClose))) )
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				bfinalResult = TRUE;
			}
			else
			{
				pwszResultInfo = L"Failed to click on \"push button\" named \"Close\" in window \"Network Connections.\"";
				bfinalResult = FALSE;
				break;
			}

			// Left Button Click - "push button" named "Close" in window "Network and Sharing Center"
			LogTestInfoW(__FUNCTIONW__, L"Clicking on \"push button\" named \"Close\" in window \"Network and Sharing Center\"...");
			if( SUCCEEDED(LOG_FAILED_HR(WOWFromPartialQueryId(L";Name => '{0}' && ClassName => 'CabinetWClass';Role = 'title bar' && ClassName = 'CabinetWClass';Name = '{1}' && Role = 'push button'", resKeyNetworkSharing, resKeyClose))) )
			{
				LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
				bfinalResult = TRUE;
			}
			else
			{
				pwszResultInfo = L"Failed to click on \"push button\" named \"Close\" in window \"Network and Sharing Center.\"";
				bfinalResult = FALSE;
				break;
			}

			pwszResultInfo = L"Test succeeded with no errors.";
			break; // No matter what, when the execution stack pointer reaches this position, break out! of the while() loop.
		} // End while( TRUE )

		if( bfinalResult )
			hr = NOERROR;
		else
			hr = E_FAIL;
		bfinalResult = SUCCEEDED(hr);
		if( FALSE == bfinalResult && FALSE == fICSExpected )
		{
			LogTestInfoW(__FUNCTIONW__, L"Internet Connection Sharring feature SKU differentiation succeeded.");
			bfinalResult = TRUE;
		}
		LogTestInfoW(__FUNCTIONW__,
			L"Unit test function ICSManageNetworkConnectionsEntryPoint() has exited with error status: %s",
			bfinalResult ? L"0" : L"-1" );
		LogTestResultW(bfinalResult, __FUNCTIONW__, L"%s%s", expectedError, pwszResultInfo);
		return hr;
	} // End STDAPI ICSManageNetworkConnectionsEntryPoint(LPVOID pvReserved)
} // End STDAPI ICSViewStatusEntryPoint(LPVOID pvReserved)
