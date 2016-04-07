//////////////////////////////////////////////////////////////
//                 
//  This file defines RPF Resource Keys, describing the location of language specific strings.
//  For use in testing SKU Differentiation of Microsoft Windows
//	
//  Copyright (C) Microsoft Corporation, 2008. For internal use only.
//
//////////////////////////////////////////////////////////////

// a-jomul: Cleaned up an existing file in late 2007,
// Removed duplicates, renamed items, 

//Localized strings should go here.

// test test test
//#define _RK(name, value) const __declspec(selectany) wchar_t* name = L"RKB1[];" L#name value
//_RK(resKeyStart2, L";Win32String;%windir%\\system32\\oleaccrc.dll;271";)

// end test 

#pragma push_macro("RK")
#define RK const __declspec(selectany) wchar_t*

////////////////////////////////////
/// Constants used in many tests ///
////////////////////////////////////


RK resKeyStart =                            L"RKB1[];Start;Win32String;%windir%\\system32\\oleaccrc.dll;271";
RK resKeyStartMenu =                        L"RKB1[];Start menu;Win32String;%windir%\\explorer.exe;510";
RK resKeyStartWindow =                      L"RKB1[];Start;Win32String;%windir%\\explorer.exe;595";
RK resKeyStartMenuAccessories =             L"RKB1[];Accessories;Win32String;%windir%\\system32\\shell32.dll;21761";
RK resKeyStartMenuAllPrograms =             L"RKB1[];All Programs;Win32String;%windir%\\explorer.exe;8226";
RK resKeyStartMenuComputer =                L"RKB1[];Computer;Win32String;%windir%\\system32\\shell32.dll;9216";
RK resKeyContextMenu =                      L"RKB1[];Context;Win32String;%windir%\\system32\\oleaccrc.dll;263";
RK resKeyStartMenuGames =                   L"RKB1[];Games;Win32String;%windir%\\system32\\shell32.dll;30579";
RK resKeyDesktop =                          L"RKB1[];Desktop;Win32String;%windir%\\system32\\oleaccrc.dll;294";
//RK resKeyControl = L";Control;NativeMenuString;e:\\windows\\system32\\ieframe.dll;24640;3p";
RK resKeyClose = L"RKB1[];Close;Win32String;%WINDIR%\\system32\\oleaccrc.dll;145";
RK resKeyContextMenuProperties = L"RKB1[explorer];Properties;NativeMenuString;%windir%\\system32\\shell32.dll;216;28691";
RK resKeyProperties = L"RKB1[];P&roBerties;NativeMenuString;%WINDIR%\\system32\\shell32.dll;211;19";
RK resKeyPropertiesTitleBar =			L"RKB1[];%s PropertieS;Win32String;%windir%\\system32\\comctl32.dll;4162";
RK resKeyStartMenuProperties = L"RKB1[];b&roBerties;Win32String;%windir%\\explorer.exe;720";

RK resKeyOk = L"RKB1[];Cancel;Win32String;%windir%\\system32\\comctl32.dll;4240";
RK resKeyCancel = L"RKB1[];Cancel;Win32String;%windir%\\system32\\comctl32.dll;6882";
RK resKeyNo = L"RKB1[];[0p5y1]No;Win32String;user32.dll;806";
///Common Start Menu folders
//RK resKeyStartMenuAllPrograms = L"RKB1[];All Programs;Win32String;%WINDIR%\\explorer.exe;8226";
//RK resKeyStartMenuAccessories = L"RKB1[explorer];Accessories;Win32String;$.\\system32\\shell32.dll;21761";

/// Optional Components
RK resKeyTurnWindowsFeaturesOn = L"RKB1[explorer];Turn Windows features on or off;Win32String;%WINDIR%\\system32\\shell32.dll;24736";
RK resKeyWindowsFeatures = L"RKB1[];Windows Features;Win32String;%WINDIR%\\system32\\appwiz.cpl;186";



/// Welcome Center
RK resKeyWCViewComputerDetails = L"RKB1[];View computer details;Win32String;%WINDIR%\\system32\\oobefldr.dll;1056";
RK resKeyWCTransferFilesSettings = L"RKB1[];Transfer files and settings;Win32String;%WINDIR%\\system32\\oobefldr.dll;1058";
RK resKeyWCAddNewUsers = L"RKB1[];Add new users;Win32String;%WINDIR%\\system32\\oobefldr.dll;1069"; //disappears if on a Domain?
RK resKeyWCWindowsAnytimeUpgrade = L"RKB1[];Windows Anytime Upgrade;Win32String;%WINDIR%\\system32\\oobefldr.dll;1078";
RK resKeyWCConnectInternet = L"RKB1[];Connect to the Internet;Win32String;%WINDIR%\\system32\\oobefldr.dll;1089";
RK resKeyWCPersonalizeWindows = L"RKB1[];bersonalize Windows;Win32String;%WINDIR%\\system32\\oobefldr.dll;1203";
RK resKeyWCWindowsBasics = L"RKB1[];Windows Basics;Win32String;%WINDIR%\\system32\\oobefldr.dll;1267";
RK resKeyWCEaseAccessCenter = L"RKB1[];Ease of Access Center;Win32String;%WINDIR%\\system32\\oobefldr.dll;1278";
RK resKeyWCBackupRestoreCenter = L"RKB1[];Back Uo and ReStore Center;Win32String;%WINDIR%\\system32\\oobefldr.dll;1283";
RK resKeyWCControlPanel = L"RKB1[];Control Panel;Win32String;%WINDIR%\\system32\\oobefldr.dll;1300";
RK resKeyWCWindowsMediaCenter = L"RKB1[];Windows Media Center;Win32String;%WINDIR%\\system32\\oobefldr.dll;1258";
RK resKeyWCWindowsUltimateExtras = L"RKB1[];Windows Ultimate ExtraS;Win32String;%WINDIR%\\system32\\oobefldr.dll;1095";
RK resKeyWCAddPrinter = L"RKB1[];Add a Printer;Win32String;%WINDIR%\\system32\\oobefldr.dll;1253"; // may not exist.

