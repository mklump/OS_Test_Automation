////////////////////////////////////////////////////////////////
//
// This source file contains RPF Reskeys and Query ID's for navigating the system Control Panel,
// utility functions to do most of the navigation for you, are in SKU_UTIL.h
//
//  Copyright (C) Microsoft Corporation, 2008. For internal use only.
//
/////////////////////////////////////////////////////////////////////////////////

// a-jomul: Created file late 2007

#pragma region Resource Keys
// 'and' 'or' 'of' etc. pruned from res key names	

const __declspec(selectany) wchar_t* resKeyControlPanel = L"RKB1[];Control Panel;Win32String;%WINDIR%\\system32\\shell32.dll;4161";

// Wildcard group
const __declspec(selectany) wchar_t* resKeyStart_ControlPanel = L"RKB1[];Control Panel;Win32String;%WINDIR%\\explorer.exe;8234";
const __declspec(selectany) wchar_t* resKeyClassicStart_ControlPanel = L"RKB1[];&Control Panel;NativeMenuString;%WINDIR%\\explorer.exe;204;505";

const __declspec(selectany) wchar_t* resKeyClassicView = L"RKB1[];Elassic View;Win32String;%WINDIR%\\system32\\shell32.dll;31058";
const __declspec(selectany) wchar_t* resKeyControlPanelHome = L"RKB1[];Control Panel Home;Win32String;%WINDIR%\\system32\\shell32.dll;31057";

//Home view link names
const __declspec(selectany) wchar_t* resKeyEaseAccess = L"RKB1[];Ease of Access;Win32String;%WINDIR%\\system32\\shell32.dll;32000";

const __declspec(selectany) wchar_t* resKeyAppearancePersonalization = L"RKB1[];ABBearance and PerSonalization;Win32String;%WINDIR%\\system32\\shell32.dll;32004";
const __declspec(selectany) wchar_t* resKeyPrograms = L"RKB1[];Programs;Win32String;%WINDIR%\\system32\\shell32.dll;32006";
const __declspec(selectany) wchar_t* resKeyHardwareSound = L"RKB1[];Hardware and Sound;Win32String;%WINDIR%\\system32\\shell32.dll;32008";
const __declspec(selectany) wchar_t* resKeyNetworkInternet = L"RKB1[];Network and Internet;Win32String;%WINDIR%\\system32\\shell32.dll;32010";
const __declspec(selectany) wchar_t* resKeyAdditionalOptions = L"RKB1[];Additional Ootions;Win32String;%WINDIR%\\system32\\shell32.dll;32012";
const __declspec(selectany) wchar_t* resKeySystemMaintenance = L"RKB1[];System and Maintenance;Win32String;%WINDIR%\\system32\\shell32.dll;32014";
const __declspec(selectany) wchar_t* resKeyClockLanguageRegion = L"RKB1[];Clock, Language, and Region;Win32String;%WINDIR%\\system32\\shell32.dll;32016";
const __declspec(selectany) wchar_t* resKeySecurity = L"RKB1[];Security;Win32String;%WINDIR%\\system32\\shell32.dll;32018";

// Wildcard group
const __declspec(selectany) wchar_t* resKeyUserAccountsPlain = L"RKB1[];User Accounts;Win32String;%WINDIR%\\system32\\shell32.dll;32002";
const __declspec(selectany) wchar_t* resKeyUserAccountsFamilySafety = L"RKB1[];User Accounts and Family Safety;Win32String;%WINDIR%\\system32\\shell32.dll;32022";


//home view sub-area link names
const __declspec(selectany) wchar_t* resKeyFonts = L"RKB1[];Fonts;Win32String;%WINDIR%\\system32\\shell32.dll;22981";
const __declspec(selectany) wchar_t* resKeyPrinters = L"RKB1[];Printers;Win32String;%WINDIR%\\system32\\shell32.dll;9319";

