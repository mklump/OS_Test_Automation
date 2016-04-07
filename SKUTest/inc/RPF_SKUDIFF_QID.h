//////////////////////////////////////////////////////////////
//                 
//  This file defines RPF QueryIDs.
//  For use in testing SKU Differentiation of Microsoft Windows
//	
//  Copyright (C) Microsoft Corporation, 2008. For internal use only.
//
//////////////////////////////////////////////////////////////

#pragma region History
// a-jomul: Cleaned up an existing file in late 2007,
// Removed duplicates, renamed items, 
// replaced many with parameterized macros, to reduce breaking the H-scroll
// Jan 2008, major cleanup, more parameterized macros
// If the macros are too much, they can be expanded in a future checkin.
// TODO: I think [VisibleOnly] is useless for us, consider purging it
// TODO: Standard dialog OK/Cancel?, problem is text resource might vary?, but always Control ID 1 and 2?
#pragma endregion History

#pragma region Templates
// macros/templates for common QID formats
#define MENU_CLASS								L";AccessibleName = '{0}' && ClassName => '#32768' && Role = 'popup menu'"
#define DIALOG_CLASS							L";Name => '{0}' && ClassName => '#32770'"
#define EXPLORER_CLASS							L";Name => '{0}' && ClassName => 'CabinetWClass'"

#define CLOSE_WINDOW(ResKey, WClass)			L";Name => '{0}' && ClassName => '" WClass L"';Role = 'title bar' && ClassName = '" WClass L"';Name = '{1}' && Role = 'push button'", ResKey, resKeyClose
#define CLOSE_DIALOG(ResKey)					CLOSE_WINDOW(ResKey, L"#32770")
#define CLOSE_EXPLORER(ResKey)					CLOSE_WINDOW(ResKey, L"CabinetWClass")

#define STARTMENU_ITEM(reskey) 					L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, reskey
#define STARTMENU_FOLDER(reskey)				L";Name => '{0}' && ClassName => 'DV2ControlHost';Role = 'outline' && ClassName = 'SysTreeView32';[VisibleOnly]Name = '{1}' && Role = 'outline item'", resKeyStartMenu, reskey
#pragma endregion Templates

// Basic QIDS
#define WINDOW_DESKTOP							L";AccessibleName = '{0}' && ClassName => '#32769';[VisibleOnly]Name = '{0}' && Role = 'window'", resKeyDesktop
#define START_BUTTON							L";Name = '{0}' && ClassName = 'Button';Name = '{1}' && Role = 'push button'", resKeyStartWindow, resKeyStart

//Items on the Start menu
#define STARTMENU_ALLPROGRAMS					L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyStartMenuAllPrograms
#define STARTMENU_COMPUTER						STARTMENU_ITEM(resKeyComputer) 
#define STARTMENU_GAMES							STARTMENU_ITEM(resKeyGames)

#define STARTMENU_CONTROL_PANEL					STARTMENU_ITEM(resKeyStart_ControlPanel)
#define STARTMENU_INTERNET_EXPLORER             STARTMENU_ITEM(resKeyInternet)
#define STARTMENU_PROJECTOR						STARTMENU_ITEM(resKeyConnecttoaNetworkProjector) 
#define STARTMENU_GAMES_EXPLORER				STARTMENU_ITEM(resKeyGamesExplorer) 
#define STARTMENU_WINDOWS_FAX_AND_SCAN          STARTMENU_ITEM(resKeyWindowsFaxandScan) 
#define STARTMENU_MORE                          STARTMENU_ITEM(resKeyMore) 
#define STARTMENU_WINDOWS_MOVIE_MAKER           STARTMENU_ITEM(resKeyWindowsMovieMaker) 
#define STARTMENU_WINDOWS_MEDIA_PLAYER          STARTMENU_ITEM(resKeyWindowsMediaPlayer)
#define STARTMENU_BACKUP_RESTORE_CENTER         STARTMENU_ITEM(resKeyBackupandRestoreCenter) 
#define STARTMENU_BACKUP_STATUS_CONFIGURATION	STARTMENU_ITEM(resKeyBackupStatusandConfiguration) 
#define STARTMENU_WINDOWS_MOVIE_MAKER			STARTMENU_ITEM(resKeyWindowsMovieMaker) 
#define STARTMENU_WELCOME_CENTER				STARTMENU_ITEM(resKeyWelcomeCenter) 

#define STARTMENU_WINDOWS_DVD_MAKER				STARTMENU_ITEM(resKeyWindowsDVDMaker) // a-facalc

// Never, EVER localized? - not Pseudo-locd, so maybe.
#define STARTMENU_MEDIACENTER					L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = 'Windows Media Center' && Role = 'menu item'", resKeyStartMenu

// Classic items
#define CLASSIC_STARTMENU_CONTROL_PANEL			STARTMENU_ITEM(resKeyClassicStart_ControlPanel)

/// All Programs sub-folders
#define STARTMENU_ACCESSORIES					L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Role = 'outline' && ClassName = 'SysTreeView32';Name = '{1}' && Role = 'outline item'", resKeyStartMenu, resKeyStartMenuAccessories

#define ALL_PROGRAMS_MAINTENANCE                STARTMENU_FOLDER(resKeyMaintenance) 
#define ALL_PROGRAMS_ACCESSORIES				STARTMENU_FOLDER(resKeyStartMenuAccessories) 
#define ALL_PROGRAMS_ACCESSORIES_SYSTOOLS       STARTMENU_FOLDER(resKeySystemTools) 
#define ALL_PROGRAMS_GAMES						STARTMENU_FOLDER(resKeyAllProgramsGames) 

// Welcome Center
#define WELCOMECENTERITEM(resKey)				EXPLORER_CLASS L";[VisibleOnly]Role = 'list' && ClassName = 'SysListView32';Name = '{1}' && Role = 'list item'", resKeyWelcomeCenter, resKey
#define WC_COMP_DETAILS							WELCOMECENTERITEM(resKeyWCViewComputerDetails)
#define WC_ADD_USERS							WELCOMECENTERITEM(resKeyWCAddNewUsers)
#define WC_EASY_TRANSFER						WELCOMECENTERITEM(resKeyWCTransferFilesSettings)
#define WC_CONNECT_INTERNET						WELCOMECENTERITEM(resKeyWCConnectInternet)
#define WC_PERSONALIZE							WELCOMECENTERITEM(resKeyWCPersonalizeWindows)
#define WC_DEMOS								WELCOMECENTERITEM(resKeyWCWindowsVistaDemos)
#define WC_EASE_ACCESS							WELCOMECENTERITEM(resKeyWCEaseAccessCenter)
#define WC_BACKUP_RESTORE						WELCOMECENTERITEM(resKeyWCBackupRestoreCenter)
#define WC_CONTROL_PANEL						WELCOMECENTERITEM(resKeyWCControlPanel)
#define WC_BASICS								WELCOMECENTERITEM(resKeyWCWindowsBasics)
#define WC_UPGRADE								WELCOMECENTERITEM(resKeyWCWindowsAnytimeUpgrade)
#define WC_MCE									WELCOMECENTERITEM(resKeyWCWindowsMediaCenter)
#define WC_ULTIMATE_EXTRAS						WELCOMECENTERITEM(resKeyWCWindowsUltimateExtras)
#define WC_ADD_PRINTER							WELCOMECENTERITEM(resKeyWCAddPrinter)
#define WC_WHATS_NEW							WELCOMECENTERITEM(resKeyWCWhatsNewWindows)
#define WC_REGISTER_WINDOWS						WELCOMECENTERITEM(resKeyWCRegisterWindowsOnline)