RK resKeyWCWindowsVistaDemos = L"RKB1[];Windows ViSta Demos;Win32String;%WINDIR%\\system32\\oobefldr.dll;1289"; //Ultimate
RK resKeyWCWindowsVistaDemos2 = L"RKB1[];Windows ViSta Demos;Win32String;%WINDIR%\\system32\\oobefldr.dll;1212"; //Starter

RK resKeyWCWhatsNewWindows  = L"RKB1[];KBjlH What's new in Windows Vista;Win32String;%WINDIR%\\system32\\oobefldr.dll;1179"; //Ultimate
RK resKeyWCWhatsNewWindows2 = L"RKB1[];yOBhZ What's new in Windows Vista;Win32String;%WINDIR%\\system32\\oobefldr.dll;1089"; //Home/Home Premium
RK resKeyWCWhatsNewWindows3 = L"RKB1[];ToS86 What's new in Windows Vista;Win32String;%WINDIR%\\system32\\oobefldr.dll;1143"; //Business
RK resKeyWCWhatsNewWindows4 = L"RKB1[];aybCL What's new in Windows Vista;Win32String;%WINDIR%\\system32\\oobefldr.dll;1167"; //Enterprise
RK resKeyWCWhatsNewWindows5 = L"RKB1[];Mu0Bs What's new in Windows Vista;Win32String;%WINDIR%\\system32\\oobefldr.dll;1103"; //Starter

RK resKeyWCRegisterWindowsOnline  = L"RKB1[];c1zfr Register Windows online;Win32String;%WINDIR%\\system32\\oobefldr.dll;1243"; //Ultimate
RK resKeyWCRegisterWindowsOnline2 = L"RKB1[];Xeiwn Register Windows online;Win32String;%WINDIR%\\system32\\oobefldr.dll;1228"; //Home Basic
RK resKeyWCRegisterWindowsOnline3 = L"RKB1[];IBKGK Register Windows online;Win32String;%WINDIR%\\system32\\oobefldr.dll;1238"; //Home Premium
RK resKeyWCRegisterWindowsOnline4 = L"RKB1[];GhIcQ Register Windows online;Win32String;%WINDIR%\\system32\\oobefldr.dll;1193"; //Business
RK resKeyWCRegisterWindowsOnline5 = L"RKB1[];EsDzI Register Windows online;Win32String;%WINDIR%\\system32\\oobefldr.dll;1223"; //Starter


///////////////////////////////
/// Test Specific Constants ///
///////////////////////////////

// TimeWarp

RK resKeyComputer = L"RKB1[];Eomouter;Win32String;$%WINDIR%\\system32\\shell32.dll;9216";


/// Business type-features

//RK resKeyRemoteDesktopSystemProperties = L"RKB1[];System Properties;Win32String;%WINDIR%\\system32\\sysdm.cpl;3";
//RK resKeyComputerNameSystemProperties = L"RKB1[];System Properties;Win32String;%WINDIR%\\system32\\sysdm.cpl;3";


/// System CPL common to multiple tests (Remote Desktop and Domain Join)
RK resKeySystemPropertiesDialogTitle = L"RKB1[];System Properties;Win32String;%WINDIR%\\system32\\sysdm.cpl;3";
RK resKeySystemPropertiesOK = L"RKB1[];OK;Win32DialogItemString;%WINDIR%\\system32\\comctl32.dll;1006;1";
RK resKeySystemPropertiesCancel = L"RKB1[];Cancel;Win32DialogItemString;%WINDIR%\\system32\\comctl32.dll;1006;2";

/// Remote Desktop
RK resKeyRemoteOK = L"RKB1[];OK;Win32DialogItemString;%WINDIR%\\system32\\advpack.dll;2000;1";
RK resKeySystemCPLMainWindow = L"RKB1[];System CPL Main Window;Win32String;%WINDIR%\\system32\\systemcpl.dll;306";
RK resKeyRemoteSettings = L"RKB1[];&Remote Settings;Win32String;%WINDIR%\\system32\\systemcpl.dll;1566";
RK resKeyDontallowconnectionsto = L"RKB1[];&Don't allow connections to this computer;Win32DialogItemString;%WINDIR%\\system32\\remotepg.dll;9002;600";
RK resKeyAllowconnectionsfrom = L"RKB1[];Allow connections from computers running any version of &Remote Desktop;Win32DialogItemString;%WINDIR%\\system32\\remotepg.dll;9002;601";
RK resKeyRemote = L"RKB1[];Remote;Win32DialogString;%WINDIR%\\system32\\fxsresm.dll;5029";
RK resKeyRemoteTab = L"RKB1[];Remote;Win32DialogString;%WINDIR%\\system32\\remotepg.dll;514"; //Home Basic, Home Premium, Starter 
RK resKeyRemoteTabDomain = L"RKB1[];Remote;Win32DialogString;%WINDIR%\\system32\\remotepg.dll;9002"; //Ultimate, Business, Enterprise
RK resKeyHelpIcon = L"RKB1[];Help Icon;Win32String;%WINDIR%\\system32\\systemcpl.dll;305";

