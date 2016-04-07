#include <windows.h>            //Common Windows types
//#include "rpf_constants.h"
#include "screenelement.h"             //RPF
#include "LoggingFunctions.h"
#include "rpf_skudiff.h" // SKU Diff Contants
#include "SKUDIFF_UTIL.h"

using namespace RPFPlayback;
using namespace SKUDiff;


#define MAHJONG_TITANS 0
#define CHESS_TITANS 3
#define FREECELL 6
#define HEARTS 9

LPCWSTR rg_Games_Open[] = {
	GAMES_MAHJONG_TITANS,
	GAMES_CHESS_TITANS,
	GAMES_FREECELL,
	GAMES_HEARTS
};

LPCWSTR rg_Games_Close[] = {
	MAHJONG_TITANS_CLOSE,
	CHESS_TITANS_CLOSE,
	FREECELL_CLOSE,
	HEARTS_CLOSE
};

LPCWSTR rg_WindowsFeaturesGames[] = {
	WINDOWS_FEATURES_MAHJONG_TITANS,
	WINDOWS_FEATURES_CHESS_TITANS
};

void CloseExcessWindows() // test specific, ensure a clean state; can be made better with RPF 12+
{
	wchar_t szGlobalQuery[1024];
	GlobalizeQueryId(szGlobalQuery, 1024, MAHJONG_TITANS_CLOSE);
	LeftClickUntilGone(szGlobalQuery);
	GlobalizeQueryId(szGlobalQuery, 1024, CHESS_TITANS_CLOSE);
	LeftClickUntilGone(szGlobalQuery);
	GlobalizeQueryId(szGlobalQuery, 1024, FREECELL_CLOSE);
	LeftClickUntilGone(szGlobalQuery);
	GlobalizeQueryId(szGlobalQuery, 1024, HEARTS_CLOSE);
	LeftClickUntilGone(szGlobalQuery);
	//TerminateProcessByModuleName(L"FreeCell.exe", 0);
	//TerminateProcessByModuleName(L"Hearts.exe", 0);
	//TerminateProcessByModuleName(L"Mahjong.exe", 0);
	//TerminateProcessByModuleName(L"chess.exe", 0);
}

STDAPI InitTest(LPVOID)
{
	HRESULT hr = SKUInitTest();
	SetRobustnessLevel(0);
	if SUCCEEDED(hr){CloseExcessWindows();}
	return hr;
}

STDAPI UnInitTest()
{
	CloseExcessWindows();
	return SKUUnInitTest();
}

// ArePremiumGamesExpected
//
// Helper function that determines if Premium Games Entry points must be present on the current installed SKU or not.
// Returns True : if Premium Games entry points are expected
// Returns False : if Premium Games entry points are not expected
BOOL ArePremiumGamesExpected()
{
	BOOL fExpected = FALSE;

	DWORD dwProductInfoType = 0;
	if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
	{
		switch (dwProductInfoType)
		{
		case PRODUCT_STARTER:
		case PRODUCT_HOME_BASIC:
		case PRODUCT_HOME_BASIC_N:
			LogTestInfoW(__FUNCTIONW__, L"Premium Games not expected here!");
			break;
		case PRODUCT_BUSINESS:
		case PRODUCT_BUSINESS_N:
		case PRODUCT_ENTERPRISE:
		case PRODUCT_ENTERPRISE_N:
		case PRODUCT_HOME_PREMIUM:
		case PRODUCT_HOME_PREMIUM_N:
		case PRODUCT_ULTIMATE:
		case PRODUCT_ULTIMATE_N:
			fExpected = TRUE;
			break;
		default:
			LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
			break;
		}
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Failed to get product/SKU info");
	}

	return fExpected;
}