//'Run' dialog (Start->Run)
#define RUN_DIALOG								DIALOG_CLASS L";ControlId = '1001';[VisibleOnly]Role = 'editable text'", resKeyRun
#define RUN_DIALOG_OK_BTN						DIALOG_CLASS L";ControlId = '1';[VisibleOnly]Role = 'push button'", resKeyRun
#define CLOSE_RUN_WINDOW						CLOSE_DIALOG(resKeyRun)

//Explorer window UI
#define EXPLORER_CLOSEBUTTON                L";ClassName => 'CabinetWClass';Name = '{0}' && Role = 'push button'", resKeyExplorerClose
#define FILEPROPERTIES_OKBUTTON             L";ClassName => '#32770';ControlId = '1';Name = '{0}' && Role = 'push button'" , resKeyFilePropertyOKButton

///////////////////////////////////////////////////////////////////////////////////////////////
// Feature area Specific constants
///////////////////////////////////////////////////////////////////////////////////////////////

//Branding

//#pragma deprecated(SYS_COMP_PROPERTIES)
#define SYS_COMP_PROPERTIES                     MENU_CLASS L";[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyContextMenu, resKeyProperties
//#define CMENU_PROPERTIES                     MENU_CLASS L";[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyContextMenu, resKeyProperties



#define CPL_WC_CLOSE_BTN                        CLOSE_WINDOW(resKeyWelcomeCenter,L"CabinetWClass")

// System Properties tabbed dialog QIDs shared by Remote Desktop and Domain Join
#define SYSTEM_PROPERTIES_OK_BTN                DIALOG_CLASS L";[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeySystemPropertiesDialogTitle, resKeySystemPropertiesOK    
#define SYSTEM_PROPERTIES_CANCEL_BTN            DIALOG_CLASS L";[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeySystemPropertiesDialogTitle, resKeySystemPropertiesCancel    
#define CPL_SYSTEM_CHANGE_SETTINGS_BTN          EXPLORER_CLASS L";Role = 'client' && ClassName = 'DirectUIHWND';Name = '{1}' && Role = 'link'", resKeySystem, resKeyDomainChange
#define SYSTEM_PROPERTIES_CLOSE_BTN             CLOSE_DIALOG(resKeySystemPropertiesDialogTitle)
#define CPL_SYSTEM_CLOSE_BTN                    CLOSE_WINDOW(resKeySystem,L"CabinetWClass")

#define CPL_REMOTE_PAGE_TAB						L";Name => '{0}' && ClassName => '#32770';[VisibleOnly]Role = 'page tab list' && ClassName = 'SysTabControl32';[VisibleOnly]Name = '{1}' && Role = 'page tab'", resKeySystemPropertiesDialogTitle, resKeyRemoteTabDomain

//Remote Desktop																																								   resKeyRemoteSettings						
#define CPL_SYSTEM_REMOTE_NAV_LINK              EXPLORER_CLASS L";[VisibleOnly]Name = '{1}' && Role = 'link'", resKeySystem, resKeyRemoteSettings//;Name = '{1}' && Role = 'window'
#define CPL_REMOTE_ALLOWCONNTO_RADIO            DIALOG_CLASS L";ControlId = '601';[VisibleOnly]Name = '{1}' && Role = 'radio button'", resKeyRemoteTabDomain, resKeyAllowconnectionsfrom
#define CPL_REMOTE_DONTALLOW_RADIO              DIALOG_CLASS L";ControlId = '601';[VisibleOnly]Name = '{1}' && Role = 'radio button'", resKeyRemoteTabDomain, resKeyDontallowconnectionsto
#define REMOTE_DESKTOP_GROUPING                 DIALOG_CLASS L";ControlId = '9005';[VisibleOnly]Name = '{1}' && Role = 'grouping'", resKeyRemoteTabDomain, resKeyRemoteDesktop

//DomainJoin
#define COMPUTER_NAME_CHANGE_NAME               DIALOG_CLASS L";ControlId = '115';[VisibleOnly, EnabledOnly]Name = '{1}' && Role = 'push button'", resKeyComputerNameTab, resKeyComputerNameChange
#define COMPUTER_NAME_CHANGE_NAME_CANCEL        DIALOG_CLASS L";[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyComputerNameChanges, resKeyComputerNameCancel //;ControlId = '2'
#define COMPUTER_NAME_CHANGE_DOMAIN             DIALOG_CLASS L";ControlId = '115';[VisibleOnly, EnabledOnly]Name = '{1}' && Role = 'push button'", resKeyComputerNameDomainTab, resKeyComputerNameDomainChange
#define COMPUTER_NAME_CHANGE_DOMAIN_CANCEL      DIALOG_CLASS L";[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyComputerNameDomainChanges, resKeyComputerNameDomainCancel //;ControlId = '2'
#define COMPUTER_NAME_DOMAIN_RADIO              DIALOG_CLASS L";ControlId = '1008';[VisibleOnly]Name = '{1}' && Role = 'radio button'", resKeyComputerNameDomainChanges,resKeyDomainRadio


//MUI
#define MUI_KEYBOARDSLANGUAGES_TAB              DIALOG_CLASS L";ControlId = '12320';[VisibleOnly]Name = '{1}' && Role = 'page tab'", resKeyRegionalLanguageOptions, resKeyKeyboardsLanguages
#define MUI_MANAGE_LANGUAGES_BTN                DIALOG_CLASS L";ControlId = '1182';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyKeyboardsLanguages, resKeyManageLanguages 
#define MUI_KEYBRD_LANGUAGES_OK_BTN             DIALOG_CLASS L";ControlId = '1';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyRegionalLanguageOptions, resKeyOk
//BitLocker
//Media Center
//Network Projector
#define CLOSE_PROJECTOR							CLOSE_WINDOW(resKeyConnecttoaNetwork,L"NativeHWNDHost")
//#define CLOSE_PROJECTOR						L";Name => '{0}' && ClassName => 'NativeHWNDHost';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyConnecttoaNetwork, resKeyClose
#define CANCEL_PROJECTOR						L";Name => '{0}' && ClassName => 'NativeHWNDHost';[VisibleOnly]Name = '{1}' && Role = 'client';[VisibleOnly]Name = '{2}' && Role = 'push button'", resKeyConnecttoaNetwork, resKeyHowdoYouwantto, resKeyCancel
#define NETPROJ_ALLOW_FIREWALL_ACCESS			DIALOG_CLASS L";[VisibleOnly]Name = '{0}' && Role = 'pane';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyPermisSiontoConnectto, resKeyNetProjYes
#define NETPROJ_DENY_FIREWALL_ACCESS			DIALOG_CLASS L";[VisibleOnly]Name = '{0}' && Role = 'pane';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyPermisSiontoConnectto, resKeyNetProjNo