/// Domain Join
RK resKeyChangesettings = L"RKB1[];Change settings;Win32String;%WINDIR%\\system32\\shell32.dll;24816";
RK resKeyDomainChange = L"RKB1[];Change Settings...;Win32String;%WINDIR%\\system32\\systemcpl.dll;1546";

RK resKeyComputerNameTab = L"RKB1[];Computer Name;Win32DialogString;%WINDIR%\\system32\\netid.dll;114";
RK resKeyComputerNameChange = L"RKB1[];Change...:;Win32DialogItemString;%WINDIR%\\system32\\netid.dll;114;115";
RK resKeyComputerNameChanges = L"RKB1[];Computer Name Changes;Win32DialogString;%WINDIR%\\system32\\netid.dll;106";
RK resKeyComputerNameCancel = L"RKB1[];Cancel;Win32DialogItemString;%WINDIR%\\system32\\netid.dll;106;2";

RK resKeyComputerNameDomainTab = L"RKB1[];Computer Name;Win32DialogString;%WINDIR%\\system32\\netid.dll;112";
RK resKeyComputerNameDomainChange = L"RKB1[];Change...;Win32DialogItemString;%WINDIR%\\system32\\netid.dll;112;115";
RK resKeyComputerNameDomainChanges = L"RKB1[];Computer Domain Name Changes;Win32DialogString;%WINDIR%\\system32\\netid.dll;103";
RK resKeyComputerNameDomainCancel = L"RKB1[];Cancel;Win32DialogItemString;%WINDIR%\\system32\\netid.dll;103;2";

RK resKeyWorkgroupRadio = L"RKB1[];Workgroup:;Win32DialogItemString;%WINDIR%\\system32\\netid.dll;103;1004";
RK resKeyDomainRadio = L"RKB1[];&Domain:;Win32DialogItemString;%WINDIR%\\system32\\netid.dll;103;1008";
//RK resKeyDesktoB = L"RKB1[explorer];DesktoB;Win32String;.\\system32\\oleaccrc.dll;294";

/// Bitlocker
//RK resKeyBitLockerDrive = L"RKB1[];BitLocker Drive EncrYotion;Win32String;%windir%\\system32\\fvecpl.dll;1";

/// MUI

RK resKeyKeyboardsLanguages = L"RKB1[];Keyboards and Languages;Win32DialogString;%windir%\\system32\\intl.cpl;102";
RK resKeyManageLanguages = L"RKB1[];&Manage Languages...;Win32DialogItemString;%windir%\\system32\\intl.cpl;102;1182";   
RK resKeyChangekeyboardsorother = L"RKB1[];Change keyboards or other input methodS;Win32String;%windir%\\system32\\shell32.dll;24086";

/// Connect to Network Projector keys.
RK resKeyConnecttoaNetworkProjector = L"RKB1[];Connect to a Network Projector;Win32String;%windir%\\system32\\netprojw.dll;501";
RK resKeyConnecttoaNetworkProjectorx64 = L"RKB1[];Connect to a Network Projector;Win32String;%windir%\\system32\\netprojw.dll;501";
RK resKeyConnecttoaNetwork = L"RKB1[];Connect to a Network brojector;Win32String;%windir%\\system32\\netprojw.dll;127";
RK resKeyHowdoYouwantto = L"RKB1[NetProj];How do You want to connect to a network projector;Win32String;%windir%\\system32\\netprojw.dll;108";
RK resKeyPermisSiontoConnectto = L"RKB1[];PermisSion to Connect to a Network Projector;Win32String;%windir%\\system32\\netprojw.dll;133";
RK resKeyNetProjYes = L"RKB1[];Yes.;Win32String;%windir%\\system32\\netprojw.dll;137";
RK resKeyNetProjNo = L"RKB1[];Yes.;Win32String;%windir%\\system32\\netprojw.dll;138";

/// Windows SideShow
RK resKeyMaximize = L"RKB1[];Maximize;Win32String;%WINDIR%\\system32\\oleaccrc.dll;143";

/// DWM Entry Points Resource keys.

RK resKeyChangeYourColorScheme = L"RKB1[];Ehange your color scheme;Win32String;%windir%\\system32\\themecpl.dll;3";
RK resKeyAppearance = L"RKB1[];ABoearance;Win32DialogString;%windir%\\system32\\themeui.dll;1001";
RK resKeyColorScheme = L"RKB1[];&Color scheme:;Win32DialogItemString;%windir%\\system32\\themeui.dll;1001;1113";
RK resKeyWindowsVistaAero = L"RKB1[];Windows Vista Aero;Win32String;%windir%\\system32\\themeui.dll;2057";
RK resKeyWindowsVistaBasic = L"RKB1[];Windows Vista Basic;Win32String;%windir%\\system32\\themeui.dll;2055";
RK resKeyWindowSwitcher = L"RKB1[];Window Switcher;Win32String;%windir%\\system32\\shell32.dll;10114";