// AreDefaultInstalledGamesExpected
//
// Helper function that determines if Default Installed Games Entry points must be present on the current installed SKU or not.
// Returns True : if Default Installed Games entry points are expected
// Returns False : if Default Installed Games entry points are not expected
BOOL AreDefaultInstalledGamesExpected()
{
	BOOL fExpected = FALSE;

	DWORD dwProductInfoType = 0;
	if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
	{
		switch (dwProductInfoType)
		{
		case PRODUCT_BUSINESS:
		case PRODUCT_BUSINESS_N:
		case PRODUCT_ENTERPRISE:
			LogTestInfoW(__FUNCTIONW__, L"Games should not be installed by default on this SKU!");
			break;
		case PRODUCT_STARTER:
		case PRODUCT_HOME_BASIC:
		case PRODUCT_HOME_BASIC_N:
		case PRODUCT_HOME_PREMIUM:
		case PRODUCT_ULTIMATE:
			fExpected = TRUE;
			break;
		default:
			LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
			break;
		}
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Failed to get product/SKU info");
	}

	return fExpected;
}

// OpenGamesExplorer
//
// Helper function that opens Games Explorer depending on the SKU installed.
// Business/Enterprise : Games are not installed by default. Go to Start->All Programs-> Games
// All other SKUs      : Games are installed by default. Go to Start-> Games.
//
// Returns True : if Games Explorer is opened successfully
// Returns False : if Games Explorer failed to open
BOOL OpenGamesExplorer()
{
	BOOL fOpenedGamesExplorer = FALSE;

//	HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
	if (SUCCEEDED(OpenStartMenu()))
	{
//		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

		DWORD dwProductInfoType = 0;
		if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
		{
			switch (dwProductInfoType)
			{
			case PRODUCT_BUSINESS:
			case PRODUCT_BUSINESS_N:
			case PRODUCT_ENTERPRISE:
				{
					HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_ALLPROGRAMS));
					if (SUCCEEDED(hr))
					{
						LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

		hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_ALLPROGRAMS));
		if (SUCCEEDED(hr))  
		{
			LogTestInfoW(__FUNCTIONW__, L"Have to re-open All Programs menu.");
			//LogTestResultW(fHDCodecsPassed, __FUNCTIONW__, pwszResultInfo);
			//return NOERROR;
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		}

						HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(ALL_PROGRAMS_GAMES));
						if (SUCCEEDED(hr))
						{
							LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

							HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_GAMES_EXPLORER));
							if (SUCCEEDED(hr))
							{
								LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
								fOpenedGamesExplorer = TRUE;
							}
						}
					}
					break;
				}
			case PRODUCT_STARTER:
			case PRODUCT_HOME_BASIC:
			case PRODUCT_HOME_BASIC_N:
			case PRODUCT_HOME_PREMIUM:
			case PRODUCT_ULTIMATE:
				{
					HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_GAMES));
					if (SUCCEEDED(hr))
					{
						LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
						fOpenedGamesExplorer = TRUE;
					}
					break;
				}
			default:
				{
					LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
					break;
				}
			}
		}
		else
		{
			LogTestInfoW(__FUNCTIONW__, L"Failed to get product/SKU info");
		}
	}

	if (fOpenedGamesExplorer)
	{
		// Games update and setup options dialog box may/maynot pop up depending 
		// on whether this is the first time Games Explorer is being opened.

		// So set timeout to 10 seconds to quickly close the dialog box if opened 
		// Save the original timeout so it can be set later.
		int originalTimeout = SetSearchTimeOut(10000);
		HRESULT hr = LOG_FAILED_HR(WOWFromPartialQueryId(GAMES_UPDATE_AND_OPTIONS));
		if (FAILED(hr))
		{
			// this is not the first time games explorer is being opened.
			LogTestInfoW(__FUNCTIONW__, L"Games update and options window was not open. Moving forward.");
		}
		else
		{
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		}
		// restore original timeout
		SetSearchTimeOut(originalTimeout);
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Failed to open Games Explorer");
	}

	return fOpenedGamesExplorer;
}