// Parental Controls
#define CPL_PARENTAL_CONTROLS_CLOSE_BTN         CLOSE_WINDOW(resKeyParentalControls,L"CabinetWClass")

#define GAMES_PARENTAL_CONTROLS_BTN             EXPLORER_CLASS L";Name = '{1}' && Role = 'tool bar';[VisibleOnly]Name = '{2}' && Role = 'push button'", resKeyGames, resKeyCommandModule, resKeyParentalControls1
#define GAMES_OVERFLOW_BTN						EXPLORER_CLASS L";[VisibleOnly]Name = '{1}' && Role = 'tool bar';[VisibleOnly]Name = '{2}' && Role = 'drop down button'", resKeyGames, resKeyCommandModule, resKeyOverflowMenu
#define GAMES_PARENTAL_CONTROLS_POPUP           MENU_CLASS L";[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyContext, resKeyParentalControls1
//#define GAMES_PARENTAL_CONTROLS_POPUP           L";AccessibleName => '{0}' && ClassName => '#32768' && Role = 'popup menu';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyContext, resKeyParentalControls1

#define GAMES_CLOSE_BTN                         CLOSE_WINDOW(resKeyGames,L"CabinetWClass")
#define IE_TOOLBAR                              L";Name => '{0}' && ClassName => 'IEFrame';Name = '{1}' && Role = 'client';[VisibleOnly]Name = '{2}' && Role = 'pane'", CMPLXKEYMSNCOMDASHWINDOWS, langNeutralHttpwwwmsncom, langNeutralMSNcom
#define IE_TOOLS_MENU_BAR                       L";Name => '{0}' && ClassName => 'InternetToolbarHost';Name = '{1}' && Role = 'menu bar';[VisibleOnly]Name = '{2}' && Role = 'menu item'", langNeutralITBarHost, resKeyApplication, resKeyTools
#define IE_TOOLS_INTERNET_OPTIONS               MENU_CLASS L";[VisibleOnly]Name = '{0}' && Role = 'menu item'", resKeyInternetOptions, resKeyContext
//#define IE_TOOLS_INTERNET_OPTIONS               L";AccessibleName = '{1}' && ClassName => '#32768' && Role = 'popup menu';[VisibleOnly]Name = '{0}' && Role = 'menu item'", resKeyInternetOptions, resKeyContext
#define IE_TOOLS_CONTENT_TAB                    DIALOG_CLASS L";Role = 'page tab list' && ClassName = 'SysTabControl32';[VisibleOnly]Name = '{1}' && Role = 'page tab'", resKeyInternetPropertiesTab, resKeyContent //wildcard
#define IE_TOOLS_PARENTAL_CONTROLS_BTN          DIALOG_CLASS L";ControlId = '5802';Name = '{1}' && [VisibleOnly]Role = 'push button'", resKeyContent, resKeyIEParentalControlsButton
#define IE_TOOLS_INTERNET_OPTIONS_CLOSE         CLOSE_DIALOG(resKeyInternetPropertiesTab)

//Windows SideShow
#define CPL_SIDESHOW_CLOSE                      CLOSE_WINDOW(resKeyWindowsSideShow,L"CabinetWClass")

// Games
#define GAMES_MAHJONG_TITANS                    EXPLORER_CLASS L";[VisibleOnly]Role = 'list' && ClassName = 'SysListView32';Name = '{1}' && Role = 'list item'", resKeyGames, resKeyMahjongTitans
#define GAMES_CHESS_TITANS                      EXPLORER_CLASS L";[VisibleOnly]Role = 'list' && ClassName = 'SysListView32';Name = '{1}' && Role = 'list item'", resKeyGames, resKeyChessTitans
#define GAMES_FREECELL                          EXPLORER_CLASS L";[VisibleOnly]Role = 'list' && ClassName = 'SysListView32';Name = '{1}' && Role = 'list item'", resKeyGames, resKeyFreeCell
#define GAMES_HEARTS                            EXPLORER_CLASS L";[VisibleOnly]Role = 'list' && ClassName = 'SysListView32';Name = '{1}' && Role = 'list item'", resKeyGames, resKeyHearts
#define GAMES_UPDATE_AND_OPTIONS                DIALOG_CLASS L";Name = '{0}' && Role = 'pane';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeySetupGameUpdatesAndOptions, resKeyOk
#define GAMES_SELECT_DIFFICULTY                 DIALOG_CLASS L";Role = 'title bar' && ClassName = '#32770';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyGamesSelectDifficulty, resKeyClose
#define WINDOWS_FEATURES_GAMES                  L";Name => '{0}' && ClassName => 'NativeHWNDHost';[VisibleOnly]Role = 'outline' && ClassName = 'SysTreeView32';Name = '{1}' && Role = 'outline item'", resKeyWindowsFeatures, resKeyGames
#define WINDOWS_FEATURES_MAHJONG_TITANS         L";Name => '{0}' && ClassName => 'NativeHWNDHost';[VisibleOnly]Role = 'outline' && ClassName = 'SysTreeView32';Name = '{1}' && Role = 'outline item'", resKeyWindowsFeatures, resKeyMahjongTitans
#define WINDOWS_FEATURES_CHESS_TITANS           L";Name => '{0}' && ClassName => 'NativeHWNDHost';[VisibleOnly]Role = 'outline' && ClassName = 'SysTreeView32';Name = '{1}' && Role = 'outline item'", resKeyWindowsFeatures, resKeyChessTitans
#define MAHJONG_TITANS_CLOSE                    CLOSE_WINDOW(resKeyMahjongTitans,L"Mahjong Titans")
#define CHESS_TITANS_CLOSE                      CLOSE_WINDOW(resKeyChessTitans,L"ChessWindowClass")
#define FREECELL_CLOSE                          CLOSE_WINDOW(resKeyFreeCell,L"FreeCell")
#define HEARTS_CLOSE                            CLOSE_WINDOW(resKeyHearts,L"Hearts")
#define WINDOWS_FEATURES_CLOSE                  CLOSE_WINDOW(resKeyWindowsFeatures,L"NativeHWNDHost")