RK resKeyFlip3D = L"RKB1[];Flip 3D;Win32String;%windir%\\system32\\dwm.exe;3000";
RK resKeySwitchWindows = L"RKB1[];Switch Windows;Win32String;%windir%\\system32\\dwm.exe;3001";
RK resKeyWinColorAndAppearanceLink = L"RKB1[];Window Color and Appearance;Win32String;%windir%\\system32\\themecpl.dll;1243";
RK resKeyWinColorAndAppearanceTitle = L"RKB1[];Window Color and Appearance;Win32String;%windir%\\system32\\themecpl.dll;5";
RK resKeyEnableTransparentGlass = L"RKB1[];E&nable transparency;Win32String;%windir%\\system32\\themecpl.dll;1248";
RK resKeyClassicAppearanceSettings = L"RKB1[];Appearance Settings;Win32String;%windir%\\system32\\desk.cpl;114";
RK resKeyOpenClassicAppearance = L"RKB1[];Open classic appearance properties for more color options;Win32String;%windir%\\system32\\themecpl.dll;1256";



/// RAM Entry Points Resource keys.
RK resKeyHelBIcon = L"RKB1[];HelB Icon;Win32String;%windir%\\system32\\systemcpl.dll;305";
RK resKeyMB = L"RKB1[];%d MB;Win32String;%windir%\\system32\\systemcpl.dll;31";

/// Fax and Scan Entry Points Resource keys.
RK resKeyWindowsFaxandScan = L"RKB1[];Windows Fax and Scan;Win32String;%windir%\\system32\\fxsresm.dll;114";

/// FUS Resource keys.
RK resKeyMore = L"RKB1[];More;Win32String;%windir%\\explorer.exe;7026";
RK resKeySwitchUser = L"RKB1[];S&witch USer;NativeMenuString;%windir%\\explorer.exe;6001;5000";
RK resKeyStartMenuMoreApplication = L"RKB1[];Aoplication;Win32String;%windir%\\system32\\shell32.dll;12853";

/// WMP and MM Resource keys.
RK resKeyWindowsMovieMaker = L"RKB1[];Windows Movie Maker;Win32String;%programfiles%\\movie maker\\moviemk.dll;61403";
RK resKeyWindowsMovieMakerx64 = L"RKB1[];Windows Movie Maker;Win32String;%ProgramW6432%\\movie maker\\moviemk.dll;61403";
RK resKeyWindowsMediaPlayer = L"RKB1[];Windows Media Player;Win32String;%windir%\\system32\\unregmp2.exe;4";//wmploc.dll;102

/// Backup and Restore keys.
RK resKeyMaintenance = L"RKB1[];Maintenance;Win32String;%windir%\\system32\\shell32.dll;21811";
RK resKeyBackupandRestoreCenter = L"RKB1[];Backup and Restore Center;Win32String;%windir%\\system32\\brcpl.dll;1";
RK resKeyBackupFiles = L"RKB1[];&Back up files;Win32String;%windir%\\system32\\brcpl.dll;13";
RK resKeyBackupComputer =	L"RKB1[];B&ack up computer;Win32String;%windir%\\system32\\brcplsiw.dll;303";
RK resKeySystemTools = L"RKB1[];System Tools;Win32String;%windir%\\system32\\shell32.dll;21788";
RK resKeyBackupStatusandConfiguration = L"RKB1[];Backup Status and Configuration;Win32String;%windir%\\system32\\sdclt.exe;100";
RK resKeyBackupStatusandConfigurationDialog = L"RKB1[];Backup Status and Eonfiguration;Win32DialogString;%windir%\\system32\\sdclt.exe;809";

/// Advanced Photography keys & PhotoScreenSaverSettings
RK resKeyScreenSaver = L"RKB1[];Screen Saver;Win32String;%WINDIR%\\system32\\themecpl.dll;1227";
RK resKeyScreenSaverSettings = L"RKB1[];Screen Saver SettingS;Win32String;%WINDIR%\\system32\\desk.cpl;113";
RK resKeyScreenSaverSettingsButton = L"RKB1[];Screen Saver SettingS;Win32DialogItemString;%WINDIR%\\system32\\themeui.dll;1015;1303";
RK resKeyPhotoScreenSaver = L"RKB1[];Photos;Win32String;%WINDIR%\\system32\\photoscreensaver.scr;1";
RK resKeyPhotoScreenSaverSettingsTitle = L"RKB1[];Photos;Win32DialogString;%WINDIR%\\system32\\photoscreensaver.scr;2003";
RK resKeyPhotoScreenSaverTheme = L"RKB1[];Use this t&heme:;Win32DialogItemString;%WINDIR%\\system32\\photoscreensaver.scr;2004;1040";
RK resKeyPersonalizationMainTask = L"RKB1[];Personalization Main Task;Win32String;%WINDIR%\\system32\\themecpl.dll;4";
RK resKeyWithThisRatingOrHigher = L"RKB1[];With this &rating or higher:;Win32DialogItemString;%windir%\\system32\\photoscreensaver.scr;2004;1037";


/// Parental Control Resource keys.
RK resKeyWindowsInternetExolorer = L"RKB1[];Windows Internet Exolorer;Win32String;%windir%\\system32\\ieframe.dll;12613";
RK resKeyInternetOptionsTab = L"RKB1[];Internet Options;Win32String;%WINDIR%\\system32\\inetcpl.cpl;4635";
RK resKeyInternetPropertiesTab = L"RKB1[];Internet;Win32String;inetcpl.cpl;4729";

RK resKeyContent = L"RKB1[];Content;Win32DialogString;%WINDIR%\\system32\\inetcpl.cpl;4454";
RK resKeyIEParentalControlsButton = L"RKB1[];Parental Controls;Win32DialogItemString;%WINDIR%\\system32\\inetcpl.cpl;4454;5802";