const __declspec(selectany) wchar_t* resKeyBackupRestoreCenter = L"RKB1[];BackuB and Restore Center;Win32String;%WINDIR%\\system32\\brcpl.dll;1";
const __declspec(selectany) wchar_t* resKeySystem = L"RKB1[];System;Win32String;%WINDIR%\\system32\\systemcpl.dll;1";
const __declspec(selectany) wchar_t* resKeyWindowsUpdate = L"RKB1[];Windows UBdate;Win32String;%WINDIR%\\system32\\wucltux.dll;1";
const __declspec(selectany) wchar_t* resKeyPowerOptions = L"RKB1[];Power Options;Win32String;%WINDIR%\\system32\\powercpl.dll;1";
const __declspec(selectany) wchar_t* resKeyUserAccounts = L"RKB1[];User Accounts;Win32String;%WINDIR%\\system32\\usercpl.dll;1";
const __declspec(selectany) wchar_t* resKeyBitLockerDriveEncryption = L"RKB1[];BitLocker Drive EncryBtion;Win32String;%WINDIR%\\system32\\fvecpl.dll;1";
const __declspec(selectany) wchar_t* resKeyPersonalization = L"RKB1[];Personalization;Win32String;%WINDIR%\\system32\\themecpl.dll;1";
const __declspec(selectany) wchar_t* resKeyNetworkSharing = L"RKB1[];Network and Sharing Center;Win32String;%WINDIR%\\system32\\netcenter.dll;1";
const __declspec(selectany) wchar_t* resKeyAutoPlay = L"RKB1[];AutoPlay;Win32String;%WINDIR%\\system32\\autoplay.dll;1";
const __declspec(selectany) wchar_t* resKeyWindowsSideShow = L"RKB1[];Windows SideShow;Win32String;%WINDIR%\\system32\\auxiliarydisplaycpl.dll;1";
const __declspec(selectany) wchar_t* resKeyDefaultPrograms = L"RKB1[];Default Programs;Win32String;%WINDIR%\\system32\\sud.dll;1";
const __declspec(selectany) wchar_t* resKeyPerformanceInformationTools = L"RKB1[];Performance Information and Tools;Win32String;%WINDIR%\\system32\\perfcentercpl.dll;1";

const __declspec(selectany) wchar_t* resKeyDateTime = L"RKB1[];Date and Time;Win32String;%WINDIR%\\system32\\timedate.cpl;51";
const __declspec(selectany) wchar_t* resKeyWelcomeCenter = L"RKB1[];Welcome Center;Win32String;%WINDIR%\\system32\\oobefldr.dll;33056";
const __declspec(selectany) wchar_t* resKeyParentalControls = L"RKB1[];Parental Controls;Win32String;%WINDIR%\\system32\\wpccpl.dll;100";
const __declspec(selectany) wchar_t* resKeyEaseAccessCenter = L"RKB1[];Ease of Access Center;Win32String;%WINDIR%\\system32\\accessibilitycpl.dll;10";
const __declspec(selectany) wchar_t* resKeySyncCenter = L"RKB1[];SYnc Center;Win32String;%WINDIR%\\system32\\synccenter.dll;3000";
const __declspec(selectany) wchar_t* resKeyProgramsFeatures = L"RKB1[];Programs and Features;Win32String;%WINDIR%\\system32\\appwiz.cpl;159";





//link names that leave the control panel UI
const __declspec(selectany) wchar_t* resKeyDeviceManager = L"RKB1[];Device Manager;Win32String;%WINDIR%\\system32\\devmgr.dll;4";
const __declspec(selectany) wchar_t* resKeyColorManagement = L"RKB1[];Color Management;Win32String;%WINDIR%\\system32\\colorcpl.exe;6";

const __declspec(selectany) wchar_t* resKeyOfflineFiles = L"RKB1[];Offline Files;Win32String;%WINDIR%\\system32\\cscui.dll;45";