// DWM
#define DWM_FLIP3D								L";Name => '{0}' && Role = 'list'", resKeyFlip3D
#define CPL_WIN_COLOR_AND_APPEARANCE            EXPLORER_CLASS L";Name = '{0}' && Role = 'client';[VisibleOnly]Name = '{1}' && Role = 'link'", resKeyPersonalization, resKeyWinColorAndAppearanceLink
#define CPL_ENABLE_TRANSPARENT_GLASS            EXPLORER_CLASS L";Name = '{1}' && Role = 'check box';[VisibleOnly]Name = '{1}' && Role = 'check box'", resKeyWinColorAndAppearanceTitle, resKeyEnableTransparentGlass
#define CPL_OPEN_CLASSIC_APPEARANCE             EXPLORER_CLASS L";Role = 'window' && ClassName = 'DirectUIHWND';[VisibleOnly]Name = '{1}' && Role = 'link'", resKeyWinColorAndAppearanceTitle, resKeyOpenClassicAppearance
#define WINDOWS_VISTA_AERO_COLOR_SCHEME         L";Name = '{0}' && ClassName = '#32770';[VisibleOnly]Name = '{1}' && Role = 'list';Name = '{2}' && Role = 'list item'", resKeyAppearance, resKeyColorScheme, resKeyWindowsVistaAero
#define WINDOWS_VISTA_BASIC_COLOR_SCHEME        L";Name = '{0}' && ClassName = '#32770';[VisibleOnly]Name = '{1}' && Role = 'list';Name = '{2}' && Role = 'list item'", resKeyAppearance, resKeyColorScheme, resKeyWindowsVistaBasic
#define WINDOWS_SWITCHER                        L";AccessibleName = 'Quick Launch' && ClassName => 'ToolbarWindow32';Name = 'Quick Launch' && Role = 'tool bar';[VisibleOnly]Name = '{0}' && Role = 'push button'", resKeyWindowSwitcher
#define CPL_CHANGE_YOUR_COLOR_SCHEME_CLOSE      CLOSE_WINDOW(resKeyWinColorAndAppearanceTitle,L"CabinetWClass")
#define CLASSIC_APPEARANCE_CLOSE                CLOSE_DIALOG(resKeyClassicAppearanceSettings)
#define CPL_PERSONALIZATION_CLOSE               CLOSE_WINDOW(resKeyPersonalization,L"CabinetWClass")

// RAM
#define RAM_IN_MB                               EXPLORER_CLASS L";Name = '{1}' && Role = 'window';[VisibleOnly]Name => 'MB' && Role = 'text'", resKeySystem, resKeyHelBIcon
// Fax and Scan
// FUS
#define SWITCH_USER                             L";AccessibleName = '{1}' && ClassName => 'ToolbarWindow32' && Role = 'popup menu';[VisibleOnly]Name = '{0}' && Role = 'menu item'", resKeySwitchUser, resKeyStartMenuMoreApplication
//WMP and MM
//Backup
#define BACKUP_CPL_FILES                        EXPLORER_CLASS L";[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyBackupandRestoreCenter, resKeyBackupFiles
#define BACKUP_CPL_COMPUTER                     EXPLORER_CLASS L";[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyBackupandRestoreCenter, resKeyBackupComputer
#define BACKUP_CPL_CLOSE                        CLOSE_WINDOW(resKeyBackupandRestoreCenter,L"CabinetWClass")
#define BACKUP_STATUS_CLOSE						CLOSE_DIALOG(resKeyBackupStatusandConfigurationDialog)

//AdvancedPhoto & PhotoScreenSaver
#define CPL_CHANGE_SCREEN_SAVER                 EXPLORER_CLASS L";Name = '{1}' && Role = 'pane';Name = '{2}' && Role = 'link'", resKeyPersonalization, resKeyPersonalizationMainTask, resKeyScreenSaver
#define SCREEN_SAVER_SELECT						DIALOG_CLASS L";ControlId = '1300';Role = 'combo box'", resKeyScreenSaverSettings
#define SCREEN_SAVER_SETTINGS					DIALOG_CLASS L";[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyScreenSaverSettings,resKeyScreenSaverSettingsButton //;ControlId = '1303'
#define SCREEN_SAVER_CANCEL 					DIALOG_CLASS L";ControlId = '2';Role = 'push button'", resKeyScreenSaverSettings
#define PHOTO_SCREEN_SAVER_THEME_LABEL			DIALOG_CLASS L";ControlId = '1040';Name = '{1}' && Role = 'text'", resKeyPhotoScreenSaverSettingsTitle, resKeyPhotoScreenSaverTheme
#define PHOTO_SCREEN_SAVER_THEME				DIALOG_CLASS L";ControlId = '1002';Role = 'combo box'", resKeyPhotoScreenSaverSettingsTitle
#define PHOTO_SCREEN_SAVER_THEME_CANCEL		    DIALOG_CLASS L";ControlId = '2';Role = 'push button'", resKeyPhotoScreenSaverSettingsTitle
#define SCREEN_SAVER_SETTINGS_CLOSE				CLOSE_DIALOG(resKeyScreenSaverSettings)
#define PHOTO_SCREEN_SAVER_THEME_CLOSE			CLOSE_DIALOG(resKeyPhotoScreenSaverSettingsTitle)
#define SCREEN_SAVER_ALL_PICTURE_AND_VIDEOS	DIALOG_CLASS L";ControlId = '1033';[VisibleOnly]Role = 'radio button'", resKeyPhotoScreenSaverSettingsTitle
#define SCREEN_SAVER_HIGHER_RATING_LABEL		DIALOG_CLASS L";ControlId = '1037';[VisibleOnly]Name ='{1}' && Role = 'text'", resKeyPhotoScreenSaverSettingsTitle,resKeyWithThisRatingOrHigher