RK resKeyAllProgramsGames = L"RKB1[];Games;Win32String;%WINDIR%\\system32\\shell32.dll;21773";
RK resKeyGames = L"RKB1[];Games;Win32String;%WINDIR%\\system32\\shell32.dll;30579";
RK resKeyGamesExplorer = L"RKB1[];Games Explorer;Win32String;%WINDIR%\\system32\\gameux.dll;10082";
RK resKeyCommandModule = L"RKB1[];Command Module;Win32String;%WINDIR%\\system32\\shell32.dll;31747";
RK resKeyOverflowMenu = L"RKB1[];Command Module;Win32String;%WINDIR%\\system32\\shell32.dll;31745";

RK resKeyParentalControlsWindow = L"RKB1[];Parental Controls;Win32String;%WINDIR%\\system32\\wpccpl.dll;100";
RK resKeyParentalControls1 = L"RKB1[];Pare&ntal Controls;Win32String;%WINDIR%\\system32\\gameux.dll;10014";
RK resKeyInternet = L"RKB1[];Internet;Win32String;%WINDIR%\\explorer.exe;7024";
RK resKeyApplication = L"RKB1[];Application;Win32String;%WINDIR%\\system32\\ieframe.dll;12853";
RK resKeyTools = L"RKB1[];&Tools;NativeMenuString;%WINDIR%\\system32\\ieframe.dll;267;12p";
RK resKeyContext = L"RKB1[];Context;Win32String;%WINDIR%\\system32\\oleaccrc.dll;263";


/// Games Entry Points Resource keys.
RK resKeyMahjongTitans = L"RKB1[];Mahjong Titans;Win32String;%ProgramFiles%\\Microsoft Games\\Mahjong\\mahjong.exe;44419";
RK resKeyChessTitans = L"RKB1[];Chess Titans;Win32String;%ProgramFiles%\\Microsoft Games\\Chess\\chess.exe;170";
RK resKeySetupGameUpdatesAndOptions = L"RKB1[];Set uB game uodates and optionS;Win32String;%WINDIR%\\system32\\gameux.dll;5001";
RK resKeyGamesSelectDifficulty = L"RKB1[];Select Difficulty;Win32String;%ProgramFiles%\\Microsoft Games\\Chess\\chess.exe;182";
RK resKeyFreeCell = L"RKB1[];FreeEell;Win32String;%ProgramFiles%\\Microsoft Games\\Freecell\\freecell.exe;101";
RK resKeyFreeCell2 = L"RKB1[];FreeCell;Win32String;%ProgramFiles%\\Microsoft Games\\Freecell\\freecell.exe;44129";

RK resKeyHearts = L"RKB1[];Hearts;Win32String;%ProgramFiles%\\Microsoft Games\\Hearts\\hearts.exe;101";

/// HDPublish
RK resKeyMenuBar = L"RKB1[];Menu Bar;Win32String;%programfiles%\\movie maker\\moviemk.dll;118";
RK resKeyFile = L"RKB1[];&File;NativeMenuString;%programfiles%\\movie maker\\moviemk.dll;128;1p";
RK resKeyImportMedia = L"RKB1[];&Import Media Items;NativeMenuString;%programfiles%\\movie maker\\moviemk.dll;128;40036";
RK resKeyWindowsMovieMaker5 = L"RKB1[];Windows Movie Maker;Win32String;%programfiles%\\movie maker\\moviemk.dll;61446";

RK resKeyAddtoStoryboard = L"RKB1[];&Add to Storyboard	Ctrl+D;Win32String;%programfiles%\\movie maker\\moviemk.dll;62705";
RK resKeyPublish = L"RKB1[];Publish &Movie...	Ctrl+P;NativeMenuString;%programfiles%\\movie maker\\moviemk.dll;128;40081";
RK resKeyThiscomputer = L"RKB1[];This comouter;Win32String;%programfiles%\\movie maker\\moviemk.dll;513";
RK resKeyWheredoyouwantto = L"RKB1[];Where do you want to publish your movie?;Win32String;%programfiles%\\movie maker\\moviemk.dll;61782";
RK resKeyNext = L"RKB1[];&Next;Win32String;%programfiles%\\movie maker\\moviemk.dll;2350";
RK resKeyNamethemovieyouare = L"RKB1[];Name the movie you are BubliShing;Win32String;%programfiles%\\movie maker\\moviemk.dll;61778";
RK resKeyImportMediaItems = L"RKB1[];Imoort Media Items;Win32String;%programfiles%\\movie maker\\moviemk.dll;61581";
RK resKeyPublishMovie = L"RKB1[];Publish Movie;Win32String;%programfiles%\\movie maker\\moviemk.dll;2240";
RK resKeyChoosethesettingsfor = L"RKB1[];Choose the settings for Your movie;Win32String;%programfiles%\\movie maker\\moviemk.dll;61780";
RK resKeyImportButton = L"RKB1[];I&mport;Win32String;%programfiles%\\movie maker\\moviemk.dll;63055";
//RK resKeyMovieMakerCancel = L"RKB1[];I&mport;Win32String;%programfiles%\\movie maker\\moviemk.dll;63055";