HRESULT GetNameFromGDF(__in char* resfile, __out wchar_t* gamename)
{
	HMODULE GameModule;
	GameModule = LoadLibraryEx(resfile,  NULL,  LOAD_LIBRARY_AS_DATAFILE);
	
	if (GameModule == NULL)
	{
		return E_FAIL;
	}
	
	HRSRC GDFResource;
	GDFResource = FindResourceEx(GameModule,    "DATA",    "__GDF_XML",    MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL));
	
	if (GDFResource == NULL)
	{
		return E_FAIL;
	}
	
	HGLOBAL hResource;
	hResource = LoadResource(GameModule,GDFResource);
	
	if (hResource == NULL)
	{
		return E_FAIL;
	}
	
	LPVOID pGDF;
	pGDF = LockResource(hResource);
	
	if (pGDF == NULL)
	{
		return E_FAIL;
	}
	
	// TODO: Should use proper XML functions.

	wchar_t* psnzGDF = (wchar_t*)pGDF;
	int i = 0;
	int StartAt = 0;
	int EndAt = 0;

	while (i++ < 1024 && EndAt == 0)
	{
		if ((((wchar_t)(psnzGDF+i)[0]) == L'<') && (((wchar_t)(psnzGDF+i)[1]) == L'N') && (((wchar_t)(psnzGDF+i)[2]) == L'a') &&
			(((wchar_t)(psnzGDF+i)[3]) == L'm') && (((wchar_t)(psnzGDF+i)[4]) == L'e') && (((wchar_t)(psnzGDF+i)[5]) == L'>'))
		{
			//LogTestInfoW(__FUNCTIONW__,L"Start at %d", i+6);
			StartAt = i+6;
		}
		if ((((wchar_t)(psnzGDF+i)[0]) == L'<') && (((wchar_t)(psnzGDF+i)[1]) == L'/') && (((wchar_t)(psnzGDF+i)[2]) == L'N') && (((wchar_t)(psnzGDF+i)[3]) == L'a') &&
			(((wchar_t)(psnzGDF+i)[4]) == L'm') && (((wchar_t)(psnzGDF+i)[5]) == L'e') && (((wchar_t)(psnzGDF+i)[6]) == L'>'))
		{
			//LogTestInfoW(__FUNCTIONW__,L"End at %d", i);
			EndAt = i;
		}
	}
	//LogTestInfoW(__FUNCTIONW__,L"Length %d", EndAt-StartAt);


	StringCchCopyW(gamename,(EndAt-StartAt)+1, psnzGDF+StartAt);
	LogTestInfoW(__FUNCTIONW__,L"GDF Name Contents: %s", gamename);
	return NOERROR;
}