//HDPublish
#define MOVIE_MAKER_FILE_MENU					L";Name => '{0}' && ClassName => 'WTL_CustomCommandBarWindow_WMT';Name = '{1}' && Role = 'menu item'", resKeyMenuBar, resKeyFile
#define MOVIE_MAKER_FILE_IMPORT_MEDIA			MENU_CLASS L";Name = '{1}' && Role = 'menu item'", resKeyContext, resKeyImportMedia
#define MOVIE_MAKER_IMPORT_FILENAME				DIALOG_CLASS L";ControlId = '1148';[VisibleOnly]Role = 'editable text'", resKeyImportMediaItems
#define MOVIE_MAKER_IMPORT_BUTTON_PUSH			DIALOG_CLASS L";[VisibleOnly]Name = {1}", resKeyImportMediaItems, ampresKeyImportButton
#define MOVIE_MAKER_IMPORT_BUTTON_SPLIT			DIALOG_CLASS L";[VisibleOnly]Name = {1}", resKeyImportMediaItems, ampresKeyImportButton
#define MOVIE_MAKER_VIDEO_BEAR					L";Name => '{0}' && ClassName => 'MovieMakerWndClass';Role = 'list' && ClassName = 'SysListView32'; Role = 'list item'", resKeyWindowsMovieMaker5, langNeutralBear//Name = '{1}' &&
#define MOVIE_MAKER_ADD_TO_STORYBOARD			MENU_CLASS L";Name = '{1}' && Role = 'menu item'", resKeyContext, resKeyAddtoStoryboard
#define MOVIE_MAKER_FILE_PUBLISH_MOVIE			MENU_CLASS L";Name = '{1}' && Role = 'menu item'", resKeyContext, resKeyPublish
#define MOVIE_MAKER_PUBLISH_THIS_COMPUTER		L";Name => '{0}' && ClassName => 'NativeHWNDHost';Role = 'list' && ClassName = 'SysListView32';Name = '{1}' && Role = 'list item'", resKeyPublishMovie, resKeyThiscomputer
#define MOVIE_MAKER_PUBLISH_NEXT1				L";Name => '{0}' && ClassName => 'NativeHWNDHost';Name = '{1}' && Role = 'client';Name = '{2}' && Role = 'push button'", resKeyPublishMovie, resKeyWheredoyouwantto, resKeyNext
#define MOVIE_MAKER_PUBLISH_NEXT2				L";Name => '{0}' && ClassName => 'NativeHWNDHost';Name = '{2}' && Role = 'client';Name = '{1}' && Role = 'push button'", resKeyPublishMovie, resKeyNext, resKeyNamethemovieyouare
#define MOVIE_MAKER_PUBLISH_MORE_SETTINGS		L";Name => '{0}' && ClassName => 'NativeHWNDHost';ControlId = '1759';Role = 'radio button'", resKeyPublishMovie
#define MOVIE_MAKER_PUBLISH_UNNAMED_COMBOBOX	L";Name => '{0}' && ClassName => 'NativeHWNDHost';ControlId = '1445';Role = 'combo box'", resKeyPublishMovie
#define MOVIE_MAKER_PUBLISH_CANCEL1				L";Name => '{0}' && ClassName => 'NativeHWNDHost';Name = '{1}' && Role = 'client';Name => '{2}' && Role = 'push button'", resKeyPublishMovie, resKeyWheredoyouwantto, resKeyCancel
#define MOVIE_MAKER_PUBLISH_CANCEL2				L";Name => '{0}' && ClassName => 'NativeHWNDHost';Name = '{1}' && Role = 'client';Name => '{2}' && Role = 'push button'", resKeyPublishMovie, resKeyNamethemovieyouare, resKeyCancel
#define MOVIE_MAKER_PUBLISH_CANCEL3				L";Name => '{0}' && ClassName => 'NativeHWNDHost';Name = '{1}' && Role = 'client';Name => '{2}' && Role = 'push button'", resKeyPublishMovie, resKeyChoosethesettingsfor, resKeyCancel
#define MOVIE_MAKER_CLOSE						CLOSE_WINDOW(resKeyWindowsMovieMaker5,L"MovieMakerWndClass")
#define MOVIE_MAKER_PUBLISH_CLOSE				CLOSE_WINDOW(resKeyPublishMovie,L"NativeHWNDHost")
#define MOVIE_MAKER_DO_NOT_SAVE					DIALOG_CLASS L";Name = '{1}' && Role = 'push button'", resKeyWindowsMovieMaker5, resKeyNo //

// Group Policy
#define CLOSE_GP_FAILED_OPEN_WINDOW				CLOSE_DIALOG(langNeutralGpeditDotmsc)
#define CLOSE_GP_SUCCEEDED_OPEN_WINDOW			CLOSE_WINDOW(resKeyGroupPolicyObjectEditor,L"MMCMainFrame")
#define GROUP_POLICY_CLOSE						CLOSE_WINDOW(resKeyGroupPolicyObjectEditor,L"MMCMainFrame")

// Time Warp
#define RESTORE_PREVIOUS_VERSIONS				MENU_CLASS L";[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyContext, resKeyRestorePreviousVersions
#define COMPUTER_CLOSE							CLOSE_WINDOW(resKeyComputer,L"CabinetWClass")


// Mobility Center
#define MOBILITY_CENTER_TITLE_BAR				L";Name => '{0}' && ClassName => 'MobilityCenterApp';[VisibleOnly]Role = 'title bar' && ClassName = 'MobilityCenterApp'", resKeyWindowsMobilityCenter
#define MOBILITY_CENTER_CLOSE					L";Name => '{0}' && ClassName => 'MobilityCenterApp';[VisibleOnly]Role = 'title bar' && ClassName = 'MobilityCenterApp';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyWindowsMobilityCenter, resKeyClose

//#define CPL_MOBILE_PC_LNK						EXPLORER_CLASS L";Name = '{1}' && Role = 'pane';[VisibleOnly]Name = '{2}' && Role = 'link'", resKeyControlPanel, langNeutralCPCategoryPanel, resKeyMobilePC
//#define CPL_MBLCTR_LNK							EXPLORER_CLASS L";Name = '{1}' && Role = 'pane';[VisibleOnly]Name = '{2}' && Role = 'link'", (wchar_t*) cmplxKeyControlbanelMobilePC, langNeutralCPCategoryPanel, resKeyMobilityCenter
#define MBLCTR_CLOSE_BTN						CLOSE_WINDOW(resKeyWindowsMobilityCenter,L"MobilityCenterApp")
#define CPL_SYS_CLOSE_BTN                       EXPLORER_CLASS L";Role = 'title bar' && ClassName = 'CabinetWClass';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeySystem, resKeyClose




// File Encryption //a-facalc

#define USERS_PUBLIC							EXPLORER_CLASS L";[VisibleOnly]Role = 'list' && ClassName = 'SysListView32';Name = '{1}' && Role = 'list item'", resKeyUsers, resKeyPublic
#define PUBLIC_TESTFOLDER						EXPLORER_CLASS L";[VisibleOnly]Role = 'list' && ClassName = 'SysListView32';Name = '{1}' && Role = 'list item'", resKeyPublic, langNeutralTestFolder
#define PUBLIC_TESTFILE							EXPLORER_CLASS L";[VisibleOnly]Role = 'list' && ClassName = 'SysListView32';Name = '{1}' && Role = 'list item'", resKeyPublic, langNeutralTestFile
#define CMENU_PROPERTIES					 	MENU_CLASS L";[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyContext, resKeyProperties

#define TESTFOLDER_PROPERTIES_ADVANCED			DIALOG_CLASS L";ControlId = '13154';Role = 'push button'", resKeyGeneralForFolder
#define TESTFOLDER_CHECK_ENCRYPT				DIALOG_CLASS L";ControlId = '13159';[VisibleOnly]Role = 'check box'", resKeyAdvancedAttributesForFolder
#define TESTFOLDER_UNCHECK_ENCRYPT				DIALOG_CLASS L";ControlId = '13159';[VisibleOnly]Role = 'check box'", resKeyAdvancedAttributesForFolder
#define TESTFOLDER_ADVANCED_CANCEL				DIALOG_CLASS L";ControlId = '2';[VisibleOnly]Role = 'push button'", resKeyAdvancedAttributesForFolder
#define TESTFOLDER_PROPERTIES_CANCEL			DIALOG_CLASS L";ControlId = '2';[VisibleOnly]Role = 'push button'", langNeutralTestFolder //(wchar_t*) cmplxKeyPropertiesTestFolder