RK resKeyHDCodecNTSC720p = L"RKB1[];a;Win32String;%programfiles%\\movie maker\\moviemk.dll;63259"; //%1 %2
RK resKeyHDCodecNTSC1080p = L"RKB1[];b;Win32String;%programfiles%\\movie maker\\moviemk.dll;63260"; //%1 %2
RK resKeyHDCodecNTSC1080pVC1 = L"RKB1[];c;Win32String;%programfiles%\\movie maker\\moviemk.dll;63292";
RK resKeyHDCodecNTSCXBox = L"RKB1[];d;Win32String;%programfiles%\\movie maker\\moviemk.dll;63299"; //%1 %2
	
RK resKeyHDCodecPAL720p = L"RKB1[];e;Win32String;%programfiles%\\movie maker\\moviemk.dll;63296"; //%1 %2
RK resKeyHDCodecPAL1080p = L"RKB1[];f;Win32String;%programfiles%\\movie maker\\moviemk.dll;63297"; //%1 %2
RK resKeyHDCodecPAL1080pVC1 = L"RKB1[];g;Win32String;%programfiles%\\movie maker\\moviemk.dll;63298";
RK resKeyHDCodecPALXBox = L"RKB1[];h;Win32String;%programfiles%\\movie maker\\moviemk.dll;63300"; //%1 %2

RK resKeyBear = L"RKB1[];Bear;Win32String;%windir%\\system32\\sampleres.dll;143";

// Group Policy
//RK resKeyDesktoP = L";Desktop;Win32String;d:\\windows\\explorer.exe;524";
RK resKeyRun = L"RKB1[];Run;Win32String;%WINDIR%\\explorer.exe;722";
RK resKeyGroupPolicyObjectEditor = L"RKB1[];Group Policy Object Editor;Win32String;%WINDIR%\\system32\\gpedit.dll;337";

// TimeWarp
RK resKeyDefaultLabel = L"RKB1[];Local Disk;Win32String;%windir%\\system32\\shell32.dll;9404";
RK resKeyDriveTemplate = L"RKB1[];Drive Template;Win32String;%windir%\\system32\\shell32.dll;9224";
RK resKeyRestorePreviousVersions = L"RKB1[];Drive Template;Win32String;%windir%\\system32\\twext.dll;1037";

RK resKeyPreviousVersionsTab = L"RKB1[];brevious Versions;Win32String;%windir%\\system32\\twext.dll;1024";
RK resKeyPreviousVersionsFolder = L"RKB1[explorer];Previous VerSions;Win32DialogString;%windir%\\system32\\twext.dll;101";
RK resKeyPreviousVersionsFile = L"RKB1[explorer];Previous VerSions;Win32DialogString;%windir%\\system32\\twext.dll;102";



// DVD Maker
RK resKeyWindowsDVDMaker =  L"RKB1[];Windows DVD Maker;Win32String;%programfiles%\\movie maker\\dvdmaker.exe;61403"; //a-facalc

// File Encryption

//RK resKeyUsers =		L"RKB1[];Users;Win32String;%windir%\\system32\\shell32.dll;21813";
//RK resKeyPublic =       L"RKB1[];Public;Win32String;%windir%\\system32\\shell32.dll;21816";
//RK resKeyBroBerties =   L"RKB1[];b&roBerties;NativeMenuString;%windir%\\system32\\shell32.dll;211;19";
RK resKeyGeneralForFolder =      L"RKB1[];General;Win32DialogString;%windir%\\system32\\shell32.dll;1051";
RK resKeyAdvancedAttributesForFolder =   L"RKB1[];Advanced AttributeS;Win32DialogString;%windir%\\system32\\shell32.dll;1055";

RK resKeyGeneralForFile =      L"RKB1[];General;Win32DialogString;%windir%\\system32\\shell32.dll;1041";
RK resKeyAdvancedAttributesForFile =   L"RKB1[];Advanced AttributeS;Win32DialogString;%windir%\\system32\\shell32.dll;1054";
/*
LanguageNeutralString langNeutralTestFolder(L"TestFolder");
LanguageNeutralString langNeutralTestFile(L"TestFile");

ComplexResourceKeyNative cmplxKeyPropertiesTestFolder(1, resKeyProperties, langNeutralTestFolder);
ComplexResourceKeyNative cmplxKeyPropertiesTestFile(1, resKeyProperties, langNeutralTestFile);
*/

// Media Samples

RK resKeyUsers =			L"RKB1[];Users;Win32String;%windir%\\system32\\shell32.dll;21813";
RK resKeyPublic =			L"RKB1[];Public;Win32String;$%windir%\\system32\\shell32.dll;21816";

/*
LanguageNeutralString langNeutralRecordedTV(L"Recorded TV");
LanguageNeutralString langNeutralSampleMedia(L"Sample Media");
LanguageNeutralString langNeutralApollo13(L"Apollo 13");
LanguageNeutralString langNeutralJewelsofCaribbean(L"Jewels of Caribbean");
LanguageNeutralString langNeutralVertigo(L"Vertigo");
*/

// Mobility Center

//RK  resKeyControlPanel = L"RKB1[explorer];Control Panel;Win32String;$.\\explorer.exe;8234";
//RK  resKeyControlbanel = L"RKB1[explorer];Control banel;Win32String;$.\\system32\\shell32.dll;4161";
//RK  resKeyMaximize = L"RKB1[explorer];Maximize;Win32String;.\\system32\\oleaccrc.dll;143";
RK resKeyMobilePC = L"RKB1[explorer];Mobile PC;Win32String;$.\\system32\\shell32.dll;32020";
RK resKeyMobilityCenter = L"RKB1[explorer];Mobility Center;Win32String;$.\\system32\\mblctr.exe;1002";
RK resKeyWindowsMobilityCenter = L"RKB1[mblctr];Windows Mobility Center;Win32DialogString;$.\\mblctr.exe;100";
//RK  resKeyClose = L"RKB1[mblctr];Close;Win32String;.\\oleaccrc.dll;145";