const __declspec(selectany) wchar_t* resKeyMouse = L"RKB1[];Mouse;Win32String;%WINDIR%\\system32\\main.cpl;100";
const __declspec(selectany) wchar_t* resKeyScannersCameras = L"RKB1[];Scanners and Cameras;Win32String;%ProgramFiles%\\windows photo gallery\\imagingdevices.exe;101";
const __declspec(selectany) wchar_t* resKeyKeyboard = L"RKB1[];Keyboard;Win32String;%WINDIR%\\system32\\main.cpl;102";
const __declspec(selectany) wchar_t* resKeyWindowsDefender = L"RKB1[];WindowS Defender;Win32String;%ProgramFiles%\\windows defender\\msmpres.dll;104";
const __declspec(selectany) wchar_t* resKeyProblemReportsSolutions = L"RKB1[];broblem ReBortS and SolutionS;Win32String;%WINDIR%\\system32\\wercon.exe;350";
const __declspec(selectany) wchar_t* resKeyIndexingOptions = L"RKB1[];Indexing OptionS;Win32String;%WINDIR%\\system32\\srchadmin.dll;601";
const __declspec(selectany) wchar_t* resKeyPeopleNearMe = L"RKB1[];PeoBle Near Me;Win32String;%WINDIR%\\system32\\p2phost.exe;710";

const __declspec(selectany) wchar_t* resKeyGetProgramsOnline = L"RKB1[];Get ProgramS Online;Win32String;%WINDIR%\\system32\\appwiz.cpl;1070";
const __declspec(selectany) wchar_t* resKeyGameControllers = L"RKB1[];Game Controllers;Win32String;%WINDIR%\\system32\\joy.cpl;1076";
const __declspec(selectany) wchar_t* resKeySecurityCenter = L"RKB1[];Security Center;Win32String;%WINDIR%\\system32\\wscui.cpl;2001";
const __declspec(selectany) wchar_t* resKeyInternetOptions = L"RKB1[];Internet Options;Win32String;%WINDIR%\\system32\\inetcpl.cpl;4312";
const __declspec(selectany) wchar_t* resKeyWindowsFirewall = L"RKB1[];Windows Firewall;Win32String;%WINDIR%\\system32\\firewallcontrolpanel.exe;3000";

const __declspec(selectany) wchar_t* resKeyTabletPCSettings = L"RKB1[];Tablet PC Settings;Win32String;%WINDIR%\\system32\\tabletpc.cpl;10100";
const __declspec(selectany) wchar_t* resKeyPenInputDevices = L"RKB1[];Pen and Input Devices;Win32String;%WINDIR%\\system32\\tabletpc.cpl;10103";
const __declspec(selectany) wchar_t* resKeyWindowsSidebar = L"RKB1[];Windows Sidebar ProBerties;Win32String;%ProgramFiles%\\windows sidebar\\sidebar.exe;11003";
const __declspec(selectany) wchar_t* resKeyAdministrativeTools = L"RKB1[];Administrative ToolS;Win32String;%WINDIR%\\system32\\shell32.dll;22982";
const __declspec(selectany) wchar_t* resKeyFolderOptions = L"RKB1[];Folder Ootions;Win32String;%WINDIR%\\system32\\shell32.dll;22985";
const __declspec(selectany) wchar_t* resKeyTaskbarStartMenu = L"RKB1[];Taskbar and Start Menu;Win32String;%WINDIR%\\system32\\shell32.dll;32517";
const __declspec(selectany) wchar_t* resKeyRegionalLanguageOptions = L"RKB1[];Regional and Language Options;Win32String;%windir%\\system32\\intl.cpl;1";


/// LanguageNeutral Strings
const __declspec(selectany) wchar_t* langNeutralCPCategoryPanel(L"CPCategoryPanel");
//const __declspec(selectany) wchar_t* langNeutralCPNavPanel(L"CPNavPanel");
const __declspec(selectany) wchar_t* langNeutralBslsh(L"\\");


/// Personalization control panel

//const __declspec(selectany) wchar_t* resKeyPersonalization = L"RKB1[explorer];Personalization;Win32String;$.\\system32\\themecpl.dll;1";
//const __declspec(selectany) wchar_t* resKeyPersonalizationMainTask = L"RKB1[explorer];Personalization Main Task;Win32String;$.\\system32\\themecpl.dll;4";

//LanguageNeutralString langNeutralWindowsCardSpace(L"Windows CardSpace");