#define TESTFILE_PROPERTIES_ADVANCED			DIALOG_CLASS L";ControlId = '13154';Role = 'push button'", resKeyGeneralForFile
#define TESTFILE_CHECK_ENCRYPT					DIALOG_CLASS L";ControlId = '13159';[VisibleOnly]Role = 'check box'", resKeyAdvancedAttributesForFile
#define TESTFILE_UNCHECK_ENCRYPT				DIALOG_CLASS L";ControlId = '13159';[VisibleOnly]Role = 'check box'", resKeyAdvancedAttributesForFile
#define TESTFILE_ADVANCED_CANCEL				DIALOG_CLASS L";ControlId = '2';[VisibleOnly]Role = 'push button'", resKeyAdvancedAttributesForFile
#define TESTFILE_PROPERTIES_CANCEL				DIALOG_CLASS L";ControlId = '2';[VisibleOnly]Role = 'push button'", langNeutralTestFile //(wchar_t*) cmplxKeyPropertiesTestFile		

#define PUBLIC_CLOSE							EXPLORER_CLASS L";[VisibleOnly]Role = 'title bar' && ClassName = 'CabinetWClass';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyPublic, resKeyClose



// Media Samples

#define USERS_PUBLIC					EXPLORER_CLASS L";[VisibleOnly]Role = 'list' && ClassName = 'SysListView32';Name = '{1}' && Role = 'list item'", resKeyUsers, resKeyPublic
#define PUBLIC_RECORDEDTV				EXPLORER_CLASS L";[VisibleOnly]Role = 'list' && ClassName = 'SysListView32';Name = '{1}' && Role = 'list item'", resKeyPublic, langNeutralRecordedTV
#define RECORDEDTV_SAMPLEMEDIA			EXPLORER_CLASS L";[VisibleOnly]Role = 'list' && ClassName = 'SysListView32';Name = '{1}' && Role = 'list item'", langNeutralRecordedTV, langNeutralSampleMedia
#define SAMPLEMEDIA_APOLLO13			EXPLORER_CLASS L";[VisibleOnly]Role = 'list' && ClassName = 'SysListView32';Name = '{1}' && Role = 'list item'", langNeutralSampleMedia, langNeutralApollo13
#define SAMPLEMEDIA_CARIBBEAN			EXPLORER_CLASS L";[VisibleOnly]Role = 'list' && ClassName = 'SysListView32';Name = '{1}' && Role = 'list item'", langNeutralSampleMedia, langNeutralJewelsofCaribbean
#define SAMPLEMEDIA_VERTIGO				EXPLORER_CLASS L";[VisibleOnly]Role = 'list' && ClassName = 'SysListView32';Name = '{1}' && Role = 'list item'", langNeutralSampleMedia, langNeutralVertigo
#define SAMPLEMEDIA_CLOSE				CLOSE_EXPLORER(langNeutralSampleMedia)
//#define PUBLIC_CLOSE					CLOSE_EXPLORER(resKeyPublic)


// Obsolete QueryIDs

//#define SYSTEM_PROPERTIES_OK_BTN                DIALOG_CLASS L";ControlId = '1';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeySystemPropertiesDialogTitle, resKeyRemoteOK    
//#define CPL_CLOSE_BTN                           CLOSE_WINDOW(resKeyControlPanel,L"CabinetWClass")    
//#define SCREEN_SAVER_SETTINGS_CLOSE				DIALOG_CLASS L";Name = '{1}' && Role = 'push button'", resKeyScreenSaverSettings, resKeyClose //DC
//#define PHOTO_SCREEN_SAVER_THEME_CLOSE			DIALOG_CLASS L";Name = '{1}' && Role = 'push button'", resKeyPhotoScreenSaverSettingsTitle, resKeyClose  //DC
//#define CPL_SYS_CLOSE_BTN                       CLOSE_WINDOW(resKeySystem,L"CabinetWClass")
//#define CPL_WC_CLOSE_BTN                        EXPLORER_CLASS L";Role = 'title bar' && ClassName = 'CabinetWClass';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyWelcomeCenter, resKeyClose
//#define IE_TOOLS_INTERNET_OPTIONS_CLOSE       DIALOG_CLASS L";Role = 'title bar' && ClassName = '#32770';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyInternetPropertiesTab, resKeyClose //DC
//#define IE_CLOSE                                L";Name => '{0}' && ClassName => 'IEFrame';Role = 'title bar' && ClassName = 'IEFrame';[VisibleOnly]Name = '{1}' && Role = 'push button'", CMPLXKEYMSNCOMDASHWINDOWS, resKeyClose //TODO, bad res key, assumes specific home page.
//#define RESTORE_PREVIOUS_VERSIONS_CLOSE			DIALOG_CLASS L";[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyComputer, resKeyClose
//#define STARTMENU_WELCOMECENTER				STARTMENU_ITEM(resKeyWelcomeCenter) 
//#define STARTMENU_COMPUTER                  L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyStartMenuComputer
//#define STARTMENU_GAMES                     L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyStartMenuGames
//#define STARTMENU_PROJECTORx64					STARTMENU_ITEM(resKeyConnecttoaNetworkProjectorx64) 
//#define STARTMENU_WINDOWS_MOVIE_MAKERx64        STARTMENU_ITEM(resKeyWindowsMovieMakerx64) 
//#define STARTMENU_BACKUP_RESTORE_CENTERx64      STARTMENU_ITEM(resKeyBackupandRestoreCenterx64) 
//#define START_MENU_CONTROL_PANEL   L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", langNeutralStartMenu, resKeyControlPanel
//#define CPL_MAXIMIZE               EXPLORER_CLASS L";Role = 'title bar' && ClassName = 'CabinetWClass';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyControlbanel, resKeyMaximize
//#define CPL_CLOSE_BTN              EXPLORER_CLASS L";Role = 'title bar' && ClassName = 'CabinetWClass';[VisibleOnly]Name = '{1}' && Role = 'push button'", (wchar_t*) cmplxKeyControlbanelMobilePC, resKeyClose
//#define PUSHBUTTONCLOSEEXCLPERSON				EXPLORER_CLASS L";[VisibleOnly]Role = 'title bar' && ClassName = 'CabinetWClass';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyPersonalization, langNeutralClose

//Make DVD Movie - PhotoGallery
#define STARTMENU_WINDOWS_PHOTO_GALLERY		L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyWindowsPhotoGallery
#define PHOTO_GALLERY_BURN					L";Name => '{0}' && ClassName => 'Windows_Photo_Library_MainWnd';[VisibleOnly]ControlId = '60006';[VisibleOnly]Role = 'push button'", resKeyWindowsPhotoGalleryWindow		
#define PHOTO_GALLERY_MORE_OPTIONS			L";Name => '{0}' && ClassName => 'Windows_Photo_Library_MainWnd';[VisibleOnly]ControlId = '60009';[VisibleOnly]Role = 'push button'", resKeyWindowsPhotoGalleryWindow
#define PHOTO_GALLERY_MORE_OPTION_BURN		L";AccessibleName = '{1}' && ClassName => '#32768' && Role = 'popup menu';[VisibleOnly]Name = '{0}' && Role = 'menu item'", resKeyBurn, resKeyContext
#define PHOTO_GALLERY_VIDEO_DVD				L";AccessibleName = '{1}' && ClassName => '#32768' && Role = 'popup menu';[VisibleOnly]Name = '{0}' && Role = 'menu item'", resKeyVideoDVD, resKeyContext
#define PHOTO_GALLERY_CLOSE					L";Name => '{0}' && ClassName => 'Windows_Photo_Library_MainWnd';[VisibleOnly]Role = 'title bar' && ClassName = 'Windows_Photo_Library_MainWnd';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyWindowsPhotoGalleryWindow, resKeyClose