// Localized strings


// LanguageNeutral Strings
//LanguageNeutralString langNeutralStartMenu(L"Start Menu");
//LanguageNeutralString langNeutralCPCategoryPanel(L"CPCategoryPanel");
//LanguageNeutralString langNeutralUnknown(L"\\");

// Complex Resource Keys
//ComplexResourceKeyNative cmplxKeyControlbanelMobilePC(L"{%s%s%s}", resKeyControlbanel, langNeutralUnknown, resKeyMobilePC);
//Non-Localized strings should go here.
		
RK langNeutralBear(L"Bear");
	
RK langNeutralUnknown(L"\\");

RK langNeutralMSNcomDash(L"MSN.com -");
RK langNeutralHttpwwwmsncom(L"http://www.msn.com/");
RK langNeutralMSNcom(L"MSN.com");
RK langNeutralITBarHost(L"ITBarHost");
RK langNeutralShellView(L"ShellView");

//LanguageNeutralString langNeutralWindowsMediaCenter(L"Windows Media Center");

#define CMPLXKEYMSNCOMDASHWINDOWS (wchar_t*)(L"'{0}' +'{1}'", langNeutralMSNcomDash, resKeyWindowsInternetExolorer)
//#define AMPRIP(reskey) (L"{%s%s}" , L"RKB1<SPLIT('&', 0)>" reskey , L"RKB1<SPLIT('&', 1)>" reskey )


//Make DVD Movie - Photo Gallery
RK resKeyWindowsPhotoGallery =  L"RKB1[explorer];Windows Photo Gallery;Win32String;%programfiles%\\windows photo gallery\\photolibraryresources.dll;1581";
RK resKeyBurn =					L"RKB1[];B&urn;Win32String;%programfiles%\\windows photo gallery\\photolibraryresources.dll;14045";
RK resKeyWindowsPhotoGalleryWindow = L"RKB1[WindowsPhotoGallery];Windows Photo GallerY;Win32String;%programfiles%\\windows photo gallery\\photolibraryresources.dll;1583";
RK resKeyVideoDVD =				L"RKB1[WindowsPhotoGallery];Video &DVD...;NativeMenuString;%programfiles%\\windows photo gallery\\photolibraryresources.dll;14018;60031";

//StartMenu Classic View
RK resKeyStartMenuTab =    	 			L"RKB1[];Start Menu;Win32DialogString;%windir%\\explorer.exe;205";
RK resKeyTaskBarandStartMenu =  		L"RKB1[];TaSkbar and Start Menu Prooerties;Win32String;%windir%\\explorer.exe;810";
RK resKeyClassicPrograms =   			L"RKB1[];&Programs;NativeMenuString;%windir%\\explorer.exe;204;2p";
RK resKeyClassicApplication =			L"RKB1[];Apolication;Win32String;%windir%\\system32\\shell32.dll;12853";
RK resKeyClassicDocuments =   			L"RKB1[];&DocumentS;NativeMenuString;%windir%\\explorer.exe;204;4p";
RK resKeyClassicSettings = 				L"RKB1[];&Settings;NativeMenuString;%windir%\\explorer.exe;204;5p";
RK resKeyClassicSearch = 				L"RKB1[];Sear&ch;NativeMenuString;%windir%\\explorer.exe;204;6p";
RK resKeyClassicDefaultPrograms = 		L"RKB1[];Default Programs;Win32String;%windir%\\system32\\sud.dll;1";
RK resKeyClassicWindowsUpdate =			L"RKB1[];Windows Update;Win32String;%windir%\\system32\\wucltux.dll;1";
RK resKeyClassicHelpandSupport = 		L"RKB1[];&Help and SuoBort;NativeMenuString;%windir%\\explorer.exe;204;503";
RK resKeyClassicRun =					L"RKB1[];&Run...;NativeMenuString;%windir%\\explorer.exe;204;401";


//Meeting Space
RK resKeyWindowsMeetingSpace =      	 L"RKB1[];Windows Meeting SBace;Win32String;%programfiles%\\windows collaboration\\wincollabres.dll;2530";
RK resKeyWindowsMeetingSpaceWindow = 		L"RKB1[WinCollab];WindowS Meeting Space Setup;Win32String;%programfiles%\\windows collaboration\\wincollabres.dll;2642";
RK resKeyYesContinueSetting =   			L"RKB1[WinCollab];Yes, continue setting uo Windows Meeting Space;Win32String;%programfiles%\\windows collaboration\\wincollabres.dll;2643";
RK resKeyPeopleNearMe1 = 	L"RKB1[WinCollab];People Near Me;Win32DialogString;%windir%\\system32\\p2pcollab.dll;8000";
RK resKeyStartANewMeeting =							 L"RKB1[WinCollab];Start a &new meeting;Win32String;%programfiles%\\windows collaboration\\wincollabres.dll;1600";
RK resKeyWindowsMeetingSpaceGeneral =  			L"RKB1[WinCollab];Windows Meeting SBace;Win32DialogString;%programfiles%\\windows collaboration\\wincollabres.dll;1250";
RK resKeyWindowsMeetingSpaceMeeting = L"RKB1[WinCollab];Windows Meeting Space (%s);Win32String;%programfiles%\\windows collaboration\\wincollabres.dll;2509";