//    
//    VerifyGames_PremiumGamesEntryPoint 
//  
STDAPI VerifyGames_PremiumGamesEntryPoint(LPVOID pvReserved)
{
	BOOL    fPassed = FALSE;
	LPWSTR pwszResultInfo = NULL;

	LogTestBeginW(__FUNCTIONW__, L"Verify Premium Games are available in Games Explorer");    

	wchar_t Chess[1024] = L"###";
	if SUCCEEDED(GetNameFromGDF("c:\\program files\\microsoft games\\Chess\\Chess.exe", Chess+3))
	{
		StringCchCatW(Chess,1024,L"###");
		LogTestInfoW(__FUNCTIONW__,L"Using Value: %s", Chess);
		rg_Games_Open[CHESS_TITANS + 2] = Chess;
	}
	wchar_t Mahjong[1024] = L"###";
	if SUCCEEDED(GetNameFromGDF("c:\\program files\\microsoft games\\Mahjong\\Mahjong.exe", Mahjong+3))
	{
		StringCchCatW(Mahjong,1024,L"###");
		LogTestInfoW(__FUNCTIONW__,L"Using Value: %s", Mahjong);
		rg_Games_Open[MAHJONG_TITANS + 2] = Mahjong;
	}
	
	// There are two ways to get to the games explorer depending on the SKU installed.
	// Business/Enterprise : Games are not installed by default.
	// All other SKUs      : Games are installed by default. Go to Start-> Games.
	if (!AreDefaultInstalledGamesExpected())
	{
		pwszResultInfo = L"Games not installed by default on Business/BusinessN/Enteprise. No need to check for Premium Games.";
		fPassed = TRUE;
	}
	else
	{
		if (OpenGamesExplorer())
		{
			BOOL fExpected = ArePremiumGamesExpected();

			// loop starting from MAHJONG_TITANS to CHESS_TITANS.
			for (int gamesIndex = MAHJONG_TITANS; gamesIndex <= CHESS_TITANS; gamesIndex += 3)
			{
				BOOL fFoundGameClickablePoint = FALSE;

				if (SUCCEEDED(FromPartialQueryId(
					(wchar_t*)rg_Games_Open[gamesIndex], 
					(wchar_t*)rg_Games_Open[gamesIndex + 1], 
					(wchar_t*)rg_Games_Open[gamesIndex + 2])))
				{
					int x, y;
					fFoundGameClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));

					LogTestInfoW(__FUNCTIONW__,
						L"%s Clickable point ", fFoundGameClickablePoint ? L"Found": L"Did not find");

					if (fFoundGameClickablePoint != fExpected)
					{
						pwszResultInfo = L"Entry point is not differentiated correctly";
						LogTestInfoW(__FUNCTIONW__,
							L"Premium Games SKU differentiation failed.[Current: %s | Expected: %s ]",
							fFoundGameClickablePoint ? L"Found": L"Not Found",
							fExpected ? L"Found" : L"Not Found");
						break;
					}
					else
					{
						fPassed = TRUE;
						if (fExpected)
						{
							// Go ahead and open the game.
							LOG_FAILED_HR(DoubleClick(CLICKABLE_POINT));

							if (gamesIndex == CHESS_TITANS)
							{
								// Select difficulty dialog box may/maynot pop up depending 
								// on whether this is the first time Chess is being opened.

								// So set timeout to 10 seconds to quickly close the dialog box if opened 
								// Save the original timeout so it can be set later.
								int originalTimeout = SetSearchTimeOut(10000);
								HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(GAMES_SELECT_DIFFICULTY));
								if (FAILED(hr))
								{
									// this is not the first time chess is being opened.
									LogTestInfoW(__FUNCTIONW__, L"Select Difficulty window was not open. Moving forward.");
								}
								else
								{
									LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
								}

								// restore original timeout
								SetSearchTimeOut(originalTimeout);
							}

							// Now close the game.
							if (SUCCEEDED(FromPartialQueryId(
								(wchar_t*)rg_Games_Close[gamesIndex], 
								(wchar_t*)rg_Games_Close[gamesIndex + 1], 
								(wchar_t*)rg_Games_Close[gamesIndex + 2])))
							{
								LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
								pwszResultInfo = L"Entry point is differentiated correctly";
								LogTestInfoW(__FUNCTIONW__,
									L"Entry point results.[Current: %s | Expected: %s ]",
									fFoundGameClickablePoint ? L"Found": L"Not Found",
									fExpected ? L"Found" : L"Not Found");  
							}
							else
							{
								fPassed = FALSE;
							}
						}
					}
				}
				else
				{
					if (fExpected)
					{
						pwszResultInfo = L"Entry point is not differentiated correctly";
						LogTestInfoW(__FUNCTIONW__,
							L"Premium Games SKU differentiation failed.[Current: %s | Expected: %s ]",
							fFoundGameClickablePoint ? L"Found": L"Not Found",
							fExpected ? L"Found" : L"Not Found");
					}
					else
					{
						pwszResultInfo = L"Premium Games Entry point is differentiated correctly";
						fPassed = TRUE;
					}
					break;
				}
			}
		}
		LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");

		HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(GAMES_CLOSE_BTN));
		if (SUCCEEDED(hr))
		{
			LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
		}
	} 

	LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
	return NOERROR;
}