//StartMenu Classic View
#define STARTMENU_PROPERTIES	L";AccessibleName = '{0}' && ClassName => '#32768' && Role = 'popup menu';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStart, resKeyStartMenuProperties
#define STARTMENU_PROPERTIES_CLASSICMENU 	L";Name => '{0}' && ClassName => '#32770';ControlId = '1133';[VisibleOnly]Role = 'radio button'", resKeyStartMenuTab
#define STARTMENU_PROPERTIES_STARTMENU		L";Name => '{0}' && ClassName => '#32770';ControlId = '1132';Class = 'Button'; [VisibleOnly]Role = 'radio button'", resKeyStartMenuTab
#define TASKBAR_STARTMENU_OK					L";Name => '{0}' && ClassName => '#32770';ControlId = '1';[VisibleOnly]Role = 'push button'", resKeyTaskBarandStartMenu
#define	STARTMENU_CLASSIC_PROGRAMS			L";AccessibleName = '{0}' && ClassName => 'ToolbarWindow32' && Role = 'popup menu';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyClassicApplication, resKeyClassicPrograms
#define	STARTMENU_CLASSIC_DOCUMENTS		L";AccessibleName = '{0}' && ClassName => 'ToolbarWindow32' && Role = 'popup menu';[VisibleOnly]Name = '{1}' && Role = 'menu item'",  resKeyClassicApplication, resKeyClassicDocuments
#define	STARTMENU_CLASSIC_SETTINGS			L";AccessibleName = '{0}' && ClassName => 'ToolbarWindow32' && Role = 'popup menu';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyClassicApplication, resKeyClassicSettings
#define STARTMENU_CLASSIC_SEARCH				L";AccessibleName = '{0}' && ClassName => 'ToolbarWindow32' && Role = 'popup menu';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyClassicApplication, resKeyClassicSearch
#define STARTMENU_CLASSIC_DEFAULT_PROGRAMS	L";AccessibleName = '{0}' && ClassName => 'ToolbarWindow32' && Role = 'popup menu';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyClassicApplication, resKeyClassicDefaultPrograms 
#define STARTMENU_CLASSIC_WINDOWS_UPDATE 	L";AccessibleName = '{0}' && ClassName => 'ToolbarWindow32' && Role = 'popup menu';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyClassicApplication, resKeyClassicWindowsUpdate
#define STARTMENU_CLASSIC_HELP_AND_SUPPORT	L";AccessibleName = '{0}' && ClassName => 'ToolbarWindow32' && Role = 'popup menu';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyClassicApplication, resKeyClassicHelpandSupport
#define STARTMENU_CLASSIC_RUN					L";AccessibleName = '{0}' && ClassName => 'ToolbarWindow32' && Role = 'popup menu';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyClassicApplication, resKeyClassicRun



//Meeting Space 
#define STARTMENU_WINDOWS_MEETING_SPACE				L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyWindowsMeetingSpace
#define WINDOWS_MEETING_SPACE_SETTINGS				L";Name => '{0}' && ClassName => '#32770';[VisibleOnly]Name = '{0}' && Role = 'pane';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyWindowsMeetingSpaceWindow, resKeyYesContinueSetting
#define PEOPLE_NEAR_ME								L";Name => '{0}' && ClassName => '#32770';ControlId = '1';[VisibleOnly]Role = 'push button'", resKeyPeopleNearMe1
#define WINDOWS_MEETING_SPACE_START_A_NEW_MEETING	L";Name => '{0}';[VisibleOnly]Role = 'push button'", resKeyStartANewMeeting  //1568748
#define WINDOWS_MEETING_SPACE_CREATE_MEETING		L";Name => '{0}' && ClassName => '#32770';[VisibleOnly]Role = 'push button'", resKeyWindowsMeetingSpaceGeneral
#define WINDOWS_MEETING_SPACE_MEETING_CLOSE			L";Name => '{0}' && ClassName => 'SpacesContainerWindow';[VisibleOnly]Role = 'title bar' && ClassName = 'SpacesContainerWindow';[VisibleOnly]Name = '{1}' && Role = 'push button'", (wchar_t*) cmplxKeyWindowsMeetingSpace, resKeyClose
#define MEETING_SPACE_DISPLAY_NAME					L";Name => '{0}' && ClassName => '#32770';ControlId = '8002';[VisibleOnly]Role = 'editable text'", resKeyPeopleNearMe1
#define MEETING_SPACE_MEETING_NAME					L";Name => '{0}' && ClassName => '#32770';ControlId = '1293';[VisibleOnly]Role = 'editable text'", resKeyWindowsMeetingSpaceGeneral
#define MEETING_SPACE_GENERAL_CLOSE					L";Name => '{0}' && ClassName => '#32770';[VisibleOnly]Name = '{1}' && Role = 'push button'",resKeyWindowsMeetingSpaceGeneral, resKeyClose 
#define MEETING_SAPCE_GENERAL_MEETING_NAME			L";Name => '{0}' && ClassName => '#32770';ControlId = '1293';[VisibleOnly]Role = 'editable text'", resKeyWindowsMeetingSpaceGeneral
#define	MEETING_SPACE_MEETING_PASSWORD				L";Name => '{0}' && ClassName => '#32770';ControlId = '1295';[VisibleOnly]Role = 'editable text'", resKeyWindowsMeetingSpaceGeneral
#define WINDOWS_MEETING_SPACE_MEETING_TITLE_BAR		L";Name => '{0}' && ClassName => 'SpacesContainerWindow';[VisibleOnly]Role = 'title bar' && ClassName = 'SpacesContainerWindow'", (wchar_t*) cmplxKeyWindowsMeetingSpace


//Client Side Caching
#define CMENU_ALWAYS_AVAILABLE_OFFLINE			L";AccessibleName = '{0}' && ClassName => '#32768' && Role = 'popup menu';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyContext, resKeyAlwaysAvailableOffline
#define SKU_FOLDER_CLOSE								L";Name => '{0}' && ClassName => 'CabinetWClass';Role = 'title bar' && ClassName = 'CabinetWClass';Name = '{1}' && Role = 'push button'",langNeutralParentFolder , resKeyClose
#define CONNECT_TO_SHARE_USERNAME				 	L";Name => '{0}' && ClassName => '#32770';ControlId = '1003';[VisibleOnly]Role = 'editable text'", (wchar_t*) cmplxKeyConnectToShare
#define CONNECT_TO_SHARE_PASSWORD 					 L";Name => '{0}' && ClassName => '#32770';ControlId = '1005';[VisibleOnly]Role = 'editable text'", (wchar_t*) cmplxKeyConnectToShare
#define CONNECT_TO_SHARE_OK 							L";Name => '{0}' && ClassName => '#32770';ControlId = '1';[VisibleOnly]Role = 'push button'", (wchar_t*) cmplxKeyConnectToShare
#define COMPUTER_NAME_FOLDER_ON_SHARE 				L";Name => '{0}' && ClassName => 'CabinetWClass';[VisibleOnly]Role = 'list' && ClassName = 'SysListView32';Name = '{1}' && Role = 'list item'", langNeutralParentFolder, langNeutralTestFolder