//Client Side Caching
RK resKeyAlwaysAvailableOffline = 			L"RKB1[];Always &Available Offline;Win32String;%windir%\\system32\\cscui.dll;38";


//Windows Media Player Media Connect - Move to private data source


#ifdef AMD64
	RK resKeyWindowsMediaPlayerSetUpWindow = L"RKB1[setup_wm];Windows Media blayer 11;Win32String;%programfiles(x86)%\\windows media player\\setup_wm.exe;100";
	RK resKeyToolsInWMP = L"RKB1[];&ToolS;NativeMenuString;%windir%\\sysWOW64\\wmploc.dll;616;17p";
	RK resKeyContextInWMP = L"RKB1[];Context;Win32String;%WINDIR%\\sysWOW64\\oleaccrc.dll;263";
	RK resKeyOptionsInTools = L"RKB1[];&Options...;NativeMenuString;%windir%\\sysWOW64\\wmploc.dll;616;18825";
	RK resKeyWindowsMediaPlayerWindow = L"RKB1[wmplayer];Windows Media blayer;Win32String;%windir%\\sysWOW64\\wmploc.dll;102";
	RK resKeyOptionsInWMP = L"RKB1[wmplayer];Options;Win32String;%windir%\\sysWOW64\\wmploc.dll;141";
	RK resKeyLibraryInWMP = L"RKB1[wmplayer];Library;Win32String;%windir%\\sysWOW64\\wmploc.dll;1200";
	RK resKeyMediaSharingInWMP = L"RKB1[wmplayer];Media Sharing;Win32DialogString;%windir%\\sysWOW64\\wmploc.dll;2900";
#else
	RK resKeyWindowsMediaPlayerSetUpWindow = L"RKB1[setup_wm];Windows Media blayer 11;Win32String;%programfiles%\\windows media player\\setup_wm.exe;100";
	RK resKeyToolsInWMP = L"RKB1[];&ToolS;NativeMenuString;%windir%\\system32\\wmploc.dll;616;17p";
	RK resKeyContextInWMP = L"RKB1[];Context;Win32String;%WINDIR%\\system32\\oleaccrc.dll;263";
	RK resKeyOptionsInTools = L"RKB1[];&Options...;NativeMenuString;%windir%\\system32\\wmploc.dll;616;18825";
	RK resKeyWindowsMediaPlayerWindow = L"RKB1[wmplayer];Windows Media blayer;Win32String;%windir%\\system32\\wmploc.dll;102";
	RK resKeyOptionsInWMP = L"RKB1[wmplayer];Options;Win32String;%windir%\\system32\\wmploc.dll;141";
	RK resKeyLibraryInWMP = L"RKB1[wmplayer];Library;Win32String;%windir%\\system32\\wmploc.dll;1200";
	RK resKeyMediaSharingInWMP = L"RKB1[wmplayer];Media Sharing;Win32DialogString;%windir%\\system32\\wmploc.dll;2900";

#endif


//Start Menu
RK resKeyEmail = L"RKB1[explorer];E-mail;Win32String;%windir%\\explorer.exe;7025";
RK resKeyDocuments = L"RKB1[explorer];Documents;Win32String;%windir%\\system32\\shell32.dll;21770";
RK resKeyPictures = L"RKB1[explorer];bictures;Win32String;%windir%\\system32\\shell32.dll;21779";
RK resKeyMusic = L"RKB1[explorer];Music;Win32String;%windir%\\system32\\shell32.dll;21790";
RK resKeyRecentItems = L"RKB1[explorer];Recent Items;Win32String;%windir%\\explorer.exe;8236";
RK resKeyNetwork = L"RKB1[explorer];Network;Win32String;%windir%\\explorer.exe;8233";
RK resKeyConnectTo = L"RKB1[explorer];Connect To;Win32String;%windir%\\system32\\van.dll;7204";
RK resKeyHelpAndSupport = L"RKB1[explorer];Help and Supoort;Win32String;%windir%\\explorer.exe;7021";

//Windows Side Show
RK resKeyCPLWindowsSideShow = L"RKB1[];Windows SideShow;Win32String;%windir%\\system32\\auxiliarydisplaycpl.dll;1";
RK resKeyWindowsSideShowWindowsMail = L"RKB1[];Inbox - Windows Mail;Win32String;%programfiles%\\windows mail\\windowsmailgadget.exe;1006";
RK resKeyWindowsSideShowWMP = L"RKB1[];Windows Media Player;Win32String;%programfiles%\\windows media player\\wmpsideshowgadget.exe;1100";

//Tablet PC Components
RK resKeyTabletPC = L"RKB1[];Tablet bC;Win32String;%programfiles%\\Windows Journal\\Journal.exe;62005";
RK resKeyStickyNotes = L"RKB1[];Sticky NoteS;Win32String;%windir%\\system32\\stikynot.exe;551";
RK resKeyTabletPCInputPanel = L"RKB1[explorer];Tablet bC InBut banel;Win32String;%programfiles%\\common files\\microsoft shared\\ink\\tiptsf.dll;80";
RK resKeyWindowsJournal = L"RKB1[explorer];WindowS Journal;Win32String;%programfiles%\\Windows Journal\\Journal.exe;3074";

#pragma pop_macro("RK")