//const __declspec(selectany) wchar_t* resKeyScreenSaver = L"RKB1[];Screen Saver;Win32String;$.\\themecpl.dll;1227";
//#define CPL_CHANGE_SCREEN_SAVER                 L";Name => '{0}' && ClassName => 'CabinetWClass';Name = '{1}' && Role = 'pane';[VisibleOnly]Name = '{2}' && Role = 'link'", resKeyPersonalization, resKeyPersonalizationMainTask, resKeyScreenSaver
//#define PUSHBUTTONCLOSEEXCLPERSON L";Name => '{0}' && ClassName => 'CabinetWClass';[VisibleOnly]Role = 'title bar' && ClassName = 'CabinetWClass';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyPersonalization, langNeutralClose

/// Complex Resource Keys

/// probably not needed, unless we plan to check which categories links appear under.
/*
ComplexResourceKeyNative cmplxKeyControlPanelSystemMaintenance(L"{%s%s%s}", resKeyControlPanel, langNeutralBslsh, resKeySystemMaintenance);
ComplexResourceKeyNative cmplxKeyControlPanelUserAccountsFamilySafety(L"{%s%s%s}", resKeyControlPanel, langNeutralBslsh, resKeyUserAccountsFamilySafety);
ComplexResourceKeyNative cmplxKeyControlPanelSecurity(L"{%s%s%s}", resKeyControlPanel, langNeutralBslsh, resKeySecurity);
ComplexResourceKeyNative cmplxKeyControlPanelAppearancePersonalization(L"{%s%s%s}", resKeyControlPanel, langNeutralBslsh, resKeyAppearancePersonalization);
ComplexResourceKeyNative cmplxKeyControlPanelNetworkInternet(L"{%s%s%s}", resKeyControlPanel, langNeutralBslsh, resKeyNetworkInternet);
ComplexResourceKeyNative cmplxKeyControlPanelHardwareSound(L"{%s%s%s}", resKeyControlPanel, langNeutralBslsh, resKeyHardwareSound);
ComplexResourceKeyNative cmplxKeyControlPanelPrograms(L"{%s%s%s}", resKeyControlPanel, langNeutralBslsh, resKeyPrograms);
ComplexResourceKeyNative cmplxKeyControlPanelEaseAccess(L"{%s%s%s}", resKeyControlPanel, langNeutralBslsh, resKeyEaseAccess);
ComplexResourceKeyNative cmplxKeyControlPanelClockLanguageRegion(L"{%s%s%s}", resKeyControlPanel, langNeutralBslsh, resKeyClockLanguageRegion);
*/
#pragma endregion Resource Keys

#pragma region Query Ids

#define CPL_CLOSE_BTN                           L";Name => '{0}' && ClassName => 'CabinetWClass';[VisibleOnly]Role = 'title bar' && ClassName = 'CabinetWClass';Name = '{1}' && Role = 'push button'", resKeyControlPanel, resKeyClose    
/// For Control Panel

#define CPL_HOME_VIEW_LINK                       L";[VisibleOnly]Name => '{0}' && ClassName => 'CabinetWClass';[VisibleOnly]Name = 'CPNavPanel' && Role = 'pane';[VisibleOnly]Name = '{1}'", resKeyControlPanel,  resKeyControlPanelHome// && Role = 'link'
#define CPL_CLASSIC_VIEW_LINK                    L";[VisibleOnly]Name => '{0}' && ClassName => 'CabinetWClass';[VisibleOnly]Name = 'CPNavPanel' && Role = 'pane';[VisibleOnly]Name = '{1}'", resKeyControlPanel,  resKeyClassicView// && Role = 'link';Name = 'CPNavPanel' && Role = 'pane'

/// common template for all control panel link items

#define CONTROLPANELHOMELINK  L";Name => '{0}' && ClassName => 'CabinetWClass';[VisibleOnly]Name = 'CPCategoryPanel' && Role = 'pane';[VisibleOnly]Name = '{1}' && Role = 'link'"
#define CONTROLPANELCLASSICICON  L";Name => '{0}' && ClassName => 'CabinetWClass';ControlID = '1';Name = '{1}' && Role = 'list item'"
//Category Links in Control Panel Home 'Root'