//    
//    VerifyGames_DefaultInstalledGamesEntryPoint 
//  
STDAPI VerifyGames_DefaultInstalledGamesEntryPoint(LPVOID pvReserved)
{
	BOOL    fPassed = FALSE;
	LPWSTR pwszResultInfo = NULL;
	BOOL fExpected = AreDefaultInstalledGamesExpected();

	LogTestBeginW(__FUNCTIONW__, L"Verify Default Installed Games are available in Games Explorer");    

	EnableInfoWindow(TRUE);

	
	wchar_t FreeCell[1024] = L"###";
	if SUCCEEDED(GetNameFromGDF("c:\\program files\\microsoft games\\freecell\\freecell.exe", FreeCell+3))
	{
		StringCchCatW(FreeCell,1024,L"###");
		LogTestInfoW(__FUNCTIONW__,L"Using Value: %s", FreeCell);
		rg_Games_Open[FREECELL + 2] = FreeCell;
	}
	wchar_t Hearts[1024] = L"###";
	if SUCCEEDED(GetNameFromGDF("c:\\program files\\microsoft games\\hearts\\hearts.exe", Hearts+3))
	{
		StringCchCatW(Hearts,1024,L"###");
		LogTestInfoW(__FUNCTIONW__,L"Using Value: %s", Hearts);
		rg_Games_Open[HEARTS + 2] = Hearts;
	}
	
	

	// There are two ways to get to the games explorer depending on the SKU installed.
	// Business/Enterprise : Games are not installed by default. Go to Start->All Programs-> Games
	// All other SKUs      : Games are installed by default. Go to Start-> Games.
	if (OpenGamesExplorer())
	{
		// loop starting from FREECELL to HEARTS.
		for (int gamesIndex = FREECELL; gamesIndex <= HEARTS; gamesIndex += 3)
		{
			BOOL fFoundGameClickablePoint = FALSE;
			if (SUCCEEDED(FromPartialQueryId(
				(wchar_t*)rg_Games_Open[gamesIndex], 
				(wchar_t*)rg_Games_Open[gamesIndex + 1], 
				(wchar_t*)rg_Games_Open[gamesIndex + 2])))
			{
				int x, y;
				fFoundGameClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));

				LogTestInfoW(__FUNCTIONW__,
					L"%s Clickable point ", fFoundGameClickablePoint ? L"Found": L"Did not find");

				if (fFoundGameClickablePoint != fExpected)
				{
					pwszResultInfo = L"Entry point is not differentiated correctly";
					LogTestInfoW(__FUNCTIONW__,
						L"Default Installed Games SKU differentiation failed.[Current: %s | Expected: %s ]",
						fFoundGameClickablePoint ? L"Found": L"Not Found",
						fExpected ? L"Found" : L"Not Found");
					break;
				}
				else
				{
					fPassed = TRUE;
					if (fExpected)
					{
						// Go ahead and open the game.
						LOG_FAILED_HR(DoubleClick(CLICKABLE_POINT));

						// Now close the game.
						if (SUCCEEDED(FromPartialQueryId(
							(wchar_t*)rg_Games_Close[gamesIndex], 
							(wchar_t*)rg_Games_Close[gamesIndex + 1], 
							(wchar_t*)rg_Games_Close[gamesIndex + 2])))
						{
							LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
							pwszResultInfo = L"Entry point is differentiated correctly";
							LogTestInfoW(__FUNCTIONW__,
								L"Entry point results.[Current: %s | Expected: %s ]",
								fFoundGameClickablePoint ? L"Found": L"Not Found",
								fExpected ? L"Found" : L"Not Found");  
						}
						else
						{
							fPassed = FALSE;
						}
					}
				}
			}
			else
			{
				if (fExpected)
				{
					pwszResultInfo = L"Entry point is not differentiated correctly";
					LogTestInfoW(__FUNCTIONW__,
						L"Default Installed Games SKU differentiation failed.[Current: %s | Expected: %s ]",
						fFoundGameClickablePoint ? L"Found": L"Not Found",
						fExpected ? L"Found" : L"Not Found");
				}
				else
				{
					pwszResultInfo = L"Default Installed Games Entry point is differentiated correctly";
					fPassed = TRUE;
				}
				break;
			}
		}
	}

	LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");

	HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(GAMES_CLOSE_BTN));
	if (SUCCEEDED(hr))
	{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	}

	LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
	return NOERROR;
}