//Network share Timewarp

#define CMENU_RESTORE_PREVIOUS_VERSION			L";AccessibleName = '{1}' && ClassName => '#32768' && Role = 'popup menu';[VisibleOnly]Name = '{0}' && Role = 'menu item'", resKeyRestorePreviousVersions, resKeyContext

#define FOLDER_PREVIOUS_VERSION_TAB  			L";Name => '{0}' && ClassName => '#32770';Role = 'page tab list' && ClassName = 'SysTabControl32';Name = '{1}' && Role = 'page tab'", langNeutralTestFolder ,resKeyPreviousVersionsTab//(wchar_t*) cmplxKeyPropertiesFolder, resKeyPreviousVersionsTab
#define PREVIOUS_VERSION_TAB_RESTORE			L";Name => '{0}' && ClassName => '#32770';ControlId = '206';Role = 'push button'", resKeyPreviousVersionsFolder
//#define PROPERTIES_CANCEL						L";Name => '{0}' && ClassName => '#32770';ControlId = '2';Role = 'push button'", langNeutralTestFolder // (wchar_t*) cmplxKeyPropertiesFolder

#define FILE_PREVIOUS_VERSION_TAB_RESTORE			L";Name => '{0}' && ClassName => '#32770';ControlId = '206';Role = 'push button'", resKeyPreviousVersionsFile
#define FILE_PREVIOUS_VERSION_TAB		L";Name => '{0}' && ClassName => '#32770';Role = 'page tab list' && ClassName = 'SysTabControl32';Name = '{1}' && Role = 'page tab'", langNeutralTestFile ,resKeyPreviousVersionsTab//(wchar_t*) cmplxKeyPropertiesFolder, resKeyPreviousVersionsTab

//Windows Media Player Media Connect

#define WMP_FIRST_TIME_LAUNCH_EXPRESS_SETTING	L";Name => '{0}' && ClassName => '#32770';ControlId = '1122';Role = 'radio button'", resKeyWindowsMediaPlayerSetUpWindow
#define WMP_FIRST_TIME_LAUNCH_FINISH_BTN		L";Name => '{0}' && ClassName => '#32770';ControlId = '39299';[VisibleOnly]Role = 'push button'", resKeyWindowsMediaPlayerSetUpWindow
#define WMP_MENU_ITEM_TOOLS		L";Name => '{0}' && ClassName => 'WMPlayerApp';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyWindowsMediaPlayerWindow, resKeyToolsInWMP
#define WMP_TOOLS_OPTIONS		L";AccessibleName = '{1}' && ClassName => '#32768' && Role = 'popup menu';[VisibleOnly]Name = '{0}' && Role = 'menu item';[VisibleOnly]Name = '{2}' && Role = 'menu item'", resKeyToolsInWMP, resKeyContextInWMP, resKeyOptionsInTools
#define OPTIONS_LIBRARY_TAB	L";Name => '{0}' && ClassName => '#32770';[VisibleOnly]Role = 'page tab list' && ClassName = 'SysTabControl32';[VisibleOnly]Name = '{1}' && Role = 'page tab'", resKeyOptionsInWMP, resKeyLibraryInWMP
#define OPTIONS_LIBRARY_CONFIGURE_SHARING	L";Name => '{0}' && ClassName => '#32770';ControlId = '1067';[VisibleOnly]Role = 'push button'", resKeyOptionsInWMP
#define CLOSE_MEDIA_SHARING	L";Name => '{0}' && ClassName => '#32770';[VisibleOnly]Role = 'title bar' && ClassName = '#32770';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyMediaSharingInWMP, resKeyClose
#define CLOSE_OPTIONS 			L";Name => '{0}' && ClassName => '#32770';[VisibleOnly]Role = 'title bar' && ClassName = '#32770';[VisibleOnly]Name = '{1}' && Role = 'push button'", resKeyOptionsInWMP, resKeyClose
#define CLOSE_WMP				L";Name => '{1}' && ClassName => 'WMPlayerApp';[VisibleOnly]Role = 'title bar' && ClassName = 'WMPlayerApp';[VisibleOnly]Name = '{0}' && Role = 'push button'", resKeyClose, resKeyWindowsMediaPlayerWindow

//Start Menu

#define STARTMENU_INTERNET		L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyInternet
#define STARTMENU_EMAIL		L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyEmail
#define STARTMENU_DOCUMENTS	L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyDocuments
#define STARTMENU_PICTURES		L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyPictures
#define STARTMENU_MUSIC		L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyMusic
#define STARTMENU_RECENT_ITEMS		L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyRecentItems
#define STARTMENU_NETWORK		L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyNetwork
#define STARTMENU_CONNECT_TO	L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyConnectTo
#define STARTMENU_DEFAULT_PROGRAMS		L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyDefaultPrograms
#define STARTMENU_HELP_AND_SUPPORT		L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyHelpAndSupport

//Windows Side Show

#define WINDOWS_SIDE_SHOW_AUX_DISPLAY		 L";Name => '{0}' && ClassName => 'MainWindow';Name = '{0}' && Role = 'client'", langNeutralWindowsSideShow
#define WINDOWS_SIDE_SHOW_AUX_DISPLAY_CLOSE 	L";AccessibleName = '{1}' && ClassName => '#32768' && Role = 'popup menu';[VisibleOnly]Name = '{0}' && Role = 'menu item'", langNeutralClose, resKeyContext
#define WINDOWS_SIDE_SHOW_WINDOWS_MAIL  	L";Name => '{0}' && ClassName => 'CabinetWClass';[VisibleOnly]Name = '{1}' && Role = 'cell';[VisibleOnly]Role = 'check box' && ClassName = 'Button'", resKeyCPLWindowsSideShow, resKeyWindowsSideShowWindowsMail 
#define WINDOWS_SIDE_SHOW_WMP		L";Name => '{0}' && ClassName => 'CabinetWClass';[VisibleOnly]Name = '{1}' && Role = 'cell';[VisibleOnly]Role = 'check box' && ClassName = 'Button'", resKeyCPLWindowsSideShow, resKeyWindowsSideShowWMP

//Tablet PC Components
#define ALL_PROGRAMS_ACCESSORIES_TABLET_PC     STARTMENU_FOLDER(resKeyTabletPC) 
#define ACCESSORIES_TABLET_PC_STICKY_NOTES	L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyStickyNotes
#define ACCESSORIES_TABLET_PC_INPUT_PANEL 	L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyTabletPCInputPanel 
#define ACCESSORIES_TABLET_PC_WINODWS_JOURNAL	L";Name => '{0}' && ClassName => 'DV2ControlHost';[VisibleOnly]Name = '{1}' && Role = 'menu item'", resKeyStartMenu, resKeyWindowsJournal