#define CPL_LINK_SYSTEMMAINTENANCE			CONTROLPANELHOMELINK, resKeyControlPanel, resKeySystemMaintenance
#define CPL_LINK_USERACCOUNTSFAMILYSAFETY	CONTROLPANELHOMELINK, resKeyControlPanel, resKeyUserAccountsFamilySafety
#define CPL_LINK_APPEARANCEPERSONALIZATION	CONTROLPANELHOMELINK, resKeyControlPanel, resKeyAppearancePersonalization
#define CPL_LINK_SECURITY					CONTROLPANELHOMELINK, resKeyControlPanel, resKeySecurity
#define CPL_LINK_HARDWARESOUND				CONTROLPANELHOMELINK, resKeyControlPanel, resKeyHardwareSound
#define CPL_LINK_EASEACCESS					CONTROLPANELHOMELINK, resKeyControlPanel, resKeyEaseAccess
#define CPL_LINK_ADDITIONALOPTIONS			CONTROLPANELHOMELINK, resKeyControlPanel, resKeyAdditionalOptions
#define CPL_LINK_PROGRAMS					CONTROLPANELHOMELINK, resKeyControlPanel, resKeyPrograms
#define CPL_LINK_CLOCKLANGUAGEREGION			CONTROLPANELHOMELINK, resKeyControlPanel, resKeyClockLanguageRegion
#define CPL_LINK_NETWORKINTERNET				CONTROLPANELHOMELINK, resKeyControlPanel, resKeyNetworkInternet


//Item links in Catagories of Home view, they might appear in more than one area.

#define CPL_LINK_ADMINISTRATIVETOOLS			CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyAdministrativeTools
#define CPL_LINK_AUTOPLAY					CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyAutoPlay
#define CPL_LINK_BACKUPRESTORECENTER			CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyBackupRestoreCenter
#define CPL_LINK_BITLOCKERDRIVEENCRYPTION	CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyBitLockerDriveEncryption
#define CPL_LINK_COLORMANAGEMENT				CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyColorManagement
#define CPL_LINK_DATETIME					CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyDateTime
#define CPL_LINK_DEFAULTPROGRAMS				CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyDefaultPrograms
#define CPL_LINK_DEVICEMANAGER				CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyDeviceManager
#define CPL_LINK_EASEACCESSCENTER			CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyEaseAccessCenter
#define CPL_LINK_FOLDEROPTIONS				CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyFolderOptions
#define CPL_LINK_FONTSCONTROLPANEL			CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyFonts
#define CPL_LINK_GAMECONTROLLERS				CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyGameControllers
#define CPL_LINK_GETPROGRAMSONLINE			CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyGetProgramsOnline
#define CPL_LINK_INDEXINGOPTIONS				CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyIndexingOptions
#define CPL_LINK_INTERNETOPTIONS				CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyInternetOptions
#define CPL_LINK_KEYBOARD					CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyKeyboard
#define CPL_LINK_MOUSE						CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyMouse
#define CPL_LINK_NETWORKSHARINGCENTER		CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyNetworkSharing
#define CPL_LINK_OFFLINEFILES				CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyOfflineFiles
#define CPL_LINK_PARENTALCONTROLS			CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyParentalControls
#define CPL_LINK_PERSONALIZATION				CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyPersonalization
#define CPL_LINK_PENINPUTDEVICES				CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyPenInputDevices
#define CPL_LINK_PERFORMANCEINFORMATION		CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyPerformanceInformation
#define CPL_LINK_POWEROPTIONS				CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyPowerOptions
#define CPL_LINK_PRINTERS					CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyPrinters
#define CPL_LINK_PROGRAMSFEATURES			CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyProgramsFeatures
#define CPL_LINK_PROBLEMREPORTSSOLUTIONS		CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyProblemReportsSolutions
#define CPL_LINK_SECURITYCENTER				CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeySecurityCenter
#define CPL_LINK_SCANNERSCAMERAS				CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyScannersCameras
#define CPL_LINK_SYSTEMCONTROLPANEL			CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeySystem
#define CPL_LINK_SYNCCENTER					CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeySyncCenter
#define CPL_LINK_TABLETPCSETTINGS			CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyTabletPCSettings
#define CPL_LINK_TASKBARSTARTMENU			CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyTaskbarStartMenu
#define CPL_LINK_USERACCOUNTS				CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyUserAccountsFamilySafety
#define CPL_LINK_WELCOMECENTER				CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyWelcomeCenter
#define CPL_LINK_WINDOWSDEFENDER				CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyWindowsDefender
#define CPL_LINK_WINDOWSSIDEBARPROPERTIES	CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyWindowsSidebar
#define CPL_LINK_WINDOWSSIDESHOW				CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyWindowsSideShow
#define CPL_LINK_WINDOWSUPDATE				CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyWindowsUpdate

/// Manually created, untested links.

#define CPL_LINK_WINDOWSFIREWALL				CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyWindowsFirewall
#define CPL_LINK_PEOPLENEARME				CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyPeopleNearMe
#define CPL_LINK_REGIONALLANGUAGEOPTIONS		CONTROLPANELHOMELINK, (wchar_t*) resKeyControlPanel, resKeyRegionalLanguageOptions

// Classic view icons.

#define CPL_ICON_ADMINISTRATIVETOOLS			CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyAdministrativeTools
#define CPL_ICON_AUTOPLAY					CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyAutoPlay
#define CPL_ICON_BACKUPRESTORECENTER			CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyBackupRestoreCenter
#define CPL_ICON_BITLOCKERDRIVEENCRYPTION	CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyBitLockerDriveEncryption
#define CPL_ICON_COLORMANAGEMENT				CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyColorManagement
#define CPL_ICON_DATETIME					CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyDateTime
#define CPL_ICON_DEFAULTPROGRAMS				CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyDefaultPrograms
#define CPL_ICON_DEVICEMANAGER				CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyDeviceManager
#define CPL_ICON_EASEACCESSCENTER			CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyEaseAccessCenter
#define CPL_ICON_FOLDEROPTIONS				CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyFolderOptions
#define CPL_ICON_FONTSCONTROLPANEL			CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyFonts
#define CPL_ICON_GAMECONTROLLERS				CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyGameControllers
#define CPL_ICON_GETPROGRAMSONLINE			CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyGetProgramsOnline
#define CPL_ICON_INDEXINGOPTIONS				CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyIndexingOptions
#define CPL_ICON_INTERNETOPTIONS				CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyInternetOptions
#define CPL_ICON_KEYBOARD					CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyKeyboard
#define CPL_ICON_MOUSE						CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyMouse
#define CPL_ICON_NETWORKSHARINGCENTER		CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyNetworkSharing
#define CPL_ICON_OFFLINEFILES				CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyOfflineFiles
#define CPL_ICON_PARENTALCONTROLS			CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyParentalControls
#define CPL_ICON_PERSONALIZATION				CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyPersonalization
#define CPL_ICON_PENINPUTDEVICES				CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyPenInputDevices
#define CPL_ICON_PERFORMANCEINFORMATION		CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyPerformanceInformation
#define CPL_ICON_POWEROPTIONS				CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyPowerOptions
#define CPL_ICON_PRINTERS					CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyPrinters
#define CPL_ICON_PROGRAMSFEATURES			CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyProgramsFeatures
#define CPL_ICON_PROBLEMREPORTSSOLUTIONS		CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyProblemReportsSolutions
#define CPL_ICON_SECURITYCENTER				CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeySecurityCenter
#define CPL_ICON_SCANNERSCAMERAS				CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyScannersCameras
#define CPL_ICON_SYSTEMCONTROLPANEL			CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeySystem
#define CPL_ICON_SYNCCENTER					CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeySyncCenter
#define CPL_ICON_TABLETPCSETTINGS			CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyTabletPCSettings
#define CPL_ICON_TASKBARSTARTMENU			CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyTaskbarStartMenu
#define CPL_ICON_USERACCOUNTS				CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyUserAccountsFamilySafety
#define CPL_ICON_WELCOMECENTER				CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyWelcomeCenter
#define CPL_ICON_WINDOWSDEFENDER				CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyWindowsDefender
#define CPL_ICON_WINDOWSSIDEBARPROPERTIES	CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyWindowsSidebar
#define CPL_ICON_WINDOWSSIDESHOW				CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyWindowsSideShow
#define CPL_ICON_WINDOWSUPDATE				CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyWindowsUpdate

//new
#define CPL_ICON_MOBILEPC				CONTROLPANELCLASSICICON, (wchar_t*) resKeyControlPanel, resKeyMobilePC


#pragma endregion Query Ids