//    
//    VerifyGames_WindowsFeaturesEntryPoint 
//  
STDAPI VerifyGames_WindowsFeaturesEntryPoint(LPVOID pvReserved)
{
	BOOL    fPassed = FALSE;
	LPWSTR pwszResultInfo = NULL;
	BOOL fExpected = ArePremiumGamesExpected();
	HRESULT hr;
	LogTestBeginW(__FUNCTIONW__, L"Verify Premium Games are available in OCM");    

	//EnableInfoWindow(TRUE);

	wchar_t Section[1024];
	wchar_t Link[1024];	

	if (SUCCEEDED(GlobalizeQueryId(Section, 1024, CPL_LINK_PROGRAMS)) &&
		SUCCEEDED(GlobalizeQueryId(Link, 1024, CPL_LINK_PROGRAMSFEATURES)) &&
		OpenSpecificHomeControlPanel(Section, Link) == TRUE)
	{
		hr = LOG_FAILED_HR(FromPartialQueryId(WINDOWS_FEATURES_GAMES));
		if (SUCCEEDED(hr))  
		{
			LOG_FAILED_HR(Expand());

			// loop starting from MAHJONG_TITANS to CHESS_TITANS.
			for (int gamesIndex = MAHJONG_TITANS; gamesIndex <= CHESS_TITANS; gamesIndex += 3)
			{
				BOOL fFoundGameClickablePoint = FALSE; 
				if (SUCCEEDED(FromPartialQueryId(
					(wchar_t*)rg_WindowsFeaturesGames[gamesIndex], 
					(wchar_t*)rg_WindowsFeaturesGames[gamesIndex + 1], 
					(wchar_t*)rg_WindowsFeaturesGames[gamesIndex + 2])))
				{
					// To ascertain presence/absence, look for the clickable point.
					int x, y;
					fFoundGameClickablePoint = SUCCEEDED(LOG_FAILED_HR(GetClickablePoint(&x, &y)));
					LogTestInfoW(__FUNCTIONW__,
						L"%s Clickable point for Mahjong Titans", 
						fFoundGameClickablePoint ? L"Found": L"Did not find");

					if (fFoundGameClickablePoint != fExpected)
					{
						pwszResultInfo = L"Windows Features Games entry point is NOT differentiated correctly";
						LogTestInfoW(__FUNCTIONW__,
							L"Windows Features Premium Games SKU differentiation failed.[Current: %s | Expected: %s ]",
							fFoundGameClickablePoint ? L"Found": L"Not Found",
							fExpected ? L"Found" : L"Not Found");
						break;
					}
					else
					{
						fPassed = TRUE;
						pwszResultInfo = L"Premium Games Windows Features entry point is differentiated correctly";

						// Go ahead and click Mahjong Titans and then check for Chess Titans as well.
						if (fExpected)
						{
							LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
						}
					}
				}
				else
				{
					if (fExpected)
					{
						pwszResultInfo = L"Windows Features Games entry point is NOT differentiated correctly";
						LogTestInfoW(__FUNCTIONW__,
							L"Windows Features Premium Games SKU differentiation failed.[Current: %s | Expected: %s ]",
							fFoundGameClickablePoint ? L"Found": L"Not Found",
							fExpected ? L"Found" : L"Not Found");
					}
					else
					{
						pwszResultInfo = L"Windows Features Games entry point is differentiated correctly";
						fPassed = TRUE;
					}
					break;
				}
			}
		}
	}
	else
	{
		LogTestInfoW(__FUNCTIONW__, L"Could not open Control Panel");
	}

	LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");

	hr = LOG_FAILED_HR(FromPartialQueryId(WINDOWS_FEATURES_CLOSE));
	if (SUCCEEDED(hr))
	{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	}
	hr = LOG_FAILED_HR(FromPartialQueryId(CPL_CLOSE_BTN));
	if (SUCCEEDED(hr))
	{
		LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
	}

	LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
	return NOERROR;
}



